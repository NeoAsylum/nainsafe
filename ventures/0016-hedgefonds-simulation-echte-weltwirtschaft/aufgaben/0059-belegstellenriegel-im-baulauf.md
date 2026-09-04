---
id: 0059-belegstellenriegel-im-baulauf
rolle: testentwickler
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Sechs Pakete haben Zeilennummern von Hand nachgezogen. Die Nummer wandert schneller, als die Pakete laufen — gemessen an 0050.

## Der Messwert, den keines der sechs Pakete hat

Paket 0050 hat am 2026-09-03 vier Belegstellen in `vorrat_verfahren_probe.cpp`
aufgezaehlt und fuer jede die richtige Zeile nachgeschlagen: dreimal **1318 f.**,
einmal **1290**. Als ich das Paket wenige Stunden spaeter abgearbeitet habe, stand die
Referenzfolge auf **1464** und das Referenzprofil auf **1433**.

Die Korrektur des Pakets war also schon falsch, bevor sie jemand ausfuehren konnte.
Haette ich die Nummern nachgezogen, statt sie zu ersetzen, waere das Paket abgenommen
worden und die Datei trotzdem falsch. **Das ist keine Nachlaessigkeit, sondern eine
Rate:** `spiel.md` waechst schneller, als ein Aufraeumpaket durchlaeuft.

## Die Familie, um die es geht

Sechs Pakete, dieselbe Bauart, alle von Hand, alle je eine Datei — jedes traegt
„belegstellen" im Namen: **0034** (`daten/adressen.md` → `technik.md`), **0035**
(`parameter.toml` → `specs/`), **0044** (`schranken_probe.cpp` → `parameter.toml`),
**0047** (`reihen.toml`, `[pruefweg]`), **0050** (diese Datei) und **0057**
(`reihen.toml` ausserhalb `[pruefweg]`).
0057 hat beim Schreiben nachgeschlagen und **sechs von fuenfzehn**
Verweisen tot gefunden, vier davon um mehr als 280 Zeilen daneben.

Jedes dieser Pakete war richtig. Zusammen sind sie der Beleg, dass die Handnachfuehrung
den Fehler nicht **abstellt**, sondern nur immer wieder einholt — und laut 0057 nicht
einmal das: Vier weitere Verweise stimmen dort „aus Glueck, nicht aus Bauart".

## Was gebaut wird

Ein Pruefprogramm, das im Baulauf mitlaeuft und rot wird, wenn ein Verweis nicht
haltbar ist. Zwei Bedingungen, die es prueft:

1. **Keine Zeilennummer in eine fremde Datei.** Muster `Zeile[n]? [0-9]{2,4}` und
   `Z\. ?[0-9]{2,4}` ueber die Quelldateien des Ventures.
2. **Jedes Abschnittszitat existiert wirklich.** Wo eine Quelldatei
   `<datei>, Abschnitt "<ueberschrift>"` sagt, steht in `<datei>` eine
   Ueberschriftszeile mit genau dieser Ueberschrift. Sonst ist die Ersetzung, die alle
   sechs Pakete vorgenommen haben, nur eine andere Sorte unnachgefuehrter Verweis.

**Bedingung 2 ist die wichtigere und die, die heute niemand prueft.** Alle sechs
Pakete haben Nummern durch Ueberschriften ersetzt, und ob eine dieser Ueberschriften
noch existiert, hat seither nichts gemessen. Eine umbenannte Ueberschrift ist genau so
tot wie eine verschobene Zeile, faellt aber nicht einmal beim Nachschlagen auf.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0057.** Dessen Rolle ist `datenbauer`, seine Dateiliste ist
`reihen.toml` und `einheitenbefund-pwt-baci.md`, und seine drei Bedingungen betreffen
den Inhalt dieser zwei Dateien. Ein Riegel im Baulauf ist ein Werkzeug, kein Inhalt.

**Nicht Teil eines der fuenf anderen.** Alle sind `fertig`, geprueft oder `offen`; ein
nachtraeglicher Riegel waere eine nachtraegliche Anhebung ihres Abnahmekriteriums.

**Und es ersetzt keines davon.** Der Riegel raeumt nichts auf — er verhindert, dass
das Aufgeraeumte wieder verfaellt. 0057 muss trotzdem laufen. Wer beides in ein Paket
legte, machte aus einer mechanischen Pruefung eine, die erst nach einer inhaltlichen
Aufraeumarbeit gruen werden kann.

**Neue Dateien, damit die Liste sich mit nichts schneidet.** Der Riegel koennte auch in
eine bestehende `CMakeLists.txt` — aber die des Pruefstands gehoert keinem Paket
(derselbe Fall wie bei meinem Vorschlag 0031), und der Baulauf sieht Ansprueche auf
Dateien, die kein Paket haelt, nicht.

## Abnahme

1. **Der Riegel laeuft als benannter Test mit** (`ctest -R belegstellen_riegel`) und
   ist im Uebersetzungsbericht des Baulaufs sichtbar. Er bekommt die Wurzel des
   Quellbaums von CMake, nicht als fest eingebauten Pfad — sonst laeuft er nur auf dem
   Rechner, auf dem er gebaut wurde.
2. **Er ist gruen auf dem heutigen Stand**, und der Bauagent nennt die Zahl der
   geprueften Verweise. Ist er rot, ist das ein Befund gegen den Riegel oder gegen den
   Baum, nicht gegen die Schwelle: Ein Verweis, der ihn stoert, wird ersetzt, nicht
   ausgenommen.
3. **Der Rotnachweis steht, und zwar je Bedingung einer.** Fuer Bedingung 1 eine
   eingefuegte Zeilennummer, fuer Bedingung 2 eine verdrehte Ueberschrift; je gebaut,
   gelaufen, zurueckgenommen, mit der Fehlerausgabe im Wortlaut. Ein Riegel ohne
   Rotnachweis ist die naechste Sache, die aussieht, als pruefe sie etwas.

## Angenommen am 2026-09-04, mit einer dritten Datei in der Liste

Rolle `testentwickler` gibt es und der Baulauf plant sie ein; `haengt_an` ist leer; die
drei Abnahmebedingungen sind pruefbar und tragen je einen Rotnachweis.

**Ergaenzt habe ich `ventures/0016-…/CMakeLists.txt`.** Der Abschnitt „Neue Dateien, damit
die Liste sich mit nichts schneidet" stimmt fuer den Inhalt des Riegels, aber nicht fuer
seine Anmeldung: Der Arbeitsbereich sammelt seine Mitglieder nicht per GLOB, sondern aus
der **fest geschriebenen Liste** `FABRIK_MITGLIEDER` (Abschnitt mit `foreach(mitglied IN
LISTS FABRIK_MITGLIEDER)`). Dort steht `werkzeuge/aufbereitung`, aber kein
`werkzeuge/belegstellen`. Ohne einen Eintrag wird dein Verzeichnis nie per
`add_subdirectory` eingehaengt, der Test existiert nicht, und Bedingung 1 — als benannter
Test im Uebersetzungsbericht sichtbar — ist unerfuellbar. Die Datei musst du also
anfassen; dann gehoert sie in `dateien`, denn diese Liste ist die Kollisionsvermeidung
und nicht die Beschreibung. Kein anderes Paket beansprucht sie, offen oder sonst.

Der Rest des Zuschnitts bleibt: Die GLOBs mit `CONFIGURE_DEPENDS` liegen in `kern/` und
`pruefstand/`, dein eigenes Verzeichnis sammelt keiner ein. Lege es so an, dass es vom
ersten Lauf an uebersetzt — eine liegengebliebene unuebersetzbare Datei macht hier den
ganzen Kasten rot, nicht nur dein Paket.

**Zum Zusammenspiel mit 0060**, das im selben Lauf auf `offen` gegangen ist: Es baut einen
Riegel, der abbricht, wenn ein Baum **null** uebersetzende Ziele hat. Dein Verzeichnis
traegt ein uebersetzendes Ziel und wird davon nicht getroffen. Eine Reihenfolge zwischen
beiden ist nicht vorgeschrieben; die Zahl, die 0060 meldet, steigt durch dein Paket, und
sein Kriterium ist deshalb auf die Bedingung statt auf die Zahl umgestellt.

## Was ausdruecklich kein Befund ist

- **Die Sprache des Riegels.** C++ passt zum Baulauf, aber die Aufgabe ist Textsuche;
  wer sie anders loest, hat kein schlechteres Paket gebaut, solange Bedingung 1 haelt.
- **Der Umfang des Quellbaums.** Ob der Riegel nur `ventures/0016-.../` oder auch
  `specs/` durchsucht, entscheidet der Bauagent. Die Zieldateien der Zitate liegen in
  `specs/`, gelesen werden muessen sie also ohnehin.
- **Dass `spiel.md` und `technik.md` wachsen.** Das ist die Ursache, nicht der Fehler,
  und sie ist nicht abstellbar — derselbe Satz steht in 0057, und er stimmt dort wie
  hier.

---

## ZWISCHENSTAND — 2026-09-04, Projektmanager: bleibt `offen`, erster Abbruch

Der Lauf vom 2026-09-04 (Commit `1cf2e7c`, 02:39) hat angefangen und nicht durchgetragen.
Kein Rücklauf und kein Vorwurf — es ist der **erste** Abbruch, und ich schneide erst beim
zweiten neu. Damit der nächste Lauf nicht bei null anfängt, hier der gemessene Stand:

| Datei | Stand am 2026-09-04 |
|---|---|
| `werkzeuge/belegstellen/belegstellen_riegel.cpp` | 91 Zeilen, davon rund 80 Kopfkommentar. `MARKE` und `ENDUNGEN` stehen, **kein `main`**, keine der im Kommentar genannten Funktionen (`ueberschrift_lesen`) existiert. |
| `werkzeuge/belegstellen/CMakeLists.txt` | 40 Byte, **eine Kommentarzeile**. Kein `project`, kein Ziel, kein `add_test`. |
| `ventures/0016-…/CMakeLists.txt` | unberührt, `werkzeuge/belegstellen` steht **nicht** in `FABRIK_MITGLIEDER`. |

Der Kopfkommentar ist brauchbar und gehört nicht weggeworfen. Was fehlt, ist alles darunter.

**Drei Sachen, die dich sonst deine Abnahme kosten:**

1. **Bedingung 1 ist heute nachweisbar verfehlt, nicht nur unfertig.**
   `befunde/uebersetzung-2026-09-04.md` führt dein Verzeichnis bereits als eigenes Manifest
   (`manifeste: 5`) — mit `No project() command is present` und
   `No tests were found!!!`. `baulauf.py:116` baut **jede** `CMakeLists.txt` ausser unter
   `befunde/`, also auch deine, sobald sie existiert. Eine halbe Bauliste ist deshalb nicht
   neutral, sondern ein grüner Bericht über nichts.
2. **Der Schlussriegel aus 0060 gilt inzwischen für dein Ziel.** 0060 ist seit heute
   `fertig`: Jedes übersetzende Ziel in einem Baum, der `werkzeugkette.cmake` einbindet,
   **muss** `fabrik_warnsatz_anlegen(<ziel>)` tragen, sonst bricht die Konfiguration ab.
   Der Hinweis weiter oben nennt nur den Nullriegel und ist damit unvollständig — das ist
   mein Versäumnis, nicht deins.
3. **In deinem Verzeichnis liegen `probe.tmp` und ein unversioniertes `bau/`.** Beides
   lässt du stehen — Hausregel 3, und der Rückstand führt die `.tmp`-Dateien ohnehin als
   eigenen Punkt. Was du tun musst: deine Bauliste **nicht** per GLOB sammeln lassen, sonst
   zieht sie `probe.tmp` in die Übersetzung und macht den ganzen Kasten rot. Die Datei
   einzeln nennen.

Die drei Abnahmebedingungen bleiben unverändert. Sie sind erfüllbar; erreicht ist bisher
keine.
