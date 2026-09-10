---
id: 0287-daten-md-nr-7-erlaubt-und-verbietet-eurostat-zugleich
rolle: architekt
status: gebaut
haengt_an: []
vermerk_annahme: "ANGENOMMEN 2026-09-10 (24. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt unveraendert. Vorgeschlagen vom `daten-pruefer` aus Bedingung 3 seiner zweiten `0280`-Pruefung. **`haengt_an` geleert: `0280` steht in genau diesem Lauf auf `fertig`, die Vorleistung ist erfuellt und damit wirkungslos.** || **DIE VIER PRUEFUNGEN.** *Rolle* `architekt` -- und das ist hier der Kern der Sache, nicht Formalie: **nur der Architekt hat `Edit(specs/**)`.** Ein Datenbauer, der eine Zahl nach `reihen.toml` traegt, **kann** diesen Widerspruch nicht aufloesen, auch wenn er ihn sieht. *Dateischnitt*: `specs/.../daten.md` -- **eine eigene Spur.** `technik.md` ist eine andere Datei; `0236` laeuft heute Nacht darauf, und ihr stoert euch nicht. *Abnahme*: vier Bedingungen; Bedingung 1 verlangt **eine** Antwort an **einer** Stelle, Bedingung 3 zaeunt ein, was unangetastet bleibt. *Vorleistung*: erfuellt. || **WAS DU AUFLOEST.** Abschnitt 7 von `daten.md` sagt zweimal Verschiedenes ueber dieselbe Frage. Lizenzteil `:195-198`: kommerzielle Weiterverwendung gegen Namensnennung erlaubt, und die Ausnahme `:203-208` -- Nicht-EU/EFTA -- **erreicht Deutschland und den Euroraum nicht.** Sechs Zeilen tiefer, `:210-214`: *„die falsche Quelle fuer ein Weltmodell mit zwoelf Laendern ... Nicht einplanen.\"* **Ein Leser bekommt heute zwei Antworten und muss zwei Absaetze gegeneinander abwaegen.** || **DER BODEN DES ZWEITEN HALBSATZES IST GEMESSEN FALSCH, und das ist der eigentliche Befund.** `:212` begruendet das Verdikt mit *„dort haben WDI und IWF dieselben Groessen ohne Sonderregel\"*. Das ist eine empirische Behauptung. `daten/quellenbefund-leitzinspfad.md` (Paket `0234`, ueberarbeitet `0241`/`0252`/`0253`) hat fuer **DEU** gemessen: WDI ist in allen fuenf Zinscodes des Themas 7 und in `FR.INR.MMKT` leer, `IMF.STA/MFS_IR` liefert nichts Brauchbares. **Fuer genau die eine Groesse, an der der kritische Pfad haengt, sind die EU-Laender nicht anderswo abgedeckt.** Bedingung 2 laesst dir beide Ausgaenge -- den Satz behalten und die widersprechende Messung danebenstellen, oder ihn berichtigen -- **aber er zitiert danach die Datei.** || **DAS IST KEIN GATE, und ich sage es, damit du nicht vorsichtshalber eines schreibst.** Eurostat steht bereits als **geprueftes** Quelle Nr. 7 in `daten.md`, mit seinen Bedingungen im Wortlaut; `daten/lizenzbefund-reihen.md:248` sagt es. Kein Geld, keine Aussenwirkung, kein neuer Lieferant -- **ein Abschnitt wird mit sich selbst einig.** Die Namensnennungsform ist bereits nennbar: `Quelle: 10.2908/IRT_ST_A, 2026-09-09`. || **WAS DU AUSDRUECKLICH NICHT ENTSCHEIDEST, und das ist die Falle dieses Pakets.** `0280` hat einen **Geldmarktsatz** fuer `geo=EA` und eine **Anleiherendite** fuer `geo=DE` gefunden -- **keiner von beiden ist ein Leitzins.** Welchen davon Reihe 9 bekommt, oder ob die Antwort Weg 1 (BIS/EZB, dann Gate) heisst, ist eine **andere** Entscheidung und wird nicht dadurch beantwortet, dass du ein Lizenzverdikt richtigstellst. Bedingung 3 haelt dich fest: **keine Quelle wird zugelassen, keine faellt weg**, und der Nicht-EU/EFTA-Ausschluss bleibt Wort fuer Wort stehen. Bedingung 4: nichts ausserhalb Abschnitt 7. **`daten/reihen.toml` fasst du nicht an** -- `deckung_urteil = \"reisst\"` (`:1256`) bleibt stehen, das Nachziehen ist der Folgelauf eines Datenbauers. || **`daten.md` IST EIN DEUTSCHES DOKUMENT und bleibt es** (CLAUDE.md: ein Dokument, das mittendrin die Sprache wechselt, ist unlesbar)."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/daten.md]
abnahme: "1. Section 7 of `daten.md` resolves the contradiction **in one place**: its licence part permits DEU/EA, its verdict at `:210-214` says `Do not plan it in`. After the package, a reader gets one answer to `may a Eurostat series be planned in for the model's EU countries?` without weighing two paragraphs against each other. 2. The ground the verdict rests on -- `:212`, `there WDI and IMF have the same quantities without a special rule` -- is either kept **with the measurement that contradicts it named**, or corrected: `daten/quellenbefund-leitzinspfad.md` (package `0234`, revised `0241`/`0252`/`0253`) measured DEU empty in all six World Bank interest-rate codes and in `IMF.STA/MFS_IR`. Whichever way it goes, the sentence cites the file. 3. The exceptions and the attribution form (`:200-208`) are **unchanged** -- no source is admitted, none dropped, the non-EU/EFTA exclusion stays exactly as worded. 4. Nothing outside section 7 is written. Carrying a value into `daten/reihen.toml` series 9 is the datenbauer's follow-up and stays out of this package."
---

# `daten.md` Nr. 7 permits Eurostat and forbids it, in the same section

## The finding

Package `0280` measured Eurostat for the German policy-rate path and its licence answer is
confirmed (`befunde/pruefung-0280-...-2026-09-09-2.md`, condition 3, re-read against the spec):
`daten.md:195-198` authorises commercial reuse against attribution, and the exception at
`:203-208` — non-EU/EFTA countries — **does not reach Germany or the euro area.** Both are EU.
Permitted, and the attribution is nameable: `Source: 10.2908/IRT_ST_A, 2026-09-09`.

Six lines further down, the same section says the opposite (`:210-214`):

> **Verdict:** the wrong source for a world model with twelve countries … It would remain usable
> only for the model's EU countries, and there WDI and IMF have the same quantities without a
> special rule. **Do not plan it in.**

## Why the second half no longer holds

Its reason is an empirical claim, and it has since been measured false for the case that matters.
`daten/quellenbefund-leitzinspfad.md` (`0234`): for **DEU**, WDI is empty in all five interest-rate
codes of topic 7 and in `FR.INR.MMKT`, and `IMF.STA/MFS_IR` returns nothing usable. The verdict
assumed the EU countries are covered elsewhere; for the one quantity the critical path is blocked
on, they are not. `0280` then found a euro-area money-market rate gapless over 21/21 window years.

## Why this is its own package and not part of the follow-up

The follow-up carries a number into `daten/reihen.toml` series 9. That is a datenbauer, and a
datenbauer **cannot write `specs/`** — only the architekt has `Edit(specs/**)`. So the follow-up
has exactly two bad options: plan in a source whose spec section says do not plan it in, or stop.
Either way the decision gets made by whoever happens to run next, silently, in a file that is not
the spec. It belongs in the spec, before the number moves.

Nor is it a gate. Eurostat already stands in `daten.md` as vetted source Nr. 7 with its conditions
in wording; `daten/lizenzbefund-reihen.md:248` says so, and the project manager's own vermerk on
`0280` states it: *„THIS IS NOT A GATE AND NOT A NEW SOURCE."* No money, no outside effect, no new
supplier — one section made self-consistent.

## What this package must not do

Not decide the concept question. `0280` found a **money-market rate** for `geo=EA` and a **bond
yield** for `geo=DE`, neither a policy rate; which of them series 9 gets, or whether the answer is
way 1 (BIS/ECB, a gate), is a separate decision and is not settled by fixing a licence verdict.
