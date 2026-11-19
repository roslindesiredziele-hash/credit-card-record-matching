# Credit Card Record Matching

A C++ project that reconstructs complete credit card records from two anonymized data dumps and compares matching approaches based on asymptotic complexity and empirical performance.

## Overview

Two CSV files contain partial information describing the same set of credit cards.

- Dump 1 stores the first 15 digits of each card number.
- Dump 2 stores the last 4 digits together with card metadata.
- Both dumps are ordered according to expiration date and PIN.

The objective is to reconstruct complete card records and evaluate two different matching approaches:

1. A Merge Sort based solution (`O(n log n)`).
2. A Counting Sort based solution (`O(n + k)`).

The project combines algorithm design, complexity analysis, benchmarking, and performance visualization.

---

## Dataset

Each record contains:

```cpp
struct CardRecord
{
    string cardNumber;
    string expiryDate;
    string verificationCode;
    string pin;
    string issuingNetwork;
};
```

Dataset size:

```text
20,000 records
```

---

## Implemented Algorithms

### Merge Sort Based Matching

Records are sorted using a custom Merge Sort implementation and then reconstructed.

Complexity:

```text
O(n log n)
```

---

### Counting Sort Based Matching

A composite key is constructed:

```cpp
CompositeKey = ExpiryKey * 10000 + PIN
```

where:

```cpp
ExpiryKey =
(year - 2024) * 12 + (month - 1)
```

Records are then sorted using a custom Counting Sort implementation.

Complexity:

```text
O(n + k)
```

where:

```text
k = 720000
```

Since the key space is fixed for this problem, the algorithm behaves linearly with respect to the input size.

---

## Benchmarking Methodology

Execution time was measured using:

```cpp
QueryPerformanceCounter()
```

from the Windows API.

Dataset sizes tested:

```text
5, 10, 15, 20, 25
30, 35, 40, 45, 50
60, 70, 80, 90, 100
200, 300, 400, 500, 600, 700, 800, 900, 1000
1200, 1400, 1600, 1800, 2000
```

Average execution times were recorded over multiple benchmark repetitions.

---

## Experimental Results

Benchmarking revealed three distinct performance regions:

- For small datasets (5-700 records), the Merge Sort based solution consistently outperformed the Counting Sort based solution.
- Around 800-900 records, both algorithms achieved comparable execution times.
- Beyond approximately 900 records, the Counting Sort based solution consistently outperformed Merge Sort.

The experimentally observed crossover point occurred at approximately:

```text
800-900 records
```

This behavior is explained by the fixed initialization cost of the Counting Sort implementation, which allocates a counting array containing 720,000 entries regardless of dataset size.

---

## Generated Figures

The benchmark results are visualized using:

- Small Inputs (5-100)
- Transition Region (500-1200)
- Large Inputs (1000-2000)
- Logarithmic Comparison (Full Dataset)

---

## Setup

### Prerequisites

- C++17 compatible compiler
- CMake 3.20+
- Python 3.13+ (for graph generation)

### Clone the Repository

```bash
git clone https://github.com/roslindesiredziele-hash/credit-card-record-matching.git
cd credit-card-record-matching
```

---

## Build (Windows)

### CMake

```bash
cmake -S . -B build
cmake --build build
```

### Manual Build

```bash
g++ src/main.cpp src/MatchingAlgorithms.cpp -o benchmark
```

---

## Usage

### Run the Benchmark

```bash
./benchmark.exe
```

The program:

1. Loads both card dumps.
2. Reconstructs the original card records.
3. Benchmarks the Merge Sort solution.
4. Benchmarks the Counting Sort solution.
5. Exports benchmark results.

Example output:

```text
Size: 100 | MergeSort: 0.96 ms | Linear: 9.82 ms
Size: 500 | MergeSort: 6.70 ms | Linear: 11.27 ms
Size: 1000 | MergeSort: 15.14 ms | Linear: 13.07 ms
```

---

### Benchmark Output

Results are automatically written to:

```text
data/data.csv
```

Format:

```csv
Size,MergeSortMs,LinearSortMs
5,0.020,9.860
10,0.055,10.706
...
```

---

### Generate Graphs

Install dependencies:

```bash
py -3.13 -m pip install pandas matplotlib
```

Run:

```bash
py -3.13 graph.py
```

Generated files:

```text
report/
├── small_inputs.png
├── transition_region.png
├── large_inputs.png
└── logarithmic_comparison.png
```

---

## Project Structure

```text
credit-card-record-matching
│
├── data/
│   ├── carddump1.csv
│   ├── carddump2.csv
│   └── data.csv
│
├── report/
│   ├── small_inputs.png
│   ├── transition_region.png
│   ├── large_inputs.png
│   └── logarithmic_comparison.png
│
├── src/
│   ├── CardRecord.h
│   ├── MatchingAlgorithms.h
│   ├── MatchingAlgorithms.cpp
│   └── main.cpp
│
├── graph.py
├── CMakeLists.txt
├── README.md
└── tests/
```

---

## Conclusion

Although the Counting Sort based solution has linear complexity, it incurs a significant constant overhead due to the initialization of a counting array containing 720,000 entries. Consequently, Merge Sort performs better for small datasets.

Experimental results show that the crossover point occurs at approximately 800-900 records. Beyond this threshold, the Counting Sort solution consistently outperforms Merge Sort, confirming the theoretical expectation that a linear-time algorithm eventually scales better than a log-linear algorithm for sufficiently large inputs.

The benchmark results demonstrate the importance of considering both asymptotic complexity and practical implementation costs when evaluating algorithm performance.

---

## Author

**Desire Roslin Dziele**  
Computer Science Student  
University of Łódź