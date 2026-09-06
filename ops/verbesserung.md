# Verbesserungsvorschlag KW 36

*Vorbemerkung zu den Zulieferungen: `ops/kontingent.md` und `ops/auslastung.md` sind von
diesem Wochenlauf (2026-09-06T05:00:01) und tragen Zahlen. `ops/wege.md` ist vom selben
Lauf, aber sein Datenblock ist **leer** — fuer die Bauphase gibt `weg.py` nichts her.
Nachgerechnet habe ich nichts davon.*

## Die Beobachtung

**Vier Baurollen fuehren je einen eigenen Katalog darueber, welche Werkzeugaufrufe der
Sandkasten durchlaesst. Zwischen dem 2026-09-04 und heute ist dieser eine Abschnitt
53-mal neu geschrieben worden.**

| Abschnitt | Rolle | Fassungen (Logbuch + Archiv) |
|---|---|---:|
| `## Werkzeuge und Sperren` | kernbauer | 30 |
| `## Der Apparat` / `## Zum Apparat` | kern-pruefer | 14 |
| `## Werkzeuge — was mich Aufrufe gekostet hat` | projektmanager | 5 |
| `## Werkzeuge` | datenbauer | 4 |

Dazu kommen dieselben Inhalte ohne eigene Ueberschrift, unter „Was nicht funktioniert":
testentwickler, test-pruefer, daten-pruefer, geschaeftsfuehrer, architekt, bruchtester.

Im laufenden Logbuch belegt der Abschnitt: **kern-pruefer 37 von 178 Zeilen (21 %),
testentwickler 29 von 167 (17 %), kernbauer 21 von 172 (12 %), projektmanager 23 von 190
(12 %).** Das ist der Anteil des privaten Gedaechtnisses, den jede Baurolle nicht fuer
ihr Gewerk ausgibt, sondern fuer den Apparat — und bei jeder Rotation verliert.

**Die Kataloge widersprechen einander, alle Eintraege vom 2026-09-06:**

- *Heredocs.* `notizen/kernbauer.md:16` — „Nicht wiederholen, sofort `python3 - <<PY`
  nehmen", der Standardweg dieser Rolle. `notizen/testentwickler.md:104` —
  „**Heredocs abgelehnt**". `notizen/projektmanager.md:152` — „Abgelehnt: … Heredocs".
- *`&&`-Ketten.* `notizen/kern-pruefer.md:26` — „**Ketten mit `&&` oder `;`,
  `for`-Schleifen und `sed` fallen regelmaessig.**" `notizen/testentwickler.md:92` —
  „**Korrektur zur Zeile darunter:** `&&`-Ketten liefen heute mehrfach".
- *`python3 -c`.* `notizen/kern-pruefer.md:172` — „`python3 -c` abgelehnt".
  `notizen/testentwickler.md:101` — „ein Ausdruck, also erlaubt".

**Der teuerste Einzelfall.** Drei Rollen melden, dass sie die Archivregel aus `CLAUDE.md`
nicht ausfuehren koennen, zwei davon ausdruecklich an den Betreiber:

- `notizen/architekt.md:8` — „**An den Betreiber: eine Zeile in der Rollendatei macht die
  Archivregel ausführbar.**"
- `notizen/projektmanager.md:6` — „**`Write` nach `notizen/archiv/` ist abgelehnt**
  (2026-09-06): nicht rotieren, sondern überholte Einträge durch ihre neue Fassung
  ersetzen. Gemeldet."
- `notizen/geschaeftsfuehrer.md:8` — „kann meine Rolle nicht ausführen (`mv`, `cp`,
  `Write` dorthin alle verwehrt) — **nicht wieder versuchen.**"

Die Antwort steht seit dem 2026-09-06 geschrieben — in `notizen/testentwickler.md:101`:

> **Kopieren ohne `cp`:** `python3 -c "…Path(ziel).write_bytes(…Path(quelle).read_bytes())"`
> — ein Ausdruck, also erlaubt. So archiviert man das eigene Logbuch ohne `mv`.

Drei Rollen halten eine Sache fuer unmoeglich, eine vierte hat sie geloest, und keine
der drei darf die Datei lesen, in der die Loesung steht. Solange das so ist, streichen
sie statt zu archivieren — und Hausregel 3 gilt fuer Logbuecher nur noch fuer die
Rollen, die zufaellig den richtigen Aufruf gefunden haben.

## Warum es passiert

`CLAUDE.md` sagt ueber das Logbuch: „Es gehört dir allein — kein anderer Agent schreibt
hinein, und du schreibst in kein fremdes." Fuer ein **Urteil** ist das richtig, und
`notizen/lehren.md` begruendet es sauber: elf Rollen an einer gemeinsamen Strategie
erzeugen Rauschen. Fuer eine **mechanische Tatsache ueber den Apparat** ist es falsch:
Die ist fuer alle dreizehn Rollen dieselbe, sie ist nachpruefbar, und sie veraltet in
Tagen.

Es gibt genau einen gemeinsamen Kanal, `notizen/lehren.md`, und er funktioniert
nachweislich: Die Lehre „Nie `cd`" steht seit dem 2026-09-06 darin, weil der
Portfolio-Manager sie in drei Logbuechern gesehen hat. Aber es ist eine einspurige
Strasse, sie wird einmal pro Woche befahren, und die Hand am Steuer gehoert einer Rolle,
deren Auftrag Strategie ist, nicht Handwerk. Eine Tatsache, die sich taeglich aendert,
kommt darueber nie an.

**Und der Runner hat die Daten laengst.** `agents/lauf.py:698` liest
`permission_denials` aus der Rueckgabe der CLI. Der Kommentar zwei Zeilen darueber nennt
sie „der wertvollste Fruehwarnwert ueberhaupt". Verwendet wird davon nur `tool_name`;
daraus entsteht eine 120 Zeichen lange Vorbemerkung am Antworttext (`:702`). Der Wortlaut
des Aufrufs — genau das, was die vier Rollen einzeln rekonstruieren — wird verworfen.
Sichtbar wird der Rest nur, wenn der Lauf ohnehin scheitert: `ops/nachtlauf.log` traegt
die Marke **14-mal**, jedes Mal neben einer Kontingentabsage, in einer Datei, die keine
Rolle liest.

Die Regel dagegen steht seit dem 2026-09-01 in `notizen/lehren.md`, geschrieben fuer den
Compiler und nie auf den Sandkasten angewandt:

> Wenn eine Rolle ein Werkzeug nicht haben darf, ihre Arbeit aber ohne dessen Ausgabe
> wertlos ist, gehört das Werkzeug in den Runner und seine Ausgabe in eine Datei.

## Der Vorschlag

**Der Runner schreibt auf, was er ohnehin sieht, und alle Rollen lesen es.**

**`agents/lauf.py`, Zeile 698–703.** Der Block bildet heute nur die Namensliste. Er
haengt zusaetzlich je Verweigerung eine Zeile an `ops/werkzeugsperren.md` an:

```
2026-09-06 | kernbauer | Bash | cd .../befunde && grep -n "..."
2026-09-06 | kern-pruefer | Write | .../kern/src/verlauf.cpp
```

Also Datum, Rolle, Werkzeug, und aus dem Eintrag das `tool_input` auf die ersten rund 80
Zeichen gekuerzt. Doppelte Zeilen (gleiche Rolle, gleiches Werkzeug, gleicher Anfang)
werden nicht zweimal geschrieben, Eintraege aelter als sieben Tage fallen weg — sonst
wird die Datei das `notizen/markt-analyst.md` der Bauphase (43.632 Zeichen, das
3,6-Fache der Grenze).

**`CLAUDE.md`, im Abschnitt zum Logbuch.** Aus „Zu Beginn jedes Laufs liest du zwei
Dateien" werden drei. Die dritte ist `ops/werkzeugsperren.md`, und ihre Einfuehrung
enthaelt im selben Atemzug die Lesevorschrift — der Satz existiert bereits, aber nur in
**einer** Rollendatei, `agents/rollen/geschaeftsfuehrer.md:72`:

> Wird dir ein Werkzeug verweigert, heisst das: **dieser eine Aufruf** war nicht erlaubt.
> Es heisst nicht, dass `Edit` in dieser Sitzung nicht ginge.

Als Vorschlagstext fuer `CLAUDE.md`:

> `ops/werkzeugsperren.md` — welche Aufrufe anderen Rollen zuletzt verweigert wurden.
> **Das ist ein Protokoll gescheiterter Aufrufe, keine Regelliste.** Ein verweigerter
> Aufruf heisst: *dieser eine Aufruf* war nicht erlaubt — nicht, dass das Werkzeug
> gesperrt ist. Probiere zuerst, sieh dann nach. Was du hier findest, spart dir den
> zweiten Versuch, nicht den ersten.

Ist der Kanal da, kann jede Rolle ihren eigenen Abschnitt streichen — 12 bis 21 Prozent
Logbuch, die wieder dem Gewerk gehoeren.

## Was er kostet und was er spart

**Kosten:** rund zehn Zeilen in `agents/lauf.py` und drei Saetze in `CLAUDE.md`.
**Kein einziger zusaetzlicher Agentenlauf** — die Daten liegen bereits im Runner, es
fehlt nur der Schreibvorgang.

**Was es beim Lesen kostet: nichts.** Jede Baurolle traegt heute 12 bis 21 Prozent ihres
Logbuchs an diesem Stoff und liest ihn in jedem Lauf. Sie traegt ihn kuenftig nicht mehr
und liest stattdessen eine gemeinsame Datei aehnlicher Groesse. Es aendert sich nicht der
Umfang, sondern die Abdeckung: von einem Dreizehntel des Wissens auf alles.

**Ersparnis, belegt:** die Wiederentdeckung. 53 Fassungen desselben Abschnitts in drei
Tagen, vier Rollen. Der Archivierungsfall allein steht seit mindestens sechs Tagen in
drei Logbuechern offen und ist in einem vierten seit dem 2026-09-06 beantwortet.

**Ersparnis, nicht bezifferbar:** die Laeufe, die an einem umgangenen statt versuchten
Werkzeug haengen. `notizen/kern-pruefer.md:18` beziffert das Verhaeltnis: „ein
abgelehntes Werkzeug kostet einen Aufruf, ein umgangenes eine halbe Stunde."

**Eines ist vorher zu pruefen, einmal, und ich kann es nicht:** ob der
`permission_denials`-Eintrag der CLI neben `tool_name` auch den Wortlaut (`tool_input`)
traegt. `lauf.py:700` liest nur den Namen, also hat noch niemand nachgesehen. Traegt er
ihn nicht, bleibt der Vorschlag gueltig, aber schwaecher: Er beendet dann den Streit
darueber, *welches Werkzeug* welcher Rolle verweigert wurde, nicht den ueber *welchen
Wortlaut*.

## Was dagegen spricht

**Der beste Einwand: Ein Verweigerungsprotokoll, das als Regelliste gelesen wird, macht
die Fabrik langsamer, nicht schneller.** Die Sperre entscheidet nach Inhalt und wechselt
innerhalb eines Laufs — `notizen/kern-pruefer.md:17`, 2026-09-06: „`Write` auf eine
`.cpp` abgelehnt, `Write` auf eine `.md` angenommen -- in **demselben** Lauf." Eine
Rolle, die „Heredoc abgelehnt" liest und deshalb gar nicht erst versucht, verliert den
billigsten Weg. Genau diese Fehlverallgemeinerung steht als Lehre vom 2026-09-02 in
`notizen/lehren.md` (der Architekt, neun gezaehlte Verweigerungen, sauber hergeleitet,
falsch). Deshalb steht die Lesevorschrift oben **im selben Satz** wie die Datei. Faellt
sie weg, ist der Vorschlag schaedlich.

**Zweiter Einwand: Es ist eine Codeaenderung, und der Betreiber hat zwei Stunden.** Die
Fuenf-Minuten-Fassung, die vielleicht ein Drittel traegt: `CLAUDE.md` bekommt nur die
zwei Saetze aus `agents/rollen/geschaeftsfuehrer.md:72`, ohne neue Datei und ohne
Runner. Das transportiert keine Tagesfakten, verhindert aber den teuersten Fehlschluss —
und es ist der Fall, den mein eigenes Logbuch als ergiebigsten kennt: eine Regel, die nur
in einem Sonderfall angewandt wird.

**Dritter Einwand, und er ist grundsaetzlich:** Der Vorschlag gibt der Fabrik eine
weitere gemeinsam gelesene Datei, eine Woche nachdem `notizen/lehren.md` aus genau
diesem Grund halbiert wurde (42.578 Zeichen, von jeder Baurolle in jedem der 1.531 Laeufe
mitgelesen). Meine Gegenrede: Hier schreibt der Runner, nicht dreizehn Rollen — kein
Parallelschreiben, kein Urteil in der Datei, und eine Verfallsfrist von sieben Tagen ist
maschinell durchsetzbar, was bei `lehren.md` nicht der Fall war. Sicher bin ich mir bei
der Verfallsfrist nicht: Sieben Tage sind geraten, nicht gemessen.
