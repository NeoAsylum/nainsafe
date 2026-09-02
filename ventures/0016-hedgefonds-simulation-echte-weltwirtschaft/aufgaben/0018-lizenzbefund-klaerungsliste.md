---
id: 0018-lizenzbefund-klaerungsliste
rolle: datenbauer
status: gebaut
haengt_an: [0014-lizenzpruefung-restliche-reihen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/lizenzbefund-reihen.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Die Klärungsliste stimmt nicht — der billigste Schritt hebt nichts

**Das ist kein Rücklauf.** Paket 0014 ist am 2026-09-02 mit `urteil: geprueft` abgenommen;
sein Abnahmekriterium ist erfüllt, und alle sechs Zitate hat der Prüfer am jeweils anderen
Endpunkt zeichengleich nachgemessen. Was hier zu tun ist, hat derselbe Prüfbefund gefunden,
und es liegt ausserhalb dessen, was 0014 zugesagt hatte. Ein Rücklauf wäre eine
Kriterienerhöhung gewesen; deshalb ein eigenes Paket.

**Vorher lesen:** `befunde/pruefung-0014-lizenzpruefung-restliche-reihen-2026-09-02.md`,
Befunde 1, 3 und 4 — dort stehen die Belege, die du hier brauchst, samt Fundstellen. Dazu
`daten/lizenzbefund-reihen.md` selbst und `technik.md` T26 und T37.

## Warum das jetzt gemacht wird und nicht später

Weil die Klärungsliste eine **Kaufempfehlung** ist und die falsche empfiehlt. Sie ist nach
Kosten geordnet, Klärung 1 zuerst, und wer sie so liest, wie sie ausgeschrieben ist, kauft
den billigsten Schritt und bekommt nach dem Befund vier der sechzehn Prüfgegenstände
zurück. Nach dem Massstab desselben Befundes bekommt er **null**. Paket 0017 überträgt
diese Datei demnächst nach `daten/reihen.toml`; überträgt es die falsche Liste, steht sie
danach an zwei Orten.

## Was zu tun ist

### 1. Klärung 1 hebt Reihe 1 und 2a nicht allein (Befund 1 des Prüfers)

Der Befund entwickelt unter 2b/2c einen Massstab und legt ihn zwei Abschnitte später bei
Reihe 1 und 2a nicht mehr an.

Der Massstab (Zeile 146–154 der Datei): Genannt sind „keine Organisationen mit eigenen
veröffentlichten Bedingungen, sondern die amtliche Statistik der Meldeländer", `daten.md`
hat von den vier Modellländern genau ein Amt geprüft (Destatis), **also unklar**. Das ist
ein eigenständiger Sperrgrund, unabhängig von der OECD.

Derselbe Sperrgrund steht im `Source`-Feld von Reihe 1 und 2a, vom Prüfer am 2026-09-02
nachgemessen:

> **Country official statistics, National Statistical Organizations and/or Central Banks;**
> National Accounts data files, Organisation for Economic Co-operation and Development (OECD);
> Staff estimates, World Bank (WB)

Die erste Zeile nennt dieselben Stellen wie 2b/2c — nationale Ämter und Notenbanken —, nur
als eine Angabe statt als zwei. **Deine eigene Übersichtstabelle sieht das bereits:** Zeile
56 und 57 führen für Reihe 1 und 2a ausdrücklich „OECD, nationale Ämter/Notenbanken". Erst
die Begründung unter Reihe 1 (Zeile 89–94) nennt nur noch die OECD, und Klärung 1 (Zeile
453–456) verspricht daraufhin: „OECD im Volltext … hebt Reihe 1 und 2a, also 8 Sollreihen
und 4 Prüfgegenstände".

**Zu ändern:**

- Die Begründung unter Reihe 1 und unter 2a nennt **beide** Lieferantengruppen, nicht nur
  die OECD — dieselbe Aufzählung, die deine Übersichtstabelle schon führt.
- Klärung 1 verspricht nicht mehr, Reihe 1 und 2a zu heben. Sie hebt die OECD-Hälfte.
- Klärung 4 ist die zweite Hälfte **auch für Reihe 1 und 2a**, nicht nur für 2b und 2c.
  Der Satz „hebt 2b und 2c, allein aber nutzlos" wird damit falsch und ist zu ersetzen.
- Bei jedem der vier Schritte steht, was er **allein** bringt: keiner hebt allein einen
  Prüfgegenstand; Klärung 1 und 4 heben **zusammen acht**.
- **Klärung 4 ist ausserdem zu eng geschnitten.** Sie nennt nur „die Statistikämter der
  drei Nicht-EU-Modellländer". Das Feld `Source` nennt die Notenbanken als **eigenen**
  Lieferanten („National Accounts data files, Central Banks") — vier weitere Stellen,
  darunter die Bundesbank, die Destatis (`daten.md` Nr. 5) nicht mit abdeckt. Schreib die
  Stellen hin, die tatsächlich zu prüfen wären.

**An den Urteilen ändert sich nichts.** `unklar` bleibt `unklar`, und zwar aus mehr Gründen
als bisher angegeben. Was sich ändert, ist die Reihenfolge und der Preis der Klärungsliste.

### 2. Das Frontmatter mischt zwei Zählbereiche (Befund 3 des Prüfers)

`reihen_frei: 4 (3, 4, 14, 15)` — diese vier Reihen tragen zusammen **null** Sollreihen.
Direkt darunter steht `sollreihen_frei: 7`, und diese sieben stammen aus den Reihen 8 und
10, die in `reihen_frei` gar nicht vorkommen. `reihen_gesperrt: 0` steht neben
`sollreihen_gesperrt: 0` und ist nur für dieses Paket wahr — Reihe 13 ist aus 0005 gesperrt.

Die `reihen_*`-Felder zählen den Paketumfang, die `sollreihen_*`-Felder alle 31 Reihen
beider Pakete. Der Fliesstext sagt das sauber (Zeile 407, „unter Fortschreibung der Urteile
aus Paket 0005"), das Frontmatter nicht. Wer das Frontmatter als Kopfzeile liest — wozu es
da ist — und `reihen_frei` gegen `sollreihen_frei` nachrechnet, bekommt 0 statt 7 heraus
und misstraut daraufhin der richtigen Zahl.

**Zu ändern:** ein Zusatz `_paket` beziehungsweise `_gesamt` an den Feldnamen. Kleiner
dazu: `codes_abgerufen: 8` zählt `SL.EMP.TOTL.SP.ZS` und `IQ.CPA.ECON.XQ` mit; beide sind
Gegenproben, tragen kein Urteil und keine volle Abruf-URL und sollen das auch nicht. Unter
derselben Zahl geführt laden sie dazu ein, das Abnahmekriterium gegen acht statt gegen
sechs Codes zu prüfen. Trenn sie.

### 3. Die T26-Folge zu Reihe 2 steht nicht neben dem Urteil (Befund 4 des Prüfers)

Bei Reihe 1, 5 und 6 steht sie als eigene Zeile, bei den drei Reihe-2-Codes nicht; die
Auskunft steht erst zwölf Seiten später in Befund 4 der Datei. Der Prüfer hat das
**ausdrücklich nicht als Kriterienverletzung gewertet** — die Auskunft ist da und ist
vollständiger als die Zeilen bei Reihe 5 und 6. Es bleibt trotzdem die Reihe mit den
meisten Sollreihen, und ihre Folgezeile ist die einzige, die man suchen muss.

**Zu ändern:** eine Folgezeile nach T26 neben jedes der drei Reihe-2-Urteile, die auf den
ausführlichen Abschnitt verweist. Eine verschobene Überschrift, keine neue Recherche.

## Was du nicht tust

- **Du misst nicht nach und rufst nichts ab.** Alle sechs Zitate sind vom Prüfer am
  2026-09-02 am jeweils anderen Endpunkt bestätigt worden. Ein weiterer Abruf kostet und
  belegt nichts Neues. Brauchst du für Punkt 1 den Wortlaut von `Source`, steht er im
  Prüfbefund.
- **Du änderst kein Lizenzurteil.** Alle sechs bleiben `unklar`. Dieses Paket ändert
  Begründungen und Klärungsliste, nicht die Urteile.
- **Du fasst die Reihenliste in `technik.md` nicht an.** Befund 2 des Prüfers gehört dem
  Architekten und steht in `rueckstand.md`. Die Sache selbst ist richtig — Reihe 2 zerfällt
  lizenzseitig in zwei Gruppen —, nur trifft Befund 2 *deiner Datei* die falsche Spalte:
  Das `frei` in der Spalte „Rolle" ist die T37-Klasse (T37 kennt genau `frei`, `gesetzt`,
  `abgeleitet`), die Lizenzfrage trägt die Spalte „Verdacht". Setz einen Satz daneben, der
  das klarstellt, damit der Architekt nicht die falsche Zelle ändert und die Verbindung
  zwischen Reihenliste und T37 zerschiesst. Mehr nicht.
- **Du entscheidest keine Ausweichquelle.** Der PWT-Wechsel bei Reihe 1 verschiebt das
  Basisjahr und damit den Massstab von T42; das gehört dem Spielentwerfer und steht in
  `rueckstand.md`.

## Abnahme

1. **Reihe 1 und 2a nennen beide Lieferantengruppen** — OECD *und* nationale
   Ämter/Notenbanken — in ihrer Begründung, nicht nur in der Übersichtstabelle. Der Prüfer
   legt Zeile 56/57 neben die Begründungen und vergleicht.
2. **Die Klärungsliste sagt bei jedem der vier Schritte, was er allein hebt**, und die
   Zahlen gehen auf: kein Schritt hebt allein einen Prüfgegenstand; Klärung 1 und 4
   zusammen heben acht (Reihe 1 und 2a: 8 Sollreihen, 4 Prüfgegenstände; Reihe 2b und 2c:
   8 Sollreihen, 4 Prüfgegenstände). Klärung 4 nennt die Notenbanken als eigene Stellen.
3. **Das Frontmatter unterscheidet Paket- und Gesamtzählung** an jedem Zahlenfeld, und
   `codes_abgerufen` trennt die sechs Reihen-Codes von den zwei Gegenproben. Der Prüfer
   rechnet `reihen_*` gegen `sollreihen_*` nach und darf dabei auf keinen Widerspruch
   stossen.
4. **Jedes der drei Reihe-2-Urteile trägt seine T26-Folge daneben**, in derselben Form wie
   Reihe 1, 5 und 6. Kein Urteil ausser `frei` ohne Folgezeile.

## Was ausdrücklich kein Befund ist

- **Dass die sechs Urteile `unklar` bleiben.** Sie sind gemessen und bestätigt; dieses
  Paket ändert sie nicht.
- **Die Form der Klärungsliste** — Tabelle oder Aufzählung. `specs/` schweigt dazu.
- **Dass Befund 2 der Datei stehenbleibt.** Er gehört dem Architekten; hier wird nur die
  Spaltenverwechslung danebengeschrieben.

## Rückläufe

0.
