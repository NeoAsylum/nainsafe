---
id: 0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four
rolle: spielentwerfer
status: offen
haengt_an: []
vermerk_annahme: "ANGENOMMEN 2026-09-10 (25. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt und Wortlaut unveraendert. Vorgeschlagen vom `entwurf-pruefer` aus seiner `0291`-Pruefung. `haengt_an` geleert: `0291` ist in diesem Lauf `fertig`, und eine erfuellte Vorleistung plant nichts ein. **`ops/plan.md` Vorrang 3.** || **DIE VIER PRUEFUNGEN.** *Rolle* `spielentwerfer` -- sie hat `0291` gebaut und hat `Edit(specs/**)`. *Dateien* `specs/.../spiel.md`, und **kein anderes offenes Paket steht heute auf dieser Datei** (geprueft ueber alle `dateien:`-Zeilen des Rueckstands): du bekommst eine freie Spur. *Abnahme* sechs Bedingungen, jede mit Zeilenstelle und Gegenzitat; Bedingung 1 laesst **beide** Ausgaenge zu -- die Behauptung zuruecknehmen oder begruenden, warum die beiden Schluessel doch nicht wirken. *Vorleistung* keine offene. || **DIE BEWEISSTELLEN LIEGEN AUSSERHALB DEINER `dateien`, UND DAS IST ABSICHT.** `parameter.toml:708-710` und `:718-720` musst du **lesen**, um Bedingung 1 zu entscheiden -- schreiben darfst du sie nicht, und Bedingung 6 verbietet es ausdruecklich. `dateien` ist die Schreibliste und die Kollisionsvermeidung, nicht die Leseliste; `Read` und `Grep` hast du auf den ganzen Baum. **Das ist ausgeschrieben, weil ich in zwei aufeinanderfolgenden Naechten Abnahmen gefunden habe, deren Beleg in einer Datei lag, die der Bauagent nicht anfassen durfte** -- hier ist es geprueft und in Ordnung. || **WARUM DAS VORRANG 3 IST, obwohl es keinen einzigen der vierzig Schluessel umhaengt.** Dein Satz *„Weg 5a ist leer\"* ist das Ergebnis, das `0291` selbst sein schaerfstes nennt und ausdruecklich an den Projektmanager richtet; von dort geht es in den Bericht des Geschaeftsfuehrers und weiter in ein Gate an den Betreiber ueber zwanzig Schluessel und einen Lauf von rund 26,5 Stunden auf einem Kern. **Eine Behauptung, der billigste Lauf der Fabrik koenne *nichts* stellen, entscheidet mit, ob der Betreiber ueberhaupt um eine Nacht gebeten wird** -- und `parameter.toml` sagt von zwei der vierzig in eigenen Worten das Gegenteil. Er muss stimmen, ehe er reist, und niemand ausser dir schreibt `spiel.md`. || **DIE FALLE IST BEDINGUNG 2, und sie ist die `0275`-Falle in neuer Kleidung.** *„A list of possibilities is not a decision.\"* Eine Fassung, die 5a mit „koennte auch\" fuellt, erfuellt 1 und 3 und laesst genau die Frage offen, wegen der das Paket geschnitten ist. **Entscheide, und wenn die Entscheidung „leer\" bleibt, dann mit den beiden Kapitalstockschluesseln namentlich weggeraeumt.** || **BEDINGUNG 4 IST DIE BREMSE, nicht die Aufgabe.** Die vierzig Zuweisungen von `0291` sind geprueft (Befund: alle sechs Bedingungen halten, die vierzig Zeilennummern nachgezaehlt). Weg 3 geht Weg 5 vor, also bleiben 707 und 717 auf Weg 3 und die Bilanz bleibt 20/20 -- **es sei denn, Bedingung 1 zwingt anders.** Aendert sich eine Zuweisung, rechnest du die Bilanzzeile `:3413-3415` und die Gruppentabelle `:3436-3442` nach. Rolle die Aufzaehlung nicht neu auf; sie ist der teure Teil und sie steht. || **MISS AM TEXT, NICHT AN DER ZEILENNUMMER.** Jede Stelle in diesem Vermerk und in der `abnahme` ist am Stand vom 2026-09-10 gemessen; `spiel.md` ist gross, lies ueber `ops/inhalt-0016-hedgefonds-simulation-echte-weltwirtschaft.md` und `Grep -n` in den Abschnitt `:3299-3493`. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`) -- deshalb steht in Bedingung 3 von `0291` auch, dass keiner der vierzig auf `Kalibriert: Selbstspieler` gesetzt werden darf; daran aendert dieses Paket nichts."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: "1. **The paragraph `spiel.md:3354-3359` no longer claims that only two of the forty act in the `weltlauf`**, or it names why `abschreibungsrate` and `investitionsquote` do not, against `parameter.toml:708-710` („der Rueckvergleich (Mass 4) scheitert an der BIP-Sollreihe\") and `:718-720` („das ist die Groesse, an der Mass 4 zuerst haengt\"). Either answer is accepted; the two texts must stop contradicting each other. 2. **Weg 5a carries a decided content**: it is either empty with the two capital-stock keys explained away, or it is not empty and the section says which keys it can pin and against which target series. A list of possibilities is not a decision. 3. **The section's own fallback at `:3482` agrees with the result.** Today it says 707 and 717 „wandern auf 5a\", which the same section calls empty. 4. **No assignment among the forty changes** unless condition 1 forces it — Weg 3 precedes Weg 5, so 707 and 717 stay on route 3 and the balance stays 20/20. If it does change, the balance line `:3413-3415` and the group table `:3436-3442` are recounted. 5. **The multi-line-mark sentence `:3406-3409` is corrected**: `1125` (`[instrument.zoll]`, keys `1131-1133`) belongs in the list, making four such marks and not three, and the quote „die beiden Grenzen sind gegen den Jahrgang zu prüfen\" is attributed to `1102-1103` alone — `:1125` and `:1145` read only „Kalibriert: Selbstspieler (`schrittweite`)\". 6. **Nothing outside `spiel.md:3299-3493` is written.** `parameter.toml` stays untouched; the role has no write right to it."
---

# Weg 5a is not empty, and the multi-line marks are four

From `befunde/pruefung-0291-wie-die-vierzig-platzhalter-zu-ihren-werten-kommen-2026-09-10.md`.
Package `0291` is `geprueft` — all six of its conditions hold. These two are precision
beyond them, which `0001-entwurf-abnahme` puts into a package rather than a second design
round.

## Why this is its own package and not a note on `0291`

`0291` delivered forty correct assignments. Neither finding moves one of them: Weg 3
precedes Weg 5, so `abschreibungsrate` (707) and `investitionsquote` (717) keep route 3
whatever 5a turns out to hold. Sending the spec lane back for a sentence that changes no
assignment would be the reviewer failure `0001` was written against.

But the sentence is not decoration. **`0291` calls „5a ist leer" its sharpest result and
addresses it to the Geschäftsführer**, who forwards it to the operator as part of the
gate. The gate is twenty keys and a 26,5-hour run. A claim that the factory's cheapest run
can pin *nothing* is exactly the kind of statement that decides whether the operator is
asked for a night at all — and `parameter.toml` says the opposite about two of the forty
in its own words. It has to be right before it travels, and it cannot be fixed by the
Geschäftsführer, who does not write `spiel.md`.

## The contradiction, in three lines

- `spiel.md:3355` — „von den vierzig wirken dort nur `zustimmung_elastizitaet` und
  `zustimmung_wechselschwelle`"; `:3358` — „Der billigste Lauf der Fabrik kann keinen der
  vierzig Schlüssel stellen."
- `parameter.toml:708-710` and `:718-720` — Maß 4 is precisely what these two keys hang
  on, and its target series is GDP (`daten.md:396`, WDI/PWT, load-bearing licence).
- `spiel.md:3482` — the section's own fallback moves 707 and 717 „auf 5a".

Note the contrast with `regulierung_last`: `parameter.toml:999-1002` states per key that
Maß 4 cannot see it, and `0291` quotes that correctly. The two capital-stock keys carry the
opposite sentence, and it was not read.

## What is cheap about the repair

Both findings sit inside the section `0291` just wrote, in two paragraphs. No other
document is involved, and the enumeration — the expensive part — stands and is verified.
