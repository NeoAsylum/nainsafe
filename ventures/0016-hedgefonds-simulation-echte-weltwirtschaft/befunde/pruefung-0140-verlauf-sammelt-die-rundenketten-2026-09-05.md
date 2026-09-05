---
typ: pruefung
paket: 0140-verlauf-sammelt-die-rundenketten
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle vier Abnahmebedingungen einzeln und mechanisch an einem frischen Baum aus `git archive HEAD` -- Bedingung 1 und 2 zusaetzlich gegen zwei eigene Mutanten, die den Kasten an genau der Stelle verletzen, die die Bedingung behauptet, und die beide rot werden; Bedingung 3 als Zeilenvergleich der drei Zustandsproben zwischen dem Baum mit und dem Baum ohne die drei neuen Dateien; Bedingung 4 ueber vier Bauwege (Kern allein und Arbeitsbereich, je beide Profile), dazu eine eigene Probe mit acht Faellen, die die Paketprobe nicht faehrt.
befunde: 3
---

# Pruefung `0140-verlauf-sammelt-die-rundenketten`

## Woran gemessen wurde

Stand `c19e388` (HEAD am 2026-09-05), ausgepackt mit
`git archive HEAD ventures/0016-… specs decisions` in einen Wegwerfbaum unter `$TMPDIR`.
`g++ 15.2.0`, `cmake 4.2.3`. Der Arbeitsbaum ist unter `kern/` gegen `HEAD` unveraendert
(`git status --porcelain -- …/kern/` leer), gemessen wurde also derselbe Inhalt, der
eingecheckt ist.

Vier Bauwege, jeder `cmake -S … -B …`, `cmake --build`, `ctest`, alle Code 0:

| Bauweg | Profil | ctest-Eintraege |
|---|---|---:|
| Kern allein | `FABRIK_SANITIZER=ON` | 11 bestanden |
| Kern allein | `FABRIK_SANITIZER=OFF` | 11 bestanden |
| Arbeitsbereich | `FABRIK_SANITIZER=ON` | 17 bestanden |
| Arbeitsbereich | `FABRIK_SANITIZER=OFF` | 17 bestanden |

## Bedingung 1 -- der Verlauf gibt heraus, was er aufgenommen hat

**Erfuellt.** `verlauf_probe` faehrt vier Runden ueber `kern::schritt::schritt` im
`weltlauf`, nimmt je Runde die gelieferte Kette auf und vergleicht sie danach Glied fuer
Glied ueber alle sieben Felder aus T18. Ausgabe im Profil `ON`:

```
  Runde 1: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 2: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 3: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 4: 175 Glieder, zeichengleich ja, fremde Glieder 0
  nach 4 Runden: 700 Glieder im Verlauf, Zustandspruefsumme 0a31f624003d031b
```

175 ist die Sollmaskengroesse des `weltlauf` nach T38 (`108 + 22 + 40 + 2 + 3`); die Probe
holt sie aus `sollmaskengroesse(Modus::Weltlauf)` und nicht aus einer abgeschriebenen Zahl.
Von Hand nachgerechnet: `4 × 175 = 700`, und `glieder()` meldet 700.

**Nicht geglaubt, sondern mutiert.** Ein Vergleich, der immer „ja" sagt, sieht von einem
richtigen nicht zu unterscheiden aus. Ich habe `src/verlauf.cpp` allein an der
Aufrufstelle mutiert -- `-include kern/verlauf.hpp -include <makro>`, damit die Definition
im Kopf unberuehrt bleibt -- und gegen das **unveraenderte** Probenobjekt gebunden:

*Mutant C, `#define eintrag(nummer) eintrag(0)`* -- `aufnehmen` legt jedes Glied als das
erste ab. Ergebnis: vier Fehlschlaege, `zeichengleich NEIN` in allen vier Runden.
Die Bedingung ist also gedeckt.

Bemerkenswert dabei: `fremde Glieder` blieb unter Mutant C bei **0**. Die Zaehlung der
fremden Glieder ist damit kein Nachweis der Zuordnung, sondern nur ein Nachweis gegen
einen Rundenversatz; getragen wird Bedingung 1 vom Kettenvergleich. Beides ist da, die
Probe verlaesst sich nicht auf das schwaechere allein.

## Bedingung 2 -- die Aufnahmekapazitaet je Runde (die tragende)

**Erfuellt, beide Seiten gemessen.**

```
  an der Grenze: Runde 7 mit 310 Gliedern aufgenommen, 0 abweichend, kein Abbruch
  eines darueber: Abbruch mit "kern::verlauf -- die Kette der Runde 7 ist voll: die
  Aufnahmekapazitaet je Runde betraegt 310 Glieder (T19). Ein weiteres Glied waere eine
  stille Kuerzung."
  danach unveraendert: 310 Glieder in Runde 7
```

Die Meldung nennt die Runde (7) und die Kapazitaet (310), wie verlangt. Der Abbruch ist
keine halbe Aufnahme: Kette und Gesamtzahl stehen danach unveraendert bei 310.

**Der Fehler aus T19 ist ausgeschlossen, und zwar gemessen.** Ein Verlauf, der die
ueberzaehlige Kette wegwirft und Code 0 meldet, faellt hier durch: Der Lauf endet mit
einer geworfenen `std::domain_error`, und ohne sie wird `PRUEFE(geworfen)` rot.

**Die doppelt gehaltene Schranke haelt die Probe auseinander.** `kern::schreiber::Kette`
traegt dieselbe Grenze von 310 und bricht ebenfalls ab, kennt aber keine Rundennummer.
Faellt die aeussere Pruefung weg, tritt die innere an ihre Stelle -- und ohne eine
Gegenprobe darauf bliebe die Probe gruen. Nachgemessen:

*Mutant A, `#define GLIEDER_JE_RUNDE (::kern::verlauf::GLIEDER_JE_RUNDE + 1)`* -- die
aeussere Schranke liegt um eins zu hoch, also greift die innere. Ergebnis: vier
Fehlschlaege, darunter beide Zeilen, auf die es ankommt --
`enthaelt(…, "kern::verlauf")` und `!enthaelt(…, "kern::schreiber")`. Abgedruckt hat der
Mutant `kern::schreiber -- die Kette dieser Runde ist voll`. Die Gegenprobe ist also
scharf und keine Zierde.

**Zusaetzlich der Weg, den die Paketprobe nicht faehrt.** Die Paketprobe erreicht die
Grenze ueber `anhaengen`; ich habe sie ueber `aufnehmen` mit einer Kette der Laenge 310
erreicht, zwanzigmal hintereinander: 6.200 Glieder aufgenommen, jede der zwanzig Ketten
zeichengleich mit der gegebenen, kein Abbruch. `20 × 310 = 6.200`, von Hand
nachgerechnet und so gemeldet.

Der `spielmodus` -- der einzige Modus, in dem eine echte Rundenkette die 310 wirklich
erreicht -- ist im Kern noch nicht gebaut; `schritt` bricht dort mit eigener Meldung ab.
Die volle Kette musste deshalb gestellt werden. Das ist kein Mangel dieses Pakets, aber
es heisst, dass die Grenze bis heute nur synthetisch erreichbar ist.

## Bedingung 3 -- der Zustand bleibt unberuehrt

**Erfuellt.**

*Nicht angefasst:* `kern/include/kern/zustand.hpp` zuletzt in `c30acc5`
(testentwickler, 0111), `kern/src/zustand.cpp` zuletzt in `de7c991` (testentwickler,
0044). Beides fremde Pakete und aelter als dieser Lauf.

*Gleiche Zahl vor und nach:* Ich habe denselben Baum ein zweites Mal ausgepackt, die
drei Dateien dieses Pakets entfernt und beide Baeume mit `FABRIK_SANITIZER=ON`
uebersetzt. Die Ausgaben von `schritt_probe`, `zustand_probe` und
`zustandsausgabe_probe` -- darin die Pruefsummen -- sind zwischen beiden Baeumen
zeilengleich (`diff` je Code 0). Bezugsstand ist `c19e388` ohne die drei Dateien.

## Bedingung 4 -- beide Profile gruen, und der Zuwachs ist genau eine Probe

**Erfuellt.** Die vier Bauwege oben, alle Code 0. Der Zuwachs an ctest-Eintraegen im
Alleinbau ist 1: Der Baum ohne die drei Dateien fuehrt zehn Dateien unter `kern/test/`,
der Baum mit ihnen elf, und die elfte ist `verlauf_probe`. Unabhaengig gegengezaehlt am
Schlussriegel, der uebersetzende Ziele statt Tests zaehlt: `ON` 13 gegen 12 ohne, `OFF`
12 gegen 11 ohne -- in beiden Profilen genau ein Ziel mehr.

Der Sperrebindungsriegel meldet beim Konfigurieren „9 Kernquelle(n) und 11 Probe(n)
geprueft"; die neue Quelle und die neue Probe sind darin enthalten, beide binden
`kern/sperre.hpp` als letzten `#include`. Belegstellen- und Bezeichnerriegel laufen im
Arbeitsbereich in beiden Profilen gruen ueber die neuen Dateien.

## Wonach ich sonst gesucht habe

**Determinismus.** Kein Gleitkomma, kein `unordered_*`, kein `chrono`, kein `rand`, kein
`reinterpret_cast`, kein `uintptr_t`, kein `getenv`, kein `__DATE__`, keine Zuteilung --
Mustervergleich ueber alle drei Dateien, null Treffer. Der Kasten haelt zwei
`std::array` fester Groesse und laeuft nur ueber Indizes; `kette_der_runde` sucht
aufsteigend ueber die belegten Plaetze. Gemessen: die Ausgabe von `verlauf_probe` ist
zwischen `FABRIK_SANITIZER=ON` und `OFF` zeilengleich (`diff` Code 0).

**Rueckkopplung.** Der Verlauf rechnet nichts und speist nichts zurueck; es gibt keinen
Weg heraus ausser Lesen, kein Loeschen, kein Zuruecksetzen. Beide Schranken sind harte
Abbrueche. Von den beiden ist nur eine hergeleitet -- siehe Befund 1.

**Raender.** Eigene Probe, acht Faelle, im Profil `ON` mit Adressen- und
Verhaltens-Sanitizer, alle bestanden und ohne eine einzige Sanitizer-Diagnose:

- Rundennummer `I64_MAX` wird aufgenommen; dieselbe noch einmal bricht ab, ohne dass
  irgendwo `runde + 1` gerechnet wuerde. `I64_MIN` bricht ab.
- Runde 0 und Runde −1 brechen ab, der Verlauf bleibt bei null Runden.
- Eine Kette aus demselben Verlauf noch einmal aufnehmen
  (`verlauf.aufnehmen(2, verlauf.kette(0))`) -- kein Selbstbezug, die Kopie kommt
  vollstaendig und zeichengleich an.
- Kopie des Verlaufs: traegt dieselben Runden und Glieder und haelt eigenen Speicher.
- Luecken in der Rundenfolge (2, 5, 6, 40, 41): jede wird unter ihrer Nummer gefunden,
  eine Nummer in der Luecke bricht ab.
- Groessen nachgemessen: `sizeof(Ursachensatz) = 56`, `sizeof(Kette) = 17.368`,
  `sizeof(Verlauf) = 347.528` Byte = 339 KiB. Das deckt die Angabe „rund ein Drittel
  Megabyte" im Kopf.
- Keine Division und keine Multiplikation in der Zustandsfortschreibung dieses Kastens;
  `glieder()` summiert hoechstens `20 × 310 = 6.200` in einem `std::size_t`.

**Was der Kasten ausgibt.** Uebersicht (`runden`, `glieder`), Detail (`rundennummer`,
`kette`, `kette_der_runde`) sind vollstaendig: Aus den Zugriffen allein laesst sich jede
aufgenommene Kette Glied fuer Glied nachvollziehen und gegen die von `schritt` gelieferte
halten -- genau das tut Bedingung 1. Eine Diff-Ebene fehlt, sie ist aber ausdruecklich
Gegenstand von `0091-diff-ursachenkette-nach-t20` und nicht dieses Pakets.

---

# Die drei Befunde

Keiner verletzt eine der vier Abnahmebedingungen; deshalb steht das Urteil auf
`geprueft`. Befund 1 verletzt eine Vorgabe aus `specs/` und wird ein eigenes Paket,
Befund 2 und 3 gehoeren in bestehende.

## Befund 1 -- `RUNDEN_KAPAZITAET` ist die Partielaenge R als Konstante des Codes, und T40 verbietet genau das

**Der Sachverhalt.** `kern/include/kern/verlauf.hpp` fuehrt
`inline constexpr std::size_t RUNDEN_KAPAZITAET = 20;` und begruendet die Zahl im selben
Kopf damit, dass sie die Partielaenge R aus `spiel.md` sei. Wird sie erreicht, bricht
`beginne_runde` hart ab.

**Die Vorgabe.** `specs/…/technik.md`, T40, erster Satz: *Die Partielänge R ist eine
Größe des Jahrgangs, keine Konstante des Codes, und keine aus ihr abgeleitete Zahl steht
als Literal irgendwo.* T40 rechnet ausdruecklich mit anderen Werten -- seine Tabelle
fuehrt jede abgeleitete Groesse fuer `R = 24` vor -- und zieht die Wand erst bei
`R > 26`, dort nachgerechnet und begruendet. T19, die Vorgabe dieses Pakets, verlangt
eine feste Aufnahmekapazitaet **je Runde**; eine Kapazitaet ueber die Partie verlangt sie
nicht.

**Wie man den Fehler erzeugt.** Ein Jahrgang mit `stuetzstellen = 25` ergibt nach T40
`R = 24`, und 24 liegt innerhalb der Wand `R ≤ 26`. Eine Sitzung, die diesen Jahrgang
spielt und die Ketten nach T19 sammelt, bricht in Runde 21 ab:

```
kern::verlauf -- der Verlauf ist voll: er nimmt 20 Runden auf, und die Runde 21 waere
die naechste. Eine stille Kuerzung gibt es nicht (T19).
```

Gemessen mit einer eigenen Probe im Profil `ON`, zweimal: einmal ueber `aufnehmen` mit
einer vollen Kette, einmal ueber eine gelaufene Partie im `weltlauf`, deren
Rundennummern aus `partie.runde` kommen. Beide Male 20 aufgenommene Runden, Abbruch in
Runde 21.

**Derselbe Abbruch trifft die Auflage des Bruchtesters.** technik.md nennt unter Mass 6
und `spiel.md` im Abschnitt zur Beschraenktheit einen Lauf ueber **200 Runden ohne
Spieler**. Gemessen: 20 von 200 Runden aufgenommen, dann Abbruch. Dass der Pruefstand die
Ketten nach T19 wegwerfen *darf*, wenn er nur Ergebnisse zaehlt, stimmt -- der Kopf des
Kastens beruft sich darauf. T19 weist diesen Lauf aber nicht selbst als kettenfrei aus;
es erlaubt dem Pruefstand nur, auf die Ketten zu verzichten. Das traegt den Verzicht,
aber es traegt nicht die Bindung der Kapazitaet an R.

**Warum das mehr ist als eine Zahl.** Der Fehler zeigt in die sichere Richtung -- er
bricht laut ab und kuerzt nicht still, und deshalb ist er kein `zurueck`. Teuer ist er
aus dem Grund, den T40 selbst nennt: Nicht die falsche Zahl kostet, sondern ihre
Verbreitung. `0091-diff-ursachenkette-nach-t20` arbeitet als naechstes auf denselben drei
Dateien und wird ueber den Verlauf laufen; jede Stelle, die sich dann auf zwanzig Plaetze
verlaesst, ist eine zweite. Solange es eine einzige Zeile ist, ist sie billig.

Der Vorschlag dazu steht als `0144-rundenkapazitaet-des-verlaufs-nicht-an-r`.

## Befund 2 -- die Speicherschranke im Kopf greift fuer keinen zulaessigen Wert von R

**Der Sachverhalt.** Der Kopf schreibt, die Schranke auf die Groesse stehe als
Zusicherung und nicht als Kommentar, und wer die Kapazitaeten hochsetze, ohne die Folge
zu bedenken, bekomme einen roten Bau. Die Zusicherung lautet
`sizeof(Verlauf) < 512 × 1024`.

**Nachgerechnet.** `sizeof(Verlauf) = N × 17.376 + 8` Byte, mit `N =
RUNDEN_KAPAZITAET`; gemessen fuer `N = 20`: 347.528 Byte, was die Formel trifft. Die
Zusicherung reisst erstmals bei `N = 31` (538.664 Byte); bei `N = 30` sind es 521.288
Byte und der Bau bleibt gruen. `GLIEDER_JE_RUNDE` ist nicht heraufsetzbar, es ist aus
`kern::schreiber::KETTE_KAPAZITAET` abgeleitet.

Damit gilt: Fuer **jedes** R, das T40 zulaesst (bis 26), meldet die Schranke nichts. Sie
faengt nur einen Sprung, den niemand vorhat. Die Aussage im Kopf ist nicht falsch, aber
sie beschreibt einen Schutz, der an der einzigen Stelle, an der man ihn braeuchte,
schweigt.

Dazu, kleiner: Von den drei `static_assert` im Kopf sind zwei durch die Bauart wahr und
koennen nicht reissen. `GLIEDER_JE_RUNDE == zustand::FELDER` ist eine Umschreibung von
`KETTE_KAPAZITAET = FELDER` aus `kern/include/kern/schreiber.hpp`, und
`sizeof(Verlauf) >= RUNDEN_KAPAZITAET * sizeof(Kette)` folgt daraus, dass der Verlauf
sein Feld als Mitglied haelt. Beide sind als Dokumentation nuetzlich; als Riegel zaehlen
sie nicht mit.

**Kein eigenes Paket.** Die Zahl wird in dem Moment richtig, in dem Befund 1 abgearbeitet
ist -- wer die Kapazitaet vom Jahrgang nimmt, muss die Schranke ohnehin neu stellen. Der
Befund gehoert deshalb in die Abnahme von `0144` und steht dort.

## Befund 3 -- `aufnehmen` prueft nicht, ob die Glieder die Runde tragen, unter der sie abgelegt werden

**Der Sachverhalt.** `aufnehmen(runde, rundenkette)` legt die Kette unter `runde` ab, ohne
je zu vergleichen, ob die Glieder in ihrem Feld `runde` nach T18 dieselbe Nummer tragen.

**Wie man es sieht.** Eigene Probe, Profil `ON`: Nach `verlauf.aufnehmen(3, kette)` haengt
`verlauf.anhaengen` einen Ursachensatz mit `runde = 99` an, und er landet ungeprueft als
viertes Glied der Runde 3. Ebenso nimmt `aufnehmen(6, kette_der_runde_5)` die fremde Kette
widerspruchslos entgegen.

**Warum es zaehlt.** Die Paketprobe fuehrt „jedes Glied traegt die Runde, unter der es
steht" als Zuordnungsnachweis. Der haelt heute, aber er haelt, weil `schritt` die Nummer
richtig setzt -- nicht, weil der Verlauf sie prueft. Der Kasten sichert seine
Rundenordnung sonst hart zu (aufsteigend, keine Wiederholung, keine Runde vor der
ersten); die eine Pruefung, die eine falsche Zuordnung wirklich faenge, fehlt, und sie
kostet einen Vergleich je Glied.

**Kein eigenes Paket.** `0091-diff-ursachenkette-nach-t20` haengt an diesem hier, haelt
dieselben drei Dateien und loest die Ketten rueckwaerts ueber Runden auf -- es ist der
erste Leser, dem eine falsche Zuordnung wehtut, und die Pruefung gehoert in seine Abnahme
statt in ein drittes Paket auf denselben Dateien.

---

## Zwei Beobachtungen ausserhalb des Pakets

**Die drei Dateien stehen nicht im Commit dieses Pakets.** `c19e388` traegt den Betreff
`kernbauer: 0140-verlauf-sammelt-die-rundenketten (4 Dateien)` und aendert
`notizen/kernbauer.md`, die Paketdatei und die zwei Dateien unter `befunde/messung-0140/`.
`verlauf.hpp`, `verlauf.cpp` und `verlauf_probe.cpp` sind mit `802706d`
(`testentwickler: 0136-…`) in den Bestand gekommen, also mit dem Commit eines fremden
Laufs. Der Inhalt an `HEAD` stimmt, gemessen wurde er -- die Zuordnung von Commit zu
Paket stimmt nicht. Das ist der Sachverhalt, den `0131-baulauf-commit-nur-paketdateien`
beschreibt; er steht auf `blockiert`. Kein neues Paket, ein weiterer Beleg fuer das
vorhandene.

**Der `spielmodus` fehlt im Kern.** `kern::schritt::schritt` bricht mit `Modus::Spielmodus`
ab, weil Schritt 2 und 6 kein Paket haben. Das ist bekannt und benannt; es steht hier nur,
weil es die einzige Zusicherung des Verlaufs betrifft, die sich heute nicht an einer
echten Runde messen laesst: Erst im `spielmodus` liegt eine Rundenkette auf der Kapazitaet
von 310. Bis dahin bleibt Bedingung 2 an einer gestellten Kette gemessen.
