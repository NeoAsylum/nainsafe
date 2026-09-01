# Logbuch: spielentwerfer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/spielentwerfer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-01 nach dem vierten Lauf; die Vorfassung steht vollständig in
`notizen/archiv/spielentwerfer-2026-09-01.md`. Übernommen ist, was noch führt.*

---

## Was funktioniert

- **Die Datenlage entscheidet den Zuschnitt, nicht der Geschmack.** Zuerst `daten.md` und
  besonders seine Lücken lesen, dann schneiden — die Idee nannte 12 Länder, 6 Sektoren,
  Quartalsrunden, die Daten trugen 4, 3 und Jahresrunden. Wer so vorgeht, bekommt jede
  Entscheidung mitgeliefert und muss nichts abwägen.
- **Jede Verkleinerung gegen ein Maß verteidigen, jede Vergrößerung auch.** Vier Länder
  statt drei mit Maß 1 (bei drei hat jeder Zoll genau einen Ausweichpartner, die Wahl ist
  keine), drei Sektoren statt sechs mit Maß 4 (sechs wären ein Konstrukt ohne Sollreihe).
  Das ergibt Zahlen, die man verteidigen kann, statt Zahlen, die plausibel klingen.
- **Die Gegenkraft gehört in die Siegbedingung, nicht daneben.** Das Mandat verlangt
  Kapital UND Einfluss, und Einfluss ist genau die Größe, deren Erwerb Aufsicht,
  Gegenlobby und Regierungswechsel weckt. Zuerst fragen, was der Sieg verlangt, dann
  prüfen, ob dessen Erwerb sich selbst bestraft.
- **Maß 3 erzwingt man mit Regeln, nicht mit Zahlen.** Nachahmer (funktionierende Position
  wird abgegrast) und Marktenge (Überrendite fällt mit dem Marktanteil) sind bloße Zähler
  mit Schwelle. Eine Optimumsverschiebung, die aus Regeln folgt, überlebt jede
  Kalibrierung; eine, die aus Zahlenwerten folgt, nicht.
- **Long UND short ist die billigste Antwort auf „eine Richtung dominiert".** Weil der
  Fonds gegen eine Politik verdienen kann, ist keine Richtung vorteilhaft — die Klage aus
  Democracy 4 ohne eine einzige Ausgleichsregel.
- **Schwellenwerte gehören nicht in den Entwurf.** Die *Form* festlegen, die Zahlen der
  Kalibrierung überlassen. Wer sie vorab rät, gibt dem Architekten falsche Präzision und
  dem Selbstspiel nichts zu tun.
- **Gegen „chaotisch" verteidigt man mit der Zahl der Rückkopplungs*kanäle*, nicht mit der
  Zahl der Felder.** Eine abschließende Liste rundenübergreifender Kanäle mit je benannter
  Dämpfung ist eine Aussage — und der Bruchtester kann sie widerlegen („200 Runden ohne
  Spieler, verlässt eine Größe ihren Bereich?").
- **Die Partielänge aus den Daten ableiten, nicht aus dem Genre.** Regel: Partielänge = das
  Fenster, in dem *jede* Sollreihe ohne Füllung belegt ist. Nebengewinn, den ich nicht
  gesucht hatte: Der Schnitt entfernte Brasiliens Hyperinflation, an der jede prozentuale
  Fehlerrechnung zerbrochen wäre.
- **Ein unscharfer Begriff in einem Maß ist ein Loch, kein Detail.** Faustregel: Jedes Maß
  einmal so lesen, als müsste man es als Schleife hinschreiben — wo man stockt, steht ein
  Wort, das der Selbstspieler später raten müsste.
- **Eine Zahl, die zwölf andere trägt, schreibt man als Buchstaben.** Eine falsche
  Partielänge machte in Fassung 2 Ergebnisskala, Partiedrittel, Fenstergrenzen und vier
  Kostenformeln falsch. Jede abgeleitete Größe steht jetzt als Formel in R; ein weiteres
  Kürzen ist eine Substitution statt einer Neufassung.
- **Verlässt eine Größe ihren Wertebereich, ist der Ausweg meist eine monotone Abbildung,
  nicht eine Kappung.** `H/(H+N)` statt `H/N`: streng monoton darin, per Konstruktion in
  [0,1], Rangfolge erhalten. — **Zweiter Fall, 2026-09-01:** Die Kappung im Fehlbetrag der
  Ergebnisskala war der Ersatz für eine fehlende Aggregationsregel und entfiel mit ihr
  ersatzlos, weil jeder Summand per Konstruktion beschränkt ist. **Eine Kappung ist meist
  der Verband über einer Lücke in der Definition — erst die Regel schreiben, dann sehen,
  ob die Kappung noch etwas tut.**
- **Ein Prüflauf ist ein anderer Modus als eine Partie, und das gehört in den Entwurf.**
  Der Rückvergleich mit „Fonds mit Nullvermögen" teilte in Runde 1 durch null. Lösung:
  eigener Modus, Fondsteilsystem ganz aus, Instrumente exogen. **Jedes Maß einmal als
  Programmablauf durchgehen und fragen, welche Regel des Spiels darin gilt und welche
  nicht** — „ohne Spieler" ist keine Antwort darauf.
- **2026-09-01 — Bei mehreren Lesarten zuerst fragen, welche dieselbe *Ordnung* erzeugen.**
  Der Prüfer legte drei nebeneinander (Summe, Mittel, schwächeres der beiden); Summe und
  Mittel gehen durch Halbieren auseinander hervor und ordnen identisch. Zu entscheiden war
  zwischen zwei, nicht zwischen drei — und nur die Skala war noch frei.

## Was nicht funktioniert

- **Quartalsrunden für einen Hedgefonds klingen zwingend und sind es nicht.** Alle
  Kernreihen außer Zins und Wechselkurs liegen jährlich vor; Quartalstakt hätte drei von
  vier Runden vom Rückvergleich abgeschnitten, also die einzige Achse geschwächt, die diese
  Fabrik voraushat. Genre-Erwartung schlägt Datenlage nicht.
- **Das Frontmatter hat entschieden, was mein Text offenließ.** Startjahr 1980 stand oben
  als Tatsache und unten unter „offene Fragen" — erster schwerer Befund, zu Recht. Vor dem
  Schreiben des Frontmatters jeden Wert gegen „Offene Entwurfsfragen" halten: Was dort
  steht, darf oben nicht als Zahl erscheinen.
- **Eine Zahl, die ein Argument trägt, muss aus dem eigenen Text nachgezählt werden.**
  „Rund 150 Größen" war meine einzige Verteidigung gegen den wunden Punkt aus
  `agentenbau.md` und um Faktor zwei falsch.
- **Eine offene Frage an eine andere Rolle weiterreichen erzeugt eine Lücke, wenn diese
  Rolle danach nichts mehr schreibt.** Vorletzter Blick jedes Laufs gehört dem Abschnitt
  „Was ich nicht entschieden habe" der Nachbarergebnisse. — 2026-09-01 zum zweiten Mal
  aufgetreten und diesmal geschlossen (Beteiligungen im Fondsvermögen, aus `technik.md`
  Abschnitt 12): **Läuft man ohnehin, kostet die Entscheidung nichts; lässt man sie liegen,
  sieht sie später aus wie ein Balanceproblem, obwohl sie eine Definition ist.**
- **„Ein Abruf hat die Frage geklärt" war falsch, und ich hatte es als Erfolg notiert.**
  Wer eine Regel über *alle* Reihen aufstellt, hat sie erst belegt, wenn er die **bindende**
  Reihe gesucht hat, nicht die erstbeste. Ein Abruf klärt eine Reihe, nie ein Minimum über
  viele.
- **2026-09-01 — Ich habe eine Invariante behauptet und zwei Absätze darunter die Probe
  dazu gerechnet, die ihr widersprach.** „Über 15 Runden `3·ai` Steckplätze" gegen „Runden
  1 bis 5: drei von fünfzehn"; richtig war die Probe, gefunden hat es der Architekt.
  **Wer eine Invariante und ein Zahlenbeispiel dazu hinschreibt, hat sich selbst einen Test
  geschrieben — er kostet dreißig Sekunden, und ich habe ihn nicht ausgeführt.**
- **2026-09-01 — Der Ausweg, den ein Prüfer anbietet, ist auf sein Kriterium optimiert,
  nicht auf den Entwurf.** Vorgeschlagen war die billigste Reparatur (Regel übernehmen,
  Kappung behalten, null Folgeänderungen); sie hätte die untere Hälfte des Ergebnisraums
  geglättet, genau dort, wo Maß 3 sein Argminimum sucht. **Prüffrage für jeden angebotenen
  Ausweg: Steht im Repo bereits ein Argument gegen genau diese Konstruktion, und gilt es
  hier auch?** Hier stand es im Nachbardokument — der Architekt kappt seine Botzielgröße
  aus demselben Grund nicht.
- **Keine Websuche gefahren, in vier Läufen nicht.** `daten.md`, das Marktprofil und
  `agentenbau.md` deckten jede Frage, an der der Entwurf hing. „Suche, wenn dich eine
  Antwort blockiert" hat hier zu null Suchen geführt, und das war richtig.

## Offene Faehrten

- **Stand 2026-09-01: Der Ruecklaufzaehler des Pakets `0001-entwurf-abnahme` steht bei 2
  von 3.** Danach `blockiert` und Meldung an den Betreiber. Fassung 5 ist die letzte, die
  zurueckgehen darf; offen sind nur noch Messungen am laufenden Kern, keine
  Entwurfsfragen.
- **Die schwerste offene Frage des Entwurfs steht in `spiel.md`:** Ist der aggregierte
  Zollsatz der Weltbank (WITS-Herkunft, Drittanbieter-Ausnahme) verwendbar? Ist er
  gesperrt, verliert der Rueckvergleich das wichtigste seiner drei verankerten
  Instrumente. Der Entwurf bleibt tragfaehig, sein Beleg halbiert sich.
- **Traegt das Fenster 1997-2021 auch die chinesische und die brasilianische
  Leitzinsreihe?** Quelle ist IWF IFS, `imf.org` weist den Abruf mit 403 ab (zweimal
  versucht). Ersatzindiz: die freie WDI-Zinsreihe `FR.INR.LEND` beginnt fuer BR ebenfalls
  1997. Lehre: **Ist die eigentliche Quelle gesperrt, gibt eine benachbarte freie Reihe
  oft dieselbe Kante** — ein Indiz fuer den Preis eines Abrufs, kein Beweis.
- Erledigt und nur als Merkposten: Deutschland vor/nach 1999 (Behandlung des Architekten
  uebernommen, Bruch in Runde 3) und Brasiliens Disinflation (faellt mit dem Start 1997
  heraus).
