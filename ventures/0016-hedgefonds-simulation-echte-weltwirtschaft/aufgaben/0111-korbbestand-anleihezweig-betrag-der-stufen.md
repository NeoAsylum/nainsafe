---
id: 0111-korbbestand-anleihezweig-betrag-der-stufen
rolle: testentwickler
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: Eine neue Pruefung in `werte_probe.cpp` zum Anleihezweig von `korbbestand` (T48 Nr. 8, `technik.md:2128`). Der Nachweis ist zweiseitig: Am unveraenderten `kern/src/werte.cpp` laeuft `werte_probe` gruen; ersetzt man in `werte.cpp:598` `mal(betrag(stufen), konst.stufenweite)` durch `mal(stufen, konst.stufenweite)`, wird sie rot. Die Pruefung belegt einen Anleihesteckplatz mit **negativer** Stufenzahl und schreibt den erwarteten Beitrag als Zahl aus, dazu die verworfene Form als **andere** Zahl. Eine Pruefung, die auch am mutierten Modul gruen bleibt, zaehlt nicht.
---

# Der Anleihezweig von `korbbestand` nimmt den Betrag der Stufenzahl -- und das laesst sich heute verletzen

Vorgeschlagen vom `test-pruefer` aus der Pruefung zu Paket
`0088-werte-probe-vier-unbelegte-vorgaben` (`urteil: geprueft`). **Das Paket selbst ist in
Ordnung**; alle vier Vorgaben sind belegt, jede einzeln gemessen. Das hier ist eine
fuenfte Stelle derselben Familie, die dabei aufgefallen ist.

## Der Befund, gemessen

`betrag` kommt in `kern/src/werte.cpp` an drei rechnenden Stellen vor:

| Stelle | Vorgabe | belegt durch |
|---|---|---|
| `fondsanteil` (`:681`) | T48 Nr. 14, `\|stufen\| · stufenweite + anteil` | `probe_fondsanteil_und_korbbestand` (Paket 0002) |
| `positionswert_aus` (`:464`) | T48 Nr. 15, **ohne** Betrag | `probe_positionswert_traegt_das_vorzeichen` (Paket 0088) |
| `korbbestand`, Anleihezweig (`:598`) | T48 Nr. 8, `\|stufen(p)\| · stufenweite` | **niemanden** |

Die Mutation, die gruen bleibt -- in `korbbestand`, Anleihezweig:

```
mal(betrag(stufen), konst.stufenweite)   ->   mal(stufen, konst.stufenweite)
```

Gefahren am 2026-09-05 auf einer Arbeitskopie von `HEAD`, konfiguriert wie `baulauf.py`
(`RelWithDebInfo`, `-fwrapv -fno-fast-math`, Sanitizer aus `werkzeugkette.cmake`):

```
100% tests passed, 0 tests failed out of 14
```

Alle vierzehn Proben bleiben gruen. Zum Vergleich: Dieselbe Aenderung an `fondsanteil`
reisst vier Zusicherungen, dieselbe an `positionswert_aus` ebenfalls vier.

**Warum es durchrutscht, in einem Satz:** Die einzige Probe, die den Anleihezweig
ueberhaupt anfasst, belegt ihn mit `stufen = +3` (`werte_probe.cpp:560`) -- und bei einer
positiven Stufenzahl sind beide Formen dieselbe Rechnung.

## Die Vorgabe im Wortlaut

`specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md:2127-2128`:

```
korbbestand(z) = Σ ueber die 12 Koerbe   mal_geteilt(korbwert(l, s), fondsanteil(l, s), 10.000)
               + Σ ueber die  4 Anleihen mal_geteilt(anleihewert(l), |stufen(p)| · stufenweite, 10.000)
```

Die Betragsstriche stehen dort ausgeschrieben, und sie stehen dort **anders** als bei
Nr. 15 -- derselbe Unterschied, den Paket 0088 fuer Nr. 14 gegen Nr. 15 als „Entscheidung
des Entwurfs und keine Schreibweise" belegt hat.

## Warum es zaehlt

Der Anleihebestand eines Fonds mit **Short**-Positionen in Staatsanleihen ginge negativ in
`korbbestand` ein, statt seinen Betrag beizutragen. Von Hand, mit `anleihewert(DE) =
2.000.000`, `stufenweite = 250` und `stufen = -4` auf dem Anleihesteckplatz DE:

| Form | Rechnung | Beitrag |
|---|---|---|
| verbindlich (T48 Nr. 8) | `mal_geteilt(2.000.000, 4 · 250, 10.000)` | **+200.000** |
| Mutation | `mal_geteilt(2.000.000, −4 · 250, 10.000)` | **−200.000** |

400.000 Unterschied auf einer einzigen Anleihe. `korbbestand` traegt nach
`technik.md:2169` den `fonds.marktanteil` (`mal_geteilt(korbbestand(z), 10.000,
markt.wert)`) -- also **Mass 3**. Ein Fonds, der genug Anleihen short haelt, bekaeme einen
negativen Marktanteil.

## Warum das ein eigenes Paket ist und kein Ruecklauf an 0088

Die Abnahme von 0088 nennt vier Vorgaben, und alle vier sind erfuellt; ich habe jede
einzeln zweiseitig nachgemessen. `korbbestand` steht in keiner der vier, und
`werte.cpp:598` gehoerte nicht zum Auftrag. Ein Ruecklauf wuerde ein Kriterium
nachtraeglich verschaerfen, statt ein unerfuelltes einzuloesen -- genau die Begruendung,
mit der 0088 selbst kein Ruecklauf an 0002 wurde.

## Warum nicht Teil von 0110

`0110-mutationslauf-als-wiederholbarer-riegel` baut das **Messgeraet**, das solche
Luecken kuenftig automatisch findet. Dieses Paket schliesst **eine bereits gemessene**
Luecke. Das eine ersetzt das andere nicht: Auch mit 0110 braeuchte dieser Fall eine Probe,
die rot wird -- 0110 wuerde ihn nur wiederfinden, nicht abriegeln. Umgekehrt ist der Fall
hier ein brauchbarer Katalogeintrag fuer 0110, sobald es den Katalog gibt.

## Hinweise fuer den Bauagenten

- **Die vorhandene Probe ist einen Zeichen davon entfernt, es zu sehen -- und das ist der
  eigentliche Hinweis.** `probe_fondsanteil_und_korbbestand` (`werte_probe.cpp:527-564`)
  belegt den Anleihezweig bereits: Sie setzt `stelle_position(steckplatz_anleihe(DE))` auf
  **`3`** (`:560`) und sichert `korbbestand == 85'000` (`:563`). Bei einer **positiven**
  Stufenzahl ist `betrag(3) == 3`, die Mutation also unsichtbar. Gebraucht wird kein neuer
  Aufbau, sondern eine **negative** Stufenzahl -- genau derselbe Griff, mit dem 0088 den
  `waehrungswert` erst sichtbar gemacht hat, indem es den Wechselkurs von seinem Startwert
  wegbewegte.
- Der Anleihewert 2.000.000 fuer DE steht in derselben Probe schon bereit
  (`:557-561`): Wertschoepfung 2.000.000 bei Staatsschuld 10.000 Basispunkten.
- Die Bauart, die dieser Datei ihr Kopf vorgibt und die 0088 durchgehalten hat: die
  verworfene Form als **andere Zahl** daneben (`!= -200'000` neben `== +200'000`), nicht
  nur die richtige Zahl allein.
- **Nicht** `kern/src/werte.cpp` anfassen. Die Stelle ist dort richtig gebaut; was fehlt,
  ist der Riegel dahinter.
