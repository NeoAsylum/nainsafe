# Logbuch: architekt

Rotated by the runner on 2026-09-09 at 14598 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-09-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (neunter Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-09 — Paket 0274: zwei rote Zeilen, zwei verschiedene Antworten

Entschieden und getrennt, wie Bedingung 3 es verlangt: `festkomma.hpp:356` fällt unter
**Regel 4, geweitet auf eine Seite**; `festkomma.hpp:99` fällt unter **keine Regel** und
verliert stattdessen in `kern/` seine Multiplikation. Fünf Regeln bleiben fünf. Neuer
Abschnitt 35, dazu vier Änderungen in T7 und ein datierter Vorwärtsvermerk in Abschnitt 33.

### Der übertragbare Fund: die Sprache kann die Regel beweisen, die der Text nur behauptet

Regel 4 verlangte den Cast auf **beiden** Seiten — aus Vorsicht, nicht aus einem Grund. Eine
Seite genügt, und zwar zwingend: Hat *ein* Operand von `*` den Typ `i128`, wandeln die usual
arithmetic conversions den anderen vor der Multiplikation ([expr.arith.conv]). Es gibt dann
gar kein `i64 * i64` mehr auf der Zeile. **Regel: Wer einen Textriegel weitet, sucht die
Sprachregel, die die Weitung erzwingt, statt eine Toleranz zu begründen. Dann ist die weitere
Regel nicht die laschere, sondern die beweisbare.** Der Riegel liest weiter nur Text; die
Garantie liegt im Übersetzer, nicht im Riegel.

Das Gegenstück, und es ist die Hälfte des Werts: **`:99` ist textlich `name * name` — die
exakte Gestalt der fünften Art.** Keine Textregel kann die eine zulassen, ohne die andere
zuzulassen. Das ist ein Beweis, keine Vorsicht, und er sagt: hier ist der Riegel fertig, die
Zeile muss sich bewegen. `az - ganz * an` **ist** `az % an` (`ganz = az / an` eine Zeile
darüber, `(a/b)*b + a%b == a`, [expr.mul]). Die Multiplikation verschwindet, statt einen
`static_cast<i128>` auf einen schon-`i128`-Wert zu bekommen, den nur der Riegel liest.

### Die Falle, in die ich fast gelaufen wäre

Beide Zeilen beginnen mit `const i128 <name> =`. Das ist textlich, greifbar, und es wäre die
naheliegende sechste Regel gewesen — **und sie ist falsch**: `const i128 x = a * b;` mit zwei
`i64` rechnet in `i64` und weitet danach. Genau der Fehler, den T7 fängt. **Der Zieltyp einer
Zuweisung sagt nichts über den Typ der Rechnung rechts davon.** Ich habe das gerechnet, bevor
ich es geschrieben habe; hätte ich es nicht, hätte die Regel den Riegel grün gemacht und die
Messung wertlos.

### Unsicher, damit der Projektmanager es sieht

1. **Die Kopfbedingung („Cast am Kopf des Operandenlaufs") ist mein Entwurf, nicht gemessen.**
   Sie schließt `f(static_cast<i128>(a)) * b` aus, wo der Rückgabetyp regiert. Im heutigen
   Korpus gibt es keine solche Zeile — ich schreibe die Regel gegen einen Fall, der noch
   nicht existiert. Ein Prüfer kann das als Ballast lesen; ich halte es für deny by default.
2. **Das `?`-Verbot kostet heute keine Zeile** (`zustand.hpp:777` ist die einzige Zeile mit
   `?` und `*`, und dort steht das `?` außerhalb beider Läufe). Auch das ist eine Regel gegen
   einen künftigen Fall.
3. **Ich habe zwei Stellen angefasst, die die Abnahme nicht nennt.** `:833` sagte „not yet
   built" — falsch, seit `0273` läuft der Riegel; ohne die Berichtigung widerspricht T7 sich
   50 Zeilen weit selbst. Und Abschnitt 33 schließt mit „runs green on its first day", was
   dieses Paket in einem Wort widerlegt; ich habe einen datierten Vorwärtsvermerk an den Kopf
   gesetzt statt die Geschichte umzuschreiben. Beides Ermessen, beides angreifbar.
4. **Ich habe die `%`-Umschreibung nicht laufen lassen**, nur bewiesen. `betrag` liefert
   `≥ 0`, `an != 0` ist Vorbedingung, also ist der Quotient darstellbar — gerechnet, nicht
   gemessen. Wer sie baut, prüft `festkomma_probe.cpp` nach.
5. **Zwei Nachfolgepakete, nicht eines**, und sie hängen nicht aneinander. Bis beide stehen,
   ist der Riegel rot — erst an zwei, dann an einer Zeile. Das ist der Preis der Entscheidung
   und steht so im Abschnitt.

### Fährten

- **Die Zeilenangaben im Paketrumpf waren wieder älter als die Datei**: `:5881-5886` für
  „Abschnitt 33, Meldung 2" zeigt bei HEAD auf die Regel-5-Herleitung; die Meldung steht bei
  `:5905-5910`. Dritter Beleg für die Regel vom 2026-09-08 — **nicht die Nummer ist
  unzuverlässig, sondern ihr Alter.** Die T7-Spannen (`:877-884`, `:918-921`) stimmten dagegen
  auf die Zeile, weil `0277` unterhalb bei `:5933` schrieb. Wer oberhalb einer Lieferung
  misst, misst richtig; die Warnung im Vermerk war pauschal.
- **Der Riegel sagt selbst, wohin die Änderung gehört:** „Wer eine davon fuer richtig haelt,
  aendert nicht diesen Riegel, sondern den Regelsatz in T7." Diese Zeile im Fehlertext hat
  mir die Richtung bestätigt, bevor ich T7 gelesen hatte. Ein Riegel, der seinen eigenen
  Eskalationsweg druckt, spart dem Nachfolger einen Lauf.
- **Der Bericht liegt unter `befunde/uebersetzung-<datum>.md`, nicht unter `berichte/`.** Mein
  erster `Grep` ging auf `berichte/` und gab „Path does not exist" — wieder der freundlichere
  Irrtum gegenüber einem stillen „no matches".
- Der Selbsttest des Riegels (9 Lesungs-, 23 Regelfälle) läuft grün, während der Riegel rot
  ist. Genau so soll es sein, und es war das schnellste Argument dafür, dass die Lücke im
  Regelsatz liegt und nicht im Werkzeug.

