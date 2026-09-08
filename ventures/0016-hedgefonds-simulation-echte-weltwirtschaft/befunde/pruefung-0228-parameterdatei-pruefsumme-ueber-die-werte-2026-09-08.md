---
typ: pruefung
paket: 0228-parameterdatei-pruefsumme-ueber-die-werte
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: All five conditions run as named Greps/Reads against parameter.toml and technik.md; all four self-counts of the file re-measured today; the 51 key lines compared character for character against the messung-0105 snapshot.
befunde: 0
---

# 0228 — checked, five conditions, no finding

The passage now stands at `parameter.toml:297-319` (was :297-300, 4 lines → 23).

## The five conditions, with the call

1. **`Grep "ueber diese Datei"` over `parameter.toml` → no hit anywhere in the file.**
   Stronger: `Grep -i "pruefsumme|Dateitext|Text dieser Datei"` returns 7 lines, all
   inside :297-319. The old reading is stated nowhere else, not even as a paraphrase
   outside the passage.
2. **Values, `Runde(feld)`, T10b, German.** :297-302 — „ueber die *Werte* … ueber die
   `Runde(feld)`-Felder des Traegers `kern::werte::Konstanten` … Bindend ist T10b".
   The embedded quote *"the parameter checksum is a function of the values, not of the
   file text"* is verbatim `technik.md:1052-1053`. T10b is the heading at
   `technik.md:999`; the checksum sentence it binds to is :1045-1048.
3. **The self-checksum sentence survives and is re-hung**, :316-319, with „er haengt
   nicht an der alten Lesart -- unter der neuen gilt er unveraendert". Not deleted.
4. **The exclusion is named**, :310-315: `leitzins_start` and `durchgriff` are not in
   the sum. Checked against the spec, not taken on trust: `technik.md:1015-1017` puts
   both in the carrier, :1029/1032 makes them T23 constants rather than `Runde(feld)`
   keys, :1062-1066 states the weaker tie. The comment's claim about the T27 cross-
   reference is exact — `technik.md:1941` reads „formed over the values of the
   carrier", which does read as if they belonged in.
5. **No key line added, removed or changed.** Measured today, not inherited:
   `^[a-z_0-9]* *=.*PLATZHALTER` → **47**, `^[a-z_0-9]* *=.*FEST (T51)` → **4**, sum
   51 — exactly what :168 and :184 read, both untouched (they sit above the passage).
   Full line accounting: 1223 comment + 55 blank + 4 table headers + 51 key = **1333**,
   so no line of the file is unaccounted for.

## Two further probes the acceptance did not ask for

**The other two self-counts still hold** — a comment run can move a self-measurement
without touching a key (:185-188 says so itself). `` `[a-z_0-9]*`\*\*? `` with `-o` →
27 sites on 26 names, minus the two bold-print sites (:473, :941) → **25 marks on 25
distinct names**, matching :223 and :233-235. The new passage adds backticked names but
no mark, and its bold run at :310 closes *before* `leitzins_start`, so it does not trip
the bold-print trap the head describes at :236-244.

**The values themselves, first time since group D landed.** All 50 key lines of the
`messung-0105` snapshot match today's character for character and in the same order;
the only difference is `regulierung_last = 0  # PLATZHALTER` at :1018. Offsets are
constant (+107 from `stufenweite` through `innerjahresausschlag_faktor`, +231 across
the four instrument tables), which proves no line below :349 moved at all.

## Checked, not a finding

- **:306 „alles uebrige ist Kommentar"** is wide by 59 lines — 55 blank and 4
  `[table]` headers are neither key nor comment. The load-bearing claim (under four
  percent carries a value; 51/1333 = 3.8 %) is right, `specs/` is silent on comment
  wording, and re-opening the passage for one clause costs more than the imprecision.
- **A one-line gap in the arithmetic, and it points at the spec, not at this run.**
  `technik.md:1056` says the file is 1,315 lines; the head grew by 19 here, so today
  should read 1,334 and `Grep "^"` reads 1,333. I read the whole head (:1-334): every
  block is continuous, every separator present, every count-off adds up
  (10+12+12+4+12+1 = 51; 25 + 26 = 51). Nothing is missing. The residue is a foreign
  measurement I cannot reproduce without a shell — most likely an editor's line count,
  one above `Grep "^"`.

## Downstream, not this package's fault

`technik.md:1054-1060` now describes a `parameter.toml` that no longer exists and still
carries the architect's report *„the head of `parameter.toml` needs one line drawn
after"*, which 0228 discharged. Proposed as
`aufgaben/0230-technikmd-t10b-meldung-und-alte-lesart-nachziehen.md`. It is not covered
by 0226, whose scope is „references only … a claim that is wrong rather than a pointer
that is dead — you report … and do not touch".
