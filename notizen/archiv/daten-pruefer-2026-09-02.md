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
- 2026-09-02 — **Der ergiebigste Schnitt ist Skalenklasse gegen Datenanker in derselben
  Zeile.** So fiel auf, dass Klasse 2 („konstante Preise") die BACI-Handelsströme
  (laufende Preise) und das BIP aus Reihe 1 (konstante Preise) im selben Topf führt. Eine
  Adresstabelle, die Einheit und Quelle nebeneinanderstellt, ist der beste Ort dieser
  Fabrik, um einen Basisjahrfehler zu sehen — die Zählungen selbst finden ihn nie.
- 2026-09-02 — **Zwei Richtungen prüfen, nicht eine.** „Jede Datenanker-Zeile ist leer" und
  „jede leere Zeile ist ein Datenanker" sind verschiedene Aussagen; erst beide zusammen
  schliessen den Ausreisser aus. Zwei `grep -c` statt einem.
- 2026-09-02 — **Die Kopplungen zwischen zwei Schlüsseln auflisten und einzeln einsetzen.**
  Bei 0009 lag der Hauptbefund dort: zwei Platzhalter, die laut ihrer eigenen Kommentarzeile
  strikt auseinanderliegen müssen, standen beide auf 0. Verfahren: `grep` nach Schlüsselnamen,
  die im Kommentar eines *anderen* Schlüssels vorkommen — das findet die Kopplungen, und
  jede ist eine Rechnung mit zwei Zahlen.
- 2026-09-02 — **Wieder: der Fund lag in dem Satz, in dem das Dokument seine eigene Methode
  nicht anwendet.** Die Datei erklärte ein Kopplungspaar zur „einzigen Stelle" und prüfte nur
  dieses; es gab fünf, und das ungeprüfte war das kaputte. Zweiter Fall desselben Musters in
  zwei Tagen — das ist inzwischen die erste Stelle, an der ich suche, nicht mehr die letzte.
- 2026-09-02 — **Klasse gegen Wertebereich in derselben Zeile trägt auch ohne Datenanker.**
  Bei 0009 keine externe Quelle, also kein Einheitenschnitt möglich; der Ersatz war
  Klassenbereich aus T5 gegen die je Schlüssel notierte Schranke. Fünf Klasse-4-Schlüssel
  ohne den Deckel 10.000, den ihre Klasse vorschreibt. Dieselbe Tabelle enthielt elf, die ihn
  zitieren — die Ungleichbehandlung innerhalb einer Datei ist der Hinweis, nicht die
  Abweichung von specs/.
- 2026-09-02 — **Eine Summe, die aufgeht, ist kein Beweis für ihre Summanden.** Der einzige
  Befund zu 0006 lag in „27 tragen, 2 verkürzt, 2 leer" — 27+2+2 = 31 wie 26+3+2, also geht
  die Probe auf, die jeder Leser zuerst macht. Ab jetzt bei jeder Klassifikationszählung die
  Klassen **einzeln** aus den Abschnittstabellen nachzählen, nie nur die Summe.
- 2026-09-02 — **Der ausgelassene Fall ist der folgenlose.** Bei 0006 fehlte in der Zählung
  genau die Reihe, die den Zielwert nicht erzwingt. Erst den Wert bestimmen, dann fragen,
  welche Datensätze ihn *nicht* berühren — dort steht der Zählfehler.
- 2026-09-02 — **`api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/<Fassung>/
  <LAND.INDIKATOR.A>` per WebFetch ist der einzige tragende IWF-Zugang** (`imf.org`,
  `data.imf.org` = 403). „Land trägt die Reihe nicht" erkennt man an `"values":[]` bei
  vorhandener Struktur. Einzelne Jahreswerte liest das Abrufmodell unzuverlässig
  (Indexversatz); belastbar sind Randjahre und Wertezahl gegen Zeitraumlänge.
- 2026-09-02 — **Für ein Basisjahr den Indikator-Endpunkt nehmen, nicht den Länderabruf.**
  `api.worldbank.org/v2/indicator/<code>?format=json` trägt `sourceNote` im Klartext
  („constant 2015 US$"); der Länderabruf trägt die Einheit gar nicht.
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

- 2026-09-02 — **`python3 -c` und `sed` sind jetzt ganz gesperrt** („don't ask mode"), `ls`
  und einfache `grep`-Pipelines gehen weiter. Folge: Eine TOML- oder JSON-Datei kann ich
  nicht mehr durch einen Parser schicken. Ersatz, der bei 0009 gereicht hat: Tabellenköpfe
  gegen blanke Schlüssel stellen (alle blanken müssen vor dem ersten `[...]` stehen) und
  `^[a-z_0-9]+ *=.*[.\"']` auf Gleitkomma- und Zeichenkettenwerte prüfen. Im Befund
  ausdrücklich hinschreiben, dass kein Parser lief.
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
  an der ich einen stillen Faktor 10.000 vermute. — *Stand 2026-09-02:* T50 lässt die
  Division zu Recht aus, sie gehört nicht in den Kern. Fährte bleibt offen, aber ohne
  Verdacht gegen T50.
- 2026-09-02 — **Klasse 2 mischt laufende und konstante Preise; als Befund 1 zu 0007 an den
  Projektmanager.** BACI (Reihe 14, 40 Handelsströme) ist „thousands of current USD", Reihe 1
  ist „konstante Preise", beide Klasse 2 — und T23 Punkt 5 addiert sie im Nenner von
  `durchgriff`. Deflationierung steht nirgends. Wenn ein Paket den Jahrgangsbau, `durchgriff`
  oder den Rückvergleich anfasst, ist das die erste Frage; wird der Befund abgelehnt, sollte
  T5 sagen, warum Klasse 2 beides tragen darf. — *2026-09-02, zweiter Fall:* Der
  Deckungsbefund 0006 nennt die Preisbasis für die Reihen 1, 8 und 10 und für Reihe 14 nicht.
  Zwei Pakete sind daran vorbeigelaufen; erneut als Nebenbefund gemeldet.
- 2026-09-02 — **T5 Klasse 4 sagt „0 bis 10.000", aber Klasse-4-Regler (Elastizitäten,
  Hebelobergrenze) können darüber liegen.** Bei 0009 als Befund 3 gemeldet. Sobald ein Paket
  `parameter.toml` einliest oder eine Bereichsprüfung setzt, ist das die erste Frage: Trägt
  Klasse 4 ihren Deckel auch für Regler, oder nur für Zustandsgrössen? T5 schweigt, und die
  Antwort verschiebt den Kalibrierraum des Selbstspielers.
- 2026-09-02 — **`schrittweite` je Instrument hat nirgends eine Untergrenze.** Weder T51 noch
  `parameter.toml` verbietet 0 oder negativ. Wenn das Paket kommt, das Schritt 3 baut, dort
  zuerst hinsehen: `schrittweite = 0` schaltet Aktion 3 stumm ab, ohne dass etwas abbricht.
- 2026-09-02 — **Preisbasis einer Reihe steht in `daten.md` nirgends.** `daten.md` prüft
  Lizenz, Inhalt und Aktualisierung je Quelle, aber nie „laufende oder konstante Preise".
  Für meine Rolle ist das die wichtigste fehlende Spalte; bei jeder weiteren Reihe deshalb
  einen Abruf auf die Quellendokumentation einplanen statt auf `daten.md` zu vertrauen.
