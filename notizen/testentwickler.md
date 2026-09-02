# Logbuch: testentwickler

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/testentwickler-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-02 — Die vom Paket 0019 vorgeschriebene Reihenfolge (CMakeLists, dann leeres
  `main`, dann Modul, dann Probe füllen) trägt, aber nur mit einem echten `cmake`-Lauf
  nach Schritt 2. Ohne den ist „im Bericht sichtbar" eine Behauptung; mit ihm steht
  `vorrat_probe … Passed` da, bevor eine einzige Zeile Fachlogik existiert.
- 2026-09-02 — Beide Bauwege einzeln prüfen. `baulauf.py` ruft jede `CMakeLists.txt`
  allein auf, der Arbeitsbereich ruft sie als Unterverzeichnis. Der Arbeitsbereich
  braucht ein erneutes `cmake -S/-B`, wenn ein Mitglied neu dazukommt: Die
  `EXISTS`-Abfrage in der Wurzel gilt zur Konfigurationszeit, und `CONFIGURE_DEPENDS`
  fängt nur neue Quelldateien, kein neues Verzeichnis.
- 2026-09-02 — Die falsche Fassung als *zweiten Aufruf desselben Prüfprädikats* bauen,
  nicht als eigenen Test. Dann misst die Vorführung nachweislich denselben Maßstab.
  Konkret: `zaehle_kerne(liste, kernfunktion)` plus `besteht_kernpruefung(befund)`, einmal
  mit der echten und einmal mit der kaputten Funktion.
- 2026-09-02 — Rotnachweis ohne Kollateralschaden geht mit zwei Edits am eigenen Modul
  (kaputt → bauen → laufen → zurück → bauen → grün). Ein Sabotagelauf in `$TMPDIR` scheitert
  hier am Werkzeugzugriff; der Weg über das Repo ist umkehrbar und im Ergebnis derselbe.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->
