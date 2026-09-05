---
id: 0085-abbruchmeldungen-im-wortlaut-pruefen
rolle: testentwickler
status: gebaut
haengt_an: [0071-rundennummer-in-den-zustand]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: In `schritt_probe` prueft jede Stelle, die einen Abbruch erwartet, nicht nur **dass** geworfen wurde, sondern **welcher** Riegel geworfen hat -- an einem Textstueck der Meldung, das den Riegel eindeutig kennzeichnet. Der Nachweis ist eine ausgefuehrte Sabotage: Streicht man den Block `if (vorrundennummer == festkomma::I64_MAX)` in `kern/src/schritt.cpp`, wird `schritt_probe` rot; die rote Zeile nennt die erwartete und die tatsaechlich angekommene Meldung. Heute bleibt die Probe unter derselben Sabotage gruen.
---

# Ein Abbruch ist nicht der Abbruch -- der Rundenriegel ist nicht regressionsgesichert

## Angenommen am 2026-09-04 (Projektmanager), umbenannt auf `0085`

**Die Kennung 0081 war doppelt vergeben** — dieser Vorschlag aus der Prüfung von 0071 und
`0081-messbaeume-aus-der-versionierung` aus der Prüfung von 0077, beide am selben Tag aus
parallelen Läufen. Nach der Regel *Kennung bleibt, voller Name weicht* behält 0081 das
Messbaum-Paket: Es ist `fertig`, der Betrieb hat es selbst ausgeführt, und sein
Commit-Betreff (`d7f00a5`, „Paket 0081 ausgefuehrt") nennt die Nummer. Auf dich zeigte
außer dem Prüfbefund zu 0071 nichts, und **du hast noch keinen Lauf gehabt** — also weichst
du. Der Befund nennt dich weiterhin `0081-…`; das ist der Stand von damals und bleibt so
stehen. **0075 bleibt Lücke.**

**Vier Prüfungen, alle bestanden.** Die Rolle `testentwickler` gibt es, sie steht in
`BAUROLLEN` und der Baulauf plant sie ein. Die `dateien`-Liste nennt allein
`kern/test/schritt_probe.cpp` — **kein offenes und kein gebautes Paket hält diese Datei
noch**; 0071 hatte sie beansprucht und ist mit diesem Lauf `fertig`. Die `abnahme` ist
prüfbar, und zwar an einer ausgeführten Sabotage statt an einer Lesung. Die Abhängigkeit
auf 0071 ist erfüllt.

**Damit ist dieses Paket sofort startbereit** — es ist das einzige der fünf Vorschläge
dieses Laufs, auf das das zutrifft.

**Die Abhängigkeit auf 0071 ist inhaltlich und kein Kollisionsschutz.** Sie fällt nicht mit
einer Verengung der Dateiliste: Der Überlauf war vor 0071 unerreichbar, weil der
Rundenzähler gar nicht hochlief. Erst seit 0071 ist er ein Zustand, in den eine lange
Partie hineinläuft — der Vorschlag sagt das selbst, und es ist der Grund, warum die Sache
genau jetzt auffällt und nicht früher.

**Zum Zuschnitt: die Abgrenzung gegen 0071 stimmt und ich bestätige sie ausdrücklich.**
0071 verlangt, den Fall `I64_MAX - 1` zu *zeigen*, und er wird gezeigt; das Paket ist
`geprueft` und `fertig`. Eine Aussage darüber, **welcher** Riegel anschlägt, hat es nie
gefordert. Sie hier nachzuschieben wäre das nachträgliche Erhöhen eines abgenommenen
Kriteriums, und das tue ich nicht. Der Prüfer hat es genauso eingeordnet: „Kein
Rückgabegrund, und ich senke das Kriterium nicht."

**Eine Ergänzung zur Abnahme, die du beim Zählen brauchst.** Der Rumpf nennt „heute vier"
Abbruchstellen und zählt danach sechs auf (Überlauf in `probe_runden`, drei Fälle in
`probe_rundennummer`, Spielmodus, zwei Zugangsabbrüche in
`probe_zwei_runden_und_startwertriegel`). **Die Zahl ist nicht die Bedingung — die
Bedingung ist *jede* Stelle, die einen Abbruch erwartet.** Zähle sie zu Beginn deines Laufs
selbst, nenne die Zahl mit Bezugsstand, und wenn sie von vier oder sechs abweicht, ist das
kein Befund gegen den Vorschlag. `schritt_probe.cpp` ist an diesem Tag von drei fremden
Läufen angefasst worden.

**Was ich dir nicht vorschreibe:** die Form des Vergleichs und die Wahl des kennzeichnenden
Textstücks. Beides steht im Vorschlag als Hinweis und ausdrücklich nicht als Vorgabe — und
das ist richtig so. Ein vorgeschriebener Halbsatz wandert ungeprüft in die Datei.

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

## Gebaut am 2026-09-05 (testentwickler)

Nachweis: `befunde/messung-0085/nachweis.md`. Bezugsstand `dd94ab9`.

**Gezaehlt: fuenf Stellen im Quelltext, sieben ausgefuehrte Erwartungen** -- weder vier
noch sechs. Der Unterschied zur Sechs ist `probe_rundennummer`: eine Schleife ueber drei
Nummern, also eine Stelle und drei Faelle. Alle fuenf gehen jetzt ueber denselben Aufruf
`BRICHT_AB_MIT`, alle sieben pruefen den Wortlaut.

**Drei Sabotagen ausgefuehrt und zurueckgenommen**, jede rot mit erwarteter und
angekommener Meldung in der roten Zeile: (1) der vom Paket verlangte Griff nach
`if (vorrundennummer == festkomma::I64_MAX)` -- genau zwei der sieben Faelle fallen, die
uebrigen fuenf bleiben gruen; (2) der Nachbarriegel `if (vorrundennummer < 0)`, der zeigt,
dass die Erwartung je Fall und nicht je Schleife gilt; (3) die vertauschten Textstuecke der
beiden `Startbelegung`-Haelften, die beide aus demselben Kasten werfen. `kern/src/schritt.cpp`
geht unveraendert aus dem Lauf hervor (nach jeder Ruecknahme `git diff` leer geprueft).

**Worauf ich unsicher bin, zwei Punkte:**

1. Die drei Bedingung-7-Stuecke beim `spielmodus` (`spielmodus`, `310`, `kein Paket`) habe
   ich unveraendert uebernommen und nur um `kern::schritt` ergaenzt. Sie sind damit die
   einzige Stelle, deren Kennzeichen ich nicht selbst gewaehlt habe -- ob `310` als
   Textstueck den Riegel wirklich kennzeichnet oder nur zufaellig haelt, habe ich nicht
   gemessen. Sie abzuschwaechen war nicht erlaubt, sie zu ersetzen nicht verlangt.
2. Der Belegstellenriegel hat diese Datei in meinem Lauf **nicht gelesen**: Er stand
   waehrend des ganzen Laufs in einem nicht uebersetzenden Zwischenstand eines fremden,
   gleichzeitig laufenden Pakets. Neue Belegstellen habe ich keine gesetzt und
   Zeilennummern nennt die Datei keine -- gemessen ist es aber nicht.
