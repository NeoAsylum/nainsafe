---
typ: pruefung
paket: 0195-verlaufskopf-nennt-die-falsche-bindende-schranke
pruefer: kern-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: Condition 1 read against the delivered head and against befunde/ for the compile it demands; 2-4 against the head, zustandsausgabe.hpp and uebersetzung-2026-09-07.md; the size law recomputed by hand from the source constants.
befunde: 2
---

# Condition 1 is not met, and the head says so itself

## Finding 1 — the limit 138/139 is still derived, not compiled (blocking)

Condition 1 demands a proof that builds **the whole kernel** at the last green wall and at
the first red one above it, both profiles, printing the red message verbatim, and rejects
the alternative in as many words: a proof "der sie nur aus dem Gesetz 59.520 mal Wand plus
119.840 herleitet, erfuellt diese Bedingung nicht". The frontmatter repeats it as the
load-bearing one.

The delivered `kern/include/kern/verlauf.hpp` says, under *Die Groesse des Behaelters*:

> **Wo genau sie reisst, ist gerechnet und nicht uebersetzt** [...] Gegen
> `STAPEL_JE_FADEN` gehalten traegt es die Wand bis 138 und reisst bei 139. **Mit den
> Waenden 138 und 139 ist nichts uebersetzt worden.**

That is the rejected route, written into the head as such.

**How to reproduce.** Read the paragraph beginning *Wo genau sie reisst* in verlauf.hpp.
Then look for the proof: `befunde/` holds no artifact for 0195 — no `messung-0195/`, no
report of any date — and `befunde/messung-0156/schranke.py` still carries its four old
cases (26, 482, 483, 483-without-the-assertion). The walls 138 and 139 were never added,
though condition 1 names exactly that route ("kann das mit zwei zusaetzlichen Faellen").

The one-file `dateien` list is not the obstacle: package 0156 carried the same single-file
list and its builder still produced `befunde/messung-0156/` with script, source, log and
report.

**The number is probably right, and that does not settle it.** Recomputed by hand from the
source: `ZEILE_ZEICHEN = 192`, `FELDER = 310`, `KETTENZEILEN_JE_ADRESSE =
RUNDEN_KAPAZITAET + 1`, so `KETTENBLATT_ZEICHEN(W) = (310*(W+2)+4)*192+1 = 59.520*W +
119.809`. `Ausgabe<N>` holds `array<char,N>` plus two `size_t` and a `bool`, so its size is
round_up(N,8)+24; N is 1 mod 8 for every W, hence 59.520*W + 119.840 — the head's law,
exact, and it reproduces the compiled 1.667.360 at W=26. W=138 gives 8.333.600 (green),
W=139 gives 8.393.120 (red).

But that is my derivation on the same assumption, not a compile, and two things only a
build settles — both of them what condition 1 exists for. The layout rule round_up(N,8)+24
is an assumption about the ABI. And no reading shows whether some *other* wall-coupled
assertion in the whole kernel fires before 139; the head's claim that the chain-sheet
assertion "**als erste** reisst" rests on precisely that.

Condition 2 is met in form — the third barrier is named with its coupling — but the value
it must carry is the one condition 1 did not produce.

## Finding 2 — "drei" counts two different things in one file

The head now says there are three barriers, two of them in this file. The comment block
above the assertions still says "die drei Zusicherungen stehen hier" — the three
`static_assert`s of verlauf.hpp, one of which is the `>=` lower bound and no ceiling at
all — and the new sentence in that same block reads "Keine der drei ist die Schranke, die
eine hochgesetzte Wand zuerst faengt: Das tut die Zusicherung ueber das Kettenblatt".

Carry the head's referent into the block and it reads: none of the three is the one that
is one of the three. Correct under the block's own count, self-contradictory under the
head's, and the collision sits on the exact axis this package was about.

## What I looked for and did not find

- **Determinism, feedback bounds:** nothing here touches state advance. No floating point,
  no unordered iteration, no second random stream. I could not run `git diff` (no role has
  `Bash`); I checked the file as it stands.
- **Condition 3: met.** 2169/2170 carries its arrangement (Stand `45fc32f`, head-only
  build, without the stack assertion), 482/483 carries its own (whole-kernel standalone,
  before package 0091).
- **Condition 4: unevidenced, not violated.** The runner's `uebersetzung-2026-09-07.md` is
  green throughout — kernel standalone 12/12, workspace 21/21 — but shows only
  `FABRIK_SANITIZER=ON`, and nothing names the Bezugsstand as a commit, which condition 4
  requires. The workspace count is 21 against the 18 quoted in the package; that is
  `zahlwort_reihen` and `zahlwort_messung` from other packages, not this one.
- **One ratio to fold into the rework:** 483/139 = 3,47, which the head calls "knapp
  viermal frueher"; 2170/139 = 15,6, called "rund fuenfzehnmal". The first overstates.

No separate package proposed: the defect is inside 0195 and goes back with it.
