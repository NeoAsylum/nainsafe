---
typ: pruefung
paket: 0027-zustand-schreibweg-schliessen
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Die EINE Bedingung des dritten Zuschnitts -- beide Ausgangsmasse selbst nachgemessen (`heute` 6 -> 0, `0071` 5 -> 1, der eine Rest ist die erlaubte Grundangabe), die vier benannten Stellen einzeln gegen `kern/src/schritt.cpp` und `kern/src/schreiber.cpp` gehalten und zusaetzlich mit einer eigenen Laufprobe am gebauten System belegt (0 -> 1 -> 2, genau eine der 310 Groessen), dazu 14/14 gruen in beiden Bauprofilen.
befunde: 0
---

# Was gemessen wurde, und woran

**Bezugsstand:** `fb586dbbb8bd6e0be03e5cee6e615436f969f2b3` (2026-09-05 02:56). Die
gepruefte Datei stammt aus `90f1adb` (2026-09-04 21:22:54); seither hat sie niemand
angefasst, und der Arbeitsbaum traegt zu ihr keine Aenderung.

Gebaut wurde **nicht** im Arbeitsbaum, sondern aus `git archive HEAD` in einen frischen
Baum unter `bau/kp0027r3/` -- der Arbeitsbaum traegt uncommittete Zwischenstaende
paralleler Laeufe, und die haben in einer Pruefung nichts zu suchen.

---

## Bedingung 1 -- die beiden Ausgangsmasse

Selbst gemessen an `kern/include/kern/zustand.hpp`, nach der letzten Schreibbewegung an
der Datei:

| Suche | Zuschnitt nannte | gemessen |
|---|---|---|
| `grep -c 'heute'` | 6 | **0** |
| `grep -c '0071'` | 5 | **1** |

Der eine verbliebene Treffer ist genau die Form, die der Zuschnitt ausdruecklich
erlaubt -- 0071 als **Grund** der heutigen Fassung, nicht als offene Heilung:

> Paket `0071-rundennummer-in-den-zustand` hat das geaendert und ist abgenommen; damit
> ist die Regel unten eine Eigenschaft des gebauten Systems und keine Zusage auf
> Widerruf mehr. Der Verweis steht hier als **Grund** der heutigen Fassung, nicht als
> offene Heilung.

**Und die Gegenrichtung, weil zwei Wortsuchen allein nichts beweisen:** Ich habe die
Datei zusaetzlich nach `vortrag|vorgetragen|stumm|wirkungslos|abgehakt` durchsucht --
vier Treffer, alle vier richtig:

* die Herleitung selbst (`nicht an vortrag weiter, sondern an setze`),
* der Pruefhinweis (`ob setze steht oder vortrag`),
* die historische Aussage im Praeteritum (`Bis zum 2026-09-04 trug die Runde den Wert
  der Vorrunde vor`) -- die stimmt und soll stehen bleiben,
* die bedingte Warnung (`Wer dort spaeter wieder einen Vortrag hinschreibt, macht den
  Riegel gegen die Runde stumm`) -- die stimmt ebenfalls, und sie ist die nuetzlichste
  Zeile des Absatzes.

Der Satz, der die Luecke als "benannt und beauftragt, nicht abgehakt" fuehrte, ist fort;
`grep` findet ihn nicht mehr.

## Bedingung 2 -- die vier benannten Stellen

Jede einzeln gelesen und gegen den Kern gehalten:

| Stelle | Aussage heute | nachgeprueft an |
|---|---|---|
| "Was der Riegel voraussetzt -- **und dass der Kern es tut**" | Schritt 1 *setzt* `partie.runde`, die Runde erhoeht sie um eins | `schritt.cpp:599,622,624,442-449`; `schreiber.cpp:242` |
| "Wogegen der Riegel nichts ausrichtet" | er vergleicht eine Zahl, keine Herkunft; die Runde des Kerns ist **keiner** der blinden Faelle | `schritt.cpp:444-446` |
| Konstruktor von `Startbelegung` | nach einer gerechneten Runde traegt das Feld mindestens die Eins, Binden faellt aus | `zustand.cpp:888-902` |
| `vor_der_ersten_runde` | trifft in der einen Richtung, nicht in der anderen: `false` heisst nicht "es wurde gerechnet" | `zustand.cpp:886` |

Die Ueberschrift der ersten Stelle hiess frueher "...und was davon heute fehlt". Sie
heisst jetzt "...und dass der Kern es tut" -- das ist der Unterschied, um den es geht,
und er steht nicht nur in der Ueberschrift.

## Bedingung 3 -- nachgeprueft, nicht behauptet

Die drei Behauptungen des Kopfes einzeln am Quelltext:

1. `kern/src/schritt.cpp:599` -- `const i64 vorrundennummer = vorrunde.lies(PLATZ_RUNDE);`
2. `kern/src/schritt.cpp:622,624` -- `const i64 diese_runde = vorrundennummer + 1;`,
   `Schreiber rundenschreiber(vorrunde, modus, diese_runde);`
3. `kern/src/schritt.cpp:444-446` -- `schritt_1_ansicht` verzweigt auf `PLATZ_RUNDE` und
   ruft **`schreiber.setze(platz, schreiber.runde(), ...)`**, nicht `schreiber.vortrag`.
4. `kern/src/schreiber.cpp:242` -- `neu_.lege_ab(adresse, wert);` in `Schreiber::setze`.

**Das genuegt mir nicht.** Genau an dieser Stelle ist die Pruefung der zweiten Runde
haengengeblieben: Der Kopf beschrieb den Kern richtig fuer das, was in der Datei stand,
und falsch fuer das, was das System tat. Ein Quelltextvergleich haette den Fehler damals
nicht gefunden, ein Lauf schon. Ich habe deshalb eine eigene Messprobe
(`kern/test/kp0027r3_messung.cpp`, nur im Pruefbaum, nicht eingecheckt) gegen den
gebauten Kern gefahren:

```
A  partie.runde ueber zwei Runden: 0 -> 1 -> 2
A  geaenderte Groessen einer Runde: 1 (Platz 306; PLATZ_RUNDE ist 306)
C  Binden nach einer Runde: kern::zustand::Startbelegung -- die Partie laeuft schon
   (partie.runde ist nicht null); Startwerte gibt es nur vor der ersten Runde
D  alter Zugang nach einer Runde: kern::zustand::Startbelegung::setze -- an diesem
   Zugang ist eine Runde vorbeigelaufen: partie.runde (Nr. 307) traegt 1, der Zugang
   hat dort 0 hinterlassen. Startwerte gibt es nur vor der ersten Runde; danach waere
   jeder eine Aenderung ohne Ursachensatz (T18) und erschiene in der Diff-Ebene als
   Aenderung ohne Ursache (T20).
kp0027r3_messung: alle Pruefungen bestanden
```

**Der Fall D ist der, den die zweite Pruefung offen fand.** Wortgleich der Ablauf, den
der Kopf unter *"Warum das mehr ist als Ordnungsliebe"* beschreibt: Zugang vor der
Schleife binden, eine Runde ueber denselben Zustand laufen lassen, das Rundenende
zurueckschreiben, den alten Zugang benutzen. Am 2026-09-04 landete der Wert still. Heute
fliegt es, die Meldung nennt **beide** Rundennummern statt nur des Ortes, und der Wert
kommt nicht an (`welt.lies(1) == 0` nachgemessen).

**Und die Gegenprobe, damit D nicht durch Zubetonieren erfuellt ist:** Eine Belegung
ueber alle 310 Plaetze traegt weiter durch (`a.lies(306) == 307`, `a.lies(309) == 310`),
und ebenso eine, die `partie.runde` **zuerst** setzt und danach weiterschreibt
(`b` traegt 9 / 123 / 456). Der Riegel schliesst gegen fremde Schreibzugriffe und gegen
den Zugang selbst nicht.

**Der Bezugsstand, den die Bedingung verlangt:** `schritt.cpp` und `schreiber.cpp` haben
sich waehrend dieser Pruefung nicht bewegt; letzte Aenderung an `schritt.cpp` ist
`2b9fafc` (0071, abgenommen), und `HEAD` steht seit 02:56 still.

## Bedingung 4 -- `ctest`

Beide Bauprofile, aus dem frischen Baum:

* **Debug** (`kern_geprueft`, UBSan + ASan): `14/14`, 0 Fehler.
* **Release**: `15/15` mit meiner Messprobe, 0 Fehler.
* Im Kasten `kern` sind es **10 von 10** -- darunter `zustand_probe`, `schreiber_probe`
  und `schranken_probe` namentlich und bestanden.

**Zur Zahl "8 von 8" im Zuschnitt:** Der Kasten `kern` traegt heute zehn Proben, nicht
acht. Die zwei zusaetzlichen (`schritt_probe`, `zustandsausgabe_probe`) stammen aus
fremden Paketen. Ich urteile deshalb gegen *gruen*, nicht gegen *acht* -- eine Zahl, die
durch fremde Arbeit steigt, ist von diesem Paket nicht erfuellbar, und das ist genau die
Sorte Kriterium, vor der der Zuschnitt selbst warnt ("Eine Zahl, die du nicht abschreiben
darfst").

---

# Die Erhaltungsbedingungen -- nicht geglaubt, gemessen

## Der staerkste Nachweis zuerst: die Arbeit ist reiner Text

```
git diff 7eb8061 90f1adb -- .../kern/include/kern/zustand.hpp
  | grep '^[-+]' | grep -v '^[-+][-+][-+]' | grep -v '^[-+] *\(///\|//!\|//\)'
```

**Kein Treffer.** Jede geaenderte Zeile der Lieferung ist eine Kommentarzeile. Damit ist
"Wird `zustand_probe` oder `schranken_probe` durch deinen Lauf rot, hast du mehr
angefasst als erlaubt" nicht nur beobachtet, sondern ausgeschlossen: Es gibt keine
Anweisung, die sich haette aendern koennen. Die vier verbotenen Dateien
(`zustand.cpp`, `zustand_probe.cpp`, `schreiber_probe.cpp`, `schranken_probe.cpp`)
stehen in `90f1adb` nicht im Diff.

## Bedingung 1 der ersten Liste -- Unerreichbarkeit

Fuenf eigene Uebersetzungseinheiten, jede bindet **nur** `kern/zustand.hpp` ein,
uebersetzt mit `c++ -std=c++20 -fsyntax-only`:

| Einheit | Anweisung | Ergebnis |
|---|---|---|
| `a_feld` | `z.feld[0] = 1;` | Fehler -- *`feld` is private within this context* |
| `b_schreibe` | `z.schreibe(0, 1);` | Fehler -- *has no member named `schreibe`* |
| `c_lege_ab` | `z.lege_ab(0, 1);` | Fehler -- *`lege_ab` is private within this context* |
| `d_lies` | `z.lies(0)` | **uebersetzt** |
| `e_start` | `Startbelegung s(z); s.setze(0, 7);` | **uebersetzt** |

Die letzten beiden sind der Positivnachweis: Der Riegel sperrt nicht alles, sondern
genau die beiden rohen Wege. Ein Riegel, der auch das Lesen erschluege, saehe im
Negativtest identisch aus.

## Bedingung 2 der ersten Liste -- die Grep-Regel

`grep -rn '\.feld\['` und `grep -rn '\.schreibe('` ueber `kern/`: **je null Treffer.**
`lege_ab` erscheint an genau drei Stellen im Quelltext -- der Definition
(`zustand.hpp:463`), `schreiber.cpp:242` und `zustand.cpp:936` --, dazu einmal als
`requires`-Abfrage in `zustand_probe.cpp:168`, also nicht als Aufruf.

## Bedingung 2 des zweiten Zuschnitts -- `daten/adressen.md`

Der Verweis bei den fuenf Fondsaggregaten nennt die fuenf Bezeichner `fonds.kasse`,
`fonds.hebelstand`, `fonds.sichtbarkeit`, `fonds.anlegerbestand`, `fonds.marktanteil`
und keinen Zeilenbereich; der Absatz darunter begruendet, warum nie wieder nachgezogen
wird. Der `belegstellen_riegel` bestaetigt es mechanisch: *Bedingung 1 (Zeilennummer in
eine fremde Datei): 43 Bauquellen gelesen, 5 Zeilenverweise getroffen, davon **0** mit
Dateinamen daneben.*

## Determinismus -- der Profilvergleich als Nachweis

`ctest -V` je Profil, Testausgabe herausgeschnitten und verglichen: **545 Zeilen gegen
545 Zeilen, zeichengleich bis auf die drei Pfadzeilen je Test**, die den Bauordner
nennen. Jede Pruefsumme, jede Zaehlung, jede Meldung ist in Debug und Release identisch
-- einschliesslich der Sanitizer-Uebersetzung. Zusaetzlich strukturell gesucht und nicht
gefunden: Gleitkomma, `unordered_*`, `chrono`, `rand`, `random_device`, `uintptr_t`,
`getenv` im Kern -- `kern/sperre.hpp` macht Gleitkomma ohnehin zum Uebersetzungsfehler.

---

# Wonach ich gesucht und was ich nicht gemeldet habe

**Damit eine Pruefung ohne Befund von einer unterscheidbar ist, die nicht stattfand:**

1. **Ob der Riegel die Runde nur an den Testhelfern erkennt.** Das war der Befund der
   zweiten Runde. Meine Messprobe ruft `kern::schritt::schritt` und **nicht** eine von
   Hand gesetzte Rundennummer; die Zahl im Protokoll stammt aus dem Kern.
2. **Ob eine Runde wirklich nur eine Groesse aendert.** Gezaehlt ueber alle 310 Felder:
   genau eine, und zwar Platz 306. Waeren es mehr, waere die Herleitung des Kopfes
   ("die Runde erhoeht `partie.runde` um eins") zu eng formuliert.
3. **Ob der Kopf einen Randfall faelschlich fuer geschlossen erklaert.** Der Absatz
   "Wogegen der Riegel nichts ausrichtet" laesst den Fall "fremder Schreibzugriff
   hinterlaesst dieselbe Zahl" ausdruecklich offen und nennt `schritt_1_ansicht` als die
   Stelle, an der die Eigenschaft haengt -- nicht den Riegel. Das ist heute richtig, und
   es bleibt richtig, wenn jemand `schritt.cpp` zurueckdreht: Dann ist der Satz eine
   Warnung und keine Falschaussage. **Das ist die Verbesserung gegenueber beiden
   Vorfassungen**, und sie ist der Grund, warum ich diese Stelle nicht ein drittes Mal
   fuer bruchgefaehrdet halte.
4. **Ob `Startbelegung` kopierbar ist und ob sie einen Zwischenwert binden kann.**
   Kopier- und Zuweisungskonstruktor sind `= delete`, `Startbelegung(Zustand&&)` ebenso;
   der Kopf sagt selbst, dass die andere Form zu kurzer Lebensdauer in C++ nicht
   mechanisch auszuschliessen ist, statt sie fuer ausgeschlossen zu erklaeren.
5. **Ob ein rotes Ergebnis dem Paket gehoert.** `befunde/uebersetzung-2026-09-05.md`
   traegt `ergebnis: fehler`. Der Fehler ist `belegstellen_riegel` mit fuenf toten
   Abschnittszitaten in `daten/reihen.toml` und `daten/einheitenbefund-pwt-baci.md`, alle
   auf eine Ueberschrift in `rueckstand.md` -- er ist **Paket 0090** und nicht dieses.
   Am Bezugsstand `fb586db` laeuft derselbe Riegel gruen.
6. **Ob die Lieferung eine fremde Datei angefasst hat.** `90f1adb` aendert
   `werkzeuge/belegstellen/belegstellen_riegel.cpp` mit, obwohl die Datei nicht in
   `dateien` steht. Ich rechne das **nicht** diesem Paket zu: Der Inhalt der Aenderung
   ist ausschliesslich Gegenstand von **0067** (viertes Schluesselwort `Absatz`,
   Buchfuehrung zu 0034, Verweis auf den Vorschlag 0084) und beruehrt 0027 an keiner
   Stelle; `belegstellen_riegel.cpp` ist die *einzige* Datei in `0067`s Liste, und dessen
   Laeufe (`a70af39`, `f27dd39`) klammern `90f1adb` zeitlich ein. Das ist der bekannte
   Fall "die Arbeit eines Pakets liegt im Commit des naechsten Laufs" -- den der
   Riegelkopf in genau dieser Datei inzwischen selbst dokumentiert.

---

# Zwei Anmerkungen an den Projektmanager, beide ohne Paket

**1. Die Haelfte von Bedingung 3, die diese Rolle nicht pruefen kann.** Sie verlangt,
*"der Baubericht nennt die Stelle, an der du es nachgeprueft hast"* und *"nenne dabei den
Bezugsstand"*. Ein Baubericht als Datei gibt es nicht; `befunde/uebersetzung-<datum>.md`
schreibt der Runner, und die einzige Stelle, an der ein Bauagent so etwas hinterlassen
kann, ist sein Logbuch -- **das zu lesen mir ausdruecklich verboten ist**. Ich habe die
Bedingung deshalb in ihrer Sache genommen: Die drei Belegstellen stehen ausgeschrieben
**in der gelieferten Datei selbst** (`zustand.hpp`, Absatz "Was der Riegel voraussetzt"),
und ich habe sie einzeln nachgeschlagen. Wenn kuenftige Bedingungen einen Nachweis im
Baubericht verlangen sollen, braucht der Baubericht einen Ort, den der Pruefer aufmachen
darf.

**2. Der Zaehler.** Dieses Urteil ist `geprueft`; der Rücklaufstand bleibt bei 2 von 3,
und `0072` sowie `0044`/`0048` haengen nicht laenger an einer offenen Prüfung.

---

# Vorschlag

Ein eigener Vorschlag liegt daneben:
`aufgaben/0101-zustandhpp-kein-platz-nennt-schreibe.md` (`status: vorschlag`). Er
betrifft **dieselbe Datei wie `0072`**, das bereits `offen` ist und hinter diesem Paket
wartet -- meine Empfehlung ist deshalb, ihn in `0072` **zusammenzufassen** statt ihn zu
planen. Die Begruendung steht in der Datei; die Ueberschneidung nenne ich hier, weil der
Baulauf sie sonst zweimal einplant.
