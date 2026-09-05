---
id: 0035-parameterdatei-belegstellen
rolle: datenbauer
status: fertig
haengt_an: [0009-parameterdatei-schluessel, 0028-parameterdatei-querverweis]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Sieben Belegstellen in `parameter.toml` zeigen auf die falsche Zeile, eine auf eine Frage, die es nicht mehr gibt

Vorgabe: `befunde/pruefung-0009-parameterdatei-schluessel-runde3-2026-09-02.md`,
Nebenbefunde 1 und 2. **Paket 0009 ist bestanden**; dies ist kein Rücklauf und kein Befund
gegen seine Arbeit. Zum Zeitpunkt, an dem die Verweise geschrieben wurden, stimmte jeder —
nachgesehen an den historischen Fassungen.

## Der Befund

### (a) Vier Zitate, sieben Fundstellen, alle mit toter Zeilennummer

| in `parameter.toml` | Verweis | stand bei `f0cae94` | steht heute |
|---|---|---|---:|
| Zeile 673 | spiel.md Aktion 4 („Aufschlag, der mit der Sichtbarkeit … steigt") | 177–178 | 183–184 |
| Zeile 674 | spiel.md Kanal 4 („Aufschlag steigt mit Sichtbarkeit") | 524 | 530 |
| Zeile 675 | technik.md T5 Klasse 3 („±2 Mio %") | 124 | 241 |
| Zeilen 762, 806, 829, 848 | technik.md T5 Klasse 10 („höchstens ein Schritt je Runde" = eine Stufe) | 155–156 | 272–273 |

Ursache sind zwei Commits desselben Tages, beide **nach** dem Bau um 05:47: `e068e1a`
(„spielentwerfer", 19:13) an `spiel.md` und `b4526dc` („architekt: 0011-stack-auf-cpp",
20:05) an `technik.md`. Der Versatz ist je Datei einheitlich, aber zwischen den Dateien
verschieden — +6 in `spiel.md`, +117 in `technik.md`. Eine pauschale Addition über alle
sieben Fundstellen geht also daneben, und die nächste Änderung an einer der beiden Dateien
verschiebt sie erneut.

**Der Inhalt jedes Zitats ist weiterhin richtig** — alle vier wurden in der heutigen
Fassung im Wortlaut wiedergefunden. Falsch sind allein die Nummern.

### (b) Ein Verweis auf eine Frage, die aus dem Rückstand verschwunden ist

`parameter.toml` Zeile 22–25 sagt über die fünf geparkten Klasse-4-Schlüssel:

> Ob Klasse 4 ihren Deckel von 10.000 auch fuer einen Regler traegt, entscheidet nicht
> diese Datei, sondern eine Zeile in T5; **die Frage steht in `rueckstand.md` als Vorlage
> an den Geschaeftsfuehrer.**

Der letzte Halbsatz war richtig — bei `f0cae94` stand sie dort als Punkt 4 („Unverändert
offen"). In `rueckstand.md` Fassung 10 (`73bbab8`, 19:45) steht sie nicht mehr, und der
Abschnitt „Was der Geschäftsführer entscheiden lassen muss" nennt die Rohdaten
ausdrücklich als „jetzt der einzige Punkt". Wer dem Verweis folgt, findet nichts.

Das ist die teure Sorte: Die fünf Schlüssel sind **wegen** dieser Frage geparkt. Zeigt der
Verweis ins Leere, sieht der nächste Leser eine unbegründete Auslassung statt einer
bewusst offenen Stelle — und beantwortet sie womöglich selbst, was eine Abweichung von T5
ohne ADR wäre.

## Warum das ein eigenes Paket ist

**Es gehört keinem bestehenden.** 0009 hat sein Kriterium erfüllt und darf dafür nicht
zurückgerufen werden; die Ursache liegt in zwei Paketen, die an `spiel.md` und
`technik.md` arbeiten durften und richtig gearbeitet haben.

**Es darf nicht in 0028.** 0028 arbeitet an derselben Datei, aber seine Abnahme 3 lautet
„Keine zweite Änderung an der Datei. Der Prüfer legt `git diff` an; was hier nicht steht,
ist ein Rücklauf." Wer diese Arbeit dort hineinzieht, erzeugt genau den Rücklauf, den das
Kriterium androht. Deshalb ein eigenes Paket **nach** 0028 — beide beanspruchen
`parameter.toml`, sie dürfen nie gleichzeitig offen sein.

**Es ist die Bauartänderung, nicht das Nachziehen.** Die Nummern jetzt einmal zu
korrigieren hält bis zum nächsten Commit des Architekten, und 0011 läuft noch, 0026 hängt
daran. Wer nur addiert, schreibt die nächste Ungültigkeit selbst. Es ist derselbe Auftrag
wie in **`0034-belegstellen-ohne-zeilennummern`** für `daten/adressen.md`, nur in der
anderen Datei; die beiden kollidieren nicht. (Die Kennung 0034 ist doppelt vergeben —
`0034-reihentoml-baci-einheit-nachziehen` stammt aus einem parallelen Lauf. Meine 0035 war
bei der Wahl frei; kollidiert sie doch, räumt der Projektmanager auf.)

## Was zu tun ist

1. Ersetze jeden Verweis der Form „Zeile N" auf `spiel.md` oder `technik.md` durch einen,
   der ohne Zeilennummer trägt: **Tabellennummer beziehungsweise Abschnittsname** (T5
   Klasse 3, T5 Klasse 10, spiel.md Aktion 4, spiel.md Kanal 4) **plus das Zitat im
   Wortlaut**, an dem die Stelle wiederzufinden ist. Die Nummer darf zusätzlich
   stehenbleiben, wenn sie ein Abrufdatum trägt — tragend ist sie dann nicht mehr.
2. Ersetze in Zeile 22–25 den Halbsatz „die Frage steht in `rueckstand.md` als Vorlage an
   den Geschaeftsfuehrer" durch **die Frage selbst**, in einem Satz und an Ort und Stelle:
   Trägt T5 Klasse 4 („0 bis 10.000") ihren Deckel auch für einen Regler, oder nur für die
   Grösse, die er stellt? Dazu, dass sie offen ist und dass die fünf Schlüssel bis zu ihrer
   Beantwortung unverändert bleiben. **Verweis auf eine Punktnummer in `rueckstand.md`
   nicht erneuern** — die Datei wird je Lauf neu geschrieben und trägt keine stabile
   Nummerierung.

**Was du nicht tust:** Du fasst keinen der 50 Schlüssel an, keine Zahl, keine Schranke,
keine Klasse und keine Marke. Insbesondere **beantwortest du die Klasse-4-Frage nicht** und
rührst die fünf geparkten Schlüssel nicht an. Dies ist eine Änderung an Belegstellen und
an nichts sonst.

## Abnahme

1. **Kein Verweis der Datei nach `specs/` hängt mehr tragend an einer Zeilennummer.** Der
   Prüfer sucht jede der vier Fundstellen über Tabellennummer und Zitat in der heutigen
   Fassung von `spiel.md` und `technik.md` und findet jede, ohne zu zählen.
2. **Der Verweis auf `rueckstand.md` ist durch die Frage selbst ersetzt**, die Frage ist als
   offen benannt und **nicht beantwortet**, und die fünf Schlüssel `preisstoss`,
   `zustimmung_elastizitaet`, `nachahmer_wirkung`, `hebel_max`,
   `innerjahresausschlag_faktor` sind unverändert.
3. **Sonst hat sich nichts geändert.** Die drei Selbstproben liefern weiter 46, 4 und 50;
   die acht Bedingungen unter BEFUNDE Punkt 5 (a) stehen unverändert da; alle 50 Werte,
   Klassen und Schranken sind dieselben. Der Nachweis wird an der Datei geführt, **nicht**
   über `git diff --stat`: Der Commit dieses Vorhabens trägt regelmässig fremde Arbeit und
   einen fremden Betreff.

## Was ausdrücklich kein Befund ist

- **Die Gültigkeit der Datei als TOML.** `python3` ist den Rollen als Kommando gesperrt —
  in drei Prüfrunden nachgewiesen, zuletzt daran, dass auch `python3 --version` abgewiesen
  wird. Der Parser gehört in den Runner. Behaupte nicht, einer sei gelaufen.
- **Dass die fünf Klasse-4-Schlüssel weiter `>= 0` ohne obere Schranke tragen.** Das ist
  Gegenstand der offenen Frage und nicht dieses Pakets.

## Angenommen — 2026-09-02, Projektmanager

`vorschlag` → `offen`, **unverändert im Auftrag.** Die vier Prüffragen: `datenbauer`
existiert und wird eingeplant; die Abnahme ist an der Datei prüfbar; die Kollision auf
`parameter.toml` mit 0028 hat der Vorschlag selbst erkannt und über `haengt_an` gelöst,
bevor ich sie gesucht habe. Die zweite Abhängigkeit, 0009, ist in diesem Lauf `fertig`
geworden — 0028 ist damit startbereit, dieses Paket wartet auf dessen Abnahme.

**Die Kennung `0035` bleibt.** Sie war zeitgleich ein zweites Mal vergeben; das andere
Paket heisst jetzt `0037-startbelegung-riegel-je-schreibzugriff` und ist in 0027
zusammengefasst. Der Absatz oben, der die Doppelvergabe von `0034` beschreibt und mir das
Aufräumen überlässt, ist damit erledigt: Aus dem fremden `0034` wurde
`0036-reihentoml-baci-einheit-nachziehen`.

**Was ich bestätige, weil der Vorschlag es sich selbst verboten hat und das richtig ist:**
Die Klasse-4-Frage wird hier **nicht** beantwortet. Sie ist der Grund, warum die fünf
Schlüssel geparkt sind; wer sie nebenbei entscheidet, weicht ohne ADR von T5 ab. Der
Auftrag lautet, den toten Verweis durch die Frage selbst zu ersetzen — und keine
Punktnummer in `rueckstand.md` zu erneuern, weil die Datei je Lauf neu geschrieben wird und
keine stabile Nummerierung trägt. Das ist zutreffend, und es ist meine eigene Datei.

## Gebaut — 2026-09-03, Datenbauer

Sechs Hunks in `parameter.toml`, alle in Kommentarzeilen, 51 eingefügt und 13 gelöscht.
Die 13 gelöschten sind genau die sieben Fundstellen mit Zeilennummer und der Halbsatz
auf `rueckstand.md`; keine Schlüsselzeile ist im Diff.

**Zu (a).** Die vier Zitate stehen jetzt mit Abschnittsname beziehungsweise
Tabellennummer und dem Wortlaut da. Jede ist in der heutigen Fassung ohne Zählen
gefunden worden:

| Verweis neu | gesucht mit | gefunden |
|---|---|---:|
| spiel.md, Abschnitt „Die Aktionen", Nummer 4 (**Hebel**) | „Kreditaufnahme zum Leitzins des Landes plus einem Aufschlag" | spiel.md 183 |
| spiel.md, Kanaltabelle im Abschnitt „Warum die Größe des Zustands keine Verteidigung ist", Tabellenzeile `\| 4 \|`, Spalte „Dämpfung" | „Hebelobergrenze, Aufschlag steigt mit Sichtbarkeit" | spiel.md 530 |
| technik.md T5, Tabellenzeile `\| 3 \|` (Raten), Spalte „Bereich" | „Basispunkte (1 bp = 0,01 %)" | technik.md 241 |
| technik.md T5, Erläuterung zu Klasse 10, Aufzählungspunkt „**Instrumentenstufe (10).**" | „heisst dort **eine Stufe**" | technik.md 269–273 |

Die vierte Fundstelle ist dabei **nicht** die T5-Tabellenzeile, sondern der
Erläuterungspunkt darunter; der alte Verweis „T5 Klasse 10 Zeile 155-156" ließ das
offen. Vier Fundstellen tragen ihn (der Gruppenkopf der Schrittweite und die drei
Instrumententabellen Leitzins, Zoll, Haushalt).

Zwei Zugaben, beide Bauart und keine Zahl: eine Regel im Kopf, **wie** diese Datei nach
`specs/` verweist, samt der gemessenen Ursache (+6 in `spiel.md`, +117 in `technik.md`,
je Datei einheitlich und zwischen den Dateien verschieden) — und der Hinweis, dass die
Datei durchgängig ohne Umlaute schreibt, `specs/` aber nicht. Der Hinweis ist nicht
kosmetisch: Das Zitat „hoechstens ein Schritt je Runde" steht in `technik.md` mit
Umlaut, und ohne den Hinweis führt eine wörtliche Suche danach ins Leere. Jede der vier
Belegstellen nennt deshalb zusätzlich einen umlautfreien Teil des Zitats.

**Zu (b).** Der Halbsatz auf `rueckstand.md` ist durch die Frage im Wortlaut ersetzt:
*Trägt T5 Klasse 4 („0 bis 10.000") ihren Deckel auch für einen Regler, oder nur für die
Größe, die er stellt?* Sie ist als **offen** markiert und nicht beantwortet; daneben
steht, dass die fünf Schlüssel bis zu ihrer Beantwortung unverändert bleiben. Eine
Punktnummer in `rueckstand.md` ist nicht erneuert, und **warum** sie es nicht ist, steht
an Ort und Stelle. Der Dateiname `rueckstand.md` kommt noch einmal vor — in dem Satz,
der sagt, dass dort bis Paket 0035 ein Verweis stand und dass er ins Leere zeigte. Das
ist die Erklärung der Auslassung, kein Verweis, dem jemand folgen soll.

**Zu Abnahme 3.** An der Datei nachgewiesen, nicht über `git diff --stat`:

- `grep -c '^[a-z_0-9]* *=.*PLATZHALTER'` → **46**
- `grep -c '^[a-z_0-9]* *=.*FEST (T51)'` → **4**
- `grep -cE '^[a-z_0-9]+ *='` → **50**
- `grep -n 'Zeile [0-9]'` → **nichts**
- Umlaute in der Datei: **null**, wie vorher.

Die fünf geparkten Schlüssel `preisstoss`, `zustimmung_elastizitaet`,
`nachahmer_wirkung`, `hebel_max`, `innerjahresausschlag_faktor` sind unberührt; die
Klasse-4-Frage ist nicht beantwortet.

**Nebenbefund, als eigenes Paket vorgeschlagen:**
`0044-schranken-probe-belegstellen`. `kern/test/schranken_probe.cpp` nennt sechsmal eine
Zeilennummer in `parameter.toml` (304, 205, 250 für `druck_max`, `stufen_max`,
`aufschlag`; heute 336, 237, 282) — dieselbe Bauart in der Gegenrichtung. Drei der sechs
sind `fprintf`-Zeilen und drucken die falsche Nummer in den Übersetzungsbefund. Die
Nummern waren schon vor diesem Lauf um 8 verschoben (Paket 0028); mein Lauf hat 24
weitere hinzugefügt. Die Datei gehört dem Testentwickler; ich habe sie nicht angefasst.

## Rückläufe

0.

## FERTIG am 2026-09-03 — Projektmanager

Befund `befunde/pruefung-0035-parameterdatei-belegstellen-2026-09-03.md`,
`urteil: geprueft`, Runde 1, 125 Zeilen (nachgemessen).

**Zwei Dinge aus dem Befund, die keine Befunde sind und trotzdem hierher gehören.**
Erstens: Der Prüfer hat die Verschiebung nachgerechnet, die dieser Lauf in
`schranken_probe.cpp` erzeugt hat, und bestätigt, dass die Zahlen von Paket **0044**
tragen. 0044 bleibt `offen` und wird startbereit, sobald 0027 abgenommen ist. Zweitens:
Ein Teil der 90 `specs/`-Verweise nennt nur eine Tabellennummer ohne Zitat. Der Prüfer hat
das gesehen, ausdrücklich **nicht** als Befund geführt und dazugeschrieben, ein Kriterium
anheben dürfe er nicht. Das ist richtig, und ich hebe es auch nicht nachträglich an: Das
Kriterium fragte nach Zeilennummern, und die halten ausnahmslos. Ich lege daraus **kein**
Folgepaket an — eine Tabellennummer ist ohne Zitat auffindbar, sie überlebt jeden Schnitt,
und der Aufwand stünde in keinem Verhältnis.
