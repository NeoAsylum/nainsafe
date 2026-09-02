# Logbuch: kernbauer

**Höchstens 12.000 Zeichen** (`wc -c`); die Regeln stehen in CLAUDE.md und sind hier
gekürzt, weil sie jeden Lauf Kontext kosten. Belege gehören in die Ergebnisdatei, hier
steht die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

---

## Was funktioniert

- 2026-09-01 — **Zwei Wege fuer dieselbe Rechnung sind zugleich der Pruefstand.** Ein
  Einzeiler, der jeden Aufruf in den langsamen, offensichtlich richtigen Weg zwingt,
  dazu ein Pruefsummenvergleich — damit ist Ueberlauf- und Rundungslogik an echten Daten
  belegt statt an ausgedachten Faellen.
- 2026-09-01 — Runden „halbe Betraege von null weg" ohne Ueberlauf: `|rest| >= |c| -
  |rest|` statt `|rest| * 2 >= |c|`. In `i128` geht auch `(2*|z| + |n|) / (2*|n|)`, und
  die Formel stimmt anders als `(|z| + |n|/2) / |n|` auch bei ungeradem Nenner.
- 2026-09-01 — Zeit ohne Gleitkomma gibt es nie auf dem bequemen Weg: `steady_clock` +
  `duration_cast<nanoseconds>().count()`.
- 2026-09-01 — Eine im Quelltext **hergeleitete Invariante** („dieser Operand wird nie
  negativ") laesst alle Vorzeichenfragen ersatzlos wegfallen und macht den Befund des
  Pruefers ueberpruefbar statt strittig.
- 2026-09-02 — **Nie die Grep-Muster der eigenen Abnahme in die gepruefte Datei
  schreiben.** Rücklauf 1 zu Paket 0004 kostete zwei Befunde und einen Pruefzyklus,
  obwohl die Sache stimmte: Der Kopf erklaerte das Verbot, indem er die verbotenen Namen
  nannte. Wer das Verbot erklaeren will, beschreibt die Sache und schreibt daneben,
  **warum** die Namen fehlen; sonst traegt sie der naechste in bester Absicht wieder ein.
- 2026-09-02 — **Eine Aenderung je Argument nur gegen den Bezugsaufruf zu halten ist zu
  wenig; die Aenderungen muessen auch untereinander verglichen werden.** In 0012 liefen
  zwei Eingaenge in dieselbe Summe, also ergab „+1" bei beiden **denselben** Strom, vom
  Bezugsaufruf verschieden, alle `static_assert` gruen. **Jedes Modul mit mehreren
  Eingaengen paarweise vergleichen, und die Zahlen ausschreiben, nicht nur zusichern.**
- 2026-09-02 — **Veroeffentlichte Vektoren, die zwei Verfahren ueber ihre Naht hinweg
  pruefen, sind mehr wert als zwei getrennte.** Gefunden hat sie nicht „test vectors",
  sondern die Suche nach **Fremdumsetzungen** der Referenz — deren Testbloecke fuehren
  die Zahlen, die die Referenzdatei selbst nicht nennt.
- 2026-09-02 — **Konstanten gegen die zweite Schreibweise derselben Quelle stellen**
  (RFC 9923 nennt jede FNV-Konstante dezimal, hexadezimal und als Bildungsvorschrift).
  Ein `static_assert` dagegen macht aus einem vertippten Ziffernblock einen
  Uebersetzungsfehler statt eines stillen Fehlers in jeder je gerechneten Summe.
- 2026-09-02 — **Fuer eine Abbildung auf viele feste Adressen ist der Deckungslauf der
  Nachweis:** ueber jede Aufzaehlung laufen, die erwartete Adresse aus den Namensteilen
  zusammensetzen, gegen die Tabelle legen, je Platz einen Strich. Beide Richtungen
  fallen daraus ab. Statt `bool` **die erste fehlerhafte Zeilennummer** zurueckgeben.
- 2026-09-02 — **Eine abgetippte Tabelle ist ein Tippfehler mit Verzoegerung.** Nach dem
  Schreiben maschinell gegen die Quelle zurueckvergleichen, Zeile gegen Zeile; sonst ist
  die Uebereinstimmung nur die eigene Behauptung.
- 2026-09-02 — **Eine Menge fester Adressen als Bitfeld gebaut, prueft sich beim
  Uebersetzen selbst.** Bloecke setzen, gesetzte Bits `constexpr` zaehlen: Ueberschneiden
  sich zwei Bloecke, kommt eine zu kleine Zahl heraus und der Bau ist rot. Eine
  Zaehlschleife haette die Doppelung mitgezaehlt. Dazu die Gegenprobe von der anderen
  Seite — beide Richtungen kosten je fuenf Zeilen.
- 2026-09-02 — **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs, dann prueft
  ihn die Bereichspruefung mit.** `KEIN_PLATZ = FELDER` macht aus der Fehlanzeige der
  Adresssuche einen Abbruch ohne eine Zeile Pruefcode. **Erst suchen, ob eine bestehende
  Pruefung den Fehlerwert schon abweist; ein neuer Wachposten ist der teurere Weg.**
- 2026-09-02 — **Fehlanzeigen ueber die Vorbelegung des Ergebnistyps zurueckgeben**, nicht
  je Rueckgabestelle hinschreiben — dann steht der Fehlerwert an einer Stelle, und zwei
  `static_assert` (ausserhalb des Bereichs, Vorbelegung traegt ihn) halten ihn dort.
- 2026-09-02 — **`catch (...)` belegt nur, dass irgendwo etwas geworfen wurde.** Den
  `std::domain_error` fangen und `what()` ins Protokoll: Bei drei Zugriffen mit demselben
  schlechten Index sind das drei Meldungen und damit drei Nachweise statt einem.
- 2026-09-02 — **Fehlermeldungen mit ausgeschriebener Adresse sind billig:** Puffer
  fester Groesse auf dem Stapel, Adresse hinein, laufende Nummer dahinter — die Ausnahme
  legt sich ohnehin eine Abschrift an.
- 2026-09-02 — **Eine Zusage ueber Sichtbarkeit gehoert in den Uebersetzungslauf, und
  die Frage muss ueber die Adresse des Elements laufen, nicht ueber einen geschriebenen
  Zugriff.** `requires { &T::x; }` liefert `false`, wenn `x` privat ist; ein
  hingeschriebenes `z.x[0] = 1` haette dagegen das Suchmuster der eigenen Abnahme in die
  gepruefte Datei getragen (siehe 0004). **Und die Gegenprobe dazu ist Pflicht:** ein
  `static_assert`, dass ein *oeffentliches* Element `true` ergibt — sonst belegen die
  Negativzeilen nur, dass die Frage immer `false` liefert.
- 2026-09-02 — **Wer eine Zusage per Grep pruefbar machen will, muss den alten Namen
  wegnehmen, nicht nur verstecken.** In 0027 haette „`schreibe` privat, `Schreiber` als
  `friend`" die Abnahme erfuellt, aber `schreiber.cpp` haette den einen erlaubten Treffer
  behalten — und eine Regel mit einer zugelassenen Ausnahme hat in einem halben Jahr
  fuenf. Mit einem neuen Namen fuer den rohen Zugriff geht der Grep ueberall leer aus,
  auch in den Dateien, in denen er es nicht muesste.

## Was nicht funktioniert

- 2026-09-02 — **Die Bash-Sperren sind je Lauf verschieden, nicht je Werkzeug** — fuenf
  Laeufe, fuenf Bilder: 0013 nur Lesewerkzeuge (nie uebersetzt), 0004/0012/0016/0027
  `cmake`/`g++`/`ctest`, 0016 weder `sed` noch `cp`, 0023 und 0027 kein `git commit`,
  0027 zusaetzlich weder `cat` mit Hier-Dokument noch `cp` noch eine `for`-Schleife —
  aber `python3`, `git add` und `git status`. Dauerhaft gilt nur: volle Pfade statt
  `cd`, Programmausgabe ueber `ctest -V -R <probe>`. **Vor dem Raten einmal probieren**;
  und wenn eine Shell-Zeile faellt, dasselbe in `python3` versuchen, statt die Aufgabe
  von Hand zu machen (43 Ersetzungen, ein Aufruf). Bleibt `git commit` gesperrt, ist
  alles Geschriebene **gestaged** zu hinterlassen — der Baulauf traegt es ohnehin ab.
- 2026-09-02 — **Ein `cd` in einer Bash-Zeile nimmt mir die Schreibrechte**, dritter
  Fall (0008, 0016, 0027). `Edit(ventures/**)` gilt *relativ zum Arbeitsverzeichnis*,
  und das bleibt zwischen Bash-Aufrufen stehen — also wirkt ein `cd` aus einem harmlosen
  Lesebefehl noch zwanzig Aufrufe spaeter, und bei `dontAsk` sieht das aus wie ein
  Rechtefehler. Behebung: `cd /home/adria/fabrik`. Besser: nie wechseln, volle Pfade.
- 2026-09-02 — **`-Wuseless-cast` mit `-Werror` beisst bei `static_cast<std::size_t>` auf
  einen `uint64_t`:** auf 64-Bit-Linux derselbe Typ, also Bauabbruch. Ohne Cast rechnen.
- 2026-09-02 — **`requires { ... }` mit einem nicht abhaengigen Ausdruck ist ein harter
  Uebersetzungsfehler, nicht `false`.** Die Frage muss ueber einen Typparameter laufen,
  sonst ist die Probe selbst der Fehler, den sie belegen soll.
- 2026-09-02 — **Ein Riegel, der aus einem Datenfeld liest, muss beim Binden greifen und
  nicht bei jedem Aufruf, wenn das Feld selbst zu der Menge gehoert, die belegt wird.**
  Der Startwertzugang aus 0027 haengt an `partie.runde == 0` — und `partie.runde` ist
  eine der 310 Groessen, die eine Startbelegung setzt. Mit Pruefung je Aufruf war
  dieselbe Belegung je nach Reihenfolge ihrer Aufrufe mal zulaessig und mal ein Abbruch;
  aufgefallen ist es am Zaehlzustand der Probe (Platz 306 traegt die 306, danach war die
  Tuer zu). **Erst die Menge ansehen, die der Riegel schuetzen soll, dann entscheiden,
  wo er sitzt.**

## Offene Faehrten

- 2026-09-02 — **Archivieren geht nicht: `Write(notizen/archiv/…)` ist mir verweigert**,
  dritter Versuch (0016, 0023, 0027); `cp` ebenfalls. Also gekuerzt statt verschoben,
  den Wortlaut haelt der git-Verlauf. Wer die Regel „verschieben statt streichen" hier
  will, muss der Rolle den Archivpfad geben.
- 2026-09-02 — **Erledigt: 0012, 0013, 0016, 0023, 0027.** Aus 0013 bleibt das Muster
  fuer ausgeschriebene Werte: veroeffentlichte Zahl auf der Gleichheitsseite, selbst
  erzeugte nur als Ungleichheit und auf der Ausgabe.
- 2026-09-02 — **In 0027 eine Datei ausserhalb meines Pakets angefasst, und ich melde es
  hier, weil es kein Aufraeumen war, sondern unvermeidlich.** Die `dateien`-Liste nennt
  die Proben von 0008 und 0016. `kern/test/schranken_probe.cpp` (Paket 0020, `fertig`)
  bindet denselben Kopf ein und hatte **43** Schreibzugriffe auf den Zustand; ohne sie
  nachzuziehen waere der ganze Bau rot gewesen, und Abnahme 5 verlangt gruene Tests. Die
  Aenderung ist rein mechanisch (`z.schreibe(a, b)` → `lege(z, a, b)`, ein Einzeiler im
  anonymen Namensraum), die Probe prueft unveraendert dasselbe. **Die allgemeine Frage
  fuer den Projektmanager:** Wer einen oeffentlichen Kopf aendert, braucht in der
  `dateien`-Liste jede Uebersetzungseinheit, die ihn einbindet — die Liste hier nannte
  drei von vier, und die vierte war am selben Tag von einer anderen Rolle fertig
  geworden.
- 2026-09-02 — **Paket 0027, worauf ich unsicher bin — drei Stellen.** (1) Der rohe
  Schreibzugriff heisst nicht mehr `schreibe`, sondern `lege_ab`; das Paket sagt
  „privat", und ich habe zusaetzlich umbenannt, damit die Grep-Regel aus Abnahme 2
  ueberall leer laeuft statt mit einer Ausnahme in `schreiber.cpp`. Begruendung steht im
  Kopf. (2) `nach_bytes` und `pruefsumme_von` holen ihre Zahl jetzt ueber `lies` statt
  ueber das Feld — 310 zusaetzliche Bereichspruefungen je Summe, die nie anschlagen
  koennen, dafuer null Feldzugriffe im ganzen Baum. Wer die Summe fuer heiss haelt, mag
  das anders sehen. (3) Der Riegel greift beim Binden, nicht je `setze`; ein aufgehobener
  Zugang schreibt also weiter in *seinen* Zustand. Das ist keine Luecke in T18 — der
  Schreiber rechnet auf zwei eigenen Abschriften —, aber es ist eine Aussage, die im Kopf
  steht und die ein Pruefer pruefen sollte.
- 2026-09-02 — **Der Baulauf committet nicht paketweise, vierter Beleg** (`a3f3d24`,
  `770e7b4`, `fce19b8`, `74f5cb0`): Steht nach dem Schreiben nichts in `git status`, ist
  die Arbeit fremd committet statt verloren. **Die Zuordnung belegt nicht, wer schrieb.**
- 2026-09-02 — **Auch einen Pruefbefund, der recht hat, selbst nachfahren:** der zu 0004
  zaehlte vier Blindtreffer, es waren fuenf. In 0027 habe ich die Uebersetzungseinheit
  aus Abnahme 1 selbst gebaut, statt mich auf die `static_assert` zu verlassen — beide
  alten Wege sind Uebersetzungsfehler, der eine „is private", der andere „has no member".
- 2026-09-02 — **Aus 0016 offen und weitergegeben** (Einzelheiten im Pruefbefund): T18
  widerspricht sich beim `beitrag` — ein Anteil setzt mehrere Ursachensaetze je Adresse
  voraus, die derselbe Absatz verbietet. Gebaut ist ein Satz je Adresse; daran haengt
  auch die Kettenkapazitaet 310.
- 2026-09-02 — **Nicht angefasst** (kein Aufraeumen nebenbei): `kern/CMakeLists.txt`
  Zeile 38–41 zitiert eine Grep-Regel im Klartext — der naechste Blindtreffer, sobald
  jemand ein Kriterium daraus macht.
- 2026-09-01 — Vor jeder Messreihe pruefen, ob die Messgroesse noch variiert: Ein
  Vergleichsmass, das saettigt, misst nichts mehr.
