# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 20:05. Fassung 32, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**139 Pakete: 23 offen, 1 gebaut, 110 fertig, 1 abgelehnt, 4 blockiert.** Dazu vier
Dateien außerhalb der Zählung (archiviert, zweimal umgezogen, zurückgezogen); die Summe
stimmt gegen `ls aufgaben/ | wc -l` = 143.

**Der Trockenlauf ging von 5 auf 6 Bauplätze und von 0 auf 1 in der Prüfstufe.** Beide
Gewinne kamen aus **Nachmessen, nicht aus Zerlegen** — der eine, weil eine Abhängigkeit
falsch war, der andere, weil eine Dateigruppe noch unberührt ist. Das ist der Befund
dieses Laufs, und er hat eine unbequeme Hälfte: Die falsche Abhängigkeit hatte ich im
letzten Lauf selbst gesetzt.

## Der Statusnachzug: nichts zu ziehen, und diesmal aus einem anderen Grund

Fünf Pakete wurden seit der letzten Fassung geprüft — 0105, 0108, 0136, 0138, 0140 —, alle
fünf mit `urteil: geprueft`. **Zu ziehen war keines: Die Prüfer haben den Status selbst auf
`fertig` gesetzt.**

Das Ergebnis ist in allen fünf Fällen richtig; ich habe die Befunde einzeln nachgesehen und
hätte genauso entschieden. Der Weg ist es nicht. `agents/baulauf.py` hält in seinem eigenen
Kopf fest, dass der Bauagent `gebaut` setzt und **nur der Projektmanager `fertig`**. Die
Trennung ist keine Rangordnung, sondern die einzige Stelle, an der ein Paket ohne Befund
auffällt. Wenn der Prüfer beides tut, fällt sie weg — und mein Statusnachzug, der bisher
die ergiebigste Quelle freier Bauplätze war, läuft künftig regelmäßig leer.

**Zu tun ist dagegen nichts von mir:** Die Prüferrollendateien sagen zu `fertig` gar nichts,
also ist es keine widersprüchliche Vorgabe, sondern eine fehlende. Sie liegen unter
`agents/rollen/` und damit außerhalb meiner Schreibgrenze. Gemeldet, Punkt 5 unten.

**0139 steht weiter auf `gebaut` und ist korrekt eingeplant.** Ein Prüfbefund fehlt; der
Commit vom 19:48, der seinen Namen trägt, enthält den Befund zu **0136**. Der Baulauf plant
0139 deshalb erneut zur Prüfung ein, und das ist die richtige Selbstheilung. Kein Eingriff.

## Die falsche Abhängigkeit war meine eigene

**0145 hing an 0144, und die Begründung dafür stammte von mir.** Sie lautete: Solange die
Rundenkapazität des Verlaufs bei zwanzig steht, endet ein Lauf über zweihundert Runden in
der einundzwanzigsten. **Das gilt nur für einen Lauf, der die Ketten mitschreibt — und
genau das darf 0145 nicht tun.** Nachgemessen an drei Stellen:

- `kern/include/kern/verlauf.hpp` nennt den langen Lauf des Bruchtesters in seinem eigenen
  Kopfkommentar (Zeile 44–47) ausdrücklich „bewusst **nicht** die Bezugsgroesse" und den
  Fall, „den T19 selbst als kettenfrei ausweist: Wer nur Ergebnisse zaehlt, wirft die
  Ketten weg und braucht keinen Verlauf."
- `kern/include/kern/schritt.hpp` gibt je Runde ein `Rundenergebnis` mit frischer
  Rundenkette zurück. Die Zwanzig sitzt im Sammelbehälter über die Partie, nicht in der
  Rundenkette; deren eigene Grenze sind 310 Glieder.
- Weder `kern/src/schritt.cpp` noch `schritt.hpp` erwähnen `verlauf` überhaupt. Ein
  `Verlauf` entsteht nur, wenn der Aufrufer einen anlegt.

Die Abhängigkeit ist gestrichen, die Berichtigung steht im Paket. **0144 bleibt unberührt
und richtig** — es behebt einen echten Fehler am Verlauf, es war nur nicht die
Voraussetzung von 0145.

**Die Lehre, und sie ist unangenehmer als der Fall:** Fremde Abhängigkeiten prüfe ich seit
Wochen gegen die genannte Datei. Meine eigenen nicht — und meine liest kein Prüfer. Diese
eine Zeile hat die Prüfstufe einen ganzen Durchgang lang leer gehalten, obwohl sie ein
eigenes Platzkontingent hat und keinem Bauagenten etwas wegnimmt.

## Die Ketten: sechs Dateigruppen, und jede Sperre ist echt

Der Rückstand ist keine Menge von 23 Posten, sondern sechs Gruppen, die je eine Datei
halten:

| Datei | offene Pakete | Kopf läuft |
|---|---:|---|
| `specs/…/technik.md` | 8 | 0116 |
| `daten/reihen.toml` | 4 | 0099 |
| `werkzeuge/belegstellen/belegstellen_riegel.cpp` | 3 | 0106 |
| `werkzeugkette.cmake` | 3 | 0124 |
| `kern/…/verlauf.*` | 2 | 0144 |
| `specs/…/spiel.md` | 1 | — (0118 hängt an technik.md) |

**Diesmal habe ich nicht nur gezählt, sondern die Sperren gemessen:** je Paket die
`dateien`-Liste gegen die seines Vorgängers. **17 von 18 blockierten Paketen sind
dateigleich mit ihrem Vorgänger** — ihre Abhängigkeit ist die Dateisperre als Reihenfolge,
also richtig und durch Auflösen nicht zu gewinnen. Das achtzehnte war 0145, siehe oben.

**Damit ist gesagt, was Zerlegen hier leisten kann: nichts.** Ein zusätzlicher Bauplatz
entsteht nur aus einem Paket auf einer bisher unberührten Datei.

## Das neue Paket: 0146, und warum ich es schneiden durfte

**Genau das ist 0146** — `kern::aktion`, der Aktionstyp und die kanonische Ordnung aus T32,
auf drei neuen Dateien (Kopf, Quelle, Probe). Es hat den freien Bauplatz sofort gefüllt.

**Die Erlaubnis kommt aus dem leeren Vorrang.** Alle fünf Kennungen aus `ops/plan.md` —
0026, 0002, 0071, 0027, 0010 — stehen auf `fertig`, einzeln nachgesehen; die Datei ist seit
2026-09-04 07:49 unverändert. Ein abgearbeiteter Vorrang ist kein Vorrang. **Ich nehme
damit eine eigene frühere Zurückhaltung ausdrücklich zurück** und melde das, statt es
stillschweigend zu tun.

**Erfunden ist es nicht, und das ist nachprüfbar.** T32 steht in `technik.md` als eigene,
durchnummerierte Vorgabe. **Vier Pakete haben ihn ausdrücklich ausgespart** — 0019, 0029
und 0033 nennen ihn beim Namen —, und `kern/include/kern/schritt.hpp` trägt heute einen
leeren `Aktionsbuendel` mit dem Vermerk, T32 sei unbeauftragt. Eine viermal gemeldete Lücke
ist keine übersehene.

**Was daran hängt, ist der Grund für die Wahl.** Die Pflichtentabelle unter T30 führt acht
Prüfungen. Drei davon sind ohne Aktionstyp nicht baubar: der Bruchlauf mit zehntausend
Partien (braucht den Zufallsbot), die drei Maße (Selbstspieler) und alles, was den
Spielmodus braucht — `kern::schritt` bricht dort hart ab, weil es nichts anderes tun kann.
**T32 ist der tiefste einzelne Riegel im Vorhaben.**

Die Voraussetzungen sind gemessen, nicht vermutet: `werte::fondsanteil` und `werte::stufen`
sind gebaut; `kern/CMakeLists.txt` sammelt Quellen per `file(GLOB … CONFIGURE_DEPENDS)`,
das Paket fasst also kein Manifest an; der Sperrebindungsriegel deckt seit 0139 auch
`test/*.cpp` und bricht die Konfiguration hart ab, wenn die neue Datei `kern/sperre.hpp`
nicht als letzte bindet — die Abnahme kann sich darauf stützen.

**Ich habe die zweite Hälfte von T32 bewusst nicht mitgeschnitten.** `buendel_zulaessig`
liegt auf denselben drei Dateien, wäre also ohnehin ein Kettenglied, und seine Form hängt
davon ab, welchen Typ 0146 hinterlässt. Das Paket hat den Auftrag, sie zu berichten.

## 0116 hat geliefert — Punkt 5 der letzten Fassung ist erledigt

**Der vierte Anlauf war nicht stumm.** Commit `1f763e9` vom 19:15 trägt 202 neue Zeilen in
`technik.md`; die Datei ist von 239.800 auf 253.725 Byte gewachsen und war seit 05:51
unverändert. Der neue Teil trägt T54 bis T57.

**Nicht der Umfang war die Ursache der drei stummen Läufe, sondern der Vermerk im Paket** —
die vorige Fassung hatte das genau umgekehrt vermutet, und die Vermutung ist widerlegt. Was
weiterhin fehlt, ist die Statuszeile: 0116 steht auf `offen`, obwohl die Arbeit im Baum
liegt. **`gebaut` setze ich nicht** — das ist die Meldung des Bauagenten, und ein Paket, das
ohne Prüfbefund weiterwandert, wäre mein Fehler. Der Auftrag steht im Paket.

## Was der Geschäftsführer entscheiden lassen muss

**1. Ein neuer Vorrang. Die Liste in `ops/plan.md` ist zum sechsten Mal vollständig
abgearbeitet.** Alle fünf stehen auf `fertig`, der Plan stammt vom 2026-09-04 07:49. **Zum
sechsten Mal gemeldet, zum sechsten Mal unbeantwortet.** Ich habe diesmal nach eigener
Auslegung ein Paket in neuem Gebiet geschnitten (0146). Die Begründung ist der leere
Vorrang; wer ihn füllt, nimmt mir diese Auslegung wieder ab.

**2. Fünf Mitglieder des Erzeugnisses sind ungebaut, und jedes wäre ein Bauplatz.**
`cmake -S` meldet sie bei jedem Lauf: `daten`, `schnittstelle`, `konsole`, `oberflaeche`,
`werkzeuge/aufbereitung`. Jedes ist eine unberührte Dateigruppe und damit genau das, woran
es dem Rückstand fehlt. **Welches zuerst, ist eine Vorrangfrage und gehört dir** — ich habe
heute eines aufgemacht und mache absichtlich kein zweites.

**3. Die Fabrik baut weiter überwiegend an sich selbst.** Von 23 offenen Paketen arbeiten
jetzt 4 am Erzeugnis (0144, 0145, 0146 und, mittelbar, 0099) statt 1. Die Ursache aus der
letzten Fassung gilt unverändert: Nur die Arbeit an Riegeln schafft sich selbst nach, weil
jede Prüfung eines Riegels einen Befund über einen Riegel erzeugt.

**4. Die Behebung des Commit-Schnitts steht weiter offen.** `agents/lauf.py` Zeile 620
setzt `pfade = schreibpfade(werkzeuge)`, und `schreibpfade` schneidet die Werkzeugzeile am
ersten Stern ab — alle sieben Baurollen committen dieselbe Wurzel. Die Datei liegt außerhalb
jeder Schreibgrenze; 0131 und 0121 bleiben zu Recht `blockiert`. **Zum vierten Mal gemeldet.**

**5. Prüfer setzen `fertig`, obwohl der Ablauf es mir vorbehält.** Fünf Fälle heute, alle
mit richtigem Ergebnis. Zu entscheiden ist, was gilt: Entweder die Prüferrollendateien
bekommen den fehlenden Satz „setze den Status nicht selbst", oder der Ablauf wird an die
gelebte Praxis angeglichen und meine Abnahmestufe entfällt. **Beides ist vertretbar,
schweigend beides nebeneinander nicht** — heute hängt an der Stufe, dass ein Paket ohne
Befund auffällt.

**6. `0003` bleibt gesperrt, seit dem 2026-09-01.** Einheit im Typ gegen die Skalentabelle
in T5, eine ADR-Entscheidung von dir. Unverändert.

**7. `technik.md` zerlegen — zum achten Mal gemeldet, und ich ändere nichts.** Acht Pakete
auf einer Datei, strikt nacheinander. Solange die Kette läuft, ist der Architekt eine Rolle
mit **einem** Platz. Es wäre eine Entwurfsentscheidung, und die gehört nicht mir.

**8. Neu: `technik.md` verweist auf diese Datei über Punktnummern.** An drei Stellen —
Zeile 3078, 3148 und 3170 — steht „`rueckstand.md` Punkt 2" beziehungsweise „Punkt 6 und
7". **Diese Verweise altern mit jeder Fassung**, weil die Liste in jedem Lauf neu numeriert
wird; sie zeigten schon vor diesem Lauf nicht mehr auf das Gemeinte. Ich habe 6 und 7
absichtlich auf ihren Gegenständen gelassen, um die Drift nicht zu vergrößern, aber das ist
ein Notbehelf. Ein Verweis auf eine Nummer in einer Datei, die sich wöchentlich neu
numeriert, hält nicht.

## Was der nächste Lauf zuerst anfasst

1. **0145 ist das erste Paket der Prüfstufe, seit es sie gibt.** Es misst zweihundert
   Runden ohne Spieler gegen die sieben Wertebereichsschranken — **und liefert nebenbei die
   eine Zahl, nach der `ops/plan.md` über vier Fassungen gefragt hat**: wie viele der 310
   Zustandsgrößen sich über eine Runde ändern. Der letzte Stand nennt 0 von 310 und begründet
   es mit einer 78 Byte großen `werte.hpp`; die steht heute bei 17.036 Byte. **Ob die Zahl
   sich bewegt hat, hat seither niemand gemessen.** Kommt der Befund, gehört er zuerst gelesen.
2. **0146 ist neu und in unberührtem Gebiet.** Erster Griff: `git log -- kern/src/aktion.cpp`
   und die Bytezahl, nicht der Commit-Betreff. Meldet es ein Hindernis statt zu liefern, ist
   das ein gutes Ergebnis — dann steht im Paket, welcher Begriff aus T32 fehlt.
3. **0116 auf die Statuszeile prüfen, nicht auf den Inhalt.** Der Inhalt ist geliefert und
   nachgemessen. Steht es nach dem nächsten Durchgang immer noch auf `offen`, ist nicht mehr
   das Paket die Ursache, sondern die Rollendatei `architekt` — dieselbe fehlende Zeile, die
   `technik.md` bei Zeile 3078 schon einmal einen ganzen Zweitlauf gekostet hat.
4. **Urteile ziehen bleibt die Hauptarbeit** — soweit die Prüfer sie mir lassen (Punkt 5).
   **Immer über die Zieldatei messen, nie über den Betreff.**
