---
typ: pruefung
paket: 0043-t48-groessen-gegenkraft-5
pruefer: entwurf-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Die vier Bedingungen des Pakets einzeln — die Namenserhebung ueber spiel.md eigenhaendig wiederholt (33 Namen, Rest null), die Lesetabelle nachaddiert und gegen spiel.md:1249 gelegt, T50 und Abschnitt 12 Punkt 3 gelesen, der verwiesene Abschnitt in spiel.md auf Existenz geprueft
befunde: 2
---

# Pruefung 0043 — T48 fuehrt die Groessen aus Gegenkraft 5

**Urteil: `geprueft`.** Die vier Bedingungen der Abnahme sind erfuellt. Die zwei Befunde
unten liegen **ausserhalb** der vier Bedingungen; sie stehen beide in Abschnitt 18
(Selbstbericht), nicht im normativen Teil, den die Abnahme regelt. Sie sind als Paket
`0092` vorgeschlagen und tragen keinen Ruecklauf — die Abnahme dieses Pakets sagt, wann
der Entwurf **baubar** ist, und das ist er.

## Bedingung 1 — die fuenf Namen, und kein Rest

Ich habe die Erhebung, die T48 selbst abdruckt, mit demselben Muster wiederholt:

```
grep -oE "\b[a-z][a-z0-9_]{2,}\(" spiel.md | sort | uniq -c
```

**33 verschiedene Namen.** Zugeordnet:

- **16 in die T48-Tabelle:** `wert` (1), `korbwert` (2), `anleihewert` (3),
  `waehrungswert` (4), `markt` (5), `stufenwert` (6), `bip` (9), `schuld` (10),
  `handelsvolumen` (11), `anleihekurs` (12), `positionswert` (15), `hub` (18),
  `keilhub` (19), `preishub_zoll` (20), `weltpreis_mit_zoll` (21), `schaden` (22).
- **17 in die Restetabelle:** `menge`, `verschiebung`, `zollstand`, `stufen`,
  `durchgriff`, `preis_start`, `lobbypunkte_aus_schaden`, `gegendruck_neu`, `wmz`,
  `preishub`, `mal_geteilt`, `teile_gerundet`, `lies_neu`, `lies_alt`, `min`, `max`, `sgn`.

16 + 17 = 33. **Rest null**, wie die Bedingung es verlangt.

**Gegenprobe mit einem weiteren Muster**, weil das des Dokuments nur Kleinbuchstaben ab
drei Zeichen sieht: `\b[a-zA-Z][a-zA-Z0-9_]*\(` bringt sieben zusaetzliche Namen —
`C(9,4)` (Binomialkoeffizient, Z. 1472), `R(R+1)/2` (Rundenzahl in Arithmetik, Z. 1555),
`Dichte(t, s)`, `Ergebnis(t, s, k)`, `E(p)` (Messgroessen der Masse 1 und 2, Z. 1533-1567),
`Sektorpreis(t−1)` (Adresse in Prosa, Z. 742), `v(z)` (Pruefstandsgroesse aus T44, in T48
ausdruecklich als ausserhalb des Kerns benannt). Keiner ist eine abgeleitete Groesse des
Kerns. Der Rest bleibt auch unter dem weiteren Muster null.

**Die fuenf Namen des Auftrags einzeln:** `hub` als Nr. 18 mit Klasse und Definition;
`schaden` als Nr. 22 mit vier Zeilen; `menge` und `verschiebung` mit Begruendung, warum
sie keine Groesse sind (`verschiebung` ohne einheitliche Klasse — 5 in der Zollzeile,
3 sonst; `menge` ohne einheitliche Stelligkeit — je Sektor in der Zollzeile, je Land
sonst). `preishub` ist seit Paket 0039 durch `keilhub` und `preishub_zoll` ersetzt, beide
registriert (19, 20); die tote Fassung steht in der Restetabelle. Alle fuenf behandelt.

**Die Formeln gegen die Quelle gelegt** (`spiel.md` Z. 884-921): Die vier `schaden`-Zeilen
in T48 stimmen zeichengenau mit der Schadenstabelle ueberein, `preishub_zoll` mit Z. 895,
`hub` mit Z. 886-887. Klassenprobe: `keilhub` = Klasse 5 mal Klasse 3 durch 10.000 = 5;
`preishub_zoll` = 5 mal Zehntausendstel durch 10.000 = 5; `hub(l, regulierung)` Klasse 10
mal `regulierung_last` Klasse 3 — deckt sich mit `spiel.md`s eigener Spalte („10 × 3") und
mit T49, das dem Regulierungsstand als einzigem Instrument Klasse 10 gibt.

## Bedingung 2 — `handelsvolumen`

Nr. 11 fuehrt die sektorweise Fassung und nennt die einstellige als deren Summe ueber
s ∈ {1, 2}; der Absatz darunter sagt es im Wortlaut („nicht zwei Definitionen desselben
Namens, sondern eine Definition und ihre Aggregation") und haelt fest, dass Nr. 4
(`waehrungswert`) weiterhin die einstellige liest. Erfuellt.

## Bedingung 3 — T50 und Abschnitt 12 Punkt 3

Beide melden die Luecke nicht mehr als offen. T50 schliesst den Satz und verweist auf den
Abschnitt; Abschnitt 12 Punkt 3 steht durchgestrichen mit Erledigungsvermerk. **Der
verwiesene Abschnitt existiert**: `spiel.md:863`, `### Der Schaden in Gegenkraft 5, als
Rechenvorschrift`, im Wortlaut des Verweises. Ein Verweis ins Leere waere hier der
naheliegende Fehler gewesen; er liegt nicht vor.

## Bedingung 4 — die Kostenzeile

Nachaddiert aus der Lesetabelle: `16 + 2 + 40 + 12 + 4 + 16 + 16 = 106`. Stimmt.
**Und sie stimmt mit `spiel.md` ueberein**: Z. 1249 nennt dieselbe Summe mit derselben
Aufschluesselung, Z. 2105 und 2122 dieselbe 106 nebst 16 Schreibzugriffen und 16 Aufrufen.
Die Ueberleitung `112 + 8 − 16 + 2 = 106` habe ich einzeln nachgerechnet (112+8=120,
−16=104, +2=106) und gegen ihre Begruendung gehalten: +8 ist der Zollstand mit `lies_neu`
und `lies_alt` (4 Laender × 2), −16 die beiden entfallenen Sektorpreiszeilen (je 4×2),
+2 die zwei Weltpreise. `spiel.md:1262` schreibt dieselbe Rechnung gruppiert als
`112 + 4 + 4 − 8 − 8 + 2 = 106` — dieselben Summanden, kein Widerspruch.

Die **112** stammt aus meinem eigenen Befund vom 2026-09-02. Ich habe sie nicht
wiedererkannt, sondern die 106 von der Tabelle aus neu gerechnet; das Urteil haengt an der
Tabelle, nicht an meiner alten Zahl.

---

# Befunde

Beide sind Zaehlfehler in **Abschnitt 18**, dem Selbstbericht. Keiner beruehrt die vier
Bedingungen, keiner blockiert den Bau. Der zweite ist der teurere, weil der
Projektmanager aus genau dieser Liste das Folgepaket zuschneidet.

## Befund 1 — „an drei Stellen" sind sechs (`technik.md` Abschnitt 18, Punkt 1 der Nachzugsliste)

Abschnitt 18 meldet: *„`kern/include/kern/werte.hpp` sagt an drei Stellen ‚siebzehn'"* und
nennt Kopfzeile, Nachweisabsatz und Blockueberschrift.

**So erzeugt man den Fehler:**

```
grep -n "siebzehn" ventures/0016-.../kern/include/kern/werte.hpp
```

Ergibt **fuenf** Treffer, nicht drei: Z. 2 (Kopfzeile, genannt), Z. 16 (*„noch eine der
siebzehn Groessen hier ist, ist ein Befund"* — **nicht genannt**), Z. 28 (Nachweisabsatz,
genannt), Z. 33 (*„muesste jede der siebzehn Funktionen sie einzeln durchreichen"* —
**nicht genannt**), Z. 115 (Blockueberschrift, genannt).

Dazu eine **sechste**, abgeleitete Stelle: Z. 30 sagt *„`Konstanten` ist keine achtzehnte
Groesse"*. Die Ordnungszahl folgt aus der 17 und muss auf „dreiundzwanzigste" mit.

**Warum das mehr ist als eine Zahl:** Der Annahmevermerk des Pakets sagt, das
Kernbauer-Folgepaket werde aus dieser Meldung zugeschnitten. Ein Paket gegen drei
genannte Stellen laesst drei stehen — und ausgerechnet Z. 16 traegt die **Regel** von T48
(„weder Adresse noch Parameter noch eine der siebzehn"), also die Stelle, an der eine
falsche Zahl den Nachweis selbst verstellt.

## Befund 2 — „die zwoelf erlaubten Reste" sind zweiundzwanzig (`technik.md` Abschnitt 18, Bedingung 1)

Abschnitt 18 schreibt: *„Die Erhebung, ihre Zuordnung und die zwoelf erlaubten Reste
stehen in T48."* T48 selbst schreibt an der Tabelle: *„die **zweiundzwanzig** Namen in den
zehn Zeilen unten"*.

**So erzeugt man den Fehler:** Die Restetabelle (`technik.md` Z. 2093-2104) abzaehlen —
`menge`, `verschiebung`, `zollstand`, `stufen`, `durchgriff`, `welt.preis_start`,
`regulierung_last`, `druck_max`, `stufenweite`, `aufschlag`, `lobbypunkte_aus_schaden`,
`gegendruck_neu`, `wmz`, `preishub`, `mal_geteilt`, `teile_gerundet`, `lies_neu`,
`lies_alt`, `min`, `max`, `sgn`, `wurzel` = **22** (`stufen` einmal gezaehlt, es steht mit
zwei Stelligkeiten in einer Zeile). T48 hat recht, Abschnitt 18 nicht.

Kein Rechtsfolgen-, sondern ein Zitierproblem: Wer die Pruefung wiederholt und den
Selbstbericht als Massstab nimmt, sucht zwoelf Reste und haelt die uebrigen zehn fuer
unerlaubt.

---

# Wonach ich gesucht habe, ohne einen Befund zu schreiben

- **`preishub` und `wmz` „stehen allein im Gegenbeispiel".** Nachgezaehlt: `preishub`
  steht ausserdem in Prosa (Z. 911, 961) und in der Nachziehtabelle (Z. 2121, als
  „entfaellt"). Keine dieser Stellen ist eine **Formel**, und die T48-Regel greift auf
  Formeln — es entsteht kein Rest. Kein Befund.
- **`keilhub` steht in T48 ohne die `lies_neu(...)`-Klammer**, die `spiel.md` Z. 890
  fuehrt. Die Lesetabelle in Abschnitt 10 fuehrt `lies_neu(welt.preis.<s>)` ausdruecklich;
  kein Zahlenwiderspruch, sondern Schreibweise. Nach meiner Rollengrenze kein Befund.
- **`zollstand(RW) = 0`**, die einzige Stelle, an der der Entwurf entschieden statt
  gemeldet hat und die er selbst als seine unsicherste benennt. Nachgesehen: T23 Punkt 5
  fuehrt `durchgriff` mit 5 × 2 = 10 Werten, die Restwelt nimmt an der Preisuebertragung
  also teil und hat nach T15 keine Instrumente. Es ist die einzige Belegung, mit der die
  Formel ueber „je Gebiet" total ist. Kein Befund.
- **`technik.md` rechnet Abschnitt 10 weiter mit `R = 24`**, waehrend `spiel.md` das
  Fenster 2001–2021 fuehrt (Z. 1555 rechnet mit R = 20). Das ist der Nachzug **0064**, und
  der steht auf `offen` — nachgesehen. Solange er offen ist, ist die alte Zahl hier kein
  Befund; Bedingung 4 betrifft allein die 106, und die haelt in beiden Fenstern, weil sie
  je Runde zaehlt.
- **„Drei Groessen liegen ausserhalb des Kerns: `B(z)`, `v(z)`, `e(z)`."** Meine
  Gegenprobe fand mit `Dichte`, `Ergebnis` und `E` drei weitere Groessen ausserhalb des
  Kerns. Sie sind Messgroessen der Masse aus `spiel.md`, keine T44-Pruefstandsgroessen,
  und der Satz ist aelter als dieses Paket. Kein Befund gegen 0043.
- **Mass 2 hat zwei Lesarten** (Frontmatter „hoechstens 25 Prozent besser" gegen
  `max(Ek) ≤ 1,25 × min(Ek)`, `spiel.md` Z. 976). Dieses Paket fasst Mass 2 nicht an —
  weiterhin nur Faehrte, kein Befund.
- **Der Commit `dffb251` fuehrt 40 Dateien**, das Paket beansprucht eine. Nachgesehen:
  ausser `technik.md` und Aufgabendateien sind es ausschliesslich Dateien unter
  `befunde/messung-0069/`, also der Messbaum eines fremden Pakets, den der Runner
  miteingesammelt hat. Kein Schreibzugriff des Architekten ausserhalb seines
  Zielverzeichnisses.
