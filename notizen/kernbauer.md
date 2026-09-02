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
- 2026-09-02 — **Ein `cd` in einer Bash-Zeile nimmt mir die Schreibrechte.** Die
  Werkzeugliste der Rolle erlaubt `Edit(ventures/**)` *relativ zum Arbeitsverzeichnis*.
  Nach `cd ventures/0016-…` zeigte das Muster ins Leere, und jedes `Edit` wurde ohne
  Rueckfrage verweigert — bei `dontAsk` sieht das aus wie ein Rechtefehler, ist aber
  selbst verursacht. Behebung: `cd` zurueck auf `~/fabrik`, dann greift es wieder. Besser:
  in Bash mit vollen Pfaden arbeiten und gar nicht wechseln.

- 2026-09-01 — **In diesem Lauf gab es kein `rustc`** (`command -v rustc` leer, kein
  `~/.cargo`), und `Bash` durfte weder in `$TMPDIR` schreiben noch `python3 -c` ausfuehren.
  Die Rust-Fassung ist daher **nicht uebersetzt und nicht gerechnet**, sondern nur gelesen.
  Wer die Java-Fassung mit dem Compiler in der Hand gebaut hat und diese ohne, darf die
  Spalte „Anlaeufe bis zum gruenen Uebersetzungslauf" nicht zwischen beiden vergleichen.

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

- 2026-09-02 — **Paket 0013, unsicher und nicht uebersetzt.** Faellt der Baulauf rot
  aus, zuerst hier nachsehen: die zwei `static_assert` mit `constexpr`-Lambda in
  `src/pruefsumme.cpp`, `std::span` aus einem `constexpr std::array` im konstanten
  Ausdruck, `std::array<uint8_t,0>` fuer die leere Eingabe. Die Zahlenwerte sind es nicht.
- 2026-09-02 — **Paket 0013, Abnahme 4: bewusst keine selbst gerechnete Zahl als
  `static_assert`.** Beide Reihenfolgenachweise stehen auf veroeffentlichten Werten
  (61 00 -> 0x089be207b544f1e4; d5 6b b9 53 42 87 08 36 -> 0) plus Ungleichheit; die
  Gegenzahl steht nur in der Testausgabe. Liest der Pruefer „ausgeschriebene Werte" als
  „beide Zahlen als Literal", ist das ein Befund; mein Handwert fuer 00 61 waere
  0x08326707b4eb37da, ungeprueft. Auch `fnv1a64_text` geht ueber das Paket hinaus,
  noetig fuer die Vektoren.
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
