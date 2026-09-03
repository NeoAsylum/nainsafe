# Logbuch: architekt

Private Arbeitsnotizen dieser Rolle. Regeln dazu stehen in `CLAUDE.md`: höchstens 12.000
Zeichen, Lehre statt Beleg, bei Erreichen der Grenze archivieren.

*Neu begonnen am 2026-09-01; Vorfassung in `notizen/archiv/architekt-2026-09-01.md`.*

*2026-09-02 bei 11.583 Zeichen, 2026-09-03 bei 11.962 — beide Male an der Grenze, **beide
Male wurde das Archivieren verweigert.** Der gescheiterte Aufruf war jeweils `Edit` auf
`notizen/archiv/architekt-<datum>.md`; `Edit` auf diese Datei geht, und alles andere in
beiden Läufen ging auch. Ich kürze deshalb erneut hier; verloren ist nichts, jeder frühere
Stand liegt in `git log -p notizen/architekt.md`. **An den Betreiber: Diese Rolle braucht
Schreibrecht auf `notizen/archiv/`** — sonst kostet das Kürzen jeden zweiten Lauf einen Teil
des Gedächtnisses.*

---

## Was funktioniert

- 2026-09-01, vierter Lauf — **Ein Befund ist eine Stichprobe aus einer Fehlerklasse; die
  Klasse abzuzählen kostet einen Lauf und findet den Rest.** Aus einer Größe mit zwei Skalen
  wurden beim Auszählen von T5 gegen alle 310 Adressen 69 ohne Skalenklasse, darunter 32 mit
  demselben Fehler. Der Rest hätte nicht wie ein Rechenfehler ausgesehen, sondern wie ein
  Balanceproblem. Zweite Hälfte derselben Lehre: **Eine Abzählregel deckt nur die Menge, über
  die sie zählt** — T45 zählt Adressen und konnte deshalb eine fehlende *Funktion* nicht
  finden. Prüffrage: *Worüber zählt sie nicht?*
- 2026-09-02, **neu und die teuerste Lehre dieses Laufs** — **Ein ADR trägt eine
  Entscheidung, keinen Beweis. Die Entscheidung bindet mich, seine technische Behauptung
  nicht.** ADR 0011 führt `-fsanitize=undefined` ein, damit ein Überlauf „laut statt still"
  wird — das kann sie nicht, weil `-fwrapv` aus derselben Massnahmenliste genau diese Prüfung
  abschaltet (seit GCC 8). **Eine Websuche von zwei Minuten** hat es geklärt. Die zwei
  Massnahmen hoben sich auf, und niemand hätte es gemerkt, bis ein Überlauf beim Käufer
  auftritt. Prüffrage für jeden ADR, den ich umsetze: *Welcher Satz darin ist eine Tatsache,
  und habe ich sie nachgesehen?*
- 2026-09-02, **neu** — **Trägt eine Messung ein Urteil, lies das Erzeugnis statt der
  Zusammenfassung.** ADR 0011 erklärt die 947 ns der C++-Messung mit einem fehlenden
  `__int128`. Der Quelltext benutzt `__int128`; `objdump` über die zwei abgelegten Programme
  zeigt den wirklichen Unterschied in einer Zeile — `__divmodti4` gegen `__udivti3`, also
  signiert dividieren gegen Beträge dividieren. Zwei Minuten, und aus einer Vermutung wurde
  eine Bauvorgabe (T6b). **Bei jedem Leistungsbefund: Welches Erzeugnis liegt herum, das die
  Frage direkt beantwortet?**
- 2026-09-03, **neu** — **Eine Aufzählung von Rechenarten muss eine Partition sein, sonst
  ist sie eine Liste mit Loch.** T7 Massnahme 4 zählte {Multiplikation-Division, Addition,
  Subtraktion} auf und liess die blanke Multiplikation zweier `i64` dazwischen liegen; unter
  `-fwrapv` bricht die still um. Der Prüfer hat es gefunden, ich hätte es beim Schreiben
  finden können. **Wo ich Operationen aufzähle, schneide ich seitdem nach der Rechenart und
  frage, welche Art zwischen zwei Punkten liegt** — nach der *Stelle* geschnitten wird jede
  solche Liste beim nächsten Zusatz wieder unvollständig.
- 2026-09-03, **neu** — **Eine Grep-Vorschrift einmal gegen den echten Baum laufen lassen,
  bevor sie im Dokument steht.** Mein erster Regexentwurf für „blanke Multiplikation" traf 40
  Zeilen `const char*` und kursive Sterne in Kommentaren. Erst das Muster ` * ` ergab 58
  Zeilen, die sich sämtlich vier Arten zuordnen liessen. Ohne den Probelauf hätte dort eine
  Vorschrift gestanden, die beim ersten Gebrauch unbrauchbar ist — und gründlich ausgesehen.
- 2026-09-01, dritter Lauf — **Eine Prüfvorschrift, die ich schreibe, führe ich im selben
  Lauf einmal von Hand aus** — sonst prüfe ich die Zusage und nicht die Sache. Beim
  Auszählen der 310 Adressen gegen die eigene Regel aus T45 fielen elf ohne Eintrag heraus
  und sechs, die nach dem Wortlaut zwei getragen hätten. Der Prüfer hatte die Bedingung
  zuvor für erfüllt erklärt.
- 2026-09-01, Läufe drei und vier — **Unabhängige Aufteilungen derselben Menge nebeneinander
  legen.** Die 310 Adressen sind dreifach aufgeteilt (Gruppe T15, Herkunft T45, Skala T49);
  jede neue Aufteilung fand beim ersten Auszählen Lücken. Eine Zahl, die nur einmal berechnet
  wird, ist unbelegt, auch wenn sie stimmt.
- 2026-09-01 — **Eine fehlende Vorgabe aus dem Entwurf *ableiten* statt sie zu erfinden.**
  Die Zielgröße des Suchbots entstand als Rechnung auf `spiel.md` statt als eigene
  Gewichtung — ohne freien Parameter fällt der Einwand „das Maß misst die Wahl des
  Bauagenten" weg, weil es keine Wahl mehr gibt. Der Spielentwerfer hat daraufhin seine
  Formel an meine angeglichen, statt umgekehrt.
- 2026-08-31, zweiter Lauf — **Die Prüfbefunde des *anderen* Gewerks daraufhin lesen, was
  sie in meinem auslösen.** Im dritten Lauf war es wieder so: Beide Befunde gehörten dem
  Spielentwerfer, und seine Antwort darauf hat vier Stellen dieses Dokuments bewegt. Wer nur
  seine eigenen abarbeitet, liefert eine Fassung, die zum neuen Entwurf nicht mehr passt.
- 2026-08-31, zweiter Lauf — **Jede Summe in einer Tabelle bekommt eine Nachrechnungszeile
  im Fließtext.**
- 2026-08-31 — **Den Kastenschnitt so legen, dass er zugleich der Kollisionsschnitt für
  Arbeitspakete ist.** Kostet beim Entwerfen nichts und spart dem Projektmanager einen
  Schritt.

## Was nicht funktioniert

- 2026-09-03, **neu und die Lehre dieses Laufs** — **Beim Übersetzen einer Vorgabe in eine
  andere Sprache überlebt nur die Hälfte, die ein Gegenstück hat.** Der T1-Satz trug zwei
  Zusagen: Werkzeugkette festgenagelt (→ `werkzeugkette.cmake`, übersetzt) und Abhängigkeiten
  mit `cargo vendor` eingefroren (→ nichts, weil CMake keinen Befehl gleichen Namens hat).
  Die zweite fiel lautlos weg, und „gestrichen" sah aus wie „übersetzt". Dasselbe eine Ebene
  tiefer bei T2: Die Erzwingung las weiter *eine* Datei, während CMake die Lücke in der
  Nachbardatei hat. **Regel: Jeden übersetzten Satz vorher in seine Zusagen zerlegen und jede
  einzeln quittieren** — übersetzt, anders eingelöst oder ausdrücklich fallengelassen.

- 2026-09-01, vierter Lauf — **Eine Vorgabe, die eine *Menge* nennt, ohne sie abzählbar zu
  machen.** T8 sagte seit Fassung 2 „alle nominalen Größen dieses Landes werden durch 1.000
  geteilt". Es sind genau fünf Adressen je Gebiet; alles andere ist real, eine Rate, ein
  Zähler oder steht im Numéraire. Der Bauagent hätte raten müssen, und die Produktivität
  wäre der wahrscheinliche Fehlgriff gewesen.
- 2026-09-01, dritter Lauf — **Eine Eintragsart mit „derzeit allein X" beschreiben.** T45
  sagte „`Vorgabe(T-Nummer)`, derzeit allein T23 Punkt 1", und das war schon beim Schreiben
  falsch — die `basiswechsel`-Zähler hingen seit Fassung 2 an T8. Ein „derzeit allein"
  behauptet eine Vollständigkeit, die niemand geprüft hat, und liest sich wie ein Befund.
  Aufzählungen gehören in eine eigene Tabelle mit Summe, nie in einen Nebensatz.
- 2026-09-01 — **Eine Formulierung, die eine fehlende Vorgabe wie eine vorhandene aussehen
  lässt.** „Bewertet durch ein Nachspiel von einem Zug" beschrieb einen *Vorgang* statt einer
  *Zielgröße*; drei Fassungen lang hat es niemand als Lücke gelesen. Regel: Wo etwas
  verglichen wird, muss das Verglichene ein Substantiv mit Rechenvorschrift sein, kein Verb.
- 2026-08-31, zweiter Lauf — **Keine Zahl in den Text, die ich nicht in diesem Lauf
  ausgerechnet habe**, auch keine aus meiner eigenen Vorfassung. Drei falsche Zahlen hatten
  dieselbe Ursache: übernommen statt nachgerechnet.
- 2026-08-31 — **Der Planwert von 10 Mikrosekunden je Weltschritt ist geschätzt, nicht
  gemessen**, und die `i128`-Divisionen können ihn um das Drei- bis Fünffache verfehlen.
  Deshalb steht `ticks_je_sekunde` als Berichtspflicht in jedem Prüfstandsbefund. Beim
  nächsten Lauf ist das Erste, was ich lese, der gemessene Wert — liegt er über 50 µs, muss
  die Markträumung anders gebaut werden als über 40 Halbierungsschritte.
- 2026-09-02, **am 2026-09-03 bestätigt** — **Ein Abnahmekriterium kann mit dem Rest seines
  eigenen Pakets unvereinbar sein, und dann erfülle ich den Zweck und sage es.**
  `0011-stack-auf-cpp` verlangte ein `grep` ohne Rust-Treffer und im selben Paket eine
  Kandidatentabelle, in der Rust eine der gemessenen Zeilen ist. Der Projektmanager hat das
  Kriterium daraufhin berichtigt, der Prüfer gegen die berichtigte Fassung geprüft. **Den
  Zweck erfüllen und den Widerspruch benennen war richtig** — hätte ich still das Kriterium
  gehalten, wäre die Tabelle weggefallen.

## Offene Fährten

- **Lehre aus fünf geschlossenen Fährten (Läufe drei und vier):** Eine Stelle, die zwei
  Dokumenten gehört, schliesst sich nicht durch eine bessere Formulierung, sondern erst, wenn
  beide Gewerke im selben Zyklus laufen — und der andere zuerst.
- 2026-09-01, vierter Lauf, **an den nächsten Lauf** — **Zwei Beobachtungen an `spiel.md`,
  die ein Prüfer als Befund zählen könnte und die dann nicht mir gehören:** „Schaden" in
  Gegenkraft 5 hat keine Rechenvorschrift (ich habe nur die Einheit gesetzt), und
  `fonds.sichtbarkeit` ist **eine** Adresse, während Aktion 5 von *einer Position* spricht.
  Beide stehen in Abschnitt 12 als Beobachtung. Fülle ich sie selbst, misst Maß 2 meine
  Wahl — dieselbe Begründung wie bei T44.
- 2026-09-02, **neu** — **ADR 0011 stützt sein erstes Argument auf einen Wechsel, den es
  nicht anordnet.** Es sagt, die plattformübergreifende Reproduzierbarkeit falle weg, *wenn*
  der Spielstand den Zustand speichert statt der Aktionsfolge — in den Folgen steht dieser
  Wechsel nicht, T22 gilt unverändert. Ich habe daraus T52 gemacht statt den ADR zu deuten.
  Beim nächsten Lauf zuerst nachsehen, ob der Betreiber den Wechsel angeordnet hat; dann
  wird T52 billiger, aber nicht überflüssig.
- 2026-08-31, **Zahlen berichtigt am 2026-09-01** — **Ob der Prüfjahrgang baubar ist, ist
  eine Behauptung.** 1997–2021, 25 Stützstellen, R = 24, alle 31 Sollreihen und 40
  Handelsströme ohne Füllung. Verdachtsfall bleibt die chinesische und brasilianische
  Leitzinsreihe (IWF IFS, HTTP 403). Die wahrscheinlichste Stelle, an der das Vorhaben an
  Daten scheitert — deshalb gehört der Jahrgangsbau nach vorn: Er kann *kippen*, nicht nur
  verzögern.
- 2026-08-31, **für R = 24 neu gerechnet am 2026-09-01** — **Ob ein Suchbot mit Tiefe 1 für
  Maß 2 stark genug ist, ist ungeprüft.** *Wonach* er sucht, ist seit T44 parameterfrei;
  offen ist *wie weit*. Tiefe 2 kostet Maß 2 und 3 zusammen 664 Mio Schritte, rund 14 Minuten
  auf acht Kernen — meine ältere Notiz („sprengt den Nachtlauf") war falsch. Ist der Bot zu
  schwach, misst Maß 2 seine Schwäche; dann ist Tiefe 2 der Weg, nicht eine
  Schwellenänderung.
- 2026-09-03, **neu** — **`festkomma.hpp` hat kein `mal(a, b)`.** T7 Massnahme 4.3 verlangt
  es seit heute, und es ist die einzige Codezeile, die aus dem Rücklauf zu 0011 folgt. In
  Abschnitt 16 von `technik.md` an den Projektmanager gemeldet; ein Paket anzulegen ist nicht
  meine Rolle. Beim nächsten Lauf zuerst nachsehen, ob es gebaut ist — daran hängt, ob die
  Vorgabe eine Zusage oder eine Tatsache ist.
- 2026-09-01, dritter Lauf — **Die Neubasierung (T8) greift im Prüfjahrgang nie**, ist also
  ungeprüfter Code, und dasselbe gilt für die Ausschlussregel `soll = 0` in T42. Beide haben
  eine Testauflage bekommen (Regressionspartie 1980). Allgemein: **Jeder Zweig, den der
  Nachtlauf nie betritt, braucht im selben Lauf eine Auflage, sonst entsteht er ungeprüft.**
