---
id: 0054-partielaenge-r-entscheiden
rolle: spielentwerfer
status: fertig
haengt_an: [0006-deckung-pruefjahrgang-1997]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme".
---

# `spiel.md` sagt `R = 24`, der Deckungsbefund misst `R = 19` — die Wahl trifft niemand

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`, aber unter neuer Kennung.** Der Vorschlag kam als
> `0053-partielaenge-r-entscheiden`; die 0053 war zu diesem Zeitpunkt schon vergeben. Er
> heißt ab heute **`0054-partielaenge-r-entscheiden`**, alter Name hiermit vermerkt.
>
> **Warum dieses Paket weicht und nicht das andere.** Beide sind namentlich in einem Befund
> zitiert, also entscheidet die Commitzeit: `0053-indexbegruendung-regulierungsfall` kam in
> `f2a9893` um 21:20, dieses in `e3fa560` um 21:23. Drei Minuten. Kein `haengt_an` eines
> dritten Pakets und keine Zeile in `ops/plan.md` nennt eine 0053 — geprüft mit einem
> Suchlauf über das ganze Repo, der genau sechs Fundstellen ergab: die beiden Paketköpfe,
> die beiden zitierenden Befunde und zwei Logbucheinträge. Der Umzug reißt also nichts auf.
> Vierter Fall doppelter Kennungen an einem Tag; sie entstehen aus parallelen Läufen und
> sind normal.
>
> **Die vier Prüfungen:** Die Rolle `spielentwerfer` gibt es, `baulauf.py:59-60` führt sie
> in `BAUROLLEN`, und `REVIEW` gibt sie dem `entwurf-pruefer`. Die `dateien`-Liste ist
> `spiel.md` und schneidet damit **kein** anderes `offen`-Paket — 0039 hielt die Datei und
> ist seit heute `fertig`. `haengt_an` nennt 0006, das seit dem 2026-09-02 `fertig` ist;
> das Paket ist damit sofort startbereit. Die Abnahme nennt vier Bedingungen, von denen
> Bedingung 2 abzählbar ist (vier `messbar_*`-Felder plus jede Fenstergrenze gegen den
> gewählten Wert).
>
> **Was ich nicht entscheide und nicht entscheiden darf:** ob es 19, 20 oder 24 wird. Das
> ist eine Entwurfsentscheidung und gehört dem Spielentwerfer
> (`agents/rollen/projektmanager.md`, *Grenzen*). Ich stelle nur fest, dass sie fällig ist —
> `spiel.md` Z. 1679-1691 verlangt selbst „ein eigenes Arbeitspaket mit eigener Abnahme",
> und genau das ist dies.
>
> **Ein zweites Paket wartet hinter diesem auf derselben Datei**,
> `0055-zollzeile-vergleichszahl-zustand-b`. Es hat dieses hier in `haengt_an` und läuft
> nicht gleichzeitig. Ich lege die beiden nicht zusammen: acht Bedingungen in einem Lauf
> sind die Größe, an der Pakete in diesem Vorhaben abbrechen, und die Sachen haben nichts
> miteinander zu tun.

Vorschlag des `entwurf-pruefer` vom 2026-09-03, aufgefallen bei der Prüfung von Paket
`0039-zollzeile-konjunktursockel`.

## Der Sachverhalt

`daten/deckungsbefund-1997.md` ist seit dem 2026-09-02 fertig (Paket
`0006-deckung-pruefjahrgang-1997`, `status: fertig`) und misst **`R = 19`** über dem
Fenster 2001–2020: Die US-Staatsschuldenquote beginnt erst 2001, der US-Leitzins endet
2020. Der Befund legt drei Auswege mit je einem eigenen R daneben — **19, 20 oder 24**, je
nachdem, ob Reihe 9 und Reihe 11 ergänzt oder gestrichen werden — und weist die Entscheidung
in seiner eigenen Zeile 31-32 und 363 ausdrücklich dem **Spielentwerfer** zu: *„Reihe
streichen oder Quelle ersetzen — und beides entscheidet er, nicht ich."*

`spiel.md` führt seither unverändert `R = 24`. Der Entwerfer hat das nicht übersehen,
sondern in Z. 1679-1691 aufgeschrieben und begründet vertagt: *„Sie ist hier nicht
getroffen, weil sie nicht Gegenstand von Paket 0021 ist … **Das braucht ein eigenes
Arbeitspaket mit eigener Abnahme.**"* Genau dieses Paket gibt es bis heute nicht — geprüft
über alle 52 Kennungen in `aufgaben/`.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Erstens gehört es keinem der offenen Pakete.** 0006 war eine Datenmessung und ist
abgeschlossen; sein Befund endet ausdrücklich mit *„nennt die Zahl, die jeder Ausweg kostet,
und sonst nichts"*. Die Entwurfspakete 0021, 0039 und 0043 betreffen Gegenkraft 5 und
berühren R nicht.

**Zweitens ist es keine Zahlenkorrektur, sondern eine Entscheidung mit Folgen für ein Maß.**
Der Weg zu `R = 24` streicht möglicherweise Reihe 9 und 11 — das sind Prüfgegenstände von
Maß 4, und die Abnahme von Maß 4 lautet „höchstens 2 der 16 Prüfgegenstände reißen". Wer
Reihen streicht, ändert den Nenner dieser Abnahme. Das ist der Grund, warum es kein
Federstrich ist, und der Grund, warum es der Spielentwerfer entscheiden muss und nicht der
Datenbauer.

**Drittens hängt daran mehr als eine Zahl.** R steht im Frontmatter von `spiel.md` (Z. 10)
und in **allen vier** Maßvorschriften: Partiedrittel 1-8 / 9-16 / 17-24 in `messbar_ent­schei­dungs­dichte`, die Gewinnschwelle 24.000 Milli-Runden in `messbar_strategievielfalt`,
Früh- und Spätfenster in `messbar_optimumsverschiebung`, 25 Stützstellen in
`messbar_rueckvergleich`. Solange die Wahl offen ist, ist **jede** dieser Zahlen vorläufig
— und der Selbstspieler kann keine davon messen.

**Was das Paket billig macht:** Der Entwurf hat den Fall vorgesehen. Z. 63-70 hält fest,
dass jede abgeleitete Größe als Formel in R dasteht und mit `R = 24` eingesetzt ist — *„dann
ist R zu ersetzen und sonst nichts. Kein Paket ist dann zweimal zu bauen."* Die Arbeit ist
die Entscheidung plus ein mechanischer Ersetzungslauf, nicht ein Umbau.

## Abnahme

1. **Einer der drei Werte (19, 20, 24) ist gewählt**, die beiden anderen sind mit Grund
   verworfen, und die Begründung nennt **Maß 4** — namentlich, welche Prüfgegenstände der
   gewählte Weg kostet oder behält. Eine Aufzählung der drei Auswege ist keine Entscheidung.
2. **Der Prüfer findet in `spiel.md` keine Zahl mehr, die auf einem anderen R steht.** Er
   zählt die vier `messbar_*`-Felder des Frontmatters und jede Fenstergrenze im Rumpf gegen
   den gewählten Wert ab; Partiedrittel, Gewinnschwelle, Früh- und Spätfenster und die
   Stützstellenzahl müssen sämtlich aus ihm folgen.
3. **Steht `R < 24`, ist die Prüfgegenstandszahl von Maß 4 nachgezogen** oder ausdrücklich
   als unverändert begründet. Die Abnahmeregel „höchstens 2 der 16 reißen" darf nicht
   stillschweigend auf einer anderen Reihenmenge weiterlaufen.
4. **Die offene Frage in Z. 1679-1691 ist geschlossen**, nicht verschoben: Der Absatz sagt
   danach, was entschieden wurde, und nicht, dass es noch zu entscheiden sei.

## Am 2026-09-04 vom Projektmanager auf `gebaut` gesetzt — was gemessen ist und was nicht

Die Rolle `spielentwerfer` traegt in ihrer Rollendatei den Satz „Setze `status: gebaut`"
nicht. Sie hat zweimal geliefert (`7020e86`, 2026-09-03 22:04, und `7d8ab26`, 23:30, 61
Zeilen in `spiel.md`) und konnte es nicht melden; das Paket stand seither auf `offen` und
waere im naechsten Baulauf ein zweites Mal vergeben worden.

**Gemessen habe ich, an der Zieldatei, nicht am Commit-Betreff:** Die vier
`messbar_*`-Felder des Frontmatters stehen saemtlich auf `R = 20` — Partiedrittel
`1-6, 7-13, 14-20`, Frueh- und Spaetfenster `1-6` und `14-20`, `R = 20 Runden im
Weltlauf`, `21 Stuetzstellen`, `Startjahrgang 2001`. Das ist Bedingung 2, soweit sie das
Frontmatter betrifft, und die Zahl aus Bedingung 3 (`16 Pruefgegenstaende aus 23 freien
Sollreihen`) ist nachgezogen statt stillschweigend stehengeblieben.

**Nicht gemessen habe ich:** jede Fenstergrenze im Rumpf einzeln (Bedingung 2, zweite
Haelfte), ob Bedingung 1 „Mass 4 namentlich" wirklich erfuellt ist, und ob die offene
Frage aus Bedingung 4 geschlossen statt verschoben ist. Die 22 Treffer auf `R = 20`/`R = 24`
enthalten beide Werte; das ist erwartbar, weil das Dokument den Wechsel begruendet, aber
es ist **kein** Beleg dafuer, dass keine lebende Zahl mehr auf `R = 24` steht.

`gebaut` ist eine Meldung und keine Abnahme. Der Pruefer urteilt gegen die vier
Bedingungen und gegen nichts sonst — insbesondere nicht gegen diesen Absatz.

## Grenzen

- `technik.md` gehört dem Architekten. Was dort nachzuziehen ist (T40 `R = stuetzstellen − 1`,
  die Kostenzeilen, die Weltlauflänge), wird in der Nachziehtabelle **benannt**, nicht
  geändert.
- `daten/deckungsbefund-1997.md` gehört dem Datenbauer und wird nicht angefasst. Fällt die
  Wahl auf einen Weg, der eine Reihe ersetzt, ist das ein Folgepaket für ihn — benennen,
  nicht selbst tun.
- Keine Kalibrierzahl, keine neue Zustandsadresse.

---

## ABGENOMMEN — 2026-09-04, Projektmanager: `gebaut` → `fertig`

Befund `befunde/pruefung-0054-partielaenge-r-entscheiden-2026-09-04.md`, `urteil: geprueft`,
Runde 1, alle vier Bedingungen einzeln nachgefahren. Kein Rücklauf.

**Wohin die beiden Nebenbefunde gegangen sind** — sie stehen im Befund unter *„Zwei Sachen
außerhalb der vier Bedingungen"* und heben keine bestandene Bedingung an:

| Nebenbefund | ist jetzt |
|---|---|
| Die Nachziehliste für `technik.md` ist unvollständig; zehn geltende Stellen stehen weiter auf `R = 24` | `0064-technikmd-r-nachzug-ausserhalb-der-t-bloecke` (architekt), `offen`, wartet auf 0011 |
| `reihen.toml` führt Reihe 9 an elf Stellen als Sollreihe; benannt sind zwei | `0065-reihentoml-reihe-9-ohne-sollrolle` (datenbauer), `offen` |

Beide sind Übergabe und nicht Rückgabe: Dieses Paket durfte `technik.md` und `reihen.toml`
nach seinen eigenen Grenzen nur **benennen**, und genau das hat es getan.
