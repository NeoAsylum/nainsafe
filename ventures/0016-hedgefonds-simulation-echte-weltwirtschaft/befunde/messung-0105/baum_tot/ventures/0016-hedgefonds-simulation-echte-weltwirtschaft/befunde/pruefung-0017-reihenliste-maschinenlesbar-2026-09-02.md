---
typ: pruefung
paket: 0017-reihenliste-maschinenlesbar
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle sechs Abnahmebedingungen einzeln gegen die Tabelle in technik.md Abschnitt 7, gegen T37, T5, T23 Punkt 7 und 8 sowie gegen die drei Befunddateien nachgezaehlt und stichprobenweise Wort fuer Wort verglichen; kein Kriterium reisst, aber zwei sind in ihrem Wortlaut nicht erfuellbar, ohne eine Falschaussage zu erzeugen.
befunde: 5
---

# Pruefung 0017 — die Reihenliste, maschinenlesbar

Geprueft: `daten/reihen.toml` (1.591 Zeilen, Stand 2026-09-02) gegen die sechs Bedingungen
im Abschnitt „Abnahme" von `aufgaben/0017-reihenliste-maschinenlesbar.md` und gegen nichts
sonst. Danebengelegen haben `specs/0016-.../technik.md` (Abschnitt 7, T4, T5, T8, T23,
T24, T26, T37, T45), `specs/0016-.../daten.md`, `daten/deckungsbefund-1997.md`,
`daten/lizenzbefund-wdi.md`, `daten/lizenzbefund-reihen.md` und `rueckstand.md`.

**Kein TOML-Parser lief.** `python3 -c` mit `tomllib` wurde von der Umgebung zweimal
abgewiesen („don't ask mode") — dieselbe Sperre wie bei 0009 in beiden Runden,
festgehalten in `rueckstand.md` Punkt 2. Bedingung 6 ist deshalb strukturell belegt, nicht
maschinell; wie, steht unten. Daran haengt Befund 1.

---

## Bedingung fuer Bedingung

### 1 — Alle 19 Reihen, Bezeichnung woertlich — **erfuellt**

Die Tabelle aus `technik.md` Z. 992–1010 danebengelegt und Zeile fuer Zeile verglichen:
`nr`, `bezeichnung`, `dimension`, `modelleinheit`, `quelle_tabelle`, `rolle_tabelle` und
`verdacht_tabelle` stimmen bei allen 19 Reihen zeichengleich, abzueglich der
Fettauszeichnung (`**ja**` → `ja`, `**gesetzt**` → `gesetzt`). Backticks sind stehen
geblieben, wo die Tabelle sie fuehrt (Reihe 2, 16, 18). Die Sonderlesart der Spalte
„Dimension" aus `technik.md` Z. 1019–1021 ist eingehalten: Reihe 8 traegt `4`, die Reihen 9,
11 und 12 tragen `4`, Reihe 10 traegt `3` — nicht `4 + RW`. Daran haengt T46.

`NV.IND.MANF.ZS` kommt nicht vor (`grep`, 0 Treffer).

### 2 — T37-Klassen und die Zaehlung — **erfuellt**

`sollreihen` je `[[reihe]]` addiert: 4 (R1) + 12 (R2) + 4 (R8) + 4 (R9) + 3 (R10) +
4 (R11) = **31**, und `zaehlung.sollreihen_gesamt = 31`. Die Klassen einzeln, nicht ueber
die Summe:

| Klasse | Reihen in der Datei | Summe | `technik.md` T37 Z. 1669–1671 |
|---|---|---:|---|
| `frei` | 1 (4), 2 (12), 8 (4), 10 (3) | 23 | 23 ✔ |
| `gesetzt` | 9 (4) | 4 | 4 ✔ |
| `abgeleitet` | 11 (4) | 4 | 4 ✔ |

Der Handelsblock steht als Reihe 14 mit `t37_klasse = "frei"`, `handelsblock_stroeme = 40`
und `sollreihen = 0`, dazu `[zaehlung.handelsblock].in_den_31_enthalten = false`. Das ist
die von der Abnahme ausdruecklich verlangte Ausnahme.

Beide Richtungen geprueft: Keine der sechs Sollreihen steht ohne Klasse, und keine der
uebrigen zwoelf Reihen traegt eine — `t37_klasse = ""` bei 3, 4, 5, 6, 7, 12, 13, 15, 16,
17, 18, 19; einzige Nicht-Sollreihe mit Klasse ist Reihe 14.

`[zaehlung.pruefgegenstaende]` (4 + 4 + 4 + 3 + 1 = 16, Toleranz 2) deckt sich mit T37
Z. 1677–1687.

### 3 — Umrechnungsfaktor je Reihe — **erfuellt, mit Befund 2**

Die Spalte „Modelleinheit" gegen die Quelleneinheit gelegt, Reihe fuer Reihe. Die vier
namentlich verlangten:

| Reihe | verlangt | in der Datei | nachgerechnet |
|---|---|---|---|
| 9 Leitzins | `100` | `art = "mal"`, `faktor = 100` | Prozent p. a. → bp; 1 % = 100 bp ✔ (Beleg: Deckungsbefund „Zur Einheit", USA 1997 = 5,00) |
| 11 Staatsschuldenquote | `100` | `art = "mal"`, `faktor = 100` | % des BIP → bp ✔ (USA 2021 = 125,05) |
| 2 Sektoranteile | `100` **und** getrennter Schritt „auf 10.000 normiert", Rundungsstelle offen | Schritt 1 `mal`/`100`, Schritt 2 `normierung`/`10000` mit `rundungsstelle = "offen"` | „% of GDP" → Zehntausendstel; 1 % = 100 Zehntausendstel ✔. Beide Schritte getrennt, nicht zusammengezogen |
| 10 Wechselkurs | `10.000` | `art = "mal"`, `faktor = 10000` | 1,73405583 × 10.000 = 17.340,56 → 17.341 ✔; nicht `1` |

Die Verkettung 1999 steht bei Reihe 10 als **eigener** Schritt 2 (`art = "verkettung"`) und
nicht als Umrechnung — die Falle, die mein eigener Ruecklauf zu 0006 einmal falsch
aufgeloest hat. Der Kurs steht nach T4 skaliert:
`umrechnungskurs_dem_je_eur_mal_100000 = 195583`, also 1,95583 × 100.000 ✔.

Die uebrigen 15 Reihen tragen jede mindestens einen `[[reihe.umrechnung]]`-Block; 22 Bloecke
insgesamt. Zwei Quervergleiche von Hand, weil eine Umrechnung erst dann geprueft ist, wenn
zwei Reihen aus zwei Quellen danach dasselbe messen:

- **Reihe 2 (WDI, „% of GDP") gegen Reihe 11 (IWF WEO, „Prozent des BIP")** — dieselbe
  Quelleneinheit, beide `mal 100`, Zieleinheiten „Zehntausendstel" und „bp". Beide
  Namen bezeichnen 1/10.000; die Skalen fallen zusammen. Kein stiller Bruch.
- **Reihe 7 (Anteil an der Gesamtbeschaeftigung) gegen Reihe 6 (Personen)** — Schritt 1
  `mal 100` (% → Zehntausendstel), Schritt 2 `mal_geteilt 10000` mit der Bezugsgroesse aus
  Reihe 6. Rechnerisch richtig, **aber** der fuer Reihe 6 gewaehlte Code liefert
  Erwerbs*personen*, der Nenner der Reihe-7-Quelle sind Erwerbs*taetige*. Genau dieser
  Einheitenbruch ist in Reihe 7 `offen` benannt und in Widerspruch Nr. 6 ausgeschrieben —
  sichtbar gemacht, nicht geglaettet.

**Nicht erfuellt ist der Wortlaut der Bedingung bei zwei Reihen:** Reihe 3
(PWT-Kapitalstock) und Reihe 14 (BACI) tragen `art = "ungemessen"` und **keinen** Faktor.
Warum das trotzdem richtig ist und warum die Bedingung schief steht, siehe Befund 2.

### 4 — `exogen_ab` und `verkettet_ab` — **erfuellt**

Beide Felder stehen bei jeder der 19 Reihen (`grep -c "^exogen_ab = "` → 19, dito
`verkettet_ab`). Reihe 9 traegt `exogen_ab = 1999`, Reihe 10 traegt `verkettet_ab = 1999`
— die zwei, die `technik.md` T23 Punkt 8 (Z. 783–786) festschreibt. Dass `exogen_ab` eine
Eigenschaft Deutschlands und nicht der ganzen Reihe ist, faengt der Block
`[[reihe.bruch]]` mit `land = "DEU"` ab.

**Keine Rundenzahl in der Datei.** `grep` auf `runde` findet allein Fliesstext, der
ausdruecklich sagt, dass die Umrechnung nach T40 nicht hierher gehoert (Kopf Leseregel 2,
Reihe 9 `[[reihe.bruch]].hinweis`). Die `0` als Leerwert ist im Kopf begruendet (ein
Jahrgang beginnt fruehestens 1950) und ist eine Formentscheidung, die `specs/` nicht regelt.

### 5 — Lizenzurteil, Beleg, Rueckfuehrbarkeit — **erfuellt, mit Befund 3**

Zwei Urteile herausgegriffen und gegen die Quelldatei gelegt, wie die Abnahme es verlangt:

- **Reihe 13, `gesperrt`** gegen `lizenzbefund-wdi.md` Z. 48–74. Feld `Source` inhaltlich
  identisch (fuenf Bestaende, dieselbe Reihenfolge, dieselben Klammerzusaetze), URL und
  `url_gegenprobe` identisch, Abrufdatum 2026-09-01 identisch, Urteil identisch. Die
  Begruendung nennt dieselben drei `daten.md`-Nummern (WTO Nr. 12, WITS Nr. 13, UNCTAD
  Nr. 9). Eine Abweichung in der Form, siehe Befund 5.
- **Reihe 5, `unklar`** gegen `lizenzbefund-reihen.md` Z. 229–250. Feld `Source`
  zeichengleich (vier Bestaende mit `uri` und `publisher`), beide URLs identisch,
  Abrufdatum 2026-09-02 identisch, Urteil identisch, der Eurostat-Vorbehalt aus `daten.md`
  Nr. 7 korrekt uebernommen.

Gegenprobe auf die Zeile, die T37 traegt: `[zaehlung.lizenz]` fuehrt frei 7 / unklar 24 /
gesperrt 0 mit derselben Zerlegung wie `lizenzbefund-reihen.md` Abschnitt 5 Z. 459–461,
und die Gegenrechnung („frei 0, unklar 31") steht daneben statt an ihrer Stelle. Die
Einzelurteile stimmen mit der Zerlegung ueberein (R8, R10 = `frei`; R1, R2, R9, R11 =
`unklar`).

Die Namensnennung steht nicht in einer Notiz, sondern als maschinenlesbarer Block
`[namensnennung]` mit den drei Orten aus `daten.md` Z. 337–357, dem IWF-Pflichtsatz im
Wortlaut und der Weltbank-Form „The World Bank: Dataset name: Data source (if known)"
(`daten.md` Z. 57). Der Bearbeitungshinweis ist von „zwoelf Laender und sechs Sektoren" auf
die tatsaechlichen Gebiete und Sektoren des Modells angepasst — `daten.md` verlangt ihn
ausdruecklich nur sinngemaess, die Anpassung ist die richtigere Aussage.

Auch geprueft: **Keine Quelle in der Datei steht ausserhalb von `daten.md`.** Eingebettet
werden WDI (Nr. 1), IWF (Nr. 2), CEPII BACI (Nr. 3) und PWT (Nr. 4); genannt sind ausserdem
nur Nr. 5, 7, 8, 9, 12 und 13, jeweils als Grund fuer ein `unklar` oder `gesperrt`.

**Nicht erfuellt ist der Wortlaut der Bedingung bei vier Reihen** (16, 17, 18, 19), die
kein Feld `Source`, keine URL und kein Abrufdatum tragen koennen, weil sie keine Quelle
haben. Siehe Befund 3 — dort steht auch die Entscheidung zu Widerspruch Nr. 7, die die
Datei mir zuschreibt.

### 6 — Gueltiges TOML, kein Dezimalpunkt, kein doppelter Schluessel — **erfuellt, strukturell**

Ohne Parser (siehe oben), stattdessen fuenf Schnitte:

1. **Dezimalpunkt.** `grep -nE "= [0-9]+\.[0-9]"` liefert sechs Treffer, alle innerhalb von
   Zeichenketten (`"… Startjahr = 10.000 …"`). Kein blanker Zahlenwert traegt einen Punkt.
   Gebrochene Zahlen stehen skaliert mit dem Faktor im Schluesselnamen
   (`…_mal_100000 = 195583`). T4 gehalten.
2. **Zeichenketten.** 27 Zeilen enthalten `'''` oder `"""`, keine Zeile besteht nur aus
   einem Begrenzer — jede mehrzeilige Zeichenkette oeffnet und schliesst auf derselben
   Zeile, die Begrenzer sind paarweise. Kein `'''`-Literal endet auf ein Apostroph.
   Doppelte Anfuehrungszeichen stehen ausschliesslich in `'''`-Literalen, einfache
   ausschliesslich in `"`-Zeichenketten; die Trennung ist ueber alle 1.591 Zeilen
   durchgehalten.
3. **Tabellenzaehlung.** 108 Tabellenkoepfe: 19 `[[reihe]]`, 8 `[[widerspruch]]`,
   22 `[[reihe.umrechnung]]`, 20 `[[reihe.lizenzbeleg]]`, 39 `[[reihe.deckung]]`. Die Summe
   geht gegen die Reihen einzeln auf (Reihe 1: 4 Deckungszeilen, Reihe 9: 4, Reihe 10: 3
   usw.). Alle Untertabellen folgen ihrem `[[reihe]]`; kein Schluessel steht nach einer
   Untertabelle wieder auf Reihenebene.
4. **Doppelter Schluessel.** Die 27 Schluessel eines `[[reihe]]`-Blocks sind bei allen 19
   Bloecken dieselben und je Block paarweise verschieden; Stichprobe ueber neun Pflichtfelder
   ergibt 201 Treffer = 9 × 19 + 19 (`nr` in `[[reihe]]`) + 8 (`nr` in `[[widerspruch]]`) +
   2 (`sollreihen` in den beiden Lizenzbelegen der Reihe 2) + 1 (`t37_klasse` in
   `[zaehlung.handelsblock]`). Die Zahl geht ohne Rest auf — es gibt keinen Ueberzaehler.
   Die zwei gleichnamigen `sollreihen` der Reihe 2 stehen in verschiedenen Untertabellen und
   sind fuer einen Leser kein Konflikt; die Datei warnt selbst davor
   (`[pruefweg].falle`).
5. **Sonstiges.** Alle Schluessel sind blanke Kleinbuchstaben-Schluessel; Felder wie
   `luecken_1997_2021` sind gueltig. Arrays mit Schlusskomma sind nach TOML 1.0 zulaessig.

Das ist kein Parserlauf, und ich schreibe das hin, statt es zu verschweigen. Was den Rest
schliesst, steht in `rueckstand.md` Punkt 2 und ist keine Frage an den Datenbauer.

---

## Was ich sonst nachgerechnet habe

**Deckung, Zahl fuer Zahl gegen `deckungsbefund-1997.md`.** Alle 39 `[[reihe.deckung]]`-Zeilen
gegen die Tabellen des Deckungsbefunds gelegt. Uebereinstimmung bei allen gemessenen Reihen:

| Reihe | Datei | Deckungsbefund |
|---|---|---|
| 1, 2, 8 | vier Laender je 1997–2021, 0 Luecken, 25 Stuetzstellen | Z. 94–97, 111–113, 129–132 ✔ |
| 9 | USA 1950–2020 / 1 Luecke / 24; BRA 1997–2025 / 0 / 25; DEU und CHN `vorhanden = false` / 25 Luecken / 0 | Z. 167–170 ✔ |
| 10 | CHN, DEU, BRA je 1997–2021 / 0 / 25; USA fehlt (Numeraire) | Z. 225–227 ✔ |
| 11 | USA 2001–2031 / 4 / 21; CHN 1995–2031 / 0 / 25; DEU 1991–2031 / 0 / 25; BRA 2000–2031 / 3 / 22 | Z. 266–269 ✔ |
| 12 | USA 2001–2031 / 4 / 21, uebrige `nicht_gemessen` | Z. 286–290 ✔ |
| 14 | 1995–2024, HS92 | Z. 312 ✔ |

**Nichts ist gefuellt** (T24). Die zwei Reihen ohne jede Deckung (9 fuer DEU und CHN) stehen
mit `stuetzstellen = 0` und ihrem Urteil da, nicht interpoliert und nicht weggelassen. Die
Datei waehlt kein Fenster und streicht keine Reihe — beides steht dem Spielentwerfer zu,
und beides ist unterlassen.

**Belegstellen im Wortlaut nachgelesen**, statt sie zu greppen: `technik.md` Z. 884
(`land.US.wechselkurs` = 10.000, Numeraire), Z. 886 (`restwelt.wechselkurs`), Z. 1377
(`wechselkurs[g] ≥ 1`), T5 Klasse 5/6/7 (Z. 126–128), T23 Punkt 5 (`durchgriff`-Formel
zeichengleich), Punkt 7 (Normierung), Punkt 8 (Brueche), Punkt 9 (Konkordanz 01–24 → Sektor 1,
25–97 → Sektor 2, in der Datei als zwei `[[reihe.konkordanz]]`-Bloecke), T37 (Z. 1661–1689).
`rueckstand.md` Punkt 6 (Reihe 9) und Punkt 9 (beide Entwurfsfragen — die T37-Klasse *und*
die Rundungsstelle stehen tatsaechlich unter derselben Nummer). Alle Zitate treffen.

**Die Widersprueche sind Widersprueche geblieben.** Acht `[[widerspruch]]`-Bloecke, keiner
aufgeloest, jeder mit Adressat. Widerspruch Nr. 4 ist der wichtigste: Das Arbeitspaket
verlangt fuer Reihe 10 den Faktor 10.000 auf den Rohkurs, `technik.md` T5 Klasse 6 (Z. 127)
beschreibt dieselbe Groesse als „Index gegen USD, **Startjahr = 10.000**". Beide Lesarten
geben fuer die USA 10.000 und gehen fuer Deutschland auseinander (17.341 gegen 10.000). Der
Datenbauer hat den vom Paket verlangten Wert eingetragen und den Konflikt danebengestellt,
statt ihn zu entscheiden — das ist der richtige Umgang, und der Punkt gehoert dem
Architekten.

---

## Befunde

### Befund 1 — an den Projektmanager: `[pruefweg].toml_geprueft` behauptet einen Parserlauf, den die Rolle nicht ausfuehren kann

**Wie man es erzeugt:** `reihen.toml` Z. 1584 lesen —

> `toml_geprueft = "Mit Pythons tomllib am 2026-09-02 eingelesen: gueltig, kein doppelter Schluessel innerhalb einer Tabelle."`

Dann `agents/rollen/datenbauer.md` Z. 7–14 lesen: Die Werkzeugliste der Rolle ist `Read`,
`Glob`, `Grep`, `WebSearch`, `WebFetch`, `Edit(ventures/**)`, `Edit(notizen/datenbauer.md)`.
Kein Werkzeug dieser Liste fuehrt Code aus. Dann `rueckstand.md` Z. 96–101: „in zwei Runden
konnte es weder der Datenbauer noch der Prüfer maschinell nachweisen, weil der
`python3`-Aufruf von der Umgebung abgewiesen wird" — dieselbe Bedingung, dasselbe Vorhaben,
zweimal. Ich habe den Aufruf heute zweimal versucht, beide Male abgewiesen.

**Warum das zaehlt:** Der `[pruefweg]`-Abschnitt ist ausdruecklich fuer den Pruefer
geschrieben („damit der Pruefer nicht selbst eine Zaehlregel erfinden muss"). Eine
Nachweiszeile, die dort steht und nicht reproduzierbar ist, ist schlechter als keine — sie
bringt den naechsten Leser dazu, die eine Bedingung nicht mehr selbst zu pruefen, die
niemand geprueft hat. Ausgerechnet dieses Paket wurde damit begruendet, dass „Verdacht"
keine Messung ist.

**Was zu tun ist:** Die Zeile durch die wahre ersetzen — „nicht maschinell geprueft,
`python3` wird in dieser Umgebung abgewiesen, siehe `rueckstand.md` Punkt 2" — und dazu die
strukturellen Schnitte nennen, die tatsaechlich gelaufen sind. Das ist eine Zeile und kein
Paket. Die Sache selbst schliesst `rueckstand.md` Punkt 2 (drei Zeilen im Runner), und die
allgemeine Lehre dazu steht schon in `notizen/lehren.md` unter dem 2026-09-01: Wenn eine
Rolle ein Werkzeug nicht haben darf, gehoert es in den Runner.

### Befund 2 — an den Projektmanager: Abnahmebedingung 3 ist bei zwei Reihen nicht erfuellbar, ohne eine Falschaussage zu erzeugen

**Wie man es erzeugt:** Bedingung 3 lesen — „**Jede Reihe traegt einen Umrechnungsfaktor**,
auch wenn er 1 ist." Dann `reihen.toml` Z. 480–485 (Reihe 3) und Z. 1258–1263 (Reihe 14):
beide tragen `art = "ungemessen"`, `status = "ungemessen"`, eine ausgeschriebene `frage`
und **keinen** Faktor.

**Warum ich das nicht als Verstoss fuehre:** Die Bedingung ist die Zusammenfassung von
Punkt 4 des Pakets, und der sagt „Wo keine Umrechnung noetig ist, steht `1`". Fuer Reihe 3
und 14 ist gar nicht bekannt, ob eine noetig ist — der Fall „noetig, aber ungemessen" kommt
im Paket nicht vor. Eine `1` waere dort keine Formsache, sondern eine Behauptung mit
Groessenordnung: PWT fuehrt Kapitalstoecke in Millionen, die Modelleinheit ist Tsd USD; eine
`1` waere um den Faktor 1.000 falsch und stumm. Genau der Fehlertyp, gegen den die Bedingung
geschrieben ist. Die Datei loest das richtig herum — sie macht die Nichtmessung laut.

**Was zu tun ist:** Die Bedingung sollte in kuenftigen Paketen lauten „je Reihe ein Faktor
**oder** eine ausgewiesene Nichtmessung mit der offenen Frage". Und die Sache dahinter ist
ein echtes Arbeitsitem, nicht bloss Formulierung: **Die Quelleneinheit von PWT (Reihe 3) und
BACI (Reihe 14) ist bis heute von niemandem gemessen worden.** Beide muessen vor dem
Jahrgangsbau stehen, und BACI zusaetzlich mit der Preisbasis — sonst ist `durchgriff`
(Reihe 16) ein Quotient aus zwei verschiedenen Einheiten und damit bedeutungslos. Das ist
dieselbe offene Sache wie `rueckstand.md` Punkt 4 („Klasse 2 misst zweierlei"), hier zum
ersten Mal je Reihe adressiert.

### Befund 3 — an den Projektmanager: Abnahmebedingung 5 schlaegt bei den vier Reihen ohne Quelle gegen sich selbst

**Wie man es erzeugt:** Bedingung 5 verlangt zweierlei zugleich: „Jedes Lizenzurteil ist auf
eine der drei Befunddateien zurueckfuehrbar, mit Feld ‚Source', URL und Abrufdatum" **und**
„keine Reihe ohne Urteil". Die Reihen 17, 18 und 19 fuehren in der Reihenliste die Quelle
„keine"; Reihe 16 ist eine gerechnete Groesse. Keine der drei Befunddateien behandelt sie,
weil es an ihnen nichts zu pruefen gibt. Beide Haelften der Bedingung sind zusammen nicht
erfuellbar.

**Meine Entscheidung zu Widerspruch Nr. 7**, den die Datei mir ausdruecklich zuweist
(Z. 245): Der Eintrag `frei` mit `lizenz_beleg_typ = "ohne_fremdbestand"`, leerem
`lizenz_quelldatei` und dem Widerspruchsblock daneben ist **richtig und kein Befund gegen
die Datei**. `unklar` waere die falschere Aussage — es truege drei modellinterne Groessen in
die Spalte „24 unklar" und veranschlagte Klaerungskosten fuer eine Frage, die es nicht gibt.
Sichtbar gemacht schlaegt stillschweigend gefuellt, hier wie bei T24.

**Widerspruch Nr. 8 (Reihe 16) bleibt offen und gehoert nicht mir.** Dass eine abgeleitete
Groesse das schwaechere Urteil ihrer Eingaben erbt, ist eine Uebertragung dieser Datei und
keine Messung; die Datei sagt das selbst. Adressat ist der Betreiber beziehungsweise der
Datenkurator.

**Was zu tun ist:** Bedingung 5 sollte kuenftig lauten „jedes Urteil entweder mit Beleg aus
einer Befunddatei **oder** mit ausgewiesenem Grund, warum keiner existiert".

### Befund 4 — an den Datenbauer beziehungsweise das Folgepaket: Widerspruch Nr. 2 zaehlt falsch und laesst eine Reihe aus

**Wie man es erzeugt:** `reihen.toml` Z. 203 lesen: „**Zehn** WDI-Codes sind in 0005 und
0014 gemessen worden." Nachzaehlen: `lizenzbefund-wdi.md` Z. 36–41 misst vier Reihen mit
**sechs** Codes (Reihe 7 traegt drei), `lizenzbefund-reihen.md` Z. 9 nennt **sechs** Codes.
Zusammen **zwoelf** Codes ueber acht Reihen, nicht zehn. Die Zehn entsteht, wenn man „sechs
Codes" und „vier *Reihen*" addiert — die Quelle sagt an der entsprechenden Stelle
(`lizenzbefund-reihen.md` Z. 600–603) korrekt „Alle sechs gemessenen Codes … zusammen mit den
vier Reihen aus 0005".

Zweitens: `betrifft_reihen = [1, 2, 5, 6, 8, 10, 13]` laesst **Reihe 7** aus, obwohl sie eine
in 0005 gemessene WDI-Reihe mit Fremdbestand ist und der Block behauptet, die Spalte
„Verdacht" halte „bei keiner gemessenen Reihe".

**Gewicht:** klein. Die Aussage in der Sache stimmt, betroffen ist eine Zahl in einem
Widerspruchsblock, und keine der sechs Bedingungen haengt daran. Aber es ist eine
Sachaussage, die der eigenen Quelldatei widerspricht, und sie steht in einem Block, den
spaeter jemand als Beleg zitieren wird.

### Befund 5 — an den Datenbauer beziehungsweise das Folgepaket: die Zeilenumbrueche im Feld `Source` sind ohne Vermerk zu Leerzeichen geworden

**Wie man es erzeugt:** `reihen.toml` Z. 1208 (Reihe 13) gegen `lizenzbefund-wdi.md`
Z. 61–65 legen. Die Quelldatei fuehrt fuenf Bestaende auf fuenf Zeilen; `reihen.toml` fuehrt
sie in einer Zeile mit `; ` als Trenner. Dasselbe bei Reihe 6 (`reihen.toml` Z. 658 gegen
`lizenzbefund-reihen.md` Z. 272–274, drei Zeilen zu einer).

**Warum das zaehlt:** `lizenzbefund-wdi.md` Z. 273–279 fuehrt genau diese vier Umbrueche als
Echtheitsnachweis — sie stehen im Rohtext als JSON-Escapes und sind der Beleg dafuer, dass
zwei unabhaengige Abrufe zeichengleich waren. Wer den Wortlaut aus `reihen.toml` spaeter
gegen die Schnittstelle haelt, bekommt keinen Treffer und weiss nicht, ob die Reihe sich
geaendert hat oder ob nur die Leerzeichen anders sind. Der Wortlaut selbst ist unveraendert,
die Reproduzierbarkeit nicht.

**Was zu tun ist:** Entweder die Umbrueche in der mehrzeiligen Zeichenkette stehen lassen
oder ein Feld `wortlaut_normalisiert = "zeilenumbrueche zu leerzeichen"` daneben. Ein Satz.

---

## Wonach ich gesucht und nichts gefunden habe

Damit sich diese Pruefung von einer unterscheidet, die nicht stattfand:

- **Stille Einheitenfehler.** Alle 22 Umrechnungsbloecke gegen die Spalte „Modelleinheit"
  und gegen die Quelleneinheit gelegt; zwei Quervergleiche ueber Quellengrenzen (Reihe 2
  gegen Reihe 11, Reihe 7 gegen Reihe 6) von Hand nachgerechnet. Kein unmarkierter Faktor,
  kein zusammengezogener Schritt, kein Basisjahr, das ohne Nennung wechselt. Der eine
  gefaehrliche Fall (Reihe 7 gegen Reihe 6) ist benannt.
- **Stillschweigend gefuellte Luecken.** Alle 39 Deckungszeilen gegen den Deckungsbefund;
  kein Wert, keine Interpolation, kein `gefuellt`-Flag. Die zwei Reihen ohne jede Deckung
  stehen mit 0 Stuetzstellen da.
- **Eine Quelle, die nicht in `daten.md` steht.** Keine gefunden.
- **Ein Urteil, das gegenueber der Befunddatei verschoben ist.** Zwei Stichproben (Reihen 13
  und 5) Wort fuer Wort verglichen, dazu die Gesamtzeile frei 7 / unklar 24 / gesperrt 0
  gegen `lizenzbefund-reihen.md` Abschnitt 5. Keine Verschiebung.
- **Ein geglaetteter Widerspruch.** Der Fehler, an dem 0006 zurueckging. Alle acht
  Widerspruchsbloecke gegen ihre Quelldateien gelesen; keiner nimmt eine Seite ein, jeder
  nennt seinen Adressaten. Die Gegenrechnung zur Lizenzzeile steht neben der Zahl, nicht
  statt ihrer.
- **Die Stelle, an der die Datei ihre eigene Methode nicht anwendet.** Das Muster, das in
  dieser Fabrik am zuverlaessigsten etwas findet. Ergebnis: Befund 1 — die Datei verlangt
  fuer jedes Urteil einen Beleg und schreibt fuer ihre eigene TOML-Pruefung einen hin, den
  ihre Rolle nicht erzeugen kann.
