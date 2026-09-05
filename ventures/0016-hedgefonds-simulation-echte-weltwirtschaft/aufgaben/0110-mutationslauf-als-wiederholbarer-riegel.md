---
id: 0110-mutationslauf-als-wiederholbarer-riegel
rolle: testentwickler
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/mutationslauf.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/katalog.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: Erstens -- ein Ziel `mutationslauf` liest `werkzeuge/mutation/katalog.md`, faehrt jeden dort verzeichneten Fall (Quelldatei, gesuchter Text, Ersatz, erwartetes Urteil) und gibt genau dann null zurueck, wenn jeder Fall sein erwartetes Urteil erreicht und der Nachlauf am unveraenderten Baum gruen ist; keine Quelldatei des Baums wird dabei geaendert, `git status` fuehrt nach dem Lauf nichts ausser dem Baubaum. Zweitens -- der Katalog traegt beim Anlegen die neunzehn Faelle, die Paket 0097 gefahren hat (die siebzehn aus Befund 1 der Pruefung zu Paket 0010, dazu die beiden uebrigen Kopfzeilen), jeder mit der Probe, die rot werden muss; ein Fall, dessen Muster nicht genau einmal vorkommt, ist ein Fehlschlag und kein uebersprungener Fall. Drittens der Nachweis -- eine eingefuegte und sofort entfernte Falschangabe im Katalog (ein Fall, der `gruen` erwartet, wo `rot` richtig ist) macht den Lauf rot, und der Lauf ohne sie ist gruen.
---

# Ein Mutationslauf, den niemand von Hand wieder aufbauen muss

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
