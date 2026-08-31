# Logbuch: spielentwerfer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/spielentwerfer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

- 2026-08-31 — **Die Datenlage entscheidet den Zuschnitt, nicht der Geschmack.** Die Idee
  nannte 12 Länder, 6 Sektoren, Quartalsrunden; `daten.md` nannte dazu vier Lücken. Wer
  die Lücken zuerst liest und den Entwurf danach schneidet (4 Länder, 3 Sektoren,
  Jahresrunden), bekommt jede Entscheidung mitgeliefert und muss nichts abwägen. Der
  Datenkurator vor dem Spielentwerfer ist die richtige Reihenfolge.
- 2026-08-31 — **Jede Verkleinerung gegen ein Maß verteidigen, jede Vergrößerung auch.**
  Vier Länder statt drei habe ich mit Maß 1 begründet (bei drei hat jeder Zoll genau einen
  Ausweichpartner, die Wahl ist keine), drei Sektoren statt sechs mit der vierten Achse
  (sechs wären ein Konstrukt ohne Sollreihe). Das ergibt Zahlen, die man verteidigen kann,
  statt Zahlen, die plausibel klingen.
- 2026-08-31 — **Die Gegenkraft gehört in die Siegbedingung, nicht daneben.** Das Mandat
  verlangt Kapital UND Einfluss; Einfluss ist genau die Größe, deren Erwerb Aufsicht,
  Gegenlobby und Regierungswechsel weckt. Damit ist die selbstverstärkende Schleife im
  Ziel gebrochen und nicht erst in der Balance. Für den nächsten Entwurf im Genre: zuerst
  fragen, was der Sieg verlangt, und dann prüfen, ob dessen Erwerb sich selbst bestraft.
- 2026-08-31 — **Zwei Regeln erzwingen Maß 3, statt es zu erhoffen:** Nachahmer
  (funktionierende Position wird abgegrast) und Marktenge (Überrendite fällt mit dem
  Marktanteil). Beide sind bloße Zähler mit Schwelle, kosten also keine Schicht. Eine
  Optimumsverschiebung, die aus Regeln folgt, überlebt jede Kalibrierung; eine, die aus
  Zahlenwerten folgt, nicht.
- 2026-08-31 — **Long UND short ist die billigste Antwort auf „eine Richtung dominiert".**
  Weil der Fonds gegen eine Politik verdienen kann, ist keine politische Richtung
  vorteilhaft — genau die Klage aus Democracy 4 („socialism always bankrupts you"), ohne
  eine einzige Ausgleichsregel.
- 2026-08-31 — **Schwellenwerte gehören nicht in den Entwurf.** Ich habe die *Form*
  festgelegt (Mandat zweiteilig, Aufsicht dreistufig, höchstens drei Aktionen je Runde)
  und die Zahlen ausdrücklich der Kalibrierung durch das Selbstspiel überlassen. Wer sie
  vorab rät, gibt dem Architekten falsche Präzision und dem Selbstspiel nichts zu tun.

## Was nicht funktioniert

- 2026-08-31 — **Quartalsrunden für einen Hedgefonds klingen zwingend und sind es nicht.**
  Alle Kernreihen außer Zins, Wechselkurs und DOTS liegen jährlich vor; Quartalstakt hätte
  drei von vier Runden vom Rückvergleich abgeschnitten — also die einzige Achse geschwächt,
  die diese Fabrik gegenüber einem Studio voraushat. Genre-Erwartung schlägt Datenlage
  nicht. Ersatz für das verlorene Innerjahresrisiko: Hebelprüfung gegen einen
  deterministischen Ausschlag aus der historischen Schwankungsbreite, statt gegen den
  Jahresendstand.
- 2026-08-31 — **Keine Websuche gefahren, bewusst.** `daten.md` (13 Quellen), das
  Marktprofil (Rezensionsvolltexte, Preise, Kohortenmessung) und `agentenbau.md` deckten
  jede Frage, an der der Entwurf hing. Die Faustregel „suche, wenn dich eine Antwort
  blockiert" hat hier zu null Suchen geführt, und das war richtig — die Vorstufen hatten
  die Arbeit schon getan.

## Offene Faehrten

- **Die schwerste offene Frage des Entwurfs steht in `spiel.md`:** Ist der aggregierte
  Zollsatz der Weltbank (WITS-Herkunft, Drittanbieter-Ausnahme) verwendbar? Ist er
  gesperrt, verliert der Rückvergleich das wichtigste der drei verankerten Instrumente.
  Der Entwurf bleibt tragfähig, sein Beleg halbiert sich.
- **Startjahr 1980 gegen 2000** hängt an der tatsächlichen Reihenlänge von CEPII BACI je
  Land. Nicht vorab entschieden, weil es eine Messung ist und keine Wahl.
- **Deutschland vor/nach 1999** (D-Mark, dann Euro, nationaler Zinshebel nur davor): Der
  Bruch ist im Modell gewollt und in der Sollreihe ein Bruch. Wie das Fehlermaß ihn nicht
  als Modellfehler liest, ist offen.
- **Fremder Befund, nicht mein Verzeichnis:**
  `signals/maerkte/2026-08-31-volkswirtschafts-und-politiksimulation.md` endet in Zeile
  342/343 mit zwei versehentlich mitgeschriebenen Werkzeug-Tags (`</content>`,
  `</invoke>`). Inhaltlich folgenlos, aber es zeigt, dass die Endung einer geschriebenen
  Datei geprüft gehört — mir ist derselbe Fehler in diesem Lauf einmal passiert und beim
  Nachsehen aufgefallen.
