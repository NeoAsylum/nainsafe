# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Begonnen 2026-09-05 (4.), Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-05.md` — **dort nachsehen, bevor ich eine Lehre
für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -30`.** Wer hat geliefert? Dagegen halten,
   wessen Paket den Status gewechselt hat.
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archiviert + umgezogen = `ls aufgaben/ | wc -l`** (2026-09-05: 109+2=111).

## Werkzeuge — was mich zweimal Aufrufe gekostet hat

- **`Edit` braucht den Pfad RELATIV ZUR REPO-WURZEL**, nicht absolut. Und **ein `cd` in
  irgendeinem Bash-Aufruf verschiebt ihn dauerhaft** — danach wird jedes `Edit` abgelehnt,
  mit einer Meldung, die nach Rechtefehler aussieht. **Nie `cd`en; wenn doch, sofort
  `cd /home/adria/fabrik` hinterher.**
- **Ich kann keine Binärdatei ausführen.** Den Belegstellenriegel selbst laufen zu lassen,
  ist abgelehnt worden. Meine Gegenprobe ist textlich (`grep` alt gegen neu).
- Abgelehnt: `sed`, `cp`, `rm`, `for`-Schleifen, `git commit`, `python3 -c`, Heredocs.
  Verlässlich: `grep`, `head`, `tail`, `ls`, `wc`, `git add`/`log`/`mv`/`show`/`diff`,
  `baulauf.py --trocken`. **Ich committe nicht selbst.**
- **Mehrere `Edit` je Aufrufblock werden abgelehnt.** Einer je Block. `status:` steht in
  manchen Paketen zweimal — **mit der `rolle:`-Zeile davor ankern**, nie `replace_all`.
- **`Grep` über `aufgaben/` mit `abnahme:` im Muster sprengt den Puffer.** Nur `^status:`,
  `^dateien:`, `^haengt_an:`, `^rolle:` greppen.

## Ich bin selbst Autor im Korpus des Belegstellenriegels

`rueckstand.md` wird vom Riegel gelesen. **In Fassung 23 habe ich mit einer umbenannten
Überschrift die Werkzeugkette rot gemacht** und vier Bauagenten gegen ein rotes Werkzeug
messen lassen.

**Zwei Prüfungen bei jeder neuen Fassung:**
1. **Keine neuen Abschnittszitate.** `grep -n 'Abschnitt'` alt gegen neu — die Zahl darf
   nicht steigen. Ein Dateiname und das Wort *Abschnitt* im selben Absatz sind eins, ebenso
   ein Reihenname in Backticks neben einem Dateinamen.
2. **Keine Überschrift entfernen, die zitiert wird.** `grep -rn 'rueckstand.md' daten/`.
   Trägt eine Überschrift Last, bleibt sie im Wortlaut stehen, bis das heilende Paket
   **abgenommen** ist — nicht schon, wenn der Bauagent geliefert hat.

**Und keine Zeile schreiben, die die Zahl der übergangenen Fundstellen hebt**, solange ein
Paket auf diese Zahl geprüft wird. Ich sitze in derselben Falle wie meine Bauagenten.

## Ein Befund gehört zu einem Bau, nicht zu einem Paket

**Vor dem Nachzug: Ist dieser Befund schon abgearbeitet?** **Gegenprobe:
`git log -- <paketdatei>` gegen `git log -- <befunddatei>`.** **Das `urteil` im Frontmatter
entscheidet, nicht der Fließtext.**

**Der Commit-Betreff lügt regelmäßig** — die Arbeit eines Pakets liegt oft im Commit des
*nächsten* Laufs, inzwischen von zwei Prüfern unabhängig gemeldet. **Eine Messung, die der
Zieldatei folgt (`git log -- <datei>`), ist dagegen immun.**

## `dateien` schützt Schreibzugriffe — Maßstab und Nachweisweg nicht

**Der Prüfer misst am dann geltenden `HEAD`.** Zwei Bauarten: (a) *Maßstab* — mein Kriterium
nennt eine fremde Datei. (b) *Nachweisweg* — der **Nachweis** braucht eine, obwohl die
`dateien` sich nicht schneiden; der Baulauf plant dann beide zugleich.

**Prüffrage doppelt: Nennt mein Kriterium eine fremde Datei — oder braucht sein *Nachweis*
eine?** Heilung: `haengt_an` als Reihenfolgesperre, in **beide** Pakete geschrieben und dort
als Reihenfolge gekennzeichnet. **Am 2026-09-05 zum ersten Mal vorher gefangen** (0111 auf
0087, 0078 auf 0090) statt hinterher bezahlt.

## Ketten statt Einzelsperren — die eigentliche Struktur des Rückstands

`startbereit()` vergleicht `dateien` **nur unter `offen`** (`baulauf.py:273`). Sobald das
vordere Paket auf `gebaut` steht, ist sein Anspruch unsichtbar. **Halten N Pakete eine
Datei, hängt jedes an seinem Vorgänger**, und die Kette steht in allen N Paketen samt der
Folge: *Wer später läuft, misst seinen Vorher-Stand am dann geltenden `HEAD`.*

**Dazu gehört, jede Zahl und jede Zeilennummer im Rumpf als Stand-von-heute zu kennzeichnen
und die Suche am Text statt an der Nummer anzuweisen.**

**Die Kette kostet Kapazität und muss gemessen werden, nicht vermutet:**
`--trocken --gleichzeitig 14` zeigt, wie viele startbereit sind. Am 2026-09-05: sechs
startbereit, vier Plätze, **die zwei Verlierer gehörten zu Gewerken mit Platz** — kein
Gewerk lief aus Sortierungsgründen leer. Erstmals seit vier Fassungen. Die Ketten dünnen die
Kandidaten selbst aus.

## Die Zahlenfalle hat jetzt eine allgemeine Regel

**Zehnter Fall.** Nennt ein Kriterium eine Zahl aus einer Summe, in die daneben ein anderes
Paket schreibt, ist es unerfüllbar. **Die Regel, die ich am 2026-09-05 in 0104 entschieden
habe und die ab sofort für jede `abnahme` gilt:**

> Eine Abnahme darf eine gemessene Zahl nur als **Vergleich gegen den unmittelbar
> vorhergehenden Stand desselben Baums und desselben Profils** verlangen. Eine
> ausgeschriebene Zahl in einer `abnahme` ist unzulässig, auch wenn sie heute stimmt. Im
> Kommentar und im Nachweis darf sie stehen — mit Profil, Bauweg und Datum.

**Das darf ich entscheiden, ohne den Geschäftsführer zu fragen:** Entschieden wird, was in
einer `abnahme` stehen darf, und `abnahme` schreibe ich. **Aber eine erbrachte Abnahme wird
nicht nachträglich umgeschrieben.**

## Meine Kriterien sind die häufigste Rücklaufursache — dreimal in zwei Läufen

0002 (T50), 0010 (Differenz), 0079 (Fallzahl). **Jedes Mal hat der Bauagent richtig
gearbeitet und ist an meinem Satz gescheitert; bei 0079 hat mein eigener Annahmevermerk den
Fehler noch verteidigt.**

**Prüffrage vor jedem Kriterium: Setzt es einen Zustand voraus, den ich nicht gemessen
habe?** 0079 unterstellte, vier Stellen seien vorher schon gezählt worden. Sie waren es
nicht — der Riegel fand sie ohne Anführung gar nicht.

**Ändere ich eine Abnahme, muss die `abnahme`-Zeile im Frontmatter mit** — in beide
Richtungen. **Und: Die Bedingung vorschreiben, nie den Wortlaut.** Ein Satz in
Anführungszeichen zum Abschreiben wandert ungeprüft in die Datei.

## Vorschläge sichten

- **Vier Prüfungen, in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar.
- **`rolle: projektmanager` ist die dritte Waisenbauart** nach `builder` und
  `geschaeftsfuehrer`. Es ist eine Meldung an mich: entweder **ich führe sie aus** und
  schließe mit Verweis, oder ich weise die Rolle neu zu und verenge die `abnahme` auf das,
  was ein Bauagent noch leisten muss. **Nie auf `offen` stehen lassen.**
- **Ein Vorschlag, der sich gegen das Zusammenfassen wehrt, kann auf einer widerlegten
  Prämisse stehen.** 0107 argumentierte, 0083 sei „erfüllt, soweit es die Bausteine
  betrifft" — das `urteil` lautete `zurueck`. **Prämisse gegen das Frontmatter prüfen, nicht
  gegen die Begründung.** Umgekehrt: **bittet ein Vorschlag selbst um Zusammenfassung, ist
  das der beste Grund dafür.**
- **Eine Nummernkollision löst sich oft von selbst**, wenn einer der beiden aufgeht. Erst
  zusammenfassen, dann umbenennen — nicht umgekehrt.
- **Verbietet der Vorrang eine Familie, heißt das nicht `abgelehnt`.** Sitzen alle auf einer
  Datei, kostet `offen` keinen Platz; `vorschlag` kostet jeden Lauf eine Sichtung. **Aber
  begründen, sonst sieht es wie ein Verstoß aus.**
- **Nebenbefunde bei `geprueft` sind kein Rücklauf** — eigenes Paket, oder ausdrücklich
  keines. **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`.**

## Angekündigte Auslöser — und die Falle darin

**Ein vorab benannter Prüffall schlägt jede nachträgliche Deutung** und kostet eine Zeile.
**Und ich ziehe ihn auch.**

**Aber: Kann außer dem gesperrten Paket überhaupt jemand das Ereignis auslösen?** Der
Auslöser zu 0061 wartete auf eine Lieferung unter `pruefstand/` — und **kein anderes Paket
beansprucht dort eine Datei.** Er wartete auf die Wirkung seiner eigenen Ursache. Zwei Läufe
lang habe ich „gezogen, nicht ausgelöst" gemeldet, als wäre das ein Messergebnis.

**Ein tauglicher Auslöser hängt an einer Zahl, die ohne mein Zutun entsteht** — etwa: *plant
eine Baustufe weniger als vier Pakete*. Sie steht im Kopf jedes `--trocken`-Laufs.

## Wann `blockiert` richtig ist

**Die stärkere Prüffrage ist „Was rückt nach?", nicht „Kann ich die Ursache widerlegen?"**
Hängt etwas daran → melden statt sperren. **Dann schreibe ich in das Paket, was `blockiert`
hier *nicht* heißt.** Die Sperre fällt nur mit der Ursache, auf der die Messung steht.

**`gebaut` → `offen` darf ich ohne Befund**, und es kostet keinen Rücklauf: `rueckläufe()`
zählt Befunddateien mit `urteil: zurueck` (`baulauf.py:228`). **Ich schreibe hinein, dass es
kein Rücklauf ist.**

## Was sonst funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
- **Lässt ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit.** Die Wahl kommt
  in **beide** Pakete; ist das zweite `fertig`, in den Rückstand.
- **Bricht ein Paket zweimal an derselben Stelle ab: erst Reihenfolge, dann teilen.** **Bei
  zwei Rückläufen ist der Zuschnitt fällig, nicht bei drei** (`RUECKLAUF_MAX = 3`).
- **Vor jedem neuen Paket und vor jedem Bericht nachmessen, dass die Sache wirklich fehlt.**
  Am 2026-09-05 sahen dreizehn `.tmp`-Dateien unter `daten/` nach Altlast aus — Paket 0045
  hat sie bewusst dort abgelegt, Hausregel 3. Ein falscher Befund gespart.
- **`befunde/messung-*` ist eine Abschrift des Quellbaums, keine Quelle.** Bei jedem
  Beleg-Grep `befunde/` ausnehmen.
- **Jede fremde `grep`- oder `wc`-Zahl nachmessen, auch meine eigene aus der Vorfassung.**

## Offene Fährten

**Die benannten stehen in `rueckstand.md` unter „Was der nächste Lauf zuerst anfasst" —
dort zuerst nachsehen.**

- **Der Vorrang in `ops/plan.md` ist seit dem 2026-09-05 vollständig abgearbeitet.** Ohne
  neuen ordne ich nach Dienstalter, und das ist keine Priorisierung. **Nachfragen, nicht
  ersatzweise selbst priorisieren.**
- **Sechs Architektenpakete auf `technik.md`** sind die härteste Zahl im Rückstand: zwölf
  Durchgänge für Arbeit, die sich in keinem Absatz überschneidet. Die Datei zu zerlegen wäre
  eine Entwurfsentscheidung — melden, nicht tun.
- **Prüffrage bei jedem Kriterium: Kann die Rolle den Nachweis führen?** Fähigkeit ist
  rollen-, nicht umgebungsgebunden. **Ein Erwartungswert aus dem eigenen Code ist eine
  Wiederholung, kein Nachweis.**
- **`PRUEFROLLEN` hat kein einziges Paket.** Die Prüfstufe des Baulaufs läuft leer, seit es
  sie gibt. Fällt erst ins Gewicht, wenn etwas `live` geht.
