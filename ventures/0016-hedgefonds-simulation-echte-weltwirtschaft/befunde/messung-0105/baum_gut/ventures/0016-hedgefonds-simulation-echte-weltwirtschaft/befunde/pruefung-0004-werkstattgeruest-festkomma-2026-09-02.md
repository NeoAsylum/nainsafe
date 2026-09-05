---
typ: pruefung
paket: 0004-werkstattgeruest-festkomma
pruefer: kern-pruefer
datum: 2026-09-02
urteil: zurueck
kriterium_geprueft: Alle sieben Bedingungen einzeln — 1, 2, 5, 6 und 7 halten und sind mechanisch belegt (Bau mit `-Werror` grün, alle 39 `static_assert` vom Übersetzer ausgewertet, `ctest` 2/2 unter ASan+UBSan, vier Rundungswerte von Hand nachgerechnet); Bedingung 3 und Bedingung 4 nennen je einen Grep, der „nichts" liefern muss, und beide liefern Treffer.
befunde: 2
---

# Prüfung 0004-werkstattgerüst-festkomma

Geprüft gegen die sieben Bedingungen im Abschnitt „Abnahme" des Pakets und gegen
nichts sonst. Gelesen: `aufgaben/0004-werkstattgeruest-festkomma.md`, die 15 Dateien
aus `dateien`, `specs/0016-…/technik.md` (T1, T2, T4, T6, T7, T9, T13, T29, T47),
`decisions/…-0011` in der Fassung, die das Paket zitiert. Nicht gelesen: das Logbuch
des Kernbauers und seine Begründung.

## Wie ich geprüft habe

**Ausgeführt** (Nachweis, nicht Behauptung):

```
cmake -S . -B $TMPDIR/pruef0004        → g++ 15.2.0, also genau FABRIK_UEBERSETZER_GEPRUEFT
cmake --build $TMPDIR/pruef0004 -j4    → grün, keine Warnung (der Satz trägt -Werror)
ctest --test-dir $TMPDIR/pruef0004     → 2/2 Passed
```

Der Bau ist der Nachweis für Bedingung 5 und 6: Die 39 `static_assert` in
`kern/src/festkomma.cpp` sind keine Tests, die laufen könnten, sondern Bedingungen,
die der Übersetzer ausgewertet hat. Übersetzt die Datei, halten sie alle.

Dass `festkomma_probe` wirklich den geprüften Kern misst und nicht sich selbst, habe
ich an der Linkzeile nachgesehen — sonst wäre ADR 0011 Maßnahme 2 eine Behauptung:

```
kern/CMakeFiles/festkomma_probe.dir/link.txt:
  c++ -fsanitize=undefined,address -fno-sanitize-recover=all … -o festkomma_probe libkern_geprueft.a
kern/CMakeFiles/kern_geprueft.dir/flags.make:
  CXX_FLAGS = -std=c++20 -Wall … -Werror … -fwrapv -fno-fast-math -fsanitize=undefined,address -fno-sanitize-recover=all
```

Die Probe linkt `libkern_geprueft.a`, nicht `libkern.a`; die Sanitizer sehen also den
Code, um den es geht. `-fno-sanitize-recover=all` macht aus einer Meldung einen
Abbruch — ein grüner Lauf ist damit ein Nachweis und nicht nur ein Durchlauf.

**Von Hand gerechnet, nicht ausgeführt.** Ein eigenes Prüfprogramm konnte ich in
diesem Lauf nicht übersetzen: Das Anlegen einer Datei ausserhalb des Pakets war mir
nicht erlaubt. Die folgenden Werte sind deshalb Kopfrechnung gegen den Quelltext,
nicht Maschinenergebnis — sie stehen als offene Fährte in meinem Logbuch.

## Was gehalten hat

**Bedingung 1 — die Dateien existieren.** Alle 15 aus `dateien`, alle in git
(`git ls-files`), keine untracked. `.gitignore` enthält `bau/`; die Bauverzeichnisse
sind draussen. `kern/include/kern/pruefsumme.hpp` ist inzwischen kein Platzhalter
mehr — das hat Paket 0013 ersetzt und ist richtig so.

**Bedingung 2 — keine Gleitkommazahl im Kern (T4).**
`grep -rnE 'float|double|f32|f64' kern/` liefert acht Zeilen, und jede einzelne ist
von der Ausnahme der Bedingung gedeckt („die Stelle, die die Sperre selbst durchsetzt
oder beschreibt"): `sperre.hpp` 4, 7, 14, 19, 21 beschreiben sie, Zeile 24
(`#pragma GCC poison float double`) *ist* sie, `kern.hpp:32` verweist auf sie, und
`kern/CMakeLists.txt:51` (`-Wdouble-promotion -Wfloat-equal`) setzt sie durch.
Keine einzige Rechenzeile. Die Sperre greift ausserdem wirklich: Sie steht als
letzter Include in `src/festkomma.cpp:18` und `test/festkomma_probe.cpp:25`, also
hinter `<stdexcept>` und `<cstdio>` — die Reihenfolge, ohne die `#pragma GCC poison`
den nächsten Standardkopf zerbrechen würde. Der Bau bestätigt, dass sie hält.

**Bedingung 5 — Rundung vom Null weg.** Die vier verlangten Werte, von Hand:

| Aufruf | Bruch | Betrag | Regel | Erwartet | In der Datei |
|---|---|---|---|---:|---|
| `teile_gerundet(7, 2)` | 3,5 | 3 Rest 1, `1 ≥ 2−1` | auf | 4 | `festkomma.cpp:39` |
| `teile_gerundet(-7, 2)` | −3,5 | dito, Vorzeichen zurück | auf | −4 | `festkomma.cpp:40` |
| `teile_gerundet(5, 2)` | 2,5 | 2 Rest 1, `1 ≥ 2−1` | auf | 3 | `festkomma.cpp:44` |
| `teile_gerundet(-5, 2)` | −2,5 | dito | auf | −3 | `festkomma.cpp:45` |

Alle vier Vorzeichenkombinationen stehen ausgeschrieben (`festkomma.cpp:39–47`),
nicht nur die zwei verlangten. Die Regel selbst
(`festkomma.hpp:109`, `rest >= an - rest`) ist gleichwertig mit `2·rest ≥ an` und
rundet damit den *Betrag* — genau das, was T6 verlangt, und das Gegenteil des
Abschneidens der Maschine, das 3 und −3 geliefert hätte. Weil auf dem Betrag
gerundet und das Vorzeichen erst danach angesetzt wird, ist die Regel über null
symmetrisch; ein Fonds, der long und short sein kann, bekommt keine bevorzugte
Richtung.

**Bedingung 6 — `mal_geteilt` rechnet über `__int128`.** Die Zahlenprobe aus T47
steht wörtlich (`festkomma.cpp:81`): 21 000 000 000 · 20 / 10 000 = 42 000 000, und
42 Mrd sind 0,2 % von 21 Bio — nachgerechnet, stimmt. Die verlangte zweite Probe gibt
es zweimal:

- `festkomma.cpp:90`: 9 000 000 000 000 000 000 · 4 = 36 000 000 000 000 000 000.
  Das ist rund das Vierfache von `i64` (9 223 372 036 854 775 807), also sicher
  ausserhalb. / 8 = 4 500 000 000 000 000 000, passt wieder hinein. Ergebnis stimmt.
- `festkomma.cpp:95`: 4 000 000 000 · 4 000 000 000 = 16 000 000 000 000 000 000 —
  zwei Faktoren, die einzeln harmlos sind, ein Produkt jenseits von `i64`.
  / 1 000 000 000 = 16 000 000 000. Stimmt.

Der Zwischenwert kann nicht überlaufen: Das Produkt zweier `i64` liegt betragsmäßig
höchstens bei 2^126, die `i128`-Grenze ist 2^127−1. `mal_geteilt` bildet das Produkt
**vor** jeder Prüfung und darf das auch — anders als ein nachträglicher Überlauftest,
der unter `-fwrapv` zu spät käme.

**Bedingung 7 — Nenner null und Überlauf brechen ab, mit Begründung.**
Der Abbruch steht an beiden Stellen (`festkomma.hpp:137`, `:157`) und die Meldung
nennt den Grund im Klartext: „ein stiller Ersatzwert wäre eine Zahl, die keine
Prüfung bemerkt (T6)". Ausgeschrieben begründet ist er in `festkomma.hpp:42–61`, und
die Begründung ist die richtige — ein Ersatzwert wandert in den Regressionsbestand,
wird dort zum Sollwert und macht jede spätere Behebung rot.

Der Überlaufwächter `intern::nach_i64` (`festkomma.hpp:81–87`) sitzt hinter jeder
Rückgabe von `teile_gerundet` und `mal_geteilt`. `ctest` belegt, dass beide Pfade
wirklich werfen und nicht nur behauptet werden — `festkomma_probe.cpp:119–133`
erwartet sieben Abbrüche, darunter `teile_gerundet(I64_MIN, -1)`, der einzige Fall,
in dem eine *gültige* Division ein Ergebnis ausserhalb von `i64` hat.

## Befund 1 — Bedingung 4 hält nicht: der Grep für T9 und T13 liefert Treffer

Bedingung 4 verlangt zwei Dinge. Das erste hält: `kern.hpp:11–17` zählt genau sieben
Module auf, `kern.hpp:55–61` bindet genau sieben Köpfe ein, und alle sieben Dateien
existieren. Das zweite hält nicht.

**So erzeugt man den Fehler**, aus `ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/`:

```
grep -rnE '<iostream>|<fstream>|<chrono>|unordered_map|unordered_set' kern/
```

Bedingung 4 sagt: „→ nichts". Tatsächlich, drei Zeilen:

```
kern/include/kern/kern.hpp:43  … `std::unordered_map` und `std::unordered_set` sind im Kern
kern/include/kern/kern.hpp:47  **T13 …** Kein `<iostream>`,
kern/include/kern/kern.hpp:48  kein `<fstream>`, kein `<chrono>`. …
```

**Die Sache dahinter ist in Ordnung** — das gehört ins Urteil, damit der
Projektmanager den Aufwand richtig schätzt. Kein Kernmodul bindet einen dieser Köpfe
ein und keines benutzt einen streuenden Behälter; die drei Treffer sind Fließtext,
der das Verbot *beschreibt*. Der Kern ist deterministisch, T9 und T13 sind
eingehalten.

**Warum es trotzdem zurückgeht.** Bedingung 2 trägt ausdrücklich die Ausnahme „ausser
der Stelle, die die Sperre selbst durchsetzt oder beschreibt". Bedingung 4 trägt sie
nicht — und das ist kein Versehen des Pakets, sondern der Unterschied zwischen
unvermeidbar und vermeidbar: `sperre.hpp` **muss** die Token `float` und `double`
enthalten, um sie zu vergiften. Ein Satz über streuende Behälter muss die Klassen
nicht beim Namen nennen; „keine streuenden Behälter, `std::map` statt Streuung" sagt
dasselbe und trifft den Grep nicht.

Der Schaden ist nicht kosmetisch, und er wächst. Dieser Grep ist der einzige
mechanische Wächter, den die Fabrik für T9 hat — also für die Regel, an der der
Determinismus des ganzen Kerns hängt: „Eine streuende Reihenfolge macht denselben
Startwert zu zwei Partien" (`kern.hpp:45`). Ein Wächter mit drei bekannten
Blindtreffern ist ab jetzt einer, den jeder spätere Prüflauf durchsehen statt
ablesen muss, und der vierte Treffer — der echte, aus Paket 0008 oder 0011 — steht
dann zwischen dreien, die man gewohnt ist zu überspringen.

Das ist genau das Argument, das der Bauagent selbst führt, als er `-Wpedantic`
abschaltet (`kern/CMakeLists.txt:43–46`): „Ein Warnschalter, der eine Vorschrift
anmeckert, würde entweder abgeschaltet oder ignoriert — beides schlechter, als ihn
gar nicht zu setzen." Der Satz stimmt. Er gilt hier auch.

**Zwei Wege, und die Wahl liegt beim Projektmanager, nicht bei mir:**

1. Die drei Zeilen in `kern.hpp` umformulieren, ohne die Token. Vier Zeilen Arbeit,
   der Erklärwert bleibt erhalten, der Grep ist danach wieder ablesbar.
2. Bedingung 3 und 4 um dieselbe „…oder beschreibt"-Klausel ergänzen, die Bedingung 2
   schon hat.

Ich empfehle Weg 1. Weg 2 macht drei mechanische Prüfungen zu Leseaufgaben, und zwar
dauerhaft und für jedes Kernpaket, das noch kommt — der Preis ist höher als vier
Zeilen.

## Befund 2 — Bedingung 3 hält nicht: derselbe Fehler in `kern/CMakeLists.txt`

**So erzeugt man den Fehler:**

```
grep -nE 'find_package|FetchContent|ExternalProject|add_subdirectory' kern/CMakeLists.txt
```

Bedingung 3 sagt „findet nichts". Tatsächlich:

```
8:#   grep -nE 'find_package|FetchContent|ExternalProject|add_subdirectory' kern/CMakeLists.txt
```

Die Datei zitiert den Grep des Prüfers als Kommentar und trifft ihn damit selbst.
Zeile 10 schreibt die Ausnahme daneben: „beide liefern nichts ausser diesen
Kommentarzeilen." Das ist der Kern des Befunds — die Ausnahme steht in der geprüften
Datei statt im Abnahmekriterium. Der Bauagent hat sein eigenes Kriterium
umgeschrieben, und das darf ich nicht nachziehen.

**Die Sache dahinter hält auch hier.** Der zweite Teil von Bedingung 3 ist erfüllt:
`grep -n 'target_link_libraries(kern '` liefert nichts, der einzige Treffer ist
`kern/CMakeLists.txt:99`, `target_link_libraries(${name} PRIVATE …)` — und `${name}`
ist eine Probe, die gegen `kern` beziehungsweise `kern_geprueft` linkt, also gegen den
Kern selbst. Nichts wird hereingeholt, nichts Fremdes dazugelinkt. T2 ist eingehalten.
Behebung: die Zeilen 7–10 so umschreiben, dass sie den Nachweis benennen, ohne die
Muster auszuschreiben.

## Die vier Fragen, und wie weit sie hier reichen

**1. Determinismus.** Gesucht nach Gleitkomma (nichts, und die `#pragma GCC poison`
macht es zum Übersetzungsfehler), nach Iteration über ungeordnete Mengen (nichts —
Befund 1 ist Fließtext, kein Behälter), nach Zeit- und Adressquellen (kein `<chrono>`,
kein `reinterpret_cast`, kein roher Zeiger, kein `new`/`delete`), nach mehr als einem
Zufallsstrom (in diesem Paket gibt es keinen; `zufall.hpp` ist Platzhalter). Das
Rechenwerk ist reine Ganzzahlarithmetik mit festgenagelter Rundungsregel. Der
Reihenfolgeeinfluss von `file(GLOB …)` auf den Bau ist keiner: CMake sortiert
GLOB-Ergebnisse, und die Bibliothek ist statisch — die Linkreihenfolge geht in kein
Ergebnis ein. **Ich habe hier nichts gefunden.**

**2. Rückkopplungen.** Dieses Paket enthält keine Zustandsfortschreibung und keine
Schleife, in der Erfolg mehr Erfolg erzeugt — `schritt.hpp` und `zustand.hpp` sind
Platzhalter. Die Frage hat hier keinen Gegenstand; sie gehört an 0008 und an das
Paket, das `schritt` baut.

**3. Zustandsausgabe.** Ebenso ohne Gegenstand: Die drei Ebenen gehören Paket
0010-zustandsausgabe-drei-ebenen. Was dieses Paket dazu beitragen musste, hat es
getan — der Kern hat keine Ausgabe und darf keine haben (T13).

**4. Die Ränder.** Das ist die Stelle, an der hier etwas zu holen gewesen wäre. Was
ich nachgerechnet habe:

- `teile_gerundet(I64_MIN, 1) = I64_MIN` und `teile_gerundet(I64_MIN, 2) =
  −4 611 686 018 427 387 904`. Beide belegt (`festkomma.cpp:70`,
  `festkomma_probe.cpp:89`). Der Betrag von `I64_MIN` ist 9 223 372 036 854 775 808
  und passt nicht in `i64` — er wird aber in `i128` gebildet
  (`intern::betrag`, `festkomma.hpp:68`), und dort ist er harmlos. Das ist die Falle,
  an der eine Betragsrechnung auf `i64` gestorben wäre; sie ist umgangen.
- `teile_gerundet(I64_MIN, -1)` ist der eine Fall, in dem eine gültige Division ein
  ungültiges Ergebnis hat. Er bricht ab, `ctest` belegt es.
- Kein Überlauf in `runde_von_null_weg`: `ganz + 1` wird nur gebildet, wenn
  `an ≥ 2` ist (bei `an = 1` ist der Rest immer null), also ist `ganz` höchstens
  `az/2`. `an − rest` kann nicht überlaufen, weil `0 ≤ rest < an` gilt.
- Kein Überlauf in `potenz`: Vor jeder Multiplikation gilt `|wert| ≤ 2^63`, weil die
  Prüfung der vorigen Runde das erzwungen hat; das Produkt bleibt unter 2^126 und
  damit unter der `i128`-Grenze. Der Wächter sieht also jeden Wert, bevor er falsch
  wird. `potenz(-2, 63) = I64_MIN` ist der genaue Rand und bricht richtigerweise
  *nicht* ab.
- Kein Überlauf im Startwert der Wurzel: `r = 2^⌈bitlänge(x)/n⌉`, und
  `r^(n−1)` wird bei `bitlänge ≤ 63` und `n ≤ 32` am grössten für `n = 31` —
  dort ist `r = 8` und `r^30 = 2^90`, weit unter 2^127. Ich habe alle Grade von 1 bis
  32 durchgerechnet; 2^90 ist das Maximum. Und selbst wenn: `potenz_i128` hat einen
  eigenen Wächter, der abbricht statt umzulaufen.
- Rundung über tausend Runden: Es gibt genau **eine** Rundungsregel, und
  `mal_geteilt` benutzt dieselbe `runde_von_null_weg` wie `teile_gerundet`
  (`festkomma.hpp:141`, `:162`). Zwei Regeln, die auseinanderlaufen, kann es also
  nicht geben. Weil symmetrisch gerundet wird, summiert sich der Fehler über viele
  Runden nicht in eine Richtung auf — das ist die Eigenschaft, an der T6 hängt.
- `wurzel` hängt nicht an `WURZEL_SCHRITTE`: Nach der Newton-Schleife stellen die
  beiden Berichtigungsschleifen (`festkomma.hpp:232–233`) die Nachbedingung
  `r^n ≤ x < (r+1)^n` exakt her. Wer die Schrittzahl ändert, ändert das Ergebnis
  nicht — für einen Regressionsbestand ist genau das die Zusage, die zählt.
  `festkomma_probe.cpp:110–113` prüft die Nachbedingung an tausend Werten, unter den
  Sanitizern, und der Lauf ist grün.

**Ich habe hier keinen Rechenfehler gefunden.** Das Rechenwerk ist die stärkste
Stelle des Pakets.

## Ausdrücklich kein Befund

- **Die sechs Platzhalter sind leer.** Das ist der Auftrag.
- **Der Abbruch ist ein `throw std::domain_error` statt `std::abort`.** Das Paket
  schreibt die Form nicht vor, nur den Abbruch, und die gewählte Form ist mechanisch
  besser: Ein Wurf macht den Ausdruck zur Übersetzungszeit zu keiner Konstante und ist
  zur Laufzeit von einer Probe fangbar — ein Signal ist beides nicht.
- **Benennung, Dateiaufteilung, Kommentarumfang.** Nicht geprüft, wie das Paket es
  vorgibt.

## Randnotizen für den Projektmanager — keine Befunde gegen 0004

1. **Das Paket verlangt Kennungen, die der Bau nicht haben konnte.** „Was du baust",
   Punkt 4, nennt `zufall` → 0012 und `pruefsumme` → 0013. `zufall.hpp:2` sagt
   „Gebaut in Paket noch kein Paket", die Modulliste in `kern.hpp:15–16` nennt für
   beide keine Kennung. Kein Befund: Diese Fassung des Pakets entstand in Commit
   `8e2a081` und damit **nach** dem Bau (`a3cd9e4`), und die Kennung steht in keiner
   der sieben Bedingungen. Für `pruefsumme` hat sich die Sache erledigt (0013 hat die
   Datei ersetzt); offen ist nur `zufall.hpp`. Wird 0004 aus einem anderen Grund
   wiedereröffnet, gehört die eine Zeile mit hinein.
2. **`-fwrapv` und `-fsanitize=undefined` greifen ineinander.** Beide stehen in
   jedem Profil (`werkzeugkette.cmake`). *Vermutung, in diesem Lauf nicht
   nachgewiesen* — ich konnte kein eigenes Programm übersetzen: Wenn `-fwrapv` den
   vorzeichenbehafteten Überlauf als Umbruch **definiert**, hat UBSan dafür nichts
   mehr zu melden, und ADR 0011 Maßnahme 2 deckt diesen einen Fehler nicht mehr ab.
   **Für 0004 ändert das nichts**: Bedingung 7 wird von den ausgeschriebenen Wächtern
   `nach_i64` und `potenz_i128` erfüllt, nicht vom Sanitizer, und `ctest` belegt, dass
   sie werfen. Die Frage gehört an den ADR, nicht an dieses Paket — sie ist es aber
   wert, einmal mit einem Zweizeiler beantwortet zu werden, bevor sich ein späteres
   Paket auf die Maßnahme verlässt.
3. **`potenz` hat keine Schranke für den Exponenten.** Für `|basis| ≥ 2` bricht der
   Wächter nach spätestens 63 Runden ab; für `basis ∈ {−1, 0, 1}` läuft die Schleife
   so oft, wie der Exponent sagt — bei `potenz(1, 4'000'000'000)` sind das vier
   Milliarden Runden. Kein falsches Ergebnis, nur eine Laufzeit, die an den Daten
   hängt. `wurzel` hat für den Grad eine Schranke (`WURZEL_GRAD_MAX`), `potenz` für
   den Exponenten keine. Kein Befund — keine der sieben Bedingungen verlangt sie, und
   T29 beschränkt die Exponenten ohnehin auf kleine Zahlen. Erwähnt, weil eine
   Simulation mit fester Rundenzahl keine unbeschränkte Schleife enthalten sollte.
4. **Eine Begründung im Quelltext trägt nicht.** `festkomma.hpp:102–108` begründet die
   Form `rest >= an - rest` damit, dass `2 * rest` bei einem Nenner nahe der
   `i128`-Grenze überlaufen könnte. Das kann nicht eintreten: `an` stammt in beiden
   Aufrufern aus einem `i64`, ist also höchstens 2^63, und damit bleibt `2 * rest`
   unter 2^64. Die Begründung verwechselt Zähler und Nenner. **Der Code ist
   trotzdem richtig** — die gewählte Form ist die sicherere, nur aus einem anderen
   Grund als dem angegebenen. Kein Befund (Kommentare sind ausgenommen); notiert,
   weil ein späterer Bauagent, der `runde_von_null_weg` mit einem echten
   `i128`-Nenner aufruft, sich auf diesen Satz verlassen könnte.

## Was ich gesucht und nicht gefunden habe

Damit diese Prüfung von einer, die nicht stattfand, unterscheidbar ist: Gesucht wurde
nach Gleitkomma in der Fortschreibung, nach streuenden Behältern, nach Zeit-, Datei-
und Bildschirmzugriff im Kern, nach `reinterpret_cast`/`const_cast`/`new`/`delete`/
`asm`, nach einem zweiten Zufallsstrom, nach einem stillen Ersatzwert bei Nenner
null, nach einem Überlauf, den ein Wächter zu spät sieht, nach zwei Rundungsregeln,
die auseinanderlaufen, nach einem Wurzelergebnis, das an der Schrittzahl hängt, und
nach fremden Abhängigkeiten im Kern. Nichts davon ist da.

Die beiden Befunde sitzen an derselben Stelle und haben dieselbe Ursache: Die Dateien
zitieren die Grep-Muster ihrer eigenen Abnahme und lösen sie damit aus. Das Rechenwerk
selbst — die Stelle, an der ein Fehler am teuersten wäre — hat gehalten.
