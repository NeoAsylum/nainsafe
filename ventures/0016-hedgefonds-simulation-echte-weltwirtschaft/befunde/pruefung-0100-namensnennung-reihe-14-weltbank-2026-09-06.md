---
typ: pruefung
paket: 0100-namensnennung-reihe-14-weltbank
pruefer: daten-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln nachgemessen -- die 14 und die 16 stehen in `namensnennung.weltbank.gilt_fuer_reihen` mit belegter Herkunft, die Vollstaendigkeitsfrage ist beantwortet, und die Blattwertbilanz samt den sechzehn Mustern der sieben Schnitte ist gegen den genannten Bezugsstand mit eigenem Werkzeug neu gezaehlt und stimmt zeichengenau mit der Selbstmessung ueberein.
befunde: 1
---

# Pruefung des Pakets 0100

Geprueft ist der Commit `d80beae`; der Arbeitsbaum ist mit ihm blobgleich
(`git hash-object` und `git ls-tree` geben beide `67b925e584277fd9e95a8e1686a27d7ce4009c95`).

Die vier Messskripte dieser Pruefung liegen unter `befunde/messung-0100/` und sind
eigenstaendig geschrieben, nicht aus `messung-0078/` uebernommen. Jedes nimmt Blobkennung
und Dateipfad und ist damit wiederholbar. Werkzeug: Python 3.14.4, `tomllib`.

## Bezugsstand -- zuerst geprueft, weil alles andere daran haengt

Das Feld `pruefweg.toml_geprueft` nennt als Bezugsstand den Commit `ca60f8a` mit dem Blob
`6ef85077ab8297bd7ca5386c756233f303e1d371` und behauptet, der dazwischengekommene fremde
Commit `bfe7e13` fasse die Datei nicht an. Beides nachgeschlagen:

- `git ls-tree ca60f8a` → `6ef85077ab8297bd7ca5386c756233f303e1d371`
- `git ls-tree bfe7e13` → derselbe Blob
- `git rev-parse ca60f8a` → `ca60f8a6ec5066f31f8a2d94c05f3b56581ea17b`, wie angegeben

Der Bezugsstand ist damit tatsaechlich der Stand nach den drei fremden Paketen 0090, 0078
und 0099, wie das Arbeitspaket es verlangt. Das ist die Angabe, an der dieses Feld
frueher dreimal gescheitert ist; sie stimmt.

## Bedingung 1 -- die 14 steht drin, mit Herkunft

`namensnennung.weltbank.gilt_fuer_reihen` liest sich nach dem Eingriff als
`[1, 2, 5, 6, 7, 8, 10, 13, 14, 16]` (`befunde/messung-0100/inhalt.py`). Die 14 ist da.

Daneben steht das neue Feld `hinweis`. Es fuehrt zwei woertliche Zitate als Fundstelle in
derselben Datei und ohne Zeilennummer. Beide sind zeichengleich gegen ihr Ursprungsfeld
verglichen, nicht nur dem Sinn nach:

| Zitat | steht in | Vergleich |
|---|---|---|
| `Das ist Quelle Nr. 1 aus daten.md -- dieselbe Lizenz, dieselbe Zitierpflicht` | `reihe[13].umrechnung[1].quelle_deflator` (Reihe 14, zweiter Block, `art = deflationierung`) | zeichengleich |
| `N stammt also aus zwei Reihen, und Reihe 1 ist eine davon` | `reihe[15].quelle_eingebettet` (Reihe 16) | zeichengleich |

Gegengeprueft ist auch, dass keines der beiden Zitate im jeweils anderen Feld steht --
sonst waere die Zuordnung zufaellig richtig. `daten.md` fuehrt die Weltbank tatsaechlich
unter Nummer 1 (`specs/0016-.../daten.md`, Zwischenzeile
„### 1. Weltbank -- World Development Indicators — **traegt**"), CEPII BACI unter Nummer 3.
Die Kette Anspruch → Beleg → Quelle traegt also durch.

Kein Rechtsrat gegeben: Das Feld sagt ausdruecklich, dass es nicht entscheidet, ob die
Deflationierung eine Bearbeitung im Sinne der Lizenz ist. Ein `[[widerspruch]]` war
danach nicht faellig, und die Liste `widerspruch` steht unveraendert bei 9.

## Bedingung 2 -- Reihe 16 entschieden, Vollstaendigkeitsfrage beantwortet

Reihe 16 ist nicht uebergangen, sondern aufgenommen, und die Aufnahme ist begruendet.
Das neue Feld `namensnennung.vollstaendigkeit` beantwortet die Frage aus Punkt 3 des
Arbeitspakets in beide Richtungen: jede Reihe mit Fremdbestand unter mindestens einer
Quelle, und unter jeder Quelle, aus der ihre ausgelieferten Werte entstehen. Damit sagt
die Tabelle jetzt selbst, dass eine fehlende Nummer eine Aussage ist und keine Luecke.

Die Behauptungen des Feldes sind gegen alle 19 Reihenbloecke nachgezaehlt
(`inhalt.py`, `gegenprobe.py`):

- Vereinigung der vier Listen: `[1 … 16]`, ohne Ausnahme — stimmt.
- Fehlend von 1 bis 19: genau `17, 18, 19` — stimmt.
- `quelle_tabelle` mit dem Wort `keine`: genau die Reihen 17, 18, 19 — stimmt, und
  ausschliesslich sie.

Weil die neue Regel eine Aussage ueber die ganze Datei ist, habe ich ihre zweite
Richtung an allen 19 Reihen gegengeprueft und nicht nur an den beiden des Pakets. Die
Frage lautete: Gibt es eine weitere Reihe, deren Umrechnung eine fremde Bezugsgroesse
zieht, ohne dass die zugehoerige Quelle in `gilt_fuer_reihen` stuende? Nein:

- Reihe 7, Schritt 2 (`mal_geteilt`) zieht `bezugsgroesse = Gesamtbeschaeftigung des
  Gebiets (Reihe 6)` — Reihe 6 ist ebenfalls Weltbank, Reihe 7 steht unter `weltbank`.
- Reihe 2, Schritt 2 (`normierung`) zieht die eigenen Sektoranteile.
- Reihen 4 und 15 (`basierung`) teilen durch das Startjahr ihrer eigenen PWT-Quellenreihe.
- Reihe 10, Schritt 2 (`verkettung`) traegt den festen Kurs im Schluesselnamen
  `umrechnungskurs_dem_je_eur_mal_100000`; das ist keine lizenzierte Datenquelle.
- Die Reihen 1, 5 und 6 fuehren `quelle_tabelle = WDI / PWT`, stehen aber nur unter
  `weltbank`. Das ist kein Verstoss gegen die neue Regel, sondern ihr Anwendungsfall:
  `quelle_eingebettet` sagt bei allen dreien `WDI`, die ausgelieferten Werte entstehen
  also nicht aus PWT. Die Nennung von PWT in `quelle_tabelle` ist ein Ausweichweg, kein
  verwendeter Bestand.

Die Reihe 14 war damit der einzige offene Fall dieser Art, und er ist geschlossen.

## Bedingung 3 -- die teure: Selbstmessung gegen den Bezugsstand

Beides mit eigenem Werkzeug neu gemessen, nicht nachgelesen.

**Blattwertbilanz** (`messen.py`, Blob `6ef85077` gegen den Arbeitsbaum):

| gemessen | behauptet in `toml_geprueft` |
|---|---|
| 1229 → 1234 Blattwerte | 1229 → 1234 |
| 5 neue Schluessel: `datei.nachgezogen_durch.11`, `namensnennung.vollstaendigkeit`, `namensnennung.weltbank.gilt_fuer_reihen.8`, `namensnennung.weltbank.gilt_fuer_reihen.9`, `namensnennung.weltbank.hinweis` | dieselben fuenf, namentlich |
| keiner weggefallen | keiner |
| 2 gemeinsame Schluessel mit anderem Wert: `datei.stand`, `pruefweg.toml_geprueft` | dieselben zwei |
| Parserlauf: gueltiges TOML 1.0, `reihe` 19, `widerspruch` 9, Wurzel 6 Tabellen, Summe `sollreihen` = 27 = `zaehlung.sollreihen_gesamt`, zweimal eingelesen strukturgleich | ebenso |
| 1837 → 1840 Zeilen; `git diff --numstat` 6 hinzugefuegt, 3 entfernt | ebenso |

**Kommentare** (`kommentare.py`): 308 Kommentarzeilen vorher wie nachher, und der
Vergleich Zeile fuer Zeile ist zeichengleich wahr. Die Behauptung „dieses Paket hat
keinen einzigen geaendert" ist damit nicht nur der Zahl nach geprueft. Das war noetig,
weil genau an dieser Stelle das Paket 0099 seine vier Zeilenzahlen verfehlt hat.

**Die sechzehn Muster** (`muster.py`, alt gegen neu, jedes einzeln und nicht als Summe --
die fuenfzehn Zaehlmuster der sieben Schnitte plus die Typaufzaehlung hinter `schnitt_3`):

| Muster | alt | neu | gegen das Feld |
|---|---|---|---|
| `schnitt_1` Dezimalpunkt | 6 | 6 | 6 ✔ |
| `schnitt_2` Zeilen / Vorkommen / Randzeilen | 29 / 54 / 27 | 29 / 54 / 27 | 29 / 54 / 27 ✔ |
| `schnitt_3` Tabellenkoepfe | 114 | 114 | 114 ✔ |
| `schnitt_3` Typaufzaehlung | 19, 9, 23, 20, 39, 2, 2 (Summe 114) | gleich | „wieder dreiundzwanzig … kein achter Typ" ✔ |
| `schnitt_4` sechs Muster | 19, 19, 19, 152, 20, 28 | gleich | 19, 19, 19, 152, 20, 28 ✔ |
| `schnitt_5` zwei Muster | 21, 28 | gleich | 21, 28 ✔ |
| `schnitt_7` zwei Muster | 20, 2 | gleich | 20, 2 ✔ |

Alle sechzehn unveraendert. Die vom Arbeitspaket verlangte Aussage — `gilt_fuer_reihen`
steht auf einer Zeile, die keines der am Zeilenanfang verankerten Muster trifft, zwei
zusaetzliche Listeneintraege heben also keine der Zahlen — ist damit gemessen und nicht
uebernommen.

**Die sechs Trefferkontexte von `schnitt_1`** (`schnitt1.py`) sind zusaetzlich alt gegen
neu verglichen und zeichengleich dieselben; eine gleiche Zahl aus anderen Stellen waere
sonst unbemerkt geblieben. Sie decken sich mit den sechs Fundstellen, die `schnitt_1`
selbst aufzaehlt (Widerspruch Nr. 4 zweimal, Reihe 4, Reihe 10, Reihe 15, Reihe 17).

## Wonach ich ausserdem gesucht und nichts gefunden habe

- **Einheiten und Basisjahre.** Der Deflator der Reihe 14 nennt Basisjahr 2015 und den
  Teiler in Zehntausendsteln; `NE.EXP.GNFS.CD` (laufend) gegen `NE.EXP.GNFS.KD`
  (konstant, 2015) ist der richtige Quotient fuer einen Deflator. Dieses Paket aendert
  daran nichts, und der Vergleich der beiden Fassungen zeigt keinen Eingriff in ein
  Umrechnungsfeld.
- **Stille Interpolation.** Kein Feld der Deckung, des Bruchs oder der Konkordanz ist
  angefasst; die Zahlen 39 `reihe.deckung`, 2 `reihe.konkordanz`, 2 `reihe.bruch` stehen
  vor und nach dem Lauf gleich.
- **Lizenz.** Beide neu beanspruchten Quellen stammen aus `daten.md` (Nr. 1 und Nr. 3);
  es ist keine fuenfte Quelle hinzugekommen. Die Namensnennung steht im Produkt und nicht
  in einer Notiz — `namensnennung.drei_orte` ist unveraendert und nennt `LIZENZEN.md` und
  die Seite „Datenquellen".
- **Reproduzierbarkeit.** Zweimaliges Einlesen ergibt dieselbe Struktur; `datei.stand`
  traegt das Datum 2026-09-06.
- **Reihe 20 / ein neuer `[[reihe]]`-Block.** Das Paket verbietet ihn ausdruecklich. Die
  Liste `reihe` steht vor und nach dem Lauf bei 19, und `schnitt_3` zaehlt unveraendert
  114 Koepfe. Nicht geschehen.

**Nicht geprueft, und ich sage es, statt es zu verschweigen:** Die Zahlen des
Belegstellenriegels am Ende von `toml_geprueft` (40 Zitate gefunden, 40 aufgeloest, 47
Fundstellen uebergangen) habe ich nicht nachgemessen — der Aufruf des gebauten Riegels
war in diesem Lauf nicht ausfuehrbar. Die Sache dahinter ist trotzdem geprueft: Die zwei
woertlichen Zitate des neuen Feldes zeigen beide in diese Datei selbst und sind beide
zeichengleich (siehe Bedingung 1). Die Riegelzahlen gehoeren zu keiner der drei
Abnahmebedingungen.

## Befund 1 -- eine Mengengleichheit in `namensnennung.vollstaendigkeit` stimmt nicht

**Kein Rueckgabegrund.** Das Feld nennt die Ausnahme im naechsten Satz selbst, kein Leser
wird in die Irre gefuehrt, und Bedingung 2 ist erfuellt. Es steht hier, weil es messbar
falsch ist und weil dieses Repo eine Vorgeschichte mit genau dieser Satzsorte hat --
`zaehlregel_umrechnung` ist zweimal an einer Einzigkeitsbehauptung zurueckgegangen.

Das Feld sagt:

> „es fehlen genau die drei Reihen 17, 18 und 19 -- dieselben drei, deren `quelle_tabelle`
> das Wort `keine` fuehrt **und deren Block `reihe.lizenzbeleg` nach
> `pruefweg.zaehlregel_lizenz` leer ist**."

Der erste Konjunkt stimmt und ist ausschliesslich. Der zweite nicht: Leer sind vier und
nicht drei. So sagt es `zaehlregel_lizenz` selbst („Leer sind diese drei Felder allein bei
den Reihen 16, 17, 18 und 19"), so sagt es `schnitt_7` („Vier davon sind leer: die Reihen
16, 17, 18 und 19"), und so misst es `inhalt.py`:

```
Reihe 16  quelle_tabelle='BACI + WDI, abgeleitet nach T23 Punkt 5'  lizenzbelege=1 leer=True
Reihe 17  quelle_tabelle='keine'                                    lizenzbelege=1 leer=True
Reihe 18  quelle_tabelle='keine'                                    lizenzbelege=1 leer=True
Reihe 19  quelle_tabelle='keine'                                    lizenzbelege=1 leer=True
```

**Wie man es erzeugt:** `python3 befunde/messung-0100/inhalt.py daten/reihen.toml` und die
vier Zeilen mit `leer=True` gegen das Wort „dieselben drei" halten. Das Wort „dieselben"
behauptet Mengengleichheit; die zweite Menge hat vier Elemente.

Der Satz danach — „Reihe 16 ist dort nicht dabei: Sie fuehrt kein eigenes Wortlautfeld,
hat aber Fremdbestand ueber ihre Eingabereihen" — zeigt, dass der Fall gesehen wurde. Er
raeumt den Fehler aus, er behebt ihn nicht: Wer die Regel zitiert, zitiert den ersten
Satz.

Der Vorschlag steht als `aufgaben/0170-vollstaendigkeit-mengengleichheit-berichtigen.md`.
Er ist ausdruecklich als Beifahrer geschrieben und nicht als eigener Lauf; die Begruendung
dafuer steht dort.

## Was der Projektmanager nachziehen muss

Der Paketstatus. Ich setze ihn nicht.
