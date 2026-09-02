# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, sechster Baulauf. Fassung 5, geschrieben vom Projektmanager. Diese Datei
sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

## Was dieser Lauf getan hat

**Ein Prüfbefund, `geprueft`.** 0012 (`kern::zufall`) geht auf `fertig` — mit dem
gründlichsten Befund, den dieses Vorhaben bisher gesehen hat: Der Prüfer hat alle vier
zitierten Quellen selbst abgerufen und den ersten xoshiro-Schritt aus dem gedruckten
Saatzustand von Hand nachgerechnet. Beide Befunde richten sich an mich und nicht gegen die
Artefakte.

**0008 hat geliefert und bleibt trotzdem `gebaut`.** `zustand.hpp` trägt 726 Zeilen,
`zustand.cpp` 842, die Probe 521 — das ist Arbeit und kein Platzhalter, ich habe in die
Dateien gesehen. Der Prüfer bekommt es in diesem Lauf; `fertig` setze ich erst mit seinem
Befund. Damit ist die Sorge aus Fassung 4 erledigt: 0008 war nicht festgefahren.

**Zwei neue Pakete, und beide für eine Rolle, die noch nie gelaufen ist.** `testentwickler`
steht seit dem ersten Baulauf in `BAUROLLEN` (`baulauf.py:49`) und in `REVIEW` (Zeile 62,
→ `test-pruefer`) und hatte bis heute kein einziges Paket. Das war ein Fehler von mir, und
er ist teuer geworden: Der Kern hat gerade keine baubare Aufgabe, und die Rolle, deren
Arbeit von keinem Kernpaket abhängt, lag brach.

- **0019 Vorratsverfahren und Profilliste** (T43, T36) — `haengt_an: []`, **sofort baubar**.
  Es rechnet mit fünf Ganzzahlen und drei Steckplätzen, kennt den `Zustand` nicht, ruft
  `schritt` nicht auf, und `spiel.md` sagt ausdrücklich „Es wird nie gerundet und nie
  gezogen" — also braucht es nicht einmal `kern::zufall`. Maß 2 und Maß 3 stehen später
  vollständig darauf. Legt den Kasten `pruefstand` an, den die `CMakeLists.txt` des
  Arbeitsbereichs schon führt und überspringt (Zeile 36–51), solange er fehlt.
- **0020 Die sieben Wertebereichsschranken** (T30 Prüfung 2, Teilmenge) — hängt an 0008,
  also baubar, sobald 0008 `fertig` ist. Eine Datei unter `kern/test/`, kein neues
  Kernmodul: Der Modulschnitt gehört dem Architekten, die Probe nicht.

Warum eine Teilmenge: T30 Prüfung 2 nennt zehn Sachen, vier davon brauchen einen
gerechneten Weltschritt, `fondsvermoegen()` aus dem blockierten 0002 oder eine gespielte
Partie. Die sechs übrigen lesen nur einen `Zustand`. Sie jetzt zu bauen kostet nichts und
schneidet nichts ab.

## Wo die Pakete stehen

| Paket | Rolle | Status | woran es hängt |
|---|---|---|---|
| 0001 Entwurfsabnahme | spielentwerfer | `fertig` | — |
| 0002 Fondsbewertung | kernbauer | `blockiert` | Klasse-2-Entscheidung |
| 0003 Einheiten | kernbauer | `blockiert` | ADR gegen T5, oder gar nicht |
| 0004 Gerüst + Festkomma | kernbauer | `fertig` | — |
| 0005 WDI-Lizenz | datenbauer | `fertig` | — |
| 0006 Deckung 1997 | datenbauer | `fertig` | — |
| 0007 Adressverzeichnis | datenbauer | `fertig` | — |
| 0008 Zustand, 310 Felder | kernbauer | `gebaut`, **im Review** | — |
| 0009 `parameter.toml` | datenbauer | `offen`, startbereit | Rücklauf 2 von 3 |
| 0010 Zustandsausgabe | kernbauer | `offen` | 0002 (blockiert) + eine Entwurfsfrage |
| 0011 Stack auf C++ | **architekt** | `offen`, **nicht einplanbar** | `BAUROLLEN` |
| 0012 Zufall | kernbauer | **`fertig`** | — |
| 0013 Prüfsumme | kernbauer | `fertig` | — |
| 0014 Lizenz, übrige Reihen | datenbauer | `fertig` | — |
| 0015 Markierungssatz | datenbauer | `offen`, startbereit | — |
| 0016 `kern::schreiber` | kernbauer | `offen` | 0008 |
| 0017 Reihenliste | datenbauer | `offen`, startbereit | — |
| 0018 Klärungsliste | datenbauer | `offen`, startbereit | — |
| 0019 Vorrat + Profile | **testentwickler** | **neu**, `offen`, startbereit | — |
| 0020 Wertebereichsschranken | **testentwickler** | **neu**, `offen` | 0008 |

`python3 agents/baulauf.py 0016-… --trocken` meldet 9 offen, 1 gebaut, 8 fertig, 2
blockiert — Summe 20, also alle Paketdateien, kein Frontmatterfehler.

## Die Reihenfolge und warum sie so ist

```
0009 Rücklauf 2 ─┐
0015 Markierung  │
0017 Reihenliste ├─ frei, keine Abhängigkeit
0018 Klärung     │
0019 Vorrat      ┘  (Prüfstand, braucht den Kern nicht)

0008 Zustand [im Review] ──> 0016 Schreiber
                         ├─> 0020 Schranken
                         └─> 0002 Werte [BLOCKIERT] ──> 0010 Ausgabe
```

**Der Kern hängt weiter an 0008, aber der Fortschritt nicht mehr.** Bis zu diesem Lauf war
0008 die einzige Wurzel: Ging es nicht durch, stand alles. Mit 0019 gibt es einen zweiten
Strang, der ohne den Kern auskommt — und er trägt mit dem Vorratsverfahren ein Stück, auf
dem Maß 2 und Maß 3 später vollständig stehen. Das ist der eigentliche Ertrag dieses Laufs.

## Was der Geschäftsführer entscheiden lassen muss

**1. Wie kommen die Entwurfsaufgaben in einen Lauf?** Unverändert, zum fünften Mal.
`architekt` und `spielentwerfer` stehen in `REVIEW`, aber nicht in `BAUROLLEN`
(`baulauf.py:49`, heute nachgesehen: unverändert). Daran hängen sechs Sachen, darunter das
blockierte 0002 auf dem kritischen Pfad des Kerns. Der Plan empfiehlt eine Zeile; ich
schliesse mich unverändert an.

**2. Ein TOML-Parser gehört in den Runner.** Unverändert. `baulauf.py:befehle()` ruft
`cmake`, `--build` und `ctest` und sonst nichts (heute nachgesehen). Abnahme 4 von Paket
0009 verlangt gültiges TOML; in zwei Runden konnte es weder der Datenbauer noch der Prüfer
maschinell nachweisen, weil der `python3`-Aufruf von der Umgebung abgewiesen wird. Drei
Zeilen neben `uebersetzen()`, die jede `*.toml` durch `tomllib` schicken, schliessen die
Lücke — für 0009 und für 0017, das dieselbe Bedingung trägt. Kein Gate.

**3. Neu und heute zum ersten Mal messbar: der Scheduler hat keine Vorfahrt, und ein
steckengebliebenes Paket verhungert jedes höher nummerierte.** `baulauf.py:257` nimmt
`startbereit(...)[:4]`, und `startbereit` läuft über `sorted(ordner.glob("*.md"))` — also
**Dateinamen-Reihenfolge**, sonst nichts. Der Trockenlauf zeigt es: 0009, 0015, 0017 und
0018 belegen alle vier Bauplätze, 0019 und 0020 kommen nicht dran, obwohl 0019 startbereit
ist und der Rolle gehört, die als einzige ohne den Kern arbeiten kann.

Normalerweise löst sich das von selbst — gebaute Pakete gehen auf `gebaut` und räumen den
Platz. Zwei Beobachtungen des Plans sagen, dass es das hier nicht sicher tut: **0015 hat
zwei Läufe hintereinander nichts geliefert** und bleibt damit `offen`, und **0009 hat
gearbeitet, aber `status: offen` stehen lassen** und blockiert seinen Platz ebenfalls
weiter. Zwei von vier Plätzen können also dauerhaft von Paketen belegt sein, die nicht
vorankommen.

Ich melde das und plane nicht um: Ein Paket künstlich zu blockieren, damit ein anderes
drankommt, wäre eine Lüge im Statusfeld, und die Nummern rückwärts zu vergeben verstösst
gegen die Namenskonvention. Wenn es nach dem nächsten Lauf immer noch so steht, ist es eine
Zeile im Runner (etwa: je Rolle höchstens zwei Plätze) und keine Frage an den Rückstand.

**4. Klasse 2 misst zweierlei — laufende und konstante Preise.** Unverändert und weiter die
schwerste offene Sache; ausgeschrieben in Fassung 4. T5 nennt Klasse 2 „Tausend USD zu
konstanten Preisen", darin liegen die 40 Handelsströme aus CEPII BACI („thousands current
USD"). Maß 4 misst so Inflation statt Modellgüte. **Sie blockiert 0002 und über 0002 das
Paket 0010.**

**5. Klasse 4 — trägt sie ihren Deckel auch für Regler?** Unverändert offen; fünf
Klasse-4-Schlüssel in `parameter.toml` tragen `>= 0` ohne obere Schranke, obwohl T5 der
Klasse 0 bis 10.000 gibt. Nicht zu verwechseln mit dem Rücklaufbefund zu `hebelaufschlag`
(Klasse 3, untere Schranke) — zwei Sachen, nicht eine.

**6. Reihe 9 und R = 19.** Unverändert; Reihe streichen oder Quelle ersetzen, beides
entscheidet der Spielentwerfer. Die drei Varianten sind durchgerechnet, keine reisst
`R ≤ 26`.

**7. „Schaden" in Gegenkraft 5 hat keine Rechenvorschrift.** Unverändert seit dem
2026-09-01 (`technik.md` Abschnitt 12). Solange es offen ist, ist Gegenkraft 5 nicht
baubar, und `schritt` bekommt kein Paket.

**8. Wo die Zustandsausgabe wohnt.** Unverändert: 0010 legt die drei Ebenen in `kern`,
T13 gibt sie `schnittstelle`. Nicht dringend, 0010 hängt an 0002.

**9. Zwei Entwurfsfragen aus den Befunden der Vornacht**, unverändert und ausgeschrieben in
Fassung 4: Das `frei` in der Spalte „Rolle" der Reihenliste ist die T37-Klasse und kein
Lizenzurteil (Warnung vor einer Reparatur, die die Verbindung zu T37 zerschösse), und:
Rundet Reihe 2 vor oder nach der Normierung? Beide gehören dem Architekten.

**10. Neu: Wandert das Vorratsverfahren später aus `pruefstand` heraus?** T43 nennt es
einen Baustein des Prüfstands, T30 Prüfung 5 und 6 geben dem Bruchtester Läufe, die es je
Runde brauchen. Ob es dafür aufgerufen wird oder dort ein zweites Mal entsteht, hat der
Architekt nicht entschieden. **Blockiert nichts** — die Mechanik ist dieselbe, es ist eine
Verdrahtungsfrage. Steht hier, damit sie nicht in Paket 0019 verschwindet. Dieselbe Sorte
Frage stellt sich für die Prüffunktion aus 0020.

## Was quer liegt, aber keine Entscheidung braucht

**Ein Commit trägt zum zweiten Mal die falsche Paketkennung.** `770e7b4` heisst
„kernbauer: 0012-zufall-abgeleitete-stroeme", enthält aber ausschliesslich die drei
`zustand`-Dateien, also die Arbeit an **0008**. Neu daran ist nicht der Fall, sondern wer
ihn gefunden hat: Der Kern-Prüfer ist von selbst darauf gestossen und macht ihn zu seinem
Befund 2. Das Ergebnis kostet es nichts, die Historie schon — „was gehörte zu 0012" ist
genau die Frage, die in einem halben Jahr beim Eingrenzen eines Regressionsbruchs gestellt
wird. Für mich ist es eine Arbeitsregel und keine Bitte an den Runner: **Vor jedem Nachzug
in die Zieldatei sehen, nicht in den Commit-Betreff.**

**Ein Abnahme-Mustervergleich war löchrig, und er hat sich nicht ausgebreitet.** Befund 1
des Prüfers: `^\s*[A-Za-z_]+ [a-z_]+ =` findet `u64 zaehler = 0;` nicht, weil
`[A-Za-z_]+` an der Ziffer abbricht — also ausgerechnet die Typen dieses Kerns. Ich habe
nachgesehen: Der Vergleich steht in **keinem** anderen Paket. Die vom Prüfer korrigierte
Fassung steht ab jetzt in 0019, dort wo er sonst übernommen worden wäre. Kein Rücklauf auf
0012 — der Prüfer hat beide Dateien zusätzlich von Hand durchgesehen, die Bedingung ist
erfüllt.

**Die Rohdaten hat niemand, und das ist eine Runner-Frage.** Unverändert: `daten/` enthält
vier Textbefunde und keine Datenzeile; `werkzeuge/aufbereitung` liest nach T23 „die
eingefrorenen Rohdateien". Kein Bauagent kann das erledigen. Kein Gate — `daten.md` sagt
für alle vier tragenden Quellen ausdrücklich keine Registrierung und kein Abonnement. Es
ist dieselbe Hand am Runner wie Punkt 1 und 2.

**Die Rücklaufgrenze** `RUECKLAUF_MAX = 3` steht. 0009 bei zwei, alles andere bei null oder
erledigt. Der nächste `zurueck` auf 0009 macht es `FESTGEFAHREN`; dann ist mein
Abnahmekriterium zu prüfen und nicht die Arbeit. Der Satz steht im Paket.

**Der Übersetzungslauf ist grün** (`befunde/uebersetzung-2026-09-02.md`). Mit 0019 kommt
eine dritte `CMakeLists.txt` dazu, und `baulauf.py` ruft auf jeder einzeln `cmake`,
`--build` und `ctest` — deshalb steht im Paket ausgeschrieben, dass sie **allein**
durchlaufen muss. Grün heisst weiterhin „die Zahlen passen zueinander", nicht „die Zahlen
sind richtig".
