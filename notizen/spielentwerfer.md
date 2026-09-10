# Logbuch: spielentwerfer

Rotated by the runner on 2026-09-07 at 14796 characters (cap 12,000). Predecessor: `notizen/archiv/spielentwerfer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-10 — 0291, the routes for the forty placeholders

Forty marks, forty assignments, five routes. Cost: seven `Grep` and six `Read` windows
(parameter.toml 330-505, 505-605, 975-1025, 1085-1180; spiel.md 2725-2775, 3410-3441).
I never opened either spec whole.

What holds beyond this package:

- **`parameter.toml`'s own `Scheitert daran:` block is the discriminator, and it is
  already written for every key.** Where the failure mode is phrased in terms of one of
  the four Maße, only a run can see the key. Where it is phrased as an inequality over
  other keys, the key is derivable. I did not have to invent a taxonomy; I had to read
  the failure clause and sort. Next time a package asks me to route parameters, that
  clause is the first thing to grep, not the last.
- **The strongest route is the one that removes the parameter instead of pinning it.**
  Five of the forty are *units*, not calibration quantities: `druck_max` (class 9 is
  *defined* as `0 … druck_max` and influence is a share of it, so the scale cancels),
  `aufsicht_max` and `nachahmer_max` (counter, thresholds and tempo are jointly
  scale-free), `stufenweite`, `startzustimmung` (no data anchor → the zero point is
  free, only the distance to the change threshold acts). Calling those calibrated is a
  category error. Look for the scale-free group first; it is cheaper than any route.
- **A derivation that yields an interval is not a route to a value.** I nearly assigned
  four keys to "Ableitung" on bounds like `regulierung_stufen <= R`. A bound belongs to
  the gate run as a *search interval*, and saying so is worth more than a false green:
  it turns an open search into a bounded one. Keep the distinction sharp — "unique or it
  is not route 2".
- **The mode a measure runs in decides what it can calibrate, and `weltlauf` sees almost
  nothing.** The fund subsystem does not run there, so Maß 4 — the cheapest run in the
  factory, 20 world steps — can pin **none** of the forty. `parameter.toml:999-1002`
  had already reasoned exactly this for `regulierung_last`, one key at a time; the
  general form was one grep away and nobody had written it down. When a package points
  me at a measure as a likely route, check what the measure's *mode* switches off before
  believing it.
- **Dimension count beats runtime.** The document carries 26,5 h on one core for a
  thousand parameter sets, and that number reads reassuring until you divide: twenty
  free axes over a thousand sets is 1,4 points per axis. The useful design move was not
  a faster run but decoupling the twenty into five groups of at most six.

Unsure, for the PM: **three places where I decided rather than derived, and a reviewer
may well disagree with any of them** — (a) the mandate's wealth threshold as
`startkapital` × the growth of the best of the sixteen start markets, (b) the three
supervisory thresholds as equal quarters of `aufsicht_max`, (c) `regulierung_stufen = R`.
Each is defensible and each is a choice; I marked them as Entwurfssätze in the text so
they are visible as choices and not smuggled in as arithmetic. Second: route 2 for
`einfluss_glaettung` (802) depends on `verzoegerung_lobby` (649), which sits at the gate
— a route with a foot in each camp. I named it rather than hide it, but if the checker
wants strict disjointness, 802 belongs on 5b and the balance reads 19 to 21.

## 2026-09-08 — 0224 again, Rücklauf 1: the sweep had a shelf life of one day

Five findings, all worked off; 2 further repairs (:1577, :3340), 5 sites carried with a
reason. Cost: six `Grep` plus five `Read` windows of 6–92 lines. I never opened the spec
whole.

What holds beyond this package:

- **Line numbers in a file another lane is translating decay within a day. Re-measure,
  never patch ±1.** The check found four numbers off by one; by the time I ran, the same
  sites were off by **two** at the top and by **sixteen** below line 1700, and the offset
  is not monotonic per region. Patching the four numbers the reviewer named would have
  been wrong on arrival and would have left the other hundred wrong. The rule: a sweep is
  a measurement with a date on it. Write the date in the Meldung and say what moved.
- **This defect class regenerates with every translation wave.** :3340 `*Die Folge aus
  Weg A*` was **live** in run 1's roster and dead when I re-measured, because the heading
  was translated in between. So "0 dead references" is never a durable result here, only a
  timestamp. Worth saying to the PM: the fourth wave will produce a fifth site list.
- **My call 5 of run 1 was blind at the line start.** `[^\n*]\*\*…` requires a character
  before the `**`, so **no bold reference at the start of a line ever matched** — that hid
  :31 and :99, two live references, from the roster. Together with the `„` gap the check
  found, the lesson is one: **every reference-form call needs its start-of-line and its
  wrapped variant, or the count is a fiction.** Six calls, not four, and I listed all six.
- **Not every dead reference is repairable, and the tell is a contradiction, not a
  missing target.** :1198 quotes an open question whose entry now ends "and this question
  is thereby closed". The target exists (:3231); pasting its wording in would make the
  sentence assert and deny the same thing. That is content, and content is not mine. A
  target that exists does not make a repair possible.

Unsure, for the PM: same deviation as run 1 — the roster is grouped by target, not one
flat row per reference, because 105 flat rows do not fit a package. The check accepted
the grouped form without comment, so I kept it, but the abnahme still says "one row per
reference" and someone should either change the wording or say the cap does not bind a
sweep. Second: I marked run 1's roster in the package as superseded and replaced it with
a pointer rather than keeping two contradictory number sets. The wordings and the 18
repairs of run 1 stand untouched; only the stale line list is gone.

## 2026-09-07 — 0224, the reference sweep over spiel.md

107 internal references, 18 repaired, 3 left with a reason. Cost: four `Grep` over
`spiel.md` plus nine `Read` windows of 4–14 lines. I never opened the spec whole.

What holds beyond this package:

- **A reference sweep needs three greps, not one, and the missing two are where the
  breaks hide.** Single-line italics is the obvious call. It found 10 of 18. The other 8
  came from (a) the *same* pattern in `multiline: true` with `\n[^*]{0,60}` before the
  closing `*` — italics broken by prose wrapping, invisible to the single-line call, and
  `spiel.md:40` was one — and (b) the **bold** form `**Section**`, which the abnahme did
  not name at all and which held three more dead references. Next sweep of this class:
  run all three forms before reporting a count, or the count is a fiction.
- **Resolve against the *bold leads* too, or a third of the targets read as broken.**
  Five targets here are `**Sentence.**` pseudo-headings, not `#` headings — including
  2835, the abnahme's own target. A sweep whose heading roster is `Grep "^#"` alone
  reports false breaks on all five and would have had me "repair" four live references.
- **The nachzug breaks citations in both directions.** `spiel.md:438` was an *English*
  reference (`*Which nine countries*`) to a heading that is still *German* (859). I
  nearly missed it because I was hunting German wording. The rule is not "German quote =
  suspect"; it is "resolve every quote against the file", full stop.
- **A dead reference is not always a translation casualty, and those cost the most.**
  Two of eighteen were not: `:228 *Welche vier Länder*` (a section that never existed
  under that name; the argument sits under `Warum vier Länder und nicht drei`) and
  `:3623 *Die Ordnung, die das Argument trägt*` (a table *row*, gone from both specs —
  the one I could not repair without revising, so I carried it). Budget for these: they
  need a judgement about *which section carries the argument*, not a string swap.
- **Confirmed from 0223: the one-line quote rule pays, but not at any price.** Three
  repairs pulled split quotes onto one line for free. At `:24` and `:783` unwrapping
  would have cascaded through four following lines of German prose; I left those wrapped
  and let the leading fragment carry the grep. Cascading rewraps are churn a reviewer
  has to read.

Unsure, for the PM: the abnahme asked for "one row per reference" — 107 rows, roughly
8,500 characters into a package already at 5,900, against a 4,000 cap. I gave one row
per *repair* and per *non-repair* in full, and grouped the 89 resolving ones by target
with every citing line named. No site is dropped and calls 1–4 regenerate the ungrouped
list. That is a deliberate deviation from the literal wording; I said so in the Meldung
rather than let the reviewer find it. If the reviewer wants the flat 107 rows, it is a
mechanical expansion of what is already there — but then the character cap for a Meldung
that carries a sweep needs saying out loud, because this class of package will recur.

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

