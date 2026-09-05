---
id: 0145-beschraenktheit-zweihundert-runden-ohne-spieler
rolle: bruchtester
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/beschraenktheit/]
abnahme: Die vier Bedingungen unter "Abnahme". Bedingung 1 ist die tragende, und sie ist ergebnisoffen -- ein Lauf, der abbricht oder in dem sich nichts bewegt, erfuellt sie ebenso wie ein sauberer Durchlauf, solange das Ergebnis gemessen und abgedruckt ist. Was sie nicht erfuellt, ist ein Befund ohne Lauf.
---

# ANGELEGT — 2026-09-05, Projektmanager: die Pflicht steht in `specs/`, die Prüfstufe war leer

**Warum es dieses Paket bisher nicht gab, und warum jetzt.** `baulauf.py` kennt vier
Arbeitsstufen. Die vierte heißt Prüfung, zieht Pakete der Rollen `selbstspieler`,
`rueckvergleicher` und `bruchtester`, hat ein eigenes Platzkontingent und war seit ihrer
Einführung **leer** — bei jedem Trockenlauf „0 Pakete". Sie steht nicht in Konkurrenz zur
Baustufe: Ein Paket hier nimmt keinem Bauagenten einen Platz weg.

Dieses Paket ist nicht erfunden. Die Pflichtentabelle unter T30 in `technik.md` führt acht
Prüfungen mit je einer verantwortlichen Rolle; die sechste heißt *Beschränktheit*, nennt
als Gegenstand 200 Runden ohne Spieler und als Verantwortlichen den Bruchtester. `spiel.md`
sagt dasselbe an eigener Stelle. Der Gegenstand ist beim Namen genannt, die Rolle auch, und
ihre Rollendatei liegt unter `agents/rollen/bruchtester.md`.

**Die Abhängigkeit auf `0144` ist am 2026-09-05 zurückgenommen worden, von mir, weil sie
falsch war.** Sie stand hier bis heute mit der Begründung, ein Lauf über zweihundert Runden
ende in der einundzwanzigsten, solange die Rundenkapazität des Verlaufs bei zwanzig steht.
Das gilt nur für einen Lauf, der die Ketten mitschreibt — und genau das tut dieses Paket
nicht. Nachgemessen an drei Stellen:

- `kern/include/kern/verlauf.hpp`, Zeile 44–47, nennt den langen Lauf des Bruchtesters
  ausdrücklich: er sei „bewusst **nicht** die Bezugsgroesse" und der Fall, „den T19 selbst
  als kettenfrei ausweist: Wer nur Ergebnisse zaehlt, wirft die Ketten weg und braucht
  keinen Verlauf."
- `kern/include/kern/schritt.hpp` gibt je Runde ein `Rundenergebnis` mit einem frischen
  `kette_dieser_runde` zurück. Die Begrenzung auf zwanzig sitzt im Sammelbehälter über die
  Partie, nicht in der Rundenkette; deren eigene Grenze sind 310 Glieder je Runde.
- Weder `kern/src/schritt.cpp` noch `schritt.hpp` erwähnen `verlauf` überhaupt. Ein
  `Verlauf` entsteht nur, wenn der Aufrufer einen anlegt.

**Für dich heißt das zweierlei.** Du kannst sofort laufen, ohne auf ein anderes Gewerk zu
warten. Und du legst **keinen `Verlauf` an** — du rufst die Runde auf, prüfst die sieben
Schranken am zurückgegebenen Zustand und wirfst die Rundenkette weg. Legtest du doch einen
an, bekämst du in Runde 21 einen Abbruch, der nichts über die Beschränktheit des Modells
aussagt, sondern nur die Kapazität des Behälters nennt.

`0144` bleibt davon unberührt und richtig — es behebt einen echten Fehler am Verlauf. Es
ist nur nicht deine Voraussetzung.

# Zweihundert Runden ohne Spieler — und die eine Zahl, nach der viermal gefragt wurde

## Was zu tun ist

Du lässt das Modell **200 Runden ohne Spieler** laufen und schreibst einen Befund darüber,
was dabei geschieht. Du reparierst nichts — das ist die Grenze deiner Rolle, und sie gilt
hier besonders: Was du findest, wird ein Paket für ein anderes Gewerk, nicht ein Eingriff
von dir.

Der Maßstab ist nicht deine Meinung, sondern die Tabelle der sieben
Wertebereichsschranken, die unter T30 direkt hinter der Pflichtentabelle steht und aus T5,
T49 und T51 folgt. Sie ist bereits als Probe gebaut
(`kern/test/schranken_probe.cpp`); nimm sie als Maßstab, statt einen zweiten zu erfinden.

Verlässt eine Größe ihren Wertebereich, ist das nach der Vorgabe **ein Befund und kein
harter Fehler deines Laufs** — die Vorgabe nennt es einen neunten Rückkopplungskanal, und
die Kanaltabelle kennt acht. Ein solcher Fund ist das wertvollste Ergebnis, das dieses
Paket haben kann, nicht sein Scheitern.

## Die zweite Frage, und sie ist die wichtigere

Der Betreiber hat über vier Pläne hinweg dieselbe Zahl verlangt: **wie viele der 310 Größen
des Zustands sich über eine Runde überhaupt ändern.** Der letzte Stand von `ops/plan.md`
vom 2026-09-04 nennt sie mit **0 von 310** und benennt als Ursache, dass `werte.hpp` bei
78 Byte stehe und `werte.cpp` fehle. Beides trifft heute nicht mehr zu: `werte.hpp` steht
bei 17.036 Byte, `werte.cpp` bei 32.531, und die vier Pakete, die der Plan als Weg dorthin
nannte — 0026, 0002, 0071, 0010 —, stehen alle auf `fertig`.

**Ob sich die Zahl bewegt hat, hat seither niemand gemessen.** Dein Lauf ist die erste
Gelegenheit, an der sie ohne Zusatzaufwand abfällt: Wer zweihundert Runden rechnet, hat
Start- und Endbelegung ohnehin in der Hand.

**Ist die Antwort weiterhin null, ist das der Befund** — dann schreib ihn hin, mit der
Rundennummer, ab der sich nichts mehr tut, und ohne ihn zu beschönigen. Ein gemessenes
Null ist etwas anderes als ein vermutetes.

## Was nicht dazugehört

- **Kein Eingriff am Kern.** Kein Quelltext unter `kern/`, keine Probe, keine
  Werkzeugkette. Findest du die Ursache eines Fehlverhaltens, benenne sie; das Paket dafür
  schneidet der Projektmanager.
- **Nicht die zehntausend Partien.** Das ist die fünfte Pflicht derselben Tabelle, sie
  braucht den Zufallsbot und ist ein eigenes Paket.
- **Keine Baumkopie in die Ablage.** Was du hinterlässt, ist der Messstand — Skripte,
  Mitschnitte, der Befund —, nicht eine Abschrift des Vorhabens. Der Grund steht in
  `0081-messbaeume-aus-der-versionierung` und ist am 2026-09-05 in `0143` erneut
  nachgemessen worden: Bereits ignorierte Kopien liegen weiter auf der Platte und werden
  von Werkzeugen mitgelesen, die von git nichts wissen.

## Abnahme

1. **Der Lauf ist gelaufen und abgedruckt.** Zweihundert Runden ohne Spieler, in beiden
   Profilen (`FABRIK_SANITIZER=ON` und `OFF`). Der Mitschnitt lässt je Runde die
   Rundennummer erkennen. **Bricht der Lauf ab, erfüllt auch das diese Bedingung** —
   dann stehen die Rundennummer des Abbruchs, der Rückgabewert und die Meldung im
   Wortlaut im Befund. Was sie nicht erfüllt, ist ein Befund ohne einen Lauf dahinter,
   und ein Mitschnitt, der bei zwanzig Runden endet, ohne dass gesagt wird warum, ist von
   einem abgebrochenen Lauf nicht zu unterscheiden.

2. **Je Schranke eine Aussage.** Für jede der sieben Wertebereichsschranken steht im
   Befund, ob sie über den Lauf gehalten hat; wo nicht, die Runde, die Adresse und der
   Wert. Die Schranken werden aus der Tabelle unter T30 übernommen und nicht neu
   hergeleitet; welche Fassung du gelesen hast, nennst du mit Commit-Kennung.

3. **Die eine Zahl steht da, gemessen.** Wie viele Größen des Zustands sich am Ende des
   Laufs gegenüber der Startbelegung unterscheiden — eine Zahl, ihr Nenner, und wie du sie
   ermittelt hast. Zusätzlich dieselbe Zahl über **eine** Runde, damit sie mit der
   Angabe aus `ops/plan.md` vergleichbar ist. Geschätzt gilt nicht.

4. **Der Baum ist unverändert.** Außerhalb von
   `befunde/beschraenktheit/` hast du nichts geschrieben. Die Zahl der ctest-Einträge des
   Arbeitsbereichs bleibt gegenüber dem unmittelbar vorhergehenden Stand desselben Baums
   und desselben Profils gleich; der Bezugsstand wird genannt.

## Rückläufe

0.
