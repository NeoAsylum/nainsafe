---
typ: pruefung
paket: 0249-der-kopf-nennt-einen-riegel-der-nicht-mehr-feuern-kann
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "The one clause in scope -- the absolute negative is deleted, and the positive claim that replaced it I re-derived from schritt_probe's two registries at HEAD, not from the text."
befunde: 0
---

# Ruecklauf 2: the negative is gone, and what replaced it holds at HEAD

Scope per Vermerk: one clause of `schritt.hpp`. Conditions 1-4 stay discharged from rounds
1 and 2; I did not re-open the enumeration.

## The deletion

Gone from the closing paragraph: `waehrend die Schranken in kern::werte und kern::festkomma
in keinem von beiden stehen` and `fuer die uebrigen antwortet nur die Quelle selbst`. In
their place, `schritt.hpp:361-365`: `Ueber die beiden anderen Eintraege sagt dieser Kopf
nichts: weder dass eine Schranke aus kern::werte oder kern::festkomma irgendwo eine Kennung
hat, noch dass sie keine hat.` Across `:346-368` no clause of the form "X steht in keinem
Verzeichnis" is left -- the only negative is that refusal, which asserts nothing.

## What replaced it, re-derived from the registries

`:357-361`: `Die beiden Abbrueche aus kern::schritt heraus haben in den Verzeichnissen der
Probe zu diesem Schritt eine Kennung -- die Nennerbedingung in deren ALLE_RIEGEL, die
Schranke vor der Summe in deren RIEGEL_OHNE_ZUSTAND.`

- `Riegel::Nennerbedingung` (`schritt_probe.cpp:348`) is the seventh of seven in
  `ALLE_RIEGEL` (`:352-355`), driven at `:1593`
  `BRICHT_AB_MIT("Bruttoinlandsprodukt nicht positiv", ...)`.
- `RiegelOhneZustand::SummeDerZustimmungsregel` (`:429`) is the sole entry of
  `RIEGEL_OHNE_ZUSTAND` (`:443-449`), keyed on `KENNZEICHEN_SUMME_DER_REGEL` (`:440`).
- Exactly two of the four entries abort out of `kern::schritt`: entry 1's
  `realeinkommenshub` half, entry 2's `summe_der_regel_pruefen`. Entries 3 and 4 are
  `kern::werte::schaden` and `kern::festkomma` -- the two the refusal covers. 2+2=4.

Mechanism sentence `:353-357`, checked against `kennzeichen.hpp` and not against a probe:
completeness `Buch::auswerten:330-343` (no message -> `++fehlgeschlagen_`), exemption
`:392-394`. `zu ihnen kommt nie eine Meldung an` is structural, not contingent: both
entrances, `bricht_ab_mit:220` and `merke:269`, take the first-category type `R`, so an `O`
value can never be filed.

No path to a probe appears in the paragraph; `der Probe zu diesem Schritt` survives a move.

## Ordering, fifth night running -- and this time it cost nothing

`0249`'s rework (`7d3ed27`) is the *oldest* of tonight's five commits. None of the four that
landed after it touches `schritt_probe.cpp`: `0251` writes `werkzeuge/kennzeichen/` only
(its `dateien`, three files), `0255` writes `werte_probe.cpp` and `kennzeichen.hpp`, `0253`
and `0064` are elsewhere. The safe ground the Vermerk named held. `0255`'s edit to
`kennzeichen.hpp` added the second entrance `merke` and raised `MELDUNGEN_MAX` to 64; it
left the completeness loop alone, so the mechanism sentence is true under both HEADs.

## What I looked for and did not find

A second reading in which `die beiden` is a wrong count -- the same paragraph says `die
beiden anderen Eintraege`, which fixes the referent to the four-entry list, not to the
frame's barriers. An assertion about the *contents* of `werte_probe.cpp` or
`kennzeichen.hpp` -- there is none; only about the two registry *kinds*, which round 1's
Vermerk demanded. A placement gone stale -- both re-read at HEAD. A green tree:
`uebersetzung-2026-09-08.md:143` reports 27/27, and `Glob` orders `schritt_probe.cpp` <
`schritt.hpp` < `kennzeichen.hpp` < that report by mtime, so the report saw this header.

Proposal written out of this run:
`aufgaben/0257-die-dritte-fassung-der-kennzeichenpruefung-steht-in-festkomma-probe.md`.
