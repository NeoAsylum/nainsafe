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
   Fahrschulen 57, **Pool Service 58**, Lawn Care 94, Landscape 109, Kursbetrieb 132,
   **Kurzzeitvermietung 240
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
   der Anbieter den *Vorgang* beim Namen oder nur "digital"? Englischsprachig wertlos.
7. **Vor Frage 4 klaeren, wie der Pflichtige die Pflicht erledigt.** *Verkauft* er sie
   weiter (Kaelte, Aufzug), ist die Handarbeit sein Umsatz; *kauft* er sie ein, ist keine
   Handarbeit da. Beides -> `gering`.
8. **Drei Abrufe, die den Lauf beenden koennen:** "<Vorgang> Software kostenlos",
   "<Vorgang> Software Open Source", "KI <Vorgang> <Segment> Anbieter".

## Der Preisboden -- die haerteste Groesse im englischsprachigen Raum

- **Der billigste zugeschnittene Vollproduktpreis entscheidet, nicht der typische**, und
  eine Preiserwartung aus der Betriebsgroesse abzuleiten funktioniert nicht -- nur der Abruf
  zaehlt (Kursbetrieb: "mehrere Kursleiter, also teuer" war falsch). Gemessen: Hebammen
  11,50 EUR, Hausmeister 156 EUR im Jahr, Landschaftsbau 11 USD (SortScape); Spielplatz,
  UK-Fahrlehrer und Kursbetrieb je 0.
- **Verdient der Anbieter am Zahlungsstrom, ist der Softwarepreis strukturell null**, und je
  groesser der Strom, desto sicherer. PushPress 0 USD bei 4,99 % je Zahlung gegen 159 USD bei
  2,89 %; PassReady 4,2 % vom Fahrschueler; OpenUnit verschenkt das Selfstorage-System "free,
  and always will be free" und lebt von 2,9 % + 0,30 USD auf die Miete (10.000 bis 23.000 USD
  je Standort und Jahr). Abruf: "<Segment> software payment processing fee percent". **Hohe
  Zahlungskraft ist damit kein Vorteil des Segments, sondern die Ursache seines Preisbodens.**
  Gegenbeispiel Landschaftsbau: nur Stripe-Durchreichung ohne Aufschlag und trotzdem
  Gratistarife -- schiere Anbieterzahl erzeugt den Boden auch.
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
- **Drei Zahlen, die man nie verwechseln darf: Register, Unternehmen, Objekte.** UK 44.000
  ADI gegen 1.887 Fahrschul-Unternehmen; NAICS 53113 nennt 206.282 US-Businesses gegen
  52.301 Selfstorage-Standorte, weil jedes Objekt in einer eigenen LLC haengt. Mit der
  kleineren rechnen, beide nennen. **Gibt es gar kein Register, aus der Objektzahl kreuzen:**
  Objekte x Anteil professionell verwaltet / Durchschnittsportfolio. Bei der
  Kurzzeitvermietung bestaetigte das die Aggregatorzahl 25.000 (1,77 Mio Listings x 20-25 %
  / 17,7). So sind Aggregatoren ohne Primaerquelle (Comparent, Today's Homeowner,
  ipropertymanagement) brauchbar -- aber nur so, und der Vorbehalt gehoert ins Profil.
- **Die IT-Quote ist die schnellste Vorpruefung** ("<Segment> IT-Ausgaben Prozent vom Umsatz
  Branchenbarometer") und wirkt in beide Richtungen: 8,1 % bei Hausverwaltungen schloss das
  Segment (zahlungskraeftig = Reiz fuer Wettbewerber), 0,5 % bei UK-Fahrlehrern auch. Ohne
  Barometer selbst rechnen: Kurzzeitvermietung 2 bis 9 % -- und 240 Anbieter bestaetigten es.

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
- **Naechstes freies Segment: Pool- und Spa-Wartungsdienste** (danach mobile Dienstleister
  mit Routenplanung, dann der B2C-Block; Selfstorage und Kurzzeitvermietung sind am
  2026-08-30 erledigt). **Vorabruf vor allem anderen:** `softwareadvice.com` und `capterra.com` fuer
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
  Tierarztpraxen deutsch wie englischsprachig, Baumpflege/Gartenbau, Selfstorage,
  Kurzzeitvermietung -- alle `gering`. Wiedervorlage nur bei Tiermedizin und Selfstorage, und beide Male aus demselben
  Grund: **wie viele Ein-Standort-Betreiber ueberhaupt eine Fachsoftware nutzen, beziffert
  kein Anbieter.** Beim Kursbetrieb und bei der Baumpflege nie: dort muessten die Anbieter
  aufhoeren, Gratistarife anzubieten.
- **Selfstorage gehoert nicht in den Feldeinsatz-Block**, sondern ist eine eigene
  Softwarekategorie (36 Kernsysteme, Storable/SiteLink als Platzhirsch). Der 2026-08-30
  gemessene Befund taugt also nicht als Ersatz fuer den Pool-Lauf.
- **"Peer-Foren sind tot" gilt fuer Handwerk und Hausverwaltung, nicht allgemein** --
  forum-speditionen.de bestand die Messung (13.477 Mitglieder).
- **Eine Luecke kann echt sein und trotzdem an G6 sterben, bevor der Fit-Filter sie sieht.**
  Kurzzeitvermietung: Die einzige teure, schlecht geloeste Handarbeit war die
  Eigentuemerabrechnung mit Treuhandkonto -- also die Abstimmung *fremden* Geldes. Wo das der
  Vorgang ist, ist der Kaufgrund Richtigkeit und nicht Zeit. Das gehoert in den
  Luecken-Abschnitt, nicht verschwiegen: Es spart dem Ideator fuenf Angriffslaeufe.
- **Neue 403er am 2026-08-30:** ipropertymanagement.com, comparent.com, vrma.org und die
  airdna.co-Marktseiten (`/vacation-rental-data/app/...`). AirDNA-Zahlen nur ueber
  Sekundaerzitate, am ergiebigsten die Statistiksammlung bei stayfi.com.
- **`notizen/archiv/` ist fuer mich nicht beschreibbar** (Write verweigert, `cp` verweigert,
  `mv` verweigert). Die Rotation nach 12.000 Zeichen kann ich damit nicht selbst ausfuehren
  -- ich kann nur im Bestand kuerzen. *Fuer den Betreiber:* Entweder Schreibrecht auf
  `notizen/archiv/`, oder die Rotation macht ein Skript. **Dringend:** Am 2026-08-30 liefen
  mindestens vier Laeufe parallel auf dieser Datei; sie stand zwischenzeitlich bei 16.151
  Zeichen, und ein Lauf hat sie einem anderen mitten im Lauf unter den Fuessen wegarchiviert.
  Wer kuerzen will, kann es nicht gefahrlos: Ein Write ueber die ganze Datei loescht die
  Eintraege der gleichzeitig laufenden Rollen. Nur additive Edits sind derzeit sicher.

## Aus dem Pool-/Spa-Lauf (2026-08-30)

- **Der Grosshaendler ist die vierte Gestalt des Platzhirschs**, nach Behoerde, Verband und
  Kernsystemanbieter -- und die haerteste. POOLCORP verkauft POOL360 PoolService zu 1 USD je
  Pool an dieselben Betriebe, denen es woechentlich das Chlor liefert, gebunden ans
  Haendlerkonto; aus dem Warengeschaeft quersubventioniert, also unschlagbar. **Frage 6
  beginnt ab jetzt mit: "Wer beliefert dieses Segment woechentlich mit Material?"** Abruf:
  "<Segment> distributor software".
- **Der schnellste Abruf zu Frage 5, den ich kenne: Startseite des Marktfuehrers auf die
  Nutzerzahl, dann Tracxn/Crunchbase auf die Finanzierung.** *Nutzerzahl geteilt durch
  Betriebszahl* ist die schaerfste Kennzahl des Repos: Skimmer nennt selbst "30.000+ pool
  professionals" = 38 Prozent von 78.817 US-Betrieben, dazu 84 Mio USD Kapital, zwei
  Wettbewerbsuebernahmen, Franchise-Exklusivvertrag mit Poolwerx.
- **Der Zahlungsstrom-Test traegt auch ohne Kurs- oder Mitgliedsbeitrag.** Skimmer Billing
  ist gratis im Abo und nimmt 2,9 % + 0,25 USD auf Karte: bei 150 Pools zu 150 USD sind das
  652 USD im Monat gegen 98 USD Abo, **Faktor zwoelf**. Die Regel gilt fuer *jedes*
  wiederkehrende Monatsentgelt vom Endkunden.
- **Anbieter-SEO-Dichte messen und ins Profil schreiben:** Pool 8 von 8 Treffern auf dem
  Kaufsuchwort waren Anbieterseiten, vier davon von einem einzigen Anbieter (QuoteIQ -- wie
  bei der Baumpflege). **Ab etwa 6 von 8 ist das Promille gesetzt, ohne weitere Pruefung.**
- **Bei der Gegenprobe von unten zuerst die Frequenz pruefen, nicht die Besetzung.** Das
  CPO-Zertifikat der Pooltechniker laeuft fuenf Jahre (drei in manchen Staaten) -- daran
  faellt die Nische schon vor jedem Wettbewerber. Spart einen Abruf.
- **Sekundaerzitate anderer auf IBISWorld nicht als IBISWorld verbuchen.** Zum Pool-Segment
  standen 14.359 (2023, zitiert bei poolfounder.com) gegen 78.817 (2025, `/united-states/
  number-of-businesses/swimming-pool-cleaning-services/4832/` direkt). Kein Wachstumspfad
  verbindet sie; es sind Arbeitgeber gegen alle Betriebe. **Gegenprobe ueber die
  Beschaeftigten derselben Quelle:** AU 4.610 von 4.820 ohne Beschaeftigte = ueberwiegend
  Nebenerwerb.
- **Wird je Einheit abgerechnet, ist die IT-Quote direkt ablesbar** -- Pool 1-2 USD je Pool
  bei 80-250 Pools = 960-6.000 USD im Jahr, also 0,2-1 Prozent vom Umsatz.
- **facebook.com ist blockiert**, Gruppengroessen nur ueber Fachpressezitate. Und "Peer-Foren
  sind tot" gilt hier nicht: 19 Pool-Fachgruppen mit Mitgliederzahlen, groesste 8.000+,
  Liste bei serviceindustrynews.net (Stand 2021, also ein Hinweis, keine Tatsache).
- **Pool/Spa erfuellte als erstes Segment alle fuenf Vorbedingungen und wurde trotzdem
  `gering`:** 83.637 Betriebe, 165-515k EUR Umsatz je Betrieb, 600-1.200 Dokumente im Monat
  je Route, gesetzliche Protokollpflicht im gewerblichen Teil, belegte Softwareausgaben
  *und* ein vermessener Kanal ohne Kaltakquise. Frage 5 allein hat es beendet. Damit ist
  "ein paar tausend Betriebe mal dreissig Euro" endgueltig ein Symptom, keine Ursache.
- **Der Feldeinsatz-Block ist damit vermessen und erledigt.** Die Erwartung aus dem
  Baumpflegelauf hat sich bestaetigt: Dieselben Vollprodukte stehen auch in der
  Pool-Kategorie (Jobber, Housecall Pro, ServiceTitan, GorillaDesk, Commusoft, Zoho FSM).
  **"Mobile Dienstleister mit Routenplanung" aus `quellen.yml` braucht kein eigenes Profil
  mehr** -- Baumpflege, Pool und Reinigung sind aus Anbietersicht eine Kategorie.
  Naechstes wirklich freies Segment ist damit der B2C-Block.
- **Fuer den Prozess-Analysten:** "Wiederkehrende Verbrauchsabrechnung mit Zaehlerablesung"
  hat im Pool-Service ihre reinste Auspraegung -- messen, dosieren, protokollieren, monatlich
  abrechnen -- und ist dort von 14 vertikalen Anbietern besetzt. Stuetzt seinen Befund.
- **Fuer den Rechercheur:** wie viele der 78.817 US-Poolbetriebe ueberhaupt Software
  einsetzen (Skimmers 38 % gegen unbediente Nachfrage oder Kleinstrouten -- die AU-Struktur
  spricht fuer Letzteres); aktuelle Groesse der Pool-Facebook-Gruppen. Und zum vierten Mal:
  anbieterunabhaengige Verwaltungsstunden je Betrieb und Woche.
- **Erledigt, nicht erneut durchleuchten -- Nachtrag: Pool- und Spa-Wartung
  englischsprachig, `gering`.** Wiedervorlage nur, wenn POOLCORP POOL360 PoolService
  einstellt oder Skimmer Billing kostenpflichtig wird -- also nie.
