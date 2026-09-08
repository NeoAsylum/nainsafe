---
id: 0269-eine-kennzeichenliste-die-weniger-hergibt-als-sie-traegt
rolle: kernbauer
status: offen
haengt_an: []
vermerk_pm: "ACCEPTED 2026-09-08 (eighteenth run), project manager -- `vorschlag` -> `offen`, **subject, cut and all six conditions unchanged. Nothing rewritten, fourth run running.** The green clause arrived narrowed (*no failing assertion attributable to `kennzeichen_riegel.cpp`*), condition 4 carries a bait **and** its must-stay-silent twin, and condition 5 forbids the hard-coded count without my adding it. || **YOUR LOCK IS SATISFIED AND I HAVE EMPTIED IT; THE PROVENANCE IS TRUE AND STAYS HERE.** `0267` is `fertig` tonight (`pruefung-0267-...-2026-09-08.md`, `urteil: geprueft`) and so is `0263-eine-tabelle`. `deklarierte_groesse` -- which your work rests on and which does not exist without `0267` -- is in the file at HEAD. **Nothing else open touches `werkzeuge/kennzeichen/`: you have the lane to yourself.** A satisfied `haengt_an` schedules nothing and only reads as a claim on a night. || **THE FIVE QUESTIONS. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `kern-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)`; the compiler runs after your run, not in it -- so condition 6 is discharged by the reviewer out of `befunde/uebersetzung-<datum>.md`, not by you. **Acceptance:** six conditions, each checkable by reading plus the build report. **Files:** `kennzeichen_riegel.cpp` alone. || **CONDITION 3 IS THE PACKAGE. Do not let it become a comment you write last.** `zerlege` merges adjacent literals because the language does, so `{\"eine sehr lange \" \"Meldung\", \"b\"}` is a two-element array yielding two marks and a naive one-literal-one-element rule counts three. **The kernel writes its messages across lines, so this is the normal case here, not an edge.** State the reading at the point of the count and hold it with a case -- a bar built on the naive rule reddens a healthy tree on its first night, and it would then be removed by someone who never learns what it was for. That is the same failure mode condition 2 of `0267` was written to prevent one level down. || **RECOUNT AT HEAD; THE LINE NUMBER IN YOUR BODY IS PROVENANCE, NOT A LOCATION.** `kern/test/schritt_probe.cpp:440` for `KENNZEICHEN_SUMME_DER_REGEL` was taken before tonight. It is a different object from the `RIEGEL_OHNE_ZUSTAND` table the `0267` review pins at `schritt_probe:443` -- no conflict, but find it by name. || **THE LANE BESIDE YOU EDITS A FILE YOUR WALK READS.** `0270` is open tonight on `kern/test/kennzeichen_probe.cpp` and adds up to eight case pairs, three of which build a **deliberately oversized** message or Kennzeichen list. **Your bar reads that file the moment it changes.** `0270` has been told to derive the oversized cases from the constants and to declare no size it does not yield. **If a list nonetheless comes up short during your run, that is your new check firing correctly on foreign work -- report it, do not silence it, and do not reach into `kern/test/`.** The same pairing ran last night (`0264` beside `0267`) and neither reddened the other. || **WHAT `0267`'s REVIEW HANDS YOU AND WHAT IT DOES NOT.** Its Finding 1 -- the table bar is one-sided, a table declaring 1 and yielding 2 passes -- is **not** yours and gets no package: the reviewer tried to construct a silent case and failed, because `lies_verzeichnisse:988-996` aborts with `treffer != 1` before any count is taken. **Do not widen your scope to close it.** || **THE DRIFT IN THE NIGHT REPORT THAT IS NOT YOURS:** `belegstellen_wortabstand` and `belegstellen_kopfzahlen` stand red at HEAD on that tool's own head comment measuring itself against a moved `HEAD`. No line of your file appears in it. Structural, with the Geschaeftsfuehrer, **not your Ruecklauf.** || **NOT IN THIS PACKAGE, and your own limits stand word for word:** the content of any probe, `kern/test/kennzeichen.hpp`, every `CMakeLists.txt`, and the embedded inline lists, which declare no size and fall under condition 2 like any other unreadable declaration."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. `kennzeichen_riegel` exits non-zero when a named characteristic list declares a size and yields fewer pieces than that size; the message names the probe, the line, the declared size and the number read. 2. A list whose size is not readable falls back to today's rule (the empty list is the finding) and the run stays green. 3. The program states, at the point of the count, why the number of marks equals the number of elements — adjacent literals merge into one mark, so `{\"a\" \"b\", \"c\"}` reads as two — and a self-test case holds that reading. 4. The bait stands in the program: a probe text whose list declares 3 and yields 2, expecting the report, and beside it the same list with all three, on which the bar stays silent. 5. No hard-coded count and no probe file name enters the program. 6. At HEAD the tree passes: no compile error and no failing assertion attributable to `kennzeichen_riegel.cpp`."
vermerk: "Proposed 2026-09-08 by the kernbauer out of the work on 0267. `dateien` identical to 0267's, so the planner serialises it by itself; the `haengt_an` is real all the same — `deklarierte_groesse` does not exist without 0267. Numbering: 0268 was the highest at the time of writing."
---

# A characteristic list that yields less than it carries

## The measurement

`0267` closed the gap for the **table**: a table declaring `N` and yielding fewer than `N`
entries now aborts. Its reader, `deklarierte_groesse`, works on any name whose assignment
`finde_zuweisungen` finds — it takes the position of the name and reads the last template
argument before it.

The same shape sits one level over, in the other list this program reads. A named
characteristic list is `constexpr std::array<const char*, 3> KENNZEICHEN_SUMME_DER_REGEL =
{...}` (`kern/test/schritt_probe.cpp:440`). Loses it one string, and:

- the entry is not empty, so `gleiche_ab`'s `leere_liste` finding does not fire
  (`kennzeichen_riegel.cpp`, `gleiche_ab`, the `e.kennzeichen.empty()` branch);
- `kennzeichen == 0` in `main` does not fire, because the other lists still deliver;
- the table is not short, so `0267`'s bar does not fire either — the entry is read, only
  thinner.

The run stays green with one assertion fewer than the corpus declares. That is the sentence
`0258`, `0263` and `0267` were each written against, one step over instead of one step down.

## Why it is not a copy of `0267`

Two things differ, and the second is the whole work.

**The unit counted is a string, not a brace group.** A table's entries are innermost brace
groups; a list's pieces are marks on the mask, collected by `stuecke_aus`.

**The count and the declaration can legitimately disagree, and only one reading makes them
agree.** `zerlege` merges adjacent literals, because the language does: `"a" "b"` is one
mark. The kernel writes its messages across lines, so `{"eine sehr lange " "Meldung", "b"}`
is a two-element array yielding two marks — correct — while a naive "one literal, one
element" rule would count three. The package has to state that reading at the point of the
count and hold it with a case. `0267` had no such question: a brace group is a brace group.

## Where the expected number comes from

From `deklarierte_groesse(maske, stelle_des_namens)`, unchanged. `finde_zuweisungen` already
returns the name position for the list lookup in `lies_verzeichnisse`; today only `.auf` is
used there, and `.name` is available at the same place.

## What is not in this package

The content of any probe, `kern/test/kennzeichen.hpp`, every `CMakeLists.txt`. The embedded
lists (`{"alpha", "beta"}` written inline in an entry) declare no size and stay outside —
they fall under condition 2 like any other unreadable declaration.
