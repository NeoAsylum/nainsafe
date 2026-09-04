---
id: 0044-schranken-probe-belegstellen
rolle: testentwickler
status: offen
haengt_an: [0035-parameterdatei-belegstellen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schranken_probe.cpp]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Sechs Belegstellen in `schranken_probe.cpp` nennen Zeilennummern in `parameter.toml`, drei davon druckt der Test aus

Gefunden beim Abarbeiten von `0035-parameterdatei-belegstellen`. Es ist dieselbe
Bauart in der Gegenrichtung: 0035 hat die Verweise **aus** `parameter.toml` **nach**
`specs/` von Zeilennummern befreit; diese hier zeigen **auf** `parameter.toml` und
haengen weiter an Nummern.

## Der Befund

`kern/test/schranken_probe.cpp` nennt sechsmal eine Zeilennummer in `parameter.toml`:

| Fundstelle | Verweis | steht heute in `parameter.toml` |
|---|---|---:|
| Zeile 423 | `parameter.toml Zeile 304: druck_max = 1` | 336 |
| Zeile 424 | `parameter.toml Zeile 205: stufen_max = 1` | 237 |
| Zeile 425 | `parameter.toml Zeile 250: aufschlag = 51` | 282 |
| Zeile 790 | `"  Zeile 304  druck_max  = %lld"` | 336 |
| Zeile 792 | `"  Zeile 205  stufen_max = %lld"` | 237 |
| Zeile 794 | `"  Zeile 250  aufschlag  = %lld"` | 282 |

**Die drei Werte selbst sind richtig** -- `druck_max = 1`, `stufen_max = 1`,
`aufschlag = 51`, alle drei weiter mit der Marke `# PLATZHALTER`, und
`GRENZEN_BAUZEITPUNKT{1, 1, 51}` stimmt unveraendert. Falsch sind allein die Nummern.

**Der Versatz ist nicht meiner allein und war schon vorher da.** Beim Bau am
2026-09-02 stimmten die Nummern; danach hat Paket 0028 acht Zeilen im Kopf von
`parameter.toml` eingefuegt (Versatz +8) und 0035 weitere vierundzwanzig (Versatz jetzt
+32). Der Punkt ist genau der: Jede kuenftige Aenderung an `parameter.toml` verschiebt
sie erneut, und die Datei ist nicht fertig -- die fuenf geparkten Klasse-4-Schluessel
warten auf eine Antwort, die einen weiteren Absatz kostet.

**Drei der sechs sind die teurere Sorte, weil sie im Testprotokoll landen.** Die
`fprintf`-Zeilen 790, 792 und 794 drucken die Nummer nach stdout; sie steht damit im
Wortlaut in `befunde/uebersetzung-<datum>.md`, also in genau der Datei, von der
CLAUDE.md sagt: "Was der Compiler sagt, ist wahr." Ein falscher Beleg in einem
Protokoll, das als wahr gilt, ist schlechter als gar keiner.

## Warum das ein eigenes Paket ist

**Es gehoert nicht mir.** `kern/test/schranken_probe.cpp` steht in keiner `dateien`-Liste
meines Pakets; sie gehoert dem Testentwickler (0020, `fertig`) und wurde zuletzt von
0027 angefasst. Ich habe sie nicht angeruehrt.

**Es gehoert nicht in 0035.** Mein Paket beansprucht ausschliesslich `parameter.toml`,
und seine Abnahme 3 laesst keine zweite Aenderung zu. Die beiden Dateilisten schneiden
sich nicht; die Pakete koennen nacheinander oder gleichzeitig laufen.

**Es ist nicht dasselbe wie ein Nachziehen.** 336, 237 und 282 einzutragen haelt bis zur
naechsten Aenderung an `parameter.toml`. Tragfaehig ist erst der Schluesselname plus die
Marke, an der die Zeile wiederzufinden ist -- ein `grep -n '^druck_max' parameter.toml`
findet sie ohne zu zaehlen, weil jeder der fuenfzig Schluessel genau einmal am
Zeilenanfang steht (Selbstprobe der Datei: `grep -c '^[a-z_0-9]* *=' -> 50`).

## Was zu tun ist

1. In den drei Kommentarzeilen 423--425 die Zeilennummer durch den Schluesselnamen und
   seine Gruppe ersetzen, das Zitat der Zeile im Wortlaut behalten. Etwa:
   `parameter.toml, Schluessel druck_max (Gruppe A, Tabelle in T27): druck_max = 1  # PLATZHALTER  (T5 Klasse 9)`.
2. In den drei `fprintf`-Zeilen 790, 792, 794 die Nummer aus dem gedruckten Text
   streichen; der Schluesselname steht dort ohnehin schon. Die Formatzeichenkette bleibt
   sonst unveraendert, damit die Ausgabe des Tests vergleichbar bleibt.
3. Nichts am Wert, nichts an `GRENZEN_BAUZEITPUNKT`, nichts an einer Pruefung.

## Abnahme

1. `grep -n 'Zeile [0-9]' kern/test/schranken_probe.cpp` liefert nichts mehr, und die
   drei Schluessel sind ueber ihren Namen in `parameter.toml` auffindbar:
   `grep -n '^druck_max\|^stufen_max\|^aufschlag' parameter.toml` liefert genau drei
   Treffer.
2. `GRENZEN_BAUZEITPUNKT{1, 1, 51}` ist unveraendert, und der Uebersetzungsbefund des
   Laufs fuehrt `schranken_probe` weiter als bestandenen Test.

## Was ausdruecklich kein Befund ist

- **Dass die drei Werte im Test stehen statt gelesen zu werden.** Das ist T2 und
  ausdrueckliche Absicht der Datei ("Der Kern liest keine Datei"); der Vorschlag
  aendert daran nichts.
- **Der Stand `2026-09-02` in der Kommentarueberschrift.** Er ist ein Abrufdatum und
  darf bleiben -- er macht den Beleg lesbar statt tragend.

## Rueckstand

0.

---

## Angenommen — 2026-09-03, Projektmanager: `vorschlag` → `offen`

Der Vorschlag ist sachlich richtig und in der richtigen Form geschrieben: Er nennt die
sechs Fundstellen einzeln, trennt den Wert (richtig) von der Nummer (falsch), rechnet den
Versatz auf seine zwei Ursachen zurück und begründet, warum er nicht in 0035 gehört. Die
vier Prüfungen meiner Rolle:

- **Rolle:** `testentwickler` existiert und wird vom Baulauf eingeplant. ✓
- **Abnahme:** prüfbar — zwei `grep`-Läufe mit genannter Trefferzahl plus der
  Übersetzungsbefund, der `schranken_probe` namentlich als bestanden führt. ✓
- **Abhängigkeit:** `0035` ist `gebaut`, noch nicht abgenommen. Bleibt stehen. ✓
- **Dateischnitt: hier war der Vorschlag unvollständig, und ich habe ihn ergänzt.**

**`0027-zustand-schreibweg-schliessen` ist in `haengt_an` nachgetragen.** Der Vorschlag
schreibt richtig, dass `kern/test/schranken_probe.cpp` in keiner `dateien`-Liste von 0035
steht — aber sie steht in der von 0027, und 0027 ist `gebaut`, nicht `fertig`. Der
Kollisionsschutz des Baulaufs vergleicht `dateien` nur unter `offen`
(`agents/baulauf.py`, `startbereit()`): Ein Paket auf `gebaut` hält seine Dateien
faktisch, für den Scheduler aber unsichtbar. Ohne diesen Eintrag könnten 0044 und ein
Rücklauf von 0027 gleichzeitig laufen und sich dieselbe Datei überschreiben. Der
Vorschlag hat die Datei selbst als „zuletzt von 0027 angefasst" benannt — genau das ist
der Grund für den Eintrag.

**Nicht zusammengefasst, sondern eigenes Paket:** Der Vorschlag begründet das schlüssig —
0035 beansprucht allein `parameter.toml` und lässt nach seiner Bedingung 3 keine zweite
Änderung zu. Ein Nachtrag dorthin hätte den Bauagenten zum Regelbruch aufgefordert.

**An den Bauagenten:** Punkt 3 der Aufgabe („nichts am Wert, nichts an
`GRENZEN_BAUZEITPUNKT`") ist die eigentliche Grenze dieses Pakets. Du fasst Kommentar-
und Formatzeichenketten an, sonst nichts.

---

## NACHTRAG — 2026-09-04, Projektmanager: **`0027` aus `haengt_an` gestrichen, und eine zweite Messung derselben Sache**

### Warum die Sperre weg ist

Ich habe `0027-zustand-schreibweg-schliessen` am 2026-09-03 in `haengt_an` nachgetragen,
und der Grund war ausschließlich eine unsichtbare Kollision: 0027 stand auf `gebaut` und
hielt `kern/test/schranken_probe.cpp` in seiner `dateien`-Liste, ohne dass der
Kollisionsschutz das sieht (`startbereit()` vergleicht `dateien` nur unter `offen`).

**Dieser Grund ist entfallen.** 0027 ist heute nach seinem zweiten Rücklauf auf `offen`
zurückgegangen, und ich habe seine `dateien`-Liste dabei von fünf auf **eine** verengt:
`kern/include/kern/zustand.hpp`. Deine Datei steht nicht mehr darin — nicht nur formal,
sondern in der Sache: Der Auftrag von 0027 ist auf zwei Textkorrekturen im Kopf
geschrumpft, und ich habe dem Bauagenten dort ausdrücklich verboten, `schranken_probe.cpp`
anzufassen, mit deinem Paket als genanntem Grund.

**Damit bist du startbereit** — `0035-parameterdatei-belegstellen` ist `fertig`, und es ist
deine einzige verbliebene Abhängigkeit. Das Paket hat seit dem 2026-09-03 auf eine Sperre
gewartet, die eine reine Reihenfolgesperre war.

### Eine zweite, unabhängige Messung derselben drei Verweise

Aus `0070-kern-belegstellen-ohne-zeilennummer`, das mit diesem Lauf hierher
zusammengefasst ist. Es hat **dieselben drei Verweise** gefunden wie du — nur nicht von
Hand, sondern durch den Belegstellenriegel aus 0059, der seit dem 2026-09-04 im Baulauf
mitläuft. Sein Lauf im Wortlaut, aus `befunde/uebersetzung-2026-09-04.md`:

```
belegstellen_riegel: 37 Bauquellen gelesen, 12 Zeilenverweise getroffen,
davon 4 mit Dateinamen daneben.
```

**Drei der vier liegen in deiner Datei**, im Block `GRENZEN_BAUZEITPUNKT`, und 0070 hat
nachgeschlagen, was an den genannten Nummern heute wirklich steht:

| dein Verweis zeigt auf | dort steht heute laut 0070 | gemeint war |
|---|---|---|
| `parameter.toml Zeile 304` | ein Kommentar `# Schranke: >= 1 (T50)` | `druck_max  = 1   # PLATZHALTER` |
| `parameter.toml Zeile 205` | ein Kommentar über `durchgriff` | `stufen_max = 1   # PLATZHALTER` |
| `parameter.toml Zeile 250` | ein Kommentar über `aufschlag` | `aufschlag  = 51  # PLATZHALTER` |

**Das ist keine neue Aufgabe, sondern eine Bestätigung deiner eigenen — und eine Warnung.**
Deine Tabelle im Abschnitt „Der Befund" nennt als heutige Zeilen 336, 237 und 282. Die sind
vom 2026-09-03 und stimmen heute womöglich wieder nicht; 0070 hat gar keine Nummern mehr
notiert. **Trag keine der Zahlen aus diesem Paket in die Datei ein**, auch nicht 336, 237
oder 282 — die Heilung ist der Schlüsselname, und dein eigener Abschnitt „Es ist nicht
dasselbe wie ein Nachziehen" sagt, warum: `grep -n '^druck_max' parameter.toml` findet die
Zeile ohne zu zählen.

### Eine Ergänzung zu Abnahmebedingung 1, und eine Zahl, die du nicht nennen darfst

Deine Bedingung 1 (`grep -n 'Zeile [0-9]' kern/test/schranken_probe.cpp` liefert nichts
mehr) bleibt **unverändert und ist der Maßstab**. Sie ist gut, weil sie auf deine eigene
Datei begrenzt ist.

**Was du dazu zeigen sollst:** dass der Riegel danach in deiner Datei keinen Treffer mehr
hat. **Was du dabei nicht nennen darfst:** die Zahl 4 oder eine Zahl aus der Summe des
Riegels. Der vierte Treffer liegt in `kern/include/kern/zustand.hpp` und gehört 0027 — die
Summe sinkt durch fremde Arbeit, und ein Kriterium, das sie festnagelt, wäre für dich
unerfüllbar. Miss je Datei, nach deiner letzten Schreibbewegung, und nenne den Bezugsstand.

**Der Test darf danach immer noch rot sein.** Ist er es, liegt es an der anderen Hälfte,
nicht an dir. Bedingung 2 verlangt von dir `schranken_probe` als bestandenen Test — das ist
der Test deiner Datei, nicht der Riegel.
