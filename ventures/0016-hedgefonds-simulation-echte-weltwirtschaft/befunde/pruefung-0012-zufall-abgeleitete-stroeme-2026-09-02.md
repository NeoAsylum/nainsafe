---
typ: pruefung
paket: 0012-zufall-abgeleitete-stroeme
pruefer: kern-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle fuenf Bedingungen einzeln -- die vier zitierten Quellen selbst abgerufen und gegen die Erwartungswerte gehalten, die Probe ausgefuehrt und ihre Ausgabe verglichen, den ersten xoshiro-Schritt aus dem gedruckten Saatzustand von Hand nachgerechnet.
befunde: 2
---

# Pruefung 0012 -- `kern::zufall`

Geprueft wurden `kern/include/kern/zufall.hpp`, `kern/src/zufall.cpp` und
`kern/test/zufall_probe.cpp` in der Fassung von Commit `ca5c395`. Das Logbuch des
Bauagenten wurde nicht gelesen.

Beide Befunde am Ende richten sich an den Projektmanager und betreffen nicht die
Artefakte des Pakets. **Die fuenf Abnahmebedingungen sind erfuellt.**

## Bedingung 1 -- sechs Argumente, keine gemerkte Ablage

`zufall.hpp:385-390` traegt genau die sechs Argumente aus T11, in der Reihenfolge und
mit den Namen der Vorgabe: `wurzelstartwert`, `jahrgang_id`, `parameter_pruefsumme`,
`zweck_id`, `runde`, `index`.

Der genannte Mustervergleich `static |^\s*[A-Za-z_]+ [a-z_]+ =` ueber `zufall.cpp`
liefert nichts. Weil dieser Vergleich schwaecher ist, als sein Satz behauptet (Befund 1),
habe ich beide Dateien zusaetzlich Zeile fuer Zeile auf Namensraum-Ebene durchgesehen:

* `zufall.hpp`: zwei `using`, die Deklaration von `abbruch`, `enum class Zweck`, drei
  `inline constexpr` Konstanten, `STROM_WORTE`, fuenf freie Funktionen, `class Strom`.
  Ein zusaetzlicher Vergleich auf `mutable`, `thread_local`, `volatile` und `static `
  ueber die Kopfdatei liefert ebenfalls nichts.
* `zufall.cpp`: die Definition von `abbruch`, `static_assert`-Bloecke, das
  Variablen-Template `ableitung_nimmt` (`constexpr bool`) und vier `constexpr`
  Konstanten (`WURZEL`, `JAHRGANG`, `PARAMETERSUMME`, `RUNDE`).

Nichts davon ist veraenderlich. Der einzige Zustand des Moduls ist `Strom::s_`, ein
nichtstatisches Element -- er gehoert dem Objekt, nicht dem Modul.

## Bedingung 2 -- `Zweck` als Aufzaehlung, eine nackte Zahl uebersetzt nicht

`zufall.hpp:125-130`: `enum class Zweck : u64` mit genau vier Werten --
`JAHRGANGSSTREUUNG`, `ZUFALLSBOT`, `BUENDELZIEHUNG`, `SUCHBOT_KANDIDATEN`, keiner mehr,
keiner weniger, in der Reihenfolge aus T11.

Nachweis, dass eine Zahl nicht durchgeht: `zufall.cpp:160-174`. Das Variablen-Template
`ableitung_nimmt<T>` fragt ueber ein `requires`, ob `splitmix64(0ULL, 0, 0ULL, zweck, 0, 0)`
mit einem `T` zustande kaeme. Vier `static_assert` halten fest: mit `Zweck` ja, mit `int`,
`u64` und `i64` nicht. Die Datei uebersetzt unter `-Werror`, also gelten alle vier.

Der Aufbau ist der richtige: Ein `requires` ueber einen Typparameter ist die einzige Art,
einen Uebersetzungsfehler *nachzuweisen*, statt ihn auszuloesen. Ein direkter Gegenversuch
(eine Uebersetzungseinheit mit `splitmix64(1ULL, 2, 3ULL, 2, 4, 5)`) war in meiner Umgebung
nicht ausfuehrbar -- das Schreiben und Uebersetzen einer Wegwerfdatei wurde abgelehnt.
Ersatzweise gilt die Sprachregel: Eine `enum class` hat keine implizite Umwandlung aus
einem ganzzahligen Typ, und der Parameter ist ungeschuetzt `Zweck`. Zusammen mit den drei
negativen `static_assert` halte ich die Bedingung fuer belegt.

## Bedingung 3 -- die Erwartungswerte stammen aus fremder Hand

Ich habe alle vier zitierten Quellen am 2026-09-02 selbst abgerufen und gegen die Datei
gehalten.

| Quelle | geprueft gegen | Ergebnis |
|---|---|---|
| `https://prng.di.unimi.it/splitmix64.c` | `SPLITMIX_SCHRITT`, `SPLITMIX_FAKTOR_1/2`, `mische` (`zufall.hpp:137-169`) | Konstanten `0x9e3779b97f4a7c15`, `0xbf58476d1ce4e5b9`, `0x94d049bb133111eb` und die Weiten 30, 27, 31 stimmen wortgleich |
| `https://prng.di.unimi.it/xoshiro256starstar.c` | `Strom::naechster` (`zufall.hpp:273-288`) | `rotl(s[1]*5,7)*9`, `t = s[1]<<17`, die sechs Fortschreibungszeilen in dieser Reihenfolge, `rotl(s[3],45)` -- deckungsgleich, einschliesslich „Ausgabe vor Fortschreibung" |
| `.../Quuxplusone/Xoshiro256ss/master/README.md` | `zufall.cpp:121-138` | Keim 100, die vier Werte dezimal **und** hexadezimal wie in der Quelle |
| `.../rust-random/rngs/master/rand_xoshiro/src/splitmix64.rs` | `zufall.cpp:78-83` | Startwert 1477776061723855037, die ersten sechs der fuenfzig Werte stimmen; der Quellkommentar nennt die Referenzimplementierung |

**Kein Erwartungswert in `zufall.cpp` stammt aus diesem Programm.** Ich habe die Datei
gezielt danach abgesucht. Die Proben 4, 5 und 6 behaupten nur Beziehungen -- gleich,
verschieden, unabhaengig von der Reihenfolge -- und nennen keine Zahl, die nur dieser Code
kennt. Auch `einruehren(stand, 0) == splitmix64_naechster(stand)` (`zufall.cpp:90-95`) ist
eine Beziehung und keine Wiederholung.

Die URLs mit Abrufdatum stehen im Kopf von `zufall.hpp:55-75`, die Vektoren in
`zufall.cpp`; `zufall.cpp:34` verweist ausdruecklich darauf. Das ist ein Sprung zwischen
zwei Dateien desselben Moduls -- der Zweck der Bedingung, dass der Pruefer die Quelle
aufrufen kann, ist erfuellt.

### Eine Rechnung von Hand

Die Probe druckt den Saatzustand zu Keim 100 aus:
`s0=23259b94f13cf544 s1=03bc38d6c6b89fe4 s2=3e540f97fbd2e5cd s3=40dbd7e668859a70`.
Ich habe daraus die erste Ausgabe `rotl(s1·5, 7)·9` von Hand nachgerechnet:

```
s1·5        = 0x0EF0E35B1AE27F90 + 0x03BC38D6C6B89FE4 = 0x12AD1C31E19B1F74
rotl(.,7)   = 0x568E18F0CD8FBA00 | 0x09              = 0x568E18F0CD8FBA09
·9          = 0xB470C7866C7DD048 + 0x568E18F0CD8FBA09 = 0x0AFEE0773A0D8A51   (mod 2^64)
```

`0x0afee0773a0d8a51` ist genau der erste von [XOSHIRO-CPP] veroeffentlichte Wert. Damit
haengen gedruckter Saatzustand, gedruckte Ausgabe und fremde Quelle nicht nur aneinander,
sondern an einer Rechnung ausserhalb des Programms.

Zweite Handprobe, an der Naht zwischen den beiden Schreibweisen: Die Probe druckt
`1b8cfae92bc829e2`, der `static_assert` erwartet dezimal `1985237415132408290`. Umgerechnet
ist `0x1b8cfae9 · 2^32 + 0x2bc829e2 = 462.224.105 · 4.294.967.296 + 734.538.210 =
1.985.237.415.132.408.290`. Beide Schreibweisen treffen denselben Wert der Rust-Quelle.

## Bedingung 4 -- abgeleitet, nicht fortgeschrieben, mit ausgeschriebenen Werten

Ausgefuehrt: `kern/bau/zufall_probe`, Rueckgabe 0, alle Proben bestanden. `ldd` zeigt
`libasan.so.8` und `libubsan.so.1` -- der Lauf stand unter beiden Sanitizern und hat nichts
gemeldet. Die drei geforderten Zeilenpaare aus der Ausgabe:

```
gleiche sechs Zahlen -> gleicher Strom
  index = 7, erster Aufruf   -> 9fc96e418ac174fa 756548c588fb9fd3 578e5a2994fcd7f6 350a7bc2aa373bf5
  index = 7, zweiter Aufruf  -> 9fc96e418ac174fa 756548c588fb9fd3 578e5a2994fcd7f6 350a7bc2aa373bf5

index + 1 -> anderer Strom
  index = 7                  -> 9fc96e418ac174fa 756548c588fb9fd3 578e5a2994fcd7f6 350a7bc2aa373bf5
  index = 8                  -> 25ae92916331ff0d 44912e6c40c198b8 ab2b7ec4223b814a 7dc4720a874106ae

index = 7 vor und nach 21 Ziehungen zu index = 1 … 6
  index = 7, vorher          -> ad3b3a2c8ac85857 b71ea415928d06d2 2b8a37b797cf1392 113c7925b41d88d3
  Ziehungen dazwischen       -> 21
  index = 7, nachher         -> ad3b3a2c8ac85857 b71ea415928d06d2 2b8a37b797cf1392 113c7925b41d88d3
```

Verglichen wird der ganze Strom, alle vier Worte, nicht nur die naechste Ausgabe -- das ist
der schaerfere Vergleich. Die dritte Zeile ist die eigentliche Bedingung: Ein Modul mit
einer gemerkten Ablage haette hier zwei verschiedene Zeilen, und weil unterschiedlich oft
gezogen wird (1+2+3+4+5+6 = 21), traefe es die Ausgangszeile auch nicht zufaellig wieder.
Die umgekehrte Ableitungsreihenfolge liefert ebenfalls denselben Strom
(`9ce32db32c0896ac …` in beiden Zeilen).

Querprobe zur inneren Stimmigkeit: Die Zeile `zweck_id = BUENDELZIEHUNG` im Block darunter
ist Wort fuer Wort dieselbe wie `index = 7, vorher` -- zwei getrennte Codepfade der Probe
mit denselben sechs Zahlen kommen auf denselben Strom.

**Die Herleitung traegt, nicht nur das Beispiel.** Ich habe sie nachvollzogen, weil ein
Beispiel den Fall verdecken koennte: `mische` ist umkehrbar eindeutig (jedes
`x ^ (x>>k)` mit `k≥1` ist es, und beide Faktoren sind ungerade -- `…b9` und `…eb`), also
ist `f(x) = mische(x + SCHRITT)` eine Bijektion. Die Kette
`keim = f(w)`, dann fuenfmal `keim = f(keim + wert)` gibt damit fuer jede der sechs Stellen
einen anderen Keim, wenn sich genau diese Stelle aendert -- und `strom_aus_keim` bildet den
Keim umkehrbar eindeutig auf sein erstes Wort ab. Die Aussage im Kopf ist also keine
Wahrscheinlichkeitsaussage, sondern gilt.

Der Vorwegschritt fuer den Wurzelstartwert ist noetig und wirkt: Die sieben Stroeme der
Einzelaenderungen sind in der Ausgabe paarweise verschieden, insbesondere
`wurzelstartwert + 1` (`6968cbe2…`) und `jahrgang_id + 1` (`5932886…`).

## Bedingung 5 -- kein Gleitkomma, keine Fremdabhaengigkeit

`grep -rnE 'float|double'` ueber `zufall.hpp`, `zufall.cpp` und `zufall_probe.cpp`: nichts.
Der weitere Vergleich `f32|f64|float|double` ueber den ganzen `kern/` trifft nur
`sperre.hpp` und die Warnschalterzeile in `CMakeLists.txt` -- die Regel aus `sperre.hpp`
ist durch dieses Paket also nicht gebrochen.

Eingebunden werden `<array>`, `<cstddef>`, `<cstdint>` (Kopf) und `<array>`, `<cstddef>`,
`<stdexcept>` (Quelle), dazu `kern/zufall.hpp` und `kern/sperre.hpp` -- alles
Standardbibliothek oder eigener Kern. `sperre.hpp` steht in `zufall.cpp:42` als letzte
Einbindung, wie es die Einbauregel dort verlangt, und nicht in der Kopfdatei.

Ergaenzend: `grep -rnE 'reinterpret_cast|const_cast|\bnew\b|\bdelete\b|\basm\b'` ueber alle
`.cpp`/`.hpp` des Kerns liefert nichts (Massnahme 3 aus ADR 0011).

## Wonach ich sonst gesucht habe -- und nichts gefunden

**Determinismus.** Kein Gleitkomma, keine ungeordnete Menge (nur `std::array` mit festen
Indizes), kein zweiter Strom, keine Zeit, keine Speicheradresse im Ergebnis. Die
Umbrueche laufen auf `std::uint64_t`, wo der Standard sie festlegt; die
`static_cast<u64>` aus `i64` sind seit C++20 wertdefiniert, und `cxx_std_20` steht in
`kern/CMakeLists.txt:67`. Die Rotationsweite ist Vorlagenwert mit `static_assert 0<K<64`,
also gibt es die undefinierte 64er-Verschiebung nicht. `zufall_probe.cpp:171-175` haelt
ausserdem Uebersetzungszeit gegen Laufzeit -- die Vorbedingung dafuer, dass ein geladener
Speicherstand dieselben Zahlen ergibt wie die gespielte Partie.

**Rueckkopplungen.** Das Modul hat keine; es ist eine reine Funktion von sechs Zahlen. Die
einzige Groesse, die davonlaufen koennte, ist die Verzerrung der Restrechnung in
`in_bereich`. Sie ist begrenzt und in T35 mit `2^-32` bei `grenze ≤ 2^32` beziffert; die
Alternative (Verwerfung) haette die *Zahl* der Ziehungen zustandsabhaengig gemacht und
damit genau das gebrochen, wogegen das Paket gebaut ist. Die Entscheidung folgt der
Vorgabe.

**Zustandsausgabe.** `Strom::worte()` gibt alle vier Worte heraus, und der oeffentliche
Konstruktor nimmt sie wieder an -- ein Strom ist also mitten in einer Ziehung
wiederherstellbar, und die Probe vergleicht den ganzen Zustand statt der naechsten Ausgabe.
Aus der Ausgabe allein ist erkennbar, ob richtig gerechnet wurde: neben jeder Zahl steht
ihr veroeffentlichter Erwartungswert.
*Hinweis nach vorn, kein Befund:* Derselbe oeffentliche Konstruktor laesst auch den
Nullzustand zu, in dem xoshiro256\*\* nur noch Nullen ausgibt. Kein Pfad dieses Moduls
erzeugt ihn -- `strom_aus_keim` schliesst ihn aus, und `zufall.cpp:351-363` prueft das am
haerteste Fall Keim 0. Wer spaeter den Speicherstand einliest (T22/T12), muss ihn abweisen.

**Raender.** `in_bereich(strom, 0)` wirft und liefert keinen stillen Ersatzwert -- in der
Ausgabe nachgewiesen. Die Grenze 1 liefert 0. Tausend Ziehungen `mod 4` ergeben
273/240/241/246, also Summe 1000 und alle vier Werte vertreten (eine Restrechnung, die
immer 0 liefert, waere im Bereich und trotzdem falsch). Die T35-Kette kann die Grenze 0
nicht treffen: `n` ist auf `m` gedeckelt, also ist `m − k ≥ 1` fuer `k = 0 … n−1`.
Negative `jahrgang_id`, `runde`, `index` und die `i64`-Raender laufen in der Probe unter
UBSan durch, ohne Meldung.

**T38.** Das Modul enthaelt keine Modusabfrage, und der Satz aus T38 steht in
`zufall.hpp:4-10` ganz oben. So verlangt es das Paket.

## Befund 1 -- der Mustervergleich in Bedingung 1 trifft die Typen dieses Kerns nicht

**An den Projektmanager. Das Paket ist davon nicht betroffen.**

Bedingung 1 belegt „das Modul haelt zwischen zwei Aufrufen nichts fest" mit
`grep -nE 'static |^\s*[A-Za-z_]+ [a-z_]+ ='`. Der zweite Zweig kann eine Ablage mit einem
Typnamen, der eine Ziffer enthaelt, nicht finden: `[A-Za-z_]+` bricht bei `u64` nach dem
`u` ab, das erwartete Leerzeichen folgt nicht.

So erzeugt man die Luecke: Man schreibt `u64 zaehler = 0;` auf Namensraum-Ebene in
`kern/src/zufall.cpp`. Das ist genau die verbotene veraenderliche Ablage. Der erste Zweig
(`static `) trifft nicht, weil kein `static` dasteht -- auf Namensraum-Ebene braucht es
keines. Der zweite Zweig trifft nicht, weil `u64` eine Ziffer enthaelt. Der Vergleich
bliebe leer, die Bedingung gaelte als erfuellt. Dasselbe gilt fuer `i64` und fuer jedes
`std::uint64_t …` (an `::` bricht `[A-Za-z_]+` ebenfalls ab).

Das trifft ausgerechnet die Typen, aus denen dieser Kern besteht. Der Mustervergleich
wandert erfahrungsgemaess in die naechsten Kernpakete; wer ihn uebernimmt, uebernimmt die
Luecke. Ein Vorschlag waere `^[A-Za-z_][A-Za-z0-9_:<>, ]* [a-z_][a-z0-9_]* *=` neben dem
`static `-Zweig, mit `constexpr`/`const` als zugelassener Ausnahme.

Fuer dieses Paket ist die Bedingung trotzdem erfuellt: Ich habe beide Dateien von Hand
durchgesehen (siehe oben), nicht nur den Vergleich laufen lassen.

## Befund 2 -- ein Commit traegt die falsche Paketkennung

**An den Projektmanager. Das Paket ist davon nicht betroffen.**

Commit `770e7b4` hat den Betreff `kernbauer: 0012-zufall-abgeleitete-stroeme (3 Dateien)`,
enthaelt aber ausschliesslich `kern/include/kern/zustand.hpp`, `kern/src/zustand.cpp` und
`kern/test/zustand_probe.cpp` -- also die Arbeit an Paket **0008**. So sichtbar zu machen:
`git show --stat 770e7b4`.

Die Artefakte von 0012 stecken vollstaendig in `ca5c395` (`zufall.hpp`, `zufall.cpp`,
`zufall_probe.cpp`, dazu Logbuch und Statuszeile des Pakets); ich habe gegen diesen Stand
geprueft. Der falsche Betreff kostet nichts am Ergebnis, macht aber die Historie
unbrauchbar fuer die Frage „was gehoerte zu 0012" -- und genau diese Frage stellt sich, wenn
in einem halben Jahr ein Regressionsbruch eingegrenzt werden muss.
