---
typ: technik
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
fassung: 3 (nach ventures/0016-.../befunde/pruefung-entwurf-fassung2-2026-08-31.md)
stack: Rust (stabile Kette, Edition 2021); Kern ohne jede Fremdabhängigkeit und ohne Gleitkommatyp; Oberfläche egui/eframe (MIT OR Apache-2.0)
determinismus: i64-Festkomma mit deklarierter Skala je Größenklasse, feste Iterationsreihenfolge über Indexlisten, ein Wurzelstartwert mit abgeleiteten Strömen, Weltschritt ohne jede Ziehung
zustand: fester, allokationsfreier Wert, 310 i64 (2.480 Byte), Prüfsumme über kanonische Byteform
speicherstand: Jahrgang, Modus, Startwert, Aktionsfolge und Prüfsumme -- nicht der Zustand
kalibrierung: alle Zahlenwerte in einer Parameterdatei ausserhalb des Codes, mitgehasht
partie: R Runden, R ist eine Größe des Jahrgangs; im Prüfjahrgang 1997-2021 ist R = 24, eine Suchbotpartie kostet R × 61 = 1.464 Weltschritte
tick_planwert: 10 Mikrosekunden je Weltschritt (Bandbreite 5 bis 30) -- geschätzt, nicht gemessen; es gibt noch keinen Kern
nachtlauf: 11.783.264 Weltschritte, 2,0 Minuten auf einem Kern beim Planwert, 9,8 Minuten im ungünstigen Fall
---

# Der Kern ist eine reine Ganzzahlfunktion ohne Ziehung -- damit ist Determinismus keine Disziplin, sondern eine Eigenschaft des Typsystems.

Dritte Fassung, gegen `ventures/0016-.../aufgaben/0001-entwurf-abnahme.md` und die zwölf
Befunde der zweiten Prüfung. Die Abarbeitung steht am Ende der Datei. Die Abarbeitung der
**ersten** Prüfung stand in Fassung 2 und ist dort vom Prüfer als erledigt abgenommen
worden; sie steht im Git-Verlauf und wird hier nicht wiederholt.

Die Vorgaben sind mit **T1** bis **T43** durchnummeriert. Der Builder weicht von keiner ab,
ohne dass ein ADR sie aufhebt; der Prüfer zitiert die Nummer, statt sie zu umschreiben.
**Die Nummern behalten über alle Fassungen ihre Bedeutung**, damit beide Prüfungen
zitierbar bleiben; neue Vorgaben tragen die nächsten freien Nummern und stehen dort, wo sie
inhaltlich hingehören. Die Nummerierung ist deshalb innerhalb der Abschnitte nicht
fortlaufend.

**Die teuerste Lehre dieser Fassung steht in T40 und nicht in einer Zahl.** Befund 1 hat
nicht eine falsche Jahreszahl gekostet, sondern zwölf abgeleitete Größen, in die sie
eingesetzt war. Die Antwort darauf ist keine bessere Jahreszahl, sondern eine Architektur,
in der die Partielänge nirgends als Literal steht.

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
kostet knapp 11,8 Millionen Weltschritte je Nacht — in einer übersetzten Sprache sind das
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
| Anteile (Sektoranteil, Marktanteil, Einfluss, Zustimmung, `durchgriff`) | Zehntausendstel | 10.000 = 100 % | 0 bis 10.000 |
| Preise und Preisniveaus | Index, Startjahr = 10.000 | 12.500 = +25 % | siehe T8 |
| Wechselkurs | Index gegen USD, Startjahr = 10.000 | 8.000 = Aufwertung um 25 % | siehe T8 |
| Ergebnis einer Partie | Milli-Runden | 12.000 = Runde 12,0 | siehe T34 |

Einfluss und Zustimmung erscheinen dem Spieler als 0 bis 100 (so nennt sie `spiel.md`);
gespeichert sind sie in Zehntausendsteln, damit die Gegenkräfte unterhalb eines
sichtbaren Punktes noch rechnen können. Die Umrechnung findet in der Sicht statt.

Der Koeffizient heisst seit `spiel.md` Fassung 3 **`durchgriff`** und nicht mehr
`handelsanteil`. Er bleibt in der Klasse Anteile — anders als sein Vorgänger hält er ihren
Bereich jetzt per Konstruktion ein; die Bildungsregel steht in T23 Punkt 5.

**Zwischen Fondsskala und volkswirtschaftlicher Skala liegt der Faktor 100.000, und er wird
an genau einer Stelle überschritten:** `cent_in_tsd` und `tsd_in_cent`, beide mit der
Rundung aus T6; jede andere Vermischung ist ein Fehler. Der Fonds bewegt Preise auf
Märkten, deren Größen in einer anderen Einheit stehen als sein Geld — das ist die
wahrscheinlichste stille Fehlerquelle des Modells.

**T6 — Genau eine Rundungsregel, `/` auf Zustandsgrößen ist verboten, und der Nenner null
ist ein harter Fehler.** Alle Divisionen laufen über `teile_gerundet(zaehler, nenner)` mit
Rundung **auf halbe Beträge vom Null weg**. Grund: Rusts `/` schneidet gegen null ab und ist
damit über dem Vorzeichen unsymmetrisch — bei einem Fonds, der nach `spiel.md` ausdrücklich
long **und** short sein können soll, würde das eine Richtung still bevorzugen und Maß 2
verfälschen. Ebenso verpflichtend: `mal_geteilt(a, b, c)` rechnet `a·b/c` über ein
`i128`-Zwischenergebnis; die naive Form läuft bei Beträgen in Cent mal Anteilen in
Zehntausendsteln über.

**`nenner == 0` bricht ab und wird nie still zu null.** Befund 2 der zweiten Prüfung
entstand genau an dieser Stelle: Ein Rückvergleich mit einem Fonds ohne Vermögen brauchte
dieses Vermögen als Nenner. Ein stiller Ersatzwert hätte den Fehler in eine falsche Zahl
verwandelt statt in einen Abbruch; die Behebung gehört nach T38 in den Modus und nicht in
die Divisionsregel, aber die Regel bleibt die Wand, gegen die ein solcher Fehler läuft.

**T7 — Überlauf ist ein Absturz, kein Umlauf.** `overflow-checks = true` auch im
Freigabeprofil. Rust schaltet die Prüfung im Freigabeprofil ab und läuft dann still im
Zweierkomplement um (doc.rust-lang.org/book/ch03-02-data-types.html, abgerufen
2026-08-31) — ein stiller Umlauf würde einen Regressionsbestand vergiften, statt ihn rot
zu machen. Die Kosten sind wenige Prozent und in Abschnitt 10 eingerechnet.

**T40 — Die Partielänge R ist eine Größe des Jahrgangs, keine Konstante des Codes, und
keine aus ihr abgeleitete Zahl steht als Literal irgendwo.** Das ist die architektonische
Antwort auf Befund 1, und sie ist die einzige, die dessen eigentlichen Preis vermeidet: Die
falsche Zahl war billig, ihre Verbreitung in zwölf abgeleitete Größen war teuer.

`R = manifest.stuetzstellen − 1` wird beim Laden des Jahrgangs gebildet. Aus R und sonst
nichts entstehen zur Laufzeit:

| Abgeleitete Größe | Formel | bei R = 24 |
|---|---|---|
| Ergebnisband „Mandat erfüllt" | `1.000 … R × 1.000` | 1.000 … 24.000 |
| Ergebnisband „überlebt" | `(R+1) × 1.000 … (R+1) × 1.000 + 2.000` | 25.000 … 27.000 |
| Ergebnisband „Todesart" | `30.000 + 1.000 … 30.000 + R × 1.000` | 31.000 … 54.000 |
| Partiedrittel (Maß 1, Fenster von Maß 3) | `1…⌊R/3⌋`, `⌊R/3⌋+1…⌊2R/3⌋`, `⌊2R/3⌋+1…R` | 1-8, 9-16, 17-24 |
| Gewinnschwelle Maß 2 | `E(p) ≤ R × 1.000` | 24.000 |
| Suchbotpartie | `R × (1 + 60)` | 1.464 |
| Kosten Maß 1 je Startwert | `30 · R(R+1)/2 + R` | 9.024 |
| `exogen_ab_runde` je Reihe | `bruchjahr − startjahr + 1` | DE-Leitzins: 1999 − 1997 + 1 = 3 |

**Eine Schranke gehört dazu, weil die Ergebnisskala von `spiel.md` an einer Stelle ein
echtes Literal trägt** — die 30.000, ab der die Todesarten zählen. Das Band „überlebt"
endet bei `(R+1) × 1.000 + 2.000`; es stösst an die 30.000, sobald `R ≥ 27`. Der
Jahrgangsbau bricht deshalb mit `R > 26` ab, statt eine Skala zu erzeugen, in der ein Wert
zwei Bedeutungen trägt. Für das Fenster 1997–2021 ist das folgenlos, und `spiel.md` lässt
das Fenster nur enger werden, nie weiter. Es ist eine Wand, keine Einschränkung — aber es
ist eine, die vor dem Bau sichtbar sein muss und nicht danach.

**T8 — Preisniveau und Wechselkurs werden geführt und neu basiert.** Der Prüfjahrgang
beginnt nach `spiel.md` Fassung 3 im Jahr **1997**, also lange nach dem Plano Real; dort
tritt die Neubasierung nie ein. Sie bleibt trotzdem, weil `spiel.md` die Jahrgänge vor 1997
ausdrücklich als **Spieljahrgänge** erhält und Brasilien zwischen 1980 und 1994 rund zwölf
Nullen gestrichen hat. Regel: Übersteigt der Preisindex eines Landes das 100.000-fache
seines Startwerts, werden Index, Wechselkurs und alle nominalen Größen dieses Landes durch
1.000 geteilt und der Zähler `basiswechsel` erhöht.

Weil sie im Prüfjahrgang nie greift, wäre sie ungeprüfter Code. **Auflage an den
Testentwickler:** Mindestens eine Partie im Regressionsbestand (T31) läuft auf einem
Spieljahrgang 1980 und durchläuft einen Basiswechsel. Ein Zweig, den der Nachtlauf nie
betritt, ist ein Zweig, den niemand kennt.

**Der Rückvergleich läuft für Preise und Wechselkurse auf Jahresänderungsraten in
Basispunkten, nicht auf Niveaus.** Ein prozentualer Fehler auf einem Niveau, das über zwei
Jahrzehnte um eine Größenordnung wandert, misst den Anfang und nicht die Maschine.
`spiel.md` hat diese Vorgabe in Fassung 3 übernommen und beziffert (300 bp); die
Rechenvorschrift steht in T42, einschliesslich der Korrektur, die eine Neubasierung
innerhalb der Reihe erzwingt.

**T9 — Feste Reihenfolge, keine streuenden Behälter.** Länder, Sektoren, Instrumente und
Handelspaare sind dichte Indexlisten (`Vec` fester Länge, angesprochen über `LandId(u8)`,
`SektorId(u8)`, `InstrumentId(u8)`). `HashMap` und `HashSet` sind im Kern verboten;
gebraucht wird eine Zuordnung, ist es ein `BTreeMap`. Die sechs Schritte der Runde laufen
in der Reihenfolge aus `spiel.md`, Abschnitt „Die Schleife", und diese Reihenfolge steht
als benannte Konstantenliste im Code, damit ein Umstellen sichtbar wird.

**T10 — Der Weltschritt zieht nicht.** Nach `spiel.md` ist jede Regel eine Schwelle, ein
Zähler oder eine Rechnung; auch der Innerjahresausschlag folgt „deterministisch aus der
Jahresbewegung und der historischen Schwankungsbreite". Also gilt:
`schritt(zustand, aktionen, modus)` ist eine **reine Funktion ohne Zufallsargument**. Das
ist die billigste Art, Anforderung 1 zu erfüllen, und sie macht den Rückvergleich zu einer
exakt wiederholbaren Rechnung.

**T11 — Zufall gibt es nur an zwei Stellen, und er hängt an einem Wurzelstartwert.**
Erstens die Streuung der Startjahrgänge (ein Spiel soll nicht immer identisch beginnen),
zweitens die Bots und Stichproben des Prüfstands. Der Erzeuger ist selbst geschrieben —
SplitMix64 zur Ableitung, xoshiro256\*\* zur Erzeugung, zwanzig Zeilen, im Repo
festgeschrieben, **kein Kasten** (T2): Ein Versionssprung eines fremden Zufallskastens
würde sonst jede gespeicherte Partie entwerten.

Jeder Strom wird **abgeleitet**, nicht fortgeschrieben:

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

**Im Modus `weltlauf` wird kein einziger Strom gezogen** (T38): Es gibt keine Bots, keine
Stichproben und keine Jahrgangsstreuung. Der Rückvergleich ist damit nicht nur
reproduzierbar, sondern startwertfrei.

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
damit die Summe nachzählbar ist:**

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
`spiel.md` nennt dieselbe Zahl und verweist für die Aufstellung hierher.

**`landespreis` bekommt keine Zeile, und das ist die Behebung von Befund 6, nicht ihre
Umgehung.** Die Größe ist nach `spiel.md` der Sektorpreis der Vorrunde. Sie hat deshalb
keine eigene Adresse, sondern einen eigenen **Lesezugriff** — siehe T39. Ein Feld dafür
wäre eine zweite Kopie derselben Zahl und damit eine Gelegenheit, sie auseinanderlaufen zu
lassen.

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

**T18 — Die Kette wird erzeugt, nicht rekonstruiert — und jede Größe der Sollmaske wird je
Runde genau einmal geschrieben.** Die Felder von `Zustand` sind ausserhalb des Kerns nicht
schreibbar; innerhalb schreibt niemand direkt, sondern über
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
Eine Adresse, die sich nicht ändert, wird trotzdem geschrieben, mit der Ursache
`Vortrag` — „unverändert" ist eine Aussage und keine Lücke.

Das ist die maschinelle Fassung der Vorgabe aus `spiel.md` und zugleich die billigste Art,
die dortige Behauptung über **sieben** rundenübergreifende Rückkopplungskanäle prüfbar zu
machen: Eine Rückkopplung innerhalb der Runde erzeugt zwangsläufig einen zweiten
Schreibzugriff und stirbt hier, statt als achter Kanal unbemerkt zu entstehen. Kosten:
40 Byte je Runde, ein Bittest je Schreibzugriff.

**T39 — Es gibt zwei Lesezugriffe, und der falsche stirbt sofort.** Der `Schreiber` hält
den Zustand der Vorrunde (`alt`, unveränderlich) und den entstehenden Zustand (`neu`):

- `lies_alt(adresse)` — der Wert am Ende der Vorrunde. Immer verfügbar.
- `lies_neu(adresse)` — der Wert dieser Runde. **Ist die Adresse in dieser Runde noch nicht
  geschrieben, ist das ein harter Fehler**, kein stiller Rückgriff auf `alt`.

Der stille Rückgriff wäre die gefährlichere Bequemlichkeit: Er macht das Ergebnis von der
Reihenfolge der sechs Schritte abhängig, ohne dass irgendwo steht, dass es das tut. Mit dem
Abbruch ist die Zyklenfreiheit der Rundenreihenfolge kein Versprechen mehr, sondern eine
Eigenschaft, die jeder Lauf nachweist — auch der beim Käufer.

Damit hat `landespreis` seinen Ort: In der Markträumung (T28) ist er
`lies_alt(gebiet.sektor.preis)`. In Runde 1 ist das der Startwert des Jahrgangs, nach
`spiel.md` der Index 10.000.

**T38 — Der Modus ist eine Eigenschaft des Laufs, nicht des Zustands — und er bringt eine
Sollmaske mit.** Das ist die Behebung von Befund 2 auf der Architekturseite.

`spiel.md` kennt zwei Modi: `spielmodus` und `weltlauf`. Der Modus steht **nicht** im
Zustand. Zwei Gründe, beide zwingend: Er wäre ein 311. Feld und widerspräche einer Zahl, die
`spiel.md` nennt; und er beschreibt nicht die Welt, sondern die Art, sie zu rechnen. Er ist
Argument von `schritt` (T10), steht im Kopf des Speicherstands (T22) und in jedem Befund.
Wer eine Partie im falschen Modus nachrechnet, bekommt keine falsche Zahl, sondern einen
Prüfsummenbruch beim Laden.

Zu jedem Modus gehört eine **Sollmaske**: die Menge der Adressen, die in diesem Modus je
Runde geschrieben werden. Am Rundenende prüft der `Schreiber` zweiseitig — jede Adresse der
Maske genau einmal geschrieben, keine Adresse ausserhalb der Maske berührt. Beides ist ein
harter Fehler, kein Bericht.

| Block | Adressen | in `weltlauf` |
|---|---:|---|
| je spielbarem Land: Sektoren (12), Aggregat (9), Zustimmung (1), Instrumentenstand (4), `basiswechsel` (1) | 27 × 4 = 108 | **ja** |
| je spielbarem Land: Aufsichtszähler (1), Einfluss (1), Instrumente ohne Stand (12), Restdauern (3) | 17 × 4 = 68 | nein |
| Restwelt | 22 | **ja** |
| Handel | 40 | **ja** |
| Weltpreise | 2 | **ja** |
| Nachahmerzähler | 12 | nein |
| Marktkorb | 2 | nein |
| Fonds (Aggregat 5, Überrendite 3, Steckplätze 20, Beteiligungen 24) | 52 | nein |
| Partie: Runde, Jahrgangskennung, Parametersatz-Prüfsumme | 3 | **ja** |
| Partie: Mandatsstand | 1 | nein |

Nachrechnung: `108 + 22 + 40 + 2 + 3 = 175` in der Maske, `68 + 12 + 2 + 52 + 1 = 135`
ausserhalb, `175 + 135 = 310`. Die Maske `spielmodus` umfasst alle 310.

Was ausserhalb der Maske liegt, behält seinen Startwert — so verlangt es `spiel.md`. Der
Fonds startet im Weltlauf also nicht mit Nullvermögen, sondern er wird **überhaupt nicht
gerechnet**: kein Vermögen, keine Rendite, keine Überrendite, kein Anlegerabzug, keine
Todesart. Der Nenner aus Befund 2 entsteht nicht, statt abgefangen zu werden. Der Prüfstand
weist die Maskengröße in jedem Befund aus.

Der Modus wirkt an genau vier Stellen und nirgends sonst — Schritt 2 und 6 der Runde
entfallen, aus Schritt 5 laufen nur Zustimmung und Regierungswechsel, und die
Politikinstrumente kommen in Schritt 3 aus dem Jahrgang statt aus dem Lobbydruck. Der
Regierungswechsel wird gerechnet und ausgewiesen, schreibt aber nichts; dass das Orakel an
dieser Stelle blind ist, gehört nach `spiel.md` in jeden Befund und steht deshalb in der
Befundvorlage, nicht in einer Fussnote.

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
Hausregel 2. Befehle: `neu {jahrgang, modus, startwert}`, `zustand {ebene, adresse}`,
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

**Die Liste wird einmal je Runde gegen den Rundenanfangszustand gebildet**, nicht nach jeder
gesetzten Aktion neu. Nach `spiel.md` hat keine Aktion einen Zeitpunkt innerhalb der Runde;
eine Liste, die sich zwischen zwei Steckplätzen ändert, würde genau diesen Zeitpunkt
einführen. Was ein Bündel als Ganzes betrifft — derselbe Steckplatz zweimal, Kasse
überzogen, mehr als drei Aktionen —, prüft `buendel_zulaessig(zustand, buendel)` gegen
denselben Rundenanfangszustand. Zwei Prüfungen, beide zustandsfrei innerhalb der Runde.

**T22 — Ein Speicherstand ist Jahrgang, Modus, Startwert, Aktionsfolge und Prüfsumme, nicht
der Zustand.** Datei: `{schema_version, jahrgang_id, modus, daten_pruefsumme,
parameter_pruefsumme, startwert, aktionen: [[runde, aktion…]], end_pruefsumme}`. Beim Laden
wird die Partie nachgerechnet und die Prüfsumme verglichen; weicht sie ab, meldet das
Programm einen Determinismusbruch, statt weiterzuspielen. Drei Gewinne auf einmal: Der
Käufer bemerkt einen Determinismusfehler zuerst, der Regressionsbestand **ist** der
Speicherordner, und eine Datei bleibt unter zwei Kilobyte. Kosten: R Weltschritte beim
Laden, bei R = 24 also 0,24 Millisekunden.

## 7. Datenschicht

**T23 — Der Jahrgang ist ein Erzeugnis, kein Programmteil.** `werkzeuge/aufbereitung`
liest die eingefrorenen Rohdateien und schreibt `jahrgang-<jahr>.bin`,
`sollreihen-<jahr>.bin` und ein `manifest.toml` mit SHA-256 je Ein- und Ausgabe, Quelle,
Lizenz und Abrufdatum. Der Bau des Spiels lädt **nichts** aus dem Netz. Der Jahrgang
enthält:

1. **Startwerte** für jede Zustandsgröße mit Datenanker; die Größen ohne Anker stehen in
   der Tabelle „Jede Größe ohne Datenanker" in `spiel.md` und kommen von dort oder aus
   `parameter.toml`;
2. **Sollreihen** für die 31 Reihen aus `spiel.md` plus den Handelsblock über 40 Ströme, je
   Reihe mit der Klassifikation aus T37;
3. **historische Politikpfade** für Leitzins, Zollniveau und Haushaltssaldo. Der vierte
   Hebel, Finanzmarktregulierung, hat keinen Anker und steht im Weltlauf fest auf seinem
   Startwert — was das Orakel für dieses Instrument blind macht, und das gehört in jeden
   Befund;
4. **exogene Pfade** nach T25;
5. **Konstanten des Jahrgangs**: `durchgriff[Gebiet][handelbarer Sektor]`, also zehn Werte
   in Zehntausendsteln. Bildungsregel mit `H` = Aus- plus Einfuhr des Sektors im Startjahr
   (aus BACI über die Konkordanz in Punkt 9) und `N` = seine Wertschöpfung (aus WDI):

   ```
   durchgriff = teile_gerundet(10.000 · H, H + N)
   ```

   Der Wertebereich 0 … 10.000 gilt damit für alle nichtnegativen `H`, `N` per
   Konstruktion; eine Kappung gibt es nicht und darf es nicht geben, weil sie den Fehler
   aus Befund 3 nur verstecken würde. **Der einzige undefinierte Fall ist `H + N = 0`** —
   ein Sektor ohne Wertschöpfung und ohne Handel. Der Jahrgangsbau setzt dann
   `durchgriff = 0` (der Sektorpreis folgt vollständig dem Landespreis, was für einen
   Sektor ohne Handel die richtige Aussage ist) und **meldet den Fall im Manifest als
   Befund**, weil ein Gebiet mit einem leeren Sektor eine Datenfrage aufwirft und keine
   Rechenfrage. Er tritt im Prüfjahrgang bei keinem der fünf Gebiete auf; die Regel steht
   hier, damit der Jahrgangsbau nicht an einer Division abbricht, deren Ursache er nicht
   nennt;
6. **abgeleitete Kennzahlen**: die mittlere absolute Jahresänderung je Land als
   Schwankungsbreite für den Innerjahresausschlag. Mittlere absolute Abweichung, nicht
   Standardabweichung — die bräuchte eine Wurzel und damit Gleitkomma (T4);
7. **Normierung**: die drei Sektoranteile je Gebiet und Jahr werden auf 10.000 normiert,
   weil die WDI-Anteile wegen der Gütersteuern abzüglich Subventionen nicht auf 100 Prozent
   summieren. Die Normierung — Verfahren und der je Gebiet und Jahr abgeschnittene Rest —
   steht im Manifest, und der Rückvergleich vergleicht normiert gegen normiert;
8. **Brüche**: je Reihe ein Feld `exogen_ab` und ein Feld `verkettet_ab`, beide als
   Jahreszahl gespeichert und nach T40 in eine Runde umgerechnet. Für Deutschland trägt der
   Leitzins `exogen_ab = 1999`, im Prüfjahrgang also **Runde 3**, und die Wechselkursreihe
   `verkettet_ab = 1999` mit dem unwiderruflichen Umrechnungskurs;
9. **die Konkordanz HS92 → Modellsektor**, als Tabelle im Manifest und nicht im Code
   (Befund 12). Sie lautet nach `spiel.md`: Kapitel **01–24 → Sektor 1 Landwirtschaft**,
   **25–97 → Sektor 2 Industrie**. Dieselbe Tabelle erzeugt `H` aus Punkt 5, die
   Handelsstartmatrix und die 40 Sollströme des Handelsblocks — deshalb ist ihr
   Zuordnungsfehler für den Rückvergleich folgenlos, und deshalb darf es sie nur einmal
   geben. Eine zweite Kopie im Code wäre die Gelegenheit, sie auseinanderlaufen zu lassen;
10. **die Restwelt als Rest**, in beiden Größen ausdrücklich gebildet: Ihre Aggregate sind
    die Weltreihe der Weltbank minus die vier Länder; ihre Handelszeilen sind die
    Gesamtein- und -ausfuhr eines Landes im Sektor minus die Ströme zu den drei anderen.
    **Je gerichtetem Paar steht genau eine Zahl** (BACI meldet den Ausfuhrwert; ein
    getrennter Einfuhrwert würde die Invariante „Summe aller Handelsbilanzen = 0" von der
    Datenqualität abhängig machen statt von der Bauart).

Größenordnung: 5 Gebiete × 25 Jahre × rund 30 Reihen × 8 Byte = 30 kB, Handel
`40 × 25 × 8` = 8 kB. Der ausgelieferte Datenteil bleibt je Jahrgang deutlich unter
100 kB und mit allen Jahrgängen deutlich unter einem Megabyte.

**T24 — Lücken werden gekennzeichnet, nicht stillschweigend gefüllt — und der Prüfjahrgang
duldet keine.** Je Reihe, Land und Jahr ein Flag `gefuellt`. Die Füllregel steht im
Manifest (Fortschreibung des letzten bekannten Werts, lineare Ganzzahlinterpolation
zwischen Stützstellen), und **gefüllte Jahre zählen im Fehlermaß des Rückvergleichs nicht
mit**, sondern werden gezählt und ausgewiesen.

Zwei Schwellen:

- **Prüfjahrgang 1997–2021:** `spiel.md` verlangt jede der 31 Sollreihen und jeden der 40
  Handelsströme über **25 Stützstellen ohne Füllung**, also `gefuellt = 0`. Eine Reihe, die
  das nicht erfüllt, wird **nicht gefüllt und nicht stillschweigend übernommen**, sondern
  als Befund an den Spielentwerfer gemeldet, samt der beiden Auswege, die ihm zustehen:
  Reihe streichen oder Fenster kürzen. Nach T40 kostet die zweite Wahl nur eine Zahl im
  Manifest.
- **Spieljahrgänge:** Eine Sollreihe, die zu mehr als einem Fünftel gefüllt ist, gilt als
  nicht belastbar und wird im Befund als solche markiert.

**Der Verdachtsfall ist enger geworden, aber nicht geschlossen.** Fassung 2 hat hier die
chinesischen und brasilianischen Leitzinsreihen der neunziger Jahre genannt; `spiel.md`
Fassung 3 hat den Fall gegen `FR.INR.LEND` geprüft (China 1995–2023 lückenlos, Brasilien
ab 1997) und damit ein Indiz, keinen Beweis. `FR.INR.LEND` ist eine andere Reihe als der
IFS-Leitzins, und `imf.org` weist den Abruf mit HTTP 403 ab. Der Jahrgangsbau prüft es an
der Reihe, die tatsächlich eingebettet wird. **Das ist unverändert die wahrscheinlichste
Stelle, an der das Vorhaben an Daten scheitert** — nur ist sie jetzt billig, weil sie
niemanden mehr zwingt, ein Paket zweimal zu bauen.

**T25 — Die Grenze zwischen exogen und endogen ist die Grenze der Aussagekraft des
Orakels, und deshalb ist sie eng gezogen.**

| Größe | im Spiel | Begründung |
|---|---|---|
| Bevölkerung, Erwerbstätige | **exogen**, Pfad aus Daten | Demografie ist nach `spiel.md` ausdrücklich keine Spielgröße |
| Restwelt-Nachfrageniveau | **exogen**, Pfad aus Daten | Randbedingung des Modells; der Rückvergleich prüft die Restwelt folglich nicht |
| `durchgriff` | **exogen und konstant**, Konstante des Jahrgangs | so von `spiel.md` festgelegt, samt der dort benannten Vereinfachung: Chinas wachsende Handelsoffenheit bildet das Modell über Mengen ab, nicht über die Preisübertragung |
| Produktivität | **endogen**, nur Startwert aus PWT | Würde sie jährlich aus den Daten gelesen, wäre das BIP im Rückvergleich eine Wiedergabe der Sollreihe und der Test prüfte sich selbst |
| Preise, Zinswirkung, Handel, Staatsfinanzen, Zustimmung | **endogen** | das ist die Maschine, die geprüft werden soll |
| Politikinstrumente | im `spielmodus` endogen, im `weltlauf` auf die historischen Pfade gesetzt | so verlangt es `spiel.md` — mit der Folge aus T37 und der Maske aus T38 |

**T26 — Ein gesperrter oder fehlender Datenanker ändert das Programm nicht, nur das
Manifest.** Drei Fälle, alle nach demselben Muster: Der Jahrgang trägt ein Modellkonstrukt,
das Manifest sagt es, der Befund wiederholt es.

| Fall | Ersatz | Folge für das Orakel |
|---|---|---|
| Aggregierter Zollsatz fällt unter die Drittanbieter-Ausnahme (die schwerste offene Frage aus `spiel.md`) | kein Zollpfad; der Weltlauf läuft mit konstantem Zoll | zwei statt drei verankerte Instrumente |
| Sektorale Beschäftigung (Reihe 7) gesperrt | Aufteilung nach Wertschöpfungsanteil | Startwert wird Modellkonstrukt, keine Sollreihe betroffen |
| **Spieljahrgang vor 1995 braucht eine Handelsmatrix, BACI beginnt 1995** | IWF-DOTS-Aggregate je Länderpaar, aufgeteilt nach den WDI-Sektoranteilen des Ausfuhrlandes | die Startmatrix ist ein Modellkonstrukt; Spieljahrgänge tragen ohnehin keinen Handelsblock im Rückvergleich (`spiel.md`) |

Der dritte Fall betrifft nach der Verschiebung auf 1997 nicht nur die Jahrgänge vor 1995,
sondern auch 1995 und 1996: Sie sind nach `spiel.md` Spiel-, aber keine Prüfjahrgänge und
tragen als US-Startwert die Sektorstruktur von 1997, gekennzeichnet als `gefuellt`.
Lizenz- und Deckungsrisiko sind damit eine Eigenschaft der Datenschicht, nie eine des Kerns.

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
| 14 | Bilaterale Ströme nach HS92, aggregiert über die Konkordanz aus T23 Punkt 9 | 5 × 4 × 2 | Tsd USD | CEPII BACI | Start + Sollblock (frei) | nein |
| 15 | Preisniveau im Ländervergleich | 4 + RW | Index | PWT | Start (Numéraire) | nein |
| 16 | `durchgriff` | 5 × 2 | Zehntausendstel | BACI + WDI, abgeleitet nach T23 Punkt 5 | Konstante des Jahrgangs | nein |
| 17 | Sektorpreise | (4+RW) × 3 | Index | **keine** | endogen, kein Soll | — |
| 18 | Zustimmung | 4 | Zehntausendstel | **keine** | aus `parameter.toml` | — |
| 19 | Marktkorbwert und Marktrendite | 1 + 1 | Tsd USD / bp | **keine** | Startwert nach T33, endogen, kein Soll | — |

`NV.IND.MANF.ZS` (verarbeitendes Gewerbe) wird nach `spiel.md` **nicht** verwendet und ist
deshalb hier nicht aufgeführt. Die 31 Sollreihen sind die Zeilen 1, 2, 8, 9, 10 und 11
(4+12+4+4+3+4); der Handelsblock aus Zeile 14 kommt als eigener Block hinzu. Die vier
Größen ohne Datenanker sind die Zeilen 17, 18, 19 und das Instrument
Finanzmarktregulierung — genau die vier, die `spiel.md` unter „Die Grenze des Orakels"
aufzählt.

**T27 — Die Kalibrierdatei liegt ausserhalb des Codes.** Sämtliche Zahlenwerte, die
`spiel.md` ausdrücklich der Kalibrierung überlässt — Mandatsschwelle, drei
Aufsichtsschwellen, Nachahmergeschwindigkeit, Stufenweite einer Position, Lobbykosten,
Anlegerabzugsanteil, Startkapital, Startzustimmung, Verzögerungen, Elastizitäten — stehen
in `parameter.toml`, werden als Dezimalzeichenketten in skalierte Ganzzahlen gelesen (T4)
und in eine Struktur mit benannten Feldern gefüllt, nie über eine Schleife über Schlüssel
(T9). Die Prüfsumme des Parametersatzes steht im Zustand und in jedem Speicherstand. Damit
ist Kalibrieren eine Datenänderung, die kein Übersetzen braucht — genau die Bauart, die
`spiel.md` an Democracy 4 belegt hat, und die Voraussetzung dafür, dass ein Agent über
Nacht tausend Parametersätze durchsucht (Abschnitt 10).

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

```
preis = teile_gerundet(weltpreis_mit_zoll · durchgriff
                       + landespreis · (10.000 − durchgriff),  10.000)
```

mit `landespreis = lies_alt(gebiet.sektor.preis)` nach T39, in Runde 1 also dem Startwert
10.000. Angebot und Nachfrage werden auf diesem Preis gebildet.

**Damit ist die Zulässigkeit der Halbierung belegt statt behauptet** — und das ist die
Behebung von Befund 6, nicht nur seine Beantwortung. Beide Gewichte sind nichtnegativ
(`durchgriff` liegt nach T23 Punkt 5 in 0 … 10.000), `landespreis` steht fest, während die
Halbierung läuft, und `preis` ist deshalb monoton wachsend im Weltpreis. Die
Überschussfunktion erbt diese Monotonie, es entsteht keine Fixpunktaufgabe, und ein Durchlauf
genügt. Die zweite Lesart des Prüfers — `landespreis` als räumender Inlandspreis derselben
Runde — hätte genau das zerstört; sie ist mit T39 nicht nur verworfen, sondern nicht mehr
formulierbar.

Dienstleistungen haben keine Handelszeile, keinen Weltpreis und `durchgriff = 0`; ihr
Sektorpreis ist die reine Fortschreibung des Vorrundenpreises durch die inländische
Räumung.

**T29 — Ganzzahlige Potenzen und Wurzeln über Newton auf `i128`.** Wo die
Produktionsfunktion einen Exponenten wie 1/3 braucht, wird `wurzel(x, n)` mit fester
Schrittzahl verwendet; Exponenten sind auf Brüche kleiner ganzer Zahlen beschränkt. Keine
Reihenentwicklung, kein Logarithmus, keine Tabelleninterpolation.

**T33 — Marktrendite und Fondsrendite werden über einen eingefrorenen Mengenkorb
gerechnet.** `spiel.md` hat die Auslegung entschieden: wertgewichtete Rendite aller
handelbaren Körbe zu Modellmarktwerten, gewichtet nach dem Markt und **nicht** nach dem
Bestand des Fonds. Die Regel, in Schritt 6 der Runde und nur im `spielmodus`:

1. Der **Marktkorb** umfasst die 12 Land×Sektor-Körbe und die 4 Staatsanleihen, jeweils zu
   Modellmarktwerten. Währungen tragen keine Marktkapitalisierung und gehen nicht ein; ihre
   Wirkung steckt in der Umrechnung der übrigen Körbe in den Numéraire.
2. `markt.wert` trägt den Wert dieses Korbs am Ende der Vorrunde. **In Runde 1 ist es der
   Startwert aus dem Jahrgang** — der Wert des Startkorbs zu Startpreisen, vom Jahrgangsbau
   gerechnet und im Manifest ausgewiesen. Damit ist die zweite Hälfte von Befund 2
   geschlossen, unabhängig vom Modus.
3. Bewerte den **Mengenkorb der Vorrunde** zu den Preisen dieser Runde: `W_neu`.
   `markt.rendite = teile_gerundet((W_neu − markt.wert) · 10.000, markt.wert)` in
   Basispunkten.
4. Erst danach wird `markt.wert` auf den Wert des **neuen** Korbs zu neuen Preisen gesetzt.

Mengenwachstum erzeugt damit keine Scheinrendite.

**Die Fondsrendite entsteht in derselben Reihenfolge, und die Reihenfolge ist die Regel:**
(a) Positionen bewerten, (b) Fondsvermögen als Kasse plus bewertete Positionen minus Hebel
bilden, (c) ist es **null oder kleiner**, greift nach `spiel.md` Todesart 1 in derselben
Runde und die Partie endet ohne Renditebildung, (d) erst sonst wird die Rendite gebildet:
Änderung des Fondsvermögens gegenüber der Vorrunde, **bereinigt um Anlegerzu- und -abflüsse
dieser Runde** — sonst zählte frisches Anlegergeld als Leistung und der Anlegerabzug aus
Gegenkraft 3 verstärkte sich selbst. Die Überrendite ist die Differenz beider Größen in
Basispunkten und steht für drei Runden im Zustand.

Schritt (c) vor (d) ist keine Feinheit: Er ist der Grund, warum `teile_gerundet` in diesem
Modell nie einen Nenner null sieht, ohne dass irgendwo ein Sonderfall geprüft würde.

## 9. Test- und Prüfstandsaufbau

**T30 — Acht Prüfungen, ein Aufruf.** `nacht` läuft der Reihe nach und bricht mit einem
Rückgabewert ungleich null ab, sobald eine Schwelle aus `spiel.md` gerissen ist. Was nicht
in einem Aufruf läuft, läuft nachts nicht.

| # | Prüfung | Gegenstand | Verantwortlich |
|---:|---|---|---|
| 1 | Einheitstests je Wirkungskette | jeder Pfeil aus `spiel.md` einzeln, auf einem Minimalzustand: Zoll rauf → Einfuhr runter → Preis rauf → Realeinkommen runter → Zustimmung runter. Dazu die Fünf-Runden-Invariante des Vorratsverfahrens aus T43 | Testentwickler |
| 2 | Invariantentest | Summe aller Handelsbilanzen einschliesslich Restwelt = 0; Staatsschuld(t) = Staatsschuld(t−1) − Saldo; Fondsvermögen = Kasse + bewertete Positionen − Hebel; die drei Sektoranteile je Gebiet summieren auf 10.000; kein Anteil ausserhalb 0…10.000; jedes Partieergebnis in einem der drei Bänder aus T34 | Testentwickler |
| 3 | Determinismustest | derselbe Startwert, Modus und dieselbe Aktionsfolge ergeben dieselbe Prüfsumme — zweimal im Lauf, über Speichern und Laden hinweg, und auf jeder Zielplattform verglichen | Testentwickler |
| 4 | Regressionsbestand | gespeicherte Partien nach T22 rechnen bitgleich nach; zusätzlich eine Prüfsumme über die Kette, damit auch eine geänderte *Begründung* auffällt; mindestens eine Partie auf einem Spieljahrgang 1980 mit Basiswechsel (T8) | Testentwickler |
| 5 | Bruchlauf | 10.000 Partien mit dem Zufallsbot: kein Absturz, kein Überlauf, keine Invariantenverletzung, kein Kettenüberlauf, kein doppelter Schreibzugriff und keine Maskenverletzung (T18, T38, T39) | Bruchtester |
| 6 | **Beschränktheit** | **200 Runden ohne Spieler**; verlässt eine Größe ihren Wertebereich, gibt es einen achten Rückkopplungskanal, und der ist ein Befund | Bruchtester |
| 7 | Die drei Maße | Entscheidungsdichte, Strategievielfalt, Optimumsverschiebung nach den Rechenvorschriften in `spiel.md`, gegen die dortigen Schwellen: **0,4 je Partiedrittel**; **drei Klassen mit je einem Gewinner bei höchstens 25 % Abstand**; **Verschiebung ≥ 0,4** | Selbstspieler |
| 8 | Rückvergleich | im Modus `weltlauf` (T38), 31 Sollreihen plus Handelsblock, Fehlermaße nach T42, Abnahme über die **16 Prüfgegenstände mit Toleranz 2** nach T37 | Rückvergleicher |

**Prüfung 6 läuft über das Ende des Jahrgangsfensters hinaus, und das braucht eine Regel.**
Die exogenen Pfade aus T25 tragen nur R+1 Stützstellen. Ab Runde R+1 werden sie **auf ihrem
letzten Wert eingefroren**, nicht fortgeschrieben, und der Lauf wird als `ueber_fenster`
gekennzeichnet. Einfrieren ist hier die schärfere Wahl: Läuft eine Größe danach weg, ist es
das Modell und nicht die Eingabe. Kosten: 200 Weltschritte.

**T31 — Der Regressionsbestand wird nie stillschweigend neu erzeugt.** Ein bewusst
geänderter Modellwert macht Prüfung 4 rot — das ist der Zweck. Die Erneuerung läuft
über einen eigenen Aufruf, der einen **Abweichungsbericht** schreibt: welche Partie,
welche Größe, alter und neuer Wert, welche Kettenglieder sich geändert haben. Dieser
Bericht ist der Gegenstand der Prüfung, nicht der neue Bestand.

**T34 — Die Ergebnisgröße ist ein `i64` in Milli-Runden; die Skala gehört `spiel.md`.**
Die dreiteilige Tabelle steht dort und wird hier **nicht** wiederholt, nicht ausgelegt und
nicht gedeckelt. Was der Architektur zusteht, ist ausschliesslich:

- Typ `i64`, Einheit Milli-Runden, **kleiner ist besser**;
- die Ordnung ist strikt total: Bei gleichem Ergebniswert entscheidet die Profilkennung,
  bei gleichem Profil der Stichprobenindex — nie die Auffindereihenfolge;
- der Median über eine gerade Anzahl ist der kleinere der beiden mittleren Werte
  (so `spiel.md`);
- **die Bereichsprüfung ist die Bandprüfung.** `spiel.md` verlangt: ein Ergebnis ausserhalb
  `1.000 … R × 1.000 + 30.000` — bei R = 24 also 1.000 … 54.000 — ist ein harter Fehler.
  Geprüft wird schärfer und ohne eigene Entscheidung, weil es aus derselben Tabelle folgt:
  Der Wert muss in **einem der drei Bänder** aus T40 liegen. Die Lücken dazwischen
  (24.001 … 24.999 und 27.001 … 30.999 bei R = 24) sind unerreichbar; ein Wert dort ist ein
  Rechenfehler und kein Ausreisser. Die Prüfung kostet zwei Vergleiche und findet genau die
  Kante, die Befund 10 an der Skala selbst gefunden hat.

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
   Ziehreihenfolge das Ergebnis nicht berührt. Verletzt es `buendel_zulaessig` (T32), wird
   es auf das größte zulässige Anfangsstück gekürzt — nicht neu gezogen, weil eine
   Verwerfungsschleife die Zahl der Ziehungen zustandsabhängig machte.
5. **Die Vorratsfortschreibung der eingespeisten Runde** folgt `spiel.md`: `vi += 3·ai` am
   Rundenanfang mit dem `ai` des Referenzprofils, dann `vi −= 5` je tatsächlich gesetzter
   Aktion der Art `i`. Bei einem Bündel kleiner als drei driftet der Vorrat, und das ist
   gewollt — die Trägerpartie spielt danach mit dem Zustand weiter, den die Einspeisung
   hinterlassen hat, nicht mit einem zurechtgesetzten.

`naechster(s) mod k` ist verzerrt, sobald `k` kein Teiler von 2^64 ist. Die Verzerrung
liegt bei `m ≤ 2^32` unter 2^-32 und ist damit kleiner als jede Wirkung, die Maß 1 misst;
sie wird hier benannt statt behoben, aus demselben Grund wie in Punkt 4.

**T43 — Das Vorratsverfahren ist ein Baustein des Prüfstands, und es hat eine Invariante,
die es testbar macht.** `spiel.md` legt es fest (Vorrat `vi`, `vi += 3·ai` je Runde, drei
Steckplätze, `vi −= 5` je Steckplatz, größtes `vi` gewinnt, Gleichstand nach kleinerer
Kennung, `ai = 0` verbietet nicht, sondern schiebt ans Ende). Der Architektur stehen zwei
Dinge zu, und beide stehen hier:

- **Die Zulässigkeit, gegen die es prüft, ist die Liste aus T32** — einmal je Runde gegen
  den Rundenanfangszustand gebildet, beim Fortschreiten über die drei Steckplätze nur um
  die mit dem Bündel unverträglichen Einträge gekürzt. Kein Weltschritt, keine
  Zwischenrechnung.
- **Die Invariante, gegen die ein Einheitstest läuft:** Sind in fünf aufeinanderfolgenden
  Runden alle fünf Arten durchgehend zulässig, so steht der Vorratsvektor danach wieder auf
  `(0,0,0,0,0)`, und jede Art `i` hat genau `3·ai` der fünfzehn Steckplätze bekommen. Das
  gilt für **alle 126 Profile** — ich habe es für alle 126 durchgerechnet, und die von
  `spiel.md` selbst angegebene Probe des Referenzprofils (`1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 |
  3,4,5`) fällt dabei zeichengleich heraus. Damit ist das Verfahren nicht nur beschrieben,
  sondern hat einen Test, der eine falsche Implementierung in fünf Runden fängt statt in
  einer 24-Runden-Partie mit Median über zwanzig Startwerte.

**T41 — Wie das Profil die Kandidaten des Suchbots einschränkt.** Das war die Hälfte von
Befund 4, die mir gehörte: T35 schrieb die Ziehregel nur für Maß 1 aus. Verbindlich ist:

1. Das Vorratsverfahren (T43) liefert für die Runde die Artenfolge der drei Steckplätze.
   Der Suchbot sucht **über Ziele und Stufen, nie über Arten** (`spiel.md`).
2. Für Kandidat `c = 0 … 59` und Steckplatz `j = 1,2,3`: `Lj` ist die Teilliste der
   zulässigen Aktionen der Art des Steckplatzes in kanonischer Ordnung (T32), gekürzt um
   die mit den schon gewählten `x1 … xj−1` unverträglichen Einträge. Gezogen wird
   `xj = Lj[naechster(s) mod |Lj|]` mit
   `s = splitmix64(…, SUCHBOT_KANDIDATEN, runde, c)`.
3. Ein Steckplatz ohne zulässige Art entfällt; `|Lj| ≥ 1` gilt sonst immer, weil das
   Vorratsverfahren nur unter Arten wählt, die mindestens eine zulässige Aktion haben.

**Genau drei Ziehungen je Kandidat, genau 60 Kandidaten, keine Verwerfungsschleife, keine
Zählung eines Produktraums.** Doppelte Kandidaten bleiben — wie in Maß 1 —, sie kosten ein
Nachspiel und ändern kein Ergebnis. Der Preis ist damit fest bei `1 + 60` Weltschritten je
Runde, unabhängig davon, wie groß die Zulässigkeitsliste gerade ist; das ist dieselbe
Begründung wie bei T28 und der Grund, warum die Rechnung in Abschnitt 10 überhaupt trägt.

**Die drei Bots:**

- **Zufallsbot(startwert)** — zulässige Aktionen gleichverteilt, Ziehung nach T35, ohne
  Profil. Für Prüfungen 5 und 6.
- **Heuristikbot(profil)** — Arten nach dem Vorratsverfahren (T43), innerhalb einer Art
  nach einer festen, dokumentierten Rangfolge. Keine Nachspiele, also billig. **Er ist auf
  dem Referenzprofil `(1,1,1,1,1)` die „feste Folgepolitik" von Maß 1.**
- **Suchbot(profil, kandidaten=60, tiefe=1)** — 60 Kandidaten nach T41, bewertet durch ein
  Nachspiel von einem Zug mit dem Heuristikbot als Fortsetzung. Gleichstand nach
  Aktionskennung, nie nach Auffindereihenfolge. Kosten je Partie `R × 61`, bei R = 24 also
  **1.464** Weltschritte.

**T36 — Was der Prüfstand zu Maß 2 und 3 fest verdrahtet.**

- **Profilliste.** Die 126 Profile werden in lexikographisch aufsteigender Ordnung von
  `(a1…a5)` erzeugt und **nullbasiert** durchnummeriert. Die **Profilkennung** ist dieser
  Index und der Gleichstandsbrecher aus `spiel.md`; sie ist Teil der Schnittstellenversion
  (T17). Zwei Festwerte als Anker für den Test, beide durchgerechnet: Das Referenzprofil
  `(1,1,1,1,1)` trägt die **Kennung 76**, und die Kennungen **0 bis 5** sind genau die sechs
  Profile `(0,0,0,a4,a5)`.
- **Strategiekern, vierwertig.** Aktionsart mit dem größten Anteil unter `{1 Position,
  2 Beteiligung, 3 Lobby}`, Gleichstand nach kleinerer Kennung; Hebel und Sichtbarkeit gehen
  nicht ein. **Sind alle drei null, ist der Kern `ohne`** — nicht 1. Das ist Befund 8, und
  er lässt sich nur an dieser Stelle beheben: Ein dreiwertiger Kern zwingt den
  Gleichstandsbrecher, eine Positionsstrategie zu behaupten, in der keine Position vorkommt.
  Profile mit Kern `ohne` laufen mit, ihr Ergebnis wird berichtet, und sie gehen in keine
  der beiden Abnahmehälften von Maß 2 ein; klassifiziert sind 120. Der Kern wird einmal je
  Profil berechnet und mit der Profilliste abgelegt, nicht je Lauf neu.
- **Fensterlogik von Maß 3.** Beide Läufe gehen über die volle Partie; die Fenster sind
  nach T40 das erste und das letzte Partiedrittel, ausserhalb gilt das Referenzprofil, und
  der Suchbot fährt innerhalb wie ausserhalb. Der Profilwechsel geschieht am Rundenanfang;
  **der Vorrat läuft über den Wechsel hinweg weiter und wird nicht zurückgesetzt**
  (`spiel.md`). Damit kostet ein Lauf dasselbe wie eine gewöhnliche Suchbotpartie, und die
  Rechnung in Abschnitt 10 trägt. Für Maß 3 sind alle 126 Profile wählbar, auch die sechs
  ohne Kern — dort misst der Vektorabstand und nicht die Klasse.

**T37 — Der Rückvergleich weist je Sollreihe aus, ob sie überhaupt etwas prüfen kann — und
`spiel.md` hat entschieden, welche entscheiden.** Im Weltlauf werden die Politikinstrumente
auf die historisch tatsächlichen Werte gesetzt. Damit ist die Leitzinsreihe des Modells per
Konstruktion die Sollreihe; ihr Fehler ist null und ihre Richtungstreue eins, ohne dass das
Modell irgendetwas geleistet hätte.

| Klasse | Reihen | Zahl | Bedeutung |
|---|---|---:|---|
| `frei` | BIP (4), Sektoranteile (12), Verbraucherpreise (4), Wechselkurs (3) | 23 (19 unabhängig), dazu der Handelsblock | prüft die Maschine, entscheidet die Abnahme |
| `gesetzt` | Leitzins (4) | 4 | Eingabe des Laufs, Fehler null per Konstruktion; wird berichtet, entscheidet nichts |
| `abgeleitet` | Staatsschuldenquote (4) | 4 | Zähler folgt dem gesetzten Haushaltssaldo, nur der Nenner ist endogen; wird berichtet, entscheidet nichts |

**Die Abnahme läuft über 16 Prüfgegenstände mit Toleranz 2**, so von `spiel.md` Fassung 3
gesetzt; meine Rückfrage aus Fassung 2 ist damit beantwortet und aus Abschnitt 12
gestrichen. Prüfgegenstand ist nicht die Reihe, sondern die Größe:

| Prüfgegenstand | Zahl | zusammengefasst aus |
|---|---:|---|
| BIP je Land | 4 | je eine Reihe |
| Sektorstruktur je Land | 4 | die drei Anteilsreihen des Landes, **alle drei** müssen bestehen |
| Verbraucherpreise je Land | 4 | je eine Reihe |
| Wechselkurs je Land ausser USA | 3 | je eine Reihe |
| Handelsblock | 1 | 40 Ströme, Median des MAPE und Median der Richtungstreue; das schlechteste Fünftel wird ausgewiesen |
| **Summe** | **16** | |

Ein Prüfgegenstand besteht, wenn er beide für ihn geltenden Schwellen einhält. Der Lauf ist
bestanden, wenn höchstens zwei der sechzehn reissen; jeder gerissene wird einzeln benannt,
mit beiden Zahlen. Berichtet werden alle 31 Reihen plus die 40 Ströme, entscheiden tun die
sechzehn.

**T42 — Die drei Fehlermaße, ausgeschrieben, weil `spiel.md` sie beziffert und nicht
rechnet.** Alles in Ganzzahlen über `teile_gerundet` (T6). `S` ist die Zahl der
Stützstellen (im Prüfjahrgang 25), `V` die Menge der verwertbaren Stützstellen.

**Niveaureihen** (BIP, Sektoranteile, Staatsschuldenquote, 40 Handelsströme) —
mittlerer absoluter prozentualer Fehler in Zehntausendsteln, Schwelle **2.000 (= 20 %)**:

```
MAPE = Mittel über t ∈ V von  teile_gerundet(|modell(t) − soll(t)| · 10.000, |soll(t)|)
```

**`V` schliesst zwei Sorten Stützstelle aus, beide gezählt und ausgewiesen:** die mit
`gefuellt = 1` (so schon T24) und die mit `soll(t) = 0`. Der zweite Fall ist bei einem
bilateralen Agrarstrom zwischen zwei Ländern real, und ein Nullnenner ist nach T6 ein
Abbruch. Hat ein Strom weniger als die Hälfte verwertbarer Stützstellen, gilt er als nicht
prüfbar, geht in den Median des Handelsblocks nicht ein und wird als solcher berichtet. Die
Regel ändert keine Schwelle; sie definiert einen Fall, den `spiel.md` nicht kennt, nach dem
Muster, das T24 für gefüllte Jahre schon vorgibt.

**Ratenreihen** (Verbraucherpreise, Wechselkurs, Leitzins) — mittlerer absoluter Fehler auf
der Jahresänderungsrate, Schwelle **300 bp**:

```
rate(t) = teile_gerundet((wert(t) − wert(t−1)) · 10.000, wert(t−1))          in bp
MAE     = Mittel über t = 2 … S von |rate_modell(t) − rate_soll(t)|
```

**Eine Neubasierung nach T8 wird vor der Ratenbildung herausgerechnet:** Steigt
`basiswechsel` zwischen `t−1` und `t` um `d`, wird `wert(t)` für diese eine Rate mit
`1.000^d` multipliziert. Ohne diese Zeile meldete ein Basiswechsel einen Absturz um 99,9
Prozent als Modellfehler. Im Prüfjahrgang tritt sie nie ein — sie steht hier, weil T8 selbst
verlangt, dass kein Zweig ungeprüft bleibt, und die Regressionspartie von 1980 sie
mitnimmt.

**Richtungstreue** (alle Reihen) — Anteil der `S−1` Übergänge mit gleichem Vorzeichen, in
Zehntausendsteln, Schwelle **6.000 (= 0,6)**:

```
treue = teile_gerundet(#{t : sgn(Δmodell(t)) = sgn(Δsoll(t))} · 10.000, S − 1)
```

`sgn` ist die dreiwertige Vorzeichenfunktion auf Ganzzahlen; „beide unverändert" zählt
damit als Treffer und „einer unverändert, einer nicht" als Fehlschlag. Das folgt aus der
Schreibweise in `spiel.md` und ist keine Auslegung — auf Ganzzahlen gibt es keine andere.

**Parallelität ohne Preisgabe des Determinismus:** Jedes Nachspiel ist eine reine Funktion
von (Jahrgang, Parametersatz, Modus, Startwert, Politik, Runde, Stichprobenindex); der
abgeleitete Zufallsstartwert folgt aus genau diesem Tupel (T11). Ergebnisse werden in ein
vorab bemessenes Feld **an ihrem Index** abgelegt, nie angehängt. Jede Zusammenfassung läuft
über das sortierte Feld. Damit liefert der Prüfstand mit einem Kern und mit
zweiunddreissig dasselbe Ergebnis.

**Berichtspflicht:** Jeder Befund trägt `ticks_gesamt`, `sekunden`, `ticks_je_sekunde`, den
Modus und die Größe der Sollmaske. Die Schätzung des nächsten Abschnitts wird damit binnen
einer Nacht durch eine Messung ersetzt — und bleibt gemessen.

## 10. Was das Modell an Rechenzeit kostet

Ein Weltschritt umfasst geschätzt 7.500 elementare Ganzzahloperationen; den Löwenanteil
tragen die Markträumung (2 Sektoren × 40 Halbierungen, T28) und das Mitschreiben der
Kette (T18). Teuer sind darin die `i128`-Divisionen aus T6. **Planwert: 10 Mikrosekunden
je Schritt**, Bandbreite 5 bis 30. Die Spalte „ungünstig" rechnet mit 50 Mikrosekunden,
also dem Fünffachen des Planwerts — eine Reserve, keine Erwartung.

**Der Planwert ist unverändert geschätzt und nicht gemessen.** Mein Logbuch verlangt, beim
nächsten Lauf zuerst den gemessenen `ticks_je_sekunde` zu lesen; es gibt ihn nicht, weil
unter `ventures/0016-…/` noch keine Zeile Code steht. Das bleibt die größte Unsicherheit
dieses Abschnitts, und sie steht in Abschnitt 12.

Grundlage ist die **R = 24-Runden-Partie** aus `spiel.md` Fassung 3. Alle Zeilen sind in
diesem Lauf gerechnet.

| Lauf | Weltschritte | bei 10 µs | ungünstig (50 µs) |
|---|---:|---:|---:|
| eine Partie, Heuristikbot | 24 | 0,24 ms | 1,2 ms |
| eine Partie, Suchbot (60 Kandidaten, 1 Zug voraus) | 1.464 | 15 ms | 73 ms |
| **1.000 Partien, Heuristikbot** | 24.000 | **0,24 s** | 1,2 s |
| **1.000 Partien, Suchbot** | 1.464.000 | **15 s** | 1,2 min |
| Entscheidungsdichte, K=30, ein Startwert | 9.024 | 0,090 s | 0,45 s |
| **Entscheidungsdichte, 50 Startwerte** | **451.200** | 4,5 s | 23 s |
| **Strategievielfalt, 126 Profile × 20 Startwerte** | **3.689.280** | 37 s | 3,1 min |
| **Optimumsverschiebung, zwei Fenster** | **7.378.560** | 1,2 min | 6,1 min |
| **Bruchlauf, 10.000 Zufallspartien** | **240.000** | 2,4 s | 12 s |
| **Beschränktheit, 200 Runden** | **200** | 2 ms | 10 ms |
| **Rückvergleich, ein Weltlauf** | **24** | 0,24 ms | 1,2 ms |
| **Regressionsbestand, 1.000 Partien** | **24.000** | 0,24 s | 1,2 s |
| **Nachtlauf gesamt** | **11.783.264** | **2,0 min** | **9,8 min** |

Die Zeilen im Einzelnen, damit die Summe nachzählbar ist: `Σ(R+1−t)` für `t = 1…24` ist
`300`, also `30 × 300 = 9.000` je Startwert, zuzüglich 24 Weltschritte für die
Trägerpartie ergibt **9.024**; mal 50 Startwerte **451.200**. `126 = C(9,4)`,
`1.464 = 24 × 61`, `3.689.280 = 126 × 20 × 1.464`, `7.378.560` das Doppelte davon. Die drei
Maße zusammen sind **11.519.040**, so wie `spiel.md` es rechnet. Der Nachtlauf addiert
Bruchlauf, Beschränktheit, Rückvergleich und Regressionsbestand:
`11.519.040 + 240.000 + 200 + 24 + 24.000 = 11.783.264`. Die beiden Zeilen „1.000 Partien"
sind Vergleichswerte und gehen nicht in die Summe ein.

Alles auf **einem** Kern. Mit acht Kernen (`rayon`) fällt der Nachtlauf auf rund
**15 Sekunden** beim Planwert und auf rund **1,2 Minuten** im ungünstigen Fall.

**Die Antwort auf die Frage, die dieser Abschnitt beantworten soll: Ja, der Prüfstand kann
täglich laufen — und stündlich.** Der Engpass ist nicht die Rechenzeit, sondern das
Tokenbudget der Agenten, die die Befunde lesen.

**Die Kalibrierschleife.** Tausend Parametersätze über den vollen Maßsatz (11.519.040
Schritte je Satz) kosten 11,52 Milliarden Weltschritte, also **32,0 Stunden auf einem Kern
und 4,0 Stunden auf acht** — keine Nachtaufgabe. Nachtfähig ist die verkürzte Fassung:
Maß 1 mit 10 statt 50 Startwerten (90.240) und Maß 2 mit 5 statt 20 (922.320), Maß 3 gar
nicht, weil die Verschiebung des Optimums erst interessant ist, wenn Maß 1 und 2 halten.
Zusammen **1.012.560 Schritte je Parametersatz**, für tausend Sätze also **21 Minuten auf
acht Kernen**. Die Vorgabe an den Selbstspieler lautet deshalb: grob mit der verkürzten
Fassung suchen, die zehn besten Sätze mit der vollen nachrechnen.

**Die Gegenrechnung, die die Stackwahl trägt:** Derselbe Weltschritt kostet in Python
zwischen 0,75 und 3 Millisekunden, also das 75- bis 300-fache. Der Nachtlauf läge bei
**2,5 bis 9,8 Stunden** auf einem Kern. Er wäre damit nicht täglich, sondern gelegentlich —
und die Kalibrierschleife wäre auch in der verkürzten Fassung unmöglich. Das ist die Zahl,
an der die Wahl aus T1 hängt. Sie ist durch die kürzere Partie kleiner geworden, aber der
Abstand ist derselbe: Der Faktor entscheidet, nicht die Partielänge.

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

Die beiden Rückfragen aus Fassung 2 — Abnahme über 31 oder 23 Reihen, Zusammenfassung des
Handelsblocks — sind von `spiel.md` Fassung 3 beantwortet und stehen jetzt in T37. Offen
bleibt:

- **Der Planwert von 10 Mikrosekunden je Weltschritt ist weiterhin geschätzt.** Es gibt
  keinen Kern, also keine Messung. Liegt der gemessene Wert über 50 µs, trägt Abschnitt 10
  nicht mehr, und dann ist die Markträumung anders zu bauen als über 40 Halbierungsschritte.
  Das ist die einzige Zahl dieses Dokuments, die eine Prüfung im Bau umwerfen kann.
- **Ob der Suchbot mit Tiefe 1 stark genug ist, damit Maß 2 das Spiel misst und nicht den
  Bot.** Neu gerechnet für R = 24: Tiefe 2 kostet je Partie `24 × (1 + 60 × 61) = 87.864`
  statt 1.464 Weltschritte, Maß 2 und 3 zusammen **664 Millionen**, also 1,8 Stunden auf
  einem Kern und **rund 14 Minuten auf acht** beim Planwert, im ungünstigen Fall 1,2 Stunden
  auf acht. Das sprengt den Nachtlauf nicht, es verlegt ihn. Tiefe 2 ist damit kein
  Ausschluss, sondern eine Entscheidung, die der Selbstspieler treffen darf, wenn Maß 2 mit
  Tiefe 1 keinen Gewinner in allen drei Klassen findet.
- **Die Zahlenwerte sämtlicher Schwellen und Elastizitäten.** Sie stehen nach T27 in der
  Parameterdatei und werden vom Selbstspieler gesucht, nicht von mir gesetzt.
- **Die konkrete Rangfolge im Heuristikbot** innerhalb einer Art. Modellierungsfrage des
  Selbstspielers; die Architektur verlangt nur, dass sie fest, dokumentiert und
  gleichstandsfrei ist.
- **Die Ausschlussregel für Stützstellen mit `soll = 0` (T42) habe ich entschieden, nicht
  offengelassen** — sie folgt dem Muster, das T24 für gefüllte Jahre schon setzt, und ohne
  sie bricht der Rückvergleich an einem bilateralen Nullstrom ab. Sie ändert keine Schwelle.
  Hält der Spielentwerfer sie für falsch, ist sie eine Zeile in T42 und sonst nichts.

**Zwei Beobachtungen an `spiel.md`, die ich melde statt zu ändern** (die Rolle verbietet
mir, dem Entwurf zu widersprechen; beide blockieren nichts):

1. Der Satz zum Vorratsverfahren „über 15 Runden bekommt Art `i` genau `3·ai` Steckplätze"
   passt nicht zur Probe zwei Absätze darunter, die fünf Runden und fünfzehn Steckplätze
   rechnet. Ich habe das Verfahren für alle 126 Profile durchgerechnet: Die Invariante gilt
   **je fünf Runden**, und die Probe des Referenzprofils fällt zeichengleich heraus. Der
   Algorithmus selbst ist eindeutig; betroffen ist nur der zusammenfassende Satz. Die
   Invariante steht als Einheitstest in T43.
2. Die Ergebnisskala trägt in der 30.000 ein echtes Literal, und das Band „überlebt" stösst
   dagegen, sobald `R ≥ 27`. Für 1997–2021 ist das folgenlos, und `spiel.md` lässt das
   Fenster nur enger werden. T40 zieht die Schranke bei `R ≤ 26` in den Jahrgangsbau, damit
   sie nicht erst in einer Ergebnisverteilung auffällt.

## 13. Hinweis für den Projektmanager

Der Kastenschnitt aus T13 ist zugleich der Kollisionsschnitt für Arbeitspakete: Zwei
gleichzeitig offene Pakete dürfen sich nicht im selben Kasten treffen. Die natürliche
Reihenfolge ist `kern` (Zustand, Festkomma, Zufall, Prüfsumme, Schreiber mit T18/T38/T39)
→ `daten` und `schnittstelle` parallel → `konsole` → Tests und `pruefstand` →
`oberflaeche`. Der Jahrgang (`werkzeuge/aufbereitung`) kann von Beginn an parallel laufen,
weil er nur gegen T5, T23 bis T26 und T40 gebaut wird und nichts vom Kern braucht.

**Zwei Pakete sind vorzuziehen, weil sie Entwurfsrisiko tragen und nicht Bauaufwand:** der
Jahrgangsbau 1997 (T24 sagt, dass er scheitern kann — 25 Stützstellen ohne Füllung für alle
31 Reihen und alle 40 Handelsströme sind eine Behauptung, keine Tatsache, und der
IFS-Leitzins ist nur durch ein Indiz gestützt) und die Prüfung der vier WDI-Verdachtsreihen
7, 8, 10 und 13 auf die Drittanbieter-Ausnahme. Beide klären sich gegen Daten, nicht gegen
Code.

**Was gegenüber Fassung 2 billiger geworden ist:** Ein engeres Fenster kostet nach T40 eine
Zahl im Manifest und kein zweites Paket. Der Jahrgangsbau muss deshalb nicht mehr *vor* dem
Kern fertig sein, sondern nur vor dem ersten Rückvergleich — er bleibt trotzdem vorn, weil
er das Vorhaben kippen kann und nicht nur verzögern.

## 14. Befundabarbeitung — Prüfung der zweiten Fassung vom 2026-08-31

Zwölf Befunde, je einer der drei zulässigen Antworten. Kein Befund war falsch; es gibt
diesmal kein *widersprochen*.

**Befund 1, Prüfjahrgang 1995 mit 28 Runden nicht belegt — behoben, und die Behebung ist
nicht die Zahl.** R = 24, Fenster 1997–2021, 25 Stützstellen: Frontmatter, T22, T23 Punkt 8,
T24, T26 und Abschnitt 10 sind darauf neu gerechnet. Die eigentliche Antwort ist **T40**:
R ist eine Größe des Jahrgangs, und jede abgeleitete Zahl entsteht zur Laufzeit aus R statt
als Literal im Code. Ein weiteres Kürzen des Fensters kostet damit eine Manifestzeile. Dazu
die Schranke `R ≤ 26`, weil die Ergebnisskala von `spiel.md` bei 30.000 ein Literal trägt —
gefunden, indem ich die drei Bänder für wachsendes R ausgerechnet habe, statt die Skala zu
übernehmen.

**Befund 2, Rückvergleichslauf nicht durchführbar — behoben.** `spiel.md` hat den Modus
`weltlauf` entschieden; **T38** gibt ihm eine Architektur: Der Modus ist Argument von
`schritt` und kein 311. Zustandsfeld (das widerspräche der Feldzahl, die `spiel.md` selbst
nennt), er bringt eine **Sollmaske** mit, und der `Schreiber` prüft sie zweiseitig — jede
Adresse der Maske genau einmal geschrieben, keine ausserhalb berührt. Nachgerechnet: 175 der
310 Adressen im Weltlauf, 135 ausserhalb. Der Nenner null entsteht damit nicht, statt
abgefangen zu werden. Zwei Riegel kommen dazu: **T6** macht `nenner == 0` zum Abbruch statt
zum stillen Nullwert, und **T33** legt die Reihenfolge in Schritt 6 fest — Todesart-Prüfung
*vor* Renditebildung. Die zweite Lücke des Befundes, `markt.wert` ohne Startwert, schliesst
T33 Punkt 2 mit dem Startwert aus dem Jahrgang.

**Befund 3, `handelsanteil` verlässt seinen Wertebereich — behoben, mit der vierten Lösung
des Spielentwerfers.** Der Koeffizient heisst in T5, T23 Punkt 5, T25, T28 und Reihenliste
Nr. 16 jetzt `durchgriff` und wird als `teile_gerundet(10.000·H, H+N)` gebildet. **Eine
Ergänzung ist meine:** `H + N = 0` ist der einzige Fall, in dem die Formel undefiniert
bleibt; T23 Punkt 5 setzt dann `durchgriff = 0` und meldet den Fall im Manifest als Befund,
damit der Jahrgangsbau nicht an einer Division abbricht, deren Ursache er nicht nennt. Die
Invariante „kein Anteil ausserhalb 0…10.000" in T30 Prüfung 2 hält jetzt per Konstruktion
und bleibt trotzdem als Wächter stehen.

**Befund 4, Profil → Aktionen nicht definiert — behoben; die Hälfte davon war meine.** Das
Vorratsverfahren gehört `spiel.md`; **T43** nimmt es auf, sagt, gegen welche
Zulässigkeitsliste es prüft (die aus T32, einmal je Runde gebildet), und gibt ihm eine
Invariante: nach je fünf Runden Vorrat wieder null und genau `3·ai` Steckplätze je Art. Ich
habe das für alle 126 Profile durchgerechnet; die Probe, die `spiel.md` selbst angibt, fällt
zeichengleich heraus. **T41** schliesst den Teil, den der Befund ausdrücklich mir zuschrieb:
wie das Profil die 60 Kandidatenbündel des Suchbots einschränkt — drei Ziehungen je
Kandidat entlang der Artenfolge, feste 60, keine Verwerfungsschleife, kein gezählter
Produktraum. Damit bleibt der Preis bei `1 + 60` Weltschritten je Runde, und die Rechnung in
Abschnitt 10 trägt.

**Befund 5, Maß 4 ohne Abnahmeregel — behoben.** Meine Rückfrage aus Abschnitt 12 ist
beantwortet: 16 Prüfgegenstände, Toleranz 2, nur die freien Reihen entscheiden, Handelsblock
nach meinem Vorschlag am Median. T37 trägt die Regel, Abschnitt 12 nennt sie nicht mehr als
offen. **T42** schreibt die drei Fehlermaße als Rechenvorschrift aus, weil `spiel.md` sie
beziffert und nicht rechnet — einschliesslich zweier Fälle, die dort nicht vorkommen und
den Lauf sonst abbrechen liessen: `soll = 0` bei einem bilateralen Strom, und eine
Neubasierung nach T8 innerhalb einer Ratenreihe.

**Befund 6, `landespreis` nicht definiert — behoben, und zwar so, dass die zweite Lesart
nicht mehr formulierbar ist.** `landespreis` ist der Sektorpreis der Vorrunde. **T39** gibt
ihm einen Ort statt eines Feldes: `lies_alt(adresse)` gegen den Zustand der Vorrunde, und
`lies_neu` auf eine in dieser Runde noch ungeschriebene Adresse ist ein harter Fehler statt
eines stillen Rückgriffs. T28 belegt damit die Monotonie der Überschussfunktion, statt sie
zu behaupten. T15 bekommt keine neue Zeile — ein Feld wäre eine zweite Kopie derselben Zahl.

**Befund 7, Zusammenfassung über die 50 Startwerte fehlt — behoben.** Die 50 und die
Zusammenfassungsregel stehen jetzt in `spiel.md`; Abschnitt 10 rechnet nur noch, was dort
festgelegt ist, und weist die Teilsummen aus. Die Gesamtzahl setzt keine Vorgabe mehr
voraus, die dieses Dokument selbst macht.

**Befund 8, sechs Profile ohne Familienaktion — behoben.** T36 macht den Strategiekern
vierwertig: `ohne` statt der Klasse 1 über den Gleichstandsbrecher. Die sechs Profile laufen
mit, werden berichtet und gehen in keine Abnahmehälfte von Maß 2 ein; klassifiziert sind
120. Dazu zwei nachgerechnete Anker für den Test: In der lexikographischen, nullbasierten
Profilliste sind es genau die Kennungen **0 bis 5**, und das Referenzprofil trägt die
Kennung **76**.

**Befund 9, Schwelle zwischen zwei erreichbaren Werten — behoben.** T30 Prüfung 7 nennt
für Maß 3 **0,4** statt 0,5; die übrigen beiden Schwellen sind unverändert und stehen
jetzt ausgeschrieben in derselben Zeile.

**Befund 10, Ergebnisskala nicht streng geordnet — behoben, und schärfer geprüft als
verlangt.** T34 nennt den Bereich `1.000 … R × 1.000 + 30.000`, bei R = 24 also
1.000 … 54.000. Geprüft wird nicht der Bereich, sondern die Zugehörigkeit zu **einem der
drei Bänder** — die Lücken dazwischen sind unerreichbar, ein Wert dort ist ein Rechenfehler.
Das kostet zwei Vergleiche und folgt ohne Auslegung aus der Tabelle in `spiel.md`.

**Befund 11, Kostenformel eine Runde zu kurz — behoben.** `spiel.md` hat die dahinterstehende
Frage entschieden (Maß 1 misst die Entscheidung der Runde `t`, Kosten `R + 1 − t`).
Abschnitt 10 rechnet `Σ(R+1−t) = 300`, also `30 × 300 + 24 = 9.024` je Startwert und
451.200 für fünfzig — in diesem Lauf gerechnet, nicht übernommen.

**Befund 12, BACI-Konkordanz fehlt — behoben.** T23 Punkt 9 nimmt die Tabelle 01–24 → Sektor
1, 25–97 → Sektor 2 als **Manifesteintrag** auf, ausdrücklich nicht als Code: Dieselbe
Tabelle erzeugt `H` für den `durchgriff`, die Handelsstartmatrix und die 40 Sollströme, und
genau deshalb ist ihr Zuordnungsfehler für den Rückvergleich folgenlos. Eine zweite Kopie
wäre die Gelegenheit, sie auseinanderlaufen zu lassen. Punkt 10 kommt hinzu, weil er an
derselben Stelle hing: wie die Restwelt als Rest entsteht und warum es je gerichtetem Paar
genau eine Zahl gibt — sonst hängt die Invariante „Summe aller Handelsbilanzen = 0" an der
Datenqualität statt an der Bauart.
