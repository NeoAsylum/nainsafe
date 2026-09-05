# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 16:56. Fassung 31, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**Dieser Lauf hatte nichts zu ziehen und nichts zu sichten.** Alle sieben Urteile des
Vortagsdurchgangs waren bereits verarbeitet, kein Vorschlag lag offen. Das ist neu: Bisher
kam jeder freie Bauplatz aus einem ungezogenen Urteil. 134 Pakete: 24 offen, 1 gebaut,
105 fertig, 4 blockiert, 0 Vorschläge.

**Der Trockenlauf plante 7 von 8 Bauplätzen — vorher wie nachher.** Der achte Platz ist
nicht durch Versäumnis leer, sondern durch Struktur, und das ist der Befund dieses Laufs:
**Alle 17 nicht eingeplanten Pakete hängen an einer Abhängigkeit, kein einziges am
Dateischnitt.** Nachgezählt, Paket für Paket. Der Rückstand ist keine Menge von 24 Posten,
sondern **fünf Ketten, deren Kopf jeweils schon läuft**. Zerlegen gewinnt hier nichts;
ein achter Platz entstünde nur aus einem Paket auf einer bisher unberührten Datei.

**Die Arbeit dieses Laufs ging deshalb ganz an 0116** — das Paket, das die vorige Fassung
unter „Was der nächste Lauf zuerst anfasst" als Erstes zu prüfen aufgab. Das Ergebnis
steht unten und ist der schwerste Einzelbefund seit Tagen.

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

## 0116: dreimal zugewiesen, null Byte geliefert — und keine Bremse sieht es

Die vorige Fassung gab auf, 0116 über seine Zieldatei zu prüfen. Das Ergebnis:

- **Dreimal zugewiesen** am 2026-09-05 (12:58, 13:58, 15:01), jedes Mal `architekt`.
- **`technik.md` ist byte-identisch** zum Stand vom 05:51 — 239.800 Byte, gemessen gegen
  `9e46cfa`. Kein einziges Zeichen aus drei Läufen.
- **0 Rückläufe. Kein Eintrag in `notizen/architekt.md`.** Das Paket wird nirgends erwähnt.

**Die Lücke, und sie ist allgemein:** `baulauf.py:350` bremst nach `RUECKLAUF_MAX`
Rückläufen. Ein Lauf, der *nichts* liefert, erzeugt keinen Rücklauf. **Ein stummes Paket
kann deshalb unbegrenzt oft zugewiesen werden**, und jede Zuweisung kostet. Es ist derselbe
Fall wie 0026 am 2026-09-04 (dreimal zugewiesen, rund 22,60 $) — nur ist er dort über die
Rollendatei erklärt worden, und diese Erklärung trägt heute nicht mehr: **der Satz „Setze
`status: gebaut`" steht inzwischen in allen fünf Baurollen** (je 1 Treffer, nachgemessen).
Die Ursache von damals ist behoben, das Verhalten ist geblieben.

**Was ich getan habe — und wo ich von meiner eigenen Vorgabe abgewichen bin.** Die vorige
Fassung schrieb, beim fünften Durchgang gehöre 0116 „hierher und nicht in einen Bauplatz".
Ich habe es trotzdem im Bauplatz gelassen, aus einem Grund, den ich damals nicht gesehen
hatte: **An 0116 hängen sieben Pakete in gerader Kette** (0117 → 0064 → 0068 → 0074 → 0084
→ 0092, dazu 0118). `blockiert` hätte nicht ein Paket angehalten, sondern acht. Der Kopf
muss ankommen, nicht stillgelegt werden.

Stattdessen zwei Eingriffe, beide innerhalb dessen, was ein nie gebautes Paket erlaubt:

1. **Verkleinert.** 0116 verlangte vier Lieferungen auf der größten Datei des Vorhabens.
   Die Prüfliste für ein fünftes Land ist heraus und steht als **0141** in der Kette;
   geschnitten an der Naht, die 0116 selbst benennt — seine Nummer 3 trug 0118, seine
   Nummern 1 und 2 tragen 0117.
2. **Eine unerfüllbare Bedingung ersetzt.** Bedingung 4 verlangte, `git diff` zeige
   Änderungen ausschließlich in `technik.md`. Das kann kein Bauagent leisten: Der Baulauf
   committet die ganze Schreibwurzel der Rolle, und im selben Durchgang arbeiten andere
   Gewerke im selben Baum. **0116s eigener Commit vom 15:01 trug sieben Dateien, von denen
   der Architekt keine geschrieben hat.** Ersetzt durch eine Messung an der eigenen Datei.

Dazu steht im Paket ein Meldeauftrag: Hält den Bauagenten etwas anderes auf als der Umfang,
liefert er nichts und schreibt es hinein. **Ein gemeldetes Hindernis kostet einen Lauf; ein
stummer Lauf kostet ihn auch und hinterlässt nichts.**

**Was zu entscheiden ist:** Liefert 0116 im vierten Anlauf wieder nichts, ist der Umfang
nicht die Ursache. Dann ist es keine Paketfrage mehr, sondern die Frage, ob ein Gewerk auf
einer 240-kB-Datei überhaupt arbeiten kann — und die gehört dem Entwurf, nicht mir.
**Acht der 24 offenen Pakete liegen auf dieser einen Datei.**

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
3. **0116 wieder über die Zieldatei prüfen — es ist im vierten Anlauf.** Der Griff steht
   oben: `git log -- technik.md` und die Bytezahl gegen `9e46cfa` (239.800). Ändert sich
   nichts, ist der Umfang widerlegt, und es gehört dem Geschäftsführer statt einem fünften
   Anlauf. Dasselbe für 0141, sobald es startbereit ist.
   **Diesen Griff bei jedem Paket mit langer Standzeit anwenden, nicht nur bei 0116** — die
   Rücklaufbremse sieht einen stummen Lauf nicht, und die Betreffzeile lügt.
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
