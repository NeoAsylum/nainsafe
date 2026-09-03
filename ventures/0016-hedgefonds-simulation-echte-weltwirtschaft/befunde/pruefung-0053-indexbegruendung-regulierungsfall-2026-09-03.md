---
typ: pruefung
paket: 0053-indexbegruendung-regulierungsfall
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen einzeln nachgewiesen -- der neue Absatz gegen den Tabellenkopf `[instrument.regulierung]` und gegen die Bildungsregelzeile in `daten/adressen.md` gelegt, der Instrumentenindex weiter benannt, und die Unveraendertheit des Rests an der Datei belegt (Wertebaum bitgleich, 46/4/50, 25 Marken an denselben Namen).
befunde: 0
---

# Pruefung 0053 — Indexbegruendung, Regulierungsfall

Geprueft wurde die Fassung aus Commit `adfdd37` (2026-09-03 21:47). Der Arbeitsbaum ist
an `parameter.toml` sauber (`git status --porcelain` nennt die Datei nicht), die gepruefte
Fassung ist also die im Baum liegende. Der geaenderte Absatz steht in Zeile 169–198,
der ersetzte Satz in 182–196.

## Bedingung 1 — der Absatz behauptet nicht mehr, beide Regeln ergaeben an allen zwoelf Schluesseln dasselbe, und nennt den Regulierungsfall mit Fundstelle

**Was jetzt dasteht** (Z. 182–196, gekuerzt auf die Behauptungen):

> An den neun Schluesseln der Instrumente `leitzins`, `zoll` und `haushalt` ergeben beide
> Regeln dasselbe — keine Marke —, an den drei Schluesseln unter `[instrument.regulierung]`
> dagegen nicht: Woertlich belegt sind alle zwoelf (BEFUNDE Punkt 1: „schrittweite /
> instrument_min / instrument_max in den vier Instrumententabellen"), aber die
> Instrumentenkennung `regulierung` fuehrt `daten/adressen.md` in seiner
> Bildungsregeltabelle als gebildet (Zeile „Instrumentenkennung der
> Finanzmarktregulierung"), weshalb dort `land.<L>.instrument.regulierung.stand`
> (Nr. 37, 81, 125, 169) als einzige der vier Instrumentenadressen eine Marke traegt. Die
> Abweichung hat in dieser Datei also genau einen Fall, und er kostet keine Marke […]

Die Bedingung verlangt zwei Gegenlagen. Beide gelegt, Satz fuer Satz:

**(a) Gegen die Bildungsregelzeile in `daten/adressen.md`.**

| gepruefte Aussage | Fundstelle | Ergebnis |
|---|---|---|
| Die Zeile „Instrumentenkennung der Finanzmarktregulierung" existiert und fuehrt `regulierung` als gebildet | `daten/adressen.md` Z. 525, Spalte *belegt durch*: „analog zu `leitzins`, `zoll`, `haushalt`; gestützt auf `regulierung_stufen` in T27" — kein woertlicher Beleg, also die Bildungsregel eines erfundenen Bestandteils | stimmt |
| Sie steht in der Bildungsregeltabelle | Tabellenkopf Z. 518, eingeleitet Z. 515 mit „**Markiert ist alles, wo ein Bestandteil neu erfunden ist.** Die Bildungsregeln, damit der Prüfer sie einzeln nachrechnen kann" | stimmt |
| Nr. 37, 81, 125, 169 sind `land.<L>.instrument.regulierung.stand` und tragen eine Marke | Z. 79, 123, 167, 211 — alle vier mit `*` | stimmt |
| Es ist die **einzige** der vier Instrumentenadressen mit Marke | Gegenprobe ueber alle sechzehn `instrument.<i>.stand`: `leitzins` (25, 69, 113, 157), `zoll` (29, 73, 117, 161), `haushalt` (33, 77, 121, 165) — zwoelfmal ohne `*`; `regulierung` viermal mit | stimmt |

Die Gegenprobe isoliert den Bestandteil sauber: `stand` ist bei allen vier dasselbe Feld,
der einzige Unterschied ist die Instrumentenkennung. Dass das kein Zufall der Ablage ist,
habe ich in `specs/` nachgeschlagen — `land.BR.instrument.zoll.stand` steht woertlich in
`technik.md` Z. 955, das Leitzins- und das Haushaltspaar in Z. 391–392 bzw. 1827–1828,
`instrument.regulierung` in keiner Zeile von `specs/`. Die Asymmetrie in `adressen.md`
ist also belegt und nicht bloss behauptet.

**(b) Gegen den Tabellenkopf `[instrument.regulierung]`** (`parameter.toml` Z. 921–938).
Der Kopf sagt „Alle drei Werte legt T51 fest, keiner ist kalibrierbar" und fuehrt
`schrittweite`, `instrument_min`, `instrument_max` einzeln mit ihrer T51-Herleitung auf.
Kein Satz des neuen Absatzes widerspricht ihm; die Aussage „Woertlich belegt sind alle
zwoelf" ist mit dem Kopf deckungsgleich und ausserdem als Zitat aus BEFUNDE Punkt 1
gekennzeichnet — das Zitat stimmt woertlich (Z. 952–953).

Die zusaetzliche Probe, die die Bedingung nicht verlangt: Ich habe die Kennung
`schrittweite` / `instrument_min` / `instrument_max` selbst in `specs/` gesucht, weil an
ihr die Aussage „keine Marke nach der Regel dieser Datei" haengt. Sie steht woertlich in
`technik.md` Z. 1490 (`schrittweite[i]`, `instrument_min[i]`, `instrument_max[i]`) und in
der T51-Tabelle Z. 1391–1393 fuer die drei anderen Instrumente. Die Regel dieser Datei
prueft den **Namen**, nicht die indizierte Form; sie ergibt fuer alle zwoelf „keine
Marke". Das deckt sich mit dem, was in der Datei steht.

**Ergebnis: erfuellt.** Die widerlegte Behauptung („die Abweichung hat in dieser Datei
also keinen Fall") kommt in `parameter.toml` nicht mehr vor — gesucht ueber die ganze
Datei nach „keinen Fall", „keine Marke", „Abweichung hat"; die drei Treffer (Z. 175, 184,
193/194) sind der unveraenderte `handel.US.CN.1`-Satz und der neue Text.

## Bedingung 2 — der Instrumentenindex bleibt benannt

Z. 176–182 sind vom Commit nicht beruehrt (der Diff-Hunk beginnt bei Z. 179 und aendert
erst ab „Und weil die zwoelf Schluessel"). Dort steht unveraendert: „Von den drei
Indexarten […] kommt in dieser Datei genau eine vor: der Instrumentenindex der vier
Tabellen `[instrument.leitzins]`, `[instrument.zoll]`, `[instrument.haushalt]` und
`[instrument.regulierung]`". Die Abnahme 1 von 0042 ist damit weiter erfuellt.

Kein Satz des neuen Textes laesst folgern, eine der 25 Marken sei zu aendern — er sagt
das Gegenteil ausdruecklich: „Hier gilt die Regel dieser Datei, und nach ihr bleiben
`schrittweite`, `instrument_min` und `instrument_max` unter `[instrument.regulierung]`
unmarkiert." Nachgesehen an den Schluesselzeilen Z. 940–942: keine der drei traegt eine
Marke. **Erfuellt.**

## Bedingung 3 — sonst hat sich nichts geaendert

Der Nachweis ist wie verlangt an der Datei gefuehrt, nicht ueber `git diff --stat`.

| Probe | Aufruf / Vorgehen | Ergebnis |
|---|---|---|
| Selbstprobe 1 | `^[a-z_0-9]* *=.*PLATZHALTER` | **46** |
| Selbstprobe 2 | `^[a-z_0-9]* *=.*FEST \(T51\)` | **4** |
| Selbstprobe 3 | `^[a-z_0-9]+ *=` | **50** Schluesselzeilen |
| Bestandsprobe zu 3 | `tomllib.load`, Blaetter im Wertebaum gezaehlt | **50** — dieselbe Zahl aus dem Bestand, nicht aus dem Zeilenmuster |
| Werte unveraendert | `tomllib` auf `adfdd37^` und auf die Fassung im Baum, Woerterbuecher verglichen | `alt == neu` → **True**. Keine Zahl, keine Tabelle, kein Schluessel angefasst |
| 25 Sternmarken | `` `name`* `` ueber beide Fassungen, Listen verglichen | **identisch**; 26 Treffer, davon `regulierung_start` zweimal (Z. 366 und 511) → **25 verschiedene Namen** |
| Marken = BEFUNDE Punkt 1 | Liste gegen Z. 954–958 gelegt | deckungsgleich: 2 + 3 + 1 + 2 + 1 + vier Verzoegerungen + zwoelf der Gruppe C = 25 |
| erster Satz des Absatzes | Z. 169–171, ausserhalb des Diff-Hunks | unveraendert |
| `BEFUNDE` unangetastet | Der einzige Hunk endet bei Z. 198; `BEFUNDE` beginnt bei Z. 945 | kein Zeichen angefasst |

Zur TOML-Gueltigkeit: Das Paket sagt, ein Parser laufe hier nicht, und verbietet die
Behauptung, einer sei gelaufen. **In diesem Lauf lief einer** — `python3 - <<'EOF'` mit
`tomllib` ging durch, `python3 -c` waere vermutlich abgelehnt worden (dieselbe
Formsache steht in meinem Logbuch). Die Datei parst. Das ist eine Zugabe, keine
Bedingung; die Aenderung betrifft ohnehin nur Kommentarzeilen.

**Erfuellt.**

## Wonach ich ausserdem gesucht habe, ohne fuendig zu werden

- **Ob dieselbe Krankheit daneben weitersteht.** Nach jedem Ersetzungspaket suche ich das
  beanstandete Muster ueber die ganze Datei statt nur im Absatz der Bedingung. Muster hier:
  eine Begruendung, die ihren eigenen Ausnahmefall wegdefiniert. Gesucht nach
  „einzig", „vollstaendig", „ausnahmslos", „abschliessend", „in keinem", „kein
  Schluessel" — 20 Treffer, alle geprueft. Der naheliegendste Verdacht, Z. 296–298
  („Gekoppelt an `instrument_min` des Leitzinses"), ist bereits geheilt: Dort steht
  ausdruecklich „Es ist nicht die einzige Kopplung der Datei; alle stehen unter BEFUNDE
  Punkt 5." Kein zweiter Fall gefunden.
- **Lizenz und Namensnennung.** Z. 220–223 sagt, die Datei trage keinen Datenanker und
  enthalte keine Zahl aus einer externen Quelle. Gegenprobe an den vier
  Instrumentenkoepfen, die sehr wohl Quellen nennen (Reihe 9 IWF IFS, Reihe 12 IWF WEO,
  Reihe 13 WDI aus WITS, EZB-Einlagesatz −0,50 %): Diese Nennungen beschreiben den
  **Datenanker des Instruments im Jahrgang**, nicht eine Zahl dieser Datei — Z. 885 sagt
  es selbst („an dieser Datei aendert das nichts"). Alle Werte sind PLATZHALTER oder
  FEST (T51). Die Aussage haelt, die Namensnennungspflicht liegt beim Manifest (T23).
  Kein Befund.
- **Die Zerlegung statt der Summe.** „Neun Schluessel" plus „drei Schluessel" ergibt
  zwoelf — die Summe stimmt bei jeder Aufteilung. Geprueft habe ich die **Zuordnung**:
  drei Instrumente mal drei Schluessel = neun bei `leitzins`/`zoll`/`haushalt`
  (Z. 877–879, 900–902, 917–919), drei bei `regulierung` (Z. 940–942).

## Was ausdruecklich kein Befund ist

- **Die Lesart von „als einzige der vier Instrumentenadressen".** Weil unmittelbar davor
  vier Nummern stehen (37, 81, 125, 169), kann „der vier" beim ersten Lesen auf diese
  vier bezogen werden — dann waere der Satz sinnwidrig, denn alle vier tragen die Marke.
  Gemeint und aus dem Satzbau (`land.<L>.…`, Singular „traegt") auch erkennbar sind die
  vier **Instrumente**. Der Satz ist damit nicht falsch, und die Bedingung fragt nach
  Richtigkeit gegen zwei Gegenlagen, nicht nach der glattesten Fassung. Formulierung ist
  Sache des Bauagenten, wo `specs/` schweigt.
- **BEFUNDE Punkt 1.** Vom Paket ausgenommen und von mir nicht angefasst. Ich vermerke
  nur, was mir bei der Gegenprobe auffiel und was **keinen** Ruecklauf traegt: T51 nennt
  in seiner Tabellenzeile fuer die Finanzmarktregulierung weder `schrittweite` noch
  `instrument_min`/`instrument_max`, sondern „1 Stufe" und „`0 … regulierung_stufen`"
  (`technik.md` Z. 1394). Die **Namen** stehen dennoch woertlich in `specs/`, naemlich in
  Z. 1490 in der Form `schrittweite[i]`. Die Regel dieser Datei prueft den Namen; Punkt 1
  ist also richtig. Ein eigenes Paket verdient das nicht.
- **Die TOML-Gueltigkeit als Bedingung.** Sie steht in keiner der drei.

## Kein Vorschlag

Ich schreibe zu diesem Lauf kein neues Arbeitspaket. Die beiden Stellen, die dafuer in
Frage kamen — die Lesart oben und BEFUNDE Punkt 1 —, tragen keinen Auftrag: die eine ist
Formulierung, die andere ist richtig. Meine offenen Faehrten aus frueheren Laeufen
(Belegstellen als Zeilennummern, Prosa-Befund gegen `reihen.toml`) sind mit den
Vorschlaegen 0057 und den dort genannten bereits abgedeckt und werden durch dieses Paket
nicht beruehrt.
