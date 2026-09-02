# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, geschrieben vom Projektmanager. Fassung 3. Diese Datei sagt, welche
Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden
lassen muss.

## Was dieser Lauf getan hat

**Sechs Statusnachzüge, alle mit Begründung im jeweiligen Paket.** Zum ersten Mal
liegen mehr Prüfbefunde vor als Bauergebnisse — vier Urteile aus der Nacht vom
2026-09-02, drei davon `zurueck`.

| Paket | von | nach | Grund |
|---|---|---|---|
| 0013 Prüfsumme | `gebaut` | **`fertig`** | Prüfbefund `geprueft`, alle fünf Bedingungen, zwei Summen unabhängig nachgerechnet |
| 0004 Gerüst + Festkomma | `gebaut` | **`offen`** | Prüfbefund `zurueck`, Rücklauf 1 |
| 0006 Deckung 1997 | `gebaut` | **`offen`** | Prüfbefund `zurueck`, Rücklauf 1 |
| 0009 `parameter.toml` | `gebaut` | **`offen`** | Prüfbefund `zurueck`, Rücklauf 1 |
| 0002 Fondsbewertung | `offen` | **`blockiert`** | seine Vorgabe ist an der Stelle in Revision, die es abschreiben soll — siehe unten |
| 0003 Einheiten | `blockiert` | `blockiert` | unverändert; eine falsch gewordene Begründung darin korrigiert |

**Zwei neue Pakete**, beide aus `specs/`, beide für den Fall, dass die drei Rückläufe
schneller durch sind als der nächste Lauf:

- **0016 `kern::schreiber`** (kernbauer, hängt an 0008) — T18, T38, T39, T19. Der
  einzige Schreibweg in den `Zustand`, die Ursachenkette, das Bitfeld über 310 Adressen
  und die zweiseitige Maskenprüfung je Modus.
- **0017 Reihenliste maschinenlesbar** (datenbauer, hängt an 0006 und 0014) — T23 Punkt 2
  und 8, T37. Die Eingabetabelle des Jahrgangsbaus, aus den drei gemessenen Befunden
  statt aus Fließtext.

**Alle drei Rückläufe sind klein**, und das ist der bemerkenswerte Teil: 0004 braucht vier
Zeilen umformulierte Prosa, 0006 zwei Zahlen in zwei Zeilen, 0009 drei Stellen in einer
Datei. Kein einziger Befund traf eine Rechnung. Der Kern-Prüfer hat `festkomma` unter ASan
und UBSan durchgerechnet, der Daten-Prüfer `R = 19` an fremden Endpunkten nachgemessen —
beides hielt.

## Wo die Pakete stehen

| Paket | Rolle | Status | woran es hängt |
|---|---|---|---|
| 0001 Entwurfsabnahme | spielentwerfer | `fertig` | — |
| 0002 Fondsbewertung | kernbauer | **`blockiert`** | Klasse-2-Entscheidung |
| 0003 Einheiten | kernbauer | `blockiert` | ADR gegen T5, oder gar nicht |
| 0004 Gerüst + Festkomma | kernbauer | **`offen`**, startbereit | Rücklauf 1 |
| 0005 WDI-Lizenz | datenbauer | `fertig` | — |
| 0006 Deckung 1997 | datenbauer | **`offen`**, startbereit | Rücklauf 1 |
| 0007 Adressverzeichnis | datenbauer | `fertig` | — |
| 0008 Zustand, 310 Felder | kernbauer | `offen`, startbereit | — |
| 0009 `parameter.toml` | datenbauer | **`offen`**, startbereit | Rücklauf 1 |
| 0010 Zustandsausgabe | kernbauer | `offen` | 0002 (blockiert) + eine Entwurfsfrage |
| 0011 Stack auf C++ | **architekt** | `offen`, **nicht einplanbar** | `BAUROLLEN` |
| 0012 Zufall | kernbauer | `offen`, startbereit | — |
| 0013 Prüfsumme | kernbauer | **`fertig`** | — |
| 0014 Lizenz, übrige Reihen | datenbauer | `gebaut` | Daten-Prüfer |
| 0015 Markierungssatz | datenbauer | `offen`, startbereit | — |
| 0016 `kern::schreiber` | kernbauer | **neu**, `offen` | 0008 |
| 0017 Reihenliste | datenbauer | **neu**, `offen` | 0006, 0014 |

`python3 agents/baulauf.py 0016-… --trocken` meldet 10 offen, 1 gebaut, 4 fertig, 2
blockiert und zieht daraus vier Baupakete — 0004, 0006, 0008, 0009 — und ein Review
(0014). Kein Bauagent läuft leer, keine zwei Pakete treffen sich in einer Datei, und im
Vorrat liegen vier weitere (0012, 0015, 0016, 0017).

**Eine Kollision musste ich dafür auflösen.** 0004 führte fünfzehn Dateien im Feld
`dateien`, darunter die sechs Modulplatzhalter. Wiedereröffnet hätte es damit 0008
(`zustand.hpp`) und 0012 (`zufall.hpp`) gesperrt — für vier Zeilen Prosa. Das Feld nennt
jetzt genau die zwei Dateien, die der Rücklauf ändern darf; die Existenzprüfung über alle
fünfzehn steht ausgeschrieben in Bedingung 1. Das Feld `dateien` ist Kollisionsvermeidung
und keine Baugeschichte — beim Rücklauf gehört es auf den Rücklauf verengt.

## Die Reihenfolge und warum sie so ist

```
0004 Rücklauf (Prosa)        0006 Rücklauf ─┐
0012 Zufall     (frei)                      ├──> 0017 Reihenliste
0015 Markierung (frei)       0014 (Review) ─┘
0009 Rücklauf   (frei)

0008 Zustand ──> 0016 Schreiber ──> (schritt, später)
             └─> 0002 Werte [BLOCKIERT] ──> 0010 Ausgabe
```

**Der Kern hat nach 0008 zwei Wege, und die Wahl ist diesen Lauf gefallen.** Meine offene
Frage vom 2026-09-02 lautete: `werte` (0002) oder `schreiber` (T18/T38/T39) zuerst?
`technik.md` Abschnitt 13 nennt beide in einem Atemzug und legt sich nicht fest.
Entschieden hat es nicht meine Vorliebe, sondern die Klasse-2-Frage: 0002 ist blockiert,
also ist der `Schreiber` der Kernkasten, der ohne offene Entwurfsfrage vorangeht. Er
hängt am `Zustand` und nicht an den Werten. Das war Glück, kein Plan — hätten beide Wege
an derselben Frage gehangen, stünde der Kern jetzt.

**Warum 0002 blockiert ist und nicht nur langsam.** Abnahme 5 dieses Pakets verlangt, dass
jede der siebzehn Formeln „Zeichen für Zeichen" mit T47 und T48 übereinstimmt, Punkt 2 die
drei Skalenübergänge aus T50. Die Klasse-2-Frage ändert nach `ops/plan.md` T5, T49, T23
Punkt 5 und T8 — und wenn sie einen vierten Skalenübergang braucht, auch T50. Dann ändert
sich das Abnahmekriterium, **nachdem** gebaut wurde, an dem Modul mit fünf Lesern
(`fondsvermoegen`, T47 Punkt 3). Ich löse den Widerspruch nicht auf; ich plane nur nichts
gegen eine Vorgabe ein, von der zwei Prüfbefunde und ein Plan sagen, dass sie an dieser
Stelle falsch ist. **Entblocken kostet eine Architektenentscheidung und sonst nichts** —
bleiben T47, T48 und T50 unberührt, geht das Paket unverändert wieder auf `offen`.

## Was der Geschäftsführer entscheiden lassen muss

**1. Wie kommen die Entwurfsaufgaben in einen Lauf?** Unverändert, zum dritten Mal, und
inzwischen hängen **fünf** Sachen daran: `architekt` und `spielentwerfer` stehen in
`REVIEW`, aber nicht in `BAUROLLEN` (`baulauf.py:49`, heute nachgesehen: unverändert).
Daran hängen 0011 (Stackwechsel in `technik.md`), Punkt 2, Punkt 3, Punkt 4 und der
Schaden aus Gegenkraft 5. Der Plan empfiehlt eine Zeile in `baulauf.py`; ich schliesse
mich unverändert an.

**Neu ist der Preis, und er ist seit heute bezifferbar:** Ein blockiertes Paket auf dem
kritischen Pfad des Kerns. Bis zum 2026-09-02 war die Antwort auf „was kostet das
Vertagen" eine Vermutung; jetzt ist sie ein Status im Frontmatter.

**2. Klasse 2 misst zweierlei — laufende und konstante Preise.** Unverändert aus dem
Prüfbefund zu 0007 vom 2026-09-02, Befund 1, und weiter die schwerste offene Sache. T5
nennt Klasse 2 „Tausend USD zu konstanten Preisen"; darin liegen die 40 Handelsströme aus
CEPII BACI („thousands current USD") und die Wertschöpfungen aus Reihe 1 (konstante
Preise). `durchgriff = teile_gerundet(10.000 · H, H + N)` addiert im Nenner laufende und
konstante Preise und fällt in allen zehn Werten gleichgerichtet zu klein aus; Maß 4 misste
Inflation statt Modellgüte. **Der Prüfbefund zu 0006 nennt dieselbe Lücke ein zweites
Mal** (Nebenbefund 2: Reihe 14 ist die einzige Reihe ohne Angabe zur Preisbasis, und sie
ist die, bei der es klemmt). Zwei Prüfer, zwei Pakete, dieselbe Ursache.

**3. Klasse 4 — trägt sie ihren Deckel auch für Regler?** *Neu, aus dem Prüfbefund zu
0009, Befund 3.* T5 gibt Klasse 4 den Bereich 0 bis 10.000 und sagt, die Bedeutung stehe
„in dieser Tabelle und nirgends sonst". Fünf Klasse-4-Schlüssel in `parameter.toml`
(`preisstoss`, `zustimmung_elastizitaet`, `nachahmer_wirkung`, `hebel_max`,
`innerjahresausschlag_faktor`) tragen `>= 0` ohne obere Schranke; bei `preisstoss` steht
sogar „specs/ nennt keine obere", was nachweislich falsch ist. Beide Lesarten sind aus der
Datei belegbar, und das Paket, das sie einliest, muss sich für eine entscheiden: Mit dem
Deckel ist `hebel_max ≤ 10.000`, der Hebel kann das Fondsvermögen nie übersteigen und
Todesart 1 wird praktisch unerreichbar; ohne ihn hält Klasse 4 ihren zugesagten Bereich
nicht mehr. **Das ist eine Entwurfsfrage und keine Datenfrage** — entweder gehören die
fünf nicht in Klasse 4, oder in T5 fehlt der Satz, der Größe und Regler unterscheidet. Die
Datei kann es: Bei `gegenlobby_satz` steht genau diese Auflösung. Ich habe den Datenbauer
angewiesen, die fünf Schlüssel im Rücklauf **nicht** anzufassen.

**4. Reihe 9 und R = 19.** Der Deckungsbefund ist jetzt geprüft, und der Prüfer hat die
Zahlen unabhängig nachgemessen: Fenster 2001–2020, 20 Stützstellen, **R = 19**, erzwungen
von Reihe 11 USA (Start 2001) und Reihe 9 USA (Ende 2020). Reihe 9 trägt für Deutschland
und China **keine einzige Beobachtung** (`"values":[]`, zweimal bestätigt). Nach T24
heisst das: Reihe streichen oder Quelle ersetzen — beides entscheidet der Spielentwerfer.
Die drei Varianten sind durchgerechnet und stehen im Befund: ohne Reihe 9 wird R = 20,
ohne Reihe 9 und 11 wird R = 24. Keine Variante reisst die Schranke `R ≤ 26`.

**5. „Schaden" in Gegenkraft 5 hat keine Rechenvorschrift.** Unverändert offen seit dem
2026-09-01 (`technik.md` Abschnitt 12, Beobachtung 3). Solange es offen ist, ist
Gegenkraft 5 nicht baubar. Es trifft den Kern erst über `schritt`, also nach 0016 — aber
wenn der Weltschritt an der Reihe ist, ist es zu spät, die Frage dann erst zu stellen.

**6. Wo die Zustandsausgabe wohnt.** Unverändert: 0010 legt die drei Ebenen in den Kasten
`kern`, T13 gibt sie `schnittstelle`. Nicht dringend — 0010 hängt an 0002 und ist damit
mittelbar mit blockiert.

**7. 0003 Einheiten.** Unverändert blockiert; zu entscheiden ist nichts, solange T5 gilt.
**Eine Korrektur gehört dazu:** Die Begründung im Paket stützte sich darauf, dass kein
Agent übersetzen kann und Typprüfung deshalb hier nicht nachweisbar sei. Seit dem
2026-09-02 ist das falsch — `baulauf.py` übersetzt. Der Widerspruch zu T5 bleibt
unberührt, aber das Zusatzargument trägt nicht mehr, und Wrappertypen sind mit einem
Übersetzungslauf das schärfere Werkzeug. Wer die Frage entscheidet, entscheidet sie jetzt
allein nach dem Entwurf. Ich habe die Stelle im Paket korrigiert, statt sie stehen zu
lassen.

## Was als Nächstes ansteht und noch kein Paket ist

**Die Rohdaten hat niemand, und das ist kein Paket, sondern eine Runner-Frage.** `daten/`
enthält vier Textbefunde und keine einzige Datenzeile; `werkzeuge/aufbereitung` liest nach
T23 „die eingefrorenen Rohdateien". Ich habe das am 2026-09-02 als „nächstes grosses
Datenpaket" geführt und korrigiere mich: **Kein Bauagent kann es erledigen.** `Edit` und
`Write` schreiben Text, `WebFetch` liefert aufbereiteten Text, eine Shell hat keine
Baurolle — eine Rohdatei (BACI kommt als Archiv je HS-Fassung) landet so nie auf der
Platte. Das ist derselbe Fall wie der Übersetzer am 2026-09-01: **Wenn eine Rolle ein
Werkzeug nicht haben darf, ihre Arbeit aber ohne dessen Ausgabe wertlos ist, gehört das
Werkzeug in den Runner und seine Ausgabe in eine Datei.** Ein Paket dafür anzulegen hiesse,
Arbeit auszuschreiben, die niemand ausführen kann — genau der Fehler, den ich bei 0011
schon einmal gemacht habe.

Es ist **kein Gate**: `daten.md` sagt für alle vier tragenden Quellen ausdrücklich keine
Registrierung und kein Abonnement. Es kostet kein Geld und keine Rechtsfolge, nur eine
Hand am Runner — dieselbe Hand, die `BAUROLLEN` erweitern müsste.

**Der Jahrgangsbau selbst** (`werkzeuge/aufbereitung`) kann nach `technik.md` Abschnitt 13
von Beginn an parallel laufen und braucht nichts vom Kern. Er wird schreibbar, sobald 0017
die Eingabetabelle liefert; sein Abnahmekriterium braucht aber Daten, an denen er laufen
kann. Deshalb steht er hinter der Rohdatenfrage und nicht davor.

## Zwei Sachen, die vom Tisch bleiben

- **Der Übersetzungslauf** ist grün und wird von den Prüfern bereits als Beleg benutzt —
  der Kern-Prüfer hat ihn am 2026-09-02 unabhängig nachgestellt, der Prüfer von 0013 sich
  ausdrücklich darauf gestützt und dazugesagt, was er damit **nicht** behauptet.
- **Die Rücklaufgrenze** `baulauf.py:RUECKLAUF_MAX = 3` steht. Stand nach diesem Lauf:
  0004, 0006 und 0009 je 1, alle übrigen 0. Ich führe den Zähler im Paket weiter; er
  kostet nichts und macht die Zahl lesbar, ohne Befunddateien zu zählen.
