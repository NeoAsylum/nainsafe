---
typ: pruefung
paket: 0238-verlaufprobe-startlage-verletzt-die-nennerbedingung
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Condition 1 recomputed by hand from the zustand.hpp address constants; conditions 2-4 read at verlauf_probe.cpp and the runner's green report of 2026-09-08.
befunde: 0
---

# Pruefung 0238 — geprueft, 0 findings

**Condition 1 (bip >= 1 per country), recomputed independently.** Address formula:
`stelle_sektorgroesse = gebiet_basis + 0 + sektor_index*4 + 0` for Wertschoepfung
(zustand.hpp:800; Wertschoepfung=0 :152, SEKTORGROESSEN=4 :158, sektor_index 1..3 -> 0..2
:754-761); `gebiet_basis = nummer*44` (:771-777, LAND_FELDER=44 :346). Twelve addresses:
US 0/4/8, CN 44/48/52, DE 88/92/96, BR 132/136/140 — mod 8 all 0 or 4, pattern values 0
and -10'000 (`musterwert`, verlauf_probe.cpp:212-223). Sums before the lift: -10'000 /
-20'000 / -10'000 / -20'000 — matches the package table and the -10000 the guard quoted
for US. After: `ausgangslage` sets all twelve to `WERTSCHOEPFUNG_DER_PROBE = 10'000`
(:266, :290-296), so bip = 30'000 per country. `werte::bip` (kern/src/werte.cpp:691-700)
reads exactly these twelve via the same `stelle_sektorgroesse(..., Wertschoepfung)` over
the same three sectors — write and read match structurally. The package body names value
(10'000), count (12), and sums (30'000). Met.

**Condition 2 (form and comment).** The lift sits after the pattern loop (:284-286), in
the same block form as the 0229 parameterpruefsumme exception (:288-289). The comment
:249-265 names `kern/src/schritt.cpp` as the guard's location and says „Die Bedingung
steht hier nicht abgeschrieben, sondern nur ihr Ort" — no `> 0` / `>= 1` transcription
anywhere; 10'000 is derived as the positive counterpart of the pattern value, not a
boundary number. Met.

**Condition 3 (every other address keeps its pattern value).** All `zugang.setze` in
`ausgangslage`: pattern loop :285, PLATZ_RUNDE :287 (pre-existing), PLATZ_PARAMETERSUMME
:288 (0229), the twelve :292. 310 - 12 - 2 = 296 as claimed; both PLATZ_ constants lie
outside the sector blocks 0-140, so no double count. The second fixture `partiestart()`
(:635-648) was not lifted — it feeds the local `Schreiber` round builder (:615-632), not
`kern::schritt`, so it never meets the guard. Met.

**Condition 4 (read at the runner's file).** The working tree's
`befunde/uebersetzung-2026-09-08.md` already carries the post-fix run: `ergebnis: ok`
(:7), `verlauf_probe Passed` root :83 and standalone :177, `100% tests passed` for 26
(:121) and 13 (:189), all other suites green. Test counts unchanged against the morning
failure (8/26, 8/13) — no test added, removed, or newly red. The green is probative: the
0237 guard stands in the tree (schritt.cpp:632-633), the same dated report showed the
abort in the morning, and the unlifted fixture cannot pass a tree with that guard —
same-tree green means the lift ran. Met.

**Searched, found nothing:** weakened assertions (failure counter :122-128 and
`return 1` :1101-1103 intact), other fixtures needing the same lift, guard transcription
in comments, test-count drift. Note, not a finding: the printf of the four sums
(:298-303) executes every run but reaches the report only on failure (the runner uses
output-on-failure) — the receipt for a green run remains the Passed entry.
