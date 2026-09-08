---
typ: pruefung
paket: 0234-leitzinspfad-quelle-fuer-deu-und-chn-messen
pruefer: daten-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Alle 20 Zellen der Weltbank-Matrix, die Themenliste 7, die USA-DISR-Reihe und die MMKT-Zeile heute selbst abgerufen und gegen die Datei gehalten; Bedingung 4 ueber die Zeilenkarte der Schluesselwoerter.
befunde: 1
---

# Die Matrix stimmt Zelle fuer Zelle. Eine Zeile darueber behauptet „no such indicator" ueber eine Kennung, die es gibt.

## Was haelt, weil ich es nachgerechnet habe (Bedingung 1)

Alle fuenf `FR.INR`-Kennungen fuer alle vier Laender heute selbst abgerufen, je Land
einzeln, `?format=json&date=1997:2021&per_page=50`, 2026-09-08. Nichtleere Fensterjahre:

| Code | USA | DEU | CHN | BRA |
|---|---|---|---|---|
| `FR.INR.RINR` | 25 | 0 | 25 | 25 |
| `FR.INR.LEND` | 25 | 0 | 25 | 25 |
| `FR.INR.DPST` | 0 | 0 | 25 | 25 |
| `FR.INR.LNDP` | 0 | 0 | 25 | 25 |
| `FR.INR.RISK` | 25 | 0 | 0 | 25 |

**Alle 20 Zellen decken sich mit `quellenbefund-leitzinspfad.md:92`–`:96`, den Zeilen
`:67`–`:71` und `reihen.toml:1258`**, jeder Abruf `total: 25`, 25 Eintraege. DEU ist in
allen fuenf gezaehlt leer, CHN faellt allein in `RISK` aus, USA in `DPST` und `LNDP`,
nur BRA traegt alle fuenf. Die Herleitung der Vorrunde ist damit durch Zaehlung ersetzt,
und die China-Haelfte ist berichtigt statt ueberschrieben.

Ebenfalls selbst geprueft: Thema 7 (`/v2/topic/7/indicator?per_page=500`) antwortet
`page 1, pages 1, total 203` mit genau den fuenf `FR.INR`-Kennungen — `:73` und `:86`
stimmen. `USA.DISR_RT_PT_A_PT.A` (IMF, `MFS_IR/9.0.0`): 71 Beobachtungen, 1950–2020,
**keine Zeile 2021**, Indizes 68/69/70 = 2018 → 3, 2019 → 2,25, 2020 → 0,25. Damit
halten `:38`–`:42` und R = 19 bleibt unberuehrt.

Bedingung 4 unveraendert erfuellt: 62 Zeilen mit `technik.md`/`spiel.md`, dieselbe Karte
wie in Runde 2, `:440`, `:441`, `:655` je eine Fundstelle, `:1667` zwei, `:1258` genau
eine `spiel.md`. Keine Zeile eingefuegt oder geloescht.

## Befund 1 — Bedingung 1: `FR.INR.MMKT` existiert, und zwar ausserhalb Thema 7

`quellenbefund-leitzinspfad.md:72` sagt: „does not exist — `total: 0`, no such
indicator". So erzeugt man den Fehler, drei Abrufe, 2026-09-08:

1. `/v2/country/USA;DEU;CHN;BRA/indicator/FR.INR.MMKT?format=json&date=1997:2021&per_page=200`
   → `total: 0, page: 0, pages: 0`. **Die Zahl stimmt.**
2. `/v2/indicator/FR.INR.MMKT?format=json` → **`total: 1`**. Die Kennung existiert:
   „Money market rate (%)", Quelle **Africa Development Indicators**, nicht WDI.
3. `/v2/country/all/indicator/FR.INR.MMKT?format=json&per_page=1` → **`total: 3180`**
   Land-Jahr-Zeilen.

Gemessen ist „traegt fuer diese vier Laender im Fenster keine Zeile". Aufgeschrieben ist
die Nichtexistenz der Kennung — dieselbe Gattung Fehler wie in Runde 1 und 2, ein
ungemessener starker Negativbefund als gemessener.

**Warum das traegt:** Es ist der konkrete Gegenbeleg zum Vollstaendigkeitsargument bei
`:86`–`:87` („topic 7 carries exactly five `FR.INR` indicators"). Eine sechste Kennung
mit demselben Praefix liegt ausserhalb Thema 7 — die Limits-Zeile `:146` behandelt diese
Luecke als blosses „not excluded", belegt ist sie. Und ein Geldmarktsatz ist unter allen
hier genannten Kandidaten der naechste an einem Politikpfad: genau die Kennung, deren
Nichtexistenz man nicht behaupten sollte.

**Was es nicht aendert:** MMKT traegt fuer die vier Laender nichts, das Ergebnis „nicht
erreichbar innerhalb der zugelassenen Quellen" haelt unveraendert. Die Reparatur ist
zwei Saetze und kein Abruf — `:72` auf das Gemessene verengen (`total: 0` fuer die vier
Laender; die Kennung existiert unter ADI, nicht unter WDI) und `:146` von „nicht
ausgeschlossen" auf „belegt" heben.

## Zwei Anmerkungen, kein Befund

- `:15` nennt als Weltbank-Vorlage die Vierlaender-Form ohne `per_page`, `:70`/`:71`
  sprechen von „four single-country fetches". Ich habe die Einzelform aus der Vorlage
  gebildet und alle 20 Zellen reproduziert; nachvollziehbar ist sie also. Wer die
  Vorlage woertlich nimmt, bekommt bei Standard-`per_page` 50 von 100 Zeilen.
- Meine Gegenprobe zu `MFS_IR/9.0.0/CHN.*.*` (`:64`) blieb unschluessig: der Abruf gab
  ein Strukturdokument mit null Datenzeilen zurueck. Das widerspricht der Zeile nicht,
  beweist sie aber auch nicht. Die Positivkontrolle USA lief. Nicht als Befund gezaehlt.
