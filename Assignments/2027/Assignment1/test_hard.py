"""Standalone benchmark script for testing ex1.py against hard_problems.txt.

Usage:
    python3 test_hard.py                # Run all problems in hard_problems.txt (30s limit)
    python3 test_hard.py --limit 60     # Use a custom time limit in seconds
    python3 test_hard.py --max 10       # Run only the first 10 problems
"""

import argparse
import ast
from pathlib import Path
import time

import ex1_check


DEFAULT_FILE = Path(__file__).resolve().parent / "hard_problems.txt"
DEFAULT_LIMIT = 100


def load_problems(path):
    """Parse all problem dictionaries from hard_problems.txt."""
    problems = []
    with open(path, "r", encoding="utf-8") as handle:
        for line_no, raw_line in enumerate(handle, start=1):
            line = raw_line.strip()
            if not line or line.startswith("#"):
                continue
            try:
                entry = ast.literal_eval(line)
            except Exception as exc:
                raise ValueError(
                    f"Failed to parse {path} line {line_no}: {exc}"
                ) from exc
            problems.append(entry)
    return problems


def format_cost_comparison(my_cost, expected_cost):
    """Return an explicit comparison string between solver cost and expected cost."""
    if my_cost == expected_cost:
        return f"my_cost ({my_cost}) == expected_cost ({expected_cost})"
    if my_cost > expected_cost:
        return f"my_cost ({my_cost}) > expected_cost ({expected_cost})"
    return f"my_cost ({my_cost}) < expected_cost ({expected_cost})"


def main():
    parser = argparse.ArgumentParser(
        description="Benchmark ex1.py against all problems in hard_problems.txt."
    )
    parser.add_argument(
        "--file",
        type=Path,
        default=DEFAULT_FILE,
        help="Path to the problem file (default: hard_problems.txt).",
    )
    parser.add_argument(
        "--limit",
        type=float,
        default=DEFAULT_LIMIT,
        help="Per-problem time limit in seconds (default: 100).",
    )
    parser.add_argument(
        "--max",
        dest="max_problems",
        type=int,
        default=None,
        help="Optional cap on the number of problems to run.",
    )
    args = parser.parse_args()

    problems = load_problems(args.file)
    if args.max_problems is not None:
        problems = problems[: args.max_problems]

    print(
        f"Loaded {len(problems)} problems from {args.file.name} "
        f"(limit={args.limit:.1f}s)",
        flush=True,
    )

    counts = {
        "PASS": 0,
        "MISMATCH": 0,
        "TIMEOUT": 0,
        "ERROR/ILLEGAL": 0,
    }
    mismatches = []
    solved_timings = []

    suite_t0 = time.perf_counter()

    for entry in problems:
        name = str(entry["name"])
        game = entry["game"]
        expected_cost = entry["cost"]
        ref_seconds = entry.get("seconds")
        ref_str = f"{ref_seconds:.1f}s" if ref_seconds is not None else "n/a"

        t0 = time.perf_counter()
        result = ex1_check.solve(game, args.limit)
        wall_elapsed = time.perf_counter() - t0
        elapsed = result["seconds"] if "seconds" in result else wall_elapsed

        verdict, why = ex1_check.judge(game, result, expected_cost)

        if verdict == "PASS":
            status = "PASS"
            my_cost = result["cost"]
            detail = f"{format_cost_comparison(my_cost, expected_cost)} | ref={ref_str}"
            solved_timings.append((elapsed, name, my_cost, ref_str))
        elif verdict == "WRONG COST":
            status = "MISMATCH"
            my_cost = result["cost"]
            detail = f"{format_cost_comparison(my_cost, expected_cost)} | ref={ref_str}"
            mismatches.append((name, my_cost, expected_cost, elapsed))
            solved_timings.append((elapsed, name, my_cost, ref_str))
        elif verdict == "TIMEOUT":
            status = "TIMEOUT"
            detail = f"expected_cost={expected_cost} | ref={ref_str} | {why}"
        else:
            status = "ERROR/ILLEGAL"
            last_line = why.strip().splitlines()[-1] if why.strip() else verdict
            detail = (
                f"expected_cost={expected_cost} | ref={ref_str} | "
                f"{verdict}: {last_line}"
            )

        counts[status] += 1
        print(
            f"[{name:>3}] {status:<13s} {elapsed:6.2f}s | {detail}",
            flush=True,
        )

    total_runtime = time.perf_counter() - suite_t0

    print("\n=== SUMMARY ===", flush=True)
    print(
        f"Total: {len(problems)} | "
        f"PASS: {counts['PASS']} | "
        f"MISMATCH: {counts['MISMATCH']} | "
        f"TIMEOUT: {counts['TIMEOUT']} | "
        f"ERROR/ILLEGAL: {counts['ERROR/ILLEGAL']}",
        flush=True,
    )
    print(f"Total runtime: {total_runtime:.2f}s", flush=True)

    if mismatches:
        print("\nMismatched problems:", flush=True)
        for name, my_cost, expected_cost, elapsed in mismatches:
            cmp_str = format_cost_comparison(my_cost, expected_cost)
            print(f"  - [{name}] {cmp_str} ({elapsed:.2f}s)", flush=True)
    else:
        print("\nMismatched problems: None", flush=True)

    if solved_timings:
        top5 = sorted(solved_timings, key=lambda item: item[0], reverse=True)[:5]
        print("\nTop 5 slowest solved problems:", flush=True)
        for rank, (elapsed, name, my_cost, ref_str) in enumerate(top5, start=1):
            print(
                f"  {rank}. [{name:>3}] {elapsed:6.2f}s "
                f"(cost={my_cost}, ref={ref_str})",
                flush=True,
            )


if __name__ == "__main__":
    main()
