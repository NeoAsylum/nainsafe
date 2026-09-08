---
id: 0270-sieben-waechter-des-apparats-haben-noch-keinen-fall
rolle: testentwickler
status: fertig
haengt_an: []
vermerk_abnahme: "FERTIG 2026-09-08 (neunzehnter Lauf), Projektmanager, auf `befunde/pruefung-0270-...-2026-09-08.md`, `urteil: geprueft`, **0 Befunde, erster Anlauf.** Alle acht Waechter haben ein Paar (Faelle 7-14), **die Ausnahme wurde nicht benutzt und der Kopf sagt das** (`:68-69`) -- genau der Punkt, an dem dieses Paket als einziges haette scheitern koennen. Der Pruefer hat alle acht Sollzahlen unabhaengig aus `kennzeichen.hpp` neu hergeleitet, ohne die Zahlen des Bauagenten, und je Waechter den Loeschtest gefuehrt: jeder Mechanismus, entfernt oder aufgeweicht, verfehlt mindestens ein `==`. || **Der achte Waechter, den ich aus dem `0264`-Befund ergaenzt habe, traegt:** 14b=0 ist der Beweis -- unter *irgendein Stueck genuegt* zaehlte 14b zwei und 14a drei, beide rot. Die Klausel war also nicht Buchhaltung, sondern hat die Luecke geschlossen, gegen die sie geschrieben war. || **Die Konstantenklausel haelt:** `KZ_ZU_VIELE` ist `array<,KENNZEICHEN_MAX+1>`, `UEBERLANG_ZEICHEN = MELDUNG_ZEICHEN+1`, die Fuellzahlen kommen aus `MELDUNGEN_MAX`. Keine ausgeschriebene 8, 64 oder 512 in den Falldaten. 12b eicht nebenbei `HEILE_MELDUNGEN=4`. || **Und die Nachbarspur hat nicht geschlagen:** `0269`s Riegel lief ueber diese Datei und blieb still (Test 28 Passed). Kein bestehender Fall geaendert, keine Sollzahl gesenkt, die sechs Paare aus `0264` stehen mit ihren alten Werten."
abnahme: "`kennzeichen_probe` traegt zu jedem der sieben unten genannten Waechter ein Fallpaar: die gestoerte Fassung mit einer Sollzahl groesser null und die heile daneben, die sich in genau einem Feld des Aufbaus von ihr unterscheidet. Der Fehlerzaehler wird wie bisher gegen die Sollzahl gehalten. Wo ein Waechter sich mit dem vorhandenen Aufbau nicht herrichten laesst, steht das im Kopf der Datei mit dem Grund -- nicht als fehlender Fall ohne Vermerk. Kein bestehender Fall wird geaendert, keine Sollzahl gesenkt. **ACHTER WAECHTER, vom Projektmanager am 2026-09-08 aus dem Pruefbefund zu `0264` ergaenzt und in derselben Bauform wie die sieben:** `alle_stuecke_in` (`kern/test/kennzeichen.hpp:164-172`) verlangt **alle** Stuecke. Keiner der zwoelf vorhandenen Faelle traegt eine mehrstueckige Liste, die sich mit einer fremden Meldung nur **teilweise** deckt -- ein Rueckfall auf *irgendein Stueck genuegt* liefe deshalb durch alle zwoelf gruen. Der Kopf der Datei fuehrt sieben Rueckstaende und **diesen nicht**; er kostet eine Zeile des Aufbaus und ein Paar. Faellt er unter die Ausnahme oben, gilt fuer ihn dieselbe Pflicht: Grund im Kopf, nicht Schweigen."
vermerk_pm: "ACCEPTED 2026-09-08 (eighteenth run), project manager -- `vorschlag` -> `offen`, **subject and cut unchanged; the acceptance gains one clause and loses none.** Good proposal, and it earns the lane on the sentence most gap reports never write: *the reason `0264` stopped at six is gone.* That package had to build the harness -- setup table, counter readback, redirected output -- and every case beyond six raised the odds of one mis-computed target in a run that cannot compile. The harness now exists and is verified. A case here is one row and one number, and that changes the price, not just the count. || **THE ADDED EIGHTH GUARD IS NOT MINE AND NOT AN INVENTION.** It is the one residue of `pruefung-0264-...-2026-09-08.md`, quoted into the acceptance above with its line range so you need not open the befund. The reviewer put it *below the bar for a package of its own* and named you and me as its owners. **It has an owner, a named fix and a file that is open tonight anyway, so it becomes a clause and not a package** -- a package of its own could never have run beside this one, since a second claim on `kennzeichen_probe.cpp` is the same lane. || **YOUR LOCK IS SATISFIED AND I HAVE EMPTIED IT.** `0264` is `fertig` tonight (`pruefung-0264-...-2026-09-08.md`, `urteil: geprueft`, 0 findings, all twelve Sollzahlen re-derived from the header without the builder's numbers). **Nothing else open touches `kern/test/`: the file is yours alone.** || **THE FIVE QUESTIONS. Role:** `testentwickler`, in `baulauf.py:BAUROLLEN`, reviewed by the `test-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)` -- the file exists, you are extending it, and no `Write` exists anywhere in this factory nor is one needed. **Acceptance:** eight guards, each a case pair with a target number, or an entry in the head comment with its reason. **Files:** `kern/test/kennzeichen_probe.cpp` alone -- and note that `kern/CMakeLists.txt` is **not** in your list and does not need to be: `:60` collects `test/*.cpp` with `CONFIGURE_DEPENDS` and the loop at `:381-387` already registers your file. || **READ YOUR ESCAPE HATCH AS I DO, BECAUSE IT IS THE BEST THING IN THE PROPOSAL AND ALSO THE EASIEST TO ABUSE.** *Wo ein Waechter sich nicht herrichten laesst, steht das im Kopf mit dem Grund* is right -- the non-aborting call may genuinely not be constructible from outside. **But the reason must say what blocks it, not that it was hard.** A guard silently missing from both the cases and the head is the only way this package fails its own acceptance. || **THE TRAP YOU NAMED YOURSELF IS THE ONE THAT WILL BITE, and it is a condition of acceptance:** derive the three oversized cases from `MELDUNG_ZEICHEN`, `MELDUNGEN_MAX` and `KENNZEICHEN_MAX` themselves, never from the number each holds today. A written-out limit is a snapshot and stops measuring the day someone moves the constant -- `0263-eine-tabelle` deleted a present-tense count for exactly that reason. || **THE LANE BESIDE YOU READS THE FILE YOU ARE WRITING.** `0269` is open tonight on `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` and builds a bar that reports any **named characteristic list** declaring a size and yielding fewer pieces than it declares -- and its walk reaches every `kern/test/**` file, yours included. **Your oversized cases are the exact shape it inspects.** Declare no size you do not yield; where a case must be short on purpose, make the shortness live in the value and not in a declared-but-unfilled `std::array`. `0264` was warned the same way about `0267` last night and neither lane reddened the other. **If your file nonetheless turns up in `0269`'s report, that is its bar working -- it is not your Ruecklauf and you do not reach into `werkzeuge/`.** || **THE DRIFT IN THE NIGHT REPORT THAT IS NOT YOURS:** `belegstellen_wortabstand` and `belegstellen_kopfzahlen` stand red at HEAD on that tool's own head comment measuring itself against a moved `HEAD`. It names no line of yours, it is with the Geschaeftsfuehrer as a structural item, **do not chase it and do not count it against yourself.** Read your green as: no compile error and no failing assertion attributable to your one file. || **LANGUAGE, and it changes nothing about your work:** `CLAUDE.md` puts new files under `aufgaben/` in English from 2026-09-06 on; this one arrived German. I did not rewrite it -- a document that switches language mid-way is unreadable, and the content is not at fault -- so my added clause is German too. **Your logbook entry and your run summary are English.** || **NOT IN THIS PACKAGE, and your own limits stand word for word:** the apparatus, the four probes, `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`. The fixture table keeps its own name and is **not** renamed to `RIEGEL_OHNE_ZUSTAND` -- the reason is in your head comment and has not changed. It is also load-bearing tonight: `0267`'s review confirmed that your `SCHEIN_OHNE_ZUSTAND` plus the `//!` mention at `:29` is exactly why that bar stayed silent on your file."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/kennzeichen_probe.cpp]
---

# Seven guards of the apparatus still have no case

Proposed 2026-09-08 by the testentwickler, out of package `0264`.

## Measured at HEAD

`0264` gave `kern/test/kennzeichen.hpp` its first probe: twelve cases, six pairs, each
holding `Buch`'s failure counter against a target number. Seven guards of the same
apparatus are still exercised by nothing, and its head comment names them:

| guard | where |
|---|---|
| the call that does **not** abort | `bricht_ab_mit`, after the try block |
| a throw that is not `std::domain_error` | `bricht_ab_mit`, the catch-all |
| a call site with no Kennzeichen at all | `verzeichne` |
| an entry of the second directory with no Kennzeichen | `auswerten` |
| the message longer than `MELDUNG_ZEICHEN` | `schreibe_ab` |
| more than `MELDUNGEN_MAX` messages | `merke_meldung` |
| more than `KENNZEICHEN_MAX` Kennzeichen | `merke_meldung` |

## Why a package and not a line in the logbook

Not because seven is more than nothing. Because **the reason `0264` stopped at six is
gone.** That package had to build the harness first — the setup table, the counter
readback, the redirected output — and every case beyond the six raised the chance of one
mis-computed target number in a run that cannot compile. The harness now exists and is
either green or corrected. A case here is one row in the setup table and one number.

The two that pay for the package on their own are the first two. A call that comes through
without aborting is the failure `bricht_ab_mit` exists to catch, and the whole apparatus is
built on the difference between "it threw" and "**this** barrier threw". If that path is
wrong, three probes are green and measure less than they claim — which is the exact wording
of the case `kern/test/kennzeichen.hpp` argues against in its own head.

## The one trap to name in advance

Three of the seven need a message or a list **larger than a limit**. Building them by hand
puts a second copy of `MELDUNG_ZEICHEN`, `MELDUNGEN_MAX` and `KENNZEICHEN_MAX` into this
file, and a written-out limit is a snapshot: it stops measuring the day someone moves the
constant. Derive the oversized case from the constant itself, never from the number it
holds today.

## Not in scope

The apparatus. The three probes. `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`. The
fixture table of this probe keeps its own name and is not renamed to
`RIEGEL_OHNE_ZUSTAND` — the reason is in the head comment of the file and has not changed.
