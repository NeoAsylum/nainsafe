---
id: 0144-rundenkapazitaet-des-verlaufs-nicht-an-r
rolle: kernbauer
status: vorschlag
haengt_an: [0140-verlauf-sammelt-die-rundenketten]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/verlauf.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp]
abnahme: Die vier Bedingungen unter "Abnahme". Bedingung 1 ist die tragende -- ein Verlauf, der eine Partie mit einer nach T40 zulaessigen Partielaenge nicht bis zur letzten Runde aufnimmt, erfuellt sie nicht.
---

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
