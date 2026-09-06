# Verbrauch und Auslastung des Kontingents

Erzeugt vom Wochenlauf, 2026-09-06T05:00:01. Quelle: `agents/kontingent.py`. Nicht von Hand aendern.

```

Verbrauch je Rolle
────────────────────────────────────────────────────────────────────────
Rolle                   Läufe   Gegenwert   je Lauf      Rohtokens
kern-pruefer               64     541.02$     8.45$    662.482.454
testentwickler            284     514.46$     1.81$    673.558.072
kernbauer                 415     500.30$     1.21$    598.608.230
test-pruefer              158     403.72$     2.56$    362.101.317
projektmanager            163     341.64$     2.10$    411.691.796
daten-pruefer              51     283.17$     5.55$    307.616.937
datenbauer                166     280.16$     1.69$    324.162.260
rechercheur                48     217.91$     4.54$     87.237.359
architekt                 137     132.68$     0.97$    139.681.686
entwurf-pruefer            18     125.09$     6.95$     88.852.672
markt-analyst              24     120.98$     5.04$    103.911.330
spielentwerfer              9      67.57$     7.51$     77.484.190
bruchtester                 4      47.00$    11.75$     62.542.774
geschaeftsfuehrer          17      40.97$     2.41$     35.984.180
prozess-analyst             8      37.91$     4.74$     33.053.333
ideator                    12      22.44$     1.87$     11.120.922
fit-filter                 12      12.40$     1.03$      5.357.430
pain-scout                 12      11.63$     0.97$      8.316.481
modell-scout                9      11.48$     1.28$     11.929.721
regel-scout                14      10.48$     0.75$      8.323.808
markt-scout                13       8.89$     0.68$      7.761.398
tech-scout                 12       7.78$     0.65$      5.162.982
portfolio-manager           2       7.60$     3.80$      7.669.823
anwalt                      3       7.42$     2.47$      3.893.563
advocatus-wettbewerb        3       6.19$     2.06$      2.706.855
advocatus-recht             3       5.97$     1.99$      2.266.548
advocatus-vertrieb          3       5.93$     1.98$      2.684.207
advocatus-nachfrage         3       5.40$     1.80$      3.074.026
verbesserer                 2       4.41$     2.20$      3.224.292
advocatus-betrieb           3       4.29$     1.43$      1.670.476
digest-redakteur            2       1.58$     0.79$        981.730

Auslastung
────────────────────────────────────────────────────────────────────────
  Laufendes 5-Stunden-Fenster
    44 Läufe, 335.47 $ Gegenwert
    (388.961.001 Rohtokens — überwiegend Cache, siehe Kopf der Datei)

  Schwerster Tag: 1192 Läufe, 1358.29 $ Gegenwert

  Abo-Woche ab 2026-08-31 08:00:00 UTC (Montag 10:00 Ortszeit)
    ███████████·····························  3277.8 von 12000 $
    Spielraum: 8722.2 $ — das ist die Zahl, die wirklich bindet.

Was es kostet
────────────────────────────────────────────────────────────────────────
  Abo:           200 € im Monat, fix
  Anteilig:      6.67 € am Tag — unabhängig von der Zahl der Läufe
  Für die EÜR:   2400 € im Jahr als Betriebsausgabe

  Das ist die einzige Zahl, die tatsächlich abfließt. Weil sie fix ist,
  kostet ein zusätzlicher Lauf nichts und ein unterlassener spart nichts.

Zum Vergleich: was dieselbe Arbeit über die API gekostet hätte
────────────────────────────────────────────────────────────────────────
    ████████████████████████████████████████  40749 $ bei diesem Tempo im Monat
    Faktor 203.7 gegenüber dem Abopreis.

  Diese Zahl ist KEINE Ausgabe und KEINE Ersparnis — sie lässt sich weder
  verbuchen noch geltend machen. Sie sagt nur, wie intensiv das Abo genutzt
  wird. Für die Stückkosten eines Produkts ist sie unbrauchbar: Dort zählen
  die echten API-Preise, weil Kundenlast nicht über das Abo laufen darf.

Befund
────────────────────────────────────────────────────────────────────────
  1069 Läufe sind gescheitert. Sind Abbrüche wegen Kontingent
  darunter, ist das Limit erreicht — die Notizen dieser Läufe sagen es:
  sqlite3 state.db "SELECT rolle, notiz FROM lauf WHERE ergebnis='fehler';"
```
