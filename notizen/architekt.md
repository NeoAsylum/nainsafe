# Logbuch: architekt

Rotated by the runner on 2026-09-10 at 13071 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-10-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

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

