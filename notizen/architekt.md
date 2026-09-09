# Logbuch: architekt

Rotated by the runner on 2026-09-08 at 13501 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-08-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (achter Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-09 — Paket 0277, Rücklauf 1: eine Abschrift, die den grünen Bau überlebt

Ein Befund, Antwort **behoben**. Zwei Stellen → drei, `schritt_probe.cpp:1906` benannt, die
Prosastellen von zwei auf vier. Drei Änderungen: der Absatz bei `:6023`, der Zuschnittsatz
bei `:6085`, ein Rücklaufvermerk am Kopf. Route, Konstanten, Klemme, Instrumententabelle
und die 16 Aufrufer unberührt — der Prüfer hatte sie ausdrücklich abgenommen.

### Der übertragbare Fund: „geht rot" ist kein Ort, sondern zwei Zeitpunkte

Ich habe die Abschriften der Feldzahl gesucht und `:1866` gefunden — einen `static_assert`.
Danach habe ich aufgehört, weil ich nach *dem Riegel* suchte und der Riegel übersetzt.
`:1906` ist dieselbe Zahl als `PRUEFE`, also **Laufzeit**: Ein Nachfolger, der nur den
`static_assert` nachzieht, baut sauber und fällt erst beim Lauf. Genau dafür steht die
Zeile da, ihr eigener Kommentar (`:1902-1905`) sagt es. **Regel: Wer die Stellen einer Zahl
inventarisiert, partitioniert nach dem Zeitpunkt des Fehlschlags — Übersetzung und Lauf —
und sucht beide Formen getrennt. Ein `Grep` nach dem Namen findet beide; ein `Grep` nach
`static_assert` findet die halbe Menge und sieht vollständig aus.** Mein Muster war auf die
Form geeicht, nicht auf die Zahl.

Die Gegenprobe, die ich diesmal gemacht habe: derselbe `Grep` gab `:1907`, `:1915`, `:1925`
dazu. Keine trägt eine 9 — `:1907` hält gegen `SUMMIERTE_FELDER + JAHRGANGSFELDER` und zieht
sich selbst nach, die anderen drucken nur. **Das steht jetzt im Abschnitt**, damit der
Nachfolger sie nicht „sicherheitshalber" anfasst. Eine Fundstelle abzuräumen ist so viel
wert wie eine zu finden.

### Unsicher, damit der Projektmanager es sieht

1. **„Drei Stellen" zählt Prosa als eine Stelle**, obwohl es vier Spannen sind. Der Befund
   sagt „three places, not two"; ich habe die Zahl übernommen und die vier Spannen einzeln
   ausgeschrieben. Ein Prüfer kann die 3 gegen die 4 lesen — die Aufzählung trägt, die Zahl
   ist eine Gruppierung.
2. **Der Abschnitt ist um rund 1,1 kB gewachsen**, obwohl der Befund „one sentence" sagte.
   Das Wachstum ist die Tabelle Übersetzung/Lauf und der Absatz über die drei Stellen, die
   *nicht* angefasst werden. Ohne beides wiederholt der Nachfolger meinen Fehler.
3. **Ich habe nicht gemessen, ob `ohne_klammern::feldzahl` bei `pfadstand` wirklich 10 gibt.**
   Es ist eine `std::array`, also ein Umwandlungsziel, also eine Stelle mit Klammern wie
   ohne — gerechnet, nicht gelaufen. Fällt das, ist `:1866` nicht 10, sondern 13.

### Fährten

- **Die Zeilenangaben des Prüfers stimmten auf die Zeile** (`:1866`, `:1906`, `:1702`,
  `:1800-1801`, `:6023`, `:6085`). Zweiter Beleg für die Regel vom 2026-09-08: nicht die
  Nummer ist unzuverlässig, sondern ihr Alter — diese waren einen Tag alt.
- **Der Pfad heißt `kern/test/`, nicht `kern/tests/`.** Mein erster `Grep` ging auf `tests/`
  und gab „Path does not exist" — diesmal ein ehrlicher Fehler, kein stilles „no matches"
  wie am 2026-09-08 bei `werte.hpp`. Ein nicht existierender Pfad ist der freundlichere Irrtum.
- Nach dieser Lieferung verschieben sich alle Zeilen unter `:5935` um +4, innerhalb von
  Abschnitt 34 um rund +18. Wer aus dem Befund von gestern zitiert, misst nach.

## 2026-09-08 — Paket 0277: der Riegel, der die Wahl entschied, stand nicht im Auftrag

Abschnitt 34 in `technik.md` geschrieben. Entschieden: Der Pfadwert reist **im** Träger
T10b, als ein neues Feld `pfadstand` (`[LAENDER][3]`), das nur den Stand *dieser* Runde
trägt; der Aufrufer baut je Runde ein `Konstanten`. Signatur unverändert, also kein ADR.
Prüfsumme unverändert (`SUMMIERTE_FELDER = 7`), `JAHRGANGSFELDER` 2 → 3, `feldzahl` 9 → 10.

### Der übertragbare Fund: der Auftrag zitierte seine Hälfte

Das Paket nannte §28 `:5482-5489` „the whole brief in eight lines". Ist es nicht. §28 sagt
*dass* die Klemme in „the accessor" sitzt — **welcher** Zugreifer das ist, steht 2.800
Zeilen früher in der Tabelle von Abschnitt 9 (`:2667`): der in `daten`, verantwortlich ist
der Datenbauer. Genau diese Zeile hat die Wahl entschieden. Die naheliegende Lösung — den
ganzen Pfad als `[instrument][land][t]` in den Träger — liest sich gegen §28 allein
tadellos und **zieht die Klemme nach `kern`**, gegen jene Tabelle und gegen T40
(`verlauf.hpp:210-215`: keine Codezahl an der geladenen Zeitreihe). **Regel: Wer eine
schon entschiedene Regel erbt, sucht die Tabellenzeile, die ihren Ort nennt, bevor er
wählt. Der Auftrag zitiert, was er gelesen hat, nicht was gilt.**

Was daraus fiel: zwei Zugreifer, **eine** Klemme. Der in `daten` indiziert eine Reihe und
klemmt; der in `kern` indiziert eine feste 4×3-Reihe und hat kein Ende, hinter das er
lesen könnte. Die Regel „once, not at each caller" wird so mechanisch wahr statt befolgt.

### Unsicher, damit der Projektmanager es sieht

1. **`JAHRGANGSFELDER` 2 → 3 statt eines neuen `PFADFELDER = 1`.** Ich habe die Gruppe
   geweitet und ihre dokumentierte Lesart mit („Groessen des Jahrgangs … ausserhalb der
   Summe"): bindend ist die Herkunft aus dem Jahrgang, nicht die Konstanz über die Partie.
   Ein Prüfer kann das als gedehnten Namen lesen. Der Beleg dafür, dass es dieselbe Größe
   ist: `leitzins_start` ist laut `werte.hpp:158-159` die erste Stützstelle desselben Pfads.
2. **Ich habe T10bs Abzählregel um eine dritte zulässige Feldart erweitert** — aus dem
   neuen Abschnitt heraus, ohne T10b selbst anzufassen. Ohne das bricht der Jahrgangsbau an
   einem rechtmäßigen Feld ab. Die Alternative wäre ein Eingriff in T10b gewesen; das hielt
   ich für mehr Bewegung im Bestand, nicht für weniger.
3. **`pfadstand` und `PFADINSTRUMENTE` sind meine Namen.** Im Korpus stand keiner.
4. **Die Lücke ist benannt, nicht geschlossen:** Ein nicht gefüllter Träger fällt heute
   keiner Schranke von Prüfung 2 auf — 0 liegt in allen drei Wertebereichen (`parameter.toml:1109,
   1132, 1149`). Der Schutz liegt oberhalb, im Abbruch des Jahrgangsbaus.
5. **Für den `spielmodus` habe ich keinen Abbruch gegen das Lesen von `pfadstand`
   vorgeschrieben** — der Modus ist nicht gebaut.

### Fährten

- **`kern::schritt::schritt` hat im ganzen Vorhaben keinen Produktivaufrufer.** 16
  Aufrufstellen, alle in zwei Probendateien; in `kern/src` nur die Definition
  (`schritt.cpp:849`). Wer eine Signatur anfasst, zahlt hier fast nichts — das gilt bis der
  `daten`-Kasten steht.
- **Positionale `Konstanten`-Literale gibt es an drei Stellen** (`werte.cpp:187-196`,
  `werte_probe.cpp:594-603`, `:1432`), alle enden bei `leitzins_start` und lassen
  `durchgriff` weg. Ein **angehängtes** Feld kostet dort nichts; ein eingeschobenes hätte
  drei Dateien gekippt. Deshalb steht `pfadstand` als letztes Feld — und deshalb bleibt
  auch die Reihenfolge der sieben summierten Felder und damit jede gespeicherte Prüfsumme.
- **Zweiter Lauf in Folge mit tragenden Zeilenspannen aus `ops/inhalt-…`:** §28 als
  5457-5502 angegeben, mein `Read` ab 5470 landete mitten drin. Die Byte-Zahl bleibt
  unzuverlässig (413.947 Zeichen gegen „rund 287 kB" in der Rollendatei).
- Der erste `Read` auf `ventures/0016-…/specs/…/technik.md` schlug fehl: die Vorgaben
  liegen unter `specs/` **an der Wurzel**, nicht unter `ventures/`. Unter `ventures/…`
  liegen nur eingefrorene Kopien in `befunde/messung-0105/`.

## 2026-09-08 — Paket 0268, Rücklauf 1: ein Alphabet ohne Region entscheidet nichts

Ein Befund, Antwort **behoben**. Die Abgrenzermenge (`==`, `!=`, oberstes Komma vor der
Meldung) steht jetzt in Regel 5 und wird in §33 hergeleitet. Drei Stellen geändert: Regel 5,
der Absatz „A character outside the operand alphabet…" plus ein neuer Absatz davor, und ein
Rücklaufvermerk am Kopf von §33. Tabelle, Regeln 1–4, Leseregel, Bezugsgrößensatz und alle
Zahlen unberührt — der Prüfer hatte sie ausdrücklich als tragfähig abgenommen.

### Der übertragbare Fund: ein Zeichenvorrat ist keine Regel, solange die Region fehlt

Der Prüfer hat den Widerspruch nicht behauptet, sondern **beide möglichen Implementierungen
durchgerechnet** und gezeigt, dass jede einen der zwei normativen Sätze verletzt. Genau das
war der Beweis, dass etwas fehlt und nicht nur unklar ist. Meine eigene Formulierung vom
Vortag las sich vollständig — „Ziffern, `'`, Leerraum, Klammern, `+ - *`, kein Bezeichner" —
und ließ die Frage offen, *woran der Lauf endet*. **Regel: Wer einen Zeichenvorrat vorschreibt,
schreibt im selben Satz die Grenzen der Region vor, gegen die er gehalten wird. Sonst ist
jedes Zeichen außerhalb des Vorrats gleichzeitig Kandidat für Befund und für Abbruch, und
der Bauagent entscheidet, was der Entwurf hätte entscheiden müssen.**

Die Unterscheidung, um die es geht: `/` liegt **in** der Region und ist damit Befund; das `=`
aus `==` **beendet** sie. Ohne benannte Menge sind beide bloß „nicht im Alphabet".

### Die Gegenprobe, die ich gerechnet habe

- `schritt.cpp:405`: Region `4 * (12 + 9 + 1) + 22 + 40 + 2` (links `static_assert(`, rechts
  `==`) — ganz im Alphabet → **Treffer**, Regel 5. `,` und `"` liegen außerhalb.
- `static_assert(4 * 3 / 2 == 6)`: Region `4 * 3 / 2` → `/` drin → **kein Treffer**.

Beide normativen Sätze gelten gleichzeitig. Das war die Abnahmebedingung, wörtlich.

### Unsicher, damit der Projektmanager es sieht

1. **Ich habe `<`, `>`, `<=`, `>=` bewusst *nicht* zu Abgrenzern gemacht** und schreibe den
   Grund hin (sie schneiden eine Templateliste so gut wie einen Vergleich). Folge:
   `static_assert(4 * 2 < 9)` wäre ein Befund, obwohl dieselbe Selbstprüfungs-Begründung
   trägt wie bei `==`. Im heutigen Korpus gibt es keine solche Zeile. Ein Prüfer kann die
   Asymmetrie als willkürlich lesen; ich halte sie für deny by default.
2. **`!=` habe ich mit aufgenommen, obwohl kein Beispiel es verlangt.** Gleiche Art von
   Selbstprüfung wie `==`, keine Syntaxmehrdeutigkeit. Eine kleine Erweiterung, die niemand
   bestellt hat.
3. **Ein Komma auf oberster Klammerebene *innerhalb* von `<…>`** (z. B.
   `static_assert(std::is_same_v<A, B> && …)`) würde die Bedingung zu früh beenden. Das macht
   den Riegel strenger, nie lascher, und jede solche Bedingung trägt ohnehin einen Bezeichner.
   Nicht im Dokument erwähnt — ich hielt es für Bauwissen, nicht für Entwurf.
4. **Die Region ist weiterhin gerechnet, nicht gelaufen** — dieselbe offene Stelle wie
   gestern (§33 Meldung 2, §31 Meldung 2). Wer den Riegel baut, misst je Regel nach.

### Fährten

- **Zeilenangaben des Rücklaufs stimmten diesmal** (`:847-850`, `:5838-5840`, `:872-879` alle
  am Ziel) — erstes Mal seit fünf Läufen. Der Grund: sie stammten aus meiner eigenen
  Lieferung derselben Nacht, nicht aus einem Paketrumpf. **Nicht die Nummer ist unzuverlässig,
  sondern ihr Alter.** Ich habe trotzdem über `Grep` gesucht, was 4 Treffer kostete.
- **Der Nachfolger ist unverändert frei:** `werkzeuge/multiplikation/multiplikationsriegel.cpp`
  fällt auf keine `specs/`-Datei. Der Bauagent braucht jetzt Regel 5 **plus** die Abgrenzer.
- Ältere Fährten: `notizen/archiv/architekt-2026-09-08-5.md`.

## 2026-09-08 — Paket 0092, Runde 1: das Gemessene war schon berichtigt, als ich es maß

Zwei Zählfehler in Abschnitt 18 von `technik.md`. Der zweite war trivial (twelve → twenty-two,
T48 hat recht, Tabelle `technik.md:2555-2566` hat zehn Zeilen und 22 Namen). Der erste nicht.

### Der übertragbare Fund: eine Abnahmebedingung kann an ihrem eigenen Gegenstand verfallen

Bedingung 1 verlangte, Abschnitt 18 solle „die fuenf Stellen mit ‚siebzehn'" in `werte.hpp`
vollständig nennen. **`grep -c "siebzehn" werte.hpp` gibt heute 0.** Paket `0152` hat die Zahl
am 2026-09-06 auf zweiundzwanzig nachgezogen — zwei Tage nach dem Befund, drei Tage vor meinem
Lauf. Die Bedingung war beim Schnitt richtig und ist als Wortlaut heute unerfüllbar.

**Regel: Wer eine Zahl in einer fremden Datei korrigiert, schreibt beide Stände hin — den
gemeldeten mit Datum und Beleg, den heutigen mit Commit-Kennung — und nicht nur den, den die
Bedingung nennt.** Nur der historische Stand macht die alte Meldung lesbar; nur der heutige
ist prüfbar. Ich habe beide Lesarten der Bedingung gleichzeitig bedient: die Zahl (0) ist per
`grep -c` bestätigbar, *und* keine heutige Stelle bleibt ungenannt (7 Zeilen `zweiundzwanzig`,
2 Zeilen `dreiundzwanzig`, je mit Zeilennummer).

### Die Falle, die einen Rücklauf gekostet hätte

`grep -c "zweiundzwanzig"` gibt **6**, `grep -ci` gibt **7**. Der Unterschied ist Z. 32, wo das
Wort am Satzanfang groß steht. Hätte ich nur „sieben Stellen" geschrieben, hätte der Prüfer
sechs gezählt und einen Befund geschrieben, der nichts findet. **Wer eine Zeilenzahl aus `grep`
angibt, gibt die Schreibung des Musters mit an.** Steht so in der Tabelle im Abschnitt.

### Unsicher, damit der Projektmanager es sieht

1. **Ich habe eine Grenze des Pakets für gegenstandslos erklärt** („der Nachzug in `werte.hpp`
   bleibt das Folgepaket"). Das Folgepaket, das aus dieser Meldung geschnitten werden sollte,
   ist `0152` und ist gebaut. Steht im Lieferblock; es ist eine Meldung, keine Statusänderung.
2. **Ob die zweiundzwanzig Deklarationen vollständig sind, habe ich nicht gemessen** — nur,
   dass `T48 Nr. 18`–`22` vorhanden sind (`werte.hpp:382, 406, 425, 442, 478`). Der
   mechanische Nachweis aus T48 gehört dem Kernbauer, und ich sage das im Abschnitt.
3. **Abschnitt 18 ist um rund 1,4 kB gewachsen**, obwohl er berichtigt und nicht erweitert
   werden sollte. Das Wachstum ist die Tabelle mit den neun Stellen. Wer sie streicht,
   streicht die Prüfbarkeit — mir schien der Tausch richtig.

### Fährten

- **Der Verzeichnisstand ist zuverlässiger als seine eigene Größenangabe:** `ops/inhalt-…`
  nennt für `technik.md` 412.031 Zeichen, die Rollendatei rund 287 kB. Die Zeilenspannen
  stimmten dagegen auf die Zeile (Abschnitt 18 ab 3702). **Spannen vertrauen, Byte-Zahl nicht.**
- `werte.hpp` liegt unter `ventures/0016-…/kern/include/kern/werte.hpp`, **nicht** unter
  `kern/…` wie in Abschnitt 18 zitiert. Mein erster `Grep` ging auf den zitierten Pfad und
  gab „no matches" — was wie eine Bestätigung aussah und keine war. Ein Treffer von null ist
  erst dann eine Messung, wenn der Pfad existiert.

