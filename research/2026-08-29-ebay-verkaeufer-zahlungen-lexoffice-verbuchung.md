---
typ: recherche
signal: signals/pain/2026-08-29-ebay-verkaeufer-zahlungen-lexoffice-verbuchung.md
erstellt: 2026-08-29
segmentgroesse: nicht aktuell ermittelbar (letzte belastbare Zahl: 118.899 aktive gewerbliche eBay-Haendler in DE, Stichtag Februar 2015)
anbieter_gefunden: 20
preisspanne: 0,00-99,00 EUR/Monat fuer die Schnittstellenschicht, dazu 299,00 EUR einmalig (Speetax, Zweijahreslizenz)
ampel: rot
---

# Gewerbliche eBay-Verkaeufer ordnen ihre Sammelauszahlungen von Hand in Lexware Office zu — eine Aufgabe, fuer die der Softwarehersteller selbst vier namentliche Partner benennt und in seinem eigenen Hilfecenter einen davon empfiehlt

## 1. Groesse des Segments

**Keine aktuelle Zahl.** eBay veroeffentlicht seit Jahren keine Verkaeuferzahl fuer Deutschland
mehr — weder in den Quartalsmitteilungen noch in den deutschen Pressemeldungen, auch nicht in
denen, die ausdruecklich ueber deutsche Kleinhaendler berichten.

Was belegbar ist, ist alt:

| Kennzahl | Wert | Stand | Quelle |
|---|---|---|---|
| Aktive gewerbliche eBay-Haendler DE | **118.899** | Februar 2015 (Gebietsstand 31.12.2013) | wortfilter.de, „Statistik: 118.899 aktive gewerbliche eBay-Haendler" |
| Aktive Verkaeufer eBay.de (gewerblich + privat) | 125.732 | 2016 | wortfilter.de, „eBay Deutschland – Marktplatz in Zahlen" |
| Gewerbliche Verkaeufer eBay.de | „175.000 … sowie mehr als 100 grosse Haendler und Markenhersteller" | eBay-Factsheet, undatiert, dem Inhalt nach 2012/2013 | static.ebayinc.com, Factsheet |
| Befragte gewerbliche eBay-Verkaeufer DE (Stichprobe, keine Grundgesamtheit) | 1.377 | Meldung vom 19.03.2026 | retail-news.de zur eBay-Mittelstandsstudie |

(alle abgerufen 2026-08-29)

Die Definition der 118.899 ist eng und brauchbar: gezaehlt wurden nur Haendler, „die mindestens
eine Bewertung fuer getaetigte Verkaeufe (im Beobachtungszeitraum) erhalten haben". Der Autor
schreibt selbst dazu, „die Zahl der Haendler unterliegt einer starken Volatilitaet".

**Wie die Zahl zu lesen ist:** als Groessenordnung, nicht als Bestand. Elf Jahre sind zu lang,
um sie fortzuschreiben; verwertbar ist allein, dass die Gruppe **sechsstellig** ist und damit
die 500er-Schwelle dieser Fabrik um mehrere Zehnerpotenzen ueberschreitet. Die Segmentgroesse
ist hier ausdruecklich **nicht** der Ablehnungsgrund.

Die eigentlich relevante Groesse — gewerbliche eBay-Verkaeufer, **die Lexware Office nutzen** —
zaehlt niemand. Die beiden Raender: Lexware Office nennt „ueber 350.000" Kunden und bezeichnet
sich als Marktfuehrer der Online-Buchhaltung (trusted.de, Lexware-Office-Test 2026, abgerufen
2026-08-29); die Schnittmenge ist ein Produkt zweier Zahlen, von denen eine elf Jahre alt und
die andere eine Herstellerangabe ist. Der Ideator darf hier keine Zahl ansetzen.

Nicht ermittelbar sind ferner die DAC7/PStTG-Meldezahlen fuer eBay: das BZSt veroeffentlicht
nach § 9 Abs. 6 PStTG keine Fallzahlen gemeldeter Anbieter (Befund aus dem Etsy-Lauf vom
2026-08-28, unveraendert).

**Richtung des Marktes:** eBays Wachstum lag im Geschaeftsjahr 2025 auf dem Heimatmarkt; der
deutsche Marktplatzblog wortfilter titelte am 19.02.2026 „eBay Zahlen sind gut, aber nicht fuer
DE Haendler" und schreibt, das Wachstum finde „hauptsaechlich auf dem Heimatmarkt" statt
(abgerufen 2026-08-29). Eine deutsche Umsatz- oder Haendlerzahl nennt auch dieser Beitrag nicht.

## 2. Wer es heute bedient

Zwanzig Anbieter, in vier Schichten. Die erste Schicht loest **genau** die Aufgabe des Signals:
eBay-Sammelauszahlung aufschluesseln, Gebuehren trennen, nach Lexware Office uebergeben.

### Schicht 1 — eBay-Payments nach Lexware Office / lexoffice (5)

| Anbieter | Was es tut | Preis |
|---|---|---|
| **PayJoe** (payjoe.de) | Ruft die eBay-Zahlungsberichte per API ab, schluesselt jede Transaktion auf, uebergibt Erloese **und Gebuehren getrennt** ueber die HBCI-/Banking-Schnittstelle an Lexware Office; optionaler Belegabgleich mit den Lexware-Rechnungen, der offene Posten wird automatisch ausgeglichen. **Kein Billbee, keine Warenwirtschaft noetig** — PayJoe ist ein eigenstaendiges Vorsystem. | **4,20 EUR/Monat je Zugang + 0,05 EUR je exportiertem Datensatz** (unter 3.000/Monat), 20 EUR Startguthaben, „vertragsfrei & unverbindlich", keine Mindestlaufzeit, Restguthaben wird bei Kuendigung ausbezahlt. Optionaler Installationsservice 130 EUR |
| **Billbee** (billbee.io) | Offizieller Lexware-Partner. Auftragsimport aus eBay, Rechnungserstellung, automatischer Zahlungsabgleich, Uebergabe der Rechnungen an Lexware Office als Einnahmebelege | **ab 9,00 EUR/Monat netto** (Starter, bis 200 Bestellungen), keine Vertragsbindung, Test ohne Zahlungsdaten. Keine dauerhafte Gratisstufe |
| **DreamRobot** | Offizieller Lexware-Partner, cloudbasierte Warenwirtschaft, eBay-Anbindung mit Uebergabe an Lexware Office | 14 Tage kostenlos, Preis nicht auf der Lexware-Seite genannt |
| **Miracle Sync** (miraclesync.de) | Lexware-Technologiepartner; im Lexware-Hilfecenter **namentlich** als Weg fuer Zahlungsdienstleister-Transaktionen genannt | „ab 9 EUR/Monat", Preis skaliert mit der Zahl der Zahlungen (Suchtreffer; die Startseite nennt nur Stripe und keine Preise) |
| **sync4** (sync4.de, `lexware.de/sync4/`) | Zertifizierte Lexware-Schnittstelle, verbindet Lexware Warenwirtschaft mit Amazon und eBay | kein oeffentlicher Preis, nur Beratungstermin |

**Und der Hersteller selbst weist den Weg dorthin.** Auf `lexware.de/funktionen/ebay-buchhaltung/`
steht woertlich: „Verbinde dein eBay-Verkaeufer-Cockpit ueber unseren Partner **Billbee** oder
**DreamRobot** direkt mit Lexware Office." Im Hilfecenter-Artikel „Umsaetze aus Online-Shops mit
PayJoe buchen" heisst es: „Wenn Sie sehr viele Umsaetze ueber Ihren Online-Shop verzeichnen,
empfehlen wir, diese ueber **PayJoe** abzurufen." Und im Artikel „Zahlungsdienstleister in der
Bank verbuchen (Stripe, eBay, Etsy, Mollie, Amazon etc.)" empfiehlt Lexware ab etwa 50-100
Belegen je Banktransaktion ausdruecklich **PayJoe oder Miracle Sync** statt der manuellen
Zuordnung. (alle abgerufen 2026-08-29)

### Schicht 2 — eBay-Payments nach anderen Buchhaltungen (6)

- **BuchhaltungsButler** — **native eBay-Managed-Payments-Anbindung**: taeglicher Import aller
  Transaktionen, „automatischer Gebuehrensplit, bei dem die eBay-Gebuehren direkt von der
  Brutto-Zahlung getrennt" werden, Vorkontierung, Belegmatching, bis zu 100 Buchungen je Klick.
  **19,90 EUR/Monat als kostenpflichtiges Add-on** (19,95 EUR im E-Commerce-Paket), 14 Tage Test,
  keine Gratisstufe fuer die eBay-Anbindung.
- **sevdesk** — eBay-Anbindung ueber die eigene Billbee-Schnittstelle; wirbt mit „Ebay
  Buchhaltung Testsieger 2026 mit Note 1,2", 14 Tage Test.
- **easybill** — von Lexware im Hilfecenter neben Billbee als Weg genannt; ab 9,00 EUR/Monat,
  Gratisstufe vorhanden (Preis aus dem Etsy-Lauf vom 2026-08-28).
- **KonverterPro** (konverter-pro.de) — eBay-Zahlungsbericht in einen fertigen DATEV-Buchungsstapel,
  ausdruecklich mit „Alternative Outputs fuer sevDesk, Lexware, Lexoffice und BuchhaltungsButler";
  verarbeitet Erloese, Einstell- und Verkaufsprovisionen, Versandkosten, Erstattungen samt
  Gebuehrenkorrektur und Promoted-Listings-Kosten. **5 Konvertierungen pro Tag kostenlos mit
  Registrierung**, bezahlte Stufen 20-99 EUR/Monat, monatlich kuendbar.
- **Speetax / sbco.cloud** — Wandlerprogramm eBay → DATEV, „Zahlungen aufs Bankkonto werden
  durch entsprechende Erloes- und Gebuehrenbuchungen automatisch aufgeloest".
  **299,00 EUR einmalig**, Lizenz auf zwei Jahre begrenzt, mandantenfaehig.
- **dekodi nexus** — Parser fuer Marktplatzabrechnungen inkl. eBay Payment, DATEV-Buchungsstapel.
  **29,00 EUR netto Grundgebuehr je Lizenznehmer und Monat** plus Staffelpreis je exportierter
  Transaktion, alternativ Festpreismodell je Mandant.

### Schicht 3 — E-Commerce-Buchhaltung mit DATEV-Anschluss (6)

Aus dem Vergleichsportal `ecommerce-buchhaltung-vergleich.de` (affiliatefinanziert, Stand
Juli 2026, abgerufen 2026-08-29), alle mit eBay als Kanal: **pathway** ab 29,99 EUR/Mon.
(Testsieger 9,8/10), **AccountOne** ab 24 EUR/Mon., **EasyPliant** auf Anfrage (eigene
DATEV-Seite „eBay Buchhaltung"), **Taxdoo** ab 49 EUR/Mon., **Amainvoice** ab 43 EUR/Mon.,
**easybill** ab 9 EUR/Mon.

### Schicht 4 — Warenwirtschaft und Werkzeugbau darum herum (3)

**JTL2Datev (Jera)** — im Verkaeuferforum als „Geht auf Knopfdruck" beschrieben; **Synesty** —
fertiger Connector „Ebay – Lexware-Office", Basispaket ab 99,00 EUR/Monat im Jahresabo;
**WISO MeinBuero** — ordnet laut Forendiskussion Zahlungen automatisch den Rechnungen zu.
Dazu **oscware** (Bestellimport eBay → Lexware Warenwirtschaft) und **CrowPrime**, das im
Februar 2026 einen eigenen „eBay Buchhaltung Deutschland: Leitfaden 2026" veroeffentlicht hat —
geschrieben vom Anbieter selbst, Saettigungsindikator (11) aus meinem Logbuch.

**Korrektur zu meiner eigenen Etsy-Recherche vom 2026-08-28:** Kassenklingeln, der
Lexware-Technologiepartner fuer Etsy-Buchhaltung, unterstuetzt eBay **nicht**. Auf
`tools.kassenklingeln.de/lexwareoffice` steht ausschliesslich Etsy; ein Suchtreffer legte
anderes nahe, die Produktseite widerlegt ihn. Der Etsy-Kanal ist vergeben, der eBay-Kanal von
diesem Anbieter nicht — er ist an Billbee und DreamRobot vergeben.

### Die Ausgangsbeobachtung des Signals stimmt trotzdem

Lexware Office hat **keine** direkte eBay-Anbindung, und das ist belegt statt vermutet: Der
Hilfecenter-Artikel „Umsaetze aus Online-Shops mit PayJoe buchen" sagt woertlich „Eine direkte
Anbindung der Online-Shops ist nicht moeglich", und die Liste der anbindbaren Zahlungsdienstleister
(`help.lexware.de/.../547966`) fuehrt PayPal, Revolut, Holvi, Kontist, Pleo, Qonto und Finom —
**eBay steht weder auf der Positiv- noch auf der Negativliste**. Die Enttaeuschung des
Forennutzers („das klang als ob lexoffice das von sich aus koennte", „keine native Schnittstelle
wie bei PayPal") ist also sachlich richtig. Sie ist nur kein Markt, weil der Hersteller die
Luecke ueber ein Partnernetz von „ueber 150 Erweiterungen" schliesst und die Partner in seinen
eigenen Hilfeartikeln namentlich empfiehlt.

## 3. Was heute dafuer gezahlt wird

Vier Ebenen, und die Zahlungsbereitschaft fliesst nachweislich — der Signalgeber selbst nennt
zwei Anbieter, zu denen Nutzer gewechselt sind.

1. **Aufschluesselungsschicht: 4,20-19,90 EUR/Monat.** PayJoe 4,20 EUR je Zugang plus 0,05 EUR
   je Datensatz — bei den im Signal genannten vier Auszahlungen mit, sagen wir, 50 zugrunde
   liegenden Transaktionen sind das **6,70 EUR im Monat**. BuchhaltungsButler 19,90 EUR als
   Add-on. dekodi 29,00 EUR Grundgebuehr plus Staffel.
2. **Warenwirtschaft darueber: ab 9,00 EUR/Monat** (Billbee Starter bis 200 Bestellungen,
   ohne Mindestlaufzeit).
3. **Buchhaltungssoftware darunter: 7,90-32,90 EUR/Monat** (Lexware Office S bis XL, Preisstand
   aus dem Lexware-Preiserhoehungslauf vom 2026-08-28). Fuer die API-gestuetzten Sync-Loesungen
   ist die **XL-Stufe Voraussetzung** — das ist die versteckte Zusatzkosten-Zeile in dieser
   Rechnung, belegt allerdings bisher nur fuer den Etsy-Sync von Kassenklingeln.
4. **Steuerberater:** Ein Verkaeufer im sellerforum berichtet, eBays neue Zahlungsabwicklung
   habe ihn „tausende von Euro" an Steuerberaterkosten gekostet — die Obergrenze dessen, was
   das Problem wert sein kann, und zugleich der Grund, warum die 6,70-EUR-Loesung sich lohnt.

**Der Preisboden ist dennoch null:** KonverterPro konvertiert fuenf eBay-Berichte pro Tag
dauerhaft kostenlos, nach Registrierung, mit Ausgabeformaten fuer Lexware Office. Fuer den im
Signal beschriebenen Fall — vier Auszahlungen im Monat — reicht die Gratisstufe vollstaendig aus.

## 4. Die heutige Notloesung

**Manuelle Zuordnung im Bankbereich, ein Offline-Konto oder ein CSV-Import — und sie kostet
zehn bis fuenfzehn Minuten im Monat.**

Der Weg, den Lexware selbst als Standard beschreibt: Auszahlung unter „Finanzen > Umsaetze"
auswaehlen, die zugehoerigen Belege unter „Erfasste Belege" **gemeinsam** markieren (Einnahmen-
und Ausgabenbelege zusammen) und zuordnen; die Differenz bucht das System nach Auswahl als
„Gebuehren mit Steuer" oder „Gebuehren ohne Steuer". Erst ab etwa 50-100 Belegen je
Banktransaktion verweist Lexware auf PayJoe oder Miracle Sync.

Daneben zwei Eigenbauten aus der Community:

- Der Startbeitrag des zitierten Quell-Threads (11.01.2021) ist selbst eine **Bauanleitung**:
  Konto „eBay Payouts" anlegen, woechentlichen Abrechnungsbericht als CSV laden, ab Zeile 12
  kopieren, in eine mitgelieferte Vorlage ab Zeile 18 einsetzen, als CSV speichern, ueber
  „Import Umsaetze CSV" einlesen. Zwei Vorlagendateien (.xls und .xlsx) haengen am Beitrag.
  Die Zielgruppe hat das Werkzeug also vor fuenf Jahren selbst gebaut und verschenkt.
- Der zweite Thread beschreibt das Offline-Konto mit dreifachem Import des
  eBay-Transaktionsbelegs.

**Der Zeitaufwand ist der entscheidende Befund.** Das Signal selbst nennt „4 Ueberweisungen sind
von eBay" bei „ca. 15 Minuten Aufwand fuer den Abgleich". Unabhaengig davon berichtet ein
Verkaeufer im sellerforum-Thread „Ebay – Rechnungs- zu Auszahlungsbetrag zuordnen?" bei
**30 Bestellungen im Monat** von „ca. 10 Minuten" nach Einrichtung seines Verfahrens. Zwei
Quellen, zwei Communities, dieselbe Groessenordnung: **10-15 Minuten im Monat**.

Nach meinem eigenen Logbucheintrag vom 2026-08-28 wird eine Notloesung in dieser Groessenordnung
nicht ersetzt. Sie ist ausserdem billiger als jede der zwanzig Loesungen: 15 Minuten im Monat
sind bei 50 EUR Stundensatz 12,50 EUR — dieselbe Groessenordnung wie das Abo, das sie ersetzen
soll, und ohne Einrichtungsaufwand.

## 5. Was dagegen spricht

**(a) Der Ausschlussgrund im Wortsinn: ein Anbieter im deutschsprachigen Markt, der genau
dieses Segment mit genau dieser Aufgabe bedient — und der Softwarehersteller empfiehlt ihn
selbst.** PayJoe nimmt eBay-Payments-Auszahlungen, schluesselt sie in Einzeltransaktionen auf,
trennt die Gebuehren, uebergibt beides an Lexware Office und gleicht die offenen Posten aus.
Das ist Satz fuer Satz die Aufgabe des Signals. Lexware nennt PayJoe im eigenen Hilfecenter,
Billbee und DreamRobot auf der eigenen eBay-Produktseite, Miracle Sync im eigenen
Zahlungsdienstleister-Artikel. Vier namentliche Wege, alle vom Hersteller kuratiert.

**(b) Der Quell-Thread nennt die Loesung selbst — zweimal, und im zweiten Fall verlinkt der
Antwortende direkt die Lexware-Partnerseite.** Im Thread „Ebay als Kleinunternehmer" (06.01. bis
24.02.2026, sechs Beitraege) antwortet „Lutzcie" mit `lexware.de/partner/billbee/`. Der
Fragesteller weist auf die Kostenpflicht hin — das ist der ganze verbliebene Einwand. Im
aelteren Thread „Ebay Zahlungen in lexoffice" (18 Beitraege, 01/2021 bis 02/2024) berichtet ein
Nutzer sogar von „100 % Vollautomatik" mit Billbee. Wie im Etsy-Lauf gilt: der Pain wurde in
genau dem Thread geloest, der ihn belegen sollte.

**(c) Der Preisboden ist null.** KonverterPro: fuenf eBay-Konvertierungen pro Tag dauerhaft
kostenlos, mit Ausgabe fuer Lexware Office. Das ist Saettigungsindikator (7) aus meinem
Logbuch — eine dauerhaft kostenlose Stufe, kein Trial —, und fuer vier Auszahlungen im Monat
ist sie nicht die Einstiegsstufe, sondern der Regelfall. Darueber liegt mit PayJoe eine
vollautomatische Loesung fuer 6,70 EUR im Monat. Zwischen null und 6,70 EUR passt kein Produkt.

**(d) Die Notloesung ist zu billig, um ersetzt zu werden.** 10-15 Minuten im Monat, aus zwei
unabhaengigen Quellen. Wer 500 Bestellungen im Monat hat, hat laengst Billbee oder
BuchhaltungsButler; wer vier Auszahlungen hat, hat ein Viertelstundenproblem.

**(e) Der Vertriebskanal ist vergeben, und zwar vom Hersteller schriftlich.** Lexware Office
fuehrt „ueber 150 Erweiterungen" in Kategorien, darunter E-Commerce; die Marktplatzanbindung
liegt bei Billbee, DreamRobot, VersaCommerce und sync4. Ein Neuer haette weder die Partnerseite
noch die Nennung im Hilfecenter — und genau diese beiden Orte sind es, an denen die Betroffenen
im Forum aufeinander verweisen.

**(f) Zwei weitere Vergleichs- und Bewertungsschichten stehen schon.**
`ecommerce-buchhaltung-vergleich.de` (sechs Anbieter mit Noten, affiliatefinanziert, Stand
07/2026), sevdesk mit „Ebay Buchhaltung Testsieger 2026 mit Note 1,2", CrowPrime mit einem
eigenen „Leitfaden 2026" in eigener Sache. Der Informationslayer ist nicht knapp, sondern
umkaempft.

**(g) Der schwierige Teil ist nicht die Schnittstelle, sondern die Wertung — und die ist
gesperrt.** Was die Foren wirklich beschaeftigt, sind nicht Dateiformate, sondern Fragen wie:
Reverse Charge auf eBay-Gebuehren aus Luxemburg? Welcher Steuersatz? Wie sind Gutschriften zu
erfassen — als Erloesminderung oder als Ausgabe? Ist die Verbuchung der reinen Gutschriftsbetraege
GoB-konform? Im Thread „eBay mit Billbee & PayJoe richtig verbuchen" (01/2022 bis 05/2022, fuenf
Antworten) lautet die Antwort woertlich: „Zum Steuerbuero gehen zur Klaerung." Genau diese
Fragen faellt § 6 StBerG einem Nebengewerbe nicht zu (Logbuch 2026-08-28: „XML uebertragen ist
erlaubt, entscheiden was hineinkommt ist es nicht"). Uebrig bliebe der Transportteil — und der
ist zwanzigfach besetzt und teilweise gratis.

**(h) Einordnung nach meiner Pain-Erstfrage.** Weder Funktions- noch Akzeptanzluecke. Es ist
dieselbe **Preisluecke nach unten** wie beim Etsy-Signal, hier sogar mit einem zusaetzlichen
Grund: der Aufwand der Notloesung liegt unterhalb der Schwelle, ab der ueberhaupt jemand kauft.
Zweite Wiederholung desselben Musters in zwei Tagen — Marktplatzverkaeufer, Buchhaltungsimport,
Kleinstbetrag.

**(i) Der Markt waechst hier nicht.** eBays Wachstum 2025 lag auf dem US-Heimatmarkt; fuer
deutsche Haendler meldet der einschlaegige Marktplatzblog ausdruecklich das Gegenteil. Ein
Nischenwerkzeug erbt die Kurve seiner Plattform.

## Offen geblieben

- **Eine aktuelle Zahl gewerblicher eBay-Verkaeufer in Deutschland existiert nicht.** Die
  einzige methodisch saubere ist elf Jahre alt (118.899, Februar 2015). eBay nennt in seinen
  deutschen Pressemeldungen von 2026 ausschliesslich Prozentwerte und eine Stichprobengroesse
  (1.377 Befragte), nie eine Grundgesamtheit. Der Ideator darf **keine** Bestandszahl ansetzen;
  belegbar ist nur „sechsstellig, Tendenz unbekannt". Zwei eBay-Pressemitteilungen
  (`ebayinc.com`, „Kleine Haendler*innen sind online auf dem Land besonders stark", Juli 2026,
  und „Starker Mittelstand, schwache Gruendungsdynamik", Maerz 2026) liefen zweimal in einen
  Timeout und konnten nur ueber Sekundaerquellen gelesen werden — dort standen keine
  Bestandszahlen, ausschliessen kann ich sie fuer die Primaerquelle aber nicht.
- **Der Preis von DreamRobot, sync4 und Miracle Sync ist nicht oeffentlich.** Bei Miracle Sync
  stammt „ab 9 EUR/Monat" aus einer Suchzusammenfassung; die Startseite nennt keine Preise und
  als Zahlungsanbieter nur Stripe. Dass Miracle Sync eBay unterstuetzt, steht nicht auf der
  Anbieterseite, sondern **nur** im Lexware-Hilfecenter, das es fuer diesen Fall empfiehlt.
  Als Beleg fuer den eBay-Fall daher schwaecher als PayJoe.
- **Ob fuer die Sync-Loesungen durchgaengig die Lexware-Office-XL-Stufe noetig ist**, konnte ich
  nur fuer den Etsy-Sync von Kassenklingeln belegen (API-Zugang erst ab XL). Falls das auch fuer
  die eBay-Wege gilt, verschiebt es die Gesamtkosten deutlich nach oben — und wuerde als
  einziger gefundener Punkt fuer eine Luecke bei den Kleinsten sprechen. Ungeprueft.
- **buchhaltungsbutler.de lieferte im Hilfecenter erneut HTTP 403** (zweiter Lauf in Folge);
  die Beschreibung der eBay-Anbindung stammt von der Produktseite, die abrufbar war, nicht aus
  der technischen Dokumentation.
- **Die zwei Threads in der offiziellen eBay-Community** („Lexware Payjoe eBay Auszahlungen",
  „Buchhaltung auf eBay") liefen in einen Timeout. Der Nachfragetest ueber Antwortzahlen stuetzt
  sich damit nur auf lex-forum (18 / 6 / 5 / 2 Beitraege) und sellerforum (22 Antworten,
  12/2021 bis 10/2023). Auffaellig gegenueber dem Etsy-Signal: hier wird tatsaechlich
  diskutiert — der Pain ist echter als dort, die Loesungsdichte aber auch hoeher.
- **Nicht geprueft:** ob eBay selbst einen Buchhaltungsexport in deutschen Formaten plant. Die
  Seller News vom April 2026 brachten ein Compliance-Werkzeug im Verkaeufer-Cockpit Pro
  (Identitaetspruefung, regulatorische und steuerliche Aufgaben gebuendelt), keinen
  Buchhaltungsexport. Kaeme er, faellt Schicht 1 und 2 weg — auch das spricht gegen, nicht dafuer.
</content>
</invoke>
