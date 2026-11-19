import pandas as pd
import matplotlib.pyplot as plt

# Read benchmark results
df = pd.read_csv("./data/data.csv")

# Graph definitions from lecturer
ranges = [
    ("graph_5_25.png",      5,    25),
    ("graph_25_50.png",    25,    50),
    ("graph_50_100.png",   50,   100),
    ("graph_100_1000.png", 100, 1000),
    ("graph_1000_2000.png",1000,2000)
]

for filename, lower, upper in ranges:

    part = df[
        (df["Size"] >= lower)
        &
        (df["Size"] <= upper)
    ]

    plt.figure(figsize=(10, 6))

    plt.plot(
        part["Size"],
        part["MergeSortMs"],
        marker="o",
        linewidth=2,
        label="Merge Sort O(n log n)"
    )

    plt.plot(
        part["Size"],
        part["LinearSortMs"],
        marker="s",
        linewidth=2,
        label="Counting Sort O(n)"
    )

    plt.xlabel("Number of Records")
    plt.ylabel("Average Execution Time [ms]")

    plt.title(
        f"Benchmark Comparison ({lower}-{upper} records)"
    )

    plt.grid(True)
    plt.legend()

    plt.tight_layout()

    plt.savefig(
        filename,
        dpi=300
    )

    plt.close()

print("All graphs generated successfully.")
