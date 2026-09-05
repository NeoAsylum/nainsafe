---
id: 0148-zielkennung-je-aktionsart
rolle: architekt
status: offen
haengt_an: [0146-aktionstyp-und-kanonische-ordnung, 0141-pruefliste-fuenftes-land]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: T32 nennt fuer jede der fuenf Aktionsarten die Menge, die ihre Zielkennung durchlaeuft, und die T9-Ordnung darauf -- fuenf Zeilen, jede mit ihrer Herleitung. Fuer eine Art ohne Ziel steht ausdruecklich da, was an ihrer Stelle gilt, statt dass die Zeile fehlt. Der Widerspruch zu Art 5 (unten, Punkt 2) ist in derselben Fassung entweder aufgeloest oder als Befund benannt.
---

# ANGENOMMEN — 2026-09-06, Projektmanager

Rolle `architekt` gibt es und wird eingeplant; die Abnahme ist prüfbar (fünf benannte
Zeilen, je mit Herleitung); die Vorbedingung 0146 steht seit heute auf `fertig`.
**Der zweite Eintrag in `haengt_an` ist eine Reihenfolgesperre und keine fachliche
Abhängigkeit:** `technik.md` ist eine Datei, und vier Pakete waren gleichzeitig für sie
bereit. Die Kette lautet 0117 → 0141 → **0148** → 0149 → 0064 → 0068 → 0074 → 0084 → 0092.
Dass 0148 vor 0149 und vor der ganzen Belegstellen-Reihe steht, ist die einzige
Vorrangentscheidung dieses Laufs und begründet sich aus dem Rumpf unten: Ohne die
Zieldomänen ist die Liste der zulässigen Aktionen für keine Art bildbar, und daran hängen
T35, T41 und die drei Maße.

**Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer.**

---

# VORSCHLAG — 2026-09-05, Kernbauer aus Paket 0146

## Was fehlt

T32 sagt: sortiert wird nach `(Aktionsart 1…5, Zielkennung, Stufe)`, und „die Zielkennung
ist die feste Indexordnung aus T9". Damit ist gesagt, **wonach** sortiert wird, und
**nicht**, welche Menge die Zielkennung je Aktionsart durchläuft. Das Wort *Zielkennung*
kommt in `technik.md` genau einmal vor, nämlich in T32 selbst; T9 nennt es nicht.

Paket 0146 hat den Aktionstyp und die kanonische Ordnung gebaut und diese Lücke
ausdrücklich **nicht** gefüllt — das Paket verlangt das so, und der Grund steht dort: Eine
geratene Ordnung bindet den Regressionsbestand, und sie zu ändern braucht danach einen
ADR. `kern::aktion::Zielkennung` ist heute deshalb der Platz in einer T9-Ordnung und sonst
nichts.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Es ist keine Bauarbeit.** Die Entscheidung gehört in `specs/`, nicht in den Kern; ein
Bauagent, der sie im Code trifft, hat sie damit getroffen, ohne dass jemand sie beschlossen
hat. Der Kernbauer darf sie nach seiner eigenen Rollengrenze nicht fällen.

**Es ist auch nicht Teil des Folgepakets zur Bündelzulässigkeit.** Das prüft eine gegebene
Menge von Aktionen gegen den Zustand; es setzt die Zieldomänen voraus, statt sie zu
begründen. Wer beides in einen Lauf legt, entscheidet die Vorgabefrage nebenbei in einem
Bauschritt — genau die Reihenfolge, die T32 verhindern will.

**Es blockiert mehr als eine Sache.** Ohne die Zieldomänen lässt sich die Liste der
zulässigen Aktionen (T32, erste Hälfte) für keine Art bilden. Daran hängen nach der
Pflichtentabelle unter T30 der Zufallsbot, die drei Maße und alles, was den Spielmodus
braucht — T35 zieht ohne Zurücklegen aus genau dieser Liste, T41 kürzt genau diese Teilliste.

## Zwei Punkte, die die Fassung beantworten muss

**1. Die fünf Zeilen.** Für die Arten 1 bis 3 liegt je eine Lesart nahe, und sie steht
nirgends als Vorgabe: `spiel.md`, Abschnitt „Jede Größe ohne Datenanker, mit ihrem
Startwert" ordnet den Positionssteckplätzen (20) Aktion 1 zu, den Beteiligungen (12
Land × Sektor) Aktion 2 und dem Lobbydruck je Instrument (16 Land × Instrument) Aktion 3.
Das ist die Zuordnung *geschriebener Zustandsgrößen* zu Aktionen und keine Aussage über die
Zielkennung — sie kann richtig sein, aber sie ist nicht gesagt. Für Art 4 (Hebel) führt der
Zustand nur `fonds.hebelstand`, für Art 5 nur `fonds.sichtbarkeit`; eine Zielmenge gibt es
dort nach heutigem Zustand nicht. Was dann in der Zielkennung steht, muss dastehen —
andernfalls trägt sie für zwei der fünf Arten einen Wert ohne Bedeutung, und der geht in
jede Prüfsumme eines Speicherstands ein.

**2. Der Widerspruch bei Art 5.** `spiel.md`, Abschnitt „Die Aktionen" sagt, der Fonds lege
„eine Position öffentlich offen oder ziehe sich zurück", und die Offenlegung verstärke
„jedes Lobbybudget in dieser Sache" — beides klingt nach einem Ziel je Steckplatz
beziehungsweise je Instrument. Der Zustand führt dafür eine **einzige** Zahl. Beides
zugleich geht nicht: Entweder ist Sichtbarkeit eine Größe ohne Ziel, dann ist „in dieser
Sache" gegenstandslos, oder sie hat ein Ziel, dann fehlen dem Zustand die Adressen dafür —
und das rührt an die 310 und damit an T15. Die Auflösung ist eine Modell- und
Adressentscheidung und ausdrücklich keine Bauentscheidung.

## Was ausdrücklich nicht dazugehört

- **Kein Code.** Die drei Dateien von 0146 werden hier nicht angefasst. Steht die Vorgabe,
  ist das Nachziehen im Kern ein eigenes, kleines Bauteil.
- **Keine Änderung der Ordnung selbst.** Die Rangfolge aus T32 steht und ist gebaut; sie
  zu ändern verlangt nach T32 einen ADR und ist nicht Gegenstand dieses Pakets.
