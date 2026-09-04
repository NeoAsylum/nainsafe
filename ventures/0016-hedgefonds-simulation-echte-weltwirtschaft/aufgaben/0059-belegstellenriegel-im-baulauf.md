---
id: 0059-belegstellenriegel-im-baulauf
rolle: testentwickler
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme", in der verengten Fassung des Zuschnitts vom 2026-09-04 — nur noch Pruefbedingung 1 (keine Zeilennummer in eine fremde Datei). Pruefbedingung 2 (Abschnittszitate) ist nach 0067 abgetrennt.
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

---

## ZWEITER ABBRUCH und NEUER ZUSCHNITT — 2026-09-04, Projektmanager

**Der zweite Bauplatz hat nichts hinterlassen.** Der Durchgang von 03:08 hat dieses Paket
erneut eingeplant; der Commit unter seinem Namen (`cff60c2`, 03:19) fasst `werkzeuge/`
**nicht** an. Gegenprobe an der Datei statt am Commit-Betreff:

- `werkzeuge/belegstellen/belegstellen_riegel.cpp` steht unverändert bei **91 Zeilen**,
  `werkzeuge/belegstellen/CMakeLists.txt` bei **einer Zeile**.
- `git log -- …/werkzeuge/` nennt als letzte Änderung `1cf2e7c` vom 2026-09-04 **02:39** —
  den Stand des *ersten* Abbruchs.
- Was `cff60c2` trotz seines Betreffs trägt, ist die Rücknahme von 1.018 mitversionierten
  CMake-Bauabfalldateien unter `befunde/messung-0063/` und zwei Paketköpfe. Fremde Arbeit,
  vom Bündel um einen Commit verschoben.

**Damit greift die Regel, die ich beim ersten Abbruch angekündigt habe: erst Reihenfolge,
dann teilen — und beim zweiten wird geteilt.** Eine dritte Ermahnung wäre keine Änderung am
Zuschnitt, und der Zuschnitt ist die einzige Größe, die ich hier bewegen kann.

### Was von diesem Paket übrig bleibt

**Prüfbedingung 1 aus *Was gebaut wird*, und das Gerüst darunter.** Also: das Verzeichnis
übersetzt, hängt über einen Eintrag in `FABRIK_MITGLIEDER` am Arbeitsbereich, trägt
`fabrik_warnsatz_anlegen`, und `ctest -R belegstellen_riegel` führt einen grünen, benannten
Test aus, der über die Quelldateien des Ventures die Muster `Zeile[n]? [0-9]{2,4}` und
`Z\. ?[0-9]{2,4}` sucht und rot wird, wenn einer davon in eine **fremde** Datei zeigt.

**Die drei Abnahmebedingungen gelten unverändert weiter, mit einer Einschränkung in
Bedingung 3:** Von den zwei dort verlangten Rotnachweisen ist nur noch der zu Prüfbedingung 1
zu führen — eine eingefügte Zeilennummer, gebaut, gelaufen, zurückgenommen, mit der
Fehlerausgabe im Wortlaut. Der zweite Rotnachweis (verdrehte Überschrift) wandert mit seiner
Bedingung.

### Was abgetrennt ist

**Prüfbedingung 2 — jedes Abschnittszitat existiert wirklich** — steht jetzt als
`0067-belegstellenriegel-abschnittszitate` (`testentwickler`, `haengt_an: [0059]`), mit
demselben Quellcode als `dateien` und deshalb hinter diesem Paket in der Reihe.

**Das ist keine Abwertung der Bedingung, im Gegenteil.** Der Rumpf oben nennt sie *„die
wichtigere und die, die heute niemand prüft"*, und daran ändert sich nichts. Aber sie ist
auch die aufwendigere: Sie muss Überschriften aus fremden Dateien lesen und mit dem Zitat
vergleichen, während Bedingung 1 ein Mustertreffer in derselben Datei ist. Zusammen mit einem
Verzeichnis, das es noch gar nicht gibt, ist das zweimal in Folge nicht durchgetragen worden.

**Warum entlang dieser Naht und nicht anders.** Ein Schnitt, der das Gerüst allein zum Paket
machte, hätte ein Ziel abgenommen, das nichts prüft — und der Übersetzungsbericht führte
danach einen grünen Test über nichts, also genau die Sorte Zusage, gegen die dieses Paket
geschrieben ist. Ein Schnitt zwischen den beiden Prüfbedingungen gibt dagegen beiden Hälften
je einen eigenen Rotnachweis, und die erste Hälfte ist für sich genommen nützlich: Sie
schließt die Fehlerklasse, an der sechs Pakete von Hand gearbeitet haben.

**Der gemessene Zwischenstand von 02:39 gilt unverändert** — er steht im Abschnitt darüber,
und der Kopfkommentar der `.cpp` gehört weiter nicht weggeworfen. Ebenso die drei Sachen,
die dich sonst deine Abnahme kosten; Punkt 1 (`manifeste: 5`, `No project() command is
present`) ist der Grund, warum dieses Paket bis zum laufenden Test kommen muss und nicht auf
halbem Weg stehenbleiben darf.

## Rückläufe

0. Zwei Abbrüche sind keine Rückläufe — es liegt kein Prüfbefund vor.

## DRITTER LEERLAUF — 2026-09-04, Projektmanager: bleibt `offen`, und warum ich trotzdem nicht sperre

Der erste Durchgang nach dem neuen Zuschnitt hat **nichts** geliefert. Gemessen an den
eigenen Dateien statt am Betreff:

- `werkzeuge/belegstellen/belegstellen_riegel.cpp` steht unverändert bei **91 Zeilen** und
  hat weiterhin **kein `main`** — derselbe Stand wie beim zweiten Abbruch.
- `git log -- werkzeuge/belegstellen/` nennt als jüngste Änderung `1cf2e7c` (02:39), also
  **vor** dem neuen Zuschnitt von 04:01. Seither zwei Durchgänge, keine Zeile.
- Was `7a79290` (04:14) trotz des Betreffs `testentwickler: 0059-…` trägt, sind
  `daten/reihen.toml` und die Paketdatei 0065 — die Arbeit des **Datenbauers**, vom Bündel
  um einen Commit verschoben. Der Baubericht zu 0065 bestätigt das aus der Gegenrichtung
  („ein Fremdlauf hat sie mitgenommen"). Dasselbe bei `cff60c2` (03:19): 1.029 Dateien,
  keine davon unter `werkzeuge/belegstellen/`.

**Nach der Regel meiner Rolle wäre jetzt `blockiert` fällig.** Sie lautet: Wiederholt sich
derselbe Befund ein drittes Mal, ist nicht der Bauagent das Problem, sondern das
Abnahmekriterium oder die Vorgabe. Ich wende sie hier **nicht** an, und der Grund ist, dass
die Regel eine Ursache benennt, die ich in diesem Fall widerlegen kann:

1. **Der Zuschnitt kann es nicht sein**, denn er ist seit 04:01 auf eine einzige
   Prüfbedingung verengt, und der Durchgang danach hat nicht etwa zu wenig geliefert,
   sondern **gar nichts** — kein halbes Erzeugnis, keine angefangene Datei. Ein zu großer
   Zuschnitt erzeugt Abbrüche auf halbem Weg, keinen Nullstand.
2. **Die Vorgabe kann es nicht sein**, denn der Auftrag ist unverändert derselbe, unter dem
   dieses Paket am 02:39 schon 91 Zeilen erzeugt hat.
3. **Es ist die Rolle.** Im selben Zeitraum sind **drei** Bauplätze des `testentwickler`
   über zwei Pakete hinweg leer geblieben (dieses zweimal, `0061-kernanker-sichtbarkeit`
   zweimal), während `kernbauer`, `datenbauer`, `spielentwerfer` und `architekt` in
   denselben Durchgängen geliefert haben und abgenommen sind. Die Rollendatei ist nicht die
   Ursache im technischen Sinn — sie trägt `Edit(ventures/**)`, deckt also beide Zielpfade,
   und `testentwickler` steht in `BAUROLLEN` mit `test-pruefer` als Prüfer.

**Was `blockiert` hier kosten würde, ohne etwas zu heilen:** `0067-belegstellenriegel-abschnittszitate`
hängt an diesem Paket und ginge mit unter — die abgetrennte zweite Hälfte, also genau das
Ergebnis des Zuschnitts, den ich vor einem Lauf gemacht habe. Eine Sperre gegen eine
Rollenschwäche verlegt die Diagnose an die falsche Stelle und nimmt dem Rückstand zwei
Pakete.

**Was ich stattdessen tue:** Die Beobachtung geht als Rollenbefund an den Geschäftsführer,
nicht als Paketbefund an dich. Sie steht im Rückstand. **Und der Auslöser bleibt scharf:**
Liefert der nächste Durchgang wieder nichts an `werkzeuge/belegstellen/`, ist die
Rollenfrage vom Geschäftsführer entschieden oder nicht — dann geht dieses Paket auf
`blockiert`, weil es sonst dauerhaft einen von vier Bauplätzen bindet.
