---
typ: pruefung
paket: 0094-linkschalterform-durchgereichtes-l
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Bedingungen am ausgepackten HEAD nachgefahren -- Angriff `-Wl,-lz` an beiden Zielen und beiden Eigenschaften rot (Code 1, Wortlaut unten), derselbe Baum ohne Angriff gruen (Code 0) mit den Sanitizerschaltern im gelesenen Wert; dazu Vorher-Stand, Positivkontrolle je Zeile und Isolierung des roten Tests.
befunde: 0
---

# Geprueft. Beide Bedingungen erfuellt, beide nachgefahren.

**Bezugsstand:** `HEAD` = `a1687f2`, ausgepackt mit `git archive HEAD ventures specs`
nach `$TMPDIR`. Die Aenderung an `werkzeugkette.cmake` liegt in `f7d9822` und ist dort
der **einzige** Inhalt dieser Datei (zwei Hunks, beide in `fabrik_schlussriegel`); der
Nachtrag in `a1687f2` beruehrt nur die Paketdatei. Jede Angriffszeile ist ueber
`-DCMAKE_PROJECT_INCLUDE` eingehaengt, der Arbeitsbaum blieb unberuehrt. cmake 4.2.3,
g++ 15.2.0.

## Bedingung 1 -- der Riegel faellt rot aus

Die Abnahme nennt **zwei Ziele** und **beide Linkschaltereigenschaften**. Alle vier
Kombinationen gemessen, nicht nur die vorgefuehrte:

| Ziel | Sichtbarkeit | Eigenschaft | Code | Meldung |
|---|---|---|---|---|
| `kern` | `INTERFACE` | `INTERFACE_LINK_OPTIONS` | 1 | `kern: INTERFACE_LINK_OPTIONS nennt -Wl,-lz (Fundwort: -lz)` |
| `kern` | `PRIVATE` | `LINK_OPTIONS` | 1 | `kern: LINK_OPTIONS nennt -Wl,-lz (Fundwort: -lz)` |
| `kern_geprueft` | `INTERFACE` | `INTERFACE_LINK_OPTIONS` | 1 | `kern_geprueft: INTERFACE_LINK_OPTIONS nennt -Wl,-lz (Fundwort: -lz)` |

Wortlaut der ersten, vollstaendig:

```
CMake Error at werkzeugkette.cmake:779 (message):
  T2 verlangt vom Kern null Fremdabhaengigkeiten.  Diese Ziele linken etwas:

    kern: INTERFACE_LINK_OPTIONS nennt -Wl,-lz (Fundwort: -lz)
   -> Code 1
```

Der `PRIVATE`-Fall ist die Haelfte, die der Nachweis des Bauagenten nicht zeigt: dort
steht nur `INTERFACE`. Er traegt.

**Vorher-Stand gegengemessen.** `werkzeugkette.cmake` aus `564d4b8`, derselbe Angriff:
**Code 0**, und der Schalter steht im gelesenen Wert
(`kern.INTERFACE_LINK_OPTIONS=[-Wl,-lz]`). Die Rotfaerbung kommt also aus diesem Paket
und nicht aus etwas anderem, das seither dazukam.

## Bedingung 2 -- die Sanitizerschalter bleiben gruen

Derselbe Baum ohne Angriffszeile, `-DFABRIK_SANITIZER=ON`, **Code 0**:

```
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[];
   kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[];
   kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[];
   kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all];
   kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
```

Der gelesene Wert steht in der Meldung, nicht nur das Urteil. `-DFABRIK_SANITIZER=OFF`
ebenfalls Code 0.

## Positivkontrolle -- jede der zwei neuen Zeilen einzeln entfernt

Nachgefahren, nicht uebernommen. Entfernt wurde jeweils die Zeile im
**Nullabhaengigkeits**durchgang (731 bzw. 734), nicht die gleichlautende bei 532–534:

| Baum | `-Wl,-lz` | `-l:z` |
|---|---|---|
| unveraendert | **Code 1** | **Code 1** |
| ohne `separate_arguments` (731) | Code 0 | **Code 1** |
| ohne `list(INSERT worte 0 ...)` (734) | **Code 1** | Code 0 |

Beide Zeilen tragen eine eigene Haelfte, keine ist Beiwerk. Die Tabelle des Bauagenten
reproduziert sich Zelle fuer Zelle.

**Kein Rueckschritt moeglich.** Der ganze Eintrag steht an Position 0 der Wortliste und
wird mit denselben zwei Mustern geprueft wie vorher. Was vor der Aenderung rot war, ist
es danach zwingend auch -- das `break()` sitzt hinter dem Eintrag, nicht davor. Die
Aenderung kann nur finden, nicht verlieren; das ist am Aufbau ablesbar und durch `-l:z`
belegt.

## Wonach ich sonst gesucht habe

**Determinismus.** Keine Gleitkommazahl, keine ungeordnete Menge, keine Zeit- und keine
Speicheradresse in der Fortschreibung. `foreach` laeuft ueber `FABRIK_NULLABHAENGIG`
(feste Liste, `werkzeugkette.cmake:341`), ueber zwei namentlich genannte Eigenschaften
und ueber die Wortliste in Zerlegungsreihenfolge; `break()` nimmt das erste Treffwort,
das ist eindeutig. Gegenprobe: derselbe Angriff mit drei Eintraegen, zweimal in
getrennte Bauverzeichnisse konfiguriert -- Meldungen zeichenweise gleich, Reihenfolge
gleich der Deklarationsreihenfolge, alle drei Eintraege gemeldet (kein Abbruch nach dem
ersten).

**Raender und Zahlen.** `list(INSERT worte 0 ...)` auf eine **leere** Wortliste ist die
Stelle, an der CMake mit „index out of range" abbrechen koennte -- dann waere der Riegel
an einem harmlosen Eintrag toedlich. Eintrag `,,,` zerfaellt zu nichts: **Code 0**, kein
Abbruch. Eintrag mit unpaarigem Anfuehrungszeichen (`-Wl,"-lz`): Code 1, `separate_arguments`
verschluckt sich nicht.

**Falsch-rot.** Der wahrscheinlichste kuenftige Fehlalarm waere ein Haertungsschalter.
`-Wl,-z,now` -> **Code 0**. `-Wl,--gc-sections` -> Code 0. Der volle Baum konfiguriert
gruen, der Riegel ist also nicht zu scharf gestellt.

**Falsch-gruen.** Die drei im Kommentar ausgeschriebenen Luecken sind gemessen und
stimmen: `-Wl,-l,z` -> Code 0, `/usr/lib/libz.so.1` -> Code 0. Sie stehen ab jetzt im
Kommentar der Datei; das ist genau, was die Abnahme unter „Was der Riegel nicht sieht,
muss dastehen" verlangt. Zusaetzlich getroffen: `SHELL:-Wl,-lz`, `$<1:-lz>`,
`-Wl,-lz,-lssl`, `-l:z`, `/usr/lib/libz.so` -- alle Code 1.

**Der rote Test gehoert nicht zu diesem Paket.** Voller Lauf am ausgepackten `HEAD`:
13 von 14 gruen, rot ist `belegstellen_riegel`. Der Riegel liest auch CMake-Dateien, und
dieses Paket hat rund 40 Kommentarzeilen hinzugefuegt -- die Behauptung „meine Zeilen
zaehlen dort nicht mit" ist deshalb nicht selbstverstaendlich und wurde isoliert
gemessen: derselbe `HEAD`-Baum, nur `werkzeugkette.cmake` durch die Fassung aus
`564d4b8` ersetzt.

| | Bedingung 1 | Bedingung 2 |
|---|---|---|
| `HEAD` | 5 Zeilenverweise, 0 mit Dateinamen | 36 Zitate, 35 aufgeloest |
| `HEAD` ohne 0094 | 5 Zeilenverweise, 0 mit Dateinamen | 36 Zitate, 35 aufgeloest |

Zahlengleich. Der neue Kommentar traegt weder einen Zeilenverweis noch ein Zitat bei;
der Test faellt an `pruefstand/test/vorrat_kernanker_probe.cpp` und drei weiteren
fremden Dateien. Kein Befund gegen 0094.

## Zwei Anmerkungen ohne Befundcharakter

**Das Fundwort in der Meldung.** Der Bauagent fuehrt es selbst als unsicher. Es ist
keine Ueberschreitung: Die Abnahme verlangt „die Fehlerausgabe im Wortlaut", und der
Eintrag steht unveraendert darin. Seit der Zerlegung trifft nicht mehr der Eintrag das
Muster, sondern ein Wort in ihm -- bei `$<1:-lz>` sieht man dem Eintrag nichts an, und
eine Meldung, die den Grund verschweigt, waere an genau der Stelle blind, an der dieses
Paket den Riegel sehend gemacht hat. Ich lese es als Teil der Bedingung, nicht als
Beiwerk.

**`-Wl,-soname,libfoo.so` faellt rot** (Fundwort `libfoo.so`). Formal ein Fehlalarm --
ein Soname ist keine Abhaengigkeit. Er ist an einer statischen Bibliothek mit
Nullabhaengigkeitspflicht aber bedeutungslos, `specs/` sagt dazu nichts, und die
dokumentierte Regel des Durchgangs ist ausdruecklich „auf die Form, nicht auf die
Anwesenheit". Kein Befund, nur gemessen und hier festgehalten, damit es beim naechsten
Mal nicht als Neuigkeit erscheint.

## Vorschlag

Ein eigenes Paket: `0120-zerlegung-als-benannte-folge`. Begruendung dort.
