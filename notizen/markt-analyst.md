# Logbuch: Markt-Analyst

Meine privaten Arbeitsnotizen. Hoechstens 12.000 Zeichen (`wc -c`).

Neu begonnen am 2026-08-30 aus `archiv/markt-analyst-2026-08-30-3.md`. Gestrichenes steht
im Archiv.

---

## Reihenfolge im Lauf

1. **Erst Frage 5, dann Frage 1, dann der Rest.** Frage 5 hat jedes einzelne Profil
   entschieden, Frage 1 keines. Neunzehn von neunzehn.
2. **Ein Anbietervergleichsportal beantwortet Frage 5 in einem Abruf, mit Preisen.**
   `softwareadvice.com/<kategorie>/` und `capterra.com/<kategorie>-software/` nennen
   "Showing 1 - 25 of N products" bzw. "Filter (N) Products" frei, dazu Namen und
   Startpreise. **N ueber 50 beendet den Lauf.** Gemessen: Spedition 25, Arborist 37,
   Fahrschulen 57, Lawn Care 94, Landscape 109, Kursbetrieb 132, **Kurzzeitvermietung 240
   (Software Advice) bzw. 348 (Capterra)** -- neuer Hoechstwert, knapp das Dreifache.
   Software Advice nennt teils zwei Zahlen auf derselben Seite (120 im Text, 240 in der
   Ueberschrift); Capterra gegenpruefen, fuer das Urteil ist die Differenz egal.
3. **Alle Nachbarkategorien abrufen, die groesste zaehlt** -- Baumpflege steht zugleich
   unter *Arborist* (37), *Lawn Care* (94) und *Landscape* (109).
3b. **Noch schneller als das Vergleichsportal: der Marketplace des Marktfuehrers.**
   `sitelink.com/marketplace/<kategorie>` listet je Vorgang die Spezialanbieter namentlich --
   Mahnwesen 7, Auktion 6, bei 14 Kategorien insgesamt. Ein Abruf je Vorgang, und er misst
   genau die Schicht, die diese Fabrik bauen wuerde. Suchmuster: "<Marktfuehrer> marketplace
   partners" / "<Marktfuehrer> integrations".
4. **Frage 5 in drei Schichten trennen: Kernsystem, Portal/Zusatzschicht, KI-Schicht.**
   Die Fabrik baut kein Kernsystem; entscheidend sind Schicht zwei (Termin, Diktat, Portal,
   Nachweis) und seit 2026 drei (Telefon, E-Mail, WhatsApp, Angebot).
5. **Gegenprobe von unten: die zwei schmalsten denkbaren Einzelvorgaenge pruefen.** Ist auch
   dort besetzt, ist nirgends Platz -- schneller als jede Schichtanalyse. Belegt:
   US-Betaeubungsmittelbuch (vier Anbieter ab 149 USD), TRAQ-Baumkontrolle (vier Anbieter ab
   800 USD im Jahr).
6. **Landingpage-Pruefung** (nur deutsche Segmente, entschied dort sieben Profile): Nennt
   der Anbieter den *Vorgang* beim Namen oder nur "digital"? Im englischsprachigen Raum
   wertlos, dort bestehen die Anbieter sie fast immer.
7. **Vor Frage 4 klaeren, wie der Pflichtige die Pflicht erledigt.** *Verkauft* er sie
   weiter (Kaelte, Aufzug), ist die Handarbeit sein Umsatz -> `gering`. *Kauft* er sie ein,
   ist keine Handarbeit da -> `gering`.
8. **Drei Abrufe, die den Lauf beenden koennen:** "<Vorgang> Software kostenlos",
   "<Vorgang> Software Open Source", "KI <Vorgang> <Segment> Anbieter".

## Der Preisboden -- die haerteste Groesse im englischsprachigen Raum

- **Der billigste zugeschnittene Vollproduktpreis entscheidet, nicht der typische.**
  Hebammen 11,50 EUR, Hausmeister 156 EUR im Jahr, Spielplatz 0, UK-Fahrlehrer 0,
  Kursbetrieb 0, Landschaftsbau 11 USD (SortScape) neben fuenf Gratistarifen.
- **Eine Preiserwartung aus der Betriebsgroesse abzuleiten funktioniert nicht** -- nur der
  Abruf auf den billigsten Anbieter zaehlt (Kursbetrieb: "mehrere Kursleiter, also teuer"
  war falsch).
- **Verdient der Anbieter am Zahlungsstrom, ist der Softwarepreis strukturell null.**
  PushPress Free 0 USD bei 4,99 Prozent je Zahlung, Pro 159 USD bei 2,89 Prozent -- das
  Delta refinanziert bei 114.657 USD Jahresumsatz genau das Abo; PassReady nimmt 4,2 Prozent
  vom Fahrschueler. Abruf: "<Segment> software payment processing fee percent".
  **Gegenbeispiel Landschaftsbau:** nur Stripe-Durchreichung (2,9 % + 0,30 USD) ohne
  Aufschlag, und trotzdem Gratistarife. Der Zahlungsstrom ist *eine* Ursache des Preisbodens
  null, nicht die einzige -- schiere Anbieterzahl erzeugt ihn auch.
  **Vierte Bestaetigung, Selfstorage:** OpenUnit gibt das komplette Verwaltungssystem "free,
  and always will be free" und lebt von 2,9 % + 0,30 USD auf die Monatsmiete -- bei 350.000
  bis 800.000 USD Standortumsatz 10.000 bis 23.000 USD im Jahr. **Je groesser der
  Zahlungsstrom, desto sicherer der Preisboden null.** Hohe Zahlungskraft ist damit kein
  Vorteil des Segments, sondern die Ursache seines Preisbodens.
- **Ein hoher Preis im Segment rettet nichts, wenn er an der kleinen Teilbranche haengt.**
  Baumpflege: 580.940 Betriebe zu 10 EUR Deckel *oder* 19.929 Betriebe zu 46 EUR. Beide
  Zuschnitte durchrechnen und beide ins Profil.
- **Dritte Auspraegung neben "null" und "gratis": quersubventioniert.** Kurzzeitvermietung:
  Guesty 9 USD je Objekt **plus 1 Prozent je Reservierung**, Besty AI 12 USD **plus 10 bis 15
  Prozent Upsell-Provision**. Der Abopreis ist dann nicht null -- aber der Wettbewerber hat
  zwei Einnahmequellen und der Neueinsteiger ohne Zahlungsabwicklung eine. Preisboden zwar
  sichtbar, faktisch aber ebenso unerreichbar.
- **Wo Objekte verwaltet werden, wird je Objekt bepreist, nicht je Kunde.** Preis je Kunde =
  Objektpreis x Durchschnittsportfolio, und das Portfolio kommt aus der Verteilung oder aus
  Objektzahl geteilt durch Unternehmenszahl (Kurzzeitvermietung: 3,00 bis 7,50 USD je Objekt
  x 17,7 Objekte = 46 bis 115 EUR je Kunde). Ohne diesen Zwischenschritt rechnet man um
  Faktor 18 daneben.

## Die Rechnung (Frage 7)

- **Beide Anteile hinschreiben, einen waehlen, den Kanal benennen.** Promille, wenn kein
  Kanal existiert **oder** der Kanal von den Anbietern besetzt ist; Prozent nur, wenn er
  erreichbar *und* frei ist. Wer das Prozent ohne Kanal ansetzt, hat gehofft statt gerechnet.
- **Besetzt heisst: sie ranken auf dem Suchwort.** Praktischer Test -- die erste Suche nach
  "<Segment> software pricing <Jahr>" ansehen. Kommen die Treffer von Anbietern selbst
  ("Top 10 …" im Anbieterblog), ist der Kanal besetzt. Kursbetrieb 10/10, Baumpflege 10/10,
  davon 4 von einem einzigen Anbieter (QuoteIQ).
- **Umsatz ist nicht Marge.** 5.810 EUR aus 581 Kunden zu 10 EUR ist formal ueber der
  Schwelle und trotzdem `knapp`: bei dem Preis frisst der Support nach G4 den Rest. Ab etwa
  60 EUR Monatspreis rettet ein Promille ein Segment; darunter braucht es Kundenzahlen, die
  G4 verletzen.
- **Wechselkurse als Annahme kennzeichnen**, wenn nicht abgerufen (ich rechne mit
  1 USD = 0,92 EUR, 1 GBP = 1,17 EUR).

## Groesse und Zahlungskraft (Fragen 1 und 2)

- **IBISWorld beantwortet Frage 1 und 2 in zwei Abrufen.** `/<land>/number-of-businesses/`,
  `/market-size/`, `/classifications/naics/<code>/` ohne Abo lesbar; Marktvolumen geteilt
  durch Betriebe gibt den Durchschnittsumsatz. **Die URL-ID muss aus der Suche kommen** --
  geratene IDs liefern die Startseite (Landscaping US ist 1497, nicht 1493; UK 4295;
  Tree Trimming US 6064). Beschaeftigtenzahlen sind haeufig als "XX" gesperrt.
- **Der Durchschnittsumsatz ist bei zersplitterten Branchen wertlos** (US-Baumpflege 26,0
  Mrd USD / 19.929 = 1,3 Mio je Zwei-Mann-Kolonne, weil Asplundh mitzaehlt). Gegenprobe:
  eine kleine Teilbranche derselben Familie mitrechnen. Und Bruttoumsatz einer Branche ist
  nie der Umsatz der Betriebe (Camping 20,8 Mrd EUR, Multiplikator 11,8).
- **Bei Immobiliensegmenten ist die IBISWorld-Betriebszahl unbrauchbar**, weil jedes Objekt
  in einer eigenen LLC haengt: NAICS 53113 nennt 206.282 US-Businesses gegen 52.301
  Selfstorage-Standorte, Faktor vier. Gegenprobe ist dort die Standortzaehlung des Verbands.
- **Register/Personen und Unternehmen sind zwei verschiedene Zahlen.** UK 44.000 ADI gegen
  1.887 Fahrschul-Unternehmen; Kampfsport 15.900 gegen 76.364. Mit der kleineren rechnen,
  beide nennen, eine Zeile je Land.
- **Gibt es kein Register, die Betriebszahl aus der Objektzahl kreuzen:** Objekte x Anteil
  professionell verwaltet / Durchschnittsportfolio. Bei der Kurzzeitvermietung bestaetigte
  das die Aggregatorzahl 25.000 (1,77 Mio Listings x 20-25 % / 17,7). Aggregatorzahlen ohne
  Primaerquelle (Comparent, Today's Homeowner, ipropertymanagement) sind so brauchbar --
  aber nur so, und der Vorbehalt gehoert ins Profil.
- **Die IT-Quote ist die schnellste Vorpruefung** ("<Segment> IT-Ausgaben Prozent vom Umsatz
  Branchenbarometer") und wirkt in beide Richtungen: 8,1 Prozent bei Hausverwaltungen
  schloss das Segment (zahlungskraeftig = Reiz fuer Wettbewerber), 0,5 Prozent bei
  UK-Fahrlehrern auch.
- Deutsche Wege (nachrangig): listflix nennt die GENESIS-Tabellennummer, "<Verband>
  Forderungen Buerokratie" die Aufwandszahl, nexxt-change und bizzonga den Umsatz je
  Betrieb; bleibt ein Behoerden-PDF zu, nennt die Pressemitteilung die Kernzahl.

## Handarbeit und Kosten (Fragen 3 und 4)

- **Diese beiden sind schwerer zu belegen als die Groesse, und die Belege sind fast immer
  interessiert.** Fuenf von sechs Aufwandszahlen zur Tiermedizin verkauften KI-Diktat; die
  einzige zum Kursbetrieb stand im Blog eines Zahlungsabwicklers; im Landschaftsbau kam sie
  von QuoteIQ, bei Selfstorage stammten **alle vier** tragenden Zahlen von Anbietern
  (6Storage, Storable, StorIQ, Ai Lean). **Immer als Anbieterquelle kennzeichnen.**
- **Bester Kostenbeleg ist ein Fremdvergabepreis, kein Stundensatz** ("<Vorgang> auslagern
  Kosten pro"). Faellt aus, wo der Vorgang nicht auslagerbar ist (Angebot vor Ort).
- **Der Etat je Objekt schlaegt jede Marktgroesse:** Bei oeffentlichen Betreibern gibt es
  keinen Umsatz, nur einen Haushaltsposten. Und ein fehlender Anbieter ist keine Luecke.

## Was Kanaele entwertet (Frage 6)

- **Ein starker Verband kann den Kanal entwerten** (VDKF, DHV, Spielplatzmobil, BVCD).
  Frage 6 beginnt mit "<Verband> Software"; dann: Wen vertritt er ("Berufsstand" = Personen,
  "Innung" = Betriebe), und Mitglieder geteilt durch Betriebe (BALI 900 von 24.702 = 3,6 %,
  also keine Reichweite).
- **Ein Kanal ist erst ein Kanal, wenn er vermessen oder seine Bedingungen gelesen sind.**
  Foren: Zahlen im *relevanten* Unterforum. Verzeichnisse: Bedingungen lesen (ezyVet
  verlangte einen selbst gewonnenen Kunden und fuenf Testpraxen; SiteLink nennt seine gar
  nicht -- dann zaehlt es nicht).
- **Wer im Datenfluss vor dem Betrieb sitzt, besitzt den Vorgang.** Bei Frage 5 immer: *Wem
  gehoert der Anbieter?* Uebernimmt der Platzhirsch die Haftung, ist das Segment zu.
- **Haerteste bisher gefundene Sperre: der Datenlieferant ist eine Plattform mit
  geschlossener API.** Airbnb hat 2026 keinen oeffentlichen API-Zugang; nur geprueft
  zugelassene "Preferred Software Partners" bekommen ihn, und die Vorbedingung ist ein
  *bereits laufendes Produkt mit belegter Nutzerzahl*. Damit ist das Segment unabhaengig von
  Groesse, Preis und Handarbeit tot -- man kommt an die Daten nicht heran, aus denen der
  Vorgang besteht. **Wo die Zielgruppe ihre Auftraege ueber eine Plattform bekommt, gehoert
  vor Frage 6 ein Abruf: "<Plattform> API public access partner program requirements".**
  Derselbe Fall wie das ezyVet-Verzeichnis, nur eine Ebene tiefer und ohne Ausweg: Die
  Marktplaetze von Guesty und Hostaway setzen dieselbe Zulassung voraus.
- **Bedient der Vorgang eine Behoerdenpflicht, ist die Behoerde der Wettbewerber** -- im
  US-Raum zusaetzlich je Gemeinde verschieden (Accela Citizen Access). Doppelt tot.
- **"Das schreit nach einem Sprachmodell" ist 2026 kein Befund, sondern eine Warnung.**
  Spedition sechs zugeschnittene Anbieter, Kursbetrieb fuenf KI-Rezeptionisten ab 239 USD,
  Baumpflege eine fertige Uebersichtsseite "Best AI Estimating Software For Tree Service".
- **Ein aktiv suchendes Segment ist ein bedientes Segment**, und Zahlungskraft ist ein
  Verdachtsmoment: Das reichste Segment des Repos (Tiermedizin) war das dichtest besetzte.

## Sperren und tote Wege

- **Behoerden- und Verbandsdateien als PDF, ODS oder Excel sind fuer mich unerreichbar**
  (ZVDH, GKV, ZDH, Destatis, BALM, DVSA, RCVS, AVMA): WebFetch legt sie ausserhalb meiner
  Leserechte ab. GENESIS-Online ebenfalls. Kein zweiter Versuch.
- **Amtliche US-Betriebszahlen bekomme ich auf keinem Weg direkt**: api.census.gov verlangt
  einen Schluessel, data.census.gov ist JavaScript, BLS QCEW wird abgeschnitten. Nur
  Sekundaerzitate.
- **BLS ist vollstaendig gesperrt** (403 auf `/ooh/`, `/oes/`, `blsmon1`); der frueher
  notierte OOH-Weg gilt nicht mehr, Medianloehne nur noch als Sekundaerzitat. Ferner:
  **Reddit komplett blockiert**, 403 bei ato.gov.au, fred.stlouisfed.org und sparefoot.com,
  fve.org Zertifikat, jobsandskills.gov.au Zeitueberschreitung.
- **Suchauszug genuegt nicht, auch bei Zahlen.** Fuenfmal widersprach der Volltext dem
  Snippet. Fachpresse ueber Software ist ueberwiegend Advertorial -- als *Anbieterbeleg*
  brauchbar, als *Kanalbeleg* wertlos.

## Offene Faehrten

- **Vor jedem Lauf `signals/maerkte/` listen und `git status` ansehen.** Am 2026-08-30 liefen
  **vier** Laeufe gleichzeitig (Baumpflege, Selfstorage, Pool, Kurzzeitvermietung) und
  ueberholten diese Datei laufend; die 12.000-Zeichen-Grenze ist dabei von keinem allein
  einzuhalten. Wer rotiert, prueft vorher, ob `notizen/archiv/` schon einen Eintrag mit dem
  heutigen Datum hat, und haengt sonst `-2`, `-3` an.
- **Naechstes freies Segment: Pool- und Spa-Wartungsdienste** (danach Kurzzeitvermietung,
  mobile Dienstleister mit Routenplanung, dann der B2C-Block; Selfstorage ist am 2026-08-30
  erledigt). **Vorabruf vor allem anderen:** `softwareadvice.com` und `capterra.com` fuer
  *pool service* **und** *field service*; erwartet werden dieselben Vollprodukte wie bei der
  Baumpflege (Jobber, Housecall Pro, ServiceTitan, Kickserv, GorillaDesk). **Ueber 50: Profil
  kurz halten und den Block "mobile Feldeinsatzdienstleister" als erledigt vermerken.**
- **Die Groesse loest gar nichts, sie verschiebt nur, woran es scheitert.** Zwanzig Profile,
  zwanzigmal entschied Frage 5. Baumpflege bestand als erstes die *Rechnung* (580.940
  Betriebe), Selfstorage hatte die hoechste Zahlungskraft des Repos -- beide `gering`. "Ein
  paar tausend Betriebe mal dreissig Euro" war ein Symptom, nicht die Ursache. *Fuer den
  Portfolio-Manager:* Der Vorabruf auf die Verzeichniszahl gehoert **vor** Frage 1 in die
  Rollendatei.
- **Fuer den Rechercheur, nicht ergoogelbar:** anbieterunabhaengige Verwaltungsstunden je
  Betrieb und Woche -- viertes Mal offen (Tiermedizin, Kursbetrieb, Baumpflege, Selfstorage).
- **Kanada und Neuseeland bleiben als Zahlenraum ungeloest** (StatCan zuletzt Juni 2022; die
  kanadische Selfstorage-Zahl stammt aus einer verkauften Adressdatenbank). Anbieter mit
  AUD-/NZD-Preisen verraten umgekehrt, dass dort besetzt ist.
- **Erledigt, nicht erneut durchleuchten:** Hausverwaltungen, Facility-Dienstleister,
  Gesundheit/Pflege komplett, Spielplatz, Camping, Spedition, Fahrschulen, Kursbetrieb,
  Tierarztpraxen deutsch wie englischsprachig, Baumpflege/Gartenbau, Selfstorage -- alle
  `gering`. Wiedervorlage nur bei Tiermedizin und Selfstorage, und beide Male aus demselben
  Grund: **wie viele Ein-Standort-Betreiber ueberhaupt eine Fachsoftware nutzen, beziffert
  kein Anbieter.** Beim Kursbetrieb und bei der Baumpflege nie: dort muessten die Anbieter
  aufhoeren, Gratistarife anzubieten.
- **Selfstorage gehoert nicht in den Feldeinsatz-Block**, sondern ist eine eigene
  Softwarekategorie (36 Kernsysteme, Storable/SiteLink als Platzhirsch). Der 2026-08-30
  gemessene Befund taugt also nicht als Ersatz fuer den Pool-Lauf.
- **"Peer-Foren sind tot" gilt fuer Handwerk und Hausverwaltung, nicht allgemein** --
  forum-speditionen.de bestand die Messung (13.477 Mitglieder).
