---
typ: pruefung
paket: 0088-werte-probe-vier-unbelegte-vorgaben
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Den zweiseitigen Nachweis je Vorgabe selbst gefahren -- am unveraenderten `werte.cpp` sind alle 14 Proben gruen, mit jeder der vier im Paket angegebenen Mutationen wird `werte_probe` rot, und zwar jedes Mal ausschliesslich in der neuen Pruefung, die dieser Vorgabe zugeordnet ist.
befunde: 0
---

# Die vier Riegel halten, jeder einzeln -- und daneben liegt eine fuenfte Vorgabe derselben Familie offen

## Zur Datei: warum sie nicht `...-2026-09-05.md` heisst

Unter dem Namen aus der Rollenvorlage liegt bereits eine Pruefung dieses Pakets von
heute. Sie zu ueberschreiben waere ein Loeschen nach Hausregel 3, also steht diese
daneben. Sie ist **unabhaengig gefahren**: Ich habe die vier Mutationen selbst gebaut und
selbst gemessen, statt ein fremdes Ergebnis zu uebernehmen. Wo meine Zahlen von denen der
ersten Pruefung abweichen, sage ich es unten.

Nicht gelesen habe ich `befunde/messung-0088/nachweis.md` und
`notizen/testentwickler.md`. Beides stammt vom Bauagenten aus demselben Commit; wer die
Begruendung liest, prueft die Absicht statt das Ergebnis.

## Aufbau

`git archive HEAD ventures/0016-... | tar -x -C $TMPDIR` als Arbeitskopie, dazu
`specs/0016-...` -- **anders als in der ersten Pruefung**, die `belegstellen_riegel` aus
dem Lauf nehmen musste, weil ihm in der Kopie die Vorgaben fehlten. Mit den `specs/`
daneben laeuft er mit, und die gruene Seite ist damit **14 von 14 ohne Ausnahme** statt
13 von 13 mit einer erklaerten Ausnahme.

Konfiguriert wie `baulauf.py:160-166` es tut, damit ich am selben Bau messe wie der
Runner:

```
cmake -S <wurzel> -B <bau> -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_CXX_FLAGS="-fwrapv -fno-fast-math"
```

`FABRIK_SANITIZER` steht in `werkzeugkette.cmake` ohnehin auf `ON`; die Proben linken also
`kern_geprueft` mit `-fsanitize=undefined,address`. g++ 15.2.0 = `FABRIK_UEBERSETZER_GEPRUEFT`.

Jede Mutation ist eine Textersetzung auf einer **Kopie** in `$TMPDIR`, jede mit
Trefferbremse (`assert text.count(alt) == 1`). Das Repo wurde nicht angefasst;
`git status` fuehrt am Ende nichts, was ich verursacht haette. Die Bremse hat einmal
zugeschlagen und dabei etwas gezeigt: Das Muster fuer die `festkomma`-Mutation kommt
**zweimal** vor (`festkomma.hpp:161` in `mal_geteilt`, `:202` in `mal`). Ohne Bremse haette
ich beide mutiert und das Ergebnis der falschen Funktion zugeschrieben.

Nach jeder Ruecknahme `os.utime` auf die Datei und **M0 erneut** -- sonst baut `make` den
Mutanten nicht zurueck. Jeder Bau ist auf „Building" geprueft (2 Ziele je Lauf: `kern` und
`kern_geprueft`); ein Lauf, der nur „Linking" zeigt, misst den Mutanten davor.

## Die gruene Seite

M0, ohne jeden Eingriff, vor der Messreihe und nach jeder Ruecknahme:

```
100% tests passed, 0 tests failed out of 14
```

## Die rote Seite, Vorgabe fuer Vorgabe

| Mutation | Urteil | gerissene Zusicherungen | Pruefung |
|---|---|---|---|
| **M0** Kontrolle ohne Eingriff | **gruen** | — | — |
| **M1** `beteiligung_wert_aus`: `tsd_in_cent` nach innen gezogen | **rot** | 693, 698, 708, 716 | `probe_skalengrenze_am_aeussersten_aufruf` |
| **M2** `positionswert_aus`: `mal(betrag(stufen), je_stufe)` | **rot** | 756, 759, 772, 773 | `probe_positionswert_traegt_das_vorzeichen` |
| **M3** `marktkorb`: `waehrungswert` je Land dazuaddiert | **rot** | 820, 823 | `probe_marktkorb_ohne_waehrungen` |
| **M4** `waehrungswert`: Wechselkurs statt des Literals 10.000 | **rot** | 860, 861, 866, 867 | `probe_waehrungswert_fester_kurs` |

**Keine Mutation reisst eine Zusicherung ausserhalb ihrer eigenen neuen Pruefung, und
keine reisst eine andere Probe als `werte_probe`.** Bei jedem der vier Laeufe blieben die
uebrigen 13 Proben gruen. Die Zuordnung „eine Pruefung je Vorgabe" ist damit gemessen und
nicht behauptet. Das Abnahmekriterium ist erfuellt.

**Die vier ausgeschriebenen Gegenzahlen stimmen auf die Einheit.** Eine `!=`-Zusicherung
reisst nur bei Gleichheit; dass sie reisst, belegt also, dass der Mutant **genau** die im
Kommentar als verworfen bezeichnete Zahl liefert: M1 `!= 99'990`, M2 `!= 10'000'000'000`,
M3 `!= 3'800'700`, M4 zweimal `!= 600'000`, dazu M1b `!= 66'670` (unten). Damit sind die
Handrechnungen des Pakets nachgerechnet und nicht geglaubt.

## Welche Zusicherung hat kein Mutant rot bekommen?

Die Frage, ohne die eine Empfindlichkeitsmessung unvollstaendig ist. Vier weitere Mutanten
allein zu diesem Zweck:

- **M1b** -- die dritte denkbare Fehlstelle aus Vorgabe 1: `tsd_in_cent` **zwischen**
  Korbanteil und Abschlag. Rot: 708, 712. Damit ist auch `!= 66'670` scharf, das M1 nicht
  erreicht.
- **M6** -- `wert` teilt durch den doppelten Wechselkurs, halbiert also jede Bewertung.
  Rot in den vier neuen Pruefungen: 688, 751, 752, 756, 765, 772, 812, 813, 814, 815, 820,
  860, 861, 866, 873.
- **M7** -- `handelsvolumen` zaehlt je Paar acht zu viel. Rot: 814, 815, 816, 817, 854,
  855, 860, 861, 872, 873.
- **MF** -- `festkomma::mal_geteilt` rechnet mit `b + 1`.

Zusammengelegt ist **jede Zusicherung der vier neuen Pruefungen mindestens einmal rot
gewesen -- ausser 697, 711 und 715.** Die drei sind reine Literalrechnungen
(`mal_geteilt(300'000, 3'333, 10'000) == 99'990` und zwei gleicher Bauart) und haengen an
`festkomma`, nicht an `werte.cpp`.

**Hier weiche ich von der ersten Pruefung ab, und zwar praeziser statt anders.** Sie nennt
die drei „der Bauart nach unerreichbar". Gemessen ist der Grund schaerfer: MF bricht schon
beim **Uebersetzen** ab, weil `festkomma.cpp:81, 90, 95` dieselben Rechnungen als
`static_assert` fuehren. Die drei Zeilen koennen also nicht rot werden, weil ein
Compilezeit-Riegel jeden Mutanten vorher toetet, der sie rot machen koennte.

Das ist **kein Befund**: Ihr Zweck ist genau der, den das Paket ihnen gibt -- aenderte sich
die Rundung in `mal_geteilt`, waere `99'990` nicht mehr der Wert des Mutanten und die
`!=`-Zusicherung daneben wuerde still wirkungslos. Dass der Draht doppelt liegt, ist
Redundanz und kein Fehler. Er sollte nur nicht als Empfindlichkeit gezaehlt werden.

## Die vier Vorgaben gegen `specs/` -- prueft die Probe das Richtige?

Ein Test kann empfindlich und trotzdem falsch sein. Deshalb jede der vier unabhaengig im
Wortlaut nachgeschlagen:

| Nr. | Vorgabe laut `specs/0016-.../technik.md` | Fundstelle |
|---|---|---|
| 1 | `tsd_in_cent` am **aeussersten Aufruf** von `positionswert` und `beteiligung_wert` | 424 (T47/T50), bestaetigt 2929 |
| 2 | Nr. 15 `positionswert(p) = tsd_in_cent(stufen(p) · stufenwert(p))` -- **ohne** Betragsstriche, im Gegensatz zu Nr. 14 `fondsanteil` **mit** | 2080 gegen 2079 |
| 3 | Nr. 7 `marktkorb(m, k)` = Σ 12 `korbwert` + Σ 4 `anleihewert` -- Waehrungen kommen nicht vor | 2072, Formel 1883 |
| 4 | Nr. 4 `waehrungswert(l) = wert(handelsvolumen(l), 10.000, l)` -- festes Literal | 2069, Formel 1932 |

Alle vier stimmen. Die Zeilennummern liegen rund 26 Zeilen hoeher als in der ersten
Pruefung; `technik.md` ist nach dem Baucommit noch einmal geaendert worden (`a127600`,
nach `ce59b8b`). Der Inhalt ist derselbe -- genau der Fall, fuer den das Paket selbst
anordnet, die Funktion gelte und nicht die Zeilennummer.

## Wonach ich sonst gesucht habe

- **Abgeschwaechte Tests.** `git log` auf die Datei nennt zwei Commits; im Baucommit
  `ce59b8b` steht `werte_probe.cpp` mit **236 hinzugefuegt, 0 entfernt**. Keine gesenkte
  Schwelle, keine entfernte Zusicherung, kein uebersprungener Aufruf. Gefunden ueber
  `git log` auf die Datei, nicht ueber den Betreff -- der Betreff lautet
  `architekt: 0051-...` und haette in die Irre gefuehrt.
- **Vier Pruefungen, vier Aufrufe.** Alle vier stehen in `main` (Zeilen 894--897). Das ist
  nicht bloss gelesen: Jede der vier Mutationen hat in ihrer Pruefung eine Zeile gerissen,
  was eine nicht aufgerufene Pruefung nicht koennte.
- **Regressionsbestand.** Die Erwartungswerte sind nicht aus einem Lauf uebernommen,
  sondern im Kommentar hergeleitet. Unabhaengig nachgerechnet: 3 · 3.333/10.000 → 1 →
  100.000; −4 · 25.000 → −10^10; 700 + 2.000.000 = 2.000.700; 600.000 · 10.000/5.000 =
  1.200.000 und /20.000 = 300.000. Alle stimmen.
- **Dateischnitt.** `kern/src/werte.cpp` und `kern/include/kern/werte.hpp` stehen beide
  zuletzt auf `ceebee3`, sind vom Paket also unberuehrt -- genau das verlangt sein
  Abschnitt *Was ausdruecklich nicht dazugehoert*.
- **Die andere Haelfte von Vorgabe 2.** Vorgabe 2 ist eine Entscheidung ueber den
  **Unterschied** zwischen T48 Nr. 14 (`|stufen|`) und Nr. 15 (`stufen`). Das Paket nagelt
  Nr. 15 fest. Ich habe die Gegenrichtung gefahren -- `fondsanteil` verliert sein `betrag`
  (**M5**) -- und sie ist belegt: rot in 541, 545, 553, 563
  (`probe_fondsanteil_und_korbbestand`, vorhanden seit 0002). Kein Befund.

## Ein Vorschlag: dieselbe Familie, dritte Fundstelle, unbelegt

`betrag` kommt in `werte.cpp` an **drei** rechnenden Stellen vor. Zwei sind jetzt belegt
(Nr. 15 durch dieses Paket, Nr. 14 durch 0002). Die dritte ist es nicht:

**M8** -- in `korbbestand`, Anleihezweig (`werte.cpp:598`),
`mal(betrag(stufen), konst.stufenweite)` → `mal(stufen, konst.stufenweite)`:

```
100% tests passed, 0 tests failed out of 14
```

`technik.md:2128` schreibt die Betragsstriche aus:

```
korbbestand(z) = Σ ueber die 12 Koerbe   mal_geteilt(korbwert(l, s), fondsanteil(l, s), 10.000)
               + Σ ueber die  4 Anleihen mal_geteilt(anleihewert(l), |stufen(p)| · stufenweite, 10.000)
```

Der Grund, warum es durchrutscht, ist genau die Bauart, gegen die dieses Paket antritt:
Die einzige Probe, die den Anleihezweig ueberhaupt anfasst
(`probe_fondsanteil_und_korbbestand`), belegt ihn mit `stufen = +3`
(`werte_probe.cpp:560`) -- und bei positiver Stufenzahl sind beide Formen dieselbe
Rechnung. Wortgleich der Mechanismus, den das Paket fuer `waehrungswert` beschreibt
(Wechselkurs auf dem Startwert) und fuer `marktkorb` (Handelsstroeme auf null).

Eine schriftliche Vorgabe laesst sich also verletzen, ohne dass eine Probe rot wird --
wortgleich die Lage, die dieses Paket fuer vier andere Vorgaben aufgeloest hat. Das ist
**kein Rueckgabegrund**: Es steht in keiner der vier Abnahmebedingungen, und `korbbestand`
gehoert nicht zum Auftrag. Es ist ein eigenes Paket, und es liegt als
`aufgaben/0111-korbbestand-anleihezweig-betrag-der-stufen.md` daneben.

Nicht doppelt zu 0110 (`mutationslauf-als-wiederholbarer-riegel`): Das baut das
**Messgeraet**, 0111 schliesst eine **einzelne gemessene Luecke**. Der Fall aus 0111 ist
ein guter Katalogeintrag fuer 0110, sobald es das gibt.
