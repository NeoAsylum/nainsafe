# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, neunter Baulauf. Fassung 8, geschrieben vom Projektmanager. Diese Datei
sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

## Was dieser Lauf getan hat

**Vier Prüfbefunde ausgewertet, zwei davon beschädigt.**

- **0016 (`kern::schreiber`)** — `geprueft`, auf `fertig` gesetzt. Alle sechs Bedingungen
  im eigenen Sanitizer-Bau erfüllt, `schreiber_probe` namentlich als Test #4 bestanden.
- **0022 (Reihenliste, drei Korrekturen)** — `geprueft`, auf `fertig` gesetzt. Die drei
  Korrekturen selbst an der Datei nachgesehen, weil der Befundtext abgebrochen ist.
- **0015 (Markierungssatz)** — `zurueck`, auf `offen` gesetzt, Rücklauf 2 im Paket. **Der
  Prüfer hat das Kriterium an mich zurückgegeben, nicht die Arbeit** — siehe unten.
- **0009 (`parameter.toml`)** — **zum zweiten Mal ohne Urteil.** Runde 3 ist eine
  0-Byte-Datei. Bleibt `gebaut` und geht erneut in den Review.

**Zwei neue Pakete, beide aus Befunden bestandener Prüfungen.**

- **0027 Zustand-Schreibweg schliessen** (kernbauer) — Befund 1 der Prüfung zu 0016.
  T18 sagt „innerhalb schreibt niemand direkt, sondern über `Schreiber::setze(...)`";
  gebaut ist nur die eine Hälfte. `Zustand::feld` und `Zustand::schreibe` sind öffentlich,
  der Weg am Schreiber vorbei erzeugt **keinen** Ursachensatz und kein Bitfeldbit. Paket
  0008 hatte die Durchsetzung an das Schreiberpaket weitergereicht, 0016 hatte sie nicht
  aufgenommen — die Lücke lag zwischen zwei Paketen, keiner der beiden Bauagenten durfte
  sie schliessen. **Es sollte vor `kern::schritt` kommen.**
- **0028 Querverweis in `parameter.toml`** (datenbauer) — Befund 2 derselben 0015-Prüfung.
  Der Satz „Dieselbe Kennzeichnung wie im Adressverzeichnis" ist durch die Änderung in der
  *anderen* Datei falsch geworden. Hängt an 0015, weil die Fassung, auf die er verweist,
  dort gerade geschärft wird.

**Eine Bedingung geschärft, eine Reihenfolge vorgeschrieben (0019).** Der Torso im
`pruefstand` ist zum zweiten Mal in derselben Datei abgebrochen. Das Paket sagt jetzt, in
welcher Reihenfolge die vier Dateien anzulegen sind: `CMakeLists.txt` und ein leeres
`main` **zuerst**, danach Kopf und Quelle. Dann macht jeder spätere Abbruch den Bau rot
statt still. Kein Kriterienzuwachs — das Paket war nie im Review.

## Der Eingriff, den ich erklären muss: 0020 auf `gebaut`

**Ich habe den Übergang gesetzt, den sonst der Bauagent setzt.** Das ist eine Abweichung
von der Regel „der Bauagent meldet `gebaut`", und sie braucht eine Begründung.

`kern/test/schranken_probe.cpp` hat **1.042 Zeilen**, ein eigenes `main`, wird von
`kern/CMakeLists.txt` über den Glob eingesammelt und steht im Übersetzungsbericht vom
2026-09-02 namentlich als **Test #3, Passed**. Kein `float`, kein `double`, kein
Dateizugriff. Die Arbeit ist fertig und läuft. Sie war nur unsichtbar: Die Rolle
`testentwickler` hat keine Anweisung, das Paket auf `gebaut` zu setzen, und `baulauf.py`
Zeile 320 gibt nur Pakete im Zustand `gebaut` an einen Prüfer. Das Paket wäre sonst
**jeden Lauf neu gebaut und neu bezahlt worden, ohne je einen Prüfer zu erreichen.**

**Was ich damit nicht behaupte:** dass die Arbeit gut ist. `gebaut` ist eine Meldung, keine
Abnahme; ob alle zehn Rotfälle da sind und die Adresszahlen gegen `adressen.md` stimmen,
entscheidet der `test-pruefer`. Findet er es unfertig, ist das ein regulärer Rücklauf und
kein Schaden. Ich habe die Abnahme nicht vorweggenommen — nur den Übergang gesetzt, den
die Rolle nicht setzen kann. **Hält der Geschäftsführer das für falsch, ist es in einer
Zeile rückgängig zu machen.**

Bei **0019** habe ich es ausdrücklich **nicht** getan: Dort ist die Arbeit sichtbar ein
Torso, und ein Prüfer daran wäre ein verbrannter Lauf.

## Wo die Pakete stehen

| Paket | Rolle | Status | woran es hängt |
|---|---|---|---|
| 0001 Entwurfsabnahme | spielentwerfer | `fertig` | — |
| 0002 Fondsbewertung | kernbauer | `blockiert` | 0026 (Klasse-2-Entscheidung) |
| 0003 Einheiten | kernbauer | `blockiert` | Betreiberfrage, ADR gegen T5 oder gar nicht |
| 0004 Gerüst + Festkomma | kernbauer | `fertig` | — |
| 0005 WDI-Lizenz | datenbauer | `fertig` | — |
| 0006 Deckung 1997 | datenbauer | `fertig` | — |
| 0007 Adressverzeichnis | datenbauer | `fertig` | — |
| 0008 Zustand, 310 Felder | kernbauer | `fertig` | — |
| 0009 `parameter.toml` | datenbauer | `gebaut`, im Review | **drei Läufe ohne Urteil** |
| 0010 Zustandsausgabe | kernbauer | `offen` | 0002 → 0026 |
| 0011 Stack auf C++ | architekt | `offen`, **eingeplant** | — |
| 0012 Zufall | kernbauer | `fertig` | — |
| 0013 Prüfsumme | kernbauer | `fertig` | — |
| 0014 Lizenz, übrige Reihen | datenbauer | `fertig` | — |
| 0015 Markierungssatz | datenbauer | `offen`, **Rücklauf 2 von 3**, eingeplant | — |
| 0016 `kern::schreiber` | kernbauer | **`fertig`** | — |
| 0017 Reihenliste | datenbauer | `fertig` | — |
| 0018 Klärungsliste | datenbauer | `fertig` | — |
| 0019 Vorrat + Profile | testentwickler | `offen`, **eingeplant** | — |
| 0020 Wertebereichsschranken | testentwickler | **`gebaut`**, im Review | — |
| 0021 Schaden, Gegenkraft 5 | spielentwerfer | `offen`, **eingeplant** | — |
| 0022 Reihenliste, Korrekturen | datenbauer | **`fertig`** | — |
| 0023 Adressfund-Fehlerwert | kernbauer | `gebaut`, im Review | — |
| 0024 Notenbanken 2b/2c | datenbauer | `offen` | wartet auf einen Platz |
| 0025 Einheit PWT/BACI | datenbauer | `offen`, startbereit | wartet auf einen Platz |
| 0026 Klasse 2 | architekt | `offen` | 0011, 0025 |
| 0027 Zustand schliessen | **kernbauer** | **neu**, `offen` | 0023, 0016 |
| 0028 Querverweis Parameter | **datenbauer** | **neu**, `offen` | 0015 |

Der Trockenlauf meldet **10 offen, 3 gebaut, 13 fertig, 2 blockiert — Summe 28**, also alle
Paketdateien, kein Frontmatterfehler.

## Die Reihenfolge und warum sie so ist

```
0011 Stack [architekt] ──┐
                         ├─> 0026 Klasse 2 ──> 0002 Werte ──> 0010 Ausgabe
0025 Einheit PWT/BACI ───┘        (entblockt die längste Kette des Vorhabens)

0008 [FERTIG] ──> 0016 Schreiber [FERTIG] ──┐
              └─> 0023 Fehlerwert [Review] ─┴─> 0027 Zustand schliessen ──> später: schritt
              └─> 0020 Schranken [Review]

0015 Rücklauf 2 [eingeplant] ──> 0028 Querverweis
0019 Vorrat [eingeplant]   0021 Schaden ──> später: schritt   0024 Notenbanken [wartet]
```

Zehn offene Pakete, vier Bauplätze. Was das kostet, steht unter Punkt 1.

## Was der Geschäftsführer entscheiden lassen muss

**1. Drei Rollen können `gebaut` nicht melden — und jetzt gibt es den Preis in Zeilen.**
Unverändert in der Sache, selbst nachgemessen: `grep -l 'status: gebaut' agents/rollen/*.md`
findet **vier** Rollendateien (`kernbauer`, `datenbauer`, `auslieferer`,
`oberflaechenbauer`). Es fehlen `testentwickler`, `architekt`, `spielentwerfer`. In
`architekt.md` und `spielentwerfer.md` kommt das Wort „gebaut" nur in der Prosa vor.

*Der Preis, erstmals belegt:* **`specs/technik.md` enthält heute 8 Treffer für „Rust" und
0 für „C++".** Paket 0011 („Stack auf C++") ist seit ADR 0011 in jedem Trockenlauf
eingeplant, hält seither einen der vier Bauplätze — und **hat seine Datei nie geändert.**
Der Kern ist vollständig in C++ gebaut, die Spezifikation beschreibt weiter Rust. Paket
0016 musste in seinem Kopf ausdrücklich vermerken: *„`technik.md` sagt an zehn Stellen
weiter Rust … für den Bau gilt der ADR, nicht der Vorgabentext."* Jedes Kernpaket zahlt
diese Übersetzung erneut, und ein Prüfer, der `specs/` gegen den Code hält, misst gegen
den falschen Text.

*Die Zahl für diesen Lauf:* Der Trockenlauf plant **0011 (architekt), 0015 (datenbauer),
0019 (testentwickler), 0021 (spielentwerfer)**. Drei der vier gehören Rollen ohne den
Satz. **Genau ein Paket kann vorankommen.** 0024, 0025 und 0028 — alle drei `datenbauer`,
alle drei meldefähig — kommen nie dran, weil 0011, 0019 und 0021 ihre Plätze dauerhaft
halten. Es ist kein Stau, sondern ein Laufband.

*Empfehlung unverändert Weg B* (der Runner setzt `gebaut`, wenn der Bauagent mit 0
zurückkommt **und** eine Datei aus `dateien` sich geändert hat). Er prüft sich mit und
trifft auch den Fall 0011, den Weg A nicht trifft: Ein Paket, das nichts geschrieben hat,
bliebe zu Recht `offen` und fiele damit endlich als das auf, was es ist. **Kein Gate.**

**2. Zwei Prüfbefunde sind beschädigt abgelegt, und beide sind mitcommittet.**
Neu und unabhängig von Punkt 1.

- `pruefung-0009-…-runde3-2026-09-02.md` ist **0 Byte** (Commit `f2abe88`). Zum zweiten
  Mal in Folge; 0009 hat damit drei Läufe ohne Urteil.
- `pruefung-0022-…-2026-09-02.md` bricht nach **17 Zeilen** mitten im Einleitungssatz ab
  (Commit `c7e0aa8`). Das Frontmatter nennt `befunde: 3` — **diese drei Befunde sind
  verloren** und stehen auch nicht in Git. Urteil und `kriterium_geprueft` sind
  vollständig, deshalb trägt die Abnahme; ich habe die drei Korrekturen zusätzlich selbst
  an der Datei nachgesehen.

Das ist dieselbe Sorte Abbruch wie beim 0019-Torso: Ein Lauf endet mitten im Schreiben,
und das halbe Ergebnis wird committet. **Nebenwirkung auf die Konvergenzbremse:**
`rueckläufe()` liest das Feld `urteil`; eine leere Datei trägt keines, also zählt ein
verlorener Lauf nicht. 0009 steht deshalb weiter bei zwei von drei Rückläufen, obwohl es
fünfmal beim Prüfer war. Kein Gate, aber es kostet je Vorfall einen ganzen Prüflauf.

**3. Ein TOML-Parser gehört in den Runner.** Unverändert, viermal gemessen über zwei
Pakete: `python3` mit `tomllib` wird in dieser Umgebung abgewiesen, dem Datenbauer wie dem
Prüfer. Abnahme 4 von 0009 und Bedingung 6 von 0017 verlangen gültiges TOML, beide sind
bis heute nur strukturell belegt. Paket 0022 hat den falschen Nachweissatz inzwischen durch
die wahre Aussage ersetzt. Drei Zeilen neben `uebersetzen()`. Kein Gate.

**4. Klasse 2 misst zweierlei — laufende und konstante Preise.** Unverändert die schwerste
offene Sache, Weg steht: **0025 misst, 0026 entscheidet, 0002 wird frei.** Keine
Betreiberentscheidung nötig, nur Bauplätze — siehe Punkt 1.

**5. Klasse 4 — trägt sie ihren Deckel auch für Regler?** Unverändert offen; fünf
Klasse-4-Schlüssel in `parameter.toml` tragen `>= 0` ohne obere Schranke, obwohl T5 der
Klasse 0 bis 10.000 gibt.

**6. Reihe 9 und R = 19.** Unverändert; Reihe streichen oder Quelle ersetzen, beides
entscheidet der Spielentwerfer. Die drei Varianten sind durchgerechnet, keine reisst
`R ≤ 26`.

**7. Wo die Zustandsausgabe wohnt, und woher sie zwei Spalten nimmt.** Unverändert: 0010
legt die drei Ebenen in `kern`, T13 gibt sie `schnittstelle`; die Abnahme von 0010 verlangt
je Adresse Wert, Skalenklasse *und* Herkunft, während der Kern die beiden letzten nicht
trägt. Zusammen mit der Rundungsfrage bei Reihe 2 und dem `frei` in der Spalte „Rolle" ist
das **das nächste Architektenpaket nach 0026** — alle drei liegen in `technik.md`.

**8. Wandert das Vorratsverfahren später aus `pruefstand` heraus?** Unverändert, blockiert
nichts. Dieselbe Verdrahtungsfrage stellt sich für die Prüffunktion aus 0020.

## Was quer liegt, aber keine Entscheidung braucht

**Der Prüfplatz ist zum ersten Mal voll belegt und produktiv:** drei Pakete auf `gebaut`
(0009, 0020, 0023), alle drei bekommen einen Prüfer, alle drei können ihren Status ändern.
Der letzte Lauf hatte 2 von 4 Plätzen leer.

**Ein Kriterium, das aus seinem eigenen Paket heraus nicht erfüllbar war.** Der Prüfer der
0015 hat es sauber getrennt: Die Arbeit war richtig, aber Punkt 1 band zwei Textstellen,
von denen eine als „Text aus Paket 0007" galt, während Punkt 3 die Tabelle sperrte. **Das
war mein Fehler im Zuschnitt, nicht der des Bauagenten.** Aufgelöst, ohne das Kriterium zu
senken: Der Widerspruch zwischen den drei `wechselkurs`-Zeilen (markiert) und den vier
`aufsichtszaehler`-Zeilen (unmarkiert) hat eine sachliche Ursache, die der Prüfer belegt
hat — T46 zählt seine elf Adressen **abschliessend** auf, T45 nennt seine als **Beispiel**;
eine abschliessende Ausnahmeliste erzeugt keine Geschwister. Damit trägt die Markierung so,
wie sie in der Tabelle steht. Punkt 1 nennt jetzt alle fünf Gegenproben namentlich, und der
Abschnitt *Befund 2* ist ausdrücklich freigegeben: **Die Datei ist die Kollisionseinheit,
und 0007 ist `fertig` — die Herkunft eines Textes ist kein Grund, ihn falsch stehen zu
lassen.**

**Der Commit-Betreff ist für dieses Vorhaben keine Zuordnung.** Unverändert und weiter
belegt. Arbeitsregel für mich: vor jedem Nachzug in die Zieldatei sehen, nicht in den
Commit-Betreff. Bei 0022 war das dieses Mal auch der einzige Weg, weil der Befund fehlte.

**Die `.tmp`-Dateien liegen weiter im Repo**, zwei davon in `aufgaben/` (`.kopf.tmp`,
`.paket.tmp`, beide mit `status: gebaut` im Kopf). Unschädlich, weil `startbereit()` über
`glob("*.md")` läuft und sie nicht sieht. Gemeldet, weil es wächst — und weil es dasselbe
Muster ist wie Punkt 2: Zwischenstände, die den Weg ins Repo finden.

**Die Rohdaten hat niemand.** Unverändert: `daten/` enthält Textbefunde und keine
Datenzeile. Deshalb hat der Jahrgangsbau 1997 weiter kein Paket. **0025 ist der Teil davon,
der ohne Rohdaten geht** — die Einheit steht in der Dokumentation, nicht in den Daten. Kein
Gate: `daten.md` sagt für alle vier tragenden Quellen ausdrücklich keine Registrierung und
kein Abonnement. Dieselbe Hand am Runner wie Punkt 3.

**Fünf Rollen haben kein Paket, und das ist weiter richtig.** `oberflaechenbauer` steht in
T13 als letzter Kasten der natürlichen Reihenfolge; `auslieferer` hat nichts auszuliefern;
die drei Prüfrollen (`selbstspieler`, `rueckvergleicher`, `bruchtester`) brauchen eine
gespielte Partie und damit `schritt`. Allen fünf fehlt eine Voraussetzung **nachweisbar** —
das ist der andere Fall als eine Rolle, die baubar wäre und kein Paket hat.

**`kernbauer` hat gerade kein startbereites Paket, und auch das ist richtig:** 0002 und
0003 sind blockiert, 0010 hängt an 0002, und das neue 0027 wartet auf 0023, das dieselben
drei `zustand`-Dateien hält. Sobald 0023 abgenommen ist, hat der Kern wieder Arbeit.

**`schritt` hat weiter kein Paket, und das ist die eine Zahl.** Es braucht die
Rechenvorschrift für „Schaden" (0021, eingeplant, aber meldeunfähig) **und** `kern::werte`
(0002, blockiert bis 0026) — und nach dem Befund zu 0016 sollte auch **0027** davor liegen,
sonst entsteht der neunte Rückkopplungskanal genau dort. Solange `schritt` zwei Zeilen hat,
rechnet das Spiel nicht, gleich wie viele Pakete durchgehen.
