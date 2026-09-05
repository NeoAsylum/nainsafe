---
typ: messung
paket: 0129-bezeichner-im-kommentar-loest-auf
rolle: testentwickler
datum: 2026-09-05
---

# Nachweis zu Paket 0129 -- der Bezeichnerriegel

Alle Zahlen stammen aus ausgefuehrten Laeufen. Die Werkzeuge des Nachweises sind
Wegwerfstuecke und keine Auslieferung; gelaufen sind sie unter `bau/kp0129/`, und weil
`bau/` von der Versionsverwaltung ausgenommen ist, liegt neben dieser Datei eine Kopie
jedes einzelnen:

* `altbaum.py` -- Kopie des Vorhabens mit dem Wortlaut vor Paket 0101;
* `vorstand.py` -- Kopie ohne das neue Mitglied, fuer die Zaehlung in Bedingung 4;
* `mutant.py` samt `mutanten.sh` -- die fuenf Mutanten der ausgelieferten Quelle;
* `nachweis-CMakeLists.txt` -- der Baum, der die sechs Programme baut und die sieben
  Laeufe faehrt (im Arbeitsordner hiess die Datei `nachweis/CMakeLists.txt`);
* `entwurf.py` -- die Entwurfsfassung in `python3`, an der der Regelsatz vor dem
  Schreiben des C++ gemessen wurde;
* `uebernehmen.py` -- der Schritt, der diese Kopien angelegt hat.

Zum Nachfahren: `mutanten.sh <wurzel> <arbeitsordner>`, dann
`nachweis-CMakeLists.txt` als `CMakeLists.txt` in einen Ordner unterhalb des
Arbeitsordners legen und `cmake`/`--build`/`ctest` darauf rufen.

## Bedingung 1 -- der Riegel laeuft, ist ein `ctest`-Eintrag und nennt drei Zahlen

Alleinbau des neuen Verzeichnisses, also der Weg, den `baulauf.py` je Bauskript geht:

```
cmake -S werkzeuge/bezeichner -B bau/kp0129/allein          -> Code 0, 1 uebersetzendes Ziel
cmake --build bau/kp0129/allein                             -> Code 0
ctest --test-dir bau/kp0129/allein --no-tests=error         -> Code 0, 1 Test bestanden
```

Der Bericht des letzten Laufs, Kopfteil im Wortlaut:

```
bezeichner_riegel, Selbsttest: 9 Faelle zur Zerlegung, 6 zur negativen
Zusicherung, 10 zur Form eines Kandidaten und 18 zu den Regeln, alle wie erwartet.
bezeichner_riegel: 29 Kernquellen mit 15183 Zeilen gelesen, davon 5682 Kommentarzeilen
in 1246 Bloecken; 898 Bezeichner in Rueckwaerts-Anfuehrung geprueft, 854 davon
aufgeloest, 44 Fundstellen uebergangen. 1994 Namen im Kern deklariert, 4 negative
Sichtbarkeitszusicherungen abgezogen. Nebenbestaende: 46 Schluessel der Kalibrierdatei,
114 Bauziele aus 7 Bauskripten, 417 Datei- und Ordnernamen, 22 vergiftete Namen,
60 eigene Behaelter.
```

Die drei von der Abnahme verlangten Zahlen stehen darin: **5.682 gelesene
Kommentarzeilen, 898 gepruefte Bezeichner, 44 uebergangene Fundstellen** -- jede
einzelne mit Namen, Regel, Datei und Zeile ausgedruckt, dazu die Summe je Regel:

```
abgelegter_name 4; bauziel 9; commitkennung 1; dateiname 6; fremder_behaelter 4;
fremdwort 2; kennung 6; namensteil 1; namensvorsilbe 1; parameterschluessel 5;
quellenangabe 3; reserviert 1; schluesselwort 1;
```

Schlusszeile: `Kein Bezeichner in einem Kommentar des Kerns zeigt ins Leere.`

## Bedingung 2 -- die negative Zusicherung zaehlt nicht als Deklaration

Der Altbaum ist eine Kopie des heutigen Vorhabens, in der genau ein Kommentarblock im
Kopf des Zustands auf den Wortlaut vor Paket 0101 zurueckgestellt ist: Er nennt wieder
`lies`, `schreibe` und `index_zu_adresse` als die heutigen Namen. `altbaum.py` bricht
ab, wenn der heutige Wortlaut nicht genau einmal vorkommt -- ein Nachweis, der die
Stelle verfehlt, misst nichts.

Beide Laeufe fahren **denselben** Baum; sie unterscheiden sich nur im Programm. Der
Mutant `bedingung2` ist die ausgelieferte Quelle mit einer geaenderten Zeile: Der
Mitgliedsname einer Anforderung `requires { &X::name; }` wird nicht mehr aus der
Deklarationsmenge genommen.

| Lauf | Programm | Wurzel | Code | Meldung |
|---|---|---|---|---|
| `ohne_bedingung2_altbaum` | Mutant `bedingung2` | Altbaum | **0** | kein Befund, 44 uebergangen |
| `echt_altbaum` | ausgeliefert | Altbaum | **1** | 1 Befund |

Der Befund im Wortlaut:

```
1 Bezeichner in Kommentaren des Kerns loesen nicht auf:

  kern/include/kern/zustand.hpp (Zeile 677)
      genannt: schreibe
      gesucht: schreibe
```

Damit ist beides gezeigt, was die Abnahme verlangt: **ohne** die Regel bleibt der
Riegel an der Wiederherstellung des alten Wortlauts gruen, **mit** ihr wird er rot und
nennt `schreibe` samt Datei. Zur Gegenprobe steht daneben `echt_heute` -- dieselbe
ausgelieferte Fassung auf dem heutigen Baum, Code 0.

Der Grund, warum die Regel ueberhaupt greift, steht im Bericht als Zahl: **vier**
negative Sichtbarkeitszusicherungen im Kern, alle in der Probe des Zustands
(`feld`, `lege_ab`, `lies`, `schreibe`). Drei davon sind anderswo im Code deklariert
und bleiben aufgeloest; nur `schreibe` ist es nicht. Genau das ist der Fall, an dem
eine Pruefung ueber blosse Mengenzugehoerigkeit vorbeigeht.

## Der Rotnachweis je Falltabelle

„Ein Test, der nie fehlschlaegt, prueft nichts." Vier weitere Mutanten, je einer gegen
eine Falltabelle des Selbsttests. Jeder faellt an **genau einem** Fall -- 1 von 43 --,
und zwar an dem gemeinten:

| Mutant | was er abschaltet | verfehlter Fall | Meldung |
|---|---|---|---|
| `zerlegung` | Zeichenketten wandern nicht mehr ungelesen in den Codeteil | Zerlegung 4 | `Code 'const char* s = "http:' erwartet 'const char* s = "http://x/y";'` |
| `form` | das leere Klammerpaar bleibt am Namen | Form 3 | `'lege_ab()': Bezeichner 0 erwartet 1` |
| `zusicherung` | die Anforderung braucht keinen Namensraumdoppelpunkt | Zusicherung 6 | `requires { &schreibe; }: gelesen 'schreibe' erwartet ''` |
| `regeln` | Regel 11 sucht die Wendung satzweit statt unmittelbar links | Regeln 1 | `Kandidat schreibe: Regel 'abgelegter_name', erwartet ''` |

Der letzte ist der wichtigste, und er hat den Zuschnitt der Regel korrigiert. In der
ersten Fassung trug Fall 1 der Regeltabelle nur den halben Satz als Text links vom
Kandidaten -- und der Mutant blieb gruen, weil in diesem halben Satz keine Verneinung
steht. Der Fall traegt jetzt den Text, den das Programm an dieser Stelle wirklich
bildet: den ganzen Kommentarblock bis zur Anfuehrung. Darin stehen zwei Verneinungen
(`**kein** Feld des Zustands` und `nicht ausgewerteten`), und damit ist gezeigt, was
der Kopf behauptet: Eine satzweite Fassung von Regel 11 haette den Kommentar aus
Paket 0101 durchgelassen, die unmittelbare tut es nicht.

Zweiter Nebenbefund derselben Art, beim Bauen gefunden: Der Fall zu `vergiftet` hiess
zuerst `double`. Er ging an der Regel `schluesselwort` heraus, die vorher steht, und
wies damit nichts nach. Er heisst jetzt `sqrt` -- vergiftet, aber kein
Schluesselwort. Ein Fall, der zwei Regeln zugleich trifft, weist keine von beiden nach.

## Bedingung 3 -- die Ausnahmen sind Regeln

Jede der 44 uebergangenen Fundstellen faellt unter eine benannte Regel und wird mit
ihrem Namen ausgedruckt. Eine Liste einzelner geduldeter Namen gibt es nicht; die
Bestaende, gegen die die Regeln pruefen, werden **gelesen** und nicht abgeschrieben:

* die vergifteten Namen aus den Vergiftungszeilen des Kerns (22),
* die Schluessel aus der Kalibrierdatei (46),
* die Ziele und Mitglieder aus den Bauskripten des Vorhabens (114 aus 7),
* die Datei- und Ordnernamen des Vorhabens (417),
* die Namensraeume und Verbunde des Kerns (60).

Die drei aus dem Vorschlag genannten Sorten sind darin aufgegangen: die
Vorgabenkennungen (`M15` bis `N11`, sechs Fundstellen) unter `kennung`, die
Namensvorsilbe `MAL_` unter `namensvorsilbe`, die Instrumentenschluessel unter
`parameterschluessel`, `kern_geprueft` unter `bauziel`, `__builtin_mul_overflow` unter
`reserviert`, `consteval` unter `schluesselwort`. Die neun Woerter, die die Koepfe des
Kerns als fremd oder verboten fuehren, verteilen sich auf `vergiftet` (die aus der
Gleitkommasperre), `fremder_behaelter` (`std::map`, `std::set`, `std::to_string`,
`std::bit_width`), `abgelegter_name` (`unsafe`, `abort` an zwei Stellen) und
`fremdwort` (`abort` an der dritten Stelle, `Verlauf`).

**Zwei Einengungen gegenueber dem, was naheliegend gewesen waere**, beide gemessen:

1. `bau` und `befunde` werden gar nicht erst betreten. Unter `befunde` liegen die
   weggeworfenen Messbaeume frueherer Pakete; ihre Bauskripte haetten die Zahl der
   Bauziele von 114 auf 127 und die der Namen von 417 auf 879 gehoben. Ein toter
   Bezeichner mit dem Namen eines Wegwerfziels waere damit entschuldigt gewesen. Die
   Zahl der uebergangenen Fundstellen aendert die Einengung nicht -- sie bleibt 44 --,
   also kostet sie nichts und nimmt einen Ausweg.
2. Der letzte Namensteil eines qualifizierten Namens wird geprueft, nicht der
   Vorspann; und die Regel `fremder_behaelter` greift nur, wenn der Vorspann **kein**
   Namensraum und kein Verbund des Kerns ist. Der Fall `zustand::gibtsnicht` in der
   Regeltabelle haelt fest, dass ein qualifizierter Name mit eigenem Vorspann sehr wohl
   ein Befund wird.

## Bedingung 4 -- beide Bauprofile gruen, ein `ctest`-Eintrag mehr

Gezaehlt wird gegen den **unmittelbar vorhergehenden Stand desselben Baums**: eine
Kopie des heutigen Vorhabens, aus der allein `werkzeuge/bezeichner` entfernt ist. Das
ist die genaue Vergleichsgroesse und nicht die Zahl aus dem Uebersetzungsbericht des
Tages -- der stand bei 14, weil Paket 0133 seither `schlussriegel_nachbau`
dazugelegt hat. Wer gegen die 14 gezaehlt haette, haette zwei gemessen und eines
gebaut.

| Baum | Profil | `ctest`-Eintraege | Lauf |
|---|---|---|---|
| Vorstand (ohne das neue Mitglied) | Sanitizer an | **15** | nur gezaehlt |
| heute | Sanitizer an | **16** | 16 von 16 bestanden |
| heute | Sanitizer aus | **16** | 16 von 16 bestanden |

Die beiden Listen unterscheiden sich in genau einem Eintrag, und zwar dem neuen:

```
Vorstand: festkomma_probe meldung_probe pruefsumme_probe schranken_probe
          schreiber_probe schritt_probe werte_probe zufall_probe zustand_probe
          zustandsausgabe_probe vorrat_kernanker_probe vorrat_probe
          vorrat_verfahren_probe schlussriegel_nachbau belegstellen_riegel
heute:    dieselben fuenfzehn, dazu bezeichner_riegel
```

`belegstellen_riegel` bleibt in beiden Profilen gruen -- die neue Quelle traegt keine
Zeilenangabe in eine fremde Datei und kein totes Abschnittszitat.

## Was der Pruefer wissen sollte

* **Kein fremder Befund.** Der Riegel liefert auf dem gelieferten Baum null Funde;
  keines der vier gleichzeitig im Kern arbeitenden Pakete hat waehrend dieses Laufs
  einen toten Bezeichner hinterlassen. Der in der Abnahme vorgesehene Ausgang „ein
  fremdes Paket legt mir einen toten Namen in den Kern" ist also nicht eingetreten.
* **Der ausgeschriebene Nachlass.** Die Regel `fremdwort` laesst einen einteiligen
  Namen durch, von dem im ganzen Codetext des Kerns keine Spur mehr steht. Der Name aus
  Paket 0101 ist nur deshalb sichtbar, weil die negative Zusicherung ihn im Code
  stehen laesst. Wer diesem Riegel „alle toten Namen geprueft" unterstellt, irrt; er
  prueft die, die eine Spur hinterlassen haben. Dasselbe gilt in kleinerem Umfang fuer
  `namensteil` und `abgelegter_name`. Alle drei drucken jede Fundstelle aus.
* **Die Vorsorge gegen den stillen Ausfall.** Der Lauf bricht mit Code 2 ab, wenn keine
  Kernquelle, kein Kandidat oder **keine einzige negative Zusicherung** gefunden wird.
  Die letzte ist die tragende Regel; verschwindet sie aus dem Bestand, ist der Lauf
  nicht gruen, sondern gegenstandslos.
