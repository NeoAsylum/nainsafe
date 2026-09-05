// Die Positivprobe zu den drei Negativproben: Dieselbe Einbindung, derselbe
// Sprachstand, ein **erlaubter** Zugriff. Sie muss uebersetzen. Ohne sie waere
// "drei Uebersetzungsfehler" auch mit einem Kopf vereinbar, der gar nicht uebersetzt.
#include "kern/zustand.hpp"

int main()
{
    kern::zustand::Zustand       z;
    kern::zustand::Startbelegung s{z};
    s.setze(0, 42);
    return static_cast<int>(z.lies(0));
}
