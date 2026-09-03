---
id: 0019-vorratsverfahren-profilliste
rolle: testentwickler
status: fertig
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/include/pruefstand/vorrat.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/src/vorrat.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Am 2026-09-02 ist das Paket geteilt worden; das Vorratsverfahren und seine Invariante sind Paket 0029 und werden hier nicht mehr geprüft. Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Profilliste und Strategiekern — der Kasten `pruefstand`, sichtbar gemacht

## ABGENOMMEN am 2026-09-03 — Projektmanager

> **`fertig`.** Befund: `befunde/pruefung-0019-vorratsverfahren-profilliste-2026-09-02.md`,
> `urteil: geprueft`, `befunde: 2`, 16.518 Byte (`wc -c`, selbst gemessen). Der Prüfer hat alle fünf Bedingungen
> selbst nachgefahren, `ctest` neu ausgeführt und acht Mutationen des Moduls gegen die
> unveränderte Probe gemessen; alle acht machen sie rot.
>
> Die beiden Nebenbefunde reißen keine der fünf Bedingungen und sind je ein eigenes
> Paket geworden: **0040-kernanker-klassenzuteilung** (der fehlende Maßstab für die
> Klassenzuteilung — heute `offen`) und **0041-baulauf-bauverzeichnisse-ueberspringen**
> (`agents/baulauf.py`, heute `blockiert`, siehe dort).
>
> **Eine Aufräumarbeit steht offen und gehört nicht in dieses Paket:** Unter
> `pruefstand/bau/pruefung-0019/` liegt der Mutationsstand des Prüfers. Er ist
> gitignoriert, berührt keine Paketdatei — und wird ab dem nächsten Baulauf ein viertes
> Manifest im Übersetzungsbericht. Der Prüfer hat keine Löschrechte; der Aufruf steht in
> seinem Befund und in 0041.

Vorgaben: `technik.md` T36 (Profilliste, Profilkennung, Strategiekern), dazu T4 (kein
Gleitkomma) und T13 (Kasten `pruefstand`). `spiel.md`, Abschnitt „Das Aktionsprofil und wie
es auf Aktionen wirkt" ist der Wortlaut, gegen den gebaut wird. ADR 0011 für die Sprache.

## 2026-09-02: Dieses Paket ist geteilt worden — lies das zuerst

**Du baust ab heute die Hälfte.** Das Vorratsverfahren (T43) und seine Invariante sind
**Paket 0029**; es hängt an diesem hier und läuft, sobald du fertig bist. Was hier bleibt,
ist die Profilliste, der Strategiekern und — das Wichtigste — die `CMakeLists.txt`, mit der
der Kasten überhaupt erst übersetzt wird.

**Der Grund ist gemessen, nicht vermutet.** Dieses Paket ist dreimal an derselben Stelle
abgebrochen: `src/vorrat.cpp` steht seit dem ersten Versuch bei 25 Zeilen und endet mitten
in `namespace pruefstand::vorrat {`. Beim dritten Mal stand die Reihenfolgevorgabe
(„`CMakeLists.txt` zuerst") schon im Paket und hat nichts geändert. Damit ist die
Reihenfolge nicht die Ursache: Es sind vier Dateien, ein 162-Zeilen-Kopf, zwei Verfahren
und eine Probe mit sieben Bedingungen und zwei absichtlich falschen Fassungen — mehr, als
ein Lauf trägt. Die Hausregel dazu ist eindeutig: *Was zwei Läufe braucht, ist zwei Pakete.*
**Das war mein Zuschnittfehler, kein Befund gegen deine Arbeit.**

**Was du im Baum vorfindest:**

| Datei | Stand | was damit ist |
|---|---|---|
| `include/pruefstand/vorrat.hpp` | 162 Zeilen, vollständig | **fertig, nicht neu schreiben.** Deklariert alle vier Funktionen, auch die beiden aus 0029. |
| `src/vorrat.cpp` | 25 Zeilen, abgeschnitten | **überschreiben.** Nur `strategiekern` und `erzeuge_profilliste` hinein. |
| `test/vorrat_probe.cpp` | `// PLATZHALTER` | deine Probe. |
| `CMakeLists.txt` | `# PLATZHALTER` | dein erster Schritt. |

`runde` und `spiele` bleiben deklariert und **undefiniert**. Das ist kein Fehler: Eine
deklarierte Funktion, die niemand ruft, bricht weder die Übersetzung noch das Binden. Deine
Probe darf sie deshalb **nicht** aufrufen — täte sie es, wäre der Kasten rot, bis 0029
gelaufen ist. Ruf `Abweichung` ebenfalls nicht an; sie gehört zu 0029.

**Dies ist das erste Paket der Rolle `testentwickler`, das je eine Prüfung erreichen soll.**

## Warum dieses Paket jetzt geht und die anderen Prüfstandssachen nicht

Die Profilliste ist reine Kombinatorik über fünf Ganzzahlen. Sie kennt den `Zustand` nicht,
sie ruft `schritt` nicht auf, und weil nie gerundet und nie gezogen wird, braucht sie auch
`kern::zufall` nicht. Damit hängt sie an **keinem** Paket dieses Vorhabens und ist sofort
baubar — während `werte` blockiert ist, `schreiber` auf 0008 wartet und `schritt` mangels
Rechenvorschrift für „Schaden" gar kein Paket hat.

Die Rolle bringt es mit: *„Der Prüfstand für den Selbstspieler … die Mechanik dafür ist
deine Arbeit, die Auswertung seine."* Du baust die Mechanik. Maß 2 und Maß 3 stehen später
vollständig darauf.

## Was du baust

1. **Die `CMakeLists.txt` des Kastens.** Sie ist die eigentliche Leistung dieses Pakets —
   siehe den Abschnitt darunter. Ohne sie ist alles andere für den Übersetzungsbericht
   nicht von einer Datei zu unterscheiden, die es nicht gibt.
2. **Die Profilliste (T36).** Ein Aktionsprofil ist ein Vektor `(a1…a5)` mit
   `ai ∈ {0…5}` und `Σai = 5`; das sind `C(9,4) = 126` Profile. Erzeugt werden sie in
   **lexikographisch aufsteigender** Ordnung von `(a1…a5)` und **nullbasiert**
   durchnummeriert. Diese Nummer ist die **Profilkennung**.
3. **Der Strategiekern, vierwertig (T36).** Je Profil einmal berechnet und mit der Liste
   abgelegt, nicht je Lauf neu: die Aktionsart mit dem größten Anteil unter
   `{1 Position, 2 Beteiligung, 3 Lobby}`, bei Gleichstand die kleinere Kennung. Hebel und
   Sichtbarkeit gehen **nicht** ein. Sind alle drei null, ist der Kern `ohne` — nicht 1.
   Das ist Befund 8 aus einer früheren Prüfung und lässt sich nur hier beheben: Ein
   dreiwertiger Kern zwingt den Gleichstandsbrecher, eine Positionsstrategie zu behaupten,
   in der keine Position vorkommt.
4. **Die Probe** mit den Bedingungen unten.

**Was du nicht baust:** das Vorratsverfahren und seine Invariante (Paket 0029), die
Zulässigkeitsliste aus T32, die Bots, die drei Maße, die Fensterlogik von Maß 3.

## Der Kasten und seine `CMakeLists.txt`

`pruefstand` ist nach T13 ein eigener Kasten. Die `CMakeLists.txt` des Arbeitsbereichs
führt ihn **schon** in `FABRIK_MITGLIEDER` und überspringt ihn, solange er keine eigene
`CMakeLists.txt` hat (Zeile 36–51) — **fass diese Datei nicht an**, sie gehört keinem
Paket und ist genau dafür so gebaut.

Zwei Sachen, an denen der Bau sonst rot wird:

- `baulauf.py` sucht **jede** `CMakeLists.txt` einzeln und ruft auf jeder `cmake`,
  `--build` und `ctest`. Deine muss also **allein** durchlaufen, nicht nur über den
  Arbeitsbereich. `kern/CMakeLists.txt` Zeile 26–29 zeigt, wie: bei
  `PROJECT_IS_TOP_LEVEL` die `werkzeugkette.cmake` des Arbeitsbereichs einbinden und
  `enable_testing()` rufen.
- Sammle Quellen und Proben mit `file(GLOB … CONFIGURE_DEPENDS)` wie der Kern, damit das
  nächste Prüfstandspaket seine Datei danebenlegen kann, statt deine anzufassen. Das ist
  der Kollisionsschutz, nicht Bequemlichkeit — **und seit der Teilung ist es keine Vorsorge
  mehr, sondern eine Zusage:** Paket 0029 legt `src/vorrat_verfahren.cpp` und
  `test/vorrat_verfahren_probe.cpp` daneben und fasst deine `CMakeLists.txt` nicht an. Je
  Probendatei ein eigenes Ziel mit eigenem `add_test`, wie im Kern — sonst hat 0029 keinen
  eigenen Testnamen im Bericht.

Dieses Paket linkt **nichts** — weder `kern` noch eine Fremdabhängigkeit. T3 erlaubt dem
Prüfstand `rayon`; hier wird nichts parallel gerechnet, also kommt es nicht herein.

## Abnahme

1. **Die Profilliste trägt 126 Einträge in lexikographisch aufsteigender Ordnung von
   `(a1…a5)`, nullbasiert nummeriert**, und die beiden Anker aus T36 stimmen: Das
   Referenzprofil `(1,1,1,1,1)` trägt die **Kennung 76**, und die Kennungen **0 bis 5** sind
   genau die sechs Profile `(0,0,0,a4,a5)`. Beide Anker stehen in der Ausgabe der Probe mit
   ihrem Vektor.
2. **Der Strategiekern ist vierwertig, und die Zählung stimmt:** Genau **6** Profile tragen
   den Kern `ohne`, **120** sind klassifiziert (T36). Die Probe nennt beide Zahlen und
   listet die sechs kernlosen Profile mit Kennung und Vektor.
3. **Eine absichtlich falsche Fassung zeigt, dass Bedingung 2 etwas misst.** Ein
   dreiwertiger Strategiekern — der, gegen den Befund 8 geschrieben ist — klassifiziert die
   sechs kernlosen Profile als `POSITION`. Die Probe führt ihn als benannte Abweichung vor
   und weist nach, dass die Prüfung ihn **verwirft**, mit Kennung und Vektor des Profils,
   an dem es auffällt. **Eine Prüfung, die nie rot wird, prüft nichts.** Die zweite falsche
   Fassung, die früher hier stand, gehört zum Vorratsverfahren und ist mit ihm nach 0029
   gegangen; `Abweichung` aus dem Kopf rührst du nicht an.
4. **Kein Gleitkomma, keine Fremdabhängigkeit, keine gemerkte Ablage.**
   `grep -rnE 'float|double'` über deine Quelldateien liefert nichts. Die Liste gehört dem
   Aufrufer, nicht dem Kasten:
   `grep -nE 'static |^[A-Za-z_][A-Za-z0-9_:<>, ]* [a-z_][a-z0-9_]* *='` über
   `vorrat.cpp` zeigt keine veränderliche Ablage ausserhalb einer Funktion; `constexpr` und
   `const` sind zugelassen. **Dieser Mustervergleich ist die vom Prüfer der 0012 korrigierte
   Fassung** — der dortige (`^\s*[A-Za-z_]+ [a-z_]+ =`) findet `u64 zaehler = 0;` nicht,
   weil `[A-Za-z_]+` an der Ziffer abbricht, und trifft damit ausgerechnet die Typen dieses
   Vorhabens nicht. Der Prüfer führt ihn zusätzlich von Hand nach; ein Mustervergleich, der
   nichts findet, ist kein Nachweis, dass nichts da ist.
5. **Der Übersetzungslauf führt die Probe wirklich aus.** In
   `befunde/uebersetzung-<datum>.md` steht unter `ctest --test-dir …/pruefstand/bau` ein
   Test mit Namen und `Passed`. **Das ist die Bedingung, an der dieses Paket dreimal
   vorbeigelaufen ist**, und sie ist der Grund, warum es überhaupt geteilt wurde: Ein
   Prüfstand, den `ctest` nicht aufruft, ist im Bericht von einem, den es nicht gibt, nicht
   zu unterscheiden — `ergebnis: ok` bei „No tests were found!!!".

Der Übersetzungslauf ist der zweite Nachweis für die Bedingungen 1 bis 3: Stimmt eine Zahl
nicht, ist `ctest` rot. Der Prüfer urteilt trotzdem gegen die Liste — grün heisst „die
Zahlen passen zueinander", nicht „die Zahlen sind die richtigen".

## Die Reihenfolge, in der du die drei Dateien anlegst

Sie ist zum zweiten Mal vorgeschrieben, und beim ersten Mal hat sie nichts bewirkt —
deshalb steht jetzt die Teilung dahinter statt nur die Ermahnung. Halte sie trotzdem ein:

1. **`CMakeLists.txt`** — der Glob-Block aus dem Abschnitt *Der Kasten und seine
   `CMakeLists.txt`*, wenige Zeilen, keine Denkarbeit.
2. **`test/vorrat_probe.cpp`** mit einem `main`, das sofort 0 zurückgibt.
3. Danach `src/vorrat.cpp`, dann die Probe füllen.

Nach Schritt 2 ist der Kasten **im Bericht sichtbar**: `ctest` nennt `vorrat_probe`
namentlich, und jeder spätere Abbruch macht den Bau **rot** statt still. Das ist der
Unterschied zwischen den drei abgebrochenen Läufen und einem, aus dem der nächste Lauf
etwas erbt.

**Achte auf den Kopf:** `src/vorrat.cpp` liegt abgeschnitten im Baum und endet mitten in
`namespace pruefstand::vorrat {`. Sobald deine `CMakeLists.txt` steht, sammelt der Glob
diese Datei ein und der Bau wird **rot**, bis du sie überschrieben hast. Das ist gewollt
und die richtige Reihenfolge — aber schreib sie in **demselben** Lauf, sonst hinterlässt
du einen roten Kasten für alle anderen Pakete.

Wenn du merkst, dass es knapp wird: **ein Kasten, der übersetzt und dessen Probe zu wenig
prüft, ist mehr wert als ein vollständiger Entwurf, den niemand baut.** Der Prüfer kann
das erste zurückgeben; das zweite sieht er gar nicht.

## Was ausdrücklich kein Befund ist

Der Modulname, die Aufteilung auf Kopf und Quelle, ob der Kern `ohne` als eigener
Aufzählungswert oder als leerer Wert geführt wird, die Benennung der Hilfsfunktionen, das
Ausgabeformat der Probe jenseits der in Bedingung 1 bis 3 genannten Zahlen. `specs/`
schweigt dazu.

**Auch kein Befund:** dass `runde` und `spiele` im Kopf deklariert und nirgends definiert
sind. Das ist der Schnitt zu 0029 und ausdrücklich so gewollt.

**Auch kein Befund:** dass `pruefstand` nach T13 auf `schnittstelle` zeigen darf und es
hier nicht tut. T13 gibt die erlaubte Richtung an, keine Pflicht, sie auszunutzen.

## Eine offene Entwurfsfrage, die dich nicht blockiert

Ob das Vorratsverfahren später aus `pruefstand` heraus auch vom Bruchtester (T30 Prüfung 5)
gerufen wird, hat der Architekt nicht entschieden. Für dieses Paket ist es gleichgültig:
Die Mechanik ist dieselbe, und die Frage ist eine Verdrahtungsfrage. Sie steht in
`rueckstand.md`, damit sie nicht in deinem Paket verschwindet.

## Übergang auf `gebaut` — 2026-09-02, Projektmanager

**Ich habe `status: gebaut` selbst gesetzt. Der `testentwickler` kann es nicht.** Seiner
Rollendatei fehlt der Satz „Setze im Arbeitspaket `status: gebaut`" — sie erwähnt das Wort
`gebaut` überhaupt nicht, nachgemessen am 2026-09-02 über alle Rollendateien. Ohne den
Übergang bliebe das Paket `offen` und würde jeden Lauf neu gebaut, obwohl es fertig
gearbeitet ist.

**Was ich gemessen habe:**

| Messung | Ergebnis |
|---|---|
| Commits `ef5c48c` (19:03) und `5f1be89` (19:51), beide „testentwickler: 0019-…" | vorhanden |
| die vier Dateien aus `dateien` | 4.561 + 6.807 + 5.001 + 21.548 = **37.917 Byte** |
| `vorrat_probe` im Übersetzungsbericht `befunde/uebersetzung-2026-09-02.md` | **namentlich und `Passed`**, in allen drei Manifesten |

Die letzte Zeile ist die Grenze, die ich mir für diesen Übergang gesetzt habe, und sie ist
hier erfüllt: Ein Kasten ohne benannten Test ist im Bericht von einem, den es nicht gibt,
nicht zu unterscheiden. Bei diesem Paket habe ich den Übergang im zehnten Lauf
**ausdrücklich nicht** gesetzt, weil damals ein sichtbarer Torso im Baum lag — 29 Byte, wo
jetzt 37.917 stehen.

**Was ich nicht behaupte:** dass die fünf Bedingungen erfüllt sind. Das misst der
`test-pruefer`. `gebaut` ist eine Meldung, keine Abnahme.

## Rückläufe

0.
