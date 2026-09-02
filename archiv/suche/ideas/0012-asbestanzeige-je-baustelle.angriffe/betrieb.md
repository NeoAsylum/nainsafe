---
linse: betrieb
idee: 0012-asbestanzeige-je-baustelle
datum: 2026-08-28
urteil: widerlegt
schwerster_einwand: Die Pflege von rund 41 Zuständigkeiten und 38 Landesformularen fällt vollständig an, bevor der erste Kunde zahlt — rund 1,8 Stunden je Woche und damit fast das ganze Budget bei null Umsatz —, und sie lässt sich nicht wegautomatisieren, weil die Fabrik bei genau diesen Behördenquellen schon zweimal am Abruf gescheitert ist.
stunden_pro_woche: rund 2,6 bei 40 Kunden, rund 3,8 bei 100; davon 1,8 als kundenunabhängiger Sockel, der auch bei null Kunden anfällt. Dazu Tage mit sechs bis acht Stunden, wenn ein Bundesland sein Formular umstellt.
---

## Der Einwand

Die Idee zerlegt die Aufgabe sauber in „konstant je Betrieb" und „wechselnd je Baustelle"
und schließt daraus, dass sie zum Werkzeug passt. Die Zerlegung stimmt. Sie beschreibt
aber die Arbeit des *Kunden*, nicht die des Betreibers. Betrieblich gibt es eine dritte
Kategorie, die in keinem Abschnitt der Idee vorkommt: **was der Betreiber pflegen muss,
damit das Werkzeug überhaupt etwas Wahres behaupten kann.**

### 1. Der Sockel ist schon bei null Kunden fast das ganze Budget

Der Fit-Filter hat 0013 abgelehnt — das reine Nachschlagewerk aus Zuständigkeit,
Formularfassung und Anlagenliste — und dabei geschrieben: „Dagegen steht laufende Pflege
von rund 41 Stellen und ihren Formularfassungen — der Aufwand ist konstant, der Ertrag
nicht." Und dann: „0012 enthält die Zuständigkeits- und Formularermittlung als
Bestandteil, dort aber gebündelt mit dem Ausfüllen, das den Preis erst trägt."

Das ist eine Antwort auf eine Margenfrage. Meine Frage ist eine andere: **Ein höherer
Preis kauft keine Stunden.** 0012 erbt den kompletten Pflegeaufwand von 0013 als
unbezahlte Vorleistung und legt eigene Arbeit obendrauf. Im Score der Idee taucht diese
Erbschaft nirgends auf; `ruhe` steht auf 3.

Der Sockel, mit Annahmen offengelegt:

| Posten | Annahme | h/Woche |
|---|---|---|
| Formularstände sichten | 41 Stellen, zweimal im Monat geprüft — schneller findet man eine Umstellung nicht, langsamer wird sie zum Schaden. 4 h/Monat für Sichtung und Triage, teilautomatisiert. Voll von Hand wären es eher 5,5 h/Monat (41 PDFs × 4 min × 2). | 0,92 |
| Änderung einarbeiten | Feldzuordnung neu, Testfall neu, alte Fassung archivieren, betroffene Kunden benachrichtigen: 3 h je Fall. 0013 vermutet „wenige Änderungen im Jahr", ausdrücklich ungeprüft. Ich rechne mit 10 — **Schätzung, nicht erhoben**; bei 41 Stellen ist das eher die Untergrenze. | 0,58 |
| Zuständigkeitsverzeichnis | Behördenreformen, Umbenennungen, Wechsel des Einreichwegs von Post auf E-Mail auf Portal | 0,20 |
| Feiertagskalender 16 Länder, Fristlogik | jährlich, klein, aber nicht null | 0,10 |
| **Sockel gesamt** | | **1,80** |

Das Budget der Fabrik ist zwei Stunden. Neunzig Prozent davon sind verbraucht, bevor ein
einziger Dachdecker etwas bezahlt hat.

### 2. Die Automatisierung, auf die man hier hoffen müsste, ist bereits gescheitert

Der übliche Ausweg wäre: ein Skript ruft die 41 Seiten ab, vergleicht Prüfsummen, meldet
Abweichungen. Genau dieser Weg ist in den eigenen Akten schon zweimal fehlgeschlagen,
beide Male dokumentiert und beide Male an derselben Sorte Quelle:

- Die BAuA-Musterformulare zur TRGS 519 ließen sich nicht abrufen, **HTTP 403** — die
  Existenz ist nur über eine Trefferliste belegt (0013, Belege; Marktprofil, Abschnitt 5).
- Das ZVDH-Steckbrief-PDF war „im Binärformat nicht auslesbar" (Marktprofil, Abschnitt 1).

Das sind keine Pannen, das ist die Normallage bei Behörden- und Verbandsservern. Und
selbst wo der Abruf gelingt, bleibt der teure Teil unautomatisiert: die Entscheidung, ob
eine neu datierte PDF-Fassung inhaltlich etwas ändert. Behörden veröffentlichen Formulare
mit neuem Datum und identischem Inhalt, und sie ändern Inhalte ohne neues Datum. Die
Triage ist Lesearbeit.

Die Idee selbst nennt das Beispiel — „Formular NRW von Fassung 05/2026 auf 08/2026
gewechselt (Feld 7 neu)" — als Beleg für gute Zustandsausgabe. Als Zustandsausgabe ist es
gut. Als Betriebsvorgang ist es der Posten, an dem die Idee stirbt: Woher weiß das System,
dass Feld 7 neu ist? Aus einem Menschen, der zweimal im Monat 41 PDFs anschaut.

### 3. Der Fehler ist korreliert, nicht verteilt

Das ist der Punkt, an dem sich diese Idee von allem unterscheidet, was ich bisher geprüft
habe. Bei 0009 war jeder Fehler ein Einzelfall: eine falsche Rechnung, ein Kunde, ein
Anruf. Hier hängen alle Kunden eines Bundeslandes an *einem* Datensatz. Stellt NRW sein
Formular um, sind nicht ein oder zwei Kunden betroffen, sondern **alle NRW-Kunden am
selben Tag** — bei 100 Kunden und einem NRW-Anteil in der Größenordnung eines Viertels
sind das zwanzig bis fünfundzwanzig gleichzeitige Fälle, jeder mit einer laufenden
Sieben-Tage-Frist.

Meine offene Fährte lautete: Ballt sich die *Nachfrage* in einem Zeitfenster? Hier ballt
sich etwas anderes und Schlimmeres: **die Fehler ballen sich.** Ein Durchschnittswert von
3,8 Stunden je Woche ist deshalb irreführend — die Arbeit kommt nicht als Rinnsal, sondern
als Tag.

### 4. Ein stiller Fehler hebelt den Fallback aus, auf dem die Idee ruht

Die Idee grenzt sich gegen 0003 mit einem Satz ab, den sie selbst als Kipppunkt markiert:
„Fällt es aus, schreibt der Betrieb die Anzeige von Hand wie bisher — das ist der
Fallback."

Der Fallback greift bei einem **Ausfall**. Er greift nicht beim **falschen Ergebnis** —
und das ist die Fehlerart, die dieses Produkt fast ausschließlich erzeugt. Ein
Formularbefüller fällt selten aus; er liefert praktisch immer ein Dokument. Nur eben
gelegentlich eines auf der Fassung vom Mai, adressiert an eine Behörde, die seit Juli
anders heißt, mit einer Person darin, deren Vorsorge letzte Woche abgelaufen ist. Der
Kunde sieht ein fertiges PDF und verlässt sich darauf. Er merkt nichts — bis die Behörde
zurückweist oder bis niemand etwas merkt.

Die zweite Variante ist betrieblich die gefährlichere. Eine Anzeige ist eine Anzeige, keine
Genehmigung; sie wird nicht inhaltlich beschieden. Ein fehlender Nachweis oder eine
unvollständige Anlagenliste fällt dann **nie** auf — bis eine Baustellenkontrolle kommt
oder bis Jahre später jemand rückwärts die Nachweislage prüft, weil ein Beschäftigter eine
Berufskrankheit anzeigt. Bei 0009 fiel der Fehler 14 bis 20 Monate später auf. Hier fällt
er womöglich in fünf Jahren auf, und dann geht es nicht um einen Steuerbescheid.

### 5. Die Bemessungsgrundlage des Supports sind nicht 100 Kunden, sondern 600 Beschäftigte

Der nicht offensichtliche Skalierungspunkt, den ich gesucht habe, liegt hier. Das Produkt
hält Qualifikations- und Vorsorgenachweise namentlich benannter Beschäftigter. Bei 100
Betrieben mit je sechs Gewerblichen sind das **600 Personen, die selbst keine Kunden sind**
— und die Betroffenenrechte haben. Der wahrscheinlichste Absender einer Auskunfts- oder
Löschanfrage ist ein ausgeschiedener Dachdecker im Streit mit seinem Ex-Chef, nicht der
Chef. Solche Anfragen sind fristgebunden, verlangen eine Identitätsprüfung und sind damit
nicht automatisierbar. Im Jahresschnitt sind das wenige Stunden; sie kommen nur eben
unangekündigt und mit Frist.

Dieselbe Mechanik im Kleinen: Ein Handwerksbetrieb hat Fluktuation, Aushilfen, im
Sommer Leute von der Leihfirma. Der Stamm, den das Produkt für Wahrheit hält, ist der
Stamm, den der Meister zuletzt gepflegt hat. Jede Lücke zwischen beidem erzeugt entweder
einen Supportfall („warum sagt das Ding, Meier sei nicht einsetzbar?") oder eine falsche
Anzeige.

Und einen dritten Absender gibt es, den die Idee nicht kennt: Wenn hundert Betriebe
Anzeigen in erkennbar identischem, maschinenerzeugtem Layout einreichen, fragt irgendwann
eine Aufsichtsbehörde beim Erzeuger nach. Der Betreiber wird damit Ansprechpartner von
Arbeitsschutzbehörden, ohne deren Kunde oder Adressat zu sein.

### 6. Die Fristangabe ist keine Kalenderaddition

Die Idee behauptet, es bleibe „Zusammensetzen aus gepflegten Stammdaten und eine
Kalenderaddition", und gibt in der Detailansicht die „früheste zulässige Aufnahme der
Arbeiten" aus. Betrieblich zerfällt diese eine Zeile in mindestens vier Rückfragen:

- Sieben Kalendertage oder sieben Werktage?
- Läuft die Frist ab Absendung oder ab Zugang bei der Behörde? Bei Postversand liegt
  dazwischen ein Intervall, das das Produkt nicht kennt.
- Welche Feiertage gelten — die am Firmensitz oder die am Ort des Objekts? Fronleichnam,
  Mariä Himmelfahrt und Reformationstag sind länder-, teils gemeindescharf verschieden.
- Zählt der Tag der Einreichung mit?

Ob das juristisch trägt, ist nicht meine Linse. Betrieblich zählt: Jede dieser Fragen
stellt irgendwann ein Kunde, und der Betreiber muss sie schriftlich beantworten — für
hundert Kunden, ohne Anwalt, und jedes Mal in dem Bewusstsein, dass seine Antwort in der
Akte des Kunden landet.

### 7. Der laufende Aufwand, ehrlich addiert

Kundenlinear, mit Annahmen:

| Posten | Annahme je Jahr | 40 Kunden | 100 Kunden |
|---|---|---|---|
| Rückfragen zu Stamm- und Nachweisdaten | 1,5 Fälle je Kunde × 15 min | 0,29 | 0,72 |
| Zurückgewiesene oder falsche Anzeige | 0,3 Fälle je Kunde × 45 min, zeitkritisch | 0,17 | 0,43 |
| Einrichtung neuer Kunden | 30 % Zuwachs/Wechsel, 25 min je Fall | 0,10 | 0,24 |
| Rechnung, Mahnung, Kündigung, Umsatzsteuer | 20 min je Kunde | 0,26 | 0,64 |
| **linear gesamt (h/Woche)** | | **0,82** | **2,03** |

Dazu der Sockel von 1,80:

- **40 Kunden: 2,6 h/Woche**
- **100 Kunden: 3,8 h/Woche**

Beides über der Grenze, und der Weg dahin führt durch keinen Punkt, an dem es passt. Bei
zehn Kunden sind es schon 2,0 Stunden — dann fast ausschließlich Sockel, also Arbeit ohne
Gegenwert.

Die Einrichtungszeit trägt hier ausnahmsweise der Kunde, nicht der Betreiber: sechs
Mitarbeiter mit je Sachkundeschein und Vorsorgebescheinigung abzutippen ist ein Abend für
den Meister. Das ist betrieblich gut und wirtschaftlich schlecht — es ist die Hürde,
an der ein Teil der Kunden vor der ersten Anzeige abspringt oder anruft.

### 8. Modellkosten je Vorgang: kein Befund

Der Vorgang ist Formularbefüllung aus gepflegten Stammdaten, deterministisch, ohne
Modellaufruf je Anzeige. Gegen einen Pauschalpreis je Betrieb ist das kein Kostenposten.
Abgehakt, wie in meinem Logbuch vorgesehen — hier liegt der Killer nicht.

### 9. Die Fremdabhängigkeit ist der Staat, und er verbessert sich

Berlin führt laut Marktprofil bereits ein eigenes Verfahren. Jedes weitere Land, das ein
Online-Verfahren einführt, entfernt ein Sechzehntel des Produktnutzens — **ohne den
Pflegeaufwand für die übrigen fünfzehn zu senken.** Das ist eine Abhängigkeit, die nach
oben ausfällt: Je besser die Behörden werden, desto wertloser das Produkt, und desto
schlechter das Verhältnis von Sockel zu Ertrag. Angekündigt wird das nirgends an einer
Stelle, die der Betreiber abonnieren könnte. Er erfährt es beim nächsten Sichtungslauf —
oder von einem Kunden.

## Was ihn entkräften würde

Ich sehe genau einen Zuschnitt, der trägt, und er ist kleiner, als die Idee möchte:

1. **Ein Bundesland statt sechzehn — vorzugsweise NRW.** Ein Formularsatz, fünf
   Bezirksregierungen, ein Feiertagskalender. Der Sockel fällt von 1,80 auf grob 0,3
   Stunden je Woche, und die Fehlerkorrelation wird beherrschbar, weil eine Umstellung
   zwar alle Kunden trifft, aber nur einmal eingearbeitet werden muss. Der Preis: Betriebe,
   die über Landesgrenzen arbeiten, fallen weg. Nach der Ablehnungsbegründung zu 0013 ist
   dieser Verlust kleiner, als er klingt — dort steht ausdrücklich, ein Betrieb unter zehn
   Gewerblichen arbeite regional. Was 0013 die Marge gekostet hat, spart 0012 hier an
   Stunden. **Das ist der einzige Rettungsweg, den ich sehe, und er verdient eine Prüfung.**
2. **Keine Fristzusage, kein Zuständigkeitsversprechen.** Das Dokument trägt sichtbar
   „Formularfassung NRW 05/2026, geprüft am 2026-08-15" und der Kunde bestätigt den Stand
   vor jedem Versand. Das verlagert die Wahrheitspflicht dorthin, wo sie hingehört —
   entwertet aber genau den Kaufgrund, was die Idee als offene Frage 4 selbst benennt.
   Beide Enden dieses Seils gleichzeitig zu halten, ist noch niemandem gelungen.
3. **Ein Formularwächter, der wirklich läuft.** Wenn sich zeigen ließe, dass die 41 Quellen
   maschinell abrufbar sind und Änderungen zuverlässig auffallen, schrumpft der größte
   Posten des Sockels. Die zwei dokumentierten Fehlversuche sprechen dagegen; ein
   Gegenbeweis wäre aber billig zu beschaffen — 41 Abrufe, eine Stunde Arbeit. **Das sollte
   vor jeder weiteren Konzeption geschehen, weil es die Idee schneller entscheidet als
   jede Marktfrage.**

Was ihn *nicht* entkräftet: mehr Kunden. Das ist der Unterschied zu den üblichen
G4-Fällen. Hier hilft Wachstum nur gegen den Ertrag, nicht gegen die Stunden — und die
Stunden sind die Randbedingung.

## Der schlimmste Tag

Dienstag, 8. September 2026. Der Betreiber sitzt seit halb neun im Problem-Management
seines Arbeitgebers, Vormittag durchgetaktet, Handy lautlos.

Am Montag hat eine NRW-Bezirksregierung ihr Anzeigeformular auf eine neue Fassung
umgestellt, mit einem zusätzlichen Feld. Der letzte Sichtungslauf war am 15. August; der
nächste ist für den 1. September vorgesehen und wurde verschoben, weil an dem Wochenende
Familienbesuch war. Das Produkt füllt seit acht Tagen die alte Fassung aus.

Dienstagvormittag weisen zwei Bezirksregierungen die eingegangenen Anzeigen zurück — per
E-Mail an die Betriebe, nicht an den Betreiber. Er erfährt es nicht von der Behörde. Er
erfährt es von Dachdeckermeistern, die feststellen, dass ihre Baustelle am kommenden
Montag beginnen soll und die Sieben-Tage-Frist mit der Zurückweisung gerissen ist. Ab elf
Uhr rufen sie an. Um 17 Uhr hat er sechs Anrufe in Abwesenheit und vierzehn Mails, die
alle dieselbe Frage stellen und alle dieselbe Antwort brauchen: bis wann?

Er kann die neue Fassung am Mittwochabend einarbeiten. Zwischen Mittwoch und Montag liegen
fünf Tage. Für die Baustellen am Montag reicht das nicht. Sechs Betriebe verschieben um
eine Woche: Kolonne umdisponiert, Gerüst und Container stehen bezahlt herum, ein Bauherr
wird vertröstet. Der Schaden liegt bei ihnen und ist vertraglich abwälzbar — juristisch
ist der Betreiber wahrscheinlich sauber.

Betrieblich ist er es nicht. Diese sechs Betriebe sind Innungsmitglieder, und die Innung
ist derselbe Kanal, über den die Idee verkaufen will: ZVDH, rund 200 Innungen, regionaler
Organisationsgrad über 70 Prozent. **Vertriebskanal und Beschwerdekanal sind identisch.**
Ein verpatzter Montag ist in einer solchen Struktur nicht lokal, sondern regional
vollständig — und er wird bei der nächsten Innungsversammlung erzählt, nicht in einem
Bewertungsportal, wo man ihn beantworten könnte.

Und der Anruf um elf Uhr ist der eigentliche Befund. Zugesagt hat der Betreiber keine
Reaktionszeit. Ein Meister, dessen Montagsbaustelle wackelt, wartet trotzdem keine 24
Stunden. Meine offene Fährte aus 0005 und 0009 lautete, dass sich die tolerierbare
Reaktionszeit unter 24 Stunden verkürzt, wenn Endverbraucher hinter dem zahlenden Kunden
stehen. Hier ist es kein Endverbraucher — es ist eine gesetzliche Frist *vor* dem Kunden,
und sie wirkt genauso. **Nicht der Vertrag setzt die Reaktionszeit, sondern die Frist des
Kunden.** Das ist keine formale Verletzung von G3, aber es ist dieselbe Falle.

Zwei Wochen Urlaub sind derselbe Tag in gedehnter Form, nur schlimmer: Das Produkt fällt
nicht aus, es läuft vierzehn Tage lang gegen einen Formularstand, den niemand prüft, und
erzeugt eine ganze Kohorte Anzeigen, deren Fehler erst nach der Rückkehr sichtbar wird.
Bis dahin sind die Baustellen entweder gelaufen — mit einer unwirksamen Anzeige in der
Akte — oder geplatzt.
