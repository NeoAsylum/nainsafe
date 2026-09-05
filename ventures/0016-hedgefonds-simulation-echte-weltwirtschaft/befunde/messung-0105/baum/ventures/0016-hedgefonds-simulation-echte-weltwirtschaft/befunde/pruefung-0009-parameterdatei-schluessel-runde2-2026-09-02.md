---
typ: pruefung
paket: 0009-parameterdatei-schluessel
pruefer: daten-pruefer
datum: 2026-09-02
urteil: zurueck
kriterium_geprueft: Alle 50 Schluessel gegen T27 und T51 abgezaehlt, jede Klassenzuweisung gegen T5 gestellt und jede der 50 Schranken gegen ihre genannte Herkunft geprueft -- eine Schranke nennt keine, und ihre Klasse traegt sie nicht.
befunde: 3
---

# Pruefung 0009, Runde 2 (Fassung 2 der Datei, 932 Zeilen)

Geprueft wurde `ventures/0016-.../parameter.toml`, Stand 2026-09-02, gegen
`specs/0016-.../technik.md` T5, T27, T30, T47, T50, T51, T23 Punkt 5 und
`specs/0016-.../spiel.md`.

**Kein TOML-Parser lief.** `python3 -c` mit `tomllib` wurde von der Umgebung
abgewiesen (dieselbe Sperre wie in Runde 1). Abnahme 4 ist deshalb wieder nur
strukturell belegt, nicht maschinell -- siehe unten.

---

## Was die drei Ruecklaufpunkte betrifft: alle drei halten

**Ruecklaufpunkt 1 -- `startzustimmung` / `zustimmung_wechselschwelle`.**
`startzustimmung = 1` (Zeile 434), `zustimmung_wechselschwelle = 0` (Zeile 580).
`1 > 0` und `0 < 1`, beide Ungleichungen gehen auf. Beide Kommentarbloecke nennen
die Ungleichung jetzt ausdruecklich als *streng* (Zeilen 416-418 und 569-571) und
verweisen aufeinander. Behoben.

**Ruecklaufpunkt 2 -- die Aufzaehlung der gekoppelten Paare.** Die
Einzigartigkeitsbehauptung ist weg. Gruppe (a) fuehrt acht Bedingungen; ich habe
jede einzeln eingesetzt und nachgerechnet:

| # | Bedingung | eingesetzt | Ergebnis |
|---|---|---|---|
| 1 | `instrument_min[leitzins] >= 1 - aufschlag` | `-50 >= 1 - 51 = -50` | wahr |
| 2 | `1 <= _1 < _2 < _3 <= aufsicht_max` | `1 <= 1 < 2 < 3 <= 3` | wahr (4 Vergleiche) |
| 3 | `0 <= regulierung_start <= regulierung_stufen` | `0 <= 0 <= 1` | wahr (2) |
| 4 | `instrument_max[regulierung] = regulierung_stufen` | `1 = 1` | wahr |
| 5 | `startzustimmung > zustimmung_wechselschwelle` | `1 > 0` | wahr |
| 6 | `instrument_min <= instrument_max` je Instrument | `-50<=10000`; `0<=10000`; `-10000<=10000`; `0<=1` | wahr (4) |
| 7 | `lobbykosten * beteiligungsrabatt >= 1` | `1 * 1 = 1` | wahr |
| 8 | `stufen_max * stufenweite <= 10.000` | `1 * 1 = 1` | wahr |

Die Datei nennt 15 Einzelvergleiche; nachgezaehlt sind es 1+4+2+1+1+4+1+1 = 15.
Die Zahl stimmt. Gruppe (a) ist vollstaendig: Ich habe die Datei nach jedem
Schluesselnamen durchsucht, der im Kommentar eines *anderen* Schluessels als
Schranke auftritt, und keine Bedingung zwischen zwei Schluesseln gefunden, die in
(a) fehlt. Gruppe (b) ist es nicht -- siehe Befund 2.

**Ruecklaufpunkt 3 -- `schrittweite` in den drei bp-Instrumenten.** Wertebereich
und Herkunft stehen jetzt in allen vier Tabellen: Gruppenkopf Zeilen 693-731,
je Instrument wiederholt in den Zeilen 744-748 (Leitzins), 767-770 (Zoll),
786-789 (Haushalt), 801-802 (Regulierung, `FEST (T51)`). Das Zitat aus T5
Klasse 10 habe ich im Wortlaut gegen `technik.md` Zeile 155-156 gehalten -- es
steht dort zeichengenau so. Die drei Spannen, mit denen der Gruppenkopf die
Wirksamkeit begruendet, gehen auf: `10000-(-50) = 10.050`, `10000-0 = 10.000`,
`10000-(-10000) = 20.000`, `1-0 = 1`. Die Ableitung ist als **Folgerung**
gekennzeichnet und nicht als woertliche Vorgabe. Behoben.

**Die fuenf geparkten Klasse-4-Schluessel sind unangetastet**, wie angewiesen:
`preisstoss` (553), `zustimmung_elastizitaet` (564), `nachahmer_wirkung` (592),
`hebel_max` (630), `innerjahresausschlag_faktor` (668), alle unveraendert `= 0`.
Der Dateikopf markiert den Satz „specs/ nennt keine obere" bei `preisstoss`
ausdruecklich als bestrittene Aussage (Zeilen 16-19). Befund 1 unten betrifft
**einen anderen Schluessel, eine andere Klasse und die andere Richtung** und
greift der Frage in `rueckstand.md` nicht vor.

---

## Befund 1 -- `hebelaufschlag`: eine Schranke ohne Herkunft, und die Klasse traegt sie nicht (Abnahme 3)

**Wo:** `parameter.toml` Zeilen 632-642, Schluesselzeile 642.

**Was dasteht:**

```
# `hebelaufschlag`* -- Klasse 3 (Raten, bp). Aufschlag auf den Leitzins
# des Landes je 10.000 Sichtbarkeit; spiel.md Aktion 4: "Kreditaufnahme
# zum Leitzins des Landes plus einem Aufschlag, der mit der Sichtbarkeit
# des Fonds steigt", Kanal 4: "Aufschlag steigt mit Sichtbarkeit".
# Nicht zu verwechseln mit `aufschlag` (Leitzins <-> Anleiherendite).
# Schranke: >= 0.
```

**Warum das Abnahme 3 verletzt.** Abnahme 3 verlangt „jede Schranke nennt die
Vorgabe, aus der sie stammt". Hier steht `>= 0` ohne jede Herkunft -- kein
Verweis auf specs/, kein „aus der Klasse", keine Kennzeichnung als Folgerung.
Und die Klasse traegt sie nicht: **T5 Klasse 3 (Raten) hat den Bereich
`±2 Mio %`** (`technik.md` Zeile 124), ist also symmetrisch um null. Aus der
Klasse folgt `>= 0` gerade nicht.

**So erzeugt man den Fehler, Schritt fuer Schritt:**

1. `grep -n "Schranke: >= 0" parameter.toml` liefert elf Treffer. Vier nennen
   eine Herkunft oder eine Kappung und scheiden aus: Zeile 259
   (`gegenlobby_satz`, „wirksam begrenzt … durch `druck_max` (T5 Klasse 9)"),
   272 (`druck_max`, „>= 0 aus der Klasse; >= 1 … Folgerung"), 361
   (`nachahmer_tempo`, „wirksam begrenzt durch `nachahmer_max`") und 547
   (`preisstoss`, „specs/ nennt keine obere" -- der geparkte Fall).
   **Sieben stehen blank:** 373, 559, 586, 600, 624, 637, 663.
2. Fuer jeden dieser sieben die im zugehoerigen Kommentarblock deklarierte
   Klasse gegen die Bereichsspalte von T5 halten:
   - `nachahmer_max` (373), `aufsicht_tempo` (600): **Klasse 11**, T5-Bereich
     „0 … Obergrenze aus `parameter.toml`" -- die 0 kommt aus der Klasse, gedeckt.
   - `zustimmung_elastizitaet` (559), `nachahmer_wirkung` (586), `hebel_max`
     (624), `innerjahresausschlag_faktor` (663): **Klasse 4**, T5-Bereich
     „0 bis 10.000" -- die 0 kommt aus der Klasse. Vier der fuenf geparkten
     Schluessel; dort geht es um den *Deckel*, nicht um die Untergrenze.
   - `hebelaufschlag` (637): **Klasse 3**, T5-Bereich „±2 Mio %" -- **die 0 kommt
     nirgendwo her.**
3. Gegenprobe an den beiden anderen Klasse-3-Schluesseln derselben Datei: beide
   nennen eine Herkunft. `aufschlag` (Zeile 204-210) nennt T51 und T23 Punkt 5;
   `abschreibungsrate` (Zeile 523-524) nennt die Schranke ausdruecklich als
   „Folgerung, keine Vorgabe aus specs/". `hebelaufschlag` ist der einzige
   Klasse-3-Schluessel ohne Herkunft.

**Die Herkunft steht zwei Zeilen darueber und wird nicht benutzt.** Die Datei
zitiert `spiel.md` Aktion 4 selbst: „ein Aufschlag, der mit der Sichtbarkeit des
Fonds **steigt**" (`spiel.md` Zeile 177-178, im Wortlaut nachgelesen; Kanal 4 in
Zeile 524 wiederholt es). Das ist die Vorgabe, aus der eine Untergrenze folgt --
sie steht als *Bedeutung* da und nicht als *Herkunft der Schranke*. Damit ist
nicht entscheidbar, ob `>= 0` eine Folgerung aus „steigt" ist oder ein
unbedachter Vorgabewert; unter der ersten Lesart waere die Schranke `>= 1`
(kleinster positiver Wert der Klasse), denn ein Faktor 0 laesst den Aufschlag
gerade nicht steigen. Dieselbe Unterscheidung, die die Datei bei `druck_max`
(Zeile 272-273) und `stufen_max` (171-172) ausdruecklich trifft und begruendet.

**Praktische Folge.** `parameter.toml` ist die einzige Stelle, an der diese
Schranke ueberhaupt steht: Die sieben Wertebereichsschranken, die der
Invariantentest je Runde prueft (T30 Pruefung 2, `technik.md` Zeilen 1375-1383),
laufen ausschliesslich ueber Zustandsadressen; kein Parameterschluessel ist
darunter, und `hebelaufschlag` kommt in specs/ in keiner Pruefung vor. Ein
Bauagent, der `>= 0` fuer eine Klassenschranke haelt und sie deshalb beim
Einlesen weglaesst, laesst `hebelaufschlag < 0` zu. Dann sinkt der Kreditzins mit
steigender Sichtbarkeit; zusammen mit `leitzins` an seiner Untergrenze `-50` bp
wird die Kreditaufnahme ertragreich, Kanal 4 („Aufschlag steigt mit
Sichtbarkeit") kehrt sich um, und **nichts bricht ab** -- derselbe stille
Ausfall, den der Ruecklauf 1 fuer `schrittweite = 0` benannt hat.

**Umfang der Reparatur:** eine Zeile. Entweder die Herkunft nachtragen (Zitat aus
`spiel.md` Aktion 4, als Folgerung gekennzeichnet, wie bei `abschreibungsrate`)
oder ausdruecklich hinschreiben, dass specs/ keine nennt und `>= 0` gesetzt ist.

---

## Befund 2 -- BEFUNDE Punkt 5 Gruppe (b) ist unvollstaendig, obwohl der Abschnitt Vollstaendigkeit zusagt

**Wo:** Zeilen 852-853 („Welche Platzhalter voneinander abhaengen --
**vollstaendig**") und Gruppe (b), Zeilen 882-893.

Gruppe (b) fuehrt drei Stellen, an denen ein Schluessel nicht den anderen
begrenzt, sondern dessen *Ergebnis*: `gegenlobby_satz` → gekappt durch
`druck_max`; `nachahmer_tempo` → gekappt durch `nachahmer_max`; `schrittweite` →
gekappt durch den Wertebereich des Instruments.

**Es fehlt ein vierter Fall derselben Bauart:** `aufsicht_tempo` (Zeile 604) ist
nach seinem eigenen Kommentar der „Zuwachs des Aufsichtszaehlers je Runde", und
der Aufsichtszaehler ist durch `aufsicht_max` (356) gekappt -- das sagt die Datei
bei `aufsicht_max` selbst: „Obergrenze des Aufsichtszaehlers … Zu niedrig -- der
Zaehler saettigt". Das ist Zeichen fuer Zeichen dasselbe Verhaeltnis wie
`nachahmer_tempo`/`nachahmer_max`, das in (b) steht.

**So sieht man es:** Die beiden Kommentarbloecke nebeneinanderlegen.
`nachahmer_tempo` (Zeile 361-362) schreibt „specs/ nennt keine obere; wirksam
begrenzt durch `nachahmer_max`". `aufsicht_tempo` (Zeile 600) schreibt nur
„Schranke: >= 0." und nennt `aufsicht_max` an keiner Stelle -- obwohl beide
Schluessel Klasse 11 sind, beide einen Zaehler je Runde erhoehen und beide einen
zugehoerigen `_max`-Schluessel in dieser Datei haben.

**Folge:** Der Abschnitt sagt „vollstaendig" zu und ist es nicht. Er wird von der
naechsten Rolle als gepruefte Aussage gelesen -- genau die Wirkung, wegen der
Ruecklauf 1 die Einzigartigkeitsbehauptung ersetzen liess. Kein Wert ist
betroffen: `aufsicht_tempo = 0 <= aufsicht_max = 3` haelt.

---

## Befund 3 -- die Selbstprobe im Dateikopf liefert nicht die Zahlen, die sie belegen soll

**Wo:** Zeilen 116-117.

```
#   Davon 46 mit `# PLATZHALTER` und 4 mit `# FEST (T51)`.
#   `grep -c PLATZHALTER` und `grep -c 'FEST (T51)'` zaehlen es nach.
```

**Nachgerechnet:** `grep -c "# PLATZHALTER"` liefert **47**, `grep -c "# FEST
(T51)"` liefert **5**. Der jeweils ueberzaehlige Treffer ist die Zeile 116
selbst, die beide Zeichenketten in Anfuehrungsstrichen fuehrt. Ohne das `# `
davor (also genau der im Text vorgeschriebene Aufruf) trifft zusaetzlich Zeile
117, dann sind es 48 und 6.

**Die Zahlen 46 und 4 stimmen** -- ich habe sie ueber die Schluesselzeilen
gezaehlt: `grep -c "^[a-z_0-9]* *="` liefert 50, davon tragen die Zeilen 778,
816, 817, 818 `# FEST (T51)` (4) und die uebrigen 46 `# PLATZHALTER`. Falsch ist
nur der **Pruefweg**, den die Datei vorschreibt. Ein Pruefer, der ihn ausfuehrt,
sieht 47 statt 46 und muss selbst herausfinden, dass die Datei sich selbst
mitzaehlt. Reparatur: die beiden Marken im Kopftext anders schreiben oder den
Aufruf auf Schluesselzeilen einschraenken.

---

## Hinweis, kein Befund

Zeile 51-52 sagt zur verschaerften Regel A: „**Betroffen ist genau ein Paar**".
Der Satz hat zwei Lesarten. Meint er „nur ein Paar hatte verletzte Werte", ist er
richtig. Meint er „die Regel greift bei genau einem Paar", ist er falsch: Streng
geordnet sind in dieser Datei drei Paare -- `aufsicht_schwelle_1 < _2`,
`_2 < _3` (Zeile 331) und `startzustimmung > zustimmung_wechselschwelle`. Bei den
Aufsichtsschwellen ist die Regel sogar sichtbar angewandt (1, 2, 3 -- je ein
ganzzahliger Schritt). Weil eine der beiden Lesarten zutrifft, ist das kein
Befund; weil es der zweite Satz dieser Art an derselben Stelle waere, notiere ich
ihn.

---

## Was ich sonst geprueft und **nicht** beanstandet habe

Damit erkennbar ist, wo diese Pruefung hingesehen hat:

- **Abnahme 1 (Vollzaehligkeit).** 50 Schluesselzeilen (`grep -c "^[a-z_0-9]* *="`).
  Gegen T27 abgezaehlt: 10 Skalare der T27-Tabelle (Zeilen 1040-1048 von
  `technik.md`), 12 aus dem Fliesstext von T27 („Mandatsschwelle … Elastizitaeten",
  Zeilen 1029-1032), 4 „Verzoegerungen", 12 „Elastizitaeten". Gegen T51 abgezaehlt:
  4 Instrumente x 3 Schluessel = 12, alle vier Tabellenkoepfe vorhanden
  (`[instrument.leitzins|zoll|haushalt|regulierung]`, Zeilen 754/776/792/815) und
  in der Reihenfolge aus T9. Summe 10+12+4+12+12 = 50. Gegenrichtung: kein
  Schluessel in der Datei, der in T27 oder T51 nicht vorkommt oder dort nicht als
  gebildeter Name (`*`) markiert ist.
- **Abnahme 2 (keine Klasse fehlt).** Jede der 50 Schluesselzeilen hat im
  zugehoerigen Kommentarblock eine Klassenangabe; die vier der Gruppe B2 tragen
  sie gemeinsam im Gruppenkopf (Zeile 457), die zwoelf Instrumentenschluessel in
  den vier Tabellenkoepfen. Die zehn Klassenzuweisungen der T27-Tabelle habe ich
  einzeln gegen `technik.md` Zeilen 1040-1049 gehalten: `stufenweite` 4,
  `stufen_max` 11, `ausstiegsabschlag`/`zwangsabschlag` 4, `aufschlag` 3,
  `lobbykosten` 1, `beteiligungsrabatt` 4, `gegenlobby_satz` 9, `druck_max` 9,
  `regulierung_stufen` 10 -- alle zehn stimmen ueberein.
- **Abnahme 3, Wertteil.** Alle 50 Startwerte gegen ihre eigene Schranke gestellt,
  einzeln. Alle 50 liegen darin; die acht Bedingungen zwischen zwei Schluesseln
  stehen oben nachgerechnet. Regel A haelt durchgehend: Jeder Schluessel mit einer
  unteren Schranke steht genau auf ihr, jeder ohne steht auf 0.
- **`aufschlag = 51` gegen den Jahrgang.** T23 Punkt 5 (`technik.md` Zeilen
  756-771) im Wortlaut nachgelesen: `aufschlag_min = 1 - min(leitzins_pfad)`, beim
  EZB-Einlagesatz `1-(-50) = 51`, beim Hauptrefinanzierungssatz `1`. Der
  Platzhalter 51 haelt beide Kandidaten ein. Die vier spielbaren Laender sind USA,
  China, Deutschland, Brasilien (`spiel.md` Zeile 8); unter ihnen ist der
  EZB-Einlagesatz mit -0,50 % tatsaechlich der tiefste Leitzinsstand im
  Pruefjahrgang, `instrument_min[leitzins] = -50` schliesst den historischen Pfad
  also ein. Ein Land mit tieferem Satz (Schweiz, Japan) ist nicht dabei -- das war
  die Gegenprobe, die den Wert haette kippen koennen.
- **Regel B (weite Wertebereiche).** `instrument_min[leitzins] = -50` ist trotz
  seiner Enge korrekt: `1 - aufschlag = -50` ist die tiefste nach T51 zulaessige
  Untergrenze, der Platzhalter ist also der weitest moegliche und nicht der engste.
- **Abnahme 4 (TOML), strukturell.** Kein Parser lief. Ersatzweise: alle 50
  Wertzeilen passen auf `^[a-z_0-9]+ *=`; `grep -n "^[a-z_0-9]* *=.*[.\"']"` ist
  leer, also kein Dezimalpunkt, keine Anfuehrungszeichen, kein Apostroph in einem
  Wert -- alle Werte sind TOML-Ganzzahlen und damit `i64` (T4); alle 38 blanken
  Schluessel stehen vor dem ersten Tabellenkopf (Zeile 754); vier Tabellenkoepfe,
  keine Wiederholung; keine Zeile beginnt mit etwas anderem als `#`, `[`, Leerraum
  oder einem Schluesselnamen. **Maschinell bestaetigt ist das nicht.**
- **Kein Wert nimmt eine Kalibrierung vorweg.** 46 `# PLATZHALTER`, 4
  `# FEST (T51)`; die vier festen sind `instrument_min[zoll] = 0` und die drei
  Werte der Regulierung, alle drei durch T51 gedeckt (`0 … regulierung_stufen`,
  1 Stufe je Runde).
- **Lizenz.** Die Datei traegt keinen Datenanker und keine Zahl aus einer externen
  Quelle (Zeilen 145-148 sagen es, und die Pruefung der 50 Werte bestaetigt es:
  alle sind 0, 1, 2, 3, 51, ±10.000 oder -50, jeder aus einer Schranke abgeleitet).
  Damit ist keine Namensnennung faellig; `specs/0016-.../daten.md` ist fuer dieses
  Paket nicht einschlaegig.

## Was ich nicht pruefen konnte

- **Ob es genau diese zwoelf Elastizitaeten sind.** T27 nennt die Gruppe, specs/
  nennt keine einzige beim Namen; die Datei sagt das selbst (BEFUNDE 2). Das
  entscheidet erst das Paket, das die Schritte 3 bis 5 baut. Nicht Gegenstand von
  Abnahme 1, weil dort keine Schluessel abzuzaehlen sind.
- **Die TOML-Gueltigkeit maschinell** (siehe oben).
- **`instrument_max` der vier Instrumente gegen den historischen Pfad.** Das
  braucht den eingebetteten Jahrgang und ist nach T51 eine Pruefung des
  Jahrgangsbaus. Die Datei benennt sie als Auflage (BEFUNDE 5c).
