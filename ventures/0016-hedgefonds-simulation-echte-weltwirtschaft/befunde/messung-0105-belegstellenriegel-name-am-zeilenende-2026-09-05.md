---
typ: messung
paket: 0105-belegstellenriegel-name-am-zeilenende
rolle: testentwickler
datum: 2026-09-05
bezugsstand: 456aefa (die eingefrorenen Baeume) und 0333b81 -> 4bbd069 (Arbeitsbaum, mit fremder Drift -- siehe unten)
ergebnis: die drei Nachweise der Abnahme liegen vor, alle elf Faelle des Messstands gruen
---

# Der Name endet, wo seine Zeile endet

## Was dieser Lauf vorgefunden hat

**Die Codeaenderung lag schon da.** Ein frueherer, abgebrochener Lauf desselben Pakets
hatte sie gebaut; der Projektmanager hat sie in `0333b81` mitcommittet, ohne dass der
Status des Pakets von `offen` wegging -- deshalb hat der Runner es erneut eingeplant.
Vorgefunden waren: die Regel in `name_ohne_anfuehrung`, die Herkunftsliste in `Absatz`,
`absatz_aus_fall` als gemeinsamer Weg fuer Ernstfall und Selbsttest, vier neue Faelle in
`ZITATFAELLE` und ein Messstand unter `befunde/messung-0105/` mit drei Baeumen.

**Gefehlt hat alles, was die Abnahme als Nachweis verlangt.** Gelaufen war nur der
Vorlauf -- zwei Faelle auf dem unveraenderten Baum. Die vier Faelle mit einem
Zeilenumbruch waren nie rot gesehen worden, die Baeume `baum_gut` und `baum_tot` nie
gemessen, und der Kopfkommentar trug die Entscheidung nicht. Er trug stattdessen einen
Verweis auf einen Abschnitt, den es nicht gab (`Absatz`, "Begruendung im Kopf").

## Was dieser Lauf getan hat

1. **Den fehlenden Kopfabschnitt geschrieben** -- `## Der Name am Zeilenende -- Paket
   0105`, dazu die vierte Grenze in der Liste der ausgeschriebenen Grenzen (vorher
   "Drei Grenzen"). Damit ist die Entscheidung dort begruendet, wo die Abnahme sie
   verlangt: an einer **benannten Eigenschaft** (`Absatz::zeile_bei`), nicht an einer
   Liste von Faellen. Der verwaiste Verweis in `Absatz` nennt jetzt den Abschnitt.
2. **Die drei Nachweise gemessen** -- unten im Wortlaut.
3. **Zwei Mutanten gebaut**, weil die vier Selbsttestfaelle sonst nur mitgelaufen
   waeren.
4. **Eine falsche Behauptung im Quelltext berichtigt.** Der Kommentar ueber der
   Umbruchgruppe in `ZITATFAELLE` sagte, ohne die Regel reissen "die ersten drei" und
   der vierte "bleibt gruen". Gemessen reissen 1, 2 und **4**; der dritte bleibt gruen
   und faellt erst bei der anderen Mutation. Der Satz war nie gemessen worden.
5. **Den Messstand um vier Eintraege erweitert** -- die Rueckgabewerte im Wortlaut, die
   zwei Mutantenselbsttests und ein Paar auf dem Arbeitsbaum von heute.
6. **`vergleich.py` berichtigt.** Es verglich mit `in` und damit deduplizierend. Der
   gedruckte Wortlaut einer Fundstelle ist nicht schluesselfaehig -- "gesucht war: 7"
   steht sechzehnmal da. Verglichen wird jetzt als Mehrfachmenge; erst dadurch ist die
   Aussage unten ueber **genau fuenf** abweichende Zeilen belastbar.

## Nachweis 1 -- rot vorher, gruen nachher an der Stelle aus dem Rumpf

`baum_gut` ist die Kopie des Bezugscommits mit **einer** angehaengten Belegstelle in
`rueckstand.md`, genau der zwei Zeilen langen Form aus dem Arbeitspaket.

| | Zitate | aufgeloest | uebergangen | Rueckgabewert |
|---|---|---|---|---|
| Fassung vorher | 37 | 36 | 47 | **1** |
| Fassung nachher | 37 | **37** | 47 | **0** |

Die Fassung vorher nennt als Grund:

```
gesuchte Ueberschrift: Reihe 1 und wird dort nicht bestritten
```

Das ist der Fehler im Wortlaut: der Name plus der halbe Folgesatz. Die Fassung nachher
loest dasselbe Zitat auf. **Das Zitat verschwindet nicht in die uebergangenen
Fundstellen** -- deren Zahl bleibt auf beiden Seiten 47; es wechselt von "gefunden, nicht
aufgeloest" zu "aufgeloest".

## Nachweis 2 -- die Lockerung laesst keine tote Belegstelle durch

`baum_tot` ist dieselbe Stelle mit `Reihe 99`, einer Ueberschrift, die
`lizenzbefund-reihen.md` nicht fuehrt.

| | Zitate | aufgeloest | Rueckgabewert |
|---|---|---|---|
| Fassung vorher | 37 | 36 | **1** |
| Fassung nachher | 37 | 36 | **1** |

Beide rot, und der Unterschied steht in der Meldung:

```
vorher:   gesuchte Ueberschrift: Reihe 99 und wird dort nicht bestritten
nachher:  gesuchte Ueberschrift: Reihe 99
```

Die Regel **kuerzt** den Namen, sie **verzeiht** ihn nicht. Was die Zieldatei nicht
fuehrt, bleibt ein Befund -- und die Meldung nennt jetzt den Namen statt des halben
Nebensatzes, ist also zugleich besser lesbar.

## Nachweis 3 -- kein aufgeloestes Zitat faellt weg

Gemessen auf **zwei** Bestaenden, beide Male beide Fassungen im selben `ctest`-Aufruf.
Der zweite ist der "dann geltende Korpus", den die Abnahme meint.

| Bestand | Fassung | Zitate | aufgeloest | uebergangen |
|---|---|---|---|---|
| `baum` (456aefa, eingefroren) | vorher | 36 | 36 | 47 |
| `baum` | nachher | 36 | 36 | 47 |
| Arbeitsbaum (heute) | vorher | 37 | 37 | 47 |
| Arbeitsbaum | nachher | 37 | 37 | 47 |

Die Abnahme nennt 38 Zitate; der Bestand fuehrt am Messtag 37. Die Abnahme sagt selbst
"auf dem dann geltenden Korpus" -- gemessen ist deshalb die **Bedingung** (keines faellt
weg), nicht die Zahl.

Die Zahlen allein wuerden das nicht tragen, also ist die ganze Ausgabe Zeile fuer Zeile
als Mehrfachmenge verglichen. Von 111 Zeilen weichen **genau fuenf** ab, auf beiden
Bestaenden dieselben fuenf:

* die Zeile mit dem Aufrufpfad (`riegel_vorher` gegen `riegel_nachher`) -- ein Artefakt
  des Messstands;
* die Selbsttestzeile: 9 Faelle zur Form ohne Anfuehrung gegen 13 -- die vier neuen;
* **drei uebergangene Fundstellen, deren gedruckter Name jetzt am Umbruch endet.**

Die dritten sind die einzige inhaltliche Abweichung, und sie ist die gewollte:

```
vorher:  gesucht war: 7 stehen in
nachher: gesucht war: 7

vorher:  gesucht war: 7 und Abschnitt 17 specs/0016-.../daten.md Quellen und Lizenzen daten/deckungsbefund-1997.md
nachher: gesucht war: 7 und Abschnitt 17

vorher:  gesucht war: 17 specs/0016-.../daten.md Quellen und Lizenzen daten/deckungsbefund-1997.md
nachher: gesucht war: 17
```

Alle drei sind Gliederungsziffern aus `daten/reihen.toml`, alle drei waren vorher
uebergangen und sind es nachher. **Keine Fundstelle wechselt die Gruppe, keine kommt
dazu, keine faellt weg.**

## Dass die vier Selbsttestfaelle die Regel wirklich decken

Ein Fall, der nie rot wird, prueft nichts. Zwei Mutanten, je einer fuer eine Haelfte der
Regel, angelegt von `mutiere.py` aus dem **ausgelieferten** Stand -- das Skript bricht
ab, wenn der erwartete Wortlaut nicht genau einmal vorkommt.

| Mutant | Aenderung | verfehlte Faelle |
|---|---|---|
| `ohne_grenze` | `zeile_bei(ende) == heimatzeile` → `>=` | **3 von 51**: Zitatfall 10, 11, 13 |
| `grenze_am_wort` | `heimatzeile = zeile_bei(j)` → `zeile_bei(i - 1)` | **1 von 51**: Zitatfall 12 |

**Kein Fall reisst bei beiden**, und die 47 Faelle der anderen vier Tabellen bleiben in
beiden Laeufen gruen. Damit ist gezeigt, dass die Tabelle nicht als Ganzes reisst,
sondern je Teilregel andere Faelle -- und dass sie Verschiedenes messen.

`ohne_grenze` nimmt auch Fall 13, den, der den **Preis** der Regel ausschreibt. Er misst
sie also mit und laeuft nicht bloss mit; das ist der Punkt, an dem der vorgefundene
Kommentar irrte.

**Der zweite Mutant griff im ersten Anlauf daneben und lief gruen durch.** Mit
`zeile_bei(i)` statt `zeile_bei(i - 1)` aendert er nichts: `i` zeigt auf das Leerzeichen,
zu dem `haenge_zeile_an` den Umbruch macht, und dieses Leerzeichen traegt bereits die
Nummer der **neuen** Zeile. Erst `i - 1` trifft das letzte Zeichen des Schluesselworts.
Der Fehlgriff steht in `mutiere.py` ausgeschrieben, weil er die Bauart des Absatzes
erklaert.

## Der Messstand

Elf Eintraege, alle gruen, Mitschnitt in `messung-0105/mitschnitt.txt`:

```
riegel_{vorher,nachher}_auf_{baum,baum_gut,baum_tot}   6
rueckgabewerte                                          1
mutant_{ohne_grenze,grenze_am_wort}_selbsttest          2
riegel_{vorher,nachher}_auf_arbeitsbaum                 2
```

`WILL_FAIL` beweist nur "ungleich 0". Der Riegel unterscheidet aber 1 (Befund am
Bestand) von 2 (gerissener Selbsttest), und ein Nachweis, der beide zusammenwirft,
koennte ein kaputtes Messgeraet als gefangenen Fehler ausweisen. `rueckgabewerte.sh`
druckt die Werte deshalb ab und vergleicht sie gegen eine Erwartung:

```
baum:     vorher 0, nachher 0
baum_gut: vorher 1, nachher 0
baum_tot: vorher 1, nachher 1
```

Dass dieser Eintrag misst, hat er selbst gezeigt: Beim ersten Lauf stand `0 0 0` als
Erwartung fuer die Fassung nachher, und er wurde rot mit
`nachher: erwartet [0 0 0], gemessen [0 0 1]`.

## Beide Bauwege

* `cmake -S ventures/0016-... -B .../bau` → `ctest`: **16 von 16 gruen**, gemessen nach
  der fremden Drift von `0333b81` auf `4bbd069`.
* `cmake -S werkzeuge/belegstellen -B .../bau/einzeln-0105` → `ctest`: **1 von 1 gruen**.
  Der Baulauf ruft jede `CMakeLists.txt` auch allein.
* **Beim letzten Durchgang war der Arbeitsbaum als Ganzes rot, und zwar aus fremdem
  Grund:** `kern/test/verlauf_probe.cpp` uebersetzt zur Stunde nicht (`expected '}' at
  end of input`, dazu zwei `-Werror=unused-function`). Ein fremder Lauf steht mitten in
  Paket `0140-verlauf-sammelt-die-rundenketten`. Nicht angefasst. Mein Ziel und der
  Einzelweg sind danach erneut gemessen und beide gruen; der Messstand ebenso, 11 von 11.

Kein neues Uebersetzungsziel, kein neuer `ctest`-Eintrag im Erzeugnis: Geaendert ist im
Vorhaben genau eine Datei, `werkzeuge/belegstellen/belegstellen_riegel.cpp`, und daran
nur Kommentar. Der Messstand liegt vollstaendig unter `befunde/` und wird von
`baulauf.py` nicht gesehen (`AUSGENOMMEN`, `baulauf.py:132`) -- gemessen daran, dass der
Uebersetzungsbericht weiter `manifeste: 7` meldet.

## Worauf ich unsicher bin

* **Fall 12 haengt an einem Mutanten, den es im Repo nicht gibt.** Er reisst nur, wenn
  jemand die Grenze auf `i - 1` verschiebt. Das ist eine echte Deckung, aber eine
  schmalere als bei den anderen dreien -- die reissen schon, wenn die Regel ganz
  entfaellt.
* **Die Regel selbst ist am Bestand nur durch die gebauten Baeume gedeckt.** Der Korpus
  fuehrt heute keine einzige Belegstelle dieser Form; faellt die Regel weg, bleibt der
  Arbeitsbaum gruen. Das Paket `0106` setzt laut Projektmanager genau dort einen Anker.
* **Ob der Kopfabschnitt an der richtigen Stelle steht.** Die Abnahme sagt "unter den
  ausgeschriebenen Grenzen". Ich habe beides getan: die vierte Grenze in die Liste
  gesetzt **und** einen eigenen Abschnitt daruntergelegt, weil der Preis der Regel in
  eine Aufzaehlung nicht passt.

## Befunde ausserhalb dieses Pakets

1. **Der Messstand unter `befunde/` blaeht die Menge der ungelesenen Pfade auf.** Der
   Riegel sammelt aus `bau/` und `befunde/` die **Dateinamen** ein (Paket 0083), auch
   wenn er den Inhalt nicht liest. Gemessen am selben Tag: auf dem eingefrorenen Baum
   452 Pfade, auf dem Arbeitsbaum **21.207** -- der Unterschied ist fast vollstaendig
   die committete Kopie des Vorhabens unter `messung-0105/baum*/`. Die Laufzeit des
   Riegels steigt dadurch von 0,23 s auf 0,84 s. Heute aendert das keine Einstufung
   (37/37/47 auf beiden Seiten), aber es ist eine wachsende Menge, gegen die Zitate
   nachgeschlagen werden. Vorschlag `0142` daneben.
2. **Ein fremder Lauf hat meine Datei mitcommittet**, zum vierten Mal an diesem Tag:
   `4bbd069` (`kernbauer: 0108-...`) traegt meine letzte Kopfzeilenaenderung. Inhaltlich
   nichts verloren; die Arbeit steht unter fremdem Betreff. Gegenstand von `0131`.
3. **`mutant/belegstellen_riegel.cpp` ist eine ueberholte Zwischenfassung aus diesem
   Lauf.** Sie entstand, bevor der zweite Mutant dazukam, und liegt jetzt neben den
   Unterordnern `mutant/ohne_grenze/` und `mutant/grenze_am_wort/`. Sie zu loeschen ist
   mir verwehrt (Hausregel 3, und der Aufruf wurde abgelehnt); sie wird von nichts
   uebersetzt. Wer den Ordner liest, soll wissen, dass die zwei Unterordner die
   gemessenen sind.
