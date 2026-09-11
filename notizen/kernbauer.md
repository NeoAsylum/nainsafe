# Logbuch: kernbauer

Rotated by the runner on 2026-09-11 at 13311 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-11-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-11 -- 0300 (the admissible list, and two gaps that are not the same gap)

Three files, all in the package. `kern/include/kern/aktion.hpp`: `zielmenge`,
`ANGEBOTE_HOECHSTENS`, `STUFE_OFFEN`, `Zulaessigkeitsliste`, `zulaessige_aktionen`,
`BUENDEL_AKTIONEN_HOECHSTENS`/`BUENDEL_FASST`, `Buendel`, `ANTEIL_HOECHSTENS`, `Einwand`,
`kassenbedarf`, `buendel_einwand`, `buendel_zulaessig`, `einwand_name`; plus the head
paragraph that used to say the bundle check does not belong here. `kern/src/aktion.cpp`:
`SEKTORLISTE`, `betrag_der_stufe`, `dasselbe_ziel`, `wird_angeboten` in the anonymous
namespace, and the five function bodies. `kern/test/aktion_probe.cpp`: `Rohling`,
`lege_dazu`, `platz_als_ziel`, `wie_oft_angeboten`, `probe_konstanten` and five new
condition functions.

- 2026-09-11, **the lesson of the run** -- **Two missing pieces in one package are not
  interchangeable, and treating them alike costs the cheaper one.** The package names one
  (`stufen_max`) and expects it recorded. The second -- what an action draws from cash --
  I found while building condition 4, and it is *not* the same kind of gap: `stufen_max`
  exists as a parameter key and is only missing its field in `Konstanten`, so someone can
  add it without deciding anything. The cash claim of kinds 1, 2 and 4 exists nowhere and
  cannot be added without deciding whether entering is paid at the pre- or post-shock
  price and whether leverage adds to cash. The first is a build package; the second needs
  a sentence in `spiel.md` or an ADR first. Proposal `0302` says so. Had I lumped them,
  the cheap one would have waited on the expensive one.
- 2026-09-11 -- **The cash condition today covers one kind of five, and that is written in
  three places on purpose.** `kassenbedarf` returns the magnitude of the Stufe for kind 3
  (T50 fixes that transition's input as cents and binds it to action 3) and 0 for the
  rest. The probe case `ohne_anspruch` asserts that a leverage action of `I64_MAX` draws
  nothing -- a case that is *supposed* to turn red the day the claim is built. A sentence
  in a header would not.
- 2026-09-11 -- **`zulaessige_aktionen` reads neither of its two arguments, and I could
  not make it.** T32 fixes the signature; T32b's five target sets depend on `LAENDER`,
  `SEKTOREN`, `INSTRUMENTE` and on T16's one permanently empty slot, and none of those is
  a number in the state. Both parameters carry `[[maybe_unused]]`. Instead of asserting
  that in prose I measured it: a probe case builds the list against two different states
  with two different step widths and demands the same 49 entries. That case turns red the
  day a specification makes the list state-dependent, which is the only honest thing
  available here.
- 2026-09-11 -- **`festkomma::betrag` is not reachable; it lives in `festkomma::intern`.**
  `kern::werte::betrag` is the i64 version and sits in the anonymous namespace of
  `werte.cpp`, outside my files. Instead of a third copy I wrote `betrag_der_stufe` as
  `stufe < 0 ? festkomma::minus(0, stufe) : stufe` -- same abort behaviour at `I64_MIN`,
  no second sign rule, only public festkomma. Worth knowing for the next module that needs
  a magnitude.
- 2026-09-11 -- **Where a line number may stand and where it may not.** No document name
  followed by a *Zeile N* anywhere under `kern/`; that rule I already had. New today: the
  **colon form** is walked past by the Belegstellenriegel -- the head of `zustand.hpp`
  says so explicitly, and `technik.md` itself and `multiplikationsriegel.cpp` both use it.
  So condition 6's "record at which line" went into the work package in colon form and
  into no source file at all.
- 2026-09-11, **what I am unsure about, for the project manager:** four things.
  **(a) I cannot compile.** The riskiest construct is `zielmenge` as a `constexpr`
  function used both in a `static_assert` and as the size of an `std::array` of actions;
  `art_kennung` in the same header already has this shape, but not as an array bound.
  Second-riskiest: `Rohling` in the probe has no user-provided constructor, so I avoided
  `const Rohling` everywhere -- a const default-init would need one.
  **(b) Predicted, so a divergence is visible instead of arguable:** `aktion_probe` green,
  printing `49 Angebote auf 50 Plaetzen`, five lines `Position 20 Plaetze, 19 Angebote`,
  `Beteiligung 12/12`, `Lobbybudget 16/16`, `Hebel 1/1`, `Sichtbarkeit 1/1`, and
  `Steckplatz 12 (Waehrung USA) wird nicht angeboten, die uebrigen 19 je einmal`. The
  `Fondsanteil DE Industrie` line prints `9000`.
  **(c) The Stufe of a list entry is my reading, not a quotation.** T32 does not say what
  Stufe an entry carries; `STUFE_OFFEN` is 0 and an entry is the offer. Condition 3 of the
  package counts offers and therefore assumes the same reading, which is why I took it --
  but a reviewer who reads the list as carrying every admissible Stufe gets a different
  shape entirely, and then the package is unbuildable until `stufen_max` arrives.
  **(d) The order of the five checks decides which reason a two-fault bundle reports.**
  Condition 5's literal case -- three top-ups of one slot -- reports `ZielDoppelt` and not
  the share scale, because the duplicate check runs first. I built the share-scale half of
  that sentence as a separate case, on a kind-1 plus a kind-2 action on the same
  country-and-sector, where no duplicate masks it. If the share reason should win, the
  order is one line.

