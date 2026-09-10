---
id: 0291-wie-die-vierzig-platzhalter-zu-ihren-werten-kommen
rolle: spielentwerfer
status: offen
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: "1. **A new section of `spiel.md` names every route by which a calibration value can arrive, and each route is defined by what it needs and who can execute it.** A route that requires running the game is admissible only if the section says which role runs it and with which tool — see condition 3. 2. **All forty marks are enumerated, each assigned to exactly one route.** The forty are the lines of `parameter.toml` carrying `# Kalibriert: Selbstspieler`, measured 2026-09-10 at HEAD: 341, 355, 368, 378, 397, 413, 431, 443, 456, 468, 487, 500, 518, 535, 545, 556, 568, 584, 610, 625, 649, 658, 667, 676, 707, 717, 730, 742, 758, 769, 789, 802, 813, 862, 874, 890, 995, 1102, 1125, 1145. Each gets its line, its parameter name and its route. A property stated over the set — 'all reaction parameters go the same way' — does not satisfy this condition; forty lines, forty assignments. Deviations from the count are named: if a line is not in fact a calibration mark, say so and say why. 3. **The section states in one sentence that `Kalibriert: Selbstspieler` is today an unreachable route, and does not assign it to any of the forty.** No agent role can execute a program: `agents/lauf.py:NIE` denies `Bash` globally, `selbstspieler` stands in `baulauf.py:PRUEFROLLEN` and gets no runner that plays a game, and package `0157` has been `blockiert` on exactly this tool question since 2026-09-06. A route that presupposes a self-play run is a gate to the operator, and the section says so with that word. 4. **At least one route is executable today by a role that exists**, named with the role and the file it would write. If the honest answer is that none of the forty can be reached without the operator, the section says that plainly and the package is still met — but then it names what the operator would have to run, and how long it takes. 5. **No number is invented.** The section decides *how* a value arrives, not which value. Any concrete figure appearing in it carries a source with a retrieval date, or is marked an estimate. 6. **Nothing outside the new section of `spiel.md` is written.** `parameter.toml` is not touched — the role has no write right to it (`Edit(specs/**)` and `Edit(ventures/**/aufgaben/**)` only), and that is a property of this package, not an oversight."
vermerk_annahme: "CREATED 2026-09-10 (24th run), project manager. **This is Vorrang 3 of the 15th plan, and it is the item the Geschäftsführer wrote as: „Solange das offen ist, rechnet die Runde und trifft null.\" Package `0284` made the round compute. This one is about whether it computes anything true.** || **THE COUNT IS 40, NOT 47, AND I MEASURED IT MYSELF.** The plan says the mark stands in 47 comments. At HEAD on 2026-09-10, `Grep -c 'Kalibriert:'` over `parameter.toml` gives **40**, all forty enumerated by line in condition 2, and `parameter.toml` is the only live file that carries the string — the other hits are archived trees under `befunde/messung-0069/` and `messung-0105/`. Three further `Selbstspieler` mentions in the file (`:84`, `:119`, `:1066`) are prose, not calibration marks; 40 + 3 = 43, so 47 is not reachable that way either. **I did not cut the package to the plan's number.** A set condition written as a sweep is what killed three packages on `0275`; the fourth demanded an enumeration and passed. **This one is an enumeration from the start.** || **THE FOUR CHECKS.** *Role* `spielentwerfer` stands in `baulauf.py:BAUROLLEN` — I checked, because that check caught a `rolle: builder` on 2026-09-02 that no runner would ever have drawn. *File cut*: `specs/.../spiel.md` — **its own lane.** `technik.md` is a different file (`0236` runs on it tonight) and `daten.md` a third (`0287`). Nobody else holds `spiel.md`. *Acceptance*: six conditions; 2 is an enumeration, 3 and 4 are the ones that make it honest rather than green. *Precondition*: none. || **THE REASON THIS IS A ROUTE AND NOT A CALIBRATION, and it is the thing I checked before cutting.** The role file grants `Edit(specs/**)` and `Edit(ventures/**/aufgaben/**)` — **it cannot write `parameter.toml`, which sits at `ventures/<venture>/parameter.toml`, outside `aufgaben/`.** A package asking this role to *fill* the forty would demand a file the role's own tools withhold. That is exactly the defect that cost `0284` its condition 6 tonight. So the deliverable is the route, in the spec, and the values follow later from whoever the section names. || **THE TRAP IS CONDITION 3, and it is the whole point.** The cheap way to satisfy conditions 1 and 2 is to write „calibrated by the self-player\" forty times in better prose. That is the state the tree is already in — and it is unreachable: **no role has `Bash`** (`agents/lauf.py:NIE`), `selbstspieler` is a `PRUEFROLLE` with no runner that plays a game, and `0157` has been `blockiert` on this same tool question since 2026-09-06, re-checked every run since. **A route nobody can walk is the design equivalent of a check whose subject cannot move** (`notizen/lehren.md`, 2026-09-06). Condition 4 is its counterweight: name one route that works today, or say plainly that none does and name what the operator must run. **Both answers are accepted. Silence is not.** || **YOU DECIDE, YOU DO NOT COLLECT.** Your role file is explicit: listing three possibilities and leaving the choice to the next agent is not a design. Forty assignments, each to one route. || **DO NOT READ `spiel.md` WHOLE.** It is about 271 kB; `ops/inhalt-0016-hedgefonds-simulation-echte-weltwirtschaft.md:37-55` lists all 15 sections with line spans in under 4 kB. The two you will want are **`Wie die vier Masse berechnet werden`** (`:2496-2874`) and **`Offene Entwurfsfragen`** (`:3096-3298`); the back-comparison measure lives in the first and is the most likely source of a route that does not need a running game. `Grep -n` the heading for today's line. || **`spiel.md` IS A GERMAN DOCUMENT AND YOUR SECTION IS GERMAN** (CLAUDE.md: a document that switches language mid-way is unreadable, and 169 findings cite this file by wording). This package is English; your section is not. || **YOU CANNOT RUN ANYTHING**, and that is not a limitation of this package but its subject."
---

# How the forty placeholders get their values

`parameter.toml` carries `# Kalibriert: Selbstspieler` on forty parameters. It is the
tree's own note that a number is a placeholder and that something later will find the real
one. Nothing can: no agent role in this factory can execute a program, so the self-player
that the note names has never run and cannot be scheduled.

Since package `0284` the round computes — step 3 writes the path level, step 5 reaches
`werte::schaden`, and the arithmetic that was multiplying by nought now multiplies by
these forty numbers. **That is what makes this urgent rather than tidy.** A simulation that
computes with forty placeholders produces confident output that means nothing, and it does
so more convincingly the better the rest of the machinery gets.

## What this package decides

Not the values. The **routes** — the ways a calibration value can arrive at all, given
that the one route written in the file is closed. Candidates the section has to weigh, and
it must choose per parameter rather than in general:

- **From the back-comparison series.** `spiel.md` already defines a measure against real
  time series (`Wie die vier Masse berechnet werden`, `:2496-2874`). A parameter that can
  be pinned by fitting the model's output to a series does not need a played game.
- **From a named real-world anchor**, with a source and a retrieval date, as the house
  rules require of every claim about the outside world.
- **From an analytic condition** the design imposes — a threshold that must sit where two
  named forces balance, solvable on paper.
- **By the operator, at a gate**, if the honest answer is that the value needs a run and
  only he can run it. Then the section says what he runs and roughly how long it takes.

## What must not happen

Rewriting the mark. Forty comments saying `Kalibriert: Selbstspieler` in better German are
forty comments that still name a route nobody can walk. The section either assigns each
parameter to a route someone can take, or says which ones are stuck and who unsticks them.

## Where this sits relative to `0157`

`0157-beschraenktheit-nach-dem-ersten-rechnenden-schritt` has been `blockiert` since
2026-09-06 on the same wall: the bruchtester has no tool that executes a program. **This
package does not unblock it and does not try to.** It answers the narrower question of
whether the forty numbers have any route at all that does not run through that wall. If the
answer is no for most of them, that is a finding for the Geschäftsführer and belongs in his
report to the operator, not in a third round between us.
