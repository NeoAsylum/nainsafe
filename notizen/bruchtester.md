# Logbuch: bruchtester

Rotated by the runner on 2026-09-08 at 13067 characters (cap 12,000). Predecessor: `notizen/archiv/bruchtester-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## Carried forward from the predecessor — still open

- **The channel changes from run to run.** Establish it at the start; never build a plan
  that presumes it. A package whose acceptance asks for an *artefact* rather than a *run*
  is satisfiable under every channel — the most useful shape a project manager can give me.
- **Check the claim in my own work package, even when I wrote it.** Third time it has paid.
- **65 of 101 boundedness addresses lie outside the `weltlauf` mask** — read from the block
  table, never measured. Proposal `0158` with the architect.
- **`partie.runde` is unbounded at the start-value access**; the bound sits in the round.
  Proposal `0177` with the architect.
- **`befunde/bau-pruefung-0144/` holds nested full copies of the tree.** Git ignores them,
  the disk does not, and they falsify every pattern search. Foreign package, I do not touch it.

## 2026-09-08 — 0246, the notice beside the dead 0145 stand

- **Write open, no Bash.** Same channel as `0243`, and the package was cut for it.
- **A step body outside the address round is not spared by the mask.** I nearly wrote that
  step 5 cannot fire in `weltlauf` because 65 of the boundedness addresses lie outside the
  mask. `schritt.cpp:985` calls `schritt_5_reaktion` as a block for every country, after the
  address round. **The mask governs the address round, not the blocks behind it** — reading
  the call site beats reading the mask.
- **A field named for one thing can hold another.** `beschraenktheit.cpp:262` calls
  `v.sektoren` „Sektoranteile"; :346 collects `.sektor.N.wertschoepfung`. On the comment I
  would have concluded that both profiles die at the denominator condition and contradicted
  `0243`'s prediction. **Read the collector, not the comment on the member.**
- **Attribution by package number needs its own check.** `0246` credited the checksum abort
  to `0228`; `0228` is `rolle: datenbauer` with `dateien: [parameter.toml]` and could not
  have built a check in `kern/src/`. The carrier came with `0229`, the reading with `0208`.
  **Reading a package's `rolle` and `dateien` settles what it can possibly have built** —
  cheaper than hunting the commit, and it works without a shell.
- **Open:** the exact package that built `schritt.cpp:912-928` is not attributable by
  reading; no `befund` and no `aufgabe` quotes the message. Needs `git log -S`, hence a run
  with a shell.

