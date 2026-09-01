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

---

## Was funktioniert

- 2026-09-01, dritter Lauf — **Eine Tabelle, die sich „abschliessend" nennt, ist erst dann
  abschliessend, wenn einmal jemand gegen sie abgezählt hat.** Ich hatte in T45 eine Regel
  geschrieben, die genau das vom Jahrgangsbau verlangt, und sie in der eigenen Fassung nicht
  angewandt. Beim Auszählen der 310 Adressen fielen elf ohne zulässigen Eintrag heraus, zwei
  ohne passende Eintragsart und sechs, die nach dem Wortlaut **zwei** Einträge getragen und
  den Bau abgebrochen hätten. Der Prüfer hatte die Bedingung zuvor für erfüllt erklärt.
  Regel ab jetzt: **Eine Prüfvorschrift, die ich schreibe, führe ich im selben Lauf einmal
  von Hand aus** — sonst prüfe ich die Zusage und nicht die Sache.
- 2026-09-01, dritter Lauf — **Zwei unabhängige Aufteilungen derselben Menge nebeneinander
  legen.** Die 310 Adressen sind einmal nach Gruppe (T15) und einmal nach Herkunft (T45)
  aufgeteilt; beide Summen müssen aufgehen. Die zweite ging vier Fassungen lang nicht auf,
  ohne dass es jemandem auffiel, weil es sie als Summe gar nicht gab. Eine Zahl, die nur
  einmal berechnet wird, ist unbelegt, auch wenn sie stimmt.
- 2026-09-01, dritter Lauf — **Die Dimensionsspalte einer Reihenliste gegen die
  Adressliste legen.** „Verbraucherpreise | 4" und „Wechselkurs | 3" heissen: die Restwelt
  und die USA haben dort keinen Anker. Das stand seit Fassung 2 da und hat nie jemand gegen
  T15 gehalten. Zwei Spalten, fünf Minuten, elf Befunde.
- 2026-09-01 — **Eine fehlende Prüfstandsvorgabe aus dem Entwurf *ableiten* statt sie zu
  erfinden.** Die Zielgröße des Suchbots fehlte; statt eine Gewichtung zu erfinden, habe ich
  die Ergebnisgröße aus `spiel.md` auf den Zwischenzustand gerechnet — kein freier Parameter,
  also fällt der Einwand „das Maß misst die Wahl des Bauagenten" nicht durch ein Argument,
  sondern weil es keine Wahl mehr gibt. **Bestätigt im dritten Lauf:** Der Spielentwerfer hat
  daraufhin seine eigene Formel an meine angeglichen, statt umgekehrt. Eine abgeleitete Größe
  zieht die andere Seite zu sich.
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
- 2026-08-31 — **Rust ist die Wahl mit dem höchsten Autorenaufwand, die ich vertreten
  konnte.** Hängen die Bauagenten wiederholt am Ausleihprüfer (erkennbar am Logbuch des
  Kernbauers oder an dreimal `zurueck` auf demselben Paket), gehört die Wahl neu gerechnet —
  dann gegen C# mit `checked`-Arithmetik.

## Offene Fährten

- **Geschlossen am 2026-09-01, dritter Lauf:** die Steckplatzzahl (`spiel.md` trägt die
  allgemeine Form jetzt selbst, dreimal Befund, jetzt weg), die Beteiligungsfrage
  (`spiel.md` sagt ja, T47), die Aggregation des fehlenden Einflusses (beide Dokumente
  rechnen dieselbe Formel, die Kappung ist ganz entfallen). **Lehre aus allen dreien:** Eine
  Stelle, die zwei Dokumenten gehört, schliesst sich nicht durch eine bessere Formulierung,
  sondern erst, wenn beide Gewerke im selben Zyklus laufen.
- 2026-08-31, **Zahlen berichtigt am 2026-09-01** — **Ob der Prüfjahrgang baubar ist, ist
  eine Behauptung.** 1997–2021, 25 Stützstellen, R = 24; `spiel.md` verlangt alle 31
  Sollreihen und alle 40 Handelsströme darüber ohne Füllung. Verdachtsfall bleibt die
  chinesische und die brasilianische Leitzinsreihe (IWF IFS, Abruf mit HTTP 403 abgewiesen);
  `FR.INR.LEND` ist nur ein Indiz. Das bleibt die wahrscheinlichste Stelle, an der das
  Vorhaben an Daten scheitert. Der Jahrgangsbau gehört an den Anfang der Paketfolge, weil er
  das Vorhaben *kippen* kann — nicht weil ein engeres Fenster teuer wäre (seit T40 eine
  Manifestzeile).
- 2026-08-31, **für R = 24 neu gerechnet am 2026-09-01** — **Ob ein Suchbot mit Tiefe 1 für
  Maß 2 stark genug ist, ist weiter ungeprüft.** *Wonach* er sucht, ist seit T44
  parameterfrei entschieden; offen ist nur, *wie weit*. Tiefe 2 kostet je Partie
  `24 × (1 + 60 × 61) = 87.864` statt 1.464 Weltschritte, Maß 2 und 3 zusammen 664 Mio, rund
  14 Minuten auf acht Kernen beim Planwert. Meine ältere Notiz („sprengt den Nachtlauf") war
  falsch. Ist der Bot zu schwach, misst Maß 2 seine Schwäche statt die des Spiels — dann ist
  Tiefe 2 der Weg, nicht eine Schwellenänderung. Zusätzliches Argument: Der Umweg der
  Klasse 2 (Beteiligung verbilligt späteres Lobbying) ist bei Tiefe 1 grundsätzlich
  unsichtbar.
- 2026-09-01, dritter Lauf, **neu und an den nächsten Lauf** — **Die vier Restweltadressen
  aus T46 (`leitzins`, `wechselkurs`, `staatsschuld`, `haushaltssaldo`) sind Ballast mit
  Auflage.** Sie existieren nur, weil `spiel.md` die Zahl 310 nennt und ich sie nicht ändern
  darf; keine Regel liest sie. Fällt später eine Regel an, die eine davon braucht, ist das
  ein ADR. Sauberer wäre, den Aggregatblock der Restwelt zu kürzen — das kostet eine Zeile
  in `spiel.md` und ist deshalb nicht meine Entscheidung. Beim nächsten Lauf des
  Spielentwerfers erwähnenswert, aber kein Befund: Es blockiert nichts.
- 2026-09-01, dritter Lauf — **Die Neubasierung (T8) greift im Prüfjahrgang nie**, ist also
  ungeprüfter Code, und dasselbe gilt für die Ausschlussregel `soll = 0` in T42. Beide haben
  eine Testauflage bekommen (Regressionspartie 1980). Allgemein: **Jeder Zweig, den der
  Nachtlauf nie betritt, braucht im selben Lauf eine Auflage, sonst entsteht er ungeprüft.**
