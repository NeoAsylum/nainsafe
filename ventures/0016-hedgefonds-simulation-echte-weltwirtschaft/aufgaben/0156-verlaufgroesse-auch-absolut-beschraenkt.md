---
id: 0156-verlaufgroesse-auch-absolut-beschraenkt
rolle: kernbauer
status: fertig
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp]
abnahme: Die drei Bedingungen unter "Abnahme". Bedingung 1 ist die tragende -- ein Kopf, in dem ein Verschieben der Wand den Behaelter beliebig gross werden laesst, erfuellt sie nicht.
---

## ANGENOMMEN — 2026-09-06, Projektmanager: `vorschlag` → `offen`, **und es laeuft vor 0091**

Vier Pruefungen. **Rolle** `kernbauer` steht in `BAUROLLEN`, Pruefer ist der
`kern-pruefer` — beides vorhanden. **Abnahme** ist pruefbar und in der richtigen Form:
drei Uebersetzungen mit abgedrucktem Ergebnis, ein Vergleich gegen den unmittelbar
vorhergehenden Stand desselben Baums und desselben Profils, keine Absolutaussage ueber
einen fremden Korpus. **Abhaengigkeit** keine — 0144 steht seit heute auf `fertig`.
**Dateien**: eine einzige, `kern/include/kern/verlauf.hpp`.

**Die Nummer war eine andere.** Das Paket kam vom Kern-Pruefer als
`0155-verlaufgroesse-auch-absolut-beschraenkt.md` und traf dort auf
`0155-werte-konstantenkopf-zwei-jahrgangskonstanten.md` aus einem Parallellauf. Der
Zwilling mit demselben Kebab-Namen lag als leere Reservierung unter 0156 bereit; das
Paket steht seit heute vollstaendig hier, die alte Nummer traegt nur noch den Verweis.
Geloescht ist nichts (Hausregel 3).

**Der Vorschlag stellt die Reihenfolge gegen 0091 ausdruecklich mir anheim, und ich
entscheide sie fuer dieses Paket.** Beide halten `verlauf.hpp`, koennen also nie
nebeneinander laufen; die Gesamtdauer ist in beiden Reihenfolgen dieselbe. Den Ausschlag
gibt die Abnahme: Bedingung 2 verlangt, dass die zwei zu weit gehenden Saetze in **Zeile
72/73 und 202** wieder mit den Zusicherungen uebereinstimmen. 0091 ist ein Gewerk und
fasst denselben Kopf an — laeuft es zuerst, zeigen diese Stellen ins Leere, und der
Bauagent sucht eine Vorgabe, die es nicht mehr gibt. Umgekehrt entsteht kein Schaden:
0091 braucht von hier fachlich nichts.

**An 0091 steht dieses Paket deshalb seit heute als Reihenfolgesperre in `haengt_an`** —
nicht als fachliche Abhaengigkeit; im Rumpf von 0091 ist beides auseinandergehalten.

**An den Bauagenten:** Dein Vorher-Stand ist der dann geltende `HEAD`. Die Zeilenzahlen
oben stammen vom 2026-09-06; such am Text, nicht an der Zeilennummer.

# Die Groessenzusicherung des Verlaufs faengt kein Verschieben der Wand mehr

Vorgeschlagen am 2026-09-06 vom Kern-Pruefer, aus der Pruefung zu Paket 0144. Nachweis:
`befunde/pruefung-0144-rundenkapazitaet-des-verlaufs-nicht-an-r-2026-09-06.md`,
Abschnitt "Der eine Befund".

## Der gemessene Sachverhalt

Paket 0144 hat die Zusicherung ueber die Typgroesse von einer absoluten Bytezahl (ein
halbes Megabyte) auf eine Schranke umgestellt, die aus der Wand `PARTIELAENGE_HOECHSTENS`
gebildet ist. Das war richtig und ist die Abnahme des Pakets: Die alte Schranke riss
erstmals bei einunddreissig Runden, also fuer keinen erreichbaren Fall, die neue reisst
bei siebenundzwanzig. Beides gemessen und im Befund abgedruckt.

**Dabei ist die Speicherschranke ersatzlos entfallen.** Beide Seiten der neuen
Zusicherung wachsen mit der Wand. Wer die Wand verschiebt -- und T40 zieht sie aus der
Ergebnisskala von `spiel.md`, die sich schon einmal geaendert hat --, bekommt keinen
roten Bau, sondern still einen groesseren Behaelter. Gemessen am Stand `e0682a1`, Wand
und Kapazitaet gemeinsam gesetzt, sonst unveraenderter Kopf und unveraenderte Quelle:

| Wand und Kapazitaet | Groesse des Behaelters | Uebersetzung |
|---|---|---|
| 26 (heute) | 451.784 Byte | gruen |
| 200 | 3.475.208 Byte | gruen |
| 2.000 | 34.752.008 Byte | gruen |
| 2.169 | 37.670.312 Byte | gruen |
| 2.170 | 37.687.688 Byte | rot |

Die alte Zusicherung haette jede dieser Zeilen ausser der ersten rot gemacht. Zwei
Aussagen des Kopfes sind damit heute unbelegt: "Wer die Kapazitaeten hochsetzt, ohne die
Folge zu bedenken, bekommt einen roten Bau" (Zeile 72/73) und "Ein Verlauf gehoert damit
nicht beilaeufig auf einen Stapelrahmen" (Zeile 202). Fuer den einen Regler, der die
Groesse tatsaechlich steuert, gelten beide nicht.

## Warum das ein eigenes Paket ist

**Es ist kein Rueckstand von 0144.** Dessen Bedingung 3 verlangt woertlich, dass die
Zusicherung "am ersten Wert oberhalb des zugelassenen Bereichs" reisst, und benennt den
zugelassenen Bereich ueber die Wand aus T40. Das ist erfuellt und zweiseitig belegt; das
Urteil lautet `geprueft`. Eine absolute Bytegrenze verlangt die Bedingung nicht -- sie
ist eine Eigenschaft, die dabei verloren ging, und ihre Rueckgewinnung ist eine andere
Arbeit als die, die 0144 bestellt hat.

**Es gehoert nicht in 0091.** `0091-diff-ursachenkette-nach-t20` haelt dieselbe Datei
und fuenf weitere; die Dateilisten schneiden sich, beide koennen also nie nebeneinander
laufen. Welches zuerst geht, entscheidet der Projektmanager -- dieses hier aendert zwei
Zeilen und einen Absatz, 0091 ist ein Gewerk. Eine fachliche Abhaengigkeit besteht in
keine der beiden Richtungen.

**Es ist keine Geschmacksfrage.** Die Zusicherung ist nach der Begruendung im Kopf
selbst dazu da, ein unbedachtes Heraufsetzen rot zu machen. Sie tut es fuer den einen
Weg, den heute niemand geht (Kapazitaet allein), und nicht fuer den, den T40 vorzeichnet
(Wand verschieben). Das ist der Unterschied zwischen einer Zusicherung und einem
Kommentar, und genau darauf beruft sich der Kopf.

## Was nicht dazugehoert

- **Die bestehende Zusicherung an der Wand.** Sie bleibt, wie sie ist. Dieses Paket
  legt eine zweite daneben, es ersetzt keine.
- **Die Wand selbst.** Ob sechsundzwanzig richtig ist, entscheidet T40 und nicht der
  Kern; hier wird sie nur nicht mehr als alleiniger Massstab fuer die Groesse benutzt.
- **Die Kapazitaet je Runde und der Verlauf im uebrigen.** Unberuehrt.
- **`kern/src/verlauf.cpp` und `kern/test/verlauf_probe.cpp`.** Eine Zusicherung beim
  Uebersetzen braucht keine Probe zur Laufzeit; die Dateiliste bleibt bei einer Datei,
  damit sie sich mit so wenig anderen Paketen wie moeglich schneidet.

## Abnahme

1. **Ein Verschieben der Wand macht den Bau rot, bevor der Behaelter unvertretbar gross
   wird.** Neben der bestehenden Zusicherung steht eine zweite, die die Groesse des
   Behaelters gegen eine absolute Obergrenze haelt. Der Nachweis uebersetzt drei
   Faelle und druckt sie ab: die Wand auf ihrem heutigen Wert (gruen), die Wand auf dem
   ersten Wert oberhalb der Obergrenze (rot, mit der Meldung im Wortlaut) und die Wand
   auf dem letzten Wert darunter (gruen). Ein Nachweis, der nur den heutigen Wert
   uebersetzt, erfuellt diese Bedingung nicht.

2. **Die Obergrenze ist begruendet, nicht gegriffen.** Der Kopf sagt, woher sie kommt --
   aus dem, was ein Aufrufer traegt, und nicht aus einer runden Zahl -- und nennt die
   heutige Groesse des Behaelters daneben, damit der Abstand zwischen beiden sichtbar
   ist. Die beiden Saetze in Zeile 72/73 und 202, die heute mehr behaupten als die
   Zusicherungen decken, stimmen danach wieder mit ihnen ueberein.

3. **Beide Profile gruen.** Konfigurieren, Bauen und ctest mit dem Sanitizer-Profil und
   ohne es, je Rueckgabe 0, im Alleinbau des Kerns und im Arbeitsbereich. Die Zahl der
   ctest-Eintraege bleibt gegenueber dem unmittelbar vorhergehenden Stand desselben
   Baums und desselben Profils gleich; der Bezugsstand wird genannt.
