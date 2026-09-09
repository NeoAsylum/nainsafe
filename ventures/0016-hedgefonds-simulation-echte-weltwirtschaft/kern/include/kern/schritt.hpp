#pragma once
//! `kern::schritt` -- die Runde als Geruest, im Modus `weltlauf`.
//!
//! Vorgaben: T10 (der Weltschritt zieht nicht), T10b (der Traeger der Zahlen, die keine
//! Adressen sind, und die Pruefsumme ueber ihn), T19 (die Kette gehoert nicht in den
//! Zustand), T38 (der Modus ist Argument und bringt eine Sollmaske mit), T39 (zwei
//! Lesezugriffe), T18 (der Schreiber ist der einzige Schreibweg), T9 (feste
//! Reihenfolge); `spiel.md`, Abschnitt *The loop* (die sechs Schritte).
//!
//! ## Was dieser Kasten ist -- und was er ausdruecklich nicht ist
//!
//! Er ist der **Rahmen** der Runde: Signatur, Rueckgabewert, die feste Reihenfolge der
//! sechs Schritte, die Rundenendpruefung. Er ist **keine fertig gerechnete Welt**: Von
//! den sechs Schritten hat seit Paket 0197 einer einen rechnenden Rumpf, Schritt 5; die
//! anderen fuenf tragen die Adressen ihrer Sollmaske vor. Danach steht dieselbe Welt
//! noch einmal da, eine Runde weiter, mit 175 Ursachensaetzen, die sagen, wo jede Zahl
//! herkommt. Das ist der Zuschnitt des Arbeitspakets 0033 und keine Unfertigkeit: Die
//! sechs Schritte der Runde sind sechs eigene Pakete, und dies ist die Buehne, auf der
//! sie einzeln aufgestellt werden.
//!
//! **Die eine Eigenschaft, die dieser Rahmen "auf Widerruf" ausgewiesen hatte, ist
//! widerrufen** -- und zwar dort, wo es vorgesehen war: in der Probe des ersten
//! rechnenden Schritts (Paket 0197). Die Kette liegt nicht mehr durchgehend in
//! aufsteigender Adressfolge, weil Schritt 5 seinen Block als Ganzes rechnet und nach
//! der Adressrunde laeuft. **Ihre Gestalt steht deshalb nicht mehr hier, sondern wird in
//! `test/schritt_probe.cpp` gemessen:** erst die Glieder der aufsteigenden Adressrunde,
//! dann die vier Zustimmungen mit der Ursache `Gegenkraft`, diese vier untereinander
//! wieder aufsteigend. Wer dem naechsten Schritt einen rechnenden Rumpf gibt, zieht sie
//! dort nach und nicht hier.
//!
//! **Am 2026-09-04 ist eine zweite Aussage widerrufen worden, und das gehoert hierher,
//! weil an ihrer Stelle etwas anderes steht.** Bis dahin hiess es: Die Pruefsumme des
//! Zustands aendert sich ueber eine Runde nicht. Seit Paket
//! `0071-rundennummer-in-den-zustand` aendert sie sich. An ihrer Stelle steht die
//! schwaechste Zusage, die der Rahmen halten kann und die ihm dafuer in **jedem**
//! Zustand haelt: **Ueber eine Runde im `weltlauf` wird `partie.runde` anders** --
//! Schritt 1 setzt sie auf die Nummer der Vorrunde plus eins, statt sie vorzutragen.
//! Wie viele der 310 Groessen sich sonst noch bewegen, haengt seit Paket 0197 am
//! Zustand; gezaehlt wird das nicht hier, sondern in `test/schritt_probe.cpp` gegen
//! einen unabhaengig gebauten Erwartungszustand.
//!
//! Der Widerruf ist keine Nachbesserung an 0033, sondern der Fall, fuer den es dort "auf
//! Widerruf" hiess: Ein Zustand, den eine vollstaendige Runde Feld fuer Feld unveraendert
//! laesst, ist von "keine Runde gelaufen" durch keinen Vergleich zu unterscheiden -- und
//! genau diese Unterscheidung braucht der Startwertriegel aus Paket 0027, der sonst gegen
//! die Runde des Kerns nie anschlaegt. Sie haengt weiterhin allein an `partie.runde`: Der
//! Zustand nach der Runde traegt eine groessere Rundennummer als der davor, und das gilt
//! ohne jede Annahme darueber, was die sechs Schritte sonst rechnen.
//!
//! ## Der Modus
//!
//! Gebaut ist **`Modus::Weltlauf`** und nur der. Er ist der einzige, der heute
//! vollstaendig baubar ist: Nach T38 entfallen in ihm Schritt 2 (Aktionen) und Schritt 6
//! (Abrechnung), also braucht der Rahmen weder einen Aktionstyp (T32, unbeauftragt) noch
//! `kern::werte` (Paket 0002, blockiert). **`Modus::Spielmodus` bricht ab**, und die
//! Meldung nennt den Grund -- ein stilles Vortragen aller 310 Adressen saehe aus wie eine
//! gerechnete Spielrunde und waere keine.
//!
//! ## Der Parametersatz, und warum er ein Argument ist
//!
//! Seit T10b nimmt die Runde als drittes Argument einen `const werte::Konstanten&` --
//! die Zahlen einer Runde, die keine Zustandsadressen sind. Eine Datei wird deshalb
//! trotzdem nicht gelesen: Der Kern liest keine (T2), der Traeger kommt fertig herein,
//! und `parameter.toml` faellt nach T27 beim Laden in benannte Felder, nicht hier.
//!
//! Der Rahmen **rechnet** mit keinem der Felder -- im `weltlauf` traegt jeder der sechs
//! Schritte vor. Er **prueft** sie: `parameter_pruefsumme` bildet die Summe ueber die
//! Schluesselfelder des Traegers, und weicht sie von der Zahl auf
//! `partie.parameter_pruefsumme` ab, bricht die Runde hart ab. Damit ist der
//! Parametersatz an den Zustand gebunden, ehe der erste Schritt ihn benutzen kann --
//! und zwar heute, wo noch keiner ihn benutzt, statt an dem Tag, an dem der erste es
//! tut und ein fremder Satz als gerechnete Welt herauskaeme.
//!
//! ## Was hier nicht steht
//!
//! Die **Regeln** der sechs Schritte (`spiel.md`), die **abgeleiteten Groessen**
//! (`kern::werte`), der **Verlauf** ueber mehrere Runden (nach T19 fuehrt ihn die
//! Sitzung, nicht der Kern) und die **Datenschicht** (T13).

#include <cstddef>
#include <utility>

#include "kern/pruefsumme.hpp"
#include "kern/schreiber.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

namespace kern::schritt {

using schreiber::Kette;
using schreiber::Modus;
using werte::Konstanten;
using zustand::Zustand;

/// Die Aktionen einer Runde -- **heute ein leerer Typ**.
///
/// Er steht in der Signatur, weil T10b ihn nennt (`schritt(vorrunde, aktionen,
/// konstanten, modus)`), und er ist leer, weil es den Aktionstyp im Kern noch nicht
/// gibt: **T32 ist unbeauftragt.** Ihn wegzulassen waere eine Signatur, die ein spaeteres Paket aendern
/// muss; ihn auszufuellen waere Arbeit an einem Kasten, den `specs/` noch nicht
/// beauftragt hat. Im Modus `weltlauf` entfaellt Schritt 2 ohnehin (T38), das Buendel
/// ist dort also nicht nur leer, sondern folgenlos.
struct Aktionsbuendel {
};

/// Was eine Runde liefert: **beides** (T19).
///
/// Die Feldnamen sind die aus T19 (`(neuer_zustand, kette_dieser_runde)`). Die Kette
/// geht **nicht** in den Zustand -- der bleibt bei 310 Feldern und 2.480 Byte; ein
/// Ergebnistyp daneben ist die Bauart, die T19 verlangt, und der Pruefstand kann die
/// Kette wegwerfen, wenn er nur Ergebnisse zaehlt.
struct Rundenergebnis {
    /// Der Zustand am Ende dieser Runde, wie ihn `Schreiber::rundenende` herausgibt --
    /// also erst nach der zweiseitigen Maskenpruefung aus T38.
    Zustand neuer_zustand;
    /// Die Ursachensaetze dieser Runde, in der Reihenfolge der Schreibzugriffe.
    Kette kette_dieser_runde;
};

/// Die Pruefsumme des Parametersatzes -- die Zahl, die auf
/// `partie.parameter_pruefsumme` gehoert (T10b, gebaut nach T12).
///
/// **Eine Funktion, zwei Aufrufer.** Der Jahrgangsbau schreibt die Zahl mit ihr in den
/// Startzustand, die Runde unten haelt sie gegen die Adresse. Zwei Rechenwege waeren
/// zwei Stellen, die auseinanderlaufen -- und ihr Auseinanderlaufen saehe genau wie ein
/// fremder Parametersatz aus.
///
/// **Sie laeuft ueber die Werte, nicht ueber den Dateitext.** Ueber den Text gerechnet
/// faerbte jede Kommentaraenderung an `parameter.toml` den ganzen Regressionsbestand
/// rot, ohne dass eine Zahl sich bewegt haette -- und der Kern, der keine Datei liest
/// (T2), koennte die Summe gar nicht nachrechnen. T10b hebt die aeltere Lesart auf.
///
/// **Sie laeuft nur ueber die sieben Schluesselfelder.** `leitzins_start` und
/// `durchgriff` sind nach T23 Groessen des Jahrgangs; der Zustand fuehrt vom Jahrgang
/// nur die Kennung und keine Summe ueber seinen Inhalt, also gaebe es zu ihnen nichts
/// zu vergleichen. Sie einzurechnen macht aus einer haltbaren Zusage eine, die kein
/// Zustand belegen kann.
///
/// Die Reihenfolge der Aufrufe **ist** die feste Feldreihenfolge aus T12 und steht
/// deshalb als Programmtext da. Die Speicheranordnung des Traegers geht nirgends ein:
/// `nimm_i64` zerlegt jeden Wert in acht Bytes in Little-Endian, auf jeder Maschine
/// gleich.
///
/// **Wer den Traeger um ein Schluesselfeld erweitert, ergaenzt hier eine Zeile.** Eine
/// Summe ohne das neue Feld ist keine kaputte Zahl, sondern eine, die sich nur nicht
/// mehr bewegt, wenn jenes Feld sich bewegt. Zwei Zusicherungen halten das, keine
/// ersetzt die andere, und die dritte Frage bleibt offen:
///
///   * Dass ein Feld **dazugekommen** ist, faengt seit Paket 0229 der Riegel unter
///     dieser Funktion. Er haelt die Feldzahl des Traegers gegen die Summe aus den
///     sieben Aufrufen hier und den drei Groessen des Jahrgangs; kommt ein elftes
///     Feld dazu, uebersetzt der Kern nicht mehr.
///   * Dass ein Feld **vergessen** wurde, faengt `test/schritt_probe.cpp`: Dort steht
///     dieselbe Liste ein zweites Mal und wird Feld fuer Feld gegen diese Rechnung
///     gehalten.
///   * Dass ein neues Feld der **richtigen** der beiden Sorten zugeschlagen wird,
///     prueft nichts. Wer es als Groesse des Jahrgangs verbucht und nur die zweite Zahl
///     hochzaehlt, kommt am Riegel vorbei. Das bleibt eine Lesung, und es steht hier,
///     damit niemand mehr in die Zusicherung hineinliest, als sie traegt.
///
/// Zurueck kommt ein `i64` und keine vorzeichenlose Zahl, weil der Platz dieser Summe
/// eine Zustandsadresse ist und die 310 Adressen `i64` tragen. Die Umdeutung ist seit
/// C++20 eine Wertumrechnung mit festgelegtem Ergebnis -- dasselbe Bitmuster, das
/// `nach_bytes_le` in der Gegenrichtung benutzt.
[[nodiscard]] constexpr zustand::i64 parameter_pruefsumme(const Konstanten& konstanten)
{
    pruefsumme::Summe summe;
    summe.nimm_i64(konstanten.stufenweite);
    summe.nimm_i64(konstanten.ausstiegsabschlag);
    summe.nimm_i64(konstanten.aufschlag);
    summe.nimm_i64(konstanten.lobbykosten);
    summe.nimm_i64(konstanten.gegenlobby_satz);
    summe.nimm_i64(konstanten.regulierung_last);
    summe.nimm_i64(konstanten.zustimmung_elastizitaet);
    return static_cast<zustand::i64>(summe.wert());
}

// ---------------------------------------------------------------------------
// Der Riegel gegen das zehnte Feld -- Paket 0229, aus dem Vorschlag 0231
// ---------------------------------------------------------------------------
//
// Bis hierher war die Zusicherung eine Lesung: Wer den Traeger erweitert, ergaenzt oben
// eine Zeile. Ab hier haelt sie der Uebersetzer, in der schwaecheren der beiden
// denkbaren Fassungen und der einzigen, die die Sprache heute hergibt: **Der Traeger
// hat genau so viele Felder, wie diese Datei glaubt.** Kommt eines dazu, ohne dass
// jemand eine der beiden Zahlen unten nachzieht, uebersetzt der Kern nicht mehr.
//
// **Ohne `sizeof`, ohne Fuellbytes, ohne die Anordnung im Speicher.** T12 verbietet der
// Summe, an der Speicheranordnung zu haengen. Ein Riegel zwei Zeilen daneben, der es
// doch taete, waere derselbe Fehler an der ueberwachenden Stelle: Er spraenge bei einem
// Ausrichtungsloch an, das keine Zahl bewegt, und schwiege bei einem Feld, das genau in
// eines hineinpasst.
//
// Gezaehlt wird stattdessen, wie viele Stellen eine Aufbauliste des Verbunds annimmt.
// Jede Stelle bekommt ihre **eigenen** geschweiften Klammern, und das ist kein
// Schoenheitsgriff, sondern die Sperre gegen die Klammerauslassung: Ohne sie duerfte eine
// Liste die Zahlen einer **rohen** Reihe einzeln hinschreiben, und der Zaehler saehe
// deren Stellen statt eines Feldes. Gemessen wird das seit Paket 0233 in
// `test/schritt_probe.cpp` an `ZahlUndRohreihe`: zwei Felder mit den Klammern, fuenf
// ohne sie -- ein zweiter Zaehler ohne die Klammern steht dort neben dem hiesigen.
//
// **Und die Grenze der Aussage, aus derselben Messung:** Eine `std::array` ist von der
// Auslassung nicht betroffen, weil der Platzhalter unten sich in sie umwandelt und die
// Stelle damit belegt ist. `Konstanten` fuehrt heute nur solche Reihen und zaehlt mit
// den Klammern wie ohne sie zehn Felder. Die Sperre gilt also nicht dem Traeger von
// heute, sondern dem von morgen -- dem ersten, der eine rohe Reihe bekommt.
//
// Beides -- dass der Zaehler zaehlt und dass er Reihen nicht aufloest -- misst dieselbe
// Datei an eigens gebauten Verbunden mit bekannter und verschiedener Feldzahl.

namespace feldzahl_intern {

/// Steht fuer irgendein Feld: Er wandelt sich in jeden Typ um, den die Stelle verlangt.
///
/// **Nur deklariert, nie definiert.** Gebraucht wird er allein in der unbewerteten
/// Anforderung unten; ein Rumpf waere Programmtext, den nichts je ruft.
struct Platzhalter {
    template <typename Feld>
    operator Feld() const noexcept;
};

/// Bindet einen `Platzhalter` an eine Stelle der Aufbauliste. Die Stellennummer wird
/// gebraucht, um das Paket zu entfalten, und sonst zu nichts -- deshalb steht sie hier
/// ohne Namen.
template <std::size_t>
using PlatzhalterAn = Platzhalter;

/// Nimmt `Verbund` eine Aufbauliste mit genau so vielen Stellen, wie das Paket lang ist?
template <typename Verbund, std::size_t... Stelle>
[[nodiscard]] consteval bool nimmt_stellen(std::index_sequence<Stelle...>) noexcept
{
    return requires { Verbund{{PlatzhalterAn<Stelle>{}}...}; };
}

/// Hier endet die Suche. Ein Verbund mit mehr Feldern bekommt diese Zahl statt seiner
/// eigenen -- also einen falschen Wert, an dem jeder Riegel unten rot wird, statt still
/// durchzulassen. Die Alternative waere eine Instanziierung ohne Ende.
inline constexpr std::size_t FELDSUCHE_ENDE = 32;

template <typename Verbund, std::size_t Bisher = 0>
[[nodiscard]] consteval std::size_t zaehle_felder() noexcept
{
    if constexpr (Bisher < FELDSUCHE_ENDE
                  && nimmt_stellen<Verbund>(std::make_index_sequence<Bisher + 1>{})) {
        return zaehle_felder<Verbund, Bisher + 1>();
    } else {
        return Bisher;
    }
}

}  // namespace feldzahl_intern

/// Die Zahl der Felder eines Verbunds, beim Uebersetzen gezaehlt.
///
/// Gilt fuer einen Verbund aus Zahlen und Reihen davon -- die Gestalt von `Konstanten`.
/// Ein Feld, das sich aus **einer** Stelle nicht aufbauen laesst, wuerde zu klein
/// gezaehlt; im Kern gibt es kein solches, und der Riegel unten stuende bei einem
/// sofort rot.
template <typename Verbund>
inline constexpr std::size_t feldzahl = feldzahl_intern::zaehle_felder<Verbund>();

/// Die sieben Schluesselfelder: so viele Aufrufe stehen in `parameter_pruefsumme`, und
/// diese Zahl ist ihre vierte Abschrift -- die einzige, die der Uebersetzer haelt.
inline constexpr std::size_t SUMMIERTE_FELDER = 7;

/// `leitzins_start`, `durchgriff` und `pfadstand` -- die Groessen des Jahrgangs, die nach
/// T23 ausserhalb der Summe liegen und deshalb nicht mitgezaehlt, sondern danebengezaehlt
/// werden.
///
/// **Was diese Gruppe bindet, ist die Herkunft des Wertes und nicht seine Bestaendigkeit**
/// (Paket 0284). Bis dahin waren ihre beiden Mitglieder ueber die ganze Partie fest, und
/// es lag nahe, das fuer die Bedingung zu halten; `pfadstand` traegt in jeder Runde eine
/// andere Zahl und gehoert trotzdem hierher. Die Bedingung ist die, die den Ausschluss aus
/// der Summe traegt: Der Wert kommt aus dem Jahrgang, und der Zustand fuehrt von ihm nur
/// `partie.jahrgang_id` und keine Summe ueber seinen Inhalt -- es gaebe zu ihm nichts zu
/// vergleichen. Bestaendigkeit war eine Eigenschaft der ersten beiden.
inline constexpr std::size_t JAHRGANGSFELDER = 3;

static_assert(feldzahl<Konstanten> == SUMMIERTE_FELDER + JAHRGANGSFELDER,
              "kern::werte::Konstanten traegt nicht mehr sieben summierte Felder und "
              "drei Groessen des Jahrgangs. Wer ein Schluesselfeld zulegt, nimmt es in "
              "parameter_pruefsumme auf und zaehlt SUMMIERTE_FELDER hoch; wer eine "
              "Groesse des Jahrgangs zulegt, zaehlt JAHRGANGSFELDER hoch. Ein Feld, das "
              "in keiner der beiden Zahlen steht, ist ein Regler, den die Pruefsumme "
              "nicht bewacht.");

/// Eine Runde: aus dem Zustand am Ende der Vorrunde wird der dieser Runde.
///
/// **Eine reine Funktion ohne gezogene Zahlen** (T10). Sie hat kein Argument dafuer und
/// zieht keine: Nach `spiel.md` ist jede Regel eine Schwelle, ein Zaehler oder eine
/// Rechnung, und im `weltlauf` wird nach T38 ohnehin kein einziger Strom angefasst.
/// Derselbe Zustand, dasselbe Buendel, derselbe Parametersatz und derselbe Modus ergeben
/// deshalb in jedem Lauf dasselbe Ergebnis -- das ist Anforderung 1 des Vorhabens, und
/// sie kostet hier nichts.
///
/// `vorrunde` ist der Zustand am Ende der Vorrunde; in Runde 1 der Startzustand des
/// Jahrgangs. Die Nummer dieser Runde ist `partie.runde` der Vorrunde **plus eins**, und
/// sie steht danach im zurueckgegebenen Zustand: Schritt 1 **setzt** das Feld, statt es
/// vorzutragen (Paket 0071). Nach T38 liegt es in beiden Sollmasken und wird damit jede
/// Runde geschrieben; seit 0071 wird es auch jede Runde veraendert. `partie.runde` traegt
/// also die Nummer der letzten abgeschlossenen Runde -- vor der ersten die Null.
///
/// `konstanten` sind die Zahlen dieser Runde, die keine Adressen sind (T10b). Der Rahmen
/// liest keines der Felder; er prueft nur, dass der Satz zu diesem Zustand gehoert.
///
/// **Harte Fehler, alle ohne Ersatzwert, in der Reihenfolge, in der sie greifen:**
///   * `modus == Modus::Spielmodus` -- in diesem Rahmen nicht gebaut, siehe oben.
///   * `partie.runde` der Vorrunde ist negativ oder der groesste `int64_t`. Eine Runde
///     vor der ersten gibt es nicht, und eine nach der letzten zaehlbaren auch nicht.
///   * die Summe ueber die Schluesselfelder von `konstanten` weicht von der Zahl auf
///     `partie.parameter_pruefsumme` ab. Ein Ersatzwert waere hier besonders verlockend
///     und besonders falsch: Ein voreingestellter Traeger rechnet nach T10b eine tote
///     Welt, die wie eine gerechnete aussieht.
///   * jeder Abbruch aus `Schreiber` -- zweiter Schreibzugriff, Lesezugriff auf eine
///     noch ungeschriebene Adresse, verfehlte Sollmaske am Rundenende.
///
/// **Vier weitere sind mit dem rechnenden Rumpf von Schritt 5 dazugekommen** (Paket
/// 0197; die Schranke vor der Summe hat Paket 0240 aus der letzten herausgeloest). Alle
/// vier greifen erst, wenn die drei Schranken des Rahmens gehalten haben. **Wo eine
/// Schranke steht, sagt ihr eigener Eintrag**, und ebenso, ob ein Zustand sie heute
/// erreicht:
///   * der Nenner der Zustimmungsregel. Gelesen wird er mit `kern::werte::bip`, und er
///     bricht nacheinander auf zwei Weisen ab: in `bip` selbst, wenn die
///     Wertschoepfungssumme den `i64` verlaesst (T7), und danach aus `kern::schritt`
///     heraus, in `realeinkommenshub`, wenn der gelesene Wert die Nennerbedingung aus
///     `spiel.md` nicht erfuellt. **Ihre Bedingungen stehen dort und nicht hier**: Ein
///     Kopf, der eine bewegliche Tatsache wiederholt, wird falsch, sobald sie sich
///     bewegt. Beide Schranken werden jede Runde gerechnet, fuer jedes Land, und dieser
///     Eintrag ist der einzige der vier, dessen Abbruch ein Zustand auch **erreicht**:
///     Ein Zustand, dessen Wertschoepfung nirgends positiv ist, faellt in die
///     Nennerbedingung, und darum kommt zu ihrer Kennung in jedem gruenen Lauf eine
///     Abbruchmeldung an.
///   * die Summe der Zustimmungsregel verlaesst den `i64`, ehe die Klemme der Regel den
///     Wert auf seine Schranke zurueckholen kann. Die Schranke steht seit Paket 0240 aus
///     `kern::schritt` heraus vor der Addition, in `summe_der_regel_pruefen`, und faengt
///     genau die Paare, an denen `festkomma::plus` dahinter abbraeche -- das `plus`
///     dieser Regel kann seither nicht mehr abbrechen. Gerechnet wird die Vorbedingung
///     jede Runde; ob ein Zustand ihren Abbruch erreicht, steht seit Paket 0284 anders da
///     als vorher. Bis dahin trug diese Zeile ein "nein" und einen Grund: Der additive
///     Term ist ein Produkt mit dem Hub, und der Hub blieb null, weil Schritt 3 vortrug.
///     Schritt 3 schreibt jetzt den Pfadstand, der Hub kann von null verschieden sein,
///     und damit ist die Frage offen statt beantwortet. **Offen und nicht beantwortet ist
///     hier die richtige Auskunft** -- wer sie schloesse, muesste ueber die Pfadwerte
///     eines Jahrgangs reden, die niemand geladen hat.
///   * jeder Ueberlauf in `kern::werte::schaden`. Dorthin fuehrt `politiklast` in
///     derselben Quelle, und nur fuer ein Instrument, dessen Stand sich in dieser Runde
///     bewegt hat. Seit Paket 0284 bewegt Schritt 3 die drei pfadgestuetzten Staende
///     jedes Landes, sobald der Traeger dort etwas anderes fuehrt als die Adresse -- der
///     Weg wird also betreten, und das ist der Zweck jenes Pakets und keine Nebenwirkung.
///   * jeder Ueberlauf ueber den `i64` hinaus in der **uebrigen** Festkommarechnung der
///     Zustimmungsregel -- Vorzeichenwechsel, Punktrechnung, die Summe der Politiklast.
///     Sie rechnet mit `kern::festkomma`, und dessen Strich- und Punktrechnung bricht
///     nach T7 hart ab, statt umzubrechen. Dorthin fuehren in `kern/src/schritt.cpp` der
///     Rumpf von Schritt 5 selbst und die beiden Hilfen, die er dafuer ruft --
///     `realeinkommenshub` und, aus ihm heraus, `politiklast`. Rumpf und
///     `realeinkommenshub` rechnen jede Runde; dass Last, Hub und Wirkung dabei null
///     bleiben, war bis Paket 0284 eine Folge des vortragenden Schritts 3 und ist es seit
///     ihm nicht mehr. `politiklast` summiert jetzt fuer jedes bewegte Instrument einen
///     `schaden`, und dieser Eintrag sagt daher dasselbe wie der darueber: Der Weg wird
///     betreten, wie weit er traegt, entscheiden die Zahlen des Jahrgangs.
///
/// **Was an dieser Aufzaehlung veraltet, und was daraus folgt** (Paket 0249): Nicht ihre
/// Genauigkeit veraltet, sondern **wo** eine Schranke steht -- Paket 0240 hat eine von
/// `kern::festkomma` nach `kern::schritt` gezogen, und dieser Kopf nannte danach den
/// falschen Ort, ohne dass irgendetwas rot wurde. Prosa ist der Traeger fuer den
/// **Grund** einer Schranke: warum sie keinen Ersatzwert bekommt und welcher Zustand
/// ihren Weg heute unbetreten laesst. Sie ist nicht der Traeger dafuer, **welche**
/// Schranke anschlaegt; das halten die `Riegel`-Verzeichnisse der Testschicht, und sie
/// halten es in zwei Staerken, nach denen sie auch heissen: Zu jeder Kennung in einem
/// `ALLE_RIEGEL` muss in jedem Lauf eine Abbruchmeldung ankommen, sonst faellt der Lauf;
/// ein `RIEGEL_OHNE_ZUSTAND` fuehrt daneben die Schranken, die kein Zustand erreicht, und
/// ist von dieser Vollzaehligkeit ausgenommen -- zu ihnen kommt nie eine Meldung an, und
/// der Lauf faellt trotzdem nicht. **Wofuer dieser Kopf einsteht: Die beiden Abbrueche aus
/// `kern::schritt` heraus haben in den Verzeichnissen der Probe zu diesem Schritt eine
/// Kennung -- die Nennerbedingung in deren `ALLE_RIEGEL`, die Schranke vor der Summe in
/// deren `RIEGEL_OHNE_ZUSTAND`. Fuer diese beiden liest, wer wissen will, welche Schranke
/// heute wirklich anschlaegt, dort und nicht hier.** Ueber die beiden anderen Eintraege
/// sagt dieser Kopf nichts: weder dass eine Schranke aus `kern::werte` oder
/// `kern::festkomma` irgendwo eine Kennung hat, noch dass sie keine hat. Beide Richtungen
/// waeren Aussagen ueber Proben, die dieses Paket nicht schreibt, und genau solche
/// Aussagen sind an dieser Aufzaehlung schon viermal veraltet, ohne dass etwas rot wurde.
/// Und wer hier eine Schranke dazuschreibt, schreibt ihren Ort in ihren eigenen Eintrag,
/// statt ihn einer Gruppe vorwegzustellen: Die Gruppenzeile, die das bisher tat, ist mit
/// diesem Paket fort.
[[nodiscard]] Rundenergebnis schritt(const Zustand& vorrunde, const Aktionsbuendel& aktionen,
                                     const Konstanten& konstanten, Modus modus);

}  // namespace kern::schritt
