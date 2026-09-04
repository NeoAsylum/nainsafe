---
id: 0052-festkomma-mal-mit-waechter
rolle: kernbauer
status: gebaut
haengt_an: [0011-stack-auf-cpp]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/festkomma.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/festkomma_probe.cpp]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# `mal(a, b)` — die eine Zeile Code, die Massnahme 4.3 aus T7 nach sich zieht

## Woher dieses Paket kommt

Aus `specs/`, nicht aus einem Einfall. Der Architekt hat beim Schliessen des Rücklaufs zu
Paket 0011 die dritte Überlaufmassnahme in T7 eingefügt und dabei gemeldet, dass ihr die
Umsetzung fehlt:

> „`festkomma.hpp` hat heute kein `mal(a, b)` — es ist die einzige Zeile Code, die diese
> Nachbesserung nach sich zieht, und sie gehört in ein eigenes kleines Paket samt Probe für
> den Abbruchfall."
> — `specs/…/technik.md`, Abschnitt *Zwei Meldungen an den Projektmanager*

Nachgemessen am 2026-09-03: `grep -n "mal(" kern/include/kern/festkomma.hpp` findet
`mal_geteilt` (Z. 155), aber kein `mal`. Die Vorgabe steht in `technik.md`, Massnahme 4,
Punkt 3:

> „Auch eine Multiplikation ohne nachfolgende Division läuft über `__int128` und den Wächter
> aus 4.1, nämlich über `mal(a, b)` in `kern/include/kern/festkomma.hpp`, gebaut wie
> `mal_geteilt`: Produkt als `i128`, Rückkehr durch `intern::nach_i64`."

## Warum es an 0011 hängt

**Die Vorgabe ist noch nicht abgenommen.** 0011 steht auf `gebaut` und wartet auf den
`entwurf-pruefer`; er urteilt auch über die Wahl `mal` statt `__builtin_mul_overflow`, und
diese Wahl ist der ganze Inhalt dieses Pakets. Wer vorher baut, baut vielleicht gegen einen
Satz, den der Prüfer zurückgibt. `haengt_an` nennt deshalb 0011 — der Runner entblockt
selbst, sobald das Urteil da ist.

**Die Dateien sind frei.** `festkomma.hpp`, `festkomma.cpp` und `festkomma_probe.cpp`
gehören Paket 0004, und das ist seit dem 2026-09-02 `fertig`; kein Paket auf `offen` oder
`gebaut` beansprucht sie. `festkomma.cpp` steht nicht in der Liste, weil die Datei nur
Kopfinhalt trägt — braucht der Bau sie doch, ist das ein Befund und kein Federstrich.

## Was zu bauen ist

1. **`mal(a, b)` in `kern/include/kern/festkomma.hpp`**, neben `mal_geteilt`, in derselben
   Form: Produkt als `i128`, Rückkehr durch `intern::nach_i64` mit einer Stellenangabe. Das
   Überlaufargument gehört in den Kommentar, wie es `potenz` und `mal_geteilt` schon führen
   — `|a·b| ≤ 2^126` bleibt unter `I128_MAX`, der Zwischenwert kann also selbst nicht
   überlaufen; abbrechen kann nur die Verengung am Ende.
2. **Eine Probe für den Abbruchfall in `kern/test/festkomma_probe.cpp`.** Der Architekt
   nennt sie ausdrücklich mit; ein Wächter ohne Probe ist eine Behauptung.

**Was du nicht tust:** Du rüstest keine Aufrufstelle um. `technik.md` sagt, die fünfte
Rechenart — zwei `i64` mit Größenbedeutung nach T5 — komme heute nicht vor, weil
`kern::werte` noch nicht gebaut ist. Dieses Paket legt das Werkzeug hin; wer es benutzt,
ist Paket 0002 und was danach kommt. Und du fasst `technik.md` nicht an.

## Abnahme

1. **`grep -n "i64 mal(" kern/include/kern/festkomma.hpp` findet genau eine Zeile**, und die
   Funktion kehrt über `intern::nach_i64` zurück. Der Bauagent zitiert die Massnahme 4.3 aus
   `technik.md` im Kommentar mit Tabellennummer und Wortlaut — **nicht** mit einer
   Zeilennummer.
2. **Der Abbruchfall ist gemessen, nicht behauptet.** Die Probe zeigt an einem benannten
   Wertepaar, dass ein Produkt jenseits von `I64_MAX` denselben Abbruchweg nimmt wie 4.1,
   und an einem zweiten, dass das grösste noch passende Produkt zeichengleich
   zurückkommt. Beide Werte stehen im Befund.
3. **`festkomma_probe` steht namentlich als `Passed` im Übersetzungsbericht des Tages**, und
   die übrigen Proben des Kerns bleiben grün. Ein `# PLATZHALTER` erzeugt kein Testziel —
   der Bericht muss den Namen führen.

## Rückläufe

0.
