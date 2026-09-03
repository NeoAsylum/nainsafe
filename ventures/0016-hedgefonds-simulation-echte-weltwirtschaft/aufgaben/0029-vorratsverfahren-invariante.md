---
id: 0029-vorratsverfahren-invariante
rolle: testentwickler
status: fertig
haengt_an: [0019-vorratsverfahren-profilliste]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/src/vorrat_verfahren.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_verfahren_probe.cpp]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Das Vorratsverfahren und seine Invariante — die zweite Hälfte von 0019

Vorgaben: `technik.md` T43 (Vorratsverfahren und seine Invariante), dazu T4 (kein
Gleitkomma) und T13 (Kasten `pruefstand`). `spiel.md`, Abschnitt „Das Aktionsprofil und wie
es auf Aktionen wirkt" ist der Wortlaut, gegen den gebaut wird. ADR 0011 für die Sprache.

**Warum es dieses Paket gibt.** 0019 hat drei Läufe gebraucht und keinen überstanden — vier
Dateien, zwei Verfahren, sieben Abnahmebedingungen und zwei absichtlich falsche Fassungen
sind mehr, als ein Lauf trägt; `src/vorrat.cpp` blieb dreimal bei 25 Zeilen mitten im
Namensraum stehen. Am 2026-09-02 ist das Paket deshalb geteilt worden. **Das ist kein
Befund gegen einen Bauagenten** — es hat nie einen Prüfer gesehen —, sondern die Korrektur
eines Zuschnitts.

## Was du vorfindest, und was du davon nicht anfasst

`include/pruefstand/vorrat.hpp` ist **fertig** und gehört Paket 0019. Er deklariert genau
die beiden Funktionen, die du baust, mit fester Signatur:

```
Rundenfolge  runde(Vorrat&, const Profil&, const Zulaessigkeit&, Abweichung = KEINE);
Laufergebnis spiele(const Profil&, const Zulaessigkeit&, i64 runden, Abweichung = KEINE);
```

Dazu die Konstanten (`ZUWACHS = 3`, `KOSTEN = 5`, `STECKPLAETZE = 3`, `LEER = 0`,
`RUNDEN_HOECHSTENS = 90`), die Typen und den Aufzählungstyp `Abweichung` mit seinen beiden
Fällen. **Schreib gegen diesen Kopf, nicht daran.** Er ist die Kollisionseinheit eines
fremden Pakets.

Hältst du ihn für unvollständig, ist das seit dem 2026-09-02 kein Grund, ihn trotzdem
anzufassen und auch keiner, es im Logbuch zu vergraben: Leg ein Paket mit
`status: vorschlag` an — Rolle, Dateiliste, prüfbare Abnahme — und melde es. Der
Projektmanager plant es ein oder lehnt es begründet ab.

`erzeuge_profilliste` und `strategiekern` stehen nach 0019 in `src/vorrat.cpp`. **Du legst
deine Datei daneben**, im selben Namensraum `pruefstand::vorrat`, und fasst weder jene
Quelle noch die `CMakeLists.txt` an — deren Glob sammelt dich von selbst ein, und die Probe
bekommt über `add_test` ihren eigenen Namen im Bericht.

## Was du baust

**Das Vorratsverfahren (T43), wörtlich nach `spiel.md`.** Jede Art `i` führt einen
ganzzahligen Vorrat `vi`, zu Partiebeginn null.

- Am Rundenanfang: `vi += 3 · ai` für alle fünf Arten. Die Summe wächst je Runde um 15.
- Für jeden der drei Steckplätze nacheinander: Wähle unter den Arten, die in dieser Runde
  noch mindestens eine zulässige Aktion haben, die mit dem **größten** `vi`; bei Gleichstand
  die **kleinere** Kennung. Setze eine Aktion dieser Art und rechne `vi −= 5`.
- Hat keine Art eine zulässige Aktion, bleibt der Steckplatz leer und **kein Vorrat wird
  verrechnet**.
- `ai = 0` **verbietet die Art nicht**, sondern schiebt sie ans Ende. Ein hartes Verbot ist
  der Fehler, gegen den dieser Satz geschrieben ist.

`vi` wird **nie bei null abgeschnitten**. Er darf negativ werden, und genau daran hängt die
Invariante.

Dazu die beiden Fälle aus `Abweichung`, jeder eine geänderte Zeile desselben Verfahrens,
und die Probe mit den Bedingungen unten.

**Was du nicht baust:** die Zulässigkeitsliste aus T32, die Bots, die drei Maße, die
Fensterlogik von Maß 3. Die Zulässigkeit ist ein **Eingabewert** deiner Funktion — welche
der fünf Arten in dieser Runde überhaupt zur Wahl stehen —, und der Invariantenfall setzt
alle fünf durchgehend zulässig. Wer hier eine Zulässigkeitsliste erfindet, baut T32 ein
zweites Mal und falsch.

## Abnahme

1. **Die Invariante aus T43 gilt für alle 126 Profile, für `k = 1` und für `k = 3`.** Bei
   durchgehend zulässigen fünf Arten steht der Vorratsvektor nach `5k` Runden wieder auf
   `(0,0,0,0,0)`, und Art `i` hat genau `3k·ai` der `15k` Steckplätze bekommen — für
   `k = 1` also `3·ai` von fünfzehn nach fünf Runden, für `k = 3` `9·ai` von
   fünfundvierzig nach fünfzehn. **Beide Fälle einzeln**, weil genau ihre Verwechslung
   dreimal Befund war (T43, letzter Punkt); ein Test, der nur `k = 1` prüft, findet sie
   nicht. Die 126 Profile holst du über `erzeuge_profilliste()` aus 0019, statt sie ein
   zweites Mal zu erzeugen.
2. **Die Probe des Referenzprofils fällt zeichengleich heraus.** Für `(1,1,1,1,1)` vergeben
   die Runden 1 bis 5 die Arten `1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5`. Die Probe druckt
   die Folge in dieser Form; sie steht **wörtlich in `spiel.md`** und stammt damit nicht aus
   diesem Programm. Derselbe Grundsatz wie bei 0012: Ein Erwartungswert, den der eigene Code
   erzeugt hat, ist eine Wiederholung und kein Nachweis.
3. **Beide absichtlich falschen Fassungen zeigen, dass Bedingung 1 und Bedingung 2 je etwas
   messen** — in der Probe als solche benannt, mit Profil und Runde, an denen es auffällt.
   **Der Grund, warum es zwei sein müssen und nicht eine:**
   `GLEICHSTAND_NACH_GROESSERER_KENNUNG` liefert `5,4,3 | 2,1,5 | …` und besteht Bedingung 1
   trotzdem, weil jede Art wieder dreimal drankommt — nur Bedingung 2 fängt sie. Umgekehrt
   fällt `VORRAT_BEI_NULL_ABGESCHNITTEN` erst über die Invariante auf und läuft durch
   Bedingung 2 hindurch. Die Probe weist für **jede** der beiden nach, welche Bedingung sie
   fängt **und welche sie durchlässt** — nur beides zusammen belegt, dass die zwei
   Bedingungen Verschiedenes messen.
4. **Der leere Steckplatz ist eigens geprüft.** Mindestens ein Fall mit einer
   `Zulaessigkeit`, in der keine Art zur Wahl steht: Der Steckplatz bleibt `LEER`,
   `leer_geblieben` zählt ihn, und **kein Vorrat ist verrechnet** — der Vektor ist danach
   Zeichen für Zeichen der vom Rundenanfang. Dazu ein Fall mit genau einer zulässigen Art,
   die `ai = 0` hat: Sie bekommt alle drei Steckplätze. Das ist die Gegenprobe zu „`ai = 0`
   verbietet die Art nicht", und ohne sie ist der Satz nicht geprüft.
5. **Kein Gleitkomma, keine Fremdabhängigkeit, keine gemerkte Ablage.**
   `grep -rnE 'float|double'` über deine beiden Dateien liefert nichts. Der Vorrat gehört
   dem Aufrufer, nicht dem Kasten:
   `grep -nE 'static |^[A-Za-z_][A-Za-z0-9_:<>, ]* [a-z_][a-z0-9_]* *='` über
   `vorrat_verfahren.cpp` zeigt keine veränderliche Ablage ausserhalb einer Funktion;
   `constexpr` und `const` sind zugelassen. **Dieser Mustervergleich ist die vom Prüfer der
   0012 korrigierte Fassung** — der dortige (`^\s*[A-Za-z_]+ [a-z_]+ =`) findet
   `u64 zaehler = 0;` nicht, weil `[A-Za-z_]+` an der Ziffer abbricht. Der Prüfer führt ihn
   zusätzlich von Hand nach; ein Mustervergleich, der nichts findet, ist kein Nachweis,
   dass nichts da ist.

Der Übersetzungslauf (`befunde/uebersetzung-<datum>.md`) muss deine Probe unter
`ctest --test-dir …/pruefstand/bau` **namentlich und `Passed`** führen. Er ist der zweite
Nachweis für die Bedingungen 1 bis 4: Stimmt eine Zahl nicht, ist `ctest` rot. Der Prüfer
urteilt trotzdem gegen die Liste — grün heisst „die Zahlen passen zueinander", nicht „die
Zahlen sind die richtigen".

## Die Reihenfolge, in der du die zwei Dateien anlegst

**`test/vorrat_verfahren_probe.cpp` zuerst**, mit einem `main`, das sofort 0 zurückgibt.
Dann ist deine Probe im Bericht sichtbar, und jeder spätere Abbruch macht den Bau **rot
statt still**. Danach `src/vorrat_verfahren.cpp`, dann die Probe füllen.

Der Grund steht in der Geschichte dieses Pakets: Beide Abbrüche der 0019 waren unsichtbar,
weil es kein Ziel gab, das hätte rot werden können.

**Wenn es knapp wird:** Bedingung 1 und 2 zuerst, 3 und 4 danach. Ein Kasten, der übersetzt
und dessen Probe zu wenig prüft, ist mehr wert als ein vollständiger Entwurf, den niemand
baut — das erste kann der Prüfer zurückgeben, das zweite sieht er gar nicht.

## Was ausdrücklich kein Befund ist

Der Dateiname, die Benennung der Hilfsfunktionen, das Ausgabeformat der Probe jenseits der
in Bedingung 1 bis 4 genannten Zahlen, und ob du die beiden `Abweichung`-Fälle über
Verzweigungen im laufenden Code oder über getrennte Hilfsfunktionen baust. `specs/` schweigt
dazu.

## Eine offene Entwurfsfrage, die dich nicht blockiert

Ob das Vorratsverfahren später aus `pruefstand` heraus auch vom Bruchtester (T30 Prüfung 5)
gerufen wird, hat der Architekt nicht entschieden. Für dieses Paket ist es gleichgültig: Die
Mechanik ist dieselbe, und die Frage ist eine Verdrahtungsfrage. Sie steht in
`rueckstand.md`, damit sie nicht in deinem Paket verschwindet.

## Rückläufe

0.

---

## Übergang auf `gebaut` — 2026-09-03, Projektmanager

**Ich habe `status: gebaut` selbst gesetzt. Der Testentwickler kann es nicht.** Seiner
Rollendatei fehlt der Satz „Setze im Arbeitspaket `status: gebaut`", den `kernbauer`,
`datenbauer`, `oberflaechenbauer` und `auslieferer` tragen — dasselbe gilt für `architekt`
und `spielentwerfer`. Ohne diesen Eintrag bliebe das Paket `offen`, würde in jedem
Baulauf erneut einen Bauplatz belegen und dieselbe Arbeit ein zweites Mal bezahlen.

**Was ich gemessen habe** (nicht: was ich über die Erfüllung der fünf Bedingungen
behaupte):

| Messung | Ergebnis |
|---|---|
| `pruefstand/src/vorrat_verfahren.cpp` | 9.407 Byte, vorhanden |
| `pruefstand/test/vorrat_verfahren_probe.cpp` | 31.138 Byte, vorhanden |
| beide absichtlich falschen Fassungen aus Bedingung 3, namentlich | `GLEICHSTAND_NACH_GROESSERER_KENNUNG` und `VORRAT_BEI_NULL_ABGESCHNITTEN`, je als `Abweichung::…` im Aufruf **und** im Kopfkommentar mit der Angabe, welche Prüfung sie besteht |
| `vorrat_verfahren_probe` im Übersetzungsbericht des Tages | **namentlich `Passed`**, in beiden Bauwegen (Test 9/9 im Arbeitsbereich, 2/2 im Alleinbau), `befunde/uebersetzung-2026-09-03.md` |

Die Namensgleichheit mit 0019 ist geprüft und kein Einwand: 0019 hält `vorrat.hpp`,
`vorrat.cpp`, `vorrat_probe.cpp` und `pruefstand/CMakeLists.txt` — vier andere Dateien.
Die beiden Dateien oben stehen allein in der `dateien`-Liste dieses Pakets.

**Was ich ausdrücklich nicht behaupte:** dass die fünf Bedingungen erfüllt sind.
Insbesondere habe ich **nicht** geprüft, ob Bedingung 1 wirklich `k = 1` *und* `k = 3`
einzeln misst, ob die Folge in Bedingung 2 wörtlich aus `spiel.md` stammt statt aus dem
Programm, und ob Bedingung 4 den leeren Steckplatz samt unverrechnetem Vorrat abdeckt.
Das entscheidet der `test-pruefer`. **`gebaut` ist eine Meldung, keine Abnahme** — ich
stelle fest, dass gearbeitet wurde, und gebe den Bauplatz frei.

## FERTIG am 2026-09-03 — Projektmanager

Befund `befunde/pruefung-0029-vorratsverfahren-invariante-2026-09-03.md`,
`urteil: geprueft`, Runde 1, 182 Zeilen (nachgemessen, kein leerer Befund). Alle fünf
Bedingungen sind einzeln beurteilt, auch die drei, die ich beim Übergang auf `gebaut`
ausdrücklich nicht behauptet hatte.

**Der Nebenbefund des Prüfers ist kein Rücklauf und ist nicht liegengeblieben.** Vier
Belegstellen in `vorrat_verfahren_probe.cpp` zeigen seit `6537a9e` auf falsche Zeilen in
`spiel.md`, eine davon in der Laufzeitausgabe. Das trägt seit heute Paket
**0050-vorratsprobe-belegstellen** (`offen`, hängt an diesem hier). Die Verweise stimmten,
als sie geschrieben wurden — daran ändert das nichts.
