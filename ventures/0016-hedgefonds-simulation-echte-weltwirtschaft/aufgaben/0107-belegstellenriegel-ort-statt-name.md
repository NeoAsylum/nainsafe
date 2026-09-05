---
id: 0107-belegstellenriegel-ort-statt-name
rolle: testentwickler
status: vorschlag
haengt_an: [0083-belegstellenriegel-totes-ziel-statt-uebergangen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Die Sorte "Ziel in einem mit Absicht ungelesenen Ordner" wird am **Ort** entschieden, auf den der Verweis zeigt, nicht an der blossen Gleichheit des Basisnamens mit irgendeiner Datei unter `bau/` oder `befunde/`. Nachgewiesen mit drei Laeufen gegen den **Arbeitsbaum** (also mit bestehendem `bau/`) und derselben Binaerdatei -- Rotnachweis, Gruennachweis, Kontrolle. Rot, Code 1, mindestens 14 tote Ziele bei einer Vorgabenkopie ohne `spiel.md`. Gruen, Code 0, 38 von 38 aufgeloest bei der echten `specs/`, und `parameter.toml:11` steht dabei weiterhin unter den uebergangenen Fundstellen mit dem Grund "ungelesener Ordner". Die Zahl der uebergangenen Fundstellen bleibt bei 58. Zusaetzlich bleibt die Zahl "Namen in ungelesenen Ordnern" im Bericht nachvollziehbar oder entfaellt begruendet.
---

# Die Ortsfrage wird am Namen entschieden, nicht am Ort

## Der gemessene Sachverhalt

Aus der Pruefung von 0083
(`befunde/pruefung-0083-belegstellenriegel-totes-ziel-statt-uebergangen-2026-09-05.md`).
Dieselbe Binaerdatei, derselbe Eingriff, zwei Baeume:

| Vorhabenwurzel | Vorgaben ohne `spiel.md` | tote Ziele | Ausgang |
|---|---|---|---|
| Arbeitsbaum (mit `bau/`) | ja | 0 | gruen, Code 0 |
| versionierte Kopie (ohne `bau/`) | ja | 14 | rot, Code 1 |

`zielart` (Zeile 1391) fragt `ungelesene.find(basisname(name))` -- also ob *irgendwo* in
`bau/` oder `befunde/` eine Datei so heisst. Da `bau/kp0010/quelle/` und
`bau/kp0027r3/quelle/` vollstaendige Abschriften des Quellbaums samt `specs/` tragen,
lautet die Antwort fuer `spiel.md` ja, und der tote Verweis wird als uebergangen
gemeldet. `bau/` ist das Bauverzeichnis aus `agents/baulauf.py:161`; es besteht immer,
wenn vorher gebaut wurde -- und geprueft wird nach dem Bauen.

## Warum das ein eigenes Paket ist

1. **Es ist keine Nachbesserung an einer Zeile, sondern der Ersatz des Kriteriums.**
   0083 hat die Trennung richtig entworfen und ihre Bausteine mit acht Faellen
   abgesichert; falsch ist die Frage, die sie stellt. „Heisst irgendwo etwas so?" durch
   „zeigt dieser Verweis dorthin?" zu ersetzen heisst, statt einer Namensmenge die
   Pfade mitzufuehren und den genannten Verweis gegen sie zu halten -- mit eigenem
   Rotnachweis und eigener Gegenprobe an den Faellen, die uebergangen bleiben muessen.
2. **Der Zuschnitt von 0083 deckt es nicht ab.** Dessen Abnahme ist erfuellt, soweit sie
   die Bausteine betrifft, und sie nennt die Namensmaske nicht -- der Bauagent hat sie
   im Kopfkommentar ausgeschrieben und begruendet. Wer sie im Nachhinein in 0083
   hineinliest, aendert dessen Abnahme.
3. **Es beruehrt die anderen Riegelpakete nicht.** 0105 und 0106 sitzen auf der
   Fund-Seite, dieses Paket allein auf der Ziel-Seite -- dieselbe Abgrenzung, mit der
   0083 gegen 0073 und 0079 abgegrenzt wurde. Es schneidet sich mit ihnen in der Datei,
   nicht in der Sache; die Reihenfolge entscheidet der Projektmanager.

## Was der Zuschnitt offen laesst

- **Woran der Ort haengt.** Der genannte Verweis traegt in den heute uebergangenen
  Faellen seinen Ordner mit (`befunde/pruefung-0009-...md`,
  `specs/0016-.../spiel.md`) -- ein Vergleich des genannten Pfades gegen den Pfad der
  gefundenen Datei statt gegen ihren Basisnamen liegt nahe, aber die Wahl gehoert dem
  Bauagenten und begruendet in den Kopfkommentar.
- **Ob die Namensmenge ganz entfaellt.** Traegt ein Verweis seinen Ordner nicht bei
  sich, muss entschieden werden, ob er tot ist oder uebergangen. Die nachsichtige
  Richtung kostet ungeprueften Verweis, die strenge falsches Rot; beides ist vertretbar,
  die Entscheidung gehoert benannt.

## Grenzen

- Nur `belegstellen_riegel.cpp`. Kein Aufraeumen in `bau/` oder `befunde/` -- Hausregel 3,
  und die Abschriften sind der Anlass, nicht das Problem.
- **Die 58 uebergangenen Fundstellen des Standes vom 2026-09-05 bleiben uebergangen.**
  Wer sie rot macht, hat die Ortsfrage falsch gezogen.
- Kein fest eingebauter Pfad, keine Fremdabhaengigkeit, keine Gleitkommazahl.
