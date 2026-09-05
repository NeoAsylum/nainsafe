---
typ: pruefung
paket: 0119-welt-in-drei-schichten
pruefer: entwurf-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Die fünf Abnahmebedingungen aus 0119 einzeln nachgemessen — Schichtentabelle gelesen, Kopplungsformeln samt Eingaben und Fixpunkt nachgerechnet, Kostentabelle an kern/zustand.hpp verankert, die vier Maß-Absätze geprüft, Diff-Umfang des Baucommits nachgemessen.
befunde: 2
---

# Prüfung 0119-welt-in-drei-schichten

Geprüft wurde der Stand von Commit `2ed2e0c` (Eltern `d2fb21b`); der Arbeitsbereich
enthält für `spiel.md` keine weiteren Änderungen. Zeilenangaben beziehen sich auf diesen
Stand. Das Kriterium sind die fünf Bedingungen im Abschnitt *Abnahme* des Pakets 0119 —
`0001-entwurf-abnahme` ist seit dem 2026-09-01 `fertig` und war nicht der Maßstab.

## Bedingung 1 — die drei Schichten: erfüllt

Tabelle `spiel.md:857-861` führt alle drei Schichten mit Einheitenzahl, Feldern und den
drei abgefragten Rechten (handelbar / beeinflussbar / im Rückvergleich, dazu
Handelszeile). Je Schicht folgt ein Warum-Absatz (Z. 863, 867, 872). Die 58 Felder der
Schicht 1 zerlegen sich als 44 + 5 + 6 + 3; nachgeprüft gegen `kern/zustand.hpp`:
`LAND_FELDER = 44`, `STECKPLAETZE/LAENDER = 20/4 = 5`, Beteiligung `24/4 = 6`, Nachahmer
`12/4 = 3`. Die Restwelt-Zeile nennt ihre Felder qualitativ (Sektor- und Aggregatgrößen);
die Abzählung (22) steht unverändert in `technik.md` T15 und `zustand.hpp:349`.

## Bedingung 2 — die Kopplung: erfüllt

Der Abschnitt *Woran ein Börsenplatz hängt* (Z. 902-1023) gibt Jahrgangskonstanten,
Zustandsfunktionen und die Schreibregel als Formeln, dazu die fünf Einflüsse als
nummerierte Aufzählung (Z. 962-974) und drei Eigenständigkeitsmechanismen (Z. 976-993).
Nachgerechnet und aufgegangen:

- **Jede Eingabe existiert.** `kapitalstock[l]` ist Grundgröße (Z. 596:
  `kapitalstock[l][s] = mal_geteilt(kapitalstock[l], sektoranteil[l][s], 10.000)`);
  Sektorpreis läuft „je Gebiet × Sektor, 15" (Z. 453), die Restwelt trägt „dieselben
  Sektor- und Aggregatgrößen" (Z. 413); `wechselkurs[l]` und `leitzins[l]` stehen in der
  Landesliste (Z. 407-409). Die Restwelt-Sonderfälle (kein Leitzins, kein Wechselkurs)
  sind in `zielzins`/`zielkurs` ausdrücklich behandelt (Z. 927-931, 941-947).
- **Der Startjahr-Fixpunkt geht auf:** `leitkurs = 10.000` (Gewichte normiert auf
  10.000, Preise 10.000), `zinsfaktor = 10.000`, `zielkurs = 10.000`, also
  `index = 10.000` als Folge, nicht als Setzung (Z. 997-1001).
- **Beharrungswert der halben Numéraire-Bindung:** Fixpunkt von
  `wechselkurs[b] ← Mittel(wechselkurs[b], zielkurs)` ist `(wechselkurs[gebiet]+10.000)/2`
  — Abweichung von 10.000 exakt halbiert, wie Z. 989-991 behauptet.
- **Die Dämpfungszahl des breiten Wegs:** 1/9 (Kapitalstockgewicht) · 1/2 (`zielzins`)
  · 1/2 (Halbierung) = 1/36 ≈ 2,8 % (Z. 782) und `(1/2)^5 ≈ 3 %` (Z. 1012) stimmen.
- **Die eine Verweisformel** (Nachahmer-/Stoßaufschlag, Z. 957-959) ist als einzige
  ausgewiesen, ihr Risikofall benannt und dem Architekten zugewiesen (Nachzugliste,
  Z. 2499). Gegengeprüft an Z. 603-635: Die bestehende Regel liest den Anteil
  (`|stufen|·stufenweite`) und `korbwert`, nicht `kapitalstock[l][s]` unmittelbar — der
  deklarierte Risikofall liegt auf `spiel.md`-Ebene nicht vor.

## Bedingung 3 — die Tabelle der Wege: erfüllt

Z. 1058-1064: fünf Zeilen einschließlich „alle Länder der Welt — verworfen" mit 87.788
Feldern, dazu die Handelsmatrix-Reihe Z. 1069-1075. **Alle Zahlen unabhängig
nachgerechnet, verankert an `zustand.hpp`:** Aus den Basiskonstanten folgt
310 = 4·44 + 22 + 40 + 2 + 12 + 2 + 5 + 3 + 20 + 24 + 4, daraus die eine Formel
`Zustand(L) = 58·L + 2·L·(L+1) + 38` (der Fixteil 38 = 22+2+2+5+3+4). Sie reproduziert
alle fünf Zeilen: 310, 740, 890 (= 740 + 5·30), 5.420, 87.788; handelbare Plätze 5·L:
20/45/75/195/975; Handelsströme 2·G·(G−1) mit G = L+1: 40/180/1.860/3.120/76.440. Auch
die Randkosten stimmen: 98 = 58 + 4·(L+1) bei L = 9, und 98/5 ≈ 20 gegen 5/1 ist der
behauptete Faktor vier (Z. 1077-1081).

## Bedingung 4 — die vier Maße: erfüllt

Je Maß ein Absatz (Z. 1158-1208). Maß 1 trägt den geforderten Verweis wörtlich: „Die
Rechnung … gehört in Paket 0118, und sie muss beide Zuwächse tragen, nicht nur die 45 aus
den Ländern" (Z. 1160-1163); die genannte Prüfform `Dichte(t)` bei K = 30 gegen K = 60
existiert im Bestand (Z. 2392). Maß 4 schreibt die 0117-Zuordnung als Verweis, nicht als
nachgemessene Tatsache (Z. 1194-1195) — 0117 ist ungebaut, genau wie das Paket es
verlangt. Die Bezugszahlen stimmen mit dem Bestand: 23 freie von 27 Sollreihen (Z. 16,
827), 16 Prüfgegenstände, 9.539.200 Weltschritte (Z. 2035).

## Bedingung 5 — der Diff-Umfang: erfüllt

`git diff --stat d2fb21b 2ed2e0c`: geändert sind `spiel.md` (+505/−13 über neun Hunks,
alle neun gelesen) und `notizen/spielentwerfer.md` — das Pflicht-Logbuch, das jeder Lauf
nach CLAUDE.md führt und das keine Paketdatei ist. `technik.md`, `reihen.toml` und der
Kern sind unberührt; keine Zahl darin ist angefasst.

## Zwei Befunde — beide unterhalb der Rücklaufschwelle

**1. Z. 1087 zählt mit `4 · R`, aber R ist in diesem Dokument die Partielänge.**
Erzeugen: Z. 16 lesen („R = 20 Runden", dazu der Abschnitt *Die Partielänge R*, Z. 81),
dann Z. 1087: „nach der Zählung `4 · R` **780** Prüfgegenstände". Mit dem R des Dokuments
ergibt die Zählung 80, nicht 780. Gemeint ist „4 je Rückvergleichsland", also `4 · L`
(4·4 = 16, 4·195 = 780 — die Zahlen selbst stimmen). Kein Bedingungsbruch: Bedingung 3
verlangt die Tabelle mit Zahl, und die Zahlen sind richtig. Aber die Passage ist
ausdrücklich als kanonische Antwort für Spätere gebaut („Wer die Frage erneut stellt,
findet hier die Antwort"), und dort ein zweitbelegtes Kernsymbol stehen zu lassen ist
genau die Fehlerfamilie, die dieses Dokument sonst jagt. → Vorschlag 0128.

**2. Die Inventur des Änderungsvermerks zählt falsch und unvollständig.** Z. 74-75
nennt „acht Zeilen unter ‚Was bewusst fehlt'"; der Diff (Hunk 7) zeigt sieben Einträge
(einer ergänzt, sechs neu, 33 Zeilen). Und der neue Absatz unter *Der Zustand*
(Z. 400-405, Hunk 4) fehlt in der Aufzählung ganz — der Vermerk nennt nur den Absatz
unter *Warum die Größe des Zustands keine Verteidigung ist* (Hunk 5). Der normative Teil
ist davon unberührt; nach dem Präzedenzfall vom 2026-09-04 (Befunde im Selbstbericht bei
erfüllten Bedingungen) kein Rücklauf. → mit in Vorschlag 0128.

## Wonach ich sonst gesucht habe, ohne etwas zu finden

- **Widersprüche zu `technik.md` durch dieses Paket:** keine — `technik.md` ist
  unberührt, und die Nachzugliste (Z. 2484-2506) deckt T15, T16, T5, T27, T33, T47, T39,
  T37, `weltlauf`, die Leitzinsschranke und das Laufzeitbudget ab. Stichproben: T16-Summe
  27+9+9+30 = 75, T33-Bestand 27/9/30, T15-Block 5·B = 150.
- **Die Blatt-Behauptung** (keine Größe der Schicht 1/3 liest Platzfelder, Z. 782-785):
  Die einzigen gefundenen Leser von Platzfeldern sind Marktkorb/`korbbestand` und
  `marktanteil` — Fondsteilsystem, im `weltlauf` abgeschaltet. Kein Gegenbeispiel
  gefunden; die 200-Runden-Auflage an den Bruchtester steht als mechanische Probe.
- **Undefinierte Eingaben der neuen Formeln:** jeden Namen einzeln gegriffen; einziger
  offener Punkt sind die Restwelt-Sektoranteile als Jahrgangs-Residuum, und der steht als
  offene Entwurfsfrage mit Ausweichregel (Z. 2464-2468) — nach der Ausschlussliste kein
  Befund.
- **Die Maß-2-Doppellesart** (Frontmatter „höchstens 25 Prozent besser" gegen
  `max(Ek) ≤ 1,25 · min(Ek)`): Dieses Paket definiert Maß 2 nicht um, es zitiert die
  Formel-Lesart (Z. 1176, 2449). Bleibt eine offene Fährte meiner Rolle, kein Befund
  dieses Pakets.
- **Kalibrierbare Zahlen** (`kippung`, `platzanteil`, die drei Halbierungen): als
  Parameter bzw. Literale mit Begründung gekennzeichnet (Z. 1014-1023) — nach der
  Ausschlussliste kein Befund.
