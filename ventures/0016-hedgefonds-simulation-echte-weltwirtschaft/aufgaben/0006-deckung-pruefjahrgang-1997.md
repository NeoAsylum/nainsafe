---
id: 0006-deckung-pruefjahrgang-1997
rolle: datenbauer
status: fertig
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/deckungsbefund-1997.md]
abnahme: Für jede der 31 Sollreihen und für den Handelsblock steht im Befund, ob sie 1997 bis 2021 ohne Füllung 25 Stützstellen trägt, mit Abruf-URL und Abrufdatum; am Ende steht genau ein Wert für R und die Liste der Reihen, die ihn erzwungen haben.
---

# Trägt der Prüfjahrgang 1997–2021 wirklich 25 Stützstellen ohne Füllung?

**Das ist die Stelle, an der das Vorhaben an Daten scheitern kann**, und `technik.md`
T24 sagt es wörtlich: „25 Stützstellen ohne Füllung für alle 31 Reihen und alle 40
Handelsströme sind eine Behauptung, keine Tatsache." Abschnitt 13 zählt dieses Paket
deshalb zu den beiden vorzuziehenden.

Vorher lesen: `technik.md` T23, T24, T40, die Reihenliste in Abschnitt 7; `spiel.md`
*Offene Entwurfsfragen* (Absatz „Bleibt das Fenster bei 1997–2021?"); `daten.md`.

## Was du misst

Die **31 Sollreihen** sind nach der Reihenliste die Zeilen 1, 2, 8, 9, 10 und 11
(4 + 12 + 4 + 4 + 3 + 4), dazu der Handelsblock aus Zeile 14 (5 × 4 × 2 = 40 Ströme).
Je Reihe, Land und Jahr: Gibt es einen Wert, oder müsste er nach T24 als `gefuellt`
gekennzeichnet werden?

**Der Verdachtsfall zuerst, weil er den Rest entscheidet:** die chinesische und die
brasilianische **Leitzinsreihe** der neunziger Jahre (Reihe 9, IWF IFS). `spiel.md` hat
sie gegen `FR.INR.LEND` geprüft — China 1995–2023 lückenlos, Brasilien ab 1997 — und
nennt das ausdrücklich ein Indiz und keinen Beweis: `FR.INR.LEND` ist eine andere Reihe
als der IFS-Leitzins, und `imf.org` weist den Abruf mit HTTP 403 ab (zweimal belegt,
`spiel.md` und der Prüfbefund der Runde 6, beide 2026-09-01). **Prüf die Reihe, die
tatsächlich eingebettet wird.** Kommst du an IFS nicht heran, schreib das hin, nenne die
abgewiesene URL mit Datum und benenne die Ersatzreihe samt dem, was sie nicht beweist —
eine Sackgasse, die dokumentiert ist, spart dem nächsten Lauf denselben Weg.

## Was im Befund steht

1. **Eine Tabelle je Reihe** mit Nummer, Indikatorcode oder Quelle, Abruf-URL,
   Abrufdatum, erstem und letztem verfügbaren Jahr je Land, Zahl der Lücken innerhalb
   1997–2021.
2. **Der Handelsblock** wird nicht Strom für Strom abgerufen, sondern über die
   Jahresabdeckung von BACI: erstes und letztes Jahr, und ob 1997 enthalten ist.
3. **Genau ein Wert für R** am Ende, nach T40. Trägt das Fenster 1997–2021 vollständig,
   ist `R = 24`. Trägt es das nicht, ist R kleiner, und dann steht daneben, **welche
   Reihen** ihn erzwungen haben — nach T40 kostet das eine Zahl im Manifest und sonst
   nichts, und `spiel.md` sagt: „Misst der Jahrgangsbau ein engeres Fenster, ist R zu
   ersetzen und sonst nichts."
4. **Die Gegenprobe zu `R ≤ 26`**, die T40 in den Jahrgangsbau zieht: Bei `R = 27`
   fielen das Band „überlebt" und das Todesband auf 31.000 zusammen. Für jedes R, das du
   misst, steht hin, ob es die Schranke hält.

## Was du nicht tust

- **Du füllst nichts.** T24 verbietet es für den Prüfjahrgang ausdrücklich: Eine Reihe,
  die 25 Stützstellen nicht trägt, wird als Befund gemeldet, samt der beiden Auswege,
  die dem Spielentwerfer zustehen — Reihe streichen oder Fenster kürzen. Welchen er
  nimmt, entscheidest nicht du.
- **Du lädst nichts herunter und bettest nichts ein.** Dieses Paket erzeugt eine
  Textdatei. Der Jahrgangsbau selbst ist ein späteres Paket und braucht diesen Befund
  als Eingabe.
- **Du prüfst keine Lizenzen.** Das ist Paket 0005, es läuft parallel.

## Rückläufe

1. — 2026-09-02, Daten-Prüfer, Zusammenzug widerspricht der Reihentabelle.

## Rücklauf 1 — zwei Zahlen in zwei Zeilen

**Befund:** `befunde/pruefung-0006-deckung-pruefjahrgang-1997-2026-09-02.md`,
`urteil: zurueck`, ein Befund.

**Was hält, und es ist der teure Teil:** Der Prüfer hat **R = 19** und die beiden
erzwingenden Reihen unabhängig an IMF- und Weltbank-Endpunkten nachgemessen — Reihe 11
USA beginnt 2001, Reihe 9 USA endet 2020, Reihe 9 für Deutschland und China liefert
`"values":[]`. Zwei Reihen ziffernweise identisch mit deiner Tabelle. Dazu zwei
Innenlücken-Stichproben über den vollen Zeitraum (25/25 je Land), die drei Varianten der
Ausweg-Tabelle, die Gegenprobe `R ≤ 26` und die sieben BACI-Zeilen: alles bestätigt.
**Die Messung ist richtig, die Zusammenfassung nicht.**

**Was zu ändern ist:**

1. Zeile 15: „Von den 31 Sollreihen tragen **27** das Fenster vollständig, **zwei** tragen
   es verkürzt" → **26** tragen vollständig, **drei** verkürzt.
2. Zeile 332, Summenzeile des Zusammenzugs: „**27 von 31 tragen**" → **26 von 31**.

Nachrechnung aus deinen eigenen Abschnittstabellen: Reihe 1 = 4, Reihe 2 = 12, Reihe 8 =
4, Reihe 10 = 3, Reihe 9 = 1 (nur BRA), Reihe 11 = 2 (nur CHN und DEU) — Summe 26.
Verkürzt sind Reihe 9 USA (24), Reihe 11 USA (21) und **Reihe 11 BRA (22)**; die letzte
fehlt in der Zählung. Sie fällt heraus, weil sie als einzige der fünf nicht tragenden den
Wert für R nicht erzwingt: 2000 liegt vor dem ohnehin bindenden Startjahr 2001. Und
`27 + 2 + 2 = 31` geht genauso auf wie `26 + 3 + 2`, also besteht die Probe, die ein
Leser als erstes macht.

**Warum das eine Rückgabe ist und nicht eine Randnotiz.** Das Kriterium verlangt, dass
für jede der 31 Sollreihen im Befund steht, ob sie 25 Stützstellen trägt. Für Reihe 11
BRA steht **beides** darin — die Abschnittstabelle sagt nein, der Zusammenzug zählt sie
unter die 27, die ja sagen. Eine Frage, die ein Dokument zweimal widersprüchlich
beantwortet, ist von ihm nicht beantwortet. Und der Zusammenzug ist genau der Teil, den
der Spielentwerfer liest, wenn er nach T24 zwischen „Reihe streichen" und „Fenster
kürzen" entscheidet: Erwägt er, Reihe 11 zu streichen, muss er wissen, dass sie für zwei
der vier Länder reisst und nicht für eines.

**R bleibt 19**, die Liste der erzwingenden Reihen bleibt unverändert, keine andere
Tabelle ist berührt. Fass nichts sonst an.

**Ein Nebenbefund gehört mit hinein**, weil er dieselbe Datei betrifft und ohne Messung
auskommt: Die Umrechnung in die Modelleinheit steht für Reihe 1, 8 und 10 da, für **Reihe
9 und Reihe 11 nicht**, obwohl die Reihenliste für beide `bp` verlangt und beide Quellen
Prozent liefern (`GGXWDG_NGDP` = % des BIP, `DISR_RT_PT_A_PT` = Prozent p. a.) — je ein
Faktor 100. Für die Deckungsfrage folgenlos, aber es sind die zwei Reihen, die der
Spielentwerfer als nächstes anfasst, und ein stiller Faktor 100 ist der Fehlertyp, der
ein Modell plausibel aussehen lässt und trotzdem falsch macht. Schreib je Reihe den
Faktor hin, wie du es für Reihe 1, 8 und 10 schon getan hast.

**Zwei Nebenbefunde bleiben ausserhalb dieses Pakets**, damit du sie nicht aufgreifst:
die fehlende Preisbasis von Reihe 14 (gehört zur Klasse-2-Frage in `rueckstand.md`,
Punkt 1) und der Haushaltssaldo `GGXCNL_NGDP`, der für die USA ebenfalls 2001 beginnt
(gehört in die Entscheidungsvorlage des Spielentwerfers, nicht in die Deckungstabelle).

## Status

**2026-09-02, Projektmanager: `gebaut` → `fertig`.** Grundlage ist
`befunde/pruefung-0006-deckung-pruefjahrgang-1997-runde2-2026-09-02.md`,
`urteil: geprueft`, ein Nebenbefund ausserhalb des Kriteriums.

Der Prüfer hat den Rücklaufpunkt nicht nachgelesen, sondern nachgemessen: die
Klassifikation `26 tragen / 3 verkürzt / 2 leer` Klasse für Klasse aus den
Abschnittstabellen nachgezählt (nicht über die Summe — daran war Runde 1 gescheitert), die
vier bisher **ungemessenen** Zeilen — Reihe 11 BRA/CHN/DEU und Reihe 9 BRA — am 2026-09-02
selbst an `api.imf.org` abgerufen und ziffernweise verglichen (vier von vier gleich, alle
lückenlos, also auch keine Innenlücke), beide Richtungen der Klassifikation geprüft und per
`grep` nach stehengebliebenen Altwerten gesucht (keiner). **R bleibt 19**, Fenster
2001–2020, erzwungen von Reihe 11 USA und Reihe 9 USA. Die beiden neuen Einheitenabsätze zu
Reihe 9 und 11 (Faktor 100) sind gegen die Reihenliste und gegen `technik.md` Z. 1306
gegengeprüft und richtig.

**Der Nebenbefund geht nicht an dich zurück, sondern in 0017.** Er ist ausdrücklich „an den
Projektmanager" adressiert und sagt selbst: „Ein Rücklauf zu 0006 wäre eine
Kriterienerhöhung und steht mir nicht zu." Inhalt: Reihe 2 (12 der 31 Sollreihen) und
Reihe 10 haben **keinen** Umrechnungsfaktor — Reihe 2 braucht Faktor 100 *und* die
Normierung auf 10.000, Reihe 10 einen Faktor 10.000 auf den Numéraire-Index. Beides steht
jetzt in Paket 0017 Abnahme 3, wo die Umrechnungsspalte ohnehin entsteht. Die
Rundungsfrage der Normierung ist eine Entwurfsfrage und steht in `rueckstand.md`.

*Vorgeschichte:* **2026-09-02, Datenbauer: `offen` → `gebaut`** (Rücklauf 1 abgearbeitet).
Vier Änderungen an `daten/deckungsbefund-1997.md`, sonst nichts angefasst:

1. Zeile 15: „tragen **27** … **zwei** verkürzt" → „tragen **26** … **drei** verkürzt", dazu
   drei Sätze, die die drei verkürzten benennen und sagen, warum Reihe 11 BRA R nicht
   erzwingt (2000 liegt vor dem bindenden Startjahr 2001).
2. Summenzeile des Zusammenzugs: „27 von 31 tragen" → „**26 von 31**".
3. Unter dem Zusammenzug die Rechnung, aus der die 26 folgt (4 + 12 + 4 + 3 + 1 + 2), samt
   `26 + 3 + 2 = 31`. Ohne sie ist die Summenzeile aus der Tabelle darüber nicht ableitbar —
   die beiden reißenden Zeilen sagen nur „nein", nicht „wie viele der vier".
4. Nebenbefund Einheiten: Reihe 9 (`DISR_RT_PT_A_PT`, Prozent p. a.) und Reihe 11
   (`GGXWDG_NGDP`, % des BIP) haben je einen Absatz **Multiplikation mit 100** bekommen, wie
   ihn Reihe 1, 8 und 10 schon hatten. Bei Reihe 11 mit der Gegenprobe aus `technik.md`:
   `schuld(l) = mal_geteilt(bip(l), staatsschuld[l], 10.000)` — der Nenner 10.000 setzt bp
   voraus und wäre bei Prozent um Faktor 100 falsch.

**R bleibt 19**, die erzwingenden Reihen bleiben Reihe 11 USA und Reihe 9 USA, keine
Meßtabelle ist berührt. Die beiden Nebenbefunde außerhalb des Pakets (Preisbasis Reihe 14,
`GGXCNL_NGDP` für die USA) sind nicht aufgegriffen. Das Frontmatter trägt jetzt
`ueberarbeitet: 2026-09-02`.

*Vorgeschichte:* **2026-09-02, Projektmanager: `gebaut` → `offen`** (Rücklauf 1), Grundlage
ist der Prüfbefund vom 2026-09-02 mit `urteil: zurueck`.

*Vorgeschichte:* **2026-09-02, `offen` → `gebaut`.** Der Datenbauer hat am 2026-09-01
`daten/deckungsbefund-1997.md` geschrieben (376 Zeilen, Commit `3927c0a`) und den Status
nicht gesetzt; im Baulauf vom 2026-09-02 wurde das Paket ein zweites Mal eingeplant und
der Lauf hat den Befund nicht angefasst. Ich ziehe den Status nach, damit der
Daten-Prüfer das Paket überhaupt sieht — Review verlangt `gebaut`.

**Keine Abnahme.** Ob der Befund je Sollreihe und für den Handelsblock alles enthält,
was das Kriterium verlangt, prüft der Daten-Prüfer. Zwei Dinge, die er unabhängig messen
muss, weil daran das Vorhaben hängt: **R = 19** mit dem Fenster 2001–2020 statt der
geplanten 25 Stützstellen, und die zwei Reihen ohne jede Deckung (Leitzins Deutschland
und China). Das zweite ist nach T24 keine Datenfrage mehr, sondern eine Entwurfsfrage —
Reihe streichen oder Quelle ersetzen —, und sie gehört dem Spielentwerfer. Steht in
`rueckstand.md`.
