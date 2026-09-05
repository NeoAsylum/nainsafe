# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Begonnen 2026-09-05 (9.), Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-05-5.md` — **dort nachsehen, bevor ich eine Lehre
für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -40`.** Wer hat geliefert?
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archiviert + umgezogen + zurückgezogen = `ls aufgaben/ | wc -l`**
   (2026-09-05: 134+4=138).

## Ziehen schlägt Schneiden — aber nur, wenn etwas zu ziehen ist

**Belegt an drei Läufen:** Statusnachzug macht mehr Bauplätze frei als jeder Schnitt.
**Wer einen leeren Bauplatz sieht, sucht zuerst ein ungezogenes Urteil, nie ein neues Paket.**

**Am 2026-09-05 (9.) war zum ersten Mal nichts zu ziehen:** sieben Urteile, alle schon
verarbeitet, keine Vorschläge offen. **Dann ist der freie Platz kein Versäumnis, sondern
Struktur** — siehe „Der Rückstand ist Ketten". Erst messen, dann schneiden.

## Der Rückstand ist Ketten, nicht Posten

**2026-09-05 gemessen: 24 offene Pakete, 7 baubar — und alle 17 anderen hängen an einer
*Abhängigkeit*, keines am Dateischnitt.** Es sind fünf Ketten, deren Kopf jeweils schon
läuft (0116→0117→0064→0068→0074→0084→0092; 0099→0100→0126; 0105→0106→0115→0130;
0108→0124→0132→0137; 0140→0091).

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

## Der stumme Lauf — die Lücke, die keine Bremse sieht

**`baulauf.py:350` zählt Rückläufe. Ein Lauf, der nichts liefert, erzeugt keinen.** Ein
Paket kann damit **unbegrenzt oft zugewiesen** werden, ohne dass eine Bremse greift; die
Kosten fallen jedes Mal an.

**2026-09-05 an 0116 gemessen:** dreimal zugewiesen (12:58, 13:58, 15:01), Zieldatei
`technik.md` **byte-identisch** zum Stand von 05:51 (239.800 gegen `9e46cfa`), 0 Rückläufe,
kein Logbucheintrag des Bauagenten. Derselbe Fall wie 0026 am 2026-09-04 (dreimal, ~22,60 $).

**Der Griff, jeden Lauf, für jedes Paket mit auffällig langer Standzeit:**
`git log -- <zieldatei>` und **die Bytezahl gegen den letzten Commit, der sie anfasste**.
Die Betreffzeile lügt: `agents/lauf.py:620` schneidet `schreibpfade` am ersten Stern ab,
darum trägt jeder Commit die ganze Schreibwurzel der Rolle. **0116s eigener Commit vom 15:01
enthielt sieben Dateien fremder Pakete.**

**Was ich dann tue** — nicht `blockiert`, wenn Pakete dahinter hängen (das fror sieben ein):
Ursache suchen, Paket verkleinern, Hindernis-Meldeauftrag hineinschreiben. **`gebaut` setze
ich nie**, das ist die Meldung des Bauagenten.

## Eine `abnahme` darf nichts verlangen, das der Bauagent nicht erreicht

> Kein ausgeschriebener Zahlwert; eine gemessene Zahl nur als **Vergleich gegen den
> unmittelbar vorhergehenden Stand desselben Baums und desselben Profils**. Und **keine
> Absolutaussage über einen Korpus, in den andere Rollen schreiben.**

**Der häufigste Verstoß ist eine Bedingung über `git diff`.** 0116 verlangte „`git diff`
zeigt Änderungen ausschließlich in `technik.md`" — unerfüllbar, weil der Baulauf die ganze
Schreibwurzel committet und im selben Lauf andere Gewerke im Baum arbeiten. **Ersatzform:
`grep -c` an der eigenen Zieldatei gegen den beim Start vorgefundenen Stand.**

**Erbrachte Abnahmen schreibe ich nicht um. Ein nie gebautes Paket hat keine erbrachte
Abnahme — dort darf ich noch**, und bei einem Vorschlag ist der Annahmevermerk der richtige
Zeitpunkt. **Meine Kriterien sind die häufigste Rücklaufursache:** Setzt es einen Zustand
voraus, den ich nicht gemessen habe? Und: **die Bedingung vorschreiben, nie den Wortlaut.**

**`dateien` muss decken, was die `abnahme` zwangsläufig anfasst, nicht nur, was der
Vorschlag aufzählt.** Prüffrage: *Welche Datei muss sich ändern, damit dieses Kriterium
erfüllt ist?* **Und doppelt fragen: Nennt mein Kriterium eine fremde Datei — oder braucht
sein *Nachweis* eine?**

## Ein zu großes Paket schneide ich an seiner eigenen Naht

**2026-09-05, 0116:** vier Lieferungen auf der größten Datei des Vorhabens (`technik.md`,
239.800 Byte). Das ist kein Lauf. **Wo schneiden? Das Paket sagt es meist selbst** — 0116
schrieb, seine Nummer 3 sei die Voraussetzung für 0118, während 1 und 2 auf 0117 zielen.
**Der Schnitt folgt der Abhängigkeitskette, die schon im Rückstand steht.** So entstand 0141.

Zwei Pakete auf einer Datei laufen nacheinander, nicht nebeneinander — **das kostet nichts,
wenn der Kopf ohnehin nichts liefert.** Sequenziell und ankommend schlägt parallel und stumm.

## Zwei Rückläufe sind der Punkt, an dem ich prüfe

**Bei zwei, nicht bei drei** (`RUECKLAUF_MAX = 3`). Reihenfolge: teilen? umstellen? Abnahme
unerfüllbar? **Ist alle drei Mal nein, nehme ich dem Bauagenten die Wahl ab, die ihn zweimal
gekostet hat.** Am 2026-09-05 gingen so drei Pakete durch (0078, 0079, 0087).

- **Lässt ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit.**
- **Nennt der Prüfer die richtige Zahl, schreibe ich sie NICHT in meinen Vermerk** — ein
  Vermerk ist eine Vorlage zum Abschreiben, und die Zahl wäre wieder nicht seine Messung.

## Ich bin selbst Autor im Korpus des Belegstellenriegels

Der Riegel liest **das ganze Vorhaben außer `bau/` und `befunde/`** — **`aufgaben/` und
`rueckstand.md` gehören dazu.** Ein Zitat braucht drei Teile im selben Absatz:
Schlüsselwort (`Abschnitt`/`Absatz`), Wortlaut **in Anführungszeichen**, und **links davon**
ein Dokumentname.

**Zwei Prüfungen bei jeder neuen Fassung, alt gegen neu:**
1. **Zahl der Schlüsselwörter darf nicht steigen** — `grep -c 'Abschnitt\|Absatz'` über die
   angefassten Dateien. **Der billigste Weg, sie zu senken: „im Abschnitt X" → „unter X".**
2. **Keine Überschrift entfernen, die zitiert wird.**

**Vor jedem Neuschreiben von `rueckstand.md` nachsehen, was dort trägt:** `technik.md:3078`
zitiert die Überschrift *Was der Geschäftsführer entscheiden lassen muss* im Wortlaut, und
laut 0106 ist **ein einziger Satz** dort der einzige Bestandsanker einer Riegelregel.

## Vorschläge sichten

- **Fünf Prüfungen in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar ·
  **Nummer gegen das Verzeichnis** (`ls aufgaben/ | tail`).
- **Es gibt keine Nummernreservierung außer mir.** Zwei Prüfer vergaben am 2026-09-05 beide
  `0138`. Der ältere behält sie, der jüngere zieht per `git mv` um, `id:` zieht mit.
- **Die Prämisse in der genannten Datei nachsehen, nicht nur ob die Sache fehlt. Nennt ein
  Vorschlag die falsche Datei, ist meist auch die Ursache falsch.** Gilt auch für Befunde.
- **Die Kette im Vorschlag ist oft ein Glied zu kurz gelesen. Selbst nachzählen.**
- **Gebe ich einem Paket eine Datei vor, gehört der Meldeauftrag dazu:** „liegt sie sachlich
  falsch, melde es, bau sie nicht trotzdem." 0133 hat gemeldet, daraus wurde 0136.
- **Waisenrollen:** `builder`, `geschaeftsfuehrer`, `projektmanager`. Liegt die Datei
  außerhalb jeder Schreibgrenze (`agents/*.py`), dann **`blockiert` plus Meldung.**
- **Nebenbefunde bei `geprueft` sind die bessere Paketquelle als `zurueck`:** Ein Rücklauf
  erzeugt Arbeit an einer belegten Datei, ein Nebenbefund zeigt auf eine freie.

## Ketten anlegen

**Halten N Pakete eine Datei, hängt jedes an seinem Vorgänger — und die Kette steht im
Frontmatter oder gar nicht.** Reihenfolgesperren **ausdrücklich als solche kennzeichnen**,
nicht als fachliche Abhängigkeit. **In jedes Kettenglied gehört:** *Dein Vorher-Stand ist
der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer.*

## Werkzeuge — was mich Aufrufe gekostet hat

- **Nie `cd`en.** Der Wechsel bleibt stehen und macht jedes spätere `git log -- <pfad>`
  still leer. Passiert es doch: `git -C /home/adria/fabrik …`.
- **`Edit` verlangt vorher den `Read`-Aufruf** — `cat` zählt nicht; `Read` mit `limit: 8`
  aufs Frontmatter genügt für einen Statusnachzug. Anker: die `id:`- oder `rolle:`-Zeile.
- Abgelehnt: `sed`, `cp`, `rm`, Schleifen, `git commit`, `python3 -c`, Heredocs,
  **Pipes und mehrere `&&`-verkettete Befehle**. Verlässlich: **je ein** `grep`, `head`,
  `ls`, `wc`, `git -C … log/show/mv/add`, `baulauf.py --trocken`. **Ich committe nicht
  selbst** und kann **keine Binärdatei ausführen**. `grep -H` bei mehreren Dateien.
- **`Grep` mit `abnahme:` im Muster sprengt den Puffer.** Nur `^status:`, `^dateien:`,
  `^haengt_an:`, `^rolle:`. Kein Look-around — Alternativen ausschreiben.
- **`befunde/` und `bau/` sind Abschriften des Quellbaums, keine Quellen.** Bei jedem
  Beleg-Grep ausnehmen. **Jede fremde Zahl nachmessen, auch meine eigene aus der Vorfassung.**

## Was sonst funktioniert

- **Die 240 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, oder
  `grep -n 'T18\|T19'` und dann `Read` mit `offset`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
- **`file(GLOB … CONFIGURE_DEPENDS)` heißt: eine neue Quelle braucht kein Manifest.** Vor
  jedem Kernpaket im Manifest nachsehen, ob gesammelt oder aufgezählt wird.
- **Vor jedem neuen Paket nachmessen, dass die Sache wirklich fehlt.**
- **Ein leerer Vorrang ist kein Vorrang:** Stehen alle Kennungen aus `ops/plan.md` auf
  `fertig`, darf ich nach `specs/` schneiden — und **melde die Rücknahme ausdrücklich**,
  wenn ich eine eigene frühere Zurückhaltung umkehre. **Erfunden ist ein Paket nicht, wenn
  `specs/` den Gegenstand beim Namen nennt.**

## Offene Fährten

- **2026-09-05, neu: Das Sitzungsfenster riss um 16:01** (Commit `851c401`) — 1.041
  Fehlläufe, alle vierzig Durchgänge verbraucht, kein Paket vorangekommen. `lauf.py` erkennt
  es jetzt. **Meine Läufe davor und danach hängen nicht zusammen; ein „stummer" Lauf nach
  16:01 kann daran liegen und nicht am Paket.** 0116s drei Läufe lagen davor.
- **0116 ist beim vierten Anlauf.** Liefert es wieder nichts, ist nicht der Umfang die
  Ursache — dann gehört es dem Geschäftsführer, nicht einem fünften Anlauf.
- **`ops/plan.md` ist seit 2026-09-04 07:49 unverändert und abgearbeitet** — sechsmal
  gemeldet, unbeantwortet. Der Betreiber hat stattdessen am 2026-09-05 vier Pakete
  (0116–0119) selbst geschrieben; **das ist die deutlichere Vorrangaussage.**
- **`PRUEFROLLEN` hat kein einziges Paket**, seit es sie gibt.
- **`technik.md` zerlegen** ist zum achten Mal gemeldet und bleibt eine Entwurfsentscheidung.
  **Acht der 24 offenen Pakete liegen auf dieser einen Datei** — sie ist der Engpass des
  ganzen Rückstands, nicht nur ein Formthema.
