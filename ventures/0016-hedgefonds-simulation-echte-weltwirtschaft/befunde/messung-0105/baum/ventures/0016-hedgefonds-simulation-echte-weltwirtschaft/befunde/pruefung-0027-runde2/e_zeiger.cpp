// Der Weg, den die Grep-Regel aus Bedingung 2 nicht sieht: Feldzugriff ueber einen
// Zeiger. Auch er muss ein Uebersetzungsfehler sein, sonst traegt Bedingung 1 nur
// gegen die Schreibweise und nicht gegen die Sache.
#include "kern/zustand.hpp"

int main()
{
    kern::zustand::Zustand  z;
    kern::zustand::Zustand* p = &z;
    p->feld[0]                = 1;
    return 0;
}
