---
id: 0137-riegelmeldung-nennt-ihr-profil
rolle: kernbauer
status: vorschlag
haengt_an: [0132-riegelmeldung-nennt-gesammelte-eintraege]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Die Meldung, ueber der die Profilregel jetzt steht, nennt ihr Profil nicht

## Herkunft

Aus der Pruefung von Paket 0104 (2026-09-05, Rolle `kern-pruefer`), Befund 1. Nachweis
und alle Zahlen in `befunde/pruefung-0104-zielzahlen-je-profil-statt-tripel-2026-09-05.md`.

## Der Befund

Paket 0104 hat in `werkzeugkette.cmake` die Regel niedergelegt, nach der kuenftige
Abnahmen die Zahl der konfigurierten Ziele benutzen duerfen: nur als Vergleich gegen den
unmittelbar vorhergehenden Stand desselben Baums **und desselben Profils**. Der Kommentar
begruendet das damit, dass eine Zahl ohne ihr Profil keine Messung sei, sondern eine
Behauptung. Das ist richtig und gemessen.

**Die Zeile unmittelbar darunter gibt genau eine solche Zahl aus und nennt ihr Profil
nicht.** Die Meldung des Warnsatz-Schlussriegels sagt, wie viele uebersetzende Ziele
geprueft wurden, und sagt nirgends, unter welchem Wert von `FABRIK_SANITIZER`.

So erzeugt man den Fehler -- drei Schritte, gemessen am 2026-09-05:

1. Den Alleinbau des Pruefstands mit `-DFABRIK_SANITIZER=ON` konfigurieren.
2. Denselben Baum mit `-DFABRIK_SANITIZER=OFF` in einen zweiten, leeren Baubaum
   konfigurieren.
3. Die beiden Konfigurationsausgaben nebeneinanderlegen.

Sie sind **zeichengleich bis auf eine einzige Ziffer** -- die Zahl der uebersetzenden
Ziele, die sich um eins unterscheidet, weil `pruefstand_geprueft` nur im einen Profil
entsteht. Kein Wort in beiden Ausgaben nennt `FABRIK_SANITIZER`, keines nennt
`pruefstand_geprueft`.

**Warum das mehr ist als eine fehlende Beschriftung.** Auf diesem Bauweg ist das
Gleichheitsmass aus der Ausgabe allein nicht anwendbar: Ein gewechseltes Profil und ein
verlorengegangenes Ziel sehen im Bericht identisch aus. Der Vorgabewert des Schalters
steht in derselben Datei und laesst sich mit einer Zeile umlegen; danach faellt die Zahl,
und der naechste Leser sucht das Ziel, das ihm angeblich abhandengekommen ist -- oder,
schlimmer, findet die Erklaerung und gewoehnt sich daran, den Abfall wegzuerklaeren.

**Die beiden anderen Bauwege kommen heute mit einem Zufall davon.** Im Arbeitsbereich und
im Alleinbau des Kerns zaehlt der Nullabhaengigkeitsriegel `kern_geprueft` in seiner
eigenen Meldung mit auf; daran ist das Profil abzulesen. Diese Zeile ist aber nicht dafuer
da, und sie fehlt genau dort, wo kein Kern im Baum liegt. Der Alleinbau des Pruefstands ist
keiner von drei gleich wichtigen Wegen, sondern einer, den jede Abnahme dieses Riegels
fuehrt.

**Und der echte Bericht sieht schon so aus.** In der Uebersetzung vom 2026-09-05 stehen
sechs Meldungen dieses Riegels; keine einzige nennt ihr Profil. Die Ueberschrift, unter der
sie steht, ist auf die ersten beiden Worte des Aufrufs gekuerzt -- die Schalter stehen dort
also auch nicht. Der Bericht ist der Ort, an dem eine kuenftige Abnahme die Zahl liest.

## Warum ein eigenes Paket und nicht Teil von 0132

0132 laesst dieselbe Meldung eine **zweite Zahl** tragen, damit ein stumpf gewordener
Riegel von einem scharfen zu unterscheiden ist. Das ist eine andere Frage mit einer
anderen Quelle: Jene Zahl kommt aus dem Zaehlwerk von `fabrik_riegel_sammeln`, dieses
Merkmal aus dem Schalter `FABRIK_SANITIZER`. Beide Bedingungen von 0132 blieben auch dann
unerfuellt, wenn das Profil dastuende, und umgekehrt.

Der zweite Grund ist Verfahren, nicht Sache: 0132 steht bereits auf `offen`. Seine Abnahme
ist angenommen, und ein Prueferbefund, der ihr nachtraeglich eine dritte Bedingung
anhaengt, verschiebt die Abnahmegrenze eines laufenden Pakets. Das ist genau die Bauart,
gegen die sich 0104 entschieden hat.

**Was beide teilen, ist die Datei, und darum haengt dieses Paket an 0132** -- als
Kollisionsschutz und nicht als sachliche Abhaengigkeit. Die Kette auf `werkzeugkette.cmake`
lautet heute 0094 → 0103 → 0104 → 0108 → 0124 → 0132; dieses Paket gehoert ans Ende.
Haelt der Projektmanager es trotzdem fuer richtig, beides in einem Zug zu bauen, ist das
seine Entscheidung -- dann aber vor dem Baubeginn von 0132 und nicht danach.

## Was zu tun ist

Die Meldung traegt kuenftig, aus welchem Profil ihre Zahl stammt. Der Weg ist frei
waehlbar, solange das Ergebnis aus der Ausgabe **allein** lesbar ist und auf allen drei
Bauwegen erscheint, auch dort, wo kein Kern im Baum liegt.

**Was nicht dazugehoert:** die Zahl selbst oder ihre Zaehlweise anfassen; die zweite Zahl
aus 0132 vorwegnehmen; den Vorgabewert des Schalters aendern; die Zahl der Ziele in einer
Abnahme ausschreiben.

## Abnahme

1. **Das Profil ist aus der Konfigurationsausgabe allein erkennbar, auf jedem der drei
   Bauwege.** Nachweis: Arbeitsbereich, Kern allein und Pruefstand allein, je in beiden
   Profilen, in sechs getrennten und leeren Baubaeumen konfiguriert; die sechs Ausgaben
   paarweise je Bauweg gegenuebergestellt und abgedruckt. Jedes Paar unterscheidet sich in
   einer Zeile, die den Schalter und seinen Wert nennt -- **auch das Paar des Alleinbaus
   des Pruefstands**, das sich heute in nichts als einer Ziffer unterscheidet. Zweiseitig:
   Die neue Zeile sagt im einen Lauf etwas anderes als im anderen; eine Zeile, die immer
   dasselbe meldet, hat den Fehler nur verdeckt.
2. **Kein Urteil aendert sich.** Dieselben sechs Konfigurationen mit Code 0, dazu Bau und
   `ctest` in beiden Profilen mit Code 0. Die Zahl der uebersetzenden Ziele wird je Profil
   **gegen den eigenen Stand davor** verglichen -- gleicher Baum, gleicher Schalter, einmal
   mit und einmal ohne die Aenderung -- und nicht gegen einen ausgeschriebenen Sollwert;
   die Begruendung dafuer steht in 0104. Der Bezugsstand wird genannt. Die Meldungen der
   uebrigen Riegel bleiben im Wortlaut unveraendert.
