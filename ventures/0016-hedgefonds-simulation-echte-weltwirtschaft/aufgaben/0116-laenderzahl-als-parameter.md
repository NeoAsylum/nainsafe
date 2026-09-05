---
id: 0116-laenderzahl-als-parameter
rolle: architekt
status: vorschlag
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme".
---

# Ein Land hinzufügen soll ein Vorgang sein, kein Umbau

**Anforderung des Betreibers, 2026-09-05.** Wörtlich: *„Was ich gerne hätte, wäre die
einfache Möglichkeit, Länder hinzuzufügen."*

Dieses Paket entscheidet **nichts** über die Zahl der Länder. Vier bleiben vier, und die
Begründung dafür (`spiel.md`, *Warum vier Länder und nicht drei*) steht nicht zur
Disposition. Es geht allein darum, ob ein fünftes Land später ein **Vorgang mit
bekannten Schritten** ist oder ein Umbau mit offenem Ende.

## Was schon trägt

Nachgemessen am 2026-09-05:

- `LAENDER = 4` und `GEBIETE = 5` sind je eine `constexpr` in `kern/zustand.hpp`. Die
  Adressbasen werden daraus **gerechnet** (`BASIS_RESTWELT = LAENDER * LAND_FELDER`) und
  von `static_assert` abgesichert. Die Arithmetik ist bereits parametrisch.
- `daten/reihen.toml` führt je Reihe eine `dimension`, und sie ist als `"4 + RW"`
  geschrieben — die Länderzahl ist dort schon eine Größe und keine Konstante.

## Was nicht trägt

- **Zwei Aufzählungen führen Länderidentität einzeln.** `enum class Gebiet` (US, CN, DE,
  BR, RW) und `enum class Steckplatz` mit zwanzig namentlichen Werten
  (`Sektor_US_1` … `Anleihe_BR`). Elf Stellen im Kern und neunzehn in den Tests nennen
  die Kürzel wörtlich.
- **Die abgeleiteten Zahlen stehen als Literale in `specs/`.** 310, 175, 135, 40 Ströme,
  27 Sollreihen, 20 Steckplätze. Wer ein Land hinzufügt, muss heute jede einzeln
  nachrechnen und in Prosa nachziehen; welche Zahl aus welcher Formel entsteht, ist
  nirgends an einer Stelle aufgeschrieben.

## Die eigentliche Schranke ist nicht der Code

Sie ist die Datenlage, und sie ist heute schon offen. `daten/reihen.toml` hält 19 Reihen;
mehrere tragen `unklar`, weil ihre Quelle Dritte nennt. Der Befund im Wortlaut: *„Von den
acht Stellen der vier Modellländer (je Amt und Notenbank) ist genau eine geprüft
(Destatis), sieben sind offen."*

**Ein fünftes Land bringt zwei weitere Stellen mit** und außerdem: drei WDI-Sektorreihen,
Bevölkerung, Erwerbstätige, Produktivität, Preisniveau, Leitzins, Wechselkurs,
Staatsschuld, Haushaltssaldo — jede mit Deckung über das Fenster ab 2001 — sowie eine
BACI-Handelszeile gegen jedes andere Gebiet. Der Leitzins ist der bekannte Problemfall:
Der eingebettete IWF-Code führt Deutschland und China schon heute nicht.

Deshalb ist die ehrliche Antwort auf die Anforderung **nicht** „wir machen es
konfigurierbar", sondern: *ein Land hinzufügen kostet einen benannten Datenaufwand, und
der Code soll nicht zusätzlich im Weg stehen.*

## Was zu tun ist

Du schreibst **keinen Code**. Du ergänzt `technik.md` um einen Abschnitt, der die
Länderzahl als Parameter behandelt:

1. **Die Ableitungskette.** Für jede heute als Literal geführte Zahl die Formel, aus der
   sie entsteht — 310, 175, 135, 40, 27, 20 — in Abhängigkeit von `L` (Länder), `S`
   (Sektoren), `I` (Instrumente). Die heutigen Werte müssen sich bei `L = 4` daraus
   ergeben.
2. **Die Identitätsfrage.** Ob `Gebiet` und `Steckplatz` namentliche Aufzählungen
   bleiben (dann: welche Datei ist die eine Stelle, an der ein Land eingetragen wird)
   oder durch Index plus Kürzeltabelle ersetzt werden. **Triff die Wahl und begründe
   sie**; beides ist vertretbar, offenlassen ist es nicht.
3. **Die Prüfliste für ein neues Land.** Was ein fünftes Land an Daten, Lizenzklärung und
   Sollreihen mitbringen muss, damit der Rückvergleich weiter gilt — als Liste, die
   jemand abarbeiten kann, ohne die Spezifikation neu zu lesen.
4. **Was ausdrücklich nicht mitwächst.** Der Fondsblock, die zwanzig Steckplätze und die
   Todesarten sind an Spielbalance gebunden, nicht an Ländergeometrie. Nenne, was bei
   `L = 5` **gleich bleibt** und warum.

**Was nicht dazugehört:** die Länderzahl ändern, ein fünftes Land auswählen, den Kern
umbauen. Das wären eigene Pakete, und Nummer 3 ist die Voraussetzung dafür.

## Abnahme

1. **Jede der sechs Zahlen hat eine Formel.** `technik.md` nennt für 310, 175, 135, 40,
   27 und 20 je einen Ausdruck in `L`, `S`, `I`. Einsetzen von `L = 4`, `S = 3`, `I = 4`
   liefert genau die heutigen Werte; die Rechnung steht daneben.
2. **Die Identitätsfrage ist entschieden.** Der Abschnitt nennt genau eine der beiden
   Möglichkeiten aus Punkt 2 als gewählt, mit Begründung, und benennt die Datei, in der
   ein neues Land einzutragen wäre.
3. **Die Prüfliste ist abzählbar.** Sie führt je Datenreihe eine Zeile mit Quelle,
   benötigtem Fenster und Lizenzstand und nennt für den Leitzins ausdrücklich, wie mit
   Ländern zu verfahren ist, die der eingebettete IWF-Code nicht führt.
4. **Der Bestand bleibt unberührt.** `git diff` zeigt Änderungen ausschließlich in
   `technik.md`; die Zahl 310 und die Aussage „vier Länder" stehen unverändert an allen
   Stellen, an denen sie heute stehen. Dieses Paket beschreibt, es ändert nicht.

## Rückläufe

0.
