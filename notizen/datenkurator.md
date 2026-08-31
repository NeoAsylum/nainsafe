# Logbuch: datenkurator

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/datenkurator-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-08-31 — **Erster Lauf (Idee 0016). Die Sperrfrage ist positiv: Weltbank, IWF,
  Penn World Table und CEPII erlauben im Wortlaut das Einbetten in ein verkauftes
  Produkt.** Wer künftig Wirtschaftsdaten braucht, fängt bei diesen vieren an.
- 2026-08-31 — **Sperrt eine Quelle die Weitergabe, ist die abgeleitete Fassung der
  Ausweg.** UN Comtrade verbietet Weiterverbreitung, sagt aber selbst, transformierte
  Daten fielen nicht mehr darunter — CEPII BACI ist genau das und steht unter Etalab 2.0.
  Vor jedem „Quelle gesperrt" also einmal nach dem bereinigten Derivat suchen.
- 2026-08-31 — **Ist eine Seite per Abruf gesperrt, hilft die Suche nach der wörtlichen
  Zeichenkette.** So kam der tragende IWF-Satz herein, obwohl `imf.org` 403 liefert. Der
  Beleg ist schwächer und gehört als solcher markiert, aber er ist besser als „ungeprüft".

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

- 2026-08-31 — **`imf.org`, `oecd.org`, `fred.stlouisfed.org` und `oecd-ilibrary.org`
  weisen den direkten Seitenabruf mit HTTP 403 ab; `web.archive.org` ist nicht
  erreichbar.** Zeit nicht mit Umwegen über Spiegel und Archive verbrennen, sondern
  gleich die Wortlaut-Suche nehmen.
- 2026-08-31 — **Aggregatoren taugen nicht als Lizenzquelle.** FRED, Our World in Data
  und WITS reichen alle die Bedingungen ihrer Lieferanten durch; der Lizenzstatus hängt
  an der einzelnen Reihe. Bei WITS gilt das sogar unter dem Dach der Weltbank — die
  CC-BY-Lizenz der Weltbank überträgt sich nicht auf fremde Bestände im selben Portal.
- 2026-08-31 — **Eine Quelle kann sich selbst widersprechen.** UNCTADstat trägt auf
  derselben Seite die UN-Standardklausel („None of the materials … may be used,
  reproduced or transmitted") und einen CC-Verweis. Bei UN-Stellen mit beiden Lesarten
  rechnen und keine wählen.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

- 2026-08-31 — **Sektorale Tiefe und Zolldaten sind die beiden offenen Löcher jeder
  Weltwirtschaftssimulation.** Eurostat sperrt Nicht-EU-Länder für gewerbliche Nutzung,
  OECD ist mehrdeutig („written content" — Daten mitgemeint?), WTO und TRAINS verlangen
  schriftliche Genehmigung. Ungeprüft geblieben: MacMap des ITC für Zölle, V-Dem für
  politische Größen.
- 2026-08-31 — **Die Ausnahme in der Weltbank-Lizenz ist noch nicht ausgemessen.**
  „Some datasets and indicators are provided by third parties" — welche Reihen der WDI
  konkret betroffen sind (ILO-Beschäftigung, WITS-Zollsatz, IWF-Preisreihen), steht je
  Indikator im Feld „Source" und ist reihenweise nachzulesen, sobald jemand die Liste
  der tatsächlich einzubettenden Reihen hat.
