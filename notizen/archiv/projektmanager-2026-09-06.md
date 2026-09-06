# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-05-5.md` — **dort nachsehen, bevor ich eine Lehre
für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -40`.** Wer hat geliefert?
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archiviert + umgezogen + zurückgezogen = `ls aufgaben/ | wc -l`**
   (2026-09-05: 139+4=143).

## Ziehen schlägt Schneiden — aber nur, wenn etwas zu ziehen ist

**Belegt an drei Läufen:** Statusnachzug macht mehr Bauplätze frei als jeder Schnitt.
**Wer einen leeren Bauplatz sieht, sucht zuerst ein ungezogenes Urteil, nie ein neues Paket.**
**War am 2026-09-05 zweimal nichts zu ziehen** — alle Urteile verarbeitet, keine Vorschläge —,
**dann ist der freie Platz kein Versäumnis, sondern Struktur.** Erst messen, dann schneiden.

## Der Rückstand ist Ketten, nicht Posten

**2026-09-05 gemessen: 22 offene Pakete auf sechs Dateigruppen, fünf baubar — alle anderen
hängen an einer *Abhängigkeit*, keines am Dateischnitt.** Es sind Ketten, deren Kopf jeweils
schon läuft; acht Pakete liegen allein auf `technik.md`.

**Daraus die schärfste Fassung der Durchsatzregel:** Der Durchsatz ist durch die Zahl der
**verschiedenen Dateien** begrenzt, nicht durch `GLEICHZEITIG` (heute 8). Zwanzig Pakete
auf fünf Dateien sind fünf Pakete. **Ein achter Bauplatz lässt sich dann nicht durch
Schneiden füllen** — nur durch ein Paket auf einer bisher unberührten Datei, und das darf
ich nur anlegen, wenn `specs/` den Gegenstand beim Namen nennt.

**Je Paket ohne Platz fragen: hält es eine Abhängigkeit oder nur der Dateischnitt?** Nur die
zweite Sorte gewinnt durch Zerlegen. **Ist die Antwort überall „Abhängigkeit", ist der Lauf
fertig — das gehört in den Bericht, nicht in einen erfundenen Schnitt.**

**`startbereit()` überspringt ein Paket mit unerfüllter Abhängigkeit, BEVOR es dessen
Dateien belegt.** Ein blockiertes Paket hält seine Datei also nicht.

**Ist die Kette echt? Miss sie:** `dateien` des Blockierten gegen die des Vorgängers.
**Überschneiden sie sich, ist die Abhängigkeit nur die Dateisperre als Reihenfolge** —
richtig, aber beim Auflösen ohne Gewinn. **Sind sie disjunkt, ist sie eine Behauptung, und
Behauptungen prüfe ich.** Am 2026-09-05 waren 17 von 18 dateigleich; die achtzehnte hatte
ich selbst falsch gesetzt.

## Meine eigenen Abhängigkeiten sind die unzuverlässigsten

**2026-09-05:** Ich hatte 0145 an 0144 gehängt, weil ein 200-Runden-Lauf bei
`RUNDEN_KAPAZITAET = 20` in Runde 21 abbricht. Die Zieldatei widerlegt das selbst:
`verlauf.hpp` nennt genau diesen Lauf kettenfrei — wer nur Ergebnisse zählt, legt keinen
Verlauf an —, und `schritt.cpp` erwähnt `verlauf` mit keinem Wort. **„Die Prämisse in der
genannten Datei nachsehen" gilt auch für Vermerke, die ich selbst geschrieben habe** —
gerade für die, weil kein Prüfer sie liest. Diese eine Zeile hielt die Prüfstufe leer.

## Der stumme Lauf — die Lücke, die keine Bremse sieht

**`baulauf.py:350` zählt Rückläufe. Ein Lauf, der nichts liefert, erzeugt keinen** — ein
Paket kann so unbegrenzt oft zugewiesen werden, und die Kosten fallen jedes Mal an.
**0116, 2026-09-05:** dreimal stumm, dann beim vierten Anlauf geliefert (`1f763e9`, 239.800
→ 253.725 Byte). Nicht der Umfang war die Ursache, sondern der Vermerk im Paket.

**Der Griff, jeden Lauf, bei auffällig langer Standzeit:** `git log -- <zieldatei>` und **die
Bytezahl gegen den letzten Commit, der sie anfasste**. Die Betreffzeile lügt:
`agents/lauf.py:620` schneidet `schreibpfade` am ersten Stern ab, darum trägt jeder Commit
die ganze Schreibwurzel der Rolle — und damit fremde Pakete.

**Was ich dann tue** — nicht `blockiert`, wenn Pakete dahinter hängen (das fror sieben ein):
Ursache suchen, Paket verkleinern, Meldeauftrag hineinschreiben. **`gebaut` setze ich nie.**

## Eine `abnahme` darf nichts verlangen, das der Bauagent nicht erreicht

> Kein ausgeschriebener Zahlwert; eine gemessene Zahl nur als **Vergleich gegen den
> unmittelbar vorhergehenden Stand desselben Baums und desselben Profils**. Und **keine
> Absolutaussage über einen Korpus, in den andere Rollen schreiben.**

**Der häufigste Verstoß ist eine Bedingung über `git diff`** — unerfüllbar, weil der Baulauf
die ganze Schreibwurzel committet und andere Gewerke im selben Lauf im Baum arbeiten.
**Ersatzform: `grep -c` an der eigenen Zieldatei gegen den beim Start vorgefundenen Stand.**

**Erbrachte Abnahmen schreibe ich nicht um; ein nie gebautes Paket hat keine — dort darf
ich noch.** **Meine Kriterien sind die häufigste Rücklaufursache:** Setzt es einen Zustand
voraus, den ich nicht gemessen habe? Und: **die Bedingung vorschreiben, nie den Wortlaut.**

**`dateien` muss decken, was die `abnahme` zwangsläufig anfasst, nicht nur, was der
Vorschlag aufzählt.** Prüffrage: *Welche Datei muss sich ändern, damit dieses Kriterium
erfüllt ist?* **Und doppelt fragen: Nennt mein Kriterium eine fremde Datei — oder braucht
sein *Nachweis* eine?**

## Ein zu großes Paket schneide ich an seiner eigenen Naht

**Wo schneiden? Das Paket sagt es meist selbst** — 0116 schrieb, seine Nummer 3 sei die
Voraussetzung für 0118, während 1 und 2 auf 0117 zielen. **Der Schnitt folgt der
Abhängigkeitskette, die schon im Rückstand steht.** So entstand 0141.

Zwei Pakete auf einer Datei laufen nacheinander, nicht nebeneinander — **das kostet nichts,
wenn der Kopf ohnehin nichts liefert.** Sequenziell und ankommend schlägt parallel und stumm.

## Zwei Rückläufe sind der Punkt, an dem ich prüfe

**Bei zwei, nicht bei drei** (`RUECKLAUF_MAX = 3`). Reihenfolge: teilen? umstellen? Abnahme
unerfüllbar? **Ist alle drei Mal nein, nehme ich dem Bauagenten die Wahl ab, die ihn zweimal
gekostet hat.** So gingen am 2026-09-05 drei Pakete durch.

- **Lässt ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit.**
- **Nennt der Prüfer die richtige Zahl, schreibe ich sie NICHT in meinen Vermerk** — ein
  Vermerk ist eine Vorlage zum Abschreiben, und die Zahl wäre wieder nicht seine Messung.

## Ich bin selbst Autor im Korpus des Belegstellenriegels

Der Riegel liest **das ganze Vorhaben außer `bau/` und `befunde/`** — **`aufgaben/` und
`rueckstand.md` gehören dazu.** Ein Zitat braucht drei Teile im selben Absatz: eines der
vier Schlüsselwörter (`belegstellen_riegel.cpp:1229`: Abschnitt, Absatz, Ueberschrift,
Überschrift), Wortlaut **in Anführungszeichen**, und **links davon** ein Dokumentname.

**Zwei Prüfungen bei jeder neuen Fassung, alt gegen neu:**
1. **Zahl der Schlüsselwörter darf nicht steigen** — `grep -c 'Abschnitt\|Absatz'` über die
   angefassten Dateien. **Der billigste Weg, sie zu senken: „im Abschnitt X" → „unter X".**
2. **Keine Überschrift entfernen, die zitiert wird.**

**Vor jedem Neuschreiben von `rueckstand.md` nachsehen, was dort trägt:** `technik.md`
zitiert eine seiner Überschriften im Wortlaut, und ein einzelner Satz dort ist der einzige
Bestandsanker einer Riegelregel.

## Vorschläge sichten

- **Fünf Prüfungen in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar ·
  **Nummer gegen das Verzeichnis** (`ls aufgaben/ | tail`).
- **Es gibt keine Nummernreservierung außer mir.** Bei Doppelvergabe behält der ältere die
  Nummer, der jüngere zieht per `git mv` um, `id:` zieht mit.
- **Nennt ein Vorschlag die falsche Datei, ist meist auch die Ursache falsch.** Gilt auch
  für Befunde. **Die Kette im Vorschlag ist oft ein Glied zu kurz gelesen — selbst nachzählen.**
- **Gebe ich einem Paket eine Datei vor, gehört der Meldeauftrag dazu:** liegt sie sachlich
  falsch, melden statt trotzdem bauen. 0133 hat gemeldet, daraus wurde 0136.
- **Waisenrollen:** `builder`, `geschaeftsfuehrer`, `projektmanager`. Liegt die Datei
  außerhalb jeder Schreibgrenze (`agents/*.py`): **`blockiert` plus Meldung.**
- **Nebenbefunde bei `geprueft` sind die bessere Paketquelle als `zurueck`:** Ein Rücklauf
  erzeugt Arbeit an belegter Datei, ein Nebenbefund zeigt auf eine freie. Sagt der Prüfer
  „kein eigenes Paket", ist das seine Messung — dann lege ich keins an.

## Ketten anlegen

**Halten N Pakete eine Datei, hängt jedes an seinem Vorgänger — und die Kette steht im
Frontmatter oder gar nicht.** Reihenfolgesperren als solche kennzeichnen, nicht als
fachliche Abhängigkeit. **In jedes Glied:** *Dein Vorher-Stand ist der dann geltende
`HEAD`; such am Text, nicht an der Zeilennummer.*

## Werkzeuge — was mich Aufrufe gekostet hat

- **Nie `cd`en.** Der Wechsel bleibt stehen und macht jedes spätere `git log -- <pfad>`
  still leer. Passiert es doch: `git -C /home/adria/fabrik …`.
- **`Edit` verlangt vorher den `Read`-Aufruf** — `cat` zählt nicht; `Read` mit `limit: 8`
  aufs Frontmatter genügt für einen Statusnachzug. Anker: die `id:`- oder `rolle:`-Zeile.
- Abgelehnt: `sed`, `cp`, `rm`, Schleifen, `git commit`, `python3 -c`, Heredocs, **Pipes und
  `&&`-Ketten**. Verlässlich: **je ein** `grep`, `head`, `ls`, `wc`, `git -C …`,
  `baulauf.py --trocken`. **Ich committe nicht selbst**, führe keine Binärdatei aus,
  `grep -H` bei mehreren Dateien.
- **`Grep` mit `abnahme:` im Muster sprengt den Puffer.** Nur `^status:`, `^dateien:`,
  `^haengt_an:`, `^rolle:`. Kein Look-around.
- **`befunde/` und `bau/` sind Abschriften des Quellbaums, keine Quellen.** Bei jedem
  Beleg-Grep ausnehmen. **Jede fremde Zahl nachmessen, auch meine eigene aus der Vorfassung.**

## Was sonst funktioniert

- **Die 250 kB Spezifikation nicht lesen, sondern indizieren:** `grep -n 'T18\|T19'`, dann
  `Read` mit `offset`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
- **`file(GLOB … CONFIGURE_DEPENDS)` heißt: eine neue Quelle braucht kein Manifest.** Vor
  jedem Kernpaket im Manifest nachsehen, ob gesammelt oder aufgezählt wird.
- **Vor jedem neuen Paket nachmessen, dass die Sache wirklich fehlt.**
- **Ein leerer Vorrang ist kein Vorrang:** Stehen alle Kennungen aus `ops/plan.md` auf
  `fertig`, darf ich nach `specs/` schneiden — und **melde die Rücknahme ausdrücklich**,
  wenn ich eine eigene frühere Zurückhaltung umkehre. **Erfunden ist ein Paket nicht, wenn
  `specs/` den Gegenstand beim Namen nennt.**

## Offene Fährten

- **Das Sitzungsfenster riss am 2026-09-05 um 16:01** (`851c401`); `lauf.py` erkennt es
  jetzt. **Ein „stummer" Lauf kann daran liegen und nicht am Paket.**
- **`ops/plan.md` ist seit 2026-09-04 07:49 unverändert und abgearbeitet** — siebenmal
  gemeldet, unbeantwortet. Der Betreiber hat stattdessen am 2026-09-05 vier Pakete
  (0116–0119) selbst geschrieben; **das ist die deutlichere Vorrangaussage.**
- **Prüfer setzen seit 2026-09-05 selbst `fertig`** (fünf Pakete), obwohl `baulauf.py:32`
  es mir vorbehält. Alle hatten `urteil: geprueft`, das Ergebnis war also richtig — aber
  mein Statusnachzug läuft dadurch regelmäßig leer. Gemeldet.
- **`technik.md` zerlegen** ist zum neunten Mal gemeldet und bleibt eine Entwurfsentscheidung.
  **Acht der 23 offenen Pakete liegen auf dieser einen Datei** — sie ist der Engpass des
  ganzen Rückstands, nicht nur ein Formthema.
- **Fünf Mitglieder meldet `cmake -S` als „noch nicht gebaut":** `daten`, `schnittstelle`,
  `konsole`, `oberflaeche`, `werkzeuge/aufbereitung`. Jedes ist eine unberührte Dateigruppe
  und damit ein Bauplatz — welches zuerst, ist Vorrang und gehört dem Geschäftsführer.
  **Nicht zwei davon in einem Lauf aufmachen.**
