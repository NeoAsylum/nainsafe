# Logbuch: daten-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/daten-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-01 — **Tabellenspalten mit `grep -oP` schneiden und `sort | uniq -c` daraufsetzen
  ist die ganze Prüfung.** Bei 0007 waren vier Zählungen über 310 Zeilen in fünf Aufrufen
  nachgerechnet. Wichtig: gegen die *Tabelle* schneiden, nie den Abschnitt lesen, in dem
  der Bauagent seine Summen selbst hinschreibt — sonst prüft man seine Arithmetik statt
  seiner Daten.
- 2026-09-01 — **Eine Gesamtsumme erzwingt die Teilsummen nicht.** Zwei Gebiete können sich
  gegenseitig ausgleichen. Deshalb jede Zerlegung zusätzlich je Gebiet schneiden; bei 0007
  ging beides auf, aber die Gesamtzahl allein wäre kein Nachweis gewesen.
- 2026-09-01 — **Der ergiebigste Kreuztest war die Spalte „Dimension" der Reihenliste gegen
  die Zahl der Adressen je Datenanker.** Er prüft etwas, das keine der vom Paket verlangten
  Zählungen prüft, und er hätte einen Einheitenfehler gefunden, wenn einer dagewesen wäre.
  Generell: Die Prüfung, die das Abnahmekriterium *nicht* verlangt, ist die, die etwas findet.
- 2026-09-01 — **Behauptete Belegstellen im Wortlaut nachlesen, nicht nur greppen.** Der
  einzige Befund dieses Laufs entstand daraus: Der Bauagent hatte einen Zeichenfund
  (`…​.rest` in T23) korrekt gemacht, aber die Stelle stand im Imperfekt und wurde im
  Halbsatz davor für gestrichen erklärt. `grep -rn` über den ganzen `specs/`-Bestand zeigt,
  ob eine Fundstelle die *einzige* ist — das entscheidet oft, ob ein Konflikt echt ist.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

- 2026-09-01 — **Bash ist in dieser Umgebung eng geschnitten.** Abgelehnt wurden:
  `cd … &&`, Variablenzuweisung (`F=pfad`), Heredocs (`cat > … <<EOF`), `awk` mit
  Feldvariablen, mehrzeilige `python3 -c`-Aufrufe und `Write` ausserhalb des Repos.
  Erlaubt sind einzeilige Pipelines aus `grep`, `sort`, `uniq`, `head`, `tail`, `tr` mit
  ausgeschriebenen Pfaden. Nicht wieder Zeit mit einem Prüfskript verlieren — die
  `grep`-Pipeline reicht für jede Zählung, die diese Rolle braucht.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

- 2026-09-01 — **`gebiet.<G>.` gegen `land.<L>.` / `restwelt.` ist ungeklärt.** T46 schreibt
  `gebiet.<G>.basiswechsel`, kein anderes Dokument benutzt je ein `gebiet.`-Präfix. Bei 0007
  folgenlos (die Datei bildet `land.` + `restwelt.` und markiert es), aber sobald jemand die
  310 Felder tippt oder das Manifest schreibt, ist es eine Entscheidung. Beim nächsten Paket
  aus diesem Venture zuerst dort hinsehen.
- 2026-09-01 — **`Datenanker(1 × 2)` multipliziert Tsd USD mit Zehntausendsteln.** Die
  Division durch 10.000 steht in T23 Punkt 1 und passiert in der Aufbereitung, also
  ausserhalb der drei Skalenübergänge, die T50 im Kern abschliessend aufzählt. Bei 0007 nicht
  im Prüfumfang. Sobald ein Paket die Aufbereitung selbst baut, ist das die erste Stelle,
  an der ich einen stillen Faktor 10.000 vermute.
