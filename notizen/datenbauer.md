# Logbuch: datenbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/datenbauer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

---

## Was funktioniert

- 2026-09-01 — Die Weltbank-Schnittstelle hat **zwei** Endpunkte je Reihe, und nur einer
  liefert das im Auftrag verlangte Feld unter seinem eigenen Namen:
  `api.worldbank.org/v2/sources/2/series/<code>/metadata?format=json` nennt es wörtlich
  `Source` und gibt zusätzlich `License_Type`, `Periodicity` und `Referenceperiod`;
  `api.worldbank.org/v2/indicator/<code>?format=json` nennt dasselbe
  `sourceOrganization`. Der Metadaten-Endpunkt ist der ergiebigere — mit ihm anfangen.
- 2026-09-01 — **Beide Endpunkte für dieselbe Reihe abrufen ist die Gegenprobe gegen das
  Werkzeug, nicht gegen die Quelle.** Der Seitenabruf reicht auf, statt roh
  durchzureichen; ein einzelnes Zitat kann umformuliert sein. Zwei Abrufe verschiedener
  URLs mit zeichengleichem Ergebnis sind der billigste Wortlautbeleg, den diese Rolle
  bekommen kann. Kostet einen Abruf je Reihe.
- 2026-09-01 — **Kontrollabrufe sind der Kern der Arbeit, nicht die Zugabe.** Das Feld
  `License_Type` sah aus wie die Antwort auf die ganze Paketfrage. Drei Abrufe auf
  Reihen mit völlig anderer Herkunft (ITU, World Federation of Exchanges,
  weltbank-eigenes BIP) ergaben denselben Wert `CC BY-4.0` — ein Feld, das nie
  widerspricht, unterscheidet nichts. Ohne die Kontrollen hätte ich es als Freigabe
  gelesen. *Regel für den nächsten Lauf:* Bevor ein Metadatenfeld ein Urteil trägt, an
  einem Fall messen, bei dem es widersprechen müsste.
- 2026-09-01 — Wenn eine Reihe einen Drittanbieter nennt, ist die nächste Frage nicht
  „wie schlimm", sondern **„was sagt dieser Drittanbieter selbst".** Zwei von vier
  Verdachtsreihen lösten sich so auf (IWF erlaubt das Verkaufen, ILO seit 2023-05-03
  CC BY 4.0), eine blieb hängen, weil ihre Anbieter die Zustimmung ausdrücklich
  vorbehalten. Der Verdacht allein entscheidet nie.

- 2026-09-01 (Paket 0007) — **Tabellenzeilen durchnummerieren macht die eigene Arbeit
  ohne Shell prüfbar.** Ohne Bash ist `Grep` mit `output_mode: count` der einzige Zähler,
  den diese Rolle hat; eine laufende Nummer plus ein Spaltenmuster
  (`^\| [0-9]+ \|.*\| 11 \| [^|]+ \|$`) ersetzt `awk`. Vier Zerlegungen einer 310er-Menge
  waren so in zwölf Aufrufen belegt statt geglaubt.
- 2026-09-01 (Paket 0007) — **Zuletzt die eigenen Prosazahlen prüfen, nicht die Tabelle.**
  Die 310 Zeilen stimmten auf Anhieb; falsch war ein Satz *über* die Tabelle. Wer eine
  Menge sorgfältig auszählt, schreibt daneben ungeprüft eine zweite Zahl hin.

- 2026-09-02 (Paket 0014) — **Die Kontrolle muss diesmal in die andere Richtung laufen: Sagt
  das Feld jemals gar nichts?** Bei `License_Type` war die Frage „widerspricht es je"; beim
  Feld `Source` ist sie „nennt es je *keinen* Fremdbestand". Ein Abruf auf eine
  weltbank-eigene Reihe beantwortet sie mit ja — und erst dadurch ist das Nennen einer
  fremden Stelle eine Aussage statt einer Formelzeile. Ein Feld, das immer dasselbe sagt,
  entscheidet nichts; eines, das schweigen kann, schon.
- 2026-09-02 (Paket 0014) — **Nie von einem Code einer mehrcodigen Reihe auf die Reihe
  schliessen.** Drei Geschwistercodes derselben Zeile trugen zwei verschiedene
  `Source`-Texte, und der Unterschied verschob die Zahl der betroffenen Sollreihen um den
  Faktor drei. Ein Abruf je Code, ausnahmslos.
- 2026-09-02 (Paket 0014) — **Der Seitenabruf kürzt wörtliche Zitate bei etwa 125 Zeichen.**
  Wer einen ganzen Lizenzsatz braucht, lässt ihn in nummerierten Bruchstücken von je
  höchstens 100 Zeichen ausgeben; aneinandergehängt ergibt sich der Wortlaut. Ohne diesen
  Kniff bleibt jeder längere Vertragssatz ein Fragment.

## Was nicht funktioniert

- 2026-09-01 — `imf.org` weist den direkten Abruf weiterhin mit **HTTP 403** ab, genau
  wie am 2026-08-31 beim Datenkurator. Dasselbe gilt neu für `ilostat.ilo.org`. Nicht
  erneut versuchen; der IWF-Wortlaut bleibt nur über Suchtreffer belegt und ist eine
  Sache für den Betreiber.
- 2026-09-01 — Ausweichhost statt Aufgeben: `ilostat.ilo.org` sperrt, `www.ilo.org`
  nicht. Bei einer 403-Sperre lohnt **ein** Versuch auf der Hauptdomain derselben
  Organisation, bevor man auf einen Suchtreffer zurückfällt. Beim IWF gab es keine
  solche zweite Adresse.

- 2026-09-01 (Paket 0007) — `Bash` ist dieser Rolle gesperrt, auch `cat` und `wc -c`.
  `Read` mit `offset`, `Glob` und `Grep` reichen; nicht erneut versuchen. — *2026-09-02:
  Lesende Shell-Befehle liefen wieder, `curl` wurde abgewiesen. Der Netzzugang bleibt der
  Seitenabruf; Rohtext über die Shell gibt es nicht.*
- 2026-09-02 (Paket 0014) — **Ein Ausweichhost derselben Organisation führt nicht zwingend
  denselben Text.** Bei der ILO trug er, beim IWF nicht: Die zweite IWF-Adresse führt die
  Bedingungen einer anderen Webseite, nicht den Datenabschnitt. Vor dem Zitieren prüfen, ob
  der Abschnitt überhaupt derselbe ist — ein falscher Volltext ist schlimmer als gar keiner.
- 2026-09-02 (Paket 0014) — Der Etalab-Lizenztext liegt nur französisch vor;
  `…/LO.en.md` gibt 404, und der PDF-Link auf `etalab.gouv.fr` leitet auf `data.gouv.fr`
  um. Der Weg, der trägt: `raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md`.

## Offene Fährten

- **Paket 0014, worauf ich unsicher bin, für den Projektmanager:** Ich habe die drei
  IWF-Reihen `unklar` genannt, weil ihr Lizenztext nach fünf Anläufen ungelesen bleibt und
  ein Suchauszug einen Vorbehalt im Definitionssatz andeutet — und zugleich die beiden
  `frei`-Urteile aus 0005 stehen lassen, die auf demselben Text ruhen. Das ist angreifbar.
  Ich habe es nicht aufgelöst, weil 0005 nicht mein Paket ist, und beide Zahlen
  nebeneinandergestellt. Ein Prüfer wird entweder die Konsequenz oder die Zurückhaltung
  loben; eines von beidem ist falsch, und ich weiss nicht, welches.
- **Zweite Unsicherheit aus 0014:** Ob „Country official statistics, National Statistical
  Offices" eine Reihe überhaupt zu einer „von Dritten bereitgestellten" macht, entscheidet
  acht Sollreihen. Sagt der Betreiber nein, sind zwei der drei Sektorcodes frei und die
  Zusammenfassung sieht anders aus. Die Frage ist bewusst offen gelassen.
- **Paket 0014, ungemessen und nicht mein Paket:** Wird Reihe 1 auf PWT umgestellt, wechselt
  das Basisjahr. Welches PWT 11.0 trägt, habe ich nicht nachgesehen — es gehört zur Deckung
  (0006), aber es ändert die Sollreihe und damit den Massstab von T42. Wer den Ersatz zieht,
  zieht ihn vor dem Einfrieren des Jahrgangs.

- **Paket 0007, worauf ich unsicher bin:** Von den 310 Adressen sind **177 gebildet**,
  nicht zitiert. Drei Stellen haben *keine* Vorlage statt einer schwachen, und nach T17
  gehört jede in die Schnittstellenversion: die Gebietskennung `RW` im Handelsblock,
  `welt.preis.<s>` und `fonds.position.waehrung.<L>` / `.anleihe.<L>`. Jetzt ist der
  billigste Zeitpunkt, sie anders zu wollen.
- **Paket 0007, gemeldeter Widerspruch, bewusst nicht behoben:** `technik.md` T23 Punkt 1
  schreibt die Restverzögerung als `…​.rest`, T15/T38/T45 nennen sie durchgehend
  Restverzögerung. Ich habe `restverzoegerung` gesetzt und es als Befund gemeldet; eine
  Adressänderung braucht nach T17 einen ADR und nicht meine Wahl.
- **Paket 0007, drei erfundene Namen, alle markiert:** die Parameterschlüssel
  `startzustimmung` und `regulierung_start` und der Manifestname `marktkorb_start`. Sie
  gehören zu Paket 0009 beziehungsweise ins Manifest — markiert, damit sie beim
  Zusammenführen auffallen, statt sich stillschweigend durchzusetzen.
- **Worauf ich unsicher bin, für den Projektmanager:** Mein Urteil zu Reihe 7
  (Beschäftigung, ILO) lautet `unklar` und nicht `frei`, obwohl die ILO ihre Datenbanken
  im Wortlaut unter CC BY 4.0 stellt. Grund: Die ILO steht nicht unter den in `daten.md`
  geprüften Quellen, und meine Grenze sagt, eine ungeprüfte Quelle ist nicht erlaubt,
  sondern ungeprüft. Ein Prüfer kann das ebenso gut als übervorsichtig lesen. Der Ersatz
  aus T26 kostet keine Sollreihe, also kostet die Vorsicht hier fast nichts — bei Reihe
  13 hätte ich sie so nicht wählen dürfen.
- **Zweite Unsicherheit:** Die Reihen 8 und 10 habe ich `frei` genannt, obwohl ihre
  Freiheit an den IWF-Bedingungen hängt, die niemand im Volltext gelesen hat. Ich habe
  sie nicht `unklar` genannt, weil das Urteil dann nicht mehr die WDI-Reihe beträfe,
  sondern eine der vier tragenden Quellen des Vorhabens — und darüber entscheidet nicht
  dieses Paket. Die Zahl für den Fall (7 der 31 Sollreihen) steht im Befund.
- Der Datenkurator könnte die ILO mit **einem** Abruf
  (`www.ilo.org/rights-and-permissions`) in die geprüften Quellen aufnehmen. Dann wird
  Reihe 7 `frei` und drei Startwerte behalten ihren Datenanker.
- Für Reihe 13 gibt es nach `daten.md` **keine** Zollquelle unter freier Lizenz: WTO,
  WITS und UNCTAD TRAINS sind alle negativ oder widersprüchlich. `daten.md` nennt MacMap
  des ITC als ungeprüfte Alternative — falls jemand den Zollpfad retten will, ist das die
  einzige offene Adresse, und sie gehört dem Datenkurator, nicht mir.
- Nebenbei gesehen, nicht angefasst (gehört zu Paket 0006): `Referenceperiod` von
  `TM.TAX.MRCH.WM.AR.ZS` ist `1988-2022`, von `FP.CPI.TOTL.ZG` und `PA.NUS.FCRF`
  `1960-2025`, von den drei `SL.*.EMPL.ZS` `1991-2025`. Der Prüfjahrgang 1997–2021 liegt
  in allen vieren — das ist eine Aussage über die *Reihenlänge*, nicht über Lücken je
  Land, und die Deckungsfrage bleibt damit offen.
