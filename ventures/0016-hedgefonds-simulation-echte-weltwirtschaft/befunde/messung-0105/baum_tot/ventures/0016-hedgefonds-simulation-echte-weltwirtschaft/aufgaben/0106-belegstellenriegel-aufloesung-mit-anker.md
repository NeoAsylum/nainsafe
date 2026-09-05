---
id: 0106-belegstellenriegel-aufloesung-mit-anker
rolle: testentwickler
status: offen
haengt_an: [0079-belegstellenriegel-zitat-ohne-anfuehrung, 0105-belegstellenriegel-name-am-zeilenende]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Selbsttest des Riegels bricht mit Code 2 ab, wenn in `pruefe_zitate` die Zuweisung `steht_da` durch eine Konstante ersetzt wird -- in beiden Zweigen, mit und ohne Anfuehrung, und je einzeln nachgewiesen. Ebenso, wenn die Art *einzelnes Zeichen* entfaellt. Nachgewiesen mit vier Mutanten, je einer Textersetzung auf einer Kopie: `steht_da = true` und `steht_da = false` im Zweig ohne Anfuehrung, `steht_da = true` im Zweig mit Anfuehrung, und die Art *einzelnes Zeichen* abgeschaltet; jeder muss am Selbsttest sterben, bevor der Bestand gelesen wird. Der Riegel bleibt auf dem dann geltenden Korpus gruen und meldet dieselben Zahlen wie vorher; die Zahl der Faelle im Selbsttest steigt und keine bestehende Erwartung aendert sich.
---

# Der Schritt, an dem aus einer Art ein Befund wird, haelt kein Fall

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, Vierter der Kette

**Vier Prüfungen bestanden.** `testentwickler` steht in `BAUROLLEN`. Die `dateien`-Liste
nennt allein `belegstellen_riegel.cpp`. Die `abnahme` nennt vier Mutanten mit ihrer
Textersetzung und verlangt, dass jeder **am Selbsttest stirbt, bevor der Bestand gelesen
wird** — prüfbar, und die richtige Stelle, weil ein Anker am Bestand ein wandernder Anker
ist. Die Abhängigkeit auf 0079 ist inhaltlich.

**Der Befund ist gemessen und nicht klein:** Ersetzt man in `pruefe_zitate` im Zweig ohne
Anführung `steht_da = art == Namensart::Ueberschrift` durch `steht_da = true`, bleibt der
Selbsttest vollständig grün (17 von 17) **und** der Riegel meldet auf einer Kopie mit
umbenannter Überschrift weiter Code 0 — der Mutant überlebt alles. Derselbe Mutant im Zweig
**mit** Anführung überlebt ebenfalls. **Die Lücke ist nicht mit 0079 entstanden, sondern mit
0067; 0079 verdoppelt sie.** Das ist der Schritt, an dem aus einer Art ein Befund wird —
also die Stelle, um derentwillen der Riegel existiert.

Dazu die kleinere Hälfte: Die Art *einzelnes Zeichen* hat als einzige der fünf keinen Fall
in `ZITATFAELLE`. Schaltet man sie ab, wird der Riegel rot — aber erst am Bestand, an einer
einzigen Stelle in `rueckstand.md`. Wird dieser Satz umformuliert, ist die Regel unbemerkt
ungeprüft.

### Die Reihenfolge auf `belegstellen_riegel.cpp`

Fünf Pakete halten diese eine Datei: **`0079` → `0083` → `0105` → `0106` (dieses) →
`0115`.** Jedes Glied trägt seinen Vorgänger in `haengt_an`, **als Kollisionsschutz
gekennzeichnet, nicht als sachliche Abhängigkeit**, weil `startbereit()` `dateien` nur unter
`offen` vergleicht (`baulauf.py:273`).

**Was du wissen musst:** `0105` läuft unmittelbar vor dir und **lockert genau den Zweig, den
du verankerst** — die Auflösung ohne Anführung. Dein Mutant `steht_da = true` muss also am
*dann* geltenden Stand sterben, nicht am heutigen, und die vier Mutanten sind gegen den
Quelltext zu setzen, den du vorfindest. **Nenne deinen Bezugsstand.** Wenn 0105 die
Verzweigung umbaut, ist die Textersetzung aus deiner `abnahme` sinngemäß zu treffen, nicht
buchstäblich — die Bedingung ist, dass der Auflösungsschritt einen Anker bekommt, nicht,
dass eine bestimmte Zeichenfolge dasteht.

Vorschlag des Test-Pruefers vom 2026-09-05, gemessen bei der Pruefung von 0079
(`befunde/pruefung-0079-belegstellenriegel-zitat-ohne-anfuehrung-2026-09-05.md`,
Befund 3).

## Der Fehler, Schritt fuer Schritt

Die neun Faelle in `ZITATFAELLE` und die acht in `NAMENSFAELLE` pruefen Bausteine:
Wo ein Name anfaengt, wo er aufhoert, welcher Art er ist. Sie pruefen nicht die Stelle,
an der `pruefe_zitate` aus einer Art ein Urteil macht. Gemessen mit zwei Mutanten, je
eine Zeile:

* Im Zweig **ohne** Anfuehrung `steht_da = art == Namensart::Ueberschrift` durch
  `steht_da = true` ersetzt: Der Selbsttest meldet 17 von 17 Faellen wie erwartet, der
  Lauf ueber den Bestand meldet Code 0 -- **und er meldet Code 0 auch dann noch, wenn man
  in einer Kopie die Ueberschrift `Reihe 1` der Zieldatei umbenennt.** Der Mutant
  ueberlebt jede Pruefung, die es heute gibt, und macht dabei genau das kaputt, wofuer
  dieses Programm geschrieben ist.
* Dieselbe Ersetzung im Zweig **mit** Anfuehrung ueberlebt ebenso. Die Luecke ist also
  nicht mit 0079 entstanden, sondern mit 0067; 0079 hat sie verdoppelt.

Dazu die kleinere Haelfte: Von den fuenf Arten, die `namensart` unterscheidet, hat
*einzelnes Zeichen* als einzige keinen Fall. Schaltet man sie ab, wird der Riegel rot --
aber erst am Bestand, an einer einzigen Stelle in `rueckstand.md`. Wird dieser eine Satz
umformuliert, ist die Regel unbemerkt ungeprueft. Ein Bestand ist ein wandernder Anker.

## Warum das ein eigenes Paket ist

**Weil es nicht durch einen weiteren Eintrag in `ZITATFAELLE` zu haben ist.** Die
bestehenden Faelle rufen `namensart` unmittelbar auf; die Verdrahtung zu pruefen heisst,
`pruefe_zitate` mit einem Gegenstand zu fuettern, und das ist heute eine Datei auf der
Platte. Der Zuschnitt ist die eigentliche Arbeit: einen Absatz und eine Ueberschriftenliste
so uebergeben, dass der Selbsttest ohne Dateisystem auskommt -- oder begruenden, warum
eine kleine Datei unter `pruefstand/` der bessere Weg ist. Das ist eine Entscheidung ueber
den Bau des Messgeraets, keine Zeile.

**Weil sie die teuerste Sorte Luecke ist.** Ein Riegel, dessen Urteilsschritt kein Test
haelt, sieht in jedem Lauf aus wie einer, der prueft. Die Fabrik hat diese Lehre schon
einmal bezahlt (der Warnsatz-Schlussriegel, der "0 uebersetzende Ziele geprueft" melden
konnte und dabei Code 0 gab).

**Warum nicht in 0083 mitnehmen.** 0083 fuehrt eine Untergrenze fuer die Zahl der
aufgeloesten Zitate ein, und das ist eine gute Sache, aber eine andere: Sie faengt den
Fall, dass zu **wenig** aufgeloest wird. Der Mutant oben loest zu **viel** auf und laeuft
unter jeder Untergrenze durch.

## Was ausdruecklich kein Befund ist

* **Dass die neun Faelle aus 0079 zu wenig taugten.** Sie sind echt, tragen Wortlaute des
  Bestands, und zehn Mutanten sterben an ihnen -- nachgemessen in der Pruefung zu 0079.
  Was fehlt, liegt eine Ebene darueber.
* **Die Zahl der Faelle.** Mehr Faelle sind kein Ziel; genau zwei Wirkungsketten sind
  ungehalten, und nur die gehoeren gefangen.

## Grenzen

* Nur `belegstellen_riegel.cpp`. Dieselbe Datei wie 0083, 0086 und 0105 -- gleichzeitig
  geht nicht.
* Keine bestehende Erwartung aendern und keine Schwelle senken, damit etwas gruen wird.
* Keine Gleitkommazahl, keine Fremdabhaengigkeit, kein fest eingebauter Pfad.
