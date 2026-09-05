---
typ: pruefung
paket: 0122-strichrechnung-sperre-in-sperrehpp
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: beide Haelften an fuenf Wegwerfbaeumen gefahren -- der unveraenderte Baum ist in beiden Profilen 14 von 14 gruen und mit wie ohne Sperrzeile objektgleich, der Rueckfall auf eine eigene Fassung von plus und getrennt von minus bricht je mit "attempt to use poisoned" ab, und dieselbe Einspeisung ohne Sperrzeile laeuft gruen durch
befunde: 0
---

# 0122 erfuellt sein Abnahmekriterium

Null Befunde gegen das Paket. Zwei Beobachtungen liegen **ausserhalb** seines
Dateiverzeichnisses und stehen unten unter ihrer eigenen Ueberschrift; die zweite ist
als Paket `0134-sperrebindung-jeder-kernquelle` vorgeschlagen.

## Der gepruefte Stand

Der Inhalt an `HEAD` entscheidet, nicht der Commit-Betreff. Die Sperrzeile steht dort:
die letzte Zeile von `kern/include/kern/sperre.hpp` lautet
`#pragma GCC poison __builtin_add_overflow __builtin_sub_overflow`. Sie ist zusammen
mit einem 45-Zeilen-Absatz im Kopf in den Baum gekommen; die Aenderung an dieser Datei
umfasst nichts sonst, und es ist die einzige angefasste Datei aus der `dateien`-Liste
des Pakets.

Fuenf Baeume, alle unter `/tmp/claude-1000/kp0122/` und damit ausserhalb des Repos, je
aus `git archive HEAD` frisch ausgepackt und einzeln konfiguriert. Die Bauzeile ist die
von `baulauf.py`, das Profil kommt zusaetzlich dazu:

    cmake -S . -B <bau> -DCMAKE_BUILD_TYPE=RelWithDebInfo \
          -DCMAKE_CXX_FLAGS="-fwrapv -fno-fast-math" -DFABRIK_SANITIZER=<ON|OFF>
    cmake --build <bau> --parallel
    ctest --test-dir <bau> --output-on-failure

## Bedingung 1 -- vergiftet sind beide Bezeichner, jeder einzeln nachgewiesen

Nicht nur der Dateiinhalt, sondern zwei getrennte rote Laeufe. Im Baum **B** ist
`using festkomma::plus;` entfernt und im anonymen Namensraum von `kern/src/werte.cpp`
eine eigene Fassung von `plus` mit `__builtin_add_overflow` eingesetzt; im Baum **D**
dasselbe mit `minus` und `__builtin_sub_overflow`. Beide brechen ab, und die Meldung
ist die verlangte:

    error: attempt to use poisoned '__builtin_add_overflow'      (Baum B)
    error: attempt to use poisoned '__builtin_sub_overflow'      (Baum D)

Beide Male zeigt die Folgemeldung `note: poisoned here` auf die Sperrzeile, und zwar
auf **verschiedene Spalten** derselben Zeile -- 20 fuer den ersten Bezeichner, 43 fuer
den zweiten. Die eine Zeile traegt also wirklich beide Sperren und nicht eine, die
zufaellig beide Faelle faengt. Der Abbruch trifft `kern` und `kern_geprueft`
gleichermassen.

## Bedingung 2 -- der unveraenderte Baum bleibt in beiden Profilen gruen

Baum **A**, unveraendert aus `HEAD`:

| Profil | Ergebnis |
|---|---|
| `FABRIK_SANITIZER=ON` | 14 von 14 Proben bestanden |
| `FABRIK_SANITIZER=OFF` | 14 von 14 Proben bestanden |

Das ist die Positivkontrolle, ohne die der rote Nachweis nichts wert waere: Eine
Sperre, die alles verbietet, saehe im Negativtest genauso aus.

**Haerter als gruen: die Sperrzeile kostet kein Bit.** Im selben Baum, mit denselben
Pfaden und demselben Bauverzeichnis, habe ich die Sperrzeile entfernt, neu gebaut, die
acht Objektdateien von `kern` gehasht, die Zeile wieder eingesetzt und erneut gehasht.
Alle acht Pruefsummen sind vorher und nachher identisch. Dass dabei wirklich neu
uebersetzt wurde und nicht nur ein Zeitstempel gestimmt hat, ist mitgemessen: Die
Aenderung an `sperre.hpp` loest 18 Uebersetzungsschritte aus, also jede
Uebersetzungseinheit, die den Kopf bindet.

Damit ist die Frage nach dem Determinismus fuer dieses Paket abschliessend beantwortet,
und nicht durch ein Argument, sondern durch eine Messung: Das Paket aendert die
erzeugte Rechnung an keiner Stelle. Es kann folglich weder eine Rueckkopplung oeffnen
noch die Zustandsausgabe veraendern noch einen Zahlenrand verschieben -- die drei
uebrigen Fragen meiner Rolle laufen hier ins Leere, und das ist ihr Ergebnis.

Der Grund, warum `festkomma.hpp` selbst nicht mit abbricht, ist die Reihenfolge und
nichts anderes: Die Vergiftung ist rein lexikalisch und wirkt ab ihrer Zeile. In
`werte.cpp` steht `kern/festkomma.hpp` im Include-Block **ueber** `kern/sperre.hpp`,
ist also fertig gelesen, bevor die Sperre gilt. Der Rumpf von `festkomma::plus` ist zu
diesem Zeitpunkt bereits Token, kein Text mehr.

## Bedingung 3 -- "wo sie heute gruen durchlaeuft"

Baum **C** traegt dieselbe Einspeisung wie Baum B, aber mit der Sperrzeile wieder
herausgenommen -- der Stand also, den das Paket vorgefunden hat. Er uebersetzt ohne
einen einzigen Fehler und besteht 14 von 14 Proben. Das ist die Gegenprobe, die
ausschliesst, dass die Einspeisung selbst den Abbruch verursacht: gleiche Einspeisung,
einzige Differenz die Sperrzeile, rot gegen gruen.

## Wie weit die Sperre reicht -- gemessen, nicht angenommen

Drei Grenzen, weil eine Sperre ohne benannte Reichweite gelesen wird, als reiche sie
ueberall hin:

1. **Genau die zwei Bezeichner.** Eine Uebersetzungsprobe gegen `kern/sperre.hpp` mit
   `__builtin_saddll_overflow` und `__builtin_ssubll_overflow` laeuft durch; nur
   `__builtin_add_overflow` in derselben Datei schlaegt an. Das ist kein Mangel: T7
   Massnahme 4, Punkt 2 nennt genau die beiden Bezeichner, die vergiftet sind, und die
   Sperre bildet die Vorgabe wortgleich ab.
2. **Nur Uebersetzungseinheiten, die den Kopf binden.** Das sind heute 18 -- die acht
   Quellen unter `kern/src` und die zehn Proben unter `kern/test`. Der Pruefstand
   bindet `sperre.hpp` nirgends und liegt damit ausserhalb; fuer ihn ist der im Kopf
   genannte Nachweis eine Textsuche und keine Uebersetzungssperre. Der Kopf sagt das
   auch so -- er schreibt den Suchbefehl hin und nennt ihn nicht anders.
3. **Nicht die Operatoren.** Die Aenderung fuegt eine einzige Pragma-Zeile hinzu und
   keine Sperre fuer `*`, `+` oder `-`. Die Abgrenzung zu Massnahme 4.3 und zu Paket
   0074, auf die der Projektmanager ausdruecklich hingewiesen hat, ist eingehalten.

## Die Behauptungen des neuen Kopftextes, einzeln nachgeschlagen

Der Absatz stellt zwei mechanische Nachweise auf. Beide habe ich im Wortlaut gefahren,
in einem frisch ausgepackten Baum ohne Bauverzeichnisse:

- Die rekursive Namenssuche nach den beiden Ueberlaufbausteinen ueber `kern/` und
  `pruefstand/` liefert genau zwei Dateien, `kern/include/kern/sperre.hpp` und
  `kern/include/kern/festkomma.hpp` -- wie angekuendigt.
- Die Zaehlung der Include-Zeile ueber die acht Quellen unter `kern/src` liefert
  ueberall den Wert 1 -- wie angekuendigt.

Dazu die Einbauregel, auf der die ganze Begruendung ruht -- die Reihenfolge ist die
Ausnahme: In allen 18 Uebersetzungseinheiten ist `kern/sperre.hpp` der **letzte**
`#include` und kommt genau einmal vor. Kein Verstoss.

Und die Belegstellen des neuen Textes sind nicht bloss mitgelaufen, sondern wirklich
geprueft. Dass der Belegstellenriegel diese Kopfdatei liest, habe ich nicht geglaubt,
sondern rot gemacht: eine eingespeiste Belegstelle in der gepruefen Form --
Dokumentname, Schluesselwort und eine Ueberschrift in Anfuehrung, die es in der
Zieldatei nicht gibt -- macht den Riegel rot und nennt `kern/include/kern/sperre.hpp`
als zitierende Datei. Ein erster Versuch mit einer blossen Gliederungsziffer blieb
gruen; das ist keine Luecke des Riegels, sondern genau die Sorte Fundstelle, die er
benannt uebergeht.

## Zwei Beobachtungen ausserhalb des Pakets

**Der Commit-Schnitt folgt wieder nicht dem Paket -- zweiter Beleg.** Der Commit mit
dem Betreff dieses Pakets enthaelt `sperre.hpp` **nicht**. Die Datei ist in einem
Commit gelandet, der den Betreff eines Datenbauer-Laufs traegt, zusammen mit einer
Aenderung an `werkzeugkette.cmake`, die dem Thema der leeren Fundmeldung gehoert und
nicht diesem Paket. Der Commit unter dem Betreff von 0122 enthaelt dafuer zwei fremde
Logbuecher und zwei fremde Paketdateien. Das ist genau der Sachverhalt, den
`0121-commit-schnitt-folgt-nicht-dem-paket` beschreibt und der dort `blockiert` steht;
die Abhilfe liegt seit demselben Tag als `0131-baulauf-commit-nur-paketdateien`
daneben. Ein zweiter Beleg gehoert in einen dieser beiden Vorgaenge und nicht in
ein drittes Paket.

Waehrend ich diesen Befund schrieb, ist er selbst zum dritten Beleg geworden: Ein
parallel laufender Commit mit dem Betreff eines **anderen** Pakets meiner eigenen
Rolle hat die Datei **halbfertig** eingecheckt. Das ist die schaerfere Form des
Sachverhalts -- nicht nur ein falscher Betreff, sondern ein Commit, der einen
Zwischenstand eines fremden, noch laufenden Vorgangs festhaelt. Die Bedingung 1 des
Vorschlags 0131, `git add` nur auf benannte Pfade, haette genau das verhindert. Fuer die Pruefung
selbst folgt daraus nur die Vorsichtsregel, die ohnehin gilt: Ob gebaut wurde,
entscheidet der Dateiinhalt an `HEAD`, nie der Betreff.

Zur Zurechnung: Die Aenderung an `werkzeugkette.cmake` in jenem Commit betrifft
ausschliesslich die Erkennung der leeren Fundmeldung und hat mit Vergiftung,
Strichrechnung oder Ueberlauf nichts zu tun. Sie gehoert einem anderen Lauf. Der
Bauagent von 0122 hat seine Dateiliste eingehalten.

**Die Einbauregel ist selbst nicht verriegelt -- daraus wird ein Vorschlag.** Der neue
Kopftext nennt die Einbauregel den ganzen Trick, und er hat recht: Ohne sie braeuchte
die Sperre eine Ausnahmeliste. Nur haelt heute nichts diese Regel ausser einer
Textsuche in einem Kommentar. Ich habe die Luecke gefahren statt sie zu behaupten. Baum
**E** bekommt eine neue Datei `kern/src/luecke.cpp`, die `kern/sperre.hpp` **nicht**
bindet und beides enthaelt, was der Kern verbietet -- eine `double`-Rechnung und eine
eigene Fassung der Strichrechnung mit `__builtin_add_overflow`. Ergebnis: Die Datei
wird vom Quellensammler des Kerns aufgelesen, in `kern` **und** in `kern_geprueft`
uebersetzt, und der Lauf ist 14 von 14 gruen. Weder T4 noch die neue Sperre erreichen
sie.

Das ist kein Befund gegen 0122 -- die Luecke ist aelter als das Paket und liegt
ausserhalb seiner einen Datei. Aber 0122 macht sie teurer, weil ab jetzt zwei Vorgaben
an derselben ungeprueften Regel haengen statt einer. Der Vorschlag steht als
`0134-sperrebindung-jeder-kernquelle`.

## Wonach ich ausserdem gesucht und nichts gefunden habe

- Ob die Sperre einen heute erlaubten Aufruf mittrifft: nein, beide Profile gruen und
  die Objektdateien bytegleich.
- Ob sie Gleitkomma, Rundung oder einen Zahlenrand beruehrt: nein, sie erzeugt keinen
  Code.
- Ob ausser `sperre.hpp` eine zweite Datei des Pakets angefasst wurde: nein.
- Ob eine Quelle den Kopf vor `festkomma.hpp` bindet und damit still eine andere
  Reihenfolge herstellt: nein, in keiner der 18 Einheiten.
- Ob im Kopf eine Zahl oder ein Name steht, den der Baum nicht hergibt: nein, die
  beiden Suchnachweise und der Belegstellenriegel decken ihn ab.
