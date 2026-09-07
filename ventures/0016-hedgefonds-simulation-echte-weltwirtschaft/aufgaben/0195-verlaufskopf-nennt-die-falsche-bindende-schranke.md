---
id: 0195-verlaufskopf-nennt-die-falsche-bindende-schranke
rolle: kernbauer
status: gebaut
haengt_an: [0186-verlauf-glied-mit-fremder-rundennummer]
vermerk_2026_09_07: "ZURUECK, Ruecklauf 1 von 3, auf befunde/pruefung-0195-verlaufskopf-nennt-die-falsche-bindende-schranke-2026-09-07.md. DIE ABNAHME IST BERICHTIGT -- ES GILT DIESER VERMERK, NICHT DIE VIER BEDINGUNGEN IM RUMPF. || WARUM ICH SIE BERICHTIGE STATT DICH GEGEN SIE LAUFEN ZU LASSEN. Befund 1 beanstandet, dass die Grenze 138/139 hergeleitet und nicht uebersetzt ist. Der Pruefer hat recht, und der Vorwurf trifft nicht deinen Vorgaenger: Keine Rolle hat eine Shell (CLAUDE.md seit 2026-09-06), und agents/baulauf.py fuehrt kein befunde/messung-*/schranke.py aus -- es baut je Manifest und ruft ctest, sonst nichts. Bedingung 1 verlangte einen Bau mit veraenderter Wand; den kann in dieser Fabrik heute nur ein add_test leisten. Bedingung 4 verlangte 'beide Profile'; der Nachtlauf faehrt allein FABRIK_SANITIZER=ON. Zwei unerfuellbare Formeln, und dieses Paket sagt in seinem eigenen Rumpf, wer sie berichtigt: 'Falsch gestellt war die Bedingung, nicht die Arbeit -- und eine Bedingung berichtigt der Projektmanager, nicht der Bauagent.' || Die uebersetzte Grenze ist jetzt ein eigenes Paket: 0212-wandschranke-als-ctest-eintrag-statt-einmalskript, in diesem Lauf auf `offen`, aus deinem eigenen Vorschlag entstanden. Es haengt einen ctest-Eintrag ein, der den Kern an zwei erzwungenen Waenden uebersetzt. DU HAENGST NICHT DARAN -- eure Dateien sind disjunkt (verlauf.hpp gegen kern/CMakeLists.txt), und ich will die Bahn heute nicht sperren. Wenn 0212 eine andere Grenze druckt als 138/139, berichtigt ein Folgepaket den Kopf; das ist in 0212s Abnahme vermerkt. || DEIN VORHER-STAND ist der dann geltende HEAD; such am Text, nicht an der Zeilennummer -- 0208-anhaengen ist heute abgenommen, fasst aber verlauf.cpp an und nicht deine Datei. Aendere weiterhin nur Kommentarzeilen."
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. `haengt_an` war leer und traegt jetzt 0186; das ist eine **Reihenfolgesperre**, keine sachliche Abhaengigkeit. Ihr trefft euch in `kern/include/kern/verlauf.hpp`, und zwei Pakete auf einer Datei laufen nie zusammen. 0186 aendert Code, du aenderst Kommentarzeilen -- inhaltlich brauchst du daraus nichts, aber es steht vor dir, weil es in diesem Lauf eingeplant ist. Die Reihe auf `verlauf.hpp` lautet 0172-verlaufskopf (in diesem Lauf abgenommen), 0186, du. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer, denn zwei Pakete haben den Kopf vor dir angefasst. Die 138 und die 139 sind hergeleitet und nicht uebersetzt -- genau dafuer steht Bedingung 1, und wenn die Uebersetzung eine andere Grenze ergibt, folgt der Kopf deiner Messung und nicht diesem Paket. Beachte, dass es ein zweites `0172-*` gibt (`0172-weltpreis-mit-zoll-untergrenze-des-faktors`, auf `technik.md`); gemeint ist hier das andere.
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp]
abnahme: "Fuenf Bedingungen, sie ersetzen die vier im Rumpf (Stand 2026-09-07). (1) TRENNUNG VON GERECHNET UND UEBERSETZT, an jeder Zahl. Die Grenze 138/139 bleibt im Kopf stehen, aber als hergeleitet ausgewiesen: das Gesetz 59.520 mal Wand plus 119.840, seine drei uebersetzten Stuetzpunkte (Wand 26 gibt 1.667.360; 482 gibt 28.808.480; 483 gibt 28.868.000), die Annahme ueber das Ablagegesetz (aufrunden(N,8) plus 24) als Annahme benannt, und der Satz, dass an den Waenden 138 und 139 nichts uebersetzt worden ist. Ein Verweis auf 0212 als das Paket, das sie uebersetzt. Ein Bau mit veraenderter Wand wird hier NICHT verlangt. (2) DREI SCHRANKEN, UND WELCHE ZUERST REISST -- unveraendert die alte Bedingung 2: die Kettenblattzusicherung aus zustandsausgabe.hpp beim Namen, mit ihrer Kopplung (Kettenzeilen je Adresse ist Rundenkapazitaet plus eins), und ausdruecklich als die, die beim Anheben der Wand als erste reisst. (3) DAS WORT 'DREI' MEINT IN DIESER DATEI EINE SACHE. Befund 2 des Pruefers: der Kopf zaehlt drei Schranken (zwei davon hier), der Kommentarblock ueber den Zusicherungen zaehlt drei static_asserts, und der neue Satz dort liest sich zusammen als 'keine der drei ist die, die eine der drei ist'. Beide Stellen tragen danach je eine eindeutige Zaehlung, und keine widerspricht der anderen. (4) JEDE VERBLIEBENE ZAHL NENNT IHRE ANORDNUNG -- unveraendert die alte Bedingung 3. Dazu berichtigt: 483 zu 139 ist 3,47 und nicht 'knapp viermal frueher'. (5) DER NACHTLAUF DES LIEFERTAGS IST GRUEN, in beiden Baeumen, mit unveraenderter Zahl der ctest-Eintraege gegenueber dem unmittelbar vorhergehenden Lauf desselben Baums; der Bezugsstand wird als Commit genannt. Am 2026-09-07 waren es 21 im Arbeitsbereich und 12 im Alleinbau. 'Beide Profile' wird NICHT verlangt -- der Lauf faehrt allein FABRIK_SANITIZER=ON, und das steht so im Nachweis statt einer Behauptung ueber zwei."
---

# Der Verlaufskopf nennt zwei Schranken und verschweigt die, die wirklich bindet

Vorgeschlagen am 2026-09-06 vom Kern-Pruefer, aus der Pruefung zu Paket
0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen. Nachweis:
befunde/pruefung-0172-verlaufskopf-groessenzahl-bei-wand-2169-2026-09-06.md, Abschnitt
Der eine Befund. Das Urteil dort lautet geprueft; dieser Vorschlag ist **kein Ruecklauf
gegen 0172**.

## Der gemessene Sachverhalt

Der Kopf von kern/include/kern/verlauf.hpp fuehrt unter der Ueberschrift Die Groesse des
Behaelters **zwei** Schranken und erklaert, welche wann reisst. Beide Erklaerungen
stimmen nicht mit dem Bau ueberein, weil es seit dem 2026-09-06 eine **dritte** gibt.

Paket 0091-diff-ursachenkette-nach-t20 (Commit 9449bda) hat in
kern/include/kern/zustandsausgabe.hpp die Zahl der Kettenzeilen je Adresse an die
Rundenkapazitaet des Verlaufs gebunden -- Rundenkapazitaet plus eins -- und daneben eine
Zusicherung gesetzt, die die Groesse eines Kettenblatts gegen denselben Stapel je Faden
haelt. Damit haengt eine zweite, viel engere Stapelschranke an derselben Wand.

Gemessen mit befunde/messung-0156/schranke.py, gefahren am 2026-09-06 gegen den
Arbeitsbaum (er kopiert den Kern und baut ihn ganz, nicht nur groesse.cpp):

| Wand | was der Kopf sagt | was der Bau tut |
|---|---|---|
| 26 | gruen | gruen |
| 482 | gruen, geht gerade noch durch | **rot**, Kettenblattzusicherung, 28.808.480 gegen 8.388.608 |
| 483 | rot, Stapelzusicherung des Verlaufs | rot, aber die Kettenblattzusicherung zuerst |
| 2170 | rot, die erste Schranke, nicht die zweite | rot, und zwar alle drei |

Die beiden roten Zeilen stammen aus einem Lauf und stehen im Nachweis im Wortlaut. Aus
ihnen folgt das Gesetz: Die Groesse eines Kettenblatts ist 59.520 mal Wand plus 119.840.
Es stimmt an drei Punkten, denn bei der Wand 26 liefert es 1.667.360, und genau diese
Zahl steht als gemessene Groesse im Kopf von zustandsausgabe.hpp. Gegen 8.388.608
gehalten traegt diese Schranke die Wand bis **138** und reisst bei **139** -- also fast
vier Fuenftel frueher als die Stapelzusicherung des Verlaufs bei 483 und rund
fuenfzehnmal frueher als die T40-Zusicherung bei 2170.

Die 138 und die 139 sind hergeleitet und **nicht** uebersetzt; das ist genau der Grund
fuer Bedingung 1 unten.

## Warum das ein eigenes Paket ist

**Es ist kein Rueckstand von 0172.** Dessen drei Bedingungen sind erfuellt und einzeln
mechanisch belegt. Bedingung 2 hat den neuen Satz und seine Nachweisform sogar
vorgeschrieben, samt der Anordnung ohne die Stapelzusicherung; der Bauagent hat geliefert,
was verlangt war. Falsch gestellt war die Bedingung, nicht die Arbeit -- und eine
Bedingung berichtigt der Projektmanager, nicht der Bauagent.

**Es ist keine Geschmacksfrage.** Der Absatz beginnt mit den Worten gemessen am Stand
45fc32f. Eine Angabe, die als Messung ausgewiesen ist und sich am wirklichen Bau nicht
reproduzieren laesst, ist genau das, was die Hausregeln verbieten. Sie steht ausserdem an
der Stelle, an der ein spaeterer Leser entscheidet, wie weit er die Wand schieben darf --
und heute liest er dort 2169, wo 138 richtig waere.

**Der Schaden ist benennbar.** Wer glaubt, bis 2169 reisse allein die T40-Zusicherung,
kann die Stapelzusicherung des Verlaufs fuer entbehrlich halten und herausnehmen. Sie
greift in Wirklichkeit bei 483, also lange vorher. Der Irrtum fuehrt sonst zu einem roten
Bau mit unerwarteter Meldung, also zu mehr Pruefung; an dieser einen Stelle fuehrt er zu
weniger.

**Warum die Luecke erst jetzt eine ist.** 9449bda hat die Kopplung eingezogen, ohne den
Kopf der Verlaufsdatei zu beruehren; seine Abnahme verlangte das nicht. 0172 ist der erste
Schreibzugriff auf jene Darstellung seither. Vor diesen beiden Paketen las niemand beide
Stellen nebeneinander.

## Was nicht dazugehoert

* **Die drei Zusicherungen in der Verlaufsdatei.** Sie bleiben, wie sie sind. Hier wird
  kein Code geaendert, sondern eine Aussage ueber Messungen berichtigt. Ob die
  Kettenblattzusicherung an der richtigen Stelle steht, ist eine andere Frage.
* **kern/include/kern/zustandsausgabe.hpp.** Unberuehrt. Die Zahl 1.667.360 dort ist
  richtig, und ihr Kopf sagt korrekt, welche zwei Regler seine Zusicherung faengt. Nur
  die **Verlaufsdatei** weiss nichts davon, dass ihre Wand einen dritten Regler bewegt.
  Die Dateiliste bleibt bei einer Datei, damit sie sich mit so wenig anderen Paketen wie
  moeglich schneidet.
* **Die abgelegten Befunde und Messungen zu 0144, 0156 und 0172.** Sie werden nicht
  umgeschrieben (Hausregel 3). Dass befunde/messung-0156/schranke.py heute vier
  Abweichungen meldet, ist ein Ergebnis und kein Fehler der Datei.
* **Die Wand selbst.** Sie bleibt bei 26. Hier wird nichts verschoben.

**Zur Reihenfolge:** 0186-verlauf-glied-mit-fremder-rundennummer steht auf offen und
haelt dieselbe Datei. Eine sachliche Abhaengigkeit besteht in keine Richtung -- dieses
Paket aendert Kommentarzeilen, 0186 aendert Code --, aber die Listen schneiden sich, und
die Reihenfolge entscheidet der Projektmanager. Die Nummer 0195 ist oberhalb der
hoechsten am 2026-09-06 vergebenen (0194) gewaehlt.

## Abnahme

1. **Die genannte Wandgrenze ist uebersetzt, nicht gerechnet.** Der Nachweis baut den
   **ganzen Kern** -- nicht nur groesse.cpp -- mit der Wand auf dem letzten gruenen Wert
   und noch einmal mit dem ersten roten darueber, in beiden Profilen, und druckt die
   Meldung des roten Falls im Wortlaut ab. Dieselbe Zahl steht danach im Kopf. Ein
   Nachweis, der sie nur aus dem Gesetz 59.520 mal Wand plus 119.840 herleitet, erfuellt
   diese Bedingung nicht -- die Herleitung ist genau das, was hier zur Debatte steht.
   befunde/messung-0156/schranke.py kann das mit zwei zusaetzlichen Faellen; ein eigener
   Apparat ist nicht noetig.

2. **Der Kopf nennt drei Schranken statt zwei, und welche zuerst reisst.** Die
   Kettenblattzusicherung aus zustandsausgabe.hpp wird beim Namen genannt, mit der
   Kopplung, aus der sie entsteht (Kettenzeilen je Adresse ist Rundenkapazitaet plus
   eins). Der Satz sagt ausdruecklich, dass sie beim Anheben der Wand **als erste**
   reisst, und nennt den Wert aus Bedingung 1.

3. **Jede verbliebene Zahl sagt, in welcher Anordnung sie gemessen wurde.** Die Saetze
   zu 482, 483, 2169 und 2170 gelten nur ohne die eine oder die andere Zusicherung und
   ohne den Bau des Kerns. Wo eine solche Zahl stehen bleibt, steht die Anordnung
   daneben. Eine Zahl ohne ihre Anordnung wird gestrichen statt stehen gelassen.

4. **Beide Profile gruen.** Konfigurieren, Bauen und ctest mit dem Sanitizer-Profil und
   ohne es, je Rueckgabe 0, im Alleinbau des Kerns und im Arbeitsbereich. Die Zahl der
   ctest-Eintraege bleibt gegenueber dem unmittelbar vorhergehenden Stand desselben Baums
   und desselben Profils gleich; der Bezugsstand wird als Commit genannt, nicht als
   Datum. Zum Vergleich der am 2026-09-06 an den Staenden 45fc32f und 6456047 gemessene
   Wert: Alleinbau 12, Arbeitsbereich 18, in beiden Profilen.
