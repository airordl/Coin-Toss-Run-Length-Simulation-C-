Coin Toss Run-Length Simulation (C++)

This project simulates a large number of coin tosses and analyzes the probability distribution of consecutive 
identical outcomes (streaks of heads or tails). The data is then fitted to an exponential decay model 
and compared against the theoretical expectation for a fair coin.

Files:
- cointoss_.C – Main C++ source file. Simulates 100 million coin tosses, tracks streaks, fits data.
- a.out – Compiled binary (if created via g++).
- coin.txt – Output file with formatted simulation data (e.g., for plotting or LaTeX use).

How to Compile and Run:
Compile with: g++ -O2 -o cointoss cointoss_.C
Then run: ./cointoss

What It Does:
- Simulates 100,000,000 coin tosses.
- Counts how many times streaks of length 0 to 49 occur.
- Normalizes these counts into probabilities.
- Fits the distribution to an exponential model: P(n) ≈ A * exp(-B * n)
- Compares the result to the ideal analytical distribution: P(n) = 0.5 * (0.5)^n
- Prints the results to terminal and writes a LaTeX-friendly table to coin.txt

Output Example (Terminal):
3 - 7.32%,        p(<4) = 92.57%,        p(>3) = 7.43%
...
best fit: 0.4998 * exp(-0.6931 * n)

