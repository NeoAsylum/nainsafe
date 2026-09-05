---
typ: pruefung
paket: 0018-lizenzbefund-klaerungsliste
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle vier Bedingungen des Abschnitts "Abnahme" einzeln gegen die geaenderte Datei gelegt — Uebersichtstabelle gegen Begruendung (1), jeden der vier Klaerungsschritte gegen die Sollreihen- und Pruefgegenstandszahlen zurueckgerechnet (2), alle zwoelf Frontmatter-Zahlenfelder gegeneinander und gegen die Abschnittstabellen nachgezaehlt (3), jedes Urteil der Datei auf eine T26-Folgezeile abgesucht (4)
befunde: 1
---

# Alle vier Bedingungen erfüllt — ein Nebenbefund an derselben Stelle, an der das Paket repariert hat

**Prüfgegenstand:** `daten/lizenzbefund-reihen.md`, Fassung nach Paket 0018.
Zeilenangaben unten beziehen sich auf diese Fassung (650 Zeilen).

**Vorbemerkung zum Commit.** Die Änderung an der Datei steckt in `efac2b1`, dessen
Betreff `datenbauer: 0015-adressen-markierungssatz` lautet; der Commit mit dem Betreff
`0018` (`b324cce`) berührt nur `notizen/datenbauer.md`, und `46ddb22` (Betreff `0009`)
trägt die letzte Formatierungsrunde an der Klärungsliste nach. Der Commit-Betreff ist
für dieses Vorhaben also **keine** verlässliche Zuordnung zum Paket. Das ist kein Befund
gegen den Datenbauer — der Inhalt ist vollständig da —, aber der nächste Prüfer sollte
nicht nach `git log --oneline -- <datei>` gehen. Fundstelle für die Zuordnung ist
`ueberarbeitet: 2026-09-02 (Paket 0018-…)` in Zeile 6 und der Änderungssatz
`git diff efac2b1^ HEAD -- <datei>`, der genau 29 Zeilen ersetzt: die acht
Frontmatter-Zahlenfelder, die Begründung unter Reihe 1, das Urteil unter 2a und die
gesamte Klärungsliste. **Keine der sechs `Source`-Zitatzeilen ist angefasst worden** —
die Messungen aus 0014 tragen unverändert, und ich habe deshalb wie beauftragt nichts
neu abgerufen.

---

## Kriterium 1 — Reihe 1 und 2a nennen beide Lieferantengruppen: **erfüllt**

Die Übersichtstabelle führt in Zeile 71 und 72 für beide Codes „OECD, nationale
Ämter/Notenbanken". Danebengelegt:

- **Reihe 1**, Zeilen 104–125: die Begründung ist in zwei nummerierte Gründe geteilt —
  „1. **Die OECD** …" (Zeile 108) und „2. **Die nationalen Ämter und Notenbanken** der
  Meldeländer, im ersten Halbsatz genannt" (Zeile 114) — mit dem Zusatz „und **keine
  einzige Notenbank**" (Zeile 118) und dem Satz „Beide Gründe stehen nebeneinander,
  keiner ersetzt den anderen" (Zeile 122).
- **Reihe 2a**, Zeilen 159–162: „aus **beiden** Gründen: die OECD (`daten.md` Nr. 8,
  ungeklärt) **und** die nationalen Ämter/Notenbanken des ersten Halbsatzes (von vier
  Modellländern ein Amt geprüft, keine Notenbank). Jeder Grund allein genügt; die
  Klärung der OECD allein hebt 2a nicht."

Der Änderungssatz zeigt, dass genau die alte Fassung ersetzt wurde, die nur die OECD
nannte (gelöschte Zeilen: „**Begründung:** Die Weltbank nennt die OECD namentlich …" und
„**Urteil: unklar**, Begründung wie dort (OECD, `daten.md` Nr. 8)").

Gegenprobe an der Belegstelle: `daten.md` Nr. 8 ist die OECD und lautet dort
„ungeklaert, nicht einplanen" (`specs/…/daten.md:219`), Nr. 5 ist Destatis
(`daten.md:158`). Beide Verweise stimmen.

## Kriterium 2 — Klärungsliste sagt je Schritt, was er allein hebt, und die Zahlen gehen auf: **erfüllt**

Die vier Schritte tragen alle die Zeile „Allein: …" (Zeilen 513, 519, 571, 579):

| Schritt | allein: Sollreihen | allein: Prüfgegenstände |
|---|---:|---:|
| Klärung 1 (OECD) | 0 | 0 |
| Klärung 4 (Ämter **und** Notenbanken) | 8 (2b, 2c) | 0 |
| Klärung 2 (IWF) | 8 (Reihe 9, 11) | 0 |
| Klärung 3 (ILO) | 0 | 0 |

**Kein Schritt hebt allein einen Prüfgegenstand** — als Satz über der Liste ausgeschrieben
(Zeile 504) und in jeder der vier Zeilen einzeln wiederholt.

**Nachgerechnet, nicht abgeschrieben.** Ich habe die Summanden einzeln aus den
Abschnittstabellen geholt, nicht aus der Summenzeile des Dokuments:

- Klärung 1 + 4 zusammen: Reihe 1 (4 Sollreihen, Zeile 138) + 2a (4, Zeile 168) = 8 mit
  4 Prüfgegenständen; 2b + 2c (4 + 4 = 8, Zeile 200) mit 4 Prüfgegenständen. Summe
  16/8 — genau die Zahlen, die das Kriterium nennt, und genau die Tabelle in Zeile
  528–532.
- Die Probe des Dokuments (Zeile 583): 16 + 8 (Klärung 2) = 24. Gegengerechnet gegen die
  Zusammenfassung Zeile 460 — Reihe 1 (4) + Reihe 2 (12) + Reihe 9 (4) + Reihe 11 (4) =
  24. Stimmt.
- Prüfgegenstände: 8 gehoben + 7 gesichert + 1 Handelsblock = 16. Gegengerechnet gegen
  die T37-Tabelle in `technik.md:1677–1684`: 4 + 4 + 4 + 3 + 1 = 16. Stimmt, und die
  Zeile „die drei Anteilsreihen des Landes, **alle drei** müssen bestehen" steht dort
  wörtlich (`technik.md:1680`) — die Begründung dafür, dass Klärung 4 allein null
  Prüfgegenstände hebt, trägt.
- Die Kaskade in Zeile 485–489 (16 → 8 → 1) rechnet ebenfalls auf: 16 − 4 − 4 = 8,
  8 − 4 − 3 = 1.

**Klärung 4 nennt die Notenbanken als eigene Stellen** (Zeile 519, 539–556): die Tabelle
in Zeile 547–552 führt für jedes der vier Modellländer Amt **und** Notenbank, also acht
Stellen, davon eine geprüft (Destatis) — „Sieben Abrufe, nicht drei" (Zeile 554). Die
vier Modellländer USA, China, Deutschland, Brasilien stimmen mit `spiel.md:8` überein.
Gegenprobe zur Behauptung „keine einzige Notenbank geprüft": `grep -i` über `daten.md`
nach Bundesbank/Notenbank/Central Bank/Federal Reserve/Banco Central findet **einen**
Treffer, Nr. 11 FRED (siehe „Wonach ich gesucht habe" unten) — keine der acht Stellen
der Tabelle. Die Behauptung trägt.

## Kriterium 3 — Frontmatter trennt Paket- und Gesamtzählung: **erfüllt**

Alle zwölf `reihen_*`/`sollreihen_*`-Felder tragen jetzt `_paket` oder `_gesamt` (Zeilen
11–23), dazu die erklärende Zeile `zaehlbereiche` (Zeile 8) und
`pruefgegenstaende_ungefaehrdet_gesamt` (Zeile 24). `codes_abgerufen` ist in
`codes_abgerufen_reihen: 6` und `codes_abgerufen_gegenprobe: 2` getrennt (Zeilen 9–10),
mit dem Zusatz, dass das Abnahmekriterium gegen die sechs gilt.

**Ich habe `reihen_*` gegen `sollreihen_*` durchgerechnet und stoße auf keinen
Widerspruch:**

| Probe | Rechnung | Ergebnis |
|---|---|---|
| Paketumfang | 4 frei + 7 unklar + 0 gesperrt | 11 = `reihen_paket` ✔ |
| Gesamtumfang | 6 + 8 + 1 | 15 = „alle 15 Reihen mit Datenanker" ✔ (Reihenliste hat 17 Zeilen, 16 und 17 tragen keinen Anker) |
| Paket ∪ 0005 | 11 (1,2,3,4,5,6,9,11,12,14,15) + 4 (7,8,10,13) | 15, keine Reihe doppelt ✔ |
| Sollreihen gesamt | 7 frei + 24 unklar + 0 gesperrt | 31 ✔ |
| `reihen_frei_paket: 4` vs. `sollreihen_frei_paket: 0` | Reihen 3, 4, 15 sind Startwerte (Zeile 350), Reihe 14 zählt getrennt (Zeile 376) | kein Widerspruch, im Feld annotiert ✔ |
| `reihen_unklar_gesamt: 8` vs. `sollreihen_unklar_gesamt: 24` | die Differenzreihe zum Paket ist Reihe 7; `lizenzbefund-wdi.md:140` sagt „Reihe 7 ist reiner Startwert" | kein Widerspruch ✔ |
| `reihen_gesperrt_gesamt: 1` vs. `sollreihen_gesperrt_gesamt: 0` | `lizenzbefund-wdi.md:77` — „Reihe 13 trägt keine der 31 Sollreihen" | kein Widerspruch ✔ |
| `sollreihen_frei_gesamt: 7` | `lizenzbefund-wdi.md:217–219` — vier aus Reihe 8, drei aus Reihe 10 | ✔ |

Genau der Widerspruch, den das Paket beheben sollte (`reihen_frei: 4` neben
`sollreihen_frei: 7` ohne Zählbereich), ist damit weg: `reihen_frei_paket: 4` steht neben
`sollreihen_frei_paket: 0`, `reihen_frei_gesamt: 6` neben `sollreihen_frei_gesamt: 7`.

## Kriterium 4 — jedes Reihe-2-Urteil trägt seine T26-Folge: **erfüllt**

`grep -n "Folge nach T26"` findet sechs Zeilen: 127 (Reihe 1), **164 (2a)**, **196 (2b
und 2c)**, 252 (Reihe 5), 295 (Reihe 6), 409 (Reihen 9, 11, 12). Der Änderungssatz zeigt
alle drei mittleren als Neuzugänge.

Gegenprobe in die andere Richtung — **kein Urteil ausser `frei` ohne Folgezeile**: die
nicht-`frei`-Urteile der Datei sind Reihe 1, 2a, 2b/2c, 5, 6 und die IWF-Gruppe 9/11/12;
alle sechs Stellen haben eine. Die beiden `frei`-Urteile (PWT, Zeile 350; BACI, Zeile
376) haben keine, was das Kriterium ausdrücklich zulässt. Die T26-Zeile zur IWF-Gruppe
war nicht verlangt, ohne sie wäre die zweite Hälfte des Kriteriums aber gerissen.

Die Zeile in 196 gilt für 2b und 2c gemeinsam und sagt das auch („weil beide Codes
dasselbe `Source`-Feld tragen"). Das ist kein Verstoß: Abschnitt und Urteil für 2b/2c
sind seit 0014 zusammengefasst, das Paket durfte den Zuschnitt nicht ändern, und die
Auskunft steht neben dem Urteil statt zwölf Seiten später — was das Kriterium wollte.

Sachprobe: `technik.md:969–977` — T26 nennt tatsächlich genau drei Fälle (Zoll/Reihe 13,
sektorale Beschäftigung/Reihe 7, Handelsmatrix vor 1995), keiner davon betrifft Reihe 2.
Die Aussage „kein Fall von T26" ist richtig.

**Zusatz ausserhalb der Abnahme, trotzdem gemessen:** Der nachgetragene Satz zu Befund 2
(Zeilen 614–622) benennt die Spaltenverwechslung korrekt. `technik.md:1667–1671` führt
genau die drei T37-Klassen `frei`, `gesetzt`, `abgeleitet` und ordnet Reihe 9 `gesetzt`,
Reihe 11 `abgeleitet`, die Reihen 1, 2, 8, 10 `frei` zu; die Reihenliste-Zelle lautet
„Start + Soll (12, frei, 8 unabhängig)" (`technik.md:993`), und T37s „19 unabhängig"
löst sich auf zu 4 + 8 + 4 + 3. Der Nachtrag stimmt Wort für Wort.

---

# Befund 1 — an den Projektmanager: die Begründung unter 2b/2c lässt die Notenbanken aus, obwohl deren `Source` sie als eigenen Lieferanten führt

**Kein Kriterienverstoß.** Kriterium 1 verlangt die beiden Lieferantengruppen
ausdrücklich für „Reihe 1 und 2a", und dort stehen sie. 2b und 2c sind vom Wortlaut der
Abnahme nicht erfasst, und ein Rücklauf wäre eine Kriterienerhöhung. Deshalb hier und
nicht im Urteil.

**Die Stelle.** Das Paket hat an drei Orten „drei" durch „sieben" ersetzt und an einem
vierten nicht. Schritt für Schritt nachvollziehbar:

1. `daten/lizenzbefund-reihen.md`, Zeilen 177–179 — das `Source`-Feld von
   `NV.IND.TOTL.ZS` und `NV.SRV.TOTL.ZS` nennt die Notenbanken als **eigene, zweite
   Angabe**, deutlicher als bei Reihe 1 und 2a, wo sie im selben Halbsatz mit den Ämtern
   stehen:

   > National Accounts data files, Central Banks;

2. Zeile 182 — die Datei sieht das selbst: „an ihrer Stelle stehen die Notenbanken".
3. Zeile 542 — Klärung 4 zieht daraus den richtigen Schluss: „Die Notenbanken sind also
   ein eigener Lieferant und nicht von den Ämtern mit abgedeckt", und Zeile 554 schreibt
   die Korrektur hin: „**Sieben Abrufe, nicht drei.**"
4. Zeilen 118–119 — Reihe 1 hat die Korrektur bekommen: „und **keine einzige Notenbank**.
   Für die Ämter der drei übrigen Länder **und für alle vier Notenbanken** liegt nichts
   vor." Zeile 161 hat sie für 2a bekommen: „keine Notenbank".
5. Zeilen 189–192 — die Begründung unter 2b/2c hat sie **nicht** bekommen und trägt
   weiterhin die alte Zählung:

   > `daten.md` hat von den vier Modellländern genau ein statistisches Amt geprüft:
   > **Destatis, Nr. 5, positiv** … Für die Ämter der drei übrigen Länder liegt nichts vor.

**Was daran falsch ist.** Der Satz zählt drei offene Stellen, wo sieben offen sind. Er
steht unter genau dem Code-Paar, dessen `Source` die Notenbanken am klarsten ausweist,
und er ist die einzige Begründung der Datei, die den zweiten Lieferanten verschweigt —
dieselbe Ungleichbehandlung innerhalb einer Datei, die Paket 0018 bei Reihe 1 behoben
hat, nur eine Ebene tiefer. Wer Reihe 2b/2c von dort aus bepreist, kommt auf drei Abrufe
und findet die Zahl sieben erst vierzig Bildschirmseiten später unter Klärung 4.

**Warum das nicht folgenlos ist.** Die Klärungsliste sagt, Klärung 4 allein hebe 2b und
2c. Ob sie das tut, hängt daran, wie viele Stellen für 2b/2c zu klären sind — und die
Begründung, die das ausweisen soll, sagt drei statt sieben. Die Zahl in der Klärungsliste
ist richtig, die Zahl an der Reihe ist es nicht; sie widersprechen einander.

**Umfang der Reparatur:** ein Satz, keine Recherche, kein Abruf. Die Belege stehen
vollständig in derselben Datei (Zeilen 177–179, 542, 547–556). Vorschlag: mit in das
Paket, das `daten/reihen.toml` aus dieser Datei fortschreibt — sonst wandert die Zahl
drei mit.

---

## Wonach ich gesucht und **nichts** gefunden habe

Damit unterscheidbar ist, wo diese Prüfung hingesehen hat und wo nicht.

- **Einheiten und Basisjahre.** Dieses Paket ändert keine Zahl mit Einheit — es ändert
  Begründungen und Abzählungen. Der Basisjahrbruch, den die Datei bei Reihe 1 nennt (WDI
  konstante Preise 2015 US$ gegen PWT mit eigenem Basisjahr, Zeilen 131–136), steht
  unverändert und mit dem richtigen Adressaten (Spielentwerfer, `rueckstand.md`). Kein
  neuer Einheitenfehler möglich, keiner gefunden.
- **Stillschweigende Interpolation.** Nicht anwendbar: die Datei enthält keine Datenreihe,
  nur Urteile über Lizenzen.
- **Lizenz und Namensnennung.** Alle zitierten Quellen (Weltbank, PWT, CEPII/Etalab, IWF,
  ILO, Destatis, OECD, Eurostat) stehen in `specs/…/daten.md`; die Nummern 2, 5, 7 und 8
  habe ich einzeln nachgeschlagen und richtig zitiert gefunden. Keine Quelle ist neu
  hinzugekommen — der Änderungssatz enthält keine neue URL.
- **Reproduzierbarkeit.** Jede der sechs `Source`-Zitatzeilen trägt weiter ihr Abrufdatum
  2026-09-02 und beide Endpunkt-URLs; keine ist angefasst worden. Ich habe wie beauftragt
  nichts nachgerufen und kann deshalb zu den Zitaten nur sagen, dass sie unverändert sind
  — gemessen hat sie die Prüfung zu 0014.
- **FRED als möglicher Gegenbeleg zu „keine einzige Notenbank geprüft" (Zeile 118).**
  `daten.md` Nr. 11 (`daten.md:282–296`) prüft FRED — Federal Reserve Bank of St. Louis —
  und urteilt **negativ**. Ich zähle das **nicht** als Befund: FRED ist dort als
  *Aggregator* beurteilt („der Lizenzstatus haengt an der einzelnen Reihe, nicht an
  FRED"), also als Bezugsweg, nicht als die Stelle, die der Weltbank die
  Volkswirtschaftliche Gesamtrechnung liefert. Das ist eine andere Frage und eine andere
  Stelle als das „Federal Reserve Board" der Tabelle in Zeile 550. Ein negatives Urteil
  über eine Fed-Datenbank macht die Aussicht für Klärung 4 nicht besser — wer sie kauft,
  sollte `daten.md` Nr. 11 gelesen haben.
- **Ob die Klärungsliste alle acht unklaren Reihen erreicht.** Sie tut es nicht: Reihe 5
  blockiert unter anderem an der UN Population Division und an Eurostat, und keiner der
  vier Schritte nennt eine der beiden. **Kein Befund**, weil die Liste ihren Zweck selbst
  auf die Zahlen beschränkt („für den, der die Zahlen bewegen will", Zeile 498) und Reihe
  5 null Sollreihen und null Prüfgegenstände trägt; den Weg für Reihe 5 nennt die Datei
  an ihrer eigenen Stelle (PWT, Zeile 252–254). Reihe 12 ist analog gelagert und in Zeile
  406–407 ausdrücklich abgehandelt.
- **Ob die Reihenfolge der Klärungsliste jetzt die richtige Empfehlung ist.** Die Liste
  ordnet nach gehobenen Prüfgegenständen (1+4, dann 2, dann 3) und sagt das (Zeile 508).
  Man könnte Klärung 2 vorziehen, weil an ihr sieben *gesicherte* Prüfgegenstände hängen,
  die bei einem negativen Volltext fallen. Beide Zahlen stehen ausgeschrieben nebeneinander
  (Zeile 572–577), die Datei nimmt sie niemandem ab und sagt „Keine Empfehlung, nur die
  Preise". Das ist Geschmack, kein Befund.
- **Behauptete Messungen ohne Werkzeug.** Das Paket verbietet neue Abrufe, und die Datei
  behauptet keinen. Nichts nachzuprüfen.

**Was diese Prüfung nicht geleistet hat:** Ich habe keinen einzigen Endpunkt abgerufen —
so beauftragt. Die sechs `Source`-Zitate gelten hier als gegeben, weil sie unverändert
sind und am 2026-09-02 an beiden Endpunkten gemessen wurden. Wäre eines davon zwischen
0014 und heute an der Quelle geändert worden, fände diese Prüfung es nicht.
