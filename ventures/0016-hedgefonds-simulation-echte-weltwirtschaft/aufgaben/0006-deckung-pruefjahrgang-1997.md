---
id: 0006-deckung-pruefjahrgang-1997
rolle: datenbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/deckungsbefund-1997.md]
abnahme: Für jede der 31 Sollreihen und für den Handelsblock steht im Befund, ob sie 1997 bis 2021 ohne Füllung 25 Stützstellen trägt, mit Abruf-URL und Abrufdatum; am Ende steht genau ein Wert für R und die Liste der Reihen, die ihn erzwungen haben.
---

# Trägt der Prüfjahrgang 1997–2021 wirklich 25 Stützstellen ohne Füllung?

**Das ist die Stelle, an der das Vorhaben an Daten scheitern kann**, und `technik.md`
T24 sagt es wörtlich: „25 Stützstellen ohne Füllung für alle 31 Reihen und alle 40
Handelsströme sind eine Behauptung, keine Tatsache." Abschnitt 13 zählt dieses Paket
deshalb zu den beiden vorzuziehenden.

Vorher lesen: `technik.md` T23, T24, T40, die Reihenliste in Abschnitt 7; `spiel.md`
*Offene Entwurfsfragen* (Absatz „Bleibt das Fenster bei 1997–2021?"); `daten.md`.

## Was du misst

Die **31 Sollreihen** sind nach der Reihenliste die Zeilen 1, 2, 8, 9, 10 und 11
(4 + 12 + 4 + 4 + 3 + 4), dazu der Handelsblock aus Zeile 14 (5 × 4 × 2 = 40 Ströme).
Je Reihe, Land und Jahr: Gibt es einen Wert, oder müsste er nach T24 als `gefuellt`
gekennzeichnet werden?

**Der Verdachtsfall zuerst, weil er den Rest entscheidet:** die chinesische und die
brasilianische **Leitzinsreihe** der neunziger Jahre (Reihe 9, IWF IFS). `spiel.md` hat
sie gegen `FR.INR.LEND` geprüft — China 1995–2023 lückenlos, Brasilien ab 1997 — und
nennt das ausdrücklich ein Indiz und keinen Beweis: `FR.INR.LEND` ist eine andere Reihe
als der IFS-Leitzins, und `imf.org` weist den Abruf mit HTTP 403 ab (zweimal belegt,
`spiel.md` und der Prüfbefund der Runde 6, beide 2026-09-01). **Prüf die Reihe, die
tatsächlich eingebettet wird.** Kommst du an IFS nicht heran, schreib das hin, nenne die
abgewiesene URL mit Datum und benenne die Ersatzreihe samt dem, was sie nicht beweist —
eine Sackgasse, die dokumentiert ist, spart dem nächsten Lauf denselben Weg.

## Was im Befund steht

1. **Eine Tabelle je Reihe** mit Nummer, Indikatorcode oder Quelle, Abruf-URL,
   Abrufdatum, erstem und letztem verfügbaren Jahr je Land, Zahl der Lücken innerhalb
   1997–2021.
2. **Der Handelsblock** wird nicht Strom für Strom abgerufen, sondern über die
   Jahresabdeckung von BACI: erstes und letztes Jahr, und ob 1997 enthalten ist.
3. **Genau ein Wert für R** am Ende, nach T40. Trägt das Fenster 1997–2021 vollständig,
   ist `R = 24`. Trägt es das nicht, ist R kleiner, und dann steht daneben, **welche
   Reihen** ihn erzwungen haben — nach T40 kostet das eine Zahl im Manifest und sonst
   nichts, und `spiel.md` sagt: „Misst der Jahrgangsbau ein engeres Fenster, ist R zu
   ersetzen und sonst nichts."
4. **Die Gegenprobe zu `R ≤ 26`**, die T40 in den Jahrgangsbau zieht: Bei `R = 27`
   fielen das Band „überlebt" und das Todesband auf 31.000 zusammen. Für jedes R, das du
   misst, steht hin, ob es die Schranke hält.

## Was du nicht tust

- **Du füllst nichts.** T24 verbietet es für den Prüfjahrgang ausdrücklich: Eine Reihe,
  die 25 Stützstellen nicht trägt, wird als Befund gemeldet, samt der beiden Auswege,
  die dem Spielentwerfer zustehen — Reihe streichen oder Fenster kürzen. Welchen er
  nimmt, entscheidest nicht du.
- **Du lädst nichts herunter und bettest nichts ein.** Dieses Paket erzeugt eine
  Textdatei. Der Jahrgangsbau selbst ist ein späteres Paket und braucht diesen Befund
  als Eingabe.
- **Du prüfst keine Lizenzen.** Das ist Paket 0005, es läuft parallel.

## Rückläufe

0.
