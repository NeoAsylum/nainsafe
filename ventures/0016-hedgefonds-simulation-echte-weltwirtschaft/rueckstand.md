# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02 abends, geschrieben vom Projektmanager. Fassung 4. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

## Was dieser Lauf getan hat

**Vier Prüfbefunde ausgewertet, drei davon `geprueft`.** Das ist die erste Nacht, in der
mehr Pakete abgenommen als zurückgewiesen wurden — und 0004 ist das erste Paket dieses
Vorhabens, das **ohne einen einzigen Nebenbefund** durchgeht.

| Paket | von | nach | Grund |
|---|---|---|---|
| 0004 Gerüst + Festkomma | `gebaut` | **`fertig`** | Runde 2 `geprueft`, **0 Befunde**; Bedingung 5–7 über den Übersetzungslauf |
| 0006 Deckung 1997 | `gebaut` | **`fertig`** | Runde 2 `geprueft`, 1 Nebenbefund → geht in 0017 |
| 0014 Lizenz, übrige Reihen | `gebaut` | **`fertig`** | `geprueft`, 4 Befunde → drei werden 0018, einer geht an den Architekten |
| 0009 `parameter.toml` | `gebaut` | **`offen`** | Runde 2 `zurueck`, **Rücklauf 2 von 3** |
| 0003 Einheiten | `blockiert` | `blockiert` | unverändert; `dateien` von `einheiten.rs` auf die drei C++-Dateien korrigiert |
| 0008 Zustand | `offen` | `offen` | **nicht gebaut** — nachgesehen, `zustand.hpp` ist unverändert die 2-Zeilen-Platzhalterdatei |

**Zwei neue Pakete**, beide aus Prüfbefunden bestandener Pakete:

- **0018 Klärungsliste Lizenzbefund** (datenbauer, hängt an 0014) — Befunde 1, 3 und 4 des
  Prüfers. Kein Rücklauf: 0014 hat sein Kriterium erfüllt, und ein Rücklauf darauf wäre
  eine Kriterienerhöhung. Der Fund ist Befund 1 und er ist teuer, wenn er stehen bleibt:
  Die Klärungsliste ist nach Kosten geordnet und empfiehlt damit den Schritt, der **nichts**
  hebt.
- **0017 wurde geschärft, nicht neu angelegt.** Der Nebenbefund zu 0006 nennt zwei Reihen
  ohne Umrechnungsfaktor, und die Umrechnungsspalte entsteht ohnehin in 0017. Punkt 4 und
  Abnahme 3 nennen jetzt vier Reihen namentlich mit der Zahl, die dort stehen muss.

**Ich habe 0008 nicht auf `gebaut` nachgezogen, obwohl ein Commit so heisst.** `fc61eaf`
trägt den Betreff „kernbauer: 0008-kern-zustand-310-felder" und enthält `parameter.toml`
und das Paket 0009 — die Arbeit eines gleichzeitig laufenden Datenbauers. Der Kernbauer
notiert dasselbe Muster zweimal in seinem Logbuch: Der Baulauf committet nicht paketweise,
sondern nimmt mit, was im Baum liegt. **Die Commit-Zuordnung belegt nicht, wer geschrieben
hat.** Nachgesehen habe ich stattdessen die Datei: `kern/include/kern/zustand.hpp` hat
zwei Zeilen und ist der Platzhalter aus dem Gerüstpaket. 0008 bleibt `offen` und ist im
nächsten Lauf wieder das erste Kernpaket.

## Wo die Pakete stehen

| Paket | Rolle | Status | woran es hängt |
|---|---|---|---|
| 0001 Entwurfsabnahme | spielentwerfer | `fertig` | — |
| 0002 Fondsbewertung | kernbauer | `blockiert` | Klasse-2-Entscheidung |
| 0003 Einheiten | kernbauer | `blockiert` | ADR gegen T5, oder gar nicht |
| 0004 Gerüst + Festkomma | kernbauer | **`fertig`** | — |
| 0005 WDI-Lizenz | datenbauer | `fertig` | — |
| 0006 Deckung 1997 | datenbauer | **`fertig`** | — |
| 0007 Adressverzeichnis | datenbauer | `fertig` | — |
| 0008 Zustand, 310 Felder | kernbauer | `offen`, **startbereit** | — |
| 0009 `parameter.toml` | datenbauer | **`offen`**, startbereit | Rücklauf 2 |
| 0010 Zustandsausgabe | kernbauer | `offen` | 0002 (blockiert) + eine Entwurfsfrage |
| 0011 Stack auf C++ | **architekt** | `offen`, **nicht einplanbar** | `BAUROLLEN` |
| 0012 Zufall | kernbauer | `offen`, startbereit | — |
| 0013 Prüfsumme | kernbauer | `fertig` | — |
| 0014 Lizenz, übrige Reihen | datenbauer | **`fertig`** | — |
| 0015 Markierungssatz | datenbauer | `offen`, startbereit | — |
| 0016 `kern::schreiber` | kernbauer | `offen` | 0008 |
| 0017 Reihenliste | datenbauer | `offen`, **startbereit** | — (0006 und 0014 sind fertig) |
| 0018 Klärungsliste | datenbauer | **neu**, `offen`, startbereit | — |

`python3 agents/baulauf.py 0016-… --trocken` meldet 9 offen, 7 fertig, 2 blockiert und
zieht vier Baupakete: **0008, 0009, 0012, 0015** — zwei Kernpakete und zwei Datenpakete,
keine zwei in derselben Datei. Kein Review, weil kein Paket auf `gebaut` steht; das ist
richtig so und heisst nur, dass alle vier Befunde ausgewertet sind. **Im Vorrat liegen
0016, 0017 und 0018**, davon zwei startbereit. Kein Bauagent läuft leer, und wenn zwei
Pakete schneller fertig werden als geplant, ist nachgeschoben.

## Die Reihenfolge und warum sie so ist

```
0009 Rücklauf 2 ─┐
0015 Markierung  ├─ frei, keine Abhängigkeit
0012 Zufall      │
0017 Reihenliste ┤  (0006 + 0014 fertig)
0018 Klärung     ┘  (0014 fertig)

0008 Zustand ──> 0016 Schreiber ──> (schritt, später)
             └─> 0002 Werte [BLOCKIERT] ──> 0010 Ausgabe
```

**Der Kern hängt an einem einzigen Paket.** 0008 ist die Wurzel von allem, was danach
kommt: 0016 (`schreiber`) wartet darauf, 0002 (`werte`) wartet darauf und ist zusätzlich
blockiert, und 0010 hängt an 0002. Solange 0008 nicht steht, bleiben von den sechs
Kernpaketen genau zwei baubar — 0008 selbst und 0012 (`zufall`, hängt an nichts). Es ist
seit zwei Läufen eingeplant und beide Male nicht gebaut worden; falls das ein drittes Mal
passiert, ist die Ursache im Runner zu suchen und nicht im Rückstand.

**Die Datenseite ist entkoppelt und trägt gerade den Fortschritt.** Vier der sieben
fertigen Pakete sind Datenpakete, und mit 0017 und 0018 stehen zwei weitere bereit, die
nichts vom Kern brauchen. Das ist die Reserve, aus der ein leerlaufender Baulauf bedient
wird.

## Was der Geschäftsführer entscheiden lassen muss

**1. Wie kommen die Entwurfsaufgaben in einen Lauf?** Unverändert, zum vierten Mal.
`architekt` und `spielentwerfer` stehen in `REVIEW`, aber nicht in `BAUROLLEN`
(`baulauf.py:49`, heute nachgesehen: unverändert). Daran hängen inzwischen **sechs**
Sachen: 0011 (Stackwechsel in `technik.md`), Punkt 2, 3, 4, 5 und neu Punkt 8. Der Plan
empfiehlt eine Zeile in `baulauf.py`; ich schliesse mich unverändert an.

Der Preis ist seit dem 2026-09-02 beziffert und unverändert: ein blockiertes Paket
(0002) auf dem kritischen Pfad des Kerns.

**2. Ein TOML-Parser gehört in den Runner.** *Neu, und es ist derselbe Fall wie der
Compiler am 2026-09-01.* Abnahme 4 von Paket 0009 verlangt gültiges TOML. In **zwei**
Runden konnte es niemand nachweisen — weder der Datenbauer noch der Prüfer: `python3` mit
`tomllib` ist vorhanden, der Aufruf wird von der Umgebung abgewiesen. Beide haben es
stattdessen strukturell belegt und beide haben ehrlich dazugeschrieben, dass das kein
maschineller Nachweis ist.

Die Lehre vom 2026-09-01 sagt genau, was zu tun ist: *Wenn eine Rolle ein Werkzeug nicht
haben darf, ihre Arbeit aber ohne dessen Ausgabe wertlos ist, gehört das Werkzeug in den
Runner und seine Ausgabe in eine Datei.* `baulauf.py:uebersetzen()` ruft schon den
Compiler; drei Zeilen daneben, die jede `*.toml` des Vorhabens durch `tomllib` schicken und
das Urteil in denselben Befund schreiben, schliessen die Lücke — für 0009 und für 0017, das
dieselbe Bedingung trägt. **Kein Gate:** kein Geld, keine Rechtsfolge, keine Aussenwirkung.

**3. Klasse 2 misst zweierlei — laufende und konstante Preise.** Unverändert und weiter
die schwerste offene Sache. T5 nennt Klasse 2 „Tausend USD zu konstanten Preisen"; darin
liegen die 40 Handelsströme aus CEPII BACI („thousands current USD") und die
Wertschöpfungen aus Reihe 1 (konstante Preise). `durchgriff = teile_gerundet(10.000 · H,
H + N)` addiert im Nenner laufende und konstante Preise und fällt in allen zehn Werten
gleichgerichtet zu klein aus; Maß 4 misst Inflation statt Modellgüte. Zwei Prüfer, zwei
Pakete, dieselbe Ursache — und sie blockiert 0002.

**4. Klasse 4 — trägt sie ihren Deckel auch für Regler?** Unverändert offen. Fünf
Klasse-4-Schlüssel in `parameter.toml` tragen `>= 0` ohne obere Schranke, obwohl T5 der
Klasse den Bereich 0 bis 10.000 gibt. Ich habe den Datenbauer angewiesen, sie auch im
zweiten Rücklauf nicht anzufassen; der Prüfer hat bestätigt, dass sie unangetastet sind.

**Ein Nachtrag, damit die Frage nicht mit dem neuen Rücklauf verwechselt wird:** Befund 1
der zweiten Runde betrifft `hebelaufschlag` — **Klasse 3, nicht 4, und die untere statt
der oberen Schranke**. Der Prüfer sagt ausdrücklich, dass er der Klasse-4-Frage nicht
vorgreift. Es sind zwei Sachen, nicht eine.

**5. Reihe 9 und R = 19.** Unverändert. Reihe 9 trägt für Deutschland und China keine
einzige Beobachtung. Nach T24 heisst das: Reihe streichen oder Quelle ersetzen — beides
entscheidet der Spielentwerfer. Die drei Varianten sind durchgerechnet (R = 19 / 20 / 24),
keine reisst `R ≤ 26`. Die zweite Prüfrunde hat R = 19 an vier weiteren, bisher
ungemessenen Zeilen bestätigt; die Zahl steht so fest, wie sie ohne diese Entscheidung
stehen kann.

**6. „Schaden" in Gegenkraft 5 hat keine Rechenvorschrift.** Unverändert offen seit dem
2026-09-01 (`technik.md` Abschnitt 12, Beobachtung 3). Solange es offen ist, ist
Gegenkraft 5 nicht baubar. Es trifft den Kern über `schritt`, also nach 0016.

**7. Wo die Zustandsausgabe wohnt.** Unverändert: 0010 legt die drei Ebenen in den Kasten
`kern`, T13 gibt sie `schnittstelle`. Nicht dringend — 0010 hängt an 0002.

**8. Zwei neue Entwurfsfragen aus den Befunden dieser Nacht.** Beide gehören dem
Architekten und keinem Bauagenten; deshalb stehen sie hier und nicht in einem Paket.

- **Das `frei` in der Spalte „Rolle" der Reihenliste ist die T37-Klasse, kein
  Lizenzurteil** (Prüfbefund zu 0014, Befund 2). Befund 2 der Datei `lizenzbefund-reihen.md`
  trifft die falsche Zelle. **Das ist eine Warnung vor einer Reparatur:** Wer ihn liest und
  das `frei` in der Rolle-Spalte ändert, zerschiesst die Verbindung zwischen Reihenliste
  und T37, während die Spalte, die wirklich falsch ist („Verdacht", an sechs von sechs
  Stellen widerlegt), unberührt bleibt. Paket 0018 schreibt die Klarstellung daneben, ändert
  `technik.md` aber nicht — das darf es nicht.
- **Rundet Reihe 2 vor oder nach der Normierung?** (Prüfbefund zu 0006, Nebenbefund.) Die
  drei WDI-Sektoranteile summieren sich nicht auf 100; die Normierung auf 10.000 verschiebt
  jeden der zwölf Werte, und die Reihenfolge von Rundung und Normierung entscheidet über
  die Zahlen. `technik.md` Z. 698 setzt die Normierung voraus und sagt nichts über die
  Reihenfolge. 0017 trägt beide Schritte getrennt ein und markiert die Stelle als offen;
  entscheiden muss es der Architekt, bevor der Jahrgangsbau gebaut wird.

## Was als Nächstes ansteht und noch kein Paket ist

**Die Rohdaten hat niemand, und das ist eine Runner-Frage.** Unverändert aus Fassung 3:
`daten/` enthält fünf Textbefunde und keine einzige Datenzeile; `werkzeuge/aufbereitung`
liest nach T23 „die eingefrorenen Rohdateien". Kein Bauagent kann das erledigen — `Edit`
und `Write` schreiben Text, `WebFetch` liefert Text, eine Shell hat keine Baurolle, und
BACI kommt als Archiv je HS-Fassung. Ein Paket dafür anzulegen hiesse, Arbeit
auszuschreiben, die niemand ausführen kann. **Kein Gate:** `daten.md` sagt für alle vier
tragenden Quellen ausdrücklich keine Registrierung und kein Abonnement.

Es ist dieselbe Hand am Runner wie Punkt 1 und Punkt 2 — drei Sachen, ein Eingriff.

**Der Jahrgangsbau selbst** (`werkzeuge/aufbereitung`) wird schreibbar, sobald 0017 die
Eingabetabelle liefert, und braucht nichts vom Kern. Sein Abnahmekriterium braucht aber
Daten, an denen er laufen kann — deshalb steht er hinter der Rohdatenfrage.

**Eine Kleinigkeit, die zum Befund wird, sobald jemand die Regel aufstellt.** Der
Kernbauer notiert sie und durfte sie in 0004 nicht anfassen: `kern/CMakeLists.txt`
Zeile 38–41 zitiert die Grep-Regel `reinterpret_cast|const_cast|new|delete|asm` im
Klartext. Heute trifft sie keine Bedingung; wer daraus ein Abnahmekriterium macht, baut
sich einen Blindtreffer wie die vier aus Rücklauf 1 von 0004. Wer die Regel aufstellt,
räumt die Zeile mit auf.

## Zwei Sachen, die vom Tisch bleiben

- **Der Übersetzungslauf** ist grün (`befunde/uebersetzung-2026-09-02.md`: `cmake`,
  `--build` und `ctest` je zweimal Code 0, 2/2 Tests) und trägt jetzt drei
  Abnahmebedingungen von 0004. Der Prüfer hat dazugesagt, was er damit **nicht**
  behauptet — grün heisst „die Zahlen passen zueinander", nicht „die Zahlen sind richtig".
- **Die Rücklaufgrenze** `baulauf.py:RUECKLAUF_MAX = 3` steht. Stand nach diesem Lauf:
  **0009 zwei**, 0004 und 0006 je einer (beide jetzt `fertig`, der Zähler ist damit
  erledigt), alle übrigen null. **0009 ist damit einen Rücklauf vom `FESTGEFAHREN`
  entfernt** — der Runner plant es dann nicht mehr ein, und zu prüfen wäre das
  Abnahmekriterium statt der Arbeit. Ich habe den Satz in das Paket geschrieben, damit der
  Datenbauer es weiss. Nach der Lage ist das unwahrscheinlich: Beide Rückläufe hingen an
  derselben Abnahmebedingung 3, beide Male an einer einzigen Zeile, und der zweite Befund
  bestätigt alle drei Reparaturen des ersten.
