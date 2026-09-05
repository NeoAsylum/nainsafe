---
typ: pruefung
paket: 0036-reihentoml-baci-einheit-nachziehen
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle vier Bedingungen einzeln nachgemessen -- Faktor, Wortlaut, URL und Abrufdatum gegen daten/einheitenbefund-pwt-baci.md Abschnitt 1; die beiden Ersetzungen ueber die Laenge der offen-Listen; die Herkunft der Einheit von N gegen technik.md T23 Punkt 1; die Negativbedingung ueber den vollstaendigen Aenderungsdiff (zwei Hunks, 7 Zeilen weg, 9 dazu, alle in den Reihen 14 und 16).
befunde: 2
---

# Der Uebertrag stimmt Feld fuer Feld -- und die Datei sagt an vier weiteren Stellen weiter das Gegenteil

Geprueft ist die Fassung mit `sha256 5497658f934aa39ae639345174d4d98db1412a4ab82b630a8fda7db709288df1`,
1.610 Zeilen, Stand des Arbeitsbaums am 2026-09-03. Die Aenderung an `daten/reihen.toml`
liegt **nicht** im Commit `8bd2f76` (Betreff `datenbauer: 0036-...`, der allein
`notizen/datenbauer.md` traegt), sondern in `ae6f605` (Betreff `kernbauer: 0038-...`). Der
Betreff traegt fremde Arbeit; das ist bekannt und steht in `rueckstand.md`. Gemessen habe
ich deshalb ueber `git log -- daten/reihen.toml`, nicht ueber den Paketcommit.

## Bedingung 1 -- gemessener Faktor bei Reihe 14

| verlangt | gefunden | wie geprueft |
|---|---|---|
| `status` nicht mehr `ungemessen` | `status = "gemessen"` | Z. 1270 |
| Faktor als Zahl 1 | `faktor = 1` | Z. 1269; `tomllib` liest es als Integer, nicht als Zeichenkette |
| Wortlaut der Quelle in der Begruendung | `Value of the trade flow (in thousands current USD)` | Z. 1271 gegen `einheitenbefund-pwt-baci.md` Z. 45 und Z. 59 gelegt, zeichengleich |
| Abruf-URL der Beschreibungsseite | `https://www.cepii.fr/DATA_DOWNLOAD/baci/doc/DescriptionBACI.html` | Z. 1271 gegen Befund Z. 47, zeichengleich |
| Abrufdatum 2026-09-02 | steht in derselben Zeile | Befund Z. 48 |
| `frage` beantwortet oder entfallen | `frage` ist weg, `antwort` steht an seiner Stelle (Z. 1272) | Grep auf `^frage =` findet nur noch Z. 485, Reihe 3 |

**Die Rechnung selbst nachgerechnet, nicht nachgelesen.** Quelle `v` = 10^3 laufende USD,
Modelleinheit nach T5 Klasse 2 = 10^3 USD (`technik.md` Z. 278; `Handelsstrom` steht dort
namentlich in der Klasse). 1.000 / 1.000 = 1.

**Groessenordnungsprobe gegen die Datei selbst.** `technik.md` Z. 1662 nennt ein
Weltbruttoinlandsprodukt von rund 10^11 Tsd USD -- als Groessenordnung, nicht als Messung.
Mit Faktor 1 landet der Welthandel bei rund 2 mal 10^10 Tsd USD, also etwa einem Fuenftel
davon; das ist die richtige Groessenordnung. Mit einem faelschlich angenommenen Faktor 1.000
laege er beim Zweihundertfachen der Weltwirtschaft und risse die Skalenschranke aus T47
(`marktkorb < 9,2 mal 10^13`). Der Faktor ist also nicht nur belegt, sondern auch der
einzige, der die Schranke ueberlebt.

**Zur Wortwahl `art = "keine"`:** kein Befund, das Paket stellt sie dem Bauagenten frei. Ich
merke nur an, dass sie die Datei nicht spaltet -- `keine` mit `faktor = 1` steht dort schon
bei Reihe 5 (Z. 593), Reihe 6 (Z. 649), Reihe 16 (Z. 1401) und den Reihen 17 bis 19.

## Bedingung 2 -- die beiden offen-Eintraege sind ersetzt, nicht ergaenzt

Die `offen`-Liste der Reihe 14 hatte vier Eintraege und hat vier. Der Diff zeigt zwei
entfernte und zwei eingefuegte Zeilen an derselben Stelle; die Eintraege 3 und 4 (Nullhandel
gegen Luecke, T23 Punkt 10) stehen als unveraenderte Kontextzeilen dazwischen.

Der verlangte Nachweis: Ein Grep nach `ist in keiner der drei Befunddateien gemessen` findet
in `daten/reihen.toml` **nur noch Z. 475** -- das ist Reihe 3, wo der Satz stehen bleiben
soll. Bei Reihe 14 kommt er nicht mehr vor.

An seiner Stelle stehen die beiden verlangten Sachen:

- **Z. 1260**, offener Widerspruch zu T5 Klasse 2, mit `Adressat Architekt` ausgeschrieben,
  dem gemessenen Wortlaut, den vier Moeglichkeiten aus Abschnitt 5 und dem Satz, dass diese
  Datei nichts davon entscheidet.
- **Z. 1261**, der Versionsvorbehalt aus Abschnitt 1: gemessen ist die Einheit der
  Beschreibungsseite am 2026-09-02, nicht die der Fassung 202601 im Wortlaut ihrer eigenen
  Freigabemitteilung, deren Abruf an der PDF-Sperre gescheitert ist.

**Die vier Sachbehauptungen in Z. 1260 gegen `specs/` gelegt**, weil ein uebernommener Satz
so falsch werden kann wie ein erfundener:

| Behauptung | Fundstelle | stimmt |
|---|---|---|
| T5 Klasse 2 verlangt Tausend USD zu konstanten Preisen des Basisjahrs | `technik.md` Z. 278 | ja, zeichengleich |
| Reihe 14 traegt 40 Stroeme | `technik.md` Z. 1446 (5 mal 4 mal 2), `reihen.toml` Z. 1250 | ja |
| T42 misst den MAPE gegen die Schwelle 2.000 (= 20 %) | `technik.md` Z. 2137-2138, Niveaureihen einschliesslich der 40 Handelsstroeme | ja |
| T37 fuehrt den Handelsblock unter den sechzehn Pruefgegenstaenden | `technik.md` Z. 2119-2126 | ja, als einer von sechzehn |

Zum letzten Punkt eine Praezisierung, die kein Befund ist: T37 vergleicht nicht jeden der 40
Stroeme einzeln gegen die Schwelle, sondern den **Median** ueber die 40. Der Eintrag sagt
beides getrennt und richtig -- T42 rechnet je Strom, T37 zaehlt den Block als einen
Gegenstand. Der Satz ist ausserdem wortgleich aus dem am 2026-09-02 abgenommenen Befund
uebernommen, und Bedingung 2 verlangt genau diese Uebernahme.

## Bedingung 3 -- die Antwort bei Reihe 16

Die `offen`-Liste der Reihe 16 hatte drei Eintraege und hat drei; der erste ist ersetzt
(Z. 1394). Die drei verlangten Bestandteile stehen darin: Groessenordnung gleich mit Faktor
1, Preisbasis verschieden, BACI laufend gegen WDI konstant 2015.

**Die Herkunft der Einheit von `N` habe ich nicht aus der Datendatei uebernommen, sondern in
`technik.md` nachgeschlagen** -- das ist die Stelle, an der eine abgeleitete Groesse still
die falsche Einheit erbt:

- `technik.md` Z. 1139: `wertschoepfung[g][s] = mal_geteilt(bip_start[g], sektoranteil[g][s], 10.000)`.
  `N` entsteht also aus Reihe 1 und den auf 10.000 normierten Anteilen der Reihe 2. Die
  Geldeinheit kommt aus Reihe **1**, weil Reihe 2 nur Anteile traegt. Der Eintrag sagt das
  ausdruecklich ("und nicht aus Reihe 2") -- Bedingung 3 verlangt es, und es stimmt.
- Reihe 1 in `reihen.toml`: `codes = ["NY.GDP.MKTP.KD"]` (Z. 275), `art = "geteilt"`,
  `faktor = 1000` (Z. 295-296), Begruendung mit `IndicatorName GDP (constant 2015 US$)`
  (Z. 298). Der Eintrag der Reihe 16 gibt beides richtig wieder.

**Die Handrechnung, die diese Rolle schuldet -- zwei Reihen aus zwei Quellen nach der
Aufbereitung gegeneinander:**

```
H (Reihe 14, BACI)     : v = 10^3 laufende USD             mal 1       -> 10^3 USD, laufend
N (ueber Reihe 1, WDI) : NY.GDP.MKTP.KD in USD, konst 2015 geteilt 1000 -> 10^3 USD, konstant 2015
```

Gleiche Waehrung, gleiche Groessenordnung, **verschiedene Preisbasis**. In
`durchgriff = teile_gerundet(10.000 mal H, H + N)` (`technik.md` Z. 1181) kuerzt sich die
Waehrungseinheit heraus, der Preisanteil nicht. Die Richtung, die der Eintrag angibt, habe
ich gegengeprueft: Bei steigenden Preisen ist `H` nach 2015 gegenueber `N` aufgeblasen, der
Zaehler waechst staerker als der Nenner, `durchgriff` faellt zu hoch aus; vor 2015
umgekehrt. Stimmt. Der Pruefjahrgang 1997 bis 2021 hat 25 Stuetzstellen (`technik.md`
Z. 2135, `S = 25`) und liegt zum groessten Teil weit von 2015 weg -- die Bezifferung des
Eintrags traegt.

Reihe 3 ist unveraendert: `art = "ungemessen"`, `status = "ungemessen"`, kein Faktor
(Z. 482-484). Sie steht nicht im Diff.

## Bedingung 4 -- sonst ist nichts geaendert

Der vollstaendige Aenderungsdiff von `daten/reihen.toml` in `ae6f605`: **zwei Hunks, 7
entfernte und 9 eingefuegte Zeilen.** Ich habe alle 16 gelesen.

- Hunk 1, `@@ -1257,18 +1257,20 @@`: die zwei `offen`-Zeilen und der Umrechnungsblock der
  Reihe 14.
- Hunk 2, `@@ -1389,7 +1391,7 @@`: die eine `offen`-Zeile der Reihe 16.

Keine der 16 Zeilen traegt eines der Felder `urteil`, `grund`, `wortlaut`, `url`,
`url_gegenprobe`, `abrufdatum` oder `sollreihen`. Die Zaehlbloecke `[zaehlung]` und
`[pruefweg]`, die acht `[[widerspruch]]`-Bloecke und alle 39 `[[reihe.deckung]]`-Bloecke
liegen ausserhalb der beiden Hunks; `deckung_gemessen` und `deckung_urteil` der Reihe 16
erscheinen in Hunk 2 als unveraenderte Kontextzeilen.

**Die Zaehlungen halten, gegen die neue Fassung gemessen:**

| Probe | verlangt | gemessen |
|---|---|---|
| Grep-Muster fuer Tabellenkoepfe (schnitt_3) | 112 | 112 |
| Grep-Muster fuer sollreihen mit Gleichheitszeichen (schnitt_5) | 21 Zeilen, Zeilensumme 43 | 21 Zeilen, Summe 43 |
| Summe `sollreihen` je `[[reihe]]`, ueber `tomllib` | 31 | 31, gleich `zaehlung.sollreihen_gesamt` |
| Dezimalpunktschnitt (schnitt_1) | 6 Treffer, alle Tausendertrenner | 6 |

## Befund 1 (an den Projektmanager) -- die Datei nennt ihre fuenfte Vorlage nicht

`daten/einheitenbefund-pwt-baci.md` steht jetzt viermal als `beleg` in `reihen.toml`
(Z. 1260, 1261, 1273, 1394). In der Herkunftsangabe der Datei steht sie nirgends:

- Kopf Z. 27-28: "**Sie misst nicht nach.** Jedes Urteil in dieser Datei stammt aus 0005,
  0006 oder 0014 und traegt seine Herkunft im Feld `beleg`." Reihe 14 traegt jetzt 0025.
- Kopf Z. 58-65, "Quellen dieser Datei": vier Dateien, der Einheitenbefund fehlt.
- `[datei.vorlagen]` Z. 79-83: vier Vorlagen, der Einheitenbefund fehlt. Der Block sagt
  ueber sich selbst: "Aendert sich eine davon, ist diese Datei nachzuziehen."
- `[datei].stand = "2026-09-02"` und `paket = "0017-reihenliste-maschinenlesbar"`: die Datei
  ist seither von 0022, 0032 und 0036 geaendert worden, zuletzt am 2026-09-03.
- Reihe 3, Z. 475 und Z. 484: "keine der **drei** Befunddateien". Es sind vier, und die
  vierte ist genau die, die den PWT-Kapitalstock vergeblich zu messen versucht hat und den
  Grund benennt (`einheitenbefund-pwt-baci.md` Abschnitt 3 und 4, PDF-Sperre). Wer der Zeile
  folgt, findet den Grund fuer `ungemessen` nicht.

**Das ist kein Ruecklauf.** Bedingung 4 verlangt wortwoertlich, dass Kopf, Zaehlbloecke und
alles ausserhalb der Reihen 14 und 16 zeichengleich bleiben. Der Bauagent haette sein eigenes
Kriterium gebrochen. Der Befund gilt dem Kriterium, nicht der Arbeit.

## Befund 2 (an den Projektmanager) -- die Selbstpruefung der Datei ist widerlegt

`[pruefweg].toml_geprueft` (Z. 1594) sagt: "nein -- nicht maschinell geprueft, und das ist
keine Nachlaessigkeit, sondern der Stand der Umgebung. Ein TOML-Leser laeuft hier nicht: der
python3-Aufruf wird abgewiesen (viermal ueber zwei Pakete, dem Datenbauer wie dem Pruefer)."

Er lief. Am 2026-09-03, in dieser Pruefung, mit Python 3.14.4 und `tomllib` gegen genau die
Fassung mit dem oben genannten sha256:

- Die Datei ist gueltiges TOML 1.0. 19 `[[reihe]]`-Bloecke.
- Zweimal eingelesen ergibt dieselbe Struktur (`a == b` ist wahr). Der Vergleich ist insoweit
  wiederholbar.
- Die Summe ueber `sollreihen` je `[[reihe]]` ist 31 und damit gleich
  `zaehlung.sollreihen_gesamt`.
- **Damit ist auch die eingestandene Luecke von `schnitt_6` geschlossen.** `tomllib` weist
  einen doppelten Schluessel innerhalb einer Tabelle ab -- gegengeprueft an einem
  Miniaturbeispiel, Fehlermeldung `TOMLDecodeError: Cannot overwrite a value`. Da die Datei
  einliest, gibt es keinen. Dasselbe gilt fuer die zwei Faelle aus
  `toml_geprueft_grenze`, ungueltiger Schluesselname und falsch verschachtelte Tabelle.

Wahr bleibt der zweite Teil des Satzes: Die Werkzeugliste der Rolle `datenbauer`
(`agents/rollen/datenbauer.md` Z. 7-14) fuehrt kein Werkzeug, das Code ausfuehrt -- das habe
ich nachgelesen. Falsch ist die Verallgemeinerung auf "die Umgebung". Der Pruefer hat Bash;
der Aufruf wird nicht durchgaengig abgewiesen, sondern uneinheitlich -- in diesem Lauf sind
vier von sieben python3-Aufrufen durchgegangen, und einer davon war der tragende.

Beide Befunde gehen in **Vorschlag `0049-reihentoml-herkunft-und-selbstpruefung`**.

## Was ich sonst gesucht und nicht gefunden habe

- **Stiller Einheitenfehler.** Der Faktor ist ausgerechnet und nicht gesetzt, und der
  Preisanteil, den er *nicht* beseitigt, steht an beiden betroffenen Reihen ausgeschrieben.
  Das ist die Gegenprobe zum teuersten Datenfehler: Die Datei sieht jetzt weniger plausibel
  aus als vorher, und das ist richtig so.
- **Stille Interpolation.** Keine dazugekommen. Der Eintrag, der gemessene Null von
  fehlendem Wert trennt (Z. 1262), steht unveraendert und ist der richtige Ort dafuer.
- **Neue Quelle ohne Lizenzpruefung.** Keine. `DescriptionBACI.html` ist eine
  Dokumentationsseite derselben Quelle, die `specs/.../daten.md` unter Nr. 3 fuehrt -- CEPII
  BACI, Etalab Open Licence 2.0. Der Etalab-Wortlaut in Z. 1278 ist unberuehrt, ebenso
  `url`, `url_gegenprobe` und `abrufdatum` aller Lizenzbloecke.
- **Zahl ohne Beleg.** Keine. Jede der vier Sachbehauptungen in Z. 1260 ist oben gegen
  `technik.md` gelegt.

## Zwei Beobachtungen, die kein neues Paket brauchen

**Erstens, Vorschlag 0047 ist gedeckt und seine Tabelle stimmt.** Er beschreibt genau die
Folgen von Bedingung 4: Leseregel 3 und `zaehlregel_umrechnung` nennen weiter zwei
ungemessene Reihen, der Widerspruch fehlt in der Widerspruchsliste, und die Belegstellen in
`[pruefweg]` sind verschoben. Nachgemessen: `schnitt_1` nennt 1345 und 1458, gemessen sind
1347 und 1460; `schnitt_2` nennt 1276, gemessen ist 1278; `schnitt_5` nennt 1324, 1380,
1437, 1492, 1547, gemessen sind 1326, 1382, 1439, 1494, 1549. Acht falsche Adressen, alle um
genau zwei Zeilen. Die Zaehlungen halten, wie 0047 sagt. Mein Vorschlag 0049 schneidet 0047
inhaltlich nicht -- die Stellen sind verschieden --, aber beide liegen in `reihen.toml`, und
aus dem Grund, den 0047 selbst nennt, gehoeren sie in **einen** Baulauf.

**Zweitens, die drei Schattenfassungen sind schlechter geworden, und 0045 hat es
vorhergesagt.** `daten/.neu.tmp`, `.neu2.tmp` und `.neu3.tmp` tragen den Wortlaut vor 0036,
je an den alten Zeilen 1260, 1271 und 1392. Ein Grep nach "Die Einheit von BACI ist
ungemessen" findet in `daten/` jetzt drei Treffer und `reihen.toml` nicht mehr. Paket 0045
(`offen`) hat den Fall wortwoertlich vorweggenommen: "Nicht Teil von 0034 oder 0036. Beide
ziehen `reihen.toml` inhaltlich nach. Sie machen die Kopien schlimmer, nicht besser." Kein
neuer Vorschlag; das ist frischer Beleg fuer ein Paket, das schon laeuft.

## Rueckwirkung auf andere Pakete

Die Frage an den Architekten steht jetzt in der maschinenlesbaren Fassung. Damit ist die
Vorbedingung erfuellt, an der 0026 (Klasse-2-Preisbasis), 0002 und 0010 haengen. Geprueft ist
hier allerdings nur, dass die Frage lesbar dasteht, nicht dass sie beantwortet waere -- das
gehoert dem Architekten und ist ausdruecklich kein Gegenstand dieses Pakets.
