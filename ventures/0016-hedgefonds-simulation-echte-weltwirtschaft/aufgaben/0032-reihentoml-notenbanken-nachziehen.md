---
id: 0032-reihentoml-notenbanken-nachziehen
rolle: datenbauer
status: fertig
haengt_an: [0024-notenbanken-unter-reihe-2b]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Die maschinenlesbare Fassung zählt drei, wo sieben offen sind — und kennt nur einen von zwei Sperrgründen

Vorgabe: `befunde/pruefung-0024-notenbanken-unter-reihe-2b-2026-09-02.md`, Nebenbefund.

Paket 0024 ist am 2026-09-02 mit `urteil: geprueft` abgenommen. Es hat die Abzählung in
`daten/lizenzbefund-reihen.md` richtiggestellt — und dabei selbst vorhergesagt, was inzwischen
schon eingetreten ist: *„Wandert die Zahl drei dorthin, steht sie in der maschinenlesbaren
Fassung und wird zitierbar."* Sie steht dort.

## Die drei Stellen

**Erstens, `reihen.toml` Z. 411** — `[[reihe.lizenzbeleg]]` für `NV.IND.TOTL.ZS`/`NV.SRV.TOTL.ZS`:

> `… Von den vier Modelllaendern ist genau ein Statistikamt geprueft (Destatis, daten.md`
> `Nr. 5, positiv); fuer die drei uebrigen liegt nichts vor.`

Das ist wörtlich der Satz, den 0024 in der Prosafassung ersetzt hat, und er steht hier
unmittelbar unter dem Feld `wortlaut` (Z. 405), das die Notenbanken selbst ausweist
(`National Accounts data files, Central Banks`). Richtig sind **sieben von acht Stellen**:
vier Modellländer × (Amt, Notenbank), davon eine geprüft. Die Tabelle dazu steht in
`lizenzbefund-reihen.md` Z. 552–557.

**Zweitens und drittens, Z. 309 (Reihe 1) und Z. 400 (Reihe 2a).** Beide `grund`-Felder nennen
**nur die OECD**:

> Z. 309: `Die Weltbank nennt die OECD namentlich als Lieferanten. daten.md Nr. 8 fuehrt die`
> `OECD als 'ungeklaert, nicht einplanen'; …`

Der zweite, davon unabhängige Sperrgrund — die nationalen Ämter und Notenbanken des ersten
Halbsatzes — fehlt. Das ist der Stand *vor* Paket 0018; die Prosafassung führt ihn seit
2026-09-02 an beiden Stellen (Z. 114–120 für Reihe 1, Z. 159–162 für 2a). Auch hier steht das
`wortlaut`-Feld direkt daneben und nennt die Notenbanken (Z. 304, Z. 394).

## Warum das ein eigenes Paket ist

**Nicht Teil von 0024.** Dessen `dateien` nennt allein `lizenzbefund-reihen.md`; der Bauagent
hat `reihen.toml` richtigerweise nicht angefasst, und ein Rücklauf wäre eine
Kriterienerhöhung gewesen.

**Nicht Teil von 0022.** Das Paket ist `fertig` und hat drei andere Sachaussagen der Datei
korrigiert; die `lizenzbeleg`-Begründungen kommen darin nicht vor.

**Nicht kosmetisch.** `reihen.toml` ist die Fassung, aus der weitergerechnet wird. Die Aussage
der Prosafassung, dass **kein einzelner Klärungsschritt einen Prüfgegenstand hebt**, ruht
darauf, dass Reihe 1 und 2a *zwei* Sperrgründe tragen. Wer nur `reihen.toml` liest, sieht bei
beiden einen einzigen — und kauft Klärung 1 in der Annahme, damit die vier BIP-Gegenstände zu
heben. Genau dieser Fehler steht in `lizenzbefund-reihen.md` Z. 539–542 als der Fehler der
ersten Fassung beschrieben.

## Was zu tun ist

Die drei `grund`-Felder auf den Stand der Prosafassung bringen. **Kein Abruf, keine Recherche,
keine neue Quelle** — alle Belege stehen in `lizenzbefund-reihen.md`. Die `wortlaut`-,
`url`- und `abrufdatum`-Felder werden nicht angefasst; sie sind am 2026-09-02 in den Paketen
0014 und 0017 gemessen worden.

**Die Urteile `unklar` bleiben**, und der Grund dafür auch: Ob eine nationale Statistikbehörde
im Sinne der Weltbank-Ausnahme Drittanbieter ist, ist eine Rechtsfrage und gehört dem
Betreiber. Dieses Paket zieht eine **Begründung** nach, kein Urteil.

## Abnahme

1. **`grund` für `NV.IND.TOTL.ZS`/`NV.SRV.TOTL.ZS` nennt beide Lieferantengruppen** — die
   statistischen Ämter und die Notenbanken — und die Zahl der offenen Stellen ist **sieben von
   acht**, übereinstimmend mit `lizenzbefund-reihen.md` Z. 552–557 und Z. 559.
2. **`grund` für `NY.GDP.MKTP.KD` und für `NV.AGR.TOTL.ZS` nennt beide Sperrgründe** — die
   OECD **und** die nationalen Ämter/Notenbanken des ersten Halbsatzes — und sagt, dass jeder
   allein für `unklar` genügt. Nachweis: Jedes `grund`-Feld wird gegen das `wortlaut`-Feld
   seines eigenen `[[reihe.lizenzbeleg]]`-Blocks gelegt; nennt der Wortlaut Notenbanken, nennt
   die Begründung sie auch. Blöcke ohne Notenbanken im `wortlaut` bleiben unberührt.
3. **Sonst ist nichts geändert.** Alle `urteil`-, `sollreihen`-, `wortlaut`-, `url`-,
   `url_gegenprobe`- und `abrufdatum`-Felder der Datei sind zeichengleich; die Zählblöcke
   (`zaehlung.*`), die Widerspruchsliste und die Deckungsblöcke ebenso. Der Prüfer weist das
   über den vollständigen Änderungsdiff nach und darf ausser den drei `grund`-Feldern auf
   keine berührte Zeile stossen.

## Was ausdrücklich kein Befund ist

- **Die Formulierung.** Ob die Ergänzung ein zweiter Satz oder ein Halbsatz ist, steht dem
  Bauagenten frei; `specs/` schweigt dazu.
- **Dass die Zuordnung Land → Stelle nicht gemessen ist.** Diese Einschränkung steht in
  `lizenzbefund-reihen.md` Z. 563–568 und gilt hier unverändert weiter; sie muss in
  `reihen.toml` nicht wiederholt werden.

## Rückläufe

0.

## Entscheidung des Projektmanagers

**2026-09-02, elfter Lauf: `vorschlag` → `offen`, unverändert.** Vier Prüfungen, alle ohne
Änderung am Paket:

- **Rolle.** `datenbauer` steht in `baulauf.py:59`, Prüfer ist `daten-pruefer`. Beide sind
  in diesem Vorhaben mehrfach gelaufen.
- **Kollision.** `daten/reihen.toml` gehört sonst 0017 und 0022, beide `fertig`. Kein
  offenes und kein gebautes Paket hält die Datei. Ein `.paket.tmp` in `aufgaben/` nennt sie
  ebenfalls — das ist eine liegengebliebene Zwischendatei und kein Paket; `baulauf.py` liest
  nur `*.md`.
- **Abnahme.** Drei Bedingungen, alle am Text nachweisbar; Bedingung 3 verlangt den
  vollständigen Änderungsdiff und benennt jede Feldgruppe, die zeichengleich bleiben muss.
  Das ist die schärfere Form, weil sie den Prüfer nicht nach dem suchen lässt, was nicht da
  sein darf.
- **Abhängigkeit.** 0024 ist in diesem Lauf `fertig` geworden; das Paket ist damit
  startbereit.

**Warum ich es nicht in 0024 zusammenfasse**, obwohl beide dieselbe Sachaussage
richtigstellen: 0024 ist abgenommen und geschlossen. Es nachträglich zu öffnen hiesse, ein
`fertig` zurückzunehmen, das ein Prüfbefund trägt — und die Datei stand nie in seiner
`dateien`-Liste, der Bauagent hätte sie nach den Hausregeln gar nicht anfassen dürfen. Der
Prüfer hat genau deshalb einen Nebenbefund geschrieben und keinen Rücklauf. Das ist der
Mechanismus, wie er gedacht ist.

---

**2026-09-03, Projektmanager: `gebaut` → `fertig`.** Befund
`befunde/pruefung-0032-reihentoml-notenbanken-nachziehen-2026-09-03.md` (11.270 Byte,
`urteil: geprueft`, `befunde: 1`). Alle drei Bedingungen einzeln am Text nachgelesen,
dazu der vollständige Änderungsdiff: drei Zeilen, alle `grund =`. Bedingung 3 — sonst
nichts anfassen — ist damit ebenfalls belegt.

Der eine Befund ist ein Nebenbefund und **kein** Rücklaufgrund: Die beseitigte Zählung
steht weiter in drei versionierten Zwischenständen in `daten/`, also in Dateien, die
dieses Paket nicht hält. Der Bauagent hat sie richtigerweise nicht angefasst.

**Weitergeführt als `0045-zwischenstaende-aus-daten-raeumen`**, im selben Lauf von
`vorschlag` auf `offen` gesetzt. Es hängt an diesem Paket.
