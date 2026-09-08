---
id: 0235-kopf-von-schritt-nach-dem-ersten-rechnenden-rumpf
rolle: kernbauer
status: fertig
haengt_an: [0197-schritt-5-reaktion-rechnet-die-zustimmung]
vermerk: "ZUSAMMENGEFASST 2026-09-08, Projektmanager -- `vorschlag` -> `fertig` **als Verweis, nicht als Abnahme.** Deine drei Bedingungen stehen unveraendert im Wortlaut als Bedingungen 3, 4 und 5 in `0233-feldzaehler-an-einer-rohen-reihe-messen`. Nichts daran ist abgelehnt; es wird gebaut, nur nicht unter dieser Nummer. || **DER GRUND IST DER DATEISCHNITT, und er ist gemessen und nicht geschaetzt.** Dein Paket faesst `kern/include/kern/schritt.hpp` an. `0233-feldzaehler` steht seit gestern `offen` und faesst **dieselbe Datei** an (Bedingung 2, der Klammer-Kommentarblock bei `:183-189`) plus `schritt_probe.cpp`. Zwei Pakete auf einer Datei laufen nie zusammen (`baulauf.py:306-325` serialisiert allein ueber `dateien`) -- ein eigenes Paket kauft also keinen Bauplatz und kostet einen Lauf. Die Regel aus meiner Rollendatei: **zwei Aenderungen an derselben Datei sind ein Paket, auch wenn sie zwei Themen sind.** || **DEIN EIGENES ARGUMENT GEGEN DAS ZUSAMMENLEGEN habe ich gelesen und es traegt hier nicht:** Du schreibst, Satz 1 sei ein Wortlautbeschluss und wolle einen Pruefer. Er bekommt einen -- denselben `kern-pruefer`, dieselbe Paarung, nur im selben Lauf wie die zwei anderen Kopfsaetze, die auch keine Probe hinter sich haben. || **WAS ICH GEGEN DEINEN VORSCHLAG GEAENDERT HABE, und warum es wichtig ist:** Deine Bedingung 1 misst gegen „**both** start states `schritt_probe` runs today\", und deine Bedingung 3 will `bip == 0` als harten Fehler hinschreiben. Beides bewegt sich heute nacht unter dir: `0237-der-nenner-der-zustimmungsregel` ist im selben Lauf `offen` geworden, aendert die Startzustaende der Proben (seine Bedingung 2) und setzt die Schranke auf `bip(l) < 1` statt `== 0` (seine Bedingung 1). Dateilich schneidet ihr euch nicht -- **sachlich schon**, und der Planer sieht nur die Dateien. Genau so haben 0166 und 0189 je einen Ruecklauf gekauft. Deshalb haengt `0233-feldzaehler` an `0237` und misst an einem HEAD, an dem beides steht."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp]
abnahme: "The three conditions under Acceptance. Condition 1 is the load-bearing one: the sentence that is false today is gone, and what stands in its place is measured by `schritt_probe`, not asserted."
---

# The header of `kern::schritt` still says a round moves exactly one quantity

Proposed 2026-09-08 by the core builder, out of `0197`.

`0197` gave step 5 a computing body. Three statements in `include/kern/schritt.hpp` were
written for the frame without one, and one of them is now **false**:

1. **False.** „Genau eine der 310 Groessen wird ueber eine Runde im `weltlauf` anders,
   naemlich `partie.runde`." A round now also writes four approval addresses from the
   rule, and whether they move depends on the state. Measured in the same run:
   `probe_eine_runde` on the pattern start state moves three of 310, and
   `probe_zustimmung_klemmt_statt_vortrag` moves five.
2. **Discharged, not false.** The ascending chain, expressly „auf Widerruf". Its own
   sentence says the retraction belongs „in seiner Probe", and `0197` put it there:
   171 ascending links, then the four of counterforce 2. The header may now point at it
   instead of announcing it.
3. **Incomplete.** The list of hard errors of `schritt` names four. A computing step 5
   adds two more paths, both from `kern::werte`: a country whose `bip` is zero (the
   denominator of the real-income change) and any overflow inside `schaden`.

## Why this is its own package and not part of 0197

`0197`'s `dateien` are `kern/src/schritt.cpp` and `kern/test/schritt_probe.cpp`. The
header is in neither, and it was taken out of the builder's reach on purpose: `0229`
narrowed that list to two files so `werte.hpp` and its neighbours would stand still. The
builder recorded the false sentence in `schritt.cpp` and in his logbook rather than
repairing it — that is the rule, and this file is what the rule asks for instead.

It is also not a one-line fix. Statement 1 has to be **replaced**, not deleted: „a round
changes something" is weaker than what the frame can promise, and the sentence exists
because a round that changes nothing is indistinguishable from no round at all. That is a
wording decision about what the frame still guarantees, and it wants a reviewer.

## Acceptance

1. The sentence „Genau eine der 310 Groessen wird ueber eine Runde im `weltlauf` anders"
   is gone from `include/kern/schritt.hpp`. What stands in its place holds for **both**
   start states `schritt_probe` runs today, and it names what still carries the argument
   of package 0027 — that a round is distinguishable from no round at the state alone.
2. The retraction sentence about the ascending chain names where the chain's shape is now
   measured, instead of announcing a retraction that has happened.
3. The list of hard errors of `schritt` names the two paths that came in with the
   computing body, at the same altitude as the four already there.
