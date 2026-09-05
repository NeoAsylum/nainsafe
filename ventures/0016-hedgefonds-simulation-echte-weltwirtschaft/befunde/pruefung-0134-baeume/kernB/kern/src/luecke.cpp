// Wegwerfquelle des Nachweises zu Paket 0134 -- gehoert nicht ins Repo.
#include <cstdint>

#include "kern/sperre.hpp"  // steht absichtlich NICHT an letzter Stelle

#include <cstdint>  // Wiedereinbindung, folgenlos -- und trotzdem der letzte #include

std::int64_t luecke_mitte(std::int64_t a);
std::int64_t luecke_mitte(std::int64_t a) {
  return a + static_cast<std::int64_t>(sizeof(std::size_t));
}
