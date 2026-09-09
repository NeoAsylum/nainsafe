# A hedge fund against the real world economy

A turn-based strategy game. You run a hedge fund. The board is the actual world
economy, calibrated against real series from 2001 to 2021, and every number that moves
carries the chain of its causes with it.

The game is built by agents. The operator decides at the gates; in between the machine
works alone. **This repository is the running factory** (`~/fabrik` under WSL2, since
2026-08-27). It commits itself.

## The game

You place up to **three actions per round**, drawn from five kinds, and the world then
computes one year forward. Twenty rounds carry you from 2001 to 2021.

| action | what it does |
|---|---|
| **Position** | long or short on a country and sector, a currency, a government bond, or an exchange venue. Entering and leaving moves the price against you, the more so the larger your share of that market |
| **Stake** | a permanent share in a country and sector. Illiquid, two rounds to exit, and the only route to cheap lobbying |
| **Lobbying budget** | money on one policy instrument in one direction. It does not act at once but attaches as pressure, and whether it takes hold is decided against the counter-lobby |
| **Leverage** | borrowing at the policy rate plus a spread that rises with your visibility. Magnifies every position and every losing streak |
| **Visibility** | disclose a position or withdraw from view. Disclosure amplifies your lobbying because it creates public pressure, and feeds the supervision counter in every country you are present in |

The first three are the strategy families the game measures itself against. Leverage and
visibility are not strategies but amplifiers, and each carries its own punishment.

**You win** by reaching the mandate: fund assets above a threshold *and* influence above
a threshold in at least two countries, before round 20, without first hitting one of the
three ways of dying. Your score is the number of rounds it took.

**Five counterforces grow with your success**, which is what keeps the game from
collapsing into a single dominant line. Lobbying that works provokes the change of
government that undoes it. Every counterforce names the mechanism it acts through, not
just an intention.

### The world, in three layers

| layer | what it holds |
|---|---|
| 1 | **9 countries.** USA, China, Germany, Brazil, Japan, India, Chile as policy countries; Singapore and Saudi Arabia playable but not backtested |
| 2 | **30 exchange venues**, one per lead sector per territory, tradable but not influenceable |
| 3 | one non-playable rest-of-world aggregate |

Three sectors — agriculture, industry, services — two of them carrying trade flows.
The whole state is **890 numbers**. The country count is a parameter, not a constant, so
layer 2 grows with it as `B = 3·(L+1)`.

### Why it is backtested

Running in `weltlauf` mode with the fund switched off and policy instruments pinned to
their historical paths, the model has to reproduce the real world within stated error
bounds: 20 percent mean absolute percentage error on level series, 300 basis points on
rate series, directional accuracy of 0.6. It passes if at most half the check subjects
break. That is the difference between a world model and a themed backdrop.

## Where it stands, 2026-09-09

| | |
|---|---|
| C++ | 50 files, 40,252 lines |
| workshop tests | **23 of 29 green** — six red, worked on in open packages |
| work packages | 270 total, 240 finished |
| agent runs | 2,103 journalled, 946 productive |
| decisions | 11 ADRs, Gate 1 granted |

The design documents under `specs/` were **translated to English on 2026-09-08**, all 50
sections. Section headings stay German on purpose: 169 findings cite this corpus by
heading, and translating a heading breaks a citation chain silently.

## How it is built

Work is cut into **packages, not roles**. Two packages of the same role run at once; two
packages whose file lists overlap never do. A package carries its acceptance condition
before anyone starts, and a reviewer who never saw the builder's reasoning checks it
afterwards.

```
design ─[Gate 1]─> build ─[Gate 2]─> operation ─[Gate 3]
```

Only the operator moves a status across a gate. **No agent deploys, sends, spends money
or deletes.** No role gets a shell, because a shell walks around every `Edit()`
restriction — measured on 2026-08-30, and proved again on 2026-09-06 with three separate
write routes.

After every build step the runner calls the compiler, and its verdict lands in
`ventures/<id>/befunde/uebersetzung-<date>.md`. It is the only voice in this factory that
does not come from a model.

## Reading discipline

An agent's context is re-sent on **every turn** of its run. Measured 2026-09-07: 98
percent of a run's input is cache reads, replayed about 39 times. The bill is context
size times turns. So `ops/inhalt-<venture>.md` lists every section of the specifications
with its line range in under 6 kB, and agents read that instead of the 710 kB the two
large ones now hold. Cutting what a run carries cut its cost by half to four fifths.

## The rules, in reading order

| file | says |
|---|---|
| `CLAUDE.md` | house rules — four hard rules, output budgets, reading discipline |
| `grenzen.md` | what the business may **sell**: nine limits |
| `agentenbau.md` | what the factory can **build**: six buildability questions |
| `decisions/` | why it is the way it is — 11 ADRs |
| `notizen/lehren.md` | what went wrong and what follows from it |

No agent may change these; the tools are withheld (`agents/lauf.py:NIE`).

## The schedule

```
:00 and :30   agents/tageslauf.py        runs the build chain until the daily budget is met
:10           agents/uebersetzungslauf.py resumes any translation left open
:20           einrichtung/sichern.sh     push, plus one bundle per day
every 30 min  agents/dashboard.py        ops/dashboard.html
Sun 07:00     agents/wochenlauf.py       portfolio, improvement, digest
@reboot       einrichtung/anker-prozess.sh keeps the VM from idling out
```

Hourly rather than nightly, and twice an hour rather than once, because the Windows host
sleeps and cron catches nothing up. On 2026-09-03 it slept from 21:30 to 15:00 and a
whole factory day vanished silently. A lock admits only one at a time, and once the daily
budget is reached an attempt ends after zero rounds without a single agent call.

## By hand

```sh
bash    einrichtung/pruefen.sh          # 23 conditions for unattended operation
python3 einrichtung/rollen-pruefen.py   # every role file against the house rules
python3 agents/inhalt.py                # regenerate the section index
python3 agents/kontingent.py            # consumption per role
python3 agents/baulauf.py --trocken     # what the next round would pull
python3 agents/uebersetzungslauf.py --trocken
```

## Layout

| path | contents |
|---|---|
| `specs/` | the design: `spiel.md` (rules), `technik.md` (model), `daten.md` (sources) |
| `ventures/` | the build: `kern/` C++ core, `werkzeuge/` checkers, `aufgaben/`, `befunde/` |
| `agents/` | runners and role files; `agents/rollen/archiv/` is retired |
| `ops/` | reports for the operator, `ops/plan.md` first |
| `notizen/` | one logbook per role, plus `lehren.md` for everyone |
| `decisions/`, `gates/` | the reasoning, and the operator's calls |
| `einrichtung/` | checks and setup |
| `archiv/` | the search phase this project came out of |

`state.db` is not versioned. It is reproducible from `schema/state.sql` and the
frontmatter, and it would conflict on every run.

## Where this came from

Until 2026-08-31 the factory searched for a business instead of building one: 81
signals, 49 research notes, 15 ideas rejected. Those sit under `archiv/suche/`, and the
rejections are the evidence behind decisions 0004 to 0011. The switch is
`agents/nachtlauf.py:FOKUS` — set it to `None` and the search resumes; nothing was
deleted.
