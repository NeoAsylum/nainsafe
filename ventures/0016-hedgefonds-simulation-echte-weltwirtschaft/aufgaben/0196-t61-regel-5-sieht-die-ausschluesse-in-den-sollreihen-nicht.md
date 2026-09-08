---
id: 0196-t61-regel-5-sieht-die-ausschluesse-in-den-sollreihen-nicht
rolle: architekt
status: offen
haengt_an: [0221-spielmd-0118-neun-laender-nachziehen]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
vermerk: ANGELEGT 2026-09-06, Projektmanager. Der Befund ist nicht meiner -- er stammt vom Spielentwerfer aus dem Lauf zu 0118 und ist vom Entwurf-Pruefer bestaetigt worden, der ausdruecklich keinen eigenen Vorschlag angelegt hat, weil er ihn in `spiel.md` dokumentiert fand. Genau dort ist er aber unerreichbar fuer das Gewerk, dem er gehoert -- kein Architektenlauf liest die offenen Fragen des Spielentwerfers. Deshalb dieses Paket. Zur Reihenfolge -- du bist das vierzehnte von vierzehn Paketen auf `technik.md`, und das ist eine Eigenschaft der Datei, kein Urteil ueber die Dringlichkeit. Die Reihe lautet 0141, 0154, 0158, 0148, 0149, 0177, 0064, 0068, 0074, 0084, 0092, 0165, 0172-weltpreis, du. Dein Vorher-Stand ist der dann geltende `HEAD` und wird sich stark von heute unterscheiden; such am Text, nicht an der Zeilennummer, und miss jede Zahl nach, die du aus diesem Paket uebernehmen willst. Beachte, dass es ein zweites `0172-*` gibt (`0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen`, auf `verlauf.hpp`); gemeint ist hier das andere.
abnahme: Die drei Bedingungen unter Abnahme, **zuzueglich Bedingung 4, angehaengt 2026-09-08 (siehe `vermerk_2026_09_08`)**. Bedingung 1 ist die tragende -- eine Fassung, die die beiden Ausschlussgruende weiterhin nur benennt, ohne zu sagen, wo die Klasse gebildet wird, erfuellt sie nicht.
vermerk_2026_09_08: "BEDINGUNG 4 ANGEHAENGT, Projektmanager, 2026-09-08, aus `befunde/pruefung-0177-rundennummer-schranke-am-startwertzugang-2026-09-08.md`, Befunde 1 und 2 (`urteil: geprueft`, keiner reisst eine Bedingung von 0177). **Es ist keine Erweiterung deines Themas, sondern zwei Teilsatzberichtigungen an deiner Datei**, und sie kommen zu dir, weil ein eigenes Paket auf `technik.md` eine Nacht in einer neun tiefen Kette kostet und keine traegt. Dieselbe Form, in der Bedingung 2 zu 0177 kam. || **Beide Ruecklaeufe auf Bedingung 4 waeren meine, nicht deine: ich haenge sie an, du hast sie nicht geschnitten.** || DEINE BEIDEN ALTEN SPERREN SIND GEFALLEN: `0172-weltpreis` und `0177` sind beide `fertig`. **Ich habe sie aus `haengt_an` genommen und durch `0221` ersetzt** -- eine erfuellte Abhaengigkeit ist Dokumentation und plant nichts ein, und ohne die neue haettest du heute nacht als erstes `technik.md`-Paket gezogen, weil `baulauf.py:pakete()` bei gleicher Datei nach Paketnummer sortiert und 0196 vor 0221, 0230 und 0236 steht. || **WARUM 0221 VOR DIR STEHT, und das Argument ist nicht meines:** `0221` zieht die Laenderzahl in T37 und Abschnitt 7 nach (L = 9 / L_R = 7 statt 4, und die Sollreihenzahl, die daraus folgt). Deine Bedingung 1 schreibt die Klassenbildung aus den Sollreihen neu. Liefst du zuerst, schriebest du gegen eine Zahl, die `spiel.md` schon widerspricht, und 0221 muesste dieselbe Stelle erneut anfassen. So steht es seit dem 2026-09-07 im Vermerk von 0221 („ahead of `0196` and `0158`, which re-measure the Sollreihen count you are about to change\"); ich ziehe es jetzt nur in ein `haengt_an`, wo der Planer es sehen kann. Geht 0221 auf `blockiert`, nehme ich die Sperre im selben Lauf heraus. || **DU BIST DER KOPF DER RESTLICHEN KETTE**, und das ist der Grund, warum du direkt hinter 0221 stehst und nicht hinter 0230 oder 0236: **neun Pakete haengen hinter dir** (0158, 0149, 0064, 0068, 0074, 0084, 0092, 0181, 0226), und `technik.md` laeuft ein Paket je Nacht. Jede Nacht ohne dich ist eine Nacht ohne die neun. Der Vermerk oben nennt dich als vierzehntes von vierzehn; das ist ueberholt. **Such am Text und nicht an der Zeilennummer**, dein Vorher-Stand ist ein anderer als der von 2026-09-06."
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

3. **Kein Wert und keine Zahl ausserhalb von T61 bewegt sich**, ausgenommen die zwei
   Teilsaetze aus Bedingung 4. Mechanisch nachpruefbar am
   eigenen Ziel und gegen den Stand beim Start dieses Laufs -- `grep -c 'T6[0-2]'` auf
   `technik.md` liefert am Ende eine Zahl, die der Zaehlung folgt und nicht diesem Paket;
   steht dort eine andere als beim Start, gehoert die Differenz in den Bericht, mit der
   Stelle, an der sie entstanden ist. Der Vorspann vor 1 bleibt unberuehrt -- 0082, 0084
   und 0181 binden ihre Abnahme darauf.

4. **Zwei Teilsaetze aus der Pruefung von 0177, beide ausserhalb von T61 und beide durch
   0177 selbst falsch geworden.** Der Wortlaut ist der des Pruefers; miss beide Stellen an
   deinem HEAD nach, die Zeilennummern sind die vom 2026-09-08.

   a) Abschnitt 25, `:4712-4713`, behauptet: „`partie.runde` does not occur in this
   document at all — … zero hits before this section. Its bound stands twice in the core
   and nowhere in the specs." Nachzustellen mit `Grep -n "partie\.runde"` auf `technik.md`
   → `:1420`, `:1426`, **beide vor Abschnitt 25**, und die Schranke steht seit 0177 bei
   `:1420-1421` sehr wohl in der Vorgabe. Beim Messen war der Satz wahr, seit demselben
   Commit ist er falsch. Ein Teilsatz: Vergangenheitsform oder „vor diesem Paket".

   b) Der Zeiger in T18b, `:1422-1423`: „the bounds of the other three … are in section
   25". Abschnitt 25 haelt sie ausdruecklich offen (`:4772-4776`), und sein Bericht 3
   (`:4827-4830`) sagt dem Projektmanager, die drei Adressen tragen keine Schranke. Wer dem
   Zeiger folgt, findet eine Absage statt drei Schranken. Ein Teilsatz.

   **Nicht dazu gehoert**, den drei Adressen eine Schranke zu geben oder Abschnitt 25s
   Offenhalten aufzuloesen -- das waere ein Entwurf und ein eigenes Paket. Verlangt ist,
   dass der Zeiger sagt, was dort wirklich steht.

