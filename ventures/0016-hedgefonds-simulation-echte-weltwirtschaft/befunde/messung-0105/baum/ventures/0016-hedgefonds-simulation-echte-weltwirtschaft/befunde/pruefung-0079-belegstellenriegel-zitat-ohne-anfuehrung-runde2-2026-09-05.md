---
typ: pruefung
paket: 0079-belegstellenriegel-zitat-ohne-anfuehrung
pruefer: test-pruefer
datum: 2026-09-05
urteil: zurueck
kriterium_geprueft: Alle fuenf Teile der Abnahme unabhaengig nachgemessen (eigener Bau an vier Staenden, eigene Mutanten, eigener A-gegen-C-Vergleich); vier Teile halten, die dokumentierten Zahlen der Vorher/Nachher-Messung stammen von keinem ausgelieferten Stand.
befunde: 1
---

# Pruefung 0079, Runde 2 (Ruecklauf 1 des Bauagenten)

Alle Laeufe an eigenen Arbeitskopien unter `$TMPDIR`, gebaut im Alleinbauweg
(`cmake -S werkzeuge/belegstellen -B <bau>`, RelWithDebInfo, Werkzeugkette samt
Sanitizern ueber `PROJECT_IS_TOP_LEVEL`). Keine Repo-Datei angefasst; der eine Lauf am
Arbeitsbereich war rein lesend. `bau/` liegt nicht in git und fehlt deshalb in den
Arbeitskopien -- sichtbar allein an den "Namen in ungelesenen Ordnern" (286 statt 380),
und der Lauf bleibt gruen: Die Behauptung des Nachweises, keine Fundstelle haenge an
diesen Namen, ist damit nebenbei bestaetigt.

## Was erfuellt ist, je mit Messweg

**1. Benannte Eigenschaft statt Liste.** Der Kopfkommentar (Abschnitt "Die
Ueberschrift ohne Anfuehrung -- Paket 0079") begruendet die Entscheidung am Punkt
hinter der Gliederungsziffer, zweifach (keine Wortgrenze; Nachweis der Nummerierung),
und beantwortet den Einwand der umbenannten Ueberschrift. Keine Stellenliste im Code;
"Reihe 1" kommt nur als Selbsttestfall vor.

**2. Die vier Stellen aus 0047.** Lauf des ausgelieferten Standes am Baum des
Baucommits `f8c8598`: `reihen.toml:259` (Ziffer 5) und `:302`/`:309` (Ziffer 3) stehen
namentlich in der Aufzaehlung der uebergangenen Fundstellen; Zeile 1752 ("Reihe 1",
"2b und 2c") kommt darin nicht vor. Rotnachweis selbst gefuehrt, anders als der
Bauagent und deshalb unabhaengig: beide Zieluberschriften in einer Korpuskopie von
`daten/lizenzbefund-reihen.md` mit Vorsatz versehen -- der Lauf meldet **beide** als
"finden ihre Ueberschrift nicht" (`daten/reihen.toml:1752`, gesucht "Reihe 1" bzw.
"2b und 2c"), Rueckgabewert 1. "2b und 2c" wird also trotz Ziffernanfang nachgeschlagen
und faellt bei Umbenennung nicht in die uebergangenen zurueck. M0 vor der Mutation und
nach der Ruecknahme gruen mit unveraenderten Zahlen.

**3. Gruen auf dem geltenden Korpus.** Am Baum von `f8c8598`: 35 Zitate, 35
aufgeloest (Untergrenze 16), 47 uebergangen, Rueckgabewert 0. Am heutigen
Arbeitsbereich (nach Drift durch u. a. 0078/0120): 36 Zitate, 36 aufgeloest, 47
uebergangen, Rueckgabewert 0.

**5. Abgedruckter Lauf = ausgelieferter Stand.** Mein Lauf am Baum von `f8c8598`
nennt zeichengleich die Zahlen des im Nachweis abgedruckten Laufs (35/35/47, 42
Bauquellen, 11 Datendokumente, 166 im Zielbestand). Erfuellt.

**Dazu die Satzgrenze, von beiden Seiten eingeklemmt** (je ein Mutant am
ausgelieferten Stand, danach zurueckgenommen, M0 gruen):

| Mutant | Ergebnis |
|---|---|
| Aufrufstelle `untergrenze = 0` | Selbsttest gruen, Bestand rot an `rueckstand.md:131`, Code 1 -- die im Kopf ausgewiesene Luecke wird real vom Bestand gefangen |
| `suchuntergrenze` immer 0 | `SATZFAELLE` 1 und 4 rot, Code 2 |
| `suchuntergrenze` immer Satzanfang | `SATZFAELLE` 3 rot, Code 2 |

**Keine Abschwaechung.** Der Gesamtdiff des Ruecklaufs (`609c538..f8c8598`, nur diese
Datei) entfernt auf der Loeschseite ausschliesslich Kommentarsaetze (drei→vier
Tabellen, fuenf→sechs Gruppen), die alte Signatur von `naechster_verweis`, die alte
Aufrufstelle und die alte Selbsttest-Meldezeile. Alle vier alten Falltabellen
unveraendert (8/9/8/8 Faelle), Untergrenze 16 unangetastet, keine Erwartung gedreht.
`SATZFAELLE` traegt je Fall eine unabhaengige Herkunftsbegruendung und beide Haelften
(mit/ohne Schranke) -- ein echter Regressionsbestand, kein abgeschriebener Lauf.

## Der Befund: Teil 4 der Abnahme ist inhaltlich wahr, aber sein Nachweis nennt Zahlen, die kein ausgelieferter Stand liefert

Die Abnahme verlangt: "beides gemessen am selben Baum, vor und nach dem Eingriff, mit
genanntem Bezugsstand und **nach der letzten Zeile des Kopfkommentars**".

**Meine Messung** (Stand A = `489aafb` und Stand C = `f8c8598` als zwei Programme am
selben Baum von `f8c8598`, Vergleich der Aufzaehlungen ueber Datei:Zeile):

* A meldet 9 uebergangene Fundstellen, alle 9 stehen auch in C -- **verschwunden:
  null.** Die 9 decken sich einzeln mit der Tabelle in Nachweis-Abschnitt a).
* C meldet **47**, davon **38 neu**: **37** x *Gliederungsziffer statt Ueberschrift*,
  **1** x *Zieldatei fuehrt keine Ueberschrift* (`rueckstand.md:269`). Jede neue
  traegt einen der beiden 0079-Gruende -- kein anderer Grund kommt vor.

**Der Nachweis und der GEBAUT-Absatz im Paket sagen stattdessen: C = 46, davon 37
neu, 36 x Gliederungsziffer.** Diese Zahlen sind mit dem ausgelieferten Stand
unvereinbar, und zwar doppelt:

1. Sie widersprechen dem **eigenen abgedruckten Lauf im selben Dokument** (47
   uebergangene; 9 + 37 = 46 ≠ 47) -- und dessen 47 habe ich reproduziert.
2. Sie sind an **keinem Stand des Baulaufs** messbar: `2de4de7`, `5133001` und
   `f8c8598` liefern alle drei 47 uebergangene mit 37 Gliederungsziffern (je eigener
   Bau und Lauf am je eigenen Baum). Eine Messung "nach der letzten Zeile des
   Kopfkommentars" haette 47/38/37 ergeben muessen.

Das ist dieselbe Fehlerklasse, fuer die der Projektmanager den ersten Rucklauf gegeben
hat (abgedruckt 56, ausgeliefert 58) -- diesmal nicht im abgedruckten Lauf, sondern in
der Vorher/Nachher-Tabelle, also genau in dem Teil, den die neue Abnahme eingefuehrt
hat. Der Nachweis zitiert die Regel "nach der letzten Zeile des Kopfkommentars noch
einmal messen" selbst und befolgt sie fuer Abschnitt b) nicht. Ich winke das nicht
durch, weil ich damit das Kriterium senkte, das eigens gegen diesen Fehler in die
Abnahme geschrieben wurde.

**So erzeugt man den Fehler, Schritt fuer Schritt:**

1. `git archive f8c8598 ventures/0016-...` und `git archive f8c8598 specs/0016-...`
   nach `$TMPDIR` entpacken; Alleinbau; Lauf `belegstellen_riegel <baum> <specs>`.
   Ausgabe: 47 uebergangene Fundstellen.
2. Dasselbe mit der Riegelquelle und CMakeLists aus `489aafb` (Bau in
   Hilfsstruktur mit `werkzeugkette.cmake` jenes Standes), Lauf **am Baum aus
   Schritt 1**. Ausgabe: 9 uebergangene Fundstellen.
3. Beide Aufzaehlungen ueber `datei:zeile` vergleichen: 0 verschwunden, 38 neu
   (37 + 1).
4. Gegen Nachweis-Abschnitt b) und den GEBAUT-Absatz des Pakets halten ("C meldet
   46 ... davon 37 neu ... 36 x"): Widerspruch.

## Was fuer den naechsten Lauf zu tun ist -- es ist noch weniger als beim ersten Ruecklauf

Die A-gegen-C-Messung am ausgelieferten Stand neu fahren (nach der letzten Zeile des
Kopfkommentars) und die drei Zahlen in Nachweis-Abschnitt b) **und** im
GEBAUT-Absatz des Pakets berichtigen; dabei die 38. neue Fundstelle benennen. Nichts
anderes ist neu zu erbringen: Teile 1, 2, 3 und 5 sind oben mit eigenem Messweg
bestaetigt, die Satzgrenze ist doppelt eingeklemmt, und die beiden Bedingungen von
Teil 4 gelten in der Sache -- falsch ist allein, was als ihre Messung dasteht.

## Wonach ich gesucht und nichts gefunden habe

Abgeschwaechte Tests in der Versionsgeschichte (Loeschseiten aller drei Commits des
Ruecklaufs); Verlust aufgeloester Zitate durch die Schranke (35 bleiben 35, am
heutigen Korpus 36); eine Entscheidungsliste statt der benannten Eigenschaft;
Fundstellen mit fremdem Grund unter den neuen; Abhaengigkeit des Urteils von den
`bau/`-Namen.
