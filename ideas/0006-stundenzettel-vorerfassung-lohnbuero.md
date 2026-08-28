---
id: 0006-stundenzettel-vorerfassung-lohnbuero
titel: Vorerfassung eingereichter Papier-Stundenzettel für Lohnbüros
status: entwurf
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: ideator

quelle: signals/pain/2026-08-28-stundenzettel-abendliche-uebertragung.md

segment: Lohnbüros und Steuerkanzleien mit eigener Lohnabteilung, die Bau- und Handwerksmandanten betreuen und deren Stunden Monat für Monat als eingescannte oder abfotografierte Papierzettel bekommen — typisch Kanzleien mit 200 bis 2.000 Abrechnungen im Monat, bei denen die Erfassung an angelernte Kräfte geht.
problem: Derselbe Zettel, der den Handwerksbetrieb abends kostet, kostet das Lohnbüro am Monatsanfang ein zweites Mal: Er wird dort erneut abgetippt, weil er als Bild ankommt. Anders als beim Betrieb ist der Aufwand hier gebündelt, wiederkehrend und in Personalstunden bezifferbar.
loesung: Ein Dienst, der die eingereichten Zettelbilder eines Mandanten zu einer geprüften Erfassungsdatei je Mandant und Monat macht, die die Lohnkraft nur noch sichtet und einliest — die Kanzlei behält Prüfung, Verantwortung und Mandantenkontakt vollständig.
zahlungsgrund: nutzen

ablehnungsgrund: null

score:
  zwang: null
  erreichbar: null
  ruhe: null
  marge: null
  genehmigung: null
  summe: null
---

## Belege

- Handwerksbetriebe erfassen Stunden und Material auf der Baustelle handschriftlich, weil das vor Ort am schnellsten geht; das Übertragen fällt hinterher an. — elektromeisterforum.de, Nutzer „Mask", abgerufen 2026-08-28, erfasst in `signals/pain/2026-08-28-stundenzettel-abendliche-uebertragung.md`
- Die Übertragung ist fehleranfällig: „Da können schnell Stunden oder Materialpositionen vergessen werden." — dieselbe Quelle, abgerufen 2026-08-28
- **Vermutung, ungeprueft und zentral:** Dass Lohnbüros die Stunden ihrer Handwerksmandanten in nennenswertem Umfang als Bild oder Papier bekommen und dort abtippen. Das Signal beschreibt ausschließlich die Betriebsseite; die Kanzleiseite ist eine Ableitung des Ideators, keine Beobachtung. Fällt sie, fällt die Idee.
- **Vermutung, ungeprueft:** Dass der Erfassungsaufwand je Kanzlei groß genug ist, um über einer Personalstunde je Monat und Mandant zu liegen. Ohne diese Größenordnung gibt es keinen Kaufanlass.
- **Vermutung, ungeprueft:** Erkennungsquote bei handschriftlichen Zetteln. Siehe die gleichlautende offene Frage in `ideas/0005-zettelfoto-in-stundenzeile.md`; beide Ideen stehen und fallen mit derselben technischen Annahme.

## Offene Fragen

- **Zuerst zu klären, weil die ganze Idee daran hängt:** Trifft die Ableitung zu? Ein einziger belegter Beitrag einer Lohnkraft oder Kanzlei, die das Abtippen eingereichter Zettel als Aufwand benennt, würde reichen; findet sich keiner, ist die Idee unbegründet und gehört zurückgezogen.
- **G5, ernst zu nehmen:** Der Dienst erfasst Daten, die in eine Lohnabrechnung fließen. Laufende Lohnabrechnung für fremde Arbeitgeber ist Hilfeleistung in Steuersachen und nur im Rahmen des § 6 Nr. 4 StBerG zulässig (belegt in `research/2026-08-28-elstam-private-kv-pv-beitraege.md`, Punkt 5, abgerufen 2026-08-28). Der Entwurf umgeht das bewusst, indem der Kunde die Kanzlei ist und der Dienst nur Bild zu Text macht, ohne zu rechnen, zu bewerten oder abzurechnen. Ob diese Abgrenzung trägt, ist ungeprüft — und das Muster „die Abgrenzung trägt vermutlich nicht" hat bereits Idee 0003 erledigt.
- **G3:** Kanzleien sind ein Kundenkreis mit Rückfragen, Terminen und Einführungsgesprächen. Lässt sich der Dienst als reine Selbstbedienung betreiben, oder verlangt jeder neue Kanzleikunde ein Gespräch? Fällt die Antwort ungünstig aus, ist die Idee unabhängig von allem anderen tot.
- **Datenschutz:** Verarbeitet werden Arbeitszeiten namentlich benannter Beschäftigter — personenbezogene Daten Dritter im Auftrag der Kanzlei, die ihrerseits im Auftrag des Mandanten handelt. Auftragsverarbeitung über zwei Stufen, dazu die Berufsverschwiegenheit nach § 203 StGB. Was das an Vertragswerk und Nachweisen verlangt, ist nicht geprüft.
- **G4:** Bringt jeder Mandant ein eigenes Zettelformular mit, hat die Kanzlei zwanzig Formulare statt einem. Ob die Erkennung formularunabhängig funktioniert, ist dieselbe offene Frage wie in 0005 — hier aber verschärft, weil sich die Formularvielfalt je Kunde multipliziert.
- **G7:** Was ist eine Kanzlei je Mandant und Monat zu zahlen bereit, gemessen an der eingesparten Personalzeit? Der Preisanker liegt hier höher als bei 0005, weil eine Kanzlei mit Stundensätzen rechnet und nicht mit Feierabendstunden.
- Erreichbarkeit: Kanzleien sind über Fachpresse, Softwarehäuser und Verbände sichtbar, aber ihr Beschaffungsweg läuft üblicherweise über den vorhandenen Softwareanbieter. Gibt es einen Zugang ohne Kaltakquise?

## Warum jetzt

Wie bei `ideas/0005-zettelfoto-in-stundenzeile.md` ist die Änderung technisch: Erst seit multimodale Modelle handschriftliche Belege ohne Vorlage lesen, lässt sich diese Arbeit überhaupt maschinell anfassen; vorher wäre je Mandantenformular ein Anlernen nötig gewesen, und genau daran scheitern Werkzeuge in Kanzleien seit Jahren.

Der zweite Punkt ist ehrlich schwächer und ausdrücklich als Vermutung markiert: Der Fachkräftemangel in Lohnabteilungen erhöht den Wert einer eingesparten Erfassungsstunde. Dafür liegt in diesem Repo kein Beleg vor.

Was dagegen spricht und hier hingehört: Dies ist derselbe Kern wie 0005 mit einem anderen Käufer. Bewahrheitet sich, dass die Kanzleiseite den Zettel gar nicht sieht, weil die Betriebe bereits digital liefern, verschwindet die Idee vollständig — während 0005 davon unberührt bliebe.
