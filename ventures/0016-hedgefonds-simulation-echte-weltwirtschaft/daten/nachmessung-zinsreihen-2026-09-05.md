---
typ: nachmessung
gegenstand: Reihe 9 (Leitzins), Datenfluss IMF.STA/MFS_IR
datum: 2026-09-05
durch: Betreiber-Lauf
berichtigt: deckungsbefund-1997.md, Abschnitt "Die Reihenliste nennt IWF IFS"
---

# Deutschland trägt sehr wohl Jahresreihen in `MFS_IR` — nur nicht die gewählte

`deckungsbefund-1997.md` führt für Reihe 9 die Gegenprobe `DEU.*.A` mit dem Ergebnis
„leer" und schließt daraus in der Tabelle: **DEU, Reihe vorhanden? nein, 0 Stützstellen.**
Dieselbe Abfrage am 2026-09-05 liefert **elf** jährliche Reihen.

## Gemessen am 2026-09-05

Endpunkt in allen Fällen:

```
https://api.imf.org/external/sdmx/3.0/data/dataflow/IMF.STA/MFS_IR/9.0.0/<SCHLUESSEL>?startPeriod=1997&endPeriod=2021
```

`<SCHLUESSEL>` ist `LAND.INDIKATOR.FREQUENZ`; `*` steht für alle.

| Land | `DISR_RT_PT_A_PT` | jährliche Reihen gesamt (`LAND.*.A`) |
|---|---|---:|
| USA | ja | 9 |
| BRA | ja | 7 |
| DEU | **nein** | **11** |
| CHN | nein | **0** |

Der Teil des alten Befunds, der trägt: Der **gewählte Code** `DISR_RT_PT_A_PT` fehlt für
DEU und CHN. Der Teil, der nicht trägt: „keine Jahresreihe" für DEU.

Für China bestätigt sich der Befund vollständig — `CHN.*.A` liefert im Fenster
1997–2021 nichts.

## Der brauchbare Kandidat für Deutschland

`S13BOND_RT_PT_A_PT` (Rendite von Staatsanleihen) liegt für USA **und** DEU vor:

| Land | Stützstellen | Fenster |
|---|---:|---|
| USA | 69 | 1953–2021 |
| DEU | 61 | 1957–**2017** |

Die deutsche Reihe **endet 2017**; im Modellfenster 1997–2021 fehlen damit vier Jahre.
Das ist eine Deckungslücke, kein Fehlen.

## Was das nicht ist

Eine Reihenwahl. Eine Staatsanleiherendite ist **kein Leitzins**: Sie ist ein Marktpreis,
kein Politikinstrument, und Reihe 9 speist in Schritt 3 ausdrücklich einen
*Politikpfad*. Ob sie als Ersatz taugt, ist eine Entwurfsfrage für den Architekten und
gehört in Paket 0117, nicht in diese Messung.

Ebenso wenig geprüft: Lizenzlage dieser Codes, die Frage, was die elf deutschen Reihen
inhaltlich messen (die Kennungen deuten auf Bankzinsen der MFI-Statistik, nicht auf
Politiksätze), und ob ein anderer IWF-Datenfluss China führt. `MFS_FMP` und `MFS_CBS`
sind angesehen, aber nicht ausgewertet.

## Warum die alte Messung danebenlag, ist offen

Möglich sind ein zwischenzeitlicher Umbau der Schnittstelle, ein Fehler in der damaligen
Abfrage oder eine andere Fensterangabe. **Nicht ermittelt.** Festgehalten ist nur, was
heute gilt — mit Endpunkt und Datum, damit die nächste Messung wieder vergleichbar ist.
