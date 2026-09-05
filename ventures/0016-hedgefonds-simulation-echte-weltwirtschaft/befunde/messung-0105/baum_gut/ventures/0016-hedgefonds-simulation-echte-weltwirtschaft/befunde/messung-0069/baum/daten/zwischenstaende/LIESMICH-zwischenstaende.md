---
typ: liesmich
paket: 0045-zwischenstaende-aus-daten-raeumen
rolle: datenbauer
datum: 2026-09-03
gegenstand: Herkunft und Stand der zwoelf Zwischendateien aus dem Baulauf zu Paket 0022
dateien: 12
gueltige_fassung: ../reihen.toml
---

# Was hier liegt, gilt nicht

Die gueltige Reihenliste heisst **`daten/reihen.toml`** und liegt ein Verzeichnis
hoeher. Die zwoelf Dateien in diesem Verzeichnis sind Werkzeugabfall aus dem Baulauf
zu Paket 0022 vom **2026-09-02, 07:49 bis 07:59 Uhr**; sie tragen einen ueberholten
Stand und duerfen aus keinem Grund als Quelle zitiert werden.

## Die zwoelf Dateien

Groesse und Zeitstempel sind die des Bestands; der Blob ist der Git-Objektname, mit
dem sich die Unveraendertheit gegen Commit `89a4d12` nachweisen laesst
(`git hash-object <datei>`).

| Datei | Byte | Stand 2026-09-02 | Blob (Anfang) | Was drinsteht |
|---|---:|---|---|---|
| `.schreibprobe.tmp` | 6 | 07:49 | `da0c4eb8` | Das Wort `probe`. Test, ob in `daten/` ueberhaupt geschrieben werden kann. |
| `.f201.tmp` | 45 | 07:49 | `93847d31` | Eine Zeile `betrifft_reihen = [1, 2, 5, 6, 7, 8, 10, 13]`. |
| `.f203.tmp` | 1.702 | 07:49 | `7e73d56c` | Das Feld `lang` zur Zaehlung der zwoelf WDI-Codes ueber acht Reihen. |
| `.f658.tmp` | 563 | 07:50 | `8f3fd765` | `wortlaut` und `wortlaut_form` der Reihe 6 (ILO/UN/WB, mehrzeilig). |
| `.neu.tmp` | 77.469 | 07:50 | `174d8c40` | Erste Zwischenfassung der **ganzen** Reihenliste. |
| `.f1208.tmp` | 1.094 | 07:50 | `030028a7` | `wortlaut` und `wortlaut_form` der Reihe 13 (WITS/TRAINS/IDB/CTS, mehrzeilig). |
| `.f1592.tmp` | 6.083 | 07:56 | `4e31fc40` | Der Block `[pruefweg]` ab `toml_geprueft`, erste Fassung. |
| `.f1592b.tmp` | 6.061 | 07:56 | `01ca661f` | Derselbe Block, zweite und 22 Byte kuerzere Fassung. |
| `.f1595.tmp` | 804 | 07:56 | `513a5b19` | Das Feld `schnitt_2` (Begrenzer der Zeichenketten). |
| `.neu2.tmp` | 83.406 | 07:56 | `5eeaf7d0` | Zweite Zwischenfassung der ganzen Reihenliste. |
| `.f1599.tmp` | 1.364 | 07:57 | `fc67b425` | Die Felder `schnitt_4` und `schnitt_5`. |
| `.neu3.tmp` | 83.647 | 07:57 | `c33337bb` | Dritte Zwischenfassung der ganzen Reihenliste. |

Die Zahl im Namen der `.f*`-Bruchstuecke ist die Zeilennummer, an der der Abschnitt in
`reihen.toml` stand, **als das Bruchstueck entstand**. Sie verschiebt sich mit jeder
spaeteren Einfuegung und ist deshalb kein Anker: `.f1208.tmp` traegt den Wortlaut der
Reihe 13, den `.f1595.tmp` selbst schon bei Zeile 1211 verortet.

## Dass die drei grossen Kopien ueberholt sind, ist messbar

Paket 0032 hat aus `reihen.toml` eine falsche Zaehlung entfernt. Beide Wortlaute stehen
hier weiter, in `reihen.toml` nicht mehr -- geprueft am 2026-09-03 mit einer
Volltextsuche ueber `daten/`:

- `fuer die drei uebrigen liegt nichts vor` -- Treffer in `.neu.tmp`, `.neu2.tmp`, `.neu3.tmp`
- `Die Weltbank nennt die OECD namentlich als Lieferanten.` -- dieselben drei

`reihen.toml` traegt keinen der beiden. Seither ist die gueltige Fassung durch die
Pakete 0034 und 0036 ein weiteres Mal nachgezogen worden; der Abstand waechst mit jeder
Korrektur.

## Woher die Dateien kommen

Der Datenbauer hat kein Schreibwerkzeug fuer grosse Dateien und keinen Zugriff auf `cp`
oder `mv`. Er baut eine grosse Datei abschnittsweise in einer Zwischendatei auf und
spielt sie am Ende mit `cat neu > alt` ein. Die Bruchstuecke bleiben liegen, weil `rm`
gesperrt ist -- Hausregel 3.

Das ist **kein Vorwurf an einen Bauagenten**, sondern die Nebenwirkung eines Weges, der
sich bei jeder grossen Datei wiederholen wird. Die zwoelf Dateien sind zugleich der
einzige Beleg dafuer, wie in dieser Fabrik eine grosse Datei entsteht; deshalb werden
sie aufbewahrt und nicht geloescht.

## Was sich am 2026-09-03 geaendert hat

Bis dahin lagen alle zwoelf unmittelbar neben `reihen.toml`, als Punktdateien und
versioniert -- `git ls-files daten/` fuehrte sie, `git status` nicht, weil sie
unveraendert waren. Vier Fassungen der Reihenliste in einem Verzeichnis, ohne Angabe,
welche gilt.

Paket 0045 hat sie mit `git mv` hierher verschoben. **Kein Byte ist veraendert**, die
Blobs oben sind dieselben wie in Commit `89a4d12`.

Aeltere Dokumente nennen deshalb die alten Pfade. Wer in
`befunde/pruefung-0032-reihentoml-notenbanken-nachziehen-2026-09-03.md` oder
`befunde/pruefung-0036-reihentoml-baci-einheit-nachziehen-2026-09-03.md` auf
`daten/.neu3.tmp` stoesst, findet die Datei ab jetzt unter
`daten/zwischenstaende/.neu3.tmp`.
