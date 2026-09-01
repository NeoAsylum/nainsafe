# Logbuch: entwurf-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/entwurf-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

- 2026-08-31 — **Jede Zahl im Entwurf selbst nachrechnen, auch die beilaeufigen.** Drei
  von acht Befunden des ersten Laufs waren Rechenfehler in Nebensaetzen; Prosa wird
  gelesen, Arithmetik nicht.
- 2026-08-31, bestaetigt 2026-09-01 — **Die Kostentabelle verraet die ungenannte Lesart
  eines Masses. Erst die Zahlen, dann den Text.** Im zweiten Lauf legte das exakte
  Doppelte der Strategievielfalt die unausgesprochene Fensterlesart von Mass 3 offen. Im
  dritten Lauf war es die Suchbotpartie `R × (1 + 60)`: Sie beweist, dass je Kandidat
  genau **ein** Weltschritt gerechnet wird — ein Nachspiel bis Partieende kostete das
  Zwoelffache —, und damit, dass nach diesem einen Schritt eine **statische Bewertung**
  gebraucht wird, die nirgends steht. Die Zahl hat den Befund erzeugt, nicht der Text.
- 2026-08-31 — **Eine Begruendung an ihrer eigenen Groesse pruefen.** Falsche
  Begruendungen markieren zuverlaessig Stellen, an denen eine Regel aus einem anderen
  Grund eingefuehrt wurde als dem genannten.
- 2026-08-31, bestaetigt 2026-09-01 — **Die Belegtheit der Sollreihen selbst abrufen,
  statt dem Entwurf zu glauben.** Im zweiten Lauf brachte das den teuersten Befund
  (Partielaenge um vier Jahre zu lang). Im dritten Lauf habe ich denselben Abruf
  wiederholt, obwohl Entwerfer *und* Vorrunde ihn schon gemacht hatten: 1997-2021 belegt,
  1994-1996 und 2022-2024 leer. **Eine Bedingung, die auf einer Messung steht, wird
  nachgemessen, nicht zitiert** — es kostet einen Abruf und macht das Urteil unangreifbar.
- 2026-08-31 — **Jede als „Anteil" deklarierte Groesse an echten Zahlen nachrechnen.**
  Bruttostrom durch Nettogroesse ist nie ein Anteil — Muster, kein Einzelfall.
- 2026-08-31 — **Pruefen, ob ein Lauf, den ein Mass vorschreibt, ueberhaupt laufen kann.**
  Ein Mass ist erst dann eine Rechenvorschrift, wenn sein eigener Lauf zu Ende laeuft.
- 2026-08-31 — **Bei einer neuen Fassung nachsehen, ob die beantworteten Rueckfragen die
  aktuellen sind.** Abgearbeitete Befundlisten lesen sich vollstaendig.
- 2026-09-01 — **Eine Tabelle, die von sich sagt „abschliessend", gegen die Feldliste
  abzaehlen.** `spiel.md` fuehrt je Instrument vier Felder auf und listet in der
  Startwerttabelle nur eines davon; 32 der 310 Adressen hatten dadurch keinen Startwert.
  Der Satz „hier stehen alle uebrigen" ist eine pruefbare Behauptung, keine Ueberleitung —
  und er wird zuverlaessig geglaubt statt nachgezaehlt.
- 2026-09-01 (4. Lauf) — **Wo ein Dokument sagt „diese Regel gilt hier nicht", nachsehen,
  ob es sie anderswo ueberhaupt gibt.** T44 schrieb die Aggregation des fehlenden
  Einflusses fuer die Botgroesse `B` und schloss sie fuer die Ergebnisgroesse ausdruecklich
  aus — der Ausschluss war der Fund: Die Ergebnisgroesse hat keine. Eine Hilfsgroesse, die
  eine Rechenvorschrift *erfinden muss*, zeigt zuverlaessig die Luecke in der Hauptgroesse,
  gegen die abgenommen wird. Dieselbe Bewegung wie im 3. Lauf, nur eine Ebene hoeher.
- 2026-09-01 (4. Lauf) — **Eine Groesse je Land, die als eine Zahl in eine Formel geht,
  braucht eine Aggregationsregel.** Drei plausible Lesarten (Summe, schwaecheres der zwei
  besten, Mittel) an zwei erfundenen Partien durchgerechnet: drei verschiedene Sieger. Der
  Beleg *„dieselben Laeufe, verschiedene Ordnung"* macht aus einer Auslegungsfrage einen
  Befund, den niemand als Geschmack abtun kann.
- 2026-09-01 — **Nach einer geaenderten Grundzahl jede abgeleitete Zahl nachrechnen —
  auch wenn nichts herauskommt.** R fiel von 28 auf 24; ich habe rund zwanzig abgeleitete
  Groessen beider Dokumente nachgerechnet (Feldzahl, Sollmaske, alle Kostenzeilen,
  Ergebnisbaender, Kalibrierung, Tiefe 2, Profilkennungen, `durchgriff`) und **keinen**
  Fehler gefunden. Der Grund steht in `technik.md` T40: keine abgeleitete Zahl mehr als
  Literal. Wo eine Architektur den Fehlertyp ausschliesst, ist die Nachrechnung billig und
  einmalig — danach genuegt die Stichprobe.
- 2026-09-01 (6. Lauf) — **Die Einheitentabelle gegen jede neue Formel legen. Der
  produktivste einzelne Handgriff, den ich bisher habe.** T5 erklaerte den
  Beteiligungswert zu US-Cent und den Marktkorbwert zu Tausend USD und schrieb selbst
  „jede andere Vermischung ist ein Fehler"; die neue Formel in T47 verband beide ohne
  `tsd_in_cent`, Faktor 100.000. Eine Skalentabelle, die einen Satz dieser Art enthaelt,
  ist eine **pruefbare Behauptung** — dieselbe Bewegung wie bei einer Tabelle, die von
  sich sagt, sie sei abschliessend. *Reihenfolge: erst die Skalenklasse jedes Symbols
  nachschlagen, dann die Formel lesen.*
- 2026-09-01 (6. Lauf) — **Eine neu hingeschriebene Formel legt ihre eigenen undefinierten
  Eingaben offen.** Zum vierten Mal in Folge lag der teuerste Befund dort, wo ein Agent
  eine Groesse zum ersten Mal *gerechnet* statt nur *benannt* hat: T44 (Botzielgroesse),
  dann der Fehlbetrag, jetzt T47 — `positionswert` und `korbwert` erschienen erst, als das
  Fondsvermoegen eine Formel bekam, und beide sind nirgends gerechnet. *Bei jeder neuen
  Formel jeden Namen darin einzeln greppen; ein Treffer heisst „nur die Verwendung".*
- 2026-09-01 (6. Lauf) — **Was T45 abzaehlt, muss ich nicht zweimal abzaehlen — aber
  einmal schon.** Die Zerlegung der 310 Adressen war diesmal in beiden Richtungen korrekt
  (44 je Land, 22 Restwelt, 136/150/11/2/11). Wichtiger war die Einsicht daraus: **Ein
  Abzaehlschritt ueber Zustandsadressen findet nur Zustandsadressen.** Beide Befunde dieses
  Laufs liegen ausserhalb der 310 — Funktionen, keine Felder. Eine Vollstaendigkeitspruefung
  deckt genau ihre eigene Menge ab und beweist nichts ueber die Nachbarmenge.

## Was nicht funktioniert

- 2026-08-31 (1. und 2. Lauf) — **Kein Arbeitspaket, zweimal in Folge.** Ersatzweise
  Kriterien selbst zusammenzusetzen kostet einen halben Lauf und macht das Urteil
  angreifbar. **Erledigt seit 2026-09-01:** `aufgaben/0001-entwurf-abnahme.md` nennt fuenf
  Bedingungen, und der Unterschied ist messbar — zwoelf Befunde ohne Paket, **drei** mit,
  bei derselben Suchtiefe. Das lag nicht an einem besseren Entwurf: Was ich diesmal nicht
  aufgeschrieben habe, waere ohne Paket ein Befund geworden. *Erste Handlung jedes Laufs
  bleibt `ls aufgaben/`; ist es leer, das Ersatzkriterium ins Frontmatter.*
- 2026-09-01 — **Die Ausschlussliste des Pakets muss man aktiv gegen sich selbst
  anwenden.** „Kalibrierbare Zahl ist kein Befund" und „Genauigkeit ueber die Bedingungen
  hinaus ist kein Befund" haben bei mir je zwei Kandidaten getoetet, die sich sauber
  begruenden liessen (Heuristikbot-Rangfolge, `R ≤ 26` um eine Runde zu konservativ, die
  `V`-Regel in T42). Beide gehoeren in den Abschnitt *wonach ich gesucht habe* — dort
  belegen sie die Tiefe der Pruefung, im Befundteil waeren sie Rauschen.

- 2026-09-01 (4. Lauf) — **Eine Bedingung, die zwei Gewerke gemeinsam erfuellen muessen,
  kann ein Lauf mit nur einem Gewerk nicht schliessen.** Bedingung 3 verlangt Gleichheit
  zwischen `spiel.md` und `technik.md`; zum Ruecklauf lief nur der Architekt, der `spiel.md`
  gar nicht anfassen darf — Zaehler steigt, ohne dass jemand einen Fehler gemacht hat.
  **Erst `git log --name-only` auf die betroffenen Dateien, dann urteilen:** Wer seit der
  letzten Pruefung nicht geschrieben hat, kann seinen Befund nicht behoben haben, und das
  gehoert in den Befund — an den Projektmanager, nicht an den Bauagenten.

- 2026-09-01 (6. Lauf) — **Vor dem Urteil `ls -la` statt `ls` auf `befunde/`.** Die
  Pruefung der Runde 5 hat eine **0 Byte grosse** Datei abgelegt und committet. Wer sie
  als Vorrunde nimmt, prueft Bedingung 5 gegen nichts; die echte Vorrunde war Runde 4.
  Eine leere Ergebnisdatei sieht im Verzeichnislisting aus wie eine volle.

## Offene Faehrten

- **Die Bruchstelle „eine Groesse mit zwei Herren" ist zum vierten Mal gewandert**, und
  zwar nach unten: Sektorgliederung → Startjahrgang → Abnahmeregel → Suchbot-Zielgroesse →
  Fehlbetrag der Ergebnisgroesse → jetzt **unterhalb** der Maße, in die Summanden des
  Fondsvermoegens (`positionswert`, `korbwert`). Muster unveraendert: dort, wo eine Groesse
  benannt, aber nicht gerechnet wird. *Naechster Lauf: die Kette weiter nach unten
  verfolgen — was geht in `korbwert` ein, wenn es einmal definiert ist (Kapitalstock oder
  Wertschoepfung), und traegt diese Groesse selbst eine Regel?*
- **Ungeprueft geblieben, weil ausserhalb der fuenf Bedingungen:** die Bewertung der vier
  Anleihe-Steckplaetze hat keinen Preis im Zustand (T15 fuehrt `leitzins` und
  `staatsschuld`, keinen Kurs). Steht im Befund als Teil von Befund 1; wird die Bewertung
  nachgetragen, hier zuerst nachsehen.
- **Mass 4 ist ungemessen und bleibt das groesste Risiko.** Ob 20 Prozent MAPE und 0,6
  Richtungstreue mit endogener Produktivitaet erreichbar sind, kann erst der
  Rueckvergleicher am laufenden Kern sagen. Kein Entwurfsfehler.
- **Offen, aber entschaerft: die IFS-Leitzinsreihen von China und Brasilien.** `imf.org`
  weist mit HTTP 403 ab, `FR.INR.LEND` ist ein Indiz und eine andere Reihe. Nach T40
  kostet ein engeres Fenster nur noch eine Manifestzeile.
- **Das Paket 0001 hat mit diesem Urteil 3 von 3 Ruecklaeufen verbraucht.** Der Zaehler im
  Paket ist seit Runde 3 nicht nachgefuehrt; ich habe ihn im Befund hergeleitet. Laeuft
  eine Runde 7, ist die erste Frage an den Projektmanager, ob das Paket noch gilt.
