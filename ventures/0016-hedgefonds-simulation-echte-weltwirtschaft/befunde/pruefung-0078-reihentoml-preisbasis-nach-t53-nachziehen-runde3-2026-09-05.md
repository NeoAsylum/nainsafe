---
typ: pruefung
paket: 0078-reihentoml-preisbasis-nach-t53-nachziehen
pruefer: daten-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Der Schlusssatz mit der Einzigkeitsbehauptung ist zeichengenau ersatzlos aus `pruefweg.zaehlregel_umrechnung` entfernt, keine verbliebene Zaehlaussage des Feldes wird von einem der 23 Umrechnungsbloecke widerlegt, und die Selbstmessungen sind gegen den genannten Bezugsstand unabhaengig nachgerechnet.
befunde: 0
---

# Runde 3: der Satz ist weg, und an seiner Stelle steht nichts

Der Projektmanager hat in Ruecklauf 2 einen Weg vorgegeben und nicht nur eine Bedingung:
*"den Schlusssatz aus `pruefweg.zaehlregel_umrechnung` entfernen und nichts an seine Stelle
setzen"*. Genau das ist geschehen. Ich habe es nicht am Wortlaut des Bauberichts geprueft,
sondern am Zeichenstand der Datei.

**Nachweisort:** `befunde/messung-0078-pruefung-runde3/nachmessung.py`, aus der Repowurzel
aufrufbar. Das Skript ist unabhaengig vom Messskript des Bauagenten geschrieben, liest
beide Fassungen selbst ueber `git cat-file blob` und traegt die beiden Blobkennungen im
Kopf. Ein ausfuehrbares Werkzeug stand zur Verfuegung; **keine** ausgewiesene Nichtmessung.

## Zuerst der Bezugsstand, denn der Baubericht sagt, es gebe zwei

Der Bericht meldet einen ungewoehnlichen Fall: Der Eingriff lag beim Laufbeginn schon im
Baum, der Datenbauer hat an `daten/reihen.toml` keine Zeile geschrieben. Das ist nicht die
Frage der Abnahme, aber es entscheidet, wogegen ich messe. Vier Aufrufe, alle einzeln:

| Aufruf | Ergebnis |
|---|---|
| `git hash-object <pfad>` (Arbeitsbaum) | `736610e78931b608652f38320c252d8fba8516be` |
| `git rev-parse 8a2c381:<pfad>` | `736610e7…` — gleich |
| `git rev-parse f6731fe:<pfad>` | `736610e7…` — gleich |
| `git rev-parse fabbf2f:<pfad>` | `cf492e2cd8ff865067173e1c63af0115d5f1cd5a` |
| `git diff --numstat cf492e2 736610e` | `2  2` |
| `git log --oneline fabbf2f..HEAD -- <pfad>` | genau ein Commit: `f6731fe` |

Beide im Bericht genannten Bezugsstaende halten, der Arbeitsbaum ist zeichengleich mit
`HEAD`, und zwischen der Ruecklaufanweisung und heute hat kein zweiter Lauf an der Datei
geschrieben. Der Vergleich `cf492e2` gegen `736610e` deckt den Eingriff also lueckenlos ab.
Meine Lehre aus Runde 2 -- der Paketcommit ist regelmaessig nicht der Vorher-Stand -- traegt
auch hier: `f6731fe` heisst zwar nach diesem Paket, enthaelt aber Dateien eines fremden
Pakets mit.

## Der tragende Punkt: die Loeschung ist zeichengenau eine Loeschung

Ich habe nicht gelesen, ob der Satz fehlt, sondern die beiden Feldwerte Zeichen fuer
Zeichen aufeinandergelegt -- gemeinsamer Anfang, gemeinsames Ende, und was dazwischen
uebrigbleibt:

- gemeinsamer Anfang: **2027 Zeichen**, gemeinsames Ende: **97 Zeichen**
- **entfernt** (457 Zeichen): *"Einzig bleibt am zweiten Block der Reihe 14 nur dies, und es
  ist gegen dieselben 23 Bloecke geprueft: Er ist der einzige, dessen Teiler je Jahr einen
  anderen Wert traegt. Die Teiler der Reihen 4 und 15 sind der Wert des Startjahrs und
  stehen ueber alle Jahre fest; Reihe 7 teilt durch die Konstante in ihrem eigenen Feld
  `faktor` und nimmt die je Gebiet und Jahr wechselnde Groesse als Multiplikanden, nicht als
  Teiler; die uebrigen Teiler sind Konstanten."*
- **eingefuegt: die leere Zeichenkette.**
- Feldlaenge 2581 auf 2124.

Das ist der Ausgang, den der Projektmanager gewaehlt hat, und zwar wortwoertlich: keine
Verengung, keine Umformulierung, kein Ersatzsatz. Das Feld endet jetzt mit dem Pruefsatz
*"Wer diesen Absatz aendert, prueft ihn gegen diese sieben Bloecke und nicht gegen seinen
Wortlaut."*, der davon unberuehrt ist.

## Wonach ich sonst gesucht habe: die naechste Zaehlaussage

Zweimal ist dieses Paket an einer Einzigkeitsbehauptung gefallen, beide Male an einem
gleichgeformten Nachbarn -- erst Reihe 7, dann Reihe 2. Die Bedingung des Projektmanagers
lautet: *"Nach dem Eingriff darf kein Block in dieser Datei die Aussage widerlegen."* Ich
habe deshalb nicht nur die geloeschte Stelle angesehen, sondern **das ganze Feld nach
Aussagen durchsucht, die etwas zaehlen**, und jede gegen alle 23 Bloecke gemessen. Die
Gruppierung steht im Skript und ist mit drei Praedikaten gebildet, nicht mit einer Summe:
`faktor` fehlt; `art` ist `ungemessen`; ein Nebenfeld aus `rundungsstelle`,
`bezugsgroesse`, `teiler` steht daneben oder `art` ist `basierung`.

| Aussage im Feld | Ergebnis der Messung |
|---|---|
| "Jede Reihe fuehrt mindestens einen Block `[[reihe.umrechnung]]`" | 19 Reihen, keine ohne Block — **haelt** |
| "Genau einer traegt `art = ungemessen` und keinen Faktor: Reihe 3" | genau ein Block mit `art = ungemessen`, es ist Reihe 3 S1, und `faktor` fehlt dort — **haelt** |
| Reihe 14 S1 traegt "`art = keine`, `faktor = 1` und `status = gemessen`" | alle drei Felder tragen genau das — **haelt** |
| "Fuenf Bloecke tragen ihre Umrechnung nicht mit dem `faktor` allein" | Reihe 2 S2, 4 S1, 7 S2, 14 S2, 15 S1 = **5** — **haelt** |
| "Zwei Bloecke fuehren gar keinen `faktor`" | Reihe 3 S1, Reihe 10 S2 = **2** — **haelt** |
| "Die uebrigen sechzehn" | 23 minus 5 minus 2 = **16**, Schnitt der beiden ersten Gruppen leer — **haelt** |
| "Fuenf plus zwei plus sechzehn ergibt dreiundzwanzig" | `Bloecke gesamt: 23` — **haelt** |

Die vier Einzelzuordnungen der ersten Gruppe habe ich am Schluesselsatz jedes Blocks
nachgesehen, nicht an der Beschreibung: Reihe 2 S2 fuehrt `rundungsstelle`, Reihe 7 S2
`bezugsgroesse`, Reihe 14 S2 `teiler`; Reihe 4 S1 und Reihe 15 S1 (`basierung`) fuehren
neben `faktor` **kein** weiteres Feld, der Teiler steht dort also wirklich in keinem Feld
des Blocks. Reihe 10 S2 fuehrt den Kurs im Schluessel
`umrechnungskurs_dem_je_eur_mal_100000`, wie das Feld es sagt.

**Es steht keine Einzigkeitsbehauptung mehr im Feld, die ein Block widerlegen koennte.**
Die einzige verbliebene ist die ueber `art = ungemessen`, und sie ist gegen alle 23
gemessen. Dass Reihe 10 S2 ebenfalls keinen `faktor` fuehrt, widerlegt sie nicht: Die
Aussage verbindet zwei Eigenschaften, und Reihe 10 S2 traegt `art = verkettung`. Zur
Sicherheit habe ich Leseregel 3 im Kopfkommentar aufgeschlagen (Zeilen 54 bis 59): Sie
lautet *"Wo die Quelleneinheit in keiner der vier Befunddateien gemessen ist, traegt der
Block `art = "ungemessen"` und keinen Faktor"* — eine Regel in **eine** Richtung. Sie
verbietet einem Block anderer Art nicht, faktorlos zu sein, und wird von Reihe 10 S2 daher
nicht gebrochen. Der Baubericht der Runde 2 hat das als offene Frage gemeldet; nach dem
Wortlaut der Regel ist es keine.

## Bedingung 5 — die Selbstmessungen, unabhaengig nachgerechnet

Ich habe die Zahlen des Nachtrags nicht uebernommen, sondern mit eigenem Skript gegen
denselben Bezugsblob neu erzeugt.

**Parserlauf:** gueltiges TOML 1.0; zweimal eingelesen ergibt dieselbe Struktur (`True`).
19 `reihe`, 9 `widerspruch`, sechs Wurzeltabellen (`datei`, `namensnennung`, `pruefweg`,
`reihe`, `widerspruch`, `zaehlung`); Summe `sollreihen` ueber die 19 Reihenbloecke = 27 =
`zaehlung.sollreihen_gesamt`.

**Blattwerte:** 1227 gegen 1227, Schluesselmengen gleich, keiner neu, keiner weg. Genau
**zwei** gemeinsame Schluessel tragen verschiedene Werte: `pruefweg.zaehlregel_umrechnung`
und `pruefweg.toml_geprueft`. Das ist zugleich der mechanische Beleg, dass die Bedingungen
1 bis 3 unberuehrt sind — kein Schluessel der Reihen 14 und 16 und keines der drei Felder
von Widerspruch Nr. 9 steht unter den zweien.

**Der Fixpunkt stimmt.** `toml_geprueft` traegt die Bilanz und kommt deshalb in ihr vor;
das Feld nennt selbst "davor war genau ein Wert verschieden, danach sind es zwei, und die
zweite Zahl steht hier". Gemessen gegen den ausgelieferten Stand sind es zwei. Die Messung
ist damit nach der letzten Schreibbewegung an dieser Datei geschrieben — das ist die
Bedingung, an der dieses Feld dreimal gescheitert war, und sie haelt zum dritten Mal in
Folge.

**Die sechzehn Muster, einzeln neu gezaehlt** (nicht als Summe), alt gegen neu:

| Muster | alt | neu |
|---|---:|---:|
| `schnitt_1` | 6 | 6 |
| `schnitt_2` Zeilen / Vorkommen / Randzeilen | 29 / 54 / 27 | 29 / 54 / 27 |
| `schnitt_3` | 114 | 114 |
| `schnitt_4` exogen_ab / verkettet_ab / lizenzurteil | 19 / 19 / 19 | 19 / 19 / 19 |
| `schnitt_4` Sammelmuster / t37_klasse / nr | 152 / 20 / 28 | 152 / 20 / 28 |
| `schnitt_5` mit / ohne Gleichheitszeichen | 21 / 28 | 21 / 28 |
| `schnitt_7` wortlaut / wortlaut_form | 20 / 2 | 20 / 2 |
| `schnitt_3` nach Typ (das sechzehnte) | 114 | 114 |

Alle sechzehn **gezaehlt und gleich**. Die Typaufzaehlung geht auf: 19 `reihe`,
9 `widerspruch`, 23 `reihe.umrechnung`, 20 `reihe.lizenzbeleg`, 39 `reihe.deckung`,
2 `reihe.konkordanz`, 2 `reihe.bruch` = 114, also kein achter Typ.

**`schnitt_1` zusaetzlich ueber die Trefferkontexte:** alle sechs Zeilen alt gegen neu
zeichengleich, Ergebnis `True`. Die sechs stehen im Skriptlauf ausgeschrieben. Eine gleiche
Zahl aus anderen Stellen waere sonst unbemerkt geblieben.

**Kommentare:** Der Eingriff aendert zwei Zeilen und fuegt keine ein — die Zahl der
Zeilenumbrueche ist in beiden Fassungen 1763. Beide geaenderten Zeilen sind die Wertzeilen
der zwei genannten Felder. Kein Kommentar ist beruehrt.

## Bedingung 4 — Reihe 20 kommt weiter nicht vor

Das von Bedingung 4 gezaehlte Wort steht in beiden Fassungen **null mal**; im Skript und in
diesem Befund steht es aus demselben Grund zusammengesetzt statt ausgeschrieben. Die Liste
`reihe` fuehrt vor und nach dem Eingriff 19 Eintraege, ein neuer `[[reihe]]`-Block ist
nicht entstanden.

## Der eine Verweis, den der Nachtrag neu einfuehrt

`toml_geprueft` begruendet die Streichung mit *"siehe technik.md T23 Punkt 7"*.
Aufgeschlagen statt geglaubt: `specs/0016-…/technik.md`, Zeile 1548, Punkt 7 der
Aufzaehlung: *"Normierung: die drei Sektoranteile je Gebiet und Jahr werden auf 10.000
normiert, weil die WDI-Anteile wegen der Guetersteuern abzueglich Subventionen nicht auf
100 Prozent summieren."* Die Fundstelle existiert, traegt den Satz woertlich, und sie
stuetzt genau die Aussage, fuer die sie zitiert wird: Der Teiler der Reihe 2 wechselt je
Gebiet und Jahr, der gestrichene Satz war also falsch.

## Was ich nicht gelesen habe

Das Logbuch des Datenbauers und seine Begruendung fuer die Feldaufteilung. Den Baubericht
im Arbeitspaket habe ich gelesen, weil dort der Bezugsstand steht, ohne den Bedingung 5
nicht pruefbar ist — aber jede seiner Zahlen ist oben unabhaengig neu erzeugt und keine
uebernommen.

## Was kein Befund ist, obwohl es auffaellt

- **Der Datenbauer hat in diesem Lauf keine Zeile an der Zieldatei geschrieben.** Der
  Eingriff stammt aus dem verlorengegangenen Lauf 507 desselben Pakets. Die Abnahme fragt
  nach dem Zustand der Datei, nicht nach der Urheberschaft der Schreibbewegung, und der
  Zustand ist gemessen richtig. Haette er den Eingriff zurueckgenommen und identisch neu
  geschrieben, waere dieselbe Datei mit einem zusaetzlichen Zwischenblob entstanden. Seine
  Entscheidung ist die bessere; ein Rueckgabegrund waere sie in keinem Fall.
- **Der Zaehler `Rueckläufe` im Paketrumpf steht auf `0`, obwohl zwei stattgefunden haben.**
  Das ist die Buchfuehrung des Projektmanagers, nicht Gegenstand der Abnahme. Der
  Bauagent hat es selbst gemeldet; ich wiederhole es nur, weil `RUECKLAUF_MAX` daran haengt.
- **`[datei.vorlagen]` fuehrt T53 nicht** (Vorschlag `0099`) und **`[namensnennung]` fuehrt
  Reihe 14 nicht** (Paket `0100`). Beide sind bekannt, beide warten auf dieselbe Datei und
  laufen nach der Abnahme. Kein neuer Vorschlag von mir.
- **Der Belegstellenriegel ist nicht gefahren.** Er kann sich durch diesen Eingriff nicht
  bewegt haben: Der Eingriff fuegt keine Zeile ein (1763 Zeilenumbrueche vorher wie
  nachher), verschiebt also keine gemeldete Zeilennummer, und die geloeschten 457 Zeichen
  nennen zwar Reihen beim Namen, koennen aber nur Fundstellen **entfernen**, nicht
  hinzufuegen. Das ist eine Ueberlegung und keine Messung; ich weise sie als solche aus.

## Kein Vorschlag aus diesem Lauf

Ich habe keinen geschrieben. Die drei Stellen, die einen verdient haetten, haben schon
einen (`0099`, `0100`, `0126`), und die vierte — Leseregel 3 und der faktorlose Block der
Reihe 10 — ist nach dem Wortlaut der Regel kein Fehler, sondern eine Regel, die einen Fall
nicht regelt, den sie nicht regeln muss. Ein Paket dafuer waere ein "waere auch gut".

## Urteil

`geprueft`. Der Ruecklaufgrund aus Runde 2 ist beseitigt, und zwar auf dem Weg, den der
Projektmanager gewaehlt hat: ersatzlos. Keine verbliebene Zaehlaussage des Feldes wird von
einem der 23 Bloecke widerlegt. Bedingung 4 und Bedingung 5 sind unabhaengig
nachgerechnet und halten; die Bedingungen 1 bis 3 sind durch die Blattwertbilanz als
unberuehrt belegt.
