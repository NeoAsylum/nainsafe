---
id: 0067-belegstellenriegel-abschnittszitate
rolle: testentwickler
status: offen
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

1.

---

# RÜCKLAUF 1 — 2026-09-04, Projektmanager: `gebaut` → `offen`

Befund: `befunde/pruefung-0067-belegstellenriegel-abschnittszitate-2026-09-04.md`,
`urteil: zurueck`, ein Befund. **Lies ihn im Wortlaut** — er enthält eine ausgeführte
Reproduktion samt Sabotage an einer Kopie von `specs/`, und du sollst sie nicht
nacherfinden.

## Was steht und nicht angefasst wird

**Bedingungen 1, 2 und 3 sind erfüllt, und der Prüfer hat sie nicht auf dein Wort hin
abgenommen**, sondern selbst gebaut: eigener Bau in `$TMPDIR`, die 21 Zitate einzeln
ausgegeben und nachgeschlagen statt gezählt, sechs Sabotagen an derselben Überschrift, und
drei Mutanten, die je eine Lockerung der Normierung abschalten. Die zwei bezifferten
Zusagen deines Kopfkommentars treffen dabei genau zu (3 von 21 und 1 von 21). **Das ist der
Gegenbeweis zu „Schwelle gesenkt, damit es grün wird", und er steht dir zu.**

Auch die Null-Bremse hält: Ein Mutant, dessen Muster nichts mehr trifft, meldet im Wortlaut
„kein einziges Abschnittszitat gefunden" und fällt. Ohne sie wäre das der gefährlichste
grüne Lauf überhaupt.

**Nicht anfassen:** das Muster, die Normierung, die Klammernliste, die Absatzlesung. Alles
geprüft und richtig.

## Was gerissen ist — eine einzige Zuordnung

Bedingung 4 verlangt für jedes der sechs Pakete zwei Angaben: welche Belegstelle es
hinterlassen hat, und ob der Riegel sie fängt **oder** an welcher Form er scheitert.
**Fünf von sechs sind sauber**, einzeln an der Messliste nachgeprüft und bestätigt,
einschließlich der ausgewiesenen Lücke bei 0047.

**Bei 0034 stimmt die Zuordnung nicht.** Dein Ergebnis nennt als Belegstelle von 0034 das
Kopffeld `quellen` in `daten/adressen.md` und urteilt „gefangen". Die Belegstelle gibt es
und sie wird gefangen — aber sie stammt aus Paket 0004 vom 2026-09-01, zwei Tage vor 0034.

**Was 0034 wirklich hinterlassen hat**, sind drei Stellen in `technik.md` (T49 zweimal, T46
einmal), und der Riegel fängt **keine** davon: zweimal heißt das Schlüsselwort *Absatz*,
das `SCHLUESSEL` nicht kennt, einmal stehen fünf Wörter zwischen Schlüsselwort und
Anführung. Entscheidend ist nicht, dass er sie nicht fängt — **sie landen auch nicht unter
den fünf übergangenen Fundstellen.** Für den Riegel sind sie kein Zitat, also zählt er sie
nirgends.

**Das ist der ganze Rücklauf:** der Unterschied zwischen einer ausgewiesenen und einer
ungenannten Lücke. Eine ausgewiesene ist keiner, das sagt deine Abnahme ausdrücklich.

## Deine Abnahme für diesen Lauf — sie ist kleiner, nicht größer

**Nur Bedingung 4, und nur die Zeile zu 0034.** Bedingungen 1 bis 3 sind belegt und bleiben
Erhaltungsbedingung: Du darfst sie nicht brechen, belegen musst du sie nicht noch einmal.

Der Prüfer nennt beide Wege gangbar, und **die Wahl ist deine, nicht meine**:

- die drei Formen so benennen, wie die von 0047 benannt ist, oder
- sie fangen.

Beides liegt in `belegstellen_riegel.cpp` und damit in deiner Dateiliste; ein neues Paket
braucht es dafür nicht. **Wählst du das Fangen, wächst die Trefferzahl** — dann gilt die
Bedingung „in meiner Datei ist die Zuordnung vollständig", nicht eine feste Zahl.

## Zwei Dinge, die ich dir mitgebe, weil sie dich sonst ein zweites Mal treffen

1. **`git log -S` allein trägt die Zuordnung nicht.** Du hast das richtige Werkzeug genommen
   und bist trotzdem zwei Tage danebengelandet. Der Grund liegt im Repo, nicht in dir: Die
   Arbeit eines Pakets liegt regelmäßig im Commit des **nächsten** Laufs, und der trägt den
   Namen des anderen Pakets. **Halte jeden `-S`-Treffer gegen das Datum des Pakets**, dessen
   Belegstelle du suchst. Das ist ab jetzt Teil des Auftrags und nicht dein Versäumnis.
2. **`befunde/messung-*` ist eine Abschrift des Quellbaums und keine Quelle.** 479 Dateien
   liegen dort im Index, darunter vollständige Kopien von `kern/` mit Sätzen, die im
   Original längst ersetzt sind. Der Riegel überspringt `befunde/` nachweislich; wer von
   Hand greppt, muss es selbst tun.

## Was ausdrücklich kein Befund gegen dich ist

- **Die beiden ausgewiesenen Lücken** (0047 „Überschrift ohne Anführung"; „Ziel außerhalb
  des Bestands"). Der Prüfer bestätigt beide als genau so gemeint. Sie sind mit diesem Lauf
  als `0079-belegstellenriegel-zitat-ohne-anfuehrung` und
  `0083-belegstellenriegel-totes-ziel-statt-uebergangen` angelegt und hängen an dir —
  **nicht** in dieses Paket zu ziehen.
- **Die Vorgabenwurzel aus dem ersten Argument** statt aus CMake. Sie ist die Folge davon,
  dass die `CMakeLists.txt` zu 0059 gehört und nicht in deiner Liste steht; der Fall
  „Verzeichnis fehlt" fällt sicher aus statt still grün.
- **`UEBERSCHRIFT_HOECHSTENS = 200`** und die fünf übergangenen Fundstellen. Alle fünf
  einzeln nachgeschlagen, keine ist ein verkappter toter Verweis.
