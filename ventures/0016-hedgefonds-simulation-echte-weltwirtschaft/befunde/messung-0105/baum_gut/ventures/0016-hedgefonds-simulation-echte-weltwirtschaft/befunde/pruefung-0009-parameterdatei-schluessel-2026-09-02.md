---
typ: pruefung
paket: 0009-parameterdatei-schluessel
pruefer: daten-pruefer
datum: 2026-09-02
urteil: zurueck
kriterium_geprueft: Alle 50 Schlüssel gegen die Tabellen in T27 und T51 abgezählt, jede Klassenzuweisung gegen T5 und jeden Startwert gegen die im selben Kommentarblock genannte Schranke gerechnet — Abnahme 1 und 2 halten, Abnahme 3 hält an zwei Stellen nicht.
befunde: 4
---

# Prüfung 0009-parameterdatei-schluessel

Geprüft: `ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml`
(763 Zeilen, Kopfstand 2026-09-02) gegen `specs/0016-…/technik.md` T5, T27, T47, T50,
T51, T23 Punkt 5 und T45.

## Was gehalten hat

**Abnahme 1 — Vollständigkeit.** Beide Tabellen danebengelegt und abgezählt.

| Quelle | Sollschlüssel | in der Datei |
|---|---:|---:|
| Tabelle T27 (Zeilen 1040–1049) | 10 Skalare + `schrittweite`/`instrument_min`/`instrument_max` | 10 + 12 |
| Fliesstext T27 (Zeile 1028–1032) | Mandatsschwelle (2), drei Aufsichtsschwellen, Nachahmergeschwindigkeit, Anlegerabzugsanteil, Startkapital, Startzustimmung, Startstand Regulierung | 12 (mit `aufsicht_max`, `nachahmer_max`) |
| „Verzögerungen" (T27) | Gruppe, keine Einzelnamen | 4 |
| „Elastizitäten" (T27) | Gruppe, keine Einzelnamen | 12 |
| Tabelle T51 (Zeilen 948–953) | 4 Instrumente × 3 | 12, davon 4 als `# FEST (T51)` |

50 Schlüssel gezählt (`^[a-z_0-9]+ = ` über die Datei: 38 auf oberster Ebene,
12 in den vier Tabellen), 46 `# PLATZHALTER`, 4 `# FEST (T51)` — die Zählung im
Dateikopf (Zeilen 73–82) stimmt. Kein Sollschlüssel fehlt.

**Abnahme 2 — kein Schlüssel ohne Skalenklasse.** Alle 50 tragen eine; die drei
`aufsicht_schwelle_*` und die vier Verzögerungen über den Gruppenkopf (Zeilen 286, 409),
die zwölf Instrumentenschlüssel über den Tabellenkopf. Die Klassenzuweisungen der zehn
T27-Tabellenzeilen stimmen zeichengenau mit Spalte 2 von T27 überein (4, 11, 4, 4, 3, 1,
4, 9, 9, 10). Umgekehrt geprüft: Jede T5-Klasse, deren Bereich `parameter.toml` als
Quelle nennt (9 → `druck_max`, 10 → `regulierung_stufen`, 11 → „Obergrenze aus
`parameter.toml`"), hat einen Schlüssel oder eine ausdrückliche Begründung (Befund 7 der
Datei). Keine Klasse ohne Schlüssel.

**Abnahme 4 — TOML.** Alle 38 blanken Schlüssel stehen vor der ersten Tabellenzeile
(letzter in Zeile 614, erste Tabelle in Zeile 655), vier Tabellenköpfe, kein doppelter
Schlüssel, kein Wert mit Dezimalpunkt, Anführungszeichen oder Apostroph
(`^[a-z_0-9]+ *=.*[.\"']` findet keine Zeile). Kein Wert ohne `# PLATZHALTER` oder
`# FEST (T51)`. **Einschränkung, ausdrücklich:** Ein Parser lief nicht — `python3` ist in
dieser Umgebung nicht freigegeben. Die Gültigkeit ist strukturell nachgelesen, nicht
maschinell bestätigt.

**Kreuzprobe, die die Abnahme nicht verlangt.** Befund 6 der Datei behauptet, T45 führe
`4×2` von elf Parameteradressen. Gegen `daten/adressen.md` gezählt (`grep "Parameter("`):
vier `land.<L>.zustimmung`, vier `land.<L>.instrument.regulierung.stand`, `fonds.kasse`,
`fonds.anlegerbestand`, `partie.parameter_pruefsumme` = 11. Die Datei führt für die
Prüfsumme zu Recht keinen Schlüssel (T27: sie steht im Zustand). Die Zählung geht auf.

Ebenfalls nachgerechnet und in Ordnung: `instrument_min[leitzins] = −50 ≥ 1 − aufschlag
= 1 − 51 = −50` (T51, T23 Punkt 5); `instrument_max[regulierung] = 1 = regulierung_stufen`
(T51); `1 ≤ aufsicht_schwelle_1 < _2 < _3 ≤ aufsicht_max`, also `1 < 2 < 3 ≤ 3`;
`regulierung_start = 0 ≤ regulierung_stufen = 1`; `gegenlobby_satz = 0 ≤ druck_max = 1`
(T5 Klasse 9).

---

## Befund 1 — `startzustimmung` und `zustimmung_wechselschwelle` verletzen beide ihre eigene Schranke

**Abnahme 3 ist damit nicht erfüllt.** Die Datei stellt zwischen den beiden eine strenge
Ungleichung auf, in beide Richtungen, und setzt dann beide Platzhalter auf 0.

So erzeugt man ihn:

1. `parameter.toml` Zeile 379–381 lesen — Schranke von `startzustimmung`:
   „0 … 10.000 aus der Klasse (T5); **ueber** `zustimmung_wechselschwelle`, sonst
   wechselt jede Regierung in Runde 1".
2. Zeile 386 lesen: `startzustimmung = 0`.
3. Zeile 521 lesen — Schranke von `zustimmung_wechselschwelle`: „0 … 10.000 aus der
   Klasse (T5); **unter** `startzustimmung`".
4. Zeile 526 lesen: `zustimmung_wechselschwelle = 0`.
5. Einsetzen: `0 > 0` ist falsch, `0 < 0` ist falsch. Beide Startwerte liegen ausserhalb
   der Schranke, die im selben Kommentarblock steht.

Das ist kein Formfehler. Die Datei benennt die Folge selbst: In Runde 1 steht die
Zustimmung aller vier spielbaren Länder auf ihrer Wechselschwelle, Gegenkraft 2 löst in
allen vier Ländern aus, `lobbykosten_rest` und `regierungsdruck_rest` werden gesetzt,
bevor der Fonds eine Aktion getan hat. Ein Satz, der nach der eigenen Regel A der Datei
zulässig sein soll („Wo eine untere Schranke steht, ist der Platzhalter genau diese
Schranke"), ist hier nicht bloss wirkungslos, sondern aktiv. Nach Regel A wäre die
untere Schranke von `startzustimmung` der kleinste Wert über 0, also 1; die Datei setzt
0 und wendet ihre eigene Regel an dieser Stelle nicht an.

Beide Zahlen zu ändern, ist Sache des Bauagenten; ich repariere nichts.

## Befund 2 — Befund 5 der Datei behauptet eine Einzigartigkeit, die nicht besteht

Zeile 743–747: „`aufschlag` und `instrument_min[leitzins]` sind gekoppelt … **Sie ist die
einzige Stelle, an der zwei Platzhalter voneinander abhaengen**; wer einen aendert,
prueft den anderen."

Nach der Datei selbst hängen mindestens fünf Paare voneinander ab:
`aufschlag`/`instrument_min[leitzins]` (Zeile 186), `aufsicht_schwelle_3`/`aufsicht_max`
(Zeile 314), `regulierung_start`/`regulierung_stufen` (Zeile 394),
`instrument_max[regulierung]`/`regulierung_stufen` (Zeile 709),
`gegenlobby_satz`/`druck_max` (Zeile 224) — und
`startzustimmung`/`zustimmung_wechselschwelle` (Zeilen 380 und 521).

Das ist der Grund, aus dem Befund 1 unbemerkt blieb: Die Datei prüft genau das eine Paar
nach, das sie für das einzige hält, und lässt die übrigen ungerechnet. Die Zeile ist
zugleich eine Anweisung an jeden späteren Leser — wer sie glaubt, ändert
`zustimmung_wechselschwelle`, ohne `startzustimmung` mitzuprüfen.

Wirkung: Der Satz steht im Abschnitt BEFUNDE der Datei, wird also von der nächsten Rolle
als geprüfte Aussage gelesen.

## Befund 3 — fünf Schlüssel der Klasse 4 tragen keinen oberen Wertebereich, den ihre Klasse vorschreibt

T5 (Zeile 125) gibt für Klasse 4 den Bereich **„0 bis 10.000"** an, und T5 sagt von sich,
die Bedeutung stehe „in dieser Tabelle und nirgends sonst". Elf Klasse-4-Schlüssel der
Datei zitieren diesen Deckel wörtlich („0 … 10.000 aus der Klasse (T5)"). Fünf tun es
nicht:

| Schlüssel | Zeile | Klasse laut Datei | Schranke laut Datei |
|---|---:|---|---|
| `preisstoss` | 493/499 | 4 | `>= 0.` **„specs/ nennt keine obere."** |
| `zustimmung_elastizitaet` | 507/511 | 4 | `>= 0.` |
| `nachahmer_wirkung` | 528/532 | 4 | `>= 0.` |
| `hebel_max` | 566/570 | 4 | `>= 0.` |
| `innerjahresausschlag_faktor` | 600/609 | 4 | `>= 0.` |

Die Aussage bei `preisstoss` ist nachweislich falsch: `specs/technik.md` Zeile 125 nennt
für die Klasse, die die Datei diesem Schlüssel selbst zuweist, eine obere Schranke.

So erzeugt man den Schaden: Das Paket, das diese Datei nach T27/T9 in eine Struktur mit
benannten Feldern einliest, muss je Feld eine Bereichsprüfung setzen. Nimmt es T5, ist
`hebel_max ≤ 10.000` — der Hebel kann das Fondsvermögen nie übersteigen, und Todesart 1
wird praktisch unerreichbar. Nimmt es die Zeile in `parameter.toml`, ist `hebel_max`
unbeschränkt und Klasse 4 hält ihren in T5 zugesagten Bereich nicht mehr — genau der
Fehlertyp, den T49 („eine Adresse ohne Klasse und eine mit zwei Klassen brechen den Bau
ab") für Adressen ausschliesst. Beide Lesarten sind aus der Datei belegbar; das ist der
Befund.

Die Datei kann das: Bei `gegenlobby_satz` (Zeile 220–224) steht genau die Auflösung —
Klasse 9, Schranke `>= 0`, „wirksam begrenzt ist das **Ergebnis** durch `druck_max`".
Dieselbe Unterscheidung zwischen dem Bereich der Grösse und dem Bereich des Reglers
fehlt bei den fünf oben. Entweder gehören sie nicht in Klasse 4, oder sie tragen deren
Deckel; welches von beidem, ist eine Entscheidung, die diese Datei treffen muss.

## Befund 4 — `schrittweite` hat in drei von vier Instrumententabellen weder Wertebereich noch Herkunft einer Schranke

Die Abnahme verlangt je Schlüssel „Skalenklasse nach T5, **Wertebereich, Herkunft der
Schranke** und einen Startwert innerhalb der Schranken".

Im Abschnitt der Instrumente (Zeilen 640–709, 12 Schlüssel) kommt das Wort „Schranke"
genau einmal vor, in Zeile 642, und dort für `instrument_min[leitzins]`. Für
`schrittweite` in `[instrument.leitzins]` (656), `[instrument.zoll]` (672) und
`[instrument.haushalt]` (684) steht kein Wertebereich und keine Fundstelle — nur die
Zeile „Kalibriert: Selbstspieler (`schrittweite`)" und ein „Scheitert daran". Alle drei
tragen `= 1  # PLATZHALTER`.

Damit ist für drei der 50 Schlüssel nicht prüfbar, was Abnahme 3 verlangt: „Startwert
innerhalb der eigenen Schranke" hat keinen Bezugspunkt. Praktische Folge: `schrittweite
= 0` ist nach dieser Datei zulässig; dann bewegt sich das Instrument im `spielmodus` nie
(`stand = min(max(stand ± 0, min), max)`), Aktion 3 und die Verzögerung aus Kanal 8
laufen ins Leere, und nichts bricht ab. Ein negativer Wert kehrt die Richtung jeder
Lobbybewegung um.

Nicht als Befund gezählt: `instrument_min`/`instrument_max` von Zoll und Haushalt. Dort
sagt die Datei ausdrücklich, T51 nenne keine Zahl und keine Bedingung und beide seien
gegen den historischen Pfad zu prüfen (Zeilen 669–680) — das ist eine benannte Herkunft,
und T51 trägt sie.

---

## Wonach ich gesucht und nichts gefunden habe

- **Einheiten- und Basisjahrfehler.** Diese Datei trägt keine Zahl aus einer externen
  Quelle; sie stellt es im Kopf ausdrücklich fest (Zeilen 110–113). Der Schnitt Klasse ×
  Herkunft, der bei Paket 0007 den Befund brachte, hat hier keinen Angriffspunkt: Es gibt
  keinen Datenanker, keine laufenden gegen konstante Preise, keine Währungsumrechnung.
  Der einzige Skalenbezug ist `aufschlag` ↔ `leitzins_pfad`, beides Basispunkte, und er
  geht auf (siehe oben).
- **Lücken.** Kein Wert ist interpoliert; alle 50 sind gekennzeichnet.
- **Lizenz.** Keine Quelle verwendet, also keine Namensnennung fällig. Die zwei
  EZB-Belege in Zeile 173–175 sind aus T23 Punkt 5 übernommen und dort mit Abrufdatum
  belegt; sie stehen hier als Verweis, nicht als eingebetteter Wert.
- **Reproduzierbarkeit.** Die Datei trägt im Kopf `Stand 2026-09-02` und das Paket, aus
  dem sie stammt. Sie ist statisch; zweimal Lesen gibt dasselbe.
- **Vorweggenommene Kalibrierung.** Jeder der 46 Platzhalter steht auf seiner unteren
  Schranke oder auf 0, die vier `# FEST (T51)`-Werte sind aus T51 abgeleitet und einzeln
  belegt. `aufschlag = 51` ist begründet (der grössere der beiden Kandidaten aus T23
  Punkt 5) und als Platzhalter markiert. Keine Zahl sieht wie ein Suchergebnis aus.
- **Nicht geprüft, weil ausserhalb dieses Pakets:** ob die zwölf Schlüssel der Gruppe C
  die richtigen zwölf Elastizitäten sind. T27 nennt die Gruppe und keinen Namen; die
  Datei meldet die Unsicherheit selbst (ihr Befund 2). Das entscheidet erst das Paket,
  das Schritt 3 bis 5 baut — an den Projektmanager, nicht an den Bauagenten.

## Was der Projektmanager daraus machen kann

Befund 1 ist ein Rücklauf an das Paket: zwei Zahlen, beide in dieser Datei.
Befund 2 und 4 gehören in denselben Rücklauf.
Befund 3 ist keine Reparatur an dieser Datei allein — er entscheidet, ob T5 Klasse 4
ihren Bereich auch für Regler trägt, und berührt damit `specs/`. Falls die Antwort
„nein" lautet, fehlt in T5 der Satz, der es sagt.
