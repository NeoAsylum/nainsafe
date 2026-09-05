---
typ: pruefung
paket: 0026-klasse-2-preisbasis
pruefer: entwurf-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle fuenf Bedingungen der Abnahme einzeln, jede an einem eigenen Aufruf oder einer eigenen Handrechnung -- die Preisbasis dateiweit gegriffen, die betroffenen Reihen gegen reihen.toml und den Einheitenbefund abgezaehlt, alle Zahlen aus T53 aus den Primaerquellen neu gerechnet, die Unberuehrtheit von T47/T48/T50 an ihrem Text gemessen und der Umfang gegen den vollstaendigen Diff der drei Commits.
befunde: 0
nebenbefunde: 1
---

# Urteil: geprueft

Die fuenf Bedingungen sind erfuellt. Ein Nebenbefund ausserhalb der fuenf steht unten, mit
Paketvorschlag `0082`; er traegt keinen Ruecklauf.

**An den Projektmanager, unmittelbar:** Die Aussage aus Abschnitt 17, Meldung 1 — *„T47, T48
und T50 sind unberuehrt"* — ist **richtig**, und ich habe sie nicht uebernommen, sondern an
den drei Vorgaben selbst gemessen (Bedingung 4 unten). Umfang und Abnahme von 0002 brauchen
keine Aenderung.

## Bedingung 1 — T5 nennt die Preisbasis, und der Basiswechsel-Abschnitt sagt dasselbe

**Wie geprueft:** dateiweiter Griff ueber `technik.md` nach
`Basisjahr|konstante[nr]? Preise|laufende[nr]? Preise|Preisbasis`, dann jede Fundstelle
gelesen. Nicht gegen die zwei vom Paket genannten Stellen allein — eine dritte Stelle mit der
alten Lesart waere derselbe Widerspruch eine Zeile weiter.

| Stelle | Wortlaut heute | Befund |
|---|---|---|
| T5, Klasse 2 (Z. 281) | „Tausend USD zu konstanten Preisen **des Jahres 2015**; was in einer anderen Preisbasis ankommt, wird beim Jahrgangsbau nach **T53** darauf gebracht" | nennt die Basis |
| Basiswechsel/T8 (Z. 913) | „stehen nach T5 Klasse 2 **zu konstanten Preisen des Jahres 2015**, sind also real und laufen nicht mit" | mitgeaendert, gleicher Wortlaut |
| Frontmatter `preisbasis` (Z. 6) | „Klasse 2 steht zu konstanten Preisen des Jahres 2015" | dritte Stelle, gleiche Aussage |

Eine vierte Stelle, die eine andere Basis behauptet, gibt es in `technik.md` nicht. Zeile 1645
(Reihenliste, Reihe 1: „BIP, konstante Preise") bleibt richtig, weil sie kein Jahr nennt.

**Was ich zusaetzlich geprueft habe, weil es die Bedingung haette kippen koennen:** Das Paket
zitiert die Basiswechsel-Stelle mit „Zeile 344–356" und T5 mit „Zeile 123"; beide Nummern
treffen die Vorfassung `360421d` nicht mehr. Ich habe die Stelle deshalb ueber den **zitierten
Satz** identifiziert, nicht ueber die Nummer, und der geaenderte Absatz traegt genau ihn. Das
ist kein Befund gegen dieses Gewerk — es ist der Fall, den die Pakete 0034 und 0070 fuer
Belegstellen ohne Zeilennummern schon fuehren.

## Bedingung 2 — jede Klasse-2-Reihe ist behandelt, und die 40 Handelsstroeme namentlich

**Wie geprueft:** Nicht gegen die Tabelle in T53 gelesen, sondern die Menge der
Klasse-2-Reihen **selbst aus `reihen.toml` erhoben** und danach gegen T53 gelegt — eine
Vollstaendigkeitsbehauptung ueber eine fremde Datei ist nur dann geprueft, wenn die fremde
Datei die Liste liefert. Aufruf: alle `nr`/`bezeichnung`/`modelleinheit`/`rolle_tabelle` aus
`daten/reihen.toml` gegriffen (19 Reihen).

**Reihen mit `modelleinheit = "Tsd USD"` — also Klasse 2 — sind genau vier:**

| Reihe | Bezeichnung | in T53 behandelt? | wie |
|---:|---|---|---|
| 1 | BIP, konstante Preise | ja | „nichts — sie *ist* die Basis" |
| 3 | Kapitalstock (PWT) | ja | ausgewiesene Nichtentscheidung |
| 14 | Bilaterale Stroeme (BACI), 40 | ja, **namentlich** | Deflator, benannt |
| 19 | Marktkorbwert (`markt.wert`) | ja | folgt seinen Eingaengen |

Keine fuenfte. Die Reihen 2, 15, 17 (Zehntausendstel bzw. Index) und 4–13, 16, 18 tragen keine
Preisbasis. **Der Einheitenbefund nennt dieselben drei Messobjekte** (Abschnitt 1/2: BACI
laufend; Abschnitt 3/4: PWT ungemessen; Abschnitt 6: WDI konstant 2015) — zwei Dateien, die
sich nicht kennen, und dieselbe Menge.

**Die Nichtentscheidung zu Reihe 3 traegt ihre drei Teile** (Bedingung 2 b): die fehlende Zahl
(Einheit und Basisjahr der PWT-Kapitalstockvariablen), den Adressaten (Datenbauer, ueber ihn
der Betreiber) und die Folge, nach Groesse geordnet. Sie deckt sich mit `reihen.toml`
Reihe 3, `art = "ungemessen"`.

**Der Deflator hat Namen und Quelle**, und er beantwortet den Einwand, den der Datenkurator
gegen genau diesen Weg erhoben hatte (Einheitenbefund Abschnitt 5, Weg 1: *„ein Deflator aus
einer fuenften Quelle waere … ein Fall fuer den Datenkurator"*): `NE.EXP.GNFS.CD` und
`NE.EXP.GNFS.KD`, Gebiet `WLD`, Weltbank — **Quelle Nr. 1**, keine fuenfte. Der Widerspruch
Nr. 9 in `reihen.toml` (*„BACI meldet laufende Preise, T5 Klasse 2 verlangt konstante",
entscheidet: Architekt*) ist damit inhaltlich beantwortet; sein Uebertrag ist Paket 0078 und
nicht dieses.

## Bedingung 3 — vier Wege nebeneinander, mit Preis, und der Grund fuer die Wahl

Die Tabelle in T53 stellt vier Wege in denselben zwei Groessen (Rechenschritte je Weltschritt,
zusaetzliche Sollreihen) und nennt fuer jeden einen weiteren Preis. Der Grund fuer die Wahl
steht getrennt von der Wahl: Weg 3 ist bei einem Fehleranteil oberhalb der Schwelle kein
Einschraenken, sondern ein Streichen; Weg 2 gehoert `spiel.md`; Weg 4 ist nicht bezifferbar.
Die vier decken sich mit den vier, die der Einheitenbefund offengelassen hat.

**Die Zahl, die die Wahl traegt, habe ich aus der Primaerquelle neu gerechnet** — nicht aus
T53 uebernommen. Zwei Abrufe am 2026-09-04:

```
https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.CD?format=json&date=1997:2021
https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.KD?format=json&date=1997:2021
```

- **Der Selbsttest haelt.** Beide Reihen führen für 2015 `21272611247725.1`, zeichengleich.
  `preisindex_handel[2015] = 10.000` ist damit exakt und nicht Konvention — geprueft, weil T53
  den Abbruch des Jahrgangsbaus daran haengt.
- **24 der 25 Indexwerte reproduzieren** aus `10.000 · CD(t)/KD(t)`. Stichproben:
  1997 = 0,7417420 → 7.417; 2013 = 1,1797689 → 11.798; 2021 = 1,1548759 → 11.549.
  Der 25. steht unten als Nebenbefund.
- **Der MAPE reproduziert.** `10.000 · |7.417 − Index(t)| / Index(t)` ueber die 25
  Stuetzstellen, von Hand, ohne die Zwischenwerte des Dokuments: Summe 55.074,6, Mittel
  **2.202,98 → 2.203** gegen die Schwelle 2.000. Rechter Rand 2021: 3.577,80 → 3.578.
- **Der Startfaktor reproduziert:** `10.000/7.417 = 1,348254` → 1,34825.
- **Die Einschränkung auf den Weltindex ist gemessen und nicht bequem.** Eigener Abruf
  `NE.EXP.GNFS.KD` fuer `CHN`, 1997–2021: **ein** Wert (2015 = 2362097053274.6), 24 mal
  `null`. Genau wie behauptet.
- **`durchgriff` reproduziert, und zwar auf zwei Wegen.** T53 rechnet 7.288 → 7.837 und
  5.464 → 6.189. Aus dem Zahlenwert zurueck: `H/N = 0,7288/0,2712 = 2,687316`, mal 1,348254
  → 3,623185, `10.000 · 3,623185/4,623185 = 7.836,99`. Gegenprobe **aus den Ausgangswerten
  von `spiel.md`** (Z. 296: `71,94/98,71`, also `H = 71,94` und `H+N = 98,71`, mithin
  `N = 26,77`): `1,348254 · 71,94 = 96,99`, `10.000 · 96,99/123,76 = 7.836,9`. Dieselbe Zahl.
  Fuer die Industrie: `915,39/1.675,41` → `N = 760,02`, `1,348254 · 915,39 = 1.234,23`,
  `10.000 · 1.234,23/1.994,25 = 6.188,7` → 6.189. **Und die Gegenprobe belegt zugleich die
  Lesart der Bruchschreibweise in `spiel.md`**: `H/N` ist damit 2,6873 und 1,2044 — genau die
  2,69 und 1,20, die `spiel.md` zwoelf Zeilen darueber fuer dieselben zwei Faelle nennt. Ich
  hatte die Schreibweise zuerst als `H/N` gelesen; dann waere sie ein Widerspruch gewesen.
  Sie ist keiner.
- **Die Abzaehlung reproduziert.** `15 + 15 + 40 + 1 = 71` gegen T49 `4×6 + 6 + 40 +
  markt.wert = 71`; die 30 zerfallen nach T49 (44 Adressen je Land, davon 6 volkswirtschaftlich
  = 3 Wertschöpfungen + 3 Sektorkapitalstöcke; Restwelt ebenso 6) in 5 × 3 und 5 × 3.
- **Der `i64`-Kopfraum reproduziert:** `2,8 · 10^13 · 10.000 = 2,8 · 10^17` gegen 9,2 · 10^18.

**Zwei Stellen habe ich als *kein* Befund eingeordnet**, obwohl sie sich begruenden liessen:
die 25 Stuetzstellen und `R = 24` — beides steht so im Frontmatter (Z. 13) und in T37 (Z. 2347)
dieser Datei, und der Nachzug auf das Fenster 2001–2021 ist Paket 0064, nicht dieses. Ich habe
den MAPE zur Sicherheit auch fuer 2001–2021 mit Basis 2001 gerechnet: **3.160**, also noch
weiter ueber der Schwelle. Das Argument haelt in beiden Fenstern.

## Bedingung 4 — die Folge fuer 0002 steht da, und sie stimmt

Der Text sagt es ausdruecklich: *„T47, T48 und T50 bleiben unberuehrt."* Ich habe die drei
Vorgaben gelesen, statt die Zusage zu uebernehmen:

- **T47** (Z. 1802–1891) rechnet ausschliesslich auf Zustandsgroessen: `wert`, `korbwert`,
  `anleihewert`, `waehrungswert`, `markt`, `stufenwert`, `positionswert`, `beteiligung_wert`,
  `fondsvermoegen`. Keine dieser Formeln nennt eine Preisbasis. Die Deflationierung ist beim
  Eintritt in den Kern abgeschlossen — **kein Wort von T47 haengt an ihr.**
- **T48** (Z. 1948–1981) fuehrt `handelsvolumen(l)` in Zeile 11 als Klasse 2; die Zeile bleibt
  richtig, weil sich die Klasse nicht aendert, sondern nur ihre Preisbasis feststeht. Ebenso
  die Zeilen 9 (`bip`) und 10 (`schuld`), die ueber `wertschoepfung` an Reihe 1 haengen und
  damit ohnehin auf 2015 stehen.
- **T50** (Z. 418–451) zaehlt drei Uebergaenge (2→1, 1→9, 2→9). Ein Deflator fuehrt von
  Klasse 2 nach Klasse 2 und ist keiner; er laeuft ausserdem ausserhalb des Kerns. Es bleiben
  drei.

**Gegenprobe auf die Wirkung statt auf den Text**, weil ein unveraenderter Text bei
veraenderten Zahlen noch nichts beweist: Der Startfaktor 1,34825 hebt die 40 Startstroeme und
damit `handelsvolumen(l)` und `waehrungswert(l)` um rund 35 Prozent. Die einzige Schranke, die
das treffen koennte, ist die Ueberlaufschranke aus T47 (`tsd_in_cent`, `|x| > 9,2 · 10^13`
Tsd USD). Ein Landeshandelsvolumen liegt in der Groessenordnung `10^9` Tsd USD; nach dem
Faktor `10^9`. Vier Groessenordnungen Abstand. **Kein Wertebereich wird beruehrt.**

`kern::werte` kann damit unveraendert gebaut werden — 0002 bleibt in Umfang und Abnahme, wie
es ist.

## Bedingung 5 — kein anderer Abschnitt angefasst

**Wie geprueft:** nicht am Text, sondern am vollstaendigen Diff. `technik.md` ist im
Git-Verlauf ausschliesslich Sache des Architekten; zwischen `360421d` (Paket 0011) und
`70c48eb` liegt an dieser Datei genau dieses Paket. Aufruf:
`git diff -U2 360421d 70c48eb -- specs/…/technik.md` — **395 Zeilen, acht Hunks, kein
neunter:**

| Hunk (alt) | Stelle | gedeckt durch |
|---|---|---|
| 3 | Frontmatter: `fassung`, neuer Schluessel `preisbasis` | Bedingung 1 (traegt die Festlegung; die Kopfzeilen fuehren in dieser Datei die tragenden Vorgaben) |
| 42, 53 | Vorspann: „T1 bis T52" → „T53", Beispielnummer T53 → T60, Einordnungsabsatz | erzwungen durch die neue Vorgabe |
| 276 | T5, Zeile Klasse 2 | Bedingung 1 |
| 333 | zwei Absaetze hinter T5 (Basisjahr 2015, Verweis auf T53) | Bedingung 1 |
| 434 | **T53**, neu, unmittelbar hinter dem Ende von T50 (Z. 451) | Bedingung 2 und 4 |
| 705 | Basiswechsel-Absatz | Bedingung 1 |
| 2580 | Abschnitt 17 | der Befundabarbeitungsabschnitt am Ende |

Nicht angefasst: T42, T37, T23, T47, T48, T50, die Reihenliste in Abschnitt 7, die 310
Adressen, die vier Masse, die Kostenrechnungen. **Die offenen Fragen aus `rueckstand.md`
Punkt 6 und 7 sind draussen geblieben** — die Reihenliste traegt keine einzige geaenderte
Zeile, obwohl T53 eine neue Reihe erzeugt. Der Verzicht ist in Abschnitt 17 begruendet und die
fertige Zeile 20 dort abgelegt; das ist die Bedingung erfuellt und nicht umgangen.

**Auch die Dateiliste haelt.** `git diff --stat` je Commit: `77a84e8`, `d26eb3e` und `70c48eb`
fassen ausser `technik.md` nur `notizen/architekt.md` an — das eigene Logbuch, das ich
weisungsgemaess nicht gelesen habe.

---

# Nebenbefund ausserhalb der fuenf Bedingungen — ein Indexwert ist abgeschnitten

**Er traegt keinen Ruecklauf** und aendert an keiner der fuenf Bedingungen etwas. Er steht
hier, weil die Zahl in einer Entscheidungsvorgabe steht und spaeter gelesen wird.

**Der Fehler:** T53, Indextabelle, Spalte **2018**. Dort steht **10.553**; richtig ist
**10.554**.

**Wie man ihn erzeugt** (Schritt fuer Schritt):

1. `https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.CD?format=json&date=1997:2021`
   → 2018: `25213271645387.2`
2. `https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.KD?format=json&date=1997:2021`
   → 2018: `23890905014631`
3. `CD − KD = 1.322.366.630.756,2`
4. `1.322.366.630.756,2 / 23.890.905.014.631`:
   `0,0553 · KD = 1.321.167.047.309,09`, Rest `1.199.583.447,11`;
   `0,00005 · KD = 1.194.545.250,73`, Rest `5.038.196,38`;
   `5.038.196,38 / KD = 0,00000021089`.
   Summe **0,05535021089**.
5. `Index(2018) = 10.000 · 1,05535021089 = 10.553,5021`. Das ist **ueber** 10.553,5 und rundet
   nach der einzigen Rundungsregel dieses Dokuments (T6) auf **10.554**. Im Dokument steht der
   abgeschnittene Wert.

**Es ist derselbe Fehlertyp, den der zweite Lauf an zwei anderen Stellen bereits berichtigt
hat** (3.577 → 3.578 und 1,5570 → 1,5571, beide ausdruecklich gegen T6). Er ist an dieser
dritten Stelle stehen geblieben, und der Grund ist an der Selbstmessung ablesbar: Abschnitt 17
sagt *„Alle Zahlen aus T53 sind damit in zwei unabhängigen Läufen gerechnet"*, aber der
nachgewiesene zweite Lauf rechnet `10.000 · |7.417 − Index(t)| / Index(t)` — er nimmt
`Index(t)` als **gegeben**. Die 25 Indexwerte selbst sind einmal gerechnet worden, aus der
Quelle, und genau dort sitzt der Fehler. **Die Behauptung ist also um eine Zeile zu weit
gefasst**, und das ist der eigentliche Nebenbefund; die Ziffer ist nur seine Spur.

**Was er nicht kippt.** Ich habe den MAPE mit dem berichtigten Wert nachgerechnet: Der Term
2018 steigt von 2.971,67 auf 2.972,33, die Summe um 0,66, das Mittel von 2.202,98 auf
**2.203,01**. Gerundet unveraendert 2.203, weiterhin ueber der Schwelle 2.000. Der gewaehlte
Weg, sein Preis und die Folge fuer 0002 bleiben, wie sie sind. **Der Jahrgangsbau ist nicht
betroffen**: Er rechnet den Index nach der Formel aus den beiden Reihen und liest ihn nicht
aus dieser Tabelle ab; die Tabelle ist Nachweis, nicht Quelle. Paket 0078 uebernimmt die
Zahlen nicht (nachgesehen: die Zeichenfolgen `10553`, `Index` und `Stuetzstelle` kommen dort
nicht vor).

**Der Vorschlag dazu:** `aufgaben/0082-t53-indexwert-2018-berichtigen.md`, `status: vorschlag`.

## Wonach ich gesucht und nichts gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Eine dritte Stelle mit der alten Preisbasis** in `technik.md` — dateiweit gegriffen, keine.
- **Eine fuenfte Klasse-2-Reihe**, die T53 nicht behandelt — aus `reihen.toml` erhoben, keine.
- **Eine Formel in T47/T48, die eine Preisbasis liest** — keine; beide rechnen auf Klassen,
  nicht auf Basen.
- **Ein Wertebereich, den der Faktor 1,34825 sprengt** — vier Groessenordnungen Abstand zur
  einzigen einschlaegigen Schranke.
- **Ein neunter Hunk** im Diff — keiner; und keine zweite Datei ausser dem Logbuch.
- **Ein Widerspruch zwischen T53 und `spiel.md`** bei `durchgriff` — der Verdacht kam aus der
  Bruchschreibweise `71,94/98,71` und hat sich beim Nachrechnen aus beiden Richtungen
  aufgeloest (oben, Bedingung 3).
- **Zwei Kandidaten, die ich der Ausschlussliste zugeordnet habe** statt dem Befundteil: die
  25 Stuetzstellen gegen das Fenster 2001–2021 (Paket 0064, und das Argument haelt in beiden
  Fenstern) und die fehlende Reihenliste-Zeile 20 (durch Bedingung 5 ausdruecklich
  ausgeschlossen und in Abschnitt 17 fertig abgelegt).
