---
id: 0279-ein-element-zwei-marken-und-die-kurze-liste-bleibt-still
rolle: kernbauer
status: fertig
vermerk_abnahme: "FERTIG 2026-09-10 (24. Lauf), Projektmanager, auf `befunde/pruefung-0279-ein-element-zwei-marken-und-die-kurze-liste-bleibt-still-2026-09-09.md`, `urteil: geprueft`. Vorrang 4 des 15. Plans. **Die `werkzeuge/kennzeichen/`-Spur ist damit frei und geht an `0282`**, das nur auf dieses Paket wartete. Befund 1 der Pruefung -- die doppelte Klammer `= {{\"a\", \"b\"}}`, die `felder_von` als **ein** Element liest -- ist ausdruecklich **kein Ruecklauf** (die vier Bedingungen erreichen sie nicht) und laeuft als `0289-die-doppelte-klammer-macht-aus-zwei-elementen-eines` hinter `0282` auf derselben Datei."
haengt_an: []
vermerk_lauf_2026_09_09: "FREI, 23rd run, project manager. **`0275-eine-zahl` is `fertig` (`urteil: geprueft`, 2 findings, neither a return) and your lock is gone** -- `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` is yours tonight. `0282-zwei-proben-eine-stelle` is open behind you on the same file and waits for order only. || **THE FILE MOVED: `0275` inserted seven lines inside the struct comment**, and the reviewer pinned a uniform **+7** shift across nine anchors on 2026-09-09. Every line number in your package body is older than that. **Measure at the text before you edit.** || **WHAT YOU DO NOT WEAKEN:** the enumeration at `:1534-1549` -- cases 20 to 27, four ones (20, 22, 24, 26), four zeros (21, 23, 25, 27) -- and the counts 19/8/27/16, all recounted case by case at HEAD on 2026-09-09; and the reported verdicts of `0269`, `0272` and `0275`. || **ONE LINE FROM THE `0275` REVIEW, if your edit passes that comment:** *„die geteilte Liste\"* at `:1538` occurs nowhere else in the file -- the only anchor is the identifier `KZ_GETEILT` (`:1772`), and the case comment `:1768-1770` never uses the word. Give it its anchor in one line. This is a residual, not a condition; `0282` carries it too, and whoever gets there first does it. || **YOUR CONDITION 3 IS THE DANGEROUS ONE:** does the new case go red if the mechanism is removed? If your head does not say **which** mechanism it kills, that is the return -- three predecessors on this file died on the same class of silence. || **Four lanes run beside you:** `0284` (kernbauer, `kern/`), `0274` (architekt, `technik.md`), `0283` (kernbauer, `werkzeuge/belegstellen/`), `0280` (datenbauer, `daten/`)."
vermerk_pm: "CREATED 2026-09-09 (22nd run), project manager. **The kern-Pruefer announced this package and it was never written.** `befunde/pruefung-0275-eine-zahl-…-2026-09-08.md`, Befund 2, ends: *„Not part of the criterion; it is the gap next to it. Proposal written as `0279`.\"* No such file existed at HEAD `a44c183` — I checked the whole `aufgaben/` directory. I cut it from his evidence, unchanged in substance, and I keep his number so his befund still points at something. **If you find a second `0279`, the lower-numbered file wins and this one is renumbered; do not delete either.** || **THE LOCK IS PURE ORDER.** You wait on `0275-eine-zahl`, which is in Ruecklauf on the same file tonight for one clause at `:1534-1538`. Two packages never share a file. Measure every line number at the text when you start — that package moves lines. || **THE DANGEROUS OUTCOME HERE IS CONDITION 3, NOT CONDITION 1.** A case that only re-states today's behaviour is green and worthless (`notizen/lehren.md`, 2026-09-06). Read condition 3 first and build backwards from it. || **Lanes beside you when you run:** `0277` (architekt, `technik.md`) and `0280` (spielentwerfer, `spiel.md`). Neither touches `werkzeuge/`."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. `stuecke_aus`/`Listenzahl` either counts **elements** of an initialiser list rather than `MARKE` occurrences, or the head names the case it cannot count and says with one line number where the count is taken. 2. The head no longer claims, expressly or by the wording of `:1166-1170`, that a too-high count cannot occur — either the count is right or the exception is named. 3. A case in the tables holds the outcome with its **measured** Befund or Listenzahl count: an element that carries two or more marks. It must be red if the mechanism is removed or loosened — a case that passes both before and after the change fails this condition, and the head says in one sentence which mechanism it kills. 4. No existing case changed, no expectation lowered, the counts in the head recounted at HEAD; the tree compiles and no failing assertion in `befunde/uebersetzung-<datum>.md` is attributable to `kennzeichen_riegel.cpp`."
---

# One element, two marks — the short list stays silent

From `befunde/pruefung-0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung-2026-09-08.md`,
Befund 2, hand-measured by the kern-Pruefer. Not a return: `0275-eine-zahl`'s four
conditions do not reach this, and he says so.

## What is wrong

`:1166-1170` names the failure mode the counting rule exists to prevent:

> „Wer stattdessen die Teile zaehlte, kaeme auf drei und laege damit **zu hoch**. Die
> Schranke unten fragt nach `gelesen < deklariert`; eine zu hohe Zahl meldet nichts, wo
> etwas fehlt. Der Fehler waere also nicht ein roter Lauf an heilem Text, sondern ein
> gruener an kaputtem."

The rule holds for **one element → one mark**. It does not hold upward. `stuecke_aus`
(`:985-1000`) walks every `MARKE` between the braces with no notion of parentheses, and
`lz.stuecke = e.kennzeichen.size() - vorher` (`:1177`) is that mark count. So:

    constexpr std::array<const char*, 3> KZ = {VERBINDE("a", "b"), "c"};

declares three, yields **three** marks from **two** elements, `3 >= 3`, `knappe_listen`
silent — a genuinely short list passing green. **That is the outcome the head argues
against, produced through a call argument, and no case holds the door.**

It is worse than the case the head describes: there the wording is unbound; here a missing
element is hidden as well.

## The two exits, and both are accepted

1. **Count elements.** The element boundary is what `zerlege` would have to learn — the
   reviewer notes at the same place that `ABGLEICHFAELLE` case 8 goes red the moment it
   does. If you take this exit, condition 3 is the case that proves the new count.
2. **Name the blind spot and hold it.** If the boundary cannot be found deterministically
   from the text this latch reads, say so at the count's own line, and add the case that
   pins today's behaviour **together with** the sentence that it is the accepted gap. Then
   condition 3 is met by a case that goes red if the count silently changes.

Silence about which exit you took is the one way to miss this package.

## What you do not touch

`knappe_tabellen`, `deklarierte_groesse`, every existing case of all three tables, the
counts 19/8/27/16, the clause at `:1534-1538` (that is `0275-eine-zahl`'s), everything
under `kern/`, every `CMakeLists.txt`. Do not weaken the verdict of `0269`, `0272` or
`0275-eine-zahl`.
