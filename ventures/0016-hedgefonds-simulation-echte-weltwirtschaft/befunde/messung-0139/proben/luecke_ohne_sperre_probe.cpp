//! Wegwerfprobe der Messung zu Paket 0139 -- Verstoss gegen Bedingung 1.
//!
//! Sie bindet `kern/sperre.hpp` **nicht**. Gegen den Riegel vor Paket 0139 kommt sie
//! ohne jeden Eingriff durch, uebersetzt und laeuft gruen; gegen den Riegel dieses
//! Pakets bricht schon das Konfigurieren ab.
//!
//! Sie liegt hier und nicht in `kern/test`: Das Messskript legt sie in eine Abschrift
//! unter `$TMPDIR` und nie in den Baum.

#include "kern/festkomma.hpp"

int main()
{
  return kern::festkomma::plus(1, 2) == 3 ? 0 : 1;
}
