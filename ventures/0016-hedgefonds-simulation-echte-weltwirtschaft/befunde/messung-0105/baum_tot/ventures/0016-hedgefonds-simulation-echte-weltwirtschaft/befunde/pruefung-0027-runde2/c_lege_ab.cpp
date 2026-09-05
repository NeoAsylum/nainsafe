// Pruefstueck zu Abnahmebedingung 1: der neue rohe Schreibzugriff `lege_ab`.
// Nicht von der Bedingung verlangt -- geprueft, weil der Zugriff umbenannt statt
// entfernt wurde und der neue Name sonst ungeprueft bliebe.
#include "kern/zustand.hpp"

int main()
{
    kern::zustand::Zustand z;
    z.lege_ab(0, 1);
    return 0;
}
