---
typ: pruefung
paket: 0146-aktionstyp-und-kanonische-ordnung
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Jede der vier Bedingungen einzeln mit eigenem mechanischem Aufruf -- zwei frische Baeume aus `git archive`, die sich in genau den drei Paketdateien unterscheiden, beide Bauprofile, dazu sechs Mutanten einschliesslich unveraenderter Gegenprobe.
befunde: 0
---

# Pruefung 0146 -- Aktionstyp und kanonische Ordnung

## Der Stand, ueber den geurteilt wird

`HEAD` stand bei Beginn **und** bei Ende meines Laufs auf `1e72668`; die md5 der drei
Paketdateien war zu beiden Zeitpunkten dieselbe:

| Datei | md5 (Start = Ende) |
|---|---|
| `kern/include/kern/aktion.hpp` | `5a394b533898894730fd706e6fd44270` |
| `kern/src/aktion.cpp` | `c4db3797d4ea41409c5700e97ee13326` |
| `kern/test/aktion_probe.cpp` | `149d982f63870dc15919680dc75ad637` |

**Der Commit-Betreff gehoert einem fremden Paket.** `1e72668` traegt den Betreff dieses
Pakets, enthaelt aber nur `notizen/kernbauer.md` und die neue Aufgabe `0148`. Angelegt
wurden alle drei Dateien in `e34ab65` (Betreff: `0144`), zusammen mit den Dateien von
0144 und 0106. Gemessen habe ich deshalb nicht gegen einen Elterncommit -- der haette
alle drei Pakete zusammen gemessen --, sondern gegen einen selbst gebauten Bezugsstand.

## Der Apparat

Zwei frische Baeume, beide aus `git archive --format=tar HEAD ventures/0016-… specs
decisions`:

- **A** = der Stand `1e72668` unveraendert.
- **B** = derselbe Stand, beim Auspacken um genau die drei Paketdateien beschnitten
  (`tar --exclude`).

`diff -rq A B` meldet genau drei Zeilen -- die drei fehlenden Dateien und sonst nichts.
Damit misst jeder Vergleich A gegen B die Aenderung dieses Pakets und nicht die Ziele
der beiden Pakete, die im selben Commit lagen.

## Bedingung 1 -- Konfiguration und Sperrebindungsriegel

`cmake -S kern -B <bau> -DFABRIK_SANITIZER=<ON|OFF>`, vier Laeufe, jeder mit Code 0:

| Baum | Profil | Meldung des Riegels |
|---|---|---|
| B (vorher) | OFF | `9 Kernquelle(n) und 11 Probe(n) geprueft` |
| B (vorher) | ON | `9 Kernquelle(n) und 11 Probe(n) geprueft` |
| A (nachher) | OFF | `10 Kernquelle(n) und 12 Probe(n) geprueft` |
| A (nachher) | ON | `10 Kernquelle(n) und 12 Probe(n) geprueft` |

Je **eine** Kernquelle und **eine** Probe mehr, in beiden Profilen. Erfuellt.

**Zweite, unabhaengige Zaehlung** derselben Groesse, damit die Zahl des Riegels nicht
ihr eigener Zeuge ist: `ls kern/src/*.cpp | wc -l` = 10 und `ls kern/test/*.cpp | wc -l`
= 12 im Arbeitsbaum. Dazu der Warnsatz-Schlussriegel als dritte Stimme: 12 uebersetzende
Ziele in B gegen 13 in A (Profil OFF).

Dass der Riegel die neue Probe wirklich **liest** und nicht nur mitzaehlt, belegt Mutant
m5 unten.

## Bedingung 2 -- die Ordnung ist eine benannte Eigenschaft

**Die gelesene Fassung ist nachgerechnet.** Kopf und Bericht nennen `1f763e9` fuer
`technik.md` und `0134179` fuer `spiel.md`. Beide Commits existieren;
`git diff 1f763e9 HEAD -- specs/…/technik.md specs/…/spiel.md`,
`git diff 0134179 HEAD -- specs/…/spiel.md` und `git log 1f763e9..HEAD -- specs/…/`
gehen alle drei leer aus. Die genannte Fassung von T32 ist also zeichengleich mit der an
`1e72668`. Erfuellt.

**Die drei Schluessel in der Rangfolge aus T32.** T32 (`technik.md` Zeile 1416) sortiert
nach `(Aktionsart 1…5, Zielkennung, Stufe)`. Gebaut:

- `enum class Schluessel { Aktionsart = 0, Zielkennung = 1, Stufe = 2 }` -- der Wert ist
  der Rang.
- `schluesselwert(eintrag, schluessel)` gibt den Wert eines **benannten** Schluessels.
- `ordnungsvergleich` laeuft ueber die Raenge 0, 1, 2, holt je Rang
  `schluessel_des_ranges(rang)` und liest darueber. Es ist die einzige Stelle des
  Kastens, die zwei Aktionen ordnet; `operator<=>` und `operator==` rufen sie auf und
  vergleichen nichts selbst.

Die Feldreihenfolge des Verbundes ist zwar dieselbe, traegt die Ordnung aber nicht --
das ist der Unterschied, den die Abnahme meint, und er steht im Text und ist nicht nur
behauptet. Mutant m1 zeigt, dass die Rangfolge am Uebersetzer haengt.

**Die Kennungen sind gegen die Quelle geprueft, nicht uebernommen.** `spiel.md`,
Abschnitt *Die Aktionen*, Zeilen 367--387: „Fuenf Arten … Die Kennungen 1 bis 5 sind
zugleich die Gleichstandsordnung aller Masse", danach 1 Position, 2 Beteiligung,
3 Lobbybudget, 4 Hebel, 5 Sichtbarkeit. Der `enum class Art` schreibt genau diese fuenf
Zahlen aus, in derselben Zuordnung.

**Die zwei Eingaben.** Die Probe baut aus derselben Menge von zwoelf Aktionen zwei
Eingaben: A genau rueckwaerts, B nach der Gegenordnung (Stufe zuerst, Aktionsart
zuletzt, und zwar **umgedreht gerechnet** als `SCHLUESSEL - 1 - k` statt hingeschrieben).
Beide laufen auf dieselbe Ausgabe und auf die von Hand gesetzte Sollfolge. Alle drei
Folgen druckt die Probe ab; die Gegenprobe daneben zeigt, dass die drei vor dem Ordnen
paarweise verschieden und beide Eingaben ungeordnet sind -- ohne sie bestuende die
Bedingung auch gegen eine Sortierung, die nichts tut.

**Von Hand nachgerechnet.** Die Sollfolge als Tripel `(Art, Ziel, Stufe)`:
`(1,0,-3) (1,0,1) (1,4,-1) (1,19,2) (2,0,5) (2,11,-5) (3,3,-7) (3,3,7) (3,15,1)
(4,0,9) (5,0,-1) (5,2,1)`. Lexikographisch aufsteigend, streng, ohne Gleichstand; die
Paare 1/2 und 7/8 trennen sich erst an der Stufe, das Paar 11/12 erst an der
Zielkennung, und negative wie positive Stufen kommen vor -- ein Vergleich auf den Betrag
statt auf den Wert fiele also auf. Die abgedruckte Ausgabe beider Eingaben ist genau
diese Folge.

Erfuellt.

## Bedingung 3 -- beide Profile

`cmake --build` mit Code 0, danach `ctest`:

| Baum | Profil | ctest |
|---|---|---|
| B (Bezugsstand) | OFF und ON | 11 Eintraege (`ctest -N`) |
| A | OFF | 12 von 12 bestanden |
| A | ON (`-fsanitize=undefined,address`) | 12 von 12 bestanden |

Die neue Probe linkt im Profil ON `kern_geprueft`, also die sanitizer-uebersetzte
Fassung von `aktion.cpp`; die Massnahme trifft damit den Code, um den es geht, und nicht
nur den Testcode. Erfuellt.

## Bedingung 4 -- nichts ausserhalb der drei Dateien

`e34ab65` enthaelt 16 Dateien. Zugeordnet nach den `dateien`-Listen der Pakete:
`kern/include/kern/verlauf.hpp` steht in der Liste von 0144,
`werkzeuge/belegstellen/belegstellen_riegel.cpp` in der von 0106. Es bleiben fuer 0146
die drei Paketdateien, das eigene Nachweisverzeichnis `befunde/messung-0146/`, die
Aufgabendatei und das Logbuch.

Namentlich geprueft, was die Bedingung ausschliesst:

- `kern/include/kern/schritt.hpp` -- zuletzt geaendert in `113d91b`
  (`0077-schranken-probe…`), nicht in `e34ab65`. Der leere `struct Aktionsbuendel` samt
  seinem Kommentar und die Signatur von `schritt` stehen unveraendert.
- `kern/CMakeLists.txt` -- nicht im Commit; die neue Probe kommt allein ueber
  `file(GLOB … CONFIGURE_DEPENDS)` herein, und der Konfigurationslauf oben belegt es.
- Keine bestehende Probe -- in `e34ab65` ist unter `kern/test/` genau eine Datei
  betroffen, und die ist neu.

Belegstellenriegel und Bezeichnerriegel laufen gegen Baum A (also einschliesslich der
neuen Aufgabe `0148`) mit Code 0 durch. Erfuellt.

## Der Mutationsnachweis

Gruen zu uebersetzen ist kein Nachweis. Sechs Baeume, jeder eine Abschrift der Quellen
aus `1e72668`, jeder im Profil ON konfiguriert, gebaut und mit `ctest` gefahren. **m0 ist
die unveraenderte Gegenprobe** -- ohne sie saehe ein Apparat, der alles rot macht,
genauso aus wie einer, der etwas findet.

| Baum | Eingriff | Ergebnis |
|---|---|---|
| m0 | keiner (Gegenprobe) | gruen, Probe bestanden |
| m1 | `Schluessel`-Werte umgedreht: `Aktionsart = 2`, `Stufe = 0` -- der Wert ist nicht mehr der Rang | **rot beim Uebersetzen**, vier `static_assert` (Zeilen 303, 310, 315, 328) |
| m2 | ein viertes Feld `std::uint8_t zusatz` an `Aktion` angehaengt | **rot beim Uebersetzen**, `sizeof(Aktion) <= 16` (Zeile 211) |
| m3 | `operator<=>`/`operator==` rechnen ueber die Felder statt ueber `ordnungsvergleich` | **gruen** -- siehe unten |
| m4 | `ordne` laesst den letzten Eintrag liegen (`k + 1 < anzahl`) | rot an der Probe, 6 Pruefungen, erste in Zeile 398 |
| m5 | die Sperrezeile aus `test/aktion_probe.cpp` entfernt | rot schon bei der Konfiguration (Code 1), Riegel nennt `test/aktion_probe.cpp` |

**m2 war eine Fallenprobe, und die Falle hielt.** Die Meldung dieser Zusicherung sagt
„eine Aktion traegt die drei Ordnungsschluessel und sonst nichts", gemessen wird aber nur
`sizeof`. Meine Vermutung war, ein viertes Feld passe in die Auffuellbytes und lasse die
Zusicherung gruen -- sie ist falsch: `stufe` endet auf Byte 15, es gibt am Ende kein
Auffuellbyte, und jedes angehaengte Feld traegt den Verbund auf 24. Ein Feld **zwischen**
die drei zu schieben scheitert an den Aggregatinitialisierungen im Kopf und in der Probe.
Die Zusicherung deckt also, was ihre Meldung behauptet.

**m3 ist gruen, und das ist kein Befund gegen dieses Paket.** Es ist der Beleg dafuer,
dass die Abnahme mit ihrem Satz recht hat: Weil die Feldreihenfolge mit der Rangfolge
zusammenfaellt, kann **keine** laufende Probe die benannte Eigenschaft von der
Nebenwirkung unterscheiden. Bedingung 2 haengt damit am Text und nicht am Testlauf, und
genau dort habe ich sie geprueft. Das gebaute Stueck fuehrt beide Operatoren ueber
`ordnungsvergleich`; m3 sagt nur, was ein kuenftiger Umbau ungestraft koennte -- und
gehoert deshalb hierher und nicht in ein Paket.

## Die vier Fragen meiner Rolle

**1. Determinismus.** Strukturell: Der Mustervergleich ueber `double|float|unordered_|
chrono|rand(|random_device|reinterpret_cast|uintptr_t|getenv|__DATE__|std::sort|new|
malloc` findet in allen drei Dateien **nichts**. `src/aktion.cpp` und
`test/aktion_probe.cpp` binden `kern/sperre.hpp` als letzten `#include`; der Riegel
belegt es, m5 zeigt, dass er dabei zusieht. Gemessen: Die vollstaendige Ausgabe der Probe
ist in beiden Bauprofilen Zeile fuer Zeile identisch (80 Zeilen; die beiden Abweichungen
sind die Pfadzeilen von `ctest` selbst).

Der Punkt, an dem eine Ordnung sonst still nichtdeterministisch wird, ist der
**Gleichstand**: Zwei unterscheidbare Eintraege mit gleichem Schluessel bekaemen ihre
Reihenfolge vom Sortierverfahren, und T9 warnt genau davor. Hier ist er doppelt
geschlossen -- `ordne` fuegt ein und sortiert nicht, und der Verbund traegt nur die drei
Schluessel, sodass ein Gleichstand zweimal derselbe Eintrag ist. m2 belegt, dass diese
zweite Haelfte nicht unbemerkt wegfallen kann.

**2. Rueckkopplungen.** Dieses Paket enthaelt keine Zustandsfortschreibung und keine
Schleife, in der Erfolg mehr Erfolg erzeugt; die Gegenkraefte aus `spiel.md` sind hier
nicht zu erwarten, und ihr Fehlen ist kein Befund. Gesucht habe ich nach der einen
unbegrenzten Groesse, die es geben koennte -- der Listenlaenge. Sie ist begrenzt, aber
nicht hier: `ordne` und `in_kanonischer_ordnung` nehmen die Kapazitaet vom Aufrufer und
brechen bei `anzahl > N` ab. Die Drei aus T32 („mehr als drei Aktionen") steht bewusst
nirgends; sie gehoert zu `buendel_zulaessig` und damit ins Folgepaket. Das ist der
Zuschnitt, den das Paket vorgibt.

**3. Zustandsausgabe.** Kein Zustand in diesem Paket. Die Prueffrage in ihrer hiesigen
Form -- *laesst sich aus der Ausgabe allein erkennen, ob richtig geordnet wurde?* -- ist
mit ja zu beantworten: Die Probe druckt beide Eingaben und beide Ausgaben vollstaendig
ab, mit Artnamen statt blossen Zahlen, und `art_name` wie `schluessel_name` brechen bei
einem unbekannten Wert ab, statt ein Fragezeichen zu drucken, das in einer Ausgabe wie
eine gueltige Art aussaehe. Die Ausgabe zeigt damit auch ihre eigene Schaerfe.

**4. Die Raender.** Einzeln gefahren und von Hand nachgerechnet:

- `ordnungsvergleich` **rechnet nicht**, es vergleicht nur (`hier < dort`). Ein
  Ueberlauf ist damit verhindert und nicht nachtraeglich erkannt -- die Form, die nicht
  an `-fwrapv` haengt -- auch bei `I64_MIN` gegen `I64_MAX`. Die Zusicherung in Zeile 299
  rechnet genau diesen Fall: `(1, 65535, I64_MAX)` gegen `(2, 0, I64_MIN)` muss negativ
  sein, weil Rang 0 mit 1 < 2 entscheidet, bevor die schwaecheren gelesen werden.
- `art_der_kennung` gegen `0`, `6`, `I64_MIN`, `I64_MAX`: bricht ab, und die Meldung
  nennt die Zahl, ueber die geurteilt wurde. Die beiden Nachbarn `1` und `5` brechen
  **nicht** ab -- Positiv- und Negativnachweis stehen beide da.
- `zielkennung(platz)`: `ZIELKENNUNG_MAX` selbst geht durch, `+ 1` bricht ab. Der
  Vergleich `platz > ZIELKENNUNG_MAX` laeuft ueber `std::size_t` gegen einen positiven
  Wert; kein Umlauf. Ein umgelaufener Platz waere ein gueltiger, und die Ordnung
  darueber still falsch -- die Schranke sitzt also an der richtigen Stelle.
- `ordne`/`in_kanonischer_ordnung` mit `ANZAHL` gehen durch, mit `ANZAHL + 1` brechen
  beide ab, jedes mit seinem eigenen Namen in der Meldung. Bei `anzahl` 0 und 1 laeuft
  keine Schleife (`k = 1 < anzahl` faellt sofort), und `platz - 1` steht immer hinter
  `platz > 0`.
- Division und Rundung kommen nicht vor; eine Summierung ueber tausend Runden ebenso
  wenig, weil dieser Kasten keinen Zustand fortschreibt.
- `ART_KENNUNG_LETZTE - ART_KENNUNG_ERSTE + 1 == ARTEN`: 5 - 1 + 1 = 5. Stimmt.
- `ZIELKENNUNG_MAX = 65535` gegen die Vorgabe gehalten: T32 und T9 nennen keine
  Obergrenze. Der Kopf begruendet die zwei Bytes damit, dass die groesste heute im Kern
  gefuehrte Indexordnung 310 Eintraege habe -- nachgeschlagen, `zustand::FELDER = 310`
  (`zustand.hpp` Zeile 88), und 310 > 255. Ein Huellentyp ueber `std::uint8_t`, wie T9
  ihn fuer `LandId`, `SektorId` und `InstrumentId` vorschreibt, truege diese Ordnung
  nicht. Die Abweichung ist begruendet, und die tragende Haelfte von T9 -- ein eigener
  Indextyp statt eines blanken Zaehltyps -- ist eingehalten.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Eine Zahl ohne Vorgabe.** Jede Konstante des Kopfes gegen ihren T-Block gehalten:
  `ARTEN`, `ART_KENNUNG_ERSTE/LETZTE` und die fuenf `Art`-Werte gegen `spiel.md`
  *Die Aktionen*; `SCHLUESSEL` und die drei `Schluessel`-Werte gegen T32;
  `ZIELKENNUNG_MAX` gegen T9 und `zustand::FELDER`. Keine geratene Zuordnung: Die
  Zielkennung ist ausdruecklich nur ein Platz und keine Menge je Art -- die Luecke ist
  gemeldet statt gefuellt, und das ist die richtige Reihenfolge, weil eine geratene
  Ordnung den Regressionsbestand baende, den T32 gerade schuetzen soll.
- **Eine Behauptung in einem Kommentar.** Drei geprueft: die gelesene T32-Fassung
  (`1f763e9`, oben nachgerechnet), die 310 der groessten Indexordnung, und die
  Zusicherung, der Verbund trage nur die drei Schluessel (m2).
- **Ein Lesefehler in der Probe selbst.** `enthaelt()` liest `heuhaufen[i + j]` -- ueber
  das abschliessende Nullzeichen hinaus kommt es nicht, weil die Schleifenbedingung dort
  abbricht. `als_text(...)` gibt einen Zeiger in ein temporaeres `Meldung` heraus; das
  Temporaere lebt bis zum Ende des Vollausdrucks, und der `PRUEFE`-Aufruf **ist** dieser
  Vollausdruck. Der Lauf unter `-fsanitize=address` haette beides gemeldet und tat es
  nicht.
- **Ein rotes Ergebnis, das dem falschen Paket gehoert.** Es gab keins: alle zwoelf
  ctest-Eintraege sind in beiden Profilen gruen.
- **Ein Widerspruch zwischen Abnahme und Vorgabe.** Keiner gefunden; die vier
  Bedingungen und T32/T9 sagen dasselbe.
- **Eine Luecke, die schon ein Paket ist.** `grep` ueber `aufgaben/`: Die beiden
  Meldungen des Bauagenten -- der fehlende Wertebereich der Zielkennung je Art und der
  Widerspruch bei Art 5 (`spiel.md` sagt „eine Position", der Zustand fuehrt eine
  einzelne `fonds.sichtbarkeit`) -- stehen beide in der neuen Aufgabe `0148`, deren
  Abnahme den zweiten Punkt ausdruecklich mitnennt. `0148` traegt korrekt
  `status: vorschlag`. Ein eigener Vorschlag von mir waere eine zweite Fassung derselben
  Luecke und unterbleibt.

## Was ich nicht geprueft habe

- Die Zulaessigkeit eines Buendels und die Kapazitaet drei aus T32. Das ist das
  Folgepaket, und 0146 schliesst es ausdruecklich aus.
- Ob der hinterlassene Zuschnitt (`ordne` nimmt die Kapazitaet vom Aufrufer, kein
  Buendeltyp) fuer das Folgepaket der richtige ist. Das ist eine Entwurfsfrage an den
  Projektmanager, keine Abnahmebedingung dieses Pakets, und `specs/` schweigt dazu.
- Die Anbindung an `kern::schritt`. Sie ist dem Paket verboten, und sie ist unterblieben.
- Das Logbuch und die Begruendung des Bauagenten.
