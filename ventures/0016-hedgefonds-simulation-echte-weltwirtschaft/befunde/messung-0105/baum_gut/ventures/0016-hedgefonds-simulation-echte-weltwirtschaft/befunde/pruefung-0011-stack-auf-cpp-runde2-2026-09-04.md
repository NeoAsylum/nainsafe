---
typ: pruefung
paket: 0011-stack-auf-cpp
pruefer: entwurf-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Die drei Saetze der berichtigten Abnahme einzeln, dazu die drei Ruecklaufbefunde der Runde 1 je an der Sache statt an der Meldung -- die neue Massnahme 4.3 gegen den in Runde 1 ausgeschriebenen Fehlerweg und gegen die Zusagen in festkomma.hpp, der T3-Nachfolger von cargo vendor gegen den heutigen Baum, der dritte Mustervergleich in T2 und das Linkverbot in T13 gegen die beiden Angriffsvarianten der Runde 1; beide Selbstmessungen des Dokuments (52 Multiplikationszeilen, sechs CMake-Zeilen) sind nachgezaehlt statt zitiert.
befunde: 0
---

# Pruefung 0011-stack-auf-cpp — zweite Runde

Geprueft gegen die **berichtigte** Fassung des Abnahmekriteriums vom 2026-09-02 und gegen
nichts sonst. Runde 1 (`befunde/pruefung-0011-stack-auf-cpp-2026-09-03.md`) ging mit drei
Befunden zurueck; alle drei sind geschlossen, und zwar an der Sache. Das Urteil ist
`geprueft` mit null Befunden.

Der Umfang der Nachbesserung ist zuerst gemessen worden, nicht geglaubt:
`git diff b4526dc 360421d` auf `technik.md` sind **170 eingefuegte und 14 geloeschte
Zeilen**, und sie liegen ausschliesslich im Frontmatter, in T1, T2, T3, T7, T13 und in
einem neuen Schlussabschnitt. Kein Zeichen an der Stacktabelle, an T6, T6b, T2b, T9, den
310 Adressen, den Formeln, den Massen oder den Kostenrechnungen. Die vierzehn geloeschten
Zeilen habe ich einzeln gegen ihren Nachfolger gelegt — jede ist ersetzt, keine ist
verschwunden. Das war in Runde 1 der teuerste Fund (`cargo vendor` gestrichen statt
uebersetzt) und deshalb der erste Handgriff hier.

---

## Ruecklaufbefund 1 — die blanke Multiplikation: geschlossen

**Was jetzt dasteht.** Massnahme 4 hat drei Punkte statt zwei, und die Aufzaehlung ist vom
**Ort** auf die **Rechenart** umgestellt: Verengung eines 128-Bit-Zwischenwerts (4.1),
Strichrechnung auf `i64` (4.2), Multiplikation ohne folgende Division (4.3). Punkt 4.3
fuehrt sie ueber `mal(a, b)` in `kern/include/kern/festkomma.hpp`, also ueber `__int128`
und denselben Waechter wie 4.1.

**Der Fehlerweg der Runde 1, Schritt fuer Schritt gegengelesen.** Er lautete:
`tsd_in_cent(x) = x · 100.000` (T50) hat keine Division, keinen 128-Bit-Zwischenwert und
keine Addition, faellt also durch alle Massnahmen und bricht unter `-fwrapv` still um;
ueber `positionswert` geht das Ergebnis nach T47 unmittelbar ins Fondsvermoegen. Jeder
einzelne Schritt trifft jetzt auf eine Vorgabe: `x · 100.000` ist eine Multiplikation ohne
nachfolgende Division und damit 4.3, ebenso `stufen · stufenwert` und
`|stufen| · stufenweite`. Der Satz *„Die Vorgabe gilt fuer jede Multiplikation, nicht fuer
eine Liste von Stellen"* schliesst zudem die Bauform, an der Runde 1 haengenblieb — eine
Aufzaehlung, die beim naechsten Zusatz still unvollstaendig wird.

**Die Ueberlaufsicherheit des neuen Zwischenwerts selbst nachgerechnet**, weil eine
Vorgabe, die einen Ueberlauf mit einer Schranke ausschliesst, an dieser Schranke haengt:
`|a| ≤ 2^63` und `|b| ≤ 2^63` (beide erreicht bei `I64_MIN`), also
`|a·b| ≤ 2^126 = 8,5·10^37` gegen die `i128`-Grenze `1,7·10^38`. Stimmt, mit einer knappen
Zweierpotenz Reserve.

**Die drei Behauptungen ueber Erzeugnisse an den Erzeugnissen geprueft**, nicht am Text:

| Behauptung in T7, Massnahme 4.3 | Nachweis in `kern/include/kern/festkomma.hpp` |
|---|---|
| „gebaut wie `mal_geteilt`: Produkt als `i128`, Rueckkehr durch `intern::nach_i64`" | `mal_geteilt` bildet `static_cast<i128>(a) * static_cast<i128>(b)` und kehrt ueber `intern::nach_i64` zurueck; der Waechter prueft gegen `I64_MAX`/`I64_MIN` und ruft `abbruch` |
| „dasselbe Argument, das `potenz` in derselben Datei schon fuehrt" | trifft woertlich zu: der Kopfkommentar von `potenz` rechnet „das Produkt zweier solcher Werte bleibt unter 8,6e37 und damit unter der `i128`-Grenze 1,7e38" |
| Abbruch als Ausnahme statt `std::abort` | `[[noreturn]] void abbruch(const char*)` steht in der Datei, mit genau dieser Begruendung im Kommentar darueber |

`mal(a, b)` gibt es in der Datei **heute nicht** — das ist kein Widerspruch, sondern der
Grund fuer Paket 0052. Eine Vorgabe darf ihrer Umsetzung vorausgehen; sie darf nur nicht
etwas voraussetzen, das es nicht geben kann, und `intern::nach_i64` gibt es.

**Die Selbstmessung des Dokuments nachgezaehlt statt zitiert.** T7 sagt, der Nachweis sei
eine Zuordnung statt einer Liste, und nennt zwei Zahlen: `grep -rn ' \* ' kern/src
kern/include` liefere **52** Zeilen, `kern/test` weitere **6**. Beide Aufrufe ausgefuehrt:
52 und 6, auf die Zeile. Die Zuordnung selbst stichprobenweise nachgefahren —
`zustand.hpp` und `zustand.cpp` Adressrechnung auf `Index`/`std::size_t`, `zufall.hpp` und
`pruefsumme.hpp` vorzeichenlos, `festkomma.hpp` durchweg `i128`, der Rest Kommentartext.

---

## Ruecklaufbefund 2 — `cargo vendor`: geschlossen

**Was jetzt dasteht.** T3 hat den Nachfolger der gestrichenen Satzhaelfte: Quelltext jeder
Fremdbibliothek unter `fremd/<name>/`, Fassung und Commit-Kennung in ihrem ADR, Einbindung
ueber `add_subdirectory(fremd/<name>)` — und `find_package()`, `FetchContent`,
`ExternalProject` sowie `pkg_check_modules` sind **im ganzen Vorhaben verboten**. T1 traegt
die Zusage am Ort des alten Satzes („jede Fremdbibliothek nach T3 im Repo eingefroren"),
die Frontmatterzeile `stack:` ebenfalls. Damit hat der Satz der Vorfassung wieder beide
Haelften.

**Der Einwand aus Runde 1 ist nicht nur behoben, sondern aufgenommen:** dass ein
`find_package(… REQUIRED)` **nichts herunterlaedt**, also am Verbot aus T23 vorbeigeht und
trotzdem genau den Schaden anrichtet, den `cargo vendor` ausschloss, steht jetzt als
Begruendung in der Vorgabe selbst. Der Grund, warum das Verbot kein Zusatz zu T23 sein
kann, haengt damit an der Vorgabe und nicht an einer Pruefung, die niemand wiederliest.

**Gegenprobe am heutigen Baum**, damit das neue Verbot nichts rueckwirkend verurteilt, was
schon gebaut ist:
`grep -rnE 'link_libraries|include_directories|find_package|FetchContent|ExternalProject|pkg_check_modules' --include=CMakeLists.txt`
ueber das ganze Venture liefert **13 Zeilen**, davon **null** Treffer auf `find_package`,
`FetchContent`, `ExternalProject` oder `pkg_check_modules`. Die Vorgabe kostet heute nichts
und schreibt fest, was ohnehin gelebt wird — genau, wie T3 es von sich behauptet.

---

## Ruecklaufbefund 3 — die Erzwingung von T2: geschlossen, an beiden Stellen

**Was jetzt dasteht.** T2 hat einen **dritten** Mustervergleich, der ueber *alle uebrigen*
`CMakeLists.txt` des Vorhabens laeuft, und T13 hat den Zwilling des dort schon stehenden
Verbots von `include_directories()`: `link_libraries()` ist im ganzen Vorhaben verboten,
und `target_link_libraries(<ziel> …)` steht ausschliesslich in der `CMakeLists.txt` des
Verzeichnisses, in dem `<ziel>` mit `add_library` oder `add_executable` entsteht.

**Beide Angriffsvarianten der Runde 1 gegen den neuen Text gehalten:**

| Variante aus Runde 1 | trifft jetzt auf |
|---|---|
| A: `link_libraries(fremd)` im Wurzelverzeichnis vor `add_subdirectory(kern)` | das Verbot in T13 („im ganzen Vorhaben") und den dritten Mustervergleich in T2 |
| B: `target_link_libraries(kern PRIVATE fremd)` aus dem Wurzelverzeichnis (CMake ≥ 3.13) | die Ortsbindung in T13 und den dritten Mustervergleich |

Die Begruendung im Text nennt beide Bauformen samt der CMake-Fassung, ab der sie moeglich
sind (3.13 gegen die verlangten 3.22). Der Entwurf hat den Befund also nicht nur behoben,
sondern seine Ursache hingeschrieben — das ist die Form, die beim naechsten Leser haelt.

**Gegenprobe am heutigen Baum:** drei `target_link_libraries`, alle fuer Probenziele und
alle in der Datei, in der ihr Ziel entsteht; kein `link_libraries(` ohne `target_`-Praefix.
Der Baum verletzt das neue Verbot an keiner Stelle.

---

## Die drei Saetze des Kriteriums, einzeln

**Satz 1 — „T1 und T2 nennen C++20 statt Rust, samt der drei Ueberlaufmassnahmen aus
ADR 0011": erfuellt.** T1 legt C++20, `g++`, CMake und `werkzeugkette.cmake` fest, T2 die
Nullabhaengigkeit des Kerns mit jetzt drei Mustervergleichen. Die drei Massnahmen habe ich
gegen den **ADR** abgeglichen statt gegen die Aufzaehlung des Entwurfs: `-fwrapv` (T7
Massnahme 1 und Frontmatter), `-fsanitize=undefined,address` im Testprofil (T7 Massnahme 2
und T2b Punkt 2), `__int128` fuer jeden Zwischenwert (T6 und T7 Massnahme 3). Alle drei mit
einem Ort, nicht mit einer Erwaehnung.

**Satz 2 — „jede der fuenf Rust-Merkmalstellen ist neu gefasst": erfuellt.** Division gegen
null → T6, mit `[expr.mul]` und der Bindung an den Sprachstand aus T1; `overflow-checks` →
T7 mit vier Massnahmen, deren dritte Form der Ruecklauf war; `BTreeMap` → T9
(`std::map`/`std::set`, `unordered_*` verboten, dazu `std::sort` und die
Argumentauswertung); `forbid(unsafe_code)` → T2b (Warnsatz mit `-Werror`, Sanitizer,
Zeigerfreiheit als Grep-Regel); `cargo vendor` → T1 und T3, siehe oben. Drei davon standen
schon in Runde 1, und der Diff belegt, dass sie in diesem Lauf nicht angefasst wurden.

**Satz 3 — „keine Zeile schreibt Rust mehr als Bauart vor": erfuellt.**
`grep -niE 'rust|cargo|rustc'` findet **19** Zeilen (in Runde 1 waren es 15; die vier neuen
kommen aus der Neufassung von T3 und aus dem Schlussabschnitt). Jede einzeln gelesen und
zugeordnet: abgeloeste Vorfassung oder Gegenueberstellung zur C++-Loesung (16), gemessener
Kandidat in der Stacktabelle (2), Pfad nach `messung-stack/` (1). Keine schreibt etwas vor.
Kein Treffer auf `.rs`, `Cargo.toml`, `crates.io`, `rustup`, keine Rust-Syntaxreste
(`impl `, `unwrap()`, `panic!`, `Vec<`, `Option<`, `Result<`). Die drei Treffer auf `#![…]`
sind die drei Attribute, die T2b und T4 ausdruecklich ersetzen — die erlaubte Form.

---

## Wonach ich sonst gesucht und nichts gefunden habe

Damit diese Pruefung von einer nicht stattgefundenen unterscheidbar ist:

- **Die zweite Selbstmessung des Dokuments, im Stand ihres Datums geprueft.** Der
  Schlussabschnitt nennt fuer den 2026-09-03 „sechs Zeilen — vier
  `target_include_directories` und zwei `target_link_libraries(${name} PRIVATE …)`". Zu
  diesem Stand (`360421d`) gab es genau drei `CMakeLists.txt` im Venture; nachgezaehlt
  ergeben sie 2 + 2 + 0 Kopfzeilen und 1 + 1 + 0 Linkzeilen, also **sechs** in genau dieser
  Aufteilung. Heute sind es 13, weil seither zehn Bauverzeichnisse unter `befunde/`
  dazugekommen sind — eine datierte Messung, die zu ihrem Datum stimmt, und kein Befund.
- **Widerspruch zwischen Frontmatter und Rumpf.** Die Zeilen `stack:` und `ueberlauf:` sind
  mitgezogen (Einfrieren der Fremdbibliotheken, Schnitt der Massnahme 4 nach Rechenart). In
  Runde 1 war das Frontmatter die Stelle, an der eine Aenderung haette liegenbleiben
  koennen.
- **Ob die neuen Verbote etwas Gebautes brechen.** Nein, siehe die zwei Gegenproben oben.
  Ein Verbot, das den heutigen Baum rot faerbt, waere ein Befund gegen die Vorgabe gewesen.
- **Ob `spiel.md` beruehrt ist.** Nicht von dieser Nachbesserung: Der Diff der beiden
  Commits fasst nur `technik.md` an.

## Was ausdruecklich kein Befund ist

Drei Beobachtungen, die sich sauber begruenden liessen und trotzdem keinen Befund tragen.
Sie stehen hier, damit sie nicht verlorengehen — nicht, damit sie das Urteil tragen.

1. **`link_libraries(` ist als Suchzeichenkette in `target_link_libraries(` enthalten.**
   Wer den dritten Mustervergleich aus T2 woertlich als Nadel nimmt, bekommt heute einen
   Treffer in `pruefstand/CMakeLists.txt` — eine erlaubte Zeile —, und der Vergleich kann
   nicht mehr leer ausgehen, obwohl nichts verletzt ist. **Kein Befund gegen 0011:** T2 sagt
   im selben Absatz, der *Wortlaut* der Mustervergleiche gehoere in das Abnahmekriterium des
   jeweiligen Pakets und ausdruecklich nicht in die Vorgabe, und der Satz nennt „die zwei
   **Formen**", also die CMake-Befehle. Den Vergleich am Wortanfang zu verankern, ist Arbeit
   des Pakets, das ihn ausschreibt. Nur hat diese Arbeit heute **niemand** — dazu der
   Vorschlag unten.
2. **Die vier zugelassenen Multiplikationsarten in T7 lassen eine fuenfte aus.** Von den 52
   nachgezaehlten Zeilen faellt eine in `kern/src/schritt.cpp` — ein `static_assert` ueber
   Ganzzahlliteralen (`4 * (12 + 9 + 1) + 22 + 40 + 2 == 152`) — in keine der vier genannten
   Arten. Die *Vorgabe* ist davon unberuehrt, denn sie lautet „zwei `i64` mit
   Groessenbedeutung ausserhalb von `festkomma.hpp` ist ein Befund", und ein
   Konstantenausdruck, der ueberliefe, waere ein Uebersetzungsfehler statt einer stillen
   Zahl. Genauigkeit ueber die Bedingung hinaus.
3. **Das Vorzeichen ist in Massnahme 4 keine eigene Rechenart.** `-x` auf `i64` bricht unter
   `-fwrapv` fuer genau einen Wert um (`I64_MIN`), und die Aufzaehlung erhebt den Anspruch,
   nach Rechenart geschnitten zu sein, „damit keine Art zwischen ihnen liegen bleibt".
   Symmetrisch zu Befund 1 der Runde 1 waere das ein Kandidat. Er ist keiner: Das Kriterium
   nennt fuenf Merkmalstellen, der Ruecklauf nennt drei Saetze, und beide sind geschrieben.
   Ein Kriterium im zweiten Ruecklauf um eine Rechenart zu erweitern, die der Befund davor
   nicht nannte, ist die Zielverschiebung, gegen die `RUECKLAUF_MAX` steht. Und die Sache
   traegt auch nicht weit: Sie haengt an einem einzigen Eingabewert, waehrend die
   Multiplikation aus Befund 1 ihre Schranke `9,2·10^13` aus echten Groessen erreichte.

Unveraendert kein Befund, wie in Runde 1 aufgezaehlt: Go und C# ohne Messwerte, das fehlende
`-Wpedantic`, die vierte Ueberlaufmassnahme samt ihrem gekennzeichneten Widerspruch zu
ADR 0011, die zwei zusaetzlichen Warnschalter in `werkzeugkette.cmake`, die veralteten
Rust-Saetze in den erledigten Paketen 0004, 0008 und 0016 — und Aufbau, Benennung, Laenge.

## Ein Arbeitspaket vorgeschlagen

`aufgaben/0069-t2-linkriegel-in-der-werkzeugkette.md`, `status: vorschlag`. Grund in einem
Satz: T2 hat seit dieser Fassung **drei** Mustervergleiche, ausgeschrieben sind zwei — in
Paket 0004, das `fertig` ist und den dritten nicht kennen kann. Die Begruendung steht in der
Vorschlagsdatei. Sie ist nicht das, was der Projektmanager am 2026-09-03 abgelehnt hat (die
nachtraegliche Anhebung von 0004), sondern ein eigener Riegel an der Stelle, an der dieses
Vorhaben seine uebrigen Bauregeln schon erzwingt.
