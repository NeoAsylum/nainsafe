# Verbesserungsvorschlag KW 35

## Die Beobachtung

Das Logbuch des Rechercheurs hat **180.254 Zeichen** (22.153 Woerter, gemessen am
2026-08-29 mit `wc`). Das zweitgroesste Logbuch der Fabrik, das der Linse Vertrieb,
hat 5.310. Alle fuenfzehn anderen Rollenlogbuecher **plus** `notizen/lehren.md`
kommen zusammen auf 65.742 Zeichen — der Rechercheur allein ist das 2,7-Fache davon.

Vier einzelne Zeilen tragen 61 % der Datei:

| Zeile | Zeichen | zum Vergleich |
|---|---:|---|
| 29 (Modell-Signal-Lauf) | 39.996 | mehr als die fuenf Linsen und der Anwalt zusammen (25.552) |
| 45 | 33.714 | mehr als das Vierfache von `lehren.md` (8.405) |
| 39 (blockierte Domains) | 22.133 | |
| 51 | 13.210 | |

Formal ist die Datei mit 51 Zeilen nur knapp ueber dem Limit von 30. Tatsaechlich
meldet ein Lesevorgang **92.311 Tokens** — und laut CLAUDE.md liest der Rechercheur
diese Datei zu Beginn *jedes* Laufs. Bei 43 Laeufen sind das mindestens 3,97 Mio.
Tokens allein fuer den Erstabruf; ab dem zweiten Turn liegt die Datei im Kontext und
wird mitgetragen, also ist der wahre Anteil ein Vielfaches davon. Der Rechercheur
verbraucht 82,5 Mio. der 131,9 Mio. Tokens der ganzen Woche — **62 %**.

## Warum es passiert

Die Regel in `CLAUDE.md:113` und `notizen/VORLAGE.md:7` lautet „Hoechstens 30 Zeilen".
Sie misst die falsche Groesse und belohnt damit genau das Verhalten, das sie verhindern
soll: **Zusammenziehen senkt die Zeilenzahl, Streichen senkt sie auch — aber
Zusammenziehen kostet nichts.** Zeile 3 des Logbuchs sagt das offen:

> „Am 2026-08-28 von 213 auf Regelmass zusammengezogen"

213 Zeilen wurden zu 51, ohne dass ein Eintrag entfiel. Was danach neu hinzukam, hing
sich an bestehende Zeilen an — deshalb heisst ein Eintrag heute „Achtzehnte Erstfrage"
und traegt in sich noch „Zweiter Griff desselben Laufs", „Dritter", „Vierter". Die
uebrigen sechzehn Rollen haben dieselbe Regel und liegen alle unter 5.500 Zeichen; der
Unterschied ist nicht Disziplin, sondern dass nur der Rechercheur oft genug lief, um
das Schlupfloch zu finden.

## Der Vorschlag

Die Regel von Zeilen auf Zeichen umstellen, an beiden Stellen wortgleich.

`CLAUDE.md:113` — statt

> Hoechstens 30 Zeilen; ist es voll, streichst du den schwaechsten Eintrag

kuenftig

> Hoechstens **12.000 Zeichen** (`wc -c notizen/<deine-rolle>.md`). Ist es voll,
> streichst du den schwaechsten Eintrag **ganz**. Zusammenziehen zaehlt nicht als
> Streichen: Ein Beleg, der eine Zeile laenger macht, gehoert in deine
> `research/`-Datei, nicht ins Logbuch.

`notizen/VORLAGE.md:7` bekommt denselben Satz.

Einmalig dazu: Der Rechercheur kuerzt sein Logbuch im naechsten Lauf auf das Limit.
Das verliert nichts — zu jedem der 43 Laeufe existiert eine eigene Datei in
`research/` (41 Stueck), und Zeile 3 des Logbuchs behauptet diese Arbeitsteilung
bereits („verdichtete Eintraege stehen ausfuehrlich in den jeweiligen
`research/`-Dateien"). Sie wird nur nicht durchgehalten.

12.000 Zeichen sind rund 30 Zeilen zu 400 Zeichen, also das, was die Regel gemeint
hat. Das Limit liegt ueber jedem anderen Logbuch der Fabrik und trifft heute
ausschliesslich den Rechercheur.

## Was er kostet und was er spart

**Kosten:** eine Zeile in zwei Dateien, plus ein einmaliger Kuerzungsdurchgang
innerhalb eines ohnehin stattfindenden Rechercheurlaufs. Keine neue Rolle, kein
zusaetzlicher Lauf, kein Skript.

**Ersparnis:** rund 168.000 Zeichen je Rechercheurlauf, entsprechend gut 86.000
Tokens Erstabruf. Bei 43 Laeufen in sieben Tagen ist die Untergrenze 3,7 Mio. Tokens
pro Woche, die Obergrenze ein Vielfaches — je nachdem, wie viele Turns ein Lauf hat.
Diese Zahl steht nicht im Journal, deshalb rechne ich sie nicht aus.

Wichtig fuer die Bewertung: Das spart **kein Geld**. `kontingent.py` sagt es
ausdruecklich — das Abo kostet 200 EUR im Monat, fix, und ein zusaetzlicher Lauf
kostet nichts. Die knappe Ressource ist das 5-Stunden-Fenster: im laufenden 22 Laeufe,
am schwersten Tag 78,9 Mio. Tokens. Der Vorschlag kauft Fensterplatz, nicht Euro.

## Was dagegen spricht

**Der beste Einwand: Dieses Logbuch ist das wertvollste Dokument der Fabrik, und ich
schlage vor, zwei Drittel davon zu loeschen.** Die achtzehn Erstfragen sind teuer
erkauft, jede aus einem eigenen Lauf, und der Rechercheur schreibt zu mehreren, sie
haetten „den Lauf in einem Satz beantwortet". Ein Zeichenlimit kann genau das treffen.
Bisher ist ein einziger Lauf gescheitert (regel-scout), und nicht nachweislich am
Kontingent — ich behebe also ein Problem, das noch keinen Schaden angerichtet hat, mit
einem Eingriff, der Wissen vernichten kann.

Meine Gegenrede, und sie ist nicht vollstaendig: Achtzehn Erstfragen brauchen achtzehn
Zeilen, keine 180.254 Zeichen. Was die Datei traegt, sind die **Belege zu** den
Fragen — Aktenzeichen, Preise, Domainlisten — und die stehen bereits in `research/`.
Das Limit erzwingt die Trennung, die das Logbuch selbst behauptet. Wo ich unsicher
bleibe: Ob der Rechercheur beim Kuerzen die Frage behaelt und den Beleg streicht oder
umgekehrt, entscheidet er, nicht die Regel.

**Zweiter Einwand:** Der Zusammenhang zwischen Logbuchgroesse und den 62 % Tokenanteil
des Rechercheurs ist plausibel, aber nicht gemessen. Er ist auch die Rolle mit den
meisten Laeufen (43) und den meisten Seitenabrufen. Ein Teil der 82,5 Mio. Tokens
gehoert dorthin, nicht ins Logbuch.
