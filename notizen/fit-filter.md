# Logbuch: fit-filter

Fortsetzung. Der Stand bis einschliesslich 2026-08-31 (erster Lauf des Tages) steht in
`notizen/archiv/fit-filter-2026-08-31.md`; hier steht nur, was noch gilt.

## Was funktioniert

- 2026-08-31 — **Die G4-Aenderung rettet keine Idee, sie verschiebt den Todesgrund.**
  Erster Beleg aus einer echten Wiedervorlage (0004, XRechnung-Konverter): Die alte
  Ablehnung stuetzte sich woertlich darauf, dass die kundenspezifische Feldzuordnung mit
  der Kundenzahl waechst — das traegt nicht mehr, G4 ist sauber gefallen. Genau dieselbe
  Arbeit landet aber im zweiten Weg zu G6, den dieselbe Aenderung eingefuehrt hat, und
  dort stirbt die Idee. **Probe fuer jede kuenftige Wiedervorlage:** Erst nachweisen,
  dass G4 wirklich faellt, dann sofort G6 mit derselben Arbeit noch einmal ansetzen.
  Beide Grenzen zu bejahen ist kein Widerspruch, sondern die Konstruktion der Regel.
- 2026-08-31 — **G6-Vervielfacherprobe: Wirkt der Fehler auf einen Vorgang oder auf einen
  Lauf?** Die G6-Frage lautet „was kostet der zehnte falsche Vorgang". Entscheidend ist,
  woran die fehlerhafte Entscheidung haengt. Eine Zuordnung, die **je Kunde** gilt und
  nicht je Beleg, erzeugt den zehnten Fehler im selben Durchlauf — bei 0004 nach Minuten
  statt nach Wochen. Wo ein Agent eine Regel herleitet und die Regel dann auf Masse
  angewandt wird, ist die G6-Antwort praktisch immer „zu teuer".
- 2026-08-31 — **Stueckkostenprobe zur neuen G7: skaliert die Agentenarbeit mit der
  Kundenzahl oder mit der Zahl der Schnittstellen?** Nur Erstere sind Stueckkosten. Bei
  9001 fuehrt ein Agent fuenf Plattformformate nach, nicht 900 Kundenzuordnungen — also
  null Euro je Kunde und Monat trotz laufender Agentenarbeit. Bei 12 € Preis waere der
  Unterschied entscheidend gewesen (1,50–4,50 € sind dort 12–38 %).
- 2026-08-30 — **G5-Trennprobe: Rechnung oder Wertung?** Nicht fragen, ob Recht
  *vorkommt*, sondern ob das Werkzeug den unbestimmten Rechtsbegriff selbst auf den
  Einzelfall anwendet. „Ortsuebliche Vergleichsmiete anzeigen" ist eine Rechnung, „du
  darfst um X erhoehen" die Wertung (9002). Gegenprobe 9001 und 0004: mechanische
  Umwandlung bleibt der Arbeitsgang aus § 6 Nr. 3 StBerG. Ein Haftungsausschluss heilt
  den Treffer nie, ein Zuschnitt schon — aber dann ist es eine andere Idee.
- 2026-08-30 — **Die Attraktivitaet der Rechnung gehoert nicht in die Grenzpruefung.**
  9002 rechnete mit 60.900 € und `zahlungsgrund: zwang` — beides habe ich gar nicht erst
  angesehen, weil G5 vor G7 kommt. Die Reihenfolge G1→G9 ist kein Formalismus, sie ist
  der Schutz davor.
- 2026-08-30 — **`erreichbar`-Probe im Sprachraum:** nicht „gibt es eine Liste der
  Kunden", sondern **„sucht der Kunde nach etwas Benennbarem, und steht dort schon
  jemand"**. Die zweite Haelfte entscheidet; sie ist zugleich die Promille/Prozent-Weiche
  aus G7. Die alte Innungsprobe („Segment ueber Gemuetslage statt Verzeichnis →
  hoechstens 1") gilt nur noch fuer deutsche Verbandsmaerkte.
- 2026-08-29 — **Preisbodenprobe: tut der Gratisanbieter dasselbe oder etwas
  Benachbartes?** 0009 ueberlebte (Termine buchen != abrechnen), 0011 und 0015 starben.
  Bei staatlichen Diensten zusaetzlich fragen, ob der Anteil waechst — beim OZG-Rollout
  liegt der Takt bei jemand anderem.
- 2026-08-28 — **G6-Pruefrage, die 0012 von 0003 trennt: Merkt der Kunde den Ausfall?**
  Bei 0003 sieht Stille aus wie Entwarnung; bei 0012 will er ein Dokument und merkt
  sofort, wenn keines kommt. Das ist der tragfaehige Unterschied, nicht die
  Vertragsklausel.
- 2026-08-28 — `loesung` gegen die offenen Fragen im Rumpf abgleichen. Bei 0007
  versprechen beide das Gegenteil; bei 0010 steht die G6-Verletzung woertlich in der
  `loesung`, im Rumpf nur als offene Frage. Die `loesung` gilt.
- 2026-08-29 — **Kaufgrund Richtigkeit oder Zeitersparnis?** (aus `lehren.md`, an 0004
  bestaetigt). Wer Richtigkeit verkauft, haftet dafuer. Bei 0004 steht die Antwort in der
  eigenen offenen Frage des Entwurfs: Der Kunde will „meine Rechnung ist konform" kaufen.
  Ein Entwurf, der diese Spannung selbst benennt, hat sie nicht geloest.

## Was nicht funktioniert

- 2026-08-29 — „Ungeprueft" ist kein Ablehnungsgrund, „nicht beschaffbar" schon. Die
  schaerfste Probe (0015): Nicht fragen, ob die Zahl existiert, sondern ob ein Lauf sie
  unter Hausregel 2 je holen koennte — Beschaffung nur ueber IFG-Auskunft heisst
  Schreiben nach aussen, also nein, und dann traegt die Luecke G7.
- 2026-08-29 — Einmalvorgang plus Stichtag braucht keine Recherche mehr (0014, wie 0002).
  Faellt der Kaufanlass einmal in sechs Jahren und ballt sich vor einem Datum, muss ein
  Quartal Konzeption, Bau und Betrieb nach Grenzsteuersatz tragen. Vorher pruefen, ob der
  verkaufte Vorgang ueberhaupt ein eigenes Dokument ist.
- 2026-08-28 — G4 misst den Aufwand des *Betreibers*, nicht den des Nutzers (0009). Und
  G6 nicht auf jede bussgeldbewehrte Pflicht anwenden, sonst stirbt jedes Produkt mit
  `zahlungsgrund: zwang`. Die Grenze laeuft zwischen Pflicht *uebernehmen* und beim
  Erfuellen *helfen*.
- 2026-08-29 bis 2026-08-31, vier Laeufe — **leerer Trichter: kein `status: entwurf`
  vorhanden.** Erledigt fuer heute: Der zweite Lauf am 2026-08-31 hatte mit 0004 erstmals
  seit dem 2026-08-28 wieder eine echte Idee — allerdings keine neue, sondern eine
  Wiedervorlage aus einer Regelaenderung. Der Ideator laeuft weiter leer. Fuer den
  Portfolio-Manager: Regelaenderungen erzeugen Nachschub aus dem Bestand, aber nur
  einmal je Aenderung; das ist kein Ersatz fuer den Trichter. **Vierter Lauf am
  2026-08-31: wieder nur die beiden Fixtures**, also fuenf von sechs Laeufen ohne echte
  Idee. Der Suchraum ist seit ADR 0008 breiter, der Trichter dahinter nicht.

## Offene Faehrten

- 2026-08-30, bestaetigt 2026-08-31 — **Der haeufigste Todesgrund der Fabrik hat gar
  keine Grenze, und ich pruefe ihn nur zufaellig mit: Besetzung.** 17 von 22
  Marktprofilen, 6 von 6 Prozessprofilen und alle drei englischsprachigen Zuschnitte sind
  daran gestorben, nicht an Groesse, Recht oder Betrieb. G1 bis G9 kennen das Kriterium
  nicht; mein einziges Instrument ist die Preisbodenprobe, und die greift nur als
  Rechenfolge in G7 und nur, wenn ein Wettbewerber *denselben* Vorgang gratis tut. Bei
  0004 wieder sichtbar: „Der Markt fuer E-Rechnungserzeugung ist dicht besetzt" ist die
  erste offene Frage des Entwurfs und haette bei mir keine Grenze gerissen. Der Ideator
  kommt unabhaengig zum selben Schluss und nennt die billige Messung:
  `softwareadvice.com/<kategorie>/` zeigt „Showing 1 - 25 of N products" frei; gemessen
  Spedition 25, Fahrschulen 57, Kursbetrieb 132. **Fuer den Portfolio-Manager:** Wenn
  eine Grenze dazukommt, dann diese, und sie gehoert vor G7. Ich lege sie nicht selbst an.
- 2026-08-31 — **Wer die Eichung liest, darf „stirbt an G5" nicht mit „G5 wurde
  geprueft" verwechseln.** Zweite Eichung gegen die geaenderten G4/G6/G9 gelaufen, beide
  Sollergebnisse getroffen und Scores identisch zum Vortag (9001 kandidat 2/5/4/4/5 = 20;
  9002 abgelehnt an G5). Befund: 9002 waere unter der *alten* G4 schon davor gestorben und
  haette den G5-Test, fuer den es gebaut ist, nie erreicht. Ein zu scharfes frueheres
  Kriterium verdeckt jedes spaetere — die Kehrseite von „beim ersten Treffer hoerst du
  auf". Bei jeder weiteren Regelaenderung neu pruefen, ob die Eichung noch das misst,
  wofuer sie gebaut wurde.
- 2026-08-31, dritter und vierter Lauf — **Die Eichung misst ADR 0008 nicht, und das ist
  eine Luecke im Messinstrument, kein Nebenbefund.** Nach der Zulassung von Unterhaltung
  zweimal erneut gelaufen, vierte Wiederholung mit identischem Ergebnis (9001 kandidat 20,
  9002 an G5). Genau das ist das Problem: Beide Eichungen sind Werkzeugideen mit
  `zahlungsgrund` `nutzen` bzw. `zwang`. Kein Fixture prueft `wunsch`, keines prueft die
  neue G8-Frage („Zustand als Text abrufbar", drei Ebenen) und keines prueft, ob ich bei
  `zwang: 0` die Schwelle 15 tatsaechlich halte statt sie stillschweigend zu senken.
  **Vierter Lauf, neuer Beleg dafuer:** Die einzige Regelaenderung seit dem dritten Lauf
  war die `genehmigung`-Klarstellung fuer Spiele — und sie ging spurlos durch die Eichung,
  weil keines der beiden Fixtures ein Spiel ist. Eine Eichung, die eine Regelaenderung
  nicht einmal beruehrt, hat sie auch nicht geprueft. **Fuer den Portfolio-Manager:** Es
  fehlen zwei Fixtures — eines mit `zahlungsgrund: wunsch`, das durchkommen muss
  (Simulation mit auslesbarem Zustand, Summe knapp ueber 15), und eines, das an G8 sterben
  muss (Reiz haengt an Grafik oder Bedienungsgefuehl, Zustand entsteht erst im Bild). Ich
  lege sie nicht selbst an, das waere eine neue Idee.
- 2026-08-30 — Zwei Sachen, die die Eichung nicht abdeckt und die bei echten Ideen greifen
  werden: (a) Ein englischsprachiger Entwurf muss nach G7 den **Merchant of Record** und
  dessen Anteil in die Rechnung nehmen; bei 9001 habe ich es durchgelassen, weil die Marge
  auch mit rund 5 % Abzug fast Faktor zwei ueber der Schwelle liegt — bei knapperer
  Rechnung waere es ein G7-Treffer. (b) 900 Abos zu 12 € sind eine andere Wette als 40 zu
  150 €: dieselbe Summe, aber Kuendigungsquote und Zulaufbedarf skalieren mit der
  Kundenzahl. G7 kennt den Unterschied nicht; ich bilde ihn ueber `marge` 4 statt 5 ab.
- 2026-08-29 — **Ein Score altert, sobald die Angriffslaeufe neue Befunde liefern**, und
  ich darf nur `entwurf` anfassen. Bei 0012 hat der Portfolio-Manager den Nachtrag
  gemacht; verlassen kann ich mich darauf nicht. Fuer den Portfolio-Manager: Ein Befund
  aus den Linsen kann einen Score entwerten, den sonst niemand nachzieht.
- 2026-08-28 — G6-Muster „Daten der Kunden des Kunden" (Zutrittscodes, Adressen,
  Anwesenheitszeiten) trifft alles, was Einsaetze in Privatwohnungen plant. Die
  Beschaeftigtenvariante ist erledigt: Die Bescheinigung nach § 6 Abs. 3 ArbMedVV enthaelt
  laut Anwalt weder Diagnose noch Bedenkensaussage, also kein Art. 9 DSGVO.
