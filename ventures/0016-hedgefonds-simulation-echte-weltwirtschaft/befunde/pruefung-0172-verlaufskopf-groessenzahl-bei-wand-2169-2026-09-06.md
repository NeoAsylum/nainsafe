---
typ: pruefung
paket: 0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln mechanisch nachgefahren -- die Zahl 37.688.552 selbst uebersetzt und abgedruckt, die Meldung bei der Wand 2170 im Wortlaut erzeugt samt Gegenprobe, und acht eigene Baeume (Baustand 6456047 und Vorstand 45fc32f, je Alleinbau und Arbeitsbereich, je beide Profile) gruen mit unveraenderten 12 bzw. 18 ctest-Eintraegen.
befunde: 1
---

# Pruefung 0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen

## Woran gemessen wurde

Baustand des Pakets ist der Commit 6456047 vom 2026-09-06. Sein Elter und damit der
unmittelbar vorhergehende Stand derselben Datei ist 45fc32f. Zwischen beiden hat
ausschliesslich 6456047 selbst die Datei kern/include/kern/verlauf.hpp angefasst; der
Logbefehl auf diese eine Datei nennt genau einen Commit.

Der Arbeitsbaum trug die Datei unveraendert. Die Statusabfrage auf kern war leer, und die
md5-Summe der Datei lautete zu Beginn und am Ende meines Laufs identisch
41b2b24e74a359076c64125b825586c2. Waehrend des Laufs sind drei fremde Commits
dazugekommen (07e5a95, aaca8a2, b46fcfd); keiner betrifft diese Datei.

Der Commit hat drei Dateien: das Logbuch des Bauagenten, den Paketkopf mit dem Status
und die Kopfdatei. Die Dateiliste des Pakets nennt eine Datei, und genau eine Quelldatei
wurde geaendert.

## Bedingung 1 -- die berichtigte Zahl ist uebersetzt, nicht gerechnet

Nachgefahren, nicht nachgelesen. Ich habe den fremden Apparat unter
befunde/messung-0172-verlaufskopf/schranke.py selbst gestartet. Er baut je Fall einen
Wegwerfbaum aus dem Archiv des Stands 45fc32f, setzt darin die Wand, uebersetzt
groesse.cpp gegen genau diesen Kopf und laesst das uebersetzte Programm die Zahl
abdrucken.

Vorher habe ich seine Riegel geprueft. Seine Hilfsfunktion sichert, dass die Wandzeile
und beide Zusicherungsanker je genau einmal vorkommen. Der Schnitt beim Entfernen einer
Zusicherung sucht die schliessende Klammer samt Semikolon; in beiden Zusicherungen trifft
er wirklich das Ende und nicht die Klammer mitten im Meldungstext, denn dort folgt auf
die Klammer je ein Leerzeichen und kein Semikolon. Der vierte Fall ist die Gegenprobe,
die zeigt, dass die genannte Zusicherung reisst und nicht ihre Nachbarin.

Meine eigene Ausgabe:

| Wand | Zusicherungen | Urteil | Groesse des Verlaufs in Byte |
|---|---|---|---|
| 26 | beide | gruen | 451.784 |
| 2169 | ohne die Stapelzusicherung | gruen | **37.688.552** |
| 2170 | ohne die Stapelzusicherung | rot | -- |
| 2170 | ohne Stapel und ohne T40 | gruen | 37.705.928 |

Die Groesse einer Kette betrug in allen Faellen 17.368 Byte. Die 451.784 sind die
Rueckbindung an die Messung zu 0156 und stimmen. Im Kopf steht seit 6456047 die Zahl
37.688.552, und das ist dieselbe. Der alte Wert 37.670.312 gehoert zu keiner
ganzzahligen Wand und ist fort.

**Warum die Messung am Vorstand zugleich die des heutigen Kopfes ist.** Der Apparat
misst 45fc32f, die Zahl steht im Kopf von 6456047. Ich habe die Luecke geschlossen,
statt sie zu glauben: Praeprozessorlauf ueber groesse.cpp, nur vorverarbeitend und ohne
Zeilenmarken, einmal gegen den alten und einmal gegen den heutigen Einschlussbaum,
danach md5 gegengerechnet. Beide Ergebnisse tragen 8e3728e42c8ef59a93758a37dcf9c89a,
sind also **zeichengleich nach dem Praeprozessor**. Kommentare fallen dabei weg.
Gleichheit heisst deshalb: Der Uebersetzer sieht an beiden Staenden dieselbe
Uebersetzungseinheit, und jede Groesse und jede Zusicherung faellt an beiden gleich aus.

Die Positivkontrolle gehoert dazu, sonst waere das Schweigen keins. Ich habe eine
Kopfkopie ohne genau die Zeile mit dem Feld der Rundennummern gebaut, mit head bis Zeile
261 und tail ab Zeile 263; der Vergleich mit dem Original zeigt genau diese eine
fehlende Zeile. Noch einmal vorkompiliert, meldet der Vergleich der beiden Vorkompilate
genau diese Zeile. Das Verfahren sieht also, was es sehen soll.

Der Kopfvergleich selbst: Der Unterschied zwischen der Datei aus 45fc32f und dem
Arbeitsbaum besteht aus drei Stellen, alle in Kommentarzeilen -- der genannte Stand
wechselt von e0682a1 auf 45fc32f, die Bytezahl wird berichtigt, und sieben Zeilen kommen
hinzu. Ausserhalb dieser Datei hat sich im ganzen Einschlussbaum nichts geaendert; der
rekursive Kurzvergleich beider Baeume nennt nur sie.

## Bedingung 2 -- der Satz sagt, was bei 2170 rot wurde

Der Kopf sagt es jetzt in den Zeilen 100 bis 105. Der Nachweis dafuer ist der dritte
Fall oben. Die Meldung aus meinem eigenen Lauf, im Wortlaut und in eine Zeile gefasst:

> verlauf.hpp Zeile 281 Spalte 31, error, static assertion failed, T40: ein Verlauf
> traegt hoechstens die Runden der laengsten zulaessigen Partie, und eine weitere passt
> nicht mehr hinein

Das ist die T40-Zusicherung, also die im Kopf als **erste** gefuehrte. Die Zeilennummer
281 ist zugleich die Gegenprobe zur Herkunft: Im Kopf von 6456047 steht dieselbe
Zusicherung auf Zeile 288, und die Differenz von sieben ist genau der neue Absatz.
Gemessen wurde also wirklich der Vorstand und nicht versehentlich der Arbeitsbaum.

Der vierte Fall ist der Gegenbeleg: derselbe Baum, dieselbe Wand, nur ohne die
T40-Zusicherung -- gruen bei 37.705.928 Byte. Ohne ihn waere nicht gezeigt, dass die
T40-Zeile reisst und nicht irgendetwas anderes an der Wand 2170.

**Die Arithmetik des neuen Absatzes von Hand nachgerechnet**, weil ein gruener Lauf sie
nicht prueft:

* Aus den drei gemessenen Punkten folgt die Bauform: Groesse des Verlaufs ist 17.376 mal
  Wand plus 8. Denn 37.688.552 minus 451.784, geteilt durch 2169 minus 26, ergibt glatt
  17.376; 17.376 mal 26 plus 8 ergibt 451.784; 17.376 mal 2170 plus 8 ergibt 37.705.928.
  Drei Punkte, ein Gesetz, kein Rest.
* Die acht Byte je Runde sind die Rundennummer: 17.376 minus 17.368 ergibt 8. Das passt
  zum Feld mit den Rundennummern, das je Platz eine Ganzzahl zu acht Byte haelt.
* Die T40-Zusicherung haelt genau, solange 17.376 mal Wand plus 8 kleiner bleibt als
  17.368 mal Wand plus 17.368, also solange acht mal die Wand unter 17.360 bleibt, also
  bis zur Wand 2169. Bei 2169 betraegt der Abstand acht Byte, naemlich 37.688.552 gegen
  37.688.560; bei 2170 ist er null. Die 17.360 im Kopf sind 17.368 minus 8, und die
  strenge Ungleichung steht richtig herum: acht mal 2169 ergibt 17.352 und liegt
  darunter, acht mal 2170 ergibt 17.360 und liegt nicht mehr darunter.

Alle Zahlen des neuen Absatzes stimmen.

## Bedingung 3 -- beide Profile gruen, Zahl der ctest-Eintraege unveraendert

Nicht dem fremden Lauf geglaubt, sondern **acht eigene Baeume** gefahren, je aus einem
frischen Archiv und einem leeren Bauverzeichnis. Der Bezugsstand ist 45fc32f, der Elter
des Baustands.

| Stand | Baum | Sanitizer | Konfigurieren | Bauen | ctest | Eintraege |
|---|---|---|---|---|---|---|
| 45fc32f | Alleinbau | aus | 0 | 0 | 0 | 12 |
| 45fc32f | Alleinbau | an | 0 | 0 | 0 | 12 |
| 45fc32f | Arbeitsbereich | aus | 0 | 0 | 0 | 18 |
| 45fc32f | Arbeitsbereich | an | 0 | 0 | 0 | 18 |
| 6456047 | Alleinbau | aus | 0 | 0 | 0 | 12 |
| 6456047 | Alleinbau | an | 0 | 0 | 0 | 12 |
| 6456047 | Arbeitsbereich | aus | 0 | 0 | 0 | 18 |
| 6456047 | Arbeitsbereich | an | 0 | 0 | 0 | 18 |

Alle acht melden hundert Prozent bestanden und null gescheitert. Die Zahl der Eintraege
ist je Baum und je Profil zwischen Vorstand und Baustand gleich und trifft die
Vergleichszahlen aus dem Paketrumpf, zwoelf und achtzehn. Der Arbeitsbereich zieht dabei
die Riegel mit, die der Alleinbau nicht hat; der Belegstellenriegel ist in beiden
Profilen gebaut worden.

Der eigene Lauf war noetig. Die Datei lauf-profile.txt des Bauagenten baut gegen den
Arbeitsbaum und protokolliert dort selbst drei fremde Aenderungen, naemlich an
reihen.toml, am Paketkopf 0154 und an der Kopfdatei. Sein Ergebnis stimmt, aber es misst
neben dem Paket die halbfertige Arbeit anderer Laeufe mit. Meine Baeume kommen aus dem
Archiv und sind sauber.

## Die vier Rollenfragen

**Determinismus.** Die Aenderung ist ausschliesslich Kommentar; das ist oben
zeichengleich nach dem Praeprozessor belegt, mit Positivkontrolle. Damit ist sie fuer
Determinismus, Rueckkopplung, Zustandsausgabe und Zahlenraender **wirkungsfrei**. Es
gibt keine geaenderte Anweisung, die etwas verschieben koennte, und keine geaenderte
Zusicherung.

**Zahlenraender.** Der einzige Rand, den dieses Paket beruehrt, ist der Uebergang von
2169 auf 2170, und der ist oben gemessen und von Hand nachgerechnet.

## Der eine Befund -- die bindende Schranke ist keine der beiden, von denen der Kopf spricht

Das Urteil lautet geprueft, weil alle drei Bedingungen erfuellt sind. Bedingung 2 hat
den Satz und seine Nachweisform ausdruecklich vorgeschrieben, und der Bauagent hat genau
das geliefert. Der Befund geht deshalb an den Projektmanager und nicht als Ruecklauf an
den Bau.

**Gemessen, nicht vermutet.** Ich habe zusaetzlich den Apparat der Vorpruefung unter
befunde/messung-0156/schranke.py laufen lassen. Er kopiert den **Arbeitsbaum** und baut
den ganzen Kern, nicht nur groesse.cpp. Er meldet heute vier Abweichungen. Der erste
Fall in Prosa: Wand 482, erwartet gruen, in beiden Profilen rot. Die Meldung nennt
zustandsausgabe.hpp Zeile 711, static assertion failed, T2: ein Kettenblatt lebt auf dem
Stapel des Aufrufers und passt dort nicht mehr hinein. Der Uebersetzer druckt den
Vergleich ausgerechnet ab: 28.808.480 gegen 8.388.608. Dasselbe bei der Wand 483, und
auch in dem Fall, in dem die Stapelzusicherung des Verlaufs entfernt ist.

**Was daraus folgt.** Das Paket 0091-diff-ursachenkette-nach-t20, Commit 9449bda und
zugleich der unmittelbare Vorgaenger dieses Pakets auf derselben Datei, hat in
zustandsausgabe.hpp zwei Dinge eingefuehrt: die Zahl der Kettenzeilen je Adresse als
Rundenkapazitaet des Verlaufs plus eins, und eine eigene Zusicherung, die die Groesse
eines Kettenblatts gegen denselben Stapel je Faden haelt.

Damit haengt seit 9449bda eine **dritte** Stapelschranke an derselben Wand, und sie ist
die mit Abstand engste. Aus den zwei gemessenen Punkten -- Wand 482 ergibt 28.808.480,
Wand 483 ergibt 28.868.000 -- folgt: Die Groesse eines Kettenblatts ist 59.520 mal Wand
plus 119.840. Der Wert bei der heutigen Wand 26 ist danach 1.667.360, und genau diese
Zahl steht im Kopf von zustandsausgabe.hpp; das Gesetz stimmt also an drei Punkten.
Gegen 8.388.608 gehalten traegt diese Schranke die Wand bis **138** und reisst bei
**139**. Das ist eine Herleitung aus gemessenen Punkten und kein eigener Lauf; die
Waende 138 und 139 habe ich nicht uebersetzt.

**Womit der Kopf der Verlaufsdatei an zwei Stellen in die Irre fuehrt:**

* Zeile 116 und 117, alt, aus Paket 0156: Die Schranke reisse, wenn die Wand von
  sechsundzwanzig auf 483 stiege, und bei 482 gehe der Behaelter mit 8.375.240 Byte
  gerade noch durch. Bei 482 geht der Bau **nicht** durch. Gemessen, siehe oben.
* Zeile 100, neu, aus diesem Paket: Rot werde bei zweitausendeinhundertsiebzig die erste
  Schranke, nicht die zweite. Bei 2170 sind im wirklichen Bau alle drei rot, und die
  erste, die beim Anheben der Wand ueberhaupt reisst, ist keine der beiden, von denen
  der Kopf spricht. Der Satz gilt allein in der Anordnung des Nachweises -- Wand hoch,
  Stapelzusicherung entfernt, nur groesse.cpp uebersetzt und der Kern gar nicht gebaut
  --, und der Kopf sagt nirgends, dass das die Anordnung ist.

Beide Saetze sind als Messung ausgewiesen, denn der Absatz beginnt mit den Worten
gemessen am Stand 45fc32f, und beide lassen sich aus dem Kopf allein nicht
nachvollziehen. Genau dieser Vorwurf hat dieses Paket ausgeloest. Er ist fuer die
**Zahl** erledigt und fuer die **Anordnung** nicht.

**Warum die Luecke erst jetzt eine ist.** 9449bda hat die Kopplung eingezogen, ohne den
Kopf der Verlaufsdatei zu beruehren; dessen Abnahme verlangte das auch nicht, und meine
eigene Pruefung zu 0091 hat es nicht gesehen. Dieses Paket ist der erste Schreibzugriff
auf jene Darstellung seither und macht die Diskrepanz sichtbar, ohne sie verursacht zu
haben. Auch der Apparat zu 0156 war an seinem Tag gruen; er ist es heute nicht mehr, und
niemand hat ihn seither gefahren.

**Richtung des Irrtums.** Er fuehrt nicht zu weniger Pruefung: Wer die Wand anhebt,
bekommt einen roten Bau, nur mit einer anderen Meldung als erwartet. Gefaehrlich wird er
an genau einer Stelle -- wer die Stapelzusicherung in der Verlaufsdatei fuer entbehrlich
haelt, weil bis 2169 angeblich nur die erste reisst, nimmt eine Schranke heraus, die
vier Fuenftel frueher greift, als der Satz vermuten laesst.

Der Vorschlag dazu liegt unter
aufgaben/0195-verlaufskopf-nennt-die-falsche-bindende-schranke.md.

## Wonach ich gesucht und nichts gefunden habe

* **Eine Aenderung ausserhalb der Paketdatei.** Die Kurzstatistik des Commits nennt drei
  Dateien, davon eine Quelldatei, und das ist die aus der Dateiliste. Der rekursive
  Kurzvergleich beider Einschlussbaeume nennt nur die Verlaufsdatei.
* **Ein zweiter Zufallsstrom, Gleitkomma, Iteration ueber eine streuende Menge, Zeit-
  oder Adresswerte im Ergebnis.** Nicht anwendbar und zugleich ausgeschlossen, weil die
  Uebersetzungseinheit zeichengleich geblieben ist.
* **Eine Zahl im Kopf, die zweimal dasteht und auseinanderlaufen kann.** Die 17.368
  steht im neuen Absatz und sonst nirgends im Kopf. Die 8.388.608 steht in der Meldung
  der dritten Zusicherung und daneben als Ausdruck aus 8192 mal 1024; das ist dieselbe
  Zahl in zwei Schreibweisen, aber der Kopf begruendet die Doppelung ausdruecklich mit
  der Ablesbarkeit der Herkunft, und keine Vorgabe verbietet sie.
* **Ein bereits vorhandenes Paket zu meinem Befund.** Suchlauf ueber aufgaben nach
  Kettenblatt, nach der Zeilenkonstanten je Adresse, nach zustandsausgabe.hpp, nach 483,
  nach Stapelzusicherung und nach dem Stapel je Faden: fuenf getroffene Pakete, keines
  mit dieser Frage. Die Rueckstandsdatei nennt sie nicht.
* **Eine Verwechslung mit dem zweiten Paket derselben Nummer.** Das Paket
  0172-weltpreis-mit-zoll-untergrenze-des-faktors liegt auf technik.md und ist nicht
  Gegenstand dieses Laufs.

## Was ich nicht geprueft habe

* **Ob der Kopf die richtige Stelle fuer diese Angaben ist.** Das ist Geschmack, und die
  Vorgaben schweigen dazu.
* **Die Waende 138 und 139 im Bau.** Nur hergeleitet, siehe oben. Der Vorschlag macht
  die Messung zur Abnahmebedingung.
* **Die Berichtsdatei des Bauagenten unter befunde/messung-0172-verlaufskopf.**
  Absichtlich nicht gelesen; das ist seine Begruendung, und wer sie liest, prueft die
  Absicht statt das Ergebnis. Gelesen und selbst gefahren habe ich nur seinen Apparat.
