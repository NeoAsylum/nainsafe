# Nachweis 0146 -- Aktionstyp und kanonische Ordnung

## Bezugsstand -- derselbe Baum ohne die drei Dateien dieses Pakets
  vorher / Profil ON -- Konfiguration Code 0
    Sperrebindungsriegel (T4, T7 Massnahme 4.2): 9 Kernquelle(n) und 11 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
    ctest-Eintraege: 11
    ok    der Bezugsstand konfiguriert durch
  vorher / Profil OFF -- Konfiguration Code 0
    Sperrebindungsriegel (T4, T7 Massnahme 4.2): 9 Kernquelle(n) und 11 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
    ctest-Eintraege: 11
    ok    der Bezugsstand konfiguriert durch

## Der Stand mit den drei Dateien -- beide Profile
  nachher / Profil ON -- Konfiguration Code 0
    Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
    ctest-Eintraege: 12
    Uebersetzung Code 0
    ok    uebersetzt gruen
    ctest Code 0
    ok    ctest gruen
    ok    ein ctest-Eintrag mehr als im Bezugsstand (11 -> 12)
  nachher / Profil OFF -- Konfiguration Code 0
    Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
    ctest-Eintraege: 12
    Uebersetzung Code 0
    ok    uebersetzt gruen
    ctest Code 0
    ok    ctest gruen
    ok    ein ctest-Eintrag mehr als im Bezugsstand (11 -> 12)

## Die Mutanten -- jeder muss rot werden, im Profil OFF
  m1 / Profil OFF -- Konfiguration Code 0
    Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
    ctest-Eintraege: 12
    Uebersetzung Code 2
    ok    uebersetzt rot
      /tmp/claude-1000/nachweis-0146/m1/kern/include/kern/aktion.hpp:303:19: error: static assertion failed: T32 Rang 0: die Aktionsart ueberwiegt Zielkennung und Stu
      299 | static_assert(ordnungsvergleich(Aktion{Art::Position, Zielkennung{ZIELKENNUNG_MAX},
      /tmp/claude-1000/nachweis-0146/m1/kern/include/kern/aktion.hpp:310:19: error: static assertion failed: T32 Rang 0: und in der Gegenrichtung ebenso
      306 | static_assert(ordnungsvergleich(Aktion{Art::Sichtbarkeit, Zielkennung{0},
      /tmp/claude-1000/nachweis-0146/m1/kern/include/kern/aktion.hpp:315:19: error: static assertion failed: T32 Rang 1: die Zielkennung ueberwiegt die Stufe
      313 | static_assert(ordnungsvergleich(Aktion{Art::Position, Zielkennung{0}, festkomma::I64_MAX},
      /tmp/claude-1000/nachweis-0146/m1/kern/include/kern/aktion.hpp:328:19: error: static assertion failed: T32: nach der Stufe zuerst zu ordnen ist genau die Nebenw
      326 | static_assert(ordnungsvergleich(Aktion{Art::Sichtbarkeit, Zielkennung{0}, i64{-9}},
  m2 / Profil OFF -- Konfiguration Code 0
    Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
    ctest-Eintraege: 12
    Uebersetzung Code 0
    ok    uebersetzt gruen
    ctest Code 8
    ok    ctest rot
      1/12 Test  #1: aktion_probe .....................***Failed    0.00 sec
      FEHLGESCHLAGEN Zeile 398: in_kanonischer_ordnung(rueckwaerts_eingabe, ANZAHL)
      FEHLGESCHLAGEN Zeile 399: in_kanonischer_ordnung(falsch_vorsortiert, ANZAHL)
      FEHLGESCHLAGEN Zeile 400: folgen_gleich(rueckwaerts_eingabe, falsch_vorsortiert)
      FEHLGESCHLAGEN Zeile 401: folgen_gleich(rueckwaerts_eingabe, SOLLFOLGE)
      FEHLGESCHLAGEN Zeile 402: folgen_gleich(falsch_vorsortiert, SOLLFOLGE)
      FEHLGESCHLAGEN Zeile 414: ordnungsvergleich(teil[k - 1], teil[k]) <= 0
      FEHLGESCHLAGEN Zeile 414: ordnungsvergleich(teil[k - 1], teil[k]) <= 0
      FEHLGESCHLAGEN Zeile 414: ordnungsvergleich(teil[k - 1], teil[k]) <= 0
      1 - aktion_probe (Failed)
  m3 / Profil OFF -- Konfiguration Code 0
    Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
    ctest-Eintraege: 12
    Uebersetzung Code 0
    ok    uebersetzt gruen
    ctest Code 8
    ok    ctest rot
      1/12 Test  #1: aktion_probe .....................***Failed    0.00 sec
      FEHLGESCHLAGEN Zeile 398: in_kanonischer_ordnung(rueckwaerts_eingabe, ANZAHL)
      FEHLGESCHLAGEN Zeile 399: in_kanonischer_ordnung(falsch_vorsortiert, ANZAHL)
      FEHLGESCHLAGEN Zeile 401: folgen_gleich(rueckwaerts_eingabe, SOLLFOLGE)
      FEHLGESCHLAGEN Zeile 402: folgen_gleich(falsch_vorsortiert, SOLLFOLGE)
      FEHLGESCHLAGEN Zeile 407: folgen_gleich(schon_geordnet, SOLLFOLGE)
      FEHLGESCHLAGEN Zeile 414: ordnungsvergleich(teil[k - 1], teil[k]) <= 0
      FEHLGESCHLAGEN Zeile 414: ordnungsvergleich(teil[k - 1], teil[k]) <= 0
      FEHLGESCHLAGEN Zeile 414: ordnungsvergleich(teil[k - 1], teil[k]) <= 0
      1 - aktion_probe (Failed)

Abweichungen: 0
