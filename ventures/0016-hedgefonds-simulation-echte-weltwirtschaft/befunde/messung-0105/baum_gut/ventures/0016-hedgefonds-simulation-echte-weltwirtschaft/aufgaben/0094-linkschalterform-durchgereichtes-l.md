---
id: 0094-linkschalterform-durchgereichtes-l
rolle: kernbauer
status: fertig
haengt_an: [0069-t2-linkriegel-in-der-werkzeugkette, 0076-riegel-sammeln-notfound-je-quelle]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, mit einer Änderung an `haengt_an`

## Nachtrag 2026-09-05, zweiter Lauf: 0076 ist fertig, und du bist der Kopf einer Kette

**Beide Abhängigkeiten sind erfüllt** — 0076 ist nach drei Prüfungen abgenommen. Dieses
Paket ist startbereit und braucht nichts mehr.

**Es halten jetzt vier Pakete `werkzeugkette.cmake`: `0094` (dieses) → `0103` → `0104` →
`0108`.** Du läufst zuerst und hast damit als einziges keinen fremden Vorher-Stand zu
berücksichtigen. Die drei hinter dir tragen ihren jeweiligen Vorgänger in `haengt_an`, **als
Kollisionsschutz gekennzeichnet, nicht als sachliche Abhängigkeit** — `startbereit()`
vergleicht `dateien` nur unter `offen` (`baulauf.py:273`), und sobald du auf `gebaut` gehst,
wäre dein Anspruch sonst unsichtbar, während dein Prüfer an derselben Datei misst.

**Für dich folgt daraus nur eines:** Nenne im Nachweis den Stand, gegen den du misst. Was du
hinterlässt, ist der Vorher-Stand von 0103.

Vier Prüfungen: **Rolle** `kernbauer` steht in `BAUROLLEN`. **Abnahme** prüfbar, beide
Bedingungen mit Rot- und Grünnachweis am selben Baum. **Abhängigkeit** 0069 ist im selben
Lauf `fertig` geworden. **Dateischnitt** — dazu die Änderung:

**`0076-riegel-sammeln-notfound-je-quelle` steht jetzt in `haengt_an`, und zwar als
Reihenfolgesperre, nicht als sachliche Abhängigkeit.** Deine Begründung, warum das
inhaltlich zwei verschiedene Durchgänge sind, stimmt und bleibt stehen; hier geht es allein
um die Reihenfolge. Der Grund, warum die bloße Kollision auf `werkzeugkette.cmake` nicht
reicht: `startbereit()` vergleicht die Dateilisten **nur unter `offen`**
(`baulauf.py:273`). Sobald 0076 auf `gebaut` steht, ist sein Anspruch unsichtbar — dieses
Paket würde eingeplant, während der `kern-pruefer` 0076 an derselben Datei misst, und zwar
am dann geltenden `HEAD`. Das ist die Falle, an der 0027 zweimal schuldlos gescheitert ist.
`haengt_an` löst erst bei `fertig`, die Kollision also für die ganze Prüfstufe mit.

**Zur Nummer:** Deine Wahl war richtig. `0092-linkschalterform-durchgereichtes-l.md` steht
auf `umgezogen` und zeigt hierher; die Kennung 0092 behält
`0092-abschnitt-18-zwei-zaehlfehler`, weil sie zuerst dastand. Von mir ist nichts zu
bereinigen.

---

# Der vierte Durchgang des Nullabhaengigkeitsriegels sieht `-Wl,-lz` nicht — und `-Wl,-lz` steht auf der Linkerzeile

Vorgeschlagen vom `kern-pruefer` aus der Pruefung zu Paket 0069
(`befunde/pruefung-0069-t2-linkriegel-in-der-werkzeugkette-2026-09-04.md`,
`urteil: geprueft`). **Paket 0069 ist erfuellt**; was hier steht, liegt ausserhalb
seiner Abnahme — der Durchgang ueber die Linkschalter ist dort ausdruecklich als
„ueber die Abnahme hinaus" gefuehrt — und ist kein Befund gegen es.

> **Zur Nummer.** Zuerst als `0092` geschrieben, dann auf `0094` gewichen: Zwischen dem
> Lesen der hoechsten Nummer und dem Schreiben hat ein paralleler Lauf `0092` mit
> `0092-abschnitt-18-zwei-zaehlfehler` belegt. `mv` steht mir nicht zur Verfuegung,
> deshalb steht unter `0092-linkschalterform-durchgereichtes-l.md` nur noch ein Zeiger
> hierher. Diese Datei ist die gueltige Fassung.

## Der Messwert

`werkzeugkette.cmake:661` prueft die Eintraege aus `LINK_OPTIONS` und
`INTERFACE_LINK_OPTIONS` auf zwei Formen:

```cmake
if("${eintrag}" MATCHES "^-l." OR "${eintrag}" MATCHES "\\.(a|so)$")
```

Beide Muster greifen am **Anfang** beziehungsweise am **Ende** des ganzen Eintrags. Der
Uebersetzungstreiber reicht einen Linkerschalter aber in der Form `-Wl,<schalter>`
durch, und dieser Eintrag beginnt mit `-W` und endet auf `z`. Gemessen am 2026-09-04 am
unveraenderten Arbeitsbaum, die Angriffszeile ueber `-DCMAKE_PROJECT_INCLUDE`
eingehaengt (`befunde/pruefung-0069/angriff-c-linkerzeile.cmake`):

```
cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}"
               CALL target_link_options kern INTERFACE "-Wl,-lz")

-- Nullabhaengigkeitsriegel (T2): 1 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[];
   kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[];
   kern.INTERFACE_LINK_OPTIONS=[-Wl,-lz]
-- Configuring done
   → Code 0
```

Der Riegel meldet Vollzug. Auf der Linkerzeile steht der Schalter trotzdem — dieselbe
Konfiguration, `cmake --build --target festkomma_probe -v`:

```
/usr/bin/c++ -Wl,-lz -Wl,--dependency-file=… festkomma_probe.cpp.o -o festkomma_probe libkern.a
```

Auf diesem Rechner scheitert der Bau danach an `cannot find -lz`, weil zlib hier nicht
installiert ist. Das ist der Zufall der Maschine und nicht der Riegel: Auf einem
Rechner mit der Bibliothek waere der Bau gruen, die Fremdabhaengigkeit haengte an jeder
Probe, und die einzige Stelle, an der sie noch dastuende, waere der Messwert in der
Statuszeile.

`INTERFACE` und nicht `PRIVATE` ist dabei die wirksame Form und keine Feinheit: `kern`
ist eine statische Bibliothek und wird selbst nie gelinkt. Ein Linkschalter an ihr wird
allein ueber die Schnittstelle wirksam — und landet dann bei **jedem**, der sie linkt.

## Was gebaut wird

Zwei Dinge, beide klein und beide in derselben Funktion.

**Erstens: der Abgleich sieht Woerter statt Eintraege.** Der Riegel eine Ebene hoeher —
der gegen Pauschalabschalter, `werkzeugkette.cmake:506` — hat genau dieses Problem schon
geloest und dafuer eine Zerlegung: `string(REPLACE "SHELL:" …)`, dann
`string(REGEX REPLACE "[$<>:,]" " " …)`, dann `separate_arguments`. Ein `-Wl,-lz` zerfaellt
daran in `-Wl` und `-lz`, und `^-l.` trifft. Dieselbe Zerlegung an derselben Datei ein
zweites Mal zu benutzen ist kein neuer Apparat, sondern der Grund, warum sie dort als
benannte Folge steht.

**Zweitens: die verbleibende Grenze wird ausgeschrieben.** Auch mit der Zerlegung bleibt
die Endungsliste `.a|.so` eine Aufzaehlung, die eine dritte Endung (`.dylib`, `.so.1`)
nicht kennt. `befunde/messung-0069/nachweis.md` fuehrt diese Luecke bereits unter „Was
der Riegel nicht sieht"; die durchgereichte Form fehlt dort. Nach dem Grundsatz aus der
Abnahme von 0069 — *„Was der Riegel nicht sieht, muss dastehen"* — gehoert sie in
denselben Absatz, und zwar im Kommentar der Datei und nicht nur im Nachweis.

## Warum das ein eigenes Paket ist

- **Nicht Teil von 0069.** Dessen Abnahme kennt drei Bedingungen, und keine nennt die
  Linkschalter. Der Durchgang darueber ist im Nachweis ausdruecklich als Zugabe
  gefuehrt. Ein bestandenes Kriterium wird nicht nachtraeglich angehoben.
- **Nicht Teil von 0076** (`riegel-sammeln-notfound-je-quelle`, `offen`). Das arbeitet
  an `fabrik_riegel_sammeln`, also am Sammeln fuer den **Warnsatz**durchgang; hier geht
  es um den Abgleich im **Nullabhaengigkeits**durchgang daneben, der gar nicht sammelt.
- **Nicht Teil eines Testpakets.** Es aendert Erzwingung, keine Probe.

**Dateischnitt, offen benannt:** `werkzeugkette.cmake` ist zurzeit von `0076` (`offen`)
beansprucht. Dieses Paket schneidet sich damit und gehoert dahinter eingeplant. Das ist
die Entscheidung des Projektmanagers, nicht meine.

## Abnahme

1. **Der Riegel faellt rot aus**, wenn `kern` oder `kern_geprueft` in einer der beiden
   Linkschaltereigenschaften einen durchgereichten Bibliotheksschalter traegt. Nachweis:
   `target_link_options(kern INTERFACE "-Wl,-lz")`, konfiguriert, Fehlerausgabe im
   Wortlaut. Die Angriffszeile wird nicht ins Wurzelmanifest geschrieben, sondern ueber
   `-DCMAKE_PROJECT_INCLUDE=<datei>` eingehaengt — dann bleibt der Arbeitsbaum unberuehrt
   und es braucht keine Abschrift; der Weg ist in `befunde/pruefung-0069/` vorgemacht.
2. **Die Sanitizerschalter bleiben gruen.** `kern_geprueft` traegt
   `-fsanitize=undefined,address` und `-fno-sanitize-recover=all` erlaubterweise in
   derselben Eigenschaft. Sie duerfen nach der Zerlegung kein Muster treffen — sonst ist
   der Riegel zu scharf und der Arbeitsbaum rot. Nachweis: derselbe Baum ohne
   Angriffszeile, Code 0, mit dem gelesenen Wert in der Meldung.

---

# Nachweis -- Kernbauer, 2026-09-05

**Bezugsstand:** Commit `564d4b8` (`projektmanager: 0016-hedgefonds-simulation-echte-
weltwirtschaft (12 Dateien)`), ausgepackt mit `git archive HEAD ventures specs` nach
`$TMPDIR`. Geaendert habe ich allein `werkzeugkette.cmake`; jede Angriffszeile ist ueber
`-DCMAKE_PROJECT_INCLUDE` eingehaengt, der Arbeitsbaum bleibt sonst unberuehrt. Was hier
steht, ist der Vorher-Stand von 0103.

`specs/` gehoert mit ausgepackt. Ohne das Verzeichnis bricht der `belegstellen_riegel`
aus einem ganz anderen Grund ab, und der Vorher-Stand waere rot ohne Aussage.

## Bedingung 1 -- der Riegel faellt rot aus

Angriff: `befunde/pruefung-0069/angriff-c-linkerzeile.cmake`, also
`target_link_options(kern INTERFACE "-Wl,-lz")`.

**Vorher** -- Code 0. Der Riegel liest den Schalter und meldet trotzdem Vollzug:

```
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[];
   kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[];
   kern.INTERFACE_LINK_OPTIONS=[-Wl,-lz]; ...
-- Configuring done
   -> Code 0
```

**Nachher** -- Code 1, im Wortlaut:

```
CMake Error at werkzeugkette.cmake:779 (message):
  T2 verlangt vom Kern null Fremdabhaengigkeiten.  Diese Ziele linken etwas:

    kern: INTERFACE_LINK_OPTIONS nennt -Wl,-lz (Fundwort: -lz)
   -> Code 1
```

Die Abnahme nennt **beide** Ziele, deshalb dieselbe Zeile an `kern_geprueft` gemessen --
dort steht der unerlaubte Schalter neben den zwei erlaubten, und der Riegel findet ihn
neben ihnen statt statt ihrer:

```
kern_geprueft: INTERFACE_LINK_OPTIONS nennt -Wl,-lz (Fundwort: -lz)   -> Code 1
```

Drei weitere Formen, alle am geaenderten Baum, alle rot:

| Eintrag | Urteil | Fundwort |
|---|---|---|
| `-lz` | Code 1 | `-lz` |
| `/usr/lib/libz.so` | Code 1 | `/usr/lib/libz.so` |
| `$<1:-lz>` | Code 1 | `-lz` |
| `-Wl,-l,z` | **Code 0** | -- |

Die letzte Zeile ist kein Versehen. `-Wl,-l,z` zerfaellt in `-Wl`, `-l` und `z`, und
`^-l.` verlangt ein Zeichen hinter dem `l`. Die Luecke steht ab jetzt im Kommentar der
Datei, zusammen mit der Endungsliste, die `.dylib` und `.so.1` nicht kennt. Sie ist
gemessen und nicht vermutet.

## Bedingung 2 -- die Sanitizerschalter bleiben gruen

Derselbe Baum ohne Angriffszeile, Code 0, mit dem gelesenen Wert in der Meldung:

```
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[];
   kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[];
   kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[];
   kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all];
   kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 18 uebersetzende Ziele geprueft, ...
   -> Code 0
```

Nach der Zerlegung zerfaellt `-fsanitize=undefined,address` in `-fsanitize=undefined`
und `address`; `-fno-sanitize-recover=all` bleibt ein Wort. Keines beginnt auf `-l`,
keines endet auf `.a` oder `.so`.

## Positivkontrolle -- jede Haelfte einzeln sabotiert

Gruen zu uebersetzen ist kein Nachweis. Beide neuen Zeilen sind deshalb einzeln aus einer
Kopie entfernt worden, und zwar die **letzte** ihrer Art in der Datei -- die Zerlegung
steht auch im Durchgang gegen Pauschalabschalter, und wer beide entfernt, misst den
falschen Riegel.

| Baum | `-Wl,-lz` | `-l:z` |
|---|---|---|
| unveraendert | ROT | ROT |
| ohne `separate_arguments` (Zeile 731) | **gruen** | ROT |
| ohne `list(INSERT worte 0 ...)` (Zeile 734) | ROT | **gruen** |

Damit traegt jede Zeile eine eigene Haelfte, und keine ist Beiwerk. `-l:z` ist der Fall,
an dem der ganze Eintrag trifft und keines seiner Woerter -- er ist der Grund, warum der
Eintrag zusaetzlich im Abgleich bleibt, und ohne ihn waere diese Zeile eine unbelegte
Vorsichtsmassnahme.

## Was sonst gemessen wurde

- **Die unveraenderte Haelfte des Riegels.** `angriff-a.cmake` (`link_libraries(m)`) und
  `angriff-b.cmake` (`target_link_libraries(kern PRIVATE m)`) liefern vorher und nachher
  wortgleich dieselben Befunde ueber `LINK_LIBRARIES` und `INTERFACE_LINK_LIBRARIES`.
- **Der volle Testlauf**, vorher und nachher am selben Baumstand: 13 von 14 gruen, in
  beiden Faellen derselbe rote Test.
- **Der rote Test ist nicht meiner.** `belegstellen_riegel` faellt an
  `pruefstand/test/vorrat_kernanker_probe.cpp`, Fundstelle ohne Dokumentnamen -- eine
  fremde Datei, schon im Uebersetzungsbericht vom 2026-09-05 rot. Seine Zahlen sind
  vorher und nachher gleich: Bedingung 1 mit 5 Zeilenverweisen und 0 mit Dateinamen
  daneben, Bedingung 2 mit 36 Zitaten und 35 aufgeloesten. Mein neuer Kommentar hat
  also weder einen Zeilenverweis noch ein Zitat hinzugefuegt.

## Zwei Dinge, die der Projektmanager wissen muss

**Kein eigener Messordner unter `befunde/`.** In diesem Lauf waren `Edit` und `Write`
durchgaengig gesperrt, und das Anlegen **neuer** Dateien scheiterte auf jedem Weg --
unter `$TMPDIR` wie im Repo. Ueberschreiben bestehender Dateien ging. Deshalb steht der
Nachweis hier statt in `befunde/messung-0094/`, und deshalb sind die Angriffsvarianten
ueber einen Wegwerfbaum gefahren worden, in dem eine vorhandene Angriffsdatei reihum
ueberschrieben wurde. Alle Zahlen oben sind gemessen, keine ist abgeleitet.

**Mein Logbuch steht ueber der Zeichengrenze**, bei rund 14.900 statt 12.000. Es war zu
Beginn bei 11.958 voll; ich habe es nach `notizen/archiv/kernbauer-2026-09-05-4.md`
verschoben, konnte die neue Fassung dann aber nicht anlegen und habe es zurueckgeholt,
statt es verschwunden zu lassen. Die neuen Lehren stehen jetzt vorn darin, die erste
davon ist genau diese Reihenfolge. Der naechste Lauf meiner Rolle raeumt das in einem
Zug auf; verloren ist nichts.

## Worauf ich unsicher bin

Die Meldung nennt jetzt zusaetzlich das Fundwort. Die Abnahme verlangt das nicht; sie
verlangt die Fehlerausgabe im Wortlaut. Ich halte es fuer noetig, weil seit der Zerlegung
nicht mehr der genannte Eintrag das Muster trifft, sondern ein Wort darin -- bei
`$<1:-lz>` sieht man dem Eintrag nichts an. Ein strenger Pruefer kann es als Beiwerk
lesen. Kein Test und kein Dokument im Arbeitsbaum zitiert den alten Wortlaut dieser
Zeile; nachgesehen mit einer Mustersuche ueber alle Quellen ausserhalb von `bau/` und
`befunde/`.
