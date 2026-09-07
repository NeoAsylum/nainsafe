# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-07. Abgedeckt: seit 2026-09-06 08:30.

## Wo das Vorhaben steht

**Der Engpass des letzten Plans ist aufgelöst, und der nächste stand schon dahinter.** Der
Projektmanager hat 0197 geschnitten — das erste Paket, das einen der sechs Rundenschritte
rechnen lässt — und die dreizehngliedrige `technik.md`-Schlange umgehängt (0165 →
0172-weltpreis → 0148 → 0177 → …), wie der Vorrang es verlangte. **Der Baulauf hat nichts
gebaut, und das war richtig:** dem Kern fehlt die Rechenvorschrift und der Draht zu ihr.
186 Pakete: 147 fertig, 18 offen, 8 Vorschläge, 7 gebaut, 3 blockiert; Spielraum 8.722 von
12.000 $ (Stand 2026-09-06 05:00), Geld bindet nicht.

## Der Engpass

**Die sechs Schritte haben jetzt einen Auftrag, aber weder eine Vorschrift noch einen Draht
— und beide Lücken liegen in `specs/`, wo kein Bauagent sie schliessen darf.**

Der Kernbauer von 0197 hat `schritt_5_reaktion` nicht angefasst und den Grund benannt: die
Zustimmungsregel liest die *Änderung des Realeinkommens*, und `Realeinkommen` steht in
`specs/` achtmal, jedes Mal als Prosa oder als Pfeil in einem Kettenbild. T48 entscheidet,
wem das gehört: „Ein Name in einer Formel … **ist ein Befund und keine Bauentscheidung**."
Vorschlag **0198** (Spielentwerfer, `spiel.md`).

Der Kernprüfer hat unabhängig die zweite Lücke gemessen: `schritt(zustand, aktionen, modus)`
hat **kein Parameterargument**, `werte::Konstanten` führt `zustimmung_elastizitaet` nicht,
und `schritt.hpp` sagt es wörtlich — „`parameter.toml` wird hier nicht gelesen, der Rahmen
braucht keinen Parameter." Damit ist jede Regel mit einem Koeffizienten unbaubar, **auch
die Politikinstrumente aus Schritt 3**. Vorschlag **0208** (Architekt, `technik.md`).

**Beide stehen auf `vorschlag`, keines auf `offen`.** Die zwei Rollen, die sie schreiben
müssen, sind die am wenigsten benutzten der Fabrik: Spielentwerfer 9 Läufe, Architekt 137
zu 0,97 $ — zusammen unter 1,5 % des Verbrauchs.

## Was quer liegt

- **Ein stehendes Rot.** `belegstellen_riegel` fällt in beiden Bäumen aus (Code 8), der
  Baulauf meldet `ergebnis: fehler` — 19 von 20 Tests grün, dieser rot. Grund: der
  Übersetzungslauf benennt Überschriften in `spiel.md` und `daten.md` um („Die Schleife",
  „Die Aktionen", „Der Zustand", „Der Fonds"), und zehn Abschnittszitate in `aktion.hpp`,
  `schritt.hpp`, `zustand.hpp`, `schritt.cpp`, `parameter.toml`, `adressen.md`,
  `reihen.toml` und im Riegel selbst suchen weiter den deutschen Wortlaut. Der Riegel hat
  recht; genau dafür gibt es ihn. Vorschlag 0200 zieht die zehn nach — der wiederkehrende
  Teil ist eine Regelfrage, unten.
- **`zurueck` ist bei 0197 das falsche Urteil.** Der Prüfer schreibt es selbst dazu: es
  gehöre auf `blockiert` hinter 0198. `zurueck` plant den Kernbauer gegen dieselbe Wand
  neu ein, und 0157 (`offen`, `haengt_an: [0197]`) läuft direkt hinterher in dasselbe
  Ergebnis. Zwei Läufe, deren Ausgabe heute schon gedruckt ist.
- **Ein Vorschlag, den kein Agent bauen kann.** 0208-baulauf-faehrt-beide-profile trägt
  `dateien: [agents/baulauf.py]`; `agents/lauf.py:NIE` sperrt `Edit(/agents/**)` für jede
  Rolle. Auf `offen` gesetzt ist es ein verlorener Lauf — zehnter Fall derselben Klasse.
- **Drei Pakete mit bestandenem Urteil stehen weiter auf `gebaut`** (0186, 0188, 0193, alle
  `urteil: geprueft` vom 2026-09-07). `fertig` steht seit gestern unverändert bei 147; ein
  Lauf des Projektmanagers behebt es.
- Unverändert fortgeschrieben, nicht neu gefragt: `daten/roh/` gibt es nicht, `reihen.toml`
  sagt weiter „**Sie enthaelt keine Datenzeile.**" Drei Pakete tragen die Nummer 0208.

## Was der Betreiber entscheiden muss

**Ob der Übersetzungslauf weiter Überschriften umbenennen darf, ohne dass die zitierenden
Dateien mitgezogen werden.** Nur du kannst das entscheiden: `CLAUDE.md` und
`agents/rollen/uebersetzer.md` sind für jeden Agenten unschreibbar. Keine Geldfrage.

`CLAUDE.md` sagt heute über `spiel.md` und `technik.md`: „**They stay German until someone
translates them whole, which is not planned.**" Der Lauf läuft (`ops/uebersetzt.txt`, 13
Abschnitte fertig gemeldet). Der Satz stimmt nicht mehr — und er steht in der Datei, die
jeder Agent in jedem Lauf liest.

- **A — nur nachziehen.** 0200 räumt die zehn Zitate ab. Die nächste übersetzte
  Überschrift bricht sie wieder; der Riegel ist morgen erneut rot.
- **B — ein Satz in `agents/rollen/uebersetzer.md`:** Eine Überschrift wird erst
  umbenannt, wenn im selben Lauf jedes Zitat darauf nachgezogen ist; sonst bleibt sie
  stehen. Dazu die Berichtigung des Satzes in `CLAUDE.md`.
- **C — `spiel.md` und `technik.md` vom Übersetzungslauf aussetzen**, bis die Runde
  rechnet. Das sind die zwei Dokumente, aus denen gebaut wird.

**Empfehlung B, und 0200 unabhängig davon sofort.** Ein Testergebnis, das jeden Tag rot
ist, erzieht die Fabrik dazu, das eine Signal zu übersehen, das sie hat. `lehren.md` hat
die eine Hälfte schon („Eine Prüfung, deren Gegenstand sich nicht bewegen *kann*, ist grün
und wertlos") — dies ist die teurere andere.

## Vorrang

1. **0208-schritt-braucht-einen-parametereingang** — der Draht. Ohne ihn ist keiner der
   sechs Schritte baubar, gleich wie 0198 ausgeht. **An den Kopf der `technik.md`-Kette,
   vor 0165.**
2. **0198-realeinkommen-als-rechenvorschrift** — die Vorschrift, die 0197 fehlte. Läuft
   neben 1 (andere Datei, andere Rolle); kollidiert auf `spiel.md` mit dem
   Übersetzungslauf — das Serialisieren ist deins.
3. **0200-zitate-auf-uebersetzte-ueberschriften-nachziehen** — nimmt das stehende Rot weg
   und entsperrt die Nachmessung von 0147.
4. **0165** — unverändert Kopf der umgehängten Kette und die Sperre vor 0172-weltpreis.
5. **0172-weltpreis** — der Zollfaktor, Schritt 4; das einzige `technik.md`-Paket, das die
   Wirtschaft bewegt. Jetzt Platz zwei der Kette statt Platz dreizehn.

**Nicht einplanen:** 0197 gehört auf `blockiert` hinter 0198 und 0208, nicht auf `zurueck`;
0157 bleibt dahinter. 0208-baulauf braucht einen anderen Schnitt oder den Betreiber — kein
Agent darf `agents/` schreiben.

## Die eine Zahl

**1 von 310** — unverändert gegenüber dem letzten Plan, aber zum ersten Mal **gedruckt
statt hergeleitet**. Mitschnitt von `schritt_probe`, 2026-09-07 um 10:30: „Vorrunde 0 ->
Runde 1: … **1 von 310 Groessen geaendert (partie.runde)**", und beide Startzustände
drucken dieselbe 1. Der Apparat ist weiter gewachsen — 20 Tests im Werkstattbaum, 12 im
Kernbaum, acht Manifeste, 407 geprüfte Schaltereinträge — und die Runde rechnet weiterhin
nichts. Neu ist, dass die beiden Sätze feststehen, die sie bewegen: die Regel aus 0198 und
der Weg aus 0208. Die Ursache ist damit zum ersten Mal nicht mehr organisatorisch.
