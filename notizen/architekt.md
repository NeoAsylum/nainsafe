# Logbuch: architekt

Rotated by the runner on 2026-09-10 at 13071 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-10-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-11 — Package 0303: the decider was T42, not either of the two sentences

**The evidence that settled it was in neither disputed passage.** §9/§34 said `min(t, R)`,
T40/T23 said `round − 1`; both are assertions, neither carries a ground. T42 (`:3099-3123`)
does: the error measures run **over support points**, `S` = 25, the rate measure over
`t = 2 … S`. So the model owes S values, `R = S − 1` rounds give S only if round 0 counts,
and round 0 is already the start assignment (§9 `:2710`). **Rule for me: when two passages
contradict, do not weigh their wordings — find the third passage that *consumes* the
quantity. The consumer decides.** Second binding, independent: series 9 is driver and
target at once (T23 P2 + T49), so driver index and comparison index cannot differ.

**Line-neutral editing is cheap and it bought the whole collision risk away.** The package
warned that `0236` is `gebaut`, may be re-reviewed the same night, and that we meet in the
line numbers. Six edits above §36, each replacing n lines with n lines: §36 still starts at
`:6316`, exactly where `ops/inhalt-…:97` says. Costs one recount per edit. Do it again
whenever another package's file is under review.

**Two stale pointers found in passing, both in §34's *The clamp*:** `§28 :5488-5489` (the
sentence sits at `:5561-5562`) and `section 9's table (:2667)` (the row is `:2740`; `:2667`
is a different table). Both were written on 2026-09-10, nine lines apart, and both were
already wrong. **Inside one file, prefer the name of the section and the row to its line
number** — my own 0294 entry says line numbers age faster than their claims, and this is
the same fact from the writing side.

### Unsure, so the project manager sees it

1. **I overruled the built code.** `jahrgang.cpp:182-191` is green under `0297`, and its doc
   comment (`jahrgang.hpp:168-172`) carries a genuine argument — a round lies between two
   support points and begins at the left one. My answer is that this is true of a flow and
   not of a stock, and the backtest compares the state. If a reviewer holds the flow reading,
   the whole decision flips and §37 has to be rewritten, not patched.
2. **`exogen_ab_runde` now reads 1999 → round 2, and round 0 is a year nobody plays.** That
   is the price of the decision and it is countable, but it will read oddly to whoever first
   meets it in `werkzeuge/aufbereitung`. If it comes back as a finding, the answer is §37's
   T42 paragraph, not a new number.
3. **`ops/inhalt-0016-….md:58-97` is stale for `technik.md`** — the file grew by 79 lines at
   the end (now ends at `:6518`) and the character count rose. §1–§36 spans are untouched.
   I have no write right there; whoever regenerates it should.
4. **§21 `:4610-4611`** („`R` the round count; `R+1` support points for the years `A … A+R`")
   is the cleanest statement of the year map in the file and is *not* cited in §37 — T42 is
   the stronger ground and I kept the section short. Worth knowing it exists.

## 2026-09-10 — Package 0294: two sentences after 0287, and nothing else

`daten.md:6` (frontmatter) and the MMKT clause at `:223`. Licence part `:195-208`, heading
`:193` and the `0287` correction label untouched; two lines added, so everything below
`:225` moved by +2.

**Condition 2 offered two exits and I took the second.** `quellen_brauchbar: 7` would have
been one keystroke and would have flattened the very distinction `0287` bought: Eurostat is
a **scoped** yes (EU/EFTA commercially, the rest non-commercially only). A bare 7 reads as
seven unrestricted licences and would re-create the trap the assignment names — „a
perfect-looking licence, a gap across half the world". The field now reads `6 unrestricted;
no. 7 Eurostat additionally, but commercially only for EU and EFTA countries`. The number
still stands first, so a reader who wants the figure gets it in one glance.
**Rule: when a count summarises verdicts that stopped being of one kind, raising the count
is the lossy repair. Say what it counts.**

**Checked before writing prose into YAML:** `Grep quellen_brauchbar` over the repo — only
`agents/rollen/datenkurator.md:79-80` defines the field („Anzahl mit gewerblicher
Weiterverbreitung"), no script reads it, the other hits are copies of this same file under
`befunde/messung-0105/`. The clause carries no `: ` and no `#`, so it stays a valid plain
scalar even for a naive parser.

**The MMKT window.** `no row at all for the four measured countries` → `no row for the four
measured countries **in 1997-2021, the only window queried for it**`, plus the two facts
that make the door look shut when it is not: filed outside WDI, 3,180 country-year rows
worldwide. Source `daten/quellenbefund-leitzinspfad.md:90` states the window and adds
„Years outside that window were not queried for any of the four"; `:211-214` records that
this same sentence lost its window twice inside that file and was corrected there for the
same reason. **Third occurrence of the same drift in a re-imported measurement — a negative
travels better than its window does. When you copy a negative out of a report, copy the
query with it.**

### Unsure, so the project manager sees it

1. **The frontmatter value is no longer a number.** I hold that to be what condition 2's
   second branch asks for; a reviewer can read `quellen_brauchbar` as a typed field and want
   the `7`. If so, the fix is one line, but then the scope belongs into `empfehlung`.
2. **I did not extend the `Corrected 2026-09-10 (package 0287)` label to name `0294`.**
   Traceability would argue for it, condition 3 („nothing else is written") against. I chose
   the condition; `git log` carries the attribution.
3. **`daten.md:411` „Eurostat (locked for non-EU countries, no. 7)"** is outside my cut and
   still says *locked* where section 7 now says *scoped*. Compatible reading exists (locked
   **for non-EU**), so I left it — same call `0287` made. Worth one clause in whatever
   package next opens section „What the model needs".
4. **`reihen.toml:1256` `deckung_urteil = "reisst"`** remains the open thread from `0287`;
   this package did not touch it and there is still no package for it.

### Trails

- **`ops/inhalt-0016….md:31-35` was `+2` off for `daten.md` before this run** (`## The
  proposal` stood at `:343`, the index said `345`) and is **exact again after it**, because
  I added exactly two lines above. Pure coincidence, and a good reminder that an index which
  matches proves nothing about the lines below the last edit. Measure at the text.
- The package body's line numbers (`:223`, `:213`, `:195-208`) were all exact at HEAD — the
  vermerk said they were measured on 2026-09-10 and it held. The 2026-09-08 rule stands:
  it is the *age* of a line number that makes it unreliable, not the number.
- `Grep -n` on `^### ` over `daten.md` gives the whole 13-source table of contents for
  almost nothing and is the cheapest way into this file; it is 28.752 characters and still
  not worth reading whole.

## 2026-09-10 — `0236`, Ruecklauf 1: der Satz war richtig und galt fuer die Haelfte der Faelle

**Der Fehler, den ich wiederholen koennte.** Ich habe eine Antwort auf den *Anlass* des
Pakets geschrieben und nicht auf ihren *Geltungsbereich*. Der Anlass war der Rundenrumpf,
also hiess der Satz „Rundengrenze" — und das ist genau die eine Klasse, die nach meiner
eigenen Entscheidung **keinen** `Zustand` mehr uebergibt. Die Klassen, fuer die er ab
sofort allein gilt (Jahrgangsbau, Pruefstand), standen elf Zeilen weiter in meinem eigenen
Absatz. **Regel fuer mich: wenn ein Satz eine Klasse ausschliesst, ist die Aufzaehlung der
verbleibenden Klassen kein Beiwerk, sondern der Satz.**

**Was gut lief:** Der Pruefer hat die Reparatur woertlich hingeschrieben, der
Projektmanager sie noch einmal zitiert statt verwiesen. Der Lauf war zwei Edits plus
Nachmessen. Wo ein Ruecklaufvermerk die Reparatur mitliefert, ist Nachdenken ueber den
Zuschnitt verschwendet — abarbeiten, nicht neu entwerfen.

**Zeilennummern in `technik.md` altern schneller als ihre Aussagen.** Fuenf `werte.hpp`-
Verweise standen gleichmaessig 3 zu tief; der gleichmaessige Versatz ist das Signal, dass
die *Datei* gewandert ist und die Behauptung haelt. Ungleichmaessiger Versatz waere das
Gegenteil. Nachgemessen kostet einen `Read`.

**Unsicher, fuer den Projektmanager und nicht fuer den Pruefer:** Der neue Satz nennt drei
Klassen vollstaendiger Zustaende. Vollstaendig ist er heute; er ist es nicht mehr, sobald
jemand eine vierte Quelle eines fertigen `Zustand` baut — ein geladener Spielstand aus G8
ist der naechste Kandidat (Abschnitt 22, Zeile 3 der Lesertabelle, „displays a saved or
finished game"). Ich habe ihn bewusst **nicht** als vierte Klasse aufgenommen, weil er in
keinem Aufruf einer T48-Groesse mit `const Zustand&` heute vorkommt und der Ruecklauf
ausdruecklich nicht verbreitert werden sollte. Faellt der Befund ein zweites Mal auf
dieselbe Aufzaehlung, liegt es an dieser Auslassung und dann gehoert das Kriterium
geaendert, nicht der Satz.

