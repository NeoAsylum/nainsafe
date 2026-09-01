# Logbuch: prozess-analyst

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/prozess-analyst-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- **2026-08-30** — Die Suche „Software fuer Pruefdienstleister <Vorgang>" beantwortet
  Frage 4 und Frage 6 in einem Abruf: Kommen branchenneutrale Anbieter mit eigener
  Landingpage zurueck, ist das Suchwort gemeinsam *und* besetzt. Das ist der billigste
  Test dieser Rolle — vor die Vereinigungszaehlung stellen, nicht danach.
- **2026-08-30** — Zuerst die `handarbeit`-Felder woertlich nebeneinanderlegen, dann erst
  addieren. Grep ueber alle Frontmatter (`segment|betriebe|handarbeit|potenzial`) kostet
  einen Aufruf und ersetzt das Lesen von 300.000 Zeichen Profiltext.
- **2026-08-30** — **Steht der Vorgang in einem Gesetz, das die Betroffenen selbst
  aufzaehlt, ist der Gesetzestext die Branchenliste.** § 302 SGB V nennt neun Gewerke in
  einem Satz; die Ausgangstabelle kannte drei. Ein Abruf hat die Vereinigung von 74.662 auf
  96.643 gehoben. **Vor der Zaehlung nach der Norm suchen, nicht nach Branchen.**
- **2026-08-30** — **Die Kundenliste des horizontalen Anbieters ist der beste Beweis, dass
  der Vorgang derselbe ist.** Wer ihn fuer neun Branchen auf einer Plattform abwickelt,
  koennte das nicht, waeren es neun Vorgaenge. Ersetzt eine lange Kern-Schale-Diskussion —
  billiger und haerter als jedes eigene Argument.
- **2026-08-30** — **Die Bauartpruefung vor die Zaehlung stellen: Wo beginnt und wo endet
  der Vorgang?** Endet er in einem System, das der Betrieb schon hat (Kalender, ERP,
  PVS), ist dessen Hersteller Torwaechter und Wettbewerber zugleich, und der Vorgang ist
  eine Haken-Funktion in seinem Tarif. Zwei Minuten Pruefung, und der ganze Profillauf
  steht schon fest. Bei der Terminwiederbesetzung war das Schritt 5 des Kerns: „die
  Buchung geht zurueck in **denselben** Kalender".
- **2026-08-30** — Frage 4 in einem Abruf beantworten: Suchwort plus „software". Kommt
  eine **Landingpage eines horizontalen Anbieters genau zum Suchwort** zurueck (Acuity
  `/learn/fill-slots-with-waitlist-software`, Square `/features/waitlist-software`), ist
  Frage 4 und Frage 6 zugleich erledigt — Kanal vorhanden, Kanal besetzt.
- **2026-08-30** — Der billigste Besetzungstest ueberhaupt: **pruefen, ob das Suchwort als
  Domain vergeben ist.** `unterweisungsnachweis.de` gehoert einem Wettbewerber. Eine Domain
  mit dem Vorgangsnamen beweist einen gemeinsamen Kanal *und* dass er besetzt ist — in
  einem Abruf, noch vor jeder Anbieterliste.
- **2026-08-30** — Der **negative** Kanaltest kostet vier Suchen und beantwortet Frage 6 und
  Frage 3 zugleich: je Branche einmal „<Branchenwort> <Vorgang> software". Kommt in keiner
  der vier Trefferlisten ein Anbieter aus einer anderen Branche vor, gibt es kein
  gemeinsames Suchwort — und dann ist der Vorgang trotz gleichem Kern nicht derselbe Markt.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

- **2026-08-30** — Die Vorgangsgruppierung aus der Ausgangstabelle haelt der Pruefung
  nicht stand: Von 65.433 Betrieben beim Pruefnachweis bleiben 10.365. Facility macht
  einen vertraglichen, keinen gesetzlichen Nachweis; Dachdecker macht eine einmalige
  Anzeige je Baustelle, keinen Turnus; Spielplatzbetreiber sind Pflichtige, keine Pruefer.
  **Lehre: Ein `handarbeit`-Feld, das aehnlich klingt, ist noch kein gleicher Vorgang —
  drei Merkmale pruefen (fremdes Objekt? gesetzliche Frist? Vorlagepflicht?).** Die
  Marktprofile selbst sind korrekt, die Fehler stecken in der Gruppierung.
- **2026-08-30** — „Kleine Schale, grosser Kern" ist **kein** Fundsignal, sondern das
  Gegenteil. Ist der branchenneutrale Kern gross, hat ihn jemand gebaut; die vertikalen
  Anbieter beweisen dann nur Zahlungsbereitschaft, nicht eine Luecke. Der Fund braucht
  zusaetzlich, dass das horizontale Werkzeug **fehlt** — Frage 4 entscheidet, nicht Frage 3.
- **2026-08-30** — Und die Gegenrichtung ist genauso toedlich: **Ein winziger Kern ist eine
  Funktion, kein Produkt.** Beim Unterweisungsnachweis sind es vier Spalten (Person, Thema,
  Datum, Frist) — so etwas wird nicht als Produkt gebaut, sondern in jedem HR-, Lern- und
  EHS-System mitgeliefert; Capterra fuehrt dafuer eine eigene Kategorie mit rund 100
  Produkten. **Lehre: Frage 3 hat zwei Absterbezonen, nicht eine.** Der Fund liegt in dem
  schmalen Band dazwischen: Kern gross genug fuer ein eigenes Produkt, klein genug, dass ihn
  noch niemand gebaut hat. Beide Vorgaenge bisher lagen ausserhalb, an entgegengesetzten
  Enden.
- **2026-08-30** — **Steht am Ende des Vorgangs eine Zahlung, gehoert der Vorgang dem, der
  die Zahlung abwickelt.** Beim Leistungsnachweis an den Kostentraeger halten drei
  Abrechnungszentren rund 96.000 Kundenbeziehungen in einer Vereinigung von 96.643 — sie
  bekommen den Beleg ohnehin, pruefen ihn ohne Grenzaufwand, kennen den Zahlungseingang und
  koennen deshalb **Haftung** zusagen. Vierte und haerteste Variante von „die Behoerde ist
  der Wettbewerber". **Vorabtest: Fliesst am Ende des Vorgangs Geld? Dann zuerst nach dem
  Abwickler suchen, nicht nach Software.**
- **2026-08-30** — **Frage 3 fragt nach der Groesse der Schale und muesste nach ihrer
  Haltbarkeit fragen.** Beim Pruefnachweis war die Schale eine *Konfiguration* (einmal
  gesetzt, jahrelang gueltig), beim Leistungsnachweis ein *Abonnement* (regionale
  Rahmenvertraege, fortgeschriebene Schluesselverzeichnisse, woechentliche Pflege). Gleiche
  Groesse, entgegengesetzte Folge: Die zweite Art ist bei zwei Wochenstunden Betriebszeit
  schon fuer sich ein Ausschluss — und wer sie heute pflegt, verkauft sie fuer 9,99 EUR.
- **2026-08-30** — **Eine unbegrenzte Vereinigung ist ein Warnzeichen, kein Fund.** Der
  Unterweisungsnachweis trifft *jeden* Arbeitgeber (2,1 Mio. Betriebe) — und ist genau
  deshalb der dichtest besetzte Vorgang der Liste. Wo eine Pflicht alle trifft, ist der
  Markt gross genug, dass ihn jemand vollstaendig bedient. **Vorabtest kuenftig: Gilt die
  Pflicht branchenunabhaengig? Dann Frage 4 sofort stellen und die Zaehlung sparen.**
- **2026-08-30** — **„Die Vereinigung ist gross genug" rettet nichts.** Terminwiederbesetzung:
  164.458 belegte Betriebe, Rechnung 6.396 EUR — die erste Vereinigung dieser Rolle, die G7
  traegt — und trotzdem `tot`. `traegt_5000` und `befund` sind zwei Fragen; wer nur die
  Rechnung sieht, meldet einen Fund, wo eine Haken-Funktion steht.
- **2026-08-30** — Wird ein Vorgang als **Tarifstufe** verkauft statt als Produkt (Acuity ab
  Standard, Square ab Plus, medatixx im PVS enthalten), ist sein Einzelpreis die Differenz
  zweier Tarife und damit fast null. Preisanker suchen heisst dann: **gibt es ueberhaupt
  einen separaten Preis?** Bei mir war es genau einer (3,99 EUR je nachbesetztem Termin) —
  der ist der Deckel, nicht der Plattformpreis.
- **2026-08-30** — Untere Absterbezone, dritter Beleg und der klarste: Der Kern der
  **Verbrauchsabrechnung** ist eine Subtraktion und eine Multiplikation. Dort zaehlt der
  Einwand „Excel ist unbequem" nicht nur nicht — Excel ist das *richtige* Werkzeug, und der
  Kern faellt beim Benutzen der Branchenschale ohnehin ab. **Pruefformel: Laesst sich der
  Kern in einem Satz als Rechenvorschrift schreiben, ist Frage 4 schon beantwortet.**

## Offene Faehrten

- **2026-08-30** — **Die Rollentrennung Pflichtiger/Pruefer ist die zweite Achse in der
  zweiten Achse.** Bei jedem Pflichtvorgang stehen zwei Parteien am selben Dokument mit
  gegenlaeufigem Interesse: Fuer den Pruefer ist der Vorgang Umsatz, fuer den Pflichtigen
  Ausgabe. Beim naechsten Vorgang der Liste zuerst entscheiden, auf welcher Seite
  geschnitten wird — sonst zaehlt man beide zusammen und rechnet mit einer Union, die es
  nicht gibt. Vermutung, an einem Vorgang belegt: Wo Fachkunde vorgeschrieben ist,
  entsteht immer ein Dienstleister, und dann ist die Prueferseite nie eine Last.
- **2026-08-30** — Ungezaehlte Prueferbranchen, die denselben Vorgang machen und fuer die
  ich keine amtliche Zahl fand: DGUV-V3-Pruefdienstleister, Torpruefer, Regalpruefer
  (DIN EN 15635), Trinkwasser-Probenehmer, Spielplatz-Pruefdienstleister. Keine wird als
  Wirtschaftszweig gefuehrt. Wer hier eine Zaehlung findet, hebt jede kuenftige
  Prueferunion — bei diesem Vorgang haette es das Urteil nicht gedreht.
- **2026-08-30** — Naechster Vorgang der Liste: **Behoerdenmeldung je Vorgang mit Formular
  und Frist** (Elektro 44.975, Dachdecker 15.241, SHK 48.000). Warnung vorab aus
  `lehren.md`: Dort ist die Behoerde der Wettbewerber und ihr Online-Dienst gebuehrenfrei —
  Frage 4 lautet hier „Serviceportal", nicht „Excel".
- **2026-08-30** — **HOPPE Wartungsplaner bedient zwei von zwei untersuchten Vorgaengen**
  (Prueffristen an Objekten, Unterweisungsfristen an Personen). Wer eine Fristendatenbank
  hat, haengt jede weitere Fristenart mit an. **Vor jedem Fristen-Vorgang ein Abruf auf
  wartungsplaner.de** — steht der Vorgang dort schon als eigene Seite, ist Frage 4 beantwortet.
- **2026-08-30** — **Die Zahl der Arztpraxen in Deutschland ist nicht frei auffindbar.**
  Destatis rechnet aus einer Stichprobe von hoechstens 7 Prozent hoch und nennt nur
  Durchschnittseinnahmen, die KBV zeigt sie nur in interaktiven Grafiken. Damit fehlt die
  groesste Branche in jeder Gesundheits-Vereinigung. Nicht erneut ueber Destatis oder
  KBV-Gesundheitsdaten versuchen — wenn, dann ueber das Bundesarztregister-PDF oder eine
  KV-Einzelauswertung. Beim Terminvorgang war es folgenlos.
- **2026-08-30** — Zwei Vorgaenge der Liste sind damit noch offen: **Leistungsnachweis
  gegenueber einem Kostentraeger** (Pflege 15.549, Hebammen 19.000, Physio 40.113) und
  **Verbrauchsabrechnung mit Zaehlerablesung** (Camping 3.200, Hausverwaltung 24.600).
  Beim Leistungsnachweis vorab pruefen, ob der Kostentraeger je Branche ein anderer ist —
  wenn ja, ist die Schale das Abrechnungsformat und damit vermutlich groesser als der Kern.
- **2026-08-30** — **Offener Punkt an den Portfolio-Manager, nicht an mich: G7 misst bei
  unbegrenzten Vereinigungen nichts mehr.** Ein Promille von 2,1 Mio. Betrieben ergibt
  60.900 EUR im Monat und nimmt die Schwelle um das Zwoelffache — obwohl der Vorgang
  eindeutig tot ist. Der Anteil unterstellt einen Markt mit Rand; hat die Vereinigung
  keinen, waechst nur der Nenner. Ich habe `traegt_5000: ja` und `befund: tot` deshalb
  bewusst auseinanderfallen lassen, statt die Rechnung passend zu machen.

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

## Einträge

- **2026-08-30 (Start, vom Betreiber angelegt)** — Die Rolle entsteht aus einer
  Auszählung, die schon vorliegt: Die `handarbeit`-Felder der achtzehn Marktprofile
  gruppieren sich zu vier Vorgängen, und drei davon sind sechsstellig oder nahe daran.
  **Fang dort an, statt neu zu suchen.**

  | Vorgang | Profile mit diesem `handarbeit`-Feld | Betriebe |
  |---|---|---:|
  | Prüfnachweis mit Frist | dachdecker (15.241), aufzugswartung (841), kaelte (3.214), schaedlingsbekaempfer (1.074), spielplaetze (10.775), facility (34.288) | 65.433 |
  | Leistungsnachweis an Kostenträger | ambulante-pflegedienste (15.549), hebammen (19.000), physiotherapiepraxen (40.113) | 74.662 |
  | Behördenmeldung mit Formular | elektroinstallation (44.975), dachdecker (15.241), sanitaer-heizungs-klima (48.000) | rund 108.000 |
  | Verbrauchsabrechnung mit Zähler | campingplaetze (3.200), hausverwaltungen (24.600) | 27.800 |

  Zwei Warnungen aus den Profilen, die du beim Rechnen brauchst:

  - **Der Preisboden null ist im englischsprachigen Raum ein Geschäftsmodell.** Wo
    wiederkehrend Geld vom Endkunden durch die Software fließt, verschenkt der
    Wettbewerber das Abo und lebt vom Zahlungsstrom (Fahrschulen, Studios). Betrifft
    vor allem die Vorgänge *Beitragsabrechnung* und *Terminwiederbesetzung* — prüfe bei
    denen den Preisboden **vor** der Größe, das spart einen ganzen Profillauf.
  - **Die Kanalfrage ist die, an der hier bisher alles gestorben ist.** Bei dir ist sie
    schärfer als beim Markt-Analysten: Fünf Branchenverbände sind kein Kanal. Suche
    nach dem, was alle sechs Branchen gemeinsam haben — die Pflicht, die Prüffrist, das
    Wort, das alle googeln.
