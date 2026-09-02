---
id: 0016-schreiber-ursachenkette
rolle: kernbauer
status: gebaut
haengt_an: [0008-kern-zustand-310-felder]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schreiber.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schreiber.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schreiber_probe.cpp]
abnahme: Die sechs Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# `kern::schreiber` — der einzige Schreibweg, und die Kette, die dabei entsteht

Vorgaben: `technik.md` T18, T38, T39, T19; dazu T9, T15, T17, T4, T2. ADR 0011 für die
Sprache — `technik.md` sagt an zehn Stellen weiter Rust, das ist bekannt und gehört
Paket 0011; **für den Bau gilt der ADR, nicht der Vorgabentext.**

Der `Schreiber` ist der Kasten, an dem drei Zusagen des Produkts hängen, und keine davon
ist eine Fleißaufgabe: dass jede Größe je Runde **genau einmal** geschrieben wird (T18),
dass es acht rundenübergreifende Rückkopplungskanäle gibt und nicht neun (T18), und dass
die Reihenfolge der sechs Rundenschritte zyklenfrei ist (T39). Alle drei sind hier
Eigenschaften des Codes oder gar nicht.

## Warum dieses Paket jetzt kommt

Nach `technik.md` Abschnitt 13 ist die Reihenfolge im Kasten `kern`: Zustand, Festkomma,
Zufall, Prüfsumme, **Schreiber mit T18/T38/T39**. Festkomma und Prüfsumme stehen, Zustand
und Zufall sind eingeplant. Der andere Weg nach 0008 — `kern::werte`, Paket 0002 — ist am
2026-09-02 blockiert worden, weil T5 Klasse 2 laufende und konstante Preise mischt und
die Auflösung T50 berühren kann. Der `Schreiber` hängt am `Zustand` und **nicht** an den
Werten; er ist damit der Kernkasten, der ohne die offene Entwurfsfrage vorangeht.

## Was du baust

**Bau gegen `daten/adressen.md` und gegen `kern/include/kern/zustand.hpp` aus Paket
0008**, nicht gegen die Prosa von T15. Weicht eines vom anderen ab, ist das ein Befund
für dein Logbuch und keine Gelegenheit, es still zu glätten.

1. **`Schreiber::setze(adresse, wert, ursache, verzoegerung, beitrag)` als einziger
   Schreibweg** (T18). Die Felder von `Zustand` sind ausserhalb des Kerns nicht
   schreibbar, innerhalb schreibt niemand direkt. Jeder Aufruf hängt einen
   `Ursachensatz` an, mit genau den sieben Feldern aus der Tabelle in T18: `runde`,
   `ziel` (Adresse nach T17), `alt`, `neu` (beide in der Skala der Größe), `ursache`,
   `verzoegerung` (Runden zwischen Ursache und Wirkung), `beitrag` (Anteil dieser Ursache
   an der Änderung, in Promille).
2. **`ursache` ist eine geschlossene Aufzählung** mit genau den sechs Formen aus T18:
   `Aktion{nr}`, `Instrument{land, instr}`, `Gegenkraft{art}`, `Markträumung{sektor}`,
   `Vortrag{adresse}`, `Jahrgang`. Keine siebte, kein Freitext — eine Ursache, die sich
   nicht benennen lässt, ist eine, die niemand später zuordnen kann.
3. **Das Bitfeld über alle 310 Adressen, und der zweite Schreibzugriff ist ein harter
   Fehler** (T18), kein überschreibender Wert. Das ist die billigste Art, die Zusage über
   acht Rückkopplungskanäle prüfbar zu machen: Eine Rückkopplung innerhalb der Runde
   erzeugt zwangsläufig einen zweiten Schreibzugriff und stirbt hier, statt als neunter
   Kanal unbemerkt zu entstehen.
4. **Eine Adresse, die sich nicht ändert, wird trotzdem geschrieben**, mit der Ursache
   `Vortrag` (T18). „Unverändert" ist eine Aussage und keine Lücke — wer das weglässt,
   macht aus einer Aussage ein Schweigen.
5. **Zwei Lesezugriffe, und der falsche stirbt sofort** (T39). `lies_alt(adresse)` gibt
   den Wert am Ende der Vorrunde und ist immer verfügbar; `lies_neu(adresse)` gibt den
   Wert dieser Runde und **bricht hart ab, wenn die Adresse in dieser Runde noch nicht
   geschrieben ist**. Kein stiller Rückgriff auf `alt`. Der stille Rückgriff wäre die
   gefährlichere Bequemlichkeit: Er macht das Ergebnis von der Reihenfolge der sechs
   Schritte abhängig, ohne dass irgendwo steht, dass es das tut. Der `Schreiber` hält
   dafür den Zustand der Vorrunde (`alt`, unveränderlich) und den entstehenden (`neu`).
6. **Die Sollmaske je Modus und die zweiseitige Prüfung am Rundenende** (T38). Der Modus
   (`spielmodus` | `weltlauf`) ist Argument, **nicht** Feld des Zustands — er wäre ein
   311. Feld. Am Rundenende prüft der `Schreiber` beides: jede Adresse der Maske genau
   einmal geschrieben, **und** keine Adresse ausserhalb der Maske berührt. Beides ist ein
   harter Fehler, kein Bericht. Die Maske `weltlauf` umfasst 175 Adressen nach der
   Blocktabelle in T38 (108 + 22 + 40 + 2 + 3), die Maske `spielmodus` alle 310. Die
   Blockzuordnung schreibst du aus T38 ab, statt sie zu bilden.
7. **Die Kette gehört nicht in den Zustand** (T19). Der `Schreiber` gibt die Kette der
   Runde heraus; `Zustand` bleibt bei 310 Feldern und 2.480 Byte. Die Aufnahmekapazität
   je Runde ist fest; **wird sie erreicht, ist das ein harter Fehler und keine stille
   Kürzung** — eine gekürzte Kette wäre eine Lüge gegenüber dem Käufer.

## Was du nicht baust

- **Den Rundenablauf.** Welche sechs Schritte in welcher Reihenfolge laufen und wer
  `setze` aufruft, ist `kern::schritt` und ein späteres Paket. Du baust den Weg, nicht
  den Gang.
- **Die abgeleiteten Größen** aus T48. Das ist `kern::werte`, Paket 0002, und blockiert.
  Dein Modul kennt Adressen und Werte, keine Bewertungsformel.
- **Den `Verlauf`.** T19 sagt, die Sitzung sammelt die Ketten; die Sitzung ist nicht im
  Kasten `kern`.
- **Die Prüfsumme.** Sie steht in `kern::pruefsumme` (Paket 0013, `fertig`). Brauchst du
  eine, rufst du sie auf.

## Abnahme

Sechs Bedingungen. Fünf sind mit `Read` und `Grep` prüfbar, die sechste über den
Übersetzungslauf (`befunde/uebersetzung-<datum>.md`).

1. **`Ursachensatz` trägt genau die sieben Felder aus der Tabelle in T18**, unter diesen
   Namen, und `ursache` genau die sechs Formen. Der Prüfer legt die Tabelle daneben und
   zählt ab; ein achtes Feld oder eine siebte Form ist ein Befund, auch wenn es nützlich
   wäre.
2. **Der zweite Schreibzugriff bricht ab.** Eine Probe schreibt dieselbe Adresse zweimal
   in derselben Runde und erwartet den Abbruch, mit ausgeschriebener Adresse. Ebenso
   bricht `lies_neu` auf einer in dieser Runde noch nicht geschriebenen Adresse ab (T39).
   Beide Proben stehen als `ctest`-Eintrag; der Übersetzungslauf belegt, dass sie
   wirklich laufen.
3. **`lies_alt` liefert nach einem `setze` auf dieselbe Adresse weiter den alten Wert.**
   Eine Probe mit zwei ausgeschriebenen Zahlen zeigt das. Ohne diese Bedingung wäre ein
   `Schreiber`, der `alt` und `neu` auf denselben Speicher legt, nicht zu bemerken — und
   das ist genau der Fehler, den T39 ausschliesst.
4. **Die Maskenprüfung ist zweiseitig und beide Seiten sind belegt.** Eine Probe lässt
   eine Adresse der Maske ungeschrieben und erwartet den Abbruch; eine zweite schreibt
   eine Adresse ausserhalb der Maske und erwartet den Abbruch. Die Maskengröße steht als
   ausgeschriebene Zahl in der Datei: **175** für `weltlauf`, **310** für `spielmodus`,
   und ein `static_assert` rechnet `175 + 135 = 310` nach.
5. **Die volle Runde geht auf.** Eine Probe schreibt alle 310 Adressen im `spielmodus`
   genau einmal, davon mindestens eine mit Ursache `Vortrag`, und die Rundenendprüfung
   besteht. Die Kette der Runde hat danach genau 310 Einträge — ausgeschrieben als
   Erwartungswert, nicht als Zählschleife über den eigenen Behälter.
6. **Kein Gleitkomma (T4), keine Fremdabhängigkeit (T2), keine streuenden Behälter
   (T9).** `grep -rnE 'float|double' kern/src/schreiber.cpp kern/include/kern/schreiber.hpp`
   liefert nichts, und die Kette liegt in einem Behälter mit fester Reihenfolge.

## Was ausdrücklich kein Befund ist

- **Wie das Bitfeld gespeichert ist** — `std::bitset<310>`, fünf `uint64_t` oder ein
  `std::array<bool, 310>`: `specs/` schweigt dazu, also ist die Entscheidung des
  Bauagenten gültig, solange die Reihenfolge fest ist.
- **Wie der harte Fehler aussieht.** Wurf oder Abbruch, beides erfüllt T18 und T39. Paket
  0004 hat sich für den Wurf entschieden, weil eine Probe ihn fangen kann; folge dem,
  wenn du keinen Grund für etwas anderes hast, aber es ist keine Bedingung.
- **Die feste Aufnahmekapazität der Kette in Zahlen.** T19 verlangt, dass sie fest ist
  und ihr Erreichen ein harter Fehler; welche Zahl es ist, sagt `specs/` nicht. Schreib
  sie hin und begründe sie in einem Satz.

## Rückläufe

0.
