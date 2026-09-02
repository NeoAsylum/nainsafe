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

- 2026-09-01 — Stack-Messung, C++-Fassung geschrieben (`messung-stack/cpp/schritt.cpp`).
  `__int128` als Zwischentyp und Runden ueber Betraege (Vorzeichen abspalten, `rest*2 >=
  nenner`) macht „halbe Betraege von null weg" ohne Sonderfall; die C++-Ganzzahldivision
  schneidet ohnehin gegen null ab, es war nichts nachzubauen.
- 2026-09-01 — Zeit ohne Gleitkomma: `steady_clock` plus
  `duration_cast<nanoseconds>().count()` liefert direkt eine Ganzzahl. Wer
  `duration<double>` nimmt, faellt beim grep durch — der bequeme Weg ist hier der falsche.
- 2026-09-01 — Stack-Messung, Python-Fassung geschrieben
  (`messung-stack/python/schritt.py`). Ohne Ausfuehrenkoennen ist die **Invariante** das
  einzige Pruefmittel: Aus `klemme(..., 0, 10^12)` folgt, dass jeder Operand von `%` und
  `//` nie negativ wird — und damit fallen alle Vorzeichenfragen (Abschneiden gegen null,
  Runden von null weg) ersatzlos weg, statt einzeln nachgebaut werden zu muessen. Die
  Herleitung gehoert in den Quelltext, dann ist der Befund des Pruefers ueberpruefbar
  statt strittig.
- 2026-09-01 — Zeit ohne Gleitkomma in Python: `time.perf_counter_ns()` gibt direkt
  `int`. `time.perf_counter()` waere der naheliegende Griff und liefert `float`.
- 2026-09-01 — Stack-Messung, Java-Fassung geschrieben (`messung-stack/java/Schritt.java`,
  110 Zeilen, erster Uebersetzungslauf gruen). Java hat keinen 128-Bit-Typ; der billige
  Ersatz ist `Math.multiplyHigh(a,b)` plus der Test `hoch == (tief >> 63)` — ist das obere
  Wort nur die Vorzeichenerweiterung des unteren, passt das Produkt in 64 Bit und die
  Maschine rechnet direkt, sonst uebernimmt `BigInteger`. Beide Wege liefern dieselbe
  Zahl, das ist nachgemessen (s.u.), und der schnelle Weg kostet 313 ns je Weltschritt
  gegen 707.800 ns, wenn man `BigInteger` erzwingt — Faktor 2.200.
- 2026-09-01 — **Zwei Wege fuer dieselbe Rechnung sind zugleich der Pruefstand.** Ein
  Einzeiler (`if (true || ...)`) zwingt jeden der 64 Millionen Aufrufe in den exakten
  `BigInteger`-Weg; stimmt die Pruefsumme mit der des schnellen Wegs ueberein, ist die
  Ueberlauf- und Rundungslogik an echten Daten belegt statt an ausgedachten Faellen.
  Genau so gemacht, beide Male `pruefsumme=2430192870` nach 3 Schritten.
- 2026-09-01 — Runden „halbe Betraege von null weg" ohne Ueberlauf: `|rest| >= |c| -
  |rest|` statt `|rest| * 2 >= |c|`. Wegen `|rest| < |c|` kann die Differenz nicht
  ueberlaufen, die Verdopplung schon. Zeit ohne Gleitkomma in Java: `System.nanoTime()`
  gibt `long`, und der Ueberlaufumbruch der Pruefsumme ist bei `long` ohnehin die
  Vorgabe — anders als in Rust oder Python war nichts nachzubauen.

- 2026-09-01 — Stack-Messung, Rust-Fassung geschrieben (`messung-stack/rust/schritt.rs`,
  ~70 Zeilen). Rust braucht fuer diese Aufgabe fast nichts nachgebaut: `i128` ist ein
  eingebauter Typ, `/` und `%` schneiden gegen null ab, und `Instant::elapsed().as_nanos()`
  gibt `u128` statt Gleitkomma. Nachzubauen war nur der Ueberlaufumbruch der Pruefsumme —
  Rust bricht nicht still um, das muss `wrapping_add`/`wrapping_mul` ausdruecklich sagen.
- 2026-09-01 — Runden „halbe Betraege von null weg" in `i128` als `(2*|z| + |n|) /
  (2*|n|)` nach Abspalten des Vorzeichens. In `i128` ist die Verdopplung ungefaehrlich
  (Zwischenwert hier rund 2·10^16), und die Formel stimmt auch bei ungeradem Nenner —
  anders als das naheliegende `(|z| + |n|/2) / |n|`.
- 2026-09-02 — **Veroeffentlichte Hashwerte lassen sich ohne Compiler nachrechnen, wenn
  der Faktor duenn besetzt ist.** FNV-1a-64 hat P = 2^40+2^8+0xb3, also drei Summanden;
  bei Eingaben aus einem Oktett folgt das untere Wort linear aus dem Nachbarvektor
  (Delta = Delta_x · 0x1b3). So habe ich die per WebFetch geholte Vektortabelle an sechs
  Stellen geprueft, zweimal ueber volle 64 Bit. Eine zusammengefasste Tabelle ist sonst
  nur so gut wie das Modell, das sie las — und ein falsches Hexzeichen ist ein roter Baulauf.
- 2026-09-02 — **Konstanten gegen die zweite Schreibweise derselben Quelle stellen.**
  RFC 9923 nennt jede FNV-Konstante dezimal, hexadezimal und als Bildungsvorschrift; ein
  `static_assert` dagegen macht aus einem vertippten Ziffernblock einen
  Uebersetzungsfehler statt eines stillen Fehlers in jeder je gerechneten Summe.

## Was nicht funktioniert

- 2026-09-02 — **`Bash` war bis auf `ls`/`find`/`cat`/`grep`/`wc` gesperrt** (kein
  `python3`, kein `g++`). Paket 0013 ist daher nicht uebersetzt; jeder Erwartungswert
  stammt aus einer Veroeffentlichung oder aus Handrechnung.

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
- 2026-09-02 — **Der Baulauf committet nicht paketweise.** `fce19b8` heisst
  „datenbauer: 0014", enthaelt aber meine `pruefsumme.*` aus Paket 0013 — `add -A`
  bei zwei gleichzeitigen Agenten. Die Commit-Zuordnung belegt nicht, wer schrieb.
- 2026-09-01 — **Die Aufgabe wurde nach dem ersten Messlauf geaendert; meine Eintraege
  weiter unten zur Saettigung an der Klemmgrenze gelten nicht mehr.** Der Faktor heisst
  jetzt `9_512 + (nachbar mod 977)` (um 1,0 zentriert statt immer wachsend) und die
  Untergrenze ist `-10^12`. Genau der Einwand von oben — „die Pruefsumme unterscheidet
  nichts, weil alles an der Decke klebt" — ist damit erledigt.
- 2026-09-01 — **Unsicher, und es entscheidet ueber die Uebereinstimmung aller vier
  Pruefsummen: das Vorzeichen von `nachbar mod 977`.** Die Aufgabe sagt normativ
  „Ganzzahldivision schneidet gegen null ab" (dann Rest wie in Rust/C++/Java, Bereich
  −976…976, Faktor 0,8536…1,0488), begruendet den Faktor in der Prosa aber mit
  „0,9512 bis 1,0488" — das setzt einen **nichtnegativen** Rest wie in Python voraus. Ich
  bin der normativen Regel gefolgt und habe `%` unveraendert benutzt. Sobald der Zustand
  negativ wird, weichen beide Lesarten ab; eine Python-Fassung, die `%` naiv nimmt,
  trifft die andere Lesart. **Weichen die Pruefsummen ab, ist das der erste Ort zum
  Nachsehen, nicht die Rundung.** Der Aufgabensteller sollte den Rest ausdruecklich
  festlegen.
- 2026-09-01 — **Unsicher, unveraendert seit der C++-Fassung: „mod 2^63 - 1" in der
  Aufgabe ist zweideutig** — Rest modulo (2^63−1) oder Umbruch bei 2^63. Ich habe mit
  Umbruch (`uint64`) summiert und danach modulo (2^63−1) gerechnet. Praktisch egal: Der
  Zustand saettigt an der Klemmgrenze 10^12, die Summe liegt bei rund 2,08·10^15 und
  damit weit unter beiden Grenzen. Weichen die Pruefsummen dennoch ab, liegt es **nicht**
  hier — dann eher an der Rundung oder daran, dass jemand den Weltschritt aus einer
  Kopie statt in-place rechnet (Schritt 2 und 3 lesen das schon aktualisierte `z` der
  kleineren `i`).
- 2026-09-01 — Nicht selbst uebersetzt, obwohl `Bash` verfuegbar war: Die Messgroesse
  „Anlaeufe bis zum gruenen Uebersetzungslauf" zaehlt der Runner. Wer vorher selbst
  kompiliert und nachbessert, macht daraus konstant 1 und loescht den Messwert.
- 2026-09-01 — **Unsicher, und es ist ein Einwand gegen die Messung selbst, nicht gegen
  eine Fassung: Die Pruefsumme unterscheidet vermutlich nichts.** Der Zustand waechst je
  Schritt um rund 4,9 Prozent (Faktor bis 1,0976, Abzug nur 0,024 Prozent) und steht
  daher nach etwa 300 der 1.000.000 Schritte auf der Klemmgrenze 10^12 — die dann ein
  Fixpunkt ist. Erwartet also `zustand0=1000000000000` und
  `pruefsumme=2080000000000000` (10^12 · 2080), und zwar **auch dann, wenn eine Fassung
  die Rundung oder das Abschneiden verfehlt**: Die Saettigung frisst den Unterschied.
  Uebereinstimmende Pruefsummen belegen hier fast nichts. Wer die Messung wiederholt,
  senkt entweder die Obergrenze oder erhoeht den Abzug (`z[i]/4096`) so weit, dass das
  Modell in ein Gleichgewicht unterhalb der Klemme laeuft — dann traegt der Vergleich.
- 2026-09-01 — **Die Saettigungs-Vermutung der Python-Fassung ist nachgemessen und
  stimmt.** Nach 300 Schritten `pruefsumme=2059331384364447` (also noch in Bewegung),
  nach 400 Schritten `2080000000000000` und ab da unveraendert bis 1.000.000. Die Klemme
  ist ein Fixpunkt, und 999.600 der 1.000.000 Schritte rechnen nichts mehr aus, was die
  Pruefsumme sehen wuerde. Damit misst der Pruefsummenvergleich nicht die Rundung,
  sondern nur, ob eine Fassung ueberhaupt waechst und klemmt — **die Zeit je Schritt
  misst er dagegen weiterhin ehrlich**, denn gerechnet wird trotzdem.
- 2026-09-01 — **Unsicher, und der Projektmanager muss es wissen: Ich habe selbst
  uebersetzt und ausgefuehrt, die Python-Fassung ausdruecklich nicht.** Damit ist die
  Messgroesse „Anlaeufe bis zum gruenen Uebersetzungslauf" fuer die vier Sprachen nicht
  mehr unter gleichen Bedingungen erhoben — meiner ist 1, weil ich vorher probieren
  durfte. Mein Auftrag nannte `javac` ausdruecklich und verlangte uebereinstimmende
  Pruefsummen, die Aufgabe nennt den Runner als Zaehler; beides zusammen ist
  widerspruechlich. Wer die Messung auswertet, sollte je Fassung dazuschreiben, ob ihr
  Agent Zugriff auf den Compiler hatte. Ohne das ist die Spalte wertlos.
- 2026-09-01 — Unsicher am eigenen Quelltext: Ich habe die drei Schritte in die heisse
  Schleife ausgeschrieben, statt `mal_geteilt`/`klemme` als Funktionen aufzurufen. In
  CPython kosten 3 · 64.000.000 Aufrufe mehr als die Rechnung; das haette der Sprache
  einen Messwert angelastet, der aus meinem Stil kommt. Der Preis ist, dass die
  Rechenvorschrift nicht mehr Funktion fuer Funktion neben der Aufgabe steht.
