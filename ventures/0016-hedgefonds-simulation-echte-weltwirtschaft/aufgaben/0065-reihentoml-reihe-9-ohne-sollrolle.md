---
id: 0065-reihentoml-reihe-9-ohne-sollrolle
rolle: datenbauer
status: gebaut
haengt_an: [0054-partielaenge-r-entscheiden]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme" plus die vierte im Annahmevermerk vom 2026-09-04.
---

# Reihe 9 ist seit dem 2026-09-03 keine Sollreihe — `reihen.toml` führt sie an elf Stellen weiter als eine

Vorschlag des `entwurf-pruefer` vom 2026-09-04, aufgefallen bei der Prüfung von Paket
`0054-partielaenge-r-entscheiden`.

## Der Sachverhalt

Paket 0054 hat entschieden: **Reihe 9 (Leitzins) verliert ihre Sollrolle und behält Start und
Politikpfad.** Die Sollreihenzahl fällt damit von 31 auf **27**, die T37-Klasse `gesetzt`
entfällt ersatzlos, und an ihre Stelle tritt für den Leitzins eine **Invariante** statt eines
Fehlermaßes (`spiel.md` Z. 133-136 und Z. 1629-1637; Urteil `geprueft` vom 2026-09-04).

Der Spielentwerfer durfte `reihen.toml` nicht anfassen und hat sie deshalb benannt
(`spiel.md` Z. 2056-2061) — aber nur mit **zwei** Schlüsseln: `t37_klasse` und
`rolle_tabelle` der Reihe 9. Die Datei führt die alte Lage an **elf** Stellen:

| # | Fundstelle | was dort steht | was daraus wird |
|---:|---|---|---|
| 1 | `[zaehlung]` Z. 153 | `sollreihen_gesamt = 31` | **27** |
| 2 | `[zaehlung]` Z. 155 | `sollreihen_gesetzt = 4` | **0** — die Klasse entfällt |
| 3 | `[zaehlung]` Z. 158 | `gesetzt_zerlegung = "Reihe 9 (4)"` | leer, mit Grund im Kommentar |
| 4 | `[zaehlung]` Z. 160 | `probe = "23 + 4 + 4 = 31"` | `"23 + 4 = 27"` |
| 5 | `[zaehlung]` Z. 161 | `beleg`: „Die **31** Sollreihen verteilen sich auf die Reihen 1, 2, 8, **9**, 10 und 11" | **27**, Reihen 1, 2, 8, 10 und 11 |
| 6 | `[zaehlung.handelsblock]` Z. 170 | Schlüsselname `in_den_31_enthalten` | der Name trägt die Zahl mit; `in_den_sollreihen_enthalten` löst das dauerhaft |
| 7 | `[zaehlung.lizenz]` Z. 184, 187, 190 | Kommentar „Lizenzstand der **31** Sollreihen"; `sollreihen_unklar = 24`; `unklar_zerlegung = "Reihe 1 (4) + Reihe 2 (12) + **Reihe 9 (4)** + Reihe 11 (4) = 24"` | 27; **20**; ohne Reihe 9 |
| 8 | `[zaehlung.lizenz]` Z. 192 | `gegenrechnung`: „frei 0, **unklar 31**, gesperrt 0" | **unklar 27** |
| 9 | `[[reihe]] nr = 9` Z. 900, 908 | `rolle = ["start", "politikpfad", "soll"]`; `sollreihen = 4` | ohne `"soll"`; **0** |
| 10 | `[[reihe]] nr = 9` Z. 921 | `offen`: „An ihm haengen **15 der 31** Sollreihen und 7 der 16 Pruefgegenstaende" | neu abzuzählen; die 7 der 16 sind von der Entscheidung **nicht** betroffen (Reihe 9 war keiner der 16) |
| 11 | `[[widerspruch]] nr = 5` Z. 289 | `entscheidet = "Spielentwerfer -- Reihe streichen oder Quelle ersetzen"` | **entschieden am 2026-09-03**: Sollrolle gestrichen, Quelle für den Pfad bleibt offen und geht an den Datenbauer |

Genannt sind davon Z. 898 und Z. 909 — also der Kopf von Nr. 9, nicht seine Zählfelder und
keine einzige Stelle im `[zaehlung]`-Block.

**Warum das mehr ist als Buchhaltung:** Der Kommentar über `[zaehlung]` (Z. 147-149) macht
die Datei zu einer prüfbaren Behauptung — *„Wer diese Datei prueft, addiert `sollreihen` ueber
alle `[[reihe]]` und vergleicht mit `sollreihen_gesamt`."* Diese Probe geht heute auf, weil
beide Seiten falsch sind. Zieht jemand nur eine Seite nach, schlägt sie fehl; zieht niemand
sie nach, bestätigt eine Selbstmessung dauerhaft die alte Lage. Beides ist schlechter als der
Zustand vor der Selbstmessung, und genau deshalb ist sie eingebaut worden.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Erstens ist es die andere Hälfte einer Übergabe.** 0054 durfte `reihen.toml` nur benennen
(seine Grenzen: „Fällt die Wahl auf einen Weg, der eine Reihe ersetzt, ist das ein Folgepaket
für ihn — benennen, nicht selbst tun"). Die Benennung ist erfolgt, sie ist unvollständig, und
vervollständigen kann sie nur, wer die Datei aufmachen darf.

**Zweitens ist es nicht die Beschaffungsfrage, und die beiden dürfen nicht zusammenfallen.**
`spiel.md` Z. 1871-1890 gibt dem Datenbauer eine zweite, größere Aufgabe: **woher der
Leitzinspfad für Deutschland und China kommt**, und ob ein einheitlicher Zinsbegriff über
vier Länder erreichbar ist. Das ist Recherche an Quellen mit offenem Ausgang. Dieses Paket
hier ist eine Nachziehung mit bekanntem Ziel. Zusammengelegt hinge die kleine, sichere
Arbeit an der großen, unsicheren — und `[zaehlung]` bliebe so lange falsch, wie die
Quellensuche dauert.

**Drittens ist es kein Duplikat der laufenden `reihen.toml`-Pakete.** 0049, 0057 und 0062
betreffen Herkunft, Belegstellen, Selbstmessung und Rückstandsverweise; keines nennt Reihe 9
oder die Zahl 31 als Gegenstand. Der einzige Berührungspunkt ist `[[widerspruch]] Nr. 5`,
dessen `entscheidet`-Feld 0062 bereits anfasst — das ist eine Dateikollision und gehört
serialisiert, nicht zusammengelegt.

## Abnahme

1. **Keine der elf Stellen führt Reihe 9 mehr als Sollreihe**, und der Prüfer zählt es nach
   statt es zu vergleichen: `sollreihen` über alle `[[reihe]]` addiert ergibt
   `sollreihen_gesamt`, und `sollreihen_frei + sollreihen_abgeleitet` ergibt dieselbe Zahl.
   `sollreihen_frei = 23` und `sollreihen_abgeleitet = 4` bleiben **unverändert** — wer sie
   mitwandern lässt, hat die Entscheidung falsch gelesen.
2. **Die 16 Prüfgegenstände und die Toleranz 2 in `[zaehlung.pruefgegenstaende]` bleiben
   unangetastet**, mit einem Satz im Kommentar, warum: Reihe 9 war nach T37 `gesetzt` und
   kam in keinem der sechzehn vor. Diese Zahl ist die einzige, die der Schnitt nicht bewegt,
   und ihr Stehenbleiben muss begründet sein statt bloß beobachtbar.
3. **`[[widerspruch]] Nr. 5` sagt, was entschieden ist und was offen bleibt**: Sollrolle
   gestrichen (Entscheidung des Spielentwerfers vom 2026-09-03, Paket 0054), Quelle für den
   **Pfad** weiter offen und beim Datenbauer. Ein Widerspruch, der als „entscheidet:
   Spielentwerfer" stehen bleibt, nachdem der entschieden hat, ist eine falsche Fährte für
   den nächsten Lauf.

## Grenzen

- Keine Quellensuche und keine Codeänderung an Reihe 9 — das ist das andere Folgepaket.
  Reihe 9 behält `quelle_eingebettet`, `codes` und ihre Deckungseinträge unverändert.
- `deckung_urteil` der Reihe 9 („reisst -- DEU und CHN tragen ... keinen einzigen Wert, USA
  endet 2020") bleibt wörtlich stehen: Es ist eine Messung und bleibt richtig, auch wenn die
  Reihe keine Sollreihe mehr ist.
- `daten/deckungsbefund-1997.md` behält Namen und Inhalt. Er hat das Fenster 1997 gemessen,
  und das bleibt richtig.
- Keine Datei außer `reihen.toml`. Widersprüche zu `technik.md` werden gemeldet — dort läuft
  der Nachzug als eigenes Paket.

---

## ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, **mit einer vierten Bedingung**

**Die vier Prüfungen meiner Rolle:**

- **Rolle:** `datenbauer` steht in `BAUROLLEN` (`baulauf.py:59`) und hat mit `daten-pruefer`
  einen Prüfer (`baulauf.py:68`). ✓
- **Dateischnitt:** `reihen.toml` beansprucht sonst nur 0047, 0049, 0057 und 0062 — alle vier
  `fertig`, 0062 mit diesem Lauf. Kein offenes Paket hält sie, und die Prüfung gegen `gebaut`
  (die `startbereit()` nicht macht, `baulauf.py:270-281`) fällt ebenfalls leer aus: 0011 hält
  `technik.md`, 0027 fünf Dateien unter `kern/`. ✓
- **Abnahme:** prüfbar, und Bedingung 1 ist die stärkste Form davon — der Prüfer **rechnet
  nach** (Summe über alle `[[reihe]]` gegen `sollreihen_gesamt`), statt gegen die Tabelle im
  Paket zu vergleichen. Bedingung 2 verlangt für die einzige Zahl, die sich *nicht* bewegt,
  eine Begründung; das ist richtig so, weil sonst Stehenbleiben und Übersehen dieselbe Spur
  hinterlassen. ✓
- **Abhängigkeit:** 0054 ist mit diesem Lauf `fertig`. Das Paket ist startbereit. ✓

**Vierte Bedingung, aus dem Prüfbefund zu 0062 übergeben.** Der `daten-pruefer` hat dort
einen Rest aus seiner eigenen Prüfung zu 0049 stehen sehen und ausdrücklich gesagt, er gehöre
*„an das nächste Paket, das den Kopf von `reihen.toml` ohnehin öffnet"*. Das bist du:

4. **Der Kommentar über `[datei.vorlagen]` sagt, was gezählt wurde, und die Zahlen stimmen.**
   Er trägt heute zwei Zahlwörter, die der Prüfer für falsch hält — die Angabe, wie oft die
   Vorlage als `beleg` auftritt, und die Angabe, wie viele Pakete lang sie gefehlt hat.
   **Zähle beide in der Datei nach und schreibe das Gezählte hin**, statt eine der beiden
   Fassungen zu übernehmen; kommst du auf die alte Zahl, bleibt sie stehen und du sagst, was
   du gezählt hast. Den Wortlaut gebe ich nicht vor — 0028 → 0042 → 0053 ist die Kette, an
   der ein vorgeschriebener Halbsatz zweimal ungeprüft in die Datei gewandert ist.

Damit sind es **vier** Bedingungen, und das Feld `abnahme` im Kopf nennt sie so. Die
Dateiliste ändert sich dadurch nicht.

**Was ich nicht entscheide:** die elf Fundstellen. Der Vorschlagende hat sie einzeln
aufgeführt, Bedingung 1 verlangt vom Prüfer die eigene Summe statt den Vergleich mit dieser
Liste. Findest du eine zwölfte oder eine der elf falsch beschrieben, ist das ein Befund gegen
den Vorschlag und kein Rücklauf gegen dich — nenne sie und begründe sie.

## Rückläufe

0.

---

## GEBAUT — 2026-09-04, Datenbauer

Eine Datei geaendert: `daten/reihen.toml`. **Vergleichsstand fuer jede Zahl dieses
Berichts ist der Commit `4eb20ac`** (`git ls-tree` dort: Blob
`7a83aef58053050b77ae502c27b9aba24e97f77d`); die Datei war beim Aufschlagen unveraendert
gegenueber diesem Commit, `git status` fuehrte sie nicht. sha256 vorher
`fd3cace0…`, nachher `661b13c4…`.

**Bilanz:** +84/−30 in **18 Hunks**. Alle achtzehn liegen in den Bereichen, die dieses
Paket nennt: `[datei]` (Z. 119, 130 der Altfassung), `[zaehlung]` samt Untertabellen
(Z. 153–192), `[[widerspruch]]` Nr. 5 (Z. 288), Reihe 9 (Z. 900–921) und `[pruefweg]`
(Z. 1662–1676). Kein Hunk ausserhalb.

**Alles maschinell gemessen**, nicht gelesen: `python3`/`tomllib`, beide Baeume flach
gezogen, Blattschluessel als Pfadtupel; jede Ersetzung mit erwarteter Trefferzahl, die
bei Abweichung abbricht. Aufgesetzt wurde auf einer Kopie in `$TMPDIR`, gemessen dort,
erst dann kopiert.

### Die Bilanz der Blattwerte

| gegen `4eb20ac` | gemessen |
|---|---|
| Blattwerte Bezugsstand | **1214** |
| Blattwerte vorliegende Fassung | **1214** |
| gemeinsame Schluessel | 1212 |
| neue Schluessel | **2** — `datei.nachgezogen_durch.7`, `zaehlung.handelsblock.in_den_sollreihen_enthalten` |
| weggefallene Schluessel | **2** — `reihe.8.rolle.2` (der Eintrag `soll` der Reihe 9), `zaehlung.handelsblock.in_den_31_enthalten` |
| verschiedene gemeinsame Werte | **20** |

Die gleiche Gesamtzahl ist hier eine Falle und deshalb aufgezaehlt statt summiert: zwei
Schluessel kommen, zwei gehen. Die zwanzig einzeln: `zaehlung.sollreihen_gesamt`,
`zaehlung.sollreihen_gesetzt`, `zaehlung.gesetzt_zerlegung`, `zaehlung.probe`,
`zaehlung.beleg`, `zaehlung.lizenz.sollreihen_unklar`,
`zaehlung.lizenz.unklar_zerlegung`, `zaehlung.lizenz.gegenrechnung`,
`reihe.8.sollreihen`, `reihe.8.t37_klasse`, `reihe.8.offen.0`, `reihe.8.offen.1`,
`widerspruch.4.entscheidet`, `widerspruch.4.in_dieser_datei`, `pruefweg.schnitt_5`,
`pruefweg.zaehlregel_sollreihen`, `pruefweg.zaehlregel_t37`, `pruefweg.handelsblock`,
`pruefweg.falle`, `pruefweg.toml_geprueft`. Genau diese Bilanz steht auch im Feld
`pruefweg.toml_geprueft`.

**Kommentare sind keine Blattwerte** und tauchen in dieser Bilanz nicht auf. Fuenf
Kommentarstellen sind geaendert: ueber `[datei.vorlagen]`, ueber
`[zaehlung.handelsblock]`, ueber `[zaehlung.pruefgegenstaende]`, neu ueber
`gesetzt_zerlegung` und neu ueber `sollreihen` im Block der Reihe 9. Das steht auch im
Feld, weil eine Blattwertbilanz sonst mehr Vollstaendigkeit behauptet, als sie hat.
