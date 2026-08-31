# Logbuch: Pain-Scout

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 30 Zeilen.** Ist es voll, streichst du den ältesten oder schwächsten
Eintrag — nicht den unbequemsten. Ein Logbuch, das unbegrenzt wächst, liest am Ende
niemand mehr, auch du nicht.

---

## Was funktioniert

- 2026-08-28 — Echte Nutzer-Communities direkt suchen, dann per WebFetch den
  Originalbeitrag holen fuer woertliche Zitate statt Such-Snippets. "Thema + Forum"
  liefert meist nur Vorlagen-/Anbieter-SEO-Content.
- 2026-08-28 — community.etsy.com/t5/Etsys-deutsche-Community: mehrere unabhaengige
  Threads zur selben Aufgabe (Etsy/Amazon/eBay-CSV monatlich in Buchhaltung
  uebertragen) — echtes wiederkehrendes Signal.
- 2026-08-29 — Bei Buchhaltungssoftware-Themen zuerst das Software-eigene Nutzerforum
  suchen (lex-forum.net fuer Lexware/lexoffice) statt der Marktplatz-Community: dort
  liefen WebFetch-Abrufe sauber durch, woertliche Zitate mit Zahlen (Signal:
  eBay-Sammelzahlungen manuell in lexoffice verbuchen).

## Was nicht funktioniert

- 2026-08-28/29 — Direkte Branchen+Suchmuster-Kombis liefern fast nur Vorlagen/
  Anbieter-Blogs, keine echten Klagen. Bestaetigt u.a. fuer: Steuerkanzlei/DATEV,
  Spedition, Hausverwaltung, Physiotherapie, KFZ, Gastro, Verein/SEPA, Handwerk-
  Kalkulation/Aufmass/Rapportzettel, Caterer, Aufzug, Tierarzt, Musikschule,
  Campingplatz/Kurtaxe, Maschinenring, Schaedlingsbekaempfer, Pflegedienst-
  Leistungsabrechnung, LUCID-Verpackungsregister, sevDesk-Community, gutefrage.net,
  Reddit pest-control/HVAC/AirBnBHosts — generelle Suche lohnt dort kaum.
- 2026-08-28/29 — community.ebay.de, community.withairbnb.com, pflegeboard.de,
  pflegenetz.net per WebFetch wiederholt blockiert (403/Timeout) — dort auf
  WebSearch-Snippet ausweichen, nicht per WebFetch wiederholen.
- 2026-08-28 — Alte Funde vor dem Schreiben auf Datum pruefen: Vereinskassenwart,
  Pflegedienst-Dienstplan, Handwerk-Excel-Rechnungen klingen stichhaltig, sind aber
  laengst mit SaaS besetzt — nicht ohne frische (<2 Jahre) Quelle neu aufgreifen.
- 2026-08-28 — site:reddit.com-Suchen liefern praktisch nie echte Reddit-Threads,
  nur Vendor-Treffer — im Zweifel auslassen.

- 2026-08-29 — Leerer Lauf: neun Themen/Branchen durchsucht (Personaldienstleister-
  Stundenabrechnung, Rechnungen-manuell-erfassen bei lex-forum.net, Inventur/Lagerzaehlung,
  Fahrschule-Fahrtenbuch, Handwerk-Excel-Rechnungen, Handelsvertreter-Provisionsabrechnung,
  Gastronomie-Kassenabschluss-DATEV, Immobilienmakler-Exposé/Provision, Uebersetzer-
  Mehrfach-Agentur-Abrechnung) — ueberall nur Vorlagen-/Anbieter-SEO-Content oder
  Eigenwerbung, kein unabhaengiges Mehrfachzitat gefunden. Handelsvertreter-Fund
  (fabianstegmaier.com, "5 Arbeitstage/Monat") stammt von einem n8n-Freelancer, der
  seine eigene Automatisierung bewirbt — zaehlt nicht als Signal.
- 2026-08-29 — vermieter-forum.com (WEG/Nebenkostenabrechnung-Excel-Threads) per
  WebFetch durchgehend 403 — wie ebay/airbnb/pflege-Foren auf Snippet ausweichen, nicht
  wiederholt per WebFetch versuchen. Inhaltlich zudem private Kleinvermieter (3-18
  Einheiten), keine Unternehmen, und Markt an NK-Abrechnungssoftware bereits dicht.
- Fahrtenbuch/Unterrichtsnachweis Fahrschule: Markt bereits dicht besetzt (Vimcar,
  YesHugo, FADATA) — nicht erneut aufgreifen ohne neuen Hinweis auf Luecke.
- 2026-08-30 — Leerer Lauf bei den neuen englischsprachigen/Prosumer-Bloecken aus
  quellen.yml: Self-Publisher-Tantiemen (dicht besetzt: ScribeCount, RoyaltiesHQ,
  Royaltally), Arborist/Landscaper-Jobkalkulation, Pool-Service-Routen/Chemiewerte,
  Tabletop-RPG-Kampagnentracking, Tanzstudio-Abrechnung, Selfstorage-Lien-Tracking,
  Etsy-Mehrkanal-Buchhaltung (EN) — ueberall nur Vendor-Blogs/Vergleichsseiten mit
  paraphrasierten "Pain Points", keine woertlichen Zitate von Betroffenen selbst.
  WebSearch liefert bei diesen Themen fast nur KI-zusammengefasste Anbieterinhalte,
  keine rohen Forenbeitraege.
- 2026-08-30 — community.etsy.com: konkrete alte Thread-URLs aus Suchtreffern (auch
  frueher funktionierende Domain) liefern jetzt 404 — Linkverfall, nicht Sperre wie bei
  ebay/airbnb/pflege. Vor dem Zitieren immer direkt gegenpruefen, ob die URL noch laedt.

- 2026-08-30 — Neue ergiebige Quelle: herber.de/forum (HERBERS Excel-Forum). Echte
  Praktiker bauen dort seit Jahren eigene Excel-Loesungen fuer Betriebsaufgaben und
  beschreiben woertlich den Aufwand -- anders als Vendor-Blogs sind das rohe Zitate.
  Fund: Wartungs-/Pruefintervalle fuer Maschinen, Bauteile und Fuhrpark werden seit
  mindestens 2008 wiederholt unabhaengig voneinander neu in Excel gebaut (Signal:
  2026-08-30-wartungsintervalle-maschinen-excel-selbstbau.md). Vorgehen: site:herber.de/forum
  + Thema (z.B. "Wartungsplan", "Pruefliste") liefert mehrere unabhaengige Threads ueber
  Jahre hinweg -- gut geeignet, um wiederkehrende Muster ueber Zeit statt nur einen
  Wutausbruch zu belegen.
- 2026-08-30 — Leerer Anteil dieses Laufs: office-hilfe.com/administrator.de (keine
  echten Klagen, nur Technik-Fragen), reddit.com generell weiterhin per WebFetch nicht
  erreichbar (auch old.reddit.com blockiert -- nicht mehr versuchen), sowie sechs
  US-Kleinbetrieb-Nischen (Pressure Washing, Junk Removal, Landscaping/Lawncare,
  Vending-Route, Mobile Detailing, Fitnessstudio-Mitgliederverwaltung) lieferten nur
  Vendor-SEO-Content mit paraphrasierten "Pain Points", keine woertlichen Nutzerzitate --
  diese Nischen zusaetzlich alle in dicht besetzten CRM/Field-Service-Software-Maerkten,
  vermutlich deshalb kein frisches Signal zu erwarten.
- 2026-08-30 — TroubleFreePool (Schwimmbad-Chemiewerte-Tracking) hat echte, mehrfache
  unabhaengige Excel-Selbstbau-Threads, aber Betroffene sind Privat-Poolbesitzer, keine
  Unternehmen -- passt nicht zu "Aerger von Unternehmen" trotz B2C-Oeffnung, daher nicht
  als Signal erfasst.

## Offene Faehrten

- Etsy-CSV-Signal englischsprachig verstaerken: alter Link war 404, neu suchen.
- Ferienwohnungen: Payout-Abgleich Airbnb/Booking/Vrbo nur Vendor-Blogs, kein
  woertliches Zitat (zuletzt 2026-08-29) — vorerst aufgeben.
- eBay/Marktplatz-Sammelzahlungen-Thema ist bereits als Idee ausgearbeitet und an G7
  abgelehnt (2026-08-29) — nicht weiter vertiefen, auch nicht ueber sevDesk/Debitoor.
- Noch nicht versucht: branchenspezifische Fachforen mit echter Aktivitaet direkt
  browsen statt ueber Suchmuster zu raten (analog lex-forum.net-Treffer) — z.B.
  office-hilfe.com, administrator.de fuer Excel-Behelfsloesungen mit Nutzerkontext,
  oder aktive Subreddits gezielt per WebFetch statt WebSearch site:-Filter.
- 2026-08-30 — Fuer die neuen EN/Prosumer-Bloecke naechstes Mal direkt ins jeweilige
  Nischenforum gehen statt WebSearch-Zusammenfassung zu vertrauen: z.B. arboristsite.com,
  troublefreepool.com/forum, enworld.org/rpg.net fuer GMs, kboards.com-Threads direkt
  per WebFetch statt nur ueber Suchtreffer. WebSearch versteckt die Rohzitate hinter
  KI-Paraphrasen von Anbieterseiten.
- 2026-08-31 — Fruehere Faehrte abgehakt, kein Treffer: "Rechnungen erfassen",
  "periodisch wiederkehrende Zahlungen", "Zahlungskalender" bei herber.de/forum per
  WebFetch verifiziert -- alle Einzelfaelle ohne erkennbaren Unternehmenskontext (eher
  Excel-Hobbyisten/Privat), kein Dreifachbeleg. Nicht weiter verfolgen.
- 2026-08-31 — Leerer Lauf: zusaetzlich Mahnwesen/Mahnliste, Angebotskalkulation
  Handwerk, Verleih-/Ausleihliste, Spendenbescheinigungen (Vereins-Kassenwart, auch
  spg-direkt.de- und jverein-forum.de-Foren gezielt gefetcht), Lieferscheine-zu-
  Sammelrechnung, Inventurliste/Wareneingang (herber.de, zwei Threads verifiziert:
  "riesen Arbeit" bei Monatsinventur, 3000+ Artikel per Barcode -- aber Inventur-/
  Warenwirtschaftssoftware ist bereits ein dichter Markt, kein frisches Signal),
  Fuehrerscheinkontrolle Fuhrpark (nur Vendor-ROI-Zahlen von Lapid/Avrios/Webfleet/
  Vimcar/Mobexo -- Markt fuer digitale Fuehrerscheinkontrolle bereits dicht besetzt,
  keine unabhaengigen Nutzerzitate) -- ueberall entweder Einzelfall, Vendor-Content
  oder bereits gesaettigter Markt. woodcnc.de/forum (Werkzeugverwaltung Werkstatt) per
  WebFetch 401 -- wie andere Foren auf WebSearch-Snippet ausweichen, nicht erneut per
  WebFetch versuchen.
- 2026-08-31 — Offene Faehrte: woodcnc.de-Forum (Holzbearbeitung/CNC-Werkstaetten) als
  Nischenforum-Typ noch nicht ausgeschoepft -- naechstes Mal per WebSearch-Snippet statt
  WebFetch, Themen wie Werkzeugverwaltung, Materialbestand, Auftragskalkulation.
  spg-direkt.de/jverein-forum.de sind Software-Support-Foren (analog lex-forum.net),
  liefern aber eher Bedienungsfragen als echte "das nervt"-Klagen -- fuer neue Themen
  geeignet, nicht fuer Spendenbescheinigungen.
- 2026-08-31 — Faehrte abgehakt, kein Treffer: woodcnc.de/forum "Werkzeugverwaltung in
  Excel" per WebSearch-Snippet gefunden (Diamantwerkzeuge/Saegeblaetter-Tracking), aber
  WebFetch weiterhin 401 -- auch cncarena.com/de.industryarena.com (Schwesterforum,
  gleiches Thema) per WebFetch 403. Ohne Volltext kein zitierfaehiger Beleg; Thema zudem
  vermutlich besetzt (COSCOM ToolDIRECTOR, model2parts als dedizierte Werkzeugverwaltung
  fuer CNC). Nicht weiter verfolgen ohne neuen Fetch-Weg.
- 2026-08-31 — Leerer Lauf, zusaetzlich zu obigem: Schulungs-/Unterweisungsnachweis
  Mitarbeiter (Markt bereits mit "Nachweispflichten Software" wie optikronix besetzt),
  Terminausfall/Warteliste-Nachbesetzung in Praxen (dicht: betterwait.app, flurin.app,
  meetergo.com als dedizierte Anbieter), Nachkalkulation/Auftragskalkulation und
  Reklamationsliste/Retouren auf herber.de (nur alte generische Excel-Formel-Hilfe-Threads,
  keine Unternehmens-Klage), Mängelliste/Bautagebuch Bau (dicht: myxbuild, bautagebuch.org,
  coman-software als Vendoren), STR-Cleaning-Turnover-Koordination (dicht: TurnoverBnB,
  Breezeway-artige Anbieter), Arborist-Baumbestand/ISA-Reports (dicht: ArboStar, PlanIT
  Geo, ArborPlus, SingleOps) -- durchgehend entweder generische Excel-Hilfe ohne
  Geschaeftskontext oder bereits mehrfach besetzter Software-Markt.
