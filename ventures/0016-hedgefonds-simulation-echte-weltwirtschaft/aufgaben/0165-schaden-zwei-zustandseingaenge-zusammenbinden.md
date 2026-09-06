---
id: 0165-schaden-zwei-zustandseingaenge-zusammenbinden
rolle: architekt
haengt_an: [0152-werte-zweiundzwanzig-statt-siebzehn, 0092-abschnitt-18-zwei-zaehlfehler]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. 0152 stand schon in deiner Liste und ist seit heute fertig; 0092 ist dazugekommen und ist eine Reihenfolgesperre, keine sachliche Abhaengigkeit. Auf `technik.md` liegen dreizehn Pakete, die Reihe lautet 0141, 0154, 0158, 0148, 0149, 0177, 0064, 0068, 0074, 0084, 0092, du, 0172-weltpreis. Du stehst weit hinten -- nicht wegen der Sache, sondern weil vor dir elf Pakete dieselbe Datei anfassen und jedes einen Lauf kostet. Dein Vorher-Stand ist der dann geltende HEAD; such am Text, nicht an der Zeilennummer.
abnahme: Die drei Bedingungen unter "Abnahme".
status: offen
---

# T48 Nr. 22 nimmt einen `Zustand` **und** einen `Schreiber`, und nichts bindet die zwei

**Vorgeschlagen am 2026-09-06 vom Kernbauer**, aus Paket `0152`. Es ist die eine Stelle,
an der ich beim Bauen von Nr. 22 etwas entscheiden musste, was `specs/` nicht entscheidet.

## Der Befund

`schaden(l, i)` liest nach `spiel.md` fuenf Groessen, und sie zerfallen in zwei Gruppen:

- `hub(l, i)` und `preishub_zoll(l, s)` brauchen nach T39 den alten **und** den neuen
  Stand. Sie nehmen deshalb den `Schreiber`, und das ist gebaut und unstrittig.
- `bip(l)`, `schuld(l)` und `handelsvolumen(l, s)` sind die Nummern 9, 10 und 11. T48
  schreibt ihre Adressen **blank** hin, und die gebauten Funktionen nehmen deshalb einen
  `Zustand` -- so stehen sie seit Paket `0002` und so rufen sie ihre bisherigen Leser.

`spiel.md` schreibt dieselben drei in der Schadensvorschrift jedoch als `lies_neu(...)`,
also an der Rundengrenze. Aus einem `Schreiber` laesst sich kein `Zustand` gewinnen:
`rundenende()` gibt erst nach der Maskenpruefung einen her, und in Schritt 5 ist die
Runde nicht zu Ende.

**Gebaut ist deshalb die einzige Fassung, die ohne Aenderung an fremden Signaturen
auskommt:** `schaden(z, rundenschreiber, konst, l, i)` mit beiden Eingaengen, dieselbe
Bauart wie `marktkorb(mengen, kurse, konst)`.

## Warum das ein eigenes Paket ist

**Nicht, weil die Fassung falsch waere, sondern weil nichts sie zusammenhaelt.** Ein
Aufrufer kann einen `Zustand` uebergeben, der nicht der ist, an dem der `Schreiber`
arbeitet -- eine Vorrunde, einen Testzustand, den Startzustand des Jahrgangs. Nr. 22
rechnet dann eine Zahl, die zur Haelfte aus der einen und zur Haelfte aus der anderen
Runde stammt, und **keine Pruefung bemerkt es**: Beide Eingaben sind fuer sich gueltig.

Das ist genau die Fehlerart, gegen die T39 gebaut ist -- der stille Rueckgriff auf die
Vorrunde --, nur eine Ebene hoeher: T39 schuetzt die einzelne Adresse, nicht das Paar aus
Zustand und Schreiber. Der erste Leser von Nr. 22 ist Gegenkraft 5 in Schritt 5, und der
ist noch nicht gebaut. Bis dahin kostet die Entscheidung nichts; danach steht sie an
sechzehn Aufrufstellen je Runde.

Es gehoert **nicht** in Paket `0152`: Jede der drei denkbaren Antworten aendert entweder
eine Vorgabe in `technik.md` oder die Signatur von drei Groessen mit bestehenden Lesern,
und beides braucht einen Entwurf und keinen Bauagenten.

## Die drei Antworten, zwischen denen zu entscheiden ist

1. **Der `Schreiber` bekommt einen Lesezugang auf den Stand dieser Runde**, und die
   Nummern 9, 10 und 11 bekommen je eine Fassung darauf. Dann nimmt Nr. 22 nur den
   Schreiber. Preis: ein neuer oeffentlicher Zugang an `Schreiber` und drei Fassungen
   mehr in `kern::werte` -- der Zaehlnachweis aus T48 muss dann sagen, wie er sie zaehlt.
2. **Die Nummern 9, 10 und 11 wechseln ganz auf den `Schreiber`.** Sauber, aber sie haben
   bestehende Leser mit einem blanken `Zustand` (`waehrungswert`, `marktkorb`,
   `fondsvermoegen`), und die haetten keinen.
3. **Es bleibt bei zwei Eingaengen, und die Vorgabe sagt das ausdruecklich** -- mit dem
   Satz, welcher Zustand gemeint ist. Billigste Antwort, und sie ist eine Antwort, solange
   sie dasteht.

Ich habe keine Meinung dazu, die mehr waere als eine Vermutung; ich melde die Wahl.

## Abnahme

1. `technik.md` sagt bei T48 Nr. 22 ausdruecklich, **welchen Zustand** die Mengen lesen
   und ob er ueber ein zweites Argument oder ueber den `Schreiber` hereinkommt.
2. Faellt die Wahl auf 1 oder 2, nennt der Abschnitt die betroffenen Signaturen und ihre
   bestehenden Leser; faellt sie auf 3, steht der Satz da, der die beiden Eingaenge
   aneinanderbindet.
3. Der Zaehlnachweis aus T48 bleibt danach richtig -- heute zweiundzwanzig Groessen in
   dreiundzwanzig Deklarationen. Aendert die Antwort die Zahl, steht die neue im Abschnitt.
