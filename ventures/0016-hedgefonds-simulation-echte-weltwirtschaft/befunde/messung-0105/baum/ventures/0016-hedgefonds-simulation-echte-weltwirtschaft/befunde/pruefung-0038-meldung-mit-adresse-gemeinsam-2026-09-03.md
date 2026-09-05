---
typ: pruefung
paket: 0038-meldung-mit-adresse-gemeinsam
pruefer: kern-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Die vier Bedingungen einzeln. 1 ueber zwei Suchlaeufe auf die beiden Dateien des Pakets, die ich vorher gegen einen echten Treffer gehalten habe; 2 ueber zwei eigene Bauten ausserhalb des Repos -- den Stand vor dem Paket und den heutigen -- und einen Zeilenvergleich der beiden schreiber_probe-Protokolle, dazu eine Laengenrechnung, die zeigt, warum der groessere Puffer die Ausgabe nicht aendern kann; 3 ueber die Auszaehlung aller zehn Abbrueche der Datei gegen die Anforderung; 4 gegen den Uebersetzungsbericht des Tages und ueber drei Mutationen des Kopfes ausserhalb des Repos, von denen jede die Probe rot macht.
befunde: 0
---

# 0038 -- alle vier Bedingungen halten, kein Ruecklaufgrund

Das Paket zieht die Klasse `Meldung` aus `kern/src/schreiber.cpp` in den eigenen Kopf
`kern/include/kern/meldung.hpp`, schliesst `schreiber.cpp` daran an und laesst die
Abbrueche in `kern/src/schritt.cpp` die Adresse im Wortlaut nennen. Es aendert keine
Rechnung und keinen Kontrollfluss.

## Was fremdgemessen ist und was ich selbst gemessen habe

**Fremdgemessen:** `befunde/uebersetzung-2026-09-03.md`, vom Baulauf erzeugt,
`ergebnis: ok`. `meldung_probe` steht dort zweimal namentlich als `Passed` -- Zeile 56
(Testliste des Arbeitsbereichs, Nr. 2 von 11) und Zeile 111 (Testliste des Kerns allein,
Nr. 2 von 8).

**Selbst gemessen,** alles ausserhalb des Repos, kein Artefakt im Baum:

- Frischer Bau gegen die Originalquellen des Kerns, Profil Debug: gruen, 8 von 8 Tests
  bestanden, keine einzige Warnung.
- Derselbe Bau im Profil Release: gruen, 8 von 8, ebenfalls keine Warnung. Beide Profile,
  weil unter Optimierung Warnungen dazukommen, die im Debug-Profil nie erscheinen -- mit
  Fehlerabbruch bei Warnung ist das der Unterschied zwischen gruen und rot.
- Der Warnsatz kommt wirklich an: In der erzeugten Schalterdatei von `meldung_probe` und
  von `kern_geprueft` stehen die fuenfzehn Warnschalter samt Fehlerabbruch, die
  Umbruchsemantik fuer Ganzzahlen und beide Sanitizer mit Abbruch statt blosser Meldung.
  Ein gruener Bau allein waere hier kein Nachweis -- ein leerer Warnsatz uebersetzt
  ebenfalls gruen und prueft weniger.

## Bedingung 1 -- der Kopf traegt die Klasse, und sie ist die einzige Fassung

Geprueft in der Fassung, die der Projektmanager am 2026-09-03 auf die Dateien dieses
Pakets verengt hat.

Die Suche nach einer Klassendefinition dieses Namens ueber Kopfverzeichnis und
Quellverzeichnis des Kerns liefert genau zwei Zeilen: den neuen Kopf und
`kern/src/zustand.cpp:879`. In den beiden Dateien dieses Pakets -- `schreiber.cpp` und
`schritt.cpp` -- steht keine. Die zweite Suche, nach einem Zeichenfeld fester Groesse in
`kern/src/`, trifft ausschliesslich in `zustand.cpp`; beide Dateien dieses Pakets gehen
leer aus.

Bevor ich dem leeren Ergebnis geglaubt habe, habe ich beide Muster gegen einen echten
Treffer gehalten: Sie finden die Fassung in `zustand.cpp` und, im Stand vor dem Paket,
auch die in `schreiber.cpp`. Sie gehen also nicht deshalb leer aus, weil sie leer
ausgehen.

**Die Fassung in `kern/src/zustand.cpp:879` ist hier ausdruecklich kein Befund.** Sie
traegt Paket 0048, das heute `offen` steht und dessen Bedingung 1 woertlich verlangt,
dass danach genau eine Zeile uebrig bleibt. Wer sie hier als Ruecklaufgrund fuehrte,
wiese ein Paket fuer Arbeit zurueck, die es nicht tun durfte.

## Bedingung 2 -- die beiden Proben bleiben gruen, die Abbruchmeldungen unveraendert

Das ist die Bedingung mit dem groessten Aufwand, weil "Zeichen fuer Zeichen dieselben wie
vorher" einen zweiten Bau verlangt.

Ich habe den Stand **vor** dem Paket in ein eigenes Verzeichnis ausserhalb des Repos
geholt und dort gebaut, dann den heutigen Stand daneben, beide mit derselben
Werkzeugkette und denselben Sanitizern. Dann `schreiber_probe` in beiden ausfuehrlich
ueber das Testwerkzeug laufen lassen und die Protokolle nebeneinandergelegt.

**Ergebnis: alle dreissig inhaltlichen Zeilen sind gleich, Zeichen fuer Zeichen.** Der
einzige Unterschied im ganzen Protokoll ist die laufende Nummer, unter der das
Testwerkzeug die Probe fuehrt -- vorher Nr. 4 von 7, heute Nr. 5 von 8, weil
`meldung_probe` dazugekommen ist. Darunter sind sechzehn Zeilen, die eine Abbruchmeldung
im Wortlaut zitieren, darunter die vier, die eine Adresse tragen
(`land.DE.leitzins (Nr. 106)`, `land.DE.inflation (Nr. 105)`,
`land.DE.preisniveau (Nr. 104)`, `welt.preis.2 (Nr. 240)`, `fonds.hebelstand (Nr. 256)`,
`land.US.sektor.1.wertschoepfung (Nr. 1)`, `fonds.kasse (Nr. 255)`).

`schritt_probe` ist in beiden Bauten gruen. Seine drei Wortlautpruefungen treffen den
`spielmodus`-Abbruch, und den hat das Paket nicht angefasst.

**Dazu die Rechnung, die den Vergleich vom Zufall trennt.** Der Umzug hat eine Zahl
geaendert: Der Puffer fasst 512 statt 256 Zeichen. Ein Vergleich, der gruen ausgeht,
belegt nur die geprueften Faelle; die Frage ist, ob es einen *ungeprueften* Fall geben
kann, in dem die groessere Zahl die Ausgabe aendert. Ich habe deshalb die Obergrenze
jeder der fuenf Meldungen aus `schreiber.cpp` ausgerechnet -- Prosa plus laengste
Adresse (47 Zeichen) plus laufende Nummer plus die laengstmoegliche Rundennummer (20
Zeichen). Die groesste ist 157 Zeichen lang, die kleinste 140. Alle fuenf liegen damit
unter der alten Grenze von 255. **Der groessere Puffer kann die Ausgabe von
`schreiber.cpp` nicht aendern, in keinem Fall, nicht nur in den geprueften.**

Zur Gegenrichtung, also ob 512 reicht: Die laengste ueber `Meldung` gebaute Meldung aus
`schritt.cpp` kommt auf 290 Zeichen (der Abbruch in `fuehre_schritt_aus`), die
zweitlaengste auf 245. Bei 256 waeren die beiden laengsten tatsaechlich abgeschnitten
worden, die Begruendung der Zahlenaenderung traegt also. Nichts kommt heute an die 511
heran.

## Bedingung 3 -- jeder Abbruch in `schritt.cpp` nennt die Adresse

Ich habe alle Abbruchstellen der Datei gezaehlt -- es sind zehn -- und einzeln
nachgesehen, statt der Zahl im Baubericht zu glauben.

**Neun von zehn nennen eine Adresse in Textform nach T17 samt laufender Nummer:** die
zweite Stelle in `teile_zu`, die Rumpfabbrueche von `schritt_2_aktionen` und
`schritt_6_abrechnung`, der `Keiner`-Fall in `fuehre_schritt_aus`, die beiden Seiten der
zweiseitigen Probe in der Rundenschleife und die beiden Enden der Rundennummer. Die
vierte Bedingung des Satzes -- die Zuordnungsabbrueche nennen zusaetzlich die Zahl, die
nicht aufging -- ist bei allen vieren erfuellt: Sie tragen die Schrittnummer aus
`spiel.md` samt Namen, die erste Stelle in `teile_zu` zusaetzlich den Platz.

Belegt ist das nicht nur gelesen, sondern gelaufen: `schritt_probe` treibt die beiden
Rundennummer-Enden wirklich durch, und das Protokoll zeigt

- `... partie.runde der Vorrunde ist -1 und damit negativ: ... Gelesen aus partie.runde (Nr. 307)`
- `... ist -9223372036854775808 und damit negativ: ... Gelesen aus partie.runde (Nr. 307)`
- `... ist 9223372036854775807 und damit der groesste int64_t: ... Gelesen aus partie.runde (Nr. 307)`

Die mittlere Zeile ist zugleich der Nachweis, dass der Betrag des kleinsten `int64_t` im
echten Lauf richtig herauskommt und nicht nur in der Probe.

**Zwei Stellen habe ich gegen die woertliche Fassung gehalten und beide nicht als
Ruecklaufgrund gefuehrt.** Ich schreibe das hin, weil sonst nicht zu erkennen waere, ob
ich sie uebersehen oder entschieden habe.

- Der `spielmodus`-Abbruch nennt keine Adresse. Er hat keine -- er handelt von einem
  Modus, nicht von einem Feld. Sein Wortlaut ist ausserdem Bedingung 7 des Pakets 0033
  und wird von `schritt_probe` woertlich geprueft; wer hier eine Adresse verlangte,
  verlangte den Bruch eines fremden, bereits abgenommenen Kriteriums.
- Die erste Stelle in `teile_zu` nennt den Platz als blosse Zahl statt ueber die
  Adressform. Die Adresse liegt dort *per Bedingung* ausserhalb der 310 und hat deshalb
  keine Textform nach T17. Der ausgegebene Text ist inhaltlich derselbe, den die
  Adressform fuer diesen Fall erzeugt.

Beides woertlich zu nehmen hiesse, ein Kriterium zu verlangen, das nicht erfuellbar ist
-- dieselbe Fehlerklasse, die der Projektmanager an Bedingung 1 dieses Pakets heute
gerade berichtigt hat. Ich hebe das Kriterium damit nicht auf, sondern lese den Zweck:
Wo eine Adresse im Spiel ist, steht sie im Wortlaut da. Das ist ausnahmslos der Fall.

## Bedingung 4 -- `meldung_probe` prueft die drei nicht trivialen Stellen

Im Uebersetzungsbericht des Tages steht sie namentlich als `Passed`, zweimal. Das ist die
halbe Bedingung; die andere ist, dass sie die drei Stellen wirklich prueft.

**Ein gruener Test beweist nicht, dass er etwas pruefen kann.** Ich habe den Kopf deshalb
in einer Kopie ausserhalb des Repos dreimal angefasst -- je eine Stelle, je ein
plausibler Fehler -- und jedes Mal neu gebaut und die Probe laufen lassen. Der Baum
selbst blieb unberuehrt.

- **Der Betrag des kleinsten `int64_t`, ueber vorzeichenbehaftete statt vorzeichenlose
  Zahlen gebildet.** Die Probe faellt mit zwei Fehlschlaegen; das Protokoll zeigt
  `zahl(-9223372036854775808) = "-'..--).0-*(+,))+(0("`. Der Fall daneben,
  `I64_MIN + 1`, bleibt dabei gruen -- genau deshalb ist die ausgeschriebene
  `I64_MIN`-Zeile in der Probe die, auf die es ankommt.
- **Die Abbruchschwelle am Pufferende um eins verschoben.** Die Probe stirbt an der
  Bereichspruefung des Feldzugriffs beim 513. Zeichen. Sie erreicht den Rand also
  wirklich, statt in seiner Naehe stehenzubleiben.
- **Die Grenze der Adresspruefung um eins verschoben.** Die Probe stirbt am zweiten
  Riegel, in `index_zu_adresse`. Gefunden hat das der Fall `KEIN_PLATZ`, der genau auf
  der Grenze liegt -- der Fall, den die Probe ausdruecklich mitfuehrt.

Drei Mutationen, drei rote Laeufe. Die Probe haelt, was ihre Bedingung verlangt.

## Wonach ich ausserdem gesucht habe, ohne etwas zu finden

Damit erkennbar ist, wo diese Pruefung hingesehen hat:

- **Determinismus.** Keine Gleitkommazahl im neuen Kopf; er wird in beiden Quellen vor
  der Gleitkommasperre eingebunden, was richtig ist -- die Sperre ist die letzte Zeile
  einer Quelle, nie einer Kopfdatei. Keine streuende Menge: Alle Schleifen laufen ueber
  Felder fester Groesse oder aufsteigende Indizes. Keine Zeitquelle, keine Adresse und
  kein Zeigerwert gelangen in die Ausgabe; die Adresstexte kommen aus einer festen
  Tabelle von Zeichenkettenliteralen mit Programmlebensdauer, nicht aus einem geteilten
  Puffer, der beim zweiten Aufruf ueberschrieben wuerde. Die Ziffern entstehen von Hand
  aus `'0' + Rest`, also ohne Gebietsschema. Kein Zufallsstrom.
- **Rueckkopplung.** Der Meldungsbau greift den Zustand nicht an; er hat keine Schleife
  ohne Schranke. Die Ziffernschleife ist doppelt begrenzt -- durch den Rest und durch die
  Feldgroesse --, die Textschleife durch das Nullbyte und durch die Pufferpruefung bei
  jedem einzelnen Zeichen.
- **Raender.** Von Hand nachgerechnet und mit der Probe abgeglichen: Der Betrag des
  kleinsten `int64_t` entsteht als Differenz von null in vorzeichenloser Arithmetik und
  ist dort darstellbar; das Ziffernfeld fasst 24 Stellen, gebraucht werden hoechstens 20.
  Der Schreibzugriff geht hoechstens auf Index 511 eines Feldes von 512, das abschliessende
  Nullbyte eingerechnet -- kein Ueberlauf, und die Sanitizer laufen bei jedem Testlauf mit.
  Der Fall, in dem eine Zahl mitten in ihren Ziffern anstoesst, endet bei 511 Zeichen mit
  `-92233`, was ich nachgerechnet habe. Keine Division ohne Nenner.
- **Kontrollfluss.** Der Vergleich der Fassungen von `schritt.cpp` vor und nach dem Paket
  zeigt ausschliesslich Meldungstexte, den Einbindungsblock und zwei neue Hilfsfunktionen
  fuer den Schrittnamen. Keine Bedingung, keine Schleife, keine Zuweisung an die
  Zuordnungstafel hat sich geaendert. Die Abbruchfunktion ist als nicht zurueckkehrend
  ausgezeichnet, der Rumpf hinter den beiden Abbruechen in `teile_zu` also unerreichbar.
- **Die Suchregel des Pruefers** auf Zeigerumdeutung, eigene Speicherverwaltung und
  Assembler geht ueber den ganzen Kern nur mit den drei geloeschten Konstruktoren aus
  Paket 0037 auf; die vier Dateien dieses Pakets tragen nichts bei.
- **Verbotene Behaelter und Koepfe** (streuende Mengen, Bildschirm, Datei, Uhr) kommen im
  neuen Kopf nicht vor. Die Probe bindet die Standardausgabe ein, wie alle acht Proben des
  Kerns es tun.

## Eine Anmerkung zur Lesbarkeit der Historie, kein Befund gegen dieses Paket

Der Commit `ae6f605` traegt den Betreff dieses Pakets und enthaelt zusaetzlich
`daten/reihen.toml` und die Statuszeile von Paket 0036 -- Dateien des Datenbauers, dessen
eigener Commit sechs Sekunden spaeter nur noch sein Logbuch enthaelt. Das ist **nicht**
der Kernbauer, der ausserhalb seiner Dateiliste geschrieben haette: `lauf.py:committen`
nimmt die Schreibverzeichnisse einer Rolle als Ganzes, und bei parallelen Laeufen faellt
die Arbeit des einen in den Commit des anderen. Der Apparat kennt das und gleicht es an
anderer Stelle aus.

Ich nenne es trotzdem, weil es die Pruefmethode bestimmt: **Der Commit ist hier keine
verlaessliche Liste dessen, was das Paket geaendert hat.** Ich habe die vier Dateien
deshalb einzeln gegen ihren Vorzustand gehalten, statt den Commit zu lesen. Fuer mich ist
das der dritte Fall derselben Sorte; er steht als offene Faehrte in meinem Logbuch.

## Vorgeschlagene Arbeit

`aufgaben/0056-meldung-abschneiden-kenntlich.md`, `status: vorschlag`. Der Meldungsbau
schneidet am Pufferende stillschweigend ab -- richtig so, ein zerstoerter Stapelrahmen
waere schlimmer --, aber er **markiert** es nicht, und der Aufrufer kann es nicht
abfragen. Heute ist das unerreichbar (laengste Meldung 290 von 511). Der Kopf existiert
allerdings genau deshalb, weil fuenf weitere Pakete ihre eigene Prosa an dieselbe Klasse
haengen werden, und die Adresse steht an den meisten Aufrufstellen am Schluss -- es waere
also gerade der informativste Teil, der verschwindet. Die Begruendung im Vorschlag.

Das ist **keine** nachgereichte Bedingung an 0038: Die Abnahme verlangt es nicht, und ich
senke oder hebe kein Kriterium.
