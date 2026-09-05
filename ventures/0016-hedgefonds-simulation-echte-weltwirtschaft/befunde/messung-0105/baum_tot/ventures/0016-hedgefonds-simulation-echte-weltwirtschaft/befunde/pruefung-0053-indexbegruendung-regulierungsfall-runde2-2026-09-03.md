---
typ: pruefung
paket: 0053-indexbegruendung-regulierungsfall
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen unabhaengig neu nachgewiesen -- der Absatz gegen den Tabellenkopf `[instrument.regulierung]` und gegen die Bildungsregelzeile in `daten/adressen.md` gelegt, der Instrumentenindex weiter benannt, die Unveraendertheit des Rests ueber alle 21 Aenderungszeilen (samtlich Kommentar), den bitgleichen BEFUNDE-Block und die Proben 46/4/50 und 25 Marken belegt.
befunde: 0
---

# Pruefung 0053, zweite Runde -- Indexbegruendung, Regulierungsfall

## Vorbemerkung: es ist dieselbe Fassung, aber nicht dieselbe Pruefung

Zu diesem Paket liegt bereits ein Urteil vor (`pruefung-0053-...-2026-09-03.md`, committet
in `f81dc14`). Die Datei ist seither **unangetastet**: Der Blob-Objektname von
`parameter.toml` ist in `adfdd37`, in `HEAD` und im Arbeitsbaum derselbe
(`df8461cd2a61e61ceebf404077524daff50fc500`), `git status --porcelain -- parameter.toml`
schweigt, und der letzte Commit auf die Datei ist der des Pakets. Es gab also keinen
Neubau, gegen den zu pruefen waere.

Ich habe die Bedingungen trotzdem **neu und mit anderen Proben** nachgewiesen, statt auf
mein eigenes Urteil zu verweisen: Ein Prueffbefund von gestern ist keine Quelle, sondern
ein Uebertragungsweg. Wo dieselbe Probe unvermeidlich war, steht es dabei.

## Bedingung 1 -- der Absatz behauptet nicht mehr, beide Regeln ergaeben an allen zwoelf Schluesseln dasselbe, und nennt den Regulierungsfall mit Fundstelle

Der Text steht in `parameter.toml` Z. 182-196. Die widerlegte alte Behauptung ("die
Abweichung hat in dieser Datei also keinen Fall") ist entfernt -- nachgewiesen nicht ueber
eine Textsuche, sondern am **Aenderungsdiff auf den Pfad** (`git diff adfdd37^ adfdd37 --
parameter.toml`): genau ein Hunk, die sechs Zeilen des alten Satzes fallen weg.

**(a) Gegen die Bildungsregelzeile in `daten/adressen.md`.**

| gepruefte Aussage des Absatzes | Fundstelle | Ergebnis |
|---|---|---|
| `daten/adressen.md` fuehrt die Instrumentenkennung `regulierung` in seiner Bildungsregeltabelle als gebildet | Z. 525: "Instrumentenkennung der Finanzmarktregulierung \| `regulierung` \| analog zu `leitzins`, `zoll`, `haushalt`; gestützt auf `regulierung_stufen` in T27" -- kein woertlicher Beleg | stimmt |
| Die Tabelle ist die der erfundenen Bestandteile | Z. 515 leitet sie ein: "**Markiert ist alles, wo ein Bestandteil neu erfunden ist.** Die Bildungsregeln, damit der Prüfer sie einzeln nachrechnen kann"; Kopf Z. 518 | stimmt |
| Nr. 37, 81, 125, 169 sind `land.<L>.instrument.regulierung.stand` und tragen eine Marke | Z. 79, 123, 167, 211 -- alle vier `...stand`*, Herkunft je `Parameter(regulierung_start*)`, K 10 | stimmt |
| als **einzige** der vier Instrumentenadressen | Gegenprobe ueber alle sechzehn `instrument.<i>.stand`-Zeilen: `leitzins` (25, 69, 113, 157), `zoll` (29, 73, 117, 161), `haushalt` (33, 77, 121, 165) zwoelfmal ohne Marke, Herkunft je `Datenanker(9/13/12)`, K 3 | stimmt |

Neu gegenueber der ersten Runde, und der staerkere Beleg: `adressen.md` nennt diesen Fall
in seiner **Spaltenlegende selbst** (Z. 29) -- "Ist der eingesetzte Bestandteil selbst neu,
trägt auch die Geschwisteradresse eine Marke -- so bei `restwelt.` vor einem Sektorpfad
(Nr. 180 ...) und **beim Instrument `regulierung` (Nr. 37, gebildet aus
`land.BR.instrument.zoll.stand`)**". Die Zuschreibung der Marke an die Instrumentenkennung
ist damit nicht mein Schluss aus der Gegenprobe, sondern die ausdrueckliche Lesart des
Adressverzeichnisses. Die Legende kennt neben dem erfundenen Bestandteil noch einen
zweiten Ast ("eine Zusammensetzung von Bestandteilen, die in keinem Dokument gemeinsam
vorkommt") -- dass hier der erste greift, ist damit belegt und nicht bloss der
naheliegendere von zweien.

Gegenprobe in `specs/`: eine Suche nach `instrument\.regulierung` und `\[regulierung\]`
ueber `specs/0016-.../` findet **null** Treffer, waehrend `land.BR.instrument.zoll.stand`
und das Leitzins- und das Haushaltspaar dort stehen. Die Asymmetrie ist belegt.

**(b) Gegen den Tabellenkopf `[instrument.regulierung]`** (`parameter.toml` Z. 921-938).
Er sagt "Alle drei Werte legt T51 fest, keiner ist kalibrierbar" und fuehrt `schrittweite`,
`instrument_min`, `instrument_max` einzeln mit ihrer T51-Herleitung auf. Kein Satz des
Absatzes widerspricht ihm. Die Aussage "Woertlich belegt sind alle zwoelf" ist als Zitat
aus BEFUNDE Punkt 1 gekennzeichnet und stimmt woertlich (Z. 952-953: "schrittweite /
instrument_min / instrument_max in den vier Instrumententabellen").

**Die Probe, die die erste Runde nicht gemacht hat -- die Zerlegung ueber alle zwoelf statt
ueber die drei.** Der Absatz behauptet "an den neun Schluesseln ... keine Marke" *und*
"unter `[instrument.regulierung]` unmarkiert". Ich habe die Markenliste der ganzen Datei
aus dem Bestand gezogen (Muster: Schluesselname in Codeticks, danach `*`) und gegen die
zwoelf Schluesselzeilen gelegt, die ich mit ihrer jeweiligen Tabelle aufgezaehlt habe:
`leitzins` Z. 877-879, `zoll` Z. 900-902, `haushalt` Z. 917-919, `regulierung`
Z. 940-942 -- dreimal drei plus drei. **Keiner der zwoelf Namen kommt in der Markenliste
vor.** Damit ist nicht nur die Zuordnung neun/drei geprueft, sondern die Aussage ueber alle
zwoelf.

**Erfuellt.**

## Bedingung 2 -- der Instrumentenindex bleibt benannt

Der Diff-Hunk setzt erst innerhalb von Z. 182 an ("An den neun"); die Saetze davor sind
unberuehrt. Dort steht unveraendert (Z. 176-182): "Von den drei Indexarten [...] kommt in
dieser Datei genau eine vor: der Instrumentenindex der vier Tabellen
`[instrument.leitzins]`, `[instrument.zoll]`, `[instrument.haushalt]` und
`[instrument.regulierung]`". Abnahme 1 von 0042 gilt weiter.

Kein Satz des neuen Textes laesst folgern, eine der 25 Marken sei zu aendern; er sagt das
Gegenteil ("nach ihr bleiben `schrittweite`, `instrument_min` und `instrument_max` unter
`[instrument.regulierung]` unmarkiert"), und die Markenliste ist gegenueber `adfdd37^`
zeichengleich (siehe Bedingung 3).

**Erfuellt.**

## Bedingung 3 -- sonst hat sich nichts geaendert

Der Nachweis ist wie verlangt an der Datei gefuehrt. `git diff --stat` kommt darin nicht
vor; wo ich den Diff benutze, ist er **auf den Pfad eingeschraenkt**, und die im Baum
liegende Fassung ist ueber den Blob-Hash als genau die des Pakets ausgewiesen -- fremde
Arbeit im selben Commit kann das Ergebnis damit nicht faerben.

| Probe | Vorgehen | Ergebnis |
|---|---|---|
| Selbstprobe 1 | `^[a-z_0-9]* *=.*PLATZHALTER` auf der Fassung im Baum | **46** |
| Selbstprobe 2 | `^[a-z_0-9]* *=.*FEST \(T51\)` | **4** |
| Selbstprobe 3 | `^[a-z_0-9]+ *=` | **50** |
| dieselben drei auf `adfdd37^` | zum Vergleich | **46 / 4 / 50** -- unveraendert |
| Bestandsprobe zu 3 | `tomllib.loads`, Blaetter im Wertebaum gezaehlt | **50** -- aus dem Bestand, nicht aus dem Zeilenmuster |
| Werte unveraendert | `tomllib` auf beide Fassungen, `alt == neu` | **True** |
| 25 Sternmarken an denselben Namen | Markenlisten beider Fassungen in Reihenfolge verglichen | **identisch**; 26 Treffer, 25 verschiedene Namen (`regulierung_start` steht zweimal) |
| Art der Aenderung | alle 21 geaenderten Zeilen (10 minus, 11 plus) darauf geprueft, ob sie mit `#` beginnen | **alle** -- keine Schluessel-, Tabellen- oder Leerzeile beruehrt |
| erster Satz des Absatzes | Z. 169-171, ausserhalb des Hunks | unveraendert |
| `BEFUNDE` unangetastet | Zeichenkette ab `# BEFUNDE` bis Dateiende in beiden Fassungen verglichen | **bitgleich** -- kein Zeilennummernargument noetig |

Zur TOML-Gueltigkeit: Das Paket verbietet die Behauptung, ein Parser sei gelaufen, wenn er
es nicht ist. **In diesem Lauf lief einer** (`python3 - <<'PY'` mit `tomllib`; `python3 -c`
wird in dieser Umgebung regelmaessig abgelehnt, die Heredoc-Form nicht). Die Datei parst in
beiden Fassungen. Das ist eine Zugabe, keine Bedingung.

**Erfuellt.**

## Wonach ich ausserdem gesucht habe, ohne fuendig zu werden

- **Dieselbe Krankheit daneben.** Nach jedem Ersetzungspaket suche ich das beanstandete
  Muster -- eine Begruendung, die ihren eigenen Ausnahmefall wegdefiniert -- ueber die
  ganze Datei statt nur im Absatz der Bedingung. Suchmuster
  `einzig|vollstaendig|ausnahmslos|abschliessend|in keinem|kein(en) Fall|kein Schluessel|niemals`,
  23 Treffer, alle gelesen. Zwei kamen naeher heran, beide tragen nicht: Z. 857
  ("`instrument_min` traegt die einzige Schranke des Modells, an der ein Kurs unendlich
  wird") deckt sich mit Z. 293, die denselben Sachverhalt an der anderen Stelle nennt --
  zwei Fundstellen, ein Sachverhalt, kein Widerspruch; Z. 583 ("weder spiel.md noch
  technik.md nennt eine einzige davon beim Namen") ist im selben Absatz als Schwaeche der
  Datei ausgewiesen und als Befund vermerkt. Der Verdacht der ersten Runde, Z. 296-298, ist
  geheilt ("Es ist nicht die einzige Kopplung der Datei").
- **Anspruchskollision auf der Datei.** Alle Pakete unter `aufgaben/` mit `parameter.toml`
  in `dateien` und Status `offen`, `gebaut` oder `vorschlag` aufgelistet: **genau dieses**.
  Kein zweiter Bauagent haelt die Datei; die Ueberschneidung, die bei 0047/0049 zugebissen
  hat, liegt hier nicht vor.
- **Lizenz und Namensnennung.** Z. 220-223 sagt, die Datei trage keinen Datenanker und
  enthalte keine Zahl aus einer externen Quelle. Alle 50 Werte sind `PLATZHALTER` (46) oder
  `FEST (T51)` (4) -- 46 + 4 = 50 deckt die Schluesselzeilen vollstaendig ab, es bleibt
  also keine Zeile mit einem Quellenwert uebrig. Die Quellennennungen in den vier
  Instrumentenkoepfen (IWF IFS, IWF WEO, WDI aus WITS, EZB-Einlagesatz) beschreiben den
  Datenanker des Instruments **im Jahrgang**, nicht eine Zahl dieser Datei. Die
  Namensnennungspflicht liegt beim Manifest (T23). Kein Befund.

## Was ausdruecklich kein Befund ist

- **BEFUNDE Punkt 1.** Vom Paket ausgenommen, von mir nicht angefasst. Vermerkt sei nur,
  was **keinen** Ruecklauf traegt: T51 nennt in seiner Zeile zur Finanzmarktregulierung
  weder `schrittweite` noch `instrument_min`/`instrument_max`, sondern "1 Stufe" und
  "`0 ... regulierung_stufen`". Die **Namen** stehen dennoch woertlich in `specs/`
  (`technik.md` Z. 1490: "`schrittweite[i]`, `instrument_min[i]`, `instrument_max[i]`").
  Die Regel dieser Datei prueft den Namen; Punkt 1 ist richtig.
- **Der Doppelherr `instrument_max` = `regulierung_stufen`** (Z. 929-936). Vom Bauagenten
  als Befund mit Auflage an das einlesende Paket vermerkt, aus `specs/` erzeugt und hier
  nicht aufloesbar. Ausserhalb dieses Pakets.
- **Formulierung.** "als einzige der vier Instrumentenadressen" laesst sich beim ersten
  Lesen auf die unmittelbar davor stehenden vier Nummern beziehen. Gemeint und am Satzbau
  erkennbar sind die vier **Instrumente**. Der Satz ist damit nicht falsch, und wo `specs/`
  schweigt, ist die Formulierung Sache des Bauagenten.

## Kein Vorschlag -- aber eine Meldung an den Projektmanager

Ich lege kein Arbeitspaket an. Es gibt nichts zu bauen: Die Datei erfuellt alle drei
Bedingungen, und die beiden Stellen, die dafuer in Frage kaemen, sind Formulierung
beziehungsweise richtig.

**Was stattdessen gemeldet gehoert, weil es keine Datei betrifft, sondern den Ablauf:**
Dieses Paket hat heute ein zweites vollstaendiges Urteil bekommen, obwohl seit dem ersten
kein Byte an `parameter.toml` geaendert wurde. Ursache ist nicht der Bauagent, sondern der
Zustand: Das Paket steht weiter auf `gebaut`, weil das erste Urteil noch nicht nachgezogen
ist, und die Reviewstufe waehlt aus `gebaut`. Ein Paket, dessen Datei seit dem letzten
Urteil unveraendert ist, kann kein anderes Urteil erzeugen -- der Lauf kostet ein volles
Kontingent und liefert bestenfalls dasselbe Ergebnis. Das ist ein Fall der Familie "eine
Regel greift an einer Stelle, die der Ablauf nicht so erreicht": Die Ordnung nach der Zahl
der bisherigen Urteile verhindert das Verhungern neuer Pakete, aber nicht die
Wiedervorlage einer unveraenderten Fassung. Die Entscheidung liegt beim Projektmanager und
beim Runner, nicht bei mir; ich nenne nur die pruefbare Bedingung, an der es haengt:
**Blob-Hash der `dateien` gleich dem Stand des letzten Urteils.**
