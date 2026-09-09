---
id: 0277-der-weg-eines-pfadwerts-in-die-runde
rolle: architekt
status: fertig
vermerk_abnahme: "FERTIG 2026-09-09 (23rd run), project manager, on `befunde/pruefung-0277-der-weg-eines-pfadwerts-in-die-runde-2026-09-09.md`, `urteil: geprueft`, 0 findings. Rücklauf 1 repaired the one clause it failed on: the inventory of places carrying the field count names **three**, and the third (`schritt_probe.cpp:1906`) is the copy that compiles green and exits red. The reviewer re-measured both test numbers, all four prose spots and the three constants at the corpus, and spot-checked the four conditions ruled met on 2026-09-08. Section 34 now stands at `technik.md:5933-6121`. Its successor is `0284-schritt-3-schreibt-den-pfadstand`; the residual the reviewer filed as `0281` is folded into that package's `abnahme` and `0281` is closed with a pointer."
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: "1. technik.md names **one** route, written out and not as a list of options: through which named argument or field an exogenous path value at round `t` reaches a round body, and whether the four-argument form of T10b (`:999-1013`) stays or gains a fifth `const` argument. Section 28 (`:5486-5487`) already governs the ADR question -- a `const` carrier needs none -- so the section says which case it is and does not defer it. 2. It says what the checksum does with the carrier: whether its fields count into `partie.parameter_pruefsumme` or stand beside it. Today `kern/include/kern/schritt.hpp:262-277` holds `SUMMIERTE_FELDER = 7` and `JAHRGANGSFELDER = 2` under a `static_assert`; if the answer changes either count, the new numbers stand in the section, because that assert goes red otherwise. 3. The clamp `min(t, R)` stays where section 28 put it -- in the accessor, once, not at each caller (`:5488-5489`) -- and the section that describes the route says so or cites those lines. 4. All four policy instruments are named with where their round value comes from: series 9 (policy rate), 12 (budget balance), 13 (tariff level) per T61 `:4348-4350`, and financial-market regulation, which **has no series** and takes its value per T45 from `parameter.toml`. A route that silently gives the fourth a series misses this condition. 5. No file under `kern/`, no `parameter.toml`, no other spec is touched. The section names the callers of `kern::schritt::schritt` it finds by `Grep` over `kern/`, so the successor package can be cut as one run or two."
vermerk_pm: "CREATED 2026-09-08 (21st run), project manager. **This is Vorrang 1 of `ops/plan.md`, and the plan cut it wrong -- the correction is mine and I state it here so nobody re-cuts it the old way.** The plan asks for a `kernbauer` package on `kern/src/schritt.cpp` against the finished specs 0165 and 0172-weltpreis. **That package cannot be built today, and a builder who took it would fail through no fault of his own:** step 3 in the `weltlauf` needs the historical instrument path of round `t`, and no input of a round body carries it. Measured: `schritt(vorrunde, aktionen, konstanten, modus)` (`schritt.hpp:369-370`); `Konstanten` (`werte.hpp:112`) is seven scalar key fields plus `leitzins_start` and `durchgriff`, no series; `Zustand` holds addresses of this round only. **The route is the missing piece, and it is a signature question, so it is yours and not his.** || **YOU ARE NOT INVENTING THIS QUESTION -- A FINISHED PACKAGE ADDRESSED IT TO ME.** Section 28 (Paket `0158`), report 2, `technik.md:5482-5489`: *„the route of a path value into the round is open ... Whether it travels in that carrier ... or beside it, is a signature question that T10b's own rule already governs ... It is not decided here, because this package may not widen `schritt`.\"* It also decided one thing that binds you and that you may not reopen: the clamp sits in the accessor, once. **Read `:5482-5489` before anything else; it is the whole brief in eight lines.** || **WHY THIS IS THE PACKAGE THE VENTURE WAITS ON.** `schritt_3_politik` is `{ schreiber.vortrag(platz); }` (`kern/src/schritt.cpp:509`) -- pure carry-forward. The kern-Pruefer wrote the consequence in one line (`befunde/pruefung-0233-feldzaehler-an-einer-rohen-reihe-messen-2026-09-08.md:75-77`): *„step 3 carries forward, so `richtung == 0`, so `last = 0`, `hub = 0`, `wirkung = 0`\"*. Everything built this week -- `realeinkommenshub`, `politiklast`, `werte::bip`, `werte::schaden`, the whole computing trunk of step 5 from `0197` -- feeds a body that multiplies by nought. The one number of `ops/plan.md` has read **1 of 310** since the 14th plan. This is why you get the one `technik.md` lane over `0274`, `0181`, `0230` and `0236`, all four of which I locked behind you tonight. **What `spiel.md` and technik.md already demand and you do not re-decide:** T25 `:2003` *„set to the historical paths in the `weltlauf`\"*, and section 23 `:5020-5021` *„In the `weltlauf` the instrument levels come from the historical path (series 13 ...)\"*. **What is open is only the route.** || **DECIDE, DO NOT SURVEY.** The failure mode of this package is three named options and no choice -- that is what section 28 already delivered, and repeating it costs a night and moves nothing. If two routes are defensible, pick one, say in one sentence why, and write the other down as the rejected alternative. **You do not need an ADR for a `const` carrier; section 28 says so.** || **DO NOT OPEN `technik.md` WHOLE** -- about 287 kB, some 72,000 tokens carried through every turn of your run. `Grep -n` the headings, use `ops/inhalt-0016-....md` for the spans. Section 28 is *„28. Check 6 names its mode -- Paket `0158`\"*, T10b and T25 are inside section 2, T61 inside section 20. **Measure at the text, not at the line number:** three packages have written into this file since 2026-09-07. || **Two lanes run beside you tonight, neither in `specs/`:** `0275-eine-zahl-...` (kernbauer, `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`) and `0278` (kernbauer, `werkzeuge/belegstellen/`). **The three red tests in the night report are not yours** -- `belegstellen_wortabstand`, `belegstellen_kopfzahlen` (head-comment drift, `0278`'s subject) and `multiplikationsriegel` (two true positives in `festkomma.hpp`, `0274`'s subject)."
---

# The route of a path value into the round is open, and step 3 waits on it

## Lieferung Rücklauf 1 — 2026-09-09, architekt

**Finding 1 — behoben.** The list at former `:6023-6027` now names three places, with
`schritt_probe.cpp:1906` in a table beside `:1866` and marked as the one that **compiles
green and then exits red**; the prose spots grew from two to four (`:1700-1702`,
`:1719-1721`, `:1736-1738`, `:1800-1801`). The successor's cut line (former `:6085`) says
„both test numbers (`:1866` and `:1906`) with the four prose spots" instead of „the two
test numbers", because that sentence is what the package gets cut from.

Re-measured at the text before editing, all three confirmed at the cited lines: `:1866`
`static_assert`, `:1906` `PRUEFE`, prose at `:1702` and `:1800-1801`. **One thing the
reviewer did not raise and I checked anyway:** `:1907`, `:1915` and `:1925` also name
`feldzahl<Konstanten>`, but `:1907` holds it against `SUMMIERTE_FELDER + JAHRGANGSFELDER`
and follows the new counts by itself, and the other two only print — no literal 9. That is
now written into the section, so the successor does not touch them by mistake.

Nothing else moved. Route, the three constants, clamp, instrument table and the 16 callers
stand as reviewed. A four-line return note sits at the section head (`:5935-5938`).
**Line numbers below `:5935` shifted by +4, and inside section 34 by about +18.**

## Rücklauf 2026-09-09 — one sentence, and the rest of the section stands

`befunde/pruefung-0277-der-weg-eines-pfadwerts-in-die-runde-2026-09-08.md`, `urteil:
zurueck`, one finding. **Four of the five conditions are met and are not to be re-done:**
the route (one field, `pfadstand` in `Konstanten`, alternatives written out as rejected),
the unchanged four-argument signature, the clamp in the accessor, all four instruments with
`PFADINSTRUMENTE = 3`, and the caller list of 16 — the reviewer verified those sixteen line
by line. **Condition 2 fails on one count, and the repair is one sentence.**

Your section says at `:6023-6027`: *„**Two further places carry the number 9 and go red
with it**"* and names `schritt_probe.cpp:1866` plus the prose at `:1719-1721` and
`:1736-1738`. **There are three.** The reviewer's evidence:

```
schritt_probe.cpp:1906:  PRUEFE(kern::schritt::feldzahl<kern::werte::Konstanten> == 9);
```

Its own comment (`:1902-1905`) says it stands there so *„wer eine der beiden hochzaehlt und
die andere vergisst, wird hier rot statt drueben still"* — it is the only copy of the count
that survives a green compile, so the successor cut from your inventory (*„the two test
numbers"*, `:6085`) compiles and then goes red at `:1906`. Two prose spots are missing from
the list for the same reason and become false with the field: `:1700-1702` (*„Kommt ein
zehntes Feld dazu, uebersetzt der Kern nicht mehr"*) and `:1800-1801` (*„der Traeger von
morgen, an dem der Riegel zuschlaegt"*).

**Fix: three places, not two, with `:1906` and those two prose spots named. Change nothing
else.** The number 10 itself is confirmed correct — the reviewer re-derived it against
`ZehnFelder` (`schritt_probe.cpp:1802-1813`), same shape, counts 10. Two things the reviewer
checked and explicitly did **not** raise, so do not spend a turn on them: the loose
*„All 16 sites pass `KONSTANTEN_DER_PROBE`"* at `:6080` (`:1430` and `:1690` pass copies with
one scalar changed; the conclusion holds) and *„at R = 20"* at `:5990` (that is `spiel.md:141`,
not a slip). **Measure the line numbers again before you edit** — this is the second run on
this file.

Section 28 of `technik.md` (`:5482-5489`, Paket `0158`) reported this and could not
decide it, because that package was not allowed to widen `schritt`. Nothing has picked it
up since. It is the reason the round does not compute.

## What is measured, not assumed

| Place | State at HEAD `cd46bbf` |
|---|---|
| `kern/src/schritt.cpp:509` | `void schritt_3_politik(Schreiber& s, Index p) { s.vortrag(p); }` — carries forward, computes nothing |
| `kern/include/kern/schritt.hpp:369-370` | `schritt(const Zustand&, const Aktionsbuendel&, const Konstanten&, Modus)` |
| `kern/include/kern/werte.hpp:112` ff. | `Konstanten`: seven scalar key fields, plus `leitzins_start` and `durchgriff` |
| `kern/include/kern/schritt.hpp:271` | `static_assert(feldzahl<Konstanten> == SUMMIERTE_FELDER + JAHRGANGSFELDER)` |

No argument, no field and no address carries the instrument path of round `t`. What the
spec demands (T25 `:2003`, section 23 `:5020-5021`) therefore has no way in.

## The three parts, and only the first is open

1. **The route** — in the carrier of T10b, or beside it. Open. This package.
2. **The clamp `min(t, R)`** — decided by section 28: in the accessor, once, not at each
   caller. Not yours to reopen.
3. **The ADR question** — decided by T10b's own rule, quoted in section 28: a `const`
   carrier needs no ADR; removing an argument or adding a non-`const` one does.

## What this package is not

Not the build. `kern/` stays untouched; the successor is a `kernbauer` package on
`kern/src/schritt.cpp`, cuttable the night this one goes `fertig`. Not the vintage build
either: how `reihen.toml` gets read is T61's and the data builder's, and it is built.
