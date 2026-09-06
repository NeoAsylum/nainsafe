#pragma once
//! `kern::verlauf` -- der Traeger, in dem die Rundenketten gesammelt werden.
//!
//! Vorgaben: T19 (die Kette gehoert nicht in den Zustand; die Runde liefert Zustand und
//! Kette nebeneinander, und die Sitzung sammelt die Ketten in einem Verlauf; die
//! Aufnahmekapazitaet je Runde ist fest, und ihr Erreichen ist ein harter Fehler und
//! keine stille Kuerzung), T18 (der Ursachensatz und seine sieben Felder), T9 (feste
//! Reihenfolge, keine streuende Menge). Die Sprache ist C++20 nach ADR 0011.
//!
//! ## Warum es diesen Kasten gibt
//!
//! Von T19 war die eine Haelfte gebaut: `kern::schritt::schritt` gibt ein
//! `Rundenergebnis` zurueck, und darin liegt neben dem Zustand die
//! `kette_dieser_runde`. Wer die Kette einer Runde zurueckgibt und sie niemand aufheben
//! laesst, hat sie fuer die naechste Runde verloren -- und mit ihr die Unterschiedsebene
//! aus T20, die die Kette rueckwaerts bis zur ausloesenden Aktion aufloest.
//!
//! Dieser Kasten ist der Behaelter, den T19 dafuer beim Namen nennt. Er nimmt die Ketten
//! entgegen und gibt sie zeichengleich wieder heraus. Er rechnet nichts, er loest nichts
//! auf, er gibt nichts aus.
//!
//! ## Was hier nicht steht
//!
//! Die **Ausgabe** in den drei Ebenen (`kern::zustandsausgabe`). Die **Erzeugung** der
//! Ketten (`kern::schreiber`, `kern::schritt`) -- an einem Ursachensatz wird hier nichts
//! geaendert, er wird abgelegt. Und der **Zustand**: T19 sagt gerade, dass die Kette dort
//! nicht hingehoert, und dieser Kasten bindet den Zustandskopf nur wegen des Zahlentyps
//! und der 310.
//!
//! ## Die Rueckwaertsaufloesung aus T20 steht seit Paket 0091 hier
//!
//! An dieser Stelle stand bis dahin, sie lese den Verlauf, statt in ihm zu stehen. Die
//! erste Haelfte gilt weiter und ist die Bauart von `Aufloesung`: Sie haelt keine Kette,
//! sie zeigt in eine. Der Kasten `Verlauf` hat keine Mitgliedsfunktion dazubekommen, die
//! aufloest -- er nimmt weiter nur auf und gibt heraus.
//!
//! Die zweite Haelfte ist eingeloest, und deshalb steht der Satz nicht mehr da: Als
//! Verweis auf ein Anderswo, das es nicht gibt, kostet er den naechsten Leser eine Suche.
//!
//! ## Die beiden Kapazitaeten, und warum beide hart sind
//!
//! **Je Runde.** `GLIEDER_JE_RUNDE` ist die Zahl, die T19 fest verlangt. Sie ist
//! hergeleitet und nicht geschaetzt: Nach T18 wird jede der 310 Adressen je Runde
//! hoechstens einmal geschrieben, und jeder Schreibzugriff haengt genau einen
//! Ursachensatz an. Mehr als 310 Glieder kann eine Rundenkette deshalb nicht haben.
//!
//! **Ueber die Partie.** `RUNDEN_KAPAZITAET` ist **nicht** die Partielaenge. Nach T40 ist
//! die Partielaenge eine Groesse des Jahrgangs und keine Konstante des Codes: Sie
//! entsteht beim Laden aus der Zahl der Stuetzstellen, faellt fuer jeden Jahrgang anders
//! aus, und keine aus ihr abgeleitete Zahl steht irgendwo als Literal. Ein Behaelter,
//! dessen Kapazitaet die Partielaenge eines bestimmten Jahrgangs waere, brauchte fuer
//! jeden anderen eine andere Uebersetzung -- ein Jahrgang mit fuenfundzwanzig
//! Stuetzstellen ist nach T40 zulaessig und liefe in einen Abbruch.
//!
//! Die Kapazitaet folgt stattdessen aus der Wand, die T40 selbst zieht:
//! `PARTIELAENGE_HOECHSTENS`. Der Verlauf traegt damit die Ketten **jeder** Partie, die
//! der Jahrgangsbau ueberhaupt zulaesst, und keine Runde mehr -- eine weitere koennte
//! kein zulaessiger Jahrgang fuellen. Die Kapazitaet ist eine Eigenschaft der Wand und
//! nicht des Jahrgangs: Sie aendert sich, wenn T40 seine Schranke verschiebt, und sonst
//! nie. Die Runde null hat keine Kette, weil vor der ersten Runde nichts geschrieben
//! wurde; die Ketten ab der Runde eins sind genau die einer vollen Partie.
//!
//! Der lange Lauf des Bruchtesters -- 200 Runden ohne Spieler -- ist bewusst **nicht**
//! die Bezugsgroesse, und er ist auch keine Partie: Er prueft nach `spiel.md`, ob eine
//! Groesse ihren Wertebereich verlaesst, und laeuft dafuer um ein Vielfaches ueber jede
//! nach T40 zulaessige Partielaenge hinaus. Er ist zugleich der Fall, den T19 selbst als
//! kettenfrei ausweist: Wer nur Ergebnisse zaehlt, wirft die Ketten weg und braucht
//! keinen Verlauf. Wer ihn trotzdem einen fuehren laesst, bekommt einen Abbruch, der die
//! Schranke nennt -- und nicht ein Achtel eines Laufs, dem man das Fehlende nicht ansieht.
//!
//! **Beide Grenzen brechen hart ab.** Das ist die eine Zusage dieses Kastens, und sie
//! ist der Grund, aus dem T19 geschrieben wurde: Eine gekuerzte Kette waere eine Luege
//! gegenueber dem Kaeufer. Ein Verlauf, der die ueberzaehlige Kette wegwirft und
//! trotzdem gruen zurueckkehrt, ist von einem vollstaendigen durch keine Messung zu
//! unterscheiden.
//!
//! ## Die Groesse des Behaelters
//!
//! Ein Verlauf traegt `RUNDEN_KAPAZITAET` Ketten zu je 310 Ursachensaetzen -- feste
//! Groesse, keine Zuteilung, wie jeder Behaelter des Kerns. Die Schranken darauf stehen
//! unten als Zusicherungen ueber die Typgroesse und nicht als Kommentar: Wer eine der
//! beiden Kapazitaeten hochsetzt oder die Wand verschiebt, ohne die Folge zu bedenken,
//! bekommt einen roten Bau. Es sind **zwei** Schranken, und sie fangen zwei
//! verschiedene Regler.
//!
//! **Die erste ist aus der Wand gebildet und nicht aus einer runden Bytezahl.** Eine
//! Zusicherung bei einem halben Megabyte liesse dreissig Runden durch; sie griffe damit
//! erst weit oberhalb des Bereichs, den sie sichern soll, und ruehrte sich bei keiner
//! Aenderung, die jemand tatsaechlich vornimmt. An `PARTIELAENGE_HOECHSTENS` gebunden
//! reisst sie beim ersten Wert oberhalb der Wand.
//!
//! **Die zweite haelt die Groesse gegen eine absolute Grenze**, und ohne sie waere die
//! erste keine Speicherschranke: Beide ihrer Seiten sind aus derselben Wand gebildet und
//! wachsen mit ihr. Wer die Wand verschiebt -- und T40 zieht sie aus der Ergebnisskala
//! von `spiel.md`, die sich schon einmal geaendert hat --, bekaeme sonst keinen roten
//! Bau, sondern still einen groesseren Behaelter. Gemessen am Stand `45fc32f` liefen
//! Wand und Kapazitaet gemeinsam bis zweitausendeinhundertneunundsechzig gruen durch,
//! bei 37.688.552 Byte.
//!
//! **Rot wird bei zweitausendeinhundertsiebzig die erste Schranke**, nicht die zweite.
//! Der Grund ist die Bauart: Neben den Ketten traegt ein Verlauf je Runde noch ihre
//! Rundennummer zu acht Byte, und die zehren den Vorsprung einer ganzen Kette langsam
//! auf. Die erste Schranke haelt genau, solange acht mal die Wand unter 17.360 Byte
//! bleibt -- eine Kette misst 17.368 Byte --, also bis
//! zweitausendeinhundertneunundsechzig und keine Runde weiter.
//!
//! **Woher die absolute Grenze kommt: aus dem, was ein Aufrufer traegt.** Jeder heutige
//! Aufrufer legt seinen Verlauf als oertliche Groesse an -- `verlauf_probe` an sieben
//! Stellen --, also ist der Platz, den er dafuer hat, der Stapel seines Fadens und nicht
//! der Freispeicher. Das ist `STAPEL_JE_FADEN` unten: eine gemessene Zahl, keine
//! gewaehlte.
//!
//! Der Abstand zwischen beiden Zahlen ist der Sinn der Schranke, und er gehoert
//! danebengeschrieben: Der Behaelter ist heute **451.784 Byte** gross, also gut ein
//! Zwanzigstel dessen, was ein Faden ueberhaupt an Stapel hat. Die Schranke reisst,
//! wenn die Wand von sechsundzwanzig auf 483 stiege; bei 482 ist der Behaelter
//! 8.375.240 Byte gross und geht gerade noch durch.
//!
//! **Und was die zweite Schranke nicht sagt**, damit sie niemand fuer mehr haelt: Ein
//! Stapelrahmen traegt mehr als den Verlauf. Wer die Wand bis dicht unter die Grenze
//! schoebe, bekaeme einen gruenen Bau und trotzdem einen Stapelueberlauf. Sie markiert
//! die Stelle, an der es **sicher** nicht mehr geht, nicht die, an der es bequem bleibt
//! -- eng gehalten wird der Behaelter von der ersten Schranke.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/schreiber.hpp"
#include "kern/zustand.hpp"

namespace kern::verlauf {

using schreiber::Kette;
using schreiber::Ursachensatz;
using zustand::i64;
using zustand::Index;

// ---------------------------------------------------------------------------
// Die beiden festen Kapazitaeten (T19) und die Wand, aus der die zweite folgt (T40)
// ---------------------------------------------------------------------------

/// Die laengste Partie, die der Jahrgangsbau nach T40 ueberhaupt zulaesst.
///
/// Das ist **nicht** die Partielaenge eines Jahrgangs, sondern die Wand darueber. T40
/// laesst den Jahrgangsbau oberhalb dieser Zahl abbrechen, weil die Ergebnisskala aus
/// `spiel.md` an einer Stelle ein echtes Literal traegt -- die Grenze, ab der die
/// Todesarten zaehlen. Eine Runde darueber fiele das obere Ende des einen Ergebnisbands
/// mit dem unteren Ende des anderen zusammen, und ein Wert truege zwei Bedeutungen; T40
/// rechnet das nach und zieht die Wand dort.
inline constexpr std::size_t PARTIELAENGE_HOECHSTENS = 26;

/// Wie viele Runden ein Verlauf aufnimmt.
///
/// Aus der Wand gebildet und nicht aus einem Jahrgang: So traegt derselbe Behaelter jede
/// Partie, die der Jahrgangsbau zulaesst, ohne dass eine Zahl des Codes an der geladenen
/// Zeitreihe haengt (T40).
inline constexpr std::size_t RUNDEN_KAPAZITAET = PARTIELAENGE_HOECHSTENS;

/// Wie viele Glieder die Kette **einer** Runde im Verlauf aufnimmt.
///
/// Abgeleitet und nicht abgeschrieben: Es ist dieselbe Zahl, die `kern::schreiber` fuer
/// die Kette einer Runde fuehrt. Zwei Zahlen fuer dieselbe Schranke koennten
/// auseinanderlaufen, und dann pruefte die eine Stelle etwas anderes als die andere.
inline constexpr std::size_t GLIEDER_JE_RUNDE = schreiber::KETTE_KAPAZITAET;

static_assert(GLIEDER_JE_RUNDE == zustand::FELDER,
              "T18: hoechstens ein Schreibzugriff je Adresse, also hoechstens 310 Glieder");

/// Die Antwort auf "diese Runde traegt der Verlauf nicht".
///
/// Sie liegt **ausserhalb** der Plaetze und nicht bei null -- derselbe Grund wie bei
/// `zustand::KEIN_PLATZ`: Ein Fehlerwert innerhalb des gueltigen Bereichs waere von einem
/// Fund nicht zu unterscheiden, und der Aufrufer, der die Pruefung vergisst, bekaeme
/// stillschweigend die erste Runde statt einer Absage.
inline constexpr std::size_t KEIN_RUNDENPLATZ = RUNDEN_KAPAZITAET;

static_assert(KEIN_RUNDENPLATZ >= RUNDEN_KAPAZITAET,
              "der Fehlerwert liegt ausserhalb der Plaetze, die ein Verlauf vergibt");

// ---------------------------------------------------------------------------
// Der Verlauf
// ---------------------------------------------------------------------------

/// Die Ketten einer Partie, Runde fuer Runde, in aufsteigender Rundenfolge.
///
/// **Zwei Wege hinein, eine Schranke.** `aufnehmen` nimmt eine ganze Rundenkette
/// entgegen -- das ist der Weg, den eine Sitzung mit dem `Rundenergebnis` in der Hand
/// nimmt. `beginne_runde` und `anhaengen` sind derselbe Weg in Einzelschritten, fuer
/// einen Aufrufer, der die Glieder erzeugt, waehrend die Runde laeuft. `aufnehmen`
/// laeuft ueber die beiden anderen und nicht daneben: Die Kapazitaetspruefung liegt
/// damit an genau einer Stelle, und kein Weg kommt an ihr vorbei.
///
/// **Die Runden steigen streng an** (T9). Eine Runde, die nicht groesser ist als die
/// zuletzt aufgenommene, ist ein harter Fehler und kein Ueberschreiben: Zweimal
/// dieselbe Runde aufzunehmen hiesse, eine der beiden Ketten zu verlieren, und genau
/// dagegen ist T19 geschrieben. Rundennummern beginnen bei eins -- vor der ersten Runde
/// wurde nichts geschrieben, es gibt dort also keine Kette.
///
/// **Die zuletzt begonnene Runde bleibt offen.** Nach `aufnehmen` haengt ein weiteres
/// `anhaengen` an dieselbe Runde an; geschlossen wird eine Runde erst dadurch, dass die
/// naechste beginnt. Das ist gewollt: Dieser Kasten kennt kein Rundenende, das er
/// pruefen koennte -- die zweiseitige Maskenpruefung dazu gehoert `kern::schreiber`.
///
/// **Es gibt keinen Weg heraus ausser dem Lesen.** Kein Loeschen, kein Zuruecksetzen,
/// kein Ueberschreiben. Ein Verlauf, dessen Inhalt sich nachtraeglich aendern liesse,
/// waere als Nachweis wertlos.
class Verlauf {
public:
    /// Beginnt die Kette der Runde `runde`.
    ///
    /// Drei harte Fehler, in dieser Reihenfolge geprueft und jeder mit eigener Meldung:
    ///   * `runde` ist kleiner als eins -- eine Runde vor der ersten gibt es nicht.
    ///   * `runde` ist nicht groesser als die zuletzt begonnene.
    ///   * der Verlauf traegt bereits `RUNDEN_KAPAZITAET` Runden.
    void beginne_runde(i64 runde);

    /// Haengt ein Glied an die zuletzt begonnene Runde.
    ///
    /// Zwei harte Fehler:
    ///   * es ist noch keine Runde begonnen;
    ///   * die Runde traegt bereits `GLIEDER_JE_RUNDE` Glieder. Die Meldung nennt die
    ///     Rundennummer und die Kapazitaet, denn ohne beides sagt sie dem Aufrufer
    ///     nicht, welche Kette wie weit gefuellt war.
    void anhaengen(const Ursachensatz& satz);

    /// Nimmt die Kette einer ganzen Runde auf -- `beginne_runde` und danach jedes Glied
    /// in der Reihenfolge, in der es in der Kette steht.
    void aufnehmen(i64 runde, const Kette& rundenkette);

    /// Wie viele Runden der Verlauf traegt.
    [[nodiscard]] std::size_t runden() const noexcept { return runden_; }

    /// Die Rundennummer der `nummer`-ten aufgenommenen Runde, ab null gezaehlt.
    /// Ein Platz ausserhalb bricht ab.
    [[nodiscard]] i64 rundennummer(std::size_t nummer) const;

    /// Die Kette der `nummer`-ten aufgenommenen Runde, ab null gezaehlt.
    /// Ein Platz ausserhalb bricht ab.
    [[nodiscard]] const Kette& kette(std::size_t nummer) const;

    /// Die Kette der Runde `runde`, nach ihrer Rundennummer gesucht.
    ///
    /// Eine Runde, die der Verlauf nicht traegt, bricht ab -- kein Ersatzwert und keine
    /// leere Kette, die wie eine Runde ohne Schreibzugriffe aussaehe.
    [[nodiscard]] const Kette& kette_der_runde(i64 runde) const;

    /// Der Platz der Runde `runde`, oder `KEIN_RUNDENPLATZ`, wenn der Verlauf sie nicht
    /// traegt.
    ///
    /// Die Frage neben `kette_der_runde`, das abbricht: Wer sie **stellen** will, statt
    /// sie am Abbruch zu erfahren, braucht eine Antwort ohne Ausnahme. Die
    /// Unterschiedsebene aus T20 ist genau dieser Aufrufer -- eine geaenderte Adresse
    /// ohne Ursachensatz ist dort ein Befund und kein Absturz.
    [[nodiscard]] std::size_t platz_der_runde(i64 runde) const noexcept;

    /// Wie viele Glieder der Verlauf ueber alle Runden traegt.
    [[nodiscard]] std::size_t glieder() const noexcept;

private:
    std::array<Kette, RUNDEN_KAPAZITAET> kette_{};
    std::array<i64, RUNDEN_KAPAZITAET> nummer_{};
    std::size_t runden_ = 0;
};

// ---------------------------------------------------------------------------
// Die Groesse des Behaelters -- an der Wand und am Stapel gehalten
// ---------------------------------------------------------------------------

/// Der Stapel, den das Betriebssystem einem Faden voreingestellt gibt.
///
/// **Gemessen, nicht gewaehlt.** `ulimit -s` meldet auf der Baumaschine 8192, also
/// Kibibyte, und `getrlimit(RLIMIT_STACK)` denselben Wert als 8.388.608 Byte
/// (2026-09-06, Ubuntu, glibc). Es ist die Voreinstellung von Linux und glibc und keine
/// Einstellung dieses Vorhabens; deshalb steht die Zahl hier als Kibibyte mal 1024 und
/// nicht als runde Bytezahl -- so ist ihre Herkunft am Ausdruck ablesbar.
inline constexpr std::size_t STAPEL_JE_FADEN = 8192u * 1024u;

// Die Groesse ist eine Folge der beiden Kapazitaeten und keine eigene Entscheidung --
// die drei Zusicherungen stehen hier, damit ein Heraufsetzen nicht unbemerkt ein
// Vielfaches daraus macht. Die ersten beiden binden die Groesse an die Wand, die dritte
// an das, was ein Aufrufer traegt: Ohne sie waechst der Behaelter mit der Wand mit, ohne
// dass eine Zusicherung sich ruehrt. Ein Verlauf gehoert schon bei seiner heutigen
// Groesse nicht beilaeufig auf einen Stapelrahmen -- er belegt dort gut ein Zwanzigstel
// dessen, was ein Faden ueberhaupt hat.
static_assert(sizeof(Verlauf) >= RUNDEN_KAPAZITAET * sizeof(Kette),
              "der Verlauf traegt seine Ketten selbst und nicht hinter einem Zeiger");
static_assert(sizeof(Verlauf) < (PARTIELAENGE_HOECHSTENS + 1) * sizeof(Kette),
              "T40: ein Verlauf traegt hoechstens die Runden der laengsten zulaessigen "
              "Partie, und eine weitere passt nicht mehr hinein");
static_assert(sizeof(Verlauf) < STAPEL_JE_FADEN,
              "T19: ein Verlauf ist groesser als der Stapel eines Fadens (8.388.608 "
              "Byte) und damit groesser, als ein Aufrufer ihn tragen kann -- die Wand "
              "aus T40 oder die Kapazitaet je Runde wurde heraufgesetzt");

// ---------------------------------------------------------------------------
// T20 -- die Rueckwaertsaufloesung ueber mehrere Runden
// ---------------------------------------------------------------------------

/// Warum eine rueckwaerts aufgeloeste Kette endet.
///
/// Fuenf Enden und kein sechstes. Die ersten drei sind Aussagen der Ursachenform selbst,
/// die letzten beiden Aussagen ueber den Verlauf:
///
///   `Ausloeser`       Aktion oder Gegenkraft -- das Ende, das T20 beim Namen nennt;
///   `Jahrgang`        der Wert kommt aus den Sollreihen und nicht aus einer Adresse;
///   `OhneAdresse`     die Form nennt einen Sektor und keine Adresse (Marktraeumung);
///   `OhneVorgaenger`  vor der Ursache hoert der Verlauf auf. Vor seiner ersten
///                     aufgenommenen Runde steht der Startwert, und der hat nach T18
///                     ausdruecklich keinen Ursachensatz;
///   `OhneEintrag`     schon der Anfangspunkt fehlt -- zu dieser Adresse traegt der
///                     Verlauf in jener Runde keinen Schreibzugriff.
///
/// Das letzte ist der Fall, den die Unterschiedsebene benennen koennen muss: eine
/// geaenderte Groesse ohne Ursache ist ein Befund und kein Absturz.
enum class Ende : std::uint8_t {
    Ausloeser      = 0,
    Jahrgang       = 1,
    OhneAdresse    = 2,
    OhneVorgaenger = 3,
    OhneEintrag    = 4,
};

/// Wie viele Enden es gibt -- die Zahl, gegen die eine Beschriftungstabelle sich haelt.
inline constexpr std::size_t ENDEN = 5;

/// Die Rueckwaertsaufloesung aus T20: von einem Schreibzugriff zu seiner Ursache und von
/// dort weiter, bis zur ausloesenden Aktion oder Gegenkraft.
///
/// **Sie zeigt in den Verlauf, sie kopiert ihn nicht.** Eine Kette als Wert waere hier
/// ein Behaelter fuer den denkbar laengsten Fall -- RUNDEN_KAPAZITAET mal
/// GLIEDER_JE_RUNDE Glieder --, also ein halbes Megabyte fuer eine Kette, die in der
/// Regel drei Glieder hat. Dieser Kasten haelt stattdessen einen Platz und geht ihn
/// zurueck; er ist ein paar Worte gross und lebt kuerzer als der Verlauf, in den er zeigt.
///
/// ## Die eine Regel, nach der ein Schritt geht
///
/// Der Vorgaenger eines Gliedes ist der **juengste** Schreibzugriff auf die
/// Ursachenadresse, der im Verlauf **vor** diesem Glied liegt und in keiner spaeteren
/// Runde steht als `runde` minus `verzoegerung`.
///
/// Sie deckt alle sechs Formen aus T18, weil die Frage nach der Ursachenadresse jede von
/// ihnen beantwortet: `Vortrag` nennt sie unmittelbar, `Instrument` den Stand des
/// genannten Politikinstruments. `Aktion` und `Gegenkraft` nennen keine -- das ist das
/// Ende, das T20 meint. `Jahrgang` nennt keine, weil der Wert aus den Sollreihen kommt,
/// und `Marktraeumung` nennt einen Sektor.
///
/// **Warum die Verzoegerung die Suche begrenzt, statt sie zu steuern.** Ein Vortrag auf
/// die eigene Adresse traegt nach T18 die Verzoegerung null: Er sagt "in dieser Runde
/// vollstaendig erklaert", nicht "in dieser Runde entstanden". Wer die Runde der Ursache
/// aus `runde` minus `verzoegerung` **ausrechnete**, landete auf dem Glied, von dem er
/// kommt, und stuende still -- und im `weltlauf`, wo jede der 175 Adressen so
/// geschrieben wird, waere das jede Kette. Wer stattdessen zurueck sucht, findet den
/// Schreibzugriff der Vorrunde. Genau das ist die Aufloesung ueber mehrere Runden, die
/// T20 verlangt, und nicht die einer einzelnen.
///
/// ## Sie endet immer, und dafuer braucht sie keine Laengenschranke
///
/// Jeder Schritt geht auf einen echt frueheren Platz -- erst innerhalb der Kette, dann in
/// eine frueher aufgenommene Runde --, und davon gibt es endlich viele. Eine
/// Laengenschranke daneben waere ein Zweig, den keine Probe erreichen kann, solange die
/// Ordnung des Verlaufs gilt; und gilt sie nicht mehr, ist die Schranke die falsche
/// Stelle, es zu bemerken.
class Aufloesung {
public:
    /// Beginnt beim Schreibzugriff auf `ziel` in der Runde `runde`.
    ///
    /// **Kein Abbruch, wenn es ihn nicht gibt.** Traegt der Verlauf die Runde nicht oder
    /// wurde `ziel` in ihr nicht geschrieben, ist die Aufloesung `leer` und beendet, mit
    /// dem Ende `OhneEintrag`.
    Aufloesung(const Verlauf& verlauf, i64 runde, Index ziel);

    /// Ob es zum Anfangspunkt ueberhaupt einen Ursachensatz gibt.
    [[nodiscard]] bool leer() const noexcept { return leer_; }

    /// Ob die Kette hier endet -- nach dem Anlegen wahr, sobald sie leer ist.
    [[nodiscard]] bool beendet() const noexcept { return beendet_; }

    /// Das Glied, auf dem die Aufloesung steht. Bricht auf einer leeren ab.
    [[nodiscard]] const Ursachensatz& glied() const;

    /// Wie viele Glieder besucht wurden -- eins nach dem Anlegen, sofern nicht leer.
    [[nodiscard]] std::size_t glieder() const noexcept { return glieder_; }

    /// Warum die Kette endet. Bricht ab, solange sie nicht beendet ist: Ein Ende, das
    /// noch nicht feststeht, waere eine Auskunft, die spaeter anders ausfaellt.
    [[nodiscard]] Ende ende() const;

    /// Einen Schritt rueckwaerts. `false` heisst: hier endet die Kette, und `ende` sagt
    /// warum. Ein weiterer Aufruf danach bleibt bei `false` und aendert nichts.
    bool weiter();

private:
    const Verlauf& verlauf_;
    std::size_t    rundenplatz_ = 0;
    std::size_t    gliedplatz_  = 0;
    std::size_t    glieder_     = 0;
    bool           leer_        = true;
    bool           beendet_     = true;
    Ende           ende_        = Ende::OhneEintrag;
};

}  // namespace kern::verlauf
