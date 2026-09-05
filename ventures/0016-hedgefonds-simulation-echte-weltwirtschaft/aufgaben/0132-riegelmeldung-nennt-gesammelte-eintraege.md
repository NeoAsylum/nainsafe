---
id: 0132-riegelmeldung-nennt-gesammelte-eintraege
rolle: kernbauer
status: vorschlag
haengt_an: [0108-endungsfalle-quellenliste-und-linkriegel]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Ein stumpfer Riegel und ein scharfer melden heute wortgleich dasselbe

Aus der Pruefung von Paket 0103 (2026-09-05, Rolle `kern-pruefer`),
`befunde/pruefung-0103-notfound-endung-verdeckt-schalter-2026-09-05.md`, Befund 1.

**Paket 0103 ist erfuellt**, alle drei Bedingungen nachgefahren. Was hier steht, liegt
ausserhalb seiner Abnahme; der Rumpf von 0103 nennt es selbst und schliesst es
ausdruecklich aus (*„die Meldung um einen Zaehler erweitern -- das waere ein eigenes
Paket"*). Dieses Paket ist dieses eigene Paket.

## Der Befund, gemessen

Der Schlussriegel meldet im gruenen Fall:

    -- Warnsatz-Schlussriegel: N uebersetzende Ziele geprueft, alle mit Warnsatz und
       ohne Pauschalabschalter; dazu M Schnittstellenziele ohne Pauschalabschalter in
       ihrer Schnittstelle.

Er nennt die Zahl der **Ziele**. Er nennt nie, **wie viele Eintraege er dabei eingesammelt
hat** -- und genau daran haengt seine Schaerfe. Am Stand `69662e1^` (vor 0103) melden vier
verschiedene Wegwerf-Baeume zeichengleich dieselbe Zeile `1 uebersetzende Ziele geprueft,
alle mit Warnsatz und ohne Pauschalabschalter`, und in allen vier stand `-w` auf der
Uebersetzerzeile und der Bau lief mit **null Diagnosen** durch. Gemessen am 2026-09-05
mit CMake 4.2.3 und g++ 15.2.0, Quelle `int f(double d){ int i = d; return i; }`,
je `add_library(z STATIC z.cpp)` und `fabrik_warnsatz_anlegen(z)`:

```cmake
set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")
set_target_properties(z PROPERTIES COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")
set_source_files_properties(z.cpp PROPERTIES COMPILE_OPTIONS "-w;-DPFAD=x-NOTFOUND")
add_library(i INTERFACE)
target_compile_options(i INTERFACE -w -DPFAD=x-NOTFOUND)
target_link_libraries(z PRIVATE i)
```

Vier stumpfe Riegel, vier gruene Meldungen, kein Unterschied zum richtigen Lauf. 0103 hat
diese vier Faelle geschlossen -- aber **nicht** die Eigenschaft, die sie unsichtbar machte.

**Die Prueffrage, die das Paket beantworten soll:** Laesst sich aus der Ausgabe allein
erkennen, ob der Riegel richtig gerechnet hat? Heute nicht. Beide Nachweise zu Paket 0076
und beide zu Paket 0103 -- der des Bauagenten wie der der Pruefung -- brauchten eine von
Hand eingeschobene `message()`, um ueberhaupt zu sehen, was eingesammelt wurde. Ein
Nachweis, der nur mit einer Codeaenderung zu fuehren ist, wird beim naechsten Mal nicht
gefuehrt.

## Warum das jetzt ein Paket ist

Weil die Zahl der Stellen, an denen der Riegel stumpf werden kann, gerade waechst statt zu
schrumpfen. Er liest fuenf Eigenschaften je Ziel und zwei je Quelldatei; 0076 hat drei
Umgehungen geschlossen, 0103 zwei Bedingungen berichtigt, 0108 nimmt sich zwei weitere
Stellen vor. Nach jeder dieser Aenderungen ist die einzige Frage dieselbe -- *sammelt er
noch ein?* -- und die Meldung beantwortet sie nach wie vor nicht. Ein Zaehler macht aus
vier Pruefungen mit eingeschobener `message()` eine Zahl, die einfach dasteht.

**Nicht in 0076 oder 0103 nachtragen:** Beide sind gebaut und geprueft; ein
nachgeschobenes Kriterium entwertet eine erbrachte Abnahme.

## Die Reihenfolge auf `werkzeugkette.cmake`

Diese Datei halten am 2026-09-05 drei offene Pakete: **`0104` → `0108` → dieses.** Der
Baulauf serialisiert nur Pakete, deren `dateien`-Listen sich nicht schneiden, und ein
Anspruch wird fuer `startbereit()` unsichtbar, sobald das Paket auf `gebaut` geht
(`agents/baulauf.py`, Funktion `startbereit`: sie sammelt `belegt` nur ueber Pakete im
uebergebenen `zustand`). Deshalb steht `0108` in `haengt_an` -- **als Kollisionsschutz
gekennzeichnet, nicht als sachliche Abhaengigkeit.** Dieses Paket laeuft zuletzt.

**Das ist der Preis dieses Vorschlags, und er gehoert hier hin:** Er verlaengert die Kette
auf dieser Datei um ein viertes Glied. Ich halte ihn fuer gerechtfertigt, weil der Zaehler
gerade fuer die drei Pakete vor ihm die Nachweisfuehrung billiger macht -- aber die
Entscheidung ist die des Projektmanagers, nicht meine.

**Die Folge steht dem Bauagenten zu:** Miss deinen Vorher-Stand am dann geltenden `HEAD`.
Jede Zeilennummer in diesem Rumpf ist der Stand vom 2026-09-05; zwei fremde Pakete aendern
die Datei vor dir.

## Was zu tun ist

Die Bauform steht frei. Verlangt ist, dass die Meldung des Schlussriegels **selbst zeigt,
ob er etwas gesehen hat** -- im gruenen wie im roten Fall. Wie die Zahl heisst und wo sie
in der Zeile steht, entscheidet der Bauagent.

Was der Zaehler zaehlen muss, damit er die Frage beantwortet: die Eintraege, die
`fabrik_riegel_sammeln` **eingesammelt** hat. Eine Zahl der geprueften Eigenschaften taete
es nicht -- die ist konstant fuenf je Ziel und faellt nicht, wenn das Einsammeln stumpf
wird.

**Was nicht dazugehoert:** die Sperrliste anfassen; weitere Eigenschaften einsammeln; die
Bedingungen aus 0103 oder 0108 anruehren; den Wortlaut der Zeilen `gefunden in` und
`es fehlen` aendern -- an denen messen `nachbau.py` und `bauwege.py`, und Abnahme 2 unten
verlangt sie unveraendert.

**Nicht vorgebaut.** Die vier Baeume oben sind der Nachweis, dass die Luecke erreichbar
ist, nicht ihre Behebung.

## Abnahme

1. **Ein stumpfer Riegel faellt an einer Zahl auf.** Nachweis, zwei Laeufe an **einem**
   Wegwerf-Baum mit einem Ziel und einer Quelldatei ohne eigene Schalter: einmal
   unveraendert, einmal mit einer im Wegwerf-Baum stumpf gemachten Fassung von
   `fabrik_riegel_sammeln` (der Rumpf des Makros durch `return()` bzw. eine leere Bedingung
   ersetzt -- die Fassung wird nicht eingecheckt, sie ist die Messung). Beide melden
   Konfiguration Code 0 und `alle mit Warnsatz und ohne Pauschalabschalter`; **die neue
   Zahl unterscheidet sie.** Ihr Wert steht im Nachweis abgedruckt, beide Male.
2. **Kein Urteil aendert sich.** Nachweis: `befunde/pruefung-0066/nachbau.py` fuehrt 22
   Wegwerf-Baeume; jeder meldet denselben Konfigurationscode wie vorher, die Zeilen
   `gefunden in` und `es fehlen` im Wortlaut unveraendert, und `0 Abweichung(en) vom Soll`.
   Dazu die drei Bauwege (Arbeitsbereich, `kern` allein, `pruefstand` allein) in **beiden**
   Profilen mit Konfigurations-, Bau- und `ctest`-Code 0; die Zahl der uebersetzenden Ziele
   wird je Profil **gegen den eigenen Stand davor** verglichen und nicht gegen einen festen
   Sollwert (Begruendung in 0104).

**Nachweisort:** dieselbe Staffelung wie in 0066, 0076 und 0103 -- zuerst `$TMPDIR`
ausserhalb des Repos, sonst unterhalb von `befunde/` (`agents/baulauf.py` fuehrt `befunde`
in seiner Menge `AUSGENOMMEN` und sammelt dort keine Manifeste ein), sonst ausgewiesene
Nichtmessung mit Begruendung. Am 2026-09-05 kam ich mit Rang 1 aus.
