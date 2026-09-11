---
typ: pruefung
paket: 0289-die-doppelte-klammer-macht-aus-zwei-elementen-eines
pruefer: kern-pruefer
datum: 2026-09-11
urteil: zurueck
kriterium_geprueft: "hand-traced `elemente_einer_liste` against the doubled brace, recounted 19/11/30/16 and cases 20-30 at HEAD 475f971, read all four references to \"the last case\""
befunde: 1
---

Conditions 1, 2, 3, 4, 5(b) and 5(c) hold. **5(a) does not:** the repaired head of
`knappe_listen` carries a *new* positional reference, and condition 2's appended case 30
makes it false in the same commit.

## Befund 1 (blocking) -- `kennzeichen_riegel.cpp:1526-1529`

> **Genannt sind sie am `was` und nicht an ihrer Stellung.** Der letzte Fall der Tabelle
> gibt eine Marke und ein Element gegen zwei deklarierte her, meldet also unter jeder der
> beiden Aenderungen weiter [...]

**How to produce it.** Read `:1526` at HEAD `475f971`, then read the last case of
`TABELLENFAELLE`. It is case 30 at `:2078` — „eine vollstaendige Liste in doppelter
Klammer", `std::array<const char*, 2> KZ_DOPPELKLAMMER = {{"alpha", "beta"}}`: **2
declared, 2 marks, 2 elements.** Not „eine Marke und ein Element gegen zwei deklarierte";
those are case **29**'s numbers (`:2047`, `KZ_DORT = {"gamma"}` against 2 declared).

The conclusion is inverted too. Under `lz.stuecke` alone case 30 gives `2 >= 2`, under the
maximum `2 >= 2` — it reports under **neither** change, and because it expects
`listen_knapp: 0` it stays green under both. So the sentence's own witness now proves the
opposite of what the sentence uses it for.

**It was written in this run.** The criterion quotes the old wording („der letzte Fall der
zweiten Falltabelle geht dann rot"), which cannot have carried the meta-sentence „Genannt
sind sie am `was` und nicht an ihrer Stellung"; and „ein Verweis auf die Stellung war hier
schon zweimal falsch" is `0293`'s finding. The builder repeated the defect inside the
sentence that announces its repair.

**Why this is `zurueck` and not a note.** Condition 5 was folded into this package for one
stated reason — the append invalidates positional references, so both halves must land in
one run, „ein Agent, eine Datei, ein Lauf". A green verdict here buys a fourth package on
the same file for the same class. Condition 3 also reaches it: „every count in the head
that this change touches recounted at HEAD" — 1 mark / 1 element / 2 declared, attached to
„der letzte Fall", is such a count, and the append moved it.

The repair is one sentence, and the correct witnesses are already named two paragraphs
above (`:1515-1524`): case 28 under both mutations, case 26 under the maximum. Name case 29
by its `was` text, or drop the sentence.

## What I checked, and how

**Condition 1 — the count.** Hand-traced `elemente_einer_liste` (`:952-966`) on
`{{"a", "b"}}`: `felder_von` yields one field starting at the inner `{`;
`balanciert` (`:782`) returns the inner `}`, `innen_zu + 1 == felder[0].zu` holds, so the
group shrinks to the inner braces and the second pass splits at the comma → **2**.
`{{A}, {B}}` has two outer fields and never enters the loop (2, as before); `{{"a"}}`
falls to 1 and was 1. The loop terminates: `g.auf` strictly increases each round. The
mask, not the text, is scanned, so braces inside literals cannot reach it. No weakening:
`{{"a","b"}}` declared 3 still yields 2 < 3.

**Condition 2 — the red proof** stands at `:2061-2066` and names the mechanism
(`finde_zuweisungen` sets `auf` on the first brace → one field → `elemente` 1 against 2
declared → the expected 0 becomes 1).

**Condition 3 — counts recounted.** 30 initialisers between `:1747` and `:2078` against
`std::array<Tabellenfall, 30>`; 19 unchanged, 10→11, 29→30 („Fall 20 bis Fall 30"),
six ones (20, 22, 24, 26, 28, 29) and five zeros (21, 23, 25, 27, 30) — checked field by
field; 16 = 19 − 3 (`lesbar: false`) unchanged; `:2536`/`:2549` derive from `.size()`.
Cases 26, 28 and 29 carry exactly the numbers the criterion recounted at HEAD on
2026-09-10, so no existing case moved and no expectation was lowered.

**Condition 4 — the build.** `befunde/uebersetzung-2026-09-11.md`, HEAD `475f971`:
`kennzeichen_riegel` Passed (main tree test #30, own tree 1/1). The three failures are
`belegstellen_wortabstand`, `zahlwort_messung`, `multiplikationsriegel` — none of them
reads this file.

**Determinism (lens 1).** Grep for `float|double|unordered|std::map|std::set|rand(|time(|chrono|getenv`
over the whole file: **0 hits.** Index access only, no pointer, no raw array.

**5(b)** `:1322-1334` names „zwei Proben, eine Stelle auf der Maske" by its `was`, no
position. **5(c)** `:302-306` names the same case by `was` and states the self-test's last
case is the last of the third table — true: `ABGLEICHFAELLE`'s last entry is at `:2326`.

No proposal: the repair belongs in this package's Ruecklauf, not in a new one.
