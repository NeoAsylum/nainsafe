---
typ: pruefung
paket: 0141-pruefliste-fuenftes-land
pruefer: entwurf-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Abnahmebedingungen einzeln nachgemessen -- die Liste Zeile fuer Zeile an reihen.toml und den Vorgaben T23-T26, T40 und T55-T61 verankert, der Bestandsschutz arithmetisch am Datei-Diff 565259c..95fb409.
befunde: 0
---

# Pruefung 0141 — Pruefliste fuenftes Land (Abschnitt 21, T62/T63)

**Gegenstand.** Der Lauf ist Commit `95fb409`, Elternstand `565259c`. Der Commit sammelt
den halben Arbeitsbaum ein (bekanntes Muster, Vorschlag 0131); belastbar ist der
Datei-Diff von `technik.md` ueber die Spanne: **229 Zeilen hinzugefuegt, 0 entfernt, ein
einziger Anfuege-Hunk** ab Zeile 3829. Der Arbeitsbaum ist mit `HEAD` identisch
(`git diff HEAD -- technik.md` leer).

## Bedingung 1 — die Liste ist abzaehlbar, der Leitzinsfall entschieden: erfuellt

**Die Tabelle in T62 fuehrt 19 Zeilen; `daten/reihen.toml` fuehrt 19 `[[reihe]]`-Bloecke**
(`grep -c '^\[\[reihe\]\]'` = 19). Jede vom Paket verlangte Reihe ist darin: drei
WDI-Sektorreihen (Zeile 2), Bevoelkerung (5), Erwerbstaetige (6), Produktivitaet (4),
Preisniveau (15), Leitzins (9), Wechselkurs (10), Staatsschuld (11), Haushaltssaldo (12),
BACI-Handelszeile gegen jedes andere Gebiet (14, als 20 Stroeme). Je Zeile stehen Quelle
mit Code, Fensterklasse und Lizenzstand.

**Jede Spalte gegen ihre Quelle gelegt, nicht gegen den Vermerk des Architekten:**

- **Lizenzstaende:** alle 19 gegen das Feld `lizenzurteil` der jeweiligen Reihe —
  unklar (1, 2, 5, 6, 7, 9, 11, 12), frei (3, 4, 8, 10, 14, 15), gesperrt (13). 1:1
  identisch. Die Fussnote 2 (frei-gegen-unklar beim IWF) steht woertlich in
  `zaehlung.lizenz.gegenrechnung` und im `offen`-Feld der Reihe 8 (HTTP 403, fuenf
  Anlaeufe, drei Rollen).
- **Quellen und Codes:** alle 13 eingebetteten Codes (NY.GDP.MKTP.KD, NV.*.TOTL.ZS x3,
  SP.POP.TOTL, SL.TLF.TOTL.IN, SL.*.EMPL.ZS x3, FP.CPI.TOTL.ZG, DISR_RT_PT_A_PT,
  PA.NUS.FCRF, GGXWDG_NGDP, GGXCNL_NGDP, TM.TAX.MRCH.WM.AR.ZS), die Datenfluesse
  `IMF.STA/MFS_IR 9.0.0` und `IMF.RES/WEO 9.0.0`, BACI Fassung 202601 (Etalab) und die
  Rueckfaelle (PWT bei 1, 5, 6; IWF IFS bei 8, 10) stimmen mit `codes`,
  `quelle_eingebettet` und `quelle_rueckfall` ueberein.
- **Fensterklassen gegen die Rollen:** Sollreihen ohne Fuellung nach T24 erste Schwelle
  (Z. 1690 ff.), exogene Pfade nach T25 (Bevoelkerung/Erwerbstaetige exogen, Z. 1713),
  Startjahr-Reihen nach T25 (Produktivitaet nur Startwert, Z. 1716). Das woertliche
  Reihe-11-Zitat („verkuerzt -- 1997 bis 2000 fehlen … erzwingt das Startjahr 2001")
  steht in `reihen.toml` Z. 1381; die Wahlzustaendigkeit des Spielentwerfers samt
  T40-Manifestzahl steht in T24 (Z. 1693–1695).
- **Alle Zaehlungen von Hand nachgerechnet:** Spaltensumme „neu" = 18 = `12 + 2S`;
  Stroeme 20 = Differenz der T55-Handelsformel `(L+1)L(S−1)` (60 − 40, selbst
  hergeleitet); Fensterklassen 27 + 5 + 6 = 38 = 18 + 20; Wertkosten 32·25+6 = 806,
  32·21+6 = 678, 5·25+33 = 158, 5·21+33 = 138, ohne Reihe 13: 781/133/657/117; die
  Quellen-Gegenrechnung 228 + 75 + 3 + 500 = 806 mit 12+3+3 = 18 Landesreihen; die
  „38 gegen 38"-Falle gegen T57 (`5S+23`, Z. 3325/3431), bei L = 5 korrekt 42;
  Sollreihen-Zuwachs S+4 = 7 gegen T59 `L_R(S+4) − n` (Z. 3584); Pruefgegenstands-Zuwachs
  4 gegen T59-Formel und T58-Klassenwechsel (Z. 3560 ff.); Herkunftsbloecke 12+16 = 28
  nach T61 Regel 1, mit fuenftem Land 15+16 = 31; Stellen 8+2 = 10 gegen
  `lizenzbefund-reihen.md` (acht Stellen unter Klaerung 4, genau eine geprueft: Destatis).
- **Die Aemter-Behauptung als Vollstaendigkeitsbehauptung geprueft:** Grep ueber alle
  `wortlaut`-Felder nach `National Statistical|Central Bank|official statistics` trifft
  ausschliesslich die Reihen 1, 2 und 5; der Reihe-5-Wortlaut (Z. 912) nennt NSOs und
  keine Notenbank — exakt wie in T62 behauptet. Die Reihe-2-Ausweichlage (PWT ohne
  sektorale Wertschoepfung, OECD ungeklaert, Eurostat fuer Nicht-EU gesperrt) steht
  woertlich in `quellenwahl_grund` (Z. 664).

**Der Leitzinsfall (T63) ist entschieden und begruendet, nicht offengelassen:** gewaehlt
ist ein Ersatzverfahren (erst `LAND.*.A` abrufen, dann Stufen 2–4 nach T60), keine
Ersatzquelle im Voraus, kein Ausschlusskriterium. Jeder tragende Verweis unabhaengig
geprueft: die Stufenfolge, die Union-Regel der Stufe 3 und die Sperre fuer die heutigen
Vier stehen in T60 (Z. 3650–3731); „eine Sollreihe traegt ausschliesslich Stufe 1" in
Z. 3733; die Manifest-Doppelbuchung in T61 Regel 5; die Pruefgegenstands-Aufzaehlung ohne
Leitzins in `reihen.toml` `[zaehlung.pruefgegenstaende]` (Z. 405–419, „Der Leitzins
steht in keiner dieser fuenf Zeilen"); die Zinsnachmessung USA 9 / BRA 7 / DEU 11 (Code
fehlt) / CHN 0 in `nachmessung-zinsreihen-2026-09-05.md` Z. 25–30; die WDI-Lizenzlage
(fuenf unklar, eine gesperrt von acht) in T60 und deckungsgleich in den
`lizenzurteil`-Feldern; T26 erster Fall (kein Zollpfad, konstanter Zoll, zwei statt drei
verankerte Instrumente) in Z. 1752.

## Bedingung 2 — der Bestand bleibt unberuehrt: erfuellt

Eigene Zaehlung, nicht die des Vermerks: `grep -c '310'` = **44**, `grep -c 'vier
Länder'` = **7** im Nachher-Stand. In den 229 hinzugefuegten Diff-Zeilen kommt keines der
beiden Muster vor (`grep -c '^+.*310'` = 0, `grep -c '^+.*vier Länder'` = 0), und der
Diff entfernt null Inhaltszeilen. Vorher = nachher folgt damit arithmetisch: 44 und 7,
staerker als jeder Vorher-Grep, weil der Anfuege-Hunk den Bestand nachweislich nicht
beruehrt (Lehre aus dem 18. Lauf).

## Wonach ich gesucht habe und nichts fand

- Sonderfall-Wanderung markanter Zahlen (Lehre 19. Lauf): die 38, die 27 und die 40
  kommen je zweimal mit verschiedener Bedeutung vor; alle Einsetzungen einzeln
  nachgerechnet, keine gewandert — der Abschnitt benennt die 38/38-Falle selbst korrekt.
- L/L_R-Verwechslung in den neuen Formeln: keine (Stroeme und Landesblock in `L`,
  Sollreihen-Bezug in `L_R`, konsistent mit T59 Z. 3610 ff.).
- Nebenzahlen in Selbstberichten: die Behauptung „44 und 7 Zeilen" des Vermerks stimmt
  mit meiner unabhaengigen Messung ueberein; „zehn Stellen und eine Pruefung" stimmt
  gegen den Lizenzbefund.
- Widerspruch zur Fensterfrage: Der Auftrag nennt „ab 2001", das Dokument fuehrt
  1997–2021. Der Widerspruch steckt in der Vorgabe, nicht in der Lieferung: Die Liste
  ist in `R` parametrisch und beziffert **beide** Lesarten (R = 24 und R = 20); die Wahl
  gehoert nach T24 dem Spielentwerfer. Kein Ruecklauf — ein Ruecklauf verlangte vom
  Bauagenten eine Wahl, die ihm nicht zusteht. Der Punkt ist die offene Arbeit von 0064.

## Beobachtungen unterhalb der Befundschwelle

1. T62 Zeile 16 nennt den Lizenzstand „geerbt", `reihen.toml` fuehrt fuer Reihe 16
   `lizenzurteil = "unklar"` — der Sache nach identisch (erbt von 1 und 2, beide
   unklar); kein Zahlwiderspruch.
2. Die zwei Mehrlieferungen, die der Vermerk selbst anzeigt (Fensterklasse aus der
   Rolle; Urteilsspalte), verletzen keine Vorgabe: „Was nicht dazugehoert" nennt sie
   nicht, und sie aendern den Bestand nicht. Kein Uebergriff.
3. Der Vorspann-Drift waechst durch diesen Lauf weiter (hoechste vergebene Nummer jetzt
   T63, naechste freie T64, gegen „T1 bis T53" in Z. 45). Das ist bereits Paket
   `0181-vorspann-nummernbereich-und-freie-nummer`, dessen Abnahme selbstmessend
   formuliert ist („die Zahl folgt deiner Zaehlung, nicht diesem Paket") und den neuen
   Stand damit automatisch erfasst. Nichts zu veranlassen.
