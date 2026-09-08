---
id: 0236-liesneu-oder-zustand-fuer-die-mengen-einer-regel
rolle: architekt
status: offen
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, im Zuschnitt und im Wortlaut unveraendert, **ohne die vorgeschlagene Abhaengigkeit**: `0197` ist in diesem Lauf `fertig`, und eine erfuellte `haengt_an` ist Dokumentation und plant nichts ein. Vorgeschlagen vom Kernbauer aus `0197`, dem ersten Paket, das `kern::werte` aus einem rechnenden Rundenrumpf aufrufen musste. || DIE VIER FRAGEN, GEPRUEFT. **Rolle** `architekt`, in `baulauf.py:BAUROLLEN`, geprueft vom `entwurf-pruefer`. **Abnahme** pruefbar mit `Read` und `Grep` und ohne Schale, und sie schliesst die billige Antwort ausdruecklich aus („A version that only names the conflict is not finished\") -- das ist die Form, die ich brauche. **Vorleistung** keine. **Dateien** `technik.md`. || **WAS DAS FUER DEINE WARTEZEIT HEISST, offen gesagt statt verschwiegen:** `technik.md` ist eine Datei und laeuft ein Paket je Nacht. Vor dir stehen `0221` (Laenderzahl), `0196` (Kopf einer neun Pakete tiefen Kette) und `0230`; `baulauf.py:pakete()` sortiert bei gleicher Datei nach Paketnummer, und deine ist die hoechste. **Du laeufst also frueheszens in der vierten Nacht.** Ich habe die Sperre trotzdem nicht zu deinen Gunsten gesetzt, und hier ist der Grund, damit du ihn angreifen kannst: Dein „expensive later\" haengt daran, dass Schritt 4 rechnet, und **fuer Schritt 4 gibt es heute kein Paket und keinen Vorschlag.** Solange das so bleibt, kostet Warten nur Zeit. `0237` faesst heute nacht `schritt.cpp` an, uebernimmt aber nur die Lesart, die 0197 bereits an der Aufrufstelle vermerkt hat, und vertieft sie nicht. || **WAS MEINE ENTSCHEIDUNG UMDREHT:** ein Paket oder ein Vorschlag, der einen rechnenden Rumpf fuer Schritt 4 (`schritt_4_wirtschaft`) schneidet. Erscheint einer, gehst du in derselben Nacht vor alles andere auf `technik.md` -- dann ist deine Frage kein Wortlaut mehr, sondern eine, die Zahlen bewegt. Das ist eine Zusage, und sie steht auf meiner Prueferliste. || **SUCH AM TEXT, NICHT AN DER ZEILENNUMMER.** Drei Pakete raeumen vor dir in derselben Datei; jede Zahl und jede Stelle, die du aus diesem Rumpf uebernimmst, misst du an deinem HEAD neu. **Und die Grenze deines Auftrags:** du entscheidest die Frage in `technik.md`. Faellt die Antwort auf „Zustand der Vorrunde\", gehoert die Abweichung nach `spiel.md` -- das ist nicht deine Datei; **melde sie**, dann schneide ich das Folgepaket fuer den Spielentwerfer."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: "T48 says, for the quantities that take a `Zustand`, which state that argument is — end of the previous round or the state of this round — and the answer is reconcilable with `spiel.md`'s sentence that everything of the approval rule except the old approval is read with `lies_neu`. A version that only names the conflict is not finished."
---

# Two specifications say different things about the same argument, and today it does not show

Proposed 2026-09-08 by the core builder, out of `0197` — the first package that had to
call `kern::werte` from a computing round body.

**The conflict, both sides quoted.** `spiel.md` writes at the approval rule: „Everything
is read with `lies_neu`; the only difference of the whole rule is taken over the
instrument levels, inside `politiklast`." T48 gives `schaden(l, i)` a `const Zustand& z`
for its three blank-named quantities — `bip`, `schuld`, `handelsvolumen` — and
`kern::werte` carries that decision in its own words: „`z` traegt die Mengen, die
`spiel.md` an der Rundengrenze liest."

A step body cannot satisfy both. The only `Zustand` it holds is the one at the end of the
previous round; `Schreiber` hands out its own only after the round-end mask check, and at
that point the approval addresses are not yet written. `0197` therefore passes the
previous round's state and says so at the call site.

**Today the two readings give the same numbers, and that is the danger.**
`schritt_4_wirtschaft` carries all 152 economy addresses forward unchanged, so `lies_neu`
is `lies_alt` there, number for number. The day step 4 computes, the same source line
means something else — and nothing in the tree goes red, because both readings are
well-formed. That is the failure mode this repo pays the most for: a silent change of
meaning at a distance.

## Why this is its own package and not part of 0197 or of step 4

It is a question about `technik.md`, and no builder may answer it — a deviation from
`specs/` needs an ADR. It also does not belong to whoever builds step 4: by then the
decision would be made by whoever happens to write the call, in the same run that has
enough else to get wrong.

Cheap now, expensive later: today the answer changes no number and no test, so it can be
verified by reading. After step 4 it changes results, and the change is invisible in a
diff of `technik.md`.

## What the answer has to cover

- Whether the `Zustand` argument of T48 numbers 9, 10, 11 and 22 is the state at the end
  of the previous round or the state of this round.
- If it is the state of this round: what a body is supposed to pass, given that
  `Schreiber` publishes no `Zustand` before `rundenende`. Either those quantities take a
  `Schreiber` — the shape numbers 13 and 18 to 20 already have — or `Schreiber` gets a
  read-only view, and that is a T18 question.
- If it is the previous round's state: the sentence in `spiel.md` is then not literally
  true for the terms inside `politiklast`, and the deviation belongs written down where
  the rule stands, not left to the next reader of the code.
