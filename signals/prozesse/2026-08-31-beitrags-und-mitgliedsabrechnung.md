---
typ: prozess
erfasst: 2026-08-31
auftrag: Beitrags- und Mitgliedsabrechnung mit Zahlungsnachlauf
vorgang: Ein Bestand wiederkehrend zahlender Mitglieder wird je Turnus abgerechnet; der Betrieb erzeugt je Mitglied eine Forderung nach dessen Tarif, zieht sie per Mandat ein, gleicht den Rueckfluss ab und verfolgt jeden fehlgeschlagenen Einzug einzeln in einer Eskalationskette mit Fristen, bis er bezahlt, erlassen oder die Mitgliedschaft beendet ist.
branchen:
  - name: Eingetragene Vereine in Deutschland (darin 86.000 Sportvereine) | betriebe: 615.759 | quelle: ZiviZ-Survey, Grundgesamtheit der Erhebungswelle, ziviz.de, abgerufen 2026-08-31; Sportvereine DOSB Bestandserhebung 2025
  - name: Kommerzielle Fitnessclubs USA | betriebe: 55.000 | quelle: Health & Fitness Association 2025, wiedergegeben bei healthandfitness.org, abgerufen 2026-08-31
  - name: Tanz-, Kampfsport- und Musikstudios mit Kursbetrieb, englischsprachiger Raum | betriebe: 48.000 | quelle: signals/maerkte/2026-08-30-tanz-kampfsport-und-musikstudios-englischsprachig.md (konservatives Ende; optimistisch 134.000)
  - name: Fitness- und Gesundheitsanlagen Deutschland | betriebe: 9.647 | quelle: DSSV, Eckdaten der deutschen Fitnesswirtschaft, Stand Ende 2025, dssv.de, abgerufen 2026-08-31
vereinigung: 728.406 (konservativ; Ueberschneidung USA siehe Abschnitt 2)
kern: Bestand mit Tarif und Mandat, Turnuslauf erzeugt Forderungen, Einzug, Abgleich des Rueckflusses, Fehlschlagliste, getaktete Eskalation, Konsequenz bei Nichtzahlung.
schale: Tarifsystematik und Kuendigungsrecht -- Familienrabatt und Ruhendstellung im Studio, Beitragsstaffel nach Lohnsumme bei der Kammer, Satzung und Vereinsausschluss beim Verein.
schale_groesser_als_kern: nein
horizontal_besetzt: ja
horizontal_werkzeug: Stripe Billing (0,7 Prozent des Abrechnungsvolumens, Smart Retries und Mahnlauf inbegriffen, Wiedereinzugsquote 55 bis 56 Prozent), GoCardless fuer SEPA (keine Gebuehr bei fehlgeschlagenem Einzug), Chargebee (frei bis 250.000 USD kumuliertem Volumen), Recurly. Dazu eine eigene horizontale Produktkategorie allein fuer den Nachlauf ("dunning management software", Churn Buster ab 249 USD, Baremetrics Recover, ProsperStack). Es gibt nichts, was diese Werkzeuge am Kern nicht koennen -- die Luecke liegt nur in der Schale, und die ist klein.
vertikal_anbieter: mehr als 344 -- SoftwareAdvice fuehrt in der Kategorie "Membership Management" 344 Produkte (abgerufen 2026-08-31). Je Branche u.a.: Verein/Verband/Kammer -- GRUEN VEWA, Linear Memberware, campai, easyVerein, ClubDesk, Webling, WISO MeinVerein, verein.cloud, SEWOBE, Clubway, IntelliVerein; Studio -- DanceStudio-Pro, Jackrabbit, Kicksite, Gymdesk, Zen Planner, PushPress, Class Manager, 1club; branchenneutral in denselben Listen -- WildApricot, TeamUp, MemberPress, Novi AMS, MemberLeap.
erreichbar_ueber: aktive Suche und Vergleichsportale (Capterra, SoftwareAdvice, G2, OMR Reviews, trusted.de) -- belegt, aber von 344 gelisteten Produkten und vier Nulltarifen vollstaendig besetzt
suchwort: "membership management software" / "Vereinssoftware Mitgliederverwaltung" / "dunning management software" -- drei Formulierungen, die aber in dieselben Verzeichnisse und teils auf dieselben Anbieter fuehren (Webling steht als deutsche Vereinssoftware auf Platz 1 der englischsprachigen SoftwareAdvice-Kategorie)
preis_plausibel: 8 EUR (unter dem billigsten zugeschnittenen Vollprodukt: WISO MeinVerein Web XS 10 EUR bis 100 Mitglieder; Preisboden im Vorgang: 0 EUR)
kunden_erreichbar: 728 (ein Promille von 728.406) -- Promille, weil der Kanal zwar existiert, aber von 344 Produkten belegt ist
monatsumsatz: 5.827 EUR
traegt_5000: ja
befund: tot
---

# Rund 728.000 Organisationen ziehen denselben wiederkehrenden Beitrag ein und verfolgen denselben Fehlschlag nach -- und genau dafuer existiert seit Jahren eine eigene horizontale Produktkategorie mit 344 Eintraegen

Dieses Profil widerspricht sich in zwei Feldern, und das ist Absicht: `traegt_5000: ja`
bei `befund: tot`. Die Rechnung nimmt die Schwelle formal, der Vorgang ist trotzdem der
am dichtesten besetzte der ganzen Liste. Die Begruendung steht in Abschnitt 7.

## 1. Der Vorgang

Fuenf Merkmale, jedes einzeln pruefbar. Eine Branche zaehlt nur mit, wenn alle fuenf zutreffen:

1. **Bestand statt Auftrag.** Es gibt eine Liste von Personen, die dauerhaft zahlen —
   nicht Rechnungen je erbrachter Leistung.
2. **Fester Turnus, individueller Betrag.** Monatlich, quartalsweise oder jaehrlich, aber
   je Mitglied nach Tarif verschieden (Ermaessigung, Familie, Beitragsstaffel, Ruhendstellung).
3. **Der Betrieb holt das Geld.** Lastschriftmandat oder hinterlegte Karte; der Betrieb
   loest den Einzug aus, nicht das Mitglied.
4. **Der Fehlschlag ist ein eigener Vorgang.** Rueckbuchung, abgelaufene Karte, gedeckte
   Ablehnung: daraus entsteht eine Nacharbeitsliste, die getaktet abgearbeitet wird —
   Erinnerung, Mahnung, Gebuehrenweiterbelastung, erneuter Einzugsversuch.
5. **Am Ende steht eine Konsequenz.** Sperre, Kuendigung, Vereinsausschluss. Ohne sie ist
   der Nachlauf freiwillig und wird nicht bezahlt.

Merkmal 4 ist das trennende. Wer Beitraege einzieht und Rueckbuchungen einfach abschreibt,
macht nur Abrechnung; der Vorgang dieses Profils ist die **Fehlschlagverfolgung**.

## 2. Wer ihn macht

| Branche | Betriebe | Quelle, abgerufen 2026-08-31 |
|---|---:|---|
| Eingetragene Vereine Deutschland | 615.759 | ZiviZ-Survey, Grundgesamtheit der Erhebungswelle |
| Kommerzielle Fitnessclubs USA | 55.000 | Health & Fitness Association 2025 |
| Tanz-, Kampfsport-, Musikstudios englischsprachig | 48.000 | Repo-Profil vom 2026-08-30, konservatives Ende |
| Fitness- und Gesundheitsanlagen Deutschland | 9.647 | DSSV Eckdaten, Stand Ende 2025 |
| **Summe** | **728.406** | |

**Was ich nicht doppelt zaehle.** Die 86.000 Sportvereine der DOSB-Bestandserhebung 2025
sind eine Teilmenge der 615.759 eingetragenen Vereine, nicht eine eigene Zeile.

**Was unsauber bleibt.** Die HFA zaehlt "commercial fitness clubs", die
IBISWorld-Zahlen des Studioprofils zaehlen Tanz- und Kampfsportstudios; ob die HFA
Boutique-Studios mitzaehlt, ist nicht offengelegt. **Die beiden US-Zeilen ueberschneiden
sich moeglicherweise um einen unbekannten Betrag.** Die Vereinigung waere dann kleiner;
am Befund aendert das nichts, weil er nicht an der Groesse haengt.

**Was ich bewusst weglasse, und warum:**

- **Selfstorage, 61.856 Standorte** (Repo-Profil 2026-08-30). Der Einzug ist derselbe,
  der Nachlauf ist es nicht: Aus dem Zahlungsausfall wird ein gesetzlich getakteter
  Pfandrechtslauf je US-Bundesstaat mit Einschreiben, oeffentlicher Bekanntmachung und
  Versteigerung. Das ist eine Zwangsverwertung, keine Zahlungserinnerung — Merkmal 4 und 5
  haben dort eine andere Bauart. Ausserdem dreifach besetzt (sieben Mitteilungsdienste,
  sechs Auktionsplattformen, Late2Lien seit 2012).
- **Campingplaetze, rund 3.100.** Die Dauercamper-Jahresabrechnung ist eine
  Verbrauchsabrechnung mit Zaehlerablesung, einmal jaehrlich, ohne Turnuseinzug. Steht
  bereits in `signals/prozesse/2026-08-30-verbrauchsabrechnung-mit-zaehlerablesung.md`.
- **Hausverwaltungen fuer Wohnungseigentum.** Das Hausgeld folgt dem Wirtschaftsplan nach
  WEG; der Nachlauf endet im gerichtlichen Mahnverfahren. Anderes Recht, andere Kette.
- **Abo-Commerce, Verlage, SaaS-Anbieter.** Sie machen den Vorgang unstreitig — aber sie
  sind die Stammkundschaft von Stripe Billing und Chargebee. Sie mitzuzaehlen wuerde die
  Vereinigung ins Unbegrenzte treiben und genau das verdecken, was Abschnitt 4 zeigt. Ich
  nenne sie dort als Beleg, nicht hier als Zeile.
- **Krankenkassen und Versicherer mit Beitragseinzug** fallen unter G1 und zaehlen nicht mit.

Der Zahlungsbereitschaftsbeleg ist im Studioprofil vom 2026-08-30 belegt: 10 bis 15
Wochenstunden Verwaltung bei 200 bis 300 Schuelern, Beitragsabrechnung und Nachlauf als
groesster Einzelposten, rund 11.200 USD im Jahr an Personalkosten.

## 3. Kern und Schale

**Der Kern ist gross und ueberall gleich.** Stammdaten mit Tarif und Mandat, ein
Turnuslauf, der je Mitglied eine Forderung erzeugt, eine Einzugsdatei, ein Abgleich des
Rueckflusses, eine Fehlschlagliste, eine Eskalationskette mit Fristen, eine Konsequenz.
Das laesst sich nicht als eine Rechenvorschrift in einem Satz beschreiben — es ist ein
Produkt, kein Feld.

**Die Schale ist klein.** Sie besteht aus Tarifsystematik und Kuendigungsrecht:
Familienrabatt und Ruhendstellung im Studio, Beitragsstaffel nach Lohnsumme oder
Mitarbeiterzahl bei der Kammer, Guertelgrad im Kampfsport, Satzung und Ausschlussverfahren
beim Verein. Alles davon ist Konfiguration, nicht Programmierung — und es ist die
haltbare Sorte Konfiguration aus meiner Lehre vom 2026-08-30: einmal gesetzt, jahrelang
gueltig, kein Abonnement fortgeschriebener Fremddaten.

**Damit ist die Antwort auf Frage 3 die beste, die diese Rolle bisher hatte** — und genau
deshalb ist sie wertlos. Ein grosser gemeinsamer Kern mit kleiner Schale ist die
Absterbezone "hat schon jemand gebaut". Abschnitt 5 zeigt, dass es 344 sind.

## 4. Das horizontale Werkzeug

Es gibt eines, es kostet fast nichts, und es hat den Nachlauf als Kernfunktion:

| Werkzeug | Preis | was es fuer diesen Vorgang tut |
|---|---|---|
| **Stripe Billing** | 0,7 % des Abrechnungsvolumens | Abonnements, Kundenportal, **Smart Retries** und Mahnlauf inbegriffen; erklaerte Wiedereinzugsquote 55 bis 56 Prozent |
| **GoCardless** | 1 bis 3 % je nach Volumen | SEPA-Lastschrift, **keine Gebuehr bei fehlgeschlagenem Einzug** |
| **Chargebee** | frei bis 250.000 USD kumuliertem Volumen | Abrechnung und Mahnwesen |
| **Recurly** | 249 USD/Monat + 0,9 %, erste 40.000 USD frei | Abrechnung und Dunning |

Und es gibt eine **eigene Produktkategorie allein fuer Merkmal 4**, mit eigenen
Vergleichslisten fuer 2026: "dunning management software" / "failed payment recovery" —
Churn Buster (ab 249 USD), Baremetrics Recover, ProsperStack, Gravy, WorkAid Dunning
(25 USD, dazu ein Gratistarif). Die Listen nennen Wiedereinzugsquoten von 55 bis 80
Prozent gegen 15 bis 25 Prozent bei einfachen Wiederholungen.

**Was diese Werkzeuge nicht koennen, ist die Schale, und die ist klein.** Stripe kennt
keine Beitragsstaffel nach Lohnsumme und kein Ausschlussverfahren nach Satzung. Das ist
der Rest, der einem Nischenprodukt bliebe — und dafuer gibt es Abschnitt 5.

Fuer den deutschen Vereinsteil ist das horizontale Werkzeug ausserdem die
Vereinssoftware selbst: Ruecklastschriften werden dort "per Mausklick in eine Rechnung mit
Ruecklastschriftgebuehr umgewandelt" (SEWOBE), Clubway und WISO MeinVerein erkennen den
Rueckfluss automatisch.

Quellen: [Stripe Billing Pricing](https://stripe.com/billing/pricing),
[GoCardless SEPA-Kosten](https://gocardless.com/de/handbuch/artikel/was-sind-die-sepa-lastschrift-kosten-fuer-haendler),
[Chargebee Dunning](https://www.chargebee.com/blog/dunning-management-for-saas-business/),
[Churn Buster, Best Dunning Management Software](https://churnbuster.io/articles/best-dunning-management-software/),
[SEWOBE VereinsMANAGER Finanzen](https://www.sewobe.de/vereinssoftware/finanzen/),
alle abgerufen 2026-08-31.

## 5. Die vertikalen Anbieter

Hier kippt der Befund endgueltig, und zwar auf zwei Wegen.

**Erstens die Zahl.** SoftwareAdvice fuehrt in der Kategorie *Membership Management*
**344 Produkte** ("Showing 1 - 25 of 344 products", abgerufen 2026-08-31). Die Schwelle
aus `lehren.md` liegt bei 50. Gemessen wurden bisher: Spedition 25, Fahrschulen 57,
Kursbetrieb 132, Selfstorage 36. **344 ist der hoechste Wert, den diese Fabrik je
gezaehlt hat**, und er steht in genau der Kategorie, die diesen Vorgang benennt.

Die ersten zehn Eintraege sind bereits gemischt vertikal und horizontal: Webling
(Vereine, deutschsprachig), WildApricot, TeamUp, Brilliant Directories, ToucanTech,
Chmeetings (Gemeinden), Gymcatch, ClubRight, MemberPress, Novi AMS (Verbaende).
"Dues Management" wird dort als Kernfunktion mehrerer Produkte gefuehrt.

**Zweitens, und das ist das eigentliche Urteil: Die Vereinigung ist bereits gehoben.**
Nach meiner Lehre vom 2026-08-30 beweist die Kundenliste eines Anbieters besser als jedes
eigene Argument, dass ein Vorgang derselbe ist. **GRUEN VEWA** nennt auf einer
Landingpage: *Vereine, Verbaende, Kammern, Parteien, Gewerkschaften* — fuenf
Organisationstypen, ein Produkt, mit automatischer Beitragsberechnung nach Mitgliedsstatus,
Lohnsumme oder Mitarbeiterzahl, Staffelungen, Ober- und Untergrenzen, Lastschrifteinzug,
Mahnwesen und Zahlungsueberwachung. **Linear Memberware** macht dasselbe mit
"Ruecklaeuferbearbeitung und automatischem Mahnverfahren". Beide haben den
Vorgangsschnitt, den diese Rolle sucht, laengst vollzogen — inklusive der Schale aus
Abschnitt 3.

**Der Preisboden ist null, in beiden Sprachraeumen:** Webling gratis bis 50 Mitglieder,
ClubDesk mit dauerhaft kostenlosem Tarif fuer kleine Vereine, PushPress Free (4,99 Prozent
je Kartenzahlung), Class Manager ohne Monatsgebuehr, 1club gratis bis 100 Schueler.
Der Mechanismus ist derselbe, den `lehren.md` seit 2026-08-30 fuehrt: Wo wiederkehrend
Geld vom Endkunden durch die Software fliesst, refinanziert sich die Software aus dem
Zahlungsstrom. Bei genau diesem Vorgang **ist** der Zahlungsstrom der Vorgang.

Quellen: [SoftwareAdvice Membership Management](https://www.softwareadvice.com/membership-management/),
[GRUEN VEWA Mitgliederverwaltung](https://www.gruen.net/software/mitgliederverwaltung/),
[Linear Memberware](https://linear-software.de/mitgliederverwaltung/),
[trusted.de Vereinsverwaltung](https://trusted.de/vereinsverwaltung),
alle abgerufen 2026-08-31.

## 6. Der gemeinsame Kanal

**Es gibt ihn, und er ist besetzt.** Der Vorgang hat kein einziges Suchwort, aber drei,
die in dieselben Verzeichnisse muenden: "membership management software", "dunning
management software", "Vereinssoftware Mitgliederverwaltung". Dass es dieselbe
Trefferlandschaft ist, laesst sich zeigen: **Webling** — eine deutschsprachige
Vereinssoftware — steht auf Platz eins der englischsprachigen SoftwareAdvice-Kategorie.
Der negative Kanaltest aus meinem Logbuch faellt hier also **positiv** aus, und das ist
das schlechte Ergebnis: Die Branchen finden einander bereits im selben Regal.

Verzeichnisse: Capterra, SoftwareAdvice, G2, SoftwareConnect fuer den englischsprachigen
Raum; OMR Reviews, trusted.de, vergleich.org, softwareabc24 fuer den deutschen. Alle
fuehren fertige "Vergleich 2026"-Listen, mehrere davon von Anbietern selbst geschrieben
(ClubDesk betreibt einen eigenen "Vereinssoftware-Vergleich", ClubPayHub eine eigene
Bestenliste).

## 7. Die Rechnung

**Preis.** Belegt am vertikalen Nischenanbieter: WISO MeinVerein Web kostet 10 EUR (XS,
bis 100 Mitglieder), 20 EUR (S), 35 EUR (M, bis 500), 50 EUR (L); easyVerein ab 7 EUR;
DanceStudio-Pro 45 USD. Das ist der Preis fuer die **komplette** Verwaltung. Eine
Einzweckfunktion muss deutlich darunter liegen: **8 EUR** ist die Obergrenze, die ich
verteidigen kann — und selbst die nur gegen einen Preisboden von **0 EUR** (Webling,
ClubDesk, PushPress Free, Class Manager, 1club).

**Kundenzahl.**

    ein Promille:  728.406 × 0,001 =   728 Kunden × 8 EUR =  5.827 EUR im Monat
    ein Prozent:   728.406 × 0,01  = 7.284 Kunden × 8 EUR = 58.272 EUR im Monat

**Ich setze das Promille an.** G7 verlangt es, wenn der Kanal von den vorhandenen
Anbietern belegt ist, und der zweite Fall trifft hier haerter zu als irgendwo sonst: 344
gelistete Produkte, acht Vergleichsportale, fuenf Nulltarife.

**5.827 EUR im Monat. Das nimmt die Schwelle — und die Zahl ist trotzdem nichts wert.**
Sie steht hier, weil G7 sie verlangt, nicht weil sie etwas misst. Drei Gegenproben:

- Bei einem Preis von 6 statt 8 EUR: 4.370 EUR. Die Schwelle haengt an zwei Euro
  Preisannahme gegen einen Nullboden.
- Ohne die deutschen Vereine (die groesste und zugleich zahlungsschwaechste Zeile):
  112.647 Betriebe, ein Promille, 901 EUR.
- Das Promille unterstellt einen Markt mit freien Kunden. Bei 344 Produkten und einer
  Kategorie, die es seit Jahren gibt, waechst mit der Vereinigung nur der Nenner. Das ist
  derselbe Messfehler, den ich am 2026-08-30 beim Unterweisungsnachweis notiert habe
  (2,1 Mio. Betriebe, 60.900 EUR, eindeutig tot) — **jetzt zum dritten Mal.**

`traegt_5000: ja`, `befund: tot`. Ich mache die Rechnung nicht passend.

## Die Luecke

**Es klafft keine, und dieser Vorgang zeigt am deutlichsten von allen sieben, warum.**

Alle Vorbedingungen dieser Rolle sind erfuellt, jede einzelne besser als in den sechs
Profilen davor: die groesste je gezaehlte Vereinigung (728.406), der grosse gemeinsame
Kern, die kleine und haltbare Schale, eine belegte teure Handarbeit (10 bis 15
Wochenstunden je Studio), ein selbstbedienbarer Suchkanal, keine Erlaubnispflicht, kein
Verband als Wettbewerber. Und trotzdem:

**Ein Vorgang, den 728.000 Organisationen ueber alle Branchengrenzen hinweg gleich
ausfuehren, ist nicht deshalb eine Luecke, sondern deshalb eine Produktkategorie.** Der
Kern ist so gross und so gleich, dass er laengst als eigenes Regal existiert — mit einem
Namen ("membership management", "dunning management"), 344 Eintraegen, acht
Vergleichsportalen und einer Unterkategorie allein fuer Merkmal 4. Die Schale, die
uebrig bliebe, ist so klein, dass sie nicht einmal einen eigenen Anbieter traegt: GRUEN
VEWA hat sie fuer fuenf Organisationstypen zugleich mitgebaut.

Das ist dieselbe Absage wie beim Leistungsnachweis an den Kostentraeger vom 2026-08-30,
aber aus dem entgegengesetzten Grund. Dort hatte der **Gesetzgeber** den Vorgang
branchenuebergreifend definiert (§ 302 SGB V), und die Antwort war eine ganze Industrie.
Hier hat der **Zahlungsverkehr** ihn branchenuebergreifend definiert: Sobald wiederkehrend
Geld eingezogen wird, ist der Vorgang identisch bis auf den Tarif — und die
Zahlungsdienstleister haben ihn zum Preis von 0,7 Prozent des Volumens eingepreist.

Fuer den Ideator bleibt daraus kein Fund, sondern eine Regel: **Nicht suchen, wo der
Vorgang gleich ist, sondern wo er gleich ist und niemand ihn benannt hat.** Ein Vorgang
mit eigenem Kategorienamen in vier Softwareverzeichnissen ist nie unbesetzt. Der Test
kostet einen Abruf und haette diesen Lauf in fuenf Minuten entschieden.

## Was unklar ist

- **Wie viele der 615.759 eingetragenen Vereine ueberhaupt per Lastschrift einziehen.**
  Der Vorgang ist konstitutiv fuer einen Verein, aber ein Kleingartenverein mit dreissig
  Mitgliedern nimmt Ueberweisungen und mahnt muendlich. Eine Quote habe ich nicht
  gefunden. Die groesste Zeile der Vereinigung ist damit die unsicherste — und zugleich
  die mit dem Preisboden null.
- **Die Ueberschneidung zwischen den 55.000 US-Fitnessclubs (HFA) und den 48.000
  Studios (IBISWorld).** Ob die HFA Boutique-, Tanz- und Kampfsportstudios mitzaehlt,
  legt sie nicht offen. Beide Zahlen stehen ungekuerzt in der Tabelle; die Vereinigung
  ist deshalb eher zu gross als zu klein.
- **Die US-Clubzahl selbst schwankt.** 55.000 kommerzielle Clubs (HFA 2025) gegen
  114.370 "fitness clubs" aus einer Anbieterauswertung (Gymdesk). Ich rechne mit der
  unteren, anbieterunabhaengigen Zahl.
- **Wie viele der 344 Produkte den Nachlauf (Merkmal 4) wirklich koennen** und wie viele
  nur eine Mitgliederliste sind, habe ich nicht ausgezaehlt. Bei zwoelf namentlich
  geprueften Anbietern war Mahnwesen jedes Mal dabei; die Stichprobe genuegt fuer das
  Urteil, nicht fuer eine Quote.
- **Der Preis von GRUEN VEWA und Linear Memberware** ist nicht oeffentlich (beide ueber
  Angebot). Der Preisanker der Rechnung stammt deshalb vom kleinen Ende (WISO MeinVerein,
  easyVerein), nicht vom Anbieter, der die Vereinigung tatsaechlich bedient. Fuer den
  Rechercheur, falls dieser Vorgang je wieder aufgerufen wird — was ich nicht empfehle.
