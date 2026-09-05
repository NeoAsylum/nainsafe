---
typ: pruefung
paket: 0065-reihentoml-reihe-9-ohne-sollrolle
pruefer: daten-pruefer
datum: 2026-09-04
urteil: zurueck
kriterium_geprueft: Alle vier Bedingungen einzeln nachgerechnet statt verglichen -- Bedingungen 1, 2 und 3 sind erfuellt, Bedingung 4 nicht: der Kommentar ueber `[datei.vorlagen]` traegt neben den zwei nachgezaehlten Zahlwoertern eine dritte, selbst hinzugefuegte Verteilungsaussage, und die stimmt nicht.
befunde: 1
---

# Pruefung 0065 -- `reihen.toml`, Reihe 9 ohne Sollrolle

## Womit gemessen wurde

Bezugsstand `4eb20ac`, Blob `7a83aef58053050b77ae502c27b9aba24e97f77d` -- nachgeschlagen,
stimmt. Vergleichsstand ist `HEAD` (`6cd55ae5…`). Die Aenderung liegt in **zwei** Commits,
nicht in einem: `7a79290` (+84/−30, ein Fremdlauf hat sie mitgenommen) und `0b378a1`
(+2/−2). Gegen `4eb20ac` sind es also **+86/−32**; die Bilanz „+84/−30" im Baubericht misst
nur den ersten der beiden. Kein weiterer Commit liegt dazwischen (`git log -- <datei>`).

Alles maschinell: `tomllib` auf beide Fassungen, Baeume flach gezogen, Blattschluessel als
Pfadtupel; Grep-Muster mit `re` auf der Datei neu gezaehlt. Der Arbeitsbaum fuehrt
`reihen.toml` nicht als geaendert, die Datei ist committet.

**Nicht gelesen:** `notizen/datenbauer.md`.

## Was gehalten hat

### Bedingung 1 -- nachgerechnet, nicht verglichen

Ich habe `sollreihen` selbst ueber alle neunzehn `[[reihe]]` addiert:

| Rechnung | Ergebnis |
|---|---|
| Summe `sollreihen` je `[[reihe]]` (4+12+0+0+0+0+0+4+**0**+3+4+0…) | **27** |
| `zaehlung.sollreihen_gesamt` | **27** |
| `sollreihen_frei + sollreihen_abgeleitet` | 23 + 4 = **27** |
| `sollreihen_frei + sollreihen_gesetzt + sollreihen_abgeleitet` | 23 + 0 + 4 = **27** |
| `[zaehlung.lizenz]` frei + unklar + gesperrt | 7 + 20 + 0 = **27** |
| `frei_zerlegung` ausmultipliziert | 4+12+4+3 = **23** |

`sollreihen_frei = 23` und `sollreihen_abgeleitet = 4` stehen unveraendert -- sie sind nicht
unter den geaenderten Blattwerten. Reihe 9 traegt `rolle = ["start", "politikpfad"]`,
`sollreihen = 0`, `t37_klasse = ""`.

Die Blattwertbilanz gegen `4eb20ac` unabhaengig nachgezogen und **zeichengleich** zum
Baubericht: 1214 → 1214, zwei neue Schluessel (`datei.nachgezogen_durch.7`,
`zaehlung.handelsblock.in_den_sollreihen_enthalten`), zwei weggefallene (`reihe.8.rolle.2`,
`zaehlung.handelsblock.in_den_31_enthalten`), **21** verschiedene gemeinsame Werte. Die
einundzwanzig Namen decken sich eins zu eins mit der Liste in `pruefweg.toml_geprueft`.

Statt der Elferliste des Pakets habe ich die Datei ganz durchsucht: **`\b31\b`** hat elf
Fundstellen, alle geprueft -- fuenf historisch mit Datum, eine der Kommentar ueber den
umbenannten Schluessel, eine das Datum `2026-08-31`, drei in `toml_geprueft` (zwei davon
ausdruecklich als ueberholt bezeichnet), eine in `schnitt_5` als alter Stand. Keine fuehrt
die 31 als geltende Zahl. `Reihe 9` kommt 29 mal auf 22 Zeilen vor; jede Stelle ist entweder
mit Datum historisch oder sagt, dass sie keine Sollreihe mehr ist.

Nachgerechnet auch die Zahlen, die aus der Entscheidung folgen:
`reihe.9.offen[1]` sagt „11 der 27 Sollreihen" -- Reihe 8 (4) + Reihe 10 (3) + Reihe 11 (4)
= 11, und 11 + 4 = 15 als alter Stand. Stimmt. `[zaehlung.lizenz].sollreihen_unklar`
24 − 4 = 20, `unklar_zerlegung` 4+12+4 = 20. Stimmt.

**Die zwoelfte Fundstelle ist echt.** `reihe.12.t26_folge` (das ist Reihe 13) nannte die
31 Sollreihen, ohne Reihe 9 zu nennen, und stand deshalb nicht in der Tabelle des Pakets.
Ich haette sie mit demselben dateiweiten `\b31\b` gefunden; sie ist behoben. Das ist ein
Befund **gegen den Vorschlag**, wie der Projektmanager es vorgesehen hat, und keiner gegen
den Bauagenten.

### Bedingung 2 -- die 16 und die Toleranz 2

`zaehlung.pruefgegenstaende` ist in der Blattwertbilanz **nicht** enthalten: kein Wert des
Blocks hat sich bewegt. Nachgerechnet: 4 + 4 + 4 + 3 + 1 = 16, `gesamt = 16`,
`toleranz = 2`. Der Kommentar darueber (Z. 207-220) begruendet das Stehenbleiben mit der
T37-Klasse `gesetzt` und zaehlt die fuenf Posten abschliessend auf. Erfuellt.

### Bedingung 3 -- `[[widerspruch]]` Nr. 5

Die Nummer selbst nachgeschlagen (`widerspruch[4].nr == 5`, die Liste zaehlt ab null).
`entscheidet` trennt jetzt drei Dinge: entschieden am 2026-09-03 durch den Spielentwerfer
(Sollrolle gestrichen, Start und Politikpfad bleiben, Invariante statt Fehlermass); offen
beim Datenbauer die Quelle fuer den Pfad; offen beim Architekten der Nachzug von
`technik.md`. Der alte `rueckstand.md`-Verweis samt Zitat steht unveraendert dahinter.
Erfuellt.

### Die Selbstmessungen -- alle nachgezaehlt, keine falsch

Die Datei behauptet in `[pruefweg]` fuenfzehn Zaehlungen ueber sich selbst. Ich habe sie
gegen die vorliegende Fassung neu gezaehlt, nicht nachgelesen:

`[=] [0-9]+\.[0-9]` = 6 · `'{3}` 29 Zeilen / 54 Vorkommen · `^'{3}|'{3}$` 27 Zeilen ·
`"{3}` 1 Zeile · `^\[\[` = 113, nach Typ 19/9/22/20/39/2/2 = 113 · `^exogen_ab = ` 19 ·
`^verkettet_ab = ` 19 · `^lizenzurteil = ` 19 · Sammelmuster 152 · `^t37_klasse = ` 20 ·
`^nr = ` 28 · `^sollreihen = ` 21 (Summe der Werte **39**) · `^sollreihen` 28 ·
`^wortlaut = ` 20 (davon 4 leer) · `^wortlaut_form` 2. **Alle fuenfzehn stimmen.** Die
neunzehn Reihenwerte tragen vierzehn Nullen und fuenf Werte, wie `schnitt_5` sagt.

`pruefweg.toml_geprueft`: Der alte Feldwert ist **Praefix** des neuen (4.597 → 7.830
Zeichen), kein Wort entfernt. Der Nachtrag nennt seinen Bezugsstand (`4eb20ac`) -- damit ist
das Feld erstmals stabil unter dem eigenen Schreibvorgang, das war der Rest aus meiner
Pruefung zu 0062.

### `rolle_tabelle` -- die Abweichung vom Handzettel ist tragfaehig

`spiel.md` Z. 2088-2090 nennt `t37_klasse` **und** `rolle_tabelle` der Reihe 9 „ab heute
falsch". Der Bauagent hat nur das erste geleert. Das ist trotzdem richtig, und ich habe es
nachgemessen statt seiner Begruendung zu folgen:

- **Leseregel 4** im Kopf der Datei (Z. 85-90) definiert `rolle_tabelle` als woertliche
  Uebernahme aus `technik.md` Abschnitt 7, nur ohne Fettauszeichnung.
- `technik.md` **Z. 1441** lautet unveraendert `| 9 | Leitzins | 4 | bp | IWF IFS | Start +
  Politikpfad + Soll (4, **gesetzt**) | nein |`, und **Z. 2112** fuehrt in T37 weiter
  `` `gesetzt` | Leitzins (4) | 4 | …``. Beides selbst aufgeschlagen.
- Das Feld traegt also weiter genau das, was seine Vorlage sagt. Falsch ist die Vorlage.
- Die Grenzen des Pakets verlangen fuer `technik.md`-Widersprueche die Meldung, nicht die
  Aenderung. Gemeldet ist er unter Nr. 5, Feld `in_dieser_datei`, mit der Vorfahrtregel
  „fuer den Jahrgangsbau gelten `rolle`, `sollreihen` und `t37_klasse`, nicht
  `rolle_tabelle`" -- dieselbe Vorfahrt, die Nr. 2 fuer `verdacht_tabelle` gegen
  `lizenzurteil` schon festlegt. Der Vorschlag `0068` (`status: vorschlag`, richtig gesetzt)
  gibt den Nachzug an den Architekten.
- **Nichts liest das Feld maschinell.** Ausserhalb von `reihen.toml` selbst kommt
  `rolle_tabelle` nur in Paket- und Befunddateien vor, in keinem Werkzeug. Die Abweichung
  kann also keinen falschen Jahrgang erzeugen.

Keine Beanstandung.

### Grenzen des Pakets eingehalten

Reihe 9 behaelt `quelle_eingebettet` (`IWF, Datenfluss IMF.STA/MFS_IR 9.0.0`), `codes`
(`DISR_RT_PT_A_PT`), `deckung_urteil` („reisst -- DEU und CHN …") und alle
`[[reihe.deckung]]`-Bloecke -- keines davon steht unter den geaenderten Blattwerten.
`daten/deckungsbefund-1997.md` ist unangetastet. Die beiden Commits tragen ausser
`reihen.toml` nur die Paketdatei, das Logbuch und den Vorschlag `0068`; **keine zweite
Datendatei und kein `technik.md`**.

Einheiten, Basisjahre, Luecken und Lizenzen: Das Paket fasst keine an, und keiner der
einundzwanzig geaenderten Blattwerte liegt in `[[reihe.umrechnung]]`,
`[[reihe.lizenzbeleg]]`, `[[reihe.deckung]]` oder `[namensnennung]`. Gepruefte
Nullaussage, kein Eindruck.

---

## Befund 1 -- Bedingung 4 ist nicht erfuellt: die dritte Zahl im Kommentar ueber `[datei.vorlagen]` stimmt nicht

**Die zwei geforderten Zahlwoerter sind richtig nachgezaehlt.** Ich habe beide unabhaengig
nachgemessen:

| Angabe | steht jetzt da | von mir gezaehlt |
|---|---|---|
| wie oft der Einheitenbefund als `beleg` auftritt | einmal | **einmal** (`reihe.13.umrechnung.0.beleg`) |
| wie viele Pakete lang die Vorlage gefehlt hat | zwei | **zwei** (0036 und 0047) |

Die zweite habe ich nicht aus `nachgezogen_durch` uebernommen, sondern an den zehn Fassungen
der Datei im Git gegengeprueft, jede mit `tomllib` eingelesen: Der Beleg erscheint mit
`ae6f605`, der Vorlagenschluessel mit `58908fa`, dazwischen liegt genau eine Fassung
(`66a463b`, Paket 0047). Stimmt.

**Falsch ist der Satz, den der Bauagent ungefragt danebengestellt hat.** Er lautet in der
Datei (Z. 143-145):

> Ueberhaupt genannt wird er in **acht** Blattwerten, `datei.vorlagen.einheiten`
> mitgezaehlt; die uebrigen sieben stehen unter `offen`, `begruendung` und `lang`.

Die Acht stimmt. Die Sieben nicht: Es sind **sechs**.

### Wie man den Fehler erzeugt

Man wendet die Zaehlregel an, die der Kommentar zwei Saetze davor selbst aufstellt --
Blattwerte, die die Zeichenfolge `einheitenbefund-pwt-baci` tragen:

```
python3 - <<'PYEOF'
import tomllib
p="ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml"
n=tomllib.loads(open(p,encoding="utf-8").read())
def flat(x,pre=()):
    if isinstance(x,dict):
        for k,v in x.items(): yield from flat(v,pre+(k,))
    elif isinstance(x,list):
        for i,v in enumerate(x): yield from flat(v,pre+(str(i),))
    else: yield ".".join(pre),x
for k,v in flat(n):
    if isinstance(v,str) and "einheitenbefund-pwt-baci" in v: print(k)
PYEOF
```

Ausgabe, acht Zeilen:

```
datei.vorlagen.einheiten
widerspruch.8.lang
reihe.2.offen.0
reihe.2.umrechnung.0.begruendung
reihe.13.offen.0
reihe.13.offen.1
reihe.13.umrechnung.0.beleg
reihe.15.offen.0
```

Die tatsaechliche Aufteilung der acht ist **1 + 1 + 6**: ein `beleg`, ein
`datei.vorlagen.einheiten`, und sechs unter `offen`, `begruendung` und `lang`.

Der Satz geht unter **beiden** moeglichen Lesarten von „die uebrigen sieben" nicht auf:

- Zieht man den einen `beleg` ab (das legt der Satz davor nahe), bleiben sieben -- aber
  `datei.vorlagen.einheiten` ist darunter, und das steht weder unter `offen` noch unter
  `begruendung` noch unter `lang`. Es steht in einer Tabelle `[datei.vorlagen]` unter dem
  Schluessel `einheiten`.
- Zieht man `datei.vorlagen.einheiten` ab (das legt der Halbsatz „mitgezaehlt" nahe),
  bleiben ebenfalls sieben -- aber dann ist der `beleg` darunter, und der steht dort
  ebenfalls nicht.

Ein Satz, der sich selbst in derselben Zeile zweimal mitzaehlt und einmal wieder abzieht,
ist keine Zaehlung.

### Warum das Bedingung 4 verfehlt und nicht bloss eine Schoenheit ist

Bedingung 4 lautet: *„Der Kommentar ueber `[datei.vorlagen]` sagt, was gezaehlt wurde, **und
die Zahlen stimmen**."* Sie ist nicht auf die zwei alten Zahlwoerter beschraenkt, sondern
auf die Zahlen dieses Kommentars -- und der Projektmanager hat ausdruecklich keinen Wortlaut
vorgegeben, gerade damit hier gezaehlt und nicht abgeschrieben wird.

Der Kommentar ist ausserdem die einzige Stelle der Datei, an der **die Zaehlregel selbst**
steht. Wer sie kuenftig anwendet -- und der Kommentar lockt genau dazu ein -- kommt auf 6
und liest daneben 7. Damit erzeugt die Nachzaehlung, die zwei falsche Zahlwoerter beseitigen
sollte, ein drittes. Das ist dieselbe Kette 0028 → 0042 → 0053, die der Annahmevermerk als
Grund fuer diese Bedingung nennt, nur eine Generation weiter.

Der Rest des Kommentars bleibt richtig und muss nicht angefasst werden. **Ein Wort.**

---

## Was ich zu den Unsicherheiten des Bauberichts sage

- **`probe = "23 + 0 + 4 = 27, kurz 23 + 4 = 27"`** ist eine Erfuellung, keine Abweichung.
  Bedingung 1 verlangt, dass die Summanden auf `sollreihen_frei`, `sollreihen_gesetzt` und
  `sollreihen_abgeleitet` zeigen; die dreigliedrige Form tut genau das und macht die Null
  sichtbar, die der Schluessel `gesetzt_zerlegung` sonst allein traegt. Der Wortlaut der
  Abnahme steht daneben. Keine Ruecknahme.
- **Die zwoelfte Fundstelle mitzunehmen war richtig.** Sie liegt in der Dateiliste des
  Pakets, traegt dieselbe Zahl und waere sonst der einzige Ort geblieben, an dem die 31 ohne
  Datum weiterlebt. Sie melden und stehen lassen haette die Selbstmessung
  `zaehlregel_sollreihen` gegen die Datei gestellt.
- **`rolle_tabelle`** -- siehe oben, tragfaehig.

## Was der Bericht anders zaehlt als ich, ohne dass es die Abnahme beruehrt

- **„+84/−30"** misst nur `7a79290`; gegen `4eb20ac` sind es +86/−32. Der Bericht sagt an
  anderer Stelle selbst, dass die Aenderung in zwei Commits liegt -- die Bilanzzeile sagt es
  nicht mit.
- **„28 Vorkommen von Reihe 9"** war beim Messen richtig; der zweite Commit hat eines
  ergaenzt, jetzt sind es 29 auf denselben 22 Zeilen.
- **`toml_geprueft` sagt „alle dreizehn Muster"**, der Bericht sagt fuenfzehn. Je nachdem, ob
  man `'{3}` in zwei Zaehlweisen und `^sollreihen` ohne Gleichheitszeichen als eigene Muster
  fuehrt, kommt man auf 13, 14 oder 15; das Feld nennt seine Zaehlregel nicht. **Kein
  Befund** -- die Sachaussage („unveraendert") habe ich fuer alle fuenfzehn Zaehlungen
  einzeln bestaetigt. Wer das Feld naechstes Mal ohnehin aufmacht, sollte die Zahl durch die
  Regel ersetzen, nach der sie zustande kommt.

## Wonach ich gesucht und nichts gefunden habe

Damit die Nullaussagen von einer nicht stattgefundenen Pruefung zu unterscheiden sind:
eine dreizehnte Stelle mit der alten Lage (dateiweit `\b31\b` und `Reihe 9`, alle 40
Fundstellen einzeln gelesen); eine Verschiebung in `sollreihen_frei` oder
`sollreihen_abgeleitet`; eine Aenderung an Einheit, Faktor, Basisjahr, Deckung oder
Lizenzbeleg irgendeiner Reihe; eine stillschweigend geglaettete Stelle ohne
`[[widerspruch]]`; eine Aenderung ausserhalb von `reihen.toml`; eine Selbstmessung, die
unter dem eigenen Schreibvorgang kippt; ein doppelter Schluessel (`tomllib` laeuft
fehlerfrei durch, 19 `[[reihe]]`, 9 `[[widerspruch]]`, sechs Wurzeltabellen).
