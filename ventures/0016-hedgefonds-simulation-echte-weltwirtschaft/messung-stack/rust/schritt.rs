// Deterministischer Festkomma-Weltschritt, Messung des Stacks fuer 0016.
// Freistehend, uebersetzt mit `rustc -O schritt.rs`. Kein Gleitkommatyp.

use std::time::Instant;

const N: usize = 64;
const SCHRITTE: u64 = 1_000_000;
const UNTEN: i64 = 0;
const OBEN: i64 = 1_000_000_000_000;

/// a * b / c ohne Ueberlauf im Zwischenergebnis (128 Bit),
/// gerundet auf halbe Betraege von null weg.
fn mal_geteilt(a: i64, b: i64, c: i64) -> i64 {
    let zaehler = (a as i128) * (b as i128);
    let nenner = c as i128;
    let mut q = zaehler / nenner; // schneidet gegen null ab
    let rest = zaehler % nenner; // traegt das Vorzeichen des Zaehlers
    let betrag_rest = if rest < 0 { -rest } else { rest };
    let betrag_nenner = if nenner < 0 { -nenner } else { nenner };
    if betrag_rest * 2 >= betrag_nenner {
        // vom Nullpunkt weg: Vorzeichen des echten Quotienten
        if (rest < 0) != (nenner < 0) {
            q -= 1;
        } else {
            q += 1;
        }
    }
    q as i64
}

/// begrenzt x auf [u, o]
fn klemme(x: i64, u: i64, o: i64) -> i64 {
    if x < u {
        u
    } else if x > o {
        o
    } else {
        x
    }
}

/// Ein Weltschritt, i aufsteigend, an Ort und Stelle.
fn weltschritt(z: &mut [i64; N]) {
    for i in 0..N {
        let nachbar = z[(i + 17) % N];
        let alt = z[i];
        let roh = mal_geteilt(alt, 10_000 + (nachbar % 977), 10_000);
        z[i] = klemme(roh + (nachbar / 1024) - (alt / 4096), UNTEN, OBEN);
    }
}

fn main() {
    let mut z = [0i64; N];
    for i in 0..N {
        z[i] = 1_000_000 + (i as i64) * 37;
    }

    let beginn = Instant::now();
    for _ in 0..SCHRITTE {
        weltschritt(&mut z);
    }
    let dauer_ns: u128 = beginn.elapsed().as_nanos();

    let mut pruefsumme: i64 = 0;
    for i in 0..N {
        pruefsumme = pruefsumme.wrapping_add(z[i].wrapping_mul((i as i64) + 1));
    }
    let pruefsumme = pruefsumme % i64::MAX; // 2^63 - 1

    println!("pruefsumme={}", pruefsumme);
    println!("nanosekunden_je_schritt={}", dauer_ns / (SCHRITTE as u128));
    println!("zustand0={}", z[0]);
}
