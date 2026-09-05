// Wegwerf-Uebersetzungseinheit des Kern-Pruefers, Paket 0046, 2026-09-03.
//
// Der Verstoss ist Absicht: `ungenutzt` ist eine ungenutzte Variable. Mit dem Warnsatz
// (`-Wall` plus `-Werror`) ist das ein Bauabbruch, ohne ihn uebersetzt dieselbe Datei
// gruen durch. Genau daran laesst sich messen, ob die Schalter angekommen sind -- ein
// gruener Bau allein belegt das nicht.
int fabrik_pruefer_probe()
{
    int ungenutzt = 7;
    return 0;
}
