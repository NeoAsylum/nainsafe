---
nr: 0002
titel: Nur Produkte, deren Qualität ein Agent beurteilen kann
datum: 2026-08-28
status: ersetzt
ersetzt_durch: 0003-zustand-textuell-inspizierbar
betrifft: [ideen, architektur, betrieb]
---

# ADR 0002 — Agentenprüfbarkeit als Grenze

## Kontext

Das Unternehmen soll vollständig online laufen und **niemanden beschäftigen** — keine
Redaktion, keinen Tester, keinen Designer, auch keine Freelancer. Damit fällt die Instanz
weg, die in jedem normalen Betrieb die Qualität sichert.

Zugleich sollen Agenten das Produkt nicht nur bauen, sondern auch warten und
weiterentwickeln. Beides zusammen ergibt eine Bedingung, die bisher nirgends stand: Was
niemand prüfen kann, kann auch niemand verantworten.

Die ersten acht Ideen der Fabrik wurden allein danach beurteilt, ob sie *tragfähig* sind
— nicht danach, ob ihre Qualität ohne Menschen sicherbar ist. Bei einer davon
(Zettelfoto-Erkennung) wäre genau das der stille Killer gewesen: Ob eine Erkennung
„richtig genug" ist, beurteilt am Ende ein Mensch, der den Zettel gesehen hat.

## Entscheidung

Zwei neue Grenzen in `grenzen.md`:

**G8 — Qualität nur von Menschen beurteilbar.** Ausgeschlossen ist alles, dessen Wert im
Aussehen steckt. Die Grenze verläuft nicht zwischen „mit Oberfläche" und „ohne", sondern
danach, *wo* die Qualität sitzt: Text, Daten, Verhalten und messbare Wirkung sind
prüfbar; Layout, Illustration, Animation und Bedienungsgefühl sind es nicht. Eine
Weboberfläche ist erlaubt — sie ist Mittel, nicht Ware.

**G9 — Braucht Personal.** Ausgeschlossen ist alles, was ohne angestellte oder
beauftragte Menschen nicht läuft. Ausdrücklich erlaubt bleibt eine Plattform, auf der
*andere* einander beauftragen: Dann stellt der Betreiber niemanden ein, sondern den
Marktplatz.

Fit-Filter, Ideator und Modell-Scout prüfen beide Grenzen ab sofort mit.

## Begründung

Die Alternative wäre, Qualität stichprobenartig selbst zu prüfen. Das verletzt die
härteste Randbedingung des Repos: zwei Stunden pro Woche. Qualitätssicherung ist keine
Tätigkeit, die sich auf vier Gates im Monat eindampfen lässt — sie fällt bei jedem
Erzeugnis an, jeden Tag.

Die Grenze ist außerdem billiger, je früher sie greift. Fällt erst beim Bau auf, dass
niemand beurteilen kann, ob das Ergebnis gut ist, sind Konzeption und Implementierung
schon bezahlt.

## Verworfene Alternativen

- **Stichprobenprüfung durch den Betreiber** — verworfen, siehe Zeitbudget. Außerdem
  wächst der Prüfaufwand mit der Menge, das Zeitbudget nicht.
- **Menschliche Qualitätssicherung einkaufen** (Freelancer, Prüfdienstleister) —
  verworfen: Das ist Personalführung, und sie beginnt beim ersten Auftrag. Als G9
  festgeschrieben.
- **Visuelle Prüfung durch Modelle mit Bildverständnis** — verworfen als tragende Säule.
  Ein Modell kann ein Bild beschreiben und ein einzelnes Motiv auswählen; es kann nicht
  verlässlich beurteilen, ob ein Layout gut *wirkt*. Für einzelne Bilder in einem sonst
  textlichen Erzeugnis reicht es, als Qualitätsmaßstab eines visuellen Produkts nicht.
- **Grenze erst in der Konzeption prüfen** — verworfen, weil bis dahin bereits ein
  Rechercheur, ein Ideator, der Fit-Filter und fünf Angriffsläufe bezahlt sind.

## Folgen

- Ganze Produktklassen fallen weg: Grafik- und Designwerkzeuge, Spiele mit visuellem
  Reiz, Vorlagenmärkte, alles mit gestalterischem Kern.
- Bevorzugt werden Produkte, deren Erzeugnis sich lesen oder nachrechnen lässt:
  Auswertung, Abgleich, Dokumentation, Benachrichtigung, Terminplanung, Abrechnung,
  Textproduktion mit messbarer Wirkung.
- Jede Idee muss künftig benennen, **woran man erkennt, dass die Arbeit gut war**. Fällt
  dazu nur „sieht gut aus" ein, ist sie für diese Fabrik unbrauchbar.
- Die beiden vorliegenden Modell-Signale bleiben zulässig: Terminplanung für
  Reinigungsfirmen und Wartungsdokumentation für Poolservice haben ihren Wert in Daten
  und Verhalten, nicht im Aussehen.
- Offen bleibt, ob G8 als Grenze ausreicht oder eine sechste Angriffslinse „Prüfbarkeit"
  nötig wird. Das entscheidet sich, wenn die erste Idee die Konzeption erreicht.
