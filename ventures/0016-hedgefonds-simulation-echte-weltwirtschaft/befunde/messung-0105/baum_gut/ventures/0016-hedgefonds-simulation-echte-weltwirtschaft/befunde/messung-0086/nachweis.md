# Messung zu Paket 0086 -- Schluesselwort mit Abstand, Dokumentname rechts

Datum: 2026-09-05. Rolle: testentwickler. Geaenderte Datei: genau eine,
`werkzeuge/belegstellen/belegstellen_riegel.cpp`. Die drei Skripte unter `bau/` sind
Werkzeug des Laufs, kein Erzeugnis des Pakets.

**Der Baum driftet, und das ist hier keine Nebenbemerkung.** `HEAD` beim Beginn des
Laufs: `87f2604`; waehrend des Laufs auf `a127600` (`architekt: 0051`) gewandert, dazu
`daten/reihen.toml` und `kern/test/zustandsausgabe_probe.cpp` durch parallele Laeufe im
Arbeitsbaum geaendert. **Die erste Messung des Laufs ist dadurch wertlos geworden:** Sie
gab 38 aufgeloeste Zitate, eine spaetere Messung derselben Fassung 33, und die Differenz
stammte vollstaendig aus `reihen.toml`. Alle Zahlen unten sind deshalb **paarweise
unmittelbar nacheinander** am selben Baum gemessen -- die Abnahme verlangt genau das und
nennt ausdruecklich keine absolute Zahl.

Ein Zwischenstand war dadurch auch der einzige rote Lauf, den dieses Paket ausgeloest
hat: `kern/test/zustandsausgabe_probe.cpp:379` nennt eine Zeilennummer in
`specs/.../technik.md` und macht Bedingung 1 rot. Das ist ein Befund **gegen ein fremdes
Paket**, nicht gegen dieses; er war beim Abschluss dieses Laufs wieder verschwunden
(5 Zeilenverweise, 0 mit Dateinamen). Gemeldet, nicht angefasst.

## Das Abnahmekriterium, an der Bedingung gemessen

Am selben Baum, mit derselben Quelldatei, back-to-back:

| Fassung | Zitate | aufgeloest | uebergangen | rot |
|---|---|---|---|---|
| **vorher** (beide Lockerungen aus) | 33 | 33 | 58 | – |
| nur der Wortabstand | 33 | 33 | 59 | – |
| nur die Suche nach rechts | 33 | 33 | 58 | – |
| **nachher** (beide) | 34 | 34 | 58 | – |

Die Zahl der gefundenen Zitate **steigt gegenueber dem unmittelbar vorhergehenden Stand
desselben Baums** um genau eins, alle loesen auf, und die uebergangenen Fundstellen
bleiben gleich -- keine Fundstelle wird zu Unrecht rot. Der Lauf ist gruen; die
vollstaendige Testreihe meldet 14 von 14 bestanden.

Die Zeile `vorher` schaltet zusaetzlich den neuen Selbsttest stumm. Das ist kein
Nachlass, sondern die Sache selbst: `ABSTANDSFAELLE` gehoert zu diesem Paket, und ohne
die Lockerungen braeche der Lauf mit Code 2 ab, ehe der Bestand ueberhaupt gelesen ist.
Gemessen werden soll dort der Bestand, nicht die Tabelle.

## Was jede Lockerung einzeln traegt -- die Antwort in einem Satz

**Keine traegt allein ein einziges Zitat.** Der Wortabstand macht die Stelle *sichtbar*
und erzeugt dabei **genau eine** neue Fundstelle (58 → 59): Ihr Absatz nennt links
keinen Dokumentnamen, also faellt sie als "kein Dokumentname im Absatz" unter die
uebergangenen. Die Suche nach rechts macht sie *aufloesbar* und erzeugt **null** neue
Fundstellen -- allein aendert sie nicht eine einzige Zahl.

Dass die Rechtssuche allein nichts bewegt, ist zugleich der Beleg dafuer, dass sie
**keine vorhandene Zuordnung umhaengt**: Sie laeuft nur, wenn links nichts steht. Damit
ist die Frage nach dem Vorrang der beiden Nachbarn nicht offen gelassen, sondern
zugunsten der gemessenen Linksregel entschieden.

Zusammen: ein Zitat mehr, eine Fundstelle weniger unter den uebergangenen, unter dem
Strich +1 Zitat und ±0 Fundstellen. Es ist die dritte Belegstelle aus Paket 0034 in
`daten/adressen.md` -- fuenf Woerter Abstand zur Anfuehrung, `technik.md` rechts in der
Klammer.

## Die Schwelle fuenf, je Schritt gemessen

| `WORTABSTAND_HOECHSTENS` | Zitate | uebergangen |
|---|---|---|
| 0 (= aus) | 33 | 58 |
| 4 | 33 | 58 |
| 5 | 33 | 59 |
| 6 | 33 | 59 |
| 8 | 33 | 59 |

Bei vier bleibt die Stelle ungefangen, bei fuenf faellt sie an; sechs und acht aendern
nichts mehr. Gewaehlt ist der **kleinste** Wert, der die gemessene Form traegt, und
nicht der groesste, der noch nichts kaputt macht -- eine Schwelle mit Luft nach oben ist
eine geratene, auch wenn die Luft heute leer ist.

## Die drei Riegel, und was ihr Abschalten kostet

| Mutation | Zitate | aufgeloest | uebergangen | rot |
|---|---|---|---|---|
| ohne Trennung der Zitatmarken | 38 | 33 | 70 | **5** |
| ohne den Riegel am zweiten Schluesselwort | 33 | 33 | 59 | – |
| Rechtssuche ohne Satzgrenze | 34 | 33 | 57 | **1** |

**Die Trennung der Zitatmarken ist der teuerste der drei.** Ohne sie faengt der Riegel
fuenf Stellen **in seinem eigenen Quelltext**, alle falsch: eine im Kopfkommentar
(`spiel.md` im Gegenstrich, ein Wort hinter dem Schluesselwort) und vier in
`ZITATFAELLE`, wo hinter `Namensart::Ueberschrift` ein Komma und danach ein
Zeichenkettenliteral steht. Genau davor warnt das Arbeitspaket, und genau so ist es
eingetreten -- gemessen, bevor der Kopfkommentar geschrieben war.

**Der Riegel am zweiten Schluesselwort aendert am Bestand nichts.** Das steht so im
Quelltext und wird nicht verschwiegen: Der Bestand fuehrt heute keine Stelle dieser
Bauart. Nachgewiesen ist er allein an Fall 5 in `ABSTANDSFAELLE`, der die Form eigens
baut. Er bleibt trotzdem stehen, weil erst die Lockerung selbst die Bauart moeglich
macht, die er faengt -- ohne ihn naehme ein fernes Schluesselwort dem nahen die
Anfuehrung weg *und* ruecke die Leseschleife ueber es hinweg.

## Der Rotnachweis, je Teilregel einer

Gefahren mit `bau/kp0086-rotnachweis.sh <mutation>`; der mutierte Quelltext kommt nie
auf die Platte (`python3 | c++ -x c++ -`), jede Ersetzung traegt ein
`assert count == 1`. Das Suffix `-rein` schaltet die jeweils **andere** Lockerung nicht
mit ab -- ohne diese Trennung fielen Faelle, die mit der gemessenen Regel nichts zu tun
haben, und der Nachweis zeigte auf die falsche Stelle.

| Mutation | rot geworden | belegt damit |
|---|---|---|
| `ohne-abstand` | Faelle 1, 6, 7, 8 | die erste Lockerung ueberhaupt |
| `nur-abstand` | Faelle 1, 7 | die zweite Lockerung ueberhaupt |
| `abstand6-rein` | Fall 2 | die Schwelle fuenf |
| `ohne-satzriegel-rein` | Fall 3 | das Satzende beendet die Suche |
| `ohne-marken-rein` | Fall 4 | nur ankuendigende Anfuehrungszeichen |
| `ohne-schluesselriegel-rein` | Fall 5 | die Anfuehrung gehoert dem naeheren |
| `rechts-ohne-satzgrenze-rein` | Fall 6 | die Satzgrenze der Rechtssuche |

Fall 8 wird nur unter `ohne-abstand` rot. Er ist die erwartete Leermeldung zu Fall 7 --
ohne ihn zeigte jener nur, dass die Rechtssuche *etwas* findet, und nicht, dass sie das
Richtige findet. Er prueft keine eigene Regel, und das steht auch in seiner Herkunft.

**Zwei der acht Faelle waren zuerst aus dem falschen Grund gruen**, und das gehoert
hierher, weil es der Grund ist, warum der Rotnachweis nicht optional ist: Fall 2 hatte
acht Woerter statt der behaupteten sechs, Fall 3 wurde von der Wortzahl gestoppt statt
vom Satzende. Beide wurden erst rot, nachdem ihr Text auf die Regel gebracht war, die er
behauptet. Ein Fall, der aus dem falschen Grund gruen ist, misst nichts.

## Die beiden Nebenzeilen

Beide bewegen keine Zahl des Riegels; die Zahlen oben sind vor und nach ihnen dieselben.

**Aus 0089.** Der Kopfkommentar nennt als Herkunft des Kopffeldzitats in
`daten/adressen.md` jetzt `0007-adressverzeichnis-310` statt 0004, und daneben, woran es
nachpruefbar ist: an der `dateien`-Liste des Arbeitspakets, nicht am Betreff des
Commits. Nachgemessen: Die Liste von 0004 nennt keine Datei unter `daten/`, die von 0007
nennt genau diese. Der alte Stand bleibt als solcher benannt, weil der Absatz sonst eine
Regel ohne das Beispiel traegt, an dem sie gescheitert ist.

**Aus 0095.** Fall 7 in `NAMENSFAELLE` ist als **historisch** ausgewiesen und nennt den
Commit, der seinen Wortlaut entfernt hat: `9bb7492` (Paket 0044, 2026-09-04), wo sechs
Belegstellen dieser Bauart in `kern/test/schranken_probe.cpp` durch den Schluesselnamen
ersetzt wurden. Nachgemessen am Baum: Die Datei traegt heute die Form
`parameter.toml, Schluessel `druck_max`:` und nicht mehr Dateiname-Nummer-Doppelpunkt.

Danach stimmt die Zahl im Tabellenkopf: Sie steht jetzt auf **drei** statt vier, und die
drei sind die Faelle 1, 2 und 4. Alle drei sind am 2026-09-05 einzeln nachgeschlagen
worden und tragen ihren Wortlaut wirklich -- `daten/adressen.md` Zeile 541,
`daten/reihen.toml` im Feld `in_dieser_datei` der Reihe 9, `kern/src/zustand.cpp` bei
`stelle_basiswechsel(Gebiet::RW)`. Fall 8 zaehlt nicht mit; seine Herkunft sagt
"abgewandelt" und behauptet keinen Wortlaut. Die Zahl **und** die Angabe daneben sind
zusammen berichtigt -- nur die Zahl zu senken haette sie richtig gemacht und die Adresse
weiter falsch gelassen, und genau das schliesst das Arbeitspaket aus.

Der Selbsttest meldet weiter acht Faelle zur Suche nach links, alle wie erwartet.

## Werkzeug

Drei Skripte unter `bau/`, damit die Messung wiederholbar ist und nicht als Zahl in
einem Bericht endet:

* `kp0086-mutieren.py <mutation>` -- schreibt den Mutanten nach stdout, fasst die
  Quelldatei nicht an;
* `kp0086-messen.sh <mutation>` -- baut ihn und gibt die drei Zahlen von Bedingung 2 aus;
* `kp0086-rotnachweis.sh <mutation>` -- baut ihn und zeigt, welche Faelle fehlschlagen.

Abgeschaltet wird immer **im Rumpf** und nie am Aufruf: Faellt eine Funktion aus dem
Spiel, bricht `-Werror=unused-function` den Bau ab, statt den Riegel rot zu machen.
