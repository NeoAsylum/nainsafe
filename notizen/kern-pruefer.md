# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 14576 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0240, `geprueft`: the fourth leftover of one shape, and this time the commit order made it

**The pattern closed at four, so the finding became the rule.** `0197` left a false header
sentence, `0233` deleted it, `0245` repaired the enumeration, `0240` broke it again the
same night — and `0245` had already banned line numbers and site counts. Altitude was not
the cure: what moved was the **module** (`kern::festkomma` → `kern::schritt`). Proposal
`0249` asks for the rule, not a fifth nachzug. **Rule for me: when the same leftover
appears a fourth time, stop proposing the repair and propose the carrier.**

**Check the commit order of the neighbours, not just their status.** `0245`'s Vermerk said
„`0240` runs before you"; git says `52a31a0` (0245) then `b3c417c` (0240). A reviewer of
`0245` measuring against *its* HEAD passes it, a reviewer of `0240` sees a file outside its
`dateien` — and the gap falls between the two. **Two packages that touch a shared truth in
one night: read `git log` order before believing either Vermerk.**

**A guard that shadows a barrier kills it.** `summe_der_regel_pruefen` aborts on exactly
the pairs that would overflow `festkomma::plus` one line later — so `plus` at
`schritt.cpp:750` is now dead as an abort site. „Set of aborting states unchanged" was
satisfied, but a *third* thing changed that nobody asked about: **which** site reports.
Any header or ledger naming the old site is now wrong. Look for this whenever a package
puts a pre-check in front of an existing abort.

**Where the invariant actually lived.** The probe's comment (`:1576-1579`) claimed
`PRUEFE(abgebrochene == 2)` guards it; that loop calls `festkomma::plus` directly, a file
outside the `dateien`. The guard was in fact covered — by `ZUSTIMMUNG_AUSSERHALB` holding
`I64_MAX` and `I64_MIN`, which run through `schritt` with `wirkung == 0` in two other
probes. **Rule: to test whether an assertion carries a claim, mutate the guard by one at
each edge and ask which line goes red. It is often not the line the comment names.**

**Message count, third time, cleared fast.** 279 prose + ≤28 address + 23 + 20 + 23 + 20 =
393 against 511. The method (chunks of ten, prose separate from address separate from
digits) now costs a few minutes and has paid twice. Keep doing it.

**Precedent beats first principles on T6.** The builder's own Vermerk called an i128 clamp
in `schritt.cpp` a T6 violation, then wrote an i128 *comparison* there. `werte.cpp:731-734`
does the same and I passed it as 0242. **Grep `src/` for the construction before arguing
about a rule — this venture answers most T6 questions by precedent.**

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

## 2026-09-08 — 0245, `geprueft`: the entry was right, the sentence comparing it to the others was not

**Check the criterion's own search boundary before you sink a package on what lies outside
it.** Two defects, both in the first entry of the same list: it is called dormant and is
not (`schritt_probe` fires it), and `werte::bip` aborts a second way that the list never
names. The second is as old as `0197` and invisible from `schritt.cpp`, which is where
condition 1 sent the builder. **A criterion that names the file to read also bounds what I
may hold against him** — otherwise I raise it, which my role forbids. Both left as
findings, one proposal (`0249`).

**"Walked today" is three different predicates, and a contrast sentence mixes them.**
Abort code never reached (`schaden`, `continue` at `:592`) / code reached, condition never
true today (`bip < 1`) / code reached and the abort demonstrably firing in a probe. The
builder's "anders als die beiden Eintraege davor" is right about the first and wrong about
the second. **When a header contrasts entries by liveness, test each entry separately
against a probe** — `BRICHT_AB_MIT` plus a green `ctest` line is the whole proof.

**The package text can be wrong about the source and the builder right.** The `vermerk`
said two paths and put the two sites at `:686/:687` inside `realeinkommenshub`; at HEAD
they are in the body of step 5, and the builder named three paths. I wrote that `vermerk`'s
premise myself in the `0233` review. **Re-derive the path list from the callers**
(`Grep politiklast\(|realeinkommenshub\(` over `kern/src` — one caller each) instead of
from the package that ordered it.

**0240 committed *after* this package, not before.** Condition 1 was written as if it ran
first. It changed nothing: all three named paths survive, and `summe_der_regel_pruefen`
aborts on exactly `plus`'s condition, so no new aborting state and no fourth entry owed.
Check the commit order before you trust a criterion's "X runs before you".

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

## 2026-09-08 — 0233, `geprueft`: the builder answered a comment claim with a second counter

**A green `static_assert` is the cheapest receipt in this venture, and it beats any
argument I could have made.** The package asked the builder to *write down* whatever the
compiler answers for a raw-array member. He wrote 2 — and then built `ohne_klammern`
(`schritt_probe.cpp:1687-1712`), the same counter with `Verbund{P...}` instead of
`Verbund{{P}...}`, reusing the header's `Platzhalter` and `FELDSUCHE_ENDE` instead of
copying them. Three further asserts (5 / 2 / 9) now carry every sentence in both files
about what an unbraced counter would say. **Rule: where a criterion says „no claim without
a compiled assertion", the strongest delivery is a second implementation beside the first,
not a deleted sentence.** I re-derived no C++ semantics: `Building CXX object ...
schritt_probe.cpp.o` in `uebersetzung-2026-09-08.md` is the proof they compiled at HEAD.

**The one gap sat in the completeness word, not in the enumeration.** `schritt.hpp:298`
says „Harte Fehler, **alle**"; `:309` says „**Zwei weitere**". Both exact about
`kern::werte` — and both blind to `kern::festkomma`, five arithmetic sites in step 5, each
`[[noreturn]]`, none of them there before 0197. Condition 5 asked for exactly those two, so
it is no `zurueck`; it is proposal `0245`, hung on `0240` because `0240` decides which
sites survive. **Rule: when a criterion enumerates („name the two X"), check the sentence
the builder wraps around the enumeration — the completeness claim gets invented there, and
it is not in the criterion.**

**Third leftover of one shape.** `0197` left a false header sentence because the header lay
outside its `dateien`; `0233` existed to delete it; `0240` is about to leave the same kind
for the same reason. **A package whose `dateien` hold the source but not the header cannot
repair what its own change makes false.** If a fourth appears, the finding is the `dateien`
rule and not the sentence.

