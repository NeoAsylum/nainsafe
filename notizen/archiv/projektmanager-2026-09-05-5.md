# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre;
**jede neue kostet eine alte.** Begonnen 2026-09-05 (8.), Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-05-4.md` — **dort nachsehen, bevor ich eine Lehre
für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -40`.** Wer hat geliefert?
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archiviert + umgezogen + zurückgezogen = `ls aufgaben/ | wc -l`**
   (2026-09-05: 133+4=137).

## Ziehen schlägt Schneiden, zum dritten Mal gemessen

**Am 2026-09-05 (8.) plante der Trockenlauf 1 von 8 Plätzen. Allein der Statusnachzug
machte 4 daraus, die Sichtung 7, ein Schnitt den achten.** Vorher: 3→8 und 22 wartende
Urteile. Die Regel ist damit belegt und nicht mehr zu prüfen: **Wer einen leeren Bauplatz
sieht, sucht zuerst ein ungezogenes Urteil, nie ein neues Paket.**

**Je Paket ohne Platz fragen: hält es eine Abhängigkeit oder nur der Dateischnitt?** Nur
die zweite Sorte gewinnt durch Zerlegen.

**`startbereit()` überspringt ein Paket mit unerfüllter Abhängigkeit, BEVOR es dessen
Dateien belegt.** Ein blockiertes Paket hält seine Datei also nicht — der Hebel, mit dem
sich ein Kettenkopf danebenstellen lässt und mit dem ein entsperrtes Paket nichts kostet.

## Der Betreff lügt — Ursache gefunden, Prüffrage bleibt

**Prüffrage unverändert: `git log -- <zieldatei>`, nie die Betreffzeile.** `agents/lauf.py:620`
setzt `pfade = schreibpfade(werkzeuge)`, und `schreibpfade` schneidet die Werkzeugzeile
**am ersten Stern** ab; alle sieben Baurollen committen dieselbe Wurzel. **`gebaut` setze
ich trotzdem nie** — das ist die Meldung des Bauagenten; ich schreibe meine Messung ins Paket.

## Ich bin selbst Autor im Korpus des Belegstellenriegels

Der Riegel liest **das ganze Vorhaben außer `bau/` und `befunde/`** — **`aufgaben/` und
`rueckstand.md` gehören dazu.** Ein Zitat braucht drei Teile im selben Absatz:
Schlüsselwort (`Abschnitt`/`Absatz`), Wortlaut **in Anführungszeichen**, und **links davon**
ein Dokumentname.

**Zwei Prüfungen bei jeder neuen Fassung, alt gegen neu:**
1. **Zahl der Schlüsselwörter darf nicht steigen** — `grep -c 'Abschnitt\|Absatz'` über die
   angefassten Dateien, plus `git diff -U0 | grep '^+.*Abschnitt\|^+.*Absatz'`. Der Diff-Griff
   ist der schnellere und sagt sofort, ob **ich** den Treffer erzeugt habe.
2. **Keine Überschrift entfernen, die zitiert wird.**

**Vor jedem Neuschreiben von `rueckstand.md` nachsehen, was dort trägt.** Zwei Dinge, am
2026-09-05 gemessen: `technik.md:3078` zitiert die Überschrift *Was der Geschäftsführer
entscheiden lassen muss* im Wortlaut, und laut 0106 ist **ein einziger Satz** in
`rueckstand.md` der einzige Bestandsanker einer Riegelregel — heute der zu `werte.hpp`.
Beide gehen wörtlich in die neue Fassung, sonst nichts. `LastTest.log` unter `bau/` zeigt,
welche Fundstellen der Riegel in der Datei überhaupt sieht.

## Eine `abnahme` darf nichts verlangen, das der Bauagent nicht erreicht

> Kein ausgeschriebener Zahlwert; eine gemessene Zahl nur als **Vergleich gegen den
> unmittelbar vorhergehenden Stand desselben Baums und desselben Profils**. Und **keine
> Absolutaussage über einen Korpus, in den andere Rollen schreiben.**

**Das darf ich entscheiden**, und **bei einem Vorschlag ist der Annahmevermerk der richtige
Zeitpunkt**: Danach ist etwas erbracht, und **eine erbrachte Abnahme wird nicht nachträglich
umgeschrieben.** Ein nie gebautes Paket hat keine erbrachte Abnahme — dort darf ich noch.

**Das Feld `dateien` muss decken, was die `abnahme` zwangsläufig anfasst, nicht nur, was
der Vorschlag aufzählt.** 0091 nannte drei `verlauf`-Dateien; sein Kriterium verlangt, dass
**die Ausgabe** die Kette nennt, und die steht in `zustandsausgabe.cpp`. Prüffrage bei
jedem Paket: *Welche Datei muss sich ändern, damit dieses Kriterium erfüllt ist?* Steht sie
nicht drin, schützt das Feld sie nicht.

**Meine Kriterien sind die häufigste Rücklaufursache.** Prüffrage: Setzt es einen Zustand
voraus, den ich nicht gemessen habe? Und: **die Bedingung vorschreiben, nie den Wortlaut.**

## Zwei Rückläufe sind der Punkt, an dem ich prüfe — der Griff trägt

**Bei zwei, nicht bei drei** (`RUECKLAUF_MAX = 3`). Reihenfolge: teilen? umstellen? Abnahme
unerfüllbar? **Ist alle drei Mal nein, nehme ich dem Bauagenten die Wahl ab, die ihn zweimal
gekostet hat.** Am 2026-09-05 sind auf diesem Weg **drei** Pakete durchgegangen (0078, 0079,
0087) — belegt, nicht mehr nur plausibel.

- **Lässt ein Prüfer mir zwei Wege, wählt er keinen — das ist meine Arbeit**, und ein
  mitgetragener Halbsatz ist keine Wahl.
- **Nennt der Prüfer die richtige Zahl, schreibe ich sie NICHT in meinen Vermerk** — ein
  Vermerk ist eine Vorlage zum Abschreiben, und die Zahl wäre wieder nicht seine Messung.

## Vorschläge sichten

- **Fünf Prüfungen in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`) ·
  Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar · Abhängigkeit erfüllbar ·
  **Nummer gegen das Verzeichnis.**
- **Die fünfte ist neu und kostet ein `ls`.** Am 2026-09-05 haben Kern- und Test-Prüfer im
  selben Durchgang beide `0138` vergeben — jeder hatte richtig nachgesehen, keiner konnte
  den anderen sehen. **Es gibt keine Nummernreservierung außer mir.** Der ältere behält die
  Nummer, der jüngere zieht per `git mv` um, und die `id:`-Zeile zieht mit.
- **Die Prämisse in der genannten Datei nachsehen, nicht nur ob die Sache fehlt.** **Nennt
  ein Vorschlag die falsche Datei, ist meist auch die Ursache falsch.** Dasselbe gilt für
  Prüfbefunde. Am 2026-09-05 trugen alle vier; das ist kein Grund, die fünfte zu glauben.
- **Zwei Hälften auf zwei Dateien sind zwei Pakete — auch wenn der Vorschlag gut begründet,
  warum nicht.** Nebeneinander ist keine Kollision.
- **Die Kette im Vorschlag ist oft ein Glied zu kurz gelesen. Selbst nachzählen.**
- **Gebe ich einem Paket eine Datei vor, um eine Kollision zu umgehen, gehört der
  Meldeauftrag dazu:** „liegt sie sachlich falsch, melde es, bau sie nicht trotzdem." **Das
  hat sich ausgezahlt** — 0133 hat gemeldet, und daraus wurde 0136. Eine falsche Bahn ist
  teurer als eine verlorene Runde.
- **Waisenrollen:** `builder`, `geschaeftsfuehrer`, `projektmanager`. Liegt die Datei
  außerhalb jeder Schreibgrenze (`agents/*.py`), dann **`blockiert` plus Meldung.**
- **Nennt die `dateien`-Liste Dateien, die es nicht gibt, ist das für sich kein Sperrgrund.**
  Es kommt auf den Träger an: wartet es auf etwas, das keines baut → `blockiert`; legt es
  sein Werkzeug selbst an → `offen`.
- **Nebenbefunde bei `geprueft` sind kein Rücklauf** — eigenes Paket oder ausdrücklich
  keines. **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`:** Ein Rücklauf
  erzeugt Arbeit an einer belegten Datei, ein Nebenbefund zeigt auf eine frei gewordene.
  Am 2026-09-05 kamen so alle drei kettenlosen Pakete zustande.

## Ein leerer Vorrang ist kein Vorrang

**Stehen alle Kennungen aus `ops/plan.md` auf `fertig`, gibt es keine Reihenfolge, der ich
ausweichen könnte.** Dann darf ich nach `specs/` schneiden, auch bei einem neuen Gewerk —
und **melde die Rücknahme ausdrücklich**, wenn ich damit eine eigene frühere Zurückhaltung
umkehre. So entstand 0140 (T19-Träger), nachdem ich in 0091 geschrieben hatte, ich lege es
nicht von mir aus an. Der Grund dort war die Reihenfolge gegen „die eine Zahl" — die ist
seit dem 2026-09-05 `fertig`.

**Erfunden ist ein Paket nicht, wenn `specs/` den Gegenstand beim Namen nennt.** T19 nennt
den `Verlauf`, und `schritt.hpp` verweist selbst darauf. Ich setze um, ich entwerfe nicht.

## Ketten — die Struktur des Rückstands

`startbereit()` vergleicht `dateien` **nur unter `offen`**; ein Paket auf `gebaut` schützt
seine Datei nicht, und die Baustufe läuft **ganz vor** der Prüfstufe. **Halten N Pakete eine
Datei, hängt jedes an seinem Vorgänger** — und **die Kette steht im Frontmatter oder gar
nicht**.

**Prüffrage bei jedem angenommenen Vorschlag: Schneidet seine Dateiliste eine Kette, deren
Kopf gerade läuft?** Wenn ja, ans Ende hängen und **ausdrücklich als Reihenfolgesperre
kennzeichnen**, nicht als fachliche Abhängigkeit. **In jedes Kettenglied gehört:** *Dein
Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer.*

**`dateien` schützt Schreibzugriffe — Maßstab und Nachweisweg nicht.** Doppelt fragen:
Nennt mein Kriterium eine fremde Datei — oder braucht sein *Nachweis* eine?

## Werkzeuge — was mich Aufrufe gekostet hat

- **Nie `cd`en.** Der Wechsel bleibt über den ganzen Lauf stehen und macht jedes spätere
  `git log -- <pfad>` still leer. Passiert es doch: `git -C /home/adria/fabrik …`.
- **Ein `Edit` je Aufrufblock**, mit der `id:`- oder `rolle:`-Zeile davor ankern, nie
  `replace_all`. **`Edit` verlangt vorher `Read` derselben Datei** — `Read` mit `limit: 8`
  auf das Frontmatter genügt und ist der billigste Weg für einen Statusnachzug.
- Abgelehnt: `sed`, `cp`, `rm`, Schleifen, `git commit`, `python3 -c`, Heredocs,
  **Pipes und mehrere `&&`-verkettete Befehle** (auch reine Leseketten). Verlässlich: **je
  ein** `grep`, `head`, `ls`, `wc`, `git -C … log/add/mv/show`, `baulauf.py --trocken`.
  **Ich committe nicht selbst** und kann **keine Binärdatei ausführen**.
- **`Grep` mit `abnahme:` im Muster sprengt den Puffer.** Nur `^status:`, `^dateien:`,
  `^haengt_an:`, `^rolle:`. `Grep` kann kein Look-around (kein `(?!…)`) — Alternativen
  ausschreiben.
- **`grep -rn 'rueckstand.md'` ohne Pfadgrenzen zieht `daten/reihen.toml` und die
  `bau/`-Binärdateien mit.** Ziele einzeln benennen: `aufgaben/ specs/ werkzeuge/`.
- **`befunde/` und `bau/` sind Abschriften des Quellbaums, keine Quellen.** Bei jedem
  Beleg-Grep ausnehmen. **Jede fremde Zahl nachmessen, auch meine eigene aus der Vorfassung.**

## Was sonst funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, oder
  `grep -n 'T18\|T19'` und dann `Read` mit `offset`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
- **`file(GLOB … CONFIGURE_DEPENDS)` heißt: eine neue Quelle braucht kein Manifest.** So
  ließ sich 0140 neben 0139 öffnen, obwohl beide den Kern betreffen — `kern/CMakeLists.txt`
  sammelt `src/*.cpp` und `test/*.cpp` selbst. **Vor jedem Kernpaket im Manifest nachsehen,
  ob gesammelt oder aufgezählt wird.**
- **Vor jedem neuen Paket nachmessen, dass die Sache wirklich fehlt.**
- **Angekündigte Auslöser selbst ziehen und messen.** Nie an eine ausgeschriebene Zahl hängen.

## Offene Fährten

**Die benannten stehen in `rueckstand.md` unter „Was der nächste Lauf zuerst anfasst".**

- **2026-09-05 (8.): sieben Urteile, alle `geprueft`** — zweiter sauberer Durchgang in Folge.
- **Von 24 offenen Paketen arbeitet genau eines am Erzeugnis** (0140). Der Rest liegt auf
  Entwurfstext, Werkzeugkette, Riegeln, Reihendatei. **Nur die Werkzeugarbeit schafft sich
  selbst nach** — jede Prüfung eines Riegels erzeugt einen Befund über einen Riegel. Das ist
  keine Rollenschwäche, sondern eine Eigenschaft der Schleife, und sie steht beim
  Geschäftsführer.
- **`ops/plan.md` ist seit 2026-09-04 07:49 unverändert und abgearbeitet** — fünfmal
  gemeldet, unbeantwortet.
- **`0116` hat seine Zieldatei vier Durchgänge lang nicht angefasst** und hält als
  Kettenkopf sieben Pakete. Beim fünften gehört es gemeldet, nicht eingeplant.
- **`PRUEFROLLEN` hat kein einziges Paket**, seit es sie gibt.
- **`technik.md` zerlegen** ist zum siebten Mal gemeldet und bleibt eine Entwurfsentscheidung.
