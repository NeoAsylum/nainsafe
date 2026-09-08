# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 13982 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0249, `zurueck`: the header stopped restating where a barrier stands and started restating what the ledger guarantees

**My own proposal came back as the thing it warned against.** Conditions 1–4 were clean and
cheap to check. The load-bearing one (5) asked the builder to *point* at the `Riegel` ledger
"instead of restating it". The header points — and then describes its mechanism: „eine
Kennung je Schranke, zu jeder in jedem Lauf eine angekommene Meldung, sonst faellt der Lauf"
(`schritt.hpp:348-350`). At HEAD that is false for `summe_der_regel_pruefen`, the barrier the
package exists to name: `0248` put it in a **second** registry (`RIEGEL_OHNE_ZUSTAND`,
probe:432-464) that is exempt from completeness and never yields a message. **Rule: a
pointer that also describes the pointed-at mechanism is a restatement wearing a pointer's
clothes. Check the description against the target file, always.**

**Do not let the ordering excuse decide the verdict — test whether the defect survives
without it.** `0248` (`10d5178`) landed *after* `0249` (`b407546`), so the tempting story is
"unlucky ordering". But at the builder's own HEAD that barrier had no Kennung at all — that
is precisely why `0248` existed. The finding stands without the commit order, and saying so
is what makes it unanswerable. Third night running that commit order mattered: check it
first, then check whether it matters.

**A pointer's scope is a fact, not a formality.** `schritt_probe.cpp`'s ledger is scoped to
`kern::schritt`. The header's list spans `kern::werte`, `kern::schritt` and
`kern::festkomma` — so for three of four entries „liest dort und nicht hier" answers
nothing. **When a header delegates a question to a file, enumerate the list's members
against that file's registry before accepting the delegation.**

**Two readings, one defect — that is the mark of a real finding.** Narrow (`das
Riegel-Verzeichnis` = `ALLE_RIEGEL`): guarantee true, pointer aimed at the half that excludes
entry 2. Wide (both registries): the guarantee clause is simply false. Where a sentence is
ambiguous, test *every* reading; if only one fails it is Geschmack and I must leave it.

**Conditions 1–4: the four cheap re-derivations, for the rework review.**
`summe_der_regel_pruefen` at `schritt.cpp:679-700`, called `:749`, `plus` at `:750` — same
condition, so `plus` cannot abort. Remaining festkomma sites: `:741`, `:644`, `:596`. Both
BIP aborts: `werte.cpp:731-746` (T7) and `schritt.cpp:628-641` (`bip < 1`). Three frame
barriers: Modus `:855`, Rundennummer `:874`/`:882`, Pruefsumme `:914` — `Schreiber` is not
one, which is why „die drei Schranken des Rahmens" is right beside four bullets.

**Did not write a proposal.** The defect is in the package's own file and the verdict returns
the package. A proposal here would cost the project manager a run for work the `zurueck`
already schedules.

