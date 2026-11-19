import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("./data/data.csv")

plt.figure(figsize=(10, 6))

plt.plot(
    df["Size"],
    df["MergeSortMs"],
    marker="o",
    linewidth=2,
    label="Merge Sort O(n log n)"
)

plt.plot(
    df["Size"],
    df["LinearSortMs"],
    marker="s",
    linewidth=2,
    label="Counting Sort O(n)"
)

plt.xlabel("Dataset Size")
plt.ylabel("Average Execution Time (ms)")

plt.title(
    "Credit Card Record Matching Benchmark"
)

plt.grid(True)
plt.legend()

plt.tight_layout()

plt.savefig(
    "./data/benchmark.png",
    dpi=300
)

plt.show()