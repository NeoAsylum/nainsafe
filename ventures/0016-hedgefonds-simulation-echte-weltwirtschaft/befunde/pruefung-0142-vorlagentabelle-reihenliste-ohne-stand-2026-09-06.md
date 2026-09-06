---
typ: pruefung
paket: 0142-vorlagentabelle-reihenliste-ohne-stand
pruefer: daten-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln nachgemessen -- zahlwoerter.py meldet fuer alle sechs Vorlageneintraege einen Stand, der Kommentar ueber der Tabelle traegt die widerlegte Einzigkeitsaussage mit Datum und gezaehlte Zahlwoerter, und die Selbstmessung stimmt gegen den genannten Bezugsstand c1844c9 / Blob d18ca19 samt allen sechzehn Mustern einzeln.
befunde: 2
---

# Pruefung des Pakets 0142 -- `datei.vorlagen.reihenliste` bekommt einen Stand

Geprueft ist der Stand `f057f74a4d8c261d1c3e857b25210d1d6b38dc02` von
`daten/reihen.toml`. Er ist zugleich `HEAD`, der Blob des Commits `aa65c70` und der
Arbeitsbaum -- `git rev-parse HEAD:<pfad>` und `git hash-object <pfad>` geben dieselbe
Kennung, es steht also nichts Ungeschriebenes daneben.

Das Logbuch des Bauagenten und sein Bericht sind nicht gelesen. Gelesen sind das
Arbeitspaket, die geaenderte Datei, `technik.md` und die vier Befunddateien der
Vorlagentabelle.

## Bedingung 1 -- der Eintrag nennt einen Stand

`python3 befunde/messung-0099/zahlwoerter.py - daten/reihen.toml` gegen den Arbeitsbaum:

```
  [datei.vorlagen]: 6 Schluessel -- deckung, einheiten, lizenz_reihen, lizenz_wdi,
                    preisbasis, reihenliste
      deckung        Stand genannt: True
      einheiten      Stand genannt: True
      lizenz_reihen  Stand genannt: True
      lizenz_wdi     Stand genannt: True
      preisbasis     Stand genannt: True
      reihenliste    Stand genannt: True
```

Sechs von sechs. Derselbe Aufruf gegen den Blob `67b925e` (Fassung vor Paket 0126) gibt
fuer `reihenliste` `Stand genannt: False` -- die Bedingung misst also wirklich den
Eingriff und nicht eine ohnehin wahre Aussage. **Erfuellt.**

Der Wert nennt Adresse, Fassungszahl und Datum:
`... technik.md, Abschnitt 7, Fassung 7 -- Stand der letzten Aenderung an Abschnitt 7
selbst vom 2026-09-05 (Paket 0051-t46-gebietspraefix-entscheiden). ...` Die Adresse
"Abschnitt 7" steht unveraendert, wie es Punkt 2 der Aufgabenliste verlangt.

## Bedingung 2 -- der Kommentar stimmt mit der Tabelle ueberein

**Die Einzigkeitsaussage steht als widerlegte Geschichte mit Datum da** (Zeilen 250-260):
"Bis Paket 0142 stand hier, `reihenliste` sei der einzige der sechs Eintraege ohne
Stand ... seit dem 2026-09-06 ist es widerlegt". Sie ist weder gestrichen noch verengt,
und die Begruendung dahinter steht als weiter geltend daneben. Der alte Wortlaut ist am
Bezugsstand `d18ca19` nachgelesen und stimmt mit dem zitierten ueberein.

**Die Zahlwoerter sind gezaehlt, nicht fortgeschrieben.** Jedes einzeln nachgemessen:

| Stelle | Zahlwort | eigene Messung |
|---|---|---|
| Z. 150/155 | "sechs Vorlagen", sechs Schluessel namentlich | 6, Namen zeichengleich |
| Z. 256 | alle **sechs** nennen einen Stand, **keiner** nennt keinen | 6 / 0 |
| Z. 252 (Geschichte) | "der einzige ... die anderen fuenf" | am Blob `67b925e`: 5 von 6 |
| Z. 214 | "die anderen fuenf Eintraege nennen ein Datum aus einem Frontmatter" | 5, alle fuenf am Frontmatter geprueft (siehe unten) |
| Z. 281/286/288 | **zweimal** / **acht** / **zwei plus eins plus fuenf** | 2 / 8 / 2+1+5, Pfade identisch |
| Z. 323 (Geschichte) | **sieben** / **zwei plus eins plus vier** | am Blob `67b925e` bestaetigt |
| Z. 218 | "Neunzehn Commits ... sieben davon Abschnitt 7" | 19 / 7, siehe unten |
| Z. 226 | "Zwoelf ... fuenf davon nach ce59b8b" | 19-7 = 12; nach `ce59b8b` liegen 5 |
| Z. 301 | "genau ein weiteres Paket, 0047" | `nachgezogen_durch`: 0036, 0047, 0049 |
| Z. 341 | "der fuenf Vorlagen, die vor Paket 0099 ... standen" | `preisbasis` kam mit 0099, also 5 |

Die Zahl **acht** und die Zerlegung **2+1+5** sind der Teil, den das Arbeitspaket nicht
verlangt hat und den der Bauagent von sich aus berichtigt hat. Sie stimmen: die fuenf
Rest-Blattwerte sind `pruefweg.toml_geprueft`, `reihe.13.offen.2`, `reihe.2.offen.0`,
`reihe.2.umrechnung.0.begruendung`, `widerspruch.8.lang`. Die Ursachenaussage stimmt
ebenfalls -- der Nachtrag des Pakets 0126 in `pruefweg.toml_geprueft` nennt
`daten/einheitenbefund-pwt-baci.md` beim Namen und traegt die Zeichenfolge damit in
einen achten Blattwert; am Blob `67b925e` sind es sieben.

**Die fuenf Frontmatter-Daten** (Z. 214), einzeln aufgeschlagen:
`deckungsbefund-1997.md` `ueberarbeitet: 2026-09-02`; `lizenzbefund-wdi.md`
`datum: 2026-09-01`; `lizenzbefund-reihen.md` `datum: 2026-09-02`;
`einheitenbefund-pwt-baci.md` `datum: 2026-09-02`; `preisbasis` nimmt den 2026-09-04 aus
der Zeile `fassung` von `technik.md`. Alle fuenf stimmen mit dem Wert in der Tabelle
ueberein. **Erfuellt.**

## Die Zaehlung ueber `technik.md`, unabhaengig wiederholt

Der Kommentar stuetzt die Wahl der Form auf eine Zaehlung. Ich habe sie nicht
uebernommen, sondern mit einem eigenen Skript wiederholt: fuer jeden der neunzehn
Commits an `technik.md` den Text ab der Zeile `## 7.` bis zur naechsten Ueberschrift
gezogen und mit dem des Vorgaengers verglichen.

- **Neunzehn** Commits fassen `technik.md` an (`git log -- <pfad>` zaehlt 19).
- **Sieben** aendern Abschnitt 7, und es sind genau die genannten: `fd777fb`, `89dc83c`
  (2026-08-31), `02759d8`, `58c1c9a`, `1a0d876`, `bbaee82` (2026-09-01), `ce59b8b`
  (2026-09-05).
- Die Zaehlung ist **gegen beide Auslegungen von "naechste Ueberschrift" gefahren** --
  einmal bis zur naechsten Zeile mit `#` (das schneidet bei `### Die Reihenliste, ...`
  ab und laesst die Reihenlisten-Tabelle draussen), einmal bis zur naechsten `## `-Zeile
  (das nimmt sie mit). **Beide geben dieselben sieben Commits.** Die Angabe im Kommentar
  ist an dieser Stelle unscharf; sie traegt trotzdem, weil das Ergebnis nicht davon
  abhaengt.
- `ce59b8b` gehoert zu Paket `0051-t46-gebietspraefix-entscheiden`, Datum 2026-09-05.
- Was `ce59b8b` an Abschnitt 7 geaendert hat, ist genau **ein neuer Absatz** von acht
  Zeilen, relative Zeile 210 des Abschnitts, unmittelbar unter der Tabelle mit den
  Startwerten aus T46: "Die erste Zeile nennt fuenf Adressen und keine Schreibweise."
  Die Unterueberschrift `### Die Reihenliste, ...` beginnt erst bei relativer Zeile 313.
  **Die Reihenliste ist unberuehrt** -- die Aussage des Kommentars stimmt.
- Und die Aussage traegt vollstaendig, weil `reihen.toml` erst am 2026-09-02 entstanden
  ist (`git log --diff-filter=A`, Commit `30e5073`, Paket 0017). Die sechs uebrigen
  Aenderungen an Abschnitt 7 liegen davor; `ce59b8b` ist die einzige, die diese Datei
  ueberhaupt betreffen konnte.
- Die Zeile `fassung` im Frontmatter von `technik.md` nennt Nachbesserungen bis zum
  2026-09-04 (Paket 0043) und nicht den 2026-09-05. Der Satz "die Fassungszahl allein
  traegt diesen Eintrag nicht" ist damit belegt und nicht behauptet.

## Bedingung 3 -- die Selbstmessung nach dem letzten Schreiben

**Bezugsstand.** Genannt sind Commit `c1844c9` und Blob
`d18ca197812364ac65dba58dd67a7851339ddfe7`. Beide Enden gegengeprueft:
`git rev-parse c1844c9` gibt `c1844c90059c9b0ccfe7a70083657215ebbb4af5`,
`git rev-parse c1844c9:<pfad>` gibt den genannten Blob. Der Nachtrag nennt ausserdem den
waehrend des Laufs dazwischengekommenen Fremdcommit `84c324b`; auch dessen Baum traegt
denselben Blob, und `84c324b` ist der Elternteil von `aa65c70`. Der Bezugsstand ist damit
wirklich der Vorher-Stand des Eingriffs und nicht nur ein plausibler.

**Blattwertbilanz**, `tomllib.loads` auf beide Blobs ohne Zwischendatei, Pfadtupel
verglichen:

```
Blattwerte alt/neu: 1235 / 1236
nur neu:  datei.nachgezogen_durch.13
nur alt:  --
geaendert: datei.vorlagen.reihenliste, pruefweg.toml_geprueft
```

Das ist zeichengenau, was der Nachtrag behauptet: einer neu, keiner weggefallen, zwei
gemeinsame verschieden. Ausserhalb von `[datei.vorlagen]` sind allein die beiden
Buchungsfelder angefasst -- das ist die Ausnahme, die Bedingung 3 selbst verlangt, und
kein Verstoss gegen "kein Blattwert ausserhalb".

**Zeilenzahlen -- die Stelle, an der dieselbe Selbstmessung bei 0099 gefallen ist.**
Separat nachgezaehlt, Blockgrenze rueckwaerts ab `[datei.vorlagen]` gesucht, solange die
Zeile mit `#` beginnt:

```
alt d18ca19: Datei 1849 Zeilen, Kommentarblock Z. 149-259 = 111 Zeilen
neu f057f74: Datei 1937 Zeilen, Kommentarblock Z. 150-347 = 198 Zeilen
```

111 -> 198 und 1849 -> 1937 stimmen mit dem Nachtrag ueberein, und die Zerlegung geht
ohne Rest auf: 198-111 = 87 im Kommentar, dazu eine Zeile in `datei.nachgezogen_durch`,
zusammen 88 = 1937-1849. `git diff --numstat` meldet `119 31`, wie angegeben; 119-31 = 88.
Die Angabe "vor der letzten Schreibbewegung stuenden hier 118 und 30" ist die richtige
Gegenprobe fuer das selbstzaehlende Feld -- die eine geaenderte Zeile ist dieses Feld
selbst.

**Die sechzehn Muster, einzeln neu gezaehlt** -- nicht als Summe, mit den Mustern, die
die Schnitte selbst nennen, gegen beide Blobs:

| Muster | alt | neu |
|---|---:|---:|
| s1 `[=] [0-9]+\.[0-9]` | 6 | 6 |
| s2 drei Apostrophe, Zeilen | 29 | 29 |
| s2 drei Apostrophe, Vorkommen | 54 | 54 |
| s2 Randzeilen | 27 | 27 |
| s3 `^\[\[` | 114 | 114 |
| s3 Typaufzaehlung | 19/9/23/20/39/2/2 | 19/9/23/20/39/2/2 |
| s4 `^exogen_ab = ` | 19 | 19 |
| s4 `^verkettet_ab = ` | 19 | 19 |
| s4 `^lizenzurteil = ` | 19 | 19 |
| s4 Sammelmuster | 152 | 152 |
| s4 `^t37_klasse = ` | 20 | 20 |
| s4 `^nr = ` | 28 | 28 |
| s5 `^sollreihen = ` | 21 | 21 |
| s5 `^sollreihen` | 28 | 28 |
| s7 `^wortlaut = ` | 20 | 20 |
| s7 `^wortlaut_form` | 2 | 2 |

Alle sechzehn unveraendert und zeichengleich mit den Zahlen, die im Feld stehen; die
Typaufzaehlung summiert sich auf 114, also weiterhin kein achter Typ. Die sechs
Trefferkontexte von `schnitt_1` sind zusaetzlich alt gegen neu gelegt und zeichengleich
dieselben -- eine gleiche Zahl aus anderen Stellen waere sonst durchgegangen.
**Erfuellt.**

## Der Belegstellenriegel, den das Paket nicht verlangt hat

Der Nachtrag gibt drei Zahlen an, die keine Abnahmebedingung fordert. Sie sind trotzdem
geprueft -- gerade weil sie freiwillig dastehen.

`werkzeuge/belegstellen/bau/belegstellen_riegel <vorhaben> <vorgaben>` gegen den
Arbeitsbaum, Stroeme getrennt: Rueckgabe 0, "40 Zitate der geprueften Form gefunden, 40
davon aufgeloest (Untergrenze 16), 55 Fundstellen uebergangen". Genau die drei
angegebenen Zahlen. Von den 55 uebergangenen Fundstellen entfallen 40 auf
`daten/reihen.toml` -- auch das steht so da.

Die Behauptung ueber den Stand *vorher* (47 und 32) ist ohne Vorher-Lauf nichts wert,
deshalb gefahren: zwei Kopien des Vorhabens ohne `bau` und `befunde` unter `$TMPDIR`,
eine mit dem Blob `d18ca19`, eine mit `f057f74`, dieselben Vorgaben.

```
alt: 41 Zitate, 40 aufgeloest, 46 uebergangen -- davon 32 in daten/reihen.toml
neu: 41 Zitate, 40 aufgeloest, 54 uebergangen -- davon 40 in daten/reihen.toml
```

Die Kopie liegt bei den uebergangenen Fundstellen um eins unter dem Repo-Lauf, weil ihr
das Ziel in `befunde/` fehlt -- derselbe Versatz, den schon der Nachtrag zu Paket 0126
beschreibt. Der **Zuwachs** ist in beiden Laeufen derselbe: **acht**, und auf
`reihen.toml` **32 -> 40**, wie angegeben.

Die Zerlegung der acht ist ueber den Fundstellentext und nicht ueber die Zeilennummer
gegengeprueft (die Zeilen verschieben sich um 88):

- **fuenf** in den neuen Kommentarabsaetzen: Z. 203, 209, 219, 227, 228;
- **eine** in der Wertzeile `datei.vorlagen.reihenliste` (Z. 349), die "Abschnitt 7"
  jetzt zweimal statt einmal nennt;
- **zwei** in `pruefweg.toml_geprueft` selbst (Z. 1921).

5 + 1 + 2 = 8, keine weggefallen. Die Zerlegung stimmt Stelle fuer Stelle.

Der Riegel selbst ist nicht neu uebersetzt: sein Quelltext ist zuletzt mit `751d01c` am
2026-09-06 03:55 geaendert worden, das Binaerprodukt unter `werkzeuge/belegstellen/bau/`
traegt 03:57, und `git status` meldet den Quelltext unveraendert.

---

# Befund 1 -- die Zusicherung ueber die Paketkennung ist staerker als die Sache

**Wo.** `daten/reihen.toml`, Kommentar ueber `[datei.vorlagen]`, Absatz "Die Schwaeche
der gewaehlten Form", Zeilen 235-238:

> "Zweitens hat es Tagesgenauigkeit -- zwei Aenderungen an Abschnitt 7 am selben Tag
> bewegen es nicht; die Paketkennung daneben faengt diesen zweiten Fall ab, den ersten
> nicht."

**Was daran nicht stimmt.** Die Paketkennung faengt den Fall nur ab, wenn die beiden
Aenderungen desselben Tages aus **verschiedenen** Paketen kommen. Kommen sie aus
demselben, bewegt sich weder das Datum noch die Kennung, und der Stand behauptete
danach eine Uebereinstimmung mit einem Abschnittstext, den diese Datei nie gesehen hat.

**Wie man es erzeugt.** Ein Aufruf:

```
git log --format="%h %ad %s" --date=iso -- specs/0016-.../technik.md
```

```
9e46cfa 2026-09-05 05:51:37 architekt: 0051-t46-gebietspraefix-entscheiden (8 Dateien)
a127600 2026-09-05 04:25:34 architekt: 0051-t46-gebietspraefix-entscheiden (4 Dateien)
ce59b8b 2026-09-05 03:43:21 architekt: 0051-t46-gebietspraefix-entscheiden (9 Dateien)
```

**Genau das Paket, das der neue Stand als Kennung fuehrt**, hat `technik.md` am
2026-09-05 dreimal angefasst. Dass nur `ce59b8b` davon Abschnitt 7 traf, ist ein Zufall
dieses Falls und keine Eigenschaft der gewaehlten Form: Haette auch `a127600` oder
`9e46cfa` Abschnitt 7 beruehrt, waere der Eintrag "2026-09-05 (Paket 0051-...)"
buchstabengleich derselbe geblieben. Die Schwaechenliste, die genau davor warnen soll,
nennt den Fall damit als abgefangen, den ihr eigenes Beispiel offenlaesst.

**Warum kein `zurueck`.** Die drei Abnahmebedingungen sind erfuellt; die Wahl der Form
hat das Arbeitspaket ausdruecklich dem Bauagenten ueberlassen und dazu verlangt, die
Schwaeche danebenzuschreiben. Das ist geschehen, in drei Punkten und ausfuehrlich. Nur
der zweite Punkt sichert einen Halbsatz weiter zu, als er kann. Ein Ruecklauf gegen
denselben Auftrag erzeugte keine bessere Datei -- er erzeugte dieselbe mit einem
berichtigten Halbsatz. Vorschlag dafuer: `0185-standschwaeche-paketkennung-je-commit`.

# Befund 2 -- die Erklaerung deckt drei von fuenf Commits

**Wo.** Dieselbe Datei, Zeilen 226-229:

> "Zwoelf haben technik.md geaendert und Abschnitt 7 nicht, fuenf davon nach ce59b8b --
> die Abschnitte 19, 20 und 21 stehen hinter Abschnitt 7 und fassen ihn nicht an."

**Was daran nicht stimmt.** Beide Zahlen sind richtig, ich habe sie nachgemessen: 12 =
19-7, und nach `ce59b8b` liegen fuenf Commits. Der Halbsatz danach erklaert aber nur
**drei** davon. Die fuenf sind:

```
9e46cfa 2026-09-05 05:51  Paket 0051-t46-gebietspraefix-entscheiden
a127600 2026-09-05 04:25  Paket 0051-t46-gebietspraefix-entscheiden
1f763e9 2026-09-05 19:15  Paket 0116 -- Abschnitt 19
565259c 2026-09-06 00:37  Paket 0117 -- Abschnitt 20
95fb409 2026-09-06 03:33  Paket 0141 -- Abschnitt 21
```

Die ersten beiden sind **weitere Commits des Pakets 0051 selbst** und keine neuen
Abschnitte. Wer den Satz liest, zaehlt drei Abschnitte gegen fuenf Commits und muss
selbst herausfinden, wo die anderen zwei herkommen -- oder er nimmt an, es seien fuenf
neue Abschnitte, und dann ist die Zaehlung fuer ihn falsch.

**Dieselbe Ursache wie Befund 1.** Beide Stellen setzen ein Paket mit einem Commit
gleich. Deshalb gehoeren sie in dieselbe Berichtigung und nicht in zwei.

**Wie man es erzeugt.** Derselbe Aufruf wie bei Befund 1; die Zeilen oberhalb von
`ce59b8b` abzaehlen und ihre Paketkennungen gegen die drei genannten Abschnitte legen.

---

# Wonach ich ausserdem gesucht und was ich nicht als Befund gefuehrt habe

- **Reproduzierbarkeit.** `zahlwoerter.py` und die eigene Bilanzmessung sind zweimal mit
  denselben Argumenten gelaufen und geben bitgleich dasselbe. Der eingebettete Stand
  traegt ein Datum (`datei.stand = 2026-09-06`) und ist unveraendert, weil dort schon
  der 2026-09-06 stand -- nachgesehen, stimmt.
- **Lizenz und Namensnennung.** Dieses Paket fasst keine Quelle und keinen
  `lizenzbeleg` an. Die Blattwertbilanz beweist es: geaendert sind genau
  `datei.vorlagen.reihenliste` und `pruefweg.toml_geprueft`, neu ist genau
  `datei.nachgezogen_durch.13`. Kein `namensnennung.*`, kein `reihe.*.lizenzbeleg.*`.
  `gilt_fuer_reihen` musste deshalb nicht nachgezogen werden.
- **Einheiten, Basisjahre, Luecken.** Kein Blattwert einer Reihe ist beruehrt --
  dieselbe Bilanz zeigt es. Nachgesehen und nichts gefunden.
- **"Die Tabelle der Restweltstartwerte"** (Z. 244) ist ein loser Name: die Tabelle in
  `technik.md` heisst dort "T46 -- Die elf Adressen, deren Herkunft dieses Dokument ist"
  und fuehrt neben den fuenf Restweltzeilen auch `land.US.wechselkurs` und die fuenf
  `gebiet.<G>.basiswechsel`. Sie ist ueber die Beschreibung auffindbar, und die Aussage,
  die der Satz traegt, stimmt. Benennung ist kein Befund, wo `specs/` schweigt.
- **Der Fuerwortbezug in Zeile 341** ("Sie traegt den groessten offenen Rest ...") zeigt
  auf `einheiten`, und dieses Paket hat den Abstand zum Bezugswort um einen Absatz
  vergroessert. Kein Befund: Die Stelle war im Bezugsstand schon so gebaut, und der
  Absatz davor nennt den Einheitenbefund im Klartext.
- **Ein Zaehlausdruck, der Kommentare traefe**, gibt es unter den sechzehn Mustern
  nicht -- alle sind am Zeilenanfang verankert oder auf `=` bezogen, und `tomllib` sieht
  Kommentare gar nicht. Deshalb sind die Musterzahlen ein Fixpunkt unter dem eigenen
  Schreibvorgang, und die Zeilenzahlen sind es nicht; genau die habe ich separat
  gezaehlt (siehe Bedingung 3).
- **Der Anteil meiner eigenen vorigen Pruefung.** Die Pruefung des Pakets 0099
  (`geprueft`, 2026-09-06) hat die Standform vollstaendig in dieses Paket verwiesen und
  keinen eigenen Vorschlag geschrieben. Beide Befunde oben liegen in Absaetzen, die es
  zum Zeitpunkt jener Pruefung noch nicht gab -- sie sind nicht dort haengen geblieben.
