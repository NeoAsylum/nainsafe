# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 13:55. Fassung 30, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**Sieben Urteile lagen vor, alle sieben `geprüft`, kein einziger Rücklauf** — zum zweiten
Mal in Folge ein ganzer Prüfdurchgang ohne Beanstandung. 133 Pakete: 24 offen, 0 gebaut,
105 fertig, 4 blockiert, 0 Vorschläge.

**Der Trockenlauf zu Beginn plante 1 von 8 Bauplätzen** — der schlechteste Stand, den
diese Datei je verzeichnet hat. Nach dem Statusnachzug waren es 4, nach der Sichtung der
Vorschläge 7, nach dem letzten Schnitt **8 von 8**. Kein einziger dieser Plätze ist durch
mehr Pakete entstanden; sie waren alle schon da und hingen an Urteilen, die niemand
gezogen hatte.

Vier Vorschläge gesichtet, **alle vier angenommen**, einer davon umnummeriert. Dazu ein
neu geschnittenes Paket und eine gelöste Sperre — beides zusammen der erste Auftrag seit
Tagen, der am Erzeugnis selbst arbeitet und nicht an den Werkzeugen darüber.

## Der Statusnachzug: sieben Abnahmen, kein Rücklauf

| Paket | Rolle | Prüfer | Urteil |
|---|---|---|---|
| 0078 reihentoml-preisbasis-nach-t53 | `datenbauer` | daten-prüfer | **geprüft** (Runde 3) → `fertig` |
| 0083 belegstellenriegel-totes-ziel | `testentwickler` | test-prüfer | **geprüft** (Runde 2) → `fertig` |
| 0104 zielzahlen-je-profil-statt-tripel | `kernbauer` | kern-prüfer | **geprüft**, 1 Befund → `fertig` |
| 0129 bezeichner-im-kommentar-löst-auf | `testentwickler` | test-prüfer | **geprüft** → `fertig` |
| 0133 schlussriegel-nachbau-läuft-nirgends | `testentwickler` | test-prüfer | **geprüft** → `fertig` |
| 0134 sperrebindung-jeder-kernquelle | `kernbauer` | kern-prüfer | **geprüft** → `fertig` |
| 0135 bauwege-sollzahl-gegen-eigenen-stand | `testentwickler` | test-prüfer | **geprüft** → `fertig` |

**0078 ist durch, im dritten Anlauf.** Es stand bei zwei Rückläufen, und die letzte Fassung
seiner Bedingung 5 war die, bei der ich dem Bauagenten die Wahl abgenommen habe, statt ihm
einen Halbsatz mitzugeben. Damit sind jetzt **drei** Pakete auf diesem Weg durchgegangen
(0078, 0079, 0087); der Griff trägt. `RUECKLAUF_MAX` ist nirgends erreicht worden.

**Nur ein einziger Befund in sieben Prüfungen**, und er ist kein Mangel: Der Kern-Prüfer
hat bei 0104 gemessen, dass die Riegelmeldung ihr Profil nicht nennt — ein Fehler, der
erst dadurch sichtbar wird, dass 0104 die Regel aufstellt, an der man ihn messen kann. Er
ist als 0137 aufgenommen.

## Vier Vorschläge, vier Annahmen — und eine doppelt vergebene Nummer

| Paket | Rolle | Datei | Entscheidung |
|---|---|---|---|
| **0136** schlussriegel-nachbau-in-eigenes-mitglied | `testentwickler` | `CMakeLists.txt`, `pruefstand/CMakeLists.txt` | `offen`, ohne Kette |
| **0137** riegelmeldung-nennt-ihr-profil | `kernbauer` | `werkzeugkette.cmake` | `offen`, viertes Kettenglied |
| **0138** bezeichnerriegel-tragende-regel | `testentwickler` | `bezeichner_riegel.cpp` | `offen`, ohne Kette |
| **0139** sperrebindung-auch-für-die-proben | `kernbauer` | `kern/CMakeLists.txt` | `offen`, **umnummeriert von 0138** |

Die vier Prüfungen halten überall: alle vier Rollen stehen in `BAUROLLEN`, alle vier
Abnahmen nennen Bedingungen statt Zahlen, drei brauchen keine Abhängigkeit und die vierte
trägt eine Reihenfolgesperre. **Zum ersten Mal seit fünf Läufen ist keine Waisenrolle
dabei** — die Rollenfrage steht trotzdem weiter an erster Stelle.

**Alle vier Prämissen habe ich selbst nachgemessen.** `kern/CMakeLists.txt` liest die
Kernquellen in Zeile 51 und die Proben erst in Zeile 185, der Sperrebindungsriegel läuft
dazwischen und sieht die Proben nie. `bezeichner_riegel.cpp` prüft seine tragende Regel im
Selbsttest an keiner Stelle im Einlesepfad. Die drei Bauwege des Prüfstands melden ihre
Zielzahl ohne den Schalter, aus dem sie folgt. Und die Bahn des Nachbau-Wächters liegt im
Prüfstand, weil **ich** ihn dorthin gelegt habe. Vier von vier tragen.

### 0139: zwei Prüfer haben am selben Tag dieselbe Nummer vergeben

Der Kern-Prüfer und der Test-Prüfer haben beide `0138` genommen — jeder hat richtig
nachgesehen, was vergeben war, und keiner konnte den anderen sehen, weil beide im selben
Durchgang liefen. Das ist keine Nachlässigkeit, sondern die Bauart des Vorschlagsrechts:
**Es gibt keine Stelle, an der eine Nummer reserviert wird, außer mir.**

Der ältere behält die Nummer, der jüngere ist mit `git mv` auf 0139 umgezogen und trägt
den Vermerk. Der Schaden wäre andernfalls nicht klein gewesen: Zwei Pakete mit derselben
Kennung sind für `haengt_an` nicht unterscheidbar, und die Kollisionsprüfung hätte sie
irgendwann gegeneinander laufen lassen.

**Für die Vorschlagenden heißt das:** Die Nummer im Dateinamen ist ein Vorschlag wie der
Rest. Wer in einem Vorschlag auf ein anderes Paket zeigt, nennt am besten den Dateinamen
und nicht die Ziffer — 0137 macht das vorbildlich und schreibt es sogar dazu.

## Das neue Paket: der Träger aus T19, und eine Rücknahme

**`0140-verlauf-sammelt-die-rundenketten`, `kernbauer`, `offen`.** Es baut den `Verlauf`,
den T19 beim Namen nennt: `schritt` liefert Zustand und Kette der Runde nebeneinander, und
die Sitzung sammelt die Ketten. Gebaut war bisher die erste Hälfte — `Rundenergebnis`
trägt die Kette einer Runde, und niemand hebt sie auf.

**Ich habe im letzten Lauf ausdrücklich geschrieben, dass ich dieses Paket nicht von mir
aus anlege.** Der Grund stand in 0091: es sei ein neues Gewerk, der Vorrang nenne es
nicht, und die Reihenfolge gegen die eine Zahl gehöre dem Geschäftsführer. **Dieser Grund
ist weggefallen, und zwar vollständig.** Alle fünf Kennungen des Vorrangs vom 2026-09-04
stehen auf `fertig`, die eine Zahl (0002) darunter. Es gibt keine Reihenfolge mehr, der
ich hier ausweichen könnte — und die Regel meiner Rolle sagt, ich soll dem Vorrang folgen
oder begründen, warum nicht. Ein leerer Vorrang lässt sich nicht befolgen.

Erfunden ist das Paket nicht: T19 steht in `specs/`, nennt den Träger beim Namen, und der
Kern verweist in `schritt.hpp` selbst darauf. Ich setze eine Vorgabe um und entscheide
nichts am Entwurf.

**Es kollidiert mit nichts.** Die drei Dateien gibt es noch nicht, und `kern/CMakeLists.txt`
ist nicht anzufassen — Quellen und Proben werden per `file(GLOB … CONFIGURE_DEPENDS)`
eingesammelt. Das steht so im Paket, samt der Warnung, dass diese Datei heute 0139 hält.

**`0091` ist damit entsperrt**, von `blockiert` auf `offen`, mit `haengt_an` auf 0140. Der
Auslöser, den ich selbst angekündigt hatte, ist eingetreten, weil ich ihn selbst gezogen
habe. Bis 0140 abgenommen ist, plant `startbereit()` es nicht ein; es kostet also keinen
Platz. Dabei ist eine zweite Sache aufgefallen und berichtigt: Seine `dateien`-Liste nannte
nur die drei `verlauf`-Dateien, obwohl seine Abnahme verlangt, dass **die Ausgabe** die
Kette nennt — und die steht in `zustandsausgabe.cpp`. Ein Feld, das die Datei nicht nennt,
die das Kriterium zwangsläufig anfasst, schützt sie nicht. Die drei Ausgabedateien sind
aufgenommen, das Kriterium selbst ist unberührt.

## Die Ketten — vier Köpfe halten sechzehn Pakete

    technik.md        0116 → 0117 → 0064 → 0068 → 0074 → 0084 → 0092   (7)
    riegel.cpp        0105 → 0106 → 0115 → 0130                        (4)
    werkzeugkette     0108 → 0124 → 0132 → 0137                        (4, +1)
    reihen.toml       0099 → 0100 → 0126                               (3)
    spiel.md          0118                                             (1, wartet auf 0117)
    verlauf/ausgabe   0140 → 0091                                      (2, neu)
    ohne Kette        0136, 0138, 0139                                 (3)

Vierundzwanzig offen, **acht startbereit, sechzehn hinter fünf Kettenköpfen.** Jedes Glied
trägt seinen Vorgänger in `haengt_an`; nachgemessen, nicht behauptet. In jedem Kettenglied
steht derselbe Satz für den Bauagenten: Dein Vorher-Stand ist der dann geltende `HEAD`,
such am Text, nicht an einer Zeilennummer.

**Die drei kettenlosen Pakete sind Vorschläge aus bestandenen Prüfungen.** Das bestätigt
zum dritten Mal, dass ein Befund mit dem Urteil `geprüft` die bessere Paketquelle ist als
ein Rücklauf: Ein Rücklauf erzeugt Arbeit an einer Datei, die schon belegt ist; ein
Nebenbefund zeigt auf eine, die gerade frei geworden ist.

**Was mir an dieser Aufstellung nicht gefällt und was ich dazu tun kann, steht unten.**
Von den vierundzwanzig offenen Paketen arbeitet genau **eines** am Erzeugnis: 0140. Die
übrigen dreiundzwanzig arbeiten an Entwurfstext, an der Werkzeugkette, an Riegeln und an
der Reihendatei. Bis heute waren es null.

## Was der Geschäftsführer entscheiden lassen muss

**1. Ein neuer Vorrang. Die Liste in `ops/plan.md` ist zum fünften Mal vollständig
abgearbeitet.** Alle fünf — 0026, 0002, 0071, 0027, 0010 — stehen auf `fertig`, einzeln
nachgesehen; der Plan stammt vom 2026-09-04 07:49 und ist seither nicht erneuert. **Zum
fünften Mal gemeldet, zum fünften Mal unbeantwortet.** Diesmal ist es mehr als eine
Formsache: Ich habe an einer Stelle nach eigener Auslegung entschieden, wo ich es im
letzten Lauf ausdrücklich unterlassen hatte (0140, oben). Die Begründung dafür ist der
leere Vorrang. Wer den Vorrang füllt, nimmt mir diese Auslegung wieder ab.

**2. Die Fabrik baut zu 96 % an sich selbst, und das lässt sich jetzt beziffern.** Von 24
offenen Paketen arbeitet 1 am Erzeugnis. Der letzte Plan hat diesen Befund an 21 von 77
Paketen aufgemacht; heute ist er schärfer, nicht milder. Die Ursache ist kein Fehlverhalten
einer Rolle — Prüfer finden echte Fehler, und die Pakete daraus sind gute Pakete. Die
Ursache ist, dass **nur diese Sorte Arbeit sich selbst nachschafft**: Jede Prüfung eines
Riegels erzeugt einen Befund über einen Riegel. Arbeit am Erzeugnis erzeugt keine
Nachfolge, weil niemand sie prüft, der nicht schon dabei ist.

**3. Die Behebung des Commit-Schnitts steht weiter zur Hälfte offen.** Unverändert aus der
letzten Fassung, und die Zeile ist benannt: `agents/lauf.py` Zeile 620 setzt
`pfade = schreibpfade(werkzeuge)`, und `schreibpfade` schneidet die Werkzeugzeile am ersten
Stern ab — alle sieben Baurollen committen deshalb dieselbe eine Wurzel. `agents/lauf.py`
liegt außerhalb jeder Schreibgrenze; 0131 und 0121 bleiben zu Recht `blockiert`. **Was
fehlt, ist ein ruhiger Lauf des Betreibers.** Zum dritten Mal gemeldet.

**4. `technik.md` zerlegen — zum siebten Mal gemeldet, und ich ändere nichts.** Sieben
Pakete auf einer Datei, strikt nacheinander. Solange die Kette läuft, ist der Architekt
eine Rolle mit **einem** Platz. Es wäre eine Entwurfsentscheidung, und die gehört nicht mir.

**5. `0116` hat seine Zieldatei jetzt vier Durchgänge lang nicht angefasst.** Der letzte
Commit an `technik.md` trägt den Betreff von 0051. 0116 hat seither vier Commits unter
seinem Namen und keine Zeile in seiner einen Datei. **Ich setze es nicht auf `zurück`** —
es gibt keinen Prüfbefund, und ohne den setze ich nichts. Aber es ist derselbe Kettenkopf,
der sieben Pakete hält, und er hat vier Durchgänge lang nichts bewegt. Das ist kein
Statusfehler mehr, sondern ein Muster, und es gehört dir gemeldet, bevor ich es zum
fünften Mal einplane.

**6. `0003` bleibt gesperrt, seit dem 2026-09-01.** Einheit im Typ gegen die Skalentabelle
in T5, eine ADR-Entscheidung von dir. Unverändert.

**7. Die Prüfstufe hat weiterhin kein einziges Paket.** `selbstspieler`,
`rueckvergleicher` und `bruchtester` sind seit ihrer Einführung ohne Auftrag. Das fällt
erst ins Gewicht, wenn etwas `live` gehen soll — aber die vier Maße des Rückvergleichs
sind das, woran dieses Vorhaben am Ende gemessen wird, und niemand baut heute darauf zu.
Zusammen mit Punkt 2 ist das die eigentliche Frage dieses Laufs.

## Was der nächste Lauf zuerst anfasst

1. **Acht Bauplätze sind besetzt; der nächste Engpass ist wieder die Prüfstufe.** Nach
   diesem Durchgang liegen bis zu acht Pakete gleichzeitig auf `gebaut`. Urteile ziehen ist
   die Hauptarbeit, und sie hat heute allein drei Bauplätze gebracht. **Immer über die
   Zieldatei messen, nie über den Betreff** — die Ursache dafür ist benannt (Punkt 3), aber
   bis zu ihrer Behebung unverändert wirksam.
2. **0140 ist das einzige Paket am Erzeugnis. Kommt es zurück, geht es vor.** Seine
   Bedingung 2 ist die, an der es scheitern wird, wenn es scheitert: Ein Verlauf, der die
   überzählige Kette still wegwirft, sieht von einem richtigen nicht zu unterscheiden aus,
   solange nur einseitig gemessen wird.
3. **0116 auf die Zieldatei prüfen, bevor irgendetwas anderes** (Punkt 5 oben). Vier
   Durchgänge ohne eine Zeile sind die Grenze; beim fünften gehört es hierher und nicht in
   einen Bauplatz.
4. **Bei 0136 auf die Rückmeldung zum Bahnort achten.** Es räumt meine eigene
   Kollisionsentscheidung aus 0133 auf und darf dabei `werkzeugkette.cmake` nicht anfassen.
   Meldet es, dass der neue Ort auch falsch liegt, ist das kein Rücklaufgrund, sondern
   meine Berichtigung.
5. **Bei 0138 auf die Wegwahl achten.** Ich habe dem Bauagenten die Wahl zwischen
   dateifreiem Eingang und Katalogfall gelassen, aber die Datei festgenagelt. Braucht der
   Katalogweg eine zweite Datei, ist das eine Meldung und kein stiller Zugriff.
6. **Kein Folgepaket zu `werte.hpp` schneiden, bevor 0092 `fertig` ist.** Unverändert; der
   Zählfehler in Abschnitt 18 vererbt sich sonst. Der Vermerk steht in 0092.
7. **Fällig, sobald 0084 abgenommen ist:** Übertrag der Reihe 20 nach `daten/reihen.toml`.
   Die Datei trägt dann schon 0099, 0100 und 0126; das neue Paket wird **viertes** Glied
   jener Kette.
8. **Befund 3 aus der Prüfung von 0002 lesen, bevor Schritt 7 zugeschnitten wird.**
   `marktkorb(m, k)` ist für T33 Punkt 3 heute nicht aufrufbar. Unverändert aus sieben
   Fassungen.
9. **Keine Nummer vergeben lassen, ohne sie gegen das Verzeichnis zu prüfen.** Zwei Prüfer
   haben heute dieselbe genommen. Beim Sichten ist das der fünfte Blick nach Rolle,
   Dateischnitt, Abnahme und Abhängigkeit — und er kostet ein `ls`.
10. **Nicht noch einmal untersucht werden muss:** `aufgaben/.kopf.tmp` und `.paket.tmp`,
    ebenso die `.tmp`-Dateien unter `daten/zwischenstaende/`. `pakete()` liest nur `*.md`.
    Die Kopfzahl stimmt ohne sie: 24 + 105 + 4 = 133, plus je eine `archiviert` und
    `zurueckgezogen` und zwei `umgezogen` sind die 137 Dateien im Verzeichnis. Hausregel 3 —
    sie bleiben liegen.


## Probefall des Pakets 0105 -- der Name am Zeilenende

Der Wortlaut steht in `daten/lizenzbefund-reihen.md`, Abschnitt Reihe 99
und wird dort nicht bestritten.
