---
id: 0025-quelleneinheit-pwt-baci
rolle: datenbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/einheitenbefund-pwt-baci.md]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Drei ungemessene Einheiten, und an einer hängt die schwerste offene Entscheidung

Vorgaben: `technik.md` T5 (Skalenklassen, Klasse 2 „Tausend USD zu konstanten Preisen des
Basisjahrs"), T23–T26 (Jahrgangsbau), T42 (Maßstab des Rückvergleichs).
`specs/…/daten.md` Nr. 3 (CEPII BACI) und Nr. 4 (Penn World Table 11.0) für Quelle,
Lizenz und Zitierpflicht. Anlass: `befunde/pruefung-0017-reihenliste-maschinenlesbar-2026-09-02.md`,
Befund 2, und `rueckstand.md` Punkt 3.

**Dieses Paket hängt an keinem anderen.** Es braucht keinen Kern, keinen Zustand und keine
Übersetzung — es misst gegen die Dokumentation zweier Quellen. Damit ist es sofort baubar.

## Was ungemessen ist, wörtlich aus `daten/reihen.toml`

Die Reihenliste hat die Lücken richtig offengelassen, statt eine `1` hinzuschreiben, und
nennt sie an drei Stellen:

| Stelle | Zeile | Wortlaut |
|---|---:|---|
| Reihe 3, PWT-Kapitalstock | 475 | „Die Quelleneinheit des PWT-Kapitalstocks ist in keiner der drei Befunddateien gemessen. Der Umrechnungsfaktor in Tsd USD steht deshalb als ungemessen und nicht als 1." |
| Reihe 3, Basisjahr | 289 | „Welches Basisjahr PWT 11.0 traegt, ist ungemessen. Ein Ersatz, der das Basisjahr wechselt, aendert die Sollreihe und damit den Massstab von T42." |
| Reihe 14, BACI | 1260–1261 | „Die Quelleneinheit von BACI ist in keiner der drei Befunddateien gemessen. … Ob BACI in laufenden oder konstanten Preisen meldet, ist ebenfalls ungemessen." |

Dazu Reihe 16 (`durchgriff`), Zeile 1392: *„H (Aus- plus Einfuhr aus BACI) und N
(Wertschoepfung aus WDI) muessen in derselben Einheit stehen, sonst ist der Quotient
bedeutungslos."*

## Warum das nicht folgenlos ist

**Eine `1` wäre bei PWT stumm und um den Faktor 1.000 falsch.** Der Kapitalstock geht in
die volkswirtschaftliche Skala (T5 Klasse 2, Tausend USD). Steht die Quelle in Millionen
oder in ganzen USD, verschiebt eine angenommene `1` jeden Wert um drei Größenordnungen —
und zwar ohne dass irgendeine Wertebereichsschranke anschlägt, weil `9,2 · 10^13` weit weg
ist und ein zu kleiner Kapitalstock einfach wie ein armes Land aussieht.

**An BACI hängt Maß 4.** T5 verlangt für Klasse 2 konstante Preise. Meldet BACI in
laufenden Preisen, misst der Rückvergleich Inflation statt Modellgüte — das ist die
schwerste offene Sache des Vorhabens (`rueckstand.md` Punkt 3), sie blockiert Paket 0002
und über 0002 das Paket 0010. **Solange die Preisbasis nicht gemessen ist, ist die Frage
an den Architekten nicht einmal richtig gestellt.**

**Und an derselben Messung hängt `durchgriff`.** Reihe 16 teilt eine BACI-Größe durch eine
WDI-Größe. Stehen beide in verschiedenen Einheiten, ist der Quotient bedeutungslos — und
er sieht dabei aus wie eine Zahl.

## Was du tust

Leg `daten/einheitenbefund-pwt-baci.md` an und miss die drei Größen gegen die
**Dokumentation der Quellen**, nicht gegen unsere eigenen Dateien. Die Belegstellen für
Quelle, Lizenz und Zitierpflicht stehen in `specs/…/daten.md` Nr. 3 und Nr. 4; die
Endpunkte dort sind der Ausgangspunkt, nicht die Antwort.

Gemessen wird je Größe: der **Feld- oder Variablenname der Quelle**, die **Einheit im
Wortlaut der Quellendokumentation**, die **Abruf-URL** und das **Abrufdatum**. Daraus
leitest du den Umrechnungsfaktor nach Tausend USD ab und schreibst die Rechnung hin.

**Du entscheidest nichts.** Ob Klasse 2 laufende Preise verträgt, ob eine Reihe die Klasse
wechselt oder ob ein Deflator dazukommt, ist Sache des Architekten. Du lieferst die Zahl,
gegen die er entscheidet, und die Frage in der Form, in der sie entscheidbar ist.

**Du fasst `daten/reihen.toml` nicht an.** Die Datei liegt in Paket 0022 beim Prüfer; der
Übertrag der gemessenen Faktoren ist ein eigenes Paket, sobald dieser Befund steht. So ist
es bei den Lizenzen auch gelaufen (`lizenzbefund-*.md` vor `reihen.toml`).

## Abnahme

1. **Für jede der drei Größen** — PWT-Kapitalstock, PWT-Basisjahr, BACI-Handelswert —
   steht im Befund entweder (a) Feld-/Variablenname, Einheit im Wortlaut, Abruf-URL,
   Abrufdatum und der daraus abgeleitete Umrechnungsfaktor nach Tausend USD als exakte
   Ganzzahl oder als Bruch, **oder** (b) eine ausgewiesene Nichtmessung mit der offenen
   Frage, dem, was du dafür abgerufen hast, und der Stelle, an der sie zu klären wäre.
   **Kein Faktor ohne Zitat, und keine `1` als Vorgabewert.**
2. **Für BACI steht zusätzlich die Preisbasis** — laufende oder konstante Preise — im
   Wortlaut der Quellendokumentation, mit derselben Belegpflicht wie unter 1, oder als
   ausgewiesene Nichtmessung.
3. **Die Folge für T5 Klasse 2 ist als Frage formuliert, nicht als Entscheidung.** Fällt
   die Messung auf „laufende Preise", nennt der Befund die Möglichkeiten, die `specs/`
   offenlässt, und den Adressaten (Architekt, `technik.md`) — und wählt keine aus.
4. **Reihe 16 ist mitbeantwortet:** Der Befund sagt ausdrücklich, ob die gemessene
   BACI-Einheit dieselbe ist wie die der WDI-Wertschöpfung, oder mit welchem Faktor sie
   sich unterscheidet, oder dass es ungemessen bleibt.
5. **Nichts ausser der neuen Datei ist angefasst.** `daten/reihen.toml`,
   `daten/lizenzbefund-*.md`, `parameter.toml` und `specs/` sind unverändert. Der Befund
   trägt Frontmatter in derselben Form wie die drei bestehenden Befunddateien in `daten/`.

## Was ausdrücklich kein Befund ist

- **Dass die Lizenzurteile zu PWT und BACI unangetastet bleiben.** Beide sind in
  `daten.md` und `lizenzbefund-reihen.md` als `frei` gemessen; dieses Paket misst
  Einheiten, keine Lizenzen.
- **Dass keine Rohdatei heruntergeladen wird.** Die Einheit steht in der Dokumentation.
  Rohdaten hat in diesem Vorhaben ohnehin niemand (`rueckstand.md`).
- **Die Form der Datei** — Tabelle oder Fließtext. `specs/` schweigt dazu.

## Rückläufe

0.
