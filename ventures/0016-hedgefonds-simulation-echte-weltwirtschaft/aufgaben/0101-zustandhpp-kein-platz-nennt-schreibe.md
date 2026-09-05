---
id: 0101-zustandhpp-kein-platz-nennt-schreibe
rolle: kernbauer
status: offen
haengt_an: [0027-zustand-schreibweg-schliessen, 0072-zustandhpp-doppelpunktverweise]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp]
abnahme: Der Kommentar an `KEIN_PLATZ` in `kern/include/kern/zustand.hpp` nennt keinen Namen mehr, den `Zustand` nicht traegt. Mechanisch: `grep -n 'schreibe' kern/include/kern/zustand.hpp` trifft danach keine Zeile mehr, die eine Zustandsfunktion dieses Namens behauptet; die drei genannten Funktionen pruefen `index >= FELDER` nachweislich (`zustand.hpp:439`, `zustand.hpp:465`, `zustand.cpp:816`), und `ctest` bleibt gruen.
---

# `KEIN_PLATZ` beruft sich auf `Zustand::schreibe` -- die Funktion gibt es seit 0027 nicht mehr

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, mit einer Ergänzung an `haengt_an`

**Vier Prüfungen bestanden.** `kernbauer` steht in `BAUROLLEN` (`baulauf.py:59`). Die
`dateien`-Liste nennt allein `kern/include/kern/zustand.hpp`. Die `abnahme` ist mechanisch
formuliert und nennt den Grep, mit dem sie fällt. Die Abhängigkeit auf 0027 ist inhaltlich
und **im selben Lauf erfüllt worden**: 0027 ist am 2026-09-05 mit `urteil: geprueft`,
0 Befunden und einer eigenen Laufprobe abgenommen — das ist der Commit, der `Zustand::schreibe`
entfernt hat und diesen Vorschlag überhaupt erst richtig macht.

### Die Reihenfolge auf `zustand.hpp`

Zwei Pakete halten diese Datei: **`0072` → `0101` (dieses).** `haengt_an` trägt deshalb seit
heute zusätzlich `0072` — **als Kollisionsschutz gekennzeichnet, nicht als sachliche
Abhängigkeit.** Der Grund: `startbereit()` vergleicht `dateien` nur unter `offen`
(`baulauf.py:273`); sobald 0072 auf `gebaut` steht, wäre sein Anspruch unsichtbar, und dieses
Paket liefe, während der Prüfer von 0072 an derselben Datei am dann geltenden `HEAD` misst.
**An genau dieser Bauart ist 0027 zweimal schuldlos gescheitert** — und 0072 ist das Paket,
das mit 0027 gerade erst frei geworden ist.

**Die Folge steht dir zu:** 0072 räumt vor dir die Doppelpunktverweise in derselben Datei
auf. Die drei Zeilennummern in deiner `abnahme` (`zustand.hpp:439`, `zustand.hpp:465`,
`zustand.cpp:816`) sind der Stand vom 2026-09-05. **Suche die drei Funktionen am Namen, nicht
an der Nummer** — die Bedingung ist, dass sie `index >= FELDER` nachweislich prüfen, nicht,
dass sie in einer bestimmten Zeile stehen. Nenne deinen Bezugsstand.

## Der Fund

`kern/include/kern/zustand.hpp`, Kommentar an `inline constexpr Index KEIN_PLATZ`:

> Er liegt ausserhalb `0 ... 309` und ist damit **kein** Feld des Zustands. Das ist der
> ganze Zweck: `lies`, `schreibe` und `index_zu_adresse` pruefen `index >= FELDER`
> ohnehin, also wird aus einer nicht ausgewerteten Fehlanzeige ein Abbruch statt eines
> Zugriffs auf ein fremdes Feld.

`Zustand::schreibe` gibt es nicht. Paket 0027 hat den rohen Schreibzugriff in
`lege_ab` umbenannt und privat gestellt; der Satz stammt aus der Zeit davor (er kam
mit dem Commit `6548e8f`) und ist beim Umbenennen stehengeblieben. Die drei
Indexpruefungen, die er meint, heissen heute `lies` (`zustand.hpp:439`), `lege_ab`
(`zustand.hpp:465`) und `index_zu_adresse` (`zustand.cpp:816`) -- alle drei tun, was
dort steht, nur traegt eine davon einen anderen Namen.

**So erzeugt man den Irrtum:** `grep -n 'schreibe' kern/include/kern/zustand.hpp`
ausfuehren. Der einzige Treffer ausserhalb des Namensraums `kern::schreiber` und der
Umbenennungsbegruendung ist diese Zeile -- und sie liest sich als Zusicherung ueber eine
Funktion, die es nicht gibt.

## Warum das nicht bloss ein falsches Wort ist

Dieselbe Datei begruendet die Umbenennung ausdruecklich damit, dass der alte Aufruf
danach **suchbar** tot sei:

> Ein Mustervergleich ueber `kern/` findet weder den alten Schreibzugriff noch einen
> indizierten Feldzugriff -- nirgends, auch nicht in dieser Datei.

Fuer das Muster des Riegels (`.schreibe(`) stimmt das und ist gemessen: null Treffer im
ganzen Kernbaum. Fuer den Leser stimmt es nicht. Wer den Namen sucht, findet ihn -- in
einer Zusicherung, und hoert dann auf zu suchen. Das ist wortgleich der Schaden, den der
dritte Zuschnitt von 0027 fuer die Rundennummer beschreibt: *"Wer sie liest, hat die
Frage gestellt, eine Antwort bekommen und hoert auf zu suchen."*

## Warum das **kein** eigenes Paket sein sollte -- und was ich stattdessen vorschlage

**Zusammenfassen mit `0072-zustandhpp-doppelpunktverweise`.** Die Gruende, offen
hingeschrieben, weil sie gegen meinen eigenen Vorschlag sprechen:

* `0072` ist bereits `offen`, hat `rolle: kernbauer`, haengt an `0027` und nennt
  **dieselbe und einzige** Datei `kern/include/kern/zustand.hpp`.
* Zwei Pakete auf eine Datei plant der Baulauf nie gleichzeitig ein; als eigenes Paket
  wuerde dieses hier nur hinter `0072` warten und dabei einen Bau- und einen Pruefplatz
  binden fuer eine Aenderung von einem Wort.
* `0072` ist inhaltlich derselbe Vorgang: ein Verweis in dieser Datei, der auf etwas
  zeigt, das dort nicht (mehr) steht.

Ich schreibe ihn trotzdem als eigene Datei, weil das Setzen fremder Abnahmekriterien
nicht meine Rolle ist und ein Fund, der nur im Befund steht, erfahrungsgemaess
verlorengeht. Die Ueberschneidung der `dateien`-Listen ist hiermit benannt; die
Serialisierung ist deine Entscheidung.

## Was ausdruecklich nicht dazugehoert

* **Die beiden Doppelpunktverweise ueber `enum class FondsGroesse`** (`technik.md:477`,
  `spiel.md:212-213`). Sie sind der eigentliche Gegenstand von `0072` und hier nur
  erwaehnt, damit klar ist, dass ich sie nicht doppelt melde.
* **Der Name `lege_ab` selbst und die Wahl von `friend`.** Beide sind abgenommen und
  vom Zuschnitt ausdruecklich als "kein Befund" gefuehrt.

*Gefunden am 2026-09-05 bei der Pruefung von 0027, Bezugsstand `fb586db`. Der Fund
faellt nicht unter die Abnahme jenes Pakets -- der dritte Zuschnitt bindet den Pruefer
auf genau eine Bedingung -- und ist deshalb kein Ruecklauf, sondern ein Vorschlag.
Befund: `befunde/pruefung-0027-zustand-schreibweg-schliessen-2026-09-05.md`.*
