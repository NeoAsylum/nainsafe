---
id: 0172-weltpreis-mit-zoll-untergrenze-des-faktors
rolle: architekt
status: vorschlag
haengt_an: [0152-werte-zweiundzwanzig-statt-siebzehn]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen unter "Abnahme".
---

# Der Zollfaktor von Nr. 21 hat keine Untergrenze, und ein Klasse-5-Index wird dabei negativ

**Vorgeschlagen am 2026-09-06 vom Kern-Pruefer**, bei der Pruefung des Pakets `0152`.
Das Paket ist erfuellt und dieser Vorschlag ist kein Befund gegen es: `weltpreis_mit_zoll`
ist die Formel aus `technik.md` T48 Nr. 21 Zeichen fuer Zeichen, und genau das hat `0152`
bestellt.

## Der belegte Schaden

Gemessen am Stand `5bb5375`, in einem Baum aus `git archive` mit einem zusaetzlichen
Pruefsatz an `probe_weltpreis_mit_zoll` und **unveraendertem** `werte.cpp`
(`befunde/bau-pruefung-0152/mutanten.md`, Abschnitt „Randmessung"). Beide Zusicherungen
halten, der Lauf ist gruen:

```
zollstand(DE) = -12'000, welt.preis.1 = 11'000  ->  weltpreis_mit_zoll = -2'200
zollstand(DE) = -10'000, welt.preis.1 = 11'000  ->  weltpreis_mit_zoll =      0
```

Kein Abbruch, keine Meldung. Die Rechnung ist `mal_geteilt(welt.preis, plus(10.000,
zollstand), 10.000)`; unterhalb von −10.000 Basispunkten dreht der Faktor das Vorzeichen,
bei genau −10.000 ist er null.

**Warum das mehr ist als eine Kuriositaet.** T48 gibt Nr. 21 die **Klasse 5** -- ein
Nominalindex mit Startjahr 10.000. T30 Pruefung 2 haelt genau diese Klasse an einer
Schranke: *„Nominalindizes > 0"*, 22 Adressen. Waere `weltpreis_mit_zoll` eine Adresse,
wuerde Pruefung 2 den Wert je Runde als **harten Fehler** zurueckweisen. Sie ist aber eine
abgeleitete Groesse, und abgeleitete Groessen prueft niemand. Die Schranke faellt genau
durch den Spalt zwischen T30 und T48.

Ihr Leser ist nach T48 und T28 die Marktraeumung, also die Preisbildung selbst. Ein
negativer oder nullwertiger Weltpreis dort ist kein Randwert, sondern eine Preisformel,
die ihr Vorzeichen verliert -- und wenn eine spaetere Zeile durch ihn teilt, ein Nenner
null.

## Warum die Luecke heute niemandem gehoert

Drei Stellen koennten sie schliessen, und keine tut es:

* **T30 Pruefung 2** (Paket `0020`, `fertig`) fuehrt sieben Wertebereichsschranken. Keine
  davon nennt den **Zollstand**, und keine nennt eine abgeleitete Groesse. Der Zollstand
  hat damit heute weder Unter- noch Obergrenze.
* **T51** begruendet, warum der Nenner von `anleihekurs` nie null und nie negativ ist --
  die Schranke sitzt dort **am Instrument**. Fuer den Zoll gibt es keine Entsprechung.
* **`0152` selbst** durfte sie nicht schliessen: Sein Auftrag lautet ausdruecklich, die
  Fassung zu bauen, die dasteht, und den Vorbehalt nur als Kommentar zu vermerken.

## Warum es ein eigenes Paket ist und kein Teil eines bestehenden

Es ist **keine Bauarbeit**, sondern eine Entwurfsentscheidung, und deshalb geht es an den
Architekten und nicht an den Kernbauer. Zu entscheiden ist, wo die Schranke sitzt, und die
drei moeglichen Orte tragen verschiedene Folgen:

1. **Am Instrument**, wie T51 es fuer den Leitzins tut: `zollstand ≥ 0` (oder eine
   ausgeschriebene Untergrenze über −10.000) wird die achte Wertebereichsschranke von T30
   Pruefung 2. Dann ist ein Zollstand unterhalb der Grenze ein harter Fehler, und Nr. 21
   braucht keine Zeile.
2. **An der Groesse**, wie bei Nr. 1 (`wechselkurs[g] ≥ 1`): `weltpreis_mit_zoll` bricht
   selbst ab. Dann bewegt sich T48, und die Zeile kostet einen Aufruf je Marktraeumung.
3. **Gar nicht**, mit ausgeschriebener Begruendung, dass Schritt 3 einen negativen
   Zollstand konstruktionsbedingt nie erzeugt. Auch das ist eine Antwort -- aber sie muss
   dastehen, sonst ist sie beim naechsten Lauf wieder nicht da.

Das ist eine Wahl zwischen drei sinnvollen Belegungen, und genau deshalb entscheidet sie
kein Bauagent nebenbei. `0152` an dieser Stelle nachzuschaerfen wuerde ausserdem seine
eigene Vorgabe brechen.

**Es ist nicht Teil von `0165`** (zwei Zustandseingaenge von `schaden`): Das betrifft Nr.
22 und die Zugriffsform, nicht den Wertebereich von Nr. 21.

## Abnahme

1. **`technik.md` entscheidet die Frage ausdruecklich** -- einer der drei Wege oben, mit
   Begruendung und mit der Zahl, falls es eine gibt. Ein Verweis auf „ergibt sich" reicht
   nicht; der Absatz nennt den gemessenen Fall (−12.000 → −2.200) und sagt, was mit ihm
   geschieht.
2. **Faellt die Entscheidung auf Weg 1**, steht die neue Schranke in der Untertabelle von
   T30 Pruefung 2 mit Adresszahl, damit der Testentwickler sie ohne Suchen findet -- so wie
   die sieben vorhandenen. Faellt sie auf Weg 2, steht die Abbruchbedingung in T48 bei
   Nr. 21. Faellt sie auf Weg 3, steht dort, welche Vorgabe in Schritt 3 den negativen
   Zollstand ausschliesst.
3. **Der Vorbehalt zum Definitionsbereich bleibt unberuehrt.** `technik.md` Zeile
   3262--3269 meldet, dass der Definitionsbereich von Nr. 21 nirgends ausgeschrieben steht;
   der Kern-Pruefer traegt dazu einen Fund bei, der dort noch fehlt: **`spiel.md` Zeile 331
   schreibt die Formel mit `l`, `technik.md` T48 Zeile 2094 mit `g`.** Die beiden Vorgaben
   schweigen an dieser Stelle nicht nur, sie widersprechen sich. Ob dieses Paket auch das
   aufloest, entscheidet der Projektmanager -- benannt ist es hier.
