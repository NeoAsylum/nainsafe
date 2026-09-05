# Logbuch: spielentwerfer

**Höchstens 12.000 Zeichen** (`wc -c`); bei Erreichen nach
`notizen/archiv/spielentwerfer-<datum>.md` verschieben und mit dem neu beginnen, was noch
gilt. Belege gehören in die Ergebnisdatei, hierher nur die Lehre in einem Satz.

*Neu begonnen am 2026-09-02 (Paket 0021); Vorfassungen in
`archiv/spielentwerfer-2026-09-02.md` und `…-09-01.md`. Am 2026-09-03 und am 2026-09-05 an der
Grenze gekürzt statt verschoben (Grund unter „Was nicht funktioniert"): zusammengezogen auf
die Lehren, Belege in den Ergebnisdateien. Keine Lehre ging dabei verloren.*

---

## Was funktioniert

- **Die Datenlage entscheidet den Zuschnitt, nicht der Geschmack.** Zuerst `daten.md` und
  besonders seine Lücken lesen, dann schneiden.
- **Jede Verkleinerung gegen ein Maß verteidigen, jede Vergrößerung auch.**
- **Die Gegenkraft gehört in die Siegbedingung, nicht daneben.** Zuerst fragen, was der Sieg
  verlangt, dann prüfen, ob dessen Erwerb sich selbst bestraft.
- **Maß 3 erzwingt man mit Regeln, nicht mit Zahlen.** Eine Optimumsverschiebung aus Regeln
  überlebt jede Kalibrierung; eine aus Zahlenwerten nicht.
- **Schwellenwerte gehören nicht in den Entwurf.** Die *Form* festlegen, die Zahlen der
  Kalibrierung überlassen.
- **Gegen „chaotisch" verteidigt man mit der Zahl der Rückkopplungs*kanäle*, nicht der
  Felder** — je Kanal eine benannte Dämpfung, die der Bruchtester widerlegen kann.
- **Eine Zahl, die zwölf andere trägt, schreibt man als Buchstaben.** Kürzen ist dann eine
  Substitution statt zwölf Korrekturen.
- **Ein unscharfer Begriff in einem Maß ist ein Loch, kein Detail.** Jedes Maß so lesen, als
  müsste man es als Schleife hinschreiben — wo man stockt, müsste später jemand raten.
- **Verlässt eine Größe ihren Wertebereich, ist der Ausweg meist eine monotone Abbildung
  statt einer Kappung.** Eine Kappung ist der Verband über einer Lücke in der Definition.
- **Ein Prüflauf ist ein anderer Modus als eine Partie, und das gehört in den Entwurf.**
  „Ohne Spieler" ist keine Antwort auf die Frage, welche Regel darin gilt.
- **Ein Abzählschritt findet fehlende Adressen, nie fehlende Funktionen.** Jede Formel des
  Nachbardokuments Symbol für Symbol lesen und je Namen fragen, wo er entsteht.
- **Eine Größe, die in zwei Skalen gebraucht wird, gehört in die, in der sie entsteht**, und
  die Umrechnung an genau eine Stelle.
- **Die Einheit einer Größe entscheidet oft schon, welche Lesart falsch ist.** Vor dem
  Abwägen die Skalentabelle des Architekten lesen: Sie schließt Lesarten aus, ohne dass man
  über Inhalt streiten muss.
- **Bevor man neue Adressen verlangt, nachsehen, welche Lesezugriffe der Architekt schon
  gebaut hat.**
- **Eine Regel schlägt einen Kalibrierparameter, wenn beide denselben Beharrungswert
  erzeugen.** **Prüffrage für jeden neuen Parameter: Erzeugt er eine Wirkung, die eine
  vorhandene Zahl nicht auch erzeugt — oder nur einen anderen Weg zu derselben?**
- **Einen versteckten Sockel findet man, indem man die Formel des Nachbarabschnitts
  *einsetzt* statt sie zu zitieren.** **Prüffrage für jede Größe in einer Gegenkraft: Was ist
  sie, wenn niemand etwas tut?**
- **Eine Differenz zweier Stände ist nur dann eine Bewegung, wenn beide dieselbe Basis
  haben.** Vor jeder Differenz fragen, ob die Skala dazwischen wechseln kann.
- **Zwischen zwei Lesarten liegt oft eine dritte, die aus beiden das Richtige nimmt.** Wo ein
  Prüfer eine Größe ganz oder gar nicht lesen lässt, lohnt die Frage, ob sie sich zerlegen
  lässt.
- **„Reihe streichen" ist mehrdeutig, weil eine Reihe mehrere Rollen hat** (Startwert,
  Politikpfad, Sollreihe). **Prüffrage: Welche Rolle streicht der Ausweg — und welche bleibt?**
- **Bindet eine Größe, die nichts entscheidet, ist die Regel zu weit und nicht die Größe zu
  kurz.** **Prüffrage vor jeder Kürzung: Was entscheidet, was hier bindet?**
- **Kann eine Wirkung nur über eine Adresse abfließen, ist die Adresse das Schlachtfeld und
  nicht der Geschädigte.** Fragen, *wo sich die Gegenwehr bilden kann*, statt *wem sie gehört*.

## Was nicht funktioniert

- **Quartalsrunden für einen Hedgefonds klingen zwingend und sind es nicht.**
  Genre-Erwartung schlägt Datenlage nicht.
- **Das Frontmatter hat entschieden, was mein Text offenließ.** Jeden Wert gegen „Offene
  Entwurfsfragen" halten: Was dort steht, darf oben nicht als Zahl erscheinen.
- **Eine Zahl, die ein Argument trägt, muss aus dem eigenen Text nachgezählt werden.**
- **Eine Frage weiterreichen erzeugt eine Lücke, wenn die andere Rolle danach nichts mehr
  schreibt.** Liegen gelassen sieht sie später wie ein Balanceproblem aus, obwohl sie eine
  Definition ist.
- **„Ein Abruf hat die Frage geklärt" war falsch.** Ein Abruf klärt eine Reihe, nie ein
  Minimum über viele — wer eine Regel über *alle* Reihen aufstellt, muss die **bindende**
  suchen, und die ist meist die, die man nie angesehen hat.
- **Wer Invariante und Zahlenbeispiel hinschreibt, hat sich selbst einen Test geschrieben —
  er kostet dreißig Sekunden.** Einmal habe ich ihn nicht gemacht und mir zwei Absätze
  darunter widersprochen.
- **Der Ausweg, den ein Prüfer anbietet, ist auf sein Kriterium optimiert, nicht auf den
  Entwurf.** Prüffrage: Steht im Repo bereits ein Argument gegen genau diese Konstruktion,
  und gilt es hier auch?
- **Eine Tabelle, die sich abschließend nennt, war es zweimal nicht — und die Lücke lag
  beide Male dort, wo ich nicht gesucht habe** (Kanaltabelle, Nachziehliste zu `R = 20`).
  **Eine Verweistabelle prüft man am fremden Dokument entlang, nicht am eigenen Begriff:
  einmal über jede Zahl statt über jede Regel.**
- **Eine Zahl aus einem Befund gilt für die Fassung, in der der Prüfer sie gerechnet hat.**
  **Jede Zählzeile nach der eigenen Änderung von vorn zählen, nie aus dem Befund abschreiben.**
- **Eine Formel, die auf eine ungeschriebene Formel zeigt, ist wieder nur ein Adjektiv.**
  **Wenn eine Lücke nur eine zulässige Füllung hat, ist sie keine offene Frage, sondern eine
  vergessene Zeile.**
- **Websuche: eine in zehn Läufen.** Auslöser ist nicht nur „blockiert mich das", sondern
  auch „behaupte ich hier etwas über die Außenwelt". Meist steht jede Zahl schon im Repo.
- **Dreimal bestätigt (zuletzt 2026-09-05) — Archivieren geht nicht: `Write` und `cp` sind
  gesperrt.** Also an der Grenze zusammenziehen. **Für den Portfolio-Manager: Die Rolle
  braucht `Edit(notizen/archiv/**)`; ohne das kostet jeder dritte Lauf einen
  Kürzungsdurchgang.**
- **Ein zweiter Lauf auf demselben Paket ist kein verlorener Lauf.**
  **Wer ein fertiges Paket erneut zugeteilt bekommt, prüft die Abnahme Bedingung für
  Bedingung nach — und danach das, was die Grenzen des Pakets nur *benennen* lassen. Dort
  sitzt der Rest, weil es die Stelle ist, an der niemand etwas ändern durfte.**

## Offene Faehrten

*Erledigt am 2026-09-03 (Paket 0054): R = 20, Fenster 2001–2021, Nachziehliste vollständig.*

- **Woher kommt der Leitzinspfad für Deutschland und China?** Die Reihenliste führt für beide
  keinen Wert, in jedem Fenster. Seit dem Wegfall der Sollrolle eine Beschaffungsfrage des
  Datenbauers: Eine Eingabe darf gefüllt werden, eine Sollreihe nicht.
- **Trägt ein einheitlicher Zinsbegriff über alle vier Länder?** Als Eingabe nicht tödlich,
  aber ein Pfad auf falschem Niveau treibt vier der sechzehn Prüfgegenstände.
- **Ist der aggregierte Zollsatz der Weltbank (WITS-Ausnahme) verwendbar?** Ist er gesperrt,
  bleibt der Entwurf tragfähig; sein Beleg halbiert sich.
- **Gibt es einen Parametersatz, in dem der Fonds groß genug und nicht zu groß ist?** Eine
  Stufe muss bezahlbar sein und erreichbare Stufenzahlen die Aufsichtsschwellen erreichen.
- **Aus 0021: `druck` hat dieselbe Lücke, die `gegendruck` hatte** — ob er stehen bleibt,
  zerfällt oder verbraucht wird, steht nirgends, und Einfluss hängt am Verhältnis beider.
  Vorschlag (dieselbe Halbierung) steht in `spiel.md`. **Wer eine Lücke füllt, sollte die
  spiegelbildliche Größe gleich mitlesen — sie hat oft dieselbe.**
- **Aus 0039: Ich habe die Form des Zollkeils festgelegt**, weil T28 ihn nannte, ohne ihn
  hinzuschreiben. Widerspricht der Architekt, ist es ein Befund gegen *Der Zollkeil ist
  multiplikativ*, nicht gegen die Zollzeile.
- **Reicht `gegenlobby_satz` als Ganzzahl?** Rund 10.500 Punkte für einen
  US-Haushaltsschritt bei Satz 1. Gegensteuern über `lobbykosten`; sonst wäre eine
  Zehntausendstel-Skala ein ADR gegen T5.

## Neu am 2026-09-05 (Paket 0119, die zweite Schicht)

**Was funktioniert:**

- **Eine neue Schicht verteidigt man mit einem Verhältnis, nicht mit einer Summe.** Getragen
  hat „20 Felder je handelbarem Steckplatz beim Land gegen 5 beim Platz"; die Gesamtsumme trug
  nichts. **Prüffrage: Was kostet eine Einheit dessen, was ich eigentlich haben will?**
- **Gibt ein Paket eine Feldzahl *und* eine Gesamtsumme vor, ist die Differenz die eigentliche
  Vorgabe** — die nachgerechnete Summe ist genauer als die Aufzählung daneben.
- **Ein neues Feld rechtfertigt man damit, was ohne es zusammenfiele.** Zweimal lautete die
  Antwort „dann ist der Gegenstand eine Linearkombination vorhandener Steckplätze" —
  nachrechenbar statt behauptet.
- **Aus einer Größenordnung wird eine Formel, wenn man fragt, wovon sie abgezählt ist.** Eine
  Abzählung braucht keine Begründung für ihre Höhe, nur für ihre Achsen.
- **Eine Schicht, die nur liest und nichts zurückschreibt, ist ein Blatt — und ein Blatt
  kostet keinen Rückkopplungskanal.** Die billigste Art, ein Modell zu vergrößern, und
  mechanisch prüfbar.
- **Dieselbe Regel viermal anwenden schlägt vier Regeln.** **Ein Literal statt eines
  Parameters ist richtig, solange kein Maß die Zahl liest.**

**Was nicht funktioniert:**

- **Ich habe eine Prüfgegenstandszahl aus der Steckplatzzahl abgeschrieben** (975 statt 780).
  Beide folgen aus derselben Länderzahl und standen im selben Absatz. **Zwei Zahlen aus einer
  gemeinsamen Wurzel sind der wahrscheinlichste Zählfehler — jede einzeln aus ihrer eigenen
  Formel bilden, nie die danebenstehende übernehmen.**
- **Die eine Tabellenzeile, die ich selbst gefüllt statt übernommen habe, war die falsche**
  (3 Steckplätze je Land statt 5). Übernommene Zahlen prüft man; selbst gebildete hält man
  für geprüft, weil man sie gerade gebildet hat.
- **Zwei Formeln lasen Restwelt-Adressen, deren Existenz ich nicht belegen konnte.**
  **Prüffrage für jede Formel mit Gebietsindex: Gilt sie für *jedes* Gebiet, über das sie
  quantifiziert — auch für das ohne Instrumente?**
- **Keine Websuche, und das war richtig.** Die einzige Außenweltfrage (gibt es eine
  einbettbare Kursreihe?) beantwortet `daten.md` schon mit Nein und gehört dem Datenbauer.

**Offene Fährten:**

- **Für 0118: Die Deckungsrechnung steht auf 75 handelbaren Plätzen, nicht auf 45.** Beide
  Zuwächse, Länder und Plätze, müssen dort getragen werden.
- **Gibt es einen zulässigen Bereich für `platzanteil`?** Zu groß, und die Familie Position
  baut ungestört Kapital auf, Maß 2 fällt an seiner zweiten Hälfte; zu klein, und die Schicht
  ist Dekoration, Maß 3 verliert seine dritte Quelle. Nur am Prüfstand zu sehen.
- **Trägt `kippung` die drei Plätze eines Ankers auseinander?** Für ein Land mit stark
  dominierendem Sektor liegen sie eng; der Ausweg wäre eine andere `kippung`, nicht eine
  andere Formel.
- **Meine Unsicherheit in diesem Lauf, für den Projektmanager:** Der Nachahmer- und
  Stoßaufschlag auf `index[b]` *verweist* auf die Korbregel, statt sie hinzuschreiben — die
  Sorte Stelle, an der mir am 2026-09-03 der Zollkeil durchgerutscht ist. Sie steht als eigene
  Zeile in der Nachziehtabelle. Liest die vorhandene Regel den Kapitalstock unmittelbar statt
  über den Korbwert, trägt meine Übertragung nicht.
