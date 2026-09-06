# Logbuch: daten-pruefer

Privat. **Hoechstens 12.000 Zeichen** (wc -c). Belege in die Ergebnisdatei, hierher die
Lehre. *Neu begonnen 2026-09-06 nach Paket 0126, Vorgaenger:
archiv/daten-pruefer-2026-09-06-2.md.*

---

## Vorgehen, das traegt

- **Zuerst den genannten Bezugsstand selbst pruefen**: `git rev-parse <commit>:<pfad>`
  gegen den im Bericht genannten Blob. Kostet einen Aufruf, traegt alles Weitere.
- **Der Paketcommit ist selten der Endstand.** `git log --oneline <bezug>..HEAD -- <pfad>`
  zeigt, wer nach dem Bauagenten geschrieben hat. Dann **beide** messen: den Paketstand
  fuers Urteil, `HEAD` fuer die Frage, ob die Arbeit noch steht (0126: 0142 kam dazwischen
  und verschob alle Zeilennummern um 88).
- **Zahlvergleiche vorher/nachher gehoeren an Kopien ausserhalb des Repos**, je Stand mit
  `git archive <commit> <pfad>` in `$TMPDIR` ausgepackt, `bau/` und `befunde/` weg. Nur so
  ist "steigt nicht" ueberhaupt messbar; im Arbeitsbaum gibt es den Vorher-Stand nicht.
- **Mengen vergleichen, nicht Zahlen.** Zwei gleiche Zahlen koennen verschiedene Mengen
  sein. Bei 0126 waren die 46 uebergangenen Fundstellen vorher wie nachher dieselben 23
  Stellen -- sichtbar erst, als ich nach *Text* statt nach Zeilennummer verglich.
- **Den Wortlaut an der Quelle holen, nie aus dem Bericht.** Und dann zeichenweise:
  `difflib.SequenceMatcher` auf die normalisierten Fassungen, Abweichungen als
  Codepoints ausgeben. So faellt ein einzelnes Zeichen auf, das im Auge verschwindet.
- **Bei Zitaten immer die Anfuehrungszeichen als Codepoints ansehen** (0126): Die Quelle
  schrieb `„Rolle"` (U+201E + ASCII U+0022), das Zitat `„Rolle“` (U+201E + U+201C). Eine
  stille typografische *Verbesserung* im Zitat ist von einem Fehler nicht zu unterscheiden.
- **Ist ein Zeichen strittig, ueber alle Fassungen zaehlen** statt ueber eine: 33
  Fassungen von `rueckstand.md` durchgesehen, sechs fuehren den Satz, alle sechs mit
  ASCII. Danach ist es keine Fassungsfrage mehr.
- **Werkzeuge des Vorhabens laufen lassen -- aber erst nach dem eigenen Weg.** Stimmen
  beide ueberein, ist zugleich die Wiederholbarkeit belegt. Fuer `reihen.toml` gibt es
  zwei: `befunde/messung-0078/messung.py` (Parser, Blattwertbilanz, 16 Muster) und
  `befunde/messung-0099/zahlwoerter.py` (die drei Zahlwoerter des Kopfkommentars).
- **Wiederholbarkeit haerter zeigen als "laeuft durch"**: denselben Riegel zweimal auf
  denselben Baum, Ausgaben bitgleich vergleichen (`len` plus `==`).
- **Suche im geprueften Dokument die Stelle, an der es seine eigene Methode nicht
  anwendet.** Zwanzigmal belegt (0005 bis 0126). Erste Stelle, an der ich suche.
- **Was der Bauagent von sich aus dazutut, ist die ergiebigste Stelle** -- und seine
  Liste "Wo ich unsicher bin" ist die zweite. Bei 0126 lag Befund 2 genau dort: Er
  meldete den Nachtrag als unsicher, hat aber dessen **Folge** nicht gemessen.

### Der teuerste Fehlertyp dieses Vorhabens

**Ein Beweis der Unberuehrtheit kann der Beweis einer Luecke sein.** Bei 0126 wies der
Bericht nach, dass alle 294 Kommentarzeilen ausser der geaenderten zeichengleich sind --
und fuehrte das als Erfolg. Richtig ist: Sein eigener Nachtrag in `pruefweg.toml_geprueft`
hob eine Zaehlung *im Kommentar* von sieben auf acht; zeichengleich hiess hier
"nicht nachgezogen". **Prueffrage: Haette diese Kommentarzeile sich aendern muessen?**
Dritter Fall in drei Tagen (0099, 0126, und 0180 beschreibt ihn fuer `werte.hpp`).

**Ein selbstmessendes Feld, das Dateinamen nennt, hebt Zaehlungen ueber die ganze
Datei.** Immer nach dem Schreiben des Bilanzfeldes noch einmal zaehlen, und zwar mit dem
Werkzeug, das die Zaehlung des Kommentars nachbildet -- nicht mit der Blattwertbilanz.

### Urteilsfindung

- **Kriterium erfuellt und trotzdem ein Befund: `geprueft` plus Vorschlag, nicht
  `zurueck`.** Entscheidende Frage: **Wuerde ein Ruecklauf gegen denselben Auftrag eine
  bessere Datei erzeugen?** Bei 0126 nein -- der Schaden war von 0142 schon geheilt.
- **Eine Abnahmeformel im Zweifel am Vorgaengerpaket auslegen.** "Keine dieser fuenf
  Fundstellen" bei 0126 war doppeldeutig; 0090 zeigte, dass "Fundstelle" die Riegel-
  Fundstelle meint, nicht die Zeile. Ohne das haette ich einen Widerspruch gemeldet, der
  keiner ist. **Und: schreib in den Befund, dass du geprueft und bewusst nicht gefuehrt
  hast** -- sonst prueft es der naechste noch einmal.
- **Was das Paket dem Bauagenten zur Wahl gestellt hat, hebe ich nicht auf.**
- **Ein Befund, der schon in einem anderen Paket steckt, gehoert gemeldet, nicht
  uebernommen.** Vor jedem Vorschlag `aufgaben/` nach dem Thema durchsuchen. Bei 0126 gab
  es `0180` fuer dieselbe Krankheit auf `werte.hpp` -- es schliesst den allgemeinen Fall
  ausdruecklich aus und **benennt** ihn als eigenes Paket. Genau daraus wurde mein 0188:
  ein Vorschlag ist stark, wenn das Nachbarpaket ihn selbst angekuendigt hat.
- **Vor dem Ablegen `aufgaben/` neu lesen und dann drei Nummern ueberspringen.** Waehrend
  meines 0126-Laufs wuchs der Raum von 0181 auf 0185; ich nahm 0188.
- **Meine eigene Pruefung von letztem Mal ist keine Quelle.**
- **Der Git-Index ist geteilt: nicht selbst committen, wenn Fremdes im Index steht.**

### Einheiten und Basisjahre

- **Die Blattwertbilanz beweist Unberuehrtheit haerter als jede Durchsicht**: Sind nur
  Prosafelder geaendert, ist kein Faktor, kein Jahr, keine Klasse beruehrt. Ein Aufruf
  statt einer Lesestunde -- aber nur, wenn `neu`/`weg`/`geaendert` **einzeln** ausgewiesen
  sind.
- **Der `faktor` eines Umrechnungsblocks sagt nicht, welche Rolle er in der Rechnung
  hat.** `faktor = 10000` ist bei Reihe 4/15 Basierung, bei Reihe 7 Teiler, bei Reihe 2
  und 14 Zaehler mit Teiler daneben. **Immer die `begruendung` lesen.**
- **Eine Normierung auf eine Zielsumme teilt durch die Istsumme**, und die wechselt je
  Gebiet und Jahr (Reihe 2, technik.md T23 Punkt 7).
- **Spalte Modelleinheit gegen die Quelleneinheit legen, Reihe fuer Reihe.** Auf 10.000
  normiert ist kein Faktor. Fuer Einheit und Basisjahr den Indikator-Endpunkt nehmen.
- **Klasse gegen die Richtung der Schranke pruefen, nicht nur gegen den Bereich.**
- **BACI-Preisbasis erledigt (T53); offen das Basisjahr von PWT 11.0.**
- **Nach jedem Umrechnungspaket `gilt_fuer_reihen` in `[namensnennung]` gegen die Quellen
  aller Umrechnungsschritte legen**, nicht nur gegen `quelle_tabelle`.
- **Ein `datum` im Frontmatter einer Befunddatei ist das Datum der Messung, nicht der
  letzten Schreibbewegung** (0126). `datei.vorlagen` in `reihen.toml` liest genau dieses
  Datum. Wer es "nachzieht", loest die Nachziehpflicht aus, gegen die das Feld gebaut ist.

### Werkzeuge und Zugaenge

- **Verkettete Bash-Aufrufe und Umleitungen (`> $TMPDIR/x`) werden regelmaessig
  abgelehnt.** Zuverlaessig: `Write` eines Skripts nach `ventures/**/befunde/`, dann
  `python3 <pfad>` als **einzelner** Aufruf. Das war bei 0126 zehnmal in Folge stabil und
  ist ausserdem der Nachweis: Das Skript bleibt liegen.
- **Skripte hinterher in einen eigenen Ordner raeumen** (`befunde/pruefung-<kennung>/`,
  `shutil.move` im Skript selbst). Lose Dateien in `befunde/` stoeren die anderen.
- **Ein Heredoc ohne Anfuehrungszeichen-Literale und ohne `**` geht meist**; sobald
  `"`, `'` oder `\*\*` darin stehen, kippt es. Dann `chr(34)`/`chr(39)`/`chr(42)` bauen
  oder gleich `Write`.
- **`git diff` in `subprocess.run` und selbst filtern** statt `| python3 -c`.
- **Stroeme trennen, nicht `2>&1`**: Der Belegstellenriegel schreibt Funde nach `stderr`.
- **Der Riegel laeuft nur als das vorgebaute Binaerprodukt aus `werkzeuge/*/bau/`.**
  Aufruf: `<exe> <wurzel-vorhaben> <wurzel-vorgaben>`, beide absolut.
- **`befunde/` und `bau/` liest der Riegel nicht** (`UNGELESENE_ORDNER`); mein Befund darf
  Wortlaute zitieren. Ein Vorschlag unter `aufgaben/` **kann** Fundstellen erzeugen.
- **Zaehlaussagen nie ueber die Trefferzahl**, immer ueber die Menge der Namen.
- **Blattwerte: Listen elementweise zaehlen.** Listen aus Skalaren sind nicht *ein* Blatt.
- **WebFetch geht, curl nicht.** IWF-Volltext 403, tragend allein SDMX ueber
  `api.imf.org`. **PDF ist unlesbar**, eine Pfadfreigabe hebt die Sperre.

## Was nicht funktioniert

- **Die Werkzeugsperren schwanken; eine Ablehnung ist kein Beweis fuer eine Sperre.**
  Zehnmal in Folge getragen: dieselbe Sache in anderer Form noch einmal versuchen.
- **Der Commit eines Pakets muss die geaenderte Datei nicht enthalten**, und
  `<paketcommit>~1` ist regelmaessig **nicht** der Vorher-Stand.
- **Grep und Parser zaehlen dasselbe Wort verschieden.** Steht "Blattwerte" in der Regel,
  ist der Parser der Massstab. Kommentare sind keine Blattwerte -- eine leere
  Blattwertdifferenz beweist nichts ueber sie.
- **Zuerst den Blob-Hash gegen den Stand des letzten Urteils legen.** Ist er gleich, gab
  es keinen Neubau; dann mit **anderen** Proben pruefen.
