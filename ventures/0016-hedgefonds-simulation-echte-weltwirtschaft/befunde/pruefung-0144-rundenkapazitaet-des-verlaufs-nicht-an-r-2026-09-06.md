---
typ: pruefung
paket: 0144-rundenkapazitaet-des-verlaufs-nicht-an-r
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Jede der vier Bedingungen einzeln mechanisch gefahren -- die 26-Runden-Partie im selbst gebauten Baum samt rotem Kontrollbaum, die Schranke zweiseitig, die Zusicherung ueber vier Mutanten und drei Kontrollen mit der alten Fassung, beide Profile auf beiden Bauwegen gegen einen selbst hergestellten Vorherstand.
befunde: 1
---

# Der geprueffte Stand, und wo die Aenderung wirklich liegt

Gemessen am Arbeitsbaum in dem Zustand, den Commit `e0682a1` hinterlassen hat
("kernbauer: 0151-werte-die-drei-hubgroessen"). Die drei Paketdateien sind dort
unveraendert gegenueber der Ablage; ihre Pruefsummen zu Beginn und am Ende dieses
Laufs:

| Datei | md5 |
|---|---|
| `kern/include/kern/verlauf.hpp` | `b8adcc310ef3935f632565939c1703c2` |
| `kern/src/verlauf.cpp` | `971f1591392c39f31e30f83850f3cf4b` |
| `kern/test/verlauf_probe.cpp` | `7d600222bd09eb8e7512eb874f215648` |

**Der Commit mit dem Betreff des Pakets traegt die Aenderung nicht.** `e34ab65`
("kernbauer: 0144-...") aendert an `verlauf.hpp` genau eine Kommentarzeile. Die Arbeit
dieses Pakets steckt in zwei fremd betitelten Commits: `41fbcd3` ("datenbauer:
0099-...") traegt `verlauf.hpp` und `verlauf.cpp`, `4ff788d` ("architekt: 0116-...")
traegt `verlauf_probe.cpp`. Ich habe fuer beide den Diff gegen den Elternstand gelesen:
er enthaelt je ausschliesslich Stellen dieses Pakets, keine fremden. Damit sind
`41fbcd3~1` und `4ff788d~1` die gueltigen Vorherfassungen, und die Kontrollbaeume unten
stehen auf belegtem Grund.

Alles Folgende ist in einem eigenen Baum gemessen, ausgepackt aus
`git archive HEAD ventures/0016-... specs decisions`, unter `befunde/bau-pruefung-0144/`.
`specs` und `decisions` sind mit ausgepackt, sonst faellt der Belegstellenriegel beim
Konfigurieren aus.

# Bedingung 1 -- die Partie ueber sechsundzwanzig Runden

**Erfuellt.** Der Kernbau mit dem Sanitizer-Profil, die Probe verlauf_probe unter
ctest ausfuehrlich gefahren. Ausgabe im Wortlaut, gekuerzt um die Runden 2 bis 25, die
zeichengleich denselben Satz tragen:

```
Groessen: sizeof(Verlauf) 451784, sizeof(Kette) 17368, RUNDEN_KAPAZITAET 26,
          PARTIELAENGE_HOECHSTENS 26
Bedingung 1 -- die Partie und ihre Ketten:
  Runde 1: 175 Glieder, zeichengleich ja, fremde Glieder 0
  ...
  Runde 26: 175 Glieder, zeichengleich ja, fremde Glieder 0
  nach 26 Runden: 4550 Glieder im Verlauf, Zustandspruefsumme 632e47f488471e75
```

Sechsundzwanzig Rundennummern, sechsundzwanzig Gliederzahlen, kein Abbruch -- und die
Rundennummern kommen aus PLATZ_RUNDE des zurueckgegebenen Zustands statt aus der
Zaehlschleife.

**Der rote Kontrollbaum, ohne den das Gruen nichts sagt.** Ein zweiter Baum `r0`,
Zeichen fuer Zeichen gleich dem geprueften bis auf **eine** Zeile in `verlauf.hpp`:
dort steht die alte Kapazitaetszeile aus `41fbcd3~1` mit dem Wert zwanzig, waehrend
`PARTIELAENGE_HOECHSTENS` bei sechsundzwanzig bleibt. `diff -rq` bestaetigt, dass sich
genau diese eine Datei unterscheidet. Ergebnis:

```
terminate called after throwing an instance of std::domain_error
  what():  kern::verlauf -- der Verlauf ist voll: er nimmt 20 Runden auf ..., und die
           Runde 21 waere die naechste. Eine stille Kuerzung gibt es nicht (T19).
1/1 Test #8: verlauf_probe ... Subprocess aborted***Exception
```

Damit ist belegt, was die Bedingung ausdruecklich verlangt: Die Probe zaehlt nicht nur
bis zwanzig, sie **erreicht** die einundzwanzigste Runde und braeche dort ab, sobald die
Kapazitaet wieder an R hinge. Die alte Fassung der Probe -- vier Runden -- waere in
diesem Kontrollbaum gruen geblieben.

# Bedingung 2 -- keine Zahl im Kasten ist mehr die Partielaenge

**Erfuellt.** Zweite, unabhaengige Zaehlung statt Verlass auf den Bericht: jede Zeile
von `verlauf.hpp` ausserhalb der Dokumentationskommentare auf Ziffern gefiltert. Uebrig
bleibt genau **eine** Zahlkonstante im Code, naemlich die Wand mit dem Wert
sechsundzwanzig; die 310 steht nur im Text einer Meldung, und `RUNDEN_KAPAZITAET` ist
keine Zahl mehr, sondern die Wand selbst.

Die 26 ist **nicht** aus R abgeleitet, sondern die Wand ueber R. T40 in `technik.md`
zieht sie selbst als Literal -- "Der Jahrgangsbau bricht mit R groesser 26 ab" --,
nachgerechnet an der Kollision des Bandes "ueberlebt" mit dem Todesband ab 31.000. Die
Ableitungstabelle von T40 fuehrt keine Groesse, die 26 hiesse. Der Kopf sagt an der
Stelle der alten Begruendung jetzt, woraus die Kapazitaet folgt.

**Die obere Schranke bleibt und bricht hart ab, zweiseitig, beide Laeufe abgedruckt:**

```
Bedingung 3 -- die Kapazitaet ueber die Partie:
  an der Grenze: 26 Runden aufgenommen, kein Abbruch
  eine darueber: Abbruch mit "kern::verlauf -- der Verlauf ist voll: er nimmt 26
  Runden auf -- so viele, wie die laengste nach T40 zulaessige Partie hat --, und die
  Runde 27 waere die naechste. Eine stille Kuerzung gibt es nicht (T19)."
```

Die Meldung nennt die Schranke und den Kasten. Der Satz "so viele, wie die laengste
nach T40 zulaessige Partie hat" ist am geprueften Stand wahr; im Kontrollbaum `r0` ist
er es nicht -- dort steht zwanzig in derselben Aussage. Das ist kein Befund gegen die
gelieferte Fassung, wohl aber der Grund, warum die beiden Konstanten in beide
Richtungen festgenagelt sein muessen. Sie sind es; beide Richtungen stehen unten.

# Bedingung 3 -- die Zusicherung ueber die Groesse des Behaelters

**Erfuellt.** Gemessen, nicht geschaetzt: der Behaelter ist 451.784 Byte gross, eine
Kette 17.368 Byte; beide Zahlen gibt die Probe selbst aus. Der erste Wert, an dem die
Zusicherung zuschlaegt, ist **siebenundzwanzig Runden**.

Der Apparat dafuer: zwei Kopfvarianten, aus vorhandenen Zeilen zusammengesetzt, in
denen die beiden Konstantenzeilen entfernt sind und die Werte beim Uebersetzen von
aussen gesetzt werden. Variante **A** traegt die neue Zusicherung, Variante **B** die
alte aus `41fbcd3~1` (halbes Megabyte); sonst sind beide zeichengleich mit dem
geprueften Kopf. Uebersetzt wird jedes Mal die unveraenderte `src/verlauf.cpp`.

| Lauf | Wand | Kapazitaet | Zusicherung | Ergebnis |
|---|---|---|---|---|
| A26 (m0) | 26 | 26 | neu | **gruen** |
| A27 | 26 | 27 | neu | **rot** -- "T40: ein Verlauf traegt hoechstens die Runden der laengsten zulaessigen Partie" |
| B27 (Kontrolle) | 26 | 27 | alt | **gruen** |
| B30 (Kontrolle) | 26 | 30 | alt | **gruen** |
| B31 (Kontrolle) | 26 | 31 | alt | **rot** |

Die drei Kontrollen belegen die Diagnose des Pakets im Wortlaut: Die alte Zusicherung
riss erstmals bei einunddreissig Runden und damit fuer keinen erreichbaren Fall; die
neue reisst beim ersten Wert oberhalb der Wand. Der gruene A26 zeigt, dass der Apparat
nicht alles rot macht.

**Die zweite Richtung deckt die Probe.** Eine Kapazitaet *unterhalb* der Wand faengt
keine Zusicherung -- `r0` uebersetzt gruen. Sie faellt stattdessen zur Laufzeit in
`verlauf_probe`, oben abgedruckt. Zusammen nageln Zusicherung und Probe die Gleichheit
von Kapazitaet und Wand von beiden Seiten fest. Das gehoert in den Nachweis, weil keine
der beiden Stellen allein es tut.

# Bedingung 4 -- beide Profile, beide Bauwege, gegen einen Bezugsstand

**Erfuellt.** Konfigurieren, Bauen, ctest; jeder Lauf Rueckgabe 0:

| Bauweg | Profil | ctest-Eintraege | Ergebnis |
|---|---|---|---|
| Alleinbau `kern/` | ON | 12 | 12/12 bestanden |
| Alleinbau `kern/` | OFF | 12 | 12/12 bestanden |
| Arbeitsbereich | ON | 18 | 18/18 bestanden |
| Arbeitsbereich | OFF | 18 | 18/18 bestanden |

**Der Bezugsstand ist selbst hergestellt, nicht zitiert.** Baum `v0`: derselbe
ausgepackte Baum, in dem die drei Paketdateien durch ihre Fassungen aus `41fbcd3~1`
beziehungsweise `4ff788d~1` ersetzt sind; `diff -rq` zeigt genau diese drei
Unterschiede und sonst keinen. `v0` im Alleinbau mit Sanitizern: **12** ctest-Eintraege,
12/12 bestanden. Die Zahl bleibt also gleich -- das Paket legt keine Probe an und nimmt
keine weg.

# Wonach ich ausserdem gesucht habe

- **Determinismus.** Die vollstaendige Ausgabe von `verlauf_probe` aus beiden
  Bauprofilen zeilenweise gegenuebergestellt: identisch bis auf die Pfad- und
  Zeitzeilen von ctest. Auch die Zustandspruefsumme nach 26 Runden ist in beiden
  Profilen `632e47f488471e75`. Im geaenderten Code kein Gleitkomma, keine streuende
  Menge, kein Zeit- oder Adressbezug; die Suche nach der Rundennummer laeuft aufsteigend
  ueber ein Feld fester Laenge.
- **Der Rand nach oben.** T40 laesst R hoechstens sechsundzwanzig zu, `spiel.md` spielt
  die Runden 1 bis R, und die Runde null traegt keine Kette. Sechsundzwanzig Plaetze
  decken damit jede zulaessige Partie genau ab -- kein Abstand nach oben und, was
  wichtiger ist, keine Runde zu wenig. Eine Abschlussrunde mit eigener Kette gibt es
  nicht; die (R+1)-Formeln in T40 gehoeren der Ergebnisskala und nicht dem Takt.
- **Der Rand nach unten und die Griffe daneben.** `beginne_runde` prueft in fester
  Reihenfolge Wert, Ordnung, Platz; der Zugriff auf die Vorrunde steht nur hinter der
  Pruefung auf mindestens eine aufgenommene Runde; `aufnehmen` kann die innere
  Kettenschranke gar nicht erreichen, weil Kette und Verlauf dieselbe Gliederzahl
  fuehren. Alle sechs Fehlerwege sind in der Probe abgedruckt.
- **Ob die 26 schon woanders steht.** Die Wand kommt im ganzen Vorhaben genau einmal
  vor, in diesem Kopf. Der Jahrgangsbau, dem T40 sie eigentlich zuschreibt, ist im Kern
  noch nicht gebaut; es gibt heute also keine zweite Zahl. Wenn er kommt, muss er diese
  Konstante lesen statt eine eigene 26 zu schreiben -- eine Auflage an das spaetere
  Paket und kein Befund gegen dieses.
- **Die Unsicherheit des Bauagenten zum 200-Runden-Lauf** ist bereits entschieden und
  gehoert nicht hierher: `0145-beschraenktheit-zweihundert-runden-ohne-spieler` nimmt in
  seinem eigenen Text die Abhaengigkeit auf 0144 zurueck, weil dieser Lauf keine Ketten
  mitschreibt.

# Der eine Befund, und warum er das Urteil nicht kippt

**Die Zusicherung ist keine Speicherschranke mehr.** Beide Seiten der neuen Zusicherung
wachsen mit der Wand, also faengt sie ein Verschieben der Wand nicht. Gemessen im
selben Apparat, Variante A, Wand und Kapazitaet gemeinsam gesetzt:

| Wand und Kapazitaet | Groesse des Behaelters | Ergebnis |
|---|---|---|
| 200 | 3.475.208 Byte | **gruen** |
| 2.000 | 34.752.008 Byte | **gruen** |
| 2.169 | 37.670.312 Byte | **gruen** |
| 2.170 | 37.687.688 Byte | rot |

Die Groesse folgt genau der Formel acht mal (2172 mal N plus eins); bei N gleich 26
ergibt das die gemessenen 451.784 Byte, die Formel ist am Messpunkt also bestaetigt.
Die alte Zusicherung haette alle vier Zeilen rot gemacht, die neue erst die letzte --
bei einem Behaelter von 37,7 MB, also weit jenseits eines Stapelrahmens.

Zwei Aussagen des Kopfes decken sich damit nicht mehr: "Wer die Kapazitaeten hochsetzt,
ohne die Folge zu bedenken, bekommt einen roten Bau" (Zeile 72/73) und "Ein Verlauf
gehoert damit nicht beilaeufig auf einen Stapelrahmen" (Zeile 202). Fuer den einen
Regler, der die Groesse tatsaechlich steuert -- die Wand --, gilt beides nicht mehr, und
die absolute Schranke, die es bis `41fbcd3~1` gab, ist im selben Zug ersatzlos entfallen.

**Das ist trotzdem kein `zurueck`.** Bedingung 3 verlangt woertlich, dass die
Zusicherung "am ersten Wert oberhalb des zugelassenen Bereichs" reisst, und benennt den
zugelassenen Bereich ueber die Wand aus T40. Genau das tut sie, zweiseitig belegt. Eine
absolute Bytegrenze verlangt die Bedingung nicht, und ein Kriterium heraufzusetzen steht
mir so wenig zu wie es zu senken. Der Verstoss wird deshalb ein Vorschlag:
`0155-verlaufgroesse-auch-absolut-beschraenkt`.

# Was ich nicht geprueft habe

Das Logbuch des Bauagenten und seine Begruendung habe ich nicht gelesen, den Bericht
unter `befunde/messung-0144/` ebenso wenig. Alle Zahlen oben stammen aus eigenen
Laeufen. Die Rueckkopplungen und die dreistufige Zustandsausgabe beruehrt dieses Paket
nicht -- es aendert einen Behaelter, der nichts rechnet und nichts ausgibt.

(Schreibfehler in der Ueberschrift oben: "geprueffte" muss "gepruefte" heissen.
Korrigieren durfte ich die Zeile nachtraeglich nicht, ohne die Datei neu zu schreiben.)

# Nachtrag zur Nummer des Vorschlags

Ein Parallellauf hat am selben Tag `0155-werte-konstantenkopf-zwei-jahrgangskonstanten.md`
angelegt. Mein Vorschlag traegt dieselbe Nummer
(`0155-verlaufgroesse-auch-absolut-beschraenkt.md`); die Kollision raeumt der
Projektmanager auf. `0156-verlaufgroesse-auch-absolut-beschraenkt.md` ist nur ein
Verweis und kein Paket.
