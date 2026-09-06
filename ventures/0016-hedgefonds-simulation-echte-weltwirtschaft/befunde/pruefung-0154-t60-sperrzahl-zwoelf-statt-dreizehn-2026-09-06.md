---
typ: pruefung
paket: 0154-t60-sperrzahl-zwoelf-statt-dreizehn
pruefer: entwurf-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Abnahmebedingungen am Datei-Diff des Commits c3f6a8d und am HEAD-Text nachgemessen, die 12 auf vier voneinander unabhaengigen Wegen von vorn gerechnet.
befunde: 0
---

# Pruefung 0154 — T60-Sperrzahl zwoelf statt dreizehn

Vorbemerkung zur Befangenheit: Das Paket geht auf meinen eigenen Befund aus der
Pruefung zu 0117 zurueck. Nach der Regel aus meinem Logbuch („kommt der eigene Befund
als Pruefgegenstand zurueck, die eigene Zahl von vorn rechnen") habe ich die 12 nicht
aus meinem alten Befund uebernommen, sondern in diesem Lauf erneut hergeleitet — alle
vier Wege unten sind in diesem Lauf gemessen.

## Bedingung 1 — erfuellt

**Wortlaut der Bedingung:** Der Sperrabsatz von T60 nennt fuer den Fall „China oder
Deutschland faellt auf Stufe 4" die Zahl `3·3 + (3−1) + 1 = 12`, im Einklang mit
`n = 1`; die Sollreihenzahl `3·7 − 1 = 20` daneben bleibt unveraendert.

**Messung:** `technik.md:3729` (HEAD, Fundstelle am Text „Deshalb eine Sperre") lautet:
„Pruefgegenstaende von 16 auf `3·3 + (3−1) + 1 = 12`, die Sollreihen von 27 auf
`3·7 − 1 = 20`". Grep auf `3·7 − 1 = 20` liefert dokumentweit genau eine Zeile (3729);
der Datei-Diff `git --no-pager diff 45fc32f c3f6a8d -- technik.md` zeigt, dass die 20
in der entfernten und der hinzugefuegten Fassung identisch steht — die Zeile ist nur
umgebrochen.

**Einklang mit `n = 1`, auf vier Wegen von vorn gerechnet, keiner zitiert einen
anderen:**

1. **T59-Formel** (Z. 3580): `3·L_R + (L_R − n) + 1` mit `L_R = 3`, `n = 1` (die USA
   bleiben in beiden Faellen des Absatzes Rueckvergleichsland und Numéraire) ergibt
   `9 + 2 + 1 = 12`. Gegenprobe am heutigen Stand, Z. 3588: `3·4 + (4−1) + 1 = 16` —
   dieselbe Belegung `n = 1`.
2. **T37-Bestandstabelle** (Z. 2555–2560), formelfrei: heute BIP 4 + Sektorstruktur 4 +
   Verbraucherpreise 4 + Wechselkurs (je Land ausser USA) 3 + Handelsblock 1 = 16.
   Ohne China oder Deutschland — beide nicht der Numéraire — je eine Zeile weniger bei
   BIP, Sektorstruktur, Preisen und Wechselkurs: 3 + 3 + 3 + 2 + 1 = 12.
3. **T58** (Z. 3562): je Rueckvergleichsland „waechst `L_R` um eins, die
   Pruefgegenstaende um vier"; die Umkehrung: 16 − 4 = 12.
4. **T62** (Z. 3921): „Die Pruefgegenstaende wachsen um vier (`3 + 1` fuer ein Land,
   das nicht [der Numéraire ist])" — dieselbe 4 aus der dritten Quelle.

Auch die **Nebenzahl traegt jetzt dieselbe Belegung**: `3·7 − 1 = 20` ist
`L_R(S+4) − n` (Z. 3584) mit `L_R = 3`, `S = 3`, `n = 1`. Der Selbstwiderspruch des
Satzes — 13 rechnete mit `n = 0`, 20 mit `n = 1` — ist damit beseitigt, nicht nur
uebertuencht.

## Bedingung 2 — erfuellt

**Wortlaut der Bedingung:** `3·3 + 3 + 1 = 13` steht danach genau einmal in
`technik.md`, im Kurzform-Absatz von T59 als `n = 0`-Fall; `git diff` zeigt
Aenderungen ausschliesslich in `technik.md`, und ausser dem einen Rechenausdruck
bewegt sich keine Zahl.

**Messung Zaehlung:** Grep auf `3·3 \+ 3 \+ 1 = 13` liefert dokumentweit genau eine
Zeile: 3607, im Kurzform-Absatz von T59, dort ausdruecklich als „`L_R = 3` **ohne die
USA** ergaebe …, nicht 12" — der `n = 0`-Fall, wie die Bedingung verlangt. Gegengrep
auf weitere Traeger derselben Groesse (`= 13`, `auf 13`, `dreizehn`): Die uebrigen
Treffer sind die dreizehn Skalenklassen (Z. 15, 27, 3444) und der Datenanker-Summand
`83 + 13 + 40` (Z. 1621) — keiner beziffert Pruefgegenstaende.

**Messung Diff:** `git --no-pager diff 45fc32f c3f6a8d --numstat` nennt drei Dateien:
`technik.md` (6 zu / 3 ab), das Arbeitspaket 0154 selbst (Ergebnisteil) und
`notizen/architekt.md`. Die beiden letzten sind die Prozessdateien des Bauagenten und
nach der stehenden Regel dieser Fabrik kein Verstoss gegen „nur Datei X"; ich habe das
Logbuch nicht gelesen, nur seinen Pfad im numstat. Innerhalb von `technik.md` ist der
Diff ein einziger Hunk am Sperrabsatz: Entfernt und hinzugefuegt tragen dieselben 16,
27, 20 und denselben Abfall von `L_R` 4 auf 3; bewegt hat sich allein der eine
Rechenausdruck `3·3 + 3 + 1 = 13` → `3·3 + (3−1) + 1 = 12`.

**Der eine Satz ueber die Abnahme hinaus** („Beide Zahlen rechnen mit `n = 1` …
gilt hier nicht", Z. 3730–3732): Ich habe ihn als moeglichen Uebergriff geprueft und
werte ihn nicht als Befund. Er fuehrt keine neue Groesse ein (`n` und beide Werte
stehen in T59), enthaelt keinen der beiden gezaehlten Ausdruecke, verletzt keine der
zwei Bedingungen und benennt genau die Verwechslung, aus der der Fehler entstand.
Seine Sachaussage stimmt: Die USA bleiben in beiden Faellen des Absatzes
Rueckvergleichsland und Numéraire (T37 fuehrt den Wechselkurs „je Land ausser USA").
Wo die Bedingungen schweigen, gilt die Entscheidung des Bauagenten.

## Wonach ich sonst gesucht habe, ohne etwas zu finden

- Eine zweite Fundstelle, die die Pruefgegenstaende des Streichfalls beziffert und
  haette mitwandern muessen: keine (Grep oben).
- Eine Zahl im umgebenden Absatz, die der Umbruch veraendert haette (16, 27, 20,
  4 auf 3, T61-Verweis): alle in beiden Diff-Seiten identisch.
- Ein Widerspruch der neuen 12 zu den Ankern aus meinen Pruefungen zu 0116/0117
  (T55-Warnpaare, `zaehlregel_t37`): keiner — die Formelzeile Z. 3580 und die
  Fliesstext-Nachrechnung Z. 3588 rechnen unveraendert mit `n = 1`.
