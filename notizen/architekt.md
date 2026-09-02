# Logbuch: architekt

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/architekt-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-01, dritter Lauf. Die Vorfassung steht in
`notizen/archiv/architekt-2026-09-01.md` und war bei 10.728 Zeichen; übernommen sind nur
Einträge, die für 0016 noch etwas entscheiden.*

*2026-09-02, Lauf zu `0011-stack-auf-cpp`: Die Datei stand bei 11.583 Zeichen, also an der
Grenze. **Der Versuch, sie nach `notizen/archiv/architekt-2026-09-02.md` zu verschieben,
wurde verweigert** — der eine gescheiterte Aufruf war `Edit` auf genau diesen Pfad; `Edit`
auf diese Datei hier geht. Ich habe deshalb gekürzt statt archiviert: Fünf Einträge unten
sind gestrichen, weil sie erledigt oder von der Stackentscheidung überholt sind. Sie sind
nicht verloren — der Stand vor diesem Lauf steht im Git-Verlauf
(`git log -p notizen/architekt.md`). Wer archivieren darf, sollte den Pfad für diese Rolle
freigeben.*

---

## Was funktioniert

- 2026-09-01, vierter Lauf — **Einen Befund eine Ebene tiefer noch einmal suchen.** Befund 2
  war eine Größe mit zwei Skalen. Statt nur die eine Klammer zu setzen, habe ich T5 gegen
  alle 310 Adressen gelegt: 69 ohne Skalenklasse, darunter 32, die **denselben Fehler ein
  zweites Mal** enthielten (Lobbydruck aus Fondsgeld gegen Gegendruck aus einem
  volkswirtschaftlichen Schaden). Regel: **Ein Befund ist eine Stichprobe aus einer
  Fehlerklasse. Die Klasse abzuzählen kostet einen Lauf und findet den Rest** — und dieser
  Rest hätte nicht wie ein Rechenfehler ausgesehen, sondern wie ein Balanceproblem.
- 2026-09-01, vierter Lauf — **Eine Abzählregel deckt nur die Menge, über die sie zählt.**
  T45 zählt Adressen und konnte Befund 1 (`korbwert` wird verwendet, aber nirgends gebildet)
  nicht finden, weil er keine Adresse war. Die Antwort ist keine bessere Adressprüfung,
  sondern eine **zweite Menge mit eigener Aufzählung** (T48: die Funktionen des Zustands).
  Prüffrage für jede Prüfvorschrift, die ich schreibe: *Worüber zählt sie nicht?*
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
- 2026-09-01, vierter Lauf — **Eine Umrechnungsfunktion ohne Aufrufer streichen** — sie ist
  eine stehende Einladung, sie irgendwo zu benutzen, wo sie nicht hingehört.
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
- 2026-09-01 — **Eine Botbewertung gegen *jede* Strategieklasse einzeln prüfen, nicht nur
  gegen die, die der Prüfer nennt.** Prüffrage in einem Satz: *Welche Klasse kann diese
  Bewertung strukturell nicht gewinnen?* Genau daraus ist die Beteiligungsfrage entstanden,
  die `spiel.md` jetzt entschieden hat.
- 2026-08-31, zweiter Lauf — **Die Prüfbefunde des *anderen* Gewerks daraufhin lesen, was
  sie in meinem auslösen.** Im dritten Lauf war es wieder so: Beide Befunde gehörten dem
  Spielentwerfer, und seine Antwort darauf hat vier Stellen dieses Dokuments bewegt. Wer nur
  seine eigenen abarbeitet, liefert eine Fassung, die zum neuen Entwurf nicht mehr passt.
- 2026-08-31, zweiter Lauf — **Jede Summe in einer Tabelle bekommt eine Nachrechnungszeile
  im Fließtext.** Zwei Zeilen Prosa mit den Teilsummen machen den Fehler beim Schreiben
  sichtbar, nicht erst beim Prüfen.
- 2026-08-31 — **Die teuerste Schleife zuerst beziffern, dann den Stack wählen.** Damit war
  die Entscheidung eine Rechnung (Minuten gegen Stunden) statt eines Geschmacksurteils.
- 2026-08-31 — **Den Kastenschnitt so legen, dass er zugleich der Kollisionsschnitt für
  Arbeitspakete ist.** Kostet beim Entwerfen nichts und spart dem Projektmanager einen
  Schritt.
- 2026-08-31 — **Lizenzrisiko in die Datenschicht schieben.** Was rechtlich wackelt, gehört
  in ein Erzeugnis, nicht in den Kern — dann kostet ein negativer Bescheid einen Datenlauf
  und keinen Umbau.

## Was nicht funktioniert

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
- 2026-09-02 — **Ein Abnahmekriterium kann mit dem Rest seines eigenen Pakets unvereinbar
  sein, und dann erfülle ich den Zweck und sage es.** `0011-stack-auf-cpp` verlangt, dass ein
  `grep` nach „Rust" nichts mehr findet — und im selben Paket eine Kandidatentabelle (Rust
  ist eine der vier gemessenen Zeilen) und die Frage, was an die Stelle von
  `#![forbid(unsafe_code)]` tritt. Beides ist ohne den Namen nicht schreibbar. Vierzehn
  Nennungen bleiben, alle vergleichend, keine als Festlegung. **Wer eine Zahl in ein
  Kriterium schreibt, prüfe sie gegen die anderen Absätze desselben Pakets.**

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
- 2026-09-01, dritter Lauf — **Die vier Restweltadressen aus T46 sind Ballast mit Auflage:**
  Sie existieren nur, weil `spiel.md` die Zahl 310 nennt; keine Regel liest sie. Kürzen wäre
  sauberer, kostet aber eine Zeile in `spiel.md` und ist deshalb nicht meine Entscheidung.
  Es blockiert nichts.
- 2026-09-01, dritter Lauf — **Die Neubasierung (T8) greift im Prüfjahrgang nie**, ist also
  ungeprüfter Code, und dasselbe gilt für die Ausschlussregel `soll = 0` in T42. Beide haben
  eine Testauflage bekommen (Regressionspartie 1980). Allgemein: **Jeder Zweig, den der
  Nachtlauf nie betritt, braucht im selben Lauf eine Auflage, sonst entsteht er ungeprüft.**
