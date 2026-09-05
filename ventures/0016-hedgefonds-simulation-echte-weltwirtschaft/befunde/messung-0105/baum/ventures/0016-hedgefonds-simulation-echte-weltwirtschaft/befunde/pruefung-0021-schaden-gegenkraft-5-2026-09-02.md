---
typ: pruefung
paket: 0021-schaden-gegenkraft-5
pruefer: entwurf-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Die sechs Bedingungen einzeln -- Bedingung 1 durch Einsetzen zweier Zustaende in zwei der vier Zeilen, Bedingung 2 durch Nachschlagen aller sechs Lesearten in daten/adressen.md, Bedingung 3 durch die Skalenklasse jedes Faktors aus T5/T49, Bedingung 4 durch Abgehen von Kanal 3 gegen T39 und T38, Bedingung 5 durch Herleitung zweier beliebig gezogener der 16 Adressen, Bedingung 6 gegen die drei Lesarten aus technik.md Abschnitt 12 und die Mass-2-Abnahme in Zeile 1121-1125.
befunde: 2
---

# Prüfung 0021 — die Schadensvorschrift trägt; zwei Befunde daneben

Das Abnahmekriterium ist erfüllt. Alle sechs Bedingungen sind einzeln nachgewiesen, keine
davon durch Augenschein. Die beiden Befunde reißen keine der sechs; sie stehen mit Nachweis
da und mit je einem Vorschlag (`0039`, `0040`).

## Bedingung 1 — Rechenvorschrift statt Adjektiv: **erfüllt**

Geprüft durch Einsetzen, nicht durch Lesen. Zwei Zustände, dieselbe Adresse
`land.BR.instrument.leitzins.gegendruck`, Vorschrift aus `spiel.md` Zeile 683, 713 und 757:

| Größe | Zustand A | Zustand B |
|---|---:|---:|
| `land.BR.sektor.{1,2,3}.wertschoepfung` (Tsd USD) | 200/500/1.300 Mio | dieselben |
| `bip(BR)` | 2.000.000.000 | 2.000.000.000 |
| `land.BR.staatsschuld` | 7.500 bp | 7.500 bp |
| `schuld(BR)` = `mal_geteilt(bip, 7.500, 10.000)` | 1.500.000.000 | 1.500.000.000 |
| `lies_alt` → `lies_neu` (`…leitzins.stand`) | 1.200 → 1.325 bp | 1.200 → 1.200 bp |
| `hub(BR, leitzins)` | 125 | 0 |
| `schaden` = `mal_geteilt(schuld, hub, 10.000)` | **18.750.000** | **0** |
| `lobbypunkte_aus_schaden` (T50) | `1.875 · gegenlobby_satz` | 0 |
| `lies_alt(gegendruck)` = 400 → `gegendruck_neu` | `min(druck_max, 200 + 1.875·satz)` | `min(druck_max, 200)` |

Zwei Zustände, zwei Zahlen, an keiner Stelle eine Wahl. Zweite Probe an der Zollzeile, weil
sie als einzige eine Summe ist: `handelsvolumen(DE,1) = 40.000.000`, `preishub(DE,1) = 300`
→ 1.200.000; `handelsvolumen(DE,2) = 100.000.000`, `preishub(DE,2) = 50` → 500.000;
`schaden(DE, zoll) = 1.700.000`. Ebenfalls genau eine Zahl.

`grep -n "proportional\|angemessen\|im Verhältnis zu" spiel.md` liefert **einen** Treffer,
Zeile 662, und der zitiert die abgelöste alte Fassung.

## Bedingung 2 — jede gelesene Größe hat eine Adresse: **erfüllt**

Alle Lesearten der Tabelle in Zeile 833-843 einzeln in `daten/adressen.md` nachgeschlagen:

| gelesen | Nummern in `adressen.md` |
|---|---|
| `land.<l>.instrument.<i>.stand` | 25, 29, 33, 37 und je +44 |
| `land.<l>.sektor.<s>.preis`, s ∈ {1,2} | 4, 8 und je +44 |
| `handel.<a>.<b>.<s>` | 199-238, vollständig |
| `land.<l>.sektor.<s>.wertschoepfung` | 1, 5, 9 und je +44 |
| `land.<l>.staatsschuld` | 20, 64, 108, 152 |
| `land.<l>.instrument.<i>.gegendruck` | 27, 31, 35, 39 und je +44 |

Keine Lücke, keine neue Adresse, die Zahl 310 bleibt. `bip`, `schuld` und `handelsvolumen`
sind zu Recht keine Adressen — sie stehen als abgeleitete Größen in T48 Nr. 9, 10 und 11.
`regulierung_last` ist keine Zustandsgröße, sondern ein neuer Parameterschlüssel; er steht
als offene Frage in Zeile 1415-1420 und in der Nachziehtabelle Zeile 1470, ändert die 310
nicht und fällt damit unter keine Rücklaufregel. Gegenprobe an `parameter.toml`: Der
Schlüssel fehlt dort tatsächlich noch — gemeldet ist er, also kein Befund.

## Bedingung 3 — Einheit gegen T50: **erfüllt**

Je Faktor die Klasse aus T5 nachgeschlagen und gegen `adressen.md` gegengelesen, statt der
Skalenprobe des Entwurfs zu glauben:

| Zeile | `menge` | K | `verschiebung` | K | Ergebnis |
|---|---|---:|---|---:|---:|
| `zoll` | `handelsvolumen(l,s)` (aus `handel.*`) | 2 | `preishub` (aus `…sektor.<s>.preis`) | 5 | 2 |
| `leitzins` | `schuld(l)` (T48 Nr. 10) | 2 | `hub(leitzins)` (aus `…stand`) | 3 | 2 |
| `haushalt` | `bip(l)` (T48 Nr. 9) | 2 | `hub(haushalt)` | 3 | 2 |
| `regulierung` | `bip(l)` | 2 | `hub(regulierung)` (K 10) × `regulierung_last` (K 3) | 3 | 2 |

Klasse 3 (Basispunkte, 1 bp = 1/10.000) und Klasse 5 (Index, Startjahr = 10.000) sind beide
Zehntausendstel; `mal_geteilt(Klasse 2, Zehntausendstel, 10.000)` ist Klasse 2. Das Ergebnis
geht unverändert in `lobbypunkte_aus_schaden(tsd)` aus T50 Übergang 3. **Kein vierter
Skalenübergang** — die Vorschrift berührt Klasse 1 an keiner Stelle, also wird `cent_in_tsd`
auch nicht gebraucht.

Überlaufprobe nachgerechnet: größter Faktor `bip(US)` ≈ 2,1·10^10 (Beispielzeile in T5), mal
einem Index bis 10^4 sind 2,1·10^14 im `i128`-Zwischenwert von `mal_geteilt` (T6). Weit
unter der Grenze.

## Bedingung 4 — Ort Schritt 5, Wirkung Folgerunde: **erfüllt**

Kanal 3 (`spiel.md` Zeile 529, im Paket noch als Zeile 523 zitiert) Glied für Glied
abgegangen:

| Glied | Schritt | Adresse | Lesart |
|---|---|---|---|
| Instrument | 3 | `…instrument.<i>.stand` | `lies_neu`, in dieser Runde geschrieben |
| Handel | 4 | `handel.*` | `lies_neu` |
| Weltpreis → Sektorpreis | 4 | `land.<l>.sektor.<s>.preis` | `lies_neu` |
| Schaden | 5 | — | gerechnet |
| Gegenlobbybudget | 5 | `…gegendruck` | einziger Schreibzugriff |
| Instrument der Folgerunde | 3 | `…gegendruck` | `lies_alt` |

Der Schluss trägt und ist keine Zusage: `gegendruck` wird ausschließlich in Schritt 5
geschrieben (`grep -n "gegendruck" spiel.md` — Zeile 757 ist der einzige Schreibort), also
ist `lies_neu(gegendruck)` in Schritt 3 nach **T39** ein harter Fehler und kein stiller
Rückgriff auf `alt`. Die Rundengrenze wird vom Werkzeug erzwungen, nicht versprochen.
Gegenprobe an **T38**: `gegendruck` liegt im `spielmodus` in der Sollmaske und muss je Runde
genau einmal geschrieben werden — die Vorschrift schreibt alle 16, in jeder Runde, auch bei
Schaden null. Die Maske hält.

Die Obergrenze `min(druck_max, …)` schließt zusätzlich T30 Prüfung 6
(`0 ≤ gegendruck ≤ druck_max`); die Untergrenze folgt daraus, dass beide Summanden
nichtnegativ sind — `hub` und `preishub` sind Beträge.

## Bedingung 5 — wer geschädigt wird, ist bestimmt: **erfüllt**

Zwei Adressen blind gezogen und hergeleitet:

- `land.DE.instrument.zoll.gegendruck`:
  `Σ_{s∈{1,2}} mal_geteilt(handelsvolumen(DE,s), preishub(DE,s), 10.000)`, darauf
  `lobbypunkte_aus_schaden`, darauf `min(druck_max, teile_gerundet(lies_alt, 2) + …)`.
- `land.US.instrument.regulierung.gegendruck`:
  `mal_geteilt(bip(US), hub(US,regulierung) · regulierung_last, 10.000)`, Rest wie oben.

Die Zuordnung ist eine Regel und kein Fall: je Land aus den Größen dieses Landes gerechnet,
auf die Instrumente desselben Landes gelegt (Zeile 737-742). Der ausländische Schaden geht
nicht verloren, sondern wird beim eigenen Gesetzgeber gebucht, mit Begründung. Dass der
Schaden **nicht** auf den geschädigten Sektor aufgeteilt wird, steht ausdrücklich unter
*Was bewusst fehlt* (Zeile 1332-1335) und ändert an keiner der 16 Zahlen etwas; die
Bedingung verlangt Herleitbarkeit je `gegendruck`-Adresse, und die ist gegeben.

## Bedingung 6 — Begründung gegen die beiden anderen Lesarten: **erfüllt**

Beide sind benannt, beide fallen mit Grund. Der Bewertungsverlust fällt zweifach, und der
zweite Grund ist gegen T50 nachgeprüft: Er steht in Klasse 1, `cent_in_tsd` gibt es nach T50
ausdrücklich nicht, ein vierter Übergang wäre ein ADR. Der Wertschöpfungsverlust fällt am
ersten von drei Gründen, und der Entwurf sagt selbst, dass der erste genügt. Maß 2 ist
genannt und richtig zitiert: `max(Ek) ≤ 1,25 × min(Ek)` steht wörtlich in Zeile 1124-1125.
Der Satz zum Weltlauf steht (Zeile 882-896) und ist gegen **T38** nachgeprüft — `gegendruck`
liegt im Block *Instrumente ohne Stand*, dort auf `nein`, und aus Schritt 5 laufen im
`weltlauf` nur Zustimmung und Regierungswechsel. „Im Weltlauf tut Gegenkraft 5 nichts" ist
damit belegt und nicht bloß erklärt.

---

# Befund 1 — die Zollzeile wächst auch dann, wenn niemand etwas tut

**Schwere:** mittel. Kein Rücklaufgrund, aber der teuerste der beiden.

Der Entwurf verwirft den Wertschöpfungsverlust unter anderem mit dem Satz: *„Er ist
Konjunktur, nicht Reaktion … ohne dass eine einzige Lobbyaktion stattgefunden hätte"*
(Zeile 794-798). Dieselbe Eigenschaft hat die gewählte Zollzeile, und sie ist dort keine
Ausnahme, sondern die Bauart.

**Wie man den Fehler erzeugt.** Aus der Preisbildungsregel (Zeile 104-105) mit
`landespreis = lies_alt(preis)` (Zeile 110) folgt durch Einsetzen:

```
preis_neu − preis_alt = durchgriff · (weltpreis_mit_zoll − preis_alt) / 10.000

also  preishub(l,s) = durchgriff(l,s)/10.000 · | weltpreis_mit_zoll(l,s) − preis_alt(l,s) |
```

`preishub` ist damit **genau dann null, wenn der Inlandspreis den zollbereinigten Weltpreis
schon erreicht hat.** Der Entwurf verlangt aber ausdrücklich das Gegenteil — Zeile 113-114
nennt es Preisträgheit: *„Der Inlandspreis eines Sektors folgt dem Weltpreis mit einem Jahr
Verzögerung."* Solange sich der Weltpreis bewegt, bleibt die Lücke offen und `preishub` von
null verschieden, in jeder Runde, ohne jede Aktion.

**Größenordnung, mit den Zahlen des Entwurfs.** Deutschland, Sektor 2,
`durchgriff = 5.464` (Zeile 135). Weltpreis 10.400, Vorrundenpreis 10.000, kein Zollschritt:
`preishub = 5.464 · 400 / 10.000 = 219`. Bei einem Handelsvolumen von 1,5·10^9 Tausend USD
sind das `mal_geteilt(1.500.000.000, 219, 10.000) = 32.850.000` Tausend USD Schaden — rund
ein Drittel dessen, was die Größenordnungsprobe des Entwurfs selbst für einen **absichtlich
gesetzten** Haushaltsschritt von 50 bp ausrechnet (1,05·10^8, Zeile 1439-1441). Nach der
Halbierungsregel läuft die Zeile gegen `2 · lobbypunkte_aus_schaden(D)`, also gegen einen
dauerhaften Sockel von rund `6.570 · gegenlobby_satz` Lobbypunkten auf jedem
Zollinstrument — bei einem Spieler, der nie etwas tut.

**Warum das nicht bloß Kalibrierung ist.** `gegenlobby_satz` skaliert Sockel und
Aktionsantwort gemeinsam; kein Parametersatz senkt den einen, ohne den anderen mitzunehmen.
Einfluss ist nach Zeile 1429-1430 der **Anteil** des Fonds am gesamten Lobbydruck; ein von
der Konjunktur gespeister Sockel verschiebt diesen Anteil dauerhaft und für alle Profile
gleich. Der Entwurf kennt die Frage — *„Ob die Gegenlobby die Einflusshälfte des Mandats
erreichbar lässt"* —, benennt als Ursache dort aber allein den Gegendruck aus den **eigenen**
Aktionen des Fonds. Die exogene Quelle steht nirgends.

**Was es nicht ist:** kein Rücklaufgrund. Bedingung 6 verlangt eine Begründung gegen die
beiden anderen Lesarten, und die trägt am ersten, vom Entwurf selbst als hinreichend
bezeichneten Grund (Blindheit gegenüber dem Zoll). Es ist auch keine Balancezahl, sondern
eine Struktureigenschaft der gewählten Größe — sie gehört entschieden, nicht gemessen. Drei
Auswege liegen nahe und keiner ist hier gewählt: den Zollkeilanteil der Preisverschiebung
isolieren, `hub(l, zoll)` doch lesen, oder den Sockel bewusst behalten und das hinschreiben.
Vorschlag **0039**.

# Befund 2 — die Lesetabelle zählt acht Zugriffe, die nicht stattfinden

**Schwere:** gering, aber die Zahl wandert.

`spiel.md` Zeile 833-846 führt auf:

```
| Schritt 3 | lies_neu(land.<l>.instrument.<i>.stand) | 16 |
| Vorrunde  | lies_alt(land.<l>.instrument.<i>.stand) | 16 |
…
120 Lesezugriffe, 16 Schreibzugriffe, keine neue Adresse.
```

**Wie man den Fehler erzeugt.** Man liest 113 Zeilen weiter oben denselben Abschnitt:
*„Warum der Zoll als einziger nicht seinen eigenen Stand liest"* (Zeile 720). Die
Instrumententabelle bestätigt es — `verschiebung(l, zoll)` ist `preishub(l,s)` und nicht
`hub(l, zoll)`. `land.<l>.instrument.zoll.stand` wird von dieser Vorschrift also **nicht**
gelesen, weder `neu` noch `alt`. Damit sind es zweimal 12 statt zweimal 16:

`12 + 8 + 40 + 12 + 4 + 12 + 8 + 16 =` **112**, nicht 120.

**Warum es nicht folgenlos ist.** Die Zahl steht ein zweites Mal in der Nachziehtabelle für
den Architekten (Zeile 1471: *„16 Aufrufe je Runde … dazu 120 Lesezugriffe und 16
Schreibzugriffe … T50, Kostenzeile in Abschnitt 10"*). Sie ist damit auf dem Weg in
`technik.md`, wo sie eine Kostenzeile wird — und eine Kostenzeile ist nach dem Logbuch
dieser Rolle die Stelle, an der eine ungenannte Lesart auffällt. Eine falsche wird dort
zweimal gelesen und einmal geglaubt. Vorschlag **0039** (die richtige Zahl hängt am Ausgang
von Befund 1) und **0040** für die Seite `technik.md`.

---

## Wonach ich gesucht und **nichts** gefunden habe

Damit diese Prüfung von einer, die nicht stattfand, unterscheidbar bleibt.

- **Arithmetik, jede Zahl des neuen Abschnitts nachgerechnet.** Der Beharrungswert
  `2 · lobbypunkte_aus_schaden(D)` aus `x = x/2 + p` ✓; die Größenordnungsprobe
  `2,1·10^10 · 50 / 10.000 = 1,05·10^8` und daraus 10.500 Lobbypunkte ✓;
  `schuld = mal_geteilt(bip, staatsschuld, 10.000)` gegen T48 Nr. 10 ✓; `bip` gegen Nr. 9 ✓;
  `handelsvolumen(l,s)` summiert über s gegen Nr. 11 ✓. Ein Fehler: Befund 2.
- **Die Einheitentabelle gegen jede neue Formel** — der produktivste Handgriff dieser Rolle,
  diesmal ohne Ertrag. Vier Zeilen, acht Faktoren, alle Klassen passen; die Grenze zu
  Klasse 1 wird nirgends berührt.
- **Doppelter Schreibzugriff auf `gegendruck`.** Ein einziger Schreibort (Zeile 757). Die
  Hausregel des Entwurfs (Zeile 88) und die Sollmaske aus T38 halten beide.
- **Adressen, die es nicht gibt.** Alle sechs Lesearten nachgeschlagen, einschließlich der
  Restwelt-Handelszeilen `handel.*.RW.*` und `handel.RW.*.*`. `handelsvolumen(l,3)` würde
  eine nicht existierende Adresse lesen — die Vorschrift schließt `s ∈ {1,2}` aber
  ausdrücklich ein, und der Satz „ändert die Zahl nicht" (Zeile 717) ist rechnerisch richtig.
- **Der Regierungswechsel als zweite Schadensquelle** (Zeile 932-939). Nachgegangen, weil er
  in Schritt 5 fällt und Instrumente in Schritt 3 stehen: Die Rückstellung wirkt erst in
  Schritt 3 der Folgerunde, ihr Schaden wird in derselben Folgerunde gebucht. Zyklenfrei;
  die Doppelbestrafung steht selbst unter *Offene Entwurfsfragen*.
- **Fünf neue abgeleitete Größen gegen T48.** `hub`, `preishub`, `schaden`, `menge` und
  `verschiebung` stehen in keiner der siebzehn Zeilen von T48, und T48 nennt genau das einen
  Befund. Die Nachziehtabelle meldet nur `handelsvolumen(l,s)` und sagt „drei Funktionen aus
  T48". **Das ist keine der sechs Bedingungen** — Bedingung 2 fragt nach Zustandsadressen,
  und die sind vollständig —, deshalb kein Befund, sondern Vorschlag **0040**. Es ist
  derselbe Fall wie `korbwert` in Runde 6, und der Entwurf beruft sich sogar auf dessen
  Bauart, ohne die Registrierung mitzunehmen.
- **Die Währungsseite der Zollzeile.** `handelsvolumen` ist Klasse 2 in USD, `preishub` ein
  Landespreisindex; `wert()` aus T48 Nr. 1 teilt an dieser Stelle durch `wechselkurs[g]`, die
  Schadensvorschrift durch 10.000. Ich habe die Preisbildungsregel gegengelesen: Sie mischt
  Weltpreis und Landespreis **ohne** Wechselkurs (Zeile 104), der Sektorpreis steht dort also
  bereits in Weltpreiseinheiten. Die Vorschrift ist damit konsistent mit der Preisbildung;
  die Spannung sitzt in `wert()` und damit in einem anderen Gewerk.
- **Kalibrierbares als Befund verkleidet.** Zwei Kandidaten aktiv verworfen: dass die
  Halbierung eine Zahl ohne Suche sei (sie ist als Regel begründet, und die Redundanz zu
  einem freien Zerfallssatz ist nachgerechnet richtig), und dass `regulierung_last` keinen
  Datenanker habe (steht als offene Frage da, und die Instrumententabelle sagt ohnehin
  „reines Modellkonstrukt"). Beides gehört nach der Ausschlussliste des Pakets hierher und
  nicht in den Befundteil.

## Was ich nicht geprüft habe

- **Ob die Schwellen von Maß 2 mit dieser Vorschrift erreichbar sind.** Das misst der
  Selbstspieler am laufenden Kern. Befund 1 benennt eine Struktureigenschaft, keine
  Schwellenverfehlung.
- **`technik.md`.** Nicht Gegenstand dieses Pakets, und Paket 0011 arbeitet darin. Gelesen
  habe ich sie als Vorgabe (T5, T6, T27, T30, T38, T39, T45, T48, T50), nicht als
  Prüfgegenstand.
- **Die R-Entscheidung aus `daten/deckungsbefund-1997.md`.** Der Entwurf verweist sie
  ausdrücklich in ein eigenes Paket (Zeile 1392-1396). Richtig so; sie bleibt offen.
