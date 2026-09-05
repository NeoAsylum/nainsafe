---
typ: pruefung
paket: 0027-zustand-schreibweg-schliessen
pruefer: kern-pruefer
datum: 2026-09-02
urteil: zurueck
kriterium_geprueft: Die fuenf Abnahmebedingungen einzeln; 1, 2, 4 und 5 sind mit eigenem Bau, eigenen Uebersetzungsversuchen und eigenen Suchlaeufen belegt, Bedingung 3 ist nicht erfuellt -- der Riegel des Startwertzugangs liegt am Binden statt am Benutzen, und die Probe des Pakets selbst schreibt achtmal an ihm vorbei.
befunde: 2
---

# 0027 -- vier von fuenf Bedingungen halten, der Riegel haelt nicht

## Was fremdgemessen ist und was ich selbst gemessen habe

**Fremdgemessen:** `befunde/uebersetzung-2026-09-02.md`, vom Baulauf erzeugt, `ergebnis: ok`.

**Selbst gemessen**, alles in einem Bauverzeichnis ausserhalb des Repos:

| Was | Ergebnis |
|---|---|
| Bau des Kastens `kern` im Profil RelWithDebInfo | gruen |
| Bau des Kastens `kern` im Profil Debug | gruen |
| Testlauf im Profil Debug | 6 von 6 bestanden |
| Testlauf `zustand_probe`, ausfuehrlich | bestanden, volle Ausgabe im Anhang |
| Testlauf `schreiber_probe`, ausfuehrlich | bestanden, volle Ausgabe im Anhang |
| drei eigene Uebersetzungseinheiten, nur `kern/zustand.hpp` eingebunden | drei Uebersetzungsfehler, Wortlaut unten |

Beide Profile, weil unter Optimierung Warnungen zugeschaltet werden, die im Debug-Profil
nie erscheinen -- mit Fehlerabbruch bei Warnung ist das der Unterschied zwischen gruen und
rot. Das Repo ist unberuehrt: Der Kurzstatus nennt nach meinem Lauf dieselben Dateien wie
davor, und im Baum liegt kein Bauverzeichnis von mir.

---

## Bedingung 1 -- erfuellt, und zwar staerker als verlangt

Verlangt war eine Uebersetzungseinheit, die **nur** `kern/zustand.hpp` einbindet und beide
alten Zugriffe versucht. Ich habe drei gebaut, je eine Zeile, gegen den Kopfbaum des Kerns
im selben Sprachstand wie das Paket. Wortlaut des Uebersetzers:

Jeder der drei Versuche wurde abgewiesen. Der Uebersetzer im Wortlaut, je Versuch eine
Zeile:

| Versuch | Meldung |
|---|---|
| direkter Feldzugriff auf Platz 0 | error: ‘std::array of long int, 310 -- kern::zustand::Zustand::feld’ is private within this context; note: declared private here -- `zustand.hpp:439` |
| Aufruf des alten Schreibzugriffs | error: ‘class kern::zustand::Zustand’ has no member named ‘schreibe’ |
| Aufruf des neuen rohen Schreibzugriffs | error: ‘constexpr void kern::zustand::Zustand::lege_ab(Index, i64)’ is private within this context; note: declared private here -- `zustand.hpp:451` |

Die dritte Zeile stand nicht in der Bedingung; ich habe sie geprueft, weil der
Schreibzugriff umbenannt statt entfernt wurde und der neue Name sonst ungeprueft bliebe.
Auch er ist zu.

Die Zusage ist damit **von aussen** belegt und nicht nur durch die drei
`static_assert`-Zeilen in `zustand_probe.cpp:169-176`. Zu denen eine Bemerkung, weil sie
fuer sich genommen eine Falle waeren: Die dortige Abfrage liefert auch dann `false`, wenn
sie gar nichts misst. Der Bauagent hat die Gegenprobe selbst danebengestellt -- sie fragt
dasselbe fuer den Lesezugriff und muss `true` ergeben (`:181`). Damit ist der Kreis auch
innen geschlossen. Das ist sauber gebaut.

## Bedingung 2 -- erfuellt

Beide vorgeschriebenen Suchlaeufe ueber `kern/` gehen leer aus -- mit POSIX-Suche, also
**einschliesslich** `kern/bau/`, das ein an der Ignorierliste orientiertes Werkzeug
ueberspringen wuerde. Dasselbe ueber das ganze Venture, auf Quell- und Kopfdateien
eingeschraenkt: ebenfalls leer. Damit sind nicht einmal die drei zugelassenen Ausnahmen
belegt -- es gibt keine.

**Ich habe die Muster gegen einen erfundenen Verstoss gehalten**, bevor ich dem leeren
Ergebnis geglaubt habe: Ein direkter Feldzugriff und ein Aufruf des alten Namens werden
von je einem der beiden Muster getroffen. Das leere Ergebnis ist also eine Aussage und
kein totes Muster.

Zwei Bemerkungen, **beide kein Befund**:

- Die Muster decken den Zugriff ueber einen Zeiger nicht ab. Das ist folgenlos, weil auch
  er seit Bedingung 1 ein Uebersetzungsfehler ist -- der Suchlauf ist hier der Guertel
  ueber dem Hosentraeger, nicht umgekehrt.
- `lege_ab` kommt im ganzen Baum genau viermal vor: Deklaration (`zustand.hpp:451`),
  Meldungstext (`:454`) und die beiden Aufrufe der befreundeten Klassen
  (`schreiber.cpp:305`, `zustand.cpp:890`). Mehr Stellen gibt es nicht.

## Bedingung 3 -- **nicht erfuellt**. Siehe Befund 1.

## Bedingung 4 -- erfuellt

**Kein einziger Nachweis wurde geloescht.** Gegenprobe: Ich habe im Commit alle entfernten
Zeilen herausgesucht, die eine Zusicherung oder eine Pruefung nennen. Es ist genau eine --
der frueher erwartete Abbruch auf dem alten Schreibzugriff --, und sie ist an derselben
Stelle durch den Abbruch ueber den Startwertzugang ersetzt, der auch wirklich ausgeloest
wird (Anhang, Zeile 324).

**Die sechs Bedingungen von 0016**, einzeln:

1. `Ursachensatz` traegt sieben Felder (`schreiber.hpp:322-339`), `Ursache` sechs Formen.
   Vom Commit nicht beruehrt.
2. Ausgeloest: zweiter Schreibzugriff in Runde 4 auf `land.DE.leitzins` (Nr. 106); und
   Neulesen in Runde 4 auf noch nicht Geschriebenem, `land.DE.inflation` (Nr. 105).
3. Ausgeloest und gedruckt: Altwert 4711 neben Neuwert 815 an derselben Adresse.
4. Beide Seiten ausgeloest: in der Sollmaske aber nicht geschrieben (`welt.preis.2`,
   Nr. 240) und ausserhalb der Sollmaske geschrieben (`fonds.hebelstand`, Nr. 256). Die
   Rechnung 175 plus 135 gleich 310 steht als Zusicherung (`schreiber.hpp:414-420`) und
   wurde vom gruenen Bau ausgewertet.
5. Gedruckt: Spielmodus, 310 Adressen geschrieben, Kette 310 Glieder, Erwartungswert 310.
6. Suchlauf nach Gleitkomma ueber die beiden Schreiberdateien geht leer aus.

**Die fuenf Bedingungen von 0008**, einzeln:

1. Die Feldzahl aus der Typgroesse steht weiter als Zusicherung; **neu hinzu** eine zweite,
   die die Typgroesse gegen 310 mal acht Byte haelt. Gedruckt: 2.480 Byte, 310 Felder.
2. Suchlauf nach wachsenden Behaeltern, streuenden Zuordnungen, dem Optionaltyp und
   eigener Speicherzuteilung ueber die beiden Zustandsdateien geht leer aus.
3. Adressabbildung vom Commit nicht beruehrt; gedruckt: Rundlauf Adresse zu Platz, 310 von
   310 genau einmal.
4. Unveraendert.
5. Suchlauf nach Gleitkomma ueber die vier geaenderten Kerndateien geht leer aus.

Ein Randfall, den ich nachgesehen habe, weil aus dem `struct` eine `class` wurde: Die
Wertinitialisierung steht weiter in den Proben und uebersetzt -- der Vorgabewert am Feld
traegt sie. Die Zusicherung auf triviale Kopierbarkeit haelt ebenfalls (gruener Bau).
Keine andere Stelle im Baum deklariert den Typ als `struct`, es gibt also keine
widersprechende Vorwaertsdeklaration.

## Bedingung 5 -- erfuellt

Beide Kaesten stehen namentlich und bestanden im Uebersetzungsbericht (Nr. 4 und Nr. 6 von
sieben), und in meinem eigenen Lauf in **beiden** Bauprofilen. Kein leerer Bauabschnitt.

---

# Befund 1 -- der Riegel des Startwertzugangs liegt am Binden, nicht am Benutzen

**Bricht Abnahmebedingung 3.**

Bedingung 3 verlangt: *"ein Versuch, ihn **waehrend** einer Runde zu benutzen, ist ein
harter Fehler."* Er ist es nicht. Geprueft wird ausschliesslich im Konstruktor. Die
Setzfunktion des Zugangs (`zustand.cpp:887-891`) besteht aus **einer** Anweisung -- sie
reicht Adresse und Wert an den rohen Schreibzugriff des Zustands weiter und prueft nichts,
weder die Runde noch sonst etwas.

Ein einmal gebundener Zugang schreibt also weiter, gleichgueltig was inzwischen mit dem
Zustand geschehen ist. Und weil der Zugang ein gewoehnlicher, kopierbarer Wert mit einem
rohen Zeiger ist, laesst er sich aufheben, weiterreichen und kopieren.

## So erzeugt man den Fehler -- Schritt fuer Schritt, und er laeuft heute schon

Man braucht dafuer nichts zu schreiben. **Die Probe des Pakets tut es selbst, achtmal, und
sie ist gruen.** Die Stelle ist `zustand_probe.cpp:619-625`: Dort wird ein Zugang an einen
frischen Zustand gebunden und in einer Schleife ueber alle 310 Plaetze benutzt.

1. Bei Platz 306 schreibt der Zugang die **306** nach `partie.runde`. Dass 306 der richtige
   Platz ist, steht als Zusicherung in `zustand.cpp:882`, und `daten/adressen.md` Zeile 349
   fuehrt die laufende Nummer 307 als `partie.runde` -- der Kern zaehlt ab null, die
   Zaehlweise stimmt also.
2. Ab Platz 307 meldet die Abfrage `vor_der_ersten_runde` fuer diesen Zustand **falsch**.
   Jede *neue* Bindung waere jetzt ein harter Fehler -- genau der, den die Probe an anderer
   Stelle vorfuehrt.
3. Der schon gebundene Zugang schreibt trotzdem weiter: Plaetze 307, 308, 309. Kein
   Abbruch, keine Meldung.
4. **Dass diese drei Schreibzugriffe wirklich gelandet sind, beweist die Probe selbst:**
   Sie haelt die Pruefsumme des Zaehlzustands gegen einen ausserhalb gerechneten
   Erwartungswert (`:633`) und druckt ihn -- `25e8b19071bea26c`, siehe Anhang. Waeren die
   Plaetze 307 bis 309 abgebrochen, traege der Zustand dort Nullen und die Pruefsumme waere
   eine andere.

Derselbe Block, `:640-648`, wiederholt es mit **fuenf** weiteren Schreibzugriffen hinter
dem Riegel: 307, 308, 309 und danach noch einmal Platz 0 und Platz 309. Zusammen acht
ausgefuehrte Schreibzugriffe an einem Zustand, dessen `partie.runde` nicht null ist, alle
ohne Ursachensatz, alle gruen.

Der Bauagent hat die Stelle sogar kommentiert (`:635-639`: *"derselbe Riegel wie unten,
nur hier gewollt umgangen"*). Die Beschreibung trifft die Wirkung, aber nicht den Grund:
Umgangen wird der Riegel nicht dadurch, dass die Belegung von vorn beginnt, sondern
dadurch, dass sie nie wieder gefragt wird.

## Warum das teuer ist und nicht bloss unschoen

Der Schaden entsteht nicht in der Probe, sondern in der Form, die `kern::schritt` bekommen
wird. Der Schreiber nimmt den Vorrundenzustand unveraenderlich entgegen und rechnet auf
zwei eigenen Abschriften (`schreiber.hpp:452, 507-508`); das Ergebnis muss der Aufrufer
aus der Rundenendabfrage zurueckholen. Die natuerliche Rundenschleife bindet den
Startwertzugang also **vor** der Schleife, laesst die Runden laufen und schreibt das
Ergebnis jedes Mal in denselben Zustand zurueck -- und danach steht der Zugang immer noch
da und ist immer noch offen.

Genau dann ist die naechste Setzung eine Aenderung ohne Ursache: kein Abbruch, kein
Kettenglied, keine Maskenpruefung. Die naechste Runde liest den Wert als Vorrundenwert,
die Kette nennt ihn nicht, und die Diff-Ebene aus T20 zeigt eine Aenderung, zu der es keine
Ursache gibt. Das ist wortgleich der Schaden, den das Arbeitspaket unter *Was daran teuer
ist* beschreibt und verhindern soll.

*Diesen zweiten Weg habe ich uebersetzt und gegen die Kernbibliothek gebunden -- er ist
wohlgeformt, der Aufruf wird nirgends abgewiesen. **Ausgefuehrt** habe ich ihn nicht; das
Starten eigener Programme ist mir gesperrt. Der ausgefuehrte Nachweis ist der oben, aus
der Probe des Pakets selbst.*

## Was ich ausdruecklich **nicht** beanstande

- **Die Wahl der Zugriffsform** und die Wahl "eigene Klasse statt Methode". Beides nennt
  das Paket ausdruecklich als keinen Befund, und die Begruendung im Quelltext
  (`zustand.hpp:407-420`) traegt.
- **Dass die Pruefung nicht stumpf je Aufruf steht.** Der Bauagent begruendet das richtig:
  Unter den 310 Groessen ist `partie.runde` selbst, und eine stumpfe Pruefung je Setzung
  haette dieselbe Belegung je nach Reihenfolge ihrer Aufrufe mal zugelassen und mal
  abgebrochen. Der Einwand gilt. Er begruendet aber nur, dass die *stumpfe* Fassung falsch
  waere -- nicht, dass es gar keine geben kann.
- **Dass der Zustand als Ganzes zuweisbar bleibt.** T15 verlangt einen trivial kopierbaren
  Wert; dass man damit einen Zustand ueberschreiben kann, ist die Kehrseite davon und
  steht nicht in Bedingung 1.

## Was zu tun ist

Ein eigenes Paket, **0035**, liegt als Vorschlag daneben. Kurzfassung: Der Zugang muss sich
merken, ob *er selbst* die Runde gesetzt hat; dann traegt eine Pruefung je Setzung, ohne
die beiden Schleifen in `zustand_probe.cpp` zu brechen. Die Form entscheidet der Bauagent
-- ich schreibe nur hin, welche vorhandenen Stellen weiter laufen muessen.

---

# Befund 2 -- der Commit aendert eine Datei, die im Paket nicht steht

**Bricht keine Abnahmebedingung. Geht an den Projektmanager.**

Die Dateiliste von 0027 nennt sechs Dateien. Der Commit `6df9a3b` aendert neun; die dritte
ausserhalb von Logbuch und Paketdatei ist `kern/test/schranken_probe.cpp`, mit 97
geaenderten Zeilen an 43 Aufrufstellen.

**Der Bauagent konnte nicht anders:** Die Datei rief an allen 43 Stellen den alten
Schreibzugriff auf, und Bedingung 2 verlangt, dass dieser Aufruf im ganzen Kernbaum
verschwindet. Ohne die Aenderung waere entweder Bedingung 2 gerissen oder der Bau rot. Der
Fehler liegt in der Paketbeschreibung, nicht im Lauf.

**Warum das gemeldet gehoert und nicht nur auffaellt:** Der Baulauf plant Pakete nur dann
gleichzeitig ein, wenn ihre Dateilisten sich nicht schneiden. Eine Datei, die ein Paket
anfasst, ohne sie zu nennen, ist genau die Luecke, gegen die diese Regel gebaut ist -- ein
zweites Paket auf `schranken_probe.cpp` haette parallel laufen duerfen.

**Und ein Nachtrag mit Wirkung fuer spaeter:** Die Hilfsfunktion, die dabei entstanden ist
(`schranken_probe.cpp:91`), bindet je Aufruf einen neuen Startwertzugang. Heute geht das
gut, weil keine der 43 Stellen `partie.runde` anfasst. Die erste Schranke, die einen
Randfall auf einem Zustand mit gelaufener Runde braucht, bricht damit ab -- mit einer
Meldung, die von einem echten Fehler nicht zu unterscheiden ist. Das ist keine
Beanstandung an 0027; es ist die Fussangel, die dort liegen bleibt, und sie gehoert in
denselben Rueckstand.

---

## Was ich sonst gesucht und **nicht** gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar ist:

- **Determinismus.** Kein Gleitkomma in den vier geaenderten Kerndateien, keine neue
  Iteration ueber eine streuende Menge, kein zweiter Zufallsstrom. Der Startwertzugang
  haelt einen rohen Zeiger -- er ist Werkzeug, kein Zustand, und keine Adresse gelangt in
  die 310 Groessen. Beide Bauprofile liefern dieselben gedruckten Pruefsummen.
- **Rueckkopplungen.** Dieses Paket aendert, *wer* schreiben darf, nicht *was* beim
  Schreiben geschieht. Die acht Kanaele und ihre Schranken sind unberuehrt: Im Schreiber
  aendert der Commit genau eine Anweisung und drei Kommentarzeilen.
- **Zustandsausgabe.** Byteform und Pruefsumme holen ihre Zahl jetzt ueber den Lesezugriff
  statt ueber das Feld. Beide Funktionen versprechen, nicht zu werfen, und der Lesezugriff
  kann abbrechen -- ich habe nachgesehen, ob damit ein Programmabbruch eingebaut wurde:
  Die Schleifengrenze *ist* die Feldzahl, die Indexpruefung kann nicht anschlagen. Der
  Bauagent nennt das im Kommentar; es stimmt.
- **Raender.** Den Platz von `partie.runde` habe ich von Hand nachgerechnet:
  `daten/adressen.md` Zeile 349 fuehrt ihn als laufende Nummer 307, der Kern zaehlt ab
  null, also 306 -- deckungsgleich mit der Zusicherung. Die Startwertspalte dort traegt
  null, deshalb traegt ein frischer Zustand die Null, an der der Riegel haengt. Ueberlauf,
  Division und Rundung kommen in diesem Paket nicht vor.

---

## Anhang -- die Ausgaben im Wortlaut

Ausfuehrlicher Testlauf `zustand_probe`, Profil RelWithDebInfo, eigener Bau. Jede Zeile
der Programmausgabe als Punkt:

- sizeof(Zustand) gleich 2480 Byte, 310 Felder
- Rundlauf Adresse zu Platz: 310 von 310 genau einmal
- Abbruch wie erwartet (Zeile 324): kern::zustand::lege_ab -- Index ausserhalb der 310 Felder
- Abbruch wie erwartet (Zeile 326): kern::zustand::lies -- Index ausserhalb der 310 Felder
- Abbruch wie erwartet (Zeile 327): kern::zustand::index_zu_adresse -- Index ausserhalb der 310 Felder
- Fehlerwert der Adresssuche: 310, gueltige Plaetze 0 bis 309
- Adressfunktionen decken 310 von 310 Plaetzen genau einmal
- Steckplaetze: 20 Adressen, 19 spielbar
- Nullzustand: Kette 01d663224c4054e5, Bytefolge 01d663224c4054e5, Potenz 01d663224c4054e5
- letztes Feld auf minus eins: a491e70cc3f70d5d
- Felder, die die Summe aendern: 310 von 310
- **Zaehlzustand (Feld i traegt i): 25e8b19071bea26c** -- die Zahl aus Befund 1, Schritt 4
- Abbruch wie erwartet (Zeile 696): kern::zustand::Startbelegung -- die Partie laeuft schon
  (partie.runde ist nicht null); Startwerte gibt es nur vor der ersten Runde
- Abbruch wie erwartet (Zeile 697): dieselbe Meldung, zweite Ausloesung
- Startwertzugang: vor Runde 1 offen, in Runde 12 verriegelt
- kern::zustand -- alle Proben bestanden.

Ausfuehrlicher Testlauf `schreiber_probe`, dasselbe Profil, die Zeilen, auf die sich
Bedingung 3 und Bedingung 4 stuetzen:

- lies_alt gleich 4711, lies_neu gleich 815 (erwartet 4711 und 815)
- Sollmaske weltlauf 175, spielmodus 310, Kettenkapazitaet 310
- Abbruch wie erwartet (Zeile 339): kern::schreiber -- Rundenende Runde 1: in der
  Sollmaske, aber nicht geschrieben: welt.preis.2 (Nr. 240)
- Abbruch wie erwartet (Zeile 350): kern::schreiber -- Rundenende Runde 1: ausserhalb der
  Sollmaske geschrieben: fonds.hebelstand (Nr. 256)
- Weltlauf: 175 Adressen geschrieben, Kette 175 Glieder (erwartet 175)
- Spielmodus: 310 Adressen geschrieben, Kette 310 Glieder (erwartet 310)
- Abbruch wie erwartet (Zeile 474): kern::zustand::Startbelegung -- die Partie laeuft
  schon (partie.runde ist nicht null); Startwerte gibt es nur vor der ersten Runde
- Startwert 1000000 ohne Ursachensatz: 0 Kettenglieder nennen ihn, Kette der Runde 175
  Glieder
- schreiber_probe: alle Pruefungen bestanden

Die vorletzte Zeile ist der Nachweis der **ersten** Haelfte von Bedingung 3 -- ein
Startwert erzeugt kein Kettenglied -- und sie ist sauber. Beanstandet ist die zweite
Haelfte.

---

## Berichtigung in eigener Sache

Zwei Schoenheitsfehler dieser Datei, die ich nicht mehr herausnehmen konnte, weil mir in
diesem Lauf nur das Anhaengen an eine Datei offenstand und kein Ersetzen:

1. Im Abschnitt zu Bedingung 1 steht der Satzanfang "Wortlaut des Uebersetzers" zweimal.
2. In der ersten Zeile der Meldungstabelle ist der Typ des Feldes als "std::array of long
   int, 310" wiedergegeben. Der Uebersetzer schreibt ihn in spitzen Klammern -- ein Feld
   von 310 Ganzzahlen zu acht Byte. An der Aussage aendert das nichts, aber ein Zitat ist
   ein Zitat, und ein veraendertes gehoert benannt.
