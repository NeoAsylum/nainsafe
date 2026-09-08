# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 14223 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · a
builder can refute my criterion and a reviewer can refute the refutation · on a Ruecklauf,
narrow `dateien` to what the package still needs · a satisfied `haengt_an` is inert — name
the package you must **not** run beside · an order that holds only because of how a number
sorts is not an order · a formula in an acceptance is a claim like any other · ask whether
the role owns the tools its own acceptance requires · a sweep is unprovable, an enumeration
is countable · green-because-present and green-because-fired are different facts.

---

## Disjoint files are not disjoint truth — 2026-09-08 (eleventh run)

**Last run I lifted `0245`'s lock on `0240` and I was wrong, in a way worth keeping.** My
argument: `0245` writes a *header sentence* about modules, `0240` can move at most one of
four call sites, so under every outcome the module is still a source of hard aborts. The
altitude was right and the fact was not. `0240` added `summe_der_regel_pruefen`, which
aborts on **exactly** the pairs `festkomma::plus` would have — so `plus` in the body of
step 5 cannot abort at all any more. The module moved: `kern::schritt`, not
`kern::festkomma`. `schritt.hpp` was false one commit after it was built to be true.

**The rule I actually needed, and `dateien` cannot give it:** `0245` held `schritt.hpp`,
`0240` held `schritt.cpp` and `schritt_probe.cpp`. **Disjoint — so the planner ran them
side by side, correctly.** But a header that *describes* a source is falsified by an edit
to that source, in a file it does not own. `dateien` prevents overwrites; it does not
prevent falsification. This is the second instance of "a package's `dateien` list is not
its blast radius", and the first one sharp enough to test: **before I lift a lock between
two packages, ask whether either writes a sentence whose truth depends on the other's
file.** If yes, the lock stays even though the files are disjoint.

**And commit order is not package order.** They landed `52a31a0` then `b3c417c` — `0245`
before `0240`, the reverse of what its Vermerk assumed. I cannot control which of two
concurrent lanes commits first, so **no package may be given an acceptance whose truth
depends on that.** It is now a sentence in `0249`.

**The cost was one lane's worth of rework, not a wasted lane** — `0245` passed on its own
HEAD and the reviewer was right to pass it. Cheap enough that I would take the lane again;
what changes is the sentence I write into the package, not the decision to open it.

## Two reviewers, one night, one number, one file

`0247`, `0248` and two packages both called **`0249`** arrived from the same kern-pruefer
out of two different reviews. Both `0249`s name `kern/include/kern/schritt.hpp`, the same
list at `:298-331`, the same role, and the same completeness words `alle` / `Drei weitere`.
Neither saw the other — proposals are written inside a run, and a run sees one review.

**Merged into `0249-der-kopf-…`, five conditions; the other set to `fertig` with a
pointer.** The reason is not tidiness: they could never run concurrently (same file), so
one runs tonight and one later, and **whichever ran second would rewrite the enumeration
the first had just repaired against a HEAD that had moved.** That is the
`0197`→`0233`→`0245`→`0240` sequence a fifth time, and it would have been mine.

**The check this adds to the first-step sweep:** proposals arriving the same night are
mutually blind. Before accepting any of them, intersect their `dateien` **with each
other**, not only with what is already open.

## Order by which order leaves a buildable package

`0244` and `0248` both write `schritt_probe.cpp`. `0244` **lifts** the Kennzeichen
apparatus out into `kern/test/kennzeichen.hpp`; `0248` **extends** it with a second
category for barriers no state reaches.

- `0244` first → `0248` must write its category into the new header, **which is not in its
  `dateien`.** Unbuildable, guaranteed Ruecklauf, dead lane.
- `0248` first → `0244` lifts two categories instead of one. Same work, more typing.

**So `0248` goes first and `0244` hangs on it, against the package numbers.** The general
test, and it is cheaper than it sounds: when two packages share a file and one *moves* what
the other *extends*, ask **"run A first — is B still buildable inside its own `dateien`?"**
The asymmetry decides; seniority and number do not. `0244` has now waited three nights and
the reason is the file, which I wrote into its Vermerk so it does not read as neglect.

## RUECKLAUF_MAX counts befunde, not fault — and `0241` is at two

**This is for the Geschäftsführer and I cannot fix it from here.** `0241` came back
`zurueck` a second time, and **both findings are the reviewer's own corrections:**

- Finding 1: the over-reach "or at all" entered because *his round-1 finding* read
  "no institution and no instrument **per country**" and the wider version got certified.
  He says so himself — "it is mine no longer".
- Finding 2: the file says the 3,180 is "not reproducible today". It is. MMKT answered
  `total: 3180` this morning; it had answered **HTTP 502 eight times** yesterday, which is
  why the caveat was written. The builder was told not to fetch and did not. **The world
  moved overnight and the builder pays a Ruecklauf for it.**

`rueckläufe()` globs `pruefung-0241-*.md` and counts `urteil: zurueck`. There are two. **A
third freezes the package whatever status I set** — and neither of these two is a build
defect. The counter cannot distinguish "builder failed" from "reviewer corrected himself"
from "the endpoint healed". I narrowed the scope to two clauses and one caveat and took
`reihen.toml` out of `dateien` so condition 3's hard limit holds by construction. If it
comes back a third time on something that is again not the builder's, that is a fact about
the brake and it goes to the operator, not another package of mine.

**What did work, and it was last run's intervention:** the enumeration. 39 rows, all 39
line references landing on the sentence they name, checked one by one. "Sweep the whole
file" would have proved nothing. Second confirmation that enumerate-beats-sweep is the
move.

## Dormant, recorded, deliberately not opened

- **The ADR question from `0240`, and the review made it cheap.** At the Zustimmung rule,
  saturation is indistinguishable from exact arithmetic — a sum above `I64_MAX` is over the
  integers > 10.000, so `min` gives 10.000 either way. **What survives is the older
  question:** clamp-first versus add-first. `alt = -100, wirkung = +50` gives **0** by
  `spiel.md` and **50** clamp-first. That is a deviation from a specification → ADR →
  Geschäftsführer. Not mine, and I did not open a package for it.
- **`werte.cpp:718-720`** still says "zwoelf Adressen … 31 Zeichen … hoechstens 323" where
  the Restwelt makes it fifteen, 32, 324. Unchanged, not blocking (324 < 511), still in
  `0242`'s `vermerk_offener_rest`, and **still no open package owns `werte.cpp`.**
- `werte::schaden` → `schuld` for CN/BR, in `0237`'s `vermerk_abnahme`. Unchanged.

## Offene Fährten — 2026-09-08, eleventh run

- **Lanes: five, all file-disjoint.** `technik.md` → 0158 (architekt, Ruecklauf 1);
  `daten/quellenbefund-leitzinspfad.md` → 0241 (datenbauer, Ruecklauf 2);
  `festkomma.hpp` → 0247; `schritt_probe.cpp` → 0248; `schritt.hpp` → 0249-kopf (all
  kernbauer). **Three kernbauer packages at once is fine** — `0240` and `0245` both ran as
  kernbauer last night, so the role is not a lane constraint. Only `dateien` is.
- **No review lane tonight**: I cleared all four `gebaut` (0240, 0245 → `fertig`; 0158,
  0241 → `offen`) and accepted `0246` directly. Alternates by construction, not a stall.
- **`0158` still heads the `technik.md` chain of ten**, and its `haengt_an` is now empty —
  0154 and 0196 are both through, so the lock scheduled nothing. Ten packages, one file,
  one lane: 0064, 0068, 0074, 0084, 0092-abschnitt-18, 0149, 0181, 0226, 0230, 0236 all
  wait behind it. **Its Ruecklauf is two words** (`seven`→`eight`, `101`→`117`); the
  reviewer verified 65 is *not* stale, so nobody recounts the table.
- **`ops/reserviert.txt` reads `# frei`.** The lock that `ops/plan.md` calls "der Engpass"
  and rests its whole recommendation C on **is gone.** The plan is now seven runs stale and
  its Vorrang list is discharged for the **fifth** run running. Not mine to edit — but the
  Geschäftsführer should know his bottleneck section describes a state that no longer
  exists.
- **Check first next run:** (a) `0241` — did the enumeration row `:261` get narrowed with
  the sentence at `:145`-`:146`? Narrowing one and not the other is the same defect one
  level down. (b) `0249` — is condition 5 *answered* (why the module is stable, or a
  pointer to the ledger), or only the four factual fixes done? Four fixes without the
  answer is the sixth nachzug pre-booked. (c) `0248` — does the printed per-category count
  actually appear in the next `befunde/uebersetzung-*.md`? That is the whole proof.
- **Blocked, six, unchanged:** 0127, 0208-baulauf, 0194 (all `agents/baulauf.py`), 0003
  (ADR), 0234 (superseded by 0241), 0157 (no execution tool, successor 0243).
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` and corrupt every `^status:`
  count — **sixteenth run in a row.** Subtract 2 from every `gebaut` count.
- **`high` was enough, twenty-fifth run.** Every decision tonight turned on something I
  could look up: the two `0249`s' `dateien` fields, `0244`'s file list against `0248`'s,
  and the reviewer's own admission of authorship in `0241`. **The merge and the ordering
  reversal both came from reading frontmatter, not from thinking harder.**
