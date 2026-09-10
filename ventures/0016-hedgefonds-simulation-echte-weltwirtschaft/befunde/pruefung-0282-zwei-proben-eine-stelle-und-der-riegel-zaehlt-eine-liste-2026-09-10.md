---
typ: pruefung
paket: 0282-zwei-proben-eine-stelle-und-der-riegel-zaehlt-eine-liste
pruefer: kern-pruefer
datum: 2026-09-10
urteil: geprueft
kriterium_geprueft: "Case 29 hand-derived to mask index 47 in both probes and red without the probe term; both key comments recounted; 19/10/29/16 regrepped; kennzeichen_riegel green in uebersetzung-2026-09-10.md."
befunde: 2
---

# 0282: the criterion holds, and the package leaves one sentence false behind it

All line numbers measured at HEAD `f031de4` in `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`.

## Condition 1 — the case, and its red proof recomputed

Case 29 (`:1979-1986`), the last of `TABELLENFAELLE` (`:1678`, now `<Tabellenfall, 29>`).

* **Same offset.** `constexpr std::array<const char*, 2> KZ_HIER = {` puts the brace at
  index 47, counted by hand; `KZ_DORT` has the same seven characters, so `probe_b`'s brace
  is at 47 too. `zerlege` (`:494-538`) copies ordinary characters one for one, and neither
  prefix carries a string, comment or raw string that could shift it. `finde_zuweisungen:660`
  sets `auf` to that brace, `:1255` makes it `stelle`.
* **The short one is second.** The two-round search (`:1194-1211`) misses `KZ_DORT` in
  `probe_a` — the entry is a use, not a `= {` — and resolves it in `probe_b`, so `:1253`
  writes `probe_b.cpp`. `KZ_DORT`: declared 2, 1 mark, 1 element → `hergegeben` 1 < 2, short.
  `KZ_HIER`: 2/2/2, not short. Entry order puts `KZ_HIER` into `listen` first.
* **Red without the term.** Drop `&& listen[l].probe == lz.probe` (`:1278`): `47 == 47` makes
  `schon` true, `KZ_DORT` never reaches `listen`, `knappe_listen` (`:1463`) returns 0, and
  `:2127` compares `listen_knapp.size() != fall.listen_knapp` → case 29 fails. Stated in one
  sentence at `:1976-1978`. Held.

## Conditions 2–4

**2.** Both comments name the probe: `Listenzahl::stelle` at `:988-993` (*„traegt die
Gleichheit **zusammen mit `probe`**, nicht allein"*) and the dedup at `:1265-1275` (*„das
**Paar aus Probe und Stelle auf der Maske**"*). The file head at `:289-298` too. Held.

**3.** Regrepped `(, [0-9]+)+\},$`: 29 entries, 19 with three trailing numbers, 10 with four
(20–29 = 1,0,1,0,1,0,1,0,1,1). `false,`: 3 hits (cases 7, 8, 9). That is exactly the head's
19 / 10 / 29 / six ones (20, 22, 24, 26, 28, 29) / four zeros / 16 reaching the check
(`:1633-1660`). The nine older four-number cases still carry 1,0,1,0,1,0,1,0 — the pattern I
recounted at HEAD on 2026-09-09 for `0279` — so no existing expectation moved. Held.

**4.** `uebersetzung-2026-09-10.md`: the file rebuilt (`:473`), `kennzeichen_riegel` passed
standalone (`:483`) and as test #28 in the aggregate run (`:167`). The four reds are
`belegstellen_wortabstand` (Messstand 0166), `zahlwort_riegel` and `zahlwort_messung`
(`werte.hpp`, `pfadstand`), `multiplikationsriegel` (`festkomma.hpp:99`). None is
attributable to this file. Held.

## Befund 1 — `knappe_listen`'s head now names a case that neither mutation reddens

`:1456-1462`: *„Wer diese Schranke wieder auf `lz.stuecke` allein stellt oder die groessere
der beiden Zahlen nimmt, macht den Fall wieder still; **der letzte Fall der zweiten
Falltabelle** geht dann rot, und das ist seine Aufgabe."*

Since this package the last case of that table is case 29, and it survives both mutations:
`KZ_DORT` is 1 mark, 1 element, 2 declared — `stuecke` alone gives 1 < 2, the maximum gives
1 < 2, the list is reported either way, `listen_knapp` stays 1, the case stays green. The
witnesses are case 28 (3 marks, 2 elements, 3 declared: both mutations find `3 >= 3` and go
silent) and, for the maximum, case 26 (1 mark, 2 elements, 2 declared). The sentence was
true until case 29 was appended, and what it protects is `0279`'s red proof.

**How to reproduce:** read `:1461`, then `:1979-1986`, then apply `hergegeben` (`:1028`) to
`KZ_DORT`'s three numbers. No build needed.

## Befund 2 — the same positional reference, twice more, one of them wrong today

`:1273-1275`, written by this package: *„Der letzte Fall der zweiten Falltabelle haelt das
fest"* — true today, and false the moment a case is appended. `0289` is `offen`, holds the
same file, and its condition 2 appends exactly one case to `TABELLENFAELLE`; it will break
this line the way this package broke `:1461`.

`:297-298` in the file head says *„Der letzte Fall **des Selbsttests**"*. The self-test has
three case tables (`:302`); its last case is the last of `ABGLEICHFAELLE` (`:2201`), not case
29. Wrong table, today.

A case named by its `was` text cannot go stale on an append; a case named by its position
goes stale on every one. Proposal `0293`.

## What I looked for and did not find

Non-determinism: `unordered_`, `std::map`, `std::set`, `rand(`, `time(`, `clock` — 0 hits,
as on `0275` and `0279`; `listen` is a vector and the dedup walks it in order. The `schon`
loop (`:1277`) assigns rather than ors, but exits on the first true, so it is correct.
Stale number words after 28 → 29: `achtundzwanzig`, `siebenundzwanzig`, `dreissig` — 0 hits;
the run summary derives every count from `.size()` (`:2439`, `:2452`). The residual carried
in the acceptance note — *„die geteilte Liste"* without an anchor — is closed: `:1871` now
names `KZ_GETEILT` and says where the phrase comes from.
