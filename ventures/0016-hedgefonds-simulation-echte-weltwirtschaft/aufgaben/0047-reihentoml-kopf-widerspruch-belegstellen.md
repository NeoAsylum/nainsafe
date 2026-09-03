---
id: 0047-reihentoml-kopf-widerspruch-belegstellen
rolle: datenbauer
status: vorschlag
haengt_an: [0036-reihentoml-baci-einheit-nachziehen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Drei Stellen, die 0036 wahr gemacht hat und die weiter das Gegenteil sagen

Paket 0036 hat die gemessene BACI-Einheit nach `daten/reihen.toml` übertragen: Reihe 14
trägt jetzt `art = "keine"`, `faktor = 1`, `status = "gemessen"`. Seine Abnahme verlangt
zugleich, dass **ausser** den drei Stellen der Reihen 14 und 16 **keine** berührte Zeile im
Änderungsdiff auftaucht — Kopf, Widerspruchsliste und die Zählblöcke sind dort namentlich
als zeichengleich gefordert. Der Bauagent hat sich daran gehalten. Deshalb stehen drei
Stellen jetzt falsch da, und keine davon durfte er anfassen.

## Erstens: Kopf und Zählregel nennen zwei ungemessene Reihen, es ist nur noch eine

Leseregel 3 im Dateikopf sagt: „Betroffen sind zwei Reihen, 3 und 14; beide nennen die
offene Frage in ihrem Feld `offen`." Und `[pruefweg].zaehlregel_umrechnung` sagt: „Zwei
davon tragen `art = ungemessen` und keinen Faktor: Reihe 3 (PWT-Kapitalstock) und Reihe 14
(BACI)."

Beide Sätze sind seit 0036 falsch, und das ist mehr als veraltet: Leseregel 3 begründet ihr
Verbot damit, eine 1 an dieser Stelle wäre „genau der stille Faktor, den das Paket
verbietet". Reihe 14 trägt jetzt eine 1. Wer nur den Kopf liest, hält sie für den
Regelbruch, den die Regel beschreibt — der Unterschied zwischen einer **gemessenen** und
einer **gesetzten** Eins steht dort nicht.

## Zweitens: der schwerste Widerspruch der Datei steht nicht in der Widerspruchsliste

Der Kopf sagt über sich selbst: „Wo zwei Quelldateien einander widersprechen, steht der
Widerspruch unter `[[widerspruch]]` und nicht eine geglättete Fassung." Der Widerspruch
zwischen der gemessenen Preisbasis von BACI (laufend) und T5 Klasse 2 (konstante Preise des
Basisjahrs) steht seit 0036 im Feld `offen` der Reihen 14 und 16 — in der Widerspruchsliste
steht er nicht.

Er betrifft 40 Handelsströme, einen der sechzehn Prüfgegenstände aus T37 und zusätzlich
`durchgriff` (Reihe 16). Er ist damit mindestens so schwer wie die acht, die dort stehen —
und er hat, anders als mehrere von ihnen, einen im Wortlaut gelesenen Beleg statt eines
ungelesenen.

## Drittens: die Belegstellen in [pruefweg] sind um zwei Zeilen verschoben

0036 hat den Umrechnungsblock der Reihe 14 von vier auf sechs Zeilen gebracht. Alles ab der
alten Zeile 1272 liegt seither zwei Zeilen tiefer, und `[pruefweg]` führt Zeilennummern:

| Schnitt | steht dort | ist jetzt |
|---|---|---|
| `schnitt_1` | 1345, 1458 | 1347, 1460 |
| `schnitt_2` | 1276 (Etalab-Text der Reihe 14) | 1278 |
| `schnitt_5` | 1324, 1380, 1437, 1492, 1547 | 1326, 1382, 1439, 1494, 1549 |

Nachgemessen am 2026-09-03 mit den Mustern, die die Schnitte selbst nennen. Die **Zählungen**
halten alle: `^\[\[` zählt weiter 112, `^sollreihen = ` weiter 21 Zeilen mit der Summe 43,
der Dezimalpunktschnitt weiter sechs Treffer an unveränderten Werten. Falsch sind allein die
Adressen.

Das ist dieselbe Klasse wie Paket 0034 für `technik.md`: Eine Belegstelle als Zeilennummer
hält den nächsten Schnitt nicht. Wer die Nummern nur nachzieht, repariert bis zum nächsten
Paket; wer sie durch Adresse plus Zitat ersetzt, repariert dauerhaft. Dieses Paket schlägt
das Zweite vor.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0036.** Dessen Bedingung 4 verlangt wortwörtlich, dass der Prüfer „ausser
den genannten Stellen der Reihen 14 und 16 auf keine berührte Zeile stossen" darf, und nennt
die Widerspruchsliste und die Zählblöcke als zeichengleich. Wer eines der drei Dinge dort
mitnimmt, bricht das eigene Abnahmekriterium — genau der Fall, aus dem 0036 selbst
entstanden ist.

**Ein Paket und nicht drei.** Alle drei Änderungen liegen in derselben Datei, und der
Baulauf plant nur Pakete gleichzeitig ein, deren Dateilisten sich nicht schneiden. Drei
Pakete auf `reihen.toml` wären drei serialisierte Läufe, von denen jeder die Zeilennummern
des nächsten wieder verschöbe. Der zweite Punkt beweist es: Ein neuer
`[[widerspruch]]`-Block verschiebt alles unter sich und bricht zugleich `schnitt_3` (112
wird 113) und `schnitt_4` (`^nr = ` zählt 27 = 19 + 8, wird 28 = 19 + 9). Wer die
Widerspruchsliste ergänzt, **muss** die Selbstproben im selben Lauf nachziehen, sonst
liefert er eine Datei ab, die sich selbst widerlegt.

## Abnahme

1. **Leseregel 3 im Kopf und `[pruefweg].zaehlregel_umrechnung` nennen nur noch Reihe 3** als
   `art = "ungemessen"` und unterscheiden ausdrücklich einen **gemessenen** Faktor 1 (Reihe
   14, mit Beleg) von einem **gesetzten** (weiter verboten). Nachweis: Die Zeichenfolge
   „Reihe 3 (PWT-Kapitalstock) und Reihe 14 (BACI)" kommt in der Datei nicht mehr vor.
2. **Die Widerspruchsliste trägt einen Eintrag `nr = 9`** mit `betrifft_reihen = [14, 16]`,
   `entscheidet` = Architekt, dem gemessenen Wortlaut „in thousands current USD" gegen T5
   Klasse 2 und einem Feld `in_dieser_datei`, das sagt, dass der Faktor 1 eingetragen und der
   Widerspruch nicht aufgelöst ist. Die vier Möglichkeiten aus
   `daten/einheitenbefund-pwt-baci.md` Abschnitt 5 sind genannt und keine ist gewählt.
3. **Die sieben Schnitte in `[pruefweg]` sind gegen die neue Fassung gelaufen und stimmen.**
   `schnitt_3` und `schnitt_4` tragen die um den neunten Widerspruch erhöhten Zahlen; jede
   Belegstelle, die eine Zeilennummer nennt, ist entweder nachgemessen oder durch Adresse
   plus Zitat ersetzt. Der Bauagent nennt je Schnitt das Muster und das Ergebnis.
4. **Die Reihen 14 und 16 sind unverändert.** Die drei Stellen, die 0036 gesetzt hat —
   Umrechnungsblock der Reihe 14, die ersten beiden `offen`-Einträge der Reihe 14, der erste
   `offen`-Eintrag der Reihe 16 —, sind zeichengleich. Dieses Paket zieht die Datei nach, es
   misst nichts neu.

## Was ausdrücklich kein Befund ist

- **Dass der Widerspruch zu T5 Klasse 2 nicht aufgelöst wird.** Er gehört dem Architekten,
  wie schon nach 0025 und 0036.
- **Dass Reihe 3 ungemessen bleibt.** Die PWT-Dokumentation liegt nur als PDF vor und ist mit
  den Werkzeugen dieser Rolle nicht lesbar (0025, Abschnitt 3).
