---
id: 0129-bezeichner-im-kommentar-loest-auf
rolle: testentwickler
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/bezeichner/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/bezeichner/bezeichner_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Bedingung 2 ist die tragende -- ein Name, der im Kern nur in einer negativen Sichtbarkeitszusicherung der Form `requires { &X::name; }` vorkommt, gilt als **nicht** deklariert; ohne diese Regel bleibt der Riegel an der Wiederherstellung des alten `KEIN_PLATZ`-Wortlauts gruen, mit ihr wird er rot und nennt `schreibe`. Beide Laeufe sind zu zeigen.
---

# Ein Bezeichner in einem Kommentar wird von nichts geprueft -- und die naheliegende Pruefung waere an 0101 blind gewesen

**Vorgeschlagen am 2026-09-05 vom `kern-pruefer` aus der Pruefung zu Paket
`0101-zustandhpp-kein-platz-nennt-schreibe`.** Der Befund dazu liegt unter `befunde/`
und traegt die Messungen, auf die sich die Zahlen unten stuetzen.

## Warum ueberhaupt

Der Belegstellenriegel prueft heute zwei Dinge, und beide sind von derselben Bauart:
eine Zeilenangabe in eine fremde Datei ist nicht haltbar, und ein zitierter
Ueberschriftentext muss dort wirklich stehen. Beide Male geht es um einen Verweis, der
beim Lesen richtig aussieht und ins Leere zeigt.

**Der dritte Fall derselben Familie hat keinen Riegel: der Bezeichner.** Ein Kommentar
nennt eine Funktion, eine Klasse oder eine Konstante in Rueckwaerts-Anfuehrung, die
Sache wird spaeter umbenannt, und der Kommentar bleibt stehen. Er ist dann teurer als
gar keiner: Wer ihn liest, hat die Frage gestellt, eine Antwort bekommen und hoert auf
zu suchen.

Belegt ist der Fall zweimal, beide Male von Hand nachgezogen:

* **Paket 0101** -- der Kommentar am Fehlerwert der Adresssuche berief sich auf eine
  Zustandsfunktion, die es seit der Umbenennung durch Paket 0027 nicht mehr gab. Der
  Satz stand ueber mehrere Pakete hinweg da.
* **Paket 0123** -- der Kopf einer Rechenart erklaert sich fuer aufruferlos, waehrend
  ein anderer Kasten sie fuenfmal ruft.

Das ist dasselbe Argument, mit dem der Belegstellenriegel selbst begruendet wurde:
Sechs Pakete hatten Belegstellen von Hand nachgezogen, jedes war richtig, und zusammen
waren sie der Beleg, dass Handnachfuehrung den Fehler einholt statt ihn abzustellen.
Hier stehen zwei solche Pakete, und der zweite ist noch offen.

## Warum das ein eigenes Werkzeug ist und keine dritte Bedingung im Belegstellenriegel

Zwei Gruende, der zweite ist der schwerere.

**Der Eingang ist ein anderer.** Die beiden bestehenden Bedingungen lesen Text und
schlagen in Text nach. Diese hier muss aus C++-Quellen eine Menge deklarierter
Bezeichner bilden und einen Kommentartext dagegen halten -- anderer Eingang, andere
Datenhaltung, andere Fehlerquellen.

**Die Datei ist besetzt.** Auf `werkzeuge/belegstellen/belegstellen_riegel.cpp` stehen
zur Stunde vier Pakete: 0083, 0105, 0106 und 0115. Eine fuenfte Bedingung dort
serialisiert hinter allen vieren, ohne dass ein einziger inhaltlicher Grund dafuer
spraeche. Der eigene Ordner unter `werkzeuge/` ist der Weg, den Paket 0110 fuer den
Mutationstreiber schon gegangen ist; die einzige geteilte Datei ist die Mitgliederliste
im obersten Bauskript, und die beansprucht heute niemand.

## Die Blindstelle, die diesen Vorschlag traegt

Ich habe die naheliegende Fassung gebaut und ueber den ganzen Kern laufen lassen:
5.343 Kommentarzeilen, jeder in Rueckwaerts-Anfuehrung genannte Bezeichner gegen die
Menge aller im Code vorkommenden Bezeichner gehalten. Ergebnis: 19 nicht aufloesbare
Kandidaten, **alle falsch positiv**, und **kein einziger toter Bezeichner**.

**Und dieselbe Fassung haette 0101 nicht gefunden.** Der tote Name war `schreibe`, und
`schreibe` kommt im Kern in einer Codezeile vor -- in der Probe des Zustands, in einem
`requires`-Ausdruck, dessen ganzer Zweck die Zusage ist, dass es den Namen **nicht**
gibt. Eine Pruefung ueber blosse Mengenzugehoerigkeit haelt eine negative Zusicherung
fuer eine Deklaration und geht genau an dem Fall vorbei, der sie veranlasst hat.

Das ist der Grund, warum dieser Vorschlag eine Bedingung mehr traegt als die Idee
dahinter, und warum die Abnahme sie an einem ausgefuehrten Rotnachweis festmacht statt
an einer Beschreibung.

Die 19 Kandidaten, damit sie niemand zweimal erheben muss, und weil sie den Zuschnitt
der Ausnahmeregeln bestimmen: Kennungen aus den Vorgaben (`M15`, `M16`, `M17`, `M18`,
`N10`, `N11`), eine Namensvorsilbe (`MAL_`), zwei Schluessel der Instrumententabellen
aus `parameter.toml` (`instrument_min`, `instrument_max`), ein fremder Testvektorname
(`fnv1a_64_test_vector`), ein CMake-Ziel (`kern_geprueft`) und neun Woerter, die die
Koepfe des Kerns als fremd oder verboten fuehren (`double`, `float`, `sqrt`, `pow`,
`log`, `abort`, `consteval`, `unsafe`, `grep`).

## Abnahme

**Bedingung 1 -- der Riegel laeuft und ist ein `ctest`-Eintrag.** Er liest die Koepfe,
die Quellen und die Proben des Kerns, sammelt jeden in Rueckwaerts-Anfuehrung genannten
Bezeichner aus den Kommentaren und meldet jeden, der nirgends aufloest. Auf dem dann
geltenden Baum endet er mit Code 0 und nennt im Bericht drei Zahlen: gelesene
Kommentarzeilen, gepruefte Bezeichner, uebergangene Fundstellen mit Grund.

**Bedingung 2 -- die negative Zusicherung zaehlt nicht als Deklaration.** Ein Name, der
im Kern ausschliesslich innerhalb eines `requires`-Ausdrucks der Form
`requires { &X::name; }` vorkommt, gilt als nicht deklariert. Nachzuweisen an einer
Kopie des Baums, an der der Wortlaut vor Paket 0101 wiederhergestellt ist -- der
Kommentar am Fehlerwert der Adresssuche nennt dann wieder `lies`, `schreibe` und
`index_zu_adresse`. Zwei Laeufe, beide zu zeigen:

  1. **ohne** die Regel: Code 0, der tote Name wird nicht gemeldet -- das ist der Beleg,
     dass die Regel etwas leistet und nicht bloss dasteht;
  2. **mit** der Regel: Code ungleich 0, und die Meldung nennt `schreibe` und die
     Datei, in der er steht.

**Bedingung 3 -- die Ausnahmen sind Regeln und keine Namensliste.** Die heute gemessenen
19 falschen Kandidaten fallen entweder unter eine benannte Regel (Vorgabenkennung,
Schluessel aus `parameter.toml`, CMake-Ziel, Dateiname des Vorhabens, Schluesselwort
oder verbotener Name der Sprache) oder erscheinen unter den uebergangenen Fundstellen
mit ihrem Grund. Eine Liste einzelner geduldeter Namen ist ausgeschlossen: Sie waere
genau die Handnachfuehrung, gegen die dieses Paket antritt. Der Riegel bleibt dabei
gruen -- nach heutigem Stand traegt der Kern keinen toten Bezeichner.

**Bedingung 4 -- der Baum bleibt in beiden Bauprofilen gruen**, und die Zahl der
`ctest`-Eintraege steigt um genau eins.

## Was ausdruecklich nicht dazugehoert

* **Die Kommentare ausserhalb des Kerns.** Pruefstand und Werkzeuge bleiben aussen vor,
  bis die Regel im Kern steht. Wer sie gleich mitnimmt, verhandelt drei Ausnahmesorten
  mehr in demselben Lauf.
* **Der Wahrheitsgehalt einer Aussage ueber einen Bezeichner.** Dass `mal` "heute ohne
  Aufrufer" heisst, obwohl es fuenf hat, faengt kein Namensriegel -- das ist Paket 0123
  und bleibt es.
* **Die beiden bestehenden Bedingungen des Belegstellenriegels.** Sie bleiben, wo sie
  sind; dieses Werkzeug liest keine Verweise und keine Ueberschriften.
