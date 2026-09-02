---
typ: prozess
erfasst: 2026-08-31
auftrag: Vorgangsdokumentation per Diktat statt Tastatur
vorgang: Die fachkundige Person spricht waehrend oder direkt nach einem Kundentermin frei, was beobachtet und getan wurde; daraus muss ein strukturierter, aufbewahrungspflichtiger Eintrag im fuehrenden System des Betriebs entstehen (Feldstruktur, Vorlage, Fachbegriffe), den der Betrieb auf Verlangen vorlegen muss.
branchen:
  - name: Tierarztpraxen Deutschland | betriebe: 10.385 | quelle: signals/maerkte/2026-08-29-tierarztpraxen.md (Bundestieraerztekammer, Stand 31.12.2025)
  - name: Tierarztpraxen USA/UK/CA/AU | betriebe: 43.500 | quelle: signals/maerkte/2026-08-30-tierarztpraxen-englischsprachig.md (AVMA/RCVS/StatCan/IBISWorld, konservativ)
  - name: Zugelassene Physiotherapiepraxen Deutschland | betriebe: 40.113 | quelle: signals/maerkte/2026-08-29-physiotherapiepraxen.md (GKV-Spitzenverband, Stand 30.04.2022)
  - name: Ambulante Pflegedienste Deutschland | betriebe: 15.549 | quelle: signals/maerkte/2026-08-29-ambulante-pflegedienste.md (Destatis Pflegestatistik, Stand 18.12.2024)
vereinigung: 109.547
kern: Sprache aufnehmen, in Text wandeln und den Text in die Felder und Vorlagen des fuehrenden Praxis- bzw. Pflegesystems schreiben.
schale: Fachvokabular, Vorlagenstruktur (SOAP, Pflegebericht, Befund), die Schnittstelle in ein je Branche anderes fuehrendes System und das jeweilige Aufbewahrungs- und Datenschutzregime.
schale_groesser_als_kern: ja
horizontal_besetzt: ja
horizontal_werkzeug: Philips SpeechLive (10,90 bis 14,50 EUR je Nutzer und Monat, Spracherkennung als Zusatz 24,90 EUR) bedient laut eigener Seite Juristen, Gesundheitswesen, Bauwesen, Finanzen, Journalismus und Strafverfolgung nebeneinander; Nuance Dragon in den Varianten Legal und Medical; darunter reine Transkriptions-API ab 0,006 USD je Minute (OpenAI whisper-1), 0,0025 USD bei AssemblyAI. Es gibt nichts, was diese Werkzeuge nicht koennen -- sie decken genau den Kern ab, und sie decken ihn ueber dieselben Branchen hinweg ab, die eine Vereinigung heben muesste.
vertikal_anbieter: >25 allein im deutschen Gesundheitsmarkt (Vergleichsliste abrechnungsstelle.com nennt u. a. ORPHEUS 15 EUR, Noa Notes 39-89 EUR, Heidi health kostenlos bis 60 EUR, Eudaria 169 EUR, Corti 99 USD, Dragon Copilot, tomedo, Idana, SpeaKING); Pflege: voize (12-15 EUR je Nutzer und Monat, ueber 180.000 unterstuetzte Pflegekraefte); Tiermedizin: mindestens 12 KI-Diktatanbieter im englischsprachigen Raum (VetRec 99 USD, Scribenote kostenlos, Otto Scribe 24 USD, PetDesk Scribe im Paket enthalten) und petleo/VOISA in Deutschland
erreichbar_ueber: Suche -- der Kanal existiert branchenuebergreifend, ist aber von Herstellern, Vergleichsportalen und Fachpresse vollstaendig belegt
suchwort: "Diktiersoftware" / "KI-Dokumentation" / "AI scribe" -- branchenuebergreifend dasselbe, deshalb branchenuebergreifend besetzt
preis_plausibel: 15 EUR je Nutzer und Monat (ORPHEUS 15 EUR; voize 12-15 EUR) -- mit einem Preisboden von null, weil Heidi health und Scribenote kostenlose Tarife fuehren und PetDesk das Diktat im Paket beilegt
kunden_erreichbar: 110 (ein Promille von 109.547) -- Promille, weil der Kanal zwar belegt, aber von den vorhandenen Anbietern besetzt ist; ein Prozent waeren 1.095
monatsumsatz: 1.643 EUR (Promille) bzw. 16.425 EUR (Prozent)
traegt_5000: nein
befund: tot
---

# Vier Branchen mit 109.547 Betrieben sprechen ihre Dokumentation statt sie zu tippen — und werden dabei von mindestens drei Schichten Anbietern gleichzeitig bedient

Dieses Profil ist die **Kontrollprobe** aus `quellen.yml`: ein Vorgang, von dem vorab
bekannt war, dass er besetzt ist. Es prueft nicht den Markt, sondern das Urteil dieser
Rolle. Der Befund faellt so aus wie erwartet, aber an einer Stelle, die vorher nicht
feststand — nicht an der Menge der Anbieter, sondern daran, dass **Frage 4 und Frage 3
zusammenfallen**: Das horizontale Werkzeug ist zugleich der ganze Kern.

## 1. Der Vorgang

Vier Merkmale, jede Branche einzeln dagegen gehalten:

1. Die Aufzeichnung ist **gesetzlich vorgeschrieben und aufbewahrungspflichtig** (fuer
   Heilberufe § 630f BGB, fuer die Pflege die Dokumentationspflicht nach SGB XI, fuer
   Tierarztpraxen die TAeHAV).
2. Der Sprecher ist die **fachkundige Person selbst**, nicht eine Schreibkraft, die eine
   fertige Vorlage abtippt.
3. Das Ergebnis ist ein **strukturierter Datensatz im fuehrenden System** — Felder,
   Vorlagenabschnitte, Codes —, keine freie Textdatei.
4. Der Vorgang **wiederholt sich mehrfach taeglich**, je Termin einmal.

Das dritte Merkmal ist das entscheidende. Es trennt diesen Vorgang vom klassischen
Kanzleidiktat, bei dem am Ende ein freies Dokument steht, und es ist der Grund, warum
der Vorgang ueberhaupt je etwas kosten koennte: Ein Textblock ist wertlos, ein
befuellter Datensatz ist der Nachweis.

## 2. Wer ihn macht

| Branche | Betriebe | Beleg, dass dort wirklich diktiert wird |
|---|---:|---|
| Tierarztpraxen DE | 10.385 | petleo, VOISA (Repo-Profil 2026-08-29) |
| Tierarztpraxen US/UK/CA/AU | 43.500 | 12 KI-Diktatanbieter (Repo-Profil 2026-08-30) |
| Physiotherapiepraxen DE | 40.113 | ORPHEUS nennt Physiotherapeuten als Zielgruppe |
| Ambulante Pflegedienste DE | 15.549 | voize, ueber 180.000 unterstuetzte Pflegekraefte |
| **Vereinigung** | **109.547** | |

Aufnahmekriterium war nicht die Aehnlichkeit des `handarbeit`-Felds, sondern der
Nachweis, dass ein Anbieter fuer genau diese Branche genau dieses Produkt verkauft. Das
ist strenger als die Feldlektuere und hier zugleich billiger zu pruefen.

**Bewusst nicht mitgezaehlt:**

- **Freiberufliche Hebammen (19.000).** Ihr `handarbeit`-Feld nennt die Abrechnung in
  Fuenf-Minuten-Einheiten, nicht die Dokumentation; ein Diktatanbieter fuer dieses
  Segment war nicht auffindbar. Merkmal 4 ist bei wenigen Terminen am Tag ausserdem
  fraglich.
- **Human- und Zahnmedizin, Psychotherapie.** Das ist der mit Abstand groesste Block und
  fehlt trotzdem: Eine belegte Zahl der Praxen ist frei nicht auffindbar. Die KBV zeigt
  sie nur in einer XLS-Datei hinter der Grafikseite, Destatis rechnet aus einer
  Stichprobe hoch, Statista steht hinter der Schranke (dritter erfolgloser Versuch, siehe
  Logbuch). **Die Vereinigung ist dadurch systematisch zu klein** — und das schaerft den
  Befund, statt ihn zu schwaechen: Der fehlende Block ist der am dichtesten besetzte.
- **Rechtsanwaelte (167.547 zugelassene Personen, BRAK zum 01.01.2026).** Zwei Gruende:
  Das ist eine Personen- und keine Betriebszahl (die BRAK weist nur 5.462
  Berufsausuebungsgesellschaften aus), und das Diktat endet dort in einem freien
  Schriftsatz, nicht in einem Feldsatz — Merkmal 3 ist verletzt.

## 3. Kern und Schale

Der Kern ist in einem Satz als Verarbeitungsvorschrift schreibbar: *Audio aufnehmen, in
Text wandeln, Text auf Felder verteilen.* Nach meiner Lehre vom 2026-08-30 ist damit
Frage 4 bereits beantwortet — was sich als Vorschrift schreiben laesst, ist eine
Funktion, kein Produkt. Hier kommt eine Verschaerfung dazu, die es bei den sechs
Vorgaengen davor nicht gab: Der Kern ist nicht nur klein, er ist **als Zukaufteil
ausgepreist**. 0,006 USD je Minute bei OpenAI, 0,0025 USD bei AssemblyAI, rund 0,04 USD
je Stunde bei Groq. Eine Tierarztpraxis mit den im englischsprachigen Profil belegten
2,5 bis 4 Stunden Dokumentation am Tag verbraucht damit Rohleistung fuer etwa 24 USD im
Monat beim Listenpreis und fuer unter 3 USD beim guenstigsten Anbieter.

Alles, wofuer tatsaechlich bezahlt wird, sitzt in der Schale: dass das Werkzeug
„Interdigitalmykose" oder „Dekubitus Kategorie 2" kennt, dass es einen SOAP-Bogen oder
einen Pflegebericht fuellt, und vor allem, dass es **in das bereits vorhandene System
schreibt**. voize wirbt genau damit — Uebertragung „in bestehende Pflegesoftware".

Diese Schale ist keine Konfiguration, sondern je Branche eine eigene Integration in ein
eigenes fuehrendes System. Damit ist die Antwort auf Frage 3 eindeutig: **Die Schale ist
groesser als der Kern.** Es sind vier Vorgaenge mit einem gemeinsamen Oberbegriff.

## 4. Das horizontale Werkzeug

Es existiert, es ist ausgepreist, und es bedient bereits genau die Branchenvereinigung,
die diese Rolle sucht. **Philips SpeechLive** nennt auf der eigenen Seite als Zielgruppen
Juristen, Gesundheitswesen, Bauwesen, Finanzen, Journalismus und Strafverfolgung
nebeneinander — 10,90 EUR (Basic) bzw. 14,50 EUR (Pro) je Nutzer und Monat, Spracherkennung
als Zusatz fuer 24,90 EUR, ein Legal AI Assistant ab 49 EUR. Daneben steht Nuance Dragon in
den Varianten Legal und Medical, und Haendler wie oa-s.de fuehren fuenf Branchenseiten
unter einem Dach (Aerzte, Kliniken, medizinische Gutachter, Anwaelte, Professionals).

Nach meiner Lehre vom 2026-08-30 beantwortet ein solcher Treffer Frage 4 und Frage 6 in
einem Zug: Der gemeinsame Kanal existiert — und er ist besetzt. Die Domainprobe
bestaetigt es, `diktat.ai` gehoert einem Anbieter.

Die uebliche Rueckfrage dieser Rolle lautet, *was genau* das horizontale Werkzeug nicht
kann. Sie laeuft hier ins Leere. Der Kern ist Spracherkennung, und Spracherkennung ist
das, was diese Werkzeuge sind.

## 5. Die vertikalen Anbieter

Sie sind vorhanden, aber sie sind hier **kein** positives Signal, weil sie nicht die
Luecke eines fehlenden horizontalen Werkzeugs fuellen, sondern oberhalb eines
vorhandenen sitzen. Drei Schichten liegen uebereinander:

- **Branchenneutral:** Philips, Nuance, dazu die Transkriptions-APIs als Selbstbau.
- **Branchenspezifisch:** allein die Vergleichsliste eines deutschen Abrechnungsdienstes
  fuehrt ueber 25 Anbieter medizinischer Spracherkennung — ORPHEUS 15 EUR, Philips
  SpeechLive 24,90 EUR Zusatz, Noa Notes 39 bis 89 EUR, Heidi health kostenlos bis 60 EUR,
  Eudaria 169 EUR, Corti 99 USD, dazu rund 18 weitere ohne oeffentlichen Preis. In der
  Pflege voize, in der Tiermedizin zwoelf Anbieter im englischsprachigen Raum.
- **Der Systemhersteller selbst:** Dragon Copilot (Microsoft/Nuance), tomedo, PetDesk
  Scribe „im Paket enthalten", Scribenote mit kostenlosem Tarif.

Die dritte Schicht ist die toedliche. Mein Vorabtest lautet: *Wo endet der Vorgang, und
sitzt dort jemand?* Er endet im fuehrenden System — PVS, PIMS, Pflegesoftware —, und
dessen Hersteller ist Wettbewerber und Zugangsweg zugleich. Als Tarifstufe verkauft ist
der Einzelpreis des Diktats die Differenz zweier Tarife, also fast null. PetDesk und
Scribenote zeigen das bereits im Preisblatt.

Ein Grund, warum keiner der vorhandenen Anbieter die Vereinigung heben koennte, liess
sich nicht finden. Nach der Rollenbeschreibung ist genau das das Warnsignal: Wenn keiner
gehindert ist, ist es kein unbesetzter Markt. Philips hebt sie bereits.

## 6. Der gemeinsame Kanal

Er existiert, und er ist ungewoehnlich sauber: „Diktiersoftware", „KI-Dokumentation",
„AI scribe" — dieselbe Anfrage aus allen vier Branchen. Genau das erklaert die
Besetzung. Ein Suchwort, das alle stellen, ist kein Vorteil dieser Fabrik, sondern der
Grund, warum die Anbieter dort schon stehen: Hersteller, Vergleichsportale
(vetsoftwarehub, abrechnungsstelle.com) und Fachpresse besetzen die erste Seite.
Deshalb Promille, nicht Prozent.

## 7. Die Rechnung

    Preis 15 EUR je Nutzer und Monat  ×  110 Betriebe (ein Promille)  =  1.643 EUR
    Preis 15 EUR je Nutzer und Monat  ×  1.095 Betriebe (ein Prozent) =  16.425 EUR

Genommen wird **das Promille**: Der Kanal ist belegt, aber vollstaendig besetzt —
G7 laesst das Prozent nur zu, wo der Kanal belegt *und* erreichbar ist.

Der Preis ist am vertikalen Nischenanbieter belegt, wie die Rolle es verlangt: ORPHEUS
15 EUR, voize 12 bis 15 EUR. Er ist trotzdem zu optimistisch, weil der Boden bei null
liegt — Heidi health und Scribenote fuehren kostenlose Tarife, PetDesk legt das Diktat
bei. Selbst die 99 USD von VetRec im englischsprachigen Tiermarkt aendern daran nichts;
sie stehen neben einem kostenlosen Wettbewerber in derselben Liste.

**1.643 EUR gegen eine Schwelle von 5.000 EUR: `traegt_5000: nein`.** Das ist der erste
der sieben Vorgaenge, bei dem Rechnung und Befund in dieselbe Richtung zeigen. Bei den
drei Vorgaengen davor fielen sie auseinander (Terminwiederbesetzung 6.396 EUR,
Unterweisungsnachweis 60.900 EUR, Leistungsnachweis 5.820 EUR — alle drei `tot`).

## Die Luecke

**Es klafft keine.** Der Vorgang ist auf allen drei Ebenen gleichzeitig bedient: von
branchenneutralen Werkzeugen, die ihn seit Jahrzehnten koennen und ihn ueber genau diese
Branchen hinweg verkaufen; von mindestens 25 branchenspezifischen Anbietern allein im
deutschen Gesundheitsmarkt; und von den Herstellern der fuehrenden Systeme, die ihn als
Paketbestandteil beilegen. Der Kern ist als API fuer 0,006 USD je Minute zu kaufen, die
Schale ist je Branche eine eigene Integration, und der gemeinsame Kanal ist das Suchwort,
auf dem die Anbieter bereits ranken.

Was diese Kontrollprobe fuer die Rolle ergibt, ist die eigentliche Ausbeute: Ein
Vorgang, der so klar branchenuebergreifend ist, dass alle Branchen dasselbe Wort dafuer
suchen, ist deshalb kein Fund, sondern die Gegenanzeige. Dieselbe Struktur hatte der
Leistungsnachweis gegenueber einem Kostentraeger (2026-08-30), wo der Gesetzgeber den
Vorgang selbst branchenuebergreifend definiert hatte. **Die Bedingung, unter der diese
Rolle etwas findet, ist enger als „gleicher Vorgang in mehreren Branchen": Der Vorgang
muss gleich sein, ohne dass die Branchen ihn gleich nennen.** Sonst hat der gemeinsame
Name den gemeinsamen Anbieter laengst hervorgebracht.

## Was unklar ist

- **Die Vereinigung ist zu klein, nicht zu gross.** Human- und Zahnmedizin sowie
  Psychotherapie fehlen mangels frei belegbarer Praxiszahl; sie waeren vermutlich der
  groesste Block. Am Befund aendert das nichts — der fehlende Block ist der am
  dichtesten besetzte.
- **Die Physiotherapiepraxen sind ueber einen Anbieterhinweis aufgenommen** (ORPHEUS
  nennt sie als Zielgruppe), nicht ueber ein eigenes Diktatprodukt. Von den vier
  Branchen ist ihre Zugehoerigkeit die schwaechste.
- **Der Preis 15 EUR ist je Nutzer, die Vereinigung zaehlt Betriebe.** Ein ambulanter
  Pflegedienst hat viele Nutzer, eine Einzelpraxis einen. Die Rechnung setzt darum
  konservativ einen Nutzer je Betrieb an; mehr Nutzer wuerden den Preis je Betrieb heben,
  aber auch den Vertriebsaufwand.
- **Ob die kostenlosen Tarife (Heidi health, Scribenote) tragfaehig sind**, ist nicht
  geprueft. Nach der Lehre vom 2026-08-30 ist die Null im englischsprachigen Raum
  regelmaessig ein Geschaeftsmodell und kein Lockangebot; hier fliesst allerdings kein
  Zahlungsstrom durch die Software, der sie refinanzieren koennte. Das ist die einzige
  offene Frage, an der sich der Preisboden noch bewegen koennte.
