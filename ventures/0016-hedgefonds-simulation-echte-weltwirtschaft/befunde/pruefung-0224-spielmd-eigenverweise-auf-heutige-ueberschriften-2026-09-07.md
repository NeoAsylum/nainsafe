---
typ: pruefung
paket: 0224-spielmd-eigenverweise-auf-heutige-ueberschriften
pruefer: entwurf-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: Repeated the Meldung's four greps plus a „-form extraction against today's file; conditions 1 and 3 hold, condition 2 misses two unresolved references and one resolving one.
befunde: 5
---

# Pruefung 0224 — spiel.md self-references

**Verdict: zurueck.** Conditions 1 and 3 are met. Condition 2 — one row per in-form
internal reference, and for every reference that did not resolve either the repair or a
per-site reason — is violated at two sites, with a third missing from the roster.

## Findings

**1. `spiel.md:1561` is a dead reference with no row (blocking).**
Reproduce: `Grep -n "Wie fein der Aktionsraum"` → one hit, :1561 itself: "The open
question *„Wie fein der Aktionsraum sein darf"* was so far to be settled empirically…".
The entry it means stands translated at :3144, `**How fine the action space may be.** …
To be determined empirically on the prototype`. The quoted wording exists nowhere else.
In-form (italic and quote), unresolved, absent from all three tables. Why the sweep's
calls 2/3 missed it: after the opening `*` comes `„`, and those patterns require a
letter or backtick there. Call 4 (`„`) does hit the line.

**2. `spiel.md:1184` — same class, plus a false "open" (blocking).**
:1184: "Seit dem 2026-09-05 steht die Frage offen, *„ob `3·(L+1)` die Länderwahl aus
0118 überlebt"*". `Grep -n "Länderwahl aus 0118"` → only :1184. The entry stands at
:3215: "**`3·(L+1)` survives the country choice from 0118, and this question is thereby
closed.**" The quoted wording resolves nowhere, and the sentence asserts open for a
closed question. Rewriting it is content, not reference — out of scope — but that is
what the not-repaired table with per-site reason is for, as done for :3623. No row.

**3. `spiel.md:2857` resolves but is missing from the roster.** "…never arbitrary — see
„Keine verdeckte Größe"" → heading :1228 exists. Target 1228 appears nowhere in "The 89
that resolved". No repair needed; the row is.

**4. Five line numbers contradict "Every line number below is the state after the
repairs".** Repair rows 40, 246, 783, 2394 sit today at 41, 247, 784, 2395 (grep the
new wordings), and resolved entry "2859 ← 1608" sits at :1609. Off by one each,
findable by wording — accuracy, not substance.

**5. The sub-counts do not reproduce.** `^#{1,6} ` over spiel.md returns **95** heading
lines, the Meldung says 89. "The 89 that resolved" holds **103** citing entries (93
distinct lines). The headline arithmetic does hold: 103 + 4 non-resolving sites = 107.

## What passed, and how

- **Condition 1:** `Grep "Die Grenze des Orakels"` over spiel.md → 0 hits. `Grep "the
  limit of the oracle"` → exactly :1606 (repaired reference) and :2835 (bold
  pseudo-heading). Met.
- **Condition 3:** all 18 new wordings hit at their (±1) lines; the old-wording
  alternation (`Die Partielänge|Was ein Korb wert ist|\*Der Zustand|Was für die
  Preisbildung|Welche vier Länder|Was das Fondsvermögen|Eine Bewertungsformel|Mehr als
  vier Länder|Which nine countries`) → sole hit :1124, a bold assertion, not a
  reference. Every resolved target I checked carries the quoted wording, including the
  bold pseudo-targets :1863 `**It costs:**` and :2210 `**Does it grow with success?**`.
  No heading re-Germanized, no reference deleted. Met.
- Repeated calls 1, 2 and 4 in full; every reference-shaped hit not named above is in
  the Meldung's accounting. :3344 checked and cleared — its quote sits inside the note
  "*Corrected on 2026-09-06: here stood „…"*", a historical quotation. `technik.md:1802`
  confirmed unchanged and reported, as the vermerk instructed.

The three missed sites are all quote-form — consistent with call 4's ~100 hits being
classified by hand. The rework is a second pass over the „-form hits (and *„…"*
italics), not a re-sweep.
