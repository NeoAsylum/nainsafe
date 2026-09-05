---
typ: pruefung
paket: 0123-mal-kopf-behauptet-null-aufrufer
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Jede Behauptung des neuen Absatzes einzeln gegen den Baum gemessen -- Zahl und Ort der Aufrufer per Mustervergleich, ihre Lebendigkeit per Mutation (zweimal rot), der Bezugsstand per `git`, die Gruenfaerbung in beiden Profilen auf einem frischen Baum aus `git archive HEAD`.
befunde: 0
---

# Pruefung 0123 -- der Kopf von `mal` nennt heute fuenf Aufrufer

Der Gegenstand ist ein Absatz in `kern/include/kern/festkomma.hpp`, nicht eine
Rechnung. Der Nachweis muss deshalb die **Behauptungen** treffen, nicht den Ablauf:
Jede Zusicherung des neuen Textes steht unten einzeln, mit dem Aufruf, der sie
gemessen hat.

## 0. Umfang der Aenderung -- mechanisch, nicht gelesen

Der Stand liegt in `HEAD`; eingecheckt wurde er unter fremdem Betreff (`0134179`,
Betreff `architekt: 0116-...`), was der bekannte Schnittfehler aus Paket 0121 ist und
nicht diesem Paket anzulasten.

```
git show 0134179 -- .../kern/include/kern/festkomma.hpp \
  | grep '^[+-]' | grep -v '^[+-][+-][+-]' | grep -v '^[+-]///'
```

Leere Ausgabe. **Es sind ausschliesslich `///`-Zeilen geaendert**, ein einziger
Abschnitt, 22 Zeilen fort, 23 dazu. Damit ist Regressionsfreiheit strukturell gegeben,
und die drei uebrigen Fragen meiner Rolle -- Determinismus, Rueckkopplung,
Zustandsausgabe -- koennen von dieser Aenderung nicht beruehrt sein. Sie sind trotzdem
unten mitgefahren, weil eine Pruefung, die das nur behauptet, von keiner zu
unterscheiden ist.

## 1. „Heute mit fuenf Aufrufern, und alle fuenf stehen in `kern::werte`"

Selbst gemessen, **weiter** als der Kopf angibt: nicht nur `kern/`, `pruefstand/`,
`werkzeuge/`, sondern zusaetzlich `messung-stack/`, das der Kopf nicht nennt.

```
grep -rn "mal(" kern pruefstand werkzeuge messung-stack \
     --include=*.cpp --include=*.hpp | grep -v "/bau/"
```

Ausserhalb von `festkomma.hpp` selbst und `kern/test/` steht der Aufruf an genau fuenf
Stellen, alle in `kern/src/werte.cpp`, alle innerhalb von `namespace kern::werte`
(Zeile 53 bis 708; drei davon zusaetzlich im anonymen Namensraum 76 bis 484):

| Zeile | Funktion | Ausdruck |
|---:|---|---|
| 125 | `tsd_in_cent` | `mal(tausend_usd, 100'000)` |
| 145 | `lobbypunkte_aus_geld` | `mal_geteilt(cent, 10'000, mal(konst.lobbykosten, rabatt))` |
| 449 | `positionswert_aus` | `tsd_in_cent(mal(stufen, je_stufe))` |
| 583 | `korbbestand` | `mal_geteilt(anleihewert(...), mal(betrag(stufen), konst.stufenweite), 10'000)` |
| 666 | `fondsanteil` | `plus(mal(betrag(stufen), konst.stufenweite), anteil)` |

Fuenf Stellen in fuenf verschiedenen Funktionen -- „fuenf Aufrufer" ist also auch in
der strengeren Lesart richtig. In `pruefstand/`, `werkzeuge/` und `messung-stack/`
steht keiner; die zwoelf Stellen in `kern/test/festkomma_probe.cpp` nimmt der Kopf
ausdruecklich aus und sagt warum. In `kern/test/werte_probe.cpp` stehen zwei weitere
Treffer (724, 881) -- beide Fliesstext in einem Mutationskatalog, keine Aufrufe.

**Die Rechenarten habe ich einzeln gegen den Code gehalten**, alle fuenf treffen zu.
Der Nenner bei 145 ist wirklich der Nenner: `mal_geteilt(a, b, c)` bricht bei `c == 0`
ab (`festkomma.hpp` Zeile 157), `c` ist also das dritte Argument.

Auch die Einordnung nach T5 traegt: `stufen` ist Klasse 11 (Positionsstufe),
`je_stufe` ueber `stufenwert_aus` Klasse 2, `stufenweite` nach `technik.md` Klasse 4,
`lobbykosten` Klasse 1. Die drei Stellen 449, 583 und 666 multiplizieren damit
tatsaechlich zwei Groessen mit erklaerter Klasse.

Und die alte Behauptung ist fort: `grep -n "nicht gebaut\|ohne Aufrufer\|keinen
Aufrufer\|noch nicht vor"` ueber die Datei liefert nur noch zwei Treffer, beide
unbeteiligt (Zeile 59 zur Nachweisbarkeit, Zeile 190 aus dem Absatz zu `plus`).

## 2. Rotnachweis -- sind die fuenf Aufrufer lebendig?

Ein Mustervergleich zeigt Text. Dass die fuenf Stellen wirklich gerechnet werden,
zeigt erst eine Mutation. Ich habe **die Aufrufstelle** verbogen und nicht die
Definition -- der saubere Kopf zuerst, dann das Makro, dann die Quelle:

```
c++ -std=c++20 ... -I kern/include \
    -include kern/include/kern/festkomma.hpp \
    -include $TMPDIR/mutant.h \
    -c kern/src/werte.cpp -o $TMPDIR/werte_mutant.o
```

**Mutant A** (`mal(a,b)` + 1 ueberall) -- Uebersetzungsfehler in `werte.cpp` 172 und
174: `4200000000001 == 4200000000000`. Damit ist Aufrufer 1 (`tsd_in_cent`) lebendig
und beim Uebersetzen abgedeckt.

**Mutant B** (+1, aber `tsd_in_cent` ausgenommen ueber `(b) == 100000`), gebunden
gegen das unveraenderte `werte_probe.cpp.o` und die uebrigen Objekte des
OFF-Baubaums: **14 Zusicherungen rot**, darunter `positionswert`, `korbbestand`,
`fondsanteil` und `fondsvermoegen`. Damit sind die Aufrufer 3, 4 und 5 lebendig und
zur Laufzeit abgedeckt.

**Mutant C** (+1000 statt +1) -- Uebersetzungsfehler in `werte.cpp` 193 und 195:
`9990 == 10000` und `19960 == 20000`. Damit ist auch Aufrufer 2
(`lobbypunkte_aus_geld`) lebendig.

**Warum es Mutant C brauchte, von Hand nachgerechnet.** Bei Mutant B blieb 145 gruen,
und das ist kein Zufall: Das +1 landet dort im *Nenner*. Mit `lobbykosten = 100` und
`rabatt = 10'000` ist der Nenner 1.000.000, der Zaehler 10^10, das Ergebnis 10.000.
Verschoben: 10^10 / 1.000.001 = 9999,990..., und `runde_von_null_weg` rundet zur
naechsten Ganzzahl (`rest >= an - rest`, Zeile 109) -- also zurueck auf 10.000. Erst
+1000 verlaesst das Rundungsfenster: 10^10 / 1.001.000 = 9990,0099... → 9990, und
10^10 / 501.000 = 19960,0798... → 19960. **Beide Zahlen stimmen mit dem ueberein, was
der Uebersetzer gemeldet hat** -- die Handrechnung und die Maschine sagen dasselbe.

Das ist eine Trennschaerfe-Beobachtung zur bestehenden Zahlenprobe aus Paket 0002,
kein Befund gegen 0123: Ein relativer Fehler von 10^-6 im Nenner ist dort unsichtbar,
die realistischen Mutationen (Operanden vertauscht, `plus` statt `mal`) sind es nicht.

## 3. „Selbst gemessen am 2026-09-05 auf dem Stand `f6731fe`"

```
git cat-file -t f6731fe                    -> commit
git log --oneline -1 f6731fe               -> datenbauer: 0078-reihentoml-preisbasis-...
git merge-base --is-ancestor f6731fe HEAD  -> Vorfahr
git diff --stat f6731fe HEAD -- .../kern/src/werte.cpp .../kern/include/kern/werte.hpp
                                           -> leer
```

Der Bezugsstand existiert, liegt vor `HEAD`, und **`werte.cpp` ist zwischen ihm und
`HEAD` unveraendert**. Die genannte Zahl galt dort und gilt heute noch; sie ist damit
weder abgeschrieben noch veraltet. Das Datum ist der heutige Tag.

## 4. „Der Baum bleibt in beiden Profilen gruen"

Nicht im Arbeitsbaum gemessen, sondern auf einem frischen Baum aus
`git archive HEAD ventures/0016-... specs decisions`, damit uncommittete
Zwischenstaende paralleler Laeufe nicht mitlaufen.

| Profil | `cmake -S` | `cmake --build` | `ctest` |
|---|---|---|---|
| `FABRIK_SANITIZER=ON` (Vorgabe) | ok | ok, 19 Ziele mit Warnsatz | **14/14 bestanden** |
| `FABRIK_SANITIZER=OFF` | ok | ok, 17 Ziele mit Warnsatz | **14/14 bestanden** |

In beiden Laeufen ist `belegstellen_riegel` unter den bestandenen Proben. Der
Warnsatz traegt `-Werror`; eine Warnung waere ein Baufehler gewesen und ist keiner
aufgetreten.

Alle Wegwerfbauten und die drei Mutantenobjekte liegen unter `$TMPDIR`
(`/tmp/claude-1000/kp0123*`), nichts davon im Vorhaben -- es kann also nichts in einen
Commit geraten.

## 5. Wonach ich sonst gesucht und nichts gefunden habe

- **Ob der Kopf sich selbst widerspricht.** Der Nachbarabsatz zu `plus`/`minus` (Zeile
  184 ff., aus Paket 0087) argumentierte mit dem gegenteiligen Stand; genau dieser
  Widerspruch ist jetzt aufgeloest. Der Absatz zu Massnahme 4.3 (239 ff.) nennt
  `tsd_in_cent` schon vorher als blanke Multiplikation -- der neue Text verweist
  darauf und stimmt damit ueberein.
- **Ob das Paket seine eigenen Ausschluesse einhaelt.** `mal` selbst unveraendert, das
  Zitat aus `technik.md` unveraendert, keine Aussage darueber, *wodurch* Massnahme 4.3
  durchgesetzt wird -- der Text sagt nur, wo sie greift.
- **Ob die enger gefasste Suche des Kopfes einen Aufrufer verdeckt.** Nein:
  `messung-stack/` steht nicht in der genannten Menge, enthaelt aber keinen Aufruf.
- **Ob der Kopf einen Aufrufer nennt, den es nicht gibt.** Nein; alle fuenf Namen
  liegen an den angegebenen Stellen.

## 6. Gesehen, aber nicht diesem Paket anzulasten

**`technik.md` sagt weiter das Gegenteil.** Dort steht im Abschnitt zu T7, die fuenfte
Rechenart komme „heute **nicht** vor, weil `kern::werte` noch nicht gebaut ist" -- also
genau der Satz, den dieses Paket im Kopf ersetzt hat. Das ist der Fall, den der
Vorschlag von 0123 vorhergesagt hat, nur in der anderen Reihenfolge. Er ist bereits
zugeschnitten und offen: `0074-massnahme-43-mechanisch-erzwingen` (`rolle: architekt`,
`status: offen`, Dateiliste `specs/.../technik.md`), und seine Bedingung nennt den Satz
zur fuenften Art ausdruecklich. **Ein zweites Paket dafuer waere eine Doppelung**, ein
zweiter Beleg gehoert in den Befund -- hier steht er.

**Die Zweiteilung im letzten Satz des Absatzes ist unscharf, aber nicht falsch.** Der
Text stellt „die letzten drei" (zwei `i64` mit Groessenbedeutung) gegen „die ersten
beiden" (ein Faktor ist Skalen- oder Kalibrierzahl). Beide Haelften sind fuer sich
wahr. Sauber trennen tun sie nicht: `stufenweite` bei 583 und 666 ist ebenso ein
Parameterschluessel wie `lobbykosten` bei 145, und `lobbykosten` hat ebenso eine
T5-Klasse wie `stufenweite`. Das ist keine Vorgabenverletzung -- `specs/` schreibt
keine Gruppierung vor --, und der moegliche Fehlschluss zeigt in die **sichere**
Richtung: Wer den Satz liest, prueft seine Multiplikation eher zu oft gegen 4.3 als zu
selten. Genau die umgekehrte Wirkung hatte der alte Satz, und sie war der Grund fuer
dieses Paket. Deshalb kein Befund.

## Urteil

**`geprueft`.** Alle drei Bedingungen der Abnahme sind erfuellt: Der Absatz sagt den
heutigen Stand mit allen fuenf Aufrufern und ihren Rechenarten, die Zahl ist selbst
gemessen und mit einem gueltigen, noch tragenden Bezugsstand genannt, und der Baum ist
in beiden Profilen gruen. Keine Befunde, kein Vorschlag.
