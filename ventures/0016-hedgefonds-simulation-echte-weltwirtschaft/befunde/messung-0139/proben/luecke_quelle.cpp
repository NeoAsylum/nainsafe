//! Wegwerfquelle der Messung zu Paket 0139 -- Verstoss gegen Bedingung 1, aber auf
//! der Seite der Bibliothek statt der Proben.
//!
//! Sie belegt, dass der Riegel nach der Erweiterung die **Quellen** weiter faengt.
//! Den Kontrollbaum dazu -- derselbe Verstoss gegen den Riegel vor Paket 0134, gruen
//! -- hat 0134 gefahren; hier geht es nur darum, dass der Umbau der Schleife die
//! erste Haelfte nicht verloren hat.

#include "kern/festkomma.hpp"

namespace kern::messung0139 {

kern::festkomma::i64 verdoppeln(kern::festkomma::i64 wert);

kern::festkomma::i64 verdoppeln(kern::festkomma::i64 wert)
{
  return kern::festkomma::plus(wert, wert);
}

}  // namespace kern::messung0139
