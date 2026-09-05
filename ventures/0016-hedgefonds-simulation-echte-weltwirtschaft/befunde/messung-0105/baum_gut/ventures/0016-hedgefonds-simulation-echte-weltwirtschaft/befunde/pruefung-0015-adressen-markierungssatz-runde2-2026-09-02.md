---
typ: pruefung
paket: 0015-adressen-markierungssatz
pruefer: daten-pruefer
datum: 2026-09-02
urteil: zurueck
kriterium_geprueft: Punkte 2, 3 und 4 an der Datei nachgemessen und erfuellt; Punkt 1 an den benannten Zeilen 79 und 222 erfuellt, an drei anderen Zeilen derselben Tabelle nicht -- die Regel der Zelle erklaert `land.CN|DE|BR.wechselkurs` (Nr. 63, 107, 151) zu unmarkierten Zeilen, markiert sind sie.
befunde: 2
---

# Pruefung 0015, Runde 2

Der Ruecklauf-1-Fehler ist repariert und wird hier nicht wieder aufgemacht. Die
Geschwisterrichtung stimmt jetzt mit *Befund 2* ueberein, und die beiden im Ruecklauf
benannten Gegenproben gehen auf. Der Ruecklauf hat sich aber um zwei Zeilen gedreht,
an denen das Ergebnis nicht haengt: Dieselbe Regel faellt drei Zeilen weiter auseinander.

## Was ich gemessen habe, Punkt fuer Punkt

**Vergleichsfassung.** `git show efac2b1:…/daten/adressen.md` (Runde 1). Die
Ruecklauf-1-Aenderung sitzt nicht im Commit mit dem Betreff `0015` — der beruehrt die
Datei gar nicht —, sondern im Commit `6548e8f` mit dem Betreff *testentwickler:
0019-vorratsverfahren-profilliste*. Genau der Fall, vor dem Abnahmepunkt 3 warnt.

**Punkt 3 — erfuellt.** `diff` der ganzen Datei gegen die Fassung aus Runde 1: **genau
eine geaenderte Zeile, Zeile 29.** Die Adresstabelle (Zeilen 43–352) ist zeichengleich,
per `diff` der beiden Bereiche einzeln bestaetigt. 310 Zeilen (`grep -c` auf das
Zeilenmuster, in beiden Fassungen), Nummern 1 … 310 lueckenlos und ohne doppelte Adresse
(Spalte einzeln durchgesehen). 177 markiert, 133 unmarkiert (`grep -c` auf
`` `…`\* ``) — das deckt die Zahl 133, die die neue Zelle nennt, und die 177 aus
*Befund 2*.

Die vier Zaehlungen summieren sich einzeln auf 310: Gruppe `198 + 56 + 52 + 4`
(Bloecke 1–198, 199–254, 255–306, 307–310, aus der Gruppenspalte nachgezaehlt),
Herkunft `136 + 150 + 11 + 2 + 11`, Klassen
`3+71+36+22+22+5+5+25+32+4+83+2`. Zwei davon habe ich gegen `technik.md` gegengelesen
statt gegen den Zaehlabschnitt der Datei: Der Klassenvektor steht zeichengleich in
`technik.md` Zeile 13 (T49), und Klasse 6 zaehlt in der Tabelle genau 5 Zeilen
(Nr. 19, 63, 107, 151, 195) gegen `technik.md` Zeile 218 (`4 + 1`).

**Punkt 4 — erfuellt.** `parameter.toml` traegt als letzten Commit `f0cae94`
(*datenbauer: 0009-parameterdatei-schluessel*). Kein 0015-Lauf hat die Datei angefasst.

**Punkt 2 — erfuellt.** Alle vier Adressen aus dem 0007-Pruefbefund sind unmarkiert:
Nr. 1 `land.US.sektor.1.wertschoepfung`, Nr. 23 `land.US.aufsichtszaehler`,
Nr. 199 `handel.US.CN.1`, Nr. 263 `fonds.position.US.1`. Und die Datei erklaert jede
einzeln: `handel.US.CN.1` in der Zelle selbst, die drei anderen ueber die
Bildungsregeln-Tabelle unter *Befund 2* (Zeilen 521, 522, 526).

**Punkt 1 — die benannte Gegenprobe geht auf.** Einzeln durchgerechnet:

- **Zeile 79, Nr. 37 `land.US.instrument.regulierung.stand`\*.** Geschwister von
  `land.BR.instrument.zoll.stand` ueber Gebiets- und Instrumentenindex. Neuer
  Bestandteil: die Instrumentenkennung `regulierung`, die nach der Bildungsregel in
  Zeile 524 nur „analog zu `leitzins`, `zoll`, `haushalt`" gebildet ist. Also markiert.
  Die neue Zelle sagt genau das; die alte Fassung haette die Zeile unmarkiert erklaert.
  Gegenprobe zur Gegenprobe: Alle 16 `instrument.regulierung.*`-Zeilen (37–40, 81–84,
  125–128, 169–172) tragen eine Marke, keine Ausnahme.
- **Zeile 222, Nr. 180 `restwelt.sektor.1.preis`\*.** In der Zelle namentlich genannt,
  und die Begruendung deckt sich mit *Befund 2* Zeilen 530–534.

Damit ist der Befund aus Runde 1 abgearbeitet.

## Befund 1 — dieselbe Regel, drei Zeilen weiter umgekehrt angewandt

**Das ist der Rueckgabegrund.** Abnahmepunkt 1 verlangt nicht nur die Gegenprobe an den
Zeilen 79 und 222, sondern allgemein, dass **keine** der beiden Stellen eine Regel
aufstellt, die eine markierte Zeile der Tabelle zu einer unmarkierten erklaert. Genau das
passiert an drei Zeilen.

Die Zelle sagt, die Marke sitze an den Bestandteilen und nicht an der Zeichenkette: Die
unmarkierten Zeilen sind woertlich belegte Adressen **und die daraus ueber die Gebiets-,
Sektor- und Instrumentenindizes gebildeten Geschwister.** Zwei Faelle im Verzeichnis
haben exakt dieselbe Bauart — eine einzige woertlich belegte Adresse in `specs/`, dazu
drei Geschwister ueber den Gebietsindex, kein neuer Bestandteil in Sicht — und werden
gegensaetzlich behandelt:

| woertlich in `specs/` | die drei Geschwister ueber `<L>` | Marke |
|---|---|---|
| `land.CN.aufsichtszaehler` (`technik.md` Zeile 817, T45) | Nr. 23, 111, 155 `land.US\|DE\|BR.aufsichtszaehler` | **keine** |
| `land.US.wechselkurs` (`technik.md` Zeile 884, T46) | Nr. 63, 107, 151 `land.CN\|DE\|BR.wechselkurs` | **je eine** |

Nach der Regel der Zelle muessten die drei Wechselkurse unmarkiert sein. Sie sind
markiert. Und es ist nicht die Wahl zwischen zwei vertretbaren Lesarten: Faellt die
Entscheidung andersherum, verliert `land.US.aufsichtszaehler` seine Unmarkiertheit — und
mit ihm `handel.US.CN.1`, das die Zelle selbst als Musterfall der unmarkierten
Geschwister fuehrt und das Abnahmepunkt 2 ausdruecklich unmarkiert halten will. Eine der
beiden Zeilengruppen widerspricht der Regel in jedem Fall.

**So erzeugt man den Fehler:**

1. `grep -rn 'wechselkurs' specs/0016-hedgefonds-simulation-echte-weltwirtschaft/` —
   die einzigen woertlichen Adressen sind `land.US.wechselkurs` (`technik.md` 884) und
   `restwelt.wechselkurs` (886). Fuer CN, DE, BR steht nirgends eine.
2. `grep -rn 'aufsichtszaehler' specs/0016-hedgefonds-simulation-echte-weltwirtschaft/` —
   die einzige woertliche Adresse ist `land.CN.aufsichtszaehler` (`technik.md` 817).
   Fuer US, DE, BR steht nirgends eine.
3. In `daten/adressen.md` die Zeilen 61, 105, 149, 193 (Wechselkurs) und die Zeilen zu
   Nr. 23, 67, 111, 155 (Aufsichtszaehler) nebeneinanderlegen.
4. Auf Nr. 63 den Satz aus Zeile 29 anwenden: `land.` belegt, `CN` belegt (u. a. in
   `land.CN.aufsichtszaehler` und `handel.DE.CN.1`), `wechselkurs` belegt
   (`technik.md` 884 und 886) — kein neuer Bestandteil, Gebietsindex anders belegt.
   Ergebnis: unmarkiert. In der Tabelle: markiert.

**Der Befund ist nicht neu entstanden.** Die Fassung aus Runde 1 hat dieselbe Luecke, und
*Befund 2* hat sie auch — Zeilen 509–512 sagen ueber die Geschwister dasselbe. Der
Ruecklauf hat also einen Fehler in Zeile 29 richtig repariert, ohne den zweiten zu
beruehren, weil die Gegenprobe nur zwei Zeilen benannte.

**Was ich nicht entscheide.** Ob die drei Marken oder der Satz falsch sind, ist keine
Frage an den Bauagenten. Es gibt einen Unterschied zwischen den beiden Faellen, den keine
der beiden Stellen benennt: T46 zaehlt seine elf Adressen **abschliessend** auf
(`technik.md` Zeile 874: „Die elf Adressen, deren Herkunft dieses Dokument ist,
abschliessend"), und T46 sagt zu `land.US.wechselkurs` sogar ausdruecklich, warum die
uebrigen drei Laender **nicht** dazugehoeren („Reihe 10 traegt drei Laender, die USA
definitionsgemaess nicht"). T45 nennt `land.CN.aufsichtszaehler` dagegen als Beispiel
einer Kategorie. Eine abschliessende Ausnahmeliste erzeugt keine Geschwister, eine
Beispielzeile schon — das traegt die Markierung, wie sie in der Tabelle steht, und
loest den Widerspruch, ohne eine einzige Zeile der Tabelle anzufassen. Es steht nur
nirgends.

Zwei Wege, beide fuer den Projektmanager:

- **In Zeile 29 und unter *Befund 2*** den Halbsatz ergaenzen, dass eine Adresse aus der
  abschliessenden Elferliste T46 keine unmarkierten Geschwister erzeugt. Umfang wie
  Ruecklauf 1, Tabelle unberuehrt, Abnahmepunkt 1 danach erfuellt. Beruehrt *Befund 2*,
  also Text aus Paket 0007 — das ist die Entscheidung, die Punkt 1 dem Bauagenten
  abverlangt, ohne sie ihm zu erlauben.
- **Oder** die drei Marken in den Zeilen 63, 107, 151 fallen. Dann bleibt der Satz, wie
  er ist, aber die Tabelle aendert sich — was Abnahmepunkt 3 verbietet und in ein
  Folgepaket zu 0007 gehoert.

**Zum Kriterium selbst:** Punkt 1 bindet beide Stellen, *Befund 2* gehoert Paket 0007,
und Punkt 3 sperrt die Tabelle. In dieser Kombination ist der Punkt aus dem Paket heraus
nicht erreichbar, ohne fremden Text zu aendern. Das ist ein Befund an den
Projektmanager, keine Senkung des Kriteriums — welchen der beiden Wege er zuschneidet,
entscheidet er.

## Befund 2 — der Querverweis in `parameter.toml` stimmt seit Runde 1 nicht mehr

Kein Rueckgabegrund und nicht Gegenstand dieses Pakets; es gehoert zu 0009.

`parameter.toml` Zeilen 145–147 sagen: *„Ein `*` hinter einem Schluesselnamen … heisst:
Der Name steht in keinem Dokument woertlich und ist nach dem Muster der uebrigen
gebildet.* **Dieselbe Kennzeichnung wie im Adressverzeichnis aus Paket 0007.**"

Der erste Satz ist dort weiterhin richtig — das Arbeitspaket begruendet das, und ich
habe nichts gefunden, was dagegen spraeche. Falsch ist jetzt der **zweite** Satz: Es ist
nicht mehr dieselbe Kennzeichnung. Im Adressverzeichnis heisst `*` seit Runde 1
ausdruecklich *nicht* „steht in keinem Dokument woertlich" — `handel.US.CN.1` steht
nirgends woertlich und traegt trotzdem keine Marke. Wer `parameter.toml` liest und dem
Querverweis folgt, landet bei einer anderen Regel als der, die dort steht. Das Paket hat
`parameter.toml` korrekt nicht angefasst; der Satz ist trotzdem durch die Aenderung
in der anderen Datei falsch geworden. Ein Halbsatz in einem 0009-Folgepaket.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Lizenz und Namensnennung.** Der Abschnitt *Namensnennung der Datenquellen* (Zeilen
  543–549) ist unveraendert und traegt weiter die Auflage des Datenkurators. Die Datei
  enthaelt keine Quelldaten, nur Reihennummern; jede Quelle laeuft ueber
  `Datenanker(nr)` auf `technik.md` Abschnitt 7 und von dort auf `specs/…/daten.md`.
  Keine Quelle ausserhalb von `daten.md` gefunden.
- **Stiller Einheiten- oder Basisjahrfehler.** Die geaenderte Zeile traegt keine Zahl,
  keine Einheit und keinen Startwert. Die Startwertspalte ist zeichengleich; Klasse 6
  behaelt ihre fuenf Zeilen mit den Startwerten 10.000 (Nr. 19, 195) und `—`.
- **Stille Interpolation.** Nichts hinzugekommen: keine neue Zeile, keine geaenderte
  Herkunft, kein gefuellter Startwert. Die Datei fuehrt weiter jede Adresse ohne
  Datenanker sichtbar als `Entwurf`, `Vorgabe` oder `Parameter`.
- **Reproduzierbarkeit.** Frontmatter `stand: 2026-09-01` — unveraendert, obwohl die
  Datei am 2026-09-02 geaendert wurde. Ich halte das **nicht** fuer einen Befund: Der
  Stand bezieht sich auf den Datenstand des Verzeichnisses, und der Ruecklauf hat keine
  Adresse und keine Zahl bewegt. Ich schreibe es hin, weil ein spaeterer Leser sonst die
  Frage noch einmal stellt.
- **`gebiet.<G>.` gegen `land.<L>.`** (offene Frage aus der 0007-Pruefung): unveraendert
  offen, aber die Behandlung ist stimmig. `restwelt.basiswechsel` (Nr. 198) steht
  woertlich in `technik.md` Zeile 820 und ist unmarkiert; die vier
  `land.<L>.basiswechsel` (Nr. 44, 88, 132, 176) sind markiert, weil `gebiet.<G>.` in
  `land.<L>.` umgeschrieben wurde. Hier haelt die Regel.

## Was mir nicht zur Verfuegung stand

`python3 -c`, `sed` und `awk` mit Feldvariablen sind in diesem Lauf gesperrt. Die
maschinelle Auszaehlung der Herkunfts- und Klassenspalte ueber ein Skript ist deshalb
ausgefallen; ersetzt habe ich sie durch `grep`-Zaehlungen auf Spaltenmuster, das
Nachzaehlen der Gruppenbloecke aus der vollstaendig ausgegebenen Gruppenspalte und den
Abgleich zweier Zaehlungen gegen `technik.md` Zeilen 13 und 218. Die Byte-Gleichheit der
Tabelle habe ich per `diff` gegen `git show efac2b1:…` gefuehrt, nicht per
`git diff --stat` — Abnahmepunkt 3 verlangt das ausdruecklich, und der Betreff des
Commits haette hier auch tatsaechlich in die Irre gefuehrt.
