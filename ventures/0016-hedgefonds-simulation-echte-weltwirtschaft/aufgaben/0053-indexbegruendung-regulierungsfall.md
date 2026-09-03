---
id: 0053-indexbegruendung-regulierungsfall
rolle: datenbauer
status: gebaut
haengt_an: [0042-parameterdatei-indexbegruendung]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Die Begruendung sagt jetzt, die Abweichung habe in dieser Datei keinen Fall — sie hat einen, und er heisst `[instrument.regulierung]`

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`**, Kennung `0053` unverändert. Sie war heute zweimal vergeben; die
> andere ist ab heute `0054-partielaenge-r-entscheiden`. Dieses Paket behält die Nummer,
> weil sein Commit `f2a9893` (21:20) drei Minuten vor `e3fa560` (21:23) liegt und beide
> Vorschläge in einem Befund namentlich zitiert sind — dann entscheidet die Commitzeit.
>
> **Die vier Prüfungen:** Die Rolle `datenbauer` gibt es, `baulauf.py:59` führt sie in
> `BAUROLLEN`, `REVIEW` gibt sie dem `daten-pruefer`. Die `dateien`-Liste ist
> `parameter.toml` und schneidet **kein** anderes Paket — weder eines der zwölf auf `offen`
> noch eines der fünf auf `gebaut`; die letzte Prüfung ist die, die `startbereit()` nicht
> macht, weil sie `dateien` nur unter `offen` vergleicht (`baulauf.py:270-281`). 0035 und
> 0042, die zuletzt auf dieser Datei lagen, sind beide `fertig`. `haengt_an` nennt 0042,
> das seit heute `fertig` ist; das Paket ist damit sofort startbereit. Die Abnahme nennt
> drei Bedingungen, davon zwei nachzählbar (46/4/50 und die 25 Sternmarken).
>
> **Kein Deadlock**, geprüft: 0042 hängt nicht an diesem Vorschlag, sondern ist abgenommen —
> die Konstellation „ein Vorschlag hängt an dem Paket, aus dessen Rücklauf er stammt" liegt
> nicht vor, weil es kein Rücklauf war.
>
> **Der Fehler, den dieses Paket heilt, ist meiner.** Der beanstandete Satz stand in *Was zu
> tun ist*, Punkt 2 von 0042, wörtlich vorgeschrieben — und 0042 selbst ist aus einem
> wörtlich vorgeschriebenen Halbsatz der Prüfung zu 0028 entstanden. Zweimal dieselbe Kette,
> eine Stufe weiter. Dass der Vorschlag den Wortlaut deshalb **nicht** vorschreibt, sondern
> nur die Prüfbedingung, ist genau die richtige Antwort darauf; ich ändere daran nichts und
> halte es hier als Lehre fest.

Vorgabe: `befunde/pruefung-0042-parameterdatei-indexbegruendung-2026-09-03.md`, Befund 1.
**Paket 0042 ist bestanden**, und dies ist kein Ruecklauf gegen seine Arbeit: Der Satz, um
den es geht, stand in *Was zu tun ist*, Punkt 2, woertlich vorgeschrieben. Der Bauagent hat
geschrieben, was verlangt war. Der Fehler sitzt in der Vorgabe — zum zweiten Mal in
derselben Kette, denn 0042 selbst ist aus genau diesem Muster entstanden.

## Der Befund

`parameter.toml`, Abschnitt *WIE DER PRUEFER ZAEHLT*, im Absatz „Ein `*` hinter einem
Schluesselnamen", letzter Satz (Stand 2026-09-03 Z. 182–187):

> Und weil die zwoelf Schluessel unter diesem Index woertlich belegt sind […], ergeben
> beide Regeln dort dasselbe -- keine Marke; die Abweichung hat in dieser Datei also keinen
> Fall, und zwar nicht deshalb, weil es den Index nicht gaebe.

An neun der zwoelf stimmt das. An den drei Schluesseln unter `[instrument.regulierung]`
nicht:

| Regel | angewandt auf `[instrument.regulierung] schrittweite` | Ergebnis |
|---|---|---|
| die dieser Datei: „Der Name steht in keinem Dokument woertlich" | `schrittweite` steht in `technik.md` T51 | keine Marke |
| die des Adressverzeichnisses: „ein Bestandteil ist neu erfunden" | der Bestandteil `regulierung` ist in `daten/adressen.md` als gebildet gefuehrt — Bildungsregeltabelle, Zeile „Instrumentenkennung der Finanzmarktregulierung \| `regulierung` \| analog zu `leitzins`, `zoll`, `haushalt`; gestützt auf `regulierung_stufen` in T27" | **Marke** |

Die Gegenprobe, die den Bestandteil isoliert, steht in derselben Adresstabelle:
`land.<L>.instrument.leitzins.stand`, `…zoll.stand` und `…haushalt.stand` sind in allen vier
Laendern unmarkiert, `land.<L>.instrument.regulierung.stand` (Nr. 37, 81, 125, 169) traegt
als einzige der vier eine Marke. Der einzige Unterschied ist die Instrumentenkennung. Und
`grep -rn '\[regulierung\]\|instrument\.regulierung' specs/0016-…/` findet nichts: T51 nennt
die Finanzmarktregulierung mit „1 Stufe" und „`0 … regulierung_stufen`", nie mit
`schrittweite[regulierung]`.

## Was daran nicht schlimm ist, und warum es trotzdem ein Paket ist

**Keine Marke aendert sich.** Die 25 Sternmarken stehen unter der Regel dieser Datei; die
Adressregel ist hier nicht anzuwenden, sondern nur zu vergleichen. `[instrument.regulierung]`
bleibt sternfrei. Wie schon bei 0042 stimmt das Ergebnis und die Begruendung nicht.

**Die Begruendung traegt trotzdem etwas.** Sie ist die Stelle, an der die Datei erklaert,
warum ihr Markierungsregime neben dem des Adressverzeichnisses bestehen kann. Der jetzige
Satz erklaert das mit einer Behauptung, die einer der vier Tabellenkoepfe widerlegt — wer
beides liest, haelt entweder die Begruendung oder die Marken fuer falsch, und beides zu
Unrecht. Der wahre Grund ist besser: Die Abweichung hat hier genau einen Fall, er ist
belegbar, und er kostet keine Marke. Eine Begruendung, die ihren eigenen Ausnahmefall nennt,
haelt dem naechsten Leser stand; eine, die ihn wegdefiniert, nicht.

## Was zu tun ist

Ersetz **nur den letzten Satz** des Absatzes (ab „Und weil die zwoelf Schluessel"). Der neue
Satz — zwei duerfen es sein — sagt, was wirklich gilt: dass die beiden Regeln an den neun
Schluesseln der drei datenverankerten Instrumente dasselbe ergeben, an den drei Schluesseln
unter `[instrument.regulierung]` dagegen auseinandergehen, weil das Adressverzeichnis dessen
Instrumentenkennung als gebildet fuehrt (mit Fundstelle) — und dass das keine Marke dieser
Datei aendert, weil hier die Regel dieser Datei gilt.

**Der Wortlaut ist deine Entscheidung, nicht die dieses Auftrags.** Zweimal hat ein
vorgeschriebener Halbsatz an dieser Stelle einen Fehler erzeugt; dieses Paket schreibt
deshalb die Pruefbedingung vor und nicht den Satz.

**Was du nicht tust:** Du fasst keinen der 50 Schluessel an, keine Zahl, keine Klasse, keine
Schranke und **keine Marke**. Der erste Satz des Absatzes bleibt unveraendert — an ihm
haengen 25 Markierungen. Die Saetze zum Adressverzeichnis (0028) und die Nennung des
Instrumentenindex (0042) bleiben, wie sie sind. **Und du fasst BEFUNDE Punkt 1 nicht an:**
Ob dessen „woertlich in specs/" fuer `instrument_min[zoll]` und fuer das Haushaltspaar
ebenso genau ist wie fuer den Leitzins, ist eine eigene Frage, an der Marken haengen. Faellt
dir dazu etwas auf, meldest du es, statt es zu aendern.

## Abnahme

1. **Der Absatz behauptet nicht mehr, beide Regeln ergaeben an allen zwoelf Schluesseln
   dasselbe, und nennt den Regulierungsfall mit Fundstelle.** Der Pruefer legt den Absatz
   neben den Tabellenkopf `[instrument.regulierung]` und neben die Bildungsregelzeile
   „Instrumentenkennung der Finanzmarktregulierung" in `daten/adressen.md`. Kein Satz des
   Absatzes darf gegen diese beiden falsch sein.
2. **Der Instrumentenindex bleibt benannt.** Die Abnahme 1 von 0042 gilt weiter: Ein Satz,
   aus dem folgt, die Datei kenne keinen Instrumentenindex, ist ein Ruecklauf. Ebenso ein
   Satz, aus dem folgt, eine der 25 Marken sei zu aendern.
3. **Sonst hat sich nichts geaendert.** Die drei Selbstproben liefern weiter 46, 4 und 50;
   die 25 Sternmarken stehen an denselben Namen; der erste Satz des Absatzes ist
   unveraendert; im Abschnitt `BEFUNDE` ist kein Zeichen angefasst. Der Nachweis wird an der
   Datei gefuehrt, **nicht** ueber `git diff --stat`: Der Commit dieses Vorhabens traegt
   regelmaessig fremde Arbeit und einen fremden Betreff.

## Warum das ein eigenes Paket ist

**Nicht in 0042.** Dessen Vorgabe schreibt den zu ersetzenden Satz woertlich vor; ein
Ruecklauf dorthin verlangte vom Bauagenten, gegen seinen eigenen Auftrag zu schreiben. Das
Paket ist ausserdem geprueft und abgeschlossen.

**Nicht in 0035.** Das Paket ist auf Belegstellen beschraenkt und abgeschlossen; hier geht
es um eine Sachaussage.

**Reihenfolge.** `dateien` ist `parameter.toml` und schneidet damit jedes andere Paket auf
dieser Datei. Das serialisiert der Projektmanager.

## Was ausdruecklich kein Befund ist

- **Dass der Absatz die Adressregel nur mit ihrem ersten Ast wiedergibt** (ohne die
  Zusammensetzungs-Alternative, ohne die T46-Ausnahme). In der Pruefung zu 0028 geprueft und
  ausdruecklich nicht beanstandet.
- **Die Gueltigkeit der Datei als TOML.** Ein Parser laeuft in dieser Umgebung nicht.
  Behaupte nicht, einer sei gelaufen.
