---
typ: pruefung
paket: 0277-der-weg-eines-pfadwerts-in-die-runde
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: All five conditions measured one by one against section 34 (`technik.md:5933-6098`) and against every place it cites in `kern/`, `parameter.toml` and `technik.md`; condition 2 fails at a third copy of the field count that the section does not name.
befunde: 1
---

# The route is decided and holds; the list of places that go red is short by one

## What I measured, condition by condition

| # | Measured at | Result |
|---|---|---|
| 1 | `:5936-5938` names one field, `pfadstand` in `Konstanten`, not a set of options; the two alternatives stand under *Why this route and not the other two* as rejected. Signature `schritt.hpp:369-370` stays four `const` arguments, „unchanged to the character". T10b's quoted sentence stands verbatim at `technik.md:1138-1139` (English at HEAD), the ADR sentence at §28 `:5486-5487`. Nothing deferred | met |
| 2 | Answer given: beside the sum. `schritt.hpp:133` says „Sie laeuft nur ueber die sieben Schluesselfelder" — the section keeps that. New numbers stand: `SUMMIERTE_FELDER` 7, `JAHRGANGSFELDER` 2 → 3, `feldzahl<Konstanten>` 9 → 10. **10 is right**: `ZehnFelder` (`schritt_probe.cpp:1802-1813`) has the same shape — eight scalars, one `std::array`, one nested one — and counts 10 | **fails, finding 1** |
| 3 | `:6031` cites §28 `:5488-5489` word for word and does not reopen it; the `daten` accessor named at §9 `:2667` carries `min(t, R)` as that table says | met |
| 4 | Table `:6041-6046`. T61 `:4348-4350` reads „series 9 (policy rate), series 12 (budget balance) and series 13 (tariff level); the fourth instrument … has no series, its value comes per T45 from `parameter.toml`" — the table maps exactly that. Enum order `zustand.hpp:141-146` is `Leitzins 0, Zoll 1, Haushalt 2, Regulierung 3`, so the index claim holds and `PFADINSTRUMENTE = 3` leaves out `Regulierung`. Address `land.<L>.instrument.regulierung.stand` exists (`parameter.toml:217`, `daten/adressen.md:79` Nr. 37, 81, 125, 169, source `Parameter(regulierung_start*)`) | met |
| 5 | `grep 'pfadstand'` over the repo: two files, `technik.md` and the architect's logbook — no `kern/`, no `parameter.toml`. Sections 1-33 sit at their old spans. `grep 'schritt::schritt('` over `kern/` gives **16 hits at exactly the 16 lines named**, 15 in `schritt_probe.cpp` and `verlauf_probe.cpp:330`, none in `kern/src` but the definition (`schritt.cpp:849`). `werte.cpp:187-196` is positional and ends at `leitzins_start` as claimed | met |

## Finding 1 — a third place carries the 9, and it is an executable assertion

`:6023-6027` says: **„Two further places carry the number 9 and go red with it"** and names
`schritt_probe.cpp:1866` and the prose at `:1719-1721` and `:1736-1738`. There are three.

**How to produce the failure.** Cut the successor from that list, add `pfadstand`, change
`JAHRGANGSFELDER` to 3, fix `:1866` and the two prose spots. The core compiles, `:1866`
passes — and then:

```
schritt_probe.cpp:1906:  PRUEFE(kern::schritt::feldzahl<kern::werte::Konstanten> == 9);
```

`feldzahl<Konstanten>` is now 10, `pruefe` (`:314`) increments `fehlgeschlagen`, the probe
exits red. The line is not an accident: its own comment `:1902-1905` says it stands there
so „wer eine der beiden hochzaehlt und die andere vergisst, wird hier rot statt drueben
still". It is the only copy of the count that survives a green compile, and the section's
inventory — „the two test numbers" (`:6085`) — is the sentence the successor is cut from.

Same repair, prose: `:1700-1702` („Kommt ein zehntes Feld dazu, uebersetzt der Kern nicht
mehr") and `:1800-1801` („der Traeger von morgen, an dem der Riegel zuschlaegt") become
false with the field, and are not in the list either.

**The repair is one sentence:** three places, not two, with `:1906` and the two further
prose spots. Nothing else in the section moves with it.

## What I found clean and what the ruecklauf need not re-check

The route, the rejected alternatives, the no-ADR case, the checksum answer and the three
constants, the clamp, all four instruments, and the caller list of 16 (verified line by
line). Two things I checked and did **not** raise: „All 16 sites pass `KONSTANTEN_DER_PROBE`"
(`:6080`) is loose — `:1430` passes `grosser_koeffizient` and `:1690` `fremder` — but both
are copies of it with one scalar changed (`:1411`, `:1683`), so the conclusion (compiles,
zero) holds; and „at R = 20" (`:5990`) is the decided game length (`spiel.md:141`), not a
slip for the older `R = 24` examples.
