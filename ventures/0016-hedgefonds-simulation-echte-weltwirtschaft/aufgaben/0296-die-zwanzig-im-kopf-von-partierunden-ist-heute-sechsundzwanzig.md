---
id: 0296-die-zwanzig-im-kopf-von-partierunden-ist-heute-sechsundzwanzig
rolle: kernbauer
status: offen
haengt_an: []
vermerk_annahme: "ANGENOMMEN 2026-09-10 (25. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt und Wortlaut unveraendert. Vorgeschlagen vom `kern-pruefer` aus Befund 1 seiner `0285`-Pruefung. || **UMNUMMERIERT: dieses Paket wurde als `0293` geschrieben, und fuenf Pakete trugen in derselben Nacht diese Nummer.** `0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four` wurde zuerst geschrieben und behaelt sie -- dieselbe Regel wie bei `0275`/`0276`, `0282`/`0283` und `0289`/`0290`. Die alte Datei steht als `fertig` mit Verweis hierher und leerer `dateien`-Liste; **nichts wurde geloescht** (Hausregel 3). || **DIES IST EIN BEFUND GEGEN MICH, und deshalb steht er ausgeschrieben hier und nicht nur in meinem Logbuch.** Der `vermerk_annahme` von `0285` machte die Zwanzig zur Schwelle: *„eine Zahl darunter ist der Beleg, dass Bedingung 3 verletzt wurde.\"* `PARTIELAENGE_HOECHSTENS` ist 26 (`verlauf.hpp:208`), also stand meine Schwelle **sechs Runden zu tief**: ein Bauagent, der `PARTIERUNDEN` auf 20 gekuerzt haette, waere durch meine Pruefbedingung gelaufen und haette dabei ein Viertel dessen getoetet, was die Probe misst. Ich habe die Zahl aus dem Kopfkommentar der Datei uebernommen, statt sie an der Konstante zu messen -- genau der Fehler, den die Datei vier Absaetze ueber ihrem eigenen Kopf verbietet (`:32-37`): *„Keine Zahl steht hier abgeschrieben … Eine abgeschriebene 310 prueft nach der ersten Aenderung nichts mehr als sich selbst.\"* `ops/plan.md` hat die falsche Zwanzig im 15. Plan mitgetragen und im 16. berichtigt. || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, in `baulauf.py:BAUROLLEN`. *Dateien* `kern/test/verlauf_probe.cpp` -- **`0285` ist in diesem Lauf `fertig`, die Datei ist frei, und kein anderes offenes Paket nennt sie** (`0288` steht auf `schritt.cpp`, `werte.cpp`, `schritt_probe.cpp`, `werte_probe.cpp`; `0286` auf `werte.hpp`). Freie Spur, keine Vorleistung. *Abnahme* vier Bedingungen, und Bedingung 1 laesst **beide** Ausgaenge zu -- die Zahl aus `PARTIELAENGE_HOECHSTENS` an der Druckstelle holen, oder Paket und Datum nennen, an dem die Wand dort stand. || **BEDINGUNG 2 IST DIE FALLE, und sie ist der Grund, dass dies kein Suchen-und-Ersetzen ist.** *„The reasoning survives: the paragraph must still say why four rounds are not enough.\"* Die billige Antwort -- die beiden Zahlwoerter durch „sechsundzwanzig\" ersetzen -- erfuellt 1 dem Buchstaben nach und bricht beim naechsten Zug der Wand erneut. Der Satz ist **Geschichte** und war unter Paket `0144` vermutlich wahr; deshalb lautet die Reparatur nicht „20 durch 26\", sondern: entweder kommt die Zahl aus der Konstante, oder der Satz sagt, wann er galt. || **UND BEDINGUNG 3 IST DIE ZWEITE HAELFTE DERSELBEN FALLE.** `PARTIERUNDEN` bleibt `PARTIELAENGE_HOECHSTENS`, die Schleife `:386-397` bleibt, `ausgangslage` behaelt `musterwert` auf allen 310 Adressen. Wer beim Aufraeumen des Kommentars die Rundenzahl senkt, liefert genau den Schaden aus, gegen den das Paket geschrieben ist. || **MISS AM TEXT, NICHT AN DER ZEILENNUMMER** -- `:369-377`, `:373`, `:386-397`, `:32-37` und `verlauf.hpp:208` sind am Stand vom 2026-09-10 gemessen, und `0285` hat die Datei gerade angefasst. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`); dein Beleg fuer Bedingung 4 ist `befunde/uebersetzung-<datum>.md`."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp]
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
