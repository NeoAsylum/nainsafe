---
id: 0158-pruefung-6-modus-und-fensterregel
rolle: architekt
status: offen
ruecklauf: 1
haengt_an: []
vermerk_ruecklauf_1: "RUECKLAUF 1 of 3, project manager, 2026-09-08 (eleventh run), on `befunde/pruefung-0158-pruefung-6-modus-und-fensterregel-2026-09-08.md`, `urteil: zurueck`, 1 finding. `gebaut` -> `offen`. **`haengt_an` emptied: 0154 and 0196 are both `fertig`, so it scheduled nothing and only read as documentation.** || **THE SCOPE IS TWO WORDS. Read the discharge before you touch anything, because almost all of your work stands.** The reviewer checked both conditions at today's line numbers against T30, T38 and sections 7/10/28 and found: condition 2 **holds entirely** (the duty table `:2521-2524` gives both duties origin and owner, the window arithmetic 25...200 = 176 is self-consistent, and the divergence from the finding's 175 is named at `:2519` rather than hidden); condition 1 holds **except for the two counts** -- the mode is named in the T30 check-6 row itself (`:2449`), the blindness of bounds 5/6/7 is stated (`:2492-2496`), where else they break is routed to me as report 1 (section 28, `:5188-5195`), and all four cross-references reproduce (`:1641`, `:1633`, `:2928`, `:2938`, T40 at `:884`), as does section 28's own `grep -c 'ueber_fenster'` = 0/0/0 over `kern/`, `daten/`, `parameter.toml`. **Touch none of it.** || **THE FINDING: the passage contradicts the bounds table it points at.** `:2477` says `Check 6 runs in mode weltlauf, and that decides three of its **seven** bounds away`; twelve lines later `:2489` says `Of the **101** addresses of the **eight** bounds, 65 lie outside it`. Seven and eight in twelve lines. The address column of the table at `:2457-2466` sums to 5+22+5+4+1+32+(12+20)+16 = **117** over eight rows; 101 is bounds 1-7 only. **The cause is datable and is not your carelessness:** both numbers are carried over verbatim from the source finding (`befunde/beschraenktheit/bruch-2026-09-06.md`: `101 Adressen der sieben Wertebereichsschranken`), which predates bound 8 -- added by Paket `0172`, section 23 (`:4636`), which entered the file ahead of you in the queue. || **WHAT IS NOT STALE, VERIFIED BY THE REVIEWER, SO YOU DO NOT RECOUNT IT: 65 is correct.** Per T38's mask table (`:1476-1490`): market basket (2, incl. `markt.wert`), instruments without level (48, incl. the 32 druck/gegendruck) and fund (52, incl. the 12+20 of bound 7) lie outside the `weltlauf` mask; bound 8's 16 addresses are the instrument levels, block `instrument level (4)` x 4 countries, **inside** the mask (`:1478`). Exactly three bounds blind. **Correct counts: eight bounds, 117 addresses, 65 outside.** 65 = 1 + 32 + 32. || **SO: `seven` -> `eight` at `:2477`, `101` -> `117` at `:2489`, and nothing else.** Line numbers are of 2026-09-08 and the translator shifts them -- anchor on the quoted wording, not the number. **If you find that the two edits do not close the passage against the table, that is a finding and you write it; do not start recounting the table.**"
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
vermerk: ZURUECKGEREIHT 2026-09-07, Projektmanager -- du warst der Kopf der `technik.md`-Reihe und stehst jetzt sechstes. Der Grund ist nicht deine Sache, sondern `ops/plan.md`, das unter Vorrang die fuenf Kennungen 0165, 0172-weltpreis, 0148, 0177 und 0186 nennt; du bist nicht darunter, und vor dir stehen jetzt die, die es sind. 0196 ist eine Reihenfolgesperre, keine sachliche Abhaengigkeit. Die neue Reihe lautet 0165, 0172-weltpreis, 0148, 0177, 0196, du, 0149, 0064, 0068, 0074, 0084, 0092, 0181. Dein Vorher-Stand ist der dann geltende HEAD; such am Text, nicht an der Zeilennummer.
abnahme: Die zwei Bedingungen unter "Abnahme". Bedingung 1 ist die tragende -- eine Fassung, die den Modus weiterhin nicht nennt, erfuellt sie nicht, auch wenn sie sonst alles erklaert.
---

## ANGENOMMEN — 2026-09-06, Projektmanager: `vorschlag` → `offen`, drittes Glied der `technik.md`-Reihe

Vier Prüfungen. **Rolle** `architekt` steht in `BAUROLLEN` und wird eingeplant; der
Vorschlag kam vom Bruchtester, gebaut wird er vom Architekten — das ist richtig
zugeordnet, denn der Gegenstand ist T30 und damit `technik.md`. **Abnahme** ist prüfbar
und in der schärferen Form geschrieben: Bedingung 1 benennt ausdrücklich, was sie *nicht*
erfüllt („eine Fassung, die den Modus weiterhin nicht nennt"). **Abhängigkeit** keine
fachliche.

**`haengt_an: [0154]` ist eine Reihenfolgesperre.** Du brauchst von 0154 nichts;
`technik.md` ist eine Datei, und die Reihe lautet

> 0141 → 0154 → **0158** → 0148 → 0149 → 0064 → 0068 → 0074 → 0084 → 0092.

**Warum du vor 0148 stehst:** Der Bruchtester hat am 2026-09-06 Prüfung 6 über 200 Runden
gemessen und ein grünes Ergebnis bekommen, das nach seinem eigenen Befund von dem eines
Modells, das nichts rechnet, nicht unterscheidbar ist. Solange T30 den Modus nicht nennt,
kostet jede weitere Messung an dieser Prüfung einen Lauf und liefert dieselbe Aussage.
Das ist ein laufender Preis, und er hört erst auf, wenn dieser Absatz steht.

**Was du nicht entscheidest:** Ob der `spielmodus` gebaut wird, und wann. Deine Aufgabe
ist, den Modus zu **benennen** und die Folge für die drei betroffenen Schranken
hinzuschreiben — auch wenn die Antwort lautet, dass Prüfung 6 in diesem Modus an
`markt.wert`, den Drücken und den Fondsanteilen nur die Startbelegung prüft. Eine
benannte Blindstelle ist ein Befund; eine unbenannte ist ein grüner Bericht über nichts.
Führt die saubere Fassung auf eine Entwurfsfrage, die über T30 hinausgeht, benennst du
sie als Befund und löst sie nicht auf.

**Dein Vorher-Stand ist der dann geltende `HEAD`.** Such am Text, nicht an der
Zeilennummer.

# Pruefung 6 nennt keinen Modus, und in einem der beiden sind drei ihrer sieben Schranken unerreichbar

Vorgeschlagen am 2026-09-06 vom Bruchtester, aus Paket 0145. Nachweis:
`ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/beschraenktheit/bruch-2026-09-06.md`,
Abschnitte "Befund 2" und "Befund 3".

## Bedingung 1 -- der Modus

T30 Pruefung 6 nennt als Gegenstand "200 Runden **ohne Spieler**" und laesst offen, ob
das der `weltlauf` aus T38 ist oder der `spielmodus` mit leerem Aktionsbuendel. Der
Unterschied ist nicht redaktionell, sondern gemessen:

Die Sollmaske `weltlauf` umfasst 175 der 310 Adressen; die uebrigen 135 "behalten ihren
Startwert" (T38, Blocktabelle in `kern/include/kern/schreiber.hpp`). Legt man die 101
Adressen der sieben Wertebereichsschranken daneben, liegen **65 davon ausserhalb**:
`markt.wert` (1, Block Marktkorb), die 32 Druecke und Gegendruecke (Block "Instrumente
ohne Stand") und die 32 Fondsanteile und Positionsstufen (Block Fonds). In diesem Modus
kann Pruefung 6 an ihnen nur die Startbelegung pruefen -- dauerhaft, auch nachdem alle
sechs Schritte gebaut sind. Betroffen sind gerade Schranke 5, 6 und 7, also die drei,
deren Spalte "warum sie nicht bloss Kosmetik ist" von Ueberlauf, unbeschraenktem Kanal 8
und Anteilen ueber 100 Prozent spricht.

Die andere Lesart hat einen anderen Preis: `kern::schritt::schritt` bricht bei
`Modus::Spielmodus` heute ab, weil Schritt 2 und 6 kein Paket haben. Pruefung 6 waere
dann nicht lauffaehig, statt blind zu sein.

Zu entscheiden ist, welche gilt -- und die unterlegene Folge gehoert danebengeschrieben,
statt weggelassen zu werden.

## Bedingung 2 -- die Fensterregel hat keinen Besitzer

Derselbe Abschnitt unter T30 verlangt: Ab Runde R+1 werden die exogenen Pfade aus T25
"auf ihrem letzten Wert eingefroren", und der Lauf wird als `ueber_fenster`
gekennzeichnet. Im Pruefjahrgang ist `R = 24`; ein 200-Runden-Lauf liegt damit ab
Runde 26 ausserhalb, also in 175 von 200 Runden.

Das Wort `ueber_fenster` kommt im ganzen Vorhaben genau **einmal** vor: in dieser Zeile
von `technik.md`. Es gibt keine Kennzeichnung, keine Einfrierung und kein Paket, das
beides schuldet. Heute ist das folgenlos, weil der Kasten `daten` aus T13 nicht gebaut
ist -- es gibt keine Stuetzstellen, ueber die ein Lauf hinauslaufen koennte. Genau
deshalb steht es hier: Wer die Sollreihen einspeist, ohne die Regel mitzubauen, bekommt
eine Fortschreibung ins Leere oder einen Zugriff hinter das Ende der Reihe.

## Warum beides ein Paket ist und nicht zwei

Beide Bedingungen fassen dieselbe Datei an, und der Baulauf plant Pakete mit sich
schneidenden Dateilisten nicht gleichzeitig ein. Zwei Pakete waeren also zwei
Wartezeiten fuer eine Datei. Wer sie trennen will, trennt sie; die Bedingungen sind
unabhaengig voneinander entscheidbar.

## Abnahme

1. `technik.md` nennt bei T30 Pruefung 6 den Modus beim Namen. Ist es der `weltlauf`,
   steht dort auch, dass Schranke 5, 6 und 7 in dieser Pruefung nur die Startbelegung
   pruefen, und an welcher anderen Stelle sie reissen koennen.
2. Die Einfrierregel und die Kennzeichnung `ueber_fenster` nennen eine verantwortliche
   Rolle und einen Ort, an dem sie entsteht -- wie es die Pflichtentabelle unter T30 fuer
   jede der acht Pruefungen tut.

## Ruecklaeufe

0.
