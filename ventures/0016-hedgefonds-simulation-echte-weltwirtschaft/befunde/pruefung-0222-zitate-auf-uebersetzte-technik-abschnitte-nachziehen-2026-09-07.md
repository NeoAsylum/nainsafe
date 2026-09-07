---
typ: pruefung
paket: 0222-zitate-auf-uebersetzte-technik-abschnitte-nachziehen
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: "Riegel green in the post-build report with Zitate == aufgeloest proven via the exit-code ladder; all five repaired sites re-resolved by hand against today's headings"
befunde: 0
---

# Pruefung 0222 — geprueft, 0 findings

## The green proof, quoted on sight (the report file mutates daily)

`befunde/uebersetzung-2026-09-07.md`, current state, `ergebnis: ok`, root build:

```
17/24 Test #17: belegstellen_riegel ..............   Passed    1.02 sec
18/24 Test #18: belegstellen_messung .............   Passed   30.66 sec
19/24 Test #19: belegstellen_wortabstand .........   Passed   17.22 sec
```

and in the same report the subtree build: `belegstellen_riegel Passed 1.04`,
with `Building CXX object ... belegstellen_riegel.cpp.o` — the delivered source
compiled and ran in this very report. Dating: the red proof at Arbeitsbaum
82fa870 (test 17 **Failed**, 40 Zitate / 36 aufgeloest / 53 uebergangen, quoted
in `befunde/pruefung-0166-...-2026-09-07.md`) is earlier the same day; a green
riegel requires the four repairs, which only 0222 made — so this report
postdates the build. Test count 24 continues today's 19→21→23 sequence.

## Passed really means Zitate == aufgeloest

The green report prints no Zahlenzeile, so I proved the equality in the source:
`CMakeLists.txt` has no `PASS_REGULAR_EXPRESSION|SKIP_RETURN_CODE|WILL_FAIL`
(Passed ⇔ exit 0). `belegstellen_riegel.cpp:4213-4219` returns 0 only when
`befunde`, `zitatbefunde` and `tote_ziele` are all empty; a counted Zitat that
does not resolve lands in `zitatbefunde` (exit 1) or, as TotesZiel, counts as
Zitat-not-aufgeloest and exits 1 (`zaehlt_als_zitat`, :2349). The
aufgeloest/Befund/uebergangen trichotomy is pinned by 73 self-test cases in
nine tables run on every invocation before the scan; any ripped case →
exit 2 (:4006-4017). `AUFGELOEST_MINDESTENS` stands unweakened at 16
(:2503, = 2+2+1+2+5+4 per its own derivation). No loosening found.

## The five sites, each re-resolved against today's tree

1. `belegstellen_riegel.cpp:39` (named in advance) — "Two address pairs carry
   the same value, and that needs a rule instead of a coincidence" =
   `technik.md:409` verbatim. Repaired, and the head comment says so honestly.
2. `daten/adressen.md:29` — same Absatz + "are the same quantity" =
   `technik.md:410`.
3. `daten/adressen.md:540-544` — "T46 — The eleven addresses whose provenance
   is this document, exhaustively" = `technik.md:1651`; "Series 10 carries
   three countries, the USA by definition not" = `technik.md:1661`;
   `technik.md` and "Zeile 1219" stand on one line (:542) as the Meldung
   promised for NAMENSFAELLE Fall 1.
4. `daten/adressen.md:554-559` — same Absatz, both pairs verbatim =
   `technik.md:409-411`.
5. `daten/reihen.toml:1870` (named in advance) — repaired, not declined:
   "'And the limit of the oracle, explicitly'" = `spiel.md:2835`; kept
   Schluesselwort-free, so the base count the 0166 Messstand prints does not
   move — a legitimate reason, not a lowered criterion.

Sites 1-4 are exactly the four unresolved of the 40/36 red state; none was
deleted — all five still cite today. The Meldung carries file, line, old and
new wording for every site, as the corrected acceptance demands.

## Also checked

- Reported-not-fixed sites confirmed verbatim: `technik.md:1802` and
  `spiel.md:1606` still carry „Die Grenze des Orakels"; both sit in specs,
  outside the builder's `dateien`. Neither is of the counted form (riegel is
  green). PM already tracks the technik.md one; spiel.md:1606 is new.
- The five unneeded `dateien` (parameter.toml, three kern headers,
  schritt.cpp) are covered by the same green run — any dead citation there
  would have been red.
- Looked for and did not find: a lowered threshold, a removed assertion, a
  citation deleted to reach green, a heading moved back toward German.

Consequence for the queue: wortabstand and messung are green as delivered —
0166's redo likely needs zero edits, as its pruefung predicted.
