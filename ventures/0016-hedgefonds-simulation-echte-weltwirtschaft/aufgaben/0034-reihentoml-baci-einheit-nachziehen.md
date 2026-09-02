---
id: 0034-reihentoml-baci-einheit-nachziehen
rolle: datenbauer
status: vorschlag
haengt_an: [0025-quelleneinheit-pwt-baci]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Die Einheit ist gemessen, und die Datei, aus der gerechnet wird, sagt weiter ungemessen

Vorgabe: daten/einheitenbefund-pwt-baci.md, Abschnitte 1, 2, 6 und 8, abgenommen am
2026-09-02 mit befunde/pruefung-0025-quelleneinheit-pwt-baci-2026-09-02.md.

Paket 0025 hat die Quelleneinheit von BACI gemessen und dabei ausdrücklich verboten,
daten/reihen.toml anzufassen. Der Übertrag ist deshalb offen — und Abschnitt 8 des Befunds
schreibt ihn feldgenau vor.

## Die drei Stellen

**Erstens, Reihe 14, der Umrechnungsblock Z. 1266 bis 1271.** Er trägt art ungemessen,
status ungemessen und eine Frage: „In welcher Einheit und zu welchen Preisen meldet BACI
202601 den Wert eines Stroms?" Beides ist beantwortet: Das Feld v der Quelle steht in
Tausend laufenden USD, der Faktor nach Tausend USD ist 1, ausgerechnet und nicht gesetzt.

**Zweitens, Reihe 14, die beiden offen-Einträge Z. 1260 und Z. 1261.** Der erste sagt, die
Quelleneinheit sei in keiner Befunddatei gemessen; der zweite, die Preisbasis sei ebenfalls
ungemessen. Beide Sätze sind seit dem 2026-09-02 falsch. An ihre Stelle gehört die gemessene
Preisbasis — laufende Preise — als **offener Widerspruch zu T5 Klasse 2**, mit dem Adressaten
Architekt, und der Versionsvorbehalt aus Abschnitt 1 des Befunds: Gemessen ist die Einheit
der Beschreibungsseite am 2026-09-02, nicht die der Fassung 202601 im Wortlaut ihrer eigenen
Freigabemitteilung.

**Drittens, Reihe 16, der offen-Eintrag Z. 1392.** Er stellt die Frage, ob H und N in
derselben Einheit stehen. Die Antwort steht in Abschnitt 6 des Befunds: in der
Größenordnung ja, Faktor 1 zwischen beiden; in der Preisbasis nein, BACI laufend gegen WDI
konstant 2015. Der Quotient ist damit nicht bedeutungslos, aber er trägt einen Preisanteil.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0025.** Dessen dateien-Liste nennt allein die Befunddatei, und der Text des
Pakets verbietet den Zugriff auf reihen.toml ausdrücklich. Der Bauagent hat sich daran
gehalten; ein Rücklauf wäre eine Kriterienerhöhung gewesen.

**Nicht Teil von 0032**, obwohl beide dieselbe Datei anfassen. Dessen Bedingung 3 verlangt,
dass ausser drei grund-Feldern **keine** berührte Zeile im Änderungsdiff auftaucht. Wer den
Einheitenübertrag dort mitnimmt, bricht das eigene Abnahmekriterium. **Die Kollision auf
reihen.toml ist echt** — sie ist der Grund, warum dieses Paket status vorschlag trägt und
die Reihenfolge dem Projektmanager gehört.

**Nicht kosmetisch.** reihen.toml ist die Fassung, aus der weitergerechnet wird. Solange
dort art ungemessen steht, hat der Jahrgangsbau für Reihe 14 keinen Faktor, obwohl einer
gemessen ist — und die Frage an den Architekten, an der die Pakete 0026, 0002 und 0010
hängen, steht in der maschinenlesbaren Fassung gar nicht. Ein bloßer Faktor 1 ohne den Satz
zur laufenden Preisbasis wäre allerdings schlimmer als der heutige Zustand: Er behauptete
Vollständigkeit, die nicht gemessen ist. Deshalb Bedingung 2.

## Was zu tun ist

**Kein Abruf, keine Recherche, keine neue Quelle.** Alle Belege stehen in
daten/einheitenbefund-pwt-baci.md. Die Felder wortlaut, url, url_gegenprobe und abrufdatum
der Lizenzblöcke werden nicht angefasst; sie sind in den Paketen 0014, 0017 und 0022
gemessen worden.

**Reihe 3 bleibt unverändert.** Die Quelleneinheit des PWT-Kapitalstocks ist weiter
ungemessen, und art ungemessen ist dort die richtige Eintragung.

**Das Wort für art wählt der Bauagent.** Die Datei kennt bisher geteilt, basierung, keine
und ungemessen; ein Faktor 1 ohne Rechenwirkung passt auf mehrere davon. specs/ schreibt
kein Vokabular vor. Der Bauagent nennt in der Begründung, welches Wort er nimmt und warum —
das ist keine Abnahmebedingung, sondern die Vermeidung einer stillen Wahl.

## Abnahme

1. **Der Umrechnungsblock der Reihe 14 trägt einen gemessenen Faktor.** status ist nicht
   mehr ungemessen, der Faktor steht als Zahl 1, und die Begründung trägt den Wortlaut der
   Quelle — „Value of the trade flow (in thousands current USD)" —, die Abruf-URL der
   Beschreibungsseite und das Abrufdatum 2026-09-02. Das Feld frage ist beantwortet oder
   entfällt; eine unbeantwortete Frage neben einem gemessenen Faktor ist ein Rücklauf.
2. **Die beiden offen-Einträge der Reihe 14 sind ersetzt, nicht ergänzt**, und an ihrer
   Stelle stehen zwei Sachen: die gemessene Preisbasis „laufende Preise" als offener
   Widerspruch zu T5 Klasse 2 mit dem Adressaten Architekt, und der Versionsvorbehalt aus
   Abschnitt 1 des Befunds. Nachweis: Die Zeichenfolge „ist in keiner der drei
   Befunddateien gemessen" kommt bei Reihe 14 nicht mehr vor.
3. **Der erste offen-Eintrag der Reihe 16 ist durch die Antwort ersetzt** — Größenordnung
   gleich mit Faktor 1, Preisbasis verschieden, BACI laufend gegen WDI konstant 2015 — und
   nennt, woher die Einheit von N kommt: über T23 Punkt 1 aus Reihe 1 und nicht aus Reihe 2.
   Reihe 3 ist unverändert und trägt weiter art ungemessen.
4. **Sonst ist nichts geändert.** Alle Felder urteil, grund, wortlaut, url, url_gegenprobe,
   abrufdatum, sollreihen und die Zählblöcke, die Widerspruchsliste und die Deckungsblöcke
   sind zeichengleich. Der Prüfer weist das über den vollständigen Änderungsdiff nach und
   darf ausser den genannten Stellen der Reihen 14 und 16 auf keine berührte Zeile stossen.

## Was ausdrücklich kein Befund ist

- **Die Wortwahl bei art.** specs/ schweigt dazu, siehe oben.
- **Dass Reihe 3 ungemessen bleibt.** Die PWT-Dokumentation ist mit den Werkzeugen dieser
  Rolle nicht lesbar; das ist in 0025 gemessen und gehört nicht hierher.
- **Dass der Widerspruch zu T5 Klasse 2 nicht aufgelöst wird.** Er gehört dem Architekten.
  Dieses Paket trägt eine Messung nach, kein Urteil.

## Rückläufe

0.
