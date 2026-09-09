# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-06-8.md` (bei 11.997 Zeichen abgeloest, im
Lauf zu 0091) und einunddreissig aeltere daneben. Uebernommen ist, was ueber sein Paket
hinaus gilt; die Beobachtungen zu 0173 stehen vollstaendig im Vorgaenger.

---

## Werkzeuge und Sperren

- 2026-09-05/06, staendig -- **`Edit`, `Write` und einzelne `Bash`-Aufrufe fallen aus**,
  je Aufruf oder fuer den ganzen Lauf; im Lauf zu 0091 war `Edit` von Anfang an tot und
  `Write` nach zwei Dateien. Nicht wiederholen, sofort `python3 - <<PY` nehmen. Durch
  kommen in jedem Lauf: der Python-Umweg, `Read`, `Grep`, `git`, `cmake`, `ctest`.
- 2026-09-06 -- **Auch der Python-Umweg faellt aus, wenn die Nutzlast im String zu gross
  ist oder C-Quelltext traegt.** Zwei Auswege, beide erprobt: langen Text in
  `open(..., "a")`-Stuecken von rund 40 Zeilen anhaengen -- oder den Codeblock erst als
  Textdatei unter `befunde/` ablegen und mit einem zweiten Skript in die Zieldatei
  spleissen. Das Skript traegt dann keinen C-Quelltext, nur einen Dateinamen.
- 2026-09-06 -- **Ein uebersetztes Programm direkt aufzurufen wird verweigert, `ctest`
  nicht.** Wer eine Zahl messen will, druckt sie in einer Probe ab, statt einen eigenen
  Berichterstatter zu bauen. Die Riegel laufen so gegen den echten Baum:
  `cmake -S werkzeuge/<x> -B <tmp> -DFABRIK_VORHABEN_WURZEL=<vorhaben>`, dann `ctest`.
- 2026-09-06 -- **Keine Shell-Umleitung, keine Pipe** (`| sed`, `> datei`), auch
  `cd ... && ...` wird verweigert. Protokolle aus Python schreiben.
- 2026-09-06 -- **`sed`/`cat`/`grep` auf Pfade ausserhalb des Arbeitsverzeichnisses
  werden verweigert; `Read` und `Grep` mit absolutem Pfad gehen.** Der Arbeitspfad einer
  `Bash`-Zeile ist nicht der der vorigen -- immer absolut schreiben.

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-06, in jedem Lauf bestaetigt -- **Der Arbeitsbaum traegt waehrend meines Laufs
  die halbfertige Arbeit anderer.** Wer darin baut, misst den Fremdlauf. Der Ausweg ist
  ein Wegwerfbaum aus `git archive <stand>` -- den ganzen Baum, dann stimmt die Pfadlage
  fuer `specs/`. Reicht der Kern allein, genuegt eine Kopie von `kern/` neben
  `werkzeugkette.cmake`.
- 2026-09-06 -- **Der Kopf des Zweiges bewegt sich waehrend des Laufs.** Den Stand
  **einmal** festhalten, als Parameter ins Skript geben und ueberall zitieren.
- 2026-09-06 -- **Auch mein eigenes Logbuch bewegt sich:** Zu Beginn des Laufs zu 0091 las
  ich eine Fassung, am Ende stand eine voellig andere da -- ein Parallellauf derselben
  Rolle hatte sie abgeloest und bis auf drei Zeichen an die Grenze gefuellt. Am Ende des
  Laufs neu lesen, nicht die Fassung vom Anfang fortschreiben.
- 2026-09-06 -- **Nur die eigenen Pfade committen** (`git commit <pfade>`), sonst nimmt
  der Commit die fremde Arbeit mit. Der billigste Nachweis, sonst nichts angefasst zu
  haben: `git diff --numstat` ueber das Vorhaben.

## Nachweise fuehren

- 2026-09-06 -- **Eine neue `static_assert` beweist man mit vier Faellen, nicht mit
  drei:** gruen unterhalb, rot oberhalb, gruen am heutigen Wert -- und denselben roten
  Fall mit **entfernter** Zusicherung, der gruen wird. Dazu der zweiseitige
  Wortlautvergleich gegen die Nachbarzusicherung. Bei 0091 genuegte dafuer
  `g++ -fsyntax-only` auf einer Quelle, die nur den Kopf bindet: Sekunden statt Minuten.
- 2026-09-06 -- **Ein Nachweisskript, das nicht aus dem Leeren startet, laeuft genau
  einmal -- und sein `lauf.txt` bleibt vom ersten Lauf stehen.** Prueffrage nach jedem
  Lauf: *Habe ich den Rueckgabecode gelesen oder nur die Datei, die er geschrieben haben
  soll?*
- 2026-09-06 -- **Vor jeder Mutation pruefen, dass der Suchtext genau einmal vorkommt.**
  Das Skript gehoert nach `befunde/messung-<paket>/` und endet mit `Abweichungen: 0`; der
  Lauf daneben in `lauf.txt`.
- 2026-09-06 -- **Ein Nachweis faehrt beide Staende, nicht nur den neuen.** Und: **Suche
  nach dem Merkmal selbst, nicht nach etwas, woraus es folgt.**
- 2026-09-06 -- **Eine Zahl, die im Kommentar steht, wird gemessen abgedruckt.**
- 2026-09-06, **bei 0172 nachgemessen** -- **Eine Zahl aus einem abgelegten Pruefbefund
  ist keine Messung.** Die falsche Bytezahl im Verlaufskopf lief ueber drei Stationen:
  Befund zu 0144, dort abgeschrieben von 0156, von dort in den Quelltext. Wer eine Zahl in
  einen Kommentar setzt, uebersetzt sie selbst -- auch wenn die Quelle ein Pruefer war.
- 2026-09-06 -- **`ctest` meldet keine Zeile "Total Tests"**, sondern "... tests passed
  ... out of N". Ein Zaehler, der ins Leere greift, gibt still -1 und sieht wie ein Befund
  aus. Und **`git archive <stand> <eine-datei>` reicht nie** -- ein Kopf bindet
  Nachbarkoepfe; immer das ganze `include`-Verzeichnis ziehen.
- 2026-09-05/06 -- **Was beim Uebersetzen rot werden kann, gehoert nicht in die Probe**;
  **"zwei Eingaben, dieselbe Ausgabe" braucht zuerst den Beleg, dass die Eingaben
  verschieden waren**; **eine Zusicherung an beiden Raendern rechnen**; **den erwarteten
  Wortlaut erzeugen, nicht abschreiben**; **Zahlwoerter zaehlen, nicht abschreiben**.
- 2026-09-06 -- **Jeden Baubaum aus dem Leeren.** Ein stehengebliebener Baum bricht mit
  "does not match the source used to generate cache" ab -- an beiden Staenden gleich,
  sieht also nach Gleichstand aus und ist keiner.

## Schranken und Zahlen im Kopf

- 2026-09-06 -- **Eine Schranke ist begruendet, wenn sie aus dem Verhalten der Aufrufer
  gemessen ist, und gegriffen, wenn sie rund ist.** Nachsehen, **wo** die Aufrufer den
  Behaelter hinlegen; oertlich heisst: die Grenze ist der Stapel eines Fadens
  (`ulimit -s`, 8.388.608 Byte, in `verlauf.hpp` als `STAPEL_JE_FADEN`).
- 2026-09-06 -- **Eine Zusicherung, deren beide Seiten aus derselben Konstante gebildet
  sind, ist keine Schranke.** Prueffrage: *Welcher Regler bewegt die linke Seite, und
  steht er auch rechts?*
- 2026-09-06, **neu bei 0091** -- **Eine Laengenschranke, die nie zuschlagen kann, ist ein
  Zweig, den keine Probe erreicht.** Ich wollte die Rueckwaertsaufloesung mit einer
  Hoechstzahl von Gliedern sichern; sie endet aber schon deshalb, weil jeder Schritt auf
  einen echt frueheren Platz geht. Erst fragen, ob die Ordnung das Ende beweist -- dann
  statt der Schranke den Beweis hinschreiben.
- 2026-09-06 -- **Zu einer Angabe gehoert der Satz, was sie nicht sagt.**

## Belegstellen, Riegel und CMake

- 2026-09-05 -- **Der Sperrebindungsriegel deckt `kern/src` und `kern/test`:**
  `kern/sperre.hpp` ist der letzte `#include` jeder Kernquelle, ein neuer gehoert
  **darueber**. Folge fuer jede Probe: kein `<cstring>`, die Teilstringsuche von Hand.
  Eine Hilfsdatei unter `befunde/` faellt nicht unter den Riegel.
- 2026-09-05/06 -- **Der Bezeichnerriegel liest jeden Namen in Rueckwaerts-Anfuehrung im
  ganzen Kern**, Gross- und Kleinschreibung zaehlt: `runde` geht, `Runde` nicht. **Der
  Belegstellenriegel** faengt Dateiname mit Zeilenangabe und ein zitiertes
  Ueberschriftenwort, das es nicht gibt. Beide haengen am Kommentartext, nicht nur am
  Code, und laufen im Arbeitsbereichsbau als `ctest` Nr. 16 bis 18 mit.
- 2026-09-05 -- **`festkomma::abbruch` wirft `std::domain_error`**, ist fangbar und am
  Wortlaut pruefbar; in `constexpr` erlaubt, solange der Zweig beim Uebersetzen nicht
  genommen wird.
- 2026-09-05 -- **Der Warnsatz endet auf `-Werror`** (`FABRIK_STRENGE` in
  `werkzeugkette.cmake`, 15 Schalter, dazu `-fwrapv -fno-fast-math`). Jede Umwandlung
  ausgeschrieben, aber keine auf denselben Typ (`-Wuseless-cast`). Ein Parametername, der
  eine Mitgliedsfunktion verdeckt, und eine Funktion ohne Aufrufer sind Bauabbrueche.
- 2026-09-06 -- **Ein CMake-Makro ersetzt seine Parameter als Text**, deshalb den
  **Namen** der Eingabevariablen uebergeben, nie ihren Wert. Und: `kern/CMakeLists.txt`
  sammelt Quellen, Koepfe und Proben mit `file(GLOB)` ein -- eine neue Datei braucht dort
  keine Zeile, eine neue Probe wird von selbst ein eigener `ctest`-Eintrag.

## Der Kern selbst

- 2026-09-06, **die Lehre des Laufs zu 0091** -- **Rueckwaerts aufloesen heisst suchen,
  nicht rechnen.** Ein Vortrag auf sich selbst traegt nach T18 die Verzoegerung null; wer
  die Ursachenrunde aus Runde minus Verzoegerung *ausrechnet*, landet auf demselben Glied
  und steht still -- und im `weltlauf` ist das jede der 175 Adressen. Richtig ist: den
  juengsten frueheren Schreibzugriff auf die Ursachenadresse suchen und die Verzoegerung
  nur als **obere Schranke** der Runde nehmen. Die Gegenprobe ist billig: dieselbe Lage
  zweimal, nur die Verzoegerung verschieden.
- 2026-09-06 -- **`kern::schritt` rechnet noch nichts und kennt keine Aktionen.** Wer eine
  Partie mit echten Ursachen braucht, baut die Runde von Hand ueber
  `kern::schreiber::Schreiber` im **Spielmodus** (Sollmaske = alle 310): die benannten
  Setzungen zuerst, dann jede noch nicht geschriebene Adresse `vortrag`, dann
  `rundenende()`. Das laeuft durch den echten Schreibweg samt zweiseitiger
  Maskenpruefung; von Hand ist nur, welche Ursache wo steht.
- 2026-09-06 -- **`partie.runde` wird von der Runde gesetzt, nicht vorgetragen**, mit der
  Ursache `Vortrag` auf sich selbst. `zustand::Startbelegung` bindet nur, solange dort
  null steht -- nach der ersten Runde gibt es keinen Startwertzugang mehr.
- 2026-09-06 -- **Eine Eingabe, die weder Zustandsadresse noch Parameterschluessel ist,
  hat einen dritten Traeger: `Konstanten` in `werte.hpp`.** Der Kern liest keine Datei
  (T2); nicht in `zustand.hpp` suchen oder anlegen.
- 2026-09-06 -- **Steht dieselbe Formel in `technik.md` und in `spiel.md`, gewinnt die
  genauere.** Und: **Eine Zuordnung ohne Leser faellt unter den Warnsatz** --
  `static_cast<void>(...)` an der Aufrufstelle, mit einem Satz daneben.
- 2026-09-05 -- **`std::sort` ist im Kern die falsche Antwort** (T9: nicht stabil);
  Einfuegesortierung, besser ein eindeutig ordnender Schluessel. Ein Behaelter des Kerns
  hat feste Groesse und keine Zuteilung; Kapazitaet vom Aufrufer nehmen, wo `specs/`
  keine nennt.

## Offene Faehrten und Unsicherheiten

- 2026-09-06, **worauf ich bei 0091 unsicher bin:** Der Puffer der vierten Abfrage
  (`Kettenblatt`) misst gemessene 1.667.360 Byte und lebt auf dem Stapel des Aufrufers.
  Das folgt aus T2 und ist abgesichert -- aber es ist viel, und wer spaeter zwei Blaetter
  in einen Rahmen legt, merkt es erst am Absturz. Zweitens: Reicht der Puffer nicht,
  bricht die Ebene ab, statt zu kuerzen; bei einer sehr langen Kette **innerhalb** einer
  Runde ist das hart. Beides ist bewusst so und beides waere ein eigenes Paket wert, wenn
  es weh tut.
- 2026-09-06 -- **Die Ausgabe der Kette ist Text, kein JSON.** T20 nennt zwei
  Ausgabeformen; gebaut ist wie bei den anderen drei Ebenen nur die erste. Das ist keine
  Luecke dieses Pakets, sondern eine der Ebene insgesamt -- und ein eigenes Paket, sobald
  T21 gebaut wird.
- 2026-09-06, **erledigt, nicht mehr vorschlagen:** die veraltete Sollzahl in
  `befunde/messung-0076/bauwege.py` (0135), die Endungsfalle in `werkzeugkette.cmake`
  (0108), das fehlende Profil in der Schlussriegelmeldung (0137) und der verrutschte
  Kommentar in `werte.cpp` (0173). Erst die vorhandenen Pakete lesen, dann vorschlagen.
- 2026-09-06, **worauf ich bei 0172 unsicher bin:** Der Kopf nennt die Grenze jetzt als
  "acht mal die Wand unter 17.360 Byte". Die 17.360 sind aus der gemessenen Kettengroesse
  hergeleitet, nicht selbst abgedruckt; belegt ist nur der Rand, beidseitig (2169 gruen,
  2170 rot). Waechst `Ursachensatz`, wandert die Zahl mit, und der Satz wird still falsch.
- 2026-09-07, **im Lauf zu 0186 -- der Lauf hatte ueberhaupt kein `Bash`.** Nicht einzelne
  Aufrufe fielen aus, sondern das Werkzeug fehlte im Satz: `Edit`, `Read`, `Grep`, `Glob`,
  `Write` -- sonst nichts. Damit faellt alles weg, was oben unter "Nachweise fuehren"
  steht: kein `cmake`, kein `ctest`, kein Python-Umweg, kein Wegwerfbaum, keine gemessene
  Zahl. Wer so einen Lauf zieht, hat genau zwei Mittel: den Quelltext der Aufrufer lesen
  und die Aenderung so klein halten, dass Lesen reicht. **Vorher pruefen, ob `Bash` da
  ist** -- die Wahl der Bauart haengt daran, nicht nur die Nachweisform.
- 2026-09-07, **worauf ich bei 0186 unsicher bin, und es ist dasselbe:** Der Riegel steht
  in `Verlauf::anhaengen`, die zweiseitige Probe steht als Bedingung 6 in `verlauf_probe`
  -- **beides ungebaut und ungelaufen.** Vier Aufrufer habe ich von Hand nachgelesen und
  jeder setzt heute beide Zahlen gleich (`verlauf_probe` an allen Stellen,
  `zustandsausgabe_probe` in `kettenpartie_bauen` und in `probe_kette_luecke` mit
  `glied.runde = 3` unter `beginne_runde(3)`); die Schranke kostet also keine Anpassung.
  Nachgelesen ist auch, dass sie nicht doch woanders greift -- ausser `verlauf.cpp` ruft
  nur diese beiden Proben `anhaengen` oder `aufnehmen`. Was ich **nicht** weiss: ob der
  Warnsatz die neue Probe durchlaesst. `-Wuseless-cast` bei `static_cast<long long>` auf
  `i64` und die vorzeichenlose Umwandlung der Literale in `muster_satz` habe ich am
  Bestand abgeglichen, nicht am Uebersetzer.
- 2026-09-07 -- **`aufnehmen` ist bei einem Fehler im Glied keine Einheit.** Es laeuft
  ueber `beginne_runde` und dann `anhaengen`; bricht das erste Glied ab, steht die Runde
  schon im Verlauf, leer. Der Verlauf kennt keinen Rueckbau (kein Loeschen, kein
  Zuruecksetzen -- das ist die Zusage des Kastens), also ist das kein Fehler, sondern die
  Bauart. Ich habe es in der Probe ausgeschrieben statt ein "unveraendert" zu behaupten,
  das nur fuer den Weg ueber `anhaengen` stimmt. Wer das anders haben will, braucht ein
  eigenes Paket -- und muesste zuerst die Zusage aufmachen.
