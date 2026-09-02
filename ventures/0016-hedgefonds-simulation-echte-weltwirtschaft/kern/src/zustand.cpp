//! Die Adresstabelle, ihr Nachweis und die kanonische Byteform.
//!
//! Diese Datei enthaelt zwei Fassungen derselben Menge von 310 Adressen:
//!
//!   1. **Die Tabelle** `ADRESSTABELLE` -- Zeile fuer Zeile die Adressspalte aus
//!      `daten/adressen.md`, in der Reihenfolge der dortigen laufenden Nummer. Sie
//!      ist zum Vergleichen da: Wer sie neben das Verzeichnis legt, sieht jede
//!      Abweichung als Zeilenunterschied und muss nichts nachrechnen.
//!   2. **Die Rechenvorschrift** -- die `stelle_*`-Funktionen aus `zustand.hpp`, die
//!      denselben Platz aus benannten Aufzaehlungen ergeben.
//!
//! **Der Nachweis, dass beide dieselbe Menge sind, steht als `static_assert` da und
//! nicht als Behauptung.** `deckungslauf()` unten laeuft ueber jede Aufzaehlung jeder
//! Gruppe, baut die erwartete Adresse aus den Namensbestandteilen zusammen, holt ueber
//! die zugehoerige `stelle_*`-Funktion den Platz und legt beides gegeneinander. Daraus
//! fallen zwei Zahlen:
//!
//!   `erste_textabweichung()`  Verzeichniszeile, deren Adresse nicht zur gerechneten
//!                             Stelle passt -- 0 heisst: keine.
//!   `erste_fehlbelegung()`    Verzeichniszeile, die von keiner oder von mehr als
//!                             einer `stelle_*`-Kombination getroffen wird -- 0 heisst:
//!                             keine.
//!
//! Zusammen sind das beide Richtungen der Abnahmebedingung: Jede der 310 Zeilen ist
//! ueber eine Adressfunktion erreichbar (keine Zeile bleibt bei null), und die
//! Abbildung kennt keine Adresse, die dort nicht steht (keine Zeile wird zweimal
//! getroffen, und die Tabelle hat genau 310 Eintraege).
//!
//! Warum ueberhaupt zwei Fassungen: Eine Tabelle allein waere gegen das Verzeichnis
//! pruefbar, aber der Kern muesste jede Adresse als Text zusammensetzen, um sie zu
//! finden. Eine Rechenvorschrift allein waere schnell, aber ihre Uebereinstimmung mit
//! dem Verzeichnis liesse sich nur lesend pruefen. Nebeneinander pruefen sie sich
//! gegenseitig, und der Uebersetzer ist der Pruefer.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/pruefsumme.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::zustand {
namespace {

// ---------------------------------------------------------------------------
// Die Adressspalte aus `daten/adressen.md`, Zeile fuer Zeile
// ---------------------------------------------------------------------------
//
// Der Kommentar hinter jeder Zeile ist der Platz im Zustand; die laufende Nummer im
// Verzeichnis ist um eins groesser. Die Bloecke sind durch Leerzeilen getrennt, damit
// sich die Gruppentabelle aus T15 (`198 + 56 + 52 + 4`) am Rand mitzaehlen laesst.

constexpr std::array<const char*, FELDER> ADRESSTABELLE = {
    // --- vier spielbare Laender, je 44 Felder: Plaetze 0 bis 175 ---------------
    "land.US.sektor.1.wertschoepfung",                   // 0
    "land.US.sektor.1.kapitalstock",                     // 1
    "land.US.sektor.1.beschaeftigung",                   // 2
    "land.US.sektor.1.preis",                            // 3
    "land.US.sektor.2.wertschoepfung",                   // 4
    "land.US.sektor.2.kapitalstock",                     // 5
    "land.US.sektor.2.beschaeftigung",                   // 6
    "land.US.sektor.2.preis",                            // 7
    "land.US.sektor.3.wertschoepfung",                   // 8
    "land.US.sektor.3.kapitalstock",                     // 9
    "land.US.sektor.3.beschaeftigung",                   // 10
    "land.US.sektor.3.preis",                            // 11
    "land.US.bevoelkerung",                              // 12
    "land.US.erwerbstaetige",                            // 13
    "land.US.produktivitaet",                            // 14
    "land.US.preisniveau",                               // 15
    "land.US.inflation",                                 // 16
    "land.US.leitzins",                                  // 17
    "land.US.wechselkurs",                               // 18
    "land.US.staatsschuld",                              // 19
    "land.US.haushaltssaldo",                            // 20
    "land.US.zustimmung",                                // 21
    "land.US.aufsichtszaehler",                          // 22
    "land.US.einfluss",                                  // 23
    "land.US.instrument.leitzins.stand",                 // 24
    "land.US.instrument.leitzins.druck",                 // 25
    "land.US.instrument.leitzins.gegendruck",            // 26
    "land.US.instrument.leitzins.restverzoegerung",      // 27
    "land.US.instrument.zoll.stand",                     // 28
    "land.US.instrument.zoll.druck",                     // 29
    "land.US.instrument.zoll.gegendruck",                // 30
    "land.US.instrument.zoll.restverzoegerung",          // 31
    "land.US.instrument.haushalt.stand",                 // 32
    "land.US.instrument.haushalt.druck",                 // 33
    "land.US.instrument.haushalt.gegendruck",            // 34
    "land.US.instrument.haushalt.restverzoegerung",      // 35
    "land.US.instrument.regulierung.stand",              // 36
    "land.US.instrument.regulierung.druck",              // 37
    "land.US.instrument.regulierung.gegendruck",         // 38
    "land.US.instrument.regulierung.restverzoegerung",   // 39
    "land.US.marktverbot_rest",                          // 40
    "land.US.lobbykosten_rest",                          // 41
    "land.US.regierungsdruck_rest",                      // 42
    "land.US.basiswechsel",                              // 43

    "land.CN.sektor.1.wertschoepfung",                   // 44
    "land.CN.sektor.1.kapitalstock",                     // 45
    "land.CN.sektor.1.beschaeftigung",                   // 46
    "land.CN.sektor.1.preis",                            // 47
    "land.CN.sektor.2.wertschoepfung",                   // 48
    "land.CN.sektor.2.kapitalstock",                     // 49
    "land.CN.sektor.2.beschaeftigung",                   // 50
    "land.CN.sektor.2.preis",                            // 51
    "land.CN.sektor.3.wertschoepfung",                   // 52
    "land.CN.sektor.3.kapitalstock",                     // 53
    "land.CN.sektor.3.beschaeftigung",                   // 54
    "land.CN.sektor.3.preis",                            // 55
    "land.CN.bevoelkerung",                              // 56
    "land.CN.erwerbstaetige",                            // 57
    "land.CN.produktivitaet",                            // 58
    "land.CN.preisniveau",                               // 59
    "land.CN.inflation",                                 // 60
    "land.CN.leitzins",                                  // 61
    "land.CN.wechselkurs",                               // 62
    "land.CN.staatsschuld",                              // 63
    "land.CN.haushaltssaldo",                            // 64
    "land.CN.zustimmung",                                // 65
    "land.CN.aufsichtszaehler",                          // 66
    "land.CN.einfluss",                                  // 67
    "land.CN.instrument.leitzins.stand",                 // 68
    "land.CN.instrument.leitzins.druck",                 // 69
    "land.CN.instrument.leitzins.gegendruck",            // 70
    "land.CN.instrument.leitzins.restverzoegerung",      // 71
    "land.CN.instrument.zoll.stand",                     // 72
    "land.CN.instrument.zoll.druck",                     // 73
    "land.CN.instrument.zoll.gegendruck",                // 74
    "land.CN.instrument.zoll.restverzoegerung",          // 75
    "land.CN.instrument.haushalt.stand",                 // 76
    "land.CN.instrument.haushalt.druck",                 // 77
    "land.CN.instrument.haushalt.gegendruck",            // 78
    "land.CN.instrument.haushalt.restverzoegerung",      // 79
    "land.CN.instrument.regulierung.stand",              // 80
    "land.CN.instrument.regulierung.druck",              // 81
    "land.CN.instrument.regulierung.gegendruck",         // 82
    "land.CN.instrument.regulierung.restverzoegerung",   // 83
    "land.CN.marktverbot_rest",                          // 84
    "land.CN.lobbykosten_rest",                          // 85
    "land.CN.regierungsdruck_rest",                      // 86
    "land.CN.basiswechsel",                              // 87

    "land.DE.sektor.1.wertschoepfung",                   // 88
    "land.DE.sektor.1.kapitalstock",                     // 89
    "land.DE.sektor.1.beschaeftigung",                   // 90
    "land.DE.sektor.1.preis",                            // 91
    "land.DE.sektor.2.wertschoepfung",                   // 92
    "land.DE.sektor.2.kapitalstock",                     // 93
    "land.DE.sektor.2.beschaeftigung",                   // 94
    "land.DE.sektor.2.preis",                            // 95
    "land.DE.sektor.3.wertschoepfung",                   // 96
    "land.DE.sektor.3.kapitalstock",                     // 97
    "land.DE.sektor.3.beschaeftigung",                   // 98
    "land.DE.sektor.3.preis",                            // 99
    "land.DE.bevoelkerung",                              // 100
    "land.DE.erwerbstaetige",                            // 101
    "land.DE.produktivitaet",                            // 102
    "land.DE.preisniveau",                               // 103
    "land.DE.inflation",                                 // 104
    "land.DE.leitzins",                                  // 105
    "land.DE.wechselkurs",                               // 106
    "land.DE.staatsschuld",                              // 107
    "land.DE.haushaltssaldo",                            // 108
    "land.DE.zustimmung",                                // 109
    "land.DE.aufsichtszaehler",                          // 110
    "land.DE.einfluss",                                  // 111
    "land.DE.instrument.leitzins.stand",                 // 112
    "land.DE.instrument.leitzins.druck",                 // 113
    "land.DE.instrument.leitzins.gegendruck",            // 114
    "land.DE.instrument.leitzins.restverzoegerung",      // 115
    "land.DE.instrument.zoll.stand",                     // 116
    "land.DE.instrument.zoll.druck",                     // 117
    "land.DE.instrument.zoll.gegendruck",                // 118
    "land.DE.instrument.zoll.restverzoegerung",          // 119
    "land.DE.instrument.haushalt.stand",                 // 120
    "land.DE.instrument.haushalt.druck",                 // 121
    "land.DE.instrument.haushalt.gegendruck",            // 122
    "land.DE.instrument.haushalt.restverzoegerung",      // 123
    "land.DE.instrument.regulierung.stand",              // 124
    "land.DE.instrument.regulierung.druck",              // 125
    "land.DE.instrument.regulierung.gegendruck",         // 126
    "land.DE.instrument.regulierung.restverzoegerung",   // 127
    "land.DE.marktverbot_rest",                          // 128
    "land.DE.lobbykosten_rest",                          // 129
    "land.DE.regierungsdruck_rest",                      // 130
    "land.DE.basiswechsel",                              // 131

    "land.BR.sektor.1.wertschoepfung",                   // 132
    "land.BR.sektor.1.kapitalstock",                     // 133
    "land.BR.sektor.1.beschaeftigung",                   // 134
    "land.BR.sektor.1.preis",                            // 135
    "land.BR.sektor.2.wertschoepfung",                   // 136
    "land.BR.sektor.2.kapitalstock",                     // 137
    "land.BR.sektor.2.beschaeftigung",                   // 138
    "land.BR.sektor.2.preis",                            // 139
    "land.BR.sektor.3.wertschoepfung",                   // 140
    "land.BR.sektor.3.kapitalstock",                     // 141
    "land.BR.sektor.3.beschaeftigung",                   // 142
    "land.BR.sektor.3.preis",                            // 143
    "land.BR.bevoelkerung",                              // 144
    "land.BR.erwerbstaetige",                            // 145
    "land.BR.produktivitaet",                            // 146
    "land.BR.preisniveau",                               // 147
    "land.BR.inflation",                                 // 148
    "land.BR.leitzins",                                  // 149
    "land.BR.wechselkurs",                               // 150
    "land.BR.staatsschuld",                              // 151
    "land.BR.haushaltssaldo",                            // 152
    "land.BR.zustimmung",                                // 153
    "land.BR.aufsichtszaehler",                          // 154
    "land.BR.einfluss",                                  // 155
    "land.BR.instrument.leitzins.stand",                 // 156
    "land.BR.instrument.leitzins.druck",                 // 157
    "land.BR.instrument.leitzins.gegendruck",            // 158
    "land.BR.instrument.leitzins.restverzoegerung",      // 159
    "land.BR.instrument.zoll.stand",                     // 160
    "land.BR.instrument.zoll.druck",                     // 161
    "land.BR.instrument.zoll.gegendruck",                // 162
    "land.BR.instrument.zoll.restverzoegerung",          // 163
    "land.BR.instrument.haushalt.stand",                 // 164
    "land.BR.instrument.haushalt.druck",                 // 165
    "land.BR.instrument.haushalt.gegendruck",            // 166
    "land.BR.instrument.haushalt.restverzoegerung",      // 167
    "land.BR.instrument.regulierung.stand",              // 168
    "land.BR.instrument.regulierung.druck",              // 169
    "land.BR.instrument.regulierung.gegendruck",         // 170
    "land.BR.instrument.regulierung.restverzoegerung",   // 171
    "land.BR.marktverbot_rest",                          // 172
    "land.BR.lobbykosten_rest",                          // 173
    "land.BR.regierungsdruck_rest",                      // 174
    "land.BR.basiswechsel",                              // 175

    // --- die Restwelt, 22 Felder: Plaetze 176 bis 197 -------------------------
    "restwelt.sektor.1.wertschoepfung",                  // 176
    "restwelt.sektor.1.kapitalstock",                    // 177
    "restwelt.sektor.1.beschaeftigung",                  // 178
    "restwelt.sektor.1.preis",                           // 179
    "restwelt.sektor.2.wertschoepfung",                  // 180
    "restwelt.sektor.2.kapitalstock",                    // 181
    "restwelt.sektor.2.beschaeftigung",                  // 182
    "restwelt.sektor.2.preis",                           // 183
    "restwelt.sektor.3.wertschoepfung",                  // 184
    "restwelt.sektor.3.kapitalstock",                    // 185
    "restwelt.sektor.3.beschaeftigung",                  // 186
    "restwelt.sektor.3.preis",                           // 187
    "restwelt.bevoelkerung",                             // 188
    "restwelt.erwerbstaetige",                           // 189
    "restwelt.produktivitaet",                           // 190
    "restwelt.preisniveau",                              // 191
    "restwelt.inflation",                                // 192
    "restwelt.leitzins",                                 // 193
    "restwelt.wechselkurs",                              // 194
    "restwelt.staatsschuld",                             // 195
    "restwelt.haushaltssaldo",                           // 196
    "restwelt.basiswechsel",                             // 197

    // --- Handel, 5 x 4 x 2: Plaetze 198 bis 237 -------------------------------
    "handel.US.CN.1",                                    // 198
    "handel.US.CN.2",                                    // 199
    "handel.US.DE.1",                                    // 200
    "handel.US.DE.2",                                    // 201
    "handel.US.BR.1",                                    // 202
    "handel.US.BR.2",                                    // 203
    "handel.US.RW.1",                                    // 204
    "handel.US.RW.2",                                    // 205
    "handel.CN.US.1",                                    // 206
    "handel.CN.US.2",                                    // 207
    "handel.CN.DE.1",                                    // 208
    "handel.CN.DE.2",                                    // 209
    "handel.CN.BR.1",                                    // 210
    "handel.CN.BR.2",                                    // 211
    "handel.CN.RW.1",                                    // 212
    "handel.CN.RW.2",                                    // 213
    "handel.DE.US.1",                                    // 214
    "handel.DE.US.2",                                    // 215
    "handel.DE.CN.1",                                    // 216
    "handel.DE.CN.2",                                    // 217
    "handel.DE.BR.1",                                    // 218
    "handel.DE.BR.2",                                    // 219
    "handel.DE.RW.1",                                    // 220
    "handel.DE.RW.2",                                    // 221
    "handel.BR.US.1",                                    // 222
    "handel.BR.US.2",                                    // 223
    "handel.BR.CN.1",                                    // 224
    "handel.BR.CN.2",                                    // 225
    "handel.BR.DE.1",                                    // 226
    "handel.BR.DE.2",                                    // 227
    "handel.BR.RW.1",                                    // 228
    "handel.BR.RW.2",                                    // 229
    "handel.RW.US.1",                                    // 230
    "handel.RW.US.2",                                    // 231
    "handel.RW.CN.1",                                    // 232
    "handel.RW.CN.2",                                    // 233
    "handel.RW.DE.1",                                    // 234
    "handel.RW.DE.2",                                    // 235
    "handel.RW.BR.1",                                    // 236
    "handel.RW.BR.2",                                    // 237

    // --- Weltpreise: Plaetze 238 bis 239 --------------------------------------
    "welt.preis.1",                                      // 238
    "welt.preis.2",                                      // 239

    // --- Nachahmerzaehler, 4 x 3: Plaetze 240 bis 251 -------------------------
    "fonds.nachahmer.US.1",                              // 240
    "fonds.nachahmer.US.2",                              // 241
    "fonds.nachahmer.US.3",                              // 242
    "fonds.nachahmer.CN.1",                              // 243
    "fonds.nachahmer.CN.2",                              // 244
    "fonds.nachahmer.CN.3",                              // 245
    "fonds.nachahmer.DE.1",                              // 246
    "fonds.nachahmer.DE.2",                              // 247
    "fonds.nachahmer.DE.3",                              // 248
    "fonds.nachahmer.BR.1",                              // 249
    "fonds.nachahmer.BR.2",                              // 250
    "fonds.nachahmer.BR.3",                              // 251

    // --- Marktkorb: Plaetze 252 bis 253 ---------------------------------------
    "markt.wert",                                        // 252
    "markt.rendite",                                     // 253

    // --- Fondsaggregate: Plaetze 254 bis 258 ----------------------------------
    "fonds.kasse",                                       // 254
    "fonds.hebelstand",                                  // 255
    "fonds.sichtbarkeit",                                // 256
    "fonds.anlegerbestand",                              // 257
    "fonds.marktanteil",                                 // 258

    // --- Ueberrenditen der letzten drei Runden: Plaetze 259 bis 261 -----------
    "fonds.ueberrendite.1",                              // 259
    "fonds.ueberrendite.2",                              // 260
    "fonds.ueberrendite.3",                              // 261

    // --- die zwanzig Steckplaetze: Plaetze 262 bis 281 ------------------------
    "fonds.position.US.1",                               // 262
    "fonds.position.US.2",                               // 263
    "fonds.position.US.3",                               // 264
    "fonds.position.CN.1",                               // 265
    "fonds.position.CN.2",                               // 266
    "fonds.position.CN.3",                               // 267
    "fonds.position.DE.1",                               // 268
    "fonds.position.DE.2",                               // 269
    "fonds.position.DE.3",                               // 270
    "fonds.position.BR.1",                               // 271
    "fonds.position.BR.2",                               // 272
    "fonds.position.BR.3",                               // 273
    "fonds.position.waehrung.US",                        // 274  -- dauerhaft leer (T16)
    "fonds.position.waehrung.CN",                        // 275
    "fonds.position.waehrung.DE",                        // 276
    "fonds.position.waehrung.BR",                        // 277
    "fonds.position.anleihe.US",                         // 278
    "fonds.position.anleihe.CN",                         // 279
    "fonds.position.anleihe.DE",                         // 280
    "fonds.position.anleihe.BR",                         // 281

    // --- Beteiligungen, 12 x 2: Plaetze 282 bis 305 ---------------------------
    "fonds.beteiligung.US.1.anteil",                     // 282
    "fonds.beteiligung.US.1.restdauer",                  // 283
    "fonds.beteiligung.US.2.anteil",                     // 284
    "fonds.beteiligung.US.2.restdauer",                  // 285
    "fonds.beteiligung.US.3.anteil",                     // 286
    "fonds.beteiligung.US.3.restdauer",                  // 287
    "fonds.beteiligung.CN.1.anteil",                     // 288
    "fonds.beteiligung.CN.1.restdauer",                  // 289
    "fonds.beteiligung.CN.2.anteil",                     // 290
    "fonds.beteiligung.CN.2.restdauer",                  // 291
    "fonds.beteiligung.CN.3.anteil",                     // 292
    "fonds.beteiligung.CN.3.restdauer",                  // 293
    "fonds.beteiligung.DE.1.anteil",                     // 294
    "fonds.beteiligung.DE.1.restdauer",                  // 295
    "fonds.beteiligung.DE.2.anteil",                     // 296
    "fonds.beteiligung.DE.2.restdauer",                  // 297
    "fonds.beteiligung.DE.3.anteil",                     // 298
    "fonds.beteiligung.DE.3.restdauer",                  // 299
    "fonds.beteiligung.BR.1.anteil",                     // 300
    "fonds.beteiligung.BR.1.restdauer",                  // 301
    "fonds.beteiligung.BR.2.anteil",                     // 302
    "fonds.beteiligung.BR.2.restdauer",                  // 303
    "fonds.beteiligung.BR.3.anteil",                     // 304
    "fonds.beteiligung.BR.3.restdauer",                  // 305

    // --- Partie: Plaetze 306 bis 309 ------------------------------------------
    "partie.runde",                                      // 306
    "partie.jahrgang_id",                                // 307
    "partie.parameter_pruefsumme",                       // 308
    "partie.mandatsstand",                               // 309
};

// ---------------------------------------------------------------------------
// Die Namensbestandteile
// ---------------------------------------------------------------------------
//
// Aus diesen Stuecken setzt `deckungslauf()` die erwartete Adresse zusammen. Die
// Reihenfolge jeder Liste ist die Reihenfolge der zugehoerigen Aufzaehlung aus
// `zustand.hpp` -- sie ist damit derselbe Gegenstand wie T9 und nicht eine zweite
// Meinung darueber.

constexpr std::array<const char*, GEBIETE> GEBIET_KUERZEL = {"US", "CN", "DE", "BR", "RW"};

constexpr std::array<const char*, SEKTORGROESSEN> SEKTORGROESSE_NAME = {
    "wertschoepfung", "kapitalstock", "beschaeftigung", "preis"};

constexpr std::array<const char*, AGGREGATE> AGGREGAT_NAME = {
    "bevoelkerung", "erwerbstaetige", "produktivitaet", "preisniveau", "inflation",
    "leitzins",     "wechselkurs",    "staatsschuld",   "haushaltssaldo"};

constexpr std::array<const char*, POLITISCHE_GROESSEN> POLITISCH_NAME = {
    "zustimmung", "aufsichtszaehler", "einfluss"};

constexpr std::array<const char*, INSTRUMENTE> INSTRUMENT_NAME = {
    "leitzins", "zoll", "haushalt", "regulierung"};

constexpr std::array<const char*, INSTRUMENTFELDER> INSTRUMENTFELD_NAME = {
    "stand", "druck", "gegendruck", "restverzoegerung"};

constexpr std::array<const char*, RESTDAUERZAEHLER> RESTDAUER_NAME = {
    "marktverbot_rest", "lobbykosten_rest", "regierungsdruck_rest"};

constexpr std::array<const char*, MARKTGROESSEN> MARKT_NAME = {"wert", "rendite"};

constexpr std::array<const char*, FONDSGROESSEN> FONDS_NAME = {
    "kasse", "hebelstand", "sichtbarkeit", "anlegerbestand", "marktanteil"};

constexpr std::array<const char*, BETEILIGUNGSFELDER> BETEILIGUNG_NAME = {"anteil", "restdauer"};

constexpr std::array<const char*, PARTIEFELDER> PARTIE_NAME = {
    "runde", "jahrgang_id", "parameter_pruefsumme", "mandatsstand"};

// ---------------------------------------------------------------------------
// Textwerkzeug -- so wenig, wie fuer den Nachweis noetig ist
// ---------------------------------------------------------------------------

/// Vergleich zweier nullbyte-begrenzter Texte. Laeuft bis zum ersten Unterschied
/// oder bis zum Ende; sind beide dort am Nullbyte, sind sie gleich.
[[nodiscard]] constexpr bool gleich(const char* links, const char* rechts) noexcept
{
    std::size_t i = 0;
    while (links[i] != '\0' && links[i] == rechts[i]) {
        ++i;
    }
    return links[i] == rechts[i];
}

/// Zeichen bis zum Nullbyte.
[[nodiscard]] constexpr std::size_t laenge_von(const char* text) noexcept
{
    std::size_t i = 0;
    while (text[i] != '\0') {
        ++i;
    }
    return i;
}

/// Ein Adresspuffer fester Groesse, an den nur angehaengt wird.
///
/// Kein wachsender Behaelter: Die laengste Adresse ist bekannt (47 Zeichen), der
/// Puffer traegt sie samt Nullbyte, und ein Ueberlauf bricht ab, statt zu wachsen.
/// Das Feld ist mit Nullen vorbelegt, also ist das Nullbyte hinter dem letzten
/// angehaengten Zeichen immer schon da.
struct Aufbau {
    std::array<char, ADRESSE_PUFFER> zeichen{};
    std::size_t laenge = 0;

    constexpr void haenge_an(const char* teil)
    {
        for (std::size_t i = 0; teil[i] != '\0'; ++i) {
            if (laenge + 1 >= zeichen.size()) {
                festkomma::abbruch("kern::zustand -- Adresse laenger als der Puffer");
            }
            zeichen[laenge] = teil[i];
            ++laenge;
        }
    }

    constexpr void haenge_ziffer(std::size_t wert)
    {
        if (wert > 9) {
            festkomma::abbruch("kern::zustand -- in einer Adresse steht nie eine zweistellige Zahl");
        }
        if (laenge + 1 >= zeichen.size()) {
            festkomma::abbruch("kern::zustand -- Adresse laenger als der Puffer");
        }
        zeichen[laenge] = static_cast<char>('0' + static_cast<int>(wert));
        ++laenge;
    }

    [[nodiscard]] constexpr const char* text() const noexcept { return zeichen.data(); }
};

/// `land.US.` fuer die vier spielbaren Laender, `restwelt.` fuer die Restwelt.
constexpr void gebietspraefix(Aufbau& ziel, std::size_t gebiet)
{
    if (gebiet < LAENDER) {
        ziel.haenge_an("land.");
        ziel.haenge_an(GEBIET_KUERZEL[gebiet]);
        ziel.haenge_an(".");
    } else {
        ziel.haenge_an("restwelt.");
    }
}

// ---------------------------------------------------------------------------
// Der Deckungslauf: jede Aufzaehlung einmal durch, jede Adresse einmal gegengelegt
// ---------------------------------------------------------------------------

struct Deckungslauf {
    /// Wie oft jeder Platz von einer `stelle_*`-Kombination getroffen wurde.
    std::array<int, FELDER> treffer{};

    /// Erste Verzeichniszeile (1-basiert), deren Tabelleneintrag nicht zur
    /// gerechneten Stelle passt. Null heisst: keine.
    Index textabweichung = 0;

    constexpr void vermerke(Index platz, const Aufbau& erwartet)
    {
        if (platz >= FELDER) {
            festkomma::abbruch("kern::zustand -- gerechnete Stelle ausserhalb der 310 Felder");
        }
        ++treffer[platz];
        if (textabweichung == 0 && !gleich(ADRESSTABELLE[platz], erwartet.text())) {
            textabweichung = platz + 1;
        }
    }
};

constexpr Deckungslauf deckungslauf()
{
    Deckungslauf lauf;

    // --- die fuenf Gebietsbloecke, so weit sie gleich gebaut sind -------------
    for (std::size_t g = 0; g < GEBIETE; ++g) {
        const Gebiet gebiet = static_cast<Gebiet>(g);

        for (std::size_t s = 1; s <= SEKTOREN; ++s) {
            const Sektor sektor = static_cast<Sektor>(s);
            for (std::size_t k = 0; k < SEKTORGROESSEN; ++k) {
                Aufbau erwartet;
                gebietspraefix(erwartet, g);
                erwartet.haenge_an("sektor.");
                erwartet.haenge_ziffer(s);
                erwartet.haenge_an(".");
                erwartet.haenge_an(SEKTORGROESSE_NAME[k]);
                lauf.vermerke(
                    stelle_sektorgroesse(gebiet, sektor, static_cast<SektorGroesse>(k)), erwartet);
            }
        }

        for (std::size_t a = 0; a < AGGREGATE; ++a) {
            Aufbau erwartet;
            gebietspraefix(erwartet, g);
            erwartet.haenge_an(AGGREGAT_NAME[a]);
            lauf.vermerke(stelle_aggregat(gebiet, static_cast<Aggregat>(a)), erwartet);
        }

        Aufbau basiswechsel;
        gebietspraefix(basiswechsel, g);
        basiswechsel.haenge_an("basiswechsel");
        lauf.vermerke(stelle_basiswechsel(gebiet), basiswechsel);
    }

    // --- was nur die vier spielbaren Laender haben ----------------------------
    for (std::size_t l = 0; l < LAENDER; ++l) {
        const Gebiet land = static_cast<Gebiet>(l);

        for (std::size_t p = 0; p < POLITISCHE_GROESSEN; ++p) {
            Aufbau erwartet;
            gebietspraefix(erwartet, l);
            erwartet.haenge_an(POLITISCH_NAME[p]);
            lauf.vermerke(stelle_politisch(land, static_cast<PolitischeGroesse>(p)), erwartet);
        }

        for (std::size_t i = 0; i < INSTRUMENTE; ++i) {
            for (std::size_t f = 0; f < INSTRUMENTFELDER; ++f) {
                Aufbau erwartet;
                gebietspraefix(erwartet, l);
                erwartet.haenge_an("instrument.");
                erwartet.haenge_an(INSTRUMENT_NAME[i]);
                erwartet.haenge_an(".");
                erwartet.haenge_an(INSTRUMENTFELD_NAME[f]);
                lauf.vermerke(stelle_instrument(land, static_cast<Instrument>(i),
                                                static_cast<InstrumentFeld>(f)),
                              erwartet);
            }
        }

        for (std::size_t r = 0; r < RESTDAUERZAEHLER; ++r) {
            Aufbau erwartet;
            gebietspraefix(erwartet, l);
            erwartet.haenge_an(RESTDAUER_NAME[r]);
            lauf.vermerke(stelle_restdauer(land, static_cast<Restdauerzaehler>(r)), erwartet);
        }
    }

    // --- Handel: jedes Gebiet gegen die vier anderen, zwei handelbare Sektoren -
    for (std::size_t v = 0; v < GEBIETE; ++v) {
        for (std::size_t n = 0; n < GEBIETE; ++n) {
            if (v == n) {
                continue;
            }
            for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
                Aufbau erwartet;
                erwartet.haenge_an("handel.");
                erwartet.haenge_an(GEBIET_KUERZEL[v]);
                erwartet.haenge_an(".");
                erwartet.haenge_an(GEBIET_KUERZEL[n]);
                erwartet.haenge_an(".");
                erwartet.haenge_ziffer(s);
                lauf.vermerke(stelle_handel(static_cast<Gebiet>(v), static_cast<Gebiet>(n),
                                            static_cast<Sektor>(s)),
                              erwartet);
            }
        }
    }

    // --- Weltpreise -----------------------------------------------------------
    for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
        Aufbau erwartet;
        erwartet.haenge_an("welt.preis.");
        erwartet.haenge_ziffer(s);
        lauf.vermerke(stelle_weltpreis(static_cast<Sektor>(s)), erwartet);
    }

    // --- Nachahmerzaehler -----------------------------------------------------
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t s = 1; s <= SEKTOREN; ++s) {
            Aufbau erwartet;
            erwartet.haenge_an("fonds.nachahmer.");
            erwartet.haenge_an(GEBIET_KUERZEL[l]);
            erwartet.haenge_an(".");
            erwartet.haenge_ziffer(s);
            lauf.vermerke(stelle_nachahmer(static_cast<Gebiet>(l), static_cast<Sektor>(s)),
                          erwartet);
        }
    }

    // --- Marktkorb ------------------------------------------------------------
    for (std::size_t m = 0; m < MARKTGROESSEN; ++m) {
        Aufbau erwartet;
        erwartet.haenge_an("markt.");
        erwartet.haenge_an(MARKT_NAME[m]);
        lauf.vermerke(stelle_markt(static_cast<MarktGroesse>(m)), erwartet);
    }

    // --- Fondsaggregate -------------------------------------------------------
    for (std::size_t f = 0; f < FONDSGROESSEN; ++f) {
        Aufbau erwartet;
        erwartet.haenge_an("fonds.");
        erwartet.haenge_an(FONDS_NAME[f]);
        lauf.vermerke(stelle_fonds(static_cast<FondsGroesse>(f)), erwartet);
    }

    // --- Ueberrenditen --------------------------------------------------------
    for (std::size_t r = 1; r <= UEBERRENDITE_RUNDEN; ++r) {
        Aufbau erwartet;
        erwartet.haenge_an("fonds.ueberrendite.");
        erwartet.haenge_ziffer(r);
        lauf.vermerke(stelle_ueberrendite(r), erwartet);
    }

    // --- die zwanzig Steckplaetze, ueber ihre drei Bildungsfunktionen ---------
    //
    // Der Umweg ueber `steckplatz_sektor`, `steckplatz_waehrung` und
    // `steckplatz_anleihe` ist Absicht: Damit steht auch deren Nummerierung im
    // Nachweis und nicht nur die Aufzaehlung `Steckplatz`.
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t s = 1; s <= SEKTOREN; ++s) {
            Aufbau erwartet;
            erwartet.haenge_an("fonds.position.");
            erwartet.haenge_an(GEBIET_KUERZEL[l]);
            erwartet.haenge_an(".");
            erwartet.haenge_ziffer(s);
            lauf.vermerke(stelle_position(steckplatz_sektor(static_cast<Gebiet>(l),
                                                            static_cast<Sektor>(s))),
                          erwartet);
        }
    }
    for (std::size_t l = 0; l < LAENDER; ++l) {
        Aufbau erwartet;
        erwartet.haenge_an("fonds.position.waehrung.");
        erwartet.haenge_an(GEBIET_KUERZEL[l]);
        lauf.vermerke(stelle_position(steckplatz_waehrung(static_cast<Gebiet>(l))), erwartet);
    }
    for (std::size_t l = 0; l < LAENDER; ++l) {
        Aufbau erwartet;
        erwartet.haenge_an("fonds.position.anleihe.");
        erwartet.haenge_an(GEBIET_KUERZEL[l]);
        lauf.vermerke(stelle_position(steckplatz_anleihe(static_cast<Gebiet>(l))), erwartet);
    }

    // --- Beteiligungen --------------------------------------------------------
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t s = 1; s <= SEKTOREN; ++s) {
            for (std::size_t f = 0; f < BETEILIGUNGSFELDER; ++f) {
                Aufbau erwartet;
                erwartet.haenge_an("fonds.beteiligung.");
                erwartet.haenge_an(GEBIET_KUERZEL[l]);
                erwartet.haenge_an(".");
                erwartet.haenge_ziffer(s);
                erwartet.haenge_an(".");
                erwartet.haenge_an(BETEILIGUNG_NAME[f]);
                lauf.vermerke(stelle_beteiligung(static_cast<Gebiet>(l), static_cast<Sektor>(s),
                                                 static_cast<BeteiligungsFeld>(f)),
                              erwartet);
            }
        }
    }

    // --- Partie ---------------------------------------------------------------
    for (std::size_t p = 0; p < PARTIEFELDER; ++p) {
        Aufbau erwartet;
        erwartet.haenge_an("partie.");
        erwartet.haenge_an(PARTIE_NAME[p]);
        lauf.vermerke(stelle_partie(static_cast<PartieFeld>(p)), erwartet);
    }

    return lauf;
}

/// Verzeichniszeile (1-basiert), deren Adresse nicht zur gerechneten Stelle passt.
[[nodiscard]] constexpr Index erste_textabweichung()
{
    return deckungslauf().textabweichung;
}

/// Verzeichniszeile (1-basiert), die von keiner oder von mehr als einer
/// `stelle_*`-Kombination getroffen wird.
[[nodiscard]] constexpr Index erste_fehlbelegung()
{
    const Deckungslauf lauf = deckungslauf();
    for (Index i = 0; i < FELDER; ++i) {
        if (lauf.treffer[i] != 1) {
            return i + 1;
        }
    }
    return 0;
}

/// Verzeichniszeile (1-basiert), deren Adresse ein zweites Mal in der Tabelle steht.
[[nodiscard]] constexpr Index erste_dopplung()
{
    for (Index i = 0; i < FELDER; ++i) {
        for (Index j = i + 1; j < FELDER; ++j) {
            if (gleich(ADRESSTABELLE[i], ADRESSTABELLE[j])) {
                return j + 1;
            }
        }
    }
    return 0;
}

/// Verzeichniszeile (1-basiert), deren Adresse nicht mehr in den Puffer passt.
[[nodiscard]] constexpr Index erste_zu_lange()
{
    for (Index i = 0; i < FELDER; ++i) {
        if (laenge_von(ADRESSTABELLE[i]) + 1 > ADRESSE_PUFFER) {
            return i + 1;
        }
    }
    return 0;
}

// Die vier Nachweise. Was hier durchgeht, ist beim Uebersetzen bewiesen und nicht
// beim Lesen geglaubt.
static_assert(ADRESSTABELLE.size() == FELDER,
              "T15: die Adresstabelle hat genau 310 Zeilen");
static_assert(erste_textabweichung() == 0,
              "T17: jede gerechnete Stelle traegt die Adresse aus daten/adressen.md");
static_assert(erste_fehlbelegung() == 0,
              "T17: jede der 310 Zeilen wird von genau einer Adressfunktion getroffen");
static_assert(erste_dopplung() == 0,
              "T17: keine Adresse steht zweimal in der Tabelle");
static_assert(erste_zu_lange() == 0,
              "der Adresspuffer traegt jede Adresse samt Nullbyte");

// Vier Stichproben an den Blockgrenzen, ausgeschrieben. Sie sind vom Deckungslauf
// mit abgedeckt und stehen trotzdem hier: Wer die Rechnung nicht nachvollziehen
// will, liest die Verzeichniszeile und den Aufruf nebeneinander.
static_assert(stelle_sektorgroesse(Gebiet::US, Sektor::Landwirtschaft,
                                   SektorGroesse::Wertschoepfung) == 0);      // Zeile 1
static_assert(stelle_instrument(Gebiet::US, Instrument::Regulierung,
                                InstrumentFeld::Restverzoegerung) == 39);     // Zeile 40
static_assert(stelle_basiswechsel(Gebiet::RW) == 197);                        // Zeile 198
static_assert(stelle_handel(Gebiet::RW, Gebiet::BR, Sektor::Industrie) == 237);  // Zeile 238
static_assert(stelle_position(steckplatz_waehrung(Gebiet::US)) == 274);       // Zeile 275
static_assert(stelle_partie(PartieFeld::Mandatsstand) == 309);                // Zeile 310

}  // namespace

// ---------------------------------------------------------------------------
// T17 -- die beiden Richtungen, oeffentlich
// ---------------------------------------------------------------------------

// Beide Fehlanzeigen gehen ueber die Vorbelegung von `Adressfund` und schreiben den
// Fehlerwert nicht selbst hin: Es gibt genau eine Stelle, an der steht, worauf eine
// unbekannte Adresse zeigt, und das ist `KEIN_PLATZ` in `zustand.hpp`.
Adressfund adresse_zu_index(const char* adresse) noexcept
{
    if (adresse == nullptr) {
        return Adressfund{};
    }
    for (Index i = 0; i < FELDER; ++i) {
        if (gleich(ADRESSTABELLE[i], adresse)) {
            return Adressfund{true, i};
        }
    }
    return Adressfund{};
}

const char* index_zu_adresse(Index index)
{
    if (index >= FELDER) {
        festkomma::abbruch("kern::zustand::index_zu_adresse -- Index ausserhalb der 310 Felder");
    }
    return ADRESSTABELLE[index];
}

// ---------------------------------------------------------------------------
// T12 -- die kanonische Byteform
// ---------------------------------------------------------------------------

// Beide Schleifen holen ihre Zahl ueber `lies` und nicht ueber das Feld selbst.
//
// Der Grund ist nicht Vorsicht, sondern dieselbe Grep-Regel wie in `zustand.hpp`: Ein
// indizierter Feldzugriff kommt im ganzen Baum nicht mehr vor, auch nicht an den beiden
// Stellen, an denen er erlaubt waere. Eine Regel mit zwei zugelassenen Ausnahmen ist in
// einem halben Jahr eine Regel mit fuenf. Die Indexpruefung, die `lies` dabei mitbringt,
// kann hier nicht anschlagen -- die Schleifengrenze *ist* `FELDER` --, und beide
// Funktionen bleiben deshalb `noexcept`, ohne dass sich daran etwas aendert.
void nach_bytes(const Zustand& zustand, std::array<std::uint8_t, BYTES>& ziel) noexcept
{
    for (Index i = 0; i < FELDER; ++i) {
        const std::array<std::uint8_t, pruefsumme::BYTES_JE_I64> acht =
            pruefsumme::nach_bytes_le(zustand.lies(i));
        for (std::size_t b = 0; b < pruefsumme::BYTES_JE_I64; ++b) {
            ziel[i * pruefsumme::BYTES_JE_I64 + b] = acht[b];
        }
    }
}

u64 pruefsumme_von(const Zustand& zustand) noexcept
{
    pruefsumme::Summe summe;
    for (Index i = 0; i < FELDER; ++i) {
        summe.nimm_i64(zustand.lies(i));
    }
    return summe.wert();
}

// ---------------------------------------------------------------------------
// Der Startwertzugang
// ---------------------------------------------------------------------------

namespace {

/// Der Platz von `partie.runde`, aus der Adressrechnung statt aus einer Zahl.
///
/// `daten/adressen.md` fuehrt ihn als laufende Nummer 307, der Kern zaehlt ab null.
/// Die Gegenrechnung steht als `static_assert` daneben: Verschoebe ein spaeteres Paket
/// den Partieblock, waere das hier ein roter Bau und kein Riegel, der ins Leere greift.
constexpr Index PLATZ_RUNDE = stelle_partie(PartieFeld::Runde);

static_assert(PLATZ_RUNDE == 306, "daten/adressen.md Nr. 307 ist partie.runde");
static_assert(PLATZ_RUNDE < FELDER, "der Riegel liegt auf einem Feld des Zustands");

/// Ein Meldungspuffer fester Groesse fuer den Riegel des Startwertzugangs.
///
/// Zwei Rundennummern gehoeren ausgeschrieben in die Meldung: die, die im Zustand
/// steht, und die, die der Zugang dort hinterlassen hat. Eine Meldung, die nur den Ort
/// nennt, laesst offen, ob der Zugang zu alt ist oder der Zustand fremd beschrieben
/// wurde -- und das ist die einzige Frage, die der Leser an dieser Stelle hat.
///
/// Fester Puffer auf dem Stapel, Grenzpruefung an jedem Zeichen, kein wachsender
/// Behaelter (T15, ADR 0011). Dass die Zeichenkette den Aufruf ueberlebt, besorgt
/// `festkomma::abbruch` selbst: Sein `std::domain_error` legt sich eine Abschrift an.
class Meldung {
public:
    void text(const char* teil)
    {
        for (Index i = 0; teil[i] != '\0'; ++i) {
            if (laenge_ + 1 >= zeichen_.size()) {
                return;  // abgeschnitten statt uebergelaufen
            }
            zeichen_[laenge_] = teil[i];
            ++laenge_;
            zeichen_[laenge_] = '\0';
        }
    }

    void zahl(i64 wert)
    {
        std::array<char, 24> ziffern{};
        Index               stellen = 0;
        const bool          negativ = wert < 0;
        // Der Betrag ueber vorzeichenlose Zahlen, damit auch der kleinste i64 geht:
        // `-I64_MIN` gibt es in `i64` nicht, `0 - (u64)I64_MIN` schon.
        u64 rest = negativ ? (u64{0} - static_cast<u64>(wert)) : static_cast<u64>(wert);
        if (rest == 0) {
            ziffern[0] = '0';
            stellen    = 1;
        }
        while (rest > 0 && stellen < ziffern.size()) {
            ziffern[stellen] = static_cast<char>('0' + (rest % 10));
            rest /= 10;
            ++stellen;
        }
        if (negativ) {
            text("-");
        }
        // Rueckwaerts ausgeben, je Ziffer eine Zeichenkette aus einem Zeichen -- damit
        // laeuft auch hier jeder Schreibzugriff durch die Grenzpruefung von `text`.
        std::array<char, 2> eine{};
        for (Index i = stellen; i > 0; --i) {
            eine[0] = ziffern[i - 1];
            text(eine.data());
        }
    }

    [[nodiscard]] const char* fertig() const { return zeichen_.data(); }

private:
    std::array<char, 512> zeichen_{};
    Index                 laenge_ = 0;
};

}  // namespace

bool vor_der_ersten_runde(const Zustand& zustand) { return zustand.lies(PLATZ_RUNDE) == 0; }

Startbelegung::Startbelegung(Zustand& ziel) : ziel_(&ziel)
{
    if (!vor_der_ersten_runde(ziel)) {
        // Kein Ersatzwert, keine stille Wirkungslosigkeit: Ein Startwert, der nach dem
        // Anpfiff gesetzt wuerde, waere eine Aenderung ohne Ursachensatz -- genau die
        // Sorte, die T18 ausschliesst und die die Diff-Ebene aus T20 spaeter als
        // Aenderung ohne Ursache zeigen wuerde.
        festkomma::abbruch(
            "kern::zustand::Startbelegung -- die Partie laeuft schon (partie.runde ist "
            "nicht null); Startwerte gibt es nur vor der ersten Runde");
    }
    // `hinterlassene_runde_` steht auf null, und die Abfrage darueber hat gerade
    // nachgesehen, dass `partie.runde` genau das traegt. Die Merkzahl ist damit von der
    // ersten Anweisung an wahr und nicht erst nach dem ersten Schreibzugriff.
}

void Startbelegung::setze(Index adresse, i64 wert)
{
    // Der Riegel, und er wird bei **jedem** Schreibzugriff gefragt: Steht auf
    // `partie.runde` noch die Zahl, die dieser Zugang dort hinterlassen hat? Wenn ja,
    // ist seit seinem letzten Schreibzugriff keine Runde ueber diesen Zustand gelaufen
    // -- entweder weil noch keine gelaufen ist (Merkzahl null, so gebunden), oder weil
    // die Zahl von ihm selbst stammt. Wenn nein, hat ein anderer geschrieben, und ein
    // Startwert waere ab hier eine Aenderung ohne Ursachensatz.
    //
    // Warum die Merkzahl und nicht stumpf die Null: `partie.runde` gehoert selbst zu
    // den 310 Groessen, die eine Startbelegung setzt. Die Begruendung in ganzer Laenge
    // steht an der Klasse in `zustand.hpp`.
    const i64 steht_im_zustand = ziel_->lies(PLATZ_RUNDE);
    if (steht_im_zustand != hinterlassene_runde_) {
        Meldung meldung;
        meldung.text("kern::zustand::Startbelegung::setze -- an diesem Zugang ist eine "
                     "Runde vorbeigelaufen: partie.runde traegt ");
        meldung.zahl(steht_im_zustand);
        meldung.text(", der Zugang hat dort ");
        meldung.zahl(hinterlassene_runde_);
        meldung.text(" hinterlassen. Startwerte gibt es nur vor der ersten Runde; "
                     "danach waere jeder eine Aenderung ohne Ursachensatz (T18) und "
                     "erschiene in der Diff-Ebene als Aenderung ohne Ursache (T20).");
        festkomma::abbruch(meldung.fertig());
    }

    // Die Indexpruefung macht der rohe Schreibzugriff; sie hier zu wiederholen hiesse,
    // dieselbe Schranke an zwei Stellen zu pflegen.
    ziel_->lege_ab(adresse, wert);

    // Und was der Zugang selbst auf `partie.runde` legt, wird seine neue Merkzahl --
    // sonst schloesse ihn sein eigener Schreibzugriff aus. Die Zuweisung steht **nach**
    // dem Schreibzugriff: Bricht der an der Indexpruefung ab, hat der Zugang nichts
    // hinterlassen und darf sich auch nichts merken.
    if (adresse == PLATZ_RUNDE) {
        hinterlassene_runde_ = wert;
    }
}

}  // namespace kern::zustand
