// Deterministischer Festkomma-Weltschritt fuer die Stackmessung 0016.
// Freistehende Datei, keine Fremdbibliothek: rustc -O schritt.rs
//
// Ganzzahldivision und Rest schneiden in Rust gegen null ab -- genau die
// Vorgabe aus AUFGABE.md. Deshalb wird `/` und `%` unveraendert benutzt.

use std::time::Instant;

const N: usize = 64;
const SCHRITTE: u64 = 1_000_000;
const UNTERGRENZE: i64 = -1_000_000_000_000;
const OBERGRENZE: i64 = 1_000_000_000_000;

/// `a * b / c` ohne Ueberlauf im Zwischenergebnis (128 Bit),
/// gerundet auf halbe Betraege von null weg.
fn mal_geteilt(a: i64, b: i64, c: i64) -> i64 {
    let zaehler = (a as i128) * (b as i128);
    let nenner = c as i128;
    let negativ = (zaehler < 0) != (nenner < 0);
    let betrag_zaehler = if zaehler < 0 { -zaehler } else { zaehler };
    let betrag_nenner = if nenner < 0 { -nenner } else { nenner };
    // floor((|z| + |n|/2) / |n|), exakt auch bei ungeradem Nenner:
    let betrag = (2 * betrag_zaehler + betrag_nenner) / (2 * betrag_nenner);
    (if negativ { -betrag } else { betrag }) as i64
}

/// Begrenzt `x` auf `[unten, oben]`.
fn klemme(x: i64, unten: i64, oben: i64) -> i64 {
    if x < unten {
        unten
    } else if x > oben {
        oben
    } else {
        x
    }
}

/// Ein Weltschritt: `i` aufsteigend, an Ort und Stelle.
fn weltschritt(z: &mut [i64; N]) {
    for i in 0..N {
        let nachbar = z[(i + 17) % N];
        let roh = mal_geteilt(z[i], 9_512 + (nachbar % 977), 10_000);
        z[i] = klemme(
            roh + (nachbar / 1024) - (z[i] / 4096),
            UNTERGRENZE,
            OBERGRENZE,
        );
    }
}

/// `summe(z[i] * (i + 1))` mit Ueberlaufumbruch in 64 Bit.
fn pruefsumme(z: &[i64; N]) -> i64 {
    let mut summe: i64 = 0;
    for i in 0..N {
        summe = summe.wrapping_add(z[i].wrapping_mul(i as i64 + 1));
    }
    summe
}

fn main() {
    let mut z = [0i64; N];
    for i in 0..N {
        z[i] = 1_000_000 + (i as i64) * 37;
    }

    let start = Instant::now();
    for _ in 0..SCHRITTE {
        weltschritt(&mut z);
    }
    let nanosekunden = start.elapsed().as_nanos();

    println!("pruefsumme={}", pruefsumme(&z));
    println!(
        "nanosekunden_je_schritt={}",
        nanosekunden / (SCHRITTE as u128)
    );
    println!("zustand0={}", z[0]);
}
