#pragma once
//! `daten::Jahrgang` -- die drei Politikpfade eines Jahrgangs im Speicher, und der
//! Aufrufer, der `kern::werte::Konstanten::pfadstand` je Runde fuellt.
//!
//! Vorgaben: T23 Punkt 3 (historische Politikpfade fuer Leitzins, Zollhoehe und
//! Haushaltssaldo; die Finanzmarktregulierung hat keinen Anker), T23 Punkt 5
//! (`leitzins_start` ist die erste Stuetzstelle des Leitzinspfads; `aufschlag_min`),
//! T40 (`R = stuetzstellen - 1`, und keine daraus abgeleitete Zahl steht als Literal),
//! T51 (Schrittweite und Wertebereich je Instrument; im `weltlauf` gilt die Schrittweite
//! nicht, der Wertebereich schon), T61 (die Regulierung hat keine Reihe), T15 (die
//! Restwelt hat keine Instrumente), T4 (kein Gleitkomma), T13 (`daten` haengt an `kern`,
//! nie umgekehrt), T2 (der Kern liest keine Datei).
//!
//! ## Warum dieser Kasten der Aufrufer ist
//!
//! `kern/include/kern/werte.hpp` verortet am Feld `pfadstand` die Klemme auf das Ende
//! der Reihe ausdruecklich beim Aufrufer, der das Feld fuellt, und damit ausserhalb des
//! Kerns. Seit Paket 0284 schreibt Schritt 3 den Pfadstand in die Adressen; gefuellt hat
//! den Traeger bis hierher niemand. Diese Datei ist die letzte Stelle, an der zu einer
//! Stuetzstelle ausserhalb ihres Wertebereichs noch Land und Reihe **namentlich** zu
//! nennen sind -- danach spricht als erstes ein `festkomma`-Abbruch in Schritt 5, und
//! der kennt weder das eine noch das andere.
//!
//! ## Was hier ausdruecklich NICHT steht
//!
//! Das Lesen von `jahrgang-<jahr>.bin`, `sollreihen-<jahr>.bin` und `manifest.toml`, das
//! Auswerten von `parameter.toml`, der `durchgriff` aus T23 Punkt 5 und die
//! Provenienztabelle aus T45. Das Jahrgangsformat schreibt `werkzeuge/aufbereitung`, und
//! dieses Mitglied ist nicht gebaut. Ein Ladeweg ohne Format waere entweder blockiert
//! oder erfaende das Format nebenbei. Was hier steht, ist die Rechnung: der Traeger, die
//! Abbildung von Runde auf Stuetzstelle, die Klemme und die beiden Schranken.
//!
//! ## Einheit und Vorzeichen
//!
//! Alle drei Reihen tragen nach `daten/reihen.toml` die Modelleinheit `bp` -- T5
//! Klasse 3, Raten in Basispunkten, ganzzahlig. Ein Pfad darf negativ werden, und das
//! ist nicht der Ausnahmefall: Der Einlagesatz der EZB steht ab 2014 unter null, und
//! `aufschlag_min` unten ist genau die Groesse, die daraus folgt.

#include <array>
#include <cstddef>

#include "kern/meldung.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

namespace daten {

using kern::zustand::Gebiet;
using kern::zustand::i64;
using kern::zustand::Instrument;

/// Die Wand aus T40: Der Jahrgangsbau bricht bei `R > 26` ab, statt eine Ergebnisskala
/// zu erzeugen, in der ein Wert zwei Bedeutungen traegt.
///
/// Das ist eine Schranke **an** R und keine aus R abgeleitete Zahl -- die verbietet T40
/// als Literal, und die Groesse eines Feldes ist genau so eine. Deshalb steht die Zahl
/// hier einmal, und die Feldbreite unten wird aus ihr gebildet.
inline constexpr i64 RUNDEN_HOECHSTENS = 26;

/// Wie viele Stuetzstellen ein Jahrgang hoechstens traegt -- hergeleitet und nicht
/// hingeschrieben, weil `R = stuetzstellen - 1` gilt (T40).
inline constexpr std::size_t STUETZSTELLEN_HOECHSTENS =
    static_cast<std::size_t>(RUNDEN_HOECHSTENS) + 1;

/// Ein Jahrgang mit weniger als zwei Stuetzstellen haette `R = 0` und damit keine Runde.
inline constexpr std::size_t STUETZSTELLEN_MINDESTENS = 2;

/// Die Nummer der Reihe, aus der ein pfadgestuetztes Instrument seinen Pfad bekommt --
/// Leitzins 9, Zollniveau 13, Haushaltssaldo 12, so wie `daten/reihen.toml` sie fuehrt.
///
/// Bricht ab fuer `Instrument::Regulierung` und fuer jede Kennung ausserhalb der
/// Aufzaehlung: Zu ihnen gibt es keine Reihe (T61). Dieselbe Bedingung wie in
/// `kern::werte::pfadstand`, hier aber diesseits des Kerns, weil die Reihennummer eine
/// Groesse der Daten ist und keine des Zustands.
[[nodiscard]] i64 reihe_von(Instrument instrument);

/// Der Name des Instruments fuer eine Meldung. Bricht unter denselben Bedingungen ab wie
/// `reihe_von`.
[[nodiscard]] const char* instrument_name(Instrument instrument);

/// Das Kuerzel eines spielbaren Landes -- `US`, `CN`, `DE`, `BR` in der Ordnung aus T9.
///
/// Die Restwelt hat keine Instrumente (T15) und bekommt deshalb kein Kuerzel, sondern
/// einen Abbruch. Der Kern fuehrt diese Namen nicht: Er kennt `Gebiet` als Aufzaehlung
/// und die Adressform, nicht das Kuerzel als eigenes Wort.
[[nodiscard]] const char* land_kuerzel(Gebiet land);

/// Der Wertebereich eines Instruments aus `parameter.toml` (T51).
///
/// **Ein Argument und kein Feld von `kern::werte::Konstanten`.** `instrument_min` und
/// `instrument_max` sind Parameterschluessel; wer sie zu Feldern des Traegers machte,
/// liesse den Traeger und die Pruefsumme ueber ihn wachsen -- und genau das schliesst
/// der Kommentar am Feld `pfadstand` aus. Gelesen werden sie hier aus nichts: Sie kommen
/// herein, weil der Aufrufer sie hat.
struct Wertebereich {
    i64 min = 0;
    i64 max = 0;
};

/// Je pfadgestuetztem Instrument einer, indiziert mit dem Wert von `zustand::Instrument`
/// -- dieselbe Ordnung wie der innere Index des Pfadtraegers.
using Wertebereiche = std::array<Wertebereich, kern::zustand::PFADINSTRUMENTE>;

/// Das Ergebnis der Wertebereichspruefung: eine **Meldung**, kein gekappter Pfad.
///
/// T51 sagt fuer den `weltlauf` woertlich, ein Verlassen des Wertebereichs sei ein Befund
/// des Jahrgangsbaus und kein stilles Kappen einer Zielgroesse. Ein Kappen erzeugte eine
/// Zahl, die keine Pruefung mehr bemerkt; deshalb kommt hier die Zahl der Verletzungen
/// heraus und der Wortlaut der ersten. Die erste und nicht alle, weil der Puffer einer
/// `Meldung` fest ist -- die Zahl daneben sagt, wie viele es sonst noch sind.
struct Bereichsbefund {
    std::size_t verletzungen = 0;
    kern::meldung::Meldung erste{};

    [[nodiscard]] bool sauber() const noexcept { return verletzungen == 0; }
};

/// Die drei pfadgestuetzten Instrumente der vier spielbaren Laender ueber die
/// Stuetzstellen eines Jahrgangs.
///
/// **Was nicht darin steht.** Die Finanzmarktregulierung: Sie hat keine Reihe (T61), ihr
/// Stand steht nach T45 in der Adresse und wird von Schritt 3 vorgetragen. Und die
/// Restwelt: Sie hat keine Instrumente (T15). Beide Einschraenkungen sind hier die
/// Feldbreite und keine Pruefung an der Aufrufstelle -- `zustand::PFADINSTRUMENTE` und
/// `zustand::LAENDER` sind genau die beiden schmaleren Zahlen.
///
/// **Feste Groesse statt Zeigerarithmetik.** Die dritte Ordnung ist auf
/// `STUETZSTELLEN_HOECHSTENS` gelegt und nicht auf die tatsaechliche Zahl; wie viele
/// davon belegt sind, sagt `stuetzstellen()`. Jeder Zugang unten prueft seinen Index
/// gegen diese Zahl und nicht gegen die Feldbreite -- eine Stuetzstelle jenseits des
/// Jahrgangs liest sonst eine vorbelegte Null und sieht wie ein Datum aus.
class Jahrgang {
public:
    /// Legt einen Jahrgang mit `stuetzstellen` Stuetzstellen an, alle Pfade auf null.
    ///
    /// Bricht ab unterhalb von `STUETZSTELLEN_MINDESTENS` und oberhalb von
    /// `STUETZSTELLEN_HOECHSTENS` (T40). Null ist dabei kein brauchbarer Pfad, sondern
    /// dieselbe Entscheidung wie bei `kern::werte::Konstanten`: Ein plausibel aussehender
    /// Vorgabewert waere ein Politikpfad, den niemand gemessen hat.
    explicit Jahrgang(std::size_t stuetzstellen);

    /// Legt den Wert einer Stuetzstelle ab. Jeder der drei Indizes wird geprueft.
    void setze(Gebiet land, Instrument instrument, std::size_t stuetzstelle, i64 wert);

    /// Der Wert einer Stuetzstelle. Jeder der drei Indizes wird geprueft.
    [[nodiscard]] i64 stelle(Gebiet land, Instrument instrument,
                             std::size_t stuetzstelle) const;

    /// Wie viele Stuetzstellen der Jahrgang traegt.
    [[nodiscard]] std::size_t stuetzstellen() const noexcept { return stuetzstellen_; }

    /// Die Spiellaenge `R = stuetzstellen - 1` (T40).
    ///
    /// Gebildet und nicht gespeichert: Zwei Felder fuer eine Groesse haetten zwei Herren,
    /// und T40 verbietet gerade die aus R abgeleitete Zahl, die nebenherlaeuft.
    [[nodiscard]] i64 runden() const noexcept;

    /// Ob eine Runde jenseits des Fensters liegt, also `runde > R`.
    ///
    /// Abgeleitet und nicht gemerkt: Dieselbe Bedingung, unter der die Abbildung unten
    /// klemmt, und damit dieselbe Zahl. Ein gemerkter Merker liefe auseinander, sobald
    /// eine Runde gar keinen Pfad liest.
    [[nodiscard]] bool ueber_fenster(i64 runde) const noexcept;

    /// Die Stuetzstelle, aus der eine Runde ihren Stand bekommt.
    ///
    /// **Die Abbildung, und woraus sie folgt.** Die Stuetzstellen sind die Jahre des
    /// Fensters, und `R = stuetzstellen - 1` ist die Zahl der Runden (T40) -- eine Runde
    /// liegt also zwischen zwei Stuetzstellen und beginnt an der linken. Runde 1 beginnt
    /// an der ersten, Runde `r` an der `r`-ten; der Versatz ist `r - 1` und keine
    /// gewaehlte Zahl.
    ///
    /// **Und hier sitzt die Klemme**, weil `kern::werte::Konstanten` sie beim Aufrufer
    /// verortet: Eine Runde jenseits von `R` bekommt die letzte Stuetzstelle. Das ist
    /// kein Ersatzwert, sondern die einzige Stelle der Reihe, die noch existiert -- ein
    /// Versatz ohne Klemme liest hinter das Feld, und der Adressensanitizer sieht das im
    /// Nachtlauf, ein Kaeufer nicht.
    ///
    /// Bricht ab fuer `runde < 1`: Die Runden beginnen bei eins, und eine Runde null ist
    /// ein Programmfehler und kein Sonderfall mit eigenem Wert.
    [[nodiscard]] std::size_t stuetzstelle_zu_runde(i64 runde) const;

    /// Fuellt `kern::werte::Konstanten::pfadstand` fuer diese Runde.
    ///
    /// Geschrieben wird in der Ordnung, in der `kern::werte::pfadstand` liest: aeusserer
    /// Index Land, innerer Index der Wert von `zustand::Instrument`. Die Schleifen laufen
    /// aufsteigend ueber beide Ordnungen -- geordnete Iteration, damit derselbe Jahrgang
    /// und dieselbe Runde bitgleich denselben Traeger ergeben.
    void fuelle_pfadstand(kern::werte::Konstanten& konstanten, i64 runde) const;

    /// Der Leitzins des Startjahrs eines Landes -- die **erste** Stuetzstelle des
    /// Leitzinspfads (T23 Punkt 5).
    ///
    /// Abgeleitet und nicht zweitgespeichert. Ein eigenes Feld daneben gaebe einer
    /// Groesse zwei Herren, und dagegen ist T45 geschrieben; ausserdem entstuende so eine
    /// Messung, die sich vom Pfad, aus dem sie stammt, unbemerkt entfernen kann.
    [[nodiscard]] i64 leitzins_start(Gebiet land) const;

    /// Schreibt `leitzins_start` fuer alle vier Laender in den Traeger.
    ///
    /// Die eine Stelle, an der diese Jahrgangsgroesse in `Konstanten` landet -- damit das
    /// naechste Paket sie nicht ein zweites Mal herleitet. Anders als `pfadstand` steht
    /// sie ueber die ganze Partie fest und wird deshalb nicht je Runde gerufen.
    void fuelle_leitzins_start(kern::werte::Konstanten& konstanten) const;

    /// `aufschlag_min = 1 - min ueber alle l und t von leitzins_pfad[l][t]` (T23 Punkt 5).
    ///
    /// Der Nenner von `anleihekurs(l)` ist `leitzins[l] + aufschlag`; der Leitzins hat
    /// damit die untere Schranke `1 - aufschlag`, und der historische Pfad muss sie
    /// halten. Ein Pfad mit dem Minimum -50 Basispunkten gibt 51, einer mit dem Minimum 0
    /// gibt 1. Gerechnet und nicht uebernommen: Welche Reihe eingebettet ist, entscheidet
    /// der Jahrgangsbau, die Schranke folgt daraus.
    [[nodiscard]] i64 aufschlag_min() const;

    /// Ob ein Parameterpaket mit diesem `aufschlag` fuer diesen Jahrgang zulaessig ist.
    ///
    /// `aufschlag < aufschlag_min()` ist unzulaessig -- zurueckgewiesen hier, statt
    /// spaeter in `anleihekurs` durch null zu teilen oder das Vorzeichen zu drehen.
    [[nodiscard]] bool aufschlag_zulaessig(i64 aufschlag) const;

    /// Haelt jede Stuetzstelle gegen den Wertebereich ihres Instruments (T51).
    ///
    /// Meldet und kappt nicht. Die Meldung nennt Land und Reihe namentlich, weil sie die
    /// letzte Stelle ist, an der beide noch bekannt sind.
    [[nodiscard]] Bereichsbefund pruefe_wertebereich(const Wertebereiche& bereiche) const;

private:
    std::size_t stuetzstellen_ = 0;

    /// `pfad_[land][instrument][stuetzstelle]`, in Basispunkten.
    ///
    /// Die beiden aeusseren Ordnungen sind die des Pfadtraegers in
    /// `kern::werte::Konstanten`; das Fuellen unten ist damit eine Abschrift ohne
    /// Umordnung, und eine vertauschte Ordnung waere an dieser Stelle zu sehen statt in
    /// einer Zahl in Runde 400.
    std::array<std::array<std::array<i64, STUETZSTELLEN_HOECHSTENS>,
                          kern::zustand::PFADINSTRUMENTE>,
               kern::zustand::LAENDER>
        pfad_{};
};

}  // namespace daten
