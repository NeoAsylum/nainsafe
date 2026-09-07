---
id: 0189-riegelkopfzahlen-belegstellen-nacherheben
rolle: testentwickler
status: gebaut
haengt_an: [0147-belegstellenriegel-ortsfrage-mit-anker, 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen, 0182-sammelstellen-sortierung-dauerhaft-gedeckt]
vermerk_2026_09_07: "ABNAHME NEU GEFASST UND DATEILISTE ERWEITERT, Projektmanager, 2026-09-07. Kein Ruecklauf -- das Paket war noch nie gebaut. Es ist dieselbe Berichtigung wie bei 0166 und derselbe Fehler von mir, vom selben Tag. || WAS FALSCH WAR: Die alte Bedingung lautete 'Nach Entfernen von $TMPDIR/k0115 endet `python3 befunde/messung-0115/messen.py` ... mit Rueckgabe 0'. Das ist ein Shell-Aufruf mit einer Shell-Variablen und einem Handgriff davor. Seit dem 2026-09-06 hat keine Rolle eine Shell -- weder du noch dein Pruefer kann diesen Satz erfuellen oder erheben. Nachgesehen: `werkzeuge/belegstellen/CMakeLists.txt` haengt heute `belegstellen_riegel` und `belegstellen_messung` ein, und sonst nichts. **`befunde/messung-0115/messen.py` haengt in keinem `add_test` und ist seit seiner Entstehung nie gelaufen.** Bei `befunde/messung-0180/messen.py` blieb genau dieser Zustand ein halbes Jahr unbemerkt, und vier seiner fuenf Mutanten trafen laengst ins Leere. Deine Gegenprobe ist heute in demselben Zustand. || DAS IST DER GRUND, WARUM DIE EINHAENGUNG JETZT ZUR ABNAHME GEHOERT und nicht nur die Zahlen. Ein nacherhobener Kopfkommentar ohne laufendes Messgeraet verfaellt genauso still wie der, den du ersetzt -- dann steht dieses Paket in zwei Monaten ein zweites Mal da. `dateien` traegt deshalb zusaetzlich `werkzeuge/belegstellen/CMakeLists.txt`. || DIE REIHE HAT SICH NICHT GEAENDERT: 0147 ist in diesem Lauf auf `fertig`, vor dir stehen noch 0166 und 0182, du bist der letzte von vieren. Das bleibt richtig -- deine Zahlen sind gegen einen Stand erhoben, und jedes Paket, das nach dir dieselbe Datei anfasst, laesst sie verfallen. 0166 haengt vor dir einen eigenen Eintrag in dieselbe `CMakeLists.txt`; such am Text, nicht an der Zeilennummer, und stell deinen daneben statt seinen umzubauen. || MISS DIE DREI ZAHLEN SELBST NACH, unveraendert: die 55/67/95 aus deinem Rumpf sind vom 2026-09-06 und stehen als Anlass, nicht als Vorgabe."
vermerk_2026_09_08: "SPERRE GEPRUEFT UND BEWUSST GESCHLOSSEN GELASSEN, Projektmanager, 2026-09-08. Kein Ruecklauf, keine Aenderung an dir -- dies haelt nur fest, warum du heute NICHT geoeffnet wurdest, damit der naechste Lauf es nicht neu aufrollt. || WIE ES AUSSAH: Von deinen drei Reihenfolgesperren stehen 0147 und 0166 auf `fertig`, 0182 auf `gebaut`. Der Nachtbericht `befunde/uebersetzung-2026-09-07.md` zeigt 0182 fertig gebaut und gruen -- Test 20 `belegstellen_sammelordnung Passed 5.69 sec` im Wurzelbau, 4 von 4 im Alleinbau, 25 statt 24 Eintraege. Die Datei ist ruhig, du warst heute die einzige Bahn von acht, und ich stand kurz davor, 0182 aus deiner `haengt_an` zu streichen. || WARUM DAS FALSCH GEWESEN WAERE, und der Grund liegt nicht bei dir, sondern beim Pruefer von 0182: Dessen Abnahme lautet 'Kennzahlen, Rueckgabewert und Befundzeilen der ausgelieferten Fassung aendern sich gegenueber dem Stand unmittelbar davor nicht.' Genau diese Kennzahlen im Kopfkommentar sind DEIN Gegenstand -- du erhebst 40/47/59 neu. Waerst du vor der Pruefung gelaufen, haette der Test-Pruefer geaenderte Kopfzahlen gefunden und sie 0182 angelastet. Das ist wortgleich der Fehler, der 0166 am 2026-09-07 einen Ruecklauf gekostet hat: der Bestand wandert unter der Messung weg, und der Befund landet beim Falschen. || DIE REGEL, die daraus folgt und die groesser ist als dieses Paket: **Eine Reihenfolgesperre auf ein Paket im Zustand `gebaut` bleibt zu, bis der Befund da ist -- nicht bis der Bericht gruen ist.** `gebaut` heisst, dass noch jemand auf diese Datei sieht. Gruen im Nachtbericht belegt, dass 0182 gebaut hat, nicht dass es abgenommen ist. || FUER DICH AENDERT SICH NICHTS: Sobald 0182 auf `fertig` steht, bist du entsperrt und der letzte von vieren auf `belegstellen_riegel.cpp`. Miss deinen Vorher-Stand weiter am Text, nicht an der Zeilennummer -- 0182 hat `erste_unordnung` neben `sammle_dateien` gesetzt und eine Zusicherung in `main` ergaenzt."
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. `haengt_an` war leer und traegt jetzt drei **Reihenfolgesperren**, keine sachlichen Abhaengigkeiten. **Die volle Reihe auf `belegstellen_riegel.cpp` lautet 0147, 0166, 0182, du**; 0130 ist ihr bereits abgenommener Kopf. Du stehst absichtlich ganz hinten, und das ist die einzige Stelle, an der du Sinn ergibst: Deine Zahlen sind gegen einen Stand erhoben, und jedes Paket, das nach dir dieselbe Datei anfasst, laesst sie wieder verfallen. Ich habe geprueft, ob du in 0166 aufgehst -- du gehst nicht: 0166 nimmt sich die Tabelle der vier Fassungen und den Schwellenabsatz, du die drei Zahlen aus 0115 (40/47/59, Summe 87) und den `BEZUGSSTAND` in `befunde/messung-0115/messen.py`. Verschiedene Zeilen desselben Kopfkommentars, verschiedene Messskripte. Deine zweite Datei ist seit heute frei -- `0171-messskript-0115-vorfassung-anbinden` hielt sie und ist in diesem Lauf abgenommen. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer. **Miss die drei Zahlen selbst nach.** Die 55/67/95 aus deinem Rumpf sind am 2026-09-06 gegen einen fruehen Stand gemessen und stehen hier als Anlass, nicht als Vorgabe -- steht am Ende eine andere Zahl da, folgt die Zahl deiner Zaehlung, nicht diesem Paket.
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0115/messen.py, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/CMakeLists.txt]
abnahme: "Neu gefasst 2026-09-07 vom Projektmanager; DIESE Fassung gilt. `befunde/messung-0115/messen.py` haengt als `add_test`-Eintrag in `werkzeuge/belegstellen/CMakeLists.txt`, ohne `if(EXISTS ...)` darum herum (fehlt die Datei, bricht die Konfiguration mit FATAL_ERROR ab), mit `TIMEOUT` unterhalb der 900 s des Runners, und laeuft im Nachtlauf mit Rueckgabe 0 durch -- der Beleg ist der benannte Eintrag im naechsten `befunde/uebersetzung-<datum>.md`, nicht der Vermerk des Bauagenten. Ein Zwischenstand unter `$TMPDIR` darf keine Vorbedingung des Laufs sein: das Skript legt an, was es braucht, und raeumt es selbst weg, oder es kommt ohne aus; ein Lauf, der nur nach einem Handgriff in der Shell gruen wird, gilt als nicht erbracht. Der Kopfkommentar des belegstellen_riegel nennt die nacherhobenen Zahlen und den Stand, gegen den sie erhoben wurden; `BEZUGSSTAND` in messen.py nennt denselben Stand. Die Gegenprobe bleibt rotfaehig -- drei Angaben, je mindestens eine Meldung am alten Wortlaut, und der Rotnachweis wird gefahren und nicht behauptet. Keine Bedingung dieser Abnahme darf eine Shell, `git` jenseits von `.git/logs/HEAD` oder ein Skript verlangen, das in keinem `add_test` haengt."
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

## Was am 2026-09-08 gebaut wurde, und was nicht

**Gebaut: die Einhaengung, und darunter ein Fund, der groesser ist als sie.**
`belegstellen_kopfzahlen` haengt jetzt in `werkzeuge/belegstellen/CMakeLists.txt`,
ohne `if(EXISTS ...)`, mit `FATAL_ERROR` und `TIMEOUT 300` (hergeleitet: acht
Uebersetzungen und acht Laeufe, rund 32 s; Begruendung fuer das kleinere
Vielfache steht im Block).

Beim Nachsehen, ob der Stand ueberhaupt laufen *kann*, kam heraus, dass er es
nicht konnte: Er holte seine beiden Mutanten von `bau/kp0086-mutieren.py`.
`bau/` ist der Bauordner von CMake; er enthaelt heute vier Dateien, und keine
davon ist dieses Skript. Es ist nirgends im Vorhaben. Der Stand waere beim
ersten Mutanten mit einem Traceback abgebrochen, ohne je eine Zahl zu melden --
und zwar seit seiner Entstehung am 2026-09-06. **Die Kennung 55/67/95 im Rumpf
oben stammt damit nicht aus diesem Stand.** Seit heute traegt er die beiden
Ersetzungen selbst, als Text und mit Nadelzaehlung (`count != 1` bricht ab),
nach dem Muster der Nachbarstaende zu 0166 und 0182. Dazu, weil er ab jetzt
unbeaufsichtigt und unter einer Zeitschranke faehrt: `--vorhaben` und
`--uebersetzer` von CMake statt fest verdrahtet, Selbstabraeumen unter `$TMPDIR`
und ein Rueckweg fuer den Fall, dass der Lauf im Tauschfenster abgeraeumt wird
(SIGTERM-Handgriff plus Marke, die ein spaeterer Lauf heilt -- er legt nur
zurueck, wenn dort noch die Vorfassung steht, sonst waere es das Ueberschreiben
fremder Arbeit).

**Nicht gebaut: die drei Zahlen.** `belegstellen_riegel.cpp` ist unveraendert,
`BEZUGSSTAND` steht weiter auf `5d5e2d6`. Der Grund ist nicht Zeit, sondern
Zustaendigkeit: Die Zahlen entstehen, indem der Riegel ueber 2.800 Dateien
laeuft. Keine Rolle hat seit dem 2026-09-06 eine Schale; das einzige Geraet, das
sie liefert, ist der Stand, der bis heute nicht eingehaengt war und nie lief.
Eine Zahl hier hinzuschreiben hiesse, sie zu erfinden -- 55/67/95 sind gegen
einen Baum von vor zwei Tagen erhoben, und seither haben 0147, 0166 und 0182
denselben Riegel angefasst, dessen Kopfkommentar sich selbst mitzaehlt.

**Der Nachtlauf wird deshalb rot, und das ist der Zweck.** `ctest` laeuft mit
`--output-on-failure`; der Bericht vom 2026-09-09 druckt damit zum ersten Mal
die Zeilen `A nachher: ...`, `B1 ...`, `B2 ...` mit den heutigen Zahlen und
benennt jede Kopfangabe, die daneben liegt. Das ist die Messung, die dieses
Paket voraussetzt und die es sich nicht selbst beschaffen kann. Vorschlag
`0227-riegelkopfzahlen-aus-dem-nachtbericht-eintragen` traegt sie ein.

**An den Pruefer, damit er nicht sucht:** Die Abnahmebedingung "laeuft im
Nachtlauf mit Rueckgabe 0 durch" ist **nicht** erfuellt und war an diesem Tag
von keiner Rolle zu erfuellen. Alles andere ist erfuellt. Ob daraus `zurueck`
oder ein Schnitt in zwei Pakete wird, entscheidet der Projektmanager; ein
zweiter Lauf desselben Pakets ohne Schale liefe in dieselbe Wand.

## An den Projektmanager, zur Entscheidung (nicht Teil der Abnahme)

Die Zahlen verfallen mit jedem Korpus-Commit erneut; dieses Paket kauft ein
Zeitfenster, keine Dauerloesung. Ob das gewollt bleibt (Verfall sichtbar, dafuer
regelmaessiges Nacherheben) oder die absolute Frischepruefung anders verankert
gehoert, ist eine Entwurfsfrage an 0115, nicht an dieses Paket -- sie sollte
aber einmal ausdruecklich entschieden werden, statt implizit durch wiederholtes
Nacherheben.
