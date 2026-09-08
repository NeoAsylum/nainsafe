---
id: 0237-der-nenner-der-zustimmungsregel
rolle: kernbauer
status: gebaut
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, im Zuschnitt und im Wortlaut unveraendert, **aber ohne die vorgeschlagene Abhaengigkeit.** `0197` ist in diesem Lauf `fertig` geworden; eine erfuellte `haengt_an` ist Dokumentation und plant nichts ein. Vorgeschlagen vom kern-pruefer aus den Befunden 1-3 der zweiten Pruefung von 0197. || DIE VIER FRAGEN, GEPRUEFT. **Rolle** `kernbauer`, in `baulauf.py:BAUROLLEN`, geprueft vom `kern-pruefer` -- dieselbe Paarung, die 0229 und 0197 getragen hat. **Abnahme** pruefbar und ohne Schale: Bedingung 3 misst die neue Schranke von beiden Seiten, das ist die Form, an der 0148 und 0231 gescheitert waeren, wenn sie sie nicht gehabt haetten. **Vorleistung** keine mehr. **Dateien** treffen `0233-feldzaehler` auf `schritt_probe.cpp` -- das ist geloest, siehe unten. || **WARUM DU HEUTE NACHT LAEUFST UND NICHT 0233-feldzaehler:** Dein Befund sagt, dass jede Runde in `schritt_probe` heute durch ein **negatives** BIP teilt und gruen bleibt, weil der Zaehler null ist (`bip(US) = -10.000`, `CN`/`BR` `-20.000`, `DE` `-10.000`, von dir aus `musterwert` und den Laenderbasen hergeleitet). Damit misst die Probe, die 0197 gerade abgenommen hat, einen Zustand, den `spiel.md:2409` verbietet. Das ist keine Kommentarfrage, sondern der Boden, auf dem die naechsten fuenf Schritte gebaut werden. 0233-feldzaehler ist Kommentargenauigkeit plus ein Probentyp und blockiert nichts. **Deshalb haengt er jetzt an dir**, und deine Bahn ist frei. || **BEDINGUNG 2 IST DIE, DIE DICH TEUER MACHEN KANN, und ich lasse sie ausdruecklich stehen:** Sie aendert die Startzustaende, auf denen die bestehenden Zustimmungsproben laufen. Faellt dabei eine bestehende Zusicherung, ist das ein **Befund und kein Ruecklauf** -- schreib ihn hin und lass die Probe rot, statt sie passend zu machen. Was du nicht darfst: die Klemmprobe `probe_zustimmung_klemmt_statt_vortrag` entschaerfen. Ihr Startwert `I64_MAX` bricht nach deinem eigenen Befund bei erstem nicht-nullem `hub` in `festkomma::plus` ab -- wenn das eintritt, ist es dieselbe Sorte Befund. || **ZUR MULTIPLIZIERENDEN HAELFTE** (dein zweiter Mitnahmepunkt): Der Wortlaut deines Vorschlags gilt -- „if condition 2 lets you move one instrument level from inside the probe without touching step 3, that answer is cheap; if it does not, **say so and leave it**\". Ich nehme das als Bedingung mit dieser Alternative an; `kern/src/schritt.cpp` Schritt 3 anzufassen ist ausdruecklich **nicht** in deinem Auftrag. **`kern/include/kern/schritt.hpp` steht nicht in deiner Dateiliste** und wird es nicht -- der Kopf gehoert 0233-feldzaehler; findest du dort einen falschen Satz, melde ihn."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: "The three conditions under Acceptance. Condition 1 is the load-bearing one; conditions 2 and 3 are what make it measurable."
---

# The approval rule divides by `bip(l)` and does not look at its sign

Proposed by the Kern-Pruefer out of
`befunde/pruefung-0197-schritt-5-reaktion-rechnet-die-zustimmung-2026-09-08-2.md`,
findings 1–3. `0197` is `geprueft`; this is what the check found beside its criterion.

## Why a package of its own

Not part of `0197`: its acceptance is met, and its four conditions say nothing about the
denominator — a reviewer may not raise a criterion after the fact. Not part of `0236`
either: that one asks *which state* the quantities are read from (`lies_neu` against
`Zustand`), this one asks *what happens when the quantity that comes back is negative*.
Both answers are needed and neither implies the other.

It claims the same two files as `0197` and therefore cannot run beside it. That is the
whole reason it is a package and not a repair inside the review.

## The defect

`kern/src/schritt.cpp:615-616`:

```
return festkomma::mal_geteilt(festkomma::minus(0, last), ZEHNTAUSENDSTEL,
                              werte::bip(rundengrenze, land));
```

`festkomma.hpp:155-158` aborts on `c == 0` and on nothing else. `werte.cpp:691-700` sums
three addresses and returns the sum, whatever its sign. `spiel.md:2409` names
`bip(l) > 0` as the denominator condition of exactly this rule.

A negative `bip(l)` therefore turns the rule around without a word: a policy burden
(`politiklast > 0`) raises approval. The same codebase has already written the argument
down for the identical shape — `werte.cpp:596-606` guards `wechselkurs < 1` because
„der **negative** Nenner ist der gefaehrlichere Fall, weil er das Vorzeichen jeder
Bewertung drehte, ohne dass irgendetwas abbraeche". Take that sentence and put it here.

**It is not hypothetical, it is the current probe.** `musterwert(p) = muster[p % 8]` with
`muster[0] = 0` and `muster[4] = -10.000`; `stelle_sektorgroesse` puts `Wertschoepfung`
at country base `+0, +4, +8`; the bases are `0, 44, 88, 132`. Hence
`bip(US) = -10.000`, `bip(CN) = -20.000`, `bip(DE) = -10.000`, `bip(BR) = -20.000`.
Every round in `schritt_probe` today divides by a negative GDP and stays green, because
`schritt_3_politik` carries forward and the numerator is zero.

## Acceptance

1. `realeinkommenshub` aborts before dividing when `bip(l) < 1`, with a message that
   names the rule and the country and not only `mal_geteilt`. The wording of the reason
   comes from `spiel.md:2409` and the precedent at `werte.cpp:596-606`; do not invent a
   second justification. **No substitute value** (T6).
2. A probe start state on which the rule can be exercised at all: the three
   `Wertschoepfung` addresses of each playable country carry a positive value, so
   `bip(l) > 0` holds for all four. Print the four `bip` values. This is the state the
   existing approval probes must run on — a probe of a rule on a state the specification
   forbids measures nothing.
3. The new bound is checked from both sides: one state with `bip(l) < 1` aborts and the
   message names the barrier (pattern of `BRICHT_AB_MIT` in this file), one with
   `bip(l) > 0` runs through.

## Two things to take with you, both from the same finding

**The multiplying half of the rule is run by no probe.** `politiklast` skips `schaden`
whenever `richtung == 0` (`schritt.cpp:592-594`), and with a carrying step 3 that is all
16 pairs. `werte::schaden`, `festkomma::mal(richtung, zeile)` and the `plus` accumulation
have never executed. `schaden` takes the `Schreiber` and reads with `lies_neu`: whether
any of its reads lands outside the `weltlauf` mask is a T39 question nobody has answered
at runtime. If condition 2 lets you move one instrument level from inside the probe
without touching step 3, that answer is cheap; if it does not, say so and leave it.

**`schritt_probe.cpp:611` still reads „die Kette hat 175 Glieder, und jedes ist ein
Vortrag".** Four of them are `Gegenkraft` since `0197`. The doc comment below the banner
is already right; the banner is what a reader greps for. One line, in your `dateien`.
