---
typ: pruefung
paket: 0155-werte-konstantenkopf-zwei-jahrgangskonstanten
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Bedingungen einzeln und mechanisch -- Bedingung 1 ueber grep plus zwei unabhaengige Feldzaehlungen, gegengehalten an T23 Punkt 5, T27 und parameter.toml; Bedingung 2 ueber ctest in beiden Profilen, einen zeichengleichen Vorkompilat-Vergleich mit Positivkontrolle und ein diff -rq zweier aus git archive hergestellter Baeume.
befunde: 1
---

# Der Kopf zaehlt jetzt zwei, und es sind zwei

## Stand, Gegenstand, Pruefweg

Gemessen am Stand **8ff7cc4**. Die Arbeit des Pakets liegt in **14d0dcb**
(kernbauer: 0155-... (2 Dateien), 2026-09-06 03:32:54), gefunden ueber
git log -- <datei> und nicht ueber den Commit-Betreff.

Geprueft wurde kern/include/kern/werte.hpp, md5 **99e0475d552f4ff6306cc25492223fbe**
am Anfang **und** am Ende des Laufs, 492 Zeilen. Der Vorherstand ist 14d0dcb^,
md5 1d65eaa910d63a39615393b4536fafa4; er wurde nicht zitiert, sondern mit
git show 14d0dcb^:<pfad> selbst hergestellt.

**Zuwachs waehrend des Laufs.** Nach 8ff7cc4 sind e2588cc, 29de6f0 und d103906
dazugekommen (daten-pruefer, kern-pruefer). Ein diff --stat 8ff7cc4 d103906 ueber
kern/, CMakeLists.txt, werkzeugkette.cmake und parameter.toml ist **leer** -- die
Messungen unten gelten am Endstand unveraendert. Zwischen 14d0dcb und 8ff7cc4 haben
fremde Pakete verlauf, zustandsausgabe und kern/src/werte.cpp geaendert,
**werte.hpp aber keines**; das Paket ist damit an seiner eigenen Datei isoliert.

---

## Bedingung 1 -- der Kopf nennt keine andere Zahl als die gezaehlte

**Erfuellt.**

grep -n "Jahrgangskonstante" kern/include/kern/werte.hpp liefert drei Stellen:

    15:  //! ... noch ein Parameterschluessel noch eine Jahrgangskonstante noch
    73:  /// Die Kalibrierwerte und die zwei Jahrgangskonstanten, die in den Formeln aus T47
   139:  /// **Die zweite Jahrgangskonstante dieses Traegers**, aus demselben Grund wie

Zeile 15 nennt keine Zahl (Aufzaehlung der Namensarten, Singular als Gattung).
Zeile 73 nennt **zwei**, Zeile 139 nennt die **zweite**. Keine dritte Stelle, kein
Widerspruch.

**Die Gegenprobe, erste Zaehlung** -- grep -n "Jahrgang" ueber dieselbe Datei gibt neun
Stellen. Als Groesse des Jahrgangs ausgewiesen sind genau zwei Felder:

| Feld | Zeile | Wortlaut, der es ausweist |
|---|---|---|
| leitzins_start | 130--131 | steht ... nach T27 nicht in parameter.toml, sondern im Jahrgang ... (T23 Punkt 5) |
| durchgriff | 139--141 | nach T23 Punkt 5 eine Groesse des Jahrgangs |

Die neunte Stelle (Zeile 403, durchgriff kommt aus Konstanten und ist eine Groesse des
Jahrgangs) nachgelesen: Sie nennt **dasselbe** Feld noch einmal im Kommentar zu
preishub_zoll und ist kein drittes. Zaehlung: **zwei**.

**Zweite, unabhaengige Zaehlung** ueber die Deklarationen statt ueber die Kommentare:

     96: struct Konstanten {
     99: stufenweite    103: ausstiegsabschlag   107: aufschlag
    111: lobbykosten    115: gegenlobby_satz     125: regulierung_last
    134: std::array<..., LAENDER> leitzins_start
    152/153: std::array<std::array<..., SEKTOREN_HANDELBAR>, GEBIETE> durchgriff
    154: };

Acht Felder, sechs davon mit "Schluessel <name> -- T5 Klasse n" ueberschrieben, zwei
ohne. Beide Zaehlungen ergeben **zwei**; der Kopf sagt zwei.

**Gegen die Vorgabe gehalten**, nicht nur gegen die Datei:

- specs/.../technik.md Zeile 1500--1502, **T23 Punkt 5**: "Konstanten des Jahrgangs:
  **vierzehn Werte** -- durchgriff[Gebiet][handelbarer Sektor], also zehn ..., und
  **leitzins_start[l]**, vier". 10 + 4 sind 14, genau diese zwei Groessen, keine dritte.
- **T27** (Zeile 1815--1830) fuehrt stufenweite, ausstiegsabschlag, aufschlag,
  lobbykosten und gegenlobby_satz in seiner Tabelle; regulierung_last steht als
  Parameterschluessel nach T27 in Zeile 2172, 2212 und 3243. Alle sechs sind gedeckt.
  T27 Zeile 1828 sagt zusaetzlich ausdruecklich, leitzins_start stehe **nicht** dort.
- parameter.toml gegengeprueft: Die sechs stehen als echte Schluessel darin (Zeilen 285,
  308, 342, 358, 385, 954). leitzins_start und durchgriff kommen darin **nur** in den
  Zeilen 246 und 248 vor -- und dort in dem Kommentar, der sie ausnimmt. Das ist genau
  die Aussage, die der neue Kopftext macht.

---

## Bedingung 2 -- Bestand gruen, Struktur unberuehrt

**Erfuellt.** Vier Nachweise, jeder mit eigenem Aufruf.

**(a) ctest, beide Profile.** Je ein frisches Bauverzeichnis unter bau/ (kp0155-san,
kp0155-off), CMAKE_BUILD_TYPE RelWithDebInfo:

    FABRIK_SANITIZER ON    100% tests passed, 0 tests failed out of 18   (12,08 s)
    FABRIK_SANITIZER OFF   100% tests passed, 0 tests failed out of 18   ( 6,32 s)

Die Namensliste beider Laeufe ist zeichengleich (diff leer). Beide Uebersetzungslaeufe
enthalten null Zeilen mit warning oder error.

**(b) Die drei Riegel, Code 0.** Belegstellen-, Bezeichner- und Schlussriegelwaechter
haengen als add_test und sind in den 18 oben enthalten (Nr. 16, 17, 18, alle Passed).
Sperrebindungsriegel und Warnsatz-Schlussriegel laufen beim Konfigurieren:

    Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft
    Warnsatz-Schlussriegel, Profil ON  (wahr):   22 Ziele, 388 Schaltereintraege
    Warnsatz-Schlussriegel, Profil OFF (falsch): 20 Ziele, 340 Schaltereintraege

Die 22/20 sind gegen die Kommentarzeilen werkzeugkette.cmake 1049--1050 gehalten
(19/17, gemessen am 2026-09-05 am Stand 8a2c381): Der Abstand ist in beiden Profilen +3
und erklaert sich aus den seither zugewachsenen Zielen. Das ist der Vergleich, den jene
Datei selbst erlaubt -- gegen den eigenen vorhergehenden Stand **desselben Profils**.

**(c) Kein Feld und keine Deklaration hat sich geaendert -- zeichengleiches Vorkompilat.**
Der staerkste der vier Nachweise, weil er nicht auf Augenschein beruht: Der Praeprozessor
wirft Kommentare weg. Ist das Ergebnis vor und nach der Aenderung Byte fuer Byte gleich,
war die Aenderung ausschliesslich Kommentar.

Der Uebersetzer wurde zweimal nur als Praeprozessor gerufen (Schalter -P und -E, C++20,
Suchpfad kern/include): einmal auf die heutige Fassung, einmal auf die Fassung aus
14d0dcb^, die dazu in einem vorgeschalteten Suchpfad lag. Ergebnis:

    diff vorher.i nachher.i    leer
    md5 beide                  924aeba828d5b533753a44fda63fb3ff, je 15.003 Zeilen

**Positivkontrolle, damit das Leere etwas heisst.** Derselbe Vergleich gegen einen
Mutanten, dem genau die Zeile 125 fehlt (das Feld regulierung_last), zusammengesetzt aus
head -n 124 und tail -n +126:

    diff nachher.i mutant.i
    14953d14952
    <     zustand::i64 regulierung_last (Vorbelegung null)

Der Apparat sieht ein entferntes Feld also. Sein Schweigen beim echten Vergleich ist ein
Ergebnis und kein Ausfall.

**(d) Ausserhalb dieser Datei null geaenderte Zeilen.** Zwei Baeume aus git archive
(14d0dcb^ und 14d0dcb, befunde/ ausgelassen), danebengelegt:

    diff -rq <vorher-baum> <nachher-baum>
    Files .../aufgaben/0155-werte-konstantenkopf-zwei-jahrgangskonstanten.md ... differ
    Files .../kern/include/kern/werte.hpp ... differ

Genau zwei Unterschiede. Der zweite ist der Gegenstand; der erste ist die eine
status-Zeile des eigenen Pakets (offen wird gebaut). Gegen die beiden vorhergehenden
Baulaeufe derselben Rolle gehalten -- e0682a1 (0151) und 5bb5375 (0152) -- tun beide
dasselbe. Das ist die stehende Form und kein Verstoss.

Der Wortlaut der Aenderung an werte.hpp: zwei Kommentarzeilen fort, sieben dazu, netto
plus fuenf. Keine Zeile ohne den Vorsatz aus drei Schraegstrichen.

**Die Behauptungen des neuen Textes selbst nachgefahren** -- ein Kommentar, der etwas
zusichert, ist ein Pruefauftrag:

| Behauptung | geprueft an | Ergebnis |
|---|---|---|
| Die zwei sind leitzins_start und durchgriff | Struktur und T23 Punkt 5 | stimmt |
| beide nach T23 Punkt 5 eine Groesse des Jahrgangs | technik.md 1500--1502 | stimmt |
| warum sie nicht in parameter.toml stehen, sagt der Kommentar an den beiden Feldern | Zeilen 129--131 und 139--143 | beide sagen es |
| Die uebrigen sechs Felder sind Parameterschluessel nach T27 | Struktur, T27, parameter.toml | stimmt heute, siehe Befund 1 |

**Der Bezeichnerriegel liest die neuen Zeilen wirklich** -- sonst waere sein Gruen zu
diesem Paket ohne Aussage. Derselbe Riegel, zweimal auf die beiden Baeume aus (d):

    vorher:   6838 Kommentarzeilen ... 1050 geprueft, 1003 aufgeloest, 47 uebergangen
    nachher:  6843 Kommentarzeilen ... 1052 geprueft, 1005 aufgeloest, 47 uebergangen

Plus fuenf Kommentarzeilen -- genau der Netto-Zuwachs des Diffs. Plus zwei geprueft und
plus zwei aufgeloest bei **drei** neuen Rueckwaerts-Anfuehrungen im Text; der Rest ist
erklaerbar und deshalb ein Beleg statt einer Luecke: ist_bezeichner()
(bezeichner_riegel.cpp 493--530) laesst nur Namenszeichen und den doppelten Doppelpunkt
zu, parameter.toml scheitert am Punkt und wird gar nicht erst Kandidat. Die uebergangenen
47 bleiben unveraendert, der Riegel bleibt gruen.

---

## Die vier Fragen meiner Rolle

Fuer dieses Paket beantwortet sie **(c)** oben zusammen, und zwar abschliessend: Das
Vorkompilat ist vor und nach der Aenderung zeichengleich. Die uebersetzte
Uebersetzungseinheit ist damit **bitgleich dieselbe** wie vorher -- an Determinismus,
Rueckkopplungen, Zustandsausgabe und Randverhalten hat sich nichts geaendert, und es kann
sich nichts geaendert haben. Ich habe das nicht angenommen, sondern gemessen.

Zusaetzlich am Quelltext nachgesehen, weil ein Profilvergleich hier nichts hergibt (die
Probe schweigt, wenn sie gruen ist -- werte_probe liefert in beiden Profilen null Zeilen,
diff leer): Eine Suche nach double, float, Dezimalliteralen und Exponentialschreibweise
ueber werte.hpp findet **nichts**. Die Struktur ist durchgehend zustand::i64 und
std::array fester Groesse -- geordnete Iteration, kein streuender Behaelter.

---

## Befund 1 -- der neue Text nennt eine Feldzahl, die der Auftrag ausgeschlossen hatte

**Kein zurueck.** Er beruehrt keine der beiden Abnahmebedingungen. Er geht an den
Projektmanager, weil es eine Frage des Zuschnitts ist und nicht des Ergebnisses.

Der Auftrag sagt in aufgaben/0155-...md Zeile 84--86:

> **Was ausdruecklich nicht dazugehoert:** die Zahl der Felder insgesamt, die Zahlwoerter
> aus T48 (0152) und jede Aenderung an der Struktur selbst.

Gebaut wurde als letzter Satz des neuen Absatzes (werte.hpp Zeile 78--79):

> Die uebrigen sechs Felder sind Parameterschluessel nach T27.

"Die uebrigen sechs" ist die Gesamtzahl minus zwei und sagt damit dieselbe Sache wie
"acht Felder". Die Aussage ist heute **richtig** -- ich habe sie oben zweimal nachgezaehlt
und gegen T27 und parameter.toml gehalten --, aber sie ist die Sorte Satz, deretwegen es
dieses Paket ueberhaupt gibt: Der berichtigte Satz war ebenfalls richtig, als 0002 ihn
schrieb, und wurde falsch, als 0152 ein sechstes Schluesselfeld (regulierung_last) in
dieselbe Struktur legte.

**Der Schaden ist nicht heute, sondern gemessen wahrscheinlich.** T27 fuehrt mehr
Schluessel, als Konstanten heute traegt; zwangsabschlag etwa steht bereits in werte.hpp
Zeile 325 als Parameterschluessel im Kommentar, ohne Feld in dieser Struktur.
technik.md Zeile 3243 zeigt am Beispiel regulierung_last, auf welchem Weg ein Schluessel
hier landet. Das naechste Feld macht "sechs" falsch, und niemand wird es merken: Weder
der Belegstellen- noch der Bezeichnerriegel prueft Zahlwoerter.

**Warum ich daraus trotzdem kein eigenes Paket schreibe.** Meine Regel lautet: kein
Vorschlag ohne belegten Schaden. Der Satz ist heute wahr, kein offenes Paket plant ein
weiteres Feld, und ein Paket, das ein Zahlwort in einem korrekten Kommentar streicht,
waere teurer als die Zeile wert ist. Der billige Ort ist die naechste Aenderung an
Konstanten: **Wer das naechste Feld einlegt, streicht dabei das Zahlwort**, statt es
nachzuziehen. Ob das als Auflage in ein kuenftiges Paket gehoert, entscheidet der
Projektmanager -- nicht ich, und nicht der Bauagent.

---

## Wonach ich sonst gesucht und nichts gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Ein drittes Feld mit Jahrgangs-Eigenschaft.** Neun Jahrgang-Stellen einzeln
  nachgelesen, darunter die entfernte in Zeile 403. Keins.
- **Ein zweites stehengebliebenes Zahlwort in derselben Datei.** "Die zweiundzwanzig
  Groessen aus T48" (Zeile 157, aus 0152) nachgezaehlt: Eine Suche nach "T48 Nr." gibt
  Nr. 1 bis 22 mit Nr. 11 zweimal, eine Zaehlung der nodiscard-Deklarationen gibt 23.
  23 Deklarationen fuer 22 Groessen -- genau das, was Zeile 250 ("Zwei Stelligkeiten und
  eine Groesse") und technik.md Zeile 17 ("22 Funktionen des Zustands im Kern") sagen.
  Stimmt.
- **Ein Widerspruch zwischen Auftrag und Vorgabe.** T23 Punkt 5, T27 und parameter.toml
  sagen alle dasselbe wie das Paket. Keiner.
- **Eine Aenderung ausserhalb der dateien-Liste.** diff -rq ueber zwei Baeume: keine
  ausser der eigenen status-Zeile.
- **Ein Riegel, der nur scheinbar gruen ist.** Bezeichnerriegel A/B gefahren (oben), sein
  Zaehlwerk reagiert auf genau diese fuenf Zeilen.

**Nicht gelesen**, und zwar mit Absicht: notizen/kernbauer.md und befunde/messung-0155/.
Der Nachweis oben ist vollstaendig selbst gefahren.

**Nicht geprueft, weil kein Werkzeug dafuer besteht:** dass die T-Block-Nummern im
Kommentar (T23 Punkt 5, T27, T47, T48) auf die gemeinten Absaetze zeigen, haelt kein
Riegel -- der Belegstellenriegel prueft Zeilennummern und Abschnittszitate, nicht
T-Nummern. Ich habe alle vier von Hand in technik.md nachgeschlagen; ein kuenftiger Lauf
muss das wieder tun.

## Aufrufe, zum Nachfahren

Aus ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/, alle Ausgaben unter bau/
(dort ausgelassen von .gitignore und von beiden Riegeln):

    cmake -S . -B bau/kp0155-san -DCMAKE_BUILD_TYPE:STRING RelWithDebInfo, dazu
        -DFABRIK_SANITIZER ON; dasselbe mit OFF nach bau/kp0155-off
    cmake --build bau/kp0155-san --parallel
    ctest --test-dir bau/kp0155-san --output-on-failure
    git show 14d0dcb^:<pfad>/werte.hpp in bau/kp0155-vorher-werte.hpp
    Praeprozessorlauf mit -P -E auf beide Fassungen, dann diff und md5
    git archive -o bau/kp0155-v.tar 14d0dcb^ ventures/0016-...
    tar -xf bau/kp0155-v.tar -C bau/kp0155-baum-v --exclude der befunde
    bau/kp0155-san/werkzeuge/bezeichner/bezeichner_riegel <baum>/ventures/0016-...

Die Protokolle beider Bauprofile, beider Riegellaeufe und der drei Vorkompilate liegen
unter bau/ mit dem Vorsatz kp0155-.

---

## Nachtrag zu Befund 1 -- Paket 0180 steht schon offen und deckt genau diese Stelle nicht

Nach dem Schreiben von Befund 1 gefunden, mit einem Suchlauf ueber aufgaben/:
Es gibt **0180-zahlwortriegel-fuer-werte-hpp**, status offen, haengt_an 0155, angelegt am
2026-09-06. Der Riegel liest genau diese Datei und zaehlt genau diese Sorte Satz nach.
Damit ist der letzte Absatz von Befund 1 ueberholt; er steht stehen, weil er die
Herleitung traegt, aber die Empfehlung darin gilt nicht mehr.

**Und es deckt die Stelle trotzdem nicht.** 0180 nennt in "Was der Riegel prueft" zwei
Behauptungen, und seine Abnahme nennt dieselben zwei:

1. das Zahlwort vor "Groessen" gegen die Zahl der T48-Nummern,
2. das Zahlwort vor "Jahrgangskonstante[n]" gegen die Felder mit Berufung auf T23 Punkt 5.

Der Satz, den dieses Paket **neu** eingefuehrt hat -- "Die uebrigen sechs Felder sind
Parameterschluessel nach T27" -- ist die dritte Zahlbehauptung im selben Kopf und faellt
unter keine der beiden. Sie zaehlt keine Groessen und keine Jahrgangskonstanten, sondern
deren Gegenstueck.

**Die Empfehlung an den Projektmanager, statt der alten.** Kein eigenes Paket. Die dritte
Zaehlung gehoert als vierte Bedingung in **0180**, und zwar aus drei Gruenden: Der Riegel
liest die Datei ohnehin, seine dateien-Liste passt unveraendert, und 0180 haengt an 0155
-- es laeuft also als naechstes auf genau dem Kopf, in dem der ungedeckte Satz jetzt
steht. Die Zaehlregel ist dieselbe wie bei Nummer 2, nur mit dem Gegenmerkmal: Felder von
struct Konstanten, deren Kommentar sich auf T27 beruft statt auf T23 Punkt 5. Heute sechs;
zwei plus sechs ergibt die acht Felder der Struktur, und diese Gegenprobe faengt beide
Zahlwoerter auf einmal.

**Warum ich das nicht selbst in 0180 schreibe:** Es ist ein offenes fremdes Paket, und
eine Abnahmebedingung nachtraeglich hineinzuschreiben waere genau der Eingriff, den mein
Auftrag ausschliesst. Der Projektmanager entscheidet, ob die vierte Bedingung dazukommt
oder ob der Satz stattdessen bei der naechsten Aenderung an Konstanten gestrichen wird.
