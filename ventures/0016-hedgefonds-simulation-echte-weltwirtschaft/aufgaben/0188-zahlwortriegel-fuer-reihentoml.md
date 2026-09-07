---
id: 0188-zahlwortriegel-fuer-reihentoml
rolle: testentwickler
status: gebaut
haengt_an: [0180-zahlwortriegel-fuer-werte-hpp]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`, unveraendert. 0180 ist eine echte sachliche Abhaengigkeit und zugleich eine Dateisperre -- ihr teilt `werkzeuge/zahlwort/CMakeLists.txt`, und 0180 baut den Riegel, den du auf eine zweite Datei ausdehnst. Es ist heute Nacht eingeplant; du ruecktest nach, sobald es abgenommen ist. Deine zweite Datei `befunde/messung-0099/zahlwoerter.py` haelt niemand. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer.
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0099/zahlwoerter.py]
abnahme: Die drei Bedingungen unter "Abnahme".
---

# Die Zahlwoerter im Kopf von `reihen.toml` werden nachgezaehlt, statt fortgeschrieben

**Vorgeschlagen am 2026-09-06 vom daten-pruefer**, aus dem Lauf zu `0126`
(`befunde/pruefung-0126-historischer-verweis-nennt-den-falschen-commit-2026-09-06.md`,
Befund 2).

## Der Befund, aus dem er kommt

Der Kopfkommentar von `daten/reihen.toml` traegt Saetze, die zaehlen, was in derselben
Datei steht: "Ueberhaupt genannt wird er in **sieben** ... Diese sieben zerfallen ohne
Rest in **zwei plus eins plus vier**". Die Zahl gilt fuer Blattwerte, die die
Zeichenfolge `einheitenbefund-pwt-baci` tragen.

Sie ist binnen zweier Tage **zweimal** falsch geworden, beide Male ohne dass jemand die
Zaehlung angefasst haette, und beide Male, weil ein Paket in `pruefweg.toml_geprueft`
einen Nachtrag schrieb, der eine Datei beim Namen nennt:

- `0099` bewegte die erste Zahl. Berichtigt hat es `0142`.
- `0126` bewegte die zweite: sieben auf acht, `zwei plus eins plus vier` auf
  `zwei plus eins plus fuenf`. Berichtigt hat es ebenfalls `0142` -- ohne Auftrag dafuer,
  denn `0142` sollte die Vorlagentabelle nachziehen, nicht diese Zaehlung.

Beide Male hat die Zahl **einen Lauf ueberlebt, in dem sie schon falsch war**, und
beide Male hat sie derselbe zufaellig danebenstehende Lauf gefunden. Der Bauagent von
`0126` hat sorgfaeltig nachgewiesen, dass alle Kommentarzeilen ausser der geaenderten
zeichengleich geblieben sind -- ein Beweis, den er als Erfolg fuehrt und der in
Wahrheit die Luecke belegt.

**Das Werkzeug liegt seit `0099` im Baum und ist nicht gelaufen:**
`befunde/messung-0099/zahlwoerter.py` zaehlt genau diese drei Groessen. Ein Aufruf haette
den Fehler in beiden Faellen sofort gezeigt. Er kostet unter einer Sekunde. Das ist die
Sorte Arbeit, die kein Agent im Kopf behalten sollte.

## Was der Riegel prueft

`zahlwoerter.py` zaehlt heute und **vergleicht nicht**; es druckt Zahlen, die ein Leser
gegen die Prosa halten muss. Das Paket macht daraus eine Probe mit Rueckgabewert. Drei
Behauptungen des Kopfkommentars gegen drei Zaehlungen derselben Datei:

1. **"Der Stand der \<N\> Vorlagen"** gegen die Zahl der Schluessel in
   `[datei.vorlagen]`.
2. **Das Zahlwort vor "genannt"** gegen die Zahl der Blattwerte mit der Marke
   `einheitenbefund-pwt-baci`.
3. **Die Zerlegung "\<a\> plus \<b\> plus \<c\>"** gegen die Aufteilung derselben Menge
   in `beleg` + Vorlagenschluessel + Rest.

Alle drei Zaehlungen sind fertig und gemessen -- sie stehen in `zahlwoerter.py` und sind
seit `0099` zweimal gegen historische Blobs bestaetigt. **Neu ist allein die
Vergleichsseite**, also das Herausloesen des Zahlworts aus der Prosa. Genau diese Frage
entscheidet `0180` fuer `werte.hpp`, und die Entscheidung ist zu uebernehmen statt neu
zu treffen: gepruefte Form ist **bestimmter Artikel plus Kardinalzahl**, eine
Ordnungszahl behauptet keine Anzahl. Das ist der eigentliche Grund fuer `haengt_an`.

## Warum das ein eigenes Paket ist

**Nicht Teil von `0126` oder `0142`.** `0126` steht auf `gebaut` und hat die Zahl
bewegt, ohne dafuer einen Auftrag zu haben; `0142` hat sie berichtigt, ebenfalls ohne
Auftrag. Beide sind Aenderungen an Prosa. Ein Werkzeug in ihre `dateien`-Liste zu nehmen
mischte den Arbeitsbereich eines Datenbauers mit einem Riegel.

**Nicht Teil von `0180`, obwohl es dieselbe Krankheit heilt.** `0180` schneidet sich
ausdruecklich auf `werte.hpp` zu und begruendet das damit, dass ein allgemeiner
Zahlwortriegel raten muesste, was eine Zahl im Kommentar zaehlt: "Wer den Riegel spaeter
allgemein will, braucht zuerst eine **erklaerte** Zaehlmarke im Kommentar -- das waere
ein anderes Paket und eine Entwurfsfrage." Dieses Paket ist jenes andere -- **ohne die
Entwurfsfrage**, weil hier nichts zu raten ist: Die Zaehlregel ist schon geschrieben,
laeuft und ist gegen zwei historische Staende belegt.

**Nicht Teil des Belegstellen- oder Bezeichnerriegels**, aus dem Grund, den `0180`
dafuer nennt: Beide lesen den ganzen Kern und pruefen Verweise beziehungsweise Namen.
Hier wird Prosa gegen den Inhalt derselben einen Datei gezaehlt.

## Die Bauform, und warum sie billig ist

Kein C++. `zahlwoerter.py` benutzt `tomllib`; ein C++-Riegel brauchte einen
TOML-Leser, den das Vorhaben nicht hat, fuer eine Probe unter einer Sekunde.

Die Fabrik hat fuer genau diesen Fall eine Bauform, und sie ist erprobt:
`werkzeuge/schlussriegel/CMakeLists.txt` haengt ein Python-Skript aus `befunde/` per
`add_test` in `ctest`, ohne uebersetzendes Ziel, mit `FATAL_ERROR` statt
`if(EXISTS ...)`, damit ein verschobenes Skript den Bau bricht statt still zu
verschwinden. Dieses Paket baut denselben Kasten -- **in `werkzeuge/zahlwort/`, das
`0180` anlegt**, damit nicht ein zweites Mitglied fuer dieselbe Sorte Probe entsteht.

## Die Kollision, die der Projektmanager sehen muss

`werkzeuge/zahlwort/CMakeLists.txt` steht auch in der `dateien`-Liste von `0180`. Das
ist keine Nachlaessigkeit, sondern der Grund fuer die Abhaengigkeit: Den Ordner legt
`0180` an, dieses Paket haengt eine zweite Probe hinein. Es kann erst laufen, wenn
`0180` `fertig` ist.

**Die Wurzel-`CMakeLists.txt` steht bewusst nicht in meiner Liste.** Den Eintrag in
`FABRIK_MITGLIEDER` macht `0180`; ein zweiter waere falsch. Stellt sich beim Bau heraus,
dass er doch noetig ist, ist das ein Befund an den Projektmanager, keine stille
Erweiterung der Dateiliste.

`befunde/messung-0099/zahlwoerter.py` beansprucht heute kein anderes Paket.

## Abnahme

1. **Die Probe haengt als `add_test` im Arbeitsbereichsbau** und endet am dann geltenden
   Stand von `daten/reihen.toml` mit Code 0, in beiden Bauprofilen. Fehlt das Skript,
   bricht die Konfiguration mit einer Meldung ab, die den erwarteten Pfad nennt --
   nachgewiesen durch einen Lauf mit umbenanntem Skript.
2. **Sie wird rot, wenn Behauptung und Zaehlung auseinandergehen** -- an zwei Sorten
   einzeln nachgewiesen: einmal ein Zahlwort im Kopfkommentar verstellt, einmal ein
   Blattwert ergaenzt, der die Marke traegt, ohne das Zahlwort nachzuziehen. Beide Male
   nennt die Meldung das gefundene Zahlwort, die gezaehlte Zahl und die Zeile. Als
   dritter, festgenagelter Fall der Blob `d18ca197812364ac65dba58dd67a7851339ddfe7`
   (`reihen.toml` nach Paket `0126`), der **rot werden muss** -- dort steht sieben und
   gezaehlt sind acht. Der Nachweis laeuft ueber `git cat-file blob` ohne Zwischendatei
   im Arbeitsbaum.
3. **Sie wird nicht rot an Zahlwoertern, die keine Anzahl behaupten.** Der
   Kopfkommentar fuehrt mehrere Zahlwoerter in Geschichtsabsaetzen ("Paket 0099 hat hier
   ... **sieben** ... gemessen ... und ist seit dem 2026-09-06 widerlegt"). Diese Saetze
   sind ausdruecklich ueberholt und muessen es bleiben duerfen; der Bestand bleibt in
   beiden Profilen gruen. Welche Form die geprueften Stellen von den historischen
   trennt, wird im Kopf der Probe begruendet und nicht nur eingebaut.

**Ein Hinweis ausserhalb der Dateiliste, als Meldung und nicht als Auftrag:**
`parameter.toml` fuehrt nach `befunde/pruefung-0153-...` dieselbe Sorte selbstmessender
Kopfzahl, und `0180` behandelt `werte.hpp`. Ob die drei Proben spaeter einen gemeinsamen
Kasten bekommen, entscheidet nicht dieses Paket.
