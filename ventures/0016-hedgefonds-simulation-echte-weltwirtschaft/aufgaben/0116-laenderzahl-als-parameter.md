---
id: 0116-laenderzahl-als-parameter
rolle: architekt
status: fertig
haengt_an: [0051-t46-gebietspraefix-entscheiden]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen unter "Abnahme".
---

# NACHGEMESSEN UND GEMELDET — 2026-09-05, Architekt, fünfter Lauf

Auftrag war: prüfen und melden, nicht neu schreiben. Ich habe `technik.md` **nicht angefasst**;
diese Datei ist die einzige Änderung des Laufs. Vorgefundener Stand: `1f763e9`, 253.725 Byte,
`md5 cef37fc35f42acd0049e29176fa04d4f`, Arbeitsbaum sauber gegenüber dem Commit.

**Bedingung 1 — erfüllt.** T55 nennt für alle sechs Zahlen einen Ausdruck in `L`, `S`, `I`;
eingesetzt `L=4, S=3, I=4`, jede von Hand nachgerechnet:

| Zahl | Formel (T55) | Rechnung |
|---:|---|---|
| 310 | `L(4S+4I+16) + (L+1)L(S−1) + L(S+2) + 3LS + 5S + 23` | `176 + 40 + 20 + 36 + 38 = 310` |
| 175 | `L(4S+I+11) + (4S+10) + (L+1)L(S−1) + (S−1) + 3` | `108 + 22 + 40 + 2 + 3 = 175` |
| 135 | `L(3I+5) + L(S+2) + 3LS + 11` | `68 + 20 + 36 + 11 = 135` |
| 40 | `(L+1)·L·(S−1)` | `5·4·2 = 40` |
| 27 | `L·(S+4) − 1` | `4·7 − 1 = 27` |
| 20 | `L·(S+2)` | `4·5 = 20` |

Die Rechnung steht im Fliesstext daneben (`technik.md` Zeile 3332–3338). Gegengeprobt an den
Quellen statt am Abschnitt: `175 + 135 = 310` steht in T38 (Zeile 1366), `198 + 56 + 52 + 4 = 310`
in T15 (Zeile 1150), und `sollreihen_gesamt = 27` in `daten/reihen.toml` Zeile 266 — die
Summe der fünf `[[reihe]]`-Einträge mit `sollreihen > 0` ist `4 + 12 + 4 + 3 + 4 = 27`.
*Warnung an den Prüfer:* Eine Suche nach `^sollreihen` in dieser Datei findet sieben Treffer und
summiert auf 39. Die beiden zusätzlichen (Zeile 609 und 620, `4` und `8`) liegen in
`[[reihe.lizenzbeleg]]`-Untertabellen und zerlegen die 12 aus Reihe 2 noch einmal nach
Lizenzgruppe; sie sind keine eigenen Sollreihen.

**Bedingung 2 — erfüllt.** T56 wählt ausdrücklich die erste Möglichkeit — `Gebiet` und
`Steckplatz` bleiben namentliche Aufzählungen —, begründet sie mit vier nachgemessenen Punkten
und nennt `kern/include/kern/zustand.hpp` als die eine Stelle. Der Preis der Wahl und die
`static_assert`-Kette, die sie trägt, stehen dabei; der nötige Umzug von `GEBIET_KUERZEL` aus
`kern/src/zustand.cpp` in den Kopf ist als Kernbauer-Arbeit benannt und nicht ausgeführt.

**Bedingung 3 — dem Zweck nach erfüllt, dem Wortlaut nach nicht, und zwar unvermeidlich.**
`git diff --numstat 9e46cfa 1f763e9` zeigt **202 Zeilen zu, 0 ab**. Kein Bestandssatz ist
geändert oder entfernt worden. Gemessen mit `grep -c`:

| Muster | `9e46cfa` | `1f763e9` | davon im neuen Abschnitt 19 |
|---|---:|---:|---:|
| `310` | 41 | 43 | 2 (Zeile 3326, 3336) |
| `vier Länder` | 4 | 4 | 0 |

`vier Länder` ist unverändert. Bei `310` ist der Bestand ebenfalls unverändert — alle 41 alten
Treffer liegen vor Zeile 3271 und sind byte-identisch. Die beiden neuen sind die Formelzeile für
310 und ihre Nachrechnung, **also genau die zwei Zeilen, die Bedingung 1 verlangt**. Bedingung 1
und der Wortlaut von Bedingung 3 sind an dieser Stelle unvereinbar: Eine Formel für 310, deren
Ergebnis danebensteht, kann die Zeichenfolge `310` nicht vermeiden.

Der Zweck der Bedingung — *„Dieses Paket beschreibt, es ändert nicht"* — ist eingehalten und mit
`0 ab` schärfer belegt, als eine Trefferzahl es könnte. **Ich habe nichts nachgetragen und nichts
zurückgebaut**; eine Formel wegzulassen, um eine Zählung zu treffen, wäre der falsche der beiden
Fehler. Der Prüfer möge gegen `0 ab` und gegen die 41 unveränderten Bestandstreffer messen.

# GELIEFERT, ABER NICHT GEMELDET — 2026-09-05, Projektmanager, nachgemessen

**Der vierte Anlauf hat geliefert.** Der Vermerk darunter ist damit erledigt und steht nur
noch als Geschichte da. Gemessen:

- Commit `1f763e9`, 19:15, trägt **202 neue Zeilen** in `technik.md`. Die Datei ist von
  239.800 auf 253.725 Byte gewachsen; sie war seit 05:51 unverändert.
- Der neue Teil trägt die Überschriften `T54` bis `T57` und schließt mit einer Erklärung,
  was er nicht angefasst hat. Das ist der Zuschnitt dieses Pakets, Punkt für Punkt.

**Was fehlt, ist eine einzige Zeile: dein Status.** Er steht auf `offen`. Der Baulauf wird
dich deshalb erneut einplanen, obwohl die Arbeit im Baum liegt, und `startbereit()` hält
`technik.md` weiter für dich belegt — sieben andere Pakete warten darauf. Deine Rollendatei
lässt dich in `ventures/**/aufgaben/**` schreiben; du kannst ihn setzen, und beim
Nachbarpaket 0051 hast du es am selben Tag um 05:51 getan.

**`gebaut` setze ich nicht.** Das ist deine Meldung, nicht meine Abnahme, und ein Paket,
das ohne Prüfbefund weiterwandert, wäre mein Fehler.

**Dein Auftrag im nächsten Lauf ist deshalb ein kurzer.** Nicht neu schreiben: prüfen und
melden.

1. Die drei Bedingungen unten gegen den gelieferten Teil messen. Bedingung 3 misst du mit
   `grep -c` an dieser einen Datei gegen den Stand, den du beim Start vorfindest.
2. **Sind sie erfüllt:** `status: gebaut`, sonst nichts anfassen. Der `entwurf-pruefer`
   übernimmt.
3. **Fehlt etwas:** genau das nachtragen und dann `gebaut` setzen.
4. **Hält dich etwas auf:** hier hineinschreiben und in dein Logbuch, und nichts liefern.

# GEMESSEN — 2026-09-05, Projektmanager: dreimal zugewiesen, null Byte geliefert

**Das ist keine Zurückweisung.** Du hast keinen Rücklauf, und kein Prüfer hat etwas an dir
beanstandet. Es ist eine Messung, und sie steht hier, damit du nicht zum vierten Mal
dasselbe versuchst.

`0116` wurde am 2026-09-05 um 12:58, 13:58 und 15:01 zugewiesen. `technik.md` — deine
einzige Zieldatei — ist seit dem 2026-09-05 05:51 **byte-identisch** (239.800 Byte, gemessen
gegen `9e46cfa`). Drei Läufe, keine Änderung, kein Eintrag in `notizen/architekt.md`, kein
Bericht. Die Konvergenzbremse greift nicht: `baulauf.py:350` zählt Rückläufe, und ein Lauf,
der nichts liefert, erzeugt keinen.

**Was ich daraufhin geändert habe, und warum:**

1. **Das Paket war zu groß für einen Lauf.** Es verlangte vier Lieferungen auf der größten
   Datei des Vorhabens. Die Prüfliste ist heraus und steht in `0141`; übrig bleiben die
   Ableitungskette, die Identitätsfrage und die Abgrenzung.
2. **Bedingung 4 war nicht erfüllbar.** Sie verlangte einen Gesamtdiff, den du nicht
   kontrollierst. Ersetzt durch eine Messung an deiner eigenen Datei.

**Wenn dich etwas anderes aufhält als der Umfang** — die Dateigröße, ein Widerspruch in der
Vorgabe, eine Zahl, die du nicht belegen kannst —, dann liefere nichts und **schreib es in
dein Logbuch und in dieses Paket**. Ein gemeldetes Hindernis kostet einen Lauf; ein
stummer Lauf kostet ihn auch und hinterlässt nichts. Das ist die Wahl, um die es hier geht.

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, mit einer Sperre und einem Vorrang

Vier Prüfungen: **Rolle** `architekt` steht in `BAUROLLEN`, Prüfer ist der
`entwurf-pruefer`. **Abnahme** vier Bedingungen, jede an `technik.md` oder am `git diff`
messbar; Bedingung 1 nennt zwar sechs ausgeschriebene Zahlen, verlangt sie aber als
*Ergebnis einer Formel bei `L = 4`*, nicht als Trefferzahl aus einer Summe — die Regel, an
der hier zehn Kriterien gescheitert sind, ist nicht berührt. **Abhängigkeit** war keine
angegeben; ich trage eine ein. **Dateischnitt** ist der Grund für beides:

## `haengt_an: [0051]` ist eine Reihenfolgesperre, keine fachliche Abhängigkeit

Dieses Paket braucht von 0051 **nichts**. Die Sperre schützt 0051, nicht dieses Paket.

`0051-t46-gebietspraefix-entscheiden` steht auf `gebaut` und bekommt in diesem Durchgang
seinen Prüfplatz. Die Baustufe läuft vollständig **vor** der Prüfstufe
(`agents/baulauf.py:365` gegen `:377`) — wer in diesem Lauf `technik.md` anfasst, verändert
den Baum, an dem 0051 unmittelbar danach gemessen wird. Und 0051 wird an genau dieser Datei
gemessen: Bedingung 1 verlangt, *„der Prüfer zählt die Fundstellen vor und nach der Regel"*,
Bedingung 3 den **Änderungsdiff von `technik.md`**. Beide Nachweise sind wertlos, sobald ein
zweites Paket im selben Lauf dieselbe Datei umschreibt.

`startbereit()` fängt das nicht: Es vergleicht `dateien` nur unter den Paketen im Zustand
`offen` (`agents/baulauf.py:293-299`). Ein Paket auf `gebaut` ist unsichtbar, sein Anspruch
auf die Datei zählt nicht mehr. **Daran ist 0027 zweimal schuldlos gescheitert**, und es ist
der teuerste wiederkehrende Fehler dieses Rückstands. Die Sperre fällt, sobald 0051
`fertig` ist — nicht wenn sein Bauagent geliefert hat.

## Warum dieses Paket vor fünf älteren steht

`technik.md` ist die engste Stelle des ganzen Vorhabens: **sieben offene Pakete auf einer
Datei**, die strikt nacheinander laufen. `startbereit()` gibt den Platz an die kleinste
Kennung, also der Reihe nach an 0064, 0068, 0074, 0084, 0092 — dieses Paket käme als
sechstes, in rund sechs Durchgängen, und 0117 als siebtes.

Das wäre falsch. Der Betreiber hat 0116, 0117, 0118 und 0119 am 2026-09-05 **selbst
geschrieben und selbst eingestellt**; der Vorrang aus `ops/plan.md` stammt vom 2026-09-04
und ist vollständig abgearbeitet. Vier eigene Pakete an einem Tag sind die deutlichste
Vorrangaussage, die dieser Rückstand kennt. Dieses hier ist ihr Tor: 0117 hängt daran, 0118
hängt an 0117, und ohne die Ableitungskette bleibt „ein Land hinzufügen" das, was das Paket
beschreibt — ein Umbau mit offenem Ende.

Die fünf älteren rücken deshalb hinter 0117. Sie verlieren zwei Durchgänge, keiner von
ihnen trägt eine Abhängigkeit eines anderen Pakets, und keiner steht auf dem Weg zu einer
Zahl, nach der jemand gefragt hat. **Der Vermerk steht in jedem der fünf**, damit niemand
die Reihenfolge für einen Zufall der Nummerierung hält.

## Eine Anmerkung zu Bedingung 1, gemessen und nicht vermutet

Zwei der sechs Zahlen können sich noch bewegen: **27** (Sollreihen) und **20** (Steckplätze).
`0084-reihenliste-zeile-20-und-t53-selbstmessung` steht hinter dir in derselben Datei und
fasst die Reihenliste an; 0118 und 0119 heben die Steckplätze auf 45 beziehungsweise 75.
**Das ist kein Widerspruch, sondern der Grund für dieses Paket:** Schreib die Formel so, dass
die Zahl aus ihr folgt, und nicht die Formel so, dass sie die Zahl trifft. Wer nach dir die
Zahl ändert, muss dann nur den Parameter ändern. Der Vermerk dazu steht auch in 0084.

# Ein Land hinzufügen soll ein Vorgang sein, kein Umbau

**Anforderung des Betreibers, 2026-09-05.** Wörtlich: *„Was ich gerne hätte, wäre die
einfache Möglichkeit, Länder hinzuzufügen."*

Dieses Paket entscheidet **nichts** über die Zahl der Länder. Vier bleiben vier, und die
Begründung dafür (`spiel.md`, *Warum vier Länder und nicht drei*) steht nicht zur
Disposition. Es geht allein darum, ob ein fünftes Land später ein **Vorgang mit
bekannten Schritten** ist oder ein Umbau mit offenem Ende.

## Was schon trägt

Nachgemessen am 2026-09-05:

- `LAENDER = 4` und `GEBIETE = 5` sind je eine `constexpr` in `kern/zustand.hpp`. Die
  Adressbasen werden daraus **gerechnet** (`BASIS_RESTWELT = LAENDER * LAND_FELDER`) und
  von `static_assert` abgesichert. Die Arithmetik ist bereits parametrisch.
- `daten/reihen.toml` führt je Reihe eine `dimension`, und sie ist als `"4 + RW"`
  geschrieben — die Länderzahl ist dort schon eine Größe und keine Konstante.

## Was nicht trägt

- **Zwei Aufzählungen führen Länderidentität einzeln.** `enum class Gebiet` (US, CN, DE,
  BR, RW) und `enum class Steckplatz` mit zwanzig namentlichen Werten
  (`Sektor_US_1` … `Anleihe_BR`). Elf Stellen im Kern und neunzehn in den Tests nennen
  die Kürzel wörtlich.
- **Die abgeleiteten Zahlen stehen als Literale in `specs/`.** 310, 175, 135, 40 Ströme,
  27 Sollreihen, 20 Steckplätze. Wer ein Land hinzufügt, muss heute jede einzeln
  nachrechnen und in Prosa nachziehen; welche Zahl aus welcher Formel entsteht, ist
  nirgends an einer Stelle aufgeschrieben.

## Die eigentliche Schranke ist nicht der Code

Sie ist die Datenlage, und sie ist heute schon offen. `daten/reihen.toml` hält 19 Reihen;
mehrere tragen `unklar`, weil ihre Quelle Dritte nennt. Der Befund im Wortlaut: *„Von den
acht Stellen der vier Modellländer (je Amt und Notenbank) ist genau eine geprüft
(Destatis), sieben sind offen."*

**Ein fünftes Land bringt zwei weitere Stellen mit** und außerdem: drei WDI-Sektorreihen,
Bevölkerung, Erwerbstätige, Produktivität, Preisniveau, Leitzins, Wechselkurs,
Staatsschuld, Haushaltssaldo — jede mit Deckung über das Fenster ab 2001 — sowie eine
BACI-Handelszeile gegen jedes andere Gebiet. Der Leitzins ist der bekannte Problemfall:
Der eingebettete IWF-Code führt Deutschland und China schon heute nicht.

Deshalb ist die ehrliche Antwort auf die Anforderung **nicht** „wir machen es
konfigurierbar", sondern: *ein Land hinzufügen kostet einen benannten Datenaufwand, und
der Code soll nicht zusätzlich im Weg stehen.*

## Was zu tun ist

Du schreibst **keinen Code**. Du ergänzt `technik.md` um einen Abschnitt, der die
Länderzahl als Parameter behandelt:

1. **Die Ableitungskette.** Für jede heute als Literal geführte Zahl die Formel, aus der
   sie entsteht — 310, 175, 135, 40, 27, 20 — in Abhängigkeit von `L` (Länder), `S`
   (Sektoren), `I` (Instrumente). Die heutigen Werte müssen sich bei `L = 4` daraus
   ergeben.
2. **Die Identitätsfrage.** Ob `Gebiet` und `Steckplatz` namentliche Aufzählungen
   bleiben (dann: welche Datei ist die eine Stelle, an der ein Land eingetragen wird)
   oder durch Index plus Kürzeltabelle ersetzt werden. **Triff die Wahl und begründe
   sie**; beides ist vertretbar, offenlassen ist es nicht.
3. **Was ausdrücklich nicht mitwächst.** Der Fondsblock, die zwanzig Steckplätze und die
   Todesarten sind an Spielbalance gebunden, nicht an Ländergeometrie. Nenne, was bei
   `L = 5` **gleich bleibt** und warum.

**Was nicht dazugehört:** die Länderzahl ändern, ein fünftes Land auswählen, den Kern
umbauen. Das wären eigene Pakete.

**Die Prüfliste für ein neues Land ist seit dem 2026-09-05 nicht mehr Teil dieses Pakets.**
Sie steht in `0141-pruefliste-fuenftes-land` und hängt an diesem hier. Der Grund steht oben
im Vermerk vom 2026-09-05: Dieses Paket hat dreimal nichts geliefert, und die Prüfliste ist
der Teil, der sich ohne die Ableitungskette schreiben lässt.

## Abnahme

1. **Jede der sechs Zahlen hat eine Formel.** `technik.md` nennt für 310, 175, 135, 40,
   27 und 20 je einen Ausdruck in `L`, `S`, `I`. Einsetzen von `L = 4`, `S = 3`, `I = 4`
   liefert genau die heutigen Werte; die Rechnung steht daneben.
2. **Die Identitätsfrage ist entschieden.** Der Abschnitt nennt genau eine der beiden
   Möglichkeiten aus Punkt 2 als gewählt, mit Begründung, und benennt die Datei, in der
   ein neues Land einzutragen wäre.
3. **Der Bestand bleibt unberührt.** In `technik.md` stehen die Zahl 310 und die Aussage
   „vier Länder" nach deinem Lauf so oft wie davor. Gemessen wird an dieser einen Datei,
   mit `grep -c` gegen den Stand, den du beim Start vorgefunden hast. Dieses Paket
   beschreibt, es ändert nicht.

   *Vorher hieß diese Bedingung, `git diff` dürfe Änderungen ausschließlich in `technik.md`
   zeigen. Das war nicht erfüllbar und ist am 2026-09-05 ersetzt worden: Der Baulauf
   committet die ganze Schreibwurzel deiner Rolle, und im selben Lauf arbeiten andere
   Gewerke im selben Baum. Dein eigener Commit vom 15:01 trug sieben Dateien, von denen du
   keine geschrieben hast. Eine Bedingung über den Gesamtdiff misst deren Arbeit, nicht
   deine.*

## Rückläufe

0.
