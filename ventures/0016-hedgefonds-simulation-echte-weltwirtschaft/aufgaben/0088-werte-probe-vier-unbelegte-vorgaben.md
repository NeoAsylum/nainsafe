---
id: 0088-werte-probe-vier-unbelegte-vorgaben
rolle: testentwickler
status: vorschlag
haengt_an: [0002-fondsbewertung-definieren]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: Vier neue Pruefungen in `werte_probe.cpp`, je eine zu den vier Vorgaben unten. Der Nachweis ist zweiseitig und wird je Vorgabe einzeln gefahren: Am unveraenderten `kern/src/werte.cpp` laeuft `werte_probe` gruen; mit der je Vorgabe angegebenen Mutation wird sie rot. Eine Pruefung, die auch am mutierten Modul gruen bleibt, zaehlt nicht.
---

# Vier Vorgaben aus T47, T48 und T33 lassen sich heute verletzen, ohne dass eine Probe rot wird

> **Zur Nummer, damit der Projektmanager es nicht nachschlagen muss.** Sie war
> kurzzeitig doppelt: Beim Lesen der hoechsten Nummer war 0087 die letzte, nach dem
> Schreiben stand `0088-kopfkommentar-herkunft-0007-statt-0004.md` daneben. Der parallele
> Lauf ist inzwischen selbst auf `0089` ausgewichen; **0088 ist damit eindeutig diese
> Datei.** Umbenennen haette die Werkzeuglage dieses Laufs nicht zugelassen (`mv`,
> `git mv` und `os.rename` alle abgelehnt).

Vorgeschlagen vom `kern-pruefer` aus der Pruefung zu Paket
`0002-fondsbewertung-definieren` (`urteil: geprueft`). **Das Paket selbst ist in
Ordnung** -- alle vier Vorgaben sind im Code richtig gebaut, ich habe jede einzeln
nachgerechnet. Was fehlt, ist der Riegel dahinter.

## Warum das ein eigenes Paket ist und kein Ruecklauf an 0002

Die sechs Abnahmebedingungen von 0002 sind erfuellt; keine verlangt eine Probe je
Vorgabe. Ein Ruecklauf wuerde also ein Kriterium nachtraeglich verschaerfen, statt ein
unerfuelltes einzuloesen. Zugleich ist die Rolle eine andere: `werte_probe.cpp` ist
Sache des Testentwicklers, und der Schnitt „Bauagent baut, Testentwickler riegelt ab"
ist genau der, an dem diese Fabrik ihre Befunde findet.

Die Datei steht in der `dateien`-Liste von 0002. Ist 0002 auf `fertig`, schneidet sich
dieses Paket mit keinem anderen offenen: Es fasst allein `kern/test/werte_probe.cpp` an.

## Wie die vier gefunden wurden

Dreiundzwanzig Mutationen am fertigen Modul, jede einzeln uebersetzt und gegen alle
zwoelf Proben des Kerns gefahren (Debug, `-fwrapv -fno-fast-math`). Neunzehn wurden rot,
eine Kontrollmutation ohne Wirkung blieb erwartungsgemaess gruen. **Vier
Verletzungen einer schriftlichen Vorgabe blieben gruen** -- das sind die vier hier.

## Die vier

### 1. Die Skalengrenze liegt am **aeussersten** Aufruf (T47, T50)

*Mutation, die gruen bleibt:* In `beteiligung_wert_aus` die Umrechnung nach innen
ziehen -- `mal_geteilt(tsd_in_cent(korb), anteil, 10'000)`, danach der Abschlag, und
kein `tsd_in_cent` mehr aussen.

Das ist **nicht** Befund 2 der sechsten Entwurfspruefung -- die Umrechnung fehlt nicht,
sie steht nur an der falschen Stelle. Die Zahl aendert sich trotzdem, weil zwei
Rundungen dazwischenliegen. Von Hand, mit Korb 3, Anteil 3.333, Abschlag 0:

| Form | Rechnung | Ergebnis |
|---|---|---|
| verbindlich (T47) | `runde(3 · 3333 / 10000) = 1`, dann `· 100.000` | **100.000** Cent |
| Mutation | `runde(300.000 · 3333 / 10000) = 99.990` | **99.990** Cent |

Die Zahlenprobe aus T47 (Abnahme 4 von 0002) faengt es nicht: Dort geht
`21.000.000.000 · 20 / 10.000` restlos auf, und wo nichts gerundet wird, liefern beide
Stellen dieselbe Zahl. Die neue Pruefung braucht deshalb **Zahlen mit Rest** -- dieselbe
Bauart, die 0002 fuer die Rundungsreihenfolge schon anwendet (`werte_probe.cpp:279`,
Kapitalstock 14.999).

### 2. Der Positionswert traegt das **Vorzeichen** der Stufenzahl (T48 Nr. 15)

*Mutation, die gruen bleibt:* in `positionswert_aus` `mal(betrag(stufen), je_stufe)`
statt `mal(stufen, je_stufe)`.

Das ist die schwerste der vier. T48 schreibt fuer Nr. 14 (`fondsanteil`) ausdruecklich
`|stufen|` und fuer Nr. 15 (`positionswert`) ausdruecklich `stufen` -- der Unterschied
ist eine Entscheidung des Entwurfs und keine Schreibweise: Ein grosser Short bewegt
einen Markt wie ein grosser Long (deshalb der Betrag), ist aber **negatives Vermoegen**
(deshalb das Vorzeichen). Faellt das Vorzeichen weg, zaehlt jeder Short als Long, und
Todesart 1 (`fondsvermoegen <= 0`) greift bei einem Fonds, der sich mit Shorts
ruiniert, nie.

Gemessen, mit Kapitalstock 1.000.000, `stufenweite` 250 und `stufen = -4`:

```
unveraendert:  stufenwert=25000  positionswert=-10000000000
mit Mutation:  stufenwert=25000  positionswert=+10000000000
```

Zwei mal 10^10 US-Cent Unterschied, und alle zwoelf Proben bleiben gruen.

*Warum keine der vorhandenen Pruefungen es sieht:* `probe_fondsvermoegen_zweiter_weg`
belegt zwar Steckplaetze mit negativen Stufenzahlen, vergleicht aber den gebuendelten
Weg gegen den einzelnen -- **beide rufen dieselbe Funktion**, also aendern sich beide
Seiten gemeinsam. Ein zweiter Rechenweg, der die gepruefte Funktion enthaelt, prueft
alles ausser ihr selbst. Gebraucht wird eine Zusage mit **ausgeschriebener negativer
Zahl**.

Diese Pruefung habe ich bereits einmal gebaut und in beide Richtungen gefahren: am
unveraenderten Modul gruen, gegen die Mutation rot, mit genau den beiden Messwerten
oben. Der Wortlaut steht im Befund
`befunde/pruefung-0002-fondsbewertung-definieren-2026-09-04.md`.

### 3. Der Marktkorb enthaelt **keine** Waehrungen (T33 Punkt 1, T48 Nr. 7)

*Mutation, die gruen bleibt:* in `marktkorb` neben `anleihewert_zwei` auch
`waehrungswert` je Land aufaddieren.

`probe_marktkorb_zwei_quellen` laesst alle Handelsstroeme auf null; damit ist jeder
Waehrungswert null und der zusaetzliche Summand unsichtbar. Die Probe braucht einen
Zustand mit **nachweislich positivem Waehrungswert** -- `probe_fondsanteil_und_korbbestand`
macht genau das fuer `korbbestand` bereits vor (`werte_probe.cpp:547-553`) und ist die
Vorlage.

Wirkung, falls verletzt: Der Marktkorb waere dauerhaft zu gross, und mit ihm sind
`markt.rendite`, `markt.wert` und `fonds.marktanteil` falsch -- also Mass 1 und Mass 3.

### 4. Der Waehrungswert nimmt den festen Kurs 10.000, nicht den Wechselkurs (T48 Nr. 4)

*Mutation, die gruen bleibt:* in `waehrungswert` statt des Literals 10.000 den
Wechselkurs des Gebiets als Kurs einsetzen.

Dann kuerzt sich der Wechselkurs gegen sich selbst weg und der Waehrungsmarkt haengt
nicht mehr am Wechselkurs -- die eine Groesse, die eine Waehrung ueberhaupt bewegt.
Unsichtbar bleibt es, weil die Grundbelegung der Proben den Wechselkurs ueberall auf
seinem Startwert 10.000 stehen laesst; genau dort sind beide Formen gleich. Die Probe
braucht einen Wechselkurs **ungleich 10.000** -- `probe_marktkorb_zwei_quellen` setzt
ihn aus demselben Grund schon einmal auf 5.000 (`werte_probe.cpp:407`).

## Was ausdruecklich nicht dazugehoert

Kein `kern/src/werte.cpp` und kein `kern/include/kern/werte.hpp`. Alle vier Vorgaben
sind dort heute richtig gebaut; wer sie „zur Sicherheit" anfasst, aendert einen Zustand,
der stimmt, und macht den Regressionsbestand ungueltig.
