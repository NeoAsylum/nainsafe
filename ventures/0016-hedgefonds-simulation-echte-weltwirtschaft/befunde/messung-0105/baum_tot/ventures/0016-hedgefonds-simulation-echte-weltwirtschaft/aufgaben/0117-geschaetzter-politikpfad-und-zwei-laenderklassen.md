---
id: 0117-geschaetzter-politikpfad-und-zwei-laenderklassen
rolle: architekt
status: offen
haengt_an: [0116-laenderzahl-als-parameter]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme".
---

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, unverändert

Vier Prüfungen, alle bestanden: **Rolle** `architekt` steht in `BAUROLLEN`, Prüfer ist der
`entwurf-pruefer`. **Dateischnitt** `technik.md` — die engste Datei des Vorhabens, deshalb
die Kette unten. **Abnahme** vier Bedingungen, jede messbar; Bedingung 3 verlangt
ausdrücklich die Kennzeichnung einer *ungeprüften Vermutung* als solche, was diese Fabrik
sonst regelmäßig vergisst. **Abhängigkeit** `0116` war schon eingetragen und ist richtig:
Ohne die Ableitungskette gibt es keine parametrische Zählung, die Bedingung 2 verlangt.

`0116` trägt seinerseits eine Sperre auf `0051`, das auf `gebaut` steht. Die Kette wirkt
transitiv — `startbereit()` verlangt jede Kennung aus `haengt_an` im Zustand `fertig`
(`agents/baulauf.py:290-296`) —, deshalb steht 0051 hier nicht noch einmal.

## Du bist das zweite Glied von sieben in `technik.md`

Die Reihenfolge, die ich in diesem Lauf festgelegt habe, und der Grund steht in 0116:

    0051 (gebaut, in Prüfung) → 0116 → **0117** → 0064 → 0068 → 0074 → 0084 → 0092

Die vier Pakete des Betreibers vom 2026-09-05 gehen den fünf älteren vor. Nach dir ist die
Datei wieder frei für den Bestand.

## Eine Anmerkung an dich, damit 0068 nicht an deiner Arbeit scheitert

`0068-technikmd-reihe-9-ohne-sollrolle` steht **hinter** dir in derselben Datei und
behandelt dieselbe Reihe 9. Seine Bedingung 2 lautet: *„Die 16 Prüfgegenstände und die
Toleranz 2 in T37 bleiben unangetastet."* Deine Bedingung 2 macht ebendiese 16 zu einer
Formel.

**Das ist kein Widerspruch, und du sollst deinen Auftrag nicht deshalb verkleinern.** 0068
verlangt, dass *es* die Zahl nicht anfasst — nicht, dass die Ziffer 16 wörtlich dasteht. Der
Vermerk dazu steht in 0068. **Was du tun sollst:** Lass die Zahl 16 als eingesetzten Wert
neben der Formel sichtbar stehen, so wie Bedingung 2 es ohnehin verlangt („Einsetzen von
vier ergibt genau 16"). Dann findet der Prüfer von 0068 seinen Bezugspunkt, und niemand
zahlt einen Rücklauf für eine Reihenfolge, die er sich nicht ausgesucht hat.

# Ein geschätzter Leitzins ist erlaubt — aber dann zählt das Land nicht im Rückvergleich

**Anforderung des Betreibers, 2026-09-05.** Sinngemäß: Wenn der Leitzins das einzige
Hindernis für weitere Länder ist, soll er notfalls aus anderen Quellen abgeleitet oder
geschätzt werden dürfen.

## Warum das weniger kostet als befürchtet

Nachgemessen in `daten/reihen.toml`: Reihe 9 (Leitzins) trägt seit Paket 0054
`rolle = ["start", "politikpfad"]`, **`sollreihen = 0`** und eine leere `t37_klasse`.
Der Leitzins ist **Eingabe, nicht Messgröße**. Die Datei begründet es selbst:

> eine Reihe, die im Weltlauf als Eingabe gesetzt wird, hat den Fehler null per
> Konstruktion, kann nicht durchfallen

Und er steht in keiner der fünf Zeilen der sechzehn Prüfgegenstände (BIP 4,
Sektorstruktur 4, Verbraucherpreise 4, Wechselkurs 3, Handelsblock 1).

**Ein geschätzter Leitzins verletzt damit keine Sollreihe und keinen Prüfgegenstand
direkt.**

## Warum es trotzdem eine Grenze braucht

Der Leitzins ist Eingabe von Schritt 3, und Schritt 4 rechnet daraus BIP, Preise und
Wechselkurs — und **die** sind Prüfgegenstände. Ein erfundener Eingabepfad schöbe die
gemessenen Ausgaben von der Wirklichkeit weg, aus einem Grund, der nichts mit der Güte
des Modells zu tun hat. `spiel.md` hat das vorweggenommen:

> Ein Lauf mit erfundener Politik prüfte nur die halbe Maschine.

Der Widerspruch löst sich nicht durch Abwägen, sondern durch **Trennung**.

## Was zu tun ist

Du schreibst **keinen Code**. Du ergänzt `technik.md` um zwei Festlegungen.

### 1. Zwei Länderklassen

- **Rückvergleichsland.** Alle Datenreihen aus gemessener Quelle, Politikpfad aus echten
  Daten. Seine Größen zählen in den sechzehn Prüfgegenständen. Die heutigen vier sind
  diese Klasse.
- **Spielland.** Darf einen geschätzten oder abgeleiteten Politikpfad tragen. Erscheint
  im `spielmodus`, ist im `weltlauf` **von den Prüfgegenständen ausgenommen** — sein BIP,
  seine Sektorstruktur, seine Preise und sein Wechselkurs gehen in kein Fehlermaß ein.

Die Zählung trägt das schon: Die sechzehn stehen als `4 + 4 + 4 + 3 + 1` je Land da. Ein
Spielland ändert die Zahl, nicht die Struktur. **Nenne die neue Formel** und was aus
`16` bei einem zusätzlichen Spielland wird.

### 2. Die Rangfolge für einen fehlenden Politikpfad

Geraten wird zuletzt, nicht zuerst. In dieser Reihenfolge:

1. **Ein anderer Code derselben schon geklärten Quelle.** Der heutige
   `DISR_RT_PT_A_PT` ist eine Wahl aus Paket 0006, keine Notwendigkeit; die Datei sagt
   selbst `code_herkunft = "gewaehlt-0006, in specs/ nicht genannt"`.
2. **Eine abgeleitete Reihe aus einer bereits lizenzgeklärten Quelle.** *Vermutung, vor
   Gebrauch zu prüfen:* Die WDI führen Zinsreihen (Kandidaten `FR.INR.RINR`,
   `FR.INR.LEND`, `FR.INR.DPST`). Sie sind keine Leitzinsen, aber sie stünden unter
   CC BY 4.0 und aus einer Quelle, die dieses Vorhaben ohnehin einbettet. **Nicht
   bestätigt** — Deckung, Länderliste und Drittanbieterlage sind ungeprüft.
3. **Kein Pfad, weil es keinen gibt.** Für Länder ohne eigenen geldpolitischen Hebel ist
   das die *richtige* Antwort und keine Lücke — Deutschland trägt diese Eigenschaft
   ausdrücklich als Entwurfsmerkmal (`spiel.md`, *Warum vier Länder und nicht drei*).
4. **Ein geschätzter Pfad**, mit hinterlegter Herleitung. Nur dann wird das Land ein
   Spielland.

Jede geschätzte oder abgeleitete Reihe wird in `reihen.toml` als solche gekennzeichnet
und trägt ihre Herleitung im Klartext. Eine Schätzung, die wie eine Messung aussieht, ist
schlimmer als eine fehlende Reihe.

**Was nicht dazugehört:** ein Land auswählen, Zinsreihen suchen, den Kern ändern, die
heutigen vier Länder anfassen.

## Abnahme

1. **Die beiden Klassen sind definiert**, jede mit der Aussage, ob ihre Größen in die
   Prüfgegenstände eingehen. Die heutigen vier Länder sind ausdrücklich als
   Rückvergleichsländer benannt.
2. **Die Zählung ist parametrisch.** `technik.md` nennt für die sechzehn
   Prüfgegenstände eine Formel in der Zahl der Rückvergleichsländer; Einsetzen von vier
   ergibt genau 16, und ein zusätzliches Spielland lässt die Zahl nachweislich
   unverändert.
3. **Die Rangfolge steht mit vier Stufen** in dieser Reihenfolge, und Stufe 2 ist als
   **ungeprüfte Vermutung** gekennzeichnet, nicht als Quelle.
4. **Die Kennzeichnungspflicht ist festgelegt:** welches Feld in `reihen.toml` eine
   geschätzte Reihe trägt und was darin stehen muss. `git diff` zeigt Änderungen
   ausschließlich in `technik.md`.

## Rückläufe

0.
