---
typ: zielbild
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
quelle: operator, 2026-09-01
status: directional, not binding for stage 1
---

# Target picture — what ends up on the screen

Set by the operator on 2026-09-01. It is **not a design**, but the direction the design
is meant to run toward. The game designer works concrete rules out of it; what stands
here is the picture, not the mechanics.

## The directive verbatim

> Die Zieldarstellung soll Interaktion erlauben und dabei rewarding sein und Progression
> auf unterschiedlichen Wegen erlauben. Hier wird Grafik schließlich eine große Rolle
> spielen. […] Ausbau eines Hedge-Fund-Hauptquartiers. Dort könnte man auch Skills
> unlocken und Aktionen und Operationen triggern. Zudem könnte man dort dann separat
> steuern, in welche Märkte man einsteigen kann, und auf einer weiteren Ansicht — der
> Weltkugel, die sich mit den Entscheidungen verändert — die unterschiedlichen Märkte und
> die weltpolitischen Entscheidungen beeinflussen.

## Two views

**The headquarters.** Expandable. It houses the abilities, unlocks actions and
operations, and is the place where it is decided which markets the fund enters.

**The globe.** It changes with the decisions and shows markets and world-political
effects.

## Why this fits the rest — and is not decoration

The two views show exactly the quantities the self-player measures anyway
(`agentenbau.md`, *Die ehrliche Grenze*):

| View | shows | is the measure |
|---|---|---|
| headquarters, ability paths | several ways to the goal, visible side by side | **strategy diversity** |
| globe that reacts | what a decision triggered, and where | **decision density** |
| expansion stages over the game | how the best option shifts over the course | **shift of the optimum** |

From this follows the design principle against which every later decision can be
measured:

> **What is measured is what gets drawn.**

A view that shows something no measure captures is ornament and costs design effort. A
view that shows a measure earns its effort twice over — it serves the documented wish of
the buyers *and* makes visible to the operator what the factory computes at night.

## What it costs — the one place where it collides

`agentenbau.md` explicitly allows the core promise to be the visual impression, as long
as the **state** stays retrievable as text. That is satisfied here: expansion stages,
unlocked abilities, entered markets and influence per country are numbers.

The collision lies elsewhere, at criterion 6 — **how often does someone have to decide
about design?**

**A headquarters with rooms needs a visual language.** How expensive that is depends on
whether it is *drawn* or *constructed* — and that is a distinction I had at first
overlooked.

> **Addendum of 2026-09-01, from the operator:** *„Ein solches Hauptquartier kann auch
> konstruktiv durch einen Agenten entworfen werden."*
>
> That is correct and corrects the original version of this section, which claimed that
> no agent can produce imagery. What is right: an agent does not **draw**, but it
> **constructs** — geometry from basic shapes, rooms from a grid, symbols from rules,
> all as SVG.
>
> And with that the same argument applies as for the view in the first place: **SVG is
> text.** A constructed headquarters is checkable like every other output of this
> factory — an agent can read it, compare it and hold it against the state. A painted
> picture it cannot.
>
> The expensive remainder is thereby small and clearly delimited: the **visual language
> itself** — which shapes, which colors, which layout. That is a decision, not ongoing
> work, and exactly the cyclical form that criterion 6 allows.

Three paths remain, all open and all for the operator to decide — later, not now:

1. **Generated depiction instead of drawn.** The globe is thereby almost free to have:
   country borders are free data, the coloring is a projection of the state, rendered as
   SVG. No imagery, every change follows from a number. For the headquarters it holds
   only in part — a schematic, iconic layout is generatable, a drawn room is not.
2. **Purchased imagery.** A package costs money and is therefore a gate, but no
   personnel — G9 is not touched. The time cost is one-off instead of ongoing.
3. **A visual language that arises from rules.** Strict, iconic, few colors, everything
   from basic shapes. It costs one design decision at the start and almost none after —
   exactly the cyclical form that criterion 6 demands.

**The globe is nearly free, the headquarters is the expensive part.** This decision is
made before stage 3 begins, not earlier.

## The order stands

The target picture changes nothing about the three stages:

1. **The state output is the first interface.** Overview, detail, diff — demanded by G8
   anyway, fully checkable, makes the game playable and self-playable before any
   graphics exist.
2. **The view is generated from the schema.** 310 addresses, thirteen scale classes —
   what follows from that is derivable and therefore checkable.
3. **The taste layer.** Here the target picture lives, and here a human decides.

Whoever pulls stage 3 forward builds an interface for a core that does not exist, and
loses the only means of checking that this factory has.
