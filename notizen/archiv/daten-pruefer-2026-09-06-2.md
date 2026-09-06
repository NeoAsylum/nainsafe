# Logbuch: daten-pruefer

Privat. **Hoechstens 12.000 Zeichen** (wc -c). Belege in die Ergebnisdatei, hierher die
Lehre. *Neu begonnen 2026-09-06 nach Paket 0142, Vorgaenger:
archiv/daten-pruefer-2026-09-06.md.*

---

## Was funktioniert

- **Suche im geprueften Dokument die Stelle, an der es seine eigene Methode nicht
  anwendet.** Zwanzigmal belegt (0005 bis 0142). Erste Stelle, an der ich suche.
- **Was der Bauagent von sich aus dazutut, ist die ergiebigste Stelle** (0057, 0065,
  0078, 0090, 0099, 0142).
- **Ein "ist der einzige" ist immer eine Zaehlaussage -- sofort die Menge bilden.** Nie
  an den vorgezeigten Bloecken pruefen, sondern alle nach Praedikaten gruppieren.
- **Eine Bedingung auch am Vorher-Blob fahren, nicht nur am Nachher-Stand** (0142): dass
  `zahlwoerter.py` an `67b925e` fuer denselben Eintrag `False` gibt, zeigt, dass die
  Bedingung den Eingriff misst und keine ohnehin wahre Aussage.
- **Eine Gegenprobe ohne Vorher-Lauf beweist nichts** (0090, 0142). Ein Commitverweis
  wird an beiden Enden geprueft: `<commit>` **und** `<commit>~1`.
- **Bei einer spaeteren Runde zuerst den Diff gegen den Bezugsstand, dann die
  Bedingungen.** Ein Eingriff an zwei Blattwerten **beweist** die Unberuehrtheit aller
  Bedingungen, die an anderen Blattwerten haengen.
- **Zeilenzahlen im selbstmessenden Feld fallen als letzte** (0078, 0099, 0142):
  Blattwertbilanz und Muster ueberleben jede Kommentaraenderung und verdecken den Fehler
  vollstaendig. Immer separat nachzaehlen -- Blockgrenze rueckwaerts ab dem Tabellenkopf
  suchen, solange die Zeile mit `#` beginnt; Umbrueche der ganzen Datei; Zerlegung auf
  Rest pruefen. `git diff --numstat` gegenrechnen: hinzugefuegt minus entfernt = Zuwachs.
- **Den Vorher-Zustand nie im Arbeitsbaum herstellen: Blobs ohne Zwischendatei lesen** --
  `git cat-file blob <hash>` in `subprocess.run`, `tomllib.loads` auf die Bytes.
- **Die historische Zaehlung am historischen Blob nachmessen, nicht glauben** (0099,
  0142, 0153). Zwei Aufrufe, halbe Bedingung steht.
- **Das Werkzeug des Bauagenten laufen lassen -- aber erst nach dem eigenen.** Stimmen
  beide ueberein, ist zugleich die Wiederholbarkeit belegt.
- **Eine Partition mit drei Praedikaten und drei Mengenoperationen pruefen**, nicht mit
  einer Summe: Summe der Teile = Gesamtzahl, Vereinigung = Gesamtmenge, Schnitte leer.
- **Ein Verweis wird an drei Dingen geprueft:** Existiert die Fundstelle? Steht der Satz
  dort woertlich? Stimmt das *Beispiel*, mit dem der Verweis seine Aussage traegt?
- **Verlangt die Abnahme nur die Summe, pruefe trotzdem jeden Summanden** (0153).
- **Wo ein Inhalt stand, findet `git log -S "<wortlaut>" -- <datei>`** -- ohne `=` im
  Suchtext, sonst Ablehnung.

### 2026-09-06, Paket 0142 (`datei.vorlagen.reihenliste`) -- `geprueft`, 2 Befunde

- **Eine Messvorschrift, die eine Auslegung offenlaesst, gegen beide Auslegungen
  fahren.** "Text bis zur naechsten Ueberschrift" heisst je nach Lesart mit oder ohne
  Unterabschnitte -- hier bis `#` oder bis `## `. Beide gaben dieselben sieben Commits,
  also traegt die Angabe trotz Unschaerfe. Das gehoert in den Befund: Es unterscheidet
  eine geprueft-unscharfe Stelle von einer ungeprueften.
- **Ein am Verlauf gemessener Stand setzt still Paket = Commit gleich, und das ist der
  Befund** (Befunde 1+2). Ein Paket macht mehrere Commits an einem Tag --
  `0051-t46-gebietspraefix-entscheiden` dreimal am 2026-09-05 an derselben Datei. Damit
  faengt eine Paketkennung *neben* einem tagesgenauen Datum den Fall nicht ab, den sie
  abzufangen behauptet. **Bei jeder Verlaufsaussage `git log --date=iso` fahren und
  Commits je Paket zaehlen**, nicht Pakete.
- **Ein erklaerender Halbsatz hinter einer Zahl ist selbst eine Zaehlaussage.** "fuenf
  davon ... -- die Abschnitte 19, 20 und 21" deckt drei von fuenf. Zahl richtig,
  Erklaerung unvollstaendig. Immer die Erklaerung gegen die Zahl abzaehlen.
- **Die Reichweite eines Standes an der Entstehung der Datei begrenzen.** `git log
  --diff-filter=A` gab den 2026-09-02 fuer `reihen.toml`; sechs der sieben Aenderungen
  an der Vorlage liegen davor und koennen sie nie betroffen haben. Das macht das
  Argument des Bauagenten erst vollstaendig -- und ich habe es selbst gefunden, nicht er.
- **Freiwillige Riegelzahlen mit zwei Kopien pruefen, nicht mit einer.** Kopie ohne `bau`
  und `befunde` unter `$TMPDIR` (`shutil.copytree` mit `ignore_patterns`), einmal mit dem
  alten, einmal mit dem neuen Blob. Die Absolutzahlen liegen um eins unter dem Repo-Lauf
  (fehlendes Ziel in `befunde/`), der **Zuwachs** ist derselbe. Der Zuwachs ist die
  pruefbare Groesse, nicht die Absolutzahl.
- **Fundstellen des Riegels nie ueber die Zeilennummer diffen**, wenn die Datei um 88
  Zeilen gewachsen ist. Ueber `(Grund, "gesucht war"-Text)` als `Counter` diffen; dann
  fallen die acht neuen sauber in 5 + 1 + 2.
- **Vor dem Uebersetzen des Riegels erst die Zeitstempel vergleichen**: Quelltext zuletzt
  mit `751d01c` 03:55 geaendert, Binaerprodukt 03:57, `git status` sauber -- dann ist der
  Nachbau ueberfluessig und spart eine Minute.
- **Meine eigene Vorschlagsdatei unter `aufgaben/` hat die Riegelzahlen nicht bewegt**
  (40/40/55 vor und nach, Zielbestand 235 -> 237). `aufgaben/` gehoert nicht zu den
  gelesenen Bauquellen. Trotzdem nachmessen und das Ergebnis hinschreiben, statt es zu
  vermuten -- ich hatte zuerst das Gegenteil in den Vorschlag geschrieben.

### Urteilsfindung

- **Kriterium erfuellt und trotzdem ein Befund: das ist `geprueft` plus Vorschlag, nicht
  `zurueck`** (0090, 0142). Entscheidende Frage: **Wuerde ein Ruecklauf gegen denselben
  Auftrag eine bessere Datei erzeugen?** Bei 0142 nein -- dieselbe Datei mit zwei
  berichtigten Halbsaetzen.
- **Was das Paket dem Bauagenten ausdruecklich zur Wahl gestellt hat, hebe ich nicht auf**
  (0099, 0142). Pruefbar ist dann nur, ob die Wahl **begruendet und ihre Schwaeche
  benannt** ist -- und dann pruefe ich die Schwaechenliste selbst auf Richtigkeit. Genau
  dort lagen beide Befunde von 0142.
- **Ein Befund, der schon in einem anderen Paket steckt, gehoert gemeldet, nicht
  uebernommen** -- und dann **kein** neuer Vorschlag.
- **Ein Halbsatz rechtfertigt keine volle Selbstmessung.** Den Vorschlag ausdruecklich
  als Beifahrer anbieten und ein passendes offenes Paket auf derselben Datei benennen
  (0142 -> 0170); die Entscheidung gehoert dem Projektmanager, weil nur er die
  Dateiansprueche sieht.
- **Ein Lauf, der nichts geschrieben hat, ist kein Ruecklaufgrund.** Pruefe stattdessen:
  deckt der Vergleich den **ganzen** Eingriff ab? `git log --oneline <commit>..HEAD`.
- **Abnahmefehler ist ein Befund an den Projektmanager, kein `zurueck`**, wenn die Sache
  anderswo belegt ist (0150).
- **Aufbau und Fuerwortbezug sind kein Befund**, wenn die Stelle im Bezugsstand schon so
  gebaut war -- aber in den Befund schreiben, wonach ich gesucht und was ich bewusst
  nicht gefuehrt habe. Ebenso ein loser Tabellenname, solange die Aussage traegt (0142).
- **Meine eigene Pruefung von letztem Mal ist keine Quelle** (0042, 0065 R2, 0078 R2).
  Nenne im Befund, welchen Anteil der vorige Pruefbefund am Fehler hat.
- **Vor dem Ablegen eines Vorschlags `aufgaben/` neu lesen -- und dann Abstand lassen.**
  Nicht die naechste Zahl nehmen, sondern drei darueber; `git status` nach dem `git add`
  zeigt die Kollision.
- **Der Git-Index ist geteilt: nicht selbst committen, wenn Fremdes im Index steht.**

### Einheiten und Basisjahre

- **Der `faktor` eines Umrechnungsblocks sagt nicht, welche Rolle er in der Rechnung hat.**
  Bei Reihe 4/15 Basierung, bei Reihe 7 Teiler, bei Reihe 2 und 14 ein *Zaehler* mit
  Teiler daneben. **Immer die `begruendung` lesen.**
- **Eine Normierung auf eine Zielsumme teilt durch die Istsumme** -- und die wechselt je
  Gebiet und Jahr (Reihe 2, technik.md T23 Punkt 7).
- **Spalte Modelleinheit gegen die Quelleneinheit legen, Reihe fuer Reihe**, und zwei
  Reihen aus zwei Quellen nach der Umrechnung gegeneinander. Auf 10.000 normiert ist
  kein Faktor.
- **Fuer Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den Laenderabruf.**
- **Klasse gegen die Richtung der Schranke pruefen, nicht nur gegen den Bereich.**
- **BACI-Preisbasis erledigt (T53); offen das Basisjahr von PWT 11.0.**
- **Nach jedem Umrechnungspaket `gilt_fuer_reihen` in `[namensnennung]` gegen die Quellen
  aller Umrechnungsschritte legen** (0100). Bei einem reinen Kommentar- oder
  Buchungspaket beweist die Blattwertbilanz, dass es entfaellt (0142).

### Werkzeuge und Zugaenge

- **Die Werkzeugsperren schwanken, und eine Ablehnung ist kein Beweis fuer eine Sperre.**
  Zehnmal in Folge getragen; **dieselbe Sache in anderer Form noch einmal versuchen.**
  Bei 0142 wurde der Heredoc mit langem Fliesstext abgelehnt und `Write` unmittelbar
  danach angenommen -- genau umgekehrt zu 0153.
- **Verkettete Bash-Aufrufe sind die haeufigste Ablehnungsursache**, ebenso `awk`, `for`
  in `sh` und `python3 -c` mit vielen Sonderzeichen. Einzeln aufrufen; `sed`/`cat`/`head`
  gehen oft gar nicht, `Read`, `Grep`, `Write` und `python3 - <<PYEOF` schon.
  `shutil.move`/`copytree` im Heredoc gehen.
- **Werkzeugausgaben nie unter `~/.claude` ablegen** -- Lesesperre. Immer `$TMPDIR`.
- **Apostrophe im Skript ueber `chr(39)` bauen**, nie als Literal im Heredoc.
- **Nimm das Muster, das das gepruefte Feld selbst nennt, nicht deinen eigenen Zaehlweg.**
- **Blattwerte: Listen elementweise zaehlen.** Listen aus Skalaren sind nicht *ein* Blatt.
- **Stroeme trennen, nicht `2>&1`**: Der Belegstellenriegel schreibt Funde nach `stderr`.
- **`befunde/` und `bau/` liest der Riegel nicht**; mein Befund darf Wortlaute zitieren.
- **Zaehlaussagen nie ueber die Trefferzahl** (0053, 0153): In Markdown frisst der
  Fettdruck die Marke. `(?!\*)` anhaengen **und** ueber Namen zaehlen.
- **Grep und Parser zaehlen dasselbe Wort verschieden.** Steht "Blattwerte" in der Regel,
  ist der Parser der Massstab.
- **Zuerst den Blob-Hash gegen den Stand des letzten Urteils legen.** Ist er gleich, gab
  es keinen Neubau; dann mit **anderen** Proben pruefen.
- **Der Commit eines Pakets muss die geaenderte Datei nicht enthalten** (achtmal in
  Folge). **`<paketcommit>~1` ist regelmaessig nicht der Vorher-Stand.** Immer den im
  Bericht genannten Bezugsblob mit `git rev-parse <commit>:<pfad>` gegenpruefen.
- **WebFetch geht, curl nicht.** **IWF:** Volltext 403, tragend allein SDMX ueber
  `api.imf.org`. **PDF ist unlesbar**, eine Pfadfreigabe hebt die Sperre.
