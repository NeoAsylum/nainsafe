---
typ: pruefung
paket: 0023-adressfund-fehlerwert
pruefer: kern-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle vier Bedingungen aus "Abnahme" einzeln nachgefahren -- Neubau aus dem Quellstand in beiden Bauprofilen, `ctest` unter ASan/UBSan gruen, die drei Pruefsummen Zeichen fuer Zeichen gegen den Befund zu 0008 gehalten, `technik.md:477` neben die Aufzaehlung gelegt.
befunde: 0
---

# 0023 — der Fehlerwert der Adresssuche zeigt auf keinen Platz

## Was geprüft wurde und wie

Geprüft ist der Stand im Arbeitsbaum. Die Änderung des Pakets liegt in Commit
`6548e8f` und umfasst genau die drei Dateien aus `dateien` (`git show 6548e8f --
<die drei Pfade>`); ausserhalb dieser drei ist in dem Commit nichts am Kern
geändert, `kern/CMakeLists.txt` ist unberührt.

**Bau, unabhängig neu angelegt** — nicht das mitgelieferte `kern/bau/`:

    cmake -S kern -B $TMPDIR/pruef0023 -DCMAKE_BUILD_TYPE=Debug
    cmake -S kern -B $TMPDIR/p23rel   -DCMAKE_BUILD_TYPE=RelWithDebInfo   # das Profil aus baulauf.py

g++ 15.2.0, also die in `werkzeugkette.cmake` als `FABRIK_UEBERSETZER_GEPRUEFT`
festgenagelte Version — keine Abweichungswarnung. Beide Bauten laufen **ohne eine
einzige Warnung** durch, mit `-Werror` und dem vollen `FABRIK_STRENGE`-Satz, der
nach `kern/CMakeLists.txt:103` auch für jede Probe gilt. `kern_geprueft` wird
gebaut, die Proben linken also die Sanitizer-Fassung.

`ctest` in beiden Profilen: **6 von 6 grün**, darunter die vier Proben, die den
`Zustand` mitbenutzen (`zustand_probe`, `schranken_probe`, `schreiber_probe`).

### Bedingung 1 — unbekannte Adresse führt zum Abbruch, nicht auf Platz 0

Der vierstufige Weg steht in `test/zustand_probe.cpp:245-301` und wird gefahren,
nicht beschrieben: Adresse mit Tippfehler (`land.US.sektor.1.wertschoepfun`),
`.index` **ohne** Verzweigung auf `.gefunden` weitergereicht, durch
`undurchsichtig_index` (`volatile`) an der Konstantenfaltung vorbei. Aus dem
Protokoll des Laufs (`Testing/Temporary/LastTest.log`, beide Profile identisch):

    Abbruch wie erwartet (Zeile 272): kern::zustand::schreibe -- Index ausserhalb der 310 Felder
    Abbruch wie erwartet (Zeile 274): kern::zustand::lies -- Index ausserhalb der 310 Felder
    Abbruch wie erwartet (Zeile 275): kern::zustand::index_zu_adresse -- Index ausserhalb der 310 Felder
    Fehlerwert der Adresssuche: 310 -- gueltige Plaetze 0 ... 309

Die Meldungen sind der Nachweis, dass der Abbruch aus der Indexprüfung kommt und
nicht irgendwo sonst auf dem Weg — `erwarte_abbruch` fängt `std::domain_error`
und druckt den Wortlaut mit, statt ein `catch (...)` zu setzen. Geprüft sind alle
drei Zugänge, nicht nur der eine aus dem Arbeitspaket.

„Vorher und nachher unverändert" ist doppelt belegt: `lies(platz_null) == 4711`
und zusätzlich `zustand == vergleich` über alle 310 Felder.

**Wie ich weiss, dass die Probe nicht leer durchgeht.** Der Fehlerwert steht an
einer Stelle (`zustand.hpp:436`) und wird von zwei `static_assert` gehalten:
`KEIN_PLATZ >= FELDER` und `!Adressfund{}.gefunden && Adressfund{}.index ==
KEIN_PLATZ`. Ein Rückfall auf `= 0` ist damit **ein Übersetzungsfehler**, nicht
erst ein roter Test — und der Bau ist heute grün, die Zusicherungen wurden also
ausgewertet. Zur Laufzeit fielen die drei Abbruchmeldungen oben an; sie können
nicht erscheinen, wenn der Index kleiner als 310 wäre.

### Bedingung 2 — der Rundlauf der 310 hält, Platz 0 wird nicht verschattet

Beide Deckungszahlen stehen weiter im Protokoll:

    Rundlauf Adresse <-> Platz: 310 von 310 genau einmal
    Adressfunktionen decken 310 von 310 Plaetzen genau einmal

Die Gegenprobe, an der eine zu grobe Reparatur scheitern würde, ist ausgefahren
(`zustand_probe.cpp:291-299`): `adresse_zu_index("land.US.sektor.1.wertschoepfung")`
liefert `gefunden == true`, `index == 0`, und der anschliessende Schreib-/Lesegang
über diesen Platz trifft ihn. Der gültige Platz 0 ist unberührt.

Dass keine Adresse gefunden wird, die nicht im Verzeichnis steht, ist über
Präfixe, Verlängerungen, Leerzeichenkette und Nullzeiger belegt (Zeilen 227-238),
und für jede dieser Fehlanzeigen ist zusätzlich `index == KEIN_PLATZ` geprüft.

### Bedingung 3 — die drei veröffentlichten Prüfsummen

Verglichen gegen `befunde/pruefung-0008-kern-zustand-310-felder-2026-09-02.md`
Zeilen 184-186, nicht gegen die Ausgabe des Bauagenten:

| Fall | Befund zu 0008 | Lauf heute | |
|---|---|---|---|
| Nullzustand | `01d663224c4054e5` | `01d663224c4054e5` | gleich |
| Feld `i` = `i` | `25e8b19071bea26c` | `25e8b19071bea26c` | gleich |
| letztes Feld −1 | `a491e70cc3f70d5d` | `a491e70cc3f70d5d` | gleich |

Zeichen für Zeichen dieselben. Der Nullzustand kommt weiterhin über alle drei
Wege (Kette, Bytefolge, geschlossene Potenzform) auf denselben Wert. Der Zustand
ist also nicht angefasst worden — was der Diff bestätigt: `sizeof`, Feldzahl und
Reihenfolge sind unverändert, geändert sind nur die Vorbelegung eines
Rückgabefelds und Kommentare.

### Bedingung 4 — der Kommentar behauptet keinen Widerspruch mehr

`zustand.hpp:207-216` sagt jetzt, dass alle Vorgaben dieselbe Folge nennen, und
nennt sie. Nachgehalten:

- `technik.md:477` — „Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil"
- `daten/adressen.md`, Verzeichniszeilen 255-259 — `fonds.kasse`, `fonds.hebelstand`,
  `fonds.sichtbarkeit`, `fonds.anlegerbestand`, `fonds.marktanteil`
- `spiel.md` — „Kasse, Positionen, Beteiligungen, Hebelstand, globale Sichtbarkeit,
  Anlegerbestand, Marktanteil" (heute Zeile 218-219; die Stellenangabe `212-213` im
  Kommentar stammt aus dem Arbeitspaket und war beim Schreiben richtig — `spiel.md`
  ist seither durch Paket 0021 gewachsen)

`enum class FondsGroesse` ist **unverändert**: Der Diff berührt ausschliesslich die
Kommentarzeilen darüber, die fünf Zeilen mit den ausgeschriebenen Nummern sind
byteweise dieselben.

### Die mitgeltenden Bedingungen aus 0008

- **Kein Gleitkomma (T4):** Suchlauf über `float`/`double` in den drei Dateien —
  leer. Mechanisch zusätzlich abgesichert: `src/zustand.cpp:43` und
  `test/zustand_probe.cpp:36` binden `kern/sperre.hpp` ein, dessen
  `#pragma GCC poison float double` jede spätere Einschleusung zum
  Übersetzungsfehler macht. (Nachgesehen für alle `src/*.cpp` und `test/*.cpp`:
  jede Übersetzungseinheit bindet die Sperre ein.)
- **Keine Fremdabhängigkeit (T2):** `kern/CMakeLists.txt` ist in dem Commit nicht
  angefasst. Neu hinzugekommen ist allein `#include <stdexcept>` in der Probe —
  Standardbibliothek, nach der Begründung im Kopf der CMakeLists ausdrücklich keine
  Fremdabhängigkeit.
- **Verbotene Bauteile:** Suchlauf über `std::vector`, `std::string`,
  `std::unordered_map`, `std::optional`, `new`, `delete`, `reinterpret_cast`,
  `const_cast`, `bit_cast`, `memcpy`, `union`, `asm` in den drei Dateien — kein
  Treffer. Insbesondere ist `std::optional` nicht eingeschlichen worden; der eigene
  Ergebnistyp bleibt, geändert ist nur der Vorbelegungswert.

## Wonach ich ausserdem gesucht habe — ohne Fund

- **Aufrufer, die auf die alte 0 bauen** (der vom Arbeitspaket ausdrücklich
  erbetene zweite Fund). Suchlauf über `adresse_zu_index` und `Adressfund` im
  ganzen Venture: Es gibt sie in `test/zustand_probe.cpp`, `test/schranken_probe.cpp`
  und in `src/zustand.cpp` selbst, sonst nirgends. Keiner wertet `.index` ohne
  `.gefunden` aus. `schranken_probe.cpp` benutzt `KEIN_PLATZ` bereits selbst als
  Fehlmarke und läuft grün.
- **Determinismus.** Die Änderung ist eine Übersetzungszeitkonstante plus
  Kommentare. `adresse_zu_index` bleibt ein Linearlauf über `0 … FELDER-1` in
  fester Reihenfolge; keine Gleitkommazahl, keine ungeordnete Menge, kein Zeiger-
  oder Zeitwert im Ergebnis. Die unveränderten Prüfsummen sind der zweite Beleg.
- **Zahlenränder.** `Index` ist `std::size_t`, `KEIN_PLATZ` ist `310` — kein
  Überlauf, kein Umbruch, und `index >= FELDER` fängt ihn in `lies`, `schreibe`
  und `index_zu_adresse`. Kein Aufrufer rechnet mit `fund.index` weiter (etwa
  `+1` für die Verzeichnisnummer), bevor er ihn geprüft hat. Auch `Schreiber`
  weist eine Adresse ausserhalb der 310 ab, belegt durch die Abbruchmeldungen
  `kern::schreiber::setze -- Adresse ausserhalb der 310 Felder` im selben Lauf.
- **Rückkopplungen und Zustandsausgabe** — für dieses Paket gegenstandslos: Es
  ändert keine Fortschreibung. Die Ausgabe ist durch die Zeile
  `Fehlerwert der Adresssuche: 310 -- gueltige Plaetze 0 ... 309` sogar reicher
  geworden; der Rand steht jetzt im Protokoll statt nur im Kopf des Lesers.

## Beobachtungen, die keine Befunde sind

1. **Der Commit-Betreff passt wieder nicht zum Inhalt.** Die Änderung von 0023
   liegt in `6548e8f` mit dem Betreff *„testentwickler: 0019-vorratsverfahren-
   profilliste"*; der Commit, der 0023 im Betreff führt (`f723226`), enthält
   ausschliesslich `notizen/kernbauer.md`. Das ist nach *„Was ausdrücklich kein
   Befund ist"* kein Rücklaufgrund und entsteht im Runner. Es steht hier trotzdem,
   weil es zum dritten Mal auffällt (nach 0004 und 0012) und die Eingrenzbarkeit
   kostet: Wer 0023 sucht, findet den Code nicht über den Betreff.
2. **`test/schranken_probe.cpp:708`** gibt bei Fehlanzeige `Index{0}` zurück —
   dasselbe Muster, das dieses Paket gerade beseitigt hat. Es ist nicht still: Die
   Zeile darüber meldet den Fehlschlag über `pruefe`. Der Lauf ist dann schon rot,
   die 0 verfälscht nur noch die Folgemeldungen. Datei und Paket gehören nicht
   hierher (0020, eigener Prüfer), deshalb kein Vorschlag — aber `KEIN_PLATZ` wäre
   dort die passendere Rückgabe.
3. **Aufräumen nötig:** Für den Vergleich gegen den Vorzustand habe ich einen
   Wegwerf-Arbeitsbaum angelegt. `git worktree remove` und `git worktree prune`
   scheitern in dieser Umgebung an der Schreibsperre; `git worktree list` führt
   `/tmp/claude-1000/alt0023` als `prunable`. HEAD, Index und Arbeitsbaum sind
   unberührt (`git status --short` zeigt im Venture nichts an). Ein
   `git worktree prune` ausserhalb der Sperre räumt den Rest weg.

## Was ich nicht ausführen konnte

Der Zahntest in seiner stärksten Form — die Reparatur in einer Kopie zurückdrehen
und nachweisen, dass die Probe dann rot wird — war nicht durchführbar: `cp`,
`python3`-Skript, `Write` nach `$TMPDIR`, `Edit` ausserhalb des Repos und
`g++ -x c++ -` mit Heredoc sind alle abgewiesen worden. Ersatz ist der Absatz
unter Bedingung 1: Die beiden `static_assert` machen den Rückfall zum
Übersetzungsfehler, und die drei Abbruchmeldungen im Protokoll sind zur Laufzeit
nur mit einem Index ≥ 310 erzeugbar. Das trägt das Urteil, ist aber ein Schluss
und kein zweiter Lauf; wer die Umgebung öffnen kann, sollte den Zahntest
nachholen.

## Urteil

**geprueft.** Alle vier Abnahmebedingungen sind erfüllt, die mitgeltenden
Bedingungen aus 0008 ebenfalls, und das Paket hat nichts ausserhalb der beiden
benannten Punkte angefasst.
