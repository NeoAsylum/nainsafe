---
id: 0003-einheit-beteiligung
rolle: kernbauer
status: offen
haengt_an: [0002-fondsbewertung-definieren]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/einheiten.rs]
abnahme: Jede Geldgröße trägt ihre Einheit im Typ, nicht im Kommentar. Ein Test, der zwei verschiedene Einheiten addiert, wird vom Compiler abgelehnt statt zur Laufzeit falsch zu rechnen.
---

# Einheiten: der Fehler, den das Dokument selbst benennt

Aus Befund 2 der sechsten Entwurfsprüfung:

> `beteiligung_wert` liefert Tausend USD und wird als US-Cent verbucht; T5 nennt genau
> diese Mischung einen Fehler.

Das Dokument widerspricht sich selbst: Es verbietet die Mischung an einer Stelle und
begeht sie an einer anderen.

## Was du baust

**Die Einheit gehört in den Typ, nicht in den Namen und nicht in den Kommentar.** In
Rust kostet das wenig — ein Wrappertyp je Größenklasse, Addition nur innerhalb
derselben Klasse, Umrechnung nur über eine benannte Funktion.

Das ist der Grund, warum dieser Befund an den Bau geht und nicht in eine siebte
Entwurfsrunde: **Ein Einheitenfehler in Prosa ist eine Fundstelle unter vielen, ein
Einheitenfehler im Typsystem ist ein Übersetzungsfehler.** Danach ist diese Klasse von
Befund für immer erledigt, nicht nur an dieser einen Stelle.
