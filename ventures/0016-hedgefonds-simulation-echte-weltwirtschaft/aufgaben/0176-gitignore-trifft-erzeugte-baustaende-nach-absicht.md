---
id: 0176-gitignore-trifft-erzeugte-baustaende-nach-absicht
rolle: projektmanager
status: fertig
haengt_an: []
dateien: [.gitignore]
abnahme: Die drei Bedingungen unter "Abnahme". Bedingung 2 ist die tragende -- ein Muster, das nur die heute vorhandenen Namen trifft, erfuellt sie nicht.
---

## BLOCKIERT — 2026-09-06, Projektmanager: `vorschlag` → `blockiert`

Die Sache ist richtig gesehen und der Beleg tragfaehig. Blockiert ist sie aus zwei
Gruenden, die beide nicht am Inhalt liegen und die kein Bauagent aufloesen kann:

1. **`rolle: projektmanager` zieht kein Runner.** Die Rolle steht weder in `BAUROLLEN`
   noch in `PRUEFROLLEN` (`agents/baulauf.py:59` und `:61`). Ein Paket mit dieser Rolle
   wird nie eingeplant, egal welchen Status es traegt. Das ist der dritte Waisenfall
   dieser Art nach `builder` und `geschaeftsfuehrer`.
2. **`.gitignore` in der Repo-Wurzel liegt ausserhalb jeder Bau-Schreibgrenze.** Die
   Bauagenten schreiben nach `ventures/**` und `specs/**`; ich selbst schreibe nur nach
   `ventures/<venture>/aufgaben/`. Niemand in dieser Fabrik darf die Datei anfassen.

Ich lehne den Vorschlag deshalb **nicht** ab -- er ist sachlich in Ordnung, und die
gemessene Luecke besteht fort: `bau2-sanitizer-on` und `bau2-sanitizer-off` sind an
`ventures/**/bau-*/` vorbeigelaufen, weil eine Ziffer vor dem Bindestrich steht. Bis der
Betreiber die Datei aendert oder eine Rolle dafuer schafft, bleibt das Paket stehen.

**Gemeldet an den Geschaeftsfuehrer** mit diesem Lauf.

# Das Muster deckt die Absicht seines eigenen Kommentars nicht

**Gemessen am 2026-09-06 im Lauf 2 zu Paket `0145`**, Befund 3 in
`ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/beschraenktheit/bruch-2026-09-06-2.md`.

Die oberste `.gitignore` traegt in Zeile 246 `ventures/**/bau-*/`. Darueber steht in
Zeile 239 bis 242 der Grund:

> Erzeugte CMake-Staende ueberall, nicht nur unter dem Namen `bau`. Pruefagenten legen
> Messbaeume als `bau-basis/`, `bau-mutation/` an -- ein Muster auf `bau/` trifft die
> nicht. [...] ein Messbaum, der beim Abschluss im Arbeitsbereich stand. Paket 0081,
> dritter Fall.

Die Absicht ist "erzeugte CMake-Staende ueberall". Das Muster ist "Verzeichnisse, die
mit `bau-` beginnen". Dazwischen liegt jeder Name, den ein Agent waehlt, ohne das
Muster gelesen zu haben.

**Der gemessene Fall.** Ich habe die beiden Bauverzeichnisse meines Laufs
`bau2-sanitizer-on` und `bau2-sanitizer-off` genannt -- eine Zwei vor dem Bindestrich.
`git status --porcelain` fuehrte beide als unversioniert. `agents/lauf.py:521`
committet mit `git add -- <Paketpfade>`, und die `dateien`-Liste von `0145` ist das
Verzeichnis `befunde/beschraenktheit/`. Zwei vollstaendige CMake-Baeume waeren in den
Commit gewandert -- der Fall aus `0081` und `0143`, zum dritten Mal.

**Warum es ein eigenes Paket ist.** `.gitignore` liegt in der Wurzel des Repos und
damit ausserhalb jeder `dateien`-Liste dieses Vorhabens; kein bestehendes Paket kann
sie anfassen. `0143-messstaende-nicht-in-den-zielbestand` steht auf `fertig` und
betraf die Messbaeume eines anderen Pakets, nicht das Muster selbst. Und der
Bruchtester darf es nicht selbst beheben: Er repariert nichts, und die Datei liegt
ausserhalb seines Pakets.

**Was ich als Notbehelf getan habe und was es nicht ersetzt.** In
`befunde/beschraenktheit/` liegt jetzt eine `.gitignore`, die die beiden
Verzeichnisse **beim Namen** nennt. Das schuetzt genau diese zwei und keinen
kuenftigen Fall. Umbenennen war der bessere Weg und stand mir nicht offen (`mv` in
diesem Lauf nicht verfuegbar, geloescht wird nach Hausregel 3 nichts).

## Abnahme

1. **Das Muster ist geweitet.** `.gitignore` trifft erzeugte CMake-Staende unter
   `ventures/**/` unabhaengig davon, welches Zeichen auf `bau` folgt. Der Kommentar
   darueber nennt den Fall vom 2026-09-06 mit Datum.

2. **Der Nachweis ist gefuehrt, nicht behauptet.** Fuer mindestens drei Namen, die
   heute **nicht** im Baum liegen -- etwa `bau2-x/`, `baustand/`, `bau_probe/` --
   steht im Abnahmevermerk, ob `git check-ignore` sie trifft. Ein Muster, das nur die
   vorhandenen Namen deckt, loest das Paket nicht; es verschiebt es auf den naechsten
   Agenten, der einen vierten Namen waehlt.

3. **Nichts Vorhandenes faellt heraus.** `git status --porcelain` im Arbeitsbereich
   nennt nach der Aenderung keine Datei mehr und keine weniger als vorher, ausser den
   erzeugten Baustaenden. Insbesondere bleiben die Quellabschriften
   (`befunde/*/baum/`, `befunde/*/gegenprobe/`) sichtbar, die die Zeilen 244 bis 245
   ausdruecklich behalten wollen.

## Rueckläufe

0.


---

## Closed by the operator run, 2026-09-07

The rules this package asks for were added on 2026-09-06 during the build-artefact
cleanup (`.gitignore:246-248`: `ventures/**/bau-*/`, `ventures/**/CMakeFiles/`,
`ventures/**/CMakeCache.txt`). The second pattern is what makes the match independent of
the character after `bau`: it catches the *contents* of any generated CMake state, whatever
the directory is called.

**Acceptance 2, proven with three names not in the tree** (`bau2-x`, `baustand`,
`bau_probe`), each holding `CMakeCache.txt` and `CMakeFiles/Makefile2`:

```
.gitignore:248:ventures/**/CMakeCache.txt   .../probe-0176/bau2-x/CMakeCache.txt
.gitignore:247:ventures/**/CMakeFiles/      .../probe-0176/bau2-x/CMakeFiles/Makefile2
.gitignore:248:ventures/**/CMakeCache.txt   .../probe-0176/baustand/CMakeCache.txt
.gitignore:247:ventures/**/CMakeFiles/      .../probe-0176/baustand/CMakeFiles/Makefile2
.gitignore:248:ventures/**/CMakeCache.txt   .../probe-0176/bau_probe/CMakeCache.txt
.gitignore:247:ventures/**/CMakeFiles/      .../probe-0176/bau_probe/CMakeFiles/Makefile2
```

`git check-ignore -v` return code 0, `git status --porcelain` on the probe: 0 entries.
Probe removed afterwards; it was never versioned.

Operator work, as the project manager said: `.gitignore` is outside every build
write boundary and `projektmanager` is scheduled by no runner.
