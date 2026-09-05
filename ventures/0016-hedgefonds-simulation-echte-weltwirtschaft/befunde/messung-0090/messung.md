---
typ: messung
paket: 0090-rueckstand-ueberschrift-fuenf-tote-zitate
rolle: datenbauer
datum: 2026-09-05
werkzeug: werkzeuge/belegstellen/bau/belegstellen_riegel, Python 3.14.4 mit tomllib
skripte: befunde/messung-0090/probe.py, befunde/messung-0090/schnitte.py
---

# Was gemessen ist, und woran es gemessen ist

**Bezugsstand, vor der ersten Schreibbewegung notiert.** Der Arbeitsbaum stand auf dem
Commit `87f2604`. Die beiden Dateien trugen die Blobs

| Datei | vor dem Lauf | nach dem Lauf |
|---|---|---|
| `daten/reihen.toml` | `cce4936c339beb6ba4e63baa77c2eaa51e56cc59` | `3ad2996765697f2426ee7bb01e608e7989710356` |
| `daten/einheitenbefund-pwt-baci.md` | `354aff593f2887061ef8b06b9c0ef7e0d616a879` | `09b0e93e9757bb5308c3aec16fc41e682db31cc1` |

Der Bezugsstand steht hier, weil er im Lauf gebraucht wurde und nicht vorsorglich: Der
fremde Commit `a127600` (`architekt`, Paket 0051) hat mitten in diesem Lauf
`einheitenbefund-pwt-baci.md` mitcommittet. Die Datei steht deshalb nicht mehr in
`git status`, und wer gegen `HEAD` misst, sieht meine Aenderung nicht. Der vollstaendige
Vergleich ist `git diff 354aff5 09b0e93` und `git diff cce4936 3ad2996`; er ist in
keinem einzelnen Commit ganz zu sehen.

## Teil 1: der Riegel gegen den Arbeitsbaum

| | vor dem Lauf | nach dem Lauf |
|---|---|---|
| Zitate der geprueften Form | 38 | 33 |
| davon aufgeloest (Untergrenze 16) | 38 | 33 |
| **uebergangene Fundstellen** | **58** | **58** |
| Befunde zu den fuenf Fundstellen | 0 (die Ueberschrift stand wieder da) | 0 |

Die fuenf Fundstellen sind aus der Zaehlung heraus: 38 minus 5 ist 33. Sie sind
**nicht** unter die uebergangenen gewandert -- deren Zahl ist unveraendert 58, und die
Liste ist Eintrag fuer Eintrag dieselbe. Verschoben haben sich allein die
Zeilennummern: in `reihen.toml` um fuenf nach unten (die Leseregel 1 im Kopfkommentar
waechst von neun auf vierzehn Zeilen), in `einheitenbefund-pwt-baci.md` ab Zeile 103 um
zwei. Beispiel: `daten/reihen.toml:1608` heisst jetzt `:1613`, mit demselben Grund und
demselben gesuchten Namen.

Die Untergrenze `AUFGELOEST_MINDESTENS` steht bei 16; 33 liegt darueber. Die Abdeckung
faellt um fuenf, und zwar rechtmaessig -- diese fuenf Zitate hatten kein Ziel mehr
verdient, das sie nachschlagen laesst.

## Teil 2: die Gegenprobe, und sie ist der Nachweis

Der erste Teil beweist wenig: Der Projektmanager hat die Gliederungszeile am 2026-09-05
als Stuetze auf Zeit wieder in `rueckstand.md` eingesetzt, damit die Werkzeugkette nicht
rot bleibt, solange dieses Paket wartet. Der Vorher-Stand war deshalb schon gruen.

Gemessen ist deshalb an einer Kopie **ausserhalb des Repos**, unter
`$TMPDIR/gegenprobe-0090`, in der genau diese eine Zeile geloescht ist (das Skript
prueft nach, dass sie dort genau einmal stand, und bricht sonst ab). Der Bau der Kopie
stellt nach, was der Riegel erwartet: `<X>/ventures/<name>` **und** `<X>/specs/<name>`.
Ohne die zweite Wurzel faellt die halbe Zielmenge weg und der Lauf endet an der
Untergrenze mit Code 2 -- der erste Versuch ist genau so ausgegangen und steht hier,
damit niemand die Gegenprobe fuer bestanden haelt, die in Wahrheit abgebrochen ist.

Ergebnis auf der Kopie mit geloeschter Gliederungszeile: **Rueckgabecode 0**, 33 Zitate,
33 aufgeloest, 58 uebergangen, **kein Befund zu einer der fuenf Fundstellen**. Bedingung 2
bleibt zu ihnen still, obwohl die Zeile, an der sie bis heute hingen, nicht mehr da ist.
Damit ist das Abnahmekriterium erfuellt.

## Der eine Befund, der nicht mir gehoert

Im Arbeitsbaum ist der Riegel im Augenblick trotzdem rot, und zwar an **Bedingung 1**:

```
1 Verweis(e) zeigen mit einer Zeilennummer in eine fremde Datei:

  kern/test/zustandsausgabe_probe.cpp:379  -> specs/.../technik.md
      T5 (`specs/.../technik.md`, Zeile 278
```

Die Datei steht nicht in meiner Dateiliste, ist zum Messzeitpunkt uncommittet und wurde
um 04:28 geschrieben -- ein Paket, das gerade laeuft. Ich fasse sie nicht an. Dass sie
und nicht mein Eingriff die Ursache ist, ist gemessen und nicht behauptet: Setzt man in
der Kopie **nur** diese eine Datei auf ihren Stand aus `87f2604` zurueck und laesst die
geloeschte Gliederungszeile geloescht, gibt derselbe Riegel Code 0 (dritte Messung in
`probe.py`). Bedingung 1 zaehlte vor meinem Lauf 5 Zeilenverweise mit 0 Dateinamen
daneben; jetzt ist es einer mit Dateinamen.

## `reihen.toml`, Bilanz mit `tomllib`

Gueltiges TOML 1.0; `reihe` 19 Eintraege, `widerspruch` 9, die Wurzel sechs Tabellen;
die Summe von `sollreihen` ueber die 19 Reihenbloecke ist 27 und gleich
`zaehlung.sollreihen_gesamt`; zweimal eingelesen ergibt dieselbe Struktur.

Blattwerte 1226 vorher, 1227 nachher. Neu ist genau einer
(`datei.nachgezogen_durch.9`), weggefallen keiner. Von den 1226 gemeinsamen Schluesseln
tragen **vier** verschiedene Werte: `reihe.1.offen.0`, `reihe.1.umrechnung.1.beleg`
(die Liste `reihe` zaehlt ab null, `reihe.1` ist Reihe 2), `widerspruch.4.entscheidet`
(Widerspruch Nr. 5) und `pruefweg.toml_geprueft`, das die Bilanz traegt und deshalb in
ihr vorkommt. Keiner doppelt, keiner ausgelassen. Kommentare sind keine Blattwerte;
geaendert ist dort genau eine Stelle, die Leseregel 1.

Die sechzehn Muster der sieben Schnitte sind einzeln neu gezaehlt (`schnitte.py`), nicht
als Summe: alle sechzehn unveraendert, dazu die sieben Tabellentypen von `schnitt_3`
einzeln. Bei `schnitt_1` sind zusaetzlich die sechs Trefferkontexte alt gegen neu
verglichen und zeichengleich dieselben.

## Was an den fuenf Stellen jetzt steht

Alle fuenf nennen den Commit `81853b8` (`projektmanager`, 2026-09-04), der die
Gliederungszeile aus `rueckstand.md` entfernt hat, weisen ihren Bezug ausdruecklich als
historisch aus und nennen `81853b8~1` als den Stand, in dem die Stelle nachzulesen ist.
Zwei von ihnen tragen darueber hinaus den gemeinten Wortlaut selbst -- „Reihe 9 und
R = 19" in `widerspruch.4.entscheidet` und „Klasse 2 misst zweierlei -- laufende und
konstante Preise" in `einheitenbefund-pwt-baci.md`; die drei uebrigen tragen die Sache,
um die es geht, ohnehin im eigenen Satz.

Keine der fuenf nennt danach noch ein Schluesselwort mit einem Zitat unmittelbar
dahinter. Das ist die Form, an der Bedingung 2 ein Zitat erkennt -- und der Grund, warum
sie auch dann still bleibt, wenn die Zeile in `rueckstand.md` wieder verschwindet.
