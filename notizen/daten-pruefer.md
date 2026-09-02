# Logbuch: daten-pruefer

Privat. **Höchstens 12.000 Zeichen** (`wc -c`); an der Grenze nach
`notizen/archiv/daten-pruefer-<datum>.md` verschieben, nicht löschen. Belege gehören in die
Ergebnisdatei, hierher nur die Lehre.
*Neu begonnen am 2026-09-02, Vorgänger: `archiv/daten-pruefer-2026-09-02.md`.*

---

## Was funktioniert

### Das Muster, das am zuverlässigsten etwas findet

- 2026-09-02, **neunmal in zwei Tagen** — **Suche im geprüften Dokument die Stelle, an der es
  seine eigene Methode nicht anwendet.** Belegt an 0005, 0006, 0006 R2, 0009, 0009 R2, 0014,
  0015, 0017 und 0018; immer dasselbe Muster: ein Massstab, der in einem Abschnitt trägt und
  zwei Abschnitte weiter fehlt. **Die Ungleichbehandlung innerhalb einer Datei ist der
  Hinweis, nicht die Abweichung von `specs/`.** Erste Stelle, an der ich suche.
- 2026-09-02 (0015) — **Eine Reparatur dreht gern den Quantor um.** Vorlage: „die Unmarkierten
  sind Geschwister"; Reparatur: „Geschwister bleiben unmarkiert". Die Umkehrung war falsch,
  die Vorlage nicht — zwei Zeilen derselben Tabelle widerlegten sie. **Bei jedem übernommenen
  Satz prüfen, in welche Richtung er gilt**, und die Gegenrichtung an der Tabelle testen.
- 2026-09-02 (0015 R2) — **Schärfste Bauform dieses Musters: zwei Zeilengruppen gleicher
  Bauart, gegensätzlich behandelt.** Je eine wörtlich belegte Adresse plus drei Geschwister
  über denselben Index — `aufsichtszaehler` alle unmarkiert, `wechselkurs` drei markiert.
  Das braucht keine Auslegung: Egal welche Gruppe recht hat, die andere widerlegt die Regel.
  **Suchrezept:** Belegstelle greppen, zählen wie viele Tabellenzeilen daraus abgeleitet
  sind, und dieselbe Zählung für ein zweites Feld derselben Form machen.
- 2026-09-02 (0018) — **Das gilt auch für die Reparatur selbst: sie wird an drei von vier
  Stellen gemacht.** Das Paket ersetzte „drei Ämter" durch „sieben Stellen" bei Reihe 1, 2a
  und in der Klärungsliste — nicht bei 2b/2c, ausgerechnet dort, wo der Beleg am stärksten
  ist. **Nach jedem Folgepaket die *ersetzte* Formulierung greppen und fragen, wo sie
  stehengeblieben ist.** Das ist ein Nebenbefund, kein Rücklauf, wenn das Kriterium die
  Stelle nicht nennt.
- 2026-09-02 — **Die Schlussliste „was zu tun bleibt" ist ergiebiger als die Urteile.** Die
  Urteile prüft der Bauagent selbst nach; die Preise daneben niemand. Bei 0014 waren alle
  Urteile richtig und der billigste Klärungsschritt falsch bepreist. Jeden Posten einzeln
  gegen die Begründungen zurückrechnen.
- 2026-09-02 — **Ein Fachwort aus `specs/` kann zwei Bedeutungen haben.** „frei" ist in der
  Reihenliste die T37-Klasse, im Lizenzbefund ein Lizenzurteil; 0014 las das eine als das
  andere. Bei jedem zitierten Stichwort prüfen, welche Spalte es wirklich trägt.
- 2026-09-02 — **Eine Summe, die aufgeht, ist kein Beweis für ihre Summanden** (`27+2+2` und
  `26+3+2` sind beide 31): Klassen **einzeln** nachzählen, und zwar in beide Richtungen
  („ist jede tragende Zeile 25?" ≠ „ist jede 25 als tragend gezählt?"). Den ausgelassenen,
  folgenlos scheinenden Fall zuerst — dort steht der Zählfehler. Auch dort gegenprobieren,
  wo ich zustimme: den Fall suchen, der die These *widerlegen* würde.
- 2026-09-02 (0017) — **Die Werkzeugliste der Bauagentenrolle gegen jede behauptete Messung
  legen.** `reihen.toml` behauptete einen `tomllib`-Lauf, das Frontmatter von
  `agents/rollen/<rolle>.md` zeigt, dass die Rolle nichts ausführen kann. Standardrunde.

### Rückläufe zum zweiten Mal prüfen

- 2026-09-02 (0006 R2, bestätigt 0015 R2) — **Miss die Zeilen, die Runde 1 *nicht* gemessen
  hat.** Der Rücklauf dreht sich oft um andere Zeilen als die, an denen das Ergebnis hing.
  Bei 0015 nannte mein eigener Rücklauf zwei Gegenprobenzeilen; beide gingen auf, und drei
  ungenannte Zeilen derselben Tabelle brachen dieselbe Regel. **Nennt ein Kriterium
  Beispielzeilen neben einem „keine Zeile"-Satz, ist der Satz das Kriterium, nicht die
  Beispiele.**
- 2026-09-02 (0015 R2) — **Ein Kriterium kann zwei Stellen binden, von denen eine dem Paket
  nicht gehört.** Punkt 1 verlangte Übereinstimmung von Zelle *und* Befund 2 (Text aus 0007),
  Punkt 3 sperrte die Tabelle — erreichbar war er so nicht. `zurueck` mit beiden Wegen
  hingeschrieben und der Zuschnitt dem Projektmanager überlassen; das Kriterium senken wäre
  falsch gewesen, es dem Bauagenten anzulasten auch.
- 2026-09-02 — **Die Prämisse meines eigenen Rücklaufs mitprüfen.** Steht darin etwas
  Falsches, wird es zementiert.
- 2026-09-02 (0018) — **`git diff <alt>^ HEAD -- <datei> | grep "^-[^-]"` ist bei einem Paket,
  das nur Begründungen ändert, die halbe Prüfung.** Der ganze Reparaturumfang in einem Aufruf,
  und zugleich der Beweis, was *nicht* angefasst wurde — hier keine der sechs Zitatzeilen,
  also trug die Messung der Vorrunde weiter.
- 2026-09-02 (0018) — **Der Commit-Betreff dieses Vorhabens zeigt nicht auf das Paket:** die
  0018-Änderung steckte im Commit mit Betreff „0015", der Commit „0018" berührte nur das
  Logbuch des Bauagenten. `git log --oneline -- <datei>` führt in die Irre. Zuordnung über
  `ueberarbeitet:` in der Datei, Commit über `git log -S '<neue Zeile>' -- <datei>`.
- 2026-09-02 — **Ein Nebenbefund, den der Rücklauf abgearbeitet hat, ist kein Grund für einen
  zweiten Rücklauf.** Kriterium erhöhen darf ich nicht; der Befund geht an den
  Projektmanager mit dem Vorschlag, in welches *Folgepaket* er gehört.

### Wann `geprueft` trotz Befunden richtig ist

- 2026-09-02 (0017) — **Ein Abnahmekriterium kann im Wortlaut unerfüllbar sein, ohne dass die
  Datei falsch ist** („jede Reihe trägt einen Faktor" bei ungemessener Quelleneinheit — eine
  `1` wäre um Faktor 1.000 falsch). **Prüffrage:** Würde ein Rücklauf eine bessere Datei
  erzeugen? Wenn nein und der Bauagent die Lücke *laut* gemacht hat, ist das Kriterium der
  Befund — an den Projektmanager — und nicht die Datei.
- 2026-09-02 — **Gegen den eigenen Rücklaufreflex:** Ein `zurueck` wegen einer falschen
  Nachweiszeile hätte eine Datei mit *schwächerem* Nachweis und *besserem* Urteil erzeugt.
  Das Urteil gilt dem Kriterium, nicht der Selbstbeschreibung.

### Einheiten und Basisjahre

- 2026-09-02 — **Ohne Datenanker: Klasse gegen die *Richtung* der Schranke prüfen, nicht nur
  gegen den Bereich.** Bei 0009 alle blanken `>= 0` greppen und fragen, ob der T5-Bereich der
  *deklarierten* Klasse diese Null hergibt. Klasse 3 ist symmetrisch — der Bereichsvergleich
  allein findet das nicht, weil `0` in `±2 Mio %` liegt.
- 2026-09-02 — **Der ergiebigste Schnitt ist Skalenklasse gegen Datenanker in derselben
  Zeile** — so fiel auf, dass Klasse 2 („konstante Preise") BACI (laufende) und BIP
  (konstante) im selben Topf führt. Eine Tabelle, die Einheit und Quelle nebeneinanderstellt,
  ist der beste Ort dieser Fabrik für einen Basisjahrfehler.
- 2026-09-02 — **Spalte „Modelleinheit" gegen die Quelleneinheit legen, Reihe für Reihe.**
  Ein *Einheitenbruch* (DEM→EUR) ist nicht die *Umrechnung*, und „auf 10.000 normiert" ist
  kein Faktor, sondern ein eigener Schritt (Basis? vor oder nach Rundung?). Und **zwei Reihen
  aus zwei Quellen nach der Umrechnung gegeneinander legen** — R2 (WDI) und R11 (WEO) landen
  beide über ×100 auf 1/10.000, obwohl ihre Zieleinheiten verschieden heissen. Die
  Einzelzeile bestätigt nur sich selbst.
- 2026-09-02 — **Für Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den
  Länderabruf.** `api.worldbank.org/v2/indicator/<code>?format=json` trägt `name` und
  `sourceNote` im Klartext („% of GDP", „constant 2015 US$"), der Länderabruf gar nicht.

### Zugänge und Abrufe

- 2026-09-02 — **`WebFetch` geht, `curl` nicht.** Weltbank:
  `/v2/sources/2/series/<code>/metadata` trägt `Source`, `/v2/indicator/<code>` dasselbe als
  `sourceOrganization`. Beim Nachprüfen **den jeweils anderen** Endpunkt nehmen als der
  Bauagent. Das Abrufmodell kürzt lange Feldwerte still — eine Kürzung ist kein Beleg für
  eine Abweichung; ein zweiter Abruf mit Bitte um den vollen Wert bringt ihn.
- 2026-09-02 — **IWF: `api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/<Fassung>/
  <LAND.INDIKATOR.A>` per WebFetch ist der einzige tragende Zugang** (`imf.org`,
  `data.imf.org` = 403; der Lizenz-Volltext ist damit **nicht** erreichbar, fünfmal
  gescheitert). „Land trägt die Reihe nicht" = `"values":[]`. Einzelne Jahreswerte liest das
  Abrufmodell unzuverlässig; **belastbar sind Randjahre und Wertezahl gegen Zeitraumlänge.**
  Je Land einzeln, und bei der Weltbank je Indikator einzeln — Mehrfachabrufe
  (`ind1;ind2;ind3?source=2`) laufen in den 60-Sekunden-Timeout.
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
- 2026-09-02 — **Das Archiv-Verschieben bei 12.000 Zeichen kann ich nicht ausführen**:
  `Edit` auf diese Datei ist mein einziges Schreibrecht, `notizen/archiv/` liegt ausserhalb.
  Ersatz: zusammenziehen statt verschieben. Reicht das nicht mehr, ist es ein Befund an den
  Projektmanager. **Zwei Läufe meiner Rolle schreiben hier gleichzeitig** — nach jedem `Edit`
  neu lesen, sonst schlägt der nächste fehl.

## Offene Faehrten

- 2026-09-02 — **Reihe 10: Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6 „Index gegen USD,
  **Startjahr** = 10.000"** — für die USA gleich, für DEU 17.341 gegen 10.000. Gehört dem
  Architekten. Ebenfalls offen: Rundung vor oder nach der Normierung (`rueckstand.md` 9).
- 2026-09-02 (0018) — **Die Zahl „drei Ämter" steht noch unter 2b/2c in
  `lizenzbefund-reihen.md` (Zeile 189–192), richtig sind sieben Stellen.** Befund 1 meines
  Prüfbefunds, an den Projektmanager. Wer `daten/reihen.toml` aus dieser Datei fortschreibt:
  vorher prüfen, sonst wandert die falsche Zahl mit.
- 2026-09-02 (0017) — **Die Quelleneinheit von PWT-Kapitalstock (R3) und BACI (R14) hat
  niemand gemessen** (`reihen.toml`: `art = "ungemessen"`), also ist `durchgriff` (R16) ein
  Quotient aus womöglich verschiedenen Einheiten. Konkreteste Fassung der Preisbasis-Fährte;
  **beim Paket, das die Aufbereitung baut: erste Stelle.**
- 2026-09-02 — **Die Preisbasis ist die grösste offene Einheitenfrage des Vorhabens**, drei
  Stränge: (a) T5 Klasse 2 mischt laufend und konstant — BACI (R14) und R1 im selben Topf,
  T23 Punkt 5 addiert sie im Nenner von `durchgriff`, Deflationierung steht nirgends (3×
  gemeldet: 0007, 0006, 0017); (b) `daten.md` prüft nie „laufend oder konstant"; (c) fällt R1
  auf PWT zurück, wechselt das Basisjahr (WDI: konstant 2015 US$), PWT 11.0 ungeprüft. Wer
  `durchgriff`, Jahrgangsbau oder Rückvergleich anfasst: erste Frage.
- 2026-09-02 — **Zwei Schranken für das Paket, das `parameter.toml` einliest:** Trägt T5
  Klasse 4 („0 bis 10.000") ihren Deckel auch für Regler wie Elastizitäten und
  Hebelobergrenze (Befund 3 zu 0009)? Und setzt die Prüfung für Klasse 3 eine Untergrenze —
  `hebelaufschlag` trägt `>= 0` ohne Herkunft, negativ kehrt Kanal 4 um (0009 R2).
- 2026-09-02 (0015 R2) — **`parameter.toml` Zeile 147 „Dieselbe Kennzeichnung wie im
  Adressverzeichnis" ist falsch geworden**, weil 0015 die Regel im Adressverzeichnis geändert
  hat. Befund 2 meines Prüfbefunds, gehört in ein 0009-Folgepaket. **Allgemein: Ändert ein
  Paket eine Definition, greppe nach Dateien, die sie *zitieren oder auf sie verweisen* — der
  Verweis wird falsch, ohne dass jemand die zweite Datei angefasst hat.**
- 2026-09-01 — **`gebiet.<G>.` gegen `land.<L>.` / `restwelt.` ist ungeklärt.** T46 schreibt
  `gebiet.<G>.basiswechsel`, kein anderes Dokument benutzt je ein `gebiet.`-Präfix. Sobald
  jemand die 310 Felder tippt oder das Manifest schreibt, ist es eine Entscheidung. **Die
  Fabrik zählt `restwelt.` inzwischen als Gebiet** (`adressen.md` zählt seine 22 Zeilen unter
  „Gebiete"), aber als eigenes Präfix, nicht als `<G>`-Wert — genau daran hing 0015.
