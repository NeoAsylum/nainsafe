# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-04 22:20. Fassung 23, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**`kern::werte` ist gebaut und geprüft — die Datei, die vier Pläne lang bei 78 Byte stand.**
Zwei Abnahmen, vier Vorschläge entschieden, kein neues Paket erfunden. 88 Pakete: 18 offen,
1 gebaut, 66 fertig, 3 blockiert, **0 Vorschläge**. Alle vier Bauplätze belegt, einer davon
mit Vorrang Nr. 5.

## Zwei Abnahmen

| Paket | Rolle | Befund | jetzt |
|---|---|---|---|
| `0002-fondsbewertung-definieren` | `kernbauer` | `geprueft`, 3 Nebenbefunde, keiner ein Rücklaufgrund | `fertig` |
| `0067-belegstellenriegel-abschnittszitate` | `testentwickler` | `geprueft`, 1 Nebenbefund aus der Prüfung selbst | `fertig` |

**0002 ist der Vorrang Nr. 2 und die eine Zahl.** Gemessen statt geglaubt:

| Datei | letzter Plan | jetzt |
|---|---|---|
| `kern/include/kern/werte.hpp` | 78 Byte | 17.036 |
| `kern/src/werte.cpp` | gibt es nicht | 32.869 |
| `kern/test/werte_probe.cpp` | — | 27.962 |

Geprüft am Stand `ceebee3`, in **beiden** Bauprofilen, aus `git archive HEAD` in einen Baum
außerhalb des Repos — nicht im Arbeitsbaum, in dem parallele Läufe Zwischenstände
hinterlassen. Alle sechs Abnahmebedingungen einzeln, die T47-Zahlenprobe von Hand
nachgerechnet, dazu **23 Sabotagen** am fertigen Modul. Das ist die gründlichste Prüfung,
die dieses Vorhaben bisher gesehen hat, und sie hat vier echte Lücken gefunden — in den
Proben, nicht im Code.

## Der Fund des Laufs: zwei Pakete kollidieren, ohne dass sich ihre Dateilisten schneiden

Aus der Prüfung von 0002 kamen zwei Vorschläge, beide angenommen:

- **0088** (`testentwickler`) — vier Vorgaben aus T47/T48/T33 lassen sich heute verletzen,
  ohne dass eine Probe rot wird. Datei: `kern/test/werte_probe.cpp`.
- **0087** (`kernbauer`) — `plus`/`minus` gehören nach `festkomma.hpp`, nicht in den
  anonymen Namensraum von `werte.cpp`. Dateien: `festkomma.hpp`, `werte.cpp`,
  `festkomma_probe.cpp`.

**Die Listen schneiden sich nicht. Der Baulauf hätte beide gleichzeitig eingeplant, und
0088 wäre ohne Verschulden gescheitert.** Denn 0088 führt jeden seiner vier Nachweise durch
eine **Mutation an `kern/src/werte.cpp`** — der Datei, die 0087 umbaut. Der Prüfer misst am
dann geltenden `HEAD`.

Das ist eine neue Bauart derselben alten Falle: `dateien` serialisiert *Schreibzugriffe*
und sagt nichts über ein Paket, dessen **Nachweisverfahren** an einer fremden Datei hängt.
Bisher kannte ich sie nur für Abnahmekriterien, die eine fremde Datei zum Maßstab nehmen
(daran ist 0027 zweimal gescheitert). Geheilt mit `haengt_an` in 0087, ausdrücklich als
Reihenfolgesperre gekennzeichnet, damit sie niemand später für eine sachliche
Abhängigkeit hält.

**Die Reihenfolge ist auch sachlich richtig:** erst das Netz, dann der Umzug. 0087
verschiebt Rechenwerk aus einem Modul, das gerade erst abgenommen wurde; die vier Proben
aus 0088 sind hinterher der Nachweis, dass der Umzug nichts bewegt hat.

## Die anderen beiden Vorschläge

**0086** (`vorschlag` → `offen`) mit zwei Änderungen an der Abnahme. Erstens ist die
**Zahl 24 heraus**: Sie stammt aus einer Summe, in die drei andere offene Pakete auf
derselben Datei schreiben, und mindestens eines läuft vorher. Geprüft wird jetzt die
Bedingung — vorher nicht gefangen, nachher gefangen, gemessen am selben Baum. Siebter Fall
derselben Bauart. Zweitens läuft **0089** dort als Nebenzeile mit.

**0089** (`vorschlag` → `fertig`, zusammengefasst in 0086). Der Vorschlag hat selbst darum
gebeten — dieselbe Rolle, dieselbe einzige Datei, derselbe Kopfkommentar, und 0086 ist noch
nicht angefangen. Ein eigener Lauf für eine berichtigte Paketnummer wäre der teuerste Weg
zu einer Zeile.

Die Sache dahinter ist es wert, gelesen zu werden: Der Kopfkommentar des Riegels trägt eine
*Berichtigung*, die aufschreibt, dass der Commit-Betreff hier regelmäßig ein anderes Paket
nennt als die Arbeit darin — **und nennt im Beispiel daneben selbst die falsche Nummer**,
weil ihr Verfasser den Betreff gelesen hat. 0004 statt 0007. Der Prüfer hat den Fehler bei
sich selbst gefunden und ihn gemeldet, statt ihn stehen zu lassen.

## 0061 bleibt gesperrt, und diesmal gegen eine neue Tatsache

Der Betreiber hat um 18:17 (`cf6331b`) den fehlenden Abschnitt *„Wenn du fertig bist"* in
`testentwickler.md` ergänzt — er fehlte während **aller drei** Leerläufe dieses Pakets. Das
ist eine echte, datierte Ursache außerhalb meiner Rolle, und das Paket kündigt ein
Entsperren an, „sobald die Ursache bekannt ist".

**Sie entsperrt trotzdem nicht.** Das Paket hatte zwei Symptome, der Eingriff heilt eines:

| Symptom | erklärt durch `cf6331b`? |
|---|---|
| dreimal derselbe Bauplatz, Status blieb `offen` | ja, vollständig |
| keine Zeile an der Zieldatei | **nein** — ein fehlender Abschluss-Abschnitt verhindert keinen Schreibvorgang |

Die Sperre steht auf dem zweiten. Und die naheliegende Rettung — „das ist doch nur die
bekannte Bündelung, der Betreff lügt" — trägt hier nicht: Die Messung folgt der
**Zieldatei** (`git log -- pruefstand/test/vorrat_kernanker_probe.cpp`), nicht dem Betreff,
und ist damit gegen genau diesen Fehler immun. Der letzte Eintrag bleibt `f68e8fb` vom
2026-09-03 aus einem fremden Paket.

Auslöser für meinen nächsten Lauf steht im Paket: liefert der `testentwickler` nach dem
18:17 an irgendeiner Datei unter `pruefstand/`, geht 0061 ohne Änderung auf `offen`.

## An den Geschäftsführer

**1. Der Vorrang ist erfüllt — und der vierte Bauplatz geht trotzdem an die
Belegstellen-Familie.** Nr. 1 (0026), 2 (0002) und 3 (0071) sind `fertig`, Nr. 4 (0027)
steht in der Prüfung, Nr. 5 (0010) hat einen Bauplatz. Nachgemessen mit
`--trocken --gleichzeitig 12`: **sieben Pakete sind startbereit, vier bekommen einen Platz.**

| Platz | Paket | Rolle |
|---|---|---|
| 1 | `0010-zustandsausgabe-drei-ebenen` | kernbauer (**Vorrang 5**) |
| 2 | `0043-t48-groessen-gegenkraft-5` | architekt |
| 3 | `0069-t2-linkriegel-in-der-werkzeugkette` | kernbauer |
| 4 | `0073-belegstellenriegel-dateiname-weiter-links` | testentwickler |
| — | `0078-reihentoml-preisbasis-nach-t53-nachziehen` | **datenbauer, verliert an drei Nummern** |
| — | `0085-abbruchmeldungen-im-wortlaut-pruefen` | testentwickler |
| — | `0088-werte-probe-vier-unbelegte-vorgaben` | testentwickler |

Dein Plan sagt: *„Nichts aus der Belegstellen-Familie in dieser Woche."* Platz 4 geht
dorthin, und der Verlierer ist **0088** — das Paket, das die vier Lücken im gerade
abgenommenen Kern schließt. Ursache ist nicht meine Wahl, sondern `sorted(glob)`
(`baulauf.py:210, 301`): 0073 ist älter als 0088, und der Bauplatz geht nach Nummer, nicht
nach Vorrang. **Ich habe 0073 nicht künstlich gesperrt** — es ist ein gültiges offenes
Paket, und `blockiert` ohne technische Ursache wäre eine Falschaussage im Statusfeld.

Wenn dir die Reihenfolge wichtiger ist als das Dienstalter, ist das eine Änderung an
`baulauf.py` und deine Entscheidung. Das ist der dritte Fall, in dem diese Regel das
Falsche einplant; die beiden vorigen hießen 0027.

**2. Der Datenbauer läuft zum vierten Plan in Folge leer.** 0078 ist seine einzige Arbeit,
die Datei (`reihen.toml`) ist frei, und er verliert an drei ältere Nummern. Ich stelle die
Frage nicht neu, ich lege nur den Messwert daneben.

**3. Eine Vorgabe aus T50 wirft drei Fehlalarme, und ich lege dafür kein Paket an.**
Abnahmebedingung 2 von 0002 verlangt, dass `tsd_in_cent` und `lobbypunkte_aus` nur in einer
Datei vorkommen. Ausgeführt liefert der Mustervergleich drei Treffer außerhalb — **alle
drei Prosa in Kommentaren**, aus 0052 und 0077, beide älter als 0002. Die Sache, die T50
sichert, ist gehalten; verletzt ist nur ihr Nachweis, **und der Bauagent hätte ihn nur
erfüllen können, indem er außerhalb seiner `dateien`-Liste schreibt. Das Kriterium war
meines und war falsch.** Die Heilung (auf Aufrufe zielen, `tsd_in_cent(` mit Klammer)
wäre eine Änderung an `technik.md`, wo bereits fünf Architektenpakete warten. Ob ein
sechstes den Vorrang wert ist, entscheidest du. Der Anlass ist nicht kosmetisch: Käme
dieser Riegel wie der `belegstellen_riegel` in die Werkzeugkette, wäre der Bau am ersten
Tag rot.

**4. 0041 trägt weiter `rolle: geschaeftsfuehrer`** und steht auf `blockiert`. Diese Rolle
ist nicht in `BAUROLLEN`; kein Runner zieht das Paket je. Unverändert seit dem letzten
Plan, hier nur damit es nicht aus dem Blick fällt.

## Was der nächste Lauf zuerst anfasst

1. **Prüfbefund zu 0027 auswerten.** Es steht bei zwei Rückläufen von drei, und 0072 hängt
   daran. Wird es `geprueft`, fällt mit `zustand.hpp` auch die Sperre für 0072.
2. **Angekündigter Auslöser 0061** (siehe oben) — ich ziehe ihn selbst.
3. **Fällig, sobald 0043 abgenommen ist:** Es meldet, welche der fünf neuen T48-Größen eine
   Schnittstelle in `kern::werte` brauchen. Daraus wird das Folgepaket geschnitten — und
   `werte.hpp`/`werte.cpp` sind seit heute frei dafür.
4. **Fällig, sobald 0084 abgenommen ist:** Übertrag der Reihe 20 nach `daten/reihen.toml`
   (Datenbauer). 0078 hat sie ausdrücklich herausgehalten.
5. **Befund 3 aus der Prüfung von 0002 lesen, bevor Schritt 6 zugeschnitten wird.**
   `marktkorb(m, k)` ist für T33 Punkt 3 heute nicht aufrufbar — der `Schreiber` gibt
   keinen `Zustand` mit dem laufenden Stand heraus. Die Heilung liegt an einer von zwei
   Stellen, und welche richtig ist, hängt daran, was Schritt 6 sonst braucht. Weder der
   Prüfer noch ich raten das.
