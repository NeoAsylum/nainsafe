---
typ: pruefung
paket: 0253-disr-je-land-identifikation-nachziehen
pruefer: daten-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Every DISR per-country statement in the three files read against the query behind it; the 62-line citation count in reihen.toml recounted; the 39-row line index and the cross-file line references spot-checked.
befunde: 1
---

# One of the three files keeps the framing the package retired in the other two

## Befund 1 — `quellenbefund-leitzinspfad.md:152`–`:153` still asserts the withdrawn per-country claim

**How to produce it, step by step:**

1. Read `:330`–`:332`, this package's own closing note: the framing that `DISR`
   „measures a different quantity per country" **„rested on the two instrument names and
   falls with them"**, so „whether the code measures the same quantity for the USA as for
   Brazil is now open rather than answered no."
2. Read `:152`–`:153` in the same file: „The known asymmetry … is not beaten: **`DISR`
   remains two concepts across two countries**".
3. Read enumeration row `:262`, which binds that sentence: „| 152–154 | … | **a summary**
   over `:134`–`:138`; no query of its own |". Then read `:134`: the USA cell and the BRA
   cell now carry the identical wording „a discount rate, not identified per country" —
   changed by this package. The summary's own stated warrant no longer carries it, and no
   other line in the file supplies one.
4. Compare the other two files, where the same claim was scoped: `reihen.toml:621` and
   `:1258` („Ob dieser Code je Land dieselbe Groesse misst, ist unbelegt"),
   `deckungsbefund-1997.md:203` and `:210` („ein Begriffsunterschied ist daraus nicht
   abgelesen"). Two of three files retracted it; the third asserts it.

**In scope.** The acceptance says „in the three files", not „at the three named sites",
and the package's own site table names the framing („`DISR` misst je Land eine andere
Groesse") as a target, not only the instrument names.

**Reachable inside both hard limits.** `:152` is in `quellenbefund`, not `reihen.toml`, so
the 62-line count is untouched; an edit inside the line adds no line, so all 39 enumeration
rows keep their references. Row `:262` wants the same edit and is itself in-line. This is
not a „report it and leave it" case — and it was not reported either.

## What I checked and how, where it passed

- **The three named sites are bound or scoped.** `:30` and `:31` and `:134` carry „a
  discount rate, not identified per country"; `reihen.toml:621` and `:1258` name the
  codelist, its date and package, and list both withdrawn attributions;
  `deckungsbefund-1997.md:213`–`:214` names the retired Selic denial as retracted.
- **62-count.** `Grep technik\.md|spiel\.md` over `reihen.toml` = **62 matching lines**,
  as required.
- **No number moved.** BRA 45,09 / 8,01 and the five USA values stand at
  `deckungsbefund-1997.md:209`, consistent with `reihen.toml:1269` and `quellenbefund:334`.
- **Line index intact.** Enumeration `:229`–`:267` = 39 rows. Landed on `:9`, `:51`–`:52`,
  `:56`, `:59`–`:61`, `:91`, `:134`–`:138`, `:140`–`:150`, `:173`–`:176`: each says what its
  row says. The new reference `:294` carries „The interest rate charged by central banks on
  loans to commercial banks." Cross-file: `reihen.toml:1294`, `:1295`, `:1296`, `:1303`,
  `:1308`–`:1313` land as cited from `quellenbefund:53`–`:60`, so no TOML line shifted.
- **TOML legality.** `:621` is a `'''` literal, embedded `"` legal; `:1258` is a basic
  string and carries no `"`.
- **No new source.** Only the 2026-09-08 codelist retrieval already in the file.
- **Same-claim sweep over `daten/` only.** The live residue is `:152`; the
  `zwischenstaende/.neu*.tmp` hits are package `0045`'s quarantine and stale by design.

Not a finding, so it does not block: `:314` says in the present tense that
`deckungsbefund-1997.md:206` „still carries the retired Brazilian denial in full", which
this package made false. It is the `0252` record and its next sentence names `0253`.

**No package proposed.** The defect is inside this package's own `dateien` and its own
acceptance criterion; it belongs in the Ruecklauf, not in a new package.
