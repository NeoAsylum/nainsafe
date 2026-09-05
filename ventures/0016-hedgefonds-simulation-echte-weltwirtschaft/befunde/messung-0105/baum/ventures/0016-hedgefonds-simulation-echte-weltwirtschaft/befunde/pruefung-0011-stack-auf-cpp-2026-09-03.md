---
typ: pruefung
paket: 0011-stack-auf-cpp
pruefer: entwurf-pruefer
datum: 2026-09-03
urteil: zurueck
kriterium_geprueft: Die drei Saetze der berichtigten Abnahme einzeln — T1/T2 auf C++20 samt der drei Ueberlaufmassnahmen, die fuenf namentlich genannten Rust-Merkmalstellen auf Neufassung, und jede der fuenfzehn verbliebenen Rust-Zeilen daraufhin, ob sie Rust als Bauart vorschreibt; dazu die Stacktabelle und T6b gegen die abgelegten Messartefakte.
befunde: 3
---

# Pruefung 0011-stack-auf-cpp — erste Runde

Geprueft gegen die **berichtigte** Fassung des Abnahmekriteriums vom 2026-09-02 und
gegen nichts sonst. Fuer dieses Paket gab es bisher keine Pruefung; dies ist Runde 1.

Der dritte Satz des Kriteriums ist erfuellt, der erste weitgehend. Zurueck geht das
Paket an zwei Stellen des zweiten Satzes — `overflow-checks` und `cargo vendor` sind
die einzigen zwei der fuenf genannten Rust-Merkmale, deren **Inhalt** die Uebersetzung
nicht vollstaendig ueberlebt hat — und an einer Luecke in der Erzwingung von T2. Alle
drei sitzen in `technik.md` und sind zusammen in einem Lauf zu schliessen.

---

## Befund 1 — Der Ersatz fuer `overflow-checks` erreicht die blanke Multiplikation nicht

**Wo:** `technik.md` T7, Massnahme 3 (Z. 496) und Massnahme 4 (Z. 499–513).

Die Vorfassung ersetzte den Ueberlaufschutz mit **einer** Einstellung, die *jede*
Rechenoperation deckte. Die Neufassung zaehlt die gedeckten Operationen einzeln auf, und
die Aufzaehlung ist nicht vollstaendig:

- Massnahme 3 (Z. 496): `__int128` fuer jeden Zwischenwert **einer Multiplikation-Division**.
- Massnahme 4.1 (Z. 504): Waechter genau dort, wo ein 128-Bit-Wert nach `i64` verengt wird.
- Massnahme 4.2 (Z. 510): *„Was nicht ueber `__int128` laeuft — **Additionen und
  Subtraktionen** auf `i64` —, benutzt `__builtin_add_overflow` und `__builtin_sub_overflow`."*

Die Menge {Multiplikation-Division, Addition, Subtraktion} laesst die **blanke
Multiplikation zweier `i64`** aus. Massnahme 1 (`-fwrapv`, Z. 467) macht deren Ueberlauf
zum *definierten* Umbruch, also still; Massnahme 2 meldet ihn nicht, was das Dokument in
seinem eigenen Einschub (Z. 482–494) selbst nachweist. Damit trifft die Ueberschrift von
T7 — *„Ueberlauf erzeugt nie still eine falsche Zahl"* — auf diese Operationsart nicht zu.

**Wie man den Fehler erzeugt**, mit den Groessen dieses Dokuments und ohne eine Zeile
Erfindung:

1. T50, Z. 369: `tsd_in_cent(x) = x · 100.000`. Keine Division, also nach Massnahme 3
   kein `__int128`; keine Addition, also nach Massnahme 4.2 kein Baustein; kein
   128-Bit-Zwischenwert, also nach Massnahme 4.1 kein Waechter. Der Bauagent darf
   `return x * 100'000;` schreiben, und keine Vorgabe haelt ihn auf.
2. Das Dokument kennt die Schranke selbst — Z. 1563: *„`x · 100.000` verlaesst den Bereich
   ab `|x| > 9,2 · 10^13` Tausend USD."*
3. `positionswert(p) = tsd_in_cent(stufen(p) · stufenwert(p))` (Z. 1656) fuehrt zwei
   solche Multiplikationen hintereinander aus, `fondsanteil` (Z. 1655) eine dritte
   (`|stufen| · stufenweite`). Ueberschreitet der Eingabewert die Schranke, liefert
   `positionswert` unter `-fwrapv` eine umgebrochene, plausibel aussehende Zahl —
   und die geht nach T47 direkt ins Fondsvermoegen, also in Abrechnung, Mandat,
   Todesart 1 und die Botzielgroesse `B`.

**Was den Befund nicht aufhebt, aber dazugehoert:** Invariante 5 (Z. 1727) begrenzt
`markt.wert` je Runde auf denselben Bereich und faengt damit *einen* Aufrufer von
`tsd_in_cent` ab — nachtraeglich, am Rundenende, und nicht auf der Fondsseite
(`positionswert`, `beteiligung_wert`). Ein Detektor nach der Tatsache ist nicht die
Zusage, die T7 in seiner Ueberschrift gibt.

**Warum das unter das Kriterium faellt:** `overflow-checks` ist eines der fuenf
namentlich genannten Rust-Merkmale, und der Auftrag sagt in seinem ersten Satz *„Der
Inhalt bleibt. … Nur die Bauart wird ausgetauscht."* Hier ist mit der Bauart ein Stueck
Inhalt verschwunden. Die Behebung ist eine Zeile: `__builtin_mul_overflow` als dritter
Baustein in Massnahme 4.2 — oder die Ansage, dass **jede** Multiplikation ueber den
`__int128`-Weg mit dem Waechter aus 4.1 laeuft.

---

## Befund 2 — `cargo vendor` ist gestrichen, nicht neu gefasst; die Zusage dahinter fehlt

**Wo:** `technik.md` T1 (Z. 88–91), gegen die Vorfassung.

Die Vorfassung (`git show bbaee82:specs/0016-…/technik.md`, Z. 66–68) sagte:

> **T1 — Kern, Datenschicht, Schnittstelle, Pruefstand und Werkzeuge in Rust**, stabile
> Toolchain, in `rust-toolchain.toml` auf eine Version festgenagelt, Abhaengigkeiten
> mit `cargo vendor` im Repo eingefroren.

Der Satz hat zwei Haelften. Die erste ist uebersetzt — `werkzeugkette.cmake` steht
wortgleich an der Stelle von `rust-toolchain.toml` (Z. 89–90). Die zweite ist ersatzlos
weg.

**Wie man das nachprueft:** `grep -niE 'eingefroren|festgenagelt|FetchContent|find_package|
Netz|Versionsupdate|spiegel'` ueber `technik.md`. Sieben Treffer, kein einziger sagt etwas
ueber die Fassung einer Fremdbibliothek. Der naechstliegende (Z. 1029, *„Der Bau des Spiels
laedt **nichts** aus dem Netz"*) steht in T23 und handelt vom Jahrgangsbau aus den
eingefrorenen Rohdateien; er verbietet ausserdem nur das *Herunterladen*, waehrend ein
`find_package(… REQUIRED)` gegen die zufaellig installierte Systemfassung nichts
herunterlaedt und trotzdem genau den Schaden anrichtet, den `cargo vendor` ausschloss.

**Wie der Fehler entsteht:** T3 (Z. 181–187) laesst die Bibliothek fuer `daten` (Leser
fuer `parameter.toml`), `schnittstelle`, `pruefstand` und `werkzeuge` ausdruecklich
`offen`. Ein spaeteres Paket waehlt eine — und findet keine Vorgabe, die sie an eine
Fassung bindet oder ins Repo zwingt. Zwei Uebersetzungen im Abstand von drei Monaten
koennen dann verschiedene Fassungen des Parameterlesers benutzen; der Rueckvergleich
prueft danach gegen ein Programm, das niemand identisch wiederherstellen kann. Genau das
war die Zusage der gestrichenen Haelfte.

**Was den Befund mildert:** Heute hat das Vorhaben null tatsaechliche
Fremdabhaengigkeiten (T2 fuer den Kern, T3 „offen" fuer alle uebrigen), es ist also
nichts kaputt, sondern etwas unbewacht. Die Behebung ist ein Satz in T1 oder T3.
Das Kriterium nennt `cargo vendor` beim Namen unter den Stellen, die **neu gefasst**
sein muessen; eine geloeschte Stelle ist nicht neu gefasst.

---

## Befund 3 — Die Erzwingung von T2 prueft eine Datei, die Luecke liegt in der Nachbardatei

**Wo:** `technik.md` T2 (Z. 148–154).

T2 sagt, die Nullabhaengigkeit des Kerns sei *„eine Eigenschaft der `CMakeLists.txt` des
Kerns …, mit zwei Mustervergleichen ueber **diese eine Datei**"* — der erste sucht
hereingeholten Fremdcode, der zweite *„jede Bibliothek, die an `kern` gelinkt wird"*.
Beide muessen leer ausgehen.

Der zweite Vergleich kann sein Ziel nicht treffen, wenn er nur diese Datei liest.

**Wie man den Fehler erzeugt** (CMake ≥ 3.13; verlangt sind 3.22, `CMakeLists.txt:25`
und `kern/CMakeLists.txt:19`):

- Variante A: `link_libraries(fremd)` in `ventures/0016-…/CMakeLists.txt` vor Zeile 45
  einfuegen. Es gilt fuer jedes danach angelegte Ziel, also auch fuer `kern` aus
  `add_subdirectory(kern)`.
- Variante B: `target_link_libraries(kern PRIVATE fremd)` an das Ende derselben Datei
  schreiben. Seit CMake 3.13 ist das fuer ein Ziel aus einem anderen Verzeichnis erlaubt.

In beiden Faellen bleiben beide Mustervergleiche ueber `kern/CMakeLists.txt` leer, und
der Kern linkt eine Fremdbibliothek. T2 waere formal erfuellt und sachlich gebrochen.
Dasselbe gilt fuer den ausgeschriebenen Wortlaut in der Abnahme von Paket 0004,
Bedingung 3 — auch er liest nur `kern/CMakeLists.txt` —, aber geschlossen gehoert die
Luecke in der Vorgabe.

**Dass die Bauform bekannt ist, zeigt dieselbe Neufassung:** T13 (Z. 750–755) sieht
genau dieses Problem auf der Kopfseite und schliesst es — *„`include_directories()` ist
deshalb im ganzen Vorhaben verboten"*. Die Linkseite hat keinen solchen Satz. Es fehlt
die zweite Haelfte eines Gedankens, den der Entwurf schon hatte, nicht ein neuer Gedanke.

---

## Wonach ich gesucht und nichts gefunden habe

Damit diese Pruefung von einer nicht stattgefundenen unterscheidbar ist:

**Satz 3 des Kriteriums — „keine Zeile schreibt Rust mehr als Bauart vor": erfuellt.**
`grep -niE 'rust|cargo|rustc'` findet **15** Zeilen, jede einzeln gelesen und
zugeordnet: abgeloeste Vorfassung (Z. 31, 33, 57, 91, 114, 550), gemessener Kandidat
(Z. 102, 122), Pfad nach `messung-stack/` (Z. 437), Gegenueberstellung zur C++-Loesung
(Z. 211, 403, 463, 492, 654, 657). Keine schreibt etwas vor. Kein Treffer auf `.rs`,
`Cargo.toml`, `crates.io`, `egui`, `kern/src/*.rs`, `Kastenrichtung`; keine
Rust-Syntaxreste (`fn `, `pub `, `#[…]`, `#![…]`, `impl `, `Vec<`, `Option<`, `Result<`,
`unwrap()`, `panic!`). Die beiden „Kasten"-Treffer (Z. 143, 684) sind deutsches Wort,
kein Crate.

**Satz 1 — T1 und T2 nennen C++20: erfuellt.** T1 (Z. 88) legt C++20, `g++`, CMake und
`werkzeugkette.cmake` fest. Die Tabelle (Z. 99–106) fuehrt sechs Kandidaten an fuenf
Kriterien dieses Vorhabens, vier davon gemessen; Go und C# sind als *nicht gemessen*
ausgewiesen statt weggelassen. Die vier Messzeilen habe ich gegen
`messung-stack/BEFUND.md` gelegt: 494 / 947 / 316 / 50.383 ns und die Pruefsumme
`1163237642073673` stimmen zeilenweise; die abgeleiteten Faktoren 1,92 (947/494), 3,0
(947/316) und 53,2 (50.383/947) sind nachgerechnet und richtig.

**Die drei Ueberlaufmassnahmen sind alle drei da**, jede mit einem Ort statt einer
Erwaehnung: `-fwrapv` in T7 Massnahme 1 (Z. 467) und im Frontmatter, Sanitizer in T7
Massnahme 2 (Z. 475) und T2b Punkt 2, `__int128` in T6 (Z. 411, mit ausdruecklichem
Verweis auf ADR 0011 Massnahme 3) und T7 Massnahme 3. Dass `-fwrapv` nicht im Absatz von
T1 selbst steht, zaehle ich nicht als Fehlstelle: Der Auftrag fuehrt die Massnahmen als
eigenen Punkt neben T1 und T2, und T1 verweist auf T7.

**T6b habe ich gegen die Artefakte geprueft, nicht gegen die Behauptung** — das ist der
belastbarste Teil der Neufassung. `nm -C messung-stack/cpp/schritt` zeigt
`__divmodti4@GCC_7.0.0` als undefiniertes Symbol; im Rust-Programm findet sich
`__udivti3` und **kein** `__divti3`. Die Tabelle in Z. 434–437 stimmt also. Und
`messung-stack/cpp/schritt.cpp:21–31` benutzt `__int128` — die Vermutung in ADR 0011,
die 947 ns haetten an einem fehlenden `__int128` gelegen, ist damit widerlegt, wie T6b
schreibt; die Zeilen 23–28 zeigen die signierte Division samt Rest und das zusaetzliche
128-Bit-Produkt `rest_betrag * 2`, auf das T6b die Differenz zurueckfuehrt.

**Drei der fuenf Rust-Merkmale sind sauber uebersetzt:** Division gegen null → T6
(Z. 402–409, mit `[expr.mul]` und dem Hinweis, dass es vor C++11 implementierungsabhaengig
war, was den Sprachstand aus T1 bindend macht); `BTreeMap` → T9 (Z. 651–655, `std::map`
/`std::set`, `unordered_*` verboten, dazu die beiden C++-eigenen Fallen `std::sort` und
Argumentauswertung); `forbid(unsafe_code)` → T2b (Z. 156–175, Warnsatz mit `-Werror`,
Sanitizer, Zeigerfreiheit als Grep-Regel).

**Nicht ausgefuehrt, und das gehoert hierher:** Ich konnte in diesem Lauf keine
Uebersetzungsprobe schreiben — `Write` und jeder `Bash`-Aufruf, der eine Datei ausserhalb
des Repos anlegt, endete mit *„Permission to use … has been denied because Claude Code is
running in don't ask mode"*. Die Aussagen zu `#pragma GCC poison` auf Schluesselwoertern,
zu `-Wpedantic` gegen `__int128` und zur Abschaltung von `-fsanitize=signed-integer-overflow`
durch `-fwrapv` habe ich deshalb am Text und an der im Dokument zitierten Quelle geprueft
(Kernel-Patch „ubsan: remove overflow checks", Z. 534–537), nicht am laufenden Uebersetzer.
Befund 1 haengt nicht daran: Er folgt aus der Aufzaehlung in Massnahme 4 und aus den
Formeln des Dokuments selbst.

## Was ausdruecklich kein Befund ist

- **Go und C# ohne Messwerte in der Stacktabelle.** Ausgewiesen statt weggelassen, das
  ist die richtige Form.
- **`-Wpedantic` fehlt im Warnsatz.** In T2b begruendet, und die Begruendung traegt:
  `__int128` ist nach T6 verpflichtend.
- **Die vierte Ueberlaufmassnahme und der Widerspruch zu ADR 0011** (Z. 482–494). Ein
  belegter, als Widerspruch gekennzeichneter Zusatz, der keine der drei Massnahmen
  aufhebt. Befund 1 sagt nicht, dass Massnahme 4 falsch ist, sondern dass sie eine
  Operationsart zu frueh aufhoert aufzuzaehlen.
- **`werkzeugkette.cmake` traegt zwei Warnschalter mehr als T2b und zusaetzlich
  `-fno-fast-math`.** Obermenge, andere Datei, anderes Paket (0031); T2b nennt seine
  Liste nicht abschliessend.
- **Der Satz „`technik.md` sagt an zehn Stellen weiter Rust"** in den Paketen 0004, 0008
  und 0016. Nach dieser Neufassung falsch, aber in erledigten Paketen und ohne Wirkung
  auf einen Bau — kein Befund gegen 0011 und keinen eigenen Lauf wert.
- **Aufbau, Benennung, Laenge.** Wo `specs/` schweigt, gilt die Entscheidung des
  Bauagenten.

## Kein Arbeitspaket vorgeschlagen — mit Grund

Alle drei Befunde sitzen in `technik.md`, also in genau der Datei, die 0011 in seinem
Feld `dateien` haelt. Ein eigenes Paket wuerde sich mit 0011 auf derselben Datei
schneiden — die Kollision, gegen die die Einplanung durch den Projektmanager gebaut ist.
Die Behebung ist ein Satz in Massnahme 4.2, ein Satz in T1 oder T3 und ein Satz in T2
oder T13; das gehoert in den Ruecklauf von 0011 und nicht in drei neue Kennungen.
