---
id: 0003-einheit-beteiligung
rolle: kernbauer
status: blockiert
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/einheiten.rs]
abnahme: Jede Geldgröße trägt ihre Einheit im Typ, nicht im Kommentar. Ein Test, der zwei verschiedene Einheiten addiert, wird vom Compiler abgelehnt statt zur Laufzeit falsch zu rechnen.
---

# Einheiten: blockiert am 2026-09-01, weil Paket und Vorgabe sich widersprechen

**Nachtrag 2026-09-02, Projektmanager: ADR 0011 ändert daran nichts, und das ist der
Punkt.** Der Stackwechsel auf C++ macht den Widerspruch weder kleiner noch grösser — die
Frage lautet weiter „Einheit im Typ oder Skala in einer Tabelle", und T5 beantwortet sie
mit der Tabelle. Der Weg über einen Wrappertyp ist in C++ so gangbar wie in Rust
(`enum class`, ein Strukturtyp mit einem Feld) und in beiden Sprachen dieselbe Abweichung
von T5. Das Paket bleibt `blockiert`; entschieden wird es vom Betreiber, per ADR gegen
T5 oder gar nicht. Die Dateiendung ziehe ich bewusst **nicht** nach: Eine Datei, die es
nicht geben soll, braucht keinen richtigen Namen.

**Der Sachbefund, aus dem dieses Paket entstand, ist behoben** — nicht hier, sondern im
Entwurf: `beteiligung_wert` lieferte Tausend USD und wurde als US-Cent verbucht;
`technik.md` T47 setzt seit dem 2026-09-01 `tsd_in_cent` um den äussersten Aufruf, und
T50 bindet die Umrechnung an einen Namen und genau einen Ort. Die Zahlenprobe ist in
T47 nachgerechnet.

**Was nicht mehr gilt, ist der Weg, den dieses Paket vorschreibt.** Es verlangt
Wrappertypen je Größenklasse:

> Die Einheit gehört in den Typ, nicht in den Namen und nicht in den Kommentar. In Rust
> kostet das wenig — ein Wrappertyp je Größenklasse, Addition nur innerhalb derselben
> Klasse, Umrechnung nur über eine benannte Funktion.

`technik.md` T5 entscheidet dieselbe Frage anders, und zwar ausdrücklich:

> **T5 — Jede Größenklasse hat eine deklarierte Skala.** Der Typ ist überall `i64`, die
> Bedeutung steht in dieser Tabelle und nirgends sonst.

Beides zugleich geht nicht. Ein Kernbauer, der dieses Abnahmekriterium erfüllte, wiche
von `specs/` ab — was seine Rolle ihm verbietet; einer, der T5 folgte, könnte das
Kriterium nie erfüllen. Nach der Regel dieser Rolle ist damit **nicht der Bauagent das
Problem, sondern die Vorgabe**, und der Zustand dafür ist `blockiert`.

## Der Zweck ist erfüllt, auf dem anderen Weg

Das Paket wollte die Fehlerklasse *gemischte Skalen* für immer schließen, nicht nur an
einer Stelle. Genau das ist zwischenzeitlich geschehen, an drei Stellen statt an einer:

- **T5** hat fünf Skalenklassen ergänzt, nachdem der Architekt die Tabelle zum ersten
  Mal gegen alle 310 Adressen gelegt und **69 ohne Klasse** gefunden hat — darunter die
  32 Druck- und Gegendruckfelder, die derselbe Fehler ein zweites Mal waren.
- **T49** gibt jeder der 310 Adressen genau eine Klasse; eine ohne und eine mit zwei
  brechen den Jahrgangsbau ab. Das ist Paket **0007**.
- **T50** gibt den drei Skalenübergängen je eine benannte, private Funktion mit genau
  einem Aufrufort, nachweisbar über `grep -rn 'tsd_in_cent\|lobbypunkte_aus' kern/`.
  Das ist Paket **0002**.

Der Unterschied zu Wrappertypen ist der Nachweisweg: Typprüfung braucht einen
Übersetzer, `grep` nicht.

**Korrektur am 2026-09-02, und sie geht gegen meine eigene frühere Begründung.** Hier
stand, kein Agent dieser Fabrik habe eine Shell, deshalb sei der Weg über T5 „nicht nur
der vorgegebene, sondern auch der einzige, der in dieser Fabrik tatsächlich geprüft
werden kann". Der zweite Halbsatz ist seit dem 2026-09-02 falsch: `baulauf.py` übersetzt
und legt das Urteil nach `befunde/uebersetzung-<datum>.md`; eine Bedingung, die der
Compiler zurückweist, ist hier ein prüfbares Abnahmekriterium. **Der Widerspruch zu T5
bleibt unberührt** — er war nie ein Nachweisproblem, sondern eine Entwurfsentscheidung
—, aber das Argument, das ihn zusätzlich stützte, trägt nicht mehr. Wer die Frage
entscheidet, entscheidet sie jetzt allein nach dem Entwurf.

## Meldung an den Geschäftsführer

Zu entscheiden ist **nichts**, solange T5 gilt. Will der Betreiber die Wrappertypen
trotzdem — mit dem Übersetzungslauf sind sie das schärfere Werkzeug, und dieses Argument
ist seit dem 2026-09-02 stärker geworden, nicht schwächer —, ist das ein **ADR gegen T5**
und danach ein neues Paket, kein Wiederaufwecken dieses hier. Ich löse den Widerspruch
nicht selbst auf: Über den Entwurf entscheide ich nicht.

**Das Feld `dateien` nennt weiter eine `.rs`-Datei, und das bleibt so.** `ops/plan.md`
führt es unter „Rest-Rust"; die Begründung von oben gilt unverändert — eine Datei, die es
nach T5 nie geben soll, braucht keinen richtigen Namen, und ein nachgezogener
C++-Dateiname sähe aus wie ein Paket, das nur auf einen Bauagenten wartet. Sollte der
Betreiber den ADR gegen T5 erlassen, entsteht ein neues Paket mit neuem Namen; sollte er
es nicht tun, ist die Zeile nie wieder relevant. Kein Bauagent liest sie, weil
`baulauf.py:startbereit` nur `offen` sieht.

Bis dahin bleibt dieses Paket blockiert und wird von keinem Bauagenten aufgegriffen —
`baulauf.py:startbereit` sieht nur `offen`.
