---
typ: pruefung
paket: 0013-pruefsumme-fnv1a-64
pruefer: kern-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle fünf Abnahmebedingungen einzeln geprüft — die drei zitierten Quellen aufgerufen und die 14 Testvektoren, beide Verfahrenskonstanten und die Rechenvorschrift Zeichen für Zeichen verglichen, dazu `fnv1a64("a")` und die unveröffentlichte Laufzeitausgabe `00 61` vollständig von Hand nachgerechnet; die beiden Greps aus Abnahme 3 und 5 liefern nichts.
befunde: 3
---

# Prüfung 0013-pruefsumme-fnv1a-64

Geprüft: `kern/include/kern/pruefsumme.hpp` (236 Zeilen), `kern/src/pruefsumme.cpp`
(297 Zeilen), `kern/test/pruefsumme_probe.cpp` (278 Zeilen) gegen die fünf Bedingungen
im Abschnitt „Abnahme" des Arbeitspakets, gegen `specs/0016-…/technik.md` T2, T4, T9,
T12, T22 und gegen ADR 0011.

**Urteil: geprüft.** Alle fünf Bedingungen halten. Die drei Nebenbefunde am Ende sind
Ungenauigkeiten in Quellenangaben und ein Loch im mechanischen Nachweis, das nicht
diesem Paket gehört — **keiner davon ist eine Rückgabe.**

## Einschränkung, vorweg und ausdrücklich

**Ich habe nicht selbst übersetzt und die Probe nicht selbst laufen lassen.** In dieser
Umgebung sind weder der Übersetzeraufruf noch das Ausführen der gebauten Programme
freigegeben. Was an die Stelle tritt:

1. **Eigene Handrechnung** statt Nachvollzug der Programmausgabe (unten, zwei Fälle,
   einer davon auf einem Wert, den keine Quelle veröffentlicht).
2. **Aufruf der Quellen** und zeichenweiser Vergleich — das ist ohnehin das, was
   Abnahme 1 dem Prüfer aufträgt, und dafür braucht es keinen Übersetzer.
3. Als Beleg, **dass** es übersetzt und gelaufen ist, `befunde/uebersetzung-2026-09-02.md`
   mit `ergebnis: ok`. Das ist nicht der Bericht des Bauagenten, sondern die Ausgabe von
   `baulauf.py` — dieselbe Einrichtung, die `notizen/lehren.md` am 2026-09-01 als Antwort
   darauf beschreibt, dass ein Bauagent seinen Compiler nicht selbst aufrufen kann: das
   Werkzeug in den Runner, seine Ausgabe in eine Datei. `cmake --build` und `ctest` je
   Code 0, beide Manifeste, „100% tests passed, 0 tests failed out of 2".

   Ergänzt um `kern/bau/Testing/Temporary/LastTest.log` (die ausgeschriebenen Zahlen der
   Probe) und `kern/bau/CMakeFiles/pruefsumme_probe.dir/flags.make` und `link.txt`. Die
   belegen, dass mit `-Werror -Wconversion -Wsign-conversion -Wold-style-cast` übersetzt
   und gegen `libkern_geprueft.a` mit `-fsanitize=undefined,address
   -fno-sanitize-recover=all` gelinkt wurde. `-fno-sanitize-recover=all` heisst: Ein Fund
   der Sanitizer hätte abgebrochen. Der bestandene Lauf ist damit ein belastbarer Beleg
   für die Abwesenheit von undefiniertem Verhalten zur Laufzeit.

   **Was ich damit nicht behaupte:** dass ich den Bau wiederholt hätte. Ich habe die
   Zahlen, die dabei herauskamen, unabhängig nachgerechnet — das ist der Teil, den ein
   Compilerprotokoll nicht leisten kann, und der Teil, für den es diese Rolle gibt.

## Abnahme 1 — veröffentlichte Testvektoren, mit Quelle

Alle drei zitierten Quellen aufgerufen (2026-09-02) und gegen die Dateien gehalten.

**[RFC 9923]** `https://www.rfc-editor.org/rfc/rfc9923.txt` existiert und trägt den
zitierten Titel „The FNV Non-Cryptographic Hash Algorithm" (Februar 2026). Abschnitt 2
enthält die Rechenvorschrift, Abschnitt 5 die Konstanten — beide Abschnittsnummern in
`pruefsumme.hpp` stimmen. Die in Zeile 159–163 zitierte Pseudocodeblock ist wortgleich
mit dem der Quelle, einschliesslich der Zeilenfolge *erst XOR, dann Multiplikation*.

**[TESTVEK]** `https://raw.githubusercontent.com/lcn2/fnv/master/test_fnv.c` abgerufen.
Die 14 Erwartungswerte, Zeichen für Zeichen verglichen — alle 14 identisch:

| Index | Eingabe | in der Quelle | in `src/pruefsumme.cpp` |
|---|---|---|---|
| [0] | `TEST("")` | `0xcbf29ce484222325` | Z. 102 ✓ |
| [1]–[5] | `"a"`…`"e"` | `af63dc4c8601ec8c`, `af63df4c8601f1a5`, `af63de4c8601eff2`, `af63d94c8601e773`, `af63d84c8601e5c0` | Z. 107–116 ✓ |
| [6]–[11] | `"f"`…`"foobar"` | `af63db4c8601ead9`, `08985907b541d342`, `dcb27518fed9d577`, `dd120e790c2512af`, `cac165afa2fef40a`, `85944171f73967e8` | Z. 118–129 ✓ |
| [12] | `TEST0("")` | `0xaf63bd4c8601b7df` | Z. 154 ✓ |
| [13] | `TEST0("a")` | `0x089be207b544f1e4` | Z. 156 ✓ |

Die Unterscheidung der beiden Makrosorten, auf der die Datei in Zeile 37–42 besteht, ist
in der Quelle bestätigt: `#define LEN(x) (sizeof(x)-1)`, `#define TEST(x) {x, LEN(x)}`,
`#define TEST0(x) {x, sizeof(x)}`. Die Zuordnung in der Datei ist richtig herum — die
`TEST`-Vektoren stehen gegen `fnv1a64_text` (ohne Nullbyte), die `TEST0`-Vektoren gegen
`fnv1a64` über ausgeschriebene Oktette (mit Nullbyte). Das ist genau die Falle, die die
Datei beschreibt, und sie ist nicht hineingetreten.

**[FNV]** `http://www.isthe.com/chongo/tech/comp/fnv/index.html` abgerufen. Der in
Zeile 260 zitierte Satz steht dort wortgleich: „The only solution for length 8 is:
FNV64_1a(d5 6b b9 53 42 87 08 36) = 0". Die acht Oktette in `NULLSUMME_VORWAERTS`
(Z. 267–268) stimmen mit den acht Oktetten des Zitats überein. Die Seite nennt
ausserdem beide Konstanten dezimal — zweite unabhängige Bestätigung von Abnahme 2.

Die leere Eingabe ist enthalten (Z. 102/104) und ist der Startwert. Dass die dezimale
Schreibweise im Kopf und die hexadezimale in der Probe dieselbe Zahl sind, habe ich
nicht dem `static_assert` geglaubt, sondern selbst ausgerechnet:
`0xcbf29ce484222325 = 203·2⁵⁶ + 242·2⁴⁸ + 156·2⁴⁰ + 228·2³² + 132·2²⁴ + 34·2¹⁶ + 35·2⁸ + 37
= 14 695 981 039 346 656 037` ✓ — identisch mit dem Literal in `pruefsumme.hpp` Z. 94.

Gefordert waren drei Vektoren aus unabhängiger Veröffentlichung. Vorhanden sind 15
(14 aus [TESTVEK], einer aus [FNV]). **Erfüllt.**

## Abnahme 2 — die beiden Konstanten im Klartext, mit Herkunft

`pruefsumme.hpp` Z. 94 und Z. 105, beide dezimal ausgeschrieben, jede mit einem
Absatz „Woher die Zahl stammt" (Z. 84–87, Z. 98–101). Die dort zitierten Zeichenketten
sind zeichengleich mit RFC 9923 Abschnitt 5, samt Tausendertrennung und samt der Lücke
in der Hexadezimalform:

- „14,695,981,039,346,656,037" / „0xCBF29CE4 84222325" ✓
- „1,099,511,628,211" / „2^40 + 2^8 + 0xB3" / „0x00000100 000001B3" ✓

Die Kreuzprobe in `src/pruefsumme.cpp` Z. 69–78 hält die Dezimalliterale gegen die
Hexadezimalform *und* gegen die Bildungsvorschrift derselben Quelle. Ich habe die
Bildungsvorschrift selbst nachgerechnet: `2⁴⁰ + 2⁸ + 0xB3 = 1099511627776 + 256 + 179
= 1099511628211` ✓. **Erfüllt.**

## Abnahme 3 — Little-Endian ohne Speicherzugriff

Der vom Arbeitspaket vorgeschriebene Aufruf, wörtlich:

```
grep -nE 'memcpy|reinterpret_cast|union|bit_cast' kern/src/pruefsumme.cpp kern/include/kern/pruefsumme.hpp
```

**liefert nichts.** Zur Sicherheit über alle drei Dateien des Pakets wiederholt,
einschliesslich `test/pruefsumme_probe.cpp` — ebenfalls nichts. Bemerkenswert, weil der
Kopf die drei verbotenen Wege inhaltlich diskutiert (Z. 44–47), sie aber umschreibt
(„das Speicherbild blockweise kopieren, den Zeigertyp umdeuten oder zwei Typen über
denselben Speicher legen") und damit den Grep nicht selbst verletzt.

Die Zerlegung in `nach_bytes_le` (Z. 132–141) ist eine Schiebefolge auf dem Wert:
`static_cast<u64>` (Wertumrechnung mod 2⁶⁴, seit C++20 festgelegt, seit C++20 auch
Zweierkomplement garantiert), dann `(muster >> (8u*i)) & 0xFFu`. Kein Zeiger, keine
Struktur, kein Speicherbild. Die Verschiebeweite läuft von 0 bis 56 und bleibt damit
unter der Bitbreite — keine undefinierte Verschiebung.

Ausgeschriebene Werte in der Probe: `1 → 01 00 00 00 00 00 00 00` und `-1 → FF`×8
(`src` Z. 181–185, `test` Z. 239–241), dazu `0` , `0x0102030405060708 → 08 07 06 05 04
03 02 01`, `I64_MAX → FF`×7`+7F`, `I64_MIN → 00`×7`+80`. Von Hand nachgerechnet, alle
sechs stimmen. Der Fall `I64_MIN` ist der einzige, der die Wertumrechnung wirklich
trägt — er ist da. **Erfüllt.**

## Abnahme 4 — die Summe hängt an der Reihenfolge

Zwei Nachweise, beide mit ausgeschriebenen Werten:

1. `61 00` gegen `00 61` (`src` Z. 250–255). Die *veröffentlichte* Zahl steht auf der
   Gleichheitsseite, die unveröffentlichte nur als Ungleichheit — dass beide Folgen aus
   denselben Oktetten bestehen, ist über die zwei veröffentlichten Einzeloktettwerte
   belegt (Z. 245–248). Konstruktiv sauber: kein selbst erzeugter Wert wird als
   Erwartungswert verlangt.
2. `d5 6b b9 53 42 87 08 36 → 0` gegen dieselben acht Oktette rückwärts (Z. 267–278).
   Ich habe geprüft, dass `NULLSUMME_RUECKWAERTS` wirklich die Umkehrung von
   `NULLSUMME_VORWAERTS` ist — Oktett für Oktett, sie ist es. Acht paarweise
   verschiedene Oktette gegen eine Zielsumme, die genau eine von 2⁶⁴ ist: Eine Summe,
   die versehentlich über eine Menge statt über eine Folge liefe, träfe die 0 nicht.

Dazu die Ebene, die Paket 0008 wirklich benutzt: `nimm_i64(1); nimm_i64(2)` gegen
`nimm_i64(2); nimm_i64(1)` (Z. 284–294). **Erfüllt.**

## Abnahme 5 — kein Gleitkomma, keine Fremdabhängigkeit

`grep -nE '\b(float|double|long double)\b'` über alle drei Dateien: nichts. Eingebunden
sind ausschliesslich `<array>`, `<cstddef>`, `<cstdint>`, `<span>`, `<string_view>`,
`<cstdio>` (nur in der Probe) sowie `kern/pruefsumme.hpp` und `kern/sperre.hpp`.
Keine Bibliothek ausserhalb der Standardbibliothek, kein `find_package`, kein
`FetchContent` (T2, `kern/CMakeLists.txt`). `sperre.hpp` steht in beiden `.cpp` als
letzte Zeile des Include-Blocks — die Einbauregel aus T4 ist eingehalten. **Erfüllt.**

Zusätzlich, weil das Paket es ausdrücklich verbietet: `zustand.hpp` wird nicht
eingebunden. Das Wort „zustand" kommt in den drei Dateien genau einmal vor — im
Kommentar, der erklärt, warum es nicht eingebunden wird (`hpp` Z. 27). ✓

## Die vier Fragen meiner Rolle

**1. Ist es wirklich deterministisch? Ja.** Wonach ich gesucht habe, und was ich fand:

| gesucht | Befund |
|---|---|
| Gleitkomma in der Fortschreibung | keins (Grep, s. o.), zusätzlich `#pragma GCC poison float double` |
| Iteration über ungeordnete Mengen | `unordered_`, `HashMap`, `HashSet` — kein Treffer. Es gibt nur `std::span` und `std::array`, beides geordnete Folgen; die Bereichsschleifen laufen über sie |
| mehr als ein Zufallsstrom | kein Zufall überhaupt — kein `rand`, kein `random` |
| Zeit im Ergebnis | kein `chrono`, `time`, `clock`, `__DATE__`, `__TIME__` |
| Speicheradressen im Ergebnis | kein `uintptr_t`, kein `const_cast`, kein `new`/`delete`, kein `asm`. `nimm_bytes` nimmt eine `std::span` und summiert die **bezeichneten Oktette**, nie den Zeiger — das ist der übliche Weg, auf dem eine Adresse in eine Summe gerät, und er ist hier zu |
| plattformabhängige Breiten | `std::uint8_t`/`std::uint64_t` sind exakt breit; die Zerlegung rechnet auf dem Wert, nicht auf dem Speicherbild |

Ein Punkt, den ich eigens geprüft habe, weil er hier die naheliegende Falle wäre:
`nimm_i64` ruft `nimm_bytes(nach_bytes_le(zahl))` — die `span` zeigt auf ein temporäres
`std::array`. Das Temporäre lebt bis zum Ende des Vollausdrucks, der Aufruf liegt darin.
**Kein hängender Verweis.** Der ASan-Lauf bestätigt es.

**2. Sind die Rückkopplungen begrenzt?** Diese Frage hat in diesem Paket keinen
Gegenstand: Es gibt keine Zustandsfortschreibung und keine Schleife, in der Erfolg mehr
Erfolg erzeugt. Der einzige „Umlauf" ist die Hashschleife, und die ist nach der Länge
der Eingabe beschränkt. Die Gegenkräfte aus `spiel.md` liegen ausserhalb dieses Pakets.

**3. Ist die Zustandsausgabe vollständig?** Ebenfalls kein Gegenstand — das Modul hat
keinen Zustand ausser dem Summenstand, und der ist über `wert()` vollständig sichtbar.
Die Prüffrage *„lässt sich aus der Ausgabe allein erkennen, ob richtig gerechnet
wurde?"* beantworte ich für dieses Modul mit **ja**: `pruefsumme_probe` schreibt jede
gerechnete Summe und jede Bytezerlegung hexadezimal aus, neben den Erwartungswert. Das
Protokoll des Baulaufs enthält damit genug, um ohne Zugriff auf den Code gegen die
Quelle zu vergleichen — ich habe das getan.

**4. Halten die Zahlen die Ränder? Ja.**

- **Überlauf:** Der Umbruch `mod 2⁶⁴` ist hier die Rechenvorschrift, nicht ein Fehler.
  Er läuft auf `std::uint64_t`, wo er im Standard definiert ist. Die Begründung im Kopf
  (Z. 51–59), warum dieses Modul ohne den Überlaufwächter aus T7 auskommt, ist richtig:
  In der Datei kommt keine vorzeichenbehaftete Arithmetik vor. Ich habe das gegen
  ADR 0011 gehalten — die Massnahmen dort sichern vorzeichenbehaftete Arithmetik.
- **Division durch null:** Es gibt keine Division und kein Modulo im Programmtext.
- **Rundung über tausend Runden:** Es wird nicht gerundet; alles ist ganzzahlig.
- **Ränder von `i64`:** `I64_MIN` und `I64_MAX` sind beide als Probe da (s. Abnahme 3).

**Handrechnung, zwei Fälle.** Beide nur mit der Vorschrift aus RFC 9923 Abschnitt 2 und
der Zerlegung des Faktors in `2⁴⁰ + 2⁸ + 0xB3`, also ohne das Programm:

*Fall 1 — `fnv1a64("a")`, gegen den veröffentlichten Vektor.*
`h = 0xcbf29ce484222325 XOR 0x61 = 0xcbf29ce484222344` (nur das unterste Oktett:
`0x25 ^ 0x61 = 0x44`). Dann `h · (2⁴⁰ + 2⁸ + 0xB3) mod 2⁶⁴` als Summe dreier Terme:

```
h·2⁴⁰ mod 2⁶⁴ = 0x2223440000000000
h·2⁸  mod 2⁶⁴ = 0xF29CE48422234400
h·0xB3 mod 2⁶⁴ = 0x9AA3B3C863DEA88C
Summe          = 0xAF63DC4C8601EC8C
```

Das ist zeichengleich mit `fnv_test_str[1]` aus [TESTVEK] und mit Z. 107 der Datei.
Die Rechnung bestätigt zugleich die **Reihenfolge** der beiden Schritte: Mit erst
Multiplikation und dann XOR (also FNV-1 statt FNV-1a) käme diese Zahl nicht heraus.

*Fall 2 — `00 61`, ein Wert, den keine Quelle veröffentlicht.* Der interessantere Fall,
weil er nur gegen meine eigene Rechnung stehen kann. Nach dem ersten Oktett steht
`0xaf63bd4c8601b7df` (veröffentlicht als `fnv_test_str[12]`). XOR `0x61` auf das unterste
Oktett: `0xdf ^ 0x61 = 0xbe`, also `h = 0xaf63bd4c8601b7be`. Multiplikation wie oben,
unteres Halbwort:

```
h·2⁴⁰ → untere 32 Bit: 0x00000000
h·2⁸  → untere 32 Bit: 0x01B7BE00
h·0xB3 → untere 32 Bit: 0xB33379DA
Summe  → untere 32 Bit: 0xB4EB37DA
```

Das Protokoll des Baulaufs schreibt für `00 61` den Wert `08326707b4eb37da`. Die unteren
32 Bit stimmen mit meiner Handrechnung überein. **Damit ist belegt, dass das Programm
echtes FNV-1a-64 rechnet und nicht nur die veröffentlichten Vektoren trifft.**

## Drei Nebenbefunde — keine Rückgabe, für den Projektmanager

**N1 — Die Autorenangabe zu RFC 9923 ist unvollständig und umgestellt.** Die Dateien
nennen „Eastlake, D., Hansen, T., Noll, L.C."; der RFC führt L. Noll, K. Vo,
D. Eastlake 3rd und T. Hansen. K. Vo fehlt, die Reihenfolge weicht ab. Die URL, die
Abschnittsnummern und jedes zitierte Zeichen stimmen — der Beleg trägt, nur die
Nennung ist ungenau. Keine Abnahmebedingung betroffen.

**N2 — Zwei Angaben zur [FNV]-Nullsumme konnte ich nicht bestätigen.** Der Satz selbst
und die acht Oktette stehen wortgleich auf der Seite, ebenso das Datum 2011-Oct-23. Der
Zusatz „bestätigt von Richard Heylen 2011-Dec-14" ist beim Abruf nicht aufgetaucht. Ich
sage ausdrücklich **nicht**, dass er falsch ist — er ist von mir nur nicht belegt.
Ebenso: Die Dateien sprechen von der „Tabelle `fnv1a_64_test_vector`"; in der Quelle
heisst so der Strukturtyp, das Feld heisst `fnv1a_64_vector`. Auffindbar bleibt es.

**N3 — Das Loch im mechanischen Gleitkommanachweis gehört nicht diesem Paket, ist aber
hier sichtbar geworden.** `sperre.hpp` wirkt ab der Zeile, an der es steht, und muss
deshalb *nach* allen anderen Einbindungen stehen — also nur in `.cpp`. Der Inhalt von
`pruefsumme.hpp` wird vorher eingelesen und ist von der Vergiftung **nicht** gedeckt.
Für dieses Paket ist das folgenlos (der Grep findet kein Gleitkomma im Kopf), aber ein
späteres `double` in einer Kern-`.hpp` liefe durch die Sperre hindurch. Was T4 im Kopf
trägt, ist der Grep, nicht das `#pragma`. Das ist ein Befund gegen den Mechanismus aus
Paket 0004, nicht gegen 0013 — deshalb hier nur benannt und weitergereicht.

## Wonach ich gesucht und nichts gefunden habe

Damit diese Prüfung von einer, die nicht stattfand, unterscheidbar bleibt: Ich habe
gezielt gesucht nach einer vertauschten Reihenfolge von XOR und Multiplikation (FNV-1
statt FNV-1a — durch Handrechnung ausgeschlossen), nach einem vertippten Ziffernblock in
den Dezimalkonstanten (durch eigene Umrechnung ausgeschlossen), nach einer erfundenen
oder nicht auflösenden Quellenangabe (alle drei URLs abgerufen, alle drei existieren und
enthalten das Zitierte), nach einem selbst erzeugten Erwartungswert, der als fremder
ausgegeben wird (keiner — die einzigen programmeigenen Zahlen stehen auf der
Ungleichheitsseite oder nur auf der Ausgabe), nach einem hängenden Verweis in
`nimm_i64`, nach einer undefinierten Verschiebeweite, nach einer Vertauschung der beiden
Makrosorten `TEST`/`TEST0` und nach dem Einbinden von `zustand.hpp`. Keines davon liegt
vor.
