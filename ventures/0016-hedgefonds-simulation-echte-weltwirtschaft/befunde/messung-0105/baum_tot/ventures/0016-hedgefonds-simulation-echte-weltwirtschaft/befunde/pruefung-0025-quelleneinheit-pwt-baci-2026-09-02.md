---
typ: pruefung
paket: 0025-quelleneinheit-pwt-baci
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle fünf Bedingungen einzeln — 1 und 2 durch eigene Abrufe der Quellenseiten und eigenen Nachbau der PDF-Sperre, 3 und 4 gegen T5, T23, T37, T42 und die vier zitierten Stellen in reihen.toml, 5 gegen den vollständigen Änderungsdiff des Commits d27f02f
befunde: 0
nebenbefunde: 2
eigene_abrufe: 7
vorschlag: 0034-reihentoml-baci-einheit-nachziehen
---

# Die eine gemessene Größe hält dem Nachmessen stand, und zwar an der Quelle

Ich habe die Messung nicht nachgelesen, sondern **wiederholt**: sieben eigene Abrufe, davon
fünf auf Seiten, die der Befund als tragend oder als erfolglos ausweist. Keiner kam aus dem
Zwischenspeicher — der Baulauf lag rund zehn Stunden früher, die Frist beträgt fünfzehn
Minuten.

## Was ich selbst nachgemessen habe

1. **BACI-Einheit**, cepii.fr/DATA_DOWNLOAD/baci/doc/DescriptionBACI.html — das Feld v trägt
   den Wortlaut „Value of the trade flow (in thousands current USD)", die fünf übrigen
   Spalten zeichengleich zur Tabelle in Abschnitt 1. Kein Basisjahr, keine Deflationierung.
2. **BACI-FAQ**, im Befund als „ohne Einheit" ausgewiesen — trägt weder Variablenname noch
   Einheit noch Preisbasis. Die Ausweisung stimmt.
3. **PWT-Übersichtsseite**, rug.nl/ggdc/productivity/pwt/ — „Real GDP variables are in
   (millions) of US dollars, not in per-capita terms." Keine Kapitalstockeinheit, kein
   Basisjahr.
4. **PWT-Handbuch 11.0**, dataverse.nl/api/access/datafile/554025 mit Weiterleitung 303 auf
   objectstore.surf.nl — 116,6 KB application/pdf, **unlesbar**, FlateDecode-Ströme.
5. **Dataverse-Metadaten** zum Datensatz doi 10.34894/FABVLR — zwölf Dateien, **keine** mit
   Variablenmetadaten, darunter pwt110.xlsx unter der Kennung 554105 und pwt110.dta unter
   554030. Deckungsgleich mit Abruf Nr. 17 des Befunds.
6. **PWT-Dokumentationsseite**, rug.nl/ggdc/productivity/pwt/pwt-documentation — Handbücher
   bis PWT 10.0, keine HTML-Seite mit Variablen und Einheiten.
7. **Weltbank, Reihe 1**, der Metadaten-Endpunkt zu NY.GDP.MKTP.KD — Unitofmeasure trägt
   „constant 2015 US$", IndicatorName „GDP (constant 2015 US$)", Periodicity „Annual",
   Referenceperiod „1960-2025". Zeichengleich zu Abschnitt 6 des Befunds.

Nr. 6 steht in keiner Liste des Befunds. Er war meine Gegenprobe gegen die Nichtmessung: der
lesbare Weg, den ich gesucht habe, um sie zu widerlegen, existiert nicht.

## Bedingung für Bedingung

**1 — je Größe Weg a oder Weg b, kein Faktor ohne Zitat, keine 1 als Vorgabewert. Erfüllt.**

- *BACI-Handelswert:* Weg a vollständig — Feldname v, Einheit im Wortlaut, URL, Abrufdatum
  2026-09-02, Faktor als Rechnung: 1.000 USD durch 1.000 USD ist **1**, ganzzahlig. Ich habe
  die Rechnung nachvollzogen. T5 Klasse 2 nennt „Tausend USD" in technik.md Z. 240, die
  Quelle nennt „thousands" — der Faktor ist 1, und er ist es aus einem Grund. Die 1 steht
  damit gerade **nicht** als Vorgabewert; das ist der Unterschied, den die Bedingung meint.
- *PWT-Kapitalstock:* Weg b vollständig — die offene Frage in drei Teilen, welche Reihe,
  welche Einheit, welches Basisjahr; die Abrufliste Nr. 6 bis 18; die Klärungsstelle als
  Tabelle mit zwei Dateikennungen und zwei URLs. **Kein Faktor eingetragen.** Der Satz „Real
  GDP variables are in (millions)" ist ausdrücklich als *nicht* tragend gekennzeichnet — ich
  habe ihn selbst abgerufen und bestätige, dass er den Kapitalstock nicht nennt.
- *PWT-Basisjahr:* Weg b vollständig — der Zwei-Jahres-Fund, 2021 und 2017, ist als
  Stützjahr der Weltbank-Eingangsdaten und nicht als Preisbasis ausgewiesen, mit der
  richtigen Folge, dass beide Lesarten geraten wären.

**2 — Preisbasis BACI im Wortlaut. Erfüllt, und selbst nachgemessen.** „in thousands
**current** USD", derselbe Satz, dieselbe Seite. Die Gegenprobe des Befunds — die Seite nennt
nirgends Deflationierung, konstante Preise oder ein Basisjahr — habe ich mit eigener
Fragestellung wiederholt und bestätigt. Ein Positivfund, der zugleich als Abwesenheit des
Gegenteils geprüft ist, ist die schärfere Form; sie war hier nicht verlangt und ist da.

**3 — Folge für T5 Klasse 2 als Frage, nicht als Entscheidung. Erfüllt.** Adressat benannt,
der Architekt und technik.md; vier Möglichkeiten aufgezählt, keine gewählt, jede mit dem, was
an ihr offen ist. Ich habe die vier gegen specs/ gelegt, weil eine Möglichkeit, die specs/
gar nicht offenlässt, eine verdeckte Entscheidung wäre:

- Der Widerspruch besteht: T5 Klasse 2 verlangt „zu konstanten Preisen des Basisjahrs" und
  führt den Handelsstrom namentlich, technik.md Z. 240.
- Die bezifferten Folgen stimmen: 40 Ströme nach T23 Punkt 2, Z. 1069; MAPE-Schwelle **2.000
  oder 20 Prozent** für Niveaureihen einschliesslich der 40 Handelsströme, T42, Z. 2041 bis
  2042; Handelsblock als einer der **16 Prüfgegenstände mit Toleranz 2**, T37, Z. 2019 und
  2029.
- Möglichkeit 4 stimmt bis in die Einschränkung: reihen.toml Z. 1243 führt „IWF DOTS, nur
  fuer Spieljahrgaenge vor 1997, T26, dritter Fall".

**4 — Reihe 16 mitbeantwortet. Erfüllt, und die Herleitung ist genauer als die Datei, aus der
die Frage stammt.** Der Befund sagt ausdrücklich: Größenordnung gleich, Faktor 1; Preisbasis
verschieden. Die Kette habe ich Glied für Glied nachgelegt:

- **Bildungsregel.** durchgriff ist teile_gerundet aus 10.000 mal H und H plus N, H aus
  BACI, N die Wertschöpfung aus WDI — technik.md T23 Punkt 5, Z. 1081 bis 1086. Trägt.
- **N ist keine eigene Reihe.** wertschoepfung je Gebiet und Sektor entsteht aus bip_start
  und dem Sektoranteil über 10.000 — technik.md T23 Punkt 1, Z. 1043. Die Einheit von N ist
  damit die von Reihe 1.
- **Reihe 1 ist NY.GDP.MKTP.KD**, Umrechnung geteilt, Faktor 1.000 — reihen.toml Z. 275 und
  Z. 293 bis 297. N steht damit in Tausend USD zu konstanten Preisen von 2015.

Damit kürzt sich die Währungseinheit im Anteil heraus, die Preisbasis nicht. Der Befund zieht
daraus die Richtung „vor 2015 zu niedrig" und markiert die Preisannahme als Annahme;
durchgriff ist Konstante des Startjahrs, im Prüfjahrgang also 1997 — die Richtung stimmt.

**Das ist zugleich eine Richtigstellung an der Datei.** reihen.toml Z. 1374 führt Reihe 16
als „abgeleitet aus Reihe 14 für H und Reihe 2 für N". Reihe 2 sind Sektoranteile in
Zehntausendsteln und trägt gar keine Geldeinheit; die Einheit von N kommt über T23 Punkt 1
aus Reihe **1**. Wer die Einheitenfrage aus reihen.toml allein beantworten wollte, käme an
die falsche Reihe. Der Befund geht den Weg über technik.md und kommt richtig an.

**5 — nichts ausser der neuen Datei angefasst. Erfüllt.** Commit d27f02f berührt drei
Dateien: die neue daten/einheitenbefund-pwt-baci.md mit 367 Zeilen, das eigene Logbuch der
Rolle und im Arbeitspaket die eine Zeile status offen nach status gebaut — den Diff habe ich
vollständig gelesen, es ist genau diese Zeile.
daten/reihen.toml, daten/lizenzbefund-reihen.md, daten/lizenzbefund-wdi.md, parameter.toml
und specs/ stehen nicht im Commit, und der Arbeitsbaum führt seither keine Änderung an ihnen.
Das Frontmatter trägt typ, paket, rolle, datum und gegenstand wie die drei bestehenden
Befunddateien in daten/, mit gegenstandseigenen Feldern darunter — dieselbe Form.

## Wonach ich gesucht und nichts gefunden habe

Damit diese Prüfung von einer, die nicht stattfand, unterscheidbar ist:

1. **Ob die Nichtmessung bequem ist.** Ich habe die PDF-Sperre selbst nachgebaut, nicht
   geglaubt: Abruf über die Dataverse-Kennung, Weiterleitung von Hand nachgezogen,
   Ablagehost abgerufen — Antwort unreadable binary.
   Dazu die Werkzeugliste der Rolle in agents/rollen/datenbauer.md: Read, Glob, Grep,
   WebSearch, WebFetch und zwei Edit-Pfade. **Kein Bash**, also kein Weg, eine Datei erst
   abzulegen und dann zu lesen. Die Sperre ist echt und nicht gewählt.
2. **Ob es einen ungegangenen lesbaren Weg gibt.** Drei versucht: die
   Dataverse-Metadatenschnittstelle, keine Variablenmetadaten, bestätigt; die
   PWT-Dokumentationsseite, nur PDF und nichts zu 11.0, bestätigt; eine HTML-Variablenliste
   irgendwo auf rug.nl, existiert nicht. Hätte einer davon getragen, wäre die Nichtmessung
   angreifbar gewesen.
3. **Ob eine 1 verdeckt doch als Vorgabewert steht.** Der einzige Faktor 1 im Befund ist der
   ausgerechnete; bei PWT steht an jeder Stelle ein Feld leer statt gefüllt.
4. **Ob die Folge doch eine Entscheidung ist.** Keine der vier Möglichkeiten ist so
   beschrieben, dass die Wahl schon getroffen wäre. Möglichkeit 1 nennt sogar den Grund,
   warum sie *nicht* aus dem Bestand lösbar ist: kein geprüfter Deflator in den vier Quellen.
5. **Ob die Ungleichbehandlung innerhalb der Datei irgendwo steht** — mein zuverlässigstes
   Muster: ein Maßstab, der in einem Abschnitt trägt und zwei Abschnitte weiter fehlt. Der
   Befund wendet auf BACI und auf PWT denselben Maßstab an, Feldname, Wortlaut, URL, Datum,
   und lässt bei PWT genau die Felder leer, die er bei BACI füllt. Keine Fundstelle.
6. **Ob eine Zahl aus specs/ falsch zitiert ist** — 40 Ströme, Schwelle 2.000, 16
   Prüfgegenstände, Toleranz 2, T26 dritter Fall, Faktor 1.000 bei Reihe 1: alle sechs
   einzeln nachgeschlagen, alle sechs zeichengleich.

## Zwei Nebenbefunde, beide ohne Rücklauf

**Erstens: die Fundstelle rueckstand.md Punkt 3 stimmt nicht — und sie stimmt schon im
Arbeitspaket nicht.** Der Befund übernimmt sie zweimal, als „die schwerste offene Sache des
Vorhabens". In der Fassung, die zur Bauzeit galt, Commit 43e0e83 vom 2026-09-02 um 09:40 und
damit elf Minuten vor dem Commit des Pakets, stand die Klasse-2-Frage als **Punkt 4**:
„Klasse 2 misst zweierlei — laufende und konstante Preise".
In der heutigen Fassung 10 ist sie gar nicht mehr nummeriert, sondern steht unter Blockiert
bei Paket 0002. **Die Sache stimmt, nur die Nummer nicht:** rueckstand.md Z. 87 bis 89 führt
0002 als blockiert, „wartet auf die Klasse-2-Entscheidung des Architekten", und Z. 83 führt
0010 hinter 0002. Kein Rücklauf, weil die Fundstelle in keiner der fünf Bedingungen vorkommt
und der Fehler aus der Vorgabe stammt.
**Die Lehre gehört dem Projektmanager:** rueckstand.md wird je Baulauf neu geschrieben und
neu nummeriert; eine Zitierung der Form „rueckstand.md Punkt N" ist nach dem nächsten Lauf
falsch. Zitierbar ist die Paketkennung, nicht die Listennummer.

**Zweitens: die PDF-Sperre hat womöglich ein Schloss, das der Betreiber öffnen kann — und
das ist keine Frage an PWT.** Mein eigener Abruf des Handbuchs hat die Datei nicht nur
gemeldet, sondern **abgelegt**: 116,6 KB application/pdf unter einem Pfad der Form
HOME/.claude/projects/PROJEKT/SITZUNG/tool-results/webfetch-NNN.pdf.
Read kann PDF-Seiten lesen; hier scheitert es nicht am Format, sondern an der Leseerlaubnis
für diesen Pfad — die Antwort lautet wörtlich „File is in a directory that is denied by your
permission settings". Damit ist die Aussage des Befunds für seine und für meine Rolle
richtig, und die Sperre liegt **eine Pfadfreigabe** von ihrer Auflösung entfernt, nicht ein
Arbeitspaket.
Das ist eine Entscheidung des Betreibers über Leserechte; ich schreibe deshalb keinen
Vorschlag dafür, sondern melde es. Betroffen wäre ausser PWT jede künftige Quelle, deren
Dokumentation nur als PDF existiert — nach daten.md die Regel und nicht die Ausnahme.

Der in rueckstand.md ohnehin oben stehende Weg — der Betreiber lädt einmal von Hand nach
daten/roh/ — löst dieselbe Frage mit, weil pwt110.xlsx unter der Kennung 554105 die
Variablenliste maschinenlesbar trägt. Die beiden Wege konkurrieren nicht; der schnellere ist
der, der ohnehin ansteht.

## Was ich vorschlage

aufgaben/0034-reihentoml-baci-einheit-nachziehen.md mit status vorschlag. Der Übertrag der
gemessenen BACI-Einheit nach daten/reihen.toml ist im Arbeitspaket 0025 ausdrücklich
ausgenommen und in Abschnitt 8 des Befunds feldgenau vorgeschrieben; **0032 kann ihn nicht
mitnehmen**, weil dessen Bedingung 3 verlangt, dass ausser drei grund-Feldern keine Zeile
berührt wird.
Die Kollision auf reihen.toml ist der Grund, warum die Reihenfolge dem Projektmanager gehört
und nicht mir. Begründung im Paket.

Solange der Übertrag nicht läuft, ist reihen.toml an drei Stellen — Z. 1260, Z. 1261 und
Z. 1392 — älter als der Befund, der sie beantwortet. Dasselbe Muster wie bei 0024 und 0032,
und beim zweiten Mal ist es keine Beobachtung mehr, sondern eine Eigenschaft der Bauweise:
**Ein Befund in Prosa und eine maschinenlesbare Zwillingsdatei laufen ohne ein drittes Paket
immer auseinander.**
