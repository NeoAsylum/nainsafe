---
typ: pruefung
paket: 0270-sieben-waechter-des-apparats-haben-noch-keinen-fall
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "all eight new Sollzahlen re-derived from auswerten()'s source independently of the builder's comments; pair discipline, constants clause and green run checked against the runner's report at HEAD 7ec1e63"
befunde: 0
---

# Pruefung 0270: eight guards of the apparatus get case pairs

## Coverage

All eight guards have pairs (cases 7-14, `kennzeichen_probe.cpp:537-601`); the escape
hatch was not used and the head says so (:68-69). Guard -> case: no-abort -> 7, foreign
throw -> 8, empty list at call site -> 9, entry without list -> 10, overlong message
-> 11, MELDUNGEN_MAX -> 12, KENNZEICHEN_MAX -> 13, `alle_stuecke_in` all-pieces -> 14.
Every disturbed half has Sollzahl > 0.

## The Sollzahlen, re-derived from kennzeichen.hpp without the builder's numbers

Healthy baseline unchanged: 4 messages, 2 own + 10 foreign pairs, 0.

- 7a=1: lambda returns, the after-try branch (:275-281) counts once; nothing else moves.
- 8a=1: `std::logic_error` is the **base** of `domain_error`, so the first handler cannot
  catch it; catch(...) (:266-273) counts once, files nothing. Widening the catch files
  the message cleanly (KZ_SEITENWAND matches the wording) -> 0 != 1, red.
- 9a=4: verzeichne's empty-list report (:559-565) = 1; the entry is still filed with
  anzahl 0, and an empty list matches every text -> foreign passes vs M_OBEN and M_SEITE
  = 2; `verletzungen==0` = 1.
- 10a=3: auswerten's empty-entry branch (:444-453) = 1 (+1 verletzung) and skips the pair
  loop -> `ohne_zustand_paare>0` fails (:494-496) = 1; `verletzungen==0` = 1.
- 11a=1: 513 chars vs schreibe_ab's 511-char copy; truncation reported at :617-623. The
  head carries both Seitenwand pieces, so the truncated copy still satisfies its own pairs.
- 12a=1: fills 1-60 land (4+60=64), the 61st hits `anzahl_>=size` (:592-598). 12b at
  exactly 64 = 0 also pins HEILE_MELDUNGEN=4 — a wrong baseline reddens both halves.
- 13a=2: 9>8 rejects the message (:600-606) = 1; Untergrenze then has one message ->
  `eigene_paare>0` fails (:488) = 1. No falscher-riegel side-fire: all 9 pieces are
  "Untergrenze", present in M_UNTEN_EINS.
- 14a=2 (both pieces of KZ_BEIDE_FREMD in M_OBEN -> 1 foreign + verletzungen). The proof
  sits in 14b=0: of KZ_TEILWEISE only "verletzt" is in M_OBEN. Under any-piece matching
  14b counts 2 and 14a counts 3 (M_SEITE carries "der Stand liegt") — both red.

## Red-if-broken (deletion test on the apparatus; nothing touched)

Each mechanism, removed or loosened in the head, misses at least one exact `==`
(comparison :657): after-try -> 7a; catch(...) widened -> 8a (removed: terminate);
:559 -> 9a (3!=4); :444 -> 10a (5!=3, the empty list then matches all four messages);
truncation flag -> 11a; capacity guard -> 12a; KENNZEICHEN_MAX guard -> 13a;
all->any -> 14b.

## Remaining clauses

- Each pair differs in exactly one Aufbau field (checked all eight rows). The new Aufbau
  fields are appended after the existing ones (:343-356), so no existing row moved.
- No existing case changed, no Sollzahl lowered: the six 0264 pairs stand with the values
  `pruefung-0264-...-2026-09-08.md` derived (0/0, 6/5, 3, 2, 1, 2/0), identical setups.
- Constants clause: KZ_ZU_VIELE is `array<,KENNZEICHEN_MAX+1>` (:212-221),
  UEBERLANG_ZEICHEN = MELDUNG_ZEICHEN+1 (:237), fill counts from MELDUNGEN_MAX
  (:323-324). No written-out 8/64/512 in case data.
- Run: `befunde/uebersetzung-2026-09-08.md` at HEAD 7ec1e63 (= the 0270 commit):
  kennzeichen_probe built in both trees and Passed (kern 3/14; 14/14 green). FAELLE is a
  compile-checked `array<Fall, 28>`, so exit 0 means all 28 held. Root reds are only the
  two pre-adjudicated belegstellen head-drift lanes; no failure line names this file.
- Mitschrift capacity: worst case 12a prints ~65 stdout lines (~6 kB) < 16384;
  `vollstaendig` holds.

`kennzeichen.hpp` unchanged at HEAD (guard :494-496, empty-case print :433-439, as
recorded before this package).
