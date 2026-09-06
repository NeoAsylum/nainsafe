#pragma once
//! `kern::werte` -- die zweiundzwanzig abgeleiteten Groessen aus T48 und die drei
//! Skalenuebergaenge aus T50.
//!
//! Vorgaben: T47 (das Fondsvermoegen ist genau eine Funktion), T48 (die abgeleiteten
//! Groessen abschliessend aufgezaehlt), T50 (genau drei Skalenuebergaenge, jeder mit
//! benannter Funktion und genau einem Aufrufort), T5 (Skalenklassen), T9 (feste
//! Indexordnung), T13 (Modulschnitt), T33 (Marktkorb), T39 (der Landespreis liest die
//! Vorrunde), T6/T6b/T7 (Rechenwerk und Ueberlauf), T4 (kein Gleitkomma), T2 (keine
//! Fremdabhaengigkeit).
//!
//! ## Wozu es dieses Modul gibt
//!
//! T48 sagt den Zweck in einem Satz: Ein Name in einer Formel der Vorgaben, der weder
//! eine Zustandsadresse noch ein Parameterschluessel noch eine Jahrgangskonstante noch
//! eine der zweiundzwanzig Groessen hier ist, **ist ein Befund und keine
//! Bauentscheidung**.
//! Waehlt der Bauagent, misst Mass 2 seine Wahl. Genau das war Befund 1 der sechsten
//! Entwurfspruefung: `korbwert` und `positionswert` standen in einer Formel und wurden
//! nirgends gebildet -- und der Abzaehlschritt aus T45 konnte die Luecke nicht finden,
//! weil er **Adressen** zaehlt und `korbwert` nie eine der 310 war.
//!
//! ## Der mechanische Nachweis, und was er zaehlt
//!
//! T48 sieht ihn ausdruecklich fuer dieses Modul vor: die oeffentlichen Deklarationen
//! dieses Kopfes gegen die Tabelle aus T48 gelegt. Gezaehlt werden **Funktionen** --
//! in Rust waere es ein Mustervergleich auf die oeffentlichen Funktionen, in C++ ist
//! es der Kopf, weil dort und nur dort steht, was das Modul nach aussen anbietet.
//! Unten stehen zweiundzwanzig, in der Reihenfolge der Tabelle aus T48 und mit deren
//! laufender Nummer davor.
//!
//! **Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen, und der Unterschied ist
//! genau einer.** Nr. 11 traegt zwei Stelligkeiten -- `handelsvolumen(l, s)` und ihre
//! Summe `handelsvolumen(l)` --; T48 nennt sie "nicht zwei Definitionen desselben
//! Namens, sondern eine Definition und ihre Aggregation" und zaehlt sie als **eine**
//! Groesse. Wer den Kopf gegen die Tabelle legt, zaehlt deshalb Nummern und nicht
//! Zeilen; die beiden Fassungen stehen unter derselben Nummer nebeneinander.
//!
//! `Konstanten` ist keine dreiundzwanzigste Groesse, sondern der Traeger der Zahlen,
//! die die Formeln aus T47 und T48 **neben** dem Zustand nennen. Ohne ihn muesste jede
//! der zweiundzwanzig Funktionen sie einzeln durchreichen, und `fondsvermoegen`
//! haette sechs gleichartige Zahlenargumente in einer Reihe, in der eine
//! Verwechslung nicht auffiele.
//!
//! ## Was hier ausdruecklich NICHT steht
//!
//! Die drei Skalenuebergaenge aus T50. Sie sind **privat**: Sie stehen allein in
//! `src/werte.cpp` und haben in diesem Kopf keine Deklaration. Der Nachweis dafuer ist
//! ein Mustervergleich derselben Bauart wie der Gleitkommanachweis aus T4 -- eine
//! Suche nach ihren Namen ueber `kern/` trifft nur jene eine Datei.
//!
//! Die Umkehrung des ersten Uebergangs gibt es nicht (T50). Der Fonds wirkt auf die
//! Welt ausschliesslich ueber Anteile in Zehntausendsteln, nie ueber einen Geldbetrag;
//! eine Umrechnung ohne Aufrufer waere eine stehende Einladung, sie irgendwo zu
//! benutzen, wo sie nicht hingehoert.
//!
//! `B(z)`, `v(z)` und `e(z)` aus T44 stehen ebenfalls nicht hier: Sie sind
//! Pruefstandsgroessen, gehoeren dem Baustein `pruefstand` und verlassen die Partie
//! nie.

#include <array>

#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/zustand.hpp"

namespace kern::werte {

// ---------------------------------------------------------------------------
// Die Zahlen neben dem Zustand
// ---------------------------------------------------------------------------

/// Die Kalibrierwerte und die eine Jahrgangskonstante, die in den Formeln aus T47 und
/// T48 neben den Zustandsadressen vorkommen.
///
/// **Warum sie als Argument hereinkommen und nicht aus einer Datei.** Der Kern liest
/// keine Datei (T2) und haengt an keinem Kasten -- `daten` haengt an `kern` und nicht
/// umgekehrt (T13). T27 schreibt vor, dass der Parametersatz beim Laden in eine
/// Struktur mit benannten Feldern faellt, nie ueber eine Schleife ueber Schluessel;
/// diese Struktur ist der Ausschnitt daraus, den die Bewertung braucht. Damit bleibt
/// Kalibrieren eine Datenaenderung, die kein Uebersetzen braucht.
///
/// Jedes Feld traegt seinen Schluesselnamen und seine Skalenklasse nach T5. Ein
/// Parameterschluessel ohne Klasse ist nach T27 derselbe Fehler wie eine Adresse ohne
/// Klasse.
///
/// **Alle Felder sind mit null vorbelegt, und das ist kein brauchbarer Parametersatz.**
/// Ein voreingestelltes `Konstanten` laesst `anleihekurs` an seinem Nenner abbrechen
/// und macht jeden Stufen- und Beteiligungswert null. Das ist gewollt: Ein plausibel
/// aussehender Vorgabewert waere eine Kalibrierung, die niemand beschlossen hat.
struct Konstanten {
    /// Schluessel `stufenweite` -- T5 Klasse 4 (Anteile, Zehntausendstel). Anteil des
    /// Marktes je Positionsstufe, **kein Geldbetrag**.
    zustand::i64 stufenweite = 0;

    /// Schluessel `ausstiegsabschlag` -- T5 Klasse 4. Abschlag auf den
    /// Beteiligungswert, im Wertansatz und damit beim Aufbau bezahlt (T47 Punkt 1).
    zustand::i64 ausstiegsabschlag = 0;

    /// Schluessel `aufschlag` -- T5 Klasse 3 (Raten, Basispunkte). Abstand zwischen
    /// Leitzins und Anleiherendite.
    zustand::i64 aufschlag = 0;

    /// Schluessel `lobbykosten` -- T5 Klasse 1 (Fondsgeld, US-Cent je Lobbypunkt,
    /// mindestens 1). Gelesen allein vom zweiten Skalenuebergang aus T50.
    zustand::i64 lobbykosten = 0;

    /// Schluessel `gegenlobby_satz` -- T5 Klasse 9 (Lobbypunkte je 10.000 Tausend USD
    /// Schaden). Gelesen allein vom dritten Skalenuebergang aus T50.
    zustand::i64 gegenlobby_satz = 0;

    /// Schluessel `regulierung_last` -- T5 Klasse 3 (Raten, Basispunkte des
    /// Bruttoinlandsprodukts je Regulierungsstufe). Gelesen allein von der
    /// Regulierungszeile der Schadensvorschrift (T48 Nr. 22).
    ///
    /// Er ist der Grund, warum jene Zeile trotz ihrer Klasse 10 denselben Nenner 10.000
    /// hat wie die drei anderen: Stufen mal Basispunkten je Stufe sind wieder
    /// Basispunkte, also Klasse 3 -- dieselbe Klasse wie die Verschiebung der beiden
    /// mittleren Zeilen (T48, T27).
    zustand::i64 regulierung_last = 0;

    /// Der Leitzins des Startjahrs je spielbarem Land -- T5 Klasse 3.
    ///
    /// **Keine Kalibriergroesse, sondern eine Messung**, und deshalb steht sie nach
    /// T27 nicht in `parameter.toml`, sondern im Jahrgang: Es ist die erste
    /// Stuetzstelle des Politikpfads, die der Jahrgang ohnehin traegt (T23 Punkt 5).
    /// Nur die vier spielbaren Laender haben einen Politikpfad; die Restwelt hat
    /// keinen und bekommt deshalb auch keinen Anleihekurs.
    std::array<zustand::i64, zustand::LAENDER> leitzins_start{};

    /// Der Preisdurchgriff je Gebiet und handelbarem Sektor -- T5 Klasse 4
    /// (Zehntausendstel), zehn Werte.
    ///
    /// **Die zweite Jahrgangskonstante dieses Traegers**, aus demselben Grund wie
    /// `leitzins_start` und auf demselben Weg: Sie ist nach T23 Punkt 5 eine Groesse
    /// des Jahrgangs und steht deshalb nicht in `parameter.toml` -- die Datei nimmt
    /// sie dort ausdruecklich aus --, und weil der Kern keine Datei liest (T2), kommt
    /// sie als Argument herein.
    ///
    /// **Sie ist keine Zustandsadresse.** Der Zustand fuehrt sie nicht und soll sie
    /// nicht fuehren; sie ist ueber die Partie fest.
    ///
    /// Alle fuenf Gebiete und nicht nur die vier Laender: Die Restwelt nimmt an der
    /// Preisuebertragung teil, und die Reihe traegt deshalb `5 x 2` Werte. Von den
    /// vier Landeszeilen liest `preishub_zoll`; die Restweltzeile gehoert der
    /// Marktraeumung.
    std::array<std::array<zustand::i64, zustand::SEKTOREN_HANDELBAR>, zustand::GEBIETE>
        durchgriff{};
};

// ---------------------------------------------------------------------------
// Die zweiundzwanzig Groessen aus T48, in der Reihenfolge seiner Tabelle
// ---------------------------------------------------------------------------
//
// Die Argumentnamen folgen den Buchstaben der Vorgaben, und der Unterschied ist
// keiner der Bequemlichkeit: `g` steht dort fuer ein **Gebiet** (alle fuenf, mit der
// Restwelt), `l` fuer ein **spielbares Land** (die vier ohne sie). Wo T47 und T48 `l`
// schreiben, obwohl die gelesene Adresse fuer alle fuenf Gebiete besteht, ist der
// Parameter hier trotzdem ein `Gebiet`, und die Einschraenkung entsteht dort, wo sie
// in den Daten steht: `stelle_beteiligung` und `steckplatz_anleihe` brechen fuer die
// Restwelt von sich aus ab, und `anleihekurs` prueft seinen eigenen Zugriff auf
// `leitzins_start`. Eine zusaetzliche Einschraenkung erfindet dieses Modul nicht.

/// **T48 Nr. 1** -- `wert(menge, kurs, g) = mal_geteilt(menge, kurs, wechselkurs[g])`.
///
/// Die eine Bewertungsformel des Modells: Menge mal Kurs, umgerechnet in den
/// Numeraire. T5 Klasse 2 (volkswirtschaftlich). Kurs und Wechselkurs sind beide
/// Indizes mit Startwert 10.000; ihr Skalenfaktor kuerzt sich gegeneinander weg, und
/// die Bewertung braucht keine Konstante.
///
/// **Erste der beiden Wertebereichsschranken aus T47:** `wechselkurs[g] >= 1`. Ein
/// Nenner null ist nach T6 ohnehin ein Abbruch; ein **negativer** Nenner waere
/// schlimmer -- er drehte das Vorzeichen jeder Bewertung, ohne dass irgendetwas
/// abbraeche. Hier bricht etwas ab.
[[nodiscard]] zustand::i64 wert(const zustand::Zustand& z, zustand::i64 menge,
                                zustand::i64 kurs, zustand::Gebiet gebiet);

/// **T48 Nr. 2** -- `korbwert(l, s) = wert(kapitalstock[l][s], sektorpreis[l][s], l)`.
/// T5 Klasse 2.
[[nodiscard]] zustand::i64 korbwert(const zustand::Zustand& z, zustand::Gebiet land,
                                    zustand::Sektor sektor);

/// **T48 Nr. 3** -- `anleihewert(l) = wert(schuld(l), anleihekurs(l), l)`.
/// T5 Klasse 2. Nur die vier spielbaren Laender, siehe `anleihekurs`.
[[nodiscard]] zustand::i64 anleihewert(const zustand::Zustand& z, const Konstanten& konst,
                                       zustand::Gebiet land);

/// **T48 Nr. 4** -- `waehrungswert(l) = wert(handelsvolumen(l), 10.000, l)`.
/// T5 Klasse 2. Der Kurs ist das Literal 10.000 und kein Parameter.
[[nodiscard]] zustand::i64 waehrungswert(const zustand::Zustand& z, zustand::Gebiet land);

/// **T48 Nr. 5** -- `markt(p)`, die Fallunterscheidung ueber die drei Steckplatzarten
/// aus T16: Korbwert, Waehrungswert oder Anleihewert. T5 Klasse 2.
[[nodiscard]] zustand::i64 markt(const zustand::Zustand& z, const Konstanten& konst,
                                 zustand::Steckplatz platz);

/// **T48 Nr. 6** -- `stufenwert(p) = mal_geteilt(markt(p), stufenweite, 10.000)`.
/// T5 Klasse 2 -- die letzte Groesse **vor** der Skalengrenze.
[[nodiscard]] zustand::i64 stufenwert(const zustand::Zustand& z, const Konstanten& konst,
                                      zustand::Steckplatz platz);

/// **T48 Nr. 7** -- `marktkorb(m, k)`: Summe der 12 Korbwerte plus der 4 Anleihewerte,
/// Mengen aus `m`, Kurse aus `k` (T33 Punkt 1). T5 Klasse 2.
///
/// Zwei Zustaende, weil T33 Punkt 3 den **Mengenkorb der Vorrunde zu den Preisen
/// dieser Runde** bewertet. Mengenwachstum erzeugt damit keine Scheinrendite. Der
/// Wechselkurs ist ein Kurs und kommt deshalb aus `k`, ebenso der Leitzins, an dem der
/// Anleihekurs haengt; Kapitalstock und Staatsschuld sind Mengen und kommen aus `m`.
[[nodiscard]] zustand::i64 marktkorb(const zustand::Zustand& mengen, const zustand::Zustand& kurse,
                                     const Konstanten& konst);

/// **T48 Nr. 8** -- `korbbestand(z)`: der Bestand des Fonds zu Modellmarktwerten,
/// Koerbe nach `fondsanteil`, Anleihen nach `|stufen(p)| * stufenweite`. T5 Klasse 2.
///
/// Waehrungen gehen nicht ein: Sie tragen nach T33 Punkt 1 keine Kapitalisierung. Das
/// Handelsvolumen ist die **Tiefe** des Waehrungsmarktes und traegt Stufenwert und
/// Preisstoss, nicht den Marktkorb.
[[nodiscard]] zustand::i64 korbbestand(const zustand::Zustand& z, const Konstanten& konst);

/// **T48 Nr. 9** -- `bip(l) = Summe ueber die 3 Sektoren wertschoepfung[l][s]`.
/// T5 Klasse 2.
[[nodiscard]] zustand::i64 bip(const zustand::Zustand& z, zustand::Gebiet land);

/// **T48 Nr. 10** -- `schuld(l) = mal_geteilt(bip(l), staatsschuld[l], 10.000)`.
/// T5 Klasse 2. `staatsschuld` ist nach T5 Klasse 3 die **Quote** in Basispunkten und
/// nicht der Betrag -- daher der Umweg ueber `bip`.
[[nodiscard]] zustand::i64 schuld(const zustand::Zustand& z, zustand::Gebiet land);

/// **T48 Nr. 11, zweistellig** -- `handelsvolumen(l, s)`: Summe ueber die 4 Gegenueber
/// `g` von `handel[l][g][s] + handel[g][l][s]`. T5 Klasse 2.
///
/// **Beide Richtungen je Paar** -- Aus- plus Einfuhr. Die Zuordnung des dichten
/// Gegenueber-Index zum Gebietsindex steht in `src/werte.cpp` als benannte Tabelle und
/// nicht als Rechnung auf Indizes (T48).
///
/// Nur die zwei handelbaren Sektoren: Der dritte hat nach T15 keine Handelszeile, und
/// ein Handelsvolumen ohne Handelszeile waere eine Summe ueber nichts. Er bricht hier
/// ab und nicht erst im Zustand.
[[nodiscard]] zustand::i64 handelsvolumen(const zustand::Zustand& z, zustand::Gebiet land,
                                          zustand::Sektor sektor);

/// **T48 Nr. 11, einstellig** -- `handelsvolumen(l)`: die Summe der zweistelligen
/// Fassung ueber s in {1, 2}. T5 Klasse 2.
///
/// **Zwei Stelligkeiten und eine Groesse** (T48): nicht zwei Definitionen desselben
/// Namens, sondern eine Definition und ihre Aggregation. Die Richtung ist vorgegeben --
/// die einstellige ruft die zweistellige und nicht umgekehrt --, und daran haengt, dass
/// die Zollzeile von Gegenkraft 5 je Sektor rechnen kann, ohne dass Nr. 4 sich aendert:
/// Dort steht weiterhin diese Fassung, und sie bedeutet weiterhin dasselbe.
[[nodiscard]] zustand::i64 handelsvolumen(const zustand::Zustand& z, zustand::Gebiet land);

/// **T48 Nr. 12** -- `anleihekurs(l) = teile_gerundet(10.000 * (leitzins_start[l] +
/// aufschlag), leitzins[l] + aufschlag)`. T5 Klasse 5 (Nominalindex, Startjahr
/// 10.000).
///
/// Der Kurs einer ewigen Anleihe: streng fallend im Zins, im Startjahr per
/// Konstruktion genau 10.000, positiv fuer jeden positiven Nenner, ohne Kappung. Der
/// Nenner ist nach T51 nie null und nie negativ -- die Schranke sitzt am Instrument
/// und nicht am Kurs.
///
/// **Nur die vier spielbaren Laender.** `leitzins_start` ist die erste Stuetzstelle
/// des Politikpfads; die Restwelt hat keinen.
[[nodiscard]] zustand::i64 anleihekurs(const zustand::Zustand& z, const Konstanten& konst,
                                       zustand::Gebiet land);

/// **T48 Nr. 13** -- `landespreis(g, s)`, der Sektorpreis eines Gebiets, gelesen aus
/// dem Zustand am Ende der Vorrunde (T39). T5 Klasse 5.
///
/// **Der einzige Grund, warum diese Groesse eine Funktion ist und kein Feldzugriff:**
/// T39 gibt ihr einen Ort. In der Marktraeumung nach T28 ist der Landespreis der Wert
/// am Ende der **Vorrunde**, nicht der dieser Runde. Der Zugriff dieser Runde waere
/// hier kein Zahlenfehler, sondern eine Abhaengigkeit von der Reihenfolge der sechs
/// Schritte, die nirgends stuende. Die Funktion nimmt deshalb den `Schreiber` und
/// nicht einen `Zustand`: An einem blanken Zustand laesst sich der Unterschied nicht
/// ausdruecken, und wer ihn nicht ausdruecken kann, trifft ihn frueher oder spaeter
/// falsch.
///
/// In Runde 1 ist das der Startwert des Jahrgangs, nach `spiel.md` der Index 10.000.
[[nodiscard]] zustand::i64 landespreis(const schreiber::Schreiber& rundenschreiber,
                                       zustand::Gebiet gebiet, zustand::Sektor sektor);

/// **T48 Nr. 14** -- `fondsanteil(l, s) = |stufen(l, s)| * stufenweite + anteil[l][s]`.
/// T5 Klasse 4 (Zehntausendstel).
///
/// Position und Beteiligung sind Anteile an **demselben** Korb und addieren sich.
/// **Betraege, nicht Vorzeichen** -- ein grosser Short bewegt einen Markt so stark wie
/// ein grosser Long. Dieselbe Zahl lesen der lokale Fussabdruck aus Gegenkraft 1 und
/// der Preisstoss aus Aktion 1.
[[nodiscard]] zustand::i64 fondsanteil(const zustand::Zustand& z, const Konstanten& konst,
                                       zustand::Gebiet land, zustand::Sektor sektor);

/// **T48 Nr. 15** -- `positionswert(p)`: die Stufenzahl mal dem Stufenwert, dann ueber
/// die Skalengrenze; **0 bei `stufen(p) = 0`**. T5 Klasse 1 (Fondsgeld, US-Cent).
///
/// Hier liegt die Skalengrenze, und sie wird **je Bewertung einmal** ueberquert, am
/// aeussersten Aufruf (T47, T50).
///
/// Zwei Vorgaben, die das Ergebnis aendern und deshalb woertlich zu nehmen sind:
///
///   * **Die Reihenfolge der Rundungen.** Verbindlich ist `stufen(p) * stufenwert(p)`
///     und nicht die genauere Form `mal_geteilt(markt(p), stufen(p) * stufenweite,
///     10.000)`. Die beiden unterscheiden sich um bis zu `|stufen(p)|` Einheiten; die
///     zweite waere genauer und machte jeden Regressionsbestand ungueltig, der mit der
///     ersten entstanden ist. Wer sie will, braucht einen ADR, keinen besseren Grund.
///   * **Der Abbruch bei `stufen(p) = 0` liegt vor `markt(p)`**, nicht dahinter. Die
///     meisten Steckplaetze sind die meiste Zeit leer.
[[nodiscard]] zustand::i64 positionswert(const zustand::Zustand& z, const Konstanten& konst,
                                         zustand::Steckplatz platz);

/// **T48 Nr. 16** -- `beteiligung_wert(l, s)`: der Korbanteil abzueglich
/// `ausstiegsabschlag`, dann ueber die Skalengrenze. T5 Klasse 1.
///
/// Die Umrechnung steht um den **aeussersten** Aufruf, also nachdem die Anteile
/// verrechnet sind. Das ist die Behebung von Befund 2 der sechsten Pruefung an der
/// Wurzel: Die Formel der Fassung 5 bestand aus zwei einheitenlosen Anteilen und war
/// damit skalenerhaltend -- was in Tausend USD hineinging, kam in Tausend USD heraus
/// und wurde als US-Cent verbucht. Faktor 100.000, Todesart 1 in derselben Runde.
///
/// Der Abschlag ist beim **Aufbau** bezahlt und wird beim gewoehnlichen Ausstieg nicht
/// ein zweites Mal abgezogen (T47 Punkt 1). Der `zwangsabschlag` aus Gegenkraft 1 ist
/// eine zusaetzliche Strafe und keine Ersetzung des ersten; er gehoert deshalb nicht
/// in diese Formel und nicht in dieses Modul.
[[nodiscard]] zustand::i64 beteiligung_wert(const zustand::Zustand& z,
                                            const Konstanten& konst, zustand::Gebiet land,
                                            zustand::Sektor sektor);

/// **T48 Nr. 17** -- `fondsvermoegen(z) = kasse + Summe der 20 Positionswerte +
/// Summe der 12 Beteiligungswerte - hebelstand`. T5 Klasse 1.
///
/// **Genau eine Funktion, fuenf Leser** (T47 Punkt 3): die Abrechnung in Schritt 6,
/// die Mandatspruefung, Todesart 1, der Invariantentest aus T30 Pruefung 2 und `v(z)`
/// aus T44. Dass alle fuenf dieselbe Zahl sehen, ist der Grund, warum
/// "Fondsvermoegen" durchgehend dasselbe heisst -- was der Fonds wert ist, wenn er
/// hier aufhoert.
///
/// **Keine Zustandsadresse.** Der Zustand haelt Kasse, Steckplaetze, Anteile und
/// Hebel; das Vermoegen ist deren Funktion. Ein Feld dafuer waere eine zweite Kopie
/// derselben Zahl -- derselbe Fehlertyp, den T39 fuer den Landespreis und T23 Punkt 9
/// fuer die BACI-Konkordanz schon geschlossen haben. Die 310 aus T15 aendern sich
/// dadurch nicht.
///
/// Beide Summen laufen ueber die Indexordnung aus T9, nie ueber eine Menge. Die zwoelf
/// Korbwerte entstehen je Aufruf **einmal** und werden von Steckplatz und Beteiligung
/// daraus gelesen (T47) -- nicht um Zeit zu sparen, sondern damit "eine Bewertung,
/// nicht zwei" eine Eigenschaft des Codes ist und nicht ein Satz.
[[nodiscard]] zustand::i64 fondsvermoegen(const zustand::Zustand& z,
                                          const Konstanten& konst);

/// **T48 Nr. 18** -- `hub(l, i) = |lies_neu(land.<l>.instrument.<i>.stand) -
/// lies_alt(land.<l>.instrument.<i>.stand)|`.
///
/// **Die einzige Groesse der Tabelle ohne eine einzige Klasse, und das ist kein
/// Versehen.** `hub` ist skalenerhaltend: Es bildet den Betrag einer Differenz zweier
/// Staende **derselben** Adresse, und die Klasse des Ergebnisses ist die der Adresse.
/// T48 schreibt sie je Instrument -- Klasse 3 fuer Zoll, Leitzins und Haushalt
/// (Basispunkte), Klasse 10 fuer die Regulierung (Stufen). Eine erfundene gemeinsame
/// Klasse waere hier die Fehlerart, gegen die T5 gebaut ist; die Zuordnung steht
/// deshalb als Fallunterscheidung in `src/werte.cpp`, und ein Instrument ausserhalb
/// der vier bekommt keine Klasse geschenkt, sondern bricht ab.
///
/// **Der Schreiber und nicht ein Zustand**, aus demselben Grund wie bei
/// `landespreis`: `lies_neu` und `lies_alt` sind nach T39 zwei verschiedene Zugriffe,
/// und an einem blanken Zustand liesse sich der Unterschied gar nicht ausdruecken.
/// Wer den Stand dieser Runde liest, bevor er geschrieben ist, bekommt keinen stillen
/// Rueckgriff auf die Vorrunde, sondern einen Abbruch.
///
/// **Der Betrag steht ueber der Differenz und nicht neben ihr.** Ist die Differenz
/// genau der kleinste `i64`, hat sie keinen darstellbaren Betrag; dann bricht diese
/// Funktion ab, statt aus einem Hub still eine negative Zahl zu machen (T6, T7).
[[nodiscard]] zustand::i64 hub(const schreiber::Schreiber& rundenschreiber,
                               zustand::Gebiet land, zustand::Instrument instrument);

/// **T48 Nr. 19** -- `keilhub(l, s) = mal_geteilt(welt.preis.<s>, hub(l, zoll),
/// 10.000)`. T5 Klasse 5.
///
/// Der Zollkeil auf dem Weltpreis, gemessen als Verschiebung in Indexpunkten: Klasse 5
/// mal Klasse 3 durch 10.000 ist wieder Klasse 5. Der Weltpreis liefert allein das
/// **Niveau**, an dem eine Rate in Basispunkten zu einer Verschiebung in Indexpunkten
/// wird; wen es getroffen hat, unterscheidet `hub` und nicht er.
///
/// **Der Weltpreis dieser Runde.** `spiel.md` schreibt ihn als `lies_neu` -- die
/// Marktraeumung setzt ihn in Schritt 4, die fuenfte Gegenkraft liest ihn in
/// Schritt 5. Die Ordnung bleibt damit zyklenfrei, und wo sie es einmal nicht ist,
/// bricht der Zugriff nach T39 ab, statt auf die Vorrunde zurueckzugreifen.
///
/// **Nur die vier spielbaren Laender und nur die zwei handelbaren Sektoren.** Die
/// Restwelt hat kein Politikinstrument und damit keinen Hub; der dritte Sektor hat
/// keinen Weltpreis. Beides bricht hier ab und nicht erst eine Ebene tiefer.
[[nodiscard]] zustand::i64 keilhub(const schreiber::Schreiber& rundenschreiber,
                                   zustand::Gebiet land, zustand::Sektor sektor);

/// **T48 Nr. 20** -- `preishub_zoll(l, s) = mal_geteilt(keilhub(l, s),
/// durchgriff(l, s), 10.000)`. T5 Klasse 5.
///
/// Der Teil der Preisverschiebung, den der Zollschritt verursacht hat -- und damit die
/// Verschiebung, mit der die Zollzeile der fuenften Gegenkraft rechnet. Der Rest der
/// Preisbewegung ist Konjunktur und hat keinen Verursacher. `durchgriff` kommt aus
/// `Konstanten` und ist eine Groesse des Jahrgangs, keine Zustandsadresse.
///
/// **Zwei Rundungen und nicht eine, und das ist die Vorgabe.** Die Formel schachtelt
/// diese Groesse ueber Nr. 19, und jede der beiden Stufen rundet nach T6 auf halbe
/// Betraege von null weg. Die zusammengezogene Form mit einer einzigen Rundung ist
/// genauer und ergibt eine **andere** Zahl -- dieselbe Lage wie bei `positionswert`,
/// und wie dort braucht sie einen ADR und keinen besseren Grund.
[[nodiscard]] zustand::i64 preishub_zoll(const schreiber::Schreiber& rundenschreiber,
                                         const Konstanten& konst, zustand::Gebiet land,
                                         zustand::Sektor sektor);

/// **T48 Nr. 21** -- `weltpreis_mit_zoll(g, s) = mal_geteilt(welt.preis.<s>, 10.000 +
/// zollstand(g), 10.000)`. T5 Klasse 5.
///
/// Der Weltpreis, wie ihn ein Gebiet sieht: das Niveau mal dem Zollfaktor. Ihr Leser
/// ist die Marktraeumung aus T28, nicht Gegenkraft 5 -- dort steht sie im Zaehler der
/// Preismischung, und der Zollkeil der Gegenkraft ist Nr. 19.
///
/// **Der Keil ist multiplikativ, und das ist keine Wahl.** Der Zollstand steht nach T5
/// in Klasse 3 (Basispunkte), der Weltpreis in Klasse 5 (Index); eine Summe zweier
/// Klassen kennt T5 nicht. Eine Rate trifft ein Niveau in diesem Modell ausnahmslos
/// als Faktor, wie in `schuld = mal_geteilt(bip, staatsschuld, 10.000)`.
///
/// **Alle fuenf Gebiete, und der Zollstand der Restwelt ist die Null.** Sie nimmt an
/// der Preisuebertragung teil -- `durchgriff` traegt nach T23 Punkt 5 zehn Werte, also
/// auch ihre Zeile --, hat aber nach T15 kein Politikinstrument. `zollstand(RW)` ist
/// deshalb keine Adresse, sondern die Zahl null, und diese Groesse liest fuer sie
/// nichts.
///
/// **Der Vorbehalt gehoert an die Funktion und wird hier nicht aufgeloest.**
/// `technik.md` meldet ihn bei T48 selbst, im Absatz ueber den Definitionsbereich
/// dieser Nummer: Er steht weder in T28 noch in `spiel.md` ausgeschrieben. Der
/// Architekt hat ihn aus dem Wort "je Gebiet" und aus
/// der Zahl zehn gelesen und meldet die Stelle selbst als die eine, an der er einem
/// Pruefer widerspruchslos folgen wuerde. Laeuft die Marktraeumung in Wahrheit nur
/// ueber die vier spielbaren Laender, ist die Restweltzeile ueberfluessig und nicht
/// falsch. Das ist eine Entwurfsfrage.
///
/// **Ein `Zustand` und kein `Schreiber`**, anders als bei Nr. 13 und Nr. 18 bis 20:
/// T48 und `spiel.md` schreiben beide Adressen dieser Formel blank hin, waehrend sie
/// dort `lies_alt` oder `lies_neu` ausschreiben, wo die Leseart das Ergebnis aendert.
/// Dazu kommt der eine benannte Leser: Die Marktraeumung sucht den Weltpreis gerade
/// erst, an ihrer Stelle gibt es weder einen alten noch einen neuen Stand von
/// `welt.preis.<s>`.
[[nodiscard]] zustand::i64 weltpreis_mit_zoll(const zustand::Zustand& z,
                                             zustand::Gebiet gebiet, zustand::Sektor sektor);

/// **T48 Nr. 22** -- `schaden(l, i) = mal_geteilt(menge(l, i), verschiebung(l, i),
/// 10.000)`, vier Zeilen. T5 Klasse 2.
///
/// Der Lobbyschaden eines Politikschritts in einer Runde: der Preis, den das Instrument
/// setzt, mal der Menge, auf die er wirkt -- beides an der Rundengrenze gemessen. Die
/// vier Zeilen aus `spiel.md`, mit Menge und Verschiebung in dieser Reihenfolge:
///
///   * `zoll`        -- `handelsvolumen(l, s)` mal `preishub_zoll(l, s)`, summiert
///                      ueber s in {1, 2}
///   * `leitzins`    -- `schuld(l)` mal `hub(l, leitzins)`
///   * `haushalt`    -- `bip(l)` mal `hub(l, haushalt)`
///   * `regulierung` -- `bip(l)` mal `hub(l, regulierung)` mal `regulierung_last`
///
/// **Eine Funktion mit vier Zeilen und nicht vier Funktionen** (T48), weil das Ergebnis
/// in allen vier Faellen Klasse 2 ist und die Stelligkeit dieselbe. Die Summe ueber die
/// Sektoren steht **innerhalb** der Zollzeile; nach aussen gibt auch sie eine Zahl je
/// Land und Instrument, und das ist die Zahl, die der dritte Skalenuebergang aus T50
/// entgegennimmt.
///
/// **`menge` und `verschiebung` gibt es hier nicht, und das ist eine Vorgabe.** T48
/// begruendet sie aus T5 selbst: `verschiebung` steht in der Zollzeile in Klasse 5 und
/// in den drei uebrigen in Klasse 3, hat also kein einheitliches Ergebnis, das sich
/// deklarieren liesse; `menge` ist immer Klasse 2, ist aber in der Zollzeile eine Zahl
/// je Sektor und sonst eine je Land. Beide sind Spaltenueberschriften einer Tabelle mit
/// vier Zeilen und keine Groessen -- eine gemeinsame Funktion muesste sich entweder
/// eine Klasse oder ein Argument ausdenken. Die Fallunterscheidung liegt deshalb
/// **innen**, dieselbe Bauart wie `markt(p)` (Nr. 5) mit den drei Steckplatzarten.
///
/// **Zwei Zustandseingaenge, und beide sind gebraucht.** `hub` und `preishub_zoll`
/// brauchen nach T39 den alten *und* den neuen Stand, also den Schreiber; `bip`,
/// `schuld` und `handelsvolumen` nennen ihre Adressen blank und nehmen einen `Zustand`,
/// aus dem sich der Schreiber nicht gewinnen laesst. `z` traegt die Mengen, die
/// `spiel.md` an der Rundengrenze liest. Dieselbe Bauart wie `marktkorb`, das aus
/// demselben Grund zwei Zustaende nimmt und beide benennt.
///
/// Ein fuenftes Instrument faellt in keine der vier Zeilen, sondern bricht ab -- und
/// die Meldung nennt `schaden` und nicht die Groesse darunter.
[[nodiscard]] zustand::i64 schaden(const zustand::Zustand& z,
                                   const schreiber::Schreiber& rundenschreiber,
                                   const Konstanten& konst, zustand::Gebiet land,
                                   zustand::Instrument instrument);

}  // namespace kern::werte
