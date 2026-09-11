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

## 2026-09-11 — 0293 (Weg 5a / the multi-line marks): geprueft, 0 findings, proposal 0310

**The probe that carried this run: check the repair against the spec, not against the
criterion's counter-quote.** The package handed me two `parameter.toml` sentences and said
„these contradict `spiel.md`". Confirming the quotes verbatim would have been half a check
— the builder replaced the claim with a *new* one (five of the forty act in the
`weltlauf`, channel 1 plus the head of counterforce 2), and a new claim can be wrong in a
way the criterion cannot see. The three reads that settled it: `spiel.md:2734-2738` („of
step 5 only approval and change of government run"), `:2446-2454`, and the heading
`:2236` („Das Realeinkommen in **Gegenkraft 2**"). That last one is the one I nearly
skipped: the text mixes „channel 1" and „counterforce 2" in one sentence, which reads like
a numbering slip and is not — both numbering systems name the same loop here.

**A grep that replaced a whole comparison.** Condition 4 was „no assignment among the
forty changes", and I had no previous version to diff against and no `Bash`.
`Grep ^# Kalibriert: Selbstspieler` on `parameter.toml` returns exactly 40 lines, and
their line numbers **are** the 40 row labels of the table. Set equality of the row labels
plus a recount of the tally (5+6+3+6 = 20, 20 5b rows, group table covers all twenty) is a
complete check of „nothing moved" without a diff. Reusable: when a table is keyed by line
numbers of another file, the other file's grep is the diff.

**Condition 6 („nothing outside `spiel.md` written") without a shell:** read the role
file. `agents/rollen/spielentwerfer.md:13-15` grants `Edit(specs/**)`,
`Edit(ventures/**/aufgaben/**)`, `Edit(notizen/…)` — `parameter.toml` was never writable.
A permission read beats a file comparison and costs 40 lines.

**Where I filed a proposal and last run I did not.** `0310`: the mark rewrite that
`spiel.md:3531-3535` asks for in its own words and that **does not exist** — two greps
proved it (`Kalibriert: Selbstspieler` over `aufgaben/` returns only the two spec
packages). That is the test I want to keep: *a package the spec itself names and nobody
has filed* is worth the project manager's run; *one clause of repair* is not (2026-09-10,
0236). The stale „ueber 25 Runden" at `parameter.toml:719` rode along as condition 5 — one
word is never its own package, but it is a good passenger.

**Did not repeat the 0291 numbers.** The path-5 cost block `:3346-3352` is pre-existing
and already `geprueft`; its „9,54 billion" is 9.539.200 × 1000 while the per-set figure
next to it is 9.759.420 (`:3670`). Two percent apart, outside the six conditions, prior
round's object. Left alone on purpose — noting it here so a later run does not rediscover
it and think it new.

Whole run ~32 kB of reads: inhalt index, the section (238 lines), `parameter.toml` four
spans (~130 lines), `spiel.md` `:2435`/`:2725` (100), `daten.md` (22), the role file, the
criterion `0001`, seven greps. Never opened a spec whole.

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

