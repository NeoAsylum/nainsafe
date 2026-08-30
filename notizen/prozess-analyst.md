# Logbuch: prozess-analyst

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/prozess-analyst-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- **2026-08-30** — Die Suche „Software fuer Pruefdienstleister <Vorgang>" beantwortet
  Frage 4 und Frage 6 in einem Abruf: Kommen branchenneutrale Anbieter mit eigener
  Landingpage zurueck, ist das Suchwort gemeinsam *und* besetzt. Das ist der billigste
  Test dieser Rolle — vor die Vereinigungszaehlung stellen, nicht danach.
- **2026-08-30** — Zuerst die `handarbeit`-Felder woertlich nebeneinanderlegen, dann erst
  addieren. Grep ueber alle Frontmatter (`segment|betriebe|handarbeit|potenzial`) kostet
  einen Aufruf und ersetzt das Lesen von 300.000 Zeichen Profiltext.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

- **2026-08-30** — Die Vorgangsgruppierung aus der Ausgangstabelle haelt der Pruefung
  nicht stand: Von 65.433 Betrieben beim Pruefnachweis bleiben 10.365. Facility macht
  einen vertraglichen, keinen gesetzlichen Nachweis; Dachdecker macht eine einmalige
  Anzeige je Baustelle, keinen Turnus; Spielplatzbetreiber sind Pflichtige, keine Pruefer.
  **Lehre: Ein `handarbeit`-Feld, das aehnlich klingt, ist noch kein gleicher Vorgang —
  drei Merkmale pruefen (fremdes Objekt? gesetzliche Frist? Vorlagepflicht?).** Die
  Marktprofile selbst sind korrekt, die Fehler stecken in der Gruppierung.
- **2026-08-30** — „Kleine Schale, grosser Kern" ist **kein** Fundsignal, sondern das
  Gegenteil. Ist der branchenneutrale Kern gross, hat ihn jemand gebaut; die vertikalen
  Anbieter beweisen dann nur Zahlungsbereitschaft, nicht eine Luecke. Der Fund braucht
  zusaetzlich, dass das horizontale Werkzeug **fehlt** — Frage 4 entscheidet, nicht Frage 3.

## Offene Faehrten

- **2026-08-30** — **Die Rollentrennung Pflichtiger/Pruefer ist die zweite Achse in der
  zweiten Achse.** Bei jedem Pflichtvorgang stehen zwei Parteien am selben Dokument mit
  gegenlaeufigem Interesse: Fuer den Pruefer ist der Vorgang Umsatz, fuer den Pflichtigen
  Ausgabe. Beim naechsten Vorgang der Liste zuerst entscheiden, auf welcher Seite
  geschnitten wird — sonst zaehlt man beide zusammen und rechnet mit einer Union, die es
  nicht gibt. Vermutung, an einem Vorgang belegt: Wo Fachkunde vorgeschrieben ist,
  entsteht immer ein Dienstleister, und dann ist die Prueferseite nie eine Last.
- **2026-08-30** — Ungezaehlte Prueferbranchen, die denselben Vorgang machen und fuer die
  ich keine amtliche Zahl fand: DGUV-V3-Pruefdienstleister, Torpruefer, Regalpruefer
  (DIN EN 15635), Trinkwasser-Probenehmer, Spielplatz-Pruefdienstleister. Keine wird als
  Wirtschaftszweig gefuehrt. Wer hier eine Zaehlung findet, hebt jede kuenftige
  Prueferunion — bei diesem Vorgang haette es das Urteil nicht gedreht.
- **2026-08-30** — Naechster Vorgang der Liste: **Behoerdenmeldung je Vorgang mit Formular
  und Frist** (Elektro 44.975, Dachdecker 15.241, SHK 48.000). Warnung vorab aus
  `lehren.md`: Dort ist die Behoerde der Wettbewerber und ihr Online-Dienst gebuehrenfrei —
  Frage 4 lautet hier „Serviceportal", nicht „Excel".

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

## Einträge

- **2026-08-30 (Start, vom Betreiber angelegt)** — Die Rolle entsteht aus einer
  Auszählung, die schon vorliegt: Die `handarbeit`-Felder der achtzehn Marktprofile
  gruppieren sich zu vier Vorgängen, und drei davon sind sechsstellig oder nahe daran.
  **Fang dort an, statt neu zu suchen.**

  | Vorgang | Profile mit diesem `handarbeit`-Feld | Betriebe |
  |---|---|---:|
  | Prüfnachweis mit Frist | dachdecker (15.241), aufzugswartung (841), kaelte (3.214), schaedlingsbekaempfer (1.074), spielplaetze (10.775), facility (34.288) | 65.433 |
  | Leistungsnachweis an Kostenträger | ambulante-pflegedienste (15.549), hebammen (19.000), physiotherapiepraxen (40.113) | 74.662 |
  | Behördenmeldung mit Formular | elektroinstallation (44.975), dachdecker (15.241), sanitaer-heizungs-klima (48.000) | rund 108.000 |
  | Verbrauchsabrechnung mit Zähler | campingplaetze (3.200), hausverwaltungen (24.600) | 27.800 |

  Zwei Warnungen aus den Profilen, die du beim Rechnen brauchst:

  - **Der Preisboden null ist im englischsprachigen Raum ein Geschäftsmodell.** Wo
    wiederkehrend Geld vom Endkunden durch die Software fließt, verschenkt der
    Wettbewerber das Abo und lebt vom Zahlungsstrom (Fahrschulen, Studios). Betrifft
    vor allem die Vorgänge *Beitragsabrechnung* und *Terminwiederbesetzung* — prüfe bei
    denen den Preisboden **vor** der Größe, das spart einen ganzen Profillauf.
  - **Die Kanalfrage ist die, an der hier bisher alles gestorben ist.** Bei dir ist sie
    schärfer als beim Markt-Analysten: Fünf Branchenverbände sind kein Kanal. Suche
    nach dem, was alle sechs Branchen gemeinsam haben — die Pflicht, die Prüffrist, das
    Wort, das alle googeln.
