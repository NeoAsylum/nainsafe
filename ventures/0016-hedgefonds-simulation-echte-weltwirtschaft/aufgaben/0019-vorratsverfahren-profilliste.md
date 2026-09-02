---
id: 0019-vorratsverfahren-profilliste
rolle: testentwickler
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/include/pruefstand/vorrat.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/src/vorrat.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp]
abnahme: Die sechs Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Vorratsverfahren und Profilliste — der Baustein des Prüfstands, der von nichts abhängt

Vorgaben: `technik.md` T43 (Vorratsverfahren und seine Invariante), T36 (Profilliste,
Profilkennung, Strategiekern), dazu T4 (kein Gleitkomma) und T13 (Kasten `pruefstand`).
`spiel.md`, Abschnitt „Das Aktionsprofil und wie es auf Aktionen wirkt" ist der Wortlaut,
gegen den gebaut wird. ADR 0011 für die Sprache.

**Dies ist das erste Paket der Rolle `testentwickler`.** Sie steht seit dem ersten Baulauf
in `BAUROLLEN` und hatte bis heute kein Paket.

## Warum dieses Paket jetzt geht und die anderen Prüfstandssachen nicht

Das Vorratsverfahren rechnet mit fünf Ganzzahlen und drei Steckplätzen. Es kennt den
`Zustand` nicht, es ruft `schritt` nicht auf, und `spiel.md` sagt ausdrücklich: *„Es wird
nie gerundet und nie gezogen."* Also braucht es auch `kern::zufall` nicht. Damit hängt es
an **keinem** Paket dieses Vorhabens und ist sofort baubar — während `werte` blockiert ist,
`schreiber` auf 0008 wartet und `schritt` mangels Rechenvorschrift für „Schaden" gar kein
Paket hat.

Die Rolle bringt es mit: *„Der Prüfstand für den Selbstspieler … die Mechanik dafür ist
deine Arbeit, die Auswertung seine."* Du baust die Mechanik. Maß 2 und Maß 3 stehen später
vollständig darauf.

## Was du baust

1. **Die Profilliste (T36).** Ein Aktionsprofil ist ein Vektor `(a1…a5)` mit
   `ai ∈ {0…5}` und `Σai = 5`; das sind `C(9,4) = 126` Profile. Erzeugt werden sie in
   **lexikographisch aufsteigender** Ordnung von `(a1…a5)` und **nullbasiert**
   durchnummeriert. Diese Nummer ist die **Profilkennung**.
2. **Der Strategiekern, vierwertig (T36).** Je Profil einmal berechnet und mit der Liste
   abgelegt, nicht je Lauf neu: die Aktionsart mit dem größten Anteil unter
   `{1 Position, 2 Beteiligung, 3 Lobby}`, bei Gleichstand die kleinere Kennung. Hebel und
   Sichtbarkeit gehen **nicht** ein. Sind alle drei null, ist der Kern `ohne` — nicht 1.
   Das ist Befund 8 aus einer früheren Prüfung und lässt sich nur hier beheben: Ein
   dreiwertiger Kern zwingt den Gleichstandsbrecher, eine Positionsstrategie zu behaupten,
   in der keine Position vorkommt.
3. **Das Vorratsverfahren (T43), wörtlich nach `spiel.md`.** Jede Art `i` führt einen
   ganzzahligen Vorrat `vi`, zu Partiebeginn null.
   - Am Rundenanfang: `vi += 3 · ai` für alle fünf Arten. Die Summe wächst je Runde um 15.
   - Für jeden der drei Steckplätze nacheinander: Wähle unter den Arten, die in dieser
     Runde noch mindestens eine zulässige Aktion haben, die mit dem **größten** `vi`; bei
     Gleichstand die **kleinere** Kennung. Setze eine Aktion dieser Art und rechne
     `vi −= 5`.
   - Hat keine Art eine zulässige Aktion, bleibt der Steckplatz leer und **kein Vorrat wird
     verrechnet**.
   - `ai = 0` **verbietet die Art nicht**, sondern schiebt sie ans Ende. Ein hartes Verbot
     ist der Fehler, gegen den dieser Satz geschrieben ist.

   `vi` wird **nie bei null abgeschnitten**. Er darf negativ werden, und genau daran hängt
   die Invariante.
4. **Die Probe** mit den Bedingungen unten.

**Was du nicht baust:** die Zulässigkeitsliste aus T32, die Bots, die drei Maße, die
Fensterlogik von Maß 3. Die Zulässigkeit ist ein Eingabewert deiner Funktion — welche der
fünf Arten in dieser Runde überhaupt zur Wahl stehen —, und der Invariantenfall setzt alle
fünf durchgehend zulässig. Wer hier eine Zulässigkeitsliste erfindet, baut T32 ein zweites
Mal und falsch.

## Der Kasten und seine `CMakeLists.txt`

`pruefstand` ist nach T13 ein eigener Kasten. Die `CMakeLists.txt` des Arbeitsbereichs
führt ihn **schon** in `FABRIK_MITGLIEDER` und überspringt ihn, solange er keine eigene
`CMakeLists.txt` hat (Zeile 36–51) — **fass diese Datei nicht an**, sie gehört keinem
Paket und ist genau dafür so gebaut.

Zwei Sachen, an denen der Bau sonst rot wird:

- `baulauf.py` sucht **jede** `CMakeLists.txt` einzeln und ruft auf jeder `cmake`,
  `--build` und `ctest`. Deine muss also **allein** durchlaufen, nicht nur über den
  Arbeitsbereich. `kern/CMakeLists.txt` Zeile 26–29 zeigt, wie: bei
  `PROJECT_IS_TOP_LEVEL` die `werkzeugkette.cmake` des Arbeitsbereichs einbinden und
  `enable_testing()` rufen.
- Sammle Quellen und Proben mit `file(GLOB … CONFIGURE_DEPENDS)` wie der Kern, damit das
  nächste Prüfstandspaket seine Datei danebenlegen kann, statt deine anzufassen. Das ist
  der Kollisionsschutz, nicht Bequemlichkeit.

Dieses Paket linkt **nichts** — weder `kern` noch eine Fremdabhängigkeit. T3 erlaubt dem
Prüfstand `rayon`; hier wird nichts parallel gerechnet, also kommt es nicht herein.

## Abnahme

1. **Die Profilliste trägt 126 Einträge in lexikographisch aufsteigender Ordnung von
   `(a1…a5)`, nullbasiert nummeriert**, und die beiden Anker aus T36 stimmen: Das
   Referenzprofil `(1,1,1,1,1)` trägt die **Kennung 76**, und die Kennungen **0 bis 5** sind
   genau die sechs Profile `(0,0,0,a4,a5)`. Beide Anker stehen in der Ausgabe der Probe mit
   ihrem Vektor.
2. **Der Strategiekern ist vierwertig, und die Zählung stimmt:** Genau **6** Profile tragen
   den Kern `ohne`, **120** sind klassifiziert (T36). Die Probe nennt beide Zahlen und
   listet die sechs kernlosen Profile mit Kennung und Vektor.
3. **Die Invariante aus T43 gilt für alle 126 Profile, für `k = 1` und für `k = 3`.** Bei
   durchgehend zulässigen fünf Arten steht der Vorratsvektor nach `5k` Runden wieder auf
   `(0,0,0,0,0)`, und Art `i` hat genau `3k·ai` der `15k` Steckplätze bekommen — für
   `k = 1` also `3·ai` von fünfzehn nach fünf Runden, für `k = 3` `9·ai` von
   fünfundvierzig nach fünfzehn. **Beide Fälle einzeln**, weil genau ihre Verwechslung
   dreimal Befund war (T43, letzter Punkt); ein Test, der nur `k = 1` prüft, findet sie
   nicht.
4. **Die Probe des Referenzprofils fällt zeichengleich heraus.** Die Runden 1 bis 5
   vergeben die Arten `1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5`. Die Probe druckt die Folge
   in dieser Form; sie steht wörtlich in `spiel.md` und stammt damit **nicht** aus diesem
   Programm. Das ist derselbe Grundsatz wie bei 0012: Ein Erwartungswert, den der eigene
   Code erzeugt hat, ist eine Wiederholung und kein Nachweis.
5. **Zwei absichtlich falsche Fassungen zeigen, dass Bedingung 3 und Bedingung 4 je etwas
   messen.** Für jede der beiden eine, in der Probe als solche benannt, und die Probe weist
   nach, dass die zugehörige Prüfung sie **verwirft** — mit Profil und Runde, an denen es
   auffällt. Der Grund, warum es zwei sein müssen und nicht eine: Der Gleichstandsbrecher
   nach *größerer* Kennung liefert `5,4,3 | 2,1,5 | …` und besteht Bedingung 3 trotzdem, weil
   jede Art wieder dreimal drankommt — nur Bedingung 4 fängt ihn. Umgekehrt fällt ein bei
   null abgeschnittenes `vi` erst über die Invariante auf. Eine Prüfung, die nie rot wird,
   prüft nichts.
6. **Kein Gleitkomma, keine Fremdabhängigkeit, keine gemerkte Ablage.**
   `grep -rnE 'float|double'` über die drei Quelldateien liefert nichts. Der Vorrat gehört
   dem Objekt, nicht dem Kasten:
   `grep -nE 'static |^[A-Za-z_][A-Za-z0-9_:<>, ]* [a-z_][a-z0-9_]* *='` über
   `vorrat.cpp` zeigt keine veränderliche Ablage ausserhalb einer Funktion; `constexpr` und
   `const` sind zugelassen. **Dieser Mustervergleich ist die vom Prüfer der 0012 korrigierte
   Fassung** — der dortige (`^\s*[A-Za-z_]+ [a-z_]+ =`) findet `u64 zaehler = 0;` nicht,
   weil `[A-Za-z_]+` an der Ziffer abbricht, und trifft damit ausgerechnet die Typen dieses
   Vorhabens nicht. Der Prüfer führt ihn zusätzlich von Hand nach; ein Mustervergleich, der
   nichts findet, ist kein Nachweis, dass nichts da ist.

Der Übersetzungslauf (`befunde/uebersetzung-<datum>.md`) ist der zweite Nachweis für die
Bedingungen 1 bis 5: Stimmt eine Zahl nicht, ist `ctest` rot. Der Prüfer urteilt trotzdem
gegen die Liste — grün heisst „die Zahlen passen zueinander", nicht „die Zahlen sind die
richtigen".

## Was ausdrücklich kein Befund ist

Der Modulname, die Aufteilung auf Kopf und Quelle, ob der Kern `ohne` als eigener
Aufzählungswert oder als leerer Wert geführt wird, die Benennung der Hilfsfunktionen, das
Ausgabeformat der Probe jenseits der in Bedingung 1 bis 5 genannten Zahlen. `specs/`
schweigt dazu.

**Auch kein Befund:** dass `pruefstand` nach T13 auf `schnittstelle` zeigen darf und es
hier nicht tut. T13 gibt die erlaubte Richtung an, keine Pflicht, sie auszunutzen.

## Eine offene Entwurfsfrage, die dich nicht blockiert

Ob das Vorratsverfahren später aus `pruefstand` heraus auch vom Bruchtester (T30 Prüfung 5)
gerufen wird, hat der Architekt nicht entschieden. Für dieses Paket ist es gleichgültig:
Die Mechanik ist dieselbe, und die Frage ist eine Verdrahtungsfrage. Sie steht in
`rueckstand.md`, damit sie nicht in deinem Paket verschwindet.

## Rückläufe

0.
