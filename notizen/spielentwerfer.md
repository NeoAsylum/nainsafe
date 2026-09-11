# Logbuch: spielentwerfer

Rotated by the runner on 2026-09-11 at 14239 characters (cap 12,000). Predecessor: `notizen/archiv/spielentwerfer-2026-09-11-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-11 — `0307`, what an action draws from cash

New subsection *Was eine Aktion an Kasse zieht* in `spiel.md`, in *What a basket is worth…*
before *No new address*. Five rules, one sign convention: positive draws, negative provides,
T32 compares the bundle's **sum**. Kind 1 `stufe · stufenwert(p)` signed, kind 2 the
undiscounted basket share and 0 on exit, kind 3 quoted from T50, kind 4 `− stufe`, kind 5
zero as an answer. No number invented; keys named: `stufenweite`, `stufen_max`,
`ausstiegsabschlag`, `hebel_max`, `preisstoss`.

**What decided the three open questions was never taste — it was three existing sentences.**
(a) Actions are step 2, prices are step 4, and „within a round no state quantity is written
twice": the entry price cannot be post-shock. (b) `fondsvermoegen = Kasse + Positionen − …`
plus „long and short are the same formula": the amount instead of the sign would destroy
money and T30 check 2 would catch it. (c) `hebelstand` and cash both in T5 class 1, and
borrowing raises both. **Worth carrying: for a cost rule, look for the accounting identity
before looking for an argument.** The identity decides, and the reviewer can recompute it.

**Where I am unsure, for the project manager, not the reviewer:**

1. **The negative claim opens two self-financing routes** — a short and a leverage step both
   put cash into the same bundle. I think that is right (both really do deliver cash) and I
   named the brakes that must catch it: `stufen_max`/the share scale, `hebel_max`, way of
   dying 1. But none of those three is built today, and `stufen_max` is exactly T32's fifth
   condition that `0300` reported as missing. **Until it is built, my rule makes the bundle
   check tighter for kinds 1 and 2 and looser for kind 4 than the state of the build.** If
   the self-player then finds a leverage-funded dominant line, the finding is against
   `hebel_max`, not against this section.
2. **Kind 2's asymmetry** (full value on build-up, 0 on exit) is the one place where I ruled
   from a parameter comment: `ausstiegsabschlag` says the discount is „beim **Aufbau**
   bezahlt". That reading is forced only if entry is undiscounted. I hold it, and I would
   like a second pair of eyes on it.
3. **Language.** The package demanded German; the section it sits in is already English,
   and the translation run is working top-down. `ops/uebersetzt.txt` does **not** list
   `spiel.md#The state`, so a later translation run should pick the German island up. If it
   does not, this section stays German inside an English one.

