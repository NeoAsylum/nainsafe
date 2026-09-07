#!/usr/bin/env python3
"""Compile the wall boundary instead of deriving it -- package 0212.

`PARTIELAENGE_HOECHSTENS` in `kern/include/kern/verlauf.hpp` is the wall T40 draws over
the length of a game. Four `static_assert` move with it. Three of them stand in that same
header; the binding one does not. It is the chain-leaf assertion in
`kern/include/kern/zustandsausgabe.hpp`:

    static_assert(sizeof(Kettenblatt) < verlauf::STAPEL_JE_FADEN, ...)

Where it breaks was, until today, a derivation: a size law of 59.520 times the wall plus
119.840 byte, fitted through the three walls anybody ever compiled -- 26, 482, 483. The
header says in as many words that walls 138 and 139 have never been compiled by anyone.
No agent has a shell, so nobody could compile them either. This script does, every night,
as a `ctest` entry.

Three cases, one compilation each:

  A  wall 138, headers untouched          -> green
  B  wall 139, headers untouched          -> red, and what broke is the chain-leaf
                                             assertion, not one of the three in
                                             `verlauf.hpp`
  C  wall 139, chain-leaf assertion off   -> green

C is the bait test. Without it a red B would also be scored a success when the throwaway
copy is broken for some entirely unrelated reason -- and a measurement that cannot tell
those two apart measures nothing.

**Nothing is built beyond what triggers the assertions.** All four sit in headers, so one
translation unit with `-fsyntax-only` reaches every one of them: no object file, no
library, no probe, no `cmake`. That is what keeps the entry cheap enough to run twice a
night, once from the workspace and once from the core-alone build.

**Nothing is derived here.** 138 and 139 stand below as a claim, not as a computed value.
A measurement that produces its own expectation from the same law it is meant to check
would be green forever.

Exit codes:

  2  an instrument without a measurement -- an input is missing, an anchor is gone, the
     compiler will not run. Nothing was measured.
  1  a finding -- a case came out other than expected. The boundary has moved, and the
     measured one is printed below so a follow-up package can write it into the header
     the next day instead of spending another night finding it.
  0  all three cases as expected.

English in a German tree, and that is the house rule rather than an oversight: CLAUDE.md
asks for English in anything authored from 2026-09-06 on and makes an exception for
continuing a German document. This file continues none -- `kern/CMakeLists.txt`, which
does, keeps its German. The German wordings quoted below stay German, because quoting is
not translating: they are what the compiler prints, and a translated needle would find
nothing.
"""

import argparse
import hashlib
import pathlib
import re
import shutil
import subprocess
import sys
import tempfile
import time

# The two claims under test. Neither is computed -- see the head.
LAST_GREEN_WALL = 138
FIRST_RED_WALL = 139

# The anchors. Searched by wording and never by position: the file they sit in is being
# worked on by other packages, and a position moves under a comment that somebody adds.
WALL_PATTERN = re.compile(
    r"^inline constexpr std::size_t PARTIELAENGE_HOECHSTENS = (\d+);$", re.MULTILINE)
LEAF_ASSERT = "static_assert(sizeof(Kettenblatt) < verlauf::STAPEL_JE_FADEN,"
LEAF_ASSERT_OFF = "static_assert(true,"

# The wording case B must carry, and the three it must not. Substrings rather than whole
# messages: what g++ prints is the concatenated string literal, and a short needle
# survives somebody reflowing the source it is spelled across.
LEAF_WORDING = "ein Kettenblatt lebt auf dem Stapel des Aufrufers"
VERLAUF_WORDINGS = (
    ("the T40 capacity assertion", "eine weitere passt nicht mehr hinein"),
    ("the T19 stack assertion", "ein Verlauf ist groesser als der Stapel eines Fadens"),
    ("the carrier assertion", "der Verlauf traegt seine Ketten selbst"),
)

TRANSLATION_UNIT = """// Written by kern/messung/wandschranke.py. Never edited by hand.
//
// One include reaches all four assertions that move with the wall: the three in
// kern/verlauf.hpp and the chain-leaf one in kern/zustandsausgabe.hpp, which includes
// the former. Nothing here is meant to run -- it is compiled for syntax only.
#include "kern/zustandsausgabe.hpp"
"""

# The bisection range, used only after a deviation. Wall 1 must be green and wall 4096
# must be red; both are verified rather than assumed, and a boundary outside the range is
# reported as such instead of being silently pinned to an end.
SEARCH_LOW = 1
SEARCH_HIGH = 4096


class NoObject(Exception):
    """Raised where the measurement lost its object -- never where it has a verdict."""


# ---------------------------------------------------------------------------
# The two mutators, and the self-test that keeps them honest
# ---------------------------------------------------------------------------


def replace_once(text, needle, replacement, where):
    """A needle that occurs twice mutates the wrong place; one that occurs never mutates
    nothing and leaves every case below green."""
    found = text.count(needle)
    if found != 1:
        raise NoObject("the anchor %r occurs %d times in %s, expected exactly once"
                       % (needle[:48], found, where))
    return text.replace(needle, replacement)


def set_wall(text, wall, where):
    """Force the wall and hand back the value it had, so the output can name it."""
    found = WALL_PATTERN.findall(text)
    if len(found) != 1:
        raise NoObject("the wall declaration occurs %d times in %s, expected exactly once"
                       % (len(found), where))
    line = "inline constexpr std::size_t PARTIELAENGE_HOECHSTENS = %d;" % wall
    return WALL_PATTERN.sub(line, text), int(found[0])


def self_test():
    """Six cases on the two mutators, before anything is compiled and at no cost.

    This is the only place where the measurement can notice that its object has wandered
    off. It is here because exactly that happened elsewhere in this tree: a counter-probe
    measured four of its five mutants against wording that had moved, and stayed green
    for months. A mutator that quietly matches nothing is indistinguishable from one that
    works.
    """
    wall_line = "inline constexpr std::size_t PARTIELAENGE_HOECHSTENS = 26;"
    done = []

    def refuses(name, thunk):
        try:
            thunk()
        except NoObject:
            done.append(name + " -> refused")
            return
        raise NoObject("self-test: %s went through, expected a refusal" % name)

    refuses("replace_once with no match",
            lambda: replace_once("a b c", "x", "y", "self-test"))
    refuses("replace_once with two matches",
            lambda: replace_once("x a x", "x", "y", "self-test"))
    refuses("set_wall with no match",
            lambda: set_wall("nothing to find here\n", 7, "self-test"))
    refuses("set_wall with two matches",
            lambda: set_wall(wall_line + "\n" + wall_line + "\n", 7, "self-test"))

    if replace_once("a x b", "x", "y", "self-test") != "a y b":
        raise NoObject("self-test: replace_once did not replace its single match")
    done.append("replace_once with one match -> replaced")

    text, old = set_wall(wall_line + "\n", 7, "self-test")
    if old != 26 or "PARTIELAENGE_HOECHSTENS = 7;" not in text:
        raise NoObject("self-test: set_wall did not rewrite its single match, and read "
                       "back %r as the old wall" % old)
    done.append("set_wall with one match -> rewritten, old value read back")

    return done


# ---------------------------------------------------------------------------
# One case: a throwaway copy, one compilation
# ---------------------------------------------------------------------------


def build_tree(headers, target, wall, leaf_assert_on):
    """Copy the headers, force the wall, write the translation unit.

    The source tree is read and never written. That is house rule 3 and it is also the
    only way this can run in a nightly build: a measurement that edits its own object
    leaves the next agent a dirty tree when it dies halfway.
    """
    include = target / "include"
    shutil.copytree(headers, include)

    verlauf = include / "kern" / "verlauf.hpp"
    text, old_wall = set_wall(verlauf.read_text(encoding="utf-8"), wall, "verlauf.hpp")
    verlauf.write_text(text, encoding="utf-8")

    if not leaf_assert_on:
        ausgabe = include / "kern" / "zustandsausgabe.hpp"
        ausgabe.write_text(
            replace_once(ausgabe.read_text(encoding="utf-8"),
                         LEAF_ASSERT, LEAF_ASSERT_OFF, "zustandsausgabe.hpp"),
            encoding="utf-8")

    unit = target / "wandschranke.cpp"
    unit.write_text(TRANSLATION_UNIT, encoding="utf-8")
    return include, unit, old_wall


def compile_unit(compiler, include, unit):
    """Syntax only -- see the head for why that reaches every assertion.

    `-fwrapv` changes nothing for a `static_assert`. It is passed anyway so that nobody
    has to argue whether the measurement ran under different arithmetic than the core
    does.

    **Without the Warnsatz, and on purpose.** It carries `-Werror`, and under it any
    unrelated warning would decide the verdict of a case. This entry measures four
    assertions, not the warning set; that one is held by the Warnsatz-Schlussriegel over
    every translating target, and this unit is none.
    """
    command = [compiler, "-std=c++20", "-fwrapv", "-fsyntax-only",
               "-I", str(include), str(unit)]
    start = time.monotonic()
    try:
        finished = subprocess.run(command, capture_output=True, text=True)
    except OSError as failure:
        raise NoObject("the compiler %r will not run: %s" % (compiler, failure))
    return (finished.returncode, finished.stdout + finished.stderr,
            time.monotonic() - start)


def run_case(compiler, headers, wall, leaf_assert_on):
    """A scratch directory per case, unique by construction.

    Not under the build tree, and that is the difference to `schlussriegel_nachbau`: this
    manifest is read by two build trees, so both run this entry every night. A fixed path
    would have them share one scratch directory. Nothing executable is produced, so a
    `noexec` temp directory is no obstacle either.
    """
    with tempfile.TemporaryDirectory(prefix="wandschranke-") as folder:
        include, unit, old_wall = build_tree(
            headers, pathlib.Path(folder), wall, leaf_assert_on)
        code, output, seconds = compile_unit(compiler, include, unit)
    return code, output, seconds, old_wall


def diagnostics(output):
    """What a reader of a red night needs verbatim, and none of the rest."""
    return [line.strip() for line in output.splitlines()
            if "error:" in line or "static assertion failed" in line]


# ---------------------------------------------------------------------------
# Only after a deviation: where is the boundary really?
# ---------------------------------------------------------------------------


def find_boundary(compiler, headers):
    """Bisect for the smallest wall that does not compile.

    Reached only when a case above came out other than expected -- that is, when the
    boundary has moved. Package 0212 asks for the measured number to stand in the output
    in so many words, so that a follow-up package can write it into the header the next
    day. Without this, a red night says only that 139 was not red and costs another night
    to find out where it is.

    The range and the cost are printed rather than assumed: a silent cap reads like
    "searched everywhere" when it was not.
    """
    budget = 2 + (SEARCH_HIGH - SEARCH_LOW).bit_length()
    print("\nboundary search: bisecting walls %d..%d, at most %d compilations"
          % (SEARCH_LOW, SEARCH_HIGH, budget))

    code, output, _, _ = run_case(compiler, headers, SEARCH_LOW, True)
    if code != 0:
        print("  wall %d is already red -- the boundary lies below the searched range"
              % SEARCH_LOW)
        for line in diagnostics(output):
            print("    | " + line)
        return
    code, red_output, _, _ = run_case(compiler, headers, SEARCH_HIGH, True)
    if code == 0:
        print("  wall %d is still green -- the boundary lies above the searched range"
              % SEARCH_HIGH)
        return

    low, high, compilations = SEARCH_LOW, SEARCH_HIGH, 2
    while high - low > 1:
        middle = (low + high) // 2
        code, output, _, _ = run_case(compiler, headers, middle, True)
        compilations += 1
        print("  wall %d -> %s" % (middle, "green" if code == 0 else "red"))
        if code == 0:
            low = middle
        else:
            high, red_output = middle, output

    print("  MEASURED BOUNDARY: wall %d is the last green one, wall %d the first red "
          "one (%d compilations). The header derives %d and %d."
          % (low, high, compilations, LAST_GREEN_WALL, FIRST_RED_WALL))
    for line in diagnostics(red_output):
        print("    | " + line)


# ---------------------------------------------------------------------------


def fingerprint(path):
    """Which stand of the header was measured -- the question a red night raises first."""
    return hashlib.sha256(path.read_bytes()).hexdigest()[:16]


CASES = (
    ("A", LAST_GREEN_WALL, True, "green",
     "the last wall the header derives as green"),
    ("B", FIRST_RED_WALL, True, "red",
     "the first wall the header derives as red"),
    ("C", FIRST_RED_WALL, False, "green",
     "bait test -- the same wall with the chain-leaf assertion switched off"),
)


def main():
    parser = argparse.ArgumentParser(description="Compile the wall boundary (0212).")
    parser.add_argument("--uebersetzer", required=True,
                        help="the C++ compiler, handed down by CMake as "
                             "CMAKE_CXX_COMPILER -- never built into this script, or it "
                             "would be a second compiler beside the one the core is "
                             "built with")
    parser.add_argument("--koepfe", required=True,
                        help="the include root of the core, that is kern/include")
    argument = parser.parse_args()

    compiler = argument.uebersetzer
    headers = pathlib.Path(argument.koepfe)

    print("wandschranke -- package 0212")
    print("  compiler: %s" % compiler)
    print("  headers : %s" % headers)
    for name in ("verlauf.hpp", "zustandsausgabe.hpp"):
        header = headers / "kern" / name
        if not header.is_file():
            raise NoObject("the header kern/%s is missing under %s" % (name, headers))
        print("    kern/%-20s sha256 %s" % (name, fingerprint(header)))

    for line in self_test():
        print("  self-test: %s" % line)

    # Read-only, and deliberately first: it fails with code 2 if the anchor is gone,
    # before three compilations are spent on a copy that was never mutated.
    _, wall_today = set_wall(
        (headers / "kern" / "verlauf.hpp").read_text(encoding="utf-8"), 0, "verlauf.hpp")
    print("  the tree carries wall %d today; the cases force their own and leave it "
          "alone" % wall_today)

    deviations = 0
    seconds_total = 0.0
    for name, wall, leaf_assert_on, expected, purpose in CASES:
        code, output, seconds, _ = run_case(compiler, headers, wall, leaf_assert_on)
        seconds_total += seconds
        verdict = "green" if code == 0 else "red"
        print("\ncase %s -- wall %d%s -- %s"
              % (name, wall, "" if leaf_assert_on else ", chain-leaf assertion off",
                 purpose))
        print("  expected %s, the compiler says %s (code %d, %.1f s)"
              % (expected, verdict, code, seconds))

        if verdict == "red":
            for line in diagnostics(output):
                print("    | " + line)

        if verdict != expected:
            print("  DEVIATION: case %s is %s, expected %s" % (name, verdict, expected))
            deviations += 1
        elif name == "B":
            # Only worth asking once B is red for the right reason: red alone would also
            # be the verdict on a copy that does not compile for some other cause.
            if LEAF_WORDING not in output:
                print("  DEVIATION: the red build does not name the chain-leaf "
                      "assertion -- expected the wording %r" % LEAF_WORDING)
                deviations += 1
            for label, wording in VERLAUF_WORDINGS:
                if wording in output:
                    print("  DEVIATION: what broke is %s in verlauf.hpp, not the "
                          "chain-leaf one" % label)
                    deviations += 1

    print("\nwall %d expected green, wall %d expected red -- %d deviation(s), %.1f s "
          "compiling" % (LAST_GREEN_WALL, FIRST_RED_WALL, deviations, seconds_total))

    if deviations:
        find_boundary(compiler, headers)
    return 1 if deviations else 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except NoObject as failure:
        print("wandschranke: no measurement -- %s" % failure)
        sys.exit(2)
