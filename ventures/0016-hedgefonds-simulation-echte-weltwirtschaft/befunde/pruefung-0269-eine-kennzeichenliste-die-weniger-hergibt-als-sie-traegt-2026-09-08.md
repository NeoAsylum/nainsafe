---
typ: pruefung
paket: 0269-eine-kennzeichenliste-die-weniger-hergibt-als-sie-traegt
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all six conditions read off the source, the mark count hand-traced on the case that separates the two readings, and condition 6 off uebersetzung-2026-09-08.md
befunde: 2
---

# 0269 -- checked

## How each condition was checked

**1 (non-zero exit, message names probe/line/declared/read).** `knappe_listen`
(`kennzeichen_riegel.cpp:1324-1335`) selects `lz.stuecke < lz.deklariert`; `main:2314-2339`
prints `lz.probe`, `lz.zeile`, `lz.name`, `lz.deklariert`, `lz.stuecke` and returns 2. It sits
behind the three older bars and in front of the null checks.

**2 (unreadable size falls back).** `knappe_listen:1329` skips `deklariert == NICHTS`. Case 25
of `TABELLENFAELLE` puts a 3 behind a `using` and expects `listen_knapp = 0`.

**3 (reading stated at the point of the count).** `lies_verzeichnisse:1121-1132`, immediately
above `lz.stuecke = e.kennzeichen.size() - vorher`. Hand-traced case 22
(`{"alpha" "beta", "gamma"}`, declared 3): `zerlege` takes the `"` branch, `hinter_fuellsel`
finds the next `"`, both parts land in one `MARKE` -- 2 marks, reported. Case 23 is the same
text declared 2 and stays silent. That pair is the only one that separates mark-counting from
part-counting; part-counting would find `3 >= 3` and pass the short list.

**4 (bait and twin).** Case 20 declares 3, yields 2, expects 1; case 21 is the same list with
the third piece and expects 0. Checked at `selbsttest_verzeichnis:1868-1876`; a bar that never
fires fails cases 20, 22 and 24.

**5 (no hard-coded count, no probe file name).** `Grep` for `schritt_probe|kennzeichen_probe|
probe_a|probe_b` in the file: only `probe_a.cpp`/`probe_b.cpp` in `als_proben:1754`, synthetic
self-test names from 0251. The expected number comes from `deklarierte_groesse` alone.

**6 (tree green at HEAD).** `befunde/uebersetzung-2026-09-08.md`: the build recompiled exactly
the night's three changed sources (`kennzeichen_riegel.cpp:37`, `belegstellen_riegel.cpp:40`,
`kennzeichen_probe.cpp:44`), so the report is post-0269 and post-0270. Test 28
`kennzeichen_riegel` Passed (`:155`), standalone Passed (`:442`). The two red tests are
`belegstellen_wortabstand` and `belegstellen_kopfzahlen` (`:162-163`) -- neither touches this
file.

**Not vacuous.** The three resolved lists at HEAD are `KENNZEICHEN_SUMME_DER_REGEL`
(`schritt_probe.cpp:440`, declares 3, 3 marks), `KZ_POTENZ_I128` (`festkomma_probe.cpp:282`,
2/2) and `KZ_STECKPLATZART` (`werte_probe.cpp:357`, 2/2). Dropping one piece from any of them
is legal C++ -- the remaining element is value-initialized -- so the bar can fire today.
Unlike `knappe_tabellen`, it is not asleep.

**Determinism.** No floating point, no time, no address. `sammle_quellen:2059` sorts the paths;
`listen` is filled in probe order; `NICHTS` is guarded before the multiply in
`deklarierte_groesse:692`. `lz.stuecke` is an unsigned difference of a size that only grows.

## Finding 1 -- a count in a comment that is off by one

`kennzeichen_riegel.cpp:1494`: "auch in den achtzehn, die es nicht angehen". 19 of the 25 cases
leave `listen_knapp` at its default, and only 16 of those reach the check at all -- cases 7, 8
and 9 have `lesbar: false` and `continue` at `:1786` before it. Neither 19 nor 16 is 18. No
condition is violated; it is a wrong number in a file whose own rule is to say the number. Not
worth a package -- it belongs to whoever next edits the file.

## Finding 2 -- the message names one cause where there are two

A list element that is not a string literal yields no mark. `constexpr std::array<const char*,
2> KZ = {TEXT_A, "b"}` gives `stuecke = 1`, `deklariert = 2`, and the report reads "2
deklariert, 1 gelesen" -- although the list is complete. The **verdict** is right: `gleiche_ab`
never checks `TEXT_A` either, so that Kennzeichen is unbound, which is the gap this package
closes. Only the reason is imprecise, and the head comment writes out its other blind spots
(raw strings `:81-84`, messages grown from several calls `:73-79`) but not this one. No such
list exists in `kern/test` today.

## Where I looked and found nothing

Duplicate reporting of one list named by two entries (case 24; dedup on `(probe, stelle)` at
`:1145-1151`); the same list name in two probes (`:1091-1108`, own probe first); `lz.zeile`
zero (`zerlege` starts lines at 1); `listen_zu == NICHTS` reaching `stuecke_aus` (candidates
without a balanced brace are skipped at `:1100`); all three call sites of the changed
`lies_verzeichnisse` signature (`:1776`, `:1979`, `:2196`).
