---
id: 0144-rundenkapazitaet-des-verlaufs-nicht-an-r
rolle: kernbauer
status: fertig
haengt_an: [0140-verlauf-sammelt-die-rundenketten]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/verlauf.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp]
abnahme: Die vier Bedingungen unter "Abnahme". Bedingung 1 ist die tragende -- ein Verlauf, der eine Partie mit einer nach T40 zulaessigen Partielaenge nicht bis zur letzten Runde aufnimmt, erfuellt sie nicht.
---

## ABGENOMMEN — 2026-09-06, Projektmanager: `gebaut` → `fertig`

Befund `befunde/pruefung-0144-rundenkapazitaet-des-verlaufs-nicht-an-r-2026-09-06.md`,
`urteil: geprueft`. Startbereit wird dadurch **0091**.

Der Befund hat einen eigenen Punkt hinterlassen: Die Umstellung auf eine aus der Wand
gebildete Schranke hat die **absolute** Speichergrenze ersatzlos entfernt. Daraus ist
**0159** geworden (`offen`, hinter 0091 auf `verlauf.hpp`). Das ist kein Rücklauf auf
dieses Paket — seine Abnahme war die Wandbindung, und die ist erfüllt.

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, und 0091 rueckt dahinter

Fünf Prüfungen. **Rolle** `kernbauer`, in `BAUROLLEN`, Prüfer `kern-pruefer` — beides
heute mehrfach gelaufen. **Abnahme** vier Bedingungen; Bedingung 1 ist tragend und in der
richtigen Form gestellt, weil sie einen *Lauf* verlangt und keine Trefferzahl in einem
Text. Bedingung 4 vergleicht gegen den unmittelbar vorhergehenden Stand desselben Baums
und desselben Profils und nennt den Bezugsstand — das ist die einzige Form, die ein
Bauagent hier erreichen kann. **Nummer** 0144 war frei. **Abhängigkeit** 0140 steht seit
diesem Lauf auf `fertig`; das Urteil vom 19:51 lautet `geprueft`. Sie ist erfüllt.

## Die Reihenfolge gegen 0091 ist entschieden, und zwar so, wie der Vorschlag sie beantragt

`0091-diff-ursachenkette-nach-t20` hält dieselben drei Dateien und drei weitere. Beide
können nie nebeneinander laufen; welches zuerst geht, war offen, und der Vorschlag bittet
ausdrücklich darum, dieses vorzuziehen. Ich ziehe es vor, aus dem Grund, den er nennt:
Wer die Rückwärtsauflösung auf zwanzig Plätze baut, schreibt die Bindung an R ein zweites
Mal hin, und dann kostet ihre Rücknahme zwei Gewerke statt einer Zeile.

**0091 trägt deshalb ab heute `haengt_an: [0144]`.** Das ist eine Reihenfolgesperre und
keine fachliche Abhängigkeit — 0091 braucht von diesem Paket keinen Baustein, es darf nur
nicht davorlaufen. Der Vermerk steht auch dort.

## Was ich nicht entschieden habe, und warum das so bleibt

Der Vorschlag lässt dir drei Wege offen, die Kapazität von R zu lösen: die Wand aus T40,
ein Parameter am Behälter, oder ein Aufbau ohne feste Rundenzahl. **Das ist deine Wahl,
nicht meine** — sie ist eine Entwurfsentscheidung im Kasten und keine Reihenfolgefrage.
Bedingung 3 nennt für zwei der drei Wege einen Nachweis und sagt für den dritten, dass sie
mit ihm entfällt; das trägt.

**Findest du dagegen, dass T40 und T19 einander an dieser Stelle widersprechen** — dass
also keine der drei Fassungen beide erfüllt —, dann liefere nichts und melde es hier und
in deinem Logbuch. Ein Widerspruch in `specs/` ist nichts, was ein Bauagent auflösen darf,
und nichts, was ich auflöse; er gehört dem Geschäftsführer.

# Die Rundenkapazitaet des Verlaufs ist die Partielaenge R, und T40 verbietet das

## Der gemessene Sachverhalt

Nachgemessen am 2026-09-05 am Stand `c19e388`, Nachweis unter
`ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/pruefung-0140-verlauf-sammelt-die-rundenketten-2026-09-05.md`.

`kern/include/kern/verlauf.hpp` fuehrt die Konstante `RUNDEN_KAPAZITAET` mit dem Wert
zwanzig und begruendet sie im selben Kopf damit, dass zwanzig die Partielaenge R aus
`spiel.md` sei. Wird sie erreicht, bricht `beginne_runde` hart ab.

T40 in `specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md` sagt, dass die
Partielaenge R eine Groesse des Jahrgangs ist und keine Konstante des Codes, und dass
keine aus ihr abgeleitete Zahl irgendwo als Literal steht. T40 rechnet mit anderen Werten
-- seine Ableitungstabelle fuehrt jede abgeleitete Groesse fuer die Partielaenge
vierundzwanzig vor -- und zieht die Wand erst oberhalb von sechsundzwanzig, dort
nachgerechnet und begruendet.

T19, die Vorgabe, aus der Paket 0140 entstanden ist, verlangt eine feste
Aufnahmekapazitaet **je Runde**. Eine Kapazitaet ueber die Partie verlangt sie nicht.

**Der Fehler, Schritt fuer Schritt.** Ein Jahrgang mit fuenfundzwanzig Stuetzstellen
ergibt nach T40 die Partielaenge vierundzwanzig, und die liegt innerhalb der Wand. Eine
Sitzung, die diesen Jahrgang spielt und die Ketten nach T19 sammelt, nimmt zwanzig Runden
auf und bricht in der einundzwanzigsten ab. Gemessen im Profil mit Sanitizern, zweimal:
einmal ueber `aufnehmen` mit einer vollen Kette, einmal ueber eine gelaufene Partie im
weltlauf, deren Rundennummern aus dem Zustand kommen. Derselbe Abbruch trifft den Lauf
ueber zweihundert Runden ohne Spieler, den technik.md und `spiel.md` dem Bruchtester
auferlegen: zwanzig von zweihundert Runden aufgenommen, dann Abbruch.

## Warum das ein eigenes Paket ist

**Es ist kein Rueckstand von 0140.** Die vier Abnahmebedingungen von 0140 sind erfuellt,
gemessen und im Befund abgedruckt; das Urteil steht auf `geprueft`. Keine der vier nennt
eine Kapazitaet ueber die Partie. Die Konstante ist eine Zugabe, und sie zurueckzunehmen
ist eine andere Arbeit als die, die 0140 bestellt hat.

**Es gehoert nicht in 0091.** `0091-diff-ursachenkette-nach-t20` haelt dieselben drei
Dateien und ist der erste Leser des Verlaufs. Genau deshalb muss die Kapazitaetsfrage
**vor** ihm entschieden sein: Wer die Rueckwaertsaufloesung auf zwanzig Plaetze baut,
schreibt die Bindung an R ein zweites Mal hin, und T40 nennt in seiner eigenen
Begruendung die Verbreitung einer Zahl als den teuren Teil, nicht die Zahl.

**Die Dateiliste schneidet sich mit 0091.** Beide Pakete koennen nicht gleichzeitig
laufen; welches zuerst geht, entscheidet der Projektmanager. Der Vorschlag hier ist,
dieses zuerst zu planen, weil es eine Zeile aendert und 0091 ein Gewerk ist.

**Es ist keine Geschmacksfrage.** Der Kopf des Kastens haelt die Entscheidung fuer
richtig und beruft sich darauf, dass der Pruefstand die Ketten nach T19 wegwerfen darf,
wenn er nur Ergebnisse zaehlt. Das stimmt und traegt den Verzicht des Pruefstands. Es
traegt nicht die Bindung der Kapazitaet an R -- die steht gegen T40, und T40 ist keine
Auslegung, sondern ein T-Block.

## Was nicht dazugehoert

- **Der Jahrgang im Kern.** Weder `stuetzstellen` noch die Partielaenge R sind heute
  irgendwo im Kern gefuehrt; dieses Paket baut sie nicht ein. Es genuegt, die Kapazitaet
  des Behaelters von R zu **loesen** -- ob ueber die Wand aus T40, ueber einen Parameter
  am Behaelter oder ueber einen Aufbau ohne feste Rundenzahl, entscheidet der Bauagent.
- **Die Aufnahmekapazitaet je Runde.** Sie ist aus `kern::schreiber::KETTE_KAPAZITAET`
  abgeleitet, nach T18 hergeleitet und richtig. Sie bleibt, wie sie ist.
- **`kern/include/kern/zustand.hpp` und `kern/src/zustand.cpp`.** Nicht anzufassen, wie
  schon in 0140.
- **Die Rueckwaertsaufloesung.** Das ist 0091.

## Abnahme

1. **Eine Partie mit einer nach T40 zulaessigen Partielaenge laeuft durch.** Ein Verlauf
   nimmt die Ketten einer Partie ueber sechsundzwanzig Runden auf, ohne abzubrechen, und
   gibt zu jeder Runde die Kette wieder heraus, die er bekommen hat. Der Nachweis druckt
   die Rundennummern und die Gliederzahlen ab. **Ein Verlauf, der bei zwanzig abbricht,
   erfuellt diese Bedingung nicht**, und ein Nachweis, der nur bis zwanzig zaehlt, ist von
   einem, der sie erfuellt, nicht zu unterscheiden.

2. **Keine Zahl im Kasten ist mehr die Partielaenge.** Weder Quelltext noch Kopf fuehren
   eine Konstante, die als R oder als eine aus R abgeleitete Groesse begruendet ist; der
   Kopf sagt stattdessen, woraus die Kapazitaet des Behaelters folgt. Gibt es weiterhin
   eine obere Schranke, ist ihr Erreichen ein harter Fehler mit einer Meldung, die die
   Schranke nennt -- zweiseitig nachzuweisen wie in 0140, beide Laeufe abgedruckt. Eine
   stille Kuerzung bleibt nach T19 ausgeschlossen.

3. **Die Speicherschranke im Kopf greift wieder.** Die Zusicherung ueber die Groesse des
   Behaelters reisst am ersten Wert oberhalb des zugelassenen Bereichs und nicht erst
   weit darueber; am Stand `c19e388` riss sie erstmals bei einunddreissig Runden, also
   oberhalb jeder nach T40 zulaessigen Partielaenge und damit fuer keinen erreichbaren
   Fall. Der Nachweis nennt die gemessene Groesse des Behaelters und den ersten Wert, an
   dem die Zusicherung zuschlaegt. Faellt die feste Rundenzahl ganz weg, entfaellt diese
   Bedingung mit ihr; das ist dann im Nachweis zu sagen.

4. **Beide Profile gruen.** Konfigurieren, Bauen und `ctest` mit `FABRIK_SANITIZER=ON`
   und mit `OFF`, je Code 0, im Alleinbau des Kerns und im Arbeitsbereich. Die Zahl der
   ctest-Eintraege bleibt gegenueber dem unmittelbar vorhergehenden Stand desselben Baums
   und desselben Profils gleich oder steigt um die Proben, die dieses Paket anlegt; der
   Bezugsstand wird genannt.

# GEBAUT -- 2026-09-05, Kernbauer

Nachweis: `befunde/messung-0144/nachweis.py`, Bericht `befunde/messung-0144/bericht.md`,
Ergebnis **Abweichungen: 0**. Der Vorher-Stand liegt als Kopie in
`befunde/messung-0144/vorher/`; HEAD taugt nicht als Bezug, weil Fremdlaeufe waehrend des
Laufs committen.

## Der gewaehlte Weg von den dreien: die Wand aus T40

`RUNDEN_KAPAZITAET` ist nicht mehr die Partielaenge, sondern folgt aus
`PARTIELAENGE_HOECHSTENS` -- der Schranke, ab der T40 den Jahrgangsbau abbrechen laesst
(hoechstens sechsundzwanzig, dort nachgerechnet an der Kollision der Ergebnisbaender).
Damit traegt derselbe Behaelter jede Partie, die der Jahrgangsbau ueberhaupt zulaesst,
und keine Zahl des Codes haengt an der geladenen Zeitreihe.

**Die beiden anderen Wege habe ich verworfen, und zwar nicht nach Geschmack.** Ein
Aufbau ohne feste Rundenzahl braucht Speicherzuteilung; im ganzen Kern steht keine
einzige, und eine hier waere eine Abweichung von `specs/`, die ein ADR braucht. Ein
Parameter am Behaelter waere ein Schablonenparameter -- er stuende in jeder Signatur, die
0091 und die Sitzung schreiben, und veraenderte die Schnittstelle fuer alle, um dieselbe
Zahl an einer anderen Stelle wieder hinzuschreiben.

**T40 und T19 widersprechen einander an dieser Stelle nicht.** T19 verlangt eine feste
Aufnahmekapazitaet **je Runde** -- die bleibt unveraendert aus `kern::schreiber` abgeleitet
-- und verbietet die stille Kuerzung. Beides ist mit einer Kapazitaet ueber die Partie
vereinbar, solange sie nicht aus R stammt und ihr Erreichen hart abbricht.

## Die vier Bedingungen

1. **Erfuellt.** `verlauf_probe` laeuft eine Partie ueber sechsundzwanzig Runden ueber
   `kern::schritt::schritt` und druckt je Runde Rundennummer und Gliederzahl ab (je 175).
   Die Zahl kommt aus `PARTIELAENGE_HOECHSTENS`, steht also nicht abgeschrieben da.
   **Der Beleg, dass der Lauf nicht leer ist:** Der Wegwerfbaum `kapazitaet-20` bindet die
   Kapazitaet wieder an R, uebersetzt gruen -- und `verlauf_probe` wird rot mit "der
   Verlauf ist voll". Vier Runden waeren auch mit der alten Kapazitaet gruen gelaufen.
2. **Erfuellt.** Mechanisch geprueft und im Bericht abgedruckt: einzige Zahlkonstante im
   Kopf ist `PARTIELAENGE_HOECHSTENS`, aus T40 begruendet; `RUNDEN_KAPAZITAET` ist keine
   Zahl mehr. Die obere Schranke bleibt und bricht hart ab -- zweiseitig nachgewiesen,
   beide Laeufe im Wortlaut, die Meldung nennt die Schranke und `kern::verlauf` und nennt
   `kern::schreiber` nicht.
3. **Erfuellt.** Gemessen: `sizeof(Verlauf)` = 451.784 Byte, `sizeof(Kette)` = 17.368. Die
   Zusicherung haengt jetzt an `PARTIELAENGE_HOECHSTENS + 1` statt an einem halben
   Megabyte und reisst beim **ersten** Wert oberhalb der Wand: Baum `kapazitaet-27` wird
   rot. Der Kontrollbaum `alte-schranke-27` zeigt denselben Verstoss mit der alten
   Bytezahl **gruen** -- sie griff erst bei einunddreissig, also fuer keinen erreichbaren
   Fall.
4. **Erfuellt.** Konfigurieren, Bauen und `ctest` je Code 0, mit `FABRIK_SANITIZER=ON` und
   `OFF`, im Alleinbau des Kerns und im Arbeitsbereich. Bezugsstand ist der Baum mit den
   Dateien aus `vorher/`: ctest-Eintraege 12 vorher, 12 nachher (das Paket legt keine
   Probe an); Arbeitsbereich 18. Die Ausgabe der drei rechnenden Proben ist vorher und
   nachher zeichengleich.

## Zwei Dinge fuer den Projektmanager, nicht fuer den Pruefer

**Worauf ich unsicher bin:** Der 200-Runden-Lauf des Bruchtesters bricht weiter ab, wenn
ihn jemand einen Verlauf fuehren laesst -- jetzt in Runde 27 statt 21. Ich halte das fuer
richtig, weil T19 diesen Lauf als kettenfrei ausweist und er nach `spiel.md` Wertebereiche
prueft statt eine Partie zu spielen. Die Abnahme verlangt es nicht; es ist eine
Entscheidung.

**Zweimal lagen halbfertige Fremddateien im Kern**, waehrend ich gemessen habe
(`werkzeuge/belegstellen/belegstellen_riegel.cpp`, dann `kern/test/aktion_probe.cpp` mit
offener Klammer). Beide gehoeren nicht zu diesem Paket, beide haben sich von selbst
erledigt. `befunde/messung-0144/warte_und_messe.py` wartet deshalb, bis der Baum
uebersetzt, und startet den Nachweis erst dann -- sonst misst er den fremden Lauf.
