---
nr: 0007
titel: Agentenarbeit ist kein Personal — G4 und G9 zählen Menschen, nicht Arbeit
datum: 2026-08-31
status: gueltig
ersetzt: null
ersetzt_durch: null
betrifft: [ideen, bewertung, betrieb]
---

# ADR 0007 — Agentenarbeit ist kein Personal

## Kontext

Der Betreiber:

> Kein Personal ist glaub etwas zu strikt gedacht bisher. Wir können natürlich für
> manche Dinge auch täglich Agenten einsetzen.

Die erste Prüfung dieser Aussage ergab etwas Unerwartetes: **An G9 („Braucht Personal")
ist keine einzige Idee gestorben.** Die fünfzehn Ablehnungen verteilen sich auf G5
(vier), G7 (vier), G3 (drei), G6 (drei) und G4 (eine). G9 hat nie ausgelöst.

Wirksam geworden ist die zu strikte Denkweise trotzdem — nur an anderer Stelle. G4
lautete: *„Prüffrage: Was passiert bei 100 Kunden statt 10? Skaliert der Aufwand mit der
Kundenzahl, ist es abgelehnt."* Das las sich, als wäre wiederkehrende Arbeit **an sich**
das Problem. Die Betriebslinse hat entsprechend geurteilt:

- 0004: „kundenspezifische Feldzuordnung ist nicht ein Anlaufproblem, sondern der Kern
  des Produkts […] Der Aufwand skaliert mit der Kundenzahl statt mit dem
  Rechnungsvolumen — genau die Prüffrage von G4."
- 0005: „die Auslegungsregeln sind je Betrieb verschieden und ändern sich laufend, womit
  der Aufwand mit der Kundenzahl wächst."
- 0012: „Die Pflege von rund 41 Zuständigkeiten und 38 Landesformularen […] rund 1,8
  Stunden je Woche und damit fast das ganze Budget bei null Umsatz."

Alle drei beschreiben Arbeit, die **ein täglich laufender Agent erledigen kann**. Die
Regel hat nicht gefragt, wer sie tut.

## Entscheidung

**G4 und G9 zählen ab sofort Menschen, nicht Arbeit.**

**G4** heißt jetzt „Mehr als zwei Stunden *des Betreibers* pro Woche". Die Prüffrage
lautet nicht mehr *„Was passiert bei 100 Kunden statt 10?"*, sondern **„Was davon muss
ein Mensch tun, und warum?"** Drei Sorten Arbeit, drei Ziele:

| Sorte | Beispiel | wohin |
|---|---|---|
| Agentenarbeit | Feldzuordnung herleiten, Formularstände nachführen, Auffälligkeiten sichten, Supportantworten entwerfen | erlaubt — kostet aber Geld, siehe G7 |
| Menschenarbeit | Freigaben mit Rechtsfolge, Vertragsverhandlung, ein Name unter einem Ergebnis, Streitfälle | zählt gegen die zwei Stunden |
| Verlagerte Arbeit | Agent handelt unbeaufsichtigt im Prozess des Kunden | zählt gegen G6 |

**G9** schließt weiter aus, was geführte Menschen braucht — Vertriebsteam, Handwerker vor
Ort, eine Schicht, die besetzt sein muss. Redaktion, Übersetzung, Moderation, Datenpflege
und Einrichtung je Kunde standen bis heute in derselben Liste, weil unausgesprochen
angenommen wurde, dass sie einen Menschen brauchen. Sie sind heraus. Die Grenze verläuft
jetzt an drei Stellen: **Verantwortung** (ein Name muss darunter), **Anwesenheit** (vor
Ort oder am Telefon — ohnehin G3) und **Führung** (einweisen, kontrollieren, bezahlen).

## Die zwei Gegenrechnungen

Eine Lockerung ohne Gegenrechnung wäre keine Regel, sondern ein Wunsch. Was aus G4
herausfällt, taucht an zwei Stellen wieder auf:

**In G7 als Stückkosten.** Agentenarbeit ist gratis in Stunden und teuer in Tokens.
`Läufe je Kunde und Monat × Tokens je Lauf × API-Preis`. Eine schmale tägliche Aufgabe liegt bei rund
60.000 Tokens je Lauf, also etwa 1,8 Mio. im Monat; je nach Modell und Cache-Anteil sind
das **unter einem Euro bis rund sechs Euro je Kunde und Monat**. Bei einem 12-€-Produkt
kann das die halbe Marge sein, bei einem 150-€-Produkt ist es ein Rundungsfehler. **Je billiger das
Produkt, desto weniger Agentenarbeit trägt es**, und die billigen Produkte sind gerade
die in den großen Segmenten. Das Abo des Betreibers zählt hier nicht: Es deckt die
Fabrik, nicht die Kundenlast.

**In G6 als Haftung.** Wo ein Agent unbeaufsichtigt im Prozess des Kunden handelt, ist
der Aufwand nicht verschwunden, sondern umgewandelt: Ein Fehler geschieht schneller,
öfter und ohne dass jemand hinsieht. Prüffrage: *Was kostet der zehnte falsche Vorgang,
bevor jemand ihn bemerkt?* Der Ausweg ist nicht Aufsicht — Aufsicht wäre wieder
menschliche Zeit —, sondern ein Produkt, dessen schlimmster Einzelfehler klein ist.

## Was das für die fünfzehn toten Ideen heißt

Ehrlich gezählt: **eine.**

| Idee | Todesursache | lebt sie durch tägliche Agenten? |
|---|---|---|
| 0004 XRechnung-Export | G4, Feldzuordnung je Kunde | **Wiedervorlage gelaufen, siehe unten.** Die alte G4-Ablehnung trägt nicht mehr — und die Idee stirbt jetzt an G6. |
| 0005 Zettelfoto | Preisarithmetik + G6 | Nein. Die Auslegungsregeln sind Agentenarbeit, aber der Preisdeckel steht (Vollprodukte 15,99–49 €, eine Teilfunktion müsste das Zwei- bis Sechsfache kosten), und G6 wird durch die Lockerung **schärfer**: eine falsch übertragene Lohnzeile ist genau der unbeaufsichtigte Vorgang. |
| 0012 Asbestanzeige | Substanz | Nein. Der Anwalt fand, dass im mittleren Risikobereich nur Ort, Beginn und Dauer anzuzeigen sind — der Produktnutzen fällt einmal in sechs Jahren an. Kein Arbeitsproblem. |
| 0003 CRA-Wachdienst | G6, Fristüberwachung | Nein — **schärfer**. Der ganze Dienst löst eine 24/72-Stunden-Frist aus; ein übersehener Treffer ist der Schaden. |
| 0010 Tagesplan | G6, Zutrittsdaten | Nein. Datenrisiko, nicht Arbeit. |
| 0009 Haushaltsturnus | Nachfrage | Nein. Kein Sensor für das, was abgerechnet wird. |
| 0001, 0002, 0007 | G5 Erlaubnis | Nein. Ein Agent erwirbt keine Erlaubnis. |
| 0011, 0013, 0014, 0015 | G7 Größe | Nein. Das löst die Prozessachse (ADR 0005), nicht die Agentenarbeit. |
| 0006, 0008 | G3 Vertrauen und Termin | Nein. Beides ist Vertrauens- und Vertriebsarbeit, keine Fleißarbeit. |

Der Ertrag rückwärts ist also dünn. **Vorwärts ist er größer:** Zwei der drei
Betriebslinsen-Urteile dieser Woche waren von der jetzt erlaubten Sorte. Die Regel hätte
still weiter Ideen getötet, deren Aufwand niemanden gekostet hätte.

## Die Probe: 0004 unter den neuen Regeln

0004 war die einzige Idee, deren Ablehnung sich vollständig auf die alte G4 stützte. Sie
wurde deshalb auf `entwurf` zurückgesetzt — mit der alten Begründung in
`ablehnungsgrund_alt` und einer Wiedervorlagenotiz, die ausdrücklich verlangt, G3 und G6
einzeln zu prüfen. Der Fit-Filter hat sie erneut beurteilt und **abgelehnt, aber an einer
anderen Grenze**:

> „G6 — ein Agent handelt unbeaufsichtigt im Rechnungsausgang des Kunden, und der
> schlimmste Einzelfehler ist groß. Die alte Ablehnung trägt nach der Änderung vom
> 2026-08-31 tatsächlich nicht mehr: Eine Feldzuordnung aus einem Beispielexport
> herzuleiten […] ist Agentenarbeit und kostet keine Betreiberzeit — G4 ist kein Treffer
> mehr. **Genau dadurch fällt die Idee aber in den zweiten Weg zu G6, den dieselbe
> Änderung eingeführt hat.** […] Eine falsch hergeleitete Zuordnung wirkt nicht auf eine
> Rechnung, sondern auf jede Rechnung desselben Laufs […]; bei 200 Rechnungen im Monat
> ist der zehnte falsche Vorgang im selben Lauf erreicht. Ein falsch übernommener
> Steuersatz erzeugt einen unrichtigen Steuerausweis, den der Aussteller nach § 14c UStG
> schuldet."

Drei Dinge daran sind bemerkenswert, und sie zusammen sind der Beleg, dass die Lockerung
trägt statt bloß zu lockern:

1. **Die alte Ablehnung wurde ausdrücklich aufgehoben**, nicht umgangen. G4 ist kein
   Treffer mehr, und der Filter sagt das hin.
2. **Die neue G6-Klausel hat sofort gegriffen** — und zwar mit einem Mechanismus, den
   niemand vorgegeben hatte: § 14c UStG, unrichtiger Steuerausweis, geschuldet vom
   Aussteller.
3. **G3 wurde einzeln geprüft und verworfen.** Die alte Ablehnung hatte behauptet, die
   monatliche Terminkritik berühre zusätzlich G3; der Filter widerspricht: „Der Entwurf
   sagt keine Reaktionszeit zu, ein Rechnungslauf ist termin-, aber nicht stundenkritisch."
   Damit ist auch die Einschätzung korrigiert, die dieser ADR vor der Probe enthielt.

Den einzigen Ausweg benennt er selbst und entwertet ihn im selben Satz: Ein Zuschnitt, in
dem der Kunde jede Datei vor dem Versand freigibt, hätte keinen unbeaufsichtigten Agenten
— „ob das noch verkäuflich ist, ist offen; bei 200 Rechnungen im Monat ist gerade der
ausbleibende Blick der Kaufgrund." Das ist die Spannung, in der jede Idee dieser Art
steht, und sie ist jetzt benannt.

## Was ausdrücklich nicht gelockert wird

- **G3** bleibt. Ein Agent kann zwar schneller antworten als ein Mensch, aber die Ideen,
  die daran starben, starben an Vertrauen und Terminen, nicht an Reaktionszeit.
- **G5** bleibt. Ein Agent erwirbt keine Erlaubnis und ersetzt keine.
- **G6** wird schärfer, nicht weicher — siehe oben.
- **Hausregel 2** bleibt unberührt und ist etwas anderes: Sie verbietet den *Agenten
  dieser Fabrik*, nach außen zu schreiben. Sie sagt nichts darüber, was ein *Produkt*
  tun darf. Diese beiden Ebenen wurden schon einmal verwechselt (Logbuch des Ideators
  zum Zahlungsstrom, 2026-08-30); sie sind zu trennen.

## Nachweis

`grenzen.md` wird nach jeder Änderung gegen die zwei Eichideen geprüft
(`einrichtung/eichen.sh`, ADR 0006). 9001 muss `kandidat` bleiben, 9002 muss an G5
sterben. Eine Lockerung, die 9002 durchlässt, ist zu weit gegangen.
