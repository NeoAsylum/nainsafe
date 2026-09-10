# Logbuch: architekt

Rotated by the runner on 2026-09-09 at 14598 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-09-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (neunter Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-10 — Package 0287: a section that contradicted itself

Replaced `daten.md:210-214`. Licence part `:195-208` untouched, heading `:193` untouched,
nothing outside section 7. The blanket „Do not plan it in" became a **scoped** verdict:
non-EU/EFTA locked, EU/EFTA admissible under the conditions at `:200-208`. Plus a dated
correction paragraph and a third one saying explicitly what is **not** decided (which
series 9 gets).

*From here on this logbook is English. CLAUDE.md names logbook entries in the English list;
the German exception covers `spiel.md`, `technik.md`, toml comments and what the operator
reads as a decision. My 2026-09-09 entry got that wrong and stays as written.*

### The vermerk said German, the file is English

The acceptance vermerk closes with „**`daten.md` IST EIN DEUTSCHES DOKUMENT und bleibt
es**". It is not one any more: `daten.md` is English throughout (`:11` „Yes: Four sources
permit…", `:39` „### 1. World Bank"), and `ops/inhalt-0016….md:31-35` lists all five
section names in English. The translator got there first. **Rule: a language instruction in
a vermerk is a claim about a file, and claims about files are checked against the file.**
Costs one 40-line `Read`; CLAUDE.md settles it — the language follows the document.

### Why corrected rather than annotated

Condition 2 allowed both. Keep-and-put-the-measurement-beside-it would have left standing a
sentence measured false for the critical path — and thereby **restored exactly the state
condition 1 abolishes**: two paragraphs the reader weighs against each other. Taken
together the two conditions leave only one way out.

**The overreach I avoided:** „WDI and IMF have the same quantities without a special rule"
is **true for most quantities** — GDP, population, trade all sit there. It is measured
false only for the interest-rate path (`quellenbefund-leitzinspfad.md`: DEU 0/5 in the
`FR.INR` codes of topic 7, `FR.INR.MMKT` no row, IMF `MFS_IR/DEU.*.A` only MFI rates plus
`S13BOND` ending 2017). Striking it wholesale would have been a second false blanket. The
sentence is now narrowed, not deleted.

### Checked before assuming

`Grep "Eurostat"` over `daten.md`: four hits, one of them outside section 7 — `:390`
„Eurostat (locked for non-EU countries, no. 7)". That is compatible with the **new**
verdict and was not entirely compatible with the old one. So condition 4 (nothing outside
section 7) cost nothing — luck, not planning; otherwise I would have had to report it
instead of changing it.

### Unsure, so the project manager sees it

1. **I did not touch the heading `:193`.** „**EU and EFTA countries only**" is compatible
   with the new verdict — whereas siblings no. 8 and no. 9 carry their verdict in the
   heading („do not plan in"). Whoever reads the section by headings gets a scope for no. 7,
   not a verdict. I hold that to be right; a reviewer can read it as an incomplete
   resolution.
2. **The new text is about four times the old one** (~1,500 against ~370 characters). The
   growth is evidence — codes, windows, file paths — and evidence is what CLAUDE.md forbids
   cutting. It stays attackable.
3. **I did not re-measure the Eurostat side**, only cited it (`0280`, checked twice). The
   finding `…-2026-09-09-2.md:43-45` confirms row 3 and the quotation fidelity; that is
   what I lean on.
4. **`reihen.toml:1256` `deckung_urteil = "reisst"` still stands.** Intended (condition 4),
   but it means: until the datenbauer follows up, the spec says „admissible" and the series
   file says „tears". No contradiction, but an open thread.

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

