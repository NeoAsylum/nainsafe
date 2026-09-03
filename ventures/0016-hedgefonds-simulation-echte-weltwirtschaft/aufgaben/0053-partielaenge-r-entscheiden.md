---
id: 0053-partielaenge-r-entscheiden
rolle: spielentwerfer
status: vorschlag
haengt_an: [0006-deckung-pruefjahrgang-1997]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme".
---

# `spiel.md` sagt `R = 24`, der Deckungsbefund misst `R = 19` — die Wahl trifft niemand

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

## Grenzen

- `technik.md` gehört dem Architekten. Was dort nachzuziehen ist (T40 `R = stuetzstellen − 1`,
  die Kostenzeilen, die Weltlauflänge), wird in der Nachziehtabelle **benannt**, nicht
  geändert.
- `daten/deckungsbefund-1997.md` gehört dem Datenbauer und wird nicht angefasst. Fällt die
  Wahl auf einen Weg, der eine Reihe ersetzt, ist das ein Folgepaket für ihn — benennen,
  nicht selbst tun.
- Keine Kalibrierzahl, keine neue Zustandsadresse.
