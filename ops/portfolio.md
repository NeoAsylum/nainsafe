# Portfolio

Stand 2026-09-06, geschrieben vom Portfolio-Manager. Dritter Lauf dieser Rolle, der erste
seit der Umstellung auf den Bau.

## Lage in einem Satz

Ein Vorhaben, kein Kandidat, keine Gate-Vorlage — und der Befund der Woche ist nicht der
Verbrauch, sondern die **Zusammensetzung**: Die Fabrik baut den Prüfapparat einer
Simulation, die noch nicht rechnet.

## Aktiv

**WIP 1 von 3**, null in `bau`. `0016-hedgefonds-simulation-echte-weltwirtschaft` steht
seit dem 2026-08-31 auf `erkundung`. Kein Stopp-Vorschlag: Es gibt nichts zu verdrängen.

Der Status ist formal richtig und faktisch überholt — gebaut wird seit fünf Tagen. Der
Übergang `erkundung` → `bau` ist Gate 2, und Gate 2 ist bewusst ausgelassen: Ökonom,
Vertriebsplaner, Compliance-Prüfer, Urlaubstester, Antrags-Vorbereiter und Konzept-Judge
liegen seit dem 2026-08-31 im Archiv (`konzeptlauf.py:44-47`). Ich melde es, ich ändere es
nicht — den Status setzt allein der Betreiber.

**Stand des Vorhabens:** 176 Arbeitspakete, davon 139 fertig, 19 offen, 8 gebaut, 4
blockiert. 18 grüne Tests, `cmake`, `--build` und `ctest` alle Code 0. Der Engpass des
letzten Plans vom 2026-09-04 ist weg: `werte.hpp` (damals 78 Byte) steht bei 29 kB,
`werte.cpp` existiert mit 47 kB.

## Diese Woche gestorben

**Keine Idee** — es gibt keine zu töten. Gestorben ist eine **Annahme über das Grün**.

Drei Rollen melden unabhängig dieselbe Sache. Der Bruchtester: der 200-Runden-Lauf ist
grün, „weil nichts rechnet" — `schritt_3` bis `schritt_5` sind je ein
`schreiber.vortrag(platz)`. Der Projektmanager: „Kein Paket baut einen rechnenden Rumpf für
`schritt_2`…`schritt_6`", deshalb steht 0157 auf `blockiert`, und daran hängen die drei
Maße. Der Geschäftsführer führt dieselbe Sache als *die eine Zahl*: **0 von 310** — eine
Runde `weltlauf` läuft durch und ändert keine der 310 Zustandsgrößen.

Daneben stehen 18 grüne Tests und **41 der 176 Arbeitspakete (23 %) über Belegstellen,
Riegel und Zitate** — den Apparat, mit dem die Fabrik ihre eigenen Dokumente prüft. Der
Geschäftsführer maß am 2026-09-04 einen vergleichbaren Anteil (21 von 77). *Die
Berichtigung gehört dazu:* Der Anteil **wächst nicht**, er ist seit zwei Tagen konstant bei
knapp einem Viertel. Er ist damit kein Ausreißer, sondern der größte Einzelposten der
Schlange.

## Was der Betreiber entscheiden muss — eine Sache, fünf Minuten

**Wofür die nächste Woche gebaut wird.** `ops/plan.md` ist seit dem 2026-09-04
abgearbeitet, alle fünf Vorrangkennungen stehen auf `fertig`; der Projektmanager meldet das
zum zwölften Mal. Ohne Vorrang schneidet er nach `specs/` — und `specs/` ist zu 555 kB
Prosa gewachsen (`technik.md` 298 kB, `spiel.md` 257 kB), aus der sich der Prüfapparat
selbst nachschafft.

Das ist **kein** Vorwurf an die vergangene Woche: Der Betreiber hat sie in die Mechanik
gesteckt — Sitzungsgrenze erkannt, WSL-Anker gebaut, Commit an das Paket gebunden, zuletzt
am 2026-09-05 um 22:13. Ohne diese sieben Eingriffe liefe die Fabrik heute nicht. Die
Klempnerei ist damit erledigt; was fehlt, ist eine Inhaltsangabe.

**Mein Vorschlag für die fünf Kennungen:** der rechnende Rumpf für `schritt_2` bis
`schritt_6`, in dieser Reihenfolge und sonst nichts. Er entblockt 0157, macht die drei Maße
überhaupt erst messbar und ist die einzige Arbeit, die aus „0 von 310" eine Zahl macht.
Nichts aus der Belegstellen-Familie in dieser Woche. Der Vorrang gehört dem
Geschäftsführer; ich sage nur, dass seine Liste leer ist.

## Drei Meldungen — Regeln ändert nur der Betreiber

1. **Die Archivregel aus `CLAUDE.md` ist für keine Rolle ausführbar.** Nachgemessen:
   **keine** der 31 Rollendateien unter `agents/rollen/` nennt `Edit(notizen/archiv/**)`;
   erlaubt ist je nur `Edit(notizen/<rolle>.md)`. Fünf Logbücher melden die Verweigerung
   schriftlich (Architekt, Geschäftsführer, Markt-Analyst, Projektmanager, Spielentwerfer),
   und alle fünf tun daraufhin genau das, wovor `CLAUDE.md` warnt: Sie ziehen zusammen,
   statt zu streichen. Ich bin beim Kürzen von `lehren.md` in dieselbe Wand gelaufen.
   Zweite Hälfte desselben Befunds: Wo es doch gelingt, landet die Datei **außerhalb des
   Commit-Pfadfilters** (`lauf.py:470`, `committen`) — **21 der 124 archivierten Logbücher
   sind nicht in git**, sie liegen nur im Arbeitsbaum. *Kosten der Behebung: eine Zeile je
   Rollendatei.* Der Architekt schlägt genau das vor. Warum es sechs Rollen trotzdem
   gelungen ist, kann ich nicht erklären — `.claude/settings.local.json` ist für mich nicht
   lesbar.

2. **Wiedervorlage 2026-09-13, sonst verfällt sie.** Das Wochenkontingent von rund
   12.700 $ Gegenwert wurde gemessen, solange der Bonus lief. Endet er, bremst
   `WOCHENGRENZE_USD = 12000` gar nicht mehr. Die alte Nacheichungsnotiz zu diesem Datum
   wurde am 2026-09-05 aufgelöst, ohne dass eine neue an ihre Stelle trat. Von innen ist
   der Kontostand nicht lesbar; es genügt, an dem Tag einmal die Anzeige vorzulesen.

3. **Die eine Geschäftszahl des Vorhabens sieht sich niemand mehr an.** 170 nötige Käufer
   im Monat gegen 121 erreichbare — Faktor 1,4. Die Lehre vom 2026-08-31 wies das Schließen
   dieser Lücke dem Ökonomen und dem Vertriebsplaner zu und Gate 2 als Kontrollpunkt; alle
   drei wurden am selben Tag archiviert. Ich habe die Lehre entsprechend berichtigt. Zur
   Fairness dieselbe Größe von der anderen Seite: 121 ist die Untergrenze unter den
   härtesten Annahmen aus G7, bei einem Prozent derselben Basis wären es 1.208. Es ist eine
   offene Arbeit, keine Absage — sie hat nur seit sechs Tagen keinen Adressaten.

## Was ich an den Lehren geändert habe

`notizen/lehren.md` von 42.578 auf 25.645 Zeichen. Nichts war älter als 60 Tage; gestrichen
wurde nach einem anderen Maß. Zwei Drittel der Datei waren an Rollen gerichtet, die seit
dem 2026-08-31 nicht mehr laufen — und wurden trotzdem von jeder Baurolle in jedem der
1.531 Läufe dieser Woche mitgelesen. Der Volltext steht in
`git show 9103e36:notizen/lehren.md`, der tragende Satz jeder gestrichenen Lehre in elf
Zeilen unter „Aus der Suchphase". Gelöscht ist nichts.

Neu eingetragen, weil je mehrfach unabhängig belegt: **„Eine Prüfung, deren Gegenstand sich
nicht bewegen kann, ist grün und wertlos"** (drei Quellen) und **„Nie `cd` — es nimmt das
Arbeitsverzeichnis mit, und danach stirbt jeder `Edit`"** (drei Logbücher, vier verlorene
`Edit` an einem Tag). Berichtigt: der Kern ist **C++**, nicht Rust (ADR 0011 ersetzt 0010,
entschieden durch vier Agenten in vier Sprachen mit identischer Prüfsumme — die Fabrik hat
den Vergleich gebaut, statt ihn zu führen), und die 70 % Fehlläufe der Woche sind zu
97 % die drei Stunden vom 2026-09-05; die normale Rate sind 28 auf sechs Tage.

## Keine Gate-Vorlage, und keine erzwungen

Es gibt keinen Kandidaten — es gibt keine Ideen mehr außer 0016, und die steht jenseits von
Gate 1. Eine Vorlage wäre diese Woche nicht schwach, sondern frei erfunden.
