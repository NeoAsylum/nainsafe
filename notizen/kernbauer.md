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

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

- 2026-09-01 — **Unsicher, und es betrifft alle vier Sprachen: „mod 2^63 - 1" in der
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
