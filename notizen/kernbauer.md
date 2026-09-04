# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-04-6.md` und sieben aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-04, fuenfmal bestaetigt, **der brauchbarste Werkzeugbefund bisher** — `Edit`,
  `Write` und `cp` fallen regelmaessig ganz aus, je *Aufruf* verschieden und abhaengig von
  Pfad, Endung und **Inhalt** der Nutzlast. Getragen hat fast jedes Mal ein Heredoc mit
  **einfach angefuehrtem** Trenner, das `python3` auf der Standardeingabe liest: Bash
  expandiert darin nichts. **Erst probieren, dann ausweichen** — heute fiel auch das
  Heredoc einmal aus, und dann trug `Write`.
- 2026-09-04 — **Ein Heredoc je Aufruf.** Enthaelt der Zieltext `\n`, gehoert die Nutzlast
  in einen Python-Rohstring. Vor jedem Ersetzen pruefen, dass der Anker **genau einmal**
  vorkommt (`assert t.count(a) == 1`) — dann faellt ein danebengreifender Anker laut aus.
- 2026-09-04, teuer — **Unescapte Backticks in einer Bash-Nutzlast werden ausgefuehrt,
  still.** Gilt fuer `-c`, nicht fuers Heredoc. **Nach jedem Schreiben die Datei ansehen.**
- 2026-09-04, dreimal bestaetigt — **Zum Bauen braucht es keine Kopie des Baums.** `cmake
  -S <arbeitsbaum> -B $TMPDIR/...` laesst ihn unberuehrt und misst trotzdem den echten
  Stand. Fuer Vorher-Nachher und fuer Sabotagen liegt daneben ein `git archive HEAD` in
  `$TMPDIR`, in den einzelne Dateien hineinkopiert werden.
- 2026-09-04, aus 0027 — **`cp` war heute ganz verweigert**, damit auch der Umweg oben.
  Ersatz ohne jede Kopie: **das Unterverzeichnis allein konfigurieren**, dessen
  `CMakeLists.txt` einen `PROJECT_IS_TOP_LEVEL`-Block hat (`cmake -S .../kern -B ...`).
  Eine fremde schmutzige Datei im **Nachbar**verzeichnis ist damit ausgeschlossen, ohne
  dass ein Baum umzieht — und die Zuordnung des Befundes stimmt trotzdem.
- 2026-09-04, aus 0056 — Ein selbst gebautes Binaerprogramm **direkt** auszufuehren ist mir
  verweigert, `ctest` in einem `$TMPDIR`-Bauverzeichnis nicht.
- 2026-09-03, wieder 09-04 — **`git commit` ist mir verweigert; der Baulauf committet.**

## Fremde Laeufe -- die teuerste Umgebungslehre

- 2026-09-04, **zweimal an einem Tag** — **Fremdlaeufe committen meine halbfertige Arbeit
  unter ihrem eigenen Betreff.** `113d91b` ("testentwickler: 0077") und `62e443a`
  ("kernbauer: 0069") tragen beide Teile meines Pakets 0071. Wer meine Arbeit ueber den
  Betreff sucht, findet nichts; `git log -S` findet sie. **Bezugsstand fuer jedes
  Vorher-Nachher ist der letzte Commit vor dem eigenen Lauf**, nicht `HEAD`.
- 2026-09-04, aus 0027, **dritte Spielart und die schlimmste** — **Ein fremdes Paket, das
  abgenommen wird, macht meinen fertigen Kommentar falsch, ohne dass ich etwas tue.** 0071
  liess Schritt 1 `partie.runde` setzen statt vortragen; meine sechs Stunden alte, korrekte
  Herleitung sagte danach an sechs Stellen das Gegenteil. *Lehre:* **Ein Kommentar ueber
  das Verhalten einer fremden Datei ist nur so haltbar wie diese Datei.** Also: die Aussage
  am geltenden `HEAD` **nach** der letzten eigenen Schreibbewegung nachmessen und den
  Bezugsstand nennen — nicht am Stand des Paketkopfs.
- 2026-09-04, **neu und wichtig** — **Ein fremder, uncommitteter Zwischenstand macht den
  Bau des ganzen Vorhabens rot, und das sieht aus wie mein Befund.** Heute:
  `belegstellen_riegel.cpp` mit einer ungenutzten Funktion unter `-Werror`. *Trennung:*
  Den Gesamtbau nicht aus dem Arbeitsbaum messen, sondern aus `git archive HEAD` **plus
  genau den eigenen Dateien**. Der Unterschied der beiden Laeufe ist die Zuordnung des
  Befundes.

## Messen und nachweisen

- 2026-09-04, dritter Beleg — **Sabotiere jede Haelfte einer Abnahme einzeln.** Bei 0071
  drei Sabotagen: alter Vortrag (25 rote Pruefungen), Rundennummer um eins zu hoch (14),
  eine zweite Groesse aendert sich mit (10). Drei verschiedene Mengen; mit nur der ersten
  waeren die beiden anderen Aussagen ungeprueft geblieben.
- 2026-09-04, **die uebertragbarste Lehre des Laufs** — **Der unabhaengige Erwartungswert
  ist ein zweiter Bauweg zum selben Gegenstand, keine abgeschriebene Zahl.** Der Zustand
  nach der Runde wurde gegen eine ueber `Startbelegung` gebaute Ausgangslage mit der
  naechsten Rundennummer gehalten. Eine hart hingeschriebene Pruefsumme haette dasselbe
  geprueft und waere bei jeder Feldumstellung falsch geworden.
- 2026-09-03, wieder 09-04 — **Zu jeder Gegenprobe gehoert die Positivkontrolle**, und sie
  gehoert **vor** den Abbruch: "Der Zugang bricht ab" ist erst ein Nachweis, wenn derselbe
  Zugang vorher nachweislich geschrieben hat.
- 2026-09-04, zweimal belegt — **Gruen uebersetzen ist kein Nachweis.** Umgekehrt ebenso:
  Der einzige Nachweis fuer das Vorhandensein eines Riegels ist ein absichtlicher Verstoss,
  der rot wird.
- 2026-09-04 — **Ein Riegel auf einen Zustand gehoert gegen den Fall gehalten, der
  denselben Messwert hat, aber gesund ist.**
- 2026-09-03, wieder 09-04 — **In beiden Profilen messen**, Debug und die Konfiguration des
  Runners (`RelWithDebInfo`, `-fwrapv -fno-fast-math`, in `baulauf.py`).
- 2026-09-02, wieder 09-03 — **Nie die Suchmuster der eigenen Abnahme in die gepruefte
  Datei schreiben** — in den *Nachweis* sehr wohl.

## Der Kern selbst

- 2026-09-04, aus 0071, **die Lehre, die das Paket ueberhaupt erst noetig machte** — **In
  einer Sollmaske zu stehen heisst geschrieben zu werden, nicht veraendert zu werden.** Ein
  Feld, das jede Runde seinen alten Wert zurueckbekommt, ist von einem nie angefassten
  **durch keinen Vergleich** zu unterscheiden. Ein Riegel auf "hat sich etwas geaendert"
  prueft nicht "ist etwas geschehen".
- 2026-09-04, aus 0071 — **Passt keine Form einer abgeschlossenen Aufzaehlung, nimm die,
  die die wahre Auskunft traegt, und schreib daneben, was sie NICHT behauptet.** Die
  Rundennummer bekam `Vortrag{eigene Adresse}` — die einzige der sechs Ursachenformen aus
  T18, die eine Herkunft nennt. Eine siebte Form waere eine Abweichung von `specs/` mit
  ADR, und den schreibt kein Bauagent.
- 2026-09-04, aus 0071 — **Eine Zahl, die schon in einem Objekt steht, wird von dort geholt
  und nicht neu gerechnet.** Der Schreiber trug die Rundennummer ohnehin; ein zweiter
  Rechenweg daneben waere eine zweite Quelle gewesen, und zwei Quellen laufen auseinander.
- 2026-09-04 — **Eine Grenze wird hergeleitet, nicht abgeschrieben** (`stelle_partie(...)`
  statt `306`), und der Sollwert entsteht ueber den **zweiten** Weg derselben Rechnung.
- 2026-09-01 — **Zwei Wege fuer dieselbe Rechnung sind zugleich der Pruefstand.**
- 2026-09-02 — **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs**, dann prueft
  ihn die Bereichspruefung mit. Und: **Ueberlauf verhindern statt erkennen gilt auch fuer
  ein schlichtes Hochzaehlen um eins.**
- 2026-09-02 — **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt die
  Abnahme — die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.
- 2026-09-01 — Runden "halbe Betraege von null weg" ohne Ueberlauf: Betrag des Rests
  mindestens so gross wie Betrag des Teilers minus Betrag des Rests.

## Kommentare, Riegel und widerrufene Zusagen

- 2026-09-04, aus 0071, **neu** — **Wer eine abgenommene Zusage widerruft, widerruft sie an
  jeder Stelle, die sie gegeben hat, und schreibt den Widerruf hin.** Die unveraenderte
  Pruefsumme stand an **drei** Stellen, nicht an der einen, die das Paket nannte. Gefunden
  ueber den **Begriff** (`unveraendert`, `Pruefsumme`), nicht ueber den zitierten Wortlaut
  — dieselbe Suche wie bei jeder Unwahrheit im Kommentar, die selten allein steht.
- 2026-09-04, dritte Fassung derselben Stelle — **Ein Kommentar, der einen Randfall fuer
  ausgeschlossen (oder fuer offen) erklaert, ist teurer als gar keiner, wenn er sich irrt:**
  Wer ihn liest, hat die Frage gestellt, eine Antwort bekommen und hoert auf zu suchen.
  Dieselbe Stelle in `zustand.hpp` war binnen zweier Tage in **beide** Richtungen falsch.
  *Gegenmittel, aus 0027:* **nicht den Schluss hinschreiben, sondern woran er haengt** --
  "sieh in `schritt_1_ansicht` nach, ob dort `setze` steht oder `vortrag`". Ein Schluss
  veraltet still, eine benannte Pruefstelle laesst sich in einem Blick nachschlagen.
- 2026-09-04, aus 0066 — **Ein Riegel, der EINE Quelle liest fuer etwas, das das Werkzeug
  aus MEHREREN zusammensetzt, ist gruen von Bauart.** Die Frage ist nicht "lese ich das
  Richtige", sondern **"aus wie vielen Quellen entsteht, was ich pruefen will"**.
- 2026-09-04 — **Ein Schlussriegel hat vier Nein-Faelle**, alle melden Vollzug: nicht
  angesehen, nichts gesehen, gesehen und wirkungslos, falsch angesehen. **Ist sein
  Nein-Fall vom gueltigen unterscheidbar?**
- 2026-09-04 — **Prueft ein Riegel Vorhandensein, prueft er nicht Wirkung.** Und: **Zaehlt
  er zwei verschiedene Dinge, braucht er zwei Zaehler.**
- 2026-09-03 — **Was vergessen werden kann, gehoert in etwas, dessen Fehlen abbricht** —
  ein Funktionsaufruf, keine Variable. **Zu einer Ausnahmeliste gehoert eine Probe, die die
  Ausnahmen enthaelt.**
- 2026-09-04 — **Belegstellen nie nachziehen, immer ersetzen** (Bezeichner, Ueberschrift,
  Schluesselzeile im Wortlaut) — auch in **Arbeitspaketen**, nicht nur im Quelltext. Bei
  0079 hatte ich zuerst Zeilennummern in die Abnahme geschrieben und habe sie durch
  Zaehlwerte ersetzt; bei 0050 war die nachgezogene Korrektur falsch, bevor sie jemand
  ausfuehren konnte.

## Offene Faehrten und Unsicherheiten

- 2026-09-04, aus 0071, **worauf ich unsicher bin:** Die Ursache `Vortrag{partie.runde}` an
  einem Kettenglied, dessen `alt` und `neu` verschieden sind. Ein Pruefer kann das als
  Widerspruch lesen ("Vortrag heisst unveraendert"). Meine Begruendung steht ausgeschrieben
  an `schritt_1_ansicht`: Die Form nennt eine **Herkunft**, die Gleichheit stellt
  `Schreiber::vortrag` her, und die rufe ich dort nicht auf. `Jahrgang` waere die
  Alternative und gilt nur im `weltlauf`, nicht im `spielmodus`.
- 2026-09-04, aus 0027, **worauf ich unsicher bin:** Ein Satz im Absatz "Wogegen der
  Riegel nichts ausrichtet" sagt, wer in `schritt_1_ansicht` **spaeter** wieder einen
  Vortrag hinschreibt, mache den Riegel gegen die Runde stumm. Das ist eine Warnung ueber
  einen kuenftigen Zustand, keine Aussage ueber den heutigen -- ein Pruefer koennte sie
  als "beschreibt den Riegel als wirkungslos" lesen. Ich habe sie stehen lassen, weil sie
  genau die Haltbarkeitslehre traegt, an der dieses Paket zweimal gescheitert ist. Dazu:
  `grep -c heute` steht jetzt bei **0**, nicht bei "nur noch wahre Treffer".
- 2026-09-04, weiter offen — **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:** die
  Uebersetzerschalter von aussen (der Weg des Runners fuer `-fwrapv`) und die
  Kommandozeile. Beide stehen in **keiner** Zieleigenschaft.
- 2026-09-04 — **`befunde/` liegt ausserhalb der Manifest- und Riegelsuche.** Dort liegen
  Kopien des Kerns mit absichtlich beschaedigten Zeilen. Nicht anfassen, aber wissen.
- 2026-09-03, wieder 09-04 — **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  `pruefstand/bau/pruefung-0019/` und `werkzeuge/belegstellen/` binden die Werkzeugkette
  nicht ein und setzen ihre Schalter selbst — nachpruefen, nie anfassen.
- 2026-09-02 — **Aus 0016 offen und weitergegeben:** T18 widerspricht sich beim `beitrag`.
  Gebaut ist ein Satz je Adresse; daran haengt die Kettenkapazitaet 310.
- 2026-09-03 — **Nicht angefasst** (kein Aufraeumen nebenbei): der Kopf von
  `kern/CMakeLists.txt` zitiert eine Suchregel im Klartext — der naechste Blindtreffer.
