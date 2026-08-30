# Verbesserungsvorschlag KW 35 (zweiter Lauf, 2026-08-30)

## Die Beobachtung

**Acht der zwoelf Fit-Filter-Ablehnungen zitieren als Todesgrund eine Frage, die der
Ideator im Entwurf selbst als die entscheidende markiert und unbeantwortet gelassen
hat.** Wortlaut aus den `ablehnungsgrund`-Zeilen:

| Idee | Grenze | Der Fit-Filter ueber den Entwurf |
|---|---|---|
| 0003 | G6 | „Die vom Ideator selbst als entscheidend markierte Abgrenzung […] traegt voraussichtlich nicht" |
| 0004 | G4 | „Der Ideator benennt diesen Punkt selbst als den, an dem die Idee vermutlich kippt." |
| 0006 | G3 | „Der Ideator benennt G3 selbst als die Frage, bei deren unguenstiger Antwort die Idee […] tot ist." |
| 0007 | G5 | „Der Ideator stellt die Frage selbst und laesst sie offen; bei Unsicherheit wird abgelehnt." |
| 0008 | G3 | „Der Ideator stellt genau diese Frage und laesst sie offen; bei Unsicherheit wird abgelehnt." |
| 0013 | G7 | „der Ideator markiert diese Frage selbst als die vor allen anderen zu klaerende" |
| 0014 | G7 | „Das ist die dritte offene Frage des Entwurfs, und sie steht vor der Marge" |
| 0015 | G7 | „der Entwurf nennt das selbst die Frage, ohne die nichts geht" |

Der Ideator kennzeichnet sie sogar mit Vorrang: „**Besetzung, entscheidend**" (0004),
„**Erste und wichtigste Frage**" (0008), „**Zuerst zu klaeren, weil die ganze Idee daran
haengt**" (0006), „**Das ist die G7-Frage vor allen anderen**" (0014).

Mindestens fuenf der acht Fragen sind mit **einem** Abruf zu entscheiden — „gibt es
bereits einen Vergleich 2026?" (0008), „wie viele Anbieter loesen genau das?" (0004),
„stellen die Laender dafuer schon einen kostenlosen Online-Dienst?" (0014). Die letzte
brauchte nicht einmal eine Suche: Die Antwort stand seit dem 2026-08-29 im Repo, in
`ideas/0012-asbestanzeige-je-baustelle.angriffe/vertrieb.md` (Hamburg, gebuehrenfrei,
seit Jahren) — derselbe Beleg, mit dem der Fit-Filter dann 0015 erschlagen hat.

Ergebnis der Kette: 15 Ideen, 12 abgelehnt, 3 widerlegt, **null Kandidaten**. Der
Fit-Filter lief am 2026-08-29 und am 2026-08-30 leer, der Ideator dreimal in Folge.

## Warum es passiert

Weil **drei Dateien versprechen, dass jemand diese Fragen beantwortet, und keine Rolle
es tut.**

1. `vorlagen/idee.md:59` — der Abschnitt **Offene Fragen** soll „konkret genug [sein],
   dass ein Recherche-Agent damit arbeiten kann".
2. `agents/rollen/rechercheur.md:22-25` — „In den bisherigen Ideen stehen Zeilen wie
   *Vermutung, ungeprueft* […] Solche Saetze gehoeren nicht in eine Idee. Sie gehoeren
   zu dir, beantwortet."
3. Das Statusmodell in `CLAUDE.md` kennt aber keinen solchen Schritt:
   `entwurf ──Fit-Filter──> kandidat | abgelehnt`. Der Rechercheur liest laut
   Rollentabelle „ein Signal", nicht eine Idee, und sein Vorgehen beginnt mit „Lies das
   **zugewiesene Signal**". Er arbeitet vor dem Ideator, nie nach ihm.

Die naechste Station nach dem Entwurf ist damit eine Rolle, deren Regel lautet: „**Bei
Unsicherheit lehnst du ab**" (`agents/rollen/fit-filter.md:40`). Ein sauber
aufgeschriebener Zweifel ist deshalb kein Arbeitsauftrag, sondern ein Todesurteil mit
Vorlauf. Der Entwurf enthaelt seine eigene Ablehnung, fertig formuliert.

Der Ideator **hat** WebSearch, und er benutzt es genau richtig — aber nur an einer
Stelle. `agents/rollen/ideator.md:73` steht unter der Ueberschrift „Die wertvollste
Quelle: gescheiterte Ideen" und gilt nur fuer Anwalts-Zuschnitte: „Nennt der Anwalt eine
Frage, von der sein Zuschnitt abhaengt, klaere sie mit WebSearch, bevor du entscheidest.
Genau eine Frage je Vorschlag, die blockierende." Wo die Regel greift, wirkt sie, zweimal
belegt in `notizen/ideator.md`: Alltagshilfe — „Zwei Suchen, kein Entwurf, fuenf
Angriffslaeufe gespart"; ezyVet-Verzeichnis — „Ein Abruf entscheidet es". Fuer Ideen aus
Signalen gilt sie nicht, und dort landet die Frage stattdessen in **Offene Fragen**.

## Der Vorschlag

Die Regel aus dem Anwaltsabschnitt loesen und auf **jede** Idee anwenden — zwei Zeilen
in zwei Dateien.

**`agents/rollen/ideator.md`** — den Absatz aus Zeile 73 aus dem Abschnitt „Die
wertvollste Quelle" herausnehmen und als eigenen Punkt in „Vorgehen" setzen, vor dem
Schreiben:

> **Bevor du eine Idee aufschreibst, benennst du die eine Frage, bei deren unguenstiger
> Antwort sie tot ist — und beantwortest sie mit WebSearch oder Grep im Repo.** Genau
> eine je Idee, die blockierende. Faellt die Antwort negativ aus, schreibst du statt der
> Idee einen Logbucheintrag mit dem Befund; das ist ein vollwertiges Ergebnis. Faellt sie
> positiv aus, steht sie belegt in **Belege** — nicht als Frage in **Offene Fragen**.

**`vorlagen/idee.md:59`** — statt

> Was muesste man wissen, um das zu entscheiden? Konkret genug, dass ein Recherche-Agent
> damit arbeiten kann.

kuenftig

> Was hier steht, beantwortet niemand mehr: Naechste Station ist der Fit-Filter, und
> der lehnt bei Unsicherheit ab. Die Frage, an der die Idee **haengt**, gehoert deshalb
> beantwortet nach **Belege**. Hierher gehoert nur, was die Entscheidung nicht traegt.

Damit sagt die Vorlage, was die Fabrik tatsaechlich tut, statt einen Rechercheschritt zu
versprechen, den das Statusmodell nicht enthaelt.

## Was er kostet und was er spart

**Kosten:** ein bis zwei Abrufe je Idee, innerhalb eines ohnehin stattfindenden
Ideatorlaufs. Keine neue Rolle, kein zusaetzlicher Lauf, kein Skript, keine
Statusaenderung. Der Ideator ist mit 1,84 $ je Lauf und 9,6 Mio. Tokens die guenstigste
produktive Rolle (`kontingent.py`, 2026-08-30); selbst eine Verdopplung bliebe ein
Achtel des Rechercheurs.

**Ersparnis, belegt:** je Idee mit negativer Antwort ein Entwurf und eine
Fit-Filter-Pruefung — der Mechanismus ist in `notizen/ideator.md` zweimal nachgewiesen
(Alltagshilfe: fuenf Angriffslaeufe; ezyVet: ein Angriffszyklus).

**Ersparnis, erhofft:** je Idee mit positiver Antwort der Unterschied zwischen
`abgelehnt` und `kandidat`. Den hat die Fabrik in 15 Versuchen kein einziges Mal
erreicht — nicht weil jede Idee schlecht war, sondern weil die entscheidende Frage nie
gestellt und „unbeantwortet" per Regel in „abgelehnt" uebersetzt wurde. Diese Zahl
verspreche ich nicht; sie ist der eigentliche Grund fuer den Vorschlag.

## Was dagegen spricht

**Der beste Einwand: Bei drei der acht haette der Vorabruf nichts geaendert, und ich
verkaufe eine Hoffnung als Ersparnis.** 0003 und 0007 haengen an Rechtsfragen
(§ 2 RDG, § 6 StBerG) — die entscheidet keine Suche, dafuer gibt es die Linse Recht.
0015 brauchte eine Zahl, die nur ueber IFG-Auskunft zu haben ist, also ueber ein
Schreiben nach aussen, das Hausregel 2 verbietet. Dort verbrennt der Ideator kuenftig
zwei Abrufe und schreibt anschliessend dasselbe Nichts. Nachweisbar wirksam ist der
Vorschlag bei fuenf von zwoelf Ablehnungen, nicht bei acht.

**Zweiter Einwand, und er wiegt schwerer:** `CLAUDE.md` warnt ausdruecklich vor genau
dieser Bewegung — „Wer als Ideator anfaengt, Marktdaten zu erheben, produziert eine
zweite Fassung dessen, was der Rechercheur schon geschrieben hat — langsamer und
schlechter." Die Grenze zwischen „eine blockierende Frage" und „Marktrecherche" ist
duenn, und ein Ideatorlauf, der sie ueberschreitet, kostet mehr als er spart. Meine
Gegenrede: Die Schutzklausel steht bereits im Satz („Genau eine Frage je Vorschlag, die
blockierende") und hat in drei Anwendungen nicht gerissen. Der Vorschlag aendert den
Geltungsbereich, nicht die Schranke. Sicher bin ich mir nicht.

**Die Variante, die ich nicht vorschlage, aber nennen muss:** Statt den Ideator suchen zu
lassen, koennte der Rechercheur einen zweiten Auftragstyp bekommen — „beantworte die als
entscheidend markierte Frage aus `ideas/<id>.md`". Das repariert das Versprechen, statt
es zu streichen, und traefe auch die Rechtsfragen. Es kostet aber je Idee einen Lauf der
teuersten Rolle der Fabrik (4,68 $, 46 Laeufe, 85,9 Mio. Tokens), dazu ein Leserecht auf
`ideas/` und eine Aenderung am Nachtlauf. Unter der Zwei-Stunden-Randbedingung halte ich
den billigeren Weg fuer richtig — die Entscheidung liegt beim Betreiber.
