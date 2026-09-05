//! Wegwerfprobe der Messung zu Paket 0139 -- Verstoss gegen Bedingung 2.
//!
//! Sie bindet `kern/sperre.hpp`, aber nicht als letzten `#include`. Der Kopf danach
//! ist mit Absicht ein **bereits gebundener**: `#pragma once` macht die dritte Zeile
//! folgenlos, der Vorverarbeiter liest also keinen vergifteten Bezeichner nach.
//!
//! Nur so ist der Kontrollbaum gegen den Riegel vor Paket 0139 wirklich gruen. Ein
//! frischer Standardkopf an dieser Stelle zerbraeche an der Vergiftung, der Baum
//! wuerde aus dem falschen Grund rot -- und bewiese dann nichts ueber den Riegel.

#include "kern/festkomma.hpp"

#include "kern/sperre.hpp"

#include "kern/festkomma.hpp"

int main()
{
  return kern::festkomma::plus(1, 2) == 3 ? 0 : 1;
}
