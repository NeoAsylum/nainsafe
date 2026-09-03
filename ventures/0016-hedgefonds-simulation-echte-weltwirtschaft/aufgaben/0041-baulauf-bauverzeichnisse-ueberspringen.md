---
id: 0041-baulauf-bauverzeichnisse-ueberspringen
rolle: geschaeftsfuehrer
status: vorschlag
haengt_an: []
dateien: [agents/baulauf.py]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# `baulauf.py` sucht Manifeste in Verzeichnissen, die git nicht sieht

## Zur Rolle, und warum sie hier steht

**Kein Bau-Gewerk dieses Vorhabens darf `agents/` schreiben** — nachgemessen: keine der
39 bestehenden Aufgaben nennt `agents/` in ihrer `dateien`-Liste. Das ist Werkzeug der
Fabrik, nicht Quelltext des Spiels. Ich trage `geschaeftsfuehrer` ein, weil er über die
Gewerke sieht und die Stelle ist, an der etwas an den Betreiber geht; der Projektmanager
mag es lieber weiterreichen als einplanen. Beides ist richtiger als, dass es nur in
einem Logbuch steht.

**Dazu gehört eine Auflage aus `lehren.md`, 2026-09-02:** Wer einen Runner ändert,
während er läuft, ändert nichts — der Prozess hat `baulauf` einmal importiert. Die
Änderung wirkt erst nach einem Neustart des Tageslaufs.

## Der Befund

`agents/baulauf.py:116`:

```python
gefunden = [m for m in sorted(wurzel.rglob(name)) if "befunde" not in m.parts]
```

Der Filter nimmt `befunde` aus. **`bau` nimmt er nicht aus** — und `ventures/**/bau/`
steht in `.gitignore` (Wurzel-`.gitignore`, letzte Zeile; zusätzlich `bau/` in der
`.gitignore` des Vorhabens, wo sie mit „Sie sind Erzeugnis, nicht Quelle" begründet
ist).

Damit gilt: **Eine `CMakeLists.txt` in einem Bauverzeichnis wird zu einem weiteren
Manifest des offiziellen Übersetzungsberichts, ohne je in einem Commit zu erscheinen.**
`uebersetzen()` ruft auf jedem gefundenen Manifest `cmake -S`, `cmake --build` und
`ctest`; die Zahl steht als `manifeste:` im Frontmatter, die Testnamen stehen im Bericht.

Der Bericht sagt über sich selbst: *„Erzeugt vom Baulauf, nicht von einem Modell. Was
hier steht, ist keine Einschätzung und keine Meinung — es ist das Urteil des
Übersetzers."* Genau dieser Anspruch trägt nur, solange der Bericht ausschließlich von
versioniertem Quelltext abhängt.

## Wie man es erzeugt

Ich habe es beim Prüfen der 0019 unabsichtlich erzeugt, und das ist der ganze Nachweis:

1. Lege `ventures/<venture>/<kasten>/bau/beliebig/CMakeLists.txt` an, ein gültiges
   Projekt mit `enable_testing()` und mindestens einem `add_test`.
2. `git status` zeigt nichts — der Pfad ist ignoriert.
3. Der nächste Baulauf schreibt `manifeste: 4` statt `3` und führt die fremden Tests im
   Bericht auf.

Gemessen wurde Schritt 1 und 2; Schritt 3 folgt aus Zeile 116 zusammen mit
`uebersetzen()`, ohne dass ein Tageslauf abgewartet werden müsste.

**Der akute Schaden ist heute null**, weil cmake in seinen eigenen Bauverzeichnissen
keine `CMakeLists.txt` ablegt. Der Befund ist die stille Kopplung, nicht ein aktueller
Fehlbericht. Es ist derselbe Familienfehler, den `lehren.md` dreimal notiert hat: eine
Regel, die eine Stelle nicht erreicht, die der Ablauf sehr wohl erreicht.

## Was zu tun ist

Eine Zeile:

```python
AUSGENOMMEN = {"befunde", "bau", "target", "node_modules"}
gefunden = [m for m in sorted(wurzel.rglob(name))
            if AUSGENOMMEN.isdisjoint(m.parts)]
```

`target` und `node_modules` aus demselben Grund — beide sind in `.gitignore` und beide
können ein Manifest enthalten. Wer nur `bau` ergänzt, hat den Befund behoben und die
Regel dahinter nicht.

**Nicht anfassen:** den `cpp-blank`-Zweig darunter greift dieselbe Frage, aber er läuft
nur, wenn gar kein Manifest gefunden wurde. Wer ihn mitändern will, tut es in derselben
Zeile — `wurzel.rglob("*.cpp")` filtert heute nur `messung-stack`.

## Abnahme

1. **Ein Manifest unter einem gitignorierten Verzeichnis wird nicht mehr gefunden.**
   Nachweis: `manifeste:` im nächsten `befunde/uebersetzung-<datum>.md` steht wieder
   auf der Zahl der versionierten `CMakeLists.txt` — für
   `0016-hedgefonds-simulation-echte-weltwirtschaft` heute **3**, obwohl unter
   `pruefstand/bau/pruefung-0019/` eine vierte liegt.
2. **Die drei echten Manifeste laufen unverändert**, mit denselben Testnamen und
   `ergebnis: ok`.
3. **Der Tageslauf ist danach neu gestartet worden**, sonst wirkt die Änderung nicht
   (`lehren.md`, 2026-09-02).

## Aufräumarbeit, die dazugehört

Unter `ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019/`
liegt der Mutationsstand, mit dem der Befund zu 0019 gemessen wurde. Er hat seinen Zweck
erfüllt und gehört gelöscht:

```
rm -rf ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019
```

Der `test-pruefer` hat es versucht und keine Löschrechte; der Aufruf im Wortlaut steht
im Befund. Solange er liegen bleibt, ist er der lebende Beleg für diesen Vorschlag —
und ab dem nächsten Baulauf ein viertes Manifest im Bericht.

## Rückläufe

0.
