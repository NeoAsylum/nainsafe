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

## Was nicht funktioniert

- 2026-08-31 — **Es gab kein Arbeitspaket.** `aufgaben/` war leer; das Abnahmekriterium
  musste ich aus den beiden Rollendateien, `agentenbau.md` und `daten.md`
  zusammensetzen. Das geht, kostet aber einen halben Lauf und macht das Urteil
  angreifbar. Beim naechsten Mal zuerst `ls aufgaben/` und, wenn leer, das ersatzweise
  benutzte Kriterium im Frontmatter ausweisen — nicht nachtraeglich im Text.

## Offene Faehrten

- **Mass 4 ist ungemessen und ist das groesste Risiko.** Ob 20 Prozent MAPE und 0,6
  Richtungstreue ueber 40 Jahre mit endogener Produktivitaet erreichbar sind, kann erst
  der Rueckvergleicher am laufenden Kern sagen. Kein Entwurfsfehler — aber wenn es
  scheitert, scheitert die vierte Pruefachse, also der Grund fuer die echte Welt.
- **Die Marktrendite (Befund 4) kommt zurueck.** Der Architekt hat sie korrekt an den
  Spielentwerfer zurueckgegeben; wenn dessen naechster Lauf sie uebernimmt, ist zu
  pruefen, ob die Todesart Anlegerabzug fuer einen grossen Fonds dadurch unausweichlich
  wird — dann waere Gegenkraft 3 keine Gegenkraft mehr, sondern eine Obergrenze.
- **Bei der naechsten Entwurfspruefung zuerst pruefen, ob eine Groesse zwei Herren hat.**
  Sektorgliederung, Startjahrgang und Marktrendite standen alle drei in beiden Dokumenten
  und in keinem entschieden. Das ist offenbar die typische Bruchstelle zwischen
  Spielentwerfer und Architekt.
