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
- 2026-09-02 — **`WebFetch` auf `api.worldbank.org/v2/...` geht, `curl` in dieser Umgebung
  nicht** (Bash-Freigabe verweigert). Zwei Endpunkte je Reihe: `/v2/sources/2/series/<code>/
  metadata` trägt das Feld `Source`, `/v2/indicator/<code>` dasselbe als
  `sourceOrganization`. Beim Nachprüfen eines Zitats **den jeweils anderen** Endpunkt nehmen
  als der Bauagent — sonst bestätigt derselbe Weg zweimal dasselbe. Achtung: Das
  Aufbereitungsmodell kürzt lange Feldwerte manchmal still; einmal fehlte der Schwanz
  `uri:/publisher:/type:/date accessed:`. Ein zweiter Abruf mit ausdrücklicher Bitte um den
  vollständigen Wert brachte ihn — eine Kürzung ist kein Beleg für eine Abweichung.
- 2026-09-02 — **Der Fund lag in dem Satz, in dem der Befund einer fremden Tabelle glaubte.**
  Er prüfte vier Reihen mustergültig am Wortlaut und nannte den Ersatzweg dann
  „unverdächtig" — übernommen aus der Spalte „Verdacht" der Reihenliste. Ein Abruf zeigte
  dort denselben Drittanbieter. Generalisiert: **Suche im geprüften Dokument die Stelle, an
  der es seine eigene Methode nicht anwendet.** Das ist zuverlässiger als jede Zählung.
- 2026-09-02 — **Die Gegenprobe gehört auch dorthin, wo ich dem Befund zustimme.** Er
  entkräftete `License_Type` mit drei Kontrollen; ich suchte den Fall, der ihn *widerlegen*
  würde (IEA, der restriktivste Anbieter im Bestand) — und auch der trug `CC BY-4.0`. Eine
  bestätigte These ist mehr wert als eine ungeprüfte, und es kostete einen Abruf.
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
- 2026-09-02 — **Die Spalte „Verdacht" der Reihenliste (`technik.md` Abschnitt 7) ist
  unbelegt.** Drei „nein"-Zeilen nachgemessen (Reihen 1, 2, 6), alle drei nennen einen
  Drittanbieter, bei zweien ist es die OECD, die `daten.md` selbst „ungeklaert" nennt. Als
  Befund an den Projektmanager gemeldet. Wenn ein Folgepaket die Reihen 1 oder 2 anfasst,
  ist das die erste Stelle zum Hinsehen — Reihe 2 trägt 12 der 31 Sollreihen.
- 2026-09-01 — **`Datenanker(1 × 2)` multipliziert Tsd USD mit Zehntausendsteln.** Die
  Division durch 10.000 steht in T23 Punkt 1 und passiert in der Aufbereitung, also
  ausserhalb der drei Skalenübergänge, die T50 im Kern abschliessend aufzählt. Bei 0007 nicht
  im Prüfumfang. Sobald ein Paket die Aufbereitung selbst baut, ist das die erste Stelle,
  an der ich einen stillen Faktor 10.000 vermute.
