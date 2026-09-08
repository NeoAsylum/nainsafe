# Logbuch: architekt

Rotated by the runner on 2026-09-07 at 14789 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht, dritter Beleg steht im Vorgänger: die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

---

## 2026-09-08 — Paket 0172, die Untergrenze des Zollfaktors

**Entschieden: Weg 1, und die Schranke ist allgemeiner als bestellt.** T30 Prüfung 2
bekommt Schranke 8 `instrument_min[i] ≤ land.<l>.instrument.<i>.stand ≤
instrument_max[i]`, 16 Adressen; Nr. 21 bekommt keine Zeile, seine Positivität folgt aus
Schranke 2 (`welt.preis > 0`) und Schranke 8. Neuer Abschnitt 23, dazu vier kleine
Änderungen an T30 und ein Zeiger bei T48 Nr. 21.

### Unsicher, damit der Projektmanager es sieht — vier Stellen

1. **Die Verbreiterung von 4 auf 16 Adressen ist der einzige Schritt über den Auftrag
   hinaus.** Begründet im Abschnitt und dort auch als solcher benannt: T51 schreibt allen
   **vier** Instrumenten einen Wertebereich vor, Prüfung 2 prüfte keinen. Eine Zollzeile
   allein hätte dasselbe Loch für Leitzins, Haushalt und Regulierung offen gelassen und
   dasselbe gekostet. Wer die Verbreiterung für falsch hält, streicht drei von sechzehn
   Adressen — der bestellte Fall bleibt stehen.
2. **Schranke 8 ist eine Prüfstandsschranke, kein Riegel im Lauf.** Sie hat genau den
   Status der sieben vorhandenen. Ist die Kappung in Schritt 3 falsch gebaut, rechnet eine
   ausgelieferte Partie weiter mit negativem Keil; rot wird es erst im Nachtlauf. Das
   steht so im Abschnitt, ist aber die Stelle, an der ein Prüfer mehr verlangen kann.
3. **Mein Satz zum `l`/`g`-Widerspruch hängt an einer eigenen früheren Entscheidung.**
   Ich sage, die beiden Schreibweisen stimmen im *Wert* überein, solange
   `zollstand(RW) = 0` gilt — und genau diese Null ist die Stelle aus Paket 0043, an der
   Abschnitt 18 sagt, ich würde einem Prüfer widerspruchslos folgen. Fällt die Null,
   fällt mein Satz mit. Entschieden habe ich den Widerspruch **nicht**; der Vorbehalt in
   Abschnitt 18 ist unberührt, wie die Abnahme es verlangt.
4. **Die obere Hälfte von Schranke 8 steht auf `PLATZHALTER`.** `instrument_max[zoll]` ist
   nicht kalibriert, und `parameter.toml` merkt selbst an, dass ein zu enger Wert den
   historischen Pfad aus dem Bereich treibt. Bis zur Kalibrierung kann Schranke 8 oben
   falsch rot werden. Im Abschnitt gemeldet, unten kann sie es nie.

### Was funktioniert — drei Funde mit Prüffrage

- **Der Präzedenzfall im Auftrag sagte das Gegenteil dessen, wofür er zitiert war —
  zweite Bestätigung.** Der Vorschlag nannte Nr. 1 (`wechselkurs[g] ≥ 1`) als Beispiel
  für „die Größe bricht selbst ab". `technik.md` schreibt an der Rundungsstelle wörtlich
  „is therefore an invariant (T30 check 2), **not an expectation**". Ein einziges `Grep`
  auf den Begriff hat es gefunden. **Prüffrage bleibt: warum nimmt der Präzedenzfall
  seine Form — aus demselben Grund wie ich?**
- **Eine Kostenzahl im Auftrag ist eine Behauptung, und diese war um Faktor 400 daneben.**
  Der Vorschlag rechnete Weg 2 mit „einem Aufruf je Marktraeumung". T28 sagt selbst
  „within each bisection step come … the tariff wedge per territory": 40 Halbierungen × 2
  Sektoren × 5 Gebiete = 400 je Runde, bei einem Eingang, der sich einmal je Runde
  ändert. **Prüffrage vor jedem Kostenargument: steht der Aufruf in einer Schleife, die
  die Vorgabe an anderer Stelle beziffert?**
- **Der schärfste Schaden stand nicht im Auftrag: nicht der Wert kippt, sondern ein
  Beweis.** Der Vorschlag argumentierte mit negativem Index und Nenner null. Wer die
  Preismischung nach dem Weltpreis ableitet, sieht: T28 beweist die Zulässigkeit der
  Halbierung aus zwei genannten Voraussetzungen und einer ungenannten
  (`10.000 + zollstand ≥ 0`). Unterhalb davon liefert die Halbierung still einen
  Nicht-Gleichgewichtspreis — deterministisch, also korpusfähig. **Prüffrage bei jedem
  Wertebereichsloch: welcher *Beweis* im Dokument nennt die Voraussetzung, die dieser
  Wert verletzt?**
- **Die Zahl der Schranke stand schon in den Daten.** `instrument_min = 0  # FEST (T51)`
  in `parameter.toml` war der Beleg, dass Weg 1 keine neue Zahl erfindet, sondern eine
  vorhandene Vorschrift an die Stelle bringt, die sie prüft. Erster Griff bei jeder
  Schrankenfrage: steht die Zahl schon in `parameter.toml`?

### Was nicht funktioniert

- **`Grep -C 6` über `kern/` kostete 19,7 kB in einem Zug** und wurde ausgelagert, für
  eine Funktion, die ich danach mit einem `Read` von 40 Zeilen hatte. Bei Quelltext erst
  die Zeilennummer holen (der Befund nannte sie), dann eng lesen.

## 2026-09-08 — Paket 0165, T48 Nr. 22, die zwei Zustandseingänge

**Entschieden: Antwort 1, in verschärfter Form.** Nr. 9, 10, 11 bekommen je eine zweite
Lesefassung auf dem `Schreiber` (über `lies_neu`), die `Zustand`-Fassungen bleiben
unangetastet, `schaden` nimmt nur noch den Schreiber. 22 Größen, 23 → 26 Deklarationen.
Steht bei T48 Nr. 22 und ausführlich in neuem Abschnitt 22.

### Unsicher, damit der Projektmanager es sieht — vier Stellen

1. **Die ADR-Frage, und ich habe sie gegen den Vermerk entschieden.** Der Paketvermerk
   legte nahe, dass 0208s Prüfstein („ein Argument entfernen braucht einen ADR") auch für
   `schaden` gilt. Ich habe **nein** gesagt, mit dem Beleg, dass T48 nie eine
   C++-Argumentliste gebunden hat (Nr. 13 und 18–20 nehmen den Schreiber, Nr. 1–12 einen
   Zustand, die Definitionsspalte nennt keins von beidem). Der Satz steht im Abschnitt,
   samt Handgriff für den Prüfer: **liest jemand den Prüfstein allgemein statt als Aussage
   über `schritt`, ist Abschnitt 22 der ADR-Text, und jemand mit Schreibrecht auf
   `decisions/` muss ihn kopieren.** Ich habe es nicht.
2. **Die Gleichheitsprobe (Punkt 3 der Vorschrift) verlangt keine Abnahmebedingung.** Sie
   ist der einzige Halt gegen das Auseinanderdriften der zwei Fassungen; ein Prüfer darf
   sie für Übergriff halten.
3. **Die 26 ist Arithmetik, nicht Messung.** Die 23 habe ich heute an `werte.hpp` von Hand
   gezählt (23 `[[nodiscard]]` ausserhalb `intern`); die 26 wird erst nach dem Bau eine
   gemessene Zahl.
4. **Kollision mit 0197, und sie ist die teuerste offene Stelle.** `0197-schritt-5-reaktion`
   lief möglicherweise neben mir und baut Schritt 5. Baut es einen Aufruf gegen die **alte**
   Signatur `schaden(z, …)`, entsteht genau der Aufrufer, den dieser Abschnitt verbietet —
   und er sieht richtig aus, weil der einzige `Zustand`, den Schritt 5 hat, die Vorrunde ist.
   **Erster Griff des Bauagenten zu 0165: `grep -rn 'werte::schaden' kern/ ventures/`.**

### Was funktioniert — vier Funde, jeder mit einer Prüffrage

- **Ein Argumentpaar, dessen zweites Glied am Aufrufort keinen zulässigen Wert hat, ist
  nicht „ungebunden", sondern falsch.** Der Auftrag stellte drei Antworten und nannte die
  billigste („zwei Eingänge, dazu ein Satz, welcher Zustand gemeint ist") *eine Antwort,
  solange sie dasteht*. Sie war keine: `spiel.md` bucht 56 Adressen als in **Schritt 4**
  geschrieben, der Schaden läuft in **Schritt 5**, und der einzige `Zustand`, den Schritt 5
  hält, ist die Vorrunde. Der Satz wäre entweder unerfüllbar oder falsch gewesen.
  **Prüffrage vor jeder Bindungsvorschrift: Welchen Wert *darf* das zweite Argument am
  Aufrufort tragen? Gibt es keinen, ist die Frage nicht Bindung, sondern Entfernung.**
- **Die eigene Abzählung des Fremddokuments war der ganze Beleg, und sie stand schon da.**
  `spiel.md`, Abschnitt *Wo die Regel läuft*, druckt eine Tabelle „woher / Adressen / Zahl"
  und die Summe 106. Daraus fielen 74 `lies_neu` und die Aufteilung 18 ✓ / 56 ✗ ohne eine
  einzige eigene Zählung. **Ein Dokument, das seine Lesezugriffe selbst bilanziert, prüft
  die Signatur, die von ihm liest.** Erster Griff bei jeder Signaturfrage: hat die Vorgabe
  eine Zugriffsbilanz?
- **Ein Präzedenzfall, den ein Bauagent zitiert, ist eine Behauptung.** Der Kopf von
  `schaden` begründete die zwei Eingänge mit „dieselbe Bauart wie `marktkorb`". Ein `grep`
  auf `marktkorb` in `technik.md` (Zeile 3020: *quantities via `lies_alt`, prices via
  `lies_neu`*) zeigte: Nr. 7 nimmt zwei Zustände, **weil sie sich unterscheiden sollen**.
  Das Gegenteil des hier vorliegenden Falls. **Prüffrage: Warum nimmt der Präzedenzfall
  seine zwei Argumente — aus demselben Grund wie ich?**
- **Die naheliegende Fassung der gewählten Antwort war die Falle.** „Der `Schreiber`
  bekommt einen Lesezugang auf den Stand dieser Runde" liest sich als billigste Variante
  von Antwort 1 und ist das T39-Loch: `neu` beginnt als **Abschrift von `alt`**, ein
  blankes `const Zustand&` liest am Bitfeld vorbei und liefert stillschweigend den
  Vorrundenwert. Der Beleg stand wörtlich im Kasten über `class Schreiber`
  (`schreiber.hpp`: „`lies_neu` entscheidet am Bitfeld und nicht am Wert"). **Fünfte
  Bestätigung von „erst im Bestand suchen": das gebaute Gewerk sagt seine eigene Grenze,
  wenn man den Kopf liest statt die Signatur.**

### Was nicht funktioniert

- **Eine grüne Probe, die das Gegenteil dessen beweist, wonach sie aussieht.**
  `probe_schaden_zollzeile` übergibt als `z` genau den Zustand, aus dem der Schreiber
  gebaut wurde, und schreibt in die Runde nur Instrumentenstände und Weltpreise. Handel,
  Wertschöpfung und Staatsschuld bewegen sich also nie *innerhalb* der Runde — und deshalb
  stimmen 440.000, 3.000, 6.000, 2.100 und verdecken den Fehler vollständig. Das ist der
  Fall aus `lehren.md` 2026-09-06 („eine Prüfung, deren Gegenstand sich nicht bewegen
  *kann*"), diesmal nicht an einer Prüfung, sondern an einer Regressionsprobe.
  **Prüffrage an jede grüne Probe zu einer Rundengrenze: bewegt der Aufbau die Größe, um
  die es geht, innerhalb der Runde?**

## Offene Fährten (aus dem Vorgänger übernommen, alle noch offen)

- **`Konstanten` bleibt in `kern::werte`**, obwohl sein Vertrag seit 0208 weiter ist als
  das Modul. Umzug heute billig (49 von 64 Fundstellen in drei Dateien), später teurer;
  gelassen, weil er nichts kauft, was der Vertragssatz nicht schon kauft.
- **`parameter.toml` sagt im Kopf, die Prüfsumme laufe „ueber diese Datei"**; T10b hat das
  auf die Werte umgestellt. **Das braucht ein Paket beim Datenbauer** — nicht mein Gewerk.
- **`kern/include/kern/werte.hpp` sagt an fünf Stellen „siebzehn"** und muss auf
  zweiundzwanzig (Kernbauer, in Abschnitt 18 gemeldet). Bis dahin ist der Nachweis aus T48
  unvollständig, nicht falsch.
- **`zollstand(RW) = 0` ist abgeleitet, nicht belegt** (Paket 0043, Abschnitt 18). Hier
  würde ich einem Prüfer widerspruchslos folgen. **Seit 0172 hängt ein zweiter Satz
  daran** (Abschnitt 23: `l` und `g` stimmen im Wert überein, *solange* die Null gilt).
- **`spiel.md` schreibt Nr. 21 mit `l`, T48 mit `g`** — ein Widerspruch, kein Schweigen.
  Das braucht ein Paket beim Spielentwerfer; ich habe ihn in Abschnitt 23 benannt und
  ausdrücklich nicht entschieden.
- **806 und 158 (T62)** hängen daran, dass ein Spielland seine sieben Nicht-Politik-Reihen
  nur im Startjahr braucht — folgt aus T58, steht nirgends als Datenvorschrift.
- **Ob der Prüfjahrgang baubar ist, ist eine Behauptung** (25 Stützstellen, 40 Ströme ohne
  Füllung; Verdachtsfall die Leitzinsreihe). Die wahrscheinlichste Stelle, an der das
  Vorhaben an Daten *kippt*.
- **Ob ein Suchbot mit Tiefe 1 für Maß 2 stark genug ist, ist ungeprüft.** Ist er zu
  schwach, misst Maß 2 seine Schwäche.
- **Die Neubasierung (T8) und `soll = 0` in T42 greifen im Prüfjahrgang nie**, sind also
  ungeprüfter Code. Jeder Zweig, den der Nachtlauf nie betritt, braucht eine Auflage.
- **Lehre aus fünf geschlossenen Fährten:** Eine Stelle, die zwei Dokumenten gehört,
  schliesst sich erst, wenn beide Gewerke im selben Zyklus laufen — und der andere zuerst.
  **Zurückgeben kostet dabei nichts.**

