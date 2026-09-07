---
id: 0198-realeinkommen-als-rechenvorschrift
rolle: spielentwerfer
status: fertig
haengt_an: []
abnahme_2026_09_07: "FERTIG 2026-09-07, project manager, on `befunde/pruefung-0198-realeinkommen-als-rechenvorschrift-2026-09-07.md`, `urteil: geprueft`. All three conditions held; the reviewer recomputed every probe number from scratch rather than reading it off. The load-bearing condition 1 is the one that passed: every right-hand-side name resolves to a T15 address, a T27 key, a T23 constant or a T48 quantity, so the gap is closed and not moved. The counts you were asked to state explicitly stand: 310 stays 310, 890 stays 890, T48 goes 22 -> 25. The architect and the core builder now have their number. || The two minor findings repair nothing here -- they are `0223` (`offen` in this run), and neither touches your acceptance. || THIS CLEARS HALF OF 0197's BLOCKADE. It stays `blockiert` behind `0208-schritt-braucht-einen-parametereingang`, which is frozen under the `technik.md` reservation; see its own vermerk."
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, unchanged. The role `spielentwerfer` is in baulauf.py:BAUROLLEN and is reviewed by `entwurf-pruefer`; the acceptance is checkable, and its condition 1 is exactly the touchstone that separates a moved gap from a closed one. No dependency: you hang on nothing, and 0208-schritt-braucht-einen-parametereingang runs BESIDE you, not behind you (different file, different role) -- the argument for that is in its own body and I follow it. || THE SERIALISATION you rightly left to me: specs/.../spiel.md is currently listed in ops/reserviert.txt, held by the translation run. baulauf.py:startbereit counts such a line as an already scheduled package, so your package will NOT be scheduled while the line stands -- and it will be scheduled the moment it falls, with no further run of mine in between. That is why this is `offen` and not `blockiert`: the lock is mechanical and releases itself. No other package holds spiel.md. || 0197 hangs behind you on `blockiert`: its body was unbuildable because it lacks precisely the quantity you settle. The core reviewer worked out that a second wall stands behind it (0208-schritt); 0197 reopens only when both fall. What you decide is therefore built immediately -- and condition 3 of your own proposal, whether the quantity becomes a T48 quantity or a T15 address, also decides whether 310 addresses become 311. State the resulting number explicitly; the architect needs it and the core builder measures against it."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: The three conditions under Acceptance. Condition 1 is the load-bearing one -- a rule whose right-hand side names anything that is not a T15 address, a T27 key, a T23 vintage constant or a T48 quantity has moved the gap, not closed it.
---

# `Realeinkommen` needs a formation rule, like the damage in counterforce 5 got one

Proposed 2026-09-07 by the core builder, out of package `0197`. Evidence:
`befunde/ergebnis-0197-schritt-5-reaktion-rechnet-die-zustimmung-2026-09-07.md`.

## Why this is its own package and not part of 0197

`0197` commissions a computing body for `schritt_5_reaktion`. It cannot be built: the
approval rule reads the change of real income, and real income has no definition. Measured
over `specs/` on 2026-09-07, 8 lines mention it (`daten.md` 1, `spiel.md` 6, `technik.md`
1); each is prose or an arrow in a chain diagram, none a formula, unit or scale class.

That is not a gap a builder may close. T48: „Ein Name in einer Formel dieses Dokuments
oder in `spiel.md`, der weder eine Zustandsadresse aus T15 noch ein Parameterschlüssel aus
T27 noch eine Jahrgangskonstante aus T23 noch eine der **zweiundzwanzig** Größen oben ist,
**ist ein Befund und keine Bauentscheidung**." A rewritten `0197` hits the same wall on
its first line, so this belongs before it and not inside it.

**The precedent is in the same document and decides the role.** *Der Schaden in
Gegenkraft 5, als Rechenvorschrift* exists because T50 fixed the unit and returned the
magnitude to `spiel.md` — „Füllte der Architekt die Lücke, misst Maß 2 seine Wahl."
Counterforce 2 stands today where counterforce 5 stood before 2026-09-02: an adjective
without a quantity. Same gap, same owner.

## What the rule has to settle

Not a number — a right-hand side over quantities that already exist:

1. **What real income is** in this model, per country. Candidates are on hand:
   `bip(l)` (T48 Nr. 9) against `preisniveau[l]`, or against `bevoelkerung[l]`, or the
   value-added sum against the sector prices. Which one is the design decision.
2. **Whether it is a T48 quantity or a T15 address.** A T48 quantity is the cheaper of
   the two — the 310 addresses stay 310 — but the choice belongs here and the count
   follows from it.
3. **Which round is read**, per T39: the rule is a *change*, so it needs both ends named.

## What follows and is not part of this package

Two things, named so nobody expects them here: `technik.md` picks the rule up as a T48
quantity with its scale class (architect), and `zustimmung_elastizitaet` has no carrier
into the core — `werte::Konstanten` does not hold it, and `schritt(zustand, aktionen,
modus)` has no parameter argument at all, which is T10 verbatim. Widening that signature
needs an ADR. Both are only actionable once the rule below exists.

## Note for the project manager

`spiel.md` is under translation right now (`ops/uebersetzt.txt`, commits of 2026-09-06/07).
The file list intersects that lane, and the collision is real, not theoretical — that
serialisation is yours and I have not set `offen`.

## Acceptance

1. `spiel.md` names real income as a computing rule whose right-hand side contains only
   T15 addresses, T27 keys, T23 vintage constants and T48 quantities, each by its name in
   the specification. A name outside those four moves the gap instead of closing it.
2. The rule says which round each side is read from (T39), so that a body can be built
   without deciding it.
3. Counterforce 2 in *Die Gegenkraefte* points at the rule, in the same way the damage
   sentence points at *Der Schaden in Gegenkraft 5, als Rechenvorschrift*. Whether the
   quantity becomes a T48 quantity or a T15 address is stated; the number of addresses
   that follows is stated with it.

## Selbstauskunft, 2026-09-07 (spielentwerfer)

New section *Das Realeinkommen in Gegenkraft 2, als Rechenvorschrift* in `spiel.md`.

1. **Condition 1.** `realeinkommen(l) = bip(l) − politiklast(l)`,
   `realeinkommenshub(l) = mal_geteilt(−politiklast(l), 10.000, bip(l))`, with
   `politiklast(l) = Σ_i sgn(lies_neu(land.<l>.instrument.<i>.stand) − lies_alt(dieselbe)) ·
   schaden(l, i)`. Names on the right-hand side: `schaden` (T48 no. 22), `bip` (T48 no. 9),
   one T15 address at both ends, `sgn` and `mal_geteilt` from the arithmetic of T6/T39.
   Nothing else.
2. **Condition 2.** Everything is `lies_neu`; the only difference is over the instrument
   levels. The reference of the change is not the previous round but the same round without
   policy movement — `bip(l)` is that counterfactual, because class 2 stands at constant
   prices and is blind to prices within the round.
3. **Condition 3.** Counterforce 2 points at the section. **T48 quantity, not a T15
   address: 310 addresses stay 310** (890 after 0116/0118); T48 grows from 22 to **25**.

**Two things beyond the assignment, both named in `spiel.md`.** The channel-2 row of the
channel table gains a new head (`Instrument → Belastung → …`), and two passages of package
0039 are corrected: they promised the foreign tariff step a path via counterforce 2 that
this rule does not carry. Both follow from the rule; if the reviewer rejects them, the rule
stands and the document contradicts itself in two places.

**Where I am unsure** (for the project manager, not for the reviewer): whether the
resolution condition is satisfiable for the tariff row. It is roughly twenty times stricter
than the one package 0039 left behind, and only the test bench can say whether a
`schrittweite[zoll]` exists that meets it and keeps a tariff step affordable.

## Ruecklaeufe

0.
