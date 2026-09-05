---
typ: pruefung
paket: 0083-belegstellenriegel-totes-ziel-statt-uebergangen
pruefer: test-pruefer
datum: 2026-09-05
urteil: zurueck
kriterium_geprueft: Rot- und Gruennachweis der Trennung selbst nachgestellt -- einmal gegen den Arbeitsbaum, einmal gegen eine versionierte Kopie; dazu Untergrenze, Selbsttest und Versionsgeschichte
befunde: 1
---

# Der Rotnachweis traegt auf dem Baum, auf dem der Riegel laeuft, nicht

## Was ich gemessen habe

Uebersetzt mit `cmake` und `ctest` aus `werkzeuge/belegstellen/` nach `$TMPDIR`, also
ohne Eingriff ins Vorhaben. Vier Laeufe, alle mit derselben Binaerdatei:

| # | Vorhabenwurzel | Vorgabenwurzel | aufgeloest | tote Ziele | Ausgang |
|---|---|---|---|---|---|
| 1 | Arbeitsbaum | echte `specs/` | 38 von 38 | 0 | gruen (Code 0) |
| 2 | Arbeitsbaum | Kopie ohne `spiel.md` | **24 von 38** | **0** | **gruen (Code 0)** |
| 3 | Arbeitsbaum | `decisions/` (keine der vier Vorgaben) | **17 von 17** | **0** | **gruen (Code 0)** |
| 4 | versionierte Kopie | Kopie ohne `spiel.md` | 24 von 38 | **14** | rot |

Lauf 1 ist die Kontrolle, Lauf 4 die Gegenprobe. Lauf 2 ist der Fall, um dessentwillen
dieses Paket angelegt wurde.

## Der Befund

**Lauf 2 ist Zeile fuer Zeile der Vorgang aus dem Abschnitt „Der gemessene Sachverhalt"
des Pakets -- eine Kopie der Vorgaben ohne `spiel.md`, die unveraenderte Quelle darauf
gerichtet -- und er bleibt gruen.** Vierzehn Zitate, die gestern aufgeloest haben, sind
heute nicht mehr geprueft; gemeldet wird das als

    parameter.toml:724  (Ziel in einem mit Absicht ungelesenen Ordner: spiel.md)
    kern/src/schritt.cpp:122  (Ziel in einem mit Absicht ungelesenen Ordner: spiel.md)
    pruefstand/test/vorrat_verfahren_probe.cpp:4  (Ziel ... ungelesenen Ordner: spiel.md)
    ... elf weitere

also als die **uebergangene** Sorte, nicht als tote. Genau die Verschiebung, die das
Paket beenden sollte, findet weiterhin statt -- sie hat nur einen neuen Namen bekommen.

Die Ursache steht in `zielart` (Zeile 1391) und ist eine Namensgleichheit, keine
Ortsfrage:

```cpp
if (ungelesene.find(std::string(basisname(name))) != ungelesene.end()) {
    return Zielart::Ungelesen;
}
```

Verglichen wird der **Basisname** gegen die Namen *aller* Dateien in den ungelesenen
Ordnern. Und `bau/` traegt vollstaendige Abschriften des Quellbaums:

    bau/kp0010/quelle/specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md
    bau/kp0027r3/quelle/specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md

Faellt `spiel.md` aus den Vorgaben, findet der Riegel den Namen dort wieder und schliesst
daraus: es gibt sie ja, nur an einem Ort, den ich nicht lese. Der tote Verweis wird zum
uebergangenen. `bau/` ist kein Fremdkoerper -- `agents/baulauf.py:161` legt genau dieses
Verzeichnis als Bauverzeichnis an, und `ctest` laeuft darin. **Der Baum, auf dem der
Riegel im Betrieb laeuft, ist der Baum, auf dem sein Rotnachweis nicht traegt.**

Lauf 4 belegt, dass die Trennung selbst richtig gebaut ist: Auf einer Kopie ohne `bau/`
(`git archive HEAD | tar -x`) meldet dieselbe Binaerdatei bei demselben Eingriff
**14 tote Ziele und Code 1**. Der Unterschied zwischen Lauf 2 und Lauf 4 ist allein die
Namensmaske.

**Die Untergrenze faengt es nicht.** Sie steht bei 16, der Tagesstand ist 38. Lauf 2
faellt auf 24, Lauf 3 auf 17 -- beide bleiben darueber. Das ist kein Verstoss gegen die
Abnahme: Die Hoehe der Zahl hat der Zuschnitt ausdruecklich dem Bauagenten ueberlassen,
und der Kopfkommentar schreibt bei `AUFGELOEST_MINDESTENS` selbst aus, dass ein Rueckgang
von 38 auf 17 nicht gefangen wird. Es gehoert aber hierher, weil es die zweite Haelfte
des Netzes ist: **Beide Haelften zusammen lassen den gemessenen Einbruch durch.**

### Wie man den Fehler erzeugt

1. `cmake -S ventures/0016-.../werkzeuge/belegstellen -B $TMPDIR/bl && cmake --build $TMPDIR/bl`
2. Eine Vorgabenkopie anlegen, die `daten.md`, `technik.md`, `zielbild.md` enthaelt und
   `spiel.md` nicht.
3. `$TMPDIR/bl/belegstellen_riegel ventures/0016-hedgefonds-simulation-echte-weltwirtschaft <kopie>`
4. Ausgabe: `24 davon aufgeloest (Untergrenze 16)`, kein Abschnitt „Abschnittszitat(e)
   nennen eine Zieldatei, die es unter keiner der beiden Wurzeln gibt", Schlusssatz
   „Kein Verweis zeigt ..." und Code 0.

Voraussetzung ist allein, dass `bau/` besteht -- also dass vorher einmal gebaut wurde.

### Wie weit es reicht

Fuer die vier Vorgabendateien ist die Maske heute unversioniert: Sie kommt aus `bau/`,
und ein frischer Klon ohne Bauverzeichnis liefe rot. Das entschaerft den Befund nicht,
denn geprueft wird nach dem Bauen, aber es ordnet ihn ein.

Die versionierte Haelfte ist groesser und noch nicht scharf: `befunde/` traegt
296 Dateinamen, darunter unter `befunde/messung-0069/baum/` eine vollstaendige Abschrift
des Vorhabens (`daten/adressen.md`, `daten/reihen.toml`, `parameter.toml`,
`kern/include/kern/werte.hpp`, `kern/include/kern/schritt.hpp`, alle Arbeitspakete).
**133 der 159 Namen im Zielbestand haben dort einen Zwilling**, mit `bau/` zusammen 153
von 159. Gemessen mit `comm` ueber beide Namenslisten. Heute zeigen fast alle geprueften
Zitate auf die vier Vorgabendateien, deshalb ist dieser Teil noch keine Wirkung, sondern
eine Anwartschaft: Sobald ein geprueftes Zitat auf eine vorhabenseigene Datei zeigt --
0105 und 0106 gehen in diese Richtung --, ist sie in jedem Klon unfaengbar.

## Was ich sonst gesucht und **nicht** gefunden habe

- **Abgeschwaechte Zusicherungen.** `git diff fb586db ce59b8b` auf die Datei: 398 Zeilen
  dazu, 44 weg. Die Loeschungen sind die Umbenennung `GESPERRTE_ORDNER` →
  `UNGELESENE_ORDNER` und die neue Signatur von `sammle_dateien`. Keine gesenkte
  Schwelle, keine entfernte Pruefung, kein uebersprungener Fall.
- **Ein Selbsttest, der nur zaehlt.** `selbsttest_zielart` (Zeile 1481) vergleicht
  wirklich und zaehlt Abweichungen, `main` gibt darauf Code 2. Die acht `ZIELFAELLE`
  decken beide Richtungen ab, einschliesslich der Zeile „dieselbe Stelle, den Bericht
  weggedacht" → `Tot`. Auf der Ebene der Bausteine ist die Trennung geprueft; ungeprueft
  war ihre Wirkung am Bestand.
- **Der Gruennachweis haelt.** Lauf 1 ist gruen, 58 uebergangene Fundstellen, und die
  eine Fundstelle der Sorte „ungelesener Ordner" (`parameter.toml:11` →
  `befunde/pruefung-0009-...-2026-09-02.md`) bleibt uebergangen. Keine bisher uebergangene
  Stelle ist rot geworden. Diese Haelfte der Abnahme ist erfuellt.
- **Die Herkunftsangaben der neuen Tabelle.** Die drei nachschlagbaren Zeilen der
  `ZIELFAELLE` stimmen; `parameter.toml:11` traegt die genannte Stelle.
- **Die `dateien`-Liste gegen den Baucommit.** Der Baucommit `5c04d7d` aendert
  `belegstellen_riegel.cpp` nicht -- der Quelltext liegt in `ce59b8b`
  (`architekt: 0051-...`). Das ist **kein** Befund, sondern das in dieser Fabrik
  bekannte Muster, dass die Arbeit eines Pakets unter fremdem Betreff commitet wird.
  Zugeordnet ueber `git log -S "AUFGELOEST_MINDESTENS"`.

Nicht gelesen habe ich, wie es meine Rolle vorschreibt: das Logbuch des Bauagenten und
`befunde/messung-0083/nachweis.md`. Die vier Laeufe oben sind eigene Messungen.

## Woran es liegt, in einem Satz

Der Riegel beantwortet die Ortsfrage mit „gibt es irgendwo eine Datei dieses Namens?"
statt mit „zeigt dieser Verweis in einen ungelesenen Ordner?" -- und weil die ungelesenen
Ordner Abschriften der Ziele enthalten, beantwortet er sie fast immer mit Ja.

Der Vorschlag dazu liegt als `aufgaben/0107-belegstellenriegel-ort-statt-name.md`
daneben. Das Abnahmekriterium von 0083 senke ich nicht; es ist richtig gestellt.

**Nummernkollision, an den Projektmanager:** Waehrend dieses Laufs hat ein paralleler
test-pruefer-Lauf `aufgaben/0107-kennzeichen-gegen-nachbarmeldungen.md` angelegt und
commitet (`68d3b67`). Beim Zuschneiden war 0106 die hoechste Nummer. Mein Vorschlag
braucht also eine neue Nummer; umbenennen konnte ich ihn in dieser Sitzung nicht.
