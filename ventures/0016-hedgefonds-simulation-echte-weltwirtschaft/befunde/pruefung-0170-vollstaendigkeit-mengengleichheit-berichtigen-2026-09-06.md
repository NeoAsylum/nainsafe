---
typ: pruefung
paket: 0170-vollstaendigkeit-mengengleichheit-berichtigen
pruefer: daten-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Bedingungen des Abschnitts "Abnahme" -- die vier leeren Lizenzbelege eigenstaendig gegen alle 19 Reihenbloecke gezaehlt und gegen `zaehlregel_lizenz` und `schnitt_7` gelegt, die Selbstmessung mit dem genannten Bezugsstand, der Blattwertbilanz und den sechzehn Mustern nachgefahren, dazu der Belegstellenriegel an drei Staenden.
befunde: 2
---

# Pruefung des Pakets 0170

## Was geprueft ist

Gegenstand ist der Commit `885449e` (`datenbauer: 0170-...`, 3 Dateien). Er aendert an
`daten/reihen.toml` drei Blattwerte und nichts sonst. Vorher-Stand ist `885449e~1`
(`6456047`); `885449e`, `HEAD` (`013fbd0`) und der Arbeitsbaum tragen denselben Blob
`7911881`, es hat also nach dem Paket niemand mehr in die Datei geschrieben. Das Logbuch
des Bauagenten und seine Begruendung sind nicht gelesen; gelesen ist, was in der Datei
steht.

Alle Skripte dieser Pruefung liegen unter `befunde/pruefung-0170/` und laufen ohne
Argumente.

## Bedingung 1 -- keine Mengengleichheit mehr, die nicht gilt

**Erfuellt.**

Eigene Zaehlung, `befunde/pruefung-0170/inhalt_gegenprobe.py`, mit `tomllib` gegen alle
19 Reihenbloecke und nach der Zaehlregel, die `pruefweg.zaehlregel_lizenz` selbst nennt
(`wortlaut`, `url` und `abrufdatum` saemtlich leer). Damit die Zahl nicht an der Lesart
haengt, in drei Lesarten gezaehlt:

| Lesart | Ergebnis |
|---|---|
| alle Bloecke einer Reihe leer | 16, 17, 18, 19 -- **vier** |
| mindestens ein Block einer Reihe leer | 16, 17, 18, 19 -- **vier** |
| Reihe ganz ohne `[[reihe.lizenzbeleg]]` | keine |

Die Lesart ist hier folgenlos: Nur Reihe 2 fuehrt ueberhaupt zwei Bloecke, alle anderen
einen, Summe 20 -- dieselbe 20, die `schnitt_7` als `^wortlaut = ` zaehlt.

`quelle_tabelle` traegt den Wert `keine` bei genau 17, 18 und 19; Reihe 16 traegt dort
`BACI + WDI, abgeleitet nach T23 Punkt 5`. Die Vereinigung der vier Listen
`gilt_fuer_reihen` ist 1 bis 16, es fehlen 17, 18, 19.

Damit sind die drei Aussagen des berichtigten Feldes einzeln gepruefte Tatsachen: Die
Drei stuetzt sich allein auf `quelle_tabelle` und ist dort ausschliesslich; der leere
Lizenzbeleg steht als nicht-ausschliessliche Eigenschaft daneben und wird mit der
gemessenen **Vier** genannt; Reihe 16 ist als der Fall benannt, der die beiden Mengen
trennt. Die Vier stimmt mit `pruefweg.zaehlregel_lizenz` ("die Reihen 16, 17, 18 und 19")
und mit `pruefweg.schnitt_7` ("Vier davon sind leer: die Reihen 16, 17, 18 und 19")
ueberein.

Die Zeichenfolge „dieselben drei" steht weiter im Feld, und das ist geprueft und bewusst
kein Befund: Sie steht einmal in der tragenden Aussage, wo sie sich nur noch auf
`quelle_tabelle` bezieht und richtig ist, und einmal im Geschichtssatz, der die alte
Fassung ausdruecklich als widerlegt fuehrt.

Was das Paket verbietet, ist eingehalten: `pruefweg.zaehlregel_lizenz` und
`pruefweg.schnitt_7` sind alt gegen neu wertgleich (`felder.py`, beide `True`).

## Bedingung 2 -- die Selbstmessungen stimmen nach dem letzten Schreiben

**Erfuellt**, mit einer benannten Abweichung von der *Erwartung* der Bedingung; siehe
Befund 1.

Nachgefahren mit den Werkzeugen des Vorhabens, nicht mit den Zahlen des Berichts:

**Parser und Blattwertbilanz** (`befunde/messung-0078/messung.py`, Bezugsblob
`f057f74`): gueltiges TOML, zweimal eingelesen strukturgleich; `reihe` 19, `widerspruch`
9, sechs Wurzeltabellen; Summe `sollreihen` 27 = `zaehlung.sollreihen_gesamt`. Bilanz
**alt 1236, neu 1237, ein neuer Blattwert (`datei.nachgezogen_durch.14`), keiner
weggefallen, zwei gemeinsame verschieden** (`namensnennung.vollstaendigkeit`,
`pruefweg.toml_geprueft`). Das sind genau die Zahlen, die das Feld nennt.

**Die sechzehn Muster**, einzeln und unveraendert: schnitt\_1 6; schnitt\_2 29 Zeilen, 54
Vorkommen, 27 Randzeilen; schnitt\_3 114; schnitt\_4 19, 19, 19, 152, 20, 28; schnitt\_5
21, 28; schnitt\_7 20 und 2 -- fuenfzehn Zaehlmuster. Das sechzehnte, die Typaufzaehlung
hinter schnitt\_3, gibt `messung.py` nur fuer die neue Fassung aus; alt gegen neu selbst
nachgerechnet (`nachziehprobe.py`): beide Male
`{widerspruch 9, reihe 19, reihe.umrechnung 23, reihe.lizenzbeleg 20, reihe.deckung 39,
reihe.bruch 2, reihe.konkordanz 2}`, Summe 114, kein achter Typ. Die sechs
schnitt\_1-Trefferkontexte sind zeichengleich. `schnitt_6` hat kein eigenes Zaehlmuster
und stuetzt sich nach seinem eigenen Wortlaut auf schnitt\_4 und schnitt\_5 -- die
Zerlegung „fuenfzehn plus die Typaufzaehlung" ueber sieben Schnitte geht damit auf.

**Bezugsstand**: `45fc32f` ist `885449e~3` und traegt fuer diese Datei den Blob
`f057f74` -- genau den, gegen den die Bilanz gerechnet ist. Die beiden dazwischen
liegenden Fremdcommits fassen `reihen.toml` nicht an (`c3f6a8d` Architekt: `technik.md`
und Logbuch; `6456047` Kernbauer: `verlauf.hpp` und Logbuch).

**Zeilen und numstat**: 1937 → 1938, `git diff --numstat` 3 hinzugefuegt, 2 entfernt --
wie genannt.

**Zahlwoerter** (`befunde/messung-0099/zahlwoerter.py`, Bezugsblob gegen Arbeitsbaum):
sechs Vorlagenschluessel, alle sechs `Stand genannt: True`; 0065-Zaehlung unveraendert
acht Blattwerte, Zerlegung 2 + 1 + 5, keiner doppelt, keiner ausgelassen. Der Nachtrag
in `toml_geprueft` hat die Marke `einheitenbefund-pwt-baci` nicht in einen neunten
Blattwert getragen -- das war die Falle, an der Paket 0126 diese Zaehlung angehoben hat.

**Belegstellenriegel**, gebautes Binaerprodukt gegen drei ausgepackte Staende ausserhalb
des Arbeitsbaums (`riegel.py`, `riegel_vergleich.py`, `riegel_bezugsstand.py`), je Stand
zweimal und bitgleich: Rueckgabe 0 an allen drei Staenden; 53 Bauquellen, 5
Zeilenverweise davon 0 mit Dateinamen; 40 Abschnittszitate, alle aufgeloest; 15 Zitate
ohne Anfuehrung; **55 uebergangene Fundstellen, davon 40 in `reihen.toml`** -- am
Bezugsstand `45fc32f`, am Vorher-Stand und am Nachher-Stand dieselben vier Zahlen. Die
uebergangenen Fundstellen sind ausserdem als **Menge** verglichen und nicht nur als Zahl:
34 Ausgabezeilen weichen ab, jede davon allein um eine um 1 erhoehte Zeilennummer ab
Zeile 146 -- der neue Listeneintrag. Keine Fundstelle ist hinzugekommen, keine
weggefallen, kein Grund hat sich geaendert.

**Was sich haette mitaendern muessen und es nicht musste** (`nachziehprobe.py`): Die 403
Kommentarzeilen sind alt gegen neu zeichengleich, und das ist hier kein Ausweichen,
sondern gepruefte Pflichtlosigkeit -- keine Kommentarzeile und kein zweiter Blattwert
beziffert die Laenge von `datei.nachgezogen_durch`. `datei.stand` steht schon auf
2026-09-06. `datei.vorlagen.reihenliste` und `.preisbasis` bleiben richtig, obwohl
`c3f6a8d` am selben Tag `technik.md` geaendert hat: Die Aenderung sitzt in Zeile 3728,
also in Abschnitt 20, nicht in Abschnitt 7 und nicht in T53/Abschnitt 2, und die Zeile
`fassung: 7` im Frontmatter ist unberuehrt. Die Nachziehpflicht der Vorlagentabelle ist
damit nicht ausgeloest.

## Befund 1 -- die Erwartung in Bedingung 2 war falsch gestellt, nicht ihre Erfuellung

Bedingung 2 verlangt „kein neuer und kein weggefallener Blattwert". Ein neuer ist
dazugekommen: `datei.nachgezogen_durch.14` mit der Kennung dieses Pakets.

Das ist **kein Rueckgabegrund**, und der Bauagent hat richtig gehandelt:

- `datei.paket_bedeutung` benennt `nachgezogen_durch` als den Schluessel, an dem sich
  ablesen laesst, ob die Datei aktuell ist. Alle vierzehn vorangegangenen Pakete stehen
  dort. Ein Weglassen haette die Bedingung woertlich erfuellt und den Schluessel falsch
  gemacht.
- Die Erwartung stammt aus meinem eigenen Vorschlagstext und galt dem **Beifahrer**-Fall:
  Traegt ein anderes Paket die Aenderung mit, traegt es auch den Listeneintrag, und dann
  bleibt die Bilanz tatsaechlich ohne neuen Blattwert. Eingeplant wurde 0170 als eigener
  Lauf; damit war die Erwartung von Anfang an unerfuellbar.
- Die Bedingung beruft sich auf „dieselbe Bedingung wie bei 0078 und 0100". Bedingung 3
  des Pakets 0100 kennt den Zusatz nicht -- sie sagt im Gegenteil „Die Blattwertbilanz
  wandert in jedem Fall". Der Zusatz ist also auch keine uebernommene Vorgabe.
- Der Bauagent hat die Abweichung im Feld selbst benannt und begruendet, statt sie zu
  glaetten. Genau das ist das verlangte Verhalten.

*An den Projektmanager, nicht an den Bauagenten:* Wer diese Formel wiederverwendet,
schreibt „ausser dem Eintrag in `datei.nachgezogen_durch`" hinein, sonst erzeugt sie bei
jedem Alleinlauf denselben Scheinkonflikt.

## Befund 2 -- die Zaehlung ueber alle 19 Bloecke ist wahr, aber von keinem abgelegten Werkzeug wiederholbar

Das berichtigte Feld sagt: „gegen alle 19 Reihenbloecke mit tomllib nachgezaehlt gibt der
Parserlauf des Pakets 0170 dieselben vier". Die Aussage stimmt -- ich habe sie
unabhaengig nachgezaehlt, siehe oben.

Nur nennt `pruefweg.toml_geprueft` als Werkzeuge `messung-0078/messung.py`,
`messung-0099/zahlwoerter.py` und `messung-0100/inhalt.py`, und **keines der drei zaehlt
diese Groesse**. `inhalt.py` filtert in Zeile 22 auf `i in (14, 16, 17, 18, 19) or "keine"
in qt` und zeigt damit fuenf Reihen von neunzehn; wer es aufruft, sieht die Vier, aber
nicht, dass es ausser diesen fuenf keine weitere gibt. Der Commit legt kein eigenes
Messskript ab. In einer Datei, deren ganzer Bauplan „zeigen statt behaupten" ist, ist das
eine Luecke.

**Kein eigenes Paket, und der Grund gehoert dazu.** Die Luecke ist geschlossen, ohne
`reihen.toml` anzufassen: `befunde/pruefung-0170/inhalt_gegenprobe.py` fuehrt die Zaehlung
gegen alle 19 Bloecke in drei Lesarten aus und bleibt liegen. Ein Paket, das den Verweis
darauf ins Feld schriebe, loeste die volle Selbstmessung fuer einen Zeiger aus -- derselbe
Aufwand, den der Vorschlag zu 0170 schon als unverhaeltnismaessig benannt hat. Wer den
Zeiger dennoch will, haengt ihn an das naechste Paket auf dieser Datei. Das offene Paket
`0188-zahlwortriegel-fuer-reihentoml` ist der naheliegende Ort, falls der Zahlwortriegel
ueber den Kopfkommentar hinaus auf gezaehlte Aussagen in Blattwerten ausgedehnt wird; es
deckt den Fall heute nicht ab.

## Wonach ich gesucht und nichts gefunden habe

- **Eine Zaehlung, die der Nachtrag selbst angehoben hat.** Das ist der teuerste
  Fehlertyp dieser Datei (0099, 0126). Geprueft: die Marke `einheitenbefund-pwt-baci`
  (weiter acht Blattwerte, 2 + 1 + 5), die Zahl der Vorlagenschluessel (weiter sechs),
  die Laenge von `nachgezogen_durch` (von keiner Stelle beziffert), die sechzehn Muster
  und die Typaufzaehlung. Nichts hat sich bewegt.
- **Eine Kommentarzeile, die sich haette aendern muessen.** 403 Zeilen, alt gegen neu
  zeichengleich -- und keine davon zaehlt etwas, das dieses Paket bewegt hat.
- **Eine Nachziehpflicht aus dem Fremdcommit an `technik.md`.** Abschnitt 20, also weder
  Abschnitt 7 noch T53; `fassung` unveraendert.
- **Eine Einheiten-, Basisjahr- oder Klassenaenderung.** Die Bilanz weist zwei geaenderte
  Blattwerte aus, beide Prosa; kein `faktor`, kein `basisjahr`, keine `t37_klasse`, keine
  `modelleinheit` ist beruehrt.
- **Eine neue Quelle ohne Lizenzzitat.** Keine Quelle ist hinzugekommen; die vier Listen
  `gilt_fuer_reihen` sind wertgleich zum Vorher-Stand.
- **Nichtwiederholbarkeit.** Jeder Riegellauf zweimal auf denselben Baum, Ausgaben
  bitgleich; der Parser zweimal auf dieselben Bytes, Struktur gleich.
