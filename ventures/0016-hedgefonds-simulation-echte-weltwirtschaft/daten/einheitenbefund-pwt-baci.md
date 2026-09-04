---
typ: einheitenbefund
paket: 0025-quelleneinheit-pwt-baci
rolle: datenbauer
datum: 2026-09-02
gegenstand: Drei ungemessene Groessen — PWT-Kapitalstock (Reihe 3), Basisjahr PWT 11.0 (Reihe 3), BACI-Handelswert (Reihe 14) — gemessen gegen die Dokumentation der Quellen
groessen_gemessen: 1 von 3 (BACI-Handelswert, Abschnitt 1)
groessen_nicht_gemessen: 2 von 3 (PWT-Kapitalstock Abschnitt 3, Basisjahr PWT 11.0 Abschnitt 4)
faktor_baci_nach_tsd_usd: 1 (exakt, gemessen — nicht als Vorgabewert eingesetzt; Rechnung in Abschnitt 1)
faktor_pwt_nach_tsd_usd: ungemessen (kein Faktor eingetragen)
preisbasis_baci: laufend ("current USD", gemessen)
basisjahr_pwt: ungemessen
folge_t5_klasse_2: als Frage an den Architekten formuliert, vier Moeglichkeiten benannt, keine gewaehlt (Abschnitt 5)
reihe_16_einheitengleichheit: Groessenordnung gleich (beide Tausend USD), Preisbasis verschieden (BACI laufend, WDI konstant 2015) — Abschnitt 6
seitenabrufe: 20 verschiedene URLs (Abschnitt 7, Nr. 1 bis 20)
abrufe_ohne_ergebnis: 8 von 20 (Nr. 4, 5, 9, 10, 11, 13, 15, 18)
websuchen: 3
befund_an_architekt: ja
befund_an_projektmanager: ja
befund_an_betreiber: ja (Abschnitt 3, Absatz "Woran es haengt")
reihen_toml_angefasst: nein
---

# Eine der drei Groessen ist gemessen, und es ist die, die weh tut: BACI meldet **laufende** Preise

Die kurze Fassung, damit der Rest lesbar bleibt:

| Groesse | gemessen? | Ergebnis | Folge |
|---|---|---|---|
| BACI-Handelswert (Reihe 14) | **ja** | `v` = „Value of the trade flow (in thousands current USD)" | Faktor **1** exakt — aber **laufende** Preise gegen T5 Klasse 2 |
| PWT-Kapitalstock (Reihe 3) | **nein** | Quelldokumentation liegt nur als PDF vor, und jede PDF-Datei ist mit den Werkzeugen dieser Rolle unlesbar | kein Faktor; die Frage bleibt offen und ist beziffert |
| Basisjahr PWT 11.0 (Reihe 3) | **nein** | dieselbe Sperre; die eine lesbare Quellseite nennt **zwei** Jahre (2021 und 2017) und keines davon als Preisbasis | kein Basisjahr; T42 haengt daran |

**Kein Faktor steht hier ohne Zitat, und keine `1` steht als Vorgabewert.** Die 1 bei BACI
ist ausgerechnet (Abschnitt 1); bei PWT steht kein Faktor, sondern die offene Frage.

---

## 1. BACI-Handelswert (Reihe 14) — gemessen

**Feldname der Quelle:** `v`

**Einheit im Wortlaut der Quellendokumentation:**

> „Value of the trade flow (in thousands current USD)"

**Abruf-URL:** `https://www.cepii.fr/DATA_DOWNLOAD/baci/doc/DescriptionBACI.html`
**Abrufdatum:** 2026-09-02

Dieselbe Seite nennt die uebrigen Spalten, und sie gehoeren dazu, weil `q` beim
Jahrgangsbau nicht mit `v` verwechselt werden darf:

| Spalte | Wortlaut der Quelle |
|---|---|
| `t` | „Year" |
| `k` | „Product category (HS 6-digit code)" |
| `i` | „Exporter (ISO 3-digit country code)" |
| `j` | „Importer (ISO 3-digit country code)" |
| `v` | „Value of the trade flow (in thousands current USD)" |
| `q` | „Quantity (in metric tons)" |

**Der Umrechnungsfaktor nach Tausend USD, als Rechnung:**

```
1 Einheit v   = 1.000 laufende USD          (Quellendokumentation, Wortlaut oben)
1 Modelleinheit = 1.000 USD                 (T5 Klasse 2: "Tausend USD")
Faktor          = 1.000 / 1.000 = 1         exakt, ganzzahlig
```

Der Faktor ist **1**, und er ist es, weil beide Seiten in Tausendern rechnen — nicht,
weil nichts gemessen wurde. Das ist der Unterschied, um den es dem Arbeitspaket geht.

**Ein Vorbehalt, der in den Uebertrag gehoert.** Die Seite nennt **keine
Versionsnummer**. `reihen.toml` bindet Reihe 14 an „CEPII BACI, Nomenklatur HS92,
Fassung 202601 (Stand 2026-01-30)"; die Beschreibungsseite spricht allgemein von den
HS-Revisionen 92 bis 17 und Daten bis 2022. Der Versuch, die Freigabemitteilung zu
202601 gegenzulesen, ist an der PDF-Sperre gescheitert (Abschnitt 7, Nr. 5). Gemessen
ist damit: **die Einheit der BACI-Beschreibungsseite am 2026-09-02**, nicht die Einheit
der Fassung 202601 im Wortlaut ihrer eigenen Mitteilung. Wer den Faktor nach
`reihen.toml` uebertraegt, uebertraegt diesen Satz mit.

## 2. Preisbasis BACI — gemessen: **laufende Preise**

Dieselbe Zeile traegt beides. Das Wort steht im Wortlaut der Quelle:

> „Value of the trade flow (in thousands **current** USD)"

(Hervorhebung von mir; die Quelle setzt keine.) Abruf-URL und Abrufdatum wie in
Abschnitt 1.

**Gegenprobe in die andere Richtung, weil ein Positivfund allein hier nicht traegt:**
Ich habe dieselbe Seite gezielt danach abgefragt, ob sie irgendwo Deflationierung,
konstante Preise, Preisindizes oder ein Basisjahr nennt. Ergebnis: **nichts davon steht
auf der Seite.** Ein Basisjahr fehlt also nicht, weil ich es uebersehen haette, sondern
weil die Quelle keines fuehrt — was zu „current" passt und die Messung stuetzt.

Damit ist die schwerste offene Sache des Vorhabens (`rueckstand.md` Punkt 3) nicht
entschieden, aber zum ersten Mal **entscheidbar gestellt**. Die Folge steht in
Abschnitt 5.

## 3. PWT-Kapitalstock (Reihe 3) — nicht gemessen

**Kein Feldname, keine Einheit, kein Faktor.** Was fehlt, fehlt aus einem benennbaren
Grund, und der Grund ist nicht PWT.

**Die offene Frage, in der Form, in der sie beantwortbar ist — drei Teile:**

1. **Welche** Kapitalstockreihe traegt Reihe 3? `reihen.toml` fuehrt fuer Reihe 3
   `codes = []` und `code_herkunft = "nirgends festgeschrieben"`. PWT fuehrt den
   Kapitalstock nicht als eine Groesse: Die Uebersichtsseite der Quelle nennt neben der
   Hauptdatei eine eigene Datei „Capital detail … Investment, capital stock and capital
   consumption data by assets" (Abruf Nr. 6). *Vermutung, ausdruecklich als solche
   markiert und aus Suchtreffern zu **PWT 10.0**, nicht aus einem eigenen Abruf der
   11.0-Dokumentation:* Die Hauptdatei fuehrt mehrere Kapitalstockreihen nebeneinander
   (zu laufenden Kaufkraftparitaeten gegen konstante nationale Preise), die sich in
   Einheit **und** Preisbasis unterscheiden. Ist das so, ist die Wahl der Reihe eine
   Entwurfsentscheidung des Architekten und keine Messung — und sie geht der
   Einheitenfrage voraus.
2. **In welcher Einheit** steht die gewaehlte Reihe — ganze USD, Tausend USD, Millionen
   USD?
3. **Zu welchem Basisjahr** (Abschnitt 4)?

**Was ich dafuer abgerufen habe** (Belegliste Abschnitt 7, Nr. 6 bis 18): die
Uebersichtsseite der Quelle, ihre Dokumentationsseite, ihre Veroeffentlichungsmitteilung
zu 11.0, die Dataverse-Landeseite des Datensatzes, die Dataverse-Metadatenschnittstelle,
das Benutzerhandbuch zu 11.0, die Mitteilung „What is new in PWT 11.0", das
Benutzerhandbuch zu 10.0 als Gegenprobe, dazu zwei geratene URLs und eine
Drittanbieterseite. Zwei Wege haben ein Ergebnis geliefert, und beide beantworten die
Frage nicht:

- **Die Uebersichtsseite der Quelle sagt zur Einheit genau einen Satz**
  (`https://www.rug.nl/ggdc/productivity/pwt/`, abgerufen 2026-09-02):

  > „Real GDP variables are in (millions) of US dollars, not in per-capita terms."

  Der Satz steht dort ueber die **Reihen des Online-Abfragewerkzeugs zum realen BIP**.
  Er nennt den Kapitalstock nicht, und er nennt kein Basisjahr. **Er traegt deshalb
  keinen Faktor.** Er steht hier, weil er die Groessenordnung anzeigt, in der die Quelle
  ueberhaupt rechnet — und damit, wie teuer die Nichtmessung ist: Stuende der
  Kapitalstock in Millionen USD, waere der Faktor nach Tausend USD **1.000** und nicht 1.
  Das ist genau der stumme Fehler um drei Groessenordnungen, den das Arbeitspaket
  beschreibt. Als Messung gilt das nicht; als Grund, hier keine 1 hinzuschreiben, schon.
- **Die Dataverse-Metadatenschnittstelle** (Abruf Nr. 17) zeigt, dass **keine** der
  zwoelf Dateien des Datensatzes als tabellarisch eingelesen gefuehrt wird. Damit gibt
  es auch keinen Weg ueber die Variablenmetadaten der Stata-Datei; die Variablenbezeich‑
  nungen liegen ausschliesslich in den Dateien selbst und im Handbuch.

**Woran es haengt — und das ist ein Punkt an den Betreiber, nicht an PWT.** Die
Dokumentation dieser Quelle liegt vollstaendig als PDF vor. **Vier PDF-Dateien aus drei
verschiedenen Verzeichnissen sind in diesem Lauf abgerufen worden, und alle vier kamen
unlesbar an** (Abschnitt 7, Nr. 5, 11, 13, 15) — der Abruf liefert den komprimierten
Datenstrom statt des Textes. Die Sperre ist nicht quellenseitig: Sie trifft ebenso das
Handbuch zu PWT 10.0 und die Freigabemitteilung von CEPII. **Fuer diese Rolle ist damit
jede Quelle unerreichbar, deren Dokumentation nur als PDF existiert.** Das ist die
zweite Sperre dieser Art in diesem Vorhaben neben dem IWF-Volltext (HTTP 403).

**Wo die Frage zu klaeren waere — zwei Dateien, beide benannt und beide erreichbar, nur
nicht lesbar:**

| Datei | Kennung | Abruf-URL | was darin steht |
|---|---|---|---|
| `pwt110_user_guide_to_data_files.pdf` | 554025 | `https://dataverse.nl/api/access/datafile/554025` | Variablenliste mit Bezeichnung, Einheit und Basisjahr |
| `pwt110.xlsx`, Blatt mit den Variablenbezeichnungen | 554105 | `https://dataverse.nl/api/access/datafile/554105` | dieselbe Liste maschinenlesbar |

Es kostet **einen** lesbaren Auszug aus einer dieser beiden Dateien, und die Messung ist
nachgetragen. Solange der nicht vorliegt, bleibt in `reihen.toml` bei Reihe 3
`art = "ungemessen"` richtig.

## 4. Basisjahr PWT 11.0 — nicht gemessen

**Kein Basisjahr.** Was vorliegt, ist ein eigener Abruf der Veroeffentlichungsmitteilung
der Quelle (`https://www.rug.nl/ggdc/blog/penn-world-table-version-11-0-is-published`,
abgerufen 2026-09-02, veroeffentlicht am 2025-10-07):

> „Since PWT version 10.0(1), the World Bank has released new data on purchasing power
> parities (PPPs) for the year 2021"

> „as part of the International Comparison Program (ICP), including revisions for the
> year 2017."

**Warum daraus kein Basisjahr wird, obwohl es danach aussieht.** Der Satz nennt das
Stuetzjahr der **Eingangsdaten** der Weltbank, nicht die Preisbasis der
veroeffentlichten Reihen — und er nennt in zwei aufeinanderfolgenden Halbsaetzen
**zwei** Jahre. Wer daraus „Basisjahr 2021" macht, hat geraten und nicht gemessen; wer
daraus „2017" macht, ebenfalls. Ein Suchtreffer, der 2021 behauptet, stuetzt sich auf
eine Drittanbieterseite (Abschnitt 7, Nr. 18), und die hat den Abruf mit HTTP 403
abgewiesen — ich kann ihren Wortlaut nicht lesen und zitiere ihn deshalb nicht.

**Warum das nicht folgenlos ist.** Reihe 1 fuehrt in `reihen.toml` PWT als
Rueckfallquelle, und die Quellenwahl ist dort ausdruecklich offen. Wechselt die Reihe
auf PWT und traegt PWT ein anderes Basisjahr als die 2015 der WDI-Reihe, aendert sich
die Sollreihe — und mit ihr der Massstab, gegen den T42 die drei Fehlermasse rechnet.
Der Zug ist vor dem Einfrieren des Jahrgangs zu machen, so wie es Reihe 3 in
`reihen.toml` schon notiert.

**Wo die Frage zu klaeren waere:** dieselben zwei Dateien wie in Abschnitt 3.

## 5. Die Folge fuer T5 Klasse 2 — als Frage, nicht als Entscheidung

**Adressat: der Architekt, `technik.md`.** Ich waehle nichts aus.

**Der gemessene Widerspruch, in zwei Zeilen:**

- T5 Klasse 2 verlangt fuer volkswirtschaftliche Betraege — und der **Handelsstrom**
  steht dort namentlich — „Tausend USD **zu konstanten Preisen des Basisjahrs**".
- BACI meldet „in **thousands current** USD" (Abschnitt 1 und 2, gemessen).

Die Modellseite ist damit real, die Sollseite nominal. Reihe 14 traegt 40
Handelsstroeme, T42 rechnet ueber jeden einzelnen den MAPE gegen die Schwelle 2.000
(= 20 %), und T37 fuehrt den Handelsblock unter den sechzehn Pruefgegenstaenden. **In
der jetzigen Fassung misst der Rueckvergleich fuer den Handelsblock die
Preisentwicklung mit**, und ueber ein Fenster von 1997 bis 2021 ist die groesser als
die Schwelle, gegen die geprueft wird.

**Die Moeglichkeiten, die `specs/` offenlaesst — vier, aufgezaehlt und keine gewaehlt:**

1. **Deflationieren.** Ein Deflatorschritt kommt in die Umrechnung von Reihe 14, und der
   Handelsstrom steht danach in konstanten Preisen des Basisjahrs. Offen daran: welcher
   Deflator, aus welcher der vier geprueften Quellen, zu welchem Basisjahr — **keine der
   vier ist auf einen dafuer tauglichen Deflator gemessen**, und ein Deflator aus einer
   fuenften Quelle waere eine neue Quelle und damit ein Fall fuer den Datenkurator.
2. **Die Klasse aendern.** Reihe 14 verlaesst Klasse 2 oder Klasse 2 bekommt fuer
   nominale Handelsstroeme eine ausgewiesene Ausnahme. Offen daran: T5 sagt von sich,
   die Bedeutung stehe „in dieser Tabelle und nirgends sonst" — eine Ausnahme muss also
   in die Tabelle und nicht in eine Fussnote. Und die Modellgroesse `Handelsstrom` muesste
   dann nominal gefuehrt werden, was der Korbwert und die Bewertung mittragen.
3. **Die Vergleichbarkeit aufgeben und sie benennen.** Sollreihe bleibt nominal, das
   Modell bleibt real, und der Befund des Rueckvergleichs weist fuer den Handelsblock
   aus, dass sein Fehlermass einen Preisanteil enthaelt. Offen daran: T37 zaehlt den
   Handelsblock unter den sechzehn Pruefgegenstaenden mit Toleranz 2 — eine Kennzahl,
   die etwas anderes misst als die uebrigen fuenfzehn, gehoert entweder aus der Zaehlung
   heraus oder mit einer eigenen Schwelle hinein.
4. **Die Quelle wechseln.** `reihen.toml` fuehrt als Rueckfall den IWF DOTS. Offen
   daran: T26 laesst ihn nur fuer Spieljahrgaenge vor 1997 zu, und die Preisbasis von
   DOTS ist **ebenfalls ungemessen** — der IWF-Volltext ist an fuenf Anlaeufen aus drei
   Rollen mit HTTP 403 gescheitert. Dieser Weg tauscht also eine gemessene Schwierigkeit
   gegen eine ungemessene.

## 6. Reihe 16 (`durchgriff`) — mitbeantwortet

Die Frage aus `reihen.toml` — Reihe 16, Feld `offen`, erster Eintrag, beginnend mit
`H und N stehen in der Groessenordnung in derselben Einheit` — lautet, ob `H` (aus BACI)
und `N` (aus WDI) in derselben Einheit stehen. **Antwort: in der Groessenordnung ja, in der Preisbasis
nein.**

**Die BACI-Seite (`H`):** „in thousands current USD", Faktor nach Tsd USD = 1
(Abschnitt 1).

**Die WDI-Seite (`N`):** `N` ist keine eigene Reihe. T23 Punkt 1 bildet die
Sektorwertschoepfung aus Reihe 1 (BIP) und den auf 10.000 normierten Sektoranteilen der
Reihe 2; die Einheit von `N` ist damit die von Reihe 1. Diese habe ich heute an beiden
Endpunkten der Weltbank nachgemessen, nicht aus `reihen.toml` uebernommen:

| Endpunkt | Feld | Wortlaut |
|---|---|---|
| `https://api.worldbank.org/v2/sources/2/series/NY.GDP.MKTP.KD/metadata?format=json` | `Unitofmeasure` | „constant 2015 US$" |
| `https://api.worldbank.org/v2/sources/2/series/NY.GDP.MKTP.KD/metadata?format=json` | `IndicatorName` | „GDP (constant 2015 US$)" |
| `https://api.worldbank.org/v2/indicator/NY.GDP.MKTP.KD?format=json` | `name` | „GDP (constant 2015 US$)" |

Abrufdatum beider Endpunkte: 2026-09-02. Beide nennen dieselbe Zeichenfolge; das ist die
Gegenprobe gegen das Werkzeug. `reihen.toml` teilt Reihe 1 durch 1.000 (Quelle in USD,
Modell in Tsd USD), also steht `N` in **Tausend USD zu konstanten Preisen von 2015**.

**Der Vergleich, Groesse fuer Groesse:**

| | `H` (BACI) | `N` (WDI ueber T23 P1) | gleich? |
|---|---|---|---|
| Waehrung | USD | USD | ja |
| Groessenordnung | Tausend | Tausend | **ja — Faktor 1 zwischen beiden** |
| Preisbasis | laufend | konstant, 2015 | **nein** |

**Was das fuer den Quotienten heisst.** `durchgriff = teile_gerundet(10.000 · H, H + N)`
ist ein Anteil, in dem sich die Waehrungseinheit herauskuerzt — der Faktor 1 der
Groessenordnung genuegt dafuer, und insoweit ist der Quotient nicht bedeutungslos. Die
Preisbasis kuerzt sich **nicht** heraus: `H` wird in den Preisen des jeweiligen Jahres
gemessen, `N` in denen von 2015. *Unter der Annahme steigender Preise* — Annahme, nicht
Messung — faellt `durchgriff` fuer Jahre nach 2015 systematisch zu hoch aus und fuer
Jahre davor zu niedrig. Der Pruefjahrgang laeuft von 1997 bis 2021; der groesste Teil
seiner Stuetzstellen liegt weit von 2015 weg. Es ist also keine Rundungsfrage.

Ob das hinnehmbar ist, entscheidet der Architekt — es ist dieselbe Entscheidung wie in
Abschnitt 5, und sie faellt fuer beide Reihen zugleich. **Sie faellt nicht hier.**

## 7. Was abgerufen wurde — alle zwanzig URLs, auch die erfolglosen

Alle Abrufe am 2026-09-02. Die Liste ist vollstaendig, damit die beiden Nichtmessungen
nachpruefbar sind und der naechste Lauf keinen Weg zweimal geht.

**BACI (CEPII):**

1. `https://www.cepii.fr/DATA_DOWNLOAD/baci/doc/DescriptionBACI.html` — **die tragende
   Quelle.** Spaltenliste mit `v`, `q`, `t`, `i`, `j`, `k` im Wortlaut.
2. `https://www.cepii.fr/DATA_DOWNLOAD/baci/doc/FAQ_BACI.html` — der Endpunkt aus
   `daten.md` Nr. 3. Nennt weder Variablennamen noch Einheit noch Preisbasis.
3. `https://www.cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37` — Landeseite,
   nennt keine Einheit; liefert die Verweise auf Nr. 1, 4 und 5.
4. `https://www.cepii.fr/DATA_DOWNLOAD/baci/doc/baci_webpage.html` — **ohne Ergebnis**,
   der Abruf kam gekuerzt an.
5. `https://www.cepii.fr/DATA_DOWNLOAD/baci/doc/release_notes_202601.pdf` — **ohne
   Ergebnis**, PDF unlesbar. Dies ist der Abruf, der den Vorbehalt in Abschnitt 1 offen
   laesst.

**PWT (GGDC / Universitaet Groningen) und Dataverse:**

6. `https://www.rug.nl/ggdc/productivity/pwt/` — der Endpunkt aus `daten.md` Nr. 4.
   Liefert den Satz zu „Real GDP variables" und die vorgeschriebene Zitierung, keine
   Kapitalstockeinheit, kein Basisjahr.
7. `https://www.rug.nl/ggdc/blog/penn-world-table-version-11-0-is-published` — die zwei
   Saetze aus Abschnitt 4.
8. `https://www.rug.nl/ggdc/productivity/pwt/pwt-documentation` — fuehrt Handbuecher bis
   PWT 10.0 und keines zu 11.0.
9. `https://www.rug.nl/ggdc/productivity/pwt/pwt-releases/pwt11.0` — **ohne Ergebnis**,
   HTTP 404 (geratene URL).
10. `https://www.rug.nl/ggdc/docs/pwt110-user-guide-to-data-files.pdf` — **ohne
    Ergebnis**, HTTP 404 (geratene URL nach dem Muster der 10.0-Ablage).
11. `https://www.rug.nl/ggdc/docs/pwt100-user-guide-to-data-files.pdf` — **ohne
    Ergebnis**, PDF unlesbar. Abgerufen als Gegenprobe: Sie zeigt, dass die Sperre am
    Dateiformat haengt und nicht an der Fassung 11.0.
12. `https://dataverse.nl/api/access/datafile/554025` — Benutzerhandbuch zu PWT 11.0,
    Weiterleitung auf den Ablagehost.
13. Der Ablagehost zu Nr. 12 (`objectstore.surf.nl/store/10.34894/FABVLR/…`) — **ohne
    Ergebnis**, PDF unlesbar.
14. `https://dataverse.nl/api/access/datafile/554031` — „What is new in PWT 11.0",
    Weiterleitung auf den Ablagehost.
15. Der Ablagehost zu Nr. 14 — **ohne Ergebnis**, PDF unlesbar.
16. `https://dataverse.nl/dataset.xhtml?persistentId=doi:10.34894/FABVLR` — Landeseite
    des Datensatzes: Titel, Fassung 2, Veroeffentlichung 2025-10-07, Dateiliste. Keine
    Einheit, kein Basisjahr.
17. `https://dataverse.nl/api/datasets/:persistentId/?persistentId=doi:10.34894/FABVLR`
    — Metadatenschnittstelle: die zwoelf Dateikennungen (darunter `pwt110.dta` = 554030
    und `pwt110.xlsx` = 554105) und der Befund, dass **keine** Datei tabellarisch
    eingelesen ist, es also keine Variablenmetadaten gibt.
18. `https://fred.stlouisfed.org/series/CKSPPPDEA666NRUG` — **ohne Ergebnis**, HTTP 403.
    Ein Drittanbieter, kein Quellenbeleg; abgerufen nur, um die aus Suchtreffern
    bekannte Jahresangabe im Wortlaut lesen zu koennen. Die Sperre bestaetigt den
    Eintrag aus `daten.md` Nr. 11 vom 2026-08-31.

**WDI (Weltbank), fuer Abschnitt 6:**

19. `https://api.worldbank.org/v2/sources/2/series/NY.GDP.MKTP.KD/metadata?format=json`
    — `Unitofmeasure` = „constant 2015 US$", `IndicatorName` = „GDP (constant 2015 US$)",
    `Periodicity` = „Annual", `Referenceperiod` = „1960-2025".
20. `https://api.worldbank.org/v2/indicator/NY.GDP.MKTP.KD?format=json` — `name` =
    „GDP (constant 2015 US$)". Gegenprobe zu Nr. 19, zeichengleich.

**Drei Websuchen** nach der BACI-Wertvariablen, nach den PWT-Kapitalstockvariablen und
nach der Zeichenfolge „Capital stock at current PPPs (in mil. 2021US$)". Keine hat einen
Quellenwortlaut geliefert, den ich selbst abrufen konnte; sie haben die URLs Nr. 1, 12
und 18 gefunden. Als Beleg zaehlt keine.

## 8. Was dieser Befund ausdruecklich nicht sagt

- **Er entscheidet nichts.** Weder ob Klasse 2 laufende Preise vertraegt, noch ob Reihe
  14 die Klasse wechselt, noch ob ein Deflator dazukommt, noch welche PWT-Reihe Reihe 3
  traegt. Alle vier gehoeren dem Architekten.
- **Er sagt nichts ueber Lizenzen.** PWT und BACI stehen in `daten.md` Nr. 3 und Nr. 4
  und in `lizenzbefund-reihen.md` als `frei`; dieses Paket misst Einheiten. Die
  Zitierpflichten aus beiden Lizenzen sind davon unberuehrt.
- **Er behauptet nicht, PWT sei ungenau dokumentiert.** Die Dokumentation existiert und
  ist benannt (Abschnitt 3, Tabelle). Sie ist mit den Werkzeugen **dieser Rolle** nicht
  lesbar. Das ist ein Befund gegen die Werkzeugkette, nicht gegen die Quelle.
- **Er fasst `daten/reihen.toml` nicht an.** Der Uebertrag der gemessenen Groessen ist
  ein eigenes Paket. Was dabei zu uebertragen waere, steht hier zusammen:
  Reihe 14 Schritt 1 `art = "mal"`, `faktor = 1`, `status = "gemessen"` — **zusammen mit
  dem Satz zur laufenden Preisbasis und dem Versionsvorbehalt aus Abschnitt 1**, denn
  ein blosser `faktor = 1` an dieser Stelle behauptet Vollstaendigkeit, die nicht
  gemessen ist. Reihe 3 bleibt `art = "ungemessen"`. Reihe 16 bekommt in `offen` die
  Antwort aus Abschnitt 6 an die Stelle der Frage.
