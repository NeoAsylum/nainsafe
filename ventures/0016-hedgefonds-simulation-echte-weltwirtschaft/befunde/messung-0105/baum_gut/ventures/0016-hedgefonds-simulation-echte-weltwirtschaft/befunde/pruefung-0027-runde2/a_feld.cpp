// Pruefstueck zu Abnahmebedingung 1 von Paket 0027, Runde 2.
// Eine Uebersetzungseinheit, die **nur** kern/zustand.hpp einbindet und den direkten
// Feldzugriff versucht. Sie muss ein Uebersetzungsfehler sein.
#include "kern/zustand.hpp"

int main()
{
    kern::zustand::Zustand z;
    z.feld[0] = 1;
    return 0;
}
