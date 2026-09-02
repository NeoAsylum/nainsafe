---
id: 0015-adressen-markierungssatz
rolle: datenbauer
status: gebaut
haengt_an: [0007-adressverzeichnis-310]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md]
abnahme: Die Beschreibung der `*`-Markierung in der Spaltentabelle sagt dasselbe wie die tatsächlich angewandte Regel unter Befund 2 derselben Datei; die 310 Zeilen und alle vier Zählungen sind unverändert.
---

# Ein Satz in `daten/adressen.md`, der etwas anderes sagt als die Datei tut

Vorgabe: der Prüfbefund `pruefung-0007-adressverzeichnis-310-2026-09-02.md`, Befund 2.
Kein Rückgabegrund für 0007 — dessen Abnahmekriterium verlangt die Markierung, nicht
ihre Beschreibung, und die Markierung stimmt.

## Der Befund, in drei Sätzen

Die Spaltentabelle der Datei sagt über das Sternchen: *„Ein `*` heisst: die Adresse steht
in **keinem Dokument wörtlich**."* Angewandt ist eine andere Regel, und sie steht in
derselben Datei unter *Befund 2*: *„Die Marke sitzt an der **Neuheit**, nicht am
Zitat"* — markiert werden die erfundenen **Bestandteile**. Der Prüfer hat vier
unmarkierte Adressen nachgeschlagen, die in `specs/` null Treffer haben
(`land.US.sektor.1.wertschoepfung`, `land.US.aufsichtszaehler`, `handel.US.CN.1`,
`fonds.position.US.1`); nach dem wörtlichen Satz müssten sie eine Marke tragen.

Die angewandte Regel ist die brauchbare — die wörtliche Lesart würde rund 296 der 310
Zeilen markieren und nichts mehr unterscheiden. **Zu ändern ist der Satz, nicht die
Markierung.**

## Warum das nicht folgenlos ist

Der Satz ist schon abgewandert: `parameter.toml` aus Paket 0009 übernimmt ihn wörtlich
und verweist dabei auf das Adressverzeichnis. Dort **stimmt** er, weil Schlüsselnamen
keine Gebiets- und Sektorindizes tragen — derselbe Satz steht damit in zwei Dateien und
bedeutet zweierlei. Wer später prüft, ob eine Adressform belegt ist (die offene Frage
`gebiet.<G>.` gegen `land.<L>.` etwa), könnte aus dem fehlenden Sternchen schliessen,
`handel.US.CN.1` sei in `specs/` belegt. Es ist nicht.

## Was du tust

Bring die Beschreibung in der Spaltentabelle auf die Formulierung, die unter *Befund 2*
derselben Datei steht, und sag dort in einem Halbsatz, dass die Marke an den
Bestandteilen sitzt und nicht an der ganzen Zeichenkette. **Sonst nichts.**

`parameter.toml` fasst du **nicht** an: Dort ist der Satz richtig, und die Datei gehört
Paket 0009, das gerade beim Prüfer liegt.

## Abnahme

1. Die Spaltentabelle und der Abschnitt *Befund 2* sagen über die `*`-Markierung
   dasselbe.
2. Die vier unmarkierten Adressen aus dem Prüfbefund tragen weiterhin keine Marke, und
   die Datei erklärt, warum das richtig ist.
3. **Die 310 Zeilen sind unverändert.** `git diff --stat` zeigt eine Änderung, die die
   Tabelle nicht anfasst; alle vier Zählungen gehen weiter auf.

## Rückläufe

0.
