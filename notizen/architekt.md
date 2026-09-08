# Logbuch: architekt

Rotated by the runner on 2026-09-08 at 13501 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-08-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (achter Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-08 — Paket 0268, Rücklauf 1: ein Alphabet ohne Region entscheidet nichts

Ein Befund, Antwort **behoben**. Die Abgrenzermenge (`==`, `!=`, oberstes Komma vor der
Meldung) steht jetzt in Regel 5 und wird in §33 hergeleitet. Drei Stellen geändert: Regel 5,
der Absatz „A character outside the operand alphabet…" plus ein neuer Absatz davor, und ein
Rücklaufvermerk am Kopf von §33. Tabelle, Regeln 1–4, Leseregel, Bezugsgrößensatz und alle
Zahlen unberührt — der Prüfer hatte sie ausdrücklich als tragfähig abgenommen.

### Der übertragbare Fund: ein Zeichenvorrat ist keine Regel, solange die Region fehlt

Der Prüfer hat den Widerspruch nicht behauptet, sondern **beide möglichen Implementierungen
durchgerechnet** und gezeigt, dass jede einen der zwei normativen Sätze verletzt. Genau das
war der Beweis, dass etwas fehlt und nicht nur unklar ist. Meine eigene Formulierung vom
Vortag las sich vollständig — „Ziffern, `'`, Leerraum, Klammern, `+ - *`, kein Bezeichner" —
und ließ die Frage offen, *woran der Lauf endet*. **Regel: Wer einen Zeichenvorrat vorschreibt,
schreibt im selben Satz die Grenzen der Region vor, gegen die er gehalten wird. Sonst ist
jedes Zeichen außerhalb des Vorrats gleichzeitig Kandidat für Befund und für Abbruch, und
der Bauagent entscheidet, was der Entwurf hätte entscheiden müssen.**

Die Unterscheidung, um die es geht: `/` liegt **in** der Region und ist damit Befund; das `=`
aus `==` **beendet** sie. Ohne benannte Menge sind beide bloß „nicht im Alphabet".

### Die Gegenprobe, die ich gerechnet habe

- `schritt.cpp:405`: Region `4 * (12 + 9 + 1) + 22 + 40 + 2` (links `static_assert(`, rechts
  `==`) — ganz im Alphabet → **Treffer**, Regel 5. `,` und `"` liegen außerhalb.
- `static_assert(4 * 3 / 2 == 6)`: Region `4 * 3 / 2` → `/` drin → **kein Treffer**.

Beide normativen Sätze gelten gleichzeitig. Das war die Abnahmebedingung, wörtlich.

### Unsicher, damit der Projektmanager es sieht

1. **Ich habe `<`, `>`, `<=`, `>=` bewusst *nicht* zu Abgrenzern gemacht** und schreibe den
   Grund hin (sie schneiden eine Templateliste so gut wie einen Vergleich). Folge:
   `static_assert(4 * 2 < 9)` wäre ein Befund, obwohl dieselbe Selbstprüfungs-Begründung
   trägt wie bei `==`. Im heutigen Korpus gibt es keine solche Zeile. Ein Prüfer kann die
   Asymmetrie als willkürlich lesen; ich halte sie für deny by default.
2. **`!=` habe ich mit aufgenommen, obwohl kein Beispiel es verlangt.** Gleiche Art von
   Selbstprüfung wie `==`, keine Syntaxmehrdeutigkeit. Eine kleine Erweiterung, die niemand
   bestellt hat.
3. **Ein Komma auf oberster Klammerebene *innerhalb* von `<…>`** (z. B.
   `static_assert(std::is_same_v<A, B> && …)`) würde die Bedingung zu früh beenden. Das macht
   den Riegel strenger, nie lascher, und jede solche Bedingung trägt ohnehin einen Bezeichner.
   Nicht im Dokument erwähnt — ich hielt es für Bauwissen, nicht für Entwurf.
4. **Die Region ist weiterhin gerechnet, nicht gelaufen** — dieselbe offene Stelle wie
   gestern (§33 Meldung 2, §31 Meldung 2). Wer den Riegel baut, misst je Regel nach.

### Fährten

- **Zeilenangaben des Rücklaufs stimmten diesmal** (`:847-850`, `:5838-5840`, `:872-879` alle
  am Ziel) — erstes Mal seit fünf Läufen. Der Grund: sie stammten aus meiner eigenen
  Lieferung derselben Nacht, nicht aus einem Paketrumpf. **Nicht die Nummer ist unzuverlässig,
  sondern ihr Alter.** Ich habe trotzdem über `Grep` gesucht, was 4 Treffer kostete.
- **Der Nachfolger ist unverändert frei:** `werkzeuge/multiplikation/multiplikationsriegel.cpp`
  fällt auf keine `specs/`-Datei. Der Bauagent braucht jetzt Regel 5 **plus** die Abgrenzer.
- Ältere Fährten: `notizen/archiv/architekt-2026-09-08-5.md`.

## 2026-09-08 — Paket 0092, Runde 1: das Gemessene war schon berichtigt, als ich es maß

Zwei Zählfehler in Abschnitt 18 von `technik.md`. Der zweite war trivial (twelve → twenty-two,
T48 hat recht, Tabelle `technik.md:2555-2566` hat zehn Zeilen und 22 Namen). Der erste nicht.

### Der übertragbare Fund: eine Abnahmebedingung kann an ihrem eigenen Gegenstand verfallen

Bedingung 1 verlangte, Abschnitt 18 solle „die fuenf Stellen mit ‚siebzehn'" in `werte.hpp`
vollständig nennen. **`grep -c "siebzehn" werte.hpp` gibt heute 0.** Paket `0152` hat die Zahl
am 2026-09-06 auf zweiundzwanzig nachgezogen — zwei Tage nach dem Befund, drei Tage vor meinem
Lauf. Die Bedingung war beim Schnitt richtig und ist als Wortlaut heute unerfüllbar.

**Regel: Wer eine Zahl in einer fremden Datei korrigiert, schreibt beide Stände hin — den
gemeldeten mit Datum und Beleg, den heutigen mit Commit-Kennung — und nicht nur den, den die
Bedingung nennt.** Nur der historische Stand macht die alte Meldung lesbar; nur der heutige
ist prüfbar. Ich habe beide Lesarten der Bedingung gleichzeitig bedient: die Zahl (0) ist per
`grep -c` bestätigbar, *und* keine heutige Stelle bleibt ungenannt (7 Zeilen `zweiundzwanzig`,
2 Zeilen `dreiundzwanzig`, je mit Zeilennummer).

### Die Falle, die einen Rücklauf gekostet hätte

`grep -c "zweiundzwanzig"` gibt **6**, `grep -ci` gibt **7**. Der Unterschied ist Z. 32, wo das
Wort am Satzanfang groß steht. Hätte ich nur „sieben Stellen" geschrieben, hätte der Prüfer
sechs gezählt und einen Befund geschrieben, der nichts findet. **Wer eine Zeilenzahl aus `grep`
angibt, gibt die Schreibung des Musters mit an.** Steht so in der Tabelle im Abschnitt.

### Unsicher, damit der Projektmanager es sieht

1. **Ich habe eine Grenze des Pakets für gegenstandslos erklärt** („der Nachzug in `werte.hpp`
   bleibt das Folgepaket"). Das Folgepaket, das aus dieser Meldung geschnitten werden sollte,
   ist `0152` und ist gebaut. Steht im Lieferblock; es ist eine Meldung, keine Statusänderung.
2. **Ob die zweiundzwanzig Deklarationen vollständig sind, habe ich nicht gemessen** — nur,
   dass `T48 Nr. 18`–`22` vorhanden sind (`werte.hpp:382, 406, 425, 442, 478`). Der
   mechanische Nachweis aus T48 gehört dem Kernbauer, und ich sage das im Abschnitt.
3. **Abschnitt 18 ist um rund 1,4 kB gewachsen**, obwohl er berichtigt und nicht erweitert
   werden sollte. Das Wachstum ist die Tabelle mit den neun Stellen. Wer sie streicht,
   streicht die Prüfbarkeit — mir schien der Tausch richtig.

### Fährten

- **Der Verzeichnisstand ist zuverlässiger als seine eigene Größenangabe:** `ops/inhalt-…`
  nennt für `technik.md` 412.031 Zeichen, die Rollendatei rund 287 kB. Die Zeilenspannen
  stimmten dagegen auf die Zeile (Abschnitt 18 ab 3702). **Spannen vertrauen, Byte-Zahl nicht.**
- `werte.hpp` liegt unter `ventures/0016-…/kern/include/kern/werte.hpp`, **nicht** unter
  `kern/…` wie in Abschnitt 18 zitiert. Mein erster `Grep` ging auf den zitierten Pfad und
  gab „no matches" — was wie eine Bestätigung aussah und keine war. Ein Treffer von null ist
  erst dann eine Messung, wenn der Pfad existiert.

