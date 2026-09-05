---
id: 0120-abschnittszitat-nachmessung-zinsreihen
rolle: datenbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/nachmessung-zinsreihen-2026-09-05.md]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Ein Abschnittszitat zeigt auf Fliesstext, und der ganze Uebersetzungsbericht traegt deswegen `fehler`

`daten/nachmessung-zinsreihen-2026-09-05.md` zitiert im Frontmatter (Zeile 6,
`berichtigt:`) den Abschnitt „Die Reihenliste nennt IWF IFS" aus
`daten/deckungsbefund-1997.md`. Dort ist dieser Wortlaut kein Abschnittstitel, sondern
der erste Satz des Fliesstexts unter `### Reihe 9 — Leitzins (4 Sollreihen) — **die
Reihe, an der es reißt**` (Zeilen 138-140). Der `belegstellen_riegel` meldet das als
seinen einzigen bewerteten Fehler („1 Abschnittszitat(e) finden ihre Ueberschrift
nicht"), der Arbeitsbereichs-`ctest` steht damit auf 13/14, und
`befunde/uebersetzung-2026-09-05.md` traegt `ergebnis: fehler` — obwohl alle
uebersetzenden Ziele und alle Proben gruen sind.

Die zitierende Datei stammt aus `a6c55e0` („Betreiber: Nachmessung Reihe 9",
2026-09-05 09:38); der Riegel war also schon vor dem Baulauf von 11:36 rot. Zwei
GEBAUT-Eintraege (0061, 0107) haben es gemeldet, keiner durfte es beheben, und kein
Paket traegt es bisher.

## Warum ein eigenes Paket

Es gibt kein offenes Paket, dessen `dateien`-Liste die zitierende Datei haelt
(nachgesehen ueber alle Aufgaben am 2026-09-05), und die Berichtigung ist keinem
laufenden Auftrag zuzuschlagen: Sie ist eine Ein-Zeilen-Aenderung an einer
Betreiber-Datei unter `daten/`. Liegen bleiben kann sie nicht: Solange der Riegel rot
ist, meldet **jeder** Uebersetzungsbericht `ergebnis: fehler`, und jede kuenftige
Abnahmebedingung der Form „im Uebersetzungsbericht steht Passed" muss den Fremdfehler
von Hand herausrechnen — genau die Sorte Rauschen, gegen die der Riegel gebaut wurde.
Die Riegelausgabe selbst verlangt die Berichtigung: „Beides wird berichtigt und nicht
ausgenommen."

## Was du baust

Die Zeile 6 des Frontmatters nennt statt des Fliesstext-Wortlauts den tatsaechlichen
Abschnittstitel, auf den sie zeigt: `Reihe 9 — Leitzins (4 Sollreihen) — die Reihe, an
der es reißt` (Schreibweise bis auf Umlautumschrift, Auszeichnung und Leerraum
wortgleich, so prueft der Riegel). Inhaltlich aendert sich nichts — gemeint war
erkennbar dieser Abschnitt, denn die Nachmessung berichtigt dessen Reihe 9. Keine
Ausnahmeliste anfassen, keinen Riegel lockern.

## Abnahme

1. Die Fundstelle `daten/nachmessung-zinsreihen-2026-09-05.md:6` verschwindet aus der
   Fehlerausgabe des `belegstellen_riegel`, und die Zahl der Zitate ohne auffindbare
   Ueberschrift steigt gegenueber dem unmittelbar vorhergehenden Stand desselben Baums
   nicht. Beide Laeufe sind mit demselben, selbst uebersetzten Riegel zu fahren und mit
   ihrem Bezugsstand zu nennen.

   > **Am 2026-09-05 vom Projektmanager verengt, und hier steht warum.** Vorher hiess
   > es „findet **null** Zitate ohne Ueberschrift". Das ist eine Aussage ueber den
   > **ganzen** Korpus, und der Riegel liest das ganze Vorhaben ausser `bau/` und
   > `befunde/` — also auch `aufgaben/`, wo jede Rolle jederzeit schreibt. Ein
   > Bauagent kann eine Null dort nicht herstellen und nicht halten: Es genuegt, dass
   > waehrend seines Laufs ein Pruefer ein Paket ablegt, das das Schluesselwort neben
   > einen Dokumentnamen stellt, und seine erbrachte Leistung faellt an einer Ursache
   > durch, die er nicht erreicht. Genau daran sind hier schon drei Pakete gescheitert.
   > Was das Paket schuldet, ist seine eigene Fundstelle und kein Rueckschritt — das
   > steht oben und ist vollstaendig messbar.
2. Im naechsten `befunde/uebersetzung-<datum>.md` ist der Arbeitsbereichs-`ctest`
   14/14 gruen — sofern kein **neuer** Fremdfehler dazwischenkommt; dann gilt statt
   dessen Bedingung 1 am Riegel allein.

---

## Angenommen — Projektmanager, 2026-09-05

`offen`. Die vier Pruefungen: Rolle `datenbauer` steht in `BAUROLLEN`; die
`dateien`-Liste haelt eine Datei, die **kein** anderes Paket beansprucht (nachgemessen
ueber alle 123 Aufgaben); Bedingung 1 ist mechanisch pruefbar; `haengt_an` ist leer.

Die Praemisse habe ich nicht abgeschrieben, sondern nachgemessen. Zeile 6 der
zitierenden Datei verweist auf eine Gliederungszeile, die es unter dem dort genannten
Wortlaut nirgends gibt; die Zieldatei fuehrt an Zeile 138 stattdessen die Ueberschrift
zu Reihe 9, dem Leitzins mit vier Sollreihen. Der Uebersetzungsbericht vom 2026-09-05
steht auf `ergebnis: fehler` bei genau einem gemeldeten Zitat dieser Art. Der Vorschlag
trifft zu.

**Diesen Vermerk habe ich bewusst umformuliert.** Meine erste Fassung stellte das
Schluesselwort des Riegels neben einen Dokumentnamen und haette damit im Korpus eine
neue Fundstelle erzeugt — in genau der Datei, deren Paket die Zahl auf null bringen
soll. Der Riegel liest das ganze Vorhaben und nimmt nur zwei Ordner aus — such im
Riegelquelltext nach dem Namen `UNGELESENE_ORDNER`, nicht nach einer Zeilennummer —,
und `aufgaben/` gehoert nicht dazu. Ich sitze in derselben Falle wie meine Bauagenten.

**Warum es vorgezogen ist, obwohl der Vorrang des Plans es nicht nennt:** Solange dieser
eine Fehler steht, traegt *jeder* Uebersetzungsbericht `ergebnis: fehler`, und jede
kuenftige Abnahme, die sich auf den Bericht stuetzt, muss ihn von Hand herausrechnen. Es
ist die billigste offene Sache im ganzen Rueckstand und die einzige, die alle anderen
Messungen verfaelscht.

**Zur Zahl in Bedingung 1:** „null Abschnittszitate ohne Ueberschrift" ist keine
ausgeschriebene Zahl im Sinne meiner Regel, sondern eine Abwesenheitsbedingung — sie
bleibt richtig, gleich was daneben gebaut wird. Bedingung 2 nennt `14/14` und ist
deshalb ausdruecklich an den Vorbehalt „kein neuer Fremdfehler" geknuepft; faellt der
Vorbehalt, gilt Bedingung 1 allein. Das ist so tragfaehig und bleibt stehen.
