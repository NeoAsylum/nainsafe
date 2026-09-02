# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, nach dem vierten Baulauf (05:00–05:15).

## Wo das Vorhaben steht

Der Kern steht, wo er heute früh stand: **vier von neun Kästen gefüllt, kein neuer
dazugekommen.** Der Lauf zog vier Pakete und arbeitete drei Rückläufe ab — 0004 und 0006
sind durch (`geprueft`, Runde 2), 0009 ging zum zweiten Mal zurück, und 0008, das einzige
gezogene Paket, das einen neuen Kernkasten gebracht hätte, lieferte **nichts**: keine
Datei, kein Logbucheintrag. Die Idee steht auf `erkundung` und wird trotzdem gebaut; das
ist seit dem 2026-08-31 so entschieden (`konzeptlauf.py:44-47`) und kein Versäumnis.

## Der Engpass

**Der Entwurf hat keinen laufenden Weg mehr in die Fabrik.** Beide Skripte, die
`architekt` und `spielentwerfer` kennen, sind zu — jedes auf andere Weise:

- `baulauf.py:49` führt sie nicht in `BAUROLLEN` (nur in `REVIEW`). Unverändert.
- `konzeptlauf.py` **hält vor dem ersten Token an**: Seine Konvergenzbremse zählt *alle*
  Urteile des Entwurfsprüfers, und es sind **5 `zurueck` bei `RUECKLAUF_MAX = 3`**
  (Zeile 126-141, `return 0`). Auch `--ab 2` läuft dagegen; die Bremse steht davor.

Das ist neu gemessen, nicht fortgeschrieben: Der letzte Plan führte den Konzeptlauf noch
als Ausweg. Er ist keiner. Der einzige heute funktionierende Weg ist
`python3 agents/lauf.py architekt <id>` von Hand — ohne Statusprüfung, ohne Bremse
(`lauf.py:513-516`).

Daran hängen sieben Sachen: 0002 (blockiert, Klasse 2), 0003 (blockiert, T5), 0010
(mittelbar), 0011 (Stacktext), die neue Klasse-4-Frage, Reihe 9 mit R = 19 und „Schaden"
aus Gegenkraft 5.

**Was ich zurücknehme:** Mein letzter Plan deutete „dieselbe Empfehlung, dreimal nicht
ausgeführt" als Darstellungsproblem. Das war falsch. Der Betreiber hat zuletzt am
**2026-09-01 um 21:02** ins Repo gegriffen; die drei Pläne davor und danach entstanden in
100 Minuten derselben Nacht. Drei Pläne sind hier keine drei Ablehnungen, sondern eine
Nachtschicht. Die Fabrik läuft schneller als ihr einziger Entscheidungspunkt — das ist
kein Fehler, aber es heißt, dass ich Wiederholung nicht als Widerstand lesen darf.

## Was quer liegt

- **0008 lieferte nichts, und die wahrscheinliche Ursache steht im Nebenlauf.** Der
  parallel laufende Kernbauer notierte um 05:02: ein `cd` in einer Bash-Zeile nimmt der
  Rolle still die Schreibrechte, jedes `Edit` wird ohne Rückfrage verweigert. Der
  0008-Lauf startete gleichzeitig und konnte diese Zeile nicht mehr lesen. Das ist eine
  Folgerung, kein Beweis — aber die Signatur passt, und die Lehre steht jetzt im Logbuch,
  das der nächste Kernbauer liest. **Ich schlage keinen Eingriff vor: geht 0008 ein
  zweites Mal leer aus, ist es nicht selbstheilend und gehört ganz nach oben.**
- **Der Lauf verbrauchte sich in Nacharbeit.** Vier Plätze, drei davon Rücklauf, und der
  vierte war der, der ausfiel. 0009 steht bei **Rücklauf 2 von 3** — das erste Paket nahe
  der Bremse. Seine drei neuen Befunde treffen wieder Herkunftsangaben und eine
  Selbstprobe, keinen Wert; dieselbe Bauart wie bei 0004. Das ist der zweite Beleg dafür,
  dass die Abnahmekriterien zum zweiten Engpass werden.
- **Die Preisbasis-Frist ist noch nicht abgelaufen.** Klasse 2 mischt weiter laufende und
  konstante Preise (Prüfbefunde 0007 und 0006, zwei Prüfer, dieselbe Ursache). Aber 0002
  ist `blockiert` und 0008 nicht gebaut — **nichts davon ist in Code gegossen.** Vorbeugung
  kostet weiterhin nur eine Entscheidung, Nacharbeit wäre teurer. Der Projektmanager hat
  0002 selbst blockiert, statt gegen eine Vorgabe zu bauen, die zwei Prüfer bestreiten;
  das war richtig und hält die Tür offen.
- **`technik.md` sagt elfmal Rust, gebaut wird C++20** (ADR 0011). Unverändert. Jedes
  Paket trägt inzwischen die Fußnote „für den Bau gilt der ADR"; die verbindliche Vorgabe
  bleibt falsch. Paket 0011, Rolle `architekt`.
- **Drei Pakete stehen auf `gebaut` mit Urteil `geprueft`** (0004, 0006, 0014). Sie werden
  im nächsten Lauf `fertig` — der Projektmanager läuft vor den Prüfern. Systematischer
  Verzug von einem Lauf je Urteil, kein Fehler.
- **Die 170-gegen-121-Lücke** ist weiter unberührt und blockiert weiter nichts.

## Was der Betreiber entscheiden muss

Eine Frage: **Wie kommt der Entwurf wieder in einen Lauf?**

- *A:* `architekt` und `spielentwerfer` in `BAUROLLEN` aufnehmen (`baulauf.py:49`). Ihr
  Prüfer steht in `REVIEW` schon bereit; ab dem nächsten Lauf planen sich Entwurfspakete
  selbst ein.
- *B:* Von Hand: `python3 agents/lauf.py architekt 0016-hedgefonds-simulation-echte-weltwirtschaft`.
  Funktioniert nachweislich — aber für jede der sieben Sachen einzeln, wieder und wieder.
- *C:* Die Bremse in `konzeptlauf.py` zurücksetzen. **Davon rate ich ab:** Sie hatte recht,
  und ihre eigene Meldung nennt die Alternative, die die Fabrik längst gewählt hat —
  „Befunde als Arbeitspakete an den Bau geben". Genau das sind 0001 bis 0017.

**Empfehlung: A.** Reihenfolge danach: Architekt zuerst auf Klasse 2 (ändert T5, T49,
T23 Punkt 5, T8, womöglich T50 und entblockt 0002 — das Modul mit fünf Lesern), dann
0011, dann die Klasse-4-Frage (trägt `hebel_max` den Deckel 10.000? Mit Deckel wird
Todesart 1 praktisch unerreichbar). Der Spielentwerfer danach auf Reihe 9 mit R = 19 und
auf „Schaden".

Nicht zu entscheiden, nur zu wissen: 0009 braucht drei Zeilen (eine Herkunft, ein
fehlender vierter Fall, ein falscher Prüfweg im Dateikopf) und läuft von allein.

## Die eine Zahl

**5 von 9 Kernkästen sind leer — unverändert.** Das gemessene Tempo war bisher ein Kasten
je Baulauf; dieser Lauf brachte null. Leer sind `schreiber`, `schritt`, `werte`, `zufall`
und `zustand`; startbereit davon sind `zustand` (0008) und `zufall` (0012). Abgelöst wird
diese Zahl vom Rückvergleich: 16 Prüfgegenstände, höchstens 2 dürfen reißen (T37).
