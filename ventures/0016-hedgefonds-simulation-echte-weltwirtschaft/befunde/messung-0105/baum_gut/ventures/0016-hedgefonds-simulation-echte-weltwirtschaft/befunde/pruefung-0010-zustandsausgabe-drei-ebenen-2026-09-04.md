---
typ: pruefung
paket: 0010-zustandsausgabe-drei-ebenen
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle fuenf Teilbedingungen einzeln mechanisch nachgefahren -- Zeilenzahl gemessen, Bereichsdeckung je Adresse gezaehlt, die drei Unterschiedszahlen von Hand nachgerechnet, die Deckung aller 310 am erzeugten Text -- und der Pufferrand mit einer eigenen Messprobe an seinem unguenstigsten Fall gefahren; dazu 50 Mutationen in zwei Runden.
befunde: 2
---

# Pruefung 0010 -- die drei Zustandsebenen

## Wie gemessen wurde

Bau aus `git archive HEAD ventures/0016-... specs decisions` in einen Baum ausserhalb
des Arbeitsbaums; `kern/` ist bei HEAD (`ccd0d54`) unveraendert, `git status` leer.
Beide Profile, `Debug` und `RelWithDebInfo`, die Proben in beiden gegen `kern_geprueft`
mit `-fsanitize=undefined,address`.

Zwei eigene Programme, beide **nur im Pruefbaum**, keine Datei des Pakets angefasst:
`randmass_probe` (Pufferrand) und `kennung_probe` (Klasse 12). Dazu zwei
Mutationslaeufe, 50 Mutationen, je Mutation eine Textersetzung, uebersetzen, Probe
fahren, Datei zuruecksetzen. Der Nachlauf am unveraenderten Baum war beide Male gruen.

---

## Frage 1 -- Ist es wirklich deterministisch?

**Ja, strukturell und gemessen.**

*Strukturell.* `grep -nE "float|double"` ueber die drei Paketdateien: kein Treffer
(Rueckgabe 1). `src/zustandsausgabe.cpp:29` bindet `kern/sperre.hpp` als **letzte**
Include-Zeile ein, genau einmal -- ab dort ist `float`/`double` ein Fehler des
Vorverarbeiters, kein Vorsatz. Keine Treffer fuer `unordered_`, `std::map`, `std::set`,
`chrono`, `rand(`, `random_device`, `reinterpret_cast`, `uintptr_t`, `getenv`,
`__DATE__`, `__TIME__`. Jede Schleife laeuft ueber `Index platz = 0 ... FELDER-1` oder
ueber ein `std::array` -- keine ungeordnete Menge. Eine Speicheradresse gelangt nie in
die Ausgabe: `Ausgabe::text` schreibt allein Zeichen aus einem `const char*`,
`Ausgabe::zahl` allein Dezimalziffern einer `i128`.

*Gemessen.* Die Ausgabe von `zustandsausgabe_probe` ist zwischen `Debug` (-O0, mit
Sanitizern) und `RelWithDebInfo` **zeichengleich** -- `diff` meldet nur die zwei
Pfadzeilen, die ctest selbst schreibt. Zeichengleich heisst hier auch: dieselben
Zaehlungen, 14 Zeilen und 1.535 Zeichen fuer die Uebersicht, 312 Zeilen und 31.581
Zeichen fuer den Unterschied ueber alle 310.

*Die eine doppelt gefuehrte Liste.* `src/zustandsausgabe.cpp:57` fuehrt
`GEBIET_KUERZEL` ein zweites Mal neben `src/zustand.cpp:403`. Das ist bewacht und nicht
behauptet: Die Probe liest das Kuerzel aus `index_zu_adresse` einer Handelsadresse
zurueck. Mutation `N01` (CN und DE in der Kernliste getauscht) wird rot.

## Frage 2 -- Sind die Rueckkopplungen begrenzt?

**Hier gibt es keine, und das ist nachweisbar statt beteuert.** Jede Bezugnahme auf
einen `Zustand` in beiden Paketdateien ist `const zustand::Zustand&` (7 Stellen,
`grep -nE "Zustand&"`); kein `setze`, keine `Startbelegung`, kein Schreibweg. Das Modul
kann keine Schleife schliessen, weil es nichts zurueckschreibt.

Die einzige gerechnete Groesse ist `werte::fondsvermoegen` in `uebersicht`. Ihre
Wertebereichsschranke aus T47 wird **geerbt und nicht zweitgeschrieben** -- und dass sie
wirklich geerbt wird, ist gemessen: Mutation `M26` (statt der Rechnung die Kasse lesen)
scheitert schon beim Uebersetzen, und die Probe erzwingt den Abbruch auf einem Zustand
mit Wechselkurs 0 samt Meldungswortlaut. `detail` und `diff` rechnen keine
Modellgroesse und brechen auf keinem Zustand ab; auf demselben kaputten Zustand liefern
beide weiter Text.

## Frage 3 -- Ist die Zustandsausgabe vollstaendig?

**Fuer die 310 Adressen: ja, und mechanisch.** Die Probe weist die Deckung zweimal nach
-- einmal in der Vereinigung der drei Ebenen (die Wortlautbedingung) und einmal
**schaerfer je Bereich**: Das Blatt eines Bereichs nennt genau die Adressen, die ihm
gehoeren, keine weniger und keine mehr, und die zehn Bereiche summieren auf 310. Der
Vorbedingung wegen -- "kommt vor" heisst "steht als Zeichenfolge da" -- prueft sie
zuerst alle 310 mal 310 Paare darauf, dass keine Adresse in einer anderen steckt. Das
ist die richtige Reihenfolge; ohne sie waere der Nachweis ein Riegel, der Dasein prueft
und Wirkung behauptet.

Gemessen statt gelesen: `M10` (eine einzige Adresse aus der Detailebene genommen) wird
rot, `M38` (Bereichsliste verengt) wird rot, `M13` (Schlusszahl um eins verschoben) wird
rot.

**Was fehlt, fehlt bekannt.** T20 verlangt zur Unterschiedsebene die Ursachenkette aus
T18. Sie ist nicht gebaut, der Kopf des Moduls sagt es, und der Bauagent hat dafuer
`0091-diff-ursachenkette-nach-t20` auf `vorschlag` gelegt. Die Abnahme dieses Pakets
verlangt die drei Zahlen, und die drei Zahlen stehen da. Kein Befund von mir; ich
wiederhole 0091 nicht.

**Was nicht fehlt, aber unbewacht ist:** siehe Befund 1.

## Frage 4 -- Halten die Zahlen die Raender?

**Ja, mit Luft, und der unguenstigste Fall ist gefahren worden statt gerechnet.**

`randmass_probe` haelt zwei Zustaende gegeneinander, in denen **jedes** der 310 Felder
sich maximal unterscheidet: `vorher = I64_MAX` (19 Zeichen), `nachher = I64_MIN` (20
Zeichen), Differenz `-18446744073709551615` (21 Zeichen). Das ist die laengste
Zeilenform, die die Ebene erzeugen kann.

| Messung | Ergebnis |
|---|---|
| `diff` unguenstigster Fall | **46.853** von 60.289 Zeichen, 312 Zeilen |
| abgeschnitten | nein; Marke `[...]` kommt nicht vor |
| Schlusszeile `310 von 310 Adressen geaendert.` | vorhanden |
| Adressen, die im Blatt fehlen | **0** von 310 |
| laengste erzeugte Zeile | **182** Zeichen (`ZEILE_ZEICHEN` = 192) |
| `detail`, groesster Bereich (`fonds`, 64 Adressen) | 6.574 von 60.289 Zeichen |

Damit haelt der Satz im Kopf des Moduls -- "Der Puffer traegt deshalb **alle** 310" --
mit 22 % Rand, und die Zeilenbreite mit 10 Zeichen. Die Gegenprobe dazu steht daneben:
`M35` (Puffer auf die Haelfte gesetzt) wird rot, `M27` (Pufferschranke um eins
verschoben) wird unter dem Adressen-Sanitizer rot, `M28` und `M29` (Merker
beziehungsweise Marke gestrichen) werden rot.

*Uebersicht.* 14 Zeilen, feste Anzahl, unabhaengig vom Zustand. Der Puffer fasst
7.681 Zeichen; die Ebene druckt 55 Zahlen zu hoechstens 20 Zeichen plus rund 1.260
Zeichen festen Text, also hoechstens rund 2.360. Die Grenze von 40 Zeilen ist um den
Faktor drei unterschritten.

*Von Hand nachgerechnet, drei Faelle:*

- `fonds.marktanteil alt 420 neu 500 Differenz 80` -- 500 minus 420 = 80. Stimmt.
- `I64_MAX - I64_MIN = 9223372036854775807 + 9223372036854775808 = 18446744073709551615`,
  und genau das steht im Protokoll; die Gegenrichtung mit Minuszeichen ebenso. Das ist
  die Zahl, wegen der die Ebene auf `i128` rechnet: In `i64` waere sie unter `-fwrapv`
  die wohlgeformte **-1**. `M07` (dieselbe Rechnung auf `i64`) uebersetzt nicht mehr.
- `werte::bip(US) = 3.000.000` -- drei Sektoren zu je 1.000.000 Wertschoepfung. Stimmt.

*Division:* keine im Modul, also auch keine durch null. *Rundung:* keine -- keine Zahl
wird skaliert, "geteilt wird erst in der Sicht" (T20) ist eingehalten. *Ziffernfeld:*
44 Plaetze fuer hoechstens 39 Stellen einer `i128`, der Rand ist unerreichbar.

---

## Befund 1 -- Zwanzig von fuenfzig Mutationen ueberleben, und sie liegen alle beieinander

**Vorschlag: `0097-zustandsausgabe-probe-zuordnungen-festnageln`.**

Die Ebenen rechnen richtig -- jede Mutation, die eine **Zahl** falsch macht, wird rot.
Was ueberlebt, ist durchweg dieselbe Sorte: eine falsche **Zuordnung von Zahl zu
Beschriftung**. Siebzehn davon sind echte Luecken; drei weitere sind es nicht und stehen
unten.

| Mutation | was sie tut | Probe |
|---|---|---|
| `M15` | `KLASSENNAME` 7 und 8 getauscht (`Realindex` / `Personen`) | GRUEN |
| `M16` | `KLASSENEINHEIT` 8 und 9 getauscht (`Personen` / `Lobbypunkte`) | GRUEN |
| `M18` | Einheit der Klasse 2 durch `Stueck bzw. Runden` ersetzt | GRUEN |
| `N10` | Einheit der Klasse 13 verstellt | GRUEN |
| `M17` | `HERKUNFTSNAME` 0 und 1 getauscht (`Datenanker` / `Entwurf`) | GRUEN |
| `M19` | Spalte `Zoll` liest den Haushaltsstand | GRUEN |
| `M20` | Spalte `Zins` liest das Aggregat statt des Instrumentenstands | GRUEN |
| `M21` | Spalte `Regulierung` durch einen Strich ersetzt | GRUEN |
| `N02` | Spalte `BIP` liest fuer jedes Gebiet das der USA | GRUEN |
| `N03` | Spalte `Zustimmung` durch einen Strich ersetzt | GRUEN |
| `N04` | Spalte `Aufsicht` liest den Einfluss | GRUEN |
| `N05` | eine der drei Ueberrenditen faellt weg | GRUEN |
| `N06` | `Korbwert` liest die Marktrendite | GRUEN |
| `N07` | `Kasse` liest den Hebelstand | GRUEN |
| `N08` | `Jahrgang` liest den Mandatsstand | GRUEN |
| `N09` | die Sektornummer der Weltpreise ist um eins verschoben | GRUEN |
| `N11` | die Kopfzeile der Detailebene ist eine andere | GRUEN |

**Wie man den Fehler erzeugt**, an `M18` durchgespielt, weil sie die teuerste ist:

1. In `kern/src/zustandsausgabe.cpp` in `KLASSENEINHEIT` den zweiten Eintrag
   (`"Tausend USD zu konstanten Preisen 2015"`) durch `"Stueck bzw. Runden"` ersetzen.
2. `cmake --build <bau> --target zustandsausgabe_probe` -- uebersetzt.
3. `ctest -R zustandsausgabe_probe` -- **bestanden.**

Danach behauptet die Detailebene fuer **71 der 310 Adressen** -- die groesste Klasse
ueberhaupt, Wertschoepfung, Kapitalstock, jeder Handelsstrom und der Marktkorb --, ihre
Zahl sei ein Stueckzaehler statt eines Betrags in Tausend USD. Das ist genau die Frage,
zu deren Beantwortung die Ebene laut Arbeitspaket existiert: "Wer hier liest, muss nicht
raten, ob eine Zahl Cent oder Tausend ist."

**Zwei Ursachen, beide benennbar.**

*Erstens:* Die Probe nagelt drei der dreizehn Klassen fest (K1, K4, K6) und eine der
fuenf Herkunftsarten (`Vorgabe`). Die uebrigen zehn und vier sind nur ueber die
Abzaehlung gebunden, und die zaehlt Adressen, keine Zeichenketten. Die
`static_assert`-Kette im Kopf ist stark -- `M36` und `M37` scheitern beim Uebersetzen --,
aber sie sieht Namen und Einheiten grundsaetzlich nicht.

*Zweitens:* Die Grundbelegung `belege_tragfaehig` macht mehrere richtige und falsche
Quellen ununterscheidbar. `M20` ist der Musterfall: Sie setzt `Aggregat::Leitzins` auf
250 **und** `instrument.leitzins.stand` auf 250. Der Kommentar an
`src/zustandsausgabe.cpp:154` erklaert ausdruecklich, warum die Uebersicht "den Herrn und
nicht den Gast" liest -- und keine Probe kann das unterscheiden, weil beide dieselbe
Zahl tragen. Dasselbe bei `N02`: Alle fuenf Gebiete haben BIP 3.000.000.

**Warum das ein eigenes Paket ist und kein Ruecklauf.** Die Abnahme von 0010 ist
erfuellt -- ich habe jede Zeile von `uebersicht` gegen ihre Adresse gehalten, alle vier
Instrumente stehen da und lesen ihr eigenes Feld. Der gebaute Code ist richtig; was
fehlt, ist der Riegel, der ihn richtig **haelt**. Ein Ruecklauf gegen ein Paket, das
liefert, waere die nachtraegliche Erweiterung seines Kriteriums.

**Nicht als Befund gezaehlt, damit die Zahl stimmt** -- drei weitere Ueberlebende, die
keine Luecke sind:

- `M04` (Pruefung auf den leeren Vorspann gestrichen) ueberlebt, weil sie redundant ist:
  Keine der 310 Adressen ist leer oder beginnt mit einem Punkt, deshalb liefert die
  Grenzbedingung darunter ohnehin `false`. Vorsorge, nicht toter Code.
- `M24` und `M25` (die beiden Abbrueche am Ende von `uebersicht` entschaerft) ueberleben,
  weil die Ebene bei fester Zeilenzahl 14 ihre Grenzen von 40 Zeilen und 7.681 Zeichen
  nicht erreichen **kann**. Der Kommentar sagt genau das und begruendet sie mit dem
  naechsten, der eine Zeile ergaenzt. Richtig so.

## Befund 2 -- Die Unterschiedsebene rechnet auf den beiden Kennungen, und T5 verbietet das

**Vorschlag: `0098-diff-kennungen-ohne-differenz`.**

T5 sagt zur Klasse 12 (`Kennungen`): "Bitmuster ohne Groessenbedeutung ... **jede
Arithmetik ausser Gleichheit ist ein Fehler**" (`specs/.../technik.md`, Zeile 291). Der
Kopf des Moduls zitiert die Regel selbst (`zustandsausgabe.hpp`, Zeile 325 bis 327).
`diff` subtrahiert trotzdem, weil es ueber alle 310 Plaetze ohne Ausnahme laeuft.

**Wie man es erzeugt** (`kennung_probe`, zwei Zustaende, die sich in genau einem Feld
unterscheiden):

```
partie.parameter_pruefsumme  alt -6917529027641081856  neu 4611686018427387904
    Differenz 11529215046068469760  [K12 Kennung, Bitmuster ohne Groessenbedeutung]
```

Die Zeile widerspricht sich in sich: Sie sagt am Ende, die Zahl habe keine
Groessenbedeutung, und nennt in der Mitte eine Groessendifferenz. Fuer eine
Parametersatz-Pruefsumme ist `11529215046068469760` nicht bloss unnuetz, sondern die
Sorte Zahl, vor der derselbe Absatz von T5 warnt: eine, "die keine Pruefung bemerkt,
weil sie in keinem Wertebereich liegt". Der Leser dieser Ebene ist nach Arbeitspaket
ausdruecklich ein **Agent**, und der hat keinen Anlass, eine Differenzspalte je Klasse
verschieden zu lesen.

**Warum ich das nicht als `zurueck` werte.** Die Abnahme sagt "nennt **jede** Adresse,
die sich geaendert hat, mit altem Wert, neuem Wert und Differenz" -- ohne Ausnahme. Der
Bauagent hat die Abnahme woertlich genommen, und das war die zulaessige Lesart. Der
Widerspruch liegt zwischen zwei Dokumenten, nicht im Bau, und ihn aufzuloesen ist nicht
meine Stelle: **Ich senke kein Abnahmekriterium und ich hebe keine Vorgabe auf.** Der
Befund geht deshalb an den Projektmanager.

Beide Lesarten sind gleichzeitig erfuellbar -- die Zeile kann alten und neuen Wert
nennen und statt der Differenz einen Strich mit dem Grund tragen. Was davon gilt,
entscheidet nicht der Bauagent und nicht ich.

---

## Wonach ich gesucht und nichts gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Pufferueberlauf** in allen drei Ebenen, am unguenstigsten Fall gefahren, nicht
  geschaetzt -- kein Ueberlauf, kein Abschneiden, 22 % Rand.
- **Ueberlauf in der Differenz** -- auf `i128`, gemessen an beiden Vorzeichen, und die
  Rueckstufung auf `i64` uebersetzt nicht mehr.
- **Division durch null, Rundung, Skalierung** -- kommt im Modul nicht vor.
- **Zeiger oder Speicheradressen in der Ausgabe** -- keine; nur Zeichen und
  Dezimalziffern.
- **Zweite Namenstabelle oder zweite Adressordnung** neben `zustand.cpp` -- nur
  `GEBIET_KUERZEL`, und die ist gegen `index_zu_adresse` bewacht (`N01` rot).
- **Grenzverletzung des Pakets** -- der Commit `ccd0d54` beruehrt genau die Dateien der
  `dateien`-Liste plus die eigene Logbuch- und Vorschlagsdatei.
- **`detail` mit Nullzeiger, mit unbekanntem Vorspann, mit einem abgeschnittenen Namen,
  mit einer vollstaendigen Adresse als Bereich** -- alle vier beantwortet, keiner bricht
  ab.
- **`belegstellen_riegel` ist rot** -- aber am Vorgaengerstand `79e92e7` mit genau
  demselben Ergebnis (Rueckgabe 1), und er nennt keine Datei dieses Pakets. Die
  Fundstellen liegen in `daten/reihen.toml`, `rueckstand.md`, `parameter.toml` und
  `daten/*.md`. Nicht dieses Paket. Die uebrigen 13 Proben sind gruen.
