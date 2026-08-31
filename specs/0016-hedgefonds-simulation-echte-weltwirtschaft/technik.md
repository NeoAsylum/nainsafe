---
typ: technik
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-08-31
fassung: 2 (nach ventures/0016-.../befunde/pruefung-entwurf-2026-08-31.md)
stack: Rust (stabile Kette, Edition 2021); Kern ohne jede Fremdabhängigkeit und ohne Gleitkommatyp; Oberfläche egui/eframe (MIT OR Apache-2.0)
determinismus: i64-Festkomma mit deklarierter Skala je Größenklasse, feste Iterationsreihenfolge über Indexlisten, ein Wurzelstartwert mit abgeleiteten Strömen, Weltschritt ohne jede Ziehung
zustand: fester, allokationsfreier Wert, 310 i64 (2.480 Byte), Prüfsumme über kanonische Byteform
speicherstand: Startwert plus Aktionsfolge plus Prüfsumme -- nicht der Zustand
kalibrierung: alle Zahlenwerte in einer Parameterdatei ausserhalb des Codes, mitgehasht
partie: 28 Runden; 28 Weltschritte mit dem Heuristikbot, 1.708 mit dem Suchbot
tick_planwert: 10 Mikrosekunden je Weltschritt (Bandbreite 5 bis 30), vom Prüfstand zu messen
nachtlauf: 13.789.108 Weltschritte, 2,3 Minuten auf einem Kern beim Planwert, 11,5 Minuten im ungünstigen Fall
---

# Der Kern ist eine reine Ganzzahlfunktion ohne Ziehung -- damit ist Determinismus keine Disziplin, sondern eine Eigenschaft des Typsystems.

Zweite Fassung. Die Abarbeitung der acht Befunde steht am Ende der Datei; die Rechenzeit
ist auf die 28-Runden-Partie der zweiten Fassung von `spiel.md` neu gerechnet.

Die Vorgaben sind mit **T1** bis **T37** durchnummeriert. Der Builder weicht von keiner ab,
ohne dass ein ADR sie aufhebt; der Prüfer zitiert die Nummer, statt sie zu umschreiben.
**Die Nummern von Fassung eins behalten ihre Bedeutung**, damit die Prüfung vom 2026-08-31
zitierbar bleibt; neue Vorgaben tragen die nächsten freien Nummern und stehen dort, wo sie
inhaltlich hingehören. Die Nummerierung ist deshalb innerhalb der Abschnitte nicht
fortlaufend.

## 1. Stack

**T1 — Kern, Datenschicht, Schnittstelle, Prüfstand und Werkzeuge in Rust**, stabile
Toolchain, in `rust-toolchain.toml` auf eine Version festgenagelt, Abhängigkeiten
mit `cargo vendor` im Repo eingefroren.

Zwei Sätze Begründung, wie verlangt. **Erstens:** Rust ist die einzige verbreitete Sprache,
in der sich die drei Determinismusregeln vom Werkzeug erzwingen lassen statt von der
Sorgfalt des nächsten Agenten — `i64`/`i128` mit `overflow-checks = true` auch im
Freigabeprofil, `BTreeMap` und `Vec` statt streuender Mengen, und ein Kern-Kasten ohne
jeden Gleitkommatyp, was ein Prüfer mit einem einzigen `grep` nachweist.
**Zweitens:** Der Prüfstand entscheidet über den einzigen Vorsprung dieser Fabrik, und er
kostet knapp 14 Millionen Weltschritte je Nacht — in einer übersetzten Sprache sind das
Minuten, in einer gedeuteten Stunden (Abschnitt 10 rechnet es vor). Dass ein einzelnes
Programm ohne Laufzeitumgebung herausfällt, das Steam unverändert ausliefert, ist der
dritte Grund und der einzige, der den Betreiber betrifft.

**Der Einwand gegen die Wahl gehört dazu.** Die Rolle verbietet exotische Stacks. Rust ist
nicht exotisch, aber es ist auch nicht Python: Ein Bauagent braucht mehr Anläufe bis zum
grünen Übersetzungslauf, und Umbauten am Zustandsgraphen kosten Nacharbeit am Ausleihprüfer.
Der Tausch ist bewusst: Autorenaufwand gegen mechanisch nachweisbaren Determinismus und
gegen einen Prüfstand, der täglich läuft. Fällt der Prüfstand aus dem Nachtlauf, ist das
Produkt für diese Fabrik wertlos — der Autorenaufwand ist dagegen nur teuer.

**T2 — Der Kasten `kern` hat null Fremdabhängigkeiten** und trägt `#![forbid(unsafe_code)]`.
Kein `serde`, kein Zufallskasten, keine Zeit, keine Ein- und Ausgabe. Ein Kasten ohne
Abhängigkeiten kann durch kein fremdes Versionsupdate sein Ergebnis ändern.

**T3 — Die Abhängigkeiten ausserhalb des Kerns sind abschliessend aufgezählt:**
`serde` und `serde_json` (Protokoll), `toml` (Parameterdatei), `eframe`/`egui` und
`egui_plot` (Oberfläche), `rayon` (Prüfstand), `sha2` (nur in `werkzeuge`, für
Datei-Prüfsummen). Alle unter MIT oder Apache-2.0. egui und eframe sind unter
„MIT OR Apache-2.0" doppelt lizenziert, eframe nennt Linux, Mac und Windows ausdrücklich
als Ziele (github.com/emilk/egui, abgerufen 2026-08-31). Eine Abhängigkeit mehr braucht
einen ADR.

**Ausdrücklich nicht gewählt:** Eine Spiel-Engine (Godot, Unity, Bevy) — sie bringt eine
Bildschleife, eine Zeitachse und eine eigene Zahlenwelt mit, also genau die drei Quellen
von Nichtreproduzierbarkeit, die hier ausgeschlossen werden sollen; das Spiel braucht
Tabellen, Verlaufsgraphen und eine Kettenansicht. Eine Netzoberfläche (Electron, Tauri) —
JavaScript kennt keinen Ganzzahltyp, und ein versehentliches `/` erzeugt still eine
Gleitkommazahl. Python — siehe die Rechnung in Abschnitt 10. Steamworks-SDK — für den
ersten Titel nicht nötig (keine Erfolge, kein Wolkenspeicher), also eine Abhängigkeit und
ein Konto weniger.

## 2. Der deterministische Kern

**T4 — Keine Gleitkommazahl im Kern, in der Datenschicht und im Protokoll.** Kein `f32`,
kein `f64`, kein `sqrt`, kein `powf`, kein `ln`. Nachweis: `grep -rn 'f32\|f64' kern/`
liefert nichts, und `clippy::float_arithmetic` ist im Kern auf `deny`. Auch die
Parameterdatei wird ohne Gleitkomma gelesen — Dezimalzeichenketten werden direkt in
skalierte Ganzzahlen zerlegt, nie über `parse::<f64>()`.

**T5 — Jede Größenklasse hat eine deklarierte Skala.** Der Typ ist überall `i64`, die
Bedeutung steht in dieser Tabelle und nirgends sonst:

| Klasse | Einheit | Beispiel | Bereich |
|---|---|---|---|
| Fondsgeld (Kasse, Position, Hebel, Anlegerbestand) | US-Cent | 4.200.000.000 = 42 Mio USD | ±9,2·10^16 USD |
| Volkswirtschaftliche Beträge (BIP, Wertschöpfung, Kapitalstock, Handelsstrom, Marktkorbwert) | Tausend USD zu konstanten Preisen des Basisjahrs | 21.000.000.000 = 21 Bio USD | reichlich |
| Raten (Zins, Inflation, Zoll, Haushaltssaldo, Schuldenquote, Rendite, Überrendite) | Basispunkte (1 bp = 0,01 %) | 250 = 2,50 % | ±2 Mio % |
| Anteile (Sektoranteil, Marktanteil, Einfluss, Zustimmung, `handelsanteil`) | Zehntausendstel | 10.000 = 100 % | 0 bis 10.000 |
| Preise und Preisniveaus | Index, Startjahr = 10.000 | 12.500 = +25 % | siehe T8 |
| Wechselkurs | Index gegen USD, Startjahr = 10.000 | 8.000 = Aufwertung um 25 % | siehe T8 |
| Ergebnis einer Partie | Milli-Runden | 27.000 = Runde 27,0 | siehe T34 |

Einfluss und Zustimmung erscheinen dem Spieler als 0 bis 100 (so nennt sie `spiel.md`);
gespeichert sind sie in Zehntausendsteln, damit die Gegenkräfte unterhalb eines
sichtbaren Punktes noch rechnen können. Die Umrechnung findet in der Sicht statt.

**Zwischen Fondsskala und volkswirtschaftlicher Skala liegt der Faktor 100.000, und er wird
an genau einer Stelle überschritten:** `cent_in_tsd` und `tsd_in_cent`, beide mit der
Rundung aus T6; jede andere Vermischung ist ein Fehler. Der Fonds bewegt Preise auf
Märkten, deren Größen in einer anderen Einheit stehen als sein Geld — das ist die
wahrscheinlichste stille Fehlerquelle des Modells.

**T6 — Genau eine Rundungsregel, und `/` auf Zustandsgrößen ist verboten.** Alle Divisionen
laufen über `teile_gerundet(zaehler, nenner)` mit Rundung **auf halbe Beträge vom Null
weg**. Grund: Rusts `/` schneidet gegen null ab und ist damit über dem Vorzeichen
unsymmetrisch — bei einem Fonds, der nach `spiel.md` ausdrücklich long **und** short sein
können soll, würde das eine Richtung still bevorzugen und Maß 2 verfälschen. Ebenso
verpflichtend: `mal_geteilt(a, b, c)` rechnet `a·b/c` über ein `i128`-Zwischenergebnis;
die naive Form läuft bei Beträgen in Cent mal Anteilen in Zehntausendsteln über.

**T7 — Überlauf ist ein Absturz, kein Umlauf.** `overflow-checks = true` auch im
Freigabeprofil. Rust schaltet die Prüfung im Freigabeprofil ab und läuft dann still im
Zweierkomplement um (doc.rust-lang.org/book/ch03-02-data-types.html, abgerufen
2026-08-31) — ein stiller Umlauf würde einen Regressionsbestand vergiften, statt ihn rot
zu machen. Die Kosten sind wenige Prozent und in Abschnitt 10 eingerechnet.

**T8 — Preisniveau und Wechselkurs werden geführt und neu basiert. Die Vorgabe bleibt, ihre
Begründung wechselt.** Der Prüfjahrgang beginnt nach `spiel.md` 1995, also nach dem Plano
Real; dort tritt die Neubasierung nie ein. Sie bleibt trotzdem, weil `spiel.md` die
Jahrgänge vor 1995 ausdrücklich als **Spieljahrgänge** erhält und Brasilien zwischen 1980
und 1994 rund zwölf Nullen gestrichen hat. Regel: Übersteigt der Preisindex eines Landes
das 100.000-fache seines Startwerts, werden Index, Wechselkurs und alle nominalen Größen
dieses Landes durch 1.000 geteilt und der Zähler `basiswechsel` erhöht.

Weil sie im Prüfjahrgang nie greift, wäre sie ungeprüfter Code. Auflage an den
Testentwickler: Mindestens eine Partie im Regressionsbestand (T31) läuft auf einem
Spieljahrgang 1980 und durchläuft einen Basiswechsel. Ein Zweig, den der Nachtlauf nie
betritt, ist ein Zweig, den niemand kennt.

**Der Rückvergleich läuft für Preise und Wechselkurse auf Jahresänderungsraten in
Basispunkten, nicht auf Niveaus.** Das gilt unabhängig von der Neubasierung: Ein
prozentualer Fehler auf einem Niveau, das über 28 Jahre um eine Größenordnung wandert,
misst den Anfang und nicht die Maschine.

**T9 — Feste Reihenfolge, keine streuenden Behälter.** Länder, Sektoren, Instrumente und
Handelspaare sind dichte Indexlisten (`Vec` fester Länge, angesprochen über `LandId(u8)`,
`SektorId(u8)`, `InstrumentId(u8)`). `HashMap` und `HashSet` sind im Kern verboten;
gebraucht wird eine Zuordnung, ist es ein `BTreeMap`. Die sechs Schritte der Runde laufen
in der Reihenfolge aus `spiel.md`, Abschnitt „Die Schleife", und diese Reihenfolge steht
als benannte Konstantenliste im Code, damit ein Umstellen sichtbar wird.

**T10 — Der Weltschritt zieht nicht.** Nach `spiel.md` ist jede Regel eine Schwelle, ein
Zähler oder eine Rechnung; auch der Innerjahresausschlag folgt „deterministisch aus der
Jahresbewegung und der historischen Schwankungsbreite". Also gilt:
`schritt(zustand, aktionen)` ist eine **reine Funktion ohne Zufallsargument**. Das ist die
billigste Art, Anforderung 1 zu erfüllen, und sie macht den Rückvergleich zu einer exakt
wiederholbaren Rechnung.

**T11 — Zufall gibt es nur an zwei Stellen, und er hängt an einem Wurzelstartwert.**
Erstens die Streuung der Startjahrgänge (ein Spiel soll nicht immer identisch beginnen),
zweitens die Bots und Stichproben des Prüfstands. Der Erzeuger ist selbst geschrieben —
SplitMix64 zur Ableitung, xoshiro256\*\* zur Erzeugung, zwanzig Zeilen, im Repo
festgeschrieben, **kein Kasten** (T2): Ein Versionssprung eines fremden Zufallskastens
würde sonst jede gespeicherte Partie entwerten.

Jeder Strom wird **abgeleitet**, nicht fortgeschrieben. Das Tupel ist gegenüber Fassung
eins erweitert, weil `spiel.md` den Startwert von Maß 1 ausdrücklich aus Jahrgang und
Parametersatz mit ableitet:

```
strom = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme,
                   zweck_id, runde, index)
```

Ein fortlaufender Strom hätte die Eigenschaft, dass eine einzige neue Ziehung irgendwo alle
späteren Ziehungen verschiebt und damit den ganzen Regressionsbestand rot macht, ohne dass
sich etwas Inhaltliches geändert hätte. Das ist die Vorgabe, an der später der Unterschied
zwischen „verbessern" und „verändern" hängt. Die `zweck_id` ist eine benannte Aufzählung
(`JAHRGANGSSTREUUNG`, `ZUFALLSBOT`, `BUENDELZIEHUNG`, `SUCHBOT_KANDIDATEN`) und wird nie
über eine Zahl geschrieben.

**T12 — Kanonische Byteform und Prüfsumme.** `Zustand` wird über eine ausdrücklich
geschriebene Funktion in Bytes gefasst (feste Feldreihenfolge, `i64` in Little-Endian),
**nie über die Speicheranordnung der Struktur**. Darüber läuft FNV-1a-64, ebenfalls im
Kern implementiert. Diese Prüfsumme ist die Währung aller Regressionstests.

## 3. Trennung von Modell und Darstellung

**T13 — Die Kastenrichtung ist die Trennung, und `cargo` erzwingt sie.**

```
kern            (keine Abhängigkeit)      Zustand, Regeln, Kette, Festkomma, Zufall, Prüfsumme
  ^
daten           -> kern                   Jahrgang laden, Sollreihen, Parameterdatei
  ^
schnittstelle   -> kern, daten            Protokoll, drei Zustandsebenen, Partieformat
  ^          ^
konsole      pruefstand                   Binärprogramme: Text und Protokoll / Bots und Maße
  ^
oberflaeche  -> schnittstelle             Binärprogramm: egui
werkzeuge/aufbereitung -> daten           einmal je Jahrgang: Rohdaten -> Jahrgang
```

`kern` kennt weder Bildschirm noch Datei noch Uhr. Dass das Modell die Sicht nie etwas
fragt, ist damit keine Verabredung, sondern scheitert am Übersetzer, sobald es jemand
versucht.

**T14 — Die Textoberfläche ist Teil des Produkts, nicht Werkzeug.** `konsole` spielt das
Spiel vollständig — Zustand in drei Ebenen, Aktionen, Speichern, Laden. Sie ist zugleich
die Schnittstelle, über die Agenten spielen (Anforderung 3), und der Rückfallweg, falls
die grafische Oberfläche je klemmt. Was `oberflaeche` zeigt, muss aus der Ausgabe von
`konsole` ableitbar sein; ist es das nicht, gehört es in den Kern.

## 4. Datenmodell

**T15 — `Zustand` ist ein Wert fester Größe ohne Speicheranforderung: 310 `i64`, also
2.480 Byte.** Feste Felder, feste Arrays, keine `Vec`, kein `String`, kein
`Option<Box<…>>`. `Clone` ist damit ein Speicherumzug von 2,5 kB (etwa 200 Nanosekunden) —
die Voraussetzung dafür, dass der Prüfstand Millionen von Nachspielen aus Zwischenständen
startet.

Fünf Gebiete (USA, China, Deutschland, Brasilien, Restwelt), drei Sektoren, davon zwei mit
Handelszeilen, vier Politikinstrumente. **Jede Zeile nennt ihre Herkunft in `spiel.md`,
damit die Summe nachzählbar ist** (Befund 8):

| Gruppe | Felder | Anzahl | Herkunft in `spiel.md` |
|---|---|---:|---|
| je Sektor (3×) | Wertschöpfung, Kapitalstock, Beschäftigung, Sektorpreis | 12 | „Der Zustand", Je Land |
| Aggregat | Bevölkerung, Erwerbstätige, Produktivität, Preisniveau, Inflation, Leitzins, Wechselkurs, Staatsschuld, Haushaltssaldo | 9 | ebd. |
| politisch | Zustimmung, Aufsichtszähler, Einfluss | 3 | ebd. |
| Instrumente (4×) | Stand, anliegender Druck, Gegendruck, Restverzögerung | 16 | ebd. |
| Restdauern | `marktverbot_rest`, `lobbykosten_rest`, `regierungsdruck_rest` | 3 | Gegenkraft 1 (dritte Schwelle) und Gegenkraft 2 |
| Buchhaltung | `basiswechsel` | 1 | T8 |
| **je spielbarem Land** | | **44** | |
| **vier spielbare Länder** | | **176** | |
| **Restwelt** | Sektoren 12 + Aggregat 9 + `basiswechsel` 1; **keine** Instrumente, Zustimmung, Aufsicht, Einfluss, Restdauern | **22** | „Die Restwelt" |
| Handel | Gebiet × Gegenüber × handelbarer Sektor = 5 × 4 × 2 | 40 | „Handel" |
| Weltpreise | je handelbarem Sektor | 2 | „Was für die Preisbildung gelten muss" |
| Nachahmerzähler | Land × Sektor = 4 × 3 | 12 | „Der Fonds" |
| Marktkorb | `markt.wert`, `markt.rendite` | 2 | „Der Fonds", Marktrendite; Regel in T33 |
| Fonds, Aggregat | Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil | 5 | „Der Fonds" |
| Fonds, Überrendite | letzte drei Runden | 3 | ebd. |
| Positionssteckplätze | 12 Land×Sektor, 4 Währung, 4 Anleihe | 20 | ebd., T16 |
| Beteiligungen | 12 Land×Sektor × (Anteil, Restdauer des Ausstiegs) | 24 | Aktion 2 |
| Partie | Runde, Jahrgangskennung, Parametersatz-Prüfsumme, Mandatsstand | 4 | — |
| **Summe** | | **310** | |

Nachrechnung: `4 × 44 + 22 = 198` für die Gebiete, `40 + 2 + 12 + 2 = 56` für die Welt,
`5 + 3 + 20 + 24 = 52` für den Fonds, `4` für die Partie. `198 + 56 + 52 + 4 = 310`.
`spiel.md` nennt „rund 300"; die Abweichung sind die drei Restdauerzähler je Land und die
beiden Marktkorbfelder, die dort im Fließtext, aber nicht in der Aufzählung stehen.

**Die drei Restdauerzähler sind keine Erfindung, sondern die Ausführbarkeit zweier
Gegenkräfte.** Gegenkraft 1 verhängt „ein Marktverbot in diesem Land für mehrere Runden",
Gegenkraft 2 „verdoppelt die Lobbykosten des Fonds für mehrere Runden" und lässt die neue
Regierung „alle Instrumente in Richtung ihres historischen Mittels zurücksetzen" — was
über mehrere Runden läuft, weil ein Instrument sich je Runde höchstens einen Schritt bewegt.
Drei Regeln mit Nachwirkung brauchen drei Zähler; ohne sie ist die Regel nicht
aufschreibbar. Sie sind nach `spiel.md`, „Keine verdeckte Größe", im Zustand sichtbar.

**T16 — Positionen sind Steckplätze, keine Liste.** Es gibt genau zwanzig mögliche
Positionen; eine Position ist eine vorzeichenbehaftete Stufenzahl auf einem festen Platz,
null heisst „keine". Damit entfällt jede Frage nach Höchstzahl, Reihenfolge und
Zusammenlegung, und der Zustand bleibt vergleichbar (T12).

**Ein Steckplatz ist dauerhaft leer:** die Währung USA. Der US-Dollar ist der Numéraire,
eine Position darauf wäre gegen sich selbst gerichtet. Der Platz bleibt für die
gleichförmige Adressierung (T17), die Zulässigkeitsprüfung bietet ihn nie an (T32).
Spielbar sind 19 der 20 Plätze; wer 20 zählt, zählt Adressen, nicht Möglichkeiten.

**T17 — Jede Größe hat eine stabile Adresse.** `land.DE.sektor.2.preis`,
`land.BR.instrument.zoll.stand`, `fonds.position.CN.1`, `handel.DE.CN.1`, `markt.rendite`.
Diese Adressen erscheinen im Protokoll, in der Kette, in den Testvorlagen und in der
Oberfläche. Sie sind Teil der Schnittstellenversion: Wer eine umbenennt, macht den
Regressionsbestand ungültig und braucht einen ADR.

**T18 — Die Kette wird erzeugt, nicht rekonstruiert — und jede Größe wird je Runde genau
einmal geschrieben.** Die Felder von `Zustand` sind ausserhalb des Kerns nicht schreibbar;
innerhalb schreibt niemand direkt, sondern über
`Schreiber::setze(adresse, wert, ursache, verzoegerung, beitrag)`. Jeder Aufruf hängt einen
`Ursachensatz` an:

| Feld | Inhalt |
|---|---|
| `runde` | in welcher Runde geschrieben |
| `ziel` | Adresse nach T17 |
| `alt`, `neu` | Werte in der Skala der Größe |
| `ursache` | `Aktion{nr}` \| `Instrument{land,instr}` \| `Gegenkraft{art}` \| `Markträumung{sektor}` \| `Vortrag{adresse}` \| `Jahrgang` |
| `verzoegerung` | wie viele Runden zwischen Ursache und Wirkung lagen |
| `beitrag` | Anteil dieser Ursache an der Änderung, in Promille |

Der `Schreiber` führt ein Bitfeld über alle 310 Adressen. **Ein zweiter Schreibzugriff auf
dieselbe Adresse in derselben Runde ist ein harter Fehler**, kein überschreibender Wert.
Das ist die maschinelle Fassung der Vorgabe aus `spiel.md` („Innerhalb einer Runde wird jede
Zustandsgröße genau einmal geschrieben, und die Reihenfolge ist zyklenfrei") und zugleich
die billigste Art, die dortige Behauptung über **sieben** rundenübergreifende
Rückkopplungskanäle prüfbar zu machen: Eine Rückkopplung innerhalb der Runde erzeugt
zwangsläufig einen zweiten Schreibzugriff und stirbt hier, statt als achter Kanal unbemerkt
zu entstehen. Kosten: 40 Byte je Runde, ein Bittest je Schreibzugriff.

Die Kette ist zugleich das verkaufte Merkmal („the consequences of choices often feel
intangible"), die Antwort auf G8 und der Gegenstand der Regressionsprüfung. Wird sie
nachträglich aus zwei Zuständen erschlossen, ist sie geraten; wird sie beim Schreiben
mitgeführt, ist sie wahr.

**T19 — Die Kette gehört nicht in den Zustand.** `schritt` liefert
`(neuer_zustand, kette_dieser_runde)`; die Sitzung sammelt die Ketten in einem `Verlauf`.
So bleibt `Zustand` klein und vergleichbar, und der Prüfstand kann die Ketten wegwerfen,
wenn er nur Ergebnisse zählt. Die Aufnahmekapazität je Runde ist fest; wird sie erreicht,
ist das ein harter Fehler und keine stille Kürzung — eine gekürzte Kette wäre eine Lüge
gegenüber dem Käufer.

## 5. Die drei Zustandsebenen (G8)

**T20 — Drei Abfragen, zwei Ausgabeformen, eine Quelle.** Jede Ebene entsteht aus
demselben Datentyp und wird entweder als Text (für Menschen und Logbücher) oder als
JSON-Zeile (für Agenten und Oberfläche) ausgegeben. Ganzzahlen bleiben Ganzzahlen; die
Skala steht im Kopf der Antwort, geteilt wird erst in der Sicht.

- **`uebersicht`** — eine Zeile je Gebiet, eine je Fonds, eine für den Markt:
  `DE | BIP 3.412 | Zins 250bp | Zoll 380bp | Haushalt -210bp | Fondsanteil 420 | Einfluss 1.700`
- **`detail <adresse>`** — ein Objekt vollständig, für **jede** adressierbare Einheit nach
  T17, nicht nur für Länder: `land.US`, `fonds`, `land.BR.instrument.zoll`,
  `land.CN.sektor.1`, `markt`.
- **`diff <von> <bis>`** — je geänderter Größe alt, neu, Änderung **und die Ursachenkette
  aus T18**, rückwärts aufgelöst bis zur auslösenden Aktion oder Gegenkraft, mit
  Verzögerung und Beitrag je Glied. Der Unterschied zweier Zustände sagt *was*, die Kette
  sagt *warum*; ausgegeben wird beides, massgeblich ist die Kette.

## 6. Maschinenschnittstelle und Partieformat

**T21 — Ein Befehl je Zeile, eine JSON-Antwort je Zeile, über Standardein- und -ausgabe.**
Kein Netzdienst, kein Anschluss, keine Zugangsdaten — damit auch keine Berührung mit
Hausregel 2. Befehle: `neu {jahrgang, startwert}`, `zustand {ebene, adresse}`,
`aktionen` (die zulässigen dieser Runde), `setze {aktionen: […]}`, `runde`,
`kette {von, bis}`, `speichern {pfad}`, `laden {pfad}`, `pruefsumme`.
Jede Antwort trägt `schema_version`. Eine mitgeschriebene Sitzung ist damit von selbst
eine Testvorlage.

**T32 — Die Liste der zulässigen Aktionen hat eine kanonische Ordnung, und sie ist Teil der
Schnittstellenversion.** Sortiert wird nach `(Aktionsart 1…5, Zielkennung, Stufe)`; die
Zielkennung ist die feste Indexordnung aus T9. Grund: Maß 1 zieht nach `spiel.md` Aktionen
**ohne Zurücklegen aus der Liste der in dieser Runde zulässigen Aktionen** (T35). Wäre die
Ordnung eine Nebenwirkung der Erzeugung, hinge die Entscheidungsdichte an einer
Schleifenreihenfolge, die niemand aufgeschrieben hat. Die Ordnung ändern entwertet den
Regressionsbestand und braucht einen ADR.

**T22 — Ein Speicherstand ist Startwert plus Aktionsfolge plus Prüfsumme, nicht der
Zustand.** Datei: `{schema_version, jahrgang_id, daten_pruefsumme, parameter_pruefsumme,
startwert, aktionen: [[runde, aktion…]], end_pruefsumme}`. Beim Laden wird die Partie
nachgerechnet und die Prüfsumme verglichen; weicht sie ab, meldet das Programm einen
Determinismusbruch, statt weiterzuspielen. Drei Gewinne auf einmal: Der Käufer bemerkt
einen Determinismusfehler zuerst, der Regressionsbestand **ist** der Speicherordner, und
eine Datei bleibt unter zwei Kilobyte. Kosten: 28 Weltschritte beim Laden, also
0,28 Millisekunden.

## 7. Datenschicht

**T23 — Der Jahrgang ist ein Erzeugnis, kein Programmteil.** `werkzeuge/aufbereitung`
liest die eingefrorenen Rohdateien und schreibt `jahrgang-<jahr>.bin`,
`sollreihen-<jahr>.bin` und ein `manifest.toml` mit SHA-256 je Ein- und Ausgabe, Quelle,
Lizenz und Abrufdatum. Der Bau des Spiels lädt **nichts** aus dem Netz. Der Jahrgang
enthält:

1. **Startwerte** für jede Zustandsgröße mit Datenanker;
2. **Sollreihen** für die 31 Reihen aus `spiel.md` plus den Handelsblock, je Reihe mit der
   Klassifikation aus T37;
3. **historische Politikpfade** für Leitzins, Zollniveau und Haushaltssaldo. Der vierte
   Hebel, Finanzmarktregulierung, hat keinen Anker und steht im Rückvergleich fest auf
   seinem Startwert — was das Orakel für dieses Instrument blind macht, und das gehört in
   jeden Befund;
4. **exogene Pfade** nach T25;
5. **Konstanten des Jahrgangs**: `handelsanteil[Gebiet][handelbarer Sektor]`, also zehn
   Werte in Zehntausendsteln, gebildet als (Ausfuhr + Einfuhr des Sektors) geteilt durch
   seine Wertschöpfung im Startjahr, aus BACI und WDI. `spiel.md` macht diesen Koeffizienten
   zum Träger der gesamten Sektorwirkung eines Zolls; er ist exogen und über die Partie
   konstant, steht also im Jahrgang und nicht im Zustand;
6. **abgeleitete Kennzahlen**: die mittlere absolute Jahresänderung je Land als
   Schwankungsbreite für den Innerjahresausschlag. Mittlere absolute Abweichung, nicht
   Standardabweichung — die bräuchte eine Wurzel und damit Gleitkomma (T4);
7. **Normierung**: die drei Sektoranteile je Gebiet und Jahr werden auf 10.000 normiert,
   weil die WDI-Anteile wegen der Gütersteuern abzüglich Subventionen nicht auf 100 Prozent
   summieren. Die Normierung — Verfahren und der je Gebiet und Jahr abgeschnittene Rest —
   steht im Manifest, und der Rückvergleich vergleicht normiert gegen normiert, so wie
   `spiel.md` es vorschreibt;
8. **Brüche**: je Reihe ein Feld `exogen_ab` und ein Feld `verkettet_ab`. Für Deutschland
   trägt der Leitzins `exogen_ab = 1999` (Runde 5) und die Wechselkursreihe
   `verkettet_ab = 1999` mit dem unwiderruflichen Umrechnungskurs. `spiel.md` hat diesen
   Umgang bestätigt.

Größenordnung: 5 Gebiete × 29 Jahre × rund 30 Reihen × 8 Byte ≈ 35 kB, Handel
`40 × 29 × 8` ≈ 9 kB. Der ausgelieferte Datenteil bleibt je Jahrgang deutlich unter
100 kB und mit allen Jahrgängen deutlich unter einem Megabyte.

**T24 — Lücken werden gekennzeichnet, nicht stillschweigend gefüllt — und der Prüfjahrgang
duldet keine.** Je Reihe, Land und Jahr ein Flag `gefuellt`. Die Füllregel steht im
Manifest (Fortschreibung des letzten bekannten Werts, lineare Ganzzahlinterpolation
zwischen Stützstellen), und **gefüllte Jahre zählen im Fehlermaß des Rückvergleichs nicht
mit**, sondern werden gezählt und ausgewiesen.

Zwei Schwellen, weil `spiel.md` für den Prüfjahrgang eine schärfere setzt:

- **Prüfjahrgang 1995:** `spiel.md` verlangt jede der 31 Sollreihen „über volle 29
  Stützstellen ohne Füllung belegt", also `gefuellt = 0`. Eine Reihe, die das nicht
  erfüllt, wird **nicht gefüllt und nicht stillschweigend übernommen**, sondern als Befund
  an den Spielentwerfer gemeldet, samt der beiden Auswege, die ihm zustehen: Reihe streichen
  oder Fenster kürzen. Das ist die wahrscheinlichste Stelle, an der der Jahrgangsbau
  scheitert; chinesische und brasilianische Leitzinsreihen der neunziger Jahre sind der
  Verdachtsfall.
- **Spieljahrgänge:** Eine Sollreihe, die zu mehr als einem Fünftel gefüllt ist, gilt als
  nicht belastbar und wird im Befund als solche markiert.

**T25 — Die Grenze zwischen exogen und endogen ist die Grenze der Aussagekraft des
Orakels, und deshalb ist sie eng gezogen.**

| Größe | im Spiel | Begründung |
|---|---|---|
| Bevölkerung, Erwerbstätige | **exogen**, Pfad aus Daten | Demografie ist nach `spiel.md` ausdrücklich keine Spielgröße |
| Restwelt-Nachfrageniveau | **exogen**, Pfad aus Daten | Randbedingung des Modells; der Rückvergleich prüft die Restwelt folglich nicht |
| `handelsanteil` | **exogen und konstant**, Konstante des Jahrgangs | so von `spiel.md` festgelegt, samt der dort benannten Vereinfachung: Chinas wachsende Handelsoffenheit bildet das Modell über Mengen ab, nicht über die Preisübertragung |
| Produktivität | **endogen**, nur Startwert aus PWT | Würde sie jährlich aus den Daten gelesen, wäre das BIP im Rückvergleich eine Wiedergabe der Sollreihe und der Test prüfte sich selbst |
| Preise, Zinswirkung, Handel, Staatsfinanzen, Zustimmung | **endogen** | das ist die Maschine, die geprüft werden soll |
| Politikinstrumente | im Spiel endogen, **im Rückvergleich auf die historischen Pfade gesetzt** | so verlangt es `spiel.md` — mit der Folge aus T37 |

**T26 — Ein gesperrter oder fehlender Datenanker ändert das Programm nicht, nur das
Manifest.** Drei Fälle, alle nach demselben Muster: Der Jahrgang trägt ein Modellkonstrukt,
das Manifest sagt es, der Befund wiederholt es.

| Fall | Ersatz | Folge für das Orakel |
|---|---|---|
| Aggregierter Zollsatz fällt unter die Drittanbieter-Ausnahme (die schwerste offene Frage aus `spiel.md`) | kein Zollpfad; der Rückvergleich läuft mit konstantem Zoll | zwei statt drei verankerte Instrumente |
| Sektorale Beschäftigung (Reihe 7) gesperrt | Aufteilung nach Wertschöpfungsanteil | Startwert wird Modellkonstrukt, keine Sollreihe betroffen |
| **Spieljahrgang vor 1995 braucht eine Handelsmatrix, BACI beginnt 1995** | IWF-DOTS-Aggregate je Länderpaar, aufgeteilt nach den WDI-Sektoranteilen des Ausfuhrlandes | die Startmatrix ist ein Modellkonstrukt; Spieljahrgänge tragen ohnehin keinen Handelsblock im Rückvergleich (`spiel.md`) |

Der dritte Fall ist neu und folgt aus der Entscheidung für 1995: Die Spieljahrgänge, die
`spiel.md` ausdrücklich erhält, haben unterhalb von 1995 **keine** bilateralen Ströme nach
Ware. Ohne diese Regel wäre ein Spieljahrgang 1980 nicht baubar, und die Zusage aus dem
Abschnitt „Was bewusst fehlt" liefe leer. Lizenz- und Deckungsrisiko sind damit eine
Eigenschaft der Datenschicht, nie eine des Kerns.

### Die Reihenliste, die `spiel.md` vom Architekten verlangt

Damit der Datenbauer je Reihe das Feld „Source" prüfen kann. Quelle nach `daten.md`;
„Verdacht" heisst Drittanbieter-Ausnahme der Weltbank. Die Nummern 7, 8, 10 und 13, die
`spiel.md` zur Prüfung benennt, sind unverändert.

| Nr | Größe | Dimension | Modelleinheit | Quelle | Rolle | Verdacht |
|---:|---|---|---|---|---|---|
| 1 | BIP, konstante Preise | 4 + RW | Tsd USD | WDI / PWT | Start + Soll (4, frei) | nein |
| 2 | Wertschöpfungsanteil je Sektor: `NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS` | (4+RW) × 3 | Zehntausendstel, auf 10.000 normiert | WDI | Start + Soll (12, frei, 8 unabhängig) | nein |
| 3 | Kapitalstock | 4 + RW | Tsd USD | PWT | Start | nein |
| 4 | Produktivität (TFP) | 4 + RW | Index | PWT | nur Start (T25) | nein |
| 5 | Bevölkerung | 4 + RW | Personen | WDI / PWT | exogener Pfad | nein |
| 6 | Erwerbstätige | 4 + RW | Personen | WDI / PWT | exogener Pfad | nein |
| 7 | Beschäftigung je Sektor | (4+RW) × 3 | Personen | WDI (ILO) | Start | **ja** |
| 8 | Verbraucherpreise | 4 | bp Jahresrate | WDI / IWF IFS | Start + Soll (4, frei) | **ja** (IWF-gestützt) |
| 9 | Leitzins | 4 | bp | IWF IFS | Start + Politikpfad + Soll (4, **gesetzt**) | nein |
| 10 | Wechselkurs gegen USD | 3 | Index | IWF IFS / WDI | Start + Soll (3, frei) | prüfen |
| 11 | Staatsschuldenquote | 4 | bp | IWF WEO | Start + Soll (4, **abgeleitet**) | nein |
| 12 | Haushaltssaldo | 4 | bp | IWF WEO | Start + Politikpfad | nein |
| 13 | Zollniveau, aggregiert | 4 | bp | WDI (aus WITS) | Start + Politikpfad | **ja, entscheidend** |
| 14 | Bilaterale Ströme, ab 1995 | 5 × 4 × 2 | Tsd USD | CEPII BACI | Start + Sollblock (frei) | nein |
| 15 | Preisniveau im Ländervergleich | 4 + RW | Index | PWT | Start (Numéraire) | nein |
| 16 | `handelsanteil` | 5 × 2 | Zehntausendstel | BACI + WDI, abgeleitet | Konstante des Jahrgangs | nein |
| 17 | Sektorpreise | (4+RW) × 3 | Index | **keine** | endogen, kein Soll | — |
| 18 | Zustimmung | 4 | Zehntausendstel | **keine** | aus `parameter.toml` | — |
| 19 | Marktkorbwert und Marktrendite | 1 + 1 | Tsd USD / bp | **keine** | endogen nach T33, kein Soll | — |

`NV.IND.MANF.ZS` (verarbeitendes Gewerbe) wird nach `spiel.md` **nicht** verwendet und ist
deshalb hier nicht aufgeführt. Die 31 Sollreihen sind die Zeilen 1, 2, 8, 9, 10 und 11
(4+12+4+4+3+4); der Handelsblock aus Zeile 14 kommt als eigener Block hinzu. Die vier
Größen ohne Datenanker sind die Zeilen 17, 18, 19 und das Instrument
Finanzmarktregulierung — genau die vier, die `spiel.md` unter „Die Grenze des Orakels"
aufzählt.

**T27 — Die Kalibrierdatei liegt ausserhalb des Codes.** Sämtliche Zahlenwerte, die
`spiel.md` ausdrücklich der Kalibrierung überlässt — Mandatsschwelle, drei
Aufsichtsschwellen, Nachahmergeschwindigkeit, Stufenweite einer Position, Lobbykosten,
Anlegerabzugsanteil, Verzögerungen, Elastizitäten — stehen in `parameter.toml`, werden als
Dezimalzeichenketten in skalierte Ganzzahlen gelesen (T4) und in eine Struktur mit
benannten Feldern gefüllt, nie über eine Schleife über Schlüssel (T9). Die Prüfsumme des
Parametersatzes steht im Zustand und in jedem Speicherstand. Damit ist Kalibrieren eine
Datenänderung, die kein Übersetzen braucht — genau die Bauart, die `spiel.md` an
Democracy 4 belegt hat, und die Voraussetzung dafür, dass ein Agent über Nacht tausend
Parametersätze durchsucht (Abschnitt 10).

## 8. Markträumung und die beiden Renditen

**T28 — Feste Iterationszahl statt Konvergenzabbruch.** Der Weltpreis je handelbarem
Sektor wird durch **genau 40 Halbierungsschritte** über einem festen Preisintervall
gesucht, nicht bis zu einer Schranke. Ein Abbruch nach Genauigkeit macht die Laufzeit vom
Zustand abhängig und die Zahl der Schritte zu einem stillen Teil des Ergebnisses; eine
feste Zahl macht beides messbar und begrenzt. 40 Halbierungen über einem Intervall von
sechs Größenordnungen lösen bis unter ein Zehntausendstel auf — mehr Auflösung, als die
Preisskala aus T5 überhaupt darstellt.

Innerhalb jedes Halbierungsschritts stehen, in dieser Reihenfolge, der Zollkeil je Gebiet
auf dem Weltpreis und daraus der wirksame Sektorpreis als Mischung
`preis = weltpreis_mit_zoll · handelsanteil + landespreis · (10.000 − handelsanteil)`,
geteilt durch 10.000 nach T6. Angebot und Nachfrage werden auf diesem Preis gebildet; die
Überschussfunktion ist damit monoton im Weltpreis, was die Halbierung überhaupt erst
zulässig macht. Dienstleistungen haben keine Handelszeile und keinen Weltpreis.

**T29 — Ganzzahlige Potenzen und Wurzeln über Newton auf `i128`.** Wo die
Produktionsfunktion einen Exponenten wie 1/3 braucht, wird `wurzel(x, n)` mit fester
Schrittzahl verwendet; Exponenten sind auf Brüche kleiner ganzer Zahlen beschränkt. Keine
Reihenentwicklung, kein Logarithmus, keine Tabelleninterpolation.

**T33 — Marktrendite und Fondsrendite werden über einen eingefrorenen Mengenkorb
gerechnet.** `spiel.md` hat die Auslegung entschieden: wertgewichtete Rendite aller
handelbaren Körbe zu Modellmarktwerten, gewichtet nach dem Markt und **nicht** nach dem
Bestand des Fonds. Eine Frage bleibt offen, und sie ist meine: Wie rechnet man das, wenn
zwischen zwei Runden nicht nur die Preise, sondern auch die Mengen wachsen? Ohne Regel
misst die Marktrendite das Wirtschaftswachstum mit und wäre systematisch positiv.

Die Regel, in Schritt 6 der Runde:

1. Der **Marktkorb** umfasst die 12 Land×Sektor-Körbe und die 4 Staatsanleihen, jeweils zu
   Modellmarktwerten. Währungen tragen keine Marktkapitalisierung und gehen nicht ein; ihre
   Wirkung steckt in der Umrechnung der übrigen Körbe in den Numéraire.
2. `markt.wert` trägt den Wert dieses Korbs am Ende der Vorrunde.
3. Bewerte den **Mengenkorb der Vorrunde** zu den Preisen dieser Runde: `W_neu`.
   `markt.rendite = teile_gerundet((W_neu − markt.wert) · 10.000, markt.wert)` in
   Basispunkten.
4. Erst danach wird `markt.wert` auf den Wert des **neuen** Korbs zu neuen Preisen gesetzt.

Mengenwachstum erzeugt damit keine Scheinrendite. Analog die **Fondsrendite**: Änderung des
Fondsvermögens (Kasse + bewertete Positionen − Hebel) gegenüber der Vorrunde, **bereinigt
um Anlegerzu- und -abflüsse dieser Runde** — sonst zählte frisches Anlegergeld als Leistung
und der Anlegerabzug aus Gegenkraft 3 verstärkte sich selbst. Die Überrendite ist die
Differenz beider Größen in Basispunkten und steht für drei Runden im Zustand.

## 9. Test- und Prüfstandsaufbau

**T30 — Acht Prüfungen, ein Aufruf.** `nacht` läuft der Reihe nach und bricht mit einem
Rückgabewert ungleich null ab, sobald eine Schwelle aus `spiel.md` gerissen ist. Was nicht
in einem Aufruf läuft, läuft nachts nicht.

| # | Prüfung | Gegenstand | Verantwortlich |
|---:|---|---|---|
| 1 | Einheitstests je Wirkungskette | jeder Pfeil aus `spiel.md` einzeln, auf einem Minimalzustand: Zoll rauf → Einfuhr runter → Preis rauf → Realeinkommen runter → Zustimmung runter | Testentwickler |
| 2 | Invariantentest | Summe aller Handelsbilanzen einschliesslich Restwelt = 0; Staatsschuld(t) = Staatsschuld(t−1) − Saldo; Fondsvermögen = Kasse + bewertete Positionen − Hebel; die drei Sektoranteile je Gebiet summieren auf 10.000; kein Anteil ausserhalb 0…10.000 | Testentwickler |
| 3 | Determinismustest | derselbe Startwert und dieselbe Aktionsfolge ergeben dieselbe Prüfsumme — zweimal im Lauf, über Speichern und Laden hinweg, und auf jeder Zielplattform verglichen | Testentwickler |
| 4 | Regressionsbestand | gespeicherte Partien nach T22 rechnen bitgleich nach; zusätzlich eine Prüfsumme über die Kette, damit auch eine geänderte *Begründung* auffällt; mindestens eine Partie auf einem Spieljahrgang 1980 mit Basiswechsel (T8) | Testentwickler |
| 5 | Bruchlauf | 10.000 Partien mit dem Zufallsbot: kein Absturz, kein Überlauf, keine Invariantenverletzung, kein Kettenüberlauf, kein doppelter Schreibzugriff (T18) | Bruchtester |
| 6 | **Beschränktheit** | **200 Runden ohne Spieler; verlässt eine Größe ihren Wertebereich, gibt es einen achten Rückkopplungskanal, und der ist ein Befund** | Bruchtester |
| 7 | Die drei Maße | Entscheidungsdichte, Strategievielfalt, Optimumsverschiebung nach den Rechenvorschriften in `spiel.md`, gegen die dortigen Schwellen 0,4 je Partiedrittel / drei Klassen bei höchstens 25 % Abstand / 0,5 | Selbstspieler |
| 8 | Rückvergleich | 31 Sollreihen plus Handelsblock, mittlerer absoluter prozentualer Fehler (Schwelle 20 %) und Richtungstreue (Schwelle 0,6), Befundformat nach T37 | Rückvergleicher |

Prüfung 6 ist neu und steht hier, weil `spiel.md` sie ausdrücklich als Auflage an den
Bruchtester formuliert: Die Verteidigung des Entwurfs gegen „chaotisch" ist die
abschliessende Liste der sieben Kanäle, und diese Liste ist nur dann eine Aussage, wenn sie
gemessen wird. Kosten: 200 Weltschritte.

**T31 — Der Regressionsbestand wird nie stillschweigend neu erzeugt.** Ein bewusst
geänderter Modellwert macht Prüfung 4 rot — das ist der Zweck. Die Erneuerung läuft
über einen eigenen Aufruf, der einen **Abweichungsbericht** schreibt: welche Partie,
welche Größe, alter und neuer Wert, welche Kettenglieder sich geändert haben. Dieser
Bericht ist der Gegenstand der Prüfung, nicht der neue Bestand.

**T34 — Die Ergebnisgröße ist ein `i64` in Milli-Runden; die Skala gehört `spiel.md`.**
Die dreiteilige Tabelle (Mandat erfüllt / 28 Runden überlebt / Todesart in Runde d) steht
dort und wird hier **nicht** wiederholt, nicht ausgelegt und nicht gedeckelt. Was der
Architektur zusteht, ist ausschliesslich:

- Typ `i64`, Einheit Milli-Runden, **kleiner ist besser**;
- die Ordnung ist strikt total: Bei gleichem Ergebniswert entscheidet die Profilkennung,
  bei gleichem Profil der Stichprobenindex — nie die Auffindereihenfolge;
- der Median über eine gerade Anzahl ist der kleinere der beiden mittleren Werte
  (so `spiel.md`);
- die drei Bereiche werden beim Bilden geprüft: ein Ergebnis ausserhalb 1.000 … 58.000 ist
  ein harter Fehler, keine Ausreisserbehandlung.

Die Deckelung aus Fassung eins ist ersatzlos gestrichen; siehe Befund 6.

**T35 — Die Ziehregel für Maß 1, ausgeschrieben, weil sie sonst am Zufallserzeuger hängt.**
`spiel.md` gibt vor: Bündelgröße gleichverteilt aus `{0,1,2,3}`, dann so viele Aktionen
ohne Zurücklegen gleichverteilt aus der Liste der zulässigen Aktionen, Doppelte im
Stichprobensatz bleiben. Das ist eindeutig bis auf das Verfahren, und ein anderes Verfahren
ergibt eine andere Stichprobe. Verbindlich ist deshalb:

1. `s = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme, BUENDELZIEHUNG, t, i)`
   nach T11; `s` wird als xoshiro-Zustand fortgeschrieben, und zwar nur innerhalb dieser
   einen Ziehung.
2. `n = naechster(s) mod 4`. Ist `n` größer als die Länge `m` der Zulässigkeitsliste, gilt
   `n = m`.
3. Die Liste steht in der kanonischen Ordnung aus T32. Partielles Fisher-Yates:
   für `k = 0 … n−1` sei `j = k + (naechster(s) mod (m − k))`, tausche `L[k]` und `L[j]`.
   Das Bündel sind die ersten `n` Einträge.
4. Das Bündel wird vor dem Setzen nach Aktionskennung sortiert. Nach `spiel.md` hat keine
   Aktion einen Zeitpunkt innerhalb der Runde; die Sortierung stellt sicher, dass die
   Ziehreihenfolge das Ergebnis nicht berührt.

`naechster(s) mod k` ist verzerrt, sobald `k` kein Teiler von 2^64 ist. Die Verzerrung
liegt bei `m ≤ 2^32` unter 2^-32 und ist damit kleiner als jede Wirkung, die Maß 1 misst;
sie wird hier benannt statt durch eine Verwerfungsschleife behoben, weil eine solche
Schleife die Zahl der Ziehungen zustandsabhängig machte — dieselbe Begründung wie bei T28.

**T36 — Was der Prüfstand zu Maß 2 und 3 fest verdrahtet.** `spiel.md` hat beide
Rechenvorschriften geschlossen; drei Punkte sind Ausführung und stehen deshalb hier:

- **Profilliste.** Die 126 Profile werden in lexikographisch aufsteigender Ordnung von
  `(a1…a5)` erzeugt und in dieser Ordnung durchnummeriert. Die **Profilkennung** ist dieser
  Index, und sie ist der Gleichstandsbrecher aus `spiel.md`. Sie ist Teil der
  Schnittstellenversion (T17).
- **Strategiekern.** Aktionsart mit dem größten Anteil unter `{1 Position, 2 Beteiligung,
  3 Lobby}`, Gleichstand nach kleinerer Kennung; Hebel und Sichtbarkeit gehen nicht ein.
  Der Kern wird einmal je Profil berechnet und mit der Profilliste abgelegt, nicht je Lauf
  neu.
- **Fensterlogik von Maß 3.** Beide Läufe gehen über die volle Partie; ausserhalb des
  Fensters gilt das Referenzprofil `(1,1,1,1,1)`, und der Suchbot fährt innerhalb wie
  ausserhalb. Der Profilwechsel geschieht am Rundenanfang, nicht innerhalb einer Runde.
  Damit kostet ein Lauf dasselbe wie eine gewöhnliche Suchbotpartie, und die Rechnung in
  Abschnitt 10 trägt.

**T37 — Der Rückvergleich weist je Sollreihe aus, ob sie überhaupt etwas prüfen kann.**
Das ist die Folge einer Vorgabe aus `spiel.md`, die dort richtig steht und deren Wirkung
auf den Befund niemand aufgeschrieben hat: Im Rückvergleich werden die Politikinstrumente
**auf die historisch tatsächlichen Werte gesetzt**. Damit ist die Leitzinsreihe des Modells
per Konstruktion die Sollreihe; ihr Fehler ist null und ihre Richtungstreue eins, ohne dass
das Modell irgendetwas geleistet hätte. Vier von 31 Reihen sind Eingabe, vier weitere sind
weitgehend determiniert.

| Klasse | Reihen | Zahl | Bedeutung |
|---|---|---:|---|
| `frei` | BIP (4), Sektoranteile (12), Verbraucherpreise (4), Wechselkurs (3), Handelsblock | 23 (19 unabhängig) | prüft die Maschine |
| `gesetzt` | Leitzins (4) | 4 | Eingabe des Laufs, Fehler null per Konstruktion |
| `abgeleitet` | Staatsschuldenquote (4) | 4 | Zähler folgt dem gesetzten Haushaltssaldo, nur der Nenner ist endogen |

Der Befund führt beide Zahlen: die Abnahme gegen die Schwellen aus `spiel.md` über alle 31
Reihen **und** dieselbe Rechnung über die 23 freien. Weichen sie auseinander, ist die
zweite die aussagekräftige. **Ich ändere das Maß nicht** — welche der beiden Zahlen die
Abnahme entscheidet, gehört dem Spielentwerfer und steht in Abschnitt 12.

**Drei Bots, und die Vorgaben, die sie deterministisch machen:**

- **Zufallsbot(startwert)** — zulässige Aktionen gleichverteilt, Ziehung nach T35. Für
  Prüfungen 5 und 6.
- **Heuristikbot(profil)** — verteilt das Rundenbudget nach dem Aktionsprofil und wählt
  innerhalb einer Art nach einer festen, dokumentierten Rangfolge. Keine Nachspiele, also
  billig. **Er ist auf dem Referenzprofil `(1,1,1,1,1)` die „feste Folgepolitik" von
  Maß 1.**
- **Suchbot(profil, kandidaten=60, tiefe=1)** — bewertet 60 Kandidatenbündel je Runde durch
  ein Nachspiel von einem Zug mit dem Heuristikbot als Fortsetzung. Gleichstand wird nach
  Aktionskennung gebrochen, nie nach Auffindereihenfolge. Kosten je Partie:
  `28 × (1 + 60) = 1.708` Weltschritte.

**Parallelität ohne Preisgabe des Determinismus:** Jedes Nachspiel ist eine reine Funktion
von (Jahrgang, Parametersatz, Startwert, Politik, Runde, Stichprobenindex); der abgeleitete
Zufallsstartwert folgt aus genau diesem Tupel (T11). Ergebnisse werden in ein vorab
bemessenes Feld **an ihrem Index** abgelegt, nie angehängt. Jede Zusammenfassung läuft
über das sortierte Feld. Damit liefert der Prüfstand mit einem Kern und mit
zweiunddreissig dasselbe Ergebnis.

**Berichtspflicht:** Jeder Befund trägt `ticks_gesamt`, `sekunden` und `ticks_je_sekunde`.
Die Schätzung des nächsten Abschnitts wird damit binnen einer Nacht durch eine Messung
ersetzt — und bleibt gemessen.

## 10. Was das Modell an Rechenzeit kostet

Ein Weltschritt umfasst geschätzt 7.500 elementare Ganzzahloperationen; den Löwenanteil
tragen die Markträumung (2 Sektoren × 40 Halbierungen, T28) und das Mitschreiben der
Kette (T18). Teuer sind darin die `i128`-Divisionen aus T6. **Planwert: 10 Mikrosekunden
je Schritt**, Bandbreite 5 bis 30. Die Spalte „ungünstig" rechnet mit 50 Mikrosekunden,
also dem Fünffachen des Planwerts — eine Reserve, keine Erwartung.

Grundlage ist die **28-Runden-Partie** der zweiten Fassung von `spiel.md`.

| Lauf | Weltschritte | bei 10 µs | ungünstig (50 µs) |
|---|---:|---:|---:|
| eine Partie, Heuristikbot | 28 | 0,28 ms | 1,4 ms |
| eine Partie, Suchbot (60 Kandidaten, 1 Zug voraus) | 1.708 | 17 ms | 85 ms |
| **1.000 Partien, Heuristikbot** | 28.000 | **0,28 s** | 1,4 s |
| **1.000 Partien, Suchbot** | 1.708.000 | **17 s** | 1,4 min |
| Entscheidungsdichte, K=30, ein Startwert | 11.368 | 0,11 s | 0,57 s |
| Entscheidungsdichte, 50 Startwerte | 568.400 | 5,7 s | 28 s |
| Strategievielfalt, 126 Profile × 20 Startwerte | 4.304.160 | 43 s | 3,6 min |
| Optimumsverschiebung, zwei Fenster | 8.608.320 | 1,4 min | 7,2 min |
| Bruchlauf, 10.000 Zufallspartien | 280.000 | 2,8 s | 14 s |
| Beschränktheit, 200 Runden | 200 | 2 ms | 10 ms |
| Rückvergleich, ein Durchlauf | 28 | 0,28 ms | 1,4 ms |
| Regressionsbestand, 1.000 Partien | 28.000 | 0,28 s | 1,4 s |
| **Nachtlauf gesamt** | **13.789.108** | **2,3 min** | **11,5 min** |

Die Zeilen im Einzelnen: `11.340 = 30 × Σ(28−t)` für `t = 1…27` nach `spiel.md`, zuzüglich
28 Weltschritte für die Trägerpartie, aus der die Stichproben abzweigen, ergibt 11.368 je
Startwert. `126 = C(9,4)`. `4.304.160 = 126 × 20 × 1.708`, `8.608.320` das Doppelte davon.
Die 50 Startwerte für Maß 1 setzt `spiel.md` nicht; sie sind eine Vorgabe des Prüfstands,
damit die Dichte nicht an einem einzelnen Startjahrgang hängt, und sie kosten 5,7 Sekunden.

Alles auf **einem** Kern. Mit acht Kernen (`rayon`) fällt der Nachtlauf auf rund 17
Sekunden beim Planwert und auf rund 1,4 Minuten im ungünstigen Fall.

**Die Antwort auf die Frage, die dieser Abschnitt beantworten soll: Ja, der Prüfstand kann
täglich laufen — und stündlich.** Der Engpass ist nicht die Rechenzeit, sondern das
Tokenbudget der Agenten, die die Befunde lesen.

**Die Kalibrierschleife, ehrlich gerechnet.** Fassung eins nannte hierfür „rund zwei
Stunden auf acht Kernen"; die Zahl war zu niedrig, und die kürzere Partie rettet sie nicht.
Tausend Parametersätze über den vollen Maßsatz (13,48 Mio Schritte) kosten 13,5 Milliarden
Weltschritte, also 37 Stunden auf einem Kern und **4,7 Stunden auf acht** — keine
Nachtaufgabe. Nachtfähig ist die verkürzte Fassung: Maß 1 mit 10 statt 50 Startwerten und
Maß 2 mit 5 statt 20, zusammen 1,19 Mio Schritte je Parametersatz, also **25 Minuten auf
acht Kernen** für tausend Sätze. Die Vorgabe an den Selbstspieler lautet deshalb: grob mit
der verkürzten Fassung suchen, die zehn besten Sätze mit der vollen nachrechnen.

**Die Gegenrechnung, die die Stackwahl trägt:** Derselbe Weltschritt kostet in Python
zwischen 0,75 und 3 Millisekunden, also das 75- bis 300-fache. Der Nachtlauf läge bei
**2,9 bis 11,5 Stunden** auf einem Kern. Er wäre damit nicht täglich, sondern gelegentlich —
und die Kalibrierschleife wäre auch in der verkürzten Fassung unmöglich. Das ist die Zahl,
an der die Wahl aus T1 hängt, und sie ist der einzige Grund, den Autorenaufwand von Rust in
Kauf zu nehmen. Sie ist durch die kürzere Partie kleiner geworden, aber der Abstand ist
derselbe: Der Faktor entscheidet, nicht die Partielänge.

**Beim Käufer** kostet eine Runde einen Weltschritt: 10 Mikrosekunden. Der Speicherbedarf
sind 2,5 kB Zustand, unter 1 MB Jahrgänge und wenige hundert kB Kettenverlauf. Das
Produkt läuft auf allem und braucht keinen Server — die Kostenrechnung der Idee (keine
Kosten je Kunde) hält.

## 11. Auslieferung, und wo Geld anfängt

**Windows x86-64 zuerst**, Linux gleich mit (dasselbe Programm, andere Zielkennung),
**macOS nicht in Fassung eins**: Beglaubigung durch Apple kostet 99 USD im Jahr und wäre
eine Ausgabe nach Hausregel 1. Ebenso: Eine gehostete Bauumgebung ist **nicht** der
Vorgabeweg — gebaut und geprüft wird im Nachtlauf der Fabrik, auf dem Rechner des
Betreibers. Wer eine gehostete Kette will, schreibt eine Gate-Vorlage.

Die Plattformgleichheit wird nicht behauptet, sondern geprüft: Prüfung 3 vergleicht die
Prüfsummen aus dem Windows- und dem Linux-Lauf derselben Partien.

Aus `daten.md` folgt eine Auslieferungsauflage: `LIZENZEN.md` neben den Jahrgangsdateien,
eine Seite „Datenquellen" im Hauptmenü, ein Satz zur Bearbeitung („Die Ausgangsdaten wurden
aggregiert und in ganzzahlige Einheiten umgerechnet; die Quellen verantworten diese
Bearbeitung nicht") und der Hinweis, dass die IWF-Daten beim IWF kostenfrei erhältlich sind.
Alle drei Stellen werden aus dem Manifest des Jahrgangs erzeugt (T23), nicht von Hand
gepflegt — sonst weichen sie beim ersten Datenaktualisierungslauf von der Wahrheit ab.

## 12. Was ich nicht entschieden habe

- **Ob die Abnahme von Maß 4 über alle 31 Sollreihen oder über die 23 freien läuft** (T37).
  Vier Reihen sind Eingabe des Laufs und tragen per Konstruktion null Fehler bei; sie machen
  das Gesamtmaß milder, als das Modell verdient. Ich berichte beide Zahlen und ändere die
  Schwelle nicht. Welche entscheidet, ist eine Aussage über das Maß und gehört dem
  Spielentwerfer.
- **Wie der Handelsblock über seine 40 Ströme zusammengefasst wird.** `spiel.md` nennt ihn
  „einen eigenen Block" mit denselben zwei Fehlermaßen, sagt aber nicht, ob die Schwelle je
  Strom, für den Median oder für das Mittel gilt. Mein Vorschlag: je Strom ein MAPE und eine
  Richtungstreue, Abnahme am Median über die 40 Ströme, dazu berichtet das schlechteste
  Fünftel. Grund: Einzelne kleine Ströme (Brasilien–China, Landwirtschaft) schwanken
  prozentual stark, ohne dass das Modell falsch wäre; ein Mittel ginge daran kaputt, eine
  Je-Strom-Schwelle noch schneller. Bis zur Entscheidung fährt der Rückvergleicher diesen
  Vorschlag und weist ihn als solchen aus.
- **Die Zahlenwerte sämtlicher Schwellen und Elastizitäten.** Sie stehen nach T27 in der
  Parameterdatei und werden vom Selbstspieler gesucht, nicht von mir gesetzt.
- **Die konkrete Rangfolge im Heuristikbot.** Sie ist eine Modellierungsfrage des
  Selbstspielers; die Architektur verlangt nur, dass sie fest, dokumentiert und
  gleichstandsfrei ist.
- **Ob der Suchbot mit Tiefe 1 stark genug ist, damit Maß 2 das Spiel misst und nicht den
  Bot.** Unverändert offen aus Fassung eins — aber die Rechnung fällt jetzt anders aus, als
  ich sie im Logbuch stehen hatte. Tiefe 2 kostet je Partie `28 × (1 + 60 × 61) = 102.508`
  statt 1.708 Weltschritte, also das Sechzigfache; Maß 2 und 3 zusammen 775 Millionen, das
  sind 2,2 Stunden auf einem Kern und **rund 16 Minuten auf acht** beim Planwert, im
  ungünstigen Fall 1,3 Stunden auf acht. Das sprengt den Nachtlauf nicht, es verlegt ihn.
  Tiefe 2 ist damit kein Ausschluss, sondern eine Entscheidung, die der Selbstspieler treffen
  darf, wenn Maß 2 mit Tiefe 1 keinen Gewinner in allen drei Klassen findet. Die Vorgabe
  bleibt die Berichtspflicht aus T30: erst der gemessene `ticks_je_sekunde`, dann die Wahl.

## 13. Hinweis für den Projektmanager

Der Kastenschnitt aus T13 ist zugleich der Kollisionsschnitt für Arbeitspakete: Zwei
gleichzeitig offene Pakete dürfen sich nicht im selben Kasten treffen. Die natürliche
Reihenfolge ist `kern` (Zustand, Festkomma, Zufall, Prüfsumme) → `daten` und
`schnittstelle` parallel → `konsole` → Tests und `pruefstand` → `oberflaeche`. Der Jahrgang
(`werkzeuge/aufbereitung`) kann von Beginn an parallel laufen, weil er nur gegen T5, T23
bis T26 gebaut wird und nichts vom Kern braucht.

**Zwei Pakete sind vorzuziehen, weil sie Entwurfsrisiko tragen und nicht Bauaufwand:**
der Jahrgangsbau 1995 (T24 sagt, dass er scheitern kann — 29 Stützstellen ohne Füllung für
alle 31 Reihen sind eine Behauptung, keine Tatsache) und die Prüfung der vier
WDI-Verdachtsreihen 7, 8, 10 und 13 auf die Drittanbieter-Ausnahme. Beide klären sich
gegen Daten, nicht gegen Code, und beide entwerten im schlechten Fall Arbeit, die sonst
schon geleistet wäre.

## 14. Befundabarbeitung — Prüfung vom 2026-08-31

**Befund 1, Sektorgliederung ohne Quellreihe — behoben, soweit mein Gewerk betroffen ist.**
Die Entscheidung gehörte dem Spielentwerfer und ist gefallen. Meinerseits geändert:
Reihenliste Zeile 2 nennt die drei WDI-Codes und schliesst `NV.IND.MANF.ZS` aus; T23
Punkt 7 macht die Normierung auf 10.000 zur Erzeugungsregel des Jahrgangs mit Ausweis im
Manifest; T30 Prüfung 2 prüft die Invariante dagegen; T23 Punkt 5 nimmt `handelsanteil` als
Konstante des Jahrgangs auf, T25 klassifiziert ihn als exogen, T28 sagt, wo er in der
Markträumung wirkt. Die Aufteilung 31 Sollreihen / 27 unabhängig steht in T37.

**Befund 2, Startjahrgang an zwei Stellen verschieden — behoben.** „Das Startjahr" ist aus
Abschnitt 12 gestrichen; 1995 und 28 Runden stehen im Frontmatter, in T22 und in
Abschnitt 10. T8 bleibt mit gewechselter Begründung: Die Neubasierung greift im
Prüfjahrgang nie und trägt jetzt die Spieljahrgänge vor 1995 — samt Testauflage, damit sie
kein ungeprüfter Zweig wird. Aus derselben Entscheidung neu: T26 regelt, woher ein
Spieljahrgang 1980 seine Handelsmatrix nimmt, denn BACI beginnt 1995 und liesse ihn sonst
unbaubar.

**Befund 3, die Zahl 150 — behoben.** Meine Zählung war die belastbarere, aber nicht
belastbar genug (Befund 8); T15 stellt sie neu auf und kommt auf 310. Die Verteidigung
gegen „chaotisch" steht jetzt in `spiel.md` auf den sieben Rückkopplungskanälen und wird
hier an zwei Stellen getragen: T18 macht eine Rückkopplung innerhalb der Runde zum harten
Fehler statt zum stillen achten Kanal, T30 Prüfung 6 misst die Beschränktheit über
200 Runden.

**Befund 4, Marktrendite ohne Datenreihe — behoben.** Der Spielentwerfer hat meine Auslegung
übernommen und die Gewichtung korrigiert (Modellmarktwerte statt Fondsbestand); seine
Fassung ist die richtige, weil sie die von mir selbst benannte Folge vermeidet. T33
schliesst die Frage, die sie offen liess: wertgewichtete Rendite über einen **eingefrorenen
Mengenkorb**, Fondsrendite bereinigt um Anlegerflüsse. Der Punkt ist aus Abschnitt 12
gestrichen; Reihenliste Zeile 19 und T15 tragen die beiden Zustandsfelder.

**Befund 5, Maß 2 und Maß 3 als Absichtserklärungen — behoben.** Die Rechenvorschriften
stehen jetzt in `spiel.md` und sind genau die Lesart, die meine Rechnung stillschweigend
voraussetzte; die Rechnung ist in Abschnitt 10 auf 28 Runden neu aufgestellt (13,79 statt
20,06 Mio Weltschritte). Was nur der Prüfstand festlegen kann, ist ausgeschrieben statt
vorausgesetzt: T32 kanonische Ordnung der Zulässigkeitsliste, T35 Ziehalgorithmus samt
benannter Restverzerrung, T36 Profilordnung, Strategiekern und Fensterwechsel.

**Befund 6, Deckelung der Ergebnisgröße — behoben.** Ersatzlos gestrichen. `spiel.md` trägt
die dreiteilige Skala, T34 beschränkt sich auf Typ, Einheit, strikte Gesamtordnung,
Medianregel und Bereichsprüfung. Der Befund traf zweimal: Die Begründung war falsch (ein
Median ist gegen einen Extremwert unempfindlich), und die Zuständigkeit war es auch. Die
Trennlinie steht jetzt ausdrücklich in T34.

**Befund 7, Handelsmatrix vier gegen fünf Gegenüber — behoben, meine Fassung bestätigt.**
Der Widerspruch lag in `spiel.md` und ist dort aufgelöst (`5 × 4 × 2 = 40`, Restwelt mit
eigenen Zeilen). T15 bleibt unverändert, die Invariante in T30 Prüfung 2 hält.

**Befund 8, Feldzählung `4 × 41 + 20 = 184` — behoben.** Der Klammerzusatz nannte 17
wegfallende Felder, gezählt waren 21. T15 ist neu aufgestellt, jede Zeile nennt ihre
Herkunft in `spiel.md`, die Restwelt trägt nach dessen zweiter Fassung 22 statt 20 Felder,
und die Summe ist nachrechenbar: `4 × 44 + 22 + 56 + 52 + 4 = 310`. Gegenüber Fassung eins
sind fünfzehn Felder hinzugekommen — drei Restdauerzähler je spielbarem Land und die beiden
Marktkorbfelder aus T33 —, jedes einzeln begründet.
