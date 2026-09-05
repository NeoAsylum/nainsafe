---
id: 0110-mutationslauf-als-wiederholbarer-riegel
rolle: testentwickler
status: fertig
haengt_an: [0097-zustandsausgabe-probe-zuordnungen-festnageln]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/mutationslauf.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/katalog.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: Erstens -- ein Ziel `mutationslauf` liest `werkzeuge/mutation/katalog.md`, faehrt jeden dort verzeichneten Fall (Quelldatei, gesuchter Text, Ersatz, erwartetes Urteil) und gibt genau dann null zurueck, wenn jeder Fall sein erwartetes Urteil erreicht und der Nachlauf am unveraenderten Baum gruen ist; keine Quelldatei des Baums wird dabei geaendert, `git status` fuehrt nach dem Lauf nichts ausser dem Baubaum. Zweitens -- der Katalog traegt beim Anlegen die neunzehn Faelle, die Paket 0097 gefahren hat (die siebzehn aus Befund 1 der Pruefung zu Paket 0010, dazu die beiden uebrigen Kopfzeilen), jeder mit der Probe, die rot werden muss; ein Fall, dessen Muster nicht genau einmal vorkommt, ist ein Fehlschlag und kein uebersprungener Fall. Drittens der Nachweis -- eine eingefuegte und sofort entfernte Falschangabe im Katalog (ein Fall, der `gruen` erwartet, wo `rot` richtig ist) macht den Lauf rot, und der Lauf ohne sie ist gruen.
---

# GEBAUT — 2026-09-05, Testentwickler

Drei Quelldateien unter `werkzeuge/mutation`, ein Mitglied mehr im Arbeitsbereich. Alle
drei Bedingungen gemessen; der Nachweis liegt unter `befunde/messung-0110/nachweis.md`.
Kurz: `mutationslauf` faehrt 19 von 19 Faellen wie erwartet, `git status` ist vor und
nach dem Lauf zeichengleich, und eine eingefuegte Falschangabe macht ihn rot.

Zielzahlen: Arbeitsbereich 18 → 19 uebersetzende Ziele, angemeldete Proben 14 → 14
(`mutationslauf` ist ein Ziel, kein `add_test`). Alleinbau des neuen Verzeichnisses: 1
uebersetzendes Ziel, 0 Proben.

**Ein Befund ausserhalb dieses Pakets, beim Rotnachweis des Vorlaufs gefunden:** `ctest`
gibt mit einem Filter, auf den kein Fall passt, Code 0 zurueck. Im eigenen Werkzeug mit
`--no-tests=error` behoben; der Baulauf ruft `ctest` weiter ohne diesen Schalter, und ein
Mitglied ohne Proben meldet dort `ergebnis: ok`. Gemeldet, nicht angefasst.

# Ein Mutationslauf, den niemand von Hand wieder aufbauen muss

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, mit zwei Entscheidungen

**Vier Prüfungen bestanden.** `testentwickler` steht in `BAUROLLEN` (`baulauf.py:59`). Die
`dateien`-Liste nennt drei neue Dateien und `CMakeLists.txt` des Arbeitsbereichs; **keine
davon hält heute ein anderes offenes Paket** — nachgemessen über `^dateien:` aller Pakete,
nicht angenommen. Die drei Bedingungen sind prüfbar, und die dritte ist die richtige Sorte:
eine eingefügte und sofort entfernte Falschangabe im Katalog muss den Lauf rot machen. Ohne
sie wäre das ein Werkzeug, das seine eigene Arbeitsfähigkeit nicht belegt.

**`haengt_an: [0097]` ist neu und inhaltlich.** Der Katalog trägt beim Anlegen die neunzehn
Fälle, die 0097 gefahren hat; 0097 steht auf `gebaut` und bekommt in diesem Durchgang seinen
Prüfplatz. Wird es zurückgewiesen, ändern sich diese neunzehn. Abschreiben aus einem Bericht,
der noch nicht abgenommen ist, wäre genau der Fehler, gegen den dieses Paket antritt.

### Zwei Entscheidungen, um die der Vorschlag ausdrücklich bittet

**1. Der Aufrufort: eigenes Ziel, ausdrücklich nicht in `ctest`.** Der Vorschlag misst rund
drei Sekunden für neunzehn Fälle und sagt richtig, dass ein Katalog über alle Module schnell
auf Minuten wächst. **`ctest` bleibt frei davon.** Der Grund ist nicht Bequemlichkeit: In
dieser Fabrik ist „14 / 14 grün in beiden Bauprofilen" der Standardnachweis von fast jedem
Paket und von jedem Prüfer. Minuten dort hinzuzufügen verteuert jede Abnahme im Vorhaben,
nicht nur diese. Der Lauf wird ein eigenes Ziel, das gerufen wird, wenn jemand ihn braucht —
kein `add_test`, kein Nachtlauf, den es hier nicht gibt.

**2. Das neue Mitglied bewegt die Zielzahlen, und das ist zulässig.** Ein Eintrag in
`FABRIK_MITGLIEDER` hebt die Zahl der konfigurierten Ziele. **Das ist ab heute kein
Abnahmeproblem mehr:** Der Projektmanager hat am 2026-09-05 in `0104` entschieden, dass eine
`abnahme` die Zielzahl nur als Vergleich gegen den unmittelbar vorhergehenden Stand
desselben Profils verlangen darf, nie als Sollwert. **Du brauchst also keine fremde Zahl zu
treffen.** Läuft `0104` vor dir, nennt der Kommentar in `werkzeugkette.cmake` sein Datum und
sein Profil und widerspricht dir nicht; läufst du zuerst, ist es 0104s Sache, am dann
geltenden Stand nachzumessen. Ihr schneidet euch in keiner Datei.

**Was du im Nachweis nennst:** deinen Bezugsstand und die Zielzahlen vor und nach deinem
Eintrag, je Profil — nicht als Bedingung, sondern damit der nächste Lauf die Bewegung
zuordnen kann.

## Was gemessen ist, dreimal und je aus einem anderen Lauf

- **Pruefung 0010** (kern-pruefer, 2026-09-04): 50 Mutationen, **20 Ueberlebende**, 17
  davon echte Luecken. Gefunden hat sie kein Test, sondern eine von Hand gebaute
  Schleife des Pruefers.
- **Paket 0088** (2026-09-05): Unter keiner der vier dort behandelten Mutationen wurde
  eine **vorhandene** Probe rot. Zwoelf gruene Proben liessen vier Vorgaben ungeprueft,
  und sichtbar wurde das allein durch einen Mutationslauf.
- **Paket 0097** (2026-09-05, dieser Lauf): 19 Mutationen, alle rot, Nachlauf gruen. Das
  Werkzeug dafuer liegt unter `bau/kp0097-mutieren.py` -- und `bau/` steht in
  `.gitignore`. Beim naechsten sauberen Bau ist es fort.

Das ist dreimal dasselbe Muster: Der Mutationslauf ist das einzige Messgeraet, das
zeigt, ob eine gruene Probe misst oder nur laeuft, und er wird jedes Mal neu gebaut,
einmal benutzt und weggeworfen. Sein Ergebnis ueberlebt als **Satz in einem Bericht**,
nicht als Riegel.

## Was daran wehtut, konkret

Nach diesem Paket sind neunzehn Mutationen an `kern/src/zustandsausgabe.cpp` rot. Kein
Mensch und kein Agent kann das morgen nachpruefen, ohne den Katalog aus dem Bericht
abzuschreiben und den Treiber neu zu schreiben. Aendert ein spaeteres Paket die
Uebersicht, faellt eine dieser neunzehn stillschweigend zurueck auf gruen, und die
Probe bleibt bestanden -- genau die Lage, aus der 0097 entstanden ist, eine Ebene
hoeher.

**Die zweite Regel meiner Rolle lautet: ein Test, der nie fehlschlaegt, prueft nichts.**
Der Nachweis dafuer ist heute eine Handarbeit je Lauf. Genau solche Handarbeit gehoert
nach den Hausregeln in ein Skript.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0097.** Dessen `dateien`-Liste ist eine einzige Probendatei, und seine
Abnahme nennt siebzehn Mutationen an einem Modul. Was hier entsteht, ist ein Werkzeug
ueber den Baum -- neue Dateien, ein neues Mitglied im Arbeitsbereich.

**Nicht Teil des Bruchtesters oder eines Pruefers.** Beide *benutzen* den Lauf; gebaut
wird er vom Testentwickler, dem der Pruefstand gehoert.

**Das Vorbild steht schon da:** `werkzeuge/belegstellen` haengt an nichts, wird von
nichts gelinkt und ist ein Riegel ueber den Baum statt ein Baustein des Erzeugnisses.
Dieselbe Bauart, dieselbe Stelle im Arbeitsbereich.

## Zwei Dinge, die der Projektmanager wissen muss

**Der Schnitt an `CMakeLists.txt` des Arbeitsbereichs.** Ein neues Mitglied braucht
einen Eintrag in `FABRIK_MITGLIEDER`. Diese Datei fassen alle Mitgliedspakete an; die
Liste oben nennt sie deshalb ausdruecklich, damit die Serialisierung greift.

**Die Laufzeit.** Ein Fall kostet Uebersetzen plus Linken plus Probe, gemessen rund
drei Sekunden bei den neunzehn Faellen aus 0097. Ein Katalog ueber alle Module waechst
schnell auf Minuten -- er gehoert deshalb in den Nachtlauf und nicht in `ctest` neben
die Proben. Wo er haengt, entscheidet der Projektmanager; die Abnahme oben verlangt nur
das Ziel, nicht seinen Aufrufort.
