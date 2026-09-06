# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-06 08:30. Abgedeckt: 2026-09-04 07:45 bis heute — **233 Commits in zwei
Tagen ohne Bericht.** Der Grund lag in `agents/tageslauf.py` und ist seit 08:24 behoben.

## Wo das Vorhaben steht

**Der Apparat steht, die Welt rechnet nicht.** Aus 77 Paketen sind 180 geworden: 147
fertig, 23 offen, 4 blockiert, **0 gebaut** — der Prüfstau, der drei Pläne lang der Engpass
war, ist weg; Review und Prüfstufe stehen im Trockenlauf beide auf null. Acht Manifeste
übersetzen grün, 38 Tests laufen durch, `werte.cpp` gibt es jetzt mit 47 kB statt gar
nicht. **Die Geldfrage des letzten Plans ist gegenstandslos:** 3.372,5 von 12.000 $
verbraucht, Spielraum 8.627,5 $.

## Der Engpass

**Die sechs Schritte der Runde haben kein einziges Arbeitspaket — und das Paket, das der
Wirtschaft am nächsten kommt, steht auf Platz 13 von 13 einer seriellen Schlange.**

`kern/include/kern/schritt.hpp:12` sagt es selbst: der Rahmen ist „**keine gerechnete
Welt**". Von 23 offenen Paketen liegen **13 auf `specs/…/technik.md`** (297 kB), 5 auf
Riegelwerkzeugen, je eins auf `parameter.toml` und `reihen.toml`; **4 berühren `kern/src`**.
Zwei Pakete auf einer Datei laufen nie gleichzeitig — die Bahn ist seriell. Der
Projektmanager schreibt es 0172-weltpreis wörtlich in den Vermerk: *„Du bist das letzte von
dreizehn Paketen auf `technik.md`."* Das ist die Preisbildung aus Schritt 4, und sie steht
hinter zwölf Zähl- und Belegkorrekturen.

Der Bruchtester hat dasselbe unabhängig gemessen (0157, `blockiert`): *„Keines der 26
offenen Pakete baut einen Rumpf für `schritt_2` bis `schritt_6`."* Zwei Rollen, zwei Wege,
derselbe Befund.

## Was quer liegt

- **Der Grund, aus dem der Spielmodus abbricht, ist abgelaufen.** `schritt.hpp:43` nennt
  als Sperre „`kern::werte` (Paket 0002, **blockiert**)" und „T32 unbeauftragt". Beides
  gilt nicht mehr: 0002 ist `fertig`, `werte.cpp` hat 47 kB, `aktion.hpp` 19 kB, und
  `aktion_probe` ist grün. Die Datei ist seit 2026-09-04 19:23 nicht angefasst. Niemand ist
  beauftragt nachzusehen, ob `Modus::Spielmodus` heute baubar wäre — die Sperre steht nur
  noch als Kommentar.
- **Die geschlossene Schleife hat sich nicht geöffnet, sie ist gewachsen.** 48 der 180
  Pakete betreffen Riegel, Belegstellen, Zahlwörter, Bezeichner. **Fünf der acht Manifeste
  sind Riegelwerkzeuge**, vier der 38 Tests prüfen Riegel. Beide heute angenommenen
  Vorschläge (0193, 0194) sind Apparat. Prüfer schlagen vor, was sie sehen — und sie sehen
  nur, was gebaut ist. Das ist die Ursache des Engpasses, nicht seine Begleiterscheinung.
- **Daten weiter nicht geladen** — nur als Zahl fortgeschrieben, nicht als Frage neu
  gestellt: `daten/roh/` gibt es nicht, `reihen.toml` ist von 115 auf **185 kB** und 105
  Reihen gewachsen und sagt in Zeile 18 unverändert „**Sie enthaelt keine Datenzeile.**"
- **Zwei Nummern doppelt vergeben:** 0172 und 0185 gibt es je zweimal. Der Projektmanager
  hat es bei 0172 vermerkt und richtig entschieden — die Kennungen sind verschieden, der
  Baulauf unterscheidet sie. Es kostet nur jeden Leser eine Rückfrage.

## Was der Betreiber entscheiden muss

**Ob die Prüfer weiter die Tagesordnung setzen.** Die Reihenfolge kann ich ändern, die
Herkunft der Pakete nicht: Vorschläge kommen von Prüfern, Prüfer lesen Gebautes, also
schlägt niemand „baue Schritt 4" vor. Geld bindet nicht mehr — 8.627,5 $ Spielraum und vier
Tage Woche. Es ist eine reine Inhaltsfrage, und darum stelle ich sie.

- **A — laufen lassen.** Die `technik.md`-Bahn ist 13 Pakete tief und seriell. Die
  Preisbildung ist am Montag nicht gebaut, und 0157 löst sich nicht auf.
- **B — ein Satz in `agents/rollen/projektmanager.md`:** In jedem Baudurchgang muss
  mindestens ein offenes Paket einen rechnenden Schritt der Runde aus `spiel.md`,
  Abschnitt *Die Schleife*, bauen — 3 Politik, 4 Wirtschaft, 5 Reaktion. Vorschläge zu
  Riegeln und `technik.md` gehen dahinter.

**Empfehlung B.** Ein Satz, kein Lauf. Der Projektmanager schreibt zu 0157, er könne es
nicht einhängen: *„Es gibt kein `haengt_an`, das ich schreiben könnte."* Er wartet auf ein
Paket, das entstehen darf, aber niemanden hat, der es schneidet — und `spiel.md` nennt die
sechs Schritte seit dem 2026-09-01 wörtlich. Es fehlt der Auftrag, nicht der Entwurf.

## Vorrang

1. **0165** — Schaden an zwei Zustandseingängen; zugleich die Reihenfolgesperre vor
   0172-weltpreis. Es steht nur deshalb oben, weil das nächste darauf wartet.
2. **0172-weltpreis** — der Zollfaktor ohne Untergrenze, Schritt 4. Von den dreizehn
   Paketen auf `technik.md` das einzige, das die Wirtschaft bewegt. **Vor** 0064, 0068,
   0084, 0092 statt hinter allen.
3. **0148** — Zielkennung je Aktionsart. Ohne sie bleibt Schritt 2 leer, und der
   Spielmodus bricht weiter mit einer Begründung ab, die nicht mehr gilt.
4. **0177** — Rundennummer-Schranke am Startwertzugang, eins von nur vier offenen Paketen
   an `kern/src`.
5. **0186** — Verlaufglied mit fremder Rundennummer; die einzige Kernbahn, die neben
   `technik.md` überhaupt frei läuft.

**0064, 0068, 0084, 0092, 0149 und 0181 ans Ende der `technik.md`-Reihe.** Es sind
Zählfehler und Belegkorrekturen in einer Entwurfsdatei. Jedes Glied, das vor der
Preisbildung steht, kostet sie einen Tag — und die Bahn ist seriell, also ist das keine
Vorliebe, sondern Arithmetik.

## Die eine Zahl

**1 von 310** — vorher 0 von 310. Eine Runde im `weltlauf` ändert genau eine der 310
Zustandsgrößen: `partie.runde`, den Zähler. `schritt.hpp:13` sagt es selbst: 174 der 175
Adressen der Sollmaske werden geschrieben und **unverändert vorgetragen**. Der Kern hat
491 kB Quelltext in 13 Kopfdateien und 10 Quelldateien, acht grüne Manifeste und 38
laufende Tests — und hat noch keinen Preis, keine Produktion und keine Gegenkraft
gerechnet. Die alte Ursache (`werte.hpp` bei 78 Byte) ist behoben; die neue ist, dass die
sechs Schritte niemandem zugewiesen sind.
