---
id: 0223-realeinkommen-abschnitt-zwei-textstellen
rolle: spielentwerfer
status: fertig
haengt_an: []
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, body and acceptance unchanged. Both conditions are checkable with `Grep` and `Read`, neither needs a shell, and each names the call rather than the goal: condition 1 is a grep that either hits technik.md's T38 paragraph or does not, condition 2 names the counterexample (9.990 → +50 → −50 → 9.950) that the repaired sentence must no longer satisfy. That is the narrow form, and I am not widening it. || ONE CORRECTION TO YOUR NOTE FOR ME, and it is in your favour: `specs/.../spiel.md` is NO LONGER in `ops/reserviert.txt`. The translation run gave it back after five days; the file now holds only `technik.md` and `zielbild.md`. There is nothing to serialise and nothing to wait for -- `0198` went to `fertig` in this run and was the only other package on the file, so you are schedulable tonight. Do not carry that sentence forward into your Meldung. || THE FOUR QUESTIONS, CHECKED. `spielentwerfer` is a real role, stands in `baulauf.py:BAUROLLEN` and is reviewed by the `entwurf-pruefer` -- the same pairing that produced you. `haengt_an` is rightly empty. No other open package lists `spiel.md`. || YOU ARE ONE OF ONLY TWO FREE LANES TODAY. Fifteen of eighteen open packages sit on `technik.md` and cannot move; the other free lane is `0222`, and its file list does not touch yours. Both fixes are one sentence each, so keep the run that size -- this is a repair of two sentences in *Das Realeinkommen in Gegenkraft 2*, not a revision of the section. The rule itself passed review and does not change. || WRITE GERMAN OR ENGLISH BY THE SITE, NOT BY THIS PACKAGE. `spiel.md` is a German document under `CLAUDE.md`, but the section 0198 wrote is English and `technik.md:1379` reads English since the §4 translation. Condition 1 is therefore an English quote of an English paragraph -- quoting is not translating, and the quote follows the document you cite, not the one you write in."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: (1) The T38 quote at spiel.md:2427 carries the wording that stands in technik.md today, so a grep for the quoted words hits technik.md's T38 paragraph. (2) The cancellation sentence at spiel.md:2372-2379 carries its bounds premise (approval inside 0…10.000 at both ends), so the counterexample 9.990 → +50 → −50 → 9.950 no longer satisfies the sentence's stated condition.
---

# Two one-line fixes in *Das Realeinkommen in Gegenkraft 2*

Proposed 2026-09-07 by the entwurf-pruefer, out of
`befunde/pruefung-0198-realeinkommen-als-rechenvorschrift-2026-09-07.md` (findings 1
and 2). Both sites, both fixes:

1. **spiel.md:2427** quotes T38 as „nur Zustimmung und Regierungswechsel"; technik.md
   is English there since the §4 translation ("of step 5 only approval and change of
   government run", technik.md:1379). Update the quote to today's wording — quoting an
   English document in English per house rule.
2. **spiel.md:2372-2379** claims up-and-back cancels "exactly if the quantity and
   `bip` are unchanged". At a clamp it does not: start 9.990, `zustimmung_elastizitaet`
   10.000, budget step down then up → 10.000, then 9.950. Add the missing premise
   (approval inside 0…10.000 at both ends). The rule is untouched; only the sentence a
   test builder would encode is.

## Why an own package

- 0198 is `gebaut` and closes with its pruefung; the entwurf-pruefer repairs nothing.
- No open package lists `spiel.md`: the architect's 0198 pickup works in `technik.md`,
  and the translation lane visits German sections only — this quote sits in a new
  English section it will never touch.
- 0222 is the same defect class but its scope is the `belegstellen_riegel` scan set
  (code and toml); spiel.md prose is outside it.

## Result 2026-09-07, spielentwerfer — both fixed

1. **behoben.** spiel.md:2426-2427 now reads: `technik.md` T38 carries `zustimmung` in the
   mask and says: „of step 5 only approval and change of government run"
   (technik.md:1379). The quoted words are a contiguous substring of technik.md:1379 and
   stand on one line in both files, so the grep hits.
2. **behoben.** spiel.md:2372ff now carries the premise: cancel exactly if quantity and
   `bip` are unchanged **and neither round is clamped, that is: the unclamped sum inside
   the update lies within `0…10.000` both times**. The counterexample fails it — the first
   unclamped sum is 9.990+50 = 10.040, outside the range — and it stands in the text with
   its two numbers, because that is what a test builder needs to not re-derive it.

The rule, the four formulas and every count are untouched; two sentences changed.

## Note for the PM

`spiel.md` is held by the translation lane in `ops/reserviert.txt` — same mechanical
serialization as 0198 had; schedules itself when the line falls.

## `fertig` 2026-09-07, project manager

`befunde/pruefung-0223-realeinkommen-abschnitt-zwei-textstellen-2026-09-07.md`,
`urteil: geprueft`, 0 findings. Both conditions checked by the named calls: the T38
quote hits `technik.md:1379` inside the T38 block (heading 1341, next rule 1385), and
the repaired sentence carries the clamp premise that the counterexample 9.990 → +50 →
−50 → 9.950 fails. Rule, four formulas and read-access numbers untouched — two
sentences changed, which is the size I asked for.
