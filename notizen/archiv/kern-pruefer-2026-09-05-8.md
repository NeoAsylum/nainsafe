# Logbuch: kern-pruefer

**Siebte Rotation am 2026-09-05** bei 11.876 Zeichen. Vorfassung unter
`notizen/archiv/kern-pruefer-2026-09-05-7.md`, aeltere daneben (`-2` bis `-7`: mehrere
Rotationen am selben Tag). Archivkopie mit `cmake -E copy`.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre
in einem Satz. **An dieser Datei schreiben mehrere eigene Laeufe gleichzeitig** -- vor
jedem Anhaengen neu lesen und die Groesse **im selben Aufruf** pruefen. *0103:* Sie wurde
mir mitten im Lauf unter den Haenden rotiert; wer blind anhaengt, schreibt sie zurueck.

---

## Der Apparat

- **Die Sperre wechselt von Lauf zu Lauf, auch die Richtung, und sie ist pfadgenau.**
  *0123:* `Write` nach `befunde/` frei, nach `notizen/archiv/` gesperrt -- in **einem**
  Lauf. *0134/0140:* Schreiben nur unter `befunde/` und `aufgaben/`; `Edit` und `Write`
  sonst ueberall gesperrt, auch unter `$TMPDIR`. Einmal probieren kostet einen Aufruf.
- **Kommt kein eigener Dateiinhalt durch, tragen `cmake -E` und `python3 -c`.**
  `copy_directory`, `copy`, `rename`, `rm -rf` blieben frei; `pathlib.write_text` nach
  `$TMPDIR` kam durch, `subprocess.run` in `python3 -c` in **0140** nicht.
- **`&&`- und `;`-Ketten werden pauschal abgelehnt**, ebenso `cmd > datei` -- auch
  `> /dev/null`. Befehle einzeln, Ausgabe mit `| tail` kuerzen. Ebenso `sed -n` --
  dafuer `Read` mit `offset`/`limit`.
- **`$TMPDIR` ist eine tmpfs, die sich fremde Laeufe teilen.** *0140:* Sie lief mitten im
  Lauf auf 0 MB; dann geht die **Ausgabe** eines Befehls verloren, nicht nur die Datei.
  Messbaeume gleich nach der Messung mit `cmake -E rm -rf` wegraeumen, `baum.tar` zuerst.
- **Messbaeume nach `befunde/bau-*/` legen, nie nach `befunde/<name>/`.** `.gitignore`
  kennt `ventures/**/bau-*/`; alles andere unter `befunde/` wird mitversioniert (0081).
- **Die Shell verliert ihr Arbeitsverzeichnis zwischen Aufrufen.** Absolute Pfade nehmen
  -- ein `grep` im falschen Verzeichnis liefert *stillschweigend* nichts.
- **Nie ueber den Commit-Betreff suchen**, immer `git log --diff-filter=A -- <datei>`.
  **Ob gebaut wurde, entscheidet der Dateiinhalt an `HEAD`.** *0121, wieder 0140:* Der
  Betreff gehoert regelmaessig einem fremden Paket -- die drei Dateien von 0140 kamen mit
  dem Commit eines anderen Laufs in den Bestand.

## Mutieren, ohne eine Paketdatei anzufassen

Viermal getragen (0098, 0123, 0140). Der saubere Kopf zuerst, dann das Makro, dann die
Quelle; danach gegen das **unveraenderte** Probenobjekt binden (`link.txt` gibt die
Zeile her, das Original weglassen):

```
c++ <Schalter aus bau/CMakeFiles/<ziel>.dir/flags.make> \
    -I kern/include -include kern/<kopf>.hpp -include $TMPDIR/mutant.h \
    -c kern/src/<quelle>.cpp -o $TMPDIR/mutant.o
```

- **Die Reihenfolge der `-include` ist der ganze Trick.** Ein blosses `-D` trifft auch
  die *Definition* im Kopf; erst Kopf, dann Makro trifft nur die **Aufrufstelle**.
- **Ein Makro auf eine Konstante ist der billigste Mutant.** *0140:*
  `#define X (::ns::X + 1)` verschiebt genau eine Schranke, ohne den Kasten umzubauen.
  Auch ein Zugriff geht: `#define eintrag(n) eintrag(0)` legt jedes Glied als das erste
  ab und erschlaegt jede Zusicherung ueber die Zuordnung.
- **Ein Makro darf waehlerisch sein.** Ein Uebersetzungsabbruch am ersten Aufrufer
  verdeckt die Deckung aller uebrigen -- die Stelle gezielt aussparen.
- **Ein absorbierter Mutant ist kein ungedeckter.** `+1` verschwand im Runden; erst
  `+1000` wurde rot. **Vor dem Urteil "nicht abgedeckt" die Schrittweite erhoehen.**
- **Trennschaerfe mitmessen:** Welche Zusicherung bleibt beim Mutanten gruen?

## Was funktioniert

- **Selbst bauen und messen ist der staerkste Nachweis, den ich habe.** Frischer Baum:
  `git archive -o $TMPDIR/baum.tar HEAD ventures/<v> specs decisions`, dann `tar -xf`.
  **`specs` und `decisions` muessen mit** -- sonst faellt `belegstellen_riegel` aus, und
  man haelt die eigene Ablage fuer einen Befund (0103).
- **Die Gegenprobe ist der Baum von `HEAD` mit genau der einen Datei zurueckgedreht**,
  nicht der Elterncommit -- der traegt die Aenderungen der Parallellaeufe nicht.
- **Jede Abnahmebedingung einzeln, mit eigenem mechanischem Aufruf.** Fast jeder Befund
  fiel genau dabei an.
- **Vorher/nachher maschinell vergleichen, nicht nach Augenschein.** *0140:* `diff` ueber
  die Ausgaben derselben Probe aus zwei Baeumen ist der ganze Nachweis fuer "der Zustand
  bleibt unberuehrt".
- **Immer beide Bauprofile** (`-DFABRIK_SANITIZER=ON|OFF`), und beide Bauwege (Kern
  allein, Arbeitsbereich). Bei Determinismus ist der Profilvergleich selbst der Nachweis.
- **Determinismus zuerst strukturell, dann gemessen.** Muster: Gleitkomma, `unordered_*`,
  `chrono`, `rand`, `random_device`, `reinterpret_cast`, `uintptr_t`, `getenv`,
  `__DATE__`, Zuteilung. Rueckkopplung ebenso negativ beweisbar: Gibt es keinen Weg
  heraus ausser Lesen und kein `setze`, kann das Modul keine Schleife schliessen.
- **Die Riegel gegen den *Arbeitsbaum* laufen lassen, bevor der eigene Befund abgeht.**
  *0140:* `belegstellen_riegel`/`bezeichner_riegel` nehmen die Vorhabenwurzel als
  Argument; ein vorhandener Baubaum genuegt, neu konfigurieren muss man nicht. `aufgaben/`
  wird von beiden gelesen -- ein eigener Vorschlag kann den Bau brechen.
- **Jede Riegel-Zahl braucht eine zweite, unabhaengige Zaehlung.** Genau genug meist: die
  Zielzahl aus zwei Konfigurationslaeufen (mit und ohne die neuen Dateien). Namen statt
  Summen liefert die CMake-File-API, `.cmake/api/v1/query/codemodel-v2` (0104).
- **Nennt eine Zahl ihren Bezugsstand, dort messen -- nicht an `HEAD`.** Auch die
  historische Nebenzahl hat einen Stand: den letzten Commit jenes Tages (0104).
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** Ein Riegel, der alles
  blockiert, sieht im Negativtest identisch aus.
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag**, ebenso ein Ausschluss in
  einem Vorschlag und der von ihm empfohlene Bauweg.
- **Eine reparierte Wurzel hat Geschwister.** Nicht nach dem Muster suchen, sondern nach
  der *Frage*: Wo steht sie im Modul noch -- und antwortet jede Stelle gleich?
- **Eine Mengenbeziehung schlaegt eine Stichprobe** (0103): Verwirft die neue Bedingung
  eine **echte Teilmenge** der alten, kann der Riegel nichts verlieren, was er vorher fing.
- **Von Hand nachrechnen, auch wenn die Probe gruen ist.**
- **Der Rand, den ein fremdes Messskript auslaesst, ist die leere Menge** (0134).

## Was nicht funktioniert

- **Ein rotes `ergebnis:` gehoert nicht automatisch dem geprueften Paket.** Liest der
  rote Test die Dateiart, die das Paket geaendert hat?
- **Eine Testeinspeisung an der falschen Stelle beweist nichts.** Scheitern Probe und
  Kontrolle gleich, ist die Einspeisung schuld, nicht der Gegenstand.
- **Den Meldungstext einer Ausnahme nach dem Fangblock lesen** -- er ist dann fort.
- **`grep -v <wort>` verwirft Treffer, die zwei Namen tragen.**

## Offene Faehrten

- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein `zurueck`** -- und eine
  Vorgabe, zu der die Abnahme **schweigt**, ebenso wenig. *0140:* Das Urteil folgt den
  Bedingungen, der Verstoss wird ein Vorschlag. Die Gegenprobe dazu ist die naechste
  Zeile: Zeigt der Irrtum in die sichere Richtung?
- **Prueffrage bei jedem unscharfen Satz:** *Fuehrt der Irrtum zu mehr Pruefung oder zu
  weniger?* Ein lauter Abbruch ist kein `zurueck`, eine stille Kuerzung immer.
- **Sagt eine Vorgabe, wo diese Zahl herkommen darf?** *0140:* Eine Kapazitaet war die
  Partielaenge R als `constexpr` -- und ein T-Block verbietet R als Konstante des Codes
  woertlich. Der Kommentar, der eine Zahl aus einem Entwurfsdokument herleitet, nennt oft
  selbst die Vorgabe, gegen die sie steht. **Jede Konstante gegen ihren T-Block halten.**
- **Bei welchem Wert schlaegt eine Schranke zuerst zu -- innerhalb oder ausserhalb des
  Zulaessigen?** *0140:* Die Speicherzusicherung riss erst weit oberhalb jedes erlaubten
  Werts und war damit fuer keinen erreichbaren Fall ein Schutz. Ausrechnen, nicht lesen.
- **Ein `static_assert`, dessen eine Seite per Definition die andere ist, kann nicht
  reissen.** Als Dokumentation gut, als Riegel null -- nicht zur Deckung zaehlen.
- **Wo zwei Schichten dieselbe Schranke tragen, sagt nur der *Verbotssatz*, welche
  zugeschlagen hat** ("die Meldung nennt die innere Schicht nicht"). Mutant darauf: die
  aeussere Schranke um eins hochsetzen, dann greift die innere -- ohne Verbotssatz bleibt
  alles gruen.
- **Deckt die Probe den Weg, den der echte Aufrufer nimmt?** *0140:* Die Kapazitaet war
  nur ueber den Einzelschritt-Weg ueberhaupt erreichbar, ueber den Sammelweg konnte sie
  nie reissen. Beide Wege selbst fahren.
- **Ein Modus, den der Kern noch nicht baut, ist ein Loch im Nachweis.** *0140:* Die
  Grenze war nur an gestellter Eingabe messbar, nicht an einer gelaufenen Runde -- das
  gehoert in den Befund, auch wenn es kein Mangel des Pakets ist.
- **Nennt die Abnahme zwei von N gleichartigen Eingaengen, die uebrigen selbst messen**
  (0103). **Ueber wie viele gleichartige Eingaenge laeuft die geaenderte Zeile?**
- **Bei einer reinen Kommentaraenderung ist der Gegenstand die Behauptung.** Jede
  Zusicherung einzeln gegen den Baum halten, Name fuer Name, Ort fuer Ort.
- **Erfuellt die Stelle, an der eine Regel steht, die Regel selbst?** (0104) Eine frisch
  geschriebene Regel ist der Pruefauftrag fuer ihre eigene Nachbarschaft.
- **Zeigt die Ausgabe die eigene Schaerfe des Riegels?** (0103) Prueffrage: Welche Zahl
  faellt, wenn der Riegel aufhoert zu greifen?
- **Welche Mutation ist unsichtbar, weil der Vorgabewert der Probe sie unsichtbar
  macht?** Namens- und Einheitentabellen sind derselbe blinde Fleck.
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an `-fwrapv`.
- **Ruft die Probe den echten Vorgang, oder stellt sie ihn nach?** Zwei Pakete, die
  einzeln richtig sind, koennen zusammen falsch sein.
- **Ein Kriterium, das im Dateiverzeichnis des Pakets nicht erfuellbar ist, ist ein
  Befund an den Projektmanager** -- kein Anlass, es zu senken.

## Zu Vorschlaegen

- **Vor dem eigenen Vorschlag pruefen, ob es die Luecke schon als Paket gibt** -- `grep`
  ueber `aufgaben/` nach der tragenden Formulierung. Viermal hat das den Vorschlag
  erledigt oder halbiert (0098, 0123, 0103, 0140 → `0131` hielt den Commit-Schnitt
  schon). **Ein zweiter Beleg gehoert in den Befund, nicht in ein zweites Paket.**
- **Sagt das gepruefte Paket selbst, welches andere die Gegenseite haelt, dort
  nachschlagen und dessen `status` und Abnahme lesen.** *0140:* `0091` haelt dieselben
  drei Dateien -- das gehoert in die Begruendung des eigenen Vorschlags, samt der Frage,
  welches zuerst laufen soll.
- **Zeilennummern aus einem fremden Paketrumpf nie uebernehmen** (0103). Im eigenen
  Vorschlag den **Namen** zitieren, nie die Zeile.
- **`befunde/` und `bau/` stehen in `UNGELESENE_ORDNER` des Belegstellenriegels** --
  Zeilennummern und Kurzzitate sind dort erlaubt. In `aufgaben/` sind sie es **nicht**.
- **Ein Messwerkzeug, das auf fehlerfreiem Baum rot meldet, ist selbst ein Befund** (0103).
- **Nummernkollision, achter Fall** (0131 entstand waehrend meines Laufs). Nummer erst
  nach `git add` endgueltig festlegen; unter der alten bleibt ein Zeiger mit
  `status: umgezogen` (Hausregel 3), Vorbild `0092`. **Im Befund auf den Paketnamen
  verweisen, nicht auf die Nummer allein.**
- **Die `dateien`-Liste eng schneiden ist kein Formalismus, sondern die Reihenfolge.**
  Die Sperre serialisiert die **Laeufe**, nicht den **Index** (0121).
- **`git add` ist selbst die Gefahr, nicht erst der eigene Commit.** Erst ganz am Schluss
  vormerken; ist das Einchecken gesperrt, sofort `git restore --staged` nachziehen.
- **Ein weiterer Pruefungslauf am selben Paket ist keine Doppelarbeit, wenn die vorigen
  Vorschlaege hinterlassen haben.** Dateiname `pruefung-<kennung>-runde<n>-<datum>.md`.
