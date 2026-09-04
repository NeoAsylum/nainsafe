# Logbuch: entwurf-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/entwurf-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören in die Ergebnisdatei, nicht hierher. Ins Logbuch kommt die Lehre daraus,
in einem Satz — ein unbegrenzt wachsendes Logbuch kostet jeden Lauf Kontext.

*Archivieren ist mir **nicht moeglich** (erneut im 14. Lauf, absoluter Pfad und `Write` —
also **kein** `cd`-Artefakt): `notizen/archiv/` ist gesperrt. Statt zu archivieren wird
verdichtet, **nie gestrichen** (volle Fassung der Laeufe 1-9:
`git show 77a84e8:notizen/entwurf-pruefer.md`). Als Regelproblem gemeldet: Die Rollendatei
verlangt eine Verschiebung, fuer die die Rechte fehlen.*

---

## Was funktioniert

- **Jede Zahl selbst nachrechnen, auch die beilaeufigen** (2026-08-31). Drei von acht
  Befunden des 1. Laufs waren Rechenfehler in Nebensaetzen; Prosa wird gelesen, Arithmetik
  nicht.
- **Die Nebenzahl neben der Abnahmezahl ist die, die nicht stimmt** (2026-09-03, best.
  2026-09-04). 9. Lauf: Die Probe fuer die Bedingung war fehlerfrei, falsch war die
  Vergleichszahl daneben. 14. Lauf: beide Befunde sassen im **Selbstbericht**, waehrend der
  normative Teil stimmte. *Beide Spalten einer Vergleichstabelle aus ihren **eigenen**
  Zeilen rechnen — und den Bericht ueber die Arbeit getrennt von der Arbeit pruefen.*
- **Vollstaendigkeitsbehauptungen sind pruefbare Behauptungen, keine Ueberleitungen** —
  fuenf Auspraegungen, alle haben getroffen: „hier stehen alle uebrigen" gegen die Feldliste
  abzaehlen (32 von 310 Adressen ohne Startwert); eine Ausnahme im Fliesstext gegen die
  Zugriffstabelle (16 statt 12, Summe 120 statt 112); eine Protokolllinie in **beide**
  Richtungen lesen; „die zwoelf Reste" gegen die Tabelle abzaehlen (es waren 22, 14. Lauf);
  und **„das ist die vollstaendige Liste" ueber eine *fremde* Datei** ist die ergiebigste
  von allen — zehn fehlende Stellen statt sieben (2026-09-04), fuenf statt drei im 14. Lauf.
  *Eine Nachziehliste muss auch nennen, was **bleibt**.*
- **Aendert sich eine Zahl, greppe auch die Ordnungszahl, die aus ihr folgt** (2026-09-04,
  14. Lauf). `grep "siebzehn"` fand fuenf Stellen; eine sechste sagte „keine **achtzehnte**
  Groesse" und haengt genauso an der 17, ohne das Suchwort zu enthalten. *Der Zahlwort-Grep
  ist der halbe Nachweis; Ordnungszahl und Nachfolger gehoeren dazu.*
- **Die Erhebung des Dokuments mit einem weiteren Muster wiederholen** (2026-09-04,
  14. Lauf). T48 druckte sein eigenes `rg`-Muster ab (nur Kleinbuchstaben ab drei Zeichen);
  ein breiteres Muster brachte sieben weitere Namen — alle harmlos, aber **erst das** macht
  aus „Rest null" einen Nachweis statt einer Wiederholung der Behauptung. Ein Aufruf.
- **Erst die Zahlen, dann den Text: die Kostentabelle verraet die ungenannte Lesart eines
  Masses** (2026-08-31, best. 2026-09-01). Zweimal so gefunden — das exakte Doppelte der
  Strategievielfalt (Fensterlesart Mass 3) und `R × (1 + 60)`, woraus folgt, dass je
  Kandidat **ein** Weltschritt gerechnet wird, also eine statische Bewertung noetig ist,
  die nirgends steht.
- **Eine Bedingung, die auf einer Messung steht, wird nachgemessen, nicht zitiert**
  (2026-08-31, best. 2026-09-01). Der eigene Abruf der Sollreihen-Belegtheit brachte den
  teuersten Befund ueberhaupt (Partielaenge vier Jahre zu lang). Ein Abruf, und das Urteil
  ist unangreifbar.
- **Zwei Quellen, die sich nicht kennen, sind der billigste Beweis** (2026-09-03, best.
  2026-09-04). Die 40 Handelsadressen in `daten/adressen.md` belegten die Entdopplung ohne
  Begruendung; die Preistraegheitsregel belegte einen vorgegebenen Startwert; im 14. Lauf
  belegte `spiel.md:1249` die 106 der Kostenzeile. *Nie gegen die Rechnung des Dokuments
  zaehlen.*
- **Die Einheitentabelle gegen jede neue Formel legen** (2026-09-01, 6. Lauf) — der
  produktivste einzelne Handgriff. T5 trennte US-Cent von Tausend USD, T47 verband beide
  ohne `tsd_in_cent`, Faktor 100.000. *Erst die Skalenklasse jedes Symbols nachschlagen,
  dann die Formel lesen.*
- **Eine neu hingeschriebene Formel legt ihre eigenen undefinierten Eingaben offen**
  (2026-09-01). Viermal in Folge lag der teuerste Befund dort, wo eine Groesse zum ersten
  Mal *gerechnet* statt nur *benannt* wurde. *Jeden Namen darin einzeln greppen; ein
  Treffer heisst „nur die Verwendung".*
- **Eine Ablehnungsbegruendung ist eine Pruefvorschrift, die der Entwerfer auf sich selbst
  nicht angewandt hat** (2026-09-02, 7. Lauf). Der Fund kam aus dem **Einsetzen**, nicht
  aus dem Text; die Prosa war widerspruchsfrei.
- **Bei einer Umschreibung die Vorfassung danebenlegen** (2026-09-03, 8. Lauf). Der
  teuerste Fund war *nicht da*: halbe Vorgabe gestrichen statt uebersetzt. Ein gestrichener
  Satz sieht in der neuen Fassung aus wie nichts. *Alte Marker greppen, jede Stelle auf
  einen Nachfolger pruefen.*
- **Ersetzt eine Aufzaehlung eine pauschale Regel, ist die Aufzaehlung der Befund**
  (2026-09-03). `overflow-checks` deckte jede Operation; der Ersatz nennt Mult-Div,
  Addition, Subtraktion — die blanke Multiplikation faellt heraus.
- **Wo ein Dokument sagt „diese Regel gilt hier nicht", nachsehen, ob es sie anderswo
  ueberhaupt gibt** (2026-09-01). Der Ausschluss war der Fund (T44).
- **Eine Groesse je Land, die als eine Zahl in eine Formel geht, braucht eine
  Aggregationsregel** (2026-09-01). Drei Lesarten, drei Sieger.
- **Behauptungen ueber Erzeugnisse an den Erzeugnissen pruefen** (2026-09-03). `nm`, und
  Grep liest auch Binaerdateien. Ebenso einen Abschnittsverweis in eine fremde Datei auf
  **Existenz** pruefen (14. Lauf, `spiel.md:863` — er stimmte).
- **Eine datierte Messung im Stand ihres Datums pruefen** (2026-09-04). „Sechs Zeilen"
  ergab heute 13, im Stand des Commits genau sechs. Ohne den Umweg haette ich eine
  richtige Zahl fuer falsch erklaert.
- **Bei einem Ruecklauf die Selbstmessungen der Behebung nachzaehlen, nicht ihre Zusagen**
  (2026-09-04, 11. Lauf). Zwei Zahlen und eine zitierte Parallele belegt — und **weil** sie
  stimmten, trug `geprueft`. Ein Urteil ohne solche Probe ist von Zustimmung nicht zu
  unterscheiden.
- **Zwei Lesarten sind zwei Rechnungen — beide rechnen, bevor der Befund geschrieben wird**
  (2026-09-04, 12./13. Lauf). Zwei Rundungswege ergaben dreimal dieselbe Zahl; `71,94/98,71`
  als `H/N` gelesen macht einen Widerspruch, als `H/(H+N)` stimmt alles — und die zweite
  Lesart belegte sich selbst am `H/N = 2,69` zwoelf Zeilen darueber. *Der Befund entsteht
  erst, wenn die Lesarten auseinanderfallen.*
- **Bei „zweimal unabhaengig gerechnet" fragen, wo die Kette anfaengt** (2026-09-04,
  13. Lauf). Zwei Laeufe hatten alles nachgerechnet — **ab** der Messtabelle, die sie als
  gegeben nahmen. Der einzige falsche Wert sass genau dort. *Die erste Zahl der Kette ist
  die, die niemand zweimal gerechnet hat.*
- **Kommt der eigene Befund als Pruefgegenstand zurueck, die eigene Zahl von vorn rechnen**
  (2026-09-04, best. im 14. Lauf an der 112 aus meinem Befund vom 2026-09-02).
  Wiederzuerkennen waere keine Pruefung. Gilt auch fuer eigene Paketvorschlaege (0054).
- **„Kommt nirgends anders vor" schliesst man mit zwei Zaehlungen, nicht mit Lesen**
  (2026-09-04): `grep -c` auf beide Fassungen, 7 zu 7.
- **Pruefen, ob ein Lauf, den ein Mass vorschreibt, laufen kann** (2026-08-31).
- Kleiner, aber wiederholt bestaetigt: jede als „Anteil" deklarierte Groesse nachrechnen
  (Bruttostrom durch Nettogroesse ist nie ein Anteil); nach einer geaenderten Grundzahl die
  abgeleiteten nachrechnen; bei einer neuen Fassung pruefen, ob die beantworteten
  Rueckfragen die aktuellen sind; ein Abzaehlschritt ueber Zustandsadressen findet **nur**
  Zustandsadressen (beide Befunde lagen bei Funktionen).

## Was nicht funktioniert

- **Kein Arbeitspaket, zweimal in Folge** (2026-08-31). Ersatzkriterien selbst zu bauen
  macht das Urteil angreifbar; messbar: zwoelf Befunde ohne Paket, drei mit, bei gleicher
  Suchtiefe. *Erste Handlung jedes Laufs bleibt `ls aufgaben/`.* Achtung: Das Kriterium ist
  die Abnahme **des gepruefen Pakets**, nicht die fuenf Bedingungen aus `0001` — das Paket
  ist seit 2026-09-01 `fertig` und vom Betreiber geschlossen.
- **Die Ausschlussliste des Pakets aktiv gegen sich selbst anwenden** (2026-09-01).
  „Kalibrierbare Zahl ist kein Befund" und „Genauigkeit ueber die Bedingungen hinaus" haben
  mir je zwei begruendbare Kandidaten getoetet. Sie gehoeren in den Abschnitt *wonach ich
  gesucht habe* — dort belegen sie die Tiefe, im Befundteil waeren sie Rauschen. Am
  2026-09-04 so eingeordnet: Notation ohne Zahlwiderspruch, ein offener Nachzug (0064), ein
  Satz aelter als das Paket.
- **Ein Fehler ausserhalb der Abnahmebedingungen ist kein Ruecklauf** (2026-09-04,
  14. Lauf). Zwei echte Zaehlfehler, aber im Selbstbericht statt im normativen Teil:
  Urteil `geprueft` **und** ein Paketvorschlag. Ein Ruecklauf haette ein Paket gegen ein
  Kriterium geoeffnet, das es erfuellt — genau der Fehler, den `0001` beschreibt.
- **Eine Bedingung, die zwei Gewerke gemeinsam erfuellen muessen, kann ein Lauf mit einem
  Gewerk nicht schliessen** (2026-09-01). *Erst `git log --name-only` auf die betroffenen
  Dateien, dann urteilen*; das gehoert an den Projektmanager.
- **Vor dem Urteil `ls -la` statt `ls` auf `befunde/`** (2026-09-01). Eine Pruefung hat eine
  **0 Byte grosse** Datei abgelegt und committet; im Listing sieht sie aus wie eine volle.
- **In Bash nur absolute Pfade, nie `cd`** (2026-09-04). Ein `cd` nimmt mir alle
  Schreibrechte, und zwei frueher notierte Diagnosen waren deshalb falsch. *Kommt eine
  Verweigerung, zuerst `pwd`.*
- **`git show` wird verweigert, `git diff` nicht** (2026-09-04, 13. Lauf) — ebenso jede
  Revision mit `^`. Weg zum Diff eines Commits: Elternhash aus `git log --oneline` ablesen,
  dann `git --no-pager diff --stat <eltern> <commit>`, **ein Kommando je Aufruf**.
- **`python3 -c` wird verweigert** (2026-09-04). Rechnen heisst Handrechnung — mit
  hingeschriebenen Zwischenprodukten, was ohnehin der bessere Nachweis ist.

## Offene Faehrten

- **Mass 2 hat zwei Lesarten und niemand hat gewaehlt:** Frontmatter „hoechstens 25 Prozent
  besser" gegen `max(Ek) ≤ 1,25 × min(Ek)` (`spiel.md` Z. 976). Von 0039, 0055 und 0043
  nicht angefasst, deshalb dreimal nicht gemeldet. **In einem Paket, das Mass 2 beruehrt,
  ist es ein Befund** — dann zuerst hierhin sehen.
- **Mass 4 bleibt das groesste Risiko und ist kein Entwurfsfehler.** Ob 20 Prozent MAPE und
  0,6 Richtungstreue mit endogener Produktivitaet erreichbar sind, sagt erst der
  Rueckvergleicher am laufenden Kern.
- **Die Bewertung der vier Anleihe-Steckplaetze hat keinen Preis im Zustand** (T15 fuehrt
  `leitzins` und `staatsschuld`, keinen Kurs). Wird sie nachgetragen, hier zuerst nachsehen.
- **Die Bruchstelle „eine Groesse mit zwei Herren" bleibt seit dem 7. Lauf aus.** Die Funde
  sitzen seither in Begruendungen und Vollstaendigkeitsbehauptungen, nicht in Formeln. Am
  13. Lauf in einer Messtabelle, am 14. im Selbstbericht — die Funde wandern nach aussen.
- **`technik.md` fuehrt weiter 25 Stuetzstellen und `R = 24`**, waehrend `spiel.md` seit
  0054 das Fenster 2001–2021 hat; der Nachzug ist **0064, am 2026-09-04 noch `offen`**.
  Solange er offen ist, ist die alte Zahl **kein** Befund — aber jede Rechnung darauf
  gehoert in beiden Fenstern geprueft.
- **`werte.hpp` sagt „siebzehn", T48 fuehrt seit 0043 zweiundzwanzig Groessen.** Der Nachzug
  ist Kernbauer-Arbeit und noch nicht geschnitten; mein Vorschlag **0092** berichtigt
  zuvor die Stellenliste. Kommt eines von beiden zur Pruefung, hier zuerst nachsehen.
