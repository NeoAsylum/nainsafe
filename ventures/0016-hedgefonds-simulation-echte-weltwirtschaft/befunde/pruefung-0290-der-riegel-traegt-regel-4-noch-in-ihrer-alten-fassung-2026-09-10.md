---
typ: pruefung
paket: 0290-der-riegel-traegt-regel-4-noch-in-ihrer-alten-fassung
pruefer: kern-pruefer
datum: 2026-09-10
urteil: geprueft
kriterium_geprueft: "All five conditions re-derived from the file and from `uebersetzung-2026-09-10.md`; the four new cases and the corpus line `festkomma.hpp:356` hand-run through `linker_operand` and `kopf_ist_i128_umdeutung`."
befunde: 2
---

# Rule 4 now reads the head of one run, and it moves exactly the one line

## What I checked, and how

**1 — the widened rule.** `kopf_ist_i128_umdeutung` (`:645-667`): whitespace dropped into
`eng`; `?` rejected over the **whole** run; enclosing parens stripped only while
`vor_klammer(eng, auf) == zu - 1` and the `(` is not preceded by a name character; then
`starts_with("static_cast<i128>")`. `ordne_ein:908` ORs the two sides. Hand-run on the real
line `festkomma.hpp:356`: `linker_operand` walks back over the balanced group and stops at
the **inner** `(` (`rueck_klammer` matches the second one), so the run is
`(static_cast<i128>(n) - 1)`, one strip, head is the cast → rule 4. Index arithmetic holds
its edges: `zu - 1` is only reached under `auf + 1 < zu`, so `zu >= 2`; an empty run
short-circuits before `eng[auf]`.

**2 — the wording and the citations.** `REGELNAMEN[3]` is *„Regel 4  static_cast<i128> am
Kopf einer Seite, kein ?"* (`:882`). `Grep` for *„beiden Seiten"*: two hits left, `:47`
(rule 2, `sizeof` on either side) and `:996` (case 6's description, where the cast really
is on both sides) — neither defines rule 4. The three old spans `:841-857`, `:865-875`,
`:904-921`: 0 hits. Section 35 named at `:69`. Ten T7 spans held against today's
`technik.md`, all correct: `:842-860` the list, `:847-851` rule 4, `:852-853` the alphabet,
`:857-858` *„Only these three end the region"*, `:868` both spellings, `:870-880` the
reading rule, `:882-888` the 36 lines, `:890-894` the 36th, `:909-911` poison/operator,
`:927-945` the mapping.

**3 — the four cases** (`:1056-1059`), array size 27, head comment *„Siebenundzwanzig"*
with 27 numbered entries, 27 counted. Each hand-run: 24 → left run
`(static_cast<i128>(n) - 1)`, strips, rule 4. 25 → left run `f(static_cast<i128>(a))`,
`eng[0]` is `f`, no strip, no head match → finding. 26 → the run carries `?` → finding.
27 → the runs beside that `*` are `b` and `c` → finding. Case 7 flips from finding to rule
4; that flip **is** the widening.

**4 — the run.** `uebersetzung-2026-09-10.md:169-190`: one place, `kern/include/kern/
festkomma.hpp:99`; 31/26, 0/0, 6/5, **3/3**, 1/1, **1/1**; 42 occurrences in 36 lines;
self-test 9 + 27 all as expected; test 29 of 29 **red**, as the criterion requires.
Recounted rule 4's three lines in the corpus by hand: `festkomma.hpp:161` and `:292`
(cast on both sides), `:356` (left run only) — the third is the line this package moves.
`:99` is `az - ganz * an`, runs `ganz` and `an`, no rule reaches it.

**5 — T7 untouched.** `technik.md:902-907` still carries 0274's wording (*„red today, at
those two lines"*, green *„once the successor under `werkzeuge/multiplikation/` carries the
widened rule 4"*) — a run that had edited T7 would have had to rewrite it.

**Searched and empty:** non-determinism. `sammle_quellen:1144` sorts the paths, the name
tables are membership tests only, and `unordered_`, `std::map`, `std::set`, `rand`,
`chrono`, `double`, `float`, `reinterpret_cast` give 0 hits in the file.

## Finding 1 — the new `?` paragraph cites a line that is not there

`:85` says the only corpus line carrying both `?` and `*` is `zustand.hpp:777`. `Grep` over
`kern/include` and `kern/src` for a line with both: exactly one hit, and it is
`zustand.hpp:797` — `return nummer < LAENDER ? nummer * LAND_FELDER : BASIS_RESTWELT;`.
`zustand.hpp:777` is `if (nummer < 1 || nummer > SEKTOREN) {`. The claim itself holds (one
line; the `?` stands outside both runs; `LAND_FELDER` puts it under rule 1 anyway) — only
the number drifted by 20.

**The number was copied from T7, which carries the same stale one:** `technik.md:925`.
Condition 5 says the latch follows T7, so this does not fail the run. It is a T7 finding,
and `0276` is already `offen` on `specs/.../technik.md`. For the project manager: one cell
of that table, or the latch's copy stays faithful to a wrong number.

## Finding 2 — the file now contradicts itself about where the alphabet lives

`:1003`, rewritten in this run, cites the operand alphabet as T7 `:852-853` — correct
today. `:800`, the doc comment of `im_alphabet`, still says *„Das Alphabet des
Operandenbereichs aus T7 `:847-848`"* — and `:847-848` today is **rule 4's** first two
lines. Out of scope by name (the package excludes rule 5), and `0292` was proposed in the
same run for that file's stale citations — but `0292`'s `abnahme` lists six numbers and
`:847-848` is not among them. It should be: it is the one that now points at the wrong rule.

Proposed as its own package: `0293`, the distribution names counts and no lines.
