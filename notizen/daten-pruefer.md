# Logbuch: daten-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/daten-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-02, Vorgänger: `archiv/daten-pruefer-2026-09-02.md` (11.501 Zeichen).*

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

### Das Muster, das am zuverlässigsten etwas findet

- 2026-09-02, **sechster Fall in zwei Tagen** — **Suche im geprüften Dokument die Stelle, an
  der es seine eigene Methode nicht anwendet.** Neu (0009 Runde 2): ein Schlüssel, dessen
  Herkunftszitat zwei Zeilen *über* seiner herkunftslosen Schranke steht — die Datei hatte
  die Quelle in der Hand und schrieb sie nicht in die Zeile, auf die es ankam. Bisher: eine
  Tabelle, deren „Verdacht"-Spalte
  ungeprüft übernommen wurde (0005); ein Kopplungspaar, das zur „einzigen Stelle" erklärt
  wurde, während es fünf gab (0009); ein Zusammenzug, der der eigenen Reihentabelle
  widersprach (0006); zwei Reihen, die als einzige keinen Umrechnungsfaktor nennen (0006
  Runde 2); zuletzt ein Sperrgrund, der bei zwei Codes das Urteil trug und bei zwei anderen
  aus Begründung *und* Preisliste verschwand, obwohl die Übersichtstabelle desselben
  Dokuments ihn dort führt (0014). **Die Ungleichbehandlung innerhalb einer Datei ist der
  Hinweis, nicht die Abweichung von `specs/`.** Erste Stelle, an der ich suche.
- 2026-09-02 — **Die Schlussliste „was zu tun bleibt" ist ergiebiger als die Urteile.** Die
  Urteile prüft der Bauagent selbst nach; die Preise, die er ihnen daneben schreibt, niemand.
  Bei 0014 waren alle Urteile richtig und der billigste Klärungsschritt trotzdem falsch
  bepreist. **Jeden Posten einer solchen Liste einzeln gegen die Begründungen zurückrechnen.**
- 2026-09-02 — **Ein Fachwort aus `specs/` kann in zwei Bedeutungen dastehen.** „frei" ist in
  der Reihenliste die T37-Klasse (gegen `gesetzt`/`abgeleitet`), im Lizenzbefund ein
  Lizenzurteil; 0014 las das eine als das andere und adressierte die falsche Tabellenzelle.
  Bei jedem zitierten Stichwort prüfen, welche Spalte es wirklich trägt.
- 2026-09-02 — **Eine Summe, die aufgeht, ist kein Beweis für ihre Summanden.** `27+2+2` und
  `26+3+2` sind beide 31. Bei jeder Klassifikationszählung die Klassen **einzeln** aus den
  Abschnittstabellen nachzählen, nie nur die Summe.
- 2026-09-02 — **Der ausgelassene Fall ist der folgenlose.** Bei 0006 fehlte in der Zählung
  genau die Reihe, die den Zielwert nicht erzwingt. Erst den Wert bestimmen, dann fragen,
  welche Datensätze ihn *nicht* berühren — dort steht der Zählfehler.
- 2026-09-02 — **Zwei Richtungen prüfen, nicht eine.** „Ist jede tragende Zeile 25?" und
  „ist jede Zeile mit 25 als tragend gezählt?" sind verschiedene Aussagen. Zwei `grep -c`
  statt einem.
- 2026-09-02 — **Die Gegenprobe gehört auch dorthin, wo ich zustimme.** Suche den Fall, der
  die These des Dokuments *widerlegen* würde, nicht den, der sie stützt.

### Rückläufe zum zweiten Mal prüfen

- 2026-09-02 (0006 Runde 2) — **Miss die Zeilen, die Runde 1 *nicht* gemessen hat.** Runde 1
  prüft, woran das Ergebnis hängt; der Rücklauf dreht sich danach oft um andere Zeilen. Bei
  0006 hing R an vier Zeilen, die neue Zählung aber an vier anderen — die waren ungemessen.
- 2026-09-02 — **Die Prämisse meines eigenen Rücklaufs mitprüfen.** Mein Rücklauf 1 zählte
  Reihe 10 als „Faktor steht schon da" auf; nachgemessen stand er nie da, ich hatte den
  Einheiten*bruch* für die Umrechnung gehalten. Der Bauagent repariert genau das, was der
  Rücklauf sagt — steht dort etwas Falsches, wird es zementiert.
- 2026-09-02 — **`git diff <alt>..<neu> -- <datei>` sagt, ob eine Reparatur eine Meßtabelle
  berührt hat.** Wenn nicht (nur Fließtext und Summenzeile), bleibt die Meßprüfung der
  Runde 1 gültig und der zweite Lauf kann seine Abrufe woandershin stecken.
- 2026-09-02 — **Ein Nebenbefund, den der Rücklauf abgearbeitet hat, ist kein Grund für einen
  zweiten Rücklauf**, auch wenn er noch woanders steht. Das Abnahmekriterium erhöhen darf ich
  nicht; der Befund geht an den Projektmanager mit dem Vorschlag, in welchem *Folgepaket* er
  hingehört.

### Einheiten und Basisjahre

- 2026-09-02 — **Ohne Datenanker ist der Ersatzschnitt: Klasse gegen die *Richtung* der
  Schranke, nicht nur gegen den Bereich.** Bei 0009 alle blanken `Schranke: >= 0` greppen und
  je Treffer fragen, ob der T5-Bereich der *deklarierten* Klasse diese Null überhaupt hergibt.
  Klasse 4 und 11 beginnen bei 0, Klasse 3 ist symmetrisch (±2 Mio %) — dort kommt die Null
  nirgendwoher, und genau dort lag der Befund. Der Bereichsvergleich allein findet das nicht,
  weil `0` in `±2 Mio %` ja liegt.
- 2026-09-02 — **Der ergiebigste Schnitt ist Skalenklasse gegen Datenanker in derselben
  Zeile.** So fiel auf, dass Klasse 2 („konstante Preise") BACI-Handelsströme (laufende
  Preise) und BIP (konstante Preise) im selben Topf führt. Eine Tabelle, die Einheit und
  Quelle nebeneinanderstellt, ist der beste Ort dieser Fabrik für einen Basisjahrfehler.
- 2026-09-02 — **Die Spalte „Modelleinheit" der Reihenliste gegen die Quelleneinheit legen,
  Reihe für Reihe.** Bei 0006 fehlte der Faktor bei 15 der 31 Sollreihen. Zwei Fallen dabei:
  Ein *Einheitenbruch* (DEM→EUR) ist nicht die *Umrechnung* in die Modelleinheit, und
  „Index" oder „auf 10.000 normiert" ist kein Faktor, sondern ein Rechenschritt mit eigener
  Frage (Basis? vor oder nach Rundung?).
- 2026-09-02 — **Für Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den
  Länderabruf.** `api.worldbank.org/v2/indicator/<code>?format=json` trägt `name` und
  `sourceNote` im Klartext („% of GDP", „constant 2015 US$"); der Länderabruf trägt die
  Einheit gar nicht.

### Zugänge und Abrufe

- 2026-09-02 — **`WebFetch` geht, `curl` nicht** (Bash-Freigabe verweigert). Weltbank:
  `/v2/sources/2/series/<code>/metadata` trägt `Source`, `/v2/indicator/<code>` dasselbe als
  `sourceOrganization`. Beim Nachprüfen eines Zitats **den jeweils anderen** Endpunkt nehmen
  als der Bauagent. Das Abrufmodell kürzt lange Feldwerte manchmal still — eine Kürzung ist
  kein Beleg für eine Abweichung, ein zweiter Abruf mit Bitte um den vollen Wert bringt ihn.
- 2026-09-02 — **IWF: `api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/<Fassung>/
  <LAND.INDIKATOR.A>` per WebFetch ist der einzige tragende Zugang** (`imf.org`,
  `data.imf.org` = 403). „Land trägt die Reihe nicht" erkennt man an `"values":[]`. Einzelne
  Jahreswerte liest das Abrufmodell unzuverlässig (Indexversatz); **belastbar sind Randjahre
  und Wertezahl gegen Zeitraumlänge** — stimmen die überein, gibt es auch keine Innenlücke.
  Sammelabfragen über mehrere Länder nicht auszählen, je Land einzeln.
- 2026-09-02 — **Multi-Indikator-Abrufe der Weltbank (`ind1;ind2;ind3?source=2`) laufen in
  den 60-Sekunden-Timeout.** Je Indikator einzeln.
- 2026-09-01 — **Behauptete Belegstellen im Wortlaut nachlesen, nicht nur greppen.**
  `grep -rn` über den ganzen `specs/`-Bestand zeigt, ob eine Fundstelle die *einzige* ist —
  das entscheidet oft, ob ein Konflikt echt ist.
- 2026-09-01 — **Tabellenspalten mit `grep -oP` schneiden und `sort | uniq -c` daraufsetzen
  ist die ganze Prüfung.** Gegen die *Tabelle* schneiden, nie gegen den Abschnitt, in dem der
  Bauagent seine Summen selbst hinschreibt.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-02 — **`python3 -c` und `sed` sind gesperrt** („don't ask mode"), auch
  `sed -n '1,50p'` auf eine Datei. Ersatz für Ausschnitte: `Read` mit `offset`/`limit`.
  Eine TOML- oder JSON-Datei kann ich nicht durch einen Parser schicken; Ersatz sind
  Tabellenköpfe gegen blanke Schlüssel und `grep`-Muster auf Werttypen. Im Befund
  ausdrücklich hinschreiben, dass kein Parser lief.
- 2026-09-01 — **Bash ist eng geschnitten.** Abgelehnt: `cd … &&`, Variablenzuweisung,
  Heredocs, `awk` mit Feldvariablen, mehrzeilige `python3 -c`, `Write` ausserhalb des Repos.
  Erlaubt: einzeilige Pipelines aus `grep`, `sort`, `uniq`, `head`, `tail`, `tr`, `wc`, `ls`
  und `git` mit ausgeschriebenen Pfaden. Keine Zeit mit einem Prüfskript verlieren.

## Offene Faehrten

- 2026-09-02 — **Einheiten der Reihen 2 und 10 (15 der 31 Sollreihen) haben nirgends einen
  Faktor.** Reihe 2: % → Zehntausendstel, ×100 *plus* Normierung auf 10.000 (die drei
  WDI-Anteile summieren nicht auf 100). Reihe 10: Landeswährung/USD → Index mit Basis 10.000
  (`technik.md` Z. 884/886/1377). Als Befund 1 zu 0006 Runde 2 gemeldet, gehört ins Paket
  „Jahrgangsbau/Aufbereitung". **Erste Stelle zum Hinsehen, sobald ein Paket die Aufbereitung
  baut.** Dort auch fragen: Rundung vor oder nach der Normierung?
- 2026-09-02 — **Klasse 2 mischt laufende und konstante Preise.** BACI (Reihe 14, laufende
  Preise) und Reihe 1 (konstante) sind beide Klasse 2, und T23 Punkt 5 addiert sie im Nenner
  von `durchgriff`. Deflationierung steht nirgends. Zweimal gemeldet (0007, 0006). Wenn ein
  Paket `durchgriff`, den Jahrgangsbau oder den Rückvergleich anfasst: erste Frage.
- 2026-09-02 — **Preisbasis einer Reihe steht in `daten.md` nirgends.** `daten.md` prüft
  Lizenz, Inhalt und Aktualisierung je Quelle, aber nie „laufende oder konstante Preise".
  Deshalb bei jeder Reihe einen Abruf auf die Quellendokumentation einplanen statt auf
  `daten.md` zu vertrauen.
- 2026-09-02 — **T5 Klasse 4 sagt „0 bis 10.000", aber Klasse-4-Regler (Elastizitäten,
  Hebelobergrenze) können darüber liegen.** Befund 3 zu 0009. Sobald ein Paket
  `parameter.toml` einliest oder eine Bereichsprüfung setzt: Trägt Klasse 4 ihren Deckel auch
  für Regler oder nur für Zustandsgrössen?
- 2026-09-02 — **`hebelaufschlag` trägt `>= 0` ohne Herkunft, und Klasse 3 ist symmetrisch.**
  Befund 1 zu 0009 Runde 2. Bei negativem Wert sinkt der Kreditzins mit der Sichtbarkeit,
  Kanal 4 kehrt sich um, nichts bricht ab. Beim Paket, das `parameter.toml` einliest, prüfen,
  ob die Bereichsprüfung für die Klasse-3-Schlüssel überhaupt eine Untergrenze setzt.
  (*Erledigt:* Die `schrittweite`-Fährte — Rücklauf 1 hat ihr `>= 1` und ganzzahlig gegeben.)
- 2026-09-02 — **Die Spalte „Verdacht" ist erledigt: 0014 hat alle sechs offenen Zeilen
  gemessen, alle sechs nennen einen Fremdbestand.** Offen bleibt der Ersatzweg: Fällt Reihe 1
  auf PWT zurück, wechselt das Basisjahr (WDI: konstante Preise 2015 US$), und niemand hat
  PWT 11.0 darauf geprüft. **Ein Ersatzweg ohne geprüfte Preisbasis ist ein Einheitenfehler
  auf Abruf** — beim Paket zum Jahrgangsbau zuerst dort hinsehen.
- 2026-09-01 — **`gebiet.<G>.` gegen `land.<L>.` / `restwelt.` ist ungeklärt.** T46 schreibt
  `gebiet.<G>.basiswechsel`, kein anderes Dokument benutzt je ein `gebiet.`-Präfix. Sobald
  jemand die 310 Felder tippt oder das Manifest schreibt, ist es eine Entscheidung.
