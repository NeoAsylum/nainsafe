---
id: 0009-parameterdatei-schluessel
rolle: datenbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Jeder in T27 und T51 genannte Schlüssel steht in der Datei, mit Skalenklasse nach T5, Wertebereich, Herkunft der Schranke und einem Startwert innerhalb der Schranken; kein Schlüssel ohne Klasse, keine Klasse ohne Schlüssel im Text.
---

# `parameter.toml` — die Schlüssel, nicht die Zahlen

T27: „Die Kalibrierdatei liegt ausserhalb des Codes, und jeder Schlüssel trägt eine
Skalenklasse." Ein Parameterschlüssel ohne Klasse ist derselbe Fehler wie eine Adresse
ohne Klasse — und es ist derselbe Fehler, an dem Befund 2 der Runde 6 hing.

**Die Zahlen sind nicht dein Auftrag.** `spiel.md` sagt es und `technik.md` Abschnitt 12
wiederholt es: Die Werte werden vom Selbstspieler *gesucht*, nicht entworfen. Was du
lieferst, ist die Form — jeder Schlüssel, seine Einheit, seine Schranken und die Stelle,
an der die Schranke steht. Der Startwert ist ein Platzhalter innerhalb der Schranken und
als solcher gekennzeichnet.

Vorher lesen: `technik.md` T5, T27, T50, T51, T47.

## Was hineingehört

1. **Die elf Schlüssel aus der Tabelle in T27**, jeder mit Klasse und Bedeutung:
   `stufenweite`, `stufen_max`, `ausstiegsabschlag`, `zwangsabschlag`, `aufschlag`,
   `lobbykosten`, `beteiligungsrabatt`, `gegenlobby_satz`, `druck_max`,
   `regulierung_stufen`, sowie `schrittweite[i]`, `instrument_min[i]`,
   `instrument_max[i]` je Instrument.
2. **Die übrigen Kalibriergrößen, die T27 im Fliesstext aufzählt:** Mandatsschwelle
   (`schwelle_v`, `schwelle_e`), drei Aufsichtsschwellen, Nachahmergeschwindigkeit,
   Anlegerabzugsanteil, Startkapital, Startzustimmung, Startstand der
   Finanzmarktregulierung, Verzögerungen, Elastizitäten.
3. **Je Schlüssel die Schranke und ihre Quelle**, wo `specs/` eine nennt — nicht
   erfunden, sondern zitiert:
   - `lobbykosten ≥ 1` (T50), `1 ≤ beteiligungsrabatt ≤ 10.000` (T50),
   - `stufenweite ≥ 1` und ganzzahlig (T47), Klasse 4 und **kein Geldbetrag** (T5),
   - `aufschlag ≥ aufschlag_min` mit `aufschlag_min = 1 − min(leitzins_pfad)`
     (T51, T23 Punkt 5) — die Zahl selbst kommt aus dem Jahrgang und steht hier als
     Verweis, nicht als Wert,
   - `instrument_min[leitzins] ≥ 1 − aufschlag` (T51) — die eine Stelle des Modells, an
     der ein Kurs unendlich würde,
   - Wertebereiche der vier Instrumente aus der Tabelle in T51.
4. **Ein Kommentar je Schlüssel, der sagt, wer ihn kalibriert und woran er scheitert.**
   Für `startkapital` und `stufenweite` gehört die Bedingung aus T47 dazu: Eine Stufe
   auf dem grössten der sechzehn Startmarktwerte muss bezahlbar sein, und erreichbare
   Stufenzahlen müssen die Aufsichtsschwellen erreichen. Beides zugleich ist nicht
   garantiert; die beiden Zahlen dafür weist der Jahrgangsbau im Manifest aus.

## Abnahme

1. Jeder in T27 und T51 genannte Schlüssel steht in der Datei. Der Prüfer legt die
   beiden Tabellen daneben und zählt ab.
2. **Kein Schlüssel ohne Skalenklasse.** Das ist die Vorgabe aus T27 und der eigentliche
   Zweck des Pakets.
3. Jeder Startwert liegt innerhalb der eigenen Schranke, und jede Schranke nennt die
   Vorgabe, aus der sie stammt.
4. Die Datei ist gültiges TOML und trägt keinen Wert, der eine Kalibrierung vorwegnimmt,
   ohne als Platzhalter gekennzeichnet zu sein.

## Grenzen

- Du **entwirfst keine Zahl.** Wo du einen Platzhalter brauchst, schreib ihn hin und
  markier ihn. Ein Wert, der wie eine Kalibrierung aussieht und keine ist, kostet den
  Selbstspieler einen Lauf.
- Du **rührst den Code nicht an.** Das Einlesen in eine Struktur mit benannten Feldern
  (T27, T9) ist ein späteres Paket im Kasten `daten`.

## Rückläufe

1. — 2026-09-02, Daten-Prüfer, Abnahme 3 (Startwert innerhalb der eigenen Schranke).
2. — 2026-09-02, Daten-Prüfer, Abnahme 3 (Herkunft der Schranke). **Der nächste Rücklauf
   ist der letzte:** `baulauf.py:RUECKLAUF_MAX = 3`. Kommt dieses Paket ein drittes Mal
   zurück, plant der Runner es nicht mehr ein und meldet `FESTGEFAHREN` — dann ist nicht
   der Datenbauer das Problem, sondern das Abnahmekriterium.

## Rücklauf 2 — drei Stellen, alle in dieser Datei, zusammen fünf Zeilen

**Befund:** `befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md`,
`urteil: zurueck`, drei Befunde. **Alle drei sind dein Rücklauf**, und keiner berührt
`specs/`.

**Zuerst das Erfreuliche, weil es sagt, was du nicht noch einmal anfassen musst.** Alle
drei Punkte aus Rücklauf 1 halten, vom Prüfer nachgerechnet und nicht nachgelesen: die
strenge Ungleichung `1 > 0`, die acht Bedingungen der Gruppe (a) einzeln eingesetzt (15
Einzelvergleiche, die Zahl stimmt), `schrittweite` mit Wertebereich und Herkunft in allen
vier Tabellen, das T5-Zitat zeichengenau gegen `technik.md` Zeile 155–156. Auch Abnahme 1
und 2 sind erneut voll geprüft: 50 Schlüssel, die Summe `10+12+4+12+12` je Summand, die
Gegenrichtung, alle zehn Klassenzuweisungen der T27-Tabelle. Und `aufschlag = 51` hält
gegen den Jahrgang — der Prüfer hat T23 Punkt 5 im Wortlaut geholt und gegengeprüft, dass
unter den vier spielbaren Ländern kein tieferer Leitzins als der EZB-Einlagesatz vorkommt.

**Was zu ändern ist:**

1. **`hebelaufschlag` (Zeile 642): eine Schranke ohne Herkunft, und die Klasse trägt sie
   nicht.** Dort steht `Schranke: >= 0.` ohne jeden Verweis. `hebelaufschlag` ist
   **Klasse 3** (Raten), und T5 gibt Klasse 3 den Bereich `±2 Mio %` — symmetrisch um
   null. Aus der Klasse folgt `>= 0` gerade **nicht**. Der Prüfer hat alle elf
   `Schranke: >= 0` durchgegangen: sieben stehen blank, sechs davon sind über ihre Klasse
   gedeckt (Klasse 11 und Klasse 4 beginnen bei 0), `hebelaufschlag` ist der einzige, bei
   dem die Null nirgendwoher kommt. Die Gegenprobe an den beiden anderen
   Klasse-3-Schlüsseln fällt gegen dich aus: `aufschlag` nennt T51 und T23 Punkt 5,
   `abschreibungsrate` nennt die Schranke ausdrücklich als „Folgerung, keine Vorgabe aus
   specs/".
   **Die Herkunft steht zwei Zeilen darüber und wird nicht benutzt:** Deine eigene
   Bedeutungszeile zitiert `spiel.md` Aktion 4 — „ein Aufschlag, der mit der Sichtbarkeit
   des Fonds **steigt**". Das ist die Vorgabe. Schreib sie als Herkunft hin und kennzeichne
   sie als Folgerung, so wie du es bei `abschreibungsrate`, `druck_max` und `stufen_max`
   schon tust — oder schreib ausdrücklich hin, dass `specs/` keine nennt.
   *Warum das kein Formfehler ist:* `hebelaufschlag` kommt in keiner Prüfung von T30 vor;
   die sieben Wertebereichsschranken je Runde laufen ausschliesslich über
   Zustandsadressen. Ein Bauagent, der `>= 0` für eine Klassenschranke hält und sie beim
   Einlesen weglässt, lässt `hebelaufschlag < 0` zu — dann sinkt der Kreditzins mit
   steigender Sichtbarkeit, Kanal 4 kehrt sich um, und **nichts bricht ab**. Derselbe
   stille Ausfall wie bei `schrittweite = 0` in Rücklauf 1.
   *Und wenn du „steigt" als Herkunft nimmst, denk die Schranke zu Ende:* Ein Faktor 0
   lässt den Aufschlag gerade nicht steigen. Der Prüfer nennt `>= 1` als die Lesart, die
   dann folgt. Entscheide es und schreib die Begründung dazu — beide Wege sind zulässig,
   keiner darf unbegründet bleiben.
2. **BEFUNDE Punkt 5 Gruppe (b) sagt „vollständig" zu und ist es nicht.** Es fehlt ein
   vierter Fall derselben Bauart: `aufsicht_tempo` (Zeile 604) erhöht nach seinem eigenen
   Kommentar den Aufsichtszähler je Runde, und der ist durch `aufsicht_max` (Zeile 356)
   gekappt — das sagt deine Datei bei `aufsicht_max` selbst („Zu niedrig — der Zähler
   sättigt"). Das ist Zeichen für Zeichen dasselbe Verhältnis wie
   `nachahmer_tempo`/`nachahmer_max`, das in (b) steht: beide Klasse 11, beide erhöhen
   einen Zähler je Runde, beide haben einen `_max`-Schlüssel in dieser Datei. Kein Wert ist
   betroffen (`0 <= 3` hält); falsch ist die Vollständigkeitszusage. **Das ist derselbe
   Fehlertyp wie die Einzigartigkeitsbehauptung aus Rücklauf 1** — ein Satz im Abschnitt
   BEFUNDE wird von der nächsten Rolle als geprüfte Aussage gelesen. Trag den vierten Fall
   nach.
3. **Die Selbstprobe im Dateikopf (Zeile 116–117) liefert nicht die Zahlen, die sie belegen
   soll.** `grep -c "# PLATZHALTER"` liefert **47** statt 46, `grep -c "# FEST (T51)"`
   liefert **5** statt 4 — der überzählige Treffer ist jeweils Zeile 116 selbst, die beide
   Zeichenketten führt. Ohne das `# ` davor, also genau so, wie der Text den Aufruf
   vorschreibt, trifft zusätzlich Zeile 117: dann 48 und 6. **Die Zahlen 46 und 4 stimmen**
   (der Prüfer hat sie über die Schlüsselzeilen nachgezählt); falsch ist nur der Prüfweg,
   den deine Datei vorschreibt. Schreib die beiden Marken im Kopftext anders oder schränk
   den Aufruf auf Schlüsselzeilen ein.

**Was du weiterhin nicht anfasst.** Die fünf geparkten Klasse-4-Schlüssel (`preisstoss`,
`zustimmung_elastizitaet`, `nachahmer_wirkung`, `hebel_max`,
`innerjahresausschlag_faktor`). Der Prüfer bestätigt ausdrücklich, dass sie unangetastet
sind, und sagt dazu, dass Befund 1 **einen anderen Schlüssel, eine andere Klasse und die
andere Richtung** betrifft und der offenen Frage in `rueckstand.md` nicht vorgreift. Die
Frage ist unverändert offen.

**Ein Hinweis, der kein Befund ist** und den du nur mitnimmst, wenn du ohnehin an der
Stelle bist: Zeile 51–52 sagt zur verschärften Regel A „Betroffen ist genau ein Paar". Der
Satz hat zwei Lesarten; unter der einen ist er richtig, unter der anderen falsch (streng
geordnet sind drei Paare). Es ist der zweite Satz dieser Art an derselben Stelle — eine
eindeutige Formulierung erspart den dritten.

**Was in zwei Runden nicht nachweisbar war und nicht dein Fehler ist:** Abnahme 4 (gültiges
TOML) ist wieder nur strukturell belegt. `python3` mit `tomllib` wurde beide Male von der
Umgebung abgewiesen — dem Datenbauer wie dem Prüfer. Das ist dieselbe Bauart wie der
Compiler vor dem 2026-09-01 und gehört in den Runner, nicht in eine Rolle; steht in
`rueckstand.md` als Punkt an den Geschäftsführer. **Belaste dich nicht damit**, und
behaupte vor allem nicht, ein Parser sei gelaufen.

## Rücklauf 1 — drei Sachen in dieser Datei, eine ausserhalb

**Befund:** `befunde/pruefung-0009-parameterdatei-schluessel-2026-09-02.md`,
`urteil: zurueck`, vier Befunde. **Drei davon sind dein Rücklauf, der vierte nicht.**

**Abnahme 1, 2 und 4 halten.** Der Prüfer hat alle 50 Schlüssel gegen T27 und T51
abgezählt, die zehn Klassenzuweisungen der T27-Tabelle zeichengenau verglichen, die
Gegenrichtung geprüft (keine Klasse ohne Schlüssel) und sechs Ungleichungen nachgerechnet.
Auch deine Kreuzprobe zu den elf Parameteradressen aus T45 geht auf. Nicht bestätigt ist
nur, dass die Datei maschinell als TOML geparst wurde — dem Prüfer stand kein Parser zur
Verfügung; er hat sie strukturell nachgelesen.

**Was zu ändern ist:**

1. **`startzustimmung = 0` und `zustimmung_wechselschwelle = 0` verletzen beide ihre
   eigene Schranke.** Zeile 379–381 verlangt `startzustimmung` **über**
   `zustimmung_wechselschwelle`, Zeile 521 verlangt `zustimmung_wechselschwelle`
   **unter** `startzustimmung` — und beide stehen auf 0. `0 > 0` ist falsch, `0 < 0`
   auch. Das ist der Kern des Rücklaufs und kein Formfehler: Die Datei nennt die Folge
   selbst — in Runde 1 steht die Zustimmung aller vier spielbaren Länder auf ihrer
   Wechselschwelle, Gegenkraft 2 löst in allen vier Ländern aus, `lobbykosten_rest` und
   `regierungsdruck_rest` werden gesetzt, bevor der Fonds eine Aktion getan hat. Deine
   eigene Regel A („wo eine untere Schranke steht, ist der Platzhalter genau diese
   Schranke") gibt die Antwort: Die untere Schranke von `startzustimmung` ist der
   kleinste Wert über 0.
2. **Befund 5 der Datei behauptet eine Einzigartigkeit, die nicht besteht** (Zeile
   743–747): `aufschlag`/`instrument_min[leitzins]` sei „die einzige Stelle, an der zwei
   Platzhalter voneinander abhaengen". Nach der Datei selbst sind es mindestens sechs
   Paare — dazu `aufsicht_schwelle_3`/`aufsicht_max` (314),
   `regulierung_start`/`regulierung_stufen` (394),
   `instrument_max[regulierung]`/`regulierung_stufen` (709),
   `gegenlobby_satz`/`druck_max` (224) und das Paar aus Punkt 1 (380/521). Das ist der
   Grund, aus dem Punkt 1 unbemerkt blieb: Die Datei rechnet genau das eine Paar nach,
   das sie für das einzige hält. Der Satz steht im Abschnitt BEFUNDE und wird deshalb von
   der nächsten Rolle als geprüfte Aussage gelesen — zähl die Paare auf und rechne jedes
   nach.
3. **`schrittweite` hat in drei von vier Instrumententabellen weder Wertebereich noch
   Herkunft einer Schranke** — `[instrument.leitzins]` (656), `[instrument.zoll]` (672),
   `[instrument.haushalt]` (684), alle drei `= 1  # PLATZHALTER`. Damit ist für drei der
   50 Schlüssel nicht prüfbar, was Abnahme 3 verlangt. Praktische Folge: `schrittweite =
   0` ist nach dieser Datei zulässig, dann bewegt sich das Instrument im `spielmodus` nie
   und Aktion 3 läuft ins Leere; ein negativer Wert kehrt die Richtung jeder
   Lobbybewegung um. Nicht betroffen sind `instrument_min`/`instrument_max` von Zoll und
   Haushalt — dort nennst du T51 als Herkunft und sagst ausdrücklich, dass T51 keine Zahl
   führt. Das ist eine benannte Herkunft und genügt.

**Was ausserhalb dieses Pakets liegt und was du deshalb nicht entscheidest.** Befund 3
des Prüfers: Fünf Klasse-4-Schlüssel (`preisstoss`, `zustimmung_elastizitaet`,
`nachahmer_wirkung`, `hebel_max`, `innerjahresausschlag_faktor`) tragen `>= 0` ohne den
Deckel 10.000, den T5 für Klasse 4 nennt; bei `preisstoss` steht sogar „specs/ nennt
keine obere", und das ist nachweislich falsch. Das ist **keine Reparatur an dieser
Datei**: Es entscheidet, ob T5 Klasse 4 ihren Bereich auch für Regler trägt, und berührt
damit `specs/`. Steht in `rueckstand.md` als Frage an den Geschäftsführer. **Fass die
fünf Schlüssel nicht an**, bis die Frage beantwortet ist — sonst baust du eine Antwort
ein, die dir nicht zusteht. Deine eigene Auflösung bei `gegenlobby_satz` (Klasse 9,
Schranke `>= 0`, „wirksam begrenzt ist das **Ergebnis** durch `druck_max`") ist übrigens
genau die Unterscheidung, um die es geht; sie ist ein Argument für die Vorlage, keine
Erlaubnis, sie selbst zu treffen.

## Status

**2026-09-02, Datenbauer: `offen` → `gebaut`** (Rücklauf 1 abgearbeitet). `parameter.toml`
liegt als **Fassung 2** vor, 932 Zeilen, Kopfstand 2026-09-02. Was sich geändert hat, je
Punkt des Rücklaufs:

1. **`startzustimmung` 0 → 1.** `zustimmung_wechselschwelle` bleibt auf 0, der unteren
   Schranke ihrer Klasse; die strenge Ungleichung trägt der andere der beiden. Regel A im
   Dateikopf ist entsprechend geschärft: Bei einem streng geordneten Paar bleibt der
   Schlüssel, dessen Schranke aus der Klasse kommt, auf der Klassenschranke, und der
   andere rückt genau einen ganzzahligen Schritt weiter. Beide Kommentarblöcke (Zeilen um
   429 und 575) nennen die Ungleichung jetzt ausdrücklich als *streng* und verweisen
   aufeinander.
2. **Befund 5 der Datei ersetzt.** Statt der Einzigartigkeitsbehauptung steht dort die
   vollständige Aufzählung in vier Gruppen: **(a)** acht in dieser Datei nachrechenbare
   Bedingungen zwischen je zwei Schlüsseln, jede eingesetzt und ausgerechnet, zusammen 15
   Einzelvergleiche — das sind die fünf Paare des Prüfbefunds plus `instrument_min ≤
   instrument_max` je Instrument (4), `lobbykosten · beteiligungsrabatt ≥ 1` und
   `stufen_max · stufenweite ≤ 10.000`; **(b)** drei Stellen, an denen der eine nicht den
   anderen begrenzt, sondern dessen Ergebnis (`gegenlobby_satz`/`druck_max`,
   `nachahmer_tempo`/`nachahmer_max`, `schrittweite`/Spanne des Wertebereichs); **(c)**
   vier Kopplungen an Zahlen aus dem Jahrgang oder Manifest, hier grundsätzlich nicht
   nachrechenbar und deshalb als Auflage an den Jahrgangsbau benannt; **(d)** fünf
   gemeinsam kalibrierte Gruppen ohne Ungleichung, nur der Vollständigkeit halber. Die
   Gegenprobe: Jede Stelle der Datei, die „gekoppelt", „zusammen mit", „gemeinsam mit"
   oder „im Verhältnis zu" sagt, kommt in einer der vier Gruppen vor.
3. **`schrittweite` hat jetzt in allen vier Tabellen Wertebereich und Herkunft.** Schranke
   `>= 1` und ganzzahlig. Die Ableitung steht einmal im Gruppenkopf der Instrumente und
   ist je Instrument kurz wiederholt: T5 Klasse 10 sagt wörtlich, „höchstens ein Schritt
   je Runde" heiße bei der Regulierung **eine Stufe** und „bei den anderen dreien
   `schrittweite[instrument]` Basispunkte" — T51 beziffert die eine Schrittweite, die es
   beziffert, mit 1, dem kleinsten positiven Wert ihrer Klasse. Dazu die beiden Ausfälle
   aus der Bewegungsregel `stand = min(max(stand ± schritt, min), max)`: Weite 0 lässt das
   Instrument stehen, ohne dass etwas abbricht; negative Weite dreht die Richtung um. **Als
   Folgerung gekennzeichnet, nicht als wörtliche Vorgabe** — dieselbe Bauart wie
   `stufen_max >= 1`. Eine obere Schranke nennt `specs/` nicht; wirksam begrenzt ist die
   Wirkung durch `instrument_max − instrument_min` (10.050 / 10.000 / 20.000 / 1 bp).

**Nicht angefasst, wie angewiesen:** die fünf Klasse-4-Schlüssel aus Befund 3 des
Prüfbefunds. Der Dateikopf sagt jetzt ausdrücklich, dass sie unverändert bleiben, warum
(die Frage berührt T5 und steht in `rueckstand.md`), und dass der Satz „specs/ nennt keine
obere" bei `preisstoss` als **bestrittene** Aussage zu lesen ist.

**Was ich nicht nachweisen kann:** Ein TOML-Parser lief auch in diesem Lauf nicht —
`python3` mit `tomllib` ist vorhanden, der Aufruf wurde von der Umgebung abgewiesen.
Abnahme 4 ist damit wie beim ersten Mal strukturell belegt und nicht maschinell: 50 Zeilen
beginnen mit einem Kleinbuchstaben und alle 50 passen auf `^[a-z_0-9]+ *=`, kein Wert
trägt Dezimalpunkt, Anführungszeichen oder Apostroph, alle 38 blanken Schlüssel stehen vor
dem ersten Tabellenkopf (Zeile 754), vier Tabellenköpfe, keine Zeile beginnt mit etwas
anderem als `#`, `[`, Leerraum oder einem Schlüsselnamen, 46 `# PLATZHALTER` plus 4
`# FEST (T51)` = 50.

*Vorgeschichte:* **2026-09-02, Projektmanager: `gebaut` → `offen`** (Rücklauf 1),
Grundlage ist der Prüfbefund vom 2026-09-02 mit `urteil: zurueck`.

*Vorgeschichte:* **2026-09-02, `offen` → `gebaut`.** `parameter.toml` liegt mit 763
Zeilen vor und trägt im Kopf dieses Paket mit Stand 2026-09-02; der Datenbauer hat den
Status nicht gesetzt. Nachgezogen, damit der Daten-Prüfer das Paket sieht. Keine
Abnahme — ob jeder Schlüssel aus T27 und T51 mit Klasse, Wertebereich, Herkunft der
Schranke und einem Startwert innerhalb der Schranken dasteht, misst der Prüfer.
