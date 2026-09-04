// Der Stand NACH Paket 0044: der Kommentarblock ueber GRENZEN_BAUZEITPUNKT und der
// Ausgabeblock darunter, beide aus der Probe des Kerns. Wortgleich abgeschrieben, nur
// der Rumpf drumherum fehlt. (Keine Nummer in dieser Ueberschrift -- sonst faengt die
// Probe sich selbst, und genau das ist beim ersten Lauf passiert.)

/// Der Stand von `parameter.toml` zum Bauzeitpunkt (2026-09-02). Alle drei Zeilen
/// tragen dort `# PLATZHALTER`; sie werden kalibriert und nicht entworfen, deshalb
/// steht die Zahl hier als Argument und nicht in der Pruefung.
///
/// Wiederzufinden sind sie ueber den **Schluesselnamen**, nicht ueber eine Nummer:
/// Jeder Schluessel der Datei steht genau einmal am Zeilenanfang, `grep -n
/// '^druck_max' parameter.toml` findet ihn ohne zu zaehlen. Alle drei stehen unter
/// der Ueberschrift `# GRUPPE A -- die elf Zeilen der Tabelle in T27`. Eine Nummer
/// stand hier bis zum 2026-09-04 und war dreimal falsch, ohne dass jemand etwas
/// getan haette (Paket 0044).
///
///   parameter.toml, Schluessel `druck_max`:  `druck_max  = 1   # PLATZHALTER`   (T5 Klasse 9)
///   parameter.toml, Schluessel `stufen_max`: `stufen_max = 1   # PLATZHALTER`   (T5 Klasse 11, T16)
///   parameter.toml, Schluessel `aufschlag`:  `aufschlag  = 51  # PLATZHALTER`   (T5 Klasse 3, T51)
inline constexpr int PLATZHALTER = 0;

void ausgabe()
{
    std::fprintf(stdout, "  druck_max  = %lld  # PLATZHALTER\n", 0LL);
    std::fprintf(stdout, "  stufen_max = %lld  # PLATZHALTER\n", 0LL);
    std::fprintf(stdout, "  aufschlag  = %lld  # PLATZHALTER\n\n", 0LL);
}
