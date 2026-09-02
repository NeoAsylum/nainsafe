# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, geschrieben vom Projektmanager. Fassung 2; die Fassung vom 2026-09-01
steht in `git log -p` und ist in ihrem wichtigsten Satz **widerlegt**. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

## Was sich seit dem 2026-09-01 grundlegend geändert hat

**Es gibt einen Übersetzer.** Die alte Fassung baute *jedes* Abnahmekriterium dieses
Vorhabens auf dem Satz „Kein Agent dieser Fabrik hat eine Shell, also kann niemand
übersetzen" auf. Der Satz stimmt für Agenten weiter — aber `baulauf.py` übersetzt seit
dem 2026-09-02 selbst und legt das Ergebnis nach `befunde/uebersetzung-<datum>.md`. Der
Lauf vom 2026-09-02 meldet `cmake`, `cmake --build` und `ctest` **grün**, maschinell
erzeugt.

Drei Folgen, und alle drei sind Gewinn:

1. **Ein Abnahmekriterium darf sich jetzt auf den Übersetzer stützen.** `static_assert`,
   eine Probe mit ausgeschriebenem Erwartungswert, ein `ctest`-Eintrag — das sind
   Nachweise und keine Behauptungen mehr. 0008 nutzt das als Erstes (2.480 Byte als
   `static_assert` statt als Kopfrechnung).
2. **Der Nachweis bleibt trotzdem zweistufig.** Grün heisst „die Zahlen passen
   zueinander", nicht „die Zahlen sind die richtigen". Wo ein Erwartungswert aus dem
   eigenen Code stammt, ist er eine Wiederholung; deshalb verlangen 0012 und 0013
   ausdrücklich Werte aus **unabhängiger Quelle** mit URL und Abrufdatum.
3. **Die Auflage „schreib keinen Code, den nie jemand übersetzt hat" entfällt.** Sie
   stand in jedem Paket und kostete jeden Bauagenten Aufmerksamkeit für ein Problem, das
   es nicht mehr gibt.

**Der Stack ist C++20** (ADR 0011). Alle Codepakete sind an diesem Lauf nachgezogen —
Dateinamen, Nachweise, Behältertypen. `technik.md` sagt an zehn Stellen weiter Rust; das
ist Paket 0011 und weiter offen. **Für den Bau gilt bis dahin der ADR, nicht der
Vorgabentext**, und das steht jetzt in jedem betroffenen Paket.

## Wo die Pakete stehen

| Paket | Rolle | Status | woran es hängt |
|---|---|---|---|
| 0001 Entwurfsabnahme | spielentwerfer | `fertig` | — |
| 0002 Fondsbewertung | kernbauer | `offen` | 0008 |
| 0003 Einheiten | kernbauer | `blockiert` | Entscheidung des Betreibers |
| 0004 Gerüst + Festkomma | kernbauer | **`gebaut`** | Kern-Prüfer |
| 0005 WDI-Lizenz | datenbauer | **`fertig`** | — |
| 0006 Deckung 1997 | datenbauer | **`gebaut`** | Daten-Prüfer |
| 0007 Adressverzeichnis | datenbauer | **`fertig`** | — |
| 0008 Zustand, 310 Felder | kernbauer | `offen`, startbereit | — |
| 0009 parameter.toml | datenbauer | **`gebaut`** | Daten-Prüfer |
| 0010 Zustandsausgabe | kernbauer | `offen` | 0002 + eine Entwurfsfrage |
| 0011 Stack auf C++ | **architekt** | `offen`, **nicht einplanbar** | `BAUROLLEN` |
| 0012 Zufall | kernbauer | `offen`, startbereit | — |
| 0013 Prüfsumme | kernbauer | `offen`, startbereit | — |
| 0014 Lizenz, übrige Reihen | datenbauer | `offen`, startbereit | — |
| 0015 Markierungssatz | datenbauer | `offen`, startbereit | — |

`python3 agents/baulauf.py 0016-… --trocken` zieht daraus vier Baupakete (0008, 0012,
0013, 0014) und drei Reviews (0004, 0006, 0009). Kein Bauagent läuft leer, und keine
zwei Pakete treffen sich in einer Datei.

**Fünf Statusnachzüge in diesem Lauf**, alle mit ihrer Begründung im jeweiligen Paket:
0005 und 0007 auf `fertig` (je ein Prüfbefund mit `urteil: geprueft`; bei 0007 lag er
seit dem 2026-09-01 vor und blieb liegen — mein Versäumnis), 0004, 0006 und 0009 auf
`gebaut`. Die drei Bauagenten hatten ihren Status nicht gesetzt; ich ziehe nach, weil
„gebaut" eine Tatsache über vorhandene Dateien ist und keine Abnahme. **`fertig` habe
ich in keinem Fall ohne Prüfbefund gesetzt.**

## Die Reihenfolge und warum sie so ist

```
0004 Gerüst (gebaut) ──> [Kern-Prüfer]
                                        0008 Zustand ──> 0002 Werte ──> 0010 Ausgabe
0012 Zufall     (frei)                       ^
0013 Prüfsumme  (frei) ──── Bytefolge ───────┘
0014 Lizenz     (frei)   0015 Markierung (frei)
```

**Warum 0008 nicht mehr auf 0004 wartet.** Es hing an ihm, weil ohne Gerüst kein Modul
existieren kann. Das Gerüst existiert und übersetzt grün, und `kern/CMakeLists.txt`
sammelt Quellen und Proben über `file(GLOB … CONFIGURE_DEPENDS)` ein — ein neues Modul
legt drei Dateien dazu und fasst keine gemeinsame an. Ein Rücklauf von 0004 träfe
`festkomma`, die Werkzeugkette oder den Sammelkopf; nichts davon braucht der `Zustand`.
Das spart dem kritischen Pfad einen ganzen Lauf. Kommt 0004 zurück, sperrt die
Kollisionsprüfung die beiden Pakete ohnehin gegeneinander, weil 0004 die
Platzhalterdateien in seinem Feld `dateien` führt.

**Warum drei Kernmodule gleichzeitig gehen.** Der Kastenschnitt aus T13 ist der
Kollisionsschnitt (Abschnitt 13 von `technik.md` sagt es), und in C++ ist er noch
schärfer als in Rust: ein Modul = Kopf + Quelle + Probe, drei eigene Dateien, keine
gemeinsame Modulliste. `zufall` (T11) und `pruefsumme` (T12) kennen den `Zustand` nicht
und können deshalb neben ihm entstehen.

**Warum 0013 den Schnitt hat, den es hat.** T12 verlangt zweierlei — die Summe über eine
Bytefolge und die feste Feldreihenfolge über die 310 Felder. Nur das zweite braucht den
`Zustand`; es bleibt bei 0008. Das ist eine Paketentscheidung, keine Entwurfsentscheidung:
T12 sagt nicht, in welcher Reihenfolge die beiden entstehen.

## Was der Geschäftsführer entscheiden lassen muss

**1. Klasse 2 misst zweierlei — laufende und konstante Preise.** *Neu, aus dem
Prüfbefund zu 0007 vom 2026-09-02, Befund 1, und die schwerste offene Sache.* T5 nennt
Klasse 2 „Tausend USD zu konstanten Preisen des Basisjahrs". In Klasse 2 liegen die 40
Handelsströme mit `Datenanker(14)` — Reihe 14 ist CEPII BACI, und BACI führt „thousands
current USD". Im selben Topf liegen die Wertschöpfungen aus Reihe 1, „BIP, konstante
Preise". Eine Deflationierung steht nirgends, und T50 zählt die Skalenübergänge
abschliessend auf; ein Preisbasiswechsel ist keiner davon.

Zwei Stellen, an denen es weh tut: `durchgriff = teile_gerundet(10.000 · H, H + N)`
addiert im Nenner laufende und konstante Preise und fällt systematisch zu klein aus, in
allen zehn Werten gleichgerichtet; und Maß 4 hielte reale Modellströme gegen eine
nominale Sollreihe und misste dann Inflation statt Modellgüte. **Das ist kein
Arbeitspaket** — es ändert T5, T49, T23 Punkt 5 und T8 und gehört Architekt und
Spielentwerfer.

**2. Wie kommen die Entwurfsaufgaben in einen Lauf?** Unverändert aus `ops/plan.md` vom
2026-09-02, und inzwischen dringender: `architekt` und `spielentwerfer` stehen in
`REVIEW`, aber nicht in `BAUROLLEN`. Daran hängen **vier** Sachen: 0011 (Stackwechsel in
`technik.md`), Punkt 1 oben, Reihe 9 samt R, und „Schaden". Der Plan empfiehlt, `BAUROLLEN`
um beide Rollen zu erweitern — eine Zeile in `baulauf.py`. Ich schliesse mich an und habe
nichts hinzuzufügen ausser der vierten Sache.

**3. Reihe 9 und R = 19.** Der Deckungsbefund vom 2026-09-01 sagt: Das Fenster 1997–2021
trägt nicht, R = 19 mit dem Fenster 2001–2020, und **zwei Reihen tragen überhaupt
nichts** — der Leitzins für Deutschland und für China. Nach T24 heisst das: Reihe
streichen oder Quelle ersetzen. Beides entscheidet der Spielentwerfer. Der Befund liegt
seit dem 2026-09-01, geprüft wird er im nächsten Lauf.

**4. „Schaden" in Gegenkraft 5 hat keine Rechenvorschrift.** Unverändert offen seit dem
2026-09-01 (`technik.md` Abschnitt 12, Beobachtung 3): `spiel.md` sagt, das Gegenbudget
wachse „proportional zum erlittenen Schaden"; welche Zahl das ist, steht nirgends. T50
legt nur die Einheit fest. Solange es offen ist, ist Gegenkraft 5 nicht baubar. Es
trifft den Kern erst in einigen Wochen — aber wenn der Weltschritt an der Reihe ist, ist
es zu spät, die Frage dann erst zu stellen.

**5. 0003 Einheiten, seit dem 2026-09-01 blockiert.** Das Paket verlangt Wrappertypen je
Größenklasse, T5 sagt „der Typ ist überall `i64`". ADR 0011 ändert daran nichts — in C++
ist der Wrappertyp so gangbar wie in Rust und dieselbe Abweichung von T5. Entweder ein
ADR gegen T5, oder das Paket bleibt liegen. Der Sachbefund dahinter ist über T47/T50
längst behoben.

**6. Wo die Zustandsausgabe wohnt.** 0010 legt die drei Ebenen in den Kasten `kern`; T13
gibt sie `schnittstelle`. Ein Aufruf, der Text **zurückgibt**, verletzt T13 nicht, aber
welcher Kasten sie beherbergt, entscheidet der Entwurf. Nicht dringend — 0010 hängt an
0002 —, aber vor dem Bau zu klären.

## Zwei Sachen, die vom Tisch sind

- **Der Übersetzungslauf** war die offene Frage der letzten Fassung. Er läuft und ist
  grün.
- **Die Rücklaufgrenze** ebenfalls: `baulauf.py:RUECKLAUF_MAX = 3` steht, und der Lauf
  meldet ein festgefahrenes Paket, bevor Tokens fliessen. Ich führe den Zähler trotzdem
  in jedem Paket unter *Rückläufe* mit — er kostet nichts und macht die Zahl lesbar,
  ohne Befunddateien zu zählen. Stand heute: überall 0.

Dazu eine Nebenwirkung dieses Laufs, die `ops/plan.md` betrifft: Der Grund, aus dem der
Plan seine Empfehlung B (Statuswechsel mechanisch aus dem Feld `dateien` setzen) auf
später vertagt hat — „genau dieses Feld nennt in fünf Paketen noch Rust-Namen" —, ist
weg. **Alle Codepakete tragen jetzt die Dateinamen, die auf der Platte stehen.** B wäre
ab sofort ziehbar.

## Was als Nächstes ansteht und noch kein Paket ist

**Die Rohdaten hat niemand.** `werkzeuge/aufbereitung` liest nach T23 „die eingefrorenen
Rohdateien"; unter `daten/` liegen drei Textbefunde und keine einzige Datenzeile.
`daten.md` sagt für alle vier tragenden Quellen ausdrücklich: keine Registrierung, kein
Abonnement — es ist also **kein Gate**, sondern ein Beschaffungsschritt, der bisher
niemandem gehört. Ich lege dafür kein Paket an, solange 0014 die Lizenzfrage für die
Reihen 1, 2, 5 und 6 nicht beantwortet hat: Reihe 2 trägt 12 der 31 Sollreihen, und wer
vorher herunterlädt, lädt möglicherweise das Falsche. Danach ist es das nächste grosse
Datenpaket.

**Die Reihenliste als maschinenlesbare Datei** (T23 Punkt 2 und 8: je Reihe die
T37-Klassifikation, `exogen_ab` und `verkettet_ab`) ist der natürliche nächste Schritt
nach 0014 und 0006 — nicht davor. Sie würde sonst die Spalte „Verdacht" fortschreiben,
von der der Prüfbefund zu 0005 gezeigt hat, dass sie keine Messung ist.
