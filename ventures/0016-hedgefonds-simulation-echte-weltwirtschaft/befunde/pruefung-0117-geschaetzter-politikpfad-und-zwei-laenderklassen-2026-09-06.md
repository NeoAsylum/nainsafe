---
typ: pruefung
paket: 0117-geschaetzter-politikpfad-und-zwei-laenderklassen
pruefer: entwurf-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: alle vier Abnahmebedingungen einzeln; jede Formel von vorn eingesetzt, jede Fundstellenbehauptung am Original nachgemessen (technik.md T37/T38/T55, reihen.toml, spiel.md, Paket 0118, nachmessung-zinsreihen-2026-09-05)
befunde: 1
---

# Pruefung 0117 — geschaetzter Politikpfad und zwei Laenderklassen

**Gegenstand.** Commit `565259c`, gegen `b9bc00e` gemessen. `technik.md` waechst um
Abschnitt 20 (T58–T61), **+360 Zeilen, 0 entfernte** — ein einziger Anfuege-Hunk ab
Zeile 3469, der Bestand ist unberuehrt. Seit dem Commit ist `technik.md` unveraendert
(`git diff 565259c HEAD -- …/technik.md` leer). Das Logbuch des Architekten habe ich
nach der Blindpruefungsregel nicht gelesen.

## Bedingung 1 — beide Klassen definiert, die vier Laender benannt: erfuellt

T58 (technik.md:3489–3494) definiert Rueckvergleichsland und Spielland tabellarisch,
je mit der Spalte *in den Pruefgegenstaenden* („ja … zaehlen" / „nein — keine seiner
Groessen geht in ein Fehlermass ein"). Zeile 3496: „Die heutigen vier Laender — USA,
China, Deutschland, Brasilien — sind Rueckvergleichslaender, alle vier." Die vier
Namen stimmen mit `spiel.md` Z. 803–809 ueberein.

## Bedingung 2 — parametrische Zaehlung: erfuellt, jede Zahl von vorn gerechnet

Formel (technik.md:3580): `3·L_R + (L_R − n) + 1`, `n = 1` wenn das Numéraireland
Rueckvergleichsland ist (Z. 3569–3570). Eingesetzt: `3·4 + 3 + 1 = 16` ✓; die Spalte
`L_R = 4, L_S = 5` ist zeilengleich mit `heute`, und keine Formel der Tabelle
enthaelt `L_S` — das zusaetzliche Spielland laesst die Zahl nachweislich unveraendert.

Die Zerlegung traegt am Original: T37 (Z. 2553–2560) zaehlt BIP 4, Sektorstruktur 4,
Verbraucherpreise 4, Wechselkurs **je Land ausser USA** 3, Handelsblock 1 = 16.
Die Nebenzeilen der T59-Tabelle stimmen mit ihren Quellen ueberein, jede selbst
nachgeschlagen: `zaehlregel_t37` in `reihen.toml` (Z. 1833: frei 23 = 4+12+4+3,
abgeleitet 4 = Reihe 11), `sollreihen_gesamt = 27` (Z. 266),
`handelsblock_stroeme = 40` (Z. 1464), T38-Maskentabelle (Z. 1352–1366:
27·4 + 22 + 40 + 2 + 3 = 175), T55-Sollmaskenformel (Z. 3328, strukturgleich mit
`L → L_R` an genau den drei benannten Stellen). Beide Gegenrechnungen, die die
Formeln nicht kennen, reproduziert: `spiel.md` Z. 1089–1091 (195 Laender, `4·L` =
780; Formel: 3·195 + 194 + 1 = 780 ✓) und Paket 0118 Z. 86–87 (62/36 gegen 27/16;
Formeln: 9·7−1 = 62, 3·9+8+1 = 36 ✓). Die 565/290/275-Zerlegung nachgerechnet:
740−175 = 565, 740−450 = 290, 450−175 = 5·27 + (180−40) = 275 ✓. Der
Restweltrest in T58 Festlegung 3: 22 + 2·4·2 = 38 ✓.

Der offene Widerspruch im Auftragstext („Ein Spielland aendert die Zahl") ist gegen
die Abnahmebedingung entschieden und im Text benannt — das ist die richtige
Aufloesung, die Abnahme ist die schaerfere und bindende Aussage.

## Bedingung 3 — Rangfolge mit vier Stufen, Stufe 2 als Vermutung: erfuellt

T60 (Z. 3648 ff.) fuehrt die vier Stufen in der Reihenfolge des Auftrags. Stufe 2
ist ausdruecklich gekennzeichnet: „eine ungeprüfte Vermutung und keine Quelle …
nichts an ihnen ist geprüft: nicht die Deckung, nicht die Länderliste, nicht die
Drittanbieterlage. Ich habe sie in diesem Lauf ausdrücklich nicht nachgesehen."
Die Verschaerfung dazu ist selbst belegt: alle acht `feld_source`-Reihen in
`reihen.toml` einzeln nachgeschlagen — Bloecke 1, 2, 5, 6, 7 `unklar`, 8 und 10
`frei`, 13 `gesperrt` (Z. 492, 572, 790, 846, 907, 973, 1153, 1402), Reihe 13
traegt `politikpfad` in `rolle` (Z. 1389). Die uebrigen Zitate stimmen im Wortlaut:
`code_herkunft = "gewaehlt-0006, in specs/ nicht genannt"` (reihen.toml:1049),
`exogen_ab = 1999` (Z. 1057), `deckung_urteil` Reihe 9 (Z. 1064), Deutschlands
„kein eigener Zinshebel" als Entwurfsmerkmal (`spiel.md`:806),
`aufschlag_min = 1 − min(leitzins_pfad)` (technik.md:1529), `aufschlag` als
Parameterschluessel „Abstand Leitzins ↔ Anleiherendite" (Z. 1820), `leitzins_start`
nicht in `parameter.toml` (Z. 1828), `S13BOND_RT_PT_A_PT` und `CHN.*.A` = 0 aus
`daten/nachmessung-zinsreihen-2026-09-05.md` (Z. 30, 40, 55).

## Bedingung 4 — Kennzeichnungspflicht und Dateischnitt: erfuellt

T61 nennt das Feld (`stufe` im Pflichtblock `[[reihe.herkunft]]`), den Inhalt
(`land`, `quelle`, `abrufdatum`, `freie_parameter`, `herleitung` mit
Nachrechenbarkeitsanspruch) und fuenf mechanische Abbruchregeln. Die Zaehlung
stimmt: 19 `[[reihe]]`-Bloecke, davon genau drei mit `politikpfad` (Nr. 9, 12, 13,
alle `dimension = "4"`) → 3·4 + 16 = 28 Bloecke. `land = "alle"` existiert als
Konvention in `[[reihe.deckung]]` (reihen.toml:707).

`git diff b9bc00e 565259c`: drei Dateien — `technik.md` (+360/−0), die Statuszeile
des Arbeitspakets (`offen` → `gebaut`, einzige geaenderte Zeile, Diff gesichtet)
und das Pflicht-Logbuch der Rolle. Die letzten beiden erzwingt der Ablauf oberhalb
des Pakets; der Zweck der Bedingung — kein zweites Gewerk, keine Zahl ausserhalb
`technik.md` — ist erfuellt, und die staerkere Messung dafuer ist der reine
Anfuege-Hunk mit 0 entfernten Zeilen. `reihen.toml` und `spiel.md` sind unberuehrt.
Dieselbe Aufloesung wie bei 0116; der Erbauer benennt die Kollision selbst.

## Befund 1 — T60-Sperrabsatz rechnet den China/Deutschland-Fall mit der USA-Formel

**technik.md:3729:** „`L_R` fiele von 4 auf 3, die Prüfgegenstände von 16 auf
`3·3 + 3 + 1 = 13`, die Sollreihen von 27 auf `3·7 − 1 = 20`". Der Fall des Absatzes
ist „Scheitern die Stufen 1 bis 3 **für China oder Deutschland**" (Z. 3726–3727) —
die USA bleiben Rueckvergleichsland, also `n = 1`.

So erzeugt man den Fehler: (1) Formel aus Z. 3580 nehmen, `L_R = 3`, `n = 1`
einsetzen: `3·3 + (3−1) + 1 = 12`, nicht 13. (2) Der Ausdruck `3·3 + 3 + 1 = 13`
ist wortgleich der `n = 0`-Fall, den Z. 3606 ausdruecklich fuer „`L_R = 3` **ohne
die USA**" vorrechnet („ergäbe 13, nicht 12") — die Zahl ist von dort in den
falschen Fall gewandert. (3) Derselbe Satz widerlegt sich selbst: die
Sollreihenzahl daneben, `3·7 − 1 = 20`, rechnet mit `n = 1`. (4) Gegenprobe am
Bestand: ohne China bleiben BIP 3 + Sektorstruktur 3 + Preise 3 + Wechselkurs 2
(DEU, BRA) + Handelsblock 1 = 12; ebenso T58 („die Prüfgegenstände um vier" je
Rueckvergleichsland): 16 − 4 = 12.

Der Absatz ist genau der, den der Betreiber liest, wenn Chinas Leitzinsreihe
scheitert; die Zahl beziffert dort den Einsatz der Entscheidung. Keine der vier
Abnahmebedingungen verlangt diese Einsetzung — deshalb kein Ruecklauf, sondern
Vorschlagspaket `0154-t60-sperrzahl-zwoelf-statt-dreizehn` (status: vorschlag).

## Wonach ich sonst gesucht habe, ohne Befund

Nummernkollision T58–T61 gegen den Bestand (T60 kommt vorher nur als
„noch freie Nummer"-Beispiel vor, Z. 56 und 3092 — als Nachzug benannt, mit
tragfaehigem Grund liegen gelassen: die Abnahmen von 0082 Z. 103 und 0084 Z. 158
binden auf den unberuehrten Vorspann, beide gelesen); alle uebrigen Einsetzungen
der T59-Tabelle einschliesslich der Spalte `L_R = 9`; Widersprueche zwischen T58
und der T38-Stilllegungsbauart (Fondsblock: „wird ueberhaupt nicht gerechnet",
Z. 1368–1371 — dieselbe Bauart, wie behauptet); T23 Punkt 9 und 10 im Wortlaut
(Z. 1556, 1563–1564); ob der Abschnitt einen Paketstatus setzt oder ausserhalb
seiner Datei schreibt (nein); ob die drei Meldungen an den Projektmanager auf
tatsaechlichen Stellen stehen (`spiel.md`:861 „ja, als Rückvergleichsland" —
stimmt). Die zwei Lesarten von Mass 2 beruehrt dieser Abschnitt nicht.
