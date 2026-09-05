---
typ: pruefung
paket: 0073-belegstellenriegel-dateiname-weiter-links
pruefer: test-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Sechs Mutanten gegen die acht Faelle des Selbsttests, dazu die Suche nach links auf drei Bestaenden gegen die Fassung von f27dd39 gehalten -- die Verbreiterung faengt genau die zwei benannten Formen und keine falsche, jeder Teilsatz des Kriteriums stirbt an einem eigenen Mutanten, und Bedingung 1 ist mit 5 Treffern und 0 Dateinamen unveraendert.
befunde: 1
---

# Pruefung 0073 -- der Riegel sieht den Dateinamen jetzt auch weiter links

Geprueft wurde der Stand im Arbeitsbaum, der an dieser Datei mit `HEAD` uebereinstimmt
(`git status` meldet `werkzeuge/` unveraendert). Vorher-Stand fuer jeden Vergleich ist die
Fassung aus `f27dd39` -- das ist die letzte Aenderung an dieser Quelldatei vor `dffb251`.
Der im Paket genannte Vorher-Stand `81853b8` hat die Datei nicht angefasst; beide Angaben
meinen denselben Quelltext.

## Aufbau der Pruefung

Wegwerf-Projekt in `$TMPDIR` mit einem `add_executable`/`add_test` je Fassung; die
Paketdatei wurde nicht angefasst. Die Mutanten entstehen als Textersetzung auf einer
**Kopie**, jede mit Abbruch, wenn das Suchmuster nicht trifft -- ein unveraenderter Mutant,
der brav besteht, waere sonst als Empfindlichkeit gezaehlt worden. `M0` ist die Kontrolle:
die unveraenderte Quelle, uebersetzt im selben Aufbau.

## Das Abnahmekriterium, in vier Teilen

### 1. Findet der Riegel den Dateinamen jetzt auch mit Woertern dazwischen?

Ja, und nicht nur im Selbsttest, sondern am Bestand. Beide Fassungen wurden mit demselben
Eingriff versehen -- Bedingung 1 liest zusaetzlich die Datendokumente, so wie es der Rumpf
des Pakets beschreibt -- und auf das Vorhaben gerichtet:

| Fassung | Bauquellen | Mustertreffer | mit Dateinamen | gefunden |
|---|---|---|---|---|
| `f27dd39` (eng) | 53 | 12 | **0** | -- |
| Arbeitsbaum (breit) | 53 | 12 | **2** | `daten/adressen.md:541` und `daten/reihen.toml:344`, beide auf `technik.md` |

Das sind genau die zwei lebenden Formen aus dem Rumpf des Pakets, und es ist kein dritter,
falscher Fund dabei. Beide Zeilen habe ich in der Quelle nachgeschlagen: In `adressen.md`
steht links vom Treffer das Datum, in `reihen.toml` acht Fuellwoerter und ein Komma.

### 2. Rotnachweis fuer die zwei benannten Formen, je einzeln

Mutant **A** stellt die enge Fassung wieder her (Rueckgabe nach dem ersten Wort, wie in
`f27dd39`). Es fallen die Faelle **1, 2, 3 und 8** -- die vier ohne erwarteten Fund bleiben
gruen. Fall 1 traegt die Form mit dem Datum dazwischen, Fall 2 die mit dem Fuellwort;
beide fallen getrennt und sind wortgleiche Ausschnitte aus `daten/adressen.md` Zeile 541
und `daten/reihen.toml` Zeile 344 -- nachgeschlagen, nicht geglaubt.

### 3. Bleibt der Riegel auf dem dann geltenden Korpus gruen?

**Der Riegel ist rot -- und zwar an Bedingung 2, aus fremder Ursache. Das ist gemessen
und nicht uebernommen.** Ich habe die Fassung von `f27dd39` unveraendert uebersetzt und auf
denselben heutigen Baum gerichtet. Sie meldet **dieselben Zahlen und dasselbe Rot**:

```
Bedingung 1: 42 Bauquellen, 5 Zeilenverweise, davon 0 mit Dateinamen daneben.
Bedingung 2: 24 Zitate gefunden, 19 aufgeloest, 8 Fundstellen uebergangen.
             5 Zitate zeigen auf eine Ueberschrift in rueckstand.md, die es nicht gibt.
```

Ursache nachgeschlagen: `81853b8` (Projektmanager, 2026-09-04 22:26) hat in
`rueckstand.md` die Ueberschrift *Was der Geschaeftsfuehrer entscheiden lassen muss* durch
*An den Geschaeftsfuehrer* ersetzt. Die fuenf Zitate stehen in `daten/reihen.toml` und
`daten/einheitenbefund-pwt-baci.md` -- fremdes Gebiet, nicht in der Dateiliste dieses
Pakets, und als Vorschlag **0090** bereits notiert.

Der Teil des Kriteriums, den dieses Paket beruehren kann, ist erfuellt: Bedingung 1 ist mit
5 Treffern und 0 Dateinamen daneben unveraendert, Bedingung 2 mit 24/19/8 ebenfalls. Die
fuenf Treffer sind unveraendert `kern/src/zustand.cpp` Zeilen 786 bis 790; ich habe den
Bestand selbst nach dem Muster durchsucht und keine sechste Stelle gefunden.

**An den Projektmanager, damit es nicht untergeht:** Die Werkzeugkette bleibt rot, bis 0090
gelaufen ist. Wer 0073 abnimmt, nimmt kein gruenes Werkzeug ab.

### 4. Die Regel bei mehreren Namen

Steht im Kopfkommentar unter *Wie weit nach links gesucht wird*, Absatz *Die Regel: es gilt
der naechstgelegene Name*, und traegt Fall 3. Ich habe dafuer einen eigenen Mutanten
gebaut, den der Bauagent nicht hatte: **C** dreht allein den Vorrang um -- gesucht wird
weiter, der **entfernteste** Name gewinnt. Es faellt genau ein Fall, Fall 3, und zwar mit
`daten/adressen.md` statt `spiel.md`. Damit ist die Naechstgelegenheit als eigene Regel
belegt und nicht nur als Nebenwirkung des Abbruchs.

## Regelabdeckung: welcher Fall stirbt woran

Die Frage dieser Rolle ist nicht, ob die Faelle gruen sind, sondern ob einer von ihnen auch
bei kaputter Sache gruen bliebe. Sechs Fassungen, acht Faelle:

| Mutant | Eingriff | rote Faelle |
|---|---|---|
| M0 | keiner (Kontrolle) | keiner, 8 von 8 wie erwartet |
| A | Suche bricht nach dem ersten Wort ab (enge Fassung) | 1, 2, 3, 8 |
| B | `satzanfang_vor` gibt immer 0 (Satzgrenze aus) | **nur 5** |
| C | Vorrang umgedreht, der entfernteste Name gewinnt | **nur 3** |
| E | `endung_zugelassen` gibt immer wahr | 1, 2, 3, 4, 5, 6, 8 |
| F | `dateiname_davor` gibt immer leer | 1, 2, 3, 7, 8 |

**Jeder der acht Faelle ist mindestens einmal rot geworden.** Kein Fall ist Zierde. Die drei
mit erwarteter Leermeldung -- 4 (die `static_assert`-Form), 5 (Name jenseits des Satzendes)
und 6 (Name rechts vom Treffer) -- sind die, an denen ich am ehesten einen stummen Waechter
vermutet haette; Mutant E toetet alle drei, Fall 5 zusaetzlich einzeln an B. Damit ist auch
die Satzgrenze als tragend belegt und nicht als Zierde: Sie ist die einzige Zusicherung,
die B reisst.

## Was ich zusaetzlich gemessen habe

**Der Preis der weiten Suche, auf einem viel groesseren Bestand.** Die Sorge im Rumpf des
Pakets ist, dass ein Dateiname vom Zeilenanfang auf eine Nummer am Zeilenende
durchschlaegt. Ich habe beide Fassungen mit dem breiten Eingriff auf das **ganze Repo**
gerichtet -- 491 Bauquellen, 468 Mustertreffer: enge Fassung 100 Funde, breite 121, also
**21 zusaetzliche**. Neun der 21 habe ich in ihrer Quellzeile nachgeschlagen; alle neun
sind echte Verweise, bei denen der Dateiname weiter links steht, darunter

* `ops/plan.md:46` -- `reihen.toml` mit Klammerzusatz, dann die Nummer;
* `ops/verbesserung.md:68` -- `agents/rollen/ideator.md`, dann vier Woerter;
* `aufgaben/0040-kernanker-klassenzuteilung.md:154` -- die zweite Musterform mit einem
  ganzen Zitat dazwischen.

Kein falscher Fund in der Stichprobe. Das ist die Zahl, die im Paket fehlt: Die
Verbreiterung ist auch dort billig, wo der Bestand zehnmal so gross ist.

**Rueckwaertsindizierung unter Sanitizer, auf demselben grossen Bestand.**
`-Werror -fsanitize=undefined,address -fno-sanitize-recover=all`, 493 Bauquellen, 472
Mustertreffer, 122 Namenssuchen mit Fund -- keine Meldung. `satzanfang_vor` und
`dateiname_davor` laufen sauber, auch an den Zeilenraendern.

**Nichts abgeschwaecht.** Der Unterschied zu `f27dd39` sind 260 hinzugefuegte und 34
entfernte Zeilen. Die 34 sind die alte enge `dateiname_davor` und die Zerlegungsschleife
im Leser, die nach `fund_ab` gewandert ist; das Verhalten des Lesers ist gleich geblieben
(Vorschub `i` auf Trefferanfang plus Trefferlaenge, Selbstverweis weiter unterdrueckt).
Keine Zusicherung entfernt, keine Schwelle gesenkt, kein Test uebersprungen. Der Selbsttest
laeuft vor jedem Lesen des Bestands und bricht mit Code 2 ab -- er ist nicht abwaehlbar,
weil er kein eigener Befehl ist.

**Die Herkunft des Quelltextes stimmt so, wie das Paket sie angibt, und die Falle geht in
beide Richtungen.** Der Quelltext liegt in `dffb251` (`architekt: 0043-...`). Die beiden
Commits mit dem Betreff `testentwickler: 0073-...` enthalten diese Datei nicht -- `79e92e7`
enthaelt stattdessen `kern/test/zustandsausgabe_probe.cpp`, also die Arbeit eines dritten
Pakets. Wer hier nach dem Betreff zuordnet, landet zweimal falsch.

## Der Befund

### Die Herkunftsangabe von Fall 7 nennt eine Datei, die diese Form nicht mehr traegt

Der Kopf der Tabelle sagt: *„Vier der acht sind im Bestand gemessen und nicht erfunden."*
Fall 7 ist einer dieser vier. Seine Herkunft nennt `kern/test/schranken_probe.cpp` und die
Form Dateiname-Nummer-Doppelpunkt zum Platzhalterschluessel.

**Diese Datei traegt die Form seit dem 2026-09-04, 06:17 Uhr nicht mehr.** Commit `9bb7492`
(Paket 0044) hat dort genau diese sechs Belegstellen durch den Schluesselnamen ersetzt;
seine eigene Botschaft sagt es woertlich. Im Bestand von heute steht der Wortlaut nur noch
zweimal, und beide Male unter `befunde/` -- also in einem Ordner, den der Riegel
ausdruecklich nicht liest.

**Wie man es nachstellt:**

1. Den Wortlaut des Falles in `kern/test/schranken_probe.cpp` suchen -- **kein Treffer**.
   `grep -n "druck_max"` auf dieselbe Datei zeigt in Zeile 434 die heutige Fassung: sie
   nennt den Schluessel und keine Nummer.
2. `git show 9bb7492 --stat` -- die Botschaft sagt: *„Sechs Belegstellen in
   kern/test/schranken_probe.cpp nannten Zeilennummern in parameter.toml. Ersetzt durch
   den Schluesselnamen."*
3. Denselben Wortlaut ueber den ganzen Baum suchen -- er steht nur noch in
   `befunde/messung-0052/gegenprobe/kern/test/schranken_probe.cpp` und in
   `befunde/pruefung-0044/alt/probe_alt.cpp`, beide unter `befunde/`.

**Warum es kein Ruecklaufgrund ist:** Der Fall selbst ist in Ordnung. Sein Wortlaut ist
historisch echt, sein Sollwert `parameter.toml` ist unabhaengig richtig, und er ist
rotnachgewiesen (Mutant F). Gemessen wird das Richtige; falsch ist nur die Adresse, unter
der es nachzuschlagen waere.

**Warum es trotzdem ein Befund ist:** Der naechste Agent, der Fall 7 nachmessen will, geht
an die genannte Datei, findet dort nichts und muss raten, ob der Fall erfunden oder die
Datei aufgeraeumt wurde. Das ist genau der Verlust, der 0067 zwei Tage gekostet hat -- und
der Grund, warum Paket 0086 eine andere Herkunftsangabe in demselben Kopf berichtigt.

Der Vorschlag dazu liegt als **0095** daneben, mit der Bitte, ihn wie 0089 in 0086
einzuschmelzen statt ihn einzeln einzuplanen.

## Wonach ich gesucht und nichts gefunden habe

* **Ein uebernommener Sollwert.** Kein Fall der Tabelle traegt einen Wert, der aus einem
  Lauf stammen koennte: Alle acht Sollwerte sind entweder ein Dateiname, der im Satz
  objektiv der naechstgelegene ist, oder die Leermeldung. Ich habe die beiden gemessenen
  Formen und die `static_assert`-Form gegen ihre Quellzeilen gehalten -- wortgleich.
* **Eine gesenkte Schwelle in der Versionsgeschichte.** Der Diff gegen `f27dd39` enthaelt
  keine geloeschte Zusicherung, keine geaenderte Zahl und kein neues Ausnahmemuster.
  `ZIFFERN_MINDESTENS`, `ENDUNGEN`, `GESPERRTE_ORDNER` und `ist_pfadzeichen` sind
  unveraendert.
* **Eine ungeprueft gebliebene Wirkungskette.** Die drei Saetze der neuen Regel -- wortweise
  nach links, naechstgelegener gewinnt, Satzanfang als Grenze -- haben je einen Mutanten
  bekommen und je einen Fall, der allein an ihm stirbt.
* **Ein falscher Fund durch die Verbreiterung.** Auf 12 Treffern im Vorhaben und 468 im
  ganzen Repo keiner in der Stichprobe.
* **Ein Ueberlauf an den Zeilenraendern.** Sanitizer ueber 472 Treffer, keine Meldung.
* **Eine Ruecklaufwirkung auf Bedingung 2.** `dateiname_davor` wird allein von `fund_ab`
  gerufen; Bedingung 2 benutzt `naechster_verweis`. Die Zahlen 24/19/8 sind vor und nach
  der Aenderung gleich.

Eine Sache bleibt ungemessen, und der Bauagent nennt sie selbst: Die Satzgrenze bricht auch
an einer Abkuerzung mit Punkt ab. Im heutigen Bestand kostet das nichts -- ich habe keine
Zeile gefunden, an der es etwas kostet -- aber die Aussage ist eine Annahme und kein
Messwert. Sie steht im Kopfkommentar als solche, und das ist die richtige Behandlung.
