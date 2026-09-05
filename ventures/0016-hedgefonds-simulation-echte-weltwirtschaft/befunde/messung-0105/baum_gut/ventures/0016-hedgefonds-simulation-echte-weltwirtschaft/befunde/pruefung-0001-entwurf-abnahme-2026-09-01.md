---
typ: pruefung
paket: 0001-entwurf-abnahme
pruefer: entwurf-pruefer
datum: 2026-09-01
urteil: zurueck
kriterium_geprueft: die fuenf Bedingungen des Pakets einzeln -- Rechenvorschrift je Mass (1), Herkunft jeder Groesse (2), Zahlengleichheit beider Dokumente (3), Durchfuehrbarkeit des Rueckvergleichs (4, mit eigenem Weltbank-Abruf), Abarbeitung aller zwoelf Vorrundenbefunde (5); Bedingung 1 und 2 gerissen, Bedingung 3 an einer Zahl
befunde: 3
---

# Prüfung des Entwurfs, dritte Fassung, gegen `0001-entwurf-abnahme`

Erstmals mit Arbeitspaket. Geurteilt wird gegen dessen fünf Bedingungen und gegen nichts
sonst; alles, was das Paket unter *Was ausdrücklich kein Befund mehr ist* aufzählt, habe
ich stehen lassen, auch wo sich Genaueres denken ließe.

**Ergebnis: Bedingung 5 ist erfüllt, Bedingung 4 ist erfüllt und von mir nachgemessen.
Bedingung 1 reißt an einer Stelle, Bedingung 2 an einer, Bedingung 3 an einer Zahl.**
Befund 1 ist der einzige, der etwas kostet — er macht Maß 2 und Maß 3 unberechenbar.
Befund 2 und 3 sind zusammen drei Tabellenzeilen und ein Wort.

Nicht gelesen: `notizen/spielentwerfer.md`, `notizen/architekt.md`.

---

## Befund 1 — Der Suchbot hat keine Bewertungsfunktion, und Maß 2 wie Maß 3 stehen vollständig auf ihm

**Bedingung 1.** Schwere: hoch. Derselbe Fehlertyp wie Vorrundenbefund 4, eine Ebene tiefer.

Beide Maße sind als Suchbotläufe definiert: Maß 2 „alle 126 Profile, je 20 Startwerte,
Suchbot"; Maß 3 „Beide Läufe verwenden den Suchbot, innerhalb wie außerhalb des Fensters".
Damit ist der Suchbot Teil der Rechenvorschrift, nicht ihre Umgebung.

**So erzeugt man den Fehler, Schritt für Schritt:**

1. Man baut Maß 2 nach `spiel.md`. Für Runde `t` liefert das Vorratsverfahren die
   Artenfolge der drei Steckplätze (eindeutig, nachgerechnet).
2. `technik.md` T41 liefert die 60 Kandidatenbündel: drei Ziehungen je Kandidat entlang
   der Artenfolge, kanonische Ordnung aus T32, Startwert nach T11. Ebenfalls eindeutig.
3. Jetzt ist **der beste der 60 zu wählen**. Die einzige Stelle, die das beschreibt, ist
   die Botliste: *„Suchbot(profil, kandidaten=60, tiefe=1) — 60 Kandidaten nach T41,
   bewertet durch ein Nachspiel von einem Zug mit dem Heuristikbot als Fortsetzung.
   Gleichstand nach Aktionskennung."* Und `spiel.md`: *„der Suchbot durch Suche"*.
   **Womit verglichen wird, steht nirgends** — weder in `spiel.md` noch in T32, T34, T35,
   T36, T41 oder T43. Der Gleichstandsbrecher setzt eine Vergleichsgröße voraus, die kein
   Satz benennt.
4. Ein Rückgriff auf die Ergebnisgröße der Partie schließt die Lücke nicht: Sie ist erst
   am Partieende definiert. Dass hier wirklich nur **ein** Weltschritt vorausgerechnet
   wird, ist über die Kosten belegt und nicht ausgelegt — `R × (1 + 60) = 1.464`. Ein
   Nachspiel bis Runde R je Kandidat kostete `60 · Σ(R+1−t) + R = 60 · 300 + 24 = 18.024`
   Weltschritte je Partie und damit das Zwölffache; die Rechnung in Abschnitt 10 trägt
   dann nicht mehr. Nach genau einem Weltschritt läuft die Partie aber noch, also braucht
   der Bot eine **statische Bewertung des Zwischenzustands**, und die fehlt.

**Warum das eine Entwurfsentscheidung ist und keine Bauentscheidung:** Zwei naheliegende
Bewertungen geben verschiedene Maße.

- *Fondsvermögen nach dem Schritt.* Lobbybudget (Aktion 3) kostet in dieser Runde Kasse
  und zahlt erst über Einfluss zurück, also über die **zweite** Hälfte des Mandats, die in
  dieser Bewertung nicht vorkommt. Ein solcher Bot spielt Lobby nur, weil das Profil ihm
  den Steckplatz zuweist, und wählt darin das billigste Ziel. Klasse 3 stellt dann
  strukturell keinen Gewinner, und Teil 1 der Abnahme von Maß 2 fällt durch — nicht am
  Spiel, sondern am Bot.
- *Abstand zum zweiteiligen Mandat (Vermögen **und** Einfluss in zwei Ländern).* Derselbe
  Lauf kann bestehen.

Damit misst Maß 2 die Wahl des Bauagenten und nicht das Spiel — wörtlich der Fall, den
Bedingung 1 ausschließt („kein *geeignet gewählt*"). Maß 3 trifft es doppelt: `p*` und
`q*` sind die Argminima über dieselbe Bewertung, und die Verschiebung ist ihr Abstand.

**Und es ist nicht delegiert.** `technik.md` Abschnitt 12 gibt genau eine Botfrage frei:
*„Die konkrete Rangfolge im Heuristikbot innerhalb einer Art"*, mit den Auflagen fest,
dokumentiert, gleichstandsfrei. Das ist eine erklärte Freiheit und deshalb **kein**
Befund. Die Zielgröße des Suchbots steht in keiner Liste offener Punkte — sie fehlt
schlicht.

**Der Ausweg ist nicht meiner.** Ein Satz in `spiel.md`, der die Vergleichsgröße benennt
(Ergebnisprognose, Mandatsabstand, gewichtete Summe aus Vermögen und Einfluss), genügt;
der Zahlenwert einer etwaigen Gewichtung ist danach ein Kalibrierwert nach T27 und
ausdrücklich kein Befund mehr.

---

## Befund 2 — Zweiunddreißig der 310 Adressen haben keinen Startwert, und die Tabelle, die „abschließend" heißt, ist es nicht

**Bedingung 2.** Schwere: niedrig, aber die Bedingung ist binär.

`spiel.md` führt je Land vier Politikinstrumente *„jedes mit Stand, anliegendem Druck,
Gegendruck und Restverzögerung"*; T15 zählt daraus `4 × 4 = 16` Felder je Land, also 64
insgesamt.

**So erzeugt man den Fehler:** Man baut den Jahrgang und sucht je Adresse den Startwert.

1. Die verankerten stehen in der Reihenliste des Architekten (19 Zeilen). Dort kommt
   weder *anliegender Druck* noch *Restverzögerung* vor.
2. Für alle übrigen verweist T23 Punkt 1 ausdrücklich auf **eine** Stelle: *„die Größen
   ohne Anker stehen in der Tabelle ‚Jede Größe ohne Datenanker' in `spiel.md`"*. Diese
   Tabelle sagt von sich: *„Hier stehen alle übrigen, abschließend."*
3. Sie führt `Gegendruck je Instrument | 0`, die `drei Restdauerzähler je Land | 0` (das
   sind `marktverbot_rest`, `lobbykosten_rest`, `regierungsdruck_rest` nach T15, nicht die
   Restverzögerung der Instrumente) und `Finanzmarktregulierung (Stand)`. **Nicht** führt
   sie den anliegenden Druck (4 Instrumente × 4 Länder = 16 Adressen) und die
   Restverzögerung (weitere 16).
4. Der Jahrgangsbau hat für diese 32 Adressen also keine Regel, und weichen kann er nicht
   aus: Die Sollmaske `spielmodus` umfasst alle 310, und T18 verlangt jede Adresse der
   Maske je Runde genau einmal geschrieben.

Die Entstehungsregel *im Lauf* ist beschrieben (Aktion 3 legt Druck an, Schritt 3
verrechnet ihn und zählt die Verzögerung herunter) — es fehlt allein der Startwert, und
er steht auch nicht in `parameter.toml`, weil die Tabelle ihn dorthin hätte verweisen
müssen. Dass die Antwort mit hoher Wahrscheinlichkeit `0` lautet, ist gerade das, was
Bedingung 2 nicht gelten lässt: *„Eine undefinierte Größe ist ein Befund."* Zwei
Tabellenzeilen.

**Zwei Fälle, die ich geprüft und *nicht* als Befund gezählt habe**, damit die Grenze
sichtbar ist: Der **Weltpreis** (2 Adressen) steht ebenfalls nicht in der Tabelle, seine
Regel — Markträumung in Schritt 4 — steht aber im Text und braucht keinen Startwert, weil
sie in Runde 1 aus `lies_alt(gebiet.sektor.preis) = 10.000` rechnet. Die vier
**Partiefelder** (Runde, Jahrgangskennung, Parametersatz-Prüfsumme, Mandatsstand) sind
Buchführung des Laufs und keine Modellgrößen.

---

## Befund 3 — `spiel.md` und `technik.md` nennen für dieselbe Invariante verschiedene Rundenzahlen

**Bedingung 3.** Schwere: niedrig. Ein Wort.

- `spiel.md`, Vorratsverfahren: *„Es wird nie gerundet und nie gezogen: über **15 Runden**
  bekommt Art `i` genau `3·ai` Steckplätze, der Rest ist beschränkt."*
- `technik.md` T43: *„Sind in **fünf** aufeinanderfolgenden Runden alle fünf Arten
  durchgehend zulässig, so steht der Vorratsvektor danach wieder auf `(0,0,0,0,0)`, und
  jede Art `i` hat genau `3·ai` der **fünfzehn** Steckplätze bekommen."*

**So erzeugt man den Widerspruch:** Man rechnet nach. Je Runde kommen `Σ 3·ai = 15`
Vorratspunkte hinzu und gehen `3 × 5 = 15` ab; die Summe schließt sich nach **jeder**
Runde, der Vektor selbst nach fünf. Ich habe das Verfahren für das Referenzprofil und für
`(2,1,1,1,0)` von Hand durchgespielt: beide stehen nach Runde 5 wieder auf
`(0,0,0,0,0)`, mit `3·ai` Steckplätzen je Art von fünfzehn, und die Folge des
Referenzprofils fällt zeichengleich als `1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5` heraus —
genau die Probe, die `spiel.md` **zwei Absätze unter dem falschen Satz selbst rechnet**,
und zwar über fünf Runden. Über 15 Runden bekäme Art `i` neun mal `ai` Steckplätze.

Der Algorithmus ist davon nicht betroffen, der zusammenfassende Satz ist es. `technik.md`
meldet die Stelle in Abschnitt 12 als Beobachtung, weil die Architektenrolle ihm verbietet,
den Entwurf zu ändern — sie steht also unverändert offen, und Bedingung 3 verlangt an
dieser Stelle denselben Wert in beiden Dokumenten.

---

## Wonach ich gesucht und was ich nicht gefunden habe

Damit diese Prüfung von einer, die nicht stattfand, unterscheidbar ist. Geordnet nach den
fünf Bedingungen.

**Bedingung 1, je Maß einzeln.**
*Maß 1* — vollständig: 50 Startwerte, Trägerpartie, 30 Bündel je Runde und Startwert,
Ziehregel bis auf das Verfahren ausgeschrieben (T35: `mod 4`, Kappung an `m`, partielles
Fisher-Yates, Sortierung nach Aktionskennung, Kürzung auf das größte zulässige
Anfangsstück statt Verwerfung, Vorratsfortschreibung der eingespeisten Runde), Median
über gerade Anzahl definiert, Zusammenfassung über die Startwerte definiert, Schwelle 0,4
je Drittel. **Kein Befund.**
*Maß 4* — vollständig: T42 rechnet MAPE, Ratenfehler und Richtungstreue in Ganzzahlen aus,
einschließlich der beiden Fälle, die `spiel.md` nicht kennt (`soll = 0`, Neubasierung
innerhalb einer Ratenreihe). Die dreiwertige `sgn`-Regel ist entschieden. **Kein Befund.**
*Maß 2 und 3* — bis auf Befund 1 vollständig: Profilliste, Kennungsvergabe, Kern
vierwertig, Fensterlogik, Vorrat läuft über den Wechsel weiter, Schwellen 24.000 / 1,25 /
0,4, Wertemenge der Verschiebung `{0; 0,4; …; 2,0}` benannt.

**Bedingung 2.** Alle 310 Adressen aus T15 gegen die Reihenliste und die Tabelle „Jede
Größe ohne Datenanker" abgeglichen. Verankert sauber: Wertschöpfung (Reihe 1 × 2),
Kapitalstock (3), Beschäftigung (7), Bevölkerung (5), Erwerbstätige (6), Produktivität (4,
nur Startwert — richtig, sonst prüfte der Rückvergleich sich selbst), Preisniveau (15),
Inflation (8), Leitzins (9), Wechselkurs (10), Staatsschuld (11), Haushaltssaldo (12),
Zollstand (13), Handel (14), `durchgriff` (16). Als Konstrukt gekennzeichnet mit Regel:
Sektorpreis, `landespreis`, Zustimmung, Aufsichtszähler, Nachahmerzähler, Einfluss,
Gegendruck, drei Restdauerzähler, Finanzmarktregulierung, `markt.wert`, `markt.rendite`,
Fondsblock. **Offen allein die 32 Adressen aus Befund 2.**

**Bedingung 3.** Jede Zahl, die beide Dokumente nennen, nachgerechnet — der Anlass steht
in meinem Logbuch: Eine geänderte Grundzahl ist die billigste Stelle für eine
unvollständige Nachbesserung, und R ist von 28 auf 24 gefallen.
`4 × 44 + 22 + 56 + 52 + 4 = 310`; Sollmaske `108 + 22 + 40 + 2 + 3 = 175` und
`68 + 12 + 2 + 52 + 1 = 135`, Summe 310; `1.464 = 24 × 61`; `Σ(25−t) = 300`, also
`30 · 300 + 24 = 9.024` und `× 50 = 451.200`; `126 = C(9,4)`;
`126 × 20 × 1.464 = 3.689.280` und das Doppelte `7.378.560`; Summe der Maße
**11.519.040** in beiden Dokumenten gleich; Nachtlauf
`11.519.040 + 240.000 + 200 + 24 + 24.000 = 11.783.264` und daraus 2,0 bzw. 9,8 Minuten;
Kalibrierung `90.240 + 922.320 = 1.012.560` je Satz und 21 Minuten auf acht Kernen;
Tiefe 2 `24 × (1 + 60 × 61) = 87.864` und daraus 664 Millionen. Ergebnisbänder
`1.000…24.000`, `25.000…27.000`, `31.000…54.000` in beiden gleich. 31 Sollreihen mit 27
unabhängigen, 23 freie mit 19 unabhängigen, 16 Prüfgegenstände, Toleranz 2, Schwellen
20 % / 300 bp / 0,6 — gleich. Die Jahreszuordnung stimmt: 1999 am Ende von Runde 2, 2001
Runde 4, 2008 Runde 11, 2020 Runde 23, und daraus `exogen_ab_runde = 1999 − 1997 + 1 = 3`
für den deutschen Leitzins. Die Profilkennungen habe ich selbst lexikographisch
abgezählt: `(1,1,1,1,1)` liegt auf **76**, die sechs kernlosen `(0,0,0,a4,a5)` auf **0
bis 5** — beide Anker des Architekten stimmen. `durchgriff` nachgerechnet:
`71,94/(71,94+26,77) = 7.288`, `915,39/(915,39+760,02) = 5.464`, `H/N = 0,3 → 2.308`;
monoton in `H/N`, per Konstruktion in `0…10.000`, Ordnung erhalten, Gewicht auf dem
Landespreis nie negativ. **Nur die eine Zahl aus Befund 3 weicht ab.**

Nicht als Befund gezählt: Die Schranke `R ≤ 26` aus T40 ist um eine Runde konservativ —
die Bänder überlappen erst ab `R = 28` (`R × 1.000 + 3.000 ≥ 31.000`). Eine zu enge Wand
ist keine falsche Zahl, und für R = 24 ist sie folgenlos.

**Bedingung 4.** Der Startjahrgang ist jetzt gemessen, und ich habe die Messung nicht
übernommen, sondern wiederholt:
`api.worldbank.org/v2/country/USA/indicator/NV.IND.TOTL.ZS?date=1994:2024`, eigener Abruf
2026-09-01 — Werte für **1997 bis 2021**, `null` für 1994–1996 und 2022–2024. Das Fenster
1997–2021 mit 25 Stützstellen und R = 24 ist damit belegt, unabhängig von beiden
Entwürfen. Die Sollreihen sind je Reihe einer Quelle aus `daten.md` zugeordnet, der
Weltlauf ist durchführbar (Fondsteilsystem aus, Maske 175 von 310, kein Nenner null, keine
Todesart), und die Abnahmeregel steht mit Zahl: 16 Prüfgegenstände, höchstens zwei dürfen
reißen. **Bedingung erfüllt.**

**Bedingung 5.** Alle zwölf Vorrundenbefunde sind in beiden Dokumenten mit *behoben*
beantwortet, keiner mit *widersprochen*, keiner übersprungen. Stichprobenartig gegen die
Sache geprüft statt gegen die Behauptung: Befund 3 (`durchgriff` hält seinen Wertebereich
jetzt per Konstruktion — nachgerechnet, siehe oben), Befund 6 (`landespreis` ist über T39
`lies_alt`, die zweite Lesart ist nicht mehr formulierbar, die Monotonie der
Überschussfunktion damit belegt statt behauptet), Befund 8 (Kern `ohne`, 120
klassifizierte Profile, Kennungen 0–5 nachgezählt), Befund 10 (Bänder disjunkt, 24.000
trägt nur noch eine Bedeutung), Befund 11 (`R + 1 − t`, Drittel meinen die Runden, die
sie nennen). **Bedingung erfüllt.**

**Zwei Fährten aus meinem Logbuch, beide geschlossen.** Die Partielänge ist von 28 auf 24
gefallen, und jede abgeleitete Zahl ist mitgefallen — vollständig, siehe oben; T40 macht
den Fehlertyp künftig unmöglich, weil keine abgeleitete Zahl mehr als Literal steht. Die
Bruchstelle „eine Größe mit zwei Herren" hat sich ein weiteres Mal verschoben: Sie liegt
diesmal nicht zwischen den Dokumenten, sondern **in der Lücke zwischen ihnen** — die
Zielgröße des Suchbots gehört dem Spielentwerfer, die Kandidatenziehung dem Architekten,
und der Architekt hat seine Hälfte geschlossen (T41).

## Was ich nicht geprüft habe

- **Ob die Schwellen von Maß 4 mit endogener Produktivität erreichbar sind.** Unverändert
  das größte ungemessene Risiko; erst der Rückvergleicher am laufenden Kern kann es sagen.
  Kein Entwurfsfehler.
- **Die Drittanbieter-Ausnahme der WDI** für die Reihen 7, 8, 10 und 13. Vier Abrufe des
  Feldes „Source", Aufgabe des Datenbauers, hängt am Jahrgang und nicht am Entwurf. Fällt
  Reihe 13 aus, fängt T26 es auf.
- **Der IFS-Leitzins für China und Brasilien 1997–2021.** `imf.org` weist den Abruf mit
  HTTP 403 ab, `FR.INR.LEND` ist ein Indiz und nicht dieselbe Reihe. Nach T40 kostet ein
  engeres Fenster eine Manifestzeile — die Fährte ist damit entschärft, aber offen.
- **Der Planwert von 10 Mikrosekunden je Weltschritt.** Es gibt keinen Kern, also keine
  Messung; `technik.md` sagt das selbst und nennt die Folge (Markträumung anders bauen,
  falls über 50 µs). Kein Befund nach diesem Kriterium.
- **Die Zahlenwerte sämtlicher Schwellen und Elastizitäten.** Sie stehen nach T27 in
  `parameter.toml` und werden gemessen, nicht entworfen.
