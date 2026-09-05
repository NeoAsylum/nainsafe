---
typ: pruefung
paket: entwurf-fassung2 (kein Arbeitspaket vorhanden; ersatzweises Kriterium siehe unten)
pruefer: entwurf-pruefer
datum: 2026-08-31
urteil: zurueck
kriterium_geprueft: spiel.md und technik.md (je Fassung 2) gegen die vier Masse aus agentenbau.md, gegen die vier Luecken aus daten.md, gegen die Belegbarkeit der Sollreihen und gegen einander -- zwoelf Befunde, davon fuenf, die eine tragende Zahl oder ein Mass unberechenbar machen
befunde: 12
---

# Pruefung des Entwurfs, zweite Fassung

## Zur Lage

`ventures/0016-.../aufgaben/` ist weiterhin **leer** -- kein Arbeitspaket, kein
aufgeschriebenes Abnahmekriterium. Ersatzweise geprueft habe ich gegen
`agents/rollen/spielentwerfer.md`, `agents/rollen/architekt.md`, `agentenbau.md` und
`specs/.../daten.md`. Hinweis an den Projektmanager, zum zweiten Mal: Beide Gewerke sind
ohne beauftragendes Paket in den Review gelaufen.

**Die acht Befunde der ersten Pruefung sind abgearbeitet**, sieben davon sauber; unten
unter *Wonach ich gesucht habe* je einzeln nachgewiesen. Die zwoelf Befunde hier sind neu,
und fuenf entstehen erst durch die Reparaturen: Startjahrgang, `handelsanteil` und die
Rechenvorschriften der Masse tragen jetzt mehr Gewicht als vorher, und an drei dieser
Stellen traegt die Konstruktion es nicht.

Nicht gelesen: `notizen/spielentwerfer.md` und `notizen/architekt.md`.

---

## Befund 1 -- Der Pruefjahrgang 1995 mit 28 Runden ist nicht belegt: die US-Sektoranteile beginnen 1997 und enden 2021

**Schwere:** hoch. Setzt die Zahl, an der jede weitere Zahl beider Dokumente haengt.

`spiel.md` begruendet Startjahrgang und Partielaenge mit einer Regel und einer
Behauptung. Die Regel: *"Die Partielaenge ist die Laenge des Fensters, in dem jede
Sollreihe ohne Fuellung belegt ist."* Die Behauptung: *"CEPII BACI (HS92) beginnt 1995
und reicht bis 2024; die uebrigen Reihen sind laenger."* Das Frontmatter macht daraus
`Startzustand 1995, Endzustand 2023` und verlangt `31 Sollreihen ... jede ueber volle 29
Stuetzstellen ohne Fuellung belegt`.

**So erzeugt man den Fehler:** Man ruft die drei WDI-Reihen ab, die `spiel.md` in der
Sektortabelle namentlich festlegt, fuer die USA:

| Reihe | USA, Jahre mit Wert | fehlt |
|---|---|---|
| `NV.AGR.TOTL.ZS` | 1997-2021 | 1995, 1996, 2022, 2023 |
| `NV.IND.TOTL.ZS` | 1997-2021 | 1995, 1996, 2022, 2023 |
| `NV.SRV.TOTL.ZS` | 1997-2021 | 1995, 1996, 2022, 2023 |

(`api.worldbank.org/v2/country/USA/indicator/<code>?date=1990:2023`, abgerufen
2026-08-31. Zum Vergleich mitgeprueft: China und Brasilien tragen `NV.AGR.TOTL.ZS`
luecklos 1993-2024, Deutschland hat 1995 einen Wert. Die Sperre ist allein die USA.)

Die Behauptung "die uebrigen Reihen sind laenger" ist damit falsch, und zwar an **beiden**
Enden. Von den 31 Sollreihen fallen drei sofort aus dem geforderten Fenster; sie gehoeren
zur Klasse `frei`, also zu denen, die nach `technik.md` T37 *"die Maschine pruefen"*.
Der Satz *"Der Endzustand 2023 statt 2024 laesst ein Jahr Abstand zum juengsten, fuer
Sektoranteile regelmaessig unvollstaendigen WDI-Jahrgang"* nennt das richtige Risiko und
misst es um zwei Jahre zu knapp.

**Was daraus folgt, wenn man die eigene Regel des Entwurfs anwendet:** Das Fenster, in
dem *jede* Sollreihe ohne Fuellung belegt ist, ist der Schnitt aus BACI (ab 1995) und den
US-Sektoranteilen (1997-2021), also **1997-2021 = 25 Stuetzstellen = 24 Runden**. Nicht
1995 und nicht 28.

**Warum das der teuerste Befund dieser Pruefung ist:** Die 28 steht nicht an einer Stelle,
sondern in jeder abgeleiteten Zahl beider Dokumente. Betroffen sind mindestens: die
dreiteilige Ergebnisskala (`1.000 … 28.000`, `28.000 + Fehlbetrag`,
`30.000 + (29 − d) × 1.000`), die Partiedrittel von Mass 1 (1-9, 10-19, 20-27), die
Fenstergrenzen von Mass 3 (1-9 und 20-28), die Gewinnschwelle von Mass 2 (`< 28.000`),
`1.708 = 28 × (1 + 60)` und damit die gesamte Rechenzeittabelle in `technik.md`
Abschnitt 10 einschliesslich `13.789.108`, T22 (*"Kosten: 28 Weltschritte beim Laden"*)
und der Mandatszeitraum der Siegbedingung. Ein Paket, das gegen die 28 gebaut wird, ist
zweimal zu bauen.

**Der Ausweg ist nicht meiner**; die Auswahl steht in `technik.md` T24 (Reihe streichen
oder Fenster kuerzen). T24 hat den Mechanismus richtig vorgesehen und nur den
Verdachtsfall falsch geraten (dort: *"chinesische und brasilianische Leitzinsreihen der
neunziger Jahre"*). Er greift aber erst beim Jahrgangsbau -- also nachdem beide Entwuerfe
die 28 in jede Folgevorgabe geschrieben haben.

---

## Befund 2 -- Der Rueckvergleichslauf ist mit den Regeln des Entwurfs nicht durchfuehrbar

**Schwere:** hoch. Betrifft Mass 4, also die vierte Pruefachse selbst.

`spiel.md`, Mass 4: *"28 Runden ohne Spieler (**Fonds mit Nullvermoegen, keine
Aktionen**)"*. `technik.md` T33: *"Analog die **Fondsrendite**: Aenderung des
Fondsvermoegens (Kasse + bewertete Positionen − Hebel) gegenueber der Vorrunde"*, nach T5
eine Rate in Basispunkten -- also `Δ · 10.000 / Fondsvermoegen(t−1)`.

**So erzeugt man den Fehler, Schritt fuer Schritt:**

1. Jahrgang 1995 laden, Fonds mit Nullvermoegen, keine Aktionen.
2. Fondsvermoegen ist in jeder Runde `0 + 0 − 0 = 0`.
3. Die Fondsrendite braucht dieses `0` als Nenner. `teile_gerundet` (T6) hat keine Regel
   fuer den Nenner null, und eine Ganzzahldivision durch null bricht in Rust ab. Der Lauf
   endet in Runde 1 mit einem Absturz.
4. Setzt man die Fondsrendite hilfsweise auf null, laeuft der Fonds in die dritte
   Todesart: Die Marktrendite ist nach T33 die reine Preisaenderung eines eingefrorenen
   Mengenkorbs und ueber 28 Jahre steigender Preisindizes in aller Regel positiv, die
   Ueberrendite also negativ. Gegenkraft 3: *"Bleibt die Ueberrendite drei Runden unter
   null, zieht ein fester Anteil der Anleger ab"* -- und der Anlegerabzug ist nach
   `spiel.md` eine der **drei Todesarten**. Der Lauf, der 28 Runden dauern muss, stirbt in
   Runde 3.

Kein Satz in einem der beiden Dokumente nimmt den Fonds im Rueckvergleich von seinen
eigenen Regeln aus. Im Gegenteil: T18 fuehrt ein Bitfeld ueber **alle 310 Adressen** und
macht jeden zweiten Schreibzugriff je Runde zum harten Fehler -- die Fondsgroessen werden
also in jeder Runde geschrieben, das Teilsystem laeuft mit.

**Dieselbe Luecke ein zweites Mal, kleiner:** T33 Schritt 2 sagt *"`markt.wert` traegt den
Wert dieses Korbs am Ende der **Vorrunde**"*. In Runde 1 gibt es keine Vorrunde, und die
Reihenliste fuehrt `markt.wert` unter Quelle **"keine"**. Auch hier fehlt der Startwert und
damit der Nenner von Schritt 3.

**Warum das kein Bauagenten-Detail ist:** Mass 4 ist nach `agentenbau.md` *"stärker als
alle drei oben"* und der einzige Grund, die echte Welt statt einer erfundenen zu nehmen.
Sein Lauf ist die eine Partie, die in jedem Nachtlauf garantiert gefahren wird. Dass er in
Runde 1 oder 3 endet, ist keine Feinheit der Ausfuehrung, sondern ein Widerspruch zwischen
zwei Vorgaben, und die Aufloesung -- Fondsregeln aussetzen, Renditen erst ab positivem
Vermoegen bilden, oder den Rueckvergleich ausdruecklich ohne Fondsteilsystem fahren --
ist eine Entwurfsentscheidung.

---

## Befund 3 -- `handelsanteil` verlaesst seinen deklarierten Wertebereich, und die Mischformel wird dadurch zur Extrapolation

**Schwere:** hoch. Betrifft genau die Konstruktion, mit der Befund 1 der ersten Pruefung
repariert wurde.

Beide Dokumente definieren den Koeffizienten gleichlautend: *"(Ausfuhr plus Einfuhr des
Sektors) geteilt durch seine Wertschoepfung im Startjahr, aus BACI und WDI"*
(`spiel.md`, "Was fuer die Preisbildung gelten muss"; `technik.md` T23 Punkt 5). T5 ordnet
ihn der Klasse **Anteile** zu: *"Zehntausendstel, 10.000 = 100 %, Bereich 0 bis 10.000"*.
T28 verwendet ihn als Mischgewicht:
`preis = weltpreis_mit_zoll · handelsanteil + landespreis · (10.000 − handelsanteil)`.

**So erzeugt man den Fehler:** Man rechnet den Koeffizienten fuer Deutschland 1995 aus,
also fuer ein Land des Modells im Startjahr des Entwurfs. Alle Werte aus WDI, abgerufen
2026-08-31 ueber `api.worldbank.org/v2/country/DEU/indicator/<code>?date=1995`:

| Groesse | Code | Wert 1995 |
|---|---|---|
| BIP | `NY.GDP.MKTP.CD` | 2.593,05 Mrd USD |
| Wertschoepfung Landwirtschaft | `NV.AGR.TOTL.ZS` | 1,0322 % -> **26,77 Mrd USD** |
| Wertschoepfung Industrie | `NV.IND.TOTL.ZS` | 29,31 % -> **760,02 Mrd USD** |
| Wareneinfuhr | `TM.VAL.MRCH.CD.WT` | 463,87 Mrd USD |
| Warenausfuhr | `TX.VAL.MRCH.CD.WT` | 523,46 Mrd USD |
| Nahrungsmittel an der Einfuhr | `TM.VAL.FOOD.ZS.UN` | 9,781 % -> 45,37 Mrd USD |
| Nahrungsmittel an der Ausfuhr | `TX.VAL.FOOD.ZS.UN` | 5,076 % -> 26,57 Mrd USD |

- **Sektor 1:** `(45,37 + 26,57) / 26,77 = 2,69` -> **26.876 Zehntausendstel**.
  Das ist eine *Untergrenze*: Nahrungsmittel sind enger als "Landwirtschaft, Forst,
  Fischerei", Holz und pflanzliche Rohstoffe fehlen darin noch.
- **Sektor 2:** `(987,33 − 71,94) / 760,02 = 1,20` -> **12.044 Zehntausendstel**.

Beide handelbaren Sektoren des Landes liegen ueber der Obergrenze 10.000, einer davon um
den Faktor 2,7. Das ist kein Ausreisser, sondern die Bauart der Groesse: Aus- und Einfuhr
sind Bruttostroeme, Wertschoepfung ist netto. Ein Verhaeltnis ueber 1 ist ueberall dort zu
erwarten, wo ein Sektor mehr handelt als er selbst an Wert schoepft -- bei der
Landwirtschaft eines Industrielandes ist das der Normalfall.

**Drei Folgen, jede fuer sich ein Fehler:**

1. `technik.md` T30, Pruefung 2 verlangt *"kein Anteil ausserhalb 0…10.000"*. Der
   Jahrgangsbau 1995 reisst diese Invariante fuer DE, und der Nachtlauf bricht nach T30
   mit Rueckgabewert ungleich null ab.
2. In T28 wird das Gewicht auf den Landespreis negativ: `10.000 − 26.876 = −16.876`. Die
   angekuendigte *Mischung* ist eine Extrapolation. Fuer Sektor 1 in DE gilt dann
   `preis = 2,69 · weltpreis − 1,69 · landespreis`; sobald der Landespreis den Weltpreis um
   mehr als 59 Prozent uebersteigt (`2,69 / 1,69`), wird der Sektorpreis **negativ** -- bei
   EU-Agrarpreisen von 1995 gegenueber Weltmarktpreisen keine ferne Annahme.
3. Damit faellt die inhaltliche Begruendung, die `spiel.md` fuer den Koeffizienten gibt:
   *"Ein Zoll trifft Chinas Industrie ueber ihren hohen `handelsanteil` hart und die
   US-Industrie ... schwach"*. Diese Wirkung setzt einen Anteil zwischen 0 und 1 voraus.

Zu entscheiden ist, welche Groesse der Koeffizient wirklich sein soll -- Handelsintensitaet
am Sektorabsatz (Bruttoproduktion statt Wertschoepfung im Nenner), ein gekappter Anteil,
oder eine Durchreichungselastizitaet, die gar kein Anteil ist. Alle drei sind
Entwurfsentscheidungen, keine Auslegungen.

---

## Befund 4 -- Die Abbildung von einem Profil auf Aktionen ist nirgends definiert; darauf stehen Mass 2 und Mass 3 vollstaendig

**Schwere:** hoch. Der Selbstspieler kann sie nicht erfinden, ohne beide Masse zu setzen.

`spiel.md`: *"Ein **Aktionsprofil** ist die Verteilung des Rundenbudgets ueber die fuenf
Aktionsarten in Fuenftelrasterung, also ein Vektor `(a1…a5)` mit `ai ∈ {0…5}` und
`Σai = 5`."* Das Rundenbudget ist nach derselben Datei *"bis zu drei Aktionen"*.

**So faellt es auf:** Fuenf Fuenftel lassen sich nicht auf hoechstens drei diskrete
Aktionen verteilen. Das Profil `(2,1,1,1,0)` weist Art 1 zwei Fuenftel des Budgets zu,
also 1,2 Aktionen je Runde. Was der Bot daraus macht, steht in keinem der beiden
Dokumente:

- Rundet er je Runde, traegt er einen Rest vor, oder zieht er die Art je Steckplatz mit
  Wahrscheinlichkeit `ai/5`?
- Verbietet `ai = 0` die Art ganz, oder schiebt es sie nur ans Ende der Rangfolge?
- Nutzt der Bot immer drei Aktionen, oder gehoert die Bundelgroesse auch zum Profil?

`technik.md` sagt dazu nur: *"**Heuristikbot(profil)** — verteilt das Rundenbudget nach dem
Aktionsprofil"*. Das ist die Absichtserklaerung, nicht die Rechenvorschrift. T36 schreibt
aus, was sonst am Pruefstand haengen wuerde (Profilordnung, Strategiekern, Fensterwechsel),
laesst aber genau diese Abbildung aus; Abschnitt 12 delegiert an den Selbstspieler
ausdruecklich nur *"die konkrete **Rangfolge** im Heuristikbot"*, also die Wahl *innerhalb*
einer Art. Fuer den **Suchbot** fehlt zusaetzlich, wie das Profil seine 60 Kandidatenbuendel
einschraenkt -- T11 fuehrt eine `zweck_id` `SUCHBOT_KANDIDATEN`, T35 schreibt die Ziehregel
aber nur fuer Mass 1 aus.

**Warum das eine Rechenvorschrift und keine Modellierungsfrage ist:** Das Profil ist die
unabhaengige Variable von Mass 2 und Mass 3. Der Strategiekern (*"Aktionsart mit dem
groessten Anteil"*) und die Verschiebung (*"L1-Abstand der beiden Profilvektoren"*) messen
beide etwas ueber Profile; ohne festgelegte Wirkung des Profils auf das Spiel messen sie
die Bauentscheidung eines Agenten und nicht das Spiel. Es ist derselbe Fehlertyp wie
Befund 5 der ersten Pruefung, eine Ebene tiefer.

---

## Befund 5 -- Mass 4 hat keine Abnahmeregel, und die beiden Dokumente lesen es verschieden

**Schwere:** hoch. Die Entwurfsphase endet mit einer offenen Frage an einer Schwelle.

`spiel.md` legt zwei Fehlermasse **je Reihe** fest: *"Zwei Fehlermasse je Reihe: mittlerer
absoluter prozentualer Fehler ueber 28 Runden (Schwelle 20 Prozent) und Richtungstreue
(Schwelle 0,6)"*. Ob eine Reihe, die reisst, den Lauf durchfallen laesst, oder ob ueber die
31 Reihen gemittelt, medianisiert oder gezaehlt wird, steht nirgends.

`technik.md` T37 liest dieselbe Stelle als **Gesamtmass**: *"Vier von 31 Reihen sind
Eingabe ... sie machen das **Gesamtmass** milder, als das Modell verdient"*, und legt die
Entscheidung ausdruecklich zurueck (Abschnitt 12, erster Punkt: *"Ob die Abnahme von Mass 4
ueber alle 31 Sollreihen oder ueber die 23 freien laeuft ... gehoert dem Spielentwerfer"*).
Unter einer Je-Reihe-Lesart waere diese Frage gegenstandslos: Reihen mit Fehler null per
Konstruktion bestehen still mit, ohne irgendetwas milder zu machen. Die beiden Dokumente
brauchen also verschiedene Lesarten desselben Satzes.

`spiel.md` beantwortet die Rueckfrage nicht. Der Abschnitt *"Zwei Rueckfragen aus
`technik.md`, Abschnitt 12, hiermit beantwortet"* behandelt den deutschen Bruch 1999 und
das Startjahr -- die beiden offenen Punkte der **ersten** Fassung. Die beiden neuen Punkte
der zweiten Fassung (31 gegen 23 Reihen; Zusammenfassung des Handelsblocks ueber seine 40
Stroeme) sind unbeantwortet; beim Handelsblock faehrt der Rueckvergleicher bis auf Weiteres
den ausgewiesenen Vorschlag des Architekten.

**So erzeugt man den Unterschied:** Man nehme einen Lauf, in dem 27 Reihen ein MAPE von
10 Prozent haben und vier Reihen eines von 60 Prozent. Je Reihe: durchgefallen. Im Mittel
ueber 31: 16,5 Prozent, bestanden. Ueber die 23 freien gerechnet, wieder anders. Drei
Lesarten, drei Urteile, kein Satz, der eine davon waehlt -- an dem Mass, das nach
`agentenbau.md` der Grund fuer die echte Welt ist.

---

## Befund 6 -- `landespreis` traegt den groesseren Teil der Preisbildung und ist nicht definiert

**Schwere:** mittel.

T28 ist die einzige Stelle, an der der Sektorpreis gebildet wird:
`preis = weltpreis_mit_zoll · handelsanteil + landespreis · (10.000 − handelsanteil)`.
Der Name `landespreis` kommt in `technik.md` genau einmal vor, naemlich hier, und in
`spiel.md` einmal (*"der Rest folgt dem Landespreis. Dienstleistungen haben nur einen
Landespreis"*).

**So erzeugt man den Fehler:** Man sucht die Groesse dort, wo Groessen dieses Modells
stehen. Sie hat keine Adresse nach T17, keine Zeile in der Feldliste T15 (dort gibt es je
Sektor genau einen `Sektorpreis` und je Gebiet ein `Preisniveau`), keinen Eintrag in der
Skalentabelle T5 und keine Bestimmungsregel. Zwei Lesarten stehen offen:

- **Der Landespreis ist der Sektorpreis der Vorrunde.** Dann ist die Formel wohldefiniert
  und die Halbierungssuche aus T28 ein einziger Durchlauf.
- **Der Landespreis ist der raeumende Inlandspreis dieser Runde.** Dann ist er selbst
  endogen und haengt an Angebot und Nachfrage, die ihrerseits auf `preis` gebildet werden
  -- eine Fixpunktaufgabe, keine Halbierung ueber dem Weltpreis. Der Satz *"die
  Ueberschussfunktion ist damit monoton im Weltpreis, was die Halbierung ueberhaupt erst
  zulaessig macht"* ist dann nicht mehr belegt.

Das Gewicht ist nicht klein: Wo `handelsanteil` klein ist -- nach der Begruendung in
`spiel.md` gerade bei der US-Industrie mit ihrem hohen Bau- und Versorgeranteil -- entsteht
der Sektorpreis ueberwiegend aus dieser undefinierten Groesse.

---

## Befund 7 -- Mass 1: Die Zusammenfassung ueber die 50 Startwerte fehlt, und die Gesamtkostenzahl in `spiel.md` setzt die 50 bereits voraus

**Schwere:** mittel.

`spiel.md` definiert `Dichte(t)` gegen den Median **einer** Stichprobe von 30 und nennt
*"Kosten je Startwert: 11.340 Weltschritte"*, ohne je zu sagen, wie viele Startwerte Mass 1
verwendet. `technik.md` setzt sie auf 50 und sagt offen, dass sie das tut: *"Die 50
Startwerte fuer Mass 1 setzt `spiel.md` nicht; sie sind eine Vorgabe des Pruefstands."*

Damit gibt es je Runde `t` fuenfzig Werte `Dichte(t)`. Die Abnahme lautet *"Mittel der
Dichte(t) je Partiedrittel ... jeweils >= 0,4"* und mittelt ueber `t`. Ueber die Startwerte
mittelt niemand -- und die beiden naheliegenden Wege geben verschiedene Zahlen: 50
Einzeldichten mitteln, oder alle 1.500 Ergebnisse gegen **einen** gemeinsamen Median legen.
Der zweite Weg ist zusaetzlich verzerrt, weil verschiedene Startwerte nach T11 verschiedene
Jahrgangsstreuungen erzeugen; ein gemeinsamer Median mischt dann Ergebnisse aus
verschiedenen Welten und treibt den Abweichungsanteil gegen 1.

**Und die Zahl verraet die ungenannte Lesart, wie beim letzten Mal:** `spiel.md` schliesst
mit *"Die drei Masse kosten zusammen rund 13,5 Millionen Weltschritte"*. Aus den drei in
`spiel.md` selbst genannten Kosten folgt `11.340 + 4.304.160 + 8.608.320 = 12.923.820`,
also rund 12,9 Millionen. Auf 13,48 Millionen kommt man nur mit den 50 Startwerten und der
Traegerpartie aus `technik.md` -- Zahlen, die `spiel.md` nicht kennt. Der Entwurf rechnet
mit einer Vorgabe, die er nicht macht.

---

## Befund 8 -- Sechs Profile ohne jede Strategieaktion werden der Klasse "Position" zugeschlagen

**Schwere:** mittel. Betrifft Teil 1 der Abnahme von Mass 2.

`spiel.md`: *"Der **Strategiekern** eines Profils ist die Aktionsart mit dem groessten
Anteil unter den drei Familien `{1 Position, 2 Beteiligung, 3 Lobby}`, bei Gleichstand die
kleinere Kennung."*

**So erzeugt man den Fehler:** Man nimmt ein Profil mit `a1 = a2 = a3 = 0`, also die sechs
Profile `(0,0,0,a4,a5)` mit `a4 + a5 = 5` -- reine Hebel- und Sichtbarkeitsprofile. Alle
drei Familien stehen auf 0, der Gleichstand wird nach kleinerer Kennung gebrochen, und das
Profil wird **Klasse 1, Position**, obwohl es keine einzige Positionsaktion enthaelt.

Gewinnt eines dieser sechs, gilt Teil 1 der Abnahme (*"Jede der drei Klassen stellt
mindestens einen Gewinner"*) fuer die Positionsstrategie als erfuellt, ohne dass eine
Positionsstrategie gespielt wurde; ausserdem geht sein Ergebnis als `E1` in den
Abstandstest `max(Ek) ≤ 1,25 × min(Ek)` ein. Die Regel ist eindeutig -- sie ist nur falsch,
und sie ist es an der Stelle, die *"trying to implement the tiniest socialist policy will
always result in bankruptcy"* beantworten soll. Der Fall ist billig zu schliessen: die
sechs Profile ausschliessen oder ihnen keinen Kern zuweisen.

---

## Kleinere Befunde

**9. Die Schwelle von Mass 3 liegt zwischen zwei erreichbaren Werten.** `Verschiebung =
Σ|p*i − q*i| / 5` mit ganzzahligen Profilvektoren, die beide auf 5 summieren. Die Summe der
Betraege ist dann stets **gerade**, die Verschiebung also aus `{0; 0,4; 0,8; 1,2; 1,6; 2,0}`.
Die Schwelle 0,5 verlangt damit in Wahrheit 0,8, also zwei verschobene Fuenftel statt
einem. Nicht falsch, aber die Kalibrierung zielt auf das Doppelte dessen, was dasteht;
gemeint ist vermutlich 0,4.

**10. Die Ergebnisskala ist an einer Stelle nicht streng geordnet.** Der Wert 28.000 traegt
zwei Ausgaenge: *"Mandat in Runde 28 erfuellt"* (`28 × 1.000`) und *"28 Runden ueberlebt,
Mandat nicht erfuellt"* mit einem Fehlbetrag, der in Promille auf 0 rundet. Dazu passt
Mass 2 nicht: *"Ein Profil **gewinnt**, wenn `E(p) < 28.000` -- also wenn es das Mandat im
Median erfuellt."* Die beiden Haelften dieses Satzes fallen genau bei einem Sieg in der
letzten Runde auseinander. T34 prueft nur den Gesamtbereich `1.000 … 58.000`, nicht diese
Kante.

**11. Die Kostenformel von Mass 1 ist um eine Runde je Stichprobe zu kurz.** `spiel.md`
sagt: *"Jedes Buendel wird gesetzt, dann laeuft die Partie ... bis Runde 28 durch"*, und
rechnet `30 × Σ(28−t)` fuer `t = 1…27` = 11.340. Wird das Buendel in Runde `t` gesetzt und
diese Runde noch gerechnet, sind es `29 − t` Schritte, also `30 × 405 = 12.150`. Die
Differenz ist fuer die Laufzeit belanglos (810 Schritte je Startwert), die dahinterstehende
Frage nicht: Sie entscheidet, ob Mass 1 die Entscheidung der Runde `t` oder die der Runde
`t+1` misst und ob die Drittel 1-9 / 10-19 / 20-27 die Runden meinen, die sie nennen.
`technik.md` uebernimmt die Formel unveraendert.

**12. Die Zuordnung der BACI-Warencodes zu den zwei handelbaren Modellsektoren fehlt.**
BACI liefert Stroeme nach HS92-Positionen; das Modell braucht zwei Sektoren, die ueber WDI
nach ISIC abgegrenzt sind. Weder `spiel.md` noch `technik.md` (Reihenliste Nr. 14 und 16)
nennen die Konkordanz. An ihr haengen der Handelsblock von Mass 4, die Startmatrix und der
Nenner aus Befund 3; ohne sie ist `handelsanteil` nicht einmal berechenbar.

---

## Wonach ich gesucht und was ich nicht gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar ist:

- **Die acht Befunde der ersten Pruefung, jeder einzeln.** Nr. 1 (Sektorgliederung): je
  Modellsektor genau eine WDI-Reihe, `NV.IND.MANF.ZS` ausgeschlossen, Normierung auf
  10.000, Zaehlung nachgerechnet (12 Sektoranteile, 8 unabhaengig; 31 − 4 = 27) --
  **sauber**. Nr. 2 (Startjahrgang): Frontmatter und Text sagen jetzt dasselbe --
  **formal behoben**, inhaltlich siehe Befund 1 oben. Nr. 3 (die Zahl 150): die
  Verteidigung steht nicht mehr auf einer Feldzahl, sondern auf sieben benannten
  Rueckkopplungskanaelen; T18 macht einen achten zum harten Fehler, T30 Pruefung 6 misst
  ihn -- **besser als verlangt**. Nr. 6 (Deckelung): ersatzlos gestrichen -- **sauber**,
  bis auf die Kante in Befund 10. Nr. 7 (Handelsmatrix): `5 × 4 × 2 = 40` in beiden
  Dokumenten -- **sauber**. Nr. 8 (Feldzaehlung): `4 × 44 + 22 + 56 + 52 + 4 = 310`
  **nachgerechnet und richtig**.
- **Nr. 4 und die Faehrte aus meinem Logbuch dazu.** Zu pruefen war, ob die Todesart
  Anlegerabzug fuer einen grossen Fonds unausweichlich wird und Gegenkraft 3 damit zur
  Obergrenze. Die Gewichtung nach Modellmarktwerten statt nach dem Fondsbestand vermeidet
  genau das: Die Ueberrendite geht **nicht** rechnerisch gegen null, die Kraft wirkt ueber
  den Preisstoss, der Ausweg ist benannt. **Faehrte geschlossen, kein Befund.**
- **Die fuenf Gegenkraefte gegen "Mechanismus statt Hoffnung".** Alle fuenf nennen den Weg
  und wachsen mit dem Erfolg. Neu nachgeprueft: Die drei Restdauerzaehler aus T15 machen
  Gegenkraft 1 und 2 ueberhaupt erst aufschreibbar und loesen zugleich den Konflikt mit
  T18, weil der Regierungswechsel Druck setzt statt den Instrumentstand ein zweites Mal in
  derselben Runde zu schreiben. **Kein Befund.**
- **Die vier Luecken aus `daten.md`, jede einzeln.** Luecke 1 jetzt richtig beantwortet;
  Luecke 2 und 4 stehen unter "Die Grenze des Orakels" und als Reihen 17/18 ohne Quelle;
  Luecke 3 ist so beantwortet, wie `daten.md` es verlangt -- kein erfundener Sektorzoll,
  Lizenzrisiko als schwerste offene Frage ausgewiesen, in T26 aufgefangen. Die
  Aufloesungsluecke ist zugunsten von Jahresrunden entschieden. **Kein Befund** -- die
  Antwort auf Luecke 3 haengt allerdings am Koeffizienten aus Befund 3.
- **Determinismus gegen Kriterium 3 aus `agentenbau.md`.** T4, T6, T9, T10, T11, T12, T28,
  T32 (ohne die kanonische Ordnung haenge Mass 1 an einer Schleifenreihenfolge), T35 samt
  benannter Restverzerrung der Modulo-Ziehung. Das haelt; T18 ist gegenueber Fassung eins
  ein echter Zugewinn. **Kein Befund.**
- **Die Rechenzeittabelle, Zeile fuer Zeile nachgerechnet.** `1.708 = 28 × 61`;
  `4.304.160 = 126 × 20 × 1.708`; `8.608.320` das Doppelte; `126 = C(9,4)`;
  `11.368 = 11.340 + 28`; `568.400 = 50 × 11.368`; Gesamtsumme
  `568.400 + 4.304.160 + 8.608.320 + 280.000 + 200 + 28 + 28.000 = 13.789.108` **exakt**.
  Auch die Kalibrierrechnung traegt. **Kein Befund** -- ausser der Grundzahl 28 (Befund 1)
  und der Formel (Befund 11).
- **Die Groesse gegen "die kleinste Fassung".** Vier Laender, drei Sektoren, fuenf
  Aktionsarten, vier Instrumente je einzeln verteidigt; "Was bewusst fehlt" nennt vierzehn
  Auslassungen mit Grund, die teuerste (Quartalstakt) mit Nennung des Verlusts und einem
  Ersatz. Vier gekoppelte Simulationsebenen liegen nicht vor. **Kein Befund.**
- **Hausregeln.** T21, T23, T3 (Abhaengigkeiten abschliessend, MIT oder Apache-2.0) und
  Abschnitt 11 (99 USD Apple-Beglaubigung und gehostete Bauumgebung ausdruecklich als
  Gate-Vorlage statt als Plan). Die Auslieferungsauflagen aus `daten.md` sind vollstaendig
  uebernommen und werden aus dem Manifest erzeugt. **Kein Befund.**

## Was ich nicht geprueft habe

- Die Belegtheit der uebrigen 28 Sollreihen ueber 1995-2023. Geprueft habe ich die zwoelf
  Sektoranteile stichprobenartig (USA vollstaendig, CN/BR/DE je die Agrarreihe). Der von
  `technik.md` T24 selbst genannte Verdachtsfall -- chinesische und brasilianische
  Leitzinsreihen der neunziger Jahre -- ist offen und koennte das Fenster aus Befund 1
  weiter verkuerzen. Das ist Arbeit des Datenbauers, aber sie gehoert **vor** die Festlegung
  der Partielaenge, nicht danach.
- Die Lizenzaussagen in `daten.md` -- nicht mein Gegenstand.
- Ob die Schwellen von Mass 4 (20 Prozent MAPE, 0,6 Richtungstreue) mit endogener
  Produktivitaet ueberhaupt erreichbar sind. Unveraendert das groesste ungemessene Risiko
  des Vorhabens; erst der Rueckvergleicher am laufenden Kern kann es beantworten.
- Die Zahlenwerte saemtlicher Schwellen. Sie gehoeren nach T27 in `parameter.toml` und
  werden kalibriert; das ist konsistent und richtig so.
