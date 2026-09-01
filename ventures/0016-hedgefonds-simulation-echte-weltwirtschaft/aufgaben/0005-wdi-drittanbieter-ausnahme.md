---
id: 0005-wdi-drittanbieter-ausnahme
rolle: datenbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/lizenzbefund-wdi.md]
abnahme: Für jede der vier Verdachtsreihen steht im Befund Indikatorcode, das wörtliche Feld "Source" aus dem Indikatorendatensatz, die Abruf-URL, das Abrufdatum und ein Urteil frei|gesperrt|unklar mit Begründung; bei jedem Urteil ausser "frei" steht die Folge nach T26 daneben.
---

# Die vier WDI-Verdachtsreihen und die Drittanbieter-Ausnahme

`spiel.md` nennt das unter *Offene Entwurfsfragen* die **schwerste** Frage des Entwurfs
und sagt dazu: „Zu prüfen, bevor gebaut wird." `technik.md` Abschnitt 13 zählt dieses
Paket zu den zweien, die vorzuziehen sind, „weil sie Entwurfsrisiko tragen und nicht
Bauaufwand". Vier Abrufe, und die Frage ist geschlossen.

Vorher lesen: `specs/0016-hedgefonds-simulation-echte-weltwirtschaft/daten.md`
(Lizenzlage), `technik.md` T26 und die Reihenliste in Abschnitt 7.

## Was du prüfst

Je Reihe **das Feld „Source" im Indikatorendatensatz der Weltbank** — nicht die
Zusammenfassung einer Übersichtsseite. Nennt es einen Drittanbieter, greift die
Drittanbieter-Ausnahme der WDI-Lizenz, und die Reihe ist für die Einbettung ins Produkt
gesperrt.

| Nr | Größe | Indikator laut Reihenliste | warum verdächtig |
|---:|---|---|---|
| 13 | Zollniveau, aggregiert | WDI, aus WITS abgeleitet | **entscheidend** — ohne sie verliert der Rückvergleich das wichtigste seiner drei verankerten Instrumente |
| 7 | Beschäftigung je Sektor | WDI, ILO-Schätzung | Start dreier Adressen je Gebiet |
| 8 | Verbraucherpreise | WDI, IWF-gestützt | Start **und** vier Sollreihen |
| 10 | Wechselkurs gegen USD | IWF IFS / WDI | Start und drei Sollreihen |

Der Indikatorcode der Reihen 7, 8, 10 und 13 steht in `daten.md`; steht er dort nicht
vollständig, such ihn über die Indikatorabfrage der Weltbank und schreib ihn mit
Abruf-URL in den Befund. Reihe 2 nennt die Codes bereits ausgeschrieben — dieselbe
Abfrageform trägt auch für die vier hier.

## Was im Befund steht

Je Reihe eine Zeile mit: Nummer, Indikatorcode, Abruf-URL, Abrufdatum, **Wortlaut** des
Feldes „Source", Urteil `frei` | `gesperrt` | `unklar`, Begründung in einem Satz.

Dazu, für jedes Urteil ausser `frei`, die Folge aus T26 — sie steht dort schon
geschrieben und ist von dir nicht zu erfinden:

- Reihe 13 gesperrt → kein Zollpfad, der Weltlauf läuft mit konstantem Zoll, zwei statt
  drei verankerte Instrumente.
- Reihe 7 gesperrt → Aufteilung nach Wertschöpfungsanteil, Startwert wird
  Modellkonstrukt, keine Sollreihe betroffen.
- Reihe 8 oder 10 gesperrt → T26 nennt den Fall nicht. Dann ist es ein **Befund an den
  Spielentwerfer** und keine Bauentscheidung: Beide Reihen tragen Sollreihen des
  Rückvergleichs, und wie viele der 31 wegfallen dürfen, entscheidet T37 und nicht du.
  Schreib die Zahl hin und melde sie.

## Warum das ein eigenes Paket ist und nicht Teil des Jahrgangsbaus

Weil die Antwort den Jahrgangsbau ändert, nicht umgekehrt. Fiele sie erst dort an,
müsste das Paket zweimal gebaut werden — genau der Fall, den `technik.md` T24 für den
Jahrgang schon vermieden hat.

## Grenzen

- Du gibst **keinen Rechtsrat**. Du liest, was die Quelle über sich selbst sagt, und
  zitierst es. Die Bewertung „nutzbar" trifft der Betreiber.
- Du lädst **nichts herunter** und bettest nichts ein. Dieses Paket erzeugt genau eine
  Textdatei.

## Rückläufe

0.
