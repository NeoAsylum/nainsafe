---
typ: pruefung
paket: 0085-abbruchmeldungen-im-wortlaut-pruefen
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Die vom Paket verlangte Sabotage ausgefuehrt (Riegel `if (vorrundennummer == festkomma::I64_MAX)` aus `kern/src/schritt.cpp` gestrichen) -- `schritt_probe` wird rot und nennt in der roten Zeile erwartetes Textstueck und angekommene Meldung; dazu sechs weitere Mutanten, die jede der sieben Erwartungen mindestens einmal rot bekommen haben.
befunde: 0
---

# Geprueft: der Wortlaut traegt, und er traegt an jeder der sieben Erwartungen

Bezugsstand `5c04d7d`. Der Quelltext des Pakets liegt in Commit `ce59b8b`
(`architekt: 0051-t46-gebietspraefix-entscheiden`); der Commit mit dem 0085-Betreff
(`ce501b2`) traegt allein das Logbuch des Bauagenten. Das ist die bekannte Eigenart des
Laeufers und kein Befund gegen das Paket.

Alle Eingriffe lagen in einer Kopie unter `$TMPDIR` (`git archive HEAD <pfad> | tar -x`).
`git status --short ventures/0016-.../kern/` ist am Ende dieses Laufs leer -- weder
`schritt_probe.cpp` noch `schritt.cpp` noch `zustand.cpp` sind im Repo angefasst worden.

## Was ich gezaehlt habe

**Fuenf Aufrufstellen, sieben ausgefuehrte Erwartungen** -- unabhaengig nachgezaehlt und
mit der Zahl des Bauagenten uebereinstimmend. Die Stellen: Zeile 485 (Ueberlauf in
`probe_runden`), 551 und 558 (die beiden `Startbelegung`-Haelften), 607 (`spielmodus`),
646 (Schleife ueber drei Rundennummern). Der Unterschied fuenf zu sieben ist die
Schleife.

**Es gibt keine sechste Stelle.** `grep` auf `try`, `catch`, `geworfen`, `wirft`,
`bricht`, `Abbruch` ueber die ganze Datei: Der einzige `try`/`catch` steht in
`bricht_ab_mit` (`:159-188`), jede Abbrucherwartung laeuft ueber `BRICHT_AB_MIT`. Das
alte `PRUEFE(geworfen)`-Muster kommt nur noch in Kommentaren vor, die es beschreiben.

## M0 -- die Kontrolle ohne Eingriff

`schritt_probe` gruen, sieben Zeilen `Abbruch wie erwartet`. Der ganze Kern gruen:
10 von 10 Proben bestanden (`ctest` in `bau-m0`). Ohne diese Kontrolle belegte "alle
Mutanten sterben" auch, dass mein Aufbau kaputt ist.

## M1 -- die vom Paket verlangte Sabotage

Der Block `if (vorrundennummer == festkomma::I64_MAX) { ... }` (14 Zeilen) ersatzlos aus
`kern/src/schritt.cpp` gestrichen. Ergebnis: **rot**, genau zwei der sieben Erwartungen
fallen, die uebrigen fuenf bleiben gruen.

```
FEHLGESCHLAGEN Zeile 485: Runde nach der letzten zaehlbaren -- es hat abgebrochen, aber der falsche Riegel.
  erwartetes Textstueck: "kern::schritt"
  angekommene Meldung:   "kern::schreiber -- eine Runde vor der ersten gibt es nicht"
FEHLGESCHLAGEN Zeile 646: partie.runde = groesster int64_t -- es hat abgebrochen, aber der falsche Riegel.
  erwartetes Textstueck: "kern::schritt"
  angekommene Meldung:   "kern::schreiber -- eine Runde vor der ersten gibt es nicht"
2 Pruefung(en) fehlgeschlagen
```

Beide geforderten Eigenschaften stehen da: **welcher** Riegel erwartet war und **was**
tatsaechlich ankam. Damit ist das Abnahmekriterium im Wortlaut erfuellt.

## M2 bis M5 -- weil M1 allein zu wenig beweist

M1 zeigt nur, dass das Stueck `"kern::schritt"` geprueft wird. Ob das **unterscheidende**
zweite Stueck etwas traegt, sagt es nicht. Vier weitere Mutanten, alle in der Quelle und
nicht in der Probe:

| Mutant | Eingriff | erwartet | gemessen |
|---|---|---|---|
| M2 | die beiden Halbsaetze `damit negativ` und `damit der groesste int64_t` in `schritt.cpp` **vertauscht** -- beide Riegel werfen weiter aus `kern::schritt` | 4 rot | **4 rot** (485, 646 dreimal) |
| M3 | Riegel `if (vorrundennummer < 0)` gestrichen | die zwei negativen Faelle | **2 rot**, die beiden `I64_MAX`-Faelle bleiben gruen |
| M4 | `spielmodus`-Riegel durch `break;` ersetzt | 1 rot | **1 rot** (607) |
| M5 | die Halbsaetze der beiden `Startbelegung`-Riegel in `zustand.cpp` vertauscht -- beide tragen weiter `kern::zustand::Startbelegung` im Namen | 2 rot | **2 rot** (551, 558) |

M2 ist der wichtigste: Er trennt "der Kastenname wird geprueft" von "der Riegel wird
geprueft". Beispielzeile:

```
FEHLGESCHLAGEN Zeile 485: Runde nach der letzten zaehlbaren -- es hat abgebrochen, aber der falsche Riegel.
  erwartetes Textstueck: "groesste int64_t"
  angekommene Meldung:   "kern::schritt -- ... 9223372036854775807 und damit negativ: eine naechste Runde ..."
```

M3 belegt die Feinheit, auf die es bei der Schleife ankommt: Die Erwartung haengt am
**Fall** und nicht an der Schleife. Von den drei Rundennummern fallen genau die zwei
negativen, `I64_MAX` bleibt gruen.

M4 beantwortet die erste der beiden Unsicherheiten, die der Bauagent selbst notiert hat
(die drei uebernommenen Bedingung-7-Stuecke beim `spielmodus`). Der Riegel entfaellt,
`kern::schritt` bricht trotzdem ab -- aber an einer anderen Stelle, ueber die
Zuordnungstafel. Das Stueck `"spielmodus"` faengt es:

```
  erwartetes Textstueck: "spielmodus"
  angekommene Meldung:   "kern::schritt -- land.US.aufsichtszaehler (Nr. 23) steht in der
                          Sollmaske, gehoert aber Schritt 0 (keiner): ..."
```

Die Stelle ist damit regressionsgesichert. Ob ausgerechnet `"310"` fuer sich genommen
entscheidet, ist damit nicht gezeigt und auch nicht verlangt -- es stammt aus Bedingung 7,
die etwas anderes fordert (die Meldung nennt ihren Grund).

## M6 -- der Riegel gegen die stille Verwaesserung

Die Kennzeichenliste an einer Stelle geleert. Zwei Dinge geschehen, beide richtig:

1. Der Warnsatz laesst es gar nicht erst durch --
   `error: unused variable 'nach_der_letzten' [-Werror=unused-variable]`.
2. Nimmt man die Deklaration mit heraus, ist der Lauf rot:
   `FEHLGESCHLAGEN Zeile 484: ... kein Kennzeichen genannt; so prueft die Stelle nur,
   dass ueberhaupt geworfen wurde`.

Die Zusicherung aus `:149-155` ist also keine Zierde.

## Gemessene Abdeckung statt behaupteter

**Jede der sieben Erwartungen war mindestens einmal rot:** 485 (M1, M2), 551 (M5),
558 (M5), 607 (M4), 646 dreimal (M1, M2, M3). Keine Zusicherung dieser Datei ist von
keinem Mutanten getroffen worden.

## Abgeschwaechte Tests -- gesucht, nichts gefunden

`git diff 2b9fafc ce59b8b -- kern/test/schritt_probe.cpp`, nur die Minuszeilen gelesen.
Entfernt wurden die vier alten `PRUEFE(geworfen)`-Bloecke und die drei Wortlautpruefungen
des `spielmodus` (`nennt_alle_310`, `nennt_den_modus`, `nennt_die_fehlenden_pakete`).
Alle drei stehen als Textstuecke in der neuen Kennzeichenliste wieder da, ergaenzt um
`"kern::schritt"` -- **keine Zusicherung ist gefallen, eine ist dazugekommen.** Keine
Schwelle gesenkt, kein Test uebersprungen.

`kern/src/schritt.cpp` ist in diesem Commit unveraendert; die einzige Fassung mit
Aenderung liegt unter `befunde/messung-0069/baum/` und gehoert einem fremden Paket.

## Die zweite Unsicherheit des Bauagenten: gemessen, gruen

Der Belegstellenriegel hat die Datei im Baulauf nicht gelesen. Nachgeholt: den Riegel aus
dem echten Baum nach `$TMPDIR` konfiguriert und gebaut, `ctest` gegen die echte
Vorhabenwurzel -- **1 von 1 bestanden, 0,82 s.** Der Punkt ist geschlossen.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Regressionsbestand:** Diese Datei fuehrt keinen -- der Erwartungswert der Runde ist
  eine zweite Bauart desselben Zustands (`ausgangslage`), keine abgeschriebene Zahl.
  Nichts, was aus einem Lauf uebernommen sein koennte.
- **`enthaelt` (`:104-119`):** liest nie ueber den Abschluss hinaus. Endet der Heuhaufen
  vor der Nadel, bricht der innere Vergleich an `'\0' != nadel[j]` ab. Kein Griff
  daneben, und der Adress-Sanitizer des Testprofils haette ihn ohnehin gesehen.
- **Ausnahmeart:** `festkomma::abbruch` wirft `std::domain_error` (`festkomma.cpp:27`);
  der Fangblock passt. Der `catch (...)`-Zweig meldet ausdruecklich, dass es die falsche
  Art war, statt sie stillschweigend gelten zu lassen.
- **Dateiliste:** `dateien` nennt allein `kern/test/schritt_probe.cpp`, und genau diese
  eine Quelldatei ist geaendert. Dazu `befunde/messung-0085/nachweis.md`, wie bei jedem
  Paket.

## Kein Befund, aber ein Anschlusspaket

Vorschlag `0107-kennzeichen-gegen-nachbarmeldungen`. Kurz: Die Eindeutigkeit, die das
Abnahmekriterium verlangt, ist heute geprueft, aber nicht **gesichert**. Gemessen
(Mutant M8): Verkuerzt man die `spielmodus`-Liste auf `{"kern::schritt"}` und streicht
denselben Riegel wie in M4, druckt die Probe

```
  Abbruch wie erwartet (Modus spielmodus): kern::schritt -- land.US.aufsichtszaehler (Nr. 23)
  steht in der Sollmaske, gehoert aber Schritt 0 (keiner): ...
```

und meldet `alle Pruefungen bestanden`. Das ist genau der Ausgang, den 0085 abgeschafft
hat -- eine Abschwaechung weiter oben. Das ist **kein Rueckgabegrund**: Das Kriterium
verlangt ein kennzeichnendes Textstueck, und die fuenf Stellen liefern es. Es verlangt
nicht, dass die Kennzeichnung maschinell nachgehalten wird. Das Nachhalten ist eigene
Arbeit, und der Vorschlag beschreibt sie.
