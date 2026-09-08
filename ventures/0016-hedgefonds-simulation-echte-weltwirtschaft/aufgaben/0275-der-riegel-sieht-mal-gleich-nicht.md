---
id: 0275-der-riegel-sieht-mal-gleich-nicht
rolle: architekt
status: fertig
haengt_an: []
dateien: []
verweis_2026_09_08: "UMNUMMERIERT, nicht abgelehnt und nicht gebaut. Dieses Paket ist inhaltlich **angenommen** und steht seit dem 2026-09-08 als `aufgaben/0276-der-riegel-sieht-mal-gleich-nicht.md`. Grund: die Nummer 0275 war doppelt vergeben -- der `kern-pruefer` schrieb in derselben Nacht zwei Vorschlaege und nannte beide `0275`. Das andere behaelt die Nummer, weil es zuerst geschrieben wurde. `status: fertig` ist hier die vom Rollenvertrag vorgesehene Form fuer einen Vorschlag, der anderswo weiterlebt (Projektmanager-Rollendatei: „zusammengefasst -- trag es dort ein, setz den Vorschlag auf `fertig` mit einem Verweis\"), und **keine Abnahme**: es gibt keinen Pruefbefund zu dieser Kennung und es soll keiner geben. `dateien` und `haengt_an` sind geleert, damit dieser Eintrag keine Spur mehr beansprucht. Geloescht wird nichts. **Der Auftrag steht in `0276`; arbeite dort und nicht hier.**"
abnahme: "1. T7 `:863` no longer names only `a * b` and `a*b`, or it names only those two and says in one half-sentence **why `*=` is out of scope** -- either decision is acceptable, silence is not. 2. If `*=` comes under the rule, the text says which of the five rules a `wert *= b` is held against and against **which** operand region, because the left operand of `*=` is also its target and the region walker of the latch has no case for that. 3. The three sites at HEAD `cd46bbf` are named with file and line -- `kern/include/kern/festkomma.hpp:123`, `:311`, `kern/include/kern/pruefsumme.hpp:177` -- with the sentence that `:177` wraps deliberately under T12 and is the exception T7 `:948` already grants. 4. The reference quantity of T7 `:877-884` is restated or expressly left standing: 36 lines counts binary `*` only, and if `*=` comes under the rule the number changes. 5. `werkzeuge/multiplikation/multiplikationsriegel.cpp` is **not** touched by this package; the latch follows T7 and not the other way round, and adjusting it is a successor package for the kernbauer."
---

# The latch reads two spellings, and `*=` is a third one nobody named

Found on 2026-09-08 while reviewing package `0273`; the evidence is in
`befunde/pruefung-0273-...-2026-09-08.md`, Befund 2.

## What is missing

`ist_binaeres_mal` (`multiplikationsriegel.cpp:416-424`) takes a `*` only when there is
whitespace on **both** sides or a name character on **both** sides. That is exactly the two
spellings T7 `:863` prescribes, and the builder is right to build no third one. But `wert *= b`
carries `=` on the right, so the latch never sees it: it produces no rule, no finding, and it
does not even raise the line count that condition 3 of `0273` makes the latch report.

Measure 4.3 (`:800-805`) says *every* multiplication of two `i64` runs through `mal(a, b)`.
`wert *= faktor;` is such a multiplication. Today nothing is violated -- the three sites are
`i128 *= i128` inside guarded loops (`festkomma.hpp:123` in `potenz_i128`, `:311` in `potenz`,
both with the overflow check in the same loop body) and the FNV checksum
`pruefsumme.hpp:177`, which wraps on purpose under T12. But the reason the latch exists at all
is T7 `:828-831`: an enumeration *„would here be the form that silently goes wrong at the next
addition."* A spelling gap has the same failure mode one level down, and it is quieter,
because it does not even change a number.

## Why this is its own package and not part of `0274`

`0274` decides one thing: whether `festkomma.hpp:99` and `:356` fall under a **named** rule,
i.e. whether the rule *set* is complete. This package decides a different thing: whether the
*corpus of sites* the rules are held against is complete. The two are independent -- `0274`
can be answered either way without touching `:863`, and this one without touching `:841-857`.
They collide only in the file: both write `technik.md`, so they cannot be `offen` at the same
time. `haengt_an` says `0274` first, because `0274` is already written and this one is the
smaller edit.

## Why the architekt and not the kernbauer

The latch may not invent a spelling any more than it may invent a sixth rule -- that was the
sharpest instruction in `0273`. T7 has to say it first. If T7 decides `*=` stays out, the
right result is one half-sentence in `:863` saying so, and then the gap is a documented
decision instead of an omission; the head comment of the latch then names it as a fifth blind
spot in the successor package.
