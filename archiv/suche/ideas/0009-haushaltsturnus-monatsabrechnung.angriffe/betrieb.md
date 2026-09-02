---
linse: betrieb
idee: 0009-haushaltsturnus-monatsabrechnung
datum: 2026-08-28
urteil: widerlegt
schwerster_einwand: Der Dienst verspricht die Rechnung über das, was stattgefunden hat, hat dafür aber keinen Sensor — er wird von genau der Person gefüttert, deren Vergesslichkeit er heilen soll, und produziert damit entweder falsche Rechnungen an Privathaushalte oder muss zum Feldsystem für rund 200 Reinigungskräfte werden, womit der Support an der Zahl der Kräfte hängt statt an der Zahl der Kunden.
stunden_pro_woche: 3,5 bei 40 Betrieben; rund 6,5 bei 100; im Abschlussfenster vom 1. bis 5. sechs bis acht Stunden in drei Tagen
---

## Der Einwand

Die Idee benennt in ihren offenen Fragen selbst die Sonderfälle des Turnus (Feiertage,
Urlaub, Sommerpause) als G4-Risiko und meint, damit an 0004 vorbeigekommen zu sein. Sie
ist es nicht, und der Grund liegt eine Ebene tiefer als der Kalender.

### 1. Der Dienst hat keinen Sensor

Das Wertversprechen ist ausdrücklich nicht gesparte Verwaltungszeit — die Idee rechnet
das in G7 selbst weg (2,6 bis 8 % Verwaltungsanteil, ein einstelliger Eurobetrag im
Monat). Das Versprechen ist die *richtige* Rechnung: „vier oder fünf Termine je nach
Kalender, abzüglich abgesagter und zuzüglich nachgeholter Einsätze".

Die Solltermine kann der Dienst erzeugen. Die Absagen und Nachholtermine kann er nicht.
Die entstehen laut der eigenen Recherche über „Excel, WhatsApp, Zettel, Telefon"
(`research/2026-08-28-…-reinigungsfirmen.md`, Abschnitt 4, Notlösung 2) — und sie gehen
oft gar nicht an den Inhaber, sondern direkt an die Reinigungskraft, die vor der
verschlossenen Tür steht oder abends eine Nachricht bekommt.

Damit gibt es genau zwei Bauformen, und beide fallen unter G4:

**(a) Der Inhaber pflegt nach.** Dann ist der Dienst ein zweiter Datenbestand neben
Kalender, WhatsApp und Kopf, und er driftet. Eine vergessene Absage erzeugt keine
fehlende Rechnung, sondern eine **zu hohe Rechnung an einen Privathaushalt** — schlechter
als der Status quo, in dem der Inhaber einen Pauschalbetrag stellt oder gar nichts. Jede
Drift ist ein Supportfall, und Drift ist bei 42 Haushalten je Betrieb kein Sonderfall,
sondern der Regelfall.

**(b) Der Dienst wird zum Feldsystem.** Dann meldet die Kraft den Einsatz selbst — und
der Betreiber hat bei 40 Betrieben rund 200 Endnutzer, die nicht zahlen, häufig wechseln,
oft ein altes Telefon und teils eine Sprachbarriere haben. Genau das ist die Bedingung
„jeder neue Kunde erzeugt Arbeit", nur multipliziert mit der Personalstärke. Zusätzlich
liegt das dann im Zuschnitt von 0010.

Es gibt keine dritte Form. Wer die Abrechnung nach tatsächlichen Terminen verkauft,
verkauft eine Behauptung über die Wirklichkeit und braucht jemanden, der sie einträgt.

### 2. Der variable Betrag zerstört den einfachen Zahlweg

Das ist der Punkt, den ich in den Aufzählungen meines Auftrags nicht gefunden habe und
der die Idee betrieblich am teuersten macht.

Genau das Merkmal, das die Idee vom „gleichbleibenden Abobetrag" abgrenzt — der
schwankende Monatsbetrag —, macht den Dauerauftrag unmöglich, mit dem ein Privathaushalt
heute zahlt. Ein wöchentlicher Turnus liefert je nach Monat vier oder fünf Termine, also
Beträge, die um 25 % schwanken. Übrig bleiben zwei Wege, beide teuer:

- **SEPA-Lastschrift.** Dann braucht jeder Haushalt ein Mandat, eine Gläubiger-ID beim
  Betrieb, eine Vorabankündigung vor jedem Einzug und ein Rücklastschrift-Verfahren. Der
  Dienst löst dann Geldflüsse aus. *Ungeprüft, aber der Größenordnung nach sicher:* eine
  Rücklastschrift kostet Gebühr und Nacharbeit, und ein falscher Einzug bei einer
  Privatperson ist ein Vorgang mit Außenwirkung, kein Softwarefehler.
- **Überweisung.** Dann muss der Dienst Zahlungseingänge abgleichen — die Idee sagt das
  selbst („3 Haushalte ohne Zahlungseingang seit 21 Tagen"). Das heißt Bankzugriff je
  Betrieb, also eine PSD2-Schnittstelle mit periodischer Neu-Zustimmung durch den Kunden.
  *Vermutung, unbelegt:* diese Zustimmung läuft in Monatsabständen ab. Sicher ist der
  Effekt: sie läuft **still** ab. Der Abgleich hört auf zu arbeiten, ohne auszufallen, und
  das Ergebnis ist eine Mahnung an einen Haushalt, der längst gezahlt hat.

Die Idee hat diesen Kostenblock nicht im Zuschnitt. Er ist nicht optional — ohne ihn ist
die Rechnung erzeugt, aber nicht kassiert, und dann hat der Betrieb nichts gewonnen.

### 3. Der Fehler fällt erst nach anderthalb Jahren auf, und dann bei allen

Der getrennt ausgewiesene Arbeitskostenanteil ist der Grund, warum der Haushalt die
Rechnung überhaupt will. Ist er systematisch falsch berechnet — falscher Prozentsatz,
falscher Monat, doppelt gezählter Nachholtermin —, merkt das niemand beim Versand. Es
merkt der Haushalt beim Erstellen seiner Steuererklärung, also **14 bis 20 Monate
später**, und weil Steuererklärungen sich im Frühjahr ballen, merken es viele gleichzeitig.
Der Betrieb bekommt dann Korrekturwünsche für ein abgeschlossenes Jahr über einen
Rechnungsbestand, den er längst dem Steuerberater gegeben hat.

Dasselbe gilt für die Rechnungsnummer. Sie muss je Betrieb fortlaufend und lückenlos
sein. Ein Wiederholungslauf nach einem Abbruch, der eine Nummer doppelt vergibt oder eine
Lücke reißt, ist kein Bug, den man einspielt — es ist ein Buchführungsmangel im Bestand
des Kunden, den der Betreiber nicht selbst reparieren darf und der bei jedem betroffenen
Betrieb einzeln aufgeräumt werden muss.

### 4. Das Abschlussfenster ist hier kein Zufall, sondern der Produktkern

Bei 0005 war die monatliche Ballung ein Nebeneffekt der Lohnabrechnung. Hier **ist** sie
das Produkt: „Monatsabrechnung". Alle Kunden brauchen denselben Dienst in denselben drei
Tagen. Ein Ausfall am 1. trifft nie einen Kunden, sondern alle. Und die tolerierbare
Reaktionszeit ist in diesen Tagen strukturell unter 24 Stunden, weil hinter jedem Kunden
42 Privathaushalte stehen, die bereits anrufen — G3 wird dabei nicht formal verletzt, aber
faktisch erwartet.

Dazu ein konkreter, jährlich wiederkehrender Fall: Ein 14-täglicher Turnus wird im
Sprachgebrauch der Branche über gerade und ungerade Kalenderwochen geführt. **2026 hat 53
ISO-Kalenderwochen** (eigene Rechnung: der 1.1.2026 ist ein Donnerstag), auf KW 53 folgt
KW 1 — zwei ungerade Wochen hintereinander. Zum Jahreswechsel verschiebt sich damit jeder
14-Tage-Haushalt jedes Kunden gleichzeitig, entweder um einen doppelten Termin oder um
eine Vier-Wochen-Lücke. Der Zeitpunkt ist der denkbar schlechteste: Dezemberrechnung,
Feiertage, Betreiber nicht da.

### 5. Die Zeitrechnung

Bei 40 Betrieben zu rund 35 EUR ARPU (der Wert, den die Recherche in Abschnitt 3
vorgibt): 1.400 EUR brutto im Monat, nach Grenzsteuersatz grob 780 EUR netto. Alle Werte
sind Schätzungen, bewusst nicht optimistisch.

| Posten | Annahme | pro Woche |
|---|---|---|
| Strittige Rechnungen | 1.680 Rechnungen/Monat, 0,5 % strittig = 8, davon 4 beim Betreiber à 20 min | 20 min |
| Zahlungsabgleich, Bankzugang, abgelaufene Zustimmungen | je Betrieb 1× im Halbjahr = 7/Monat à 10 min | 16 min |
| Abschlussfenster überwachen, Nachläufe, Stornos | 3 Tage im Monat à 40 min | 30 min |
| Einrichtung neuer Betriebe, rein schriftlich | 42 Haushalte je Betrieb, kein Importweg; 2 Neukunden/Monat à 2 h | 60 min |
| Turnus-Sonderfälle, Feiertagskalender, Jahreswechsel | 20 min/Woche plus 6 h im Jahr | 30 min |
| Zustellbarkeit, Bounces, Spam-Beschwerden | 40 Absenderidentitäten auf einer Infrastruktur | 15 min |
| Buchhaltung, eigene Rechnungen, AV-Verträge, Auskünfte | | 30 min |
| **Summe** | | **rund 3,4 h** |

Vier der sieben Zeilen (20+16+60+15 = 111 min) wachsen linear mit der Kundenzahl. Bei 100
Betrieben sind allein sie bei 4,6 Stunden, mit dem Rest bei rund 6,5. Die Grenze liegt bei
zwei — und dieser Zustand ist erreicht, *bevor* der erste ernste Fehler passiert.

**Was nicht das Problem ist, der Fairness halber.** Modellkosten je Vorgang gibt es
praktisch nicht: Turnus zu Terminen zu Rechnung ist Arithmetik, kein Modellaufruf. G7
stirbt hier nicht an Tokens. Auch die Gestaltungsfrage ist ehrlich klein — eine
Rechnungsvorlage, danach jährlich. G4 stirbt hier.

## Was ihn entkräften würde

In dieser Reihenfolge, jede Zeile schneidet Umfang weg:

1. **Umkehrung der Eingabe: Der Dienst nimmt an, dass jeder Solltermin stattgefunden
   hat, und lässt sich nur *Abweichungen* melden — per Antwort auf eine Nachricht, ohne
   Anmeldung, ohne App.** Das ist der einzige Weg, bei dem das Nichtstun des Kunden zum
   richtigen Ergebnis führt statt zum falschen. Der Preis: Der Dienst kann nicht mehr
   versprechen, richtig zu sein, sondern nur, vollständig zu *fragen*.
2. **Kein Geld anfassen.** Kein Lastschrifteinzug, kein Bankzugang, kein Mahnwesen. Der
   Dienst erzeugt Rechnungen und gibt sie ab; ob gezahlt wurde, weiß der Betrieb. Damit
   fällt Zeile 2 der Tabelle weg und der halbe Haftungsraum. Der Preis: Die Übersichts-
   zeile aus der Idee („3 Haushalte ohne Zahlungseingang") ist dann nicht baubar, und
   ExtraSauber wirbt genau damit („Vollautomatische Erfassung aller Zahlungseingänge").
3. **Genau eine Turnusform: fester Wochentag, wöchentlich oder 14-täglich, Anker als
   Datum und nicht als Kalenderwoche.** Alles andere wird abgelehnt statt konfiguriert.
   Damit verschwindet der 53-Wochen-Fall und der Regelsatz je Kunde.
4. **Selbstbedienungs-Einrichtung mit einer Tabellenzeile je Haushalt, ohne Import aus
   Fremdsystemen und ohne Mithilfe.** Wer sie nicht ausfüllt, wird nicht Kunde. Sonst ist
   Zeile 4 der Tabelle nicht zu halten — und die Kategorie erwartet laut Recherche
   ohnehin eine persönliche Einführung, die G3 verbietet.
5. **Der Arbeitskostenanteil ist ein Feld, das der Betrieb setzt, und wird ohne jeden
   steuerlichen Begriff ausgegeben.** Nicht wegen G5 — das ist die Linse Recht —, sondern
   weil jeder erklärende Satz auf der Rechnung eine Rückfrage eines Privathaushalts
   erzeugt, die beim Betreiber landet.

Auch mit allen fünf Schnitten bleibe ich über zwei Stunden, weil die Einrichtung je
Kunde 42 Datensätze verlangt und das Abschlussfenster nicht wegzuschneiden ist. Punkt 1
und 2 machen die Idee überhaupt erst diskutabel — kosten aber genau das Merkmal, mit dem
sie sich vom bestehenden Aborechnungs-Angebot abgrenzt.

## Der schlimmste Tag

Donnerstag, der 2. April, 9:20 Uhr. Der Betreiber ist in der Eskalationsrunde zu einer
Kernbanken-Störung und kommt vor 18 Uhr an nichts.

In der Nacht ist der Monatsabschluss für März gelaufen. Der März hatte fünf Dienstage;
ein Umstellungsfehler bei der Sommerzeit hat den Termin vom 29. März auf den 30. gelegt
und in zwei Monaten gleichzeitig gezählt. 1.680 Rechnungen sind raus, rund 300 davon mit
einem Termin zu viel. Betroffen sind nicht 40 Kunden, sondern rund 300 Privathaushalte,
die alle bei ihrem Reinigungsbetrieb anrufen — nicht beim Betreiber. Der Betrieb hat
keinen Knopf für „alles zurück", denn die Nummern sind vergeben; er braucht 300 Stornos
und 300 neue Rechnungen, und er weiß nicht, welche.

Um 12:30 liegen elf Mails da, drei davon von Betrieben, die den Abgleich aktiv haben und
deren automatischer Mahnlauf in neun Tagen über die falschen Beträge geht. Ein Betrieb
hat bereits alle 42 Haushalte per WhatsApp gewarnt und dabei den Namen des Dienstes
genannt.

Die technische Reparatur ist ein Nachmittag. Die betriebliche ist es nicht: Der Betreiber
darf die Bücher seiner Kunden nicht selbst anfassen, muss also jedem Betrieb einzeln eine
Storno- und Neuausgabe-Anleitung schreiben und die Rückfragen dazu beantworten — vierzig
Mal, in derselben Woche, abends. Der Rest schleppt sich: Ein Teil der falschen Beträge
läuft trotzdem durch, taucht als zu hoher Arbeitskostenanteil in den Bescheinigungen des
Jahres auf und kommt im **Frühjahr des Folgejahres** wieder, als Korrekturwunsch für ein
Jahr, dessen Bücher zu sind.

Das ist kein unwahrscheinlicher Tag. Es ist die absehbare Folge davon, dass ein einzelner
Rechenfehler gleichzeitig bei allen Kunden gegen Endverbraucher wirkt, dass die Korrektur
in fremden Büchern stattfinden muss und dass der Betreiber am 2. eines Monats
Vollzeitangestellter ist.
