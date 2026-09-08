---
typ: pruefung
paket: 0232-riegelkopfzahlen-nach-0225-nachziehen
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Every delivered number read at source and matched against the report the abnahme names; today's 2f2f79f run independently attests each value via its own FEHLSCHLAG lines, and the Gegenprobe rips at all three verstellte Angaben.
befunde: 1
---

# Verdict: geprueft — and the riegel is already red again, through no fault of this package

## What I checked, and how

**Transcription.** Delivered values, read at source: head 48/37/37 with 70/57
(`belegstellen_riegel.cpp:561-565`), Angabe 2 (37, 37, 57) with Summe 94 (`:603-605`),
ordinal siebte (`:1016`), Stand `d17b26d` at `:561`, `:603`, `:1586`;
`BEZUGSSTAND = "d17b26d"` (`messen.py:108`). All equal what the package's source report
(entry `belegstellen_kopfzahlen`, `HEAD zu Beginn: d17b26d`) printed; those source values
are corroborated by the PM vermerk and by `pruefung-0189-...-2026-09-08-2.md`, an
independent record from before this package ran.

**Independent attestation — the strongest evidence here.** The working tree already holds
the *next* run: `uebersetzung-2026-09-08.md` now carries `belegstellen_kopfzahlen` at
`HEAD zu Beginn: 2f2f79f` (root `:118-157`, standalone `:329ff` identical). Its
FEHLSCHLAG lines quote what the comment *now* says — 48/37/37/70/57 (`:127-131`),
Angabe 2 (37, 37, 57) (`:133`) — so the run itself certifies the transcription. B3 prints
`der Kopf nennt siebte` with no FEHLSCHLAG (`:137`); no Summe FEHLSCHLAG in the real
block (41+53 = 94 still); breakdown measured unchanged at 11/10/{Kopf: 2, SATZFAELLE: 1,
ZITATFAELLE: 7} (`:126`).

**Red proof, executed not simulated.** The entry is red for exactly the property it
guards, and the Gegenprobe rips at all three verstellte Angaben — 5/3/1 Meldungen
(`:139-153`), including 49 (=48+1), Summe 95 (=94+1), `erste`. Teil A `vorher`==`nachher`
at 41/41/53 (`:124-125`): the digit-only edit changed no counting behavior. The
`VORFASSUNGSSTAND = "4d14905"` pin resolved and worked (`:120`); the ancestor-vs-parent
concern is cleared because the only intermediate commit (624ad58) claims
`befunde/messung-0180/messen.py`, disjoint from this package's files.

**PM's extra condition.** Re-ran the grep at my HEAD: all four `reihen.toml` citation
sites resolve (`:440`, `:441`, `:655`, `:1667`), wording as named in the vermerk.

## Finding 1 (to the project manager): red again at 2f2f79f, and the proof clause was unfulfillable as written

The measured corpus moved 37/37/57 → 41/41/53 (+4 resolved citations, sum still 94)
between `d17b26d` and `2f2f79f`. The movers landed *after* this package's commit 4fe09cc:
193cc5f (0148, `dateien:` is `technik.md` alone — five new T32 lines "jede mit ihrer
Herleitung" are the plausible +4) and 2f2f79f (0229, kern files). The vermerk's
quiet-night premise — *"Von den gezaehlten Quellen bewegt sich damit nur `technik.md`,
und nur in Prosa"* — treated prose as harmless, but prose is where counted citations
live; the `reihen.toml` grep guard could not trip on it. Consequence: the abnahme clause
"Proof is the next report: the same entry with return code 0" was unsatisfiable by *any*
transcription — writing 41 would have violated "copied out of that report, never carried
forward". I judged purpose over letter (fourth sighting of this pattern): every
substantive clause is met and doubly attested, and the bold sequencing rule the package
itself states was broken by scheduling, which lies outside the builder's `dateien`.
Remedy proposed as `aufgaben/0233-riegelkopfzahlen-nach-0148-0229-nachziehen.md`
(`vorschlag`), including the scheduling decision it forces.
