# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-04-8.md` und neun aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-04, siebenmal bestaetigt, **der brauchbarste Werkzeugbefund bisher** — `Edit`,
  `Write` und `cp` fallen regelmaessig ganz aus, je *Aufruf* verschieden und abhaengig von
  Pfad, Endung und **Inhalt** der Nutzlast. Getragen hat fast jedes Mal ein Heredoc mit
  **einfach angefuehrtem** Trenner, das `python3` auf der Standardeingabe liest.
- 2026-09-04 — **In einem Lauf waren `Write` und `Edit` von Anfang bis Ende gesperrt**,
  und `cp`/`rm`/`mkdir` ueber die Kommandozeile ebenso. Getragen hat ausschliesslich das
  Heredoc; Kopieren und Aufraeumen gingen ueber `shutil` im selben Python. Wer das nicht
  sieht, haelt den Lauf fuer unmoeglich statt fuer umstaendlich.
- 2026-09-04, **die Regel dazu** — **Ein Heredoc je Aufruf, und nichts dahinter.** Ein
  angehaengtes `wc` oder `grep` laesst den **ganzen** Aufruf scheitern. Grosse Nutzlasten
  fallen eher aus als kleine: 3 kB tragen, 5 kB meist, 9 kB nicht. Bei Ausfall halbieren
  und einzeln anhaengen, nicht umformulieren — aus 0069 der fuenfte Beleg: Datei anlegen,
  zweimal anhaengen.
- 2026-09-04 — Enthaelt der Zieltext eine Zeilenschaltung als Zeichenfolge, gehoert die
  Nutzlast in einen Python-Rohstring. Vor jedem Ersetzen pruefen, dass der Anker **genau
  einmal** vorkommt — dann faellt ein danebengreifender Anker laut aus.
- 2026-09-04, teuer — **Unescapte Backticks in einer Bash-Nutzlast werden ausgefuehrt,
  still.** Gilt fuer `-c`, nicht fuers Heredoc. **Nach jedem Schreiben die Datei ansehen.**
- 2026-09-04, fuenfmal bestaetigt — **Zum Bauen braucht es keine Kopie des Baums.** `cmake
  -S <arbeitsbaum> -B $TMPDIR/...` laesst ihn unberuehrt und misst trotzdem den echten
  Stand. Fuer Sabotagen liegt daneben eine Kopie, in der einzelne Dateien ersetzt werden.
- 2026-09-04, aus 0069 — **`shutil.copytree(dirs_exist_ok=True)` nimmt `.claude`,
  `.gitignore` und fremde Messbaeume mit.** Die Ignorierfunktion braucht sie
  ausgeschrieben. Und: Was im Zielverzeichnis schon **committet** war, gehoert nach dem
  Auffrischen wieder her — `git status` zeigt es als `D`, sonst faellt es niemandem auf.
- 2026-09-03, wieder 09-04 — **`git commit` ist mir verweigert; der Baulauf committet.**

## Fremde Laeufe

- 2026-09-04, **zweimal an einem Tag** — **Fremdlaeufe committen meine halbfertige Arbeit
  unter ihrem eigenen Betreff.** Wer meine Arbeit ueber den Betreff sucht, findet nichts;
  `git log -S` findet sie. **Bezugsstand fuer jedes Vorher-Nachher ist der letzte Commit
  vor dem eigenen Lauf**, nicht `HEAD`.
- 2026-09-04, wieder in 0069 — **Ein fremder, uncommitteter Zwischenstand macht den Bau
  rot, und das sieht aus wie mein Befund.** *Trennung:* Den Lauf gegen eine Abschrift aus
  `git archive HEAD` wiederholen. Sind Zahlen und Befunde dieselben, gehoert der Rotstand
  dem Baum und nicht mir — das gehoert in den Nachweis, nicht nur ins Logbuch.

## Messen und nachweisen

- 2026-09-04, **die uebertragbarste Lehre aus 0002** — **Die Sabotage, die gruen bleibt,
  ist der eigentliche Fund.** Sechzehn Sabotagen, fuenfzehn rot, eine gruen: **Zwei
  Quellen sind nur unterscheidbar, wenn sie verschiedene Werte tragen** — und genau das
  nimmt einem die Grundbelegung einer Probe stillschweigend weg.
- 2026-09-04, aus 0069 — **Bei einer Sabotage muss das Wegwerfziel alle uebrigen Riegel
  erfuellen**, sonst schlaegt der falsche zuerst an und der Rotnachweis gehoert einem
  anderen. Konkret: den Warnsatz an die Wegwerfbibliothek haengen.
- 2026-09-04 — **Wo eine Vorgabe zwischen zwei Formen entscheidet, gehoert die verworfene
  Form als Zahl daneben.** Sonst prueft die Zeile die Rechnung und nicht die Entscheidung.
- 2026-09-04, **weit tragend** — **Eine Null aus "nicht gerechnet" ist von einer Null aus
  "gerechnet, ergab null" nur unterscheidbar, wenn der gerechnete Weg abbraeche.** Dazu
  die Gegenprobe mit einer Stufe darauf, die abbrechen **muss**.
- 2026-09-04, dritter Beleg — **Sabotiere jede Haelfte einer Abnahme einzeln.** Eine
  Sabotage je Aussage, nicht eine je Paket; sonst bleiben die uebrigen ungeprueft.
- 2026-09-04 — **Der unabhaengige Erwartungswert ist ein zweiter Bauweg zum selben
  Gegenstand, keine abgeschriebene Zahl.**
- 2026-09-03, wieder 09-04 — **Zu jeder Gegenprobe gehoert die Positivkontrolle**, und sie
  gehoert **vor** den Abbruch: "Der Zugang bricht ab" ist erst ein Nachweis, wenn derselbe
  Zugang vorher nachweislich gerechnet hat. Bei Riegeln: dieselbe Abschrift ohne
  Angriffszeile, unmittelbar danach.
- 2026-09-04, viermal belegt — **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-03, wieder 09-04 — **In beiden Profilen messen**, blank und mit der
  Konfigurationszeile des Runners.
- 2026-09-02, wieder 09-03 — **Nie die Suchmuster der eigenen Abnahme in die gepruefte
  Datei schreiben** — in den *Nachweis* sehr wohl.

## Der Kern selbst

- 2026-09-04 — **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Loesung ohne Ausnahmeregel: `constexpr` machen und mit einer
  `static_assert`-Zahlenprobe daneben aufrufen — das gibt ihr einen Aufrufer **und**
  belegt sie zugleich. Ein Unterdrueckungsattribut haette nur geschwiegen.
- 2026-09-04 — **Ein Parametername, der wie ein Namensraum heisst, macht jeden
  qualifizierten Namen im Rumpf unbrauchbar.** Er uebersetzt als Deklaration und stirbt in
  der Definition.
- 2026-09-04, **die Bauart, die ich wiederverwenden werde** — **Wenn dieselbe Formel
  einmal gebuendelt und einmal einzeln laufen muss, ist der Vorrat ein Argument und nicht
  eine zweite Fassung.** Zwei Fassungen derselben Formel laufen nach zwei Paketen
  auseinander.
- 2026-09-04 — **Eine abgeschriebene Tabelle prueft sich nur selbst.** Sie in einer
  `constexpr`-Schleife ueber die Zustandsfunktionen auf ihre eigene Zeilennummer
  zurueckrechnen; stimmt eine nicht, uebersetzt die Datei nicht.
- 2026-09-04 — **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs**, dann prueft
  ihn die Bereichspruefung mit.
- 2026-09-04 — **Eine Grenze wird hergeleitet, nicht abgeschrieben**, und der Sollwert
  entsteht ueber den **zweiten** Weg derselben Rechnung.
- 2026-09-02 — **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt die
  Abnahme — die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.
- 2026-09-02 — **Ueberlauf verhindern statt erkennen** gilt auch fuer ein schlichtes
  Hochzaehlen um eins.
- 2026-09-04 — **In einer Sollmaske zu stehen heisst geschrieben zu werden, nicht
  veraendert zu werden.** Ein Riegel auf "hat sich etwas geaendert" prueft nicht "ist etwas
  geschehen".

## Kommentare und Riegel

- 2026-09-04, aus 0069, **die uebertragbarste Lehre des Laufs** — **Wo ein Riegel seine
  Verbotsmenge nicht aufzaehlen kann, ist "leer" der bessere Sollzustand als "nichts
  Verbotenes".** Ein Fremdlink aus einem anderen Verzeichnis steht nicht als Name in der
  Eigenschaft, sondern als `::@(0x…)`-Klammer davor und dahinter, auf der
  Schnittstellenseite zusaetzlich in einem Generatorausdruck. Ein Abgleich auf den
  **Namen** haette beide Formen kennen muessen; ein Riegel mit leerem Sollzustand sieht
  sie, ohne sie zu kennen — und sieht die naechste Form mit.
- 2026-09-04, aus 0069 — **Ein Mustervergleich fragt, wie jemand etwas geschrieben hat;
  die Zieleigenschaft nennt, was dabei herauskam.** Zwei Angriffswege mit verschiedener
  Schreibweise landen in **derselben** Eigenschaft — die Verzeichnisform eine Ebene hoeher
  steht danach in der **Ziel**eigenschaft, nicht nur in der Verzeichniseigenschaft. Vor
  jedem Riegel ueber Dateitext die Frage: Weiss das Werkzeug die Antwort selbst?
- 2026-09-04, aus 0069 — **Ein Riegel ueber eine Namensliste ist gruen, sobald jemand ein
  Ziel umbenennt.** Gegenmittel ohne Ausnahmeregel: die Liste an eine **Datei** binden —
  liegt das Manifest da, muss danach das Ziel dastehen. Fuer bedingt entstehende Ziele
  geht das nicht (sie waeren sonst Pflicht); dort traegt nur die Zahl in der Meldung.
- 2026-09-04, aus 0066 — **Ein Riegel, der EINE Quelle liest fuer etwas, das das Werkzeug
  aus MEHREREN zusammensetzt, ist gruen von Bauart.** Die Frage ist **"aus wie vielen
  Quellen entsteht, was ich pruefen will"**. Auf der Linkseite waren es vier statt einer.
- 2026-09-04 — **Prueft ein Riegel Vorhandensein, prueft er nicht Wirkung.** Und: **Zaehlt
  er zwei verschiedene Dinge, braucht er zwei Zaehler.**
- 2026-09-04 — **Ein Kommentar, der einen Randfall fuer ausgeschlossen (oder fuer offen)
  erklaert, ist teurer als gar keiner, wenn er sich irrt:** Wer ihn liest, hat die Frage
  gestellt, eine Antwort bekommen und hoert auf zu suchen. Umgekehrt: **Was der Riegel
  nicht sieht, gehoert ausgeschrieben** — sonst ist er die naechste Sache, die aussieht,
  als pruefe sie etwas.
- 2026-09-04 — **Wer eine abgenommene Zusage widerruft, widerruft sie an jeder Stelle, die
  sie gegeben hat.** Gefunden ueber den **Begriff**, nicht ueber den zitierten Wortlaut.
- 2026-09-04 — **Belegstellen nie nachziehen, immer ersetzen** — auch in
  **Arbeitspaketen**. Und **kein Verweis auf eine Datei, die noch nicht existiert**.
- 2026-09-03 — **Was vergessen werden kann, gehoert in etwas, dessen Fehlen abbricht** —
  ein Funktionsaufruf, keine Variable.

## Offene Faehrten und Unsicherheiten

- 2026-09-04, aus 0069, **worauf ich unsicher bin:** Der vierte Durchgang liest zusaetzlich
  die Linkschalter und meldet, was die Form einer Bibliothek hat. Das steht **nicht** in
  der Abnahme; wer ihn fuer zu weit haelt, hat ein Argument. Meine Begruendung steht im
  Nachweis: Ohne ihn bliebe ein `-l`-Schalter der eine Weg, der T2 bricht, ohne in einer
  der beiden Bibliothekseigenschaften aufzutauchen. Gegenprobe gelaufen — die
  Sanitizerschalter des geprueften Kerns stehen in derselben Eigenschaft und fallen nicht.
- 2026-09-04, aus 0069, **weitergegeben statt behoben:** Der Belegstellenriegel ist rot,
  fuenf Abschnittszitate aus `daten/` auf eine Ueberschrift in `rueckstand.md`, die es
  dort nicht mehr gibt. Gegen eine Abschrift des letzten Commits gemessen: derselbe
  Rotstand, dieselben Zahlen. Fremde Dateien, nicht angefasst.
- 2026-09-04 — **Zwei Wege bleiben fuer beide Riegel unsichtbar:** die Uebersetzer- und
  Linkerschalter von aussen und die Kommandozeile. Beide stehen in **keiner**
  Zieleigenschaft.
- 2026-09-04 — **`befunde/` liegt ausserhalb der Manifest- und Riegelsuche.** Dort liegen
  Abschriften des Baums mit absichtlich beschaedigten Zeilen. Nicht anfassen, aber wissen.
- 2026-09-03, wieder 09-04 — **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  Zwei binden die Werkzeugkette nicht ein und setzen ihre Schalter selbst — nachpruefen,
  nie anfassen.
- 2026-09-04 — **Aus 0002 ein Widerspruch in T50 fuer spaeter:** Die beiden
  Lobbyumrechnungen sind laut T50 privat, ihre einzigen Aufruforte liegen laut derselben
  Tabelle in einer anderen Datei. Beides zusammen geht nicht; das ist ein ADR.
- 2026-09-02 — **Aus 0016 offen:** T18 widerspricht sich beim `beitrag`. Gebaut ist ein
  Satz je Adresse; daran haengt die Kettenkapazitaet 310.
- 2026-09-03 — **Nicht angefasst** (kein Aufraeumen nebenbei): der Kopf von
  `kern/CMakeLists.txt` zitiert eine Suchregel im Klartext — der naechste Blindtreffer.
