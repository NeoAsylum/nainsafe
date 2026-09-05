import java.math.BigInteger;

/**
 * Deterministischer Festkomma-Weltschritt, Messfassung fuer den Stackvergleich.
 *
 * Ganzzahlarithmetik durchgehend, kein Gleitkommatyp -- auch nicht in der
 * Zeitmessung. Java rundet die Ganzzahldivision und den Restoperator gegen null
 * ab; das ist genau die von der Aufgabe verlangte Abschneiderichtung.
 */
public final class Schritt {

    private static final int N = 64;
    private static final int SCHRITTE = 1_000_000;
    private static final long UNTERE_GRENZE = -1_000_000_000_000L;
    private static final long OBERE_GRENZE = 1_000_000_000_000L;
    private static final long NENNER = 10_000L;

    private Schritt() {
    }

    public static void main(String[] args) {
        long[] z = new long[N];
        for (int i = 0; i < N; i++) {
            z[i] = 1_000_000L + (long) i * 37L;
        }

        long begonnen = System.nanoTime();
        for (int s = 0; s < SCHRITTE; s++) {
            weltschritt(z);
        }
        long gedauert = System.nanoTime() - begonnen;

        System.out.println("pruefsumme=" + pruefsumme(z));
        System.out.println("nanosekunden_je_schritt=" + gedauert / SCHRITTE);
        System.out.println("zustand0=" + z[0]);
    }

    /** Ein Weltschritt, i aufsteigend, an Ort und Stelle. */
    private static void weltschritt(long[] z) {
        for (int i = 0; i < N; i++) {
            long nachbar = z[(i + 17) & (N - 1)];
            long alt = z[i];
            long roh = malGeteilt(alt, 9_512L + nachbar % 977L, NENNER);
            z[i] = klemme(roh + nachbar / 1024L - alt / 4096L, UNTERE_GRENZE, OBERE_GRENZE);
        }
    }

    /**
     * a * b / c ohne Ueberlauf im Zwischenergebnis, gerundet auf halbe Betraege
     * von null weg. c ist positiv.
     *
     * Passt das Produkt in 64 Bit -- was bei geklemmtem Zustand immer der Fall
     * ist --, laeuft der schnelle Weg; sonst rechnet BigInteger die vollen
     * 128 Bit. Die Erkennung vergleicht das hohe Wort mit der Vorzeichenmaske
     * des niedrigen.
     */
    private static long malGeteilt(long a, long b, long c) {
        long tief = a * b;
        long hoch = Math.multiplyHigh(a, b);
        if (hoch == (tief >> 63)) {
            return geteiltGerundet(tief, c);
        }
        BigInteger produkt = BigInteger.valueOf(a).multiply(BigInteger.valueOf(b));
        BigInteger nenner = BigInteger.valueOf(c);
        BigInteger betrag = produkt.abs();
        BigInteger ganz = betrag.divide(nenner);
        BigInteger rest = betrag.subtract(ganz.multiply(nenner));
        if (rest.shiftLeft(1).compareTo(nenner) >= 0) {
            ganz = ganz.add(BigInteger.ONE);
        }
        if (produkt.signum() < 0) {
            ganz = ganz.negate();
        }
        return ganz.longValueExact();
    }

    /** n / c auf halbe Betraege von null weg gerundet, c positiv. */
    private static long geteiltGerundet(long n, long c) {
        long betrag = n < 0 ? -n : n;
        long ganz = betrag / c;
        long rest = betrag - ganz * c;
        if (rest >= c - rest) {
            ganz++;
        }
        return n < 0 ? -ganz : ganz;
    }

    private static long klemme(long x, long unten, long oben) {
        if (x < unten) {
            return unten;
        }
        if (x > oben) {
            return oben;
        }
        return x;
    }

    /** summe(z[i] * (i + 1)) mit Ueberlaufumbruch, danach mod 2^63 - 1. */
    private static long pruefsumme(long[] z) {
        long summe = 0L;
        for (int i = 0; i < N; i++) {
            summe += z[i] * (long) (i + 1);
        }
        return summe % Long.MAX_VALUE;
    }
}
