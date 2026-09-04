---
typ: pruefung
paket: 0054-partielaenge-r-entscheiden
pruefer: entwurf-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle vier Abnahmebedingungen einzeln nachgerechnet — die Wahl gegen den Deckungsbefund und `reihen.toml`, jede aus R abgeleitete Zahl des lebenden Dokuments aus `R = 20` neu gerechnet, die Prüfgegenstandszahl gegen die eigene Tabelle abgezählt und die alte offene Frage an ihrer Nachfolgestelle gelesen.
befunde: 0
---

# Vier Bedingungen, vier Nachweise — und kein Befund

Erste Prüfung dieses Pakets; unter `befunde/` liegt keine Vorrunde zu 0054 (`ls -la`,
2026-09-04). Geprüft ist der Stand von `7d8ab26` gegen die Vorfassung `6537a9e`.

## Bedingung 1 — eine Wahl, zwei begründete Verwerfungen, Maß 4 namentlich

**Erfüllt.**

`spiel.md` Z. 93 und Z. 147 wählen **20**; das Frontmatter Z. 10 und Z. 15 tragen den Wert.
Die beiden anderen Werte fallen mit je einem eigenen, nachprüfbaren Grund:

- **`R = 24` fällt an den Daten.** Der Entwurf zerlegt den Ausweg „Reihe 9 und Reihe 11
  gestrichen" in drei nötige Quellenersetzungen (Z. 111-115) und zeigt, dass Streichen nur
  die *Soll*-Rolle trifft, nicht die Rollen Start und Politikpfad. **Gegengeprüft an
  `daten/reihen.toml`, nicht am Entwurf:** Reihe 11 trägt dort Z. 1086
  `rolle_tabelle = "Start + Soll (4, abgeleitet)"`, Reihe 9 Z. 898
  `"Start + Politikpfad + Soll (4, gesetzt)"`. Beide Rollenangaben stützen das Argument
  unabhängig vom Text, der es macht. Der Startwert für 1997 existiert nach
  `deckungsbefund-1997.md` Z. 42 und Z. 266-272 für die USA nicht (WEO beginnt 2001) und
  nach Z. 269 für Brasilien nicht (2000) — eine **Anfangslücke**, und die Füllregel T24
  („Fortschreibung des letzten bekannten Werts") hat vor der ersten Stützstelle nichts
  fortzuschreiben. Die Zeile „Reihe 11 BRA" allein erledigt 1997.
- **`R = 19` fällt an der weggeworfenen Stützstelle 2021** (Z. 121-131): Der US-Leitzins ist
  nach T37 `gesetzt`, sein Fehler null per Konstruktion, er ist keiner der 16
  Prüfgegenstände und konnte keiner werden. Ein Fenster, das 2020 endet, prüft den Einbruch
  und nie die Rückkehr.

**Maß 4 ist namentlich genannt, nicht bloß erwähnt.** Die Tabelle Z. 143-147 führt für jeden
der drei Auswege die Prüfgegenstände getrennt von den Sollreihen, und Z. 149-153 nennt deren
Herkunft einzeln: Reihe 1 BIP (4), Reihe 2 Sektorstruktur (4), Reihe 8 Verbraucherpreise (4),
Reihe 10 Wechselkurs (3), Reihe 14 Handelsblock (1). **Abgezählt: 4+4+4+3+1 = 16**, gegen die
eigene Tabelle Z. 1664-1671 und gegen `reihen.toml` `[zaehlung.pruefgegenstaende]` Z. 174-181
(`gesamt = 16`, dieselbe Zerlegung). Der gewählte Weg kostet keinen — das ist die verlangte
Aussage, und sie steht als Aussage da und nicht als Aufzählung.

**Der Vergleich mit der Quelle, die entscheiden ließ:** `deckungsbefund-1997.md` Z. 55-59
legt genau drei Auswege mit R = 20 / 19 / 24 und den Fenstern 2001–2021 / 2001–2020 /
1997–2021 vor. Die Tabelle in `spiel.md` Z. 143-147 gibt alle drei Zeilen mit Fenster,
Stützstellen und Sollreihenzahl unverändert wieder. Nichts ist verschoben, um die Wahl
leichter zu machen.

## Bedingung 2 — keine Zahl mehr auf einem anderen R

**Erfüllt.** Nachgerechnet, nicht gelesen. Jede Zahl unten habe ich aus `R = 20`
neu gebildet und gegen das Dokument gehalten:

| Größe | Fundstelle | Formel | aus R = 20 | steht da |
|---|---|---|---|---|
| Partiedrittel (Maß 1) | Z. 12, 1514 | `1…⌊R/3⌋`, `…⌊2R/3⌋`, `…R` | 1-6, 7-13, 14-20 | ✓ |
| Gewinnschwelle (Maß 2) | Z. 13, 1535 | `R × 1.000` | 20.000 | ✓ |
| Frühfenster (Maß 3) | Z. 14, 1567 | erstes Drittel | 1-6, Rest 7-20 | ✓ |
| Spätfenster (Maß 3) | Z. 14, 1569 | letztes Drittel | 14-20, davor 1-13 | ✓ |
| Stützstellen | Z. 10, 15, 135 | `R + 1` | 21 | ✓ |
| Übergänge (Maß 4) | Z. 1644, 1645 | `R` | 20 | ✓ |
| Band „Mandat erfüllt" | Z. 1379 | `1.000 … R × 1.000` | 1.000 … 20.000 | ✓ |
| Band „überlebt" | Z. 1380, 1409 | `(R+1)×1.000 + 0…3.000` | 21.000 … 24.000 | ✓ |
| Todesband | Z. 1381 | `30.000 + (R+1−d)×1.000`, `d = 1…R` | 31.000 … 50.000 | ✓ |
| unerreichbare Lücken | Z. 1425-1427 | — | 20.001…20.999 / 24.001…30.999, 7.000 Luft | ✓ |
| Bereichstest | Z. 1434 | `1.000 … R×1.000+30.000` | 1.000 … 50.000 | ✓ |
| Steckplätze je Partie | Z. 1468 | `3R`, `3k·ai` bei `k = R/5` | 60, `12·ai` | ✓ |
| Maß 1 je Startwert | Z. 1523-1526 | `30·R(R+1)/2 + R` | 30·210 + 20 = 6.320 | ✓ |
| Maß 1, 50 Startwerte | Z. 1527 | ×50 | 316.000 | ✓ |
| Suchbotpartie | Z. 1559 | `R × 61` | 1.220 | ✓ |
| Maß 2 | Z. 1560 | `126 × 20 × 1.220` | 3.074.400 | ✓ |
| Maß 3 | Z. 1588 | das Doppelte | 6.148.800 | ✓ |
| Summe der drei Maße | Z. 1590 | — | 9.539.200 | ✓ |
| Maß 4 | Z. 1697 | `R` | 20 | ✓ |
| Sollreihen | Z. 134, 1623 | 4+12+4+3+4 | 27, davon 23 frei | ✓ |

**Die Fenstergrenzen im Rumpf, die keine Maßfenster sind, ebenfalls einzeln:** Startzustand
2001 + t = Ende Runde t — WTO-Beitritt Dezember 2001 wirkt ab Runde 1, Finanzkrise 2008 =
Ende Runde 7, Einbruch 2020 = Ende Runde 19, Erholung 2021 = Ende Runde 20 (Z. 190-192, alle
vier nachgerechnet). Der negative Euro-Einlagesatz ab 2014 liegt in den Runden **13 bis 20**
(Z. 652); 2014 − 2001 = 13 ✓. Der Euro-Bruch 1999 und `verkettet_ab = 1999` liegen vor dem
Fenster, und die drei Stellen, die vorher „ab Runde 3" sagten (Z. 407, 759, 1350), sagen es
nicht mehr.

**Die Nachziehtabelle für den Architekten ist in beiden Spalten nachgerechnet**, nicht nur in
der neuen — das ist die Stelle, an der eine Prüfung sonst die Vergleichszahl übersieht. Alle
dreizehn Zeilen der „war"-Spalte (Z. 2020-2032) stimmen mit `technik.md` Z. 2216-2230 wörtlich
überein; die Nachzählzeile `9.539.200 + 200.000 + 200 + 20 + 20.000 = 9.759.420` geht auf,
und die alte `11.519.040 + 240.000 + 200 + 24 + 24.000 = 11.783.264` ebenfalls. Die
Kalibrierschleife: `1.000 × 9.539.200 = 9,54 Mrd`, beim Planwert 10 µs sind das 95.392 s =
**26,5 h** auf einem Kern und **3,3 h** auf acht ✓; die verkürzte Fassung `10 × 6.320 = 63.200`
und `126 × 5 × 1.220 = 768.600` ✓ (die Vorwerte 90.240 und 922.320 stehen in `technik.md`
Z. 2254 und passen zu R = 24).

**Wie ich die 22 Treffer auf `R = 20`/`R = 24` behandelt habe.** Sie enthalten beide Werte,
und das allein beweist nichts. Entschieden hat die Frage, ob ein Treffer eine *geltende*
oder eine *zitierte* Zahl ist. Das Dokument zieht dafür Z. 2125-2138 eine ausdrückliche
Linie: darunter stehen nur die erledigten Nachziehtabellen der Fassungen 3 und 4 und die
Befundabarbeitungen, also datierte Nachweise abgeschlossener Läufe. **Ich habe die Linie
nicht geglaubt, sondern die Abschnittsüberschriften darunter einzeln gelesen** (Z. 2140,
2165, 2192, 2236, 2308, 2364) — sechs Stück, alle sechs Protokoll, keine geltende Regel
darunter. Und umgekehrt: die drei Nachziehtabellen **oberhalb** der Linie (Z. 2063, 2081,
2098) enthalten keine aus R gebildete Zahl; ihre Sätze „R ändert sich nicht" (Z. 2077,
Z. 2115) sind Aussagen über die Pakete 0021, 0039 und Fassung 5 und bleiben richtig.
Ein Protokoll nachzuziehen wäre der Fehler, den die Hausregel dem Chronisten verbietet.

## Bedingung 3 — die Prüfgegenstandszahl bei `R < 24`

**Erfüllt, und zwar in der Form „ausdrücklich als unverändert begründet".**

Z. 1678-1685 sagt es und rechnet es vor: Gestrichen sind die vier Leitzinsreihen; keiner der
sechzehn enthält Reihe 9, und keiner könnte sie enthalten, weil sie nach T37 `gesetzt` war —
Fehler null per Konstruktion. **Verändert hat sich der Nenner der Sollreihen (31 → 27), nicht
der der Prüfgegenstände.** Genau das verlangt die Bedingung: dass „höchstens 2 der 16"
nicht stillschweigend auf einer anderen Reihenmenge weiterläuft.

**Nachgezählt, nicht übernommen:** Die 16 aus Z. 1664-1671 speisen sich aus den Reihen 1, 2,
8, 10, 14. Die 27 Sollreihen aus Z. 134 sind die Reihen 1 (4), 2 (12), 8 (4), 10 (3), 11 (4).
Der Schnitt beider Mengen enthält Reihe 9 in keiner Richtung. Die 23 freien Sollreihen des
Frontmatters bleiben deshalb dieselben 23 wie vorher (4+12+4+3), obwohl die Gesamtzahl von 31
auf 27 fällt — die einzige Zahl, die in diesem Paket *nicht* mitwandern durfte, und sie ist
nicht mitgewandert. Die Toleranz 2 steht unverändert.

Die Folgezahl an anderer Stelle ist ebenfalls nachgezogen: Z. 779-782 („von den **27**
Sollreihen sind **23** unabhängig", vorher 31 und 27), und die Klasse `gesetzt` entfällt
mit Begründung statt stillschweigend (Z. 1629-1637). An ihre Stelle tritt eine **Invariante**
statt einer Schwelle — das ist schärfer und nicht weicher, und damit keine Absenkung.

## Bedingung 4 — die offene Frage ist geschlossen, nicht verschoben

**Erfüllt.** Die Stelle, die das Paket mit „Z. 1679-1691" meint, ist der Punkt unter *Offene
Entwurfsfragen*, der in der Vorfassung „Bleibt das Fenster bei 1997–2021?" hieß und im
Nachtrag vom 2026-09-02 mit **„Das braucht ein eigenes Arbeitspaket mit eigener Abnahme"**
endete. **Gegengelesen an der Vorfassung** (`6537a9e`, dort Z. 1662-1691) und an ihrer
Nachfolgestelle (heute Z. 1861-1870): Der Punkt heißt jetzt „**Das Fenster ist entschieden
und diese Frage geschlossen**", nennt Wert, Fenster, Stützstellenzahl, Paketkennung und den
Ort der Begründung. Der Satz „Das braucht ein eigenes Arbeitspaket" ist nicht mehr im
Dokument (Suchlauf über die ganze Datei).

**Die zwei neuen Punkte dahinter sind nicht dieselbe Frage in anderer Form**, und ich habe
das geprüft statt es zu glauben: Der eine fragt, *woher* der Leitzinspfad für Deutschland und
China kommt (Beschaffung, Datenbauer), der andere, ob ein *einheitlicher Zinsbegriff* über
vier Länder erreichbar ist. Beide betreffen den Leitzins in seiner Rolle als **Eingabe** und
nicht das Fenster; keiner von beiden lässt R offen. Das deckt sich mit `reihen.toml`
Z. 919-921, wo die zweite Frage schon als `offen` der Reihe 9 steht.

**Der Satz „Und R kann weiter fallen" (Z. 216-220) ist keine Rückverschiebung.** Er benennt
drei Pfade mit `deckung_gemessen = false` — nachgesehen in `reihen.toml`: Reihe 5 Z. 652,
Reihe 6 Z. 708, Reihe 13 Z. 1260, alle drei `false`, alle drei reine Pfade ohne Sollrolle —
und stellt fest, dass die Ersetzungsregel für sie gilt. Das ist
ein benanntes Restrisiko mit einer Regel daneben, keine offene Entscheidung: Der Wert ist
gesetzt, das Frontmatter trägt ihn, und der Selbstspieler kann jede der vier Maßvorschriften
ab sofort rechnen. Genau das war der Zweck des Pakets.

## Wonach ich gesucht und **nichts** gefunden habe

Damit diese Prüfung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Die Nebenzahl neben der Abnahmezahl.** Mein teuerster Fund der Vorrunde saß in der
  Vergleichsspalte, nicht in der geprüften. Hier habe ich beide Spalten der
  Abschnitt-10-Tabelle aus ihren eigenen Zeilen gerechnet — dreizehn Zeilen, zweimal — und
  zusätzlich die Vorwerte gegen `technik.md` gehalten. Fehlerfrei.
- **Die Einheitentabelle gegen jede neue Formel.** Dieses Paket schreibt keine neue Formel;
  es ersetzt einen Wert in vorhandenen. Skalenklassen unberührt, kein Kandidat.
- **Eine neu gerechnete Größe mit undefinierter Eingabe.** In den letzten sechs Läufen lag
  der teuerste Befund jedes Mal dort, wo eine Größe zum ersten Mal *gerechnet* statt nur
  *benannt* wurde. Hier gibt es keine: Der Unterschied `6537a9e → 7d8ab26` fasst keine
  Zustandstabelle und keinen Abschnitt *Der Zustand* an; er ersetzt Werte in vorhandenen
  Formeln und fügt Begründungstext hinzu. Kein Kandidat.
- **Ein Lauf, den ein Maß vorschreibt und der nicht zu Ende läuft.** Alle vier Maße rechnen
  mit R = 20 durch; Maß 3 hat mit 1-6 und 14-20 ein Früh- und ein Spätfenster, die sich nicht
  überlappen und die Partie nicht überschreiten.
- **Die Zugabe „20 ist ein Vielfaches von 5" gegengeprüft statt geglaubt.** Sie steht auf dem
  Vorratsverfahren (Z. 1446-1473), und das gilt nach Z. 1455-1456 für **beide** Bots — der
  Bot wählt die Art, die Bots wählen nur die Aktion darin. Also gilt sie tatsächlich für alle
  126 Läufe von Maß 2. `24 mod 5 = 4` und `19 mod 5 = 4`: beide verworfenen Werte enden
  mitten im Zyklus ✓. Für Maß 3 gilt sie nicht, und der Entwurf sagt das selbst — Fenster
  von 6 und 7 Runden, Wechsel nach Runde 6 und 13, keiner davon ein Nullpunkt ✓.
- **Was nach der Ausschlussregel des Pakets kein Befund ist und deshalb hier steht statt
  oben:** Ob 20 Runden für die Entscheidungsdichte im letzten Drittel genügen, ob die
  Schwellen MAPE 20 % / 300 bp / 0,6 über ein kürzeres Fenster leichter oder schwerer zu
  halten sind, und ob der Verlust des Euro-Übergangs Maß 3 eine Quelle nimmt, die es braucht.
  Alle drei sind **Messungen** von Rückvergleicher und Selbstspieler, keine Entwurfsfehler —
  Balance wird gemessen, nicht entworfen. Der Entwurf benennt alle drei selbst (Z. 163-166,
  Z. 176-178, Z. 1750-1758) und erfindet für keine eine Zahl.

## Zwei Sachen außerhalb der vier Bedingungen — als Vorschlag, nicht als Befund

Beide betreffen **andere Dateien** und damit weder Bedingung 2 (die auf `spiel.md` lautet)
noch die drei übrigen. Sie sind Arbeit, kein Mangel dieses Laufs, und liegen als
`aufgaben/0064-…` und `aufgaben/0065-…` mit `status: vorschlag` daneben:

1. **Die Nachziehliste für `technik.md` ist unvollständig, und sie behauptet von sich das
   Gegenteil** („Die beiden Tabellen zusammen sind die Liste", Z. 2004). Zehn geltende
   Stellen in `technik.md` stehen weiter auf `R = 24` und sind in keiner der beiden Tabellen
   genannt — darunter der Frontmatter-Schlüssel `nachtlauf` (Z. 20), dessen richtige Zahl
   dasselbe Dokument zwei Absätze weiter selbst ausrechnet. Der Fehlertyp ist derselbe, den
   der zweite Lauf dieses Pakets an sich selbst gefunden hat: Zahlen außerhalb eines
   T-Blocks. Er ist nur nicht weit genug getrieben worden.
2. **`reihen.toml` trägt Reihe 9 an neun Stellen als Sollreihe**, benannt sind zwei
   (`t37_klasse`, `rolle_tabelle`, Z. 2058-2060). Der ganze `[zaehlung]`-Block, der von sich
   sagt, er sei maschinell nachrechenbar, steht auf 31 statt 27.
</content>
</invoke>
