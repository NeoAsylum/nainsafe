---
typ: pruefung
paket: 0291-wie-die-vierzig-platzhalter-zu-ihren-werten-kommen
pruefer: entwurf-pruefer
datum: 2026-09-10
urteil: geprueft
kriterium_geprueft: "All six conditions checked against the new section `spiel.md:3299-3493`; the forty lines re-measured in `parameter.toml`, every key name matched, every cited cost figure traced to its source line."
befunde: 2
---

# 0291 — geprueft, 2 findings beyond the criterion

Section `Wie die vierzig Platzhalter zu ihren Werten kommen`, `spiel.md:3299-3493`.

## How each condition was checked

**1 — routes.** Table `:3320-3326`: five routes, each with what it needs, who walks it,
where it writes. Weg 5 needs a run and names no role — it names the gate, which is what
conditions 3 and 4 allow.

**2 — forty assignments.** `Grep -n 'Kalibriert:'` over `parameter.toml` at HEAD gives
exactly the forty lines of the criterion, no more, no less. Laid the table `:3363-3404`
against my own output line by line: all forty present, no duplicate, one route each. Key
names spot-checked against the definition line under each mark (`stufenweite` 349,
`stufen_max` 361, … `regulierung_last` 1018, three `schrittweite` at 1108/1131/1148) —
all forty correct. Balance recount: Weg 1 five, 2 six, 3 three, 4 six, 5b twenty = 40, and
the five gate groups `:3438-3442` hold those same twenty with no overlap.

**3 — the self-player.** `:3306-3312`, and all three of its citations verified at HEAD:
`"Bash"` is `agents/lauf.py:60` inside `NIE`, deny-beats-allow is `:44`, `selbstspieler`
is `baulauf.py:61` in `PRUEFROLLEN`, `0157` carries `status: blockiert`. No key in the
table is assigned to it, and the word `Gate` stands at `:3311`.

**4 — executable today.** `:3419-3426`: `datenkurator` → `daten.md` (three keys),
`datenbauer` → manifest (six), `kernbauer` → `parameter.toml` (eleven). `datenbauer.md:13`
does carry `Edit(ventures/**)` as cited.

**5 — no invented number.** Every figure traced: `9.759.420`, `9,54 Milliarden`,
`26,5`/`3,3` hours, `63.200`, `768.600` and the `20` world steps of a backtest all stand
in *Was der Architekt neu rechnen muss* at `:3618-3635`, quoted correctly — including that
`9,54` is `1.000 × 9.539.200` (three Maße), not `1.000 ×` the night-run total. `5.001`,
`R = 20`, `1,4` grid points (`1000^(1/20) = 1,41`) are arithmetic. No outside-world claim
without a source; the four unprocured anchors are marked unchecked at `:3483-3487`.

**6 — nothing outside.** `parameter.toml` still carries all forty marks unchanged, and the
role's tools (`spielentwerfer.md:13-15`) cannot reach it. Sections before the insertion
still start at their pre-build lines (`Wie die vier Masse berechnet werden` 2496,
`Offene Entwurfsfragen` 3096-3298), so no line was added or removed ahead of `:3299`.

## Finding 1 — „5a ist leer" is contradicted by `parameter.toml` itself

`:3355` claims that of the forty „wirken dort nur `zustimmung_elastizitaet` und
`zustimmung_wechselschwelle`", and concludes `:3358` „Der billigste Lauf der Fabrik kann
keinen der vierzig Schlüssel stellen."

`parameter.toml:708-710` says of `abschreibungsrate`: „zu gross -- die Wirtschaft
schrumpft in jeder Partie und **der Rueckvergleich (Mass 4)** scheitert an der
BIP-Sollreihe." And `:718-720` of `investitionsquote`: „das ist die Groesse, an der
**Mass 4 zuerst haengt**." Both act in the `weltlauf` and both have a target series
(GDP, `daten.md:396`). The section concedes this itself at `:3482` — „wandern 707 und 717
auf 5a" — which cannot be true if 5a is empty.

**Reproduce:** read `:3355`, then `parameter.toml:708-710` and `:718-720`, then `:3482`.

**No assignment moves.** Weg 3 precedes Weg 5, so 707 and 717 keep route 3 and the balance
stays 20/20. What is wrong is the sentence the section calls its sharpest result and hands
to the Geschäftsführer. Proposal `0293`.

## Finding 2 — the multi-line-mark sentence names three marks and misquotes one

`:3406-3409`: „Drei Marken decken je mehr als eine Zeile … 1102 und 1145 je eine
`schrittweite` neben zwei Grenzen, die die Marke ausdrücklich *nicht* trägt („die beiden
Grenzen sind gegen den Jahrgang zu prüfen")."

Two slips. **1125 is missing** — `[instrument.zoll]` has the identical shape (mark
`:1125`, keys `1131-1133`), so by the sentence's own criterion there are four such marks,
not three. **The quote belongs to 1102 alone**: `:1102-1103` carries it verbatim, while
`:1125` and `:1145` read only „Kalibriert: Selbstspieler (`schrittweite`)."

Neither touches condition 2 — the count of forty and the forty assignments are right, and
1125 is assigned (Weg 4). Per `0001-entwurf-abnahme`, precision beyond the conditions is a
package. Folded into `0293`.
