---
typ: pruefung
paket: 0203-parametertoml-selbstzaehlende-fassungsangaben
pruefer: daten-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: (d) by Grep for `0[0-9]{3}` over the head block, (a)(b) by reading the two places, (c) by re-running the four counting calls and comparing all 51 leaf lines against the frozen tree of messung-0105
befunde: 1
---

# 0203 round 2 — the roll-call is gone, one line was removed, nothing else moved

## (d), the binding part

Head block = lines 1–66, ending at the divider before "WAS DIESE DATEI IST". One
`Grep` for `0[0-9]{3}` over the file, hits inside the block:

| line | hit | older than 0203? |
|---|---|---|
| 6, 12, 14 | `0009` | yes, the origin package |
| 37, 51 | `0035` | yes, stood there before round 1 |
| 46, 47 | `0016` | not a package — the venture number in two paths |

No `0150`, `0153`, `0175`, `0193`, `0200`. The roll-call is gone; lines 7–8 now carry
the rule alone: "Was spaetere Pakete geaendert haben, steht da, wo sie es geaendert
haben."

**On the boundary:** the wide reading (whole leading comment up to the first key at 326)
makes (d) unsatisfiable — `0150` (166), `0175` (225), `0193` (263) sit in comment text
that (c) freezes. So the block ends at the divider, and the project manager's own
operationalisation ("one `Grep` over the head block") is what I ran.

## (c) Nothing else moved — and the shift proves it

Every anchor below the head is **exactly −1** against my round-1 check: `0035` 38→37 and
52→51, `0175` 226→225, `0193` 264→263, the `**` marks 451→450 and 919→918, the call block
1184–1197→1183–1196, `regulierung_last` 996→995, 0200's citation 809→808. A uniform −1
with no anchor at −2 or 0 means one line was removed in the head and no line was inserted
or deleted anywhere else.

Counts re-measured on today's file:

| call in the file (line) | stated | measured |
|---|---|---|
| `\*\*\?` + `grep -v '\*\*$'` + `sort -u` (228, 1183) | 25 | 25 |
| `\*` + `sort -u` (1190) | 26 | 26 |
| `\*\*\?` + `grep -v '\*\*$'` (262, 1194) | 25 | 25 |
| `\*` (1196) | 27 | 27 |

27 match sites, two ending in `**` (450 `regulierung_start`, 918 `regulierung_last`), the
other 25 pairwise distinct. `^[a-z_0-9]* *=.*PLATZHALTER` → 47, `^[a-z_0-9]* *=.*FEST
(T51)` → 4, `^[a-z_0-9]* *=` → 51. All 51 leaf lines — key, value and mark — are
character-identical to `befunde/messung-0105/baum/.../parameter.toml`, which holds the
same 50 in the same order plus nothing; today's file adds only `regulierung_last = 0  #
PLATZHALTER`.

## (a) and (b)

(a) The `sort -u` justification names no version count; lines 248–259 say why and put
`git log --oneline -- <pfad> | wc -l` outside the file. (b) Line 4 stands unchanged.

## Finding 1 — the head still carries a list that later packages had to extend, and one did not

Lines 46–49, **not** written by this package and **not** covered by its criterion:

    Quellen: specs/0016-.../technik.md T5, T27, T45, T46, T47, T50, T51,
             T23 Punkt 5, T15, T16, T6, T40; ...

`Grep -o 'T[0-9]+'` over the file gives nine cited technik.md tables the list does not
name: T4 (132, 139), T7 (953), T9 (133, 1001), T18 (493, 1011), T26 (1091), T28 (302),
T30 (379, 825), T33 (290), T48 (879, 883, 913, 920, 934, 935).

The sharpest is **T48**: line 879 says `regulierung_last` "ist ein Schluessel *aus* T27 --
technik.md T48 sagt woertlich, er sei 'der Parameterschluessel aus T27'". T48 is the
source that introduced group D through package 0150 on 2026-09-06 — a source added to the
file after the head list was written and never entered there.

**Why this is not a `zurueck`.** The list is character-identical to the frozen 0105 tree
(there at lines 38–41) and was already incomplete then — T4, T9, T18, T26, T28, T30, T33
were cited in the body at 0105 and missing from the list. It predates round 1, it is not a
count of the file's versions or editions, and the vermerk said "Mehr nicht". A rerun
against *this* order could not produce a better file. It goes to package **0217**.

**Where the acceptance overreaches:** (d)'s second clause — "carries no list that a future
package touching `parameter.toml` would have to extend" — is false of the head as a
universal, and was false before this package existed. Read as the generalisation of the
package-number clause it describes, which is how its own `Grep` operationalises it, (d)
holds.
