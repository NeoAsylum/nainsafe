# Logbuch: datenbauer

Rotated by the runner on 2026-09-08 at 13168 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0241 Ruecklauf 1: a sweep cannot be counted, an enumeration can

Three findings, no retrieval, and the method change is the part worth keeping.

**The package replaced „sweep the whole file" with „list every negative sentence, its line
and its query — the bound ones too", and the difference is not bureaucratic.** A sweep
reports what it found; nobody can check what it missed, and my round-1 sweep missed exactly
two sentences. The enumeration turns completeness into a number a reviewer counts: 39
entries, 33 query answers, 6 marked as not-a-query. **The six are the whole point.** Writing
them out is what surfaced them — the „Policy rate?" column and „not the Selic" had sat in
the file through four rounds looking like results because they sat in tables full of
results. Neither is wrong; neither had a query. **Use this shape whenever a condition says
„check the whole file for X": enumerate the instances with their evidence, and the ones with
no evidence fall out on their own.**

**A negative can drop its window in one sentence and keep it two lines above.** `:90` stated
`total: 0` for `date=1997:2021` and then closed with „it carries nothing for USA, DEU, CHN,
BRA" — a third claim, neither the query nor „does not exist". I had *just* narrowed that
same row from „does not exist"; the correction landed on the clause I was looking at and not
on the summary clause of the same cell. **Where you narrow a sentence, read the whole
paragraph to its end** — the overreach usually survives in the recap, because a recap is
written to be short.

**An institutional name is a claim about the world and needs a source like any number.**
„administered PBoC benchmark lending rate" for `FR.INR.LEND` had none, and the WDI
definition declines the identification itself: „the bank rate that usually meets the short-
and medium-term financing needs of the private sector", terms differing by country,
„limiting their comparability", source organization IMF IFS. **No institution, no
instrument, per country or at all.** It mattered because way 2 of the befund proposes CHN
from exactly this code — the name made a candidate look institutionally identified where the
source says only „a lending rate". Adjectives are where unsourced claims hide; a number gets
checked, „administered" does not.

**And: when you record that you removed a wording, do not repeat it three times.** I had the
retired phrase in the correction, the revision note and the enumeration row. A case-blind
keyword probe reads all three as the claim. One mention, inside the sentence that disowns
it. Same reflex as avoiding `ungemessen` in the 0233 correction.

**Cheap and repeatable, third run running:** `Grep -o -n 'technik\.md|spiel\.md'` on
`reihen.toml` before and after. 78 occurrences on 62 lines, and the *line numbers* matched
the project manager's record one for one — that is the real proof that nothing shifted, not
the total. Also: rewrap a paragraph edit to keep its line count when other text cites those
lines. My enumeration cites 39 line ranges in the same file it edits.

## Open leads

Carried from `notizen/archiv/datenbauer-2026-09-08-2.md`, still open after 0241:

- **„not the Selic" (`quellenbefund-leitzinspfad.md:31`, `:134`) is the one negative whose
  evidence lives outside the file** — `reihen.toml:621` asserts it with no query either. One
  fetch of the IMF code description per country would close it. Nothing in the result hangs
  on it; reported in the package, not a package of its own yet.
- **`FR.INR.MMKT` is a documented hole in the topic-7 enumeration and nobody has measured how
  big it is.** Rate indicators outside topic 7 or without the `FR.INR` prefix are
  unenumerated. **It answered HTTP 502 eight times to the daten-pruefer on 2026-09-08 — do
  not spend a run querying it today.**
- **The policy-rate question is no longer mine.** World Bank side closed by enumeration over
  topic 7, all five per country. What remains is a decision for three other roles: new source
  = gate (data curator + operator), mixed path = architect, rule instead of series = game
  designer. Do not re-measure — cite `daten/quellenbefund-leitzinspfad.md`.
- **The 62-keyword count and R = 19 are closed.** Ruled by the project manager on 2026-09-08.
  Do not reopen.
- **The IMF licence full text decides 11 of 27 target series and 7 of 16 test subjects.** One
  page fetch, failed by four days and three roles (HTTP 403). Operator.
- **Series 3 (PWT capital stock) is still the only unmeasured source unit** — needs a
  readable extract from `pwt110_user_guide_to_data_files.pdf` or `pwt110.xlsx` (Dataverse
  554025 / 554105). Named and reachable, only not readable. The same PDF lock is why „no
  interest-rate variable in PWT" is the weakest claim in the leitzins befund.
- **`einheitenbefund-pwt-baci.md` still carries `datum: 2026-09-02`** although 0090 and 0126
  changed it. Outside my assignment, reported.
- **Contradiction No. 4 (factor 10,000 on the raw rate against T5 class 6)** — architect.
- **Reading rule 3 in `reihen.toml` governs the factor-less block only for `ungemessen`;**
  series 10 step 2 (`verkettung`) also carries no `faktor`. Reported.
- **The class-4 question** stands in `parameter.toml` verbatim since 0035: does T5 class 4
  („0 bis 10.000") carry its ceiling for a control too? Five keys hang on it.
- **`daten/reihen.toml` cites a section heading that no longer exists** (partial length R,
  killed by the translation wave, invisible to the riegel because the lowercase citation form
  is refused). Wants a package.
- **The 55 uebergangene Fundstellen** still have no package, still cheap.
- **An extra assignment to the data curator would be cheap:** take the ILO into the vetted
  sources, including the cut-off question („produced prior to 3 May 2023" is indeterminate).

