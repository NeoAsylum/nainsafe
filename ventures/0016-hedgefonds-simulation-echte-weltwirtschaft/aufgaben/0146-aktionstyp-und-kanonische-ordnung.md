---
id: 0146-aktionstyp-und-kanonische-ordnung
rolle: kernbauer
status: offen
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
