---
typ: pruefung
paket: 0258-die-zahlen-der-nachtriegel-stehen-in-keinem-bericht
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "Floor traced from stumme_proben:924 to the abort at main:1610 and re-derived on the bait case in the self-test; probe set found by symbol and directory only; exit 0 in the report proves all three tables at HEAD were parsed."
befunde: 1
---

# 0258 — `geprueft`

## Non-zero when a probe names the table and yields none

`stumme_proben:920-929` selects `nennungen > 0 && tabellen == 0`; `main:1590-1611` names
the probes and returns 2, **before** the three null checks (`:1613`, `:1622`, `:1632`).

The failing input stands in the program, not only in prose: `TABELLENFAELLE` case 10
(`:1158-1161`) is `constexpr auto RIEGEL_OHNE_ZUSTAND = verzeichnis_bauen();` plus a
`.size()` line — two mentions on the mask, neither followed by `= {`, so `tabellen` is 0
and `stumm` **must** be 1, asserted at `:1251-1258`. Three silencers beside it
(`:1163-1173`): the name only in a comment, only in a message, and a second probe without
it. Without those the floor would hit every probe.

Header trace (`:129-141`) re-derived clause by clause: `tabellen` cannot exceed `nennungen`
because `finde_zuweisungen:489-506` filters the hits of `finde_woerter` (`:765` against
`:761`/`:776`); place and wording of the abort are at `:1593`. It names the raise site by
function and message, not by line number — accepted, a line number in the same file rots at
the next edit.

**The narrowing I checked and let stand.** The criterion says "outside a comment"; the tool
asks on the mask, so a mention inside a *string* is not counted either (`finde_woerter:458`,
case `:1166`). It loses nothing — a table is code, so one that stops parsing still leaves
its name on the mask — and it spares a probe that names the table in a message.

## By symbol and directory, no count, no second mechanism

`TABELLE` (`:727`), `VERZEICHNISBAUM = "test"` (`:1479`), `sammle_quellen:1393` walks and
sorts the tree. No probe file name occurs in the program; the only `.cpp` strings are the
synthetic self-test names at `:1199`, `:1204`, `:1317`. No comparison against a literal
touches a table count — they are `== 0` guards and `argumente.size() != 2` (`:1507`).
`:1601-1609` prints `verzeichnisse` (= `tabellen_zusammen`) and the probe count on stderr,
where `--output-on-failure` shows it, `:1578` on stdout too; the kennzeichen lane's
configure output (`uebersetzung-2026-09-08.md:510-514`) carries no added `message(STATUS)`.

## The tree at HEAD

`uebersetzung-2026-09-08.md:520-522` builds clean, `:529-532` `kennzeichen_riegel … Passed`,
Code 0; in the whole tree `:156-157` the same. The five red tests (`:164-168`) name no line
of `kennzeichen_riegel.cpp`: belegstellen's finding is `kern/test/festkomma_probe.cpp:259`
(`:356`), red "vorher wie nachher" (`:355`); bezeichner's list (`:440-493`) is all under
`kern/`. `Glob` mtime, oldest first: source, `.o`, binary, report.

Exit 0 is the stronger receipt: it requires `stumm.empty()`, so **all three** probes naming
the table on the mask gave one up — `werte_probe:361/371/436`,
`schritt_probe:443/453/463/464/480`, `festkomma_probe:286/296/342` (`:146` is a comment).
The third table, which the `vermerk` asked to be survived, is parsed.

## Finding 1 — the file says two and three about the same thing

`:32-33` "seither gibt es zwei Verzeichnisse statt einem" against the new `:107-109`
"Faellt die Zahl der gelesenen Verzeichnisse von drei auf zwei". At HEAD there are three
(`0257`, `805589b`). The old sentence is from `0251` and no condition asked for it, so it
carries no Ruecklauf — but a file whose subject is the count of tables should not answer
that question twice. Correction folded into proposal `0263`.

## Not guarded, and it is new work

A table parsing to **zero entries** counts as a table (`:776` increments before
`eintragsgruppen` runs) and stays silent; only the all-zero case is caught (`:1622`).
Reachable: `eintragsgruppen:567` needs `::` inside the entry, so a `using enum` in one probe
drops that table to 0 entries, the total falls 3 → 2, and no number reaches zero. The
criterion is table-granular and met; the entry-granular half is proposal `0263`.
