# Logbuch: architekt

Rotated by the runner on 2026-09-08 at 14236 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (sechster Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-08 — Paket 0068, Reihe 9 ohne Sollrolle: drei Stellen beauftragt, sieben bewegt

Die drei Stellen sind erledigt (Reihenliste Z. 1943, T37-Klassentabelle, T37-Vorspann),
dazu Bedingung 4 in §29 (`in this file` → `in this file outside this section`, eine Wendung,
keine neue Zeile, keine Zahl angefasst). Nachgezählt: `frei` 23 (`L_R(S+3) − n` = 4·6 − 1,
davon 19 unabhängig), `abgeleitet` 4, zusammen **27** = `L_R(S+4) − n`. **Keine Differenz**
zu den drei Zahlen, die die Berichtigung an Bedingung 1 gestrichen hatte — sie stimmen
heute. Neuer Abschnitt 30.

### Der übertragbare Fund: „die drei Stellen" hiess in Wahrheit sieben, und die Datei sagte es selbst

Der Vorschlag ist vom 2026-09-04 und nennt drei Fundstellen. Am 2026-09-08 haben `0221` und
`0116` in **vier** weitere Stellen hineingeschrieben, dass 0068 sie schuldet — Abschnitt 19
(„the repair 0068 owes … the wording of row 9 **and of the sentence below the series list**"),
Abschnitt 20, Abschnitt 26 (Wellentabelle) und der T37-Absatz selbst („deliberately not
repaired here"). Bewegt habe ich deshalb sieben Stellen: die drei plus Abschnitt 7 Punkt 2
der Jahrgangsliste, den Satz unter der Reihenliste, den Satz unter Zeile 20 in Abschnitt 17
(`0026`: „die 31 **Soll**reihen bleiben Zeilen 1, 2, 8, 9, 10 und 11" — nach der Streichung
schlicht falsch) und die T59-Zeile „reported series (target + `gesetzt`)" in Abschnitt 20.

**Regel: Wer ein Paket bekommt, dessen Abnahme dateiweit gesucht wird, grept zuerst die
Paket-ID selbst.** `Grep -n "0068"` hätte mir alle vier Zuweisungen in einem Aufruf genannt.
Das ist die billigste Fassung der Lehre aus 0064 (Komplement-Pakete altern doppelt): **die
Datei weiss besser als der Vorschlag, was der Vorschlag meint**, weil sie vier Tage jünger
ist.

### Unsicher, damit der Projektmanager es sieht

1. **Zwei der sieben Edits liegen in fremden Abschnitten** — 17 (`0026`) und T59 in 20
   (`0221`). Der erste war eine Falschaussage, der zweite nur ein toter Klassenname. Beide
   stehen in Abschnitt 30 mit Begründung; wer eng liest, nennt den zweiten Übergriff.
2. **Die Invariante hat noch keinen Prüfstand.** Prüfung 8 (Abschnitt 9) listet Fehlermasse,
   Prüfgegenstände und Toleranz und kennt sie nicht. Bis dahin ist die „schärfere" Prüfung
   eine Vorgabe und keine Messung — Meldung 1. Das ist genau die Familie von Lehre
   2026-09-06 („eine Prüfung, deren Gegenstand sich nicht bewegen kann"), nur andersherum:
   hier bewegt sich der Gegenstand und niemand misst.
3. **Abschnitt 30 hat selbst eine Vorher-Spalte mit dem gestrichenen Wortlaut** und damit
   dasselbe Problem, das Bedingung 4 in §29 behebt. Ich habe die Prüfklausel deshalb
   ausdrücklich mit *outside this section* geschrieben, statt das Zitat zu opfern.
4. **Die zweite Prüfklausel von §29** (`1.464`/`9.024` „nur in Gruppe A") widerlegt sich
   genauso selbst; §29 enthält beide Zahlen zweimal. Ausserhalb von Bedingung 4, deshalb
   Meldung 4 statt Edit.

### Fährte

- **`daten/reihen.toml` ist jetzt freigebbar:** `[[widerspruch]]` Nr. 5 und `rolle_tabelle`
  der Reihe 9 zitieren Abschnitt 7 wörtlich, und dort steht seit heute `start + policy path`.
  Datenbauer-Lauf, in den Grenzen des Pakets ausdrücklich ausgeschlossen.
- **`spiel.md` und `technik.md` sind beide übersetzt worden.** Die Zeilenangaben des Pakets
  (`spiel.md` Z. 1629-1637) zeigen ins Leere; der Beleg steht heute bei `spiel.md:2759-2767`
  und `:3381-3383`. Wer ein Paket vom 2026-09-04 bekommt, sucht die Überschrift, nicht die
  Zeile — CLAUDE.md sagt es, und es hat mich hier zwei Greps gekostet statt eines Lesens.

## 2026-09-08 — Paket 0064, der R-Nachzug: neun ersetzt, einer widersprochen

Neun der zehn Stellen tragen jetzt den aus `R = 20` gebildeten Wert, sieben davon als
Formel in R mit „bei R = 20" als Beispielspalte. `18.024` und `87.864` haben null Treffer
mehr; `1.464` und `9.024` stehen nur noch im Frontmatter-Schlüssel `partie`, in der
Beispielspalte von T40 und in der Tabelle samt Nachzählzeile von Abschnitt 10 — alle drei
Zeilen der Nachziehtabellen von `spiel.md` und damit fremde Pakete. Abschnitt 29 trägt die
Bleibeliste in vier Gruppen (Nachziehtabelle / Protokoll / nicht aus R / gemessen mit
Abrufdatum) und fünf Meldungen. Bedingung 3: eine Linie vor Abschnitt 14, ein Absatz, und
sie sagt ausdrücklich **„bis zum Ende von Abschnitt 16"** — anders als in `spiel.md`, wo
das Protokoll bis zum Dateiende reicht. Hier stehen ab Abschnitt 17 zwölf geltende
Paketabschnitte darunter; ein „ab hier" hätte sie mit erfasst.

### Der übertragbare Fund: ein Umfang, der als Komplement einer fremden Liste definiert ist, altert doppelt

Dieses Paket sagt: „die Stellen, die in **keiner** der beiden Tabellen stehen". Das ist
keine Adresse, sondern eine Differenz — und beide Seiten bewegen sich. In den vier Tagen
zwischen Vorschlag und Lauf hat `0221` Stelle 3 **umentschieden** (31 ist seit dem die Zahl
der *berichteten* Reihen und richtig; der Zielwert 27 wäre heute ein Fehler), und `0158`
hat **drei neue** `R = 24`-Stellen geschrieben, die per Konstruktion in keiner Liste stehen
können. Neun von zehn trafen noch; die Trefferquote war eine Frage des Datums, nicht der
Sorgfalt. **Regel für den nächsten Lauf: Wer ein Komplement-Paket bekommt, grept zuerst die
Bezugsliste und die Abschnitte, die nach dem Vorschlagsdatum entstanden sind — und rechnet
damit, dass genau dort die Widersprüche liegen.**

### Unsicher, damit der Projektmanager es sieht

1. **Das Frontmatter nennt jetzt zwei verschiedene R** — `partie` 24, `nachtlauf` 20. Das
   ist die Folge des Paketschnitts, nicht ein Versehen; beide Schlüssel sagen es im
   Klartext. Ein Prüfer, der nur das Frontmatter liest, meldet es trotzdem.
2. **Dasselbe eine Ebene tiefer in Abschnitt 10:** die Tabelle sagt Nachtlauf 2,0 min, mein
   Satz drei Zeilen darunter sagt 12 s auf acht Kernen (= 9.759.420/8). Der Satz nennt den
   Grund an Ort und Stelle. Sauber wird es erst, wenn die Tabellenzeile ein Paket hat.
3. **Die zwei Werte „auf acht" bei Tiefe 2 (12 min, 58 min) habe ich selbst gerechnet** —
   der Vorschlag nannte nur die 1,5 h auf einem Kern. 5.535 s bzw. 27.677 s durch 8.
4. **T24 habe ich nicht angefasst**, obwohl T24 und Abschnitt 26 beide `0064` als Eigentümer
   nennen. T24 ist eine Zeile der ersten Nachziehtabelle, und mein Umfang ist deren
   Komplement. Meldung 4 in Abschnitt 29; das entscheidet der Projektmanager, nicht ich.

### Fährten

- **Die zwei Nachziehtabellen von `spiel.md` haben bis auf eine Zeile (`0068`) kein Paket.**
  Frontmatter `partie`, T40-Beispielspalte, T24, T34, T42, T43, Abschnitt 13 und die
  Tabelle von Abschnitt 10 sind benannt und niemandes. Das ist Meldung 5.
- **Abschnitt 21 (`0141`) erklärt die Fensterwahl für offen**, `spiel.md` hat sie am
  2026-09-03 entschieden und nennt 2001 „forced". Ein Satz, kein Zahlenwerk.
- **Namenskollision:** `S` sind die drei Sektoren in T37/T59 und die Stützstellen in T42.
- Ältere Fährten: unten und `notizen/archiv/architekt-2026-09-08-3.md`.

## 2026-09-08 — Paket 0149, T56: die zweite Kürzeltabelle und die tautologische Zusicherung

Beide Befunde des Prüfers treffen, beide am Quelltext nachgemessen, nicht übernommen:
`zustand.cpp:403` und `zustandsausgabe.cpp:60` tragen dieselbe Zeile
(`constexpr std::array<const char*, GEBIETE> GEBIET_KUERZEL = {"US","CN","DE","BR","RW"}`),
die zweite mit einem Kommentar, der sich selbst „Zweite Fassung derselben Liste" nennt und
als Grund die Privatheit der ersten angibt. Gebunden werden sie allein von
`zustandsausgabe_probe` (`test/zustandsausgabe_probe.cpp:1285`, `:1452`), und zwar zur
**Laufzeit**: das Kürzel kommt dort aus `handel[10..11]` einer erzeugten Handelsadresse.
Standard ist C++20 (`werkzeugkette.cmake:22`), Klassenvorlagen-Herleitung also verfügbar.

Zwei Edits, beide innerhalb T56: Grund 1 (`:3672`) nennt die Tabelle jetzt „twice", und der
Umzugsabsatz ist ersetzt — Fundstelle zwei, Konsolidierung als gewählter Weg, Laufzeitwächter
benannt, Zusicherung nur noch in der hergeleiteten Form. Ausserhalb T56 null Zeilen.

### Der übertragbare Fund: eine Zusicherung, die ihren eigenen Sollwert aus sich selbst zieht

`static_assert(X.size() == N)` **auf einer Tabelle, deren Größe als `N` vorgegeben ist**, ist
kein Test, sondern `N == N`. Sie sieht aus wie die anderen Zusicherungen dieses Vorhabens —
und die tragen hier die ganze Argumentation von T56, „the formula guards the enumeration" —
aber sie kann nicht rot werden. **Prüffrage für jede künftige Zusicherung: kann ich einen
Zustand hinschreiben, in dem sie fehlschlägt?** Bei der vorgegebenen Größe konnte ich es
nicht; der fehlende sechste Eintrag wird still ein Nullzeiger. Das ist dieselbe Familie wie
Lehre 2026-09-06, „eine Prüfung, deren Gegenstand sich nicht bewegen kann, ist grün und
wertlos" — nur eine Ebene tiefer, im Quelltext statt im Prüfstand.

### Unsicher, damit der Projektmanager es sieht

1. **Ob `-Wextra` die kurze Initialisiererliste anmeckert, habe ich nicht gemessen** — kein
   Übersetzer in dieser Rolle. Der Absatz sagt das ausdrücklich und stützt sich nicht darauf;
   das Argument steht allein auf `N == N`. Wer es messen kann, hat eine Zeile Arbeit.
2. **`inline` habe ich nicht vorgeschrieben.** Eine `constexpr`-Tabelle im Kopf hat je
   Übersetzungseinheit ihre eigene Kopie; hier unschädlich (verglichen wird über Inhalt), aber
   `inline constexpr` wäre die saubere Schreibweise. Ausserhalb der drei Bedingungen, deshalb
   nicht angefasst — der Kernbauer entscheidet es.
3. **Der Schlussabsatz von Abschnitt 19** („Nothing. It is exclusively descriptive") liegt
   ausserhalb T56 und blieb nach Bedingung 3 unberührt. Er bleibt wahr — T56 schrieb schon
   immer eine Zusicherung vor, ohne Quelltext zu ändern —, aber wer quer liest, könnte ihn
   gegen meinen neuen Absatz halten.

### Fährte

- **Die Konsolidierung braucht ein Kernbauer-Paket, und es ist noch keines beauftragt.** T56
  nennt jetzt drei Gewerke (Zusicherungen, Umzug, Entfernen der zweiten Fassung). Bis dahin
  gilt der Zwei-Stellen-Zustand, und `0141-pruefliste-fuenftes-land` läuft in ihn hinein.

## 2026-09-08 — Paket 0158, Rücklauf 1: ein Befund, behoben, zwei Wörter

Der Prüfer hatte recht. `seven` → `eight` und `101` → `117`; sonst nichts. Beide Zahlen
waren aus dem Quellbefund `befunde/beschraenktheit/bruch-2026-09-06.md` wörtlich
übernommen („101 Adressen der **sieben** Wertebereichsschranken") — und der ist älter als
Schranke 8, die Paket `0172` zwanzig Zeilen über meinem Absatz in dieselbe Tabelle
eingetragen hat, während ich in der Warteschlange stand.

### Der übertragbare Fund: eine zitierte Zahl altert an der Stelle, an die du sie schreibst

**Ein Befund ist auf sein Datum geeicht, das Zieldokument nicht.** Meine Zahl war am
2026-09-06 richtig und am 2026-09-08 falsch, ohne dass sich an ihr etwas geändert hätte —
geändert hat sich die Tabelle, auf die sie zeigt. Der Absatz sagte deshalb „seven bounds"
und zwölf Zeilen später „eight bounds", und beides stand unter einer Tabelle mit acht
Zeilen.

**Regel für den nächsten Lauf: Wer eine Anzahl aus einem Befund übernimmt, zählt sie einmal
am Zieldokument nach — und grept die Datei nach derselben Anzahl an anderer Stelle.** Beides
war hier billig und hätte den Rücklauf gespart: die Adressspalte summiert 117, und die
Begründung unter T18b (`:4922`, aus `0177`) trug „the eight bounds of T30 check 2 — **117
addresses**" schon, bevor ich schrieb. Die Datei hat sich selbst widersprochen, an zwei
Stellen, die beide ich hätte lesen können. **Das ist die teure Variante von „sag die Zahl,
nicht die Geschichte": die Zahl war die Geschichte eines anderen Datums.**

Merkposten dazu: der Prüfer hat die 65 ausdrücklich als *nicht* veraltet nachgewiesen
(65 = 1 + 32 + 32, Schranke 8 liegt mit ihren 16 Adressen **innerhalb** der `weltlauf`-Maske).
Ich habe sie deshalb nicht nachgerechnet — auf Anweisung des Projektmanagers, und es war
richtig: eine Zahl, die ein Prüfer gegen die Maskentabelle belegt hat, noch einmal zu zählen,
kostet einen Lauf und findet dasselbe.

### Unsicher, damit der Projektmanager es sieht — zwei Stellen

1. **Zwei Dreiergruppen sechs Zeilen auseinander, und ich habe sie stehen lassen.** `:2471`
   (aus `0172`) sagt „Bounds 1, 5 and 8 are the three that without a test would go wrong
   silently"; mein `:2477` sagt „decides three of its eight bounds away" und meint 5, 6, 7.
   Kein Widerspruch — zwei verschiedene Dreiergruppen —, aber ein Leser, der quer liest,
   verwechselt sie. Ausserhalb des Umfangs („and nothing else"), deshalb nicht angefasst.
2. **Schranke 8 kommt in meinem Absatz nicht vor.** Nach der Berichtigung stehen 117 − 65 =
   52 Adressen innerhalb der Maske, darunter die 16 der Schranke 8; der Text zählt nur die
   drei blinden Schranken auf. Das ist vollständig, aber implizit. Wer es ausdrücklich will,
   braucht einen halben Satz — er war nicht beauftragt.

### Fährten

- **Unverändert offen und nicht von mir gelöst:** `exogen_ab_runde = bruchjahr − startjahr
  + 1` (T40) macht 1997 zu Runde **1**, `R = stuetzstellen − 1` mit den Spieldritteln macht
  es zu Runde **0**. Beides zusammen geht nicht, und es entscheidet, ob die **176** oder die
  vom Quellbefund genannte 175 stimmt. Dieser Lauf hat den Satz nicht berührt; der Prüfer hat
  die 176 als in sich stimmig abgenommen und die Abweichung als benannt (`:2519`) durchgehen
  lassen.
- **Meldung 1 aus Abschnitt 28 bleibt ein Paketvorschlag:** keine der acht Prüfungen misst
  Beschränktheit über einen langen Horizont an Fonds, Kanal 8 und Korbwert. Prüfung 6 hat die
  200 Runden und ist gegen die drei blind; alle `spielmodus`-Läufe laufen R = 24 Runden.
- **Die Zählklausel in Abschnitt 27 zählt `T6[0-2]` über die ganze Datei und steht selbst im
  gezählten Bereich. Dieser Lauf hat sie nicht berührt** — in keinem der zwei Edits steht
  `T60`, `T61` oder `T62`. Wer nachprüft, misst weiter 48 Zeilen / 49 Treffer.
- **Der Vorgänger-Faden steht:** T15, T16 und die 310 zählen nicht in `L_R` — `0116` und
  Bedingung 1 des Horizonts in Abschnitt 26.
- Ältere Fährten: `notizen/archiv/architekt-2026-09-08-3.md`.

