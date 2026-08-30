---
typ: pain
erfasst: 2026-08-30
quelle: https://www.herber.de/forum/archiv/1568to1572/1570749_maschinenwartung_und_Pruefliste_organisieren.html
abgerufen: 2026-08-30
betroffen: kleine Betriebe und Vereine mit Maschinenpark, Fuhrpark oder pruefpflichtigen
  Bauteilen -- ohne eigene Instandhaltungs-/CMMS-Software (u.a. Industriebetrieb mit
  pruefpflichtigen Bauteilen, Fuhrparkhalter, Sportverein mit Schiessstand-Vorrichtungen)
haeufigkeit: laufend -- die Liste muss bei jeder durchgefuehrten Wartung/Pruefung
  aktualisiert werden, Intervalle reichen von Monaten (Pruefungen) bis Betriebsstunden
  (Maschinen) bis TUEV-Terminen (Fahrzeuge)
heutige_loesung: selbstgebaute Excel-Tabelle mit Formeln (SVERWEIS, VERWEIS, WENNFEHLER),
  wiederholt ueber Jahre unabhaengig voneinander neu erfunden
---

# Wartungs- und Prüftermine für Maschinen, Geräte und Fuhrpark per Hand in Excel nachverfolgen

Kleine Betriebe ohne dedizierte Wartungssoftware bauen sich immer wieder eine eigene
Excel-Tabelle, um zu sehen, wann welches Bauteil, welche Maschine oder welches Fahrzeug
als Nächstes fällig ist. Das Muster taucht im selben Forum über mehrere Jahre hinweg mit
unterschiedlichen Postern und unterschiedlichen Branchen wieder auf, jedes Mal als
Neubau von vorne.

## Belegstelle

- 25.07.2017, Nutzer "Jürgen" zu wiederkehrenden Bauteilprüfungen: das manuelle
  Fortschreiben der Prüfdaten in neue Spalten „erwies sich als ein MegaAct und für den
  Enduser nicht praktikabel". Zusatzbedingung, die die Tabelle noch komplizierter macht:
  „nie mehr als 2 Bauteile gleicher Nennweite zur Prüfung fällig". (herber.de/forum/archiv/1568to1572/1570749_maschinenwartung_und_Pruefliste_organisieren.html, abgerufen 2026-08-30)
- 01.08.2016, Nutzer "Petro" baut eine Fuhrpark-Tabelle mit Fahrzeugdaten, TÜV-Terminen
  und Reparaturen über zwei verknüpfte Tabellenblätter (Fahrzeuge/Service); die
  Lösung deckt am Ende nur datumsbasierte Termine ab, kilometerbasierte Wartung bleibt
  manuell nachzutragen. (herber.de/forum/archiv/1504to1508/1507181_KFZ_Wartungsplan_erstellen.html, abgerufen 2026-08-30)
- Nutzer "Marcus" (Sportverein, mehrere Schießstände mit Vorrichtungen, vier
  unterschiedliche Wartungsintervalle, 87 Objekte): seine bestehende Tabelle „bedingt
  funktioniert aber ewig viel Arbeit verlangt"; eine „überschaubare Darstellung" bleibt
  am Ende des Threads ungelöst. (herber.de/forum/archiv/1872to1876/1874291_Wartungsplan.html, abgerufen 2026-08-30)
- Frühere, unabhängige Threads zum selben Grundproblem seit 2008 (u.a. „Wartungsplaner",
  „Wartungsplan erstellen", „Wartungsplaner mit VBA lösen", „Wartungsplan" nach
  Betriebsstunden 2018) zeigen, dass dasselbe Muster über mindestens zehn Jahre
  wiederkehrend neu gebaut wird, statt einmal gelöst zu bleiben.

## Was unklar ist

Ob diese Betriebe eine dedizierte Wartungssoftware (CMMS) überhaupt kennen oder bewusst
ablehnen -- aus der Quelle geht nur hervor, dass sie stattdessen selbst bauen. Unklar
auch, ob der Schmerz an der *Terminverfolgung* liegt oder an der *Dokumentation* der
durchgeführten Prüfung (Nachweispflicht) -- beides vermischt sich in den Zitaten. Keine
der Quellen sagt, ob dafür bezahlt würde; das selbstgebaute Excel ist der einzige
Kaufbeleg, der vorliegt.
