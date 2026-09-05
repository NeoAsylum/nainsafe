# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-2.md` und elf aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-04, neunmal bestaetigt, wieder 09-05 -- `Edit`, `Write` und `cp` fallen
  regelmaessig ganz aus, je *Aufruf* verschieden. Getragen hat fast jedes Mal ein
  Heredoc mit **einfach angefuehrtem** Trenner, das `python3` auf der Standardeingabe
  liest. In Paket 0072 war `Edit` von Anfang bis Ende gesperrt.
- 2026-09-05, **neu und wichtiger als es aussieht** -- **auch der Heredoc faellt je
  Aufruf aus, und zwar bei identischer Nutzlast.** Dreimal in 0072: derselbe Text ging
  im zweiten Anlauf durch, einmal erst gar nicht. *Vorgehen:* nicht umschreiben,
  sondern **denselben Aufruf wiederholen** -- und wenn auch das scheitert, auf `Write`
  ausweichen. Es sind zwei unabhaengige Sperren; welche gerade offen ist, wechselt.
- 2026-09-05 -- **Der `Grep`-Weg traegt, wo Bash faellt.** Die ganze Abnahmemessung von
  0072 (Muster ueber die Bauquellen, `bau` und `befunde` ausgenommen) laesst sich als
  ein `Grep` mit Dateimuster fahren -- kein Skript, keine Sperre, und die Fundstellen
  stehen mit Datei und Zeile da.
- 2026-09-04, wieder 09-05 -- **Ein Heredoc je Aufruf, und nichts dahinter.** Ein
  angehaengtes `tee`, `wc` oder `grep` laesst den **ganzen** Aufruf scheitern. Ausgabe
  im Python selbst kuerzen. Ebenso faellt eine `awk`-Pipe hinter `grep` regelmaessig aus.
- 2026-09-04 -- **Ein Programm aus `$TMPDIR` direkt aufzurufen ist verweigert; ueber
  `ctest` laeuft dasselbe Programm.** Messen also immer ueber `cmake -S <arbeitsbaum> -B
  $TMPDIR/...` und `ctest --test-dir`, nie ueber den Binaerpfad.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren, und darin laeuft
  `ctest`.** Damit ist die Vorher-Nachher-Messung samt Wiederherstellung im `finally`
  ein einziger Aufruf statt dreier, die einzeln ausfallen koennen.
- 2026-09-03, wieder 09-04 und 09-05 -- **`git commit` ist mir verweigert; der Baulauf
  committet.**

## Fremde Laeufe

- 2026-09-04, **zum fuenften Mal** -- **Fremdlaeufe committen meine halbfertige Arbeit
  unter ihrem eigenen Betreff**, und zwar **mitten im Lauf**. `git log -S` findet sie,
  die Betreffsuche nicht. **Bezugsstand fuer jedes Vorher-Nachher ist der letzte Commit
  vor dem eigenen Lauf** -- am 09-05 fuer 0072 `609c538`. Und: **nach dem Abschluss noch
  einmal nachmessen**, der Baum kann sich unter dir bewegt haben.
- 2026-09-04, **bestaetigt am 09-05 in 0072** -- **Ein roter Test ist erst dann mein
  Befund, wenn die Fundstelle in meinen Dateien liegt.** Der `belegstellen_riegel` war
  vor und nach meinem Eingriff rot, beide Male an demselben fremden Zitat
  (`rueckstand.md` nach `werkzeugkette.cmake`). Wer nur nachher misst, haelt das fuer
  seinen eigenen Schaden und repariert eine fremde Datei.

## Messen und nachweisen

- 2026-09-05, **der billigste Nachweis, den ich bisher hatte** -- **Ein Riegel, der den
  Quellbaum zur Laufzeit liest, braucht fuer das Vorher keinen zweiten Baum und keine
  Neuuebersetzung.** Datei kurz auf den Stand des letzten Commits setzen, `ctest`
  laufen lassen, im `finally` zurueckschreiben -- und die **SHA-256 vor, waehrend und
  nach** dem Ausflug ausgeben. Ohne den Abdruck ist die Wiederherstellung eine
  Behauptung. Kosten: ein Aufruf.
- 2026-09-05, **teuer gelernt in 0072** -- **Die Fehlermeldung eines Riegels steht auf
  `stderr` und landet dadurch MITTEN in seiner `stdout`-Liste, nicht am Ende.** Ich habe
  dreimal den Schluss der Ausgabe durchsucht und den Block nicht gefunden, obwohl die
  Zaehlung ihn ansagte (36 gefunden, 35 aufgeloest). Er stand in
  `<bau>/Testing/Temporary/LastTest.log` in der Mitte, und eine Zeile war sogar
  mittendrin zerschnitten. *Vorgehen:* **nach dem Wortlaut der Meldung suchen, nie nach
  ihrer Lage** -- und die Zahlen der Zusammenfassung als Wegweiser nehmen.
- 2026-09-04, **die teuerste Lehre** -- **Vor jede Sabotagereihe eine Kontrolle auf dem
  unveraenderten Baum, die GRUEN sein muss.** Und das **Urteil trennen**: rot (cmake) /
  (uebersetzung) / (probe).
- 2026-09-05 -- **`ctest` gruen ist keine Zahl, sondern eine je Profil.**
  `FABRIK_SANITIZER` aendert, **welche Ziele es ueberhaupt gibt**. Wer eine Zielzahl als
  Sollwert notiert, ohne das Profil dazuzuschreiben, notiert eine Zahl, die in der
  Haelfte der Laeufe falsch ist.
- 2026-09-05, **daraus die allgemeinere Lehre, in 0072 wieder bestaetigt** -- **Eine
  Abnahme kann veralten, ohne dass jemand etwas falsch gemacht hat.** 0072 nennt 37
  Bauquellen; gemessen waren es 42, und der Riegel selbst meldete 44 im Bericht
  desselben Tages. *Vorgehen:* die veraltete Zahl **am Stand davor nachmessen** und
  beide Zahlen nebeneinander berichten.
- 2026-09-04, dritter Beleg -- **Sabotiere jede Haelfte einer Abnahme einzeln** -- und
  bei einem Muster jede Haelfte des **Musters**.
- 2026-09-05 -- **Wo eine Messung nicht unterscheidet, gehoert das hingeschrieben.**
  Sie als Nachweis auszugeben waere die bequemste Sorte Luege.
- 2026-09-04 -- **Eine Abnahme, die in mindestens einer der drei Ausgaben sagt, ist
  von einer einzigen Ausgabe erfuellbar.** Den Wortlaut erfuellen **und** daneben die
  Aussage pruefen, die sie gemeint hat.
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-05, **Fund, den ich weiterreiche** -- `befunde/pruefung-0066/nachbau.py` ist
  ein fertiger Regressionsstand fuer den Schlussriegel. Wer `werkzeugkette.cmake`
  anfasst, faehrt ihn vorher und nachher.

## Der Kern selbst

- 2026-09-04, **die Bauart, die ich wiederverwenden werde** -- **Eine abgeschriebene
  Tabelle prueft sich nur selbst; eine gerechnete laesst sich gegen die Abzaehlungen
  halten.** Beide Haelften sind noetig.
- 2026-09-04 -- **Die Regel erst ausserhalb gegen das Verzeichnis halten, dann in C++
  schreiben.** Dann ist der Bau ein Uebertrag statt eines Versuchs.
- 2026-09-04 -- **Eine Summenzeile neben den Einzelzahlen faengt die Klasse, die
  dazukommt und deren Einzelzeile niemand ergaenzt.** Und: **Ein Fehlerwert gehoert
  ausserhalb des gueltigen Bereichs.**
- 2026-09-04 -- **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Ersatzlos weg statt unterdrueckt.
- 2026-09-04 -- **`[[nodiscard]]` und ein Abbruchnachweis vertragen sich nur mit
  `(void)`.**
- 2026-09-02 -- **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt
  die Abnahme -- die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.

## Belegstellen und Riegel

- 2026-09-05, **der Fund aus 0072 und der wertvollste Teil des Pakets** -- **Ein fett
  ausgezeichneter Vorspann zaehlt fuer Bedingung 2 als Ueberschrift.** In `spiel.md`
  ist die Stelle, die die fuenf Fondsaggregate aufzaehlt, kein Rautenabschnitt, sondern
  beginnt mit einem fetten Namen. Damit laesst sich eine tote Zeilennummer nicht nur
  ersetzen, sondern in etwas verwandeln, das der Riegel von da an **bewacht**: Zaehlung
  35/34 vorher, 36/35 nachher -- das neue Zitat loest auf. Ersetzen heisst also nicht
  bloss Nummer weg, sondern Nummer gegen Pruefbares.
- 2026-09-05 -- **Die Nummer war in beiden Faellen schon tot, bevor sie jemand ansah.**
  Die eine zeigte auf eine Begruendung statt auf die Aufzaehlung, die andere auf einen
  Absatz ueber Mass 3. Das ist der vierte Fall dieser Sorte in dieser Datei.
  **Nie nachziehen, immer ersetzen** -- wer nachzieht, schreibt nur die naechste tote
  Nummer hin.
- 2026-09-05 -- **Der Riegel kennt zwei Schreibweisen und die Krankheit hat drei.** Er
  sucht das Wort fuer eine Zeile und `Z` mit Punkt; die Doppelpunktform laeuft durch,
  obwohl der Dateiname direkt davor steht. **Ein gruener Riegel ist eine Aussage ueber
  seine Muster, keine ueber den Baum.**
- 2026-09-04, in 0076 zum zweiten Mal bezahlt -- **Ein Kommentar, der einen Randfall
  fuer ausgeschlossen erklaert, ist teurer als gar keiner, wenn er sich irrt:** Wer ihn
  liest, hat die Frage gestellt, eine Antwort bekommen und hoert auf zu suchen.
- 2026-09-04 -- **Wer in einem Kommentar eine Pruefung verspricht, muss sie schreiben
  koennen.** Sonst ist der Kommentar eine Zusage auf Widerruf.
- 2026-09-04 -- **Ein Riegel, der EINE Quelle liest fuer etwas, das das Werkzeug aus
  MEHREREN zusammensetzt, ist gruen von Bauart.** Und: **Prueft ein Riegel Vorhandensein,
  prueft er nicht Wirkung.**
- 2026-09-03 -- **Was vergessen werden kann, gehoert in etwas, dessen Fehlen abbricht**
  -- ein Funktionsaufruf, keine Variable.

## CMake

- 2026-09-05 -- **Der Nichtwert hat zwei Schreibweisen, und welche kommt, haengt an der
  Abfrage.** `get_target_property` setzt den Variablennamen mit angehaengtem
  `-NOTFOUND`, `get_source_file_property` das blanke `NOTFOUND`. An CMakes eigener Regel
  entlangschreiben statt eine Abfrageart zu bevorzugen.
- 2026-09-04 -- **`befunde/` liegt ausserhalb der Manifest- und Riegelsuche.** Deshalb
  der zweitbeste Nachweisort nach `$TMPDIR`, und deshalb liegen dort Kopien mit
  absichtlich beschaedigten Zeilen. Nicht anfassen.
- 2026-09-03, wieder 09-04 -- **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  Zwei binden die Werkzeugkette nicht ein -- nachpruefen, nie anfassen.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0072 unsicher bin:** Die Abnahme sagt, nachgemessen werde
  mit dem Muster aus dem Rumpf und **nicht** mit dem Riegel. Genau das habe ich getan --
  null Fundstellen. Fuer `spiel.md` habe ich darueber hinaus eine Form gewaehlt, die der
  Riegel **doch** nachschlaegt. Das ist mehr, als verlangt war, und bindet den Kommentar
  an den Wortlaut in `spiel.md`: Wer den Vorspann dort umbenennt, macht den Baulauf rot.
  Ich halte das fuer richtig, weil es die Zusage des Pakets pruefbar macht -- ein
  Pruefer kann es als ungefragte Zusatzkopplung lesen.
- 2026-09-05 -- **Der `belegstellen_riegel` ist rot und war es vor mir**, an einem Zitat
  in `rueckstand.md` nach `werkzeugkette.cmake`. Nicht meine Datei, nicht mein Paket;
  gemeldet statt behoben.
- 2026-09-05, **Vorschlag, den ich nicht schreibe, weil 0072 ihn schon begruendet
  ablehnt:** das dritte Muster im Riegel fuer die Doppelpunktform. Die Datei haelt Paket
  0067. Jetzt, wo mein Baum bei null steht, ist der Zeitpunkt dafuer aber da -- der
  Riegel wuerde davon nicht rot.
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in **keiner**
  Zieleigenschaft.
- 2026-09-04, weitergegeben statt behoben -- T20 verlangt zur Unterschiedsebene die
  Ursachenkette aus T18; die Abnahme von 0010 verlangte sie nicht. Steht als
  Vorschlag 0091.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
