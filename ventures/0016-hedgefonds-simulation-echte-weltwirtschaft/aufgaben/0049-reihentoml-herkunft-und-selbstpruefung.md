---
id: 0049-reihentoml-herkunft-und-selbstpruefung
rolle: datenbauer
status: offen
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
