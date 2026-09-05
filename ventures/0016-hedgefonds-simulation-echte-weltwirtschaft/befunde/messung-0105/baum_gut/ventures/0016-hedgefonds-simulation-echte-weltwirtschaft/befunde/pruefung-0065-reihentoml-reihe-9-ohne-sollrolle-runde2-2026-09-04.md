---
typ: pruefung
paket: 0065-reihentoml-reihe-9-ohne-sollrolle
pruefer: daten-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Bedingung 5 mit eigenem tomllib-Lauf auf der geschriebenen Datei nachgerechnet (acht Blattwerte, Aufteilung 1 + 1 + 6, disjunkt und erschoepfend, jede Fundstelle einzeln), Bedingung 6 an der Herkunft der Zahlen und an der Zerlegung 4/1/1 geprueft, die im Befund der Runde 1 nicht vorkommt; Bedingung 4 unabhaengig an drei Git-Fassungen nachgemessen; Bedingungen 1 bis 3 sind durch den Diff als unberuehrt belegt.
befunde: 0
---

# Pruefung 0065, Runde 2 — `reihen.toml`, Kommentar ueber `[datei.vorlagen]`

## Womit gemessen wurde

Bezugsstand des Bauberichts ist Commit `37cce4d`, Blob
`6cd55ae5375cbf3b51c084fd573150c2846d3d18` — **nachgeschlagen, stimmt** (`git ls-tree`).
Vergleichsstand ist `HEAD` (`849abc3`, Blob `db80e48`). Der Arbeitsbaum fuehrt
`reihen.toml` nicht als geaendert; unter `ventures/` ist allein
`befunde/uebersetzung-2026-09-04.md` geaendert, und die gehoert nicht zu diesem Paket.

Alles maschinell: `tomllib` auf die vorliegende Datei, Baum flach gezogen, Blattschluessel
als Pfadtupel; die Grep-Muster mit `grep -cE` neu gezaehlt; drei historische Fassungen mit
`git show` gezogen.

**Nicht gelesen:** `notizen/datenbauer.md`.

## Der Eingriff — Umfang zuerst

`git diff 37cce4d HEAD -- daten/reihen.toml`: **ein** Hunk, **+8/−2**, Zeilen 141–151,
ausschliesslich Kommentarzeilen (`# …`). Kein Blattwert kann sich dabei geaendert haben,
und damit sind **die Bedingungen 1 bis 3 durch den Diff selbst als unberuehrt belegt** —
sie haengen samt und sonders an Blattwerten. Ich habe sie deshalb nicht erneut
nachgerechnet, wie das Abnahmefeld es vorsieht. Die Zeilenbilanz 1732 → 1738 stimmt
(`wc -l` = 1738).

Entfallen ist:

> Ueberhaupt genannt wird er in **acht** Blattwerten, `datei.vorlagen.einheiten`
> mitgezaehlt; die uebrigen sieben stehen unter `offen`, `begruendung` und `lang`.

Das ist wortgleich der Satz, den Befund 1 der Runde 1 beanstandet hat. Der beanstandete
Fehler ist damit nicht umformuliert, sondern entfernt.

## Bedingung 5 — die Aufteilung geht auf

**Erfuellt, nachgerechnet statt verglichen.** Ich habe die Zaehlregel angewandt, die der
Kommentar selbst aufstellt — Blattwerte des mit `tomllib` eingelesenen Baums, die die
Zeichenfolge `einheitenbefund-pwt-baci` tragen — und die drei Teile aus dem Kommentar als
Praedikate darauf gelegt:

```
python3 - <<'EOF'
import tomllib
d=tomllib.load(open('reihen.toml','rb'))
def flat(o,p=()):
    if isinstance(o,dict):
        for k,v in o.items(): yield from flat(v,p+(k,))
    elif isinstance(o,list):
        for i,v in enumerate(o): yield from flat(v,p+(str(i),))
    else: yield p,o
L=list(flat(d)); N="einheitenbefund-pwt-baci"
hits=[p for p,v in L if isinstance(v,str) and N in v]
t1=[p for p in hits if p[-1]=="beleg"]
t2=[p for p in hits if p==("datei","vorlagen","einheiten")]
t3=[p for p in hits if p[-1]!="beleg" and p!=("datei","vorlagen","einheiten")]
print(len(L), len(hits), len(t1), len(t2), len(t3))
print(len(set(t1)|set(t2)|set(t3)), set(t1)&set(t2), set(t1)&set(t3), set(t2)&set(t3))
EOF
```

Ausgabe: `1214 8 1 1 6` und `8 set() set() set()`.

| Was der Kommentar sagt | von mir gezaehlt |
|---|---|
| Blattwerte mit der Zeichenfolge, **gesamt acht** | **8** |
| als `beleg` **genau einmal**, naemlich `reihe.13.umrechnung.0.beleg` | **1**, dieselbe Adresse |
| der Vorlagenschluessel `datei.vorlagen.einheiten` | **1** |
| **sechs weitere** | **6** |
| `1 + 1 + 6 = 8` | 1 + 1 + 6 = 8 |
| jedes Blatt in genau einem Teil | Vereinigung der drei Teile hat **8** Elemente, alle drei paarweisen Schnitte sind leer |

Die acht Fundstellen einzeln, gegen die Liste im Baubericht gelegt und **zeichengleich**:
`datei.vorlagen.einheiten`, `widerspruch.8.lang`, `reihe.2.offen.0`,
`reihe.2.umrechnung.0.begruendung`, `reihe.13.offen.0`, `reihe.13.offen.1`,
`reihe.13.umrechnung.0.beleg`, `reihe.15.offen.0`.

Die Zerlegung des dritten Teils, die der Kommentar zusaetzlich behauptet — „viermal
`offen`, einmal `begruendung`, einmal `lang`" — habe ich nach demselben Verfahren
gezaehlt (letzter Pfadteil, der keine Listennummer ist): `Counter({'offen': 4, 'lang': 1,
'begruendung': 1})`. 4 + 1 + 1 = 6. Stimmt.

Auch die beiden Nebenaussagen des Satzes nachgeschlagen statt geglaubt:
`reihe[13]["nr"] == 14`, die Liste `reihe` hat 19 Eintraege und zaehlt ab null — „der
erste Umrechnungsblock der Reihe 14" ist richtig, und `reihe[13]["umrechnung"]` hat
genau **einen** Block, „der erste" ist also nicht bloss der erste von mehreren. Die
Tabelle `[datei.vorlagen]` steht tatsaechlich unmittelbar unter dem Kommentar (Z. 165),
`einheiten` in Z. 170. `[datei.vorlagen]` fuehrt fuenf Schluessel, wie der Kopf des
Kommentars sagt.

**Bezugsstand und Einzelnachweis, die Bedingung 5 zusaetzlich verlangt:** Der Baubericht
nennt die Commit-Kennung (`37cce4d`) — von mir gegen `git ls-tree` geprueft — und listet
die acht Fundstellen einzeln. Ich konnte deshalb nachrechnen statt vergleichen; die
Uebereinstimmung ist das Ergebnis, nicht die Methode.

### Die Falle, die der Kommentar nicht stellt

`grep -c einheitenbefund-pwt-baci` ergibt **12**, nicht 8. Vier der zwoelf stehen in
Kommentarzeilen (Z. 31, 58, 103 und Z. 141 — der Kommentar zitiert seine eigene
Zeichenfolge), die uebrigen acht in Wertzeilen (Z. 170, 375, 599, 608, 1388, 1389, 1401,
1522) und decken sich eins zu eins mit den acht Blattwerten oben. Der Kommentar sagt
ausdruecklich „Blattwerte" und nicht „Zeilen", er ist also richtig; wer ihn mit `grep`
statt mit einem Parser nachzaehlt, kommt auf 12 und haelt ihn faelschlich fuer falsch.
Das ist kein Befund, aber die Stelle, an der die naechste Nachzaehlung kippen wird.

## Bedingung 6 — keine uebernommene Zahl

**Erfuellt.** Die Bedingung verlangt nicht, dass die Zahlen von denen des Befunds
abweichen — bei acht Fundstellen ist Uebereinstimmung der einzig moegliche richtige
Ausgang —, sondern dass der Baubericht sagt, woher **seine** stammen, falls sie sich
treffen. Er tut das, und zwar pruefbar:

- Er gibt die Zaehlregel zeichengenau an und die **acht Fundstellen einzeln**. Der
  Prueffbefund der Runde 1 nennt dieselben acht (er gibt sein Skript aus) — die
  Pruefbarkeit haengt aber an den Adressen, und die habe ich unabhaengig erzeugt.
- Er nennt eine Zerlegung, **die im Befund der Runde 1 nicht vorkommt**: die 4 / 1 / 1
  des dritten Teils. Nachgeschlagen — der Befund schreibt dort nur „sechs unter `offen`,
  `begruendung` und `lang`", ohne Aufteilung. Eine Zahl, die man abschreibt, kann man
  nicht verfeinern; die 4 / 1 / 1 ist der Nachweis einer eigenen Zaehlung.
- Der Befund der Runde 1 nennt **kein** Zahlwort, das im Kommentar neu steht und dort
  nicht auch gezaehlt waere. Die Zahlen der Bedingungen 1 bis 3 aus der Paketdatei
  (27, 0, 20, 11) sind in diesem Lauf nicht angefasst worden — der Diff zeigt es.

## Bedingung 4 — unabhaengig nachgemessen, obwohl sie im Ruecklauf schon als richtig galt

Der Ruecklauf sagt, die zwei Zahlwoerter seien richtig; das Abnahmefeld nimmt aber nur
die Bedingungen 1 bis 3 von der erneuten Pruefung aus. Ich habe deshalb beide selbst
gezaehlt und mich **nicht** auf meinen eigenen Befund von Runde 1 gestuetzt:

| Angabe im Kommentar | von mir gezaehlt |
|---|---|
| als `beleg` **genau einmal** | 1 (`reihe.13.umrechnung.0.beleg`) — aus dem Lauf oben |
| die Vorlage hat **zwei Pakete** lang gefehlt | 2 |

Die zweite an drei Git-Fassungen gezogen (`git show <ref>:<datei>`) und darin gesucht:

| Fassung | `beleg = "daten/einheitenbefund-pwt-baci…"` | Schluessel `einheiten` in `[datei.vorlagen]` |
|---|---|---|
| `ae6f605` (traegt die Aenderung des Pakets 0036) | Z. 1273 vorhanden | fehlt |
| `66a463b` (Paket 0047) | Z. 1305 vorhanden | fehlt |
| `58908fa` (traegt die Aenderung des Pakets 0049) | Z. 1334 vorhanden | Z. 136 vorhanden |

Die Luecke bestand also waehrend genau zwei Paketen, 0036 und 0047. Gegenprobe an
`datei.nachgezogen_durch`: zwischen `0036-…` und `0049-…` steht genau ein Eintrag,
`0047-…`. Beide Wege ergeben zwei.

## Die Selbstmessungen — neu gezaehlt, keine gekippt

Sechs Kommentarzeilen einzufuegen kann eine zeilenbasierte Selbstmessung aus
`[pruefweg]` verschieben. Neu gezaehlt gegen die vorliegende Fassung:

`[=] [0-9]+\.[0-9]` = **6** (`schnitt_1`) · `'{3}` = **29** Zeilen (`schnitt_2`) ·
`^\[\[` = **113** (`schnitt_3`) · `^nr = ` = **28** · `^t37_klasse = ` = **20**
(`schnitt_4`) · `^sollreihen = ` = **21** (`schnitt_5`) · `^wortlaut = ` = **20**
(`schnitt_7`). **Alle unveraendert.** Insbesondere `schnitt_1` bleibt bei 6: die neue
Formel `1 + 1 + 6 = 8` traegt keine Dezimalstelle, und die neuen Zeilen beginnen mit
`# `, treffen die `^`-verankerten Muster also nicht.

`pruefweg.toml_geprueft` ist bewusst nicht fortgeschrieben. **Das ist richtig, und ich
habe es gegen die eigene Aussage des Feldes geprueft:** Es bilanziert Blattwerte gegen
`4eb20ac`, dieser Lauf aendert keinen Blattwert, die Bilanz bleibt also wahr. Der Satz
„das Paket hat ausserdem fuenf Kommentar**stellen** geaendert" bleibt ebenfalls wahr —
der Kommentar ueber `[datei.vorlagen]` ist zweimal geaendert worden, aber es ist
dieselbe Stelle. Ein Nachtrag haette den einzigen Blattwert des Laufs erzeugt und die
Aussage „null verschiedene Werte" zerstoert, mit der der Bericht die Unberuehrtheit der
Bedingungen 1 bis 3 belegt. Damit ist das Feld auch in diesem Lauf **stabil unter dem
eigenen Schreibvorgang** geblieben — die Eigenschaft, an der es dreimal gescheitert war.

## Zu den Unsicherheiten des Bauberichts

- **Der Umfang der Reparatur.** Der Ruecklauf sagte „eine Aenderung an einem Wort", der
  Bauagent hat den ganzen Satz ersetzt. **Keine Ruecknahme.** Seine Begruendung habe ich
  nicht gelesen, sondern selbst nachgerechnet: Haette er nur „sieben" durch „sechs"
  ersetzt, stuende dort „acht Blattwerte, `datei.vorlagen.einheiten` mitgezaehlt; die
  uebrigen sechs stehen unter `offen`, `begruendung` und `lang`" — und unter der Lesart,
  die „mitgezaehlt" nahelegt (uebrig nach Abzug des Vorlagenschluessels), waeren es
  sieben, nicht sechs. Der Einwortweg haette den Fehler also nur auf die andere Lesart
  verschoben. Bedingung 5 verlangt eine Aufteilung, deren Teile sich zur Gesamtzahl
  summieren; genau das leistet erst die dreigliedrige Fassung. Der groessere Eingriff war
  der einzige, der die Bedingung erfuellt.
- **Die Formel `1 + 1 + 6 = 8` als erste Rechnung in einem Kommentar dieser Datei.** Ich
  habe nach einer Konvention gesucht, die das verbietet, und keine gefunden: Der Kopf der
  Datei (Leseregeln 1 bis 5) sagt nichts ueber Rechnungen in Kommentaren, `[pruefweg]`
  auch nicht. Wo `specs/` und die Datei schweigen, ist die Entscheidung des Bauagenten
  gueltig — das ist Geschmack und kein Befund. Die Rechnung ist ausserdem der Grund,
  warum Bedingung 5 maschinell pruefbar ist statt nur behauptet.

## Grenzen des Pakets eingehalten

Der Diff beruehrt genau eine Datei und darin genau einen Kommentar. Keine Quellensuche,
keine Codeaenderung, kein `technik.md`, kein `deckungsbefund-1997.md`. Reihe 9 ist in
diesem Lauf nicht angefasst worden. Einheiten, Basisjahre, Luecken, Lizenzen und
Namensnennung sind unberuehrt — **kein Blattwert hat sich geaendert**, das ist eine
gepruefte Nullaussage und kein Eindruck.

## Wonach ich gesucht und nichts gefunden habe

Damit diese Nullaussagen von einer nicht stattgefundenen Pruefung zu unterscheiden sind:

- eine **neunte** Fundstelle der Zeichenfolge in einem Blattwert (`tomllib` ueber alle
  1214 Blaetter, nicht ueber die acht vorgezeigten);
- ein Blatt, das in **zwei** der drei Teile faellt, oder eines, das aus allen dreien
  herausfaellt (paarweise Schnitte leer, Vereinigung gleich der Gesamtmenge);
- eine **weitere** Zahl im geaenderten Kommentar, die niemand nachgezaehlt hat: die
  Zahlwoerter des ganzen Kommentarblocks (Z. 126–164) einzeln geprueft — fuenf Vorlagen,
  zwei Pakete, genau einmal, acht, eins/eins/sechs, viermal/einmal/einmal, `1 + 1 + 6 = 8`,
  dazu „vier Pakete" und „viermal" als ausdruecklich historische, als falsch bezeichnete
  Angaben. Keine ohne Deckung;
- eine Selbstmessung in `[pruefweg]`, die durch die sechs neuen Kommentarzeilen kippt
  (sieben Muster neu gezaehlt, alle unveraendert);
- eine Aenderung an einem Blattwert, die sich hinter dem Kommentareingriff versteckt
  (Diff auf Zeilenebene: alle zehn beruehrten Zeilen beginnen mit `# `);
- eine Aenderung ausserhalb von `reihen.toml` (`git diff --stat 37cce4d HEAD` auf die
  Datei, `git status` auf `ventures/`);
- eine Zahl im Kommentar, die nur im Prueffbefund der Runde 1 steht und nirgends
  gezaehlt ist (Herkunft je Zahl oben).

## Was offen bleibt und nicht diesem Paket gehoert

`technik.md` fuehrt Reihe 9 an Z. 1441 und in der T37-Klassentabelle Z. 2112 weiter als
Sollreihe der Klasse `gesetzt`. Der Widerspruch ist in `reihen.toml` unter Nr. 5
gemeldet, der Vorschlag `0068` liegt vor und gehoert dem Architekten. Unveraendert
gegenueber Runde 1, kein neuer Vorschlag noetig.
