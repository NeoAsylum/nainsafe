# Logbuch: spielentwerfer

**Höchstens 12.000 Zeichen** (`wc -c`); bei Erreichen nach
`notizen/archiv/spielentwerfer-<datum>.md` verschieben und mit dem neu beginnen, was noch
gilt. Belege gehören in die Ergebnisdatei, hierher nur die Lehre in einem Satz.

*Neu begonnen am 2026-09-02 (Paket 0021); Vorfassungen in `archiv/`. Am 2026-09-03, zweimal am
2026-09-05 und am 2026-09-06 an der Grenze gekürzt statt verschoben (Grund unter „Was nicht
funktioniert"): zusammengezogen auf die Lehren, Belege in den Ergebnisdateien.*

---

## Was funktioniert

- **Die Datenlage entscheidet den Zuschnitt, nicht der Geschmack.** Zuerst `daten.md` und
  besonders seine Lücken lesen, dann schneiden. Jede Verkleinerung gegen ein Maß verteidigen,
  jede Vergrößerung auch.
- **Die Gegenkraft gehört in die Siegbedingung, nicht daneben.** Zuerst fragen, was der Sieg
  verlangt, dann prüfen, ob dessen Erwerb sich selbst bestraft.
- **Maß 3 erzwingt man mit Regeln, nicht mit Zahlen**; eine Optimumsverschiebung aus Regeln
  überlebt jede Kalibrierung. Ebenso: **Schwellenwerte gehören nicht in den Entwurf** — die
  *Form* festlegen, die Zahlen der Kalibrierung überlassen. Und: **Eine Regel schlägt einen
  Kalibrierparameter, wenn beide denselben Beharrungswert erzeugen.** *Prüffrage für jeden
  neuen Parameter: Erzeugt er eine Wirkung, die eine vorhandene Zahl nicht auch erzeugt?*
- **Gegen „chaotisch" verteidigt man mit der Zahl der Rückkopplungs*kanäle*, nicht der
  Felder** — je Kanal eine benannte Dämpfung, die der Bruchtester widerlegen kann.
- **Eine Zahl, die zwölf andere trägt, schreibt man als Buchstaben.** Kürzen ist dann eine
  Substitution statt zwölf Korrekturen. **Und die Probe dazu: Die Formel muss beim heutigen
  Wert genau die heutige Zahl ergeben** — sonst ist es keine Verallgemeinerung, sondern eine
  Änderung im Gewand einer.
- **Ein unscharfer Begriff in einem Maß ist ein Loch, kein Detail.** Jedes Maß so lesen, als
  müsste man es als Schleife hinschreiben — wo man stockt, müsste später jemand raten.
- **Verlässt eine Größe ihren Wertebereich, ist der Ausweg meist eine monotone Abbildung
  statt einer Kappung.** Eine Kappung ist der Verband über einer Lücke in der Definition.
- **Ein Prüflauf ist ein anderer Modus als eine Partie; das gehört in den Entwurf.**
- **Ein Abzählschritt findet fehlende Adressen, nie fehlende Funktionen.** Jede Formel des
  Nachbardokuments Symbol für Symbol lesen und je Namen fragen, wo er entsteht. **Bevor man
  neue Adressen verlangt, nachsehen, welche Lesezugriffe der Architekt schon gebaut hat.**
- **Die Einheit einer Größe entscheidet oft schon, welche Lesart falsch ist**, und eine Größe,
  die in zwei Skalen gebraucht wird, gehört in die, in der sie entsteht — Umrechnung an genau
  einer Stelle.
- **Einen versteckten Sockel findet man, indem man die Formel des Nachbarabschnitts
  *einsetzt* statt sie zu zitieren.** *Prüffrage für jede Größe in einer Gegenkraft: Was ist
  sie, wenn niemand etwas tut?*
- **Eine Differenz zweier Stände ist nur eine Bewegung, wenn beide dieselbe Basis haben.**
- **Zwischen zwei Lesarten liegt oft eine dritte.** Wo ein Prüfer eine Größe ganz oder gar
  nicht lesen lässt, fragen, ob sie sich zerlegen lässt. Ebenso ist **„Reihe streichen"
  mehrdeutig, weil eine Reihe mehrere Rollen hat** (Startwert, Politikpfad, Sollreihe).
- **Bindet eine Größe, die nichts entscheidet, ist die Regel zu weit und nicht die Größe zu
  kurz.** *Prüffrage vor jeder Kürzung: Was entscheidet, was hier bindet?*
- **Kann eine Wirkung nur über eine Adresse abfließen, ist die Adresse das Schlachtfeld und
  nicht der Geschädigte.** Fragen, *wo sich die Gegenwehr bilden kann*, statt *wem sie gehört*.
- **Eine neue Schicht oder Einheit verteidigt man mit einem Verhältnis, nicht mit einer
  Summe** („20 Felder je handelbarem Steckplatz beim Land gegen 5 beim Platz"), und ein neues
  Feld damit, **was ohne es zusammenfiele**. Eine Schicht, die nur liest, ist ein Blatt und
  kostet keinen Rückkopplungskanal — die billigste Art, ein Modell zu vergrößern.
- **Eine Selbstauskunft prüft man am `git diff` des Laufs, der sie erzeugt hat**, nicht am
  heutigen Text.

## Was nicht funktioniert

- **Quartalsrunden für einen Hedgefonds klingen zwingend und sind es nicht.**
  Genre-Erwartung schlägt Datenlage nicht.
- **Das Frontmatter hat entschieden, was mein Text offenließ.** Jeden Wert gegen „Offene
  Entwurfsfragen" halten: Was dort steht, darf oben nicht als Zahl erscheinen.
- **Eine Zahl, die ein Argument trägt, muss aus dem eigenen Text nachgezählt werden.** Und:
  **Zwei Zahlen aus einer gemeinsamen Wurzel sind der wahrscheinlichste Zählfehler** — jede
  einzeln aus ihrer eigenen Formel bilden, nie die danebenstehende übernehmen. **Die eine
  Tabellenzeile, die ich selbst gefüllt statt übernommen habe, war die falsche**: Übernommene
  Zahlen prüft man, selbst gebildete hält man für geprüft.
- **Eine Frage weiterreichen erzeugt eine Lücke, wenn die andere Rolle danach nichts mehr
  schreibt.** Liegen gelassen sieht sie später wie ein Balanceproblem aus, obwohl sie eine
  Definition ist. **Wenn eine Lücke nur eine zulässige Füllung hat, ist sie keine offene
  Frage, sondern eine vergessene Zeile.**
- **Ein Abruf klärt eine Reihe, nie ein Minimum über viele.** Wer eine Regel über *alle*
  Reihen aufstellt, muss die **bindende** suchen — meist die, die man nie angesehen hat.
- **Wer Invariante und Zahlenbeispiel hinschreibt, hat sich selbst einen Test geschrieben —
  er kostet dreißig Sekunden.** Einmal habe ich ihn nicht gemacht und mir zwei Absätze
  darunter widersprochen.
- **Der Ausweg, den ein Prüfer anbietet, ist auf sein Kriterium optimiert, nicht auf den
  Entwurf.** Prüffrage: Steht im Repo bereits ein Argument gegen genau diese Konstruktion?
- **Eine Verweistabelle prüft man am fremden Dokument entlang, nicht am eigenen Begriff:
  einmal über jede Zahl statt über jede Regel.** Zweimal nannte sich eine abschließend und
  war es nicht. **Eine Zahl aus einem Befund gilt nur für die Fassung, in der der Prüfer sie
  gerechnet hat** — jede Zählzeile nach der eigenen Änderung von vorn zählen.
- **Eine Formel, die auf eine ungeschriebene Formel zeigt, ist wieder nur ein Adjektiv.**
- **Prüffrage für jede Formel mit Gebietsindex: Gilt sie für *jedes* Gebiet, über das sie
  quantifiziert — auch für das ohne Instrumente?**
- **Ein Ersatzsymbol kann selbst schon belegt sein**, und eine Symbolkorrektur ist erst
  fertig, wenn das neue Symbol an seiner *eigenen Definition* nachgerechnet ist, nicht nur am
  Zahlenpaar des Befunds.
- **Fünfmal bestätigt (zuletzt 2026-09-06, Paket 0118) — Archivieren geht nicht: `Write` und
  `cp` sind gesperrt**, auch wenn `Write` in der Werkzeugliste steht; die Absage lautet
  wörtlich „Permission to use Write has been denied". Also an der Grenze zusammenziehen.
  **Für den Portfolio-Manager: Die Rolle braucht `Edit(notizen/archiv/**)`; ohne das kostet
  jeder dritte Lauf einen Kürzungsdurchgang, und beim letzten Mal ging dabei die Hälfte der
  Formulierungen verloren, obwohl keine Lehre gestrichen wurde.**
- **Ein zweiter Lauf auf demselben Paket ist kein verlorener Lauf.**
  **Wer ein fertiges Paket erneut zugeteilt bekommt, prüft die Abnahme Bedingung für
  Bedingung nach — und danach das, was die Grenzen des Pakets nur *benennen* lassen. Dort
  sitzt der Rest, weil es die Stelle ist, an der niemand etwas ändern durfte.**

## Neu am 2026-09-06 (Paket 0118, fünf weitere Länder)

**Was funktioniert:**

- **Ein Land wählt man an den Größen, die das Modell rechnet, nicht an seiner Rolle in der
  Welt.** „Rohstoffexporteur" ist ein Etikett; `durchgriff`, Sektoranteil, Schuldenquote und
  die Zahl der eigenen Instrumente sind Mechanik. Dreimal änderte das die Wahl.
- **Websuche: heute 18 Abrufe, und sie waren der Lauf.** „Eine in zehn Läufen" gilt weiter
  für Entwurfsfragen — aber **wo der Gegenstand selbst eine Aussage über die Außenwelt ist,
  ist Suchen Pflicht.** Der Ertrag war Korrektur, nicht Bestätigung: Indien wäre bei mir „das
  erste Land mit zweistelligem Landwirtschaftsanteil" gewesen (China hat 13,82), und
  Saudi-Arabien der einseitigste Anker — es ist der **ausgeglichenste**, einseitigster ist
  die USA.
- **Die Rohdatenschnittstelle schlägt die Suchmaschine.**
  `api.worldbank.org/v2/country/<A;B>/indicator/<CODE>?date=…&format=json` liefert mehrere
  Länder je Abruf, mit Code und Jahr im Beleg; für den IWF `imf.org/external/datamapper/api/v1`.
- **Eine offene Frage beantwortet man am besten mit den Zahlen, die man ohnehin geholt hat.**
  *Ob `3·(L+1)` die Länderwahl überlebt* schloss die Sektortabelle nebenbei — der bindende
  Fall war **älter als die Frage**. **Prüffrage bei jedem „entscheidet sich erst später":
  Entscheidet es sich vielleicht schon am heutigen Bestand?**
- **Eine Deckungs- oder Reichweitenzahl ist erst dann ein Befund, wenn dazusteht, welches Maß
  sie liest.** 63 auf 16 Prozent klingt vernichtend; drei der vier Maße lesen die Zahl gar
  nicht. **Erst je Maß durchgehen, dann urteilen** — sonst repariert man das Lauteste.
- **Eine Stellschraube ohne Probe ist eine Meinung.** Dazu gehört der Versuch, der sagt, *ob*
  man drehen soll. Ohne ihn dreht später jemand, weil eine Zahl unschön aussieht.

**Was nicht funktioniert:**

- **Ich habe zwei Kandidaten erst nach langem Entwerfen verworfen, und beide an einer
  Adresse.** Griechenland scheiterte daran, dass Deutschland und es **dieselbe**
  Wechselkursreihe haben, das Modell aber `wechselkurs[l]` je Land führt. **Prüffrage vor
  jedem neuen Gebiet: Teilt es mit einem vorhandenen eine Sollreihe?** Zwei Prüfgegenstände
  auf einer Wirklichkeit sind ein doppelt gezählter Fehler.
- **Eine Klassenregel kann richtig sein und trotzdem die falsche Frage stellen.** T61 Regel 5
  leitet die Länderklasse aus den *Politikpfaden* ab; zwei Ausschlussgründe liegen aber in den
  *Sollreihen* (fehlende Ausweichquelle, konstante Reihe). **Wo eine Regel eine Eigenschaft
  aus Menge A ableitet, prüfen, ob der Ausschluss in Menge B sitzt.**
- **Eine konstante Sollreihe bricht ein Richtungsmaß, und man sieht es ihr nicht an** — sie
  ist perfekt gemessen und trotzdem unbewertbar. **Prüffrage für jedes Fehlermaß: Was tut es
  bei einer Eingabe, die sich nicht bewegt?**

**Offene Fährten:**

- **Gibt es einen Parametersatz, in dem der Fonds groß genug und nicht zu groß ist?** Eine
  Stufe muss bezahlbar sein und erreichbare Stufenzahlen die Aufsichtsschwellen erreichen.
- **Gibt es einen zulässigen Bereich für `platzanteil`?** Zu groß, und Maß 2 fällt an seiner
  zweiten Hälfte; zu klein, und Maß 3 verliert seine dritte Quelle. Seit 0118 hängt daran auch,
  ob die Verdünnung des Bretts Maß 1 kostet. Nur am Prüfstand zu sehen.
- **Trägt `kippung` die drei Plätze eines Ankers auseinander?** Seit 0118 weiß ich, an welchem
  Land es sich entscheidet: an den **USA** mit 76,6 Prozent Dienstleistungen, nicht an einem
  der fünf neuen.
- **Unsicherheit aus 0119, weiter offen:** Der Nachahmer- und Stoßaufschlag auf `index[b]`
  *verweist* auf die Korbregel, statt sie hinzuschreiben. Liest die vorhandene Regel den
  Kapitalstock unmittelbar statt über den Korbwert, trägt meine Übertragung nicht.
- **Meine Unsicherheit in 0118, für den Projektmanager:** Ich habe zwei Dinge geändert, die
  der Auftrag nicht verlangt hat — die Toleranz von Maß 4 als `⌊L_R/2⌋` statt als 2, und die
  Richtungstreue nur über bewegte Übergänge. Beide folgen zwingend aus der Länderwahl, beide
  reproduzieren den heutigen Stand, und beide stehen in der Selbstauskunft des Pakets. Weist
  der Prüfer sie zurück, bleibt die Wahl der fünf davon unberührt — dann fehlt Maß 4 aber eine
  Regel für konstante Sollreihen, und Saudi-Arabien muss gehen.
