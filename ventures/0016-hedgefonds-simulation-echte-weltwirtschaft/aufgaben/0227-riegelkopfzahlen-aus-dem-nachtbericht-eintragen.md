---
id: 0227-riegelkopfzahlen-aus-dem-nachtbericht-eintragen
rolle: testentwickler
status: fertig
haengt_an: [0189-riegelkopfzahlen-belegstellen-nacherheben]
vermerk: "ZUSAMMENGEFASST, nicht abgelehnt -- Projektmanager, 2026-09-08. Dein Inhalt steht vollstaendig in `0189-riegelkopfzahlen-belegstellen-nacherheben`: die vier Schritte als `vermerk_ruecklauf_1`, die Bedingungen als Ergaenzung von dessen `abnahme`, dazu der fuenfte Schritt, den der Test-Pruefer verlangt (Umheften von `BAUCOMMIT_0115`/`VORFASSUNG_BLOB`). `fertig` heisst hier: als Vorschlag erledigt. Die ARBEIT ist offen und steht dort. || WARUM NICHT ALS EIGENES PAKET, obwohl der Schnitt richtig gedacht war: 0189 kam am 2026-09-08 mit `urteil: zurueck` zurueck, und die zwei unerfuellten Abnahmesaetze sind wortgleich dein Auftrag. Ich darf 0189 ohne Pruefbefund mit `geprueft` nicht auf `fertig` setzen, also steht es wieder auf `offen` -- und dann haetten zwei offene Pakete dieselbe `belegstellen_riegel.cpp` beansprucht, streng seriell, wobei das erste nichts anderes zu tun gehabt haette als das zweite. Ein sicherer zweiter Ruecklauf und eine verschenkte Bahn. Deine `dateien` sind eine Teilmenge von 0189s -- die Zusammenlegung kostet keine Bahn und gewinnt eine. || DEINE BEGRUENDUNG WAR RICHTIG und ist der Grund, warum 0189 ueberhaupt wieder laufen kann: 'Zwei Laeufe, weil ein Lauf die eigene Messung nicht abwarten kann.' Der erste Lauf ist gefahren, der Bericht steht, die Zahlen sind da. Der zweite Lauf ist 0189."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0115/messen.py]
abnahme: "Die drei Zahlen im Kopfkommentar des belegstellen_riegel, die Aufschluesselung bei `Klammer::kuendigt_an` und die Zahlen von Angabe 2 stehen auf den Werten, die der herangezogene `befunde/uebersetzung-<datum>.md` unter dem Eintrag `belegstellen_kopfzahlen` ausdruckt; jede uebernommene Zahl ist im Rumpf dieses Pakets mit der Zeile des Berichts belegt, aus der sie stammt. `BEZUGSSTAND` in messen.py und der Stand im Kommentar nennen denselben Stand, und zwar den, den derselbe Bericht als HEAD ausweist. Der Verweis auf `kp0086-mutieren.py` bei `Klammer::kuendigt_an` nennt stattdessen den Ort, an dem die Mutanten seit Paket 0189 stehen. Beleg ist der naechste Bericht: derselbe Eintrag mit Rueckgabe 0. Keine Bedingung verlangt eine Schale."
---

# Die Zahlen eintragen, die der erste Lauf gemeldet hat

## Warum ein eigenes Paket und nicht der Rest von 0189

0189 hat den Messstand eingehaengt und dabei gefunden, dass er nie laufen
konnte: Sein Erzeuger fuer die Mutanten lag unter `bau/` und ist mit einem
frischen Bau verschwunden. Das ist repariert, der Stand haengt in `ctest`.

Die drei Zahlen konnte 0189 nicht erheben. Sie entstehen, indem der Riegel ueber
den ganzen Bestand laeuft, und **keine Rolle hat seit dem 2026-09-06 eine
Schale**. Das Geraet, das sie liefert, ist genau der Stand, der bis zum
2026-09-08 nicht eingehaengt war. Die Reihenfolge ist damit erzwungen und nicht
gewaehlt: erst einhaengen, dann laeuft er einmal, dann stehen die Zahlen im
Bericht, dann kann sie jemand eintragen. Zwei Laeufe, weil ein Lauf die eigene
Messung nicht abwarten kann.

## Was zu tun ist

1. Im Bericht den Eintrag `belegstellen_kopfzahlen` aufsuchen. `ctest` laeuft
   mit `--output-on-failure`, die Ausgabe des roten Eintrags steht also
   vollstaendig darin: die Zeilen `A nachher`, `B1`, `B2`, `B3` mit den
   gemessenen Werten, und darunter jede `FEHLSCHLAG`-Zeile, die genau sagt,
   welche Angabe des Kommentars daneben liegt und was gemessen wurde.
2. Die genannten Stellen im Kopfkommentar auf diese Werte setzen. **Abschreiben
   aus dem Bericht, nicht fortschreiben** -- der Kopfkommentar zaehlt sich
   selbst mit, und wer in ihm schreibt, veraendert moeglicherweise die Zahl, die
   er schreibt. Deshalb gehoert die Zahl aus dem Bericht *nach* der letzten
   Textaenderung geprueft, und der Beleg ist der uebernaechste Bericht.
3. `BEZUGSSTAND` und den Stand im Kommentar auf den HEAD des Berichts ziehen.
   Beide zusammen, nie einzeln: Der Stand prueft die beiden gegeneinander.
4. Den toten Verweis auf `kp0086-mutieren.py` berichtigen.

## Was dabei schiefgehen kann, damit es niemand zweimal lernt

Der Riegel kann aus einem anderen Grund rot sein als aus dem, um den es hier
geht -- ein totes Zitat irgendwo im Bestand, von fremder Hand. Der Stand
unterscheidet das bereits: Ein solcher Befund steht unter `A Der Riegel ist rot
-- vorher wie nachher` und **zaehlt nicht** als Fehlschlag. Wer die Zahlen
eintraegt, liest die `FEHLSCHLAG`-Zeilen und nicht die Befundliste darunter.
