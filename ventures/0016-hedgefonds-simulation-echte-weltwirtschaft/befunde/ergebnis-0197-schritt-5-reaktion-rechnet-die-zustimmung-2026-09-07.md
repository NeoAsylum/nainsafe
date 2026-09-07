---
typ: ergebnis
paket: 0197-schritt-5-reaktion-rechnet-die-zustimmung
rolle: kernbauer
datum: 2026-09-07
---

# No body built: the approval rule reads a quantity that is nowhere defined

Under the package's own clause -- "If you cannot find the approval-rating rule there in a
form a body can be built from, then **build nothing invented**" -- `schritt_5_reaktion`
stays one `schreiber.vortrag(platz)`. No source file changed. What is missing, exactly:

## The rule, traced to its end

`spiel.md`, section *Die Gegenkraefte*, counterforce 2: „Jede durchgesetzte Lobbyaktion
verschiebt Preise und damit Realeinkommen. **Sinkt das Realeinkommen, sinkt die
Zustimmung**; unter einer Schwelle wechselt die Regierung."

Its only quantified form is the comment at `zustimmung_elastizitaet` in `parameter.toml`:
„Aenderung der Zustimmung in Zehntausendsteln je Zehntausendstel Aenderung des
Realeinkommens". The body would therefore be
`zustimmung' = zustimmung + elastizitaet * Δrealeinkommen`.

## The missing quantity: `Realeinkommen`

Measured over `specs/` on 2026-09-07: **8 lines** mention it (`daten.md` 1, `spiel.md` 6,
`technik.md` 1). Every one is prose or an arrow in a chain diagram. None gives a formula,
a unit or a scale class. It is:

* **not a state address (T15)** -- the nine aggregates per territory are `Bevoelkerung`,
  `Erwerbstaetige`, `Produktivitaet`, `Preisniveau`, `Inflation`, `Leitzins`,
  `Wechselkurs`, `Staatsschuld`, `Haushaltssaldo`;
* **not a parameter key (T27)** and **not a vintage constant (T23)**;
* **not one of the twenty-two derived quantities (T48)** -- `kern/include/kern/werte.hpp`
  declares all of them and it is not among them.

T48 decides what that means, and the decision is not mine: „Ein Name in einer Formel
dieses Dokuments oder in `spiel.md`, der weder eine Zustandsadresse aus T15 noch ein
Parameterschlüssel aus T27 noch eine Jahrgangskonstante aus T23 noch eine der
**zweiundzwanzig** Größen oben ist, **ist ein Befund und keine Bauentscheidung**."

## A second gap, independent of the first

Even with `Realeinkommen` defined, the coefficient has no way into step 5.
`werte::Konstanten` carries six parameter keys -- `stufenweite`, `ausstiegsabschlag`,
`aufschlag`, `lobbykosten`, `gegenlobby_satz`, `regulierung_last` -- and
`zustimmung_elastizitaet` is not one of them. `schritt(zustand, aktionen, modus)` has no
parameter argument at all, and that signature is T10 verbatim. Widening it needs an ADR.

## Condition 2 is not reachable from step 5 -- two separate reasons

1. The rule is driven by the **change** of real income. `schritt_4_wirtschaft` is one
   `vortrag`, so all 152 economy addresses are identical before and after; any real income
   built from prices, price level or value added has Δ = 0, and approval does not move.
2. `zustimmung_elastizitaet = 0  # PLATZHALTER`. Zero times anything is zero.

**The second changed quantity has to come from step 4, not from step 5.** That is a
sequencing question and belongs to whoever orders the six step packages.

## The four conditions, one by one

1. **Not met** -- no computed value, because the rule is unbuildable as written.
2. **Not met, and unreachable here.** The measuring instrument the condition asks for
   already exists and was not touched: `probe_eine_runde` in `schritt_probe.cpp` counts
   over all 310 addresses and prints „%zu von 310 Groessen geaendert". The number is
   **1**, and it stays 1 -- the probe asserts `geaenderte == 1`, the last compiler verdict
   (`befunde/uebersetzung-2026-09-06.md`, `ergebnis: ok`) has it green, and this run
   changed no source. I did not build; the runner's verdict for today is the measurement.
3. **Not due.** The body still takes its block address by address, so the ascending chain
   in `kern/src/schritt.cpp` still ascends; nothing is retracted.
4. **Met** -- no probe added, removed or changed.

## What unblocks the package

A definition of `Realeinkommen`: either as a T48 quantity with a formula over existing
addresses, or as a T15 address. Until it exists, no agent can build this package -- and a
guessed behavioural equation would be measured by Maß 2 as the builder's choice.
