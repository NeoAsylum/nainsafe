---
id: 0041-baulauf-bauverzeichnisse-ueberspringen
rolle: geschaeftsfuehrer
status: fertig
haengt_an: []
dateien: [agents/baulauf.py]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# `baulauf.py` sucht Manifeste in Verzeichnissen, die git nicht sieht

## ZURÜCK AN DEN BETREIBER am 2026-09-03 — Projektmanager

> **`vorschlag` → `blockiert`, nicht `abgelehnt` und nicht `offen`.** Der Befund ist
> richtig und im Wortlaut nachgemessen; abgelehnt wäre falsch. `offen` wäre eine Lüge im
> Statusfeld, denn kein Lauf dieser Fabrik würde ihn je ziehen.
>
> **Der Grund, gemessen statt vermutet.** `baulauf.py:59-61` führt die Rollen, die ein
> Paket ziehen können:
>
> ```python
> BAUROLLEN = {"datenbauer", "kernbauer", "oberflaechenbauer", "auslieferer",
>              "testentwickler", "architekt", "spielentwerfer"}
> PRUEFROLLEN = {"selbstspieler", "rueckvergleicher", "bruchtester"}
> ```
>
> `geschaeftsfuehrer` steht in keiner der beiden. Er läuft in Stufe 5 als fester
> Aufruf (`baulauf.py:374`), ohne Paket und ohne `--gegenstand` auf eine Aufgabe. Ein
> Paket mit dieser Rolle ist damit weder Bau noch Prüfung; `startbereit()` und
> `reviewbereit()` übergehen es beide, still.
>
> **Und es gibt auch keine andere Rolle, in die es passt.** Ich habe die Frage in beide
> Richtungen geprüft: Keine der 43 Aufgaben nennt `agents/` in ihrer `dateien`-Liste, und
> keine Rollendatei unter `agents/rollen/` hat `Edit(agents/**)`. Der `verbesserer` kommt
> `agents/` am nächsten und darf ausdrücklich **nichts selbst ändern** — er schreibt
> einen Vorschlag nach `ops/verbesserung.md`. Das ist Absicht und keine Lücke: Der Runner
> ist Werkzeug der Fabrik, nicht Quelltext des Spiels.
>
> **Damit ist das hier eine Betreiberaufgabe**, und sie steht als solche im
> `rueckstand.md` und geht über den Bericht des Geschäftsführers weiter. Sie kostet eine
> Zeile plus einen Neustart des Tageslaufs — die Auflage aus `lehren.md` (2026-09-02)
> steht oben im Vorschlag und gilt.
>
> **Der Vorschlagende hat die Rollenfrage selbst gesehen** und geschrieben, der
> Projektmanager möge es „lieber weiterreichen als einplanen". Genau das tue ich. Das ist
> der siebte Fall der Familie *eine Regel an einer Stelle, die der Ablauf nicht erreicht*
> — und der erste, in dem die Stelle eine **Rolle** ist statt einer Zeile.
>
> **Was der Betreiber entscheiden kann, wenn ihm die Weitergabe zu langsam ist:** Ein
> Paket, das `agents/` ändern darf, braucht eine Rolle in `BAUROLLEN` und eine
> Rollendatei mit `Edit(agents/**)`. Das ist eine Regeländerung und gehört nicht mir —
> ich melde nur, dass es ohne sie keinen Weg gibt.

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

## Nachtrag 2026-09-03, abends — Projektmanager: der Schaden ist nicht mehr null

**Der Satz „Der akute Schaden ist heute null" oben ist seit heute falsch, und zwar
gemessen.** Der Übersetzungsbericht des Tages,
`befunde/uebersetzung-2026-09-03.md`, trägt im Frontmatter `manifeste: 4`. Versioniert sind
aber nur drei, die für den Bau zählen:

```
git ls-files …/0016-…/ | grep CMakeLists
  …/CMakeLists.txt
  …/befunde/pruefung-0029/CMakeLists.txt      ← liegt unter befunde/, Z. 116 filtert sie
  …/kern/CMakeLists.txt
  …/pruefstand/CMakeLists.txt
```

Das vierte Manifest des Berichts ist `pruefstand/bau/pruefung-0019/CMakeLists.txt`, und es
steht im Bericht namentlich: Zeile 163 nennt seinen Bauordner, Zeile 185 sein Testprojekt.
Es ist in keinem Commit. **Damit hängt der offizielle Übersetzungsbericht der Fabrik heute
an einer Datei, die git nicht kennt** — genau die stille Kopplung, die dieser Vorschlag
beschreibt, nur nicht mehr als Möglichkeit.

**Der Status bleibt `blockiert`, und die Prüfung dazu ist in diesem Lauf wiederholt
worden.** `agents/baulauf.py:59-61` führt `geschaeftsfuehrer` weiterhin weder in
`BAUROLLEN` noch in `PRUEFROLLEN`; keine Rollendatei unter `agents/rollen/` trägt
`Edit(agents/**)`. Es gibt also nach wie vor keinen Weg über ein Gewerk, und `offen` wäre
weiter eine Lüge im Statusfeld. **Ich gebe die Sache damit zum zweiten Mal an den Betreiber
zurück**, jetzt mit einem eingetretenen statt einem erwarteten Schaden — sie geht über den
Bericht des Geschäftsführers und steht im Rückstand.

**Zweite Fundstelle derselben Familie, heute dazugekommen und harmlos:** Der `test-pruefer`
hat in `142e956` einen ganzen Bauordner nach `befunde/pruefung-0029/` versioniert
(`CMakeLists.txt` plus `bau/`). Der Filter aus Zeile 116 nimmt `befunde` aus, also zählt sie
nicht mit — der Bericht bleibt bei vier statt fünf. Löschen darf ich nicht (Hausregel 3),
und ich melde es deshalb nur: Der Ordner ist Erzeugnis, nicht Quelle, und gehört nach
derselben Begründung aufgeräumt wie `pruefstand/bau/pruefung-0019/`.


---

## Ausgefuehrt vom Betreiber-Lauf, 2026-09-05

Der Projektmanager hatte richtig entschieden: , nicht , weil kein
Lauf dieser Fabrik das Paket je gezogen haette --  steht in keiner der
beiden Rollenmengen, und keine Rollendatei darf  schreiben. Es ist damit
Betreiberarbeit, und sie ist hiermit getan.

Uebernommen ist der Vorschlag im Wortlaut, einschliesslich  und .

**Der Befund war groesser als angenommen.** Das Paket rechnete mit einem Phantom-Manifest
( statt ). Gemessen am 2026-09-05: **13 vorher, 4 nachher -- neun
Phantome.** Das Vorhaben hatte unter `bau/kp0010/quelle/` und `bau/kp0027r3/quelle/` zwei
vollstaendige Schattenkopien seiner selbst; der offizielle Uebersetzungsbericht hat sie
gebaut und ihre Tests unter eigenem Namen gefuehrt.

Die vier verbleibenden sind die versionierten: Arbeitsbereich, `kern`, `pruefstand`,
`werkzeuge/belegstellen`.

**Bedingung 3 ist ohne Zutun erfuellt:** Es laeuft gerade kein Tageslauf -- die
Wochenbremse hat ihn um 03:00 angehalten. Der naechste Cron-Aufruf importiert die neue
Fassung.

**Nicht getan:** die Aufraeumarbeit am Ende des Pakets. `pruefstand/bau/pruefung-0019/`
bleibt liegen. Mit dem erweiterten Filter ist es harmlos, und Hausregel 3 spricht
dagegen, etwas zu loeschen, das ein Pruefergebnis belegt -- auch wenn es unversioniert
ist. Wer es doch raeumen will, tut es als eigene Entscheidung.
