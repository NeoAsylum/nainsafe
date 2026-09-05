---
typ: pruefung
paket: 0078-reihentoml-preisbasis-nach-t53-nachziehen
pruefer: daten-pruefer
datum: 2026-09-05
urteil: zurueck
kriterium_geprueft: Die neue Fassung von pruefweg.zaehlregel_umrechnung gegen alle 23 mit tomllib aufgezaehlten Bloecke [[reihe.umrechnung]] gelegt, dazu Bedingung 4 und Bedingung 5 gegen den genannten Bezugsstand 3ad2996 neu gemessen.
befunde: 1
---

# Runde 2: Die neue Einzigkeitsbehauptung hat dieselbe Bauform und faellt an derselben Datei

Gegenstand dieses Ruecklaufs war nach dem Vermerk des Projektmanagers genau eine Aussage,
und die Bedingung dazu lautete woertlich: *"Nach dem Eingriff darf kein Block in dieser
Datei die Aussage widerlegen."* Bedingungen 1, 2 und 3 sind aus Runde 1 erbracht und hier
nicht neu geprueft; Bedingung 4 und Bedingung 5 waren neu zu erbringen und sind erbracht.

**Die Aussage wird widerlegt -- von Reihe 2, Schritt 2.** Das ist derselbe Blocktyp, den der
Bauagent zwei Saetze vorher selbst an die erste Stelle seiner eigenen Aufzaehlung setzt.

## Bezugsstand und Umfang -- nachgemessen, nicht uebernommen

| Angabe | Aufruf | Ergebnis |
|---|---|---|
| Bezugsstand `f71017c` | `git ls-tree f71017c <pfad>` | Blob `3ad2996765697f2426ee7bb01e608e7989710356` |
| Endstand Arbeitsbaum | `git hash-object <pfad>` | Blob `cf492e2cd8ff865067173e1c63af0115d5f1cd5a` |
| Endstand `HEAD` | `git ls-tree HEAD <pfad>` | derselbe Blob `cf492e2` |
| Bilanz | `git diff --numstat 3ad2996 cf492e2` | `2 2` |
| Hunks | `git diff -U0 3ad2996 cf492e2`, Zeilen mit Hunkmarke | 2, an den Zeilen 1747 und 1762 |

Beide Angaben des Bauberichts treffen zu. Geaendert sind genau zwei Blattwerte,
`pruefweg.toml_geprueft` (Z. 1747) und `pruefweg.zaehlregel_umrechnung` (Z. 1762), beides
einzeilige Felder; keine Zeilennummer der Datei verschiebt sich. Der Commit `07cc49b`
(`datenbauer: 0078 ...`) enthaelt `reihen.toml` **nicht** -- den Endstand traegt der fremde
Commit `c30acc5` (`testentwickler: 0111 ...`, 12:42:43), wie der Bericht es beschreibt. Der
Vergleich `3ad2996` gegen `cf492e2` ist damit tatsaechlich der einzige saubere.

## Der Befund -- `pruefweg.zaehlregel_umrechnung`, letzter Absatz

Der neue Schlusssatz lautet:

> "Einzig bleibt am zweiten Block der Reihe 14 nur dies, und es ist gegen dieselben 23
> Bloecke geprueft: Er ist der einzige, dessen Teiler je Jahr einen anderen Wert traegt.
> Die Teiler der Reihen 4 und 15 sind der Wert des Startjahrs und stehen ueber alle Jahre
> fest; Reihe 7 teilt durch die Konstante in ihrem eigenen Feld `faktor` und nimmt die je
> Gebiet und Jahr wechselnde Groesse als Multiplikanden, nicht als Teiler; **die uebrigen
> Teiler sind Konstanten**."

**Der Gegenkandidat ist Reihe 2, Schritt 2** (`reihe.1.umrechnung.1`, `art = "normierung"`,
`faktor = 10000`, `rundungsstelle = "offen"`). Er steht unter "die uebrigen", denn benannt
sind nur die Reihen 4, 15 und 7. Sein Teiler ist keine Konstante.

### Wie man den Fehler erzeugt -- Schritt fuer Schritt

1. **Was die Normierung teilt, sagt die Vorgabe.** `specs/.../technik.md`, T23 Punkt 7:
   *"die drei Sektoranteile je Gebiet und Jahr werden auf 10.000 normiert, **weil die
   WDI-Anteile wegen der Guetersteuern abzueglich Subventionen nicht auf 100 Prozent
   summieren**. Die Normierung -- Verfahren und **der je Gebiet und Jahr abgeschnittene
   Rest** -- steht im Manifest."* Auf eine Zielsumme normieren heisst durch die Istsumme
   teilen: normiert je Sektor gleich roh mal 10.000, geteilt durch die Summe der drei
   Rohanteile. Der `faktor = 10000` ist -- genau wie im Block der Reihe 14 -- der
   **Zaehler**; der Teiler ist die Istsumme.
2. **Dass diese Istsumme je Jahr wechselt, sagt `reihen.toml` selbst**, im `offen`-Feld
   derselben Reihe (`reihe.1.offen.1`, Z. 506): *"Die Normierung ist kein Rundungsdetail:
   Die drei WDI-Anteile summieren sich nicht auf 100 (der Rest sind Nettoguetersteuern),
   sie verschiebt jeden der zwoelf Werte."* Der naechste Eintrag (Z. 507) nennt die
   gemessene Groesse dieses Rests fuer ein Modelland. Nettoguetersteuern in Prozent des BIP
   sind eine je Gebiet **und je Jahr** verschiedene Groesse -- waere der Rest ueber die
   Jahre fest, muesste ihn T23 nicht "je Gebiet und Jahr" abschneiden und ins Manifest
   schreiben.
3. **Der Bauagent schreibt es zwei Saetze vorher selbst hin.** Erste Gruppe seiner eigenen
   Aufzaehlung: *"Reihe 2 Schritt 2 (`normierung`) **braucht die drei Sektoranteile des
   Gebiets und Jahres** und fuehrt daneben `rundungsstelle`."* Damit steht die Widerlegung
   im selben Feld wie die Behauptung.
4. **Die Ausrede "ohne eigenes Feld ist es kein Teiler" ist im Text schon verbraucht.**
   Derselbe Satz spricht den Reihen 4 und 15 einen Teiler zu, obwohl die Aufzaehlung eine
   Zeile hoeher ausdruecklich sagt, er *"steht in keinem Feld des Blocks"*. Wer "Teiler"
   arithmetisch fasst -- und nur so ist der Satz ueber 23 Bloecke ueberhaupt pruefbar --,
   muss Reihe 2 mitzaehlen. Faende man "Teiler" dagegen als "Wert des Feldes `teiler`", ist
   die Aussage leer: Reihe 14 ist dann trivial der einzige, weil kein anderer Block das
   Feld fuehrt.

**Warum das nicht Geschmack ist.** `[pruefweg]` ist der Pruefapparat dieser Datei; ein "ist
der einzige" ist dort eine Zaehlaussage. Dieselbe Bauform ist in Runde 1 gefallen, und der
Bauagent benennt die Gefahr in seinem Bericht selbst -- er hat sie gesehen und die Messung
trotzdem nicht auf den Teiler der Normierung ausgedehnt.

### Was ich dem Projektmanager dazu sage -- der Weg des letzten Befunds war die Falle

Der Befund aus Runde 1 hat als Ausweg *"die Einzigkeit auf den jahresweisen Teiler
einschraenken"* genannt, und der Vermerk des Projektmanagers hat diesen Halbsatz
mitgetragen -- mit dem richtigen Zusatz, dass die Bedingung die Vorgabe ist und nicht der
Wortlaut. Genau dieser Ausweg fuehrt an Reihe 2 vorbei. Ein dritter Ruecklauf, der wieder
eine engere Einzigkeit sucht, hat gute Aussichten, wieder zu scheitern.

**Der sichere Ausgang ist der, den die Bedingung ausdruecklich zulaesst: streichen.** Die
Aufzaehlung der drei Gruppen davor ist gemessen richtig (unten belegt) und traegt die Regel
allein; der Schlusssatz *"Wer diesen Absatz aendert, prueft ihn gegen diese sieben
Bloecke"* bleibt davon unberuehrt. Bleibt eine Einzigkeit stehen, muss sie Reihe 2
Schritt 2 ausdruecklich mit abhandeln.

## Was haelt -- mit Nachweis

### Die Aufzaehlung der drei Gruppen ist richtig

Alle 23 Bloecke mit `tomllib` aus dem Blob `cf492e2` aufgezaehlt und nach Schluesselmenge
gruppiert, nicht an den vorgezeigten Stellen geprueft:

- **23 Bloecke** `[[reihe.umrechnung]]` -- die Zahl im Text stimmt.
- **Ohne `faktor` genau zwei:** Reihe 3 (`ungemessen`) und Reihe 10 Schritt 2
  (`verkettung`, Kurs im Schluessel `umrechnungskurs_dem_je_eur_mal_100000`). Gemessen ueber
  die Schluesselmengen aller 23, nicht an den beiden genannten geprueft.
- **Die fuenf der ersten Gruppe** tragen alle die behauptete `art` und das behauptete
  Nachbarfeld: Reihe 2 Schritt 2 (`normierung`, `rundungsstelle`), Reihe 7 Schritt 2
  (`mal_geteilt`, `bezugsgroesse`), Reihe 14 Schritt 2 (`deflationierung`, `teiler`),
  Reihe 4 und Reihe 15 (`basierung`, kein Teilerfeld).
- **16 uebrige**, fuenf plus zwei plus sechzehn ergibt dreiundzwanzig, keiner doppelt,
  keiner ausgelassen.
- Die drei Einzelaussagen ueber die Gegenkandidaten treffen zu: Reihe 7 Schritt 2 teilt
  laut eigener `begruendung` *"geteilt durch 10.000"* und nimmt die `bezugsgroesse` als
  Multiplikanden; Reihen 4 und 15 werden laut eigener `begruendung` *"auf ihr Startjahr"*
  basiert; Reihe 10 Schritt 2 verkettet mit dem festen Kurs 195583.

Der Fehler steckt also nicht in der Aufzaehlung, sondern allein im Satz danach.

### Bedingung 5 -- die Selbstmessungen, unabhaengig nachgerechnet

Werkzeug: Python 3.14.4, `tomllib.loads` auf den Bytes beider Blobs aus
`git cat-file blob`, beide Baeume flach gezogen, Blattschluessel als Pfadtupel; die Muster
mit `re` je Zeile. Kein Skript des Bauagenten benutzt.

- **Parserlauf:** gueltiges TOML 1.0, zweimal eingelesen gleich. 19 `reihe`, 9
  `widerspruch`, sechs Wurzeltabellen. Summe `sollreihen` = **27** = `zaehlung.sollreihen_gesamt`.
- **Blattwerte:** 1227 nach 1227, **keiner neu, keiner weg**, Schluesselmengen gleich. Genau
  **zwei** gemeinsame Schluessel tragen verschiedene Werte: `pruefweg.zaehlregel_umrechnung`
  und `pruefweg.toml_geprueft`. Das deckt sich mit dem Bericht Wert fuer Wert.
- **Die sechzehn Muster einzeln neu gezaehlt, alt gegen neu, alle gleich:** `schnitt_1` 6;
  `schnitt_2` 29 / 54 / 27 (die Randzeilen mit dem Muster des Feldes gezaehlt, nicht mit
  einem eigenen -- mein erster, eigener Zaehlweg gab 4 und war der falsche); `schnitt_3` 114;
  `schnitt_4` 19 / 19 / 19, Sammelmuster 152, dazu 20 und 28; `schnitt_5` 21 / 28;
  `schnitt_7` 20 / 2. Als sechzehntes die Typaufzaehlung: 19 `reihe`, 9 `widerspruch`,
  23 `reihe.umrechnung`, 20 `reihe.lizenzbeleg`, 39 `reihe.deckung`, 2 `reihe.konkordanz`,
  2 `reihe.bruch` = 114 in **beiden** Fassungen, also weiter kein achter Typ.
- **`schnitt_1` ueber die Trefferkontexte:** die sechs Zeilen alt gegen neu zeichengleich --
  nicht nur die Zahl. Der neue Absatz nennt seine Zahlen als Zahlwoerter und hebt das Muster
  deshalb nicht an; das ist gemessen und nicht geglaubt.
- **Der Fixpunkt:** `toml_geprueft` nennt die Bilanz "zwei verschiedene Werte" und ist einer
  der beiden. Meine Messung gegen die Endfassung gibt dieselbe Zwei -- das Feld misst sich
  hier ohne Nachkorrektur richtig.

**Bedingung 5 ist erfuellt.** Sie ist nicht der Grund dieses Ruecklaufs.

### Bedingung 4 -- Reihe 20 kommt weiter nicht vor

Das von Bedingung 4 gezaehlte Wort steht in **beiden** Fassungen **null mal**, gezaehlt ueber
den vollstaendigen Blobtext; das Suchwort ist im Skript zusammengesetzt, damit dieser Befund
es nicht selbst in die Datei traegt. Die Liste `reihe` fuehrt vor und nach dem Ruecklauf
**19** Eintraege, `reihe.umrechnung` in beiden Fassungen **23** -- kein neuer Block.

## Wonach ich gesucht und was ich nicht gefunden habe

- **Einheiten und Preisbasis:** Der Ruecklauf aendert keinen Umrechnungsblock, kein
  `basisjahr` und keinen `faktor` -- die Blattwertbilanz zeigt zwei geaenderte Felder, beide
  unter `[pruefweg]`. Ein stiller Einheitenfehler ist hier konstruktiv ausgeschlossen; die
  Preisbasis der Reihe 14 ist unberuehrt.
- **Neue Quelle ohne Lizenzzitat:** keine. Der Ruecklauf bringt keine Quelle ins Produkt;
  `quelle_deflator` und die Lizenzbloecke sind unter den 1227 Schluesseln unveraendert. Der
  offene Punkt aus Runde 1 -- `[namensnennung]` fuehrt Reihe 14 nicht -- liegt bei Paket
  `0100` und ist hier weiter kein Rueckgabegrund.
- **Stille Interpolation oder verdeckte Luecke:** nichts hinzugekommen, `deckung_*`
  unveraendert.
- **Reproduzierbarkeit:** zweimaliges Einlesen ergibt dieselbe Struktur; `datei.stand` steht
  auf 2026-09-05 und ist zu Recht nicht bewegt worden.
- **Ob der Ruecklauf ausserhalb seines Auftrags geschrieben hat:** nein -- der Diff ist auf
  zwei `[pruefweg]`-Felder begrenzt, kein Kommentar geaendert, Leseregel 3 im Kopf
  unangetastet. Die Behauptung des Bauberichts trifft zu.
- **Der erste Satz des Feldes** -- *"Genau einer traegt `art = ungemessen` und keinen Faktor:
  Reihe 3"* -- steht jetzt neben dem neuen *"Zwei Bloecke fuehren gar keinen `faktor`"*. Ich
  habe geprueft, ob das ein zweiter Widerspruch ist: Es ist keiner. Genau ein Block traegt
  `art = "ungemessen"`, und er fuehrt keinen `faktor`; die Konjunktion trifft zu. Der Satz
  ist ausserdem aelter als dieses Paket und war nicht sein Gegenstand. **Kein Befund.**
- **Kein Vorschlag aus diesem Lauf.** Vor dem Schreiben `aufgaben/` neu gelesen: `0099`
  (Vorlagenliste um T53) und `0100` (`[namensnennung]`, Reihe 14) decken die beiden
  gemeldeten Nebenpunkte bereits ab. Der Befund oben gehoert in diesen Ruecklauf und nicht
  in ein eigenes Paket -- er ist ein Satz in einem Feld, das ohnehin gerade offen liegt.
