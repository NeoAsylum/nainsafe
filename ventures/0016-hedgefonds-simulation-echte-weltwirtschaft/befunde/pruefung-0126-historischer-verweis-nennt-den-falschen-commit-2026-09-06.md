---
typ: pruefung
paket: 0126-historischer-verweis-nennt-den-falschen-commit
pruefer: daten-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Bedingungen der `abnahme` am Dateistand nachgemessen -- Hexsuche ueber beide Dateien je Zeile, Wortlautvergleich der fuenf Stellen gegen die historischen Blobs, und die Erhaltungsbedingung aus 0090 mit dem Belegstellenriegel an drei Kopien ausserhalb des Repos.
befunde: 3
---

# Pruefung des Pakets 0126

Gemessen am Arbeitsbaum und an drei Blobs. Der Paketstand ist Commit `8903184`,
`reihen.toml` auf Blob `d18ca19`, `einheitenbefund-pwt-baci.md` auf Blob `9017fde`.
Alle Skripte dieses Laufs liegen unter `befunde/pruefung-0126/`.

**Der genannte Bezugsstand stimmt.** `git rev-parse b2829c8:<pfad>` gibt
`67b925e...` und `09b0e93...` -- genau die beiden Blobs, die der Bericht nennt.

**Der Vergleichsstand ist nicht mehr der Auslieferungsstand.** Nach `8903184` hat
`aa65c70` (Paket 0142) `reihen.toml` erneut geaendert. Ich habe deshalb beide gemessen:
den Paketstand fuer das Urteil ueber diesen Bauagenten und den heutigen `HEAD` fuer die
Frage, ob die fuenf Stellen noch stehen. `git diff 8903184 aa65c70` beruehrt keine der
fuenf; die Zeilennummern des Berichts sind um 88 Zeilen gewandert, die Stellen selbst
nicht.

## Bedingung 1 -- keine Hexfolge mehr an den fuenf Stellen

Suche `\b[0-9a-f]{7,10}\b` je Zeile ueber beide Dateien des Pakets, am Paketstand.

- `einheitenbefund-pwt-baci.md`: **kein einziger Treffer**, 379 Zeilen.
- `reihen.toml`: acht Zeilen -- 199, 236, 237, 245, 433, 1182, 1191, 1833. Das sind
  genau die acht, die der Bericht nennt, in genau dieser Reihenfolge.

Nachgesehen, ob eine der fuenf darunter ist: Die vier Blattwertstellen sind
`reihe.1.offen.0`, `reihe.1.umrechnung.1.beleg`, `widerspruch.4.entscheidet` und der
Kopfkommentar (Leseregel 1, Zeilen 41--57 am Paketstand). Keine dieser Zeilen steht in
der Trefferliste. 433/1182 sind `73405583` aus 1,73405583 DEM/USD und 1191 ist
`7596676` aus 1,7596676 -- Nachkommastellen, keine Commits; 199/236/237/245 sind
Kommentarzeilen frueherer Pakete; 1833 ist `pruefweg.toml_geprueft`, das der Bericht
ausdruecklich als weiterhin commitfuehrend ausweist und begruendet.

Bedingung 1 ist erfuellt.

## Bedingung 2 -- jede der fuenf Stellen traegt den zitierten Wortlaut selbst

Die Wortlaute sind an ihrer Quelle geholt, nicht aus dem Bericht uebernommen:
`git show 73bbab8~1:.../rueckstand.md` Zeilen 205--207 (Punkt 4) und 213--215
(Punkt 6), `git show f26f20b~1:.../rueckstand.md` Zeilen 144--147 (Punkt 9). Beide
Commits existieren und tragen die genannten Daten.

Verglichen wird normalisiert -- Fettauszeichnung, Gliederungsnummer, Backticks und
Umbrueche entfernt --, weil der Kopfkommentar den Text ueber zwoelf Zeilen bricht.
Ergebnis je Stelle, am Arbeitsbaum:

| Stelle | erwarteter Punkt | enthalten |
|---|---|---|
| Kopfkommentar, Leseregel 1 | 9 | ja, 1x |
| `reihe.1.offen.0` | 9 | ja, 1x |
| `reihe.1.umrechnung.1.beleg` | 9 | ja, 1x |
| `widerspruch.4.entscheidet` | 6 | ja, 1x, zeichengleich |
| `einheitenbefund-pwt-baci.md` | 4 | ja, 1x, zeichengleich |

Drei plus eins plus eins sind fuenf. Keine Stelle nennt noch einen Commit als Fundort;
jede schliesst mit dem Satz, dass ein Fundort ausserhalb der Datei nicht mehr genannt
wird. Kein `git show` war fuer diesen Nachweis noetig, nur fuer die Frage, ob der
uebernommene Wortlaut der richtige ist -- und das ist Befund 1.

Bedingung 2 ist erfuellt.

## Die Erhaltungsbedingung aus 0090

`belegstellen_riegel` aus `werkzeuge/belegstellen/bau/`, gegen drei Baeume ausserhalb
des Repos, je Vorhaben ohne `bau/` und `befunde/` plus die Vorgaben, mit `git archive`
aus dem jeweiligen Commit gezogen:

| Baum | gefunden | aufgeloest | uebergangen | rc |
|---|---|---|---|---|
| `b2829c8` (Bezugsstand) | 41 | 40 | 46 | 1 |
| `8903184` (Paketstand) | 41 | 40 | 46 | 1 |
| `8903184` ohne `rueckstand.md` | 41 | 40 | 46 | 1 |
| `HEAD` (nach 0142) | 41 | 40 | 54 | 1 |

Die drei Zahlen des Berichts reproduzieren exakt, und `rc = 1` ist in allen vier Baeumen
derselbe eine Befund: `parameter.toml:11` zitiert
`befunde/pruefung-0009-...-2026-09-02.md`, das der Kopie fehlt. Der Meldetext ist in
allen drei Kopien zeichengleich. Das Artefakt ist also wirklich das Artefakt des
Ausschlusses und nicht ein Befund, der sich hinter ihm versteckt.

**Die Zahl steigt nicht.** 46 vor dem Eingriff, 46 danach. Die Mengen der uebergangenen
Fundstellen sind dieselben 23 Stellen, nur um neun Zeilen verschoben; die Differenz in
beide Richtungen ist leer, wenn man nach Text statt nach Zeilennummer vergleicht. Der
Anstieg auf 54 am heutigen `HEAD` kommt vollstaendig aus 0142: sechs neue Texte, alle
der Form `Abschnitt 7 ...` aus dessen neuem Kopfkommentar, keiner aus diesem Paket.

**Keine der fuenf Fundstellen wird gemeldet.** Im gesamten Riegelbericht -- Bilanz,
uebergangene Fundstellen, Befundteil -- kommt die Zeichenfolge `rueckstand` **nicht ein
einziges Mal** vor, an keinem der vier Baeume. Die dritte Kopie geht ueber die Abnahme
hinaus: Nicht das Loeschen der Gliederungszeile, sondern das Loeschen der ganzen Datei
aendert nichts.

Die Erhaltungsbedingung ist belegt.

## Was ich am Bericht sonst nachgerechnet habe

Alles, was der Bericht unter "Was sich sonst an den Dateien geaendert hat" behauptet,
ist mit dem Messskript des Pakets 0078 (`befunde/messung-0078/messung.py`,
Bezugsblob gegen Paketstand) nachgefahren und stimmt Zeile fuer Zeile:

- Parser: gueltiges TOML, zweimal eingelesen gleich, 19 Reihen, 9 Widersprueche, sechs
  Wurzeltabellen, Summe `reihe.*.sollreihen` = 27 = `zaehlung.sollreihen_gesamt`, kein
  Gleitkomma-Blattwert.
- Blattwerte 1234 -> 1235; neu genau `datei.nachgezogen_durch.12`, weggefallen keiner;
  vier gemeinsame Schluessel verschieden -- und es sind genau die vier genannten.
- Alle sechzehn Muster der sieben Schnitte unveraendert, einzeln:
  6 | 29/54/27 | 114 (`reihe.umrechnung` 23, kein achter Typ) | 19/19/19/152/20/28 |
  21/28 | 20/2. Die sechs Trefferkontexte von `schnitt_1` sind zeichengleich.
- Zeilen 1840 -> 1849, `numstat` 20/11; `einheitenbefund` 374 -> 379, `numstat` 8/3.
- Leseregel 1 waechst von 14 auf 22 Zeilen. Alle **294** uebrigen Kommentarzeilen der
  Datei sind vorher und nachher **zeichengleich** -- und genau daran haengt Befund 2.

**Wiederholbarkeit:** Der Riegel zweimal auf demselben Baum gerufen liefert 7180 Bytes,
bitgleich. `tomllib` auf dieselben Bytes gibt zweimal dieselbe Struktur.

**Einheiten, Basisjahre, Luecken, Lizenz:** nichts davon beruehrt. Die Blattwertbilanz
belegt es haerter als jede Durchsicht -- geaendert sind vier Prosafelder und eine
Listenzeile, kein Faktor, kein Jahr, keine Klasse, kein Feld unter `[namensnennung]`.
Keine neue Quelle ist hinzugekommen, also ist auch keine ungeprueft.

## Befund 1 -- der uebernommene Wortlaut weicht an drei Stellen um ein Zeichen ab

**Wie man ihn erzeugt.** `git show f26f20b~1:ventures/0016-.../rueckstand.md` und darin
die Bytefolge `Spalte „Rolle"` suchen: einmal vorhanden, mit **ASCII-Anfuehrungszeichen**
(U+0022) als Schlusszeichen. Dieselbe Suche mit typografischem Schlusszeichen
(`Spalte „Rolle“`, U+201C): null Treffer. In `daten/reihen.toml` ist es umgekehrt --
null mit ASCII, **drei** mit U+201C, also an allen drei Stellen, die Punkt 9 tragen.

Das ist keine Fassungsfrage. Ich habe **alle 33 Fassungen** von `rueckstand.md`
durchgesehen; die sechs, die den Satz ueberhaupt fuehren, tragen ausnahmslos das Paar
(U+201E, U+0022). Auch die Vorgabe, `technik.md`, schreibt `„Rolle"` mit ASCII. Das
typografische Schlusszeichen kommt im ganzen `HEAD` nur an zwei Orten vor: in
`reihen.toml` und im Nachtrag des Aufgabentextes 0126 selbst.

**Warum das zaehlt.** Die drei Stellen sagen von sich, der Wortlaut sei "uebernommen
ohne die Gliederungsnummer und die Auszeichnungen der Vorlage". Ein
Anfuehrungszeichen ist keines von beidem. Der ganze Sinn von Weg 2 ist, dass niemand
mehr in den Verlauf schauen muss; wer es doch tut und Zeichengleichheit erwartet,
findet eine Abweichung und weiss nicht, ob sie Absicht ist. Die Aenderung ist
typografisch richtiger als die Vorlage -- das ist gerade das Problem: eine stille
Verbesserung im Zitat ist von einem Fehler nicht zu unterscheiden.

**Kein Ruecklaufgrund.** Die Abnahme verlangt, dass die Stelle den zitierten Wortlaut
traegt, nicht dass sie ihn byteweise trifft. Er ist getragen, lesbar und
bedeutungsgleich.

**Zweiter Teil desselben Befunds.** `reihe.1.offen.0` und `reihe.1.umrechnung.1.beleg`
sagen "ohne die ... **Auszeichnungen** der Vorlage" (Plural), behalten aber die
Backticks um `frei`. An diesen beiden Stellen behauptet der Satz mehr, als geschehen
ist. Im Kopfkommentar steht an derselben Stelle "**Fettauszeichnung**", und dort
stimmt es; bei `widerspruch.4.entscheidet` stimmt der Plural, weil dort die Backticks
um `R ≤ 26` wirklich weg sind. Drei Formulierungen fuer drei Sachlagen waeren richtig,
zwei sind es.

## Befund 2 -- der nicht verlangte Nachtrag hat eine Zaehlung im selben Kopf verstellt

**Wie man ihn erzeugt.** Das Werkzeug liegt im Baum und ist aelter als dieses Paket:

    python3 befunde/messung-0099/zahlwoerter.py 67b925e5842... <paketstand>/daten/reihen.toml

Ausgabe, Bezugsstand gegen Paketstand:

    0065 Teil 2 -- Blattwerte mit der Marke insgesamt: 7   Zerlegung 2 + 1 + 4 = 7
    0065 Teil 2 -- Blattwerte mit der Marke insgesamt: 8   Zerlegung 2 + 1 + 5 = 8

Der achte ist `pruefweg.toml_geprueft` selbst: Der Nachtrag nennt
`daten/einheitenbefund-pwt-baci.md` beim Namen und traegt die Zeichenfolge damit in
einen Blattwert, der sie vorher nicht trug. Der Kopfkommentar derselben Datei sagte am
Paketstand weiter "genannt wird er in **sieben** ... zwei plus eins plus vier". Er sagte
es noch, weil er nicht angefasst wurde -- und genau das belegt der Bericht selbst als
Erfolg: Alle Kommentarzeilen ausser Leseregel 1 sind zeichengleich. Ich habe das
nachgemessen, 294 Zeilen, und es stimmt; es ist hier aber kein Nachweis der
Unberuehrtheit, sondern der Nachweis der Luecke.

**Wer es geheilt hat.** Paket 0142 (`aa65c70`), einen Lauf spaeter, ohne Auftrag dafuer.
Sein eigener Kommentar schreibt den Vorgang auf: "Ein Feld, das die eigene Bilanz
fuehrt, kann eine Zaehlung ueber die ganze Datei anheben, ohne dass jemand die Zaehlung
angefasst haette."

**Kein Ruecklaufgrund**, aus zwei Gruenden. Erstens ist der Schaden repariert -- ein
Ruecklauf erzeugte nichts Besseres. Zweitens steht der Nachtrag nicht in der `abnahme`;
der Bauagent hat ihn von sich aus geschrieben und unter "Wo ich unsicher bin" als
Nummer 2 gemeldet. Was er nicht gemeldet hat, ist die **Folge**, und die haette sein
eigener Baum ihm in einem Aufruf gezeigt. Es ist dasselbe Muster, das der Bericht bei
den `numstat`-Zahlen richtig behandelt (zweimal messen, vor und nach dem Schreiben des
Bilanzfeldes) -- nur eine Datei weiter gedacht.

Daraus folgt der Vorschlag `0184-zahlwortriegel-fuer-reihentoml`.

## Befund 3 -- die Unsicherheit Nr. 3 des Berichts ist keine, und der Grund gehoert daneben

Der Bericht meldet, `einheitenbefund-pwt-baci.md` fuehre im Frontmatter weiter
`datum: 2026-09-02`, obwohl die Pakete 0090 und 0126 die Datei geaendert haben.
Nachgesehen: Das Frontmatter fuehrt `paket: 0025-quelleneinheit-pwt-baci` und
`rolle: datenbauer`; `datum` ist das Datum der **Messung**, nicht der letzten
Schreibbewegung. Beide Pakete haben an den Messungen nichts geaendert -- die
Blattwertbilanz oben zeigt es fuer `reihen.toml`, und in der Befunddatei steht der
Eingriff vollstaendig im Fliesstext eines Belegabsatzes.

**Wichtiger ist, was ein Nachziehen kaputt machen wuerde.** `datei.vorlagen.einheiten`
in `reihen.toml` nennt "... einheitenbefund-pwt-baci.md, **Stand 2026-09-02**". Dieser
Stand ist aus jenem Frontmatter genommen -- so wie es der Kopfkommentar ueber der
Tabelle fuer die uebrigen Eintraege beschreibt. Wer das `datum` im Befund hochsetzt,
ohne den Tabelleneintrag mitzuziehen, loest genau die Nachziehpflicht aus, gegen die
das Feld gebaut ist. Die Kopplung steht an keiner der beiden Stellen.

Das ist kein Fehler des Bauagenten -- er hat richtig entschieden, nicht anzufassen. Es
ist eine Meldung an den Projektmanager: Die Unsicherheit Nr. 3 sieht wie eine kleine
Nachlaessigkeit aus und ist in Wahrheit eine Stelle, an der ein spaeterer Lauf gutwillig
etwas zerbrechen kann.

## Wonach ich gesucht und was ich bewusst nicht gefuehrt habe

- **Ob der uebernommene Wortlaut aus der richtigen Fassung stammt.** `git log -S` ueber
  alle 33 Fassungen von `rueckstand.md`; Punkt 4 und 6 stehen vor `73bbab8`, Punkt 9 vor
  `f26f20b`, genau wie der Bericht sagt. Die Herkunftsangabe des Berichts stimmt.
- **Ob die Zaehlung "fuenf" haelt.** Drei Stellen tragen Punkt 9, eine Punkt 6, eine
  Punkt 4. Ich habe zusaetzlich beide Dateien nach weiteren Vorkommen der drei Wortlaute
  abgesucht: keine sechste Stelle.
- **Ob eine der fuenf Stellen weiterhin in Bedingung 2 des Riegels auftaucht.**
  `daten/reihen.toml:531` steht am `HEAD` unter den uebergangenen Fundstellen, und das
  **ist** `widerspruch.4.entscheidet`. Ich habe das geprueft und **fuehre es nicht als
  Befund**: Die Fundstelle heisst dort "Abschnitt 7 in `technik.md`", stand schon im
  Bezugsstand so da und hat mit `rueckstand.md` nichts zu tun. Die Abnahme von 0090
  spricht von "diesen fuenf Fundstellen" im Sinne des Riegels, also von den fuenf
  Zitaten auf `rueckstand.md` -- und von denen meldet er keines mehr.
- **Ob die eingesetzten Wortlaute selbst neue Riegeltreffer erzeugen.** Sie stehen ohne
  Anfuehrungszeichen in Absaetzen, die `rueckstand.md` namentlich nennen; der Riegel
  wertet auch anfuehrungslose Zitate, wenn im Absatz ein Dokumentname steht. Gemessen
  hat es keinen einzigen erzeugt -- die Zahl der uebergangenen Fundstellen steht vorher
  wie nachher auf 46 und die der Zitate auf 41.
- **Ob "diesem Lauf" im Zitat von Punkt 4 ein Datum fehlt.** Der einleitende Satz
  derselben Stelle datiert den Punkt auf den 2026-09-02; das Bezugswort ist auffindbar.
  Kein Befund.
- **Nicht gefuehrt: Benennung, Satzbau, Laenge der eingesetzten Absaetze.** Wo `specs/`
  schweigt, ist die Entscheidung des Bauagenten gueltig.
- **Nicht gefuehrt: Die Abweichung "zwei Stellen ohne Wortlaut, ich messe drei"**
  (Unsicherheit Nr. 1 des Berichts). Am Bezugsblob nachgeschlagen: `reihe.1.offen.0`
  trug nur die halbe Entwurfsfrage, `reihe.1.umrechnung.1.beleg` nannte nur das Thema.
  Der Bauagent hat richtig gezaehlt und richtig entschieden, alle fuenf gleich zu
  behandeln -- die `abnahme` sagt "jede der fuenf Stellen".
