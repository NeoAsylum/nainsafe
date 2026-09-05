---
typ: pruefung
paket: 0004-werkstattgeruest-festkomma
pruefer: kern-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle sieben Bedingungen einzeln; die drei Mustervergleiche aus Bedingung 3 und 4, an denen Rücklauf 1 hing, gehen jetzt leer aus (nachgemessen), Bedingung 2 liefert dieselben acht gedeckten Zeilen wie in Runde 1, und der Baulauf vom 2026-09-02 belegt Bedingung 5, 6 und 7 mit grünem `-Werror`-Bau und `ctest` 2/2 gegen `libkern_geprueft.a`.
befunde: 0
---

# Prüfung 0004-werkstattgerüst-festkomma — Runde 2 (nach Rücklauf 1)

Geprüft gegen die sieben Bedingungen im Abschnitt „Abnahme" und gegen nichts sonst.
Gelesen: das Arbeitspaket, die fünfzehn Dateien aus Bedingung 1, mein eigener Befund
aus Runde 1, der Baulaufbericht `befunde/uebersetzung-2026-09-02.md`, die
Bauverzeichnisse. **Nicht gelesen:** das Logbuch des Kernbauers und seine Begründung.

## Vorbemerkung: was ich diesmal nicht selbst ausführen konnte

In Runde 1 habe ich selbst übersetzt und `ctest` laufen lassen. In diesem Lauf war mir
die Shell bis auf wenige Aufrufe gesperrt; ausgeführt habe ich `git log`, `git show`
und die Mustervergleiche. Bau und Test sind deshalb **fremdgemessen**, aus dem Bericht
des Runners — der aber ist genau die Quelle, die dafür vorgesehen ist, und keine
Einschätzung eines Modells. Was ich mechanisch geprüft habe und was ich gerechnet
habe, steht unten getrennt.

## Was Rücklauf 1 verlangt hat, und was tatsächlich geändert wurde

Verlangt waren zwei Kommentarstellen in zwei Dateien. Der Diff der Änderung
(`git show 74f5cb0 -- kern/include/kern/kern.hpp kern/CMakeLists.txt`) umfasst genau
diese zwei Dateien und ausschliesslich Kommentarzeilen. **Das Rechenwerk ist
unberührt** — `festkomma.hpp`, `festkomma.cpp` und `festkomma_probe.cpp` stehen
unverändert auf dem Stand `a3cd9e4`, den ich in Runde 1 selbst gebaut und grün
gemessen habe. `zufall.hpp` ist nicht angefasst worden, wie der Rücklauf es vorgibt
(letzte Änderung: `a3cd9e4`).

Beiläufig, ohne Belang für das Urteil: Die Änderung liegt nicht in dem Commit, dessen
Betreff sie nennt (`830e011` enthält Logbuch, Arbeitspaket und `parameter.toml`),
sondern in `74f5cb0`. Das ist Bündelung des Runners, nicht Sache des Pakets.

## Die sieben Bedingungen

**Bedingung 1 — die fünfzehn Dateien existieren.** Einzeln nachgesehen, alle da:
`CMakeLists.txt`, `werkzeugkette.cmake`, `.gitignore`, `kern/CMakeLists.txt`,
`kern/include/kern/kern.hpp`, `sperre.hpp`, `festkomma.hpp`, `kern/src/festkomma.cpp`,
`kern/test/festkomma_probe.cpp` sowie die sechs Moduldateien `zustand.hpp`,
`werte.hpp`, `schreiber.hpp`, `zufall.hpp`, `pruefsumme.hpp`, `schritt.hpp`.
`zustand.hpp` und `pruefsumme.hpp` sind inzwischen keine Platzhalter mehr — 0008 und
0013 haben sie ersetzt, und das ist richtig so; die Bedingung fordert Existenz.

**Bedingung 2 — keine Gleitkommazahl im Kern (T4).** Der Mustervergleich
`float|double|f32|f64` über `kern/` liefert acht Zeilen — **dieselben acht wie in
Runde 1**, und jede ist von der Ausnahme der Bedingung gedeckt:

| Fundstelle | gedeckt als |
|---|---|
| `sperre.hpp:24` `#pragma GCC poison float double` | *ist* die Sperre |
| `sperre.hpp:4, 7, 14, 19, 21` | beschreiben die Sperre |
| `kern.hpp:32` | verweist auf die Sperre |
| `kern/CMakeLists.txt:54` `-Wdouble-promotion -Wfloat-equal` | setzt sie durch |

Keine einzige Rechenzeile. Die Sperre greift auch wirklich: Sie steht als **letzter**
Include in `src/festkomma.cpp:18` und `test/festkomma_probe.cpp:25`, also hinter
`<stdexcept>` beziehungsweise `<cstdio>` — die Reihenfolge, ohne die `#pragma GCC
poison` den nächsten Standardkopf zerbrechen würde. Dass sie hält, belegt der grüne
Bau.

**Bedingung 3 — null Fremdabhängigkeiten (T2). Hier hing Rücklauf 1; jetzt hält es.**
Beide Vergleiche über `kern/CMakeLists.txt` gehen leer aus:

```
find_package|FetchContent|ExternalProject|add_subdirectory   → keine Treffer
target_link_libraries(kern                                   → keine Treffer
```

In Runde 1 traf die Datei beide Muster selbst, weil sie sie als Kommentar zitierte.
Der neue Kommentar (Zeilen 7–13) benennt den Nachweis und verweist für den Wortlaut
auf Bedingung 3, statt ihn abzuschreiben. Die Ausnahme „ausser diesen Kommentarzeilen",
mit der die geprüfte Datei ihr eigenes Kriterium umgeschrieben hatte, ist ersatzlos
weg — das war der eigentliche Befund, und er ist behoben. Der einzige verbliebene
`target_link_libraries`-Aufruf ist Zeile 102, `${name} PRIVATE
${FABRIK_PROBEN_BIBLIOTHEK}`: eine Probe, die gegen den Kern selbst linkt. Nichts wird
hereingeholt, nichts Fremdes dazugelinkt.

**Bedingung 4 — sieben Module, und der Grep für T9/T13. Hier hing Rücklauf 1
ebenfalls; jetzt hält es.**

Erster Teil: `kern.hpp:11–17` zählt genau sieben Module auf (`festkomma`, `zustand`,
`werte`, `schreiber`, `zufall`, `pruefsumme`, `schritt`), `kern.hpp:63–69` bindet genau
sieben Köpfe ein, alle sieben Dateien existieren.

Zweiter Teil:

```
<iostream>|<fstream>|<chrono>|unordered_map|unordered_set  über kern/   → keine Treffer
```

Runde 1 hatte hier drei Treffer in `kern.hpp:43, 47, 48`. Die Absätze zu T9 und T13
sagen jetzt dasselbe ohne die Muster („Streuende Behaelter sind im Kern verboten […]
`std::map`, `std::set`"; „Keine Stromausgabe, kein Dateizugriff, keine Zeitquelle").
`kern.hpp:52–56` sagt ausserdem, **warum** die Namen dort nicht stehen — damit ein
späteres Paket sie nicht in bester Absicht wieder ausschreibt. Der einzige mechanische
Wächter, den dieses Vorhaben für T9 hat, ist damit wieder ablesbar statt durchsehbar.

**Bedingung 5 — Rundung vom Null weg.** Die vier verlangten Werte, von Hand gegen
`runde_von_null_weg` (`festkomma.hpp:92–112`) gerechnet:

| Aufruf | `ganz` | `rest` | `rest ≥ an − rest` | Betrag | Vorzeichen | Ergebnis | belegt in |
|---|---:|---:|---|---:|---|---:|---|
| `teile_gerundet(7, 2)` | 3 | 1 | `1 ≥ 1` ja | 4 | + | **4** | `festkomma.cpp:39` |
| `teile_gerundet(-7, 2)` | 3 | 1 | `1 ≥ 1` ja | 4 | − | **−4** | `festkomma.cpp:40` |
| `teile_gerundet(5, 2)` | 2 | 1 | `1 ≥ 1` ja | 3 | + | **3** | `festkomma.cpp:44` |
| `teile_gerundet(-5, 2)` | 2 | 1 | `1 ≥ 1` ja | 3 | − | **−3** | `festkomma.cpp:45` |

Alle vier Vorzeichenkombinationen stehen mit ausgeschriebenen Erwartungswerten da
(`festkomma.cpp:39–47`), nicht nur die zwei verlangten. Die Regel rundet den *Betrag*
und setzt das Vorzeichen erst danach an — deshalb ist sie über null symmetrisch, und
ein Fonds, der long und short sein kann, bekommt keine still bevorzugte Richtung. Die
Maschine hätte abgeschnitten und 3 und −3 geliefert.

**Bedingung 6 — `mal_geteilt` rechnet über `__int128`.** Die Zahlenprobe aus T47 steht
wörtlich (`festkomma.cpp:81`): 21 000 000 000 · 20 / 10 000 = 42 000 000 — nachgerechnet,
und 42 Mrd sind genau 0,2 % von 21 Bio. Die verlangte zweite Probe, deren Produkt `i64`
sprengt, gibt es zweimal:

- `festkomma.cpp:90`: 9 000 000 000 000 000 000 · 4 = 36 000 000 000 000 000 000, also
  rund das Vierfache der `i64`-Grenze 9 223 372 036 854 775 807. / 8 =
  4 500 000 000 000 000 000, passt wieder hinein. Stimmt.
- `festkomma.cpp:95`: 4 000 000 000 · 4 000 000 000 = 16 000 000 000 000 000 000, zwei
  einzeln harmlose Faktoren. / 1 000 000 000 = 16 000 000 000. Stimmt.

Der Zwischenwert selbst kann nicht überlaufen: Das Produkt zweier `i64` liegt
betragsmässig höchstens bei 2^126, die `i128`-Grenze ist 2^127−1.

**Bedingung 7 — Nenner null und Überlauf brechen ab, mit Begründung an der Stelle.**
Der Abbruch steht an beiden Aufrufern (`festkomma.hpp:137`, `:157`), und die Meldung
nennt den Grund im Klartext: „ein stiller Ersatzwert waere eine Zahl, die keine
Pruefung bemerkt (T6)". Ausgeschrieben begründet ist er an der Deklaration
(`festkomma.hpp:42–61`), und die Begründung trägt — ein Ersatzwert wandert in den
Regressionsbestand, wird dort zum Sollwert und macht jede spätere Behebung rot. Der
Überlaufwächter `intern::nach_i64` (`festkomma.hpp:81–87`) sitzt hinter jeder Rückgabe
von `teile_gerundet` und `mal_geteilt`; `potenz` und `potenz_i128` haben eigene.
`festkomma_probe.cpp:119–133` erwartet zehn Abbrüche, darunter
`teile_gerundet(I64_MIN, −1)` — der eine Fall, in dem eine *gültige* Division ein
Ergebnis ausserhalb von `i64` hat — und `ctest` ist grün.

## Der mechanische Nachweis für 5, 6 und 7

`befunde/uebersetzung-2026-09-02.md`, erzeugt vom Baulauf:

```
cmake --build   → ok (Code 0): kern, kern_geprueft, festkomma_probe, pruefsumme_probe
ctest           → ok (Code 0): 2/2 Passed
```

Der Bau trägt `-Werror` (`kern/CMakeLists.txt:51`), also ist ein grüner Bau der Beleg,
dass der Übersetzer **alle 39 `static_assert`** in `festkomma.cpp` ausgewertet und
gehalten gefunden hat. Sie sind keine Tests, die laufen könnten, sondern Bedingungen
an die Übersetzung.

Dass die Probe wirklich den geprüften Kern misst und nicht sich selbst, habe ich wie
in Runde 1 an der Linkzeile nachgesehen — sonst wäre ADR 0011 Maßnahme 2 eine
Behauptung:

```
bau/kern/CMakeFiles/festkomma_probe.dir/link.txt:
  c++ … -fsanitize=undefined,address -fno-sanitize-recover=all … -o festkomma_probe libkern_geprueft.a
bau/kern/CMakeFiles/kern_geprueft.dir/flags.make:
  CXX_FLAGS = … -Werror … -fwrapv -fno-fast-math -fsanitize=undefined,address -fno-sanitize-recover=all
```

Gelinkt wird `libkern_geprueft.a`, nicht `libkern.a`. `-fno-sanitize-recover=all` macht
aus einer Meldung einen Abbruch; ein grüner Lauf ist damit ein Nachweis und nicht nur
ein Durchlauf.

## Die vier Fragen, und wie weit sie hier reichen

**1. Determinismus.** Gesucht nach Gleitkomma in der Fortschreibung (nichts, und die
`#pragma GCC poison` macht sie zum Übersetzungsfehler), nach Iteration über ungeordnete
Mengen (nichts — der Grep aus Bedingung 4 geht jetzt vollständig leer aus, es gibt also
nicht einmal mehr Fliesstext), nach Zeit- und Adressquellen (keine Zeitquelle, kein
`reinterpret_cast`, kein roher Zeiger, kein `new`/`delete`), nach mehr als einem
Zufallsstrom (in diesem Paket gibt es keinen; `zufall.hpp` ist unverändert Platzhalter).
Das Rechenwerk ist reine Ganzzahlarithmetik mit **genau einer** Rundungsregel:
`mal_geteilt` benutzt dieselbe `runde_von_null_weg` wie `teile_gerundet`
(`festkomma.hpp:141`, `:162`), zwei auseinanderlaufende Regeln kann es also nicht
geben. **Nichts gefunden.**

**2. Rückkopplungen.** Ohne Gegenstand: Dieses Paket enthält keine
Zustandsfortschreibung und keine Schleife, in der Erfolg mehr Erfolg erzeugt.
`schritt.hpp` ist Platzhalter. Die Frage gehört an 0008 und an das Paket, das `schritt`
baut.

**3. Zustandsausgabe.** Ebenso ohne Gegenstand — die drei Ebenen gehören Paket
0010. Was dieses Paket beitragen musste, hat es getan: Der Kern hat keine Ausgabe und
darf keine haben (T13).

**4. Die Ränder.** Nachgerechnet, unverändert gegenüber Runde 1, weil das Rechenwerk
unverändert ist:

- `betrag()` rechnet auf `i128` (`festkomma.hpp:68`). Der Betrag von `I64_MIN` ist
  9 223 372 036 854 775 808 und passt nicht in `i64` — in `i128` ist er harmlos. Das ist
  die Falle, an der eine Betragsrechnung auf `i64` gestorben wäre; sie ist umgangen.
- `an − rest` kann nicht überlaufen, weil `0 ≤ rest < an` gilt; `ganz + 1` bleibt weit
  unter der `i128`-Grenze.
- `potenz`: Vor jeder Multiplikation gilt `|wert| ≤ I64_MAX`, weil der Wächter der
  vorigen Runde das erzwungen hat. Das Produkt bleibt unter 2^126, also unter der
  `i128`-Grenze — der Wächter sieht jeden Wert, bevor er falsch wird.
- `wurzel`: Der Divisor `potenz_i128(r, n−1)` kann nicht null werden. Für `x ≥ 2` ist
  der Startwert `r ≥ 2`, und der Newton-Schritt liefert für jedes `r ≥ 1` mindestens 1
  — bei `r = 1` ist er `(n−1+ziel)/n ≥ (n+1)/n ≥ 1`, bei `r ≥ 2` schon
  `(n−1)·r ≥ n`. `r` wird also nie null, und **es gibt keine Division durch null in der
  Iteration.** Das habe ich diesmal ausgerechnet statt vorausgesetzt.
- Das Ergebnis hängt nicht an `WURZEL_SCHRITTE`: Die beiden Berichtigungsschleifen
  (`festkomma.hpp:232–233`) stellen `r^n ≤ x < (r+1)^n` exakt her.
  `festkomma_probe.cpp:110–113` prüft die Nachbedingung an tausend Werten unter den
  Sanitizern, grün. Für einen Regressionsbestand ist genau das die Zusage, die zählt.
- Rundung über tausend Runden: Weil auf dem Betrag gerundet und das Vorzeichen erst
  danach angesetzt wird, summiert sich der Fehler nicht in eine Richtung auf.

**Ich habe keinen Rechenfehler gefunden.** Das Rechenwerk ist die stärkste Stelle des
Pakets, und es ist seit Runde 1 nicht angefasst worden.

## Ausdrücklich kein Befund

- **Die vier Platzhalter sind leer.** Das ist der Auftrag.
- **`kern.hpp:15–16` nennt für `zufall` und `pruefsumme` keine Paketkennung.** Der
  Rücklauf hat das ausdrücklich abgelehnt und `zufall.hpp` gesperrt; ich ziehe das nicht
  nach. Keine der sieben Bedingungen verlangt die Kennung.
- **Der Abbruch ist ein `throw std::domain_error` statt `std::abort`.** Das Paket
  schreibt die Form nicht vor, nur den Abbruch.
- **Benennung, Dateiaufteilung, Kommentarumfang.** Nicht geprüft, wie das Paket es
  vorgibt.

## Randnotizen für den Projektmanager — keine Befunde gegen 0004

1. **`kern/bau/` steht im Suchpfad der Bedingungen 2 und 4.** `baulauf.py` legt seit dem
   2026-09-02 ein Bauverzeichnis **innerhalb** von `kern/` an
   (`uebersetzung-2026-09-02.md`, zweiter Konfigurationslauf). Dort steht in
   `kern/bau/CMakeFiles/kern.dir/flags.make:9` die Zeile `… -Wdouble-promotion
   -Wfloat-equal …`. Ein wörtliches `grep -rnE 'float|double|f32|f64' kern/` trifft sie,
   weil POSIX-`grep` `.gitignore` nicht kennt; ein `.gitignore`-treues Werkzeug
   (`rg`, und damit auch dieser Prüflauf und der aus Runde 1) trifft sie nicht.
   **Kein Befund gegen 0004** — das Paket liefert die `.gitignore` mit `bau/`, und das
   Verzeichnis ist Erzeugnis, nicht Quelle. Aber der Wächter für T9 und T4 liest sich
   je nach Werkzeug verschieden, und genau das war der Schaden, den Rücklauf 1
   abgestellt hat. Wenn es dabei bleiben soll, gehört das Werkzeug in die Bedingung
   oder das Bauverzeichnis aus `kern/` heraus. Beides ist eine Entscheidung des
   Projektmanagers, nicht meine.
2. **Eine Begründung im Quelltext trägt weiterhin nicht.** `festkomma.hpp:101–108`
   begründet die Form `rest >= an - rest` damit, dass `2 * rest` bei einem Nenner nahe
   der `i128`-Grenze überlaufen könnte. Das kann nicht eintreten: `an` stammt in beiden
   Aufrufern aus einem `i64`, ist also höchstens 2^63. Die Begründung verwechselt
   Zähler und Nenner. **Der Code ist trotzdem richtig** — die gewählte Form ist die
   sicherere, nur aus einem anderen Grund. Kein Befund (Kommentare sind ausgenommen);
   erneut notiert, weil ein späterer Bauagent, der `runde_von_null_weg` mit einem echten
   `i128`-Nenner aufruft, sich auf den Satz verlassen könnte.
3. **`potenz` hat keine Schranke für den Exponenten.** Für `|basis| ≥ 2` bricht der
   Wächter nach spätestens 63 Runden ab; für `basis ∈ {−1, 0, 1}` läuft die Schleife so
   oft, wie der Exponent sagt. Kein falsches Ergebnis, nur eine Laufzeit, die an den
   Daten hängt. `wurzel` hat mit `WURZEL_GRAD_MAX` eine Schranke, `potenz` keine.
4. **`-fwrapv` und `-fsanitize=undefined` — weiterhin ungeklärt.** Beide stehen im
   Testprofil (`werkzeugkette.cmake:57, 63`). Wenn `-fwrapv` den vorzeichenbehafteten
   Überlauf als Umbruch *definiert*, hat UBSan dafür nichts mehr zu melden, und ADR 0011
   Maßnahme 2 deckt diesen einen Fehler nicht ab. Ich konnte es auch in diesem Lauf
   nicht messen (keine eigene Übersetzung möglich) und behaupte es deshalb nicht.
   **Für 0004 ändert es nichts:** Bedingung 7 wird von den ausgeschriebenen Wächtern
   `nach_i64`, `potenz` und `potenz_i128` erfüllt, nicht vom Sanitizer, und `ctest`
   belegt, dass sie werfen. Die Frage gehört an den ADR — sie ist es aber wert, mit
   einem Zweizeiler beantwortet zu werden, bevor sich ein späteres Kernpaket auf die
   Maßnahme statt auf einen eigenen Wächter verlässt.
5. **`kern.hpp` wird von nichts übersetzt.** Der Sammelkopf steht über
   `file(GLOB KERN_KOEPFE …)` als Quelle in `add_library`, aber CMake übersetzt Köpfe
   nicht, und keine `.cpp` bindet ihn ein. Seine sieben `#include` sind damit nie
   geprüft — ein Tippfehler darin fiele erst auf, wenn ein späteres Paket den Kopf
   benutzt. Kein Befund: Keine der sieben Bedingungen verlangt, dass er übersetzt wird,
   und Bedingung 4 verlangt nur Aufzählung und Existenz, beides erfüllt. Erwähnt, weil
   es billig zu ändern wäre, solange nur ein Paket den Kopf besitzt.

## Was ich gesucht und nicht gefunden habe

Damit diese Prüfung von einer, die nicht stattfand, unterscheidbar ist: Gesucht wurde
nach einer Regression im Rechenwerk durch die Rücklauf-Änderung (der Diff zeigt
ausschliesslich Kommentare in zwei Dateien), nach einem vierten Blindtreffer der drei
Muster (keiner), nach einem neu eingeschleppten Treffer in den umformulierten Absätzen
(keiner), nach Gleitkomma, streuenden Behältern, Zeit-, Datei- und Bildschirmzugriff im
Kern, nach `reinterpret_cast`/`const_cast`/`new`/`delete`/`asm`, nach einem zweiten
Zufallsstrom, nach einem stillen Ersatzwert bei Nenner null, nach einer Division durch
null in der Newton-Iteration, nach einem Überlauf, den ein Wächter zu spät sieht, nach
zwei Rundungsregeln, die auseinanderlaufen, nach einem Wurzelergebnis, das an der
Schrittzahl hängt, und nach fremden Abhängigkeiten im Kern. Nichts davon ist da.

Beide Befunde aus Rücklauf 1 sind behoben, und zwar auf dem Weg, der das
Abnahmekriterium unangetastet lässt. Die drei Mustervergleiche gehen leer aus, das
Rechenwerk ist unberührt und weiterhin grün. **Das Abnahmekriterium ist erfüllt.**
