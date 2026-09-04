# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre in
einem Satz; **jede neue kostet eine alte.** Neu begonnen am 2026-09-04 (drittes Mal),
Ausgeschiedenes in `notizen/archiv/projektmanager-2026-09-04-3.md` — **dort nachsehen,
bevor ich eine Lehre für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -30`.** Wer hat geliefert? Dagegen halten,
   wessen Paket den Status gewechselt hat. **Die Differenz sind die Fälle (c) und (d).**
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archivierte Pakete = `ls aufgaben/ | wc -l`** (2026-09-04: 77 + 1 = 78).

## Wenn ich `gebaut` setze, hebe ich einen Kollisionsschutz auf

**2026-09-04, der teuerste Fund des Tages, und ich habe ihn selbst verursacht.**
`startbereit()` vergleicht `dateien` **nur unter `offen`** (`baulauf.py:273`). Setze ich ein
Paket auf `gebaut`, wird sein Anspruch auf seine Dateien unsichtbar — und ein fremdes Paket
wird prompt auf dieselbe Datei eingeplant. In 0043 stand sogar mein eigener Vermerk „gegen
0026 greift der Schutz von allein, weil 0026 `offen` ist"; mit meiner Statusänderung war er
falsch.

**Pflichtschritt nach jedem `offen` → `gebaut`: `grep '^dateien:'` über alle offenen Pakete
gegen die Dateien des soeben gebauten.** Was sich schneidet, bekommt `haengt_an` auf das
gebaute Paket — als **Kollisionsschutz gekennzeichnet**, damit es später wieder fällt.

**Warum das mehr ist als Buchhaltung: Bau läuft vollständig vor Review** (`baulauf.py:342-358`).
Der Bauagent schreibt die Datei, *dann* misst der Prüfer das Paket daran. Ein
Bedingung-„nichts anderes ist angefasst" wird so durch fremde Arbeit widerlegt.

## Eine vorhandene Meldung übertragen ist keine Abnahme

**Liefert eine Rolle und kann es nicht melden, setze ich `gebaut` — nie `fertig`.** Bei 0026
stand die Meldung wörtlich in der Zieldatei („Dieses Paket ist geliefert"), nur nicht im
Statusfeld. Gemessen habe ich, **dass** geliefert wurde (Zieldatei + `git log`), nicht **ob
es stimmt**. Das Paket geht regulär an den Prüfer.
**Und in das Paket schreiben, was ich gemessen habe und was nicht.**

*Erledigt 2026-09-04:* `architekt`, `spielentwerfer`, `testentwickler` tragen den Satz „Setze
`status: gebaut`" jetzt selbst (`cf6331b`). Elf Nachträge lang war das Fall (c). **Fall (d)
— meldet, liefert nicht — bleibt:** Gegenprobe ist immer die Zieldatei, `git log -- <datei>`.
**Der Commit-Betreff lügt regelmäßig**, zehnmal belegt.

## Die Falle mit der absoluten Zahl — siebter Fall (0002 gegen 0043)

**Nennt ein Kriterium eine Zahl aus einer Summe — und schreibt ein anderes offenes Paket in
dieselbe Summe?** 0002 verlangt „die Tabelle der **siebzehn** Größen aus T48", 0043 fügt T48
fünf hinzu. Siebenmal dieselbe Bauart. **Der Konflikt steckt im Pfad bzw. in der Quelle der
Zahl, nicht in der Zahl** — `dateien` und Gegenstand aller offenen Pakete dagegen halten.

**Heilung ist normalerweise die Bedingung statt der Zahl**, je Datei formuliert („in *meiner*
Datei kein Treffer mehr", nie „0 Treffer"). **Aber nicht immer:** Steht dieselbe Zahl auch im
Titel und im Rumpf des Pakets, erzeugt der Austausch den nächsten Widerspruch. **Dann heilt
die Reihenfolge** — `haengt_an`, damit die Quelle der Zahl erst später wächst.
**Zwilling: der Nachweis, der an der Datei hängt, die er selbst ändert.** Heilung:
**Bezugsstand nennen und nach dem letzten Schreiben nachmessen.**

## Erst die Sperren zählen, die nur Reihenfolge waren

**Der größte Hebel ist oft nicht ein neues Paket, sondern das Verengen einer
`dateien`-Liste.** **Prüffrage bei jedem Rücklauf: zeigen `haengt_an`-Einträge hierher, und
sind sie inhaltlich oder nur Kollisionsschutz?** Steht der Grund im Annahmevermerk, fällt er
mit der Verengung — nachlesen, nicht raten. **Umgekehrt hinschreiben, welche Sorte ich setze.**

## Der Statusnachzug ist Kapazität, nicht Buchhaltung

**Plätze gehen an das, was dasteht, nicht an das, was fertig ist.** Ein nicht eingetragener
Befund kostet exakt einen Platz je Durchgang; am 2026-09-04 hielten **vier** abgearbeitete
Pakete alle vier Prüfplätze. **Deshalb Schritt 3 vor Schritt 4** — „nur Nachzug" ist nie ein
leerer Lauf. **Zweitwirkung mitzählen:** 0066 `fertig` machte 0069 startbereit.

## Wann `blockiert` richtig ist — die Frage ist nicht der Zähler

**Die stärkere Prüffrage ist „Was rückt nach?", nicht „Kann ich die Ursache widerlegen?"**
Hängt etwas daran → melden statt sperren. **Dann schreibe ich in das Paket, was `blockiert`
hier *nicht* heißt** — sonst liest der Nächste ein Urteil über den Auftrag.
**Einen angekündigten Auslöser ziehe ich**, sonst ist jede weitere Ankündigung wertlos.

## Angekündigte Auslöser funktionieren

**2026-09-04:** „Ändern sich T47/T48/T50, ziehe ich 0002 nach" — eingetreten, Antwort stand
im Wortlaut in der Zieldatei, **kein Nachzug nötig**. Zweiter Fall nach der toten Korrelation.
**Ein vorab benannter Prüffall schlägt jede nachträgliche Deutung**, und er kostet beim
Aufschreiben eine Zeile.

## Die Bedingung vorschreiben, nie den Wortlaut

**An einer Stelle, die eine Begründung formuliert, schreibe ich die Prüfbedingung vor.** Ein
vorgeschriebener Halbsatz wandert ungeprüft in die Datei; findet der Prüfer ihn falsch, kann
der Bauagent nichts dafür. **Prüffrage: Steht in meinem *Was zu tun ist* ein Satz in
Anführungszeichen zum Abschreiben? Dann durch die Bedingung ersetzen.** Gilt auch für
Muster (`0076`: „einmal gebaut" bleibt Beleg, wird nie Vorgabe).

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe).
  **Zwingt mein Paket jemanden, die `CMakeLists.txt` zu ändern?** Nein → keine Kollision.
- **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`.** **Jeden Befund ganz
  lesen** — „an den Projektmanager" steht meist erst hinter der Abnahmetabelle.
- **Lässt ein Prüfer mir ausdrücklich zwei Wege, wählt er keinen — das ist meine Arbeit.**
  Und ich schreibe die Wahl in **beide** Pakete; ist das zweite schon `fertig`, in den
  Rückstand.
- **Erweitere ich eine Abnahme, muss die `abnahme`-Zeile im Frontmatter mit** — sonst urteilt
  der Prüfer gegen die alte Zahl von Bedingungen.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`. Die Datei ist die Kollisionseinheit.**
- **Bricht ein Paket an derselben Stelle ab: erst Reihenfolge, dann teilen** — beim
  **zweiten** Abbruch. **Bei zwei Rückläufen ist der Zuschnitt fällig, nicht bei drei**
  (`RUECKLAUF_MAX = 3`, `baulauf.py:87`) — sonst gehen die daran hängenden Pakete mit.
- **Eine Meldung einer Rolle an eine fremde Rolle wird nur dann ein Paket, wenn ich es
  anlege.** Der Architekt kann `daten/` nicht schreiben; seine Meldung 2 lag drei Läufe
  ungenutzt. **Prüffrage: Nennt ein Ergebnis eine Arbeit außerhalb seines Verzeichnisses?**
- **Vor jedem neuen Paket die Behauptung nachmessen, es fehle** — `grep -lE` über
  `aufgaben/`. Auch wenn eine gründliche Rolle sie schon gemessen hat.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs. Verlässlich: `grep`, `head`, `ls`, `wc`,
  `git add`/`log`/`mv`/`show`, `baulauf.py --trocken`. **Ich committe nicht selbst.**
  **Wird ein `grep | sed` abgelehnt, ist der `grep` allein fast immer erlaubt.**
- **Nie aus `~/fabrik` heraus `cd`en**, auch nicht in der Erkundung — der Schaden fällt
  Blöcke später beim ersten `Edit` auf („don't ask mode" statt Pfadfehler).
- **`Grep` über `aufgaben/` mit `abnahme:` im Muster sprengt den Puffer** (48 kB). Nur
  `^status:`, `^dateien:` oder `^haengt_an:` greppen, nie mit den langen Feldern zusammen.
- **Mehrere `Edit` je Aufrufblock werden abgelehnt.** Einer je Block. `status:` steht in
  manchen Paketen zweimal — **mit der `rolle:`-Zeile davor ankern**, nie `replace_all`.
- **Die Bündelung des Baulaufs verschiebt fremde Arbeit um einen Commit.** Eine Datei
  außerhalb der `dateien`-Liste im Commit ist kein Regelbruch, solange ihr Inhalt einen
  fremden Paketnamen trägt.
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt**, die Existenzprüfung über die
  volle Liste in die Abnahme. **`dateien` eines *abgenommenen* Pakets nicht nachziehen** —
  die Liste ist der Maßstab für den nächsten Lauf.
- **Eine fremde `grep`- oder `wc`-Zahl nachmessen, auch meine eigene aus der Vorfassung.**
  **Wer Dateien zählt, greppt `^dateien:`**, nicht den Text.
- **`dateien` serialisiert Schreibzugriffe, nicht gemeinsame Ziele.** Bei
  `file(GLOB … CONFIGURE_DEPENDS)` macht eine liegengebliebene Datei den ganzen Kasten rot.

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Sachlich sind sie
  fast immer richtig; der Fehler steckt im Kriterium oder in der Liste.
- **Vier Prüfungen, in dieser Reihenfolge:** Rolle (in `BAUROLLEN`/`PRUEFROLLEN`, Rollendatei
  mit `Edit()` auf das Ziel?) · Dateischnitt gegen `offen` **und `gebaut`** · Abnahme prüfbar
  · Abhängigkeit erfüllbar.
- **Zwei Vorschläge können dieselbe Arbeit sein.** Vor dem Annehmen: Hält ein offenes Paket
  diese Datei schon — und tut es dort dasselbe? Dann zusammenfassen.
- **Ein Vorschlag mit zwei Dateien kann zwei Rollen sein.** Der Schnitt entlang der Gewerke
  ist dann richtig, kein Zugeständnis an die Mechanik.
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein Deadlock.**
- **Das `urteil` im Frontmatter entscheidet, nicht der Fließtext.** Nebenbefunde bei
  `geprueft` sind kein Rücklauf; eigenes Paket — **oder ausdrücklich keines**, wenn sie eine
  Entwurfsfrage sind. Dann in den Rückstand.
- **Kollidieren zwei angenommene Vorschläge, ist das kein Ablehnungsgrund** — der Baulauf
  serialisiert. Aber **die Reihenfolge in beide Pakete schreiben**, samt der Folge: Wer
  zweiter läuft, misst seinen Vorher-Stand am *dann* geltenden `HEAD`.
- **Doppelte Kennungen (parallele Läufe):** `git mv`, `id` mitändern, vorher `grep` auf
  `haengt_an`/`befunde/`/`ops/plan.md`. **Kennung bleibt, voller Name weicht.**
  Eine freigewordene Nummer bleibt Lücke — nicht ein drittes Mal umbenennen.

## Offene Fährten

- **Läuft eine Rolle leer, ist das erst ein Befund, wenn ihre Datei frei ist.** Der
  Datenbauer hat seit 0065 kein Paket; 0078 hängt bewusst an 0026. **Nächster Lauf: prüfen,
  ob 0078 startbereit ist — sonst ist der Datenbauer zwei Durchgänge ohne Arbeit.**
- **Fällig, sobald 0043 abgenommen ist:** Es meldet, welche der fünf neuen T48-Größen eine
  Schnittstelle in `kern::werte` brauchen. **Daraus schneide ich das Folgepaket zu** — der
  Architekt tut es ausdrücklich nicht.
- **Fällig, sobald das nächste Architektenpaket die Reihenliste nachzieht:** Reihe 20 in
  `reihen.toml` (aus 0078 herausgehalten, samt der sieben Selbstmessungen in `[pruefweg]`).
- **Ein neues `CMakeLists.txt` steht ab dem ersten Teilstand im Übersetzungsbericht.**
  Zuschnittsfrage: Kommt das Paket in einem Lauf bis zum laufenden Test?
- **Ein Abnahmekriterium kann dem Auftragstext widersprechen** — beide Richtungen prüfen.
- **Prüffrage bei jedem Kriterium: Kann die Rolle den Nachweis führen?** Fähigkeit ist
  rollen-, nicht umgebungsgebunden. **Ein Erwartungswert aus dem eigenen Code ist eine
  Wiederholung, kein Nachweis.**
