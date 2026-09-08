---
typ: pruefung
paket: 0197-schritt-5-reaktion-rechnet-die-zustimmung
pruefer: kern-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Conditions 1 and 2 read against the delivered schritt.cpp and schritt_probe.cpp; both unmet, both blockers recomputed from the headers, and the addresses of condition 2 counted by hand.
befunde: 4
---

# 0197 — `zurueck`: conditions 1 and 2 unmet, and condition 2 is the wrong measurement

**Condition 1.** `kern/src/schritt.cpp:529` reads
`void schritt_5_reaktion(Schreiber& schreiber, Index platz) { schreiber.vortrag(platz); }` —
unchanged. The condition demands that the four approval addresses no longer call
`schreiber.vortrag`.

**Condition 2.** `kern/test/schritt_probe.cpp:593` still asserts `geaenderte == 1`, and
:620 still prints `%zu von 310 Groessen geaendert` with that 1. The acceptance line says
in as many words that this does not meet it.

## 1. The coefficient blocker is real — confirmed from three places

* `kern::werte::Konstanten` (`werte.hpp:96`) carries no `zustimmung_elastizitaet`; a grep
  over `werte.hpp` for that key has zero hits.
* `schritt(const Zustand&, const Aktionsbuendel&, Modus)` (`schritt.cpp:599`) takes three
  arguments, not the four of T10b.
* `werte::schaden(const Zustand&, const Schreiber&, const Konstanten&, Gebiet, Instrument)`
  (`werte.hpp:487-490`) needs the carrier, so no term of the right-hand side is callable.

Holds. It touches `schritt.hpp`, `werte.hpp` and the callers — outside `dateien`.

## 2. The ordering blocker is measured correctly but is **not** outside this package

The order is right, recomputed by hand: `LAND_POLITISCH_AB = 21`,
`LAND_INSTRUMENTE_AB = 24` (`zustand.hpp:357-358`), `Zustimmung = 0` (:182),
`Stand = 0`, `INSTRUMENTFELDER = 4` (:195-201). Approval sits at 21, 65, 109, 153; a
land's four instrument stands at base + 24, 28, 32, 36. All 16 pairs, as the probe
asserts. `lies_neu` on an address unwritten this round is a hard error
(`schreiber.hpp:480-482`), and sharper than reported: `werte::schaden` takes the
`Schreiber` itself, because `hub` and `preishub_zoll` need both stands (`werte.hpp:478-483`).

**But the way out lies in the two files of this package.** `schritt()` is in
`kern/src/schritt.cpp`; condition 3 authorises the whole-block variant expressly;
`include/kern/schritt.hpp:22-25` places the retraction "in seiner Probe", i.e. in
`schritt_probe.cpp`; and `kern/src/schreiber.cpp` enforces no write order at all (grep for
`Reihenfolge`: one comment about iteration order, no check). A separate package for the
restructuring would claim `schritt.cpp` and deadlock 0197's own lane.

## 3. Condition 2 is not unreachable — it is satisfiable without the rule

The report calls condition 2 refuted by `spiel.md`, because without an instrument step the
hub is exactly zero (`spiel.md:2382-2386`, correct). But the rule is not `lies_alt + hub`,
it is `min(10.000, max(0, lies_alt(zustimmung) + …))` — a clamp (`spiel.md:2314-2318`).
The probe's start state puts `musterwert(platz)` on all 310 addresses
(`schritt_probe.cpp:388-399`). By hand: `21 % 8 = 5` and `109 % 8 = 5` give `123.456.789`;
`65 % 8 = 1` and `153 % 8 = 1` give `1`. A faithful body clamps US and DE to 10.000 and
leaves CN and BR — **3 von 310 geaendert**, condition 2 green, measuring the clamp instead
of the rule. That is the reason to replace it by the two-state comparison, and it is a
stronger one than "unreachable". The criterion is the project manager's; I do not lower it.

## 4. Condition 4 is unproven

`Glob *0197*` over the venture returns the package and two findings. There is no
`messung-0197*`, while 37 `messung-*/` directories exist. Nothing shows `schritt_probe`
was translated or run with the added function.

## Where I looked and found nothing

* **Determinism:** the added probe brings no floating point (`sperre.hpp`), no scattering
  set, no second random stream, no time or address into the result; it walks two
  written-out arrays in T15 order. Nothing.
* **The added assertion at :898** (`bewegte_instrumente != 0 || bewegte_zustimmungen == 0`)
  cannot fail while step 3 and step 5 both carry forward: both counts are 0. It is a
  forward guard. The content of the run is the second assertion, :922, verified by hand above.
* **Feedback bounds:** no computing body was added, nothing to bound.

No work-package proposal from me: blocker 1 is covered by `0229`, blocker 2 needs none.
