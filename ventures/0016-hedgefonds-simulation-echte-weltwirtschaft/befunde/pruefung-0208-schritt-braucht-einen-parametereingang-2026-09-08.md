---
typ: pruefung
paket: 0208-schritt-braucht-einen-parametereingang
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: All three acceptance conditions checked by targeted greps and section reads against technik.md, spiel.md, parameter.toml and werte.hpp; every load-bearing claim reproduced.
befunde: 0
---

# Pruefung 0208 — the parameter carrier into the round

Checked the built state of `specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md`
against the three conditions of the package. No condition failed; 0 findings.
Line numbers are as of 2026-09-08 — anchor by T-number, the translator shifts lines.

## Condition 1 — decided, and both routes are named

- Normative vs. illustrative: technik.md:990-997, „What of that sentence is normative —
  decided 2026-09-08, package 0208". Normative is the absence of a randomness argument
  and nothing else about the argument list; touchstone given, ADR boundary drawn
  (removing an argument or adding a non-`const` one needs an ADR; a `const` carrier
  covered by T10b does not). Binding signature stands in T10b.
- Route for a T27 key: T10b (:999-1013) — `schritt(vorrunde, aktionen, konstanten,
  modus)` with `const kern::werte::Konstanten&`; `Runde(feld)` keys are carrier fields,
  and the split table (:1026-1029) names `zustimmung_elastizitaet`, the key the package
  measured.
- Route for a T23 vintage constant: same carrier (:1015-1017 — `leitzins_start`,
  `durchgriff`; :1031-1032 — a carrier field must be one of the two kinds, else the
  vintage build aborts).
- The question is settled in place, not moved: an ADR remains only for changes beyond
  this decision (non-`const` argument, argument removal, 311th address :1070).

## Condition 2 — at every place a step builder reads

The decision stands in the body at four load-bearing sites, not in a change log:
T10/T10b directly under the round-order passage (:980-1076); T38's argument passage —
„a step builder looks here first", pointer to T10b (:1438-1444); T27 — „since 0208 it
is an argument of `schritt` — this is the one route" (:1935-1940); section 8's
name-legitimacy rule — „Two of the four kinds reach a step body only through the
carrier of T10b" (:2295-2297).

## Condition 3 — not applicable

Its antecedent is „if the signature stays as written"; it does not — T10b replaces it.

## What I searched for and did not find

- Stale signatures: `schritt(` appears at exactly two sites in technik.md (:986 quoted
  rule, :1003 binding form). No third.
- A 311th address smuggled in: `lies_alt(partie.parameter_pruefsumme)` reads an address
  that pre-exists as „game: parameter-set checksum" (technik.md:1461, inside the 310
  recount :1464-1465; spiel.md:515 „from parameter.toml, fixed over the game"). „310
  stays 310" (:1072) holds. Note: `partie.` in that spelling appears only in the 0208
  text — the address tables are translated („game:"); that is translation, not absence.
- Numbers: 51 keys is parameter.toml's own count-off (parameter.toml:168 „51
  Schluessel", :184 „47 + 4 = 51"). Six T27 keys in `Konstanten` matches the
  independent pre-0208 statement at spiel.md:3313.
- Quotes: werte.hpp:85 carries „der Ausschnitt daraus, den die Bewertung braucht"
  verbatim, with `leitzins_start` (:134) and `durchgriff` (:153) as fields.
  parameter.toml:297 still computes the checksum „ueber diese Datei" — the conflict
  T10b supersedes is real, and the architect reported it to the PM instead of editing a
  file outside `dateien` (:1059-1060). Correct under the rules.
- T12 (:1109) is the checksum construction T10b references.

## Noted, no findings

1. T27's pointer sentence (:1941-1942) says the checksum is formed „over the values of
   the carrier"; T10b (:1045-1047) restricts it to the `Runde(feld)` fields — vintage
   constants deliberately outside (:1062-1070). The sentence cites T10b for the
   construction, so the binding text is unambiguous. If a builder ever includes vintage
   constants in the parameter checksum, this sentence is where it came from.
2. spiel.md:3313 still carries the pre-0208 gap row („needs an ADR … Package `0208`
   covers it"). Outside this package's `dateien`, and the row names 0208, whose outcome
   now stands at T10/T10b — the pointer resolves. No follow-up package for one
   self-resolving table row.
