// Berichterstatter zu Paket 0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen:
// die Groesse des Behaelters aus demselben Kopf, den der Bau uebersetzt. Er linkt den
// Kern nicht -- `sizeof` braucht keine Definition der Mitgliedsfunktionen, nur die
// Felder. Er druckt zusaetzlich `sizeof(Kette)` und die Wand ab, damit an der Ausgabe
// selbst ablesbar ist, welcher Fall gerade uebersetzt wurde.
//
// Die Datei liegt unter befunde/ und nicht unter kern/: Sie ist kein Teil des Kerns,
// wird von keinem Sammler eingelesen und bindet deshalb auch kern/sperre.hpp nicht.
#include <cstdio>

#include "kern/verlauf.hpp"

int main()
{
    std::printf("%zu %zu %zu",
                sizeof(kern::verlauf::Verlauf),
                sizeof(kern::verlauf::Kette),
                kern::verlauf::PARTIELAENGE_HOECHSTENS);
    return 0;
}
