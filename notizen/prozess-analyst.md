# Logbuch: prozess-analyst

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/prozess-analyst-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Fortsetzung von `notizen/archiv/prozess-analyst-2026-08-30.md` (Grenze erreicht am
2026-08-30, nach sechs Prozessprofilen). Uebernommen ist, was ueber den einzelnen Vorgang
hinaus gilt.*

---

## Stand

Sechs der acht Vorgaenge aus `quellen.yml` sind profiliert, **alle sechs `tot`**:
Pruefnachweis, Unterweisungsnachweis, Terminwiederbesetzung, Verbrauchsabrechnung,
Behoerdenmeldung, Leistungsnachweis an den Kostentraeger. Offen: **Beitrags- und
Mitgliedsabrechnung mit Zahlungsnachlauf** und die Kontrollprobe **Vorgangsdokumentation
per Diktat**.

## Was funktioniert

- **2026-08-30** — **Frage 4 zuerst, in genau einem Abruf: Suchwort plus „software".**
  Kommt eine Landingpage eines branchenneutralen Anbieters *genau zum Suchwort* zurueck,
  sind Frage 4 und Frage 6 zugleich beantwortet — Kanal vorhanden, Kanal besetzt. Vor die
  Vereinigungszaehlung stellen, nicht danach. Hat bei fuenf von sechs Vorgaengen das Urteil
  schon vorweggenommen.
- **2026-08-30** — Noch billiger: **pruefen, ob das Suchwort als Domain vergeben ist.**
  `unterweisungsnachweis.de` gehoert einem Wettbewerber. Eine Domain mit dem Vorgangsnamen
  beweist gemeinsamen Kanal *und* Besetzung, noch vor jeder Anbieterliste.
- **2026-08-30** — **Steht der Vorgang in einem Gesetz, das die Betroffenen selbst
  aufzaehlt, ist der Gesetzestext die Branchenliste.** § 302 SGB V nennt neun Gewerke in
  einem Satz; die Ausgangstabelle kannte drei, die Vereinigung stieg von 74.662 auf 96.643.
  **Nach der Norm suchen, nicht nach Branchen.**
- **2026-08-30** — **Die Kundenliste des horizontalen Anbieters beweist besser als jedes
  eigene Argument, dass der Vorgang derselbe ist.** Wer ihn fuer neun Branchen auf einer
  Plattform abwickelt, koennte das nicht, waeren es neun Vorgaenge. Ersetzt die halbe
  Kern-Schale-Diskussion.
- **2026-08-30** — Der **negative** Kanaltest, vier Suchen: je Branche „<Branchenwort>
  <Vorgang> software". Kommt in keiner Trefferliste ein Anbieter aus einer anderen Branche
  vor, gibt es kein gemeinsames Suchwort — und dann ist der Vorgang trotz gleichem Kern
  nicht derselbe Markt.
- **2026-08-30** — Zuerst die `handarbeit`-Felder woertlich nebeneinanderlegen, dann erst
  addieren. Grep ueber alle Frontmatter (`segment|betriebe|handarbeit|potenzial`) kostet
  einen Aufruf und ersetzt das Lesen von 300.000 Zeichen Profiltext.
- **2026-08-30** — Bei Pflichtvorgaengen den **Volltext der Landesbehoerdenseite** holen,
  nicht den Suchauszug. Er hat die Vorgangsdefinition gedreht: Die objektbezogene
  Asbestanzeige gilt nur bei *hohem* Risiko und setzt eine behoerdliche Zulassung voraus;
  bei mittlerem genuegt eine Meldung von Ort und Zeit. Der Auszug haette „je Baustelle,
  7 Tage" gesagt und mich 15.241 statt 2.588 Betriebe rechnen lassen.

## Was nicht funktioniert

- **2026-08-30** — **Ein `handarbeit`-Feld, das aehnlich klingt, ist noch kein gleicher
  Vorgang.** Beim Pruefnachweis blieben von 65.433 Betrieben 10.365 uebrig. Immer drei bis
  fuenf Merkmale festschreiben und jede Branche einzeln dagegen halten. Die Marktprofile
  sind korrekt; die Fehler stecken in der Gruppierung der Ausgangstabelle.
- **2026-08-30** — **Frage 3 hat zwei Absterbezonen, nicht eine.** Grosser Kern: hat schon
  jemand gebaut (Pruefnachweis, Leistungsnachweis). Winziger Kern: ist eine Funktion, kein
  Produkt — vier Spalten (Unterweisungsnachweis), eine Subtraktion und eine Multiplikation
  (Verbrauchsabrechnung). **Pruefformel: Laesst sich der Kern in einem Satz als
  Rechenvorschrift schreiben, ist Frage 4 schon beantwortet.** Der Fund liegt im schmalen
  Band dazwischen; sechs Vorgaenge lagen ausserhalb, an beiden Enden.
- **2026-08-30** — **Frage 3 fragt nach der Groesse der Schale und muesste nach ihrer
  Haltbarkeit fragen.** Beim Pruefnachweis war sie eine *Konfiguration* (einmal gesetzt,
  jahrelang gueltig), beim Leistungsnachweis ein *Abonnement* (regionale Rahmenvertraege,
  fortgeschriebene Schluesselverzeichnisse, woechentliche Pflege). Gleiche Groesse,
  entgegengesetzte Folge: Die zweite Art reisst schon fuer sich das Zwei-Stunden-Budget —
  und wer sie heute pflegt, verkauft sie fuer 9,99 EUR im Monat.
- **2026-08-30** — **Steht am Ende des Vorgangs eine Zahlung, gehoert der Vorgang dem, der
  die Zahlung abwickelt.** Drei Abrechnungszentren halten rund 96.000 Kundenbeziehungen in
  einer Vereinigung von 96.643: Sie bekommen den Beleg ohnehin, pruefen ihn ohne
  Grenzaufwand, kennen den Zahlungseingang und koennen deshalb **Haftung** zusagen. Vierte
  und haerteste Variante von „die Behoerde ist der Wettbewerber". **Vorabtest: Fliesst am
  Ende Geld? Dann zuerst nach dem Abwickler suchen, nicht nach Software.**
- **2026-08-30** — **Wo der Vorgang endet, sitzt der Torwaechter.** Endet er in einem
  System, das der Betrieb schon hat (Kalender, ERP, PVS, Abrechnungszentrum), ist dessen
  Hersteller Wettbewerber und Zugang zugleich, und der Vorgang ist eine Haken-Funktion in
  seinem Tarif. Wird er als **Tarifstufe** verkauft, ist sein Einzelpreis die Differenz
  zweier Tarife und damit fast null.
- **2026-08-30** — **Eine unbegrenzte Vereinigung ist ein Warnzeichen, kein Fund.** Der
  Unterweisungsnachweis trifft jeden Arbeitgeber (2,1 Mio. Betriebe) und ist genau deshalb
  der dichtest besetzte Vorgang der Liste. **Gilt die Pflicht branchenunabhaengig? Dann
  Frage 4 sofort stellen und die Zaehlung sparen.**
- **2026-08-30** — **„Die Vereinigung ist gross genug" rettet nichts.** Dreimal belegt:
  Terminwiederbesetzung 164.458 Betriebe / 6.396 EUR, Unterweisungsnachweis 2,1 Mio. /
  60.900 EUR, Leistungsnachweis 96.643 / 5.820 EUR — alle drei `tot`. `traegt_5000` und
  `befund` sind zwei Fragen; wer nur die Rechnung sieht, meldet einen Fund, wo eine
  Haken-Funktion steht. Beim Leistungsnachweis war die Groesse zum ersten Mal ueberhaupt
  nicht der Engpass.

- **2026-08-30** — **Nach „machen sie denselben Vorgang?" sofort die zweite Frage: „wuerde
  derselbe Kunde beide Meldungen machen?"** Bei der Behoerdenmeldung war die erste Antwort
  ja und die zweite nein — Elektro meldet nie Asbest, ein Dachdecker nie ans Netz. 110.804
  Betriebe, drei Formulare ohne ein gemeinsames Feld ausser Firma und Anschrift. Nein
  heisst: Summe, kein Markt, `schale_groesser_als_kern: ja`.
- **2026-08-30** — **Wo ein Preis gezahlt wird, sitzt schon jemand; wo niemand sitzt, wird
  auch nichts gezahlt.** In einem Profil dreifach belegt: Netzanmeldung 299-399 EUR je
  Vorgang (vier Anbieter), KfW-Bestaetigung 210 EUR (zwei), Asbestanzeige gebuehrenfrei
  (keiner). **„Kein Anbieter gefunden" zuerst als Warnsignal lesen, nicht als Fund** — und
  gegenpruefen: Zahlt irgendwer irgendwem etwas fuer genau diesen Vorgang?

## Offene Faehrten

- **2026-08-30** — **Zu jedem Vorgang zuerst die Endkundengruppe suchen, nicht die
  Betriebe.** Bei der Verbrauchsabrechnung nannte die Ausgangstabelle 27.800 Betriebe; die
  eigentliche Gruppe sind 5,5 Mio. private Vermieter — Faktor 200. Marktprofile kennen nur
  Betriebe, deshalb fehlt diese Seite in der Tabelle systematisch. Frage: *Wer macht
  denselben Vorgang, ohne ein Gewerbe zu sein?* Regelmaessig um Groessenordnungen groesser
  — und regelmaessig die Seite mit dem Preisboden null (objego Basics, hellohousing,
  Laubenmeister: alle drei dauerhaft gratis). Beim offenen Vorgang Beitragsabrechnung
  heisst diese Seite **Vereinskassierer**, und der Gratis-Beleg liegt schon vor.
- **2026-08-30** — **Ein herrenloser Vorgang, den ich nicht bearbeiten darf: „vertraglicher
  Leistungsnachweis an den Auftraggeber".** Die Facility-Dienstleister (34.288) sind jetzt
  zweimal aussortiert — beim Pruefnachweis (kein gesetzlicher Turnus) und beim
  Kostentraeger-Nachweis (kein Dritter, keine Verordnung, kein vorgeschriebener Datensatz).
  Ihr Vorgang existiert, ist gross und steht in keinem Eintrag von `quellen.yml`. Die
  Liste aendert der Betreiber, nicht ich.
- **2026-08-30** — **Vier Crawler-Zahlen liessen sich durch amtliche ersetzen, wenn jemand
  das HLV auslesen kann.** Der GKV-Spitzenverband fuehrt auf gkv-spitzenverband.de das
  Heilmittelleistungserbringerverzeichnis mit allen zugelassenen Praxen (Physio, Ergo,
  Logopaedie, Podologie, Ernaehrungstherapie). Ich fand nur die Suchmaske, keine Gesamtzahl
  je Bereich. Die Vereinigung 96.643 ist deshalb eher zu klein: Logopaedie 5.570 gegen
  9.000 zugelassene, Ergotherapie 7.381 gegen kursierende 18.000 bis 20.000.
- **2026-08-30** — **Die Zahl der Arztpraxen in Deutschland ist nicht frei auffindbar.**
  Destatis rechnet aus einer Stichprobe von hoechstens 7 Prozent hoch, die KBV zeigt sie
  nur in interaktiven Grafiken. Damit fehlt die groesste Branche in jeder
  Gesundheits-Vereinigung. Nicht erneut ueber Destatis oder KBV-Gesundheitsdaten versuchen
  — wenn, dann ueber das Bundesarztregister-PDF oder eine KV-Einzelauswertung. Bisher
  zweimal folgenlos.
- **2026-08-30** — Ungezaehlte Prueferbranchen ohne amtliche Zahl:
  DGUV-V3-Pruefdienstleister, Torpruefer, Regalpruefer (DIN EN 15635),
  Trinkwasser-Probenehmer, Spielplatz-Pruefdienstleister. Keine wird als Wirtschaftszweig
  gefuehrt. Wer hier eine Zaehlung findet, hebt jede kuenftige Prueferunion.
- **2026-08-30** — **HOPPE Wartungsplaner bedient zwei von zwei untersuchten
  Fristen-Vorgaengen.** Wer eine Fristendatenbank hat, haengt jede weitere Fristenart mit
  an. Vor jedem Fristen-Vorgang ein Abruf auf wartungsplaner.de.
- **2026-08-30** — **Naechster Vorgang: Beitrags- und Mitgliedsabrechnung mit
  Zahlungsnachlauf.** Warnung vorab aus der Startnotiz und aus `lehren.md`: Dort ist der
  Preisboden null ein Geschaeftsmodell (PushPress verschenkt das Abo und lebt von 4,99
  Prozent auf den Beitragseinzug). **Preisboden vor der Groesse pruefen** — und die Lehre
  von heute daneben halten: Am Ende dieses Vorgangs fliesst Geld, also zuerst nach dem
  Abwickler suchen.
- **2026-08-30** — **Offener Punkt an den Portfolio-Manager, nicht an mich: G7 misst bei
  sehr grossen Vereinigungen nichts mehr.** Ein Promille von 2,1 Mio. Betrieben ergibt
  60.900 EUR und nimmt die Schwelle um das Zwoelffache, obwohl der Vorgang eindeutig tot
  ist. Der Anteil unterstellt einen Markt mit freien Kunden; ist er gesaettigt, waechst nur
  der Nenner. Ich lasse `traegt_5000` und `befund` deshalb bewusst auseinanderfallen, statt
  die Rechnung passend zu machen.

- **2026-08-30** — **Das Wirtschaftsportal des Landes ist ein horizontales Werkzeug und
  gehoert bei jedem Behoerdenvorgang in Frage 4.** WSP.NRW: ueber 80 Online-Dienste,
  ELSTER-Unternehmenskonto, Stammdaten mehrfach nutzbar. Hamburg: Asbestanzeige seit 2020
  digital, mit Statusverfolgung und Filter. Gebuehrenfrei und per OZG wachsend. Abruf:
  „<Meldung> Onlinedienst Serviceportal <Land>".

## Einträge

- **2026-08-30** — Fuenfter Vorgang, **Behoerdenmeldung je Vorgang**: `befund: tot`, aber
  an einer anderen Stelle als die uebrigen — nicht an Frage 4, sondern an **Frage 3**.
  Alle drei Branchen machen wirklich eine Behoerdenmeldung je Auftrag; es sind nur drei
  verschiedene. Zwei Drittel der Vereinigung sind zusaetzlich besetzt, und zwar **quer**:
  autarc und Reonic bedienen Netzanmeldung *und* KfW-Foerderantrag, in Elektro *und* SHK —
  sie haben den Vorgangsschnitt, den diese Rolle sucht, bereits vollzogen. Gerechnet habe
  ich bewusst mit dem **Prozent** (Kanal belegt, von keinem Wettbewerber besetzt); es
  traegt trotzdem nicht, weil fuer die einzige freie Teilmenge kein Preis existiert.
  **Melde an den Portfolio-Manager:** Das Dachdeckerprofil vom 2026-08-28 ordnet die
  objektbezogene Asbestanzeige „mittleres + hohes Risiko" zu und nennt sie den Regelfall je
  Baustelle — nach dem Volltext der NRW-Arbeitsschutzverwaltung gilt sie nur bei hohem
  Risiko. Nicht falsch, aber aufwandsueberzeichnend. Ich fasse `signals/maerkte/` nicht an.

- **2026-08-30** — Sechster Vorgang, **Leistungsnachweis gegenueber einem Kostentraeger**:
  neun Branchen, 96.643 Betriebe, `befund: tot`. Erstmals waren *alle* Vorbedingungen
  dieser Rolle gleichzeitig erfuellt — grosser Kern, kleine Schale, Handarbeit als echter
  Kostenblock statt Umsatz, gesetzlicher Zwang, und ein gemeinsamer Kanal, der keine
  Umschreibung ist, sondern eine Paragrafennummer. **Genau deshalb war die Vereinigung
  besetzt:** § 302 SGB V hat den Vorgang 1989 branchenuebergreifend definiert, und die
  Antwort darauf ist eine ganze Industrie. Die Lehre, die ich mitnehme: Ein Vorgang, den
  der Gesetzgeber selbst branchenuebergreifend beschreibt, ist die **schlechteste**
  Fundstelle dieser Rolle, nicht die beste — die Vorlage lag jedem anderen genauso vor,
  und zwar seit Jahrzehnten.
- **2026-08-30** — **Ausgefallene Termine kurzfristig wiederbesetzen**, 164.458 Betriebe
  aus vier Branchen, `traegt_5000: knapp` (6.396 EUR) und trotzdem `befund: tot`. Erste
  Vereinigung dieser Rolle, deren Rechnung die Schwelle nimmt — sie scheitert an der
  Bauart, nicht an der Groesse. Zwei Dinge, die ich mitnehme: Der Vorgang beginnt und
  endet im Terminkalender, also gehoert er dessen Hersteller (Acuity ab Standard 27 USD,
  Square ab Plus, Waitwhile gratis, Doctolib prueft alle 10 Minuten auf Absagen). Und die
  Strenge bei Frage 1 hat sich zum ersten Mal *gegen* eine grosse Zahl gerichtet: Das
  dritte Merkmal — **ein Bestand wartender Kunden** — hat 80.118 Friseursalons aus der
  Vereinigung geworfen, obwohl Acuity und Fresha sie ausdruecklich als Zielgruppe nennen.
  Ohne Nachfrageueberhang ist Wiederbesetzung kein Vorgang, sondern Werbung.
