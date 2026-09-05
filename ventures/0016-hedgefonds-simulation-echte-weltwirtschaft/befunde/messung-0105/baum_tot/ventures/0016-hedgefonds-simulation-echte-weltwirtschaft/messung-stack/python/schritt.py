#!/usr/bin/env python3
"""Deterministischer Festkomma-Weltschritt -- Python-Fassung der Stackmessung.

Rechenvorschrift: ../AUFGABE.md. Keine Fremdbibliothek, kein Gleitkommatyp,
auch nicht fuer die Zeitmessung. Laeuft ohne Argumente und ohne Eingabe.

Pythons int ist beliebig genau. Das erspart die 128-Bit-Kruecke im
Zwischenergebnis von mal_geteilt(), macht aber zwei Dinge noetig, die in Rust,
C++ und Java umsonst kommen: die Klemmung auf 64 Bit mit Vorzeichen (zu_i64)
und die gegen null abschneidende Division (geteilt), denn Pythons // rundet
zur naechstkleineren Zahl ab und sein % traegt das Vorzeichen des Divisors.
"""

import time

BREITE = 64
SCHRITTE = 1_000_000
UNTEN = -1_000_000_000_000
OBEN = 1_000_000_000_000

I64_MASKE = (1 << 64) - 1
I64_VORZEICHEN = 1 << 63


def zu_i64(x):
    """Bildet x auf 64 Bit mit Vorzeichen ab -- Ueberlaufumbruch wie in C, Java, Rust."""
    x &= I64_MASKE
    return x - (1 << 64) if x >= I64_VORZEICHEN else x


def geteilt(a, b):
    """Ganzzahldivision, die gegen null abschneidet."""
    q = abs(a) // abs(b)
    return -q if (a < 0) != (b < 0) else q


def rest(a, b):
    """Rest zur abschneidenden Division -- traegt das Vorzeichen von a."""
    return a - geteilt(a, b) * b


def mal_geteilt(a, b, c):
    """a * b / c ohne Ueberlauf im Zwischenergebnis, auf halbe Betraege von null weg."""
    zaehler = a * b
    negativ = (zaehler < 0) != (c < 0)
    z, n = abs(zaehler), abs(c)
    q = (2 * z + n) // (2 * n)
    return -q if negativ else q


def klemme(x, u, o):
    """Begrenzt x auf [u, o]."""
    if x < u:
        return u
    if x > o:
        return o
    return x


def main():
    z = [zu_i64(1_000_000 + i * 37) for i in range(BREITE)]

    begonnen = time.perf_counter_ns()
    for _ in range(SCHRITTE):
        for i in range(BREITE):
            nachbar = z[(i + 17) % BREITE]
            alt = z[i]
            roh = mal_geteilt(alt, 9_512 + rest(nachbar, 977), 10_000)
            z[i] = klemme(roh + geteilt(nachbar, 1024) - geteilt(alt, 4096), UNTEN, OBEN)
    gedauert = time.perf_counter_ns() - begonnen

    pruefsumme = 0
    for i in range(BREITE):
        pruefsumme = zu_i64(pruefsumme + zu_i64(z[i] * (i + 1)))

    print("pruefsumme=" + str(pruefsumme))
    print("nanosekunden_je_schritt=" + str(gedauert // SCHRITTE))
    print("zustand0=" + str(z[0]))


if __name__ == "__main__":
    main()
