---
typ: pruefung
paket: 0074-massnahme-43-mechanisch-erzwingen
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all three Abnahme conditions (condition 3 in the 2026-09-08 corrected form), each reproduced against source and a repeat of the mapping at today's HEAD
befunde: 0
---

# Pruefung 0074 — geprueft, 0 findings

## Condition 1 — enforcement path named: met

T7 `:812-831` names `werkzeuge/multiplikation/multiplikationsriegel.cpp`: what it reads,
four named rules (deny by default, first match wins), and the build/test registration.
Every claim a builder would copy checks out: `PROJECT_IS_TOP_LEVEL` block exists in the
sibling latch (`werkzeuge/bezeichner/CMakeLists.txt:20`, `add_test` `:45`);
`FABRIK_MITGLIEDER` is in the venture `CMakeLists.txt:70` (with graceful skip `:86-89`);
four `*_riegel.cpp` exist beside it (belegstellen, bezeichner, zahlwort, kennzeichen).
Rule-backing declarations verified: `SPLITMIX_FAKTOR_1` is `u64` (`zufall.hpp:140`),
`BYTES_JE_I64` is `std::size_t` (`pruefsumme.hpp:110`), `Index = std::size_t`
(`zustand.hpp:85`), `LAND_FELDER` is `Index` (`:346`). That it does not yet run is
disclosed (§31 report 1) and routed to the PM.

## Condition 2 — text latch expressly treated: met

Three alternatives, each with reason: compiler lock unavailable (`#pragma GCC poison`
takes identifiers — `sperre.hpp:58-63` confirms verbatim it leaves this to 0074); type
route expired (`kern::werte` built on `i64` signatures — `werte.cpp:131` confirmed);
plain text latch rejected on the three-line table, all three verified in source at their
stated lines: `zufall.hpp:166`, `zustand.cpp:840`, `zustand.hpp:777` (move from `:753`
disclosed, §31 report 4).

## Condition 3 — mapping re-executed with reference state: met

Repeated `Grep`, pattern ` \* `, over `kern/src` and `kern/include` at today's HEAD:
**92 lines in 14 files, every per-file count identical** to T7's table (`:856-864`).
By-kind decomposition independently recounted: 56 comment + 28 address/dimension +
4 unsigned (`zufall.hpp:166,167,277`, `pruefsumme.hpp:138`) + 4 `i128`
(`festkomma.hpp:99,161,292,356`) = 92; none is a bare magnitude multiplication.
Fifth-kind sentence present with the "where": seven places, all through `mal` —
reproduced exactly (`werte.cpp:131,151,550,684,856,1065`, `schritt.cpp:596`; no `mal(`
callers in headers, only the definition `festkomma.hpp:290`). Blind spot reproduced:
identifier`*`identifier gives exactly 2 hits, both non-multiplications
(`festkomma.cpp:91` string, `meldung.hpp:54` comment). 92 vs the package's 52/54 shows a
real re-measurement, not a copied number.

## Scope — nothing else moved

Old mapping text gone (0 hits for `52 Zeilen` / `genau dort entsteht sie`);
`multiplikationsriegel` hits only in T7 and §31, as §31's self-check claims; shift below
T7 uniform +66 (§29 first clause `:5395`→`:5461`, §29 span 91 lines unchanged, §30 +1 =
the blank line before the new §31 heading — same precedent as §29/§30 last round).
Sampling limit: no anchor of mine sits between `:912` and `:2877`.

## Remarks, no Befund (for the latch-builder package, PM already owns it via §31 report 1)

1. Today's corpus already holds two day-one false positives for the rules as written:
   `schritt.cpp:405` (`4 * (12 + 9 + 1)` — literal-only `static_assert` recount, no rule
   matches) and `festkomma.cpp:91` (`a*b` inside an assertion string; the spec drops
   comments but not string literals). Deny-by-default makes both loud, not silent —
   consistent with the design; the builder should plan string-dropping and a rule for
   literal-only compile-time recounts.
2. §31 report 3's hit enumeration is accurate only across **both** number formats
   (`1.464` dots, `1,464`/`9,024` commas — T40 `:965-966`, section 10 `:3075-3078`); and
   its own line `:5572` now joins the hit set, so the rejected phrase-heal would leave
   two false lines, not one. Strengthens, not weakens, its conclusion.
