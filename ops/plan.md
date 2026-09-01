# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-01, geschrieben vom Geschäftsführer. Erster Lauf dieser Rolle, kein
Vorgängerplan.

## Wo das Vorhaben steht

Der Entwurf ist **abgenommen, nicht freigegeben**: Nach fünf Rückläufen hat der Betreiber
Paket `0001-entwurf-abnahme` auf `fertig` gesetzt und damit das Tor zum Bau geöffnet — der
Prüfer hatte zuletzt weiter zwei Befunde. Gebaut ist bisher **nichts**;
`ventures/0016/` enthält Aufgaben und Befunde, aber keine einzige Quelldatei. Der nächste
Nachtlauf ist der erste Baulauf dieses Vorhabens: Er beginnt beim Projektmanager und
trifft zwei offene Pakete, von denen 0003 auf 0002 wartet.

## Der Engpass

**Paket 0002 — `korbwert(l, s)` und `positionswert(p)`.** Es ist der einzige nicht
blockierte Bauauftrag, und alles Übrige hängt daran: 0003 als Abhängigkeit, über
`fondsvermoegen(z)` (T47) die Siegbedingung, die Abrechnung, die Mandatsprüfung, der
Invariantentest und `v(z)`, darüber Maß 1 bis 3, und über denselben Marktkorb zusätzlich
Gegenkraft 3.

Die eigentliche Schwierigkeit steht nicht im Paket: **Es verlangt eine
Entwurfsentscheidung von einem Bauagenten.** Die Bauart `Menge × Preis` ist vorgegeben,
*welche* Menge, ist es nicht — T15 nennt Kapitalstock und Wertschöpfung, gewählt ist
keine, und für die vier Anleihe-Steckplätze existiert gar kein Preis. Der Kernbauer
entscheidet damit ohne Vorgabe und ohne Test, an dem seine Wahl scheitern könnte. Das ist
die bewusste Folge der Abnahme und vertretbar — aber es ist eine Entscheidung im Bau, die
niemand gegenliest.

## Was quer liegt

- **Gate 2 gibt es weder als Dokument noch als Rolle.** Die Idee steht auf `erkundung`,
  während Code entstehen soll; Ökonom, Vertriebsplaner, Compliance-Prüfer,
  Urlaubstester, Antrags-Vorbereiter und Konzept-Judge liegen unter
  `agents/rollen/archiv/`. Vom Betreiber am 2026-08-31 so entschieden und in `gates/0016-g1.md`
  festgehalten. Nebenwirkung, die dort nicht steht: `nachtlauf.py:wip()` liest den Status,
  zählt 0016 also als `aktiv` und **nicht** als `im_bau` — das WIP-Limit „höchstens eine
  im Bau" greift für dieses Vorhaben nicht mehr. Bei einem einzigen Vorhaben folgenlos.
- **Die Konvergenzbremse steht hinter der Tür, die sie sichern soll.**
  `konzeptlauf.py:RUECKLAUF_MAX = 3` würde bei fünf `zurueck`-Urteilen sofort greifen —
  aber weil Paket 0001 `fertig` ist, ruft der Nachtlauf den Konzeptlauf nicht mehr auf.
  Im Baulauf gibt es **keine** entsprechende Grenze: `offen → gebaut → zurueck → offen`
  ist unbeschränkt, und dieselbe Nichtkonvergenz kostet dort Code statt Prosa.
- **Eine Prüfung vor dem Bau ist niemandem zugewiesen.** `spiel.md` nennt die
  Lizenzfrage des aggregierten Zollsatzes (WITS-Ableitung, Drittanbieter-Ausnahme der
  WDI-Lizenz) ausdrücklich „zu prüfen, bevor gebaut wird", dazu vier weitere WDI-Reihen
  (Nr. 7, 8, 10, 13) — Aufgabe des Datenbauers, für den kein Paket existiert. Ist der
  Zollsatz gesperrt, verliert der Rückvergleich sein wichtigstes verankertes Instrument.
  Vier Abrufe schließen die Frage.
- **Die Lücke von Gate 1 ist unbewacht.** `notizen/lehren.md` (2026-08-31) weist das
  Schließen der 170-gegen-121-Lücke Ökonom und Vertriebsplaner zu und nennt Gate 2 als
  die Stelle, an der ein Scheitern sichtbar würde. Alle drei sind archiviert. Es gibt
  derzeit keine Rolle und keinen Lauf, der diese Zahl je wieder anfasst.
- **Runde 5 war ein Leerlauf**: `pruefung-...-runde5-2026-09-01.md` hat 0 Byte. Für einen
  Leser ist das eine verbrauchte Runde, für `entwurfsurteile()` gar keine — ein leerer
  Output fällt stillschweigend durch die Zählung.

## Was der Betreiber entscheiden muss

**1. Braucht der Baulauf eine Rücklaufgrenze, bevor er das erste Mal läuft?**
Genau diese fehlende Grenze hat im Entwurf 95 $ und fünf Runden gekostet; im Bau ist sie
nicht eingebaut.

- *A:* Nichts tun, erst messen. Billig, wiederholt aber einen belegten Fehler.
- *B:* Grenze je Paket — nach dem zweiten `zurueck` steht es auf `blockiert` und geht in
  diesen Plan. Der Projektmanager kann sie durchsetzen, er setzt `fertig` und `blockiert`
  ohnehin.
- *C:* Grenze über das Vorhaben statt über das Paket. Gröber, trifft den Fall aber nicht.

**Empfehlung: B.** Der Fehler ist einmal belegt, die Regel gehört an die Stelle, die sie
erreicht, und im Bau kostet eine Runde mehr als im Entwurf.

**2. Wann wird die Zahl aus Gate 1 wieder angefasst — 170 nötige gegen 121 erreichbare
Käufer im Monat?** Sie ist vertagt, nicht beantwortet, und die Rollen, die sie beantworten
sollten, liegen im Archiv. Ich empfehle, sie **nicht** jetzt zu klären, sondern an ein
Ereignis zu binden: den ersten bestandenen Rückvergleich. Vorher ist jede Marktzahl eine
Wette auf ein Produkt, das noch nicht rechnet; nachher gibt es etwas, das man zeigen kann.
Ohne festen Auslöser fällt die Frage sonst aus dem Repo.

## Die eine Zahl

**0 Zeilen Code bei 242 kB Entwurf.** Das ist derzeit die einzige Zahl, die zählt — sie
ersetzt sich selbst, sobald der Kern läuft, durch die Abnahme des Rückvergleichs:
**16 Prüfgegenstände, höchstens 2 dürfen reißen** (T37).
