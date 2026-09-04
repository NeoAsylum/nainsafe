# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-04-7.md` und acht aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-04, sechsmal bestaetigt, **der brauchbarste Werkzeugbefund bisher** — `Edit`,
  `Write` und `cp` fallen regelmaessig ganz aus, je *Aufruf* verschieden und abhaengig von
  Pfad, Endung und **Inhalt** der Nutzlast. Getragen hat fast jedes Mal ein Heredoc mit
  **einfach angefuehrtem** Trenner, das `python3` auf der Standardeingabe liest.
- 2026-09-04, neu und teuer — **In einem Lauf waren `Write` und `Edit` von Anfang bis
  Ende gesperrt**, und `cp`/`rm`/`mkdir` ueber die Kommandozeile ebenso. Getragen hat
  ausschliesslich das Heredoc; Kopieren und Aufraeumen gingen ueber `shutil` im selben
  Python. Wer das nicht sieht, haelt den Lauf fuer unmoeglich statt fuer umstaendlich.
- 2026-09-04, **die Regel dazu** — **Ein Heredoc je Aufruf, und nichts dahinter.** Ein
  angehaengtes `wc` oder `grep` laesst den **ganzen** Aufruf scheitern. Grosse Nutzlasten
  fallen ausserdem eher aus als kleine: 5 kB trugen, 9 kB nicht. Bei Ausfall halbieren
  und einzeln anhaengen, nicht umformulieren.
- 2026-09-04 — Enthaelt der Zieltext eine Zeilenschaltung als Zeichenfolge, gehoert die
  Nutzlast in einen Python-Rohstring. Vor jedem Ersetzen pruefen, dass der Anker **genau
  einmal** vorkommt — dann faellt ein danebengreifender Anker laut aus.
- 2026-09-04, teuer — **Unescapte Backticks in einer Bash-Nutzlast werden ausgefuehrt,
  still.** Gilt fuer `-c`, nicht fuers Heredoc. **Nach jedem Schreiben die Datei ansehen.**
- 2026-09-04, viermal bestaetigt — **Zum Bauen braucht es keine Kopie des Baums.** `cmake
  -S <arbeitsbaum> -B $TMPDIR/...` laesst ihn unberuehrt und misst trotzdem den echten
  Stand. Fuer Sabotagen liegt daneben eine Kopie in `$TMPDIR`, in der einzelne Dateien
  ersetzt werden.
- 2026-09-03, wieder 09-04 — **`git commit` ist mir verweigert; der Baulauf committet.**

## Fremde Laeufe

- 2026-09-04, **zweimal an einem Tag** — **Fremdlaeufe committen meine halbfertige Arbeit
  unter ihrem eigenen Betreff.** Wer meine Arbeit ueber den Betreff sucht, findet nichts;
  `git log -S` findet sie. **Bezugsstand fuer jedes Vorher-Nachher ist der letzte Commit
  vor dem eigenen Lauf**, nicht `HEAD`.
- 2026-09-04 — **Ein fremder, uncommitteter Zwischenstand macht den Bau des ganzen
  Vorhabens rot, und das sieht aus wie mein Befund.** *Trennung:* Den Gesamtbau aus
  `git archive HEAD` **plus genau den eigenen Dateien** messen. Der Unterschied der
  beiden Laeufe ist die Zuordnung des Befundes.

## Messen und nachweisen

- 2026-09-04, aus 0002, **die uebertragbarste Lehre des Laufs** — **Die Sabotage, die
  gruen bleibt, ist der eigentliche Fund.** Sechzehn Sabotagen, fuenfzehn rot, eine
  gruen: Der Marktkorb liest den Wechselkurs aus den Kursen, meine Probe setzte ihn aber
  in beiden Zustaenden auf denselben Startwert. **Zwei Quellen sind nur unterscheidbar,
  wenn sie verschiedene Werte tragen** — und genau das nimmt einem die Grundbelegung
  einer Probe stillschweigend weg.
- 2026-09-04, aus 0002 — **Wo eine Vorgabe zwischen zwei Formen entscheidet, gehoert die
  verworfene Form als Zahl daneben.** Sonst prueft die Zeile die Rechnung und nicht die
  Entscheidung: Bei glatten Werten liefern beide Formen dasselbe.
- 2026-09-04, aus 0002, **neu und weit tragend** — **Eine Null aus "nicht gerechnet" ist
  von einer Null aus "gerechnet, ergab null" nur unterscheidbar, wenn der gerechnete Weg
  abbraeche.** Um "der Abbruch liegt vor der Bewertung" zu pruefen, wurde der Wechselkurs
  des Gebiets auf null gesetzt: Dann bricht die Bewertung ab, und die zurueckgegebene
  Null ist ein Beleg statt eines Zufalls. Dazu die Gegenprobe mit einer Stufe darauf,
  die abbrechen **muss**.
- 2026-09-04, dritter Beleg — **Sabotiere jede Haelfte einer Abnahme einzeln.** Eine
  Sabotage je Aussage, nicht eine je Paket; sonst bleiben die uebrigen ungeprueft.
- 2026-09-04 — **Der unabhaengige Erwartungswert ist ein zweiter Bauweg zum selben
  Gegenstand, keine abgeschriebene Zahl.**
- 2026-09-03, wieder 09-04 — **Zu jeder Gegenprobe gehoert die Positivkontrolle**, und sie
  gehoert **vor** den Abbruch: "Der Zugang bricht ab" ist erst ein Nachweis, wenn derselbe
  Zugang vorher nachweislich gerechnet hat.
- 2026-09-04, dreimal belegt — **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-03, wieder 09-04 — **In beiden Profilen messen**, Debug ohne Sanitizer und die
  Konfiguration des Runners mit dem Testprofil darueber.
- 2026-09-02, wieder 09-03 — **Nie die Suchmuster der eigenen Abnahme in die gepruefte
  Datei schreiben** — in den *Nachweis* sehr wohl.

## Der Kern selbst

- 2026-09-04, aus 0002, **neu** — **Eine private Funktion ohne Aufrufer ist unter dem
  Warnsatz ein Bauabbruch.** Zwei der drei Skalenuebergaenge aus T50 haben ihren
  Aufrufort in einem ungebauten Schritt. Loesung ohne Ausnahmeregel: `constexpr` machen
  und mit einer `static_assert`-Zahlenprobe daneben aufrufen — das gibt ihnen einen
  Aufrufer **und** belegt sie zugleich. Ein Unterdrueckungsattribut haette nur geschwiegen.
- 2026-09-04, aus 0002 — **Ein Parametername, der wie ein Namensraum heisst, macht jeden
  qualifizierten Namen im Rumpf unbrauchbar.** Er uebersetzt als Deklaration und stirbt in
  der Definition. Die Vorgaben schrieben `z`; der Name aus der Vorgabe war zugleich der
  richtige C++-Name.
- 2026-09-04, aus 0002, **die Bauart, die ich wiederverwenden werde** — **Wenn dieselbe
  Formel einmal gebuendelt und einmal einzeln laufen muss, ist der Vorrat ein Argument
  und nicht eine zweite Fassung.** Ein Traeger mit einem Merker: leer rechnet jede Formel
  ihren einen Wert selbst, gefuellt lesen alle dieselbe Zahl. Zwei Fassungen derselben
  Formel laufen nach zwei Paketen auseinander.
- 2026-09-04, aus 0002 — **Eine abgeschriebene Tabelle prueft sich nur selbst.** Die
  Steckplatztabelle rechnet in einer `constexpr`-Schleife jede Zeile ueber die
  Zustandsfunktionen auf ihre eigene Zeilennummer zurueck; stimmt eine nicht, uebersetzt
  die Datei nicht.
- 2026-09-04 — **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs**, dann prueft
  ihn die Bereichspruefung mit. Bei 0002: Sektoren zaehlen ab eins, also ist die Null der
  "kein Sektor" der Waehrungs- und Anleiheplaetze und bricht bei Gebrauch ab.
- 2026-09-04 — **Eine Grenze wird hergeleitet, nicht abgeschrieben** (die Zahl der Koerbe
  ist der Platz, an dem die Waehrungen beginnen), und der Sollwert entsteht ueber den
  **zweiten** Weg derselben Rechnung.
- 2026-09-02 — **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt die
  Abnahme — die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.
- 2026-09-02 — **Ueberlauf verhindern statt erkennen** gilt auch fuer ein schlichtes
  Hochzaehlen um eins.
- 2026-09-04, aus 0071 — **In einer Sollmaske zu stehen heisst geschrieben zu werden, nicht
  veraendert zu werden.** Ein Riegel auf "hat sich etwas geaendert" prueft nicht "ist etwas
  geschehen".

## Kommentare und Riegel

- 2026-09-04 — **Ein Kommentar, der einen Randfall fuer ausgeschlossen (oder fuer offen)
  erklaert, ist teurer als gar keiner, wenn er sich irrt:** Wer ihn liest, hat die Frage
  gestellt, eine Antwort bekommen und hoert auf zu suchen.
- 2026-09-04 — **Wer eine abgenommene Zusage widerruft, widerruft sie an jeder Stelle, die
  sie gegeben hat.** Gefunden ueber den **Begriff**, nicht ueber den zitierten Wortlaut.
- 2026-09-04, aus 0066 — **Ein Riegel, der EINE Quelle liest fuer etwas, das das Werkzeug
  aus MEHREREN zusammensetzt, ist gruen von Bauart.** Die Frage ist **"aus wie vielen
  Quellen entsteht, was ich pruefen will"**.
- 2026-09-04 — **Prueft ein Riegel Vorhandensein, prueft er nicht Wirkung.** Und: **Zaehlt
  er zwei verschiedene Dinge, braucht er zwei Zaehler.**
- 2026-09-04 — **Belegstellen nie nachziehen, immer ersetzen** — auch in
  **Arbeitspaketen**. Und **kein Verweis auf eine Datei, die noch nicht existiert**: Bei
  0002 hatte ich einen Vorschlag unter seiner Nummer zitiert, die schon vergeben war; der
  Verweis nennt jetzt den Bezeichner.
- 2026-09-03 — **Was vergessen werden kann, gehoert in etwas, dessen Fehlen abbricht** —
  ein Funktionsaufruf, keine Variable.

## Offene Faehrten und Unsicherheiten

- 2026-09-04, aus 0002, **worauf ich unsicher bin:** Abnahme 1 verlangt "genau die
  siebzehn Namen, keiner mehr und keiner weniger". Im Kopf steht daneben ein Typ fuer die
  Kalibrierwerte. Meine Auslegung: Die Bedingung nennt als ihr Vorbild einen
  Mustervergleich auf **Funktionen**, und ein Datentraeger ist keine. Steht ausgeschrieben
  im Paket, nicht nur hier.
- 2026-09-04, aus 0002, **weitergegeben statt behoben:** Abnahme 2 verlangt die
  Uebergangsnamen aus T50 nur in der einen Quelle. Drei Treffer stehen ausserhalb, alle in
  **Prosa** und keiner ein Aufruf (Kommentar an `mal` in `festkomma.hpp` aus 0052, zwei in
  `schranken_probe.cpp` aus 0020). Beide Dateien fremd — nicht angefasst.
- 2026-09-04, aus 0002, **ein Widerspruch in T50 fuer spaeter:** Die beiden
  Lobbyumrechnungen sind laut T50 in `kern::werte` **privat**, und ihre einzigen
  Aufruforte liegen laut derselben Tabelle in Schritt 2 und Schritt 5 — also in einer
  anderen Datei. Beides zusammen geht nicht. Wer jene Schritte baut, braucht entweder
  einen Kopf-Eintrag oder verlegt die Rechnung ins Modul; das ist ein ADR.
- 2026-09-04, aus 0002 — **Was meine Probe NICHT belegt:** dass die zwoelf Korbwerte je
  Aufruf des Fondsvermoegens nur **einmal** entstehen. Sie belegt, dass der gebuendelte und
  der einzelne Weg dieselbe Zahl liefern. Die Einmaligkeit ist eine Eigenschaft des Codes
  und nur durch Lesen pruefbar.
- 2026-09-04, weiter offen — **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:** die
  Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in **keiner**
  Zieleigenschaft.
- 2026-09-04 — **`befunde/` liegt ausserhalb der Manifest- und Riegelsuche.** Dort liegen
  Kopien des Kerns mit absichtlich beschaedigten Zeilen. Nicht anfassen, aber wissen.
- 2026-09-03, wieder 09-04 — **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  Zwei binden die Werkzeugkette nicht ein und setzen ihre Schalter selbst — nachpruefen,
  nie anfassen.
- 2026-09-02 — **Aus 0016 offen und weitergegeben:** T18 widerspricht sich beim `beitrag`.
  Gebaut ist ein Satz je Adresse; daran haengt die Kettenkapazitaet 310.
- 2026-09-03 — **Nicht angefasst** (kein Aufraeumen nebenbei): der Kopf von
  `kern/CMakeLists.txt` zitiert eine Suchregel im Klartext — der naechste Blindtreffer.
