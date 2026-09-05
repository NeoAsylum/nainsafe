---
typ: pruefung
paket: 0151-werte-die-drei-hubgroessen
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle vier Abnahmebedingungen einzeln mechanisch gefahren -- Kopf gegen die T48-Tabelle, beide Bauprofile plus -O2 und -O3 gebaut und gelaufen, die drei Riegel mit Code 0, die Zahlenprobe aus spiel.md von Hand nachgerechnet, neun Mutanten gegen die Proben gestellt (alle neun rot, der unveraenderte Baum gruen).
befunde: 2
---

# Pruefung 0151 -- `hub`, `keilhub`, `preishub_zoll` in `kern::werte`

**Geprueftes Werk.** Commit `e0682a1` ("kernbauer: 0151-werte-die-drei-hubgroessen"),
Elternstand `f4f2f47`. Waehrend des Laufs ist der Zweig auf `fd1f3a7` gewandert
(`e714fa8` daten-pruefer, `fd1f3a7` test-pruefer); die drei Paketdateien sind davon
unberuehrt -- ihre md5 sind zu Laufbeginn und zu Laufende dieselben:

```
fc8a9fcdb16a77b24c57ad0c26534ed7  kern/include/kern/werte.hpp
e8d1aa22308220c4aad6294515ffbd77  kern/src/werte.cpp
6f40b954fcf878f2a8e343f6225d6dba  kern/test/werte_probe.cpp
```

`git diff --stat e0682a1^ e0682a1` nennt genau vier Dateien: die drei des Pakets
(79 / 163 / 422 Zeilen, **null Loeschungen**) und die eine geaenderte Zeile im
Paketdokument selbst (`status: offen` -> `gebaut`). Damit ist der Elternstand die
gueltige Vorherfassung, und der Diff enthaelt kein fremdes Paket.

Gemessen wurde in einem frischen Baum aus
`git archive fd1f3a7 ventures/0016-... specs decisions`, ausgepackt nach
`befunde/bau-pruefung-0151/nachher/`; die Mutantenbaeume liegen daneben unter
`befunde/bau-pruefung-0151/mutanten/`.

---

## Urteil: geprueft

Alle vier Bedingungen sind erfuellt. Was ich wie geprueft habe, einzeln:

### Bedingung 1 -- die drei Deklarationen, in der Form von Nr. 1 bis 17

`werte.hpp` hat **keinen** `namespace intern`; alle Deklarationen stehen unmittelbar in
`kern::werte`. Gezaehlt ueber `grep -n '^\[\[nodiscard\]\]' include/kern/werte.hpp`:
**20** Deklarationen in den Zeilen 157 bis 372, in der Reihenfolge der T48-Tabelle, jede
mit einem Kommentarkopf `**T48 Nr. N**` -- N laeuft luecken- und sprungfrei von 1 bis 20.
Nr. 21 und Nr. 22 fehlen und gehoeren nach dem Paketschnitt zu `0152`.

Die drei Formeln gegen `technik.md` Zeile 2091--2093 und den Formelblock Zeile
2154--2158 gelegt, Zeichen fuer Zeichen:

| # | Kopfzeile in `werte.hpp` | Vorgabe | |
|---|---|---|---|
| 18 | `hub(l, i) = \|lies_neu(land.<l>.instrument.<i>.stand) - lies_alt(land.<l>.instrument.<i>.stand)\|` | Zeile 2154--2155 im Wortlaut | gleich |
| 19 | `keilhub(l, s) = mal_geteilt(welt.preis.<s>, hub(l, zoll), 10.000)` | Zeile 2157 | gleich |
| 20 | `preishub_zoll(l, s) = mal_geteilt(keilhub(l, s), durchgriff(l, s), 10.000)` | Zeile 2158 | gleich |

Die Tabellenzeile 2091 kuerzt den zweiten Summanden zu `lies_alt(dieselbe Adresse)`; der
Kopf schreibt die Adresse aus, wie der Formelblock darunter es tut. Das ist dieselbe
Vorgabe in ihrer ausgeschriebenen Fassung und keine Abweichung.

### Bedingung 2 -- die Formel und nicht eine, die auf den Probewerten dasselbe ergibt

**Von Hand nachgerechnet**, mit der Rundungsregel aus T6 (`festkomma.hpp` Zeile 130: auf
halbe Betraege von null weg), gegen die Tabelle in `spiel.md` Zeile 1489--1505:

```
hub(DE,zoll)        = |430 - 380|                     =     50
keilhub(DE,1)       = 11.000 * 50 / 10.000            =     55      glatt
keilhub(DE,2)       = 10.400 * 50 / 10.000            =     52      glatt
preishub_zoll(DE,1) =  7.288 * 55 / 10.000 = 40,084   =     40
preishub_zoll(DE,2) =  5.464 * 52 / 10.000 = 28,4128  =     28
preishub_zoll(US,1) =  1.000 * 55 / 10.000 =  5,5     =      6      halber Betrag
preishub_zoll(US,2) =  2.000 * 52 / 10.000 = 10,4     =     10
```

Alle sieben Zahlen stimmen mit `werte_probe.cpp` Zeile 1250--1264 ueberein, die ersten
fuenf zusaetzlich mit `spiel.md` Zeile 1497--1498. Die Rundungsprobe (Zeile 1281--1294)
ebenso nachgerechnet: `hub(CN) = 4`; `11.500 * 4 / 10.000 = 4,6 -> 5` (abschneidend
waeren es 4); `3.000 * 5 / 10.000 = 1,5 -> 2`; die zusammengezogene Form rechnet
`11.500 * 4 * 3.000 / 10^8 = 1,38 -> 1`. Zwei Zahlen, und der Quelltext nennt die, die
die Vorgabe vorschreibt.

Die verlangten Trennfaelle sind da: negative Differenz (430 -> 380, Zeile 1108--1120),
`lies_neu == lies_alt` ueber `vortrag` (Zeile 1122--1130) und je ein rundungsabhaengiger
Fall fuer Nr. 19 und Nr. 20 mit dem Sollwert im Kommentar.

**Dass die Proben tragen und nicht mitlaufen, ist gemessen und nicht behauptet.** Neun
Mutanten, jeder eine Aenderung an `src/werte.cpp` in einem eigenen Baum, dazu `m0` als
unveraenderte Kontrolle. Gebaut mit `FABRIK_SANITIZER=ON`, gelaufen als
`ctest -R '^werte_probe$'`:

| | Mutation | `ctest` | wo es bricht |
|---|---|---|---|
| m0 | keine | **gruen** | -- (die Kontrolle) |
| m1 | `hub` gibt die blanke Differenz statt des Betrags | rot | Zeile 1096, 1187 |
| m2 | `keilhub` liest den Weltpreis mit `lies_alt` | rot | Zeile 1251--1253 |
| m3 | `preishub_zoll` rundet nur einmal (zusammengezogene Form) | rot | **allein** Zeile 1293 |
| m4 | `hubklasse` gibt unbekannten Instrumenten Klasse 3 statt abzubrechen | rot | Zeile 1161--1164 |
| m5 | `hub` ohne den `I64_MIN`-Waechter | rot | Zeile 1202--1203 |
| m6 | `pruefe_landessektor` meldet immer unter `keilhub` | rot | Zeile 1368--1373 |
| m7 | `preishub_zoll` nimmt den Durchgriff des anderen Sektors | rot | Zeile 1253--1263 |
| m8 | `hub` liest immer den Zollstand von DE | rot | Abbruch in `lies_neu` |
| m9 | `hub` liest `InstrumentFeld::Druck` statt `Stand` | rot | Abbruch in `lies_neu` |

Neun von neun gedeckt, m0 gruen. **m3 ist der wichtigste Eintrag der Tabelle:** Die
zusammengezogene Fassung ergibt auf **allen** Zahlen der Zahlenprobe (DE und US, beide
Sektoren) dieselben Werte -- 40, 28, 6, 10 -- und faellt einzig ueber die Rundungsprobe.
Ohne Zeile 1293 waere genau die Verwechslung ungedeckt, gegen die Bedingung 2 geschrieben
ist.

**m8 und m9 habe ich nachgelegt**, weil die Zahlenprobe DE und US mit demselben
Zollschritt belegt und einen vertauschten Landesindex in `hub` dort nicht trennen wuerde.
Sie trennt ihn woanders: In der Rundungsprobe ist allein der Zollstand von CN
geschrieben, und `Schreiber::lies_neu` bricht auf einer ungeschriebenen Adresse ab
(`src/schreiber.cpp` Zeile 276--286, T39). Der Mutant stirbt mit

```
kern::schreiber::lies_neu -- in Runde 1 noch nicht geschrieben:
land.DE.instrument.zoll.stand (Nr. 117)
```

Die Deckung ist also da, nur nicht dort, wo man sie zuerst sucht.

### Bedingung 3 -- die Raender brechen ab, unter dem Namen ihrer eigenen Groesse

Fuenf neue Abbruchpfade, jeder nennt Namensraum, Groesse und den Wert, ueber den
geurteilt wurde -- dieselbe Form wie `src/aktion.cpp` Zeile 44--53
(`"kern::aktion -- die Kennung " <zahl> " ist keine Aktionsart; ..."`):

1. `hub`, unbekanntes Instrument -- `kern::werte::hub -- zur Instrumentenkennung <n> ...`
2. `hub`, Restwelt -- `kern::werte::hub -- das Gebiet <g> hat keine Politikinstrumente ...`
3. `hub`, Ueberlaufgrenze -- `kern::werte::hub -- die Differenz <d> hat keinen ... Betrag ...`
4. `keilhub`/`preishub_zoll`, Gebiet -- `<groesse> -- das Gebiet <g> ist kein spielbares Land ...`
5. `keilhub`/`preishub_zoll`, Sektor -- `<groesse> -- der Sektor <s> traegt keinen Weltpreis ...`

Alle vier von der Bedingung namentlich verlangten Faelle sind einzeln belegt
(`werte_probe.cpp` Zeile 1159--1170, 1194--1205, 1346--1374), und m4, m5 und m6 zeigen,
dass die Proben sie halten.

**m5 ist praeziser, als er aussieht.** Ohne den `I64_MIN`-Waechter in `hub` bricht der
Lauf trotzdem ab -- `kern::werte::betrag` faengt denselben Wert eine Ebene tiefer
(`src/werte.cpp` Zeile 97). Still falsch gerechnet wird an keiner Stelle. Was der
Waechter leistet, ist genau das, was die Bedingung verlangt: dass die Meldung **die
Groesse** nennt, in der sie ausloest. Der Mutant faellt an Zeile 1202--1203 und an keiner
Zahlenzeile -- das ist der Beleg dafuer und kein Zufall.

**Zwei Lesarten des Satzes "Jede Abbruchmeldung nennt den Namen der Groesse", beide
hingeschrieben.** Lesart A: die Meldungen der vier aufgezaehlten Raender -- erfuellt.
Lesart B: jede aus den drei Funktionen erreichbare Meldung -- dann verletzten sie
`festkomma::minus` (`"minus: Differenz ausserhalb von i64 (T7)"`) und
`festkomma::mal_geteilt`. Ich folge Lesart A, aus einem Grund im Paket und nicht aus
Milde: Lesart B waere nur erfuellbar, indem der Bauagent `festkomma.hpp` anfasst, und die
Datei steht nicht in seiner `dateien`-Liste. Die Probe schreibt den Unterschied
ausdruecklich hin (Zeile 1207--1220) und prueft, dass die `minus`-Meldung `minus` nennt
und **nicht** `hub` -- zwei Waechter an zwei Stellen, kein Ersatz fuereinander.

### Bedingung 4 -- der Bestand bleibt gruen, die drei Zahlwoerter unberuehrt

Frischer Baum, beide Bauprofile, voll gebaut und gelaufen:

```
cmake -S . -B baus_on  -DFABRIK_SANITIZER=ON    -> rc 0
cmake --build baus_on  -j8                      -> rc 0, keine Warnung
ctest --test-dir baus_on                        -> 18/18 Passed, rc 0
cmake -S . -B baus_off -DFABRIK_SANITIZER=OFF   -> rc 0
cmake --build baus_off -j8                      -> rc 0, keine Warnung
ctest --test-dir baus_off                       -> 18/18 Passed, rc 0
```

Die drei Riegel:

* **Sperrebindungsriegel** -- laeuft beim Konfigurieren, rc 0: *"10 Kernquelle(n) und 12
  Probe(n) geprueft, jede bindet `kern/sperre.hpp` als letzten `#include`."*
* **Belegstellenriegel** (`ctest` Nr. 16) -- Passed.
* **Bezeichnerriegel** (`ctest` Nr. 17) -- Passed.

Beide Riegel habe ich zusaetzlich gegen den **Arbeitsbaum** gefahren, mit meinen
Messordnern unter `befunde/` darin -- Passed, rc 0. `befunde` steht in
`UNGELESENE_ORDNER` des Belegstellenriegels (`belegstellen_riegel.cpp` Zeile 720); die
Messung bestaetigt das, statt sich darauf zu verlassen. Der Warnsatz-Schlussriegel meldet
22 uebersetzende Ziele im Sanitizerprofil und 20 ohne -- der Unterschied sind die beiden
`_geprueft`-Ziele und kein Befund.

**„siebzehn" in `werte.hpp`: 5 Treffer vorher, 5 Treffer nachher** (Zeilen 2, 16, 28, 33
und die Zwischenueberschrift, die von 115 auf 134 gerutscht ist). Unangetastet, wie das
Paket es anordnet.

Am Rande, fuer den Lauf zu `0152` und nicht fuer diesen: Dessen Bedingung 4 spricht von
„allen vier Stellen, an denen heute siebzehn steht" -- es sind **fuenf**. Die mechanische
Haelfte derselben Bedingung („eine Suche nach siebzehn geht leer aus") deckt alle fuenf
ab, die Aufzaehlung daneben nicht.

### Zusaetzlich, ohne dass eine Bedingung es verlangt

* **Determinismus.** Kein Gleitkomma, keine Iteration ueber eine ungeordnete Menge, kein
  zweiter Zufallsstrom, keine Zeit- und keine Speicheradresse in den Paketdateien
  (`grep -niE 'float|double|rand|time\(|clock|chrono|reinterpret_cast|uintptr|unordered'`
  ueber `werte.hpp` und `werte.cpp` findet ausserhalb von Fliesstext nichts). Die
  **ganze** Ausgabe von `werte_probe` aus beiden Bauprofilen zeilenweise
  gegenuebergestellt: identisch bis auf die Laufzeitangabe von `ctest`.
* **Optimierte Uebersetzung.** Der Bestand laeuft ohne Bautyp, also ohne `-O`. Ich habe
  `werte_probe` zusaetzlich als `Release` (`-O3 -DNDEBUG`) und `RelWithDebInfo`
  (`-O2 -g -DNDEBUG`) gebaut und gefahren -- beide rc 0. Der verworfene Aufruf
  `static_cast<void>(hubklasse(instrument))` ueberlebt die Optimierung; sein Abbruchzweig
  ist die Bereichspruefung von `hub` und faellt nicht weg.
* **Ueberlauf.** `mal_geteilt` bildet das Produkt in `i128` und prueft danach gegen `i64`
  (`festkomma.hpp` Zeile 155--164); `I64_MAX^2` liegt bei rund `8,5 * 10^37` und damit
  innerhalb von `i128`. Die Kette `hub -> keilhub -> preishub_zoll` kann an keiner Stelle
  still ueberlaufen. Division durch null gibt es nicht: der Nenner ist an beiden Stellen
  das Literal `10'000`.
* **Rueckkopplung.** Die drei Groessen bilden keine Schleife; `preishub_zoll` ruft
  `keilhub`, `keilhub` ruft `hub`, und dort endet es. Die Schranke, die `spiel.md` Zeile
  1737 fuer `hub(l, zoll)` nennt (`instrument_max[zoll]`), sitzt nach T32 an der
  Zulaessigkeitspruefung des Instruments und nicht hier; dieses Paket erfindet sie
  richtigerweise nicht nach. Und weil die drei Groessen je Runde neu aus dem Zustand
  gerechnet werden und nichts fortschreiben, gibt es keinen Ort, an dem sich eine Rundung
  ueber tausend Runden ansammeln koennte.
* **Der dritte Sektor bricht ab, statt null zu liefern.** `spiel.md` Zeile 1340--1342
  sagt, er trage „in der Zollzeile null", und es sei gleich, ob man ueber zwei oder drei
  Sektoren summiere. Die gebaute Fassung bricht bei `Sektor::Dienstleistungen` ab. Das
  ist **kein** Widerspruch: dieselbe Stelle sagt zwei Zeilen weiter *„`welt.preis.<s>`
  gibt es ohnehin nur fuer s in {1, 2}"*, die Schadenstabelle Zeile 1335 summiert
  ausdruecklich ueber `s in {1, 2}`, und `zustand::stelle_weltpreis` bricht von sich aus
  ab. Der laute Abbruch ist die schaerfere und damit richtige Wahl -- und Bedingung 3
  verlangt ihn.
* **`Konstanten` hat ein Feld dazubekommen, und niemand ausserhalb faellt darueber.**
  `K_GRUND` (`werte_probe.cpp` Zeile 249) und `PROBE_KONSTANTEN` (`werte.cpp` Zeile 187)
  sind nicht mitgezogen worden und bekommen `durchgriff` mit Nullen. Das uebersetzt
  warnungsfrei trotz `-Wextra -Werror`, weil jedes Feld der Struktur einen
  Vorbelegungswert traegt, und es ist folgenlos, weil `preishub_zoll` die einzige Groesse
  ist, die das Feld liest, und sie noch keinen Aufrufer hat. Beides gemessen und nicht
  geschlossen: der Bau ist gruen, und `grep -rn Konstanten` ueber `kern/` und
  `pruefstand/` findet keine dritte Aufbaustelle ausser `tragfaehige_konstanten()` in
  `zustandsausgabe_probe.cpp`, die feldweise zuweist.

---

## Befund 1 -- `durchgriff` ist keine Zustandsadresse; das Paket sagt es falsch, der Bau hat es richtig

**Kein Mangel am Werk, sondern am Auftrag.** Punkt 3 unter *"Vier Dinge, an denen es
scheitern kann"* sagt:

> **`durchgriff(l, s)` und `welt.preis.<s>` sind Zustandsadressen und keine Parameter.**
> Nachsehen, unter welchem Namen sie in `zustand.hpp` stehen, statt sie zu erfinden.

Fuer `welt.preis.<s>` stimmt das (`zustand::stelle_weltpreis`). Fuer `durchgriff` ist es
falsch, an drei Stellen belegbar:

* `technik.md` Zeile 2210, in der Restetabelle von T48 selbst: *"`durchgriff(l, s)` |
  Jahrgangskonstante, T23 Punkt 5, zehn Werte"*.
* `technik.md` Zeile 1500, T23 Punkt 5: `durchgriff[Gebiet][handelbarer Sektor]` als Teil
  der vierzehn Konstanten des Jahrgangs.
* `spiel.md` Zeile 2625: *"Es bleibt eine Jahrgangskonstante nach T23 Punkt 5 und wird
  **keine Adresse**."*

Der Bauagent ist der Vorgabe gefolgt und hat ein Feld in `Konstanten` angelegt. Das ist
richtig; wer dem Paket woertlich gefolgt waere, haette eine Adresse erfunden -- genau die
Fehlerart, gegen die T48 gebaut wurde. **Das geht an den Projektmanager und nicht an den
Bauagenten**, und es senkt kein Kriterium: Die vier Abnahmebedingungen schweigen zu
dieser Frage, sie steht in der Begruendung darueber.

Nachgemessen, dass der Bau die richtige Form hat: `array<array<i64, SEKTOREN_HANDELBAR>,
GEBIETE>` sind `2 * 5 = 10` Werte, wie T23 Punkt 5 sie zaehlt -- alle fuenf Gebiete und
nicht nur die vier Laender, so wie `technik.md` Zeile 2114--2117 es begruendet.

## Befund 2 -- `werte.hpp` Zeile 65 sagt "die eine Jahrgangskonstante"; es sind jetzt zwei

**Der Kopf der Struktur `Konstanten` widerspricht seit diesem Paket dem Kommentar
fuenfzig Zeilen darunter, in derselben Datei.**

```
Zeile  65:  /// Die Kalibrierwerte und die eine Jahrgangskonstante, die in den Formeln
Zeile  66:  /// aus T47 und T48 neben den Zustandsadressen vorkommen.
...
Zeile 116:      /// **Die zweite Jahrgangskonstante dieses Traegers**, aus demselben Grund
```

**Wie man den Fehler erzeugt:** `grep -n "Jahrgangskonstante"
kern/include/kern/werte.hpp` -- Zeile 65 sagt "die eine", Zeile 116 sagt "die zweite".
Zwei Felder tragen die Eigenschaft (`leitzins_start`, `durchgriff`), der Kopf zaehlt eins.

Der Satz war richtig, als `0002` ihn schrieb (`aufgaben/0002-fondsbewertung-definieren.md`
Zeile 223, Status `fertig`); dieses Paket hat ihn ueberholt. **Er ist kein `zurueck`** --
keine der vier Abnahmebedingungen nennt ihn, und er aendert keine Zahl. Er faellt aber
auch nicht mit `0152` weg: Das Folgepaket zieht die Zahlwoerter "siebzehn" nach und legt
`regulierung_last` an, und das ist nach `technik.md` Zeile 3243 ein **Parameterschluessel
nach T27**, keine Jahrgangskonstante. Nach `0152` steht der Satz unveraendert falsch da.
Deshalb der Vorschlag `0155` und nicht eine Zeile im Logbuch.

Der Schaden ist klein und benennbar: Wer den Kopf liest, sucht **eine**
Jahrgangskonstante und hoert auf. Das ist die Richtung, in der ein Irrtum weniger
Pruefung erzeugt statt mehr.

**Was ich am selben Block geprueft und nicht beanstandet habe.** Zeile 79 (*"Alle Felder
sind mit null vorbelegt"*) gilt weiter -- `durchgriff{}` ist eine Reihe aus Nullen. Zeile
75 (*"Jedes Feld traegt seinen Schluesselnamen und seine Skalenklasse"*) ist nicht
verletzt: `durchgriff` traegt keinen `Schluessel`-Vorsatz, weil es keiner ist, und folgt
darin `leitzins_start`, das schon vorher so dastand. `grep -rn "Jahrgangskonstante"` ueber
`include/ src/ test/` findet genau eine ueberholte Stelle, Zeile 65 -- der Vorschlag ist
damit ein Einzeiler und kein Umbau.

---

## Wonach ich gesucht und nichts gefunden habe

* **Eine Rechnung, die die Formel nur auf den Probewerten trifft.** Neun Mutanten,
  darunter die drei naheliegendsten Verwechslungen (Betrag statt Differenz,
  `lies_neu` statt `lies_alt`, eine statt zwei Rundungen) und die drei Indexfehler (Land,
  Sektor, Instrumentenfeld). Keiner ueberlebt.
* **Eine Klasse, die am Namen statt am Instrument haengt.** `hubklasse` ist eine
  Fallunterscheidung ueber die Aufzaehlung mit vier `static_assert` daneben, nicht eine
  Rechnung auf der Instrumentennummer.
* **Ein stiller Rueckgriff auf die Vorrunde.** `Schreiber::lies_neu` bricht auf einer
  ungeschriebenen Adresse ab; m8 und m9 fahren genau diesen Pfad.
* **Ein Ueberlauf, eine Division durch null, eine Rundung, die sich aufsummiert.** Siehe
  oben; die drei Groessen tragen nichts fort.
* **Eine Zahl in `technik.md` oder `spiel.md`, die der Bau nicht trifft.** Sieben Werte
  von Hand nachgerechnet, alle sieben gleich.
* **Ein Riegel, den die Aenderung umgeht.** Alle drei gefahren, dazu der
  Warnsatz-Schlussriegel und der Nullabhaengigkeitsriegel beim Konfigurieren.

## Was ausserhalb dieses Pakets liegt und keinen Vorschlag bekommt

`spiel.md` Zeile 1471--1479 stellt eine Bedingung an die Kalibrierung: Ist der kleinste
Zollschritt zu klein, rundet `preishub_zoll` fuer ein Land-mal-Sektor-Paar auf null, und
*"die Gegenkraft ist dort **stumm, ohne es zu sagen**"*. Das ist die einzige Stelle in der
Umgebung dieses Pakets, an der ein Fehler still bliebe. Der Entwurf weist sie
ausdruecklich **dem Jahrgangsbau** zu, nicht `kern::werte`; ein Paket dafuer gibt es noch
nicht (`grep -rn preishub_zoll aufgaben/` findet allein `0151`). Ich schreibe keinen
Vorschlag, weil der Traeger noch nicht gebaut ist und ein Vorschlag ohne belegten Schaden
den Projektmanager einen Lauf kostet. Er gehoert notiert, wenn der Jahrgangsbau ansteht.
