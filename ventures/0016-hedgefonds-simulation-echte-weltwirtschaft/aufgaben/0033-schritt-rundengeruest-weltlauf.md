---
id: 0033-schritt-rundengeruest-weltlauf
rolle: kernbauer
status: fertig
haengt_an: [0008-kern-zustand-310-felder, 0016-schreiber-ursachenkette]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: Die sieben Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# `kern::schritt` — die Runde als Gerüst, im Modus `weltlauf`

Vorgaben: `technik.md` **T10** (der Weltschritt zieht nicht), **T19** (die Kette gehört
nicht in den Zustand), **T38** (der Modus ist Argument und bringt eine Sollmaske mit),
**T39** (zwei Lesezugriffe), **T18** (der Schreiber ist der einzige Schreibweg), **T9**
(feste Reihenfolge); `spiel.md` *Die Schleife* (die sechs Schritte).

**Warum es dieses Paket überhaupt gibt.** `ops/plan.md` meldet seit vier Fassungen dieselbe
Zahl — sieben von neun Kernkästen tragen Code, eine Spielrunde ist nie gerechnet worden —
und hat im zehnten Lauf ihre Ursache benannt: `werte` ist blockiert, `schritt` ist **nie
beauftragt** worden. 32 Pakete, keines nannte `kern/src/schritt.cpp` im Feld `dateien`.
`kern/include/kern/schritt.hpp` besteht aus zwei Zeilen und sagt selbst „Gebaut in Paket
noch kein Paket". Das ist die Hälfte, die niemand bestellt hat.

## Der Zuschnitt, und warum er so klein ist

**Dieses Paket baut die Runde, nicht die Regeln.** Es baut den Rahmen: Signatur,
Rückgabewert, die feste Reihenfolge der sechs Schritte, die Rundenendprüfung — und einen
Rundeninhalt, der jede Größe unverändert vorträgt. Nach einer Runde steht dieselbe Welt
noch einmal da, mit 175 Ursachensätzen, die das ausdrücklich sagen.

Der Grund für diesen Schnitt ist die Hausregel *ein Paket, ein Agent, ein Lauf* — und die
Lehre aus 0019, das dreimal an derselben Stelle abgebrochen ist, weil es zu groß war. Die
sechs Schritte der Runde sind sechs Pakete, nicht sechs Absätze.

**Der Rahmen läuft im Modus `weltlauf` und nur dort**, und dieser Modus ist mit Absicht
gewählt: Er ist der einzige, der heute vollständig baubar ist.

- **Schritt 2 (Aktionen) und Schritt 6 (Abrechnung) entfallen im `weltlauf`** (T38). Damit
  braucht dieses Paket **keinen Aktionstyp** — den gibt es im Kern noch nicht, T32 ist
  unbeauftragt — und **kein `kern::werte`**: Paket 0002 ist blockiert, bis der Architekt
  die Klasse-2-Frage entschieden hat. Der Rahmen hängt an keinem von beiden.
- **Im `weltlauf` wird kein einziger Strom gezogen** (T38). Das passt auf T10, wonach
  `schritt` ohnehin eine reine Funktion ohne Zufallsargument ist.
- Alles, was der Rahmen braucht, ist `Zustand` (Paket 0008, `fertig`) und `Schreiber`
  (Paket 0016, `fertig`). **Beide Vorbedingungen stehen seit dem 2026-09-02.**

**Was der Rahmen nicht ist.** Er ist keine gerechnete Welt. Eine Runde, in der sich nichts
bewegt, ist kein Modell — sie ist die Bühne, auf der die sechs Schritte einzeln aufgestellt
werden. Der `spielmodus` ist deshalb ausdrücklich ein Abbruch und keine zweite Fassung:
siehe Bedingung 7.

## Was du baust

Ein Modul `kern::schritt` aus den drei Dateien im Feld `dateien`.

1. **Die Signatur aus T10 und T19.** `schritt` nimmt den Zustand am Ende der Vorrunde, ein
   Aktionsbündel und den Modus und liefert **beides**: den neuen Zustand und die Kette
   dieser Runde. Die Kette geht nicht in den Zustand (T19) — der bleibt bei 310 Feldern und
   2.480 Byte. Kein Zufallsargument (T10).

   Der Aktionsparameter steht in der Signatur, weil T10 ihn nennt, und ist in diesem Paket
   ein leerer Typ mit einem Kommentar, der auf T32 zeigt. Ihn wegzulassen wäre eine
   Signatur, die ein späteres Paket ändern muss; ihn auszufüllen wäre Arbeit an einem
   Kasten, den `specs/` noch nicht beauftragt hat.

2. **Die sechs Schritte als sechs benannte Funktionen**, in der Reihenfolge aus `spiel.md`
   — Ansicht, Aktionen, Politik, Wirtschaft, Reaktion, Abrechnung. Jede ist privat (nur in
   `schritt.cpp`, ohne Deklaration im Kopf), jede trägt im Kommentar den Adressblock aus
   der Tabelle in T38, den sie später schreiben wird, und jede ruft heute für ihren Block
   `Schreiber::vortrag`.

   **Das ist der Anschlussort für die Folgepakete**, und deshalb ist es eine Vorgabe und
   keine Geschmacksfrage: Wer Schritt 4 baut, ersetzt den Vortragsblock von Schritt 4 und
   fasst nichts anderes an. Die beiden Schritte, die im `weltlauf` entfallen, stehen
   trotzdem da — leer, mit dem Verweis auf T38.

3. **Der Rundeninhalt: jede Adresse der Sollmaske genau einmal vorgetragen.** Über
   `schreiber::sollmaske(Modus::Weltlauf)` iterierst du die Adressen `0 … 309` in
   aufsteigender Reihenfolge (T9, keine streuende Menge) und rufst für jede gesetzte
   `vortrag(adresse)`. `vortrag` ist genau dafür da: „Eine Adresse, die sich nicht ändert,
   wird trotzdem geschrieben — *unverändert* ist eine Aussage und keine Lücke."

4. **Der Abschluss über `rundenende()`.** Die zweiseitige Prüfung aus T38 — jede Adresse
   der Maske genau einmal, keine ausserhalb — gehört dem `Schreiber` und wird **nicht**
   nachgebaut. Was `schritt` tut, ist sie aufzurufen und ihr Ergebnis herauszugeben.

5. **Kein Schreibzugriff am `Schreiber` vorbei.** Kein `feld[i] = …`, kein
   `zustand.schreibe(…)`. Paket 0027 schliesst diesen Weg gerade in `zustand.hpp` und nennt
   in seiner Begründung wörtlich den Fall, den dieses Paket sonst wäre: *„Ein späterer
   Bauagent, der in `kern::schritt` einmal `feld[i] = …` schreibt, erzeugt einen neunten
   Rückkopplungskanal, der in keiner Ursachenkette auftaucht."* Bedingung 5 misst das.

## Abnahme

1. **Die Signatur.** `kern/include/kern/schritt.hpp` deklariert genau eine öffentliche
   Funktion `schritt`. Sie nimmt Zustand, Aktionsbündel und Modus, sie liefert Zustand
   **und** Kette, und sie hat **kein** Zufallsargument. Nachweis am Kopf, wie bei jedem
   Modul dieses Kerns: `grep -rn 'zufall' kern/src/schritt.cpp kern/include/kern/schritt.hpp`
   liefert nichts.

2. **Die Maskengröße stimmt aus unabhängiger Quelle.** Die Probe prüft
   `schreiber::sollmaskengroesse(Modus::Weltlauf) == 175` und
   `… (Modus::Spielmodus) == 310`. Beide Zahlen stehen ausgeschrieben in der Tabelle von
   T38 samt Nachrechnung (`108 + 22 + 40 + 2 + 3 = 175`), nicht in diesem Paket.

3. **Eine Runde läuft durch.** `schritt(z, {}, Modus::Weltlauf)` auf einem Zustand mit
   beliebigen Feldwerten kehrt zurück, ohne abzubrechen. Das ist der Nachweis, dass die
   Rundenendprüfung aus T38 gehalten hat — sie bricht hart ab, wenn eine Maskenadresse
   fehlt oder eine ausserhalb berührt wurde.

4. **Die Kette hat genau 175 Glieder, und jedes ist ein Vortrag.** Die Probe zählt
   `kette.laenge() == 175` und geht alle Glieder durch: Jedes trägt `UrsacheArt::Vortrag`,
   `verzoegerung == 0`, `beitrag == 1000`, `alt == neu`, und die `ziel`-Adressen sind
   aufsteigend und paarweise verschieden.

5. **Der Schreibweg ist der einzige.** `grep -nE '\.feld\[|\.schreibe\(|feld_\[' kern/src/schritt.cpp`
   liefert **nichts**. Jede Zustandsänderung dieses Moduls läuft über `Schreiber::setze`
   oder `Schreiber::vortrag` (T18).

6. **Der unabhängige Erwartungswert: die Prüfsumme ändert sich nicht.** Eine Runde, die nur
   vorträgt, lässt jeden der 310 Werte stehen. Die Probe rechnet über
   `zustand::nach_bytes` und `pruefsumme` FNV-1a-64 auf Eingangs- und Ausgangszustand und
   verlangt **Gleichheit**. Das ist kein Erwartungswert aus dem eigenen Code, sondern eine
   Eigenschaft, die aus T12 und der Bedeutung von `vortrag` folgt — und sie fällt, sobald
   ein Schritt anfängt zu rechnen. Genau dann soll sie fallen; das Folgepaket zieht sie
   nach.

7. **Der `spielmodus` bricht ab, und die Meldung sagt warum.** `schritt(z, {},
   Modus::Spielmodus)` bricht über `festkomma::abbruch` ab, und der Wortlaut nennt, dass
   die Maske `spielmodus` alle 310 Adressen umfasst und die Schritte 2 und 6 noch kein
   Paket haben. Die Probe zeigt den Abbruch. **Ein stilles Vortragen aller 310 wäre eine
   Falschaussage** — es sähe aus wie eine gerechnete Spielrunde und wäre keine.

8. **`schritt_probe` steht namentlich als `Passed` im Übersetzungsbericht des Tages.**
   `kern/CMakeLists.txt` sammelt `test/*.cpp` über `file(GLOB … CONFIGURE_DEPENDS)` und
   macht aus jeder Datei ein eigenes Programm und einen eigenen `add_test`-Eintrag; dieses
   Paket fasst die Datei deshalb **nicht** an. Ein Kasten ohne benannten Test ist von einem,
   den es nicht gibt, nicht zu unterscheiden.

## Reihenfolge im Lauf, falls es eng wird

Zuerst der Kopf und ein `schritt.cpp`, das übersetzt und nur Bedingung 2 erfüllt, dann die
Probe, dann der Vortragsblock, dann die Bedingungen 6 und 7. Ein Kasten, der übersetzt und
zu wenig prüft, ist mehr wert als ein vollständiger Entwurf, den niemand baut — er macht
jeden späteren Abbruch **rot statt still**.

## Was ausdrücklich kein Befund ist

- **Wie die Rückgabe heisst und ob sie ein `struct` oder ein `std::pair` ist.** T19 verlangt
  beide Teile, nicht einen Namen.
- **Wie der leere Aktionstyp heisst.** T32 ist unbeauftragt; dieses Paket entscheidet über
  ihn nichts und darf es nicht.
- **Dass die Welt sich nicht bewegt.** Das ist der Zuschnitt und keine Unfertigkeit. Wer
  hier eine Regel aus `spiel.md` einbaut, weicht von diesem Paket ab.
- **Dass `parameter.toml` nicht gelesen wird.** Der Kern hat keine Datenschicht (T13); das
  Laden gehört `daten`, und der Rahmen braucht keinen Parameter.

## Warum es an nichts Blockiertem hängt

Weder an 0002 (blockiert, Klasse-2-Frage beim Architekten) noch an 0003 (blockiert, ADR
gegen T5 beim Betreiber) noch an 0027 (offen). Zu 0027 ist die Beziehung eine Vorgabe statt
einer Abhängigkeit: Es dichtet `zustand.hpp` ab, dieses Paket verpflichtet sich in
Bedingung 5 zum selben Ergebnis. Die beiden treffen sich in keiner Datei — 0027 hält
`zustand.*` und `schreiber.*`, dieses Paket `schritt.*` —, und wer zuerst fertig wird,
ändert am anderen nichts.

**Damit ist dies das Paket, das die eine Zahl aus `ops/plan.md` bewegen kann**, ohne auf
eine Entscheidung zu warten.

## Rückläufe

0.

---

**2026-09-03, Projektmanager: `gebaut` → `fertig`.** Befund
`befunde/pruefung-0033-schritt-rundengeruest-weltlauf-2026-09-03.md` (20.754 Byte,
`urteil: geprueft`, `befunde: 1`). Alle acht Bedingungen einzeln, fünf davon über einen
eigenen Bau und eine eigene Gegenprobe, die die Sollmaske ein drittes Mal aus den
Adresstexten bildet — nicht gegen einen Erwartungswert aus dem geprüften Code.

Der eine Befund ist ein Nebenbefund und **kein** Rücklaufgrund: Er sagt, dass die Arbeit
dieses Pakets in einem Commit mit dem Betreff von 0027 liegt. Das ist eine Feststellung
zur Buchführung, keine zur Sache — der Commit-Betreff belegt ohnehin nicht, wer gebaut
hat; die Datei belegt es. Kein eigenes Paket.

**Entblockt `0038-meldung-mit-adresse-gemeinsam`**, dessen zweite Sperre dieses Paket war.
Die Dateilisten der beiden schneiden sich nicht mehr: `kern/src/schritt.cpp` gehört mit
dieser Abnahme keinem offenen Paket mehr.
