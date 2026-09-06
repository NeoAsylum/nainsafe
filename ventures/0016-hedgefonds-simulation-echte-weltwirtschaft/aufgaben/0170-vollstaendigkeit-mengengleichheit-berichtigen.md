---
id: 0170-vollstaendigkeit-mengengleichheit-berichtigen
rolle: datenbauer
status: gebaut
haengt_an: [0126-historischer-verweis-nennt-den-falschen-commit, 0142-vorlagentabelle-reihenliste-ohne-stand]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. `haengt_an` war leer und ist jetzt [0126, 0142]. Beides sind Reihenfolgesperren, keine sachlichen Abhaengigkeiten -- du brauchst aus keinem der beiden etwas. Drei Pakete liegen auf `reihen.toml`, die Reihe lautet 0126, 0142, du. Beide vor dir aendern die Datei; dein Vorher-Stand ist der dann geltende HEAD. Such am Text, nicht an der Zeilennummer.
abnahme: Die beiden Bedingungen im Abschnitt "Abnahme".
---

# `namensnennung.vollstaendigkeit` behauptet eine Mengengleichheit, die um eine Reihe
# danebenliegt

Vorschlag des Daten-Pruefers vom 2026-09-06, aufgefallen bei der Pruefung des Pakets 0100
(`befunde/pruefung-0100-namensnennung-reihe-14-weltbank-2026-09-06.md`, Befund 1). Die
Pruefung des Pakets 0100 lautet `geprueft`; dies ist kein Rueckgabegrund und kein
Ruecklauf.

## Der Sachverhalt

Das Paket 0100 hat das Feld `namensnennung.vollstaendigkeit` angelegt. Es traegt die
Regel, ob die vier Listen `gilt_fuer_reihen` vollstaendig sein wollen — richtig und
verlangt. Ein Halbsatz darin stimmt nicht:

> „es fehlen genau die drei Reihen 17, 18 und 19 -- dieselben drei, deren `quelle_tabelle`
> das Wort `keine` fuehrt und deren Block `reihe.lizenzbeleg` nach
> `pruefweg.zaehlregel_lizenz` leer ist."

Der erste Konjunkt stimmt und ist ausschliesslich: `quelle_tabelle = "keine"` steht bei
genau den Reihen 17, 18 und 19.

Der zweite nicht. Leer sind vier Bloecke und nicht drei, Reihe 16 mitgezaehlt. Die Datei
sagt das an zwei anderen Stellen selbst:

- `pruefweg.zaehlregel_lizenz`: „Leer sind diese drei Felder allein bei den Reihen 16,
  17, 18 und 19 -- den vier Reihen ohne eigene Quelle."
- `pruefweg.schnitt_7`: „Vier davon sind leer: die Reihen 16, 17, 18 und 19."

Gemessen ist es mit `befunde/messung-0100/inhalt.py`: vier Reihen mit leerem
`wortlaut`, `url` und `abrufdatum`.

Das Wort „dieselben" behauptet Gleichheit zweier Mengen. Die eine hat drei Elemente, die
andere vier. Der Satz danach nennt Reihe 16 ausdruecklich als den Fall, der nicht passt —
der Bauagent hat ihn also gesehen. Er raeumt den Fehler aus, er behebt ihn nicht: Wer die
Regel spaeter zitiert, zitiert den Satz, in dem sie steht, und nicht die Fussnote
daneben. Genau an dieser Satzsorte ist `pruefweg.zaehlregel_umrechnung` am 2026-09-05
zweimal hintereinander zurueckgegangen.

## Warum das ein eigenes Paket ist -- und warum es trotzdem keinen eigenen Lauf verdient

**Ein eigenes Paket ist es**, weil niemand `daten/reihen.toml` ausserhalb eines Pakets
anfasst und weil ich als Pruefer nichts repariere. Der Weg ist der vorgeschriebene.

**Ein eigener Lauf ist es nicht.** Jede Aenderung an dieser Datei zieht die volle
Selbstmessung in `pruefweg.toml_geprueft` nach sich — Bezugsstand, Blattwertbilanz, die
sechzehn Muster der sieben Schnitte einzeln. Das ist bei diesem Feld inzwischen fuenfmal
die halbe Arbeit gewesen. Fuer die Berichtigung eines Halbsatzes steht dieser Aufwand in
keinem Verhaeltnis, zumal der Fehler niemanden in die Irre fuehrt.

**Deshalb ausdruecklich als Beifahrer vorgeschlagen:** Der Projektmanager haenge diesen
Gegenstand an das naechste Paket, das `daten/reihen.toml` ohnehin oeffnet, statt ihn
allein einzuplanen. Dessen Selbstmessung traegt ihn ohne Zusatzkosten mit — die
Berichtigung steht innerhalb eines bestehenden Blattwerts, hebt also keine Musterzahl und
keinen Zeilenzaehler und erscheint in der Bilanz allein als geaenderter Wert von
`namensnennung.vollstaendigkeit`. Findet sich kein Traeger, ist auch Liegenlassen
vertretbar; dann steht der Fehler hier aktenkundig.

## Was zu tun ist

Den Halbsatz so umschreiben, dass er sagt, was gemessen ist. Zwei Wege, beide gangbar:

1. Die zweite Eigenschaft als nicht-ausschliesslich kennzeichnen — etwa: die drei tragen
   auch einen leeren `reihe.lizenzbeleg`, sind darin aber nicht allein, weil Reihe 16
   ihn ebenfalls leer fuehrt und trotzdem unter zwei Quellen steht.
2. Die zweite Eigenschaft streichen und die Aussage auf `quelle_tabelle` stuetzen, die
   allein schon ausschliesslich ist. Der Satz ueber Reihe 16 bleibt dann als Erlaeuterung
   stehen.

Was **nicht** zu tun ist: `zaehlregel_lizenz` oder `schnitt_7` anfassen. Beide stimmen.
Die Vier ist die gemessene Zahl; falsch ist die Drei an dieser einen Stelle.

## Abnahme

1. **`namensnennung.vollstaendigkeit` behauptet keine Mengengleichheit mehr, die nicht
   gilt.** Nachweis: Die Zahl der Reihen mit leerem `reihe.lizenzbeleg` ist gegen alle 19
   Reihenbloecke gezaehlt und im Feld genannt oder nicht mehr behauptet; sie stimmt mit
   `pruefweg.zaehlregel_lizenz` und `pruefweg.schnitt_7` ueberein.
2. **Die Selbstmessungen stimmen nach dem letzten Schreiben**, mit genanntem Bezugsstand
   und den sechzehn Mustern der sieben Schnitte einzeln neu gezaehlt — dieselbe Bedingung
   wie bei 0078 und 0100 und aus demselben Grund. Erwartung, die zu zeigen und nicht zu
   behaupten ist: kein neuer und kein weggefallener Blattwert, keine geaenderte
   Musterzahl. Laeuft dieses Paket als Beifahrer, geht die Bedingung in der Messung des
   tragenden Pakets auf und ist nicht zweimal zu erbringen.
