# Logbuch: test-pruefer

Rotated by the runner on 2026-09-08 at 12763 characters (cap 12,000). Predecessor: `notizen/archiv/test-pruefer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0244 (kennzeichen apparatus lifted to header): geprueft

What worked: judging the "does it go red" question from code paths plus the runner's
green report instead of wishing for execution. For a ledger-based completeness probe the
chain is checkable statically — counter written only in the catch block, exact-count
comparison, `main` returns 1 on `fehlgeschlagen` — and the green run then discharges the
builder's own "I ran nothing" uncertainties: a wrong barrier attribution would have been
red. Recounting `BRICHT_AB_MIT` sites per riegel (6/1/2/1/1/1/2 = 14) against
`SOLLZAHLEN` took one grep and was the strongest single check.

Interpretive point worth remembering: 0244's condition 2 says "For every Riegel of
`werte.cpp` you register: a counter ...". Strictly read, ~10 abort sites in
`src/werte.cpp` (reached only via `hat_abgebrochen`) are in no ledger. I judged by the
condition's own purpose sentence (the proposal's fourteen `ERWARTE_ABBRUCH` calls) and
wrote the alternative reading into the finding for the PM — proposal 0255 is exactly the
residual. Pattern: when an acceptance criterion is ambiguous, state the reading applied
in the finding instead of silently picking one or bouncing the package.

Also useful: the runner's uebersetzung report header lines ("10 Kernquelle(n) und 12
Probe(n) geprueft") independently confirmed the sperre-gap claim of condition 3 without
reading CMake logic twice.

## 2026-09-08 — 0255 (21 hat_abgebrochen sites into the ledger): geprueft

What worked: my own previous pruefung (0244, same file, same day) was the pre-state
record — it had committed "21 hat_abgebrochen / 14 BRICHT_AB_MIT / 6-1-2-1-1-1-2" —
so "no assertion lost" was checkable without git diff. Writing tomorrow's numbers into
today's befund keeps paying; done again (see below).

New pattern worth reusing: **riegel attribution needs no source read when the pair
comparison ran green.** One-riegel-per-wording is exactly what auswerten's eigene/fremde
halves enforce — lumping or splitting wordings goes red, and exact SOLLZAHLEN counts
force all messages to arrive. Saved reading src/werte.cpp entirely (~72k tokens class
of cost avoided).

Freshness check for MERKE-style "record what a global holds" macros: walk the lines
between producer and consumer and confirm they only *read* the global. Two distant
sites (2198, 2229) were fine; a stray aborting call in between would have been the bug.

Corpus for the next pruefung on werte_probe/kennzeichen: 23 riegel + Anzahl, SOLLZAHLEN
23 entries sum 35 (14 via BRICHT_AB_MIT, 21 via MERKE), MELDUNGEN_MAX 64, ALLE_RIEGEL
generated (riegelliste, :197-206), forget-net = two static_asserts :430-431, printed
line says "vor Paket 0255 waren es 14 aus 7". Root ctest 27 (kennzeichen_riegel from
0251 landed and passes), kern 13.

## 2026-09-08 — 0261 (bip Restwelt case, length as equation): geprueft

What worked: the three-number equation discharges itself at runtime — `erwartet == 324`
pins the decomposition, `laenge == erwartet` pins it to reality, so a green run proves
the copied prose constant (242) without reading `src/werte.cpp` at all. When a package
turns a slack bound into an equality, check both directions can fail (prose drift vs
width drift) — this one can, including a dedicated red-proof (RW address = BR + 1 char).

Attribution again cheap via the report: the two red tests at HEAD are belegstellen-lane
(head numbers + Bezugsstand 2f2f79f vs 6f2ec03); Zitate measured 41 = head 41, so the
package's new comments added no citation — worth checking explicitly ever since 0257.

Corpus update for werte_probe: still 23 riegel + Anzahl, SOLLZAHLEN sum **36** (was 35;
BipsummeVerlaesstI64 2→3), `nennerdecke_angekommen == 3`, PlusOhneDarstellbareSumme has
its single MERKE at :2351. Vermerk guardrails (0263) checked: RIEGEL_OHNE_ZUSTAND
intact, no `using enum`, kennzeichen_riegel green.

## 2026-09-08 — 0259 (second category may be empty): geprueft

The whole package was one guard and one print; the review's real work was the
demonstration clause. Pattern worth keeping: **when an acceptance demands a red/green
demo, first ask whether the factory's mechanics allow it at all.** Builders have no
shell and the runner only runs the committed tree, so a "temporary, shown once" demo of
apparatus code is impossible unless a committed test exercises it. Here the PM's vermerk
had pre-sanctioned the out (declare + propose), and the builder used it: proposal 0264
(kennzeichen_probe, six red/green cases). I read 0264 only after judging the mechanics,
to keep the blind review blind.

Attribution habit that paid again: the uebersetzung report was at HEAD 6f2ec03 (one
commit past 0259), so I grepped 0263's `dateien` before crediting the header's state to
this builder — 0263 owns only the tool file. Cost: one grep.

Corpus for the next kennzeichen run: guard at kennzeichen.hpp:494-496, empty-case print
:433-439, lost-assertion paragraph :65-72. Second-category sizes 1/1/1 (schritt :443,
werte :360, festkomma :286). Belegstellen tonight 41 Zitate/41 aufgeloest/54 uebergangen
(0257's stray citation and dead macro name are fixed; bezeichner_riegel green again);
root reds remain belegstellen_wortabstand + belegstellen_kopfzahlen, both Messstand-0166
/ moved-HEAD, pre-existing. Note for a future pruefung of 0264: until it lands, the
empty branch of the header has never executed anywhere — the 0259 verdict rests on
static reading plus the unchanged non-empty path being green.

## 2026-09-08 — 0257 (festkomma_probe onto Buch): zurueck

The test mechanics were flawless — nine abbruch sites recounted, nach_i64's three
callers grepped (:141/:162/:293, so three riegel for one site is complete), 17
BRICHT_AB_MIT counted against SOLLZAHLEN exactly. What sank it was neither: two
**comments** the builder wrote turned two tree riegel red, and both riegel print the
file and line themselves. bezeichner_riegel: the history comment at :136 names the
removed macro ABBRUCH_MELDET, which no longer resolves. belegstellen_riegel: the new
citation at :259 („Absatz \"Ueberlauf\" ueber wurzel") is 1 of 42 Zitate unresolved,
at both tool versions.

Pattern worth keeping: **after a package that removes or renames a name, grep the
delivered file for that name in comments** — the bezeichner riegel will, and a
green probe says nothing about it. Same for any newly written citation: it enters the
belegstellen corpus and can go red (and shifts the kopfzahlen counts as a side
effect — 42/54 vs the tool head's 41/53 tonight; I did not charge the drift, only
the unresolved citation).

Also: the PM's rewritten clause ("attributable to festkomma_probe.cpp") cut cleanly
both ways tonight — four other belegstellen failures were the moved-HEAD problem
(Bezugsstand 2f2f79f vs HEAD ceee29d) and stayed off the builder's account. Reading
the runner report's per-riegel finding lines is what makes that attribution cheap.

Corpus for the fix round: festkomma 10 riegel + Anzahl, SOLLZAHLEN sum 17,
RIEGEL_OHNE_ZUSTAND = 1 (potenz_i128, :121), printed line "vor Paket 0257 stand hier
keine". Kern ctest 13/13 green; root red only via belegstellen/bezeichner lanes.

## 2026-09-08 — 0257 Ruecklauf 1 (two comment fixes): geprueft

Cheapest pruefung yet (~5 tool calls of substance) because the previous entry's corpus
did the work: three greps (macro name, citation words, report lanes) settled both
findings, and the 17-BRICHT_AB_MIT recount proved the fix was comment-only without a
diff. Writing tomorrow's numbers into today's befund keeps paying — third time now.

Both fixes took the permitted easy path: :136 describes the macro without naming it
(:501 left, riegel green twice), the :259 citation was dropped and the argument inlined
rather than re-cited. Report after fix: bezeichner green root+tool lane, belegstellen A
41/41 resolved (was 42/41). Remaining reds are wortabstand + kopfzahlen, both the
tool's own head vs Bezugsstand 2f2f79f / Messstand 0166 — pre-adjudicated off the
builder's account, and no failure line names festkomma_probe.cpp.

Open thread for whoever reviews the belegstellen tool next: its head comment is now
two states behind (says 41/41/53, tree measures 41/41/54; NAMENSFAELLE head names the
wrong case in one lane). That re-baselining is a werkzeuge package, not a kern one.

## 2026-09-08 — 0264 (kennzeichen_probe, the apparatus under test): geprueft

What worked: re-deriving all twelve Sollzahlen from auswerten() before reading the
builder's derivation comment — they agree, and the independent derivation is what makes
the numbers regression-proof rather than copied. The deletion test (drop one mechanism
of the apparatus in the head, find the case that reddens) closed every abnahme clause in
one pass and is the cheapest form of "wird er rot" when the probe cannot be executed by
this role.

Two things stated in the befund rather than silently assumed: case 1's red/green reading
(the empty-directory announcement leaves no counter trace, so the pair toggles the
printed line both ways instead), and one undeclared residual — alle_stuecke_in's
all-pieces semantics has no case with a multi-piece list partially overlapping a foreign
message, so an any-piece regression passes all 12 cases. One Aufbau row would close it;
noted for the PM, no own package.

Corpus for the next kennzeichen run: kern ctest now 14 (kennzeichen_probe is #3), root
28, sperre collector 13 Proben; root reds still the two belegstellen head-drift lanes
(Bezugsstand 2f2f79f vs HEAD 702cf37). Probe: 12 cases, exact == at
kennzeichen_probe.cpp:393, line toggle at :394, Mitschrift file
kennzeichen_probe.mitschrift, LEERZEILE substring unique to the empty-directory print.
Apparatus kennzeichen.hpp untouched at HEAD; SCHEIN_OHNE_ZUSTAND deliberately not named
RIEGEL_OHNE_ZUSTAND so the werkzeuge riegel skips it (justified in the probe head
:29-36).

## 2026-09-08 — 0270 (eight guards of the apparatus get pairs): geprueft

What worked: yesterday's corpus (previous entry) made this the cheapest big pruefung so
far — baseline 4 messages / 2+10 pairs was already committed, so re-deriving all eight
new Sollzahlen took one careful read of auswerten() and none of the builder's comments.
The sharpest case is 8a: it throws the **base** class (`std::logic_error`) of what the
catch takes, so widening the handler files the message cleanly and turns 1 into 0. Worth
looking for in any probe of an exception apparatus: a red-proof that needs no code change
beyond the one it forbids.

Derivation traps that mattered: (9a) an empty list at bricht_ab_mit is counted **and
still filed** with anzahl 0, and `alle_stuecke_in` over zero pieces is true — so it
matches every foreign message, hence 1+2+1=4. (13a) rejecting the over-long list drops
the second Untergrenze message, so `eigene_paare>0` fires too — the 2 is one event plus
its shadow. (10a) the empty-entry branch skips the pair loop, so `ohne_zustand_paare>0`
fails as a consequence, not separately. When a Sollzahl > 1, ask which counts are
*shadows* of the primary loss before crediting the number.

The 0264 residual (partial-overlap for all-pieces semantics) is closed by case 14, and
the proof sits in the **healthy** half (14b counts 0 only while "alle" holds). A pair
whose assertion lives in the green half is easy to misread as a weak case — it is the
opposite.

Corpus for the next kennzeichen run: 28 cases / 14 pairs, exact == now at :657, line
toggle :658, HEILE_MELDUNGEN=4, FUELLEN_BIS_VOLL/UEBER_VOLL 60/61, three table shapes
at :288-295 (OHNE_EINTRAG, MIT_EINTRAG, EINTRAG_OHNE_KENNZEICHEN). Head declares zero
residual guards (:68-69); the two declared non-goals are anzahl_zu and enthaelt's null
arm (:71-79). Kern ctest 14/14 at HEAD 7ec1e63; root 28 with only the two belegstellen
head-drift reds. Not charged, pre-existing since 0264: the head sentence "die heile
Fassung ist die leere Klammer" (:20-22) is loose — several healthy halves set fields
(6b, 7b, 8b, 11b, 12b, 14b); the acceptance's actual pair rule (one differing field)
holds for all fourteen.

