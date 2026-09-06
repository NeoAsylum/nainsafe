---
typ: pruefung
paket: 0156-verlaufgroesse-auch-absolut-beschraenkt
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Bedingung 1 durch eigene Uebersetzung der drei Waende samt Gegenprobe ohne die neue Zusicherung, Bedingung 2 durch eigenes Nachmessen von RLIMIT_STACK, der Behaeltergroesse und der sieben Aufrufstellen, Bedingung 3 durch vier eigene Laeufe gegen einen selbst hergestellten Vorherstand.
befunde: 1
---

# Der gepruefte Stand

Gemessen am Arbeitsbaum, `kern/` unveraendert gegenueber der Ablage
(`git status --porcelain -- kern/` leer). Pruefsumme der einen Paketdatei zu Beginn und
am Ende dieses Laufs:

| Datei | md5 |
|---|---|
| `kern/include/kern/verlauf.hpp` | `a7da5d3e926e74548de1ef0f7a3a40f2` |

Alles Folgende laeuft in eigenen Baeumen unter `befunde/bau-pruefung-0156/`, ausgepackt
aus `git archive`:

* **`m0`** — der gepruefte Stand. `specs` und `decisions` sind mit ausgepackt, sonst
  faellt der Belegstellenriegel beim Konfigurieren aus.
* **`v0`** — derselbe Baum, in dem allein `verlauf.hpp` durch seine Fassung aus
  `9fd8c3f~1` ersetzt ist. Pruefsumme dort `b8adcc310ef3935f632565939c1703c2` — dieselbe,
  die die Pruefung zu 0144 als Stand `e0682a1` festgehalten hat, und ohne jedes Vorkommen
  von `STAPEL_JE_FADEN`. `diff -rq m0 v0` zeigt ausser den Bauverzeichnissen und zwei
  Befunddateien aus Parallellaeufen genau diese eine Abweichung.

Waehrend des Laufs haben zwei fremde Rollen committet (`e0a91ce`, `eaafdd0`); beide
tragen ausschliesslich `.md`-Befunde und keine Quelle.

# Bedingung 1 — der Bau wird rot, bevor der Behaelter unvertretbar gross wird

**Erfuellt, zweiseitig und mit Gegenprobe.**

Zuerst der heutige Wert, an der **unveraenderten** Kopfdatei und ohne fremdes Werkzeug:
eine eigene Uebersetzungseinheit gegen `m0/.../kern/include`, uebersetzt mit
`g++ -std=c++20 -Wall -Wextra -Werror`, Rueckgabe 0:

```
sizeof(Verlauf) 451784 sizeof(Kette) 17368 RUNDEN_KAPAZITAET 26 WAND 26 STAPEL 8388608
```

Dann die drei Faelle. Den Apparat dafuer (`befunde/messung-0156/schranke.py`) habe ich
vor dem Lauf Zeile fuer Zeile gelesen: Er kopiert den Kern in einen Wegwerfbaum, ersetzt
dort **genau** die Wandzeile — mit einem Riegel, der abbricht, wenn der Suchtext nicht
genau einmal vorkommt —, entfernt fuer die Gegenprobe **genau** den dritten
`static_assert` samt Meldung und uebersetzt danach den Kern samt `verlauf_probe` in
beiden Profilen. Er prueft bei Rot zusaetzlich, dass die Meldung die Stapelschranke nennt
und **nicht** die aus T40 — ohne diese zweite Bedingung waere nicht gezeigt, welche
Zusicherung gerissen ist. Der Apparat taugt; mein eigener Lauf, Rueckgabe 0:

| Wand | Zusicherung | Groesse des Behaelters | ON | OFF |
|---|---|---|---|---|
| 26 (heute) | vorhanden | 451.784 Byte | **gruen** | **gruen** |
| 482 (letzter darunter) | vorhanden | 8.375.240 Byte | **gruen** | **gruen** |
| 483 (erster darueber) | vorhanden | — | **rot** (Code 2) | **rot** (Code 2) |
| 483 | **entfernt** | 8.392.616 Byte | **gruen** | **gruen** |

Die Meldung im Wortlaut, aus meinem Lauf:

```
verlauf.hpp:253:31: error: static assertion failed: T19: ein Verlauf ist groesser als
der Stapel eines Fadens (8.388.608 Byte) und damit groesser, als ein Aufrufer ihn
tragen kann -- die Wand aus T40 oder die Kapazitaet je Runde wurde heraufgesetzt
```

Die vierte Zeile ist die tragende: Derselbe Fall 483 ist ohne die neue Zusicherung
**gruen**. Damit ist belegt, dass das Rot von ihr kommt und nicht von einer der beiden
aelteren — und zugleich, dass genau das der Zustand vor diesem Paket war.

Mein Lauf ist zeichengleich mit `befunde/messung-0156/lauf.txt` bis auf den Pfad des
Wegwerfbaums. Der Nachweis reproduziert also.

# Bedingung 2 — die Obergrenze ist begruendet, nicht gegriffen

**Erfuellt.** Die vier Behauptungen, auf die sich die Begruendung stuetzt, habe ich
einzeln nachgemessen statt sie zu lesen:

| Behauptung im Kopf | eigene Messung |
|---|---|
| `ulimit -s` meldet 8192 | 8192 |
| `getrlimit(RLIMIT_STACK)` meldet 8.388.608 Byte | `cur=8388608 max=-1` (eigenes Programm, `befunde/bau-pruefung-0156/rl.cpp`) |
| der Behaelter ist heute 451.784 Byte gross | 451.784, aus dem unveraenderten Kopf und aus `verlauf_probe` in beiden Profilen |
| jeder Aufrufer legt ihn oertlich an, `verlauf_probe` an sieben Stellen | genau sieben `Verlauf`-Griffe, alle im Funktionsrumpf (Zeilen 239, 321, 378, 409, 421, 435, 459); im ganzen Vorhaben sonst keiner |

Der Abstand steht daneben und stimmt: 451.784 von 8.388.608 sind 5,39 Prozent, also
tatsaechlich „gut ein Zwanzigstel".

**Die beiden zu weit gehenden Saetze.** Zeile 202 alt („Ein Verlauf gehoert damit nicht
beilaeufig auf einen Stapelrahmen") sagt jetzt „schon bei seiner heutigen Groesse … gut
ein Zwanzigstel" — eine Aussage ueber den gemessenen Ist-Zustand, oben nachgerechnet.
Zeile 72/73 alt nennt jetzt beide Regler, und fuer jeden von ihnen gibt es eine
Zusicherung: die Kapazitaet je Runde faengt der Riegel gegen `zustand::FELDER`, die
Kapazitaet ueber die Partie die T40-Zusicherung ab siebenundzwanzig, die Wand die neue ab
483. Der Satz bleibt der ungenaueste des Abschnitts — eine Wand von 60 gibt einen gruenen
Bau bei mehr als verdoppeltem Behaelter —, aber die Bedingung stellt es selbst so
(„**bevor** der Behaelter unvertretbar gross wird"), und der Kopf zieht die Grenze dieser
Lesart dreissig Zeilen weiter ausdruecklich („die Stelle, an der es **sicher** nicht mehr
geht, nicht die, an der es bequem bleibt"). Das deckt sich.

# Bedingung 3 — beide Profile, beide Bauwege, gegen einen Bezugsstand

**Erfuellt.** Konfigurieren, Bauen, ctest; jeder Lauf Rueckgabe 0:

| Bauweg | Profil | `m0` (geprueft) | `v0` (Bezugsstand) |
|---|---|---|---|
| Alleinbau `kern/` | ON | 12/12 | 12/12 |
| Alleinbau `kern/` | OFF | 12/12 | 12/12 |
| Arbeitsbereich | ON | 18/18 | 18/18 |
| Arbeitsbereich | OFF | 18/18 | 18/18 |

Der Bezugsstand ist selbst hergestellt, nicht zitiert: `v0` oben. Die Zahl der
ctest-Eintraege bleibt in jeder der vier Paarungen gleich — das Paket legt keine Probe an
und nimmt keine weg, wie seine Dateiliste es auch vorsieht.

# Wonach ich ausserdem gesucht habe

- **Ob die Schranke die Uebersetzung von der Maschine abhaengig macht.** Das waere der
  naheliegende Fehler an dieser Stelle gewesen: eine Zusicherung, die den Stapel beim
  Bauen *abfragt*, macht denselben Quelltext auf zwei Rechnern verschieden rot und
  zerstoert den Regressionstest. `STAPEL_JE_FADEN` ist ein Literal (`8192u * 1024u`),
  kein `getrlimit`, kein `#ifdef`, keine Umgebungsvariable. Die Uebersetzung ist damit
  reproduzierbar. Der Preis steht im Kopf: Wer sein `ulimit -s` heruntersetzt, bekommt
  trotzdem einen gruenen Bau — der Kopf nennt die Zahl als Voreinstellung von Linux und
  glibc und behauptet nichts anderes.
- **Determinismus im uebrigen.** Das Paket fuegt keine Zeile Laufzeitcode hinzu. Im
  geaenderten Bereich kein Gleitkomma, keine streuende Menge, kein Zeit- oder
  Adressbezug. `verlauf_probe` gibt aus beiden Bauprofilen dieselben Groessen aus
  (451784 / 17368 / 26 / 26).
- **Die Raender der Arithmetik.** `8192u * 1024u` ist 8.388.608 und bleibt im Bereich von
  `unsigned int`; beide Seiten der neuen Zusicherung sind `std::size_t`, es gibt keinen
  Vorzeichenwechsel und keine Division. Der Gleichheitsfall ist ausgeschlossen, aber nur
  zufaellig: `17376·N + 8 = 8.388.608` hat keine ganzzahlige Loesung (N = 482,77), sonst
  stuende in der Meldung „groesser", wo „gleich gross" richtig waere. Ein Ueberlauf von
  `RUNDEN_KAPAZITAET * sizeof(Kette)` ist kein Loch: Lange vorher weigert sich der
  Uebersetzer, den Typ ueberhaupt zu bilden, und das ist ebenfalls rot.
- **Ob die dritte Zusicherung die zweite verdeckt.** Sie tut es nicht. Die T40-Zusicherung
  reisst bei einer Kapazitaet oberhalb der Wand weiterhin ab siebenundzwanzig; die neue
  greift erst ab 483 und nur, wenn beide gemeinsam wachsen. Zwei Regler, zwei Schranken.
- **Ob die Wand noch woanders steht.** `PARTIELAENGE_HOECHSTENS` kommt in genau einem Kopf
  vor; `verlauf_probe` liest sie, statt eine eigene 26 zu schreiben. Unveraendert
  gegenueber der Feststellung aus der Pruefung zu 0144.
- **Rueckkopplungen und Zustandsausgabe** beruehrt dieses Paket nicht — es aendert einen
  Behaelter, der nichts rechnet und nichts ausgibt.
- **Die Meldung traegt „T19:"**, und T19 in `technik.md` sagt nichts ueber Stapel oder
  Speicher, sondern ueber die feste Aufnahmekapazitaet und das Verbot der stillen
  Kuerzung. Die Groessenfolge ist daraus hoechstens abgeleitet. `specs/` schreibt keine
  Form fuer Meldungstexte vor, und der Inhalt der Meldung ist richtig; deshalb ist das
  kein Befund, sondern eine Notiz fuer den, der die Zeile das naechste Mal anfasst.

# Der eine Befund: eine Bytezahl, die nicht reproduziert

**Zeile 87–89 nennt fuer die Wand 2169 eine Groesse, die es nicht gibt.** Der Kopf sagt:

> Gemessen am Stand `e0682a1` liefen Wand und Kapazitaet gemeinsam bis
> zweitausendeinhundertneunundsechzig gruen durch, bei 37.670.312 Byte.

Die Wand 2169 stimmt. Die Bytezahl nicht.

**So erzeugt man den Widerspruch.** Drei Punkte sind in diesem Lauf gemessen: 26 →
451.784, 482 → 8.375.240, 483 → 8.392.616. Zwei davon legen das Gesetz fest — die Stufe
je Runde ist (8.375.240 − 451.784) / (482 − 26) = 17.376 Byte, also
`sizeof(Verlauf) = 17.376·N + 8` —, der dritte bestaetigt es (17.376·483 + 8 = 8.392.616,
gemessen). Das ist auch die Bauform des Typs: eine `Kette` zu 17.368 Byte und eine `i64`
zu 8 Byte je Runde, dazu ein `std::size_t`. Eingesetzt:

| Wand | nach dem Gesetz | im Kopf |
|---|---|---|
| 2169 | **37.688.552** | 37.670.312 |
| 2170 | **37.705.928** | 37.687.688 (in der Pruefung zu 0144) |

Beide Zahlen sind um genau 18.240 zu klein, und 37.670.312 gehoert zu **keiner**
ganzzahligen Wand: (37.670.312 − 8) / 17.376 = 2167,95.

**Woher sie kommt.** Aus meiner eigenen Zunft: Die Tabelle unter „Der eine Befund" in
`befunde/pruefung-0144-rundenkapazitaet-des-verlaufs-nicht-an-r-2026-09-06.md` traegt
dieselben zwei Zahlen, und sie widersprechen dort schon den Zeilen 200 und 2.000
derselben Tabelle, die beide zum Gesetz passen. Das Paket 0156 hat sie uebernommen. Ein
Bauagent, der einen Pruefbefund abschreibt, tut das Richtige; der Fehler liegt an der
Quelle.

**Was daneben auffiel und der Berichtigung hilft:** Die Grenze 2169/2170 selbst ist echt
und hat einen benennbaren Grund, der in keinem der beiden Texte steht. Es ist die
T40-Zusicherung: `17.376·W + 8 < 17.368·(W + 1)` gilt genau fuer `8W < 17.360`, also fuer
W ≤ 2169. Die alte Schranke war damit nicht ganz ersatzlos entfallen — sie hielt noch,
nur eben erst bei 37,7 MB, und weil die Rundennummern (8 Byte je Runde) den Vorsprung
einer ganzen Kette langsam aufzehren. Das aendert an der Diagnose des Pakets nichts, es
benennt sie genauer.

**Warum das kein `zurueck` ist.** Keine der drei Bedingungen verlangt diese Zahl.
Bedingung 2 verlangt, dass die Obergrenze begruendet ist und die heutige Groesse
danebensteht — beides ist erfuellt und oben nachgemessen. Der Satz mit der falschen Zahl
begruendet, *warum* es die zweite Schranke braucht, und sein Punkt (ein Behaelter von
rund 37,7 MB, ohne dass sich eine Zusicherung ruehrte) traegt mit der richtigen Zahl
genauso. Ein Abnahmekriterium heraufzusetzen steht mir so wenig zu wie es zu senken.
Der Befund wird deshalb ein Vorschlag:
`0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen`.

# Was ich nicht geprueft habe

Das Logbuch des Bauagenten und `befunde/messung-0156/bericht.md` habe ich nicht gelesen.
Von `messung-0156` habe ich das Skript `schranke.py` gelesen und ausgefuehrt — als
Apparat, den ich vorher auf seine Riegel geprueft habe, nicht als Begruendung; `lauf.txt`
erst danach, zum Abgleich mit meinem eigenen Lauf.

Die Waende 2169 und 2170 konnte ich in dieser Umgebung **nicht** selbst uebersetzen: Das
Anlegen weiterer Kopfvarianten war mir hier verwehrt. Der Befund oben steht deshalb auf
drei gemessenen Punkten und der Bauform des Typs, nicht auf einer vierten Uebersetzung.
Wer die Zeile berichtigt, sollte die 2169 einmal wirklich uebersetzen — das Paket `0172`
verlangt es.
