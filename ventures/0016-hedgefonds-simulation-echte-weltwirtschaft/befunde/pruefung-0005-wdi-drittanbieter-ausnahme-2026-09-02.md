---
typ: pruefung
paket: 0005-wdi-drittanbieter-ausnahme
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle fünf Pflichtangaben je Reihe sind vorhanden, und das Feld „Source" aller vier Reihen (sieben Indikatorcodes) wurde am 2026-09-02 unabhängig über beide Weltbank-Endpunkte neu abgerufen und zeichenweise gegen den Wortlaut im Befund gehalten.
befunde: 2
---

# Prüfung 0005 — die vier Wortlaute halten, die Verdachtsspalte hält nicht

Das Abnahmekriterium ist erfüllt. Die beiden Befunde betreffen **nicht** die vier
geprüften Reihen, sondern zwei Stellen, an denen der Befund eine Aussage über eine
*fünfte* Reihe trifft oder stützt, ohne sie mit derselben Methode zu messen. Beide gehen
an den Projektmanager, keiner an den Bauagenten.

## 1. Das Abnahmekriterium, Angabe für Angabe

Fünf Pflichtangaben je Reihe, dazu die T26-Folge bei jedem Urteil ausser `frei`:

| Reihe | Code | „Source" wörtlich | Abruf-URL | Abrufdatum | Urteil + Begründung | T26-Folge |
|---|---|---|---|---|---|---|
| 13 | ✓ | ✓ | ✓ (zwei) | 2026-09-01 | `gesperrt`, begründet | ✓ erster Fall |
| 7 | ✓ (drei Codes) | ✓ | ✓ (zwei) | 2026-09-01 | `unklar`, begründet | ✓ zweiter Fall |
| 8 | ✓ | ✓ | ✓ (zwei) | 2026-09-01 | `frei`, begründet | entfällt |
| 10 | ✓ | ✓ | ✓ (zwei) | 2026-09-01 | `frei`, begründet | entfällt |

Der Auftrag lässt offen, ob `unklar` eine T26-Folge braucht; der Befund schreibt sie für
Reihe 7 trotzdem hin, mit der Bedingung „falls es bei `unklar` bleibt oder gesperrt
wird". Die Angabe fehlt also nicht.

Dass die Indikatorcodes nicht in `daten.md` standen und deshalb selbst gesucht werden
mussten, ist zutreffend: `grep -n "TM.TAX\|SL.AGR\|SL.IND\|SL.SRV\|FP.CPI\|PA.NUS"` über
`daten.md`, `technik.md` und `spiel.md` liefert **keinen** Treffer in `daten.md` und in
`technik.md` nur die Reihe-2-Codes (Zeile 993). Der Auftrag hat diesen Fall vorgesehen.

## 2. Der Nachweis: sieben Wortlaute unabhängig neu abgerufen

Kein zitierter Wortlaut wurde übernommen. Jeder wurde am **2026-09-02** neu geholt und
gegen den Befund gehalten — teils über den anderen der beiden Endpunkte, damit nicht
derselbe Weg zweimal dasselbe bestätigt.

| Indikatorcode | Endpunkt meines Abrufs | Ergebnis |
|---|---|---|
| `TM.TAX.MRCH.WM.AR.ZS` | `/v2/sources/2/series/…/metadata` | **zeichengleich**, alle fünf Bestände (Staff estimates; WITS/WB; TRAINS/UNCTAD; IDB/WTO; CTS/WTO) |
| `FP.CPI.TOTL.ZG` | `/v2/sources/2/series/…/metadata` | **zeichengleich** („International Financial Statistics database, International Monetary Fund (IMF)") |
| `PA.NUS.FCRF` | `/v2/sources/2/series/…/metadata` | **zeichengleich**, dieselbe IWF-Zeile |
| `SL.AGR.EMPL.ZS` | `/v2/indicator/…` (`sourceOrganization`) | **zeichengleich**, einschliesslich `uri:`, `publisher: ILOSTAT`, `type: external database`, `date accessed: January 17, 2026` |
| `SL.IND.EMPL.ZS` | `/v2/sources/2/series/…/metadata` | **zeichengleich** |
| `SL.SRV.EMPL.ZS` | `/v2/indicator/…` (`sourceOrganization`) | **zeichengleich** |

Damit ist auch die Behauptung „bei allen drei Codes zeichengleich dasselbe" belegt: Ich
habe alle drei einzeln geholt, zwei davon über den anderen Endpunkt.

Mitgeprüfte Nebenangaben, alle bestätigt: `Referenceperiod` `1988-2022` (Reihe 13),
`1960-2025` (Reihen 8 und 10), `Periodicity: Annual` durchgehend, `License_Type:
CC BY-4.0` und `License_URL` in allen Fällen.

Die drei Belegstellen ausserhalb der Weltbank ebenfalls im Wortlaut nachgelesen statt
gegriffen:

- **ILO**, `www.ilo.org/rights-and-permissions`, abgerufen 2026-09-02: alle drei zitierten
  Sätze (CC BY 4.0 ab 3 May 2023, Mikrodaten-Ausnahme, Vorbehalt für vor dem 3 May 2023
  Erzeugtes) stehen dort **wörtlich so**.
- **`daten.md` Nr. 1**: die Ausnahmeklausel („may not be redistributed or reused without
  the consent of the original data provider") steht in Zeile 62–64 wörtlich.
- **`daten.md` Nr. 2, 9, 12, 13**: IWF-Erlaubnis samt „and sell" (Zeile 79–81) und samt
  der beiden Auflagen (Zeile 86–89); UNCTAD „widerspruechlich, nicht einplanen" (245);
  WTO „written permission from the WTO" (300–303); WITS „reicht die Auflagen seiner
  Lieferanten durch", negativ (310–321). Alle vier tragen die Begründungen, für die sie
  zitiert werden.
- **`technik.md` T26** (Zeile 969–977): Die beiden Folgen sind wörtlich übernommen, nicht
  umformuliert und nicht erfunden.

## 3. Die Zahlen der Reihenliste nachgerechnet

Gegen `technik.md` Abschnitt 7 (Zeilen 990–1017), geschnitten und einzeln nachgezählt:

- Reihe 13 trägt die Rolle „Start + Politikpfad" — **keine** Sollreihe. Die Aussage des
  Befundes stimmt.
- Reihe 8 „Start + Soll (4, frei)", Dimension 4. Reihe 10 „Start + Soll (3, frei)",
  Dimension 3. 4 + 3 = **7**, und 4+12+4+4+3+4 = **31**. Die Zahl „7 der 31" ist richtig,
  und „bei Reihe 10 wären das alle drei" folgt aus Dimension 3 gegen Soll 3.
- Reihe 7 trägt die Rolle „Start" — keine Sollreihe. Die T26-Zeile sagt dasselbe.

## 4. Der Kreuztest, den das Abnahmekriterium nicht verlangt

Der Befund entkräftet das Feld `License_Type` mit drei Kontrollabrufen. Ich habe die
Gegenprobe gesucht, die seine These *widerlegen* würde: einen Indikator, dessen
Drittanbieter für restriktive Bedingungen bekannt ist und bei dem das Feld deshalb
abweicht. Gemessen am 2026-09-02:

| Indikator | „Source" nennt | `License_Type` |
|---|---|---|
| `EG.USE.PCAP.KG.OE` | IEA Energy Statistics Data Browser, International Energy Agency (IEA) | `CC BY-4.0` |
| `CM.MKT.LCAP.CD` | World Federation of Exchanges database (WFE) | `CC BY-4.0` |

Die IEA ist der härteste denkbare Fall — ein Anbieter, der seine Bestände kostenpflichtig
lizenziert —, und das Feld sagt auch dort `CC BY-4.0`. Die These des Befundes hält also
nicht nur, sie hält gegen einen Fall, den er selbst nicht geprüft hat. Das Feld
unterscheidet nicht.

---

# Befund 1 — die Spalte „Verdacht" der Reihenliste ist keine Messung, und der Befund
# stützt sich an einer Stelle darauf

**An den Projektmanager. Kein Rückgabegrund für Paket 0005** — die Spalte stammt aus
`technik.md`, nicht vom Bauagenten, und der Umfang des Pakets war auf vier Reihen gesetzt.

Der Befund schreibt zum T26-Ersatzweg für Reihe 7: *„Der Ersatzweg liegt in Reihe 2
(`NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS`) bereits vor und ist selbst
unverdächtig."* Diese Aussage ist nicht gemessen, sondern aus der Spalte „Verdacht"
übernommen. Ich habe sie gemessen.

**So erzeugt man den Widerspruch, Schritt für Schritt:**

1. `https://api.worldbank.org/v2/sources/2/series/NV.AGR.TOTL.ZS/metadata?format=json`
   abrufen (2026-09-02).
2. Feld `Source` lesen. Es lautet:
   > Country official statistics, National Statistical Organizations and/or Central Banks;
   > National Accounts data files, Organisation for Economic Co-operation and Development (OECD);
   > Staff estimates, World Bank (WB)
3. Diesen Wortlaut gegen `daten.md` Nr. 8 halten: **„OECD — ungeklaert, nicht
   einplanen"** (Zeile 219).

Das ist exakt die Bauart, wegen der Reihe 13 gesperrt wurde: „Staff estimates" plus
namentlich genannte Drittbestände, deren Bedingungen `daten.md` nicht positiv geklärt
hat. Wendet man die Methode des Befundes auf Reihe 2 an, ist sie nicht „unverdächtig",
sondern mindestens `unklar` — und Reihe 2 trägt **12 der 31 Sollreihen** und ist zugleich
der Ersatzweg, mit dem T26 den Ausfall von Reihe 7 auffangen soll.

**Zwei weitere Gegenbeispiele derselben Spalte**, beide am 2026-09-02 gemessen:

| Reihe | Code | „Verdacht" laut Reihenliste | „Source" nennt tatsächlich |
|---|---|---|---|
| 1 (BIP, konstante Preise, **4 Sollreihen**) | `NY.GDP.MKTP.KD` | nein | OECD National Accounts data files, daneben nationale Ämter und WB staff |
| 6 (Erwerbstätige, exogener Pfad) | `SL.TLF.TOTL.IN` | nein | ILO, `type: estimates based on external database`; UN Population Division; WB staff |

Reihe 6 nennt damit denselben Drittanbieter wie Reihe 7, die die Reihenliste mit „ja"
markiert. Drei von drei stichprobenweise nachgemessenen „nein"-Zeilen nennen einen
Drittanbieter.

**Was daraus folgt** (Entscheidung des Projektmanagers, nicht meine): Die Frage, die
Paket 0005 für vier Reihen geschlossen hat, ist für mindestens drei weitere offen, und
eine davon (Reihe 2) trägt mehr Sollreihen als alle vier geprüften zusammen. Der Aufwand
ist derselbe wie hier: ein Abruf je Code. Der Befund selbst weist in die Richtung — seine
Kontrollzeile `NY.GDP.MKTP.CD` nennt „OECD, nationale Ämter, WB staff" —, zieht aber
keine Folgerung daraus, weil sie ausserhalb seines Auftrags lag.

# Befund 2 — die Stichtagsargumentation zur ILO verwechselt Abrufstand mit Erzeugung

**An den Projektmanager, geringes Gewicht. Kein Rückgabegrund** — das Urteil zu Reihe 7
lautet `unklar`, beide Lesarten stehen da, und der Bauagent wählt ausdrücklich keine.

Der Befund schreibt: *„der Weltbank-Eintrag weist als Abrufstand den 2026-01-17 aus,
liegt also nach dem Stichtag."* Der ILO-Vorbehalt lautet aber, im heute nachgelesenen
Wortlaut: *„Databases and datasets … **produced prior to** 3 May 2023 do not
automatically benefit from a Creative Commons licence."* Das Datum, auf das es ankommt,
ist der Zeitpunkt der **Erzeugung** des Bestandes, nicht der des Abrufs durch die
Weltbank. ILOEST als Datenbank besteht seit weit vor 2023; ob die im Januar 2026
abgerufene Ausgabe als „produced" nach dem Stichtag gilt, sagt weder der zitierte Satz
noch der Weltbank-Eintrag.

**So erzeugt man die Lücke:** Den Satz aus `www.ilo.org/rights-and-permissions` neben das
Feld `date accessed: January 17, 2026` legen und fragen, welches der beiden Daten der
Satz meint. Der Befund beantwortet die Frage nicht, sondern setzt beide gleich.

Folge: keine für das Urteil, aber der Zusatzauftrag an den Datenkurator, den der Befund
selbst vorschlägt („kostet vermutlich einen Abruf"), muss diese Frage mitstellen — sonst
kommt er mit derselben Zweideutigkeit zurück.

---

## Wonach ich gesucht und nichts gefunden habe

Damit diese Prüfung von einer, die nicht stattfand, unterscheidbar ist:

- **Erfundener oder geglätteter Wortlaut:** sieben Codes einzeln neu abgerufen, teils über
  den jeweils anderen Endpunkt. Kein Abweichen.
- **Falscher Indikatorcode für die Modelleinheit:** `FP.CPI.TOTL.ZG` ist die Jahresrate,
  wie Reihe 8 sie mit „bp Jahresrate" verlangt; `PA.NUS.FCRF` ist der Jahresdurchschnitt,
  passend zur Jahresauflösung des Modells. Beide `Periodicity: Annual`.
- **Stiller Einheitenbruch bei Reihe 10:** Die Reihenliste verlangt „Index", `PA.NUS.FCRF`
  liefert Landeswährung je US-Dollar, und Deutschland wechselt 1999 mitten im
  Prüfjahrgang die Währung. Das ist **kein neuer Befund**: `deckungsbefund-1997.md`
  (Paket 0006) führt den Bruch bereits, Zeile 219–225 und Zeile 330 („Einheitenbruch
  1999"). Beide Pakete benennen denselben Code — kein Widerspruch zwischen ihnen.
- **Verdeckte Interpolation oder ein Download:** Das Paket erzeugt genau eine Textdatei;
  `ls` über `daten/` und `git show --stat` zeigen keine Datenartefakte aus diesem Lauf.
- **Ein Urteil, das die Rolle nicht setzen darf:** Der Befund trifft keine
  Nutzbarkeitsentscheidung, nennt zu Reihe 7 beide Lesarten und verweist dreimal
  ausdrücklich auf den Betreiber. Kein Rechtsrat.
- **Eine übersehene T26-Folge:** T26 kennt drei Fälle; der dritte (Handelsmatrix vor 1995)
  betrifft keine der vier Reihen.

**Randnotiz, kein Befund:** Der Befund gibt den Indikatornamen zu `FP.CPI.TOTL.ZG` als
„Inflation, consumer prices (annual %)" an; der Metadaten-Endpunkt schreibt „Inflation,
consumer prices (annual % growth)". Das Abnahmekriterium verlangt den Wortlaut des Feldes
„Source", nicht den des Namens, und beide Schreibweisen führt die Weltbank selbst auf
verschiedenen Wegen. Ohne Folge.

**Die offene Stelle, die der Befund selbst benennt, bleibt offen und ist nicht sein
Fehler:** `imf.org/en/about/copyright-and-terms` wies den Abruf auch mir gegenüber ab.
Die IWF-Bedingungen tragen die beiden `frei`-Urteile und sind weiterhin nur über einen
Suchtreffer belegt. Der Befund sagt das an der richtigen Stelle und in der richtigen
Schärfe.
