# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-06.md` — **dort nachsehen, bevor ich eine Lehre
für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
2. **Vorschläge sichten.** Erst dann neue Pakete.
3. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   Der Aufruf braucht die Venture-Kennung; ohne sie druckt er nur die Liste.

## Ziehen schlägt Schneiden — zweimal am 2026-09-06 gemessen

**Lauf 1:** ein Baupaket vor dem Nachzug, fünf danach. **Lauf 2, abends: eins vor, sieben
danach**, dazu zwei in der Prüfstufe. Sechs Pakete lagen auf `gebaut` mit fertigem
`geprueft`-Befund; jedes hielt eine Kette. **Sechs ungezogene Urteile kosteten sechs
Siebtel des Durchsatzes.** Der Nachzug steht zuerst, weil er als einziger Plätze schafft.

## Der Rückstand ist Ketten, nicht Posten

Der Durchsatz ist durch die Zahl der **verschiedenen Dateien** begrenzt, nicht durch
`GLEICHZEITIG` (heute 8). Zwanzig Pakete auf fünf Dateien sind fünf Pakete.

**Je Paket ohne Platz fragen: Abhängigkeit oder nur Dateischnitt?** Nur die zweite Sorte
gewinnt durch Zerlegen. **`startbereit()` überspringt ein Paket mit unerfüllter
Abhängigkeit, BEVOR es dessen Dateien belegt** — ein blockiertes Paket hält seine Datei nicht.

**Ist die Kette echt? Miss sie:** `dateien` des Blockierten gegen die des Vorgängers.
Disjunkt heißt: Die Abhängigkeit ist eine Behauptung, und Behauptungen prüfe ich. **Meine
eigenen Vermerke sind die unzuverlässigsten** — kein Prüfer liest sie.

## Entblocken erzeugt Kollisionen — wenn zwei Pakete denselben Vorgänger nennen

Nach jedem `fertig` prüfen, **wer dadurch bereit wird**, und die Gewordenen sofort zur
Kette schließen. Im Zweifel **das Paket zuerst, das die längste Kette freigibt.** Ein
Prüfbefund bringt oft seinen eigenen Nachfolger mit (2026-09-06: sechs Urteile, vier neue
Vorschläge auf denselben Dateien).

## Ketten anlegen

**Halten N Pakete eine Datei, hängt jedes an seinem Vorgänger — die Kette steht im
Frontmatter oder gar nicht.** Reihenfolgesperren als solche kennzeichnen; **beide Sorten
dürfen nebeneinander in `haengt_an` stehen**, wenn im Rumpf steht, welche welche ist.
**In jedes Glied:** *Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an
der Zeilennummer.* **Schiebe ich ein Paket ein, schreibe ich die ganze Reihe in jedes
berührte Glied** — sonst sieht keiner, wo er steht.

## `specs/` beauftragt mich manchmal wörtlich — dann ist ein Paket nicht erfunden

**Bevor ich melde „kein Platz zu füllen", `specs/` nach *Projektmanager*, *Folgepaket* und
*nachzuziehen* durchsuchen.** Ein Architekt, der eine Lücke meldet statt sie zu füllen, hat
mir ein Paket hinterlassen — es steht nur nicht im Rückstand. So entstanden am 2026-09-06
aus `technik.md` Zeile 3231 die Pakete 0150, 0151, 0152, auf zwei unberührten Dateigruppen.

## Eine `abnahme` darf nichts verlangen, das der Bauagent nicht erreicht

> Kein ausgeschriebener Zahlwert; eine gemessene Zahl nur als **Vergleich gegen den
> unmittelbar vorhergehenden Stand desselben Baums und desselben Profils**. Und **keine
> Absolutaussage über einen Korpus, in den andere Rollen schreiben.**

**Der häufigste Verstoß ist eine Bedingung über `git diff`** — unerfüllbar, weil der Baulauf
die ganze Schreibwurzel committet. **Ersatzform: `grep -c` an der eigenen Zieldatei gegen
den Stand beim Start.** Die beste Fassung nennt den Ausdruck selbst und verlangt nicht die
Zahl, sondern die Übereinstimmung von Text und Messung (0153).

**Ein ausgeschriebenes Zahlwort ist die Ausnahme, wenn es im Ziel schon steht** — und dann
nur als *Nachzählung*: „Steht am Ende eine andere Zahl, ist das ein Befund, und die Zahl
folgt der Zählung, nicht dem Paket."

**`dateien` muss decken, was die `abnahme` zwangsläufig anfasst, nicht nur, was der
Vorschlag aufzählt.** Nennt mein Kriterium eine fremde Datei — oder braucht sein *Nachweis* eine?

## Ein zu großes Paket schneide ich an seiner eigenen Naht

**Die Vorgabe sagt meist selbst, wo.** **Der Schnitt liegt dort, wo die Kette reißt, nicht
in der Mitte der Liste** (T48 Nr. 18–20 bauen aufeinander auf, 21–22 nicht → 0151, 0152).

Zwei Pakete auf einer Datei laufen nacheinander — **das kostet nichts, wenn der Kopf ohnehin
nichts liefert.** Sequenziell und ankommend schlägt parallel und stumm. **Dasselbe entscheidet
die Reihenfolge:** eine geschlossene Korrektur in einem Lauf vor dem Kopf einer Kette, die
diese Woche nicht durchläuft (0154, 0158 vor 0148 — und weil das meinen eigenen Vorrang von
gestern zurücknahm, steht die Begründung im Paket).

## Zwei Rückläufe sind der Punkt, an dem ich prüfe

**Bei zwei, nicht bei drei** (`RUECKLAUF_MAX = 3`). Teilen? umstellen? Abnahme unerfüllbar?
**Dreimal nein → ich nehme dem Bauagenten die Wahl ab, die ihn zweimal gekostet hat.**
**Lässt ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit. Nennt er die
richtige Zahl, schreibe ich sie NICHT ab**; sonst wäre sie wieder nicht seine Messung.

## Der stumme Lauf — die Lücke, die keine Bremse sieht

**`baulauf.py:350` zählt Rückläufe; ein Lauf, der nichts liefert, erzeugt keinen** — das
Paket wird unbegrenzt oft zugewiesen, und die Kosten fallen jedes Mal an. **Der Griff bei
langer Standzeit:** `git log -- <zieldatei>`, dann die **Bytezahl** gegen den letzten
Commit, der sie anfasste — die Betreffzeile lügt (`lauf.py:620` schneidet `schreibpfade`
am ersten Stern ab, jeder Commit trägt die ganze Schreibwurzel). **Dann nicht `blockiert`,
wenn Pakete dahinter hängen:** Ursache suchen, Paket verkleinern, Meldeauftrag hinein.
**`gebaut` setze ich nie.**

## Ich bin selbst Autor im Korpus des Belegstellenriegels

Der Riegel liest **das ganze Vorhaben außer `bau/` und `befunde/`; `aufgaben/` gehört dazu.**
Ein Zitat braucht drei Teile im selben Absatz: eines der vier Schlüsselwörter (Abschnitt,
Absatz, Ueberschrift, Überschrift), Wortlaut **in Anführungszeichen**, **links davon** ein
Dokumentname. Zahl der Schlüsselwörter nie steigern („im Abschnitt X" → „unter X").

## Vorschläge sichten

- **Fünf Prüfungen in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar ·
  **Nummer gegen das Verzeichnis** (`ls aufgaben/ | tail`).
- **Es gibt keine Nummernreservierung außer mir.** Bei Doppelvergabe behält einer die
  Nummer, der andere zieht um — **nicht per `git mv`** (ein frischer Vorschlag ist
  unversioniert, blankes `mv` ist mir verboten), sondern per **zwei `Edit`**: Text in die
  freie Nummer; an der alten ein Verweis **ohne Frontmatter**, damit sie in keiner Zählung
  über `^status:` mitläuft. Legt der Parallellauf schon einen leeren Zwilling gleichen
  Namens an, ist das der Platz (0155/0156 am 2026-09-06).
- **Meldet ein Vorschlag seine eigene Kollision, ist er gut — die Auflösung bleibt meine.**
  Stellt er mir die Reihenfolge ausdrücklich anheim, entscheide ich sie **und begründe sie
  im Paket** (0156 vor 0091: dessen Abnahme zitiert Zeilen, die 0091 sonst wegschreibt).
- **Nennt ein Vorschlag die falsche Datei, ist meist die Ursache falsch.**
- **Waisenrollen:** `builder`, `geschaeftsfuehrer`, `projektmanager`. Liegt die Datei
  außerhalb jeder Schreibgrenze (`agents/*.py`): **`blockiert` plus Meldung.**
- **„Zu früh" ist kein Ablehnungsgrund, sondern `blockiert`** — und wenn es das Paket, an
  das ich hängen müsste, noch nicht gibt, gehört genau das in die Meldung (0157).
- **Nebenbefunde bei `geprueft` sind die bessere Paketquelle als `zurueck`.** Sagt der
  Prüfer „kein eigenes Paket", ist das seine Messung — dann lege ich keins an.

## Werkzeuge — was mich Aufrufe gekostet hat

- **Nie `cd`en — der Preis ist höher, als hier bisher stand.** Am 2026-09-06 nahm ein `cd`
  nach `befunde/` das **Arbeitsverzeichnis der Sitzung** mit, und danach wurde **jeder
  `Edit` abgelehnt**: `Edit(ventures/**)` ist ein *relatives* Muster und trifft meine
  absoluten Pfade nicht mehr. Die Meldung nennt nur „don't ask mode" und zeigt nie auf die
  Ursache. **Heilung: `cd /home/adria/fabrik && pwd`.** Sonst `git -C …`; Sekundärschaden
  wie gehabt: `git log -- <pfad>` läuft still leer.
- **`Edit` verlangt vorher den `Read`-Aufruf** — `cat` zählt nicht; `Read` mit `limit: 8`
  aufs Frontmatter genügt für einen Statusnachzug. Anker: die `id:`- oder `rolle:`-Zeile.
- Abgelehnt: `sed`, `cp`, `rm`, Schleifen, `git commit`, `python3 -c`, Heredocs, **Pipes und
  `&&`-Ketten**. Verlässlich: **je ein** `grep`, `head`, `ls`, `wc`, `git -C …`, `baulauf.py
  --trocken`. **Ich committe nicht selbst.**
- **Dieses Logbuch kann ich nicht archivieren:** kein `Write`, `Edit` nur auf
  `notizen/projektmanager.md`, `mv` abgelehnt. „Jede neue Lehre kostet eine alte" ist
  deshalb Mechanik, nicht Mahnung — **im selben Lauf schneiden, in dem ich schreibe.**
- **`Grep` mit `abnahme:` im Muster sprengt den Puffer.** Nur `^status:`, `^dateien:`,
  `^haengt_an:`, `^rolle:`. Kein Look-around. **`^(status|rolle):` mit `glob` über eine
  Nummernliste `0{064,068,…}*.md` holt den halben Rückstand in einem Aufruf.**
- **`befunde/` und `bau/` sind Abschriften des Quellbaums, keine Quellen.** Bei jedem
  Beleg-Grep ausnehmen. **Jede fremde Zahl nachmessen, auch meine eigene.**

## Was sonst funktioniert

- **Spezifikation nicht lesen, indizieren:** `grep -n 'T18\|T19'`, dann `Read` mit `offset`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
- **`file(GLOB … CONFIGURE_DEPENDS)`: eine neue Quelle braucht kein Manifest.**
- **Vor jedem neuen Paket nachmessen, dass die Sache wirklich fehlt.**
- **Ein leerer Vorrang ist kein Vorrang:** Stehen alle Kennungen aus `ops/plan.md` auf
  `fertig`, darf ich nach `specs/` schneiden — und **melde die Rücknahme ausdrücklich**.

## Offene Fährten

- **`ops/plan.md` ist seit 2026-09-04 abgearbeitet**, alle fünf Vorrangkennungen `fertig`.
  **Neunmal gemeldet, unbeantwortet.** Der Betreiber hat am 2026-09-05 stattdessen vier
  Pakete (0116–0119) selbst geschrieben; **das ist die deutlichere Vorrangaussage**, und
  danach richte ich die Kettenspitze. **„Nichts aus der Belegstellen-Familie diese Woche"**
  gilt weiter — deshalb steht 0147 hinter 0130.
- **Prüfer setzen mal selbst `fertig`, mal gar nicht**, obwohl `baulauf.py:32` es mir
  vorbehält. Am 2026-09-06 zweimal die teurere Hälfte: erst vier, dann sechs Pakete lagen
  als `gebaut` mit fertigem Befund da. **Zum dritten Mal gemeldet.**
- **`technik.md` zerlegen** ist zum elften Mal fällig: **zehn der 26 offenen Pakete liegen
  auf dieser einen Datei** — eine Reihe, in der jedes Glied einen Lauf kostet.
- **Kein Paket baut einen rechnenden Rumpf für `schritt_2`…`schritt_6`.** Darum steht 0157
  auf `blockiert` — ich habe kein `haengt_an`, das ich schreiben könnte. **Das ist die
  Sperre, an der die drei Maße hängen**; ohne sie ist Prüfung 6 grün über nichts. Gemeldet.
- **Fünf Mitglieder meldet `cmake -S` als „noch nicht gebaut"** (`daten`, `schnittstelle`,
  `konsole`, `oberflaeche`, `werkzeuge/aufbereitung`). Nach T13 hat **nur `daten` einen
  existierenden Vorgänger**; `technik.md` 144/201 nennt es „später" — Aufmachen ist
  Entwurfsentscheidung, nicht meine. **Nie zwei in einem Lauf.**
- **Zwei Reste `.kopf.tmp`/`.paket.tmp` mit `status: gebaut`** verfälschen jede Zählung
  über `^status:`. Ich lösche nicht (Hausregel 3).
- **Die Stufe `high` reicht.** Zwei Läufe am 2026-09-06, beide Buchhaltung plus Reihenfolge
  entlang schon geschriebener Befunde. An keiner Stelle fehlte mir der Kopf.
