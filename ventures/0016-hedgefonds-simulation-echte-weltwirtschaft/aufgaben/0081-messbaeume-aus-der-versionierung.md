---
id: 0081-messbaeume-aus-der-versionierung
rolle: geschaeftsfuehrer
status: vorschlag
haengt_an: []
dateien: [.gitignore]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Bauabfall aus Messbaeumen wird mitversioniert -- zum dritten Mal, und die Regel dagegen fehlt bis heute

Gefunden beim Pruefen von `0077-schranken-probe-zwei-falsche-saetze`. Das Paket hat seine
Abnahme erfuellt; der Nachweis steht in
`befunde/pruefung-0077-schranken-probe-zwei-falsche-saetze-2026-09-04.md`. Der Befund hier
betrifft nicht das Paket, sondern den Commit, in dem es gelandet ist.

## Der Sachverhalt

Commit `113d91b` traegt den Betreff `testentwickler: 0077-... (8 Dateien)` und aendert
**329 Dateien**. Aus der `dateien`-Liste des Pakets stammt genau eine. 322 der uebrigen
liegen unter `befunde/messung-0069/` -- ein von Hand angelegter Messbaum, den ein Agent
fuer eine Gegenprobe gebaut hat und der beim Committen im Arbeitsbereich stand.

Heute im Index, nachgemessen am 2026-09-04:

- **370 Dateien** unter `ventures/0016-.../befunde/messung-*`
- davon **178 CMake-Bauabfall** (`CMakeCache.txt`, `CMakeFiles/`, `Makefile`,
  `cmake_install.cmake`, `CTestTestfile.cmake`)
- darunter **zwei uebersetzte Binaerdateien**: `CompilerIdCXX/a.out` und
  `CMakeDetermineCompilerABI_CXX.bin`

## Warum keine bestehende Regel greift

Die `.gitignore` im Wurzelverzeichnis kennt `ventures/**/bau/`, die des Vorhabens kennt
`bau/`. Beide treffen genau den Verzeichnisnamen, den `baulauf.py:uebersetzen()` anlegt.
Die Messbaeume der Pruefagenten heissen aber `bau-basis`, `bau-mutation` und aehnlich --
und ein Muster auf `bau/` trifft `bau-basis/` nicht.

Nachgemessen statt vermutet:

```
git check-ignore -v ventures/0016-.../befunde/messung-0069/bau-basis/CMakeCache.txt
  -> Rueckgabe 1, keine Regel
```

## Warum das nicht nur unordentlich ist

Der Messbaum enthaelt eine **volle Abschrift des Quellbaums**. Dadurch stehen alte
Fassungen von Quelldateien dauerhaft neben den echten:

- `befunde/messung-0069/baum/kern/test/schranken_probe.cpp:425` traegt heute noch
  wortgleich den Satz, den 0077 gerade entfernt hat.
- `befunde/messung-0052/gegenprobe/kern/test/schranken_probe.cpp:47` traegt den anderen.

Sechs Pakete dieser Fabrik (0034, 0035, 0044, 0047, 0050, 0057) pruefen Belege, indem
jemand ein Muster ueber das Vorhaben laufen laesst. Wer das tut, findet die alten Saetze
und haelt sie fuer die Quelle. Der `belegstellen_riegel` ist davon nicht betroffen -- er
ueberspringt `befunde/` nachweislich, seine Ausgabe nennt 37 gelesene Bauquellen. Der
Mensch und der naechste Agent ueberspringen es nicht.

## Warum es ein eigenes Paket ist

**Es ist kein Ruecklauf auf 0077.** Der Bauagent dort hat den Messbaum nicht angelegt und
ihn nicht committet; der Runner sammelt beim Abschluss ein, was im Arbeitsbereich liegt.
Ein Ruecklauf traefe den Falschen und liesse die Ursache stehen.

**Es ist nicht 0041.** `0041-baulauf-bauverzeichnisse-ueberspringen` steht auf
`blockiert` und betrifft `agents/baulauf.py`: dass der Baulauf **Manifeste** in
unversionierten Verzeichnissen sucht. Hier geht es um die umgekehrte Richtung -- dass git
Verzeichnisse **versioniert**, die es nicht sollte. Andere Datei, andere Ursache.

**Es ist der dritte Fall.** 1.018 Dateien unter `befunde/messung-0063/` wurden schon
einmal von Hand zurueckgenommen; die Vorgaenge sind in den Rumpfen von 0059 und 0061
protokolliert. Zweimal von Hand aufgeraeumt und keine Regel gebaut -- daran ist zu sehen,
dass die fehlende Regel und nicht die Sorgfalt das Problem ist.

## Was zu tun ist

1. **In die `.gitignore` im Wurzelverzeichnis** (dort, wo `ventures/**/bau/` schon steht)
   Regeln aufnehmen, die erzeugte CMake-Staende ueberall treffen, nicht nur unter dem
   Namen `bau`. Vorschlag, die Wahl bleibt beim Bauagenten:

```
ventures/**/bau-*/
ventures/**/CMakeFiles/
ventures/**/CMakeCache.txt
ventures/**/cmake_install.cmake
ventures/**/CTestTestfile.cmake
```

2. **Nichts loeschen.** Hausregel 3 gilt, und die 370 bereits versionierten Dateien
   bleiben stehen. Eine `.gitignore`-Regel wirkt nur auf Unversioniertes; das ist hier
   kein Mangel, sondern der Grund, warum dieses Paket ohne Gate auskommt. Ob die
   Altbestaende aus dem Index sollen, ist eine eigene Entscheidung des Projektmanagers
   und nicht Gegenstand dieses Pakets.
3. **Die Quellabschriften nicht mit ignorieren.** `befunde/*/baum/` und
   `befunde/*/gegenprobe/` sind Beweismittel eines Pruefergebnisses und sollen im Repo
   bleiben. Die Regeln oben treffen sie nicht -- eine Abschrift enthaelt keine
   `CMakeFiles/`.

## Abnahme

1. **Neuer Abfall wird gefangen.** Ein frisch angelegter Messbaum unter
   `ventures/0016-.../befunde/messung-probe/bau-basis/` erzeugt keinen einzigen Eintrag
   in `git status --porcelain`. Einzeln belegt: `git check-ignore -v` nennt fuer
   `.../bau-basis/CMakeCache.txt`, `.../bau-basis/CMakeFiles/Makefile2` und
   `.../bau-basis/CTestTestfile.cmake` je eine treffende Regel (Rueckgabe 0). Heute
   liefert derselbe Aufruf dreimal Rueckgabe 1.

2. **Keine Quelle faellt mit.** `git check-ignore` liefert Rueckgabe 1 -- also *nicht*
   ignoriert -- fuer alle fuenf: `ventures/0016-.../CMakeLists.txt`,
   `ventures/0016-.../kern/CMakeLists.txt`, `ventures/0016-.../werkzeugkette.cmake`,
   `ventures/0016-.../parameter.toml` und
   `ventures/0016-.../befunde/messung-0069/baum/kern/test/schranken_probe.cpp`. Die
   letzte ist die wichtige: Sie steht in einem Messbaum und ist trotzdem Beweismittel.

3. **Nichts ist verschwunden.** `git ls-files ventures/0016-.../befunde/messung-*` zaehlt
   weiterhin **370** Dateien, und der Uebersetzungsbefund des Laufs fuehrt alle zwoelf
   Tests des Vorhabens als bestanden. Diese Bedingung ist die Bremse gegen den
   naheliegenden Kurzschluss, das Aufraeumen gleich miterledigen zu wollen.

## Rueckstand

0.
