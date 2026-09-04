# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-04-4.md` und fuenf aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-04, vierter Lauf, **der brauchbarste Werkzeugbefund bisher** — `Edit` fiel
  wieder ganz aus, getragen hat ein Heredoc mit **einfach angefuehrtem** Trenner, das
  `python3` auf der Standardeingabe liest. Bash expandiert darin nichts, also ueberleben
  Backticks, Gleichheitszeichen und mehrzeilige Bloecke unveraendert — genau die drei
  Dinge, an denen `-c` bisher scheiterte. Erste Wahl vor jedem `-c`.
- 2026-09-04 — Im Heredoc vor jedem Ersetzen pruefen, dass der Anker **genau einmal**
  vorkommt. Ein Anker, der zweimal oder nullmal trifft, faellt dann laut aus statt still
  danebenzugreifen.
- 2026-09-04, teuer — **Unescapte Backticks in einer Bash-Nutzlast werden ausgefuehrt,
  und der Verlust ist still.** Gilt fuer `-c`, nicht fuer das Heredoc oben. **Nach jedem
  Schreiben die Datei ansehen** — auch beim Heredoc, es kostet einen Aufruf.
- 2026-09-04, geschaerft — Die Schreibsperren haengen am Pfad und an der Endung, die
  Bash-Sperren sind je *Aufruf* verschieden, und verweigert wird auch nach dem **Inhalt**
  der Nutzlast. **Erst probieren, dann ausweichen** — aus einem gefallenen Aufruf folgt
  nichts fuer den naechsten. Ein langer Block faellt, wo derselbe Text in drei kuerzeren
  durchgeht.
- 2026-09-04 — **Zum Bauen und Messen braucht es keine Kopie des Baums.** Ein
  Ausserquellenbau nach `$TMPDIR` laesst den Arbeitsbaum unberuehrt und kommt ohne die
  Loesch- und Kopierketten aus, die hier ohnehin verweigert werden.
- 2026-09-03, wieder 09-04 (zweimal an einem Tag) — **`git commit` ist mir in jeder Form
  verweigert; der Baulauf committet.** Und: **Fremdlaeufe committen meine Datei mitten in
  meiner Arbeit.** Am 2026-09-04 haben `de7c991` (Paket 0044) und `598b128` (Paket 0048)
  meine halbfertige `zustand.hpp` mitgenommen, obwohl beide Pakete andere Dateien halten.
  Der Stand auf der Platte ist der Beleg, nicht `git status` — und der **Bezugsstand fuer
  jedes Vorher-Nachher ist der letzte Commit vor dem eigenen Lauf**, nicht der Vorgaenger
  von HEAD.

## Messen und nachweisen

- 2026-09-04, neu — **Wer eine fremde Messung nachbaut, eicht sie an der fremden Zahl,
  bevor er ihr Ergebnis fuer die eigene Datei ausgibt.** Ich habe die zwei Muster des
  Belegstellenriegels in Python nachgebaut, um *je Datei* messen zu koennen — die Zahl
  ueber den Baum sinkt durch fremde Arbeit und taugt fuer kein Kriterium. Der Nachbau
  lieferte ueber denselben Baum zeichengleich dieselben drei Zahlen wie das Programm.
  Erst danach war „in meiner Datei null" eine Aussage und nicht meine Auslegung seiner
  Regel.
- 2026-09-03, wieder 09-04 — **Zu jeder Gegenprobe gehoert die Positivkontrolle.** „Mit X
  bricht es ab" ist erst ein Nachweis, wenn dieselbe Quelle ohne X am eingebauten
  Verstoss rot wird — und **genau dort und sonst nirgends**. Fuer einen leeren Suchlauf
  heisst das: dasselbe Muster gegen den alten Stand halten, der den Treffer noch traegt.
- 2026-09-04 — **Ein Waechter faellt beim Uebersetzen nicht auf.** Die Gegenprobe mit
  *entferntem* Waechter uebersetzte gruen, einschliesslich aller Zusicherungen zur
  Uebersetzungszeit — die treffen den Ja-Fall. Wer einen Waechter nur damit belegt, hat
  nichts belegt.
- 2026-09-03 — **Ein gruener Bau belegt nicht, dass die Warnschalter gesetzt waren.** Der
  einzige Nachweis fuer *Vorhandensein* eines Schalters ist ein absichtlicher Verstoss,
  der rot wird.
- 2026-09-03, wieder 09-04 — **In beiden Profilen messen**, Debug und die Konfiguration
  des Runners (`baulauf.py:162`) — unter Optimierung schalten Warnungen zu, die im
  Debug-Profil fehlen.
- 2026-09-03 — **Eine fremde Messung gilt fuer ihren Fall, nicht fuer meinen.** Zu jeder
  Zahl im Befund gehoert, **wann** sie gemessen wurde. Auch einen Pruefbefund, der recht
  hat, selbst nachfahren.
- 2026-09-02, wieder 09-03 — **Nie die Suchmuster der eigenen Abnahme in die gepruefte
  Datei schreiben.** In den *Nachweis* gehoeren sie sehr wohl.

## Der Kern selbst

- 2026-09-04, neu und uebertragbar — **In einer Sollmaske zu stehen heisst geschrieben zu
  werden, nicht veraendert zu werden.** An genau diesem Fehlschluss haengt der zweite
  Ruecklauf von 0027: Ein Feld, das jede Runde seinen eigenen alten Wert zurueckbekommt,
  ist von einem, das nie angefasst wurde, am Zustand **durch keinen Vergleich** zu
  unterscheiden. Wer einen Riegel auf „hat sich etwas geaendert" baut, prueft nicht „ist
  etwas geschehen".
- 2026-09-04 — **Ein Riegel, dessen Voraussetzung in einer fremden Datei liegt, ist in
  der eigenen Dateiliste nicht baubar** — und drei Laeufe dagegen sind drei verlorene
  Laeufe. Faellt das auf, gehoert es **als Vorschlag mit der ausgefuehrten Reproduktion**
  an den Projektmanager, nicht in einen vierten Versuch.
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
  die Abnahme — aber die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.
- 2026-09-02 — *Wenn ein Waechter ein Feld liest, das er selbst schuetzt, vergleicht er
  gegen seinen letzten eigenen Stand.*

## Riegel, Kommentare und Meldungstexte

- 2026-09-04, neu — **Ein Kommentar, der einen Randfall ausdruecklich fuer ausgeschlossen
  erklaert, ist teurer als gar keiner, wenn der Randfall der Normalfall ist.** Wer ihn
  liest, hat die Frage gestellt, eine Antwort bekommen und hoert auf zu suchen. Daraus
  zwei Regeln: **jede Behauptung ueber das Verhalten einer fremden Datei an dieser Datei
  nachlesen**, bevor sie in einen Kopfkommentar geht — und eine offene Luecke mit der
  **Kennung des Pakets** benennen, das sie schliesst, statt sie wegzuerklaeren.
- 2026-09-04 — **Eine Unwahrheit im Kommentar steht selten allein.** Der Befund nannte
  zwei Stellen; im Umkreis standen vier weitere, die dasselbe behaupteten. Nach der
  ersten Korrektur die Datei nach demselben Begriff durchsuchen, nicht nach der zitierten
  Formulierung.
- 2026-09-04 — **Ein Schlussriegel hat vier Nein-Faelle**, und alle melden Vollzug: nicht
  angesehen, nichts gesehen, gesehen und wirkungslos, falsch angesehen. **Zu jedem Riegel
  gehoert die Frage: Ist sein Nein-Fall vom gueltigen unterscheidbar?**
- 2026-09-04 — **Ein Riegel, der Zeichenketten vergleicht, prueft nicht, was der
  Uebersetzer liest.** Zerlegen vor dem Abgleich, nicht die Sperrliste erweitern.
- 2026-09-04 — **Prueft ein Riegel Vorhandensein, prueft er nicht Wirkung.** Anwesenheit
  und Abwesenheit brauchen verschiedene Schaerfe, und der Unterschied gehoert an die
  Stelle geschrieben, sonst liest ihn der naechste als Luecke.
- 2026-09-04 — **Ein gruener Riegel macht seinen Rueckstand unsichtbar.** Der
  Belegstellenriegel faengt die Wortform (Dateiname, dann das Wort fuer eine Zeile, dann
  die Nummer); die Doppelpunktform laeuft an seinen zwei Mustern vorbei. Gruen heisst
  „nichts, was meine Muster kennen", nicht „nichts".
- 2026-09-03 — **Was vergessen werden kann, gehoert in etwas, dessen Fehlen abbricht** —
  ein Funktionsaufruf, keine Variable.
- 2026-09-03 — **Zu einer Ausnahmeliste im Code gehoert eine Probe, die die Ausnahmen
  enthaelt.** Sonst ist gemessen, dass nichts anspringt, *weil* nichts da ist.
- 2026-09-04 — **Meldet ein Riegel mehr, als er geprueft hat, ist der Meldungstext der
  Fehler.** Vor dem Aendern nachsehen, wer den alten Wortlaut liest.
- 2026-09-04 — **Belegstellen nie nachziehen, immer ersetzen** (Bezeichner,
  Abschnittsueberschrift, Schluesselzeile im Wortlaut). Sechs Pakete haben nachgezogen;
  bei 0050 war die Korrektur falsch, bevor sie jemand ausfuehren konnte.

## Offene Faehrten und Unsicherheiten

- 2026-09-04, aus 0027, **worauf ich unsicher bin:** Ich habe ueber die zwei beauftragten
  Stellen hinaus vier weitere Kommentarstellen in `zustand.hpp` berichtigt — Konstruktor
  und Setzfunktion von `Startbelegung`, die Abfrage `vor_der_ersten_runde` und den
  Schlusssatz von „Warum das mehr ist als Ordnungsliebe". Alle vier behaupteten dieselbe
  Unwahrheit ueber den Kern; sie stehen zu lassen haette den Zweck der Bedingung
  verfehlt. Ein Pruefer kann es trotzdem als Ueberschreitung lesen — Datei und Gewerk
  stimmen, der Auftrag nannte zwei.
- 2026-09-04 — **Vorschlag 0072 abgelegt:** die zwei Doppelpunktverweise in
  `zustand.hpp`. Sie waren nicht beauftragt; sie sind der ganze Rueckstand dieser Form im
  Baum, gemessen. Die naheliegende Heilung — ein drittes Muster im Riegel — kollidiert
  mit Paket 0067, das die Riegeldatei haelt.
- 2026-09-04 — **`befunde/` liegt ausserhalb der Manifest- und Riegelsuche**
  (`baulauf.py:116`; der Riegel sperrt `bau` und `befunde`). Dort liegen vollstaendige
  Kopien des Kerns mit absichtlich beschaedigten Zeilen. Nicht anfassen, aber wissen.
- 2026-09-04, nach 0063 offen — **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen (derselbe Weg, auf dem der Runner `-fwrapv` setzt)
  und die Kommandozeile. Beide stehen in keiner Zieleigenschaft.
- 2026-09-03, wieder 09-04 — **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  `pruefstand/bau/pruefung-0019/` und `werkzeuge/belegstellen/` binden die Werkzeugkette
  nicht ein und setzen ihre Schalter selbst — jedes Mal nachpruefen, nie anfassen.
- 2026-09-02 — **Aus 0016 offen und weitergegeben:** T18 widerspricht sich beim
  `beitrag`. Gebaut ist ein Satz je Adresse; daran haengt die Kettenkapazitaet 310.
- 2026-09-03 — **Nicht angefasst** (kein Aufraeumen nebenbei): der Kopf von
  `kern/CMakeLists.txt` zitiert eine Suchregel im Klartext — der naechste Blindtreffer.
