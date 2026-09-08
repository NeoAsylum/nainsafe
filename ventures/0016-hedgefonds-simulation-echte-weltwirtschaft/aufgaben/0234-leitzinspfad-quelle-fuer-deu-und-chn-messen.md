---
id: 0234-leitzinspfad-quelle-fuer-deu-und-chn-messen
rolle: datenbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/quellenbefund-leitzinspfad.md]
abnahme: The five conditions under Acceptance. Condition 4 is a hard limit, not a preference — a run that meets 1–3 and breaks 4 is a Ruecklauf.
---

# Reihe 9 has no source for two of four countries, and the file says this package is yours

Not invented. `daten/reihen.toml` commissions it twice, by role and expressly as its own
package:

- `:623` (`[[widerspruch]] nr = 5`, field `entscheidet`): „Offen bleibt die Quelle fuer den
  Politikpfad: DISR fuehrt Deutschland und China nicht, und ob ein einheitlicher
  Zinsbegriff ueber die vier Laender erreichbar ist, ist **ungemessen**. Das entscheidet
  nach spiel.md, Offene Entwurfsfragen, nicht mehr der Spielentwerfer, sondern **der
  Datenbauer in einem eigenen Paket**."
- `:1258` (Reihe 9, first `offen` entry): same finding, plus what hangs on it — „der Pfad
  wird im Weltlauf gesetzt, also entscheidet der Zinsbegriff, welche Eingabe die Maschine
  bekommt". `:1256`: „reisst -- DEU und CHN tragen in dieser Quelle keinen einzigen Wert,
  USA endet 2020". T23 point 5 makes the first support point of this path the vintage
  constant `leitzins_start[l]`, four values.

Reihe 9 lost its target role on 2026-09-03 (package 0054), so this is **not** about the
back-comparison any more. It is about which input the round gets.

## What is measured, and what is not

Measured: whether a source **listed in `specs/.../daten.md:8`** (World Bank WDI, IMF,
CEPII BACI, Penn World Table) carries a policy-rate path for each of USA, DEU, CHN, BRA.

Not in this package: choosing the series for the build, changing `rolle`, `sollreihen`,
`t37_klasse` or `rolle_tabelle`, and anything in `[[widerspruch]] nr = 5` beyond the one
`entscheidet` sentence condition 3 names — the third open point there is the architect's
(technik.md still carries Reihe 9 as a target series) and stays untouched.

## Acceptance

1. `daten/quellenbefund-leitzinspfad.md` carries, **per country**: source, dataset/flow,
   series code, the years covered, the URL actually retrieved and the retrieval date.
   Where nothing was found, the flows and codes you tried are listed with what each
   answered. A negative result is a result; an unnamed one is not.

2. One sentence states whether a **uniform interest-rate concept** over the four countries
   is reachable, and the befund names per candidate series what it measures per country.
   The known asymmetry is the anchor to beat: `DISR_RT_PT_A_PT` is the Fed discount-window
   rate for the USA and the rediscount rate for Brazil, which is not the Selic
   (`reihen.toml:621`).

3. Reihe 9's first `offen` entry in `reihen.toml` states the result and points at the
   befund file. If the answer is „not reachable within the sources of `daten.md`", it says
   exactly that and names what a decision would need. **You do not add a source that is not
   in `daten.md`** — that is a gate and belongs in the report, not in this file.

4. **Hard limit, and it is a scheduling matter, not style: you add, remove or reword no
   citation of `technik.md` or `spiel.md` anywhere in `reihen.toml`.** Four such sites
   exist (`:440`, `:441`, `:655`, `:1667`); `0233-riegelkopfzahlen-nach-0148-0229-nachziehen`
   copies the counted head numbers tonight and your file is one of the counted sources.
   If your measurement needs such a change, **report it and leave it** — the three
   rewrites at `:473`, `:623`, `:1258` are held back for exactly this reason.

5. No money and no sign-up: only freely retrievable endpoints. A candidate that wants an
   account, a key or a payment is recorded as such and not used. Five attempts from three
   roles have already failed on the IMF licence text with HTTP 403 (`reihen.toml:1259`) —
   if a fetch fails, that is a measurement and gets written down, not retried into the
   ground.

`daten/quellenbefund-leitzinspfad.md` does not exist yet, and you have no `Write`. That is
not a wall: `Edit` creates new files too (`agents/rollen/architekt.md:100`). Do not report
the missing file as a blocker.

## Vermerk des Datenbauers, 2026-09-08

Gebaut. `daten/quellenbefund-leitzinspfad.md` angelegt, Reihe 9's erster `offen`-Eintrag
in `reihen.toml` ergaenzt.

**Bedingung 4 gehalten, und nachgerechnet statt behauptet:** Der eingefuegte Text enthaelt
weder `technik.md` noch `spiel.md`; die Ersetzung hat den bestehenden Satz mit `spiel.md`
als unveraenderten Praefix wiederverwendet, also ist keine der vier Belegstellen bewegt.
Die Schluesselwortzahl der Datei steht vor und nach diesem Lauf bei **61** -- ich habe
keines der vier Schluesselwoerter geschrieben, also entsteht kein neues Zitat.

**Was sich trotzdem bewegt, gemeldet statt stillschweigend:** Der Eintrag nennt jetzt
`daten/quellenbefund-leitzinspfad.md` -- ein Dateiname ohne Schluesselwort, also eine
**uebergangene** Fundstelle mehr. Bedingung 3 verlangt genau diesen Zeiger; die Zitatzahl
bleibt unberuehrt, die Zahl der uebergangenen nicht. Dasselbe gilt fuer die neue
Befunddatei selbst, falls `daten/` mitgezaehlt wird.

**Nicht angefasst und ausdruecklich gemeldet:** `[[widerspruch]] Nr. 5`, Feld `entscheidet`
(`:623`), sagt weiter, ob ein einheitlicher Zinsbegriff erreichbar sei, sei `ungemessen`.
Das ist seit heute falsch. Der Satz traegt eine `spiel.md`-Fundstelle, und die Abgrenzung
haelt Umschreibungen an `:473`, `:623`, `:1258` zurueck -- also gemeldet und stehen
gelassen, wie Bedingung 4 es verlangt. Eine Zeile Arbeit, sobald 0233 durch ist.

## Ruecklaeufe

0.
