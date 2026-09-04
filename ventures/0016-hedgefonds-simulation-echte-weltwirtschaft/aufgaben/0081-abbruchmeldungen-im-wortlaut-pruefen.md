---
id: 0081-abbruchmeldungen-im-wortlaut-pruefen
rolle: testentwickler
status: vorschlag
haengt_an: [0071-rundennummer-in-den-zustand]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: In `schritt_probe` prueft jede Stelle, die einen Abbruch erwartet, nicht nur **dass** geworfen wurde, sondern **welcher** Riegel geworfen hat -- an einem Textstueck der Meldung, das den Riegel eindeutig kennzeichnet. Der Nachweis ist eine ausgefuehrte Sabotage: Streicht man den Block `if (vorrundennummer == festkomma::I64_MAX)` in `kern/src/schritt.cpp`, wird `schritt_probe` rot; die rote Zeile nennt die erwartete und die tatsaechlich angekommene Meldung. Heute bleibt die Probe unter derselben Sabotage gruen.
---

# Ein Abbruch ist nicht der Abbruch -- der Rundenriegel ist nicht regressionsgesichert

Befund: `befunde/pruefung-0071-rundennummer-in-den-zustand-2026-09-04.md`, Befund 1.
Dort steht die ausgefuehrte Reproduktion.

## Was heute geschieht

`kern::schritt` faengt den Rundenueberlauf ab, **bevor** addiert wird
(`schritt.cpp:608-621`): Ist die Vorrundennummer `I64_MAX`, bricht die Runde mit einer
Meldung ab, die den Grund nennt. Der Riegel ist richtig gebaut und seine Begruendung steht
an ihm.

Er ist nur nicht gesichert. Streicht man ihn ersatzlos, bleibt `schritt_probe` **gruen**:

```
Abbruch wie erwartet (Runde nach der letzten zaehlbaren): kern::schreiber -- eine Runde vor der ersten gibt es nicht
schritt_probe: alle Pruefungen bestanden
100% tests passed
```

Der Grund ist `-fwrapv`: `I64_MAX + 1` bricht ins Negative um, und der
`Schreiber`-Konstruktor weist negative Rundennummern ab (`schreiber.cpp:206-208`). Es
fliegt also weiterhin ein `std::domain_error` -- aus einem anderen Riegel, mit einer
Meldung, die die Ursache nicht mehr nennt. Beide Prueforte fragen nur `PRUEFE(geworfen)`
(`schritt_probe.cpp:391-399` und `:550-558`) und sehen den Unterschied nicht.

Das Bemerkenswerte: **Der Kommentar der Probe beschreibt diesen Ausgang bereits**
(`:542-544`, „mit einer Meldung, die die Ursache nicht mehr nennt"), und
`schritt.cpp:609-612` begruendet den Riegel genau damit. Die Fabrik weiss also von der
Unterscheidung -- nur haelt sie keine Zusicherung fest. Ein kuenftiger Lauf, der den Block
fuer redundant haelt („der Schreiber faengt es doch ohnehin"), bekommt von der Werkzeugkette
gruenes Licht.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0071.** Dessen Abnahme verlangt, den Fall `I64_MAX - 1` zu *zeigen*, und
er wird gezeigt -- der Zustand traegt danach `I64_MAX`, die naechste Runde bricht ab. Das
ist erfuellt und ist geprueft. Was fehlt, ist eine Aussage darueber, **welcher** Riegel
anschlaegt, und die hat 0071 nie gefordert. Sie hier nachzuschieben hiesse, das Kriterium
eines abgenommenen Pakets nachtraeglich zu erhoehen.

**Nicht Teil von 0033.** Der Riegel stammt von dort und ist `fertig`. Sein Verhalten
aendert dieses Paket nicht -- es fasst `schritt.cpp` gar nicht an. Nur die Probe.

**Nicht Teil von 0077.** Das ist die Schrankenprobe und eine andere Datei.

Es ist also die Absicherung einer bestehenden, richtigen Schranke, und sie faellt genau
jetzt auf, weil 0071 den Rundenzaehler zum ersten Mal wirklich hochzaehlen laesst: Vorher
war der Ueberlauf unerreichbar, seither ist er ein Zustand, in den eine lange Partie
hineinlaeuft.

## Was zu bauen ist

Ein Vergleich auf ein **kennzeichnendes Textstueck** der erwarteten Meldung, an jeder
Stelle in `schritt_probe`, die einen Abbruch erwartet -- heute vier: der Ueberlauf in
`probe_runden`, die drei Faelle in `probe_rundennummer`, der Spielmodus in
`probe_spielmodus_bricht_ab` und die beiden Zugangsabbrueche in
`probe_zwei_runden_und_startwertriegel`.

Die Form entscheidet der Bauagent. Zwei Hinweise, damit die Sicherung nicht selbst zur
Last wird:

1. **Nicht die ganze Meldung abschreiben.** Ein Volltextvergleich geht bei jeder
   Umformulierung rot und erzieht dazu, die erwartete Zeichenkette nachzuziehen statt
   hinzusehen. Ein Stueck, das den Riegel eindeutig macht -- `"groesste int64_t"` gegen
   `"vor der ersten"` --, trennt die beiden Faelle und ueberlebt eine Umformulierung des
   Rests.
2. **Der Fehlerfall muss beide Zeichenketten drucken**, die erwartete und die
   angekommene. Ein `PRUEFE`, das nur „falsche Meldung" sagt, kostet den naechsten Lauf
   einen Bau.

## Was ausdruecklich kein Befund ist

Dass `schritt.cpp` den Riegel doppelt haelt -- einmal in `schritt`, einmal im
`Schreiber`-Konstruktor. Die Doppelung ist gewollt und in `schritt.cpp:609-612` begruendet:
Der aeussere nennt die Ursache, der innere ist der Fangnetz-Riegel. Dieses Paket macht die
Doppelung pruefbar, es baut sie nicht ab.
