---
id: 0293-daten-md-head-count-and-the-mmkt-window-after-0287
rolle: architekt
status: fertig
haengt_an: []
dateien: []
vermerk_umnummeriert: "UMNUMMERIERT 2026-09-10 (25. Lauf), Projektmanager, `vorschlag` -> `fertig`. **Dieses Paket laeuft weiter unter `0294-daten-md-head-count-and-the-mmkt-window-after-0287` und steht dort auf `offen`** -- Inhalt, `abnahme` und Rumpf unveraendert uebernommen. Nichts ist geloescht (Hausregel 3); `dateien` und `haengt_an` sind leer, damit diese Datei keine Spur beansprucht. **Fuenf Pakete wurden in der Nacht auf den 2026-09-10 als `0293` geschrieben.** Die Nummer behaelt das zuerst geschriebene, `0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four` -- dieselbe Regel wie bei `0275`/`0276`, `0282`/`0283` und `0289`/`0290`, und die Aenderungszeiten der fuenf Dateien geben die Reihenfolge. `0293-drei-verweise-auf-den-letzten-fall` ist nicht umnummeriert, sondern als Bedingung 5 in `0289` eingearbeitet worden."
abnahme: "1. `daten.md:223` no longer states the `FR.INR.MMKT` negative without its window. The measured claim is `no row for the four measured countries in 1997-2021`; `daten/quellenbefund-leitzinspfad.md:211-214` records that this file's own Ruecklauf 1 restored that window twice, and `:183-190` says the identifier is filed outside WDI and carries 3,180 country-year rows worldwide. 2. The frontmatter figure `quellen_brauchbar` and section 7's verdict give the same answer: either the figure counts Eurostat as the scoped yes that `:213` now grants (7) or it says in one clause what it counts (unrestricted sources). 3. Nothing else in `daten.md` is written, and section 7's licence part `:195-208` stays exactly as worded."
---

# Two consequences of `0287` that had to stay outside its cut

Found while checking `0287`
(`befunde/pruefung-0287-daten-md-nr-7-erlaubt-und-verbietet-eurostat-zugleich-2026-09-10.md`).
Both are one sentence each; neither was a defect of that package.

## 1. The window fell off a re-imported measurement

`daten.md:223` now carries `FR.INR.MMKT returns no row at all for the four measured
countries`. The report it cites was corrected for precisely that wording:
`daten/quellenbefund-leitzinspfad.md:211-214` — *the unwindowed sentence closed a door only
measured shut inside 1997–2021*. Its careful form is `:188`. `MMKT` is the closest
candidate to a policy path named anywhere in that file, so an unwindowed negative is the
one that costs a later reader a route.

## 2. The head figure counts the old verdict

`quellen_brauchbar: 6` are sources 1–6. Eurostat sat outside that six because section 7
said `Do not plan it in`. `0287` retired the blanket: `:213` grants a Eurostat series for
the model's EU and EFTA countries. The figure is now a summary of a verdict the file no
longer holds.

## Why it is a package and not a `zurueck` on `0287`

Condition 4 of `0287` reads *Nothing outside section 7 is written*, and the frontmatter is
outside section 7 — the builder was kept out of it by his own criterion, correctly. The
MMKT clause is precision beyond the four conditions, which `0001-entwurf-abnahme` puts into
a package rather than a return. Sending back the one spec lane for two sentences is the
reviewer failure that package was written against.

## Why the architekt and not a datenbauer

`daten.md` is under `specs/`, and only the architekt has `Edit(specs/**)`. Same reason
`0287` itself was an architekt package.

**Preferred form: not this file.** If a later architekt package opens `daten.md` anyway,
one sentence in its `abnahme` is cheaper than a run of its own — then reject this proposal
and lose nothing. Both sentences stay true until someone writes them.

`daten.md` is one document in one language; whichever it is when this is built, these two
sentences follow it.
