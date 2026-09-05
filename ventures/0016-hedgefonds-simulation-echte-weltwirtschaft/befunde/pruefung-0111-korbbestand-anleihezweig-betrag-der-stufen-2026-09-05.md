---
typ: pruefung
paket: 0111-korbbestand-anleihezweig-betrag-der-stufen
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Zweiseitig selbst nachgemessen -- werte_probe gruen an HEAD (14/14), rot mit genau den zwei Abnahme-Zusicherungen am selbst gebauten Mutanten im Anleihezweig, alte Probenfassung bleibt am selben Mutanten gruen.
befunde: 0
---

# Pruefung 0111: Der Anleihezweig von `korbbestand` ist jetzt abgeriegelt

Unabhaengig gemessen -- eigener Bau, eigener Mutant, Arbeitskopie unter `$TMPDIR`,
Konfiguration wie `baulauf.py` (`RelWithDebInfo`, `-fwrapv -fno-fast-math`, Sanitizer
aus `werkzeugkette.cmake`). Bezugsstand: `HEAD` = `2f5211e`, `kern/` im Arbeitsbaum
sauber (`git status` leer). Die fremde Messtabelle aus dem GEBAUT-Absatz habe ich erst
nach der eigenen Messung gegengelesen.

## Gruene Haelfte

`cmake --build bau` + `ctest --output-on-failure` am Arbeitsbereich der Venture-Wurzel,
unveraendertes `kern/src/werte.cpp`:

```
100% tests passed, 0 tests failed out of 14
```

`werte_probe` besteht. Nebenbefund ohne Gewicht: Der `belegstellen_riegel`, den der
GEBAUT-Absatz als vorher schon rot nennt, ist heute gruen -- Paket 0120
(`datenbauer`, Commit `bf0519b`) hat das Abschnittszitat inzwischen berichtigt. Die
13/14-Angabe des Bauagenten passt zur Geschichte, ist aber ueberholt.

## Rote Haelfte

Mutation in der Arbeitskopie, nie am Repo. Nadel mit Schwanz, damit von den **zwei**
Vorkommen der Form `mal(betrag(stufen), konst.stufenweite)` in `werte.cpp` (`:583`
Anleihezweig Nr. 8, `:666` `fondsanteil` Nr. 14) allein die erste faellt:

```
mal(betrag(stufen), konst.stufenweite), 10'000));  ->  mal(stufen, konst.stufenweite), 10'000));
```

Trefferbremse: `assert count(nadel) == 1` vor der Ersetzung, `assert count(form) == 1`
danach -- die Nachbarstelle `:666` stand nachweislich noch. Bau uebersetzt gruen,
`werte_probe` faellt:

```
FEHLGESCHLAGEN Zeile 937: korbbestand(z, konst) == 200'000
FEHLGESCHLAGEN Zeile 941: korbbestand(z, konst) != -200'000
2 Pruefung(en) fehlgeschlagen
```

Genau die zwei Zusicherungen der Abnahme, und nur sie; nachgeschlagen sind die Zeilen
937 und 941 wirklich `== 200'000` und `!= -200'000`. Von allen zehn Kernproben faellt
am Mutanten allein `werte_probe`.

## Gegenprobe: die Luecke war vorher offen

Die alte Fassung `git show c30acc5^:kern/test/werte_probe.cpp` gegen **denselben**
Mutanten: `100% tests passed`. Der neue Einschub ist der einzige Faenger; das Paket
schliesst eine wirklich offene Luecke, statt etwas doppelt zu sichern.

## Kontrollen und Abnahme-Details

- **M0 vor der Mutation:** Arbeitskopie unveraendert, `werte_probe` gruen.
- **M0 nach der Ruecknahme:** Original-`werte.cpp` und neue Probe zurueckgestellt,
  alle 10 Kernproben gruen. Der Messaufbau traegt.
- **Negative Stufenzahl:** `r.lege(stelle_position(platz), -4)` auf
  `steckplatz_anleihe(Gebiet::DE)` (`werte_probe.cpp:932`).
- **Erwarteter Beitrag als Zahl:** `== 200'000` (`:937`); **verworfene Form als andere
  Zahl:** `!= -200'000` (`:941`). Beide verschieden, beide ausgeschrieben.
- **Aufruf aus `main`:** `probe_korbbestand_nimmt_den_betrag()` steht dort (`:987`).
- **Nichts abgeschwaecht:** Der Diff des Baucommits `c30acc5` an `werte_probe.cpp` ist
  +91/-0 -- rein additiv, keine bestehende Zusicherung geaendert, keine Schwelle
  gesenkt, kein Test uebersprungen. `kern/src/werte.cpp` ist nicht im Commit.
- **Vorgabe im Wortlaut:** `technik.md:2136` (gewandert von `:2128`) schreibt
  `|stufen(p)| · stufenweite` aus; die Umsetzung an `werte.cpp:583` entspricht ihr.
- **Reihenfolgesperre:** `0087` steht auf `fertig`; die Sperre war eingehalten, die
  Stelle wurde -- wie vom Projektmanager verlangt -- am Text gefunden, nicht an der
  Nummer.

Wonach ich sonst gesucht und nichts gefunden habe: eine zweite unbelegte `betrag`-Stelle
(alle drei rechnenden Vorkommen in `werte.cpp` sind jetzt je einzeln gedeckt: `:464`
durch 0088, `:583` durch dieses Paket, `:666` durch 0002), eine Belegung, unter der
beide Formen zusammenfallen (die Probe schliesst sie durch die Long-Gegenprobe `+4` und
die Null-Ruecksetzung selbst aus), und Aenderungen an fremden Zusicherungen im Commit.

Hinweis ohne Urteilsgewicht: Commit `c30acc5` buendelt 11 Dateien mehrerer Pakete
(u. a. 0078, 0101) unter dem Betreff dieses Pakets -- bekanntes Verhalten des Runners,
fuer die Bewertung dieses Pakets ohne Belang, fuer die Suche nach seinem Quelltext der
Grund, warum `git log -- <datei>` der Weg ist und `git show <betreff>` nicht.
