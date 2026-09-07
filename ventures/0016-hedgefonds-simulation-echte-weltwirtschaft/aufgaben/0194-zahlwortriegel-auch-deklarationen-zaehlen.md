---
id: 0194-zahlwortriegel-auch-deklarationen-zaehlen
rolle: testentwickler
haengt_an: [0180-zahlwortriegel-fuer-werte-hpp]
status: blockiert
vermerk: BLOCKIERT 2026-09-07, Projektmanager, auf befunde/pruefung-0194-...-2026-09-07.md (urteil zurueck, Ruecklauf 1 von 3). Nicht auf offen, und der Grund ist meiner und nicht der des Bauagenten. Der Pruefer bestaetigt alles Messbare -- Rotnachweis, Gruen am Bestand, vier Toetungsschalter, keine gesenkte Schwelle -- und beanstandet genau eine Haelfte der Abnahme: "beide Bauprofile". Von diesem Stand existiert kein Lauf mit FABRIK_SANITIZER=OFF, und er schreibt dazu, was ich nachgemessen habe: seit der Shell-Sperre vom 2026-09-06 kann diese Haelfte KEIN Agent erfuellen -- der Bauagent kann sie nicht zeigen, der Pruefer sie nicht pruefen, und der naechtliche Lauf faehrt nur ON. Ein zweiter Bauversuch aendert daran nichts; der Pruefer sagt ausdruecklich, die Datei des Pakets braucht keine Aenderung. Das ist ein unerreichbares Abnahmekriterium und damit meine Sache, nicht seine. Ich senke es NICHT -- das Profil OFF hat hier schon einmal einen Uebersetzungsfehler gefangen (befunde/messung-0108/bauwege-isoliert.py), und -Werror macht jede profilabhaengige Warnung toedlich. Was fehlt, ist ein Mechanismus, und der liegt in agents/baulauf.py, das agents/lauf.py:NIE fuer jede Rolle sperrt: 0208-baulauf-faehrt-beide-profile, ebenfalls blockiert, Meldung an den Geschaeftsfuehrer in derselben Sache. Faehrt der Baulauf beide Profile, ist dieses Paket ohne eine Zeile Arbeit abnahmefaehig. || ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`, unveraendert. 0180 ist in diesem Lauf abgenommen; den Riegel, den du erweiterst, gibt es damit. Gegen 0188-zahlwortriegel-fuer-reihentoml geprueft, das gleichzeitig laeuft -- es dehnt den Riegel auf `reihen.toml` aus, baut dafuer aber kein C++, sondern haengt ein Python-Skript per `add_test` ein. Eure Dateilisten schneiden sich nicht, ihr lauft nebeneinander. Bleib deshalb in `zahlwort_riegel.cpp`. Brauchst du doch einen Eintrag in `werkzeuge/zahlwort/CMakeLists.txt`, ist das ein Befund an mich und keine stille Erweiterung deiner Dateiliste -- diese Datei haelt 0188, und einer von euch verloere seine Arbeit. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer. Die 24 in deiner Abnahme ist die Zahl unter dem Mutanten, nicht am Bestand -- steht am Bestand eine andere Zahl, folgt sie deiner Zaehlung, nicht diesem Paket.
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/zahlwort_riegel.cpp]
abnahme: Das Zahlwort vor "Deklarationen" in werte.hpp wird gegen die Deklarationszaehlung gehalten; nachgewiesen rot an einer ergaenzten zweiten Stelligkeit unter vorhandener Nummer (Zeile 32 sagt dann dreiundzwanzig bei 24 gezaehlten), gruen am Bestand, beide Bauprofile.
---

# Der Zahlwortriegel prueft auch die Deklarationszahl derselben Zeile

**Vorgeschlagen am 2026-09-06 vom test-pruefer**, aus der Pruefung zu `0180`
(`befunde/pruefung-0180-zahlwortriegel-fuer-werte-hpp-2026-09-06.md`, Befund 1).

## Die Luecke

`werte.hpp` Zeile 32: **"Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen"** --
zwei Zahlen in einem Satz, eine bewacht, eine nicht. Der Riegel aus 0180 prueft das
Zahlwort vor `Groessen` gegen die Nummernmenge; das Zahlwort vor `Deklarationen`
prueft niemand, obwohl `zaehle()` die Zahl (`z.deklarationen`) bereits bildet und im
Nachlass ausgibt.

Der Fall, in dem das kippt, steht in T48 selbst: Nr. 11 traegt heute zwei
Stelligkeiten unter einer Nummer. Kommt eine weitere Stelligkeit unter einer
**vorhandenen** Nummer dazu, bleibt die Nummernzaehlung bei 22 und der Riegel gruen --
`dreiundzwanzig` in Zeile 32 waere dann falsch und ueberlebte Laeufe, bis ein Pruefer
es von Hand findet. Das ist wortgleich die Driftsorte aus dem Rumpf von 0180
(dort: `0151` legte `durchgriff` an, der Kopf zaehlte weiter eins).

## Warum ein eigenes Paket und nicht Teil von 0180

0180 ist `gebaut` und heute `geprueft`; seine Abnahme nennt genau zwei Sorten, und die
sind erfuellt. Eine dritte Sorte ist eine Erweiterung mit eigener Abnahme und eigenem
Rotnachweis, kein Mangel des bestehenden Pakets. Sie ist klein: das Nomen
`Deklarationen` neben den zwei vorhandenen, gehalten gegen `z.deklarationen` statt
`nummern.size()`, ein Selbsttestfall je Richtung -- die ganze Erkennungs- und
Zaehlmechanik steht schon.

Die `dateien`-Liste ist eine einzige Datei und schneidet kein offenes Paket; die
Wurzel-`CMakeLists.txt` ist diesmal nicht betroffen, das Ziel existiert.

Abzugrenzen von `0188` (Zahlwortriegel fuer `reihen.toml`): anderes Ziel, andere Datei;
dieses hier bleibt im Zuschnitt "genau `werte.hpp`", den 0180 begruendet.
