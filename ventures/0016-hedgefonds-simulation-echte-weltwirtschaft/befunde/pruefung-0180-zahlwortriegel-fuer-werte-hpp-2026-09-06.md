---
typ: pruefung
paket: 0180-zahlwortriegel-fuer-werte-hpp
pruefer: test-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen am eigenen Bau in beiden Profilen gemessen, Rotnachweise mit eigenen Mutationen an werte.hpp und am Riegel selbst gefuehrt
befunde: 1
---

# Pruefung 0180 -- der Zahlwortriegel fuer `werte.hpp`

## Messaufbau

Arbeitskopie aus `git archive HEAD` (Vorhaben und specs im Betriebslayout) unter
`bau/tp0180/`, gebaut wie `baulauf.py`: `RelWithDebInfo`, `-fwrapv -fno-fast-math`,
einmal `FABRIK_SANITIZER=ON` (Vorgabewert), einmal `OFF`. Kopie vor der Messung
byteweise gegen den Arbeitsbaum gehalten: identisch. Alle Mutationen an der Kopie,
jede mit Trefferbremse (`count == 1`) und Ruecknahmelauf auf Code 0; die Baeume sind
nach der Messung entfernt, die Kopie war zuvor nachweislich wieder zeichengleich.

## Bedingung 1 -- haengt im Arbeitsbereichsbau, Code 0 in beiden Profilen: erfuellt

`ctest -N` listet in beiden Profilen 19 Tests, `zahlwort_riegel` als Nr. 19.
Voller `ctest`-Lauf: `100% tests passed, 0 tests failed out of 19`, in ON und OFF.
Alleinbau (`cmake -S werkzeuge/zahlwort`, Bauweg 2 der CMakeLists): 1/1, Code 0 --
der `PROJECT_IS_TOP_LEVEL`-Block zieht Werkzeugkette und `enable_testing()` wirklich.
Der Uebersetzungsbericht des Runners vom 2026-09-06 zeigt dieselben Zahlen (19/19
Arbeitsbereich, 1/1 allein, `ergebnis: ok`) -- erst nach der eigenen Messung gegengelesen.

## Bedingung 2 -- wird rot bei Abweichung: erfuellt, an beiden Sorten und am Altstand

Eigene Mutationen, nicht die des Bauers:

| Mutante | Ergebnis |
|---|---|
| Zeile 73 `zwei` -> `drei` (Sorte 2, Zahlwort verstellt) | Code 1, `Zeilennummer 73: 'drei Jahrgangskonstante[n]' nennt 3, gezaehlt sind 2` |
| Zeile 157 `zweiundzwanzig` -> `einundzwanzig` (Sorte 1) | Code 1, `nennt 21, gezaehlt sind 22`, Zeile genannt |
| Deklaration `**T48 Nr. 23**` ergaenzt, Kopf nicht nachgezogen | Code 1, **vier** Befunde: Zeilen 2, 16, 32, 157, je `nennt 22, gezaehlt sind 23` |
| drittes Feld mit Berufung auf T23 Punkt 5 ergaenzt | Code 1, Zeile 73 `nennt 2, gezaehlt sind 3`; die Ordnungszahl Zeile 139 (`zweite`, 2 <= 3) bleibt korrekt stumm |
| Stand vor 0155 (`git show b2829c8:...werte.hpp`) | Code 1, `Zeilennummer 73: 'eine Jahrgangskonstante[n]' nennt 1, gezaehlt sind 2` -- exakt der historische Fehler |

Jede Meldung nennt gefundene Zahl, gezaehlte Zahl und Zeile. Jede Ruecknahme: Code 0.

## Bedingung 3 -- nicht rot ohne Zahlbehauptung: erfuellt

Der Bestandslauf listet 9 Fundstellen; Zeile 15 (Kategorienzeile), Zeile 6 (`die
abgeleiteten Groessen abschliessend`) und Zeile 474 (`vier Zeilen und keine Groessen`)
stehen als `keine Zahlbehauptung`, keine davon rot. Meine unabhaengige Zaehlung am
Quelltext deckt sich mit der des Riegels: 22 Nummern in 23 Deklarationen (Nr. 11
doppelt), 8 Felder, davon 2 Jahrgangskonstanten (`leitzins_start`, `durchgriff`) und
6 Parameterschluessel.

## Das Messgeraet selbst -- wird der Riegel rot, wenn man IHN kaputtmacht: ja

Drei eigene Mutationen am Riegelcode, je mit Neubau:

- Urteilsschritt auf immer-Gruen genagelt (`|| true`): Code 2, Tabellen 3 und 5 reissen.
- Artikelregel neutralisiert (`false &&` vor `ist_mehrdeutig`): Code 2, Tabelle 2
  Faelle 3 und 17 reissen -- genau die Faelle der Kategorienzeile.
- Befund-Anhaengen in `pruefe()` neutralisiert: Code 2, Verdrahtungsfaelle 2, 3, 5
  reissen. Die fuenfte Tabelle deckt also wirklich die Stelle, die sich in zwei
  verwandten Riegeln auf immer-gruen festnageln liess.

Die Schranken in `main`, die der Selbsttest nicht deckt, einzeln dynamisch geprobt:
Nomen `Groessen` ueberall ersetzt -> Code 2 (gegenstandslos, nicht bestanden); eine
einzelne T48-Nummer verstuemmelt -> Code 1 mit 4 Zahlbefunden plus Mangel `nennt keine
Nummer der Tabelle`; Ordnungszahl ueber die Zaehlung gehoben (Zeile 139 `zweite` ->
`dritte`) -> Code 1; nicht existierende Wurzel -> Code 2. Die `<=`-Regel der
Ordnungszahl ist damit von beiden Seiten eingeklemmt (2<=2 gruen, 2<=3 stumm, 3>2 rot).

Dateiliste des Baucommits `cf9e15a` gegen `dateien` gelegt: die drei Paketdateien,
dazu nur Paketstatus und eigenes Logbuch. Keine fremde Quelldatei, nichts abgeschwaecht
-- das Paket ist eine Neuanlage, es gab keinen Test, den es haette senken koennen.

## Befund 1 (Nebenbefund, kein Hindernis der Abnahme): die zweite Zahl der Zeile 32

`werte.hpp` Zeile 32 sagt `Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen`.
Die erste Zahl prueft der Riegel, die zweite nicht: `Deklarationen` ist kein Nomen
seiner beiden Sorten, obwohl die Zaehlung (`z.deklarationen`) im Code bereits existiert
und in der Ausgabe steht. Kommt eine weitere Stelligkeit unter einer vorhandenen Nummer
dazu (der Nr.-11-Fall, den T48 ausdruecklich kennt), bleibt die Nummernzaehlung 22, der
Riegel gruen -- und `dreiundzwanzig` stuende falsch da, in derselben Zeile, deren erste
Haelfte bewacht ist. Das ist exakt die Driftsorte, gegen die das Paket antritt.
Der Paketauftrag nennt nur die zwei Sorten; deshalb kein `zurueck`, sondern
Vorschlag `0194`.

## Wonach ich sonst gesucht und nichts gefunden habe

Fenstergrenze (genau ein Beiwort), Nur-Plural, Nur-Zahlwoerter, Nur-ganzzeilige
Kommentare: alle vier im Riegelkopf als Grenzen erklaert und je durch einen
Selbsttestfall festgehalten -- Entwurfsentscheidungen, kein Befund. Ein beim
Fehlplatzieren meines Testfelds entdecktes Parserverhalten (ein zwischen fremden
Kommentar und fremde Deklaration geschobenes Feld erbt den fremden Kommentar) fuehrt
zu Rot ueber die Sortenschranke, nicht zu still-gruen -- keine Luecke.
