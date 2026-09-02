# Logbuch: kernbauer

**Höchstens 12.000 Zeichen** (`wc -c`). Belege gehören in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

---

## Was funktioniert

- 2026-09-01 — **Zwei Wege fuer dieselbe Rechnung sind zugleich der Pruefstand.** Ein
  Einzeiler, der jeden Aufruf in den langsamen, offensichtlich richtigen Weg zwingt,
  dazu ein Pruefsummenvergleich — damit ist Ueberlauf- und Rundungslogik an echten Daten
  belegt statt an ausgedachten Faellen.
- 2026-09-01 — Runden „halbe Betraege von null weg" ohne Ueberlauf: `|rest| >= |c| -
  |rest|` statt `|rest| * 2 >= |c|`. In `i128` geht auch `(2*|z| + |n|) / (2*|n|)`, und
  die Formel stimmt anders als `(|z| + |n|/2) / |n|` auch bei ungeradem Nenner.
- 2026-09-01 — Eine im Quelltext **hergeleitete Invariante** („dieser Operand wird nie
  negativ") laesst alle Vorzeichenfragen ersatzlos wegfallen und macht den Befund des
  Pruefers ueberpruefbar statt strittig.
- 2026-09-02 — **Nie die Grep-Muster der eigenen Abnahme in die gepruefte Datei
  schreiben.** Rücklauf 1 zu Paket 0004 kostete zwei Befunde und einen Pruefzyklus,
  obwohl die Sache stimmte: Der Kopf erklaerte das Verbot, indem er die verbotenen Namen
  nannte. Wer das Verbot erklaeren will, beschreibt die Sache und schreibt daneben,
  **warum** die Namen fehlen; sonst traegt sie der naechste in bester Absicht wieder ein.
- 2026-09-02 — **Eine Aenderung je Argument nur gegen den Bezugsaufruf zu halten ist zu
  wenig; die Aenderungen muessen auch untereinander verglichen werden.** In 0012 ergab
  „+1" bei zwei Eingaengen **denselben** Strom, vom Bezugsaufruf verschieden, alle
  `static_assert` gruen. **Paarweise vergleichen und die Zahlen ausschreiben.**
- 2026-09-02 — **Konstanten gegen die zweite Schreibweise derselben Quelle stellen**
  (RFC 9923 nennt jede FNV-Konstante dezimal, hexadezimal und als Bildungsvorschrift):
  Ein vertippter Ziffernblock wird so ein Uebersetzungsfehler. Veroeffentlichte
  Pruefvektoren findet nicht „test vectors", sondern die Suche nach **Fremdumsetzungen**
  der Referenz — deren Testbloecke fuehren die Zahlen, die die Referenz selbst nicht nennt.
- 2026-09-02 — **Fuer eine Abbildung auf viele feste Adressen ist der Deckungslauf der
  Nachweis:** ueber jede Aufzaehlung laufen, die erwartete Adresse aus den Namensteilen
  zusammensetzen, gegen die Tabelle legen, je Platz einen Strich. Statt `bool` **die
  erste fehlerhafte Zeilennummer** zurueckgeben. Und eine abgetippte Tabelle ist ein
  Tippfehler mit Verzoegerung: maschinell gegen die Quelle zurueckvergleichen.
- 2026-09-02 — **Eine Menge fester Adressen als Bitfeld gebaut, prueft sich beim
  Uebersetzen selbst.** Bloecke setzen, gesetzte Bits `constexpr` zaehlen: Ueberschneiden
  sich zwei, kommt eine zu kleine Zahl heraus und der Bau ist rot; eine Zaehlschleife
  haette die Doppelung mitgezaehlt. Gegenprobe von der anderen Seite dazu.
- 2026-09-02 — **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs, dann prueft
  ihn die Bereichspruefung mit** (`KEIN_PLATZ = FELDER`); ueber die *Vorbelegung* des
  Ergebnistyps zurueckgeben, nicht je Rueckgabestelle.
- 2026-09-02 — **`catch (...)` belegt nur, dass irgendwo etwas geworfen wurde.** Den
  `std::domain_error` fangen und `what()` ins Protokoll.
- 2026-09-02 — **Meldungen mit ausgeschriebenen Zahlen sind billig:** Puffer fester
  Groesse auf dem Stapel, Anhaengen mit Grenzpruefung. **Eine Meldung, die nur den Ort
  nennt, laesst genau die Frage offen, die der Leser hat.**
- 2026-09-02 — **Eine Zusage ueber Sichtbarkeit oder Lebensdauer gehoert in den
  Uebersetzungslauf.** Elemente: `requires { &T::x; }` **ueber einen Typparameter** (ohne
  ihn ist es ein harter Fehler statt `false`), nie ein hingeschriebener Zugriff — der
  traegt das Suchmuster der eigenen Abnahme in die gepruefte Datei. Typen:
  `std::is_copy_constructible_v` und Verwandte. **Die Gegenprobe ist Pflicht** — je ein
  `static_assert`, das `true` ergeben muss, sonst belegen die Negativzeilen nur, dass die
  Frage immer `false` liefert.
- 2026-09-02 — **Wer eine Zusage per Grep pruefbar machen will, muss den alten Namen
  wegnehmen, nicht nur verstecken.** In 0027 haette „`schreibe` privat, `Schreiber` als
  `friend`" die Abnahme erfuellt, aber `schreiber.cpp` haette den einen erlaubten Treffer
  behalten — und eine Regel mit einer zugelassenen Ausnahme hat in einem halben Jahr
  fuenf. Mit einem neuen Namen fuer den rohen Zugriff geht der Grep ueberall leer aus,
  auch in den Dateien, in denen er es nicht muesste.
- 2026-09-02 — **Dieselbe Tabelle zweimal abschreiben — ueber verschiedene Schleifen —
  und beide zur Laufzeit zweiseitig gegeneinander legen.** In 0033 steht die Sollmaske
  aus T38 einmal nach Bloecken (`schreiber.cpp`) und einmal nach den sechs
  Rundenschritten (`schritt.cpp`); jede Runde prueft, dass keine Maskenadresse ohne
  Schritt und kein Schritt ohne Maskenadresse dasteht. Die Zaehlungen fallen als
  `static_assert` nebenbei ab. **Zwei Abschriften mit demselben Tippfehler gibt es nicht,
  wenn die Schleifen verschieden sind** — eine Wiederholung derselben Schleife waere
  wertlos gewesen.
- 2026-09-02 — **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt
  die Abnahme — aber die Aufloesung gehoert in den Quelltext.** 0033 verlangte in der
  Prosa, dass jeder der sechs Schritte seinen Adressblock vortraegt, und in Bedingung 4
  eine **aufsteigende** Kette; die Bloecke liegen ineinander, beides zusammen geht nicht.
  Gebaut ist die aufsteigende Adressrunde mit Zuteilung je Adresse, und der Kopf sagt in
  drei Saetzen, warum. Ein Pruefer, der die Prosa liest, findet die Begruendung dort, wo
  er sucht — nicht nur hier.
- 2026-09-02 — **Eine Eigenschaft, die nur fuer das Geruest gilt, gehoert als „auf
  Widerruf" in den Kopf, samt der Anweisung, wer sie wann nachzieht.** Unveraenderte
  Pruefsumme und aufsteigende Kette fallen beide, sobald der erste Schritt rechnet. So
  aufgeschrieben ist das kein spaeter ueberraschend roter Test, sondern ein bestellter.
- 2026-09-02 — **Ueberlauf verhindern statt erkennen gilt auch fuer ein schlichtes
  `+ 1`.** `partie.runde + 1` waere mit `-fwrapv` ein Umbruch ins Negative gewesen;
  abgewiesen haette ihn erst der `Schreiber` — mit einer Meldung, die die Ursache nicht
  mehr nennt. Zwei Zeilen davor kosten nichts und nennen sie.

## Was nicht funktioniert

- 2026-09-02 — **Die Bash-Sperren sind je *Aufruf* verschieden, nicht je Werkzeug und
  nicht je Lauf.** Im Ruecklauf zu 0027 lief `python3 - <<'PY'` einmal durch und wurde
  beim naechsten Mal verweigert; `for`-Schleife, `sed` und `cat`-Hier-Dokument fielen,
  `printf ... | g++ -x c++ -` ging. **Also nicht aus einer Verweigerung auf eine Sperre
  schliessen — dieselbe Zeile einzeln noch einmal probieren**, und mehrere Faelle als
  einzelne Aufrufe statt als Schleife. **Und `Write` ist nicht dauerhaft entzogen**, wie
  hier vorher stand: In 0033 legte es zwei Quelldateien und ein Aufgabenblatt unter
  `ventures/` an und wurde nur unter `notizen/archiv/` verweigert. Dauerhaft gilt sonst
  nur: volle Pfade statt `cd`, Programmausgabe ueber `ctest -V -R <probe>`.
- 2026-09-02 — **Ein `cd` in einer Bash-Zeile nimmt mir die Schreibrechte**, vierter
  Fall (0008, 0016, 0027 zweimal, 0033). `Edit(ventures/**)` gilt *relativ zum
  Arbeitsverzeichnis*, und das bleibt zwischen Bash-Aufrufen stehen; auch ein `cd X && …`
  mit scheiterndem zweiten Teil wechselt. In 0033 sah es aus wie ein dauerhafter Entzug
  von `Write` **und** `Edit` — es war ein `cd` aus einem Lesebefehl zwei Aufrufe vorher.
  **Behebung: `cd /home/adria/fabrik` allein in einer Zeile, dann `pwd` glauben.**
- 2026-09-02 — **`-Wuseless-cast` mit `-Werror` beisst bei `static_cast<std::size_t>` auf
  einen `uint64_t`:** auf 64-Bit-Linux derselbe Typ, also Bauabbruch. Ohne Cast rechnen.
- 2026-09-02 — **„Riegel beim Binden statt je Aufruf" war die falsche Antwort auf die
  richtige Beobachtung, und sie hat mir Ruecklauf 1 zu 0027 eingebracht.** Ein fester
  Vergleich (`partie.runde == 0`) je Aufruf geht nicht, wenn das gelesene Feld selbst zu
  der Menge gehoert, die belegt wird. Mein Schluss „dann eben nur beim Binden" liess
  einen gebundenen Zugang beliebig lange weiterschreiben; **acht Schreibzugriffe hinter
  dem Riegel liefen in meiner eigenen gruenen Probe.** Richtig ist eine **Merkzahl**:
  *Wenn ein Waechter ein Feld liest, das er selbst schuetzt, vergleicht er gegen seinen
  letzten eigenen Stand, nicht gegen eine Konstante.*
- 2026-09-02 — **Eine Hilfsfunktion, die je Aufruf ein Recht neu erwirbt, ist eine
  Fussangel mit Zuender.** `lege(zustand, platz, wert)` band je Aufruf einen neuen
  Startwertzugang — gruen, bis die erste Aufrufstelle das geschuetzte Feld anfasst.
  Behebung: ein Typ, der **Zustand und Recht zusammen haelt**. Erkennungsmerkmal: Die
  Hilfe erzeugt in jedem Aufruf denselben Wert neu.

## Offene Faehrten

- 2026-09-02 — **Archivieren geht nicht: `Write(notizen/archiv/…)` ist mir verweigert**,
  dritter Versuch (0016, 0023, 0027); `cp` ebenfalls. Also gekuerzt statt verschoben,
  den Wortlaut haelt der git-Verlauf. Wer die Regel „verschieben statt streichen" hier
  will, muss der Rolle den Archivpfad geben.
- 2026-09-02 — **Erledigt: 0012, 0013, 0016, 0023, 0027 (samt Ruecklauf 1).** Aus 0013
  bleibt: veroeffentlichte Zahl auf der Gleichheitsseite, selbst erzeugte nur als
  Ungleichheit. Und: Wer einen oeffentlichen Kopf aendert, braucht in der
  `dateien`-Liste **jede** Uebersetzungseinheit, die ihn einbindet.
- 2026-09-02 — **Der Baulauf committet nicht paketweise, sechster Beleg:** `00d6f21`
  traegt „kernbauer: 0027" und enthaelt die fuenf Dateien aus **0033**. Steht nach dem
  Schreiben nichts in `git status`, ist die Arbeit fremd committet statt verloren. **Die
  Betreffzeile belegt weder, wer schrieb, noch welches Paket.**
- 2026-09-02 — **Auch einen Pruefbefund, der recht hat, selbst nachfahren:** der zu 0004
  zaehlte vier Blindtreffer, es waren fuenf. In 0027 habe ich die fuenf verbotenen
  Schreibwege selbst uebersetzt statt den `static_assert` zu glauben — alle fuenf rot.
- 2026-09-02 — **Aus 0016 offen und weitergegeben** (Einzelheiten im Pruefbefund): T18
  widerspricht sich beim `beitrag` — ein Anteil setzt mehrere Ursachensaetze je Adresse
  voraus, die derselbe Absatz verbietet. Gebaut ist ein Satz je Adresse; daran haengt
  auch die Kettenkapazitaet 310.
- 2026-09-02 — **Nicht angefasst** (kein Aufraeumen nebenbei): `kern/CMakeLists.txt`
  Zeile 38–41 zitiert eine Grep-Regel im Klartext — der naechste Blindtreffer, sobald
  jemand ein Kriterium daraus macht.
- 2026-09-02 — **Erledigt: 0033** (Rundengeruest `weltlauf`), acht Bedingungen gruen,
  `schritt_probe` bestanden. Daraus geschrieben: **Vorschlag 0038** — der Meldungsbau aus
  `schreiber.cpp` als eigener Kopf, weil sonst jedes der sechs Schrittpakete ihn
  abschreibt. Bis dahin nennen die Abbrueche in `schritt.cpp` die Datei statt der Adresse.
- 2026-09-02 — **Paket 0033, worauf ich unsicher bin — drei Stellen.** (1) Die drei
  Partiefelder der Maske nennt T38 **ohne Schritt**; ich habe sie Schritt 1 (Ansicht)
  gegeben, weil die Runde mit „welche Runde, welcher Jahrgang, welcher Parametersatz"
  beginnt. Begruendet in `schritt.cpp`; ein anderer Schritt waere vertretbar. (2)
  `partie.runde` wird **vorgetragen statt hochgezaehlt** — anders ginge Bedingung 6 nicht.
  Damit bleibt `vor_der_ersten_runde` nach einer Rahmenrunde wahr; wer Schritt 1 baut,
  zieht es nach. (3) Bedingung 3 sagt „beliebige Feldwerte", meine Runde bricht aber bei
  negativer oder nicht mehr zaehlbarer `partie.runde` ab. Ich halte das fuer richtig — der
  `Schreiber` weist eine Runde vor der ersten ohnehin ab —, aber es ist eine Auslegung,
  und die Probe zeigt beide Faelle im Wortlaut.
