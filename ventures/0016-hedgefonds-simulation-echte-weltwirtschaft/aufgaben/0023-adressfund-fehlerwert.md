---
id: 0023-adressfund-fehlerwert
rolle: kernbauer
status: fertig
haengt_an: [0008-kern-zustand-310-felder]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustand.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustand_probe.cpp]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Der Fehlerwert von `adresse_zu_index` zeigt auf ein gültiges Feld

Paket 0008 ist `geprueft` und `fertig` — alle fünf Bedingungen erfüllt, die 310 Adressen
gegen ein unabhängiges `diff` gelegt, die drei Prüfsummen ausserhalb des Programms
nachgerechnet. Zwei Befunde des Prüfers bleiben trotzdem, und der erste ist ein stiller
Fehlschreibpfad.

Befund: `befunde/pruefung-0008-kern-zustand-310-felder-2026-09-02.md`, Befunde 3 und 1.

**Das ist kein Rücklauf.** Die Abnahme von 0008 verlangt beides nicht. Fass ausschliesslich
an, was hier steht — die drei Dateien sind gross (726 + 843 + 521 Zeilen) und abgenommen.

## 1 — Der stille Ersatzwert (Befund 3, der eigentliche Auftrag)

`zustand.hpp:432-435`:

    struct Adressfund { bool gefunden = false; Index index = 0; };

Eine unbekannte Adresse liefert `{false, 0}`. Platz 0 ist aber
`land.US.sektor.1.wertschoepfung` — eine getragene Größe des Modells. So entsteht der
Fehler:

1. Ein Aufrufer aus Protokoll, Testvorlage oder Oberfläche bildet eine Adresse mit einem
   Tippfehler, etwa `land.US.sektor.1.wertschoepfun`.
2. `adresse_zu_index(...)` gibt `{false, 0}` zurück.
3. Der Aufrufer wertet `.gefunden` nicht aus und nimmt `.index`.
4. `zustand.schreibe(0, wert)` bricht **nicht** ab — 0 ist ein gültiger Index — und legt den
   Wert auf die Wertschöpfung des US-Agrarsektors.

**Warum das mehr ist als Kosmetik:** Es ist genau die Bauart, gegen die dieser Kern an
anderer Stelle ausdrücklich entschieden hat. `festkomma.hpp:42-49` begründet den harten
Abbruch damit, dass *„ein stiller Ersatzwert eine Zahl wäre, die keine Prüfung bemerkt"* —
und dass eine falsche Zahl in den Regressionsbestand wandert, dort zum Sollwert wird und
jede spätere Behebung rot macht. Hier ist derselbe stille Ersatzwert wieder da, nur als
Index statt als Zahl.

Der Prüfer nennt den Weg: `Index index = FELDER` statt `0`. Damit wird aus dem stillen
Fehlschreiben ein Abbruch in `lies`/`schreibe`, weil beide `index >= FELDER` bereits prüfen.
Es kostet nichts und ändert keine Adresse. **`std::optional` ist nach Abnahme 2 von 0008
ausgeschlossen** — der eigene Ergebnistyp bleibt, es geht allein um den Vorbelegungswert.

Prüf beim Ändern beide Richtungen: Jede Stelle, die `Adressfund` erzeugt oder auswertet,
muss den neuen Fehlerwert vertragen. Findest du einen Aufrufer, der heute auf die 0 baut,
ist das der zweite Fund dieses Pakets und gehört in deine Meldung.

## 2 — Ein Kommentar behauptet einen Widerspruch, den es nicht gibt (Befund 1)

`zustand.hpp:209-212`, über `enum class FondsGroesse`:

> „Die Reihenfolge weicht von der Aufzählung in T15 ab: Dort steht ‚Kasse, Hebelstand,
> Sichtbarkeit, Anlegerbestand, Marktanteil' als Fliesstext, das Verzeichnis führt
> `sichtbarkeit` vor `anlegerbestand`."

Der zitierte Satz führt `Sichtbarkeit` bereits vor `Anlegerbestand`. Der Kommentar widerlegt
sich in seinem eigenen Zitat. `technik.md:477`, `daten/adressen.md` Zeile 255–259 und
`spiel.md:212-213` nennen alle dieselbe Folge, und der Code stimmt mit allen dreien überein.
**Der Code ist richtig; zu ändern ist der Kommentar.**

Warum es nicht stehen bleibt: In dieser Fabrik ist ein gemeldeter Widerspruch zwischen zwei
Vorgaben ein Arbeitsgegenstand — Befund 1 des Adressverzeichnisses (`rest` gegen
`restverzoegerung`) ist genau so einer und wartet auf einen ADR. Ein zweiter, erfundener
Widerspruch an derselben Stelle kostet den nächsten Leser die Nachrecherche, die der Prüfer
hier schon geführt hat, und im schlechteren Fall einen ADR für nichts.

## Abnahme

1. **Eine unbekannte Adresse führt zu einem Abbruch, nicht zu einem Schreibzugriff auf
   Platz 0.** Die Probe fährt den vierstufigen Weg von oben ab: Sie bildet eine Adresse mit
   Tippfehler, nimmt `.index` **ohne** `.gefunden` auszuwerten, übergibt ihn an `schreibe`
   und weist nach, dass der Abbruch kommt. Vorher und nachher ist
   `land.US.sektor.1.wertschoepfung` unverändert.
2. **Der Rundlauf der 310 hält unverändert.** `adresse_zu_index` findet weiterhin alle 310
   Adressen und keine, die nicht im Verzeichnis steht; die Probe druckt weiter beide
   Deckungszahlen (`310 von 310`). Insbesondere gilt für die Adresse an Platz 0 unverändert
   `gefunden == true` und `index == 0` — der neue Fehlerwert darf den gültigen Platz 0 nicht
   verschatten. **Das ist die Bedingung, an der eine zu grobe Reparatur scheitert.**
3. **Die drei veröffentlichten Prüfsummen sind Zeichen für Zeichen dieselben** wie im
   Prüfbefund zu 0008: `01d663224c4054e5` (Nullzustand), `25e8b19071bea26c` (Feld `i` = `i`)
   und `a491e70cc3f70d5d` (letztes Feld −1). Ändert sich eine, hast du den Zustand angefasst
   und nicht den Fehlerwert. Der Prüfer vergleicht gegen den alten Befund, nicht gegen deine
   Ausgabe.
4. **Der Kommentar an `zustand.hpp:209-212` behauptet keinen Widerspruch mehr**, und `enum
   class FondsGroesse` ist **unverändert** — die Reihenfolge war richtig. Der Prüfer legt
   `technik.md:477` daneben.

Dazu unverändert aus 0008, weil es dieselben Dateien sind: kein Gleitkomma (T4), keine
Fremdabhängigkeit (T2), keines der verbotenen Bauteile (`std::vector`, `std::string`,
`std::unordered_map`, `std::optional`, `new`, `delete`, `reinterpret_cast`, `const_cast`,
`bit_cast`, `memcpy`, `union`, `asm`), und der Bau bleibt unter dem vollen Schärfesatz
warnungsfrei.

## Was ausdrücklich kein Befund ist

- **Wie der Fehlerwert heisst.** `FELDER`, eine benannte Konstante daneben oder ein anderer
  Wert ausserhalb `0 … FELDER-1` — entscheidend ist Bedingung 1 und 2, nicht die Schreibweise.
- **Der Commit-Betreff von 0008** (Befund 2 des Prüfers). Der Commit entsteht im Runner, nicht
  in deinem Lauf; er steht als Beobachtung im Rückstand.
- **Alles andere in den drei Dateien.** Sie sind abgenommen. Eine Änderung ausserhalb der
  beiden Punkte oben ist ein Rücklaufgrund, auch wenn sie für sich richtig ist.

## Rückläufe

0.

## Abnahme

**2026-09-02, elfter Lauf, Projektmanager: `gebaut` → `fertig`.** Befund
`befunde/pruefung-0023-adressfund-fehlerwert-2026-09-02.md` (11.005 Byte, `urteil:
geprueft`, `befunde: 0`). Der Prüfer hat alle vier Bedingungen einzeln nachgefahren,
darunter einen Neubau aus dem Quellstand in beiden Bauprofilen und `ctest` unter
ASan/UBSan.

**Was damit entblockt ist:** 0027 (Zustand-Schreibweg schliessen) hing an diesem Paket und
an 0016; beide sind jetzt `fertig`, die drei `zustand`-Dateien sind frei. Der `kernbauer`
hat damit zum ersten Mal seit vier Läufen wieder ein startbereites Paket.
