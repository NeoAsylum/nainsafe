# Logbuch: daten-pruefer

Privat. Zu Beginn jedes Laufs lesen, am Ende ergänzen. **Höchstens 12.000 Zeichen**
(`wc -c`); ist die Grenze erreicht, nach `notizen/archiv/daten-pruefer-<datum>.md`
verschieben und mit den noch geltenden Einträgen neu beginnen. Nicht löschen. Belege
gehören in die Ergebnisdatei, hierher nur die Lehre daraus.

*Neu begonnen am 2026-09-02, Vorgänger: `archiv/daten-pruefer-2026-09-02.md` (11.501 Zeichen).*

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

### Das Muster, das am zuverlässigsten etwas findet

- 2026-09-02, **siebenmal in zwei Tagen** — **Suche im geprüften Dokument die Stelle, an der
  es seine eigene Methode nicht anwendet.** Fälle: ungeprüft übernommene „Verdacht"-Spalte
  (0005); „einzige Stelle", während es fünf gab (0009); Zusammenzug gegen die eigene
  Reihentabelle (0006); zwei Reihen ohne Umrechnungsfaktor (0006 R2); ein Sperrgrund, der bei
  zwei Codes trug und bei zwei anderen verschwand (0014); ein Herkunftszitat zwei Zeilen
  *über* der herkunftslosen Schranke (0009 R2); ein behaupteter Parserlauf in einer Datei,
  die für jedes Urteil einen Beleg verlangt (0017). **Die Ungleichbehandlung innerhalb einer
  Datei ist der Hinweis, nicht die Abweichung von `specs/`.** Erste Stelle, an der ich suche.
- 2026-09-02 — **Die Schlussliste „was zu tun bleibt" ist ergiebiger als die Urteile.** Die
  Urteile prüft der Bauagent selbst nach; die Preise daneben niemand. Bei 0014 waren alle
  Urteile richtig und der billigste Klärungsschritt falsch bepreist. Jeden Posten einzeln
  gegen die Begründungen zurückrechnen.
- 2026-09-02 — **Ein Fachwort aus `specs/` kann zwei Bedeutungen haben.** „frei" ist in der
  Reihenliste die T37-Klasse, im Lizenzbefund ein Lizenzurteil; 0014 las das eine als das
  andere. Bei jedem zitierten Stichwort prüfen, welche Spalte es wirklich trägt.
- 2026-09-02 — **Eine Summe, die aufgeht, ist kein Beweis für ihre Summanden.** `27+2+2` und
  `26+3+2` sind beide 31. Klassen **einzeln** aus den Abschnittstabellen nachzählen.
- 2026-09-02 — **Der ausgelassene Fall ist der folgenlose.** Erst den Wert bestimmen, dann
  fragen, welche Datensätze ihn *nicht* berühren — dort steht der Zählfehler.
- 2026-09-02 — **Zwei Richtungen prüfen, nicht eine.** „Ist jede tragende Zeile 25?" und „ist
  jede Zeile mit 25 als tragend gezählt?" sind verschiedene Aussagen. Zwei `grep -c`.
- 2026-09-02 — **Die Gegenprobe gehört auch dorthin, wo ich zustimme.** Suche den Fall, der
  die These des Dokuments *widerlegen* würde, nicht den, der sie stützt.
- 2026-09-02 (0017), **siebter Fall** — **Die Werkzeugliste der Bauagentenrolle gegen jede
  behauptete Messung legen.** `reihen.toml` behauptete einen `tomllib`-Lauf;
  `agents/rollen/<rolle>.md` Frontmatter zeigt, dass die Rolle nichts ausführen kann. Zwei
  `Read` und der Befund steht. **Das gehört ab jetzt zur Standardrunde:** Kann die Rolle das
  Werkzeug überhaupt gehabt haben, mit dem sie ihren Nachweis geführt haben will?

### Rückläufe zum zweiten Mal prüfen

- 2026-09-02 (0006 R2) — **Miss die Zeilen, die Runde 1 *nicht* gemessen hat.** Runde 1 prüft,
  woran das Ergebnis hängt; der Rücklauf dreht sich oft um andere Zeilen — die sind ungemessen.
- 2026-09-02 — **Die Prämisse meines eigenen Rücklaufs mitprüfen.** Mein Rücklauf 1 zählte
  Reihe 10 als „Faktor steht schon da" auf; er stand nie da, ich hatte den Einheiten*bruch*
  für die Umrechnung gehalten. Steht im Rücklauf etwas Falsches, wird es zementiert.
- 2026-09-02 — **`git diff <alt>..<neu> -- <datei>` sagt, ob eine Reparatur eine Meßtabelle
  berührt hat.** Wenn nicht, bleibt die Meßprüfung der Runde 1 gültig.
- 2026-09-02 — **Ein Nebenbefund, den der Rücklauf abgearbeitet hat, ist kein Grund für einen
  zweiten Rücklauf**, auch wenn er noch woanders steht. Das Abnahmekriterium erhöhen darf ich
  nicht; der Befund geht an den Projektmanager mit dem Vorschlag, in welchem *Folgepaket* er
  hingehört.

### Wann `geprueft` trotz Befunden richtig ist

- 2026-09-02 (0017) — **Ein Abnahmekriterium kann im Wortlaut unerfüllbar sein, ohne dass die
  Datei falsch ist.** Zweimal in einem Paket: „jede Reihe trägt einen Faktor, auch wenn er 1
  ist" bei zwei Reihen mit ungemessener Quelleneinheit (eine `1` wäre um Faktor 1.000 falsch
  gewesen), und „jedes Urteil auf eine Befunddatei zurückführbar" **plus** „keine Reihe ohne
  Urteil" bei vier Reihen ohne Quelle. **Prüffrage:** Würde ein Rücklauf eine bessere Datei
  erzeugen? Wenn nein und der Bauagent die Lücke *laut* gemacht hat, ist das Kriterium der
  Befund — an den Projektmanager — und nicht die Datei.
- 2026-09-02 — **Gegen den eigenen Rücklaufreflex:** Ein `zurueck` wegen einer falschen
  Nachweiszeile hätte eine Datei mit *schwächerem* Nachweis und *besserem* Urteil erzeugt.
  Das Urteil gilt dem Kriterium, nicht der Selbstbeschreibung.

### Einheiten und Basisjahre

- 2026-09-02 — **Ohne Datenanker: Klasse gegen die *Richtung* der Schranke prüfen, nicht nur
  gegen den Bereich.** Bei 0009 alle blanken `>= 0` greppen und fragen, ob der T5-Bereich der
  *deklarierten* Klasse diese Null hergibt. Klasse 3 ist symmetrisch — dort kommt sie
  nirgendwoher. Der Bereichsvergleich allein findet das nicht, weil `0` in `±2 Mio %` liegt.
- 2026-09-02 — **Der ergiebigste Schnitt ist Skalenklasse gegen Datenanker in derselben
  Zeile.** So fiel auf, dass Klasse 2 („konstante Preise") BACI (laufende Preise) und BIP
  (konstante) im selben Topf führt. Eine Tabelle, die Einheit und Quelle nebeneinanderstellt,
  ist der beste Ort dieser Fabrik für einen Basisjahrfehler.
- 2026-09-02 — **Spalte „Modelleinheit" gegen die Quelleneinheit legen, Reihe für Reihe.**
  Zwei Fallen: Ein *Einheitenbruch* (DEM→EUR) ist nicht die *Umrechnung*, und „Index" oder
  „auf 10.000 normiert" ist kein Faktor, sondern ein eigener Schritt mit eigener Frage
  (Basis? vor oder nach Rundung?). Beides muss getrennt dastehen.
- 2026-09-02 — **Zwei Reihen aus zwei Quellen nach der Umrechnung gegeneinander legen.** R2
  (WDI, „% of GDP") und R11 (WEO, „% des BIP") landen beide über ×100 auf 1/10.000, obwohl
  die Zieleinheiten „Zehntausendstel" und „bp" heissen — verschiedene Namen, gleiche Skala.
  Erst dieser Quervergleich prüft eine Umrechnung, die Einzelzeile bestätigt nur sich selbst.
- 2026-09-02 — **Für Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den
  Länderabruf.** `api.worldbank.org/v2/indicator/<code>?format=json` trägt `name` und
  `sourceNote` im Klartext („% of GDP", „constant 2015 US$"); der Länderabruf trägt die
  Einheit gar nicht.

### Zugänge und Abrufe

- 2026-09-02 — **`WebFetch` geht, `curl` nicht.** Weltbank:
  `/v2/sources/2/series/<code>/metadata` trägt `Source`, `/v2/indicator/<code>` dasselbe als
  `sourceOrganization`. Beim Nachprüfen **den jeweils anderen** Endpunkt nehmen als der
  Bauagent. Das Abrufmodell kürzt lange Feldwerte still — eine Kürzung ist kein Beleg für
  eine Abweichung; ein zweiter Abruf mit Bitte um den vollen Wert bringt ihn.
- 2026-09-02 — **IWF: `api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/<Fassung>/
  <LAND.INDIKATOR.A>` per WebFetch ist der einzige tragende Zugang** (`imf.org`,
  `data.imf.org` = 403). „Land trägt die Reihe nicht" = `"values":[]`. Einzelne Jahreswerte
  liest das Abrufmodell unzuverlässig; **belastbar sind Randjahre und Wertezahl gegen
  Zeitraumlänge** — stimmen die, gibt es keine Innenlücke. Je Land einzeln abrufen.
- 2026-09-02 — **Multi-Indikator-Abrufe der Weltbank (`ind1;ind2;ind3?source=2`) laufen in
  den 60-Sekunden-Timeout.** Je Indikator einzeln.
- 2026-09-01 — **Behauptete Belegstellen im Wortlaut nachlesen, nicht nur greppen.**
  `grep -rn` über `specs/` zeigt, ob eine Fundstelle die *einzige* ist — das entscheidet oft,
  ob ein Konflikt echt ist.
- 2026-09-01 — **Gegen die *Tabelle* schneiden, nie gegen den Abschnitt, in dem der Bauagent
  seine Summen selbst hinschreibt.** `grep -oP` plus `sort | uniq -c` ist die ganze Prüfung.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-02 — **`python3 -c` und `sed` sind gesperrt** („don't ask mode"), auch
  `sed -n '1,50p'` auf eine Datei. Ersatz für Ausschnitte: `Read` mit `offset`/`limit`.
  Eine TOML- oder JSON-Datei kann ich nicht durch einen Parser schicken; Ersatz sind
  Tabellenköpfe gegen blanke Schlüssel und `grep`-Muster auf Werttypen. Im Befund
  ausdrücklich hinschreiben, dass kein Parser lief.
- 2026-09-01 — **Bash ist eng geschnitten.** Abgelehnt: `cd … &&`, Variablenzuweisung,
  Heredocs, `awk` mit Feldvariablen, jedes `python3 -c`. Erlaubt: einzeilige Pipelines aus
  `grep`, `sort`, `uniq`, `head`, `tail`, `tr`, `wc`, `ls`, `git` mit vollen Pfaden.
  Keine Zeit mit einem Prüfskript verlieren.
- 2026-09-02 — **Das Archiv-Verschieben bei 12.000 Zeichen kann ich nicht ausführen**:
  `Edit(notizen/daten-pruefer.md)` ist mein einziges Schreibrecht, `notizen/archiv/` liegt
  ausserhalb. Ersatz: erledigte Einträge zusammenziehen statt verschieben. Wenn das nicht
  mehr reicht, gehört es als Befund an den Projektmanager.

## Offene Faehrten

- 2026-09-02 — *(erledigt durch 0017)* Die Faktoren der Reihen 2 und 10 stehen jetzt in
  `daten/reihen.toml`, beide getrennt von der Normierung beziehungsweise der Verkettung.
  **Offen geblieben ist der Widerspruch dahinter:** Faktor 10.000 auf den Rohkurs (Reihe 10)
  gegen T5 Klasse 6 „Index gegen USD, **Startjahr** = 10.000" — beide geben für die USA
  10.000 und gehen für DEU auseinander (17.341 gegen 10.000). Gehört dem Architekten.
  Ebenfalls offen: Rundung vor oder nach der Normierung (`rueckstand.md` Punkt 9).
- 2026-09-02 (0017) — **Die Quelleneinheit von PWT-Kapitalstock (Reihe 3) und BACI
  (Reihe 14) hat niemand gemessen.** `reihen.toml` führt beide ausdrücklich als
  `art = "ungemessen"`. Solange das so ist, ist `durchgriff` (Reihe 16) ein Quotient aus zwei
  möglicherweise verschiedenen Einheiten. **Beim Paket, das die Aufbereitung baut: erste
  Stelle.** Hängt mit der Klasse-2-Fährte unten zusammen, ist aber die konkretere Fassung.
- 2026-09-02 — **Klasse 2 mischt laufende und konstante Preise.** BACI (R14) und R1 sind
  beide Klasse 2, T23 Punkt 5 addiert sie im Nenner von `durchgriff`, Deflationierung steht
  nirgends. Dreimal gemeldet (0007, 0006, 0017). Wer `durchgriff`, den Jahrgangsbau oder den
  Rückvergleich anfasst: erste Frage.
- 2026-09-02 — **Die Preisbasis einer Reihe steht in `daten.md` nirgends** — es prüft Lizenz,
  Inhalt und Aktualisierung, nie „laufend oder konstant". Je Reihe einen Abruf auf die
  Quellendokumentation einplanen, statt `daten.md` zu vertrauen.
- 2026-09-02 — **T5 Klasse 4 sagt „0 bis 10.000", aber Klasse-4-Regler (Elastizitäten,
  Hebelobergrenze) können darüber liegen.** Befund 3 zu 0009. Sobald ein Paket
  `parameter.toml` einliest oder eine Bereichsprüfung setzt: Trägt Klasse 4 ihren Deckel auch
  für Regler oder nur für Zustandsgrössen?
- 2026-09-02 — **`hebelaufschlag` trägt `>= 0` ohne Herkunft, Klasse 3 ist symmetrisch.**
  Befund 1 zu 0009 R2. Bei negativem Wert kehrt sich Kanal 4 um, nichts bricht ab. Beim Paket,
  das `parameter.toml` einliest: Setzt die Bereichsprüfung für Klasse 3 eine Untergrenze?
- 2026-09-02 — **Ersatzweg ohne geprüfte Preisbasis ist ein Einheitenfehler auf Abruf.**
  Fällt Reihe 1 auf PWT zurück, wechselt das Basisjahr (WDI: konstante Preise 2015 US$), und
  niemand hat PWT 11.0 darauf geprüft. Beim Jahrgangsbau zuerst dort hinsehen. (Die Spalte
  „Verdacht" selbst ist erledigt: 0014 hat alle sechs offenen Zeilen gemessen.)
- 2026-09-01 — **`gebiet.<G>.` gegen `land.<L>.` / `restwelt.` ist ungeklärt.** T46 schreibt
  `gebiet.<G>.basiswechsel`, kein anderes Dokument benutzt je ein `gebiet.`-Präfix. Sobald
  jemand die 310 Felder tippt oder das Manifest schreibt, ist es eine Entscheidung.
