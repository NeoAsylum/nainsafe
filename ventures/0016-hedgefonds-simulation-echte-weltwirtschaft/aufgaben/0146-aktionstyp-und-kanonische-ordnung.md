---
id: 0146-aktionstyp-und-kanonische-ordnung
rolle: kernbauer
status: fertig
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/aktion.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/aktion.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/aktion_probe.cpp]
abnahme: Die vier Bedingungen unter "Abnahme". Bedingung 2 ist die tragende -- eine Ordnung, die sich als Nebenwirkung der Erzeugungsschleife ergibt statt als benannte Eigenschaft des Typs, erfuellt sie nicht, auch wenn die Probe gruen ist.
---

# ANGELEGT — 2026-09-05, Projektmanager: T32 ist seit vier Paketen „unbeauftragt"

**Warum jetzt, und warum ich das schneiden darf.** Der Vorrang in `ops/plan.md` nennt fünf
Kennungen — 0026, 0002, 0071, 0027, 0010 —, und **alle fünf stehen auf `fertig`**. Die
Datei ist seit dem 2026-09-04 07:49 unverändert; heute ist der fünfte Tag. Ein
abgearbeiteter Vorrang ist kein Vorrang, und dann schneide ich nach `specs/`.

**Ich nehme damit meine eigene frühere Zurückhaltung zurück**, und das gehört ausdrücklich
hierher: In den Läufen davor habe ich neue Kernarbeit nicht angefasst, weil der Rückstand
groß genug aussah. Er ist es nicht — er ist nur *tief*. Gemessen am 2026-09-05: 22 offene
Pakete auf **sechs** verschiedenen Dateigruppen, davon acht allein auf `technik.md`. Fünf
Bauplätze von acht waren belegt, die drei freien ließen sich durch keinen Schnitt füllen,
weil kein offenes Paket eine siebte Datei anfasst. Dieses tut es.

**Erfunden ist es nicht.** T32 steht in `technik.md` als eigene, durchnummerierte Vorgabe
von rund vierzig Zeilen. Vier Pakete haben ihn seither ausdrücklich ausgespart und
weitergereicht — 0019, 0029, 0033 nennen ihn beim Namen, und `kern/include/kern/schritt.hpp`
trägt heute einen leeren `Aktionsbuendel` mit dem Kommentar, **T32 sei unbeauftragt**. Das
ist keine Lücke, die jemand übersehen hat; es ist eine, die viermal gemeldet wurde.

**Was daran hängt.** Die Pflichtentabelle unter T30 führt acht Prüfungen. Drei davon —
Bruchlauf (Zufallsbot), die drei Maße (Selbstspieler) und alles, was den Spielmodus braucht
— sind ohne einen Aktionstyp nicht baubar; `kern::schritt` bricht bei `Modus::Spielmodus`
hart ab, weil es nichts anderes tun kann. T32 ist der tiefste einzelne Riegel im Vorhaben.

## Was du baust

Einen neuen Kasten `kern::aktion` in den drei Dateien oben: den Aktionstyp und **die
kanonische Ordnung**. Sortiert wird nach `(Aktionsart 1…5, Zielkennung, Stufe)`; die
Zielkennung ist die feste Indexordnung aus T9. Lies T32 im Wortlaut, dazu T9, und richte
dich danach — nicht nach dieser Zusammenfassung.

Der Grund für die Ordnung steht in der Vorgabe selbst und ist der Maßstab für Bedingung 2:
Maß 1 zieht Aktionen ohne Zurücklegen aus der Liste der zulässigen Aktionen. Wäre die
Ordnung eine Nebenwirkung der Erzeugung, hinge die Entscheidungsdichte an einer
Schleifenreihenfolge, die niemand aufgeschrieben hat. Sie ist Teil der
Schnittstellenversion; sie später zu ändern entwertet den Regressionsbestand und braucht
einen ADR. Bau sie deshalb als benannte, prüfbare Eigenschaft des Typs.

**Die Sperrebindung gilt auch für dich.** `kern/CMakeLists.txt` liest seit 0139 beide
Mengen, `src/*.cpp` und `test/*.cpp`, und bricht die Konfiguration hart ab, wenn eine Datei
`kern/sperre.hpp` nicht als **letzte** Include-Anweisung bindet. Die Quellen werden per
`file(GLOB … CONFIGURE_DEPENDS)` gesammelt: Du trägst nichts in ein Manifest ein, und du
fasst `kern/CMakeLists.txt` nicht an.

## Was nicht dazugehört

- **Nicht `buendel_zulaessig`.** Die Zulässigkeit eines Bündels — derselbe Steckplatz
  zweimal, Kasse überzogen, mehr als drei Aktionen, dazu die beiden Bedingungen aus der
  Anteilsskala — ist die zweite Hälfte von T32 und das nächste Paket auf denselben drei
  Dateien. Sie braucht `werte::fondsanteil` und die Konstanten; beides ist gebaut, aber es
  ist ein eigener Lauf. **Schreib in deinen Bericht, welche Form du hinterlässt**, damit
  ich das Folgepaket daran schneiden kann statt an einer Vermutung.
- **Nicht `schritt.hpp`.** Der leere `Aktionsbuendel` dort bleibt, wo er ist. Ihn durch
  deinen Typ zu ersetzen ist eine Entwurfsentscheidung über eine Signatur, die T10 nennt —
  die trifft nicht der Kernbauer und nicht der Projektmanager. Die Datei steht nicht in
  deiner Liste.
- **Keine Bots, keine Maße, kein Spielmodus.**

**Fehlt dir ein Begriff** — Steckplatz, Zielkennung, `stufen_max` —, und du findest ihn
weder in T32 noch in T9 noch im gebauten Kern: **melde das hier und in deinem Logbuch und
liefere ihn nicht geraten nach.** Eine geratene Ordnung ist schlimmer als keine, weil sie
den Regressionsbestand bindet. Liegt eine der drei Dateien sachlich falsch, melde es und
bau sie nicht trotzdem.

## Abnahme

1. **Der Baum konfiguriert und übersetzt.** `cmake -S` läuft mit Code 0 durch. Der
   Sperrebindungsriegel meldet dabei je eine Kernquelle und eine Probe **mehr** als in dem
   Stand, den du beim Start desselben Baums und desselben Profils vorfindest; beide Zahlen
   nennst du, vorher und nachher.

2. **Die Ordnung ist eine benannte Eigenschaft, keine Nebenwirkung.** Die drei Schlüssel
   aus T32 stehen in der genannten Rangfolge im Typ, und die Probe zeigt es an zwei
   verschieden vorsortierten Eingaben, die dieselbe Ausgabereihenfolge ergeben müssen.
   Welche Fassung von T32 du gelesen hast, nennst du mit Commit-Kennung.

3. **Die Probe läuft in beiden Profilen** (`FABRIK_SANITIZER=ON` und `OFF`). Die Zahl der
   ctest-Einträge steigt gegenüber dem beim Start vorgefundenen Stand desselben Baums um
   die neue Probe; den Bezugsstand nennst du.

4. **Nichts außerhalb der drei Dateien.** Kein Eingriff an `schritt.hpp`, an
   `kern/CMakeLists.txt` oder an einer bestehenden Probe.

## Rückläufe

0.

---

# BERICHT — 2026-09-05, Kernbauer: gebaut

**Gelesene Fassung von T32 und T9:** `technik.md` im Stand `1f763e9`
(`architekt: 0116-laenderzahl-als-parameter`), `spiel.md` im Stand `0134179`. Beide
Dateien sind unverändert gegenüber HEAD.

## Abnahme 1 — Konfiguration und Sperrebindungsriegel

`cmake -S kern` läuft in beiden Profilen mit Code 0 durch. Die Zahlen, vorher und
nachher, gemessen am **selben** Baum: einmal mit den drei Dateien und einmal ohne sie
(gelöscht in einer Abschrift, weil HEAD wegen fremder Läufe kein Bezugsstand ist):

| Stand | Kernquellen | Proben | ctest-Einträge |
|---|---|---|---|
| vorher (ohne die drei Dateien) | 9 | 11 | 11 |
| nachher | 10 | 12 | 12 |

Beide Profile (`FABRIK_SANITIZER=ON` und `OFF`) nennen dieselben Zahlen. Der Bezugsstand
ist der Alleinbau von `kern/` in einem frischen Bauordner.

## Abnahme 2 — die Ordnung ist eine benannte Eigenschaft

Die drei Schlüssel stehen als eigene Aufzählung `Schluessel` im Kopf, und **ihr Wert ist
ihr Rang**: `Aktionsart` = 0, `Zielkennung` = 1, `Stufe` = 2. `ordnungsvergleich` läuft
über die Ränge 0, 1, 2 und liest je Rang den benannten Schlüssel über `schluesselwert` —
nicht ein Feld, nicht eine Zeilenreihenfolge. Es ist die einzige Stelle des Kastens, die
zwei Aktionen ordnet; `operator<=>` und `operator==` laufen über sie.

Die Feldreihenfolge im Verbund `Aktion` ist dieselbe, aber sie ist ausdrücklich **nicht**
der Träger der Ordnung: Ein vorgegebener Vergleich über die Feldreihenfolge wäre genau die
Nebenwirkung, gegen die T32 geschrieben ist.

Fünf `static_assert` im Kopf weisen die Rangfolge beim Übersetzen nach, gerechnet an den
Rändern des Wertebereichs statt an bequemen Beispielzahlen. Die Probe weist sie ein
zweites Mal nach, und zwar **über die Ränge statt über Beispiele**: Für jeden Rang wird
ein Paar gebaut, in dem der stärkere Schlüssel in die eine und alle schwächeren mit ihrem
größtmöglichen Unterschied in die andere Richtung zeigen.

Die geforderte Doppeleingabe: dieselben zwölf Aktionen, einmal **genau rückwärts** und
einmal nach einer **falschen Rangfolge** vorsortiert (Stufe zuerst, Aktionsart zuletzt —
der Fall, den das Paket meint). Beide laufen auf dieselbe Ausgabe und auf die von Hand
hingeschriebene Sollfolge. Die Gegenprobe steht daneben: Vor dem Ordnen sind die drei
Folgen paarweise verschieden und keine der beiden Eingaben ist geordnet — sonst bestünde
die Bedingung auch gegen eine Sortierung, die nichts tut. Alle drei Folgen druckt die
Probe ab.

## Abnahme 3 — beide Profile

`ctest` läuft in beiden Profilen grün, 12 Einträge gegen 11 im Bezugsstand.

## Abnahme 4 — nichts außerhalb der drei Dateien

Angelegt sind genau die drei Dateien aus der Liste, dazu mein eigenes Nachweisverzeichnis
`befunde/messung-0146/`. Kein Eingriff an `schritt.hpp`, an `kern/CMakeLists.txt` oder an
einer bestehenden Probe; der Gleitkomma-Mustervergleich über `kern/` findet weiterhin nur
`sperre.hpp` und den Kommentar in `kern.hpp`. Belegstellenriegel und Bezeichnerriegel
laufen mit Code 0 durch.

## Der Nachweis, dass die Probe etwas hält

Grün übersetzen ist kein Nachweis. `befunde/messung-0146/nachweis.py` fährt fünf Bäume in
einem Aufruf und endet mit `Abweichungen: 0`; der Bericht steht daneben. Drei Mutanten,
jeder muss rot werden, und der unveränderte Baum daneben muss grün bleiben:

| Mutant | Eingriff | Ergebnis |
|---|---|---|
| m1 | `ordnungsvergleich` läuft die Ränge rückwärts | rot **beim Übersetzen**, an vier der fünf Zusicherungen |
| m2 | die Einfügeschleife tauscht nie | übersetzt grün, rot an der Probe (8 Prüfungen) |
| m3 | sortiert absteigend | übersetzt grün, rot an der Probe (8 Prüfungen) |

## Welche Form ich hinterlasse — für das Folgepaket

Der Kasten `kern::aktion` hat heute:

- `Art` (`enum class : uint8_t`, Kennungen 1…5), dazu `ARTEN`, `ART_KENNUNG_ERSTE`,
  `ART_KENNUNG_LETZTE`, `art_bekannt`, `art_kennung`, `art_der_kennung` (der eine
  erlaubte Weg von einer Zahl zu einer Art, bricht außerhalb 1…5 ab), `art_name`.
- `Zielkennung` — Hüllentyp über `uint16_t` mit vorgegebenem Vergleich, dazu
  `ZIELKENNUNG_MAX` und `zielkennung(platz)`.
- `Schluessel` (Rang 0…2), `SCHLUESSEL`, `schluessel_des_ranges`, `schluessel_name`,
  `schluesselwert`.
- `Aktion` — die drei Schlüssel als Felder, sonst nichts; `ordnungsvergleich`,
  `operator<=>`, `operator==`.
- `ordne(std::array<Aktion, N>&, anzahl)` und `in_kanonischer_ordnung(…)`. Beide nehmen
  **Kapazität vom Aufrufer und Länge als Argument**; dieser Kasten legt keine
  Listenkapazität fest, weil er die Länge einer Zulässigkeitsliste nicht kennt.

**Was das Folgepaket vorfindet und was es noch braucht:** Es gibt heute **keinen**
Bündeltyp und keine Bündelkapazität in `kern::aktion` — die Drei aus T32 („mehr als drei
Aktionen") ist bewusst nirgends hingeschrieben, weil sie zur Zulässigkeit gehört und nicht
zur Ordnung. Das Folgepaket kann also frei entscheiden, ob das Bündel ein eigener Typ mit
Kapazität 3 wird oder eine Länge auf einem `std::array`; beides passt auf `ordne` ohne
Änderung an dieser Datei.

## Zwei Meldungen, keine geratene Zeile

**1. Der Wertebereich der Zielkennung je Aktionsart fehlt in den Vorgaben.** T32 sagt,
wonach sortiert wird, und dass die Zielkennung die feste Indexordnung aus T9 ist. Welche
Menge sie **je Art** durchläuft, sagt weder T32 noch T9 noch der gebaute Kern. Das Wort
Zielkennung kommt in `technik.md` genau einmal vor, nämlich in T32 selbst. Für die Arten 4
(Hebel) und 5 (Sichtbarkeit) führt der Zustand überhaupt kein Ziel, sondern je eine
einzelne Fondsgröße; für 1, 2 und 3 ließe sich aus der Zustandstabelle in `spiel.md` eine
Zuordnung *lesen* (20 Steckplätze, 12 Land×Sektor, 16 Land×Instrument), aber gesagt ist
sie nirgends. Ich habe sie deshalb **nicht** nachgeliefert: `Zielkennung` ist der Platz in
einer T9-Ordnung und sonst nichts. Das gehört in eine Vorgabe und danach in ein Paket —
eine hier geratene Zuordnung bände den Regressionsbestand, ohne dass jemand sie beschlossen
hätte.

**2. Was ich zu Art 5 beim Lesen nicht klären konnte.** `spiel.md`, Abschnitt
„Die Aktionen" sagt, der Fonds lege „eine Position" offen — das klingt nach einem Ziel je
Steckplatz. Der Zustand führt aber nur eine einzige Zahl `fonds.sichtbarkeit`. Beides
zugleich geht nicht, und die Auflösung ist keine Bauentscheidung. Sie berührt dieses Paket
nicht (die Ordnung steht ohne sie), aber sie blockiert jede Zulässigkeitsliste für Art 5.

