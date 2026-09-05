---
typ: pruefung
paket: 0116-laenderzahl-als-parameter
pruefer: entwurf-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen einzeln nachgemessen — jede Formel von Hand eingesetzt und an zustand.hpp, T15, T38 und reihen.toml verankert; die vier T56-Messungen mit eigenem grep wiederholt; der Bestandsschutz am Datei-Diff der Spanne 9e46cfa→1f763e9 gemessen
befunde: 2
---

# Pruefung 0116 — Die Laenderzahl als Parameter

**Gegenstand:** der neue Abschnitt 19 (T54–T57) in
`specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md`, geliefert in Commit
`1f763e9`. Das ist der letzte Commit auf der Datei (`git log -- technik.md`); der
Arbeitsbaum ist gegenueber ihm unveraendert (253.725 Byte). Gemessen habe ich am
Datei-Diff der Spanne `9e46cfa → 1f763e9` und am heutigen Stand, nicht an den
Selbstberichten im Paket.

## Bedingung 1 — erfuellt, und zwar strukturell, nicht nur numerisch

Alle sechs Zahlen tragen in T55 einen Ausdruck in `L`, `S`, `I`; jede habe ich selbst
eingesetzt (`L=4, S=3, I=4`), und die Rechnung steht im Fliesstext daneben:

| Zahl | Formel | meine Rechnung |
|---:|---|---|
| 310 | `L(4S+4I+16) + (L+1)L(S−1) + L(S+2) + 3LS + 5S + 23` | `176+40+20+36+38 = 310` |
| 175 | `L(4S+I+11) + (4S+10) + (L+1)L(S−1) + (S−1) + 3` | `108+22+40+2+3 = 175` |
| 135 | `L(3I+5) + L(S+2) + 3LS + 11` | `68+20+36+11 = 135` |
| 40 | `(L+1)·L·(S−1)` | `5·4·2 = 40` |
| 27 | `L·(S+4) − 1` | `4·7−1 = 27` |
| 20 | `L·(S+2)` | `4·5 = 20` |

Symbolisch konsistent: die 175er- und die 135er-Formel addieren sich exakt zur
310er-Formel (`L(4S+I+11) + L(3I+5) = L(4S+4I+16)`; `(4S+10)+(S−1)+3+11 = 5S+23`).

**Entscheidend ist, dass die Formeln die Struktur der Quellen wiedergeben und nicht bloss
die Zahl treffen.** Nachgemessen an vier Stellen, die den neuen Abschnitt nicht kennen:

- `kern/include/kern/zustand.hpp`: `LAENDER=4`, `SEKTOREN=3`, `INSTRUMENTE=4`,
  `SEKTOREN_HANDELBAR=2` als `constexpr`; `LAND_FELDER=44` mit dem bestehenden
  `static_assert` `12+9+3+16+3+1` — das ist Term fuer Term `4S + 4I + 16` (12
  Sektorfelder, 16 Instrumentenfelder, 16 = 9 Aggregate + 3 politische + 3 Restdauern
  + 1 Basiswechsel). Handel steht dort als `GEBIETE·(GEBIETE−1)·SEKTOREN_HANDELBAR`,
  also `(L+1)·L·2`; die Warnung in T54, dass `S−1` nur heute mit `SEKTOREN_HANDELBAR`
  zusammenfaellt, trifft den Code woertlich. Steckplaetze 12+4+4 = `L(S+2)`,
  Beteiligungen `LAENDER·SEKTOREN·2 = 2LS`.
- Die T38-Tabelle (technik.md, Maskenzerlegung): in der Maske je Land
  `12+9+1+4+1 = 27 = 4S+I+11`, ausserhalb je Land `1+1+12+3 = 17 = 3I+5`, Partie `3`,
  dazu Mandatsstand, Marktkorb, Fondsaggregat, Ueberrendite `1+2+5+3 = 11` — jede
  Konstante der beiden Maskenformeln hat dort ihre benannte Zeile.
  `108+22+40+2+3 = 175` und `68+12+2+52+1 = 135` stehen im Bestand (Z. 1365 f.),
  unveraendert.
- `daten/reihen.toml`: `sollreihen_gesamt = 27`; die fuenf Top-Level-Eintraege tragen
  4+12+4+3+4, und die dateieigene `zaehlregel_t37` nennt unabhaengig davon „Reihen 1,
  2, 8, 10 mit 4 + 12 + 4 + 3, abgeleitet 4 (Reihe 11)" — exakt die Zerlegung
  `L + LS + L + (L−1) + L = L(S+4) − 1`. Das `L−1` der Reihe 10 deckt der Bestand
  selbst (Z. 1653: „Reihe 10 traegt drei Laender, die USA definitionsgemaess nicht").
  Die Warnung zu den zwei weiteren `sollreihen`-Treffern (Z. 609, 620) stimmt: beide
  liegen in `[[reihe.lizenzbeleg]]`-Untertabellen von Reihe 2.
- Die `L=9`-Spalte: alle vierzehn Werte von Hand nachgerechnet (396+180+45+81+38 = 740;
  Sollmaske 243+22+180+2+3 = 450; ausserhalb 153+45+81+11 = 290; Sollreihen 62), und
  alle acht Vergleichszahlen stehen tatsaechlich in Paket `0118` (Tabelle „Was neun
  Laender kosten" und Sollreihen-Tabelle), samt der dort festgehaltenen Wahl von Weg A.

## Bedingung 2 — erfuellt

T56 waehlt genau eine der beiden Moeglichkeiten (Aufzaehlungen bleiben), begruendet sie
und benennt `kern/include/kern/zustand.hpp` als die eine Eintragstelle. Die vier
Begruendungspunkte habe ich einzeln nachgemessen: `enum class Gebiet : std::uint8_t`
traegt die Werte 0–4 und die Adressarithmetik rechnet aus den Konstanten (Punkt 1); die
Zeilenzaehlung habe ich mit `grep -c -E 'Gebiet::(US|CN|DE|BR|RW)'` ueber `kern/`
wiederholt und **alle neun Einzelwerte exakt reproduziert** (werte.cpp 25, schritt.cpp 6,
schreiber.cpp 5, zustand.cpp 5, zustandsausgabe.hpp 1 = 42; werte_probe 109,
schreiber_probe 22, zustand_probe 9, zustandsausgabe_probe 1 = 141) (Punkt 3);
`GEBIET_KUERZEL` existiert in `kern/src/zustand.cpp` (Punkt 1/Umzug); die T17b-Adressen
tragen die Kuerzel im Text (Punkt 4). Zu Punkt 1 ein sachlicher Fehler im Nebenwerk —
Befund 2 unten; er stellt weder die Wahl noch ihre Begruendung um.

## Bedingung 3 — Zweck erfuellt und schaerfer belegt, als der Wortlaut es koennte; der Wortlaut selbst ist unerfuellbar (Befund 1)

Eigene Messung, ohne den alten Stand auszuchecken: Der Datei-Diff der Spanne ist **ein
einziger Hunk am Dateiende, 202 hinzugefuegte und null entfernte Zeilen** — jede
Bestandszeile ist byte-identisch. `grep -c` am heutigen Stand: `310` → 43, `vier Laender`
→ 4. Im Diff enthalten die hinzugefuegten Zeilen kein „vier Laender" (4 vorher = 4
nachher, Wortlaut erfuellt) und genau **zwei** Zeilen mit `310`: die Formelzeile der
Tabelle und die Nachrechnung (41 vorher, 43 nachher).

**Befund 1, an den Projektmanager, kein Baufehler:** Bedingung 1 und der Wortlaut von
Bedingung 3 sind fuer die Zeichenfolge `310` unvereinbar. Bedingung 1 verlangt eine
Formel, deren Einsetzung „genau die heutigen Werte" liefert und deren „Rechnung daneben
steht" — eine Rechnung, die ihr Ergebnis 310 nicht nennt, ist keine. Jede Lieferung, die
Bedingung 1 erfuellt, erhoeht die `310`-Trefferzahl um mindestens die Formel- und die
Rechenzeile. Ein `zurueck` hierauf oeffnete das Paket gegen ein Kriterium, das nur durch
Verletzen eines anderen Kriteriums desselben Pakets erfuellbar waere. Der **Zweck** der
Bedingung steht in ihr selbst („Der Bestand bleibt unberuehrt … Dieses Paket beschreibt,
es aendert nicht") und ist mit der staerksten verfuegbaren Messung belegt: null entfernte
Zeilen, reine Anfuegung, Bestand byte-identisch. Ich urteile deshalb `geprueft` und melde
den Kriterienwiderspruch. Fuer kuenftige Pakete: Eine Trefferzahl-Bedingung darf keine
Zahl bewachen, die eine andere Bedingung desselben Pakets hinschreiben muss; „null
entfernte oder geaenderte Bestandszeilen im Datei-Diff" misst denselben Zweck ohne den
Widerspruch.

## Befund 2 — T56 uebergeht die zweite Kuerzeltabelle; die vorgeschlagene Zusicherung waere wirkungslos

T56 schreibt: nach dem Umzug von `GEBIET_KUERZEL` in den Kopf sei der vollstaendige
Vorgang fuer ein weiteres Land „**alles in einer Datei**, alles von `static_assert`
bewacht". Das ist falsch: `kern/src/zustandsausgabe.cpp` haelt eine **ausdrueckliche
zweite Fassung derselben Liste** (`constexpr std::array<const char*, GEBIETE>
GEBIET_KUERZEL`, im Kommentar dort: „Zweite Fassung derselben Liste — `src/zustand.cpp`
fuehrt sie fuer den Adressbau"). Ein sechstes Gebiet braucht auch dort ein Kuerzel. Weil
die Groesse als `GEBIETE` vorgegeben ist, **uebersetzt eine vergessene Ergaenzung stumm**
— der sechste Eintrag wird ein Nullzeiger; gefangen wuerde das erst zur Laufzeit von
`zustandsausgabe_probe`, nicht beim Uebersetzen. Aus demselben Grund ist die in T56
vorgeschlagene Zusicherung `static_assert(GEBIET_KUERZEL.size() == GEBIETE)` in der
heutigen Deklarationsform eine Tautologie: `.size()` eines
`std::array<const char*, GEBIETE>` ist per Konstruktion `GEBIETE`, mit oder ohne sechsten
Initialisierer. Wirksam wird sie nur, wenn die Groesse aus der Initialisiererliste
abgeleitet wird statt vorgegeben. **So erzeugt man den Fehler:** `GEBIETE` auf 6 und
`LAENDER` auf 5 setzen, beide Kuerzeltabellen unangetastet lassen — `zustandsausgabe.cpp`
uebersetzt fehlerfrei. Vorschlag als eigenes Paket:
`aufgaben/0149-t56-zweite-kuerzeltabelle-und-wirksame-zusicherung.md`
(`status: vorschlag`). Kein Ruecklauf: Die drei Abnahmebedingungen verlangen Wahl,
Begruendung und Dateinennung, und alle drei stehen; der Fehler liegt im Umzugsvermerk.

## Wonach ich sonst gesucht habe, ohne Befund

- **Symbolbelegung:** `L`, `S`, `I` sind in T54 definiert und kollidieren mit keiner
  dokumentweiten Belegung; `R` wird in T57 korrekt als Partielaenge verwendet; die
  `G`-Schreibweise aus 0118 kommt im Abschnitt nicht vor.
- **Die beiden Verwechslungswarnungen:** T28 fuehrt tatsaechlich „genau 40
  Halbierungsschritte" (Z. 1842) und T38 tatsaechlich 27 Maskenadressen je Land
  (Z. 1354) — beide „gleiche Zahl, andere Groesse"-Warnungen stimmen.
- **Die 31-Behauptung:** Abschnitt 7 nennt die Sollreihen weiterhin als „Zeilen 1, 2, 8,
  9, 10 und 11" (Z. 1790); Reihe 9 traegt in `reihen.toml` `sollreihen = 0` seit
  2026-09-03 (dortige Zaehlregel). Paket `0068` existiert und steht offen — der
  Abschnitt ordnet die Abweichung ihm korrekt zu und fasst die Stelle nicht an.
- **Fundstellenverweise:** T15 (Z. 1144, 1150), T16 (Z. 1168), T38 (Z. 1352 ff.), T28 —
  alle existieren und tragen die genannten Zahlen.
- **Verbotszonen:** Der Abschnitt aendert weder die Laenderzahl noch waehlt er ein
  fuenftes Land noch fasst er den Kern an — der Diff enthaelt ausschliesslich den neuen
  Abschnitt.

Ein Werkzeughinweis fuer Nachpruefer: Mein erster Existenztest auf `aufgaben/0068-*` per
Glob meldete faelschlich „nicht gefunden"; `ls` fand die Datei. Wer eine Nichtexistenz
als Befund schreiben will, prueft sie mit einem zweiten Werkzeug.
