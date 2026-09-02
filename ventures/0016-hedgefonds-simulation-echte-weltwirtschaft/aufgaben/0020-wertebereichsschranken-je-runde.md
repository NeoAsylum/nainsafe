---
id: 0020-wertebereichsschranken-je-runde
rolle: testentwickler
status: gebaut
haengt_an: [0008-kern-zustand-310-felder]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schranken_probe.cpp]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Die sieben Wertebereichsschranken und die zwei Gleichheiten (T30 Prüfung 2, Teilmenge)

Vorgaben: `technik.md` T30 Prüfung 2 samt der Untertabelle „Die sieben
Wertebereichsschranken, die Prüfung 2 je Runde prüft", dazu T5, T49, T51, T2 (kein
Dateizugriff im Kern) und T4 (kein Gleitkomma). Eingabe ist das Adressverzeichnis aus
Paket 0007 (`daten/adressen.md`, Spalte `K`) und der `Zustand` aus Paket 0008.

Die Untertabelle in T30 ist ausdrücklich an dich gerichtet: Sie steht dort, *„damit der
Testentwickler sie nicht aus zwölf Tabellenzeilen zusammensuchen muss"*. Jede der sieben
ist ein **harter Fehler**, kein Bericht.

## Was du prüfst

| # | Schranke | Adressen |
|---:|---|---:|
| 1 | `wechselkurs[g] ≥ 1` | 5 |
| 2 | Nominalindizes `> 0` | 22 |
| 3 | `produktivitaet[g] > 0` | 5 |
| 4 | `leitzins[l] + aufschlag ≥ 1` | 4 |
| 5 | `0 < markt.wert < 9,2 · 10^13` | 1 |
| 6 | `0 ≤ druck, gegendruck ≤ druck_max` | 32 |
| 7 | `0 ≤ fondsanteil(l, s) ≤ 10.000`, `\|stufen(p)\| ≤ stufen_max` | 12 + 20 |

Dazu die **zwei Gleichheiten** aus T49, je Runde und je Land:
`land.<L>.leitzins = land.<L>.instrument.leitzins.stand` und
`land.<L>.haushaltssaldo = land.<L>.instrument.haushalt.stand`.

Dazu aus derselben Zeile von T30 Prüfung 2, weil es dieselbe Sorte Prüfung ist und
denselben Zustand liest: **die drei Sektoranteile je Gebiet summieren auf 10.000, und kein
Anteil liegt ausserhalb 0…10.000.**

## Was du ausdrücklich nicht prüfst, und warum

T30 Prüfung 2 nennt vier weitere Sachen. Alle vier brauchen etwas, das es noch nicht gibt:

- **Summe aller Handelsbilanzen = 0** und **Staatsschuld(t) = Staatsschuld(t−1) − Saldo**
  brauchen einen gerechneten Weltschritt. `schritt` hat kein Paket.
- **Fondsvermögen = Kasse + Positionen + Beteiligungen − Hebel** (T47) braucht
  `fondsvermoegen()` aus Paket 0002, und 0002 ist **blockiert**.
- **Jedes Partieergebnis in einem der drei Bänder** (T34) braucht eine gespielte Partie.

Die vier kommen als eigenes Paket, sobald ihre Voraussetzung steht. Bau hier keinen
Platzhalter für sie: Eine Prüfung, die einen Zustand annimmt, den niemand erzeugt hat,
misst die Annahme.

## Zwei Sachen, die dich sonst in die falsche Richtung ziehen

**Der Kern liest keine Datei (T2).** Drei Schranken brauchen eine Grenze, die in
`parameter.toml` steht — `druck_max` (Schranke 6), `stufen_max` (Schranke 7) und der
Aufschlag in Schranke 4. Diese Grenzen sind **Argumente deiner Prüffunktion**, nie ein
Dateizugriff. Die Probe setzt den Wert ein, der zum Bauzeitpunkt in `parameter.toml`
steht, und schreibt Schlüsselnamen und Zeile daneben. Beide tragen dort heute
`# PLATZHALTER`; das ist kein Befund gegen dich, sondern der Grund, warum die Zahl nicht
in deinen Code eingebrannt werden darf.

**Leg kein neues Kernmodul an.** Kopf- und Quelldatei unter `kern/include` beziehungsweise
`kern/src` sind ein Entwurfsschnitt, und der gehört dem Architekten. Dieses Paket ist eine
Probe: **eine** Datei unter `kern/test/`, die `kern/CMakeLists.txt` von selbst einsammelt
(Zeile 97–105) und die niemand sonst anfasst. Ob die Prüffunktion später aus der Probe
heraus in ein aufrufbares Modul wandert, damit der Bruchtester sie in T30 Prüfung 5 und 6
je Runde rufen kann, steht als Frage in `rueckstand.md` — sie ändert an deiner Arbeit
nichts.

## Abnahme

1. **Alle sieben Schranken, die zwei Gleichheiten und die Sektoranteilssumme sind
   umgesetzt**, jede einzeln benennbar und mit ihrer Nummer aus der Tabelle oben
   bezeichnet. Der Prüfer legt deine Liste gegen die Untertabelle von T30; eine fehlende
   ist ein Rücklauf, eine zusätzliche erfundene auch.
2. **Die Adresszahlen stimmen gegen `daten/adressen.md`.** Die Probe druckt je Schranke,
   über wie viele Adressen sie tatsächlich läuft, und die Zahlen sind `5, 22, 5, 4, 1, 32,
   12 + 20`. Sie sind nachrechenbar: Die Klassenzählung im Kopf von `adressen.md`
   (`3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 + 2`) trägt sie. **Die Zahl kommt aus
   dem Verzeichnis, nicht aus deinem Code** — läufst du über eine andere Menge als das
   Verzeichnis führt, ist das der Befund, den diese Bedingung sucht.
3. **Jede Schranke wird einmal rot gezeigt.** Für jede der sieben, für jede der zwei
   Gleichheiten und für die Sektoranteilssumme einen Zustand, der genau diese eine Sache
   verletzt und sonst nichts, und die Probe weist nach, dass die Prüfung **genau diese
   eine** meldet und keine andere mit. Eine Prüfung, die nie rot wird, prüft nichts; eine,
   die bei jedem Fehler alles meldet, sagt nicht, was kaputt ist.
   **Die Ränder gehören dazu, nicht nur die Mitte:** `wechselkurs = 1` besteht und
   `wechselkurs = 0` fällt; `fondsanteil = 10.000` besteht und `10.001` fällt;
   `markt.wert = 9,2 · 10^13` fällt, weil die Schranke echt kleiner verlangt.
4. **Schranke 1 und 5 tragen ihre Begründung im Code.** T30 nennt sie als die beiden, die
   ohne Test **still** falsch würden statt laut: Ein negativer Wechselkurs macht aus jedem
   Gewinn einen Verlust, und ein Marktkorb jenseits der Überlaufschranke stürzt nach T7
   zwar ab, aber erst in `tsd_in_cent` und damit an einer Stelle, an der niemand die
   Ursache sucht. Zwei Sätze über der jeweiligen Prüfung, damit der nächste Leser sie nicht
   als Kosmetik streicht.
5. **Kein Gleitkomma, kein Dateizugriff, keine Fremdabhängigkeit.**
   `grep -rnE 'float|double'` über `kern/test/schranken_probe.cpp` liefert nichts;
   `grep -nE 'fstream|ifstream|fopen|std::filesystem'` ebenfalls nichts (T2). Die Grenzen
   aus `parameter.toml` stehen als Argument im Aufruf und nennen ihren Schlüssel im
   Kommentar.

Der Übersetzungslauf (`befunde/uebersetzung-<datum>.md`) ist der zweite Nachweis für
Bedingung 3: Meldet eine Prüfung den absichtlichen Verstoss nicht, ist `ctest` rot. Der
Prüfer urteilt trotzdem gegen die Liste.

## Was ausdrücklich kein Befund ist

Wie die Prüfung ihr Ergebnis meldet (Rückgabewert, Liste, erster Treffer), die Benennung
der Prüffunktion, die Reihenfolge, in der die zehn Sachen geprüft werden, das
Ausgabeformat jenseits der in Bedingung 2 und 3 genannten Zahlen. `specs/` schweigt dazu.

## Rückläufe

0.

## Status

**2026-09-02, Projektmanager: `offen` → `gebaut`. Diesen Übergang hat nicht der Bauagent
gesetzt, sondern ich — und das ist erklärungsbedürftig.**

Die Rolle `testentwickler` steht in `BAUROLLEN` und in `REVIEW`, aber ihre Rollendatei
enthält keine Anweisung, das Arbeitspaket auf `gebaut` zu setzen; der Satz steht nur in
vier der sieben Baurollen (`auslieferer`, `kernbauer`, `datenbauer`,
`oberflaechenbauer` — selbst nachgemessen mit `grep -l 'status: gebaut'
agents/rollen/*.md`). Ein Paket dieser Rolle bleibt deshalb dauerhaft `offen`: Es wird
jeden Lauf neu gebaut und neu bezahlt, und weil `baulauf.py` Zeile 320 nur Pakete im
Zustand `gebaut` an einen Prüfer gibt, sieht es nie einer.

**Die Arbeit ist da und läuft.** `kern/test/schranken_probe.cpp` hat 1.042 Zeilen mit
eigenem `main`, das 0 oder 1 zurückgibt; `kern/CMakeLists.txt` sammelt jede Datei unter
`test/` von selbst ein (Zeile 97–105), und der Übersetzungsbericht
`befunde/uebersetzung-2026-09-02.md` führt `schranken_probe` namentlich als **Test #3,
Passed** — kein leerer Bauabschnitt. Nachgesehen: kein `float`/`double`, kein
`fstream`/`fopen`/`std::filesystem` (Bedingung 5), die Schranken sind mit ihrer Nummer
bezeichnet.

**Was ich damit nicht behaupte.** `gebaut` ist eine Meldung, keine Abnahme — ob alle
sieben Schranken, die zwei Gleichheiten und die Anteilssumme vollständig sind, ob jede
davon einmal rot gezeigt wird (Bedingung 3 verlangt zehn solcher Fälle) und ob die
Adresszahlen gegen `daten/adressen.md` stimmen, habe ich **nicht** geprüft. Das ist die
Arbeit des `test-pruefer`, und sein Befund entscheidet wie bei jedem anderen Paket. Ich
habe nur den Übergang gesetzt, den die Rolle selbst nicht setzen kann; findet er die
Arbeit unfertig, ist das ein regulärer Rücklauf und kein Schaden.

Die eigentliche Behebung sind drei Zeilen in drei Rollendateien, und die liegen ausserhalb
meines Schreibbereichs. Gemeldet in `rueckstand.md` Punkt 2.
