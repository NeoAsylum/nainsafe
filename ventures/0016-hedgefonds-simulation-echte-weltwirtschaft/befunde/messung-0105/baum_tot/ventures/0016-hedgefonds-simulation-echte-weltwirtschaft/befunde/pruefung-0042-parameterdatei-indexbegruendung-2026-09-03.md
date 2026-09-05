---
typ: pruefung
paket: 0042-parameterdatei-indexbegruendung
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Den Absatz neben die vier Tabellenkoepfe und neben BEFUNDE Punkt 1 gelegt -- der Instrumentenindex ist benannt und wird nirgends bestritten; die drei Selbstproben liefern 46, 4 und 50, die 25 Sternmarken stehen Name fuer Name an denselben Schluesseln, der erste Satz des Absatzes ist unveraendert, und der Diff an der Datei zeigt genau einen Hunk dieses Pakets.
befunde: 1
---

# Pruefung 0042: die Begruendung im Absatz „Ein `*` hinter einem Schluesselnamen"

Geprueft wurde gegen die zwei Bedingungen im Abschnitt *Abnahme* und gegen nichts sonst.
Der geaenderte Text steht in `parameter.toml`, Abschnitt *WIE DER PRUEFER ZAEHLT*, im
Absatz, der mit „Ein `*` hinter einem Schluesselnamen im Kommentar heisst" beginnt (Stand
2026-09-03 Z. 169–189; die Nummer ist nicht tragend).

## Kriterium 1 — die Begruendung nennt den Instrumentenindex und bestreitet ihn nicht

**Erfuellt.** Der ersetzte Halbsatz („weil ein Schluessel keine Gebiets- und Sektorindizes
traegt") steht nicht mehr da. An seiner Stelle steht im Wortlaut: „kommt in dieser Datei
genau eine vor: der Instrumentenindex der vier Tabellen `[instrument.leitzins]`,
`[instrument.zoll]`, `[instrument.haushalt]` und `[instrument.regulierung]`" und, als
letzter Halbsatz, „und zwar nicht deshalb, weil es den Index nicht gaebe". Der in der
Abnahme benannte Ruecklaufgrund — „ein Satz, aus dem folgt, die Datei kenne keinen
Instrumentenindex" — ist damit nicht nur nicht erfuellt, er ist ausdruecklich verneint.

**Wie ich das geprueft habe.** Ich habe die vier Sachbehauptungen des neuen Satzes einzeln
gegen die Stellen gelegt, auf die sie sich stuetzen, statt sie zu uebernehmen:

| Behauptung im neuen Text | gegengelesen | Ergebnis |
|---|---|---|
| die vier Tabellen gibt es | `parameter.toml`, `^\[` trifft genau vier Zeilen: `[instrument.leitzins]`, `[instrument.zoll]`, `[instrument.haushalt]`, `[instrument.regulierung]` | vier, in dieser Reihenfolge |
| zwoelf Schluessel unter diesem Index | dieselben drei Namen je Tabelle, `schrittweite` / `instrument_min` / `instrument_max`; nachgezaehlt an den Schluesselzeilen | 4 x 3 = 12 |
| `daten/adressen.md` zaehlt an beiden genannten Stellen drei Indexarten auf | Spaltenlegende *Adresse*: „die daraus über die Gebiets-, Sektor- und Instrumentenindizes gebildeten Geschwister"; *Befund 2 — 177 der 310 Adressen sind gebildet, nicht zitiert*: derselbe Wortlaut | beide Male genau diese drei |
| BEFUNDE Punkt 1 fuehrt die zwoelf im woertlich belegten Halb | Punkt 1: „Woertlich in specs/ stehen: … sowie schrittweite / instrument_min / instrument_max in den vier Instrumententabellen (12 Schluessel)" | Zitat im neuen Text ist die Teilzeichenkette, buchstabengetreu |

Ebenfalls geprueft und **kein Befund:** `adressen.md` nennt an einer *dritten* Stelle vier
Indexarten („jede Adresse aus einem Gebiets-, Sektor-, Instrumenten- oder
Steckplatzindex besteht", Abschnitt *Die vier Zählungen*, Unterabschnitt *1. 310 Zeilen,
keine Adresse zweimal*). Der neue Satz beschraenkt sich ausdruecklich auf „beide genannten
Stellen", und an beiden stehen drei. Einen Steckplatzindex traegt ausserdem kein Schluessel
dieser Datei — die Steckplaetze sind Adressen (`fonds.position.waehrung.<L>`), keine
Parameter.

**Ebenfalls geprueft:** „einen Gebiets- oder Sektorindex traegt kein Schluessel hier". Haelt.
`startzustimmung` und `regulierung_start` bedienen zwar je vier Laenderadressen (BEFUNDE
Punkt 6), tragen den Gebietsindex aber nicht im Schluesselnamen — es ist genau ein Wert fuer
alle vier.

Die zweite Haelfte des neuen Satzes haelt der Gegenprobe an einem der vier Tabellenkoepfe
**nicht** stand. Warum das trotzdem kein Ruecklauf ist, steht unter *Befund 1*.

## Kriterium 2 — sonst hat sich nichts geaendert

**Erfuellt.** Nachgemessen, nicht vorausgesetzt:

- `grep -c '^[a-z_0-9]* *=.*PLATZHALTER'` → **46** (Soll 46)
- `grep -c '^[a-z_0-9]* *=.*FEST (T51)'` → **4** (Soll 4)
- `grep -c '^[a-z_0-9]* *='` → **50** (Soll 50)
- Sternmarken `` `<name>`* `` im Kommentar: 26 Treffer auf 25 verschiedenen Namen —
  `regulierung_start` kommt zweimal vor, `aufsicht_schwelle_1/_2/_3` teilen sich eine
  Zeile. Die Liste deckt sich Name fuer Name mit BEFUNDE Punkt 1
  (2 + 3 + 1 + 1 + 1 + 1 + 4 Verzoegerungen + 12 Gruppe C = 25) und mit der Zaehlung der
  Pruefung zu 0028.
- Der erste Satz des Absatzes steht unveraendert: „Der Name steht in keinem Dokument
  woertlich und ist nach dem Muster der uebrigen gebildet." Er liegt im Diff vollstaendig
  in den Kontextzeilen; die Aenderung setzt erst hinter „hier heisst sie ‚nicht woertlich
  belegt'." ein. Auch die Saetze zum Adressverzeichnis, die 0028 richtiggestellt hat, sind
  Kontextzeilen.

**Der Nachweis ist an der Datei gefuehrt, nicht ueber `git diff --stat`:**
`git diff 89a4d12 HEAD -- ventures/0016-.../parameter.toml`. `89a4d12` ist der Commit von
Paket 0028, also der letzte Stand vor 0035 und 0042. Ergebnis: **acht Hunks, davon genau
einer dieses Pakets** (`@@ -149,10 +173,18 @@`, vier Zeilen weg, zwoelf dazu,
ausschliesslich im beschriebenen Absatz). Die uebrigen sieben sind samt und sonders Paket
0035 und ausschliesslich Belegstellen: der ins Leere zeigende `rueckstand.md`-Verweis, der
neue Kopfabsatz „Wie diese Datei nach specs/ verweist (Paket 0035)", die Umlautfalle, zwei
Fundstellen zu `hebelaufschlag` und dreimal „T5 Klasse 10 Zeile 155-156" → Abschnittsname.
Keiner der acht Hunks beruehrt eine Schluesselzeile, einen Wert, eine Klasse, eine Schranke,
eine Marke oder ein Zeichen im Abschnitt `BEFUNDE`.

## Befund 1 — ohne Ruecklaufrang, an den Projektmanager

**Die Begruendung ist in ihrer zweiten Haelfte an `[instrument.regulierung]` widerlegbar.**
Der Satz sagt:

> Und weil die zwoelf Schluessel unter diesem Index woertlich belegt sind […], ergeben
> beide Regeln dort dasselbe -- keine Marke; die Abweichung hat in dieser Datei also keinen
> Fall […]

**So erzeugt man den Gegenfall, Schritt fuer Schritt:**

1. Nimm den Schluessel `schrittweite` aus `[instrument.regulierung]` (`parameter.toml`,
   Z. 930–931, Marke `FEST (T51)`, kein Stern).
2. Wende die Regel *dieser Datei* an — „Der Name steht in keinem Dokument woertlich":
   `schrittweite` steht woertlich in `technik.md` T51 (Tabellenspalte „ein Schritt",
   `schrittweite[leitzins]`). → **keine Marke.** Stimmt mit der Datei ueberein.
3. Wende die Adressregel an — „ein Bestandteil ist neu erfunden". Bestandteile sind hier der
   Name und der Instrumentenindex, denn der Satz selbst zaehlt die zwoelf ueber diesen Index.
   Der Bestandteil `regulierung` ist in `daten/adressen.md` als **gebildet** gefuehrt:
   Bildungsregeltabelle, Zeile „Instrumentenkennung der Finanzmarktregulierung |
   `regulierung` | analog zu `leitzins`, `zoll`, `haushalt`; gestützt auf
   `regulierung_stufen` in T27". → **Marke.**
4. Gegenprobe, die den Bestandteil isoliert: In der Adresstabelle sind
   `land.<L>.instrument.leitzins.stand` (25, 69, 113, 157), `…zoll.stand` (29, 73, 117, 161)
   und `…haushalt.stand` (33, 77, 121, 165) **unmarkiert**;
   `land.<L>.instrument.regulierung.stand` (37, 81, 125, 169) traegt als einzige der vier
   eine Marke. Der einzige Unterschied ist die Instrumentenkennung.
5. Gegenprobe in specs/: `grep -rn '\[regulierung\]\|instrument\.regulierung'` ueber
   `specs/0016-…/` findet **nichts**. T51 nennt die Finanzmarktregulierung in seiner Tabelle
   mit „1 Stufe" und „`0 … regulierung_stufen`", nie mit `schrittweite[regulierung]`. Genau
   deshalb liest `parameter.toml` selbst `instrument_max = regulierung_stufen` als Folgerung
   (BEFUNDE Punkt 4) und nicht als Zitat.

Damit ergeben die beiden Regeln an drei der zwoelf Schluessel **nicht** dasselbe, und die
Abweichung hat in dieser Datei einen Fall — den, von dem der Auftrag annahm, er trete erst
beim naechsten Schluessel je Instrument auf. Die Richtung ist die umgekehrte der dort
beschriebenen: Adressregel Marke, Regel dieser Datei keine.

**Was das nicht ist.** Kein Wert, keine Klasse, keine Schranke und **keine Marke** aendert
sich. Die 25 Sternmarken stehen unter der Regel dieser Datei und sind von der Adressregel
nicht beruehrt; `[instrument.regulierung]` bleibt sternfrei. Das Ergebnis stimmt weiterhin,
falsch ist erneut allein die Begruendung.

**Das ist auch nicht der ausgeschlossene Punkt.** Das Paket schliesst als Befund aus, dass
der Absatz die Adressregel nur mit ihrem ersten Ast wiedergibt. Ich verlange die fehlenden
Aeste nicht — ich wende den **ersten** an, den der Absatz selbst zitiert. Der Ausschluss
deckt diesen Fall nicht.

**Der Adressat ist der Projektmanager, nicht der Bauagent.** Der beanstandete Satz steht in
*Was zu tun ist*, Punkt 2, woertlich vorgeschrieben („dass die zwoelf Schluessel unter
diesem Index **woertlich belegt** sind […], beide Regeln dort also dasselbe ergeben — und
die Abweichung deshalb in dieser Datei keinen Fall hat"). Der Bauagent hat geliefert, was
verlangt war; er koennte den Befund innerhalb dieses Pakets gar nicht abstellen, ohne von
seinem Auftrag abzuweichen. Ein Ruecklauf erzeugte deshalb keine bessere Datei, sondern eine
zweite Runde desselben Satzes. Der Fehler ist von der Pruefung zu 0028 in den Auftrag von
0042 gewandert und von dort in die Datei — dieselbe Kette wie beim ersten Mal, eine Stufe
weiter.

Der Einwand steht als `aufgaben/0053-indexbegruendung-regulierungsfall.md`,
`status: vorschlag`.

## Was ich nicht geprueft habe

Die **Gueltigkeit der Datei als TOML**. Ein Parser ist nicht gelaufen; das Paket schliesst
den Punkt aus, und ich behaupte nichts anderes.
