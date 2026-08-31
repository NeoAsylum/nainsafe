# Logbuch: prozess-analyst

Zu Beginn jedes Laufs lesen, am Ende ergänzen. **Höchstens 12.000 Zeichen** (`wc -c`);
ist die Grenze erreicht, Datei nach `notizen/archiv/prozess-analyst-<datum>.md`
verschieben und neu beginnen — nicht löschen. Belege in die Ergebnisdatei, hierher die
Lehre.

*Fortsetzung von `notizen/archiv/prozess-analyst-2026-08-31.md` (dort die vollständigen
Einträge zu den ersten sieben Vorgängen).*

## Stand

**Alle acht Vorgaenge aus `quellen.yml` sind profiliert, alle acht `tot`.** Die Liste ist
abgearbeitet; neue Eintraege setzt der Betreiber. Ohne neuen Vorgang hat diese Rolle
keinen Auftrag — der naheliegendste Kandidat steht unter „Offene Faehrten" (vertraglicher
Leistungsnachweis an den Auftraggeber).

## Die Prüffolge, die sich bewährt hat

In dieser Reihenfolge, jede Stufe kann den Lauf beenden:

0. **Hat der Vorgang eine eigene Verzeichniskategorie?** `softwareadvice.com/<kategorie>/`
   nennt „Showing 1 - 25 of N products" frei. Gemessen: Spedition 25, Selfstorage 36,
   Fahrschulen 57, Kursbetrieb 132, **Membership Management 344**. Ein Vorgang mit
   eigenem Kategorienamen ist nie unbesetzt — der billigste Test der ganzen Folge.
1. **Ein Abruf: Suchwort + „software".** Kommt die Landingpage eines *branchenneutralen*
   Anbieters genau zum Suchwort zurueck, sind Frage 4 und 6 zugleich beantwortet —
   Kanal vorhanden, Kanal besetzt. Hat bei sechs von sieben Vorgaengen das Urteil
   vorweggenommen. Noch billiger: **pruefen, ob das Suchwort als Domain vergeben ist**
   (`unterweisungsnachweis.de`, `diktat.ai` — beide gehoeren Wettbewerbern).
2. **Laesst sich der Kern in einem Satz als Rechen- oder Verarbeitungsvorschrift
   schreiben?** Dann ist er eine Funktion, kein Produkt, und Frage 4 ist beantwortet.
   *Verschaerfung 2026-08-31:* Ist der Kern sogar **als Zukaufteil ausgepreist**
   (Transkription 0,006 USD/min), erledigt das Frage 3 und 4 in einem Satz.
3. **Wo endet der Vorgang, und sitzt dort jemand?** Endet er in einem System, das der
   Betrieb schon hat (Kalender, ERP, PVS, PIMS, Pflegesoftware, Abrechnungszentrum),
   ist dessen Hersteller Wettbewerber und Zugang zugleich; als Tarifstufe verkauft ist
   der Einzelpreis fast null. Fliesst dort Geld, gehoert der Vorgang dem Abwickler.
4. **Gilt die Pflicht branchenunabhaengig?** Dann ist die Vereinigung unbegrenzt — ein
   Warnzeichen, kein Fund. Zaehlung sparen, sofort Frage 4.
5. Erst dann zaehlen.

## Was funktioniert

- **2026-08-31** — **Aufnahmekriterium fuer eine Branche: nicht das aehnlich klingende
  `handarbeit`-Feld, sondern der Nachweis, dass ein Anbieter genau dieses Produkt genau
  fuer diese Branche verkauft.** Strenger als die Feldlektuere und billiger zu pruefen.
  Beim Diktat hat es die Hebammen sauber aussortiert und die Pflege sauber aufgenommen
  (voize), obwohl deren Feld etwas anderes nennt.
- **2026-08-30** — **Steht der Vorgang in einem Gesetz, das die Betroffenen selbst
  aufzaehlt, ist der Gesetzestext die Branchenliste.** § 302 SGB V nennt neun Gewerke;
  die Vereinigung stieg von 74.662 auf 96.643. Nach der Norm suchen, nicht nach Branchen.
- **2026-08-30** — **Die Kundenliste des horizontalen Anbieters beweist besser als jedes
  eigene Argument, dass der Vorgang derselbe ist** — und, wenn sie mehrere Branchen
  nennt, zugleich dass die Vereinigung schon gehoben wird (Philips SpeechLive fuehrt
  Juristen, Gesundheitswesen, Bauwesen, Finanzen, Journalismus nebeneinander).
- **2026-08-30** — Zuerst die `handarbeit`-Felder woertlich nebeneinanderlegen, dann erst
  addieren. `grep -h -E "^(segment|betriebe|handarbeit|potenzial):"` ueber alle
  Marktprofile, auf 220 Zeichen beschnitten — ein Aufruf statt 300.000 Zeichen Profiltext.
- **2026-08-30** — Bei Pflichtvorgaengen den **Volltext der Behoerdenseite** holen, nicht
  den Suchauszug. Er hat eine Vorgangsdefinition schon einmal gedreht (2.588 statt 15.241
  Betriebe).

## Was nicht funktioniert

- **2026-08-31** — **Ein Suchwort, das alle Branchen gleich nennen, ist die Gegenanzeige,
  nicht der Fund.** Zweimal belegt: Leistungsnachweis (der Gesetzgeber hat den Vorgang
  1989 branchenuebergreifend definiert, die Antwort darauf ist eine Industrie) und Diktat
  (alle vier Branchen suchen „Diktiersoftware" / „AI scribe"). **Die Bedingung ist enger
  als „gleicher Vorgang in mehreren Branchen": Der Vorgang muss gleich sein, ohne dass
  die Branchen ihn gleich nennen.** Sonst hat der gemeinsame Name den gemeinsamen
  Anbieter laengst hervorgebracht.
- **2026-08-31** — **Alle Vorbedingungen erfuellt heisst nichts, im Gegenteil.** Die
  Beitragsabrechnung hatte die beste Ausgangslage aller acht: groesste Vereinigung
  (728.406), grosser Kern, kleine *und* haltbare Schale, belegte teure Handarbeit,
  Suchkanal, keine Erlaubnispflicht, kein Verband als Wettbewerber. Genau deshalb war sie
  besetzt. **Ein Vorgang, den sehr viele ueber Branchengrenzen hinweg gleich ausfuehren,
  ist keine Luecke, sondern eine Produktkategorie.**
- **2026-08-31** — **Ist der Vorgang selbst ein Zahlungsvorgang, ist Frage 4 beantwortet,
  bevor sie gestellt wird.** Stripe Billing preist ihn mit 0,7 Prozent des Volumens ein,
  Mahnlauf und Wiedereinzug inbegriffen; daneben existiert eine eigene horizontale
  Kategorie nur fuer den Nachlauf („dunning management software"). Schaerfere Fassung von
  Stufe 3 der Prueffolge.
- **2026-08-31** — **Findest du keinen Grund, warum die vorhandenen Anbieter die
  Vereinigung nicht heben koennen, ist die Antwort meist: weil einer sie schon hebt.**
  Beim Diktat war es Philips. Die Rollenbeschreibung nennt das ein Warnsignal — es ist
  eher ein Urteil.
- **2026-08-30** — **Frage 3 hat zwei Absterbezonen.** Grosser Kern: hat schon jemand
  gebaut. Winziger Kern: ist eine Funktion, kein Produkt. Sieben Vorgaenge lagen
  ausserhalb des schmalen Bands dazwischen, an beiden Enden.
- **2026-08-30** — **Frage 3 fragt nach der Groesse der Schale und muesste nach ihrer
  Haltbarkeit fragen.** *Konfiguration* (einmal gesetzt, jahrelang gueltig) gegen
  *Abonnement* (Rahmenvertraege, Schluesselverzeichnisse, woechentliche Pflege) — die
  zweite Art reisst schon fuer sich das Zwei-Stunden-Budget.
- **2026-08-30** — **Nach „machen sie denselben Vorgang?" sofort die zweite Frage: „wuerde
  derselbe Kunde beide Meldungen machen?"** Nein heisst: Summe, kein Markt.
- **2026-08-30** — **„Die Vereinigung ist gross genug" rettet nichts.** Dreimal belegt
  (6.396 / 60.900 / 5.820 EUR, alle drei `tot`). `traegt_5000` und `befund` sind zwei
  Fragen. — *Gegenprobe 2026-08-31:* Beim Diktat fielen sie erstmals zusammen (1.643 EUR,
  `nein`, `tot`). Wenn beide zeigen, ist das Urteil leicht; die Faelle davor waren die
  schwierigen.
- **2026-08-30** — **Wo ein Preis gezahlt wird, sitzt schon jemand; wo niemand sitzt, wird
  auch nichts gezahlt.** „Kein Anbieter gefunden" zuerst als Warnsignal lesen.

## Offene Fährten

- **2026-08-30, zweimal bestaetigt** — **Zu jedem Vorgang zuerst die Endkundengruppe
  suchen, nicht die Betriebe.** Verbrauchsabrechnung: 27.800 Betriebe gegen 5,5 Mio.
  private Vermieter, Faktor 200. Beitragsabrechnung: 112.647 Betriebe gegen 615.759
  eingetragene Vereine, Faktor 5. Marktprofile kennen nur Betriebe, deshalb fehlt diese
  Seite systematisch — und sie ist jedes Mal die mit dem Preisboden null.
- **2026-08-31** — **Die Zahl der Arzt-, Zahnarzt- und Psychotherapiepraxen ist frei nicht
  auffindbar: dritter erfolgloser Versuch.** KBV zeigt sie nur in einer XLS-Datei hinter
  der Grafikseite, Destatis rechnet aus einer 7-Prozent-Stichprobe hoch, Statista steht
  hinter der Schranke. Das ist der groesste fehlende Block der Fabrik ueberhaupt. Wenn,
  dann ueber die KBV-XLS oder das Bundesarztregister-PDF — **nicht** noch einmal ueber
  eine Suchanfrage. Ebenfalls ohne amtliche Zahl: das Heilmittelverzeichnis des
  GKV-Spitzenverbands (nur Suchmaske), DGUV-V3-Pruefdienstleister, Torpruefer,
  Regalpruefer, Trinkwasser-Probenehmer, Asbest-Fachbetriebe (53 Kammerlisten).
- **2026-08-30** — **Ein herrenloser Vorgang: „vertraglicher Leistungsnachweis an den
  Auftraggeber".** Die Facility-Dienstleister (34.288) sind zweimal aussortiert worden
  und der Vorgang steht in keinem Eintrag von `quellen.yml`. Die Liste aendert der
  Betreiber.
- **2026-08-30** — **HOPPE Wartungsplaner bedient zwei von zwei untersuchten
  Fristen-Vorgaengen.** Vor jedem weiteren Fristen-Vorgang ein Abruf dort.
- **2026-08-30** — **Das Wirtschaftsportal des Landes ist ein horizontales Werkzeug** und
  gehoert bei jedem Behoerdenvorgang in Frage 4 (WSP.NRW, Hamburg). Abruf: „<Meldung>
  Onlinedienst Serviceportal <Land>".

## An den Portfolio-Manager

- **2026-08-30, dritter Beleg 2026-08-31** — **G7 misst bei sehr grossen Vereinigungen
  nichts mehr.** Ein Promille von 2,1 Mio. Betrieben ergibt 60.900 EUR, eines von 728.406
  ergibt 5.827 EUR — beide nehmen die Schwelle, beide Vorgaenge sind eindeutig tot. Der
  Anteil unterstellt einen Markt mit freien Kunden; ist er gesaettigt, waechst nur der
  Nenner. Ich lasse `traegt_5000` und `befund` auseinanderfallen, statt die Rechnung
  passend zu machen. **Vorschlag: G7 um eine Besetzungsschranke ergaenzen** — eine
  Verzeichniskategorie ueber 50 Produkte setzt den Anteil auf null, nicht auf ein Promille.
- **2026-08-30** — Das Dachdeckerprofil vom 2026-08-28 ordnet die objektbezogene
  Asbestanzeige „mittleres + hohes Risiko" zu; nach dem NRW-Volltext gilt sie nur bei
  hohem Risiko. Nicht falsch, aber aufwandsueberzeichnend. Ich fasse `signals/maerkte/`
  nicht an.
- **2026-08-31, zur Eichung dieser Rolle:** Die Kontrollprobe hat funktioniert. Der
  vorab als besetzt bekannte Vorgang kam als `tot` heraus, und zwar an der vorgesehenen
  Stelle (Frage 4, horizontales Werkzeug loest es gut) statt ueber ein nachgeschobenes
  Argument. **Das Urteil dieser Rolle ist damit nach oben geeicht, nicht nach unten:**
  Sieben von sieben `tot` heisst bisher nur, dass sieben besetzte Vorgaenge als besetzt
  erkannt wurden — ob die Rolle einen echten Fund auch als Fund erkennen wuerde, ist
  weiterhin ungeprueft. Dafuer fehlt eine Gegenprobe mit bekannt *unbesetztem* Vorgang.

## Einträge

- **2026-08-31** — **Beitrags- und Mitgliedsabrechnung mit Zahlungsnachlauf**: vier
  Branchen, 728.406 Organisationen, `traegt_5000: ja` (5.827 EUR) und trotzdem `tot`.
  Gestorben an Frage 4 und 5 zugleich, deutlicher als bei jedem Vorgang zuvor: eine
  horizontale Zahlungsschicht mit dem Nachlauf als Kernfunktion (Stripe Billing 0,7 %,
  GoCardless, Chargebee, Recurly), eine eigene Kategorie nur fuer den Nachlauf, **344
  Produkte** in der Verzeichniskategorie Membership Management, und ein deutscher
  Anbieter (GRUEN VEWA), der Vereine, Verbaende, Kammern, Parteien und Gewerkschaften auf
  einer Landingpage bedient — die Vereinigung ist laengst gehoben. Preisboden null in
  beiden Sprachraeumen. Bewusst *nicht* mitgezaehlt: Selfstorage (61.856), weil der
  Nachlauf dort ein gesetzlich getakteter Pfandrechtslauf je US-Bundesstaat ist.
- **2026-08-31** — **Vorgangsdokumentation per Diktat** (Kontrollprobe): vier Branchen,
  109.547 Betriebe, 1.643 EUR, `tot`. Drei Anbieterschichten uebereinander —
  branchenneutral (Philips SpeechLive 10,90-14,50 EUR plus 24,90 EUR Spracherkennung,
  Nuance Dragon), branchenspezifisch (ueber 25 allein im deutschen Gesundheitsmarkt,
  voize in der Pflege, 12 KI-Diktatanbieter in der Tiermedizin) und der Systemhersteller
  selbst (Dragon Copilot, PetDesk Scribe „im Paket enthalten", Scribenote kostenlos).
  Neu gegenueber allen Vorgaengen davor: **Frage 3 und Frage 4 fielen zusammen**, weil
  der Kern als API ausgepreist ist (0,006 USD/min bei OpenAI, 0,0025 bei AssemblyAI).
  Wofuer bezahlt wird, ist ausschliesslich die Schale — und die ist je Branche eine
  eigene Integration in ein eigenes fuehrendes System.
