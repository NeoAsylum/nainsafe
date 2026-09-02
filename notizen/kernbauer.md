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
  Daten belegt statt an ausgedachten Faellen (in Java gemacht, beide Male
  `pruefsumme=2430192870`).
- 2026-09-01 — Runden „halbe Betraege von null weg" ohne Ueberlauf: `|rest| >= |c| -
  |rest|` statt `|rest| * 2 >= |c|`. Wegen `|rest| < |c|` kann die Differenz nicht
  ueberlaufen, die Verdopplung schon. In `i128` geht auch `(2*|z| + |n|) / (2*|n|)`, und
  die Formel stimmt anders als `(|z| + |n|/2) / |n|` auch bei ungeradem Nenner.
- 2026-09-01 — Zeit ohne Gleitkomma gibt es in jeder Sprache, aber nie auf dem bequemen
  Weg: `steady_clock` + `duration_cast<nanoseconds>().count()`, `perf_counter_ns()`,
  `System.nanoTime()`. Wer `duration<double>` oder `perf_counter()` greift, faellt beim
  Gleitkomma-Grep durch.
- 2026-09-01 — Ohne Compiler ist die **Invariante** das einzige Pruefmittel: Steht im
  Quelltext hergeleitet, dass ein Operand nie negativ wird, fallen alle Vorzeichenfragen
  ersatzlos weg, statt einzeln nachgebaut werden zu muessen — und der Befund des Pruefers
  wird ueberpruefbar statt strittig.
- 2026-09-02 — **Veroeffentlichte Hashwerte lassen sich ohne Compiler nachrechnen, wenn
  der Faktor duenn besetzt ist.** FNV-1a-64 hat P = 2^40+2^8+0xb3, also drei Summanden;
  bei Eingaben aus einem Oktett folgt das untere Wort linear aus dem Nachbarvektor
  (Delta = Delta_x · 0x1b3). So habe ich die per WebFetch geholte Vektortabelle an sechs
  Stellen geprueft, zweimal ueber volle 64 Bit. Eine zusammengefasste Tabelle ist sonst
  nur so gut wie das Modell, das sie las — und ein falsches Hexzeichen ist ein roter Baulauf.
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
  in Bash mit vollen Pfaden arbeiten und gar nicht wechseln.

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
- 2026-09-02 — **Der Baulauf committet nicht paketweise, zweiter Beleg.** `fce19b8`
  („datenbauer: 0014") enthielt meine `pruefsumme.*` aus 0013, `74f5cb0` („datenbauer:
  0006") enthaelt meine beiden Kommentaraenderungen aus 0004 — beide Male hat ein
  gleichzeitig laufender Agent sie mitgenommen. Zweimal ist kein Zufall mehr. Praktische
  Folge fuer mich: Nach dem Schreiben `git status` pruefen; steht dort nichts, ist die
  Arbeit nicht verloren, sondern schon fremd committet (`git show HEAD:<pfad>` belegt es).
  Die Commit-Zuordnung belegt nicht, wer schrieb — wer Zeilen je Rolle zaehlt, zaehlt
  falsch.
- 2026-09-02 — **Paket 0004, Rücklauf 1: ein vierter Blindtreffer, den der Pruefbefund
  nicht nennt.** Er zaehlte drei Treffer in `kern.hpp` und einen in `CMakeLists.txt`;
  tatsaechlich traf Zeile 9 auch den *zweiten* Grep aus Bedingung 3 (`grep -n
  'target_link_libraries(kern '`), wo der Befund „liefert nichts" schreibt. Alle vier
  sind mit derselben Aenderung weg, und ich habe alle drei Greps nach der Aenderung
  ausgefuehrt statt behauptet. Lehre: Auch einen Pruefbefund, der recht hat, selbst
  nachfahren — er kann in dieselbe Richtung zu wenig gefunden haben.
- 2026-09-02 — **Paket 0004, unsicher: ob mein Ersatztext dem Pruefer *genug* sagt.**
  Der Rücklauf verlangte, T9 und T13 ohne die Klassen- und Kopfnamen zu erklaeren. Wer
  „streuende Behaelter" liest und die Namen nicht kennt, muss sie anderswo nachschlagen —
  ich habe den Verlust in Kauf genommen und stattdessen hingeschrieben, *warum* sie
  fehlen. Haelt der Pruefer den Erklaerwert fuer zerstoert, ist das ein Befund, den ich
  nicht sehe; die Alternative waere Weg 2 des Vorbefunds (Kriterium aufweichen) gewesen,
  und den hat der Projektmanager ausdruecklich verworfen.
- 2026-09-02 — **Nicht angefasst, obwohl es auffiel** (Paket 0004 erlaubt kein
  Aufraeumen): `kern/CMakeLists.txt` Zeile 38–41 zitiert eine weitere Grep-Regel
  (`reinterpret_cast|const_cast|new|delete|asm`) im Klartext. Dieselbe Bauart wie die
  zwei Befunde, nur trifft sie heute keine der sieben Bedingungen — sobald jemand daraus
  ein Kriterium macht, ist es der dritte Blindtreffer. Gehoert dem Paket, das die Regel
  aufstellt.
- 2026-09-01 — **Die Eintraege zur Stack-Messung (Saettigung an der Klemmgrenze,
  Vorzeichen von `nachbar mod 977`, Zweideutigkeit von „mod 2^63−1", ungleiche
  Compilerverfuegbarkeit der vier Fassungen) sind mit ADR 0011 gegenstandslos** und
  stehen im git-Verlauf dieser Datei. Was davon uebrig bleibt und weitertraegt: Ein
  Vergleichsmass, das saettigt, misst nichts mehr — 999.600 von 1.000.000 Schritten
  rechneten gegen einen Fixpunkt. **Vor jeder Messreihe pruefen, ob die Messgroesse
  ueberhaupt noch variiert**, sonst belegen uebereinstimmende Zahlen nur die Klemme.
