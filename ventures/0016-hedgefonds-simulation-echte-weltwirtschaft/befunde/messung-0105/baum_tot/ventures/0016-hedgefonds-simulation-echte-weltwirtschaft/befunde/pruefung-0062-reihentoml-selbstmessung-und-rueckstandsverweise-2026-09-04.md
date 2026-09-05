---
typ: pruefung
paket: 0062-reihentoml-selbstmessung-und-rueckstandsverweise
pruefer: daten-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen selbst nachgemessen -- Blattvergleich mit tomllib ueber drei Staende, das Verbotsmuster mit re und Grep ueber beide Dateien, die fuenf Ersatzadressen einzeln gegen die vorliegende und die historischen Fassungen von rueckstand.md, und die sieben Schnitte aus [pruefweg] neu gezaehlt.
befunde: 0
---

# Urteil

**`geprueft`.** Die drei Bedingungen sind erfuellt. Ich habe keinen Befund gegen das
Paket.

## Wie ich gemessen habe

Alles in einem `python3`-Heredoc, `tomllib` und `re` gegen den Dateiinhalt, `git show`
fuer die historischen Staende. **Keine Zahl dieses Befunds stammt aus dem Baubericht** --
jede ist neu erhoben. Der Baubericht ist erst danach dagegengelegt worden.

Der Stand, den ich prueife, ist der Arbeitsbaum. Er ist mit `HEAD` (`b1ce529`) identisch:
`git status` fuehrt weder `daten/reihen.toml` noch `daten/einheitenbefund-pwt-baci.md`.
Die Aenderung des Pakets liegt nicht im Paketcommit `34f48f8` (der traegt nur Logbuch und
Paketdatei), sondern in `cff60c2` (`testentwickler: 0059-…`) -- zum zweiten Mal in Folge
hat ein fremder Lauf die Datendateien mitgenommen. Vergleichsstand vor dem Lauf ist damit
`24aa5aa`, der letzte Commit davor, der `reihen.toml` traegt.

## Bedingung 1 -- die drei Zahlen im Nachtrag

**Erfuellt.** Das Feld nennt als Bezugsstand den Commit `1a4d240`. Der ist echt und sitzt
richtig: `1a4d240` (2026-09-04 02:22:59) ist Vorfahr von `24aa5aa` (02:25:30), und zwischen
beiden liegt kein weiterer Commit, der `reihen.toml` traegt -- `1a4d240` ist also die
Fassung vor dem Baulauf des Pakets 0057, so wie das Feld es behauptet.

Blattvergleich `1a4d240` gegen den vorliegenden Stand, beide Baeume flach gezogen,
Blattschluessel als Pfad:

| im Feld behauptet | von mir gemessen |
|---|---|
| Bezugsstand 1212 Blattwerte | **1212** |
| vorliegende Fassung 1214 | **1214** |
| zwei neue Schluessel, `datei.nachgezogen_durch.5` und `.6` | **2**, genau diese |
| keiner weggefallen | **0** |
| 1212 gemeinsame Schluessel | **1212** |
| davon 13 mit verschiedenem Wert | **13** |

Die Aufzaehlung im Feld ist nicht nur summengleich, sondern elementweise gleich. Gemessen:
`datei.stand`, `pruefweg.toml_geprueft`, `reihe.1.offen.0`,
`reihe.1.umrechnung.1.begruendung`, `reihe.1.umrechnung.1.beleg`,
`reihe.5.lizenzbeleg.0.wortlaut_form`, `reihe.9.umrechnung.0.begruendung`,
`reihe.9.umrechnung.0.beleg`, `reihe.12.lizenzbeleg.0.wortlaut_form`, `widerspruch.1.lang`,
`widerspruch.3.lang`, `widerspruch.4.entscheidet`, `zaehlung.beleg`. Das Feld zerlegt sie in
„die neun oben genannten" (aus 0057) plus `datei.stand` und sich selbst plus
`widerspruch.4.entscheidet` und `reihe.1.offen.0` -- 9 + 2 + 2 = 13. Die neun aus dem
0057-Nachtrag habe ich einzeln in Pfadschreibweise uebersetzt und gegen meine Liste gelegt;
sie decken sich. Die Nebenbemerkung stimmt ebenfalls: `reihe.1.umrechnung.1.beleg` ist der
dritte von 0062 berichtigte Verweis und steht schon unter den neun, der vierte steht im
Kopfkommentar und ist kein Blattwert.

**Gegenprobe zur 0057-Bilanz:** `1a4d240` gegen `24aa5aa` ergibt 1213 Blattwerte, einen
neuen Schluessel und elf Unterschiede -- genau die Zahlen, die der Rumpf des Pakets als die
richtigen benannt hat. Die Aufteilung im Feld ist damit von zwei Seiten belegt.

**„Kein Wort des vorher dort stehenden Textes ist entfernt."** Maschinell: der Feldwert aus
`24aa5aa` ist eine Praefix-Teilzeichenkette des vorliegenden (3.225 gegen 4.597 Zeichen,
1.372 angehaengt, `neu.startswith(alt)` ist wahr). Der falsche Halbsatz von 0057 steht
unveraendert drin und ist im Nachtrag als falsch bezeichnet.

**Zur Selbstbezueglichkeit, an der dieses Feld dreimal gescheitert ist:** Die Messung ist
stabil unter dem eigenen Schreibvorgang. `pruefweg.toml_geprueft` ist selbst einer der 13
Unterschiede und war es schon vor dem Nachtrag; die Blattzahl aendert sich durch eine
Textaenderung im Feld nicht. Ein spaeteres Umformulieren des Nachtrags macht die drei
Zahlen also nicht erneut falsch. Falsch wuerden sie erst durch eine Aenderung an einem
*anderen* Feld -- und dafuer nennt der Nachtrag jetzt den Bezugsstand, an dem sich das
unterscheiden laesst. Genau das war der Zweck der Bedingung.

## Bedingung 2 -- die fuenf toten Verweise

**Erfuellt.** Das Muster `rueckstand\.md[^\n]{0,40}Punkt ?[0-9]` liefert ueber
`daten/reihen.toml` und `daten/einheitenbefund-pwt-baci.md` **0 Treffer** -- mit `Grep` und
unabhaengig davon mit `re` gegen den Dateiinhalt. `rueckstand.md` steht weiterhin viermal
in `reihen.toml` und einmal im Einheitenbefund; die Adressen sind ersetzt, nicht entfernt.

**Ich habe nicht nur das Muster geprueft, sondern die Sache.** Alle 23 verbliebenen
Vorkommen von `Punkt <n>` in beiden Dateien einzeln nachgesehen: sie zeigen ausnahmslos auf
`technik.md` (T23, T37, T5) oder auf `daten/deckungsbefund-1997.md`. Keiner meint
`rueckstand.md` -- das Muster ist also nicht knapp unterlaufen worden.

Alle fuenf Ersatzadressen nennen die Ueberschrift als Zitat und sagen ausdruecklich, dass
die Sache in der vorliegenden Fassung nicht mehr aufgefuehrt ist:

| Stelle | Sache | „nicht mehr aufgefuehrt" gesagt |
|---|---|---|
| `reihen.toml` Z. 37-43, Leseregel 1 | T37-Klasse gegen Lizenzurteil, eine von zwei Entwurfsfragen der Vornacht | ja |
| `reihen.toml` Z. 289, `widerspruch.4.entscheidet` | eigener Punkt, Zitat „Reihe 9 und R = 19" | ja |
| `reihen.toml` Z. 437, `reihe.1.offen.0` | Rundungsstelle vor oder nach Normierung | ja |
| `reihen.toml` Z. 457, `reihe.1.umrechnung.1.beleg` | dieselbe offene Rundungsstelle | ja |
| `einheitenbefund-pwt-baci.md` Z. 99, Abschnitt 2 | Zitat „Klasse 2 misst zweierlei — laufende und konstante Preise" | ja |

**Das Zitat als Teilzeichenkette wiedergefunden.** „Was der Geschäftsführer entscheiden
lassen muss" steht **einmal** in der vorliegenden `rueckstand.md` (als `## `-Ueberschrift,
Fassung 16, Stand 2026-09-03) und **viermal** in `reihen.toml`, **einmal** im
Einheitenbefund -- jedes Vorkommen zeichengleich mit `ä` und `ü` und ungebrochen auf einer
Zeile, auch das im Kopfkommentar, wo der Praefix `#    ` es haette zerreissen koennen.

**Die Behauptung „nicht mehr aufgefuehrt" habe ich nicht geglaubt, sondern gezaehlt.** In
der vorliegenden `rueckstand.md` kommen `T37-Klasse`, `Rundet Reihe 2`, `Rundungsstelle`,
`Reihe 9 und R = 19`, `Entwurfsfragen aus den Befunden der Vornacht` und `Klasse 2 misst
zweierlei` **je null Mal** vor.

**Und die historische Datierung „stand am 2026-09-02" ebenfalls.** Nicht nur, ob die Worte
dort standen, sondern ob sie *unter jener Ueberschrift* standen -- dafuer habe ich den
Abschnitt von der Ueberschrift bis zur naechsten `## `-Marke herausgeschnitten und nur
darin gesucht:

- `30e5073` (2026-09-02 07:07, Stand beim Eintrag der vier Verweise in `reihen.toml`):
  Punkt 6 heisst „Reihe 9 und R = 19", Punkt 9 heisst „Zwei Entwurfsfragen aus den Befunden
  der Vornacht" und enthaelt beide gemeinten Sachen -- das `frei` als T37-Klasse und kein
  Lizenzurteil, und „Rundet Reihe 2 vor oder nach der Normierung?". Alle drei Fundstellen
  liegen im Abschnitt, nicht anderswo in der Datei.
- `d27f02f` (2026-09-02 09:51, Stand beim Eintrag des Verweises im Einheitenbefund):
  „Klasse 2 misst zweierlei — laufende und konstante Preise" steht unter derselben
  Ueberschrift.

## Bedingung 3 -- sonst nichts geaendert

**Erfuellt.** Blattvergleich `24aa5aa` gegen den vorliegenden Stand: 1213 gegen 1214
Blattwerte, **ein** neuer Schluessel (`datei.nachgezogen_durch.6`), keiner weggefallen,
**vier** verschiedene gemeinsame Werte -- `pruefweg.toml_geprueft`,
`widerspruch.4.entscheidet`, `reihe.1.offen.0`, `reihe.1.umrechnung.1.beleg`. Das liegt
innerhalb der erlaubten Liste und ist kleiner als sie: `datei.stand` steht schon auf
`2026-09-04` und ist nicht angefasst.

Der Zeilendiff bestaetigt das ueber den Blattvergleich hinaus, der Kommentarzeilen nicht
sieht: `git diff 24aa5aa HEAD -- daten/reihen.toml` ergibt **+12/−6 in sechs Hunks** an
genau den fuenf Verweisstellen plus `nachgezogen_durch`. Keine andere Kommentarzeile, keine
Leerzeile, keine Umsortierung. `einheitenbefund-pwt-baci.md`: **ein** Hunk, `@@ -94,8 +94,12
@@`, +6/−2, betroffen sind allein die zwei Zeilen des Satzes; die Folgezeile
(`Abschnitt 5.`) steht als unveraenderter Kontext.

**Die sieben Schnitte aus `[pruefweg]` habe ich neu gezaehlt, nicht nachgelesen** -- alle
sieben reproduzieren gegen die vorliegende Fassung:

- **schnitt_1** `[=] [0-9]+\.[0-9]`: **6** Treffer, und alle sechs an den beschriebenen
  Stellen (Widerspruch Nr. 4 `kurz` und `lang`, Reihen 4, 10, 15, 17).
- **schnitt_2** `[']{3}`: **29** Zeilen, **54** Vorkommen, `^[']{3}|[']{3}$` **27** Zeilen.
  25·2 + 4 = 54, die Rechnung geht auf. `["]{3}` genau **1** Zeile.
- **schnitt_3** `^\[\[`: **113**, aufgeteilt 19 reihe + 9 widerspruch + 22 reihe.umrechnung
  + 20 reihe.lizenzbeleg + 39 reihe.deckung + 2 reihe.konkordanz + 2 reihe.bruch = **113**,
  und kein achter Typ.
- **schnitt_4** `^exogen_ab = ` **19**, `^verkettet_ab = ` **19**, `^lizenzurteil = ` **19**,
  Sammelmuster **152** (= 8·19), `^t37_klasse = ` **20**, `^nr = ` **28**.
- **schnitt_5** `^sollreihen = ` **21**, ohne Gleichheitszeichen **28**, Summe ueber alle 21
  Zeilen **43**, davon auf Reihenebene 43 − 4 − 8 = **31**.
- **schnitt_6** `tomllib` liest die Datei fehlerfrei -- kein doppelter Schluessel.
- **schnitt_7** `^wortlaut = ` **20**, `^wortlaut_form` **2**.

**Zusaetzlich, weil das meine Rolle ist und nicht in der Abnahme steht:** Die innere
Konsistenz der Datei ist nach dem Lauf unversehrt. `zaehlung.sollreihen_gesamt` = 31, die
Summe der `sollreihen` ueber die 19 Reihenbloecke = **31**. 19 Reihen, 9 Widersprueche.
Keine Einheit, kein Faktor, kein Basisjahr, kein Lizenzwortlaut ist beruehrt worden -- das
folgt schon aus der Vierer-Liste des Blattvergleichs, ich habe es aber gegen die
Umrechnungs- und Lizenzblöcke einzeln gegengelesen.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Die Stelle, an der das Dokument seine eigene Methode nicht anwendet.** Das ist bei dieser
  Datei `toml_geprueft`, und genau dort sass der Fehler von 0057. Diesmal traegt das Feld
  seinen Bezugsstand und ist unter dem eigenen Schreibvorgang stabil.
- **Was der Bauagent ueber den Auftrag hinaus geaendert hat.** Genau eines:
  `datei.nachgezogen_durch.6`. Von Bedingung 3 gedeckt, sachlich richtig -- die Liste fuehrt
  jetzt sieben Eintraege, und `0062-…` gehoert dazu.
- **Ob eine Sachaussage im Adressersatz mitgewandert ist.** Die vier Felder Wort fuer Wort
  gelesen: in allen vier bleibt der Sachsatz vor der Adresse woertlich stehen; ersetzt ist
  ausschliesslich der Klammerteil. Beispiel Leseregel 1: „Das Lizenzurteil steht in
  `lizenzurteil` und nirgends sonst" steht unveraendert am Ende.
- **Ob das Muster von Bedingung 2 anderswo im Vorhaben noch trifft.** Ja, aber nur in
  `daten/zwischenstaende/` -- in `.neu.tmp`, `.neu2.tmp`, `.neu3.tmp`, `.f1592.tmp`,
  `.f1592b.tmp`. Das ist **kein Befund**: Paket 0045 hat diese zwoelf Dateien dorthin
  verschoben und ihnen `LIESMICH-zwischenstaende.md` beigelegt, das im ersten Satz sagt
  „Was hier liegt, gilt nicht" und die gueltige Fassung benennt. Sie sind ausserdem nicht
  Teil der Dateiliste dieses Pakets.

## Zwei Sachen ausserhalb der Abnahme, beide ohne Paket

**Erstens: die Spalte „gemeint war" im Paketrumpf ist beim fuenften Eintrag falsch, und die
Datei traegt zu Recht etwas anderes.** Der Rumpf sagt fuer den Einheitenbefund „gemeint
war: die fehlenden Rohdaten". Ich habe unabhaengig nachgesehen: Der Satz steht in
**Abschnitt 2** (*Preisbasis BACI — gemessen: laufende Preise*, Z. 82-104) und endet mit
„Die Folge steht in Abschnitt 5"; Abschnitt 5 heisst *Die Folge fuer T5 Klasse 2*. Zum
Stand `d27f02f` lautete der dortige Punkt 4 „**Klasse 2 misst zweierlei** … Unveraendert
und weiter **die schwerste offene Sache**" -- woertlich der Halbsatz, den der Verweis
traegt. Punkt 3 war zu jenem Stand „Ein TOML-Parser gehoert in den Runner". Der Verweis war
also schon bei seiner Eintragung falsch nummeriert, und die eingetragene Sache
(Klasse-2-Frage) ist die richtige. **Das ist ein Fehler im Paketrumpf, kein Fehler in der
Datei** -- er beruehrt keine der drei Bedingungen, und ein Paket braucht es nicht, weil die
Datei bereits das Richtige sagt. Vermerkt fuer den Projektmanager.

**Zweitens, zur Meldung des Bauagenten ueber den fremden Commit `cff60c2`: nichts ist
verloren gegangen.** Ich habe es nachgezaehlt, weil „74.209 geloeschte Zeilen unter
`ventures/`" alarmierend klingt. Gegen den echten Elternteil (`cff60c2^`, nicht `24aa5aa`)
loescht der Commit 1018 Dateien -- **alle** unter `befunde/messung-0063/*/bau-vorher-*/`
und `bau-nachher-*/`, also CMake-Bauabfall, der zuvor versehentlich mitversioniert war.
Keine Quelldatei, kein Befund, kein Arbeitspaket. Von den 74.209 Zeilen liegen 74.199 in
`befunde/messung-0063/`, davon die groessten Einzelposten in `CMakeCXXCompilerId.cpp`. Die
Datendateien verlieren in demselben Commit acht Zeilen, und das sind genau die sechs plus
zwei dieses Pakets. **Kein Befund, kein Vorschlag** -- nur die Zahl, damit sie nicht als
Datenverlust in den Rueckstand wandert.

**Ein Vorschlag ergibt sich aus diesem Lauf nicht.** Die einzige Sache, die ich in
`reihen.toml` noch offen sehe, ist die aus meiner Pruefung zu 0049: der Kommentar ueber
`[datei.vorlagen]` sagt „viermal als `beleg`" (es ist eine Vorlage) und „vier Pakete lang
gefehlt" (es sind zwei bis drei). Beides steht unveraendert in der Datei. 0062 haette es
nicht anfassen duerfen -- Bedingung 3 verbietet jede weitere Aenderung --, und ein eigenes
Paket fuer zwei Zahlwoerter in einem Kommentar lohnt den Lauf nicht. Es gehoert an das
naechste Paket, das den Kopf von `reihen.toml` ohnehin oeffnet.
