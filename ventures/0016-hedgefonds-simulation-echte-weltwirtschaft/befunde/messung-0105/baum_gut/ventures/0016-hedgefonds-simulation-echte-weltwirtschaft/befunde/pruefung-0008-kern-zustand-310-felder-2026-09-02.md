---
typ: pruefung
paket: 0008-kern-zustand-310-felder
pruefer: kern-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle fuenf Abnahmebedingungen einzeln mechanisch belegt -- Bau und `ctest` gruen unter ASan/UBSan, die 310 Adressen der Tabelle Zeile fuer Zeile deckungsgleich mit `daten/adressen.md` (eigener `diff`, nicht der Selbsttest des Pakets), und die drei veroeffentlichten Pruefsummen ausserhalb des Programms nachgerechnet.
befunde: 3
---

# `kern::zustand` — 310 Felder, beide Richtungen, 2.480 Byte

Geprueft wurden `kern/include/kern/zustand.hpp`, `kern/src/zustand.cpp` und
`kern/test/zustand_probe.cpp` gegen das Abnahmekriterium aus `aufgaben/0008-*.md`,
gegen `daten/adressen.md` und gegen T15, T16, T17, T9, T12.

Nicht gelesen: `notizen/kernbauer.md`. Die Kommentare in den drei Dateien sind
gelesen, weil sie Teil des Ergebnisses sind — Befund 1 stammt daraus.

## Werkzeugkette und Messumgebung

`cmake 4.2.3`, `g++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0` — also genau die in
`werkzeugkette.cmake` als geprueft festgenagelte Version, keine Warnung des
Versionsvergleichs. `bau/CMakeCache.txt` fuehrt `FABRIK_SANITIZER:BOOL=ON`.

`bau/kern/CMakeFiles/zustand_probe.dir/link.txt` zeigt, dass die Probe wirklich den
geprueften Code misst und nicht sich selbst:

    c++ -fwrapv -fno-fast-math -O2 -g -DNDEBUG -fsanitize=undefined,address
        -fno-sanitize-recover=all ... zustand_probe.cpp.o -o zustand_probe libkern_geprueft.a

## Die fuenf Abnahmebedingungen, einzeln

**1. 310 `int64_t`, `static_assert` rechnet die Feldzahl aus `sizeof` nach und nennt
2480.** Erfuellt. `zustand.hpp:417-419` traegt beide Rechnungen (`sizeof(Zustand) ==
2480` und `sizeof(Zustand) / sizeof(i64) == FELDER`) plus
`is_trivially_copyable_v<Zustand>`. Nachweis, dass sie nicht nur dastehen: Ich habe
`zustand.cpp` mit dem vollen Schaerfesatz aus `flags.make` neu uebersetzt —

    c++ -I kern/include -fwrapv -fno-fast-math -O2 -DNDEBUG -std=c++20 -Wall -Wextra
        -Werror -Wconversion -Wsign-conversion -Wshadow -Wold-style-cast -Wcast-qual
        -Wuseless-cast -Wdouble-promotion -Wfloat-equal -Wnull-dereference -Wformat=2
        -c kern/src/zustand.cpp -o /dev/null

— ohne Warnung und ohne Fehler. Damit sind alle `static_assert` der
Uebersetzungseinheit ausgewertet, einschliesslich der Blockgrenzenrechnung
`zustand.hpp:341-367` und der vier Deckungsnachweise `zustand.cpp:768-777`. Die Probe
druckt zur Laufzeit dieselbe Zahl: `sizeof(Zustand) = 2480 Byte, 310 Felder`.

**2. Der Grep der verbotenen Bauteile geht leer aus.** Erfuellt. `std::vector`,
`std::string`, `std::unordered_map`, `std::optional`, `new `, `delete ` — kein Treffer
in `zustand.cpp` und `zustand.hpp`. Dazu geprueft, weil `kern/CMakeLists.txt` es als
Pruefregel fuehrt: `reinterpret_cast`, `const_cast`, `bit_cast`, `memcpy`, `union`,
`asm` — ebenfalls kein Treffer, auch nicht in der Probe.

**3. Jede der 310 Zeilen ueber die Adressabbildung erreichbar, und die Abbildung kennt
keine Adresse, die dort nicht steht.** Erfuellt, und das ist die Bedingung, an der ich
am laengsten gestanden habe, weil der Selbsttest des Pakets sie **von innen** nachweist.
Ich habe sie deshalb dreifach von aussen gemessen:

*Erstens, Text gegen Text.* Die Adressspalte aus `daten/adressen.md` und die Zeilen aus
`ADRESSTABELLE` unabhaengig voneinander extrahiert und gegeneinander gelegt:

    diff <(grep -oE '^\| [0-9]+ \| `[^`]+`' daten/adressen.md | sed -E 's/^\| [0-9]+ \| `//; s/`$//') \
         <(sed -n '/ADRESSTABELLE = {/,/^};/p' kern/src/zustand.cpp | grep -oE '^ +"[^"]+"' | tr -d ' "')
    -> IDENTISCH

Dazu: 310 Zeilen im Verzeichnis (`Grep -c`), die laufenden Nummern gegen `seq 1 310`
lueckenlos, die Indexkommentare der Tabelle gegen `seq 0 309` lueckenlos, und im
Verzeichnis keine Adresse zweimal (`sort` gegen `sort -u`, kein Unterschied).

*Zweitens, Rechenvorschrift gegen Verzeichnis, von Hand.* Fuenfzehn `stelle_*`-Werte
ohne Uebersetzer ausgerechnet und gegen die Verzeichniszeile gelegt, mindestens einer
je Gruppe und je Blockgrenze:

| Aufruf | gerechnet | Verzeichnis |
|---|---:|---|
| `stelle_sektorgroesse(DE, 2, Preis)` | 88+4+3 = 95 | 96 `land.DE.sektor.2.preis` |
| `stelle_aggregat(RW, Wechselkurs)` | 176+12+6 = 194 | 195 `restwelt.wechselkurs` |
| `stelle_politisch(BR, Einfluss)` | 132+21+2 = 155 | 156 `land.BR.einfluss` |
| `stelle_instrument(CN, Haushalt, Gegendruck)` | 44+24+8+2 = 78 | 79 `land.CN.instrument.haushalt.gegendruck` |
| `stelle_restdauer(US, Regierungsdruck)` | 0+40+2 = 42 | 43 `land.US.regierungsdruck_rest` |
| `stelle_basiswechsel(BR)` / `(RW)` | 175 / 197 | 176 / 198 |
| `stelle_handel(DE, US, 1)` | 198+(2·4+0)·2+0 = 214 | 215 `handel.DE.US.1` |
| `stelle_handel(BR, RW, 2)` | 198+(3·4+3)·2+1 = 229 | 230 `handel.BR.RW.2` |
| `stelle_handel(RW, US, 1)` | 198+(4·4+0)·2+0 = 230 | 231 `handel.RW.US.1` |
| `stelle_weltpreis(2)` | 239 | 240 `welt.preis.2` |
| `stelle_nachahmer(DE, 3)` | 240+6+2 = 248 | 249 `fonds.nachahmer.DE.3` |
| `stelle_fonds(Anlegerbestand)` | 254+3 = 257 | 258 `fonds.anlegerbestand` |
| `stelle_ueberrendite(3)` | 261 | 262 `fonds.ueberrendite.3` |
| `stelle_position(steckplatz_anleihe(BR))` | 262+19 = 281 | 282 `fonds.position.anleihe.BR` |
| `stelle_beteiligung(CN, 2, Restdauer)` | 282+8+1 = 291 | 292 `fonds.beteiligung.CN.2.restdauer` |
| `stelle_partie(ParameterPruefsumme)` | 308 | 309 `partie.parameter_pruefsumme` |

Alle sechzehn treffen. Besonders angesehen habe ich die Gegenueberrechnung im Handel
(`gegenueber = n < v ? n : n - 1`, `zustand.cpp` ueber `zustand.hpp:589`): Sie ist die
einzige Stelle des Pakets, an der ein Index nicht linear laeuft, und sie stimmt fuer
`n < v`, `n > v` und die Restwelt als Quelle wie als Ziel.

*Drittens, ueber die oeffentliche Schnittstelle.* `ctest` gruen, 4 von 4. Die Probe
kennt die Tabelle nicht und meldet:

    Rundlauf Adresse <-> Platz: 310 von 310 genau einmal
    Adressfunktionen decken 310 von 310 Plaetzen genau einmal

Die Gegenrichtung ist mitgeprueft: echtes Praefix (`…sektor.1.prei`), echte
Verlaengerung (`…sektor.1.preis.`), leerer Text, Nullzeiger, `land.RW.leitzins`,
`handel.US.US.1`, `fonds.position.waehrung.RW` und die `rest`-Schreibweise aus Befund 1
des Verzeichnisses werden alle **nicht** gefunden. Ich habe `gleich()` dafuer von Hand
durchgespielt: Der Vergleich liest nie ueber das Nullbyte des kuerzeren Textes hinaus.

**4. Die Reihenfolgen aus T9 als Aufzaehlung mit ausgeschriebenen Nummern, nicht als
Kommentar.** Erfuellt. `Gebiet`, `Sektor`, `Instrument`, `SektorGroesse`, `Aggregat`,
`PolitischeGroesse`, `InstrumentFeld`, `Restdauerzaehler`, `MarktGroesse`,
`FondsGroesse`, `BeteiligungsFeld`, `PartieFeld` und `Steckplatz` — jede mit fester
Grundzahl und jeder Eintrag mit ausgeschriebener Nummer. `Sektor` zaehlt ab eins wie die
Adresse, die Umrechnung steht an genau einer Stelle (`sektor_index`).

**5. Kein Gleitkomma (T4), keine Fremdabhaengigkeit (T2).** Erfuellt. Kein `float`,
`double`, `long double` in den drei Dateien. `sperre.hpp` steht als letzte
Include-Zeile in `zustand.cpp` und in `zustand_probe.cpp` und — richtig — in keiner
`.hpp`. Eingebunden werden ausschliesslich `<array>`, `<cstddef>`, `<cstdint>`,
`<type_traits>`, `<cstdio>` und Koepfe des eigenen Kerns.

## Die vier Fragen meiner Rolle

**1. Ist es wirklich deterministisch?** Ja, soweit dieses Paket reicht. Kein
Gleitkomma; keine Iteration ueber eine streuende Menge (es gibt nur Indexschleifen ueber
`std::array`); kein Zufall in diesem Paket; keine Zeitquelle (`chrono`, `time`, `clock`,
`rand`, `getenv` kommen nicht vor); keine veraenderliche Ablage auf Namensraumebene.
**Die Speicheradresse gelangt nirgends ins Ergebnis**, und das war die Frage, die hier
haette schiefgehen koennen: `index_zu_adresse` gibt einen Zeiger zurueck, aber weder
`erste_dopplung()` noch `adresse_zu_index` vergleichen Zeiger — beide vergleichen ueber
`gleich()` den Inhalt. Waeren es Zeiger, haenge das Ergebnis daran, ob der Uebersetzer
gleiche Zeichenkettenkonstanten zusammenlegt. `nach_bytes` und `pruefsumme_von` laufen
ueber den **Wert** jedes Feldes und rufen `pruefsumme::nach_bytes_le` auf; kein Byte des
`Zustand` wird als Byte gelesen. Damit ist T12 nicht behauptet, sondern gebaut.

**2. Sind die Rueckkopplungen begrenzt?** Fuer dieses Paket nicht anwendbar im engeren
Sinn — `Zustand` schreibt sich nicht fort, `schritt.hpp` ist noch ein Rumpf. Die Frage,
die hier zu stellen ist, lautet: Traegt der Zustand fuer jede Gegenkraft aus `spiel.md`
das Feld, das sie braucht? Nachgesehen gegen `spiel.md` Zeilen 246-265 und die acht
Rueckkopplungskanaele aus Zeile 528: Aufsichtszaehler, Nachahmerzaehler, Gegendruck je
Instrument, Restverzoegerung je Instrument, die drei Restdauerzaehler je Land,
Zustimmung, Einfluss, Sichtbarkeit, Marktanteil, die drei Ueberrenditerunden und
`partie.mandatsstand` haben alle eine Adresse. Keine Gegenkraft ist im Zustand ohne
Traeger. Die Betragsgrenze je Steckplatz (`stufen_max`) ist nach `technik.md` ein
Parameter und nach Paket 0020 ein eigenes Arbeitspaket — dass `schreibe` sie nicht
erzwingt, ist deshalb kein Befund.

**3. Ist die Zustandsausgabe vollstaendig?** Die drei Ebenen sind Paket 0010. Geprueft
habe ich, ob dieses Paket sie moeglich macht: `index_zu_adresse` deckt alle 310, `lies`
gibt jeden Wert, `operator==` ist feldweise. Uebersicht, Detail und Diff sind damit
baubar. **Die Ausgabe der Probe selbst ist ausreichend**, um zu erkennen, ob richtig
gerechnet wurde und nicht nur, ob es lief: Sie druckt `sizeof`, beide Deckungszahlen,
die Steckplatzzahlen und drei Pruefsummen im Wortlaut. Insbesondere der Zaehlzustand
(Feld `i` = `i`) unterscheidet eine richtige von einer vertauschten Feldreihenfolge —
und weil die Zahl gedruckt wird, ist sie von aussen nachrechenbar. Genau das habe ich
getan (siehe Frage 4).

**4. Halten die Zahlen die Raender?** Ja. Nachgerechnet:

* `lies`/`schreibe`/`index_zu_adresse` pruefen `index >= FELDER`; ein negativer Index
  wird als `std::size_t` riesig und faellt in dieselbe Pruefung. Die Probe faehrt jede
  dieser drei Grenzen einzeln an und faengt den Abbruch.
* `stelle_ueberrendite(0)` prueft `runden_zurueck < 1` **vor** der Subtraktion; ein
  Unterlauf ist nicht moeglich.
* `sektor_index` faengt `0` und `> 3` ab, bevor `nummer - 1` gerechnet wird.
* `Aufbau::haenge_an` bricht bei `laenge + 1 >= 64` ab; nach dem letzten zugelassenen
  Schreibzugriff steht `laenge` hoechstens auf 63, das Nullbyte an Position 63 bleibt
  also immer stehen. Die laengste tatsaechliche Adresse hat 47 Zeichen.
* Der einzige Umlauf im Paket ist FNV-1a auf `std::uint64_t` — vorzeichenlos, also
  vom Standard definiert und die Rechenvorschrift selbst. Es gibt keine Division und
  keine Rundung in diesem Paket, also auch nichts, was sich ueber tausend Runden
  aufsummieren koennte.

**Und der Fall, den ich von Hand nachgerechnet habe:** die drei veroeffentlichten
Pruefsummen, in beliebig genauer Ganzzahlarithmetik **ausserhalb** des Programms, aus
der Vorschrift und den beiden RFC-Konstanten neu aufgebaut. Das bricht den Kreis „das
Programm prueft sich selbst":

| Zustand | Probe druckt | ausserhalb gerechnet |
|---|---|---|
| Nullzustand, geschlossene Form `basis · prim^2480 mod 2^64` | `01d663224c4054e5` | `0x1d663224c4054e5` |
| Feld `i` = `i`, 310 Felder Little-Endian | `25e8b19071bea26c` | `0x25e8b19071bea26c` |
| letztes Feld = −1, sonst null | `a491e70cc3f70d5d` | `0xa491e70cc3f70d5d` |

Der zweite Wert ist der aussagekraeftige: Er entsteht aus 2.480 Bytes, die ich selbst
als `(i >> 8k) & 255` fuer `k = 0…7` aufsteigend gebildet habe. Dass er trifft, belegt
zugleich die Feldreihenfolge, die Little-Endian-Zerlegung, die acht Bytes je Feld und
beide FNV-Konstanten — vier Vorgaben aus T12 in einer Zahl.

## Befunde

Keiner der drei bricht eine Abnahmebedingung. Alle drei gehen an den Projektmanager.

### Befund 1 — ein Kommentar behauptet einen Widerspruch zwischen zwei Vorgaben, den es nicht gibt

`kern/include/kern/zustand.hpp:209-212`, ueber `enum class FondsGroesse`:

> „Die Reihenfolge weicht von der Aufzaehlung in T15 ab: Dort steht ‚Kasse, Hebelstand,
> Sichtbarkeit, Anlegerbestand, Marktanteil' als Fliesstext, das Verzeichnis fuehrt
> `sichtbarkeit` vor `anlegerbestand`."

Der zitierte Satz aus T15 fuehrt `Sichtbarkeit` bereits vor `Anlegerbestand`. Der
Kommentar widerlegt sich in seinem eigenen Zitat.

**So erzeugt man den Befund:** `technik.md:477` lesen —
`| Fonds, Aggregat | Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil | 5 |`
— und daneben `daten/adressen.md` Zeilen 255-259 (`kasse`, `hebelstand`,
`sichtbarkeit`, `anlegerbestand`, `marktanteil`) und `spiel.md:212-213` (dieselbe
Folge). Alle drei Quellen und der Code stimmen ueberein; eine Abweichung gibt es
nirgends.

**Warum das mehr ist als ein Schreibfehler:** In dieser Fabrik ist ein gemeldeter
Widerspruch zwischen zwei Vorgaben ein Arbeitsgegenstand — Befund 1 des Verzeichnisses
(`rest` gegen `restverzoegerung`) ist genau so einer und wartet auf einen ADR. Ein
zweiter, erfundener Widerspruch an derselben Stelle kostet den naechsten Leser die
Nachrecherche, die ich hier gefuehrt habe, und im schlechteren Fall einen ADR fuer
nichts. Der **Code ist richtig**; zu aendern ist der Kommentar.

### Befund 2 — die drei Dateien liegen in einem Commit mit fremdem Betreff

`git log --oneline -- kern/include/kern/zustand.hpp` nennt fuer dieses Paket keinen
Commit. Gefunden wird es unter:

    770e7b4 kernbauer: 0012-zufall-abgeleitete-stroeme (3 Dateien)
     kern/include/kern/zustand.hpp      724 +++++
     kern/src/zustand.cpp               843 +++++
     kern/test/zustand_probe.cpp        521 +++++

Der Dateisatz ist **genau** der aus dem Feld `dateien` von 0008 — die Auflage „keine
Datei ausserhalb deiner drei anfassen" ist also eingehalten. Falsch ist nur der
Betreff: Wer 0008 in der Geschichte sucht, findet es nicht, und wer 0012 zurueckdreht,
nimmt 0008 mit. Ich habe denselben Befund am 2026-09-02 schon einmal notiert (bei der
Ruecklauf-Behebung an 0004 lag die Aenderung ebenfalls unter fremdem Betreff); es ist
das zweite Mal, also ein Muster und kein Ausrutscher. Kein Ruecklaufgrund fuer den
Bauagenten — der Commit entsteht im Runner.

### Befund 3 — der Fehlerwert von `adresse_zu_index` zeigt auf ein gueltiges Feld

`zustand.hpp:432-435`: `struct Adressfund { bool gefunden = false; Index index = 0; };`
Eine unbekannte Adresse liefert `{false, 0}`. Der Platz 0 ist aber
`land.US.sektor.1.wertschoepfung` — eine getragene Groesse des Modells.

**So erzeugt man den Fehler, Schritt fuer Schritt:**

1. Ein Aufrufer aus Protokoll, Testvorlage oder Oberflaeche bildet eine Adresse mit
   einem Tippfehler, etwa `land.US.sektor.1.wertschoepfun`.
2. `adresse_zu_index(...)` gibt `{false, 0}` zurueck.
3. Der Aufrufer wertet `.gefunden` nicht aus und nimmt `.index`.
4. `zustand.schreibe(0, wert)` bricht **nicht** ab — 0 ist ein gueltiger Index — und
   legt den Wert auf die Wertschoepfung des US-Agrarsektors.

Das ist genau die Bauart, gegen die dieser Kern an anderer Stelle ausdruecklich
entschieden hat: `festkomma.hpp:42-49` begruendet den harten Abbruch damit, dass „ein
stiller Ersatzwert eine Zahl waere, die keine Pruefung bemerkt" — und dass eine falsche
Zahl in den Regressionsbestand wandert, dort zum Sollwert wird und jede spaetere
Behebung rot macht. Hier ist der stille Ersatzwert wieder da, nur als Index statt als
Zahl.

`std::optional` ist nach Abnahmebedingung 2 ausgeschlossen, ein eigener Ergebnistyp
also richtig. Es geht allein um den Fehlerwert: `Index index = FELDER` statt `0` macht
aus dem stillen Fehlschreiben einen Abbruch in `lies`/`schreibe`, kostet nichts und
aendert keine Adresse. Ob das ein eigenes Arbeitspaket wert ist, entscheidet der
Projektmanager.

## Wonach ich sonst gesucht und nichts gefunden habe

* **Ein Feld zu viel oder zu wenig irgendwo in der Mitte.** Vier unabhaengige
  Zaehlungen: `sizeof`, die Blockgrenzen-`static_assert`-Kette (`176 → 198 → 238 → 240
  → 252 → 254 → 259 → 262 → 282 → 306 → 310`), die 310 Zeilen der Tabelle und die 310
  Zeilen des Verzeichnisses. Alle vier gehen auf und sind nicht dieselbe Rechnung.
* **Ein Steckplatz zu viel.** 20 Adressen, 19 spielbar, `Waehrung_US` dauerhaft leer und
  trotzdem adressierbar — nachgewiesen ueber `steckplatz_spielbar` und ueber
  `adresse_zu_index("fonds.position.waehrung.US")`. `steckplatz_spielbar` ist die
  einzige Stelle, an der die Ausnahme steht; eine zweite Fassung gibt es nicht.
* **Auffuellbytes oder eine Anordnung des Uebersetzers in der Byteform.** Nicht
  moeglich: `nach_bytes` laeuft ueber den Index und den Wert, nie ueber das Speicherbild.
  Die drei naheliegenden Abkuerzungen (`memcpy`, `reinterpret_cast`, `union`) kommen
  nicht vor.
* **Ein `-Wconversion`-Loch.** Der Neubau mit dem vollen Schaerfesatz ist ohne jede
  Warnung durchgelaufen, `-Werror` also nicht durch eine unterdrueckte Meldung erkauft.
* **Etwas, das die Skalenklasse braucht.** `daten/adressen.md` fuehrt je Adresse eine
  Klasse `K 1…12` und einen Herkunftseintrag; der Kern traegt beides nicht. Fuer 0008
  ist das kein Mangel — die Abnahme verlangt es nicht. **Hinweis an den Projektmanager:**
  Die Abnahme von 0010 verlangt Wert, Skalenklasse *und* Herkunft je Adresse. Woher 0010
  die beiden Spalten nimmt, ist heute nicht entschieden; eine zweite Tabelle ueber
  dieselben 310 Adressen waere die Sorte Doppelfuehrung, gegen die T17 argumentiert.
