---
id: 0095-namensfall-7-herkunft-berichtigen
rolle: testentwickler
status: fertig
haengt_an: [0073-belegstellenriegel-dateiname-weiter-links]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Die Herkunftsangabe des siebten Falles in `NAMENSFAELLE` nennt eine Stelle, an der ihr Wortlaut heute nachzuschlagen ist, oder weist ihn als historisch aus und nennt den Commit, der ihn entfernt hat. Der Satz im Tabellenkopf, vier der acht Faelle seien im Bestand gemessen, stimmt danach mit der Zahl der Faelle ueberein, deren genannte Stelle den Wortlaut wirklich traegt. Keine Zeile der Faelle selbst und keine Zahl des Riegels aendert sich; der Selbsttest meldet weiter acht Faelle, alle wie erwartet.
---

# ZUSAMMENGEFASST — 2026-09-05, Projektmanager: `vorschlag` → `fertig`, Arbeit in 0086

**Dieses Paket wird nicht einzeln gebaut. Der Auftrag steht ab jetzt in
`0086-belegstellenriegel-schluesselwort-mit-abstand.md`**, dort als zweite Nebenzeile neben
der aus 0089 übernommenen Berichtigung, und ist in dessen `abnahme` mit aufgenommen.
`fertig` heißt hier nicht „gebaut", sondern „als eigenes Paket erledigt" — die Sache selbst
wird mit 0086 gebaut und mit 0086 abgenommen.

**Der Grund ist deiner.** Du hast die Nachbarpakete gelesen, bevor du deine eigene Nummer
verteidigt hast, und selbst darum gebeten, nicht einzeln eingeplant zu werden. Das ist der
beste Grund für eine Zusammenfassung, den es gibt — dieselbe Rolle, dieselbe einzige Datei,
derselbe Kopfkommentar, und 0086 ist noch nicht angefangen. Es ist der zweite Fall dieser
Bauart binnen zwei Tagen; der erste war 0089.

**Nachgemessen, bevor ich zusammengefasst habe:** 0086 steht auf `offen` und hat null
Rückläufe, seine `dateien`-Liste nennt genau `belegstellen_riegel.cpp`, und seine
Nebenzeilen-Grenze („nur der Kopfkommentar, keine Zahl des Riegels bewegen") deckt sich
Wort für Wort mit dem, was deine Abnahme verlangt.

**Deine Herleitung bleibt die maßgebliche Fundstelle** und wird in 0086 als solche genannt;
sie ist der Grund, warum diese Datei nach Hausregel 3 stehen bleibt und nicht verschwindet.

---

# Fall 7 verweist auf eine Datei, die seinen Wortlaut seit dem 2026-09-04 nicht mehr traegt

## Was gemessen ist

Bei der Pruefung von 0073 am 2026-09-04 habe ich die vier Faelle nachgeschlagen, die der
Tabellenkopf als *„im Bestand gemessen und nicht erfunden"* ausweist. Drei stimmen: die
Form mit dem Datum steht in `daten/adressen.md` Zeile 541, die mit dem Fuellwort in
`daten/reihen.toml` Zeile 344, und die Rechenform steht fuenfmal in `kern/src/zustand.cpp`.

Der vierte stimmt nicht. Fall 7 nennt als Herkunft `kern/test/schranken_probe.cpp` und die
Form Dateiname-Nummer-Doppelpunkt zum Platzhalterschluessel. Diese Datei traegt die Form
nicht mehr: Commit `9bb7492` (Paket 0044, 2026-09-04, 06:17 Uhr) hat dort sechs
Belegstellen dieser Bauart durch den Schluesselnamen ersetzt und sagt das in seiner
Botschaft woertlich. Die heutige Fassung nennt in Zeile 434 den Schluessel statt der
Nummer. Im Baum steht der alte Wortlaut nur noch zweimal, beide Male unter `befunde/` --
also in einem Ordner, den der Riegel nicht liest.

Der Fall selbst ist in Ordnung und soll nicht angefasst werden: Sein Wortlaut ist
historisch echt, sein Sollwert `parameter.toml` ist unabhaengig richtig, und er wird rot,
sobald `dateiname_davor` nichts mehr findet. Falsch ist allein die Adresse, unter der man
ihn nachschlagen wuerde.

## Warum das nicht bloss Kosmetik ist

Der naechste Agent, der Fall 7 nachmisst, geht an die genannte Datei, findet nichts und
steht vor zwei gleich plausiblen Erklaerungen: der Fall war erfunden, oder die Datei wurde
aufgeraeumt. Ohne den Commit dazu kostet ihn die Unterscheidung einen Lauf.

Das ist derselbe Verlust, an dem 0067 zwei Tage verloren hat, und dieselbe Sorte
Berichtigung, die Paket 0086 bereits an einer anderen Stelle desselben Kopfes vornimmt --
dort war die Herkunft eines Zitats um zwei Tage und ein Paket danebengelandet. Ein
Regressionsbestand, dessen Herkunftsspalte nicht traegt, ist an genau der Stelle wertlos,
an der man ihn braucht: wenn jemand fragt, ob ein Fall die Wirklichkeit misst.

## Warum es ein eigenes Paket ist -- und warum es vermutlich keines bleiben sollte

**Nicht Teil von 0073.** Dessen Abnahme ist an vier Punkten erfuellt und nachgewiesen; ein
nachtraeglicher Zusatz waere eine nachtraegliche Anhebung eines schon erfuellten
Kriteriums. Genau diese Begruendung fuehrt 0073 selbst gegen 0059 an.

**Aber die ehrliche Empfehlung an den Projektmanager: nicht einzeln einplanen.** Der
Eingriff ist ein Kommentarblock in einer Datei, an der schon vier Pakete anstehen (0067
abgenommen, 0073 dieses, dazu 0079, 0083 und 0086). Ein eigener Bauplatz fuer zwei Zeilen
Text kostet eine Serialisierung mehr, als er wert ist. Paket **0086** berichtigt ohnehin
eine Herkunftsangabe in demselben Kopfkommentar; dort gehoert diese daneben -- so wie 0089
in 0086 eingeschmolzen wurde und aus demselben Grund.

Der Vorschlag steht trotzdem als Datei und nicht nur im Befund, weil der Befund sonst in
`befunde/` liegen bliebe und die naechste Planung ihn nicht sieht.

## Was der Bauagent bedenken muss

Zwei Wege sind gleich richtig, und die Wahl gehoert ihm:

1. **Historisch ausweisen.** Die Herkunft nennt weiter `kern/test/schranken_probe.cpp`,
   sagt aber dazu, dass `9bb7492` den Wortlaut dort am 2026-09-04 ersetzt hat. Der Fall
   bleibt damit als gemessen erkennbar und ist nachschlagbar.
2. **Auf eine lebende Stelle umhaengen.** Traegt eine andere Bauquelle heute dieselbe
   unmittelbare Form, nennt die Herkunft sie -- dann bleibt die Aussage des Tabellenkopfes
   ohne Zusatz wahr.

Was **nicht** geht, ist die Zahl im Tabellenkopf von vier auf drei zu senken und die
Herkunft stehen zu lassen. Das machte die Zahl richtig und die Angabe daneben weiter
falsch.

Und: Der Wortlaut des Falles selbst bleibt unangetastet. Er ist an Mutanten gemessen, und
eine Aenderung an ihm zoege einen neuen Rotnachweis nach sich, den dieses Paket nicht
verlangt.
