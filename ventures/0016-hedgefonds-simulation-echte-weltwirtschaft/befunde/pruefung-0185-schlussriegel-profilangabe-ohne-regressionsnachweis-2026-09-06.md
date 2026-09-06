---
typ: pruefung
paket: 0185-schlussriegel-profilangabe-ohne-regressionsnachweis
pruefer: test-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Abnahmebedingungen selbst gefahren, dazu zwei eigene Mutanten der Werkzeugkette an anderen Stellen als die eingebauten Brueche -- alle rot gefangen, am unveraenderten Baum RC 0 vor wie nach der Aenderung.
befunde: 0
---

# Pruefung 0185: Profilangabe des Schlussriegels bekommt ihren Regressionsnachweis

Geaenderter Stand: Commit `adbf4a8` (2026-09-06). Er fasst genau
`befunde/pruefung-0066/nachbau.py`, die Paketdatei und das Logbuch des Bauers an --
die `dateien`-Liste ist eingehalten, `werkzeugkette.cmake`, `bauwege.py` und
`werkzeuge/schlussriegel/CMakeLists.txt` sind unberuehrt (`git show --numstat adbf4a8`).
Gemessen an HEAD `07e5a95`; `git status` der Messdateien war sauber, $TMPDIR hatte
2,5 GB frei.

## Bedingung 1: Die Probe wird rot, wenn die Angabe bricht -- an beiden Haelften einzeln

**Alle drei eingebauten Brueche selbst gefahren** (nicht aus dem GEBAUT-Absatz
uebernommen), Aufruf je `python3 befunde/pruefung-0066/nachbau.py --bruch=<name>`:

| Bruch | RC | gerissene Haelfte laut Meldung | 22 Baeume |
|---|---|---|---|
| `wahrheitswort` | 1 | 'Wahrheitswort' unter OFF: nennt 'wahr', erwartet 'falsch' | 0 Abweichungen |
| `rohwert` | 1 | 'roher Wert' unter OFF: nennt 'ON', konfiguriert 'OFF' | 0 Abweichungen |
| `ohne` | 1 | alle vier Haelften-Meldungen, dazu "ON und OFF melden zeichengleich" | 0 Abweichungen |

Jeder Lauf nennt die gerissene Haelfte namentlich, und die 22 Baeume bleiben dabei
gruen -- es reisst wirklich die neue Bedingung, nicht etwas anderes. Die untergeschobene
Fassung entsteht aus der von `kette_holen` geholten Fassung (`kette_verbiegen`), nicht
von Hand; die Trefferbremse (`count != 1` -> Abbruch vor dem ersten Baum) habe ich an
`5d5e2d6 --bruch=ohne` ausgeloest gesehen (RC 1, "kommt 0-mal vor"), ein unbekannter
Bruchname (`--bruch=tippfehler`) endet ebenfalls mit RC 1 und der Namensliste.

**Zwei eigene Mutanten an anderen Stellen als die eingebauten Brueche** -- Arbeitskopien
unter `bau/test-pruefer-0185/` (gitignoriert, am Ende entfernt), je eigene
`NACHBAU_ABLAGE`, Trefferbremse `count == 1` je Nadel:

- **mutA:** `if(FABRIK_SANITIZER)` -> `if(NOT FABRIK_SANITIZER)` an der Berechnung des
  Wahrheitsworts (`werkzeugkette.cmake:1100`, andere Stelle als der `wahrheitswort`-
  Bruch, der `set(profilwort "falsch")` festnagelt). RC 1, Haelfte 'Wahrheitswort'
  reisst unter **beiden** Profilen (ON nennt 'falsch', OFF nennt 'wahr'), 0 Abweichungen.
- **mutB:** `message(STATUS` -> `message(DEBUG` an der Riegelmeldung -- die Zeile
  verschwindet ganz aus der Ausgabe. Das ist der `zeile is None`-Zweig, den keiner der
  drei eingebauten Brueche trifft. RC 1, je Profil "in der Ausgabe steht ueberhaupt
  keine Zeile des Schlussriegels ... beide Haelften fehlen", 0 Abweichungen.

Der vierte Rotnachweis (alter Stand ohne Bruch): `python3 ... 5d5e2d6` endet mit RC 1,
vier Haelften-Meldungen, der Gleichheitsmeldung und der Zeile "(Der Stand 5d5e2d6 liegt
vor Paket 0137 ... Aussage ueber ihn, nicht ueber HEAD.)" -- wie im Paket beschrieben
und im Skriptkopf als bewusste Verhaltensaenderung alter Aufrufe festgehalten.

Die dritte Teilzusicherung (Koepfe von ON und OFF unterscheiden sich) ist logisch
redundant zur Konjunktion der beiden Haelften-Pruefungen -- stimmen beide Haelften,
unterscheiden sich die Koepfe zwangslaeufig. Sie ist ein Zusatzgurt; ein Mutant, der nur
sie reisst, ist nicht konstruierbar. Kein Befund.

## Bedingung 2: Am unveraenderten Baum aendert sich kein Urteil

- **Handaufruf an HEAD:** `python3 befunde/pruefung-0066/nachbau.py` -> alle 22 Baeume
  im Soll, Positivkontrolle `bau code=2, 1 Fehler` (`-Werror=float-conversion`), beide
  Profilhaelften genannt und verschieden, `0 Abweichung(en) vom Soll.`, **RC 0**.
- **Drift-Isolation alt gegen neu am selben heutigen Baum:** die Vorfassung
  `adbf4a8^:.../nachbau.py` in einer Arbeitskopie gefahren -> ebenfalls RC 0,
  0 Abweichungen, Positivkontrolle rot bauend. Kein Urteil kippt durch das Paket.
- **`ctest` in beiden Profilen**, frisch konfigurierte und gebaute Baeume unter `bau/`:
  ON `100% tests passed, 0 tests failed out of 19`, OFF dasselbe;
  `schlussriegel_nachbau` bestanden in 4,90 s (ON) bzw. 4,85 s (OFF), kalt.
- **18 gegen 19 Proben ist Korpusdrift, kein Widerspruch:** Der Bauer mass 18 an seinem
  Bezugsstand `6456047`..`885449e`; der 19. Test kam mit `cf9e15a`
  (0180-zahlwortriegel) **nach** dem Baucommit dazu. Die Behauptung des Nachweises,
  `git log 6456047..885449e` sei ueber die drei gemessenen Dateien leer, habe ich
  nachgefahren: leer.
- **Laufzeit und Zeitgrenze:** meine kalten 4,9 s passen zur Groessenordnung des
  Nachweises (4,6-4,8 s nachher); `TIMEOUT 600` steht unveraendert in
  `werkzeuge/schlussriegel/CMakeLists.txt:122`.

## Wonach ich sonst gesucht habe

- **Abgeschwaechte Tests:** Der Diff `adbf4a8^..adbf4a8` an `nachbau.py` ist rein
  additiv; die 8 entfernten Zeilen sind Signatur- und Pfadumbauten. Die Rueckgabezeile
  wurde von `abweichungen or positiv_stumpf` auf `... or risse` **verschaerft**, nichts
  gesenkt, nichts uebersprungen.
- **Negativliste des Pakets:** Meldung nicht angefasst (Kette nicht im Commit), nur
  `p_positiv` faehrt beide Profile (Laufzeit +~0,4-0,7 s statt Verdoppelung), keine
  Zielzahl in der Abnahme ausgeschrieben, `bauwege.py` unberuehrt.
- **Falsch-gruen-Wege im Pruefcode:** `FABRIK_SANITIZER=(\S*)` faengt auch den leeren
  Wert, der Kopfvergleich endet am ersten Doppelpunkt vor dem Zaehlwerk, ein
  cmake-Fehlschlag ohne Riegelzeile faellt in den None-Zweig (durch mutB belegt).
  Der Handaufruf ohne `--bruch` nutzt denselben Ablagepfad wie vor dem Paket
  (`nachbau0066-HEAD`), die Abnahmen 0103/0108 sehen ihn unveraendert.

Keine Befunde. Meine Baubaeume und Arbeitskopien unter `bau/test-pruefer-0185/` sind
entfernt.
