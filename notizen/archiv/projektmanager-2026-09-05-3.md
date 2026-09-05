# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Begonnen 2026-09-05 (5.), Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-05-2.md` — **dort nachsehen, bevor ich eine Lehre
für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -30`.** Wer hat geliefert?
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archiviert + umgezogen + zurückgezogen = `ls aufgaben/ | wc -l`**
   (2026-09-05: 119+4=123).

## „Bau 0 Pakete" heißt nicht Kollision — erst messen, dann schneiden

**2026-09-05: 22 offene Pakete, acht freie Plätze, null eingeplant.** Das sah aus wie das
Dateiproblem der drei Fassungen davor. Es war es nicht: **Alle 22 warteten auf eines von
zehn `gebaut`-Paketen**, acht davon mit geschriebenem, nicht gezogenem Urteil. Das reine
Ziehen brachte 0 → 7 Bauplätze, ohne ein einziges neues Paket.

**Die Messung, die die zwei Fälle trennt** — je Paket ohne Platz fragen: *hält es eine
Abhängigkeit oder nur der Dateischnitt?* Nur die zweite Sorte gewinnt durch Zerlegen. Ein
urteilsgestauter Rückstand sieht aus wie ein dateigeklemmter und verlangt das Gegenteil.

## Ich bin selbst Autor im Korpus des Belegstellenriegels

Der Riegel liest **das ganze Vorhaben außer `bau/` und `befunde/`** (Konstante
`UNGELESENE_ORDNER`) — **`aufgaben/` und `rueckstand.md` gehören dazu.**

**2026-09-05, beinahe bezahlt:** In meinem Annahmevermerk zu 0120 stand das Schlüsselwort
des Riegels neben einem Dokumentnamen — in genau der Datei, deren Paket die Fehlerzahl auf
null bringen soll. Ein Zitat braucht drei Teile im selben Absatz: Schlüsselwort
(`Abschnitt`/`Absatz`), Wortlaut **in Anführungszeichen**, und **links davon** ein
Dokumentname. Ohne Anführungszeichen entsteht keins.

**Zwei Prüfungen bei jeder neuen Fassung, alt gegen neu:**
1. **Zahl der Schlüsselwörter darf nicht steigen** (2026-09-05: 1, und zwar `Abschnitt 18`
   ohne Zitat).
2. **Keine Überschrift entfernen, die zitiert wird.** Trägt eine Last, bleibt sie im
   Wortlaut, bis das heilende Paket **abgenommen** ist — nicht wenn es geliefert hat.

## Eine `abnahme` darf nichts verlangen, das der Bauagent nicht erreicht

**Die Regel, erweitert am 2026-09-05 (0120):**

> Kein ausgeschriebener Zahlwert; eine gemessene Zahl nur als **Vergleich gegen den
> unmittelbar vorhergehenden Stand desselben Baums und desselben Profils**. Und **keine
> Absolutaussage über einen Korpus, in den andere Rollen schreiben** — „null Fundstellen
> im Vorhaben" ist unerfüllbar, sobald ein Prüfer währenddessen ein Paket ablegt. Was
> geschuldet ist: die **eigene** Fundstelle und kein Rückschritt.

**Das darf ich entscheiden** — `abnahme` schreibe ich. **Aber eine erbrachte Abnahme wird
nicht nachträglich umgeschrieben.**

**Meine Kriterien sind die häufigste Rücklaufursache** (0002, 0010, 0079). **Prüffrage vor
jedem Kriterium: Setzt es einen Zustand voraus, den ich nicht gemessen habe?** Und: **die
Bedingung vorschreiben, nie den Wortlaut** — ein Satz in Anführungszeichen wandert
ungeprüft in die Datei. Ändere ich eine Abnahme, muss die `abnahme`-Zeile im Frontmatter
mit, in **beide** Richtungen.

## Ein Befund gehört zu einem Bau, nicht zu einem Paket

**Vor dem Nachzug: Ist dieser Befund schon abgearbeitet?** Gegenprobe
**`git log -- <paketdatei>` gegen `git log -- <befunddatei>`**. Das `urteil` im
Frontmatter entscheidet, nicht der Fließtext.

**Der Commit-Betreff lügt regelmäßig, und das ist gemessen:** Am 2026-09-05 lagen die
Befunde zu **0097 und 0072** in Commits, deren Betreff **0087** und **0094** nennt. Wer
nach Betreff sortiert, zieht zwei Urteile nicht. Ursache ist die offene erste Hälfte von
0121 (`pfade` aus der Werkzeugliste der Rolle statt aus `dateien`). **Eine Messung, die
der Zieldatei folgt, ist dagegen immun.**

**Gegenbeispiel derselben Sorte:** 0079 trug einen `zurueck`-Befund von 03:22, den ich um
05:43 verarbeitet hatte; um 06:09 war es neu gebaut. Ein Befund **vor** dem letzten Bau
ist erledigt, das Paket wartet auf sein nächstes Urteil.

## Ketten statt Einzelsperren — die Struktur des Rückstands

`startbereit()` vergleicht `dateien` **nur unter `offen`**. Sobald ein Paket auf `gebaut`
steht, ist sein Anspruch unsichtbar, und die Baustufe läuft **ganz vor** der Prüfstufe.
**Halten N Pakete eine Datei, hängt jedes an seinem Vorgänger** — und **die Kette steht im
Frontmatter oder gar nicht** (Fassung 25 hat eine behauptet, die in drei von fünf fehlte).

Stand 2026-09-05: vier Ketten — `technik.md` (7), `belegstellen_riegel.cpp` (5),
`reihen.toml` (4), `werkzeugkette.cmake` (4).

**Neu gefangen:** 0126 hing nur an einem `fertig`-Paket und wäre sofort neben der Prüfung
seines Kettenkopfs gelaufen. **Prüffrage bei jedem angenommenen Vorschlag: Schneidet seine
Dateiliste eine Kette, deren Kopf gerade läuft?** Wenn ja, ans Ende hängen und
**ausdrücklich als Reihenfolgesperre kennzeichnen**, nicht als fachliche Abhängigkeit.

**In jedes Kettenglied gehört:** *Dein Vorher-Stand ist der dann geltende `HEAD`; such am
Text, nicht an der Zeilennummer.*

**`dateien` schützt Schreibzugriffe — Maßstab und Nachweisweg nicht.** Prüffrage doppelt:
Nennt mein Kriterium eine fremde Datei — oder braucht sein *Nachweis* eine? (0122 misst an
`werte.cpp` auf einem Wegwerfbaum; unbedenklich nur, weil deren Eigentümer `fertig` ist.)

## Vorschläge sichten

- **Vier Prüfungen in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar.
- **Waisenrollen:** `builder`, `geschaeftsfuehrer`, `projektmanager`. Bei
  `projektmanager`: entweder ich führe es aus und schließe mit Verweis, oder ich weise neu
  zu. **Nie auf `offen` stehen lassen** — außer es liegt außerhalb jeder Schreibgrenze
  (0121, `agents/lauf.py`), dann `blockiert` plus Meldung.
- **Die Praemisse gegen das Frontmatter prüfen, nicht gegen die Begründung** — und
  **selbst nachmessen, dass die Sache wirklich fehlt.** Am 2026-09-05 haben alle fünf
  Praemissen gehalten; das ist kein Grund, die sechste zu glauben.
- **Nennt der Vorschlag eine Zahl, die seine Abnahme selbst gemessen haben will, schreibe
  ich sie nicht in meinen Vermerk** (0123). Ein Vermerk ist eine Vorlage zum Abschreiben.
- **Lässt ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit.** Die Wahl
  kommt in **beide** Pakete; ist das zweite `fertig`, in den Rückstand. Bei 0126: den
  belastbareren Nachweis wählen — **was nur am Arbeitsbaum hängt, schlägt was an der
  Commit-Geschichte hängt.**
- **Eine Nummernkollision löst sich oft von selbst** (`umgezogen`/`zurueckgezogen`). Erst
  zusammenfassen, dann umbenennen.
- **Verbietet der Vorrang eine Familie, heißt das nicht `abgelehnt`.** Sitzen alle auf
  einer Datei, kostet `offen` keinen Platz; `vorschlag` kostet jeden Lauf eine Sichtung.
- **Nebenbefunde bei `geprueft` sind kein Rücklauf** — eigenes Paket oder ausdrücklich
  keines. **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`.**

## Wann `blockiert` richtig ist

**Die stärkere Prüffrage ist „Was rückt nach?", nicht „Kann ich die Ursache widerlegen?"**
Hängt etwas daran → melden statt sperren. **Dann schreibe ich ins Paket, was `blockiert`
hier *nicht* heißt.** **Angekündigte Auslöser ziehe ich selbst und messe sie**: 0091s
Auslöser (T19-Träger) hat am 2026-09-05 **nicht** gefeuert — `verlauf.hpp` gibt es nicht.
Ein Auslöser darf nie an einer ausgeschriebenen Zahl hängen (die alte Vier gegen
`GLEICHZEITIG`, inzwischen 8).

**`gebaut` → `offen` darf ich ohne Befund**, und es kostet keinen Rücklauf: `rueckläufe()`
zählt nur Befunddateien mit `urteil: zurueck`. Ich schreibe hinein, dass es keiner ist.

## Werkzeuge — was mich Aufrufe gekostet hat

- **`Edit` braucht den Pfad relativ zur Repo-Wurzel.** **Nie `cd`en**; ein `cd` verschiebt
  ihn dauerhaft, und jedes `Edit` wird danach mit einer Rechtefehler-Meldung abgelehnt.
- **Ein `Edit` je Aufrufblock.** `status:` steht manchmal zweimal — **mit der
  `rolle:`-Zeile davor ankern**, nie `replace_all`.
- Abgelehnt: `sed`, `cp`, `rm`, `for`/`while`-Schleifen, `git commit`, `python3 -c`,
  Heredocs, **mehrere `echo`+`cd` in einem Block**. Verlässlich: `grep`, `head`, `tail`,
  `ls`, `wc`, `git add`/`log`/`mv`/`show`/`diff`, `baulauf.py --trocken`. **Ich committe
  nicht selbst.** Ich kann **keine Binärdatei ausführen** — meine Gegenprobe ist textlich.
- **`Grep` mit `abnahme:` im Muster sprengt den Puffer.** Nur `^status:`, `^dateien:`,
  `^haengt_an:`, `^rolle:`.
- **`grep -rn 'rueckstand.md' daten/` zieht ein 20-kB-Feld aus `reihen.toml` mit.**
  `daten/zwischenstaende/` ausnehmen oder `-l` nehmen.
- **`befunde/` und `bau/` sind Abschriften des Quellbaums, keine Quellen.** Bei jedem
  Beleg-Grep ausnehmen. **Jede fremde Zahl nachmessen, auch meine eigene aus der
  Vorfassung.**

## Was sonst funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
- **Bricht ein Paket zweimal an derselben Stelle ab: erst Reihenfolge, dann teilen** —
  bei **zwei** Rückläufen, nicht bei drei (`RUECKLAUF_MAX = 3`).
- **Vor jedem neuen Paket nachmessen, dass die Sache wirklich fehlt.** `.tmp`-Dateien
  unter `daten/` und `aufgaben/` sind Absicht (Paket 0045), keine Altlast.

## Offene Fährten

**Die benannten stehen in `rueckstand.md` unter „Was der nächste Lauf zuerst anfasst".**

- **Schreibt der Betreiber selbst Pakete, ist das der Vorrang.** Die Liste in `ops/plan.md`
  vom 2026-09-04 ist **vollständig abgearbeitet** und seither nicht erneuert. Ich habe die
  Auslegung **als Auslegung gemeldet** — zweimal, bisher unbeantwortet.
- **`PRUEFROLLEN` hat kein einziges Paket.** Die Prüfstufe läuft leer, seit es sie gibt.
  Fällt erst ins Gewicht, wenn etwas `live` geht.
- **`technik.md` zerlegen** ist zum vierten Mal gemeldet und bleibt eine
  Entwurfsentscheidung. Solange die Kette läuft, ist der Architekt eine Rolle mit **einem**
  Platz.
