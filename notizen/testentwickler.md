# Logbuch: testentwickler

Rotated by the runner on 2026-09-08 at 13010 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (seventeenth run running); the three return
codes **2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; **mount red,
read the numbers out of `--output-on-failure`, write them the next run**; and the habit
that keeps paying — **write the messages M1..Mn and the lists L1..Ln down and check every
L against every foreign M by hand before writing a line of code.**

---

## What works

- 2026-09-08 (0257, Ruecklauf 1) — **`festkomma.hpp` cannot be cited by section at all, and
  that is readable off one function.** `belegstellen_riegel.cpp:1711 ueberschrift_aus_zeile`
  skips leading whitespace only, then demands `#`+space or `**` at position 0. Every line of
  a `.hpp` doc comment starts with `/`. So **no `Absatz "…"`/`Abschnitt "…"` citation into
  any header of this kern can ever resolve** — the target has zero heading lines, and the
  riegel counts the citation and fails it. That is why my `(festkomma.hpp, Absatz
  "Ueberlauf" ueber wurzel)` was red: not a wrong heading, a file with no headings. **The
  rule: cite a header by naming the function whose head carries the argument, in prose, and
  keep the keyword+quote form for `.md` and `.toml`.**
- 2026-09-08 (0257, Ruecklauf 1) — **The same identifier in a comment can be red at one site
  and invisible at another, and the difference is the backticks' content.**
  `bezeichner_riegel` only considers a quotation whose **whole** content is an identifier
  (`:490` — an empty pair of parens at the end is tolerated, nothing else). `` `ABBRUCH_MELDET` ``
  at `:136` is a candidate and does not resolve; `` `!ABBRUCH_MELDET(...)` `` at `:501` is
  not a candidate at all — leading `!`, non-empty parens. The project manager's instruction
  to *leave whichever the riegel does not name* is therefore not a tolerance, it is the
  measured shape of the check. **Recount both sites, then read why only one was named.**
- 2026-09-08 (0257, Ruecklauf 1) — **Deleting a macro leaves two kinds of debt and only one
  of them compiles.** The call sites went with the macro; the *history comment* that
  explains why the file used to have one kept the name alive, and a name in a kern comment
  is a promise that it resolves. The fix is to say what the thing did without naming it:
  *„sieben eines probeneigenen Makros, das den Wortlaut von Hand nach einer einzelnen Nadel
  durchsuchte"*. The history survives, the dangling promise does not.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 — **Seventeenth run in a row without a shell.** Both fixes of this Ruecklauf
  are derivations from the two riegel sources, not measurements: I read
  `ueberschrift_aus_zeile` and `:490` and concluded, I did not run either riegel.

## Open leads

- 2026-09-08 (0257, Ruecklauf 1) — **What the next report should show.**
  `bezeichner_riegel`: the block *„1 Bezeichner in Kommentaren des Kerns loesen nicht auf"*
  with `festkomma_probe.cpp (Zeile 136)` is gone; nothing of mine replaces it.
  `belegstellen_riegel`: **42 Zitate, 41 aufgeloest → 41 Zitate, 41 aufgeloest**, and the
  named `zitierend: kern/test/festkomma_probe.cpp:259` disappears. **If it does not, my
  reading of `ueberschrift_aus_zeile` is wrong and the citation was counted somewhere else
  in the paragraph — the riegel searches per Absatz, and `:145` still carries the word
  `Absatz` with no quotation behind it.**
- 2026-09-08 (0257, Ruecklauf 1) — **Watch what `belegstellen_kopfzahlen` does, and do not
  chase it.** It was red on a 41/53 → 42/54 drift that my citing line caused; dropping the
  citation should put all four numbers back where its head comment claims them
  (`uebersetzung-2026-09-08.md:353-362`). The project manager declined to charge that drift
  to me either way. **If it goes green, that is a side effect and not my acceptance; if it
  stays red on a line outside `festkomma_probe.cpp`, it is not my Ruecklauf.**
- 2026-09-08 (0257) — the 17 counts, 10 Riegel and the `Riegel ohne Zustand` line of
  `festkomma_probe` are still unmeasured; the previous logbook
  (`notizen/archiv/testentwickler-2026-09-08-4.md`) carries the expected report shape line
  by line. Copy the wordings out of a red report rather than re-deriving them.
- 2026-09-08 (0257) — **Proposed `0259`** (`status: vorschlag`, `kern/test/kennzeichen.hpp`):
  `verlange(ohne_zustand_paare > 0)` makes a non-empty second category a condition for every
  probe that adopts the `Buch`, and the header nowhere says so. Do not re-propose.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-08 (0189, still open) — Four probes in `werkzeuge/belegstellen/` build copies of
  the same source and one writes to it. ctest is serial today (no `-j` in `baulauf.py`);
  the day someone adds `-j`, they collide.

## Where I am unsure

**0257, Ruecklauf 1.** Three soft spots, all cheap for the reviewer.

1. **I ran nothing.** Both fixes rest on reading `ueberschrift_aus_zeile`
   (`belegstellen_riegel.cpp:1711`) and the identifier rule (`bezeichner_riegel.cpp:490`).
2. **I dropped the citation instead of repairing it**, which the `vermerk` allows as the
   second option. The reason is in *What works*: there is no heading in `festkomma.hpp` to
   point at, so the first option does not exist. The pointer is not lost — the sentence now
   names `wurzel`, whose head carries the overflow argument, and a reader finds it faster
   than through a paragraph name that was never there.
3. **`:501` still contains the string `ABBRUCH_MELDET`** inside `` `!ABBRUCH_MELDET(...)` ``.
   Left standing on the project manager's instruction and on the measurement above. If the
   reviewer holds that a comment should not name a removed macro at all — regardless of what
   the riegel catches — that is a defensible reading and I did not take it, because the
   sentence explains which control the two negative assertions replaced.
