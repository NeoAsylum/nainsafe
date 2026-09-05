---
typ: messung
paket: 0107-kennzeichen-gegen-nachbarmeldungen
rolle: testentwickler
datum: 2026-09-05
bezugsstand: 564d4b8
geaenderte_dateien: [kern/test/schritt_probe.cpp]
---

# Die Eindeutigkeit der Kennzeichen ist jetzt gemessen

Geaendert wurde **eine** Datei, `kern/test/schritt_probe.cpp`. `kern/src/schritt.cpp` und
`kern/src/zustand.cpp` gehen unveraendert aus diesem Lauf hervor; jede Sabotage unten lief
auf einer *Kopie* der Probe, die Quellen des Kerns hat keine davon je beruehrt.

## Was zugesichert wird

Ein Satz: **Die Kennzeichenliste einer Abbruchstelle passt genau auf die Meldungen ihres
eigenen Riegels.** Zwei Haelften, beide gebraucht.

1. *Auf keine fremde.* Die Haelfte, um die es dem Paket geht. Wer eine Liste auf ein
   Allerweltsstueck verkuerzt, kollidiert sofort mit fremden Meldungen.
2. *Auf jede eigene.* Die Haelfte, die den Ausweg schliesst: Wer die verkuerzte Liste
   behalten will, koennte ihren Riegel zu dem erklaeren, mit dem sie kollidiert -- und
   Haelfte 1 schwiege, weil nur noch fremde Paare geprueft werden. Haelfte 2 macht daraus
   einen Tausch statt eines Auswegs.

Gerechnet wird ueber Dinge, die beide im selben Lauf entstehen. **Kein Wortlaut ist in die
Datei gewandert**; die Warnung aus 0085 gegen den Volltextvergleich bleibt gewahrt.

Dazu zwei Riegel gegen die stille Aushoehlung: Die Pruefung verlangt, dass zu **jedem** der
fuenf Riegel in diesem Lauf eine Meldung angekommen ist, und dass die Zahl der geprueften
Paare in beiden Klassen groesser null ist.

## Der ausgelieferte Stand, gemessen

```
  Kennzeichen: 7 Meldungen aus 5 Riegeln, 38 fremde und 4 eigene Paare geprueft, 0 Verletzung(en)
schritt_probe: alle Pruefungen bestanden
```

Sieben Meldungen aus fuenf Riegeln ergeben 7x6 = 42 geordnete Paare, davon 4 innerhalb
eines Riegels (die beiden Stellen an der oberen Rundenschranke und die beiden negativen
Rundennummern, je zweimal geordnet) und 38 zwischen Riegeln. Beide Zahlen stehen in der
Ausgabe, damit eine spaetere Umstellung, die Paare verliert, an der Zahl auffaellt und
nicht am ausbleibenden Fund.

**Die fuenf heutigen Listen sind unveraendert.** Nachgemessen, nicht angenommen: Alle
Zeichenkettengruppen der Datei wurden aus dem Stand `564d4b8` und aus dem Auslieferstand
gezogen und verglichen -- sieben Vorkommen, fuenf verschiedene Listen, Menge identisch. Die
Zusicherung war fuer kein einziges Textstueck ein Anlass, es nachzuziehen.

## Die Sabotagen -- sechs Mutanten, jede Teilregel einmal rot

Getrieben von `bau/kp0107_mutanten.py` (unter `bau/`, also nicht Teil des
Auslieferstands). Jede Ersetzung prueft vorher, dass ihr Suchmuster genau einmal vorkommt;
ein Mutant, dessen Muster nicht mehr passt, faellt auf, statt still nichts zu tun.

| Mutant | Eingriff | Ergebnis |
|---|---|---|
| `kontrolle_unveraendert` | keiner | **gruen**, 0 Verletzungen |
| `m1_liste_verkuerzt` | `spielmodus`-Liste auf `{"kern::schritt"}` | **rot**, 4 Verletzungen |
| `m2_verkuerzt_und_umetikettiert` | wie m1, dazu fremder Riegel als eigener genannt | **rot**, 4 Verletzungen + fehlender Riegel |
| `m3_liste_ueberangepasst` | eine Liste trifft nur einen von zwei Faellen ihres Riegels | **rot**, 1 Verletzung |
| `m4_stelle_stumm` | zum Riegel `spielmodus` kommt keine Meldung mehr an | **rot**, fehlender Riegel |
| `m5_sammlung_tot` | die Sammlung nimmt nichts mehr auf | **rot**, 5x fehlender Riegel + beide Paarzaehlungen |

### m1 -- die vom Paket verlangte Abschwaechung

An der Quelle wurde **nichts** geaendert, nur die Liste verkuerzt. Die rote Zeile nennt die
Stelle und die fremde Meldung, auf die die Liste ebenfalls passt:

```
FEHLGESCHLAGEN Zeile 768: Modus spielmodus -- die Kennzeichenliste dieser Stelle
kennzeichnet nicht: Sie passt auch auf die Meldung des Riegels "obere Rundenschranke"
(Stelle "Runde nach der letzten zaehlbaren").
  fremde Meldung: "kern::schritt -- partie.runde der Vorrunde ist 9223372036854775807 und
  damit der groesste int64_t: eine naechste Runde laesst sich nicht mehr zaehlen. Gelesen
  aus partie.runde (Nr. 307)"
```

Dieselbe Stelle kollidiert ausserdem mit beiden negativen Rundennummern und mit dem
dritten Fall der Rundennummernprobe -- vier Verletzungen, alle mit ausgeschriebener
Fremdmeldung. Die Zaehlung `38 fremde Paare` bleibt dabei gleich; verkuerzt wird eine
Liste, nicht der Bestand.

### m2 -- der Ausweg, und dass er keiner ist

Der interessante Mutant: Wer m1 behalten will, koennte die Stelle als `ObereRundenschranke`
etikettieren. Dann schweigt Haelfte 1 fuer dieses eine Paar -- und Haelfte 2 spricht:

```
FEHLGESCHLAGEN Zeile 644: Runde nach der letzten zaehlbaren -- diese Stelle und "Modus
spielmodus" nennen beide den Riegel "obere Rundenschranke", aber die Liste der ersten
passt nicht auf die Meldung der zweiten. Entweder sind es zwei Riegel und nicht einer,
oder die Liste greift zu eng.
```

Dazu meldet die Vollzaehligkeit den nun unvertretenen Riegel `spielmodus`. Der Tausch
kostet also mehr, als er einbringt -- genau das war die Absicht.

### m3 -- Haelfte 2 allein, ohne jede andere Regel

Die Liste des Falls `partie.runde = -1` wurde von `"damit negativ"` auf
`"ist -1 und damit negativ"` verschaerft. Sie passt weiter auf ihre eigene Meldung, sie
kollidiert mit keiner fremden, alle fuenf Riegel sind vertreten -- **nur** die zweite
Haelfte schlaegt an, weil dieselbe Liste den Geschwisterfall mit dem kleinsten `int64_t`
nicht mehr trifft. Das ist der isolierte Rotnachweis fuer Haelfte 2.

### m4 -- die Vollzaehligkeit allein

Kommt zum Riegel `spielmodus` keine Meldung mehr an, bleiben die uebrigen sechs unter sich
widerspruchsfrei: 26 fremde und 4 eigene Paare, 0 Verletzungen. Ohne die
Vollzaehligkeitspruefung waere dieser Lauf gruen und saehe weniger. Er ist rot.

### m5 -- die beiden Paarzaehlungen

Nimmt die Sammlung nichts mehr auf, meldet der Lauf `0 Meldungen`, `0 fremde und 0 eigene
Paare` und wird rot -- fuenfmal ueber die Vollzaehligkeit und zweimal ueber die
Zaehlungen. **Ehrlich dazugesagt:** Ich habe keinen Eingriff gefunden, bei dem *nur* die
Paarzaehlungen anschlagen, ohne zugleich einen Riegel unvertreten zu lassen. Sie sind ein
Rueckhalt gegen eine spaetere Umstellung, die die Schleife leerlaufen liesse, und keine
eigenstaendige Messung.

## Nebenbefund: die offene Unsicherheit aus 0085 ist beantwortet

0085 hat offengelassen, ob `310` beim `spielmodus` den Riegel wirklich kennzeichnet oder
nur zufaellig haelt. Gemessen mit `bau/kp0107_tragkraft.py`, gegen die sechs fremden
Meldungen dieses Laufs:

| Stelle | Textstueck | passt auf fremde Meldungen |
|---|---|---|
| Runde nach der letzten zaehlbaren | `kern::schritt` | 3 von 5 -- allein zu schwach |
| Runde nach der letzten zaehlbaren | `groesste int64_t` | 0 von 5 -- allein trennscharf |
| partie.runde = -1 | `kern::schritt` | 3 von 5 -- allein zu schwach |
| partie.runde = -1 | `damit negativ` | 0 von 5 -- allein trennscharf |
| Zugang von vor Runde 1 | `kern::zustand::Startbelegung::setze` | 0 von 6 -- allein trennscharf |
| Zugang von vor Runde 1 | `eine Runde vorbeigelaufen` | 0 von 6 -- allein trennscharf |
| neuer Zugang nach der Runde | `kern::zustand::Startbelegung` | 1 von 6 -- allein zu schwach |
| neuer Zugang nach der Runde | `die Partie laeuft schon` | 0 von 6 -- allein trennscharf |
| Modus spielmodus | `kern::schritt` | 4 von 6 -- allein zu schwach |
| Modus spielmodus | `spielmodus` | 0 von 6 -- allein trennscharf |
| Modus spielmodus | `310` | 0 von 6 -- allein trennscharf |
| Modus spielmodus | `kein Paket` | 0 von 6 -- allein trennscharf |

**Die Antwort auf 0085 lautet: `310` haelt, aber es traegt nicht allein.** Es ist gegen den
heutigen Bestand trennscharf und zugleich neben `spielmodus` und `kein Paket` redundant.
Der Kasten-Praefix `kern::schritt` ist in jeder Liste das schwaechste Stueck -- er steht
in vier von sechs fremden Meldungen. Das ist kein Befund gegen die Listen: Genau dafuer
hat jede von ihnen ein zweites Stueck. Aber es sagt, wo eine Verkuerzung teuer waere.

Die Tabelle ist eine Beobachtung vom 2026-09-05 und **keine Zusicherung** im Quelltext.
Ein einzelnes Stueck auf Trennschaerfe festzunageln, waere eine andere Entscheidung als
die dieses Pakets; sie steht mir nicht zu.

## Die Werkzeugkette

- `kern/bau`, alle 10 Tests: **gruen**, `schritt_probe` darunter.
- Gesamtbaum `bau`, 14 Tests: 13 gruen. Rot ist allein `belegstellen_riegel`, und zwar an
  einem Abschnittszitat in `daten/nachmessung-zinsreihen-2026-09-05.md` in ein
  Deckungsdokument -- eine Datei, die weder zu meinem Paket gehoert noch von mir angefasst
  wurde. `schritt_probe.cpp` kommt in der Ausgabe dieses Riegels **null Mal** vor
  (nachgezaehlt). Gemeldet, nicht behoben: Reparatur ausserhalb des eigenen Pakets ist der
  Rolle verwehrt.
- Beide Bauwege einzeln gefahren, wie es der Baulauf tut.

**Zu den Zahlen des Belegstellenriegels:** Der Schlusslauf zaehlt `391 Namen in ungelesenen
Ordnern`. Darin stecken meine eigenen Messdateien unter `bau/` **und diese Datei selbst**
-- die Zahl vor ihrem Anlegen war 390. Die Messdateien sind durch `.gitignore` gedeckt und
mit dem naechsten sauberen Bau fort; ein Lauf ohne sie nennt eine kleinere Zahl. Das ist
kein Unterschied im Auslieferstand, aber die abgedruckte Zahl stimmt nur mit *diesem*
Arbeitsbaum ueberein. Die beiden Zahlen, auf die es ankommt, ruehrt das nicht an: `1
Abschnittszitat` rot und `0` Zeilenverweise mit Dateinamen daneben, vor und nach dem
Anlegen gleich.
