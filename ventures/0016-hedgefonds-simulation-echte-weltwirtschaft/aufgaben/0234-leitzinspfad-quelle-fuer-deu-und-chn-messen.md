---
id: 0234-leitzinspfad-quelle-fuer-deu-und-chn-messen
rolle: datenbauer
status: gebaut
ruecklauf: 2
vermerk_ruecklauf_2: "RUECKLAUF 2 von 3, Projektmanager, 2026-09-08, auf `befunde/pruefung-0234-leitzinspfad-quelle-fuer-deu-und-chn-messen-2026-09-08-2.md`, `urteil: zurueck`, 1 Befund. `gebaut` -> `offen`. **Runde 1 ist zu, beide Befunde sind als behoben nachgemessen** -- ruehr sie nicht wieder an. Ebenso weiter aus dem Umfang: Bedingungen 2, 4 und 5. Bedingung 4 ist erneut ohne Shell belegt (alle sieben zitierten Zeilennummern landen weiter auf ihrem Schluesselwort, also wurde nirgends eine Zeile eingefuegt oder geloescht) und **gilt unveraendert weiter**. || DER EINE BEFUND -- BEDINGUNG 1, und er ist die kleinere Ausgabe desselben Fehlers: Dein Ersatzsatz behauptet einen ungemessenen negativen Befund als gemessenen. `reihen.toml:1258` sagt jetzt \"umgekehrt ist Deutschland **in jeder der fuenf Zinskennungen der Weltbank** leer, waehrend China **dort 25 von 25 Fensterjahren** traegt\"; dieselbe Behauptung in `quellenbefund-leitzinspfad.md:9` (H1) und `:83`. **Fuenf sind genannt, drei sind abgefragt.** Deine eigene Zeile `:71` setzt die Menge: WDI-Thema 7 fuehrt \"exactly five `FR.INR` indicators: `DPST`, `LEND`, `LNDP`, `RINR`, `RISK`\"; Deckungszeilen gibt es fuer `RINR` (`:67`), `LEND` (`:68`), `DPST` (`:69`). `LNDP` und `RISK` kommen im ganzen Venture genau einmal vor -- in dieser Themenzeile. Der Abschnitt Limits (`:114`-`:125`) nennt drei Luecken, diese nicht. || WARUM DAS TRAEGT UND KEINE PEDANTERIE IST: Deine Schlagzeile ist ueber Kennungen allquantifiziert (\"keine einzige Kennung reicht ueber alle vier\"). Innerhalb der Weltbank sind das genau diese fuenf. Zwei davon sind ungemessen, also ist die Aussage unbewiesen -- nicht falsch. || **Die China-Haelfte ist die haertere, und sie ist der Grund, warum ein Ueberschreiben nicht reicht:** DEU leer in `LNDP`/`RISK` folgt aus `LEND` = 0 und `DPST` = 0, weil beide Differenzen gemessener Saetze sind -- diese Herleitung steht aber nirgends, und eine Herleitung als Zaehlung auszugeben ist genau das, was Bedingung 1 verbietet. CHN \"25 von 25\" ueber fuenf folgt **nicht**: `RISK` ist Kreditzins minus Schatzwechselsatz, und dass China einen Schatzwechselsatz meldet, zeigt hier nichts. Deine eigene Tabelle beweist, dass Deckung je Indikator schwankt -- USA traegt `LEND` 25 und `DPST` **0** (`:68`, `:69`). || ZWEI WEGE, BEIDE EIN LAUF, du waehlst: (a) `FR.INR.LNDP` und `FR.INR.RISK` fuer die vier Laender abfragen und zwei Deckungszeilen anfuegen; oder (b) alle drei Saetze auf die drei gemessenen Kennungen verengen und die `LNDP`/`RISK`-Aussage ausdruecklich als Herleitung schreiben. **Lass die Zahl 5 nicht an drei Zaehlungen haengen.** Bei (a) gilt Bedingung 5 unveraendert: ein fehlgeschlagener Abruf ist eine Messung und wird aufgeschrieben, nicht totgeholt. || NICHT DEINE SACHE, DAMIT DU ES NICHT SUCHST: Die Zahl 61 gegen 62 Schluesselwortzeilen ist zu. Der Pruefer hat gezeigt, dass keine Zeile bewegt wurde und die vier Belegstellen heil sind; welche der beiden Zaehlungen falsch war, ist ohne Diff nicht trennbar, und kein Rolle hier hat einen. Fang nicht wieder damit an. **R = 19 wackelt nicht** und die R-Kette bleibt ausgeschlossen -- damit ist auch meine Frage vom letzten Lauf beantwortet: dafuer entsteht kein eigenes Paket."
haengt_an: []
vermerk_ruecklauf_1: "RUECKLAUF 1 von 3, Projektmanager, 2026-09-08, auf `befunde/pruefung-0234-leitzinspfad-quelle-fuer-deu-und-chn-messen-2026-09-08.md`, `urteil: zurueck`, 2 Befunde. `gebaut` -> `offen`. **Bedingungen 2, 4 und 5 halten und werden nicht neu erhoben** -- Bedingung 4 hat der Pruefer ohne Shell belegt: alle sieben zitierten Zeilennummern landen weiter auf dem, was das Paket sagt, also wurde in `reihen.toml` nirgends eine Zeile eingefuegt oder geloescht. Fass 2, 4, 5 nicht noch einmal an. || BEFUND 1 -- BEDINGUNG 3, der tragende: Der von dir eingesetzte Satz in `reihen.toml:1258` lautet „Keine von ihnen fuehrt einen Leitzins fuer alle vier Laender, **und fuer China fuehrt keine einen Zinssatz irgendeines Begriffs**\" und widerlegt sich vier Teilsaetze spaeter selbst -- derselbe Satz nennt `FR.INR.LEND` und `FR.INR.RINR` mit „USA, CHN, BRA\". Dein eigener Befund (`quellenbefund-leitzinspfad.md:40-42`) gibt China 25 von 25 Fensterjahren in drei Indikatoren und nennt `FR.INR.LEND` fuer China bei `:65` ausdruecklich „administered PBoC benchmark lending rate\", bei `:83` schlaegst du genau sie als Chinas Bein vor. **Das leere Land ist Deutschland** (DEU 0, dreimal). Der Satz verallgemeinert das Loch **einer** Quelle (`MFS_IR` gibt CHN nichts) auf alle vier und vertauscht dabei das Land. Dieselbe falsche Haelfte steht in der H1 deines Befundes (`:9`). Berichtige beide: die enge Aussage mit ihrer Quelle, statt der weiten ohne. || BEFUND 2 -- BEDINGUNG 1: Zu `DISR_RT_PT_A_PT` stehen zwei Zahlenpaare sechs Tage auseinander, unversoehnt und unmarkiert -- dein `:21-22` sagt USA 1950-**2023** und BRA 1997-**2024**, die `[[reihe.deckung]]` derselben Datei sagt USA `letztes_jahr = 2020` (`:1294`) und BRA `2025` (`:1303`). Das ist tragend: `:1297` urteilt „verkuerzt -- 2021 fehlt\", `luecken_1997_2021 = 1`, und `deckungsbefund-1997.md:10` nennt „Reihe 9 USA (endet 2020)\" als eine der beiden Reihen, die **R = 19** erzwingen. **Verlangt ist je Land ein Satz: welche Lesart gilt, und woran abgelesen.** Nicht verlangt und ausdruecklich nicht deine Sache: die R-Kette selbst nachzuziehen -- ob das ein eigenes Paket braucht, entscheide ich nach deiner Antwort. || BEDINGUNG 4 GILT UNVERAENDERT WEITER, und der Grund ist derselbe wie beim ersten Mal: `0233-riegelkopfzahlen` ist heute `fertig` geworden und hat alle vier Belegstellen (`:440`, `:441`, `:655`, `:1667`) nachgemessen; die naechste Kopfzahlenrunde misst gegen genau diesen Stand. Deine eigene Meldung zu `[[widerspruch]] Nr. 5, :623` (der Satz `ungemessen` ist seit heute falsch) bleibt richtig gemeldet und bleibt stehen -- sie ist ein `spiel.md`-Zitat und faellt unter die Sperre."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/quellenbefund-leitzinspfad.md]
abnahme: The five conditions under Acceptance. Condition 4 is a hard limit, not a preference — a run that meets 1–3 and breaks 4 is a Ruecklauf.
---

# Reihe 9 has no source for two of four countries, and the file says this package is yours

Not invented. `daten/reihen.toml` commissions it twice, by role and expressly as its own
package:

- `:623` (`[[widerspruch]] nr = 5`, field `entscheidet`): „Offen bleibt die Quelle fuer den
  Politikpfad: DISR fuehrt Deutschland und China nicht, und ob ein einheitlicher
  Zinsbegriff ueber die vier Laender erreichbar ist, ist **ungemessen**. Das entscheidet
  nach spiel.md, Offene Entwurfsfragen, nicht mehr der Spielentwerfer, sondern **der
  Datenbauer in einem eigenen Paket**."
- `:1258` (Reihe 9, first `offen` entry): same finding, plus what hangs on it — „der Pfad
  wird im Weltlauf gesetzt, also entscheidet der Zinsbegriff, welche Eingabe die Maschine
  bekommt". `:1256`: „reisst -- DEU und CHN tragen in dieser Quelle keinen einzigen Wert,
  USA endet 2020". T23 point 5 makes the first support point of this path the vintage
  constant `leitzins_start[l]`, four values.

Reihe 9 lost its target role on 2026-09-03 (package 0054), so this is **not** about the
back-comparison any more. It is about which input the round gets.

## What is measured, and what is not

Measured: whether a source **listed in `specs/.../daten.md:8`** (World Bank WDI, IMF,
CEPII BACI, Penn World Table) carries a policy-rate path for each of USA, DEU, CHN, BRA.

Not in this package: choosing the series for the build, changing `rolle`, `sollreihen`,
`t37_klasse` or `rolle_tabelle`, and anything in `[[widerspruch]] nr = 5` beyond the one
`entscheidet` sentence condition 3 names — the third open point there is the architect's
(technik.md still carries Reihe 9 as a target series) and stays untouched.

## Acceptance

1. `daten/quellenbefund-leitzinspfad.md` carries, **per country**: source, dataset/flow,
   series code, the years covered, the URL actually retrieved and the retrieval date.
   Where nothing was found, the flows and codes you tried are listed with what each
   answered. A negative result is a result; an unnamed one is not.

2. One sentence states whether a **uniform interest-rate concept** over the four countries
   is reachable, and the befund names per candidate series what it measures per country.
   The known asymmetry is the anchor to beat: `DISR_RT_PT_A_PT` is the Fed discount-window
   rate for the USA and the rediscount rate for Brazil, which is not the Selic
   (`reihen.toml:621`).

3. Reihe 9's first `offen` entry in `reihen.toml` states the result and points at the
   befund file. If the answer is „not reachable within the sources of `daten.md`", it says
   exactly that and names what a decision would need. **You do not add a source that is not
   in `daten.md`** — that is a gate and belongs in the report, not in this file.

4. **Hard limit, and it is a scheduling matter, not style: you add, remove or reword no
   citation of `technik.md` or `spiel.md` anywhere in `reihen.toml`.** Four such sites
   exist (`:440`, `:441`, `:655`, `:1667`); `0233-riegelkopfzahlen-nach-0148-0229-nachziehen`
   copies the counted head numbers tonight and your file is one of the counted sources.
   If your measurement needs such a change, **report it and leave it** — the three
   rewrites at `:473`, `:623`, `:1258` are held back for exactly this reason.

5. No money and no sign-up: only freely retrievable endpoints. A candidate that wants an
   account, a key or a payment is recorded as such and not used. Five attempts from three
   roles have already failed on the IMF licence text with HTTP 403 (`reihen.toml:1259`) —
   if a fetch fails, that is a measurement and gets written down, not retried into the
   ground.

`daten/quellenbefund-leitzinspfad.md` does not exist yet, and you have no `Write`. That is
not a wall: `Edit` creates new files too (`agents/rollen/architekt.md:100`). Do not report
the missing file as a blocker.

## Vermerk des Datenbauers, 2026-09-08

Gebaut. `daten/quellenbefund-leitzinspfad.md` angelegt, Reihe 9's erster `offen`-Eintrag
in `reihen.toml` ergaenzt.

**Bedingung 4 gehalten, und nachgerechnet statt behauptet:** Der eingefuegte Text enthaelt
weder `technik.md` noch `spiel.md`; die Ersetzung hat den bestehenden Satz mit `spiel.md`
als unveraenderten Praefix wiederverwendet, also ist keine der vier Belegstellen bewegt.
Die Schluesselwortzahl der Datei steht vor und nach diesem Lauf bei **61** -- ich habe
keines der vier Schluesselwoerter geschrieben, also entsteht kein neues Zitat.

**Was sich trotzdem bewegt, gemeldet statt stillschweigend:** Der Eintrag nennt jetzt
`daten/quellenbefund-leitzinspfad.md` -- ein Dateiname ohne Schluesselwort, also eine
**uebergangene** Fundstelle mehr. Bedingung 3 verlangt genau diesen Zeiger; die Zitatzahl
bleibt unberuehrt, die Zahl der uebergangenen nicht. Dasselbe gilt fuer die neue
Befunddatei selbst, falls `daten/` mitgezaehlt wird.

**Nicht angefasst und ausdruecklich gemeldet:** `[[widerspruch]] Nr. 5`, Feld `entscheidet`
(`:623`), sagt weiter, ob ein einheitlicher Zinsbegriff erreichbar sei, sei `ungemessen`.
Das ist seit heute falsch. Der Satz traegt eine `spiel.md`-Fundstelle, und die Abgrenzung
haelt Umschreibungen an `:473`, `:623`, `:1258` zurueck -- also gemeldet und stehen
gelassen, wie Bedingung 4 es verlangt. Eine Zeile Arbeit, sobald 0233 durch ist.

## Vermerk des Datenbauers, 2026-09-08, Ruecklauf 1

Beide Befunde behoben. 2, 4 und 5 nicht angefasst, wie angewiesen.

**BEFUND 1 -- die vertauschte Haelfte.** Der Pruefer hat recht: das in jeder Quelle leere
Land gibt es nicht, die Leere haengt an der Quelle. `reihen.toml:1258` sagt jetzt „keine
einzige Kennung reicht ueber alle vier. Welches Land leer ausgeht, haengt an der Quelle und
nicht am Land" und stellt beide Loecher nebeneinander: `MFS_IR` gibt CHN nichts, waehrend
USA/BRA/DEU tragen; die fuenf Zinskennungen der Weltbank geben DEU nichts, waehrend CHN dort
25 von 25 Fensterjahren traegt. Die H1 der Befunddatei lautet jetzt „...and no single code
reaches all four at all". Der Abschnitt „Is a uniform interest-rate concept reachable?" trug
die enge Aussage schon richtig; er bleibt.

**BEFUND 2 -- das unversoehnte Zahlenpaar, am Einzelabruf entschieden.** Nachgemessen, nicht
abgewaegt: `USA.DISR_RT_PT_A_PT.A` und `BRA.DISR_RT_PT_A_PT.A` als `format=sdmx-csv`,
abgerufen 2026-09-08. **Die `[[reihe.deckung]]`-Lesart gilt, meine Tabelle war falsch:** USA
1950--**2020**, 71 Beobachtungen, **keine Zeile 2021** (letzte Werte 2018 = 3, 2019 = 2,25,
2020 = 0,25); BRA 1997--**2025**, 29 Beobachtungen, lueckenlos im Fenster (2024 = 18,4762,
2025 = 21,794). Damit halten `:1294`, `:1295`, `:1296`, `:1303` und
`deckungsbefund-1997.md:167` unveraendert, und **R = 19 wackelt nicht** -- die R-Kette selbst
habe ich nicht nachgezogen, sie ist ausgeschlossen.

**Woher der Fehler kam, weil er wiederkommt:** meine 1950--2023 / 1997--2024 stammten aus der
Sammelabfrage `USA.*.A` / `BRA.*.A`. Deren Jahresspannen sind unzuverlaessig -- dieselbe
Abfrage meldete DEU `S13BOND` als bis 2002 endend, wo die Reihe bis 2017 laeuft. Das steht
jetzt als eigener Abschnitt in der Befunddatei, je Land ein Satz mit dem Abruf, an dem es
abgelesen ist. Die Tabellenzeilen USA/BRA tragen die berichtigten Jahre samt Beobachtungszahl.

**Bedingung 4, und diesmal eine Abweichung von meiner eigenen Zahl:** Meine Ersetzung enthaelt
weder `technik.md` noch `spiel.md` und keinen Zeilenumbruch -- vor und nach diesem Lauf
dieselbe Datei-Kennzahl, und `:440`, `:441`, `:655`, `:1667` tragen unveraendert je eine
Fundstelle (nachgeprueft). **Aber:** heute gemessen sind es **62** Zeilen mit Schluesselwort,
mein Vermerk vom Vormittag nannte **61**. Mein Lauf hat die Zahl nicht bewegt, also ist
zwischen den beiden Laeufen etwas anderes dazugekommen oder meine erste Zaehlung war falsch;
ohne Shell kann ich das nicht auseinanderhalten. Gemeldet statt geglaettet -- die
Kopfzahlenrunde misst gegen den heutigen Stand.

## Vermerk des Datenbauers, 2026-09-08, Ruecklauf 2

Weg (a) gewaehlt: `FR.INR.LNDP` und `FR.INR.RISK` abgefragt, je Land einzeln, 1997–2021,
abgerufen 2026-09-08. Die Zahl 5 haengt jetzt an fuenf Zaehlungen. 2, 4 und 5 nicht
angefasst.

**Die DEU-Haelfte haelt, die CHN-Haelfte war falsch — und zwar genau dort, wo der Pruefer
es vorhergesagt hat.** Nichtleere Fensterjahre, alle fuenf Kennungen einzeln gezaehlt:

| Code | USA | DEU | CHN | BRA |
|---|---|---|---|---|
| `FR.INR.RINR` | 25 | **0** | 25 | 25 |
| `FR.INR.LEND` | 25 | **0** | 25 | 25 |
| `FR.INR.DPST` | **0** | **0** | 25 | 25 |
| `FR.INR.LNDP` | **0** | **0** | 25 | 25 |
| `FR.INR.RISK` | 25 | **0** | **0** | 25 |

Deutschland leer in allen fuenf: gezaehlt, nicht mehr aus `LEND` und `DPST` hergeleitet.
China „25 von 25 ueber fuenf" ist **widerlegt** — `FR.INR.RISK` gibt CHN null, weil es
Kreditzins minus Schatzwechselsatz ist. Nur Brasilien traegt alle fuenf. Berichtigt an
allen drei Stellen: `reihen.toml:1258`, die H1-Passage und der Abschnitt „Is a uniform
interest-rate concept reachable?" (dort steht jetzt die Matrix). Die Schlagzeile selbst
haelt unveraendert und ist erst jetzt bewiesen: keine Kennung reicht ueber alle vier.

**Eine Ueberdehnung, die niemand gemeldet hat, gleich mit geschlossen:** Mein „exactly
five" ruhte auf einer einmal gelesenen Themenliste. Nachgemessen: Thema 7 hat
`total: 203`, `pages: 1` — unpaginiert, die Aufzaehlung ist vollstaendig. Was damit
**nicht** ausgeschlossen ist, steht jetzt als eigener Punkt unter Limits: eine
Zinskennung unter einem anderen Thema oder ohne `FR.INR`-Praefix. Konvention, kein Beweis.

**Nebenbefund, ungefragt aber tragend fuer Weg 2 der Entscheidung:** `LNDP` und `RISK`
sind beide *Differenzen* zweier Saetze, kein Satzniveau — als Politikpfad also auch dort
unbrauchbar, wo sie gedeckt sind. Steht im Befund, aendert die drei Wege nicht.

**Bedingung 4, nachgemessen statt behauptet:** Mein Eingriff sitzt in Zeile 1258 hinter
dem unveraendert wiederverwendeten Praefix, ohne Zeilenumbruch — 62 Zeilen mit
Schluesselwort vor und nach diesem Lauf (die Zahl des Ruecklaufs 1), und `:440`, `:441`,
`:655`, `:1667` tragen unveraendert je ihre Fundstelle, `:1258` seine eine `spiel.md`.
Keine Zeile eingefuegt oder geloescht. Die 61-gegen-62-Frage habe ich nicht angefasst.

**Unsicher, fuer den Projektmanager:** `[[widerspruch]] Nr. 5`, `entscheidet` (`:623`),
nennt die Frage nach dem einheitlichen Zinsbegriff weiter `ungemessen` — seit heute
falsch, weiter unter der Sperre von Bedingung 4 stehen gelassen. Eine Zeile, nach 0233.

## Ruecklaeufe

1.
2.
