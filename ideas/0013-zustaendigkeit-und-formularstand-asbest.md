---
id: 0013-zustaendigkeit-und-formularstand-asbest
titel: Welche Behoerde, welches Formular, welche Anlagen — Nachschlagewerk zur Asbestanzeige
status: entwurf
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: ideator

quelle: signals/maerkte/2026-08-28-dachdeckerbetriebe.md

segment: Dachdecker- und Bedachungsbetriebe in Deutschland unter zehn gewerblichen Mitarbeitern, die Asbestzement-Wellplatten abnehmen und dabei ueber Landes- oder Bezirksgrenzen hinweg arbeiten — also Betriebe, fuer die der Adressat der Anzeige mit jeder Baustelle wechselt. Auffindbar ueber die rund 200 Innungen des ZVDH und die Verbandszeitschrift DDH.
problem: Die objektbezogene Asbestanzeige geht an die Arbeitsschutzbehoerde am Ort des Objekts, nicht am Firmensitz. Ein bundeseinheitliches Portal gibt es nicht: NRW stellt PDF-Formulare bereit, Berlin fuehrt ein eigenes Verfahren. Wer landesuebergreifend arbeitet, sucht Zustaendigkeit, geltende Formularfassung und Anlagenliste bei jeder fremden Baustelle neu zusammen.
loesung: Ein gepflegtes Verzeichnis, das zu einer Objektadresse die zustaendige Stelle, das aktuell geltende Formular und die vollstaendige Anlagenliste ausgibt — ohne Personendaten, ohne Ausfuellen, ohne Terminueberwachung.
zahlungsgrund: zwang

ablehnungsgrund: null

score:
  zwang: null
  erreichbar: null
  ruhe: null
  marge: null
  genehmigung: null
  summe: null
---

## Belege

Quellen aus dem Marktprofil uebernommen, Abrufdatum dort vermerkt; nicht selbst erneut
abgerufen.

- Der Adressat wechselt mit der Baustelle, nicht mit dem Betrieb: Die objektbezogene Anzeige
  geht an die Arbeitsschutzbehoerde am Ort des Objekts, die unternehmensbezogene an die am
  Firmensitz. Arbeitsschutz NRW, Fachthema Asbest
  (https://www.arbeitsschutz.nrw.de/fachthemen-publikationen/gefahrstoffverordnung/asbest),
  abgerufen 2026-08-28.
- Kein bundeseinheitliches Portal. NRW stellt PDF-Formulare ueber die Bezirksregierung bereit,
  fuer Berlin ist ein eigenes Verfahren belegt. Die BAuA haelt Musterformulare zur TRGS 519
  bereit (Fassung 19.05.2026) — der Abruf per Skript wurde mit HTTP 403 abgewiesen, die
  Existenz ist nur ueber die Trefferliste belegt.
- Beizufuegen sind Beschaeftigte namentlich, Qualifikationsnachweise, Nachweise der
  arbeitsmedizinischen Pflichtvorsorge, Gefaehrdungsbeurteilung/Arbeitsplan nach Anlage 1.4
  TRGS 519 und Betriebsanweisung. https://www.ddh.de/bg-bau-neue-asbestpflichten-fuer-dachdecker-20022026,
  abgerufen 2026-08-28.
- Keines der sieben geprueften Handwerksprogramme deckt die Anzeigepflicht ab; fuer die
  Anzeigepflicht selbst wurde kein Anbieter gefunden (Marktprofil, Abschnitt 5).
- Segment und Kanal woertlich aus dem Profil: 15.241 SOKA-DACH-pflichtige Betriebe, 78 Prozent
  unter zehn Arbeitnehmenden; erreichbar ueber ZVDH mit rund 200 Innungen (~7.000
  Mitgliedsbetriebe, regionaler Organisationsgrad ueber 70 Prozent), DDH als Verbandsorgan,
  DACH+HOLZ (naechste Ausgabe erst 2028), SOKA-DACH als Pflichtkontakt.

**Warum dieser Zuschnitt neben 0012 steht:** 0012 fuellt das Formular aus und haelt dafuer
Personendaten vor. Dieser Zuschnitt tut beides nicht. Er speichert keine Beschaeftigtendaten
(damit kein Art.-9-Risiko und kein G6-Pfad ueber Datenabfluss), uebernimmt keine Frist (damit
kein zweiter 0003-Fall) und trifft keine Wertung (die Risikostufe gibt der Nutzer an, das
Verzeichnis antwortet nur auf „welche Stelle, welches Formular"). Uebrig bleibt eine gepflegte
Tabelle. Ob dafuer jemand zahlt, ist die offene Frage — aber der Preis eines Fehlgriffs ist
eine Anzeige bei der falschen Stelle und damit ein verschobener Baustellenbeginn.

**Warum der Betriebsaufwand nicht mit den Kunden waechst:** Gepflegt werden 16 Laender mit
ihren Bezirksregierungen, nicht 15.241 Betriebe. Der Aufwand skaliert mit der Zahl der
Behoerden und der Formularaenderungen — das ist die Pruefrage von G4, und sie faellt hier
anders aus als bei 0004, das an kundenspezifischer Feldzuordnung starb.

## Wie der Zustand als Text aussaehe

- **Uebersicht:** `16 Laender, 41 zustaendige Stellen erfasst, 38 Formulare mit Fassungsdatum,
  3 seit der letzten Pruefung geaendert, 2 Stellen ohne belegten Formularlink.`
- **Detail:** eine Stelle vollstaendig — Bezeichnung, Zustaendigkeitsbereich als PLZ-Bereiche,
  Einreichweg (PDF per Post, E-Mail, Landesportal), Formularfassung mit Datum und Quell-URL,
  Anlagenliste, Datum der letzten Pruefung.
- **Veraenderung:** `2026-09-03: Bayern Formularfassung 06/2026 -> 08/2026, Feld
  "Vorsorgenachweis" neu; Berlin Einreichweg von E-Mail auf Landesportal umgestellt.`

Ein Agent kann daraus pruefen, ob das Ergebnis stimmt: jede Stelle mit Quell-URL und
Pruefdatum, jede PLZ Deutschlands genau einer Stelle zugeordnet, keine Fassung aelter als der
zuletzt geprueften Quelle.

**Gestaltungsentscheidungen:** selten, hoechstens jaehrlich. Das Produkt ist im Kern eine
Tabelle mit einer Suchmaske.

## Offene Fragen

- **Wie unterschiedlich sind die 16 Landesformulare wirklich?** Diese Frage entscheidet die
  Idee vollstaendig — anders als bei 0012, wo sie nur den Mehrwert schmaelert. Sind die
  Formulare nahezu identisch und die Zustaendigkeit trivial ableitbar, gibt es nichts zu
  verkaufen. Geprueft sind bislang NRW und ein Hinweis auf Berlin.
- Stellt eine Behoerde, die BAuA, die BG BAU oder der ZVDH dieselbe Uebersicht bereits kostenlos
  bereit? Das Marktprofil hat nach Anbietern gesucht, nicht nach amtlichen Uebersichten. Nach
  meinem Logbuch vom 2026-08-28 ist der dokumentierte Nullpreis das haeufigste stille Ende
  solcher Ideen — diese Frage ist vor allen anderen zu klaeren.
- Wie oft aendern sich Formularfassungen und Zustaendigkeiten? Daraus ergibt sich der laufende
  Pflegeaufwand und damit G4. **Vermutung, ungeprueft:** wenige Aenderungen im Jahr.
- Wie viele Dachdeckerbetriebe arbeiten ueberhaupt landesuebergreifend? Das Segment ist eine
  Teilmenge der Asbest-Betriebe und damit deutlich kleiner als 15.241 — bei einem
  Nachschlagewerk mit kleinem Abo-Preis ist das die Frage an G7. Der Fit-Filter hat 0011 genau
  daran scheitern lassen.
- Traegt ein Preis, der niedrig genug ist, damit ein Betrieb ein blosses Nachschlagewerk kauft,
  ueberhaupt ein Nebengewerbe nach Steuern? Alternativ waere der Datensatz an die Anbieter von
  Handwerkersoftware zu verkaufen — das habe ich nicht als eigene Idee aufgeschrieben, weil
  ein Vertragsabschluss mit fuenf Softwarehaeusern ohne Telefonat unwahrscheinlich ist und
  damit auf G3 zeigt, an dem bereits 0006 und 0008 gestorben sind.

## Warum jetzt

Vor dem 20.12.2025 stellte sich die Frage nach der zustaendigen Stelle fuer Dachdecker kaum:
Die objektbezogene Anzeige galt nur bei hohem Risiko, und Arbeiten an Asbestzement-Wellplatten
fallen dort nicht hinein. Mit der Ausweitung auf den mittleren Risikobereich betrifft die
Anzeige nun den Regelfall des Gewerks, und damit wird der laenderweise unterschiedliche
Verfahrensweg zum ersten Mal ein wiederkehrendes Alltagsproblem statt eines Sonderfalls fuer
Sanierungsspezialisten. Die BG BAU hat im Februar 2026 einen Leitfaden dazu veroeffentlicht,
die DDH das Thema am 20.02.2026 redaktionell aufgegriffen — die Betriebe wissen also, dass sie
ein Problem haben, und suchen gerade jetzt nach der Antwort.
