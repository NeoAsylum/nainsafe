# Logbuch: projektmanager

Rotated by the runner on 2026-09-07 at 12021 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-07-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force from the predecessor, not repeated here:** pulling beats cutting · three
separate budgets · the backlog is chains, not items · `specs/` **and** the source code
order me verbatim · tool list (never `cd`, `Edit` needs `Read`, `Grep` only on
`^status:`/`^rolle:`/`^dateien:`) · the four formulas I no longer write into an `abnahme` ·
**the defect is per chain, not per package** · re-anchor every tree-number in a returned
acceptance · check the body language before writing the vermerk.

---

## The unbuildable acceptance came from a reviewer this time, not from me — 2026-09-07 (6)

**0222's abnahme demanded that the builder quote the report entries produced by the run
that follows his own.** Sixth case of the class, first one I did not write. The predecessor
entry treats these as "my own pre-2026-09-07 acceptances are the fundort" — that is now too
narrow. The defect is not a habit of mine; it is a property of the factory nobody has
written down: **the nightly report is an output of the run, so no clause resting on it can
be owed by the builder.**

The general rule, and it is cheap to apply because it is purely syntactic: **an acceptance
clause naming `befunde/uebersetzung-<datum>.md` must assign that reading to the reviewer.**
Builder owes what he can produce — file, line, old wording, new wording. Reviewer owes what
only the next report can show — red, green, runtime. I moved the clause rather than dropped
it: what it was reaching for (do 0166's numbers survive the repair?) was real, and it now
stands in 0166's return vermerk, where the agent who needs it will read it.

## A return whose cause lies outside the package's own dateien

**0166 came back `zurueck` with almost everything sound.** Mounting proven live on both
build paths, exit codes 0/1/2 separated, the script reads the delivered comment and its
selbstprobe proves it can say no, runtime 18 s against a 240 s cap. What failed is half the
red proof: green-at-new is not shown, because `belegstellen_wortabstand` reports 5
deviations — and the reviewer pinned why. The corpus moved under the package after its
build commit: `technik.md:409` was translated, so the riegel's own head citation died, the
riegel went 40/40/47 → 40/36/53, and the 0034 Stelle the table describes is itself among
today's unresolved. **The table cannot be green while the riegel is red on the corpus.**

**So the return is a reorder, not a rebuild** — and that is a shape I had not used before. I
hung 0166 on 0222 (the corpus repair) and wrote into it: *measure first, do not build.* If
the post-repair report shows 0 deviations, the delivered table was right all along and the
builder changes nothing but his vermerk. Rebuilding a correct number costs the next
Ruecklauf. **When a return's cause is provably outside the package's `dateien`, the
instruction to the builder is a reading order, not a work order.**

## `ops/reserviert.txt` changes under the proposals that cite it

**0223 came in saying `spiel.md` is held by the translation lane. It is not — it came off
after five days**, and the file now holds only `technik.md` and `zielbild.md`. Had I
believed the proposal's own note I would have written a serialisation vermerk for a lock
that does not exist, and the package would have looked blocked while being schedulable.

**Read `reserviert.txt` yourself in the run, every run.** A proposal is written hours
before I see it, and this file is exactly the kind of state that turns over inside that
window. Same class as the report that is overwritten per run: the proposer's situational
notes age faster than the proposer's evidence.

## Offene Fährten

- **Lanes today: two of eight** (0222, 0223), against one yesterday. **21 open, and 15 of
  them sit on `technik.md`** — sixth day of the reservation, including priority places 1, 4
  and 5. The wall is unchanged and nothing I cut moves it.
- **0222 is the whole evening.** Three tests (riegel, messung-0147, wortabstand) and three
  packages (0166 → 0182 → 0189) hang on that one run. It is the head of the belegstellen
  queue as of today; before it, none of the three is measurable.
- **Third wave of citation breakage, and I am carrying the count to the Geschäftsführer.**
  0200 repaired wave one, 0222 repairs wave three. Whether nachzug belongs in the
  uebersetzer's own loop is recommendation B in `ops/plan.md` and has been the operator's
  open decision for a day. The testentwickler raised it in the proposal rather than filing
  it in a logbook — that is the 2026-09-02 rule working, and it should be said.
- **0197 lost half its blockade** (0198 `fertig`, removed from `haengt_an`) and is now
  blocked on 0208-schritt alone — which is frozen under the same `technik.md` line. The
  bottleneck of `ops/plan.md` is now one package deep instead of two, and both remaining
  gaps are behind the translation run rather than behind an agent.
- **`Realeinkommen` is settled**: T48 quantity, 310 stays 310, 890 stays 890, T48 22 → 25.
  The architect needs that number and the core builder measures against it.
- **The daten-pruefer's own boundary is worth quoting when someone asks what green means
  here:** without a shell he cannot read a blob, so a leaf value changed *in place* moves
  none of his counts. He wrote it himself rather than letting it pass as coverage.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` corrupt every `^status:` count.
  Third run in a row they show up.
- **`technik.md` zerlegen**, nineteenth time due — fifteen packages on one file.
- **`high` was enough**, twelfth run. Two acceptances, one return, two proposals, one
  unblocking; the hardest call was spotting the report-timing defect, and that was reading,
  not reasoning.

