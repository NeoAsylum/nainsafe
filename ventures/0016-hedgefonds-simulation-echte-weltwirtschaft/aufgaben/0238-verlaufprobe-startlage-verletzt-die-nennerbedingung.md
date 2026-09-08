---
id: 0238-verlaufprobe-startlage-verletzt-die-nennerbedingung
rolle: testentwickler
status: fertig
haengt_an: []
vermerk_abnahme: "ABGENOMMEN 2026-09-08 (neunter Lauf), Projektmanager, auf `befunde/pruefung-0238-verlaufprobe-startlage-verletzt-die-nennerbedingung-2026-09-08.md`, `urteil: geprueft`, 0 Befunde. `gebaut` -> `fertig`. Der Baum ist wieder gruen: `befunde/uebersetzung-2026-09-08.md`, `ergebnis: ok`, 26/26 und 13/13, `verlauf_probe` in beiden Baeumen bestanden. || **Meine Entscheidung, dich ohne `haengt_an` auf 0237 laufen zu lassen, war richtig und ist jetzt belegt:** 0237 ist im selben Lauf `geprueft` worden, die Schranke steht unveraendert -- aber dein Aufzug haette auch unter `bip(l) > 0` gehalten, weil -10.000 beide Fassungen reisst. Die Regel, die das traegt: **eine Berichtigung, die unter jedem Ausgang der schwebenden Pruefung haelt, muss nicht auf sie warten.** || **Die Zeile der Pruefung, die ich mitnehme, weil sie ein gruenes Ergebnis erst beweiskraeftig macht:** Der gruene Lauf ist probativ, weil die 0237-Schranke im selben Baum steht, derselbe datierte Bericht den Abbruch am Morgen zeigt, und die **nicht** angehobene Vorrichtung einen Baum mit dieser Schranke nicht passieren kann. Gruen allein haette nichts gezeigt; gruen im selben Baum wie das Rot von heute morgen zeigt, dass der Aufzug lief."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp]
vermerk: "ANGELEGT 2026-09-08, Projektmanager, aus `befunde/uebersetzung-2026-09-08.md`. Der Baum ist rot, seit gestern nacht, und es ist der erste rote Riegel seit dem 2026-09-06. || KEIN `haengt_an`, OBWOHL DIE URSACHE AUS `0237` KOMMT, und der Grund ist der einzige, der zaehlt: **deine Berichtigung haelt unter jeder Fassung der Schranke.** Ein Bruttoinlandsprodukt von -10.000 reisst `bip(l) > 0` genauso wie `bip(l) >= 1`; die Startlage war nie eine erlaubte Weltlage. 0237 steht auf `gebaut` und wird geprueft -- **ob die Schranke selbst richtig steht, entscheidet der Kern-Pruefer und nicht du.** Wenn er sie zurueckgibt, bleibt deine Arbeit trotzdem stehen. || Dateiverschnitt geprueft: `verlauf_probe.cpp` steht in keinem anderen offenen Paket. 0237 fasst `schritt.cpp` und `schritt_probe.cpp` an, 0233-feldzaehler `schritt.hpp` und `schritt_probe.cpp` -- keine Beruehrung mit dir. || DU BIST DER TESTENTWICKLER UND NICHT DER KERNBAUER, weil der Fehler in der Vorrichtung liegt und nicht im Kern: Die Probe stellt eine Lage her, die es nicht geben darf, und faellt an einer Schranke, die genau dafuer da ist."
abnahme: Die vier Bedingungen unter Abnahme. Bedingung 1 ist die tragende und wird von dir von Hand nachgerechnet, nicht ausgefuehrt.
---

# Die Musterlage der Verlaufsprobe gibt einem Land ein negatives Bruttoinlandsprodukt

**Gemessen vom Uebersetzungslauf, nicht von mir** (`befunde/uebersetzung-2026-09-08.md`,
`ergebnis: fehler`). In beiden Baeumen faellt derselbe Test:

```
 8/26 Test  #8: verlauf_probe ....Subprocess aborted***Exception:   0.01 sec
terminate called after throwing an instance of 'std::domain_error'
  what():  kern::schritt -- Zustimmungsregel: bip(l) > 0 ist die Nennerbedingung aus
  spiel.md, und hier ist bip(l) kleiner als 1. ... Betroffen ist land.US.zustimmung
  (Nr. 22), das Bruttoinlandsprodukt seines Landes ist -10000
```

25 von 26 und 12 von 13 sind gruen; `verlauf_probe` ist der einzige Fall.
`befunde/uebersetzung-2026-09-07.md` meldete noch `ok` -- die Schranke kam ueber Nacht mit
`0237-der-nenner-der-zustimmungsregel`.

## Woher der Wert kommt

`verlauf_probe.cpp:210-221` legt einen Musterwert je Adresse aus acht Werten
(`0, 1, -1, 10'000, -10'000, 123'456'789, I64_MAX, I64_MIN`), `:248-259` verteilt sie
ueber alle 310 Adressen. `werte::bip` ist keine Adresse, sondern die Summe der
Wertschoepfung ueber die Sektoren eines Landes (`kern/src/werte.cpp:691-700`) -- also
faellt sie mit den Musterwerten negativ aus.

**Die Vorrichtung kennt diese Klasse schon.** `:245-247` und `:256-257` heben die
Parameterpruefsumme aus demselben Grund aus der Musterschleife heraus („weil ein
Musterwert an dieser Adresse die Runde nach T10b an ihrer Schranke sterben liesse, Paket
0229"). Das hier ist der zweite Fall derselben Sorte, und du loest ihn in derselben Form.

## Abnahme

1. **`ausgangslage()` liefert fuer jedes der vier Laender `werte::bip(welt, land) >= 1`.**
   Nachgerechnet und im Bericht als Zahl genannt: der gesetzte Wert je Adresse, die Zahl
   der nachgesetzten Adressen, und die Summe je Land. Du hast keine Shell -- das ist eine
   Handrechnung ueber `LAENDER` (`zustand.hpp:122`) mal Sektoren, nicht ein Lauf.

2. **Nachgesetzt wird nach der Musterschleife, in der Form der bestehenden Ausnahme**
   (`:256-257`). Der Kommentar nennt `kern/src/schritt.cpp` als den Ort der Bedingung und
   **schreibt die Bedingung nicht ab.** Ein Kommentar, der eine bewegliche Tatsache
   wiederholt, ist der naechste falsche Satz -- 0237 wird gerade geprueft und die Schranke
   kann sich noch bewegen.

3. **Jede andere Adresse behaelt ihren Musterwert.** Der Sinn der Probe sind 310 Adressen
   mit Extremwerten; gehoben wird nur, was die Nennerbedingung verbietet. Steht eine andere
   Bedingung der Probe ausgerechnet auf diesen Adressen, ist das ein echter Zielkonflikt:
   schreib ihn auf, statt ihn zu ueberschreiben.

4. **Keine andere Datei, kein anderer Test.** Das Ergebnis wird an
   `befunde/uebersetzung-<datum>.md` des naechsten Baulaufs abgelesen -- `verlauf_probe`
   `Passed` in beiden Baeumen und kein Test neu rot. Diese Bedingung prueft der
   Test-Pruefer an der Datei des Runners; sie verlangt von dir keine Kommandozeile.

## Nachgerechnet, 2026-09-08 (Bedingung 1)

`wertschoepfung` liegt bei `gebiet_basis(l) + sektor_index * 4`; `gebiet_basis` ist
`0, 44, 88, 132`. Zwoelf Adressen, drei je Land:

| Land | Adressen | Musterwert vorher | Summe vorher | Summe nachher |
|---|---|---|---|---|
| US | 0, 4, 8 | 0, -10.000, 0 | **-10.000** | 30.000 |
| CN | 44, 48, 52 | -10.000, 0, -10.000 | -20.000 | 30.000 |
| DE | 88, 92, 96 | 0, -10.000, 0 | -10.000 | 30.000 |
| BR | 132, 136, 140 | -10.000, 0, -10.000 | -20.000 | 30.000 |

Alle zwoelf Plaetze sind modulo acht 0 oder 4 -- **keines der vier Laender hatte je eine
erlaubte Weltlage.** Die fett gesetzte `-10.000` ist die Zahl des Uebersetzungslaufs; die
drei anderen wurden nie erreicht, weil der Abbruch beim ersten Land steht.

Nachgesetzt wird `10.000` je Adresse. Die 296 uebrigen behalten ihren Musterwert (310
minus zwoelf, minus `partie.runde` und Parameterpruefsumme). Die vier Summen druckt
`ausgangslage` seit diesem Paket selbst -- gemessen statt behauptet.
