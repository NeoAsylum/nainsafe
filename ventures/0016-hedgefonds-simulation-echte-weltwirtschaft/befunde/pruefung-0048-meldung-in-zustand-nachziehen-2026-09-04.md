---
typ: pruefung
paket: 0048-meldung-in-zustand-nachziehen
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln mechanisch nachgestellt -- den Mustervergleich aus Bedingung 1 selbst ausgefuehrt, die Proben aus Bedingung 2 und 3 in drei eigenen Bauverzeichnissen ausserhalb des Repos gebaut und laufen lassen.
befunde: 0
---

# 0048 -- Der Meldungsbau in `kern/src/zustand.cpp` auf den Kopf umgestellt

## Was ich gebaut und ausgefuehrt habe

Drei Bauverzeichnisse, alle ausserhalb des Repos, keines im Baum:

| Verzeichnis | Quelle | Profil |
|---|---|---|
| `/tmp/claude-1000/pruef0048` | `kern/` | `RelWithDebInfo` |
| `/tmp/claude-1000/pruef0048dbg` | `kern/` | `Debug` |
| `/tmp/claude-1000/pruef0048all` | Arbeitsbereich (`.`) | `RelWithDebInfo` |

`FABRIK_SANITIZER` steht in `werkzeugkette.cmake:62` auf `ON`, also linken alle Proben
`kern_geprueft` mit `-fsanitize=undefined,address -fno-sanitize-recover=all`. Der
Meldungsbau des Riegels ist damit nicht nur gelaufen, sondern **unter ASan/UBSan**
gelaufen -- fuer einen Puffer fester Groesse der Nachweis, auf den es hier ankommt.

Kein Warnhinweis in einem der drei Bauten; ein Mustervergleich nach `warn` und `error`
ueber die Bauprotokolle bleibt leer bis auf die Zeile des Warnsatz-Schlussriegels.

## Bedingung 1 -- erfuellt

Aufruf, wortgleich aus dem Kriterium, aus dem Wurzelverzeichnis des Vorhabens:

```
$ grep -rn "class Meldung" kern/include kern/src
kern/include/kern/meldung.hpp:85:class Meldung {
```

**Genau eine Zeile, und sie steht im Kopf.** Statt dem leeren Rest zu glauben, habe ich
das Muster geweitet und ueber das ganze Vorhaben laufen lassen -- `class Meldung`,
`struct Meldung` und `Meldung {`, ueber alle `.cpp` und `.hpp`:

```
./kern/include/kern/meldung.hpp:85
./befunde/messung-0052/gegenprobe/kern/include/kern/meldung.hpp:85
./befunde/messung-0052/gegenprobe/kern/src/zustand.cpp:879
```

Die beiden weiteren Treffer sind die eingefrorene Abschrift des Baums aus meiner eigenen
Messung zu Paket 0052. Sie liegt unter `befunde/`, wo der Baulauf nicht sammelt
(`baulauf.py:116`), sie uebersetzt nicht mit, und sie liegt ausserhalb des Suchraums, den
Bedingung 1 nennt. Sie ist kein zweiter Meldungsbau, sondern ein Pruefstueck.

**Zum Anspruch, damit sei Bedingung 1 von Paket 0038 nachtraeglich erfuellt:** Er stimmt.
Der Projektmanager hat jene Bedingung am 2026-09-03 auf `kern/src/schreiber.cpp` und
`kern/src/schritt.cpp` verengt und dieses Paket ausdruecklich als den Ort der dritten
Fassung genannt. Beide Dateien sind trefferfrei, und die dritte Fassung ist fort.

**Was ich zusaetzlich gesucht habe, weil 0038 von „einem zweiten Puffer" sprach und nicht
von einer Klasse:** ein Mustervergleich nach `std::array<char`, `puffer` und `zeichen`
ueber `kern/src` und `kern/include`. Uebrig bleibt `struct Aufbau`
(`kern/src/zustand.cpp:465`). Das ist **kein** Meldungsbau: Er baut Adresstexte fuer den
Deckungslauf, ist `constexpr`, und er **bricht ab** statt abzuschneiden. Er stand vor
0038 da, liegt ausserhalb der verengten Bedingung und ist kein Befund.

## Bedingung 2 -- erfuellt

`zustand_probe` ist in **beiden** Profilen gruen. Die Meldungen des Riegels aus dem
Protokoll des Laufs, im Wortlaut (Umbrueche von mir, der Text ist je eine Zeile):

```
  Abbruch wie erwartet (Zeile 728): kern::zustand::Startbelegung -- die Partie laeuft
  schon (partie.runde ist nicht null); Startwerte gibt es nur vor der ersten Runde
  Abbruch wie erwartet (Zeile 729): [dieselbe Meldung]
Startwertzugang: vor Runde 1 offen, in Runde 12 verriegelt
  Abbruch wie erwartet (Zeile 773): kern::zustand::Startbelegung::setze -- an diesem
  Zugang ist eine Runde vorbeigelaufen: partie.runde (Nr. 307) traegt 7, der Zugang hat
  dort 0 hinterlassen. Startwerte gibt es nur vor der ersten Runde; danach waere jeder
  eine Aenderung ohne Ursachensatz (T18) und erschiene in der Diff-Ebene als Aenderung
  ohne Ursache (T20).
  Abbruch wie erwartet (Zeile 778): [dieselbe Meldung]
Riegel je Schreibzugriff: Zugang mit Merkzahl 0 gegen partie.runde 7 -- zu
```

**Die Aenderung gegenueber dem Vorzustand ist genau `(Nr. 307)` und sonst nichts.** Den
Vorzustand habe ich nicht ueber den Commit-Betreff gesucht, sondern ueber
`git log -S "class Meldung" -- kern/src/zustand.cpp`; der Umbau liegt in `de7c991`. Dort
lautete die Zeichenkette `"… vorbeigelaufen: partie.runde traegt "`, jetzt steht
`"… vorbeigelaufen: "` + `adresse(PLATZ_RUNDE)` + `" traegt "`. Eingefuegt ist also
` (Nr. 307)`, entfernt ist nichts.

**Was nicht ausfallen durfte, faellt tatsaechlich nicht aus:**

- Der Riegel greift. Beide Schreibversuche des veralteten Zugangs brechen ab
  (`zustand_probe.cpp:773` und `:778`), und die Zusicherungen daneben (`:774`, `:779`)
  belegen, dass der Zustand auf 2.000.000 bzw. 7 stehen bleibt. Sie sind Teil des
  gruenen Laufs, nicht meine Lesart.
- Beide Rundennummern stehen drin: die `7` aus dem Zustand und die `0` des Zugangs.
- Die Meldung des Konstruktors (Zeilen 728/729) ist eine feste Zeichenkette und
  unveraendert.

**Die Adressform habe ich gegen das Verzeichnis gehalten, nicht gegen den Code:**
`daten/adressen.md:349` fuehrt `| 307 | partie.runde |`. Textform und laufende Nummer
stimmen beide. Und diese Auskunft kann nicht aus einem Rest der alten Klasse stammen --
die hatte kein `adresse()`. Dass der Kopf tragend ist, belegt damit die Ausgabe selbst
und nicht erst eine Gegenprobe.

### Der Rand des Puffers, von Hand nachgerechnet

Die laengste Meldung, die dieser Aufruf ueberhaupt erzeugen kann:

| Stueck | Zeichen |
|---|---|
| fester Vorspann bis `vorbeigelaufen: ` | 87 |
| `partie.runde (Nr. 307)` | 22 |
| ` traegt ` | 8 |
| `zahl(steht_im_zustand)`, schlimmstenfalls `-9223372036854775808` | 20 |
| `, der Zugang hat dort ` | 22 |
| `zahl(hinterlassene_runde_)`, dito | 20 |
| fester Nachsatz ab ` hinterlassen.` bis `(T20).` | 183 |
| **Summe, schlimmster Fall** | **362** |

`meldung::PUFFER_ZEICHEN` ist 512, nutzbar sind 511. Der schlimmste Fall liegt 149
Zeichen darunter; ein Abschneiden ist an dieser Stelle **nicht herstellbar**, nicht bloss
unwahrscheinlich. Die Gegenprobe zur Rechnung: Mit den beiden einstelligen Zahlen des
Laufs ergibt dieselbe Tabelle 324 -- und gemessen sind es 324. Der Betrag von `I64_MIN`
laeuft in `meldung.hpp:111` ueber `u64` und nicht ueber `-wert`.

## Bedingung 3 -- erfuellt

`meldung_probe`, `schreiber_probe` und `schritt_probe` stehen namentlich als `Passed` im
Uebersetzungsbericht des Tages (`befunde/uebersetzung-2026-09-04.md`, Zeilen 79, 85, 87
und noch einmal 158, 164, 166; `ergebnis: ok`). Ich habe dem Bericht nicht geglaubt,
sondern nachgebaut -- in allen drei eigenen Bauverzeichnissen sind sie gruen:

```
100% tests passed, 0 tests failed out of 12   (Arbeitsbereich, RelWithDebInfo)
100% tests passed, 0 tests failed out of 8    (kern/, RelWithDebInfo)
100% tests passed, 0 tests failed out of 8    (kern/, Debug)
```

Darin auch `belegstellen_riegel`, den der Baubericht des Bauagenten noch als rot mit
einem Fund beschreibt. Er ist gruen; der Fund lag in `kern/include/kern/zustand.hpp` und
gehoerte Paket 0027, das ihn inzwischen geraeumt hat (`7eb8061`, dazu Vorschlag 0072).

## Die nicht-mechanische Stelle -- selbst nachgesehen, nicht uebernommen

Das Paket verlangt, den Weg `meldung.hpp` -> `zustand.hpp` -> `index_zu_adresse` geprueft
zu haben statt vermutet. Nachgesehen:

- `kern/include/kern/zustand.hpp` bindet ausser Standardkoepfen nur `festkomma.hpp` und
  `pruefsumme.hpp` ein; beide fuehren nur noch Standardkoepfe. Keiner der drei fuehrt
  auf `meldung.hpp` zurueck.
- Das Wort `meldung` kommt in `zustand.hpp` an keiner Stelle vor -- der Mustervergleich
  darauf bleibt leer. Kein Zyklus.
- `index_zu_adresse` ist in `zustand.hpp` deklariert und in `zustand.cpp` definiert. Der
  Kopf braucht beim Einbinden nur die Deklaration; dass die Definition in derselben
  Uebersetzungseinheit spaeter faellt, ist folgenlos. Beide Bauten belegen es.
- Die Einbindestelle ist dieselbe wie in den beiden Schwesterquellen: `meldung.hpp`
  hinter `festkomma.hpp` und **vor** `sperre.hpp` (`schreiber.cpp:25`, `schritt.cpp:42`,
  `zustand.cpp:40`). Das ist keine Geschmacksfrage -- `meldung.hpp` traegt die
  Gleitkommasperre bewusst nicht (`meldung.hpp:42-44`), und ein Kopf nach der Vergiftung
  zerbraeche an ihr. Die Sperre selbst steht unveraendert auf `zustand.cpp:44` und deckt
  den ganzen Rumpf.

## Wonach ich sonst gesucht habe -- und nichts gefunden

Meine vier Fragen, auf die geaenderten Zeilen angewandt:

1. **Determinismus.** Kein Gleitkomma (die Sperre steht, der Bau ist gruen), keine
   Iteration ueber eine ungeordnete Menge, kein Zufallsstrom, keine Zeit- und keine
   Speicheradresse im Ergebnis. `index_zu_adresse` ist ein Zugriff auf eine
   `constexpr`-Tabelle. Die Meldung haengt allein an `PLATZ_RUNDE` -- der Konstanten 306,
   die zwei `static_assert` festnageln -- und an zwei `i64` aus dem Zustand.
2. **Rueckkopplung.** Das Paket beruehrt keine Schleife des Spiels.
3. **Zustandsausgabe.** Die Aenderung **erweitert** die Auskunft um den Ort in derselben
   Form wie jeder andere Abbruch des Kerns und entfernt keine. Aus der Meldung allein
   bleibt erkennbar, welches Feld betroffen ist, welche Zahl im Zustand steht und welche
   der Zugang hinterlassen hat.
4. **Zahlenraender.** Oben nachgerechnet: `I64_MIN`, Pufferende, kein Ueberlauf --
   zusaetzlich von ASan und UBSan abgedeckt, ohne Befund.

Ausserdem verglichen: die entfallene Klasse Zeile fuer Zeile gegen die im Kopf. Die
Unterschiede sind `Index` statt `std::size_t`, `text("-")` statt eines
Ein-Zeichen-Feldes, eine getauschte Reihenfolge von `rest /= 10` und `++stellen`
innerhalb derselben Schleife, dazu im Kopf ein zusaetzlicher `nullptr`-Schutz und ein
`laenge()`. **Keiner davon aendert das Ergebnis**, und die Puffergroesse ist in beiden
512. Ein Verhaltensunterschied durch den Umbau ist damit ausgeschlossen und nicht nur
unbeobachtet.

## Abweichung ohne Befundwert

Der Baubericht nennt die Meldung „rund 360 Zeichen". Gemessen sind es **324**; 362 ist
der schlimmste Fall mit zwei zwanzigstelligen Zahlen. Die Zahl im Bericht beschreibt also
die Obergrenze und nicht den Lauf. Die Aussage, die sie traegt -- deutlich unter 511,
kein Abschneiden --, ist in beiden Lesarten richtig und oben unabhaengig nachgerechnet.
Kein Kriterium haengt daran: kein Befund, kein Ruecklauf.

## Was diese Pruefung **nicht** belegt

- Sie sagt nichts darueber, ob der Riegel des Startwertzugangs gegen die **echte Runde**
  greift. Er tut es heute nicht -- das ist der Befund meiner Pruefung zu Paket 0027 vom
  2026-09-04; er steht seither im Kopf von `zustand.hpp` ausgeschrieben und ist als Paket
  `0071-rundennummer-in-den-zustand` beauftragt. Dieses Paket hat den Riegel nicht
  angefasst, nur seine Meldung, und es war auch nicht damit beauftragt.
- Sie sagt nichts ueber den Meldungsinhalt als Zusicherung: `zustand_probe` **druckt**
  ihn, sie behauptet nichts ueber ihn. Der Wortlaut der Adressform ist dagegen in
  `meldung_probe` festgenagelt (`(Nr. 1)`, `(Nr. 310)`, `(Nr. 106)`, und ausserhalb der
  310 ohne erfundene Nummer) -- die Luecke ist geschlossen, nur an anderer Stelle. Ein
  eigenes Paket dafuer waere Doppelarbeit; deshalb schlage ich keines vor.
