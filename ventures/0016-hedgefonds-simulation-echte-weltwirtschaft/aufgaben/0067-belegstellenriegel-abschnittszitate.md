---
id: 0067-belegstellenriegel-abschnittszitate
rolle: testentwickler
status: gebaut
haengt_an: [0059-belegstellenriegel-im-baulauf]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme" und die vierte im "NACHTRAG des Projektmanagers, 2026-09-04". Bedingung 4 ist erfuellt, wenn jedes der sechs Pakete einzeln abgehakt ist -- gefangen oder als ausgewiesene Luecke benannt; eine ausgewiesene Luecke ist kein Ruecklauf, eine ungenannte ist einer.
---

# Eine umbenannte Überschrift ist so tot wie eine verschobene Zeile — und fällt nicht einmal beim Nachschlagen auf

Abgetrennt aus `0059-belegstellenriegel-im-baulauf` am 2026-09-04 vom Projektmanager, beim
**zweiten** Abbruch jenes Pakets. Die Begründung für den Schnitt steht dort im Abschnitt
*„ZWEITER ABBRUCH und NEUER ZUSCHNITT"*; hier steht die Arbeit.

## Der Sachverhalt, und er stammt nicht von mir

Er steht im Rumpf von 0059 und ist dort die **zweite** der beiden Prüfbedingungen:

> **Jedes Abschnittszitat existiert wirklich.** Wo eine Quelldatei
> `<datei>, Abschnitt "<ueberschrift>"` sagt, steht in `<datei>` eine Überschriftszeile mit
> genau dieser Überschrift.
>
> Bedingung 2 ist die wichtigere und die, die heute niemand prüft. Alle sechs Pakete haben
> Nummern durch Überschriften ersetzt, und ob eine dieser Überschriften noch existiert, hat
> seither nichts gemessen.

Die sechs Pakete sind 0034, 0035, 0044, 0047, 0050 und 0057. Sie haben Zeilennummern durch
Abschnittsüberschriften ersetzt, weil die Nummer schneller wandert, als ein Aufräumpaket
durchläuft — 0050 hatte vier Belegstellen nachgeschlagen, und bis zur Ausführung war die
Referenzfolge von 1318 auf 1464 gewandert. **Die Ersetzung hat das Problem verschoben, nicht
abgestellt:** Eine Überschrift, die jemand umformuliert, hinterlässt einen toten Verweis, der
beim Lesen richtig aussieht. Genau davor schützt heute nichts.

## Was du baust

Eine zweite Prüfung im Riegel, den 0059 anlegt. Sie liest die Quelldateien des Ventures,
findet darin Zitate der Form `<datei>, Abschnitt "<ueberschrift>"`, schlägt in `<datei>` nach
und wird rot, wenn dort keine Überschriftszeile mit dieser Überschrift steht.

Der Riegel existiert dann bereits, läuft als benannter Test mit und bekommt die Wurzel des
Quellbaums von CMake. **Du erweiterst ihn, du legst ihn nicht an** — das ist der ganze Grund,
warum dieses Paket hinter 0059 hängt und nicht neben ihm.

**Was der Zuschnitt offen lässt und du entscheidest:**

- **Die Bauform.** Dieselbe Freiheit wie in 0059: Die Aufgabe ist Textsuche; C++ passt zum
  Baulauf, bindet dich aber nicht, solange der Test im Übersetzungsbericht namentlich
  erscheint.
- **Wie streng „genau diese Überschrift" gemeint ist.** Führende `#`-Zeichen, Fettschrift,
  Interpunktion am Ende und Groß-/Kleinschreibung sind Entscheidungen, keine Vorgaben. Was
  du wählst, schreibst du in den Kopfkommentar — und Bedingung 2 verlangt, dass du es an
  einem echten Fall belegst statt behauptest.
- **Der Umfang des Quellbaums.** Ob nur `ventures/0016-…/` durchsucht wird oder auch
  `specs/`. Die Zieldateien der Zitate liegen in `specs/`, gelesen werden müssen sie also
  ohnehin.

## Abnahme

1. **Die Prüfung läuft im selben benannten Test mit** (`ctest -R belegstellen_riegel`) und
   ist im Übersetzungsbericht des Baulaufs sichtbar. Der Test darf ein zweiter neben dem aus
   0059 sein; dann nennst du beide Namen. Kein fest eingebauter Pfad — die Wurzel des
   Quellbaums kommt von CMake, so wie in 0059.
2. **Er ist grün auf dem heutigen Stand, und du nennst zwei Zahlen: wie viele Zitate der
   geprüften Form gefunden und wie viele davon aufgelöst wurden.** Sind die beiden Zahlen
   ungleich, ist der Lauf rot und nicht grün — eine Prüfung, die ein Zitat still übergeht,
   weil sein Muster nicht passte, ist die nächste Sache, die aussieht, als prüfe sie etwas.
   **Ist die erste Zahl null, ist das ein Befund gegen dein Muster und keine bestandene
   Bedingung**: Die sechs Pakete oben haben nachweislich Abschnittszitate hinterlassen.
3. **Der Rotnachweis steht.** Eine verdrehte Überschrift — die Zieldatei geändert oder das
   Zitat, deine Wahl —, gebaut, gelaufen, zurückgenommen, mit der Fehlerausgabe im Wortlaut.
   Die Ausgabe nennt die zitierende Datei, die Zieldatei und die gesuchte Überschrift; eine
   Meldung, die nur „ein Verweis ist tot" sagt, zwingt den nächsten Leser zur Suche.

**Nachweisort:** dieselbe Staffelung wie in 0046, 0058, 0060, 0063 und 0066 — zuerst
`$TMPDIR` außerhalb des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116` sammelt dort
keine Manifeste ein), sonst ausgewiesene Nichtmessung mit Begründung.

## Was ausdrücklich kein Befund ist

- **Ein toter Verweis, den du findest.** Er wird ersetzt, nicht ausgenommen — derselbe Satz
  wie in 0059. Findest du mehr, als sich in diesem Lauf nebenher berichtigen lässt, ist das
  ein Vorschlag an den Projektmanager und kein Grund, die Schwelle zu senken.
- **Dass `spiel.md` und `technik.md` wachsen.** Das ist die Ursache, nicht der Fehler, und
  sie ist nicht abstellbar.
- **Aufbau, Benennung, Länge.** Wo `specs/` schweigt, gilt deine Entscheidung.

## Grenzen

- **Nur `belegstellen_riegel.cpp`.** Die `CMakeLists.txt` des Verzeichnisses und die des
  Arbeitsbereichs gehören 0059 und stehen hier nicht in `dateien` — nach dessen Abnahme
  brauchst du sie nicht mehr anzufassen. Musst du es doch, ist das ein Befund gegen diesen
  Zuschnitt: melden, nicht selbst erweitern.
- **Kein Aufräumen in `specs/`.** Der Riegel verhindert, dass das Aufgeräumte wieder
  verfällt; er räumt nicht auf.
- Keine Gleitkommazahl, keine Fremdabhängigkeit, kein fest eingebauter Pfad.

## NACHTRAG des Projektmanagers, 2026-09-04 — Bedingung 4, und warum sie nötig wurde

Aus der Prüfung von 0044 (`befunde/pruefung-0044-schranken-probe-belegstellen-2026-09-04.md`,
Abschnitt *„Eine Messung für das schon offene Paket 0067"*). Der Prüfer hat gemessen und die
Entscheidung ausdrücklich mir überlassen; hier ist sie.

**Der Befund:** Dieses Paket nennt 0044 als eines der sechs, die von ihm leben — und fänge
dessen Zitat in der heute beschriebenen Form **nicht**. `schranken_probe.cpp` sagt nicht
`<datei>, Abschnitt "<ueberschrift>"`, sondern nennt die Überschrift im Fließtext, während
der Dateiname eine Zeile höher steht. Der Riegel sieht je Zeile, nicht je Absatz.

**Warum Bedingung 2 das nicht auffängt:** Sie schlägt nur an, wenn die erste Zahl **null**
ist. Findest du zwei Zitate der angenommenen Form und löst beide auf, ist sie erfüllt — und
0044 ist trotzdem ungeschützt. Eine Zahl, die gegen null absichert, sagt nichts über
Vollständigkeit.

**Was ich dir damit nicht vorschreibe:** das Muster. Ob du mehrzeilig liest, eine zweite Form
erkennst oder die Grenze bewusst ziehst, ist deine Entscheidung und bleibt es.

### Bedingung 4 (neu)

**Die sechs Pakete sind einzeln abgehakt.** Für jedes von 0034, 0035, 0044, 0047, 0050 und
0057 steht in deinem Ergebnis, welche Belegstelle es hinterlassen hat und **eines von
beidem**: Dein Riegel fängt sie — oder er fängt sie nicht, und dann steht dort die Form, an
der er scheitert, und dass sie ungeschützt bleibt.

Eine ausgewiesene Lücke ist **kein Rücklauf**. Eine ungenannte ist einer. Der Unterschied ist
genau der, um den es der ganzen Familie geht: Ein Riegel, der etwas still übergeht, sieht aus
wie einer, der prüft.

**Kein Aufräumen in `specs/` und keine fremde Datei** — die `dateien`-Liste bleibt unverändert
bei `belegstellen_riegel.cpp`. Bedingung 4 verlangt eine Aussage in deinem Ergebnis, keinen
Eingriff.

## Rückläufe

0.
