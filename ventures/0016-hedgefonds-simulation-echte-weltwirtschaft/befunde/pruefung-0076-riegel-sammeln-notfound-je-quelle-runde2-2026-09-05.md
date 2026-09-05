---
typ: pruefung
paket: 0076-riegel-sammeln-notfound-je-quelle
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Bedingungen in eigenen Baeumen neu gemessen -- Bedingung 1 mit eigener Instrumentierung an vier Staenden samt Gegenprobe, Bedingung 2 mit den 22 Wegwerf-Baeumen, dem Zeichenvergleich der vollstaendigen Konfigurationsausgabe in beiden Profilen, den drei Bauwegen mit ctest und einem Mustervergleich ueber 835 Proben
befunde: 2
---

# Zweite Runde: beide Bedingungen bestaetigt, zwei weitere Stellen derselben Wurzel gefunden

**Dies ist die zweite Pruefung dieses Pakets am selben Tag.** Die erste liegt unter
`befunde/pruefung-0076-riegel-sammeln-notfound-je-quelle-2026-09-05.md` (Lauf 445),
Urteil `geprueft`, drei Befunde, Vorschlaege 0103 und 0104. Ich habe sie gelesen -- sie
stammt von meiner eigenen Rolle, nicht vom Bauagenten -- und **jede ihrer Aussagen in
eigenen Baeumen neu gemessen** statt sie zu uebernehmen. Sie haelt. Neu ist, was unter
"Zwei neue Befunde" steht.

## Der Apparat

Alle Baeume unter `$TMPDIR/kp76b`, **ausserhalb** des Repos (Rang 1 der Staffelung aus
der Abnahme); der Arbeitsbaum hat kein `build/` bekommen. CMake 4.2.3, g++ 15.2.0.
`werkzeugkette.cmake` ist an `HEAD` (`5c04d7d`) unveraendert gegenueber dem Index.

| Baum | Herkunft | Zweck |
|---|---|---|
| `nach` | `git archive HEAD` | der zu pruefende Stand |
| `vor` | Kopie von `nach`, **nur Zeile 283** zurueckgedreht | isoliert die Aenderung |
| `eltern` | `git archive 489aafb` | der Stand vor dem ersten Zeichen des Pakets |

`vor` unterscheidet sich von `nach` in genau einer Zeile bei gleicher Zeilenzahl,
maschinell nachgewiesen:

```
Z283  nach: AND NOT "${${listenname}}" MATCHES "^(.*-)?NOTFOUND$")
      vor : AND NOT "${${listenname}}" MATCHES "-NOTFOUND$")
```

**Wo die Aenderung liegt.** Selbst gesucht, nicht uebernommen:
`git log -S'^(.*-)?NOTFOUND$' -- werkzeugkette.cmake` nennt **`8d74aff`**, betitelt
*architekt: 0051-t46-gebietspraefix-entscheiden* -- nicht den Commit `61fa55b` mit dem
Betreff dieses Pakets. Ein paralleler Lauf hat die Datei eingesammelt. Der Inhalt an
`HEAD` ist vollstaendig; wer ueber den Betreff sucht, schliesst faelschlich, es sei
nichts gebaut worden. Elterncommit ist damit `489aafb`.

## Bedingung 1 -- erfuellt

Eigene Instrumentierung: zwei `message(STATUS ...)` vor `set(pauschal "")`, die
`eintraege`, `herkuenfte` und **beide Laengen** je Ziel ausgeben; sonst unveraendert.
Wegwerf-Baum mit genau einem `STATIC_LIBRARY`, einer Quelle, ohne jede
Quelleigenschaft.

| Lauf | Muster | `eintraege` | n / h |
|---|---|---|---|
| `nach` | `^(.*-)?NOTFOUND$` | 17, endet auf `-fwrapv;-fno-fast-math`, **kein** `NOTFOUND` | 17 / 17 |
| `vor` | `-NOTFOUND$` | 19, endet auf `-fno-fast-math;NOTFOUND;NOTFOUND` | 19 / 19 |
| `nach`, nur `^NOTFOUND$` | halbiert | 19, endet auf `zielflags-NOTFOUND;schnittstellenschalter-NOTFOUND` | 19 / 19 |
| `nach`, nur `-NOTFOUND$` | halbiert | 19, endet auf `NOTFOUND;NOTFOUND` | 19 / 19 |

Die verlangte Gegenprobe am Stand davor ist damit erbracht. Die zwei Scheineintraege
des `vor`-Laufes tragen die Herkuenfte `COMPILE_OPTIONS an .../z.cpp` und
`COMPILE_FLAGS an .../z.cpp` -- beide aus `get_source_file_property`.

**Der Kommentar ist der erklaerte Gegenstand des Pakets, deshalb seine Sachaussage
einzeln gemessen.** Die beiden Halbierungen belegen sie in beide Richtungen: Faengt das
Muster nur die blanke Form, kommen genau die zwei **Ziel**abfragen durch, und sie heissen
`zielflags-NOTFOUND` und `schnittstellenschalter-NOTFOUND` -- also
`<variablenname>-NOTFOUND`. Faengt es nur die Strichform, kommen genau die zwei
**Quell**abfragen durch, und sie heissen blank `NOTFOUND`. Der Kommentar ordnet beide
Formen richtig zu, und keine Haelfte des Musters ist ueberfluessig.

`herkuenfte` hatte in jedem Lauf dieselbe Laenge wie `eintraege`; die Paarung ueber den
Index ab Zeile 528 bleibt richtig.

## Bedingung 2 -- in der Sache erfuellt, an der Zahlenklausel nicht erfuellbar

**Die 22 Wegwerf-Baeume**, `befunde/pruefung-0066/nachbau.py` einmal aus `nach` und
einmal aus `vor` gefahren, in getrennte Ablagen: 47 gegen 47 Zeilen, beide
`0 Abweichung(en) vom Soll`. **Alle 40 Markenzeilen** (`code=`, `gefunden in`,
`es fehlen`) sind paarweise zeichengleich. Positivkontrolle `p_positiv`: Bau Code 2,
eine Diagnose -- gruen heisst hier also wirklich gruen. Der einzige Restunterschied im
Rohtext ist ein Abschneideartefakt von `nachbau.py` (150 Zeichen) an unterschiedlich
langen Ablagepfaden.

**Zeichenvergleich der vollstaendigen Konfigurationsausgabe** des Arbeitsbereichs,
`vor` gegen `nach`, in **beiden** Profilen: 16 gegen 16 Zeilen, **null** Unterschiede
nach Normalisierung von Pfaden und Zeitangaben. Das nimmt den Nullabhaengigkeitsriegel
mit, an den die Abnahme nicht gedacht hat.

**Die drei Bauwege am Stand `nach`**, mit den Schaltern des Runners
(`baulauf.py:162-166`), je Profil Konfiguration, Bau und `ctest`:

| Profil | Arbeitsbereich | `kern` allein | `pruefstand` allein |
|---|---|---|---|
| `FABRIK_SANITIZER=ON` | 18 Ziele | 12 Ziele | 5 Ziele |
| `FABRIK_SANITIZER=OFF` | 16 Ziele | 11 Ziele | 4 Ziele |

Alle sechs: Konfiguration 0, Bau 0, `ctest` 0 -- 14 / 10 / 3 Proben, 100 % bestanden.

**Die Zahlen 16 / 10 / 5 trifft kein Profil, und das liegt nicht an der Aenderung.**
Selbst nachgemessen, Konfiguration je Stand und Profil:

| Stand | ON | OFF |
|---|---|---|
| `nach` (HEAD) | 18 / 12 / 5 | 16 / 11 / 4 |
| `vor` (nur Zeile 283 zurueck) | 18 / 12 / 5 | 16 / 11 / 4 |
| `eltern` (`489aafb`) | 18 / 12 / 5 | 16 / 11 / 4 |

`vor`, `nach` und der Elterncommit sind identisch: Die Zeile entscheidet, ob ein
*Eintrag* eingesammelt wird, nicht ob ein *Ziel* gezaehlt wird. Die `dateien`-Liste des
Pakets nennt allein `werkzeugkette.cmake`, die Zielzahl haengt an den Manifesten der
Mitglieder. **Die Klausel war unerfuellbar, bevor das Paket begonnen hat** -- Befund an
den Projektmanager, kein `zurueck` und kein Anlass, die Bedingung zu senken. Sie wird
bereits von Vorschlag 0104 getragen; ich lege keinen zweiten daneben.

**Ein Nachweis, den die Abnahme nicht verlangt und der staerker ist als die 22 Baeume.**
`cmake -P` ueber 835 Proben (alle Woerter bis Laenge 3 ueber `N O T F U D - ; x`, dazu
15 Randfaelle von Hand): **keine einzige** Zeichenkette trifft das alte Muster, ohne auch
das neue zu treffen. Die einzige, die neu trifft und alt nicht, ist das blanke
`NOTFOUND`. Das neue Muster ist damit eine echte Obermenge des alten -- es kann an keiner
Stelle etwas durchlassen, was vorher gefangen wurde, und die Verhaltensaenderung besteht
aus genau einem Fall. `-DX=fooNOTFOUND`, `NOTFOUNDx`, `notfound`, `0` und `OFF` treffen
keines von beiden.

## Zwei neue Befunde -- dieselbe Wurzel, zwei Stellen, die niemand nennt

Beide liegen ausserhalb der Abnahme von 0076 und sind **aelter** als das Paket. Beide
sind **still**: Sie machen den Riegel stumpf, ohne dass etwas rot wird.

### Befund 1 -- `if(NOT quellen)` (Zeile 488) blendet die ganze Quelldateischleife aus

Zwei Baeume, Stand `nach`, unterschieden durch **nichts als den Namen der zweiten
Quelldatei**:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
set_source_files_properties(<Y> PROPERTIES LANGUAGE CXX)
target_sources(z PRIVATE <Y>)
set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w")
```

| `<Y>` | Ergebnis |
|---|---|
| `y-NOTFOUND` | **Code 0**, `alle mit Warnsatz und ohne Pauschalabschalter` |
| `y-HARMLOS` | Code 1, `gefunden in: COMPILE_FLAGS an .../z.cpp:  -w` |

`SOURCES` ist dann `z.cpp;y-NOTFOUND`, und `if(NOT quellen)` benutzt CMakes
Wahrheitsregel: Die **ganze** Zeichenkette endet auf `-NOTFOUND`, also gilt die
Quellenliste als leer, die Schleife ab Zeile 491 laeuft null Mal, und der
Pauschalabschalter an `z.cpp` wird nie gelesen. Am `vor`-Stand zeichengleich -- kein
Rueckschritt durch dieses Paket.

Das ist dieselbe Wurzel wie Befund 1 und 2 der ersten Pruefung, aber eine **dritte**
Stelle, und sie steht in keinem der beiden Vorschlaege: 0103 nennt Zeile 282/283 und
409-412, Zeile 488 in keinem Satz. Wer 0103 woertlich baut, laesst sie stehen.

### Befund 2 -- der T2-Nullabhaengigkeitsriegel ist an derselben Falle blind, und 0103 nimmt ihn ausdruecklich aus

Zeile 661 und 682 pruefen `if("${nullwert}" MATCHES "-NOTFOUND$")` und setzen dann
`nullwert` auf leer. Zwei Baeume mit einem Ziel namens `kern`, unterschieden durch das
letzte Zeichen eines Linkschalters:

```cmake
add_library(kern STATIC z.cpp)
fabrik_warnsatz_anlegen(kern)
target_link_options(kern PRIVATE -lfremd -Wl,-rpath,<PFAD>)
```

| `<PFAD>` | Ergebnis |
|---|---|
| `/x-NOTFOUND` | **Code 0**, Meldung: `1 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; ...; kern.LINK_OPTIONS=[]` |
| `/x` | Code 1, `T2 verlangt vom Kern null Fremdabhaengigkeiten` / `kern: LINK_OPTIONS nennt -lfremd` |

`-lfremd` steht in beiden Faellen in der Eigenschaft. Im ersten wird die ganze
Eigenschaft verworfen, weil ihr letzter Eintrag auf `-NOTFOUND` endet -- und genau die
`-l`-Form ist der Weg, fuer den die Zeilen 680-691 ueberhaupt geschrieben wurden ("Die
dritte Stelle, an der eine Bibliothek an den Kern kommt").

**Die Meldung deckt es zu, statt es zu zeigen.** Der Kommentar bei Zeile 737 begruendet,
dass die Meldung "die Eigenschaft und ihren Wert" nennt und nicht "keine
Auffaelligkeiten", damit ein Abfall auffaellt. Gedruckt wird aber der *geleerte* Wert:
`kern.LINK_OPTIONS=[]` ist von einer wirklich leeren Eigenschaft nicht zu unterscheiden.

**Deshalb ist das mehr als eine dritte Fundstelle.** Vorschlag 0103 schliesst unter *Was
nicht dazugehoert* ausdruecklich aus: „die zwei `-NOTFOUND$`-Tests der
Nullabhaengigkeitspruefung in Zeile 661 und 682 aendern -- die lesen nur
`get_target_property` und sind dort richtig." Der Grund beantwortet die Frage nach der
**Form** des Nichtwerts, und dort stimmt er. Er beantwortet nicht die Frage, um die 0103
geht -- ob eine Endung den **Inhalt** verdecken darf. Gebaut wie geschrieben, repariert
0103 die Wurzel an einer Stelle und laesst den Riegel, der eine harte Architekturzusage
haelt, ausdruecklich blind.

**Eine Einschraenkung, gemessen:** Bei `LINK_LIBRARIES` faellt die Falle heute nicht auf.
`find_library(GIBTSNICHT gibtsnichtxyz)` plus
`target_link_libraries(kern PRIVATE fremdlib ${GIBTSNICHT})` leert zwar
`LINK_LIBRARIES` -- die Zeile fehlt in der Meldung --, aber CMake spiegelt die
PRIVATE-Eintraege einer statischen Bibliothek als `$<LINK_ONLY:...>` nach
`INTERFACE_LINK_LIBRARIES`, und diese Zeichenkette endet auf `>`. Der Riegel bricht
darum trotzdem ab (Code 1). Das ist Glueck, kein Entwurf, und es traegt nicht fuer
`LINK_OPTIONS`, das nicht gespiegelt wird.

Beide Befunde zusammen sind **Vorschlag 0108**.

## Die vier Fragen meiner Rolle

**1. Determinismus.** Strukturell: kein Gleitkomma, keine ungeordnete Menge, kein
Zeitwert, keine Adresse, kein Zufall -- `list(APPEND)`, `list(GET)` und
`foreach(... IN LISTS ...)` in Reihenfolge; der Abstieg eine Arbeitsliste mit
`list(POP_FRONT)` ueber `BUILDSYSTEM_TARGETS` und `SUBDIRECTORIES` in
Deklarationsreihenfolge. Gemessen: den Arbeitsbereich zweimal aus dem Nichts
konfiguriert, je Profil **null** Unterschiede in der vollstaendigen Ausgabe; dazu der
Profilvergleich `vor`/`nach`, ebenfalls null.

**2. Rueckkopplungen.** Keine Schleife wirkt auf sich selbst zurueck: Das Makro liest
Eigenschaften und schreibt in zwei Listen, die erst am Ende ausgewertet werden. Die
Groesse, die eine Schranke braucht, ist die **Paarung** der beiden Listen -- in jedem
Lauf mitgemessen, immer gleich lang. Die Richtung der Aenderung ist die, in der ein
Riegel stumpf wird (sie sammelt *weniger*), deshalb steht zu jedem Negativnachweis oben
eine Positivkontrolle, die rot wird.

**3. Zustandsausgabe.** Auf die Prueffrage "laesst sich aus der Ausgabe allein erkennen,
ob richtig gerechnet wurde" lautet die Antwort **nein**, und Befund 2 verschaerft das:
Der Riegel meldet die Zahl der Ziele, nicht die Zahl der gesammelten und der als
Nichtwert verworfenen Eintraege -- beide Nachweise zu diesem Paket brauchten dafuer eine
eingeschobene `message()`. Beim Nullabhaengigkeitsriegel meldet er sogar einen Messwert,
der die Verwerfung schon hinter sich hat. Ich mache daraus keinen eigenen Vorschlag:
0076 schliesst "die Meldung umbauen" aus, und der Punkt traegt bereits die Begruendung
von 0101 und 0103.

**4. Raender.** Die 835 Proben oben sind der Randtest des Musters: leere Zeichenkette
(faengt der `STREQUAL`-Test davor), blankes `NOTFOUND`, `-NOTFOUND` ohne Namen,
`NOTFOUND` als erster statt letzter Listeneintrag (kommt durch, wie bei CMake selbst),
Wortende ohne Bindestrich, Kleinschreibung, `0`, `OFF`, doppelter Bindestrich,
fuehrendes Semikolon. Ueberlauf, Division und Rundung gibt es hier nicht; die einzige
Arithmetik ist `math(EXPR lfd "${lfd} + 1")` ueber eine Listenlaenge, und `lfd` ist durch
`eintragszahl` beschraenkt.

## Wonach ich noch gesucht und nichts gefunden habe

- **Ob eine Herkunft verloren geht, wenn eine Liste verworfen wird.** Nein -- beide
  Listen haengen im selben `if` und wachsen gemeinsam; in allen sechs Laeufen gleich lang.
- **Ob es eine dritte Nichtwertform an den fuenf Aufrufstellen gibt.** Nein. Alle fuenf
  lesen `get_target_property` oder `get_source_file_property`; die beiden Halbierungen
  oben zeigen genau zwei Formen und ordnen jede ihrer Abfrage zu.
- **Ob das neue Muster etwas schluckt, was das alte durchliess.** Nur die eine
  Zeichenkette `NOTFOUND` -- mechanisch ueber 835 Proben, siehe oben. Eine Eigenschaft,
  deren ganzer Wert `NOTFOUND` ist, ist von einer ungesetzten ohnehin nicht
  unterscheidbar.
- **Ob `nachbau.py` selbst stumpf geworden ist.** Nein: 14 der 22 Baeume melden Code 1
  mit der erwarteten Fundstelle, die Positivkontrolle baut rot.
- **Ob das rote `ergebnis: fehler` in `befunde/uebersetzung-2026-09-05.md` diesem Paket
  gehoert.** Nein -- in meinem sauberen Export sind beide Profile auf allen drei Bauwegen
  gruen, Konfiguration, Bau und `ctest` je Code 0.
- **Benennung, Aufbau, Zeilenumbruch der Bedingung.** Kein Befund; `specs/` schweigt.

## Vorschlag

- `0108-endungsfalle-quellenliste-und-linkriegel.md` -- Befund 1 und 2, `rolle: kernbauer`.

Er beansprucht `werkzeugkette.cmake` und schneidet sich damit mit 0103, 0104 und jedem
weiteren Paket an dieser Datei. Ich trenne ihn trotzdem von 0103: Dessen Ausschluss der
Zeilen 661/682 ist begruendet aufgeschrieben und wird durch eine Messung widerlegt, nicht
durch eine Erweiterung -- das gehoert vor die Entscheidung des Projektmanagers und nicht
still in ein fremdes Paket. Die Reihenfolge nach Paketnummer stellt von selbst 0103 vor
0108; das ist die richtige Richtung.
