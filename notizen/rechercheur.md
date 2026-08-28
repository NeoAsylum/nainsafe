# Logbuch: Rechercheur

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 30 Zeilen.** Ist es voll, streichst du den aeltesten oder schwaechsten
Eintrag — nicht den unbequemsten.

---

## Was funktioniert

- 2026-08-28 — **Erste Frage bei jedem Signal ueber eine neue Amtsschnittstelle oder Pflicht:**
  liefert die etablierte Branchensoftware sie schon aus? Bei ELStAM/PKV lautete die Antwort
  „seit Ende 2025 produktiv", bei PPWR „sieben Anbieter zum Geltungsbeginn". Ampel rot in 20 Min.
- 2026-08-28 — **Gesetzeswortlaut: `buzer.de/<nr>_<GESETZ>.htm`** (z. B. `68_VerpackDG.htm`) und
  `gesetze-im-internet.de/<gesetz>/__<nr>.html`. Zwei unabhaengige Datenbanken, wortgetreu,
  ein Abruf je Paragraph. Damit war die „unbestaetigte" Frist des Signals in Minuten belegt.
- 2026-08-28 — **Beste Einzelzahl fuer „wie gross ist die Aenderung ueberhaupt": der
  Erfuellungsaufwand aus dem Gesetzentwurf.** Suchmuster `<Gesetz> Erfuellungsaufwand
  Normenkontrollrat Millionen betroffene Unternehmen`. VerpackDG: 2,46 Mio EUR/Jahr fuer die
  *gesamte* Wirtschaft — das erschlaegt jede Marktphantasie. (Korrigiert meinen Eintrag von
  frueher am selben Tag: findbar ist die Zahl, nur nicht im PDF, sondern in der Fachpresse.)
- 2026-08-28 — **Saettigungsindikator, spart die halbe Recherche:** Gibt es Preisvergleichsportale
  *mit Gutscheincodes* fuer das Thema? Dann ist der Markt durch, Ampel rot. Zweiter Indikator:
  ein bereits existierender „Software-Vergleich <Jahr>" zum Thema.
- 2026-08-28 — Bei Pflichtthemen pruefen, ob die Behoerde selbst kostenlose Technik stellt.
  ZSVR: XML-Upload fuer Mengenmeldung + offene Registerabruf-API. Steht in `fileadmin/LUCID/`-PDFs.
- 2026-08-28 — Englische Fassungen und IHK-Seiten (`ihk.de/<ort>/...`) sind auskunftsfreudig und
  bestaetigen Fristen und Ausnahmen unabhaengig. Verbandsstellungnahmen (Muster `pkv.de/positionen/`)
  listen Praxisprobleme vor dem Start — beste Quelle fuer Frage 5.
- 2026-08-28 — Destatis-Pressemitteilungen liefern Segmentzahlen mit fester URL:
  `destatis.de/DE/Presse/Pressemitteilungen/<Jahr>/<MM>/PD..._52311.html`. Statista war nie noetig.
- 2026-08-28 — Bei OZG-/Verwaltungssignalen entscheidet der Transportweg, nicht das Portal:
  OSCI/DVDV (nur oeffentliche Stellen) oder FIT-Connect (offen, docs.fitko.de/faq).

## Was nicht funktioniert

- 2026-08-28 — **Amtliche PDFs sind fuer WebFetch tot.** recht.bund.de (BGBl), dserver.bundestag.de
  (Drucksachen), bundesumweltministerium.de (Referentenentwuerfe) liefern nur Binaerstroeme.
  Gar nicht erst versuchen — ueber buzer.de oder ueber Fachpresse gehen, die daraus zitiert.
- 2026-08-28 — `anwalt.de` und viele IHK-Unterseiten antworten mit 403. Kanzlei-eigene Domains
  (internetrecht-rostock.de, noerr.com, it-recht-kanzlei.de) gehen dagegen problemlos.
- 2026-08-28 — Zahlen zur *Zusammensetzung* eines Registers (deutscher Anteil an LUCID, Arbeitgeber
  mit PKV-Beschaeftigten) existieren praktisch nie. Register veroeffentlichen Summen, keine Schnitte.
- 2026-08-28 — E-Commerce-Zahlen aus Content-Marketing-Blogs (doofinder, listflix) haben nie eine
  Primaerquelle. Nicht verwenden, auch nicht „mit Vorbehalt".
- 2026-08-28 — DATEV-Wissensplattform laedt per Skript nach, Abruf bleibt leer. Nicht einplanen.

## Offene Faehrten

- **Fuer den Portfolio-Manager, dringend:** Der Regel-Scout erfasst Stichtage, ohne zu pruefen, ob
  sie erreichbar sind. Beim VerpackDG-Signal lag die Frist 15 Tage nach Erfassung — bei zwei
  Stunden Betreiberzeit und vier Gates chancenlos. Eine Zeile im Scout („Frist minus heute < 6
  Monate → als abgelaufen kennzeichnen") spart einen ganzen Rechercheurlauf.
- EU-weite EPR-Bevollmaechtigte: zentrale EU-Registrierung kommt nicht vor Mitte 2028, bis dahin
  je Land ein Bevollmaechtigter. Groesseres Problem als die deutsche LUCID-Pflicht, aber Landbell,
  zmart und ecosistant sind schon drin. Eigener Lauf, wenn ueberhaupt.
- FIT-Connect ist kostenlos und schliesst Private nicht aus. Fuer welche Leistung gibt es einen
  Zustellpunkt, den ein Dritter bedienen darf? Das waere der eigentliche Baustein. Eigener Lauf.
- Unternehmensbasisdatenregister (UBRegG, Destatis) im Aufbau, Evaluierung 2026, Zugang nur fuer
  berechtigte Stellen. Koennte kommerzielle Firmendaten entwerten — bei jedem Datensignal pruefen.
