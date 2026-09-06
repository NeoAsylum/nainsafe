# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-06.md` — **dort nachsehen, eh ich etwas für neu halte.**
**`Write` nach `notizen/archiv/` ist abgelehnt** (2026-09-06): nicht rotieren, sondern
überholte Einträge durch ihre neue Fassung ersetzen. Gemeldet.

---

## Der Lauf beginnt immer gleich

1. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
2. **Vorschläge sichten.** Erst dann neue Pakete.
3. **`baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.

## Ziehen schlägt Schneiden — fünfmal am 2026-09-06 gemessen

Baupakete vor dem Nachzug → danach: **1→5**, **1→7**, **1→6**, **0→7**. Jedes Mal hielten
vier bis acht `gebaut`-Pakete mit fertigem Befund je eine Kette. **Der Nachzug steht zuerst,
weil er als einziger Plätze schafft** — im fünften Lauf war er der ganze Durchsatz: acht
Befunde, alle `geprueft`, und die Fabrik stand vorher auf null Bauplätzen.

**Ein Lauf zog null, und das war der harmlose Fall:** acht `gebaut`, **kein Befund**, weil
alle im Review saßen. Leerer Nachzug heißt nicht säumiger Prüfer — erst nachsehen, ob die
Prüfung läuft.

## Bau, Review und Prüfung haben je ein eigenes Budget

`baulauf.py:362/375/381` schneidet **drei** Listen unabhängig auf `gleichzeitig` zu. „2 von 8
Bauplätzen" ist **nicht** die Auslastung: am 2026-09-06 liefen 2 Bau + 8 Review + 1 Prüfung,
**Review am Anschlag**. Bevor ich Bauplätze als leer melde, zähle ich die andere Stufe.

## Der Rückstand ist Ketten, nicht Posten

Der Durchsatz ist durch die Zahl **verschiedener Dateien** begrenzt, nicht durch
`GLEICHZEITIG` (8). Zwanzig Pakete auf fünf Dateien sind fünf.

**Je Paket ohne Platz: Abhängigkeit oder nur Dateischnitt?** Nur die zweite Sorte gewinnt
durch Zerlegen. **`startbereit()` überspringt ein Paket mit unerfüllter Abhängigkeit,
BEVOR es dessen Dateien belegt** — ein blockiertes Paket hält seine Datei nicht.

**Ist die Kette echt? Miss sie:** `dateien` des Blockierten gegen die des Vorgängers;
disjunkt heißt, die Abhängigkeit ist eine Behauptung — **gleich heißt, Streichen brächte
null**, die Dateisperre hielte die Bahn ohnehin. Dann trage ich sie trotzdem ein, als
Reihenfolgesperre: kostenlos, und sie sagt dem Bauagenten, wo er steht. **Meine eigenen
Vermerke sind die unzuverlässigsten** — kein Prüfer liest sie.

## Ketten anlegen

Nach jedem `fertig` prüfen, **wer dadurch bereit wird**, und sofort zur Kette schließen; im
Zweifel **das Paket zuerst, das die längste Kette freigibt.** Ein Prüfbefund bringt oft
seinen Nachfolger mit.

**Halten N Pakete eine Datei, hängt jedes an seinem Vorgänger — die Kette steht im
Frontmatter oder gar nicht.** Reihenfolgesperren als solche kennzeichnen; beide Sorten
dürfen nebeneinander in `haengt_an` stehen. **In jedes Glied:** *Vorher-Stand ist der dann
geltende `HEAD`; such am Text, nicht an der Zeilennummer* — und **die ganze Reihe**, sonst
sieht keiner, wo er steht.

## `specs/` beauftragt mich manchmal wörtlich — dann ist ein Paket nicht erfunden

**Bevor ich melde „kein Platz zu füllen", `specs/` nach *Projektmanager*, *Folgepaket* und
*nachzuziehen* durchsuchen.** Ein Architekt, der eine Lücke meldet statt sie zu füllen, hat
mir ein Paket hinterlassen — es steht nur nicht im Rückstand (0150, 0151, 0152).

**Aber der Auftrag selbst kann verfallen sein — erst die Zieldatei messen, dann schneiden.**
`technik.md` verlangte am 2026-09-06 ein Folgepaket des Datenbauers, `regulierung_last` fehle
in `parameter.toml`. Es stand längst drin, nachgezogen von 0153; die Meldung war älter als
ihre Erledigung. **Ein Auftrag in `specs/` ist ein Hinweis, keine Messung** — dieselbe Regel
wie für meine eigenen alten Einträge.

## Eine `abnahme` darf nichts verlangen, das der Bauagent nicht erreicht

> Kein ausgeschriebener Zahlwert; eine gemessene Zahl nur als **Vergleich gegen den
> unmittelbar vorhergehenden Stand desselben Baums und Profils**. Und **keine Absolutaussage
> über einen Korpus, in den andere Rollen schreiben.**

**Der häufigste Verstoß ist eine Bedingung über `git diff`** — unerfüllbar, weil der Baulauf
die ganze Schreibwurzel committet. **Ersatzform: `grep -c` an der eigenen Zieldatei gegen den
Stand beim Start.** Die beste Fassung nennt **den Ausdruck selbst** und verlangt die
Übereinstimmung von Text und Messung, nicht die Zahl (0153, 0175). **Ein Zahlwort nur als
*Nachzählung*:** „Steht am Ende eine andere Zahl, folgt sie der Zählung, nicht dem Paket."

**`dateien` muss decken, was die `abnahme` zwangsläufig anfasst, nicht nur, was der
Vorschlag aufzählt.** Nennt mein Kriterium eine fremde Datei — oder braucht sein *Nachweis* eine?

## Ein zu großes Paket schneide ich an seiner eigenen Naht

**Die Vorgabe sagt meist selbst, wo. Der Schnitt liegt dort, wo die Kette reißt, nicht in
der Mitte der Liste** (T48 Nr. 18–20 bauen aufeinander auf, 21–22 nicht → 0151, 0152).

Zwei Pakete auf einer Datei laufen nacheinander — **das kostet nichts, wenn der Kopf ohnehin
nichts liefert.** Sequenziell und ankommend schlägt parallel und stumm.

## Zwei Rückläufe sind der Punkt, an dem ich prüfe

**Bei zwei, nicht bei drei** (`RUECKLAUF_MAX = 3`). Teilen? umstellen? Abnahme unerfüllbar?
**Dreimal nein → ich nehme dem Bauagenten die Wahl ab, die ihn zweimal gekostet hat.** Lässt
ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit. **Nennt er die richtige
Zahl, schreibe ich sie NICHT ab**; sonst wäre sie wieder nicht seine Messung.

## Zwei Lücken, die kein Zähler sieht — und beide zahle ich doppelt

**Der stumme Lauf.** `baulauf.py:350` zählt Rückläufe; ein Lauf, der nichts liefert, erzeugt
keinen — das Paket wird unbegrenzt zugewiesen. **Griff bei langer Standzeit:** `git log --
<zieldatei>`, dann die **Bytezahl** gegen den letzten Commit, der sie anfasste — die
Betreffzeile lügt. **Nicht `blockiert`, wenn Pakete dahinter hängen:** verkleinern.

**Die Prüfrolle ohne Ausgang.** `REVIEW` bildet nur Baurollen auf einen Prüfer ab (`:378`),
also entsteht zu `bruchtester`, `selbstspieler`, `rueckvergleicher` **nie ein
`pruefung-*`-Befund** — und `startbereit` zieht sie weiter aus `offen` (`:381`). Sie liefern
und bleiben stehen: 0145 lief **zweimal**, 0178 wäre am 2026-09-06 erneut vergeben worden.
**Ich nehme sie gegen den abgedruckten Lauf ab** und begründe es im Paket — die eine Ausnahme
von „nur mit Prüfbefund". **Der Griff:** je Abnahmebedingung ein Teil der Befundgliederung.

## Ich bin selbst Autor im Korpus des Belegstellenriegels

Er liest **alles außer `bau/` und `befunde/`; `aufgaben/` gehört dazu.** Ein Zitat braucht
drei Teile im selben Absatz: eines der vier Schlüsselwörter (Abschnitt, Absatz, Ueberschrift,
Überschrift), Wortlaut **in Anführungszeichen**, **links davon** ein Dokumentname. Zahl der
Schlüsselwörter nie steigern — in meinen Vermerken „unter X" statt „im Abschnitt X".

## Vorschläge sichten

- **Fünf Prüfungen in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar ·
  **Nummer gegen das Verzeichnis** (`ls aufgaben/ | tail`).
- **Doppelte Nummer ist kein Umzugsgrund — doppelte `id` ist einer.** `_id` kommt aus dem
  Frontmatter (`baulauf.py:239`): zwei `0172-*`, zwei `0185-*` mit verschiedener `id` trennt
  der Baulauf sauber → **nur ein Vermerk in beiden.** Bei doppelter **`id`** umziehen per
  **zwei `Edit`**: Text in die freie Nummer, an der alten ein Verweis **ohne Frontmatter**.
- **Nennt ein Vorschlag die falsche Datei, ist meist die Ursache falsch.**
- **Waisenrollen:** `builder`, `geschaeftsfuehrer`, `projektmanager`. Liegt die Datei außerhalb
  jeder Schreibgrenze (`agents/*.py`, `.gitignore`): **`blockiert` plus Meldung**, ausdrücklich
  **kein `abgelehnt`**, wenn die Sache stimmt und nur der Weg fehlt.
- **„Zu früh" ist kein Ablehnungsgrund, sondern `blockiert`** — und wenn es das Paket, an
  das ich hängen müsste, noch nicht gibt, gehört genau das in die Meldung (0157).
- **Nebenbefunde bei `geprueft` sind die bessere Paketquelle als `zurueck`.** Sagt der
  Prüfer „kein eigenes Paket", ist das seine Messung — dann lege ich keins an.

## Werkzeuge — was mich Aufrufe gekostet hat

- **Nie `cd`en — auch nicht im harmlosesten `grep`.** Am 2026-09-06 hat mich genau das zum
  zweiten Mal getroffen, im **ersten** Aufruf des Laufs (`cd …/befunde && grep`), und vier
  `Edit` starben daran. Es nimmt das **Sitzungs-Arbeitsverzeichnis** mit, danach wird **jeder
  `Edit` abgelehnt** (`Edit(ventures/**)` ist *relativ*); die Meldung nennt nur „don't ask
  mode" und sieht wie ein Rechteproblem aus. **Heilung: `cd /home/adria/fabrik && pwd`.**
  Sonst `git -C …` oder absolute Pfade als Argument.
- **`Edit` verlangt vorher `Read`** — `cat` zählt nicht; `limit: 8` aufs Frontmatter genügt.
  Anker: `rolle:`-Zeile mitnehmen, `status:` allein ist nicht eindeutig.
- Abgelehnt: `sed`, `cp`, `rm`, Schleifen, `git commit`, `python3 -c`, Heredocs, **Pipes und
  `&&`-Ketten**. Verlässlich: **je ein** `grep`, `head`, `ls`, `wc`, `git -C …`, `baulauf.py
  --trocken`. **Ich committe nicht selbst.**
- **`Write` habe ich** (2026-09-06 für ein neues Paket), `mv` nicht. „Jede neue Lehre kostet
  eine alte" ist Mechanik: **im selben Lauf schneiden, in dem ich schreibe**, und **nach
  jedem Schnitt `wc -c`** — Kürzen im Kopf trifft nie.
- **`Grep` mit `abnahme:` im Muster sprengt den Puffer.** Nur `^status:`, `^dateien:`,
  `^haengt_an:`, `^rolle:`. **`Grep -A2` auf `^status: offen` gibt Kette und Dateien in einem
  Aufruf** — aber nur, wo `status:` vor `dateien:` steht; bei 0165 stand es dahinter, und das
  Paket fehlte still in meiner Zählung. **Ein Frontmatter ist nicht sortiert.**
- **`befunde/` und `bau/` sind Abschriften des Quellbaums, keine Quellen.** Bei jedem
  Beleg-Grep ausnehmen. **Jede fremde Zahl nachmessen, auch meine eigene.**

## Was sonst funktioniert

- **Spezifikation nicht lesen, indizieren:** `grep -n 'T18\|T19'`, dann `Read` mit `offset`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
- **`file(GLOB … CONFIGURE_DEPENDS)`: eine neue Quelle braucht kein Manifest.**
- **Ein leerer Vorrang ist kein Vorrang:** stehen alle `ops/plan.md`-Kennungen auf `fertig`,
  schneide ich nach `specs/` — und **melde es ausdrücklich**.

## Offene Fährten

- **`ops/plan.md` ist seit 2026-09-04 abgearbeitet**, alle fünf Vorrangkennungen `fertig`,
  **zwölfmal gemeldet, unbeantwortet.** Der Betreiber schrieb am 2026-09-05 stattdessen vier
  Pakete (0116–0119) selbst; **das ist die deutlichere Vorrangaussage.**
- **Prüfer setzen mal selbst `fertig`, mal gar nicht**, obwohl `baulauf.py:32` es mir
  vorbehält. Am 2026-09-06 dreimal die teurere Hälfte. **Viermal gemeldet.**
- **`technik.md` zerlegen**, zum vierzehnten Mal fällig: **dreizehn der 25 offenen Pakete
  auf dieser einen Datei**, die übrigen zwölf verteilen sich auf sechs Bahnen. Das letzte
  Glied läuft in keiner denkbaren Woche. **Der Schnitt liegt in der Datei, nicht in meinen
  Paketen** — solange sie eine ist, ist ein Achtel meiner Bauplätze strukturell tot.
- **Kein Paket baut einen rechnenden Rumpf für `schritt_2`…`schritt_6`.** Darum steht 0157
  weiter auf `blockiert` — es gibt kein `haengt_an`, das ich schreiben könnte. **Das ist
  die Sperre, an der die drei Maße hängen**, vom Bruchtester am 2026-09-06 bestätigt.
- **Reste `.kopf.tmp`/`.paket.tmp` mit `status: gebaut`** verfälschen jede `^status:`-Zählung;
  seit 2026-09-06 auch `befunde/beschraenktheit/widerruf.neu`. Ich lösche nicht (Hausregel 3).
- **Die Stufe `high` reicht** — fünfter Lauf am 2026-09-06, nirgends fehlte mir der Kopf.
