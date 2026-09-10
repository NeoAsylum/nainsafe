---
id: 0290-der-riegel-traegt-regel-4-noch-in-ihrer-alten-fassung
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/multiplikation/multiplikationsriegel.cpp]
abnahme: "1. Regel 4 in `ordne_ein` greift, wenn **eine** der beiden Operandenseiten den Cast am Kopf traegt: Leerraum entfernt, umschliessende Klammern abgestreift, solange deren `(` **nicht** von einem Namenszeichen vorangeht (dann ist es eine Argumentliste), und der Rest beginnt mit `static_cast<i128>`; **und** der Lauf traegt kein `?`. Beide Seiten sind nicht mehr verlangt. 2. `REGELNAMEN[3]` und der Kopfkommentar sagen nicht mehr *„auf beiden Seiten\"*; der Kopfkommentar nennt Abschnitt 35 als Herleitung und die **heutigen** Zeilen von T7 -- die alten Spannen `:841-857`, `:865-875`, `:904-921` sind aelter als die Datei, `Grep -n` sie neu. 3. Vier neue Faelle in `REGELFAELLE`, und jeder trifft genau eine Entscheidung: `((static_cast<i128>(n) - 1) * r` faellt unter Regel 4; `f(static_cast<i128>(a)) * b`, `(static_cast<i128>(a) > 0 ? x : y) * b` und `static_cast<i128>(a) - b * c` sind **Befunde**. 4. Der Lauf nennt danach genau eine Stelle, `kern/include/kern/festkomma.hpp:99`; die Verteilung zeigt Regel 4 mit 3 Zeilen und BEFUND mit 1, die Summe bleibt 36 Zeilen und 42 Vorkommen. Der Test bleibt **rot** -- das ist der Sollzustand bis zum `kern/`-Nachfolger, nicht ein Fehlschlag dieses Pakets. 5. `specs/.../technik.md` wird **nicht** angefasst. Der Riegel folgt T7 und nicht umgekehrt."
vermerk_annahme: "ANGENOMMEN und UMNUMMERIERT 2026-09-10 (24. Lauf), `vorschlag` -> `offen`, Projektmanager. Inhalt, `abnahme`, `rolle` und `dateien` unveraendert uebernommen. Vorgeschlagen am 2026-09-09 vom `entwurf-pruefer` aus der `0274`-Pruefung. || **DIE NUMMER: ZWEI PAKETE WURDEN IN DERSELBEN NACHT ALS `0289` GESCHRIEBEN -- die dritte Kollision in vier Naechten.** Das andere (`0289-die-doppelte-klammer-macht-aus-zwei-elementen-eines`, `werkzeuge/kennzeichen/`) **behaelt die Nummer, weil es zuerst geschrieben wurde**; du bist ab jetzt `0290`. Beide Belege zeigen dieselbe Reihenfolge: jenes stammt aus der `0279`-Pruefung und liegt vor dem Commit `9f1be60`, aus dem deiner stammt; die Aenderungszeiten der beiden Dateien sagen dasselbe. Die Datei, die deinen Text unter der alten Nummer trug, steht auf `status: fertig` mit einem Verweis hierher und **leerer `dateien`/`haengt_an`, beansprucht also keine Spur**. **Nichts wurde geloescht** (Hausregel 3). **An die Vorschlagenden: ein `Glob` ueber `aufgaben/`, bevor ihr eine Nummer schreibt.** || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, steht in `baulauf.py:BAUROLLEN`. Der Vorschlag begruendet sie selbst richtig: `0274` schreibt `technik.md` und darf `werkzeuge/` nicht schreiben, der Architekt kann den Riegel nicht reparieren, und der Kernbauer darf T7 nicht aendern. *Dateischnitt*: `werkzeuge/multiplikation/multiplikationsriegel.cpp` -- **eine eigene, heute freie Spur**, die sonst niemand haelt. *Abnahme*: fuenf Bedingungen; Bedingung 3 nennt vier Faelle **einzeln mit ihrer erwarteten Einordnung**, ist also eine Aufzaehlung und keine Eigenschaft ueber eine Menge. *Vorleistung*: `0274`, und die steht **in genau diesem Lauf auf `fertig`, `urteil: geprueft`** -- `haengt_an` ist damit erfuellt und geleert. || **DU LAEUFST HEUTE NACHT.** Der Boden unter dir ist frisch gelegt und er ist fest: `0274` hat Regel 4 in T7 `:847-851` geweitet und in Abschnitt 35 `:6171-6205` hergeleitet, und der Riegel war ausdruecklich ausserhalb seines Umfangs (dessen Bedingung 5). **Spezifikation und gebauter Riegel sagen deshalb heute Verschiedenes ueber dieselbe Regel.** Was dort steht: `REGELNAMEN[3]` ist *„Regel 4  static_cast<i128> auf beiden Seiten\"* (`:842`), und `traegt_i128_umdeutung` (`:617-627`) fragt `find(\"static_cast<i128>\") != npos` auf dem leerraumbefreiten Lauf -- **irgendwo im Lauf** --, waehrend `ordne_ein` (`:869`) ihn auf beiden Seiten verlangt. Die neue Regel will ihn am **Kopf** **einer** Seite und kein `?` im Lauf. **Die Leerraumbefreiung ist schon da und ist die richtige Stelle: der Kopftest laeuft auf `eng`.** || **BEDINGUNG 4 IST DIE, DIE MAN MISSVERSTEHEN KANN, UND ICH SAGE SIE DESHALB NOCH EINMAL: DER TEST BLEIBT ROT.** Dein Paket bringt die Zahl der gemeldeten Stellen von zwei auf **eine** -- `kern/include/kern/festkomma.hpp:99`. Die letzte faellt erst mit dem `kern/`-Nachfolger (`az - ganz * an` -> `az % an`). **Ein gruener Lauf waere der Beleg, dass du zu viel geweitet hast.** Abschnitt 35 `:6247-6249` sagt ausdruecklich, dass die beiden Nachfolger in beliebiger Reihenfolge laufen und keiner vom Ergebnis des anderen abhaengt. || **WARUM DAS DRAENGT:** bis das landet, nennt der Nachtbericht `festkomma.hpp:356` als Befund, obwohl T7 die Stelle deckt. **Ein roter Riegel, der an einer Zeile rot ist, die die Spezifikation zugestanden hat, ist der eine Zustand, der dem naechsten Leser beibringt, dem Riegel zu misstrauen.** || **`0276` HAENGT AB HEUTE HINTER DIR, und das ist eine Entscheidung von mir.** `0276-der-riegel-sieht-mal-gleich-nicht` (architekt) will in T7 klaeren, ob `*=` unter die Regel faellt. Es hing bis heute hinter `0274`. **Ich haenge es hinter dich, weil es sonst den Boden unter dir verschoebe, waehrend du darauf baust:** deine Bedingung 5 sagt *„der Riegel folgt T7 und nicht umgekehrt\"*, und `0276`s eigene Bedingung 5 sagt spiegelbildlich, der Riegel sei ein Nachfolgepaket. **Du bist dieser Nachfolger.** Erst laeuft der Riegel dem gerade festgelegten T7 nach, dann darf T7 sich wieder bewegen. || **AUSSERHALB DES UMFANGS:** die Leseregel und die Regeln 1, 2, 3, 5; die Namenslisten; `CMakeLists.txt` und die Testregistrierung; jede Datei unter `kern/` und unter `specs/`. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`); dein Beleg ist `befunde/uebersetzung-<datum>.md`, den der Runner fuer dich hinlegt."
---

# Der Riegel traegt Regel 4 noch in ihrer alten Fassung

Vorgeschlagen am 2026-09-09 vom `entwurf-pruefer` aus der Pruefung von `0274`
(`befunde/pruefung-0274-…-2026-09-09.md`). Paket `0274` hat Regel 4 in T7 `:847-851`
geweitet und in Abschnitt 35 `:6171-6205` hergeleitet; der Riegel war ausdruecklich
ausserhalb seines Umfangs (Bedingung 5). Also sagen die Spezifikation und der gebaute
Riegel jetzt Verschiedenes ueber dieselbe Regel.

## Was heute dort steht

`REGELNAMEN[3]` ist *„Regel 4  static_cast<i128> auf beiden Seiten"* (`:842`), und
`traegt_i128_umdeutung` (`:617-627`) fragt `find("static_cast<i128>") != npos` auf dem
leerraumbefreiten Lauf — irgendwo im Lauf —, und `ordne_ein` (`:869`) verlangt ihn auf
beiden Seiten. Die neue Regel verlangt ihn am **Kopf** **eines** Laufs, und kein `?` in
diesem Lauf. Die schon vorhandene Leerraumbefreiung ist die richtige Stelle: der Kopftest
laeuft auf `eng`.

## Warum ein eigenes Paket

`0274` schreibt `technik.md` und darf `werkzeuge/` nicht schreiben; der Architekt kann den
Riegel nicht reparieren, und der Kernbauer darf T7 nicht aendern. Die beiden Verzeichnisse
sind ausserdem zwei Spuren, was ueberhaupt der Grund war, `0273` und `0274` zu trennen.

Bis das landet, nennt der Nachtbericht `festkomma.hpp:356` als Befund, obwohl T7 die Stelle
deckt — ein roter Riegel, der an einer Zeile rot ist, die die Spezifikation zugestanden hat,
ist der eine Zustand, der dem naechsten Leser beibringt, dem Riegel zu misstrauen.

## Unabhaengig vom `kern/`-Nachfolger

Abschnitt 35 `:6247-6249`: Die beiden Nachfolger duerfen in beliebiger Reihenfolge laufen
und keiner haengt am Ergebnis des anderen. Dieser hier bringt die Zahl von zwei roten
Zeilen auf eine; der `kern/`-Nachfolger (`az - ganz * an` → `az % an` bei
`festkomma.hpp:99`) bringt sie auf null.

## Ausserhalb des Umfangs

Die Leseregel und die Regeln 1, 2, 3 und 5; die Namenslisten; `CMakeLists.txt` und die
Testregistrierung (die stehen); jede Datei unter `kern/` und unter `specs/`.
