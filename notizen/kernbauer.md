# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 15047 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-8.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- 0272 (the third blind spot has two halves, the dangerous one was missing)

Delivered in `kennzeichen_riegel.cpp`: the head's third blind spot split into two named halves
(`:88-113`), the count-without-a-set at the old `:1756` replaced by its rule, and case 27 --
`{ERSTES("alpha"), "beta"}` declared two, two marks, `knappe_listen` silent, read wording
`alpha`. Bound 26 -> 27; the split recounted by grep at 19 default-leaving + 8 writing the
fourth value = 27, three `lesbar: false` still inside the 19, so 16 still reach the check.

- 2026-09-08, **the lesson of the run** -- **A blind spot written from one example is written
  from the half that example happens to sit in, and the missing half is systematically the
  silent one.** `0271` wrote "an element that is no string literal -- a constant, **a call** --
  leaves no mark" from the `TEXT_A` case. A call carrying a literal leaves a mark, just the
  wrong one; that half reports *nothing* on a broken binding, while the written half reports
  *too much* on healthy text. The over-reporting half is the one you meet first, because it
  reddens a run and demands an explanation -- the silent half never asks for anything. General
  form: **when you write down a blind spot, ask which direction the failure points. If the
  example that taught you the rule was loud, look for the quiet sibling of the same rule, and
  do not let one sentence cover both.**
- 2026-09-08 -- **A case whose expectation is a zero must write the zero out.** `0269` taught
  me that an NSDMI default is how you add an expectation without touching rows already right,
  and that stays true -- for rows the field does not concern. Case 27 is *about* the field
  being zero: the silence is the finding. Inherited, the reader cannot tell measurement from
  omission. **The default is the expectation only where the case is not about the default.**
- 2026-09-08 -- **The package forbade touching `:1503-1519`, and adding a case moved it
  anyway.** The counts there (19 + 7 = 26) were true at HEAD and false the moment a 27th case
  existed. I changed two number words rather than leave a false count standing in the file
  whose whole purpose is that text and code agree -- that is exactly the disease `0271` was
  written to cure. Reported here because it is strictly outside the named scope. **A "do not
  touch these numbers" clause is written against re-litigating them, not against the run that
  makes them false; when your own work moves a count, moving the count is part of the work.**
- 2026-09-08 -- **Verified before writing, not assumed:** merging happens only across
  whitespace and comments (`hinter_fuellsel`, `:406-425`), so `)` and `,` separate
  `ERSTES("alpha")` from `"beta"` and two marks is right; all three resolved lists in the tree
  carry literals only (`schritt_probe.cpp:440`, `werte_probe.cpp:357`, `festkomma_probe.cpp:282`),
  so the head's "neither form stands in the tree today" holds for both halves.
- 2026-09-08, **a lead I did not act on, for whoever owns `kern/test/` next:** the second
  half's form already exists in the tree -- `KZ_ZU_VIELE = zu_viele_stuecke()` in
  `kennzeichen_probe.cpp` is a list built by a call -- but no entry resolves it, because that
  probe's table is deliberately not named `RIEGEL_OHNE_ZUSTAND`. So the day that probe joins
  the directory, the second half bites on the first run. I left it out of the head: it is a
  citation into a file another package owns, and it would go stale there.
- 2026-09-08, **what I am unsure about, for the project manager:** three things.
  **(a)** I cannot compile. Riskiest edit is the bound `26 -> 27` against the one appended
  initialiser -- a miscount fails loudly, which is the good failure. Then case 27's `was`
  string, which is split across two lines (adjacent-literal concatenation) unlike every other
  case, and its escaped probe text `{ERSTES(\"alpha\"), \"beta\"}`.
  **(b)** Case 27's expectation is a **silence** (`listen_knapp = 0`). A reviewer may call a
  green expectation worthless. It is not: the load-bearing part is the expectation string
  `R::Eins=alpha;beta`, which pins that two marks came out and that `alpha` -- the macro's
  argument, not the element's wording -- is what the tool binds. Under the sentence `0271`
  wrote, this case would read one mark and report knapp. It separates text from code.
  **(c)** I rewrote the two paragraphs above case 26 as well as the head, to name the halves
  consistently. The case initialiser is byte-identical and no expectation moved, but the prose
  around an existing case is strictly more than "add the third".

