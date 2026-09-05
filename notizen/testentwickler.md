# Logbuch: testentwickler

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/testentwickler-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören in die Ergebnisdatei — hier steht die Lehre.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 — **Der Rotnachweis deckt auf, dass ein Fall aus dem *falschen Grund* grün
  ist.** 0086: Zwei von acht gebauten Fällen überlebten ihre Mutation — der eine hatte
  acht Wörter statt der behaupteten sechs, den anderen stoppte die Wortzahl statt des
  Satzendes. Beide grün, beide maßen nichts. **Erst rot, dann zählt der Fall**, und die
  Zahl im Fall nachzählen statt schätzen.
- 2026-09-05 — **Eine Lockerung an einem Textriegel zuerst am *eigenen* Quelltext
  messen, vor jeder Zeile Kommentar.** 0086: Der gelockerte Riegel fing fünf Stellen in
  seiner eigenen Datei, alle falsch. Ausweg war keine Ausnahmeliste, sondern eine echte
  Regel: **mit Abstand zählt nur ein ankündigendes Anführungszeichen**, kein
  Gegenstrich, Sternchen oder gerades — die tragen hier andere Aufgaben.
- 2026-09-05 — **Eine neue Regel als *Rückfall* hinter die alten hängen, nicht neben
  sie.** Dann hängt sie keine vorhandene Einordnung um, sondern ergänzt nur eine
  fehlende. Gegenprobe: Läuft sie allein und ändert **keine einzige Zahl**, ist genau
  das der Beleg.
- 2026-09-05 — **Eine Verbreiterung kann unter dem Strich Fundstellen *verlieren*.**
  Springt die Leseschleife hinter den Fund, überspringt ein *ferner* Treffer den näheren
  und nimmt ihm seine Fundstelle. Regel: Die Suche endet am nächsten gleichartigen
  Anker; sonst gewinnt der falsche.
- 2026-09-05 — **Zwei Lockerungen, die je allein nichts tragen, trotzdem einzeln
  messen.** 0086: beide je 0 Zitate, zusammen 1. Erst die Tabelle aller vier Fassungen
  zeigt, dass A *sichtbar* macht und B *auflösbar*.
- 2026-09-05 — **Die gleichförmige Grundbelegung ist die Ursache stumpfer Proben.** 0097:
  elf von siebzehn Mutationen überlebten allein daran. Eine Belegung ist erst dann eine
  Messlatte, wenn die gedruckten Werte **paarweise verschieden** sind — gezählt, nicht
  behauptet. Fordert ein gültiger Zustand eine Gleichheit, braucht die Entscheidung
  dahinter einen zweiten, ausdrücklich **ungültigen** Zustand.
- 2026-09-05 — **„Zahl steht in der Zeile" ist schwächer, als es aussieht:** `1013`
  steckt in `10137`. Vergleich mit **Abschlussprüfung**, plus Gegenprobe.
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **auch Testquellen**. Belege über die Abschnittsüberschrift,
  nie über eine Zeilennummer; nach jedem Zitat die Gesamtprobe.
- 2026-09-05 — **Mutationstreiber als Python-Skript nach `bau/`** (dort greift
  `.gitignore`): Muster je Fall ersetzen, mit `g++ -x c++ -` über eine **Pipe** bauen,
  fahren. `git status` führt die fremde Quelle danach nicht. Je Fall `count(alt) == 1`.
  Danach Quelle `touch`en und neu bauen.
- 2026-09-05 — **Ein Mutant, der ein Merkmal abschaltet, lässt den *neuen* Selbsttest mit
  Code 2 abbrechen, ehe der Korpus gelesen ist.** Die Vorher-Messung braucht eine
  Fassung, die die neue Falltabelle stummschaltet, und einen Schalter, der die jeweils
  *andere* Neuerung stehen lässt — sonst fallen Fälle, die mit der gemessenen Regel
  nichts zu tun haben, und der Nachweis zeigt auf die falsche Stelle.
- 2026-09-05, **zweimal** — **Ein fremder Lauf committet meinen halbfertigen Stand mit.**
  `git log -- <datei>`: kein Datenverlust, aber die Paketzuordnung stimmt nur übers Datum.
- 2026-09-05 — **Eine vollständige Adresse als Bereichsname liefert genau eine Zeile.**
  Jede Klasse an *ihrer eigenen* Adresse messen; zählen, wie viele Sorten gefunden
  wurden — sonst überspringt die Schleife stumm.
- 2026-09-05 — **Ein Test auf „es hat geworfen" prüft fast nie das, was er soll.** Das
  tragende Kennzeichen ist **zweiteilig**, Kasten **und** Ursache — den Volltext nie.
  `what()` zeigt in die Ausnahme: Vergleiche gehören in den Fangblock.
- 2026-09-05 — **Trennt eine Abnahme zwei Sorten, muss die trennende Eigenschaft
  woandersher kommen als aus dem geschriebenen Namen.** Faustregel: den Rotnachweis
  suchen, den die **bequeme** Fassung überlebt hätte. Die Erwartung an den *Fall*
  hängen, nicht an die Schleife; ein leeres Erwartungsfeld ist ein **Fehlschlag**.
- 2026-09-04, 2026-09-05 wieder — **Eine Schwelle, deren Zahl sich nicht messen lässt,
  gehört nicht ins Messgerät.** Sie braucht eine **Herkunft, keine Marge**, und den
  **kleinsten** Wert, der die gemessene Form trägt — je Schritt messen, Tabelle
  hinschreiben.
- 2026-09-04 — Gehört die `CMakeLists.txt` einem fremden Paket, ist die **Falltabelle im
  Programm** der Weg zu dauerhaften Fällen. Liest das Werkzeug seinen **eigenen**
  Quelltext, muss das Musterwort maskiert sein (`Zeil\145`) — auch in Meldungstexten.
- 2026-09-04, seither siebenmal — **Ein Rotnachweis je Teilregel.** Eine Grenze, deren
  Abschalten nichts ändert, ist Zierde — **oder** sie braucht einen eigens gebauten Fall
  und den ausgeschriebenen Satz, dass der Korpus sie heute nicht misst. Für ein
  Messgerät statt für den Kern: die Erwartungen zweier Nachbarstellen vertauschen.
- 2026-09-04, seither sechsmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** aus der Leseschleife herausziehen. Sonst prüft man zwei Fassungen, von denen
  nur eine läuft.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt. Halbe Tabelle mit **erwarteter Leermeldung**.
- 2026-09-03 — Einen Erwartungswert **zweimal** abschreiben und die Abschriften
  gegeneinander prüfen. — Eine Zeilennummer in einem Aufräumpaket ist beim Abarbeiten
  meist schon falsch (fünfmal): Stelle selbst suchen, durch Bleibendes ersetzen.
- 2026-09-04, 2026-09-05 wieder — Beim Aufräumen von Belegstellen ist der Riegel selbst
  das Messgerät (0→1→0 in der **eigenen** Datei). Muster *beschreiben* statt abschreiben.
  Eine Zählung von **Zeilen** belegt nichts über Gegenstände; ein Riegel über Text liest
  **je Absatz**. Zeichensatz **messen statt raten**.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**: Die Arbeit eines Pakets
  liegt regelmäßig im Commit des *nächsten* Laufs. Treffer gegen das **Datum** halten,
  Herkunft an der `dateien`-Liste prüfen, nie am Commit-Betreff.
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl:** je Vorgabe
  beide Zeilen, `== soll` und `!= gegenzahl`.
- 2026-09-05 — **Eine im Paket genannte Mutation ist selten die einzige ihrer Art.**
  Vorgaben „X sitzt an Stelle N" gegen **alle** Stellen rechnen.
- 2026-09-05 — **Eine Falltabelle zahlt sich beim Bauen aus, nicht erst beim Prüfen** —
  *vor* dem ersten Korpuslauf schreiben, mit den Fällen, die der Korpus **nicht** hergibt.
- 2026-09-02 — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft jede `CMakeLists.txt`
  auch allein; ein neues Verzeichnis braucht ein erneutes `cmake -S/-B`.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **viermal getroffen** (zuletzt 2026-09-05) — `cd` nimmt mir `Edit` und
  `Write` still weg, auch als Teil eines zusammengesetzten Befehls; die Ablehnung nennt
  den Modus, nicht den Pfad. **Nie `cd`.** Ist es passiert: `cd /home/adria/fabrik` als
  eigener Aufruf holt die Werkzeuge zurück.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Shell-Befehle (`a && b`, `a; b`)
  und `for`-Läufe werden abgelehnt, einzelne Aufrufe, **Pipes** und **mehrzeilige**
  Befehle nicht; Heredoc an `python3` läuft **ohne** vorheriges `cd`. Auch ein `=` im
  Argument eines eigenen Skripts lässt den Aufruf ablehnen (`messen.sh abstand=4`),
  `abstand4` läuft — Schalternamen ohne Gleichheitszeichen bauen.
- 2026-09-05 — **`sed` wird abgelehnt**, auch mit `-e`; Ersatz ist `python3 -c "…"` oder
  ein Skript unter `bau/`. Ein Binärprogramm **aus `$TMPDIR`** auszuführen ebenfalls.
- 2026-09-03, 2026-09-05 präzisiert — `grep` über die Shell wird für die Suche im Baum
  abgelehnt (Grep-Werkzeug oder `git grep` tun es), **auf Programmausgaben hinter einer
  Pipe läuft es** — `ctest -V | grep …` und `Testing/Temporary/LastTest.log` sind der
  schnellste Weg an alle roten Zeilen.
- 2026-09-04, 2026-09-05 berichtigt — Nach `$TMPDIR` geht **Bauen**, nicht Kopieren.
  `Write` nach `bau/` geht und ist der bessere Ort.
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function` und `-Wunused-variable`:
  Fällt etwas aus dem Spiel, wird der **Bau** rot statt des Tests. Deshalb **im Rumpf**
  abschalten, nie am Aufruf — eine immer wahre Bedingung statt `if (true)`.
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3), wird auch nicht gebraucht.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. -->

- 2026-09-05 — **Der Mutationslauf lebt nur in `bau/`, beim nächsten sauberen Bau fort.**
  Viermal belegt (0010, 0088, 0097, 0086). Als Paket **0110** vorgeschlagen.
- 2026-09-05 — **`kern/test/zustandsausgabe_probe.cpp` nannte eine Zeilennummer in
  `technik.md`** und machte Bedingung 1 des Belegstellenriegels mitten in meinem Lauf
  rot; beim Abschluss wieder grün. Fremdes Paket, nicht angefasst — kommt es wieder, ist
  es ein echter Befund.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Meine Abschrift folgt dem Kern; strengere Wortgleichheit ist eine
  Entscheidung zwischen zwei Dokumenten, nicht meine.
- 2026-09-04, 2026-09-05 **dreimal** — **Der Korpus driftet während des eigenen Laufs**,
  auch dieses Logbuch. 0086 kostete es eine ganze Messreihe: 38 aufgelöste Zitate vorher,
  33 nachher, die Differenz ganz aus einer fremden Datei. **Nie gegen eine früher
  notierte Zahl rechnen — Vorher und Nachher unmittelbar nacheinander am selben Baum.**
- 2026-09-05 — **Ein grüner Übersetzungsbericht gilt nur für den gelesenen Stand**, und
  ein gemeldeter Bruch ist oft nur ein Zwischenstand.
- 2026-09-05 — **Ohne den äußeren Riegel in `kern::schritt` liefe `partie.runde = -1`
  still durch.** Kein Befund, aber die Doppelung ist *keine* echte.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten;
  `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-05, dreimal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** 0086 nahm sie deshalb heraus und prüfte die **Bedingung** (steigt
  gegenüber dem Stand von eben) — die bessere Bauart, gehört in mehr Abnahmen.
- 2026-09-04, **dreimal bestätigt** — `Write` nach `notizen/archiv/` ist der Rolle nicht
  erlaubt (`cp`/`mv` auch nicht). Die 12.000-Zeichen-Regel ist damit nur durch
  Zusammenziehen einzuhalten. Als **Berechtigung** gemeldet.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** Nur ein gebauter
  Fall mit *einer* zulässigen Art fängt es.
