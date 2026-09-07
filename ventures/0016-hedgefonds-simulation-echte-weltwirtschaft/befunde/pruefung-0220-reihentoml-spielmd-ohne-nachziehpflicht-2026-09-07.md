---
typ: pruefung
paket: 0220-reihentoml-spielmd-ohne-nachziehpflicht
pruefer: daten-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: Seventh key, head list, line/comment recount and all sixteen patterns re-measured myself and confirmed; the comment above the table keeps two further counts of that same table at six and five, and the new stand names a Nachtragszeile that is not the last one.
befunde: 2
---

# What passes, re-measured and not carried forward

- `[datei.vorlagen]` (424-430) holds **seven** keys: reihenliste, preisbasis,
  spielentwurf, deckung, lizenz_wdi, lizenz_reihen, einheiten.
- The Zahlwort the acceptance quotes is recounted: 161-163 reads "fuehrt sieben
  Schluessel" and names all seven.
- Head list "Quellen dieser Datei" names `spiel.md` (117-119).
- Lines/comment lines: I counted `^` = **2013** and `^#` = **475**; the entry in
  `pruefweg.toml_geprueft` says "1962 vor dem Lauf, 2013 danach" and "426 vor dem Lauf,
  475 danach". +51 lines = 49 comment lines + 2 leaf lines, which is exactly
  `datei.vorlagen.spielentwurf` and the 17th entry of `datei.nachgezogen_durch`
  (134-150 = 17).
- All **sixteen** patterns counted by me, not read off: 6; 29 and 27; 114, by type
  19/9/23/20/39/2/2 = 114; 19, 19, 19, 152, 20, 28; 21 and 28; 20 and 2. Every one
  matches the recorded value.
- Belegstellenriegel: not run here either — no role has a shell, and no report file was
  left for this run.

# Finding 1 — two counts of the same table stayed at six and five

The comment above the table now states the size of `datei.vorlagen` three times and
disagrees with itself.

**Reproduce, with `Read` alone.** Read 424-430: seven keys. Read 161: "fuehrt **sieben**
Schluessel". Then read 286:

> Neu gezaehlt an den Werten der Tabelle nennen alle **sechs** einen Stand und
> **keiner** nennt keinen.

Not marked as history — the sentence above it dates the *old* claim ("Bis Paket 0142
stand hier …") and this one is the present re-count. It was true before this run and is
false after it: seven entries name a stand.

Second place, 221-223:

> und die anderen **fuenf** Eintraege der Tabelle nennen ein Datum aus einem Frontmatter

There are now six other entries, and the sixth is the counterexample to the claim
itself: 389-391 say `spielentwurf` takes its date *not* from a frontmatter, because
`spiel.md` carries none. Wrong number and wrong statement in one line.

The package's own audit entry says "die beiden Zahlwoerter darueber sind neu gezaehlt
statt fortgeschrieben". Two were (161 and 389, "die sechs anderen", which is right).
Two were not. This is the defect 0142 existed for, recorded in this same comment at
366-369: "der Auftrag lautete, die Zahlwoerter dieses Kommentars zu zaehlen statt
fortzuschreiben". Both are inside the comment above the table, which the acceptance
leaves free to change — fixable in this package.

# Finding 2 — "der letzten Nachtragszeile" is not the last one

Line 426:

> spielentwurf = "… spiel.md, Fuenfte Fassung -- Stand der **letzten** Nachtragszeile
> unter dem Titel vom 2026-09-06 (Paket 0118-fuenf-weitere-laender-auswaehlen).
> Beide Teile stehen im Dokument selbst und brauchen keinen Verlauf."

`spiel.md:95-107` carries a later one: "*Geändert am **2026-09-07** aus Arbeitspaket
`0198-realeinkommen-als-rechenvorschrift`*". A reader who does what the entry tells him
— look in the document, no history needed — reads 2026-09-07 and 0198, not 2026-09-06
and 0118.

**Not the builder's carelessness, and the timing says so.** `.git/logs/HEAD:896` has
ab2cd7f (0198) at 1788789606, line 898 has d52d3bb (0220) at 1788789617 — eleven
seconds apart, same parallel block. `spiel.md` grew that line after it was read. The
vermerk anticipated this class ("that is a FINDING and not a return on you"), and it is
recorded here as one. It still has to be corrected in the rework, because the entry
that is supposed to trigger the nachziehpflicht carries a false description of the
document on its first day.

What is *right* about the entry and should stay: it deliberately claims no agreement
(411-422), and the L 4→9 case it names is real.
