---
id: 0122-strichrechnung-sperre-in-sperrehpp
rolle: kernbauer
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/sperre.hpp]
abnahme: `sperre.hpp` vergiftet `__builtin_add_overflow` und `__builtin_sub_overflow`; der unveraenderte Baum bleibt in beiden Profilen gruen, und eine zweite Fassung der Strichrechnung in `kern/src/werte.cpp` -- eigene Funktion im anonymen Namensraum, `using festkomma::plus` entfernt -- bricht die Uebersetzung mit "attempt to use poisoned" ab, wo sie heute gruen durchlaeuft. Beide Haelften sind nachzuweisen, die zweite an einem Wegwerfbaum.
---

# Die Strichrechnung braucht dieselbe Sperre wie das Gleitkomma -- und sie passt ohne Ausnahmeliste

**Vorgeschlagen am 2026-09-05 vom `kern-pruefer` aus der Pruefung zu Paket 0087
(`urteil: geprueft`, `befunde: 0`).** Das Paket ist in Ordnung; dieser Vorschlag
betrifft die Luecke, die sein Bauagent selbst benannt hat.

## Der Sachverhalt

Die zweite Abnahmebedingung von 0087 lautet "`werte.cpp` hat keine eigene Fassung
mehr". Sie ist erfuellt -- aber sie ist eine Aussage ueber die **Gestalt** des
Quelltexts, und keine Messung unterscheidet sie. Ich habe das nicht geglaubt,
sondern gefahren: Ein Baum aus dem geprueften `HEAD`, in dem die alte lokale
Fassung von `plus` in den anonymen Namensraum von `werte.cpp` zurueckgelegt und die
Zeile `using festkomma::plus;` entfernt ist, **uebersetzt und laeuft gruen** -- 10
von 10 Proben, Profil `ON`.

Damit ist der Satz aus T6, `festkomma.hpp` sei "die einzige Rechenstelle des Kerns",
heute genau das, was 0087 abschaffen wollte: ein Satz, den ein Mensch lesen muss.

## Warum das jetzt faellt und nicht spaeter

Der Verlauf ist im Repo dreimal aktenkundig, und 0087 nennt ihn in seiner eigenen
Begruendung: Der Kopf von `meldung.hpp` beschreibt ihn fuer die Meldungsklasse,
0074 rechnet ihn fuer die Belegstellen (sechs Pakete Handnachfuehrung, bis 0059 den
Riegel baute) und fuer den Warnsatz (0046, 0058, 0060) vor. Bei einer
Ueberlaufpruefung heisst Auseinanderlaufen: ein Modul bricht ab, das andere bricht
um -- und mit `-fwrapv` bricht es **still** um.

Heute ist der billige Tag: Die beiden Bausteine kommen im ganzen Kern und im
Pruefstand als Code genau zweimal vor, beide in `festkomma.hpp`. Der Stand ist
sauber; nach dem ersten Verstoss ist es Nachfuehrung.

## Die Bauform -- und warum der Einwand aus 0074 hier nicht greift

0074 hat fuer Massnahme **4.3** einen Textriegel gemessen und **verworfen**: Ob
`a * b` zwei `i64` mit Groessenbedeutung multipliziert, traegt die Zeile nicht bei
sich, und ein zeilenlokaler Klassierer braeuchte eine Ausnahmeliste nach Pfadnamen.
Der Einwand ist richtig -- und er gilt fuer **4.2 nicht**. `__builtin_add_overflow`
und `__builtin_sub_overflow` sind Bezeichner, keine Operatoren: Es gibt keine
Typfrage, kein Doppelleben als Adressrechnung, keinen Grenzfall.

0074 nennt im selben Absatz auch die Bauform, die ohne Ausnahmeliste auskommt --
"eine Sperre, die der Uebersetzer haelt" -- und haelt sie fuer 4.3 fuer nicht
nachruestbar, weil man `operator*` fuer eingebaute Typen nicht abschalten kann. Fuer
zwei benannte Bezeichner ist sie es sehr wohl, und der Kern besitzt das Werkzeug
bereits: `#pragma GCC poison` in `sperre.hpp`, seit T4 fuer `float` und `double`.

**Die Einbauregel jener Datei ist genau das, was den Fall traegt.** `sperre.hpp` ist
die *letzte* Zeile des Include-Blocks jeder Kernquelle; die Vergiftung gilt ab dort
bis zum Ende der Uebersetzungseinheit. `festkomma.hpp` ist zu diesem Zeitpunkt schon
vollstaendig gelesen. Es braucht deshalb **keine** Ausnahme fuer die eine erlaubte
Stelle -- die Reihenfolge ist die Ausnahme.

## Gemessen, bevor ich das hier abgegeben habe

Drei Baeume, jeder einzeln konfiguriert und gefahren, Profil `ON`:

| Baum | Ergebnis |
|---|---|
| `HEAD` + Sperrzeile, sonst unveraendert | **gruen**, 10 von 10 -- die Sperre kostet heute nichts |
| `HEAD` + Rueckfall auf die lokale Fassung, ohne Sperrzeile | **gruen** -- das ist die Luecke |
| `HEAD` + Rueckfall + Sperrzeile | **rot beim Uebersetzen**: `werte.cpp:81: error: attempt to use poisoned '__builtin_add_overflow'` |

Die erste Zeile ist die Positivkontrolle und nicht wegzulassen: Eine Sperre, die
alles verbietet, sieht im Negativtest identisch aus.

Die zu schreibende Zeile ist eine:

    #pragma GCC poison __builtin_add_overflow __builtin_sub_overflow

Dazu der Absatz im Kopf, der sagt, **warum** sie dort steht und nicht in
`festkomma.hpp` -- naemlich wegen der Einbauregel oben. Ohne diesen Satz sieht die
Zeile aus wie ein Verbot der Bausteine, und sie ist das Gegenteil: die Zusicherung,
dass es bei der einen Stelle bleibt, die sie benutzt.

## Warum ein eigenes Paket und nicht Teil von 0087 oder 0074

Nicht 0087: Dessen Dateiliste nennt `sperre.hpp` nicht, und sein Bauagent schreibt
selbst hin, ein Riegel dafuer waere ein eigenes Paket. Nicht 0074: Das ist ein
Architektenpaket auf `technik.md` mit dem ausdruecklichen Satz "Kein Code", und es
behandelt 4.3, nicht 4.2. Die beiden schneiden sich nicht -- weder in der Datei noch
in der Rechenart -- und koennen nebeneinander laufen.

## Was ausdruecklich nicht dazugehoert

Keine Sperre fuer `*`, `+` oder `-` als Operator. Das ist die Frage von 4.3, sie
liegt bei 0074, und sie ist nach dessen Messung mit diesem Mittel nicht loesbar. Wer
sie hier mitentscheidet, entscheidet sie an der falschen Stelle.
