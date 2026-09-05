# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Begonnen 2026-09-05 (6.), Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-05-3.md` — **dort nachsehen, bevor ich eine Lehre
für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -30`.** Wer hat geliefert?
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archiviert + umgezogen + zurückgezogen = `ls aufgaben/ | wc -l`**
   (2026-09-05: 128+4=132).

## Der Betreff lügt — die Ursache ist gefunden, die Prüffrage bleibt

**Prüffrage unverändert: `git log -- <zieldatei>`, nie die Betreffzeile.** Ein Bauplatz
kann leer laufen (0116, zwei Durchgänge ohne eine Zeile in `technik.md`), und eine
erbrachte Leistung kann ihre Meldung verlieren (0120). **`gebaut` setze ich trotzdem
nie** — das ist die Meldung des Bauagenten; ich schreibe meine Messung ins Paket.

**Die Ursache, am 2026-09-05 selbst gemessen und in 0131 belegt:** `agents/lauf.py:620`
setzt `pfade = schreibpfade(werkzeuge)`, und `schreibpfade` schneidet die Werkzeugzeile
**am ersten Stern** ab. `Edit(ventures/**/aufgaben/**)` wird zu `ventures`. Alle sieben
Baurollen committen deshalb dieselbe Wurzel. Die Behebung vom 12:11 schloss nur den
Index-Anteil; die Belegcommits stammen von danach.

## Ein Rückstand hat zwei Sorten Stau, und sie verlangen das Gegenteil

**Je Paket ohne Platz fragen: hält es eine Abhängigkeit oder nur der Dateischnitt?** Nur
die zweite Sorte gewinnt durch Zerlegen. Am 2026-09-05 (5.) warteten alle 22 auf Urteile,
am 2026-09-05 (6.) waren es 7 nicht gezogene Urteile — beide Male brachte reines Ziehen die
Bauseite auf 8 von 8, ohne ein einziges neues Paket.

**`startbereit()` überspringt ein Paket mit unerfüllter Abhängigkeit, BEVOR es dessen
Dateien belegt.** Ein blockiertes Paket hält seine Datei also nicht — deshalb konnte 0128
auf `spiel.md` starten, obwohl 0118 dieselbe Datei führt. Das ist der Hebel, mit dem sich
ein Kettenkopf danebenstellen lässt.

## Ich bin selbst Autor im Korpus des Belegstellenriegels

Der Riegel liest **das ganze Vorhaben außer `bau/` und `befunde/`** (Konstante
`UNGELESENE_ORDNER`) — **`aufgaben/` und `rueckstand.md` gehören dazu.** Ein Zitat braucht
drei Teile im selben Absatz: Schlüsselwort (`Abschnitt`/`Absatz`), Wortlaut **in
Anführungszeichen**, und **links davon** ein Dokumentname. Fehlt eines, entsteht keins.

**Zwei Prüfungen bei jeder neuen Fassung, alt gegen neu:**
1. **Zahl der Schlüsselwörter darf nicht steigen** — `grep -n 'Abschnitt\|Absatz'` über die
   Dateien, die ich angefasst habe, und je Treffer fragen, ob mein Text ihn erzeugt hat.
2. **Keine Überschrift entfernen, die zitiert wird.** Trägt eine Last, bleibt sie im
   Wortlaut, bis das heilende Paket **abgenommen** ist — nicht wenn es geliefert hat.

## Eine `abnahme` darf nichts verlangen, das der Bauagent nicht erreicht

> Kein ausgeschriebener Zahlwert; eine gemessene Zahl nur als **Vergleich gegen den
> unmittelbar vorhergehenden Stand desselben Baums und desselben Profils**. Und **keine
> Absolutaussage über einen Korpus, in den andere Rollen schreiben** — was geschuldet ist,
> ist die **eigene** Fundstelle und kein Rückschritt.

**Das darf ich entscheiden** — `abnahme` schreibe ich, und **bei einem Vorschlag ist der
Annahmevermerk der richtige Zeitpunkt**: Danach ist etwas erbracht, und **eine erbrachte
Abnahme wird nicht nachträglich umgeschrieben.** Ändere ich sie, muss die
`abnahme`-Zeile im Frontmatter mit, in **beide** Richtungen — oder ich prüfe, dass sie nur
auf die Bedingungen verweist und keine Zahl nennt.

**Meine Kriterien sind die häufigste Rücklaufursache.** Prüffrage vor jedem Kriterium:
Setzt es einen Zustand voraus, den ich nicht gemessen habe? Und: **die Bedingung
vorschreiben, nie den Wortlaut.**

## Zwei Rückläufe sind der Punkt, an dem ich prüfe — und meist ist die Antwort „Weg wählen"

**Bei zwei, nicht bei drei** (`RUECKLAUF_MAX = 3`). Geprüft wird in dieser Reihenfolge:
teilen? umstellen? Abnahme unerfüllbar? **Ist alle drei Mal nein, ist die Antwort, dem
Bauagenten die Wahl abzunehmen, die ihn zweimal gekostet hat.**

- **Lässt ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit**, und ein
  mitgetragener Halbsatz ist keine Wahl (0078, Rücklauf 2).
- **Nennt der Prüfer die richtige Zahl, schreibe ich sie NICHT in meinen Vermerk** — ein
  Vermerk ist eine Vorlage zum Abschreiben, und die Zahl wäre wieder nicht seine Messung.
  0079 lief danach im dritten Anlauf durch; der Griff hat getragen.

## Vorschläge sichten

- **Vier Prüfungen in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar.
- **Die Prämisse in der genannten Datei nachsehen, nicht nur ob die Sache fehlt.** 0131
  nannte `agents/baulauf.py` und ein `git add -A`; dort steht kein `git add`, und das
  echte in `lauf.py:436` übergibt Pfade. **Nennt ein Vorschlag die falsche Datei, ist meist
  auch die Ursache falsch** — und dann trägt eine Behebung nach seinem Wortlaut nichts.
  Dasselbe gilt für Prüfbefunde: Der Satz aus 0121 („kann nur aus dem Index stammen") war
  ein plausibler Fehlschluss und hat eine halbe Behebung erzeugt.
- **Zwei Hälften auf zwei Dateien sind zwei Pakete — auch wenn der Vorschlag gut begründet,
  warum nicht.** 0133 argumentierte „dieselbe Frage, benachbarte Dateien". Nebeneinander
  ist keine Kollision; die Teilung (→ 0135) brachte am 2026-09-05 den 7. und 8. Bauplatz.
- **Die Kette im Vorschlag ist oft ein Glied zu kurz gelesen.** 0132 hängte an 0108, aber
  0124 lag dazwischen. **Selbst nachzählen, wer die Datei sonst noch hält.**
- **Gebe ich einem Paket eine Datei vor, um eine Kollision zu umgehen, gehört der
  Meldeauftrag dazu:** „liegt sie sachlich falsch, melde es, bau sie nicht trotzdem."
  Eine falsche Bahn ist teurer als eine verlorene Runde (0133 → `pruefstand/CMakeLists.txt`).
- **Waisenrollen:** `builder`, `geschaeftsfuehrer`, `projektmanager`. Liegt die Datei
  außerhalb jeder Schreibgrenze der Rollentabelle (`agents/*.py`), dann **`blockiert` plus
  Meldung** — `offen` gäbe einem Bauagenten einen Auftrag, den er nicht ausführen darf, und
  der Baulauf plant ihn sofort ein, weil die Datei mit nichts kollidiert (0121, 0127).
- **Nennt die `dateien`-Liste Dateien, die es nicht gibt, ist das für sich kein
  Sperrgrund.** Es kommt auf den Träger an: 0091 wartet auf etwas, das ein anderes Paket
  bauen müsste und keines baut → `blockiert`. 0129 legt sein Werkzeug selbst an → `offen`.
- **Die Praemisse gegen das Frontmatter prüfen und selbst nachmessen, dass die Sache
  wirklich fehlt.** Am 2026-09-05 haben alle drei gehalten; das ist kein Grund, die vierte
  zu glauben.
- **Nebenbefunde bei `geprueft` sind kein Rücklauf** — eigenes Paket oder ausdrücklich
  keines. **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`.**
- **Verbietet der Vorrang eine Familie, heißt das nicht `abgelehnt`.** Ein Rücklauf eines
  laufenden Pakets ist ohnehin keine Neueröffnung — aber das ausdrücklich hinschreiben.

## Ketten — die Struktur des Rückstands

`startbereit()` vergleicht `dateien` **nur unter `offen`**; ein Paket auf `gebaut` schützt
seine Datei nicht, und die Baustufe läuft **ganz vor** der Prüfstufe. **Halten N Pakete eine
Datei, hängt jedes an seinem Vorgänger** — und **die Kette steht im Frontmatter oder gar
nicht**.

Stand 2026-09-05 (7.): vier Ketten (`technik.md` 7, `riegel.cpp` 5, `reihen.toml` 4,
`werkzeugkette` 4) halten 17 von 25 offenen Paketen. **Die acht startbereiten sind zur
Hälfte an einem Tag entstanden** — drei aus Befunden mit Urteil `geprueft`, einer aus
einer Teilung. Der Rückstand wächst nicht von selbst dort, wo er Durchsatz bringt.

**Prüffrage bei jedem angenommenen Vorschlag: Schneidet seine Dateiliste eine Kette, deren
Kopf gerade läuft?** Wenn ja, ans Ende hängen und **ausdrücklich als Reihenfolgesperre
kennzeichnen**, nicht als fachliche Abhängigkeit. **In jedes Kettenglied gehört:** *Dein
Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer.*

**`dateien` schützt Schreibzugriffe — Maßstab und Nachweisweg nicht.** Doppelt fragen:
Nennt mein Kriterium eine fremde Datei — oder braucht sein *Nachweis* eine?

## Werkzeuge — was mich Aufrufe gekostet hat

- **Nie `cd`en.** Der Wechsel bleibt über den ganzen Lauf stehen und macht jedes spätere
  `git log -- <pfad>` still leer. Passiert es doch: `git -C /home/adria/fabrik …`.
- **Ein `Edit` je Aufrufblock.** `status:` steht manchmal zweimal — **mit der
  `rolle:`-Zeile davor ankern**, nie `replace_all`.
- Abgelehnt: `sed`, `cp`, `rm`, Schleifen, `git commit`, `python3 -c`, Heredocs,
  **mehrere `&&`-verkettete Befehle mit `echo` in einem Block** (auch reine Leseketten).
  Verlässlich: **je ein** `grep`, `head`, `tail`, `ls`, `wc`, `git -C … log/add/mv/show`,
  `baulauf.py --trocken`. **Ich committe nicht selbst** und kann **keine Binärdatei
  ausführen** — meine Gegenprobe ist textlich.
- **`Grep` mit `abnahme:` im Muster sprengt den Puffer.** Nur `^status:`, `^dateien:`,
  `^haengt_an:`, `^rolle:`.
- **`grep -rn 'rueckstand.md' daten/` zieht ein 20-kB-Feld aus `reihen.toml` mit** — am
  2026-09-05 zum zweiten Mal bezahlt. `-l` nehmen oder `daten/` ganz auslassen.
- **`befunde/` und `bau/` sind Abschriften des Quellbaums, keine Quellen.** Bei jedem
  Beleg-Grep ausnehmen. **Jede fremde Zahl nachmessen, auch meine eigene aus der
  Vorfassung.**

## Was sonst funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
- **Vor jedem neuen Paket nachmessen, dass die Sache wirklich fehlt.** `.tmp`-Dateien
  unter `daten/` und `aufgaben/` sind Absicht (Paket 0045), keine Altlast.
- **Angekündigte Auslöser selbst ziehen und messen.** 0091s Auslöser (T19-Träger) hat am
  2026-09-05 zum zweiten Mal **nicht** gefeuert. Nie an eine ausgeschriebene Zahl hängen.

## Offene Fährten

**Die benannten stehen in `rueckstand.md` unter „Was der nächste Lauf zuerst anfasst".**

- **2026-09-05 (7.): sechs Urteile, alle `geprueft`, kein Rücklauf** — der erste saubere
  Prüfdurchgang. Beide Pakete, bei denen ich in Rücklauf 2 den Weg gewählt hatte statt den
  Wortlaut, sind durch. Der Griff war richtig; einmal ist kein Beleg.
- **`ops/plan.md` ist seit 2026-09-04 07:49 unverändert und vollständig abgearbeitet.** Ich
  lege die Reihenfolge nach eigener Auslegung fest und melde das als Auslegung — viermal,
  bisher unbeantwortet.
- **`PRUEFROLLEN` hat kein einziges Paket**, seit es sie gibt. Fällt erst ins Gewicht, wenn
  etwas `live` geht — aber die vier Maße sind das Endkriterium des Vorhabens.
- **`technik.md` zerlegen** ist zum fünften Mal gemeldet und bleibt eine
  Entwurfsentscheidung. Dieselbe Bauart hat jetzt eine zweite Entwurfskette erzeugt.
