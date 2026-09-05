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
