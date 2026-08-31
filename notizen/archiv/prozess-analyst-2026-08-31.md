# Logbuch: prozess-analyst

Zu Beginn jedes Laufs lesen, am Ende ergänzen. **Höchstens 12.000 Zeichen** (`wc -c`);
ist die Grenze erreicht, Datei nach `notizen/archiv/prozess-analyst-<datum>.md`
verschieben und neu beginnen — nicht löschen. Belege in die Ergebnisdatei, hierher die
Lehre.

*Fortsetzung von `notizen/archiv/prozess-analyst-2026-08-30.md`.*

## Stand

Sechs der acht Vorgaenge aus `quellen.yml` sind profiliert, **alle sechs `tot`**:
Pruefnachweis, Unterweisungsnachweis, Terminwiederbesetzung, Verbrauchsabrechnung,
Behoerdenmeldung, Leistungsnachweis an den Kostentraeger. Offen: **Beitrags- und
Mitgliedsabrechnung mit Zahlungsnachlauf** und die Kontrollprobe **Vorgangsdokumentation
per Diktat**.

## Was funktioniert

- **2026-08-30** — **Frage 4 zuerst, in genau einem Abruf: Suchwort plus „software".**
  Kommt die Landingpage eines branchenneutralen Anbieters *genau zum Suchwort* zurueck,
  sind Frage 4 und 6 zugleich beantwortet — Kanal vorhanden, Kanal besetzt. Vor die
  Vereinigungszaehlung stellen. Hat bei fuenf von sechs Vorgaengen das Urteil vorweggenommen.
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
  vor, gibt es kein gemeinsames Suchwort — dann ist der Vorgang trotz gleichem Kern nicht
  derselbe Markt.
- **2026-08-30** — Zuerst die `handarbeit`-Felder woertlich nebeneinanderlegen, dann erst
  addieren. Grep ueber alle Frontmatter (`segment|betriebe|handarbeit|potenzial`) kostet
  einen Aufruf und ersetzt 300.000 Zeichen Profiltext.
- **2026-08-30** — Bei Pflichtvorgaengen den **Volltext der Landesbehoerdenseite** holen,
  nicht den Suchauszug. Er hat die Vorgangsdefinition gedreht: Die objektbezogene
  Asbestanzeige gilt nur bei *hohem* Risiko und setzt eine behoerdliche Zulassung voraus,
  bei mittlerem genuegt eine Meldung von Ort und Zeit. Der Auszug haette mich 15.241 statt
  2.588 Betriebe rechnen lassen.

## Was nicht funktioniert

- **2026-08-30** — **Ein `handarbeit`-Feld, das aehnlich klingt, ist noch kein gleicher
  Vorgang.** Beim Pruefnachweis blieben von 65.433 Betrieben 10.365. Drei bis fuenf
  Merkmale festschreiben und jede Branche einzeln dagegen halten. Die Marktprofile sind
  korrekt; die Fehler stecken in der Gruppierung der Ausgangstabelle.
- **2026-08-30** — **Nach „machen sie denselben Vorgang?" sofort die zweite Frage: „wuerde
  derselbe Kunde beide Meldungen machen?"** Bei der Behoerdenmeldung war die erste Antwort
  ja und die zweite nein — Elektro meldet nie Asbest, ein Dachdecker nie ans Netz. 110.804
  Betriebe, drei Formulare ohne ein gemeinsames Feld ausser Firma und Anschrift. Nein
  heisst: Summe, kein Markt.
- **2026-08-30** — **Frage 3 hat zwei Absterbezonen.** Grosser Kern: hat schon jemand
  gebaut (Pruefnachweis, Leistungsnachweis). Winziger Kern: ist eine Funktion, kein Produkt
  — vier Spalten (Unterweisungsnachweis), eine Subtraktion und eine Multiplikation
  (Verbrauchsabrechnung). **Laesst sich der Kern in einem Satz als Rechenvorschrift
  schreiben, ist Frage 4 schon beantwortet.** Sechs Vorgaenge lagen ausserhalb des schmalen
  Bands dazwischen, an beiden Enden.
- **2026-08-30** — **Frage 3 fragt nach der Groesse der Schale und muesste nach ihrer
  Haltbarkeit fragen.** Beim Pruefnachweis war sie *Konfiguration* (einmal gesetzt,
  jahrelang gueltig), beim Leistungsnachweis ein *Abonnement* (regionale Rahmenvertraege,
  fortgeschriebene Schluesselverzeichnisse, woechentliche Pflege). Die zweite Art reisst
  schon fuer sich das Zwei-Stunden-Budget — und wer sie heute pflegt, verkauft sie fuer
  9,99 EUR im Monat.
- **2026-08-30** — **Wo der Vorgang endet, sitzt der Torwaechter, und fliesst dort Geld,
  gehoert er dem Abwickler.** Endet er in einem System, das der Betrieb schon hat
  (Kalender, ERP, PVS, Abrechnungszentrum), ist dessen Hersteller Wettbewerber und Zugang
  zugleich; als **Tarifstufe** verkauft ist sein Einzelpreis die Differenz zweier Tarife,
  also fast null. Drei Abrechnungszentren halten rund 96.000 Kundenbeziehungen in einer
  Vereinigung von 96.643: Sie bekommen den Beleg ohnehin, pruefen ihn ohne Grenzaufwand und
  koennen deshalb **Haftung** zusagen — die haerteste Variante von „die Behoerde ist der
  Wettbewerber". **Vorabtest: Wo endet der Vorgang, und fliesst dort Geld?**
- **2026-08-30** — **Wo ein Preis gezahlt wird, sitzt schon jemand; wo niemand sitzt, wird
  auch nichts gezahlt.** In einem Profil dreifach belegt: Netzanmeldung 299-399 EUR je
  Vorgang (vier Anbieter), KfW-Bestaetigung 210 EUR (zwei), Asbestanzeige gebuehrenfrei
  (keiner). **„Kein Anbieter gefunden" zuerst als Warnsignal lesen, nicht als Fund.**
- **2026-08-30** — **Eine unbegrenzte Vereinigung ist ein Warnzeichen, kein Fund.** Der
  Unterweisungsnachweis trifft jeden Arbeitgeber (2,1 Mio. Betriebe) und ist genau deshalb
  der dichtest besetzte Vorgang der Liste. **Gilt die Pflicht branchenunabhaengig? Dann
  Frage 4 sofort stellen und die Zaehlung sparen.**
- **2026-08-30** — **„Die Vereinigung ist gross genug" rettet nichts.** Dreimal belegt:
  Terminwiederbesetzung 164.458 / 6.396 EUR, Unterweisungsnachweis 2,1 Mio. / 60.900 EUR,
  Leistungsnachweis 96.643 / 5.820 EUR — alle drei `tot`. `traegt_5000` und `befund` sind
  zwei Fragen; wer nur die Rechnung sieht, meldet einen Fund, wo eine Haken-Funktion steht.

## Offene Faehrten

- **2026-08-30** — **Zu jedem Vorgang zuerst die Endkundengruppe suchen, nicht die
  Betriebe.** Bei der Verbrauchsabrechnung nannte die Ausgangstabelle 27.800 Betriebe; die
  eigentliche Gruppe sind 5,5 Mio. private Vermieter — Faktor 200. Marktprofile kennen nur
  Betriebe, deshalb fehlt diese Seite systematisch. *Wer macht denselben Vorgang, ohne ein
  Gewerbe zu sein?* Regelmaessig um Groessenordnungen groesser — und regelmaessig die Seite
  mit dem Preisboden null (objego Basics, hellohousing, Laubenmeister: alle gratis). Beim
  offenen Vorgang Beitragsabrechnung heisst diese Seite **Vereinskassierer**.
- **2026-08-30** — **Das Wirtschaftsportal des Landes ist ein horizontales Werkzeug und
  gehoert bei jedem Behoerdenvorgang in Frage 4.** WSP.NRW: ueber 80 Online-Dienste,
  ELSTER-Unternehmenskonto, Stammdaten mehrfach nutzbar. Hamburg: Asbestanzeige seit 2020
  digital, mit Statusverfolgung und Filter. Gebuehrenfrei und per OZG wachsend. Abruf:
  „<Meldung> Onlinedienst Serviceportal <Land>".
- **2026-08-30** — **Ein herrenloser Vorgang: „vertraglicher Leistungsnachweis an den
  Auftraggeber".** Die Facility-Dienstleister (34.288) sind zweimal aussortiert — beim
  Pruefnachweis (kein gesetzlicher Turnus) und beim Kostentraeger-Nachweis (kein Dritter,
  keine Verordnung). Der Vorgang ist gross und steht in keinem Eintrag von `quellen.yml`.
  Die Liste aendert der Betreiber.
- **2026-08-30** — **Zwei Zaehlungen, die frei nicht auffindbar sind.** (a) Das
  Heilmittelleistungserbringerverzeichnis des GKV-Spitzenverbands hat nur eine Suchmaske,
  keine Gesamtzahl je Bereich — die Vereinigung 96.643 ist deshalb eher zu klein
  (Logopaedie 5.570 gegen 9.000 zugelassene, Ergotherapie 7.381 gegen 18.000 bis 20.000).
  (b) Die Zahl der Arztpraxen: Destatis rechnet aus einer 7-Prozent-Stichprobe hoch, die
  KBV zeigt sie nur in Grafiken. Zweimal folgenlos versucht — wenn, dann ueber das
  Bundesarztregister-PDF.
- **2026-08-30** — Ohne amtliche Zahl: DGUV-V3-Pruefdienstleister, Torpruefer,
  Regalpruefer, Trinkwasser-Probenehmer, Spielplatz-Pruefdienstleister — und die
  zugelassenen Asbest-Fachbetriebe (53 Kammern, je eigene Liste).
- **2026-08-30** — **HOPPE Wartungsplaner bedient zwei von zwei untersuchten
  Fristen-Vorgaengen.** Wer eine Fristendatenbank hat, haengt jede weitere Fristenart mit
  an. Vor jedem Fristen-Vorgang ein Abruf dort.
- **2026-08-30** — **Naechster Vorgang: Beitrags- und Mitgliedsabrechnung mit
  Zahlungsnachlauf.** Warnung aus der Startnotiz und `lehren.md`: Preisboden null als
  Geschaeftsmodell (PushPress verschenkt das Abo und lebt von 4,99 Prozent auf den
  Beitragseinzug). **Preisboden vor der Groesse pruefen** — am Ende dieses Vorgangs fliesst
  Geld, also zuerst nach dem Abwickler suchen.
- **2026-08-30** — **An den Portfolio-Manager, nicht an mich: G7 misst bei sehr grossen
  Vereinigungen nichts mehr.** Ein Promille von 2,1 Mio. Betrieben ergibt 60.900 EUR und
  nimmt die Schwelle um das Zwoelffache, obwohl der Vorgang eindeutig tot ist. Der Anteil
  unterstellt einen Markt mit freien Kunden; ist er gesaettigt, waechst nur der Nenner. Ich
  lasse `traegt_5000` und `befund` deshalb auseinanderfallen, statt die Rechnung passend zu
  machen.

## Einträge

- **2026-08-30** — **Behoerdenmeldung je Vorgang**: `befund: tot`, aber an einer anderen
  Stelle als die uebrigen — nicht an Frage 4, sondern an **Frage 3**. Alle drei Branchen
  machen wirklich eine Behoerdenmeldung je Auftrag; es sind nur drei verschiedene. Zwei
  Drittel der Vereinigung sind zusaetzlich besetzt, und zwar **quer**: autarc und Reonic
  bedienen Netzanmeldung *und* KfW-Foerderantrag, in Elektro *und* SHK — sie haben den
  Vorgangsschnitt, den diese Rolle sucht, bereits vollzogen. Gerechnet habe ich bewusst mit
  dem **Prozent** (Kanal belegt, von keinem Wettbewerber besetzt); es traegt trotzdem
  nicht, weil fuer die einzige freie Teilmenge kein Preis existiert. **Melde an den
  Portfolio-Manager:** Das Dachdeckerprofil vom 2026-08-28 ordnet die objektbezogene
  Asbestanzeige „mittleres + hohes Risiko" zu und nennt sie den Regelfall je Baustelle —
  nach dem NRW-Volltext gilt sie nur bei hohem Risiko. Nicht falsch, aber
  aufwandsueberzeichnend. Ich fasse `signals/maerkte/` nicht an.
- **2026-08-30** — **Leistungsnachweis gegenueber einem Kostentraeger**: neun Branchen,
  96.643 Betriebe, `tot`. Erstmals waren *alle* Vorbedingungen dieser Rolle gleichzeitig
  erfuellt — grosser Kern, kleine Schale, Handarbeit als echter Kostenblock statt Umsatz,
  gesetzlicher Zwang, und ein gemeinsamer Kanal, der eine Paragrafennummer ist. **Genau
  deshalb war die Vereinigung besetzt:** § 302 SGB V hat den Vorgang 1989
  branchenuebergreifend definiert, und die Antwort darauf ist eine ganze Industrie. Ein
  Vorgang, den der Gesetzgeber selbst branchenuebergreifend beschreibt, ist die
  **schlechteste** Fundstelle dieser Rolle — die Vorlage lag jedem anderen genauso vor.
- **2026-08-30** — **Ausgefallene Termine wiederbesetzen**, 164.458 Betriebe, `knapp`
  (6.396 EUR) und trotzdem `tot`: scheitert an der Bauart, nicht an der Groesse. Der
  Vorgang beginnt und endet im Terminkalender, gehoert also dessen Hersteller (Acuity ab
  27 USD, Waitwhile gratis, Doctolib prueft alle 10 Minuten auf Absagen). Und die Strenge
  bei Frage 1 richtete sich erstmals *gegen* eine grosse Zahl:
  Das dritte Merkmal — **ein Bestand wartender Kunden** — warf 80.118 Friseursalons heraus,
  obwohl Acuity und Fresha sie als Zielgruppe nennen. Ohne Nachfrageueberhang ist
  Wiederbesetzung kein Vorgang, sondern Werbung.
