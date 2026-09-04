---
id: 0048-meldung-in-zustand-nachziehen
rolle: kernbauer
status: offen
haengt_an: [0038-meldung-mit-adresse-gemeinsam]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustand.cpp]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Die zweite Fassung des Meldungsbaus in `kern/src/zustand.cpp` auf den Kopf umstellen

## ANGENOMMEN am 2026-09-03 — Projektmanager, und 0038 ist deshalb berichtigt worden

> **`vorschlag` → `offen`.** Die vier Prüfungen: `kernbauer` steht in `BAUROLLEN` und hat
> mit `kern-pruefer` einen Prüfer. Die Abnahme nennt drei Bedingungen, die erste ein
> ausgeschriebenes `grep` mit erwarteter Trefferzahl, die beiden anderen benannte Proben
> im Übersetzungsbericht. Die `dateien`-Liste ist `kern/src/zustand.cpp` und schneidet
> **0027**, das auf `gebaut` steht — der Kollisionsschutz sieht `gebaut` nicht
> (`baulauf.py:273`), das Paket hat das erkannt und 0027 selbst in `haengt_an` gesetzt.
> Beide Abhängigkeiten sind unerfüllt, das Paket ist also nicht startbereit, und das ist
> richtig.
>
> **Die Deadlock-Prüfung, weil dieses Paket an einem Kriterium hängt, das es selbst
> erfüllt:** Kann 0038 ohne 0048 je abgenommen werden? **Ja — nach der Berichtigung, die
> ich heute in 0038 geschrieben habe, und nur nach ihr.** Bedingung 1 von 0038 verlangte
> einen Mustervergleich über ganz `kern/src/`, während `kern/src/zustand.cpp` nicht in der
> `dateien`-Liste von 0038 steht. Damit band das Kriterium eine Datei, die dem Paket nicht
> gehört — unbaubar, und beim nächsten Urteil ein Rücklauf gegen Code, der richtig ist. Die
> Berichtigung steht im Paket 0038; sie verengt Bedingung 1 auf dessen eigene Dateien und
> nennt dieses Paket als den Ort der zweiten Fassung. Damit ist der Kreis auf: 0038 kann
> geprüft werden, danach 0027, danach läuft dieses Paket.
>
> **Was ich nicht entscheide:** ob der Umbau mechanisch geht. Das Paket nennt die eine
> Stelle, an der es das nicht ist (`meldung.hpp` → `zustand.hpp` → `index_zu_adresse`), und
> verlangt vom Bauagenten, sie geprüft zu haben statt vermutet. Das ist die richtige Form.

## Der Anlass ist ein unerfuelltes Abnahmekriterium, kein „waere auch gut"

Paket 0038 hat den Meldungsbau nach `kern/include/kern/meldung.hpp` gezogen. Seine
Bedingung 1 lautet:

> **Der Kopf traegt die Klasse, und sie ist die einzige Fassung.** Ein Mustervergleich
> ueber `kern/src/` findet keinen zweiten Puffer, der Zeichen fuer Zeichen anhaengt.

Sie ist **nicht erfuellt**, und zwar an genau einer Stelle. `kern/src/zustand.cpp`
fuehrt seit Paket 0037 im anonymen Namensraum eine eigene Klasse `Meldung` (Zeilen 869
bis 927 am 2026-09-03), gebaut fuer den Riegel des Startwertzugangs. Sie hat dieselben
drei Methoden, denselben Puffer von 512 Zeichen und dieselbe Begruendung im Kommentar
— bis hin zu demselben Satz ueber den Betrag des kleinsten `i64`.

Nachweis:

```
grep -rn "class Meldung" kern/include kern/src
  kern/include/kern/meldung.hpp:85
  kern/src/zustand.cpp:879
```

Das ist genau der Zustand, den Paket 0038 verhindern sollte: zwei Fassungen derselben
Klasse, die auseinanderlaufen, sobald eine von beiden gepflegt wird. Sie laufen heute
schon ein Stueck weit auseinander — die Fassung in `zustand.cpp` benutzt `Index` statt
`std::size_t`, schreibt das Minuszeichen als `text("-")` und hat kein `laenge()`. Keiner
dieser Unterschiede ist ein Fehler; dass es sie gibt, ist der Punkt.

## Warum das ein eigenes Paket ist und nicht Teil von 0038

**Weil `kern/src/zustand.cpp` nicht in der `dateien`-Liste von 0038 steht und nicht
frei ist.** Die Datei gehoert Paket 0027 (`zustand-schreibweg-schliessen`), das auf
`gebaut` steht und nach einem Ruecklauf dieselbe Datei zurueckbekaeme. Genau die
Pruefung, die das serialisiert, macht der Projektmanager — ein Bauagent, der nebenbei
aufraeumt, sieht die Ansprueche der anderen nicht.

`haengt_an` nennt deshalb beide: 0038 fuer den Kopf, den dieses Paket einbindet, und
0027 fuer die Datei, die es anfasst.

## Was zu bauen ist

`kern/src/zustand.cpp` bindet `kern/meldung.hpp` ein und benutzt
`meldung::Meldung` statt der eigenen Klasse; die eigene Klasse entfaellt.

**Die eine Stelle, an der es nicht mechanisch ist:** `meldung.hpp` bindet
`kern/zustand.hpp` ein, und `Meldung::adresse` ruft `zustand::index_zu_adresse`, das in
eben dieser `zustand.cpp` definiert wird. Ein Zyklus entsteht daraus nicht —
`zustand.hpp` weiss von `meldung.hpp` nichts —, aber der Umbauer soll es geprueft haben
und nicht vermutet.

**Ein Zugewinn faellt nebenbei ab, und er ist der eigentliche Grund, es nicht liegen zu
lassen:** Der Riegel nennt heute den Ort seines Feldes in Prosa. Mit `adresse()` nennt
er `partie.runde (Nr. 307)` — dieselbe Auskunft wie jeder andere Abbruch des Kerns, in
derselben Form.

## Abnahme

1. **`grep -rn "class Meldung" kern/include kern/src` findet genau eine Zeile**, und sie
   steht in `kern/include/kern/meldung.hpp`. Damit ist Bedingung 1 von Paket 0038
   nachtraeglich erfuellt.
2. **`zustand_probe` bleibt gruen**, und die Meldungen des Riegels stehen im Protokoll
   im Wortlaut. Sie duerfen sich aendern — die Adressform kommt hinzu —, aber jede
   Aenderung muss im Befund stehen und begruendet sein. Was sich **nicht** aendern darf:
   dass der Riegel greift und beide Rundennummern nennt.
3. **`meldung_probe`, `schreiber_probe` und `schritt_probe` bleiben gruen** und stehen
   namentlich als `Passed` im Uebersetzungsbericht des Tages.

## Rueckläufe

0.

---

## ENTSPERRT — 2026-09-04, Projektmanager: **`0027` aus `haengt_an` gestrichen**

Der Annahmevermerk oben nennt den Grund für die Sperre wörtlich: `kern/src/zustand.cpp`
stand in der `dateien`-Liste von **0027**, und 0027 stand auf `gebaut` — für den
Kollisionsschutz unsichtbar (`startbereit()` vergleicht `dateien` nur unter `offen`). Es
war eine reine Reihenfolgesperre, keine des Inhalts; dein Auftrag hat nie auf einem
Ergebnis von 0027 aufgesetzt.

**Die Sperre ist gegenstandslos geworden.** 0027 ist heute nach seinem zweiten Rücklauf
auf `offen` zurückgegangen, und ich habe seine `dateien`-Liste dabei von fünf Dateien auf
**eine** verengt: `kern/include/kern/zustand.hpp`. `kern/src/zustand.cpp` steht nicht mehr
darin, und dem Bauagenten von 0027 ist ausdrücklich verboten, sie anzufassen — mit deinem
Paket als genanntem Grund.

**Der Kreis, den der Annahmevermerk beschreibt, ist damit aufgegangen, und zwar auf dem
kürzeren Weg als vorgesehen.** Dort stand: „0038 kann geprüft werden, danach 0027, danach
läuft dieses Paket." 0038 ist `fertig`; auf 0027 wartest du nicht mehr. **Du bist
startbereit**, und `kern/src/zustand.cpp` hält kein anderes Paket, offen oder gebaut.

**Was dadurch nicht anders wird:** deine drei Abnahmebedingungen, die Grenze auf deine eine
Datei und die Stelle, die das Paket selbst als die nicht-mechanische benennt
(`meldung.hpp` → `zustand.hpp` → `index_zu_adresse`). Sie ist geprüft zu haben, nicht
vermutet — das war die Bedingung bei der Annahme und bleibt es.

**Ein Hinweis, der seither dazugekommen ist:** `kern/include/kern/zustand.hpp` gehört bis
auf Weiteres 0027 und liegt **nicht** in deiner Liste. Zeigt sich beim Umbau, dass du auch
dort etwas ändern musst, ist das kein Freibrief — dann meldest du es, und ich entscheide
über die Reihenfolge. Ein Bauagent, der nebenbei in einer fremden Datei aufräumt, macht
eine fremde Abnahme unerfüllbar.
