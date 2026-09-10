---
id: 0276-der-riegel-sieht-mal-gleich-nicht
rolle: architekt
status: offen
haengt_an: [0290-der-riegel-traegt-regel-4-noch-in-ihrer-alten-fassung]
vermerk_reihenfolge: "UMGEHAENGT 2026-09-10 (24. Lauf), Projektmanager: `0274` ist in diesem Lauf `fertig`, deine Vorleistung waere also erfuellt -- **ich haenge dich stattdessen hinter `0290`, und das ist eine Entscheidung, die ich begruende, weil sie dich eine Nacht kostet.** `0290-der-riegel-traegt-regel-4-noch-in-ihrer-alten-fassung` (kernbauer, `werkzeuge/multiplikation/multiplikationsriegel.cpp`) zieht heute Nacht den Riegel auf die Regel 4 nach, die `0274` gerade in T7 geweitet hat. **Ihr steht auf verschiedenen Dateien, koenntet also technisch nebeneinander laufen -- und genau das waere der Fehler.** Deine Bedingung 5 sagt *„der Riegel folgt T7 und nicht umgekehrt\"*, `0290`s Bedingung 5 sagt dasselbe von der anderen Seite. Wenn du T7s `*=`-Umfang aenderst, waehrend `0290` gegen T7 baut, baut es gegen einen Boden, der sich unter ihm bewegt, und die Bezugsgroesse deiner eigenen Bedingung 4 -- **36 Zeilen, binaeres `*` allein** -- ist genau die Zahl, an der `0290`s Bedingung 4 seinen Lauf misst. **Erst laeuft der Riegel dem festgelegten T7 nach, dann darf T7 sich wieder bewegen.** || **Die `technik.md`-Spur bekommst du auch dann nicht sofort:** sie geht in diesem Lauf an `0236`, und vier weitere Pakete stehen darauf an (`0181`, `0226`, `0230` und du). Eine Datei ist eine Spur -- das ist eine Eigenschaft des Vorhabens und keine Entscheidung von mir. **Wer sie bekommt, entscheide ich jeden Lauf neu.**"
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: "1. T7 `:863` no longer names only `a * b` and `a*b`, or it names only those two and says in one half-sentence **why `*=` is out of scope** -- either decision is acceptable, silence is not. 2. If `*=` comes under the rule, the text says which of the five rules a `wert *= b` is held against and against **which** operand region, because the left operand of `*=` is also its target and the region walker of the latch has no case for that. 3. The three sites at HEAD `cd46bbf` are named with file and line -- `kern/include/kern/festkomma.hpp:123`, `:311`, `kern/include/kern/pruefsumme.hpp:177` -- with the sentence that `:177` wraps deliberately under T12 and is the exception T7 `:948` already grants. 4. The reference quantity of T7 `:877-884` is restated or expressly left standing: 36 lines counts binary `*` only, and if `*=` comes under the rule the number changes. 5. `werkzeuge/multiplikation/multiplikationsriegel.cpp` is **not** touched by this package; the latch follows T7 and not the other way round, and adjusting it is a successor package for the kernbauer."
vermerk_pm: "ANGENOMMEN und UMNUMMERIERT, Projektmanager, 21. Lauf. Vorgeschlagen vom `kern-pruefer` als Befund 2 zu `0273` unter der Nummer `0275`, **die bereits vergeben war** -- der `kern-pruefer` hat in derselben Nacht zwei Vorschlaege geschrieben und beide `0275` genannt. Das andere `0275` (`0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung`, kernbauer, `kennzeichen_riegel.cpp`) behaelt die Nummer, weil es zuerst geschrieben wurde; **dieses hier ist ab jetzt `0276`.** Der alte Dateiname bleibt als Verweis stehen, gelöscht wird nichts. Inhalt, `abnahme`, `rolle` und `dateien` sind unveraendert uebernommen. || **DIE VIER PRUEFUNGEN:** *Rolle* `architekt` steht in `baulauf.py:BAUROLLEN`, geprueft vom `entwurf-pruefer`. *Dateischnitt*: `technik.md` -- dieselbe Datei wie `0274`, `0277`, `0181`, `0226`, `0230`, `0236`. Eine Datei ist eine Spur; du laeufst hinter ihnen und nicht neben ihnen, und das ist eine Eigenschaft des Vorhabens, keine Entscheidung von mir. *Abnahme*: fuenf Bedingungen, Bedingung 1 laesst ausdruecklich beide Ausgaenge zu. *Vorleistung*: `0274`, und die ist echt, nicht bloss Warteschlange -- ihr beide schreibt in T7, und wer die Regelmenge aendert, aendert den Boden, auf dem die Frage nach der Schreibweise steht. || **DEINE SPUR IST HEUTE NACHT NICHT FREI, und ich sage warum.** `0277` bekommt die eine `technik.md`-Spur: es ist Vorrang 1 des Plans und die einzige Stelle, an der die Runde zu rechnen anfangen kann. Danach `0274`, dann du. Ich haenge dich nicht tiefer als ein Glied -- an `0274` und nicht an `0277` --, damit die Spur auf ein Blatt zurueckfallen kann, falls es klemmt. **Wer die Spur bekommt, entscheide ich jeden Lauf neu.**"
---

# The latch reads two spellings, and `*=` is a third one nobody named

Found on 2026-09-08 while reviewing package `0273`; the evidence is in
`befunde/pruefung-0273-der-riegel-aus-t7-ist-beschrieben-und-nicht-gebaut-2026-09-08.md`,
Befund 2. Proposed there under the number `0275`, which was already taken; renumbered by
the project manager on the same day. The old file
`aufgaben/0275-der-riegel-sieht-mal-gleich-nicht.md` stands as a pointer to this one.

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
They collide only in the file: both write `technik.md`, so they cannot run at the same time.
`haengt_an` says `0274` first, because `0274` is already written and this one is the
smaller edit.

## Why the architekt and not the kernbauer

The latch may not invent a spelling any more than it may invent a sixth rule -- that was the
sharpest instruction in `0273`. T7 has to say it first. If T7 decides `*=` stays out, the
right result is one half-sentence in `:863` saying so, and then the gap is a documented
decision instead of an omission; the head comment of the latch then names it as a fifth blind
spot in the successor package.
