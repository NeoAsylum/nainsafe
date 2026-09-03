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
- **Maß 3 erzwingt man mit Regeln, nicht mit Zahlen.** Eine Optimumsverschiebung aus Regeln
  überlebt jede Kalibrierung; eine aus Zahlenwerten nicht.
- **Schwellenwerte gehören nicht in den Entwurf.** Die *Form* festlegen, die Zahlen der
  Kalibrierung überlassen.
- **Gegen „chaotisch" verteidigt man mit der Zahl der Rückkopplungs*kanäle*, nicht der
  Felder** — eine Liste mit je benannter Dämpfung, die der Bruchtester widerlegen kann.
- **Eine Zahl, die zwölf andere trägt, schreibt man als Buchstaben.** Als Formel in R ist ein
  Kürzen eine Substitution statt zwölf Korrekturen. Hat sich am 2026-09-02 ausgezahlt: Der
  Jahrgangsbau misst enger, und die Ersetzungsregel stand schon da.
- **Ein unscharfer Begriff in einem Maß ist ein Loch, kein Detail.** Jedes Maß einmal so
  lesen, als müsste man es als Schleife hinschreiben — wo man stockt, steht ein Wort, das
  später jemand raten müsste.
- **Verlässt eine Größe ihren Wertebereich, ist der Ausweg meist eine monotone Abbildung
  statt einer Kappung.** Eine Kappung ist der Verband über einer Lücke in der Definition.
- **Ein Prüflauf ist ein anderer Modus als eine Partie, und das gehört in den Entwurf.**
  Jedes Maß als Programmablauf durchgehen und fragen, welche Regel darin gilt — „ohne
  Spieler" ist keine Antwort darauf.
- **Ein Abzählschritt findet fehlende Adressen, nie fehlende Funktionen.** Jede Formel des
  Nachbardokuments Symbol für Symbol lesen und je Namen fragen, wo er entsteht.
- **Eine Größe, die in zwei Skalen gebraucht wird, gehört in die, in der sie entsteht**, und
  die Umrechnung an genau eine Stelle.
- **2026-09-02 — Die Einheit einer Größe entscheidet oft schon, welche Lesart falsch ist.**
  Von drei Lesarten für „Schaden" fiel eine, weil die Skalenklasse *zu konstanten Preisen*
  lautet und ihre Kandidatengröße damit real ist — ein Preisinstrument bewegt sie gar nicht.
  **Vor dem Abwägen die Skalentabelle des Architekten lesen: Sie schließt Lesarten aus, ohne
  dass man über Inhalt streiten muss.**
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
- **Eine Frage an eine andere Rolle weiterreichen erzeugt eine Lücke, wenn die danach nichts
  mehr schreibt.** Läuft man ohnehin, kostet die Entscheidung nichts; liegen gelassen sieht
  sie später wie ein Balanceproblem aus, obwohl sie eine Definition ist.
- **„Ein Abruf hat die Frage geklärt" war falsch.** Ein Abruf klärt eine Reihe, nie ein
  Minimum über viele — wer eine Regel über *alle* Reihen aufstellt, muss die **bindende**
  suchen. Am 2026-09-02 bestätigt: Die bindende war eine, die ich nie angesehen hatte.
- **Ich habe eine Invariante behauptet und zwei Absätze darunter die Probe gerechnet, die
  ihr widersprach.** Wer Invariante und Zahlenbeispiel hinschreibt, hat sich selbst einen
  Test geschrieben — er kostet dreißig Sekunden.
- **Der Ausweg, den ein Prüfer anbietet, ist auf sein Kriterium optimiert, nicht auf den
  Entwurf.** Prüffrage: Steht im Repo bereits ein Argument gegen genau diese Konstruktion,
  und gilt es hier auch?
- **Eine Tabelle, die sich abschließend nennt, war es zweimal nicht — und die Lücke lag
  beide Male dort, wo ich nicht gesucht habe.** Die Kanaltabelle ließ den Kanal aus, an dem
  das Genre stirbt; die Nachziehliste zu `R = 20` ließ sieben Stellen in `technik.md` aus,
  sechs außerhalb eines T-Blocks, darunter dessen ganzes Laufzeitbudget — ich war die
  T-Nummern durchgegangen, die R *definieren*, und das findet jede Regel und keine
  Erwähnung. **Eine Verweistabelle prüft man am fremden Dokument entlang, nicht am eigenen
  Begriff: einmal über jede Zahl statt über jede Regel.**
- **2026-09-03 — Eine Zahl aus einem Befund gilt für die Fassung, in der der Prüfer sie
  gerechnet hat.** Er korrigierte 120 auf 112; nach meiner Entscheidung waren es 106. **Jede
  Zählzeile nach der eigenen Änderung von vorn zählen, nie aus dem Befund abschreiben.**
- **2026-09-03 — Eine Formel, die auf eine ungeschriebene Formel zeigt, ist wieder nur ein
  Adjektiv.** Der Zollkeil stand seit Fassung 2 in der Markträumung und war nirgends
  hingeschrieben; erst als ich ihn vom Rest trennen musste, fiel es auf. **Wenn eine Lücke
  nur eine zulässige Füllung hat, ist sie keine offene Frage, sondern eine vergessene Zeile.**
- **Websuche: eine in neun Läufen.** Auslöser ist nicht nur „blockiert mich das", sondern
  auch „behaupte ich hier etwas über die Außenwelt". In beiden 0054-Läufen keine: Jede Zahl
  stand im Deckungsbefund, in `reihen.toml` oder in `technik.md`.
- **2026-09-03, zweimal bestätigt — Archivieren geht nicht: `Write` und `cp` sind gesperrt,
  die Rolle hat nur `Edit(specs/**)` und `Edit(notizen/spielentwerfer.md)`.** Also an der
  Grenze zusammengezogen statt verschoben; zusammenziehen statt streichen verliert nichts.
  **Für den Portfolio-Manager: Die Rolle braucht `Edit(notizen/archiv/**)`.**
- **2026-09-03 — Ein zweiter Lauf auf demselben Paket ist kein verlorener Lauf.** Die
  Entscheidung stand und hielt jede Nachrechnung; gefunden habe ich trotzdem sieben Stellen.
  **Wer ein fertiges Paket erneut zugeteilt bekommt, prüft die Abnahme Bedingung für
  Bedingung nach — und danach das, was die Grenzen des Pakets nur *benennen* lassen. Dort
  sitzt der Rest, weil es die Stelle ist, an der niemand etwas ändern durfte.**

## Offene Faehrten

- **Erledigt am 2026-09-03 (Paket 0054, zwei Läufe): R = 20, Fenster 2001–2021**, und die
  Nachziehliste für `technik.md` ist vollständig. Was daraus hervorging: die nächsten zwei.
- **Woher kommt der Leitzinspfad für Deutschland und China?** Die Reihenliste führt für beide
  keinen Wert, in jedem Fenster. Seit dem Wegfall der Sollrolle ist es eine Beschaffungsfrage
  des Datenbauers: Eine Eingabe darf gefüllt werden, eine Sollreihe des Prüfjahrgangs nicht.
- **Trägt ein einheitlicher Zinsbegriff über alle vier Länder?** Als Sollreihe war die
  Uneinheitlichkeit tödlich, als Eingabe ist sie es nicht — aber ein Pfad auf falschem Niveau
  treibt vier der sechzehn Prüfgegenstände. Am Jahrgangsbau zu sehen.
- **Ist der aggregierte Zollsatz der Weltbank (WITS, Drittanbieter-Ausnahme) verwendbar?**
  Ist er gesperrt, verliert der Rückvergleich das wichtigste seiner drei verankerten
  Instrumente. Der Entwurf bleibt tragfähig, sein Beleg halbiert sich.
- **Gibt es einen Parametersatz, in dem der Fonds groß genug und nicht zu groß ist?** Die
  Märkte sind ganze Sektorkapitalstöcke: Eine Stufe muss bezahlbar sein, und erreichbare
  Stufenzahlen müssen die Aufsichtsschwellen erreichen. Nur am Prüfstand zu sehen.
- **2026-09-02, aus Paket 0021: `druck` hat dieselbe Lücke, die `gegendruck` hatte.** Ob der
  anliegende Lobbydruck stehen bleibt, zerfällt oder verbraucht wird, steht nirgends — nicht
  folgenlos, weil Einfluss der Anteil am Verhältnis `druck : gegendruck` ist. Vorschlag
  (dieselbe Halbierung) steht in `spiel.md`. **Lehre: Wer eine Lücke füllt, sollte die
  spiegelbildliche Größe gleich mitlesen — sie hat oft dieselbe.**
- **2026-09-03, neu aus Paket 0039: Ich habe die Form des Zollkeils in `spiel.md`
  festgelegt**, weil T28 ihn nannte, ohne ihn hinzuschreiben. Widerspricht der Architekt,
  ist es ein Befund gegen *Der Zollkeil ist multiplikativ*, nicht gegen die Zollzeile.
  Zweite Folge: Die Zollzeile misst einen Handelsstrom, die Haushaltszeile das ganze BIP —
  **ob ein `gegenlobby_satz` beide trägt, ist damit schärfer gestellt; nur am Prüfstand zu
  sehen.**
- **2026-09-02: Reicht `gegenlobby_satz` als Ganzzahl?** Klasse 9 kennt keine Unterteilung,
  kleinster Wert 1 Punkt je 10.000 Tsd USD; die Größenordnungsprobe ergibt rund 10.500
  Punkte für einen US-Haushaltsschritt. Gegensteuern geht über `lobbykosten`, weil in
  Schritt 3 nur das Verhältnis zählt; sonst ist eine Zehntausendstel-Skala ein ADR gegen T5.
