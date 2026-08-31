---
typ: technik
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-08-31
stack: Rust (stabile Kette, Edition 2021); Kern ohne jede Fremdabhängigkeit und ohne Gleitkommatyp; Oberfläche egui/eframe (MIT OR Apache-2.0)
determinismus: i64-Festkomma mit deklarierter Skala je Größenklasse, feste Iterationsreihenfolge über Indexlisten, ein Wurzelstartwert mit abgeleiteten Strömen, Weltschritt ohne jede Ziehung
zustand: fester, allokationsfreier Wert, rund 300 i64 (2,4 kB), Prüfsumme über kanonische Byteform
speicherstand: Startwert plus Aktionsfolge plus Prüfsumme -- nicht der Zustand
kalibrierung: alle Zahlenwerte in einer Parameterdatei ausserhalb des Codes, mitgehasht
tick_planwert: 10 Mikrosekunden je Weltschritt (Bandbreite 5 bis 30), vom Prüfstand zu messen
nachtlauf: rund 20 Mio Weltschritte, 3,4 Minuten auf einem Kern beim Planwert, unter 20 Minuten im ungünstigen Fall
---

# Der Kern ist eine reine Ganzzahlfunktion ohne Ziehung -- damit ist Determinismus keine Disziplin, sondern eine Eigenschaft des Typsystems.

Die Vorgaben sind mit **T1** bis **T31** durchnummeriert. Der Builder weicht von keiner ab,
ohne dass ein ADR sie aufhebt; der Prüfer zitiert die Nummer, statt sie zu umschreiben.

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
kostet rund 20 Millionen Weltschritte je Nacht — in einer übersetzten Sprache sind das
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
| Volkswirtschaftliche Beträge (BIP, Wertschöpfung, Kapitalstock, Handelsstrom) | Tausend USD zu konstanten Preisen des Basisjahrs | 21.000.000.000 = 21 Bio USD | reichlich |
| Raten (Zins, Inflation, Zoll, Haushaltssaldo, Schuldenquote) | Basispunkte (1 bp = 0,01 %) | 250 = 2,50 % | ±2 Mio % |
| Anteile (Sektoranteil, Marktanteil, Einfluss, Zustimmung) | Zehntausendstel | 10.000 = 100 % | 0 bis 10.000 |
| Preise und Preisniveaus | Index, Startjahr = 10.000 | 12.500 = +25 % | siehe T8 |
| Wechselkurs | Index gegen USD, Startjahr = 10.000 | 8.000 = Aufwertung um 25 % | siehe T8 |
| Ergebnis einer Partie | Milli-Runden | 27.000 = Runde 27,0 | siehe Abschnitt 9 |

Einfluss und Zustimmung erscheinen dem Spieler als 0 bis 100 (so nennt sie `spiel.md`);
gespeichert sind sie in Zehntausendsteln, damit die Gegenkräfte unterhalb eines
sichtbaren Punktes noch rechnen können. Die Umrechnung findet in der Sicht statt.

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

**T8 — Preisniveau und Wechselkurs werden geführt und neu basiert.** Brasilien hat zwischen
1980 und 1994 rund zwölf Nullen gestrichen; ein Index in Zehntausendsteln erreicht dort
Größenordnungen, in denen ein prozentualer Fehler nichts mehr aussagt. Deshalb: Übersteigt
der Preisindex eines Landes das 100.000-fache seines Startwerts, werden Index, Wechselkurs
und alle nominalen Größen dieses Landes durch 1.000 geteilt und der Zähler `basiswechsel`
erhöht — dasselbe, was das Land historisch getan hat. **Und der Rückvergleich läuft für
Preise und Wechselkurse auf Jahresänderungsraten in Basispunkten, nicht auf Niveaus**
(T23). Wird als Startjahrgang 2000 gewählt, greift die Neubasierung nie; sie kostet dann
nichts.

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

Jeder Strom wird **abgeleitet**, nicht fortgeschrieben:
`strom = splitmix64(wurzelstartwert, zweck_id, runde, index)`. Ein fortlaufender Strom
hätte die Eigenschaft, dass eine einzige neue Ziehung irgendwo alle späteren Ziehungen
verschiebt und damit den ganzen Regressionsbestand rot macht, ohne dass sich etwas
Inhaltliches geändert hätte. Das ist die Vorgabe, an der später der Unterschied zwischen
„verbessern" und „verändern" hängt.

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

**T15 — `Zustand` ist ein Wert fester Größe ohne Speicheranforderung.** Feste Felder, feste
Arrays, keine `Vec`, kein `String`, kein `Option<Box<…>>`. `Clone` ist damit ein
Speicherumzug von rund 2,4 kB (etwa 200 Nanosekunden) — das ist die Voraussetzung dafür,
dass der Prüfstand Millionen von Nachspielen aus Zwischenständen starten kann.

Fünf Länder (USA, China, Deutschland, Brasilien, Restwelt; die Restwelt ohne
Politikmodell), drei Sektoren, davon zwei handelbar, vier Politikinstrumente.

| Behälter | Felder | Anzahl |
|---|---|---|
| `Land` je Sektor | Wertschöpfung, Kapitalstock, Beschäftigung, Sektorpreis | 4 × 3 = 12 |
| `Land` gesamt | Bevölkerung, Erwerbstätige, Produktivität, Preisniveau, Inflation, Leitzins, Wechselkurs, Staatsschuld, Haushaltssaldo, Zustimmung, Aufsichtszähler, Einfluss, Basiswechsel | 13 |
| `Instrument` je Land | Stand, anliegender Druck, Gegendruck, Restverzögerung | 4 × 4 = 16 |
| je Land zusammen | | 41 |
| vier Länder plus Restwelt (ohne Instrumente, ohne Zustimmung) | | 4 × 41 + 20 = 184 |
| Handel | Land × Gegenüber × handelbarer Sektor | 5 × 4 × 2 = 40 |
| Weltpreise | je handelbarem Sektor | 2 |
| Nachahmerzähler | Land × Sektor | 4 × 3 = 12 |
| `Fonds` | Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Überrendite der letzten drei Runden, Marktanteil | 8 |
| Fondspositionen | feste Steckplätze: 12 Land×Sektor, 4 Währung, 4 Anleihe, Größe vorzeichenbehaftet in Stufen | 20 |
| Beteiligungen | Land × Sektor, Anteil und Restdauer eines Ausstiegs | 24 |
| Runde, Jahrgangskennung, Parametersatz-Prüfsumme, Mandatsstand | | 4 |
| **Summe** | | **rund 294 i64** |

**T16 — Positionen sind Steckplätze, keine Liste.** Es gibt genau zwanzig mögliche
Positionen; eine Position ist eine vorzeichenbehaftete Stufenzahl auf einem festen Platz,
null heisst „keine". Damit entfällt jede Frage nach Höchstzahl, Reihenfolge und
Zusammenlegung, und der Zustand bleibt vergleichbar (T12).

**T17 — Jede Größe hat eine stabile Adresse.** `land.DE.sektor.2.preis`,
`land.BR.instrument.zoll.stand`, `fonds.position.CN.1`, `handel.DE.CN.1`. Diese Adressen
erscheinen im Protokoll, in der Kette, in den Testvorlagen und in der Oberfläche. Sie sind
Teil der Schnittstellenversion: Wer eine umbenennt, macht den Regressionsbestand
ungültig und braucht einen ADR.

**T18 — Die Kette wird erzeugt, nicht rekonstruiert.** Die Felder von `Zustand` sind
ausserhalb des Kerns nicht schreibbar; innerhalb schreibt niemand direkt, sondern über
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

Das ist die wichtigste Strukturentscheidung des Produkts: Die Kette ist zugleich das
verkaufte Merkmal („the consequences of choices often feel intangible"), die Antwort auf
G8 und der Gegenstand der Regressionsprüfung. Wird sie nachträglich aus zwei Zuständen
erschlossen, ist sie geraten; wird sie beim Schreiben mitgeführt, ist sie wahr.

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

- **`uebersicht`** — eine Zeile je Land, eine je Fonds. Format wie in der Idee:
  `DE | BIP 3.412 | Zins 250bp | Zoll 380bp | Haushalt -210bp | Fondsanteil 420 | Einfluss 1.700`
- **`detail <adresse>`** — ein Objekt vollständig, für **jede** adressierbare Einheit nach
  T17, nicht nur für Länder: `land.US`, `fonds`, `land.BR.instrument.zoll`,
  `land.CN.sektor.1`.
- **`diff <von> <bis>`** — je geänderter Größe alt, neu, Änderung **und die Ursachenkette
  aus T18**, rückwärts aufgelöst bis zur auslösenden Aktion oder Gegenkraft, mit
  Verzögerung und Beitrag je Glied. Der Unterschied zweier Zustände sagt *was*, die Kette
  sagt *warum*; ausgegeben wird beides, massgeblich ist die Kette.

## 6. Maschinenschnittstelle und Partieformat

**T21 — Ein Befehl je Zeile, eine JSON-Antwort je Zeile, über Standardein- und -ausgabe.**
Kein Netzdienst, kein Anschluss, keine Zugangsdaten — damit auch keine Berührung mit
Hausregel 2. Befehle: `neu {jahrgang, startwert}`, `zustand {ebene, adresse}`,
`aktionen` (die zulässigen dieser Runde, als Liste mit Kennungen), `setze {aktionen: […]}`,
`runde`, `kette {von, bis}`, `speichern {pfad}`, `laden {pfad}`, `pruefsumme`.
Jede Antwort trägt `schema_version`. Eine mitgeschriebene Sitzung ist damit von selbst
eine Testvorlage.

**T22 — Ein Speicherstand ist Startwert plus Aktionsfolge plus Prüfsumme, nicht der
Zustand.** Datei: `{schema_version, jahrgang_id, daten_pruefsumme, parameter_pruefsumme,
startwert, aktionen: [[runde, aktion…]], end_pruefsumme}`. Beim Laden wird die Partie
nachgerechnet und die Prüfsumme verglichen; weicht sie ab, meldet das Programm einen
Determinismusbruch, statt weiterzuspielen. Drei Gewinne auf einmal: Der Käufer bemerkt
einen Determinismusfehler zuerst, der Regressionsbestand **ist** der Speicherordner, und
eine Datei bleibt unter zwei Kilobyte. Kosten: 40 Weltschritte beim Laden, also 0,4
Millisekunden.

## 7. Datenschicht

**T23 — Der Jahrgang ist ein Erzeugnis, kein Programmteil.** `werkzeuge/aufbereitung`
liest die eingefrorenen Rohdateien und schreibt `jahrgang-<jahr>.bin`,
`sollreihen-<jahr>.bin` und ein `manifest.toml` mit SHA-256 je Ein- und Ausgabe, Quelle,
Lizenz und Abrufdatum. Der Bau des Spiels lädt **nichts** aus dem Netz. Der Jahrgang
enthält:

1. **Startwerte** für jede Zustandsgröße mit Datenanker,
2. **Sollreihen** für die 31 Reihen aus `spiel.md` plus den Handelsblock,
3. **historische Politikpfade** für Leitzins, Zollniveau und Haushaltssaldo (der vierte
   Hebel, Finanzmarktregulierung, hat keinen Anker und steht im Rückvergleich fest auf
   seinem Startwert — was das Orakel für dieses Instrument blind macht, und das gehört in
   jeden Befund),
4. **exogene Pfade** nach T25,
5. **abgeleitete Kennzahlen**: die mittlere absolute Jahresänderung je Land als
   Schwankungsbreite für den Innerjahresausschlag. Mittlere absolute Abweichung, nicht
   Standardabweichung — die bräuchte eine Wurzel und damit Gleitkomma (T4).

Größenordnung: 5 Gebiete × 41 Jahre × rund 30 Reihen × 8 Byte ≈ 50 kB, Handel 13 kB. Der
ausgelieferte Datenteil bleibt deutlich unter einem Megabyte.

**T24 — Lücken werden gekennzeichnet, nicht stillschweigend gefüllt.** Je Reihe, Land und
Jahr ein Flag `gefuellt`. Die Füllregel steht im Manifest (Fortschreibung des letzten
bekannten Werts, lineare Ganzzahlinterpolation zwischen Stützstellen), und **gefüllte
Jahre zählen im Fehlermaß des Rückvergleichs nicht mit**, sondern werden gezählt und
ausgewiesen. Eine Sollreihe, die zu mehr als einem Fünftel gefüllt ist, gilt als nicht
belastbar und wird im Befund als solche markiert.

**T25 — Die Grenze zwischen exogen und endogen ist die Grenze der Aussagekraft des
Orakels, und deshalb ist sie eng gezogen.**

| Größe | im Spiel | Begründung |
|---|---|---|
| Bevölkerung, Erwerbstätige | **exogen**, Pfad aus Daten | Demografie ist nach `spiel.md` ausdrücklich keine Spielgröße |
| Restwelt-Nachfrageniveau | **exogen**, Pfad aus Daten | Randbedingung des Modells; der Rückvergleich prüft die Restwelt folglich nicht |
| Produktivität | **endogen**, nur Startwert aus PWT | Würde sie jährlich aus den Daten gelesen, wäre das BIP im Rückvergleich eine Wiedergabe der Sollreihe und der Test prüfte sich selbst |
| Preise, Zinswirkung, Handel, Staatsfinanzen, Zustimmung | **endogen** | das ist die Maschine, die geprüft werden soll |
| Politikinstrumente | im Spiel endogen, **im Rückvergleich auf die historischen Pfade gesetzt** | so verlangt es `spiel.md` |

**T26 — Ein gesperrter Datenanker ändert das Programm nicht, nur das Manifest.** Fällt der
aggregierte Zollsatz unter die Drittanbieter-Ausnahme der Weltbank (die schwerste offene
Frage aus `spiel.md`), enthält der Jahrgang keinen Zollpfad; der Rückvergleich läuft dann
mit konstantem Zoll und weist das aus. Dasselbe für die sektorale Beschäftigung: fehlt sie,
wird sie nach Wertschöpfungsanteil aufgeteilt und als Modellkonstrukt gekennzeichnet.
Lizenzrisiko ist damit eine Eigenschaft der Datenschicht, nie eine des Kerns.

### Die Reihenliste, die `spiel.md` vom Architekten verlangt

Damit der Spielentwerfer je Reihe das Feld „Source" prüfen kann. Quelle nach `daten.md`;
„Verdacht" heisst Drittanbieter-Ausnahme der Weltbank.

| Nr | Größe | Dimension | Modelleinheit | Quelle | Rolle | Verdacht |
|---:|---|---|---|---|---|---|
| 1 | BIP, konstante Preise | 4 Länder + RW | Tsd USD | WDI / PWT | Start + Soll | nein |
| 2 | Wertschöpfungsanteil je Sektor | 4 × 3 | Zehntausendstel | WDI | Start + Soll (12) | nein |
| 3 | Kapitalstock | 4 + RW | Tsd USD | PWT | Start | nein |
| 4 | Produktivität (TFP) | 4 + RW | Index | PWT | nur Start (T25) | nein |
| 5 | Bevölkerung | 4 + RW | Personen | WDI / PWT | exogener Pfad | nein |
| 6 | Erwerbstätige | 4 + RW | Personen | WDI / PWT | exogener Pfad | nein |
| 7 | Beschäftigung je Sektor | 4 × 3 | Personen | WDI (ILO) | Start | **ja** |
| 8 | Verbraucherpreise | 4 | bp Jahresrate | WDI / IWF IFS | Start + Soll (4) | **ja** (IWF-gestützt) |
| 9 | Leitzins | 4 | bp | IWF IFS | Start + Soll + Politikpfad | nein |
| 10 | Wechselkurs gegen USD | 3 | Index | IWF IFS / WDI | Start + Soll (3) | prüfen |
| 11 | Staatsschuldenquote | 4 | bp | IWF WEO | Start + Soll (4) | nein |
| 12 | Haushaltssaldo | 4 | bp | IWF WEO | Start + Politikpfad | nein |
| 13 | Zollniveau, aggregiert | 4 | bp | WDI (aus WITS) | Start + Politikpfad | **ja, entscheidend** |
| 14 | Bilaterale Ströme | 5 × 4 × 2 | Tsd USD | CEPII BACI | Start + Sollblock | nein |
| 15 | Preisniveau im Ländervergleich | 4 + RW | Index | PWT | Start (Numéraire) | nein |
| 16 | Sektorpreise | 4 × 3 | Index | **keine** | endogen, kein Soll | — |
| 17 | Zustimmung | 4 | Zehntausendstel | **keine** | aus Parameterdatei | — |
| 18 | Marktrendite als Vergleichsmaßstab | — | bp | **keine unter freier Lizenz** | siehe unten | — |

Die 31 Sollreihen sind die Zeilen 1, 2, 8, 9, 10, 11 (4+12+4+4+3+4); der Handelsblock aus
Zeile 14 kommt als eigener Block hinzu — genau die Aufteilung aus `spiel.md`.

**Zeile 18 ist ein Fund und keine Formalie.** `spiel.md` lässt die Anleger die Rendite des
Fonds mit einer Marktrendite vergleichen, „die aus den echten Daten kommt". Unter den vier
freigegebenen Quellen gibt es **keinen Aktienindex** — die Indexreihen der Weltbank
stammen von S&P und fallen mit hoher Wahrscheinlichkeit unter die Drittanbieter-Ausnahme.
Der architektonische Ausweg, der die Absicht des Entwurfs trägt, ohne eine fünfte Quelle
zu erfinden: **Die Marktrendite ist die wertgewichtete Rendite aller im Modell handelbaren
Körbe und Anleihen.** Im Startjahrgang sind deren Werte aus echten Daten gesetzt, also
kommt der Maßstab mittelbar doch aus den Daten — und er ist genau der Markt, in dem der
Fonds steht, was die Kraft von Gegenkraft 3 eher stärkt als schwächt. Das ist eine
Auslegung, keine Änderung; sie gehört dem Spielentwerfer vorgelegt (Abschnitt 11).

**T27 — Die Kalibrierdatei liegt ausserhalb des Codes.** Sämtliche Zahlenwerte, die
`spiel.md` ausdrücklich der Kalibrierung überlässt — Mandatsschwelle, drei
Aufsichtsschwellen, Nachahmergeschwindigkeit, Stufenweite einer Position, Lobbykosten,
Verzögerungen, Elastizitäten — stehen in `parameter.toml`, werden als Dezimalzeichenketten
in skalierte Ganzzahlen gelesen (T4) und in eine Struktur mit benannten Feldern gefüllt,
nie über eine Schleife über Schlüssel (T9). Die Prüfsumme des Parametersatzes steht im
Zustand und in jedem Speicherstand. Damit ist Kalibrieren eine Datenänderung, die kein
Übersetzen braucht — genau die Bauart, die `spiel.md` an Democracy 4 belegt hat, und die
Voraussetzung dafür, dass ein Agent über Nacht tausend Parametersätze durchsucht.

## 8. Markträumung, die einzige Schleife im Modell

**T28 — Feste Iterationszahl statt Konvergenzabbruch.** Der Weltpreis je handelbarem
Sektor wird durch **genau 40 Halbierungsschritte** über einem festen Preisintervall
gesucht, nicht bis zu einer Schranke. Ein Abbruch nach Genauigkeit macht die Laufzeit vom
Zustand abhängig und die Zahl der Schritte zu einem stillen Teil des Ergebnisses; eine
feste Zahl macht beides messbar und begrenzt. 40 Halbierungen über einem Intervall von
sechs Größenordnungen lösen bis unter ein Zehntausendstel auf — mehr Auflösung, als die
Preisskala aus T5 überhaupt darstellt.

**T29 — Ganzzahlige Potenzen und Wurzeln über Newton auf `i128`.** Wo die
Produktionsfunktion einen Exponenten wie 1/3 braucht, wird `wurzel(x, n)` mit fester
Schrittzahl verwendet; Exponenten sind auf Brüche kleiner ganzer Zahlen beschränkt. Keine
Reihenentwicklung, kein Logarithmus, keine Tabelleninterpolation.

## 9. Test- und Prüfstandsaufbau

**T30 — Sieben Prüfungen, ein Aufruf.** `nacht` läuft der Reihe nach und bricht mit einem
Rückgabewert ungleich null ab, sobald eine Schwelle aus `spiel.md` gerissen ist. Was nicht
in einem Aufruf läuft, läuft nachts nicht.

| # | Prüfung | Gegenstand | Verantwortlich |
|---:|---|---|---|
| 1 | Einheitstests je Wirkungskette | jeder Pfeil aus `spiel.md` einzeln, auf einem Minimalzustand: Zoll rauf → Einfuhr runter → Preis rauf → Realeinkommen runter → Zustimmung runter | Testentwickler |
| 2 | Invariantentest | Summe aller Handelsbilanzen einschliesslich Restwelt = 0; Staatsschuld(t) = Staatsschuld(t-1) − Saldo; Fondsvermögen = Kasse + bewertete Positionen − Hebel; alle Anteile summieren auf 10.000 | Testentwickler |
| 3 | Determinismustest | derselbe Startwert und dieselbe Aktionsfolge ergeben dieselbe Prüfsumme — zweimal im Lauf, über Speichern und Laden hinweg, und auf jeder Zielplattform verglichen | Testentwickler |
| 4 | Regressionsbestand | gespeicherte Partien nach T22 rechnen bitgleich nach; zusätzlich eine Prüfsumme über die Kette, damit auch eine geänderte *Begründung* auffällt | Testentwickler |
| 5 | Bruchlauf | 10.000 Partien mit dem Zufallsbot: kein Absturz, kein Überlauf, keine Invariantenverletzung, kein Kettenüberlauf | Bruchtester |
| 6 | Die drei Maße | Entscheidungsdichte, Strategievielfalt, Optimumsverschiebung nach den Formeln in `spiel.md`, gegen die dortigen Schwellen 0,4 / 3 Profile bei höchstens 25 % Abstand / 0,5 | Selbstspieler |
| 7 | Rückvergleich | 31 Sollreihen plus Handelsblock, mittlerer absoluter prozentualer Fehler (Schwelle 20 %) und Richtungstreue (Schwelle 0,6) | Rückvergleicher |

**T31 — Der Regressionsbestand wird nie stillschweigend neu erzeugt.** Ein bewusst
geänderter Modellwert macht die Prüfungen 4 rot — das ist der Zweck. Die Erneuerung läuft
über einen eigenen Aufruf, der einen **Abweichungsbericht** schreibt: welche Partie,
welche Größe, alter und neuer Wert, welche Kettenglieder sich geändert haben. Dieser
Bericht ist der Gegenstand der Prüfung, nicht der neue Bestand.

**Drei Bots, und die Vorgaben, die sie deterministisch machen:**

- **Zufallsbot(startwert)** — zulässige Aktionen gleichverteilt. Für Prüfung 5.
- **Heuristikbot(profil)** — verteilt das Rundenbudget nach dem Aktionsprofil aus
  `spiel.md` (Fünftelrasterung über die fünf Aktionsarten) und wählt innerhalb einer Art
  nach einer festen, dokumentierten Rangfolge. Keine Nachspiele, also billig. **Er ist die
  „feste Folgepolitik" der Entscheidungsdichte.**
- **Suchbot(profil, kandidaten=60, tiefe=1)** — bewertet Kandidatenbündel durch ein
  Nachspiel mit dem Heuristikbot als Fortsetzung. Gleichstand wird **nach Aktionskennung**
  gebrochen, nie nach Auffindereihenfolge.

**Ergebnisgröße einer Partie**, als genaue Lesart von `spiel.md` („die Rundenzahl bis zur
Mandatserfüllung, oder bei Nichterfüllung 40 plus der Fehlbetrag"): ein `i64` in
Milli-Runden. Erfüllt = `runde × 1.000`. Nicht erfüllt =
`40.000 + min(60.000, fehlbetrag)`, wobei der Fehlbetrag die Summe aus fehlendem Vermögen
und fehlendem Einfluss in Promille der jeweiligen Schwelle ist. Die Deckelung hält die
Skala vergleichbar; ohne sie zöge eine einzige Bankrottpartie jeden Median.

**Parallelität ohne Preisgabe des Determinismus:** Jedes Nachspiel ist eine reine Funktion
von (Jahrgang, Parametersatz, Startwert, Politik, Runde, Stichprobenindex); der abgeleitete
Zufallsstartwert folgt aus genau diesem Tupel (T11). Ergebnisse werden in ein vorab
bemessenes Feld **an ihrem Index** abgelegt, nie angehängt. Jede Zusammenfassung läuft
über das sortierte Feld; der Median bei gerader Anzahl ist der kleinere der beiden
mittleren Werte. Damit liefert der Prüfstand mit einem Kern und mit zweiunddreissig
dasselbe Ergebnis.

**Berichtspflicht:** Jeder Befund trägt `ticks_gesamt`, `sekunden` und `ticks_je_sekunde`.
Die Schätzung des nächsten Abschnitts wird damit binnen einer Nacht durch eine Messung
ersetzt — und bleibt gemessen.

## 10. Was das Modell an Rechenzeit kostet

Ein Weltschritt umfasst geschätzt 7.500 elementare Ganzzahloperationen; den Löwenanteil
tragen die Markträumung (2 Sektoren × 40 Halbierungen, T28) und das Mitschreiben der
Kette (T18). Teuer sind darin die `i128`-Divisionen aus T6. **Planwert: 10 Mikrosekunden
je Schritt**, Bandbreite 5 bis 30. Die Spalte „ungünstig" rechnet mit 50 Mikrosekunden,
also dem Fünffachen des Planwerts — eine Reserve, keine Erwartung.

| Lauf | Weltschritte | bei 10 µs | ungünstig (50 µs) |
|---|---:|---:|---:|
| eine Partie, Heuristikbot | 40 | 0,4 ms | 2 ms |
| eine Partie, Suchbot (60 Kandidaten, 1 Zug voraus) | 2.440 | 24 ms | 122 ms |
| **1.000 Partien, Heuristikbot** | 40.000 | **0,4 s** | 2 s |
| **1.000 Partien, Suchbot** | 2.440.000 | **24 s** | 2,0 min |
| Entscheidungsdichte, K=30, ein Startwert | 23.400 | 0,23 s | 1,2 s |
| Entscheidungsdichte, 50 Startwerte | 1.170.000 | 12 s | 59 s |
| Strategievielfalt, 126 Profile × 20 Startwerte | 6.148.800 | 61 s | 5,1 min |
| Optimumsverschiebung, zwei Fenster | 12.297.600 | 2,1 min | 10,2 min |
| Bruchlauf, 10.000 Zufallspartien | 400.000 | 4 s | 20 s |
| Rückvergleich, ein Durchlauf | 40 | 0,4 ms | 2 ms |
| Regressionsbestand, 1.000 Partien | 40.000 | 0,4 s | 2 s |
| **Nachtlauf gesamt** | **rund 20 Mio** | **3,4 min** | **17 min** |

Alles auf **einem** Kern. Mit acht Kernen (T30, `rayon`) fällt der Nachtlauf unter eine
Minute beim Planwert und unter drei Minuten im ungünstigen Fall.

**Die Antwort auf die Frage, die dieser Abschnitt beantworten soll: Ja, der Prüfstand kann
täglich laufen — und stündlich.** Der Engpass ist nicht die Rechenzeit, sondern das
Tokenbudget der Agenten, die die Befunde lesen. Eine Kalibrierschleife über tausend
Parametersätze (T27) kostet beim Planwert rund zwei Stunden auf acht Kernen und ist damit
ebenfalls eine Nachtaufgabe.

**Die Gegenrechnung, die die Stackwahl trägt:** Derselbe Weltschritt kostet in Python
zwischen 0,75 und 3 Millisekunden, also das 75- bis 300-fache. Der Nachtlauf läge bei
4 bis 17 Stunden auf einem Kern. Er wäre damit nicht täglich, sondern gelegentlich — und
eine Kalibrierschleife wäre gar nicht möglich. Das ist die Zahl, an der die Wahl aus T1
hängt, und sie ist der einzige Grund, den Autorenaufwand von Rust in Kauf zu nehmen.

**Beim Käufer** kostet eine Runde einen Weltschritt: 10 Mikrosekunden. Der Speicherbedarf
sind rund 2,4 kB Zustand, unter 1 MB Jahrgang und wenige hundert kB Kettenverlauf. Das
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

## 12. Was ich nicht entschieden habe

- **Das Startjahr.** `spiel.md` lässt 1980 gegen 2000 offen und will die Reihenlängen
  gemessen haben. Die Architektur macht die Entscheidung billig: Der Jahrgang ist ein
  Erzeugnis (T23), beide sind gleichzeitig lieferbar, und keine Zeile Code hängt daran.
  Entschieden wird sie nach der Vermessung durch den Datenbauer.
- **Der Bruch bei Deutschland 1999.** Architektonisch behandelt als Datenfrage: Die
  Sollreihe des Wechselkurses wird über den unwiderruflichen Umrechnungskurs zu einer
  durchgehenden Indexreihe verbunden, und das Instrument Leitzins trägt im Jahrgang ein
  Feld `exogen_ab`. Damit liest das Fehlermaß den Bruch nicht als Modellfehler. Ob der
  gewählte Umgang dem Entwurf entspricht, entscheidet der Spielentwerfer.
- **Die Marktrendite (Reihe 18).** Meine Auslegung steht in Abschnitt 7 und ist die
  einzige, die ohne eine fünfte Datenquelle auskommt. Sie berührt Gegenkraft 3 und gehört
  deshalb dem Spielentwerfer vorgelegt, nicht vom Builder entschieden.
- **Die Zahlenwerte sämtlicher Schwellen und Elastizitäten.** Sie stehen nach T27 in der
  Parameterdatei und werden vom Selbstspieler gesucht, nicht von mir gesetzt.
- **Die konkrete Rangfolge im Heuristikbot.** Sie ist eine Modellierungsfrage des
  Selbstspielers; die Architektur verlangt nur, dass sie fest, dokumentiert und
  gleichstandsfrei ist.

## 13. Hinweis für den Projektmanager

Der Kastenschnitt aus T13 ist zugleich der Kollisionsschnitt für Arbeitspakete: Zwei
gleichzeitig offene Pakete dürfen sich nicht im selben Kasten treffen. Die natürliche
Reihenfolge ist `kern` (Zustand, Festkomma, Zufall, Prüfsumme) → `daten` und
`schnittstelle` parallel → `konsole` → Tests und `pruefstand` → `oberflaeche`. Der Jahrgang
(`werkzeuge/aufbereitung`) kann von Beginn an parallel laufen, weil er nur gegen T5, T23
bis T26 gebaut wird und nichts vom Kern braucht.
