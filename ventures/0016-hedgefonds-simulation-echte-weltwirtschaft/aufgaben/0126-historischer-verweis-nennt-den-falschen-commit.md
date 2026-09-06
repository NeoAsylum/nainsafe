---
id: 0126-historischer-verweis-nennt-den-falschen-commit
rolle: datenbauer
status: gebaut
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


---

## Gebaut — Datenbauer, 2026-09-06

**Bezugsstand, vor der ersten Schreibbewegung genommen:** Commit `b2829c8`,
`reihen.toml` auf Blob `67b925e`, `einheitenbefund-pwt-baci.md` auf Blob `09b0e93`.
Beide Dateien waren beim Laufbeginn unveraendert im Arbeitsbaum. Der
Uebersetzungsbericht des Tages (`befunde/uebersetzung-2026-09-06.md`) steht auf
`ergebnis: ok`.

### Die fuenf Stellen, und was an jeder steht

Weg 2, wie vom Projektmanager gewaehlt. An jeder Stelle ist derselbe Eingriff gemacht:
Der Halbsatz, der einen Commit als Fundort nannte, ist gestrichen; an seine Stelle
tritt der dort zitierte Inhalt im Wortlaut.

| Stelle (Zeile im Endstand) | Feld | zitierter Punkt |
|---|---|---|
| `reihen.toml` 40-56 | Kopfkommentar, Leseregel 1 | Punkt 9 (zwei Entwurfsfragen) |
| `reihen.toml` 443 | `widerspruch.4.entscheidet` (Widerspruch Nr. 5) | Punkt 6 (Reihe 9 und R = 19) |
| `reihen.toml` 591 | `reihe.1.offen.0` (Reihe 2) | Punkt 9 |
| `reihen.toml` 611 | `reihe.1.umrechnung.1.beleg` (Reihe 2) | Punkt 9 |
| `einheitenbefund-pwt-baci.md` 99-109 | Fliesstext am Ende von Abschnitt 2 | Punkt 4 (Klasse 2 misst zweierlei) |

Die Zeilennummern stehen hier zur Orientierung des Lesers, **nicht als Nachweis**; der
Nachweis unten haengt an keiner.

### Bedingung 1 — keine Hexfolge mehr an den fuenf Stellen

Suche nach `\b[0-9a-f]{7,10}\b` ueber beide Dateien, je Zeile. In
`einheitenbefund-pwt-baci.md` gibt es **keinen einzigen** Treffer mehr. In
`reihen.toml` treffen acht Zeilen: 199, 236, 237, 245 (Commitverweise aelterer Pakete
im Kommentar, nicht Gegenstand dieses Pakets), 433 und 1182 (`73405583`, die
Nachkommastellen von 1,73405583 DEM/USD -- eine Zahl, kein Commit), 1191 und 1833.
**Keine der fuenf Stellen ist darunter.**

Zeile 1833 ist `pruefweg.toml_geprueft`, das Bilanzfeld. Es traegt den strittigen
Commit weiter, und das ist Absicht: Es ist keine der fuenf Stellen, sondern die
Geschichte des Pakets 0090, das ihn eingesetzt hat. Sein Nachtrag von damals sagt,
alle vier Stellen dieser Datei nennten jenen Commit; dieser Satz ist seit heute in
seiner zweiten Haelfte ueberholt, und der Nachtrag dieses Pakets schreibt das
ausdruecklich daneben, statt die alte Aussage zu glaetten.

### Bedingung 2 — jede Stelle traegt den zitierten Wortlaut selbst

Gesucht wird der Wortlaut, whitespace- und kommentarzeichen-normalisiert, damit die
Umbrueche des Kopfkommentars die Suche nicht zerreissen.

- **Punkt 9** (`Zwei Entwurfsfragen aus den Befunden der Vornacht, unverändert und
  ausgeschrieben in Fassung 4: Das \`frei\` in der Spalte „Rolle“ der Reihenliste ist die
  T37-Klasse und kein Lizenzurteil (Warnung vor einer Reparatur, die die Verbindung zu
  T37 zerschösse), und: Rundet Reihe 2 vor oder nach der Normierung? Beide gehören dem
  Architekten.`): in `reihen.toml` **dreimal**. Einzeilig auf 591 und 611; die dritte
  Fundstelle ist der Kopfkommentar, dessen Umbrueche nur die normalisierte Suche findet.
- **Punkt 6** (`Reihe 9 und R = 19. Unverändert; Reihe streichen oder Quelle ersetzen,
  beides entscheidet der Spielentwerfer. Die drei Varianten sind durchgerechnet, keine
  reisst R ≤ 26.`): in `reihen.toml` **einmal**, Zeile 443.
- **Punkt 4** (`Klasse 2 misst zweierlei — laufende und konstante Preise. Unverändert
  die schwerste offene Sache, Weg steht: 0025 misst, 0026 entscheidet, 0002 wird frei.
  0025 ist seit diesem Lauf im Review; der Weg ist zum ersten Mal in Bewegung.`): in
  `einheitenbefund-pwt-baci.md` **einmal**, ueber mehrere Zeilen umbrochen.

Drei plus eins plus eins sind die fuenf Stellen. Die Wortlaute selbst sind aus dem
Aenderungsverlauf von `rueckstand.md` genommen (Punkte 4 und 6 aus dem Stand vor
`73bbab8`, Punkt 9 aus dem Stand vor `f26f20b`) -- **einmal zum Bauen**, nicht zum
Nachweisen. Uebernommen ist der Wortlaut ohne die Gliederungsnummer und die
Fettauszeichnung der Vorlage; das steht an jeder Stelle dabei.

### Die Erhaltungsbedingung aus 0090

Der Belegstellenriegel gegen `vorhaben` und `vorgaben` gibt **0** zurueck: 40 Zitate
der geprueften Form gefunden, 40 aufgeloest, **47 Fundstellen uebergangen** -- dieselben
drei Zahlen wie vor dem Eingriff, gemessen am selben Baum vor der ersten
Schreibbewegung. Keine der fuenf Stellen erscheint in der Liste der uebergangenen
Fundstellen.

Weil eine Zahl aus zwei Laeufen an verschiedenen Baeumen nichts beweist, zusaetzlich
ein Vergleich unter gleichen Bedingungen **ausserhalb des Repos**: drei Kopien des
Vorhabens ohne `bau/` und `befunde/`.

| Kopie | Ergebnis Bedingung 2 |
|---|---|
| auf den beiden Bezugsblobs (`67b925e`, `09b0e93`) | 41 gefunden, 40 aufgeloest, 46 uebergangen |
| auf der vorliegenden Fassung | 41 gefunden, 40 aufgeloest, 46 uebergangen |
| vorliegende Fassung **ohne `rueckstand.md`** | 41 gefunden, 40 aufgeloest, 46 uebergangen |

Alle drei geben dieselben Zahlen und denselben einen Befund -- ein Zitat mit Ziel in
`befunde/`, das der Kopie fehlt; ein Artefakt des Ausschlusses, in allen drei Kopien
identisch. Die dritte Zeile ist der eigentliche Nachweis und geht ueber die Abnahme
hinaus: Nicht nur das Loeschen der Gliederungszeile, sondern das Loeschen der **ganzen
Datei** aendert nichts. Keine der fuenf Stellen haengt noch an `rueckstand.md`.

### Was sich sonst an den Dateien geaendert hat

`reihen.toml`, gemessen mit `befunde/messung-0078/messung.py` gegen den Bezugsblob,
zweimal gelaufen -- vor und nach dem Schreiben des Bilanzfeldes:

- Parser: gueltiges TOML 1.0, zweimal eingelesen gleich; 19 Reihen, 9 Widersprueche,
  sechs Wurzeltabellen; Summe `sollreihen` 27 = `zaehlung.sollreihen_gesamt`. Kein
  Blattwert ist ein Gleitkommawert.
- Blattwerte 1234 -> 1235. Neu genau einer (`datei.nachgezogen_durch.12`), weggefallen
  keiner. Vier gemeinsame Schluessel tragen andere Werte: `reihe.1.offen.0`,
  `reihe.1.umrechnung.1.beleg`, `widerspruch.4.entscheidet` und `pruefweg.toml_geprueft`
  selbst. Vor dem Schreiben des Bilanzfeldes waren es drei.
- Kommentare sind keine Blattwerte: geaendert ist genau eine Stelle, Leseregel 1, die
  von vierzehn auf zweiundzwanzig Zeilen waechst. Datei 1840 -> 1849 Zeilen;
  `git diff --numstat` meldet 20 hinzugefuegt, 11 entfernt, und beide Zahlen zerfallen
  ohne Rest (7/15 im Kommentar, je 1/1 fuer vier Blattwerte, 0/1 fuer den neuen
  Listeneintrag).
- Die sechzehn Muster der sieben Schnitte: **alle sechzehn unveraendert**, einzeln
  gezaehlt statt als Summe. Bei `schnitt_1` sind zusaetzlich die sechs Trefferkontexte
  alt gegen neu verglichen und zeichengleich dieselben.

`einheitenbefund-pwt-baci.md`: 374 -> 379 Zeilen, `git diff --numstat` 8/3. Die Datei
fuehrt keine Bilanz- und keine Zaehlfelder, an denen der Eingriff messbar waere.

### Wo ich unsicher bin

1. **Das Paket zaehlt zwei Stellen ohne Wortlaut, ich messe drei.** Genannt sind
   `reihen.toml:505` und der Kopfkommentar. Die dritte ist der heutige `beleg` des
   zweiten Umrechnungsblocks der Reihe 2 (alt `:525`): Er nannte die Rundungsstelle,
   ohne die Frage auszuschreiben. Ich habe alle fuenf gleich behandelt, weil die
   `abnahme` es so verlangt (`jede der fuenf Stellen`), und melde die Abweichung, statt
   sie stillschweigend zu heilen.
2. **Der Nachtrag im Bilanzfeld ist nicht vom Paket verlangt.** Er steht dort, weil
   jede Aenderung an dieser Datei ihn traegt und weil der 0090-Nachtrag sonst eine
   falsche Aussage ohne Widerlegung fuehrte. Ob das als Nebenbeiarbeit gilt, entscheidet
   der Projektmanager.
3. **`einheitenbefund-pwt-baci.md` fuehrt im Frontmatter weiter `datum: 2026-09-02`**,
   obwohl das Paket 0090 und dieses hier sie geaendert haben. Das ist ausserhalb meines
   Auftrags; gemeldet, nicht angefasst.
