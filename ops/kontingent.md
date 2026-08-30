# Verbrauch und Auslastung des Kontingents

Erzeugt vom Wochenlauf, 2026-08-30T07:35:44. Quelle: `agents/kontingent.py`. Nicht von Hand aendern.

```

Verbrauch je Rolle
────────────────────────────────────────────────────────────────────────
Rolle                   Läufe   Gegenwert   je Lauf      Rohtokens
rechercheur                48     217.91$     4.54$     87.237.359
markt-analyst              18      88.66$     4.93$     75.471.939
ideator                    11      20.29$     1.84$      9.612.432
pain-scout                 11      10.54$     0.96$      6.829.286
modell-scout                8      10.53$     1.32$     10.478.073
fit-filter                 10      10.27$     1.03$      3.905.951
regel-scout                13       9.30$     0.72$      6.329.621
markt-scout                12       8.03$     0.67$      6.231.776
portfolio-manager           2       7.60$     3.80$      7.669.823
anwalt                      3       7.42$     2.47$      3.893.563
tech-scout                 11       7.30$     0.66$      4.481.300
advocatus-wettbewerb        3       6.19$     2.06$      2.706.855
advocatus-recht             3       5.97$     1.99$      2.266.548
advocatus-vertrieb          3       5.93$     1.98$      2.684.207
advocatus-nachfrage         3       5.40$     1.80$      3.074.026
verbesserer                 2       4.41$     2.20$      3.224.292
advocatus-betrieb           3       4.29$     1.43$      1.670.476
prozess-analyst             1       3.19$     3.19$      2.218.205
digest-redakteur            2       1.58$     0.79$        981.730

Auslastung
────────────────────────────────────────────────────────────────────────
  Laufendes 5-Stunden-Fenster
    23 Läufe, 54.41 $ Gegenwert
    (56.688.025 Rohtokens — überwiegend Cache, siehe Kopf der Datei)

  Schwerster Tag: 95 Läufe, 253.40 $ Gegenwert

Was es kostet
────────────────────────────────────────────────────────────────────────
  Abo:           200 € im Monat, fix
  Anteilig:      6.67 € am Tag — unabhängig von der Zahl der Läufe
  Für die EÜR:   2400 € im Jahr als Betriebsausgabe

  Das ist die einzige Zahl, die tatsächlich abfließt. Weil sie fix ist,
  kostet ein zusätzlicher Lauf nichts und ein unterlassener spart nichts.

Zum Vergleich: was dieselbe Arbeit über die API gekostet hätte
────────────────────────────────────────────────────────────────────────
    ████████████████████████████████████████  7602 $ bei diesem Tempo im Monat
    Faktor 38.0 gegenüber dem Abopreis.

  Diese Zahl ist KEINE Ausgabe und KEINE Ersparnis — sie lässt sich weder
  verbuchen noch geltend machen. Sie sagt nur, wie intensiv das Abo genutzt
  wird. Für die Stückkosten eines Produkts ist sie unbrauchbar: Dort zählen
  die echten API-Preise, weil Kundenlast nicht über das Abo laufen darf.

Befund
────────────────────────────────────────────────────────────────────────
  1 Läufe sind gescheitert. Sind Abbrüche wegen Kontingent
  darunter, ist das Limit erreicht — die Notizen dieser Läufe sagen es:
  sqlite3 state.db "SELECT rolle, notiz FROM lauf WHERE ergebnis='fehler';"
```
