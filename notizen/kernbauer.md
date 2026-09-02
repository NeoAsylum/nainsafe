# Logbuch: kernbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/kernbauer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

*(Die Stack-Messung ist abgeschlossen und ADR 0011 entschieden; ihre vier Fassungen
brauche ich nicht mehr im Kopf. Die Einzeleintraege dazu stehen im git-Verlauf dieser
Datei, ihr Ertrag in vier Saetzen:)*

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
  das sie las.** Bei FNV-1a-64 ist der Faktor duenn besetzt (P = 2^40+2^8+0xb3), also
  folgt bei Eingaben aus einem Oktett das untere Wort linear aus dem Nachbarvektor —
  damit habe ich sechs Stellen von Hand geprueft. Immer eine solche Quernaht suchen; ein
  falsches Hexzeichen ist sonst ein roter Baulauf.
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
  Wurzelstartwert und Jahrgang in dieselbe Summe, also ergaben „Wurzel + 1" und
  „Jahrgang + 1" **denselben** Strom — beide vom Bezugsaufruf verschieden, alle sechs
  `static_assert` gruen. Gefunden hat es nur die ausgeschriebene Ausgabe der laufenden
  Probe, an zwei gleich aussehenden Zeilen. **Lehre fuer jedes Modul mit mehreren
  Eingaengen: paarweise vergleichen, und die Zahlen ausschreiben, nicht nur zusichern.**
- 2026-09-02 — **Veroeffentlichte Vektoren, die zwei Verfahren ueber ihre Naht hinweg
  pruefen, sind mehr wert als zwei getrennte** (0012: „SplitMix64 mit 100 gesaet, dann
  vier Ausgaben von xoshiro256**" belegt Saatregel, Wortreihenfolge, beide
  Rotationsweiten und die Reihenfolge der Fortschreibung in einem Stueck). Gefunden hat
  sie nicht „test vectors", sondern die Suche nach Fremdumsetzungen der Referenz — deren
  Testbloecke fuehren die Zahlen, die die Referenzdatei selbst nicht nennt.
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
- 2026-09-02 — **Fehlermeldungen mit ausgeschriebener Adresse sind billig:** Puffer
  fester Groesse auf dem Stapel, `index_zu_adresse` hinein, laufende Nummer dahinter —
  die Ausnahme legt sich ohnehin eine Abschrift an. Und die Probe schreibt jede gefangene
  Meldung mit, damit im Testprotokoll steht, dass die Adresse wirklich drin war.

## Was nicht funktioniert

- 2026-09-02 — **Die Bash-Sperren sind je Lauf verschieden, nicht je Werkzeug** — vier
  Laeufe, vier Bilder: 0013 hatte nur `ls`/`find`/`cat`/`grep`/`wc` (das Paket ist
  deshalb nie uebersetzt worden), 0004 und 0012 hatten `cmake`/`g++`/`ctest`/`python3`,
  0016 hatte die Bauwerkzeuge, aber weder `sed` noch `cp` noch `Write` ausserhalb der
  eigenen Dateien. Dauerhaft gilt nur: volle Pfade statt `cd`, keine Pipe, und die
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
  Typ und damit ein Bauabbruch. Ohne Cast rechnen (`if ((x & 1) != 0) { ++n; }`) statt den
  Schalter anzufassen.
- 2026-09-02 — **`requires { ... }` mit einem nicht abhaengigen Ausdruck ist ein harter
  Uebersetzungsfehler, nicht `false`.** Wer nachweisen will, dass ein Aufruf *nicht*
  uebersetzt, muss ihn ueber einen Typparameter fuehren
  (`template <typename T> constexpr bool nimmt = requires(T x) { f(x); };`), sonst ist
  die Probe selbst der Fehler, den sie belegen soll.

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

- 2026-09-02 — **Archivieren geht nicht: `Write(notizen/archiv/…)` ist mir verweigert.**
  Im Lauf zu 0016 versucht, abgelehnt — meine Werkzeugliste erlaubt nur diese eine Datei.
  Also gekuerzt statt verschoben: Erledigtes auf je einen Satz, den Wortlaut haelt der
  git-Verlauf. Wer die Regel „verschieben statt streichen" hier will, muss der Rolle den
  Archivpfad geben.
- 2026-09-02 — **Erledigt: 0012 und 0013 sind gruen und geprueft** (Einzelheiten im
  git-Verlauf). Aus 0013 bleibt das Muster fuer ausgeschriebene Werte, das der Pruefer
  „konstruktiv sauber" nannte: veroeffentlichte Zahl auf der Gleichheitsseite, selbst
  erzeugte nur als Ungleichheit und auf der Ausgabe. Standardweg ab jetzt.
- 2026-09-02 — **Aus 0008 offen, und 0016 hat es nicht geschlossen:**
  `Zustand::schreibe` ist oeffentlich. T18 will den Zugriff hinter dem Schreiber, C++
  kennt keine Sichtbarkeit „innerhalb des Kastens". 0016 hat den Schreibweg gebaut, aber
  die Tuer daneben nicht zugemauert — das braucht eine Aenderung an `zustand.hpp` und
  damit ein eigenes Paket. Ebenfalls offen: die Startwerte (kommen aus `daten`) und dass
  `FondsGroesse` dem Verzeichnis folgt statt dem Fliesstext von T15.
- 2026-09-02 — **Der Baulauf committet nicht paketweise, vierter Beleg.** `a3f3d24`
  („testentwickler: 0019") trug meine `schreiber.hpp` und `schreiber.cpp` aus 0016
  mitten im Lauf davon; vorher `770e7b4`, `fce19b8`, `74f5cb0`. Praktische Folge: Nach
  dem Schreiben `git status` pruefen — steht dort nichts, ist die Arbeit nicht verloren,
  sondern fremd committet. **Die Commit-Zuordnung belegt nicht, wer schrieb.**
- 2026-09-02 — **Auch einen Pruefbefund, der recht hat, selbst nachfahren:** der zu 0004
  zaehlte vier Blindtreffer, es waren fuenf. Greps nach der Aenderung ausfuehren, nicht
  behaupten.
- 2026-09-02 — **Paket 0016, worauf ich unsicher bin — drei Stellen.** (1) `Aktion{nr}`:
  Ich lese `nr` als die Aktionsart 1 bis 5 (`spiel.md`, *Die Aktionen*). Meint T18
  stattdessen die laufende Nummer einer Aktion in der Runde, ist meine Pruefung auf 1..5
  zu eng. (2) **T18 widerspricht sich, und ich habe es stehen lassen:** `beitrag` ist der
  *Anteil* einer Ursache an der Aenderung — mehrere Anteile setzen mehrere Ursachensaetze
  je Adresse voraus, und genau die verbietet derselbe Absatz („genau einmal geschrieben").
  Gebaut ist die Fassung mit einem Satz je Adresse; `beitrag` ist damit praktisch immer
  1.000. (3) Die Kettenkapazitaet 310 faellt aus (2): Loest jemand den Widerspruch
  zugunsten mehrerer Ursachen je Adresse, ist sie zu klein.
- 2026-09-02 — **Nicht angefasst, obwohl es auffiel** (0004 erlaubt kein Aufraeumen):
  `kern/CMakeLists.txt` Zeile 38–41 zitiert eine Grep-Regel im Klartext. Heute trifft sie
  kein Kriterium; sobald jemand eines daraus macht, ist es der naechste Blindtreffer.
  Gehoert dem Paket, das die Regel aufstellt.
- 2026-09-01 — Aus der Stack-Messung bleibt eine Lehre (der Rest ist mit ADR 0011
  gegenstandslos und steht im git-Verlauf): Ein Vergleichsmass, das saettigt, misst
  nichts mehr — 999.600 von 1.000.000 Schritten rechneten gegen einen Fixpunkt. **Vor
  jeder Messreihe pruefen, ob die Messgroesse ueberhaupt noch variiert.**
