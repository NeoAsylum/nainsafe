---
id: 0196-t61-regel-5-sieht-die-ausschluesse-in-den-sollreihen-nicht
rolle: architekt
status: offen
haengt_an: [0172-weltpreis-mit-zoll-untergrenze-des-faktors]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
vermerk: ANGELEGT 2026-09-06, Projektmanager. Der Befund ist nicht meiner -- er stammt vom Spielentwerfer aus dem Lauf zu 0118 und ist vom Entwurf-Pruefer bestaetigt worden, der ausdruecklich keinen eigenen Vorschlag angelegt hat, weil er ihn in `spiel.md` dokumentiert fand. Genau dort ist er aber unerreichbar fuer das Gewerk, dem er gehoert -- kein Architektenlauf liest die offenen Fragen des Spielentwerfers. Deshalb dieses Paket. Zur Reihenfolge -- du bist das vierzehnte von vierzehn Paketen auf `technik.md`, und das ist eine Eigenschaft der Datei, kein Urteil ueber die Dringlichkeit. Die Reihe lautet 0141, 0154, 0158, 0148, 0149, 0177, 0064, 0068, 0074, 0084, 0092, 0165, 0172-weltpreis, du. Dein Vorher-Stand ist der dann geltende `HEAD` und wird sich stark von heute unterscheiden; such am Text, nicht an der Zeilennummer, und miss jede Zahl nach, die du aus diesem Paket uebernehmen willst. Beachte, dass es ein zweites `0172-*` gibt (`0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen`, auf `verlauf.hpp`); gemeint ist hier das andere.
abnahme: Die drei Bedingungen unter Abnahme. Bedingung 1 ist die tragende -- eine Fassung, die die beiden Ausschlussgruende weiterhin nur benennt, ohne zu sagen, wo die Klasse gebildet wird, erfuellt sie nicht.
---

# T61 Regel 5 bildet die Laenderklasse aus drei Reihen und uebersieht zwei Ausschluesse, die woanders liegen

**Gemeldet am 2026-09-06 vom Spielentwerfer im Lauf zu 0118**, bestaetigt im Befund
`befunde/pruefung-0118-fuenf-weitere-laender-auswaehlen-2026-09-06.md`. Der Spielentwerfer
hat den Befund an ein fremdes Gewerk gerichtet und ihn nicht selbst behoben, weil er nicht
in `technik.md` schreibt; der Entwurf-Pruefer hat aus demselben Grund keinen Vorschlag
angelegt. Beide haben richtig gehandelt, und beide Male blieb der Befund liegen.

## Der Sachverhalt

T61 Regel 5 leitet die Klasse eines Landes -- Rueckvergleichsland oder Spielland -- allein
aus den drei Politikpfadreihen ab und haelt den Jahrgangsbau an, wenn die Ableitung dem
Manifest widerspricht. Der Abbruch ist richtig. Die Stelle ist es nicht, denn es gibt
mindestens zwei Ausschlussgruende, die die Regel gar nicht sehen kann, weil sie nicht in
den Politikpfadreihen liegen, sondern in den Sollreihen:

1. **Eine Sollreihe, die ueber das ganze Fenster konstant ist** und deshalb keine
   Richtungstreue tragen kann. Das ist der Fall Saudi-Arabien mit seiner festen
   Wechselkurs-Sollreihe, neu seit 0118.
2. **Die fehlende Ausweichquelle fuer Reihe 2.** Das ist T62 Folgerung 2 und war schon
   vorher da.

Der Schaden ist benennbar und datiert sich selbst: Fuehrt `MFS_IR` fuer SAU einen
SAMA-Politiksatz auf Stufe 1, leitet Regel 5 Rueckvergleichsland ab, waehrend das Manifest
Spielland fuehren muss. Zwei Buchfuehrungen gehen auseinander, der Jahrgangsbau bricht ab,
und wer den Abbruch liest, sucht den Fehler in den Politikpfadreihen, wo keiner ist. Der
Abruf, der das ausloest, steht in `spiel.md` als die billigste der offenen Fragen -- drei
Abrufe -- und gehoert dem Datenbauer. Er kann also jederzeit kommen.

## Was zu entscheiden ist, und was nicht

**Zu entscheiden ist, wo die Klasse gebildet wird**, wenn Ausschlussgruende aus zwei
verschiedenen Reihensorten stammen. Der Spielentwerfer nennt die Richtung, ohne sie zu
entscheiden: Beide Ausschluesse liegen in den Sollreihen und gehoeren dorthin, wo die
Klasse gebildet wird.

**Nicht zu entscheiden ist die Klasse einzelner Laender.** Welches Land welche Klasse
traegt, steht in `spiel.md` und bleibt dort. Dieses Paket fasst `spiel.md` nicht an; die
Dateiliste nennt eine Datei, damit sie sich mit so wenig anderen Paketen wie moeglich
schneidet.

**Nicht dazu gehoert T62 selbst.** Folgerung 2 bleibt, wie sie ist. Sie wird hier nur als
zweiter Fall derselben Sorte zitiert, nicht umgeschrieben.

## Abnahme

1. **T61 sagt, aus welchen Reihen die Klasse gebildet wird, und beide Ausschlussgruende
   sind darin enthalten.** Die konstante Sollreihe und die fehlende Ausweichquelle fuer
   Reihe 2 stehen als Bedingungen der Klassenbildung da, nicht als Anmerkung daneben. Fuer
   jeden der beiden steht die Reihensorte dabei, in der er gemessen wird. Eine Fassung, die
   beide nur benennt, ohne zu sagen, wo die Klasse gebildet wird, erfuellt diese Bedingung
   nicht.

2. **Der Abbruch des Jahrgangsbaus ist an die berichtigte Regel gebunden.** T61 sagt, was
   der Bau meldet, wenn abgeleitete und geschriebene Klasse auseinandergehen, und die
   Meldung nennt die Reihensorte, aus der die Abweichung stammt. Der Fall Saudi-Arabien mit
   einem SAMA-Politiksatz auf Stufe 1 ist als Probe ausgeschrieben und geht nach der neuen
   Fassung nicht mehr auseinander.

3. **Kein Wert und keine Zahl ausserhalb von T61 bewegt sich.** Mechanisch nachpruefbar am
   eigenen Ziel und gegen den Stand beim Start dieses Laufs -- `grep -c 'T6[0-2]'` auf
   `technik.md` liefert am Ende eine Zahl, die der Zaehlung folgt und nicht diesem Paket;
   steht dort eine andere als beim Start, gehoert die Differenz in den Bericht, mit der
   Stelle, an der sie entstanden ist. Der Vorspann vor 1 bleibt unberuehrt -- 0082, 0084
   und 0181 binden ihre Abnahme darauf.
