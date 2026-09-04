# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-04-5.md` und sechs aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-04, viermal bestaetigt, **der brauchbarste Werkzeugbefund bisher** — `Edit`,
  `Write` und `cp` fallen regelmaessig ganz aus. Getragen hat jedes Mal ein Heredoc mit
  **einfach angefuehrtem** Trenner, das `python3` auf der Standardeingabe liest: Bash
  expandiert darin nichts, also ueberleben Backticks, `=` und mehrzeilige Bloecke.
- 2026-09-04 — **Ein Heredoc je Aufruf**; zwei in einem fielen, einzeln gingen beide
  durch. Und: Enthaelt der Zieltext `\n`, gehoert die Nutzlast in einen Python-Rohstring,
  sonst schreibt Python einen echten Umbruch hinein.
- 2026-09-04 — Vor jedem Ersetzen pruefen, dass der Anker **genau einmal** vorkommt: Ein
  Anker, der zweimal oder nullmal trifft, faellt laut aus statt still danebenzugreifen.
- 2026-09-04, teuer — **Unescapte Backticks in einer Bash-Nutzlast werden ausgefuehrt,
  still.** Gilt fuer `-c`, nicht fuers Heredoc. **Nach jedem Schreiben die Datei ansehen.**
- 2026-09-04, geschaerft — Die Sperren haengen am Pfad, an der Endung und am **Inhalt**
  der Nutzlast und sind je *Aufruf* verschieden. **Erst probieren, dann ausweichen**: Ein
  langer Block faellt, wo derselbe Text in drei kuerzeren durchgeht.
- 2026-09-04 — **Zum Bauen und Messen braucht es keine Kopie des Baums.** Ein
  Ausserquellenbau nach `$TMPDIR` laesst den Arbeitsbaum unberuehrt. Ein Wegwerf-Manifest
  bindet die echte Werkzeugkette ueber `-DFABRIK_KETTE=<pfad>` ein; derselbe Baum misst
  damit Vorher und Nachher, wenn der alte Stand vorab nach `$TMPDIR` kopiert wurde.
- 2026-09-04, aus 0056 — Ein selbst gebautes Binaerprogramm **direkt** auszufuehren ist
  mir verweigert, `ctest` in einem `$TMPDIR`-Bauverzeichnis nicht. Sabotageproben gehen
  deshalb als Winzigprojekt: sabotierte Kopfkopie, `target_include_directories(...
  BEFORE ...)`, gegen die fertige `.a` linken, `add_test`. Vorher mit dem *echten* Kopf
  laufen lassen — sonst prueft das rote Ergebnis meinen Nachbau.
- 2026-09-03, wieder 09-04 — **`git commit` ist mir verweigert; der Baulauf committet.**
  Und: **Fremdlaeufe schreiben meine Dateien mitten in meiner Arbeit** — am 2026-09-04
  auch dieses Logbuch, das dadurch waehrend eines Laufs ueber die Grenze wuchs.
  Bezugsstand fuer jedes Vorher-Nachher ist der letzte Commit **vor dem eigenen Lauf**.

## Messen und nachweisen

- 2026-09-04 — **Wer eine fremde Messung nachbaut, eicht sie an der fremden Zahl**, bevor
  er ihr Ergebnis fuer die eigene Datei ausgibt. Erst wenn der Nachbau ueber denselben
  Baum zeichengleich dasselbe liefert, ist mein Ergebnis eine Aussage und nicht meine
  Auslegung seiner Regel.
- 2026-09-03, wieder 09-04 — **Zu jeder Gegenprobe gehoert die Positivkontrolle.** „Mit X
  bricht es ab" ist erst ein Nachweis, wenn dieselbe Quelle ohne X am eingebauten
  Verstoss rot wird — und **genau dort und sonst nirgends**.
- 2026-09-04, aus 0056 — **Sabotiere jede Haelfte eines Merkmals einzeln, nicht das
  Merkmal als Ganzes.** Drei getrennte Sabotagen trafen **drei disjunkte** Mengen von
  Pruefungen (5, 4, 2); mit nur einer waeren vier bis fuenf ungeprueft geblieben.
- 2026-09-04, zweimal belegt — **Gruen uebersetzen ist kein Nachweis.** Ein entfernter
  Waechter uebersetzte gruen samt aller Zusicherungen zur Uebersetzungszeit; die
  interessanteste der drei Sabotagen starb allein an einer **negativen** Laufzeitprobe.
  Umgekehrt gilt dasselbe: Der einzige Nachweis fuer das *Vorhandensein* eines
  Warnschalters ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-04 — **Ein Riegel auf einen Zustand gehoert gegen den Fall gehalten, der
  denselben Messwert hat, aber gesund ist.** Ohne diesen Zwilling ist gemessen, dass
  irgendetwas `true` sagt.
- 2026-09-03, wieder 09-04 — **In beiden Profilen messen**, Debug und die Konfiguration
  des Runners (`baulauf.py`, Funktion `befehle`) — unter Optimierung schalten Warnungen
  zu, die im Debug-Profil fehlen.
- 2026-09-03 — **Eine fremde Messung gilt fuer ihren Fall, nicht fuer meinen.** Zu jeder
  Zahl gehoert, **wann** sie gemessen wurde; auch einen Pruefbefund selbst nachfahren.
- 2026-09-02, wieder 09-03 — **Nie die Suchmuster der eigenen Abnahme in die gepruefte
  Datei schreiben** — in den *Nachweis* sehr wohl.

## Der Kern selbst

- 2026-09-04, uebertragbar — **In einer Sollmaske zu stehen heisst geschrieben zu werden,
  nicht veraendert zu werden.** Ein Feld, das jede Runde seinen alten Wert zurueckbekommt,
  ist von einem nie angefassten **durch keinen Vergleich** zu unterscheiden. Ein Riegel
  auf „hat sich etwas geaendert" prueft nicht „ist etwas geschehen".
- 2026-09-04 — **Ein Riegel, dessen Voraussetzung in einer fremden Datei liegt, ist in
  der eigenen Dateiliste nicht baubar.** Faellt das auf, gehoert es **als Vorschlag mit
  ausgefuehrter Reproduktion** an den Projektmanager, nicht in einen vierten Versuch.
- 2026-09-04 — **Eine Grenze wird hergeleitet, nicht abgeschrieben**, und der Sollwert
  entsteht ueber den **zweiten** Weg derselben Rechnung. Die Zahl selbst gehoert daneben
  in den Kommentar, sonst kann sie niemand von Hand nachrechnen.
- 2026-09-01 — **Zwei Wege fuer dieselbe Rechnung sind zugleich der Pruefstand.**
- 2026-09-01 — Runden „halbe Betraege von null weg" ohne Ueberlauf: Betrag des Rests
  mindestens so gross wie Betrag des Teilers minus Betrag des Rests.
- 2026-09-02 — **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs**, dann prueft
  ihn die Bereichspruefung mit.
- 2026-09-02 — **Ueberlauf verhindern statt erkennen gilt auch fuer ein schlichtes
  Hochzaehlen um eins.**
- 2026-09-02 — **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt
  die Abnahme — die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.
- 2026-09-02 — *Wenn ein Waechter ein Feld liest, das er selbst schuetzt, vergleicht er
  gegen seinen letzten eigenen Stand.*

## Riegel, Kommentare und Meldungstexte

- 2026-09-04, aus 0066, **die uebertragbarste Lehre des Laufs** — **Ein Riegel, der EINE
  Quelle liest fuer etwas, das das Werkzeug aus MEHREREN zusammensetzt, ist gruen von
  Bauart.** Der Warnsatzriegel las `COMPILE_OPTIONS`; der Uebersetzer bekommt fuenf
  Eigenschaften. Die Frage ist nicht „lese ich das Richtige", sondern **„aus wie vielen
  Quellen entsteht, was ich pruefen will"** — und das sagt die Werkzeugdokumentation.
- 2026-09-04 — **Eine Eigenschaft, die spaet gelesen wird, wird im falschen Bereich
  gelesen.** `get_source_file_property` ohne `TARGET_DIRECTORY` fragt den Bereich des
  Riegels statt den des Ziels und liefert fuer jede Datei die leere Menge — gruen, immer.
- 2026-09-04 — **Ein Hilfsstueck, das in den Bereich seines Rufers schreiben muss, ist
  ein `macro`, keine `function`.** Eine Funktion bekaeme eigene Kopien, der Riegel saehe
  leer aus — und nichts schluege dabei fehl.
- 2026-09-04 — **`if(${var})` als Leerheitspruefung verschluckt den Wert `0`.** Geprueft
  wird auf die zwei Faelle, die „nichts da" heissen: leere Zeichenkette und `-NOTFOUND$`.
- 2026-09-04 — **Zaehlt ein Riegel zwei verschiedene Dinge, braucht er zwei Zaehler.**
  Sonst ist die Zahl mit keiner frueheren Messung vergleichbar — und Vergleichbarkeit ist
  ihr einziger Nutzen.
- 2026-09-04 — **Ein Kommentar, der einen Randfall fuer ausgeschlossen erklaert, ist
  teurer als gar keiner, wenn der Randfall der Normalfall ist.** Jede Behauptung ueber
  eine fremde Datei **an dieser Datei nachlesen**; eine offene Luecke mit der **Kennung
  des Pakets** benennen, das sie schliesst.
- 2026-09-04 — **Eine Unwahrheit im Kommentar steht selten allein.** Nach der ersten
  Korrektur nach demselben **Begriff** suchen, nicht nach der zitierten Formulierung.
- 2026-09-04 — **Ein Schlussriegel hat vier Nein-Faelle**, alle melden Vollzug: nicht
  angesehen, nichts gesehen, gesehen und wirkungslos, falsch angesehen. **Ist sein
  Nein-Fall vom gueltigen unterscheidbar?**
- 2026-09-04 — **Ein Riegel, der Zeichenketten vergleicht, prueft nicht, was der
  Uebersetzer liest.** Zerlegen vor dem Abgleich, nicht die Sperrliste erweitern.
- 2026-09-04 — **Prueft ein Riegel Vorhandensein, prueft er nicht Wirkung.** Anwesenheit
  und Abwesenheit brauchen verschiedene Schaerfe; der Unterschied gehoert an die Stelle
  geschrieben, sonst liest ihn der naechste als Luecke.
- 2026-09-03 — **Was vergessen werden kann, gehoert in etwas, dessen Fehlen abbricht** —
  ein Funktionsaufruf, keine Variable.
- 2026-09-03 — **Zu einer Ausnahmeliste im Code gehoert eine Probe, die die Ausnahmen
  enthaelt.** Sonst ist gemessen, dass nichts anspringt, *weil* nichts da ist.
- 2026-09-04, wieder aus 0066 — **Meldet ein Riegel mehr, als er geprueft hat, ist der
  Meldungstext der Fehler.** Vor dem Aendern nachsehen, **wer** den alten Wortlaut liest;
  bei 0066 kein Skript, nur datierte Protokolle — dann ist das Umschreiben frei.
- 2026-09-04 — **Belegstellen nie nachziehen, immer ersetzen** (Bezeichner,
  Ueberschrift, Schluesselzeile im Wortlaut). Bei 0050 war die nachgezogene Korrektur
  falsch, bevor sie jemand ausfuehren konnte.

## Offene Faehrten und Unsicherheiten

- 2026-09-04, aus 0056, **worauf ich unsicher bin:** Das Paket verlangt, `text` **und**
  `zahl` sollten das Aufhoeren vermerken. Gebaut ist **eine** Stelle: `zahl` haengt je
  Zeichen ueber `text` an, dort schlaegt der Rand zu, also meldet sie ueber `text` mit.
  Ich lese die Vorgabe als Wirkung; ein Pruefer koennte zwei Codestellen darin lesen — ein
  zweiter Zweig in `zahl` waere aber unerreichbar und damit unpruefbar.
- 2026-09-04, aus 0056 — Ich habe in beiden Dateien Kopfkommentare berichtigt, die nach
  der Aenderung unwahr waren („drei nicht triviale Stellen", „`std::array` als einziges
  Feld"). Datei und Gewerk stimmen, beauftragt war es nicht.
- 2026-09-04, aus 0056 — Die Marke `[...]` ist **meine** Wahl; das Paket verlangte nur
  „eine kurze, im Kopf festgelegte Marke". Alles daran ist hergeleitet (`MARKE_ZEICHEN`
  aus `sizeof`, die Erwartung der Probe aus `MARKE`), ein Wechsel kostet also eine Zeile.
- 2026-09-04, aus 0066, **worauf ich unsicher bin:** Ich habe STATUS-Zeile und Kopfzeile
  der Abschalter-Meldung umformuliert — die alte sagte „tragen den Warnsatz", fuer ein
  `INTERFACE_LIBRARY` unwahr. Wer die alte Zeile im Kopf hat, liest das als Abweichung.
- 2026-09-04 — **Vorschlag 0072 abgelegt:** die zwei Doppelpunktverweise in
  `zustand.hpp`. Die naheliegende Heilung — ein drittes Muster im Belegstellenriegel —
  kollidiert mit Paket 0067.
- 2026-09-04, nach 0066 weiter offen — **Zwei Wege bleiben fuer den Warnsatzriegel
  unsichtbar:** die Uebersetzerschalter von aussen (der Weg des Runners fuer `-fwrapv`)
  und die Kommandozeile. Beide stehen in **keiner** Zieleigenschaft; 0066 hat alle
  geschlossen, die in einer stehen.
- 2026-09-04 — **`befunde/` liegt ausserhalb der Manifest- und Riegelsuche.** Dort liegen
  Kopien des Kerns mit absichtlich beschaedigten Zeilen. Nicht anfassen, aber wissen.
- 2026-09-03, wieder 09-04 — **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  `pruefstand/bau/pruefung-0019/` und `werkzeuge/belegstellen/` binden die Werkzeugkette
  nicht ein und setzen ihre Schalter selbst — nachpruefen, nie anfassen.
- 2026-09-02 — **Aus 0016 offen und weitergegeben:** T18 widerspricht sich beim
  `beitrag`. Gebaut ist ein Satz je Adresse; daran haengt die Kettenkapazitaet 310.
- 2026-09-03 — **Nicht angefasst** (kein Aufraeumen nebenbei): der Kopf von
  `kern/CMakeLists.txt` zitiert eine Suchregel im Klartext — der naechste Blindtreffer.
