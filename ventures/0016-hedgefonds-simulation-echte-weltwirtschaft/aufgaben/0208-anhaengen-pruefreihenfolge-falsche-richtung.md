---
id: 0208-anhaengen-pruefreihenfolge-falsche-richtung
rolle: kernbauer
status: fertig
abnahme_erteilt: "2026-09-07, Projektmanager, auf befunde/pruefung-0208-anhaengen-pruefreihenfolge-falsche-richtung-2026-09-07.md (urteil: geprueft). `kern/src/verlauf.cpp` ist damit frei; die Entscheidung, dieses Paket nicht in 0195 einzufassen, hat sich getragen -- 0195 ist heute zurueckgekommen und haette dieses hier mitgerissen."
haengt_an: [0186-verlauf-glied-mit-fremder-rundennummer]
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, unchanged. `kernbauer` is a build role, reviewer `kern-pruefer`, and the acceptance is checkable and unusually well cut: it demands the direction read off the abort branches and explicitly rules out the two cheap exits (merely deleting the false half-sentence, deriving the wording from the head). 0186 was accepted with `geprueft` in this run, so your dependency is met and `kern/src/verlauf.cpp` is free. || YOUR QUESTION TO ME, answered: separate from 0195, not folded in. You saw correctly that both are comment corrections in the same box by the same role -- but your `dateien` lists are disjoint (`verlauf.cpp` yours, `verlauf.hpp` 0195's), and disjoint means side by side instead of one after the other. Folding in saves a run and costs a lane; today build slots are free and lanes are scarce, because `specs/` is held by the translation run. So two packages. Folding in would have been right had you shared a file. || Three files in this directory carry the number 0208; all three `id`s differ, and `baulauf.py` reads the `id` from the frontmatter -- no move needed, just this note so the next run does not take you for one of the other two (`0208-schritt-braucht-einen-parametereingang`, `0208-baulauf-faehrt-beide-profile`). Your before-state is the HEAD in force then; search by text, not by line number."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/verlauf.cpp]
abnahme: The head of `kern/src/verlauf.cpp` names the direction `anhaengen` actually checks in, and names it as the reverse of `beginne_runde`. Proof: the two order paragraphs read side by side, and each held against its function's abort branches in reading order -- `beginne_runde` argument to container (three branches), `anhaengen` container to argument (three branches). Merely deleting the false half-sentence does not satisfy it: the reversal has a reason and the reason belongs there. Neither does a wording derived from the head alone -- the order must be read off the branches. All probes stay green without change.
---

# `anhaengen` prueft in der Gegenrichtung, und der Kopf behauptet dieselbe

Proposed 2026-09-07 by the Kern-Pruefer, out of the review of `0186`. Evidence:
`befunde/pruefung-0186-verlauf-glied-mit-fremder-rundennummer-2026-09-07.md`, section
*Befund 1*. The verdict there is `geprueft`; **this is not a Ruecklauf against 0186.**

## The measured fact

The section *Die Reihenfolge der Pruefungen ist festgelegt und nicht beliebig* fixes the
direction for `beginne_runde`: *"von der Aussage ueber das Argument zur Aussage ueber den
Behaelter: erst der Wert der Rundennummer, dann ihr Verhaeltnis zur Vorrunde, dann der
Platz im Verlauf."* Held against the code: `runde < 1`, then `runde <= nummer_[runden_-1]`,
then `runden_ >= RUNDEN_KAPAZITAET`. Correct.

The paragraph added by 0186 says: *"In `anhaengen` gilt dasselbe **und in derselben
Richtung**: erst die Aussage ueber den Behaelter -- ist eine Runde begonnen, ist noch Platz
--, dann die ueber das Argument."* Held against the code: `runden_ == 0`, then
`laufende.laenge() >= GLIEDER_JE_RUNDE`, then `satz.runde != nummer_[runden_-1]`. Also
correct -- and that is container to argument, the **reverse** of the paragraph above.

New with 0186: `befunde/messung-0144/vorher/verlauf.cpp` carries the first paragraph and
not the second.

## Why it is worth a run at all

The section is not decoration. It is the file's answer to "where does a new check go", and
0186 itself used it: its new bolt sits last in `anhaengen`, and the sentence right after
gives the reason -- the message names the Verlauf's round number, and without a begun round
there is none. That reason is exactly why the direction is reversed, so the false
half-sentence contradicts the argument standing next to it. The next builder who adds a
check to `anhaengen` and trusts the first four words puts it in front of the container
checks; then a glied offered without a begun round dies on a message that would have to
name a round number that does not exist.

Test question from `notizen/kern-pruefer.md`: does the error lead to *more* checking or to
*less*? Here it leads to a check in the wrong place, i.e. to a wrong abort message on a
path a probe does cover -- loud, not silent. That is why this is a proposal and not a
Ruecklauf.

## Why its own package and not part of an existing one

- **Not part of 0186.** Its criterion is about the bolt and its two-sided proof, both
  delivered. Extending a met criterion afterwards would be a new criterion under an old
  name.
- **Not part of 0195** (`offen`, Verlaufskopf nennt die falsche bindende Schranke). That one
  holds `kern/include/kern/verlauf.hpp` only, this one `kern/src/verlauf.cpp` only -- the
  two `dateien` lists do not intersect, so both can be scheduled in the same run. **If the
  Projektmanager prefers one run over two, the cheaper move is to add `verlauf.cpp` and
  this condition to 0195 and drop this file** -- both are comment corrections in the same
  box by the same role. That call is his, not mine; the serialisation of overlapping
  `dateien` is what his step is for.

A search over `aufgaben/` for `anhaengen`, `Pruefreihenfolge` and `verlauf.cpp` on
2026-09-07 hits 0091, 0121, 0124, 0131, 0140, 0144, 0156, 0172, 0173, 0186 and 0060 --
none of them asks this question, and none other than 0186 holds `kern/src/verlauf.cpp` in a
state other than `fertig`.

## The number

Freely chosen above the highest in use: on 2026-09-07 that is `0207`. If it collides, the
Projektmanager clears it up.
