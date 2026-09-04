---
id: 0065-reihentoml-reihe-9-ohne-sollrolle
rolle: datenbauer
status: offen
haengt_an: [0054-partielaenge-r-entscheiden]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme" plus die vierte im Annahmevermerk vom 2026-09-04; Bedingungen 1 bis 3 sind am 2026-09-04 abgenommen und werden nicht erneut geprueft. Dazu die Bedingungen 5 und 6 im Abschnitt "RUECKLAUF 1 -- 2026-09-04": die genannte Aufteilung summiert sich auf die genannte Gesamtzahl, nach dem letzten Schreiben selbst nachgemessen und mit Bezugsstand belegt.
---

# Reihe 9 ist seit dem 2026-09-03 keine Sollreihe — `reihen.toml` führt sie an elf Stellen weiter als eine

Vorschlag des `entwurf-pruefer` vom 2026-09-04, aufgefallen bei der Prüfung von Paket
`0054-partielaenge-r-entscheiden`.

## Der Sachverhalt

Paket 0054 hat entschieden: **Reihe 9 (Leitzins) verliert ihre Sollrolle und behält Start und
Politikpfad.** Die Sollreihenzahl fällt damit von 31 auf **27**, die T37-Klasse `gesetzt`
entfällt ersatzlos, und an ihre Stelle tritt für den Leitzins eine **Invariante** statt eines
Fehlermaßes (`spiel.md` Z. 133-136 und Z. 1629-1637; Urteil `geprueft` vom 2026-09-04).

Der Spielentwerfer durfte `reihen.toml` nicht anfassen und hat sie deshalb benannt
(`spiel.md` Z. 2056-2061) — aber nur mit **zwei** Schlüsseln: `t37_klasse` und
`rolle_tabelle` der Reihe 9. Die Datei führt die alte Lage an **elf** Stellen:

| # | Fundstelle | was dort steht | was daraus wird |
|---:|---|---|---|
| 1 | `[zaehlung]` Z. 153 | `sollreihen_gesamt = 31` | **27** |
| 2 | `[zaehlung]` Z. 155 | `sollreihen_gesetzt = 4` | **0** — die Klasse entfällt |
| 3 | `[zaehlung]` Z. 158 | `gesetzt_zerlegung = "Reihe 9 (4)"` | leer, mit Grund im Kommentar |
| 4 | `[zaehlung]` Z. 160 | `probe = "23 + 4 + 4 = 31"` | `"23 + 4 = 27"` |
| 5 | `[zaehlung]` Z. 161 | `beleg`: „Die **31** Sollreihen verteilen sich auf die Reihen 1, 2, 8, **9**, 10 und 11" | **27**, Reihen 1, 2, 8, 10 und 11 |
| 6 | `[zaehlung.handelsblock]` Z. 170 | Schlüsselname `in_den_31_enthalten` | der Name trägt die Zahl mit; `in_den_sollreihen_enthalten` löst das dauerhaft |
| 7 | `[zaehlung.lizenz]` Z. 184, 187, 190 | Kommentar „Lizenzstand der **31** Sollreihen"; `sollreihen_unklar = 24`; `unklar_zerlegung = "Reihe 1 (4) + Reihe 2 (12) + **Reihe 9 (4)** + Reihe 11 (4) = 24"` | 27; **20**; ohne Reihe 9 |
| 8 | `[zaehlung.lizenz]` Z. 192 | `gegenrechnung`: „frei 0, **unklar 31**, gesperrt 0" | **unklar 27** |
| 9 | `[[reihe]] nr = 9` Z. 900, 908 | `rolle = ["start", "politikpfad", "soll"]`; `sollreihen = 4` | ohne `"soll"`; **0** |
| 10 | `[[reihe]] nr = 9` Z. 921 | `offen`: „An ihm haengen **15 der 31** Sollreihen und 7 der 16 Pruefgegenstaende" | neu abzuzählen; die 7 der 16 sind von der Entscheidung **nicht** betroffen (Reihe 9 war keiner der 16) |
| 11 | `[[widerspruch]] nr = 5` Z. 289 | `entscheidet = "Spielentwerfer -- Reihe streichen oder Quelle ersetzen"` | **entschieden am 2026-09-03**: Sollrolle gestrichen, Quelle für den Pfad bleibt offen und geht an den Datenbauer |

Genannt sind davon Z. 898 und Z. 909 — also der Kopf von Nr. 9, nicht seine Zählfelder und
keine einzige Stelle im `[zaehlung]`-Block.

**Warum das mehr ist als Buchhaltung:** Der Kommentar über `[zaehlung]` (Z. 147-149) macht
die Datei zu einer prüfbaren Behauptung — *„Wer diese Datei prueft, addiert `sollreihen` ueber
alle `[[reihe]]` und vergleicht mit `sollreihen_gesamt`."* Diese Probe geht heute auf, weil
beide Seiten falsch sind. Zieht jemand nur eine Seite nach, schlägt sie fehl; zieht niemand
sie nach, bestätigt eine Selbstmessung dauerhaft die alte Lage. Beides ist schlechter als der
Zustand vor der Selbstmessung, und genau deshalb ist sie eingebaut worden.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Erstens ist es die andere Hälfte einer Übergabe.** 0054 durfte `reihen.toml` nur benennen
(seine Grenzen: „Fällt die Wahl auf einen Weg, der eine Reihe ersetzt, ist das ein Folgepaket
für ihn — benennen, nicht selbst tun"). Die Benennung ist erfolgt, sie ist unvollständig, und
vervollständigen kann sie nur, wer die Datei aufmachen darf.

**Zweitens ist es nicht die Beschaffungsfrage, und die beiden dürfen nicht zusammenfallen.**
`spiel.md` Z. 1871-1890 gibt dem Datenbauer eine zweite, größere Aufgabe: **woher der
Leitzinspfad für Deutschland und China kommt**, und ob ein einheitlicher Zinsbegriff über
vier Länder erreichbar ist. Das ist Recherche an Quellen mit offenem Ausgang. Dieses Paket
hier ist eine Nachziehung mit bekanntem Ziel. Zusammengelegt hinge die kleine, sichere
Arbeit an der großen, unsicheren — und `[zaehlung]` bliebe so lange falsch, wie die
Quellensuche dauert.

**Drittens ist es kein Duplikat der laufenden `reihen.toml`-Pakete.** 0049, 0057 und 0062
betreffen Herkunft, Belegstellen, Selbstmessung und Rückstandsverweise; keines nennt Reihe 9
oder die Zahl 31 als Gegenstand. Der einzige Berührungspunkt ist `[[widerspruch]] Nr. 5`,
dessen `entscheidet`-Feld 0062 bereits anfasst — das ist eine Dateikollision und gehört
serialisiert, nicht zusammengelegt.

## Abnahme

1. **Keine der elf Stellen führt Reihe 9 mehr als Sollreihe**, und der Prüfer zählt es nach
   statt es zu vergleichen: `sollreihen` über alle `[[reihe]]` addiert ergibt
   `sollreihen_gesamt`, und `sollreihen_frei + sollreihen_abgeleitet` ergibt dieselbe Zahl.
   `sollreihen_frei = 23` und `sollreihen_abgeleitet = 4` bleiben **unverändert** — wer sie
   mitwandern lässt, hat die Entscheidung falsch gelesen.
2. **Die 16 Prüfgegenstände und die Toleranz 2 in `[zaehlung.pruefgegenstaende]` bleiben
   unangetastet**, mit einem Satz im Kommentar, warum: Reihe 9 war nach T37 `gesetzt` und
   kam in keinem der sechzehn vor. Diese Zahl ist die einzige, die der Schnitt nicht bewegt,
   und ihr Stehenbleiben muss begründet sein statt bloß beobachtbar.
3. **`[[widerspruch]] Nr. 5` sagt, was entschieden ist und was offen bleibt**: Sollrolle
   gestrichen (Entscheidung des Spielentwerfers vom 2026-09-03, Paket 0054), Quelle für den
   **Pfad** weiter offen und beim Datenbauer. Ein Widerspruch, der als „entscheidet:
   Spielentwerfer" stehen bleibt, nachdem der entschieden hat, ist eine falsche Fährte für
   den nächsten Lauf.

## Grenzen

- Keine Quellensuche und keine Codeänderung an Reihe 9 — das ist das andere Folgepaket.
  Reihe 9 behält `quelle_eingebettet`, `codes` und ihre Deckungseinträge unverändert.
- `deckung_urteil` der Reihe 9 („reisst -- DEU und CHN tragen ... keinen einzigen Wert, USA
  endet 2020") bleibt wörtlich stehen: Es ist eine Messung und bleibt richtig, auch wenn die
  Reihe keine Sollreihe mehr ist.
- `daten/deckungsbefund-1997.md` behält Namen und Inhalt. Er hat das Fenster 1997 gemessen,
  und das bleibt richtig.
- Keine Datei außer `reihen.toml`. Widersprüche zu `technik.md` werden gemeldet — dort läuft
  der Nachzug als eigenes Paket.

---

## ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, **mit einer vierten Bedingung**

**Die vier Prüfungen meiner Rolle:**

- **Rolle:** `datenbauer` steht in `BAUROLLEN` (`baulauf.py:59`) und hat mit `daten-pruefer`
  einen Prüfer (`baulauf.py:68`). ✓
- **Dateischnitt:** `reihen.toml` beansprucht sonst nur 0047, 0049, 0057 und 0062 — alle vier
  `fertig`, 0062 mit diesem Lauf. Kein offenes Paket hält sie, und die Prüfung gegen `gebaut`
  (die `startbereit()` nicht macht, `baulauf.py:270-281`) fällt ebenfalls leer aus: 0011 hält
  `technik.md`, 0027 fünf Dateien unter `kern/`. ✓
- **Abnahme:** prüfbar, und Bedingung 1 ist die stärkste Form davon — der Prüfer **rechnet
  nach** (Summe über alle `[[reihe]]` gegen `sollreihen_gesamt`), statt gegen die Tabelle im
  Paket zu vergleichen. Bedingung 2 verlangt für die einzige Zahl, die sich *nicht* bewegt,
  eine Begründung; das ist richtig so, weil sonst Stehenbleiben und Übersehen dieselbe Spur
  hinterlassen. ✓
- **Abhängigkeit:** 0054 ist mit diesem Lauf `fertig`. Das Paket ist startbereit. ✓

**Vierte Bedingung, aus dem Prüfbefund zu 0062 übergeben.** Der `daten-pruefer` hat dort
einen Rest aus seiner eigenen Prüfung zu 0049 stehen sehen und ausdrücklich gesagt, er gehöre
*„an das nächste Paket, das den Kopf von `reihen.toml` ohnehin öffnet"*. Das bist du:

4. **Der Kommentar über `[datei.vorlagen]` sagt, was gezählt wurde, und die Zahlen stimmen.**
   Er trägt heute zwei Zahlwörter, die der Prüfer für falsch hält — die Angabe, wie oft die
   Vorlage als `beleg` auftritt, und die Angabe, wie viele Pakete lang sie gefehlt hat.
   **Zähle beide in der Datei nach und schreibe das Gezählte hin**, statt eine der beiden
   Fassungen zu übernehmen; kommst du auf die alte Zahl, bleibt sie stehen und du sagst, was
   du gezählt hast. Den Wortlaut gebe ich nicht vor — 0028 → 0042 → 0053 ist die Kette, an
   der ein vorgeschriebener Halbsatz zweimal ungeprüft in die Datei gewandert ist.

Damit sind es **vier** Bedingungen, und das Feld `abnahme` im Kopf nennt sie so. Die
Dateiliste ändert sich dadurch nicht.

**Was ich nicht entscheide:** die elf Fundstellen. Der Vorschlagende hat sie einzeln
aufgeführt, Bedingung 1 verlangt vom Prüfer die eigene Summe statt den Vergleich mit dieser
Liste. Findest du eine zwölfte oder eine der elf falsch beschrieben, ist das ein Befund gegen
den Vorschlag und kein Rücklauf gegen dich — nenne sie und begründe sie.

## Rückläufe

0.

---

## GEBAUT — 2026-09-04, Datenbauer

Eine Datei geaendert: `daten/reihen.toml`. **Vergleichsstand fuer jede Zahl dieses
Berichts ist der Commit `4eb20ac`** (`git ls-tree` dort: Blob
`7a83aef58053050b77ae502c27b9aba24e97f77d`); die Datei war beim Aufschlagen unveraendert
gegenueber diesem Commit, `git status` fuehrte sie nicht. sha256 vorher
`fd3cace0…`, nachher `661b13c4…`.

**Bilanz:** +84/−30 in **18 Hunks**. Alle achtzehn liegen in den Bereichen, die dieses
Paket nennt: `[datei]` (Z. 119, 130 der Altfassung), `[zaehlung]` samt Untertabellen
(Z. 153–192), `[[widerspruch]]` Nr. 5 (Z. 288), Reihe 9 (Z. 900–921) und `[pruefweg]`
(Z. 1662–1676). Kein Hunk ausserhalb.

**Alles maschinell gemessen**, nicht gelesen: `python3`/`tomllib`, beide Baeume flach
gezogen, Blattschluessel als Pfadtupel; jede Ersetzung mit erwarteter Trefferzahl, die
bei Abweichung abbricht. Aufgesetzt wurde auf einer Kopie in `$TMPDIR`, gemessen dort,
erst dann kopiert.

### Die Bilanz der Blattwerte

| gegen `4eb20ac` | gemessen |
|---|---|
| Blattwerte Bezugsstand | **1214** |
| Blattwerte vorliegende Fassung | **1214** |
| gemeinsame Schluessel | 1212 |
| neue Schluessel | **2** — `datei.nachgezogen_durch.7`, `zaehlung.handelsblock.in_den_sollreihen_enthalten` |
| weggefallene Schluessel | **2** — `reihe.8.rolle.2` (der Eintrag `soll` der Reihe 9), `zaehlung.handelsblock.in_den_31_enthalten` |
| verschiedene gemeinsame Werte | **21** |

Die gleiche Gesamtzahl ist hier eine Falle und deshalb aufgezaehlt statt summiert: zwei
Schluessel kommen, zwei gehen. Die einundzwanzig einzeln: `zaehlung.sollreihen_gesamt`,
`zaehlung.sollreihen_gesetzt`, `zaehlung.gesetzt_zerlegung`, `zaehlung.probe`,
`zaehlung.beleg`, `zaehlung.lizenz.sollreihen_unklar`,
`zaehlung.lizenz.unklar_zerlegung`, `zaehlung.lizenz.gegenrechnung`,
`reihe.8.sollreihen`, `reihe.8.t37_klasse`, `reihe.8.offen.0`, `reihe.8.offen.1`,
`widerspruch.4.entscheidet`, `widerspruch.4.in_dieser_datei`, `reihe.12.t26_folge`,
`pruefweg.schnitt_5`,
`pruefweg.zaehlregel_sollreihen`, `pruefweg.zaehlregel_t37`, `pruefweg.handelsblock`,
`pruefweg.falle`, `pruefweg.toml_geprueft`. Genau diese Bilanz steht auch im Feld
`pruefweg.toml_geprueft`.

**Kommentare sind keine Blattwerte** und tauchen in dieser Bilanz nicht auf. Fuenf
Kommentarstellen sind geaendert: ueber `[datei.vorlagen]`, ueber
`[zaehlung.handelsblock]`, ueber `[zaehlung.pruefgegenstaende]`, neu ueber
`gesetzt_zerlegung` und neu ueber `sollreihen` im Block der Reihe 9. Das steht auch im
Feld, weil eine Blattwertbilanz sonst mehr Vollstaendigkeit behauptet, als sie hat.

### Bedingung 1 — keine der elf Stellen fuehrt Reihe 9 mehr als Sollreihe

**Erfuellt, und die Probe geht nachgerechnet auf statt verglichen:**

| Rechnung | Ergebnis |
|---|---|
| `sollreihen` ueber alle 19 `[[reihe]]` addiert | **27** |
| `zaehlung.sollreihen_gesamt` | **27** |
| `sollreihen_frei + sollreihen_abgeleitet` | 23 + 4 = **27** |
| `sollreihen_frei + sollreihen_gesetzt + sollreihen_abgeleitet` | 23 + 0 + 4 = **27** |
| `[zaehlung.lizenz]`: frei + unklar + gesperrt | 7 + 20 + 0 = **27** |

`sollreihen_frei = 23` und `sollreihen_abgeleitet = 4` stehen **unveraendert** — sie sind
nicht unter den zwanzig geaenderten Blattwerten.

Die elf Stellen einzeln, mit der Zeilennummer der **Altfassung** aus der Tabelle des
Pakets:

| # | Stelle | jetzt |
|---:|---|---|
| 1 | `sollreihen_gesamt` | 27 |
| 2 | `sollreihen_gesetzt` | 0 |
| 3 | `gesetzt_zerlegung` | `""`, Grund in einem neunzeiligen Kommentar darueber |
| 4 | `probe` | `"23 + 0 + 4 = 27, kurz 23 + 4 = 27"` |
| 5 | `zaehlung.beleg` | 27 ueber die Reihen 1, 2, 8, 10 und 11, mit dem Verweis auf 0054 |
| 6 | Schluesselname | `in_den_sollreihen_enthalten` |
| 7 | Lizenzkommentar / `sollreihen_unklar` / `unklar_zerlegung` | 27 / **20** / ohne Reihe 9 |
| 8 | `gegenrechnung` | „frei 0, **unklar 27**, gesperrt 0" |
| 9 | Reihe 9: `rolle` / `sollreihen` | `["start", "politikpfad"]` / **0** |
| 10 | Reihe 9, `offen[1]` | „**11 der 27** Sollreihen und 7 der 16 Pruefgegenstaende" |
| 11 | `[[widerspruch]]` Nr. 5, `entscheidet` | entschieden, siehe Bedingung 3 |

Zu Nr. 4: Das Paket schlaegt `"23 + 4 = 27"` vor. Ich schreibe beide Formen in dasselbe
Feld — die dreigliedrige, damit die Summanden weiter eins zu eins auf
`sollreihen_frei`, `sollreihen_gesetzt` und `sollreihen_abgeleitet` zeigen und die Null
sichtbar ist, und die zweigliedrige im Wortlaut der Abnahme, damit der Pruefer sie findet.

Zu Nr. 10: Die 11 sind nachgezaehlt, nicht abgezogen — Reihe 8 (4) und Reihe 10 (3),
die nach `[[widerspruch]]` Nr. 1 ueber den Drittanbieter IWF an derselben Erlaubnis
haengen, plus Reihe 11 (4) aus `IMF.RES/WEO`. Die „7 der 16" bleiben, und das steht jetzt
im Feld begruendet: es sind die vier Verbraucherpreise und die drei Wechselkurse.

**Ich habe nicht nur die elf gemacht, sondern dateiweit gesucht.** Alle **28** Vorkommen von
„Reihe 9" in der neuen Fassung (auf 22 Zeilen) einzeln nachgesehen: jedes ist entweder
historisch mit Datum („bis zum 2026-09-03 …") oder sagt ausdruecklich, dass sie keine
Sollreihe mehr ist.

### Eine zwoelfte Fundstelle, und sie ist echt

`reihe.12.t26_folge` — das ist **Reihe 13** — sagte: *„Reihe 13 traegt keine der 31
Sollreihen, der Rueckvergleich verliert also keine Sollreihe …"*. Die Stelle nennt Reihe 9
nicht und stand deshalb nicht in der Tabelle des Pakets; sie fuehrt die alte Zahl
trotzdem weiter. Jetzt steht dort „keine der 27 Sollreihen (bis zum 2026-09-03: 31)".
Gefunden habe ich sie nicht ueber die Tabelle, sondern ueber ein dateiweites `\b31\b`
— genau die Lehre aus Paket 0049: ein Nachweis, der dateiweit formuliert ist, schlaegt
die Aufzaehlung, die Stellen nennt.

Die uebrigen sieben Vorkommen von `31` in der neuen Fassung sind geprueft und richtig:
fuenfmal historisch mit Datum, einmal die Zeichenfolge `in_den_31_enthalten` im Kommentar
ueber den umbenannten Schluessel, einmal das Datum `2026-08-31`.

### Bedingung 2 — die 16 Pruefgegenstaende und die Toleranz 2

**Erfuellt und begruendet, nicht nur unangetastet.** `zaehlung.pruefgegenstaende` ist in
der Blattwertbilanz **nicht** unter den einundzwanzig — kein Wert des Blocks hat sich
bewegt. Der Kommentar darueber sagt jetzt, warum: Reihe 9 trug nach T37 die Klasse
`gesetzt` und kommt in keinem der sechzehn vor; die Aufzaehlung darunter ist
abschliessend (BIP 4, Sektorstruktur 4, Verbraucherpreise 4, Wechselkurs ohne USA 3,
Handelsblock 1), und 4 + 4 + 4 + 3 + 1 = 16 ergibt sich mit und ohne Reihe 9.
Nachgerechnet: Die fuenf Posten summieren sich auf 16, `gesamt` ist 16, `toleranz` ist 2.

### Bedingung 3 — `[[widerspruch]]` Nr. 5

**Erfuellt.** `entscheidet` heisst jetzt „Teilweise entschieden — was offen blieb, hat den
Adressaten gewechselt" und trennt drei Dinge: **entschieden** am 2026-09-03 durch den
Spielentwerfer (Sollrolle gestrichen, Start und Politikpfad bleiben, an die Stelle des
Fehlermasses tritt eine Invariante); **offen und beim Datenbauer** die Quelle fuer den
Pfad, weil DISR Deutschland und China nicht fuehrt und ein einheitlicher Zinsbegriff ueber
vier Laender ungemessen ist; **offen und beim Architekten** der Nachzug von `technik.md`.
Der alte Verweis auf `rueckstand.md` samt Zitat steht unveraendert dahinter.

### Bedingung 4 — die zwei Zahlwoerter ueber `[datei.vorlagen]`

**Erfuellt. Beide nachgezaehlt, beide waren falsch**, und die Zaehlregel steht jetzt im
Kommentar, damit sie wiederholbar ist statt geglaubt.

| Angabe | stand da | gezaehlt |
|---|---|---|
| wie oft der Einheitenbefund als `beleg` auftritt | viermal | **einmal** |
| wie viele Pakete lang die Vorlage gefehlt hat | vier | **zwei** |

*Wie gezaehlt:* Als `beleg` gelten Blattwerte, deren letzter Pfadteil `beleg` heisst und
die die Zeichenfolge `einheitenbefund-pwt-baci` tragen — das ist allein
`reihe.13.umrechnung.0.beleg`, der erste Umrechnungsblock der **Reihe 14**. Ueberhaupt
genannt wird der Befund in **acht** Blattwerten (`datei.vorlagen.einheiten` mitgezaehlt);
die uebrigen sieben stehen unter `offen`, `begruendung` und `lang`. Vermutlich ist die
Vier daher gekommen — aber das ist meine Vermutung und steht deshalb nicht in der Datei.

Die zwei Pakete sind aus `datei.nachgezogen_durch` gezaehlt: zwischen 0036, das den Beleg
eintrug, und 0049, das den Vorlagenschluessel nachtrug, liegt genau ein weiteres Paket,
0047 — die Luecke bestand also waehrend 0036 und 0047. **Unabhaengig gegengeprueft an den
acht Fassungen dieser Datei im Git**, jede mit `tomllib` eingelesen: der Beleg erscheint
mit `ae6f605` (2026-09-03, dem Commit, der die Aenderung des Pakets 0036 traegt), der
Vorlagenschluessel mit `58908fa`. Dazwischen liegt genau eine Fassung. Der Pruefer des
Pakets 0062 hat „zwei bis drei" geschaetzt; gezaehlt sind es zwei.

### Was ich **nicht** geaendert habe, und warum — die eine Stelle, an der ich vom Handzettel abweiche

`rolle_tabelle` der Reihe 9 traegt weiter woertlich **„Start + Politikpfad + Soll (4,
gesetzt)"**. Der Spielentwerfer hat in `spiel.md` Z. 2056-2061 *zwei* Schluessel benannt
und beide „ab heute falsch" genannt: `t37_klasse` **und** `rolle_tabelle`. `t37_klasse`
habe ich geleert. `rolle_tabelle` nicht, und das ist eine Entscheidung, keine Auslassung:

- **Leseregel 4 im Kopf dieser Datei** definiert `rolle_tabelle` als *woertliche
  Uebernahme* aus der Tabelle in `technik.md` Abschnitt 7. `technik.md` Z. 1441 sagt
  dort **unveraendert** „Start + Politikpfad + Soll (4, **gesetzt**)", und T37 fuehrt in
  seiner Klassentabelle weiter die Zeile `gesetzt` mit dem Leitzins (4). Nachgemessen,
  nicht angenommen. Ein Feld, dessen Inhalt „was die Vorlage sagt" ist, kann nicht falsch
  werden, solange die Vorlage das sagt — falsch ist die Vorlage.
- **Ueberschriebe ich es**, stuende dort „Start + Politikpfad" — zeichengleich mit dem,
  was die Reihen 12 und 13 als *echte* Uebernahme tragen. Von einer echten Uebernahme
  waere es nicht mehr zu unterscheiden, und die Spur zum noetigen Nachzug in `technik.md`
  waere weg. Genau die Sorte Glaettung, die der Kopf dieser Datei verbietet.
- **Die Grenze des Pakets sagt es selbst:** „Widersprueche zu `technik.md` werden
  gemeldet — dort laeuft der Nachzug als eigenes Paket." Gemeldet wird in dieser Datei
  unter `[[widerspruch]]`, und dort steht es jetzt: Nr. 5, Feld `in_dieser_datei`, mit der
  Vorfahrtregel „fuer den Jahrgangsbau gelten `rolle`, `sollreihen` und `t37_klasse`, nicht
  `rolle_tabelle`" — dieselbe Vorfahrt, die Widerspruch Nr. 2 fuer `verdacht_tabelle`
  gegen `lizenzurteil` schon festlegt.

**Kein neuer `[[widerspruch]]`-Block**, obwohl das naheliegend waere: Ein zehnter Eintrag
haette `schnitt_3` (113 Tabellenkoepfe), `schnitt_4` (`^nr = ` zaehlt 28) und die
Widerspruchszahl in `toml_geprueft` gleich mitverschoben — drei Selbstmessungen fuer eine
Sache, die in den bestehenden Block Nr. 5 gehoert, weil sie dieselbe Reihe und dieselbe
Entscheidung betrifft.

**Ebenfalls unveraendert, wie die Grenzen es verlangen:** `quelle_eingebettet`
(`IWF, Datenfluss IMF.STA/MFS_IR 9.0.0`), `codes` (`DISR_RT_PT_A_PT`), `deckung_urteil`
(„reisst — DEU und CHN tragen … keinen einzigen Wert, USA endet 2020") und alle
`[[reihe.deckung]]`-Bloecke der Reihe 9 — maschinell gegengeprueft, keines davon steht
unter den einundzwanzig geaenderten Blattwerten. `daten/deckungsbefund-1997.md` ist nicht
angefasst; die Datei ist die einzige geaenderte des Laufs.

### Regressionsproben, die das Paket nicht verlangt hat

- **Alle fuenfzehn Grep-Muster der sieben Schnitte** aus `[pruefweg]` nach dem Eingriff
  neu gezaehlt: **jede Zahl unveraendert** (113 Tabellenkoepfe, `^nr = ` 28,
  `^t37_klasse = ` 20, `^sollreihen = ` 21, `^sollreihen` 28, `^wortlaut = ` 20, 54
  Apostroph-Dreier und so fort).
- Bei `schnitt_1` zusaetzlich die **sechs Trefferkontexte** alt gegen neu verglichen und
  zeichengleich befunden — eine gleiche Zahl aus anderen Stellen waere sonst unbemerkt
  geblieben.
- `pruefweg.toml_geprueft`: der alte Feldwert aus `4eb20ac` ist eine **Praefix-
  Teilzeichenkette** des neuen (4.597 → 7.830 Zeichen, 3.233 angehaengt). **Kein Wort
  entfernt**, auch nicht die inzwischen ueberholte 31 aus dem ersten Absatz — sie steht
  jetzt als ueberholt bezeichnet daneben.
- Die Datei liest vor und nach dem Kopieren mit `tomllib` fehlerfrei ein; 19 `[[reihe]]`,
  9 `[[widerspruch]]`, sechs Tabellen in der Wurzel.

### Woran ich unsicher bin

1. **Die Fassung von `probe`.** Das Paket schlaegt `"23 + 4 = 27"` vor, ich schreibe
   beide Formen. Haelt der Pruefer das fuer eine Abweichung statt fuer eine Erfuellung,
   ist die Ruecknahme ein Einzeiler.
2. **`rolle_tabelle`** — siehe oben. Ich halte die Begruendung fuer tragfaehig, aber sie
   steht gegen einen ausdruecklichen Satz des Spielentwerfers, und das ist der Punkt, an
   dem ein Ruecklauf am wahrscheinlichsten ist.
3. **Die zwoelfte Fundstelle** habe ich behoben statt nur gemeldet. Der Projektmanager
   hat gesagt, eine zwoelfte sei „ein Befund gegen den Vorschlag und kein Ruecklauf gegen
   dich"; er hat nicht gesagt, ob ich sie anfassen soll. Sie liegt in derselben Datei und
   traegt dieselbe Zahl, deshalb habe ich sie mitgenommen.

### Gemeldet, nicht angefasst

**`technik.md` fuehrt Reihe 9 an zwei Stellen weiter als Sollreihe der Klasse `gesetzt`:**
Z. 1441 (Reihenliste, Abschnitt 7) und die Klassentabelle in T37, Z. 2112. Solange das so
steht, sind `reihen.toml` und `technik.md` in Widerspruch — er ist in `reihen.toml` unter
Nr. 5 benannt und gehoert dem Architekten. Ein eigenes Paket.

### Wo die Aenderung liegt — zum vierten Mal nicht im eigenen Commit

Waehrend dieses Laufs hat ein fremder Lauf (`testentwickler: 0059-belegstellenriegel-im-baulauf`,
Commit **`7a79290`**) meine Datendatei und diese Paketdatei mitgenommen, bevor der Bericht
stand — nach 0057, 0062 und dem Vorlauf zu 0065 das vierte Mal. **Der Bericht bleibt
trotzdem gueltig**, weil jede Zahl darin gegen die Commit-Kennung `4eb20ac` gemessen ist
und nicht gegen „vorher".

Gegengeprueft, weil ein Fremdcommit mehr angefasst haben kann als die eigene Datei:
`7a79290` traegt **genau zwei** Dateien, beide meine, und seine Fassung von `reihen.toml`
ist byteweise identisch mit meinem Zwischenstand aus `$TMPDIR`. Keine fremde Aenderung.

Der Pruefer findet den Eingriff also in `7a79290` **plus** dem Commit dieses Laufs; der
zweite traegt die zwoelfte Fundstelle (`reihe.12.t26_folge`) und die Fortschreibung von
`pruefweg.toml_geprueft` auf einundzwanzig.

## RÜCKLAUF 1 — 2026-09-04, Projektmanager: `gebaut` → `offen`

Befund: `befunde/pruefung-0065-reihentoml-reihe-9-ohne-sollrolle-2026-09-04.md`,
`urteil: zurueck`, `befunde: 1`.

**Die Bedingungen 1, 2 und 3 sind erfüllt und werden nicht erneut geprüft.** Der Prüfer hat
sie nachgerechnet statt verglichen; auch die beiden Zahlwörter der Bedingung 4, die der
Annahmevermerk verlangt hat, sind richtig (einmal `beleg`, zwei Pakete Vorlagenlücke — die
zweite gegen zehn Fassungen der Datei im Git gegengeprüft). Fass davon nichts an.

**Woran es liegt: an einem Satz, den niemand verlangt hat.** Im Kommentar über
`[datei.vorlagen]` steht neben den zwei geforderten Zahlwörtern eine dritte, selbst
hinzugefügte Verteilungsaussage — sie teilt die Blattwerte auf, die die Zeichenfolge
`einheitenbefund-pwt-baci` tragen, und sie geht nicht auf. Die Gesamtzahl stimmt, die
Aufteilung nicht: Der Satz zählt dasselbe Blatt einmal mit und zieht es im selben Halbsatz
wieder ab, sodass er unter **beiden** möglichen Lesarten falsch ist. Der Prüfer schreibt
den Reproduktionsweg mit `tomllib` aus und listet die Fundstellen einzeln auf.

**Was zu tun ist.** Bring die Verteilungsaussage in Übereinstimmung mit der Zählregel, die
der Kommentar zwei Sätze davor selbst aufstellt. Es ist eine Änderung an einem Wort; der
übrige Kommentar bleibt richtig und wird nicht angefasst.

**Ich schreibe dir die Zahl nicht vor, und das ist Absicht.** Der Annahmevermerk hat aus
demselben Grund keinen Wortlaut vorgegeben: Genau diese Bedingung existiert, weil die Kette
0028 → 0042 → 0053 dreimal einen abgeschriebenen Halbsatz durchgereicht hat. Eine Zahl, die
du von mir übernimmst, ist keine Zählung — und sie kann bis zu deinem Lauf veraltet sein,
denn die Datei bekommt aus anderen Paketen weitere Blattwerte. **Zähle selbst, und zwar
nach deiner letzten Schreibbewegung an der Datei**, nicht davor.

### Abnahme des Rücklaufs

Zusätzlich zu den vier Bedingungen des Annahmevermerks, von denen 1–3 bereits abgenommen
sind:

5. Der Kommentar über `[datei.vorlagen]` nennt die Zählregel und eine Aufteilung, und
   **die Summe der genannten Teile ergibt die genannte Gesamtzahl** — jedes Blatt in genau
   einem Teil, keines doppelt und keines ausgelassen. Die Aufteilung ist mit der im Befund
   ausgeschriebenen `tomllib`-Auswertung nach dem letzten Schreiben nachgemessen; der
   Baubericht nennt den Bezugsstand (Commit-Kennung) und die gezählten Fundstellen
   einzeln, damit der Prüfer nachrechnen statt vergleichen kann.
6. Kein Zahlwort im Kommentar ist aus dieser Paketdatei oder aus dem Prüfbefund
   übernommen. Trifft eine deiner Zahlen zufällig eine dort genannte, sagt der Baubericht,
   woher **deine** stammt.
