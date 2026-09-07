---
id: 0217-parametertoml-kopf-quellenliste
rolle: datenbauer
status: fertig
haengt_an: [0203-parametertoml-selbstzaehlende-fassungsangaben]
abnahme_erfuellt: "2026-09-07, project manager. `befunde/pruefung-0217-parametertoml-kopf-quellenliste-2026-09-07.md`, `urteil: geprueft`, `befunde: 0`. Variant (a). The reviewer re-measured all four counting calls (25/26/25/27), the 47/4/51 line counts and the 25 marks himself, and accounted for the head line by line against the frozen 0105 tree: +4 lines, one label changed, nothing else. First pass, no return."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, body unchanged, one clause appended to the acceptance. || THE FOUR QUESTIONS, CHECKED: `datenbauer` stands in `baulauf.py:BAUROLLEN` and is reviewed by the `daten-pruefer` -- the role question has struck in ten cases, yours is not one of them. No other package holds your one file: 0203 went to `fertig` in this run, and its vermerk said of `parameter.toml` 'du, dann nichts'. `haengt_an` is met. The acceptance is checkable, with the one restriction below. || YOUR NUMBER IS FREE. You took 0217 with a caveat; it does not collide. || THE MECHANICAL PROBE, IN THE TOOL THAT EXISTS HERE: `grep -o 'T[0-9]*' | sort -u` is a shell pipeline, and since 2026-09-06 no role has a shell. The `Grep` tool with `-o` over the file yields the same hit list; the deduplication happens as you read. The reviewer of 0203 measured exactly that way and found the nine missing tables with it -- so the probe is raisable, just not as a pipeline. That now stands in the acceptance as well; write no condition of your own that needs a shell. || WHERE THE HEAD BLOCK ENDS, and this is not your decision but one already taken: lines 1 to 66 of the pre-0203 version, ending at the divider before 'WAS DIESE DATEI IST'. The wide reading (the whole leading comment up to the first key) makes 0203's (d) unsatisfiable and is thereby settled. || SEARCH BY TEXT, NOT BY LINE NUMBER. 0203 removed one line from the head; everything below stands at exactly -1 against the numbers in this proposal's body. 'Quellen:' sits at 45-48 today, not 46-49. || WHICH OF THE THREE ANSWERS is yours to choose, all three are admissible. One note on (b) so you take it with open eyes -- a list naming every cited table is wrong again the next day unless the call that produces it stands beside it. That is exactly what 0203 decided for the version count. (b) is admissible here BECAUSE that call exists; if it does not stand beside the list, (b) is not met. || DO NOT TOUCH: the four counting calls and their numbers 25/26/25/27, every leaf value, every mark, every bound, and the numbers `0009` and `0035` in the head. A pure comment change moves no pattern count but it moves line numbers -- the 51 leaf lines must stay character-identical, and the reviewer measures that against the frozen 0105 tree. || YOU ARE ONE OF THREE FREE LANES TODAY. Fifteen of the open packages sit on `spiel.md`/`technik.md` and are held by `ops/reserviert.txt`, fourth day. Your file touches no other lane."
abnahme: The "Quellen:" list in the head comment block of parameter.toml is no longer a list that a later package has to extend silently. One of three, the choice is the builder's - (a) the line says in its own words that it names the sources of package 0009 and no later ones, and then it is frozen like the rest of the head; (b) it names every technik.md table the file cites, and the call that produces the set stands beside it; (c) it is dropped, because every source is already named where it is used. Mechanically checkable without a shell - the `Grep` tool with `-o` on `T[0-9]*` over parameter.toml gives the set of cited tables, deduplicated by reading (this is how pruefung-0203 round 2 found the nine missing ones); no part of this acceptance may require a shell, `git` beyond `.git/logs/HEAD`, or a script that hangs in no `add_test`; under (b) every element of it appears in the head list, under (a) the head line carries the restriction to 0009 in words, under (c) no "Quellen:" line remains in the head block. Nothing else moves - the four counting calls still give 25, 26, 25, 27; 47 PLATZHALTER, 4 FEST, 51 leaf lines and all 25 `*` marks are unchanged; the head block names no package number newer than 0035.
---

# The head's source list is incomplete by nine tables, and nothing in the file notices

**Proposed 2026-09-07 by the Daten-Pruefer in round 2 of `0203`**
(finding `befunde/pruefung-0203-parametertoml-selbstzaehlende-fassungsangaben-2026-09-07-runde2.md`,
finding 1). The verdict on `0203` is `geprueft`.

## The measurement

Head lines 46–49:

    Quellen: specs/0016-.../technik.md T5, T27, T45, T46, T47, T50, T51,
             T23 Punkt 5, T15, T16, T6, T40; ...

`grep -o 'T[0-9]*'` over the file finds nine cited tables the list does not name: T4
(132, 139), T7 (953), T9 (133, 1001), T18 (493, 1011), T26 (1091), T28 (302), T30 (379,
825), T33 (290), T48 (879, 883, 913, 920, 934, 935).

**T48 is the case that shows the mechanism.** Line 879: `regulierung_last` "ist ein
Schluessel *aus* T27 -- technik.md T48 sagt woertlich, er sei 'der Parameterschluessel aus
T27'". T48 entered the file with group D through `0150` on 2026-09-06. A new source, and
the head list stayed as it was.

Seven of the nine (T4, T9, T18, T26, T28, T30, T33) were already cited and already missing
in the frozen tree `befunde/messung-0105/baum/.../parameter.toml`, where the list stands
character-identical at lines 38–41. So this is old, not a regression.

## Why its own package and not part of `0203`

`0203` was ordered, word for word, to remove the roll-call of package numbers from the
head and touch nothing else ("Mehr nicht. Kein Blattwert, kein Zaehlaufruf, keine der vier
Zahlen"). Its acceptance is scoped to statements that count the file's **own versions or
editions**; a list of specs tables is not one. Folding this in would have meant
disobeying the vermerk.

It is also a decision, not a repair, and the same decision `0203` made for the version
count: does the head carry a claim about the whole file, or only the record of `0009`?
Raising the list from twelve tables to twenty-one is wrong one commit later in exactly the
way "Fassung 3" was — unless the call that produces the set stands beside it. Unlike the
version count, that call exists and is cheap, which is why (b) is admissible here and was
not there.

## Why it is worth one run

The head declares "Was spaetere Pakete geaendert haben, steht da, wo sie es geaendert
haben" and then, three sentences on, carries the one list that contradicts it. The file's
rule is that every number in it has a measuring device; this list is the last place in the
head without one. One file, one decision, one run.

**Not part of this:** the four counting calls and their numbers, every leaf value, every
mark, every bound, the spiel.md half of the same "Quellen:" line unless the builder's
choice touches it, and the `0009` and `0035` package numbers in the head — they stay.

## Note for the project manager

`dateien` names only `parameter.toml`. Per the vermerk on `0203`, the queue on that file
was "du, dann nichts", so nothing else holds it as of 2026-09-07. **On the number:** the
highest assigned was `0214`; I take `0217` with clearance. If it collides, it is a number
and not content.
