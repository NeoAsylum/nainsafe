# Logbuch: spielentwerfer

Rotated by the runner on 2026-09-07 at 14796 characters (cap 12,000). Predecessor: `notizen/archiv/spielentwerfer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — 0223, two sentences in *Das Realeinkommen in Gegenkraft 2*

Both findings of `pruefung-0198-...-2026-09-07.md` fixed, both **behoben**, nothing else
touched. Cost: two `Read` windows of spiel.md (2240-2314, 2355-2444), one `Grep` in
technik.md. I never opened either spec whole.

What holds beyond this package:

- **A quote is only worth its greppability.** Finding 1 existed because the German quote
  was still *true* — same substance — and therefore invisible to anyone reading for sense.
  It broke only for `Grep`. When I cite a document that another lane is translating,
  the quote is a dangling pointer by default. Cite with the line number next to it
  (`(technik.md:1379)`), and keep the quoted words on **one line** in my own file — a
  quote split by prose wrapping fails the same grep the translation broke.
- **Invariants I write get encoded as tests, so the premise is the payload.** Finding 2
  was not a wrong rule but a wrong *sentence*: "cancel exactly if quantity and `bip` are
  unchanged" is true everywhere except at the clamp, and `min`/`max` in the update was
  three lines above my own claim. Rule for the next section: whenever I claim a
  cancellation, a conservation or a "leaves X where it was", I check every `min`, `max`
  and `sgn` between the two ends first, and write the excluded case into the sentence
  with numbers. Both fixes here were one clause; finding them cost a reviewer a full run.
- **The counterexample stays in the text.** I kept 9.990 → +50 → −50 → 9.950 in spiel.md
  rather than pointing at the finding. It is 60 characters and it is the only thing that
  stops the premise from being dropped again as pedantry.

Unsure, for the PM: I put the quote on its own line after a colon, which reads slightly
stiff in a paragraph that otherwise flows. I chose greppability over the cadence. If the
entwurf-pruefer prefers the smoother wrap, the quote survives either way — only the
one-line property is lost.

