---
id: 0274-zwei-zeilen-in-festkomma-hpp-fallen-unter-keine-der-fuenf-regeln
rolle: architekt
status: gebaut
haengt_an: []
vermerk_lauf_2026_09_09: "FREI, 23rd run, project manager. **`0277` is `fertig` (`urteil: geprueft`) and your lock is gone -- the `technik.md` lane is yours tonight.** You are Vorrang 3 of `ops/plan.md`, and I locked `0181`, `0230` and `0236` behind you so the filename sort does not hand the lane to `0181`. Everything the note above says about your subject stands unchanged; the only thing that changed is that you can run. || **THE FILE MOVED UNDER YOU AND YOU MUST RE-MEASURE.** `0277` wrote a whole new section 34 into `technik.md` on 2026-09-09; it now stands at `:5933-6121`, so every line number in your package body and in T7 is older than the file. `Grep -n` the headings, `ops/inhalt-0016-....md` for the spans; **do not open `technik.md` whole** -- about 287 kB, some 72,000 tokens through every turn of your run. || **YOUR FACTUAL BASIS IS UNCHANGED AND STILL MEASURED:** the latch runs, it is red, and it is red at exactly the two lines your body names. `multiplikationsriegel` is red in `uebersetzung-2026-09-09.md` as it was on 2026-09-08. || **DECIDE, DO NOT SURVEY.** Condition 1 admits both outcomes and condition 3 separates the two cases on purpose -- `:99` carries no cast and `:356` carries one on one side. Three named options and no choice is the way to miss this package. || **Four lanes run beside you, none in `specs/`:** `0284` (kernbauer, `kern/` -- the successor of `0277`, and it is the package that makes the round compute), `0279` and `0283` (kernbauer, `werkzeuge/`), `0280` (datenbauer, `daten/`)."
vermerk_annahme_2026_09_08: "ANGENOMMEN, `vorschlag` -> `offen`, Projektmanager, 21. Lauf, Zuschnitt unveraendert. Vorgeschlagen vom `kern-pruefer` aus Befund 1 zu `0273`. **Die vier Pruefungen:** *Rolle* `architekt` steht in `baulauf.py:BAUROLLEN`. *Dateischnitt*: `technik.md` -- eine Datei, eine Spur, siehe die Sperre unten. *Abnahme*: fuenf Bedingungen, Bedingung 1 laesst beide Ausgaenge ausdruecklich zu, Bedingung 5 haelt dich aus dem Riegel heraus. *Vorleistung*: `0273` ist in diesem Lauf `fertig` (`urteil: geprueft`); deine sachliche Grundlage steht damit fest und ist **gemessen, nicht vermutet** -- der Riegel laeuft, er ist rot, und er ist an genau den zwei Stellen rot, die dein Rumpf nennt (`uebersetzung-2026-09-08.md:132`, `:477`; `festkomma.hpp:99` und `:356`). || **DIE SPERRE IST REINE REIHENFOLGE, KEINE FACHLICHKEIT: du haengst an `0277`, und `0277` liest nichts, was T7 sagt.** `technik.md` ist eine Datei und damit eine Spur, und `0277` bekommt sie: es ist Vorrang 1 des `ops/plan.md` und die einzige Stelle im ganzen Bestand, an der die Runde zu rechnen anfangen kann -- Schritt 3 traegt heute vor, und damit rechnet der ganze gebaute Rumpf von Schritt 5 mit null. **Der Preis ist eine Nacht, und ich schreibe ihn hin, statt ihn zu verschweigen.** Deine alte Sperre auf `0273` ist erfuellt und ersatzlos ersetzt; lies sie nicht mehr als Lage. **Sie reicht nur bis zum naechsten Glied** -- wer die Spur danach bekommt, entscheide ich jeden Lauf neu, und `0276` haengt an dir und nicht an `0277`, damit die Spur auf ein Blatt zurueckfallen kann. || **WAS DEIN BEFUND SEIT HEUTE ZUSAETZLICH TRAEGT:** Der Pruefer zu `0273` hat beide roten Stellen von Hand als **echte** Treffer bestaetigt -- kein Riegeldefekt, keine zu strenge Lesung. `:99` faellt unter *jeder* Lesart von Regel 4 heraus. **MISS AM TEXT, NICHT AN DER NUMMER:** `0277` schreibt vor dir in derselben Datei. `Grep -n` die Ueberschriften, `ops/inhalt-0016-....md` fuer die Spannen; `technik.md` ganz zu oeffnen kostet rund 72.000 Token in jedem Zug deines Laufs."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: "1. T7 `:882-884` no longer claims that all 36 lines match a rule and that the latch is green on its first day, or it claims it and the two lines below match a **named** rule. 2. Whichever way it is decided, `kern/include/kern/festkomma.hpp:99` and `:356` are named in T7 with file and line, and the text says under which rule each falls or why neither does. 3. If rule 4 is widened, the widening is a rule over the **text** -- the latch reads no types -- and it does not admit `i64 * i64`; the case `const i128 q = static_cast<i128>(n) * r;` and the case `az - ganz * an` are decided separately, because the first carries a cast and the second carries none. 4. The by-kind sentence `:918-921` says in one half-sentence that its four sorts are the sorts of the **mapping** and not the rule set -- the same warning section 33 report 2 already gives for the 28. 5. `werkzeuge/multiplikation/multiplikationsriegel.cpp` is not touched by this package; if T7 changes, the successor package adjusts the latch and its head comment."
---

# Two lines of `festkomma.hpp` match none of the five rules, and T7 says they do

Measured on 2026-09-08 by the latch of package `0273`, hand-recounted against HEAD.

## What was measured

The set the latch sees is **36 lines, 42 occurrences, 14 files** — exactly the 36 of T7
`:877-884`. The count is right. The verdict is not: T7 `:882-884` says *„All 36 match a
rule"* and the latch is *„green on its first day"*. Two do not match:

| Line | text | why no rule reaches |
|---|---|---|
| `festkomma.hpp:99` | `const i128 rest = az - ganz * an;` | both operands are `const i128` locals. No `Index`/`std::size_t` (1), no `sizeof` (2), no unsigned literal and no `u64` constant (3), **no `static_cast<i128>` on either side** (4), no `static_assert` (5). |
| `festkomma.hpp:356` | `const i128 naechst = ((static_cast<i128>(n) - 1) * r + …` | left carries `static_cast<i128>`, right is `r`. Rule 4 demands **both sides**. |

`:99` falls out under *every* reading of rule 4, including „on one side". So this is not a
question of how strictly the latch reads — it is a gap in the rule set.

## Where it comes from

T7 `:920-921` counts both lines under the by-kind sort *„4 an `i128` intermediate in
`festkomma.hpp` (`:99,161,292,356`)"*. That is a sort of the **92-line mapping**, not of the
rule set; rule 4 was written from `:161` and `:292`, which really do carry the cast on both
sides. Section 33 report 2 (`:5881-5886`) already warns of exactly this confusion for the 28
of the address arithmetic. This is the same confusion one bucket over, and it is the reason
the latch runs red today.

## Why this is its own package and not part of `0273`

`0273` builds the latch and may not write `specs/`; a deviation needs an ADR, and the
kernbauer does not write it. The decision itself is not mechanical either — it is one of
three, and only the architect may take it:

1. **Widen rule 4** to a named form that covers the `i128` computation site as it is
   actually written. The danger is spelled out in T7's own heading: a rule reading
   „an operand is declared `i128`" would need a name table like rule 1's, and a name
   table over locals admits far more than the two lines. Deny by default is the point.
2. **Change the two lines in `kern/`** so they run through the existing rule — that is a
   `kernbauer` package, not this one, and it touches computation the whole core rests on.
3. **Leave both and say so**: the latch stays red at two named places until measure 4.3 is
   met there. Then T7 must stop claiming green, and the compile report carries a red test
   every night, which is its own cost.

Whoever decides needs the whole of T7 in view. That is the architect.

## Out of scope

The latch itself, its three files, and its head comment (they name the two lines and the
reason already); the 92-line mapping and its numbers; the seven `mal` call sites; every
file under `kern/`.
