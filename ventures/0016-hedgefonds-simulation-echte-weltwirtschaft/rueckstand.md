# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-03, nach dem Betriebslauf von 18:55 (`72b7da9`). Fassung 13, geschrieben
vom Projektmanager. Diese Datei sagt, welche Pakete es gibt, warum in dieser Reihenfolge,
und was der Geschäftsführer entscheiden lassen muss.

**Dies ist ein kurzer Lauf, und der Grund dafür ist eine gute Nachricht.** Zwischen meinem
letzten Lauf (`635348d`, 15:20) und jetzt hat **kein einziger Bau- oder Prüfagent
gearbeitet** — `git log` zeigt dazwischen nur Betriebs-Commits des Betreibers und einen
Ideator-Lauf. Es gibt also keinen Prüfbefund nachzuziehen und keinen Vorschlag zu sichten;
beides war um 15:20 vollständig. Es bleibt eine Sache, und sie ist strukturell.

## Was dieser Lauf getan hat

**0002 steht nicht mehr auf `blockiert`, sondern auf `offen` mit `haengt_an:
[0008, 0026-klasse-2-preisbasis]`.** Am Sachverhalt ändert das nichts — das Paket wird
weiter nicht eingeplant, und genau das ist geprüft (Trockenlauf unten). An der Mechanik
ändert es alles.

Der Entblockungssatz von 0002 lautet seit dem 2026-09-02 wörtlich: *„eine Entscheidung des
Architekten zur Klasse-2-Frage, schriftlich in `technik.md` oder in einem ADR."* Seit
demselben Tag ist genau das ein Paket — 0026, `rolle: architekt`,
`dateien: [specs/…/technik.md]`. **Eine Sperre, die ein Paket ist, gehört in `haengt_an`
und nicht ins Statusfeld.**

Was der Unterschied kostet: `blockiert` verlangt einen Lauf von mir, bevor hier irgendetwas
weitergeht — erst 0026 abnehmen, dann in einem *weiteren* Lauf 0002 von Hand öffnen. Über
`haengt_an` tut es der Runner selbst, in derselben Nacht. Die Kette
**0011 → 0026 → 0002 → 0010** ist die längste des Vorhabens und trägt den letzten leeren
Kernkasten; sie hatte bis heute zwei reine Wartegriffe von mir darin.

Dass das die richtige Form ist, steht schon im Vorhaben: **0010 wartet seit jeher als
`offen` mit unerfüllter `haengt_an` auf 0002.** Es war 0002, das aus der Reihe fiel, nicht
0010.

**Damit wird `blockiert` wieder scharf**, und das ist der eigentliche Gewinn. Es heisst ab
jetzt: *eine Sperre, die kein Paket auflöst.* Übrig bleiben zwei, beide zu Recht — 0003
braucht einen ADR des Betreibers gegen T5, 0041 hat überhaupt keine Rolle, die es ziehen
dürfte. Für beide gibt es nichts, worauf sie hängen könnten.

**Die Auflage aus dem Paket bleibt bestehen und ist keine Formsache:** Ändern sich T47, T48
oder T50 durch 0026, ziehe ich in 0002 die Punkte 1 bis 3 und Abnahme 4 nach, **bevor** es
startbereit wird. Der Ort dafür ist mein Abnahmelauf zu 0026 — der Runner plant 0002 erst
ein, wenn 0026 auf `fertig` steht, und dieser Übergang geht durch meine Hand.

## Gemessen, nicht angenommen

| | vorher | nachher |
|---|---|---|
| offen | 12 | 13 |
| gebaut | 4 | 4 |
| fertig | 24 | 24 |
| blockiert | 3 | 2 |
| Bauplätze belegt | 4 von 4 | 4 von 4 |
| Prüfplätze belegt | 4 von 4 | 4 von 4 |

**Die Einplanung ist Zeile für Zeile dieselbe geblieben** — 0029, 0031, 0034, 0035 im Bau,
0011, 0027, 0032, 0033 im Review. 0002 taucht nicht auf. Das war die Prüffrage: Ein
`offen`, das der Runner ziehen würde, wäre ein Bauwerk gegen eine Vorgabe, von der zwei
Prüfbefunde und der Plan sagen, dass sie an dieser Stelle nicht trägt.

## Der Nachtrag des Betreibers zu 0031, und was ich dazugelegt habe

Der Betreiber hat am 2026-09-03 in 0031 nachgetragen, dass **die Schritte 1 bis 3 bereits
im Baum liegen** (`95903a6`): Der Bauagent wurde erschlagen, bevor er `gebaut` setzen
konnte. Ich habe die tragende Zahl nachgemessen statt sie zu übernehmen —
`grep -c "set(FABRIK_STRENGE"` auf `werkzeugkette.cmake` liefert **1**, und
`kern/CMakeLists.txt` trägt an der Stelle nur noch einen Kommentar. Bedingung 1 ist
erfüllt. Der Status bleibt richtig auf `offen`: Bedingung 4 ist offen, und der Nachweis
gehört in den Befund des Bauagenten, nicht in eine Messung von mir.

**Dazu habe ich eine Warnung in das Paket geschrieben — kein Kriterium, Bedingung 4 steht
wörtlich unverändert.** Beide Kästen sammeln ihre Quellen mit
`file(GLOB … CONFIGURE_DEPENDS … /src/*.cpp)` ein (`kern/CMakeLists.txt` Zeile 47,
`pruefstand/CMakeLists.txt` Zeile 46). Das ist der Grund, warum Bedingung 4 überhaupt
funktioniert — und dieselbe Mechanik ist die Gefahr: **Eine liegengebliebene
`warnsatzprobe.cpp` macht nicht das Paket rot, sondern die Bibliothek insgesamt**, und mit
ihr jeden Test, jeden Prüfer, der danach übersetzt, und den Übersetzungsbericht des Tages.

**Das Feld `dateien` kann davor nicht schützen, und das ist der Punkt, den ich hier
festhalte.** Es serialisiert Schreibzugriffe. Dieser Agent fasst keine fremde Datei an — er
vergiftet ein gemeinsames Ziel. Es ist die erste Kollisionsart in diesem Vorhaben, die
mein Werkzeug nicht ausdrücken kann.

**Es ist auch keine Theorie.** Der Agent, der heute um 18:41 starb, arbeitete an genau
diesem Paket und war zwischen Schritt 3 und 4 — also **vor** dem Anlegen der Probedateien.
Zwanzig Minuten später, und der ganze Kern stünde rot, mit drei Prüfern, die einen Fehler
melden, den keiner von ihnen verursacht hat. Was ich hineingeschrieben habe, ist deshalb
eine Reihenfolge, keine Bedingung: den Nachweis zuerst notieren, die Dateien zuletzt
anlegen und sofort wieder löschen.

## Der Rückstand

**Im Bau (4):** 0029 Vorratsverfahren-Invariante (testentwickler), 0031 Warnsatz in die
Werkzeugkette (kernbauer), 0034 Belegstellen ohne Zeilennummern (datenbauer), 0035
Parameterdatei-Belegstellen (datenbauer).

**Im Review (4):** 0011 Stack auf C++ (entwurf-pruefer), 0027 Zustand-Schreibweg
(kern-pruefer), 0032 reihen.toml Notenbanken (daten-pruefer), 0033 Schritt-Rundengerüst
(kern-pruefer).

**Startbereit in Reserve (2):** 0039 Zollzeile Konjunktursockel (spielentwerfer), 0040
Kernanker Klassenzuteilung (testentwickler). Sechs startbereite Pakete auf vier Plätze ist
der gesunde Zustand, nicht ein Stau.

**Wartend auf ein laufendes Paket (7):** 0026 (an 0011), 0036 (an 0032), 0038 (an 0033),
0042 (an 0035), 0043 (an 0011 und 0039), **0002 (an 0026, neu)**, 0010 (an 0002).

**Blockiert (2):** 0003 (Einheiten im Typ, braucht einen ADR gegen T5), 0041
(`baulauf.py`, keine zuständige Rolle).

## Zum Vorrang des Geschäftsführers

Seine fünf Kennungen aus dem Bericht von 15:10 waren 0011, 0026, 0019, 0028, 0034. Um
15:20 waren 0019 und 0028 nachgezogen, 0011 im Review und 0034 im Bau; **daran hat sich
nichts geändert, weil dazwischen niemand gearbeitet hat.** 0026 wartet unverändert auf das
Urteil zu 0011.

**Meine einzige Handlung dieses Laufs berührt seine Liste an einer Stelle**, und zwar zu
seinen Gunsten: Sein Vorrangpunkt 2 (0026) ist der Grund, warum 0002 bisher blockiert war.
Nach dieser Änderung entblockt sein Punkt 2 die Kette ohne einen weiteren Lauf von mir.
Das ist keine Abweichung von seiner Reihenfolge, sondern das Wegräumen eines Handgriffs
darin.

## Was der Geschäftsführer entscheiden lassen muss

**Unverändert alle drei, und alle drei liegen beim Betreiber, nicht bei mir.**

1. **Die Rohdaten.** `daten/` enthält weiter keine Datenzeile. Empfehlung B (der Betreiber
   lädt die vier Quellen einmal von Hand) steht seit vier Plänen. Die Frist dafür ist
   näher, als die Zahlen zeigen: Von den offenen Datenbaupaketen arbeiten 0034, 0035, 0036
   und 0042 alle an Belegstellen und Begründungen in Textdateien. **Nach 0042 hat der
   Datenbauer ohne geladene Quellen nichts mehr zu tun.**
2. **0041 braucht eine Hand.** Eine Zeile in `agents/baulauf.py`, Neustart des Tageslaufs,
   dazu ein `rm -rf` auf `pruefstand/bau/pruefung-0019/`. Wortlaut im Paket.
3. **Die Prüfplätze nicht erhöhen — noch nicht.** Meine Messung von 15:20 steht: Bau und
   Prüfung sind gleich voll, ohne dass eine Zahl im Runner geändert wurde. Die Bedingung
   des Geschäftsführers — eine Nacht mit der neuen Rücklaufgrenze — ist weiterhin erst zur
   Hälfte eingelöst, denn seit 15:20 lief keine. *Widersprechen wir uns hier ein zweites
   Mal, gehört es in seinen Bericht an den Betreiber statt in eine dritte Runde.*

**Klein gehalten, weil nicht fällig:** Den drei Rollendateien `architekt`,
`spielentwerfer` und `testentwickler` fehlt weiter der Satz „Setze `status: gebaut`". Der
Punkt ist nicht erledigt, nur nicht aufgetreten.

## Die eine Zahl

**Ein fehlendes Urteil, jetzt nur noch dreimal weitergereicht statt viermal.** `werte`
(78 Byte, unverändert) hängt an 0002, 0002 an 0026, 0026 an dem Urteil zu 0011. Das vierte
Glied war ich: ein Lauf von mir zwischen 0026 und 0002, der nichts entschieden, sondern nur
ein Statusfeld umgestellt hätte. Den gibt es nicht mehr.

Eine Spielrunde ist noch immer nie gerechnet worden, und keine Zahl dieses Laufs ändert
daran etwas. Der Nachweis bleibt derselbe und kann von keinem Agenten erfunden werden: 175
Ursachensätze und eine FNV-1a-64-Prüfsumme, die sich nicht bewegt hat.
