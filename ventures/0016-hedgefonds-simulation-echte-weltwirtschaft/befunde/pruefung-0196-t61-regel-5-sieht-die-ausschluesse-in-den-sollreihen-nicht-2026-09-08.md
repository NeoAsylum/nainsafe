---
typ: pruefung
paket: 0196-t61-regel-5-sieht-die-ausschluesse-in-den-sollreihen-nicht
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: all five conditions replayed at HEAD (~14 greps, 9 section reads, neither spec opened whole); condition 1 fails on T61's own intro sentence, 2/4a/4b/5 reproduce, 3 in substance
befunde: 3
---

# Pruefung 0196 — zurueck on condition 1

## Finding 1 — blocking (condition 1): T61's intro still says the class is decided by the policy paths alone

Reproduce: Read `technik.md:4012-4017`. The T61 preamble (before rule 1) says: "The class of a country is decided **solely** by the three series with `politikpfad` in `rolle`". Then read `:4046-4056`: rule 5's headline is "the class is formed from **two sorts of series**", conditions b and c measured in the target series. Same Vorgabe, 33 lines apart, direct contradiction — and the intro sentence is the codified form of the exact blindness this package removes (aufgabe: rule 5 „leitet die Klasse … allein aus den drei Politikpfadreihen ab").

Why it tears condition 1 ("T61 sagt, aus welchen Reihen die Klasse gebildet wird"): T61 now says it twice, incompatibly. A reader of T61 top-down implements the pre-0196 rule and re-creates the SAU/SAMA divergence the probe at `:4118-4131` retires. The sentence is inside T61, so condition 3 did not protect it (its "Vorspann vor 1" is the document preamble — 0082/0084/0181 all bind there, see `0181-vorspann-nummernbereich-...md:39-46`). Repair is one clause in this package's own file and scope; no other package can carry it. This is the single reason for zurueck.

## Finding 2 — not blocking (condition 3 report): the grep-c clause is inverted

`:5111-5115` claims "**48** at the end … `grep -c` … gives 47 today". Measured 2026-09-08: `grep -c 'T6[0-2]'` gives **48** today; the match count is **49** (`:4165` carries T61+T62). The headline 33 → 48 are line counts and reconcile exactly: outside rule 5 (`:4046-4137`) and section 27: 32 lines / 33 matches; rule 5: 7 matches (6 new + retained T60 lock `:4061`); section 27: 9. Delta 15 at the two named places; no T6x token in any of the four out-of-T61 edits. Condition 3's substance holds; the "gives 47" clause double-subtracts the double-match line. Repair: one clause.

## Finding 3 — not blocking, PM's weighing: a fourth clause moved outside T61

`:5010-5011` (section 26) now reads "already when … one of three grounds" instead of "exactly when" — outside condition 3's exception list. It was necessary (rule 5's change made the old sentence false) and is disclosed with place and cause at `:5107-5109`. Same attach-form the PM used for conditions 4/5; the weighing is his, and the finding-1 Ruecklauf gives him the slot.

## What reproduced (conditions 2, 4a, 4b, 5)

- **2:** abort bound inside rule 5 (`:4058`); the Meldung names country, both classes, which of a/b/c and the series measured (`:4113-4116`); probe SAU + SAMA stage 1 written out `:4118-4131`, derived play-only = manifest, build runs.
- **4a:** `:4858-4864` — past tense, "before this package", plus "T18b is that master since `0177`". `partie.runde` before section 25 today: `:1420`, `:1428`, both inside T18b — consistent.
- **4b:** `:1423-1425` now says section 25 "deliberately holds open" the three bounds, prescribing *that* not *which* — matches `:4919-4923`.
- **5:** `:5007-5009` carries anchor + "read 2026-09-08"; quote verbatim at `spiel.md:3330` (T58 row) at HEAD.
- Side checks: 27 target series = `reihen.toml:456` (`sollreihen_gesamt = 27`, `frei` 23); c's quote verbatim at `spiel.md:1015`, heading `spiel.md:859`; "Belongs to T61" at `spiel.md:3253`; document preamble untouched (`:46` T1–T53, T60-as-free-example `:56`) — 0082/0084/0181 keep their anchor.

Searched, found nothing: a new T-number (none added); T6x tokens in the four out-of-T61 edits (none); a second "solely"-type class sentence outside T61 (`:3984`, `:4002-4008` stay true — stage 4 remains a sufficient ground, the marking duty sentence is about `stufe`, not the class).
