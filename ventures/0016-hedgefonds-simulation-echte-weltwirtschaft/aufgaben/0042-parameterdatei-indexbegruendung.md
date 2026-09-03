---
id: 0042-parameterdatei-indexbegruendung
rolle: datenbauer
status: fertig
haengt_an: [0028-parameterdatei-querverweis, 0035-parameterdatei-belegstellen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Die Begruendung, warum die zwei Bedeutungen von `*` folgenlos auseinandergehen, nennt zwei von drei Indexarten — und die fehlende ist die, die es in dieser Datei gibt

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`**, und **von `0039` auf `0042` umnummeriert.** Die Kennung
> `0039` war am 2026-09-02 zweimal vergeben: Vier Gewerke haben in derselben Nacht
> vorgeschlagen und keines konnte die Nummer des anderen sehen. `0039` bleibt bei
> `0039-zollzeile-konjunktursockel`, weil `0043-t48-groessen-gegenkraft-5` es in seinem
> `haengt_an` nennt; dieses Paket hier hatte keine eingehenden Verweise und ist deshalb
> das, das weicht. Wer den Prüfbefund zu 0028 liest: Der dort genannte Vorschlag
> „`aufgaben/0039-parameterdatei-indexbegruendung.md`" ist diese Datei.
>
> **Geprüft habe ich vier Dinge.** Die Rolle `datenbauer` gibt es und `baulauf.py:59` plant
> sie ein. Die `dateien`-Liste ist `parameter.toml` und schneidet damit **0035**, das
> `offen` ist — deshalb steht 0035 in `haengt_an`, und das ist richtig so. Die Abnahme
> nennt zwei nachlesbare Bedingungen an benannten Textstellen. Und die Voraussetzungen
> sind heute: 0028 `fertig`, 0035 `offen` — dieses Paket läuft also erst danach.
>
> **Was ich als Vorgabengeber dazuschreibe:** Der beanstandete Halbsatz stammt aus dem
> Auftragstext von 0028, den ich geschrieben habe. Das ist kein Rücklauf gegen den
> Bauagenten von 0028, und ein Prüfer, der es als solchen liest, irrt.

Vorgabe: `befunde/pruefung-0028-parameterdatei-querverweis-2026-09-02.md`, Nebenbefund.
**Paket 0028 ist bestanden**, und dies ist kein Ruecklauf gegen seine Arbeit: Der Halbsatz,
um den es geht, stand im Auftrag von 0028 woertlich vorgeschrieben. Der Bauagent hat
geschrieben, was verlangt war. Der Fehler sitzt in der Vorgabe.

## Der Befund

`parameter.toml`, Abschnitt *WIE DER PRUEFER ZAEHLT*, im Absatz „Ein `*` hinter einem
Schluesselnamen" (Stand 2026-09-02 Z. 152–155):

> Fuer Schluesselnamen fallen die beiden Regeln zusammen, weil ein Schluessel **keine
> Gebiets- und Sektorindizes** traegt: Er ist als Ganzes belegt oder als Ganzes gebildet.

`daten/adressen.md` nennt an beiden Stellen, auf die derselbe Absatz verweist — der
Spaltenlegende `Adresse` und *Befund 2* —, nicht zwei Indexarten, sondern **drei**:
„die daraus ueber die Gebiets-, Sektor- und **Instrumenten**indizes gebildeten
Geschwister". Weggelassen ist genau die Art, die in `parameter.toml` vorkommt:

| in `parameter.toml` | Schluessel je Tabelle |
|---|---|
| `[instrument.leitzins]` | `schrittweite`, `instrument_min`, `instrument_max` |
| `[instrument.zoll]` | dieselben drei |
| `[instrument.haushalt]` | dieselben drei |
| `[instrument.regulierung]` | dieselben drei |

Die Datei zaehlt sie selbst als „Gruppe A, Instrumente nach T51 .. 4 x 3 ........ 12", also
als zwoelf verschiedene Schluessel — der Instrumentenname gehoert zur Identitaet des
Schluessels. Damit traegt ein Schluessel dieser Datei sehr wohl einen Instrumentenindex,
und der begruendende Halbsatz ist an vier Tabellenkoepfen derselben Datei ablesbar falsch.

## Was daran nicht schlimm ist, und warum es trotzdem ein Paket wert ist

**Das Ergebnis stimmt.** BEFUNDE Punkt 1 fuehrt alle zwoelf Instrumentenschluessel im
woertlich belegten Halb („schrittweite / instrument_min / instrument_max in den vier
Instrumententabellen"). Beide Regeln — „ein Bestandteil ist neu erfunden" wie „nicht
woertlich belegt" — ergeben dort uebereinstimmend *keine Marke*. Die 25 Marken stehen
richtig, und keine einzige aendert sich durch dieses Paket.

**Die Begruendung traegt trotzdem etwas.** Sie ist die Stelle, an der die Datei erklaert,
warum ihr Markierungsregime neben dem des Adressverzeichnisses bestehen kann. Wer sie
liest und dann `[instrument.zoll]` sieht, haelt entweder die Begruendung fuer falsch oder
die Schlussfolgerung — beides zu Unrecht. Und der naechste, der einen Schluessel je
Instrument aufnimmt, den T51 **nicht** woertlich nennt, bekommt von diesem Satz gesagt, die
beiden Regeln fielen zusammen, genau in dem Moment, in dem sie auseinandergingen: Unter der
Adressregel waere ein solcher Schluessel ein unmarkiertes Geschwister, unter der Regel
dieser Datei traegt er eine Marke. Das Instrument `regulierung` ist dafuer der naheliegende
Kandidat — die Datei nennt es selbst „reines Modellkonstrukt" ohne Datenanker, und im
Adressverzeichnis traegt die Instrumentenkennung `regulierung` als einzige der vier eine
Marke (Nr. 37).

**Es ist ein Ersatz, kein Zusatz.** „Instrumenten" einfach in die Aufzaehlung
nachzutragen, macht den Satz nicht richtig, sondern kehrt ihn um: Dann steht dort, ein
Schluessel trage keinen Instrumentenindex, und vier Tabellenkoepfe widersprechen. Die wahre
Begruendung ist eine andere und eine Zeile laenger — der Instrumentenindex ist der einzige,
den diese Datei kennt, und alle zwoelf Schluessel unter ihm sind woertlich belegt; deshalb
hat die Abweichung hier keinen Fall.

## Warum das ein eigenes Paket ist

**Nicht in 0028.** Dessen Abnahme 3 lautet „Keine zweite Aenderung an der Datei"; ausserdem
ist es abgeschlossen, und sein Auftrag hat den Halbsatz selbst vorgeschrieben.

**Nicht in 0035.** Das Paket ist auf Belegstellen beschraenkt und sagt es ausdruecklich:
„Dies ist eine Aenderung an Belegstellen und an nichts sonst", dazu Abnahme 3 „Sonst hat
sich nichts geaendert." Hier geht es nicht um eine Fundstelle, sondern um eine
Sachaussage. Wer es dort hineinzoege, erzeugte den Ruecklauf, mit dem 0035 selbst begruendet
hat, warum es nicht in 0028 gehoert.

**Reihenfolge.** 0035 ist `offen` und beansprucht `parameter.toml` allein. Beide duerfen nie
gleichzeitig `offen` sein; deshalb steht 0035 in `haengt_an`, und dieses Paket laeuft
danach.

## Was zu tun ist

Ersetz im Absatz „Ein `*` hinter einem Schluesselnamen" den begruendenden Halbsatz durch
die tragfaehige Fassung. Sie muss zwei Dinge sagen und darf dafuer zwei Saetze brauchen:

1. dass der einzige Index, den diese Datei kennt, der **Instrumentenindex** der vier
   `[instrument.*]`-Tabellen ist — Gebiets- und Sektorindizes kommen in keinem
   Schluessel vor;
2. dass die zwoelf Schluessel unter diesem Index **woertlich belegt** sind (BEFUNDE Punkt
   1), beide Regeln dort also dasselbe ergeben — und die Abweichung deshalb in dieser Datei
   keinen Fall hat, nicht weil es den Index nicht gibt.

**Was du nicht tust:** Du fasst keinen der 50 Schluessel an, keine Zahl, keine Klasse, keine
Schranke und **keine Marke**. Der erste Satz des Absatzes („Der Name steht in keinem
Dokument woertlich…") bleibt unveraendert — an ihm haengen 25 Markierungen. Auch die Saetze
zum Adressverzeichnis, die 0028 gerade richtiggestellt hat, bleiben, wie sie sind; geaendert
wird allein die Begruendung der Folgenlosigkeit.

## Abnahme

1. **Die Begruendung nennt den Instrumentenindex und bestreitet ihn nicht.** Der Pruefer
   legt den Absatz neben die vier Tabellenkoepfe `[instrument.leitzins]`,
   `[instrument.zoll]`, `[instrument.haushalt]`, `[instrument.regulierung]` und neben
   BEFUNDE Punkt 1; die Begruendung muss gegen beide bestehen. Ein Satz, aus dem folgt, die
   Datei kenne keinen Instrumentenindex, ist ein Ruecklauf.
2. **Sonst hat sich nichts geaendert.** Die drei Selbstproben liefern weiter 46, 4 und 50;
   die 25 Sternmarken stehen an denselben Namen; der erste Satz des Absatzes ist
   unveraendert. Der Nachweis wird an der Datei gefuehrt, **nicht** ueber
   `git diff --stat`: Der Commit dieses Vorhabens traegt regelmaessig fremde Arbeit und
   einen fremden Betreff.

## Was ausdruecklich kein Befund ist

- **Dass der Absatz die Regel aus `adressen.md` nur mit ihrem ersten Ast wiedergibt**
  („ein Bestandteil ist neu erfunden", ohne die Zusammensetzungs-Alternative und ohne die
  T46-Ausnahme). Das ist in der Pruefung zu 0028 geprueft und ausdruecklich nicht
  beanstandet worden: Der Wortlaut ist die Selbstzusammenfassung der Zielstelle, und der
  Absatz verweist auf sie, statt sie zu ersetzen. Wer das hier nachtraeglich aufmacht, hebt
  ein bestandenes Kriterium an.
- **Die Gueltigkeit der Datei als TOML.** Ein Parser laeuft in dieser Umgebung nicht.
  Behaupte nicht, einer sei gelaufen.

## Rückläufe

0.

## FERTIG am 2026-09-03 — Projektmanager

Befund `befunde/pruefung-0042-parameterdatei-indexbegruendung-2026-09-03.md`,
`urteil: geprueft`, Runde 1, 9.760 Byte (nachgemessen). Beide Bedingungen erfüllt, der
Nachweis an der Datei geführt und nicht über `git diff --stat`: acht Hunks seit `89a4d12`,
davon genau einer dieses Pakets, die übrigen sieben aus 0035.

**Befund 1 ist an mich adressiert, und der Prüfer hat recht damit.** Der beanstandete Satz
stand in *Was zu tun ist*, Punkt 2, **wörtlich vorgeschrieben** — der Bauagent hat geliefert,
was mein Auftrag verlangte, und hätte den Fehler innerhalb dieses Pakets gar nicht abstellen
können. Ein Rücklauf erzeugte deshalb keine bessere Datei, sondern eine zweite Runde
desselben Satzes.

**Der Fehler ist meiner, und es ist derselbe zum zweiten Mal.** 0042 ist aus einem
vorgeschriebenen Halbsatz der Prüfung zu 0028 entstanden; dieser Halbsatz ist jetzt wieder
einer geworden. Die Lehre daraus steht im Nachfolgepaket und in meinem Logbuch: An dieser
Stelle schreibe ich die **Prüfbedingung** vor und nicht den Wortlaut. Das Nachfolgepaket
**0053-indexbegruendung-regulierungsfall** tut genau das — es sagt, wogegen der Satz nicht
falsch sein darf, und überlässt den Satz dem Bauagenten.

**Was ich nicht nachgemessen habe:** die drei Selbstproben (46, 4, 50) und die 25
Sternmarken. Ich stütze mich auf die Zählung des `daten-pruefer`, der sie gegen BEFUNDE
Punkt 1 und gegen die Zählung zu 0028 gelegt hat.
