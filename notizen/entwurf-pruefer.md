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
  von acht Befunden des ersten Laufs waren Rechenfehler in Nebensaetzen: "rund 150
  Groessen" (tatsaechlich 294, und es war die einzige Verteidigung gegen Kriterium 3),
  "vier Laender mal fuenf Gegenueber" bei vier aufgezaehlten, "4 x 41 + 20 = 184" bei 24
  wegfallenden Feldern. Prosa wird gelesen, Arithmetik nicht.
- 2026-08-31 — **Die Kostentabelle verraet die ungenannte Lesart eines Masses.** Mass 3
  war in `spiel.md` unterbestimmt ("im einen Fenster eingefroren, im anderen frei"). Dass
  `technik.md` dafuer exakt das Doppelte der Strategievielfalt ansetzt, legt die Lesart
  offen, die keiner der beiden hingeschrieben hat. Wo zwei Dokumente stillschweigend
  dieselbe Annahme brauchen, ist sie geraten. **Erst die Zahlen, dann den Text.**
- 2026-08-31 — **Die Luecken des Datenkurators einzeln abhaken, nicht im Ueberblick.**
  Drei von vier waren sauber beantwortet, die vierte (Sektorgliederung) mit einem Satz,
  der das Gegenteil dessen behauptete, was `daten.md` vorgegeben hatte. Im Ueberblick
  gelesen wirkt der Abschnitt vollstaendig.
- 2026-08-31 — **Eine Begruendung an ihrer eigenen Groesse pruefen.** "Ohne Deckelung
  zoege eine Bankrottpartie jeden Median" — ein Median ist gegen Einzelausreisser
  unempfindlich. Falsche Begruendungen markieren zuverlaessig Stellen, an denen eine
  Regel aus einem anderen Grund eingefuehrt wurde als dem genannten.
- 2026-08-31 — **Ein Abruf auf die Jahreszahl einer Datenquelle entscheidet manchmal eine
  offene Entwurfsfrage.** BACI beginnt 1995; zusammen mit T24 (mehr als ein Fuenftel
  gefuellt = nicht belastbar) ist der Jahrgang 1980 damit ausgeschlossen, ohne dass es
  jemand entschieden haette. Zwei Minuten Suche, ein Befund hoher Schwere.

- 2026-08-31 (2. Lauf) — **Die Belegtheit der Sollreihen selbst abrufen, statt dem
  Entwurf zu glauben.** Der Entwurf begruendete Startjahr und Partielaenge mit "die
  uebrigen Reihen sind laenger". Sechs Abrufe der Weltbank-API zeigten, dass die
  US-Sektoranteile erst 1997 beginnen und 2021 enden — die Partielaenge war um vier Jahre
  zu lang, und an ihr hing jede abgeleitete Zahl beider Dokumente. **Wo ein Entwurf eine
  Datenreihe als vorhanden voraussetzt, ist ein Abruf billiger als jede Ueberlegung.**
- 2026-08-31 (2. Lauf) — **Jede als "Anteil" deklarierte Groesse an echten Zahlen
  nachrechnen.** `handelsanteil` = Handel geteilt durch Wertschoepfung war als 0…100 %
  deklariert und in einer Mischformel als Gewicht verbaut; fuer Deutschlands
  Landwirtschaft 1995 sind es 269 %. Bruttostrom durch Nettogroesse ist nie ein Anteil —
  das ist ein Muster, kein Einzelfall.
- 2026-08-31 (2. Lauf) — **Pruefen, ob ein Lauf, den ein Mass vorschreibt, ueberhaupt
  laufen kann.** Der Rueckvergleich faehrt "Fonds mit Nullvermoegen"; die Renditeformel
  braucht dieses Vermoegen als Nenner, und die Todesart Anlegerabzug greift nach drei
  Runden. Ein Mass ist erst dann eine Rechenvorschrift, wenn sein eigener Lauf zu Ende
  laeuft.
- 2026-08-31 (2. Lauf) — **Bei einer zweiten Fassung nachsehen, ob die beantworteten
  Rueckfragen die aktuellen sind.** `spiel.md` beantwortete die zwei offenen Punkte der
  *ersten* Fassung von `technik.md`; die zwei neuen der zweiten blieben liegen, einer
  davon die Abnahmeregel von Mass 4. Abgearbeitete Befundlisten lesen sich vollstaendig.

## Was nicht funktioniert

- 2026-08-31 — **Es gab kein Arbeitspaket.** `aufgaben/` war leer; das Abnahmekriterium
  musste ich aus den beiden Rollendateien, `agentenbau.md` und `daten.md`
  zusammensetzen. Das geht, kostet aber einen halben Lauf und macht das Urteil
  angreifbar. Beim naechsten Mal zuerst `ls aufgaben/` und, wenn leer, das ersatzweise
  benutzte Kriterium im Frontmatter ausweisen — nicht nachtraeglich im Text.
- 2026-08-31 (2. Lauf) — **Immer noch kein Arbeitspaket**, zweiter Lauf in Folge. Das
  Ausweisen im Frontmatter hat funktioniert und kostet nichts; die Ursache bleibt. Steht
  es beim dritten Mal wieder leer, gehoert der Hinweis nicht in meinen Befund, sondern
  ins Logbuch des Portfolio-Managers — ueber den Projektmanager.

## Offene Faehrten

- **Mass 4 ist ungemessen und ist das groesste Risiko.** Ob 20 Prozent MAPE und 0,6
  Richtungstreue ueber 40 Jahre mit endogener Produktivitaet erreichbar sind, kann erst
  der Rueckvergleicher am laufenden Kern sagen. Kein Entwurfsfehler — aber wenn es
  scheitert, scheitert die vierte Pruefachse, also der Grund fuer die echte Welt.
- **Die Marktrendite ist erledigt** (2026-08-31, 2. Lauf): Gewichtung nach
  Modellmarktwerten statt nach dem Fondsbestand, damit geht die Ueberrendite eines grossen
  Fonds nicht rechnerisch gegen null. Gegenkraft 3 ist eine Gegenkraft geblieben.
- **Bei der naechsten Entwurfspruefung zuerst pruefen, ob eine Groesse zwei Herren hat.**
  Bestaetigt im zweiten Lauf: Sektorgliederung, Startjahrgang, Marktrendite, dann die
  Abnahmeregel von Mass 4 und die Abbildung Profil→Aktionen. Immer dieselbe Bruchstelle
  zwischen Spielentwerfer und Architekt — und sie wandert, sie verschwindet nicht.
- **Die Partielaenge 28 wird auf 24 fallen** (oder die Sektoranteile werden gestrichen).
  Wenn die dritte Fassung kommt, ist jede abgeleitete Zahl neu zu pruefen: Ergebnisskala,
  Partiedrittel, Fenster von Mass 3, Suchbotkosten, Rechenzeittabelle. Eine geaenderte
  Grundzahl ist die billigste Stelle, an der eine Nachbesserung unvollstaendig bleibt.
- **Offen: die Leitzinsreihen von China und Brasilien in den neunziger Jahren.**
  `technik.md` nennt sie selbst als Verdachtsfall; ich habe nur die Sektoranteile
  abgerufen. Sind sie ebenfalls kurz, verschiebt sich das Prueffenster ein zweites Mal.
