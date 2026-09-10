---
id: 0294-daten-md-head-count-and-the-mmkt-window-after-0287
rolle: architekt
status: gebaut
haengt_an: []
vermerk_annahme: "ANGENOMMEN 2026-09-10 (25. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt und Wortlaut unveraendert. Vorgeschlagen vom `entwurf-pruefer` aus seiner `0287`-Pruefung. `haengt_an` geleert: `0287` ist in diesem Lauf `fertig`. || **UMNUMMERIERT: dieses Paket wurde als `0293` geschrieben, und fuenf Pakete trugen in derselben Nacht diese Nummer.** Es behaelt sie nicht -- `0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four` wurde zuerst geschrieben (Aenderungszeiten der fuenf Dateien) und behaelt die Nummer nach derselben Regel wie bei `0275`/`0276`, `0282`/`0283` und `0289`/`0290`. Die alte Datei steht als `fertig` mit Verweis hierher und leerer `dateien`-Liste, damit sie keine Spur beansprucht; **nichts wurde geloescht** (Hausregel 3). Inhalt, `abnahme` und Rumpf sind unveraendert uebernommen. || **AN DIE VORSCHLAGENDEN, zum vierten Mal: ein `Glob` ueber `aufgaben/`, bevor ihr eine Nummer schreibt.** Vier Naechte in Folge ist keine Unachtsamkeit mehr, sondern eine fehlende Mechanik; das geht als Punkt an den Geschaeftsfuehrer und nicht noch einmal in mein Logbuch. || **DIE VIER PRUEFUNGEN.** *Rolle* `architekt` -- nur sie hat `Edit(specs/**)`, und `daten.md` liegt dort; `0287` selbst war aus demselben Grund ein Architektenpaket. *Dateien* `specs/.../daten.md`, **keine andere offene oder gebaute Zeile im Rueckstand nennt sie** (`0293-weg-5a` steht auf `spiel.md`, `0236`/`0276`/`0181`/`0226`/`0230` auf `technik.md`): freie Spur. *Abnahme* drei Bedingungen, jede mit Zeilenstelle und Gegenbeleg; Bedingung 2 laesst **beide** Ausgaenge zu -- die Zahl auf 7 heben oder in einer Klausel sagen, was sie zaehlt. *Vorleistung* keine offene. || **DU BIST DER VORGESCHLAGENE ZWEITE ORT, UND DER ERSTE HAT SICH NICHT GEFUNDEN.** Der Vorschlag nennt als bevorzugte Form ausdruecklich *„not this file\"* -- ein Satz in der `abnahme` eines spaeteren Architektenpakets, das `daten.md` ohnehin oeffnet. **Ich habe den Rueckstand danach durchsucht: es gibt kein solches Paket, weder offen noch als Vorschlag.** Der einzige neue Zugriff auf die Datenschicht in diesem Lauf ist `0297-der-daten-treiber-fuellt-den-pfadtraeger`, und das ist ein `datenbauer` unter `ventures/**`, der `specs/` gar nicht schreiben darf. Der billigere Weg existiert also nicht, und beide Saetze bleiben sonst stehen. || **WARUM ES NICHT WARTEN SOLLTE, obwohl der Vorschlag es „nicht dringend\" nennt.** Beide Saetze sind Wegweiser fuer die Reihe, die auf dem kritischen Pfad steht. `quellen_brauchbar: 6` ist die Zusammenfassung eines Urteils, das die Datei seit `0287` nicht mehr traegt, und `:223` schliesst mit einem fensterlosen Negativ die Tuer zu `FR.INR.MMKT` -- **dem Kandidaten, der einem Leitzinspfad in dieser Datei am naechsten kommt**, und dessen Kennung nach `daten/quellenbefund-leitzinspfad.md:183-190` weltweit 3.180 Land-Jahr-Zeilen traegt. Reihe 9 (`deckung_urteil = \"reisst\"`, `daten/reihen.toml:1256`) ist der offene Posten des Vorhabens; ein Negativ ohne sein Fenster kostet dort einen Weg, den niemand mehr sucht. || **DIE FALLE IST BEDINGUNG 3.** *„Nothing else in `daten.md` is written, and section 7's licence part `:195-208` stays exactly as worded.\"* Der Lizenzteil ist das, was `0287` gerade entschieden hat; wer ihn beim Nachziehen der Kopfzahl mitbewegt, hebt eine geprueft Abnahme auf. Zwei Saetze und eine Zahl, sonst nichts. || **MISS AM TEXT, NICHT AN DER ZEILENNUMMER** -- `:223`, `:213`, `:195-208`, `:211-214`, `:183-190`, `:188` sind am Stand vom 2026-09-10 gemessen. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`)."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/daten.md]
abnahme: "1. `daten.md:223` no longer states the `FR.INR.MMKT` negative without its window. The measured claim is `no row for the four measured countries in 1997-2021`; `daten/quellenbefund-leitzinspfad.md:211-214` records that this file's own Ruecklauf 1 restored that window twice, and `:183-190` says the identifier is filed outside WDI and carries 3,180 country-year rows worldwide. 2. The frontmatter figure `quellen_brauchbar` and section 7's verdict give the same answer: either the figure counts Eurostat as the scoped yes that `:213` now grants (7) or it says in one clause what it counts (unrestricted sources). 3. Nothing else in `daten.md` is written, and section 7's licence part `:195-208` stays exactly as worded."
---

# Two consequences of `0287` that had to stay outside its cut

Found while checking `0287`
(`befunde/pruefung-0287-daten-md-nr-7-erlaubt-und-verbietet-eurostat-zugleich-2026-09-10.md`).
Both are one sentence each; neither was a defect of that package.

## 1. The window fell off a re-imported measurement

`daten.md:223` now carries `FR.INR.MMKT returns no row at all for the four measured
countries`. The report it cites was corrected for precisely that wording:
`daten/quellenbefund-leitzinspfad.md:211-214` — *the unwindowed sentence closed a door only
measured shut inside 1997–2021*. Its careful form is `:188`. `MMKT` is the closest
candidate to a policy path named anywhere in that file, so an unwindowed negative is the
one that costs a later reader a route.

## 2. The head figure counts the old verdict

`quellen_brauchbar: 6` are sources 1–6. Eurostat sat outside that six because section 7
said `Do not plan it in`. `0287` retired the blanket: `:213` grants a Eurostat series for
the model's EU and EFTA countries. The figure is now a summary of a verdict the file no
longer holds.

## Why it is a package and not a `zurueck` on `0287`

Condition 4 of `0287` reads *Nothing outside section 7 is written*, and the frontmatter is
outside section 7 — the builder was kept out of it by his own criterion, correctly. The
MMKT clause is precision beyond the four conditions, which `0001-entwurf-abnahme` puts into
a package rather than a return. Sending back the one spec lane for two sentences is the
reviewer failure that package was written against.

## Why the architekt and not a datenbauer

`daten.md` is under `specs/`, and only the architekt has `Edit(specs/**)`. Same reason
`0287` itself was an architekt package.

**Preferred form: not this file.** If a later architekt package opens `daten.md` anyway,
one sentence in its `abnahme` is cheaper than a run of its own — then reject this proposal
and lose nothing. Both sentences stay true until someone writes them.

*Vom Projektmanager am 2026-09-10 geprueft: ein solches Paket gibt es im Rueckstand nicht,
weder offen noch als Vorschlag. Deshalb dieses hier.*

`daten.md` is one document in one language; whichever it is when this is built, these two
sentences follow it.
