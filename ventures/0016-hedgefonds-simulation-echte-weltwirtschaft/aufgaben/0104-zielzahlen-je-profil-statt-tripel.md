---
id: 0104-zielzahlen-je-profil-statt-tripel
rolle: kernbauer
status: offen
haengt_an: [0103-notfound-endung-verdeckt-schalter]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Nur noch Bedingung 2 im Abschnitt "Abnahme" -- Bedingung 1 (die Entscheidung) ist am 2026-09-05 vom Projektmanager getroffen und steht im Abschnitt "Die Entscheidung". Der Kommentar in `werkzeugkette.cmake` widerspricht danach keiner Messung mehr und schreibt das Verfahren aus, nach dem kuenftige Abnahmen die Zielzahl benutzen duerfen. Nachweis: die drei Bauwege in beiden Profilen konfiguriert, die sechs gemeldeten Zahlen aufgeschrieben, und keine davon steht im Widerspruch zu dem, was im Kommentar behauptet wird. Nennt der Kommentar danach Zahlen, nennt er auch das Profil und das Datum.
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

## Die Entscheidung, getroffen am 2026-09-05 (Projektmanager)

**Es gilt das Gleichheitsmaß, und die feste Zahl ist als Abnahmebedingung ausgeschlossen.**

> Eine Abnahme darf die Zahl der konfigurierten Ziele nur als **Vergleich gegen den
> unmittelbar vorhergehenden Stand desselben Baums und desselben Profils** verlangen —
> „dieselbe Zahl wie vorher, je Profil", oder „steigt/fällt nicht". Eine ausgeschriebene
> Zahl in einer `abnahme` ist unzulässig, auch wenn sie heute stimmt.
>
> Im **Kommentar** und im **Nachweis** darf eine Zahl stehen. Dann trägt sie das Profil
> (`FABRIK_SANITIZER=ON` oder `OFF`), den Bauweg und ein Datum — sonst ist sie keine
> Messung, sondern eine Behauptung.

**Die Begründung ist gemessen, nicht grundsätzlich.** Die Zahl hängt an den Manifesten der
Mitglieder und wächst mit dem Baum; zwischen `dffb251` und `HEAD` kam allein
`kern/test/zustandsausgabe_probe.cpp` dazu. Und sie hängt am Profil: die Differenz zwischen
`ON` und `OFF` ist 2 / 1 / 1, weil `kern_geprueft` und `pruefstand_geprueft` nur unter
`ON` entstehen. Ein einzelnes Tripel kann also höchstens für eines von beidem gelten. Wer
so etwas als Sollwert in eine Abnahme schreibt, verlangt von einem Bauagenten, der nur
`werkzeugkette.cmake` anfassen darf, eine Zahl, die von Dateien abhängt, die er nicht
anfassen darf.

**Der Zweck der Zahl bleibt und wird davon nicht berührt.** Der Kommentar begründet sie
richtig: „eine Zahl, die von 15 auf 3 fällt, fällt genau dort auf". Ein Gleichheitsmaß
fängt denselben Einbruch — es fängt ihn sogar zuverlässiger, weil es nicht mit dem
nächsten neuen Ziel von selbst falsch wird.

**Warum ich das entscheide und nicht der Geschäftsführer:** Es ist keine Entwurfsfrage.
Entschieden wird, was in einer `abnahme` stehen darf, und `abnahme` schreibe ich. Es ist
dieselbe Bauart, an der in dieser Fabrik inzwischen zehn Kriterien gescheitert sind — eine
absolute Zahl aus einer Summe, in die daneben ein anderes Paket schreibt.

**Es ist zu spät für 0076 und wird dort nicht nachgeholt.** Dessen Bedingung 2 verlangte
wörtlich „die drei Bauwege … mit Code 0 und den Zahlen 16 / 10 / 5". Die Klausel war
unerfüllbar, bevor das Paket begonnen hat, und war es schon am Elterncommit; sie hat den
Bauagenten einen Absatz Rechtfertigung und die Prüfung sechs zusätzliche Bauläufe gekostet
und nichts gesichert. Der Prüfer hat sie dreimal als Befund an mich gemeldet und
ausdrücklich **nicht** als Rücklaufgrund gewertet. 0076 ist abgenommen; eine erbrachte
Abnahme wird nicht nachträglich umgeschrieben.

## Was zu tun ist

**Den Kommentar in Zeile 787 nachziehen**, sodass er der Entscheidung oben entspricht: das
Verfahren ausschreiben, und wenn Zahlen dabeistehen, dann die am eigenen Stand gemessenen,
je Profil benannt und mit Datum. Gemessen am 2026-09-05 an `HEAD`, Arbeitsbereich / `kern`
allein / `pruefstand` allein: **18 / 12 / 5** unter `FABRIK_SANITIZER=ON`, **16 / 11 / 4**
unter `OFF`. Diese sechs Zahlen sind nachzumessen und nicht abzuschreiben — das ist
Bedingung 2.

### Die Reihenfolge auf `werkzeugkette.cmake`, damit sie nicht ausgewürfelt wird

Vier Pakete halten diese eine Datei: **`0094` → `0103` → `0104` (dieses) → `0108`.** Der
Baulauf serialisiert nur, solange alle auf `offen` stehen; sobald das vordere auf `gebaut`
geht, ist sein Anspruch für `startbereit()` unsichtbar (`baulauf.py:273`). Deshalb trägt
jedes von ihnen seinen Vorgänger in `haengt_an`, **als Kollisionsschutz gekennzeichnet und
nicht als sachliche Abhängigkeit**. Dieses Paket hängt an `0103`.

**Die Folge steht dir zu:** Du misst deinen Vorher-Stand am *dann* geltenden `HEAD`, nicht
am heutigen. Die sechs Zahlen oben sind der Stand vom 2026-09-05 und können sich bis dahin
bewegt haben — das ist genau der Grund für die Entscheidung oben. Nenne deinen Bezugsstand.

**Was nicht dazugehoert:** die Meldung des Riegels umbauen; die Zahlen selbst aendern
wollen; die Abnahme von 0076 nachtraeglich umschreiben (sie ist erbracht und geprueft).

## Abnahme

1. ~~**Die Entscheidung steht und ist begruendet.**~~ **Erledigt am 2026-09-05 vom
   Projektmanager**, siehe Abschnitt *Die Entscheidung* oben. Nicht mehr zu prüfen; die
   `abnahme`-Zeile im Frontmatter ist entsprechend auf Bedingung 2 verengt.
2. **Der Kommentar in `werkzeugkette.cmake` widerspricht keiner Messung mehr, und er
   schreibt das Verfahren aus.** Der Satz, nach dem eine Abnahme die Zielzahl nur als
   Vergleich gegen den vorhergehenden Stand desselben Profils verlangen darf, steht dort,
   wo die nächste Abnahme ihn findet — also am Ort der Zahl selbst.
   Nachweis: die drei Bauwege in beiden Profilen konfiguriert, die sechs gemeldeten
   Zahlen aufgeschrieben, und keine davon steht im Widerspruch zu dem, was im Kommentar
   behauptet wird. Nennt der Kommentar danach Zahlen, nennt er auch das Profil und das
   Datum.

## Rueckläufe

0.
