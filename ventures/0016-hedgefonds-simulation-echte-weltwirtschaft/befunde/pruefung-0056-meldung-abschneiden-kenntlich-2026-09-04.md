---
typ: pruefung
paket: 0056-meldung-abschneiden-kenntlich
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen selbst gebaut und gemessen -- beide Richtungen des Merkers ueber fuenf Mutationen des Kopfes, das Ende der gekuerzten Zahl Zeichen fuer Zeichen, und die Unveraendertheit von schreiber_probe und schritt_probe durch byteweisen Vergleich gegen einen Bau mit dem Kopf vor 0056.
befunde: 0
---

# `kern::meldung` sagt jetzt, wenn sie abgeschnitten hat

## Wo ich hingesehen habe

Gebaut und gelaufen ist alles selbst, ausserhalb des Repos unter `$TMPDIR/kp0056`
(Kopie von `kern/` und `werkzeugkette.cmake`, `bau/` ausgenommen). Zwei Bauprofile:
Vorgabeprofil und `-DCMAKE_BUILD_TYPE=RelWithDebInfo`. `FABRIK_SANITIZER` ist an, die
Proben linken `libkern_geprueft.a`; die Bindezeile weist es nach:

```
c++ -fsanitize=undefined,address -fno-sanitize-recover=all ... -o meldung_probe libkern_geprueft.a
```

Das ist wichtig fuer dieses Paket im Besonderen: Die Marke **ueberschreibt** Plaetze
506 bis 510 eines 512 Byte grossen Feldes. Ein Fehlgriff um einen Platz waere ohne
Adressen-Sanitizer eine gruene Probe.

Der Arbeitsbaum ist an beiden Paketdateien sauber (`git status --short kern/` leer),
gemessen wurde also der abgegebene Stand.

**Der Commit-Betreff luegt wieder, zum zehnten Mal.** Der Kopf
`kern/include/kern/meldung.hpp` steckt nicht in `8fff575` („kernbauer: 0056"), sondern
in `849abc3` („datenbauer: 0065-reihentoml-reihe-9-ohne-sollrolle") -- gefunden ueber
`git log -S 'abgeschnitten_'`. Umgekehrt traegt `8fff575` mit
`werkzeugkette.cmake` (203 Zeilen) die Arbeit von Paket 0066. Beides ist **keine
Grenzverletzung des Bauagenten**, sondern der bekannte Zuschnitt von
`lauf.py:committen`; geprueft habe ich den Inhalt, nicht den Commit.

## Bedingung 1 -- beide Richtungen des Merkers, an den drei Randstellen

Erfuellt.

`meldung_probe` (`kern/test/meldung_probe.cpp`) laeuft und ist gruen; selbst gebaut und
gerufen ueber `cmake -E env $TMPDIR/kp0056/bau/meldung_probe`:

```
  abgeschnitten bei 511 von 1000 angebotenen Zeichen, Ende "2345[...]"
  Zahl am Pufferende abgeschnitten zu "-[...]" (frueher "-92233")
  voller Puffer ohne Verlust: laenge 511, abgeschnitten false
  ein Zeichen zu viel: laenge 511, Ende "yyyy[...]"
meldung_probe: alle Pruefungen bestanden
```

Dass die Zusagen wirklich gemessen sind und nicht nur dastehen, zeigen fuenf Mutationen
des Kopfes. Jede ist eine Kopie des Baumes mit genau einer geaenderten Stelle.

**M1 -- `abgeschnitten_ = true;` aus `text()` entfernt.** Uebersetzung rot:
`meldung_probe.cpp:339: error: static assertion failed: eine gekuerzte Meldung meldet es
und endet auf der Marke`. Mit abgeschalteten Zusicherungen (M1b, damit die Laufzeitseite
sichtbar wird) faellt die Probe an genau den Stellen, die die Bedingung nennt:

```
FEHLGESCHLAGEN Zeile 187: lang.abgeschnitten()      <- Text ueber den Puffer hinaus
FEHLGESCHLAGEN Zeile 215: lang.abgeschnitten()
FEHLGESCHLAGEN Zeile 239: knapp.abgeschnitten()     <- Zahl mitten in den Ziffern
FEHLGESCHLAGEN Zeile 301: voll.abgeschnitten()      <- Anhang an den vollen Puffer
```

Der dritte Randfall wird dabei zweimal geprueft, und nur einmal davon zaehlt: Zeile 215
haengt an `lang`, das **schon** abgeschnitten war. Die tragende Stelle ist Zeile 301 --
dort war der Puffer in Zeile 285 und 294 nachweislich voll und trotzdem verlustfrei,
und erst `voll.text("z")` kippt den Merker. Ohne diese Reihenfolge waere die Bedingung
nicht belegt.

**M3 -- `abgeschnitten()` misst Fuelle statt Verlust** (`return laenge_ >=
MELDUNG_ZEICHEN_MAX;`). Uebersetzt gruen, beide Zusicherungen zur Uebersetzungszeit
halten, alle vier Positivpruefungen oben halten -- und trotzdem faellt die Probe:

```
FEHLGESCHLAGEN Zeile 285: !voll.abgeschnitten()
FEHLGESCHLAGEN Zeile 294: !voll.abgeschnitten()
```

Das ist die Mutation, die zaehlt. Sie beweist, dass die Negativrichtung eigenstaendig
gemessen ist und nicht als Beifang der Positivrichtung. Dieselben zwei Zeilen fallen
auch unter `-O2` (`RelWithDebInfo`) -- die Probe misst den Laufzeitweg und nicht die
Konstantenfaltung.

**M4 -- `MARKE` von `"[...]"` auf `"~~~"` (andere Laenge).** Probe bleibt gruen,
Laufcode 0, das Protokoll traegt die neue Marke:
`Zahl am Pufferende abgeschnitten zu "-~~~"`.

**M5 -- `PUFFER_ZEICHEN` von 512 auf 300.** Probe bleibt gruen, Laufcode 0:
`abgeschnitten bei 299 von 1000 angebotenen Zeichen`, `voller Puffer ohne Verlust:
laenge 299`.

M4 und M5 zusammen belegen den Halbsatz „Keine Grenze wird abgeschrieben" mechanisch:
Die Probe haengt an `MELDUNG_ZEICHEN_MAX`, `MARKE` und `MARKE_ZEICHEN`, nicht an 511
oder an fuenf.

## Bedingung 2 -- der Fall, der das Paket ausgeloest hat

Erfuellt.

`meldung_probe.cpp:229-255`: Der Puffer wird auf `MELDUNG_ZEICHEN_MAX - (MARKE_ZEICHEN +
1)` gefuellt, dann kommt `I64_MIN`. Das erwartete Ende wird gebaut (`'-'` plus `MARKE`)
und mit `gleich()` Zeichen fuer Zeichen verglichen; `PRUEFE(knapp.abgeschnitten())` steht
daneben.

**M2 -- `marke_setzen()` aus `text()` entfernt.** Uebersetzung rot an derselben
Zusicherung wie M1. Mit abgeschalteten Zusicherungen (M2b) faellt genau der
Zeichenvergleich, und das Protokoll zeigt den Fehler, um den es dem Paket ging, im
Wortlaut zurueck:

```
FEHLGESCHLAGEN Zeile 199: gleich(lang.fertig() + (MELDUNG_ZEICHEN_MAX - MARKE_ZEICHEN), MARKE)
FEHLGESCHLAGEN Zeile 216: gleich(lang.fertig() + (MELDUNG_ZEICHEN_MAX - MARKE_ZEICHEN), MARKE)
FEHLGESCHLAGEN Zeile 254: gleich(knapp.fertig() + (...), erwartetes_ende.data())
FEHLGESCHLAGEN Zeile 261: !enthaelt(knapp.fertig(), "-92233")
FEHLGESCHLAGEN Zeile 302: gleich(voll.fertig() + (MELDUNG_ZEICHEN_MAX - MARKE_ZEICHEN), MARKE)

  Zahl am Pufferende abgeschnitten zu "-92233" (frueher "-92233")
```

Die letzte Zeile ist der Nachweis, dass die Gegenprobe kein Strohmann ist: Ohne die
Marke steht dort wirklich `-92233`, eine tadellose Zahl mit vierzehn fehlenden Ziffern.

## Bedingung 3 -- nichts anderes aendert sich

Erfuellt, und zwar isoliert gemessen statt aus dem Baubericht abgeschrieben.

Ich habe einen zweiten Baum angelegt, der sich vom ersten in **genau einer Datei**
unterscheidet: `meldung.hpp` in der Fassung vor 0056
(`git show 849abc3^:.../meldung.hpp`). Beide Baeume gebaut, `schreiber_probe` und
`schritt_probe` gelaufen, Ausgaben byteweise verglichen:

```
diff schreiber-alt.txt schreiber-neu.txt -> 0
diff schritt-alt.txt   schritt-neu.txt   -> 0
cksum: 3000347287 3280  (beide schreiber)
       565531488  1448  (beide schritt)
```

Beide gruen (Laufcode 0), und keine ihrer 23 Abbruchmeldungen traegt die Marke
(`grep '\[\.\.\.\]'` ohne Treffer). Die laengste gemessene Meldung des Kerns hat **327
von 511** Zeichen -- der Riegel des Startwertzugangs aus `zustand.cpp:918`.

Dass keine von ihnen den Rand erreichen **kann**, habe ich zusaetzlich gerechnet statt
nur beobachtet. Alle 15 Meldungsstellen des Kerns (5 in `schreiber.cpp`, 9 in
`schritt.cpp`, 1 in `zustand.cpp`; ausserhalb von `src/` gibt es keine) mit den
schlimmsten Eingaben: je `zahl` 20 Zeichen (`-9223372036854775808`), je `adresse` 63
(43 feste Zeichen der Aussenform plus 20 Ziffern; die laengste Innenform misst
gemessene 57, `land.DE.instrument.regulierung.restverzoegerung (Nr. 128)`).

| Datei | schlimmster Fall | Zeile |
|---|---|---|
| `zustand.cpp` | 403 | 918 |
| `schritt.cpp` | 274 | 516 |
| `schreiber.cpp` | 163 | 302 |

403 von 511. Der Abstand ist Faktor 1,27 -- enger, als das Paket selbst annimmt (es
rechnet mit 316 gegen 511), aber er haelt.

`meldung_probe` steht namentlich als `Passed` im Uebersetzungsbericht des Tages
(`befunde/uebersetzung-2026-09-04.md:75`, `ergebnis: ok`, 12 von 12). Der Bericht ist um
07:19:48 geschrieben worden, die beiden Paketdateien um 07:07:21 und 07:13:50 -- er
deckt also den abgegebenen Stand und nicht einen aelteren. Unabhaengig davon ist in
meinem eigenen Bau `ctest` ueber alle Kernproben gruen.

## Was ich ausserdem geprueft habe und was nichts ergab

- **Zusagen aus „Was zu bauen ist", die in keiner Abnahmebedingung wiederkehren.**
  `abgeschnitten()` ist `constexpr`, `noexcept` und `[[nodiscard]]` wie `laenge()`
  (`meldung.hpp:215`). `PUFFER_ZEICHEN` steht unveraendert auf 512 -- die Marke
  ueberschreibt, statt den Puffer zu verlaengern (Codediff gegen `849abc3^`). Der Kopf
  bindet weiterhin nur `<array>`, `<cstddef>` und `kern/zustand.hpp` ein; `sperre.hpp`
  steht nicht darin. Kein Abbruch beim Abschneiden. `Meldung` ist Literaltyp geblieben --
  das beweisen die beiden `static_assert`, und M1/M2 beweisen, dass sie beissen.
- **Die Raender von Hand.** Abgeschnitten wird bei `laenge_ >= 511`, also ist `laenge_`
  an der Aufrufstelle von `marke_setzen()` immer genau 511, `beginn` immer 506, und
  geschrieben werden 506 bis 510 eines Feldes mit 512 Plaetzen; Platz 511 traegt die Null.
  Kein Unterlauf von `laenge_ - MARKE_ZEICHEN` moeglich, die Zusicherung
  `MARKE_ZEICHEN <= MELDUNG_ZEICHEN_MAX` deckt auch den entarteten Fall. ASan haette das
  Gegenteil gemeldet und tat es nicht.
- **Der zweite Abschneideweg, den `text` nicht sieht.** `zahl` hat ein eigenes
  Ziffernfeld `std::array<char, 24>` mit der Schranke `stellen < ziffern.size()`; liefe
  es voll, gingen Ziffern **ohne** Merker verloren. `|I64_MIN|` hat 19 Stellen, das Feld
  24 -- die Schranke ist unerreichbar, der Kommentar „Kein eigener Merker fuer `zahl`"
  stimmt also. Nachgerechnet, nicht geglaubt; die Probe vergleicht `-9223372036854775808`
  zusaetzlich Zeichen fuer Zeichen.
- **Jede Behauptung in den neuen Kommentaren einmal hergestellt.** „Mehrfach zu rufen ist
  folgenlos": nach dem Abschneiden verlangt der Schreibzweig Platz, den es nicht mehr
  gibt, `laenge_` waechst nicht, die Marke landet immer gleich -- gemessen in
  `meldung_probe.cpp:205-216` mit vier weiteren Anhaengen. „Die Laengenpruefung greift an
  dieser Aufrufstelle nie": stimmt, sie ist tot und als Vorsorge deklariert.
- **Fehlalarm hergestellt, wer eine Pruefung feiner macht.** Eine **nicht** abgeschnittene
  Meldung, die zufaellig auf die Marke endete, saehe fuer den Menschen abgeschnitten aus.
  `grep '\[\.\.\.\]'` ueber den ganzen Kern trifft nur `meldung.hpp` selbst -- keine
  Meldungsprosa endet so. Die Probe deckt die Gegenrichtung in Zeile 286 ab
  (`!gleich(voll.fertig() + ..., MARKE)`).
- **Teilzeichen durch das Ueberschreiben.** Die Marke ist ASCII und ueberschreibt Bytes;
  bei UTF-8-Prosa koennte sie mitten in einem Zeichen ansetzen. `grep -rlP '[^\x00-\x7F]'`
  ueber `kern/src` und `kern/include`: `schreiber.cpp`, `schritt.cpp`, `zustand.cpp` und
  `meldung.hpp` sind rein ASCII. Der Fall existiert nicht.
- **Ruft die Probe den echten Vorgang?** Ja. Kein Testhelfer, keine nachgestellte Klasse
  -- jede Zahl im Protokoll (511, 299, `-[...]`) kommt aus `kern::meldung::Meldung`
  selbst. Deshalb wandern 511 und 299 auch mit, wenn man den Puffer aendert (M5).
- **Beide Bauprofile.** Vorgabeprofil und `RelWithDebInfo` (`-O2 -g -DNDEBUG`): keine
  neue Warnung trotz `-Werror -Wconversion -Wsign-conversion -Wuseless-cast`, und die
  Ausgabe von `schreiber_probe` ist zwischen beiden Profilen byteidentisch.

## Kein Vorschlag

Zwei Sachen habe ich erwogen und verworfen, damit der naechste Lauf sie nicht noch
einmal erwaegt:

**`abgeschnitten()` hat im Kern keinen Aufrufer.** Sonst waere das mein Standardbefund --
ein Werkzeug ohne Aufrufer ist eine Vorgabe ohne Durchsetzung. Hier nicht: Die
Durchsetzung ist die Marke, und die setzt sich selbst, ohne dass jemand fragt. Genau
deshalb ist sie im Paket als **zweite** Anzeige verlangt und nicht als Alternative.

**Ein Riegel, der die 403 von 511 ueberwacht.** Die Rechnung oben ist heute von Hand
gemacht und nichts haelt sie fest, waehrend die sechs Schrittpakete ihre Prosa an
dieselbe Klasse haengen. Das waere ein Paket -- aber es waere das dritte Netz unter
einem Fehler, dessen Folge eine **sichtbar** gekuerzte Diagnose ist, nicht eine falsche
Zahl. 0056 hat den unsichtbaren Fall beseitigt; den sichtbaren noch einmal abzusichern,
ist „waere auch gut" und kostet den Projektmanager einen Lauf.

## Pruefstuecke

Unter `befunde/pruefung-0056-pruefstuecke/` liegen das Messprogramm fuer die
Adressbreite und die Liste der fuenf Mutationen als Textersetzungen, damit der naechste
Lauf sie nachbauen kann, ohne sie neu zu erfinden.
