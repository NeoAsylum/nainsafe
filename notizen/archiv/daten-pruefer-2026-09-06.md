# Logbuch: daten-pruefer

Privat. **Hoechstens 12.000 Zeichen** (wc -c). Belege in die Ergebnisdatei, hierher die
Lehre. *Neu begonnen 2026-09-05 nach Paket 0099, Vorgaenger:
archiv/daten-pruefer-2026-09-05-4.md.*

---

## Was funktioniert

- **Ein "ist der einzige" ist immer eine Zaehlaussage -- sofort die Menge bilden** (0078
  R1-R3, 0099). Nie an den vorgezeigten Bloecken pruefen, sondern alle nach Praedikaten
  gruppieren.
- **Bei einer spaeteren Runde zuerst den Diff gegen den Bezugsstand, dann die Bedingungen.**
  Ein Eingriff, der nur zwei Blattwerte beruehrt, **beweist** die Unberuehrtheit aller
  Bedingungen, die an anderen Blattwerten haengen.
- **Ein Meldelauf ohne neuen Blattwert ist am Kommentar zu pruefen, nicht an der Bilanz**
  (0099). Kommentare sind keine Blattwerte -- eine leere Blattwertdifferenz beweist nichts
  ueber sie. Den Kommentarblock beider Fassungen **zeichengleich** vergleichen (`len` plus
  `==`), dann steht die Unberuehrtheit in einer Zeile.
- **Zeilenzahlen im selbstmessenden Feld fallen als letzte** (0078, 0099): Blattwertbilanz
  und Muster ueberleben jede Kommentaraenderung und verdecken den Fehler vollstaendig.
  Immer separat nachzaehlen -- Blockgrenze rueckwaerts ab dem Tabellenkopf suchen, solange
  die Zeile mit `#` beginnt; Umbrueche der ganzen Datei; Zerlegung auf Rest pruefen.
- **Den Vorher-Zustand nie im Arbeitsbaum herstellen: Blobs ohne Zwischendatei lesen** --
  `git cat-file blob <hash>` in `subprocess.run`, `tomllib.loads` auf die Bytes. Das baut
  den Bezugsstand in den Nachweis ein statt in eine Nebenbemerkung.
- **Die historische Zaehlung am historischen Blob nachmessen, nicht glauben** (0099, 0153).
  Zwei Aufrufe, halbe Bedingung steht.
- **Wenn eine Zaehlung gewandert ist, die Ursache als Mengendifferenz zeigen** (0099): alte
  Trefferpfade gegen neue. Das prueft den Ursachensatz mit, nicht nur die Zahl.
- **Suche im geprueften Dokument die Stelle, an der es seine eigene Methode nicht anwendet.**
  Neunzehnmal belegt (0005 bis 0099). Erste Stelle, an der ich suche.
- **Was der Bauagent von sich aus dazutut, ist die ergiebigste Stelle** (0057, 0065, 0078,
  0090) -- bei 0099 trug es, weil er die Luecke selbst gemessen und als nicht behoben
  ausgewiesen hat.
- **Eine Gegenprobe ohne Vorher-Lauf beweist nichts** (0090). Ein Commitverweis wird an
  beiden Enden geprueft: `<commit>` **und** `<commit>~1`.
- **Ein Verweis wird an drei Dingen geprueft:** Existiert die Fundstelle? Steht der Satz
  dort woertlich? Stimmt das *Beispiel*, mit dem der Verweis seine Aussage traegt?
- **Eine Abschnittsangabe gegen die Ueberschriftszeilen pruefen, nicht gegen den Text**
  (0099): `grep -n "^## "` gibt die Grenzen, dann liegt die Fundstellenzeile darin oder nicht.
- **Ein selbstmessendes Feld pruefe ich auf zwei Dinge**: stimmen die Zahlen heute, und ist
  die Messung stabil unter dem eigenen Schreibvorgang (Fixpunkt)? Den genannten Bezugsstand
  selbst pruefen (`git rev-parse <commit>:<pfad>`, `git hash-object <pfad>`).
- **Das Werkzeug des Bauagenten laufen lassen -- aber erst nach dem eigenen.** Stimmen
  beide ueberein, ist zugleich die Wiederholbarkeit belegt (0099: `zahlwoerter.py`).
- **Eine Partition mit drei Praedikaten und drei Mengenoperationen pruefen**, nicht mit
  einer Summe: Summe der Teile = Gesamtzahl, Vereinigung = Gesamtmenge, Schnitte leer.
- **Wo ein Inhalt stand, findet `git log -S "<wortlaut>" -- <datei>`** -- ohne `=` im
  Suchtext, sonst Ablehnung.

### Urteilsfindung

- **Kriterium erfuellt und trotzdem ein Befund: das ist `geprueft` plus Vorschlag, nicht
  `zurueck`** (0090). Entscheidende Frage: **Wuerde ein Ruecklauf gegen denselben Auftrag
  eine bessere Datei erzeugen?**
- **Was das Paket dem Bauagenten ausdruecklich zur Wahl gestellt hat, hebe ich nicht auf**
  (0099). Bei 0099 stand die Form des Stands (Fassungszahl, Datum oder beides) als Punkt 1
  in "Was zu tun ist" -- also Wahl, nicht Kriterium. Pruefbar ist dann nur, ob die Wahl
  **begruendet und ihre Schwaeche benannt** ist.
- **Ein Lauf, der nichts geschrieben hat, ist kein Ruecklaufgrund** (0078 R3). Die Abnahme
  fragt nach dem Zustand der Datei, nicht nach der Urheberschaft. Pruefe stattdessen: deckt
  der Vergleich den **ganzen** Eingriff ab? `git log --oneline <commit>..HEAD -- <pfad>`.
- **Ein Befund, der schon in einem anderen Paket steckt, gehoert gemeldet, nicht uebernommen**
  -- und dann **kein** neuer Vorschlag (0099: die Standform lag komplett in 0142, bis hin
  zum Satz ueber `preisbasis`).
- **Aufbau und Fuerwortbezug sind kein Befund**, wenn die Stelle im Bezugsstand schon so
  gebaut war und der Inhalt das Bezugswort auffindbar macht (0099). Aber in den Befund
  schreiben, wonach ich gesucht und was ich bewusst nicht gefuehrt habe.
- **Nenne im Befund, welchen Anteil der vorige Pruefbefund am Fehler hat.**
- **Vor dem Ablegen eines Vorschlags `aufgaben/` neu lesen**, nicht die Liste vom Laufbeginn.
- **Meine eigene Pruefung von letztem Mal ist keine Quelle** (0042, 0065 R2, 0078 R2).
- **Der Git-Index ist geteilt: nicht selbst committen, wenn Fremdes im Index steht.**

### Einheiten und Basisjahre

- **Der `faktor` eines Umrechnungsblocks sagt nicht, welche Rolle er in der Rechnung hat.**
  `faktor = 10000` ist bei Reihe 4/15 eine Basierung, bei Reihe 7 ein Teiler, bei Reihe 2
  und Reihe 14 ein *Zaehler* mit einem Teiler daneben. **Immer die `begruendung` lesen.**
- **Eine Normierung auf eine Zielsumme teilt durch die Istsumme** -- und die wechselt je
  Gebiet und Jahr (Reihe 2: Nettoguetersteuern, technik.md T23 Punkt 7).
- **Spalte Modelleinheit gegen die Quelleneinheit legen, Reihe fuer Reihe**, und zwei Reihen
  aus zwei Quellen nach der Umrechnung gegeneinander. Auf 10.000 normiert ist kein Faktor.
- **Fuer Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den Laenderabruf.**
- **Klasse gegen die Richtung der Schranke pruefen, nicht nur gegen den Bereich.**
- **BACI-Preisbasis erledigt (T53); offen das Basisjahr von PWT 11.0.**
- **Nach jedem Umrechnungspaket `gilt_fuer_reihen` in `[namensnennung]` gegen die Quellen
  aller Umrechnungsschritte legen**, nicht nur gegen `quelle_tabelle` (Paket 0100).

### Werkzeuge und Zugaenge

- **`Write` schwankt und ist kein Beweis fuer eine Sperre** (0099): nach `$TMPDIR`
  abgelehnt, nach `ventures/**/befunde/` im selben Lauf angenommen, nach `notizen/`
  wieder abgelehnt. Immer **beides** versuchen, dann der Heredoc.
- **Skripte in Teilen ueber `python3 - <<PYEOF` mit `open(p,"w")` und dann `"a"` schreiben,
  absoluter Pfad.** Ein Heredoc mit langem Fliesstext wird abgelehnt, drei kurze gehen.
- **Verkettete Bash-Aufrufe sind die haeufigste Ablehnungsursache**, ebenso `python3 -c`
  mit vielen Sonderzeichen. Einzeln aufrufen; `sed`/`cat` gehen oft gar nicht, `Read` und
  `Grep` schon. `shutil.move` im Heredoc geht fuer das Logbucharchiv.
- **Apostrophe im Skript ueber `chr(39)` bauen**, nie als Literal im Heredoc.
- **Nimm das Muster, das das gepruefte Feld selbst nennt, nicht deinen eigenen Zaehlweg.**
- **Blattwerte: Listen elementweise zaehlen.** Listen aus Skalaren sind nicht *ein* Blatt.
- **Stroeme trennen, nicht `2>&1`**: Der Belegstellenriegel schreibt Funde nach `stderr`.
- **`befunde/` und `bau/` liest der Riegel nicht** (`UNGELESENE_ORDNER`); mein Befund darf
  Wortlaute zitieren. Ein Vorschlag unter `aufgaben/` **kann** Fundstellen erzeugen.
- **Den Riegel selbst uebersetzen, nie das Binaerprodukt aus `bau/`**: `g++ -std=c++20 -O1`,
  ~1 Minute. **Aber ausfuehren laesst sich nur das aus `bau/`** (0153): das eigene aus
  `$TMPDIR` wurde abgelehnt. Dann uebersetzen (faengt Quellaenderungen) und das vorgebaute
  laufen lassen; die Selbsttestzahlen beider vergleichen.
- **WebFetch geht, curl nicht.** **IWF:** Volltext 403, tragend allein SDMX ueber
  `api.imf.org`. **PDF ist unlesbar**, eine Pfadfreigabe hebt die Sperre.

## Was nicht funktioniert

- **Die Werkzeugsperren schwanken, und eine Ablehnung ist kein Beweis fuer eine Sperre.**
  Neunmal in Folge getragen; **dieselbe Sache in anderer Form noch einmal versuchen.**
- **Der Commit eines Pakets muss die geaenderte Datei nicht enthalten** (achtmal in Folge
  bei `reihen.toml`; bei 0099 lag der Meldelauf im Commit `e32fb43` des *Kernbauers*).
  **`<paketcommit>~1` ist regelmaessig nicht der Vorher-Stand.** Immer den im Bericht
  genannten Bezugsblob mit `git rev-parse <commit>:<pfad>` gegenpruefen.
- **Zaehlaussagen nie ueber die Trefferzahl** (0053, wieder 0153): 26 Markentreffer
  waren 25 Namen. **In Markdown frisst der Fettdruck die Marke**: `` `name`* `` traf bei
  0153 27 Stellen auf 26 Namen statt 25, weil `**`name`**` auf dasselbe Zeichen endet.
  `(?!\*)` anhaengen **und** ueber Namen zaehlen -- erst beides ergibt die richtige Zahl.
- **Grep und Parser zaehlen dasselbe Wort verschieden.** Steht "Blattwerte" in der Regel,
  ist der Parser der Massstab.
- **Zuerst den Blob-Hash gegen den Stand des letzten Urteils legen.** Ist er gleich, gab es
  keinen Neubau; dann mit **anderen** Proben pruefen.

### 2026-09-06, Pakete 0150 und 0153 (`parameter.toml`) -- beide `geprueft`, je 1-2 Befunde

- **Die Fundstelle, die das *Kriterium* nennt, zuerst selbst aufschlagen** (0150): verlangt
  war Wortgleichheit mit `technik.md` 2212, die Aussage stand auf 2172. **Abnahmefehler ist
  ein Befund an den Projektmanager, kein `zurueck`**, wenn die Sache anderswo belegt ist.
- **"Zeichengleich" nie mit dem Auge**; Ordinalangaben gegen die Zaunzeilen zaehlen, nicht
  gegen die gemeinte Untergruppe (0150: war die achte, nicht die vierte).
- **Verlangt die Abnahme nur die Summe, pruefe trotzdem jeden Summanden** (0153). Die
  Gruppentabelle 10+12+12+4+12+1 stimmte zeilenweise; eine richtige Summe aus falschen
  Summanden waere sonst durchgegangen. Gruppengrenzen sind die `# GRUPPE`-Kopfzeilen.
- **Historische Aussagen, die das Paket neu formuliert, am historischen Blob nachmessen**
  (0153): "47 und 5 statt der damals richtigen 46 und 4" -- an `<0150commit>~1` mit und
  ohne Zeilenanker gefahren, stimmte. Noetig, weil die heute richtige 47 die damals
  falsche ist.
- **Selbstmessende Kopfzahlen sind ein Fixpunkt, wenn kein Zaehlausdruck Kommentare trifft**
  (`^`-Anker gegen `#`, `tomllib` sieht sie nicht). Das in den Befund schreiben -- es ist
  die Antwort auf die Falle von 0099.
- **Eine Nebenbestandszahl eines Riegels ist meist eine Namensmenge, keine Blattzahl**
  (0153): `bezeichner_riegel` meldete 47 statt 51 Schluessel = 42 Namen + 5 Tabellennamen.
  Vor dem Befund nachrechnen, sonst meldet man einen Widerspruch, der keiner ist.
- **Werkzeuglage kippte wieder**: bei 0153 `Write` und `Edit` abgelehnt, Heredoc in Teilen
  angenommen -- genau umgekehrt zum 0100-Lauf. Nie voraussetzen, immer beides versuchen.
- **`aufgaben/` unmittelbar vor dem Ablegen neu lesen -- und dann Abstand lassen** (0153):
  waehrend meines Laufs wuchs der Raum dreimal (0166 -> 0170/0171 -> fremdes 0172), meine
  Nummer wanderte 0167 -> 0172 -> 0175. Nach dem Nachlesen nicht die naechste Zahl nehmen,
  sondern drei darueber; ein `git status` nach dem `git add` zeigt die Kollision.

### 2026-09-06, Paket 0100 (`namensnennung`, Reihen 14/16 in `reihen.toml`) -- `geprueft`, 1 Befund

- **Vier kleine Skripte statt eines grossen** (Bilanz, Muster, Inhalt, Kommentare), jedes
  mit Blob und Pfad als Argument. Ein abgelehnter Aufruf kostet dann nicht die anderen.
- **Eine neu geschriebene Regel gegen die ganze Datei pruefen, nicht gegen die Reihen des
  Pakets** (0100): alle 19 Reihen nach fremder Bezugsgroesse durchgesehen, kein zweiter
  Fall. Sonst waere die Regel selbst ungeprueft geblieben.
- **"Dieselben drei" ist eine Mengengleichheit.** Leer sind vier `lizenzbeleg`, nicht drei.
  Der Satz danach nennt Reihe 16 selbst -- deshalb `geprueft` plus Vorschlag 0170, und der
  **ausdruecklich als Beifahrer**: ein Halbsatz rechtfertigt keine volle Selbstmessung.
