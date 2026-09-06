# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-06 03:07. Fassung 33, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**170 Dateien, 169 mit Frontmatter: 22 offen, 8 gebaut, 130 fertig, 1 abgelehnt,
4 blockiert.** Dazu vier außerhalb der Zählung (archiviert, zweimal umgezogen,
zurückgezogen) und eine Verweisdatei ohne Frontmatter, die absichtlich in keiner
Statuszählung mitläuft — daher 170 gegen 169.

**Der Befund dieses Laufs ist eine Korrektur an meiner eigenen Berichterstattung, und sie
geht zugunsten der Fabrik.** Der Trockenlauf zeigt 2 von 8 Bauplätzen belegt. Das habe ich
in früheren Fassungen als Auslastung der ganzen Fabrik gelesen. Das war falsch.

## Bau, Review und Prüfung haben je ein eigenes Budget — und Review ist heute voll

`agents/baulauf.py` schneidet in Zeile 362, 375 und 381 **drei** Listen unabhängig
voneinander auf `gleichzeitig` zu. Die drei Stufen teilen sich keinen Topf. Heute laufen
deshalb nicht 2 Agenten, sondern **elf**: 2 im Bau, **8 im Review**, 1 in der Prüfstufe.

**Die Reviewstufe steht exakt am Anschlag: 8 Pakete auf `gebaut`, 8 Plätze.** Sie ist der
Engpass dieses Laufs, nicht mein Zuschnitt. Mehr offene Baupakete hätten heute nichts
gebracht — sie hätten in eine Stufe geliefert, die schon voll ist.

## Der Statusnachzug war leer, und diesmal aus dem harmlosesten der drei Gründe

Zu keinem der acht `gebaut`-Pakete gibt es einen Prüfbefund. **Die Prüfer sind nicht
säumig, sie laufen gerade** — alle acht sitzen in genau den acht Reviewplätzen oben. Der
Nachzug dieses Laufs ist damit nicht verschleppt, sondern noch nicht fällig; die Ernte
fällt im nächsten Lauf an.

Das ist ausdrücklich **nicht** der Fall aus Fassung 32, in der die Prüfer den Status selbst
auf `fertig` gesetzt hatten. Diesmal hat niemand etwas übersprungen.

## Kein Schnitt öffnet heute einen Bauplatz — nachgemessen, nicht vermutet

Die 22 offenen Pakete verteilen sich auf **acht Dateibahnen**, und zwei Pakete auf einer
Datei laufen nie gleichzeitig. Je Bahn steht genau ein Paket vorn:

| Bahn | Kopf | Zustand |
|---|---|---|
| `daten/reihen.toml` | 0142 | **läuft** |
| `parameter.toml` | 0175 | **läuft** |
| `befunde/beschraenktheit/` | 0178 | **läuft** (Prüfstufe) |
| `specs/…/technik.md` | 0154 | wartet auf 0141 |
| `specs/…/spiel.md` | 0118 | wartet auf 0141 |
| `werkzeuge/belegstellen/…cpp` | 0147 | wartet auf 0130 |
| `kern/include/kern/verlauf.hpp` | 0172-verlaufskopf | wartet auf 0091 |
| `werkzeuge/zahlwort/` | 0180 | wartet auf 0155 |

**Alle fünf wartenden warten auf ein Paket, das in diesem Moment im Review sitzt.** Ich
habe geprüft, ob die Abhängigkeiten echt sind oder nur behauptet — bei **vier von fünf**
liegt der Vorgänger auf **derselben Datei** (0141 und 0154 auf `technik.md`, 0130 und 0147
auf demselben Riegel, 0091 und 0172 auf `verlauf.hpp`). Dort hielte die Dateisperre die
Bahn auch dann, wenn ich das `haengt_an` striche. Nur 0180 hängt dateiübergreifend an
0155, und dort ist die Abhängigkeit inhaltlich zwingend.

**Ergebnis: Es gibt heute keine Umstellung, die einen sechsten Bauplatz öffnet.** Das ist
eine Eigenschaft des Vorhabens — dreizehn Pakete auf einer Entwurfsdatei —, keine
Entscheidung von mir.

## Was ich getan habe

- **0180 angenommen** (`vorschlag` → `offen`), ein Zahlwortriegel für `werte.hpp` vom
  Kernbauer. Die fünf Prüfungen bestanden: Rolle `testentwickler` bildet auf `test-pruefer`
  ab, also bekommt es einen Befund; kein anderes Paket nennt heute die Wurzel-`CMakeLists.txt`;
  die drei Bedingungen sind am Quelltext messbar. Es eröffnet eine achte Dateibahn.
- **0181 angelegt**, den Nachzug des Vorspanns von `technik.md`. Das ist kein erfundenes
  Paket: Der Architekt hat es in `technik.md` selbst beauftragt und die Reihenfolge
  mitgeliefert. Nachgemessen und noch offen — die Datei nennt in Zeile 45 den Bereich
  T1 bis T53, vergeben ist bis T61.

## Was der Geschäftsführer entscheiden muss

**Erstens: `technik.md` zerlegen. Zum dreizehnten Mal, und der Preis ist jetzt bezifferbar.**
Dreizehn der 22 offenen Pakete stehen auf dieser einen Datei, in einer Kette von zehn
Gliedern: 0154 → 0158 → 0148 → 0149 → 0177 → 0064 → 0068 → 0074 → 0084 → 0181. Bei einem
Glied je Lauf läuft das letzte in keiner Woche durch, die absehbar ist. Ich habe 0181
sehenden Auges ans Ende gehängt, weil ein vergessener Auftrag teurer ist als ein wartendes
Paket — aber das ist Schadensbegrenzung, keine Lösung. **Der Schnitt liegt in der Datei,
nicht in meinen Paketen**, und über den Entwurf entscheide ich nicht.

**Zweitens: `ops/plan.md` ist abgearbeitet.** Alle fünf Vorrangkennungen (0026, 0002, 0071,
0027, 0010) stehen auf `fertig`; der Plan trägt den Stand 2026-09-04. **Elfte Meldung.** Ich
schneide seither nach `specs/`, wie mein Logbuch es für einen leeren Vorrang vorsieht, und
melde die Rücknahme hiermit erneut ausdrücklich.

**Drittens, zur Kenntnis, nicht zur Entscheidung:** Die vier blockierten Pakete bleiben
blockiert, und zwar zu Recht. 0003 widerspricht T5 und braucht einen ADR des Betreibers;
0157 hat kein Paket, an das es hängen könnte, weil kein Paket einen rechnenden Rumpf für
`schritt_2` bis `schritt_6` baut; 0127 und 0176 liegen mit `agents/baulauf.py` und
`.gitignore` außerhalb jeder Schreibgrenze der Baurollen.
