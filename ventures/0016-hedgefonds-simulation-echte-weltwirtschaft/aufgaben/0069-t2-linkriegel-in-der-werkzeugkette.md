---
id: 0069-t2-linkriegel-in-der-werkzeugkette
rolle: kernbauer
status: vorschlag
haengt_an: [0066-schlussriegel-liest-nur-eine-eigenschaft]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
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
