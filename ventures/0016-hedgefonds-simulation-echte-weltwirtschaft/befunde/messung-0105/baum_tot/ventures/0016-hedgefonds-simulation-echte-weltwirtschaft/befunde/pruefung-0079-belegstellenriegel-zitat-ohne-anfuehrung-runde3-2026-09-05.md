---
typ: pruefung
paket: 0079-belegstellenriegel-zitat-ohne-anfuehrung
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Den in Ruecklauf 2 allein strittigen Teil 4 der Abnahme mit eigenem Bau beider Staende an beiden benannten Baeumen nachgemessen (A=9, C=47, verschwunden=0, neu=38, davon 37+1 mit 0079-Gruenden); die uebrigen vier Teile gelten fort, weil der Riegel seit f8c8598 nachweislich unveraendert ist.
befunde: 0
---

# Pruefung 0079, Runde 3 (Ruecklauf 2 des Bauagenten)

Ruecklauf 2 hat `belegstellen_riegel.cpp` nicht angefasst; geaendert sind allein
`befunde/messung-0079/nachweis.md` und der Vermerk in der Paketdatei. Beides habe ich
zuerst an der Versionsgeschichte geprueft, dann die strittigen Zahlen vollstaendig
selbst gemessen -- eigener Bau beider Programme, eigene Baeume, eigener Vergleich.
Alle Laeufe an Arbeitskopien unter `$TMPDIR`; der eine Lauf am Arbeitsbereich war rein
lesend, mit einem ausserhalb gebauten Programm.

## Der Riegel ist wirklich unveraendert -- die Voraussetzung des ganzen Urteils

* `git diff f8c8598 HEAD -- werkzeuge/belegstellen/belegstellen_riegel.cpp`: leer.
  Arbeitsbereichs-Diff derselben Datei: leer. Kein Commit in
  `f8c8598..HEAD` fasst `werkzeuge/belegstellen/` an.
* Die Ruecklauf-2-Aenderungen liegen unter fremden Betreffs, wie der Vermerk es
  ankuendigt und **an der Dateiliste nachpruefbar**: `0134179` (`architekt: 0116-...`)
  traegt `nachweis.md` (+70/−10), `d0467b2` (`kernbauer: 0122-...`) traegt die
  Paketdatei (+8/−1). Der Commit mit dem 0079-Betreff (`7a4183b`) aendert nur
  Sandbox-Symlinks (saemtliche numstat-Eintraege 0/0).
* **Keine Abschwaechung moeglich und keine gefunden:** kein Testcode, keine
  Falltabelle, keine Schwelle geaendert -- nur die Messschrift. Meine Pruefung aus
  Runde 2 (benannte Eigenschaft, vier 0047-Stellen mit selbst gefuehrtem Rotnachweis,
  Satzgrenze von beiden Seiten mit je einem Mutanten eingeklemmt, Loeschseiten aller
  Baucommits) gilt damit fuer denselben Binaerstand fort.

## Teil 4, vollstaendig selbst nachgemessen

Beide Baeume mit `git archive` ausgepackt (`f8c8598` und `fabbf2f`, je
`ventures/0016-...` und `specs/0016-...`). Stand C = der ausgelieferte Riegel, je Baum
im Alleinbauweg gebaut (`RelWithDebInfo`, Werkzeugkette samt Sanitizern ueber
`PROJECT_IS_TOP_LEVEL`). Stand A = `belegstellen_riegel.cpp`, `CMakeLists.txt` und
`werkzeugkette.cmake` aus `489aafb`, in einer Hilfsstruktur **ausserhalb** der Baeume
gebaut und mit den zwei Wurzeln des jeweiligen Baums als Argumente aufgerufen. Alle
vier Laeufe Rueckgabewert 0. Vergleich der Aufzaehlungen ueber `datei:zeile` als
Mehrfachmenge:

| Baum | A | C | verschwunden | neu | *Gliederungsziffer* | *Zieldatei fuehrt keine Ueberschrift* |
|---|---|---|---|---|---|---|
| `f8c8598` | 9 | 47 | 0 | 38 | 37 | 1 |
| `fabbf2f` | 9 | 47 | 0 | 38 | 37 | 1 |

Das deckt sich Zahl fuer Zahl mit der berichtigten Tabelle in Nachweis-Abschnitt b)
und im GEBAUT-Absatz. Ein dritter Grund kommt unter den 38 neuen nicht vor. Die neun
A-Fundstellen decken sich einzeln mit der Tabelle in Nachweis-Abschnitt a),
einschliesslich des dort erklaerten Grundwechsels von `parameter.toml:11` (A: *Ziel
ausserhalb des Bestands*, C: *Ziel in einem mit Absicht ungelesenen Ordner* -- Arbeit
von 0083, Fundstelle nicht verschwunden).

**Die 38. Fundstelle existiert und ist das behauptete Doppelpaar.** In der C-Ausgabe
steht der Eintrag `daten/reihen.toml:1401 (Gliederungsziffer statt Ueberschrift: 7) /
gesucht war: 7 fuehrt sie nicht` an beiden Baeumen genau **zweimal, Zeichen fuer
Zeichen gleich**, und es ist das einzige Mehrfachpaar der Aufzaehlung (47 Eintraege,
46 verschiedene Textpaare). Zeile 1401 nennt "Abschnitt 7" tatsaechlich zweimal --
einmal im eigenen Satz, einmal im woertlichen technik.md-Zitat.

**Der alte Zaehlfehler ist reproduzierbar, wie der Nachweis behauptet.** Liest man
die gedruckte Liste dedupliziert (das zeichengleiche Paar als ein Eintrag) statt als
Mehrfachmenge, erhalte ich an beiden Baeumen exakt 46 / 37 / 36 -- die drei Zahlen,
die bis Ruecklauf 2 im Nachweis standen. Die Erklaerung ist also nachgerechnet, nicht
uebernommen.

## Die uebrigen Teile der Abnahme, je mit heutigem Messweg

* **Vier Stellen aus 0047:** In meinem heutigen C-Lauf an Baum 1 stehen
  `daten/reihen.toml:259` (Ziffer 5) und `:302`/`:309` (Ziffer 3) namentlich in der
  Aufzaehlung der uebergangenen; `reihen.toml:1752` kommt darin nicht vor (beide
  Ueberschriften aufgeloest). Der Rotnachweis ueber die Korpuskopie aus Runde 2 gilt
  fuer den unveraenderten Stand fort.
* **Gruen auf dem geltenden Korpus:** Lauf des ausserhalb gebauten C-Programms gegen
  den heutigen Arbeitsbereich (`HEAD 38ab29f` plus laufende Aenderungen): 36 Zitate,
  36 aufgeloest, 47 uebergangen, Rueckgabewert 0, Selbsttest vollstaendig gruen.
* **Abgedruckter Lauf = ausgelieferter Stand:** Mein C-Lauf an Baum `f8c8598` nennt
  zeichengleich die Zahlen des abgedruckten Laufs (42 Bauquellen, 11 Datendokumente,
  166 im Zielbestand, 35/35/47, 14 Zitate ohne Anfuehrung, 54 ohne Dokumentnamen);
  allein *Namen in ungelesenen Ordnern* steht bei 286 statt 380, exakt wie der
  Nachweis es selbst misst und begruendet (`bau/` liegt nicht in git).
* **"Nach der letzten Zeile des Kopfkommentars":** In Ruecklauf 2 wurde der
  Kopfkommentar nicht angefasst; die Messungen laufen an benannten, unveraenderlichen
  Commits. Trivial erfuellt, wie der Vermerk sagt.

## Randbemerkung ohne Urteilswirkung

Nachweis-Abschnitt b) sagt zur einen Fundstelle der Sorte *Zieldatei fuehrt keine
Ueberschrift*: "(Baum 2: Zeile 227, Baum 1: Zeile 269 -- eine fremde Einfuegung
dazwischen hat sie verschoben), gesucht war *18 vererbt sich sonst*". Die Zeilen
stimmen, aber der gesuchte Wortlaut gilt nur an Baum 2; an Baum 1 lautet er *18 nennt
drei von sechs Stellen mit*, und die Stelle ist zwischen den Baeumen nach **oben**
gewandert -- der Absatz in `rueckstand.md` wurde umformuliert, nicht durch eine
Einfuegung verschoben. Beides beruehrt keine Abnahmebedingung und keine der drei
Zahlen; es steht hier, damit niemand die Detailangabe fuer eine Messung haelt.

## Wonach ich gesucht und nichts gefunden habe

Eine Aenderung am Riegel oder an einer Falltabelle seit `f8c8598` (Diff leer);
verschwundene A-Fundstellen (null, an beiden Baeumen); neue Fundstellen mit fremdem
Grund (keine); ein weiteres zeichengleiches Mehrfachpaar (keines); eine Abweichung
zwischen abgedrucktem Lauf und ausgeliefertem Stand (keine ausser der selbst
ausgewiesenen Namenszahl); Rot am heutigen Arbeitsbereich (gruen, Code 0).
