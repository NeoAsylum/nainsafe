---
typ: pruefung
paket: 0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four
pruefer: entwurf-pruefer
datum: 2026-09-11
urteil: geprueft
kriterium_geprueft: All six conditions read against the delivered section `spiel.md:3299-3536` and against every line it cites in `parameter.toml`, `daten.md` and the two `weltlauf` sections; each quote compared character by character, each count recounted.
befunde: 0
---

# 0293 — all six hold

Section today `spiel.md:3299-3536` (index of 2026-09-11), heading unchanged.

**1 — the paragraph.** `:3354-3361` now says **five** of the forty act in the `weltlauf`,
not two. The two counter-quotes match character for character: `parameter.toml:708-710`
reads „die Wirtschaft schrumpft in jeder Partie und der Rueckvergleich (Mass 4) scheitert
an der BIP-Sollreihe", `:718-720` reads „das ist die Groesse, an der Mass 4 zuerst
haengt" — both stand verbatim at `:3369` and `:3371`. I checked the new claim against the
spec too, not only against the toml: `spiel.md:2734-2738` („The fund subsystem does not
run … of step 5 only approval and change of government run") and `:2446-2454` carry it.
Counterforce 2 is the real-income/approval force (`:2236`), channel 1 is
investment/capital stock (`:619`, `:2039`, `:2257`) — so the mixed numbering at
`:3360-3361` is right, not a slip. Grepped `specs/` for the old wording („wirken dort
nur", „keinen der vierzig"): no residue.

**2 — 5a carries a decision.** `:3375-3378`: two-axis fit of 707 and 717 against the
`L_R` GDP paths, level, MAPE ≤ 20 %, 21 support points. All three exist as written —
`:2773` is the level/MAPE ≤ 20 % row, `:2755` the 21 support points, `:3559` `L_R`. No
„could also". Arithmetic recomputed: 10.000 × 20 = 200.000; 200.000 / 9.759.420 = 2,05 %;
√10.000 = 100; 1000^(1/20) = 1,41. The 20 world steps per backtest stand at `:3661`.

**3 — the fallback agrees.** `:3523-3525`: 707/717 to 5a, 758 to 5b, tally 17 to 23, of
which 21 night and 2 backtest. Recounted: 20 − 3 = 17, 20 + 1 = 21, 21 + 2 = 23. Agrees
with `:3380-3384` („at worst twenty-one, never twenty-two") and with `:3467-3468`. All
nine „5a" occurrences in `spiel.md` read; none still calls it empty.

**4 — no assignment changed.** `Grep ^# Kalibriert: Selbstspieler` on `parameter.toml`
returns exactly 40 lines, and their numbers are the 40 rows of `:3390-3429`, one for one.
Tally recounted from the rows: path 1 five, 2 six, 3 three, 4 six = 20; 5b rows counted =
20. The group table `:3478-3482` holds all twenty 5b keys, each once. 707 and 717 on 3,
742 on 5b, 758 on 3.

**5 — four marks, not three.** Blocks read: 518 above 524-526, 1102 above 1108-1110, 1125
above 1131-1133, 1145 above 1148-1150. Only `:1102-1103` carries „die beiden Grenzen sind
gegen den Jahrgang zu pruefen, nicht zu suchen"; 1125 and 1145 read „Kalibriert:
Selbstspieler (`schrittweite`)" and stop. The three substitute citations are verbatim:
`instrument_min = 0  # FEST (T51)` at 1132, the failure clause at 1128-1129, the budget
block head at 1136-1138. `[instrument.regulierung]` carries no mark, and `instrument_max`
is called a second copy of `regulierung_stufen` at 1160-1161 — that is what stands there.

**6 — nothing outside `spiel.md`.** Every quoted `parameter.toml` line still reads as the
quote, which is the proof; and the role could not have written it anyway —
`agents/rollen/spielentwerfer.md:13-15` grants `Edit(specs/**)`,
`Edit(ventures/**/aufgaben/**)`, `Edit(notizen/spielentwerfer.md)`, nothing else under
`ventures/`.

## What I searched for and did not find

A second place in `specs/` still calling 5a empty; a fifth mark standing above more than
one key line; an assignment moved between paths; a broken tally; a 5b key missing from the
group table. None of the five.

## Not a finding — for the project manager

`parameter.toml:718-720` says the two capital-stock keys decide whether the model grows
„ueber **25** Runden". R is 20 (`spiel.md:11`, `:141`, `:2501`); 25 is the support-point
count of the retired 1997-2021 vintage, whose R was 24 (`:3638`). Outside this package's
`dateien` and outside its six conditions, so no finding — but it sits in the very comment
block condition 1 turns on. Proposal **`0310`** files it together with the package
`spiel.md:3531-3535` asks for and which does not exist.
