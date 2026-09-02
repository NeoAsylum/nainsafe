---
typ: pruefung
paket: 0014-lizenzpruefung-restliche-reihen
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle sechs Reihen-Codes am 2026-09-02 selbst nachgerufen und die zitierten `Source`-Felder Zeichen fuer Zeichen verglichen, dazu Etalab-, ILO- und Kontrollzitat; die Sollreihen- und Pruefgegenstandszahlen gegen die Reihenliste und T37 einzeln nachgerechnet
befunde: 4
---

# Sechs Zitate, sechsmal zeichengleich — und ein Preis in der Schlussliste, der den eigenen Massstab nicht mehr anlegt

## Was geprueft wurde und wie

**Die Zitate, gegen den jeweils anderen Endpunkt.** Der Befund nennt fuer jeden Code beide
Endpunkte und behauptet Zeichengleichheit. Ich habe deshalb den Indikator-Endpunkt
(`sourceOrganization`) genommen, alle Abrufe am **2026-09-02**, und jedes Feld im Volltext
angefordert:

| Abruf | Ergebnis gegen den Befund |
|---|---|
| `https://api.worldbank.org/v2/indicator/NY.GDP.MKTP.KD?format=json` | zeichengleich, `name: "GDP (constant 2015 US$)"` |
| `…/v2/indicator/NV.AGR.TOTL.ZS?format=json` | zeichengleich, OECD-Zeile vorhanden |
| `…/v2/indicator/NV.IND.TOTL.ZS?format=json` | zeichengleich, **keine OECD**, `National Statistical Offices (NSOs)` / `Central Banks` |
| `…/v2/indicator/NV.SRV.TOTL.ZS?format=json` | zeichengleich, wortgleich mit `NV.IND.TOTL.ZS` |
| `…/v2/indicator/SP.POP.TOTL?format=json` | zeichengleich, einschliesslich der vier `uri:`/`publisher:`-Paare und des abwegigen Eurostat-Links `…node_code=earn_ses_monthly` |
| `…/v2/indicator/SL.TLF.TOTL.IN?format=json` | zeichengleich, `type: estimates based on external database` ohne `uri` und ohne `date accessed` |
| `…/v2/indicator/IQ.CPA.ECON.XQ?format=json` (Kontrolle) | zeichengleich, ein einziger Lieferant, und es ist die Weltbank |

**Damit ist der Kernsatz des Pakets unabhaengig belegt:** Alle sechs Codes, die die
Reihenliste mit „Verdacht: nein" fuehrt, nennen einen Bestand ausserhalb der Weltbank, und
der Unterschied zwischen `NV.AGR.TOTL.ZS` und den beiden anderen Anteilsreihen ist echt und
nicht eine Umformulierung des Abrufwerkzeugs. Das war die Stelle, an der dieser Befund haette
kippen koennen — er kippt nicht.

**Die drei uebrigen Wortlaute, je ein eigener Abruf am 2026-09-02:**

- **Etalab** (`https://raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md`): Der
  Abschnitt *Droits de propriete intellectuelle* traegt den zitierten Garantiesatz wortgleich,
  und `La presente licence est regie par le droit francais.` steht dort ebenfalls. Der Befund
  kuerzt den zweiten Absatz nach dem ersten Satz; die Kuerzung nimmt nichts weg, was die
  Aussage drehen wuerde (der Rest ist die Rechteeinraeumung des Konzedenten).
- **ILO** (`https://www.ilo.org/rights-and-permissions`): Beide zitierten Saetze stehen dort
  wortgleich. Die Gegenprobe, auf die Abschnitt 4 hinauslaeuft, habe ich selbst gestellt — die
  Seite definiert `produced` **nirgends** und sagt nichts darueber, ob eine fortlaufend
  aktualisierte Datenbank mit jeder Ausgabe neu erzeugt wird. Der Schluss „aus dem Wortlaut
  nicht zu beantworten" traegt, und die Zuruecknahme der Gleichsetzung aus 0005
  (`date accessed` = Erzeugungsdatum) ist richtig.
- **Weltbank-Vorbehalt** (`daten.md` Nr. 1, Zeile 62–64): der in Abschnitt 3 als Massstab
  zitierte Satz steht dort wortgleich.

**Die Zahlen, einzeln nachgerechnet — nicht die Summen.**

- Reihenliste `technik.md` Zeile 1013: die 31 Sollreihen sind die Zeilen 1, 2, 8, 9, 10, 11
  mit 4+12+4+4+3+4. Damit stimmen `frei: 7` (8 → 4, 10 → 3), `unklar: 24` (1 → 4, 2 → 12,
  9 → 4, 11 → 4) und `gesperrt: 0` je Summand, nicht nur in der Summe. Die Reihen 3, 4, 5, 6,
  7, 12, 13, 14, 15 tragen ausweislich der Spalte „Rolle" keine Sollreihe — der Befund gibt
  ihnen ueberall 0, auch bei Reihe 13, die aus 0005 gesperrt ist. Kein ausgelassener Fall.
- T37 (`technik.md` Zeile 1677–1684): 4 + 4 + 4 + 3 + 1 = 16, und die Zuordnung der fuenf
  Gegenstaende zu den Reihen 1, 2, 8, 10, 14 stimmt mit der dortigen Spalte „zusammengefasst
  aus" ueberein. Die Aussage, Reihe 9 und 11 kosteten keinen Gegenstand, ist durch die
  T37-Klassen `gesetzt` und `abgeleitet` gedeckt.
- Die Verfallsrechnung: 16 − 4 − 4 = 8, 8 − 4 − 3 = 1. Beide Zeilen stimmen.
- Klaerung 2 („15 Sollreihen, 7 Pruefgegenstaende"): 8 aus 9 und 11, 7 aus 8 und 10 = 15; die
  Gegenstaende 4 (Reihe 8) + 3 (Reihe 10) = 7. Stimmt.
- Der Beleg fuer den kleinen Agraranteil: `pruefung-entwurf-fassung2-2026-08-31.md` Zeile 148
  fuehrt 1,0322 % fuer die USA. Der Befund nennt ihn korrekt als „ein Modelland" und
  ueberdehnt ihn nicht.
- Eurostat: `spiel.md` Zeile 8 nennt USA, China, Deutschland, Brasilien. „Drei der vier
  Modelllaender" ist richtig — auch Brasilien liegt ausserhalb EU/EFTA, obwohl `daten.md`
  Nr. 7 es nicht als Beispiel nennt.

**Wonach ich ausserdem gesucht und nichts gefunden habe:** einen zweiten Einheitenschnitt
(dieses Paket rechnet nicht und bettet nichts ein, es gibt keine Skala und kein Basisjahr zu
pruefen — der einzige Ansatz waere der PWT-Basisjahrwechsel unter Reihe 1, und den benennt
der Befund selbst als offen); eine stillschweigend interpolierte Zahl (es gibt keine Zahl aus
Daten, nur Zaehlungen); eine Quelle, die nicht in `daten.md` steht (PWT Nr. 4, BACI/Etalab
Nr. 3, IWF Nr. 2, ILO ueber die WDI-Ausnahme, Eurostat Nr. 7, OECD Nr. 8, Destatis Nr. 5 —
alle sieben stehen dort). Das Paket hat nichts heruntergeladen; `daten/` enthaelt ausser der
Textdatei nichts Neues.

## Das Abnahmekriterium, Stueck fuer Stueck

| Verlangt | Befund |
|---|---|
| je Code `Source` woertlich | fuer alle sechs Reihen-Codes vorhanden **und von mir nachgemessen** |
| je Code Abruf-URL | vorhanden; bei `NV.SRV.TOTL.ZS` als `…/NV.SRV.TOTL.ZS/metadata?format=json` abgekuerzt, eindeutig |
| je Code Abrufdatum | 2026-09-02, durchgehend |
| je Code Urteil mit Begruendung | sechsmal `unklar`, je mit Begruendung |
| Folge nach T26 bei jedem Urteil ausser `frei` | bei Reihe 1, 5, 6 als eigene Zeile; **bei den drei Reihe-2-Codes nicht daneben**, sondern erst in Befund 4 — siehe Befund 4 unten |
| Sollreihenzahl bei jedem Urteil ausser `frei` | vollstaendig, je Code und in der Zusammenfassung |
| je Nicht-WDI-Reihe: Drittanbietervorbehalt ja/nein, woertlich, mit Fundstelle | PWT (3, 4, 15) als belegte Abwesenheit, BACI (14) mit Gegenteil-Zitat, IWF (9, 11, 12) mit dem Satz **und** der ausdruecklichen Feststellung, dass er nur aus einem Suchauszug stammt |

Der IWF-Teil ist die Stelle, an der man den Befund abweisen koennte, und er ist genau richtig
gebaut: Das Paket erlaubte hoechstens einen Abruf je Quelle, der Abruf scheiterte mit 403, und
statt den Suchauszug als Beleg zu verkaufen, schreibt der Befund hin, dass er nach den Regeln
dieser Fabrik keiner ist, und rechnet die Zusammenfassung ein zweites Mal ohne ihn
(`frei: 0, unklar: 31`). Ein Befund, der seine eigene Hauptzahl mit der Gegenrechnung
daneben ausliefert, erfuellt das Kriterium besser als einer, der sich entschieden haette.

**Urteil: geprueft.** Die vier Befunde unten aendern das nicht — drei liegen ausserhalb des
Kriteriums, der vierte ist eine Platzierung.

---

# Befund 1 — an den Projektmanager: Klaerung 1 kann Reihe 1 und 2a nicht heben, und ihr Preis ist deshalb falsch

**Das ist der Fund dieses Laufs.** Der Befund entwickelt einen Massstab, wendet ihn auf 2b
und 2c an — und legt ihn zwei Abschnitte spaeter bei Reihe 1 und 2a nicht mehr an.

Der Massstab steht unter 2b/2c (Zeile 146–154): Genannt sind „keine Organisationen mit eigenen
veroeffentlichten Bedingungen, sondern die amtliche Statistik der Meldelaender", `daten.md`
hat von den vier Modelllaendern genau ein Amt geprueft (Destatis), **also unklar**. Das ist
ein eigenstaendiger Sperrgrund, unabhaengig von der OECD.

Und derselbe Sperrgrund steht in Reihe 1 und 2a, nachgemessen am 2026-09-02:

> **Country official statistics, National Statistical Organizations and/or Central Banks;**
> National Accounts data files, Organisation for Economic Co-operation and Development (OECD);
> Staff estimates, World Bank (WB)

Die erste Zeile nennt dieselben Stellen wie 2b/2c — nationale Aemter und Notenbanken —, nur
als eine Angabe statt als zwei. Der Befund **sieht** das: Seine Uebersichtstabelle Zeile 56
und 57 fuehrt fuer Reihe 1 und 2a ausdruecklich „OECD, nationale Aemter/Notenbanken". Dann
verschwindet die zweite Haelfte:

- Die Begruendung unter Reihe 1 (Zeile 89–94) nennt ausschliesslich die OECD.
- Klaerung 1 (Zeile 453–456) verspricht: *„OECD im Volltext … hebt Reihe 1 und 2a, also
  8 Sollreihen und 4 Pruefgegenstaende — die vier BIP-Gegenstaende."*
- Klaerung 4 (Zeile 462–465) preist die nationalen Aemter ausdruecklich als *„hebt 2b und 2c,
  allein aber nutzlos"* — dass sie **auch fuer Reihe 1 und 2a** noetig sind, steht nirgends.

**Wie man den Fehler erzeugt:** Man liest die Liste „Was zu tun bleibt" so, wie sie
ausgeschrieben ist — nach Kosten geordnet, Klaerung 1 zuerst — und kauft den billigsten
Schritt. Nach dem Befund bringt er vier der sechzehn Pruefgegenstaende zurueck. Nach dem
Massstab desselben Befundes bringt er **null**: Reihe 1 bleibt an derselben ungeprueften
Lieferantengruppe haengen wie 2b und 2c, und die vier BIP-Gegenstaende haengen damit an
Klaerung 1 **und** Klaerung 4 zugleich — genau die Doppelbedingung, die der Befund fuer die
vier Sektorstruktur-Gegenstaende korrekt aufschreibt und fuer die vier BIP-Gegenstaende nicht.

**Was das an Zahlen aendert:** an den Urteilen nichts — `unklar` bleibt `unklar`, und zwar aus
mehr Gruenden als angegeben. Es aendert die Klaerungsliste: Keiner der vier Schritte hebt
allein einen Pruefgegenstand; Klaerung 1 und 4 heben zusammen acht, und Klaerung 4 wird von
der billigen Restarbeit zur Voraussetzung der Haelfte des Rueckvergleichs.

**Und Klaerung 4 ist selbst zu eng geschnitten.** Sie nennt nur „die Statistikaemter der drei
Nicht-EU-Modelllaender". Das Feld `Source` von 2b/2c nennt die Notenbanken als **eigenen**
Lieferanten („National Accounts data files, Central Banks") — vier weitere Stellen, darunter
die Bundesbank, die Destatis Nr. 5 nicht mit abdeckt.

# Befund 2 — an den Architekten: das Wort „frei" in der Spalte „Rolle" ist keine Lizenzaussage

Befund 2 des Pakets sagt: *„Die Zeile ,Start + Soll (12, frei, 8 unabhaengig)' fasst damit
zwei verschiedene Lizenzlagen zusammen."* Das trifft die falsche Zelle. In der Reihenliste ist
`frei` an dieser Stelle die **T37-Klasse**, nicht ein Lizenzurteil: T37 (`technik.md`
Zeile 1667–1671) kennt genau die drei Klassen `frei`, `gesetzt`, `abgeleitet`, und die Spalte
„Rolle" vergibt sie zeilenweise — Reihe 9 `gesetzt`, Reihe 11 `abgeleitet`, Reihen 1, 2, 8, 10
`frei`, mit den „8 unabhaengig" aus T37s „19 unabhaengig". Die Lizenzfrage traegt die Spalte
**„Verdacht"**, und die trifft Befund 1 des Pakets bereits richtig.

Der Befund weiss das an anderer Stelle selbst: Zeile 432 liest `gesetzt` und `abgeleitet`
korrekt als T37-Klassen. Nur in Befund 2 wird dasselbe Vokabular zur Lizenzlage.

**Wie man den Fehler erzeugt:** Der Architekt liest Befund 2 und streicht oder differenziert
das `frei` in der Rolle-Spalte von Zeile 2 — und zerschiesst damit die Verbindung zwischen
Reihenliste und T37, waehrend die Spalte, die wirklich falsch ist, unberuehrt bleibt. Die
Sache selbst (Reihe 2 zerfaellt lizenzseitig in zwei Gruppen) ist richtig und belegt; nur der
Adressat in der Tabelle ist es nicht.

# Befund 3 — an den Projektmanager: das Frontmatter mischt zwei Zaehlbereiche ohne Hinweis

`reihen_frei: 4 (3, 4, 14, 15)` — diese vier Reihen tragen zusammen **null** Sollreihen.
Direkt darunter steht `sollreihen_frei: 7`, und diese sieben stammen aus den Reihen 8 und 10,
die in `reihen_frei` nicht vorkommen. `reihen_gesperrt: 0` steht neben `sollreihen_gesperrt: 0`
und ist nur fuer dieses Paket wahr — Reihe 13 ist aus 0005 gesperrt.

Die `reihen_*`-Felder zaehlen also den Paketumfang, die `sollreihen_*`-Felder alle 31 Reihen
beider Pakete. Der Fliesstext sagt das sauber („unter Fortschreibung der Urteile aus Paket
0005", Zeile 407), das Frontmatter nicht.

**Wie man den Fehler erzeugt:** Man liest das Frontmatter als Kopfzeile — wozu es da ist — und
rechnet `reihen_frei` gegen `sollreihen_frei` nach. Es kommt 0 heraus, nicht 7. Wer daraufhin
dem Fliesstext misstraut, misstraut der richtigen Zahl. Ein Zusatz `_paket` beziehungsweise
`_gesamt` an den Feldnamen schliesst es.

Dazu, kleiner: `codes_abgerufen: 8` zaehlt `SL.EMP.TOTL.SP.ZS` und `IQ.CPA.ECON.XQ` mit. Beide
sind Gegenproben, tragen kein Urteil und keine volle Abruf-URL, und beide sollen das auch
nicht. Sie unter derselben Zahl zu fuehren wie die sechs Reihen-Codes laedt dazu ein, das
Abnahmekriterium gegen acht statt gegen sechs zu pruefen.

# Befund 4 — an den Projektmanager: die T26-Folge zu Reihe 2 steht nicht neben dem Urteil

Das Abnahmekriterium verlangt sie „daneben". Bei Reihe 1, 5 und 6 steht sie als eigene Zeile,
bei den drei Reihe-2-Codes nicht; die Antwort steht erst zwoelf Seiten spaeter in Befund 4 des
Pakets („fuer die Reihen 1, 2, 5, 6 gibt es keinen Eintrag … fuer Reihe 2 gibt es keine
[Ausweichquelle]"). **Ich habe das Kriterium deshalb nicht als verletzt gewertet** — die
Auskunft ist da, sie ist vollstaendiger als die Zeilen bei Reihe 5 und 6, und der Abschnitt
„Was Reihe 2 als Ganzes kostet" beantwortet die Frage nach dem Ersatz ausfuehrlicher als jede
Standardzeile es koennte.

Es bleibt trotzdem die Reihe mit den meisten Sollreihen, und ihre Folgezeile ist die einzige,
die man suchen muss. Wenn der Projektmanager die Form nachzieht, ist es eine verschobene
Ueberschrift, kein Ruecklauf.

---

## Was diese Pruefung nicht geprueft hat

- **Die Deckung.** Ob eine Reihe 25 Stuetzstellen traegt, ist Paket 0006. Der Hinweis des
  Befundes, `SL.TLF.TOTL.IN` beginne erst 1990, habe ich nicht nachgerufen.
- **Das PWT-Basisjahr.** Der Befund benennt selbst, dass ein Wechsel auf PWT bei Reihe 1 das
  Basisjahr und damit den Massstab von T42 verschiebt, und misst es nicht. Das ist richtig so
  — es gehoert nicht in ein Lizenzpaket. Fuer meine Rolle bleibt es die offene Stelle: Ein
  Ersatzweg, den niemand auf seine Preisbasis geprueft hat, ist ein Einheitenfehler auf Abruf.
- **Ob der IWF-Satz so dasteht.** Ich habe den fuenften Fehlversuch nicht zum sechsten gemacht.
- **Die Reihenliste selbst.** Sie gehoert dem Architekten; ihre Spalte „Verdacht" ist nach
  diesem Paket an sechs von sechs Stellen widerlegt, und das ist Befund 1 des Pakets, nicht
  meiner.
