# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, nach dem dritten Baulauf. Der Plan von heute früh ist überholt: sein
Engpass hat sich erledigt, seine Empfehlung nicht.

## Wo das Vorhaben steht

Der Baulauf trägt jetzt — fünf Rollen, fünf Ergebnisse, fünf ergänzte Logbücher; das
Muster „Arbeit da, Schlussarbeit nicht" von heute früh ist ohne Eingriff verschwunden.
Der Kern hat rund 1.000 Zeilen C++ in vier von neun Kästen, `cmake --build` und `ctest`
sind grün, und beide vorhandenen Proben laufen wirklich (`festkomma_probe`,
`pruefsumme_probe`, 2/2 — vom Runner erzeugt, vom Kern-Prüfer unter ASan/UBSan
unabhängig nachgestellt). Sechs Prüfungen sind ergangen: drei `geprueft` (0005, 0007,
0013), drei `zurueck` (0004, 0006, 0009).

## Der Engpass

**Alle sechs Fragen, die `rueckstand.md` dem Betreiber vorlegt, hängen an denselben zwei
Rollen — und der Baulauf kann sie nicht einplanen.** `architekt` und `spielentwerfer`
stehen in `REVIEW`, aber nicht in `BAUROLLEN` (`baulauf.py:49`). Unverändert seit zwei
Plänen; die Liste der Dinge, die daran hängen, ist von zwei auf sechs gewachsen.

Eine davon ist neu und schwerer als alles andere im Rückstand: **Klasse 2 mischt
laufende und konstante Preise** (Prüfbefund 0007, Befund 1). Die 40 Handelsströme kommen
aus CEPII BACI in *laufenden* USD, die Wertschöpfungen aus WDI Reihe 1 in *konstanten*
Preisen, und T50 zählt die Skalenübergänge abschliessend auf — ein Preisbasiswechsel ist
keiner davon. Folge: `durchgriff = teile_gerundet(10.000 · H, H + N)` addiert im Nenner
Äpfel und Birnen und fällt in allen zehn Werten gleichgerichtet zu klein aus, und Maß 4
misst Inflation statt Modellgüte.

**Das ist kein Textproblem, sondern ein Rechenfehler — und er hat noch etwa einen Lauf
Vorlauf.** Er wird von Paket 0002 (`kern::werte`) in Code gegossen; 0002 liest genau T5
und T50 und implementiert die drei Skalenübergänge. 0002 hängt an 0008, und 0008 ist
heute Nacht startbereit. Solange 0002 nicht gebaut ist, kostet die Korrektur nichts.
Danach ist sie Nacharbeit an dem Modul, das fünf Leser hat.

Ich deute das nicht zum dritten Mal um. Mein Logbuch sagt, eine Frage, die dreimal
steht, spreche gegen meine Umdeutung — hier nicht: Der Projektmanager ist unabhängig auf
dieselbe Ursache gekommen und schliesst sich an. Was fehlt, ist eine Hand an
`baulauf.py`, und die hat kein Agent.

## Was quer liegt

- **`technik.md` sagt elfmal Rust und keinmal C++.** Gebaut wird C++20 (ADR 0011). Der
  Projektmanager hat alle Codepakete nachgezogen — Dateinamen, Nachweise, Behältertypen
  — und in jedes den Satz „für den Bau gilt der ADR, nicht der Vorgabentext" geschrieben.
  Das hält den Bau am Laufen, macht aber die verbindliche Vorgabe dauerhaft falsch und
  jedes künftige Paket um eine Fussnote länger. Das ist Paket 0011, Rolle `architekt`.
  Rest-Rust in den Paketen: eine Zeile Fliesstext in 0002, ein `.rs` im Feld `dateien`
  von 0003.
- **Die Abnahmekriterien werden zum zweiten Engpass.** 0004 ging zurück, und **beide**
  Befunde treffen das Kriterium, nicht den Code: Bedingung 3 und 4 verlangen je einen
  Grep, der „nichts" liefern muss, und die Treffer sind Prosa, die das Verbot
  *beschreibt* — plus die Zeile, in der `kern/CMakeLists.txt` den Grep des Prüfers
  zitiert. Der Kern selbst hält (kein Gleitkomma, `#pragma GCC poison` greift, 39
  `static_assert` vom Übersetzer ausgewertet, vier Rundungswerte nachgerechnet). Kosten:
  ein voller Rücklauf von drei erlaubten (`RUECKLAUF_MAX`) für rund vier Zeilen Text.
  Bedingung 2 trägt die Ausnahme „…oder beschreibt", Bedingung 3 und 4 tragen sie nicht.
  Der Kern-Prüfer empfiehlt, die Prosa umzuformulieren statt das Kriterium
  aufzuweichen — das ist richtig, aber es plant sich nicht selbst ein.
- **Zwei Prüfbefunde sind noch nicht verarbeitet, und 0014 hat gar keinen.** Der
  Projektmanager läuft als Erster im Baulauf, die Prüfer als Letzte; die Urteile von
  heute Nacht (0004, 0006, 0009 `zurueck`, 0013 `geprueft`) wirken deshalb erst im
  nächsten Lauf. Kein Fehler, aber ein systematischer Verzug von einem Lauf je Urteil.
- **0003 liegt seit dem 2026-09-01 unberührt auf `blockiert`.** Es verlangt Wrappertypen
  je Größenklasse, T5 sagt „überall `int64_t`". Entweder ein ADR gegen T5 oder das Paket
  bleibt liegen — auch das eine Architektenfrage.
- **Richtig entschieden und hier nur als Beleg:** Der Projektmanager hat 0008 von 0004
  entkoppelt und begründet (`file(GLOB … CONFIGURE_DEPENDS)`, keine gemeinsame Datei).
  Das spart dem kritischen Pfad genau den Lauf, den 0004s Rücklauf sonst gekostet hätte.
- **Die 170-gegen-121-Lücke** ist weiter unberührt und blockiert weiter nichts. Fällig,
  wenn der Kern rechnet, nicht vorher.

## Was der Betreiber entscheiden muss

Eine Frage, dieselbe wie in den letzten beiden Plänen — und der Rückstand legt sechs
vor, die alle darunter hängen. **Kommen `architekt` und `spielentwerfer` in
`BAUROLLEN`?**

- *A:* Eine Zeile in `agents/baulauf.py:49`. Ab dem nächsten Lauf planen sich
  Entwurfspakete selbst ein, ihre Prüfer sind in `REVIEW` schon zugeordnet.
- *B:* Von Hand starten:
  `python3 agents/lauf.py architekt 0016-hedgefonds-simulation-echte-weltwirtschaft`,
  dazu zweimal `spielentwerfer`. Löst diesmal dasselbe dreimal und lässt die Lücke stehen.
- *C:* Weiter vertagen. Der Preis steht seit heute fest und ist nicht mehr abstrakt: 0002
  gießt die Preisbasis-Mischung in `kern::werte`, sobald 0008 gebaut ist.

**Empfehlung: A, und die Reihenfolge zählt.** Zuerst der Architekt auf die Klasse-2-Frage
(sie ändert T5, T49, T23 Punkt 5 und T8), dann 0011, dann der Spielentwerfer auf Reihe 9
mit R = 19 und auf „Schaden". Der Stackwechsel ist unangenehm, aber er kostet nichts,
solange der ADR gilt — die Preisbasis kostet ab dem übernächsten Lauf Code.

Nicht zu entscheiden, sondern nur zu wissen: 0004 braucht rund vier Zeilen umformulierte
Prosa in `kern.hpp` und `kern/CMakeLists.txt`. Das ist Projektmanager-Arbeit und läuft
von allein, wenn nichts dazwischenkommt.

## Die eine Zahl

**5 von 9 Kernkästen sind leer** — vorgestern 6. Inhalt haben `festkomma`, `kern`,
`sperre` und seit heute Nacht `pruefsumme`; `schreiber`, `schritt`, `werte`, `zufall`
und `zustand` sind Zwei-Zeilen-Platzhalter. Zwei davon (`zustand`/0008, `zufall`/0012)
sind startbereit. Ein Kasten je Baulauf ist das gemessene Tempo; das reicht bis zum
ersten Weltschritt. Der Kasten `werte` ist der, an dem die Preisbasis hängt. Abgelöst
wird diese Zahl vom Rückvergleich: 16 Prüfgegenstände, höchstens 2 dürfen reißen (T37).
