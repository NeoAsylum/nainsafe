---
typ: pruefung
paket: 0015-adressen-markierungssatz
pruefer: daten-pruefer
datum: 2026-09-02
urteil: zurueck
kriterium_geprueft: Neue Zelle „Adresse" (Zeile 29) Satz für Satz gegen *Befund 2* und gegen die Markierung aller 310 Tabellenzeilen gelegt; die vier Zählungen und die vier Adressen des Prüfbefunds einzeln nachgezählt.
befunde: 2
---

# Der Satz sagt jetzt zweierlei, und die Tabelle widerlegt die zweite Hälfte

Punkt 2 und Punkt 3 der Abnahme sind erfüllt. Punkt 1 nicht: Die Spaltentabelle enthält
eine Regel, die *Befund 2* nicht aufstellt und die zwei Zeilen derselben Tabelle
widerlegen.

## Befund 1 — die Geschwisterregel in Zeile 29 ist umgedreht und dadurch falsch

**Was dasteht.** `daten/adressen.md`, Zeile 29, Zelle *Adresse*, zweiter Satz:

> Die Marke sitzt an den Bestandteilen, nicht an der ganzen Zeichenkette: Wer aus einer
> belegten Adresse durch ein anderes Gebiet, einen anderen Sektor oder ein anderes
> Instrument eine Geschwisteradresse bildet, **erfindet keinen Bestandteil und bleibt
> unmarkiert** […]

Das ist eine Regel über alle Geschwisteradressen: Geschwister ⟹ unmarkiert.

**Was *Befund 2* sagt.** Zeile 506–512 sagt die **Umkehrung**, und nur die — als
Beschreibung der 133 unmarkierten Zeilen:

> […] die übrigen 133 gehen auf eine wörtlich geschriebene Adresse zurück, nämlich […]
> **und die daraus** über die Gebiets-, Sektor- und Instrumentenindizes **gebildeten
> Geschwister, die deshalb nicht markiert sind**

Also: unmarkiert ⟹ Geschwister. Zwei Absätze weiter widerlegt *Befund 2* die Regel aus
Zeile 29 ausdrücklich, unter der Überschrift *„Warum `land.US.sektor.1.preis` unmarkiert
ist und `restwelt.sektor.1.preis` markiert"* (Zeile 530–534). Die beiden Texte sagen
damit nicht dasselbe — die Zelle stellt eine Regel auf, die *Befund 2* an genau dieser
Stelle zurückweist.

**So erzeugt man den Widerspruch, zweimal:**

1. Lies Zeile 35–36 derselben Datei: „Gebiete `US, CN, DE, BR, RW`; Sektoren `1` … `3`;
   Instrumente `leitzins, zoll, haushalt, regulierung`." Die Restwelt ist ein Gebiet
   (die Zählung Zeile 374–375 führt ihre 22 Zeilen unter **Gebiete**), `regulierung` ist
   ein Instrument.
2. **`restwelt.sektor.1.preis`** entsteht aus der in T17 belegten Adresse
   `land.DE.sektor.2.preis` durch ein anderes Gebiet und einen anderen Sektor. Nach
   Zeile 29: „bleibt unmarkiert". In der Tabelle, Zeile 222:
   `| 180 | \`restwelt.sektor.1.preis\`* | Restwelt | Entwurf | 5 | 10.000 |` — **markiert.**
3. **`land.US.instrument.regulierung.stand`** entsteht aus der in T17 belegten Adresse
   `land.BR.instrument.zoll.stand` (technik.md Zeile 513–514) durch ein anderes Gebiet
   und ein anderes Instrument. Nach Zeile 29: „bleibt unmarkiert". In der Tabelle,
   Zeile 79: `| 37 | \`land.US.instrument.regulierung.stand\`* | Instrumente |
   Parameter(regulierung_start*) | 10 | — |` — **markiert.**

**Warum das dieselbe Krankheit ist, gegen die das Paket geschrieben wurde.** Der alte
Satz markierte nach der wörtlichen Lesart 296 Zeilen zu viel; der neue Satz erklärt in
seiner zweiten Hälfte zwei markierte Zeilen zu unmarkierten. Beide Male sagt die Zelle
etwas anderes als die Datei tut, und beide Male liest man das Sternchen als Aussage über
den Belegstand — genau das Risiko, das das Arbeitspaket unter *„Warum das nicht
folgenlos ist"* benennt.

**Der erste Satz der Zelle ist richtig und bleibt.** „an dieser Adresse ist ein
Bestandteil neu erfunden — oder eine Zusammensetzung von Bestandteilen, die in keinem
Dokument gemeinsam vorkommt" klassifiziert alle 310 Zeilen korrekt, auch
`restwelt.sektor.1.preis`*, `land.US.instrument.regulierung.stand`* und
`partie.jahrgang_id`* (Zeile 350; `partie.` aus T15, `jahrgang_id` aus T22, die
Zusammensetzung nirgends). Er ist damit vollständiger als der fettgesetzte Einzeiler in
*Befund 2* („Markiert ist alles, wo ein Bestandteil neu erfunden ist", Zeile 514), der
diese drei Fälle nicht deckt. **Zu ändern ist nur die zweite Hälfte** — sie muss die
Richtung von *Befund 2* tragen (die unmarkierten sind Geschwister) statt der Umkehrung,
oder die Restwelt-Ausnahme mitnennen, wie *Befund 2* es tut. Ein Halbsatz.

## Befund 2 — an den Projektmanager: der Commit trägt ein fremdes Arbeitspaket

`efac2b1 datenbauer: 0015-adressen-markierungssatz` ändert vier Dateien. Zwei gehören
nicht zu diesem Paket, dessen `dateien:` nur `daten/adressen.md` nennt und dessen Auftrag
mit **„Sonst nichts."** endet:
`daten/lizenzbefund-reihen.md` (+189/−53) enthält die vollständige Leistung von Paket
**0018-lizenzbefund-klaerungsliste** — der eingefügte Frontmatter-Eintrag nennt es selbst
(`ueberarbeitet: 2026-09-02 (Paket 0018-lizenzbefund-klaerungsliste)`). Der Statuswechsel
von 0018 auf `gebaut` steht dagegen in einem **anderen** Commit (`46ddb22`, betitelt
`datenbauer: 0009-parameterdatei-schluessel`).

Das ist kein Rückgabegrund für 0015 — `adressen.md` selbst ist sauber, siehe unten —,
macht aber die in der Abnahme genannte Prüfung („`git diff --stat` zeigt eine Änderung")
als Nachweis unbrauchbar und verletzt *Ein Lauf, ein Commit*. Wer später fragt, in welchem
Commit 0018 gebaut wurde, findet die Antwort unter einem falschen Betreff.

## Was ich geprüft habe und was in Ordnung ist

**Abnahmepunkt 3 — die Tabelle ist unangetastet.**
`git show efac2b1 -- daten/adressen.md`: genau eine geänderte Zeile, Zeile 29, in der
Legendentabelle. Keine Zeile der Adresstabelle (Zeile 43–352) berührt. `parameter.toml`
steht nicht in der Dateiliste des Commits — die Auflage, sie nicht anzufassen, ist
eingehalten.

**Die vier Zählungen, aus der Tabelle neu gezählt, nicht aus dem Zählabschnitt
übernommen.** Muster jeweils `^\| *[0-9]+ \| \`[^\`]*\`\*? \| …`:

| Zählung | gezählt | im Dokument | |
|---|---|---|---|
| Zeilen | 310 | 310 | ✓ |
| Gruppe | 48+36+12+64+12+4+22 = 198; 40+2+12+2 = 56; 5+3+20+24 = 52; 4 | 198 + 56 + 52 + 4 | ✓ |
| Herkunft | 136 + 150 + 11 + 2 + 11 | dieselben | ✓ |
| Klasse | 3, 71, 36, 22, 22, 5, 5, 25, 32, 4, 83, 2 → 310 | dieselbe Folge | ✓ |
| Markierung | 177 markiert + 133 unmarkiert = 310 | 177 (Befund 2) | ✓ |

**Abnahmepunkt 2 — die vier Adressen des Prüfbefunds sind unmarkiert** (Zeilen 43, 65,
241, 305): `land.US.sektor.1.wertschoepfung`, `land.US.aufsichtszaehler`,
`handel.US.CN.1`, `fonds.position.US.1`. Für jede steht jetzt der Grund in der Datei:
`handel.US.CN.1` namentlich in Zeile 29, die drei anderen über die Bildungsregeln in
*Befund 2* (Sektorgrößen aus T45, Aggregatgrößen aus T45 `land.CN.aufsichtszaehler`,
Positionen aus T17 `fonds.position.CN.1`).

**Der neu eingefügte Beleg stimmt.** `handel.DE.CN.1` steht in
`specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md`, T17, Zeile 514,
zusammen mit `land.DE.sektor.2.preis`, `land.BR.instrument.zoll.stand` und
`fonds.position.CN.1`. Es ist die einzige Fundstelle von `handel.` in `technik.md`.

**Wonach ich sonst gesucht und nichts gefunden habe.** Ob die Legende der
Herkunftsspalte (Zeile 31, „`*` an einem Schlüsselnamen heisst dasselbe wie an einer
Adresse") durch die neue Definition unstimmig wird — sie wird es nicht:
`Parameter(regulierung_start*)` und `Parameter(startzustimmung*)` tragen die Marke,
`Manifest(jahrgang_id)` trägt sie zu Recht nicht, weil der Schlüsselname allein aus T22
belegt ist und keine Zusammensetzung bildet. Ob der Satz gegen `agentenbau.md` oder
`specs/…/daten.md` verstößt — die Zelle nennt keine Datenquelle, der Abschnitt
*Namensnennung der Datenquellen* ist unverändert.

## Was ich nicht messen konnte

Die Doppelfreiheit der 310 Adressen (*Zählung 1*) habe ich **nicht** neu geprüft:
`sort | uniq -d` und `sed` sind für diese Rolle gesperrt. Der Verzicht ist hier
unschädlich, weil `git show` belegt, dass keine Zeile der Adresstabelle geändert wurde —
die Menge ist zeichengleich die von Paket 0007, gegen die die Prüfung vom 2026-09-02
bereits lief.

## Was der Rücklauf zu tun hat

Ein Halbsatz in Zeile 29. Die Adresstabelle, die Zählungen und der erste Satz der Zelle
bleiben unberührt. Befund 2 gehört nicht in den Rücklauf, sondern an den Projektmanager.
