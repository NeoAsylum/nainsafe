#pragma once
//! FNV-1a-64 und die Bytes, ueber die sie laeuft (T12).
//!
//! **Wofuer diese Summe gilt, und warum der Satz hier steht und nicht anderswo.**
//! Sie ist die Waehrung aller Regressionstests (T12): Zwei Laeufe gelten genau dann
//! als gleich, wenn diese Zahl gleich ist. Und sie steht in jedem Speicherstand
//! (T22) -- beim Laden wird die Partie nachgerechnet und die Summe verglichen, und
//! weicht sie ab, meldet das Programm einen Determinismusbruch, statt weiterzuspielen.
//!
//! **Daraus folgt eine Regel, die niemand findet, wenn sie nicht hier steht: Wer das
//! Verfahren wechselt, macht jeden gespeicherten Stand ungueltig und braucht einen
//! ADR.** Nicht die Zahlen aendern sich dann, sondern der gesamte Regressionsbestand
//! wird auf einen Schlag rot -- und zwar aus einem Grund, der nichts mit dem Spiel zu
//! tun hat. Betroffen ist alles zugleich: der Bestand, die Speicherstaende der
//! Kaeufer und jeder Befund, der eine Summe zitiert. Das ist keine Aenderung am
//! Rechenwerk, das ist ein Schnitt durch das Gedaechtnis des Vorhabens.
//!
//! ## Was hier steht und was nicht
//!
//! Zwei Dinge stecken in T12, und nur eines davon braucht den `Zustand`:
//!
//!   * **Die Summe und die Byte-Bausteine** -- FNV-1a-64 ueber eine Bytefolge, und
//!     die Zerlegung eines `i64` in acht Bytes in Little-Endian. Beides haengt an
//!     keinem Datentyp des Modells. Das ist diese Datei.
//!   * **Die feste Feldreihenfolge ueber die 310 Felder** -- die haengt am `Zustand`
//!     und gehoert Paket 0008. Dieses Modul kennt Bytes, nicht das Modell, und bindet
//!     `zustand.hpp` auch dann nicht ein, wenn es die Datei schon gibt.
//!
//! ## Die Vorschrift aus T12, die jede Zeile hier bestimmt
//!
//! *„`Zustand` wird ueber eine ausdruecklich geschriebene Funktion in Bytes gefasst
//! (feste Feldreihenfolge, `i64` in Little-Endian), **nie ueber die Speicheranordnung
//! der Struktur**."*
//!
//! Das Verbot ist der eigentliche Inhalt der Vorgabe. Ein Verfahren, das die Bytes
//! einer Struktur so nimmt, wie sie im Speicher liegen, liest drei Dinge mit, die
//! nirgends entschieden wurden: die Byte-Reihenfolge der Maschine, die Auffuellbytes
//! zwischen den Feldern und die Anordnung, die der Uebersetzer gewaehlt hat. Alle drei
//! duerfen sich aendern, ohne dass sich am Modell etwas aendert -- und dann ist die
//! Summe verschieden, obwohl das Spiel dasselbe gerechnet hat. Genau das waere das
//! Ende der Regressionsfaehigkeit: rote Tests ohne Ursache im Modell.
//!
//! Deshalb steht die Zerlegung in `nach_bytes_le` als Schiebefolge da. Sie rechnet auf
//! dem **Wert**, nicht auf seinem Speicherbild, und liefert auf jeder Maschine
//! dieselben acht Bytes. Die drei naheliegenden Abkuerzungen -- das Speicherbild
//! blockweise kopieren, den Zeigertyp umdeuten oder zwei Typen ueber denselben
//! Speicher legen -- lesen samt und sonders die Speicheranordnung und sind genau das,
//! was T12 verbietet. Der Pruefer weist ihre Abwesenheit mit einem `grep` nach; sie
//! kommen in dieser Datei nicht vor, auch nicht als Wort in einem Kommentar.
//!
//! ## Ueberlauf ist hier Absicht, und zwar die des Standards
//!
//! Anders als im Rechenwerk (`festkomma.hpp`, T7: Ueberlauf ist ein Abbruch) **ist**
//! der Umbruch hier die Rechenvorschrift: FNV-1a multipliziert `mod 2**64`. Er laeuft
//! auf `std::uint64_t`, und fuer vorzeichenlose Ganzzahlen ist der Umbruch im
//! Standard definiert -- nicht durch `-fwrapv` und nicht durch eine Annahme ueber den
//! Uebersetzer. Das ist der Grund, warum diese Datei ohne den Ueberlaufwaechter
//! auskommt und trotzdem kein undefiniertes Verhalten enthaelt: Die Massnahmen aus
//! ADR 0011 sichern vorzeichenbehaftete Arithmetik ab, und hier ist keine.
//!
//! ## Quellen der beiden Verfahrenskonstanten und der Rechenvorschrift
//!
//!   [RFC 9923] Eastlake, D., Hansen, T., Noll, L.C., „The FNV Non-Cryptographic
//!              Hash Algorithm", RFC 9923, Abschnitt 2 (Rechenvorschrift) und
//!              Abschnitt 5 (Konstanten). https://www.rfc-editor.org/rfc/rfc9923.txt
//!              -- abgerufen am 2026-09-02.
//!   [FNV]      Noll, L.C., „FNV Hash".
//!              http://www.isthe.com/chongo/tech/comp/fnv/index.html
//!              -- abgerufen am 2026-09-02.

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>

namespace kern::pruefsumme {

using u64 = std::uint64_t;
using i64 = std::int64_t;

/// Der Startwert des Verfahrens („offset basis").
///
/// **Woher die Zahl stammt:** [RFC 9923], Abschnitt 5, nennt fuer 64 Bit die
/// Dezimalzahl „14,695,981,039,346,656,037" und daneben die Hexadezimalform
/// „0xCBF29CE4 84222325". Dieselbe Dezimalzahl steht auf der Seite des Verfassers
/// des Verfahrens, [FNV]. Beide am 2026-09-02 abgerufen.
///
/// Der Wert steht hier dezimal, weil die Vorgabe des Arbeitspakets ihn dezimal nennt.
/// Dass die Dezimalform und die Hexadezimalform derselben Veroeffentlichung wirklich
/// dieselbe Zahl sind, prueft `src/pruefsumme.cpp` beim Uebersetzen -- ein
/// vertippter Ziffernblock ist damit kein stiller Fehler in jeder je gerechneten
/// Summe, sondern eine Datei, die sich nicht uebersetzen laesst.
inline constexpr u64 FNV_OFFSET_BASIS_64 = 14695981039346656037ULL;

/// Der Faktor des Verfahrens („FNV prime").
///
/// **Woher die Zahl stammt:** [RFC 9923], Abschnitt 5, nennt fuer 64 Bit die
/// Dezimalzahl „1,099,511,628,211", die Bildungsvorschrift „2^40 + 2^8 + 0xB3" und
/// die Hexadezimalform „0x00000100 000001B3". Dieselbe Dezimalzahl steht in [FNV].
/// Beide am 2026-09-02 abgerufen.
///
/// Auch hier prueft `src/pruefsumme.cpp` die Dezimalzahl gegen die Bildungsvorschrift
/// derselben Quelle, statt sie zu glauben.
inline constexpr u64 FNV_PRIME_64 = 1099511628211ULL;

/// Ein `i64` wird zu genau so vielen Bytes. Die Zahl steht als Name da, weil sie an
/// zwei Stellen gebraucht wird und ein zweites Mal `8` nicht als dieselbe Groesse zu
/// erkennen waere.
inline constexpr std::size_t BYTES_JE_I64 = 8;

/// Ein `i64` als acht Bytes in Little-Endian -- auf jeder Maschine gleich (T12).
///
/// Little-Endian heisst: das niederwertigste Byte zuerst. `1` wird also zu
/// `01 00 00 00 00 00 00 00` und `-1` zu acht mal `FF`; beides steht als Probe in
/// `src/pruefsumme.cpp`.
///
/// **Der Schritt, der Erklaerung braucht, ist der erste.** Die Umdeutung nach
/// `std::uint64_t` ist eine Wertumrechnung und kein Blick in den Speicher: Der
/// Standard schreibt fuer sie seit C++20 das Ergebnis `wert mod 2**64` vor, und weil
/// vorzeichenbehaftete Zahlen seit C++20 Zweierkomplement sind, ist das genau das
/// erwartete Bitmuster -- fuer `-1` also durchweg Einsen. Dieselbe Zahl auf jedem
/// Uebersetzer und jeder Maschine, ohne Fallunterscheidung.
///
/// Der Grund fuer den Umweg ueber den vorzeichenlosen Typ ist das Schieben danach:
/// `>>` auf einer negativen Zahl zieht das Vorzeichen nach, `>>` auf einer
/// vorzeichenlosen schiebt Nullen nach. Nur die zweite Form legt die Bytes so frei,
/// wie sie in der Zahl stehen.
///
/// Ueber den Index gibt es nichts zu pruefen: Die Schleife laeuft gegen dieselbe
/// Konstante, die die Groesse des Feldes ist, und `i` waechst um eins.
[[nodiscard]] constexpr std::array<std::uint8_t, BYTES_JE_I64> nach_bytes_le(i64 zahl)
{
    const u64 muster = static_cast<u64>(zahl);

    std::array<std::uint8_t, BYTES_JE_I64> bytes{};
    for (std::size_t i = 0; i < BYTES_JE_I64; ++i) {
        bytes[i] = static_cast<std::uint8_t>((muster >> (8u * i)) & 0xFFu);
    }
    return bytes;
}

/// FNV-1a-64 als Kette: anfangen, fuettern, abschliessen.
///
/// **Warum die Kette und nicht nur ein Aufruf ueber eine fertige Bytefolge.** Paket
/// 0008 laeuft ueber 310 Felder. Mit der Kette schiebt es Feld fuer Feld hinein und
/// braucht nirgends einen Zwischenspeicher fuer die ganze Bytefolge; die Reihenfolge
/// der Aufrufe **ist** dann die feste Feldreihenfolge aus T12, und sie steht als
/// Programmtext da statt in einem Puffer. Wer die Bytes schon beisammen hat, nimmt
/// `fnv1a64` -- das ist dieselbe Rechnung in einer Zeile.
class Summe {
public:
    constexpr Summe() noexcept = default;

    /// Ein Byte, die Rechenvorschrift selbst.
    ///
    /// [RFC 9923], Abschnitt 2, schreibt sie so:
    ///
    ///     hash = offset_basis
    ///     for each octet_of_data to be hashed
    ///         hash = hash XOR octet_of_data
    ///         hash = hash * FNV_Prime mod 2**HashSize
    ///     return hash
    ///
    /// **Erst verodern, dann multiplizieren** -- das und nur das unterscheidet FNV-1a
    /// von FNV-1, das dieselben zwei Konstanten benutzt und die Schritte tauscht. Wer
    /// die beiden Zeilen vertauscht, bekommt kein kaputtes Programm, sondern ein
    /// anderes, ebenfalls gaengiges Verfahren mit anderen Summen -- deshalb liegt der
    /// Nachweis nicht im Lesen dieser Zeilen, sondern in den veroeffentlichten
    /// Testvektoren in `src/pruefsumme.cpp`, die FNV-1 nicht erfuellen wuerde.
    ///
    /// Das `mod 2**64` der Vorschrift ist das Verhalten von `std::uint64_t` und
    /// braucht keine eigene Zeile; siehe den Abschnitt zum Ueberlauf im Kopf.
    constexpr void nimm_byte(std::uint8_t byte) noexcept
    {
        wert_ ^= static_cast<u64>(byte);
        wert_ *= FNV_PRIME_64;
    }

    /// Mehrere Bytes, in der Reihenfolge, in der sie stehen.
    constexpr void nimm_bytes(std::span<const std::uint8_t> bytes) noexcept
    {
        for (const std::uint8_t byte : bytes) {
            nimm_byte(byte);
        }
    }

    /// Ein `i64` als seine acht Bytes in Little-Endian. Der Baustein, aus dem Paket
    /// 0008 die kanonische Byteform des `Zustand` zusammensetzt.
    constexpr void nimm_i64(i64 zahl) noexcept
    {
        nimm_bytes(nach_bytes_le(zahl));
    }

    /// Die Oktette eines Textes, ohne abschliessendes Nullbyte.
    ///
    /// Gebraucht wird das an zwei Stellen: fuer die veroeffentlichten Testvektoren,
    /// die Zeichenketten sind, und spaeter fuer benannte Kennungen, die T12 als Name
    /// und nicht als Zahl geschrieben haben will. Es ist keine zweite Rechnung,
    /// sondern `nimm_bytes` ueber die Oktette des Textes.
    ///
    /// Die Umdeutung `char` -> `std::uint8_t` ist wieder eine Wertumrechnung mit
    /// festgelegtem Ergebnis: Ob `char` auf dieser Maschine ein Vorzeichen hat,
    /// aendert das Byte nicht.
    constexpr void nimm_text(std::string_view text) noexcept
    {
        for (const char zeichen : text) {
            nimm_byte(static_cast<std::uint8_t>(zeichen));
        }
    }

    /// Der Stand nach allem, was bisher hineingegangen ist.
    [[nodiscard]] constexpr u64 wert() const noexcept { return wert_; }

private:
    u64 wert_ = FNV_OFFSET_BASIS_64;
};

/// FNV-1a-64 ueber eine fertige Bytefolge, in einem Aufruf.
[[nodiscard]] constexpr u64 fnv1a64(std::span<const std::uint8_t> bytes) noexcept
{
    Summe summe;
    summe.nimm_bytes(bytes);
    return summe.wert();
}

/// FNV-1a-64 ueber die Oktette eines Textes, ohne abschliessendes Nullbyte.
[[nodiscard]] constexpr u64 fnv1a64_text(std::string_view text) noexcept
{
    Summe summe;
    summe.nimm_text(text);
    return summe.wert();
}

}  // namespace kern::pruefsumme
