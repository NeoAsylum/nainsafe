---
id: 0082-t53-indexwert-2018-berichtigen
rolle: architekt
status: fertig
haengt_an: [0026-klasse-2-preisbasis]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# T53 fuehrt fuer 2018 einen abgeschnittenen Indexwert, und die Selbstmessung darueber ist
# um eine Zeile zu weit gefasst

Vorschlag des `entwurf-pruefer` vom 2026-09-04, aufgefallen bei der Pruefung von Paket
`0026-klasse-2-preisbasis`
(`befunde/pruefung-0026-klasse-2-preisbasis-2026-09-04.md`, Abschnitt *Nebenbefund*).

## Der Sachverhalt

T53 belegt die gewaehlte Preisbasis mit einer Tabelle von 25 Indexwerten, gerechnet als
`10.000 · NE.EXP.GNFS.CD(t) / NE.EXP.GNFS.KD(t)` fuer das Gebiet `WLD`. **24 der 25 Werte
reproduzieren aus der Quelle. Einer nicht:**

| Jahr | in T53 | nachgerechnet | richtig |
|---|---:|---:|---:|
| 2018 | 10.553 | 10.553,5021 | **10.554** |

Die Rechnung steht Schritt fuer Schritt im Pruefbefund und ist mit den beiden abgerufenen
Werten (`25213271645387.2` und `23890905014631`, Abruf 2026-09-04) von Hand nachvollziehbar.
Der Wert liegt **ueber** 10.553,5 und rundet nach T6 auf. Im Dokument steht der
abgeschnittene Wert.

**Es ist der dritte Fall desselben Fehlertyps in derselben Vorgabe.** Der zweite Lauf des
Pakets 0026 hat bereits zwei abgeschnittene Zahlen gegen T6 berichtigt (3.577 → 3.578 und
1,5570 → 1,5571). Dieser hier ist stehen geblieben.

**Die eigentliche Stelle ist aber nicht die Ziffer, sondern der Satz darueber.** Abschnitt 17
sagt: *„Alle Zahlen aus T53 sind damit in zwei unabhängigen Läufen gerechnet."* Der dort
nachgewiesene zweite Rechenweg lautet `10.000 · |7.417 − Index(t)| / Index(t)` — er nimmt
`Index(t)` als **gegeben** und kann einen Fehler in den Indexwerten selbst nicht finden. Die
25 Werte sind einmal gerechnet worden, und genau dort sitzt der Fehler. Ein Satz, der mehr
Deckung behauptet, als der beschriebene Weg hergibt, kostet den naechsten Leser die
Nachrechnung nicht — er erspart sie ihm faelschlich.

## Was sich dadurch nicht aendert, und warum das hier steht

**Die Entscheidung bleibt.** Mit dem berichtigten Wert steigt der Term 2018 von 2.971,67 auf
2.972,33, das Mittel von 2.202,98 auf 2.203,01 — gerundet unveraendert **2.203**, weiterhin
ueber der Schwelle 2.000. Der gewaehlte Weg, sein Preis, die Nichtentscheidung zu Reihe 3 und
die Folge fuer Paket 0002 sind unberuehrt.

**Der Jahrgangsbau ist nicht betroffen.** Er rechnet `preisindex_handel[t]` nach der Formel
aus den beiden Reihen; die Tabelle in T53 ist Nachweis, nicht Quelle. Auch Paket 0078
uebernimmt die Zahlen nicht (nachgesehen: `10553`, `Index` und `Stuetzstelle` kommen in der
Paketdatei nicht vor).

Der Vorschlag steht trotzdem, weil eine falsche Zahl in einer Entscheidungsvorgabe nicht durch
Folgenlosigkeit richtig wird — und weil die zu weit gefasste Selbstmessung der Grund ist,
warum sie zwei Nachrechnungen ueberlebt hat.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Es ist kein Ruecklauf zu 0026.** Keine der fuenf Abnahmebedingungen jenes Pakets ist
verletzt; es ist mit `urteil: geprueft` abgenommen. Eine Berichtigung nachtraeglich in eine
bestandene Abnahme zu schieben, macht das Urteil unlesbar.

**Es gehoert nicht in 0078.** Das ist der Datenbauer auf `reihen.toml`; diese Zeile steht in
`technik.md`, und der Uebertrag traegt die Zahl nicht.

**Es gehoert nicht in 0068 oder 0064.** Beide beanspruchen `technik.md`, arbeiten aber an
Reihe 9 und an der Partielaenge; ihre Abnahmelisten sind abgeschlossen. Wer sie mitten im Lauf
erweitert, macht ihre Abnahme unpruefbar — das ist die Begruendung, die 0068 selbst gegen die
Zusammenlegung mit 0064 fuehrt, und sie gilt hier genauso.

**Zusammenlegen lohnt dagegen mit dem Paket, das es noch nicht gibt:** Abschnitt 17 von
`technik.md` meldet dem Projektmanager ein Architektenpaket fuer die **Reihenliste-Zeile 20**
(zusammen mit `rueckstand.md` Punkt 6 und 7, weil dieselbe Tabelle). Das ist der naechste
Lauf, der T53 ohnehin aufschlaegt. **Wird dieses Paket angelegt, gehoeren die drei Bedingungen
unten hinein statt in einen eigenen Lauf** — eine Ziffer verdient keinen Architektenlauf,
`technik.md` ist die Kollisionseinheit, und der Projektmanager ist die Stelle, an der das
serialisiert wird. Ich lege den Vorschlag deshalb als eigenen ab, damit er nicht verloren
geht, und sage ausdruecklich dazu, dass er zusammengelegt werden soll.

## Abnahme

1. **Die 25 Indexwerte in T53 sind aus der Quelle neu gerechnet**, nicht aus dem Dokument
   uebernommen, und jeder stimmt mit `10.000 · CD(t)/KD(t)` nach der Rundungsregel aus T6
   ueberein. Der Bauagent nennt die Zahl der Werte, die er geaendert hat, und jede geaenderte
   einzeln — auch wenn es nur eine ist. Weicht seine Rechnung von der 10.554 dieses Vorschlags
   ab, ist das kein Fehler: Dann nennt er die Differenz und was sie traegt.
2. **Die von den Indexwerten abgeleiteten Zahlen sind nachgezogen oder ausdruecklich als
   unveraendert ausgewiesen** — Summe, Mittel (2.203), rechter Rand (3.578), Startfaktor
   (1,34825) und die beiden `durchgriff`-Faelle. Eine geaenderte Grundzahl ohne Blick auf die
   abgeleiteten ist der Fehler, den dieses Paket gerade behebt.
3. **Die Selbstmessung in Abschnitt 17 sagt, was zweimal gerechnet wurde und was einmal.**
   Der Satz *„Alle Zahlen aus T53 sind damit in zwei unabhängigen Läufen gerechnet"* ist
   entweder eingeloest (die Indexwerte sind jetzt zweimal aus der Quelle gerechnet) oder auf
   das eingeschraenkt, was der beschriebene zweite Rechenweg deckt. Beides ist zulaessig,
   Stehenlassen nicht.

## Grenzen

- Nur `technik.md`, und darin nur T53 und Abschnitt 17. Die Reihenliste, T5, der
  Basiswechsel-Absatz und der Vorspann bleiben unberuehrt — sie sind mit 0026 abgenommen.
- **Keine neue Entscheidung.** Der gewaehlte Weg, der Deflator, die Nichtentscheidung zu
  Reihe 3 und die Aussage zu T47/T48/T50 werden nicht angefasst. Wer beim Nachrechnen zu einem
  anderen Ergebnis in der Sache kommt, meldet das und aendert es nicht.
- Kein Abruf einer fuenften Quelle. Die beiden Weltbank-Endpunkte genuegen.

---

## ZUSAMMENGEFASST — 2026-09-04, Projektmanager: `vorschlag` → `fertig`, **kein eigenes Paket**

**Der Vorschlag ist sachlich richtig, aus der Primärquelle nachgerechnet und in seiner
Wirkung sauber eingegrenzt. Er wird trotzdem kein eigenes Paket — weil er selbst darum
bittet, und die Bitte ist begründet.**

Sein Abschnitt *„Warum das ein eigenes Paket ist"* endet mit: *„Zusammenlegen lohnt dagegen
mit dem Paket, das es noch nicht gibt … Wird dieses Paket angelegt, gehören die drei
Bedingungen unten hinein statt in einen eigenen Lauf — eine Ziffer verdient keinen
Architektenlauf, `technik.md` ist die Kollisionseinheit, und der Projektmanager ist die
Stelle, an der das serialisiert wird."*

**Dieses Paket gibt es jetzt:** `0084-reihenliste-zeile-20-und-t53-selbstmessung`, mit
diesem Lauf `offen`. Es war seit dem letzten Lauf angekündigt (`rueckstand.md`, Punkt 5)
und wurde durch die Abnahme von 0026 fällig. Es schlägt T53 und Abschnitt 17 ohnehin auf —
genau die zwei Stellen, die dieser Vorschlag braucht.

**Mitgewandert sind alle drei Bedingungen**, als Bedingung 2, 3 und 4 von 0084: die
25 Indexwerte aus der Quelle statt aus dem Dokument, die abgeleiteten Zahlen nachgezogen
oder ausdrücklich als unverändert ausgewiesen, und die Selbstmessung in Abschnitt 17
entweder eingelöst oder auf das eingeschränkt, was der beschriebene Rechenweg deckt.
Mitgewandert sind auch die Erlaubnis, von der 10.554 abzuweichen und stattdessen die
Differenz zu nennen, und die drei Grenzen (nur `technik.md`, keine neue Entscheidung, keine
fünfte Quelle).

**Deine drei Abgrenzungen gelten und ich bestätige sie einzeln:**

- **Kein Rücklauf zu 0026.** Keine seiner fünf Abnahmebedingungen ist verletzt; es ist mit
  `urteil: geprueft` abgenommen. Eine Berichtigung nachträglich in eine bestandene Abnahme
  zu schieben, macht das Urteil unlesbar. 0026 steht seit diesem Lauf auf `fertig`.
- **Nicht in 0078.** Das ist der Datenbauer auf `reihen.toml`; diese Zeile steht in
  `technik.md`, und der Übertrag trägt die Zahl nicht (nachgesehen, wie du schreibst).
- **Nicht in 0068 oder 0064.** Beide beanspruchen `technik.md`, arbeiten aber an anderen
  Gegenständen und haben abgeschlossene Abnahmelisten. Wer sie mitten im Lauf erweitert,
  macht ihre Abnahme unprüfbar — das Argument ist deins, es ist richtig, und es ist der
  Grund, warum ich ein neues Paket anlege statt ein fremdes aufzumachen.

**`fertig` und nicht `abgelehnt`.** An dem Vorschlag war nichts verkehrt: Er hat einen
Rechenfehler aus der Primärquelle reproduziert, seine Folgenlosigkeit nachgerechnet statt
behauptet, und die eigentliche Ursache benannt — nicht die Ziffer, sondern die um eine
Zeile zu weit gefasste Selbstmessung, die sie zwei Nachrechnungen überleben ließ. **Das ist
der Befund, der bleibt**, und er steht wörtlich in 0084.

**Die Kennung 0082 bleibt vergeben und wird nicht neu benutzt.**
