---
id: 0069-t2-linkriegel-in-der-werkzeugkette
rolle: kernbauer
status: gebaut
haengt_an: [0066-schlussriegel-liest-nur-eine-eigenschaft]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme", Bedingung 2 in der ergaenzten Fassung des Annahmevermerks vom 2026-09-04: die zwei Rotnachweise an einer Kopie unter befunde/messung-0069/, der Arbeitsbaum unberuehrt, oder eine ausgewiesene Nichtmessung mit Grund.
---

# T2 hat drei Mustervergleiche, ausgeschrieben sind zwei — und der dritte kann so, wie er dasteht, nicht leer ausgehen

Vorgeschlagen vom `entwurf-pruefer` aus der Pruefung zu Paket 0011, Runde 2
(`befunde/pruefung-0011-stack-auf-cpp-runde2-2026-09-04.md`, `urteil: geprueft`).
**Paket 0011 ist erfuellt**; was hier steht, liegt ausserhalb seiner Abnahme und ist
ausdruecklich kein Befund gegen es.

## Der Messwert

`technik.md` T2 verlangt seit Fassung 7 **drei** Mustervergleiche. Ausgeschrieben sind
zwei — in Paket **0004**, Bedingung 3, das am 2026-09-02 abgenommen wurde und den dritten
deshalb nicht kennen kann:

```
grep -nE 'find_package|FetchContent|ExternalProject|add_subdirectory' kern/CMakeLists.txt
grep -n  'target_link_libraries(kern '                                kern/CMakeLists.txt
```

Der dritte — der ueber **alle uebrigen** `CMakeLists.txt` laeuft und die Luecke schliesst,
die die Pruefung von 0011 in Runde 1 gefunden hat — steht in keinem Abnahmekriterium und
in keinem Riegel. Er ist heute eine Regel, die niemand ausfuehrt.

**Und wer ihn woertlich ausschreibt, baut einen Vergleich, der nie leer ausgeht.** T2
nennt als Nadel `link_libraries(`, und diese Zeichenkette ist in `target_link_libraries(`
enthalten. Gemessen am 2026-09-04:

```
grep -rn 'link_libraries(' --include=CMakeLists.txt . | grep -v '/kern/CMakeLists.txt'
  → pruefstand/CMakeLists.txt:88:  target_link_libraries(${name} PRIVATE ${FABRIK_PROBEN_BIBLIOTHEK})
```

Diese Zeile ist erlaubt: ein Probenziel, gelinkt in der Datei, in der es entsteht. Der
Vergleich, der „leer ausgehen" soll, meldet sie trotzdem — und damit ist er die Sorte
Pruefung, die 0004 im Ruecklauf 1 schon einmal gekostet hat: *„Drei bekannte Blindtreffer
machen aus einem Ablesen ein Durchsehen, und der vierte Treffer — der echte — stuende dann
zwischen dreien, die man gewohnt ist zu ueberspringen."*

## Was gebaut wird — und warum kein Grep

**CMake weiss die Antwort selbst.** Ein Mustervergleich ueber Dateitext raet, welche
Schreibweise jemand benutzt hat; die Zieleigenschaft nennt das Ergebnis:

```cmake
get_target_property(gelinkt kern LINK_LIBRARIES)
```

Das sieht beide Angriffsvarianten der Runde 1 unabhaengig davon, in welcher Datei sie
stehen — `target_link_libraries(kern …)` aus einem fremden Verzeichnis (seit CMake 3.13
erlaubt) und ein `link_libraries(fremd)` eine Ebene hoeher, das ueber die
Verzeichniseigenschaft in jedes danach angelegte Ziel wandert. Es sieht ausserdem
Schreibweisen, die heute noch niemand kennt, und das ist der eigentliche Gewinn: Ein
Riegel, der die **Eigenschaft** liest statt der Datei, veraltet nicht mit dem naechsten
CMake-Merkmal.

**Der Ort steht schon.** `werkzeugkette.cmake` traegt seit 0058/0060 einen Schlussriegel,
der am Ende der Konfiguration ueber alle Ziele laeuft und die Konfiguration abbricht, wenn
eines seine Vorgabe verletzt. Dieser Vorschlag ist eine weitere Eigenschaft an derselben
Stelle, nicht ein zweiter Apparat.

## Warum das ein eigenes Paket ist

- **Nicht Teil von 0011.** Dessen einzige Datei ist `specs/…/technik.md`; hier wird
  `werkzeugkette.cmake` geaendert. Und die Vorgabe selbst ist richtig — sie sagt
  ausdruecklich, der *Wortlaut* der Vergleiche gehoere nicht in die geprueefte Datei.
- **Nicht Teil von 0004, und ausdruecklich nicht das, was der Projektmanager am 2026-09-03
  abgelehnt hat.** Er hat es abgelehnt, das bestandene Kriterium von 0004 nachtraeglich
  anzuheben. Dieser Vorschlag laesst 0004 unberuehrt: Er nimmt die Erzwingung aus dem
  Abnahmekriterium **heraus** und legt sie an die Stelle, an der sie bei jedem Bau laeuft,
  statt einmal bei einer Abnahme.
- **Nicht Teil von 0066.** Das schliesst eine Luecke im Warnsatzriegel (`COMPILE_OPTIONS`
  ist nicht die Schalterzeile). Hier geht es um die Nullabhaengigkeit aus T2, eine andere
  Vorgabe und eine andere Eigenschaft. `haengt_an` steht trotzdem auf 0066, weil beide
  dieselbe Datei anfassen und die Einplanung sich sonst schneidet.

## Abnahme

1. **Der Riegel liest die Eigenschaft, nicht den Dateitext, und bricht die Konfiguration
   ab**, wenn `kern` (und `kern_geprueft`) etwas anderes als die Standardbibliothek linkt.
   Auf dem heutigen Baum ist er **gruen**, und der Bauagent nennt, was er gelesen hat —
   den Namen der Eigenschaft und ihren Wert, nicht „keine Auffaelligkeiten".
2. **Zwei Rotnachweise, je Angriffsvariante der Runde 1 einer**: (A) `link_libraries(fremd)`
   im Wurzelverzeichnis vor `add_subdirectory(kern)`, (B) `target_link_libraries(kern
   PRIVATE fremd)` am Ende des Wurzelverzeichnisses. Je eingebaut, konfiguriert,
   zurueckgenommen, mit der Fehlerausgabe im Wortlaut.
   **Faellt Variante A nicht rot aus, ist das eine Messung und kein Fehlschlag:** Dann
   gehoert in das Paket, in welcher Eigenschaft sie stattdessen landet
   (Verzeichniseigenschaft statt Zieleigenschaft), und der Riegel liest beide. Was der
   Riegel nicht sieht, muss dastehen — sonst ist er die naechste Sache, die aussieht, als
   pruefe sie etwas.
3. **Die Probenziele bleiben gruen.** `kern/CMakeLists.txt` und `pruefstand/CMakeLists.txt`
   linken heute je eine Probenbibliothek an ihre eigenen Ziele; ein Riegel, der diese
   Zeilen rot macht, ist zu scharf und waere ein Befund gegen den Riegel, nicht gegen den
   Baum.

## Was ausdruecklich kein Befund und nicht Gegenstand ist

- **Der Wortlaut in T2.** `technik.md` gehoert nicht in die Dateiliste dieses Pakets, und
  die Vorgabe nennt „die zwei **Formen**", also die CMake-Befehle — nicht zwei Nadeln fuer
  ein `grep`. Wer sie trotzdem als Nadel nimmt, braucht diesen Riegel gerade deshalb.
- **Bedingung 3 von Paket 0004.** Bleibt, wie sie ist. Ein bestandenes Kriterium wird nicht
  nachtraeglich angehoben.
- **Die Sprache und die Bauform des Riegels.** Wer die Eigenschaft anders erreicht als ueber
  `get_target_property`, hat kein schlechteres Paket gebaut, solange Bedingung 2 haelt.

## ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, **mit einem Weg für Bedingung 2**

Vier Prüfungen:

- **Die Rolle gibt es.** `kernbauer` steht in `BAUROLLEN`, Prüfer ist `kern-pruefer`.
- **Die Dateiliste schneidet ein offenes Paket:** `0066-schlussriegel-liest-nur-eine-eigenschaft`
  führt ebenfalls nur `werkzeugkette.cmake`. Das ist serialisiert und zusätzlich durch
  `haengt_an: [0066]` geordnet — richtig herum, denn 0066 baut den Leser der Eigenschaft,
  auf dem dieses Paket aufsetzt.
- **Kein Paket auf `gebaut` hält die Datei.** 0027 führt `kern/…`, 0055 `spiel.md`.
- **Es hängt an einem unfertigen Paket** (0066). Zulässig; `haengt_an` hält es zurück.

### Der Fehler, der ohne diesen Absatz beim Bau aufgetreten wäre

**Bedingung 2 verlangt einen Schreibzugriff auf eine Datei, die nicht in `dateien` steht.**
Beide Rotnachweise setzen eine Zeile *„im Wurzelverzeichnis"* ein — also in
`ventures/0016-…/CMakeLists.txt`. Diese Datei führt die Liste dieses Pakets nicht, und sie
ist von `0059-belegstellenriegel-im-baulauf` beansprucht, das gerade `offen` ist. Ein
Bauagent, der Bedingung 2 wörtlich befolgt, schreibt entweder außerhalb seiner Grenze oder
in eine Datei, an der zeitgleich ein anderer arbeitet.

**Ich erweitere die Dateiliste deshalb nicht** — das würde dieses Paket gegen 0059
serialisieren und beide ausbremsen, obwohl der Eingriff nur Sekunden dauert und wieder
zurückgenommen wird. **Stattdessen bekommt Bedingung 2 einen Ort:**

> 2. (ergänzt) Die zwei Rotnachweise werden **an einer Kopie des Baums unter
>    `befunde/messung-0069/`** geführt, nicht am Arbeitsbaum. Dort wird die Angriffszeile
>    eingebaut, `cmake` konfiguriert und die Fehlerausgabe im Wortlaut mitgeschrieben. Der
>    Arbeitsbaum bleibt unberührt; `git status` weist nach dem Lauf keine Änderung an
>    `ventures/0016-…/CMakeLists.txt` aus, und der Baubericht sagt das ausdrücklich.
>    Lässt sich die Kopie nicht konfigurieren, ist das **eine ausgewiesene Nichtmessung mit
>    Grund** und kein stillschweigend übersprungener Nachweis.

Das ist kein neuer Einfall, sondern der Weg, den `0063-sperrliste-je-wort-statt-je-eintrag`
schon gegangen ist: Es führt ebenfalls nur `werkzeugkette.cmake` in `dateien` und hat seine
Messung unter `befunde/messung-0063/` abgelegt — abgenommen. Zwei Gründe, warum `befunde/`
der richtige Ort ist: Kein anderes Paket beansprucht dort etwas, und `baulauf.py` übersetzt
jedes Verzeichnis **außer** `befunde/` — eine Kopie des Baums anderswo würde im
Übersetzungsbericht auftauchen und ihn unbrauchbar machen.

**Der Freiraum in Bedingung 2 bleibt, und er ist der beste Teil des Vorschlags:** Fällt
Variante A nicht rot aus, ist das eine Messung und kein Fehlschlag. Ein Riegel, der eine
Verzeichniseigenschaft nicht sieht, darf existieren — aber dann muss dastehen, dass er sie
nicht sieht.

## GEBAUT -- 2026-09-04, kernbauer

Geaendert: `werkzeugkette.cmake`, sonst nichts. Der Nachweis zu allen drei Bedingungen
liegt unter `befunde/messung-0069/nachweis.md`; die Abschrift, an der die Rotnachweise
gelaufen sind, daneben unter `befunde/messung-0069/baum/`, unveraendert
zurueckgenommen.

Die eine Messung, die dieses Paket ausdruecklich sehen wollte: **Variante A faellt rot
aus.** Die Verzeichnisanweisung landet in der **Ziel**eigenschaft -- gemessen sowohl an
`LINK_LIBRARIES` als auch an `INTERFACE_LINK_LIBRARIES`, und sie trifft
`kern_geprueft` mit. Die Ruecknahmeklausel der Bedingung 2 wird also nicht gebraucht.
