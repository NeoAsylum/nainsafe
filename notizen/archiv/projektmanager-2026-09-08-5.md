# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 17714 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · on a
Ruecklauf, narrow `dateien` to what the package still needs · a satisfied `haengt_an` is
inert — name the package you must **not** run beside, and recompute a proposed one, never
carry it over · the asymmetry test: "run A first — is B still buildable inside its own
`dateien`?" · a sweep is unprovable, an enumeration is countable · ask whether the role owns
the tools its own acceptance requires · a riegel without `add_test` never runs · before
lifting a lock, ask whether either package writes a sentence **or a parser** whose truth
depends on the other's file — for prose raise the altitude and keep the lane, for a parser
serialise.

---

## I wrote a false clause into an acceptance criterion and a builder obeyed it — 2026-09-08 (fourteenth run)

**`0251` passed with 0 findings and the reviewer still handed me a defect: mine.** Its
condition 1 demanded the riegel be wired *„so the runner executes it and the numbers land in
`befunde/uebersetzung-<datum>.md`"*. `agents/baulauf.py:186` runs `ctest
--output-on-failure` — **a passing test's stdout goes nowhere.** The clause is false for
every riegel in the tree, `bezeichner` included, and `bezeichner` is the shape I named to
the builder as the model. Tonight's report proves it: four riegel, four lines, each
`Passed`, no number. The numbers that do land come from `message(STATUS)` at configure time.

**The builder complied and the clause stayed false, which is the part worth keeping.** An
unreachable criterion announces itself — `0157`, five strikes, each caught before the run.
**A false one does not: it is satisfiable, the package passes, and nobody notices the clause
never became true.** That is the more expensive kind and I had no test for it. The one I
have now: **before writing „and the number lands in the report", ask where the number
physically goes.** Configure-time `message(STATUS)` lands. A passing test's stdout does not.

**And the fix for a false criterion is to stop writing it, not to build the mechanism it
assumed.** The proposal offered both: way 1 makes every riegel's number visible at configure
time; way 2 gives the tool a floor so a half-blind run cannot stay green. Way 1's real
benefit was that it would make *my* clause true. **That is not worth a package — the
operator has two hours a week and a number in a report nobody diffs is the same silence with
more characters.** Way 2 only, in `0258`; way 1 recorded in its `vermerk` with the
proposer's cost numbers so nobody re-measures them.

## A lock is retargeted, not removed, when the chain merely moved one link along

Last night's note to myself was: *if `0064` is `fertig`, remove the locks on `0230`/`0236`
rather than renewing them down the chain.* **Half right, and I nearly followed it into the
failure it was written against.** `0064` is `fertig`, so the lock is discharged — but the
lane is unchanged: eight packages on `technik.md`, the planner picking arbitrarily among
whatever is startable, and tonight the startable three are `0068` (head of a chain five
deep) and the same two leaves. Remove the locks and two thirds of the time the lane goes to
a leaf again.

**The rule I actually meant, stated properly: never lock past the next link, and re-decide
the one link every run.** „Do not renew" guards against locking to the chain's *tail* — five
nights of unreviewed commitment, unable to fall back if a member jams. It does not mean
letting the ordering fall to chance the moment the head changes. `0230` and `0236` now hang
on `0068`, with the discharge condition written into the package: **`0068` `fertig` and this
is inert; re-decide, do not renew blind.**

## Two proposals, one number — and the pointer shape was already in the tree

The kern-pruefer proposed two packages tonight, out of two reviews, and both took `0257`.
`0092` and `0107` and `0232` and `0233` all carry the same collision, so the house has been
living with it. **The repair is `0092-linkschalterform-durchgereichtes-l.md`:
`status: umgezogen`, `dateien: []`, body says „Kein Paket. Diese Datei ist nur ein Zeiger."**
No delete (rule 3), no ambiguous number. I renumbered the *dependent* one so the
prerequisite keeps the lower number: `0257` is festkomma, `0258` hangs on it.

**Why they are serialised at all, and it is the parser rule again, now with its limit
found.** `0258` sweeps every probe under `kern/test/` that names `RIEGEL_OHNE_ZUSTAND`;
`0257` gives `festkomma_probe.cpp` a third such table. Last night's refinement — a parser
raises its altitude by naming a symbol instead of a file — **is what makes `0258` a good
tool and does not save the lane here**, because the hazard is not that the parser goes blind
but that a table it has never seen *joins its set* the same night. **Naming a symbol widens
what a parser sees; it does not stop what it sees from arriving mid-flight.** Asymmetry test
answers cleanly: `0257` first and `0258` is written against three tables instead of two.

## A Ruecklauf that narrows `dateien` frees a lane for somebody else

`0253` came back with one finding — one sentence in one of its three files, the other two
verified line by line and done. Narrowing `dateien` to `quellenbefund-leitzinspfad.md` is my
standing rule, and tonight it paid twice: **`deckungsbefund-1997.md` came free, which is the
only reason `0256` could open at all.** A Ruecklauf is not only a cost; it is a release, if
you cut the package back to what is actually left.

Both packages then got the same instruction in both directions: **assert nothing about the
other's file, presence or absence.** That is the `0249` mechanism — four true sentences
falsified by lanes landing the same night, two Rueckläufe spent on it, one short of frozen.

## Offene Fährten — 2026-09-08, fourteenth run

- **Four to `fertig`, one back.** `0064`, `0249`, `0251`, `0255` `geprueft`. **`0249` passed
  on its third attempt, one short of `RUECKLAUF_MAX`** — what carried it was the reviewer's
  remedy of *deleting* the absolute negative rather than replacing it. `0253` `zurueck`,
  Ruecklauf 1, and its finding is one sentence.
- **Lanes tonight: five, all file-disjoint.** `technik.md` → `0068` (architekt, chain head);
  `daten/quellenbefund` → `0253`; `daten/deckungsbefund` → `0256`; `kern/CMakeLists.txt` →
  `0254` (freed by `0255`); `kern/test/festkomma_probe.cpp` → `0257`.
  **Three of the eight slots stand idle on purpose:** everything else `offen` is on
  `technik.md`, and `0258` is deliberately held behind `0257`.
- **Three proposals, three accepted, two cuts unchanged.** `0256` needed nothing. `0257`
  needed its `ctest bleibt gruen` rewritten — a claim about the whole tree while three other
  lanes run. `0258` needed a way chosen, a number, and a lock.
- **`0064` left a residue and it went into `0068` rather than into a package.** §29's own
  check clause (`technik.md:5359`) says a `Grep` for `18.024`/`87.864` gives zero hits, and
  three lines inside §29 hold both; the reviewer names the fix (*outside this section*).
  **One phrase on the one lane this venture has — a package of its own would cost a whole
  night.** Bounded in the vermerk: that phrase, nothing else in §29.
- **For the Geschäftsführer, fourth run running: `RUECKLAUF_MAX` counts befunde, not fault.**
  `0249` survived on its last attempt having spent both rounds on sentences falsified by
  concurrent lanes. **The brake is aimed at the builder and is hitting the schedule.**
- **`ops/plan.md`, eighth run:** its Vorrang list (0224, 0225, 0189, 0208-schritt, 0165,
  0172-weltpreis) is entirely discharged, and „Der Engpass" still rests on a lock
  (`ops/reserviert.txt` = `# frei`) that has been gone for eight runs. **The real bottleneck:
  eight packages on `technik.md`, one lane, a chain six deep.** Not mine to edit. Reported.
- **Check first next run:** (a) `0253` — is `:152` scoped and row `:262` with it, and does
  anything in it still speak about `deckungsbefund`? (b) `0257` — did it recount the nine
  `abbruch` sites at HEAD, and did it stay out of `kennzeichen.hpp`? If it touched the
  header, `0254`'s round is compromised through no fault of its own. (c) `0068` — did it
  re-measure after `0064` moved ten places in `technik.md`, and did condition 4 stay one
  phrase? (d) If `0068` is `fertig`, retarget `0230`/`0236` to `0074`, do not free them.
- **Blocked, five:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` — no agent may
  write `agents/`), `0003` (ADR), `0157` (no execution tool, successor `0243`).
- **Dormant, unchanged:** clamp-first vs add-first deviation from `spiel.md` → ADR →
  Geschäftsführer. `werte.cpp:718-720` still says „zwoelf Adressen … 31 Zeichen … hoechstens
  323" where the Restwelt makes it fifteen/32/324; **still no open package owns `werte.cpp`.**
  `werte::schaden` → `schuld` for CN/BR in `0237`'s `vermerk_abnahme`.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **nineteenth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, twenty-eighth run.** The two real decisions — that a *false* criterion
  is a different animal from an unreachable one, and that naming a symbol does not protect a
  parser from a table arriving mid-flight — were both corrections to rules I wrote in the
  last two runs. That is what the logbook is for.

---

## The planner picks arbitrarily among startable packages, and nobody was choosing — 2026-09-08 (thirteenth run)

**This is the throughput lever I had not noticed in twelve runs, and it was free.**

`0149` finished tonight and freed the `technik.md` lane. Nine packages stand `offen` on
that one file; `startbereit` (`baulauf.py:306-325`) serialises on `dateien`, so **one file
is one lane** — that part I had written down five times. What I had not asked is *which*
of the nine runs. Tonight three were startable at once: `0064`, `0230`, `0236`. The planner
picks among them **arbitrarily**, and `0064` is the head of a chain of six
(`0068` → `0074` → `0084` → `0092` → `0181` → `0226`, each locked to its predecessor)
while `0230` and `0236` are leaves that unlock nothing.

**Two thirds of the time the single lane would have been spent on a leaf and six packages
would have stood another night.** I have written down "one file, one lane, nine nights" in
three consecutive runs as a fact about the venture. It is a fact about the venture; **which
nine nights, in which order, was mine and I was leaving it to chance.**

**The fix is an ordering lock in `haengt_an`, and the repo already had the precedent** —
`0149`'s own Vermerk of 2026-09-07 calls its second entry "eine Reihenfolgesperre auf
`technik.md` und keine fachliche Abhaengigkeit". Two edits: `0230` and `0236` now hang on
`0064`. Costs them nothing they had (same file, same lane either way); buys six packages a
night each.

**And the shape of the lock is the part I nearly got wrong.** The tempting version locks
the two leaves behind the chain's *tail* `0226`, which fully orders all nine and never has
to be revisited. **That is six nights of unreviewed commitment: if a chain member jams —
`blockiert`, or spends its three Rueckläufe — the lane must fall back to a leaf, and a lock
on `0226` would freeze it instead.** I run every night and can re-decide in two edits, so
the lock goes one link deep and says so in its own Vermerk: *`0064` `fertig` and this lock
is inert and should be removed, not renewed further down.* **Lock as far as the next run
can see, not as far as the plan goes.**

## A parser can raise its altitude after all — by naming a symbol, not a file

Last night's rule was: when A merely *describes* B's structure, fix the altitude and keep
the lane; when A *reads* B's structure, **serialise**, because code must name a file.

**The second half is too strong, and `0251` is the counterexample.** Its riegel reads the
`RIEGEL_OHNE_ZUSTAND` table out of a probe; `0255` edits one of the probes that holds one.
Same shape as last night, and the rule said lock. But a parser does not have to name a
*file* — it can name a **symbol and a directory**: find the tables by name under
`kern/test/`, the way `bezeichner_riegel` already walks a tree and owns its file selection.
**Then `0255`'s edit cannot blind it, and the lane stays.**

**And this is not a trick to save a lane — it is the better tool.** `0244` proved it the
hard way: the package was written when there was **one** `RIEGEL_OHNE_ZUSTAND` table and
there are now **two** (`schritt_probe.cpp:443`, `werte_probe.cpp:233`), because `0244`
lifted the apparatus into `kennzeichen.hpp` but deliberately left one enumeration per probe
(`kennzeichen.hpp:15`). **A tool that had hard-coded `schritt_probe.cpp` would have been one
refactor from looking at nothing — the precise state `0251`'s own condition 3 exists to
detect.** So: **serialise a parser only when it cannot be written against a name.**

`0254` got the lock instead, and for the opposite reason: it asserts `the current tree
passes` about `kennzeichen.hpp`, which `0255` rewrites tonight. **An acceptance that is a
claim about somebody else's file in flight is not raisable — you can only wait.**

## The `0157` trap, fifth strike — and the second one replaced by something stronger

`0254`'s condition 1 as proposed: *a header under `test/` that names a poisoned identifier
fails the configure run.* **No role runs cmake** (`agents/lauf.py:NIE`), the compiler runs
after the run, and a bait committed to the tree would leave the tree red — so the criterion
is unreachable *and* the workaround is worse than unreachable.

**The replacement was already in the tree, again:** the test-pruefer discharged `0244`'s
condition 2 by **red-when-broken traced in code** — name the line at which the check raises,
name what input reaches it. That is the house method for "this check really fires" without
executing anything, and it is now `0254`'s condition 1. **Two strikes running (`0251`,
`0254`) replaced by something better rather than smaller; the three before them were struck
and shrunk.** The pattern: **before weakening an unreachable criterion, look for who in this
tree already had to solve the same problem.**

## `0249` is at Ruecklauf 2, and the third falsification is the same mechanism

`schritt.hpp` has now had **four** sentences falsified by an edit in a file the package did
not own. Round 2's finding: the builder wrote *"die Schranken in `kern::werte` und
`kern::festkomma` stehen in keinem von beiden [Verzeichnissen]"* — true at their own HEAD,
false after `0244` landed the same night and created `werte_probe`'s registries. **They
avoided the *path* exactly as I instructed and then asserted the ledgers' *contents*, which
is the same defect one level in.**

**The reviewer's remedy is a deletion and that is why it will hold:** *"Drop the absolute
negative … Any clause of the form X steht in keinem Verzeichnis is an assertion about files
this package does not own and will go stale again."* **A clause you delete cannot be
falsified; a clause you replace can.** I passed that through verbatim and named tonight's
live hazard (`0255` on `werte_probe.cpp` and `kennzeichen.hpp`) with the instruction:
**assert nothing about those two files in either direction — presence *or* absence.**

One more Ruecklauf freezes it. The scope is one clause.

## Offene Fährten — 2026-09-08, thirteenth run

- **Three to `fertig`, one back.** `0244`, `0149`, `0252` `geprueft` — **`0252` on its first
  attempt, on the file that cost `0241` three**, because it wrote what its retrieval
  supported and named the residue instead of widening (that residue is `0253`). `0249`
  `zurueck`, Ruecklauf 2.
- **Lanes tonight: five, all file-disjoint.** `technik.md` → `0064` (architekt, chain head);
  `schritt.hpp` → `0249` (kernbauer, Ruecklauf 2); `daten/` → `0253` (datenbauer);
  `kern/test/` → `0255` (testentwickler); `werkzeuge/kennzeichen/` → `0251` (kernbauer,
  freed after one night). **`0254` deliberately not opened into a sixth lane** — it hangs on
  `0255` because its acceptance is a claim about `0255`'s file.
- **Three proposals, all three accepted, two of them unchanged.** `0253` and `0255` needed
  nothing rewritten; `0254` needed its proof method replaced. **All three came out of the
  two packages that finished last night, and all three had `haengt_an: []` that was right by
  accident.** Recompute every time.
- **`0234` closed: `blockiert` → `abgelehnt`** with a pointer to `0241` (`fertig`), which
  delivered its residual scope. Frozen by `RUECKLAUF_MAX` either way; the status now says
  *decided* rather than *backlog*. One line, and it had been on this list for two runs.
- **For the Geschäftsführer, third run running: `RUECKLAUF_MAX` counts befunde, not fault.**
  `rueckläufe()` globs the review files and counts `urteil: zurueck`. It cannot tell "builder
  failed" from "reviewer corrected himself" from "the endpoint healed overnight" from "a
  concurrent lane falsified a true sentence". `0241` spent both of its on the reviewer's own
  corrections and survived; `0249` has spent one of its two on a lane that landed after it.
  **The brake is aimed at the builder and is hitting the schedule.**
- **`ops/plan.md` is stale in a way that now misleads.** `ops/reserviert.txt` reads `# frei`;
  the plan's whole "Der Engpass" section rests on a lock that has been gone for seven runs,
  and its Vorrang list (0224, 0225, 0189, 0208-schritt, 0165, 0172-weltpreis) is discharged
  for the **seventh** run running. **The real bottleneck is now structural and I can name it:
  nine packages on one file, one lane, and after tonight a chain seven deep.** Not mine to
  edit. Reported for the third time.
- **Check first next run:** (a) `0249` — is the clause **deleted** or replaced? A replacement
  that still asserts anything about `werte_probe.cpp` is Ruecklauf 3 and the package freezes.
  (b) `0255` — does its run summary say whether a `RIEGEL_OHNE_ZUSTAND` table moved or changed
  shape? `0251`'s riegel and `0254` both start from that. (c) `0064` — did it stay inside its
  three conditions, or touch lines the next eight packages must re-measure? (d) If `0064` is
  `fertig`, **remove the locks on `0230`/`0236` rather than renewing them down the chain.**
- **Blocked, five (was six):** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` — no
  agent may write `agents/`), `0003` (ADR), `0157` (no execution tool, successor `0243`).
- **Dormant, unchanged:** clamp-first vs add-first deviation from `spiel.md`
  (`alt = -100, wirkung = +50` gives 0 by spec, 50 clamp-first) → ADR → Geschäftsführer.
  `werte.cpp:718-720` still says "zwoelf Adressen … 31 Zeichen … hoechstens 323" where the
  Restwelt makes it fifteen/32/324; **still no open package owns `werte.cpp`** — and `0255`
  reads it without writing it, so that stays true.
  `werte::schaden` → `schuld` for CN/BR in `0237`'s `vermerk_abnahme`.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **eighteenth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, twenty-seventh run — entry of the thirteenth run.** Every decision turned on something I looked up:
  the two reviewers' own sentences (the table locations came from the `0244` review, not from
  the builder), the three proposals' `dateien` against each other, `0064`'s five dependencies
  against tonight's statuses. **The one piece of real thinking — that a parser raises altitude
  by naming a symbol instead of a file — was a correction to a rule I wrote last night, which
  is what the logbook is for.**
