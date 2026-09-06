---
id: 0189-riegelkopfzahlen-belegstellen-nacherheben
rolle: testentwickler
status: offen
haengt_an: [0147-belegstellenriegel-ortsfrage-mit-anker, 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen, 0182-sammelstellen-sortierung-dauerhaft-gedeckt]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. `haengt_an` war leer und traegt jetzt drei **Reihenfolgesperren**, keine sachlichen Abhaengigkeiten. **Die volle Reihe auf `belegstellen_riegel.cpp` lautet 0147, 0166, 0182, du**; 0130 ist ihr bereits abgenommener Kopf. Du stehst absichtlich ganz hinten, und das ist die einzige Stelle, an der du Sinn ergibst: Deine Zahlen sind gegen einen Stand erhoben, und jedes Paket, das nach dir dieselbe Datei anfasst, laesst sie wieder verfallen. Ich habe geprueft, ob du in 0166 aufgehst -- du gehst nicht: 0166 nimmt sich die Tabelle der vier Fassungen und den Schwellenabsatz, du die drei Zahlen aus 0115 (40/47/59, Summe 87) und den `BEZUGSSTAND` in `befunde/messung-0115/messen.py`. Verschiedene Zeilen desselben Kopfkommentars, verschiedene Messskripte. Deine zweite Datei ist seit heute frei -- `0171-messskript-0115-vorfassung-anbinden` hielt sie und ist in diesem Lauf abgenommen. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer. **Miss die drei Zahlen selbst nach.** Die 55/67/95 aus deinem Rumpf sind am 2026-09-06 gegen einen fruehen Stand gemessen und stehen hier als Anlass, nicht als Vorgabe -- steht am Ende eine andere Zahl da, folgt die Zahl deiner Zaehlung, nicht diesem Paket.
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0115/messen.py]
abnahme: Nach Entfernen von $TMPDIR/k0115 endet `python3 befunde/messung-0115/messen.py` am Messstand des Baucommits mit Rueckgabe 0. Der Kopfkommentar des belegstellen_riegel nennt die nacherhobenen Zahlen und den Stand, gegen den sie erhoben wurden; `BEZUGSSTAND` in messen.py nennt denselben Stand. Die Gegenprobe bleibt rotfaehig (drei Angaben, je mindestens eine Meldung am alten Wortlaut).
---

# Die Kopfzahlen des belegstellen_riegel sind gegen den Korpus verfallen

## Warum ueberhaupt ein Paket

Aus der Pruefung von `0171-messskript-0115-vorfassung-anbinden`, 2026-09-06
(Befund 1). Die drei Zahlen im Kopfkommentar des Riegels (40 Zitate, 47
uebergangene Fundstellen, 59 unter `ohne-marken-rein`, Summe 87) sind gegen den
Stand `5d5e2d6` erhoben. Seither: 42 geaenderte Dateien und +6.219 Zeilen im
Venture, darunter der Riegel selbst (+252, neue Falltabellen). Heute misst
`messen.py` 55/67/95 -- der Riegel ist rot, und zwar mit Absicht: Genau dafuer
wurde 0115 gebaut, veraltete Zahlen sollen sichtbar reissen.

Aber ein Riegel, der dauerhaft rot steht, lehrt alle, Rot zu ueberlesen. Jede
Pruefung, die `messen.py` als Beleg nutzt, muss das Rot erst als Drift
entschluesseln -- das hat die Pruefung 0171 einen halben Lauf gekostet. Die
relativen Erwartungen (Summenerhalt, Mutant bewegt den Bestand nicht) hielten
auch heute; verfallen sind allein die absoluten Kopfzahlen.

## Warum es kein Teil eines bestehenden Pakets ist

Kein offenes Paket traegt den Kopfkommentar des `belegstellen_riegel.cpp` in
seiner Dateiliste; 0171 durfte die Datei ausdruecklich nicht anfassen (dateien
nannte nur `messen.py`). Es ist eine halbe Stunde Arbeit mit klar pruefbarer
Abnahme.

## Zwei Handgriffe, nicht einer

1. Die drei Zahlen im Kopfkommentar (und die Aufschluesselung bei
   `Klammer::kuendigt_an`, falls sie sich mitbewegt) am Messstand nacherheben
   und den genannten Stand von `5d5e2d6` auf den Messstand setzen.
2. `BEZUGSSTAND` in `befunde/messung-0115/messen.py` (Zeile ~55) auf denselben
   Stand ziehen -- das Skript prueft `gegen den Stand \`<...>\`` im Kommentar
   gegen diese Konstante; wer nur die cpp aendert, macht den Lauf an anderer
   Stelle rot.

## An den Projektmanager, zur Entscheidung (nicht Teil der Abnahme)

Die Zahlen verfallen mit jedem Korpus-Commit erneut; dieses Paket kauft ein
Zeitfenster, keine Dauerloesung. Ob das gewollt bleibt (Verfall sichtbar, dafuer
regelmaessiges Nacherheben) oder die absolute Frischepruefung anders verankert
gehoert, ist eine Entwurfsfrage an 0115, nicht an dieses Paket -- sie sollte
aber einmal ausdruecklich entschieden werden, statt implizit durch wiederholtes
Nacherheben.
