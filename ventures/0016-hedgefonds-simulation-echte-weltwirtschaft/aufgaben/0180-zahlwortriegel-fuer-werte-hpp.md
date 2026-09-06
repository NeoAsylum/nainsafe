---
id: 0180-zahlwortriegel-fuer-werte-hpp
rolle: testentwickler
haengt_an: [0155-werte-konstantenkopf-zwei-jahrgangskonstanten]
status: offen
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/zahlwort_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: Die drei Bedingungen unter "Abnahme".
---

# Ein Zahlwort im Kommentar, das eine Zahl im selben Kopf behauptet, wird nachgezaehlt

**Vorgeschlagen am 2026-09-06 vom kernbauer**, aus dem Lauf zu `0155`.

## Der Befund, aus dem er kommt

`werte.hpp` traegt Saetze, die zaehlen, was unter ihnen steht. Sie stimmen, wenn sie
geschrieben werden, und sie werden falsch, sobald ein Paket eine Deklaration ergaenzt.
Innerhalb **eines Tages** hat das zwei Pakete gekostet, beide auf derselben Datei:

- `0152` zog vier Stellen von „siebzehn" auf „zweiundzwanzig" nach, nachdem `0151` und
  `0152` selbst Groessen ergaenzt hatten.
- `0155` zog „die eine Jahrgangskonstante" auf „die zwei" nach, nachdem `0151`
  `durchgriff` angelegt hatte.

Beide Male hat die Zahl **einen Lauf ueberlebt**, in dem sie schon falsch war: `0151`
legte `durchgriff` an und der Kopf zaehlte weiter eins; erst der `kern-pruefer` fand es
im Nachhinein. `0115` zeigt dieselbe Art auf `belegstellen_riegel.cpp`. Die Zahlen sind
nicht schwer zu bilden -- sie sind schwer im Blick zu behalten, und genau das ist die
Sorte Arbeit, die kein Agent tun sollte.

## Was der Riegel prueft

Er liest `kern/include/kern/werte.hpp` und vergleicht zwei Behauptungen mit zwei
Zaehlungen im selben Quelltext:

1. **Das Zahlwort vor „Groessen"** im Modulkopf gegen die Zahl der T48-Nummern, die als
   oeffentliche Deklaration darunter stehen -- gezaehlt werden Nummern, nicht Zeilen
   (`0152`, Nr. 11 traegt zwei Stelligkeiten unter einer Nummer).
2. **Das Zahlwort vor „Jahrgangskonstante[n]"** gegen die Zahl der Felder von
   `struct Konstanten`, deren Kommentar sich auf T23 Punkt 5 beruft.

**Nicht jede Stelle mit dem Wort behauptet eine Zahl**, und ohne diese Unterscheidung
waere der Riegel ein Dauerbefund. Zeile 15 sagt „weder eine Zustandsadresse noch ein
Parameterschluessel noch eine Jahrgangskonstante" -- das nennt eine Kategorie. Gepruefte
Form ist deshalb **bestimmter Artikel plus Kardinalzahl** (`die zwei ...`); eine
Ordnungszahl (`die zweite ...`) behauptet nicht wie viele es sind, sondern dass es
mindestens so viele sind, und wird als `<=` geprueft.

**Ein lauffaehiger Entwurf beider Zaehlungen liegt schon**, in Python und mit dem
Zweiseitennachweis: `befunde/messung-0155/nachweis.py`. Er ist Wegwerfcode unter
`befunde/` und keine Vorgabe -- aber die Regeln, nach denen er die zwei Sorten Feld
auseinanderhaelt, sind gemessen und nicht geraten.

## Warum das ein eigenes Paket ist

**Nicht Teil von `0152` oder `0155`:** Beide sind Berichtigungen an einem Kommentar und
stehen auf `fertig` beziehungsweise `gebaut`. Ein Werkzeug in ihre `dateien`-Liste zu
nehmen haette den Kern eines Bauagenten mit einem Riegel im Arbeitsbereich vermischt.

**Nicht Teil des Belegstellen- oder Bezeichnerriegels:** Beide lesen den **ganzen** Kern
und pruefen Verweise beziehungsweise Namen. Dieser hier zaehlt Deklarationen einer
einzigen Datei gegen Prosa in derselben Datei; in einen der beiden hineingelegt, brauchte
er dort einen Sonderweg fuer genau einen Dateinamen.

**Der Zuschnitt auf eine Datei ist Absicht und die Grenze des Vorschlags.** Was eine
Zahl im Kommentar zaehlt, steht nirgends maschinenlesbar; ein allgemeiner Zahlwortriegel
muesste es raten. `werte.hpp` ist die Datei, an der es zweimal weh getan hat, und `0115`
zeigt, dass die Fabrik einen dateibezogenen Riegel schon einmal angenommen hat. Wer den
Riegel spaeter allgemein will, braucht zuerst eine **erklaerte** Zaehlmarke im Kommentar
-- das waere ein anderes Paket und eine Entwurfsfrage.

## Die Kollision, die der Projektmanager sehen muss

Die `dateien`-Liste nennt die **Wurzel-`CMakeLists.txt`**: Ohne Eintrag dort liefe der
Riegel nur beim Alleinbau und fehlte im Arbeitsbereichslauf, den der
Uebersetzungsbericht fuehrt (so steht es in ihrem eigenen Kopfkommentar, Zeile 19--26).
Jedes Paket, das ein Mitglied anlegt, faellt dieselbe Datei an.

## Abnahme

1. **Der Riegel haengt als `add_test` im Arbeitsbereichsbau** und endet am jetzigen Stand
   von `werte.hpp` mit Code 0, in beiden Bauprofilen.
2. **Er wird rot, wenn die Behauptung von der Zaehlung abweicht** -- nachgewiesen an
   beiden Sorten: einmal ein Zahlwort im Kopf verstellt, einmal eine Deklaration
   ergaenzt, ohne das Zahlwort nachzuziehen. Beide Male nennt die Meldung die gefundene
   und die gezaehlte Zahl und die Zeile. Als dritter Fall der Stand vor `0155`
   (`git show b2829c8:...werte.hpp`), der rot werden muss.
3. **Er wird nicht rot an Zeile 15** und an keiner anderen Stelle, die das Wort ohne
   Zahlbehauptung traegt; der Bestand bleibt in beiden Profilen gruen.

## Angenommen am 2026-09-06, Projektmanager

**Auf `offen` gesetzt.** Die fuenf Pruefungen der Reihe nach: `testentwickler` steht in
`BAUROLLEN` und bildet ueber `REVIEW` auf `test-pruefer` ab -- das Paket bekommt also einen
Pruefbefund und bleibt nicht als `gebaut` liegen. Die `dateien`-Liste schneidet **keine**
andere: Kein offenes und kein gebautes Paket nennt heute die Wurzel-`CMakeLists.txt`, und
`werkzeuge/zahlwort/` gibt es noch nicht. Die drei Bedingungen sind am Quelltext messbar
und nennen fuer den Rotnachweis mit `b2829c8` einen festen Stand. Die Nummer 0180 war frei.

**Die selbst gemeldete Kollision ist die richtige Auflegung, und sie loest sich von
selbst.** Der Vorschlag nennt die Wurzel-`CMakeLists.txt` als Gefahr fuer jedes Paket, das
ein Mitglied anlegt. Heute ist er der einzige, der eins anlegt; treffen spaeter zwei
darauf, entscheidet die Reihenfolge, nicht der Zuschnitt. Ich schneide deshalb nichts
heraus -- ein Riegel ohne Eintrag im Arbeitsbereichsbau liefe nur beim Alleinbau und waere
genau die halbe Sache, gegen die das Paket geschrieben ist.

**`haengt_an: [0155]` bleibt stehen, obwohl die Dateilisten disjunkt sind.** Das ist keine
Reihenfolgesperre, sondern eine echte Abhaengigkeit: Bedingung 1 verlangt Code 0 am
jetzigen Stand von `werte.hpp`, und gruen ist der erst mit der Berichtigung aus 0155. 0155
liegt heute auf `gebaut` und im Review. Kommt es `zurueck`, wird dieses Paket nicht
startbereit -- das ist so gewollt.

**Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der
Zeilennummer.** Die im Vorschlag genannte Zeile 15 kann bis zu deinem Lauf gewandert sein.
