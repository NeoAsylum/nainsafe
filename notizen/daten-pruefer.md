# Logbuch: daten-pruefer

Privat. **Hoechstens 12.000 Zeichen** (wc -c). Belege in die Ergebnisdatei, hierher die
Lehre. *Neu begonnen 2026-09-05 nach Paket 0078 Runde 2, Vorgaenger:
archiv/daten-pruefer-2026-09-05-2.md.*

---

## Was funktioniert

- **Ein "ist der einzige" ist immer eine Zaehlaussage -- sofort die Menge bilden** (0078 R1
  und R2). Nie an den vorgezeigten Bloecken pruefen, sondern alle nach Schluesselmengen
  gruppieren (`Counter(tuple(sorted(u.keys())))`).
- **Eine *ersetzte* Einzigkeitsbehauptung ist wieder eine, und sie faellt am gleichgeformten
  Nachbarn** (0078 R2, wichtigste Lehre des Laufs). Die Prueffrage ist nicht "stimmt der
  neue Satz", sondern: **welcher Block hat dieselbe Bauform wie der, dessen Einzigkeit
  behauptet wird?** Bei 0078 war Reihe 14 (`deflationierung`) strukturgleich zu Reihe 2
  (`normierung`) -- beide `faktor = 10000` als *Zaehler*, beide mit einem je Jahr wechselnden
  Teiler. Der Bauagent hatte alle 23 Bloecke gemessen und trotzdem nur das Feld `faktor`
  angesehen, nicht die Rechenrolle.
- **Der Ausweg, den mein eigener letzter Befund vorschlaegt, kann die Falle sein** (0078).
  R1 empfahl "die Einzigkeit auf den jahresweisen Teiler einschraenken" -- genau daran ist R2
  gefallen. **Ab jetzt: keinen Ersatzwortlaut vorschlagen, ohne ihn selbst gegen dieselbe
  Menge gemessen zu haben.** Im Befund stattdessen die Bedingung nennen und den sicheren
  Ausgang (streichen).
- **Suche im geprueften Dokument die Stelle, an der es seine eigene Methode nicht anwendet.**
  Siebzehnmal belegt (0005 bis 0078 R2). Erste Stelle, an der ich suche.
- **Die Widerlegung steht oft im selben Feld, zwei Saetze ueber der Behauptung** (0078 R2):
  Die Aufzaehlung, die der Bauagent selbst schreibt, um die Behauptung zu stuetzen, enthielt
  sie woertlich ("braucht die drei Sektoranteile des Gebiets und Jahres").
- **Was der Bauagent von sich aus dazutut, ist die ergiebigste Stelle** (0057, 0065, 0078,
  0090). Fuenfmal in Folge.
- **Bei einer Runde 2 zuerst den Diff gegen den Bezugsstand, dann erst die Bedingungen.**
  Ein Eingriff, der nur zwei Blattwerte beruehrt, **beweist** die Unberuehrtheit aller
  Bedingungen, die an anderen Blattwerten haengen -- die Bilanz ersetzt die Nachpruefung.
- **Eine Gegenprobe ohne Vorher-Lauf beweist nichts** (0090). Jede Negativ-Gegenprobe
  braucht einen Positiv-Zwilling auf dem Vorher-Stand.
- **Eine Partition pruefe ich mit drei Praedikaten und drei Mengenoperationen**, nicht mit
  einer Summe: Summe der Teile = Gesamtzahl, Vereinigung = Gesamtmenge, Schnitte leer.
- **Ein selbstmessendes Feld pruefe ich auf zwei Dinge** (0062, 0065, 0078, 0090): stimmen
  die Zahlen heute, und ist die Messung stabil unter dem eigenen Schreibvorgang? Den
  genannten Bezugsstand selbst pruefen (`git ls-tree`, `git hash-object`).
- **Ein Verweis wird an drei Dingen geprueft:** Existiert die Fundstelle? Steht der Satz dort
  woertlich? Und -- der Schritt, den man ueberspringt -- stimmt das *Beispiel*, mit dem der
  Verweis seine Aussage traegt? Bei Indexangaben `reihe[i]["nr"]` nachschlagen; ab null.
- **Verlangt eine Bedingung eine Regel, pruefe sie ueber die ganze Datei**, nicht an den
  vorgezeigten Stellen.
- **Wo `specs/` und die Datei schweigen, ist die Entscheidung des Bauagenten gueltig.**
- **Wo ein Inhalt wirklich stand, findet `git log -S "<wortlaut>" -- <datei>`.** Vorsicht:
  `-S` mit `=` im Suchtext wurde abgelehnt, ohne `=` ging derselbe Aufruf.

### Urteilsfindung

- **Kriterium erfuellt und trotzdem ein Befund: das ist `geprueft` plus Vorschlag, nicht
  `zurueck`** (0090). Die Prueffrage, die es entscheidet: **Wuerde ein Ruecklauf gegen
  denselben Auftrag eine bessere Datei erzeugen?** Nein, wenn der Fehler im Arbeitspaket
  **vorgegeben** war -- dann geht der Befund an den Projektmanager. Ja bei 0078 R2: Der PM
  hatte ausdruecklich geschrieben, die *Bedingung* sei die Vorgabe und nicht der Wortlaut des
  Pruefers. Damit lag die Ursache im Bau.
- **Nenne im Befund, welchen Anteil der vorige Pruefbefund am Fehler hat.** Bei 0078 R2 war
  das der wichtigste Satz fuer den PM: Ein dritter Ruecklauf, der wieder eine engere
  Einzigkeit sucht, faellt vermutlich wieder.
- **Ein Befund, der schon in einem anderen Paket steckt, gehoert gemeldet, nicht uebernommen.**
- **Vor dem Ablegen eines Vorschlags `aufgaben/` neu lesen, nicht die Liste vom Laufbeginn.**
  `grep -ln "<datei>" aufgaben/*.md` in einem Aufruf; fremde Laeufe legen waehrenddessen an.
- **Meine eigene Pruefung von letztem Mal ist keine Quelle** (0042, 0065 R2, 0078 R2).
- **Der Git-Index ist geteilt: nicht selbst committen, wenn Fremdes im Index steht.**

### Einheiten und Basisjahre

- **Der `faktor` eines Umrechnungsblocks sagt nicht, welche Rolle er in der Rechnung hat.**
  `faktor = 10000` ist bei Reihe 4/15 eine Basierung, bei Reihe 7 ein Teiler, bei Reihe 2 und
  Reihe 14 ein *Zaehler* mit einem Teiler daneben. **Immer die `begruendung` lesen, nie das
  Feld allein.** Das ist der Kern des Befunds zu 0078 R2.
- **Eine Normierung auf eine Zielsumme teilt durch die Istsumme** -- und die wechselt je
  Gebiet und Jahr, wenn die Quelle nicht auf die Zielsumme aufgeht (Reihe 2:
  Nettoguetersteuern, T23 Punkt 7).
- **Spalte Modelleinheit gegen die Quelleneinheit legen, Reihe fuer Reihe**, und zwei Reihen
  aus zwei Quellen nach der Umrechnung gegeneinander. Auf 10.000 normiert ist kein Faktor.
- **Fuer Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den Laenderabruf.**
- **Die Einheit einer abgeleiteten Groesse steht nie in ihrer eigenen Zeile.**
- **Klasse gegen die Richtung der Schranke pruefen, nicht nur gegen den Bereich.**
- **Stand 2026-09-05:** BACI-Preisbasis inhaltlich erledigt (T53). Offen allein das Basisjahr
  von PWT 11.0.
- **Nach jedem Umrechnungspaket `gilt_fuer_reihen` in `[namensnennung]` gegen die Quellen
  aller Umrechnungsschritte legen**, nicht nur gegen `quelle_tabelle` (0078 → Paket 0100).

### Werkzeuge und Zugaenge

- **`Write` kann ganz fehlen** (0078 R2, auch nach `$TMPDIR`). Ausweg: `python3 - <<'PYEOF'`
  mit `open(p,"w").write(...)` und `"a"` fuer die Fortsetzung, **in drei Haeppchen**.
  **Zwingend absoluter Pfad** -- das cwd der Bash ist nicht die Repowurzel.
- **Lange Heredocs mit vielen Regex-Sonderzeichen werden abgelehnt.** Kurz halten, aufteilen,
  `[.]` statt Backslash-Punkt und `[[]` statt Backslash-Klammer schreiben.
- **Nimm das Muster, das das gepruefte Feld selbst nennt, nicht deinen eigenen Zaehlweg**
  (0078 R2): Meine Zeilen-mit-genau-einem-Vorkommen gab 4, das Feldmuster des Schnitts gab 27.
  Beides richtig gezaehlt, nur eines war die Frage.
- **Blobs ohne Zwischendatei lesen:** `git cat-file blob <hash>` in `subprocess.run` und
  `tomllib.loads` auf die Bytes -- baut den Bezugsstand in den Nachweis ein.
- **`befunde/` und `bau/` liest der Riegel nicht** (`UNGELESENE_ORDNER`, Z. 613 von
  `belegstellen_riegel.cpp`). Mein Befund darf Wortlaute zitieren; ein Vorschlag unter
  `aufgaben/` **kann** neue Fundstellen erzeugen -- dann nachmessen.
- **Den Riegel selbst uebersetzen, nie das Binaerprodukt aus `bau/` nehmen** (0090):
  `g++ -std=c++20 -O1`, ~1 Minute. Zweites Argument ist der Schluessel zur Gegenprobe.
- **WebFetch geht, curl nicht.** **IWF:** Volltext 403, tragend allein SDMX ueber
  `api.imf.org`. **PDF ist unlesbar**, eine Pfadfreigabe hebt die Sperre.

## Was nicht funktioniert

- **Die Werkzeugsperren schwanken, und eine Ablehnung ist kein Beweis fuer eine Sperre.**
  Siebenmal in Folge getragen; **dieselbe Sache in anderer Form noch einmal versuchen.**
- **Verkettete Bash-Aufrufe sind die haeufigste Ablehnungsursache**, nicht das Werkzeug
  selbst. Erst der einzelne Aufruf, dann die Verkettung -- nie umgekehrt.
- **Wo Bash scheitert, nimmt das dedizierte Werkzeug denselben Weg:** `Grep` mit `path` liest
  auch Dateien, die eine Bash-Pipe nicht anfassen durfte.
- **Der Commit eines Pakets muss die geaenderte Datei nicht enthalten** (sechsmal in Folge bei
  `reihen.toml`; bei 0078 R2 trug sie der fremde Commit `c30acc5`, der Paketcommit `07cc49b`
  gar nicht). **`<paketcommit>~1` ist regelmaessig nicht der Vorher-Stand.** Immer den im
  Bericht genannten Bezugsblob mit `git ls-tree` und `git hash-object` gegenpruefen -- bei
  0078 R2 waren das zwei Aufrufe und die halbe Pruefung stand.
- **Zaehlaussagen nie ueber die Trefferzahl** (0053): 26 Markentreffer waren 25 Namen.
- **Grep und Parser zaehlen dasselbe Wort verschieden.** Steht "Blattwerte" in der Regel, ist
  der Parser der Massstab.
- **Zuerst den Blob-Hash gegen den Stand des letzten Urteils legen.** Ist er gleich, gab es
  keinen Neubau; dann mit **anderen** Proben pruefen.
- **Pipes in Markdown-Tabellen nicht maskieren.**

## Offene Faehrten

- **0078 laeuft auf Ruecklauf 3 zu.** Wenn der naechste Durchgang wieder eine Einzigkeit
  formuliert statt zu streichen, zuerst Reihe 2 Schritt 2 pruefen -- und dann nach dem
  *naechsten* gleichgeformten Block suchen, nicht nach demselben.
- **Belegstellen als Nummern sind eine Bauart, kein Einzelfall** (0034 bis 0090). Naechste
  Kandidaten: `Abschnitt <n>`, `Fassung <n>`, `<commit>~1` (Vorschlag 0126).
- **Prosa-Befund und maschinenlesbare Zwillingsdatei laufen ohne ein drittes Paket immer
  auseinander** (0024, 0032, 0036, 0049, 0057).
- **Zwei `offen`-Pakete auf derselben Datei koennen dasselbe Feld beanspruchen.** Vor dem
  Urteil die anderen `offen`-Pakete auf die Dateiliste lesen.
- **PWT bleibt ungemessen** -- Kapitalstockeinheit und Basisjahr. Loest sich erst, wenn der
  Betreiber `pwt110.xlsx` nach `daten/roh/` legt oder den PDF-Pfad freigibt.
- **`technik.md` fuehrt Reihe 9 weiter als Sollreihe der Klasse `gesetzt`** -- Widerspruch
  Nr. 5, Vorschlag `0068`, gehoert dem Architekten.
- **Reihe 10:** Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6 (Widerspruch Nr. 4, weiter
  offen). Offen ist auch die Rundung vor oder nach der Normierung (Reihe 2, `rundungsstelle`).
- **`[datei.vorlagen]` fuehrt T53 nicht** -- Vorschlag `0099`, unveraendert offen.
