---
id: 0147-belegstellenriegel-ortsfrage-mit-anker
rolle: testentwickler
status: gebaut
haengt_an: [0106-belegstellenriegel-aufloesung-mit-anker, 0130-belegstellenriegel-berichtsreihenfolge-festnageln]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Selbsttest des Riegels bricht mit Code 2 ab, wenn in `pruefe_zitate` der Schritt von der `Zielart` zum `grund` durch eine Konstante ersetzt wird -- je einzeln nachgewiesen fuer *ausserhalb beider Wurzeln*, *ungelesener Ordner* und *totes Ziel*, sowie fuer den Fall, dass die Reihenfolge der drei Zitatformen (unmittelbar mit Anfuehrung, ohne Anfuehrung, mit Wortabstand) vertauscht wird. Jeder Mutant muss am Selbsttest sterben, bevor der Bestand gelesen wird; jeder muss genau einen neuen Fall reissen und keinen der bestehenden. Der Riegel bleibt auf dem dann geltenden Korpus gruen und meldet zeichengleich dieselbe Zahlenzeile wie die Fassung unmittelbar davor, beide im selben Aufruf gemessen.
---

# ANGENOMMEN — 2026-09-06, Projektmanager

Rolle `testentwickler` gibt es und wird eingeplant; die Abnahme ist prüfbar und nennt je
Mutant vier Messgrößen. Du hast die Kollision selbst gemeldet — sie ist hiermit
aufgelöst: **0115 → 0130 → 0147** auf `belegstellen_riegel.cpp`, der zweite Eintrag in
`haengt_an` ist die Reihenfolgesperre. Die ganze Kette steht hinter 0106, das noch auf
seinen Prüfbefund wartet.

**Nachrangig, und das ist Absicht:** `ops/plan.md` sagt „Nichts aus der
Belegstellen-Familie in dieser Woche". Ich lege das Paket an, damit die Meldung nicht
verfällt, stelle es aber ans Ende seiner Kette.

**Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer.**

---

# Die Ortsfrage und die Reihenfolge der Formen halten keinen Fall

## Warum das ein eigenes Paket ist

**Weil 0106 genau eine von mehreren Kopplungen geschlossen hat, und die Prüffrage dabei
verallgemeinerbar geworden ist.** 0106 hat gemessen, dass `ZITATFAELLE` den Baustein
`namensart` prüft und nicht den Schritt darüber. Dieselbe Bauart liegt an zwei weiteren
Stellen in `pruefe_zitate`, und beide sind ungehalten:

* **Die Ortsfrage.** `ZIELFAELLE` ruft `zielart` unmittelbar auf und misst, welche Art
  ein Ort hat. Was `pruefe_zitate` daraus macht — drei verschiedene `grund`-Texte, und
  im Fall *totes Ziel* stattdessen ein Eintrag in `tote_ziele` **samt** Hochzählen von
  `zaehlwerk.zitate` ohne `zaehlwerk.aufgeloest` — prüft kein Fall. Der letzte ist der
  heikelste: Dort hängt eine Zählregel dran, und eine falsche Zählung hier bricht den
  Satz, dass ungleiche Zahlen einen roten Lauf bedeuten.
* **Die Reihenfolge der drei Zitatformen.** `ueberschrift_hinter`, dann
  `name_ohne_anfuehrung`, dann `ueberschrift_mit_abstand` — die Reihenfolge ist laut
  Quelltext „die ganze Verträglichkeit dieser Lockerung" (Paket 0086). Jede der drei
  Formen hat eigene Fälle; **dass sie in dieser Reihenfolge gefragt werden, hat keinen.**

**Weil es die teuerste Sorte Lücke ist**, dieselbe wie bei 0106: Ein Riegel, dessen
Verdrahtung kein Test hält, sieht in jedem Lauf aus wie einer, der prüft.

**Warum nicht in 0106 mitnehmen.** 0106 nennt in seiner `abnahme` vier Mutanten an einer
benannten Stelle und sagt ausdrücklich, mehr Fälle seien kein Ziel. Die Ortsfrage dort
mitzunehmen hätte den Zuschnitt aufgeweicht, den der Projektmanager geprüft hat — und
sie braucht einen eigenen Schnitt: `zielart` bekommt seinen `grund` teils aus
`es->second`, also aus dem Zielbestand, und der ist heute ein Gegenstand auf der Platte.
**Der Zuschnitt ist die eigentliche Arbeit**, genau wie bei 0106.

## Der Weg, den 0106 gezeigt hat

Die Entscheidung als eigenen Aufruf herausziehen, den Selbsttest den **Ausgang** messen
lassen und nicht das Zwischenergebnis, und `pruefe_zitate` denselben Aufruf benutzen
lassen. Der Messstand steht als `befunde/messung-0106/messung.py` und ist übertragbar:
Er übersetzt beide Fassungen nebeneinander, lässt sie im selben Aufruf über denselben
Arbeitsbaum laufen und prüft je Mutant vier Dinge — Rückgabecode, welcher Fall riss,
dass keine fremde Tabelle riss, und dass der Bestand gar nicht erst gelesen wurde.

## Grenzen

* Nur `belegstellen_riegel.cpp`. Dieselbe Datei wie 0115 und 0130, beide auf `offen` —
  gleichzeitig geht nicht. Die Einordnung in die Kette gehört dem Projektmanager.
* Keine bestehende Erwartung ändern und keine Schwelle senken, damit etwas grün wird.
* Keine Gleitkommazahl, keine Fremdabhängigkeit, kein fest eingebauter Pfad.
* **Kein Fall um der Zahl willen.** Zu jedem neuen Fall gehört ein Mutant, der genau ihn
  rot macht; wo keiner zu bauen ist, gehört der Fall nicht in die Tabelle, sondern die
  Begründung in den Quelltext.
