---
linse: betrieb
idee: 0005-zettelfoto-in-stundenzeile
datum: 2026-08-28
urteil: widerlegt
schwerster_einwand: Der Dienst automatisiert nicht das Abtippen, sondern die Auslegung des Zettels — und die Auslegungsregeln (Pause, Fahrzeit, Zuschlag, Lohnart, Auftragsnummer, Importformat) sind je Betrieb verschieden und aendern sich laufend, womit der Aufwand mit der Kundenzahl waechst.
stunden_pro_woche: 3,5 bei 40 Betrieben; ueber 5 bei 100; Spitzen von 6 im monatlichen Lohnfenster
---

## Der Einwand

Die Idee weicht dem Sturz von 0004 an einer Stelle geschickt aus und laeuft an drei
anderen genau hinein.

**Ausgewichen ist sie auf der Eingabeseite.** Die Frage aus dem Entwurf („bringt jeder
Betrieb sein eigenes Zettelformular mit?") ist die falsche Sorge. Formularunabhaengiges
Lesen ist genau das, was ein multimodales Modell kann; ein Zettel mit Datum, Name,
Zeiten und Materialzeilen ist auch dann lesbar, wenn er anders aussieht. Diesen Punkt
gebe ich dem Entwurf.

**Nicht ausgewichen ist sie auf der Auslegungsseite, und das ist der eigentliche
Befund.** Auf dem Zettel steht „7:00–16:30, 30 min Pause, Fahrt 45". Was daraus im
Lohn wird, steht nicht auf dem Zettel:

- Ist die Fahrzeit Arbeitszeit, bezahlte Fahrzeit zu geringerem Satz oder gar nichts?
- Wird die gesetzliche Pause abgezogen, wenn der Mitarbeiter sie nicht notiert hat?
- Welche Lohnart bekommt die Samstagsstunde, welchen Zuschlag die neunte Stunde?
- Wird auf Viertelstunden gerundet, und in welche Richtung?

Das sind keine Erkennungsfragen, das sind Betriebsregeln — aus Tarif, Arbeitsvertrag
und Gewohnheit. Sie sind der Grund, warum das abendliche Uebertragen mehr ist als
Tippen. Ein Dienst, der nur die Ziffern liefert, nimmt dem Betrieb den kleineren Teil
der Arbeit ab; ein Dienst, der die Zeile fertig macht, traegt je Kunde einen
Regelsatz, den jemand einrichtet und bei jeder Tarifrunde und jeder neuen
Betriebsvereinbarung nachzieht. Das ist die Konstellation aus G4, nur eine Ebene
tiefer als bei 0004 versteckt.

**Zweitens die Ausgabeseite.** Der Entwurf sagt „eine Datei zum Import in das System,
das der Betrieb ohnehin nutzt". Genau dort sitzt die Heterogenitaet, die bei 0004
toedlich war — nur umgezogen von der Quelle ans Ziel. Craftnote, openHandwerk,
ToolTime, 1Tool, eine gewachsene Excel-Mappe, dazu auf der Lohnseite DATEV, Lexware
oder Sage: jedes mit eigenem Importformat, eigenen Pflichtfeldern und eigenem
Versionsrhythmus. Fuenf unterstuetzte Zielsysteme sind fuenf Formate, die kaputtgehen
koennen, ohne dass der Betreiber es erfaehrt, bis ein Kunde schreibt.

**Drittens die Stammdaten, und das ist der Punkt, den man leicht uebersieht.** Auf dem
Zettel steht „Mueller" und „BV Schmidt, Kueche". Das Zielsystem will Personalnummer 47
und Auftrag 2026-0331. Diese Zuordnung ist je Betrieb eigen und **veraendert sich
woechentlich**, weil staendig neue Baustellen dazukommen. Entweder der Betrieb pflegt
sie selbst — dann ist der Dienst nur so gut wie die Pflege, und jede vergessene
Baustelle erzeugt nicht zuordenbare Zeilen — oder der Betreiber pflegt mit, und dann
skaliert Datenpflege mit der Kundenzahl. Beides ist genau die Pruefrage von G4.

**Die Zeitrechnung, bei 40 Betrieben und 49 € im Monat** (rund 2.000 € brutto, nach
Grenzsteuersatz etwa 1.100 € netto — das ist die Groessenordnung, ab der sich der
Aufwand ueberhaupt lohnen muss). Alle Werte sind Schaetzungen, bewusst nicht
optimistisch:

| Posten | Annahme | pro Woche |
|---|---|---|
| Supportfaelle | 1 je Betrieb und 2 Monate = 5/Woche à 15 min | 75 min |
| Zielsystem- und Stammdatenpflege | 1 Aenderung je Betrieb und Quartal à 20 min | 60 min |
| Onboarding bei 3 % Abwanderung | ~1,2 neue Betriebe/Monat à 1,5 h | 30 min |
| Regressionspruefung nach Modelländerung | 4 h, 4× im Jahr | 20 min |
| Buchhaltung, Rechnungen, AV-Vertraege, Auskunftsersuchen | | 30 min |
| **Summe** | | **rund 3,5 h** |

Die ersten beiden Zeilen wachsen linear mit der Kundenzahl. Bei 100 Betrieben stehen
allein sie bei rund 5,5 Stunden. Die Grenze liegt bei zwei.

**Was nicht das Problem ist — der Fairness halber.** Die Modellkosten je Vorgang
tragen. *Schaetzung, unbelegt, keine Preisliste geprueft:* ein Zettelfoto liegt bei
grob 1.500 Bild-Tokens plus rund 500 Anweisung und 600 Ausgabe, in der Groessenordnung
oeffentlicher Preise mittlerer multimodaler Modelle also bei ein bis zwei Cent. Bei
200 Zetteln im Monat sind das drei bis vier Euro je Betrieb gegen 49 € Preis. Selbst
mit Wiederholungslaeufen nach Korrektur bleibt das unkritisch. G7 stirbt hier nicht;
G4 stirbt hier.

**Und der Umkehrschluss zum Wertversprechen.** Der Entwurf legt die Freigabe bewusst
beim Betrieb: der Dienst schlaegt vor, der Betrieb bucht. Haftungsrechtlich ist das
klug. Betrieblich ist es die Falle: Muss der Meister jede Zahl gegenlesen, spart er
gegenueber dem Abtippen wenig und kuendigt. Liest er nicht gegen, ist bei jedem Fehler
der Dienst der Schuldige — nicht vor Gericht, aber im Kopf des Kunden, und dort
entsteht der Supportfall. Es gibt keine Einstellung, bei der beides gleichzeitig gut
ausgeht.

## Was ihn entkraeften wuerde

In dieser Reihenfolge, jede Zeile schneidet Umfang weg:

1. **Genau ein Zielsystem, dokumentiertes Importformat, alles andere wird abgelehnt.**
   Nicht „zunaechst eines" — dauerhaft eines. Damit hoert die Ausgabeseite auf, mit
   der Kundenzahl zu wachsen. Der Preis dafuer ist ein Segment, das um ein Vielfaches
   kleiner ist als das im Entwurf beschriebene.
2. **Keine Auslegung.** Der Dienst liefert, was auf dem Zettel steht: Rohzeiten,
   Rohmengen, Klartextnamen. Keine Pausenregel, kein Zuschlag, keine Lohnart, keine
   Rundung. Die Auslegung bleibt beim Zielsystem, das sie ohnehin kann. Damit
   verschwindet der Regelsatz je Kunde — und mit ihm ein Teil des Nutzens, der
   ehrlicherweise mitgerechnet werden muss.
3. **Stammdaten ausschliesslich per Selbstbedienung**, naechtlicher Export aus dem
   Zielsystem, nie eine Zuordnung von Hand, und nicht zuordenbare Zeilen werden
   markiert statt geraten. Kein Betreiber fasst je Kundendaten an.
4. **Erkennungsfehler sind kein Supportkanal, sondern eine Korrekturmaske.** Die
   Erkennungsquote wird offen ausgewiesen und der Preis danach gesetzt. Ein Kunde, der
   „hat falsch gelesen" schreibt, bekommt eine Textbausteinantwort und einen Knopf,
   mit dem er den Zettel selbst zur Pruefung freigibt — sonst fehlt dem Betreiber
   wegen des Loeschkonzepts ohnehin das Bild, um irgendetwas nachzusehen.
5. **Ein Regressionssatz aus eigenen, selbst geschriebenen Zetteln**, nicht aus
   Kundendaten, damit eine Modelländerung ohne Rechtsproblem und in einer Stunde
   geprueft werden kann.

Auch mit allen fuenf Schnitten bleibe ich ueber zwei Stunden, weil die Nachfrage sich
monatlich in einem Drei-Tage-Fenster ballt (siehe unten). Punkt 1 und 2 zusammen
machen die Idee aber ueberhaupt erst diskutabel — ohne sie ist sie 0004 mit besserem
Vorderteil.

**Nicht geprueft, aber betrieblich relevant:** Stundenzettel enthalten Namen und
Arbeitszeiten benannter Mitarbeiter. Der Dienst waere Auftragsverarbeiter — ein
AV-Vertrag je Betrieb, ein Loeschkonzept, ein Unterauftragsverarbeiter im Drittland,
falls das Modell dort laeuft. Das ist kein Ausschluss, aber es sind 15 Minuten
Papierkram je Neukunde und gelegentlich ein Kunde, dessen Berater den Vertrag geaendert
haben will. In Betrieben mit 3 bis 20 Mitarbeitern duerfte es meist keinen Betriebsrat
geben, dieser Faktor faellt also vermutlich weg. Die Linse Recht soll das bewerten,
ich zaehle es nur in die Zeit.

## Der schlimmste Tag

Dienstag, der 3. eines Monats, 10:40 Uhr. Der Betreiber sitzt in der Lagebesprechung
des Problem-Managements und hat das Telefon lautlos.

In der Nacht hat der Modellanbieter eine Version umgestellt. Die Erkennung laeuft
weiter, sie faellt nicht aus — sie liest nur bei Zetteln mit Dezimalkomma jetzt
gelegentlich „8,5" als „85". Kein Feld ist als unsicher markiert, denn das Modell ist
sich sicher. Genau in diesen Tagen laden alle Betriebe gleichzeitig die Zettel des
Vormonats, weil die Lohnabrechnung ansteht; das ist die Woche, in der der Dienst
seinen ganzen Wert liefert.

Bis Mittag haben elf Betriebe importiert. Zwei haben die Lohnlaeufe bereits
abgeschickt. Ein Polier bekommt statt 168 Stunden 1.680 gutgeschrieben, was auffaellt;
ein anderer bekommt statt 8,5 nur 8,0 an vier Tagen, was nicht auffaellt und in drei
Wochen als Beschwerde beim Meister landet.

Um 12:15 findet der Betreiber neun Mails, davon vier mit dem Wort „sofort" und eine
mit einer Handynummer und der Bitte um Rueckruf — den er nach G3 gar nicht anbieten
darf. Er hat die Bilder nicht, denn er loescht sie nach Verarbeitung. Er kann also
weder nachvollziehen, was falsch gelesen wurde, noch die betroffenen Zeilen bei allen
Kunden gezielt zurueckrollen; er kann nur alle 40 Betriebe warnen, ihre Importe des
laufenden Monats von Hand zu pruefen. Damit hat er allen genau die Abendarbeit
zurueckgegeben, fuer deren Wegfall sie zahlen — im schlechtestmoeglichen Moment und
mit dem Zusatz, dass sie jetzt auch noch misstrauisch sind.

Die Reparatur ist technisch klein: eine Anweisung nachschaerfen, ein Regressionssatz,
ein Tag. Die Kosten sind es nicht. Der Abend geht fuer Schadensbegrenzung drauf, der
naechste auch, und in der Woche darauf kuendigen die zwei Betriebe, die den Lohnlauf
korrigieren mussten. Das ist kein unwahrscheinlicher Tag — es ist die absehbare Folge
davon, dass ein fremdes Modell ohne Vorwarnung sein Verhalten aendert und die Nachfrage
sich auf drei Tage im Monat konzentriert.
