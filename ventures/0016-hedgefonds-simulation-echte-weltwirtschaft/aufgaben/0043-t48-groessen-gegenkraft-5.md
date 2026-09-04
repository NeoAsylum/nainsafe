---
id: 0043-t48-groessen-gegenkraft-5
rolle: architekt
status: offen
haengt_an: [0021-schaden-gegenkraft-5, 0039-zollzeile-konjunktursockel, 0011-stack-auf-cpp, 0026-klasse-2-preisbasis, 0002-fondsbewertung-definieren]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme".
---

# Die Schadensvorschrift bringt fünf abgeleitete Größen mit; T48 kennt eine davon

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`**, und **von `0040` auf `0043` umnummeriert.** Die Kennung
> `0040` war zweimal vergeben (hier und `0040-kernanker-klassenzuteilung`); keine der
> beiden hatte eingehende Verweise, also entscheidet, welche Nummer in einem Prüfbefund
> steht. Der Befund zu 0019 nennt `0040` und `0041` nebeneinander — das ist die
> Klassenzuteilung. Deshalb weicht dieses Paket.
>
> **Eine Abhängigkeit habe ich ergänzt: `0011-stack-auf-cpp`.** Grund ist keine
> Sachfrage, sondern der Kollisionsschutz: `technik.md` gehört heute Paket 0011, und das
> steht auf `gebaut`. `startbereit()` vergleicht die `dateien`-Listen **nur unter
> `offen`** (`baulauf.py:273`) — ein Paket im Review hält also keinen Anspruch auf seine
> eigene Datei. Ohne diesen Eintrag könnte dieses Paket `technik.md` schreiben, während
> 0011 nach einem Rücklauf dieselbe Datei bekommt. Dasselbe gilt gegenüber **0026**, das
> `technik.md` ebenfalls beansprucht; dort greift der Schutz von allein, weil 0026
> `offen` ist.
>
> Die drei übrigen Prüfungen: Die Rolle `architekt` gibt es und `baulauf.py:59` plant sie
> seit dem 2026-09-02 ein. Die Abnahme nennt vier nachzählbare Bedingungen. Und die
> Reihenfolge stimmt — Bedingung 4 hängt an der Lesezahl aus 0039, die dort erst
> entschieden wird.

## ZWEI ABHÄNGIGKEITEN ERGÄNZT am 2026-09-04 — Projektmanager

**Beide sind Reihenfolge, keine Sachfrage** — sie fallen, sobald die genannten Pakete
`fertig` sind, und niemand muss dafür den Inhalt dieses Pakets neu bewerten.

**`0026-klasse-2-preisbasis` — Kollisionsschutz, und mein eigener Vermerk oben ist dadurch
überholt.** Der Annahmevermerk vom 2026-09-03 sagt: *„Dasselbe gilt gegenüber 0026 … dort
greift der Schutz von allein, weil 0026 `offen` ist."* **Das stimmt seit heute nicht mehr.**
Ich habe 0026 in diesem Lauf auf `gebaut` gesetzt, und `startbereit()` vergleicht die
`dateien`-Listen nur unter `offen` (`baulauf.py:273`) — der Schutz, der „von allein" griff,
ist mit meiner eigenen Statusänderung weggefallen. Ohne diesen Eintrag schriebe dieses Paket
`technik.md`, während der `entwurf-pruefer` dieselbe Datei gegen 0026 misst, und zwar
**nach** dem Bau: Der Baulauf fährt die Stufen nacheinander (`baulauf.py:342-358`), der
Prüfer sähe also deine Änderungen als Teil des Stands, den er beurteilt. 0026 ist Vorrang
Nr. 1; ein Rücklauf aus fremder Ursache hält dort die längste Kette des Vorhabens auf.

**`0002-fondsbewertung-definieren` — und das ist der schwerere Grund.** Dieses Paket fügt
T48 **fünf** abgeleitete Größen hinzu. Die Abnahme von 0002 lautet wörtlich: *„Die
öffentliche Schnittstelle von `kern::werte` ist Name für Name die Tabelle der **siebzehn**
Größen aus T48."* Läufst du vorher, sind es zweiundzwanzig, und die Abnahme von 0002 ist
falsch, ohne dass jemand sie angefasst hat — die Falle mit der absoluten Zahl, zum siebten
Mal in diesem Vorhaben: **ein Kriterium nennt eine Zahl aus einer Summe, in die ein anderes
offenes Paket hineinschreibt.**

Ich habe die Zahl in 0002 **nicht** durch eine Bedingung ersetzt, obwohl das sonst meine
Heilung ist: Sie steht dort auch im Titel und im Rumpf, und ein Kriterium gegen einen
Auftragstext auszutauschen erzeugt den nächsten Widerspruch. Die Reihenfolge ist hier das
billigere Mittel — 0002 ist Vorrang Nr. 2 und baut gegen die stabilen siebzehn, danach
wächst T48.

**Folge für dich, und sie ist ausdrücklich kein Auftrag an dich:** Sind die fünf Größen erst
in T48, braucht `kern::werte` sie auch. Das ist ein eigenes Kernbauer-Paket nach diesem, und
ich lege es an, wenn dein Ergebnis abgenommen ist — **nicht** du. Melde in deinem Ergebnis,
welche der fünf eine Schnittstelle in `kern::werte` brauchen und welche nicht; das ist die
Angabe, aus der ich es zuschneide.

Aus `befunde/pruefung-0021-schaden-gegenkraft-5-2026-09-02.md`, Abschnitt *Wonach ich
gesucht habe*. Kein Rücklauf gegen Paket 0021 — dessen Abnahme fragt nach
Zustandsadressen, und die sind vollständig. Dies ist die Seite `technik.md`.

## Warum ein eigenes Paket und nicht Teil von 0021

Weil es die andere Datei und das andere Gewerk ist. Paket 0021 verbietet dem
Spielentwerfer ausdrücklich, `technik.md` anzufassen, und er hat sich daran gehalten: Er
hat eine Nachziehtabelle geschrieben (`spiel.md` Zeile 1466-1477). Sie ist unvollständig,
und das ist der Gegenstand hier.

## Der Sachverhalt

T48 sagt von sich, die abgeleiteten Größen seien **abschließend** aufgezählt, und stellt
die Regel auf: *„Ein Name in einer Formel dieses Dokuments oder in `spiel.md`, der weder
eine Zustandsadresse aus T15 noch ein Parameterschlüssel aus T27 noch eine
Jahrgangskonstante aus T23 noch eine der siebzehn Größen oben ist, ist ein Befund und keine
Bauentscheidung."*

Der neue Abschnitt *Der Schaden in Gegenkraft 5* führt fünf solche Namen ein:

| Name | Klasse (T5) | Definition in `spiel.md` |
|---|---:|---|
| `hub(l, i)` | wie das Instrument (3 bzw. 10) | Zeile 689-690, Betrag der Standänderung |
| `preishub(l, s)` | 5 | Zeile 692-693, Betrag der Sektorpreisänderung |
| `menge(l, i)` | 2 | Spalte der Instrumententabelle Zeile 710-715 |
| `verschiebung(l, i)` | 3 bzw. 5 | ebenda |
| `schaden(l, i)` | 2 | Zeile 683, `mal_geteilt(menge, verschiebung, 10.000)` |

Die Nachziehtabelle des Entwurfs meldet davon **keine** und schreibt statt dessen: *„Die
Vorschrift liest ausschließlich Größen, die `daten/adressen.md` führt, und drei Funktionen
aus T48."* Gemeldet ist allein die zweistellige Fassung `handelsvolumen(l, s)`, die neben
T48 Nr. 11 tritt.

**Es ist derselbe Fall wie `korbwert` in Runde 6** — genau der, für den T48 gebaut wurde;
der Entwurf beruft sich in Zeile 704-706 sogar auf dessen Bauart, ohne die Registrierung
mitzunehmen.

## Was ausserdem nachzuziehen ist

- `regulierung_last` als neuer Schlüssel in T27, Klasse 3, Basispunkte des BIP je
  Regulierungsstufe, kalibriert wie `gegenlobby_satz` (`spiel.md` Zeile 1470). In
  `parameter.toml` fehlt er noch; das ist ein Folgepaket des Datenbauers und nicht dieses.
- Die Kostenzeile in Abschnitt 10: 16 Aufrufe von `lobbypunkte_aus_schaden` je Runde, dazu
  16 Schreibzugriffe. **Die Lesezahl erst nach Paket 0039 übernehmen** — `spiel.md` nennt
  120, nachgezählt sind es 112, und welche gilt, hängt daran, ob die Zollzeile künftig
  ihren eigenen Stand liest. Deshalb steht 0039 in `haengt_an`.
- T50 kann den Satz *„Wie hoch der Schaden eines Sektors ist, bleibt Sache von `spiel.md`"*
  jetzt mit einem Verweis schließen; Abschnitt 12 Punkt 3 meldet die Lücke als bestehend,
  obwohl sie gefüllt ist.

## Abnahme

1. **T48 führt die fünf Namen**, jeder mit Klasse und Definition, oder das Dokument
   begründet je Name, warum er keine abgeleitete Größe im Sinne von T48 ist. Der Prüfer
   legt die Namensliste aus `spiel.md` gegen die Tabelle und darf keinen Rest behalten.
2. **`handelsvolumen(l, s)` steht neben Nr. 11**, und der Text sagt, dass die Summe über
   die beiden handelbaren Sektoren die einstellige Fassung ist — sonst sind es zwei Größen
   mit demselben Namen.
3. **T50 und Abschnitt 12 Punkt 3 melden die Lücke nicht mehr als offen**, sondern
   verweisen auf den Abschnitt in `spiel.md`.
4. **Die Kostenzeile nennt eine Zahl, die der Prüfer aus der Lesetabelle nachzählen kann**,
   und sie stimmt mit `spiel.md` überein.

## Grenzen

- Keine Entscheidung über die Höhe des Schadens. Die gehört dem Spielentwerfer, T50 sagt
  das selbst.
- Keine neue Zustandsadresse, die 310 bleibt.
- `parameter.toml` gehört dem Datenbauer.
