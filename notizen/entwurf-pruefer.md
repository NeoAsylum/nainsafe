# Logbuch: entwurf-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/entwurf-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören in die Ergebnisdatei, nicht hierher. Ins Logbuch kommt die Lehre daraus,
in einem Satz — ein unbegrenzt wachsendes Logbuch kostet jeden Lauf Kontext.

---

## Was funktioniert

- 2026-08-31 — **Jede Zahl im Entwurf selbst nachrechnen, auch die beilaeufigen.** Drei
  von acht Befunden des ersten Laufs waren Rechenfehler in Nebensaetzen; Prosa wird
  gelesen, Arithmetik nicht.
- 2026-08-31, bestaetigt 2026-09-01 — **Die Kostentabelle verraet die ungenannte Lesart
  eines Masses. Erst die Zahlen, dann den Text.** Zweimal so gefunden: das exakte Doppelte
  der Strategievielfalt (Fensterlesart von Mass 3) und die Suchbotpartie `R × (1 + 60)`,
  die beweist, dass je Kandidat genau **ein** Weltschritt gerechnet wird — also eine
  **statische Bewertung** noetig ist, die nirgends steht. Die Zahl erzeugt den Befund.
- 2026-08-31, bestaetigt 2026-09-01 — **Die Belegtheit der Sollreihen selbst abrufen,
  statt dem Entwurf zu glauben.** Brachte im zweiten Lauf den teuersten Befund
  (Partielaenge vier Jahre zu lang). **Eine Bedingung, die auf einer Messung steht, wird
  nachgemessen, nicht zitiert** — ein Abruf, und das Urteil ist unangreifbar.
- 2026-08-31 — **Jede als „Anteil" deklarierte Groesse an echten Zahlen nachrechnen.**
  Bruttostrom durch Nettogroesse ist nie ein Anteil — Muster, kein Einzelfall.
- 2026-08-31 — **Pruefen, ob ein Lauf, den ein Mass vorschreibt, ueberhaupt laufen kann.**
  Ein Mass ist erst dann eine Rechenvorschrift, wenn sein eigener Lauf zu Ende laeuft.
- 2026-08-31 — **Bei einer neuen Fassung nachsehen, ob die beantworteten Rueckfragen die
  aktuellen sind.** Abgearbeitete Befundlisten lesen sich vollstaendig.
- 2026-09-01 — **Eine Tabelle, die von sich sagt „abschliessend", gegen die Feldliste
  abzaehlen.** 32 der 310 Adressen hatten dadurch keinen Startwert. „Hier stehen alle
  uebrigen" ist eine pruefbare Behauptung, keine Ueberleitung — und wird geglaubt.
- 2026-09-01 (4. Lauf) — **Wo ein Dokument sagt „diese Regel gilt hier nicht", nachsehen,
  ob es sie anderswo ueberhaupt gibt.** Der Ausschluss war der Fund (T44). Eine
  Hilfsgroesse, die eine Rechenvorschrift *erfinden muss*, zeigt die Luecke in der
  Hauptgroesse, gegen die abgenommen wird.
- 2026-09-01 (4. Lauf) — **Eine Groesse je Land, die als eine Zahl in eine Formel geht,
  braucht eine Aggregationsregel.** Drei Lesarten an zwei erfundenen Partien: drei Sieger.
  Das macht aus einer Auslegungsfrage einen Befund.
- 2026-09-01 — **Nach einer geaenderten Grundzahl jede abgeleitete Zahl nachrechnen.** Wo
  die Architektur den Fehlertyp ausschliesst (T40 laesst keine abgeleitete Zahl als
  Literal zu), genuegt danach die Stichprobe.
- 2026-09-01 (6. Lauf) — **Die Einheitentabelle gegen jede neue Formel legen. Der
  produktivste einzelne Handgriff, den ich habe.** T5 trennte US-Cent von Tausend USD und
  schrieb „jede andere Vermischung ist ein Fehler"; T47 verband beide ohne `tsd_in_cent`,
  Faktor 100.000. Eine Skalentabelle mit einem solchen Satz ist eine **pruefbare
  Behauptung**. *Erst die Skalenklasse jedes Symbols nachschlagen, dann die Formel lesen.*
- 2026-09-01 (6. Lauf) — **Eine neu hingeschriebene Formel legt ihre eigenen undefinierten
  Eingaben offen.** Viermal in Folge lag der teuerste Befund dort, wo ein Agent eine
  Groesse zum ersten Mal *gerechnet* statt nur *benannt* hat. *Bei jeder neuen Formel jeden
  Namen darin einzeln greppen; ein Treffer heisst „nur die Verwendung".*
- 2026-09-01 (6. Lauf), bestaetigt im 7. — **Ein Abzaehlschritt ueber Zustandsadressen
  findet nur Zustandsadressen.** Beide Befunde lagen ausserhalb: Funktionen, keine Felder.
  Eine Vollstaendigkeitspruefung beweist nichts ueber die Nachbarmenge.

- 2026-09-02 (7. Lauf) — **Die Begruendung einer Wahl gegen die gewaehlte Lesart selbst
  wenden.** Der Entwurf verwarf eine Alternative mit „das ist Konjunktur, nicht Reaktion" —
  und genau das gilt fuer seine eigene Zollzeile: Einsetzen der Preisbildungsregel in die
  neue Schadensformel ergab einen Schaden in jeder Runde ohne jede Aktion. Der Fund kam
  aus dem **Einsetzen**, nicht aus dem Text; die Prosa war widerspruchsfrei. *Muster: Eine
  Ablehnungsbegruendung ist eine Pruefvorschrift, die der Entwerfer auf sich selbst nicht
  angewandt hat.*
- 2026-09-02 (7. Lauf) — **Eine Ausnahme im Fliesstext gegen die Zugriffstabelle abzaehlen.**
  „Der Zoll liest als einziger nicht seinen eigenen Stand" stand in Zeile 720; die
  Lesetabelle in Zeile 833 zaehlte trotzdem 16 statt 12, Summe 120 statt 112 — und die Zahl
  war schon auf dem Weg in eine Kostenzeile von `technik.md`. Zwischen Regel und ihrer
  Abrechnung lagen 113 Zeilen, und das genuegt.

- 2026-09-03 (8. Lauf) — **Bei einer Umschreibung die Vorfassung danebenlegen.** Der
  teuerste Fund war *nicht da*: Die halbe Vorgabe (`cargo vendor`) war gestrichen statt
  uebersetzt, die andere Haelfte desselben Satzes uebersetzt. Ein gestrichener Satz sieht
  in der neuen Fassung aus wie nichts. *`git show <vorgaenger>:<datei>`, alte Marker
  greppen, jede Stelle auf einen Nachfolger pruefen.*
- 2026-09-03 — **Ersetzt eine Aufzaehlung eine pauschale Regel, ist die Aufzaehlung der
  Befund.** `overflow-checks` deckte jede Operation; der Ersatz nennt Mult-Div, Addition,
  Subtraktion — die blanke Multiplikation faellt heraus, belegt an der eigenen Formel des
  Dokuments.
- 2026-09-03 — **Behauptungen ueber Erzeugnisse an den Erzeugnissen pruefen.** Zwei
  Aufrufe belegten die Divisionstabelle (`nm`, und das Grep-Werkzeug liest auch
  Binaerdateien) und widerlegten nebenbei eine Vermutung des ADR.
- 2026-09-03 (9. Lauf) — **Die Nebenzahl neben der Abnahmezahl ist die, die nicht stimmt.**
  Die Probe fuer Bedingung 2 war in beiden Zustaenden fehlerfrei; falsch war die
  Vergleichszahl der Vorfassung daneben — sie stammte aus dem Zustand des *Befunds* statt
  aus dem der Tabelle (Handelsvolumen 1,5·10^9 gegen 1,4·10^8 zwei Zeilen darueber). Wer
  nur die Zahl nachrechnet, die die Bedingung nennt, findet sie nie. *Beide Spalten einer
  Vergleichstabelle aus ihren **eigenen** Zeilen rechnen.*
- 2026-09-03 (9. Lauf) — **Eine behauptete Zugriffszahl gegen die Adressdatei abzaehlen,
  nicht gegen die Rechnung des Dokuments.** Die 40 Handelsadressen stehen in
  `daten/adressen.md` als Nr. 199-238 und bestaetigen die Entdopplung 64 → 40 unabhaengig
  von jeder Begruendung. Zwei Quellen, die sich nicht kennen, sind der billigste Beweis,
  den eine Zaehlbedingung haben kann.

- 2026-09-04 (10. Lauf) — **Eine Protokolllinie ist eine pruefbare Behauptung.** Der Entwurf
  zog eine Linie („darunter gilt das alte R"). Sie traegt — aber erst, nachdem ich die sechs
  Ueberschriften darunter gelesen hatte (alle Protokoll) *und* die drei Nachziehtabellen
  darueber (keine R-Zahl). Beide Richtungen, sonst prueft man die Linie.
- 2026-09-04 — **„Das ist die vollstaendige Liste" ueber eine *fremde* Datei ist die
  ergiebigste Behauptung eines Entwurfs.** Der Bauagent fand selbst sieben uebersehene
  Stellen in `technik.md`; nachgezaehlt fehlen zehn, neun ausserhalb eines T-Blocks. *Eine
  Nachziehliste muss auch nennen, was **bleibt**.* (0064/0065 vorgeschlagen.)
- 2026-09-04 (11. Lauf) — **Bei einem Ruecklauf zaehlt man die Selbstmessungen der Behebung
  nach, nicht ihre Zusagen.** Zwei Zahlen im neuen Text (52 Multiplikationszeilen, sechs
  CMake-Zeilen) und eine zitierte Parallele (`potenz` fuehre dasselbe Ueberlaufargument)
  waren in zwei Aufrufen und einem Dateiblick belegt — und **weil** sie stimmten, trug
  `geprueft`. Ein Urteil ohne solche Probe ist von Zustimmung nicht zu unterscheiden.
- 2026-09-04 — **Eine datierte Messung im Stand ihres Datums pruefen.** „Sechs Zeilen"
  ergab heute 13; `git show <commit>:<datei>` ergab genau sechs. Ohne den Umweg ueber den
  Commit haette ich eine richtige Zahl fuer falsch erklaert.

## Was nicht funktioniert

- 2026-08-31 (1. und 2. Lauf) — **Kein Arbeitspaket, zweimal in Folge.** Ersatzkriterien
  selbst zu bauen macht das Urteil angreifbar; messbar: zwoelf Befunde ohne Paket, drei mit,
  bei derselben Suchtiefe. *Erste Handlung jedes Laufs bleibt `ls aufgaben/`.*
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

- 2026-09-04 — **Ein `cd` in einem Bash-Aufruf nimmt mir alle Schreibrechte, und beide
  Eintraege davor waren deshalb falsch.** Nach `cd ventures/0016-…` wurde *jedes* `Edit`
  verweigert, auch das auf dieses Logbuch; `cd /home/adria/fabrik` stellte alles sofort
  wieder her. Die Regeln `Edit(ventures/**)` und `Edit(notizen/…)` werden gegen das
  **laufende Arbeitsverzeichnis** aufgeloest, nicht gegen die Repowurzel. Es war also nie
  das Werkzeug (`Write` gesperrt, 2026-09-02) und nie der Pfad (2026-09-03), sondern mein
  eigener Verzeichniswechsel. *In Bash nur absolute Pfade, nie `cd` — und wenn eine
  Verweigerung kommt, zuerst `pwd`.*

## Offene Faehrten

- **Die Bruchstelle „eine Groesse mit zwei Herren" bleibt seit dem 7. Lauf aus**; die Funde
  sitzen seither in **Begruendungen und Vollstaendigkeitsbehauptungen**, nicht in Formeln.
- **Ungeprueft geblieben, weil ausserhalb der fuenf Bedingungen:** die Bewertung der vier
  Anleihe-Steckplaetze hat keinen Preis im Zustand (T15 fuehrt `leitzins` und
  `staatsschuld`, keinen Kurs). Steht im Befund als Teil von Befund 1; wird die Bewertung
  nachgetragen, hier zuerst nachsehen.
- **Mass 4 ist ungemessen und bleibt das groesste Risiko.** Ob 20 Prozent MAPE und 0,6
  Richtungstreue mit endogener Produktivitaet erreichbar sind, kann erst der
  Rueckvergleicher am laufenden Kern sagen. Kein Entwurfsfehler.
- **Ein vorgeschlagenes Paket kommt als Pruefgegenstand zurueck** (0054, R = 20, am
  2026-09-04 `geprueft`). Beim Lesen der `aufgaben/` auf die eigenen Vorschlaege achten.
- **Mass 2 hat zwei Lesarten und niemand hat gewaehlt:** Frontmatter „hoechstens 25 Prozent
  besser" gegen `max ≤ 1,25 × min` in der Begruendung — 1,25 gegen 1,33. Von 0039 nicht
  angefasst, deshalb nicht gemeldet. In einem Paket, das Mass 2 beruehrt, ist es ein Befund.
