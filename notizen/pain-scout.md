# Logbuch: Pain-Scout

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 30 Zeilen.** Ist es voll, streichst du den ältesten oder schwächsten
Eintrag — nicht den unbequemsten. Ein Logbuch, das unbegrenzt wächst, liest am Ende
niemand mehr, auch du nicht.

---

## Was funktioniert

- 2026-08-28 — Suche nach konkreten Themen + "Forum" liefert meist nur Vorlagen-/
  Anbieter-SEO-Content. Besser: echte Nutzer-Communities direkt suchen, dann per
  WebFetch den Originalbeitrag holen fuer woertliche Zitate statt Such-Snippets.
- 2026-08-28 — community.etsy.com/t5/Etsys-deutsche-Community: mehrere unabhaengige
  Threads zur selben Aufgabe (Etsy/Amazon/eBay-CSV monatlich in Buchhaltung
  uebertragen) ueber Zeit hinweg — echtes wiederkehrendes Signal.
- 2026-08-29 — Bei Buchhaltungssoftware-Themen zuerst das Software-eigene Nutzerforum
  suchen (lex-forum.net fuer Lexware/lexoffice), nicht nur die Marktplatz-Community:
  dort liefen WebFetch-Abrufe sauber durch und brachten woertliche Zitate mit Zahlen
  (Signal: eBay-Sammelzahlungen manuell in lexoffice verbuchen). Vermutlich analog
  fuer sevDesk-/Debitoor-Community nutzbar.

## Was nicht funktioniert

- 2026-08-28/29 — Direkte Branchen+Suchmuster-Kombis liefern fast nur Vorlagen/
  Anbieter-Blogs, keine echten Klagen. Bestaetigt u.a. fuer: Steuerkanzlei/DATEV,
  Spedition, Hausverwaltung, Physiotherapie, KFZ, Gastro, Verein/SEPA, Handwerk-
  Kalkulation, Aufmass, Caterer, Aufzug, Tierarzt, Musikschule, Campingplatz,
  Maschinenring, Schaedlingsbekaempfer, Reddit pest-control/HVAC — dort lohnt
  generelle Suche kaum, nur gezielte Suche in konkreten Nischen-/Software-Foren.
- 2026-08-28 — Auch echte Nischenforen liefern oft kein Signal ohne erkennbaren
  Unmut in den Zitaten (Imkerforum, physio.de, landtreff.de) — reine
  Sachbeschreibung reicht nicht.
- 2026-08-28/29 — community.ebay.de, community.withairbnb.com, pflegeboard.de,
  pflegenetz.net per WebFetch wiederholt blockiert/Timeout (403, ECONNREFUSED,
  >60s) — dort gleich auf WebSearch-Snippet ausweichen, nicht wiederholen.
- 2026-08-28 — Alte Funde vor dem Schreiben auf Datum pruefen: Vereinskassenwart,
  Pflegedienst-Dienstplan, Handwerk-Excel-Rechnungen klingen stichhaltig, sind aber
  laengst mit SaaS besetzt — nicht ohne frische (<2 Jahre) Quelle neu aufgreifen.
- 2026-08-28 — site:reddit.com-Suchen liefern praktisch nie echte Reddit-Threads,
  nur Vendor-Treffer — im Zweifel auslassen.

## Offene Faehrten

- Etsy-CSV-Signal englischsprachig verstaerken: alter Link war 404, neu suchen.
- Ferienwohnungen mit mehreren Objekten: Payout-Abgleich Airbnb/Booking/Vrbo taucht
  wiederholt in Vendor-Blogs auf, aber weiterhin kein woertliches Nutzerzitat
  (2026-08-29 erneut versucht, BiggerPockets nur Forums-Uebersicht gefunden).
  Naechstes Mal gezielt einzelne BiggerPockets-Thread-URLs suchen und per WebFetch
  abrufen, statt der Forums-Startseite.
