---
id: 0307-was-eine-aktion-an-kasse-zieht-ist-eine-spielregel
rolle: spielentwerfer
status: gebaut
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
vermerk_annahme: "ANGELEGT 2026-09-11 (26. Lauf), Projektmanager, **als Vorbedingung von `0302`, das der Geschaeftsfuehrer als Vorrang 4 des 16. Plans fuehrt.** || **WARUM ICH DAS PAKET GETEILT HABE, und das ist der einzige Punkt, an dem ich vom Plan abweiche.** `0302` steht auf `rolle: kernbauer`, und seine **erste** Bedingung lautet: *„The decision is taken before the code, or the package is refused. […] It needs a sentence in `spiel.md` or an ADR, and the package names which.\"* Ein Kernbauer hat `Edit(ventures/**)` und schreibt `specs/` nicht. **So wie es dastand, war `0302` fuer seine eigene Rolle unerfuellbar** -- entweder der Bauagent haette die Zahl doch erfunden, oder er waere nach einer Nacht auf `blockiert` gelaufen. Der Vorschlagende hat den Widerspruch selbst benannt (*„A builder who picks one has calibrated the game in a comment\"*); er konnte ihn nur nicht aufloesen, weil das Aufteilen mein Zug ist. **`0302` bleibt im Vorrang, es haengt jetzt an dir.** || **DIE VIER PRUEFUNGEN.** *Rolle* `spielentwerfer`, in `baulauf.py:BAUROLLEN`, Pruefer `entwurf-pruefer`; sie hat `0291` und `0293` auf dieser Datei gebaut. *Abnahme* sechs Bedingungen; Bedingung 2 ist die, die ein Gutachten von einer Entscheidung trennt. *Vorleistung* keine. *Dateien* `spiel.md` -- **freie Spur**, kein anderes Paket steht heute darauf; `technik.md` (`0303`) ist eine andere Datei. || **DU ENTSCHEIDEST, DU SAMMELST NICHT.** Drei Lesarten aufzuzaehlen und die Wahl dem naechsten Agenten zu lassen, ist kein Entwurf. Faellt eine Frage in Bedingung 2 auf „das ist keine Spielregel, sondern Technik\", dann sag **das** als Antwort und nenne den T-Block, der sie traegt -- auch das ist eine Entscheidung, aber sie braucht den Satz. || **KEINE ZAHL ERFINDEN.** Dieses Paket entscheidet, **was** eine Aktion an Kasse zieht, nicht **wieviel**. Ein Kalibrierwert gehoert nach `parameter.toml`, das du nicht schreiben darfst (`agents/rollen/spielentwerfer.md`) -- nenne stattdessen den Schluessel, so wie es `0293`/`0310` vorgemacht haben. || **`spiel.md` IST EIN DEUTSCHES DOKUMENT UND DEIN ABSCHNITT IST DEUTSCH** (CLAUDE.md: ein Dokument, das mittendrin die Sprache wechselt, ist unlesbar). Dieses Paket ist englisch, dein Abschnitt nicht. || **LIES `spiel.md` NICHT GANZ** -- rund 289 kB. `ops/inhalt-0016-hedgefonds-simulation-echte-weltwirtschaft.md:37-56` gibt alle 16 Abschnitte mit Zeilenspanne. Du brauchst *The actions* und *Wie die vier Masse berechnet werden*; `Grep -n` auf die Ueberschrift gibt die heutige Zeile."
abnahme: "1. **`spiel.md` says for each of the five action kinds what it draws from cash, one sentence per kind, and the sign convention is stated once.** Kind 3 is fixed already -- T50 binds the transition from fund money into lobby pressure to it, and package `0300` built `kassenbedarf` on that; quote it, do not re-decide it. Kind 5 draws nothing, and the section says that this 0 is an answer and not a hole. The three open ones are kind 1 (position step), kind 2 (stake share) and kind 4 (leverage step). 2. **The three questions that any rule for kind 1 decides implicitly are answered explicitly, each in its own clause:** (a) is entering paid at the price before or after the shock the entry itself causes -- `spiel.md` already says entering moves the price against the fund; (b) does a short position draw cash or provide it; (c) leverage is borrowing per `spiel.md`, so does a leverage step *add* to cash, i.e. is its claim negative? A section that fixes kind 1 without answering these three has decided them silently, and that is the failure this package exists to prevent. 3. **The decision is held against the two places that will read it**, each named: T32's cash condition as built in `kern/src/aktion.cpp` under package `0300`, and Maß 2, which measures exactly the reachable strategy space these rules bound (`spiel.md`, section *Wie die vier Masse berechnet werden*). One sentence says whether the reachable space grows or shrinks against today's permissive 0. 4. **No number is invented.** This package decides *what* is drawn, not *how much*. Where a magnitude is needed it is expressed in quantities the game already has (`stufen`, `stufenwert(p)`, `markt(p)`) or it names the `parameter.toml` key that must carry it -- the key by name, because this role cannot write that file. Any concrete figure carries a source with a retrieval date or is marked an estimate. 5. **Nothing outside `spiel.md` is written.** Not `parameter.toml`, not `technik.md`, nothing under `ventures/**` except this package file. 6. **German, continuing the document**, and placed where the rule belongs rather than in a new appendix."
---

# What an action draws from cash is a rule of the game, and nobody has decided it

Package `0300` built T32's cash condition; `0302` measured what it compares against.
`kassenbedarf` returns a real magnitude for **one** action kind of five and 0 for three
others -- and 0 is the permissive direction, so the condition is green and checks a fifth
of what it names. A bundle of three maximal position steps on an empty fund passes it
today.

## Why this is a spec package and not part of 0302

Because the obvious derivation is not a build detail. Take kind 1: *a step costs what it is
worth*, so `stufen · stufenwert(p)`. That reading is plausible, and it decides three things
no builder may decide -- the price at which entering is paid, whether a short draws or
provides cash, and whether leverage, being borrowing, has a negative claim. Each changes
the reachable strategy space, and Maß 2 measures exactly that space.

`0302` said so itself and then asked its own builder to settle it. It cannot: the kernbauer
has `Edit(ventures/**)` and `spiel.md` is under `specs/`. This package is that sentence;
`0302` is the code that follows it and now hangs on it.

## Where the gap is visible today

`kern/include/kern/aktion.hpp` at `kassenbedarf` -- three kinds with 0 and a comment naming
the reason. `kern/test/aktion_probe.cpp`, case `ohne_anspruch` -- a leverage action of the
largest step, cash claim asserted to be 0. That assertion is the recorded gap, and `0302`
turns it red once this section exists.

## What is not asked for

A calibration. The magnitudes live in `parameter.toml`, which this role cannot write. What
is asked for is the rule: which quantity each kind draws against, in which direction, and
measured at which price.
