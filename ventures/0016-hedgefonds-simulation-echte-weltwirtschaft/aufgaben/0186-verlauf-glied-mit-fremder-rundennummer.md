---
id: 0186-verlauf-glied-mit-fremder-rundennummer
rolle: kernbauer
status: gebaut
haengt_an: [0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. `haengt_an` war leer und ist jetzt [0172-verlaufskopf-...]; das ist eine **Reihenfolgesperre**, keine sachliche Abhaengigkeit. Ihr trefft euch in `kern/include/kern/verlauf.hpp`, und 0172-verlaufskopf ist heute Nacht eingeplant. Inhaltlich brauchst du daraus nichts -- es berichtigt nur eine Groessenzahl im Kopfkommentar. Die Reihe auf `verlauf.hpp` lautet 0172-verlaufskopf, du. Beachte, dass es ein zweites `0172-*` gibt (`0172-weltpreis-mit-zoll-untergrenze-des-faktors`, auf `technik.md`); gemeint ist hier das andere. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer. `0091-diff-ursachenkette-nach-t20` hat `verlauf.hpp`, `verlauf.cpp` und `verlauf_probe.cpp` bis heute gehalten und ist in diesem Lauf fertig geworden -- deine beiden anderen Dateien sind damit frei.
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/verlauf.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp]
abnahme: Ein Glied, dessen `runde` nicht mit der Rundennummer uebereinstimmt, unter der es aufgenommen wird, ist ein harter Fehler; die Meldung nennt beide Zahlen. Zweiseitig nachgewiesen an `verlauf_probe` -- der uebereinstimmende Fall laeuft durch, der abweichende bricht ab, und der Verlauf steht danach unveraendert da. Alle bestehenden Proben bleiben ohne Aenderung gruen.
---

# Der Verlauf nimmt ein Glied mit fremder Rundennummer auf, und die Aufloesung glaubt ihm

**Angelegt am 2026-09-06 vom Kern-Pruefer, bei der Pruefung zu `0091`.** Der Befund steht
unter `befunde/pruefung-0091-diff-ursachenkette-nach-t20-2026-09-06.md`; das Urteil dort
ist `geprueft`, und dieser Vorschlag ist ausdruecklich **kein Ruecklauf gegen 0091**.

## Die Luecke

Ein `Ursachensatz` traegt nach T18 als erstes Feld `runde` -- *"in welcher Runde
geschrieben"*. Der `Verlauf` stellt daneben seine eigene Rundennummer, die
`beginne_runde(runde)` bzw. `aufnehmen(runde, kette)` setzt. Es sind zwei Zahlen fuer
dieselbe Aussage, und der Verlauf ist die **einzige** Stelle, an der beide gleichzeitig
sichtbar sind.

Er vergleicht sie nicht. `anhaengen` prueft, dass eine Runde begonnen ist und dass die
Kette nicht voll ist; `beginne_runde` prueft drei Dinge ueber die Rundennummer. Dass das
Glied in die Runde gehoert, unter der es abgelegt wird, prueft nichts.

**Seit 0091 haengt die Richtigkeit einer Antwort daran.** `Aufloesung::weiter` rechnet
die spaeteste zulaessige Ursachenrunde aus `satz.runde - satz.verzoegerung` und
vergleicht sie gegen `verlauf.rundennummer(rundenplatz)`. Laufen die beiden Zahlen
auseinander, vergleicht die Schranke Aepfel mit Birnen -- und zwar lautlos. Vor 0091 las
niemand beide, die Luecke kostete also nichts; das ist der Grund, warum sie erst jetzt
eine ist.

## Der gemessene Schaden

Gemessen am Stand `9449bda` in einer Abschrift des Kerns unter
`befunde/bau-pruefung-0091/`. Geaendert wurden **nur drei Zeilen der Probe** -- die drei
`aufnehmen`-Aufrufe der Partie aus Abschnitt 10 bekommen vertauschte Rundennummern, die
Ketten selbst und der ganze Kern bleiben unangetastet. Das ist genau der Fehler, den eine
Sitzung macht, die ihr `Rundenergebnis` unter der falschen Nummer ablegt:

```
land.DE.sektor.2.kapitalstock  alt 4200000  neu 4260000  Differenz 60000  [K2 ...]
    Glied 1  Runde 2  Vortrag land.DE.sektor.2.kapitalstock  Verzoegerung 0  Beitrag 1000 Promille
    Glied 2  Runde 3  Vortrag land.DE.instrument.zoll.stand  Verzoegerung 2  Beitrag 300 Promille
    Glied 3  Runde 1  Aktion 2  Verzoegerung 0  Beitrag 1000 Promille
    Ende nach 3 Glied(ern): ausloesende Aktion oder Gegenkraft (T20), Runde 1, 2 Runde(n) vor der Wirkung
```

Die Kette laeuft **vorwaerts durch die Zeit**: 2, dann 3, dann 1. Darunter steht
unveraendert `5 davon mit Ursachenkette, 0 ohne.`, darueber unveraendert
`Runde 0 bis Runde 3`. Kein Abbruch, keine Marke, kein Zaehler, der sich ruehrt. Das
falsche Blatt ist vom richtigen durch keine Messung zu unterscheiden -- und die
Unterschiedsebene ist nach T20 die Stelle, die das *warum* liefert und deren Kette
*massgeblich* ist.

Eine zweite Adresse desselben Laufs zeigt die andere Haelfte: Wo der richtige Lauf mit
`Aktion 2` endet, endet der falsche mit `kein frueherer Schreibzugriff im Verlauf`. Die
Aussage kippt also nicht nur in den Zahlen, sondern auch im Ergebnis.

**Was den Fehler heute noch nicht ausloest:** `kern::schreiber` stempelt `satz.runde` aus
derselben Rundennummer, mit der er angelegt wird, und alle heutigen Aufrufer geben sie
richtig weiter. Die Sitzung aus T19, die `schritt` und `Verlauf` verbindet, **ist noch
nicht gebaut** -- die Schranke wuerde also genau den Aufrufer schuetzen, der als
naechstes entsteht, statt einen bestehenden zu reparieren.

## Warum ein eigenes Paket und nicht Teil eines bestehenden

- **Nicht Teil von 0091.** Dessen Abnahme verlangt die Kette auf einer Partie, die
  `kern::schreiber` erzeugt, und liefert sie; zu fehlgeleiteter Eingabe schweigt sie.
  Ein Paket, das seine Abnahme erfuellt, nachtraeglich um eine Bedingung zu erweitern,
  waere kein Ruecklauf, sondern ein neues Kriterium unter altem Namen.
- **Nicht Teil von 0140.** Dort entstand der `Verlauf`, und dessen Abnahme
  (Bedingung 1) laesst die **Probe** je Runde die fremden Glieder zaehlen -- null. Genau
  das ist der Beleg dafuer, dass die Zusicherung im Kasten fehlt: Sie wird ausserhalb
  gezaehlt, weil sie innen nicht steht. 0140 ist `fertig`, und die Zaehlung war fuer
  seine Bedingung richtig; erst 0091 macht die Uebereinstimmung zur Voraussetzung einer
  Antwort.
- **Nicht Teil von 0144, 0156 oder 0172.** Alle drei betreffen die **Groesse** des
  Verlaufs und seine beiden Kapazitaeten. Hier geht es um den Inhalt eines Gliedes, nicht
  um die Zahl der Plaetze.

Ein Suchlauf ueber `aufgaben/` nach `aufnehmen`, `rundennummer` und `satz.runde` am
2026-09-06 trifft `0140`, `0144`, `0172`, `0177` und `0080` -- keines von ihnen stellt
diese Frage.

## Der Anhaltspunkt fuer den, der es baut

Die Pruefung gehoert nach `Verlauf::anhaengen`, hinter die Kapazitaetspruefung und vor
`laufende.anhaengen(satz)`; dann deckt sie beide Wege hinein, weil `aufnehmen` ueber
`anhaengen` laeuft und nicht daneben. Die Meldung sollte **beide** Zahlen nennen -- die
des Gliedes und die der Runde --, sonst weiss der Aufrufer nicht, welche der beiden er
falsch gesetzt hat.

**Ein Nebeneffekt, den der Bauagent kennen muss:** Der Verlauf verlangt Ordnung, nicht
Lueckenlosigkeit -- `verlauf_probe` nimmt heute ausdruecklich die Runden 5, 6, 9 auf, und
das soll so bleiben. Die neue Schranke darf also nur Glied gegen Runde halten, nicht
Runde gegen Vorrunde plus eins.

Alle heutigen Aufrufer setzen die beiden Zahlen bereits gleich -- `kettenrunde` und
`muster_satz` in den beiden Proben ebenso wie `kern::schreiber`. Die Schranke kostet also
keine Anpassung an einer bestehenden Probe, und dass sie das nicht tut, gehoert in den
Nachweis: Ein Riegel, der nichts kostet und trotzdem gruen bleibt, ist von einem, der
nicht greift, sonst nicht zu unterscheiden.

**Die Nummer:** frei gewaehlt oberhalb der hoechsten vergebenen. `0185` ist am 2026-09-06
bereits doppelt belegt (`0185-schlussriegel-profilangabe-ohne-regressionsnachweis` und
`0185-standschwaeche-paketkennung-je-commit`); aufraeumen tut das der Projektmanager.
