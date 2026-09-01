# Logbuch: datenbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/datenbauer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

---

## Was funktioniert

- 2026-09-01 — Die Weltbank-Schnittstelle hat **zwei** Endpunkte je Reihe, und nur einer
  liefert das im Auftrag verlangte Feld unter seinem eigenen Namen:
  `api.worldbank.org/v2/sources/2/series/<code>/metadata?format=json` nennt es wörtlich
  `Source` und gibt zusätzlich `License_Type`, `Periodicity` und `Referenceperiod`;
  `api.worldbank.org/v2/indicator/<code>?format=json` nennt dasselbe
  `sourceOrganization`. Der Metadaten-Endpunkt ist der ergiebigere — mit ihm anfangen.
- 2026-09-01 — **Beide Endpunkte für dieselbe Reihe abrufen ist die Gegenprobe gegen das
  Werkzeug, nicht gegen die Quelle.** Der Seitenabruf reicht auf, statt roh
  durchzureichen; ein einzelnes Zitat kann umformuliert sein. Zwei Abrufe verschiedener
  URLs mit zeichengleichem Ergebnis sind der billigste Wortlautbeleg, den diese Rolle
  bekommen kann. Kostet einen Abruf je Reihe.
- 2026-09-01 — **Kontrollabrufe sind der Kern der Arbeit, nicht die Zugabe.** Das Feld
  `License_Type` sah aus wie die Antwort auf die ganze Paketfrage. Drei Abrufe auf
  Reihen mit völlig anderer Herkunft (ITU, World Federation of Exchanges,
  weltbank-eigenes BIP) ergaben denselben Wert `CC BY-4.0` — ein Feld, das nie
  widerspricht, unterscheidet nichts. Ohne die Kontrollen hätte ich es als Freigabe
  gelesen. *Regel für den nächsten Lauf:* Bevor ein Metadatenfeld ein Urteil trägt, an
  einem Fall messen, bei dem es widersprechen müsste.
- 2026-09-01 — Wenn eine Reihe einen Drittanbieter nennt, ist die nächste Frage nicht
  „wie schlimm", sondern **„was sagt dieser Drittanbieter selbst".** Zwei von vier
  Verdachtsreihen lösten sich so auf (IWF erlaubt das Verkaufen, ILO seit 2023-05-03
  CC BY 4.0), eine blieb hängen, weil ihre Anbieter die Zustimmung ausdrücklich
  vorbehalten. Der Verdacht allein entscheidet nie.

## Was nicht funktioniert

- 2026-09-01 — `imf.org` weist den direkten Abruf weiterhin mit **HTTP 403** ab, genau
  wie am 2026-08-31 beim Datenkurator. Dasselbe gilt neu für `ilostat.ilo.org`. Nicht
  erneut versuchen; der IWF-Wortlaut bleibt nur über Suchtreffer belegt und ist eine
  Sache für den Betreiber.
- 2026-09-01 — Ausweichhost statt Aufgeben: `ilostat.ilo.org` sperrt, `www.ilo.org`
  nicht. Bei einer 403-Sperre lohnt **ein** Versuch auf der Hauptdomain derselben
  Organisation, bevor man auf einen Suchtreffer zurückfällt. Beim IWF gab es keine
  solche zweite Adresse.

## Offene Fährten

- **Worauf ich unsicher bin, für den Projektmanager:** Mein Urteil zu Reihe 7
  (Beschäftigung, ILO) lautet `unklar` und nicht `frei`, obwohl die ILO ihre Datenbanken
  im Wortlaut unter CC BY 4.0 stellt. Grund: Die ILO steht nicht unter den in `daten.md`
  geprüften Quellen, und meine Grenze sagt, eine ungeprüfte Quelle ist nicht erlaubt,
  sondern ungeprüft. Ein Prüfer kann das ebenso gut als übervorsichtig lesen. Der Ersatz
  aus T26 kostet keine Sollreihe, also kostet die Vorsicht hier fast nichts — bei Reihe
  13 hätte ich sie so nicht wählen dürfen.
- **Zweite Unsicherheit:** Die Reihen 8 und 10 habe ich `frei` genannt, obwohl ihre
  Freiheit an den IWF-Bedingungen hängt, die niemand im Volltext gelesen hat. Ich habe
  sie nicht `unklar` genannt, weil das Urteil dann nicht mehr die WDI-Reihe beträfe,
  sondern eine der vier tragenden Quellen des Vorhabens — und darüber entscheidet nicht
  dieses Paket. Die Zahl für den Fall (7 der 31 Sollreihen) steht im Befund.
- Der Datenkurator könnte die ILO mit **einem** Abruf
  (`www.ilo.org/rights-and-permissions`) in die geprüften Quellen aufnehmen. Dann wird
  Reihe 7 `frei` und drei Startwerte behalten ihren Datenanker.
- Für Reihe 13 gibt es nach `daten.md` **keine** Zollquelle unter freier Lizenz: WTO,
  WITS und UNCTAD TRAINS sind alle negativ oder widersprüchlich. `daten.md` nennt MacMap
  des ITC als ungeprüfte Alternative — falls jemand den Zollpfad retten will, ist das die
  einzige offene Adresse, und sie gehört dem Datenkurator, nicht mir.
- Nebenbei gesehen, nicht angefasst (gehört zu Paket 0006): `Referenceperiod` von
  `TM.TAX.MRCH.WM.AR.ZS` ist `1988-2022`, von `FP.CPI.TOTL.ZG` und `PA.NUS.FCRF`
  `1960-2025`, von den drei `SL.*.EMPL.ZS` `1991-2025`. Der Prüfjahrgang 1997–2021 liegt
  in allen vieren — das ist eine Aussage über die *Reihenlänge*, nicht über Lücken je
  Land, und die Deckungsfrage bleibt damit offen.
