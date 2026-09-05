# Nachweis zu Paket 0083 -- totes Ziel statt uebergangen

**Rolle:** testentwickler. **Datum:** 2026-09-05.
**Geaenderte Datei:** `werkzeuge/belegstellen/belegstellen_riegel.cpp`, sonst keine.

**Stand zu Beginn des Laufs:** `dd94ab9`. Waehrend des Laufs hat ein paralleler Lauf
`ce59b8b` (architekt, 0051) committet und dabei `specs/.../technik.md`,
`kern/test/schritt_probe.cpp` und `kern/test/werte_probe.cpp` geaendert sowie zwei
Berichte unter `befunde/` angelegt. Derselbe Commit hat meinen halbfertigen Stand der
Riegelquelle mitgenommen; er entspricht dem Endstand dieses Laufs, geprueft mit
`git diff ce59b8b --` auf die Datei (leer). Alle Zahlen unten sind nach der Drift erneut
gemessen und unveraendert.

## Was gebaut wurde

**Erstens: die Sorte "Ziel ausserhalb des Bestands" ist in drei zerlegt.** Steht der
naechstgelegene Dokumentname nicht im Zielbestand, entscheidet `zielart` in dieser
Reihenfolge:

| Antwort | Bedingung | Ausgang |
|---|---|---|
| `Gelesen` | der Basisname steht im Zielbestand | nachschlagen wie bisher |
| `Ausserhalb` | der Name spricht seinen Ort selbst aus (fuehrender Schraegstrich, Aufstieg mit zwei Punkten) | uebergangen |
| `Ungelesen` | es gibt eine Datei dieses Namens unter `bau/` oder `befunde/` | uebergangen, Meldung nennt den Namen |
| `Tot` | kein Ort unter beiden Wurzeln traegt den Namen | **Befund, Lauf rot** |

Damit der zweite Fall vom vierten unterscheidbar ist, sammelt `sammle_dateien` seit
diesem Paket die **Dateinamen** unter den ungelesenen Ordnern ein -- nicht ihren Inhalt.
Gemessen: 340 Namen. Versteckte Ordner (`.git`, `.claude`) bleiben ganz aussen vor; dort
liegt Maschinerie und kein Dokument, das ein Zitat nennen koennte.

**Die zwei offen gelassenen Entscheidungen, beide im Kopfkommentar begruendet:**

* *Die Untergrenze ist eine Zahl im Quelltext*, nicht aus der Bestandsgroesse abgeleitet.
  Grund ist der gemessene Fall selbst: Faellt eine Vorgabendatei weg, halbiert sich die
  Zahl der aufgeloesten Zitate, waehrend der Bestand um **eine** von 159 Dateien
  schrumpft. Eine mitwandernde Schranke verdeckte genau das.
* *`aufgaben/` wird **nicht** wie `befunde/` behandelt.* Die beiden stehen auf
  verschiedenen Seiten: Ungelesen ist `aufgaben/` nur als **zitierende** Menge, als
  **Ziel** steht es im Bestand und wird nachgeschlagen. Es dort herauszunehmen hiesse,
  heute aufloesende Zitate kuenftig zu uebergehen -- also die stille Verkleinerung der
  Abdeckung, gegen die dieses Paket geschrieben ist.

**Zweitens: die Untergrenze.** `AUFGELOEST_MINDESTENS = 16`. Die Zahl ist gezaehlt und
nicht gegriffen: die aufgeloesten Belegstellen der sechs Pakete, um derentwillen der
Riegel existiert, wie der Kopfkommentar sie einzeln abhakt -- 0034 zwei, 0035 zwei, 0044
eines, 0047 zwei (die beiden anderen sind Gliederungsziffern), 0050 fuenf, 0057 vier.

## Gruennachweis

Lauf gegen die Vorhabenswurzel, beide Bauwege einzeln (`werkzeuge/belegstellen` allein
und der Arbeitsbereich mit `FABRIK_SANITIZER=ON`), identische Zahlen:

```
Selbsttest: 8 Faelle zur Suche nach links, 9 zur Form ohne Anfuehrung
            und 8 zur Ortsfrage, alle wie erwartet.
Bedingung 1: 42 Bauquellen, 5 Zeilenverweise, davon 0 mit Dateinamen daneben.
Bedingung 2: 42 Bauquellen und 11 Datendokumente, 159 Dateien im Zielbestand,
             340 Namen in ungelesenen Ordnern; 38 Zitate gefunden, 38 aufgeloest
             (Untergrenze 16), 58 Fundstellen uebergangen.
Rueckgabe 0.
```

**Vorher-Stand am selben Korpus: 38 gefunden, 38 aufgeloest, 58 uebergangen.** Die drei
Zahlen sind unveraendert -- die Trennung fuegt heute keinen Befund hinzu und nimmt keinen
weg. Sie aendert eine Meldung: Aus `Ziel ausserhalb des Bestands` wird
`Ziel in einem mit Absicht ungelesenen Ordner`.

**Die fuenf uebergangenen Fundstellen aus Paket 0067, die die Abnahme namentlich
schuetzt, bleiben alle uebergangen:**

```
  parameter.toml:11  (Ziel in einem mit Absicht ungelesenen Ordner: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
  daten/lizenzbefund-reihen.md:164  (kein Dokumentname im Absatz)
  daten/lizenzbefund-reihen.md:202  (kein Dokumentname im Absatz)
  daten/lizenzbefund-reihen.md:364  (naechstes Ziel ist eine Netzadresse: //raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md)
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
```

Der ganze Arbeitsbereich: **14 von 14 Tests bestanden**, unter dem Adressen- und
Verhaltenssanitizer, keine Meldung.

## Rotnachweise -- vier, je einer fuer eine Teilregel

Jeder ueber die **eigene** Datei, jeder wieder herausgenommen.

**1. Ein Zitat auf einen erfundenen Dateinamen.** Eine Zeile in den eigenen
Kopfkommentar, die `spiel-gibt-es-nicht.md` mit einer zitierten Ueberschrift nennt:

```
1 Abschnittszitat(e) nennen eine Zieldatei, die es unter keiner der beiden
Wurzeln gibt:

  zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:429
  genannte Zieldatei: spiel-gibt-es-nicht.md
  gesuchter Wortlaut: Die Schleife
```

Rueckgabe 1, Test fehlgeschlagen. Das Zaehlwerk sagt dabei `39 gefunden, 38 aufgeloest`
bei unveraendert 58 uebergangenen -- die Stelle wandert nicht in den blinden Fleck,
sondern in die Befunde. Das ist der Kern der Abnahme.

**2. Die Untergrenze unterschritten.** `AUFGELOEST_MINDESTENS` von 16 auf 39 gestellt:

```
belegstellen_riegel: nur 38 Zitate haben aufgeloest, die Untergrenze im Quelltext
steht bei 39. Das ist ein Befund gegen die Abdeckung und keine bestandene Bedingung
```

Rueckgabe 2.

**3. Die Teilregel "Ort ausserhalb beider Wurzeln" abgeschaltet** (`nennt_ort_ausserhalb`
gibt unbedingt falsch zurueck). Es fallen **genau die drei** Faelle, die sie tragen --
6, 7 und 8 --, die anderen fuenf bleiben gruen:

```
Zielfall 6: die Art ist 3, erwartet war 1.   Name: /usr/share/doc/lizenz.md
Zielfall 7: die Art ist 3, erwartet war 1.   Name: ../../CLAUDE.md
Zielfall 8: die Art ist 3, erwartet war 1.   Name: werkzeuge/../daten/gibt-es-nicht.md
```

Rueckgabe 2, ohne dass der Bestand ueberhaupt gelesen wird.

**4. Die Namen der ungelesenen Ordner nicht mehr eingesammelt.** Das ist der Rotnachweis,
der die Trennung **auf dem Korpus** zeigt statt in der Tabelle: Ohne die Namensmenge
faellt die eine echte Fundstelle dieser Sorte von `uebergangen` in `Befund`.

```
159 Dateien im Zielbestand, 0 Namen in ungelesenen Ordnern; 39 Zitate gefunden,
38 davon aufgeloest, 57 Fundstellen uebergangen.

  zitierend: parameter.toml:11
  genannte Zieldatei: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md
  gesuchter Wortlaut: WIE DER PRUEFER ZAEHLT
```

Uebergangene 58 auf 57, Befunde 0 auf 1, Rueckgabe 1. Damit ist belegt, dass die
Entscheidung an der **Ordnerliste** haengt und nicht am Vorsatz im geschriebenen Pfad --
haette ich sie am `befunde/` im Namen festgemacht, waere dieser Lauf gruen geblieben.

## Was ich offen lasse, und wo es weh tun kann

* **Die Trennung gilt fuer beide Zitatformen, auch fuer die ohne Anfuehrung.** Dort ist
  die Fundstelle mit einem Wahrscheinlichkeitsurteil gefunden, und bisher hat das
  Nachschlagen des Ziels sie stillschweigend bestaetigt. Kuenftig wird ein Absatz, der
  einen Dateinamen nennt, den es nicht gibt, rot -- auch wenn das Zitat daneben keines
  war. Ich halte die Richtung fuer richtig, aber es ist eine **neue Quelle von Rot**.
  Am 2026-09-05 gibt es im ganzen Bestand keine Fundstelle, die davon betroffen waere.
* **Die Untergrenze von 16 faengt einen Rueckgang von 38 auf 17 nicht.** Das ist
  Absicht und im Quelltext ausgeschrieben: Eine Schranke dicht unter dem Tagesstand
  wuerde bei jeder rechtmaessig entfernten Belegstelle rot und beim naechsten Lauf
  nachgezogen. Der Rueckgang auf der **Zielseite** haengt ohnehin nicht an ihr, sondern
  ist seit diesem Paket ein Befund. Wer die Zahl fuer zu weich haelt, hat ein Argument;
  ich habe kein Mass gefunden, das enger waere, ohne geraten zu sein.
* **`nennt_ort_ausserhalb` fragt an der Gestalt des Namens, nicht am Dateisystem.** Ein
  Dokument der Fabrik oberhalb beider Wurzeln, das jemand ohne Pfadvorsatz zitiert
  (etwa `agentenbau.md` statt `../../agentenbau.md`), wuerde als toter Verweis gemeldet.
  Heute kommt das nicht vor -- gemessen, der Lauf ist gruen. Traete es auf, waere die
  saubere Antwort die oberste Ebene der gemeinsamen Wurzel als dritter Ort, und das ist
  ein eigenes Paket und keine Zeile hier.
