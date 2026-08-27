---
nr: 0001
titel: Agentenfabrik als Betriebsform, Gates als einzige menschliche Schnittstelle
datum: 2026-08-27
status: gueltig
ersetzt_durch: null
betrifft: [architektur, recht, betrieb]
---

# ADR 0001 — Grundentscheidungen

## Kontext

Ziel ist ein nebenberufliches IT-Unternehmen in Deutschland, betrieben neben einer
Vollzeitstelle als IT-Problem Manager bei einem Finanzdienstleister. Verfügbar sind rund
zwei Stunden pro Woche und ein Claude-Max-Abo. Eine Geschäftsidee existiert noch nicht —
die Maschine soll sie mit hervorbringen.

Der Arbeitsvertrag enthält einen Genehmigungsvorbehalt für Nebentätigkeiten. Der Antrag
soll erst gestellt werden, wenn absehbar ist, dass Einnahmen entstehen.

## Entscheidung

1. **Zwei getrennte Token-Ökonomien.** Das Max-Abo betreibt ausschließlich die interne
   Produktion (Recherche, Konzeption, Code, Reviews). Alles, was ein Kunde auslöst, läuft
   über die Anthropic API mit kommerziellen Konditionen und wird in die Stückkosten
   eingerechnet.
2. **Das Repo ist das Gedächtnis.** Agenten sind zustandslos; jeder Lauf endet in einem
   Commit. Rollen werden über Lese- und Schreibrechte auf Verzeichnisse definiert, nicht
   über Persönlichkeitsbeschreibungen.
3. **Vier Gates als einzige menschliche Schnittstelle.** Ausarbeitung, Bau, Live, Bilanz.
   Dazwischen entscheidet die Maschine selbst und dokumentiert. Alles mit Rechtsfolge,
   Geldfluss oder Außenwirkung ist ein Gate.
4. **WIP-Limit drei aktiv, eines im Bau.** Hart durchgesetzt, auch gegen bessere Ideen.
5. **Der Genehmigungsantrag entsteht in der Konzeption und wird nach Gate 2 gestellt** —
   nicht nach Gate 3. Gebaut wird, während er im Umlauf ist.

## Begründung

Zu 1: Ein Consumer-Abo als Produktions-Backend für Kundenlast verbindet drei Risiken —
Nutzungsbedingungen, Rate Limits als einziger Ausfallpunkt und nicht kalkulierbare
Stückkosten. Die Trennung kostet nichts, solange sie von Anfang an besteht, und ist später
nur noch mit einem Umbau nachzuholen.

Zu 2: Der eigentliche Engpass ist nicht die Tokenmenge, sondern die Lesezeit des
Betreibers. Ein durchsuchbares, versioniertes Repo mit klaren Schreibrechten erlaubt es,
den Zustand über `git log` zu erfassen, statt Dateien zu sichten.

Zu 3: Zwei Stunden pro Woche lassen sich nur einhalten, wenn die Zahl der
Entscheidungspunkte von vornherein begrenzt ist. Vier Gates ergeben etwa zwei Stunden
pro Monat plus einen kurzen wöchentlichen Digest.

Zu 5: Wird der Antrag erst nach Fertigstellung gestellt, wartet ein fertiges Produkt auf
die Bearbeitung, und eine Ablehnung entwertet die gesamte Bau- und Konzeptionsarbeit. Nach
Gate 2 steht bereits fest, was beantragt wird, während der Aufwand noch gering ist.

## Verworfene Alternativen

- **Kundenlast über das Max-Abo** — verworfen wegen Nutzungsbedingungen, Rate Limits und
  fehlender Stückkostenrechnung.
- **Dienstleistungs- oder Agenturmodell** — verworfen, weil Kundenkommunikation nicht
  delegierbar ist und das Zeitbudget sprengt. Als Grenze G3 festgeschrieben.
- **UG oder GmbH zum Start** — verworfen; laufende Buchhaltungspflichten kosten genau die
  Zeit, die knapp ist. Einzelunternehmen mit Kleinunternehmerregelung bis zur
  Umsatzrelevanz.
- **Genehmigungsantrag vor der Ideenfindung** — verworfen, weil ohne konkretes Vorhaben
  nicht beantragbar und weil Phase 0 bis 2 ohne Gewerbe, Außenauftritt und Kunden in der
  Regel noch keine Nebentätigkeit im Sinne der Klausel darstellen.

## Folgen

- Die Stückkostenrechnung jeder Idee muss API-Kosten enthalten; der Ökonom rechnet nach
  Steuern, nicht auf Bruttoumsatz.
- Das WIP-Limit wird regelmäßig unangenehm sein: Gute Ideen warten oder sterben, obwohl
  Kapazität in Tokens vorhanden wäre. Das ist beabsichtigt — der knappe Faktor ist
  Aufmerksamkeit, nicht Rechenzeit.
- Die Fabrik selbst darf nicht zum Projekt werden. Vor dem ersten Euro wird sie nicht über
  die in der Startsequenz beschriebenen fünf Stufen hinaus ausgebaut.
- Der genaue Wortlaut der Nebentätigkeitsklausel ist noch zu prüfen, insbesondere ob sie
  auch unentgeltliche Tätigkeit erfasst. Bis dahin gilt die engere Auslegung.
