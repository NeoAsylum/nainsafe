//! Pruefsumme -- die Zahlenproben gegen veroeffentlichte Testvektoren.
//!
//! Das Rechenwerk steht in `include/kern/pruefsumme.hpp`, weil es `constexpr` sein
//! muss. Hier steht, was nicht in einen Kopf gehoert: die Proben.
//!
//! **Die Proben sind `static_assert`, und das ist der Punkt.** Sie laufen beim
//! Uebersetzen, nicht beim Testen. Eine verfehlte Konstante oder zwei vertauschte
//! Zeilen im Verfahren sind damit kein roter Test, den jemand lesen muss, sondern
//! eine Datei, die sich nicht uebersetzen laesst -- und `baulauf.py` legt das Urteil
//! des Uebersetzers ungefiltert als Befund ab. Dieselbe Bauart wie in
//! `src/festkomma.cpp`. Was ein `static_assert` nicht kann -- unter den Sanitizern
//! laufen --, steht in `test/pruefsumme_probe.cpp`.
//!
//! ## Warum hier nur fremde Zahlen stehen
//!
//! **Jeder Erwartungswert in dieser Datei stammt aus einer Veroeffentlichung, keiner
//! aus diesem Programm.** Ein selbst erzeugter Erwartungswert pruefte nur, dass der
//! Code heute dasselbe tut wie gestern -- er kann nicht zeigen, dass er FNV-1a-64
//! rechnet und nicht irgendetwas anderes, das sich reproduzierbar irrt. Genau das ist
//! der Unterschied, auf den es ankommt: Die Summe ist die Waehrung der
//! Regressionstests, also darf ihre Richtigkeit nicht aus den Regressionstests
//! stammen.
//!
//! Die drei Quellen, alle am 2026-09-02 abgerufen:
//!
//!   [RFC 9923]  Eastlake, D., Hansen, T., Noll, L.C., „The FNV Non-Cryptographic
//!               Hash Algorithm", RFC 9923. Abschnitt 2 nennt die Rechenvorschrift,
//!               Abschnitt 5 die Konstanten.
//!               https://www.rfc-editor.org/rfc/rfc9923.txt
//!   [TESTVEK]   Noll, L.C., `test_fnv.c` -- das Pruefprogramm der Urfassung, mit der
//!               Tabelle `fnv1a_64_test_vector` und der Zeichenkettenliste
//!               `fnv_test_str`.
//!               https://raw.githubusercontent.com/lcn2/fnv/master/test_fnv.c
//!   [FNV]       Noll, L.C., „FNV Hash".
//!               http://www.isthe.com/chongo/tech/comp/fnv/index.html
//!
//! **Zwei Lesarten in [TESTVEK], die man kennen muss, sonst vergleicht man falsch.**
//! Die Liste `fnv_test_str` wird ueber zwei Makros gefuellt: `TEST(x)` nimmt
//! `sizeof(x)-1` Oktette, also den Text **ohne** abschliessendes Nullbyte; `TEST0(x)`
//! nimmt `sizeof(x)`, also **mit**. Beide Sorten kommen unten vor und sind getrennt
//! ausgewiesen -- ein Vektor der einen Sorte gegen eine Funktion der anderen gehalten
//! ergaebt einen Fehlschlag, der wie ein Fehler im Verfahren aussieht und keiner ist.

#include <array>
#include <cstdint>

#include "kern/pruefsumme.hpp"

#include "kern/sperre.hpp"   // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::pruefsumme {

// ---------------------------------------------------------------------------
// Probe 1 -- die beiden Verfahrenskonstanten gegen ihre Quelle (Abnahme 2)
// ---------------------------------------------------------------------------
//
// Das Arbeitspaket verlangt die Konstanten im Klartext, und im Klartext stehen sie
// in `pruefsumme.hpp` -- dezimal, so wie die Vorgabe sie nennt. Eine dezimal
// geschriebene 20-stellige Zahl ist allerdings genau die Sorte Wert, bei der ein
// vertippter Ziffernblock beim Lesen nicht auffaellt und danach in jeder je
// gerechneten Summe steckt.
//
// Deshalb wird sie hier nicht geglaubt, sondern gegen die **zweite Schreibweise
// derselben Veroeffentlichung** gehalten. [RFC 9923], Abschnitt 5, nennt jede der
// beiden Konstanten doppelt: dezimal und hexadezimal, den Faktor zusaetzlich als
// Bildungsvorschrift. Stimmen die Schreibweisen ueberein, ist ein Tippfehler
// ausgeschlossen -- er muesste in beiden Formen derselbe sein.

static_assert(FNV_OFFSET_BASIS_64 == 0xcbf29ce484222325ULL,
              "[RFC 9923] Abschnitt 5: dezimal 14,695,981,039,346,656,037, "
              "hexadezimal 0xCBF29CE4 84222325");

static_assert(FNV_PRIME_64 == 0x00000100000001b3ULL,
              "[RFC 9923] Abschnitt 5: dezimal 1,099,511,628,211, "
              "hexadezimal 0x00000100 000001B3");

static_assert(FNV_PRIME_64 == (1ULL << 40) + (1ULL << 8) + 0xb3ULL,
              "[RFC 9923] Abschnitt 5: Bildungsvorschrift 2^40 + 2^8 + 0xB3");

// ---------------------------------------------------------------------------
// Probe 2 -- veroeffentlichte Testvektoren, Sorte `TEST` (Abnahme 1)
// ---------------------------------------------------------------------------
//
// Aus [TESTVEK], Tabelle `fnv1a_64_test_vector`, gelesen ueber die Liste
// `fnv_test_str`. Sorte `TEST(x)`, also **ohne** abschliessendes Nullbyte -- und
// genau das ist es, was `fnv1a64_text` ueber einen `std::string_view` rechnet.
//
// Die leere Eingabe ist der vom Arbeitspaket ausdruecklich verlangte Vektor. Sie
// prueft fuer sich genommen wenig -- jede Umsetzung, die den Startwert richtig setzt
// und die Schleife nie betritt, besteht sie --, und deshalb steht sie hier nicht
// allein.
//
// **Was die Kette f -> fo -> foo -> foob -> fooba -> foobar zusaetzlich leistet:**
// Sechs Werte derselben Quelle, jeder um genau ein Oktett laenger als der
// vorhergehende. Sie treffen alle sechs nur dann, wenn der Uebergang von einem Stand
// zum naechsten stimmt -- also die Reihenfolge der beiden Schritte (erst verodern,
// dann multiplizieren, [RFC 9923] Abschnitt 2), der Faktor und der Umbruch `mod
// 2**64`. FNV-1, das dieselben zwei Konstanten benutzt und nur die Schritte tauscht,
// erfuellt ab dem ersten Oktett keinen dieser Werte. Damit belegt die Kette die
// Rechenvorschrift und nicht nur die Konstanten.

static_assert(fnv1a64_text("") == 0xcbf29ce484222325ULL,
              "[TESTVEK] fnv_test_str[0] = TEST(\"\")");
static_assert(fnv1a64_text("") == FNV_OFFSET_BASIS_64,
              "die leere Eingabe ist der Startwert -- keine Runde, keine Aenderung");

static_assert(fnv1a64_text("a") == 0xaf63dc4c8601ec8cULL,
              "[TESTVEK] fnv_test_str[1] = TEST(\"a\")");
static_assert(fnv1a64_text("b") == 0xaf63df4c8601f1a5ULL,
              "[TESTVEK] fnv_test_str[2] = TEST(\"b\")");
static_assert(fnv1a64_text("c") == 0xaf63de4c8601eff2ULL,
              "[TESTVEK] fnv_test_str[3] = TEST(\"c\")");
static_assert(fnv1a64_text("d") == 0xaf63d94c8601e773ULL,
              "[TESTVEK] fnv_test_str[4] = TEST(\"d\")");
static_assert(fnv1a64_text("e") == 0xaf63d84c8601e5c0ULL,
              "[TESTVEK] fnv_test_str[5] = TEST(\"e\")");

static_assert(fnv1a64_text("f") == 0xaf63db4c8601ead9ULL,
              "[TESTVEK] fnv_test_str[6] = TEST(\"f\")");
static_assert(fnv1a64_text("fo") == 0x08985907b541d342ULL,
              "[TESTVEK] fnv_test_str[7] = TEST(\"fo\")");
static_assert(fnv1a64_text("foo") == 0xdcb27518fed9d577ULL,
              "[TESTVEK] fnv_test_str[8] = TEST(\"foo\")");
static_assert(fnv1a64_text("foob") == 0xdd120e790c2512afULL,
              "[TESTVEK] fnv_test_str[9] = TEST(\"foob\")");
static_assert(fnv1a64_text("fooba") == 0xcac165afa2fef40aULL,
              "[TESTVEK] fnv_test_str[10] = TEST(\"fooba\")");
static_assert(fnv1a64_text("foobar") == 0x85944171f73967e8ULL,
              "[TESTVEK] fnv_test_str[11] = TEST(\"foobar\")");

// ---------------------------------------------------------------------------
// Probe 3 -- dieselben Vektoren ueber die Byte-Schnittstelle, Sorte `TEST0`
// ---------------------------------------------------------------------------
//
// Probe 2 laeuft ueber `fnv1a64_text`. Der Kern rechnet spaeter aber nicht ueber
// Text, sondern ueber Bytes -- Paket 0008 schiebt Feld fuer Feld hinein. Also muss
// auch dieser Weg gegen veroeffentlichte Werte stehen, sonst ist der eine Weg belegt
// und der andere, der gebraucht wird, nur behauptet.
//
// Genommen sind die Vektoren der Sorte `TEST0(x)` aus [TESTVEK], die das
// abschliessende Nullbyte mitzaehlen. Das trifft sich gut: Ein Nullbyte laesst sich
// als Text nicht sauber uebergeben, als Oktett dagegen ohne Weiteres -- die beiden
// Sorten pruefen damit zwangslaeufig die beiden Schnittstellen.

/// [TESTVEK] fnv_test_str[12] = TEST0(""), also ein einzelnes Nullbyte.
constexpr std::array<std::uint8_t, 1> NUL_ALLEIN = {0x00};

/// [TESTVEK] fnv_test_str[1] = TEST("a"), hier als das Oktett 0x61 geschrieben.
constexpr std::array<std::uint8_t, 1> A_ALLEIN = {0x61};

/// [TESTVEK] fnv_test_str[13] = TEST0("a"), also 'a' und danach ein Nullbyte.
constexpr std::array<std::uint8_t, 2> A_DANN_NUL = {0x61, 0x00};

static_assert(fnv1a64(NUL_ALLEIN) == 0xaf63bd4c8601b7dfULL,
              "[TESTVEK] fnv_test_str[12] = TEST0(\"\") -- ein Nullbyte");
static_assert(fnv1a64(A_DANN_NUL) == 0x089be207b544f1e4ULL,
              "[TESTVEK] fnv_test_str[13] = TEST0(\"a\") -- 'a', dann ein Nullbyte");

// Beide Wege muessen ueber denselben Oktetten dasselbe rechnen, sonst waere
// `nimm_text` eine zweite Rechnung statt einer Schreibweise fuer `nimm_bytes`.
constexpr std::array<std::uint8_t, 6> FOOBAR_ALS_BYTES = {0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72};
static_assert(fnv1a64(FOOBAR_ALS_BYTES) == fnv1a64_text("foobar"),
              "Text- und Byteweg rechnen ueber denselben Oktetten dasselbe");
static_assert(fnv1a64(FOOBAR_ALS_BYTES) == 0x85944171f73967e8ULL,
              "[TESTVEK] fnv_test_str[11], hier oktettweise geschrieben");

// ---------------------------------------------------------------------------
// Probe 4 -- Little-Endian ohne Speicherzugriff (Abnahme 3)
// ---------------------------------------------------------------------------
//
// Die Zerlegung steht in `pruefsumme.hpp` als Schiebefolge. Hier stehen die Bytes,
// die dabei herauskommen muessen, ausgeschrieben -- die beiden vom Arbeitspaket
// genannten Faelle zuerst.
//
// `-1` ist der Fall, der die Wertumrechnung nach `std::uint64_t` traegt: Acht mal
// `FF` kommt nur heraus, wenn die negative Zahl als Zweierkomplementmuster gelesen
// und danach vorzeichenlos geschoben wird. Ein Schieben auf der vorzeichenbehafteten
// Zahl zoege das Vorzeichen nach und lieferte fuer die oberen Bytes ebenfalls `FF` --
// deshalb steht `I64_MIN` daneben, wo sich beide Wege unterscheiden.

static_assert(nach_bytes_le(1) == std::array<std::uint8_t, 8>{0x01, 0, 0, 0, 0, 0, 0, 0},
              "1 -> 01 00 00 00 00 00 00 00 (niederwertigstes Byte zuerst)");
static_assert(nach_bytes_le(-1) == std::array<std::uint8_t, 8>{0xFF, 0xFF, 0xFF, 0xFF,
                                                               0xFF, 0xFF, 0xFF, 0xFF},
              "-1 -> acht mal FF (Zweierkomplement, vorzeichenlos geschoben)");

static_assert(nach_bytes_le(0) == std::array<std::uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0},
              "null ist acht Nullbytes");

// Der aussagekraeftigste Fall: acht verschiedene Bytes. Er zeigt die Reihenfolge
// vollstaendig, statt sie an einer Zahl mit lauter gleichen Bytes zu behaupten.
static_assert(nach_bytes_le(0x0102030405060708) ==
                  std::array<std::uint8_t, 8>{0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01},
              "0x0102030405060708 -> 08 07 06 05 04 03 02 01, genau umgekehrt");

// Die Raender von i64. Bei `I64_MIN` ist genau ein Bit gesetzt, das hoechstwertige --
// es muss im **letzten** Byte landen und in keinem anderen.
static_assert(nach_bytes_le(9'223'372'036'854'775'807) ==
                  std::array<std::uint8_t, 8>{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F},
              "I64_MAX -> sieben mal FF, dann 7F");
static_assert(nach_bytes_le(-9'223'372'036'854'775'807 - 1) ==
                  std::array<std::uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0x80},
              "I64_MIN -> sieben Nullbytes, dann 80");

// Und der Weg ueber die Kette muss derselbe sein wie der ueber die Bytes -- sonst
// haette Paket 0008 zwei Ergebnisse zur Auswahl.
constexpr std::array<std::uint8_t, 8> ZAHL_ALS_BYTES =
    {0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};

static_assert([] {
    Summe summe;
    summe.nimm_i64(0x0102030405060708);
    return summe.wert();
}() == fnv1a64(ZAHL_ALS_BYTES),
              "nimm_i64 ist nimm_bytes ueber nach_bytes_le, nicht eine zweite Rechnung");

// ---------------------------------------------------------------------------
// Probe 5 -- die Summe haengt an der Reihenfolge (Abnahme 4)
// ---------------------------------------------------------------------------
//
// **Der Fehler, gegen den diese Probe steht.** Eine Summe, die versehentlich ueber
// eine *Menge* statt ueber eine *Folge* liefe -- etwa, weil jemand die Felder aus
// einer streuenden Ablage zieht oder die Bytes vor dem Rechnen sortiert --, faende
// jeden der Vektoren aus Probe 2 und 3 trotzdem: Deren Eingaben sind so kurz, dass
// die Reihenfolge kaum auffaellt, und `foobar` hat man dann eben in der Reihenfolge
// gefuettert, in der es dasteht. Der Ausfall zeigte sich erst am `Zustand` mit 310
// Feldern, also dort, wo T9 ihn ausschliesst und niemand mehr hinsieht.
//
// **Warum auch hier keine selbst erzeugte Zahl steht.** Der naheliegende Nachweis
// waere ein Paar wie `sum({61,00})` und `sum({00,61})`, beide als Zahl hingeschrieben.
// Die zweite dieser Zahlen ist aber nirgends veroeffentlicht -- sie kaeme aus diesem
// Programm, und dann pruefte die Probe sich selbst. Stattdessen steht die
// veroeffentlichte Zahl auf der einen Seite und die Ungleichheit auf der anderen.
// Das ist die schwaechere Behauptung und der staerkere Nachweis.

/// Dieselben zwei Oktette wie `A_DANN_NUL`, in der anderen Reihenfolge. Nicht in
/// [TESTVEK] enthalten -- deshalb steht darunter kein Gleichheits-, sondern ein
/// Ungleichheitsnachweis.
constexpr std::array<std::uint8_t, 2> NUL_DANN_A = {0x00, 0x61};

// Dass die beiden Folgen wirklich aus denselben Oktetten bestehen, ist an den beiden
// Einzeloktetten abzulesen -- und beide sind veroeffentlicht:
//   0x61 allein -> 0xaf63dc4c8601ec8c   [TESTVEK] fnv_test_str[1]
//   0x00 allein -> 0xaf63bd4c8601b7df   [TESTVEK] fnv_test_str[12]
static_assert(fnv1a64(A_ALLEIN) == 0xaf63dc4c8601ec8cULL,
              "das eine der beiden Oktette, veroeffentlicht");
static_assert(fnv1a64(NUL_ALLEIN) == 0xaf63bd4c8601b7dfULL,
              "das andere der beiden Oktette, veroeffentlicht");

static_assert(fnv1a64(A_DANN_NUL) == 0x089be207b544f1e4ULL,
              "61 00 -> 0x089be207b544f1e4, veroeffentlicht in [TESTVEK]");
static_assert(fnv1a64(NUL_DANN_A) != 0x089be207b544f1e4ULL,
              "00 61 -> nicht dieselbe Summe, obwohl dieselben zwei Oktette");
static_assert(fnv1a64(A_DANN_NUL) != fnv1a64(NUL_DANN_A),
              "Abnahme 4: dieselben Bytes, andere Reihenfolge, andere Summe");

// **Der zweite Nachweis, und er ist der schaerfere.** [FNV] nennt die kuerzeste
// bekannte Eingabe, deren FNV-1a-64-Summe glatt null ist:
//
//     „The only solution for length 8 is:  FNV64_1a(d5 6b b9 53 42 87 08 36) = 0"
//     (gefunden 2011-Oct-23, bestaetigt von Richard Heylen 2011-Dec-14)
//
// Acht Oktette, alle verschieden, und ein Ergebnis, das keine Umsetzung zufaellig
// trifft: Von 2^64 moeglichen Summen ist genau diese eine gemeint. Dieselben acht
// Oktette rueckwaerts ergeben sie nicht -- und das ist der Reihenfolgennachweis auf
// einer Laenge, bei der eine mengenartige Summe nicht mehr davonkommt.
constexpr std::array<std::uint8_t, 8> NULLSUMME_VORWAERTS =
    {0xd5, 0x6b, 0xb9, 0x53, 0x42, 0x87, 0x08, 0x36};

constexpr std::array<std::uint8_t, 8> NULLSUMME_RUECKWAERTS =
    {0x36, 0x08, 0x87, 0x42, 0x53, 0xb9, 0x6b, 0xd5};

static_assert(fnv1a64(NULLSUMME_VORWAERTS) == 0ULL,
              "[FNV]: FNV64_1a(d5 6b b9 53 42 87 08 36) = 0");
static_assert(fnv1a64(NULLSUMME_RUECKWAERTS) != 0ULL,
              "dieselben acht Oktette rueckwaerts sind nicht null");
static_assert(fnv1a64(NULLSUMME_VORWAERTS) != fnv1a64(NULLSUMME_RUECKWAERTS),
              "Abnahme 4, auf acht paarweise verschiedenen Oktetten");

// Und dasselbe eine Ebene hoeher, dort wo es Paket 0008 trifft: Zwei `i64`-Felder in
// getauschter Reihenfolge sind zwei verschiedene Zustaende und muessen zwei
// verschiedene Summen haben. Ohne diese Eigenschaft waere die feste Feldreihenfolge
// aus T12 eine Verabredung ohne Wirkung.
static_assert([] {
    Summe summe;
    summe.nimm_i64(1);
    summe.nimm_i64(2);
    return summe.wert();
}() != [] {
    Summe summe;
    summe.nimm_i64(2);
    summe.nimm_i64(1);
    return summe.wert();
}(), "zwei Felder in getauschter Reihenfolge -> verschiedene Summen");

}  // namespace kern::pruefsumme
