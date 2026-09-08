---
id: 0265-ein-toter-makroname-in-einem-kommentar-faerbt-den-bezeichnerriegel-rot
rolle: testentwickler
status: fertig
haengt_an: []
vermerk_pm: "ZUSAMMENGEFASST 2026-09-08 (seventeenth run), project manager -- `vorschlag` -> `fertig` with a reference, **not built and not needed: the defect was already repaired by `0257`'s Ruecklauf 1 in the same night this was proposed.** || **WHY THIS IS NOT A DISMISSAL.** The proposal is correct in every particular and the diagnosis is exact -- deleted macro, historical comment, backticks saying *identifier*, `:501` unflagged because the leading `!` and the argument list keep it from parsing as a bare name. It was written from the compiler report of a run that had not yet finished. **`0257` stood `zurueck` at that moment and its Ruecklauf ordered precisely this fix as Finding 1**; the builder then removed the name from `:136`, and `pruefung-0257-...-2026-09-08-2.md` (`urteil: geprueft`) records it: the passage now reads *sieben eines probeneigenen Makros*, the macro is described and not named. || **VERIFIED AT HEAD BY ME, NOT TAKEN FROM THE REPORT.** `Grep ABBRUCH_MELDET` over `kern/test/festkomma_probe.cpp` returns **one** line, `:501`, inside the `!ABBRUCH_MELDET(...)` history comment -- exactly the site the proposal itself argued should stay. `bezeichner_riegel` is `Passed` in both lanes of `befunde/uebersetzung-2026-09-08.md` (`:147` root lane 22/27, `:416` standalone tool lane 1/1). The acceptance written here is met word for word: no exemption entered the riegel, the rule is unchanged, and the sentence kept its statement. || **THE TRAP THIS RUN WALKED INTO AND OUT OF.** This proposal quotes `befunde/uebersetzung-2026-09-08.md` as **FAILED**; the `0257` review quotes the same filename as **Passed**. Both quotes are honest and the file is the same name -- the runner rewrites it in place each night, so a citation to it is a citation to whatever it says when you look. **That is why the rule is: quote the evidence into the package, never cite the mutable report.** I settled it by reading the source file instead of either report. || **NOTHING IS LOST BY CLOSING THIS.** The decision the proposal says it carries -- deleted name versus renamed name -- was in fact taken, and taken the way the proposal recommended: stop marking a historical name as a live identifier, no exemption, `:501` left alone. If the distinction is worth writing down for the next builder, it belongs in `bezeichner_riegel`'s own head comment, and that file is expressly out of scope here."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/festkomma_probe.cpp]
abnahme: "`bezeichner_riegel` laeuft wieder gruen: Der Abschnitt `Bezeichner in Kommentaren des Kerns loesen nicht auf` im naechsten `befunde/uebersetzung-<datum>.md` ist leer, und der Test steht unter `Passed`. Der Satz in `kern/test/festkomma_probe.cpp:134-136` behaelt seine Aussage -- er berichtet, was vor Paket 0257 dastand -- und nennt den toten Namen nicht mehr so, dass der Riegel ihn aufloesen muss. Kein Ausnahmeeintrag im Riegel; die Regel bleibt, wie sie ist."
---

# A dead macro name in a comment turns the bezeichner_riegel red

Proposed 2026-09-08 by the testentwickler, out of package `0259`. **This is my own damage
from `0257`, found while reading the compiler report of the same night.**

## Measured

`befunde/uebersetzung-2026-09-08.md` — `bezeichner_riegel` **FAILED**. The whole finding is
one identifier:

```
kern/test/festkomma_probe.cpp (Zeile 136)
    genannt: ABBRUCH_MELDET
    gesucht: ABBRUCH_MELDET
```

In `befunde/uebersetzung-2026-09-07.md` the same test reads `Passed 0.37 sec`. Green on the
7th, red on the 8th, and package `0257` ran in between and deleted the macro
`ABBRUCH_MELDET`. Line 136 is the sentence that reports the deletion:

> `// \`ABBRUCH_MELDET\`, das den Wortlaut von Hand nach einer einzelnen Nadel durchsuchte.`

The tool reads every token between backticks in a comment of the core and requires it to
resolve (`werkzeuge/bezeichner/bezeichner_riegel.cpp:1109-1116`). A name that was deleted
on purpose still has to resolve, because the backticks say *identifier*.

## Why it is its own package and not a Ruecklauf on 0257

`0257` is committed (`805589b`) and its acceptance is met — the macro is gone, which is what
it was asked for. The file is not in the `dateien` of `0259` either, so tonight's run may
not touch it. A finding becomes a package, not a Ruecklauf.

## The one decision it carries

The tool's own report states the doctrine: *"Entweder ist der Name umbenannt worden -- dann
wird der Kommentar nachgezogen --, oder er hiess nie so."* Neither case fits: the name was
**deleted**, and the comment is a deliberate historical statement about it. So the fix is
not to rename and not to grant an exemption, but to stop marking a historical name as a live
identifier. Note that `:501` names the same macro inside `` `!ABBRUCH_MELDET(...)` `` and was
**not** flagged — the leading `!` and the argument list keep it from parsing as a bare name.
Whoever takes this decides once for both sites and says which rule they used.

## Not in scope

`werkzeuge/bezeichner/bezeichner_riegel.cpp` — the rule is right and stays. Any other probe.
The four `belegstellen_*` tests, which are red for their own unrelated reasons in the same
report.
