import subprocess, sys, os

V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
S = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft"
EXE = os.path.abspath(V + "/werkzeuge/belegstellen/bau/belegstellen_riegel")


def lauf(wurzel_v, wurzel_s):
    r = subprocess.run([EXE, wurzel_v, wurzel_s], capture_output=True)
    return r.returncode, r.stdout.decode("utf-8", "replace"), r.stderr.decode("utf-8", "replace")


if __name__ == "__main__":
    rc, out, err = lauf(os.path.abspath(V), os.path.abspath(S))
    print("RC =", rc)
    print("===== STDOUT =====")
    print(out)
    print("===== STDERR =====")
    print(err)
