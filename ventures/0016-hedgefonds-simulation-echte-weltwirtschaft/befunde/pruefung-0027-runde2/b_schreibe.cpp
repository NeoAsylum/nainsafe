// Pruefstueck zu Abnahmebedingung 1: der alte Schreibzugriff `schreibe`.
#include "kern/zustand.hpp"

int main()
{
    kern::zustand::Zustand z;
    z.schreibe(0, 1);
    return 0;
}
