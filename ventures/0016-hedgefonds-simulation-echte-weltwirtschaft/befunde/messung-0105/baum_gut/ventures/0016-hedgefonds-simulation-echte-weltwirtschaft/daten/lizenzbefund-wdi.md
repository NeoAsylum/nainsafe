---
typ: lizenzbefund
paket: 0005-wdi-drittanbieter-ausnahme
rolle: datenbauer
datum: 2026-09-01
gegenstand: WDI-Reihen 7, 8, 10, 13 gegen die Drittanbieter-Ausnahme der Weltbank-Lizenz
reihen_geprueft: 4
urteil_frei: 2
urteil_gesperrt: 1
urteil_unklar: 1
befund_an_spielentwerfer: nein
---

# Die vier WDI-Verdachtsreihen: eine gesperrt, eine unklar, zwei frei

**Reihe 13 (Zollniveau) ist gesperrt** — das Feld „Source" nennt WTO und UNCTAD, und
`daten.md` hat beider Bedingungen bereits als negativ beziehungsweise widersprüchlich
belegt. Damit tritt der erste Fall aus T26 ein: kein Zollpfad, konstanter Zoll im
Weltlauf, zwei statt drei verankerte Instrumente. Das ist die teuerste der vier Antworten
und die, wegen der das Paket vorgezogen wurde.

**Reihe 7 (Beschäftigung je Sektor) ist unklar, aber billig** — das Feld nennt die ILO
als Drittanbieter, und die ILO gewährt für ihre Datenbanken seit dem 2023-05-03
ausdrücklich CC BY 4.0. Beide Lesarten stehen unten; ich wähle keine. Der Ersatz aus T26
kostet keine Sollreihe.

**Reihen 8 und 10 sind frei** — beide nennen als Drittanbieter den IWF, und der IWF ist
genau die Quelle, deren Zustimmung `daten.md` unter Nr. 2 belegt und deren Daten das
Produkt ohnehin unmittelbar einbettet (Reihen 9, 11, 12). Kein Befund an den
Spielentwerfer, keine der 31 Sollreihen fällt. Die Freiheit hängt aber **nicht** an der
CC-BY-Lizenz der Weltbank, sondern an den IWF-Bedingungen — mit einer Folge für die
Namensnennung, siehe unten.

## Die vier Reihen im Überblick

| Nr | Größe | Indikatorcode | Drittanbieter laut „Source" | Urteil |
|---:|---|---|---|---|
| 13 | Zollniveau, aggregiert | `TM.TAX.MRCH.WM.AR.ZS` | WITS (WB), TRAINS (UNCTAD), IDB (WTO), CTS (WTO) | **gesperrt** |
| 7 | Beschäftigung je Sektor | `SL.AGR.EMPL.ZS`, `SL.IND.EMPL.ZS`, `SL.SRV.EMPL.ZS` | ILOEST (ILO) | **unklar** |
| 8 | Verbraucherpreise | `FP.CPI.TOTL.ZG` | IFS (IWF) | **frei** |
| 10 | Wechselkurs gegen USD | `PA.NUS.FCRF` | IFS (IWF) | **frei** |

Die Indikatorcodes standen in `daten.md` nicht; sie sind unten je Reihe mit Abruf-URL
belegt. Sämtliche Abrufe am **2026-09-01**.

---

## Reihe 13 — Zollniveau, aggregiert — **gesperrt**

**Indikatorcode:** `TM.TAX.MRCH.WM.AR.ZS` („Tariff rate, applied, weighted mean, all
products (%)")

**Abruf-URL:**
`https://api.worldbank.org/v2/sources/2/series/TM.TAX.MRCH.WM.AR.ZS/metadata?format=json`
(Feld `Source`), gegengelesen gegen
`https://api.worldbank.org/v2/indicator/TM.TAX.MRCH.WM.AR.ZS?format=json`
(Feld `sourceOrganization`, wortgleich). **Abrufdatum: 2026-09-01.**

**Feld „Source" im Wortlaut:**

> Staff estimates;
> World Integrated Trade Solution system (WITS), World Bank (WB);
> Trade Analysis and Information System (TRAINS), UN Conference on Trade and Development (UNCTAD);
> Integrated Data Base (IDB), World Trade Organization (WTO);
> Consolidated Tariff Schedules (CTS), World Trade Organization (WTO)

**Begründung:** Von fünf genannten Beständen ist einer eine Eigenleistung der Weltbank
(„Staff estimates"), die vier übrigen sind Drittbestände — und zu dreien davon hat
`daten.md` die Bedingungen bereits im Wortlaut gelesen: WTO Nr. 12 („Commercial use of
materials from the website requires written permission from the WTO", also negativ, weil
Hausregel 2 den Weg über eine Anfrage verschließt), WITS Nr. 13 (reicht die Auflagen
seiner Lieferanten durch, negativ) und UNCTAD Nr. 9 (widersprüchlich, ungeprüft). Der
Zollsatz ist damit die eine der vier Reihen, bei der der genannte Drittanbieter seine
Zustimmung nicht erteilt, sondern sie ausdrücklich vorbehält.

**Folge nach T26, erster Fall:** Kein Zollpfad; der Weltlauf läuft mit konstantem Zoll.
Das Orakel hat zwei statt drei verankerte Instrumente. Reihe 13 trägt keine der 31
Sollreihen (sie ist „Start + Politikpfad"), der Rückvergleich verliert also keine
Sollreihe, wohl aber seine Verankerung im wichtigsten Instrument des Spiels.

**Zwei Dinge, die dagegensprechen, und warum sie das Urteil nicht drehen** — beide
gehören dem Betreiber, nicht mir:

1. Der Weltbank-Datensatz selbst führt für diese Reihe `License_Type: "CC BY-4.0"`. Warum
   das nicht trägt, steht unten unter *Das Lizenzfeld*.
2. „Staff estimates" steht an erster Stelle: Der veröffentlichte Wert ist eine Berechnung
   der Weltbank aus fremden Tariflinien, keine Durchreichung. Ob eine solche Aggregation
   die Auflagen der Lieferanten abstreift — wie es Comtrade für transformierte Bestände
   ausdrücklich zulässt (`daten.md` Nr. 3) —, ist genau die Rechtsfrage, die diese Rolle
   nicht beantwortet.

**Nebenbefund für Paket 0006, nicht von mir zu verwerten:** Das Feld `Referenceperiod`
dieser Reihe lautet `1988-2022`. Der Prüfjahrgang 1997–2021 liegt darin.

---

## Reihe 7 — Beschäftigung je Sektor — **unklar**

**Indikatorcodes:** `SL.AGR.EMPL.ZS`, `SL.IND.EMPL.ZS`, `SL.SRV.EMPL.ZS`
(„Employment in agriculture / industry / services (% of total employment) (modeled ILO
estimate)")

**Abruf-URLs:** `https://api.worldbank.org/v2/sources/2/series/<code>/metadata?format=json`
für alle drei Codes, gegengelesen gegen
`https://api.worldbank.org/v2/indicator/<code>?format=json`. **Abrufdatum: 2026-09-01.**

**Feld „Source" im Wortlaut** — bei allen drei Codes zeichengleich dasselbe:

> ILO Modelled Estimates database (ILOEST), International Labour Organization (ILO), uri: https://ilostat.ilo.org/data/bulk/, publisher: ILOSTAT, type: external database, date accessed: January 17, 2026

**Begründung:** Die Weltbank bezeichnet den Bestand hier selbst als `type: external
database` und nennt den Drittanbieter mit Namen, Adresse und Abrufdatum. Damit ist die
Drittanbieter-Ausnahme der Fassung nach eröffnet — anders als bei Reihe 13 verweigert der
Drittanbieter seine Zustimmung aber nicht, sondern erteilt sie:

> As of 3 May 2023, databases and datasets together with the accompanying referential metadata are covered by the Creative Commons CC BY 4.0 licence.

mit der Einschränkung

> This licence does not apply to microdata submitted by or obtained from constituents and partner institutions that is restricted solely to the ILO's use.

und dem Vorbehalt

> Databases and datasets together with the accompanying referential metadata produced prior to 3 May 2023 do not automatically benefit from a Creative Commons licence.

(`https://www.ilo.org/rights-and-permissions`, abgerufen 2026-09-01, direkter
Seitenabruf.)

ILOEST ist eine Datenbank, keine Mikrodatensammlung, und der Weltbank-Eintrag weist als
Abrufstand den 2026-01-17 aus, liegt also nach dem Stichtag. Beide Lesarten:
(a) Die Drittanbieter-Ausnahme greift, der Drittanbieter erlaubt es aber ausdrücklich —
dann frei. (b) Die ILO steht nicht unter den in `daten.md` geprüften Quellen, und eine
Quelle, die dort nicht steht, gilt in dieser Fabrik als ungeprüft, nicht als erlaubt —
dann bleibt es zu klären. **Ich wähle keine.** Die Bewertung „nutzbar" trifft der
Betreiber; die Aufnahme der ILO in die geprüften Quellen wäre ein kleiner Zusatzauftrag
an den Datenkurator und kostet nach dem oben Zitierten vermutlich einen Abruf.

**Folge nach T26, zweiter Fall** (falls es bei `unklar` bleibt oder gesperrt wird):
Aufteilung nach Wertschöpfungsanteil; der Startwert wird ein Modellkonstrukt. **Keine
Sollreihe ist betroffen** — Reihe 7 ist reiner Startwert. Der Ersatzweg liegt in Reihe 2
(`NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS`) bereits vor und ist selbst
unverdächtig.

Das ist die billigste der vier Antworten: Sie kostet drei Adressen ihren Datenanker und
sonst nichts.

---

## Reihe 8 — Verbraucherpreise — **frei**

**Indikatorcode:** `FP.CPI.TOTL.ZG` („Inflation, consumer prices (annual %)") — die
Jahresrate, wie sie die Reihenliste in `technik.md` Abschnitt 7 als Modelleinheit „bp
Jahresrate" verlangt.

**Abruf-URL:** `https://api.worldbank.org/v2/sources/2/series/FP.CPI.TOTL.ZG/metadata?format=json`,
gegengelesen gegen `https://api.worldbank.org/v2/indicator/FP.CPI.TOTL.ZG?format=json`.
**Abrufdatum: 2026-09-01.**

**Feld „Source" im Wortlaut:**

> International Financial Statistics database, International Monetary Fund (IMF)

**Begründung:** Der genannte Drittanbieter ist der IWF, und dessen Bedingungen erlauben
nach `daten.md` Nr. 2 wortwörtlich das Vervielfältigen, Verbreiten und **Verkaufen**
seiner Daten. Die Ausnahme der Weltbank-Lizenz verlangt „the consent of the original data
provider" — dieser Anbieter hat sie in seinen allgemeinen Bedingungen erteilt. Hinzu
kommt ein Umstand, der die Frage praktisch entschärft: Dieselbe Größe kommt in diesem
Vorhaben ohnehin unmittelbar vom IWF (Reihen 9, 11, 12 nach `daten.md`), die Reihe hängt
also nicht an der Weltbank als Durchreicher.

`Referenceperiod` dieser Reihe: `1960-2025`, `Periodicity: Annual`.

**Zwei Auflagen, die aus diesem Urteil folgen und die kein späteres Paket überspringen
darf:**

1. Die Namensnennung für die Reihen 8 und 10 ist **nicht** die der Weltbank allein. Wer
   sich für die Weitergabe auf die IWF-Zustimmung stützt, übernimmt deren Auflagen:
   Quellenangabe IWF, ausdrückliche Angabe der materiellen Transformation und der Satz
   aus `daten.md` (*„Die verwendeten IWF-Statistikdaten sind beim IWF kostenfrei
   erhältlich."*). Beides steht in `daten.md` unter *Der Vorschlag* bereits geschrieben —
   neu ist nur, dass es **auch für diese beiden WDI-Reihen** gilt und nicht nur für die
   unmittelbar vom IWF geholten.
2. Die offene Stelle aus `daten.md` bleibt offen und ist heute erneut gescheitert:
   `https://www.imf.org/en/about/copyright-and-terms` hat den direkten Abruf am
   2026-09-01 mit **HTTP 403** abgewiesen, genau wie am 2026-08-31. Der IWF-Wortlaut ist
   damit weiterhin nur über einen Suchtreffer belegt. Er trägt die Urteile zu Reihe 8 und
   10 — das ist der schwächste Punkt dieses Befundes und gehört vor dem Bau aus dem
   Volltext bestätigt, aus einem anderen Netz oder durch den Betreiber.

---

## Reihe 10 — Wechselkurs gegen USD — **frei**

**Indikatorcode:** `PA.NUS.FCRF` („Official exchange rate (LCU per US$, period average)")

**Abruf-URL:** `https://api.worldbank.org/v2/sources/2/series/PA.NUS.FCRF/metadata?format=json`,
gegengelesen gegen `https://api.worldbank.org/v2/indicator/PA.NUS.FCRF?format=json`.
**Abrufdatum: 2026-09-01.**

**Feld „Source" im Wortlaut:**

> International Financial Statistics database, International Monetary Fund (IMF)

**Begründung:** Zeichengleich dieselbe wie bei Reihe 8, und dieselbe Begründung gilt. Die
Reihenliste führt Reihe 10 mit der Quelle „IWF IFS / WDI"; der Weltbank-Datensatz bestätigt
mit diesem Feld, dass beide Wege auf denselben Bestand zeigen. `Referenceperiod: 1960-2025`,
`Periodicity: Annual`.

Die beiden Auflagen aus Reihe 8 gelten hier unverändert.

---

## Die Zahl für den Fall, dass die IWF-Kette doch reißt

Der Auftrag verlangt sie, und sie kostet eine Zeile: Würden die Reihen 8 und 10 später
doch gesperrt — nicht wegen der Weltbank, sondern weil die IWF-Bedingungen im Volltext
anders lauten als der Suchtreffer sagt —, dann fielen **7 der 31 Sollreihen**: vier aus
Reihe 8 (Verbraucherpreise, vier Länder) und drei aus Reihe 10 (Wechselkurs, drei
Länder). Bei Reihe 10 wären das **alle drei** Wechselkurs-Sollreihen, der Rückvergleich
verlöre die Größe also vollständig. Dieser Fall träfe zugleich die Reihen 9, 11 und 12,
die unmittelbar vom IWF kommen — es wäre kein Befund über eine WDI-Reihe, sondern über
eine der vier tragenden Quellen des Vorhabens.

Wie viele der 31 Sollreihen wegfallen dürfen, entscheidet T37 und nicht diese Rolle. Da
mein Urteil zu beiden Reihen `frei` lautet, ist das **kein Befund an den Spielentwerfer**,
sondern eine Zahl für den Fall, den die Auflage 2 unter Reihe 8 offenhält.

---

## Das Lizenzfeld — ein Fund, der nichts entscheidet, und warum das wichtig ist

Der Metadaten-Endpunkt der Weltbank führt je Reihe ein Feld `License_Type`. Es sieht aus
wie die Antwort auf genau die Frage dieses Pakets, und es ist keine. Gemessen:

| Reihe | Feld „Source" nennt | `License_Type` |
|---|---|---|
| `TM.TAX.MRCH.WM.AR.ZS` (13) | WITS, UNCTAD, WTO | `CC BY-4.0` |
| `SL.AGR/IND/SRV.EMPL.ZS` (7) | ILO | `CC BY-4.0` |
| `FP.CPI.TOTL.ZG` (8) | IWF | `CC BY-4.0` |
| `PA.NUS.FCRF` (10) | IWF | `CC BY-4.0` |
| `NY.GDP.MKTP.CD` (Kontrolle, Weltbank-eigen) | OECD, nationale Ämter, WB staff | `CC BY-4.0` |
| `CM.MKT.LCAP.CD` (Kontrolle) | World Federation of Exchanges | `CC BY-4.0` |
| `IT.CEL.SETS` (Kontrolle) | ITU | `CC BY-4.0` |

`License_URL` lautet in allen sieben Fällen
`https://datacatalog.worldbank.org/int/public-licenses#cc-by`. Sieben Reihen, sieben
verschiedene Herkünfte — darunter mit der WFE und der ITU zwei Anbieter, die ihre eigenen
Bestände bekanntlich nicht freigiebig lizenzieren —, und **immer derselbe Wert**. Ein
Feld, das nie widerspricht, unterscheidet nicht; es gibt die Datenbanklizenz der WDI
wieder, nicht eine Prüfung je Reihe.

Deshalb steht es hier: Wer es später findet, ohne die Kontrollen zu kennen, liest es als
Freigabe für Reihe 13 und hebt damit ein Urteil auf, das auf dem Wortlaut zweier
Drittanbieter beruht. Die drei Kontrollabrufe kosteten je einen Abruf und schließen genau
diesen Fehlschluss.

Ob das Feld gleichwohl eine belastbare Zusage der Weltbank ist — sie schreibt sie schließlich
selbst und je Reihe hin —, ist eine Rechtsfrage. Sie gehört dem Betreiber, und sie ist
billig zu stellen: Sie betrifft nur noch Reihe 13, denn 7 löst sich über die ILO, 8 und 10
über den IWF.

## Belegführung und ihre Grenze

Der Abruf lief über zwei Endpunkte der Weltbank-Schnittstelle, weil sie verschiedene
Felder tragen:

- `…/v2/sources/2/series/<code>/metadata?format=json` liefert ein Feld, das **wörtlich
  `Source` heißt** — das im Auftrag verlangte. Es liefert zusätzlich `License_Type`,
  `Periodicity` und `Referenceperiod`.
- `…/v2/indicator/<code>?format=json` liefert dasselbe unter dem Namen
  `sourceOrganization`.

Beide wurden für jede der vier Reihen getrennt abgerufen und stimmen zeichengleich
überein, einschließlich der vier Zeilenumbrüche in Reihe 13 — im Rohtext stehen sie als
JSON-Escapes (Rückwärtsschrägstrich, `u000a`), sind also nicht nachträglich gesetzt. Das ist
die Gegenprobe gegen die eine Schwäche des Verfahrens: Der Abruf lief nicht über eine
Shell, sondern über ein Werkzeug, das die Seite aufbereitet — ein einzelner Abruf könnte
umformuliert sein, zwei unabhängige Abrufe mit identischer Zeichenfolge nicht plausibel
beide auf dieselbe Weise.

Nicht erreichbar am 2026-09-01, beide mit **HTTP 403**: `www.imf.org` (Nutzungsbedingungen)
und `ilostat.ilo.org` (Nutzungsbedingungen). Für die ILO trug der Ausweichabruf auf
`www.ilo.org/rights-and-permissions`; für den IWF gibt es keinen, siehe Auflage 2 unter
Reihe 8.

**Was dieser Befund nicht ist:** kein Rechtsrat. Er zitiert, was die Weltbank, die ILO und
— vermittelt über `daten.md` — der IWF, die WTO und Comtrade über sich selbst sagen. Ob
das für die Einbettung in ein verkauftes Spiel genügt, entscheidet der Betreiber.

**Was dieser Befund nicht getan hat:** Es wurde nichts heruntergeladen und nichts
eingebettet. Diese Datei ist das einzige Erzeugnis des Pakets.
