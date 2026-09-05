---
id: 0119-welt-in-drei-schichten
rolle: spielentwerfer
status: vorschlag
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme".
---

# Die Welt hat drei Schichten, und der Entwurf kennt nur eine

**Einwand des Betreibers, 2026-09-05,** sinngemäß: Er möchte ein Modell der ganzen Welt
und den weltweiten Aktienmarkt, wenigstens die wichtigsten Börsen. Wie soll das gehen,
wenn nur einzelne Länder simuliert werden?

**Der Einwand trifft.** Nachgemessen: `spiel.md` nennt das Wort „Börse" **einmal** im
ganzen Dokument. Die zwanzig Positionssteckplätze sind 12 Sektorkörbe, 4 Währungen und
4 Anleihen — **ausnahmslos innerhalb der vier Länder**. Ein Hedgefonds, der nur in vier
Ländern etwas halten kann, ist kein globaler Hedgefonds, gleichgültig wie gut das
Makromodell darunter rechnet.

## Der Denkfehler steckt im Entwurf, nicht im Wunsch

Der Entwurf hat **zwei Achsen zu einer verschmolzen**:

1. **Politische Auflösung** — wo kann der Spieler lobbyieren, bestechen, Regulierung
   verschieben? Wo läuft eine volle Volkswirtschaft, die gegen echte Daten geprüft wird?
2. **Investierbares Universum** — wo kann der Fonds Positionen halten?

Heute sind beide dasselbe: `L = 4`. Deshalb sieht „mehr Welt" aus wie „mehr Länder zum
vollen Preis". Das ist ein Modellierungsfehler, kein Sachzwang. Ein echter Fonds kauft
japanische Aktien, ohne die Bank of Japan zu bestechen.

## Was die Trennung kostet — gerechnet aus `kern/zustand.hpp`

Die Formel reproduziert für `L = 4` exakt die heutigen 310 Adressen.

| | Politikländer | Börsenplätze | Zustand | handelbare Plätze |
|---|---:|---:|---:|---:|
| heute | 4 | 0 | **310** | 20 |
| nur mehr Länder (0118) | 9 | 0 | 740 | 45 |
| **drei Schichten** | 9 | **30** | **890** | **75** |
| alle Länder der Welt | 195 | 0 | **87.788** | 975 |

**Der Sprengsatz ist die Handelsmatrix**, sie wächst mit `G·(G−1)`:

| Länder | Handelsströme |
|---:|---:|
| 4 | 40 |
| 9 | 180 |
| 30 | 1.860 |
| 195 | **76.440** |

Ein Börsenplatz steht **nicht** in dieser Matrix. Er ist ein Finanzpreis, keine
Volkswirtschaft — er hat keine Sektoren, keinen Kapitalstock, keine Handelszeilen. Genau
daran hängt der Unterschied zwischen 890 und 87.788 Feldern.

## Die drei Schichten

1. **Politikland** (heute 4, geplant 9). Volle 44 Felder, Politikinstrumente, Lobbyismus,
   Korruption, Gegenkräfte, Handelszeilen, Rückvergleich gegen echte Daten. Teuer, tief,
   knapp.
2. **Börsenplatz** (neu, Größenordnung 20–40). Trägt einen Indexstand, einen Wechselkurs
   gegen den Numéraire, einen kurzen Zins und einen Bestandszähler — Größenordnung vier
   Felder. **Handelbar, nicht beeinflussbar.** Keine Instrumente, keine Zustimmung, kein
   Einfluss, keine Handelszeile.
3. **Restwelt** (existiert). Schließt den Kreislauf, damit die Summe der Handelsbilanzen
   nicht null sein muss.

**Woran ein Börsenplatz hängt, ist die eigentliche Entwurfsfrage.** Ein Index, der sich
unabhängig von allem bewegt, ist Dekoration; einer, der nur mitläuft, ist eine Kopie.
Nenne die Kopplung: über den Weltpreis, über den Handelsdurchgriff des nächstgelegenen
Politiklands, über den Weltzins — und was ihn *eigenständig* macht, damit
Diversifikation eine Entscheidung ist und kein Etikett.

## Was das für die vier Maße bedeutet

Das ist die harte Prüfung, und sie gehört in denselben Abschnitt:

- **Maß 4 (Wirklichkeit als Orakel)** — Börsenplätze sind nach Paket 0117
  **Spielländer**: sie zählen nicht in den sechzehn Prüfgegenständen. Der Rückvergleich
  bleibt bei den Politikländern, seine Schärfe sinkt nicht.
- **Maß 1 (Entscheidungsdichte)** — 75 Plätze bei unverändert drei Aktionen je Runde.
  Der Betreiber hat am 2026-09-05 entschieden, dass die Steckplätze mitwachsen (Weg A in
  Paket 0118). Die Rechnung dazu gehört dorthin und muss **beide** Zuwächse tragen, nicht
  nur die 45 aus den Ländern.
- **Maß 2 und 3** — mehr handelbare Plätze heißt mehr Strategien; ob sie sich
  *unterscheiden*, hängt allein an der Kopplung oben. Zwanzig Indizes, die dasselbe tun,
  sind ein Index.

## Was du entscheidest, und was nicht

**Du entscheidest:** dass es die Schicht gibt, was ein Börsenplatz an Feldern trägt,
woran sein Preis hängt, wie er handelbar wird, und in welcher Größenordnung — eine Zahl
mit Begründung, keine Liste von Städten.

**Du entscheidest nicht:** welche Börsen namentlich (eigenes Paket, nach der Datenlage),
die Adressarithmetik (0116), die Länderklassen (0117), welche fünf Länder (0118).

**Und du entscheidest nicht, ob 195 Länder gehen.** Die Zahl oben sagt es: 87.788 Felder,
76.440 Handelsströme und 195 × 19 lizenzgeprüfte Datenreihen. Das ist kein „später",
sondern ein anderes Produkt. Schreib das als verworfene Möglichkeit hin, mit der Zahl
daneben — der nächste, der die Frage stellt, soll die Antwort finden statt sie neu zu
rechnen.

## Abnahme

1. **Die drei Schichten stehen in `spiel.md`**, jede mit ihren Feldern, ihren Rechten
   (handelbar? beeinflussbar? im Rückvergleich?) und einem Satz, warum sie existiert.
2. **Die Kopplung eines Börsenplatzes ist benannt** — woran sein Preis hängt und was ihn
   eigenständig macht, in einer Formel oder einer Aufzählung von Einflüssen, nicht in
   Prosa.
3. **Die Tabelle mit den vier Wegen steht dort**, einschließlich der Zeile für alle
   Länder der Welt und der Handelsmatrix-Reihe, als verworfene Möglichkeit mit Zahl.
4. **Die Wirkung auf alle vier Maße ist benannt**, je Maß ein Absatz, und für Maß 1
   ausdrücklich mit dem Verweis, dass die Rechnung in 0118 beide Zuwächse tragen muss.
5. **`git diff` zeigt Änderungen ausschließlich in `spiel.md`.** Keine Zahl in
   `technik.md`, `reihen.toml` oder im Kern wird angefasst.

## Rückläufe

0.
