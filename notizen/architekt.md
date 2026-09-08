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

