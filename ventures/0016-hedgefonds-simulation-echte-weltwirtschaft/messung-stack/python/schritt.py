#!/usr/bin/env python3
"""Deterministischer Festkomma-Weltschritt -- Umsetzung in Python.

Vorgabe: ../AUFGABE.md. Kein Gleitkommatyp, keine Fremdbibliothek, keine
Argumente, keine Eingabe.

Pythons int ist beliebig genau. Das erfuellt die 128-Bit-Forderung an das
Zwischenprodukt von selbst, verlangt aber umgekehrt, den 64-Bit-Wertebereich
ausdruecklich herzustellen -- dafuer gibt es `umbruch64`.
"""

import time

GROESSE = 64
SCHRITTE = 1_000_000
NACHBAR_VERSATZ = 17
STREUER = 977
NENNER = 10_000
NACHBAR_TEILER = 1_024
EIGEN_TEILER = 4_096
UNTERGRENZE = 0
OBERGRENZE = 1_000_000_000_000
PRUEFSUMME_MOD = (1 << 63) - 1

_MASKE64 = (1 << 64) - 1
_VORZEICHENBIT64 = 1 << 63


def umbruch64(x):
    """Bildet x auf den Wertebereich eines vorzeichenbehafteten 64-Bit-Ganzworts
    ab: Ueberlauf bricht um, wie in C, Rust (wrapping) und Java."""
    x &= _MASKE64
    return x - (1 << 64) if x & _VORZEICHENBIT64 else x


def pruefsumme(z):
    """summe(z[i] * (i + 1)) mit Ueberlaufumbruch, danach mod 2^63 - 1."""
    summe = 0
    for i in range(GROESSE):
        summe = umbruch64(summe + umbruch64(z[i] * (i + 1)))
    return summe % PRUEFSUMME_MOD


def main():
    # Startbelegung: z[i] = 1_000_000 + i * 37
    z = [1_000_000 + i * 37 for i in range(GROESSE)]

    # Die drei Schritte stehen ausgeschrieben in der Schleife statt in
    # Hilfsfunktionen: 64.000.000 Fortschreibungen mal drei Aufrufe kosten in
    # CPython mehr Zeit als die Rechnung selbst und wuerden die Messung
    # verfaelschen. Ein Python-Programmierer schreibt eine so heisse Schleife
    # ebenso; die Rechenvorschrift ist Zeile fuer Zeile dieselbe.
    #
    # Zwei Eigenschaften der Vorgabe erlauben die kurzen Formen:
    #
    # 1. `klemme(..., 0, 10^12)` haelt jeden Zustandswert dauerhaft in
    #    [0, 10^12], und die Startbelegung liegt schon darin. Alle Operanden
    #    von `%` und `//` sind also nie negativ -- dort stimmen Pythons
    #    abrundende Operatoren mit der gegen null abschneidenden
    #    Ganzzahldivision der Vorgabe ueberein.
    # 2. Damit ist `mal_geteilt(a, b, 10_000)` mit a, b >= 0 gleich
    #    (2*a*b + 10_000) // 20_000 -- das ist genau "auf halbe Betraege von
    #    null weg" gerundet, denn a*b/10_000 = k + f wird zu k + f + 1/2
    #    abgerundet.
    #
    # Kein Zwischenwert verlaesst dabei den 64-Bit-Bereich: das Produkt bleibt
    # unter 10^12 * 10.976, also rund 1,1 * 10^16. Der Umbruch bleibt deshalb
    # der Pruefsumme vorbehalten.
    grenze = GROESSE
    versatz = NACHBAR_VERSATZ
    streuer = STREUER
    nenner = NENNER
    doppel_nenner = 2 * NENNER
    nachbar_teiler = NACHBAR_TEILER
    eigen_teiler = EIGEN_TEILER
    untergrenze = UNTERGRENZE
    obergrenze = OBERGRENZE

    beginn = time.perf_counter_ns()
    for _ in range(SCHRITTE):
        for i in range(grenze):
            # 1. Nachbar -- in-place, ein spaeteres i sieht die schon
            #    fortgeschriebenen Werte der frueheren.
            nachbar = z[(i + versatz) % grenze]
            eigen = z[i]
            # 2. roh = mal_geteilt(z[i], 10_000 + (nachbar mod 977), 10_000)
            zaehler = eigen * (nenner + nachbar % streuer)
            roh = (2 * zaehler + nenner) // doppel_nenner
            # 3. klemme(roh + nachbar/1024 - z[i]/4096, 0, 10^12)
            wert = roh + nachbar // nachbar_teiler - eigen // eigen_teiler
            if wert < untergrenze:
                wert = untergrenze
            elif wert > obergrenze:
                wert = obergrenze
            z[i] = wert
    ende = time.perf_counter_ns()

    print("pruefsumme=%d" % pruefsumme(z))
    print("nanosekunden_je_schritt=%d" % ((ende - beginn) // SCHRITTE))
    print("zustand0=%d" % z[0])


if __name__ == "__main__":
    main()
