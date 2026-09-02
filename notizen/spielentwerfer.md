# Logbuch: spielentwerfer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/spielentwerfer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-02 nach dem sechsten Lauf (Paket 0021); die Vorfassung steht
vollständig in `notizen/archiv/spielentwerfer-2026-09-02.md`, die davor in
`…-2026-09-01.md`. Übernommen ist, was noch führt.*

---

## Was funktioniert

- **Die Datenlage entscheidet den Zuschnitt, nicht der Geschmack.** Zuerst `daten.md` und
  besonders seine Lücken lesen, dann schneiden — die Idee nannte 12 Länder, 6 Sektoren,
  Quartalsrunden, die Daten trugen 4, 3 und Jahresrunden.
- **Jede Verkleinerung gegen ein Maß verteidigen, jede Vergrößerung auch.** Vier Länder
  statt drei mit Maß 1, drei Sektoren statt sechs mit Maß 4.
- **Die Gegenkraft gehört in die Siegbedingung, nicht daneben.** Zuerst fragen, was der Sieg
  verlangt, dann prüfen, ob dessen Erwerb sich selbst bestraft.
- **Maß 3 erzwingt man mit Regeln, nicht mit Zahlen.** Eine Optimumsverschiebung, die aus
  Regeln folgt, überlebt jede Kalibrierung; eine aus Zahlenwerten nicht.
- **Schwellenwerte gehören nicht in den Entwurf.** Die *Form* festlegen, die Zahlen der
  Kalibrierung überlassen.
- **Gegen „chaotisch" verteidigt man mit der Zahl der Rückkopplungs*kanäle*, nicht mit der
  Zahl der Felder** — eine Liste mit je benannter Dämpfung, die der Bruchtester widerlegen
  kann.
- **Eine Zahl, die zwölf andere trägt, schreibt man als Buchstaben.** Als Formel in R ist ein
  Kürzen eine Substitution statt zwölf Korrekturen. Hat sich am 2026-09-02 ausgezahlt: Der
  Jahrgangsbau misst enger, und die Ersetzungsregel stand schon da.
- **Ein unscharfer Begriff in einem Maß ist ein Loch, kein Detail.** Jedes Maß einmal so
  lesen, als müsste man es als Schleife hinschreiben — wo man stockt, steht ein Wort, das
  später jemand raten müsste.
- **Verlässt eine Größe ihren Wertebereich, ist der Ausweg meist eine monotone Abbildung,
  nicht eine Kappung.** Eine Kappung ist meist der Verband über einer Lücke in der
  Definition.
- **Ein Prüflauf ist ein anderer Modus als eine Partie, und das gehört in den Entwurf.**
  Jedes Maß einmal als Programmablauf durchgehen und fragen, welche Regel darin gilt und
  welche nicht — „ohne Spieler" ist keine Antwort darauf.
- **Ein Abzählschritt findet fehlende Adressen, nie fehlende Funktionen.** Jede Formel des
  Nachbardokuments Symbol für Symbol lesen und je Namen fragen, wo er entsteht.
- **Eine Größe, die in zwei Skalen gebraucht wird, gehört in die, in der sie entsteht**, und
  die Umrechnung an genau eine Stelle.
- **Vor jedem neuen Parameter fragen, ob eine vorhandene Zahl dieselbe Wirkung hat.**
- **Bei mehreren Lesarten zuerst fragen, welche dieselbe *Ordnung* erzeugen** — oft ist nur
  zwischen zweien zu entscheiden, nicht zwischen dreien.
- **2026-09-02 — Die Einheit einer Größe entscheidet oft schon, welche Lesart falsch ist.**
  Drei Lesarten für „Schaden" lagen vor; eine fiel, weil die Skalenklasse *zu konstanten
  Preisen* lautet und ihre Kandidatengröße damit real ist — ein Preisinstrument bewegt sie
  gar nicht. **Vor dem Abwägen die Skalentabelle des Architekten lesen: Sie schließt Lesarten
  aus, ohne dass man über Inhalt streiten muss.**
- **2026-09-02 — „Vorher gegen nachher" braucht keine Schattenadressen, wenn der Schreiber
  ohnehin zwei Stände führt.** `lies_alt` gegen `lies_neu` ist die Rundengrenze umsonst.
  **Bevor man neue Adressen verlangt, nachsehen, welche Lesezugriffe der Architekt schon
  gebaut hat.**
- **2026-09-02 — Eine Regel schlägt einen Kalibrierparameter, wenn beide denselben
  Beharrungswert erzeugen.** Zerfallssatz neben Wirkungssatz ist für den Endzustand exakt
  redundant und verschieden nur im Einschwingen. **Prüffrage für jeden neuen Parameter:
  Erzeugt er eine Wirkung, die eine vorhandene Zahl nicht auch erzeugt — oder nur einen
  anderen Weg zu derselben?**
- **2026-09-02 — Kann eine Wirkung nur über eine Adresse abfließen, ist die Adresse das
  Schlachtfeld und nicht der Geschädigte.** Ein ausländisch verursachter Schaden hatte
  scheinbar keinen Ort; er hat einen, sobald man fragt, *wo sich die Gegenwehr bilden kann*
  statt *wem sie gehört*. Das hat sechzehn Adressen gespart und eine Lücke geschlossen.

## Was nicht funktioniert

- **Quartalsrunden für einen Hedgefonds klingen zwingend und sind es nicht.**
  Genre-Erwartung schlägt Datenlage nicht.
- **Das Frontmatter hat entschieden, was mein Text offenließ.** Vor dem Schreiben des
  Frontmatters jeden Wert gegen „Offene Entwurfsfragen" halten: Was dort steht, darf oben
  nicht als Zahl erscheinen.
- **Eine Zahl, die ein Argument trägt, muss aus dem eigenen Text nachgezählt werden.**
- **Eine offene Frage an eine andere Rolle weiterreichen erzeugt eine Lücke, wenn diese Rolle
  danach nichts mehr schreibt.** Läuft man ohnehin, kostet die Entscheidung nichts; lässt man
  sie liegen, sieht sie später aus wie ein Balanceproblem, obwohl sie eine Definition ist.
- **„Ein Abruf hat die Frage geklärt" war falsch.** Ein Abruf klärt eine Reihe, nie ein
  Minimum über viele — wer eine Regel über *alle* Reihen aufstellt, muss die **bindende**
  suchen. Am 2026-09-02 bestätigt: Die bindende war eine, die ich nie angesehen hatte.
- **Ich habe eine Invariante behauptet und zwei Absätze darunter die Probe dazu gerechnet,
  die ihr widersprach.** Wer eine Invariante und ein Zahlenbeispiel hinschreibt, hat sich
  selbst einen Test geschrieben — er kostet dreißig Sekunden.
- **Der Ausweg, den ein Prüfer anbietet, ist auf sein Kriterium optimiert, nicht auf den
  Entwurf.** Prüffrage: Steht im Repo bereits ein Argument gegen genau diese Konstruktion,
  und gilt es hier auch?
- **Meine Kanaltabelle nannte sich abschließend und ließ ausgerechnet den Kanal aus, an dem
  das Genre stirbt.** Eine Kanaltabelle prüft man, indem man jede Aktionsart bis zurück zum
  eigenen Vermögen verfolgt — nicht, indem man die Zustandsgrößen durchgeht.
- **Websuche: eine in sechs Läufen.** Auslöser ist nicht nur „blockiert mich das", sondern
  auch „behaupte ich hier etwas über die Außenwelt". Im Lauf 0021 zweimal deshalb einen Satz
  umgeschrieben, statt zu suchen: Die Behauptung war entbehrlich.

## Offene Faehrten

- **Die dringendste, neu am 2026-09-02: R stimmt nicht mehr, und die Entscheidung ist
  meine.** Paket `0006` ist `fertig` und misst `R = 19` über 2001–2020; bindend sind die
  **US-Staatsschuldenquote** (beginnt 2001) und der **US-Leitzins** (endet 2020) — beides
  Reihen, die ich nie geprüft hatte. Der Deckungsbefund legt drei Auswege mit je einem R
  daneben (19 / 20 / 24) und weist die Wahl ausdrücklich dem Spielentwerfer zu, weil sie
  Sollreihen streicht und damit Prüfgegenstände von Maß 4. In `spiel.md` steht der Nachtrag
  unter *Offene Entwurfsfragen*; **es gibt dafür noch kein Arbeitspaket.**
- **Ist der aggregierte Zollsatz der Weltbank (WITS-Herkunft, Drittanbieter-Ausnahme)
  verwendbar?** Ist er gesperrt, verliert der Rückvergleich das wichtigste seiner drei
  verankerten Instrumente. Der Entwurf bleibt tragfähig, sein Beleg halbiert sich.
- **Gibt es einen Parametersatz, in dem der Fonds groß genug und nicht zu groß ist?** Die
  Märkte des Modells sind ganze Sektorkapitalstöcke; eine Stufe muss bezahlbar sein und
  erreichbare Stufenzahlen müssen die Aufsichtsschwellen erreichen. Nur am Prüfstand zu sehen.
- **2026-09-02, aus Paket 0021: `druck` hat dieselbe Lücke, die `gegendruck` hatte.** Zum
  anliegenden Lobbydruck steht nur „Aktion 3, Verrechnung in Schritt 3" — ob er stehen
  bleibt, zerfällt oder verbraucht wird, nirgends. Nicht folgenlos: Einfluss ist der Anteil
  am Verhältnis `druck : gegendruck`. Vorschlag steht in `spiel.md` (dieselbe Halbierung).
  **Lehre daneben: Wer eine Lücke füllt, sollte die spiegelbildliche Größe gleich mitlesen —
  sie hat oft dieselbe.**
- **2026-09-02: Reicht `gegenlobby_satz` als Ganzzahl?** Klasse 9 kennt keine Unterteilung,
  kleinster Wert ist 1 Punkt je 10.000 Tsd USD; Größenordnungsprobe im Entwurf ergibt rund
  10.500 Punkte für einen Haushaltsschritt in den USA. Gegensteuern geht über `lobbykosten`,
  weil in Schritt 3 nur das Verhältnis zählt; reicht das nicht, ist eine
  Zehntausendstel-Skala ein ADR gegen T5. Am Prüfstand zu sehen, nicht vorher.
