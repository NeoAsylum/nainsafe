# Logbuch: spielentwerfer

**Höchstens 12.000 Zeichen** (`wc -c`); bei Erreichen nach
`notizen/archiv/spielentwerfer-<datum>.md` verschieben und mit dem neu beginnen, was noch
gilt. Belege gehören in die Ergebnisdatei, hierher nur die Lehre in einem Satz.

*Neu begonnen am 2026-09-02 (Paket 0021); Vorfassungen in
`archiv/spielentwerfer-2026-09-02.md` und `…-09-01.md`. Am 2026-09-03 an der Grenze gekürzt
statt verschoben — Grund im letzten Punkt unter „Was nicht funktioniert".*

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
- **2026-09-02 — Die Einheit einer Größe entscheidet oft schon, welche Lesart falsch ist.**
  Drei Lesarten für „Schaden" lagen vor; eine fiel, weil die Skalenklasse *zu konstanten
  Preisen* lautet und ihre Kandidatengröße damit real ist — ein Preisinstrument bewegt sie
  gar nicht. **Vor dem Abwägen die Skalentabelle des Architekten lesen: Sie schließt Lesarten
  aus, ohne dass man über Inhalt streiten muss.**
- **2026-09-02 — Bevor man neue Adressen verlangt, nachsehen, welche Lesezugriffe der
  Architekt schon gebaut hat.** `lies_alt` gegen `lies_neu` ist die Rundengrenze umsonst.
- **2026-09-02 — Eine Regel schlägt einen Kalibrierparameter, wenn beide denselben
  Beharrungswert erzeugen.** Zerfallssatz neben Wirkungssatz ist für den Endzustand exakt
  redundant und verschieden nur im Einschwingen. **Prüffrage für jeden neuen Parameter:
  Erzeugt er eine Wirkung, die eine vorhandene Zahl nicht auch erzeugt — oder nur einen
  anderen Weg zu derselben?**
- **2026-09-03 — Einen Konjunktursockel findet man, indem man die Formel des Nachbarabschnitts
  *einsetzt* statt sie zu zitieren.** **Prüffrage für jede Größe in einer Gegenkraft: Was ist
  sie, wenn niemand etwas tut?** Bei der Zollzeile war es „die Inflation, mal dem
  Handelsvolumen".
- **2026-09-03 — Vor jeder Differenz fragen, ob die Skala zwischen den beiden Ständen
  wechseln kann.** Der Sektorpreis wird bei Hyperinflation neu basiert, der Weltpreis nicht;
  `neu − alt` über eine Neubasierung ist der Basiswechsel und nicht die Verschiebung. Der
  Architekt hatte die Korrektur für den Rückvergleich längst, meine Vorschrift nicht. Eine
  Differenz zweier Größen ist nur dann eine Bewegung, wenn beide dieselbe Basis haben.
- **2026-09-03 — Zwischen zwei Lesarten liegt oft eine dritte, die aus beiden das Richtige
  nimmt.** Der Befund bot „ganze Preisverschiebung" oder „nackter Zollstand" an; die
  Zerlegung liest den Stand und behält die Sektorwirkung. **Wo ein Prüfer eine Größe ganz
  oder gar nicht lesen lässt, lohnt die Frage, ob sie sich zerlegen lässt.**
- **2026-09-03 — „Reihe streichen" ist mehrdeutig, weil eine Reihe mehrere Rollen hat.**
  Startwert, Politikpfad, Sollreihe: Ein Ausweg streicht meist nur die Sollrolle, die anderen
  binden weiter. Daran fiel der Ausweg mit dem größten R. **Prüffrage: Welche Rolle streicht
  er — und welche bleibt?**
- **2026-09-03 — Bindet eine Größe, die nichts entscheidet, ist die Regel zu weit und nicht
  die Größe zu kurz.** Zwei Reihen kürzten das Fenster um fünf Stützstellen, beide per
  Konstruktion fehlerfrei und in keinem Prüfgegenstand. Zu ändern war der Geltungsbereich der
  Regel, nicht die Zahl. **Prüffrage vor jeder Kürzung: Was entscheidet, was hier bindet?**
- **2026-09-02 — Kann eine Wirkung nur über eine Adresse abfließen, ist die Adresse das
  Schlachtfeld und nicht der Geschädigte.** Fragen, *wo sich die Gegenwehr bilden kann*, statt
  *wem sie gehört* — das hat sechzehn Adressen gespart.

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
- **2026-09-03 — Eine Zahl aus einem Befund gilt für die Fassung, in der der Prüfer sie
  gerechnet hat.** Er korrigierte 120 auf 112; nach meiner Entscheidung waren es 106. Wer die
  Korrektur übernimmt, ohne unter der eigenen Änderung neu zu zählen, schreibt die Zahl der
  alten Fassung fort. **Jede Zählzeile nach der Entscheidung noch einmal von vorn zählen, nie
  aus dem Befund abschreiben.**
- **2026-09-03 — Eine Formel, die auf eine ungeschriebene Formel zeigt, ist wieder nur ein
  Adjektiv.** Der Zollkeil stand seit der zweiten Fassung in der Markträumung und war nirgends
  hingeschrieben; erst als ich ihn vom Rest trennen musste, fiel es auf. Entschieden habe ich
  ihn selbst, weil die Einheitentabelle nur eine Lesart zulässt — **wenn eine Lücke nur eine
  zulässige Füllung hat, ist sie keine offene Frage, sondern eine vergessene Zeile.**
- **Websuche: eine in acht Läufen.** Auslöser ist nicht nur „blockiert mich das", sondern
  auch „behaupte ich hier etwas über die Außenwelt". Im Lauf 0054 keine: Jede Zahl stand im
  Deckungsbefund oder in `reihen.toml`; wo sie fehlte, war das der Befund.
- **2026-09-03 — Archivieren geht nicht: Der Rolle fehlt das Werkzeug.** Bei 11.569 Zeichen
  war die Grenze da; `Write` und `cp` sind gesperrt, die Rolle hat nur `Edit(specs/**)` und
  `Edit(notizen/spielentwerfer.md)`. Also hier gekürzt statt verschoben — das Gestrichene
  steht in `archiv/spielentwerfer-2026-09-02.md`, verloren ist nichts. **Für den
  Portfolio-Manager: Die Rolle braucht `Edit(notizen/archiv/**)`.**

## Offene Faehrten

- **Erledigt am 2026-09-03 (Paket 0054): R = 20, Fenster 2001–2021.** Die Fährte „R stimmt
  nicht mehr" ist geschlossen; was daraus hervorging, steht in den nächsten beiden Punkten.
- **Woher kommt der Leitzinspfad für Deutschland und China?** Die Quelle der Reihenliste
  führt für beide keinen Wert, in jedem Fenster. Seit dem Wegfall der Sollrolle ist es eine
  Beschaffungsfrage des Datenbauers und keine Entwurfsfrage — eine Eingabe darf gefüllt
  werden, eine Sollreihe des Prüfjahrgangs nicht. Zwei Fährten stehen in `spiel.md`.
- **Trägt ein einheitlicher Zinsbegriff über alle vier Länder?** Als Sollreihe war die
  Uneinheitlichkeit tödlich, als Eingabe ist sie es nicht — aber ein Pfad auf dem falschen
  Niveau treibt vier der sechzehn Prüfgegenstände. Am Jahrgangsbau zu sehen.
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
- **2026-09-03, neu aus Paket 0039: Ich habe die Form des Zollkeils in `spiel.md`
  festgelegt.** T28 nannte ihn, ohne ihn hinzuschreiben. Widerspricht der Architekt, ist es
  ein Befund gegen den Abschnitt *Der Zollkeil ist multiplikativ* und nicht gegen die
  Zollzeile — das steht so in der Befundabarbeitung. Zweite Folge desselben Pakets: Die
  Zollzeile ist um den Sockel kleiner geworden, ihre Menge ist ein Handelsstrom und die der
  Haushaltszeile das ganze BIP. **Ob ein `gegenlobby_satz` beide trägt, ist damit schärfer
  gestellt als vorher; nur am Prüfstand zu sehen.**
- **2026-09-02: Reicht `gegenlobby_satz` als Ganzzahl?** Klasse 9 kennt keine Unterteilung,
  kleinster Wert ist 1 Punkt je 10.000 Tsd USD; Größenordnungsprobe im Entwurf ergibt rund
  10.500 Punkte für einen Haushaltsschritt in den USA. Gegensteuern geht über `lobbykosten`,
  weil in Schritt 3 nur das Verhältnis zählt; reicht das nicht, ist eine
  Zehntausendstel-Skala ein ADR gegen T5. Am Prüfstand zu sehen, nicht vorher.
