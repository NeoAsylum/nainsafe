---
id: 0293-die-zwanzig-im-kopf-von-partierunden-ist-heute-sechsundzwanzig
rolle: kernbauer
status: fertig
haengt_an: []
dateien: []
vermerk_umnummeriert: "UMNUMMERIERT 2026-09-10 (25. Lauf), Projektmanager, `vorschlag` -> `fertig`. **Dieses Paket laeuft weiter unter `0296-die-zwanzig-im-kopf-von-partierunden-ist-heute-sechsundzwanzig` und steht dort auf `offen`** -- Inhalt, `abnahme` und Rumpf unveraendert uebernommen. Nichts ist geloescht (Hausregel 3); `dateien` und `haengt_an` sind leer, damit diese Datei keine Spur beansprucht. **Fuenf Pakete wurden in der Nacht auf den 2026-09-10 als `0293` geschrieben.** Die Nummer behaelt das zuerst geschriebene, `0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four` -- dieselbe Regel wie bei `0275`/`0276`, `0282`/`0283` und `0289`/`0290`."
abnahme: "1. The head comment of `PARTIERUNDEN` (`verlauf_probe.cpp:369-377`) no longer states a capacity as a bare number word. Either the sentence takes the number from `PARTIELAENGE_HOECHSTENS` at the point where it is printed, or it names the package and date at which the wall stood there, so a reader cannot take it for today's value. 2. The reasoning survives: the paragraph must still say why four rounds are not enough -- a proof that only counts to the old wall is indistinguishable from one that reaches the current wall. 3. `PARTIERUNDEN` stays `PARTIELAENGE_HOECHSTENS`, the loop at `:386-397` stays, `ausgangslage` keeps `musterwert` on all 310 addresses. 4. `verlauf_probe` green in the build report."
---

# The word "zwanzig" outlived the wall it described

## What is wrong, measured on 2026-09-10

`verlauf_probe.cpp:373` reads:

> "Vier Runden liefen auch gruen, als der Verlauf bei **zwanzig** abbrach -- ein Nachweis,
> der nur bis **zwanzig** zaehlt, ist von einem, der die Wand erreicht, nicht zu
> unterscheiden."

`PARTIELAENGE_HOECHSTENS` is 26 (`verlauf.hpp:208`), so `RUNDEN_KAPAZITAET` is 26 and this
probe runs 26 rounds. The two number words are the only place in this file where a capacity
is written out instead of taken from the constant, and the file rejects exactly that four
paragraphs above its own head (`:32-37`): *"Keine Zahl steht hier abgeschrieben … Eine
abgeschriebene 310 prueft nach der ersten Aenderung nichts mehr als sich selbst."*

## Why it is worth a package and not a note

It has already cost a criterion its correctness. The acceptance of package `0285` demanded
"twenty rounds and 175 links per round" and its `vermerk_annahme` made twenty the floor:
*"eine Zahl darunter ist der Beleg, dass Bedingung 3 verletzt wurde."* Against a wall of 26
that floor sits six rounds too low — a builder who had cut `PARTIERUNDEN` to 20 would have
passed the stated test while killing a quarter of what the probe measures. `ops/plan.md:98-104`
carries the same chain. Details in
`befunde/pruefung-0285-verlauf-probe-faehrt-mit-einem-pfadstand-der-ihre-lage-nicht-bewegt-2026-09-10.md`,
finding 1.

The sentence is *history* and may well have been true when package `0144` wrote it. That is
why the fix is not "replace 20 with 26" — the next move of the wall would break it again.
Either the number comes from the constant, or the sentence says when it held.

## Not part of `0285`

`0285` was allowed one change to this file, the carrier, and it made exactly that one. This
paragraph is a different region of the same file and predates it; it belongs to whoever
next opens the file, serialised through `dateien` like everything else.
