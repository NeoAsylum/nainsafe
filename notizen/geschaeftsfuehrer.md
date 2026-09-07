# Logbuch: geschaeftsfuehrer

Rotated by the runner on 2026-09-07 at 13071 characters (cap 12,000). Predecessor: `notizen/archiv/geschaeftsfuehrer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

---

## 2026-09-08, 16th run — the lock, and a new best tool

**`ops/reserviert.txt` × `^dateien:` is the best tool I have had.** It replaces the queue
arithmetic of 2026-09-07. The file is a *scheduling input* — `baulauf.py:startbereit`
counts each line as an already-scheduled package, so nothing whose `dateien:` hits it gets
planned. One `Grep "^dateien:.*technik\.md"` over `aufgaben/`, intersected with the `offen`
set, turned "it is stalled" into **15 of 19 open packages held by one line**. No report,
no finding and no role named this. Check `reserviert.txt` **first**, every run: it is four
lines long and it can silently hold the whole backlog.

**The project manager's `vermerk:` field is the richest single source about the queue.**
0208's vermerk named the reservation verbatim, the chain order, and why he set `offen` and
not `blockiert` ("you are scheduled only once it falls -- and then without a further run
of mine"). That is his reasoning, not a report about it. **Read the vermerk of the
priority-1 package before anything else.** It is cheaper than the package body.

**Zero proposals is a signal, not an absence.** My role says the `vorschlag` packages are
the best evidence I get. Today there were **0** (yesterday 8) — because the PM accepted all
of them. Do not read `0 vorschlag` as "the trades stopped proposing"; check whether the
numbers reappeared as new `offen` ids (here 0212–0225).

**What the 15th plan achieved — record it, it is the only test of this role.** All five
priorities and the entire "was quer liegt" list landed within one day: 0198 `fertig`
(geprueft, 2 minor findings), 0200 `fertig`, 0197 → `blockiert` (not `zurueck`, as
recommended), 0208-baulauf → `blockiert`, the standing red gone (`ergebnis: ok`, 25/25 and
13/13), `gebaut`-with-`geprueft` down from 3 to 1. `fertig` 147 → 169. **The pattern from
the archive holds: one statement, to the right hand, works.** The right hand for the lock
is the operator, not the PM — the PM had already done everything he could.

**I changed a recommendation and said so (B → C).** Not because B was wrong but because
the *cost changed shape*: on 2026-09-07 the translation run cost a red test, today it costs
the lock, and B does not touch a lock. Naming the old recommendation in the same paragraph
is what makes the change readable rather than a contradiction.

**A hypothesis I checked instead of writing down.** The index arithmetic said 284.520 −
275.563 = 8.957 characters of `technik.md` sit outside all 21 sections, so I concluded the
Vorspann was the untranslated remainder holding the reservation. I read lines 1–31: **it is
already English.** The arithmetic was right about the size and wrong about the cause. Cost:
one `Read` with `limit`. *Every "therefore the cause must be X" about a spec is one cheap
Read away from being checked — take it, always.*

**Without `Bash` again (16th run, as on the 15th).** The whole plan came from `Read`,
`Grep`, `Glob`. Do not go looking for tools. The working substitutes:
`ops/reserviert.txt` (the lock), `ops/uebersetzt.txt` (what the translator claims is done),
`befunde/uebersetzung-<datum>.md` (compiler and ctest verbatim, runner-made — read
`ergebnis:` in the frontmatter first, it is one line), `ops/kontingent.md` (up to two days
old — say the age), `ops/inhalt-<venture>.md` (section sizes), and `Grep "^status:"` over
`aufgaben/` with `output_mode: files_with_matches` per status. The `.tmp` files still
inflate the `gebaut` count by two (`.paket.tmp`, `.kopf.tmp`) — subtract them.

### Next run, in this order

1. **Is `ops/reserviert.txt` empty?** If yes, 0208 should have run by itself — check
   `aufgaben/0208-schritt-*.md` for `gebaut`. If no, the operator has not decided C, and it
   goes to him as the single point, **counted, not re-argued** (this is the second plan in
   a row on the translation question).
2. **Did the one number move?** 1 of 310. It may only move after 0208 is `fertig`; if it
   moves earlier the measurement is wrong. Name the old value alongside.
3. 0157 (`offen` behind blocked 0197) — did the PM set it `blockiert`? If not, it is a
   second case of the class and belongs in the plan as a class, not as an item.

