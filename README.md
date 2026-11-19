# Credit Card Record Matching

A C++ project that reconstructs complete credit card records from two anonymized data dumps and compares matching approaches based on asymptotic complexity.

## Overview

Two CSV files contain partial information about the same set of credit cards.

- Dump 1 stores the first 15 digits of each card number.
- Dump 2 stores the last 4 digits together with metadata.
- Both dumps are sorted according to expiration date and PIN.

The objective is to reconstruct the original card records and investigate the practical performance of:

1. A Merge Sort based solution (`O(n log n)`).
2. A Counting Sort based solution (`O(n)`).

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

## Implemented Algorithms

### Merge Sort Based Matching

Records are ordered using a custom Merge Sort implementation and then reconstructed.

Complexity:

```text
O(n log n)
```

### Counting Sort Based Matching

A composite key is constructed:

```cpp
CompositeKey =
ExpiryKey * 10000 + PIN
```

Records are then sorted using Counting Sort.

Complexity:

```text
O(n)
```

for the given bounded key space.

## Benchmarking Methodology

Execution time was measured using:

```cpp
QueryPerformanceCounter()
```

from the Windows API.

Dataset sizes:

```text
5–25
25–50
50–100
100–1000
1000–2000
```

Each benchmark was executed repeatedly and the average execution time was recorded.

## Experimental Results

The benchmark revealed:

- Merge Sort performs better for small datasets.
- Counting Sort incurs a fixed initialization overhead.
- Performance becomes comparable around 800–900 records.
- Counting Sort outperforms Merge Sort for larger datasets.

### Generated Figures

- `small_inputs.png`
- `transition_region.png`
- `large_inputs.png`
- `logarithmic_comparison.png`

## Build

```bash
g++ src/main.cpp src/MatchingAlgorithms.cpp -o benchmark
```

## Run

```bash
./benchmark.exe
```

## Generate Graphs

```bash
py -3.13 graph.py
```

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
└── README.md
```

## Conclusion

Although Counting Sort has linear complexity, its large counting array introduces a significant constant overhead. Experimental results show that Merge Sort is preferable for small inputs, while Counting Sort becomes superior once the dataset exceeds approximately 800–900 records. This confirms the expected theoretical complexity behavior.

## Author

**Desire Roslin Dziele**  
University of Łódź