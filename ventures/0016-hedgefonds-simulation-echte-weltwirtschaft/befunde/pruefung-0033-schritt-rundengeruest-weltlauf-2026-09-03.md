---
typ: pruefung
paket: 0033-schritt-rundengeruest-weltlauf
pruefer: kern-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Die acht Abnahmebedingungen einzeln. 1 und 5 ueber Suchlaeufe, deren Muster ich vorher gegen einen echten Treffer gehalten habe; 2, 3, 4, 6 und 7 ueber einen eigenen Bau ausserhalb des Repos, den Testlauf des Pakets und eine eigene Gegenprobe, die die Sollmaske ein drittes Mal aus den Adresstexten bildet und die Pruefsumme mit eigener FNV-Schleife rechnet; 8 gegen den Uebersetzungsbericht des Tages.
befunde: 1
---

# 0033 -- alle acht Bedingungen halten; ein Befund an den Projektmanager

Das Paket baut den Rahmen der Runde: Signatur, Rueckgabewert, sechs benannte Schritte in
fester Reihenfolge, eine Runde, die jede der 175 Maskenadressen genau einmal unveraendert
vortraegt. Es rechnet nichts, und das ist sein erklaerter Zuschnitt.

## Was fremdgemessen ist und was ich selbst gemessen habe

**Fremdgemessen:** befunde/uebersetzung-2026-09-03.md, vom Baulauf erzeugt, ergebnis ok.
schritt_probe steht dort zweimal namentlich als Passed -- Zeile 60 (Testliste des
Arbeitsbereichs, Nr. 5 von 9) und Zeile 110 (Testliste des Kerns allein, Nr. 5 von 7).

**Selbst gemessen:**

- Frischer Bau **ausserhalb des Repos** gegen die Originalquellen, mit cmake auf das
  Quellverzeichnis des Kerns und ein Bauverzeichnis unter dem Temporaerpfad, Profil Debug.
  Gruen, keine einzige Warnung -- also mit dem vollen Warnsatz aus werkzeugkette.cmake
  samt Fehlerabbruch bei Warnung und mit den Sanitizern, denn die Proben binden
  kern_geprueft.
- Testlauf schritt_probe ueber das Testwerkzeug, ausfuehrlich: bestanden, volle Ausgabe im
  Anhang.
- **Dreimal in drei getrennten Prozessen** gelaufen: dieselben beiden Pruefsummen jedes
  Mal, bec587d71f6905ff und cedf8f3d65103b52.
- Eine **eigene Gegenprobe** als eigenes Bauprojekt, gegen dieselben Quellen mit Adress-
  und Verhaltenssanitizer. Sie geht andere Wege als die Probe des Pakets; was sie belegt
  und was nicht, steht im naechsten Abschnitt.
- Suchlaeufe fuer Bedingung 1 und 5, beide Muster vorher gegen einen echten Treffer
  gehalten.

**Der Baum ist unberuehrt.** Der Kurzstatus nennt nach meinem Lauf dieselben Dateien wie
davor. Mein Gegenprobenprojekt lag kurzzeitig unter bau/pruefer-gegenprobe/ und ist wieder
entfernt -- es musste weg, weil baulauf.py in Zeile 116 **jede** CMakeLists.txt unter dem
Venture einsammelt und ein liegengebliebenes Projekt den naechsten Uebersetzungsbericht rot
gefaerbt haette. Gegenprobe danach: unter dem Venture liegen wieder genau vier Manifeste,
also die Zahl, die der Bericht des Tages als manifeste 4 fuehrt.


## Die Gegenprobe -- was sie belegt und wo sie gestorben ist

Sie prueft dieselben Aussagen ueber andere Quellen:

- Die Sollmaske weltlauf wird ein **drittes** Mal gebildet -- aus den Adresstexten
  (index_zu_adresse), also aus daten/adressen.md, und nicht aus den
  stelle-Rechenvorschriften, aus denen sowohl schreiber.cpp als auch schritt.cpp ihre
  Fassung ziehen. Regel: alles unter restwelt, handel und welt.preis, drei der vier
  partie-Felder, und bei land die zwoelf Sektorfelder, die neun Aggregate, zustimmung,
  basiswechsel und die vier Instrumentenstaende.
- Die Pruefsumme rechnet eine **eigene** FNV-1a-64-Schleife mit den Konstanten aus RFC 9923
  ueber eine eigene Little-Endian-Zerlegung, ohne kern::pruefsumme und ohne
  zustand::nach_bytes.
- Vier Ausgangslagen statt zwei, darunter **alle 310 Felder auf I64_MIN** und **alle auf
  I64_MAX**, und eine zweite Runde auf dem Ergebnis der ersten.

**Sie ist an einem Fehler meiner eigenen Datei gestorben, nicht an einem des Pakets.** Der
Adress-Sanitizer nennt die Stelle: meine Hilfsfunktion liest den Meldungstext der Ausnahme,
nachdem der Fangblock verlassen ist, und der Text ist dann fort. Das trifft die letzten
beiden Abschnitte meiner Gegenprobe -- die Wortlautvergleiche zum spielmodus und die
Raender der Rundennummer.

**Was das fuer die Beweislage heisst, genau:** Meine Pruefroutine schreibt auf die
**ungepufferte** Standardfehlerausgabe. Vor dem Sanitizerbericht steht dort keine einzige
Zeile -- weder eine fehlgeschlagene Pruefung noch eine Maskenabweichung. Alles bis dorthin
ist damit durchgelaufen und bestanden: die dritte Maskenabschrift gegen die des Kerns,
adressweise ueber alle 310; die vier Ausgangslagen mit Kette, eigener Pruefsumme und
feldweisem Vergleich; die zwei Aufrufe auf derselben Lage; die zweite Runde. Dass der
spielmodus ueberhaupt abbricht, steht ebenfalls fest -- der Sanitizerbericht zeigt den
Aufrufweg, auf dem festkomma::abbruch aus kern::schritt::schritt heraus die Ausnahme baut.
Nicht belegt sind allein die **Wortlautvergleiche**, und die habe ich aus der Probe des
Pakets, die ihren Text noch im Fangblock ausgibt (Anhang).

Die Sanitizer sind damit nebenbei als scharf nachgewiesen: Sie haben in diesem Lauf einen
echten Speicherfehler gefunden -- meinen.

---


## Bedingung 1 -- Signatur -- erfuellt

schritt.hpp deklariert **eine** oeffentliche Funktion, schritt mit Zustand, Aktionsbuendel
und Modus (Zeile 98 bis 99). Daneben stehen zwei Typen und keine weitere Funktion. Sie
liefert **beides**: Rundenergebnis traegt neuer_zustand und kette_dieser_runde (Zeile 71
bis 77) -- die Kette also neben dem Zustand und nicht in ihm, wie T19 es verlangt. Ein
Zufallsargument gibt es nicht.

Der vorgeschriebene Suchlauf nach zufall ueber beide Dateien geht leer aus. **Das Muster
ist lebendig:** derselbe Ausdruck trifft im Kern 40-mal in vier Dateien -- zufall.hpp,
zufall.cpp, zufall_probe.cpp und kern.hpp. schritt.cpp bindet kern/zufall.hpp auch nicht
ein; sein Include-Block sind sieben Zeilen (37 bis 46).

Gegenrichtung aus dem Testlauf: Der Aufruf hat genau drei Argumente, und beide Rueckgaben
kommen an. Ein viertes gaebe es nicht zu uebergeben.

## Bedingung 2 -- Maskengroesse aus unabhaengiger Quelle -- erfuellt

Gedruckt: Sollmaske weltlauf gleich 175, spielmodus gleich 310. Gefragt ist kern::schreiber,
also der Kasten, der die Maske fuehrt, nicht kern::schritt.

Ich habe beide Zahlen **gegen die Vorgabe** gehalten statt gegen den Code: technik.md
Zeile 928 bis 942 fuehrt die Blocktabelle und rechnet nach -- 108 plus 22 plus 40 plus 2
plus 3 gleich 175 in der Maske, 68 plus 12 plus 2 plus 52 plus 1 gleich 135 ausserhalb,
zusammen 310; die Maske spielmodus umfasst alle 310. Deckungsgleich.

Meine Gegenprobe bildet die Maske ein drittes Mal aus den Adresstexten und zaehlt ebenfalls
175, mit **null** Abweichungen gegen das Bitfeld des Kerns, adressweise geprueft. Damit
sind es drei voneinander unabhaengige Abschriften derselben Tabelle: nach Bloecken in
schreiber.cpp, nach Schritten in schritt.cpp, nach Namen in meiner.

## Bedingung 3 -- eine Runde laeuft durch -- erfuellt

Der Aufruf im Modus Weltlauf kehrt zurueck. Belegt auf sechs Ausgangslagen: die zwei der
Probe -- Musterwerte mit partie.runde gleich 0 und gleich I64_MAX minus eins -- und vier
eigene, darunter **alle 310 Felder auf I64_MIN** und **alle auf I64_MAX**. Alle unter
Adress- und Verhaltenssanitizer ohne Meldung.

Der zurueckgekehrte Aufruf ist der Nachweis, dass die zweiseitige Rundenendpruefung aus T38
gehalten hat: Sie bricht hart ab, wenn eine Maskenadresse fehlt oder eine ausserhalb
beruehrt wurde, und schritt holt den Zustand ausschliesslich aus ihr (schritt.cpp Zeile 536).


## Bedingung 4 -- 175 Glieder, jedes ein Vortrag -- erfuellt

Die Probe des Pakets prueft alle geforderten Aussagen und dazu die Gegenrichtung -- jede
Maskenadresse kommt in der Kette vor. Meine Gegenprobe prueft dieselben Aussagen noch
einmal und stellt die Ziele gegen die **textabgeleitete** Maske:

- 175 Glieder,
- jedes traegt die Ursachenform Vortrag, und die Vortragsadresse ist die eigene Zieladresse,
- verzoegerung gleich 0, beitrag gleich 1000, alt gleich neu,
- Ziele echt aufsteigend, damit paarweise verschieden,
- kein Ziel doppelt, keine Maskenadresse fehlend, keine ausserhalb der Maske,
- runde an jedem Glied gleich partie.runde der Vorrunde plus eins.

Zusammen mit aufsteigend und paarweise verschieden und der Laenge ist die Kette damit
**genau** die Maske und nicht 175 beliebige Adressen, die zufaellig in ihr liegen.

## Bedingung 5 -- der Schreibweg ist der einzige -- erfuellt

Der vorgeschriebene Suchlauf ueber schritt.cpp geht leer aus. **Das Muster ist lebendig:**
derselbe Ausdruck trifft im Venture neunmal, unter anderem genau die beiden Formen, gegen
die er gebaut ist -- der indizierte Feldzugriff auf den Zustand und der Aufruf des alten
Schreibzugriffs. Alle neun Treffer stehen in Prosa, also in Aufgaben- und Befunddateien; in
**keiner** Quell- oder Kopfdatei des Ventures trifft er.

Der zweite, staerkere Nachweis liegt seit Paket 0027 im Uebersetzer: Das Feld und der rohe
Schreibzugriff des Zustands sind privat, und kern::schritt ist kein Freund. Ein
Schreibzugriff am Schreiber vorbei waere in dieser Datei nicht bloss ungeprueft, sondern
nicht uebersetzbar.

## Bedingung 6 -- die Pruefsumme aendert sich nicht -- erfuellt

Gedruckt, auf beiden Lagen der Probe: Vorrunde 0 auf Runde 1 mit bec587d71f6905ff vorher
und nachher, und Vorrunde 9223372036854775806 auf Runde 9223372036854775807 mit
cedf8f3d65103b52 in beiden Richtungen.

Ich habe die Aussage auf **drei** Wegen abgestuetzt, weil eine Summengleichheit allein ein
Zusammenstoss sein koennte:

1. Die Byteform aus zustand::nach_bytes mit pruefsumme::fnv1a64 gegen
   zustand::pruefsumme_von -- zwei Rechenwege, dieselbe Zahl.
2. Meine eigene FNV-Schleife mit den Konstanten aus RFC 9923 kommt auf dieselbe Zahl wie
   pruefsumme_von, auf allen vier meiner Ausgangslagen.
3. Feldweise: null abweichende Felder von 310, auf allen vier Lagen.

## Bedingung 7 -- der spielmodus bricht ab, und die Meldung sagt warum -- erfuellt

Der Abbruch tritt ein. Der Wortlaut nennt beides, was die Bedingung verlangt: dass die
Sollmaske spielmodus **alle 310 Adressen** umfasst, und dass die Schritte **2 (Aktionen)
und 6 (Abrechnung) noch kein Paket** haben. Er nennt zusaetzlich den Grund, den die
Bedingung selbst gibt -- ein stilles Vortragen aller 310 waere eine Falschaussage. Der
Wortlaut steht im Anhang.

Bemerkenswert und richtig gebaut: Auch die beiden entfallenden Schritte haben einen Rumpf,
und der Rumpf ist ein Abbruch statt eines leeren Blocks (schritt.cpp Zeile 358 bis 366 und
409 bis 416). Eine Adresse, die dort ankaeme, bedeutete, dass Zuordnungstafel und Sollmaske
auseinanderlaufen; ein leerer Rumpf haette sie verschluckt.

## Bedingung 8 -- namentlich im Uebersetzungsbericht -- erfuellt

befunde/uebersetzung-2026-09-03.md, Zeile 60 und Zeile 110, beide Passed. Die Datei
kern/CMakeLists.txt ist vom Paket nicht angefasst worden -- es hat sich also wirklich auf
das Einsammeln verlassen und nicht am Bauskript nachgeholfen.

---


# Befund 1 -- die Arbeit von 0033 liegt in einem Commit, der 0027 heisst

**Bricht keine Abnahmebedingung. Geht an den Projektmanager.**

Der Commit 00d6f21 traegt den Betreff kernbauer 0027-zustand-schreibweg-schliessen mit
funf Dateien und enthaelt die **drei Dateien von 0033** -- schritt.hpp, schritt.cpp und
schritt_probe.cpp --, dazu die Statuszeile der Aufgabendatei 0033 und den neuen Vorschlag
0038. Kein Byte von 0027 steht darin; das echte 0027 ist 6df9a3b, Lauf 286.

Der Commit, der 0033 im Betreff nennt, ist f4b2d61, Lauf 295 -- und er enthaelt **nur** das
Logbuch des Kernbauers, keine Quelle.

**So findet man es wieder:** Eine Suche im Commit-Betreff nach 0033 liefert einen Commit
ohne Quelltext; eine Suche ueber den Pfad von kern/src/schritt.cpp liefert einen Commit,
dessen Betreff ein anderes Paket nennt. Wer in drei Monaten fragt, woher kern::schritt
kommt, findet ueber beide Wege die falsche Antwort.

**Die Ursache liegt im Werkzeug, nicht beim Bauagenten.** lauf.py bildet in Zeile 381 den
Betreff aus dem Gegenstand *des Laufs*, und die Commit-Funktion nimmt **ganze
Verzeichnisse**, nicht einzelne Dateien -- die Datei selbst nennt diese Folge in ihrem
Kommentar in Zeile 336 bis 337. Zwei Laeufe waren gleichzeitig offen: Lauf 294 auf 0027 und
Lauf 295 auf 0033. Lauf 294 hat die schon geschriebenen Dateien von 0033 mitgenommen, Lauf
295 fand nur noch sein Logbuch vor.

**Was ich ausdruecklich nicht beanstande:** Die Dateiliste von 0033 ist eingehalten. Der
Bauagent hat genau die drei genannten Dateien angefasst; die Statuszeile der eigenen
Aufgabendatei und ein Vorschlag daneben sind vorgesehen. Und der Kollisionsschutz hat
gehalten -- 0027 hielt zustand, schreiber und schranken_probe, 0033 nur schritt, die Listen
schneiden sich nicht. Serialisiert wurden die **Dateien**; gemischt hat der **Commit**.

**Kein Arbeitspaket von mir dazu.** Die Behebung liegt in agents/lauf.py, also ausserhalb
dieses Ventures; ein Paket unter dem Aufgabenverzeichnis waere der falsche Ort. Zustaendig
ist der Projektmanager oder der Verbesserer.

---


## Die vier Fragen meiner Rolle

**Determinismus.** Kein Gleitkomma -- sperre.hpp steht als letzte Zeile des Include-Blocks
(schritt.cpp Zeile 46) und vergiftet float und double ab dort. Keine streuende Menge: die
aeussere Schleife ist die aufsteigende Adressrunde von 0 bis 309, die Zuordnungstafel ein
zur Uebersetzungszeit gebautes Feld fester Groesse, jede Aufzaehlung ausgeschrieben. Kein
Zufallsstrom, kein Zufallsargument, kein Einbinden von zufall.hpp. Keine Sortierung, keine
ungeordnete Zuordnung. Keine Zeit- und keine Speicheradresse gelangt in ein Ergebnis -- die
Kette traegt Adressen im Sinne von T17, also Zahlen von 0 bis 309, keine Zeiger. Gemessen:
dieselben Pruefsummen in drei getrennten Prozessen, und zwei Aufrufe auf derselben Lage
liefern bis zum letzten Kettenglied dasselbe.

**Rueckkopplungen.** Dieses Paket rechnet nichts, es gibt hier also keine Schleife, in der
Erfolg mehr Erfolg erzeugt. Die **Schranken** sind trotzdem schon da und wirksam, und das
ist der eigentliche Inhalt des Rahmens: Der zweite Schreibzugriff auf dieselbe Adresse
stirbt im Schreiber -- dort stirbt jede Rueckkopplung *innerhalb* einer Runde, statt als
neunter Kanal zu entstehen. Der Lesezugriff auf eine noch ungeschriebene Adresse stirbt
ebenso, und das macht die Zyklenfreiheit der sechs Schritte zu einer Eigenschaft, die jeder
Lauf nachweist. Die zweiseitige Maskenpruefung am Rundenende schliesst den Kreis. Die fuenf
Gegenkraefte aus spiel.md sind **nicht** eingebaut -- im weltlauf laufen nach T38 nur
Zustimmung und Regierungswechsel, und der Regierungswechsel schreibt nichts. Das ist der
Zuschnitt und keine fehlende Schranke.

**Zustandsausgabe.** Aus der Ausgabe allein laesst sich erkennen, ob richtig gerechnet
wurde -- und zwar hier schaerfer als spaeter: alt gleich neu an jedem der 175 Glieder ist
genau die Aussage, dass nichts gerechnet wurde, und sie ist pruefbar, statt nur behauptet
zu sein. Die drei Ebenen aus T20 gehoeren nach T13 der schnittstelle; der Kern liefert
ihnen, was sie brauchen: den vollstaendigen Zustand und die Kette mit Ursache, Verzoegerung
und Beitrag je Schreibzugriff. Es fehlt keine Groesse, die die Abnahme nennt.

**Raender.** In diesem Modul wird auf Zustandswerten **nicht gerechnet**: der Vortrag legt
den gelesenen Altwert unveraendert wieder hin. Kein Ueberlauf, keine Division, keine
Rundung, keine Summe ueber tausend Runden -- deshalb gehen I64_MIN und I64_MAX in allen 310
Feldern unveraendert durch, von mir gemessen. Die **einzige** Rechnung ist die
Vorrundennummer plus eins, und beide Enden sind **vor** der Addition abgefangen. Von Hand
nachgerechnet und im Lauf bestaetigt:

- minus eins und I64_MIN ergeben den Abbruch, dass es eine Runde vor der ersten nicht gibt,
- I64_MAX ergibt den Abbruch, dass sich eine naechste Runde nicht mehr zaehlen laesst,
- I64_MAX minus eins ergibt die Rundennummer I64_MAX, an allen 175 Kettengliedern gedruckt,
- null ergibt die Rundennummer eins.

Damit ist die offene Faehrte aus meinem Logbuch vom 2026-09-02 fuer dieses Paket
gegenstandslos: Ob die Umbruchsemantik den Sanitizertest auf vorzeichenbehafteten Ueberlauf
abschaltet, spielt hier keine Rolle, weil der Ueberlauf **verhindert** und nicht
nachtraeglich erkannt wird. Der Quelltext begruendet genau das an Ort und Stelle
(schritt.cpp Zeile 487 bis 495). Fuer andere Kernpakete bleibt die Frage offen.


## Zwei Beobachtungen, beide **kein** Befund

**Die Runde zaehlt nicht hoch, und eine zweite Runde traegt dieselbe Nummer.** Die Kette
sagt Runde N plus eins, partie.runde im Zustand sagt weiter N. Ich habe zwei Runden
hintereinander gerechnet: Die zweite meldet dieselbe Nummer wie die erste, und der Zustand
ist danach wieder der Ausgangszustand. Das ist **kein** Befund -- Bedingung 6 verlangt die
unveraenderte Pruefsumme und erzwingt damit genau dieses Verhalten, und das Paket schreibt
es zweimal ausdruecklich hin. Ich halte es fest, damit niemand eine Rundenschleife auf den
heutigen Rahmen setzt und sich wundert, dass sie stehenbleibt, ohne abzubrechen. Wer den
Schritt 1 baut, zieht die Zahl nach -- das Paket sagt es an der richtigen Stelle
(schritt.cpp Zeile 338 bis 343).

**Eine Kommentarzeile rechnet falsch.** schritt.cpp Zeile 223 bis 224 schreibt 27 mal 4
gleich 88 minus die vier Zustimmungen. 27 mal 4 ist 108, und 88 kommt heraus, nachdem
sowohl die vier Zustimmungen als auch die sechzehn Instrumentenstaende abgezogen sind. Die
Zahl 88 ist richtig, der Weg dorthin ist im Satz falsch wiedergegeben. Kein Befund: Direkt
darunter steht die Zusicherung ueber 4 mal (12 plus 9 plus 1) plus 22 plus 40 plus 2 gleich
152, die beim Uebersetzen laeuft und die richtige Rechnung fuehrt.

## Was ich sonst gesucht und **nicht** gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar ist:

- Keine Umdeutung eines Zeigertyps, kein Wegwerfen einer Unveraenderlichkeit, keine eigene
  Speicherzuteilung, kein Maschinencode, keine ungeordnete Zuordnung, keine Sortierung, kein
  blockweises Speicherkopieren, keine Ueberlagerung zweier Typen, kein float und kein double
  in schritt.cpp. Suchlauf leer.
- Kein Fall im Schrittschalter ohne Behandlung: Die Verteilung auf die sechs Schritte hat
  **keinen** Auffangzweig, damit ein siebter Schritt ein Bauabbruch statt einer stillen
  Auslassung ist. Mit dem Warnsatz und dem Fehlerabbruch bei Warnung ist das wirksam.
- Kein Zeiger auf einen Zwischenwert: Die Rundenendabfrage gibt eine Referenz auf den
  Zustand des Schreibers heraus, und schritt **kopiert** sie in das Ergebnis (Zeile 536 bis
  537), bevor der Schreiber endet. Der Adress-Sanitizer haette es sonst gemeldet -- er hat
  in diesem Lauf bewiesen, dass er hinsieht.
- Keine Datei ausserhalb der Liste dateien angefasst; und kein Status offen, den der
  Bauagent selbst gesetzt haette -- der Vorschlag 0038 stand bei seiner Entstehung auf
  vorschlag, wie es die Regel verlangt, und wurde erst danach hochgestuft.

---


## Anhang -- die Ausgabe des Testlaufs im Wortlaut

Ausfuehrlicher Testlauf schritt_probe, eigener Bau ausserhalb des Repos, Profil Debug, jede
Zeile der Programmausgabe als Punkt:

- Sollmaske weltlauf gleich 175, spielmodus gleich 310 (erwartet 175 und 310)
- Vorrunde 0 auf Runde 1: Pruefsumme bec587d71f6905ff vorher, bec587d71f6905ff nachher
- Kette: 175 Glieder (erwartet 175), Runde 1 an jedem Glied
- Vorrunde 9223372036854775806 auf Runde 9223372036854775807: Pruefsumme cedf8f3d65103b52
  vorher, cedf8f3d65103b52 nachher
- Kette: 175 Glieder (erwartet 175), Runde 9223372036854775807 an jedem Glied
- Abbruch wie erwartet: kern::schritt -- der Modus spielmodus ist in diesem Rahmen nicht
  gebaut: seine Sollmaske umfasst alle 310 Adressen, und die Schritte 2 (Aktionen) und 6
  (Abrechnung) haben noch kein Paket. Ein stilles Vortragen aller 310 waere eine
  Falschaussage -- es saehe aus wie eine gerechnete Spielrunde und waere keine
- Abbruch wie erwartet (partie.runde gleich minus eins): kern::schritt -- partie.runde der
  Vorrunde ist negativ: eine Runde vor der ersten gibt es nicht
- Abbruch wie erwartet (partie.runde gleich minus 9223372036854775808): dieselbe Meldung
- Abbruch wie erwartet (partie.runde gleich 9223372036854775807): kern::schritt --
  partie.runde der Vorrunde ist der groesste int64_t: eine naechste Runde laesst sich nicht
  mehr zaehlen
- schritt_probe: alle Pruefungen bestanden

Der zweite und der dritte Lauf desselben Programms haben Zeile fuer Zeile dasselbe
ausgegeben; die beiden Pruefsummen sind in allen drei Laeufen gleich.

## Berichtigung in eigener Sache

Im Abschnitt zu Befund 1 steht in der ersten Zeile funf statt fuenf. Mir stand in diesem
Lauf nur das Anhaengen an eine Datei offen und kein Ersetzen, deshalb bleibt der Tippfehler
stehen und wird hier benannt. An der Aussage aendert er nichts: Der Betreff des Commits
00d6f21 nennt fuenf Dateien.

