---
typ: pruefung
paket: 0027-zustand-schreibweg-schliessen
pruefer: kern-pruefer
datum: 2026-09-04
urteil: zurueck
kriterium_geprueft: Die fuenf Bedingungen einzeln, mit eigenem Bau in beiden Profilen, fuenf eigenen Uebersetzungseinheiten und einer eigenen laufenden Gegenprobe; 1, 2, 4 und 5 sind belegt, Bedingung 3 haelt gegen die von Hand gebaute Runde der Probe, aber nicht gegen die echte Runde des Kerns -- nach `kern::schritt::schritt` schreibt der alte Zugang weiter, und ein neuer bindet noch.
befunde: 2
---

# 0027, Runde 2 -- der Riegel greift, aber nicht gegen die Runde, um die es geht

## Was fremdgemessen ist und was ich selbst gemessen habe

**Fremdgemessen:** `befunde/uebersetzung-2026-09-04.md`, vom Baulauf erzeugt.

**Selbst gemessen**, alles ausserhalb des Repos gebaut (`git archive HEAD` in ein
Wegwerfverzeichnis); die Pruefstuecke liegen unter `befunde/pruefung-0027-runde2/`, wo der
Baulauf nicht einsammelt:

| Was | Ergebnis |
|---|---|
| Bau des Kastens `kern`, Profil Debug | gruen |
| Bau des Kastens `kern`, Profil RelWithDebInfo | gruen |
| `ctest` in beiden Profilen | 8 von 8 bestanden |
| `zustand_probe` und `schreiber_probe`, ausfuehrlich | bestanden, Wortlaut im Anhang |
| vier feindliche Uebersetzungseinheiten gegen `kern/zustand.hpp` | vier Uebersetzungsfehler |
| eine Positivprobe, dieselbe Einbindung | uebersetzt, gebunden, ausgefuehrt, Rueckgabewert 42 |
| eine eigene Gegenprobe mit `kern::schritt::schritt` | **beide Schreibwege offen** -- Befund 1 |

Beide Profile, weil unter Optimierung Warnungen zugeschaltet werden, die im Debug-Profil
nicht erscheinen. Die Proben binden `kern_geprueft`, also dieselben Quellen mit den beiden
Sanitizern (ADR 0011, Massnahme 2) -- die Laeufe sind also sanitizergedeckt. Der Baum ist
unberuehrt: Ausser meinen Pruefstuecken unter `befunde/` und dieser Datei habe ich nichts
geschrieben.

---

## Bedingung 1 -- erfuellt, und mit Positivprobe

Verlangt war **eine** Uebersetzungseinheit, die nur `kern/zustand.hpp` einbindet. Ich habe
vier gebaut und eine fuenfte danebengestellt, die uebersetzen **muss**. Der Uebersetzer im
Wortlaut, aufgerufen mit dem Sprachstand des Pakets und nur dem Kopfbaum des Kerns:

| Pruefstueck | Versuch | Meldung |
|---|---|---|
| `a_feld.cpp` | Feldzugriff auf Platz 0 | error: das Feld der 310 Ganzzahlen `kern::zustand::Zustand::feld` is private within this context; declared private here -- `zustand.hpp:439` |
| `b_schreibe.cpp` | Aufruf des alten Schreibzugriffs | error: `class kern::zustand::Zustand` has no member named `schreibe` |
| `c_lege_ab.cpp` | Aufruf des neuen rohen Schreibzugriffs | error: `constexpr void kern::zustand::Zustand::lege_ab(Index, i64)` is private within this context; declared private here -- `zustand.hpp:451` |
| `e_zeiger.cpp` | Feldzugriff ueber einen Zeiger | error: dieselbe Zeile 439, dieselbe Aussage |

Die dritte und die vierte Zeile verlangt die Bedingung nicht. Die dritte steht hier, weil
der rohe Schreibzugriff umbenannt statt entfernt wurde und der neue Name sonst ungeprueft
bliebe; die vierte, weil die Grep-Regel aus Bedingung 2 den Weg ueber einen Zeiger nicht
sieht -- **hier ist er zu, also traegt Bedingung 1 gegen die Sache und nicht bloss gegen die
Schreibweise.**

**Die Positivprobe** (`d_positivprobe.cpp`): dieselbe Einbindung, derselbe Sprachstand, ein
erlaubter Zugriff -- ueber den Startwertzugang die 42 auf Platz 0 legen und wieder lesen.
Sie uebersetzt, bindet gegen `zustand.cpp` und `festkomma.cpp` und **laeuft**:
Rueckgabewert 42. Ohne sie waeren die vier Fehler oben auch mit einem Kopf vereinbar, der
gar nicht uebersetzt.

Die drei `static_assert`-Zeilen in `zustand_probe.cpp:173-177` sagen dasselbe innen, und
ihre Gegenprobe steht daneben (`:182`, der Lesezugriff **muss** erreichbar sein). Auch die
beiden Nebendinge aus dem Ruecklauf sind dort mechanisch beantwortet statt beschrieben:
keine Kopie und keine Verschiebung (`:193-198`), kein Zugang auf einen Zustand ohne Namen
(`:199-200`), und die Gegenprobe dazu, dass an einen benannten sehr wohl einer bindet
(`:204`). Das ist sauber gebaut.

## Bedingung 2 -- erfuellt

Beide vorgeschriebenen Suchlaeufe ueber `kern/` gehen leer aus, mit POSIX-Suche, also
**einschliesslich** des mitversionierten `kern/bau/`. Dasselbe ueber das ganze Vorhaben auf
Quell- und Kopfdateien: ebenfalls leer -- ausser meinen eigenen Pruefstuecken.

**Ich habe beide Muster gegen einen echten Verstoss gehalten, bevor ich dem leeren Ergebnis
geglaubt habe:** Ueber `befunde/pruefung-0027-runde2/` treffen sie `a_feld.cpp` Zeile 9 und
`b_schreibe.cpp` Zeile 7. Das leere Ergebnis ist also eine Aussage und kein totes Muster.

`lege_ab` kommt im Kernbaum an genau vier Stellen vor: Deklaration (`zustand.hpp:451`),
Meldungstext (`:454`) und die beiden Aufrufe der befreundeten Klassen (`schreiber.cpp:242`,
`zustand.cpp:977`). Mehr gibt es nicht.

## Bedingung 3 -- **nicht erfuellt.** Siehe Befund 1.

Teilbedingung a und die Gegenprobe halten; b und c halten gegen die von Hand gebaute Runde
der Probe und **nicht** gegen die Runde des Kerns. Im Einzelnen:

- **a. Ein Startwert erzeugt keinen Ursachensatz.** Erfuellt, gedruckt: *Startwert 1000000
  ohne Ursachensatz: 0 Kettenglieder nennen ihn, Kette der Runde 175 Glieder.*
- **b. Binden an einen Zustand mit gelaufener Runde ist ein harter Fehler.** Erfuellt,
  solange die Rundennummer von Hand gesetzt wurde (`zustand_probe` Zeile 729,
  `schreiber_probe` Zeile 474). **Nach einer echten Runde nicht** -- Befund 1.
- **c. Ein gebundener Zugang, an dem eine Runde vorbeigelaufen ist, bricht ab.** Die Probe
  fuehrt genau den vorgeschriebenen Ablauf vor (`schreiber_probe.cpp:501-527`), und der
  Abbruch kommt mit ausgeschriebener Meldung, die beide Rundennummern nennt. **Mit der
  echten Runde bricht nichts ab** -- Befund 1.
- **Die Gegenprobe:** Beide Belegungsschleifen laufen durch. Der Zaehlzustand ergibt
  weiterhin `25e8b19071bea26c` (gedruckt, `zustand_probe.cpp:664`), die Fassung mit zwei
  getauschten Feldern eine andere (`:681`, gruen). Die Feldreihenfolge ist unberuehrt.
  **Zubetoniert ist hier nichts** -- das habe ich zuerst geprueft, weil ein Riegel, der
  alles blockiert, im Negativtest genauso aussieht wie ein richtiger.

## Bedingung 4 -- erfuellt

Runde 2 liegt in zwei Commits: `89d5af2` (21:03, `zustand.hpp`, `zustand.cpp`,
`zustand_probe.cpp`, `schreiber_probe.cpp`) und `9cac478` (21:10, `schranken_probe.cpp`).
Beide tragen einen Betreff, der etwas anderes nennt; gefunden ueber `git log -S`, nicht
ueber den Betreff. **Keiner der beiden fasst `schreiber.hpp` oder `schreiber.cpp` an.** Die
Bedingungen von 0016 haengen genau dort und sind damit nicht nur unveraendert, sondern
unberuehrt. Nachgezaehlt habe ich sie trotzdem:

1. `Ursachensatz` traegt sieben Felder (`schreiber.hpp:322-339`), `UrsacheArt` sechs Formen
   (`:152-159`).
2. Ausgeloest und gedruckt: zweiter Schreibzugriff (Zeile 192 und 422), `lies_neu` vor dem
   Schreiben (Zeile 202 und 453).
3. Altwert 4711 neben Neuwert 815 gedruckt.
4. Maskenpruefung beidseitig ausgeloest (Zeile 339 und 350); dass Maske und Aussenmenge
   zusammen 310 ergeben, steht als Zusicherung (`schreiber.hpp:419`) und wurde vom gruenen
   Bau ausgewertet. Gedruckt: 175 und 310.
5. Weltlauf 175 Adressen, Kette 175 Glieder; Spielmodus 310 und 310.
6. Suchlauf nach Gleitkomma ueber alle fuenf Dateien des Pakets: leer.

Die Bedingungen von 0008 ebenso: 2.480 Byte und 310 Felder gedruckt und als Zusicherung
(`zustand.hpp:467-476`), Rundlauf Adresse zu Platz 310 von 310 genau einmal, kein wachsender
Behaelter und keine eigene Speicherzuteilung in den beiden Zustandsdateien.

Und die Fussangel aus dem Ruecklauf ist ausgeraeumt: `schranken_probe.cpp` bindet nicht mehr
je Aufruf einen Zugang, sondern haelt Zustand und Zugang zusammen (`Rohling`, `:106-118`).
Der Fall, an dem der Vorgaenger gestorben waere, laeuft dort jetzt vor (`:868-874`: erst
die Rundennummer auf zwoelf setzen, danach weiter belegen, und die Belegung traegt).
`schranken_probe` ist in beiden Profilen gruen.

## Bedingung 5 -- erfuellt

Der Uebersetzungsbericht `befunde/uebersetzung-2026-09-04.md` nennt **`schreiber_probe`
(Nr. 5) und `zustand_probe` (Nr. 8) beide namentlich und bestanden**; kein leerer
Bauabschnitt. In meinen eigenen Laeufen stehen beide ebenso, in beiden Profilen.

**Zum `ergebnis: fehler` im Kopf des Berichts, damit es niemand diesem Paket zurechnet:**
Rot ist genau ein Test, `belegstellen_riegel` (Nr. 12), wegen vier Verweisen mit
Zeilennummern in `zustand.hpp` und `schranken_probe.cpp`. Das ist der Riegel aus Paket
0059, der seit dem 2026-09-04 mitlaeuft -- zwei Tage **nach** dem Bau dieses Pakets --, und
die Reparatur hat mit `aufgaben/0070-kern-belegstellen-ohne-zeilennummer.md` bereits einen
eigenen Vorschlag, der beide Dateien nennt. Kein Befund gegen 0027.

---

# Befund 1 -- der Riegel haelt gegen die Runde der Probe, nicht gegen die des Kerns

**Bricht Abnahmebedingung 3, Teilbedingungen b und c.**

## So erzeugt man den Fehler -- Schritt fuer Schritt, ausgefuehrt

Pruefstueck `befunde/pruefung-0027-runde2/f_echte_runde.cpp`, gebunden gegen `zustand.cpp`,
`schreiber.cpp`, `schritt.cpp` und `festkomma.cpp`. Es tut **genau**, was Teilbedingung c
vorschreibt -- binden, eine Runde ueber denselben Zustand laufen lassen, das Rundenende
zurueckschreiben, den alten Zugang benutzen --, nur mit `kern::schritt::schritt` statt mit
dem Rundenhelfer der Probe:

1. frischer Zustand, Startwertzugang darauf binden, `fonds.kasse` auf 1.000.000 setzen,
2. eine Runde im Modus `weltlauf` rechnen lassen,
3. das Rundenende in denselben Zustand zurueckschreiben,
4. mit dem alten Zugang `fonds.kasse` auf 4711 setzen.

Die Ausgabe im Wortlaut:

```
nach einer echten Runde: partie.runde = 0, Kette 175 Glieder, vor_der_ersten_runde = ja
KEIN ABBRUCH: der Zugang von vor Runde 1 hat nach der Runde geschrieben -- fonds.kasse = 4711
KEIN ABBRUCH: ein neuer Zugang bindet nach der Runde -- fonds.kasse = 815
2 von 2 Schreibwegen sind nach einer echten Runde offen.
```

Es ist eine **vollstaendige** Runde: 175 Kettenglieder, also die ganze Sollmaske des
Weltlaufs, samt zweiseitiger Rundenendpruefung -- ohne sie waere der Aufruf abgebrochen.

## Warum der Riegel danebengreift

`Startbelegung::setze` vergleicht `partie.runde` mit der Zahl, die der Zugang dort selbst
hinterlassen hat (`zustand.cpp:961-973`). Das faengt jeden fremden Schreibzugriff, der die
Zahl **aendert**. Die Runde des Kerns aendert sie nicht:

- `partie.runde` gehoert nach der Zuordnungstafel zu Schritt 1 (`schritt.cpp:268`),
- Schritt 1 ist der Vortrag (`schritt.cpp:406`),
- und der Vortrag schreibt den Wert der Vorrunde zurueck (`schreiber.cpp:256-262`) --
  **denselben Wert.**

Die Rundennummer, Vorrundennummer plus eins (`schritt.cpp:577`), geht nur an den Schreiber
und steht in den Ursachensaetzen; **in den Zustand kommt sie nicht.** Ein dritter Zeuge
dafuer, ohne meine eigenen Laeufe: `schritt_probe.cpp:291` sichert feldweise, dass der
Zustand nach der Runde derselbe ist wie davor -- eine gruene, fremde Probe. Und
`pruefung-0033-schritt-rundengeruest-weltlauf-2026-09-03.md` haelt dieselbe Beobachtung
schon fest ("Die Runde zaehlt nicht hoch"), dort ausdruecklich als kein Befund, weil
Bedingung 6 jenes Pakets genau das verlangt. Beides stimmt einzeln. Zusammen ergeben sie,
dass der Riegel dieses Pakets im gebauten System nie anschlaegt.

## Warum das nicht bloss unschoen ist

Es ist wortgleich der Schaden, den der Ruecklauf beschreibt: Eine Rundenschleife bindet den
Zugang vor der Schleife und schreibt jede Runde zurueck; danach steht er offen. Seine
naechste Setzung ist eine Aenderung ohne Ursachensatz, ohne Kettenglied und ohne
Maskenpruefung, und die Diff-Ebene aus T20 zeigt eine Aenderung ohne Ursache. Die Zusagen
"genau einmal je Runde" und "acht Kanaele, nicht neun" haengen genau daran.

Dazu die zweite Zeile der Ausgabe, die ueber Teilbedingung c hinausgeht: Auch ein **neuer**
Zugang bindet nach einer echten Runde noch. Teilbedingung b galt in Runde 1 als erfuellt --
belegt war sie aber nur an einem Zustand, dessen Rundennummer von Hand gesetzt wurde.

## Was ich ausdruecklich **nicht** beanstande

- **Die Wahl der Zugriffsform, den Namen des Zugangs und die Merkzahl-Regel.** Die Regel hat
  der Ruecklauf vorgegeben, und sie ist richtig umgesetzt: Der Zugang traegt ueber seinen
  eigenen Schreibzugriff auf `partie.runde` hinweg, ein fremder schliesst ihn. Was fehlt,
  ist nicht die Umsetzung, sondern die Voraussetzung.
- **Den Bauagenten.** `kern/src/schritt.cpp` entstand mit Commit `00d6f21` um 21:10 des
  2026-09-02, seine Arbeit liegt in `89d5af2` um 21:03 -- **sieben Minuten frueher**. Er
  konnte den Rahmen der Runde nicht lesen; er hat vorhergesagt, was sie tun wuerde.
- **`kern::schritt`.** Sein Vortragen ist von der eigenen Bedingung 6 jenes Pakets gefordert
  und dort ausdruecklich als "auf Widerruf" ausgewiesen.

## Warum das der Projektmanager entscheiden muss und nicht der Bauagent

**Innerhalb der `dateien`-Liste von 0027 ist Bedingung 3 nicht erfuellbar.** Der Riegel
kennt nur den Zustand, und eine Runde, die ihn Feld fuer Feld unveraendert laesst, ist von
"keine Runde gelaufen" durch **keinen** Vergleich am Zustand zu unterscheiden -- auch nicht
durch einen, der alle 310 Groessen mitnimmt. Ein 311. Feld ist durch T15 und durch den
Ruecklauf ausgeschlossen. Die einzige Stelle, an der sich das aufloest, ist Schritt 1 der
Runde: Er muesste `partie.runde` **setzen** statt vortragen. Das ist `kern/src/schritt.cpp`
und gehoert 0033.

Ich senke die Bedingung nicht und lege auch keine Auslegung nach. Beide Wege stehen dem
Projektmanager offen -- die `dateien`-Liste von 0027 um die Dateien von `kern::schritt`
erweitern, oder Bedingung 3 auf ein Folgepaket schieben. Fuer den zweiten Weg liegt
`aufgaben/0071-rundennummer-in-den-zustand.md` als Vorschlag daneben; er nennt auch, was
dabei an 0033 nachzuziehen ist.

---

# Befund 2 -- die Begruendung im Kopf sagt etwas Falsches ueber den Kern

**Bricht keine Abnahmebedingung. Liegt in `zustand.hpp` und ist dort reparierbar.**

`zustand.hpp:519-524` schreibt, wogegen der Riegel nichts ausrichtet, und nimmt den Fall
danach ausdruecklich zurueck:

> "Er vergleicht eine Zahl und keine Herkunft. Ein fremder Schreibzugriff, der auf
> `partie.runde` genau die Zahl zuruecklaesst, die schon dort stand, bleibt ihm verborgen.
> **Die Runde des Kerns tut das nicht** -- sie traegt ihre eigene Nummer ein, und die ist
> groesser als jede vorige --, und ausser ihr schreibt niemand auf dieses Feld."

Der hervorgehobene Satz ist falsch: Die Runde des Kerns tut genau das. Dasselbe steht ein
zweites Mal in `:498-501` ("Sobald eine Runde gelaufen ist, traegt das Feld ihre Nummer,
denn es steht in beiden Sollmasken aus T38 und wird jede Runde geschrieben") -- in der Maske
zu stehen heisst geschrieben zu werden, nicht veraendert zu werden.

**Warum das ein eigener Befund ist und nicht nur die Textseite von Befund 1:** Diese beiden
Stellen sind die Begruendung, mit der die Luecke abgehakt wird. Wer sie liest, hat die Frage
gestellt und eine Antwort bekommen -- und hoert auf zu suchen. Ein Kommentar, der einen
Randfall ausdruecklich fuer ausgeschlossen erklaert, ist teurer als gar keiner, wenn der
Randfall der Normalfall ist. Die Stellen liegen in `zustand.hpp` und damit im Zugriff dieses
Pakets, auch wenn Befund 1 es nicht ist.

---

## Was ich sonst gesucht und **nicht** gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar ist:

- **Determinismus.** Kein Gleitkomma in den fuenf Dateien des Pakets, keine Iteration ueber
  eine streuende Menge, kein zweiter Zufallsstrom. Der Startwertzugang haelt einen rohen
  Zeiger und eine Ganzzahl -- Werkzeug, kein Zustand; keine Adresse gelangt in die 310
  Groessen. Beide Bauprofile drucken dieselben Pruefsummen (`25e8b19071bea26c`,
  `01d663224c4054e5`, `a491e70cc3f70d5d`).
- **Rueckkopplungen.** Das Paket aendert, *wer* schreiben darf, nicht *was* beim Schreiben
  geschieht; Schreiber und Kette sind von beiden Commits nicht beruehrt. Der neunte Kanal,
  den es schliessen soll, ist beim Uebersetzen zu (Bedingung 1) -- gegen die Runde bleibt er
  offen (Befund 1).
- **Zustandsausgabe.** Byteform und Pruefsumme holen ihre Zahl ueber den Lesezugriff; die
  Schleifengrenze *ist* die Feldzahl, die Indexpruefung kann dort nicht anschlagen.
- **Raender, von Hand nachgerechnet.**
  * Der Platz von `partie.runde` ist 306: `daten/adressen.md` fuehrt ihn als laufende Nummer
    307, der Kern zaehlt ab null. Das steht als Zusicherung (`zustand.cpp:866`), also ist
    ein verschobener Partieblock ein roter Bau und kein ins Leere greifender Riegel.
  * **Der Meldungspuffer kann nicht abschneiden.** 512 Zeichen; die drei Textstuecke des
    Riegels sind 107, 22 und 183 Zeichen, dazu zweimal hoechstens 20 Zeichen Zahl -- 352 im
    schlimmsten Fall. Nachgezaehlt, nicht geschaetzt. Das Abschneiden waere still
    (`zustand.cpp:884-886`), deshalb habe ich es gerechnet.
  * **Die Zifferndarstellung haelt die kleinste Ganzzahl.** Der Betrag laeuft ueber die
    vorzeichenlose Subtraktion von null (`:900`), das Ziffernfeld ist 24 Zeichen breit bei
    hoechstens 19 Ziffern.
  * Die Merkzahl wird **nach** dem Schreibzugriff gesetzt (`:983-985`): Bricht der an der
    Indexpruefung ab, merkt sich der Zugang nichts. Richtig herum.
  * Ueberlauf, Division und Rundung kommen in diesem Paket sonst nicht vor.
- **Die Reihenfolge in `Rohling`.** Der Zustand steht vor dem Zugang, die Bindung geschieht
  also an ein fertig gebautes Mitglied.

---

## Anhang -- die Ausgaben im Wortlaut

`zustand_probe`, Profil RelWithDebInfo, eigener Bau. Jede Zeile der Programmausgabe als
Punkt:

- sizeof(Zustand) gleich 2480 Byte, 310 Felder
- Rundlauf Adresse zu Platz: 310 von 310 genau einmal
- Abbruch wie erwartet (Zeile 348): kern::zustand::lege_ab -- Index ausserhalb der 310 Felder
- Abbruch wie erwartet (Zeile 350): kern::zustand::lies -- Index ausserhalb der 310 Felder
- Abbruch wie erwartet (Zeile 351): kern::zustand::index_zu_adresse -- Index ausserhalb der
  310 Felder
- Fehlerwert der Adresssuche: 310, gueltige Plaetze 0 bis 309
- Adressfunktionen decken 310 von 310 Plaetzen genau einmal
- Steckplaetze: 20 Adressen, 19 spielbar
- Nullzustand: Kette 01d663224c4054e5, Bytefolge 01d663224c4054e5, Potenz 01d663224c4054e5
- letztes Feld auf minus eins: a491e70cc3f70d5d
- Felder, die die Summe aendern: 310 von 310
- **Zaehlzustand (Feld i traegt i): 25e8b19071bea26c**
- Abbruch wie erwartet (Zeile 728): kern::zustand::Startbelegung -- die Partie laeuft schon
  (partie.runde ist nicht null); Startwerte gibt es nur vor der ersten Runde
- Abbruch wie erwartet (Zeile 729): dieselbe Meldung, zweite Ausloesung
- Startwertzugang: vor Runde 1 offen, in Runde 12 verriegelt
- Abbruch wie erwartet (Zeile 773): kern::zustand::Startbelegung::setze -- an diesem Zugang
  ist eine Runde vorbeigelaufen: partie.runde traegt 7, der Zugang hat dort 0 hinterlassen.
  Startwerte gibt es nur vor der ersten Runde; danach waere jeder eine Aenderung ohne
  Ursachensatz (T18) und erschiene in der Diff-Ebene als Aenderung ohne Ursache (T20).
- Abbruch wie erwartet (Zeile 778): dieselbe Meldung, an einer Adresse ohne Bezug zur Runde
- Riegel je Schreibzugriff: Zugang mit Merkzahl 0 gegen partie.runde 7 -- zu
- kern::zustand -- alle Proben bestanden.

`schreiber_probe`, dasselbe Profil, die Zeilen zu den Bedingungen 3 und 4:

- lies_alt gleich 4711, lies_neu gleich 815 (erwartet 4711 und 815)
- Sollmaske weltlauf 175, spielmodus 310, Kettenkapazitaet 310
- Abbruch wie erwartet (Zeile 339): Rundenende Runde 1: in der Sollmaske, aber nicht
  geschrieben: welt.preis.2 (Nr. 240)
- Abbruch wie erwartet (Zeile 350): Rundenende Runde 1: ausserhalb der Sollmaske
  geschrieben: fonds.hebelstand (Nr. 256)
- Weltlauf: 175 Adressen geschrieben, Kette 175 Glieder (erwartet 175)
- Spielmodus: 310 Adressen geschrieben, Kette 310 Glieder (erwartet 310)
- Abbruch wie erwartet (Zeile 474): kern::zustand::Startbelegung -- die Partie laeuft schon
- Startwert 1000000 ohne Ursachensatz: 0 Kettenglieder nennen ihn, Kette der Runde 175
  Glieder
- Abbruch wie erwartet (Zeile 522): kern::zustand::Startbelegung::setze -- an diesem Zugang
  ist eine Runde vorbeigelaufen: partie.runde traegt **3060**, der Zugang hat dort 0
  hinterlassen; danach derselbe ausgeschriebene Grund wie oben
- Zugang von vor Runde 1 nach der Runde (partie.runde gleich 3060): zu
- schreiber_probe: alle Pruefungen bestanden

**Die 3060 ist die Zahl, an der Befund 1 haengt.** Sie entsteht im Rundenhelfer der Probe,
der auf jede Maskenadresse den Platz mal zehn schreibt (`schreiber_probe.cpp:315-327`) --
306 mal zehn. Die echte Runde schreibt dort die Null, die schon da stand.
