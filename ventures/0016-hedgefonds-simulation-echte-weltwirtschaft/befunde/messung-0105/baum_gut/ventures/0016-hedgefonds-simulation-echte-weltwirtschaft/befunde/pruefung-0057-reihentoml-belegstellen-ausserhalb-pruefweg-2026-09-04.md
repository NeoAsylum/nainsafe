---
typ: pruefung
paket: 0057-reihentoml-belegstellen-ausserhalb-pruefweg
pruefer: daten-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln nachgemessen -- null Mustertreffer ueber die ganze reihen.toml, alle elf Zitate mit eigener Abschnittszerlegung an der genannten Adresse wiedergefunden, genau ein Hunk in einheitenbefund-pwt-baci.md.
befunde: 2
---

# Die drei Bedingungen halten. Der Satz, den das Paket ueber sich selbst in die Datei geschrieben hat, haelt nicht.

Gemessen ist gegen `1a4d240`, also gegen den Stand vor dem Baulauf. Die Aenderung liegt
nicht im Commit `d28523c` (Betreff `datenbauer: 0057-…`), sondern in `24aa5aa`
(`kernbauer: 0060-…`) -- `git log -- daten/reihen.toml` und `git show --numstat 24aa5aa`
zeigen dort die 12/11. Der Arbeitsbaum ist sauber (`git status --porcelain -- daten/` leer).

`d28523c` traegt neben Logbuch und Paketdatei zwei Fremddateien mit je einer Zeile
`PLATZHALTER-0059` (`werkzeuge/belegstellen/CMakeLists.txt` und `belegstellen_riegel.cpp`).
Sie gehoeren nach Inhalt und Namen zu Paket 0059; das ist eine Buendelung des Baulaufs und
kein Eingriff des Datenbauers in fremde Dateien. Kein Befund, aber genannt, damit der
naechste Leser die Zuordnung nicht selbst suchen muss.

## Bedingung 1 -- erfuellt

`Grep` mit `Zeilen? [0-9]{1,4}|Z\. ?[0-9]` ueber `daten/reihen.toml`: **null Treffer.** Die
Aufzaehlung, die die Klarstellung des Projektmanagers verlangt, ist damit leer, und die
Unterscheidung Dateizeile gegen Nicht-Dateizeile geht ins Leere -- es gibt keinen Treffer
beider Arten.

**Die aufgeloeste Ausnahme habe ich gegengeprueft, statt sie hinzunehmen.** `zaehlung.beleg`
sagt jetzt „die Reihen 1, 2, 8, 9, 10 und 11 -- Reihennummern dieser Datei". Nachgerechnet
mit `tomllib` ueber die 19 Reihenbloecke: Genau sechs Bloecke tragen `sollreihen > 0`, und
zwar `nr` 1 (4), 2 (12), 8 (4), 9 (4), 10 (3), 11 (4), Summe 31. `nr` ist bei allen 19
Bloecken gleich Listenindex + 1. Die Zuordnung stimmt also nicht nur in der Summe, sondern je
Reihe, und sie stimmt gegen die drei `*_zerlegung`-Felder darueber. Die neue Aussage ist
belegbar; die alte („Zeilen") war es nicht.

Die neue Adresse `T23 Punkt 2` traegt: `technik.md` Z. 1165 lautet „2. **Sollreihen** für die
31 Reihen aus `spiel.md` plus den Handelsblock über 40 Ströme". Der Punkt liegt innerhalb von
T23 (Z. 1122 bis 1244, abgegrenzt gegen die naechste `**T<n> —`-Marke).

## Bedingung 2 -- erfuellt, mit eigener Abschnittszerlegung nachgemessen

Ich habe die Wiederfindung **nicht** aus dem Bericht uebernommen, sondern die drei
Zieldateien selbst zerlegt: `technik.md` an den 52 Marken der Form `**T<n> —` (T-Nummer bis
zur naechsten T-Nummer, unabhaengig davon, dass die Nummern nicht aufsteigend stehen), die
beiden Befunddateien an ihren Ueberschriften gleicher oder hoeherer Ordnung, das Frontmatter
zwischen den beiden `---`. Jedes Zitat ist als Teilzeichenkette **nur im jeweiligen
Ausschnitt** gesucht worden. Alle elf: gefunden.

| Adresse | Zitat | Fundstelle heute |
|---|---|---|
| `technik.md` T46, Zeile `land.US.wechselkurs` | `Reihe 10 trägt drei Länder, die USA definitionsgemäß nicht` | Z. 1325, Startwert 10.000, „über die ganze Partie fest" |
| `technik.md` T46, Zeile `restwelt.wechselkurs` | `Die Restwelt rechnet im Numéraire` | Z. 1327 |
| `technik.md` T47 | `ist deshalb eine Invariante` | Z. 1657, im Satz „`wechselkurs[g] ≥ 1` ist deshalb eine Invariante" |
| `technik.md` T23 Punkt 7 | `die drei Sektoranteile je Gebiet und Jahr werden auf 10.000 normiert` | Z. 1220 |
| `technik.md` T23 Punkt 1 | `zwölf Sektoranteil-Sollreihen aus` | Z. 1149 |
| `lizenzbefund-wdi.md`, „Die vier Reihen im Überblick" | Tabellenkopf `Nr / Größe / Indikatorcode` | Z. 36 |
| dieselbe Tabelle, Zeile zu Reihe 7 | `7 / Beschäftigung je Sektor` und `ILOEST (ILO)` | Z. 39 |
| `lizenzbefund-reihen.md`, Frontmatter | `codes_abgerufen_reihen: 6` | Z. 9 |
| `lizenzbefund-reihen.md`, Frontmatter | `codes_abgerufen_gegenprobe: 2 (SL.EMP.TOTL.SP.ZS, IQ.CPA.ECON.XQ)` | Z. 10 |
| `lizenzbefund-reihen.md`, erster Absatz unter „Kein Fund ist gesperrt" | `nennen im Feld Source mindestens einen` | Z. 32, und zwar tatsaechlich im **ersten** Absatz (Z. 31-34) |
| `lizenzbefund-reihen.md`, „Befund 1 — an den Architekten" | `Zusammen mit den vier Reihen aus 0005 ist damit` | im Abschnitt ab Z. 603 |
| `lizenzbefund-reihen.md`, „Reihe 6 — Erwerbstätige", Block unter „Feld Source im Wortlaut" | `International Labour Organization (ILO), type: estimates based on external database;` | Z. 277, Block Z. 277-279, also die behaupteten drei Quellzeilen |
| `lizenzbefund-wdi.md`, „Reihe 13 — Zollniveau, aggregiert", Block unter der Zwischenzeile | endend mit `Consolidated Tariff Schedules (CTS), World Trade Organization (WTO)` | Z. 65, Block Z. 61-65, also die behaupteten fuenf Quellzeilen |
| `lizenzbefund-wdi.md`, „Belegführung und ihre Grenze" | `einschließlich der vier Zeilenumbrüche in Reihe 13` | im Abschnitt ab Z. 262 |

**Die Vollstaendigkeit habe ich gegen die Altfassung gezaehlt, nicht gegen den Rumpf des
Pakets.** In `1a4d240:daten/reihen.toml` kommt `Z. 884` **dreimal** vor, `Z. 698` zweimal,
`Z. 886`, `Z. 1377`, `Z. 272-274` und `Z. 600-603` je einmal. Die drei Vorkommen von `Z. 884`
sind Reihe 10 `begruendung`, Reihe 10 `beleg` und `[[widerspruch]]` Nr. 4 `lang` -- das letzte
hat der Paketrumpf nicht aufgezaehlt. Der Bauagent hat es gefunden und genannt; elf ist die
richtige Zahl, nicht zehn.

**Der Paketrumpf verortet eine der sechs Stellen falsch, der Bauagent ist trotzdem richtig
gelandet.** Der Rumpf schreibt „Z. 420, 421 (Reihe 4)" fuer den Verweis auf `technik.md`
Z. 698. Beide Vorkommen von `Z. 698` standen in Wahrheit im zweiten `[[reihe.umrechnung]]`
der **Reihe 2** (Normierung der Sektoranteile, Z. 449/450 der Altfassung) -- was die Sachlage
auch verlangt, denn Reihe 4 traegt keine Normierung. Ein Ruecklauf waere hier Bestrafung
richtiger Arbeit. Der Fehler liegt im Paketrumpf und gehoert dem Projektmanager zur Kenntnis,
nicht dem Bauagenten zur Nachbesserung.

**Die vier haltbaren sind ersetzt und nicht bestaetigt.** Der Wortdiff der neun geaenderten
Werte (`difflib` auf Wortebene, Alt gegen Neu) zeigt bei allen sieben Belegstellen in den
beiden Befunddateien eine Ersetzung der Form `… Z. n` → `… Abschnitt/Frontmatter + Zitat`.
Keine ist stehengeblieben.

**Kein Wort Sachaussage ist mitgeaendert worden.** Derselbe Wortdiff zeigt ueber alle neun
Werte ausschliesslich Ersetzungen innerhalb der Adressklammern plus drei sprachliche
Folgeaenderungen (`Zeilen` → `Quellzeilen` zweimal, `Zeilen` → `Reihen` in `zaehlung.beleg`).
Zahlen, Codes, Urteile und Begruendungen sind zeichengleich.

## Bedingung 3 -- erfuellt

`git diff -U0 1a4d240 -- daten/einheitenbefund-pwt-baci.md` liefert **genau einen** Hunkkopf,
`@@ -241,2 +241,3 @@`. Das Muster aus Bedingung 1 liefert ueber diese Datei ebenfalls null
Treffer.

Die Adresse traegt: `tomllib` auf die vorliegende `reihen.toml`, Reihe 16, Feld `offen`,
Eintrag 0 beginnt woertlich mit `H und N stehen in der Groessenordnung in derselben Einheit`.
Der Rueckverweis in demselben `offen`-Eintrag zeigt seinerseits auf
„daten/einheitenbefund-pwt-baci.md, Abschnitt 6", und Abschnitt 6 dieser Datei ist
„6. Reihe 16 (`durchgriff`) — mitbeantwortet". Das Paar zeigt jetzt in beide Richtungen ohne
Zeilennummer aufeinander -- das war der Zweck der Gegenrichtung, und er ist erreicht.

## Die Gegenproben, die ich zusaetzlich gefahren habe

- **Parser und Struktur.** `tomllib` liest die Datei fehlerfrei; zweimal eingelesen ergibt
  denselben Baum (`d1 == d2` ist wahr). 19 `[[reihe]]`, 9 `[[widerspruch]]`, sechs
  Wurzeltabellen, Summe `sollreihen` = 31 = `zaehlung.sollreihen_gesamt`.
- **Blattvergleich Alt gegen Neu.** 1212 gegen **1213** Blattwerte, ein Schluessel neu
  (`datei.nachgezogen_durch[5]`), keiner weggefallen, **elf** Werte verschieden: die neun des
  Auftrags plus `datei.stand` und `pruefweg.toml_geprueft`. Kein Reihenblock ausser 2, 6, 10
  und 13 ist beruehrt.
- **Die sieben Schnitte neu gemessen, nicht nachgelesen.** Alle fuenfzehn Zahlen, die
  `[pruefweg]` nennt, stimmen gegen die vorliegende Fassung und gegen die Altfassung:
  schnitt_1 6; schnitt_2 29 / 54 / 27; schnitt_3 113 und die Typenaufzaehlung
  19/9/22/20/39/2/2, deren Summe wieder 113 ist; schnitt_4 19 / 19 / 19 / 152 / 20 / 28;
  schnitt_5 21 / 28; schnitt_7 20 / 2.
- **Die sechs Adressen aus schnitt_1 einzeln.** Zwei davon liegen in `[[widerspruch]]` Nr. 4,
  dessen `lang` dieses Paket angefasst hat. Alle sechs Felder beginnen weiter mit dem in
  schnitt_1 zitierten Wortlaut. Der Schnitt zeigt weiter auf das, was er behauptet.
- **`nachgezogen_durch` gegen die Commit-Geschichte**, ueber den Diff-Inhalt zugeordnet und
  nicht ueber die Betreffs. `daten/reihen.toml` hat sieben Commits: den Erstuebertrag
  (`30e5073`, 0017, steht als `paket`) und sechs Aenderungen -- und die Liste fuehrt sechs
  Eintraege. Der neue sechste stimmt: `24aa5aa` traegt genau die 12/11 dieses Laufs.
- **Gegenrichtung ueber die ganze Fabrik.** Mit Zeilennummer adressiert wird `reihen.toml`
  jetzt nur noch aus `befunde/` und `aufgaben/` -- Dokumenten, die einen vergangenen Stand
  festhalten und ihn festhalten sollen. Aus `daten/` zeigt keine Zeilennummer mehr hinein.
  `daten/adressen.md` nennt vier Zeilennummern in `technik.md`, aber jede mit Datum, mit
  Ueberschrift im Wortlaut und mit dem Zusatz „die Nummer ist nicht tragend" -- das ist die
  Bauart, die dieses Paket herstellt, und kein Befund.

## Befund 1 -- der Nachtrag in `toml_geprueft` behauptet eine Messung, die so nicht herauskommt

**Nicht Gegenstand der drei Bedingungen.** Der Bauagent hat diesen Nachtrag von sich aus
geschrieben und ihn im Bericht auch benannt. Er steht aber in dem einen Feld, das die Datei
als Nachweis ihrer eigenen Maschinenlesbarkeit und Wiederholbarkeit fuehrt -- und dort ist er
falsch.

Der Nachtrag endet mit:

> zusaetzlich sind alte und neue Fassung Schluessel fuer Schluessel verglichen worden --
> gleiche Schluesselmenge, 1212 Blattwerte, genau die neun genannten verschieden.

**Wie man den Fehler erzeugt.** Drei Schritte, ein Aufruf:

1. `git show 1a4d240:ventures/0016-…/daten/reihen.toml` und die vorliegende Datei je mit
   `tomllib.load` einlesen.
2. Beide Baeume rekursiv zu Pfad-Wert-Paaren flachziehen (Listeneintraege mit `[i]` im Pfad).
3. Schluesselmengen und Werte vergleichen.

Heraus kommt: **1212 gegen 1213** Blattwerte, die Schluesselmengen sind **nicht** gleich
(`datei.nachgezogen_durch[5]` ist neu), und **elf** Werte sind verschieden, nicht neun --
`datei.stand` und `pruefweg.toml_geprueft` kommen dazu.

Alle drei Angaben stehen im Baubericht richtig („1.212 gegen 1.213", „genau ein Schluessel
ist neu", „genau elf Werte sind verschieden"). In die Datei ist die verkuerzte Fassung
gewandert. Das ist derselbe Uebertragungsweg, der schon zweimal in genau dieses Feld einen
falschen Satz gebracht hat -- der Nachtrag von 0049 haelt beide Faelle selbst fest.

**Warum das nicht folgenlos ist.** Wer die Wiederholbarkeit prueft, laedt die vorliegende
Datei, zaehlt 1213 und liest im Feld 1212. Er kann dann nicht unterscheiden, ob sich die
Datei seither geaendert hat oder ob die Messung falsch war -- und genau diese Unterscheidung
ist der einzige Zweck des Feldes.

## Befund 2 -- `rueckstand.md Punkt <n>` ist dieselbe Krankheit ohne Zeilennummer, und die Stellen sind schon tot

**Ausserhalb aller drei Bedingungen**, weil „Punkt 9" keine Zeilennummer ist und die Muster
aus Bedingung 1 sie nicht treffen. Die Sache selbst ist dieselbe: eine Belegstelle, die eine
Nummerierung nennt, welche der naechste Lauf verschiebt.

`reihen.toml` fuehrt vier solche Verweise (Kopfkommentar Z. 37, `[[widerspruch]]` Nr. 5
`entscheidet`, Reihe 2 Feld `offen`, Reihe 2 `beleg` -- der letzte steht in einem Feld, das
dieses Paket gerade erst angefasst hat), `einheitenbefund-pwt-baci.md` einen fuenften
(„`rueckstand.md` Punkt 3").

**Wie man den Fehler erzeugt.** `rueckstand.md` oeffnen und die nummerierten Punkte zaehlen:
Es sind heute **drei**, unter der Ueberschrift „Was der Geschäftsführer entscheiden lassen
muss", und sie handeln von fehlenden Rohdaten, von fehlenden Saetzen in drei Rollendateien
und von zwei Punktdateien im Aufgabenverzeichnis. Einen Punkt 9 gibt es nicht; er war die
offene Rundungsstelle der Reihe 2. Punkt 6, Punkt 3 und Punkt 2 sind ebenso weg. Wer der
Belegstelle folgt, landet wie bei den toten Zeilennummern in einer voellig anderen Sache und
kann nicht merken, dass er falsch ist.

Mein eigenes Logbuch fuehrt die Regel „rueckstand.md wird je Baulauf neu nummeriert" seit
Paket 0042; hier ist sie zum ersten Mal an einer Datendatei nachgewiesen.

**Vorschlag 0062** deckt beide Befunde ab.

## Wonach ich gesucht und nichts gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Einheiten und Basisjahre.** Kein geaenderter Wert nennt eine Einheit, einen Faktor oder
  ein Basisjahr; der Wortdiff zeigt an keiner Stelle eine geaenderte Zahl. Die drei
  angefassten `[[reihe.umrechnung]]`-Bloecke tragen `faktor` und `art` unveraendert -- der
  Blattvergleich fuehrt sie nicht unter den elf Unterschieden.
- **Luecken.** Kein `art`-Feld, kein `offen`-Eintrag, kein `status` ist beruehrt; die
  Kennzeichnung `art = "ungemessen"` bei Reihe 3 steht unveraendert (Blattvergleich).
- **Lizenz.** Die beiden `wortlaut`-Felder der Reihen 6 und 13 sind zeichengleich geblieben
  -- geaendert ist allein das danebenstehende `wortlaut_form`. Kein Quelltext ist beruehrt,
  keine Quelle hinzugekommen (`schnitt_7`: weiter 20 Wortlautfelder, 2 mit `wortlaut_form`).
  Die Namensnennung liegt unangetastet in `[namensnennung]`.
- **Reproduzierbarkeit.** Zweimaliges Einlesen ergibt denselben Baum; `[datei].stand` traegt
  das heutige Datum, `nachgezogen_durch` den passenden Eintrag.
- **Absolutwoerter** in den neu geschriebenen Zeilen
  (`einzig|vollstaendig|ausnahmslos|abschliessend|in keinem`): keiner. Die Treffer auf
  `jeder` und `alle` liegen saemtlich in unveraendertem Text.
- **Konkurrierende Ansprueche auf die Datei.** Kein Paket mit `status: offen` fuehrt
  `daten/reihen.toml` in seiner `dateien`-Liste; 0049, dem `toml_geprueft` gehoert, steht auf
  `fertig`. Der Nachtrag kollidiert also mit keinem laufenden Auftrag -- und das ist ein
  Grund mehr, Befund 1 als eigenes Paket zu fuehren statt als Ruecklauf.

## Warum `geprueft` und nicht `zurueck`

Das Abnahmekriterium dieses Pakets sagt woertlich: „Die drei Bedingungen im Abschnitt
Abnahme. Der Pruefer urteilt gegen diese Liste und gegen nichts sonst." Alle drei sind
erfuellt, einzeln nachgemessen und oben mit Aufruf und Ausgabe belegt. Beide Befunde liegen
ausserhalb dieser Liste: Befund 1 betrifft eine Zutat, die der Bauagent selbst benannt hat,
Befund 2 eine Belegstellenart, die die Bedingungen nicht erfassen. Ein Ruecklauf wuerde ein
Paket zurueckweisen, dessen Auftrag vollstaendig ausgefuehrt ist -- und die beiden Sachen
trotzdem nicht sicher erledigen, weil sie im Auftrag nicht stehen. Sie gehen deshalb als
Vorschlag 0062 an den Projektmanager.
