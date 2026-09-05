---
typ: pruefung
paket: 0101-zustandhpp-kein-platz-nennt-schreibe
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle vier Bedingungen der Abnahme einzeln und mechanisch -- der Mustervergleich auf `schreibe` ueber den Kopf, die drei Indexriegel als ausgefuehrte Abbrueche mit Positivkontrolle in einer eigenen Messprobe, und die volle Testbatterie in beiden Bauprofilen aus einem frischen Export.
befunde: 0
---

# `KEIN_PLATZ` nennt keinen toten Namen mehr -- vier Bedingungen, vier Messungen

**Bezugsstand:** `HEAD` = `2f5211e`, frischer Export ueber `git archive HEAD ventures/0016-...
specs decisions` nach `$TMPDIR`, ausserhalb des Arbeitsbaums. Der Arbeitsbaum wurde
nicht gemessen: Er traegt uncommittete Zwischenstaende paralleler Laeufe und
liegengebliebene Pruefbaeume unter `bau/`.

**Wo die Aenderung liegt:** Der Diff auf `kern/include/kern/zustand.hpp` steht im Commit
`c30acc5`, dessen Betreff ein anderes Paket nennt. Das ist der Gegenstand von
`0121-commit-schnitt-folgt-nicht-dem-paket` und kein Befund gegen dieses Paket -- ich
nenne es nur, damit der naechste Leser die Aenderung findet. Gesucht wurde sie nicht
ueber den Betreff, sondern mit `git log -S` auf den neuen Wortlaut.

Der Diff ist eine reine Kommentaraenderung: ein Wort ersetzt, acht Zeilen eingefuegt,
keine Zeile Code. Regressionsfreiheit an den Rechenarten ist damit strukturell gegeben
und nicht nur gemessen -- gemessen ist sie trotzdem, Bedingung 4.

## Bedingung 1 -- der Kommentar nennt keinen Namen, den es nicht gibt

Der Kommentar an `KEIN_PLATZ` nennt heute `lies`, `lege_ab` und `index_zu_adresse`.
Alle drei loesen auf:

| Name | wo | traegt ihn `Zustand`? |
|---|---|---|
| `lies` | oeffentlich an der Klasse `Zustand` in `zustand.hpp` | ja |
| `lege_ab` | privat an der Klasse `Zustand` in `zustand.hpp` | ja |
| `index_zu_adresse` | am Namensraum, angekuendigt in `zustand.hpp`, ausgeschrieben in `zustand.cpp` | nein, freie Funktion |

**Die strenge Lesart der Abnahme habe ich geprueft und verworfen, und das gehoert
hierher:** Woertlich verlangt sie einen Kommentar, der *keinen* Namen nennt, den
`Zustand` nicht traegt -- und `index_zu_adresse` ist so einer. Dieselbe Abnahme nennt
aber im mechanischen Teil genau diese Funktion als eine der drei, die stehenbleiben
sollen, und verortet sie in `zustand.cpp`, also ausserhalb der Klasse. Die beiden Teile
widersprechen sich; die zulaessige Lesart ist die des mechanischen Teils: gemeint ist
ein Name, den es **nicht gibt**, nicht ein Name ausserhalb der Klasse. Das ist kein
`zurueck`, und ein Vorschlag daraus waere es auch nicht -- der eingefuegte Absatz sagt
von sich aus, dass nur zwei der drei Namen an der Klasse stehen, und raeumt die
Zweideutigkeit damit ab.

## Bedingung 2 -- der Mustervergleich

`grep -n schreibe kern/include/kern/zustand.hpp` trifft zwoelf Zeilen. Keine behauptet
eine Zustandsfunktion dieses Namens; jede faellt in eine der drei vom Paket selbst
genannten Gruppen:

* **Namensraum `kern::schreiber`** -- die Ankuendigung des Rundenschreibers, die
  `friend`-Zeile, der Weg `schreiber::Schreiber::setze` und die Herleitung ueber
  `Schreiber::setze`. Sieben Zeilen.
* **Die Umbenennungsbegruendung** am rohen Schreibzugriff -- "Er heisst nicht mehr
  `schreibe`" und der Satz, der sie fortsetzt. Zwei Zeilen. Vom Paket ausdruecklich
  ausgenommen.
* **Das deutsche Verb** -- "duerfte dann der eine schreiben" an der Kopierregel des
  Startwertzugangs und "dann schreibe ich eben trotzdem" an der Frage
  `vor_der_ersten_runde`. Zwei Zeilen, beide ohne Rueckwaerts-Anfuehrung, beide keine
  Zusicherung.

Zusaetzlich, weil der Nachbarabsatz sich darauf beruft und eine Behauptung in einem
Kommentar ein Pruefauftrag ist: `.schreibe(` und `feld[` haben ueber `kern/`,
`pruefstand/` und `werkzeuge/` **je null Treffer**. Der einzige Treffer auf
`Z::schreibe` im ganzen Baum steht in `zustand_probe.cpp` und ist der
Uebersetzungszeitriegel, der die Abwesenheit des Namens behauptet -- mit
Positivkontrolle ueber `hat_lesezugriff`, damit die drei Negativzusagen nicht bloss
belegen, dass `requires` immer `false` liefert.

## Bedingung 3 -- die drei Riegel, ausgefuehrt statt gelesen

Quelltext zu lesen belegt, dass die Schranke dasteht, nicht dass sie faellt. Ich habe
deshalb eine eigene Messprobe in den Pruefbaum gelegt (`kern/test/kp0101_probe.cpp`,
vom CMake-Glob von selbst ein ctest-Eintrag) und alle drei Abbrueche gefahren. Der
**Meldungstext** entscheidet, welcher der drei Riegel gefallen ist -- ein blosses "es
hat geworfen" traegt hier nicht, weil `Startbelegung` eigene Abbrueche kennt.

`lege_ab` ist privat und ueber den Schreiber nicht erreichbar: `Schreiber::setze`
prueft die Adresse selbst und bricht vorher ab. Erreichbar ist der Riegel ueber
`Startbelegung::setze` -- dieser Weg verzichtet ausdruecklich auf eine eigene Pruefung
("Die Indexpruefung macht der rohe Schreibzugriff") und legt den Wert direkt ueber
`lege_ab` ab.

```
FELDER = 310, KEIN_PLATZ = 310 (hoechster gueltiger Platz 309)
ok     lies(KEIN_PLATZ) -> kern::zustand::lies -- Index ausserhalb der 310 Felder
ok     Startbelegung::setze(KEIN_PLATZ) -> lege_ab -> kern::zustand::lege_ab -- Index ausserhalb der 310 Felder
ok     index_zu_adresse(KEIN_PLATZ) -> kern::zustand::index_zu_adresse -- Index ausserhalb der 310 Felder
ok     lies(0) und lies(FELDER - 1) laeuft durch
ok     Startbelegung::setze(0) und setze(FELDER - 1) laeuft durch
ok     index_zu_adresse(0) und index_zu_adresse(FELDER - 1) laeuft durch
kp0101_probe: alles gruen
```

Die drei letzten Zeilen sind der Positivnachweis: Ein Riegel, der **alles** blockiert,
saehe im Negativtest genauso aus. Die Probe lief gegen `kern_geprueft`, also unter
Adress- und Verhaltenspruefer -- ein Zugriff neben das Feld waere zusaetzlich dort
aufgeschlagen.

**Der Randfall, den die Abnahme nicht nennt, und warum er keiner ist:** `Index` ist
`std::size_t`, also vorzeichenlos. `index >= FELDER` deckt damit den ganzen ungueltigen
Bereich ab; ein "negativer" Index waere eine sehr grosse Zahl und faellt in dieselbe
Bedingung. Bei einem vorzeichenbehafteten Index waere die Zusage des Kommentars nur
halb wahr.

**Und die Reihenfolge stimmt auch dort, wo sie zaehlt:** In `Schreiber::setze` steht
die Adressschranke vor dem Bitfeld und vor jedem Feldzugriff. Ein Index gleich
`KEIN_PLATZ` erreicht das Bitfeld der geschriebenen Adressen nicht.

## Bedingung 4 -- `ctest` bleibt gruen

Frischer Export, beide Profile, volle Batterie -- nicht nur die Proben, die das Paket
beruehrt:

| Profil | Ergebnis |
|---|---|
| `Debug` | 14 von 14 bestanden, 0 gescheitert |
| `Release` | 14 von 14 bestanden, 0 gescheitert |

Bei Determinismus ist der Profilvergleich selbst ein Nachweis: Beide Profile liefern
dieselben 14 Urteile.

## Wonach ich ausserdem gesucht habe -- und was ich nicht gefunden habe

Eine reparierte Wurzel hat Geschwister, und die Frage ist nicht "steht irgendwo noch
`schreibe`", sondern **"nennt irgendein Kommentar des Kerns einen Bezeichner, den es
nicht gibt?"**. Mechanisch gemessen ueber alle Koepfe, Quellen und Proben des Kerns:
5.343 Kommentarzeilen, jeder in Rueckwaerts-Anfuehrung genannte Bezeichner gegen die
Menge aller im Code vorkommenden Bezeichner, gegen die Schluessel aus `parameter.toml`,
gegen die Dateinamen des Vorhabens und gegen die CMake-Ziele gehalten.

**19 nicht aufloesbare Kandidaten, alle falsch positiv** und einzeln nachgesehen:
Kennungen aus den Vorgaben (`M15` bis `N11`), eine Namensvorsilbe (`MAL_`), Schluessel
der Instrumententabellen aus `parameter.toml` (`instrument_min`, `instrument_max`), ein
fremder Testvektorname (`fnv1a_64_test_vector`), ein CMake-Ziel (`kern_geprueft`) und
die verbotenen oder fremden Woerter, die die Koepfe ausdruecklich als verboten fuehren
(`double`, `float`, `sqrt`, `pow`, `log`, `abort`, `consteval`, `unsafe`, `grep`).
**Kein einziger toter Bezeichner.** Nach diesem Paket ist der Kern in dieser Hinsicht
sauber.

**Die Messung hat aber eine Blindstelle, und sie ist der interessante Teil: Sie haette
genau den Fehler nicht gefunden, den dieses Paket behebt.** Der alte Kommentar nannte
`schreibe`, und `schreibe` steht im Kern in einer Codezeile -- in `zustand_probe.cpp`,
in dem `requires`-Ausdruck, dessen ganzer Zweck die Zusage ist, dass es den Namen
**nicht** gibt. Eine Pruefung ueber Mengenzugehoerigkeit haelt eine negative Zusicherung
fuer eine Deklaration. Daraus ist ein Vorschlag geworden:
`0129-bezeichner-im-kommentar-loest-auf`.

## Was kein Befund ist, obwohl ich hingesehen habe

* **Der Satz "die Probe ist der Mustervergleich ueber `kern/`".** Er beschreibt einen
  Handgriff, waehrend es fuer den einen Namen `schreibe` laengst einen
  Uebersetzungszeitriegel gibt -- der Satz sagt also weniger, als der Baum kann. Falsch
  ist er nicht, und `specs/` schreibt zur Formulierung nichts vor.
* **Die Laenge des eingefuegten Absatzes.** Aufbau und Stil sind kein Befund, solange
  sie keine Vorgabe verletzen.
* **Dass `lege_ab` seinen Riegel doppelt fuehrt**, wo `Schreiber::setze` schon prueft.
  Ueber `Startbelegung` ist er der einzige, und der Kommentar an beiden Stellen sagt,
  wofuer er da ist.
