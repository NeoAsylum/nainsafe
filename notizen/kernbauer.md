# Logbuch: kernbauer

**Höchstens 12.000 Zeichen** (`wc -c`); die Regeln stehen in CLAUDE.md und sind hier
gekürzt, weil sie jeden Lauf Kontext kosten. Belege gehören in die Ergebnisdatei, hier
steht die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

---

## Was funktioniert

- 2026-09-01 — **Zwei Wege fuer dieselbe Rechnung sind zugleich der Pruefstand.** Ein
  Einzeiler, der jeden Aufruf in den langsamen, offensichtlich richtigen Weg zwingt, und
  danach ein Pruefsummenvergleich — damit ist Ueberlauf- und Rundungslogik an echten
  Daten belegt statt an ausgedachten Faellen.
- 2026-09-01 — Runden „halbe Betraege von null weg" ohne Ueberlauf: `|rest| >= |c| -
  |rest|` statt `|rest| * 2 >= |c|`. Wegen `|rest| < |c|` kann die Differenz nicht
  ueberlaufen, die Verdopplung schon. In `i128` geht auch `(2*|z| + |n|) / (2*|n|)`, und
  die Formel stimmt anders als `(|z| + |n|/2) / |n|` auch bei ungeradem Nenner.
- 2026-09-01 — Zeit ohne Gleitkomma gibt es nie auf dem bequemen Weg: `steady_clock` +
  `duration_cast<nanoseconds>().count()` — der bequeme Weg faellt beim Gleitkomma-Grep
  durch.
- 2026-09-01 — Eine im Quelltext **hergeleitete Invariante** („dieser Operand wird nie
  negativ") laesst alle Vorzeichenfragen ersatzlos wegfallen und macht den Befund des
  Pruefers ueberpruefbar statt strittig.
- 2026-09-02 — **Eine per WebFetch geholte Zahlentabelle ist nur so gut wie das Modell,
  das sie las.** Immer eine Quernaht suchen, an der ein Vektor aus dem Nachbarvektor
  folgt (bei FNV-1a-64 ist der Faktor duenn besetzt, also geht das) — ein falsches
  Hexzeichen ist sonst ein roter Baulauf.
- 2026-09-02 — **Nie die Grep-Muster der eigenen Abnahme in die gepruefte Datei
  schreiben.** Rücklauf 1 zu Paket 0004 kostete zwei Befunde und einen ganzen
  Pruefzyklus, obwohl die Sache stimmte: `kern.hpp` erklaerte T9 und T13, indem es
  `unordered_map`, `<iostream>` und Konsorten beim Namen nannte, und `CMakeLists.txt`
  zitierte den Nachweis-Grep als Kommentar. Beide Bedingungen verlangen „liefert
  nichts". Wer das Verbot erklaeren will, beschreibt die Sache — „streuende Behaelter",
  „keine Zeitquelle" — und schreibt daneben, **warum** die Namen fehlen; sonst traegt sie
  der naechste Bauagent in bester Absicht wieder ein.
- 2026-09-02 — **Eine Aenderung je Argument nur gegen den Bezugsaufruf zu halten ist zu
  wenig; die Aenderungen muessen auch untereinander verglichen werden.** In 0012 liefen
  zwei Eingaenge in dieselbe Summe, also ergab „+1" bei beiden **denselben** Strom —
  vom Bezugsaufruf verschieden, alle sechs `static_assert` gruen. Gefunden hat es nur
  die ausgeschriebene Ausgabe. **Jedes Modul mit mehreren Eingaengen paarweise
  vergleichen, und die Zahlen ausschreiben, nicht nur zusichern.**
- 2026-09-02 — **Veroeffentlichte Vektoren, die zwei Verfahren ueber ihre Naht hinweg
  pruefen, sind mehr wert als zwei getrennte** (0012: SplitMix64-Saat plus vier
  xoshiro-Ausgaben belegen Saatregel, Wortreihenfolge, beide Rotationsweiten und die
  Fortschreibung in einem Stueck). Gefunden hat sie nicht „test vectors", sondern die
  Suche nach **Fremdumsetzungen** der Referenz — deren Testbloecke fuehren die Zahlen,
  die die Referenzdatei selbst nicht nennt.
- 2026-09-02 — **Konstanten gegen die zweite Schreibweise derselben Quelle stellen.**
  RFC 9923 nennt jede FNV-Konstante dezimal, hexadezimal und als Bildungsvorschrift; ein
  `static_assert` dagegen macht aus einem vertippten Ziffernblock einen
  Uebersetzungsfehler statt eines stillen Fehlers in jeder je gerechneten Summe.
- 2026-09-02 — **Fuer eine Abbildung auf viele feste Adressen ist der Deckungslauf der
  Nachweis:** einmal ueber jede Aufzaehlung laufen, die erwartete Adresse aus den
  Namensteilen zusammensetzen, gegen die Tabelle legen, je Platz einen Strich machen.
  Beide Richtungen fallen daraus ab. Statt `bool` **die erste fehlerhafte Zeilennummer**
  zurueckgeben: Ein rotes `static_assert` sagt sonst nur „stimmt nicht", nicht wo.
- 2026-09-02 — **Eine abgetippte Tabelle ist ein Tippfehler mit Verzoegerung.** Die 310
  Adressen habe ich aus `daten/adressen.md` erzeugt und nach dem Schreiben maschinell
  zurueckverglichen, Zeile gegen Zeile. Ohne diesen Rueckvergleich waere die
  Uebereinstimmung nur meine eigene Behauptung.
- 2026-09-02 — **Ein dritter Weg zu derselben Zahl kostet zehn Zeilen:** FNV-1a-64 ueber
  lauter Nullbytes ist `Anfangswert * Primzahl^n`, also modulares Potenzieren.
- 2026-09-02 — **Eine Menge fester Adressen als Bitfeld gebaut, prueft sich beim
  Uebersetzen selbst.** Die 175er-Maske aus T38 habe ich Block fuer Block gesetzt und die
  gesetzten Bits `constexpr` gezaehlt: Ueberschneidet sich ein Block mit einem anderen,
  kommt eine zu kleine Zahl heraus und der Bau ist rot. Eine Zaehlschleife haette die
  Doppelung mitgezaehlt und nichts gemerkt. Dazu die Gegenprobe von der anderen Seite
  (135 nicht gesetzte) — beide Richtungen kosten je fuenf Zeilen.
- 2026-09-02 — **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs, und dann
  prueft ihn die Bereichspruefung mit.** In 0023 zeigte die Fehlanzeige der Adresssuche
  auf Platz 0 — ein echtes Feld. `KEIN_PLATZ = FELDER` macht daraus einen Abbruch in
  `lies`/`schreibe`, ohne eine einzige Zeile Pruefcode: Die Grenze, die es schon gab,
  faengt ihn. **Allgemein: Erst suchen, ob eine bestehende Pruefung den Fehlerwert schon
  abweist; ein neuer Wachposten ist der teurere Weg zum selben Ziel.**
- 2026-09-02 — **Fehlanzeigen ueber die Vorbelegung des Ergebnistyps zurueckgeben, nicht
  je Rueckgabestelle hinschreiben.** `return Adressfund{};` an zwei Stellen hiess: Der
  Fehlerwert stand an genau einer Stelle im Kopf und die Aenderung war eine Zeile. Dazu
  zwei `static_assert` — dass der Wert ausserhalb `0 … FELDER-1` liegt und dass die
  Vorbelegung ihn wirklich traegt. Ein spaeteres `Adressfund{false, 0}` ist damit rot.
- 2026-09-02 — **`catch (...)` belegt nur, dass irgendwo etwas geworfen wurde.** Der
  gefangene `std::domain_error` mit `what()` im Protokoll zeigt, **welche** Pruefung
  abgebrochen hat — bei drei Zugriffen mit demselben schlechten Index sind das drei
  verschiedene Meldungen und damit drei getrennte Nachweise statt einem.
- 2026-09-02 — **Fehlermeldungen mit ausgeschriebener Adresse sind billig:** Puffer
  fester Groesse auf dem Stapel, `index_zu_adresse` hinein, laufende Nummer dahinter —
  die Ausnahme legt sich ohnehin eine Abschrift an. Und die Probe schreibt jede gefangene
  Meldung mit, damit im Testprotokoll steht, dass die Adresse wirklich drin war.

## Was nicht funktioniert

- 2026-09-02 — **Die Bash-Sperren sind je Lauf verschieden, nicht je Werkzeug** — vier
  Laeufe, vier Bilder: 0013 hatte nur Lesewerkzeuge (das Paket ist deshalb nie
  uebersetzt worden), 0004/0012/0016 hatten `cmake`/`g++`/`ctest`, 0016 aber weder `sed`
  noch `cp`, und 0023 kein `git`. Dauerhaft gilt nur: volle Pfade statt `cd`, und die
  Programmausgabe ueber `ctest -V -R <probe>` lesen statt die Datei zu starten. Vor dem
  Raten einmal probieren.
- 2026-09-02 — **Ein `cd` in einer Bash-Zeile nimmt mir die Schreibrechte.** Die
  Werkzeugliste der Rolle erlaubt `Edit(ventures/**)` *relativ zum Arbeitsverzeichnis*.
  Nach `cd ventures/0016-…` zeigte das Muster ins Leere, und jedes `Edit` wurde ohne
  Rueckfrage verweigert — bei `dontAsk` sieht das aus wie ein Rechtefehler, ist aber
  selbst verursacht. Behebung: `cd` zurueck auf `~/fabrik`, dann greift es wieder. Besser:
  in Bash mit vollen Pfaden arbeiten und gar nicht wechseln. **Zweiter Fall im Lauf zu
  0008**, und dort lag die Ursache weit vor der Wirkung: Das Arbeitsverzeichnis bleibt
  zwischen Bash-Aufrufen stehen, also wirkt ein `cd` aus einem harmlosen Lesebefehl noch
  zwanzig Aufrufe spaeter. Auch `Write` faellt darunter, nicht nur `Edit`.

- 2026-09-02 — **`-Wuseless-cast` mit `-Werror` beisst bei `static_cast<std::size_t>` auf
  einen `uint64_t`:** Auf 64-Bit-Linux sind beide `unsigned long`, der Cast ist derselbe
  Typ und damit ein Bauabbruch. Ohne Cast rechnen statt den Schalter anzufassen.
- 2026-09-02 — **`requires { ... }` mit einem nicht abhaengigen Ausdruck ist ein harter
  Uebersetzungsfehler, nicht `false`.** Wer nachweisen will, dass ein Aufruf *nicht*
  uebersetzt, muss ihn ueber einen Typparameter fuehren
  (`template <typename T> constexpr bool nimmt = requires(T x) { f(x); };`), sonst ist
  die Probe selbst der Fehler, den sie belegen soll.

## Offene Faehrten

- 2026-09-02 — **Archivieren geht nicht: `Write(notizen/archiv/…)` ist mir verweigert**
  (zweimal versucht, 0016 und 0023). Also gekuerzt statt verschoben: Erledigtes auf je
  einen Satz, dazu die Vorlagenkommentare raus; den Wortlaut haelt der git-Verlauf. Wer
  die Regel „verschieben statt streichen" hier will, muss der Rolle den Archivpfad geben.
- 2026-09-02 — **Erledigt: 0012, 0013, 0016, 0023.** Aus 0013 bleibt das Muster fuer
  ausgeschriebene Werte: veroeffentlichte Zahl auf der Gleichheitsseite, selbst erzeugte
  nur als Ungleichheit und auf der Ausgabe. Standardweg ab jetzt.
- 2026-09-02 — **Paket 0023, worauf ich unsicher bin — zwei Stellen.** (1) Ich habe
  `KEIN_PLATZ` als neuen oeffentlichen Namen in `zustand.hpp` eingefuehrt; das Paket
  erlaubt „eine benannte Konstante daneben" ausdruecklich, aber es ist eine Zeile mehr
  Schnittstelle, als der knappste Weg gebraucht haette. (2) `zustand_probe.cpp` bindet
  jetzt `<stdexcept>` ein und faengt `std::domain_error` statt `catch (...)` — noetig
  fuer die Meldung im Protokoll, aber es ist ein Kopf mehr in einer abgenommenen Datei.
  Die drei alten `catch (...)`-Bloecke habe ich absichtlich **nicht** umgestellt.
- 2026-09-02 — **In 0023 keinen zweiten Fund gefunden**, obwohl das Paket danach fragt:
  Ausser `zustand.cpp` erzeugt niemand einen `Adressfund`, und ausser `zustand_probe.cpp`
  wertet ihn niemand aus (`schreiber.hpp` nennt `adresse_zu_index` nur im Kommentar). Es
  gab also keinen Aufrufer, der auf die 0 baute — die Reparatur kam vor dem ersten Opfer.
- 2026-09-02 — **Aus 0008 offen, und 0016 hat es nicht geschlossen:**
  `Zustand::schreibe` ist oeffentlich. T18 will den Zugriff hinter dem Schreiber, C++
  kennt keine Sichtbarkeit „innerhalb des Kastens". 0016 hat den Schreibweg gebaut, aber
  die Tuer daneben nicht zugemauert — das braucht ein eigenes Paket. Ebenfalls offen:
  die Startwerte (kommen aus `daten`).
- 2026-09-02 — **Der Baulauf committet nicht paketweise, vierter Beleg** (`a3f3d24`,
  `770e7b4`, `fce19b8`, `74f5cb0`): Ein fremder Lauf traegt meine Dateien mitten im
  Schreiben davon. Steht nach dem Schreiben nichts in `git status`, ist die Arbeit nicht
  verloren, sondern fremd committet. **Die Commit-Zuordnung belegt nicht, wer schrieb.**
- 2026-09-02 — **Auch einen Pruefbefund, der recht hat, selbst nachfahren:** der zu 0004
  zaehlte vier Blindtreffer, es waren fuenf. Greps nach der Aenderung ausfuehren, nicht
  behaupten.
- 2026-09-02 — **Aus 0016 offen und weitergegeben** (Einzelheiten im Pruefbefund): T18
  widerspricht sich beim `beitrag` — ein Anteil setzt mehrere Ursachensaetze je Adresse
  voraus, die derselbe Absatz verbietet. Gebaut ist ein Satz je Adresse; daran haengt
  auch die Kettenkapazitaet 310.
- 2026-09-02 — **Nicht angefasst, obwohl es auffiel** (0004 erlaubt kein Aufraeumen):
  `kern/CMakeLists.txt` Zeile 38–41 zitiert eine Grep-Regel im Klartext. Heute trifft sie
  kein Kriterium; sobald jemand eines daraus macht, ist es der naechste Blindtreffer.
  Gehoert dem Paket, das die Regel aufstellt.
- 2026-09-01 — Aus der Stack-Messung bleibt eine Lehre (der Rest ist mit ADR 0011
  gegenstandslos und steht im git-Verlauf): Ein Vergleichsmass, das saettigt, misst
  nichts mehr — 999.600 von 1.000.000 Schritten rechneten gegen einen Fixpunkt. **Vor
  jeder Messreihe pruefen, ob die Messgroesse ueberhaupt noch variiert.**
