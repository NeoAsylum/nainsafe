---
typ: pruefung
paket: 0165-schaden-zwei-zustandseingaenge-zusammenbinden
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all three Abnahme conditions reproduced by grep/read against technik.md, spiel.md, werte.hpp/.cpp, schreiber.hpp and both test files
befunde: 1
---

# Pruefung 0165 — geprueft, 1 accuracy note

**Condition 1 — met.** T48 no. 22 itself carries the decision (technik.md:2286–2310):
"Number 22 takes exactly one state input, and it is the `Schreiber`"; numbers 9–11 read
"the state emerging in this round", and the route is named — a second read form per
quantity taking `const schreiber::Schreiber&`, every address through `lies_neu`, no
second `Zustand` argument. Both questions of the condition are answered at the required
place.

**Condition 2 — met.** The choice is answer 1 in the shape "forms on the writer"; the
public-read-access variant is rejected with the box quote from `schreiber.hpp`, verified
verbatim at schreiber.hpp:445–447. Signatures named:
`schaden(rundenschreiber, konstanten, l, i)` (technik.md:2302, 4298), three second forms
with same name/arity/class, `Zustand` forms unchanged. The reader table
(technik.md:4266–4271) reproduces exactly and completely: werte.cpp:628 (`waehrungswert`
→ `handelsvolumen(z, l)`), werte.cpp:581 (`anleihewert_zwei` → `schuld(mengen, l)`),
zustandsausgabe.cpp:169 (`bip(z, gebiet)`); a grep for `\b(bip|schuld|handelsvolumen)\(`
over `kern/src` and `kern/test` yields no reader outside the table — remaining hits are
the definitions and `schaden` itself (werte.cpp:940–990).

**Condition 3 — met.** Still twenty-two quantities; declarations 23 → 26, both numbers in
the spec (T48: technik.md:2305–2308; section 22: 4315–4320). Today's 23 reproduces:
exactly 23 `[[nodiscard]]` declarations outside `intern` in werte.hpp (lines 180–487),
`handelsvolumen` twice; the no.-11 precedent for "a name once, its forms beside it"
stands in the header's own head comment (werte.hpp:33–34).

**Core evidence reproduced.** spiel.md *Wo die Regel läuft* (2080–2096) books
16+2+40+12+4 `lies_neu` + 32 `lies_alt` = 106; the 56 = 40+12+4 arrive through
`Zustand`-carried quantities; *Die eine Regel* (1725–1736) writes all three with
`lies_neu`. `schaden` has no caller in `kern/src` (only the definition, werte.cpp:940)
and exactly twelve call sites in werte_probe.cpp (1576–1686). Report 2's reading of
`probe_schaden_zollzeile` is accurate: the writer is constructed from the same `z`
(werte_probe.cpp:1563–1567) and the round writes only instrument levels and world prices
(1544–1557). `rundenende()` releases a state only after the mask check
(schreiber.hpp:501–504). The marktkorb-precedent rejection is grounded: T33, "quantities
via lies_alt, prices via lies_neu" (technik.md:3046).

**Finding 1 (accuracy; violates no condition).** technik.md:4288 quotes T39 in German
(„kein stiller Rueckgriff auf `alt`"), but T39 is translated and today reads "that is a
hard error, not a silent fallback to `alt`" (technik.md:1417–1419). Same meaning, but
the quoted wording exists nowhere in the document — ungreppable, the defect class of
pruefung 0224. A one-line edit for the next citation-repair wave; no package proposed
for one sentence.

**Probed, nothing found:** leftover two-input prescriptions (`schaden\(z` in technik.md
hits only section 22, which quotes the built version as the thing to move);
table-vs-spiel.md contradictions (row-by-row match, incl. the line-wrapped quote "by two
paths instead of one", spiel.md:2128–2129); ADR touchstone (technik.md:995–1003 is about
`schritt`; the section engages it and leaves the fallback explicit).
