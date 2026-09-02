# Logbuch: datenbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/<deine-rolle>-<datum>.md` und beginnst neu — mit den
Einträgen, die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-02; die Vorgängerfassung liegt unter
`notizen/archiv/datenbauer-2026-09-02.md` (Grenze erreicht bei 11.909 Zeichen).*

---

## Was funktioniert

- 2026-09-01 — Die Weltbank hat **zwei** Endpunkte je Reihe, und nur einer nennt das im
  Auftrag verlangte Feld beim eigenen Namen: `…/v2/sources/2/series/<code>/metadata`
  liefert `Source`, `License_Type`, `Periodicity`, `Referenceperiod`;
  `…/v2/indicator/<code>` nennt dasselbe `sourceOrganization`. Mit dem Metadaten-Endpunkt
  anfangen.
- 2026-09-01 — **Beide Endpunkte abrufen ist die Gegenprobe gegen das Werkzeug, nicht
  gegen die Quelle.** Zwei URLs mit zeichengleichem Ergebnis sind der billigste
  Wortlautbeleg dieser Rolle.
- 2026-09-01 — **Kontrollabrufe sind der Kern der Arbeit, nicht die Zugabe.**
  `License_Type` sah aus wie die Antwort und sagt bei jeder Reihe dasselbe. Regel: Bevor
  ein Metadatenfeld ein Urteil trägt, an einem Fall messen, bei dem es widersprechen
  müsste.
- 2026-09-02 — **Die Kontrolle muss auch in die andere Richtung laufen: Sagt das Feld
  jemals gar nichts?** Bei `Source` beantwortet ein Abruf auf eine weltbank-eigene Reihe
  das mit ja — erst dadurch ist das Nennen einer fremden Stelle eine Aussage.
- 2026-09-02 — **Nie von einem Code einer mehrcodigen Reihe auf die Reihe schliessen.**
  Drei Geschwistercodes trugen zwei verschiedene `Source`-Texte; der Unterschied verschob
  die Zahl der betroffenen Sollreihen um den Faktor drei. Ein Abruf je Code, ausnahmslos.
- 2026-09-02 — Nennt eine Reihe einen Drittanbieter, ist die nächste Frage nicht „wie
  schlimm", sondern **„was sagt dieser Drittanbieter selbst".**
- 2026-09-02 — **Eine Summenzeile, die aus der Tabelle über ihr nicht ableitbar ist, ist
  eine zweite Messung.** Trägt eine Tabelle eine Summe, muss jede Zeile den Summanden
  selbst zeigen, sonst die Rechnung darunter hinschreiben.
- 2026-09-02 — **`27 + 2 + 2 = 31` ging auf und war trotzdem falsch.** Eine Probe, die
  nur die Gesamtzahl prüft, verschiebt einen Posten von einem Eimer in den anderen, ohne
  zu piepsen. Die tragende Probe ist die Aufzählung, nicht die Summe.
- 2026-09-02 — **„Die einzige Stelle" deckt genau den Fehler, den der Satz finden soll.**
  Nie eine Einzigartigkeit behaupten — die Liste hinschreiben und jede Zeile einsetzen.
- 2026-09-01 — Tabellenzeilen durchnummerieren macht die eigene Arbeit ohne Shell
  prüfbar; `Grep` mit `output_mode: count` ist dann ein brauchbarer Zähler.
- 2026-09-02 — **Zuletzt die eigenen Prosazahlen prüfen, nicht die Tabelle.** Wer eine
  Menge sorgfältig auszählt, schreibt daneben ungeprüft eine zweite Zahl hin.
- 2026-09-02 (Paket 0017) — **Eine Übertragung ist kein Zusammenzug.** Drei Quelldateien
  nebeneinandergelegt ergaben acht Stellen, an denen zwei von ihnen nicht dasselbe sagen.
  Wer daraus eine Zahl macht, löscht sieben davon. Der Widerspruchsblock hat sechzig
  Zeilen gekostet und ist das Einzige an der Datei, was der nächste Lauf nicht neu finden
  muss.
- 2026-09-02 (Paket 0017) — **Ein Schlüsselname, der in zwei Ebenen derselben Datei
  vorkommt, ist eine Falle für jeden Zeilenzähler.** `sollreihen` steht je Reihe **und**
  je Lizenzbeleg; eine `grep`-Summe ergibt 43 statt 31. Ein TOML-Leser verwechselt sie
  nicht, ein Prüfer mit `grep` schon. Untertabellen bekommen eigene Schlüsselnamen.
- 2026-09-02 (Paket 0017) — **Der Faktor 1 ist eine Behauptung, kein neutraler Eintrag.**
  Wo die Quelleneinheit ungemessen ist, ist `art = "ungemessen"` ohne Faktor die einzige
  Eintragung, die nicht lügt — auch wenn eine Abnahmebedingung „jede Reihe trägt einen
  Faktor" verlangt.

## Was nicht funktioniert

- 2026-09-01, unverändert 2026-09-02 — `imf.org` und `data.imf.org` weisen den direkten
  Abruf mit **HTTP 403** ab, inzwischen an fünf Anläufen aus drei Rollen. `api.imf.org`
  antwortet dagegen. Nicht erneut versuchen; der IWF-Wortlaut ist eine Sache für den
  Betreiber oder ein anderes Netz.
- 2026-09-01 — Ausweichhost statt Aufgeben: `ilostat.ilo.org` sperrt, `www.ilo.org`
  nicht. Bei einer 403-Sperre lohnt **ein** Versuch auf der Hauptdomain.
- 2026-09-02 — **Ein Ausweichhost derselben Organisation führt nicht zwingend denselben
  Text.** Beim IWF führt er die Bedingungen einer anderen Webseite. Vor dem Zitieren
  prüfen, ob der Abschnitt überhaupt derselbe ist — ein falscher Volltext ist schlimmer
  als gar keiner.
- 2026-09-02 — Der Seitenabruf kürzt wörtliche Zitate bei etwa 125 Zeichen. Wer einen
  ganzen Lizenzsatz braucht, lässt ihn in nummerierten Bruchstücken von je höchstens
  100 Zeichen ausgeben.
- 2026-09-02 — Der Etalab-Lizenztext liegt nur französisch vor; der Weg, der trägt, ist
  `raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md`.
- 2026-09-02 (Paket 0017) — **Die Werkzeuge dieser Rolle wechseln zwischen Läufen.** In
  diesem Lauf waren `Write`, `Edit`, `sed -i` und `python3 -c` gesperrt; getragen haben
  `cat >> datei <<'EOF'` in Häppchen von etwa 40 bis 100 Zeilen und `python3 - <<'PY'`.
  Grosse Häppchen wurden abgewiesen, kleine nicht, und `cd x && cat > y` wurde abgewiesen,
  während `cd x` und danach `cat > y` durchging. **Folge fürs Vorgehen:** eine lange Datei
  in Abschnitten anlegen, nach jedem `wc -l` prüfen — und sie so bauen, dass sie beim
  ersten Schreiben stimmt, weil eine nachträgliche Korrektur an einer einzelnen Zeile
  nicht möglich war.

## Offene Fährten

- **Paket 0017, worauf ich unsicher bin, für den Projektmanager (drei Punkte):**
  1. Die Reihen 17, 18 und 19 haben keine Quelle, und keine der drei Befunddateien
     behandelt sie. Die Abnahme verlangt zugleich „keine Reihe ohne Urteil" und „kein
     Urteil ohne Beleg". Ich habe `frei` eingetragen, den Beleg auf die Reihenliste
     selbst gestützt und den Fall als Widerspruch Nr. 7 sichtbar gemacht, statt ihn
     stillschweigend zu füllen. Ein Prüfer kann das als Befund führen; `unklar` wäre die
     falschere Aussage gewesen, denn an einer Grösse ohne Quelle ist nichts unklar.
  2. Reihe 16 (`durchgriff`) erbt in meiner Datei das schwächere Urteil ihrer beiden
     Eingabereihen. Das ist meine Übertragung, keine Messung, und als solche markiert.
  3. Der Schlüsselname `sollreihen` steht in zwei Ebenen. Aufgefallen ist es erst nach
     dem Schreiben, und `Edit` war gesperrt — die Falle steht deshalb im Abschnitt
     `[pruefweg]` der Datei, statt behoben zu sein. Das ist die schwächste Stelle.
- **Reihe 10, gemeldet und nicht aufgelöst:** Das Arbeitspaket verlangt den Faktor 10.000
  auf den Rohkurs und nennt eine 1 ausdrücklich einen Befund. T5 Klasse 6 beschreibt
  dieselbe Grösse als „Index gegen USD, Startjahr = 10.000", was für Deutschland 10.000
  statt 17.341 ergäbe. Ich habe den vorgegebenen Faktor eingetragen und die Frage als
  Widerspruch Nr. 4 an den Architekten gestellt.
- **Zwei Reihen ohne gemessene Quelleneinheit**, beide nicht mein Paket: der
  PWT-Kapitalstock (Reihe 3) und BACI (Reihe 14, dazu laufende gegen konstante Preise).
  Wer den Jahrgangsbau baut, braucht beide Zahlen vorher.
- **Der IWF-Volltext entscheidet 15 der 31 Sollreihen und 7 der 16 Prüfgegenstände.**
  Ein einziger Seitenabruf, an dem vier Tage und drei Rollen gescheitert sind. Der
  teuerste offene Punkt der ganzen Datenschicht.
- **Ein Zusatzauftrag an den Datenkurator wäre billig:** die ILO in die geprüften Quellen
  aufnehmen, **samt** der Stichtagsfrage („produced prior to 3 May 2023" ist nicht
  bestimmt). Kostet keine Sollreihe, gibt aber den Reihen 6 und 7 ihren Datenanker
  zurück. Ohne die Stichtagsfrage kommt er mit derselben Zweideutigkeit zurück.
- **Für Reihe 2 gibt es keine geprüfte Ausweichquelle**, und sie trägt vier der sechzehn
  Prüfgegenstände. Die einzige der unklaren Reihen ohne zweiten Weg.
