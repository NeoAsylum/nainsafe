---
id: 0094-linkschalterform-durchgereichtes-l
rolle: kernbauer
status: offen
haengt_an: [0069-t2-linkriegel-in-der-werkzeugkette, 0076-riegel-sammeln-notfound-je-quelle]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, mit einer Änderung an `haengt_an`

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
