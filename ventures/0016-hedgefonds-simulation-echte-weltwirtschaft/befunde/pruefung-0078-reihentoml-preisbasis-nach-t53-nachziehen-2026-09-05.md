---
typ: pruefung
paket: 0078-reihentoml-preisbasis-nach-t53-nachziehen
pruefer: daten-pruefer
datum: 2026-09-05
urteil: zurueck
kriterium_geprueft: Alle fuenf Bedingungen einzeln nachgemessen -- die sechzehn Muster der sieben Schnitte, die Blattwertbilanz mit tomllib gegen den Bezugsblob und 19 Zitate maschinell gegen technik.md; die vier Zahlen und alle Zitate halten, aber der Lauf schreibt in `pruefweg.zaehlregel_umrechnung` eine Einzigkeitsbehauptung, die dieselbe Datei mit Reihe 7 widerlegt.
befunde: 3
---

# Pruefung 0078 — `reihen.toml`, Preisbasis nach T53

Gemessen gegen den Bezugsblob `db80e48f8f1b234fde0ec9ad8ecb8b3c7fcf954e`
(`git ls-tree 849abc3 …/daten/reihen.toml`, nachgeschlagen und nicht uebernommen) und
gegen den Arbeitsbaum, `git hash-object` = `cce4936c339beb6ba4e63baa77c2eaa51e56cc59`.
`git log 849abc3..HEAD -- <datei>` nennt genau zwei Commits, `8d74aff` und `61fa55b`;
`61fa55b` und `a4850f7` tragen beide den Endblob. Es liegt also kein dritter, fremder
Schreibzugriff dazwischen.

Werkzeug: Python 3.14.4, `tomllib.load` im Binaermodus, beide Baeume flach gezogen und
Blattschluessel als Pfadtupel verglichen; die Muster mit `Grep` und mit `grep -c`, beides
einzeln.

## Befund 1 (tragend) — `pruefweg.zaehlregel_umrechnung` behauptet eine Einzigkeit, die Reihe 7 widerlegt

**Der Satz.** Der Lauf haengt an `pruefweg.zaehlregel_umrechnung` an:

> „Dieser zweite Block ist der einzige, dessen `faktor` nicht die ganze Umrechnung
> traegt: Er nennt den Zaehlerfaktor 10.000, und der jahresweise Teiler steht daneben im
> Feld `teiler`."

**Das Gegenbeispiel steht in derselben Datei**, im zweiten Umrechnungsblock der Reihe 7:

```
schritt        = 2
art            = "mal_geteilt"
faktor         = 10000
bezugsgroesse  = "Gesamtbeschaeftigung des Gebiets (Reihe 6)"
begruendung    = "… Der Anteil in Zehntausendsteln mal der Bezugsgroesse, geteilt
                  durch 10.000. Ein Anteil allein kann keine Personenzahl ergeben."
```

Auch dort traegt der `faktor` nicht die ganze Umrechnung: Er ist der **Teiler**, und der
zweite Operand — eine je Gebiet und Jahr wechselnde Groesse — steht **daneben in einem
eigenen Feld**. Das ist nicht bloss ein zweiter Fall, sondern derselbe Zuschnitt wie der
neue Block: konstanter Faktor plus Nachbarfeld, das den veraenderlichen Teil benennt.
`bezugsgroesse` verhaelt sich zu Reihe 7, wie `teiler` sich zu Reihe 14 verhaelt.

**Wie man den Fehler erzeugt** — drei Schritte, ohne Werkzeug ausser einem TOML-Leser:

1. `pruefweg.zaehlregel_umrechnung` lesen, letzter Satz: „ist der einzige".
2. Die 23 Bloecke `[[reihe.umrechnung]]` durchgehen und die heraussuchen, die neben
   `faktor` ein weiteres inhaltstragendes Feld fuehren. Ergebnis, gemessen:

   | Reihe | `art` | `faktor` | Nachbarfeld |
   |---|---|---:|---|
   | 2, Schritt 2 | `normierung` | 10000 | `rundungsstelle` |
   | **7, Schritt 2** | **`mal_geteilt`** | **10000** | **`bezugsgroesse`** |
   | 10, Schritt 1 | `verkettung` | *keiner* | `gilt_ab_jahr`, `umrechnungskurs_dem_je_eur_mal_100000`, `hinweis` |
   | 14, Schritt 2 | `deflationierung` | 10000 | `teiler` (neu mit 0078) |

3. Reihe 7 lesen: Die `begruendung` schreibt die Rechnung selbst aus und widerlegt den
   Satz woertlich.

Reihe 10 scheidet als Gegenbeispiel aus, weil sie gar keinen `faktor` fuehrt; Reihe 7
scheidet nicht aus. Die Bloecke der Reihen 4 und 15 (`basierung`, `faktor = 10000`) sind
der schwaechere, aber gleichgerichtete Fall: Der Teiler ist dort der Wert des Startjahrs
und steht ueberhaupt nicht im Block.

**Warum das nicht Wortwahl ist.** `[pruefweg]` ist der Pruefapparat dieser Datei, und
`zaehlregel_umrechnung` ist die Regel, nach der ein spaeterer Leser die 23 Bloecke liest,
die `schnitt_3` zaehlt. Ein „ist der einzige" an dieser Stelle ist eine Zaehlaussage, keine
Formulierung. Und sie wirkt genau in die Richtung, gegen die dieses Paket angetreten ist,
nur mit umgekehrtem Vorzeichen: Das Paket raeumt eine Frage weg, die entschieden war;
dieser Satz stellt eine Bauform als einmalig hin, die es zweimal gibt. Wer die
Abstraktion sucht — ein Feldname fuer „der veraenderliche Operand steht daneben" —, liest
hier, dass es sie nicht zu suchen gibt.

**Was den Befund stuetzt, ohne ihn zu tragen:** Der Baubericht schreibt unter „Woran ich
unsicher bin", die fuenf neuen Schluessel machten den Block „formal unaehnlich zu allen
anderen 22", und ein Leser erwarte „eine feste Blockform". Eine feste Blockform gibt es
nicht: Die 23 Bloecke tragen **sieben** verschiedene Schluesselmengen (17 mal die
sechsfeldrige Grundform, dazu je einmal die Varianten mit `rundungsstelle`, `frage`,
`bezugsgroesse`, dem Verkettungssatz der Reihe 10, `antwort` und die neue). Das steht im
Bericht und nicht in der Datei und ist deshalb kein eigener Befund.

**Der Weg zurueck ist kurz** und darum verhaeltnismaessig: Der Halbsatz wird gestrichen
oder auf das eingeschraenkt, was zutrifft — dass dieser Block als einziger einen
**jahresweisen** Teiler fuehrt, waehrend Reihe 7 eine Bezugsgroesse und Reihe 2 eine
Rundungsstelle daneben stellt. Eine Zeile, und die Regel stimmt wieder.

## Befund 2 (gemeldet, nicht Rueckgabegrund) — Reihe 14 benutzt jetzt Weltbankdaten, `[namensnennung]` weiss davon nichts

`[namensnennung]` ist nach dem Kommentar darueber nicht eine Notiz, sondern die Stelle,
aus der der Jahrgangsbau „die ausgelieferte `LIZENZEN.md`" und die Seite „Datenquellen"
im Spiel fuellt. Die Zuordnung laeuft ueber `gilt_fuer_reihen`:

```
namensnennung.weltbank.gilt_fuer_reihen   = [1, 2, 5, 6, 7, 8, 10, 13]
namensnennung.cepii_baci.gilt_fuer_reihen = [14, 16]
```

Seit diesem Lauf entstehen die ausgelieferten Werte der Reihe 14 aus BACI **und** aus zwei
Weltbank-Indikatoren (`NE.EXP.GNFS.CD`, `NE.EXP.GNFS.KD`, Gebiet `WLD`) — so steht es im
neuen Feld `quelle_deflator`. Die Weltbankzeile fuehrt Reihe 14 nicht, und die
Deflatorreihe hat noch keinen eigenen Block. Die CC-BY-4.0-Pflicht, die dieselbe Tabelle
als „an jeden weiterzureichen, dem man die Daten weitergibt" festhaelt, kommt fuer die
40 Handelsstroeme damit nicht ins Produkt.

**Kein Rueckgabegrund**, und der Grund dafuer steht im Paket: Es verbietet ausdruecklich,
die Lizenzbloecke anzufassen. Richtig war also, es liegen zu lassen — es gehoerte aber
unter „Gemeldet, nicht angefasst", wo drei andere Punkte stehen und dieser fehlt.
**Vorschlag als eigenes Paket geschrieben: `0100-namensnennung-reihe-14-weltbank`.**

Nicht Gegenstand dieses Laufs, aber beim Zaehlen mitgefallen: Reihe 16 steht ebenfalls nur
unter `cepii_baci`, obwohl ihr `N` seit jeher ueber die Reihen 1 und 2 aus der Weltbank
kommt. Das ist aelter als 0078 und im Vorschlag mit aufgenommen.

## Befund 3 (gemeldet) — die Diff-Bilanz des Bauberichts misst gegen den falschen Stand

Der Bericht schreibt: *„Bilanz gegen den Bezugsstand: 27 Zeilen hinzu, 12 weg, 12 Hunks"*,
und definiert den Bezugsstand zwei Zeilen darunter als `849abc3` / `db80e48`. Gemessen:

| Vergleich | hinzu | weg | Hunks (`-U0`) |
|---|---:|---:|---:|
| `db80e48 → cce4936` (der genannte Bezugsstand) | **36** | **17** | 14 |
| `5c39f47 → cce4936` (der Zwischenblob aus `8d74aff`) | 27 | 12 | 12 |

Alle drei Zahlen des Berichts gehoeren zur zweiten Zeile. Wer der Anweisung des Berichts
folgt — *„Der vollstaendige Vergleich ist `git diff db80e48 cce4936`"* —, bekommt andere
Zahlen als die, die daneben stehen; das ist mir zuerst passiert.

**Inhaltlich fehlt nichts.** Die Differenz `9 hinzu / 5 weg` ist genau der Zwischenstand,
den `8d74aff` mitgenommen hat, und der Bericht beschreibt ihn eine Zeile spaeter richtig
als „den Absatz der Leseregel 3 und die drei Felder des Widerspruchs Nr. 9". Es ist eine
falsch beschriftete Zahl, keine unterschlagene Aenderung — deshalb gemeldet und nicht
Rueckgabegrund.

## Was ich gemessen habe und was gehalten hat

**Bedingung 1 — die drei Stellen.** Gehalten.

- `widerspruch[8]` (`nr = 9`, Index nachgeschlagen, nicht gezaehlt): `entscheidet`
  beginnt „Entschieden am 2026-09-04 vom Architekten…" und folgt damit dem Muster, das
  Widerspruch Nr. 5 in dieser Datei schon traegt. `lang` endet auf „gewaehlt hat sie der
  Architekt … und zwar die erste"; `in_dieser_datei` beginnt „Aufgeloest und nachgetragen
  mit Paket 0078". Keines der drei Felder stellt die Frage noch.
- `reihe[13]` (`nr = 14`): zwei Bloecke `[[reihe.umrechnung]]`, Schritt 2 mit
  `art = "deflationierung"`, `basisjahr = 2015`. Der alte `offen`-Eintrag mit den vier
  Moeglichkeiten ist weg.
- `reihe[15]` (`nr = 16`): `quelle_eingebettet` nennt Reihe 1 jetzt ausdruecklich; der
  `offen`-Eintrag zur Preisbasis ist weg.
- **Ueber die ganze Datei geprueft, nicht nur an den drei Stellen:** `grep -n 'Preisbasis'`
  und `grep -n 'Klasse 2'` — neun beziehungsweise zehn Treffer, jeder einzeln gelesen.
  Keiner fuehrt die Frage noch als offen. Die vierte Stelle, der letzte Absatz der
  Leseregel 3 im Kopf, ist mitgezogen („ist seit T53 aufgeloest").

**Bedingung 2 — Fundstellen.** Gehalten. 19 Zitate maschinell gegen `technik.md`
geprueft (Weissraum normalisiert, `**` entfernt, Backticks belassen): **alle 19 gefunden**,
17 davon genau einmal, zwei mehrdeutig („darauf gebracht" 2 mal, „mal dem Sektoranteil aus
Reihe 2" 2 mal) — beide stehen mit Absatzadresse daneben und sind damit eindeutig.
Zeilennummern kommen in keiner der neuen Belegstellen vor; adressiert wird durchweg mit
Abschnittsueberschrift und Zeichenfolge, wie die Datei es sonst tut.

Zwei Randbemerkungen ohne Befundcharakter: Der Absatz zu T53 beginnt in `technik.md`
streng genommen mit „T53 — Was Klasse 2 fuer eine Reihe bedeutet…", die Belegstelle nennt
die Zeichenfolge ohne das „T53 —"; sie bleibt eindeutig. Und die Abschnittsueberschrift 17
ist in `reihen.toml` transliteriert (`--` statt Gedankenstrich, Backticks weg) — das ist
die durchgehende Schreibweise dieser Datei fuer Adressen, waehrend die Zitate selbst
Umlaute zeichengleich fuehren.

**Bedingung 3 — was T53 offen laesst.** Gehalten. `reihe[13].offen[0]` traegt die
Restgroesse mit T53s Wortlaut *„er ist ungemessen und die ehrliche Restgrösse dieses
Wegs"* — Zitat gegen `technik.md` geprueft, Treffer. Sie ist weder als gemessen
umformuliert noch mit der erledigten Frage verschwunden. Reihe 3 bleibt unberuehrt
(`art = "ungemessen"`, kein Faktor) — durch die Blattwertbilanz bewiesen, nicht
angenommen: `reihe.2.*` kommt unter den 18 Aenderungen nicht vor.

**Bedingung 4 — Reihe 20.** Gehalten. `grep -c 'Ausfuhrpreisindex'` gibt **0 im
Bezugsblob und 0 im Arbeitsbaum**; beide selbst gezaehlt, der alte Blob dafuer nach
`$TMPDIR` ausgepackt. Der Deflatorname `preisindex_handel` enthaelt das Wort nicht, die
Ausnahme der Bedingung greift also gar nicht. Ein neuer `[[reihe]]`-Block ist nicht
entstanden: 19 vorher, 19 nachher, mit dem Parser gezaehlt.

**Bedingung 5 — die Selbstmessungen.** Die Zahlen halten alle; das Feld ist zum vierten
Mal die schwierigste Stelle des Pakets, und diesmal stimmen sie.

*Bezugsstand:* `849abc3` existiert, `git ls-tree` gibt den genannten Blob `db80e48`,
und zwischen ihm und dem Endstand liegen nur die zwei Commits oben. Der Nachtrag steht
**im letzten geschriebenen Feld** und misst eine Datei, die danach nicht mehr angefasst
wurde — nachgewiesen dadurch, dass meine eigene Zaehlung gegen den Arbeitsbaum dieselben
Zahlen gibt.

*Parserlauf:* gueltiges TOML 1.0, 19 `reihe`, 9 `widerspruch`, sechs Wurzeltabellen,
`sum(sollreihen) = 27 = zaehlung.sollreihen_gesamt`. Ein ausfuehrbares Werkzeug stand zur
Verfuegung; keine ausgewiesene Nichtmessung noetig.

*Die sechzehn Muster, von mir einzeln neu gezaehlt* — nicht nachgelesen, und die Spalte
„gezaehlt" ist mein eigener Aufruf:

| Muster | im Feld | gezaehlt |
|---|---:|---:|
| `schnitt_1` `[=] [0-9]+\.[0-9]` | 6 | 6 |
| `schnitt_2` `[']{3}` Zeilen / `-o` Vorkommen / `^[']{3}\|[']{3}$` | 29 / 54 / 27 | 29 / 54 / 27 |
| `schnitt_3` `^\[\[` | 114 | 114 |
| `schnitt_4` `^exogen_ab = ` / `^verkettet_ab = ` / `^lizenzurteil = ` | 19 / 19 / 19 | 19 / 19 / 19 |
| `schnitt_4` Sammelmuster / `^t37_klasse = ` / `^nr = ` | 152 / 20 / 28 | 152 / 20 / 28 |
| `schnitt_5` `^sollreihen = ` / `^sollreihen` | 21 / 28 | 21 / 28 |
| `schnitt_7` `^wortlaut = ` / `^wortlaut_form` | 20 / 2 | 20 / 2 |

Die Aufzaehlung nach Typ hinter `schnitt_3` habe ich mit `grep -oE '^\[\[[a-z._]+\]\]'`
einzeln nachgezaehlt und nicht die Summe geglaubt: 19 `reihe`, 9 `widerspruch`,
23 `reihe.umrechnung`, 20 `reihe.lizenzbeleg`, 39 `reihe.deckung`, 2 `reihe.konkordanz`,
2 `reihe.bruch` — Summe 114, gleich der Musterzahl, also weiterhin kein achter Typ.
Die 113 und die 22 stehen als alte Zahlen daneben, wie verlangt.

*`schnitt_1` ueber die Trefferkontexte, nicht nur ueber die Zahl:* beide Fassungen mit
`grep -n` ausgegeben und Zeile fuer Zeile verglichen. Dieselben sechs Fundstellen
(Widerspruch Nr. 4 `kurz` und `lang`, Reihe 4, Reihe 10 `offen`, Reihe 15, Reihe 17), nur
um sechs bis zwanzig Zeilen verschoben. Keine gleiche Zahl aus anderen Stellen.

*Blattwerte:* 1214 → 1226, mit `tomllib` gegen beide Baeume gezaehlt. 13 neu, 1 weg,
1213 gemeinsam, davon 18 verschieden — alle vier Zahlen stimmen mit dem Feld ueberein,
`1226 = 1214 − 1 + 13` geht auf. Die Aufteilung „4 + 14" habe ich nicht uebernommen,
sondern die beiden Listengleichheiten selbst ausgefuehrt:
`alt[reihe.13.offen][1:] == neu[…][2:]` → wahr, `alt[reihe.15.offen][1:] == neu[…]` →
wahr. Damit sind die vier Verschiebungen wirklich Verschiebungen, und die 14 uebrigen
sind der Eingriff. Dass `pruefweg.toml_geprueft` als vierzehnter in seiner eigenen Bilanz
steht, stimmt und ist der Fixpunkt, den das Feld beschreibt.

Der neue Block verletzt T4 nicht: `faktor = 10000` und `basisjahr = 2015` tragen keinen
Dezimalpunkt, alle „10.000" der neuen Felder stehen innerhalb von Zeichenketten —
`schnitt_1` bleibt deshalb bei 6.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Einheiten und Basisjahre, von Hand nachgerechnet.** T53s Index ist
  `laufend / konstant · 10.000` mit 2015 = 10.000; fuer 1997 steht dort 7.417, also
  `handel_konstant = handel_laufend · 10.000 / 7.417 = ·1,348`. Die Richtung stimmt:
  Werte in Preisen von 1997 werden auf das hoehere Preisniveau von 2015 gehoben, nicht
  gesenkt. Die `formel` in `reihen.toml` ist zeichengleich zu T53s beiden Zeilen; der
  Zaehlerfaktor 10.000 im Feld `faktor` ist wirklich der Zaehlerfaktor aus
  `mal_geteilt(…, 10.000, preisindex_handel[t])` und nicht der Teiler.
- **Die zweite Seite des Quotienten.** Reihe 16: `H` in Tsd USD (BACI, Faktor 1),
  `N` ueber Reihe 1 (`NY.GDP.MKTP.KD`, USD) mit `art = "geteilt"`, `faktor = 1000` — also
  ebenfalls Tsd USD. Groessenordnung und Preisbasis stimmen nach dem Eingriff auf beiden
  Seiten ueberein, und `quelle_eingebettet` nennt Reihe 1 jetzt.
- **Stille Interpolation.** Keine. Die einzige Luecke, die der Lauf beruehrt — Chinas
  fehlende 24 Stuetzstellen in `NE.EXP.GNFS.KD` —, ist in `reihe[13].offen[0]` benannt
  und ist der Grund, warum T53 den Weltindex „erzwungen und nicht bevorzugt" nennt. Nichts
  ist gefuellt, nichts geglaettet.
- **Ob eine Quelle ohne Deckung durch `daten.md` hereinkommt.** Nein: WDI ist Quelle Nr. 1
  in `specs/…/daten.md` („1. Weltbank -- World Development Indicators — traegt"),
  nachgeschlagen und nicht aus T53 uebernommen. Der Deflator bringt keine fuenfte Quelle.
  Was fehlt, ist die Zuordnung im Produkt — Befund 2.
- **Ob `quelle_eingebettet` eine woertliche Uebernahme aus Abschnitt 7 ist**, die nicht
  haette geaendert werden duerfen. Ist es nicht: Leseregel 4 im Kopf zaehlt die sechs
  Felder mit woertlicher Uebernahme auf, und `quelle_eingebettet` gehoert nicht dazu.
  `quelle_tabelle` der Reihe 16 ist unveraendert — durch die Blattwertbilanz belegt.
- **Ob der Lauf ausserhalb seiner Dateiliste geschrieben hat.** `reihen.toml` ist die
  einzige beruehrte Datei unter `daten/`. Der Commit `a4850f7` traegt daneben
  `werkzeuge/belegstellen/belegstellen_riegel.cpp`; die Aenderung gehoert dem Lauf, den
  `fb586db` als `testentwickler: 0079` fuehrt, und ist derselbe Einsammeleffekt, den der
  Bericht fuer die eigene Datei beschreibt — nur in die andere Richtung. Kein Befund
  gegen dieses Paket, aber die fuenfte Runde in Folge, in der die Commitgrenzen dieser
  Fabrik nicht mit den Laufgrenzen zusammenfallen.
- **Widerspruch Nr. 4 (Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6).** Weiter offen,
  weiter beim Architekten, vom Lauf nicht angefasst — richtig so.

## Was ich ausdruecklich nicht geprueft habe

Die 25 Indexwerte aus T53 gegen die Weltbank. Das Paket verbietet eigene Quellensuche und
macht T53 zur Vorgabe; `reihen.toml` uebernimmt sie ausserdem gar nicht — die Datei nennt
die beiden Indikatorcodes und die Formel, nicht die Tabelle. Dass es zu einem dieser Werte
ein eigenes Paket gibt (`0082-t53-indexwert-2018-berichtigen`), aendert an dieser Datei
nichts, weil sie keine Indexzahl fuehrt.
