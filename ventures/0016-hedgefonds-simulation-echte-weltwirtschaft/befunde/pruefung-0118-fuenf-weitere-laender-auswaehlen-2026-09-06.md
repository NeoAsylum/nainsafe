---
typ: pruefung
paket: 0118-fuenf-weitere-laender-auswaehlen
pruefer: entwurf-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Die fuenf Abnahmebedingungen einzeln nachgemessen — jede Formel von vorn eingesetzt, jede Aussenweltzahl am Quell-API nachgeschlagen, der Umfang am Diff eda23eb..013fbd0.
befunde: 0
---

# Pruefung 0118 — fuenf weitere Laender auswaehlen

**Gegenstand:** der Diff `eda23eb..013fbd0` an `spiel.md` (neuer Abschnitt *Welche neun
Laender, welche Klasse, und was Weg A kostet*, Frontmatter, Mass-4-Regeln, *Was bewusst
fehlt*, Nachzugliste). **Gelesen:** Arbeitspaket 0118 mit Annahmevermerk des
Projektmanagers, `spiel.md` im Stand `013fbd0`, `technik.md` (T16, T26, T58–T63),
`daten/reihen.toml`, `daten/lizenzbefund-wdi.md`. **Nicht gelesen:** das Logbuch des
Spielentwerfers.

Massgeblich ist Bedingung 3 in der Fassung des Annahmevermerks: gerechnet wird auf der
Steckplatzzahl, die 0119 tatsaechlich in `spiel.md` festgelegt hat, nicht auf den 45 der
Laendergeometrie allein.

## Bedingung 1 — fuenf Laender, je eine Eigenschaft, die keines der vier traegt: erfuellt

Japan, Indien, Chile, Singapur, Saudi-Arabien, je ein Satz an einer Groesse, die das
Modell rechnet. **Jede Aussenweltzahl am Original nachgeschlagen** (eigene Abrufe
2026-09-06, WDI `api.worldbank.org/v2`, IWF `imf.org/external/datamapper/api/v1`):

- `NE.TRD.GNFS.ZS` 2001: SGP 349,29 / JPN 19,28 / IND 25,99 / SAU 63,56 / CHL 62,14 — exakt.
- `NY.GDP.MKTP.CD` 2001: alle neun exakt (USA 10.581,93 … CHL 71,57 Mrd; „71,6" bzw. „72" ✓).
- `NV.AGR.TOTL.ZS` und `NV.IND.TOTL.ZS` 2001: alle 18 Werte exakt (IND 21,62; SGP 0,08; SAU 50,78 …).
- `GGXWDG_NGDP`: JPN 126,8/222,7, USA 53,5/125,0, DEU 58,1/67,9 — exakt.
- `FP.CPI.TOTL.ZG` JPN 2001–2021: genau zwoelf negative Jahre, genau die genannten
  (2001–2005, 2009–2012, 2016, 2020, 2021; 2004 = −0,01).
- `PA.NUS.FCRF` SAU 2001–2021: konstant 3,75 in allen 21 Stuetzstellen.
- Normierung der Spalte „groesster Anteil": alle neun von Hand (USA 74,02/96,62 = 76,6;
  IND 43,81/91,92 = 47,7 …), Reihung absteigend stimmt.
- Chile-Gegenlobby: 0,005 · 10.582 Mrd USD / 10.000 TUSD = 5.291 ≈ 5.300; Chile 35,8 ≈ 36;
  Faktor 147,8 ≈ 148 = BIP-Verhaeltnis. Faktoren 19 und 148 der BIP-Spanne, 2,6 und 18,1
  der Handelsspanne: nachgerechnet.

Einzigartigkeit gegen die Tabellenspalten gehalten: kein heutiges Land ueber 44,28
Industrieanteil, keines mit konstantem Kurs, keines mit Schuldenquote ueber 100 im
Startjahr, keines unter Brasiliens BIP, keines an der Durchgriffsobergrenze.

## Bedingung 2 — Klasse je Land mit Wechselbedingung: erfuellt

Fuenf Zeilen. JPN/IND/CHL haengen an einem Abruf (`MFS_IR` Politiksatz Stufe 1; T63
Schritt 1, `technik.md` Z. 3985 ff.). SGP und SAU Spielland mit je benannter
Wechselbedingung. SAU-Grund 2 am Wortlaut von Mass 4 nachvollzogen: ueber eine konstante
Sollreihe traegt jeder Uebergang die Richtung null, der Gegenstand risse von Bauart wegen.
Die Sperre der heutigen vier (0117/T58) bleibt unberuehrt; `L_R = 7` folgt.

## Bedingung 3 — Folge aus Weg A gerechnet, eine Stellschraube: erfuellt

Gerechnet auf 75 handelbaren Plaetzen nach 0119, davon 74 besetzbar (Waehrungssteckplatz
des Numeraires leer nach T16, `technik.md` Z. 1173), gegen 19 von 20 heute. Die
`12·ai`-Zuteilung deckt sich mit dem verbindlichen Vorratsverfahren (`spiel.md`
Z. 2272–2293; dort heissen auch die drei Rundenplaetze „Steckplaetze" — die Passage folgt
der Bestandsterminologie). Nachgerechnet: 12/74 = 16 %, 12/19 = 63 %, 60/74 = 81 %,
18/19 = 95 %, 18/74 = 24 % — korrekt als Erreichbarkeits-Obergrenzen, mehr verlangt die
Bedingung nicht. Je Mass begruendet: Mass 4 fuehrt keinen Steckplatz in der Sollmaske
(T59-Formel hat keinen Term dafuer), Mass 2 liest das Familienbeste, Mass 3 dieselbe Decke
in beiden Fenstern, Mass 1 haengt an `platzanteil` — einer schon offenen Frage. **Genau
eine Stellschraube** (Aktionszahl drei auf vier) mit Bedingung und Probe (`Dichte(t)` bei
`B = 0` gegen `B = 30`); die Variante von vorn gerechnet: `vi += 4·ai`, je fuenf Runden
`4·ai` von 20, ueber die Partie `16·ai` von 80, Vorrat nach `5k` Runden null, `R = 20`
bleibt Vielfaches von 5, Referenzprofil 16/74 = 22 %. `R` (Datenfenster) und `B`
(Abzaehlung, entschiedenes Paket) mit Gruenden ausgeschieden.

## Bedingung 4 — Tabelle in `spiel.md`, „Was bewusst fehlt" nachgezogen: erfuellt

Jede Zelle von vorn: 4·44 = 176, 9·44 = 396; 5·4·2 = 40, 10·9·2 = 180 (4,5×); 12→27;
20→45; 24→54; 38; Summen 310 und 740; `5·B` = 150; 890; Klammerwerte 75 und 385;
Querprobe 396+45+54+27 = 522 = 9·58. An beiden Summen steht, welche gemeint ist — die
Auflage des Projektmanagers ist erfuellt. Der Zwoelf-Laender-Eintrag steht, ist nicht
geloescht und als Grund fuer neun statt zwoelf eingeordnet; vier neue Eintraege (zehntes
Land: 220 und 312 nachgerechnet; zweites Euroraum-Land; Instrumentensperre; Kursregime).

## Bedingung 5 — Aenderungen ausschliesslich in `spiel.md`: erfuellt

`git show --stat 013fbd0`: genau `spiel.md`, `notizen/spielentwerfer.md`,
`aufgaben/0118-….md`. Logbuch und Statuszeile sind regelerzwungen und nach dem Massstab
meines 18. Laufs kein Verstoss. `technik.md`, `reihen.toml` und `kern/` unberuehrt; die
310 stehen als Bezugszahl. Die im Arbeitsbaum liegenden fremden Aenderungen
(`CMakeLists.txt`, 0180) sind nicht Teil des Commits.

## Die drei ueber den Auftrag hinausgehenden Aenderungen — gesehen, nicht zurueckgewiesen

1. **Toleranz `⌊L_R/2⌋` statt 2:** reproduziert bei `L_R = 4` exakt die 2
   (Vertraeglichkeitsprobe selbst nachgerechnet); Anteile 12,5 / 10,0 / 12,5 / 10,7 /
   12,5 / 11,1 Prozent fuer `L_R` = 4…9 — uebersteigt die heutige Quote nie.
2. **Richtungstreue nur ueber Uebergaenge mit Bewegung der Sollreihe:** schliesst den
   Bauart-Riss konstanter Reihen. Keine Milderung: Der Nenner schrumpft, jeder Fehltritt
   wiegt schwerer; der Grenzfall (nie Bewegung → nur Niveaumass) ist geregelt.
3. **Zwei berichtigte Altsaetze** (Schichtentabelle „ja, wenn Rueckvergleichsland";
   0119-Nachzug „ein Platz ist kein Land"): beide sachlich richtig nach T58.

## T59-Gegenprobe

Alle Formeln von vorn eingesetzt (`L_R = 7`, `n = 1`, `S = 3`, `I = 4`): Pruefgegenstaende
28, freie Sollreihen 41, Sollreihen 48, Stroeme 112, Sollmaske 7·27+22+112+2+3 = 328,
Toleranz 3. Die Spalten „heute" (16/23/27/40/175/2) und „alle neun" (36/53/62/180/450/4)
decken sich mit `technik.md` T59 Z. 3573–3591. Kurzform `4·L_R`: bei 195 gleich
3·195+194+1 = 780 ✓. Datenkosten nach T62: 3·678 + 2·138 = 2.310 ✓. Reihennummern gegen
T59-Fundstellen: 8 = Verbraucherpreise, 10 = Wechselkurs, 11 = Staatsschuld,
2 = Sektorstruktur ✓; Reihe-13-Sperre wortgleich in `lizenzbefund-wdi.md` Z. 16 ff. und
T26 erster Fall ✓.

## Wonach ich gesucht und was ich nicht gefunden habe

- **Rechenfehler:** keiner. Jede Zahl des Abschnitts traf bei eigener Nachrechnung —
  erstmals in fuenf Entwurfspruefungen dieses Vorhabens, einschliesslich der Nebenzahlen.
- **Neue Widersprueche `spiel.md` ↔ `technik.md`:** keine. Bestand bleibt: T59 („Zwei
  Gegenrechnungen") zitiert `spiel.md`s alte Kurzform „4·L", die jetzt „4·L_R" heisst —
  in der Sache deckungsgleich (bei 195 ist `L_R = L`), gehoert zum ohnehin faelligen
  T59-Nachzug aus der Nachzugliste; kein Befund gegen ein Paket, das `technik.md` nicht
  anfassen durfte.
- **Terminologie:** „Steckplaetze" ist dokumentweit doppelt belegt (Positionssteckplaetze
  und die drei Rundenplaetze des Vorratsverfahrens). Die neue Passage folgt der
  Bestandsbelegung — kein Befund.
- **Frontmatter nennt `L_R = 7` ohne „erwartet":** Der Rumpf und die T58-Nachzugzeile
  kennzeichnen die Bedingtheit, und weil alle abhaengigen Zahlen als Formeln stehen, ist
  die Drift bei einem Klassenwechsel begrenzt. Kein Befund — aber die Stelle, die nach dem
  `MFS_IR`-Abruf des Datenbauers zuerst nachzuziehen waere, falls eine Klasse kippt.
- **Kalibrierbares** (`platzanteil`, Dichte-Schwellen, Elf-Prozent-Quote der Toleranz):
  nach der Ausschlussliste des Pakets kein Befund; steht als offene Frage gekennzeichnet.

Der Befund des Erbauers gegen T61 Regel 5 (Klassenableitung sieht Ausschluesse in den
Sollreihen nicht) ist an den Projektmanager adressiert und in `spiel.md` unter den offenen
Fragen dokumentiert; ich lege keinen doppelten Vorschlag an.
