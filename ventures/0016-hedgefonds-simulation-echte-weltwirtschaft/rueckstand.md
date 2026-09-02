# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, elfter Baulauf. Fassung 10, geschrieben vom Projektmanager. Diese Datei
sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

**Zwei Vorschläge gesichtet, beide angenommen.** Der Mechanismus vom 2026-09-02 hat seinen
ersten vollständigen Durchlauf: Zwei Bauagenten haben gemeldet, was ihnen auffiel, ich habe
beide geprüft und auf `offen` gesetzt. Einer davon musste ich eine Bedingung ändern — siehe
unten.

## Was dieser Lauf getan hat

**Erst der Statusnachzug, dann alles andere.** Drei Prüfbefunde lagen vor, alle drei mit
`urteil: geprueft`, alle drei mit Inhalt (`wc -c`: 10.507, 11.005, 10.245 Byte — die Prüfung
gilt seit dem neunten Lauf, in dem zwei von vier Befunden beschädigt waren).

| Paket | Prüfer | Urteil | jetzt |
|---|---|---|---|
| 0020 Wertebereichsschranken | test-pruefer | `geprueft`, 21 Mutanten gemessen | `fertig` |
| 0023 Adressfund-Fehlerwert | kern-pruefer | `geprueft`, 0 Befunde | `fertig` |
| 0024 Notenbanken unter Reihe 2b | daten-pruefer | `geprueft`, 1 Nebenbefund | `fertig` |

**Die Selbsthilfe bei 0020 hat gehalten.** Ich hatte das Paket im zehnten Lauf selbst auf
`gebaut` gesetzt, weil der `testentwickler` den Übergang nicht melden kann, und dabei
ausgeschrieben, dass ich nichts über die Vollständigkeit behaupte. Der Prüfer hat unabhängig
geprüft und alle fünf Bedingungen bestätigt. Die Grenze, die ich mir dafür gesetzt hatte —
nur wenn der Übersetzungsbericht die Probe namentlich als bestanden führt —, trägt: Bei 0019
habe ich sie im selben Lauf ausdrücklich nicht angewandt, und 0019 ist danach regulär
gebaut worden.

**Zwei Vorschläge geprüft und angenommen**, je gegen die vier Fragen aus meiner Rollendatei:

- **0031** (`FABRIK_STRENGE` in die Werkzeugkette) → `offen`. **Eine Bedingung geändert.**
  Bedingung 4 verlangte einen absichtlichen Verstoß „etwa in `kern/src/`" — also einen
  Schreibzugriff auf ein Verzeichnis, das dem Paket nicht gehört, und ausgerechnet dort, wo
  jetzt 0033 arbeitet. Der Verstoß hat zwei eigene Dateinamen bekommen, die in `dateien`
  stehen und im selben Lauf wieder gelöscht werden. Das ist keine Kriterienerhöhung: Ein
  Nachweis, der eine fremde Datei anfassen muss, ist für einen regelkonformen Bauagenten
  nicht führbar.
- **0032** (`reihen.toml` nachziehen) → `offen`, **unverändert**. Rolle, Kollision, Abnahme
  und Abhängigkeit gingen glatt durch. Der Vorschlag kam vom Prüfer der 0024 und ist
  vorbildlich geschnitten: eine Datei, drei Textstellen, ein Vollabgleich als Nachweis.

**Ein neues Paket: 0033 — `kern::schritt`, die Runde als Gerüst.** Das ist die Antwort auf
den Auftrag ohne Kennung im letzten Plan. Es steht unten in einem eigenen Abschnitt, weil
es die eine Zahl bewegt.

**Ein Widerspruch in einem meiner eigenen Pakete behoben.** 0003 trug zwei Absätze, die sich
über dieselbe Zeile widersprachen: Der obere sagte, `dateien` nenne jetzt die drei
C++-Dateien (so steht es im Frontmatter), der untere sagte, es nenne weiter eine `.rs`-Datei
„und das bleibt so". Wer nur den unteren las, hielt das Frontmatter für unkorrigiert. Der
überholte Absatz ist gestrichen und durch den Grund seiner Streichung ersetzt.

## Wo die Pakete stehen

33 Pakete. Der Trockenlauf zählt **11 offen, 3 gebaut, 17 fertig, 2 blockiert** — Summe 33,
also geht kein Frontmatter daneben.

**Vier Bauplätze, zum ersten Mal alle vier belegt:**

| Rolle | Paket |
|---|---|
| architekt | 0011 Stack auf C++ |
| testentwickler | 0019 Vorratsverfahren-Profilliste |
| spielentwerfer | 0021 Schaden-Gegenkraft 5 |
| kernbauer | 0027 Zustand-Schreibweg schliessen |

**Drei Reviewplätze, alle belegt** — 0025, 0030 und **0009**. Das ist die Auflösung eines
Staus, den ich zwei Läufe lang gemeldet habe: `reviewbereit()` sortiert nach der Zahl der
bisherigen Urteile, und 0009 stand mit zwei Rückläufen hinter fünf Paketen, die noch nie
geprüft worden waren. Mit den drei Abnahmen dieses Laufs sind es nur noch zwei — 0009 kommt
dran. Es ist sein dritter und nach `RUECKLAUF_MAX` letzter Versuch: Ein weiterer Rücklauf
heisst nicht „noch einmal", sondern `blockiert` und eine Meldung an den Geschäftsführer,
dass das Abnahmekriterium das Problem ist und nicht der Bauagent.

**In Reserve, startbereit, aber ohne Platz:** 0032 und 0033. Beide verlieren nur am
Dateinamen — `startbereit()` nimmt die ersten vier nach `sorted(glob("*.md"))`. Das ist der
gute Fall der Regel „halte mehr offen, als gearbeitet werden kann"; kein Bauagent läuft leer,
und fällt ein Platz aus, rückt sofort etwas nach.

**Wartend auf ein Paket, das gerade läuft:** 0026 (an 0011 und 0025), 0029 und 0031 (beide
an 0019), 0028 (an 0009), 0010 (an 0002, blockiert).

**Blockiert, beide weiter zu Recht:**

- **0002** (`kern::werte`) — wartet auf die Klasse-2-Entscheidung des Architekten. Baut man
  es vorher, ändert sich sein Abnahmekriterium **nachdem** es gebaut wurde; `fondsvermoegen`
  hat fünf Leser, Nacharbeit daran ist die teuerste im ganzen Kern.
- **0003** (Einheiten im Typ) — braucht einen ADR gegen T5, und den erlässt der Betreiber
  oder niemand. Zu entscheiden ist nichts, solange T5 gilt.

## 0033 — warum `schritt` jetzt ein Paket hat und was es nicht ist

Der letzte Plan hat es ohne Kennung verlangt: *„`schritt` braucht ein Paket. Bauen lässt es
sich erst nach 0002 — schreiben lässt es sich jetzt."* Der erste Halbsatz stimmt für die
ganze Runde. Für den **Rahmen** stimmt er nicht, und das ist der Fund dieses Laufs.

**Im Modus `weltlauf` entfallen Schritt 2 (Aktionen) und Schritt 6 (Abrechnung)** — T38 sagt
das ausdrücklich und rechnet die Sollmaske dazu vor: 175 der 310 Adressen. Damit braucht der
Rahmen

- **kein `kern::werte`** (Paket 0002, blockiert) — die Abrechnung läuft in diesem Modus nicht,
- **keinen Aktionstyp** (T32, unbeauftragt) — die Aktionen laufen in diesem Modus nicht,
- **keinen Zufall** — im `weltlauf` wird nach T38 kein einziger Strom gezogen,

sondern nur `Zustand` (0008, `fertig`) und `Schreiber` (0016, `fertig`). **Beide stehen seit
heute.** Der Rahmen hängt an nichts Blockiertem.

Gebaut wird eine Runde, die jede Maskenadresse über `Schreiber::vortrag` unverändert
fortschreibt — 175 Ursachensätze, die aussagen, dass sich nichts geändert hat. Das ist keine
Attrappe, sondern die Bauweise, die T18 für unveränderte Größen vorschreibt: *„unverändert
ist eine Aussage und keine Lücke."* Die sechs Schritte stehen als sechs benannte Funktionen
da, jede mit ihrem Adressblock aus T38 im Kommentar. Wer später Schritt 4 baut, ersetzt
dessen Vortragsblock und fasst nichts anderes an.

**Das Abnahmekriterium hat einen unabhängigen Erwartungswert**, und das war mir wichtig:
Eine Runde, die nur vorträgt, darf die FNV-1a-64-Prüfsumme des Zustands **nicht ändern**.
Das folgt aus T12 und der Bedeutung von `vortrag`, nicht aus dem Code des Pakets. Und die
Bedingung fällt in dem Moment, in dem der erste Schritt anfängt zu rechnen — genau dann soll
sie fallen, und das Folgepaket zieht sie nach.

**Zwei Bedingungen schützen davor, dass das Gerüst für eine Welt gehalten wird.** Der
`spielmodus` muss hart abbrechen und im Wortlaut sagen, dass die Schritte 2 und 6 noch kein
Paket haben — ein stilles Vortragen aller 310 sähe aus wie eine gerechnete Spielrunde und
wäre keine. Und `grep` darf in `schritt.cpp` weder `.feld[` noch `.schreibe(` finden: Paket
0027 dichtet diesen Weg gerade ab und nennt in seiner Begründung wörtlich den Fall, den 0033
sonst wäre.

**Warum ich es geteilt habe, statt die ganze Runde zu beauftragen:** Hausregel — ein Paket,
ein Agent, ein Lauf. 0019 ist dreimal an derselben Stelle abgebrochen, weil es zu groß war,
und beim dritten Mal stand meine Reihenfolgevorgabe schon drin. Die sechs Schritte der Runde
sind sechs Pakete, nicht sechs Absätze.

## Zum Vorrang des Geschäftsführers

Seine fünf Kennungen waren 0011, 0025, 0026, 0029, 0031. Umgesetzt ist, was umsetzbar war —
und das ist genau eine:

| | Stand | warum |
|---|---|---|
| 1. 0011 | **läuft** | einziger Bauplatz des Architekten, belegt |
| 2. 0025 | **im Review** | das fehlende Urteil, erster von drei Reviewplätzen |
| 3. 0026 | wartet | hängt an 0011 **und** 0025, beide erst in diesem Lauf unterwegs |
| 4. 0029 | wartet | hängt an 0019, das gerade gebaut wird |
| 5. 0031 | wartet | angenommen und `offen`, hängt an 0019 |

Drei der fünf sind Folgeglieder von Paketen, die erst in diesem Lauf laufen — der Vorrang
war insoweit eine Reihenfolge für den *nächsten* Lauf, nicht für diesen. Der frei gewordene
vierte Bauplatz ging an 0027, weil es das einzige weitere startbereite Paket war, als es
vergeben wurde. **Das ist keine Abweichung vom Vorrang**, sondern die Antwort auf die Frage,
was auf einen Platz kommt, den keine der fünf Kennungen erreichen konnte.

## Was der Geschäftsführer entscheiden lassen muss

**Die Rohdaten — unverändert und jetzt der einzige Punkt.** `daten/` enthält nach elf
Bauläufen fünf Textbefunde und `reihen.toml`, also Metadaten über Reihen und **keine einzige
Datenzeile**. Deshalb hat der Jahrgangsbau 1997 weiter kein Paket, und die drei Prüfrollen
(`selbstspieler`, `rueckvergleicher`, `bruchtester`) haben nichts zu prüfen.

Kein Gate: `daten.md` nennt für alle vier tragenden Quellen ausdrücklich keine Registrierung
und kein Abonnement, also kein Geld und keine Anmeldung. Die Frage ist allein, welche Hand
lädt — ein Ladeschritt im Runner oder der Betreiber einmal von Hand nach `daten/roh/`. Der
letzte Plan empfiehlt die Hand, mit dem Argument, dass sie zugleich beantwortet, ob die vier
Quellen so aussehen wie beschrieben. **Ich schliesse mich an und habe nichts hinzuzufügen**;
es ist der zweite Plan in Folge, in dem der Punkt oben steht.

**Was ich diesmal nicht mehr melde:** Die Frage, ob `technik.md` weiter Rust sagt, ist bei
0011 im Bau, und der Architekt hat seinen Platz. Die Frage nach `ops/baulauf.log` hat der
Betreiber am 2026-09-02 um 19:13 von Hand beantwortet.

## Was quer liegt, aber keine Entscheidung braucht

**Der Nebenbefund zu 0020 wird kein Paket, und das ist die Empfehlung des Prüfers.**
`anteile_aus_zustand` sichert die Summe zweifach, nicht aber den Quotienten;
`mal_geteilt(wert, 10.000, summe)` bricht nach T7 hart ab, wenn das Ergebnis nicht in `i64`
passt. Der Abbruch ist laut und regelkonform, zeigt aber auf `festkomma` statt auf die
Sektoranteile — das Muster, das T30 bei Schranke 5 beim Namen nennt. Im heutigen Zuschnitt
ist der Fall unerreichbar, weil die Probe ihre Zustände selbst setzt; scharf wird er erst,
wenn die Prüfung aus der Probe in ein aufrufbares Modul wandert. **Die dritte Wache gehört
in das Paket, das diese Verschiebung baut** — ein eigenes Paket über drei Zeilen kostet mehr,
als es bringt.

**Der Scheduler hat weiter keine Vorfahrt.** `baulauf.py:267` nimmt `startbereit(...)[:4]`
über `sorted(glob("*.md"))`; wer vorn im Alphabet steht, kommt zuerst dran. In diesem Lauf
schadet es nicht — die vier Belegten sind vier, die ohnehin laufen sollten. Es ist trotzdem
der Grund, warum 0032 und 0033 warten, und beide sind kleiner als das, was vor ihnen steht.
Ein Vorschlag dazu bleibt aus: Künstlich blockieren wäre eine Lüge im Statusfeld, rückwärts
nummerieren bricht die Konvention.

**Die `.tmp`-Dateien liegen weiter im Repo**, zwei davon in `aufgaben/` (`.kopf.tmp`,
`.paket.tmp`). Unschädlich, weil `baulauf.py` über `glob("*.md")` läuft — die Summe 33 des
Trockenlaufs geht ohne sie auf. Bemerkenswert nur, weil `.paket.tmp` in seinem Kopf
`daten/reihen.toml` beansprucht, also dieselbe Datei wie das neu angenommene 0032. Eine
Zwischendatei, die eine Kollisionsangabe trägt, sieht aus wie ein Anspruch und ist keiner.

**Fünf Rollen haben kein Paket, und das ist weiter richtig.** `oberflaechenbauer` steht in
T13 als letzter Kasten der natürlichen Reihenfolge; `auslieferer` hat nichts auszuliefern;
die drei Prüfrollen brauchen eine gespielte Partie. Allen fünf fehlt eine Voraussetzung
**nachweisbar** — und für die drei Prüfrollen ist 0033 der erste Schritt darauf zu.

## Die eine Zahl

**Sieben von neun Kernkästen tragen Code, den sechsten Lauf in Folge unverändert — aber der
Grund ist ab heute nur noch ein halber.** `werte` (78 Byte) bleibt blockiert, bis der
Architekt entschieden hat. `schritt` (63 Byte) ist seit diesem Lauf **beauftragt**: 0033
baut den Rundenrahmen, hängt an nichts Blockiertem und braucht weder `werte` noch einen
Aktionstyp noch den Zufall.

Eine Spielrunde ist noch immer nie gerechnet worden. Eine **Weltlaufrunde** kann es ab dem
nächsten Lauf sein, an dem 0033 einen Platz bekommt — und der Nachweis dafür ist eine Zahl,
die kein Agent dieses Vorhabens erfinden kann: 175 Ursachensätze und eine Prüfsumme, die
sich nicht bewegt hat.
