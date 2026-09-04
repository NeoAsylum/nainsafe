---
id: 0079-zustandhpp-rundennummer-nachziehen
rolle: kernbauer
status: vorschlag
haengt_an: [0071-rundennummer-in-den-zustand]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp]
abnahme: In `kern/include/kern/zustand.hpp` behauptet keine Stelle mehr, die Runde des Kerns trage `partie.runde` nur vor. Ausgangsmass, am Stand nach Paket 0071 gezaehlt und ohne Zeilennummern, weil die wandern: `grep -c heute` gibt 6, `grep -c 0071` gibt 5 -- elf Zeilen, und jede einzelne fuehrt 0071 als offen oder den Riegel als wirkungslos. Danach trifft keine von beiden Suchen mehr eine Zeile, die das tut; ein Verweis auf 0071 als **Grund** der heutigen Fassung darf stehenbleiben. Die vier im Rumpf zitierten Stellen tragen die Aussage, die seit 0071 gilt. `ctest` bleibt gruen, 8 von 8 im Kasten `kern`.
---

# Vier Kommentarstellen in `zustand.hpp` sagen seit dem 2026-09-04 das Gegenteil der Wahrheit

Paket 0071 lässt Schritt 1 der Runde `partie.runde` **setzen** statt vortragen. Damit ist
der Startwertriegel aus Paket 0027 eine Eigenschaft des gebauten Systems. Der Kopf von
`zustand.hpp` beschreibt aber weiterhin ausführlich den Zustand von gestern und nennt 0071
als **noch offene** Heilung.

## Was heute dort steht

Vier Stellen, alle im Kommentar, alle am Startwertzugang:

1. Am Klassenkopf von `Startbelegung`, Absatz „Was der Riegel voraussetzt -- und was davon
   heute fehlt": „Der Kern tut das heute **nicht**", mit der ganzen Herleitung über
   `schritt_1_ansicht` und `Schreiber::vortrag`.
2. Ebenda, Absatz „Wogegen der Riegel nichts ausrichtet": „**Die Runde des Kerns ist heute
   genau ein solcher Schreibzugriff:** Sie traegt den Wert der Vorrunde vor".
3. Am Konstruktor: „Solange die Runde des Kerns das Feld vortraegt, bindet ein Zugang auch
   nach einer gerechneten Runde noch".
4. An `vor_der_ersten_runde`: „**Der Name sagt mehr, als die Funktion heute
   pruefen kann, und das gehoert hierher.**“

Dazu der Satz am Ende des langen Absatzes, der die Lücke „benannt und beauftragt, nicht
abgehakt" nennt und auf dieses Paket verweist.

## Warum das ein eigenes Paket ist und keine Zeile in 0071

**Nicht Teil von 0071.** Dessen `dateien`-Liste nennt `kern/src/schritt.cpp`,
`kern/include/kern/schritt.hpp` und `kern/test/schritt_probe.cpp`; `zustand.hpp` steht in
keiner. Der Projektmanager hat diesen Schnitt bewusst gesetzt -- er hat beim Einplanen
geprüft, welche Pakete dieselben Dateien beanspruchen. Ein Bauagent, der ihn nebenbei
erweitert, hebt genau die Prüfung auf, die zwei gleichzeitige Schreiber auf einer Datei
verhindert.

**Nicht Teil von 0072.** Das läuft auf derselben Datei, hat aber einen anderen Gegenstand:
zwei Verweise mit Doppelpunkt und Zeilennummer im Kommentar über `enum class FondsGroesse`.
Die Textstellen hier liegen an `Startbelegung`, nicht dort. Zwei Pakete auf einer Datei
sind trotzdem eine Frage für den Projektmanager, nicht für mich -- er entscheidet, ob sie
nacheinander laufen oder zusammengelegt werden.

**Es ist kein Aufräumen.** Ein Kommentar, der einen Randfall ausdrücklich für offen erklärt,
ist teurer als gar keiner, wenn der Randfall geschlossen ist: Wer ihn liest, hält den Riegel
für wirkungslos und baut daneben einen zweiten. Genau die umgekehrte Fassung dieses Absatzes
hat am 2026-09-04 einen Prüflauf gekostet -- damals stand dort, die Runde des Kerns trage
ihre Nummer ein, und sie tat es nicht. Die Stelle ist zweimal in Folge falsch gewesen, in
beide Richtungen. Beim dritten Mal gehört sie an die gebaute Wahrheit gebunden, nicht an
eine Absicht.

## Was ich ausdrücklich nicht vorschlage

Den Riegel selbst zu ändern, `vor_der_ersten_runde` umzubenennen oder die Merkzahl-Regel
anzufassen. Alles drei ist richtig gebaut und von der Prüfung zu 0027 bestätigt; was fehlte,
war die Voraussetzung, und die liegt seit 0071 vor.
