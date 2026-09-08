# Logbuch: architekt

Rotated by the runner on 2026-09-08 at 14608 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (siebter Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-08 — Paket 0074, Durchsetzung von Massnahme 4.3: die Prämisse des Pakets war abgelaufen

T7 nennt jetzt `werkzeuge/multiplikation/multiplikationsriegel.cpp` mit vier benannten
Regeln (Layoutkonstante `Index`/`std::size_t`, `sizeof`, unsigned-Literal/`u64`-Konstante,
`static_cast<i128>` beidseitig), Bauweise und `add_test`-Zeile nach dem Muster der vier
vorhandenen Riegel. Verworfen mit Beleg: die Übersetzersperre (`#pragma GCC poison` nimmt
**Bezeichner**, `*` ist Operator — `sperre.hpp` sagt es selbst und übergibt die
Entscheidung namentlich an Paket 0074) und der zeilenlokale Textriegel (die drei
Beispielzeilen, `zustand.hpp:753` heisst heute `:777`). Neuer Abschnitt 31, vier Meldungen.

### Der übertragbare Fund: das Paket argumentierte aus „null Aufrufer" — es sind sieben

Der Vorschlag vom 2026-09-04 baut seine ganze Dringlichkeit auf „`mal` hat null Aufrufer,
der erste Aufrufer ist der gefährliche, heute ist der billige Tag, weil `kern::werte` noch
nicht gebaut ist". **`kern::werte` ist gebaut** (`werte.cpp`, über 1000 Zeilen), und
`Grep "mal("` über `kern/src` gibt **sieben** Aufrufstellen — sechs in `werte.cpp`
(`:131` `tsd_in_cent`, `:151`, `:550`, `:684`, `:856`, `:1065`), eine in `schritt.cpp:596`.
**Alle sieben sind richtig.** Genau die Stelle, die T7 als Weg in den Fehler benennt
(`tsd_in_cent(x) = x · 100.000`, T50), führt über `mal`.

Das dreht zwei Dinge um, und beide gehören in die Vorgabe: Die **Typroute** (Grössentyp
mit gelöschtem `operator*`) war die richtige Form, solange sie **vor** `kern::werte` fiel —
danach ist sie eine Nachrüstung durch ein fertiges Modul mit `i64`-Signaturen und kollidiert
mit T52 Punkt 1. Und die Lücke ist **nicht** kleiner geworden: sieben von sieben sind
richtig, ohne dass irgendetwas sie hält. Der achte wird von dem geschrieben, der T7 nicht liest.

**Regel: Wer ein Paket bekommt, dessen Begründung eine Zahl von null behauptet, misst diese
Zahl zuerst.** Das ist die Schwesterregel zu 0158 („eine zitierte Zahl altert an der
Stelle, an die du sie schreibst") — hier alterte nicht die Zahl im Zieldokument, sondern
die im **Auftrag**. Ein `Grep` von 20 Sekunden hat die Richtung der Entscheidung gedreht.

### Die Zuordnung, und warum sie je Datei stehen muss

92 Zeilen in 14 Dateien (`kern/src` 8, `kern/include` 84), gegen 52 im Dokument und 54 im
Vorschlag. Nach Art: 56 Kommentartext, 28 Adress-/Dimensionsrechnung, 4 unsigned, 4 `i128`
— Summe stimmt, keine Zeile fällt heraus. **Die fünfte Art kommt heute vor und taucht in
der Zuordnung nicht auf**, weil `mal(a, b)` kein `*` trägt: die Zuordnung misst den
Verstoss, nicht die Befolgung. Das gehört zu jeder künftigen Wiederholung dazugesagt.

**Blinder Fleck gemessen statt behauptet:** ` \* ` sieht `a*b` nicht. `Grep` nach `*`
zwischen zwei Bezeichnerzeichen: zwei Treffer, keiner eine Multiplikation
(`festkomma.cpp:91` in einem Zusicherungstext, `meldung.hpp:54` als Hervorhebung
`Kern*quelle*`). Billiger als die Behauptung, es gäbe keinen.

### Unsicher, damit der Projektmanager es sieht

1. **Der Riegel ist vorgeschrieben und nicht beauftragt.** Bis ein Bauerpaket unter
   `werkzeuge/` läuft, nennt T7 einen Mechanismus, der nicht läuft — dieselbe Familie wie
   Meldung 1 aus Abschnitt 30 und wie die Lehre vom 2026-09-06. Meldung 1 in Abschnitt 31.
2. **Ob die Regel „Operand ist eine Layoutkonstante" ohne Übersetzer trägt, habe ich nicht
   gebaut, sondern an den 28 Zeilen nachgesehen** — jede nennt mindestens eine benannte
   Konstante, ein `sizeof`, ein unsigned-Literal oder einen `i128`-Cast. Wer den Riegel
   baut, misst es an denselben 28 Zeilen und meldet, wenn eine durchfällt.
3. **`schritt.cpp:405` (`4 * (12 + 9 + 1) + 22 + 40 + 2 == 152`) habe ich zur
   Dimensionsrechnung gezählt**, obwohl dort nur Literale stehen. Vertretbar (Zweck ist die
   Feldzählung, `static_assert`, kein Überlaufraum), aber ein enger Prüfer nennt es eine
   fünfte zugelassene Art. Steht so nicht ausdrücklich im Dokument.
4. **`technik.md` nennt zum ersten Mal einen Riegel.** `Grep "riegel"` über die Datei gab
   vor diesem Lauf **null** Treffer; die vier vorhandenen Riegel leben nur in `werkzeuge/`.
   Ich halte das für richtig — die Durchsetzung ist eine Architekturentscheidung —, aber es
   ist ein neues Muster in dieser Vorgabe.

### Fährten

- **§29 zweite Prüfklausel: nicht geheilt, und der Grund ist neu.** Punkt 3 des
  Paketvermerks bot die Heilung an, *falls* dieselbe Wendung reicht. Sie reicht nicht:
  `1.464`/`9.024` treffen ausser in §29 auch **§30 Meldung 4** — also genau die Zeile, die
  den Mangel meldet. *Outside this section* liesse die Klausel um diese eine Zeile falsch.
  Wer §29 gehört, braucht eine Bereichsangabe, keine Wendung. Meldung 3 in Abschnitt 31.
- **`kern/test` hat 83 Treffer in 10 Dateien** (`werte_probe.cpp` 45, `schritt_probe.cpp`
  22) gegen „sechs" im alten Text. Steht nicht unter der Regel, prüft sie.
- **Zeilenangaben eines Pakets vom 2026-09-04 sind hier zwei Runden alt** — dritter Beleg
  in Folge. Ich habe keine einzige Nummer aus dem Paketrumpf benutzt.
- Ältere Fährten: `notizen/archiv/architekt-2026-09-08-4.md`.

