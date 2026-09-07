---
typ: messung
paket: 0147-belegstellenriegel-ortsfrage-mit-anker
datum: 2026-09-07
ergebnis: nicht_ausgefuehrt
---

# Der Messstand steht, gelaufen ist er nicht

**Das Wichtigste zuerst, damit es niemand uebersieht:** Dieser Lauf hatte **keine
Shell**. `messung.py` ist geschrieben und vollstaendig, aber **nicht einmal
ausgefuehrt**. Jede Zahl unten ist am Quelltext hergeleitet und **nicht gemessen**. Wer
das Paket abnimmt, laesst zuerst `python3 messung.py` laufen; sie gibt 0 oder 1 zurueck
und braucht kein Urteil.

## Was schon da war und was dieser Lauf beitraegt

Der Quelltext des Pakets lag am 2026-09-07 bereits im Baum und war eingecheckt:
`beurteile_ort`, `zaehlt_als_zitat`, `ORTSFAELLE` (4), `selbsttest_ortsurteil`,
`waehle_zitatform`, `FORMFAELLE` (4), `selbsttest_zitatform`, beide in `pruefe_zitate`
verdrahtet, beide in `main` aufgesummt. Der Status des Pakets stand trotzdem auf
`offen` -- genau der Fall, den die Rollendatei mit 0026 beschreibt.

Beigetragen hat dieser Lauf den fehlenden Teil: den Messstand. Am `.cpp` ist **nichts**
geaendert; der Uebersetzungsbericht vom 2026-09-06 fuehrt den Riegel gruen (7,44 s,
Code 0), und ein ungemessener Eingriff haette das nur riskiert.

## Die neun Mutanten und der erwartete Ausgang

Alle sterben am Selbsttest (Rueckgabe 2), also **bevor** der Bestand gelesen wird.

| Mutant | Eingriff | erwartet reisst |
|---|---|---|
| M1 | `Zielart::Ausserhalb` -> Grund als Konstante ohne Namen | Ortsfall 2 |
| M2 | `Zielart::Ungelesen` -> Grund als Konstante ohne Namen | Ortsfall 3 |
| M3 | `Zielart::Tot` -> Ausgang `Uebergangen` statt Befund | Ortsfall 4 (Ausgang) |
| M4 | Regelfall -> `Uebergangen` statt `Nachschlagen` | Ortsfall 1 |
| M5 | `zaehlt_als_zitat` -> immer `false` | Ortsfall 4 (Zaehlung) |
| M6 | Form mit Anfuehrung zuletzt gefragt | Formfall 2 |
| M7 | Form ohne Anfuehrung zuletzt gefragt | Formfall 3 |
| M8 | Form mit Wortabstand entfaellt | Formfall 1 |
| M9 | jede Stelle gilt als Fundstelle | Formfall 4 |

M1--M3 und M6--M7 sind die Abnahme. M4, M5, M8 und M9 stehen dazu aus der Rollenregel
*ein Test, der nie fehlschlaegt, prueft nichts*: ohne sie haetten vier der acht neuen
Faelle keinen eigenen Mutanten.

**Die dritte Vertauschung fehlt mit Absicht.** Anfuehrung und blosser Name koennen an
derselben Stelle nie zugleich zutreffen -- `ist_namensanfang` verlangt Grossbuchstabe,
Ziffer oder grossen Umlaut, keines der elf Anfangszeichen aus `KLAMMERN` ist eines
davon. Sie reisst also nichts, und die Begruendung steht im Quelltext statt als
gruener Fall in der Tabelle.

## Was der Messstand ueber 0106 hinaus tut

Drei Dinge, jedes aus einer bezahlten Lehre:

1. **Der Vergleichsstand wird geholt, nicht eingetragen** (`git log -S "Paket 0147"`,
   dann `^`), danach mit vier Proben belegt und abgedruckt. Eine eingetragene Kennung
   verfaellt in Stunden -- Paket 0135.
2. **Der Auswerter wird zuerst selbst beprobt** (Teil 0). Er muss alle neun Marken
   namentlich lesen *und* an einer gruenen Ausgabe nichts finden.
3. **Gezaehlt wird aus der Schlusszeile des Riegels**, nicht aus meiner Namensliste.
   *"Genau ein Fall gerissen"* haengt damit nicht daran, dass ich alle Marken kenne.

**Ein Befund gegen `messung-0106/messung.py`, gemeldet und nicht behoben** (fremdes
Paket): Seine Liste `FREMDE_FAELLE` fuehrt `Namensfall` und `Abstandsfall`. Der Riegel
schreibt diese beiden Tabellen aber als `Selbsttest N:` und `Selbsttest Abstand N:`.
Die zwei Eintraege konnten dort nie treffen -- die Pruefung *"keine fremde Tabelle
gerissen"* war fuer sie blind. Dieselbe Bauart steckt in jedem Messstand, der die
Marken abschreibt statt sie zu beproben.
