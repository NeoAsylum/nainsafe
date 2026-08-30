# Logbuch: Verbesserer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c notizen/verbesserer.md`). Ist die Grenze erreicht,
verschiebe die Datei nach `notizen/archiv/` und beginne neu. Streichen, nicht
zusammenziehen — genau daran ist das Logbuch des Rechercheurs gewachsen.

---

## Was funktioniert

- 2026-08-29 — Ergiebigster Griff mit Abstand: **die Logbuecher nicht lesen, sondern
  erst messen.** `wc -c notizen/*.md | sort -n` bringt den Befund in einem Befehl.
  Danach gezielt einzeln lesen.
- 2026-08-29, **am 2026-08-30 zum zweiten Mal bestaetigt** — Ebene 2 des Auftrags („eine
  Formulierung wirkt anders als gedacht") ist die ergiebigste. Diesmal:
  `vorlagen/idee.md:59` verspricht einen „Recherche-Agenten" fuer die **Offene
  Fragen**, den das Statusmodell nicht enthaelt. Suchmuster fuer den naechsten Lauf:
  **jeden Satz suchen, der einen naechsten Schritt verspricht, und pruefen, ob es die
  Rolle gibt, die ihn ausfuehrt.**
- 2026-08-30 — **Der beste Einstieg sind die `ablehnungsgrund`-Zeilen am Stueck**
  (`grep -h -A2 "^ablehnungsgrund:" ideas/*.md`). Ein Fit-Filter, der achtmal „der
  Ideator stellt die Frage selbst und laesst sie offen" schreibt, hat das Muster schon
  gefunden und nur nicht benannt. Danach die zitierten Abschnitte im Entwurf gegenlesen
  (`sed -n '/^## Offene Fragen/,/^## Warum jetzt/p'`) — dort steht der Beweis.
- 2026-08-30 — **Eine Rolle, die eine Regel nur in einem Sonderfall anwendet, ist eine
  fertige Verbesserung.** `ideator.md:73` („klaere die blockierende Frage mit WebSearch")
  gilt nur fuer Anwalts-Zuschnitte, wirkt dort nachweislich zweimal und fehlt ueberall
  sonst. Nach solchen Regeln gezielt suchen: Sie sind schon erprobt, nur zu eng gefasst.
- 2026-08-30 — **Die Rollen adressieren den Verbesserer nicht, den Portfolio-Manager
  schon.** `grep -rn "Portfolio-Manager" notizen/` foerdert fertig formulierte
  Systembefunde zutage (G7-Promille, Zuschnitt der Scouts, 90-Tage-Regel). Naechstes Mal
  zuerst dorthin schauen.

## Was nicht funktioniert

- 2026-08-29 — `cat notizen/*.md` in einem Rutsch: abgeschnitten, unbrauchbar. Immer
  erst messen.
- 2026-08-29, **2026-08-30 bestaetigt** — `weg.py` und `kontingent.py` haben den
  Vorschlag wieder nicht hergegeben. Sie sagen *wo* Ideen sterben (12 von 15 am
  Fit-Filter, G7 viermal), nicht *warum*. Das Warum steht in den `ablehnungsgrund`-Zeilen
  und den Logbuechern. Beide Skripte trotzdem zuerst laufen lassen — sie kosten nichts
  und liefern die Zahlen, mit denen man den Fund spaeter belegt.
- 2026-08-30 — **Regelaenderungen wandern nicht in die bestehenden Dateien.** Die
  Zeichengrenze aus KW 35 steht in `CLAUDE.md` und `notizen/VORLAGE.md`; die Koepfe von
  `notizen/ideator.md` und (bis heute) `notizen/verbesserer.md` sagten weiter „Hoechstens
  30 Zeilen". Kein eigener Vorschlag wert, aber beim naechsten Umsetzungsvorschlag
  mitschreiben, **wer die Altbestaende nachzieht**.

## Offene Faehrten

Drei Kandidaten fuer KW 36, in dieser Reihenfolge:

- **Das Promille aus G7.** `grenzen.md:115` gibt ein Promille Marktdurchdringung vor,
  „wenn kein Vertriebskanal belegt ist" — alle drei englischsprachigen Marktprofile vom
  2026-08-30 nennen in `erreichbar_ueber` einen Kanal und rechnen trotzdem mit einem
  Promille. Faktor zehn auf jede Marge; `traegt_5000: nein` kippt in allen drei Faellen
  allein daran (Fahrschulen 1.348 statt 13.388 EUR). Der Portfolio-Manager nennt es „die
  schaerfste offene Frage, die ich nicht entscheiden darf" und hat es als Meldung 3 im
  Portfolio. **Vor einem Vorschlag pruefen, ob der Betreiber schon geantwortet hat** —
  sonst ist es eine Wiedervorlage seiner Meldung, nicht meine Beobachtung. Ausserdem
  pruefen, ob das Promille je ein Urteil *entschieden* hat: In den drei Profilen lautete
  der genannte Grund Besetzung bzw. Preisboden, nicht die Rechnung.
- **Der leere Trichter kostet zwei Rollenlaeufe am Tag.** Fit-Filter und Ideator liefen
  am 2026-08-29 und 2026-08-30 beide leer, und der Fit-Filter schreibt selbst, die
  Vorpruefung sei deterministisch (`grep -l "status: entwurf" ideas/*.md`) und gehoere
  nach der Hausregel „Keine Rollen, sondern Skripte" in den Starter. Ebene 4, kostet
  nichts. Schwach nur darin, dass es Tokens spart, die laut `kontingent.py` kein Geld
  sind — der Ertrag ist Fensterplatz.
- **`notizen/lehren.md` hat als einzige gemeinsam gelesene Datei keine Groessengrenze**
  und waechst schneller, als die 60-Tage-Pruefung sie leert: 8.405 (2026-08-29) → 12.977
  Zeichen (2026-08-30), bei 18 Rollen, die sie zu Beginn jedes Laufs lesen. Der
  Portfolio-Manager hat es selbst notiert. **Zurueckgestellt, weil es die KW-35-Mechanik
  ein zweites Mal ist** — erst vorschlagen, wenn die Datei die 12.000 dauerhaft reisst
  oder ein Lauf nachweislich daran scheitert.
