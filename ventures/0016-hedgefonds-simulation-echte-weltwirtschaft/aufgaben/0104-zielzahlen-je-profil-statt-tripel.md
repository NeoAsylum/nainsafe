---
id: 0104-zielzahlen-je-profil-statt-tripel
rolle: projektmanager
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# "16 / 10 / 5" gilt fuer kein Profil mehr und ist trotzdem schon zweimal in eine Abnahme gewandert

Aus der Pruefung von Paket 0076 (2026-09-05, Rolle `kern-pruefer`), Befund 3.

## Der Befund

`werkzeugkette.cmake` haelt in Zeile 787 einen Messwert fest:

> Am 2026-09-04 waren es 16 im Arbeitsbereich, 10 im Kern und 5 im Pruefstand; die
> Differenz von einem traegt `werkzeuge/belegstellen` aus `FABRIK_MITGLIEDER`.

Gemessen am 2026-09-05 mit den Schaltern des Runners (`-DCMAKE_BUILD_TYPE=RelWithDebInfo`,
`-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`), Arbeitsbereich / `kern` allein /
`pruefstand` allein, aus `git archive` in frische Baeume ausserhalb des Repos:

| Stand | `FABRIK_SANITIZER=ON` | `FABRIK_SANITIZER=OFF` |
|---|---|---|
| `HEAD` | 18 / 12 / 5 | 16 / 11 / 4 |
| `489aafb` | 18 / 12 / 5 | 16 / 11 / 4 |
| `dffb251` | 17 / 11 / 5 | 15 / 10 / 4 |

**Kein Profil und kein Stand ergibt 16 / 10 / 5.** Zwei Dinge daran sind verschieden
und beide zaehlen:

1. **Der Zahl ist ihr Profil nicht angesehen.** `kern_geprueft` und
   `pruefstand_geprueft` entstehen nur unter `FABRIK_SANITIZER=ON`; die gemessene
   Differenz zwischen den Profilen ist 2 / 1 / 1. Ein einzelnes Tripel kann also
   hoechstens fuer eines von beiden gelten -- und der Kommentar sagt nicht, fuer welches.
2. **Dem Baum wachsen Ziele zu.** Zwischen `dffb251` und `HEAD` kam unter anderem
   `kern/test/zustandsausgabe_probe.cpp` dazu. Das ist der Normalfall und kein Fehler;
   es macht die Zahl nur zu einem Wert mit Verfallsdatum.

## Warum das nicht bloss ein alter Kommentar ist

**Die Zahl ist von dort in eine Abnahme gewandert.** Bedingung 2 von Paket 0076
verlangt woertlich "die drei Bauwege ... mit Code 0 und den Zahlen 16 / 10 / 5". Der
Bauagent von 0076 durfte allein `werkzeugkette.cmake` anfassen -- die Zahl der Ziele
haengt an den Manifesten der Mitglieder. **Die Klausel war unerfuellbar, bevor das
Paket begonnen hat**, und sie war es schon am Elterncommit. Sie hat den Bauagenten
einen Absatz Rechtfertigung und die Pruefung sechs zusaetzliche Baulaeufe gekostet, und
sie hat nichts gesichert.

**Und der Zweck der Zahl ist gut.** Der Kommentar daneben begruendet sie richtig: "eine
Zahl, die von 15 auf 3 faellt, faellt genau dort auf". Ein Riegel, der die Haelfte der
Ziele durchwinkt, baut sonst gruen. Es geht also nicht darum, die Zahl zu streichen,
sondern darum, sie so hinzuschreiben, dass die naechste Abnahme sie nicht wieder als
Sollwert abschreibt.

**Warum `rolle: projektmanager` und nicht `kernbauer`:** Zu entscheiden ist zuerst, was
kuenftige Abnahmen verlangen duerfen -- eine feste Zahl, einen Vergleich gegen den
eigenen Stand davor, oder gar nichts. Erst danach steht fest, was im Kommentar stehen
muss. Ein Bauagent, der das selbst entschiede, schriebe sich seine eigene Abnahme.

**Nicht in 0103 buendeln:** Dort geht es um eine Bedingung im Code und um einen
Nichtwert; hier um eine Messgroesse und darum, wie Abnahmen sie benutzen duerfen. Beide
beanspruchen dieselbe Datei -- das ist ein Grund zu serialisieren, keiner zu buendeln.

## Was zu tun ist

1. **Entscheiden**, wie die Zielzahl kuenftig in Abnahmen vorkommt. Der Vorschlag der
   Pruefung, nicht bindend: als **Gleichheitsmass** gegen den unmittelbar vorhergehenden
   Stand desselben Profils ("dieselbe Zahl wie vorher, je Profil"), nicht als Sollwert.
   Wer eine feste Zahl will, nennt das Profil dazu und ein Datum.
2. **Den Kommentar in Zeile 787 nachziehen**, sodass er der Entscheidung entspricht:
   entweder mit den zwei heute gemessenen Tripeln und ihren Profilnamen, oder ohne
   Zahlen und mit dem Verfahren stattdessen.

**Was nicht dazugehoert:** die Meldung des Riegels umbauen; die Zahlen selbst aendern
wollen; die Abnahme von 0076 nachtraeglich umschreiben (sie ist erbracht und geprueft).

## Abnahme

1. **Die Entscheidung steht und ist begruendet.** Ein Absatz, der beide Ausgaenge
   benennt -- feste Zahl je Profil, oder Vergleich gegen den Stand davor -- und sagt,
   welcher gilt und warum. Er steht dort, wo die naechste Abnahme ihn findet.
2. **Der Kommentar in `werkzeugkette.cmake` widerspricht keiner Messung mehr.**
   Nachweis: die drei Bauwege in beiden Profilen konfiguriert, die sechs gemeldeten
   Zahlen aufgeschrieben, und keine davon steht im Widerspruch zu dem, was im Kommentar
   behauptet wird. Nennt der Kommentar danach Zahlen, nennt er auch das Profil und das
   Datum.

## Rueckläufe

0.
