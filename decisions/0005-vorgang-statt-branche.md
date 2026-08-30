---
nr: 0005
titel: Der Markt wird nach Vorgang geschnitten, nicht nur nach Branche
datum: 2026-08-30
status: gueltig
ersetzt: null
ersetzt_durch: null
betrifft: [sensorik, ideen, bewertung]
---

# ADR 0005 — Vorgang statt Branche

## Kontext

ADR 0004 hat die Größenschwelle eingeführt und den Suchraum um englischsprachige Märkte
und Endkunden erweitert. Die ersten drei englischsprachigen Marktprofile kamen in
derselben Nacht zurück, und alle drei standen auf `potenzial: gering` — obwohl die
Segmente 43.500 bis 134.000 Betriebe groß sind. Das Größenproblem war gelöst und das
Ergebnis dasselbe.

Der Betreiber hat daraufhin die Diagnose an der Wurzel korrigiert:

> Ich glaube die Marktsegmente sind falsch. Wir suchen nach Märkten für
> Endkundenprodukte und versuchen dann darauf unsere Leistung abzustimmen, dabei löst
> die meiste Software wie Abrechnungssoftware oder Terminbuchungssoftware oder auch
> Mailsoftware jeweils Prozessthemen und ist insofern branchenübergreifend.

Das ist überprüfbar, und die Fabrik hatte die Daten dafür längst. Jedes Marktprofil nennt
im Feld `handarbeit` den teuersten wiederkehrenden Vorgang seiner Branche. Achtzehn
Profile nebeneinandergelegt:

| Vorgang | Branchen | Betriebe zusammen |
|---|---|---:|
| Wiederkehrende Prüfung mit Frist und Nachweispflicht | Dachdecker, Aufzug, Kälteanlagen, Schädlingsbekämpfer, Spielplätze, Facility | 65.433 |
| Leistungsnachweis gegen einen Kostenträger | Pflege, Hebammen, Physiotherapie | 74.662 |
| Behördenmeldung je Vorgang mit Formular und Frist | Elektro, Dachdecker, SHK | rund 108.000 |
| Wiederkehrende Verbrauchsabrechnung mit Zählerablesung | Camping, Hausverwaltung | 27.800 |

Sechs Segmente, ein Vorgang. Jedes einzelne war als `potenzial: gering` abgelegt, in der
Mehrzahl mit der Begründung „zu klein". **Keines davon ist klein.** Der Zuschnitt war das
Problem, nicht der Markt — und die Begründung „zu klein" war in diesen Fällen schlicht
falsch.

Der Mechanismus dahinter erklärt zugleich den zweiten Befund aus ADR 0004, dass jede
Nische bereits von zugeschnittenen Anbietern besetzt ist: Wer nach Branche sucht, findet
je Branche einen zu kleinen Markt **und** je Branche einen Nischenanbieter, der ihn schon
bedient. Beide Beobachtungen sind dieselbe Beobachtung, von zwei Seiten.

## Entscheidung

**Der Markt wird nach zwei Achsen geschnitten.** Die Branche bleibt eine davon; der
**Vorgang** kommt als zweite dazu, und er ist meist die größere.

Dafür gibt es eine neue Rolle, den **Prozess-Analysten**
(`agents/rollen/prozess-analyst.md`). Sein Rohstoff ist nicht das Web, sondern die
bereits bezahlten Marktprofile: Er liest alle `signals/maerkte/*.md`, gruppiert deren
`handarbeit`-Felder und beantwortet sieben Fragen zu **einem** Vorgang. Ergebnis ist ein
Prozessprofil unter `signals/prozesse/`.

Der Markt-Analyst bleibt unverändert bestehen. Die beiden Rollen stehen nicht in
Konkurrenz: **Die Branchenprofile sind der Sensor, die Prozessprofile der Verdichter.**
Jedes neue Marktprofil liefert ein weiteres `handarbeit`-Feld und macht die Achse darüber
genauer. Die vertikale Arbeit ist damit rückwirkend nicht mehr Ausschuss, sondern
Datengrundlage.

## Das Urteil des Prozess-Analysten

Zwei der sieben Fragen entscheiden fast allein, und sie ergeben eine Tabelle:

| horizontales Werkzeug | vertikale Anbieter | Befund |
|---|---|---|
| löst es gut | egal | **tot** — der Vorgang ist bedient, der Preisboden steht |
| keines | keine | **Warnsignal** — vermutlich löst es niemand, weil es kein Problem ist |
| keines | einer, groß | **tot** — er wird die Vereinigung selbst heben |
| keines | mehrere, je Branche | **Fund** — gleicher Vorgang, branchenweise gelöst, Vereinigung unbesetzt |

Die letzte Zeile ist der Zweck der Rolle. Die dritte ist die, die man am ehesten
übersieht.

Der Einwand gegen die ganze Umstellung steht in derselben Tabelle, Zeile eins: **Die
großen horizontalen Kategorien sind die umkämpftesten Softwaremärkte überhaupt.**
Abrechnung, Terminbuchung und Mailversand — genau die drei Beispiele des Betreibers —
sind besetzt, und zwar gut. „Branchenübergreifend" ist deshalb kein Fund, sondern nur
eine andere Suchrichtung. Der Fund liegt dort, wo ein Vorgang branchenübergreifend
**gleich** ist, aber ausschließlich branchenspezifisch **gelöst** wird.

## Zwei harte Bedingungen

Die Vereinigung ist keine Rechenerlaubnis. In `grenzen.md`, G7, hängen zwei Bedingungen
daran:

1. **Der Vorgang muss derselbe sein, nicht ein ähnlicher.** Ist die branchenspezifische
   Schale größer als der gemeinsame Kern, sind es fünf Vorgänge mit einem Oberbegriff.
   Ein Werkzeug, das sechs Branchen halb bedient, verliert gegen sechs Werkzeuge, die je
   eine ganz bedienen. Der Kern gehört programmiert, die Schale konfiguriert.
2. **Ein Kanal muss mehrere Branchen zugleich erreichen** — eine Suchanfrage, die alle
   stellen; ein Werkzeug, an das alle andocken; eine Pflicht, zu der alle dasselbe
   googeln. Fünf Branchenverbände sind kein Kanal, sondern fünf Vertriebsprobleme.

Dazu die Formvorschrift: Wer über Branchen hinweg zählt, **zählt sie einzeln auf**, jede
mit Betriebszahl und Quelle. Eine Vereinigung ohne Aufzählung ist eine Behauptung und
zählt nicht — dieselbe Regel wie für „weltweit verfügbar".

## Folgen

- `agents/rollen/prozess-analyst.md` — neue Rolle, sieben Fragen, Befundtabelle.
- `quellen.yml` — Block `prozesse` mit acht Vorgängen. Sieben sind aus den vorhandenen
  Marktprofilen abgeleitet und im Repo belegt; der achte (*Vorgangsdokumentation per
  Diktat*) steht als **Kontrollprobe** auf der Liste, weil er nachweislich besetzt ist —
  allein bei Tierarztpraxen von zwölf KI-Diktatanbietern. Ein Profil, das ihn sauber als
  `tot` begründet, eicht das Urteil der Rolle.
- `grenzen.md` G7 — Abschnitt *Die Kundenzahl darf über Branchen hinweg zählen*.
- `CLAUDE.md` — die zwei Achsen im Abschnitt *Wonach gesucht wird*, neue Zeile in der
  Rollentabelle.
- `agents/rollen/ideator.md` — Kern und Schale trennen, Branchen einzeln aufzählen.
- `agents/nachtlauf.py` — `PROZESS_MAX = 2` je Nacht; `MARKT_MAX` von 3 auf 2 gesenkt,
  damit der Lauf nicht wächst.
- `agents/repo.py` — `vorgangsliste()` und `offene_prozesse()`. Der Zeilenleser für
  Aufzählungsblöcke ist als `_liste()` herausgezogen und wird von beiden Achsen genutzt.

## Was das nicht heißt

Die sechzehn `gering`-Urteile werden nicht zurückgenommen. Sie sind als
**Branchen**urteile richtig: In keinem dieser Segmente allein liegt ein tragfähiges
Produkt. Falsch war nur die Verallgemeinerung, die niemand ausgesprochen hat — dass damit
auch der Vorgang erledigt sei, den sie beschreiben.

Und die Umstellung ist keine Zusage, dass die Vereinigung trägt. Sie sagt nur, dass die
Fabrik die Frage bisher nicht gestellt hat.
