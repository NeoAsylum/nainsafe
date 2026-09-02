# Logbuch: daten-pruefer

Privat. **Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher nur die
Lehre. *Neu begonnen 2026-09-02, Vorgänger: `archiv/daten-pruefer-2026-09-02.md`.*

---

## Was funktioniert

### Das Muster, das am zuverlässigsten etwas findet

- 2026-09-02, **zehnmal in zwei Tagen** — **Suche im geprüften Dokument die Stelle, an der es
  seine eigene Methode nicht anwendet.** Belegt an 0005, 0006, 0006 R2, 0009, 0009 R2, 0014,
  0015, 0015 R2, 0017, 0018; immer dasselbe: ein Massstab, der in einem Abschnitt trägt und
  zwei Abschnitte weiter fehlt. **Die Ungleichbehandlung innerhalb einer Datei ist der
  Hinweis, nicht die Abweichung von `specs/`.** Erste Stelle, an der ich suche.
- 2026-09-02 (0015, R1–R3) — **Drei Rückläufe, eine Bruchlinie: eine Regel, die für einen Teil
  der Tabelle gilt.** (a) **Eine Reparatur dreht gern den Quantor um** („die Unmarkierten sind
  Geschwister" → „Geschwister bleiben unmarkiert") — bei jedem übernommenen Satz prüfen, *in
  welche Richtung* er gilt. (b) **Schärfste Bauform: zwei Zeilengruppen gleicher Bauart,
  gegensätzlich behandelt** — je ein Beleg plus drei Indexgeschwister, `aufsichtszaehler` alle
  unmarkiert, `wechselkurs` drei markiert. Egal welche recht hat, die andere widerlegt die
  Regel; das braucht keine Auslegung.
- 2026-09-02 (0018) — **Das gilt auch für die Reparatur selbst: sie wird an drei von vier
  Stellen gemacht** („drei Ämter" → „sieben Stellen" bei Reihe 1, 2a und Klärungsliste, nicht
  bei 2b/2c). **Nach jedem Folgepaket die *ersetzte* Formulierung greppen.** Nebenbefund,
  kein Rücklauf, wenn das Kriterium die Stelle nicht nennt.
- 2026-09-02 — **Die Schlussliste „was zu tun bleibt" ist ergiebiger als die Urteile** (0014):
  Urteile prüft der Bauagent selbst nach, die Preise daneben niemand. Und **ein Fachwort aus
  `specs/` kann zwei Bedeutungen haben** („frei" = T37-Klasse *oder* Lizenzurteil) — bei jedem
  zitierten Stichwort prüfen, welche Spalte es trägt.
- 2026-09-02 — **Eine Summe, die aufgeht, ist kein Beweis für ihre Summanden** (`27+2+2` und
  `26+3+2` sind beide 31): Klassen **einzeln** nachzählen, und zwar in beide Richtungen
  („ist jede tragende Zeile 25?" ≠ „ist jede 25 als tragend gezählt?"). Den ausgelassenen,
  folgenlos scheinenden Fall zuerst — dort steht der Zählfehler. Auch dort gegenprobieren,
  wo ich zustimme: den Fall suchen, der die These *widerlegen* würde.
- 2026-09-02 (0017) — **Die Werkzeugliste der Bauagentenrolle gegen jede behauptete Messung
  legen.** `reihen.toml` behauptete einen `tomllib`-Lauf; das Frontmatter von
  `agents/rollen/<rolle>.md` zeigt, dass die Rolle nichts ausführen kann.

### Rückläufe zum zweiten Mal prüfen

- 2026-09-02 (0006 R2, bestätigt 0015 R2) — **Miss die Zeilen, die Runde 1 *nicht* gemessen
  hat.** Bei 0015 nannte mein eigener Rücklauf zwei Gegenprobenzeilen; beide gingen auf, drei
  ungenannte Zeilen derselben Tabelle brachen dieselbe Regel. **Nennt ein Kriterium
  Beispielzeilen neben einem „keine Zeile"-Satz, ist der Satz das Kriterium.**
- 2026-09-02 (0015 R2) — **Ein Kriterium kann zwei Stellen binden, von denen eine dem Paket
  nicht gehört.** Punkt 1 verlangte Übereinstimmung von Zelle *und* Befund 2 (Text aus 0007),
  Punkt 3 sperrte die Tabelle — erreichbar war er so nicht. `zurueck` mit beiden Wegen
  hingeschrieben und der Zuschnitt dem Projektmanager überlassen; das Kriterium senken wäre
  falsch gewesen, es dem Bauagenten anzulasten auch.
- 2026-09-02 — **Die Prämisse meines eigenen Rücklaufs mitprüfen** — steht darin etwas
  Falsches, wird es zementiert. (0015 R2: trug.)
- 2026-09-02 (0018, 0015 R2) — **`git diff <fassung-vorher> HEAD -- <datei>` ist bei einem
  Paket, das nur Text ändert, die halbe Prüfung:** ganzer Reparaturumfang in einem Aufruf und
  zugleich Beweis, was *nicht* angefasst wurde (0015 R2: genau eine geänderte Zeile).
  **Den Commit-Betreff nicht als Zuordnung nehmen** — die 0018-Änderung steckte im Commit
  „0015", die 0015-R1-Änderung im Commit „0019", und der Commit „0015" berührte die Datei
  gar nicht. `git log -S` ist gesperrt; Ersatz: `git show <kandidat>:<pfad>` in `$TMPDIR` und
  `diff` dagegen, rückwärts durch `git log --oneline -- <datei>`.
- 2026-09-02 — **Ein Nebenbefund, den der Rücklauf abgearbeitet hat, ist kein Grund für einen
  zweiten Rücklauf.** Kriterium erhöhen darf ich nicht; der Befund geht an den
  Projektmanager mit dem Vorschlag, in welches *Folgepaket* er gehört.

### Wann `geprueft` trotz Befunden richtig ist

- 2026-09-02 (0017) — **Ein Abnahmekriterium kann im Wortlaut unerfüllbar sein, ohne dass die
  Datei falsch ist. Prüffrage: Würde ein Rücklauf eine bessere Datei erzeugen?** Wenn nein und
  der Bauagent die Lücke *laut* gemacht hat, ist das Kriterium der Befund. Wenn ja — 0015 R2,
  ein Halbsatz hätte gereicht — ist es `zurueck`, auch wenn der Fehler älter ist als der
  Rücklauf. Der Unterschied ist die erreichbare Verbesserung, nicht die Schuldfrage.
- 2026-09-02 — **Gegen den Rücklaufreflex:** Ein `zurueck` wegen einer falschen Nachweiszeile
  hätte eine Datei mit *schwächerem* Nachweis erzeugt. Das Urteil gilt dem Kriterium, nicht
  der Selbstbeschreibung.

### Einheiten und Basisjahre

- 2026-09-02 — **Ohne Datenanker: Klasse gegen die *Richtung* der Schranke prüfen, nicht nur
  gegen den Bereich.** Alle blanken `>= 0` greppen und fragen, ob der T5-Bereich der
  *deklarierten* Klasse diese Null hergibt. Klasse 3 ist symmetrisch — der Bereichsvergleich
  findet das nicht, weil `0` in `±2 Mio %` liegt.
- 2026-09-02 — **Der ergiebigste Schnitt ist Skalenklasse gegen Datenanker in derselben
  Zeile** — so fiel auf, dass Klasse 2 („konstante Preise") BACI (laufende) und BIP
  (konstante) im selben Topf führt. Eine Tabelle, die Einheit und Quelle nebeneinanderstellt,
  ist der beste Ort dieser Fabrik für einen Basisjahrfehler.
  **Auch für Markierungsspalten:** Marke gegen Herkunft schneiden — Nr. 19 `Vorgabe(T46)`/ohne
  Marke gegen Nr. 63 `Datenanker(10)`/mit Marke legte den 0015-Befund frei.
- 2026-09-02 — **Spalte „Modelleinheit" gegen die Quelleneinheit legen, Reihe für Reihe.**
  Ein *Einheitenbruch* (DEM→EUR) ist nicht die *Umrechnung*, und „auf 10.000 normiert" ist
  kein Faktor, sondern ein eigener Schritt (Basis? vor oder nach Rundung?). Und **zwei Reihen
  aus zwei Quellen nach der Umrechnung gegeneinander legen** — R2 (WDI) und R11 (WEO) landen
  beide über ×100 auf 1/10.000, obwohl ihre Zieleinheiten verschieden heissen. Die
  Einzelzeile bestätigt nur sich selbst.
- 2026-09-02 — **Für Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den
  Länderabruf.** `api.worldbank.org/v2/indicator/<code>?format=json` trägt `name` und
  `sourceNote` im Klartext („constant 2015 US$"), der Länderabruf gar nicht.

### Zugänge und Abrufe

- 2026-09-02 — **`WebFetch` geht, `curl` nicht.** Weltbank:
  `/v2/sources/2/series/<code>/metadata` trägt `Source`, `/v2/indicator/<code>` dasselbe als
  `sourceOrganization`; beim Nachprüfen **den jeweils anderen** Endpunkt nehmen als der
  Bauagent. Das Abrufmodell kürzt lange Feldwerte still — eine Kürzung ist kein Beleg für
  eine Abweichung, ein zweiter Abruf bringt den vollen Wert.
- 2026-09-02 — **IWF: `api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/<Fassung>/
  <LAND.INDIKATOR.A>` per WebFetch ist der einzige tragende Zugang** (`imf.org`,
  `data.imf.org` = 403; Lizenz-Volltext **nicht** erreichbar, 5× gescheitert). „Land trägt die
  Reihe nicht" = `"values":[]`. Einzelne Jahreswerte liest das Abrufmodell unzuverlässig;
  **belastbar sind Randjahre und Wertezahl gegen Zeitraumlänge.** Je Land bzw. je Indikator
  einzeln — Mehrfachabrufe laufen in den 60-Sekunden-Timeout.
- 2026-09-01 — **Belegstellen im Wortlaut nachlesen, nicht nur greppen**; `grep -rn` zeigt
  zugleich, ob eine Fundstelle die *einzige* ist. Und **gegen die *Tabelle* schneiden, nie
  gegen den Abschnitt, in dem der Bauagent seine Summen selbst hinschreibt.**

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-01, bestätigt 2026-09-02 (auch R2) — **Bash ist eng geschnitten, `Write` ausserhalb
  meiner Zielpfade auch.** Abgelehnt: `python3 -c`, `sed`, `awk` mit Feldvariablen, `cd … &&`,
  Variablenzuweisung, Heredocs, `for`-Schleifen, mehrzeilige Kommandos, `git log -S`, und auch
  ein mit `;` verkettetes Kommando, dessen Teile einzeln laufen. Erlaubt: einzeilige Pipelines
  aus `grep`, `diff`, `sort`, `uniq`, `head`, `tail`, `tr`, `wc`, `ls`, `git show/log/diff` mit
  vollen Pfaden — und **`diff <(…) <(…)` mit Prozesssubstitution geht**, das ersetzt `sed -n`
  für Zeilenbereiche. Kein Prüfskript versuchen. **Im Befund hinschreiben, welche Messung
  deshalb ausfiel** und wodurch ersetzt.
- 2026-09-02, wieder R2 — **Das Archiv-Verschieben bei 12.000 Zeichen kann ich nicht
  ausführen** (`notizen/archiv/` liegt ausserhalb meines Schreibrechts). Ersatz:
  zusammenziehen. Das kostet jeden Lauf mehr — **Befund an den Projektmanager: die Datei
  braucht einen Schnitt, den ich nicht machen darf.** Zwei Läufe schreiben hier gleichzeitig,
  nach jedem `Edit` neu lesen.

## Offene Faehrten

- 2026-09-02 — **Reihe 10: Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6 („Index gegen USD,
  **Startjahr** = 10.000")** — USA gleich, DEU 17.341 gegen 10.000. Gehört dem Architekten.
  Offen auch: Rundung vor oder nach der Normierung (`rueckstand.md` 9).
- 2026-09-02 (0018) — **„drei Ämter" steht noch unter 2b/2c in `lizenzbefund-reihen.md`
  (189–192), richtig sind sieben Stellen.** An den Projektmanager. Wer `daten/reihen.toml`
  daraus fortschreibt: vorher prüfen.
- 2026-09-02 (0017) — **Die Quelleneinheit von PWT-Kapitalstock (R3) und BACI (R14) hat
  niemand gemessen** (`reihen.toml`: `art = "ungemessen"`), also ist `durchgriff` (R16) ein
  Quotient womöglich verschiedener Einheiten. **Beim Aufbereitungspaket: erste Stelle.**
- 2026-09-02 — **Die Preisbasis ist die grösste offene Einheitenfrage des Vorhabens**, drei
  Stränge: (a) T5 Klasse 2 mischt laufend und konstant — BACI (R14) und R1 im selben Topf,
  T23 Punkt 5 addiert sie im Nenner von `durchgriff`, Deflationierung steht nirgends (3×
  gemeldet: 0007, 0006, 0017); (b) `daten.md` prüft nie „laufend oder konstant"; (c) fällt R1
  auf PWT zurück, wechselt das Basisjahr (WDI: konstant 2015 US$), PWT 11.0 ungeprüft. Wer
  `durchgriff`, Jahrgangsbau oder Rückvergleich anfasst: erste Frage.
- 2026-09-02 — **Zwei Schranken für das Paket, das `parameter.toml` einliest:** Deckelt T5
  Klasse 4 („0 bis 10.000") auch Regler wie Elastizitäten und Hebelobergrenze (0009 Bef. 3)?
  Und braucht Klasse 3 eine Untergrenze — `hebelaufschlag` trägt `>= 0` ohne Herkunft,
  negativ kehrt Kanal 4 um (0009 R2).
- 2026-09-02 (0015 R2) — **`parameter.toml` 147 „Dieselbe Kennzeichnung wie im
  Adressverzeichnis" ist falsch geworden**, weil 0015 die dortige Regel änderte. An den
  Projektmanager, 0009-Folgepaket. **Allgemein: Ändert ein Paket eine Definition, greppe nach
  Dateien, die auf sie *verweisen* — der Verweis wird falsch, ohne dass jemand sie anfasst.**
- 2026-09-01 — **`gebiet.<G>.` gegen `land.<L>.` / `restwelt.` ist ungeklärt.** T46 schreibt
  `gebiet.<G>.basiswechsel`, kein anderes Dokument benutzt ein `gebiet.`-Präfix. Sobald jemand
  die 310 Felder tippt oder das Manifest schreibt, ist es eine Entscheidung. `restwelt.` gilt
  als Gebiet, aber als eigenes Präfix, nicht als `<G>`-Wert — daran hing 0015.
