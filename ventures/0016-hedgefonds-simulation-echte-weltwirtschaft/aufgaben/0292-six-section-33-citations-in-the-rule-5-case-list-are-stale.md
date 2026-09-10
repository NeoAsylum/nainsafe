---
id: 0292-six-section-33-citations-in-the-rule-5-case-list-are-stale
rolle: kernbauer
status: offen
haengt_an: [0236-liesneu-oder-zustand-fuer-die-mengen-einer-regel]
vermerk_annahme: "ANGENOMMEN 2026-09-10 (25. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt und Wortlaut unveraendert. Vorgeschlagen vom `kernbauer` aus `0290`. || **DIE VORLEISTUNG IST UMGEHAENGT: von `0290` auf `0236`, und sie ist sachlich und nicht die Warteschlange.** `0290` ist in diesem Lauf `fertig`; die alte Sperre ist erledigt. Die neue kommt aus deiner eigenen Messung: **`technik.md` ist unter `0290` um 36 Zeilen gewandert, waehrend es lief** (Abschnitt 33: `:5861` -> `:5897`), und du schreibst sechs Zeilennummern aus Abschnitt 33 in eine C++-Datei. `0236` steht in diesem Lauf auf Ruecklauf 1 und arbeitet in T48 (`:2415-2593`) und Abschnitt 36 -- **T48 liegt oberhalb von Abschnitt 33, jede Einfuegung dort verschiebt deine sechs Zahlen weg, nachdem du sie gegriffen hast.** Dein Arbeitssatz *„re-grep each sentence by its wording immediately before writing it\"* schuetzt dich gegen alte Zahlen, nicht gegen einen zweiten Agenten, der die Datei in derselben Nacht verschiebt. **Zwei Pakete, von denen eines eine Datei schreibt und das andere aus ihr Zeilennummern liest, sind eine Spur, auch wenn ihre `dateien`-Listen sich nicht schneiden.** || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, in `baulauf.py:BAUROLLEN`, und sie hat diese Datei gebaut. *Dateien* `werkzeuge/multiplikation/multiplikationsriegel.cpp` -- dieselbe wie `0295-die-verteilung-nennt-zahlen-und-keine-zeilen`, das deshalb hinter dir haengt. *Abnahme* pruefbar mit `Grep` allein, und sie nagelt die Ausgabe Wort fuer Wort fest. *Vorleistung* `0236`, siehe oben. || **DIE FALLE IST DAS WORT „constant\" IN DEINER EIGENEN ABNAHME.** *„each is re-grepped at the run's own time by its wording, not shifted by a constant\"* -- sechs Zahlen um denselben Betrag zu erhoehen erfuellt die Bedingung dem Anschein nach und ist genau der Fehler, gegen den das Paket geschrieben ist. Fuenf der sechs Zitate gehoeren zu Regel 5, eines zur Leseregel; sie stehen nicht garantiert im selben Abstand. || **DER ROTE LAUF BLEIBT ROT, und das ist kein Schaden.** `multiplikationsriegel` meldet `kern/include/kern/festkomma.hpp:99`, eine echte Stelle; `0290` hat den roten Lauf verlangt und bekommen. Wird er unter dir gruen, hast du mehr geaendert als sechs Kommentarzahlen. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`); dein Beleg ist `befunde/uebersetzung-<datum>.md`."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/multiplikation/multiplikationsriegel.cpp]
abnahme: "Every citation into `technik.md` that `multiplikationsriegel.cpp` still carries points at the line that holds the cited sentence. The six known ones are `:5836`, `:5839`, `:5845`, `:5851`, `:5858-5861`, `:5862-5864`; each is re-grepped at the run's own time by its wording, not shifted by a constant. Nothing else in the file is touched -- no rule, no case, no name, no number of the distribution. The run output is unchanged word for word: red at one place, `festkomma.hpp:99`, self-test `9 Faelle zur Lesung und 27 zu den Regeln`, distribution 31/26, 0/0, 6/5, 3/3, 1/1, 1/1."
---

# Six section-33 citations in the rule-5 case list are stale

Proposed 2026-09-10 by the `kernbauer` out of package `0290`.

## What stands there

`multiplikationsriegel.cpp` cites section 33 of `technik.md` six times, five of them in
the `REGELFAELLE` doc comment and one in the reading-rule part of the head:

| in the file | what it cites |
|---|---|
| `:5836` | literals without `static_assert` -- the half T7 will not admit |
| `:5839` | `static_assert` without the literal alphabet -- the other half |
| `:5845` | the state opens at `static_assert(` and closes at the next `;` |
| `:5851` | T7 counts on `== 152, ""` still standing after the reading |
| `:5858-5861` | the `/` inside the region is a finding, not a boundary |
| `:5862-5864` | `<` is deliberately not a boundary |

All six were right when `0273` wrote them. Section 33 now begins at `:5897` and the
sentences sit roughly a hundred lines below the cited numbers -- a reader who follows one
lands in section 32.

## Why a package of its own and not part of `0290`

`0290` widened rule 4. Its scope names *„die Leseregel und die Regeln 1, 2, 3 und 5"* as
out of scope, and five of these six citations belong to rule 5. I renumbered every **T7**
span in that run, because condition 2 demanded it and because T7 (`:842-945`) is stable;
I did not renumber these, and the reason is measured, not tidiness:

**`technik.md` moved 36 lines under `0290` while it ran.** Sections 30 to 36 all shifted
`+36` between two greps of the same run (33: `:5861` -> `:5897`, 35: `:6157` -> `:6193`);
the insertion sits inside section 29. Numbers written into a file from a grep taken at the
start of a run are not the numbers at the end of it. This package therefore has one
working rule: **re-grep each sentence by its wording immediately before writing it, and
write nothing else in the same run.**

## Why it is worth a run at all

The six are the only citations in the file that a reader cannot check by reading further
in the same file -- they are the derivation of rule 5's two halves and of its boundary
set, i.e. exactly the part of the rule set nobody would re-derive from the code. A dead
citation there teaches the next reader that the file's citations are decorative, which is
the same damage `0290` was written to undo one bucket over.

It is small: six numbers, one file, no behaviour. It is not urgent, and it should not be
bundled with anything that changes a rule -- a run that touches both cannot be reviewed
apart.
