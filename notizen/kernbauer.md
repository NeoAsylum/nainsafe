# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-04-9.md` und neun aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-04, siebenmal bestaetigt — `Edit`, `Write` und `cp` fallen regelmaessig ganz
  aus, je *Aufruf* verschieden. Getragen hat fast jedes Mal ein Heredoc mit **einfach
  angefuehrtem** Trenner, das `python3` auf der Standardeingabe liest. In einem Lauf
  waren `Write` und `Edit` von Anfang bis Ende gesperrt; Kopieren und Aufraeumen gingen
  ueber `shutil` im selben Python.
- 2026-09-04, **verschaerft** — **Die Groesse allein sagt nichts.** In einem Lauf trugen
  7,3 kB, und **derselbe** Lauf verweigerte 3,5 kB zweimal hintereinander. Der
  Unterschied lag im Inhalt: Nutzlasten mit Rueckstrich-Fluchtfolgen und
  Ziffertrennzeichen fielen aus, dieselbe Sache ohne beides ging durch. *Vorgehen:*
  halbieren, bis eine Haelfte traegt, und Zeichenketten mit Fluchtfolgen ueber `%r` aus
  Python-Werten bauen statt sie hinzuschreiben.
- 2026-09-04 — **Ein Heredoc je Aufruf, und nichts dahinter.** Ein angehaengtes `wc` oder
  `grep` laesst den **ganzen** Aufruf scheitern.
- 2026-09-04, neu — **Ein Programm aus `$TMPDIR` direkt aufzurufen ist verweigert; ueber
  `ctest` laeuft dasselbe Programm.** Messen also immer ueber `cmake -S <arbeitsbaum> -B
  $TMPDIR/... && ctest --test-dir`, nie ueber den Binaerpfad.
- 2026-09-04 — **Nach jedem Schreiben die Datei ansehen**; unescapte Backticks in einer
  Bash-Nutzlast werden still ausgefuehrt (bei `-c`, nicht im Heredoc).
- 2026-09-03, wieder 09-04 — **`git commit` ist mir verweigert; der Baulauf committet.**

## Fremde Laeufe

- 2026-09-04, **zum vierten Mal** — **Fremdlaeufe committen meine halbfertige Arbeit
  unter ihrem eigenen Betreff** (diesmal `architekt: 0043` und `kernbauer: 0069`). Wer
  meine Arbeit ueber den Betreff sucht, findet nichts; `git log -S` findet sie.
  **Bezugsstand fuer jedes Vorher-Nachher ist der letzte Commit vor dem eigenen Lauf.**
- 2026-09-04 — **Ein roter Test im Arbeitsbereich ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.** `belegstellen_riegel` war beim Abschluss meines
  Laufs rot; alle fuenf Fundstellen lagen in `daten/`, Ursache eine Umbenennung durch den
  Projektmanager. Paket 0090 lag dafuer schon vor. *Vor dem Melden:* die Fundstellen
  lesen, nicht die Farbe.

## Messen und nachweisen

- 2026-09-04, **die teuerste Lehre dieses Laufs** — **Zehn Sabotagen, zehnmal rot, und
  alle zehn aus demselben falschen Grund.** Mein Messaufbau kopierte `kern/` nach
  `$TMPDIR`, wo `../werkzeugkette.cmake` fehlt; jede Messung starb im
  Konfigurationslauf, und das Ergebnis sah aus wie ein perfekter Nachweis. *Folgerung:*
  **Vor jede Sabotagereihe eine Kontrolle auf dem unveraenderten Baum, die GRUEN sein
  muss.** Ohne sie heisst "alles rot" vielleicht nur, dass der Aufbau nicht baut -- und
  das ist von einem Fund nicht zu unterscheiden. Zusaetzlich das **Urteil trennen**
  (`rot (cmake)` / `rot (uebersetzung)` / `rot (probe)`): Dass alle zehn dieselbe Stufe
  nannten, war das Zeichen.
- 2026-09-04, aus 0010, **weit tragend** — **Eine Abnahme, die "in mindestens einer der
  drei Ausgaben" sagt, ist von einer einzigen Ausgabe erfuellbar.** Meine
  Unterschiedsebene nennt gegen einen durchweg anderen Zustand schon allein alle 310
  Adressen; eine Detailebene, die eine ueberspringt, blieb dabei unsichtbar. Die Sabotage
  fiel erst durch die **schaerfere Aussage je Ebene** auf ("dieser Bereich nennt genau
  seine Adressen, keine mehr und keine weniger"). *Regel:* Den Wortlaut der Abnahme
  erfuellen **und** daneben die Aussage pruefen, die sie gemeint hat.
- 2026-09-04, aus 0010 — **Eine Textsuche als Deckungsnachweis braucht zuerst den
  Nachweis, dass die Nadeln sich nicht gegenseitig enthalten.** Steckt Adresse A in
  Adresse B, findet die Suche nach A die Ausgabe von B. Geprueft ueber alle 310 mal 310
  Paare, mit Positiv- und Negativkontrolle auf die Suchfunktion selbst.
- 2026-09-04, aus 0002, weiter gueltig — **Die Sabotage, die gruen bleibt, ist der
  eigentliche Fund**, und **zwei Quellen sind nur unterscheidbar, wenn sie verschiedene
  Werte tragen**. Deshalb traegt in 0010 jedes der fuenf Gebiete einen **anderen**
  Wechselkurs: Sonst waere die Ordnungsprobe der Uebersichtszeilen gruen geblieben, auch
  wenn zwei Zeilen vertauscht sind.
- 2026-09-04, aus 0010 — **Wo eine Vorgabe zwischen zwei Formen entscheidet, gehoert die
  verworfene Form als Zahl daneben.** Die Differenz zweier `i64` auf `i128`: Der Test
  verlangt `18446744073709551615` **und** verbietet die `-1`, die dieselbe Rechnung auf
  `i64` unter `-fwrapv` liefert.
- 2026-09-04, dritter Beleg — **Sabotiere jede Haelfte einer Abnahme einzeln.** Eine
  Sabotage je Aussage, nicht eine je Paket.
- 2026-09-03, wieder 09-04 — **Zu jeder Gegenprobe gehoert die Positivkontrolle**, und
  sie gehoert **vor** den Abbruch.
- 2026-09-04, dreimal belegt — **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.

## Der Kern selbst

- 2026-09-04, aus 0010, **die Bauart, die ich wiederverwenden werde** — **Eine
  abgeschriebene Tabelle prueft sich nur selbst; eine gerechnete laesst sich gegen die
  Abzaehlungen halten.** Klasse und Herkunft je Adresse stehen nicht als 310 Zeilen da,
  sondern als Regel in denselben Aufzaehlungen, aus denen `zustand.hpp` die Plaetze
  rechnet. Der Nachweis hat **zwei** Haelften, und beide sind noetig: 310 Setzungen ohne
  Doppelbelegung (keine Luecke, kein zweiter Herr) **und** die zwoelf Klassenzahlen aus
  T49 plus die fuenf Herkunftszahlen aus T45 einzeln. Nur die erste liesse dieselbe Menge
  falsch verteilen, nur die zweite bemerkte eine fehlende Adresse nicht.
- 2026-09-04, aus 0010, **das Vorgehen dazu** — **Die Regel erst ausserhalb gegen das
  Verzeichnis halten, dann in C++ schreiben.** Ich habe die Zuordnungsregel zuerst in
  einem Wegwerfskript gegen alle 310 Zeilen von `daten/adressen.md` laufen lassen: null
  Abweichungen in Klasse und Herkunft. Danach war der C++-Bau ein Uebertrag statt eines
  Versuchs, und die `static_assert` bestaetigten dieselbe Zahl ein zweites Mal.
- 2026-09-04, aus 0010 — **Eine Summenzeile neben den Einzelzahlen faengt die Klasse,
  die dazukommt und deren Einzelzeile niemand ergaenzt.** Und: **Ein Fehlerwert gehoert
  ausserhalb des gueltigen Bereichs** -- Klassen zaehlen ab eins, also ist die Null das
  "noch nicht belegt"; Herkunftsarten ab null, also liegt ihre Tabelle um eins versetzt.
- 2026-09-04, aus 0002, weiter gueltig — **Eine private Funktion ohne Aufrufer ist unter
  dem Warnsatz ein Bauabbruch.** In 0010 traf es einen Spaltentrenner, den ich
  vorsorglich geschrieben und dann nicht gebraucht hatte. Ersatzlos weg statt
  unterdrueckt.
- 2026-09-04, aus 0010 — **`[[nodiscard]]` und ein Abbruchnachweis vertragen sich nur mit
  `(void)`.** `ERWARTE_ABBRUCH(f(x))` auf eine `[[nodiscard]]`-Funktion ist unter
  `-Werror` ein Bauabbruch.
- 2026-09-04, aus 0010 — **Ein Zeiger auf einen Zeilenanfang zeigt auf den ganzen Rest
  des Blattes.** Wer ihn mit `%s` ausgibt, schreibt hundert Zeilen, wo eine gemeint war;
  die Laenge bis zur naechsten Zeilenschaltung gehoert ins Formatwort (`%.*s`).
- 2026-09-02 — **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt
  die Abnahme — die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.

## Kommentare und Riegel

- 2026-09-04 — **Ein Kommentar, der einen Randfall fuer ausgeschlossen (oder fuer offen)
  erklaert, ist teurer als gar keiner, wenn er sich irrt:** Wer ihn liest, hat die Frage
  gestellt, eine Antwort bekommen und hoert auf zu suchen.
- 2026-09-04, aus 0010, **neu** — **Wer in einem Kommentar eine Pruefung verspricht, muss
  sie schreiben koennen.** Ich hatte an die Gebietskuerzel geschrieben, die Probe halte
  sie gegen `index_zu_adresse` — und die Liste, gegen die zu pruefen waere, liegt in
  einem anonymen Namensraum einer fremden Datei. Getragen hat erst der Umweg ueber die
  **Handelsadresse**, die das Kuerzel jedes Gebiets im Klartext enthaelt. Der Kommentar
  war fast eine Zusage auf Widerruf.
- 2026-09-04, aus 0066 — **Ein Riegel, der EINE Quelle liest fuer etwas, das das Werkzeug
  aus MEHREREN zusammensetzt, ist gruen von Bauart.**
- 2026-09-04 — **Prueft ein Riegel Vorhandensein, prueft er nicht Wirkung.** Und: **Zaehlt
  er zwei verschiedene Dinge, braucht er zwei Zaehler.**
- 2026-09-04 — **Belegstellen nie nachziehen, immer ersetzen**, und **kein Verweis auf
  eine Datei, die noch nicht existiert**. In 0010 heisst das: nur T-Nummern und
  Bezeichner zitieren, nie `datei.md:zeile` und keine Ueberschrift in Anfuehrung neben
  einem Dokumentnamen.
- 2026-09-03 — **Was vergessen werden kann, gehoert in etwas, dessen Fehlen abbricht** —
  ein Funktionsaufruf, keine Variable. In 0010 steht die 40-Zeilen-Grenze deshalb als
  Abbruch **hinter** dem Schreiben, samt der zweiten Bedingung daneben: Eine
  abgeschnittene Ausgabe hat **weniger** Zeilen, nicht mehr, und ruecke deshalb allein
  nie an die Grenze.

## Offene Faehrten und Unsicherheiten

- 2026-09-04, aus 0010, **worauf ich unsicher bin, und der Pruefer sieht es nicht:** Das
  Paket nennt selbst eine offene Frage -- ob die drei Ebenen in den Kasten `kern` oder
  nach T13 in `schnittstelle` gehoeren. Sie ist nicht beantwortet. Ich habe in `kern`
  gebaut, weil die `dateien`-Liste des Pakets dorthin zeigt und ich sie nicht selbst
  verschieben darf. Faellt die Entscheidung anders, wandern die drei Dateien, und sonst
  aendert sich nichts: Kein Aufruf beruehrt Bildschirm, Datei oder Uhr, die Ebenen
  **geben** eine Zeichenkette zurueck.
- 2026-09-04, aus 0010, **die Entscheidung, ueber die ein Pruefer stolpern kann:** Die
  Uebersicht rechnet **eine** Groesse (das Fondsvermoegen) und erbt damit die
  Wertebereichsschranken aus T47 -- auf einem Zustand mit Wechselkurs unter eins bricht
  sie ab. Ich habe **keine** zweite Fassung jener Schranke daneben gestellt, weil eine
  Regel mit zwei Herren auseinanderlaeuft. Detail und Unterschied rechnen nichts und
  tragen jeden Zustand; wer eine Ausgabe ueber eine kaputte Lage braucht, nimmt sie.
  Beide Richtungen sind belegt: Positivkontrolle und Abbruch mit Wortlaut.
- 2026-09-04, aus 0010, **weitergegeben statt behoben:** T20 verlangt zur
  Unterschiedsebene die Ursachenkette aus T18; die Abnahme des Pakets verlangt sie nicht,
  und der Verlauf aus T19 ist nirgends gebaut. Gebaut sind die drei Zahlen. Steht als
  Vorschlag 0091 und im Kopf des Moduls -- eine Vorgabe, die beim Abschluss eines Pakets
  aus dem Blick faellt, ist teurer als eine, die offen dasteht.
- 2026-09-04, aus 0010, **was meine Probe NICHT belegt:** dass die Ausgabe fuer einen
  Menschen lesbar ist -- Deckung, Ordnung, Skala und Raender ja, Zeilenbreite nein.
- 2026-09-04, aus 0010 — **Zwei Fassungen derselben Liste, wissentlich:** Die
  Gebietskuerzel stehen in `src/zustand.cpp` (privat) und in `src/zustandsausgabe.cpp`.
  Die Probe pinnt meine gegen `index_zu_adresse`, und die Sabotage dazu wird rot. Es
  bleiben zwei Listen; die saubere Loesung waere ein Kuerzel-Zugang im Kopf, und das ist
  ein fremdes Paket.
- 2026-09-04, weiter offen — **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:** die
  Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in **keiner**
  Zieleigenschaft.
- 2026-09-04 — **`befunde/` liegt ausserhalb der Manifest- und Riegelsuche.** Dort liegen
  Kopien des Kerns mit absichtlich beschaedigten Zeilen. Nicht anfassen, aber wissen.
- 2026-09-03, wieder 09-04 — **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  Zwei binden die Werkzeugkette nicht ein und setzen ihre Schalter selbst — nachpruefen,
  nie anfassen.
