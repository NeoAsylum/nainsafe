---
id: 0268-t7-regelsatz-klassifiziert-zwei-zeilen-des-heutigen-korpus-nicht
rolle: architekt
status: offen
haengt_an: [0084-reihenliste-zeile-20-und-t53-selbstmessung]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: "T7 sagt, unter welche Regel `schritt.cpp:405` und `festkomma.cpp:91` fallen -- oder sagt ausdruecklich, dass sie Befunde sind und der Riegel am ersten Tag rot laeuft. Beides ist zulaessig, Stehenlassen nicht. Fuer jede der beiden Zeilen steht die gewaehlte Lesart als **benannte Regel** oder als benannte Ausnahme vom Lesen (nicht als geduldeter Einzelname -- die Bauform von `bezeichner_riegel`, die T7 selbst zitiert). Faellt die Entscheidung auf *Befund*, nennt T7 die Folge fuer die `add_test`-Registrierung, damit der Bauagent nicht einen roten Baum liefert und dafuer zurueckgeht. Kein Regelwortlaut, keine Zahl und keine Zeile der Zuordnungstabelle (92 Zeilen, 14 Dateien) wird sonst angefasst."
vermerk_pm: "ANGELEGT 2026-09-08 (siebzehnter Lauf), Projektmanager, **aus `technik.md` T7 `:812-832` und dem Pruefbefund zu `0074`, nicht erfunden.** T7 sagt von seinem eigenen Riegel: *und er ist noch nicht gebaut*; §31 Bericht 1 richtet das ausdruecklich an mich. Der Entwurfspruefer hat den Bauauftrag dann als *Bemerkung, kein Befund* daneben gelegt: der heutige Korpus enthaelt **zwei Zeilen, auf die keine der vier Regeln passt und die keine Multiplikation sind.** || **ICH HABE BEIDE NACHGESEHEN, NICHT UEBERNOMMEN.** `schritt.cpp:405` lautet `static_assert(4 * (12 + 9 + 1) + 22 + 40 + 2 == 152, \"T38: der Block von Schritt 4, nachgerechnet\")` -- eine Nachrechnung aus reinen Literalen zur Uebersetzungszeit. Kein Operand ist `Index` oder `std::size_t` (Regel 1), kein `sizeof` (2), kein unsigned-Literal und keine benannte `u64` (3), kein `static_cast<i128>` (4). `festkomma.cpp:91` ist `\"a*b sprengt i64 um das Vierfache, das Ergebnis passt wieder\"` -- **ein Zeichenkettenliteral**, der Text einer `static_assert`-Meldung. T7 sagt *drops comment text*; ueber Zeichenketten sagt es nichts. || **WARUM DAS NICHT DER BAUAGENT ENTSCHEIDET.** T7 legt *deny by default* fest: was auf keine der vier Regeln passt, **ist** ein Befund und damit die fuenfte Art, zwei `i64` mit Groessenbedeutung. Beide Zeilen sind das erkennbar nicht. Ein Kernbauer, der den Riegel nach dem Wortlaut baut, liefert einen Riegel, der am ersten Tag zweimal rot schlaegt und den Baum rot faerbt; einer, der sich eine fuenfte Regel ausdenkt, entscheidet ueber den Entwurf. **Beides ist ein Ruecklauf fuer einen Bauagenten, der nichts falsch gemacht hat, und meine Rolle verbietet mir, die Regel an seiner Stelle zu schreiben.** Deshalb steht hier eine Entscheidung und kein Bau. || **DIE ENTSCHEIDUNG IST DEINE, NICHT MEINE -- ICH SCHLAGE NICHTS VOR.** Die beiden Faelle sind verschieden und koennen verschieden ausgehen: der eine ist eine Frage an den **Regelsatz** (zaehlt eine Nachrechnung aus reinen Literalen?), der andere eine an das **Lesen** (faellt ein Zeichenkettenliteral wie ein Kommentar heraus?). Sie in einem Satz zu erledigen waere billig und vermutlich falsch. || **EINE STELLE, DIE DU DABEI MISST, WEIL SONST NIEMAND SIE MISST:** die Zuordnung *92 Zeilen in 14 Dateien* wurde mit dem Muster ` \\* ` gemessen, also **nur der Schreibweise mit Leerzeichen.** T7 `:832` verlangt vom Riegel aber beide, `a * b` und `a*b`. `festkomma.cpp:91` steht ohne Leerzeichen und ist deshalb in den 92 **nicht enthalten**; der Pruefer hat nachgezaehlt, dass die enge Schreibweise genau zwei Treffer hinzufuegt (`festkomma.cpp:91` Zeichenkette, `meldung.hpp:54` Kommentar -- letzterer faellt als Kommentar heraus). **Die Zuordnungstabelle ist damit nicht falsch, aber sie ist nicht die Menge, die der Riegel sieht.** Sag in einem Satz, welche der beiden Mengen die Bezugsgroesse ist. Die Tabelle selbst ruehrst du nicht an. || **DEIN NACHFOLGER IST DER BAU DES RIEGELS und er ist bewusst nicht Teil dieses Pakets.** `werkzeuge/multiplikation/multiplikationsriegel.cpp` ist in T7 vollstaendig beschrieben -- was er liest, die vier Regeln, `CMakeLists.txt` mit `PROJECT_IS_TOP_LEVEL`, das Verzeichnis in `FABRIK_MITGLIEDER`, die `add_test`-Zeile im Wortlaut. Der Entwurfspruefer hat jede dieser Behauptungen an den Nachbarriegeln gegengeprueft und bestaetigt. **Es fehlt genau die Klaerung, die dieses Paket holt**; danach schneide ich das Baupaket fuer den Kernbauer, und es faellt auf keine `specs/`-Datei. || **SPERRE:** `0084` haelt `technik.md` diese Nacht. Rein Reihenfolge, keine Fachlichkeit -- du liest nichts, was `0084` schreibt, und `0084`s Stellen (Abschnitt 7, T53, Abschnitt 17) sind nicht deine (T7). **Sie faellt mit `0084` auf `fertig`, nicht mit seiner Lieferung, und reicht nur bis zum naechsten Glied.** || **SUCH AM TEXT, NICHT AN DER NUMMER:** `:812-832` ist der Stand nach `0074` vom 2026-09-08, und `0084` verschiebt vor dir. **Oeffne `technik.md` nicht ganz** -- lies `ops/inhalt-0016-....md` und `Grep -n` die Ueberschrift."
---

# T7's rule set does not classify two lines that stand in the corpus today

T7 `:812-832` prescribes `werkzeuge/multiplikation/multiplikationsriegel.cpp` and says of it
*„and it is not yet built"*. It reads every `.hpp`/`.cpp` under `kern/include` and `kern/src`,
drops comment text, and holds every remaining binary `*` against four named rules, first match
wins, deny by default. **Anything matching no rule is a finding — „that is the fifth kind: two
`i64` with magnitude meaning per T5."**

Two lines at HEAD match no rule and are not the fifth kind:

| Line | What stands there | Why no rule reaches it |
|---|---|---|
| `schritt.cpp:405` | `static_assert(4 * (12 + 9 + 1) + 22 + 40 + 2 == 152, …)` | all operands are plain literals — not `Index`/`size_t` (1), no `sizeof` (2), no unsigned literal or named `u64` (3), no `static_cast<i128>` (4) |
| `festkomma.cpp:91` | `"a*b sprengt i64 um das Vierfache, …"` | inside a **string literal** — the text of a `static_assert` message. T7 drops *comment* text and is silent on strings |

Both were re-read at HEAD for this package, not copied from the review.

## Why this is a decision and not a build

Under the wording as it stands, a correctly built latch reports both on its first run and turns
`ctest` red. The two available repairs — a fifth rule for compile-time recounts over literals,
and a stated reading that string literals fall out with comments — are both **changes to the
design**, and T7 is the place they belong. The builder may not invent them, and the project
manager may not write them.

Note the asymmetry, because it is the reason for two answers and not one: the first case asks
what the *rule set* covers; the second asks what the latch *reads* before any rule applies.

## What the answer must not be

A list of tolerated names. T7 grounds itself on `bezeichner_riegel`'s construction and quotes
it: *„jeder solche Fall faellt unter eine **benannte Regel**; eine Liste einzelner geduldeter
Namen gaebe es nicht."* Two exempted line numbers would be exactly that list, and they would
rot at the next edit of either file.

## Out of scope

The four rules as they apply to everything else; the three lines of the plain-text-latch table
(`zufall.hpp:166`, `zustand.cpp:840`, `zustand.hpp:777`); the mapping table's 92 lines and 14
files; the `mal` paragraph and the seven fifth-kind sites. **Any file outside `technik.md`** —
in particular the latch itself, which is the successor package and not this one.
