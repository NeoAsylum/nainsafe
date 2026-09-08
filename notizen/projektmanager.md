# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 16953 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-6.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · on a
Ruecklauf, narrow `dateien` to what the package still needs · a satisfied `haengt_an` is
inert — name the package you must **not** run beside, and recompute a proposed one, never
carry it over · the asymmetry test · a sweep is unprovable, an enumeration is countable ·
ask whether the role owns the tools its own acceptance requires · before writing „and the
number lands in the report", ask where the number physically goes · never lock past the
next link, and re-decide the one link every run · an already-`offen` package is not a
vetted package — re-ask the tool question before it gets a lane · a residue with a named
fix and no owner becomes a package; one with an owner-less *decision* does not.

---

## Two reports quoted the same filename against each other, and only the source settled it — 2026-09-08 (seventeenth run)

`0265` was a proposal to fix a red `bezeichner_riegel`. It quotes
`befunde/uebersetzung-2026-09-08.md` — **FAILED**, one identifier, `festkomma_probe.cpp:136`,
`ABBRUCH_MELDET`. The `0257` Ruecklauf review quotes **the same filename** as *Passed* twice,
`:147` and `:416`. Both agents were honest and both quotes were accurate when taken. **The
runner rewrites that file in place every night, so a citation to it is a citation to whatever
it says at the moment you look.**

I settled it by grepping the source: one hit, `:501`, inside the `!ABBRUCH_MELDET(...)`
history comment the riegel never flagged — exactly the site `0265` itself argued should stay.
`0265` → `fertig` with a reference, subsumed by `0257`'s Ruecklauf 1, which had ordered
precisely this fix as Finding 1 hours earlier.

**This is the rule I already carry (*never cite the mutable report*) seen from the other end.**
I had it as advice for what to write into a package. It is also a **reading** rule: when two
sources disagree and one of them is `uebersetzung-<datum>.md`, do not adjudicate between the
quotes — go to the file the quotes are about. Cost me two greps. Reading the two reports
harder would have produced a wrong answer with high confidence, because both are true.

**And the near-miss underneath it:** a proposal written from a *running* pass describes a
world that the same pass then changes. `0265` was proposed out of `0259` while `0257` stood
`zurueck` with the fix already ordered. **Before accepting any proposal that cites tonight's
report, check whether a package in the same pass already owns the defect.**

## `Edit()` creates files; there is no `Write` anywhere, and now I have the citation

`0264` asks for a new file, `kern/test/kennzeichen_probe.cpp`. The testentwickler's frontmatter
lists `Edit(ventures/**)` and no `Write`, and I nearly wrote a condition around it.
`agents/lauf.py` answers it in terms: *„Ausschliesslich Edit(), nie Write(): … Edit() deckt
alle eingebauten Werkzeuge ab, die Dateien aendern, **das Anlegen neuer Dateien
eingeschlossen**."* The reason is not economy — a `Write()` path rule is *accepted and never
evaluated*, so it looks like protection and is none.

**So: no package ever needs a `Write` and no acceptance should ask for one.** This will recur —
every new probe, every new riegel, every new tool directory. It is answered.

## A residue with an owner-less *design* decision is not nothing — it is an architekt package

Last run I split residues two ways: named fix and no owner → package; owner-less decision →
Geschäftsführer. **That split was too coarse and I found the third case tonight.**

T7 `:812-832` fully specifies `multiplikationsriegel.cpp` and says of it *„and it is not yet
built"*; §31 report 1 routes it to me by name. The `0074` review then laid two lines beside it
as a *remark, not a finding*. I re-read both at HEAD rather than take them:
`schritt.cpp:405` is `static_assert(4 * (12 + 9 + 1) + 22 + 40 + 2 == 152, …)` — plain literals,
matching none of the four rules; `festkomma.cpp:91` is `"a*b sprengt i64 …"` — **inside a string
literal**, and T7 drops *comment* text and is silent on strings.

**T7 is deny-by-default, so a latch built to its wording goes red on its first run.** The
builder cannot invent a fifth rule (that is designing) and I cannot write one (same). But the
work is not stuck and it is not the operator's: **the decision has an owner — the architekt —
and `technik.md` is where it lives.** That became `0268`, which asks for the decision and
explicitly does not build the latch; the latch is its successor and touches no `specs/` file.

**The general form:** before sending a decision upward, ask whether a *role* owns it. Only a
decision no role owns goes to the Geschäftsführer. `werte::schaden` → `schuld` still does —
it needs `spiel.md` **and** a judgement about start state versus clamping that no package
frames. This one only needed the right role.

**One thing `0268` must not be let to skip, because nobody else measures it:** the 92-line
mapping was taken with pattern ` \* ` — spaced only. T7 `:832` demands the latch read `a*b`
too. So `festkomma.cpp:91` is **not in the 92**, and the reference table is not the set the
latch sees. Correct, and not the same thing.

## The re-vet was method this time, not luck

Last run I caught `0074`'s unsatisfiable condition 3 by opening a body I had no procedural
reason to open, and wrote that down as luck. **Tonight I ran it as a step:** `0084` has stood
`offen` since 2026-09-05 and was about to take the lane, so I re-asked the tool question before
giving it one. Its condition 2 wants 25 index values *recomputed from source* — same bauart as
`0074`'s broken one. It holds: the architekt has `WebFetch` **and** `WebSearch`
(`agents/rollen/architekt.md:8-9`) plus `Edit(specs/**)`. Checked, not assumed.

**What the re-vet did turn up is smaller and would still have cost a run:** `0084`'s closing
paragraph *Zur Reihenfolge auf `technik.md`* names five packages as holding the file and **all
five are `fertig`**, and it tells the builder *welches zuerst laeuft, entscheidet die Sortierung
und nicht ich* — which stopped being true when I started ordering that queue by retargeting
locks. A stale paragraph that describes the factory's mechanics is worse than a stale line
number: a builder checks a number and trusts a mechanism. Flagged in the vermerk, not deleted.

## Offene Fährten — 2026-09-08, seventeenth run

- **Seven to `fertig`** (`0074`, `0257`, `0259`, `0261`, `0262`, `0263-die-achtundsiebzig`,
  `0263-eine-tabelle`), **none back.** Every `gebaut` package had a verdict and every verdict
  was `geprueft` — `0257` on its Ruecklauf 1, both comment fixes confirmed. **Review is empty
  going in, so tonight's agents are Bau only.**
- **Lanes tonight: four, against eight slots.** `technik.md` → `0084`;
  `kern/test/kennzeichen_probe.cpp` + `kern/CMakeLists.txt` → `0264`;
  `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` → `0267`; two files in `daten/` → `0266`.
  **Four slots idle and I could not honestly fill them:** every other `offen` package is an
  architekt on `technik.md`, and that is one lane by construction.
- **Four proposals: three accepted, one subsumed.** `0264` and `0267` needed **nothing
  rewritten** — both arrived with narrowed green clauses and `0267` with a bait *and* two
  must-stay-silent cases. **That is three runs in a row now.** The green-clause wording problem
  I nearly sent to the operator as a `CLAUDE.md` question is self-correcting; **drop it.**
- **`0266` needed the tool question and would not have been buildable without it.** Its
  acceptance said *every package that has rewritten the body since* — **no `git`, no history.**
  Appended a derivation over `aufgaben/` frontmatter (`dateien:` names the file, `status: fertig`,
  date from its befund), which gives package ids instead of a hash. Same defect class as
  `0074`'s condition 3, caught before the lane this time.
- **Check first next run:** (a) `0084` `fertig` → `0092`, `0230`, `0236`, `0268` startable at
  once on `technik.md`; **re-decide, do not renew** — `0092` heads the chain (`0181` → `0226`),
  `0268` unblocks a spec-mandated tool, and that is a genuine contest. (b) Did `0267` fire on
  `0264`'s new probe file? Both were told about each other; if it fired, the bar works and the
  report is not a defect. (c) `0266`'s derived set for `deckungsbefund-1997.md` — does it match
  the proposal's `0252`/`0253`/`0256`/`0262`?
- **For the Geschäftsführer, one item, and it is not new but it is now standing:**
  `belegstellen_wortabstand` and `belegstellen_kopfzahlen` are red at HEAD on the tool's **own
  head comment** measuring itself against a moved `HEAD` (*„Bezugsstand im Kommentar: 2f2f79f;
  HEAD zu Beginn: 6f2ec03"*). **No agent can read a commit, so no agent can write the value
  this check demands.** It is a check whose reference point is structurally unreachable by the
  role that would repair it — not a package, and I told three builders tonight not to chase it.
  `RUECKLAUF_MAX` counting befunde rather than fault stands, sixth run running.
- **`ops/plan.md`, tenth run:** Vorrang (0224, 0225, 0189, 0208-schritt, 0165, 0172-weltpreis)
  **fully discharged**; „Der Engpass" still rests on `ops/reserviert.txt` holding `technik.md`,
  and the file reads `# frei` — **eleventh run.** Its recommendation C answers a question that
  no longer exists. **The real bottleneck is unchanged and is not a lock: five architekt
  packages on one file, one lane a night.** Not mine to edit. Reported, fourth time.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` — no
  agent may write `agents/`), `0003` (ADR), `0157` (no execution tool, successor `0243`).
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` → `schuld`
  for CN/BR — **still Geschäftsführer, and now for a sharper reason** (see above: no *role*
  owns the start-state-vs-clamp judgement, which is what separates it from `0268`). The `0254`
  residue — one stale sentence in a `CMakeLists.txt` error message — has a plausible owner in
  `0264`, which opens that file tonight. **Check it next run.**
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twenty-second run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-first run.** The run turned on three lookups — the source file
  behind two contradicting reports, `lauf.py` on `Write`, and the architekt's tool list. None
  wanted a deeper step; all three wanted me to check instead of infer.

