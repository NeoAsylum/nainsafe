---
typ: pruefung
paket: 0002-fondsbewertung-definieren
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle sechs Abnahmebedingungen einzeln und mechanisch -- die siebzehn Kopfdeklarationen gegen die Tabelle aus T48, die drei Mustervergleiche aus T50, die T47-Zahlenprobe von Hand nachgerechnet und im Bau gemessen, jede der siebzehn Formeln Zeichen fuer Zeichen gegen T47/T48, und 23 Sabotagen am fertigen Modul in beiden Bauprofilen.
befunde: 3
---

# Pruefung `0002-fondsbewertung-definieren`

Geprueft wurde der Stand `ceebee3` (`kernbauer: 0002-fondsbewertung-definieren`), aus
`git archive HEAD` in einen Baum ausserhalb des Repos exportiert und dort uebersetzt --
nicht aus dem Arbeitsbaum, in dem parallele Laeufe uncommittete Zwischenstaende
hinterlassen.

Uebersetzer g++ 15.2.0, CMake 4.2.3. **Beide Bauprofile**, so wie der Runner sie
konfiguriert:

| Profil | Schalter | Ergebnis |
|---|---|---|
| `Debug` | `-fwrapv -fno-fast-math` | 13 von 13 Proben bestanden |
| `RelWithDebInfo` | dazu `-fsanitize=undefined,address -fno-sanitize-recover=all` | 13 von 13 Proben bestanden |

Der `belegstellen_riegel` ist darin enthalten; er faellt zunaechst aus, wenn man nur
`ventures/` exportiert, und besteht nach dem Nachexportieren von `specs/`. Das ist eine
Eigenschaft meines Aufbaus und kein Befund am Paket.

## Die sechs Abnahmebedingungen, einzeln

**1. Genau die siebzehn Namen aus T48 im Kopf.** Mustervergleich ueber
`kern/include/kern/werte.hpp` nach Deklarationszeilen: siebzehn Treffer, Name fuer Name
und in der Reihenfolge der Tabelle aus T48 -- `wert`, `korbwert`, `anleihewert`,
`waehrungswert`, `markt`, `stufenwert`, `marktkorb`, `korbbestand`, `bip`, `schuld`,
`handelsvolumen`, `anleihekurs`, `landespreis`, `fondsanteil`, `positionswert`,
`beteiligung_wert`, `fondsvermoegen`. Keiner mehr, keiner weniger. **Erfuellt.**

Daneben steht `struct Konstanten`. Ich habe geprueft, ob das eine achtzehnte Groesse
ist, und komme zum selben Ergebnis wie der Bauagent, aber aus dem Wortlaut der Bedingung
statt aus der Zweckmaessigkeit: Die Bedingung nennt ihre eigene mechanische Form, und
das ist `grep -n 'pub fn' werte.rs` -- sie zaehlt **Funktionen**. Ein Datentraeger ist
keine. Kein Befund.

**2. `tsd_in_cent` und die Lobbyumrechnungen privat, mit genau den Aufruforten aus T50.**
Zur Ortsbindung: `tsd_in_cent` wird im rechnenden Code an genau zwei Stellen gerufen --
`werte.cpp:464` (aeusserster Aufruf des Positionswerts) und `werte.cpp:478` (aeusserster
Aufruf des Beteiligungswerts). Das sind die zwei aus T50. Keine Deklaration im Kopf.
**Erfuellt.**

Zum Mustervergleich: **nicht erfuellt, und nicht vom Bauagenten heilbar** -- siehe
Befund 2.

**3. `cent_in_tsd` gibt es nicht.** `grep -rn 'cent_in_tsd' kern/` -> null Treffer.
**Erfuellt.**

**4. Die Zahlenprobe aus T47 mit ausgeschriebenem Erwartungswert.** Von Hand:

```
korbwert          = 21.000.000.000 · 10.000 / 10.000   = 21.000.000.000  Tausend USD
innen             = 21.000.000.000 · 20 / 10.000       =      42.000.000  Tausend USD
nach Abschlag 0   = 42.000.000 · 10.000 / 10.000       =      42.000.000  Tausend USD
tsd_in_cent       = 42.000.000 · 100.000               = 4.200.000.000.000 US-Cent
```

Dieselbe Zahl steht ausgeschrieben in `werte_probe.cpp:203`, und der Lauf bestaetigt
sie. Der innere Wert entsteht in der Probe ueber `festkomma::mal_geteilt` und nicht
durch Abschreiben aus dem Modul. Die Gegenprobe mit Abschlag 2.500 (drei Viertel,
3.150.000.000.000) habe ich mitgerechnet und sie stimmt. **Erfuellt.**

**5. Jede der siebzehn Formeln Zeichen fuer Zeichen gegen T47/T48.** Einzeln gelesen und
gegengelegt; alle siebzehn stimmen, einschliesslich der vier, die T48 erst nachtraegt
(`bip`, `handelsvolumen`, `anleihekurs`, `korbbestand`), der Gegenuebertabelle als
benannter Tabelle statt als Indexrechnung, der Indexordnung aus T9 in beiden Summen und
des einmal je Aufruf gerechneten Korbvorrats. **Erfuellt.**

Eine Stelle weicht in der Schreibweise ab und ist trotzdem kein Befund: T48 schreibt
`anleihekurs = teile_gerundet(10.000 · (leitzins_start + aufschlag), leitzins +
aufschlag)`, gebaut ist `mal_geteilt(10'000, zaehlerzins, nenner)`. Das ist dieselbe
Rechnung mit derselben Rundungsregel -- beide Wege enden in
`intern::runde_von_null_weg` --, und die woertliche Form muesste das Produkt zuerst
blank auf `i64` bilden, was T7 Massnahme 4.3 gerade verbietet. T48 zieht diese
Umformung fuer `fonds.marktanteil` selbst und mit derselben Begruendung.

**6. Kein Gleitkomma, keine Fremdabhaengigkeit, keine Division ausser ueber
`festkomma`.** `kern/src/werte.cpp` bindet `kern/sperre.hpp` als letzte Zeile des
Include-Blocks ein; `#pragma GCC poison float double` macht Gleitkomma dahinter zu einem
Vorverarbeiterfehler. Mustervergleich ueber die Datei nach `float`, `double`,
`unordered_`, `chrono`, `rand(`, `random_device`, `reinterpret_cast`, `uintptr_t`,
`std::map`, `std::set`: null Treffer. Eingebunden sind `<array>`, `<cstddef>`,
`<cstdint>` und vier Kernkoepfe -- nichts Fremdes. Ein `/`-Operator kommt in der Datei
ausserhalb von Pfaden und Prosa nicht vor. **Erfuellt.**

## Die vier Fragen meiner Rolle

**Ist es deterministisch?** Ja, und zwar strukturell statt gemessen. Gleitkomma ist
unuebersetzbar (Sperre oben). Alle vier Schleifen laufen ueber `std::array` in fester
Indexordnung -- die zwanzig Steckplaetze, die zwoelf Koerbe, die drei bzw. zwei Sektoren,
die vier Gegenueber je Gebiet; es gibt keinen streuenden Behaelter, keinen Zufallsstrom,
keine Zeit- und keine Adressabfrage. Die beiden benannten Tabellen tragen je einen
Gegenweg, der beim **Uebersetzen** laeuft: `plaetze_stimmen()` rechnet jede Zeile auf
ihre eigene Platznummer zurueck, `gegenueber_stimmt()` prueft, dass jede Zeile die vier
anderen Gebiete aufsteigend und ohne das eigene enthaelt. Beide Bauprofile liefern
dieselben Probenergebnisse; damit ist auch Optimierungsabhaengigkeit ausgeschlossen.

**Sind die Rueckkopplungen begrenzt?** In diesem Modul gibt es keine Schleife, in der
Erfolg mehr Erfolg erzeugt -- es rechnet Funktionen des Zustands ohne Zustandsaenderung.
Die zwei Schranken, die T47 dafuer verlangt, sind beide gebaut und beide gemessen: die
Invariante `wechselkurs >= 1` in `wert` (Mutation M10 unten) und der Ueberlaufwaechter am
Skalenuebergang (M15). Jede Summe laeuft ueber gepruefte Strichrechnung
(`__builtin_add_overflow`), nicht ueber blankes `+`.

**Ist die Zustandsausgabe vollstaendig?** Nicht Gegenstand dieses Pakets -- die drei
Ebenen sind Paket `0010-zustandsausgabe-drei-ebenen`, das auf dieses hier wartet. Ich
habe geprueft, was hier davon abhaengt: `fondsvermoegen` ist keine Zustandsadresse (T47
Punkt 4) und darf keine sein; das ist eingehalten, die 310 aus T15 aendern sich nicht.

**Halten die Zahlen die Raender?** Ja. `tsd_in_cent` ist die einzige Stelle, an der ein
`i64` ueberlaufen kann, und sie laeuft ueber `festkomma::mal` mit 128-Bit-Zwischenwert
und hartem Waechter. Von Hand nachgerechnet und im Lauf bestaetigt: 9 · 10^12 Tausend USD
gehen als 900.000.000.000.000.000 Cent durch, 93 · 10^12 brechen ab -- die Schranke aus
T47 liegt bei 9,2 · 10^13, und beide Seiten liegen belegt daneben. `betrag()` bricht bei
`I64_MIN` ab, statt still eine negative Zahl zu liefern. Die Division sieht nie einen
Nenner null: `mal_geteilt` bricht nach T6 ab, und `wert` faengt den gefaehrlicheren
negativen Nenner davor.

## Der Sabotagelauf

Dreiundzwanzig Mutationen, jede einzeln in einen frischen Baum eingespielt, uebersetzt
und gegen alle zwoelf Kernproben gefahren. Der Vorlauf ohne Mutation ist gruen, die
Kontrollmutation ohne Wirkung (M17) bleibt gruen -- ohne dieses zweite Vorzeichen belegte
der Lauf nur, dass irgendetwas rot wird.

**Neunzehn wurden rot**, darunter jede Vorgabe, die 0002 selbst als „woertlich zu
nehmen" fuehrt: Rundungsreihenfolge (M8), Abbruch bei `stufen = 0` **vor** `markt(p)`
(M9, Abbruch statt Zahl), Wechselkursschranke gegen den negativen Nenner (M10),
Ueberlaufwaechter (M15), Landespreis aus der Vorrunde (M16), beide Handelsrichtungen
(M7), Betrag statt Vorzeichen im Fondsanteil (M18), Korbvorrat (M12, schon in der
Uebersetzung), Hebel als Abzug (M11), Anteilsskala 10.000 (M22), Anleihekurs (M14),
`bip` ueber drei Sektoren (M13), Quote statt Betrag in `schuld` (M6), Kurs gegen
Wechselkurs in `wert` (M5), Korbbestand mit Fondsanteil (M21), Ausstiegsabschlag (M20).

**Vier blieben gruen.** Sie sind Befund 1.

## Befund 1 -- vier Vorgaben, die sich verletzen lassen, ohne dass eine Probe rot wird

*Schwere: mittel. Kein Verstoss gegen eine Abnahmebedingung -- der Code ist an allen
vier Stellen richtig. Was fehlt, ist der Riegel dahinter.*

| Mutation | verletzte Vorgabe | Lauf |
|---|---|---|
| Skalengrenze nach innen gezogen | T47/T50: „am aeussersten Aufruf" | gruen |
| `positionswert` nimmt den Betrag der Stufenzahl | T48 Nr. 15 gegen Nr. 14 | gruen |
| `marktkorb` zaehlt die Waehrungen mit | T33 Punkt 1 | gruen |
| `waehrungswert` nimmt den Wechselkurs statt 10.000 | T48 Nr. 4 | gruen |

**Wie man den schwersten Fall erzeugt, Schritt fuer Schritt:**

1. In `kern/src/werte.cpp:464` `mal(stufen, je_stufe)` durch
   `mal(betrag(stufen), je_stufe)` ersetzen -- eine Zeile, sonst nichts.
2. Uebersetzen und `ctest` fahren: **alle dreizehn Proben bleiben gruen.**
3. Auf einem Zustand mit Kapitalstock 1.000.000, `stufenweite` 250 und `stufen = -4`
   messen. Gemessen mit einem `fprintf` in einer Kopie der Probe:

```
unveraendert:  stufenwert=25000  positionswert=-10000000000
mit Mutation:  stufenwert=25000  positionswert=+10000000000
```

Ein Short von vier Stufen zaehlt danach als Long. `fondsvermoegen` meldet einen Fonds um
2 · 10^10 US-Cent zu reich, und Todesart 1 (`fondsvermoegen <= 0`) greift bei einem
Fonds, der sich mit Shorts ruiniert, nie.

**Warum keine vorhandene Pruefung es sieht** -- das ist der uebertragbare Teil:
`probe_fondsvermoegen_zweiter_weg` belegt Steckplaetze durchaus mit negativen
Stufenzahlen, haelt aber den gebuendelten Weg gegen den einzelnen, und **beide rufen
dieselbe Funktion**. Ein zweiter Rechenweg, der die gepruefte Funktion enthaelt, prueft
alles ausser ihr selbst. Die anderen drei sind derselbe Fehlertyp in mildere Form: Die
Grundbelegung der Proben laesst den Wechselkurs auf 10.000 und die Handelsstroeme auf
null -- genau die Werte, bei denen die richtige und die falsche Form dieselbe Zahl
liefern.

Bei der Skalengrenze kommt hinzu, dass die T47-Zahlenprobe sie nicht faengen **kann**:
`21.000.000.000 · 20 / 10.000` geht restlos auf, und wo nichts gerundet wird, ist es
gleichgueltig, wo der Faktor 100.000 steht. Von Hand, mit Korb 3 und Anteil 3.333:
verbindlich 100.000 Cent, mit der Mutation 99.990 Cent.

**Ich habe die fehlende Pruefung fuer den schwersten Fall einmal gebaut, bevor ich sie
vorschlage**, und in beide Richtungen gefahren: am unveraenderten Modul gruen, gegen die
Mutation rot, mit den beiden Messwerten oben. Der Vorschlag ist
`aufgaben/0088-werte-probe-vier-unbelegte-vorgaben.md`, `rolle: testentwickler`,
`status: vorschlag`, Dateiliste allein `kern/test/werte_probe.cpp`.

**Zur Nummer, weil sie kurz doppelt war:** Beim Lesen der hoechsten Nummer war 0087 die
letzte, nach dem Schreiben stand `0088-kopfkommentar-herkunft-0007-statt-0004.md`
daneben -- ein paralleler Lauf war dazwischen. Er ist inzwischen selbst auf `0089`
ausgewichen, **0088 ist eindeutig**. Nichts zu tun; ich notiere es, weil es nach 0079 der
zweite Fall ist und die Regel „hoechste Nummer vorher und nachher lesen" gegen den
Zufall hilft, nicht gegen die gleichzeitige Vergabe. Umbenennen haette dieser Lauf nicht
gekonnt (`mv`, `git mv`, `os.rename` alle abgelehnt).

## Befund 2 -- Abnahmebedingung 2 ist im Wortlaut nicht erfuellt, und nicht vom Bauagenten

*Schwere: gering. Geht an den Projektmanager, nicht an den Kernbauer.*

Bedingung 2 verlangt: `grep -rn 'tsd_in_cent\|lobbypunkte_aus' kern/` liefert Treffer
**nur in dieser Datei**. Ausgefuehrt liefert er dreizehn Treffer, drei davon ausserhalb:

```
kern/test/schranken_probe.cpp:587   /// Die Ueberlaufschranke von `tsd_in_cent` (T47), als Zahl: 9,2 * 10^13.
kern/test/schranken_probe.cpp:646   // `tsd_in_cent` -- an einer Stelle, an der niemand die Ursache sucht. Hier
kern/include/kern/festkomma.hpp:185 /// also still. `tsd_in_cent` (T50) vervielfacht blank mit 100.000 und hat weder
```

**Alle drei sind Prosa in einem Kommentar, keiner ist ein Aufruf.** Die Sache, die T50
sichern will -- die Skalengrenze wird nur in diesem einen Modul ueberquert --, ist also
gehalten; verletzt ist nur der Mustervergleich, mit dem sie nachgewiesen wird.

Beide Dateien stehen **nicht** in der `dateien`-Liste von 0002, stammen aus 0052 und
0077 und sind aelter als dieses Paket. Der Bauagent haette die Bedingung nur erfuellen
koennen, indem er ausserhalb seines Pakets schreibt. Ich melde das deshalb hier und
mache daraus keinen Ruecklauf und keine gesenkte Bedingung.

**Was ich empfehle, ohne es zu einem Paket zu machen:** T50 (und mit ihm Bedingung 2
kuenftiger Pakete) sollte auf Aufrufe zielen statt auf Namen -- `tsd_in_cent(` mit
oeffnender Klammer, oder ausdruecklich „ausserhalb von Kommentaren". Kein Paket, weil
das eine Aenderung an `specs/.../technik.md` waere und dort bereits vier
Architektenpakete warten (0026, 0064, 0068, 0074); ob ein fuenftes den Vorrang wert ist,
entscheidet der Geschaeftsfuehrer und nicht ich. Der Anlass ist real und nicht
kosmetisch: Ein Riegel, der drei Fehlalarme wirft, wird abgeschaltet oder ignoriert --
und wuerde er wie der `belegstellen_riegel` in die Werkzeugkette gezogen, waere der Bau
am ersten Tag rot.

## Befund 3 -- `marktkorb(m, k)` ist mit den heutigen Schnittstellen fuer T33 Punkt 3 nicht aufrufbar

*Schwere: gering, und keine Verletzung einer Abnahmebedingung. Beobachtung fuer den, der
Schritt 6 baut.*

T33 Punkt 3 verlangt `W_neu = marktkorb(alt, neu)` -- „Mengen ueber `lies_alt` und Kurse
ueber `lies_neu`", also mitten in der Runde. Gebaut ist
`marktkorb(const Zustand& mengen, const Zustand& kurse, const Konstanten&)`, und das
entspricht T48 Nr. 7 Zeichen fuer Zeichen; die Typen nennt keine Vorgabe, also ist die
Wahl nach meinen eigenen Grenzen die des Bauagenten und kein Befund.

Sie laesst sich trotzdem nicht bedienen: Der `Schreiber` haelt `alt_` und `neu_` privat
und gibt nach aussen nur `lies_alt`, `lies_neu`, `ist_geschrieben` und `rundenende()`.
`rundenende()` prueft nach T38 vorher, dass **jede** Adresse der Sollmaske geschrieben
ist -- in Schritt 6, bevor `markt.rendite` und `markt.wert` gesetzt sind, ist sie das
gerade nicht. Es gibt damit keinen Weg zu einem `Zustand`, der den laufenden Stand
traegt. Punkt 2 (`marktkorb(start, start)` im Jahrgangsbau) und Punkt 4
(`marktkorb(neu, neu)` am Rundenende) sind dagegen bedienbar.

Die Heilung liegt an einer von zwei Stellen -- `marktkorb` nimmt den `Schreiber`, so wie
`landespreis` es aus genau diesem Grund tut, oder der `Schreiber` bekommt eine
Lesesicht --, und welche richtig ist, haengt daran, was Schritt 6 sonst noch braucht.
Ich mache daraus kein Paket, weil ich sonst die Entscheidung raten wuerde, statt sie zu
belegen.

## Wonach ich gesucht und nichts gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Ein zweiter Rechenweg fuer dieselbe Groesse**, der auseinanderlaufen kann. Es gibt
  keinen: `markt`, `stufenwert`, `positionswert` und `beteiligung_wert` fuehren alle
  ueber die `*_aus`-Fassungen mit dem Korbvorrat als Argument, und `korbwert`
  beziehungsweise `anleihewert` sind die Ein-Zustand-Faelle von `korbwert_zwei` und
  `anleihewert_zwei`. Eine Verdopplung, die nach zwei Paketen auseinanderlaeuft, ist
  nirgends angelegt.
- **Eine Zahl aus dem Testhelfer statt aus dem Kern.** Der innere Wert der T47-Probe
  entsteht ueber `festkomma::mal_geteilt` und damit unabhaengig vom geprueften Modul;
  keine Erwartung schreibt eine Zahl ab, die das Modul selbst geliefert hat.
- **Eine Behauptung in einem Kommentar, die einen Fall fuer ausgeschlossen erklaert.**
  Vier gefunden und einzeln hergestellt: der Nenner des Anleihekurses („nach T51 nie null
  und nie negativ" -- er bricht ab, wenn er es doch ist, Probe Zeile 512), die Restwelt
  ohne Politikpfad (Zeile 515/516), der Steckplatz ausserhalb der zwanzig (Zeile 634),
  der Betrag von `I64_MIN`. Alle vier brechen wirklich ab.
- **Eine Aufzaehlung mit einem fehlenden Glied.** Die drei Steckplatzarten, die drei
  Sektoren, die zwei handelbaren, die vier Gegenueber, die zwoelf Koerbe, die vier
  Anleihen, die zwanzig Plaetze -- alle sieben Listen abgezaehlt, jede vollstaendig, und
  drei davon haben einen `static_assert` als eigenen Gegenweg.
- **Ein Werkzeug ohne Aufrufer.** `plus`, `minus` und `betrag` sind privat und werden
  benutzt; die beiden Lobbyumrechnungen haben heute nur ihre Zahlenproben als Aufrufer,
  und das ist in `werte.cpp:33-35` ausgeschrieben begruendet -- ihre Aufruforte nach T50
  (Aktion 3, Gegenkraft 5) sind noch nicht gebaut, und ein Uebergang, der erst mit seinem
  ersten Aufrufer entstuende, waere genau der Fall, den T50 ausschliesst.
- **Der Commit-Betreff.** Diesmal stimmt er: `ceebee3` traegt die drei Dateien des
  Pakets. Gesucht habe ich ueber `git log -- <datei>`, nicht ueber den Betreff.
