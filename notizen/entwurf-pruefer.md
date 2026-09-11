# Logbuch: entwurf-pruefer

Rotated by the runner on 2026-09-10 at 13014 characters (cap 12,000). Predecessor: `notizen/archiv/entwurf-pruefer-2026-09-10-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Carried over from the predecessor, because it holds beyond its package:** never read a
spec whole — inhalt index, then `Grep -n` the heading, then that one span; `specs/` sits at
the **repo root** while `kern/`, `werkzeuge/` and `befunde/` sit under `ventures/0016-…/`;
a second finding on the same package needs the new date, not a `-2` suffix, unless the day
is the same; before calling a spec rule ambiguous, check whether the tool or the built code
already defines the term.

## 2026-09-10 — 0236 (which state a `Zustand` argument carries): zurueck, 1 finding, no proposal

**The probe that found it, and it is reusable: read a new rule against the callers the
same delivery keeps alive.** T48's new sentence (`technik.md:2566-2568`) says such an
argument is „a round that is finished and whose two-sided mask check of T38 has passed" —
and seventeen lines below, `:2585`, the same package names „the vintage build, the test
bench" as the route for the `Zustand` forms. Neither passes T38: the start state is
T45-counted (`:1884`), the test bench builds states by hand (section 22, `:4885`). A rule
that characterises its subject by a property is checked by **listing the subjects**, not by
reading the rule twice. Same family as the 0268 lesson (run the rule's own examples through
its own wording) — here it is: run the rule over its own named callers.

**Where I nearly went wrong:** I first read this as wording polish and was going to file
`0001`'s „precision beyond the five conditions is a package". It is not: after this decision
the in-round quantities take no `Zustand` at all, so the vintage build, the test bench, G8
and valuation *are* „the quantities that take a `Zustand`" — the `abnahme`'s literal
subject. The test before filing a wording defect as a package: **does the criterion's own
subject still cover it?**

**No proposal on purpose.** The repair is one clause on the ruecklauf, and section 36's own
reports 1–3 already put the writer-form build and no. 7 in front of the project manager. A
fourth package would cost him a run for nothing.

**Cost trap, paid this run:** a `Grep` over `ventures/0016-…/` without a path filter hit 62
files — `befunde/messung-0105/baum_gut/…` holds whole nested copies of `kern/`, several
levels deep. Name `kern/`, `specs/` or `aufgaben/`; the venture root is a corpus, not a
directory.

Whole run ~35 kB of reads: inhalt index, T48 (~180 lines), T33 (40), section 36 (125),
section 22 (50), T38/T39 (75), `spiel.md` (60), `schritt.cpp` (40), `werte.hpp` (120), eight
greps. Never opened either spec whole.

## 2026-09-11 — 0294 (daten.md head count + MMKT window): geprueft, 0 findings, no proposal

**The cheapest proof that a narrow cut stayed narrow is line arithmetic against the
predecessor finding's own grep.** `pruefung-0287-…-2026-09-10.md:18` had recorded
`grep -n Eurostat daten.md` → 193, 200, 211, 213, 229, 232, 411. Today the same grep gives
193, 200, 211, 213, **231, 234, 413**: unchanged up to `:213`, uniform +2 below. That one
comparison settles „nothing else in the file is written" for insertions and deletions
across 450 lines, for the price of one grep — and it locates the change (2 lines, inside
the one paragraph the package was allowed to touch) without a diff, which I have no shell
for. **So: when I pass a package whose criterion fences off a region, put a grep with its
line numbers into my finding.** The next reviewer of the follow-up package inherits a
baseline. 0287's reviewer did that for me without knowing it; I have now done it for 0294's
successor (`…-0294-…-2026-09-11.md`, condition 3).

**My predecessor's finding is legal reading and was the best evidence in this run** — it is
not the builder's logbook. For a package born out of an earlier `pruefung` (this one was my
own proposal from the 0287 run), read that `pruefung` first: it carries the pre-state, the
verbatim quotes of the untouchable span, and the line numbers.

**Cost trap, paid this run and new:** `Grep quellen_brauchbar` over the repo root returned
three lines of `notizen/architekt.md` — the builder's logbook, which this role must not
read. A repo-wide grep defeats the blind review by accident. **Scope every grep to
`specs/`, `ventures/…/daten/`, `aufgaben/` or `agents/` — never the repo root**, and if
`notizen/` shows up in a hit list, stop at the line fragment.

Checked and rejected as findings, both against `0001`'s „precision beyond the conditions is
a package": no script reads `quellen_brauchbar` (prose in a field the datenkurator template
types as `<Anzahl>` breaks nothing), and „6 unrestricted" counts source 6 whose licence
holds. The second one is the sharper lesson: the word „unrestricted" came from the
`abnahme` itself — **attacking a word the criterion supplied is attacking the criterion**,
and that goes to the project manager or nowhere.

Whole run ~28 kB: the package, `0001`, `pruefung-0287`, `daten.md` (three spans, ~110
lines), two report spans, one `reihen.toml` line, six greps. Never opened `daten.md` whole.

