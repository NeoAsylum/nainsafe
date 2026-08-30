---
nr: 0006
titel: Nicht die Scouts aussetzen, sondern die Recherche rationieren — und die Kette eichen
datum: 2026-08-30
status: gueltig
ersetzt: null
ersetzt_durch: null
betrifft: [sensorik, kosten, bewertung]
---

# ADR 0006 — Recherche rationieren, Kette eichen

## Kontext

Die erste volle Betriebswoche endete mit einer Null: 167 Läufe, 434 $ Gegenwert,
224,7 Mio. Tokens, 64 Signale, 46 Recherchen, 15 Ideen — **0 Kandidaten, 0
Gate-Vorlagen, 0 aktive Vorhaben**. Zweite Woche in Folge ohne eine Entscheidung für
den Betreiber.

Drei Vorschläge lagen vor, zwei von Agenten, einer vom Betreiber delegiert:

1. Der Portfolio-Manager: Das Promille aus G7 wird angewendet, wo die Regel es nicht
   verlangt.
2. Der Verbesserer: Acht von zwölf Fit-Filter-Ablehnungen zitieren als Todesgrund eine
   Frage, die der Ideator selbst als entscheidend markiert und offen gelassen hat.
3. Der Portfolio-Manager: Regel-Scout und Markt-Scout aussetzen — `signals/regulation`
   ergab bei 19 Signalen null überlebende Ideen, `signals/market` bei 14 eine.

Der Betreiber hat alle drei ins Ermessen gestellt. Eins und zwei sind umgesetzt wie
vorgeschlagen. **Der dritte ist nachgerechnet und dabei durchgefallen.**

## Warum der dritte Vorschlag nicht trägt

Der Portfolio-Manager hat das richtige Problem gefunden und den falschen Hebel
vorgeschlagen. Die Kosten je Rolle, Stand 2026-08-30:

| Rolle | Läufe | Gegenwert | je Lauf |
|---|---:|---:|---:|
| **rechercheur** | 48 | **217,9 $** | 4,54 $ |
| markt-analyst | 18 | 88,7 $ | 4,93 $ |
| ideator | 11 | 20,3 $ | 1,85 $ |
| regel-scout | 13 | 9,3 $ | 0,72 $ |
| markt-scout | 12 | 8,0 $ | 0,67 $ |

Die beiden Scouts zusammen kosten **17,3 $ — vier Prozent des Gesamtverbrauchs.** Sie
auszusetzen spart fast nichts und schneidet zwei Signalquellen ab, darunter die einzige,
die `zwang` liefert: eine gesetzliche Pflicht mit Stichtag, die höchstbewertete
Dimension der ganzen Bewertung.

Teuer ist nicht der Scout, sondern **die Recherche auf seinem Ergebnis.** Der
Rechercheur ist mit 218 $ die Hälfte des gesamten Verbrauchs, und **41 seiner 46
Ergebnisse stehen auf `rot`** — seit dem 2026-08-29 sogar zehn von zehn. 20
Regulierungssignale à 4,54 $ sind rund 91 $ Recherche für null Ideen. Das Geld liegt
dort, nicht beim Scout.

## Entscheidung

**Die Scouts bleiben. Die Recherche wird rationiert, auf zwei Wegen.**

**Erstens: eine Vorprüfung vor der vollen Recherche.** Der Rechercheur benennt zuerst
die eine Frage, bei deren ungünstiger Antwort das Signal erledigt ist, und beantwortet
sie mit **einer** Suche. Fällt sie ungünstig aus, schreibt er eine Kurzabsage — `ampel:
rot`, `vorpruefung: <die Frage>`, fünf Zeilen Begründung — und ist fertig. Das ist
dieselbe Logik, die der Verbesserer für den Ideator vorgeschlagen hat, angewandt auf die
teuerste Rolle der Fabrik.

**Zweitens: Reihenfolge nach beobachtetem Ertrag statt nach Datum.** Von den vier
`gelb`-Recherchen kamen **zwei aus `signals/modelle`** — einer Quelle mit gerade zwei
Signalen. Regulation lieferte bei 20 Signalen eine, market bei 15 eine, pain und tech
bei je vier keine. Die Reihenfolge lautet deshalb: `modelle`, `pain`, `market`,
`regulation`, `tech`.

Das ist eine kleine Stichprobe und damit eine Wette, keine Wahrheit — aber eine
begründete: Ein Modellsignal bringt den Beleg, dass jemand zahlt, schon mit. Genau die
Frage, an der hier alles stirbt. Ein Regulierungssignal bringt dagegen eine Pflicht, die
öffentlich ist und die der Wettbewerb genauso lange kennt wie wir.

## Die Eichung der Kette

Der eigentliche Grund für diesen ADR steht nicht in den Kosten. Jede Stufe dieser Fabrik
hat „nein" als Vorgabewert: Rechercheur 89 % `rot`, Fit-Filter 15 von 15 abgelehnt,
Angriffslinsen mehrheitlich `widerlegt`. Das ist so gebaut und richtig so — aber es
heißt, dass niemand sagen kann, ob „0 Kandidaten" bedeutet *es gab keine gute Idee* oder
*es kommt keine durch*.

Die Kette ist nie gegen einen bekannten Fall geeicht worden. Deshalb gibt es ab jetzt
**Eichideen**: Ideen mit bekannter Antwort, die durch dieselbe Kette laufen wie echte.

- `ideas/9001-eichung-muss-durchkommen.md` — erfüllt alle neun Grenzen, trägt die
  Schwelle mit Faktor zwei, hat einen belegten Kanal. **Muss `kandidat` werden.**
- `ideas/9002-eichung-muss-sterben.md` — rechnet mit 60.900 € weit über die Schwelle,
  großes Segment, offener Kanal, Zahlungsgrund `zwang`, und bewertet trotzdem einen
  konkreten Einzelfall anhand rechtlicher Vorgaben. **Muss an G5 sterben.**

Beide tragen `typ: eichung` und sind in ihrem eigenen Text als Messwerkzeug
gekennzeichnet; ihre Zahlen sind ausdrücklich **gesetzte Prämissen, keine
recherchierten Belege**. Das ist kein Verstoß gegen „keine erfundenen Zahlen": Eine
Eichung misst nicht die Welt, sondern das Messgerät, und dafür müssen die Eingangswerte
bekannt sein statt wahr.

`repo.ideen()` blendet sie aus, damit sie keine Quote verfälschen; der Fit-Filter sieht
sie trotzdem, weil er selbst nach `status: entwurf` sucht. Genau sein Urteil wird
gemessen.

Vier mögliche Ergebnisse, und alle vier sind verwertbar:

| A (muss passieren) | B (muss sterben) | Befund |
|---|---|---|
| kandidat | abgelehnt an G5 | Die Kette arbeitet. „0 Kandidaten" heißt: keine gute Idee gefunden. |
| abgelehnt | abgelehnt | Die Kette ist zu scharf. Die Begründung bei A nennt die Regel. |
| kandidat | kandidat | Die Kette ist zu weich — eine gute Rechnung schlägt eine harte Grenze. |
| abgelehnt | kandidat | Die Kette urteilt nicht, sie würfelt. |

## Was das nicht heißt

Die Eichung ersetzt keine Idee. Sie sagt nichts darüber, ob die Fabrik je einen
tragfähigen Kandidaten findet — nur, ob sie einen erkennen würde.

Und sie ist kein Dauerzustand: Zwei Eichideen im Bestand sind Messwerkzeug. Nach der
Messung bekommen sie einen Endstatus und bleiben liegen, damit die nächste Änderung an
`grenzen.md` gegen dieselben zwei Fälle geprüft werden kann. Gelöscht wird nichts
(Hausregel 3).
