// Verengung von `double` auf `int` -- loest `-Werror=float-conversion` aus, wenn der
// Warnsatz wirkt, und bleibt still, wenn ein Pauschalabschalter ihn aufhebt.
// Dieselbe Quelle wie in Befund 3 von Paket 0060.
int f(double d){ int i = d; return i; }
