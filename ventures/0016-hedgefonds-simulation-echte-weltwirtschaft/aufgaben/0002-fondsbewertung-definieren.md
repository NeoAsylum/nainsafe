---
id: 0002-fondsbewertung-definieren
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bewertung.rs]
abnahme: `korbwert(l, s)` und `positionswert(p)` sind als Ganzzahlfunktionen implementiert, ihre Einheit ist im Typ oder im Namen deklariert, und `fondsvermoegen(z)` rechnet nachweislich in einer einzigen Einheit. Ein Test rechnet einen Fall von Hand nach.
---

# Fondsbewertung: die beiden fehlenden Funktionen

Aus Befund 1 der sechsten Entwurfsprüfung, Schwere hoch:

> `positionswert(p)` und `korbwert(l, s)` haben keine Entstehungsregel, und an ihnen
> hängt alles.

`technik.md` T47 gibt `fondsvermoegen(z)` als verbindliche Formel an — Kasse plus
20 Positionssteckplätze plus 12 Land×Sektor-Beteiligungen minus Hebelstand. `kasse`,
`anteil[l][s]` und `hebelstand` sind Zustandsadressen mit Herkunftseintrag,
`ausstiegsabschlag` ist ein Parameterschlüssel. **Die beiden Bewertungsfunktionen sind
es nicht.**

Ohne sie ist das Fondsvermögen nicht berechenbar, und damit auch nicht die
Siegbedingung.

## Was du entscheidest

Wie ein Korb und eine Position bewertet werden — aus Weltpreis, Landespreis, Menge und
Anteil. Der Entwurf gibt es nicht her; entscheide es, schreib die Regel in den Code und
in einen Kommentar, und nenne die Einheit ausdrücklich.

**Kein weiterer Prosaentwurf.** Genau das hat fünf Runden lang nicht funktioniert.
