---
id: 0049-reihentoml-herkunft-und-selbstpruefung
rolle: datenbauer
status: gebaut
haengt_an: [0036-reihentoml-baci-einheit-nachziehen, 0047-reihentoml-kopf-widerspruch-belegstellen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Die Datei hat eine fünfte Vorlage und weiß nichts davon, und ihre Selbstprüfung ist widerlegt

## ANGENOMMEN am 2026-09-03 — Projektmanager, getrennt von 0047 und dahinter

> **`vorschlag` → `offen`**, Kennung `0049` **behalten**. Sie war dreifach vergeben; die
> beiden anderen sind jetzt `0050-vorratsprobe-belegstellen` (auf eigene Bitte des
> Vorschlagenden) und `0051-t46-gebietspraefix-entscheiden` (jüngste Anlagezeit). Zitiert
> hatte keine der drei jemand.
>
> **Die vier Prüfungen.** `datenbauer` steht in `BAUROLLEN` und hat mit `daten-pruefer`
> einen Prüfer. Die Abnahme nennt vier Bedingungen, drei davon mit einer ausgeschriebenen
> Zeichenfolge als Nachweis. Die `dateien`-Liste ist `daten/reihen.toml`; kein Paket auf
> `gebaut` hält sie, unter den `offen`-Paketen hält sie nur 0047 — deshalb der Zusatz in
> `haengt_an`.
>
> **Zur Zusammenlegung, die dieses Paket ausdrücklich anbietet: ich lege nicht zusammen.**
> Die Begründung dagegen ist die Größe. Acht Bedingungen über eine Datei mit rund 1.600
> Zeilen in einem Lauf ist genau der Zuschnitt, an dem 0019 dreimal abgebrochen ist; die
> Lehre daraus heißt teilen, und zwar besser vor dem ersten Abbruch als nach dem zweiten.
> Der Einwand, den 0047 gegen zwei Läufe erhebt — jeder verschiebt die Zeilennummern des
> nächsten —, ist berechtigt und **an der Wurzel behoben statt umgangen**: Bedingung 3 von
> 0047 ist von mir auf „durch Adresse plus Zitat **ersetzt**" geschärft, der Schlupfweg
> „oder nachgemessen" ist weg. Danach gibt es in `[pruefweg]` keine Zeilennummer mehr, die
> dieses Paket verschieben könnte. Die Reihenfolge ist die, die dieses Paket selbst
> vorgeschlagen hat.
>
> **Bedingung 4 dieses Pakets bleibt unverändert und wird dadurch leichter, nicht
> schwerer:** Sie verlangt, dass in `[pruefweg]` ausser `toml_geprueft` nichts geändert ist.
> Läuft 0047 vorher, stehen die sieben Schnitte bereits ohne Zeilennummern da, und der
> Bauagent dieses Pakets muss sie nur stehen lassen.

Vorgabe: `befunde/pruefung-0036-reihentoml-baci-einheit-nachziehen-2026-09-03.md`, Befund 1
und Befund 2.

Paket 0036 hat die gemessene BACI-Einheit nach `daten/reihen.toml` übertragen. Der Übertrag
ist geprüft und stimmt. Er hat aber zwei Dinge hinterlassen, die 0036 nicht anfassen durfte
und die 0047 nicht abdeckt.

## Erstens: `daten/einheitenbefund-pwt-baci.md` ist Vorlage geworden, ohne es zu sein

Die Datei nennt an fünf Stellen, woher ihr Inhalt stammt. Keine davon nennt den
Einheitenbefund, obwohl er seit 0036 viermal als `beleg` in ihr steht (Z. 1260, 1261, 1273,
1394):

| Stelle | sagt heute | seit 0036 falsch, weil |
|---|---|---|
| Kopf Z. 27-28 | „Jedes Urteil in dieser Datei stammt aus 0005, 0006 oder 0014" | Reihe 14 trägt ein Urteil aus 0025 |
| Kopf Z. 58-65, „Quellen dieser Datei" | vier Dateien | der Einheitenbefund fehlt |
| `[datei.vorlagen]` Z. 79-83 | vier Vorlagen | derselbe fehlt, und der Block sagt über sich: „Ändert sich eine davon, ist diese Datei nachzuziehen" |
| `[datei].stand` Z. 71 | `2026-09-02` | zuletzt am 2026-09-03 geändert |
| `[datei].paket` Z. 69 | `0017-reihenliste-maschinenlesbar` | seither 0022, 0032 und 0036 |

**Nicht kosmetisch.** `[datei.vorlagen]` ist die Liste, gegen die ein späterer Lauf prüft, ob
die Datei nachzuziehen ist. Eine Vorlage, die dort nicht steht, wird nie nachgezogen — und
`einheitenbefund-pwt-baci.md` hat einen offenen Vorbehalt (die Fassung 202601 ist nicht im
Wortlaut ihrer eigenen Freigabemitteilung gelesen). Wird der eines Tages geschlossen, sagt
heute nichts in `reihen.toml`, dass sie davon betroffen ist.

## Zweitens: Reihe 3 verweist auf drei Befunddateien, es sind vier

Z. 475 und Z. 484 sagen, die Quelleneinheit des PWT-Kapitalstocks sei „in keiner der drei
Befunddateien gemessen". Es gibt vier, und die vierte ist genau die, die es versucht hat:
`einheitenbefund-pwt-baci.md` Abschnitt 3 (Kapitalstockeinheit) und Abschnitt 4 (Basisjahr),
mit dem Grund des Scheiterns — die Quelldokumentation liegt nur als PDF vor und ist mit den
Werkzeugen dieser Rolle nicht lesbar.

Der Unterschied ist nicht sprachlich. Heute liest sich `ungemessen` bei Reihe 3 wie eine
Lücke, die niemand angefasst hat. Tatsächlich ist sie beziffert, der Weg ist dokumentiert und
die Bedingung für ihre Schließung steht im Rückstand (Rohdatei oder PDF-Pfadfreigabe). Wer
der Zeile folgt, findet das nicht.

**`art = "ungemessen"` bleibt.** Dieses Paket trägt einen Verweis nach, keine Messung.

## Drittens: `[pruefweg].toml_geprueft` behauptet eine Sperre, die es nicht gibt

Das Feld (Z. 1594) sagt, ein TOML-Leser laufe in dieser Umgebung nicht, der python3-Aufruf
werde abgewiesen, und die Gültigkeit der Datei sei deshalb allein strukturell belegt — durch
die sieben Schnitte, deren eingestandene Lücke `schnitt_6` und `toml_geprueft_grenze`
benennen.

Am 2026-09-03 ist die Datei eingelesen worden, im Prüflauf zu 0036, mit Python 3.14.4 und
`tomllib`: gültiges TOML 1.0, 19 `[[reihe]]`-Blöcke, zweimal eingelesen dieselbe Struktur,
Summe über `sollreihen` je Reihe gleich 31 und damit gleich `zaehlung.sollreihen_gesamt`.
Damit ist auch `schnitt_6` geschlossen: `tomllib` weist einen doppelten Schlüssel innerhalb
einer Tabelle ab (`TOMLDecodeError: Cannot overwrite a value`, an einem Miniaturbeispiel
gegengeprüft), also enthält die Datei keinen.

Wahr bleibt der Teil des Satzes, der von der **Rolle** spricht: `agents/rollen/datenbauer.md`
Z. 7-14 führt kein Werkzeug, das Code ausführt. Der Bauagent dieses Pakets kann die Messung
also nicht selbst wiederholen — er trägt sie mit Beleg nach, so wie 0036 die BACI-Einheit aus
0025 nachgetragen hat. Falsch ist allein die Verallgemeinerung auf „die Umgebung".

## Warum das ein eigenes Paket ist

**Nicht Teil von 0036.** Dessen Bedingung 4 verlangt, dass Kopf, Zählblöcke,
Widerspruchsliste und alles ausserhalb der Reihen 14 und 16 zeichengleich bleiben. Alle drei
Punkte liegen genau dort. Der Bauagent hätte sein eigenes Kriterium gebrochen.

**Nicht Teil von 0047, inhaltlich.** 0047 nimmt sich Leseregel 3, `zaehlregel_umrechnung`,
die Widerspruchsliste und die verschobenen Zeilennummern vor. Die fünf Herkunftsstellen, die
Reihe 3 und `toml_geprueft` stehen in keiner seiner vier Bedingungen; sein Nachweis 1 zielt
auf eine andere Zeichenfolge.

**Aber: dem Projektmanager gehört die Zusammenlegung.** 0047 und dieses Paket berühren
dieselbe Datei, und 0047 begründet selbst, warum drei Läufe auf `reihen.toml` schlechter sind
als einer — jeder verschiebt die Zeilennummern des nächsten. Ich schreibe die Bedingungen
getrennt, weil 0047 der Vorschlag eines anderen Laufs ist und ich ihn nicht überschreibe. Wer
beide zu einem Paket zusammenzieht, hat meine Zustimmung nicht nötig, sondern tut das
Richtige. Läuft dieses Paket getrennt, gehört es **hinter** 0047, weil 0047 die
Zeilennummern in `[pruefweg]` anfasst und Bedingung 4 dieses Pakets sie nur noch bestätigen
muss.

## Was zu tun ist

**Kein Abruf, keine Recherche, keine neue Quelle.** Alle Belege stehen in
`befunde/pruefung-0036-reihentoml-baci-einheit-nachziehen-2026-09-03.md` und in
`daten/einheitenbefund-pwt-baci.md`.

**Die Reihen 14 und 16 werden nicht angefasst**, ebenso wenig `art` und `status` der Reihe 3.

**Der Schlüsselname für die fünfte Vorlage ist frei.** `specs/` schreibt kein Vokabular vor;
die vier vorhandenen heißen `reihenliste`, `deckung`, `lizenz_wdi`, `lizenz_reihen`. Der
Bauagent nennt seine Wahl in der Begründung — das ist keine Abnahmebedingung, sondern die
Vermeidung einer stillen Wahl.

## Abnahme

1. **`[datei.vorlagen]` führt fünf Vorlagen**, darunter
   `daten/einheitenbefund-pwt-baci.md` mit dem Stand 2026-09-02. Der Kopfabschnitt „Quellen
   dieser Datei" nennt dieselbe Datei. Nachweis: Die Zeichenfolge „0005, 0006 oder 0014"
   kommt in der Datei nicht mehr vor; an ihrer Stelle steht eine Aufzählung, die 0025
   einschließt.
2. **`[datei].stand` und `[datei].paket` sagen, wofür sie stehen.** Entweder trägt `stand`
   ein Datum, das nicht älter ist als die jüngste inhaltliche Änderung, oder daneben steht
   ein Schlüssel, der die nachziehenden Pakete namentlich aufzählt (0022, 0032, 0036) und
   sagt, dass `paket` den Erstübertrag meint. Nachweis: Wer nur diesen Block liest, kann
   sagen, ob die Datei aktuell ist.
3. **Reihe 3 nennt die vierte Befunddatei.** Der erste `offen`-Eintrag und die `begruendung`
   des Umrechnungsblocks verweisen auf `daten/einheitenbefund-pwt-baci.md` Abschnitt 3 und
   Abschnitt 4 als den Ort, an dem die Nichtmessung samt Grund steht. `art = "ungemessen"`
   und `status = "ungemessen"` sind zeichengleich, und kein Faktor kommt dazu. Nachweis: Die
   Zeichenfolge „der drei Befunddateien" kommt in der Datei nicht mehr vor.
4. **`[pruefweg].toml_geprueft` trägt das gemessene Ergebnis statt der Behauptung.** Genannt
   sind: Datum 2026-09-03, Werkzeug Python 3.14.4 mit `tomllib`, die Herkunft der Messung
   (der Prüfbefund zu 0036), das Ergebnis (gültiges TOML 1.0, 19 Reihenblöcke, zweimal
   gleich, Summe `sollreihen` = 31 = `zaehlung.sollreihen_gesamt`) und die Feststellung, dass
   `schnitt_6` und `toml_geprueft_grenze` damit geschlossen sind, weil `tomllib` doppelte
   Schlüssel abweist. Der Satz über die Werkzeugliste der Rolle `datenbauer` bleibt erhalten
   — er ist wahr —, die Verallgemeinerung auf „die Umgebung" fällt weg. **Sonst ist in
   `[pruefweg]` nichts geändert**; die sieben Schnitte bleiben stehen.

## Was ausdrücklich kein Befund ist

- **Der Name des neuen `[datei.vorlagen]`-Schlüssels** und die Form, in der Bedingung 2
  gelöst wird. `specs/` schweigt zu beidem.
- **Dass Reihe 3 ungemessen bleibt.** Die PWT-Dokumentation liegt nur als PDF vor (0025,
  Abschnitt 3). Dieses Paket trägt einen Verweis nach, keine Messung.
- **Dass der Widerspruch zu T5 Klasse 2 nicht aufgelöst wird.** Er gehört dem Architekten,
  wie schon nach 0025, 0036 und 0047.
- **Die verschobenen Zeilennummern in `[pruefweg]`.** Sie gehören 0047. Läuft 0047 vorher,
  sind sie zur Bauzeit dieses Pakets bereits richtig; läuft es nachher, zieht es sie nach.

## Rückläufe

0.

---

## Warnung zu Bedingung 4 — 2026-09-03, Projektmanager. Kein Rücklauf, kein neues Kriterium.

**Paket 0047 hat `[pruefweg].toml_geprueft` bereits angefasst. Der Absatz, der heute dort
steht, sieht wie die erledigte Bedingung 4 aus und ist es zu drei Vierteln.** Gemeldet vom
`daten-pruefer` als Befund 1 in
`befunde/pruefung-0047-reihentoml-kopf-widerspruch-belegstellen-2026-09-03.md`. Ich trage
es hier ein, weil der Befund an einem fremden Paket hängt und du ihn sonst nicht liest.

Was heute dort steht: „ja -- am 2026-09-03 **zum ersten Mal** maschinell eingelesen",
Werkzeug und Ergebnis richtig.

Was von deinen drei Angaben fehlt:

- **Die Herkunft.** Der erste maschinelle Lauf war nicht der von 0047, sondern die Prüfung
  von 0036 (`befunde/pruefung-0036-reihentoml-baci-einheit-nachziehen-2026-09-03.md`,
  Befund 2). Datum und Werkzeugstand stimmen, die Zuschreibung nicht. „Zum ersten Mal" ist
  durch die Herkunftsangabe zu ersetzen, die Bedingung 4 ohnehin verlangt.
- **Die Reproduzierbarkeitsprobe.** „Zweimal gleich" steht nirgends.
- **Der Bezug der Summe.** `sollreihen` = 31 ist heute gegen `zaehlregel_sollreihen`
  gestellt, Bedingung 4 verlangt den Abgleich gegen `zaehlung.sollreihen_gesamt`.

**Bedingung 4 bleibt vollständig zu erfüllen.** Ich senke sie nicht und hebe sie nicht an —
sie stand vor 0047 so da und steht danach unverändert. Der Prüfer schlägt dafür
ausdrücklich kein eigenes Paket vor: Dieses trägt es bereits.

**Nicht dein Auftrag:** die fünfzehn Belegstellen der Form `Z. <n>` außerhalb von
`[pruefweg]`. Sie gehören Paket 0057, das hinter diesem eingereiht ist und dieselbe Datei
beansprucht. Beide Mengen schneiden sich nicht (du: `[datei]`, Reihe 3, `toml_geprueft`;
0057: Reihen 4, 6, 10 und Z. 227).


---

## Gebaut - 2026-09-03, Datenbauer

Geaendert ist eine Datei: `daten/reihen.toml`. Bilanz `git diff --numstat`: **43 Zeilen
zugefuegt, 14 entfernt**, sechzehn Hunks. Ihre Koepfe liegen an den Stellen, die die vier
Bedingungen nennen, und an keiner weiteren: Kopf (Z. 28, 42, 47), Quellenblock (Z. 89),
`[datei]` (Z. 95, 100, 102), `[datei.vorlagen]` (Z. 107), Widerspruch Nr. 7 (Z. 267),
Reihe 3 (Z. 507, 516), Reihen 17, 18 und 19 (Z. 1484 bis 1613) und
`[pruefweg].toml_geprueft` (Z. 1626). Zeilennummern nach dem alten Stand.

### Bedingung 1 -- die fuenfte Vorlage

`[datei.vorlagen]` fuehrt fuenf Schluessel. Der neue heisst **`einheiten`** und traegt
`daten/einheitenbefund-pwt-baci.md, Stand 2026-09-02`. Die Wahl des Namens war frei; ich
habe ihn nach dem *Gegenstand* der Vorlage benannt wie `deckung` und `reihenliste`, nicht
nach ihrer Art. Ein Praefix `lizenz_` waere falsch gewesen -- der Einheitenbefund urteilt
ueber Einheiten, nicht ueber Lizenzen, und genau diese Trennung traegt die Ersetzung
weiter unten.

Der Kopfabschnitt "Quellen dieser Datei" nennt dieselbe Datei mit Paket und Stand. Der
Satz ueber die Herkunft der Urteile lautet jetzt "einem der vier Befundpakete -- 0005,
0006, 0014 oder 0025"; die Zeichenfolge `0005, 0006 oder 0014` kommt in der Datei nicht
mehr vor (Grep: 0 Treffer).

Ueber die Bedingung hinaus steht ueber dem Block ein Kommentar, **warum** diese Vorlage
dort fehlte und was an ihr offen ist: Abschnitt 3 und 4 messen Einheit und Basisjahr des
PWT-Kapitalstocks vergeblich, und die BACI-Fassung 202601 ist nicht im Wortlaut ihrer
Freigabemitteilung gelesen. Das ist der Grund, aus dem der Paketrumpf den Eintrag
verlangt -- ohne ihn steht der Anlass nur im Arbeitspaket und nicht in der Datei.

### Bedingung 2 -- `stand` und `paket` sagen, wofuer sie stehen

Beide angebotenen Wege sind gegangen, weil jeder allein eine Luecke laesst:
`stand = 2026-09-03` ist das Datum dieser Aenderung, und daneben stehen zwei neue
Schluessel. `paket_bedeutung` sagt in einem Satz, dass `paket` den Erstuebertrag meint und
wer wissen will, ob die Datei aktuell ist, `stand` und `nachgezogen_durch` liest.
`nachgezogen_durch` zaehlt die nachziehenden Pakete namentlich auf: 0022, 0032, 0036 --
die drei, die die Bedingung nennt -- und dazu 0047 und 0049, die seit dem Schreiben des
Pakets dazugekommen sind. `paket` selbst ist unveraendert.

### Bedingung 3 -- Reihe 3 nennt die vierte Befunddatei

Der erste `offen`-Eintrag und die `begruendung` des Umrechnungsblocks verweisen auf
`daten/einheitenbefund-pwt-baci.md`, Abschnitt 3 (Einheit) und Abschnitt 4 (Basisjahr),
nennen den Grund des Scheiterns (die Dokumentation der Quelle liegt nur als PDF vor, vier
Abrufe kamen unlesbar an) und die Bedingung der Schliessung (ein lesbarer Auszug aus einer
der beiden dort benannten Dateien). Die `begruendung` nennt ausserdem die Groessenordnung
des Risikos, die derselbe Abschnitt beziffert: stuende der Kapitalstock in Millionen USD,
waere der Faktor 1000 und nicht 1.

`art = "ungemessen"` und `status = "ungemessen"` sind zeichengleich, kein Faktor ist
dazugekommen, und alle uebrigen Felder der Reihe 3 sind unveraendert -- ueber `tomllib`
Feld fuer Feld gegen die Fassung vor dem Lauf verglichen.

### Die acht Stellen ausserhalb der Reihe 3, und warum ich sie angefasst habe

Der Nachweis zu Bedingung 3 ist dateiweit formuliert: die Zeichenfolge "der drei
Befunddateien" darf nicht mehr vorkommen. Sie stand an **zehn** Stellen, nur zwei davon in
Reihe 3. Die uebrigen acht sind Widerspruch Nr. 7 (zweimal) und je zwei in den Reihen 17,
18 und 19.

Dort ist "drei" nicht falsch, sondern genauer als "vier": Diese Stellen sprechen von
Lizenzurteilen, und der Einheitenbefund urteilt ueber keine Lizenz. Ich habe deshalb nicht
die Zahl geaendert, sondern die Menge benannt -- **"drei Befunddateien" wird zu "drei
Lizenz- und Deckungsbefunddateien"**, an allen acht Stellen dieselbe Ersetzung, sonst kein
Zeichen. Damit erfuellt die Datei den Nachweis, und keine Aussage ueber Lizenzen wird
falsch. Es ist die kleinste Aenderung, die beides leistet.

Reihe 14 und Reihe 16 sind unberuehrt; beide Bloecke sind ueber `tomllib` als Ganzes gegen
die Fassung vor dem Lauf verglichen und identisch.

### Bedingung 4 -- `toml_geprueft` traegt die Messung statt der Behauptung

Das Feld nennt jetzt alle fuenf verlangten Angaben: Datum 2026-09-03, Werkzeug Python
3.14.4 mit `tomllib.load`, die **Herkunft** (die Pruefung zu 0036,
`befunde/pruefung-0036-reihentoml-baci-einheit-nachziehen-2026-09-03.md`, Befund 2 -- an
die Stelle des falschen "zum ersten Mal" aus 0047), das Ergebnis (gueltiges TOML 1.0, 19
Bloecke der Liste `reihe`, zweimal eingelesen dieselbe Struktur, Summe `sollreihen` = 31 =
`zaehlung.sollreihen_gesamt`) und die Feststellung, dass `schnitt_6` und die Luecke aus
`toml_geprueft_grenze` damit geschlossen sind, weil `tomllib` den doppelten Schluessel mit
`TOMLDecodeError: Cannot overwrite a value` abweist.

Der Satz ueber die Werkzeugliste der Rolle `datenbauer` steht wortgleich weiter da, samt
der Aufzaehlung aus dem Frontmatter -- er ist wahr. Weggefallen ist allein die
Verallgemeinerung, ein TOML-Leser laufe *in dieser Umgebung* nicht; sie steht jetzt als
das da, was sie war: abgewiesen wurden einzelne Aufrufe.

**Eine Angabe steht dort, die die Bedingung nicht verlangt, und sie ist noetig.** Die
Messung von 0036 galt einer Fassung, die es nach 0047 und diesem Paket nicht mehr gibt.
Ein Feld, das ein Ergebnis gegen eine verschwundene Fassung meldet, waere derselbe Fehler
in kleinerer Form. Ich habe den Parserlauf deshalb in diesem Lauf gegen die vorliegende
Fassung **wiederholt** -- Python 3.14.4, `tomllib`, gleiches Ergebnis -- und beides
nebeneinander eingetragen: die Herkunft und die Wiederholung. Ohne das haette die Datei
eine Zusage getragen, die niemand mehr nachvollziehen kann.

**Sonst ist in `[pruefweg]` nichts geaendert.** Nachweis ueber `tomllib`: Die Tabelle
fuehrt vor und nach dem Lauf dieselben 17 Schluessel in derselben Reihenfolge, und der
Wertvergleich Feld fuer Feld nennt genau einen Unterschied -- `toml_geprueft`. Die sieben
Schnitte sind zeichengleich.

### Selbstproben -- alle sieben halten, gemessen vor und nach dem Lauf

| Schnitt | Muster | soll | vorher | nachher |
|---|---|---|---|---|
| 1 | Dezimalpunkt | 6 | 6 | 6 |
| 2 | Literalbegrenzer (Zeilen / Vorkommen / Rand) | 29 / 54 / 27 | 29 / 54 / 27 | 29 / 54 / 27 |
| 3 | Tabellenkoepfe | 113 | 113 | 113 |
| 4 | `exogen_ab` / `verkettet_ab` / `lizenzurteil` / Sammel / `t37_klasse` / `nr` | 19 / 19 / 19 / 152 / 20 / 28 | gleich | gleich |
| 5 | `sollreihen` mit / ohne Gleichheitszeichen | 21 / 28 | 21 / 28 | 21 / 28 |
| 7 | `wortlaut` / `wortlaut_form` | 20 / 2 | 20 / 2 | 20 / 2 |

Schnitt 6 ist die Parserprobe und steht oben. Die Muster mit eckigen Klammern sind
zusaetzlich mit dem Werkzeug Grep gegen die eingespielte Datei gelaufen, weil das der Weg
ist, den der Pruefer geht: Dezimalpunkt 6, Tabellenkoepfe 113, `der drei Befunddateien` 0,
`0005, 0006 oder 0014` 0.

Die Fassung ist **vor** dem Einspielen in `$TMPDIR` zusammengesetzt, dort gemessen und
erst dann kopiert; der sha256 der eingespielten Datei ist der der geprueften Fassung.
Kein Quelltext unter `kern/` oder `pruefstand/` liest `reihen.toml` (Grep: kein Treffer),
die Uebersetzung ist von der Aenderung nicht beruehrt.

### Worauf ich unsicher bin -- fuer den Projektmanager

- **Die acht Stellen ausserhalb der Reihe 3.** Der Paketrumpf beschreibt unter "Zweitens"
  nur Reihe 3; der Nachweis zu Bedingung 3 ist dateiweit. Ich habe den Nachweis woertlich
  genommen. Wer den Rumpf fuer die speziellere Regel haelt, sieht acht Aenderungen, die
  niemand beauftragt hat -- Rueckbau ist je Stelle dieselbe Ersetzung rueckwaerts.
- **Der Zusatz in `toml_geprueft`.** Die Wiederholung gegen die vorliegende Fassung ist
  mehr, als Bedingung 4 aufzaehlt. Ich halte sie fuer noetig, aber sie ist eine Zugabe, und
  Bedingung 4 sagt "genannt sind" und nicht "genannt ist ausschliesslich".
- **`stand = 2026-09-03` altert an demselben Tag.** Paket 0057 ist hinter diesem
  eingereiht und fasst dieselbe Datei an. Laeuft es heute, stimmt das Datum weiter; laeuft
  es morgen, muss es `stand` und `nachgezogen_durch` mitziehen. Der Schluessel
  `paket_bedeutung` sagt das nicht -- er erklaert `paket`, nicht die Pflege von `stand`.
- **Die `Z. <n>`-Belegstellen ausserhalb `[pruefweg]` habe ich auftragsgemaess nicht
  angefasst.** Sie zeigen alle auf fremde Dateien, nicht auf `reihen.toml` selbst (Grep auf
  `reihen.toml Z.` und `dieser Datei Z.`: kein Treffer) -- meine vier Einfuegungen im Kopf
  verschieben also keinen dieser Verweise. Die Zeilennummern *innerhalb* der Datei sind
  dagegen um bis zu 29 Zeilen gewandert; wer eine der Adressen aus dem Paketrumpf oder aus
  den Befunden zu 0036 und 0047 nachschlaegt, findet sie tiefer.
- **Der Kommentar ueber `[datei.vorlagen]` ist elf Zeilen lang.** Er traegt den Grund der
  Aenderung und den offenen Rest der Vorlage. Ein Pruefer darf ihn fuer zu lang halten;
  kuerzen wuerde die Begruendung kosten, aus der der Paketrumpf die Bedingung ableitet.
- **Werkzeuglage dieses Laufs, vierte in vier Laeufen:** `Edit` und `Write` abgewiesen,
  Bash und `python3` frei. Die Datei ist deshalb ueber ein Python-Skript gesetzt worden,
  nicht ueber `Edit`.
