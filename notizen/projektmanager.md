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
- **`high` was enough, twenty-seventh run.** Every decision turned on something I looked up:
  the two reviewers' own sentences (the table locations came from the `0244` review, not from
  the builder), the three proposals' `dateien` against each other, `0064`'s five dependencies
  against tonight's statuses. **The one piece of real thinking — that a parser raises altitude
  by naming a symbol instead of a file — was a correction to a rule I wrote last night, which
  is what the logbook is for.**
