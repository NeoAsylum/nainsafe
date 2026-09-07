---
typ: pruefung
paket: 0217-parametertoml-kopf-quellenliste
pruefer: daten-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Variant (a) taken -- head line 46 restricts the list to package 0009 in words; all four counting calls, 47/4/51 and the 25 marks re-measured unchanged; head/0105 line accounting shows 0217 added exactly four lines and touched nothing else.
befunde: 0
---

# The source list carries its restriction to 0009 in words, and nothing else moved

Commit `d07c4e9`, `datenbauer: 0217-parametertoml-kopf-quellenliste (3 Dateien)`.

## Which variant, and where it stands

**(a).** `parameter.toml` lines 46–49:

    # Quellen: die von Paket 0009, und wie Paketnummer, Stand und
    # Fassungszahl darueber nicht fortgeschrieben -- kein Verzeichnis der
    # Tabellen, die diese Datei heute zitiert. Das steht bei den
    # Schluesseln, die sie zitieren, und nur dort.

The restriction to 0009 is stated, and the freeze is stated by naming the three items
above it that the head already declares frozen (line 4). The twelve-table list survives
below at 50–53 as 0009's record. Acceptance under (a) met.

## The mechanical probe

`Grep -o 'T[0-9]+'` over the file, deduplicated by reading: 21 distinct tables cited,
12 named in the head list, **nine cited and not named** — T4, T7, T9, T18, T26, T28,
T30, T33, T48. Same set as in the 0203 round-2 finding. The gap is unchanged and is now
**declared** instead of silent, which is what (a) asks for. T46 stands in the list and is
cited nowhere else in the file — correct under (a), where the list is a record and not an
index.

## Nothing else moved

| Probe | Required | Measured |
|---|---|---|
| `` `[a-z_0-9]*`\* `` occurrences | 27 | 27 (lines 454…922) |
| …distinct names | 26 | 26 |
| …minus the two bold `**` hits (454 `regulierung_start`, 922 `regulierung_last`) | 25 | 25 |
| …distinct | 25 | 25 |
| `^[a-z_0-9]* *=.*PLATZHALTER` | 47 | 47 |
| `^[a-z_0-9]* *=.*FEST \(T51\)` | 4 | 4 |
| `^[a-z_0-9]+ *=` leaf lines | 51 | 51 |
| package numbers in head (lines 1–71) | none newer than 0035 | 0009, 0035 only |

The four calls at lines 1187/1194/1198/1200 still yield 25, 26, 25, 27. The new text
contains no backtick, so it cannot enter any of the four patterns.

**Line accounting against the frozen tree**
(`befunde/messung-0105/baum/.../parameter.toml`): its head is lines 1–58, today's is
1–70, difference +12. Lines 4–11 (0203's "Dieser Kopf haelt die Entstehung fest",
8 lines) plus lines 46–49 (0217, 4 lines) = 12, and every other head line matches
character for character. Old line 38 `# Quellen: specs/…` became line 50
`#          specs/…` — the ten-space indent puts `specs` in column 12 exactly as before,
so it aligns with its own continuation lines 51–53, which are untouched. 0217 therefore
added four lines and changed one label. Nothing else in the head.

No `0217` anywhere in the file: the builder recorded his package where the head forbids
it and nowhere else.

## Checked, not a finding

`und nur dort` is slightly wide: T33 and T28 are cited only in "WAS HIER BEWUSST NICHT
STEHT" (lines 294, 306), a section about keys that deliberately do not exist, not at a
key. The sentence's job — do not extend this list — is unaffected, `specs/` is silent on
comment wording, and re-opening a head just declared frozen costs more than the four
words are worth. No proposal.

Not looked at: leaf values against 0105 beyond the 51-line count and the mark set (the
frozen tree predates group D, so it is not a decisive reference for values), and the
spiel.md half of the "Quellen:" line, which (a) leaves in place.
