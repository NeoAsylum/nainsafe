---
id: 0028-parameterdatei-querverweis
rolle: datenbauer
status: gebaut
haengt_an: [0015-adressen-markierungssatz, 0009-parameterdatei-schluessel]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Ein Querverweis in `parameter.toml`, der seit dem 2026-09-02 ins Leere zeigt

Vorgabe: `befunde/pruefung-0015-adressen-markierungssatz-runde2-2026-09-02.md`, Befund 2.
Der Prüfer hat ihn ausdrücklich **nicht** als Rückgabegrund für 0015 gewertet: Das Paket
hat `parameter.toml` korrekt nicht angefasst, der Satz ist durch die Änderung in der
**anderen** Datei falsch geworden.

**Das ist ein Halbsatz, kein Umbau.** Fass ausschliesslich an, was hier steht.

## Der Befund

`parameter.toml` Zeilen 145–149 sagen:

> **Ein `*` hinter einem Schluesselnamen im Kommentar heisst: Der Name steht in keinem
> Dokument woertlich und ist nach dem Muster der uebrigen gebildet.** Dieselbe
> Kennzeichnung wie im Adressverzeichnis aus Paket 0007.

**Der erste Satz ist weiterhin richtig** und bleibt, wie er ist — für Schlüsselnamen
stimmt er, weil sie keine Gebiets- und Sektorindizes tragen. Falsch ist der **zweite**:
Es ist nicht mehr dieselbe Kennzeichnung. Im Adressverzeichnis heisst `*` seit Paket 0015
ausdrücklich *nicht* „steht in keinem Dokument wörtlich" — dort sitzt die Marke an den
**Bestandteilen**, und `handel.US.CN.1` steht nirgends wörtlich und trägt trotzdem keine
Marke.

Wer `parameter.toml` liest und dem Querverweis folgt, landet bei einer anderen Regel als
der, die dort steht. Das ist die teure Sorte Fehler: Beide Sätze für sich sind richtig,
nur die behauptete Gleichheit ist es nicht.

## Was du tust

Ersetz den zweiten Satz durch die wahre Aussage: Die beiden Kennzeichnungen sind
**verwandt, aber nicht dieselbe** — hier heisst `*` „nicht wörtlich belegt", im
Adressverzeichnis „ein Bestandteil ist neu". Sag in einem Halbsatz, warum der Unterschied
für Schlüsselnamen folgenlos ist (keine Gebiets- und Sektorindizes, also fallen die beiden
Regeln hier zusammen), und verweis auf die Stelle im Adressverzeichnis, statt sie für
gleich zu erklären.

**Sonst nichts.** Die 50 Schlüsselnamen, die Zahl 25, der Abschnitt `BEFUNDE` am Dateiende
und jeder Wert in der Datei bleiben unberührt.

## Reihenfolge

Dieses Paket hängt an 0015, und zwar nicht formal: Der Satz, auf den du verweist, wird
dort gerade geschärft (Rücklauf 2 nimmt die Elferliste aus T46 mit auf). Schreib den
Querverweis gegen die Fassung, die dann in `daten/adressen.md` steht — **lies sie, bevor
du formulierst**, statt dich auf das Zitat in diesem Paket zu verlassen.

**2026-09-02, Projektmanager: 0009 als zweite Abhängigkeit nachgetragen.** 0015 ist seit
heute `fertig`, damit wäre dieses Paket startbereit — es darf trotzdem noch nicht laufen.
`parameter.toml` gehört Paket 0009, und 0009 steht auf `gebaut` und wartet auf sein Urteil.
Der Kollisionsschutz des Baulaufs sieht das nicht: `startbereit()` vergleicht die
Dateilisten nur unter den Paketen im Zustand `offen`, ein Paket im Review ist für ihn kein
Anspruch auf seine Datei. Wer hier jetzt schriebe, legte dem Prüfer der 0009 fremde Arbeit
in dieselbe Datei — und 0009 steht bei zwei von drei Rückläufen, ein ungerechter dritter
würde es endgültig festfahren. Genau diese Verwechslung hat den Prüfer der 0015 einen
halben Befund gekostet.

Sobald 0009 `fertig` ist, fällt die Abhängigkeit von selbst weg und das Paket wird
startbereit. Es ist bis dahin `offen` mit unerfüllter `haengt_an` — die ehrliche Form; der
Scheduler zieht es nicht.

## Abnahme

1. **Der zweite Satz behauptet keine Gleichheit mehr**, und der Unterschied zwischen den
   beiden Bedeutungen von `*` steht in einem Satz da. Der Prüfer liest beide Stellen
   nebeneinander — `parameter.toml` und den Markierungsabsatz in `daten/adressen.md` — und
   prüft, ob die Beschreibung in `parameter.toml` die dortige Regel richtig wiedergibt.
2. **Der erste Satz ist unverändert.** Für Schlüsselnamen gilt „nicht wörtlich belegt"
   weiter; eine Änderung daran wäre ein Rücklauf, weil sie 25 Markierungen in derselben
   Datei ungültig machen würde.
3. **Keine zweite Änderung an der Datei.** Der Prüfer legt `git diff` an; was hier nicht
   steht, ist ein Rücklauf. Der Nachweis wird an der Datei geführt, **nicht** über
   `git diff --stat`: Der Commit dieses Vorhabens trägt regelmässig fremde Arbeit und
   einen fremden Betreff.

## Was ausdrücklich kein Befund ist

- **Dass `parameter.toml` weiterhin `# PLATZHALTER` bei `druck_max` und `stufen_max`
  trägt.** Das ist gewollt und Gegenstand anderer Pakete.
- **Die Gültigkeit der Datei als TOML.** Ein Parser läuft in dieser Umgebung nicht; das
  steht als Punkt 3 im Rückstand und gehört in den Runner. Behaupte vor allem nicht, einer
  sei gelaufen.

## Rückläufe

0.
