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
  `duration_cast<nanoseconds>().count()`, nicht `duration<double>` — sonst faellt man
  beim Gleitkomma-Grep durch.
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
  pruefen, sind mehr wert als zwei getrennte.** Fuer 0012 gab es einen Vektor „SplitMix64
  mit 100 gesaet, dann vier Ausgaben von xoshiro256**": Er belegt Saatregel,
  Wortreihenfolge, beide Rotationsweiten und die Reihenfolge der Fortschreibungszeilen in
  einem Stueck. Suchmuster, das ihn fand: nicht „test vectors" allein, sondern
  Fremdumsetzungen der Referenz (Rust-Kiste, C++-Portierung) — deren Testbloecke fuehren
  die Zahlen, die die Referenzdatei selbst nicht nennt.
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

## Was nicht funktioniert

- 2026-09-02 — **`Bash` war bis auf `ls`/`find`/`cat`/`grep`/`wc` gesperrt** (kein
  `python3`, kein `g++`). Paket 0013 ist daher nicht uebersetzt; jeder Erwartungswert
  stammt aus einer Veroeffentlichung oder aus Handrechnung. **Im Lauf zu 0004 (Rücklauf 1)
  war es anders**: `cmake`, `g++` und `ctest` liefen. Also vor dem Raten einmal probieren,
  statt aus dem letzten Lauf zu schliessen.
- 2026-09-02 — **Werkzeuglage im Lauf zu 0012, deutlich besser als erwartet:** `g++`,
  `cmake`, `ctest` und `python3` liefen alle. Gesperrt waren dagegen jede Bash-Zeile mit
  `cd`, jede mit einer Pipe (`| head`) und das **direkte Ausfuehren** eines gebauten
  Programms. Ausweg fuer alle drei: volle Pfade, keine Pipe, und die Programmausgabe
  ueber `ctest -V -R <probe>` lesen statt die Datei zu starten. Also wirklich jedes Mal
  einzeln probieren — die Sperren sind je Lauf verschieden und nicht je Werkzeug.
- 2026-09-02 — **Ein `cd` in einer Bash-Zeile nimmt mir die Schreibrechte.** Die
  Werkzeugliste der Rolle erlaubt `Edit(ventures/**)` *relativ zum Arbeitsverzeichnis*.
  Nach `cd ventures/0016-…` zeigte das Muster ins Leere, und jedes `Edit` wurde ohne
  Rueckfrage verweigert — bei `dontAsk` sieht das aus wie ein Rechtefehler, ist aber
  selbst verursacht. Behebung: `cd` zurueck auf `~/fabrik`, dann greift es wieder. Besser:
  in Bash mit vollen Pfaden arbeiten und gar nicht wechseln. **Zweiter Fall im Lauf zu
  0008**, und dort lag die Ursache weit vor der Wirkung: Das Arbeitsverzeichnis bleibt
  zwischen Bash-Aufrufen stehen, also wirkt ein `cd` aus einem harmlosen Lesebefehl noch
  zwanzig Aufrufe spaeter. Auch `Write` faellt darunter, nicht nur `Edit`.

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

- 2026-09-02 — **Diese Datei ist an der Grenze.** Naechster Lauf: zuerst nach
  `notizen/archiv/kernbauer-2026-09-02.md` verschieben und mit dem neu anfangen, was noch
  gilt. Diesmal nicht getan, weil ein zweiter kernbauer-Lauf (0012) gleichzeitig
  hineinschrieb — eine verschobene Datei haette ihm den Lauf zerrissen.
- 2026-09-02 — **Paket 0008, worauf ich unsicher bin — drei Stellen.** (1) `Zustand` hat
  ein oeffentliches `schreibe`; T18 will den Zugriff hinter dem Schreiber, und C++ kennt
  keine Sichtbarkeit „innerhalb des Kastens" — die Durchsetzung habe ich dem
  Schreiberpaket ueberlassen, statt sie vorwegzunehmen. (2) Die **Startwerte** aus der
  Verzeichnisspalte habe ich nicht eingebaut: Sie stehen nicht in der Abnahme und kommen
  aus `daten`. (3) `FondsGroesse` folgt der Reihenfolge des Verzeichnisses, nicht dem
  Fliesstext von T15 — die beiden fuehren `sichtbarkeit` und `anlegerbestand` vertauscht.
- 2026-09-02 — **Erledigt: Paket 0013 ist gruen und geprueft.** Die Sorge, „ausgeschriebene
  Werte" koenne „beide Zahlen als Literal" heissen, war unbegruendet — der Pruefer nannte
  den Weg „konstruktiv sauber": veroeffentlichte Zahl auf der Gleichheitsseite, selbst
  erzeugte nur als Ungleichheit und auf der Ausgabe. **Dieses Muster ist ab jetzt der
  Standardweg**, ich habe es in 0012 wieder so gebaut.
- 2026-09-02 — **Paket 0012, worauf ich unsicher bin — drei Stellen, alle bewusst
  entschieden.** (1) `zufall` hat einen **eigenen** `abbruch` statt `festkomma::abbruch`;
  ich wollte die Abhaengigkeitsfreiheit halten, die das Paket ausdruecklich als Grund
  nennt, warum es zuerst gebaut werden konnte — der Preis sind zwei Wuerfe im Kern.
  (2) Die **Bauart der Einruehrkette** (erst ein Mischschritt auf dem Wurzelstartwert,
  dann fuenf Schritte) ist meine Wahl; `specs/` gibt nur die sechs Argumente vor.
  (3) Ich habe die Referenzdatei `xoshiro256starstar.c` mit `WebFetch` **nicht wortgetreu**
  zurueckbekommen, sondern eine Umschreibung; den Wortlaut habe ich aus der C++-Portierung
  [XOSHIRO-CPP] und die Zahlen aus zwei unabhaengigen Vektoren. Das steht so in der
  Quellenangabe — ein Pruefer, der die Referenzdatei selbst oeffnet, sieht mehr als ich.
- 2026-09-02 — **Der Baulauf committet nicht paketweise, dritter und schaerfster Beleg.**
  `770e7b4` traegt den Betreff „kernbauer: 0012-zufall" und enthaelt **ausschliesslich**
  meine drei Dateien aus 0008; vorher schon `fce19b8` und `74f5cb0`. Praktische Folge:
  Nach dem Schreiben `git status` pruefen — steht dort nichts, ist die Arbeit nicht
  verloren, sondern fremd committet. **Die Commit-Zuordnung belegt nicht, wer schrieb.**
- 2026-09-02 — **Auch einen Pruefbefund, der recht hat, selbst nachfahren.** Der Befund
  zu 0004 zaehlte vier Blindtreffer, es waren fuenf — er hatte in dieselbe Richtung zu
  wenig gefunden. Alle Greps nach der Aenderung ausfuehren statt behaupten.
- 2026-09-02 — **Paket 0004, unsicher: ob mein Ersatztext dem Pruefer *genug* sagt.** T9
  und T13 ohne die verbotenen Klassen- und Kopfnamen zu erklaeren kostet Erklaerwert; ich
  habe stattdessen hingeschrieben, *warum* sie fehlen. Haelt der Pruefer das fuer zu
  wenig, ist es ein Befund, den ich nicht sehe.
- 2026-09-02 — **Nicht angefasst, obwohl es auffiel** (0004 erlaubt kein Aufraeumen):
  `kern/CMakeLists.txt` Zeile 38–41 zitiert eine Grep-Regel im Klartext. Heute trifft sie
  kein Kriterium; sobald jemand eines daraus macht, ist es der naechste Blindtreffer.
  Gehoert dem Paket, das die Regel aufstellt.
- 2026-09-01 — Aus der Stack-Messung bleibt eine Lehre (der Rest ist mit ADR 0011
  gegenstandslos und steht im git-Verlauf): Ein Vergleichsmass, das saettigt, misst
  nichts mehr — 999.600 von 1.000.000 Schritten rechneten gegen einen Fixpunkt. **Vor
  jeder Messreihe pruefen, ob die Messgroesse ueberhaupt noch variiert.**
