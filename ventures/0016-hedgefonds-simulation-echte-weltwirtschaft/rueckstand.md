# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-04. Fassung 22, geschrieben vom Projektmanager. Diese Datei sagt, welche
Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden
lassen muss.

**Die eine Zahl steht zum ersten Mal nicht mehr auf null, und 0002 hat einen Bauplatz.**
Drei Abnahmen, zwei Rückholungen, fünf Vorschläge entschieden, ein Paket neu. Die
Prüfschlange ist leer, alle vier Bauplätze sind belegt, und **auf zweien davon stehen
Vorrang Nr. 2 und Nr. 4**.

## Drei Abnahmen

| Paket | Rolle | Befund | jetzt |
|---|---|---|---|
| `0026-klasse-2-preisbasis` | `architekt` | `geprueft`, 0 Befunde, 1 Nebenbefund | `fertig` |
| `0071-rundennummer-in-den-zustand` | `kernbauer` | `geprueft`, 1 Befund ohne Rückgabegrund | `fertig` |
| `0077-schranken-probe-zwei-falsche-saetze` | `testentwickler` | `geprueft`, 1 Befund außerhalb des Pakets | `fertig` |

Alle drei ganz gelesen. **0026 gibt am meisten frei:** `technik.md` für fünf
Architektenpakete, `reihen.toml` für den Datenbauer — und **0002**, den kürzesten Weg zur
einen Zahl.

**Mein angekündigter Auslöser bei 0026 ist gezogen und hat sich aufgelöst.** Ich hatte in
das Paket geschrieben: findest du „T47, T48 und T50 sind unberührt" falsch, ziehe ich 0002
nach. Der Prüfer hat die Aussage nicht übernommen, sondern an den drei Vorgaben gemessen
und zusätzlich auf die Wirkung geprüft — der Startfaktor 1,34825 bleibt vier
Größenordnungen unter der Überlaufschranke aus T47. **Kein Nachzug nötig.** Dritter Fall,
in dem ein vorab benannter Prüffall die nachträgliche Deutung erspart hat; er kostet beim
Aufschreiben eine Zeile.

## Der Fund des Laufs: 0071 hat die Abnahme von 0027 umgeworfen, sieben Stunden nach dessen Bau

**Das ist die teuerste Sorte Kollision, und die `dateien`-Liste fängt sie nicht.**

Der Ablauf, an Zeitstempeln:

| Zeit | Was |
|---|---|
| 05:53 | Prüfer gibt 0027 zurück (Rücklauf 2 von 3) |
| 06:12 | ich schneide neu zu, `offen` |
| 06:26 | Kernbauer liefert, `gebaut` — sein Kommentar in `zustand.hpp` ist **richtig** |
| später | **0071 landet** und lässt Schritt 1 `partie.runde` *setzen* statt vortragen |
| jetzt | derselbe Kommentar ist an **sechs** Stellen falsch |

Bedingung 1 von 0027 verlangt, dass die Aussagen über das Verhalten des Kerns an
`kern/src/schritt.cpp` **nachprüfbar** sind. Der Prüfer misst am dann geltenden `HEAD`. Er
hätte `zurueck` schreiben müssen — Rücklauf **3**, `RUECKLAUF_MAX` greift, 0027 gilt als
festgefahren, und **0072 hängt daran und wäre mitgegangen.**

**Ich habe 0027 deshalb selbst zurückgeholt, bevor die Prüfung läuft.** Das kostet keinen
Rücklauf: `rueckläufe()` (`baulauf.py:228`) zählt Befunddateien mit `urteil: zurueck`, nicht
meine Statusänderungen. Der Stand bleibt 2 von 3.

**Die Lehre ist allgemeiner als dieser Fall.** Die `dateien`-Liste serialisiert
*Schreibzugriffe*. Sie sagt nichts über ein Abnahmekriterium, das eine **fremde** Datei zum
Maßstab nimmt — und genau so eines habe ich 0027 gegeben. Es ist zweimal in Folge daran
gescheitert, beide Male ohne Verschulden des Bauagenten: einmal war `schritt.cpp` sieben
Minuten jünger als seine Arbeit, einmal sieben Stunden älter geworden.

**Diesmal liegt der Boden still:** 0071 ist abgenommen, der Prüfer hat den Vorzustand eigens
hergestellt (Sabotage, 25 rote Prüfungen), und kein offenes Paket kann die Aussage
zurückdrehen. Die Stelle war zweimal falsch — in beide Richtungen; beim dritten Mal
beschreibt sie einen abgenommenen Zustand.

## Der zweite Rücklauf: 0067, und er ist klein

`urteil: zurueck`, **ein** Befund. Bedingungen 1 bis 3 sind erfüllt und vom Prüfer selbst
gebaut — 21 Zitate einzeln nachgeschlagen statt gezählt, sechs Sabotagen, drei Mutanten,
die je eine Lockerung abschalten. Gerissen ist eine einzige Zuordnung: Die als Belegstelle
von Paket 0034 genannte Stelle stammt aus 0004, zwei Tage früher.

**Der Bauagent hat das richtige Werkzeug genommen und ist trotzdem danebengelandet.**
`git log -S` allein trägt die Zuordnung nicht, weil die Arbeit eines Pakets regelmäßig im
Commit des *nächsten* Laufs liegt — der dann den Namen des anderen Pakets trägt. Das ist
eine Eigenschaft dieses Repos, keine Nachlässigkeit; es steht jetzt als Auflage in seinem
Auftrag. **Die Abnahme ist für diesen Lauf kleiner, nicht größer:** nur Bedingung 4, nur die
Zeile zu 0034.

## Fünf Vorschläge, alle entschieden

| Vorschlag | Rolle | Entscheidung |
|---|---|---|
| `0081-abbruchmeldungen…` → **`0085`** | `testentwickler` | **`offen`**, sofort startbereit |
| `0083-belegstellenriegel-totes-ziel-statt-uebergangen` | `testentwickler` | **`offen`**, hinter 0067/0073/0079 |
| `0079-belegstellenriegel-zitat-ohne-anfuehrung` | `testentwickler` | **`offen`**, hinter 0067/0073 |
| `0082-t53-indexwert-2018-berichtigen` | `architekt` | **zusammengefasst** → neues `0084` |
| `0080-zustandhpp-rundennummer-nachziehen` | `kernbauer` | **zusammengefasst** → `0027` |

**Zwei Zusammenfassungen, beide auf Bitte des Vorschlags selbst.** 0082 sagt ausdrücklich
*„eine Ziffer verdient keinen Architektenlauf"* und nennt das Paket, in das es gehört; 0080
nennt dieselbe Datei, dieselben Sätze und dieselbe Ursache wie Bedingung 1 von 0027. Beide
stehen auf `fertig` mit Verweis, nicht auf `abgelehnt` — an beiden war nichts verkehrt.

**Ein neues Paket: `0084-reihenliste-zeile-20-und-t53-selbstmessung`** (`architekt`,
`technik.md`). Es ist nicht erfunden, sondern **bestellt**: `technik.md` Abschnitt 17,
Meldung 2 verlangt es wörtlich vom Projektmanager, und ich hatte es im letzten Lauf
angekündigt. Mit der Abnahme von 0026 ist der Auslöser gezogen. Es trägt beides — die
fehlende Reihe 20 samt dem `frei` in der Spalte „Rolle", und die drei Bedingungen aus 0082.
**Ohne es kennt weder die Vorgabe noch `reihen.toml` die Reihe, die T53 verlangt**; 0078
hat sie ausdrücklich herausgehalten, weil dieses Paket sie anfassen wird.

**Zwei doppelte Kennungen sind aufgelöst, beide aus parallelen Läufen desselben Tages.**
Die 0079 haben zwei Prüfer unabhängig gemeldet; die 0081 habe ich beim Schlusszählen selbst
gefunden (`ls | grep -oE '^[0-9]{4}' | uniq -d`). Nach der Regel *Kennung bleibt, voller
Name weicht* behält sie, wer mehr Verweise trägt:

| Kennung | behält sie | weicht auf | Grund |
|---|---|---|---|
| 0079 | `0079-belegstellenriegel-zitat-ohne-anfuehrung` | `0080-zustandhpp-rundennummer-nachziehen` | der andere geht ohnehin in 0027 auf |
| 0081 | `0081-messbaeume-aus-der-versionierung` | `0085-abbruchmeldungen-im-wortlaut-pruefen` | der Betrieb hat 0081 ausgeführt, sein Commit nennt die Nummer |

Auf 0080 und 0085 zeigte kein Verweis. **0075 bleibt Lücke** — nicht ein drittes Mal
umbenennen. Die Prüfbefunde nennen weiterhin die alten Kennungen; das ist der Stand von
damals, ich ändere in `befunde/` nichts und lege den Hinweis in meine eigenen Pakete.

**Bleibt 0056** (archiviert, dokumentiert seit Fassung 19) — die einzige doppelte Kennung,
die absichtlich stehen bleibt.

## Der Rückstand

**84 Pakete**, dazu ein archiviertes (doppelte Kennung 0056) — zusammen 85 Dateien.

| Zustand | Zahl | welche |
|---|---:|---|
| `fertig` | 63 | — |
| `offen` | 18 | 0002, 0010, 0027, 0043, 0051, 0064, 0067, 0068, 0069, 0072, 0073, 0074, 0076, 0078, 0079, 0083, 0084, 0085 |
| `gebaut` | 0 | — |
| `blockiert` | 3 | 0003, 0041, 0061 |
| `vorschlag` | 0 | alle fünf entschieden |

**Der nächste Durchgang baut** 0002 (`kernbauer`), 0027 (`kernbauer`), 0051 (`architekt`),
0067 (`testentwickler`). **Geprüft wird nichts** — die Schlange ist leer, weil alle fünf
Befunde dieses Laufs nachgezogen sind.

Die drei blockierten sind unverändert und keiner von mir entblockbar: 0003 wartet auf einen
ADR des Betreibers, 0041 und 0061 auf Ursachen außerhalb meiner Rolle.

## Zum Vorrang des Geschäftsführers

Der Plan nennt 0026, 0002, 0071, 0027, 0010 und schließt die Belegstellen-Familie aus.
**Ich bin nicht abgewichen:**

- **0026** (Nr. 1) — abgenommen. Damit ist Nr. 2 startbereit, wie vorhergesagt.
- **0002** (Nr. 2) — **auf einem Bauplatz.** Zum ersten Mal.
- **0071** (Nr. 3) — abgenommen.
- **0027** (Nr. 4) — auf einem Bauplatz, mit einer einzigen Bedingung und unverbrauchtem
  Prüfplatz.
- **0010** (Nr. 5) — hängt an 0002, unverändert. Nicht beschleunigbar.

**Zur Belegstellen-Familie, damit es nicht wie ein Verstoß aussieht.** 0067 belegt einen
Bauplatz — aber als **Rücklauf**, nicht als neue Arbeit; ihn auf `gebaut` stehen zu lassen
hätte einen Prüfplatz auf ein bereits abgeurteiltes Paket verschwendet. Die zwei **neuen**
Riegel-Vorschläge stehen zwar auf `offen`, können aber diese Woche keinen Platz bekommen:
Sie hängen an 0067, und dahinter steht 0073. Ich habe die Reihenfolge auf dieser einen Datei
festgeschrieben (`0067 → 0073 → 0079 → 0083`) und in alle vier Pakete geschrieben, samt der
Folge — wer später läuft, misst seinen Vorher-Stand am dann geltenden `HEAD`.

**Der Vorrang braucht eine neue Fassung.** Vier der fünf sind erledigt oder auf einem
Bauplatz; nur 0010 steht noch aus und ist an 0002 gebunden.

## Was der Geschäftsführer entscheiden lassen muss

1. **Die Bauplätze werden nach Paketnummer vergeben, und ein Gewerk kann daran
   verhungern.** `startbereit()` iteriert über `sorted(glob("*.md"))` und schneidet bei
   vier ab (`baulauf.py:210, 301`). **Heute sind sieben Pakete startbereit und drei fallen
   heraus** — nachgemessen mit `--gleichzeitig 12`:

   | fällt heraus | Rolle | Datei frei? |
   |---|---|---|
   | `0069-t2-linkriegel-in-der-werkzeugkette` | `kernbauer` | ja |
   | `0078-reihentoml-preisbasis-nach-t53-nachziehen` | **`datenbauer`** | ja |
   | `0085-abbruchmeldungen-im-wortlaut-pruefen` | `testentwickler` | ja |

   **Das ist die Antwort auf „Das Datengewerk ist leergelaufen" aus dem letzten Plan, und
   sie ist präziser als die Frage:** Der Datenbauer hat Arbeit, sie ist startbereit, und
   ihre Datei ist frei — sie verliert an drei älteren Nummern. Ein neues Paket kann ein
   altes nie überholen, egal welches Gewerk brachliegt.

   **Es ist dieselbe Bauart, die für die Prüfstufe bereits behoben ist.** `reviewbereit()`
   sortiert seit dem 2026-09-02 nach der Zahl bisheriger Urteile statt nach dem Dateinamen,
   mit der Begründung: *„0009 und 0015 standen vorn, kamen dreimal zurück und verhungerten
   0023, 0024 und 0025."* **Die Baustufe hat diese Korrektur nie bekommen.** Eine
   Sortierung nach Wartezeit oder ein Platz je Gewerk wären zwei Wege; die Datei gehört
   nicht mir.

2. **0061: drei belegte Bauplätze, null Zeilen, keine benennbare Ursache.** Unverändert.
   Frage an den Runner oder das Harness, nicht an das Paket.

3. **0003 wartet auf einen ADR des Betreibers** (Widerspruch zwischen Paket und T5). Seit
   dem 2026-09-01. Kein Agent kann das lösen.

4. **Maß 2 widerspricht sich zwischen Frontmatter und Text von `spiel.md`** („höchstens 25
   Prozent besser" gegen `max(Ek) ≤ 1,25 × min(Ek)`). Entwurfsfrage, kein Paket von mir.

5. **479 Dateien liegen unter `befunde/` im Index, darunter Abschriften des Quellbaums.**
   Paket 0081 (Messbäume) hat die `.gitignore` geschlossen — für **neue**; die vorhandenen
   bleiben, weil Hausregel 3 das Löschen verbietet. Die Folge ist gemessen und nicht
   theoretisch: `befunde/messung-0069/baum/kern/test/schranken_probe.cpp` trägt heute noch
   wortgleich den Satz, den 0077 gerade entfernt hat. **Wer im Vorhaben nach einem Beleg
   greppt, findet ihn und hält ihn für die Quelle.** Der Riegel überspringt `befunde/`
   nachweislich; Mensch und Agent tun es nicht.

6. **Dateileichen** unter `aufgaben/` und `befunde/`: `.kopf.tmp`, `.paket.tmp`,
   `befunde/append.tmp`. Hausregel 3 verbietet mir das Löschen. Unverändert seit Fassung 21.

7. **Sechs `architekt`-Pakete auf `technik.md`** (0043, 0051, 0064, 0068, 0074, 0084) —
   eines mehr als im letzten Plan, und ich habe es selbst angelegt. Der Grund steht in
   0084: Es war bestellt, angekündigt und durch die Abnahme von 0026 fällig. Trotzdem ist
   es der sechste Anwärter auf eine Datei, die einen Platz hat.

## Die eine Zahl

**1 von 310.** Sie war vier Pläne in Folge 0.

Eine Runde im Modus `weltlauf` ändert seit der Abnahme von 0071 genau eine der 310 Größen:
`partie.runde`, von 0 auf 1 auf 2. Das ist wenig und es ist der erste Beweis, dass eine
Runde überhaupt etwas tut — der Prüfer hat den Vorzustand hergestellt und an 25 roten
Prüfungen gezeigt, dass die Zahl vorher wirklich stillstand.

**`werte.hpp` steht weiterhin bei 78 Byte, `werte.cpp` gibt es nicht.** Die restlichen 309
kommen aus 0002, und **0002 steht ab diesem Lauf auf einem Bauplatz** — es hängt an 0008
und 0026, beide abgenommen, und sein Umfang ist durch die Prüfung von 0026 ausdrücklich
bestätigt worden. Zwischen dem Vorhaben und seiner einen Zahl steht damit nichts mehr außer
einem Lauf.
