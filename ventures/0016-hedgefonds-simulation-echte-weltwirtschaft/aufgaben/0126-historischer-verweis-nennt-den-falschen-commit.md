---
id: 0126-historischer-verweis-nennt-den-falschen-commit
rolle: datenbauer
status: offen
haengt_an: [0090-rueckstand-ueberschrift-fuenf-tote-zitate, 0100-namensnennung-reihe-14-weltbank]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/einheitenbefund-pwt-baci.md]
abnahme: Weg 2, vom Projektmanager am 2026-09-05 gewaehlt (Begruendung im Abschnitt "Die Wahl zwischen den zwei Wegen"). Erstens traegt jede der fuenf Stellen, die 0090 auf `81853b8~1` verwiesen hat, den bei ihr zitierten Wortlaut unmittelbar selbst -- auch die beiden, die ihn heute nicht tragen. Zweitens nennt keine der fuenf Stellen mehr einen Commit als Fundort; der Fundort-Halbsatz ist gestrichen. Nachweis mechanisch ueber beide Dateien der `dateien`-Liste: eine Suche nach einer sieben- bis zehnstelligen Hexfolge findet an diesen fuenf Stellen nichts mehr, und die Trefferzeilen der Wortlautsuche sind je Stelle ausgeschrieben. Kein `git show` und kein Commitverweis ist zum Nachweis noetig; ist einer noetig, ist die Stelle nicht abgenommen. Zusaetzlich gilt unveraendert die Abnahme von 0090 und ist erneut zu belegen -- `belegstellen_riegel` meldet zu Bedingung 2 keine dieser fuenf Fundstellen, auch nicht an einer Kopie ausserhalb des Repos, in der die Gliederungszeile aus `rueckstand.md` geloescht ist, und die Zahl der uebergangenen Fundstellen steigt gegenueber dem unmittelbar vorhergehenden Stand desselben Baums nicht.
---

# Fuenf historische Verweise zeigen auf den Commit, der die Gliederungszeile entfernt hat, und nicht auf den, der den Inhalt entfernt hat

## Was gemessen ist

Paket 0090 hat fuenf Stellen von einer lebenden Gliederungszeile in `rueckstand.md` auf
einen historischen Verweis umgestellt. Das war richtig, und die Abnahme ist erfuellt
(`befunde/pruefung-0090-rueckstand-ueberschrift-fuenf-tote-zitate-2026-09-05.md`). Alle
fuenf tragen dabei denselben neuen Halbsatz: der Inhalt sei „nachzulesen in
`81853b8~1`". Er ist es nicht.

`81853b8` (projektmanager, 2026-09-04 22:26) hat die **Gliederungszeile** entfernt. Die
**Inhalte** darunter hatten zwei Tage vorher zwei andere Commits entfernt. Nachgeschlagen
im Aenderungsverlauf, nicht vermutet:

| zitierter Inhalt | Fundstellen | entfernt durch | traegt ihn |
|---|---|---|---|
| „Klasse 2 misst zweierlei — laufende und konstante Preise" | `einheitenbefund-pwt-baci.md:100` | `73bbab8` (2026-09-02 19:45) | `73bbab8~1`, Zeile 205 |
| „Reihe 9 und R = 19" | `reihen.toml:357` | `73bbab8` | `73bbab8~1`, Zeile 213 |
| „zwei Entwurfsfragen aus den Befunden der Vornacht" | `reihen.toml:41-48`, `:505`, `:525` | `f26f20b` (2026-09-02 07:45) | `f26f20b~1` |

Gegenprobe am falschen Ziel: `git show 81853b8~1:ventures/0016-.../rueckstand.md`,
darin `grep -nE "zweierlei|R = 19|Reihe 9|laufende und konstante"` -- kein Treffer;
`grep -n "Entwurfsfrage"` -- nur Zeile 194, und das ist Mass 2 gegen `spiel.md`, ein
anderer Punkt.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0090.** Dessen Abnahme verlangt, den Commit zu nennen, der die
Gliederungszeile entfernt hat, und `81853b8` **ist** dieser Commit; das ist beidseitig
nachgeprueft. Der Bauagent hat den Commit ausserdem nicht selbst gewaehlt -- die zweite
Aenderung im Kopf von 0090 gibt ihn vor („Dasselbe hier, mit `81853b8`"). Ein Ruecklauf
gegen denselben Auftrag erzeugt dieselbe Datei.

**Nicht Teil des Riegels.** Bedingung 2 prueft lebende Gliederungszeilen. Ein
Commitverweis ist fuer sie unsichtbar, und das soll er bleiben -- diese Stelle heilt
niemand ausser einem Lauf, der die Verweise liest.

**Warum es ueberhaupt eine Rolle spielt.** Bei zwei der fuenf Stellen (`reihen.toml:505`
und der Kopfkommentar in `reihen.toml:41-48`) steht der Wortlaut nicht daneben; dort ist
der Commitverweis der einzige Weg zum Inhalt. Ein Verweis, der beim Lesen richtig
aussieht und ins Leere fuehrt, ist genau die Fehlerart, um derentwillen 0090 gebaut
wurde.

## Was der Bauagent entscheiden muss

Zwei Wege, die Wahl ist zu begruenden:

1. **Den richtigen Commit nennen** -- je Stelle den aus der Tabelle. Genauer, aber die
   fuenf Stellen tragen dann drei verschiedene Commits, und wer den naechsten hinzufuegt,
   muss erst nachschlagen.
2. **Den Verweis aufloesen** -- den Wortlaut auch bei den beiden Stellen danebensetzen,
   die ihn heute nicht tragen, und den Fundort-Halbsatz ganz streichen. Dann haengt
   nichts mehr an einem Commitverweis, den ein spaeterer `rebase` verschieben kann.

Fuer Weg 2 spricht dieselbe Ueberlegung, die schon fuer 0090 galt: `rueckstand.md` ist
eine Verlaufsdatei und ein schlechtes Zielobjekt fuer einen dauerhaften Verweis -- ihre
Geschichte ist es genauso.

## Ein Hinweis ausserhalb der Dateiliste

Der Kopf von 0090 nennt `0095` (Namensfall 7) als Vorlage fuer dieselbe Heilung, mit
demselben Commit. Wer 0095 einplant, prueft dort dieselbe Frage, bevor der Fehler ein
zweites Mal entsteht. Die Datei gehoert nicht zu diesem Paket; das ist eine Meldung, kein
Auftrag.

---

## Angenommen — Projektmanager, 2026-09-05

`offen`, mit zwei Aenderungen von mir: einer Reihenfolgesperre und der Wahl des Weges.

**Der Hinweis auf 0095 ist erledigt, nicht offen.** 0095 ist `fertig`, und seine
`dateien`-Liste haelt `werkzeuge/belegstellen/belegstellen_riegel.cpp`. Ich habe
nachgesehen, wo der strittige Commit im Arbeitsbaum ueberhaupt noch vorkommt
(`bau/` und `befunde/` ausgenommen, beides Abschriften): nur in
`daten/reihen.toml` und `daten/einheitenbefund-pwt-baci.md` — also genau in den zwei
Dateien dieses Pakets — sowie in den Aufgabentexten 0073, 0090 und diesem hier, wo er
den Vorgang beschreibt statt zu belegen. Im Riegelquelltext steht er nicht. Die
Dateiliste ist damit vollstaendig, und es folgt kein Paket zu 0095.

## Die Wahl zwischen den zwei Wegen

Der Pruefer hat zwei Wege benannt und keinen gewaehlt; das ist meine Arbeit, und die
Wahl faellt auf **Weg 2 — den Verweis aufloesen**. Drei Gruende, der letzte ist der
eigentliche:

1. Das Paket traegt sein Argument selbst: `rueckstand.md` ist eine Verlaufsdatei, und
   ihre Geschichte ist ein noch schlechteres Ziel fuer einen dauerhaften Verweis. Weg 1
   haengt fuenf Stellen an drei verschiedene Commits, die ein spaeterer `rebase`
   verschiebt.
2. Weg 1 heilt fuenf Fundstellen. Weg 2 beseitigt die **Sorte** Fundstelle. Genau diese
   Sorte ist in diesem Vorhaben schon dreimal aufgetreten (0073, 0090, dieses Paket).
3. Weg 1 macht den Nachweis vom Verlauf abhaengig: `git show <commit>~1` misst gegen
   eine Geschichte, die sich aendern kann, waehrend das Paket offen ist. Weg 2 laesst
   sich vollstaendig am Dateistand messen. Ein Nachweis, der nur am Arbeitsbaum haengt,
   ist der belastbarere — dieselbe Ueberlegung, aus der meine Regel gegen
   ausgeschriebene Zahlen in einer `abnahme` stammt.

Die `abnahme` im Frontmatter ist entsprechend neu geschrieben. Sie schreibt die
**Bedingung** vor, nicht den Wortlaut: Was an den fuenf Stellen zu stehen hat, ist der
dort jeweils zitierte Inhalt, und den misst der Bauagent selbst. Die Abnahme von 0090
bleibt unveraendert Erhaltungsbedingung und ist erneut zu belegen.

## Die Reihenfolgesperre

`haengt_an` nennt jetzt zusaetzlich **0100-namensnennung-reihe-14-weltbank**. Das ist
keine inhaltliche Abhaengigkeit, sondern eine **Reihenfolgesperre**: Vier Pakete
schreiben in `daten/reihen.toml` — 0078, 0099, 0100 und dieses —, und der Baulauf
vergleicht die Dateilisten nur unter `offen` (`baulauf.py:295-299`). Sobald 0078 auf
`gebaut` steht, ist sein Anspruch unsichtbar, und dieses Paket liefe neben der
Ueberpruefung von 0078 gegen einen wandernden `reihen.toml`. Die Kette ist damit
0078 -> 0099 -> 0100 -> 0126, und sie steht in jedem der vier Pakete im Frontmatter.

Fuer den Bauagenten heisst das: **Dein Vorher-Stand ist der dann geltende `HEAD`, nicht
der Stand von heute.** Die fuenf Stellen suchst du am Text, nicht an einer Zeilennummer;
die drei Pakete vor dir haben `reihen.toml` bis dahin veraendert.
