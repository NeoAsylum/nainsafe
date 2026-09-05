---
typ: pruefung
paket: 0016-schreiber-ursachenkette
pruefer: kern-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: die sechs Bedingungen einzeln -- Feldtabelle und Ursachenformen abgezaehlt gegen T18 (1), beide Abbrueche im eigenen Sanitizer-Bau ausgeloest und die Meldungen gelesen (2, 3), Maskengroessen als static_assert im Uebersetzungslauf und beide Seiten der Rundenendpruefung ausgeloest (4), volle 310er-Runde durchlaufen mit Kettenlaenge 310 (5), Grep und Include-Liste (6); alle sechs erfuellt
befunde: 1
---

# Prüfung `kern::schreiber` gegen `0016-schreiber-ursachenkette`

Geurteilt ist gegen die sechs Bedingungen im Abschnitt *Abnahme* und gegen nichts sonst.
Das Logbuch des Kernbauers und seine Begründung habe ich nicht gelesen.

**Ergebnis: alle sechs Bedingungen erfüllt.** Der eine Befund reißt keine davon — er
betrifft eine Zusage aus T18, die dieses Paket in seinen drei Dateien gar nicht
durchsetzen *kann*, und gehört deshalb dem Projektmanager und nicht dem Bauagenten.

## Wie geprüft wurde

Eigener Bau aus dem Quellstand, nicht der vorhandene unter `bau/`:

```
cmake -S . -B $TMPDIR/pruef-0016 -DCMAKE_BUILD_TYPE=Debug     -> Code 0
cmake --build $TMPDIR/pruef-0016 -j 4                          -> Code 0, keine Warnung
ctest --output-on-failure                                      -> 6/6 bestanden
```

`FABRIK_SANITIZER:BOOL=ON`, und `kern/CMakeFiles/schreiber_probe.dir/link.txt` zeigt
`-fsanitize=undefined,address -fno-sanitize-recover=all ... libkern_geprueft.a`: Die Probe
läuft gegen die mitsanitierten Kernquellen, nicht gegen die ungeprüfte `kern`. Damit sind
die vier Zahlen- und Speicherfragen unten nicht nur gelesen, sondern gelaufen. Alles unter
`-Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wold-style-cast` — der Bau ist
warnungsfrei.

## Die sechs Bedingungen

**1 — Sieben Felder, sechs Formen.** T18-Tabelle danebengelegt und abgezählt.
`Ursachensatz` (`schreiber.hpp:313`) trägt `runde`, `ziel`, `alt`, `neu`, `ursache`,
`verzoegerung`, `beitrag` — sieben, unter diesen Namen, in dieser Reihenfolge, kein
achtes. `UrsacheArt` (`schreiber.hpp:143`) trägt `Aktion`, `Instrument`, `Gegenkraft`,
`Marktraeumung`, `Vortrag`, `Jahrgang` — sechs, keine siebte, kein Freitextfeld. Die
Aufzählung ist geschlossen: Ein `Ursache`-Wert entsteht nur über einen der sechs
Erzeuger, der private Konstruktor ist der einzige andere Weg. **Erfüllt.**

**2 — Zweiter Schreibzugriff und `lies_neu` sterben.** Beide ausgelöst, `ctest -V`:

```
Abbruch wie erwartet (179): kern::schreiber::setze -- zweiter Schreibzugriff in Runde 4
                            auf land.DE.leitzins (Nr. 106)
Abbruch wie erwartet (189): kern::schreiber::lies_neu -- in Runde 4 noch nicht
                            geschrieben: land.DE.inflation (Nr. 105)
```

Die Adresse steht ausgeschrieben darin, wie verlangt. Gegengeprüft gegen
`daten/adressen.md`: Zeile 148 führt Nr. 106 als `land.DE.leitzins`, Zeile 43 Nr. 1 als
`land.US.sektor.1.wertschoepfung` (der Abbruch in Zeile 409 der Probe) — die Nummern und
Namen der Meldungen stimmen mit dem Verzeichnis überein, nicht nur mit sich selbst.
Beide Proben liegen im `ctest`-Eintrag `schreiber_probe`, den `kern/CMakeLists.txt` je
Datei unter `test/` erzeugt; er ist bestanden, und ein ausgebliebener Abbruch hätte ihn
über `KEIN ABBRUCH` rot gemacht. Der Übersetzungslauf `uebersetzung-2026-09-02.md` zeigt
denselben Eintrag als bestanden. **Erfüllt.**

**3 — `lies_alt` bleibt alt.** `probe_alt_bleibt_alt` gibt aus:

```
lies_alt = 4711, lies_neu = 815 (erwartet 4711 und 815)
```

Zwei verschiedene Zahlen, beide ausgeschrieben. Der Konstruktor
(`schreiber.cpp:266`) legt `alt_` und `neu_` als zwei Kopien an; läge beides auf
demselben Speicher, stünde hier zweimal 815. Der Ursachensatz trägt beide Zahlen.
**Erfüllt.**

**4 — Maskenprüfung zweiseitig.** Beide Seiten ausgelöst:

```
Rundenende Runde 1: in der Sollmaske, aber nicht geschrieben: welt.preis.2 (Nr. 240)
Rundenende Runde 1: ausserhalb der Sollmaske geschrieben: fonds.hebelstand (Nr. 256)
```

`daten/adressen.md` Zeile 282 und 298 führen genau diese beiden Namen unter Nr. 240 und
256. Die Zahlen stehen ausgeschrieben in `schreiber.hpp:401,405,408`
(175 / 135 / 310), und `schreiber.hpp:410` rechnet `175 + 135 == 310` als
`static_assert` nach. Nicht verlangt, aber vorhanden und stärker: `schreiber.cpp:146`
zählt die Bits der gebauten Maske gegen 175, `schreiber.cpp:163` die Gegenprobe gegen
135. Beide liefen in meinem Bau.

Die Blockzuordnung habe ich gegen die T38-Tabelle (`technik.md:583-597`) Zeile für Zeile
nachgelesen. Je Land setzt `baue_maske_weltlauf` die Versätze 0-11 (Sektoren), 12-20
(Aggregate), 21 (Zustimmung), 24/28/32/36 (Instrumentenstand) und 43 (`basiswechsel`) —
27 Stück; draußen bleiben 22/23, die zwölf Instrumentenfelder ohne Stand und 40-42
(Restdauern) — 17 Stück. Das ist genau die Aufteilung `27 × 4 = 108` und `17 × 4 = 68`
aus T38. Restwelt 22, Handel 40, Weltpreise 2, Partie ohne Mandatsstand 3.
Nachahmerzähler, Marktkorb und der ganze Fondsblock sind nirgends gesetzt. **Erfüllt.**

**5 — Volle Runde.** `probe_volle_runde` schreibt alle 310 Adressen im `spielmodus`, zwei
davon (7 und 300) über `vortrag`, und die Rundenendprüfung besteht:

```
Spielmodus: 310 Adressen geschrieben, Kette 310 Glieder (erwartet 310)
```

Erwartungswert `310` steht ausgeschrieben in `schreiber_probe.cpp:384-385`, keine
Zählschleife über den eigenen Behälter. Der Vortrag hält den Wert (`alt == neu == 123456`
und die 310 Kettenglieder liegen in Schreibreihenfolge. **Erfüllt.**

**6 — Kein Gleitkomma, keine Fremdabhängigkeit, keine streuenden Behälter.**
`grep -rnE 'float|double'` über `kern/src/schreiber.cpp` und
`kern/include/kern/schreiber.hpp` liefert nichts — auch nicht im Kommentar. Zusätzlich
liegt `#include "kern/sperre.hpp"` als letzte Include-Zeile in `schreiber.cpp`; ab dort
sind `float` und `double` per `#pragma GCC poison` Übersetzungsfehler. Die Include-Liste
beider Dateien enthält nur `<array>`, `<cstddef>`, `<cstdint>` und Kernköpfe, die
CMake-Ziele linken nichts außer `kern`. Behälter: `Kette` ist
`std::array<Ursachensatz, 310>` mit laufendem Index, `Bitfeld` fünf `uint64_t`, `Meldung`
zwei `std::array<char, N>` — Grep auf `std::map|std::unordered|std::set|std::vector|
std::string|reinterpret_cast|const_cast|new|delete|asm` über alle drei Paketdateien:
keine Treffer. **Erfüllt.**

## Die vier Kernfragen — wonach ich gesucht habe

**Determinismus.** Gesucht nach Gleitkomma in der Zustandsfortschreibung (keins, siehe
Bedingung 6), nach Iteration über ungeordnete Mengen (keine — jede Schleife läuft über
`0 ... FELDER` oder über ein ausgeschriebenes `constexpr std::array`, `schreiber.cpp:40-62`),
nach mehr als einem Zufallsstrom (dieses Modul zieht keinen), nach Zeit- oder
Speicheradressen im Ergebnis (`Ursachensatz` besteht aus vier `i64`, einem `size_t` und
drei Ganzzahlen in `Ursache`; kein Zeiger, kein `<chrono>`). `sollmaske` gibt eine
Referenz auf ein `constexpr`-Objekt mit statischer Lebensdauer zurück. Zwei Läufe der
Probe hintereinander sind Zeichen für Zeichen gleich (28 Zeilen Ausgabe, `diff` leer).

**Rückkopplungsschranken.** Dieses Paket *ist* die Schranke, nicht ihr Nutzer: Das
Bitfeld tötet jede Rückkopplung innerhalb der Runde, die zweiseitige Maskenprüfung tötet
den falschen Modus, `lies_neu` tötet den Lesezugriff vor dem Schreibzugriff. Alle drei
sind ausgelöst und ausgeschrieben. Die Gegenkräfte aus `spiel.md` gehören `kern::schritt`
und sind hier zu Recht nicht eingebaut.

**Zustandsausgabe.** Aus `(Zustand, Kette)` lässt sich prüfen, ob richtig *gebucht* wurde:
je Adresse alt, neu, Ursache, Verzögerung, Beitrag; jede Maskenadresse genau einmal; die
Rückwärtsauflösung aus T20 ist möglich, weil `Instrument{land,instr}` und
`Vortrag{adresse}` sich über `stelle_instrument` bzw. direkt wieder in eine Adresse
übersetzen und `Aktion`, `Gegenkraft`, `Jahrgang` Endpunkte sind. Ob richtig *gerechnet*
wurde, kann diese Ausgabe nicht sagen — das braucht die Bewertungsformeln aus
`kern::werte`, und die sind ausdrücklich nicht Teil dieses Pakets. Der Modus fehlt im
Ursachensatz, steht aber über `Schreiber::modus()` bereit; ein achtes Feld wäre ein
Verstoß gegen Bedingung 1.

**Zahlenränder.** Von Hand nachgerechnet: `Meldung::zahl` bildet den Betrag über
`u64{0} - static_cast<u64>(wert)` — für `INT64_MIN` ergibt das 9.223.372.036.854.775.808
und nicht den Überlauf, den `-wert` gäbe. Der Ziffernpuffer fasst 24 Zeichen, die längste
`u64` hat 20. `Meldung::text` bricht bei `laenge_ + 1 >= 256` ab und setzt das Nullbyte
innerhalb des Feldes; die längste erzeugbare Meldung (Rundenende + 20 Ziffern + längste
Adresse mit 47 Zeichen + Nummer) liegt bei rund 150 Zeichen. `Bitfeld` prüft jeden Zugriff
gegen `FELDER` und nicht gegen `5 × 64`, die zehn überzähligen Bits werden nie gesetzt.
Rundung und Division gibt es in diesem Modul nicht — es speichert `i64` und rechnet nicht.
Der Zeiger aus `Meldung::fertig()` überlebt seinen Puffer nicht: `std::domain_error`
kopiert den Text im Konstruktor, bevor der Wurf die Rahmen abbaut, und ASan hätte das
Gegenteil in allen sechzehn ausgelösten Abbrüchen gemeldet.

## Befund 1 — „einziger Schreibweg" ist im Code kein einziger Schreibweg

**An den Projektmanager, nicht an den Kernbauer.** Keine der sechs Bedingungen verlangt
es, und der Kernbauer könnte es in seinen drei Dateien nicht herstellen.

T18 sagt: *„Die Felder von `Zustand` sind ausserhalb des Kerns nicht schreibbar; innerhalb
schreibt niemand direkt, sondern über `Schreiber::setze(...)`."* Das Arbeitspaket
wiederholt den Satz als Punkt 1 von *Was du baust*. Gebaut ist die eine Hälfte — `setze`
existiert und tut das Richtige. Die andere Hälfte gibt es nicht: `kern::zustand::Zustand`
ist ein `struct` mit öffentlichem `std::array<i64, 310> feld` und öffentlichem
`schreibe(index, wert)` (`zustand.hpp:390-410`).

**So erzeugt man den Fehler, Schritt für Schritt:**

1. Eine beliebige Übersetzungseinheit bindet `kern/zustand.hpp` ein — mehr braucht es
   nicht, `schreiber.hpp` ist dafür nicht nötig.
2. Sie hält einen `Zustand`, etwa den, den `Schreiber::rundenende()` gerade
   herausgegeben hat und den die Sitzung nach T19 für die nächste Runde aufbewahrt.
3. Sie ruft `zustand.schreibe(adresse, wert)` oder schreibt `zustand.feld[adresse] = wert`.
4. Der Wert steht im Zustand. Es entsteht **kein** Ursachensatz, das Bitfeld sieht nichts,
   die Rundenendprüfung sieht nichts, und kein Übersetzer und kein Sanitizer meldet etwas.

Die Probe des Pakets führt diesen Aufruf selbst vor: `schreiber_probe.cpp:212` und
`:364-365` schreiben mit `vorrunde.schreibe(...)` am Schreiber vorbei. Dort ist es
harmlos und mangels Startwertquelle auch alternativlos — es belegt aber, dass der Weg
offensteht.

**Was daran teuer ist.** Der Kopf von `schreiber.hpp` nennt drei Zusagen und schreibt
dazu: *„Alle drei sind Eigenschaften des Codes oder gar nicht."* Zusage 1 („genau einmal
je Runde") und Zusage 2 („acht Kanäle, nicht neun") sind es nur für Schreibzugriffe, die
durch `setze` gehen. Ein späterer Bauagent, der in `kern::schritt` oder in der Sitzung
einmal `feld[i] = ...` schreibt, erzeugt einen neunten Rückkopplungskanal, der in keiner
Kette auftaucht — und die `diff`-Ebene aus T20 zeigt dann eine Änderung ohne Ursache. Das
ist genau die Sorte Fehler, die T18 verhindern soll, und sie fällt erst auf, wenn jemand
einem Diff nicht glaubt.

**Warum es hier nicht behoben werden konnte.** Die Behebung liegt in `zustand.hpp`
(`feld` privat, `schreibe` privat, `friend class schreiber::Schreiber` oder ein
Zugriffsschlüssel), und `zustand.hpp` steht nicht in der `dateien`-Liste dieses Pakets.
Paket 0008 hat die Durchsetzung ausdrücklich weitergereicht (`zustand.hpp:385-389`:
*„die Durchsetzung gehört deshalb dem Paket, das den Schreiber baut"*), dieses Paket hat
sie nicht aufgenommen. Zwischen beiden liegt eine Lücke, die keiner der beiden
Bauagenten schließen durfte.

**Vorschlag:** ein eigenes Arbeitspaket, das `Zustand::feld` und `Zustand::schreibe`
schließt und dem Startwertweg aus dem Kasten `daten` einen benannten zweiten Zugang gibt
(die Probe braucht ihn ebenfalls). Es berührt `zustand.hpp`, `zustand.cpp`, `schreiber.cpp`
und die Proben von 0008 und 0016 — kein großes Paket, aber eines, das vor `kern::schritt`
kommen sollte. Danach ist die Regel eine Grep-Regel wie die Gleitkommasperre:
`grep -rn '\.feld\[' kern/` läuft leer.

## Was ich ausdrücklich nicht als Befund behandelt habe

- **Speicherform des Bitfelds** (fünf `uint64_t`), **Gestalt des harten Fehlers** (Wurf)
  und **Zahl der Kettenkapazität** (310) — das Arbeitspaket erklärt alle drei zur
  Entscheidung des Bauagenten. Die Reihenfolge ist fest, die Kapazität begründet.
- **Dass die Kapazitätsprüfung in `Kette::anhaengen` unerreichbar ist**, weil das Bitfeld
  vorher greift. Das ist die Folge der zugelassenen Zahl 310 und keine Abweichung; T19
  verlangt eine feste Kapazität mit hartem Fehler, und beides steht da.
- **Dass `verzoegerung < 0` geprüft wird, `beitrag` aber nicht.** T18 nennt für den
  Beitrag keine Schranke; eine erfundene wäre schlechter als keine.
- **Dass `rundenende()` nur prüft, wenn jemand es ruft.** Der fertige Zustand ist nur über
  diesen Aufruf zu bekommen, `neu_` ist privat — der Weg an der Prüfung vorbei führt an
  der Rundenausgabe vorbei.
- **Größe eines `Schreiber` auf dem Stapel** (rund 22 kB, davon 17 kB Kette). Kein
  Vorgabenverstoß; T19 will die Kette ausdrücklich neben dem Zustand. Für den Planwert
  von 10 Mikrosekunden je Runde (`technik.md:1751`) ist das Nullsetzen unkritisch, aber
  es ist eine Zahl, die der Prüfstandbauer kennen sollte.
- **Benennung, Aufbau, Kommentardichte.** Kein Geschmacksbefund.
