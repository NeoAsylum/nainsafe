---
id: 0100-namensnennung-reihe-14-weltbank
rolle: datenbauer
status: fertig
haengt_an: [0078-reihentoml-preisbasis-nach-t53-nachziehen, 0099-reihentoml-vorlagenliste-um-t53]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Bedingung 3 ist die teure -- dieselbe Selbstmessung mit Bezugsstand wie bei 0078, weil `[namensnennung]` Blattwerte traegt und die Bilanz in `pruefweg.toml_geprueft` dadurch wandert.
---

# `namensnennung.weltbank` fuehrt Reihe 14 nicht, obwohl Reihe 14 seit 0078 Weltbankdaten benutzt

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, mit einer Ergänzung an `haengt_an`

**Vier Prüfungen bestanden.** `datenbauer` steht in `BAUROLLEN`. Die `dateien`-Liste nennt
allein `daten/reihen.toml`. Die drei Bedingungen sind prüfbar, und Bedingung 3 verlangt die
Selbstmessung mit Bezugsstand — richtig, weil `[namensnennung]` Blattwerte trägt und die
Bilanz in `pruefweg.toml_geprueft` mitwandert.

**Warum das kein Nebenbefund bleiben durfte:** `[namensnennung]` ist nach dem Kommentar
darüber nicht eine Notiz, sondern die Stelle, aus der der Jahrgangsbau die ausgelieferte
`LIZENZEN.md` und die Seite „Datenquellen" füllt. Seit 0078 entstehen die ausgelieferten
Werte der Reihe 14 aus BACI **und** aus zwei Weltbank-Indikatoren; die CC-BY-4.0-Pflicht
kommt für die 40 Handelsströme damit nicht ins Produkt. Der Daten-Prüfer hat es
ausdrücklich **nicht** als Rückgabegrund gewertet, weil 0078 das Anfassen der Lizenzblöcke
verbietet — richtig, und genau deshalb ein eigenes Paket.

**Reihe 16 ist mit aufzunehmen**, wie der Vorschlag es vorsieht: Sie steht ebenfalls nur
unter `cepii_baci`, obwohl ihr `N` seit jeher über die Reihen 1 und 2 aus der Weltbank
kommt. Das ist älter als 0078 und dieselbe Sache.

### Die Reihenfolge auf `daten/reihen.toml`

Vier Pakete halten diese eine Datei: **`0090` → `0078` → `0099` → `0100` (dieses).** Du
läufst zuletzt. `haengt_an` trägt deshalb seit heute zusätzlich `0099` — **als
Kollisionsschutz gekennzeichnet, nicht als sachliche Abhängigkeit**: `startbereit()`
vergleicht `dateien` nur unter `offen` (`baulauf.py:273`), und sobald 0099 auf `gebaut`
steht, wäre sein Anspruch unsichtbar.

**Die Folge steht dir zu, und sie ist hier am größten:** Drei fremde Pakete schreiben vor dir
in diese Datei. Jede Zahl in `pruefweg`, jedes Zahlwort in einem Kommentar und die
Blattwertbilanz sind bis dahin gewandert. **Miss deinen Vorher-Stand am dann geltenden
`HEAD` und nenne ihn.**

Vorschlag des Daten-Pruefers vom 2026-09-05, aufgefallen bei der Pruefung des Pakets 0078
(`befunde/pruefung-0078-reihentoml-preisbasis-nach-t53-nachziehen-2026-09-05.md`,
Befund 2).

## Der Sachverhalt

`[namensnennung]` ist keine Notiz. Der Kommentar darueber sagt, wozu sie da ist:

> „gehoert nach den Lizenzen ins Produkt, nicht in eine Notiz. Sie steht hier, damit der
> Jahrgangsbau sie ins Manifest und in die ausgelieferte `LIZENZEN.md` schreiben kann,
> ohne sie neu zusammenzusuchen."

Die Zuordnung Quelle → Reihe laeuft ueber `gilt_fuer_reihen`, und sie steht heute so:

```
namensnennung.weltbank.gilt_fuer_reihen   = [1, 2, 5, 6, 7, 8, 10, 13]
namensnennung.cepii_baci.gilt_fuer_reihen = [14, 16]
```

Seit Paket 0078 entstehen die ausgelieferten Werte der **Reihe 14** nicht mehr allein aus
BACI. Der zweite Umrechnungsblock deflationiert sie mit einem Index aus zwei
Weltbank-Indikatoren — `quelle_deflator` nennt sie im Klartext:

> „Weltbank WDI, Gebiet WLD, Indikatorcodes NE.EXP.GNFS.CD … und NE.EXP.GNFS.KD …
> Das ist Quelle Nr. 1 aus daten.md -- dieselbe Lizenz, dieselbe Zitierpflicht"

**Dieselbe Zitierpflicht** — und genau die kommt nicht ins Produkt, weil die
Weltbankzeile die 14 nicht fuehrt und die Deflatorreihe noch keinen eigenen
`[[reihe]]`-Block hat. Der Zusatz in `namensnennung.weltbank` sagt selbst, was daran
haengt: *„die Namensnennungspflicht ist an jeden weiterzureichen, dem man die Daten
weitergibt."*

**Der zweite, aeltere Fall gehoert dazu, weil er dieselbe Zeile betrifft.** Reihe 16
(`durchgriff`) steht ebenfalls nur unter `cepii_baci`, obwohl ihr `N` seit jeher ueber die
Reihen 1 und 2 aus der Weltbank kommt. Das ist aelter als 0078 — 0078 hat es nur sichtbar
gemacht, indem es Reihe 1 in `quelle_eingebettet` ausdruecklich nennt. Wer die 14
nachtraegt und die 16 stehen laesst, macht die Liste an einer Stelle richtig und laesst
den Leser an der Nachbarstelle glauben, dort sei nichts.

## Warum das ein eigenes Paket ist und nicht Teil von 0078

Drei Gruende, und der erste allein traegt schon:

1. **0078 verbietet es ausdruecklich.** Unter „Was du sonst nicht tust" steht: keine
   Lizenzbloecke anfassen. Der Datenbauer hat sich daran gehalten; das war richtig.
2. **Es ist eine Lizenzfrage, keine Preisbasisfrage.** 0078 zieht eine Entscheidung des
   Architekten nach. Wer welche Quelle im Produkt nennen muss, entscheidet nicht T53,
   sondern `daten.md` und die Lizenztexte — ein anderer Vorgang mit anderer Vorlage.
3. **Der Umfang.** `[namensnennung]` traegt Blattwerte; jede Aenderung verschiebt die
   Bilanz in `pruefweg.toml_geprueft`, und das ist die Bedingung, an der dieses Feld
   inzwischen viermal die halbe Arbeit war. Zusammen mit dem Deflatornachtrag waere das
   kein Lauf.

**Nicht dazu gehoert Reihe 20.** Solange die Reihenliste in `technik.md` Abschnitt 7 die
Deflatorreihe nicht fuehrt, entsteht hier kein `[[reihe]]`-Block — aus demselben Grund,
den 0078 dafuer ausgeschrieben hat. Dieses Paket aendert `gilt_fuer_reihen` und sonst
nichts an der Reihenstruktur.

## Was zu tun ist

1. **`namensnennung.weltbank.gilt_fuer_reihen` um die 14 ergaenzen**, mit einem Wort dazu,
   woher der Anspruch kommt: nicht aus der Quellenreihe, sondern aus dem Deflator des
   zweiten Umrechnungsblocks. Beleg ist `quelle_deflator` derselben Datei und
   `daten.md` Nr. 1.
2. **Ueber die 16 entscheiden und die Entscheidung hinschreiben.** Entweder sie kommt
   dazu (sie erbt `N` aus den Reihen 1 und 2), oder es steht daneben, warum eine
   abgeleitete Groesse ohne eigene Quelle nicht in `gilt_fuer_reihen` gehoert. Beides ist
   vertretbar; ungeschrieben ist es nicht.
3. **Pruefen, ob `gilt_fuer_reihen` ueberhaupt vollstaendig sein will.** Die Tabelle nennt
   keine Regel dazu — es gibt kein Feld, das sagt „jede Reihe steht unter mindestens einer
   Quelle". Wenn das die Absicht ist, gehoert der Satz hin; wenn nicht, gehoert der Grund
   hin. Ohne das weiss der naechste Leser nicht, ob eine fehlende Nummer eine Luecke oder
   eine Aussage ist — und genau daran ist dieser Fall unbemerkt geblieben.

**Kein Rechtsrat.** Dieses Paket legt keine Lizenz aus und entscheidet nicht, ob die
Deflationierung eine „Bearbeitung" im Sinne von CC BY 4.0 ist. Es traegt nach, was
`daten.md` und der Zusatz in `namensnennung.weltbank` bereits sagen. Haelt der Bauagent
die Frage fuer offen, ist das ein Fall fuer den Compliance-Pruefer und gehoert als
`[[widerspruch]]` in die Datei, nicht in eine stille Entscheidung.

## Abnahme

1. **`namensnennung.weltbank.gilt_fuer_reihen` fuehrt die 14**, und die Herkunft des
   Anspruchs steht daneben — mit Fundstelle in derselben Datei, ohne Zeilennummer.
2. **Reihe 16 ist entschieden, nicht uebergangen.** Entweder in der Liste oder mit
   geschriebener Begruendung, warum nicht. Und die Frage aus Punkt 3 oben ist beantwortet:
   Die Tabelle sagt danach selbst, ob sie vollstaendig sein will.
3. **Die Selbstmessungen stimmen nach dem letzten Schreiben**, mit genanntem Bezugsstand
   und den sechzehn Mustern der sieben Schnitte einzeln neu gezaehlt — dieselbe Bedingung
   wie in 0078 und aus demselben Grund. `gilt_fuer_reihen` steht auf einer Zeile, die
   keines der `^`-verankerten Muster trifft; wer das behauptet, zeigt es. Die
   Blattwertbilanz wandert in jedem Fall.

## Rueckläufe

0.
