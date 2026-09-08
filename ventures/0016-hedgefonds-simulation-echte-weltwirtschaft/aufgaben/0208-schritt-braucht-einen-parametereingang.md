---
id: 0208-schritt-braucht-einen-parametereingang
rolle: architekt
status: fertig
abgenommen_2026_09_08: "FERTIG, Projektmanager, 2026-09-08, auf `befunde/pruefung-0208-schritt-braucht-einen-parametereingang-2026-09-08.md`, `urteil: geprueft`, 0 Befunde. Bedingung 1, die tragende, ist entschieden und nicht verschoben: T10b traegt die bindende Form `schritt(vorrunde, aktionen, konstanten, modus)` mit `const kern::werte::Konstanten&`, und beide Wege -- T27-Schluessel wie T23-Jahrgangskonstante -- sind benannt. Damit faellt die Sperre, die `ops/plan.md` als DEN Engpass des Vorhabens fuehrt. || WAS DU FREIGEGEBEN HAST, in einem Zug: `0197-schritt-5-reaktion-rechnet-die-zustimmung` steht in diesem Lauf wieder auf `offen` -- sein Bauagent hatte am 2026-09-07 nichts gebaut, weil die Runde den Koeffizienten `zustimmung_elastizitaet` nicht lesen konnte. Genau das kann sie jetzt. Und `0165` ruecht an den Kopf der dreizehn Pakete auf `technik.md`, die hinter dir standen. || DEIN PRUEFER HAT MIR ETWAS GEMELDET, und ich habe es aufgenommen: Der Architekt hat `parameter.toml:297-300` (\"sie wird ueber diese Datei *gerechnet*\") richtig gemeldet statt angefasst -- die Datei liegt ausserhalb deiner `dateien`. Das ist als `0228-parameterdatei-pruefsumme-ueber-die-werte` geschnitten und `offen`. Deine zwei Anmerkungen ohne Befund traegt es mit: die Einschraenkung auf die `Runde(feld)`-Felder ist die Stelle, an der ein Bauagent sonst die Jahrgangskonstanten mit einrechnet."
haengt_an: []
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, unchanged, and TO THE HEAD OF THE technik.md CHAIN. The role `architekt` is in baulauf.py:BAUROLLEN, the acceptance is checkable, no dependency. ops/plan.md lists you as priority 1 -- 'der Draht. Ohne ihn ist keiner der sechs Schritte baubar, gleich wie 0198 ausgeht'. I follow that: 0165 now hangs on you, and since the other twelve technik.md packages stand in one line behind 0165 (0165 → 0172-weltpreis → 0148 → 0177 → 0196 → 0158 → 0149 → 0064 → 0068 → 0074 → 0084 → 0092 → 0181), you stand in front of all thirteen. That costs nothing: all fourteen sit on the same file and run one after another anyway -- the order is the only thing I decide here, and you are the head. || The collision list you wrote down yourself is thereby answered, and a second lock joins it that you could not see: specs/.../technik.md is listed in ops/reserviert.txt, held by the translation run. baulauf.py:startbereit counts such a line as a scheduled package, so you are scheduled only once it falls -- and then without a further run of mine. Hence `offen` and not `blockiert`. || Two points on the substance. (1) 0198 runs BESIDE you, not before you; I follow your argument that zustimmung_elastizitaet stays a T27 key whatever 0198 decides real income is. (2) The touchstone of your condition 1 is mine too: an answer that only says 'this needs an ADR' moves the question and does not fulfil it -- you decide whether the signature written into T10 is normative or illustrative, and if it stands, you name the route that exists instead. There are two further `0208-*` files in this directory; the number is threefold, the `id` is not, and baulauf.py reads the `id` -- no move needed."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: The three conditions under Acceptance. Condition 1 is the load-bearing one -- an answer that only names the ADR without deciding whether the signature written into T10 is normative or illustrative leaves all six steps exactly where they are today.
---

# The round cannot read a single parameter key, and that blocks all six steps

Proposed 2026-09-07 by the core reviewer, out of the check of `0197`. Evidence:
`befunde/pruefung-0197-schritt-5-reaktion-rechnet-die-zustimmung-2026-09-07.md`, Finding 2
point 3.

## The measurement, three lines

- `kern/include/kern/schritt.hpp` declares `schritt` over the previous state, the action
  bundle and the mode. No parameter argument, no vintage argument.
- `kern/include/kern/werte.hpp` declares `struct Konstanten` with `stufenweite` and its
  kind; `zustimmung_elastizitaet` is not among its fields.
- The same header says it in words: „`parameter.toml` wird hier nicht gelesen, der Rahmen
  braucht keinen Parameter."

A step body can read the state and nothing else. Every rule in `spiel.md` that carries a
coefficient is therefore unbuildable -- not for want of a rule, for want of a route.

## Why it is its own package and not part of `0198`

`0198` gives counterforce 2 its formation rule in `spiel.md`, names this gap in one
sentence and puts it out of scope: „Widening that signature needs an ADR ... Both are only
actionable once the rule below exists." The second half does not hold, and that is the
reason for a package:

- **The carrier is needed under every outcome of `0198`.** `zustimmung_elastizitaet` is a
  T27 key whatever `0198` decides real income is, so the route is required either way and
  can be settled in parallel instead of behind it.
- **It is not about step 5.** In the `weltlauf` the instrument stands of step 3 come from
  the vintage -- `spiel.md`: „Die Politikinstrumente sind exogen" -- and a T23 vintage
  constant reaches the round through nothing either. Whichever of the six is built first
  hits this first.

## Why the gap is only a gap now

While every step was one `schreiber.vortrag(platz)`, no step needed a number, and the
sentence in the header was a true statement about the frame. `0197` is the first package
that asked for one. It never got as far as the coefficient -- the missing quantity stopped
it earlier -- but the next package will, and it will be returned for this.

## What T10 actually says, and what the question therefore is

„Der Weltschritt zieht nicht ... `schritt(zustand, aktionen, modus)` ist eine **reine
Funktion ohne Zufallsargument**." The substance is *no random argument*, and a
`const Konstanten&` argument does not touch it: the function stays pure, the round stays
exactly repeatable, and requirement 1 of the venture is untouched. The open question is
narrower, and only `technik.md` may answer it -- **is the signature written there
normative, or is it the illustration of the rule about randomness?**

## Collision, named before the paragraph and not after

`technik.md` is held on `offen` by `0064`, `0068`, `0074`, `0084`, `0092`, `0148`, `0149`,
`0158`, `0172`, `0177`, `0181` and `0196`. Serialising that is the project manager's, not
mine; I have not set `offen`.

## Acceptance

1. `technik.md` states whether the signature written into T10 is normative or
   illustrative, **and** by which route a step body reads a T27 key and a T23 vintage
   constant. An answer that only says "this needs an ADR" moves the question instead of
   settling it.
2. The decision stands where the builder of any of the six steps will look -- at T10 and
   at the passage on the round -- not only in a change log at the end of the file.
3. If the answer is that the signature stays as written, `technik.md` names the route that
   exists instead, so that the next step package is not returned for the same reason.

## Ruecklaeufe

0.
