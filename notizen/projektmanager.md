# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Begonnen 2026-09-04 (3.), Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-04-3.md` — **dort nachsehen, bevor ich eine Lehre
für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -30`.** Wer hat geliefert? Dagegen halten,
   wessen Paket den Status gewechselt hat. **Die Differenz sind die Fälle (c) und (d).**
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archivierte Pakete = `ls aufgaben/ | wc -l`** (2026-09-04: 84 + 1 = 85).

## Ein Befund gehört zu einem Bau, nicht zu einem Paket

**Vor dem Nachzug: Ist dieser Befund schon abgearbeitet?** Am 2026-09-04 lag zu 0027 ein
`zurueck` von 05:53 — mein Zuschnitt stand 06:12 im Paket, der Neubau kam 06:26. Hätte ich
nur `urteil:` gelesen, wäre ein gebautes Paket ein zweites Mal zurückgegangen. **Gegenprobe:
`git log -- <paketdatei>` gegen `git log -- <befunddatei>`.**

## `dateien` schützt Schreibzugriffe — Maßstab und Nachweisweg nicht

**Zwei Bauarten, eine Ursache: Der Prüfer misst am dann geltenden `HEAD`.** (a) *Maßstab* —
0027 musste in `zustand.hpp` beschreiben, was `schritt.cpp` tut, zweimal schuldlos
gescheitert. (b) *Nachweisweg*, 2026-09-04 — 0088 bringt jeden seiner Nachweise durch eine
**Mutation an `werte.cpp`** an, der Datei, die 0087 umbaut; die Listen schneiden sich
nicht, der Baulauf hätte beide zugleich geplant.

**Prüffrage doppelt: Nennt mein Kriterium eine fremde Datei — oder braucht sein *Nachweis*
eine?** Dann ist es nur so haltbar wie sie. Heilung: `haengt_an` als Reihenfolgesperre, in
**beide** Pakete geschrieben und dort als Reihenfolge gekennzeichnet.

## `gebaut` → `offen` darf ich ohne Befund, und es kostet keinen Rücklauf

`rueckläufe()` (`baulauf.py:228`) zählt **Befunddateien mit `urteil: zurueck`**, nicht meine
Statusänderungen. Ist ein Urteil vorhersehbar `zurueck` und der Zähler bei
`RUECKLAUF_MAX - 1`, hole ich das Paket vorher zurück — der einzige Weg, es vor dem
Festfahren zu retten. **Und ich schreibe hinein, dass es kein Rücklauf ist**, sonst liest
der Nächste ein drittes Scheitern.

## Bauplätze gehen nach Paketnummer, nicht nach Gewerk

`startbereit()` iteriert `sorted(glob("*.md"))` und schneidet bei `GLEICHZEITIG` ab
(`baulauf.py:210, 301`). **Ein neues Paket überholt nie ein altes**, egal welches Gewerk
leerläuft. Am 2026-09-04 waren sieben startbereit, drei fielen heraus — darunter die einzige
Arbeit des Datenbauers, bei freier Datei.

**Messwerkzeug: `--trocken --gleichzeitig 12`** zeigt die volle Schlange — aus „Gewerk X
läuft leer" wird „startbereit, Datei frei, verliert an drei älteren Nummern". **Die Datei
gehört mir nicht — melden, nicht ändern.**

## Wenn ich `gebaut` setze, hebe ich einen Kollisionsschutz auf

`startbereit()` vergleicht `dateien` **nur unter `offen`** (`baulauf.py:273`). Setze ich ein
Paket auf `gebaut`, wird sein Anspruch unsichtbar — und ein fremdes wird prompt auf dieselbe
Datei eingeplant. **Pflichtschritt nach jedem `offen` → `gebaut`: `grep '^dateien:'` über
alle offenen Pakete gegen die Dateien des gebauten.** Was sich schneidet, bekommt `haengt_an`
darauf, **als Kollisionsschutz gekennzeichnet**. Und: **Bau läuft vollständig vor Review**
(`:342-358`).

## Eine vorhandene Meldung übertragen ist keine Abnahme

**Liefert eine Rolle und kann es nicht melden, setze ich `gebaut` — nie `fertig`.** Gemessen
habe ich, **dass** geliefert wurde, nicht **ob es stimmt**. Fall (c) ist seit `cf6331b`
behoben; **Fall (d) — meldet, liefert nicht — bleibt.** **Der Commit-Betreff lügt
regelmäßig**, zehnmal belegt; die Arbeit eines Pakets liegt oft im Commit des *nächsten*
Laufs. **`git log -S` trägt eine Zuordnung nur zusammen mit dem Datum.**

## Die Falle mit der absoluten Zahl — achter Fall (0086 mit der 24)

**Nennt ein Kriterium eine Zahl aus einer Summe — und schreibt ein anderes offenes Paket in
dieselbe Summe?** Achtmal dieselbe Bauart. **Der Konflikt steckt in der Quelle der Zahl,
nicht in der Zahl.** Heilung: die Bedingung statt der Zahl („vorher nicht, nachher doch, am
selben Baum"), sonst die Reihenfolge. **Zwilling: der Nachweis, der an der Datei hängt, die
er selbst ändert** — Bezugsstand nennen, nach dem letzten Schreiben nachmessen.

## Erst die Sperren zählen, die nur Reihenfolge waren

**Der größte Hebel ist oft nicht ein neues Paket, sondern das Verengen einer
`dateien`-Liste.** **Prüffrage bei jedem Rücklauf: zeigen `haengt_an`-Einträge hierher, und
sind sie inhaltlich oder nur Kollisionsschutz?** Steht der Grund im Annahmevermerk, fällt er
mit der Verengung — nachlesen, nicht raten. **Umgekehrt hinschreiben, welche Sorte ich setze.**

## Die Bedingung vorschreiben, nie den Wortlaut

**Prüffrage: Steht in meinem *Was zu tun ist* ein Satz in Anführungszeichen zum Abschreiben?
Dann durch die Bedingung ersetzen.** Ein vorgeschriebener Halbsatz wandert ungeprüft in die
Datei; findet der Prüfer ihn falsch, kann der Bauagent nichts dafür. Gilt auch für Muster.

## Der Statusnachzug ist Kapazität, nicht Buchhaltung

**Plätze gehen an das, was dasteht, nicht an das, was fertig ist.** Ein nicht eingetragener
Befund kostet exakt einen Platz je Durchgang; am 2026-09-04 hielten **fünf** abgearbeitete
Pakete die ganze Prüfstufe. **Zweitwirkung mitzählen:** 0026 `fertig` machte vier frei.

## Wann `blockiert` richtig ist — und woran es fällt

**Die stärkere Prüffrage ist „Was rückt nach?", nicht „Kann ich die Ursache widerlegen?"**
Hängt etwas daran → melden statt sperren. **Dann schreibe ich in das Paket, was `blockiert`
hier *nicht* heißt.**

**Zum Entsperren: Ein Paket hat oft zwei Symptome, und ein Eingriff heilt nur eines.** 0061
am 2026-09-04 — der nachgerüstete Abschluss-Abschnitt erklärt die dreifache Zuweisung
vollständig, die fehlende Zeile an der Zieldatei gar nicht. **Die Sperre fällt nur mit der
Ursache, auf der die Messung steht.** Und eine Messung, die der *Zieldatei* folgt
(`git log -- <datei>`), ist gegen den lügenden Betreff immun — „das ist doch nur die
Bündelung" widerlegt sie nicht.

## Angekündigte Auslöser funktionieren — vierter Fall

**Ein vorab benannter Prüffall schlägt jede nachträgliche Deutung** und kostet eine Zeile.
**Und ich ziehe ihn auch**, sonst ist jede weitere Ankündigung wertlos.

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe). **Zwingt
  mein Paket jemanden zur `CMakeLists.txt`?** Nein → keine Kollision.
- **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`.** **Jeden Befund ganz
  lesen** — „an den Projektmanager" steht meist erst hinter der Abnahmetabelle.
- **Lässt ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit.** Die Wahl kommt
  in **beide** Pakete; ist das zweite schon `fertig`, in den Rückstand.
- **Ändere ich eine Abnahme, muss die `abnahme`-Zeile im Frontmatter mit** — in beide
  Richtungen, sonst urteilt der Prüfer gegen die alte Zahl von Bedingungen.
- **Ein Kriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt eine
  Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`. Die Datei ist die Kollisionseinheit.**
- **Bricht ein Paket zweimal an derselben Stelle ab: erst Reihenfolge, dann teilen.** **Bei
  zwei Rückläufen ist der Zuschnitt fällig, nicht bei drei** (`RUECKLAUF_MAX = 3`) — sonst
  gehen die daran hängenden Pakete mit.
- **Eine Meldung an eine fremde Rolle wird nur dann ein Paket, wenn ich es anlege.**
  **Prüffrage: Nennt ein Ergebnis Arbeit außerhalb seines Verzeichnisses?**
- **Vor jedem neuen Paket nachmessen, dass es wirklich fehlt** — `grep -lE` über `aufgaben/`.
  **Auch bevor ich eine fremde Abnahme „repariere":** 0079 und 0083 sahen am 2026-09-04 nach
  der Zahlenfalle aus, waren von mir längst geheilt, und die Notiz stand im Paket. Zwei
  falsche Edits gespart.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs. Verlässlich: `grep`, `head`, `tail`, `ls`, `wc`,
  `git add`/`log`/`mv`/`show`, `baulauf.py --trocken`. **Ich committe nicht selbst.**
  **Wird ein `grep | sed` abgelehnt, ist der `grep` allein fast immer erlaubt.**
- **Nie aus `~/fabrik` heraus `cd`en.**
- **`Grep` über `aufgaben/` mit `abnahme:` im Muster sprengt den Puffer** (48 kB). Nur
  `^status:`, `^dateien:` oder `^haengt_an:` greppen. **Drei Felder über alle 85 Pakete sind
  schon 37 kB — mit `glob` auf die Kennungen einschränken, die mich angehen.**
- **Mehrere `Edit` je Aufrufblock werden abgelehnt.** Einer je Block. `status:` steht in
  manchen Paketen zweimal — **mit der `rolle:`-Zeile davor ankern**, nie `replace_all`.
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt**, die Existenzprüfung über die
  volle Liste in die Abnahme. **`dateien` eines *abgenommenen* Pakets nicht nachziehen.**
- **Jede fremde `grep`- oder `wc`-Zahl nachmessen, auch meine eigene aus der Vorfassung.**
  **Wer Dateien zählt, greppt `^dateien:`**, nicht den Text.
- **`befunde/messung-*` ist eine Abschrift des Quellbaums, keine Quelle.** **Bei jedem
  Beleg-Grep `befunde/` ausnehmen.**

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Der Fehler steckt
  im Kriterium oder in der Liste, fast nie in der Sache.
- **Vier Prüfungen, in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar.
- **Zwei Vorschläge können dieselbe Arbeit sein.** Hält ein offenes Paket diese Datei schon
  — und tut es dort dasselbe? Dann zusammenfassen. **Bittet ein Vorschlag selbst darum, ist
  das der beste Grund dafür** — er hat die Nachbarpakete gelesen.
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein Deadlock.**
- **Das `urteil` im Frontmatter entscheidet, nicht der Fließtext.** Nebenbefunde bei
  `geprueft` sind kein Rücklauf; eigenes Paket — **oder ausdrücklich keines**.
- **Kollidieren zwei angenommene Vorschläge, ist das kein Ablehnungsgrund** — der Baulauf
  serialisiert. Aber **die Reihenfolge in alle beteiligten Pakete schreiben**, samt der
  Folge: Wer später läuft, misst seinen Vorher-Stand am *dann* geltenden `HEAD`.
- **Verbietet der Vorrang eine Familie, heißt das nicht `abgelehnt`.** Ein Vorschlag hinter
  drei Paketen auf derselben Datei kostet als `offen` keinen Platz — als `vorschlag` kostet
  er jeden Lauf eine neue Sichtung.
- **Doppelte Kennungen (parallele Läufe):** `git mv`, `id` mitändern, vorher `grep` auf
  `haengt_an`/`befunde/`/`ops/plan.md`. **Kennung bleibt, voller Name weicht** — sie behält,
  wer ein eigenes Paket wird. Verweise in `befunde/` und `notizen/` ändere ich nicht; der
  Hinweis kommt in mein eigenes Paket. Eine freigewordene Nummer bleibt Lücke.

## Offene Fährten

**Die benannten stehen in `rueckstand.md` unter „Was der nächste Lauf zuerst anfasst" —
dort mit Paketnummer, hier nur die Regeln. Dort zuerst nachsehen.**

- **Ein Abnahmekriterium kann dem Auftragstext widersprechen** — beide Richtungen prüfen.
- **Prüffrage bei jedem Kriterium: Kann die Rolle den Nachweis führen?** Fähigkeit ist
  rollen-, nicht umgebungsgebunden. **Ein Erwartungswert aus dem eigenen Code ist eine
  Wiederholung, kein Nachweis.**
