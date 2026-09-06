---
id: 0141-pruefliste-fuenftes-land
rolle: architekt
status: fertig
abnahme_befund: befunde/pruefung-0141-pruefliste-fuenftes-land-2026-09-06.md (urteil geprueft, entwurf-pruefer, 2026-09-06)
haengt_an: [0116-laenderzahl-als-parameter, 0117-geschaetzter-politikpfad-und-zwei-laenderklassen]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die zwei Bedingungen unter "Abnahme".
---

# Herkunft — 2026-09-05, Projektmanager: aus 0116 herausgeschnitten

Dieses Paket ist nicht neu erfunden. Es war Punkt 3 von `0116-laenderzahl-als-parameter`
und ist am 2026-09-05 herausgenommen worden, weil 0116 dreimal zugewiesen wurde und
null Byte lieferte. Die Messung steht dort im Vermerk. Vier Lieferungen auf der größten
Datei des Vorhabens waren zu viel für einen Lauf; die Regel dahinter ist
*ein Paket, ein Agent, ein Lauf*.

**Warum genau an dieser Stelle geschnitten:** 0116 sagt selbst, wofür die Prüfliste die
Voraussetzung ist — für die Auswahl eines fünften Landes, also `0118`. Die anderen beiden
Lieferungen von 0116 (Ableitungskette, Identitätsfrage) tragen `0117`. Der Schnitt folgt
damit der Abhängigkeitskette, die schon im Rückstand steht, und nicht meiner Bequemlichkeit.

**`haengt_an: [0116]` ist eine Reihenfolgesperre, keine fachliche Abhängigkeit.** Du
brauchst von 0116 inhaltlich nichts. Ihr teilt euch `technik.md`, und zwei Pakete auf einer
Datei laufen nie zusammen. Dein Vorher-Stand ist der dann geltende `HEAD`; **such am Text,
nicht an der Zeilennummer.**

# Was ein fünftes Land an Daten mitbringen muss

Du schreibst **keinen Code** und wählst **kein Land aus**. Du ergänzt `technik.md` um eine
Liste, die jemand abarbeiten kann, ohne die Spezifikation neu zu lesen.

## Was schon feststeht

Aus 0116, dort am 2026-09-05 nachgemessen und hier nicht neu zu erheben:

- `daten/reihen.toml` hält 19 Reihen; mehrere tragen `unklar`, weil ihre Quelle Dritte
  nennt. Von den acht Stellen der vier Modellländer (je Amt und Notenbank) ist genau eine
  geprüft (Destatis), sieben sind offen.
- Ein fünftes Land bringt **zwei weitere solche Stellen** mit.
- Dazu je Land: drei WDI-Sektorreihen, Bevölkerung, Erwerbstätige, Produktivität,
  Preisniveau, Leitzins, Wechselkurs, Staatsschuld, Haushaltssaldo — jede mit Deckung über
  das Fenster ab 2001 — sowie eine BACI-Handelszeile gegen jedes andere Gebiet.
- **Der Leitzins ist der bekannte Problemfall.** Der eingebettete IWF-Code führt
  Deutschland und China schon heute nicht.

## Was zu tun ist

1. **Die Liste je Datenreihe.** Eine Zeile je Reihe, die ein fünftes Land mitbringen muss,
   mit Quelle, benötigtem Fenster und Lizenzstand.
2. **Der Leitzinsfall ausdrücklich.** Nenne, wie mit Ländern zu verfahren ist, die der
   eingebettete IWF-Code nicht führt — er führt schon zwei der heutigen vier nicht. Ob
   Ersatzquelle, Ersatzverfahren oder Ausschlusskriterium: **triff die Wahl und begründe
   sie**, offenlassen ist keine Lieferung.

**Was nicht dazugehört:** ein fünftes Land auswählen (das ist `0118`), die Länderzahl
ändern, Daten laden, eine Lizenz bewerten. Du beschreibst den Aufwand, du treibst ihn nicht.

**Wenn dich etwas aufhält** — ein Widerspruch in der Vorgabe, eine Zahl, die du nicht
belegen kannst, die Größe der Datei —, dann liefere nichts und **schreib es in dein Logbuch
und in dieses Paket.** Ein gemeldetes Hindernis ist eine Lieferung; ein stummer Lauf ist
keine.

## Abnahme

1. **Die Liste ist abzählbar.** `technik.md` führt je Datenreihe, die ein fünftes Land
   mitbringen muss, eine Zeile mit Quelle, benötigtem Fenster und Lizenzstand. Für den
   Leitzins steht dort, wie mit Ländern zu verfahren ist, die der eingebettete IWF-Code
   nicht führt, und die Wahl ist begründet.
2. **Der Bestand bleibt unberührt.** In `technik.md` stehen die Zahl 310 und die Aussage
   „vier Länder" nach deinem Lauf so oft wie davor — `grep -c` gegen den Stand, den du beim
   Start vorgefunden hast. Dieses Paket beschreibt, es ändert nicht.

## Vermerk des Architekten — 2026-09-06

Geliefert als **Abschnitt 21** von `technik.md`, Vorgaben **T62** (Liste) und **T63**
(Leitzins). Reiner Anhang: `git diff --numstat` sagt `229 0`, also keine geänderte
Bestandszeile. Bedingung 2 nachgemessen, vorher wie nachher: 44 und 7 Zeilen.

**Ein Widerspruch in der Vorgabe, aufgehalten hat er nicht.** Der Auftrag nennt „Deckung über
das Fenster ab 2001"; `technik.md` führt durchgehend den Prüfjahrgang 1997–2021. Beides ist
belegt — `reihen.toml` misst für Reihe 11 den ersten US-Wert 2001 und urteilt „erzwingt das
Startjahr 2001". Die Wahl gehört nach T24 dem Spielentwerfer, nicht mir. Ich habe die Liste
deshalb parametrisch in `R` geschrieben und jede Zahl für beide Lesarten angegeben, statt eine
zu wählen.

**Zwei Stellen, an denen ich mehr geliefert habe als die Abnahme verlangt** — der Prüfer soll
es wissen und darf es für Übergriff halten: (1) Die Fensterangabe je Reihe folgt aus der
**Rolle** der Reihe, nicht aus einer einheitlichen Vorgabe; daraus fällt der Unterschied
zwischen Spielland (158 Werte) und Rückvergleichsland (806) heraus, den der Auftrag nicht
verlangt hat. (2) Die Spalte „bewegt ein weiteres Land das Urteil?" ist neu; sie zeigt, dass
nur die Reihen 1, 2 und 5 überhaupt betroffen sind und dass **Reihe 2** — nicht der Leitzins —
das einzige harte Ausschlusskriterium für ein Rückvergleichsland ist.

# Rückläufe

0.
