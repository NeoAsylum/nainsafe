---
typ: pruefung
paket: 0039-zollzeile-konjunktursockel
pruefer: entwurf-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen nachgerechnet statt gelesen — Weg 1 gewählt und beide Alternativen mit Maß-2-Begründung verworfen, `schaden(l, zoll)` für den aktionslosen Zustand selbst ausgerechnet (null, wie angekündigt), und die 106 Lesezugriffe Zeile für Zeile gegen die Adressliste abgezählt.
befunde: 1
---

# Prüfung 0039 — die Zollzeile misst nur noch den Keil

Gegenstand ist `specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md` im Stand
von Commit `6537a9e` (2.138 Zeilen). Geurteilt ist gegen die drei Bedingungen im Abschnitt
*Abnahme* von `aufgaben/0039-zollzeile-konjunktursockel.md` und gegen nichts sonst.

## Bedingung 1 — eine Entscheidung, keine Aufzählung: **erfüllt**

| verlangt | gefunden |
|---|---|
| einer der drei Wege gewählt | **Weg 1** (Zollkeilanteil isolieren), gleichlautend an drei Stellen: Kopfnotiz Z. 35-43, Abschnitt *Warum die Zollzeile nur den Keil misst* Z. 775-777, Befundabarbeitung Z. 1888-1889. Kein vierter Satz, der einen anderen Weg offenhält |
| die beiden anderen mit Grund verworfen | Weg 2 in Z. 850-868 mit **zwei** Gründen (Blindheit gegenüber der Sektorwirkung; Rate ist kein Preis), Weg 3 in Z. 870-876 mit einem, der über den bekannten hinausgeht (der Sockel wächst mit dem nominalen Preisniveau und wäre damit auch für **Maß 3** eine Scheinverschiebung) |
| die Begründung nennt Maß 2 | Z. 812-822, Grund 1 von dreien, mit der Abnahmeform `max(Ek) ≤ 1,25 × min(Ek)` und dem Mechanismus: `gegenlobby_satz` skaliert Sockel und Aktionsantwort gemeinsam, also trägt der Sockel genau eine der drei Klassen |

**Nachgeprüft, nicht übernommen:** Der Selbstwiderspruch, den Weg 2 erzeugt hätte, ist an
seiner Quelle belegt. Z. 856 zitiert *„ein Zoll trifft Chinas Industrie über ihren hohen
`durchgriff` hart"*; der Satz steht im Wortlaut in Z. 146-148. Die Ablehnung stützt sich
also auf eine Zeile, die es gibt.

## Bedingung 2 — `schaden(l, zoll)` ohne Aktion ist ausrechenbar: **erfüllt**

Selbst gerechnet, ohne die Probe der Datei zu benutzen, aus Z. 728-746:

```
hub(DE, zoll)       = |380 − 380|                       = 0
keilhub(DE, s)      = mal_geteilt(welt.preis.<s>, 0, 10.000)   = 0    für s = 1 und 2
preishub_zoll(DE,s) = mal_geteilt(0, durchgriff(DE,s), 10.000) = 0
schaden(DE, zoll)   = Σ mal_geteilt(handelsvolumen(DE,s), 0, 10.000)  = 0
```

Das ist **null für jeden Weltpreis, jedes Handelsvolumen und jeden `durchgriff`** — die
Zahl, die Z. 927 und Z. 934-936 ankündigen. Der Nullpunkt hängt allein daran, dass `hub`
als Faktor eingeht und nicht als Summand; das ist ohne Kenntnis der Keilform nachprüfbar,
wie der Text behauptet.

**Die Gegenprobe mit Aktion stimmt ebenfalls**, Zeile für Zeile mit der Rundungsregel aus
T6 nachgerechnet: `11.000·50/10.000 = 55`; `10.400·50/10.000 = 52`;
`55·7.288/10.000 = 40,084 → 40`; `52·5.464/10.000 = 28,4128 → 28`;
`40.000.000·40/10.000 = 160.000`; `100.000.000·28/10.000 = 280.000`; Summe **440.000**.
Alle sieben Zahlen der Tabelle in Z. 917-927 sind reproduzierbar.

**Und die Zerlegung, auf der alles steht, ist algebraisch exakt.** Nachgerechnet aus der
Preisbildungsregel Z. 113-116 mit `landespreis = preis_alt`:

```
preis_neu − preis_alt = [wmz_neu·d + preis_alt·(10.000−d)]/10.000 − preis_alt
                      = d/10.000 · (wmz_neu − preis_alt)
```

und mit `wmz_neu = welt.preis_neu · (10.000 + zoll_neu)/10.000` aus Z. 165 zerfällt der
Klammerausdruck exakt in die beiden Summanden aus Z. 789-791 — die Summe der beiden ergibt
den Ausgangsausdruck zurück, ohne Restglied. Die Behauptung „exakt und nicht ungefähr"
(Z. 884) hält.

## Bedingung 3 — dieselbe, nachzählbare Zahl: **erfüllt**

Die **106** steht an vier Stellen und ist überall dieselbe: Kopfnotiz Z. 43, Lesetabelle
Z. 1069, Nachziehtabelle aus Paket 0021 Z. 1782, Nachziehtabelle aus Paket 0039 Z. 1799.
Kein Rest von 120 oder 112 als geltende Zahl — geprüft mit einem Suchlauf über die ganze
Datei; die vier Fundstellen von „120" und „112" sind sämtlich als Vorfassung
gekennzeichnet, und die 120 in Z. 1394/2116 ist die Profilzahl von Maß 2 und nicht diese.

**Jede Zeile der Lesetabelle einzeln abgezählt**, nicht summiert geglaubt:

| Zeile | behauptet | nachgezählt |
|---|---:|---|
| `lies_neu(…instrument.<i>.stand)` | 16 | 4 Länder × 4 Instrumente = 16 ✓ |
| `lies_neu(welt.preis.<s>)` | 2 | `daten/adressen.md` Nr. 239 und 240, Klasse 5 ✓ |
| `lies_neu(handel.<a>.<b>.<s>)` | 40 | `daten/adressen.md` Nr. **199 bis 238** = 40 ✓ |
| `lies_neu(…sektor.<s>.wertschoepfung)` | 12 | 4 Länder × 3 Sektoren = 12 ✓ |
| `lies_neu(land.<l>.staatsschuld)` | 4 | 4 Länder ✓ |
| `lies_alt(…instrument.<i>.stand)` | 16 | ✓ |
| `lies_alt(…instrument.<i>.gegendruck)` | 16 | ✓ |
| Summe | 106 | 16+2+40+12+4+16+16 = **106** ✓ |

**Die Entdopplung des Handelsblocks stimmt und ist der einzige nicht triviale Schritt:**
`handelsvolumen(l,s)` greift für 4 Länder × 4 Gegenüber × 2 Richtungen × 2 Sektoren
64-mal zu, aber nur auf 20 geordnete Gebietspaare × 2 Sektoren = 40 verschiedene Adressen;
die 24 Doppelungen sind die 12 geordneten Paare zwischen zwei spielbaren Ländern mal 2
Sektoren. `64 − 24 = 40`, und die Adressliste bestätigt es unabhängig.

**Übereinstimmung mit der Instrumententabelle** (Z. 761-766), je Zeile geprüft: `zoll`
braucht Weltpreise (2), Zollstand doppelt (Teil der 16+16) und den Handelsblock (40);
`leitzins` braucht `bip` (12) und `staatsschuld` (4); `haushalt` und `regulierung` nur
`bip`. Keine Zeile verlangt eine Adresse, die die Lesetabelle nicht führt, und keine Zeile
der Lesetabelle ist überzählig. `durchgriff` und `regulierung_last` fehlen dort zu Recht —
`durchgriff` ist nach Z. 284 Jahrgangskonstante, `regulierung_last` nach Z. 1781 ein
Schlüssel in `parameter.toml`.

**Beide Rechenwege zur 106 gehen auf:** `112 + 4 + 4 − 8 − 8 + 2` (Z. 1082) und
`112 + 8 − 16 + 2` (Z. 1911) ergeben dieselbe Zahl und beschreiben dieselbe Bewegung.

## Befund 1 — die Vergleichszahl 32.850.000 gehört nicht zu Zustand B

**Schwere: gering. Kein Rücklaufgrund** — sie betrifft keine der drei Bedingungen, sondern
einen Nebensatz derselben Tabelle, und sie ändert die Entscheidung nicht.

**Wo:** `spiel.md` Z. 937-939.

> „Zum Vergleich die Zahl der Vorfassung für **denselben Zustand B**, mit den Zahlen des
> Befunds (Weltpreis 10.400 gegen Vorrundenpreis 10.000, Handelsvolumen 1,5·10^9):
> **32.850.000** statt null."

**Wie man den Fehler erzeugt** — drei Schritte:

1. Aus der Tabelle darüber (Z. 919) das Handelsvolumen von Zustand B ablesen:
   40.000.000 für Sektor 1 und 100.000.000 für Sektor 2, zusammen **1,4·10^8**.
2. Daneben das Handelsvolumen legen, mit dem die Vergleichszahl gebildet ist:
   **1,5·10^9**. Das ist derselbe Satz, zehneinhalbmal so groß. Zustand B kann beide
   Werte nicht zugleich haben.
3. Die alte Vorschrift auf die Zahlen der Tabelle anwenden. Zustand B führt keinen
   `land.DE.sektor.<s>.preis` — die Eingabe der alten Zeile fehlt in der Tabelle
   vollständig. Setzt man dafür den Startindex 10.000 ein (Z. 121), ergibt sich:
   `wmz(DE,1) = 11.000·10.380/10.000 = 11.418`, `|11.418 − 10.000| = 1.418`,
   `preishub = 1.418·7.288/10.000 → 1.033`, Beitrag `40.000.000·1.033/10.000 = 4.132.000`;
   `wmz(DE,2) = 10.400·10.380/10.000 = 10.795`, `|10.795 − 10.000| = 795`,
   `preishub = 795·5.464/10.000 → 434`, Beitrag `100.000.000·434/10.000 = 4.340.000`.
   **Summe 8.472.000**, nicht 32.850.000 — Faktor 3,9.

**Die 32.850.000 selbst ist richtig**, nur für einen anderen Zustand: Sie stammt aus
Befund 1 der Prüfung vom 2026-09-02 (Sektor 2 allein, Weltpreisanstieg 400 Indexpunkte,
Handelsvolumen 1,5·10^9) und rechnet sich dort sauber nach — `5.464·400/10.000 → 219`,
`1,5·10^9·219/10.000 = 32.850.000`. Der Fehler ist die Zuschreibung „**denselben** Zustand
B", nicht die Zahl.

**Warum das die Entscheidung nicht berührt und deshalb kein Rücklauf ist:** Auch die
richtige Zahl für Zustand B, 8.472.000, ist das **Neunzehnfache** des Schadens, den ein
absichtlicher Zollschritt in Zustand A erzeugt (440.000). Der Sockel bleibt damit auch
nachgerechnet um Größenordnungen zu groß, das Argument aus Z. 812-822 trägt unverändert,
und Weg 1 bleibt begründet. Es ist eine falsche Beschriftung an einer richtigen Zahl.

**Warum es trotzdem ein Befund ist:** Die Tabelle in Z. 917-927 ist ausdrücklich die
Nachweisform für Bedingung 2 und trägt die Überschrift *Zwei Zustände, zwei Zahlen*. Wer
sie später als Regressionsfall benutzt — und dafür ist sie gebaut —, liest zwei Zahlen zu
einem Zustand, von denen nur eine aus ihm folgt. Die Reparatur ist ein Halbsatz: entweder
8.472.000 einsetzen und `preis_alt = 10.000` in die Tabelle aufnehmen, oder „für denselben
Zustand B" durch „für den Zustand des Befunds" ersetzen.

## Wonach ich außerdem gesucht und nichts gefunden habe

- **Ob `technik.md` widerspricht.** Die Datei nennt an keiner Stelle eine Lesezugriffszahl
  für Schritt 5 (Suchlauf über „Lesezugriffe", einziger Treffer ist T39 zum
  Lesezugriffs*paar*). Es gibt also keine 120, die stehen bliebe. Die Nachziehtabelle
  benennt sie richtig als nachzuziehen und ändert nichts — die Grenze des Pakets ist
  eingehalten, `git log` zeigt `technik.md` in `6537a9e` unverändert durch diesen Agenten.
- **Ob die neuen Namen definierte Eingaben haben.** Jeden Namen der neuen Formeln einzeln
  gesucht: `keilhub`, `preishub_zoll`, `hub`, `handelsvolumen`, `bip`, `schuld`,
  `durchgriff` (Z. 139 mit Bildungsregel), `welt.preis.<s>` (Adresse 239/240),
  `regulierung_last` (Z. 1781, `parameter.toml`), `schrittweite[zoll]` und
  `instrument_max[zoll]` (`technik.md` Z. 1392, `parameter.toml` Z. 868-886). Keiner ist
  nur verwendet. Einziger Grenzfall: `zollstand(l)` in Z. 165 hat keine eigene
  Definitionszeile — es ist aus dem Kontext eindeutig `land.<l>.instrument.zoll.stand`,
  geht in `schaden` nicht ein und ist damit keiner der drei Bedingungen zuzurechnen.
- **Die Einheitentabelle gegen jede neue Formel gelegt** (der produktivste Handgriff der
  letzten Läufe). `keilhub` = Klasse 5 × Klasse 3 / 10.000 → Klasse 5; `preishub_zoll` =
  Klasse 5 × Klasse 4 / 10.000 → Klasse 5; `schaden` = Klasse 2 × Klasse 5 / 10.000 →
  Klasse 2, wie T50 es verlangt. Klasse 4 als Anteil in Zehntausendsteln ist in
  `technik.md` Z. 2371 bestätigt. Kein vierter Skalenübergang, Klasse 1 nirgends berührt.
- **Ob eine Behauptung über eine fremde Datei stimmt.** Zwei geprüft, beide richtig:
  `welt.preis.1/.2` sind Nr. 239 und 240 in `daten/adressen.md`, und `technik.md` Z. 1030
  führt „Weltpreise | 2 | **ja**" in der Weltlaufmaske — die Aussage in Z. 1156-1159, die
  Formel ließe sich im Weltlauf mitrechnen, ist belegt.
- **Ob die Streichung des Sockels als Dämpfung fehlbeschrieben ist.** Die alte Größe war
  `|a + b|·d`, die neue ist `|a|·d`; „was wegfällt, ist der Summand ohne Verursacher"
  (Z. 801) ist für die vorzeichenbehaftete Zerlegung richtig und für den Betrag ungenau —
  bei gegenläufigen Vorzeichen kann die neue Zahl größer sein als die alte. Das ist **kein
  Befund**: Es spricht für die Wahl und nicht gegen sie, denn unter der alten Regel konnte
  ein Zollschritt durch den Sockel rechnerisch verschwinden. Der Aktionsanteil, um den es
  in Z. 883 geht, ist tatsächlich unverändert.
- **Ausdrücklich kein Befund**, nach der Ausschlussliste in `0001-entwurf-abnahme.md`: der
  Wert von `schrittweite[zoll]` (Z. 909 kennzeichnet ihn als Kalibrierung und schreibt die
  Prüfform ohne Zahl hin), `regulierung_last`, und die Frage aus Z. 1732, ob ein
  `gegenlobby_satz` alle vier Zeilen trägt — sämtlich Zahlen, die gemessen und nicht
  entworfen werden.
- **Die Lesart von Maß 2 in Z. 819-820.** Das Frontmatter (Z. 13) sagt „das beste
  Klassenergebnis ist höchstens 25 Prozent besser als das schlechteste", die Begründung
  formt daraus `max(Ek) ≤ 1,25 × min(Ek)`. Beide Lesarten sind vertretbar und
  unterscheiden sich (1,25 gegen 1,33); die Formel stand aber schon in der Fassung vom
  2026-09-02 und ist von diesem Paket nicht angefasst. Sie gehört nicht hierher — ich
  vermerke sie, damit der nächste Lauf sie nicht für neu hält.

## Vorgeschlagene Arbeit

`aufgaben/0053-partielaenge-r-entscheiden.md`, `status: vorschlag`. Nicht aus diesem Paket,
aber beim Nachrechnen erneut aufgefallen und inzwischen die älteste offene Entscheidung des
Entwurfs: `spiel.md` führt weiter `R = 24`, während `daten/deckungsbefund-1997.md` seit dem
2026-09-02 `R = 19` misst. Der Entwurf verlangt in Z. 1690 selbst ein eigenes Paket dafür.
