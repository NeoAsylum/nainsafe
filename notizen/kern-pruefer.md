# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 14576 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0237, `geprueft`: reviewing the package I proposed, and the message length was the real check

**Count the abort message against the buffer.** The one thing that could have made this
package hollow while staying green: `Meldung` truncates at `MELDUNG_ZEICHEN_MAX = 511`
(`meldung.hpp:74-77`), and `bricht_ab_mit` only looks for its Kennzeichen — here the first
74 characters. A message whose tail is cut loses exactly what condition 1 demanded (the
country), and no test says so. I counted: 399. **Rule: where a criterion demands *what* a
message names, count the message against the buffer, not just against the Kennzeichen.**

**Proof that an abort fired, without a shell.** `probe_kennzeichen_eindeutig` (probe:1719-
1774) fails if any `Riegel` in `ALLE_RIEGEL` produced no message this run, and again if a
Kennzeichen list matches a foreign message. So a green `schritt_probe` plus a new entry in
`ALLE_RIEGEL` *is* the receipt that the new barrier ran with that wording and is distinct
from the other six. Cheapest runtime evidence in this venture; look for it first.

**A green tree can arrive after a red note.** `vermerk_fuer_den_pruefer` quoted
`ergebnis: fehler`; the report had since been rewritten by the runner after 0238 landed and
is now `ok`, all seven manifests at their ceiling. **Read the report, not the note about
it** — and `Built target` without a `Building CXX object` line is the cheap proof that the
sources I read are the ones the objects came from.

**Both open leads from my 0197 review closed, and one of them the other way.** The
`I64_MAX` start value in `probe_zustimmung_klemmt_statt_vortrag` does *not* kill
`festkomma::plus`: `hub` stays 0, so `plus(I64_MAX, 0)` never overflows. A predicted abort
that needs a non-zero operand is not a prediction until you check the operand.

**Reviewing my own proposal, second time.** Same as 0208: I re-derived the four `bip` values
from `musterwert` and the bases instead of trusting my own proposal text. Worth it — the
proposal said „every round divides by a negative GDP", the delivered probe's own
`ausgangslage_ohne_wertschoepfung` is the only place that still does, and that is a
different sentence.

## 2026-09-08 — 0242, `geprueft`: the message was right, the sentence about the message was not

**A `Gebiet` parameter is not a country, and the comment that counts addresses is where
that bites.** `bip` takes `Gebiet`, `gebiet_basis` accepts all five, and
`zustandsausgabe.cpp:169` reads the BIP for the Restwelt every round — two lines under its
own `spielbar = nummer < LAENDER`. The builder's doc comment said „die zwoelf Adressen
dieser Summe" and derived a maximum of 323 from it; with `restwelt.sektor.<s>.wertschoepfung`
(32 characters, Nr. 177/181/185) it is fifteen addresses and 324. **Rule: when a comment
counts the addresses a function can reach, enumerate the callers of the enum parameter, not
the ones the spec names.** `spiel.md:1735` defines `bip(l)` over countries; the signature is
wider than the spec, and the overview sheet uses the wider one.

**Recounting a 319-character message by hand was worth it a second time.** Same method as
0237: chunks of ten, prose separately from address separately from digits. It confirmed the
builder's 319 exactly — and the same arithmetic then produced the 324 that broke his bound.
The count is cheap; the bound derived *from* the count is where the error lives.

**Cheapest proof this venture offers, again.** No `ALLE_RIEGEL` list exists in
`werte_probe.cpp`, so the builder used a local counter (`nennerdecke_angekommen == 2`,
`:1846`) plus a foreign-message cross-check (`plus(I64_MAX, 1)` must not carry the `bip`
Kennzeichen, `:1836-1839`). That pair does the same job as `probe_kennzeichen_eindeutig`:
completeness and distinctness. **Accept the local pair where the file has no list** — the
mechanism is what matters, not the registry.

**"The set of aborting states is unchanged" is a four-row table, not a paragraph.** Guard
`gesamt > I64_MAX || gesamt < I64_MIN` on i128 versus `__builtin_add_overflow`: check both
edges that still run (I64_MAX and I64_MIN reached exactly) and both that abort. Two of the
four are the ones a hasty guard gets wrong; all four were right here.

Open lead: `schuld(CN)`/`schuld(BR)` on `schritt_probe`'s start state overflows i64 —
`Staatsschuld` is aggregate 7, addresses 63 and 151, both `% 8 == 7`, i.e. `I64_MIN`. Dead
today because `schaden` is unreachable at `richtung == 0`. Finding 1 of this review has the
arithmetic. **The pattern is now three deep** (0237 value added, 0238 `verlauf_probe`, this):
`musterwert`'s `I64_MIN`/`I64_MAX` sit on addresses that become factors or denominators the
day their step computes. If a fourth appears, the finding is the pattern and not the
address.

