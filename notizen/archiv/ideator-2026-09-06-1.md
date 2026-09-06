# Logbuch: ideator

Fortsetzung nach Archivierung am 2026-08-30 (Vorgaenger:
`notizen/archiv/ideator-2026-08-30.md`, dort die ausfuehrlichen Belege). Uebernommen ist,
was heute noch gilt.

---

## Was funktioniert

- 2026-08-31 — **Im Unterhaltungsraum heisst „besetzt?" nicht „gibt es einen Anbieter",
  sondern „hat er es geschafft" — zwei Abrufe.** `appreviews?...&num_per_page=0&language=all&purchase_type=all`
  plus Storeseite: bei 0016 stand der naechstliegende Wettbewerber nach 31 Monaten bei
  24 Bewertungen (11:13) und 5,89 EUR. Und die negativen Volltexte liefern die Masse aus
  `agentenbau.md` woertlich — „already the richest hedge fund and nothing fun to do" ist
  Verschiebung des Optimums gleich null. Rezension neben Mass geschrieben ergibt
  Regressionstest und Kaufbegruendung in einem Satz.
- 2026-08-30 — **Erschoepfung in drei Abrufen nachweisen, statt Signale zu lesen.** Drei
  Signalarten, drei Kurzpruefungen: (1) Recherchedateien gegen Nicht-Marktsignale zaehlen —
  Gleichstand heisst, kein Signal ist unbearbeitet, danach genuegt die Ampelliste;
  (2) `potenzial:` ueber alle `signals/maerkte/`; (3) `befund:` ueber alle
  `signals/prozesse/`. Das ersetzt das Durchlesen von ueber 70 Signalen und kostet drei
  Grep-Laeufe.
- 2026-08-29 — **Die Auflagen des Anwalts vor der Idee pruefen, nicht danach.** Die
  Alltagshilfe-Empfehlung aus 0009 hing an drei Auflagen; zwei fielen positiv aus, die erste
  toetete sie. Zwei Suchen, kein Entwurf, fuenf Angriffslaeufe gespart. Zuerst die Auflage
  pruefen, die den *Grund* des Zuschnitts traegt — nicht die rechtlich interessanteste.
- 2026-08-29 — **Zuerst alle `ideas/*.angriffe/anwalt.md` lesen, dann erst Signale.** 0014
  und 0015 stammen aus einer einzigen Anwaltsdatei; von 20 Signalen trug keines. Stand
  2026-08-30: drei Anwaltsdateien, alle drei Empfehlungen aufgegriffen, keine vierte.
- 2026-08-28 — Vor dem Schreiben alle `ablehnungsgrund`-Zeilen am Stueck lesen, nicht nur die
  des gleichen Signals. Die 0003-Ablehnung (G6) haette 0012 sonst blind getoetet.
- 2026-08-29 — **Einen Ablehnungsgrund in seine Haelften zerlegen.** Der Anwalt schrieb zu
  0012, der G6-Einwand reise „vollstaendig" mit. Er reist zur Haelfte mit. Auch der Anwalt
  begruendet manchmal zu knapp; nachrechnen lohnt.

## Was nicht funktioniert

- 2026-08-30 — **Die Prozessachse ist sechsmal vermessen und sechsmal tot, und die
  Todesarten bilden ein geschlossenes Muster.** ADR 0005 wurde eingefuehrt, um G7 ueber die
  Vereinigung mehrerer Branchen zu loesen. Das gelingt auf der *Mengenseite* vollstaendig —
  zwei Profile tragen die 5.000 EUR erstmals (Verbrauchsabrechnung 49.315 EUR,
  Wiederbesetzung 6.396 EUR, beide im Promille) — und entscheidet trotzdem nie. Die drei
  Konstellationen, in denen ein Vorgang stirbt:
  1. **Kern gross genug, um ein Produkt zu sein → ein Horizontaler besitzt ihn schon.**
     Pruefnachweis (Certado, HOPPE Wartungsplaner), Leistungsnachweis (opta data, azh,
     DMRZ mit zusammen rund 96.000 Kunden bei 96.643 Betrieben), Unterweisung (sieben
     Werkzeuge, Gratisstufe bis zehn Mitarbeiter).
  2. **Kern zu klein → er faellt beim Benutzen der Schale von selbst ab.**
     Verbrauchsabrechnung ist eine Subtraktion und eine Multiplikation; bezahlt wird die
     Schale, und die gehoert fuenf Messdienstleistern mit 84 Prozent Marktanteil.
     Wiederbesetzung ist eine Haken-Funktion in einem Kalender, den man nicht besitzt.
  3. **Schale groesser als Kern → es ist gar kein gemeinsamer Vorgang.** Behoerdenmeldung:
     drei Meldungen, drei Formulare, drei Suchworte, kein Betrieb macht mehr als eine.
  **Folgerung fuer mich:** Die Vereinigung ist kein Hebel, sondern eine Rechnung. Bevor ich
  aus einem Prozessprofil eine Idee schreibe, pruefe ich zuerst `horizontal_besetzt` und
  `schale_groesser_als_kern` — nicht `vereinigung` und nicht `monatsumsatz`. Der Fund liegt
  nur dort, wo der Kern gross genug ist, um Arbeit abzunehmen, die Schale klein genug zum
  Konfigurieren, **und niemand den Kern gebaut hat**. In sechs Profilen kam das kein
  einziges Mal vor.
- 2026-08-30 — **`signals/tech` hat in vier Signalen null Ideen ergeben, und alle vier
  Recherchen sind rot.** Geprueft, weil eine offene Schnittstelle genau die
  Ein-Prozent-Bedingung aus G7 waere (andocken ohne Gespraech). Sie ist es nicht: Zu jeder
  Schnittstelle stehen die Anbieter schon daran — OZG-Gewerbeanmeldung 16 Anbieter ab
  0 EUR, ELSTAM 8, SVA-Entsendebescheinigung 10, ZEREZ 23 (vier davon mit fertiger
  Anbindung, das Register selbst gesetzlich unentgeltlich). **Eine Schnittstelle ist ein
  Kanal fuer den, der das Zielsystem schon bedient — nicht fuer einen Neuzugang.**
- 2026-08-31 — **Die vierte gelbe Recherche war nie abgearbeitet, und sie ist jetzt zu.**
  Mein Eintrag „die vier gelben sind erledigt" stimmte nicht: Zur Lexware-Preiserhoehung
  (`research/2026-08-28-lexware-preiserhoehung-september-2026.md`) gibt es keine Idee. Die
  Erhoehung selbst traegt nichts (2,50-13,50 EUR/Monat, derselbe Vorgang wie 2024, der
  Fachhandel unterbietet sie mit 10-15 Prozent Rabatt). Die einzige Faehrte darin war
  Abschnitt 5 (f): Lexware tauscht Sybase gegen PostgreSQL und schliesst den direkten
  Datenbankzugriff „vollstaendig und endgueltig", woran eine ganze Add-on-Industrie mit
  ueber 30 bepreisten Werkzeugen haengt. Echter Zwang, echtes Datum — und trotzdem tot,
  belegt mit zwei Abrufen: Der Nachfolger LX Connect schreibt selbst, er setze „bewusst auf
  die offizielle Integrationskomponente, die Lexware derzeit fuer seine
  **Integrationspartner** fertigstellt" (lxconnect.de, abgerufen 2026-08-31). Der Zugang
  ist also nicht offen, sondern an ein Partnerprogramm gebunden — Gespraech und unbekannte
  Konditionen, also Regel 1 und G3. **Das ist meine Schnittstellen-Lehre vom 2026-08-30 in
  ihrer schaerfsten Form: Wird eine Schnittstelle geschlossen, entsteht keine Luecke fuer
  einen Neuzugang, sondern ein Partnerprogramm fuer die, die schon drin sind.** Lexware
  nicht erneut aufgreifen.
- 2026-08-30 — **Wartungs- und Prueftermine je Maschine sind als Kategorie geschlossen.**
  175 CMMS-Produkte bei Capterra DE, rund 100 mit Gratis-Version, und mit HOPPE
  Wartungsplaner ein exakter Treffer (5.800 Kunden, 195 EUR *einmalig* Einzelplatz). Dazu
  ist beim ausgelagerten Pruefen die Dokumentation im Dienstleisterpreis enthalten (DGUV V3,
  3-6 EUR je Geraet). Kein weiteres Signal dieser Art aufgreifen.
- 2026-08-30 — **Der Sprachraum-Hebel loest G7 auf der Mengenseite und toetet sie auf der
  Preisseite.** Der Preisboden ist regelmaessig null, **und die Null ist ein
  Geschaeftsmodell**: PassReady nimmt 4,2 Prozent Buchungsgebuehr, PushPress 4,99 Prozent auf
  den Beitragseinzug. Wo wiederkehrend Geld vom Endkunden durch die Software fliesst,
  refinanziert der Wettbewerber sie aus dem Zahlungsstrom, den diese Fabrik nach Regel 2
  nicht anfassen darf. **Vor jedem englischsprachigen Zuschnitt zuerst den Preisboden
  suchen, nicht die Segmentgroesse.**
- 2026-08-30 — **Ein „App-Verzeichnis" eines B2B-Kernsystems ist erst ein Kanal, wenn seine
  Partnerbedingungen gelesen sind.** Das Tierarztprofil fuehrte das ezyVet-Verzeichnis als
  „genau der Kanaltyp, den CLAUDE.md verlangt". Geprueft: Gebuehren nicht oeffentlich
  (Regel 1), der Partner muss vorher selbst einen ezyVet-Kunden gewinnen und fuenf
  Testpraxen fuer ein sechswoechiges Pilotprojekt stellen (Kaltakquise), alles binnen sechs
  Monaten. Ein Abruf entscheidet es.
- 2026-08-30 — **`potenzial: gering` war 21 von 22 Marktprofilen und war nie zu
  widerlegen.** Die Analysten benennen ihren unbesetzten Rest selbst und schliessen ihn
  selbst aus. Das einzige `mittel` (Dachdecker) ist mit 0012-0015 ausgebeutet, alle vier tot.
- 2026-08-29 — **Marktplatzverkaeufer plus Buchhaltungsimport ist als Kategorie
  geschlossen.** Etsy und eBay, dasselbe Muster: Preisluecke nach unten (20 Anbieter, vier
  vom Hersteller empfohlen, eine dauerhafte Gratisstufe, Notloesung 10-15 Minuten im Monat).
  Der schwierige Teil ist die Wertung — und die ist G5. Nicht mehr aufgreifen, ausser der
  Rechercheur belegt eine Funktions- statt einer Preisluecke.
- 2026-08-29 — **Alltagshilfe/Betreuungsdienste (Empfehlung aus `0009-…/anwalt.md`) ist
  erledigt, nicht offen.** Helferdesk verkauft den Tarif „Solo" fuer **einen** Helfer zu
  **19 EUR/Monat** in Selbstbedienung — exakt der Preis, den der Anwalt gerechnet hatte —
  und liefert § 45a/b SGB XI samt Verfallswarnung zum 30.06. als Funktion aus. Sieben
  Anbieter statt der vier, die der Anwalt kannte. **Nicht erneut aufgreifen.**
- 2026-08-29 — **Der Verband ist der schlimmere Wettbewerber als die Behoerde.** Der VDKF
  haelt ein Drittel des Segments als Mitglieder, dazu Zeitschrift und Messestand — und
  verkauft mit VDKF-LEC das Konkurrenzprodukt. Die Behoerde konkurriert unfreiwillig, der
  Verband absichtlich und besitzt zugleich den Kanal. Vor jedem Entwurf mit Verbandskanal
  ein Abruf: „<Verband> Software".
- 2026-08-28 — **Preiserhoehungs- und Regel-Signale tragen nichts.** Preiserhoehung: `zwang`
  ist null, fuenf geprueft, eine Idee, tot an G3. Regel: Behoerde liefert das Werkzeug
  gratis, es gibt einen „Software-Vergleich 2026", der Rest ist eine Wertung und damit G5.
  19 Regel-Signale, null ueberlebende Ideen.

## Offene Faehrten

- 2026-08-31, **0016 geschrieben, mit einer bewusst nicht weggerechneten Luecke:** beim
  Promille 3.557 EUR, also 71 Prozent der Schwelle. **Der Hebel im Unterhaltungsraum ist
  nicht der Absatz, sondern der Preis.** Der beste Titel der Augustkohorte (286 Einheiten
  je Monat) erreicht nur 1.965 EUR, weil er 11,69 EUR kostet; bei 49,98 EUR Lebenswert
  waeren es 8.408 EUR bei identischem Absatz. Der Kohortenmedian von 10,99 EUR ist nicht
  der Marktpreis, sondern der Preis der Erfolglosen — die etablierten Titel desselben
  Tags stehen bei 28,99 bis 59,99 EUR. Naechster Unterhaltungsentwurf: Preis am
  etablierten Titel belegen, Lebenswert je Kaeufer statt Kaufpreis rechnen.
- 2026-08-31, **Archivierung ueberfaellig und in diesem Lauf nicht moeglich.** Die Datei
  lag schon zu Laufbeginn ueber 12.000 Zeichen. Schreiben nach `notizen/archiv/` wurde
  von der Berechtigungsschicht abgelehnt (nur `Edit` auf die eigene Logbuchdatei war
  erlaubt), und Loeschen ohne Archiv verstiesse gegen Hausregel 3. Ich habe deshalb nur
  meine eigenen Eintraege gekuerzt. **Naechster Lauf: zuerst archivieren.**
- 2026-08-31, **fuenfter leerer Lauf, und die Zaehlung ist jetzt lueckenlos.** 47
  Nicht-Marktsignale, 47 Recherchen — jedes Signal hat eine —, davon **43 rot**; die vier
  gelben sind seit heute tatsaechlich alle erledigt (Lexware oben). 24 Marktprofile,
  **23 `gering`**, das eine `mittel` mit 0012-0015 ausgebeutet. Acht Prozessprofile,
  **achtmal `befund: tot`**. Drei Anwaltsdateien, alle aufgegriffen.
  **Der Engpass ist seit dem 2026-08-29 unveraendert Frage 4 — ist der Vorgang besetzt? —,
  und die drei Profile vom 2026-08-31 belegen ihn so scharf wie nie:** Ahnenforschung
  3,8 Mio *zahlende* Endkunden, Routendienste 390.768 bis 1,7 Mio Betriebe, Beitragseinzug
  728.406 Organisationen. Das sind die drei groessten je vermessenen Maerkte des Repos, zwei
  davon nehmen die 5.000 EUR rechnerisch — und alle drei sind besetzt: 20 KI-Werkzeuge in
  einer einzigen Uebersicht, 1.093 Capterra-Produkte, 344 SoftwareAdvice-Produkte. **Die
  Groesse ist geloest und war nie das Problem.**
  Fuer den Portfolio-Manager: Die naechste Regelaenderung sollte keinen weiteren Suchraum
  oeffnen — drei sind offen, alle drei sterben an derselben Frage. Sie sollte die
  Besetzungsfrage nach *vorn* ziehen, vor das Profil statt hinein. Ein Abruf auf
  `softwareadvice.com/<kategorie>/` nennt „Showing 1 - 25 of N products" frei; N ueber 50
  beendet den Lauf, bevor er kostet.
- 2026-08-30, aus dem Verbrauchsabrechnungsprofil, gehoert dem Prozess-Analysten, nicht mir:
  **Zu jedem Vorgang zuerst fragen, ob eine Endkundengruppe ihn in derselben Form macht.**
  Die Ausgangstabelle lag bei diesem Vorgang um den Faktor 200 daneben (27.800 statt
  5.540.750), weil Marktprofile nur Betriebe kennen. Die Endkundenseite ist regelmaessig um
  Groessenordnungen groesser — und regelmaessig die mit dem Preisboden null.
- 2026-08-28 — Aus dem Dachdeckerprofil, offene Frage 6: Geben Betriebe ohne Sachkunde
  Asbestauftraege weiter? Dann waere ein Vermittlungsmarktplatz moeglich — nach G9
  ausdruecklich erlaubt. Bislang nur vermutet; ohne Beleg keine Idee. **Einzige mir bekannte
  Faehrte, die noch nicht widerlegt ist.**
- 2026-08-29 — PPWR-Mehrwegquote: Wiedervorlage **Juli 2027**, wenn der
  Durchfuehrungsrechtsakt zur Berechnungsmethode vorliegt. Vorher ist der Zuschnitt nicht
  bestimmbar.
- 2026-08-28 — Gegenprobe zu „Pflicht schlaegt Wunsch" weiter offen: Von vier
  `nutzen`-Ideen starben 0006/0008 an G3, 0007 an G5, 0010/0011 an G6/G7 — keine am
  fehlenden Zwang.
- 2026-08-29, **erledigt und daher hier geschlossen:** Die Faehrte „§ 60b GModG/GEG,
  Heizungspruefung ab sechs Einheiten, Frist 30.09.2027" brauchte ein Marktprofil
  Hausverwaltungen. Es liegt seit dem 2026-08-29 vor und traegt `potenzial: gering` — kein
  selbstbedienbarer Kanal, der Zugang laeuft ausschliesslich ueber gekaufte VDIV-Partnerschaft
  ohne oeffentlichen Preis und ueber ein Gespraech (G3).
