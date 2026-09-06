// Nur ein Berichterstatter zu Paket 0156: die Groesse des Behaelters aus demselben
// Kopf, den der Bau uebersetzt. Er linkt den Kern nicht -- sizeof braucht keine
// Definition der Mitgliedsfunktionen, nur die Felder.
//
// Die Datei liegt unter befunde/ und nicht unter kern/: Sie ist kein Teil des Kerns,
// wird von keinem Sammler eingelesen und bindet deshalb auch kern/sperre.hpp nicht.
#include <cstdio>

#include "kern/verlauf.hpp"

int main()
{
    std::printf("%zu", sizeof(kern::verlauf::Verlauf));
    return 0;
}
