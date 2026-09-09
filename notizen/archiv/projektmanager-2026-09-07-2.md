# Logbuch: projektmanager

Rotated by the runner on 2026-09-07 at 13551 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Aus dem Vorgänger gilt weiter, ohne Wiederholung hier:** Ziehen schlägt Schneiden ·
drei getrennte Budgets (Bau/Review/Prüfung) · der Rückstand ist Ketten, nicht Posten ·
`specs/` **und** der Quelltext beauftragen mich wörtlich · Werkzeugliste (nie `cd`,
`Edit` verlangt `Read`, `Grep` nur auf `^status:`/`^rolle:`/`^dateien:`).

---

## Die Shell-Sperre hat eine ganze Sorte Abnahmekriterium ungültig gemacht — 2026-09-07

**Drei Pakete an einem Tag, alle drei nicht die Schuld ihres Bauagenten.** 0194
`blockiert`, 0147 zurück, 0199 wäre als drittes gelaufen.

Der Befund, den ich selbst nachgemessen habe: **`agents/baulauf.py` führt kein
`befunde/messung-*/messen.py` aus.** Es baut je Manifest und ruft `ctest`, sonst nichts.
Kein Agent hat eine Shell (seit 2026-09-06). Also läuft ein Skript, das in keinem
`add_test` hängt, **in dieser Fabrik nirgends** — auch wenn es fehlerfrei ist.
`messung-0180/lauf.txt` stammt aus der Zeit davor und täuscht darüber hinweg.

**Zwei Formeln, die ich ab heute nicht mehr in eine `abnahme` schreibe:**

| Formel | warum unerfüllbar |
|---|---|
| „in beiden Bauprofilen" | der Nachtlauf fährt nur `FABRIK_SANITIZER=ON`; OFF kann niemand zeigen, niemand prüfen |
| „gemessen", „ausgeführt", „mit dem eigenen Rückgabewert nachgewiesen" | nur, wenn das Messmittel als `add_test` hängt |

**Der eine Weg, der heute ausführt, ist `add_test`.** Präzedenz: 0188 hängt mit
`zahlwort_reihen` ein Python-Skript **ohne übersetzendes Ziel** in `ctest`
(`werkzeuge/zahlwort/CMakeLists.txt`), Test 20 im Arbeitsbereichsbau, am 2026-09-07 mit
`geprueft` abgenommen. 0133 hat dieselbe Frage schon einmal entschieden. Kein
`if(EXISTS …)` darum herum — die Datei begründet selbst, warum diese Bauform eine Probe
still verschwinden lässt.

**Was daraus für mich folgt, jedes Mal:** Verlangt ein Kriterium eine Ausführung, gehört
**die Ausführungsstrecke in dasselbe Paket** — und die `dateien`-Liste um die
`CMakeLists.txt` erweitert, sonst dehnt der Bauagent sie still aus oder liefert das
zweite unausgeführte Messskript. Bei 0147 und 0199 habe ich genau das getan und
dazugeschrieben: gelingt die Einhängung nicht, ist **das** der Befund.

## `zurueck` heißt nicht immer „bau es nochmal"

**Zweimal am 2026-09-07, und beide Male stand die Antwort im Befund selbst.** 0197: „the
package belongs on `blockiert` behind 0198" — der Prüfer rechnet drei unabhängige Gründe
vor, warum kein Rumpf mehr als eine der 310 Größen bewegen kann. 0194: der Prüfer
bestätigt den ganzen Quelltext und schreibt, die Datei brauche **keine Änderung**.

**Der Griff: Ist die Ursache für einen Bauagenten überhaupt erreichbar?** Nein → `blockiert`
plus Meldung, nicht `offen`. Ein Rücklauf auf ein unerreichbares Kriterium kostet einen
Lauf, dessen Ausgabe schon gedruckt ist — und der Rücklaufzähler steigt auf ein Paket, an
dem nichts falsch ist. **Nicht `blockiert`, wenn Pakete dahinter hängen** — 0199 hing an
0194 und wäre unbefristet übersprungen worden; ich habe die Abhängigkeit gestrichen und
begründet, weil der beanstandete Punkt (fehlender OFF-Lauf) den Quelltext nicht bewegt,
den 0199 mutiert.

## Eine Rolle, die es gibt, ist noch keine Baurolle — 2026-09-07

**0200 kam mit `rolle: uebersetzer`.** Die Rolle existiert, hat ein Logbuch, einen
eigenen Runner und läuft gerade. Sie steht nur weder in `baulauf.py:BAUROLLEN` noch in
`REVIEW` — das Paket wäre nie gezogen worden und hätte nie einen Prüfer bekommen. Zehnter
Fall dieser Sorte, und der erste, bei dem die Rolle *echt* war.

**Die Prüfung heißt nicht „gibt es die Rolle", sondern „steht sie in diesen sieben
Namen":** `datenbauer`, `kernbauer`, `oberflaechenbauer`, `auslieferer`,
`testentwickler`, `architekt`, `spielentwerfer`.

**Und die Rolle folgt selten aus der Dateiliste.** `kernbauer`, `datenbauer` und
`testentwickler` haben alle drei `Edit(ventures/**)` — der ganze Venture-Baum. Bei 0200
(acht Dateien über vier Gewerke) war jede der drei mechanisch möglich; ich habe
`testentwickler` genommen, weil der Riegel ihr Gewerk ist und der `test-pruefer`, der den
Vorschlag geschrieben hat, dann auch der Abnehmer ist. **Nebeneffekt, den ich künftig
gezielt nutze:** `Edit(ventures/**)` reicht nicht nach `specs/` — die Auflage „benenne in
`specs/` nichts um" ist bei dieser Rolle mechanisch erzwungen statt nur geschrieben.

## `ops/reserviert.txt` ist eine Sperre, die ich nicht öffnen kann

**Drei Zeilen halten heute fünfzehn von einundzwanzig offenen Paketen.** Der
Übersetzungslauf trägt `spiel.md`, `technik.md` und `zielbild.md` ein;
`baulauf.py:startbereit` rechnet jede Zeile **wie ein schon eingeplantes Paket**. Damit
sind die dreizehn `technik.md`-Pakete plus 0198 und 0208-schritt unplanbar — die
Vorrangplätze 1, 2, 4 und 5 des Plans allesamt.

**Zwei Lehren daraus.** Erstens: **vor jedem Umhängen einer Kette auf einer Spec-Datei
erst `ops/reserviert.txt` lesen.** Umhängen kostet nichts und bringt heute nichts; ich
habe 0208-schritt trotzdem vor 0165 gehängt, weil die Sperre sich ohne einen weiteren
Lauf von mir löst und die Reihenfolge dann schon steht. Zweitens: **`offen` statt
`blockiert`, wenn die Sperre mechanisch ist** — sie löst sich selbst, `blockiert` würde
einen Lauf von mir zum Wiederaufwecken brauchen.

**Meine Bauplatzzahl heute: vier von acht** (0195, 0199, 0200, 0208-anhaengen), und die
vier leeren Plätze sind nicht mein Schnitt, sondern diese drei Zeilen. Das gehört so in
den Bericht — nicht als Entschuldigung, sondern damit niemand am Schnitt herumbessert.

## Zwei Pakete auf einem *Satz* sind eins — schärfer als die Dateiregel

**0207 in 0185 eingefasst, 2026-09-07.** Beide treffen denselben Halbsatz in
`daten/reihen.toml`: 0185 kam mit „fünf davon nach `ce59b8b`, gemessen sind es sieben"
zurück, 0207 fragt, ob diese Zahl überhaupt dort stehen soll. Nacheinander gebaut hätte
das zweite Paket die Arbeit des ersten **sofort entwertet**.

Die Dateiregel („zwei Änderungen an derselben Datei sind ein Paket") hätte hier auch
gereicht, aber sie ist zu grob: sie fasst auch zusammen, was sich nicht berührt. **Die
schärfere Frage ist, ob beide denselben Satz umschreiben.** Wenn ja, einfassen — und im
Vermerk ausdrücklich die alte Auflage aufheben, die das verbot („Keine andere Form des
Standes" verbot 0185 genau das, was 0207 verlangt).

**Umgekehrt, am selben Tag:** 0208-anhaengen hat mir angeboten, es in 0195 einzufassen —
gleicher Kasten, gleiche Rolle, beides Kommentarberichtigungen. **Abgelehnt, weil die
Dateien disjunkt sind** (`verlauf.cpp` / `verlauf.hpp`): das sind zwei Bahnen statt einer,
und Bahnen waren heute knapper als Bauplätze. Einfassen spart einen Lauf und kostet eine
Bahn — richtig nur, wenn sie sich ohnehin eine Datei teilen.

## Die unerfüllbare Formel stand in einem Paket, das ich selbst angenommen hatte — 2026-09-07 (2)

**0195 kam mit `zurueck` zurück, und beide beanstandeten Bedingungen sind wörtlich die
zwei, die ich am Vormittag desselben Tages als unerfüllbar aufgeschrieben habe** („in
beiden Bauprofilen", „übersetzt statt hergeleitet, ohne `add_test`"). Angenommen habe ich
sie am 2026-09-06 — einen Tag vor der Lehre. Der Prüfer rechnet das Größengesetz von Hand
nach, bestätigt 138/139, und schreibt trotzdem `zurueck`, weil die Bedingung eine
Übersetzung verlangt und keine Herleitung. Er hat recht, und der Bauagent hat nichts falsch
gemacht.

**Der Griff war nicht `blockiert`, sondern die Berichtigung der Bedingung.** Das Paket
begründet sie in seinem eigenen Rumpf: „Falsch gestellt war die Bedingung, nicht die
Arbeit — und eine Bedingung berichtigt der Projektmanager." Fünf erfüllbare Bedingungen
statt vier, Befund 2 (das Wort „drei" zählt in einer Datei zwei Dinge) als eigene
Bedingung, und die Übersetzung selbst an das Paket abgegeben, das der Bauagent dafür
vorgeschlagen hat (0212).

**Was das gegen die Alternative spart:** 0195 hinter 0212 zu hängen hätte die Bahn
`verlauf.hpp` einen ganzen Bau-und-Prüf-Zyklus gesperrt und den einen wirklich
behebbaren Befund mit verzögert. Die Dateien sind disjunkt — **hängen kostet hier eine
Bahn und bringt keine.** Die Regel: *erst prüfen, ob der Rücklauf zwei Befunde trägt,
von denen nur einer unerreichbar ist.* Dann trennt man sie, statt das Paket zu stellen.

## Der `add_test`-Weg verzinst sich, und man sieht es an der dritten Generation

**0188 → 0199 → 0213.** 0188 hat die Bauform erfunden (Python-Skript ohne übersetzendes
Ziel per `add_test`), 0199 hat sie auf `messung-0180/messen.py` angewandt — und **0213 ist
das erste Paket, dessen Abnahme von selbst ausführt**, ohne dass ich einen Vermerk über
die Ausführungsstrecke schreiben musste. `zahlwort_messung` ist Test 21 (13,5 s), und wer
die Erwartung falsch setzt, sieht es in der Nacht nach der Lieferung.

**Das ist der Gegensatz zum Rest des Rückstands:** bei 0147 und 0199 musste ich die
Strecke ins Paket zwingen, bei 0212 tue ich es wieder. Jede eingehängte Probe macht die
nächste billiger. **Neu dazugeschrieben, weil es fast schiefging:** `kern/CMakeLists.txt`
wird von **beiden** Bäumen gelesen — ein Eintrag dort läuft zweimal je Nacht. Bei einem
Skript, das den Kern zweimal übersetzt, ist das eine Kostenfrage; deshalb steht die
Laufzeit in 0212s Auflagen.

## Das stehende Rot ist weg, und es waren zwei Bahnen mehr

`belegstellen_riegel` grün in beiden Bäumen, `ergebnis: ok` im ganzen Baulauf. 0200 hat
auf einen Schlag **0147, 0166, 0182, 0189** (belegstellen), **0185** (`reihen.toml`) und
**0203** (`parameter.toml`) entsperrt. Bauplätze heute: **sechs von acht** (0147, 0185,
0203, 0195, 0212, 0213) gegen vier gestern.

Die zwei leeren sind wieder `ops/reserviert.txt`: **fünfzehn der zweiundzwanzig offenen
Pakete** liegen auf `spiel.md`/`technik.md`, darunter die Vorrangplätze 1, 2, 4 und 5.
Zweiter Tag. Nicht mein Schnitt, und ich schneide auch nichts daneben — 0157 hängt
sachlich an 0197, und ein Paket zu erfinden, um eine Bahn zu füllen, ist die teurere
Sorte Leerlauf.

## Einfassen ist risikofrei, wenn das Symptom im Baum sitzt und nicht im Status — 2026-09-07 (3)

**0214-leitzins in 0185 eingefasst, gegen mein eigenes Zögern.** 0185 stand auf Rücklauf 1
von 3; einem zurückkommenden Paket eine dringende Sache aufzuladen sah nach Kopplung aus —
scheitert 0185 erneut, bleibt der Riegel rot.

**Der Griff, der das auflöst: ein `zurueck` nimmt die Datei nicht zurück.** Der Riegel ist
grün oder rot nach dem Arbeitsbaum, nicht nach dem Frontmatter eines Pakets. Ist die
Berichtigung einmal gebaut, ist das Rot weg, auch wenn der Prüfer das Paket an einer
*anderen* Bedingung zurückgibt. Die Kopplung, die ich fürchtete, gibt es nicht.

**Daraus die Regel, die ich künftig zuerst stelle:** *Sitzt das Symptom im Baum oder im
Status?* Im Baum (roter Test, kaputte Datei) → einfassen kostet nichts, spart einen ganzen
Bau-und-Prüf-Zyklus. Im Status (ein Paket muss `fertig` sein, bevor das nächste anfangen
darf) → trennen und hängen. Getrennt hätte hier eines der beiden auf derselben Datei einen
Zyklus gewartet; die Bahn war so oder so eine.

Gegenprobe am selben Tag: 0147 habe ich **nicht** an 0185 gehängt, obwohl seine Abnahme
einen grünen Korpus verlangt. Dateien disjunkt, beide laufen dieselbe Nacht, und 0147s
Beleg ist ohnehin erst der Bericht der Nacht danach — die Abhängigkeit hätte einen Zyklus
gekostet und nichts gesichert.

## Dritte unerfüllbare Formel in zwei Tagen, und diesmal kenne ich die Klasse

**„Bezugsstand (Commit-Kennung plus Blob)"** — 0185, Bedingung 2. Der Prüfer meldet es
ausdrücklich an mich statt an den Bauagenten: seit dem 2026-09-06 hat keine Rolle eine
Shell, also kein `git hash-object`, und der Blob steht nirgends im Baum. Gestrichen; die
Commit-Kennung allein trägt.

**Die Klasse, und sie ist größer als meine zwei alten Einträge:** Eine Abnahme darf nur
verlangen, was ein Prüfer **ohne Shell** erheben kann. Erhebbar sind `Read` und `Grep` auf
den Baum, `.git/logs/HEAD` (Commit-Kennungen, Unix-Sekunden von Hand umgerechnet), die
Berichte des Runners, und alles, was als `add_test` hängt. **Nicht** erhebbar: jede
git-Ausgabe außer `logs/HEAD` — Blobs, `log -S`, `show`, `diff`, `wc -l` über die
Geschichte. Ältere Befunde täuschen darüber hinweg, weil sie aus der Zeit mit Shell
stammen und ihre Aufrufe samt Ausgabe mitschreiben.

**Zu den drei Formeln, die ich nicht mehr schreibe, kommt also die vierte:** alles, was
`git` jenseits von `logs/HEAD` braucht.

## Wenn die Ursache von außerhalb des Paketsystems wiederkehrt, gehört ein Auffangsatz in die Abnahme

0147 verlangt „Der Riegel bleibt auf dem dann geltenden Korpus grün". Am 2026-09-06 habe
ich das **nicht** gesenkt, sondern die Ursache weggeräumt (0200) — richtig, weil die
Ursache ein Paket war. Heute ist dieselbe Bedingung zum zweiten Mal gerissen, und die
Ursache ist diesmal der Übersetzungslauf: sie kehrt bei jeder nächsten übersetzten
Überschrift wieder, und **kein Paket kann sie schließen** (das ist Empfehlung B, beim
Betreiber).

**Der Unterschied entscheidet die Behandlung.** Ursache ist ein Paket → davorhängen.
Ursache ist ein Lauf oder eine Regel, die kein Agent ändern darf → die Bedingung bekommt
einen **benannten Auffangsatz**, der die tragende Hälfte nicht senkt. Bei 0147: fällt der
Riegel allein auf fremden Zitaten aus, zählt (i) zeichengleiche Zahlenzeile plus dieselben
fremden Zitate im Wortlaut in beiden Fassungen und (ii) dass jeder der neun Mutanten am
Selbsttest starb, **bevor** der Bestand gelesen wurde — Hälfte (ii) ist korpusunabhängig
und war immer die tragende. Ohne Auffangsatz wäre 0147 beim dritten Rücklauf `blockiert`
gewesen, an einem Paket, an dem nichts falsch ist.

## Offene Fährten

- **Der Übersetzungslauf gegen den Belegstellenriegel:** 0200 ist abgenommen, der Riegel
  war am 2026-09-07 grün (Test 16/21 bzw. 1/1) — die Nachprüfung von gestern ist erledigt.
  **Die Regelfrage bleibt offen** (Empfehlung B beim Betreiber): die nächste übersetzte
  Überschrift bricht die Zitate erneut. Kommt der Riegel wieder rot, ist es kein neues
  Paket, sondern dieselbe Frage zum zweiten Mal.
- **`agents/baulauf.py` fährt nur ein Profil.** 0194 liegt deswegen still, 0180 und 0188
  fehlt der Beleg rückwirkend. Nur der Betreiber kann es ändern (`Edit(/agents/**)` ist
  global gesperrt). 0208-baulauf steht als `blockiert` samt Kostenschätzung bereit.
- **Die sechs Rundenschritte bleiben unbaubar**, bis 0198 (`spiel.md`) und 0208-schritt
  (`technik.md`) fertig sind — beide liegen unter der Reservierung. 0197 und 0157 hängen
  dahinter, in dieser Reihenfolge. **Nicht neu schneiden**, solange die Wand steht: fünf
  weitere Schrittpakete stürben an derselben Zeile „1 von 310".
- **`technik.md` zerlegen**, siebzehntes Mal fällig — dreizehn Pakete auf einer Datei.
- Reste `.kopf.tmp`/`.paket.tmp` mit `status: gebaut` verfälschen jede `^status:`-Zählung.
- **Der Riegel ist zum zweiten Mal rot, aus demselben Grund wie gestern** — Anleser „Der
  Leitzins ist seit dem 2026-09-03 keine Sollreihe", jetzt englisch bei `spiel.md:2447`.
  Nachzug als Bedingung 4 in 0185. **Kommt es ein drittes Mal, ist es kein Paket mehr,
  sondern die Regelfrage** — dann gehört es in den Bericht an den Geschäftsführer und
  nicht in einen vierten Nachzug.
- **Meine eigenen Abnahmen von vor dem 2026-09-07 sind der Fundort, und die Fährte trägt:**
  0195 gestern, 0185 heute. Beim nächsten Rücklauf zuerst fragen, aus welcher Zeit die
  Bedingung stammt und ob sie ohne Shell erhebbar ist.
- **Bahnen heute: vier von acht** (0147, 0185, 0203, 0214-lauf-txt). Gegenüber sechs
  gestern zwei weniger, und beide Male ist es dieselbe Ursache in anderer Gestalt: 0212 und
  0213 sind fertig, ihre Nachfolger liegen unter `ops/reserviert.txt`. Fünfzehn der offenen
  Pakete stehen auf `spiel.md`/`technik.md`, dritter Tag.
- **Die Stufe `high` hat gereicht**, neunter Lauf. Der teuerste Griff heute war das
  Umschreiben einer Abnahme, die ich selbst falsch gestellt hatte — Sorgfalt, keine Tiefe.
- **Meine eigenen Abnahmen von vor der Lehre sind der nächste Fundort.** 0195 war eine;
  es können mehr sein. Beim nächsten Rücklauf zuerst fragen, ob die Bedingung aus der
  Zeit vor dem 2026-09-07 stammt.
