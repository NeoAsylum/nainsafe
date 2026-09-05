// Der Stand VOR Paket 0044, aus `git show 9bb7492` (die entfernten Zeilen).
// Wortgleich abgeschrieben, nur der Rumpf drumherum fehlt.

/// Der Stand von `parameter.toml` zum Bauzeitpunkt (2026-09-02). Alle drei Zeilen
/// tragen dort `# PLATZHALTER`; sie werden kalibriert und nicht entworfen, deshalb
/// steht die Zahl hier als Argument und nicht in der Pruefung.
///
///   parameter.toml Zeile 304: `druck_max  = 1   # PLATZHALTER`   (T5 Klasse 9)
///   parameter.toml Zeile 205: `stufen_max = 1   # PLATZHALTER`   (T5 Klasse 11, T16)
///   parameter.toml Zeile 250: `aufschlag  = 51  # PLATZHALTER`   (T5 Klasse 3, T51)
inline constexpr int PLATZHALTER = 0;

void ausgabe()
{
    std::fprintf(stdout, "  Zeile 304  druck_max  = %lld  # PLATZHALTER\n", 0LL);
    std::fprintf(stdout, "  Zeile 205  stufen_max = %lld  # PLATZHALTER\n", 0LL);
    std::fprintf(stdout, "  Zeile 250  aufschlag  = %lld  # PLATZHALTER\n\n", 0LL);
}
