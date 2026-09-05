---
typ: pruefung
paket: 0088-werte-probe-vier-unbelegte-vorgaben
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Der zweiseitige Nachweis je Vorgabe selbst gefahren -- am unveraenderten `werte.cpp` laeuft `werte_probe` gruen, mit jeder der vier angegebenen Mutationen wird sie rot, und zwar jedes Mal in genau der neuen Pruefung, die dieser Vorgabe zugeordnet ist.
befunde: 0
---

# Die vier Riegel halten, und sie halten einzeln

## Was geprueft wurde und wie

Aufbau: `git archive HEAD ventures/0016-... | tar -x -C $TMPDIR` als Arbeitskopie, dort
`cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS="-fwrapv -fno-fast-math"
-DFABRIK_SANITIZER=ON`. Jede Mutation ist eine Textersetzung mit Trefferbremse
(`assert text.count(alt) == 1`) auf einer **Kopie** von `kern/src/werte.cpp` in `$TMPDIR`;
das Repo selbst wurde nicht angefasst. Bezugsstand ist `ceebee3` -- `git log` auf
`kern/src/werte.cpp` nennt seither keinen weiteren Commit, die Zeilennummern des Pakets
gelten also unveraendert.

Die Arbeit des Pakets liegt in `ce59b8b`, dessen Betreff `architekt: 0051-...` lautet.
Gefunden ueber `git log` auf die Datei, nicht ueber den Betreff. Umfang dort:
**236 Zeilen dazu, 0 entfernt** (`git show --numstat`). Es wurde also keine Zusicherung
gestrichen, keine Schwelle bewegt und keine Pruefung uebersprungen.

## Die vier Vorgaben gegen `specs/`

Vor der Messung nachgeschlagen, ob jede Pruefung die **verbindliche** Form festhaelt und
nicht eine ausgedachte:

| Nr. | Vorgabe | Fundstelle in `specs/0016-.../technik.md` |
|---|---|---|
| 1 | `tsd_in_cent` am **aeussersten** Aufruf von `positionswert` und `beteiligung_wert` | Zeile 424 (T50, Uebergang 1) |
| 2 | `positionswert(p) = tsd_in_cent(stufen(p) · stufenwert(p))` -- **mit** Vorzeichen | Zeile 2054 (T48 Nr. 15), gegen Zeile 2053 (Nr. 14 mit `\|stufen\|`) |
| 3 | `marktkorb(m, k)` = Σ 12 `korbwert` + Σ 4 `anleihewert`, sonst nichts | Zeile 2046 (T48 Nr. 7) und Zeile 1849--1851 (T33 Punkt 1: „Waehrungen tragen keine Marktkapitalisierung und gehen nicht ein") |
| 4 | `waehrungswert(l) = wert(handelsvolumen(l), 10.000, l)` -- festes Literal | Zeile 2043 (T48 Nr. 4) |

Alle vier stimmen. Die Zuordnung Pruefung → Vorgabe ist keine Behauptung des Pakets,
sondern nachgeschlagen.

## Die gruene Seite

Unveraendertes `kern/src/werte.cpp`, voller Bau, `ctest`:

```
13/13 Test #13: vorrat_verfahren_probe ...........   Passed
100% tests passed, 0 tests failed out of 13
```

`werte_probe` gruen. (`belegstellen_riegel` ist aus dem Lauf genommen: Er verlangt
`specs/` als zweites Argument und meldet in einer Kopie ohne Repowurzel
`'...specs/0016-...' ist kein Verzeichnis` -- ein Umgebungsbefund der Kopie, kein
Zustand des Baums, und er uebersetzt `werte.cpp` nicht.)

## Die rote Seite, Vorgabe fuer Vorgabe

Je Mutation einzeln gebaut und gefahren. „Zeilen" sind die Zusicherungen, die gerissen
sind; in Klammern die neue Pruefung, in der sie stehen.

| Mutation | Urteil | gerissene Zusicherungen |
|---|---|---|
| **M0** Kontrolle ohne Eingriff | **gruen** | — |
| **M1** in `beteiligung_wert_aus`: `mal_geteilt(tsd_in_cent(korb), anteil, 10'000)`, kein `tsd_in_cent` mehr aussen | **rot** | 693, 698, 708, 716 (alle in `probe_skalengrenze_am_aeussersten_aufruf`) |
| **M2** in `positionswert_aus`: `mal(betrag(stufen), je_stufe)` | **rot** | 756, 759, 772, 773 (alle in `probe_positionswert_traegt_das_vorzeichen`) |
| **M3** in `marktkorb`: `waehrungswert` je Land dazuaddiert | **rot** | 820, 823 (beide in `probe_marktkorb_ohne_waehrungen`) |
| **M4** in `waehrungswert`: Wechselkurs statt des Literals 10.000 als Kurs | **rot** | 860, 861, 866, 867 (alle in `probe_waehrungswert_fester_kurs`) |

Keine Mutation reisst eine Zusicherung ausserhalb ihrer eigenen neuen Pruefung. Die
Zuordnung „eine Pruefung je Vorgabe" ist damit gemessen und nicht bloss behauptet.

**Die vier ausgeschriebenen Gegenzahlen stimmen auf die Einheit.** Das ist der Teil, der
sonst gern ungeprueft bleibt: Bei M1 riss `!= 99'990`, bei M2 `!= 10'000'000'000`, bei M3
`!= 3'800'700`, bei M4 zweimal `!= 600'000`. Eine `!=`-Zusicherung reisst nur, wenn die
Gleichheit eintritt -- der Mutant liefert also **genau** die Zahl, die im Kommentar als
verworfene Form steht. Die Handrechnungen des Pakets sind damit nachgerechnet.

## Der Gegenbeweis: waren die vier vorher wirklich unbelegt?

Die staerkste Frage an ein Testpaket ist nicht „wird es rot", sondern „wurde es vorher
gruen". Dazu den **Probenstand vor 0088** eingelegt (`git show ceebee3:...
kern/test/werte_probe.cpp`, 668 Zeilen gegen 904 heute) und alle vier Mutationen darauf
gefahren, jedes Mal die volle Kette:

| Mutation | Probenstand vor 0088 |
|---|---|
| M1 | `100% tests passed, 0 tests failed out of 13` |
| M2 | `100% tests passed, 0 tests failed out of 13` |
| M3 | `100% tests passed, 0 tests failed out of 13` |
| M4 | `100% tests passed, 0 tests failed out of 13` |

Alle vier Verletzungen liefen vorher durch **alle dreizehn** Proben -- nicht nur durch
`werte_probe`. Die Ausbeute des Pakets ist damit von der Seite belegt, von der sie
zaehlt: Die vier neuen Pruefungen sind das Einzige im Baum, das diese vier Vorgaben
haelt.

## Welche Zusicherung hat kein Mutant rot bekommen?

Die Frage, ohne die eine Empfindlichkeitsmessung unvollstaendig ist. Drei zusaetzliche
Mutanten, allein zu diesem Zweck:

- **M1b** -- die dritte denkbare Fehlstelle aus Vorgabe 1: Umrechnung **zwischen**
  Korbanteil und Abschlag (`tsd_in_cent` um das innere `mal_geteilt`). Rot: 708 und 712.
  Damit ist auch `!= 66'670` scharf, das M1 nicht erreicht -- die Pruefung deckt beide
  falschen Orte, nicht nur den im Paket genannten.
- **M6** -- `wert` teilt durch den doppelten Wechselkurs, also jede Bewertung halbiert.
  Rot: 688, 751, 752, 756, 765, 772, 812, 813, 814, 815, 820, 860, 861, 866, 873.
- **M7** -- `handelsvolumen` zaehlt acht zu viel. Rot: 814, 815, 816, 817, 854, 855, 860,
  861, 872, 873.

Zusammen mit M1--M4 ist damit **jede** Zusicherung der vier neuen Pruefungen mindestens
einmal rot gewesen, die Positivkontrollen eingeschlossen. Uebrig bleiben genau drei
Zeilen, die kein Mutant reissen konnte: 697, 711 und 715. Sie sind der Bauart nach
unerreichbar -- `mal_geteilt(300'000, 3'333, 10'000) == 99'990` und die beiden anderen
rechnen auf Literalen und haengen an `festkomma`, nicht an `werte.cpp`. **Das ist kein
Befund, sondern der Sinn dieser drei Zeilen:** Aenderte sich die Rundung in
`mal_geteilt`, waere die Gegenzahl 99'990 nicht mehr der Wert des Mutanten, und die
`!=`-Zusicherung daneben wuerde still wirkungslos. Die drei Zeilen sind der Draht, der
das meldet.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Abgeschwaechte Tests.** `git log` auf `kern/test/werte_probe.cpp` nennt zwei Commits
  (`ceebee3`, `ce59b8b`); der Baucommit ist reine Ergaenzung, 236/0. Keine gesenkte
  Schwelle, keine entfernte Zusicherung, kein uebersprungener Aufruf.
- **Vier Pruefungen, vier Aufrufe.** Alle vier stehen in `main`. Das ist nicht bloss
  gelesen: Jede der vier Mutationen hat in ihrer Pruefung eine Zeile gerissen -- eine
  nicht aufgerufene Pruefung koennte das nicht.
- **Der Regressionsbestand.** Die Erwartungswerte sind nicht aus einem Lauf uebernommen,
  sondern in den Kommentaren hergeleitet, und ich habe sie unabhaengig nachgerechnet
  (Korb 3 · 3.333/10.000 → 1 → 100.000 Cent; −4 · 25.000 → −10^10 Cent; 700 + 2.000.000;
  600.000 · 10.000/5.000 und /20.000). Alle stimmen.
- **Zustandswiederbelegung.** `probe_positionswert_traegt_das_vorzeichen` legt
  `stelle_position` dreimal neu, nachdem die `Zustand`-Referenz schon genommen ist. Das
  ist tragfaehig und beweist sich selbst: Griffe die zweite Belegung nicht, muesste
  Zeile 765 (`positionswert == +10^10`) am unveraenderten Modul rot sein. Sie ist gruen.
- **Dateischnitt.** Der Baucommit fasst ausserhalb dieses Pakets nur `befunde/` und die
  Statuszeile `offen` → `gebaut` im eigenen Paket an. `kern/src/werte.cpp` und
  `kern/include/kern/werte.hpp` sind unberuehrt -- genau das verlangt der Abschnitt *Was
  ausdruecklich nicht dazugehoert*.
- **Die Reihenfolgesperre.** 0087 traegt `haengt_an: [0002-..., 0088-...]`. Die in 0088
  angeordnete Reihenfolge steht also dort, wo sie wirkt.

## Kein Vorschlag

Ich habe keinen geschrieben. Der naechstliegende waere ein wiederholbarer
Mutationslauf statt der einmaligen Handmessung des `kern-pruefer`s -- aber
Mutationsproben sind in diesem Vorhaben laengst gaengige Praxis (neunzehn Pakete nennen
sie), und ein Paket „macht das nochmal, aber allgemein" waere die Sorte Vorschlag, die
einen Lauf kostet und nichts entscheidet.
