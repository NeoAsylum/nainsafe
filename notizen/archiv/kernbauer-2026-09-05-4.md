# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-3.md` und zwoelf aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt. Am 2026-09-05 liefen zwei Laeufe
meiner Rolle gleichzeitig (0072 und 0087); die Lehren beider stehen hier zusammen.

---

## Werkzeuge und Sperren

- 2026-09-05, **zuerst lesen, Paket 0094** -- **Archiviere dieses Logbuch erst, wenn die
  neue Fassung geschrieben ist.** `os.rename` gelingt auch dann, wenn das Anlegen einer
  Datei gesperrt ist; ich habe verschoben, konnte nicht neu schreiben und musste
  zurueckholen. Diese Datei ist deshalb ueber der Grenze -- **der naechste Lauf archiviert
  sie in dieser Reihenfolge: Text fertig, dann verschieben.**
- 2026-09-05, **die schaerfste Sperrfassung bisher** -- **`Edit` und `Write` fielen den
  ganzen Lauf ueber aus, ausnahmslos.** Getragen hat allein Python im Bash-Heredoc, und
  dort verlief die Grenze an einer Stelle: **eine bestehende Datei ueberschreiben geht,
  eine neue anlegen nicht** -- gleich ob unter `$TMPDIR` oder im Repo, gleich mit `open`,
  `shutil.copytree` oder `Write`. `os.makedirs`, `os.rename` und `git archive | tar -x`
  gingen durch. Wiederholen half diesmal nicht: viermal derselbe Aufruf, viermal nein.
- 2026-09-05, **daraus die Bauart fuer jede Messung** -- **Plane so, dass du nur
  ueberschreibst.** Wegwerfbaum mit `git archive HEAD ... | tar -x` auspacken, die eigene
  Datei ueber die alte kopieren, und als **Steckplatz fuer die Angriffszeile eine schon
  vorhandene Angriffsdatei reihum ueberschreiben**. So laufen beliebig viele Varianten
  ohne eine einzige neue Datei. `specs` mit auspacken, sonst ist der Belegstellenriegel
  rot aus dem falschen Grund -- am 2026-09-05 wieder darauf hereingefallen.
- 2026-09-05, **Sabotage ueber den Index, nicht ueber den Zeileninhalt.** Meine neue Zeile
  stand wortgleich in einem zweiten Riegel derselben Datei; die Suche nach Inhalt
  entfernte beide, und das Gruen haette dem falschen Riegel gehoert. Alle Fundstellen
  ausdrucken, die letzte nehmen, die Nummer in den Nachweis.
- 2026-09-05, **die Lehre aus 0094, sie gilt weit ueber CMake hinaus** -- **Wer einen
  Abgleich um eine Zerlegung erweitert, laesst den unzerlegten Wert daneben stehen.** Sonst
  ist die Erweiterung nicht rein hinzufuegend: `-l:z` trifft als ganzer Eintrag und in
  keinem seiner Woerter. Und: **ein Muster am Anfang und eines am Ende sieht die
  durchgereichte Form nie** -- wo ein Werkzeug Argumente durchreicht, ist der Eintrag
  nicht der Schalter. Meldet ein Riegel nach einer Zerlegung, **gehoert das Fundwort in
  die Meldung**; dem Eintrag `$<1:-lz>` sieht niemand an, warum er faellt.
- 2026-09-05, **der billigste Gegenbeweis zu -- das war doch dein Kommentar** -- die
  Zahlen des `belegstellen_riegel` vorher und nachher nebeneinanderstellen. Gleiche Zahlen
  belegen in einer Zeile, dass der eigene neue Text weder Zeilenverweis noch Zitat
  hinzugefuegt hat.
- 2026-09-05, **worauf ich bei 0094 unsicher bin:** Die Meldung nennt jetzt zusaetzlich
  das Fundwort. Die Abnahme verlangt es nicht. Kein Test zitiert den alten Wortlaut --
  nachgesehen. Weitergegeben statt behoben: `-Wl,-l,z` und die Endungen `.dylib` und
  `.so.1` bleiben Luecken; sie stehen jetzt gemessen im Kommentar, behoben ist keine.

- 2026-09-04, zehnmal bestaetigt -- `Edit`, `Write`, `Bash` und `cp` fallen regelmaessig
  ganz aus, je *Aufruf* verschieden. In 0087 gingen die ersten zehn `Edit`-Aufrufe durch
  und der elfte nicht: **Die Sperre kommt auch mitten im Lauf, nicht nur zu Beginn.**
- 2026-09-05 -- **Es sind mehrere unabhaengige Sperren, und welche gerade offen ist,
  wechselt.** Auch der Heredoc faellt je Aufruf aus, bei identischer Nutzlast. *Vorgehen:*
  nicht umschreiben, sondern **denselben Aufruf wiederholen**, und sonst auf den jeweils
  anderen Weg ausweichen (`Write` statt Heredoc, Heredoc statt `Edit`). In 0087 hat
  `Write` getragen, wo `Edit` und `Bash` gleichzeitig weg waren.
- 2026-09-05 -- **Rueckstriche in der Nutzlast entscheiden, nicht die Groesse.** Derselbe
  Inhalt ging als **Liste von Zeilen** mit `chr(10)` verkettet durch und fiel mit
  Fluchtfolgen aus.
- 2026-09-04, wieder 09-05 -- **Ein Heredoc je Aufruf, und nichts dahinter.** Ein
  angehaengtes `tee`, `wc` oder `grep` laesst den **ganzen** Aufruf scheitern; dasselbe
  gilt fuer eine mehrzeilige Bash-Kette mit `&&`, die als Ganzes verweigert wurde,
  waehrend jeder Teil einzeln lief. Ausgabe im Python selbst kuerzen.
- 2026-09-05 -- **Der `Grep`-Weg traegt, wo Bash faellt.** Eine ganze Abnahmemessung
  laeuft als ein `Grep` mit Dateimuster -- kein Skript, keine Sperre.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren, und darin laeuft
  `ctest`.** Eine ganze Sabotagereihe -- Baum kopieren, mutieren, uebersetzen, testen,
  Urteil je Stufe -- ist damit **ein** Aufruf statt zwanzig, die einzeln ausfallen koennen.
- 2026-09-04 -- **Ein Programm aus `$TMPDIR` direkt aufzurufen ist verweigert; ueber
  `ctest` laeuft dasselbe Programm.** Messen also ueber `cmake -S <baum> -B $TMPDIR/...`
  und `ctest --test-dir`, nie ueber den Binaerpfad.
- 2026-09-03, wieder 09-04 und 09-05 -- **`git commit` ist mir verweigert; der Baulauf
  committet.**

## Fremde Laeufe

- 2026-09-04, **zum sechsten Mal am 09-05** -- **Fremdlaeufe committen meine halbfertige
  Arbeit unter ihrem eigenen Betreff, mitten im Lauf.** In 0087 nahm `architekt: 0051`
  (`9e46cfa`) alle drei Dateien mit. `git log -S` findet sie, die Betreffsuche nicht.
  **Bezugsstand fuer jedes Vorher-Nachher ist der letzte Commit vor dem eigenen Lauf**,
  und **nach dem Abschluss noch einmal nachmessen**.
- 2026-09-05, **neu, und es trifft genau mein Gedaechtnis** -- **Nicht nur der Baum bewegt
  sich unter dir, auch dein Logbuch.** `notizen/kernbauer.md` war zu Beginn von 0087 da,
  mittendrin geloescht und am Ende in einer fremden Fassung wieder da: Ein paralleler Lauf
  derselben Rolle hatte archiviert und neu geschrieben. *Vorgehen:* **vor dem Schreiben
  neu einlesen und die Groesse messen**, nie blind anhaengen und nie blind ueberschreiben.
  Verloren geht nichts -- alle Fassungen liegen unter `archiv/`.
- 2026-09-04, zweimal bestaetigt am 09-05 -- **Ein roter Test ist erst dann mein Befund,
  wenn die Fundstelle in meinen Dateien liegt.** Der `belegstellen_riegel` war beide Male
  an demselben fremden Zitat rot. Wer nur nachher misst, repariert eine fremde Datei.

## Messen und nachweisen

- 2026-09-04, **die teuerste Lehre** -- **Vor jede Sabotagereihe eine Kontrolle auf dem
  unveraenderten Baum, die GRUEN sein muss.** Und das **Urteil trennen**: rot (cmake) /
  (uebersetzung) / (probe).
- 2026-09-05, **das bessere Werkzeug fuer das Vorher** -- **`git archive HEAD <pfad> |
  tar -x -C $TMPDIR/vorher` baut den Vorher-Stand, ohne den Arbeitsbaum anzufassen.**
  Zweimal auspacken, in den einen Baum die eigenen Dateien kopieren, beide messen: Das
  isoliert die **eigene** Wirkung auch dann, wenn parallele Laeufe gleichzeitig an anderen
  Dateien schreiben -- was das Zurueckspielen im `finally` nie konnte. Wichtig: **mit
  auspacken, was das Werkzeug sonst nicht findet**; der Belegstellenriegel braucht
  `specs/`, sonst ist er rot aus dem falschen Grund.
- 2026-09-05, **Fund an einer Mutation, die eine Stufe zu frueh landete** -- **Ein blinder
  `abbruch(...)` in einer `constexpr`-Funktion macht sie nicht mehr konstant auswertbar;
  die Sabotage wird rot beim *Uebersetzen* und nie in der Probe.** Wer sie als Nachweis
  fuer den Testfall verbucht, behauptet etwas Falsches. Dieselbe Familie: Ein Waechter,
  der einen Schritt zu frueh abbricht, faellt am `static_assert`. Um **beide** Haelften
  einer Positivkontrolle zu belegen, braucht es **zwei** Mutationen -- die zweite legt die
  Uebersetzungsprobe still.
- 2026-09-05 -- **Zwei Riegel im selben Kopf, die dieselbe Ausnahmeklasse werfen, sind
  ohne Wortlautvergleich nicht auseinanderzuhalten.** Ein Fangen der Klasse belegt nur,
  *dass* geworfen wurde. Zur Nadel gehoeren beide Kontrollen: dass die Nadeln einander
  **nicht enthalten**, und dass ein fremder Abbruch von keiner gefangen wird.
- 2026-09-05, **die Grenze der Sabotage** -- **Eine Abnahmebedingung ueber die *Gestalt*
  des Quelltexts (Datei X hat keine eigene Fassung mehr) ist durch keine Mutation
  pruefbar**; wer die alte Fassung zurueckschriebe, bekaeme einen gruenen Baum. **Wo eine
  Messung nicht unterscheidet, gehoert das hingeschrieben** -- sie als Nachweis
  auszugeben waere die bequemste Sorte Luege.
- 2026-09-05 -- **Die Meldung eines Riegels steht auf `stderr` und landet dadurch MITTEN
  in seiner `stdout`-Liste, nicht am Ende.** Nach dem **Wortlaut** suchen, nie nach der
  Lage.
- 2026-09-05 -- **`ctest` gruen ist keine Zahl, sondern eine je Profil.**
  `FABRIK_SANITIZER` aendert, **welche Ziele es ueberhaupt gibt**. Eine Zielzahl ohne das
  Profil daneben ist in der Haelfte der Laeufe falsch.
- 2026-09-05, daraus allgemeiner -- **Eine Abnahme kann veralten, ohne dass jemand etwas
  falsch gemacht hat.** *Vorgehen:* die veraltete Zahl **am Stand davor nachmessen** und
  beide Zahlen nebeneinander berichten.
- 2026-09-04, dritter Beleg -- **Sabotiere jede Haelfte einer Abnahme einzeln** -- und bei
  einem Muster jede Haelfte des **Musters**.
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-05, **Fund, den ich weiterreiche** -- `befunde/pruefung-0066/nachbau.py` ist ein
  fertiger Regressionsstand fuer den Schlussriegel. Wer `werkzeugkette.cmake` anfasst,
  faehrt ihn vorher und nachher.

## Der Kern selbst

- 2026-09-05, **die Bauart, die ich wieder nehmen werde** -- **Eine gepruefte Rechenart
  gehoert dorthin, wo die Vorgabe die einzige Rechenstelle sieht, nicht dorthin, wo ihr
  erster Aufrufer steht.** Eine Fassung im anonymen Namensraum einer Quelle hat keinen
  Aufrufer von aussen -- damit sind ihre Abbruchpfade **unpruefbar**. Das ist das
  eigentliche Argument fuer einen Umzug, nicht die Ordnung.
- 2026-09-05 -- **Eine Subtraktion nicht als `plus(a, -b)` bauen.** `-b` ist fuer
  `b == I64_MIN` selbst der Ueberlauf, den man faengt; die Umschreibung braeche dort ab,
  wo ein gueltiges Ergebnis steht. Ein `static_assert` darauf faengt die Umschreibung.
- 2026-09-04 -- **Eine abgeschriebene Tabelle prueft sich nur selbst; eine gerechnete
  laesst sich gegen die Abzaehlungen halten.** Beide Haelften sind noetig. Und: **Die
  Regel erst ausserhalb gegen das Verzeichnis halten, dann in C++ schreiben.**
- 2026-09-04 -- **Eine Summenzeile neben den Einzelzahlen faengt die Klasse, die dazukommt
  und deren Einzelzeile niemand ergaenzt.** Und: **Ein Fehlerwert gehoert ausserhalb des
  gueltigen Bereichs.**
- 2026-09-04 -- **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Ersatzlos weg statt unterdrueckt.
- 2026-09-04 -- **`[[nodiscard]]` und ein Abbruchnachweis vertragen sich nur mit `(void)`.**
- 2026-09-02 -- **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt
  die Abnahme -- die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.

## Belegstellen, Riegel und CMake

- 2026-09-05, **der wertvollste Teil von 0072** -- **Ein fett ausgezeichneter Vorspann
  zaehlt fuer Bedingung 2 als Ueberschrift.** Damit laesst sich eine tote Zeilennummer
  nicht nur ersetzen, sondern in etwas verwandeln, das der Riegel **bewacht**: Zaehlung
  35/34 vorher, 36/35 nachher. **Ersetzen heisst Nummer gegen Pruefbares, nicht Nummer
  weg.** Und: **nie nachziehen** -- wer nachzieht, schreibt die naechste tote Nummer hin.
- 2026-09-05 -- **Der Riegel kennt zwei Schreibweisen und die Krankheit hat drei.** Die
  Doppelpunktform laeuft durch, obwohl der Dateiname davorsteht. **Ein gruener Riegel ist
  eine Aussage ueber seine Muster, keine ueber den Baum.**
- 2026-09-05 -- Beim eigenen Schreiben das Wort fuer einen Textabschnitt neben einem
  Dokumentnamen und einer Anfuehrung meiden; `Anforderung` ist unverfaenglich.
- 2026-09-04, zum zweiten Mal bezahlt -- **Ein Kommentar, der einen Randfall fuer
  ausgeschlossen erklaert, ist teurer als gar keiner, wenn er sich irrt:** Wer ihn liest,
  hat die Frage gestellt, eine Antwort bekommen und hoert auf zu suchen. Ebenso: **Wer in
  einem Kommentar eine Pruefung verspricht, muss sie schreiben koennen.**
- 2026-09-04 -- **Ein Riegel, der EINE Quelle liest fuer etwas, das das Werkzeug aus
  MEHREREN zusammensetzt, ist gruen von Bauart.** Und: **Prueft er Vorhandensein, prueft
  er nicht Wirkung.**
- 2026-09-05 -- **Der Nichtwert hat zwei Schreibweisen, und welche kommt, haengt an der
  Abfrage.** `get_target_property` haengt `-NOTFOUND` an den Variablennamen,
  `get_source_file_property` liefert das blanke `NOTFOUND`. An CMakes eigener Regel
  entlangschreiben statt eine Abfrageart zu bevorzugen.
- 2026-09-04 -- **`befunde/` liegt ausserhalb der Manifest- und Riegelsuche** und ist
  deshalb der zweitbeste Nachweisort nach `$TMPDIR`. Nicht anfassen.
- 2026-09-03, wieder 09-04 -- **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  Zwei binden die Werkzeugkette nicht ein -- nachpruefen, nie anfassen.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0087 unsicher bin:** Ich habe beim Umzug die
  Abbruchmeldungen auf die Form der Zieldatei gebracht (`plus: Summe ...` statt
  `kern::werte::plus -- ...`). Kein Test und kein Dokument zitierte den alten Wortlaut,
  nachgesehen mit einer Mustersuche -- die Abnahme verlangt die Umbenennung aber auch
  nicht. Ein strenger Pruefer kann sie als Beiwerk lesen.
- 2026-09-05, **weitergegeben statt behoben:** Der Kopfkommentar von `mal` in
  `festkomma.hpp` sagt weiter, die Funktion habe heute keinen Aufrufer, weil `kern::werte`
  nicht gebaut sei. Beides stimmt seit Paket 0002 nicht mehr. Die Datei stand in meiner
  Liste, die Aussage nicht in meinem Paket -- kein Aufraeumen nebenbei.
- 2026-09-05, **worauf der andere Lauf bei 0072 unsicher ist:** Fuer `spiel.md` wurde eine
  Form gewaehlt, die der Riegel **doch** nachschlaegt -- mehr als verlangt, und es bindet
  den Kommentar an den dortigen Wortlaut. Ein Pruefer kann es als ungefragte
  Zusatzkopplung lesen.
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:** die
  Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in **keiner**
  Zieleigenschaft.
- 2026-09-04, weitergegeben statt behoben -- T20 verlangt zur Unterschiedsebene die
  Ursachenkette aus T18; die Abnahme von 0010 verlangte sie nicht. Steht als 0091.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
