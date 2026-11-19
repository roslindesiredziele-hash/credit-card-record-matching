import pandas as pd
import matplotlib.pyplot as plt

# Load benchmark data
df = pd.read_csv("./data/data.csv")

# Empirical crossover point
CROSSOVER_X = 850

graphs = [
    ("report/small_inputs.png", 5, 100,
     "Small Inputs (5-100)"),

    ("report/transition_region.png", 500, 1200,
     "Transition Region (500-1200)"),

    ("report/large_inputs.png", 1000, 2000,
     "Large Inputs (1000-2000)")
]

for filename, low, high, title in graphs:

    subset = df[
        (df["Size"] >= low) &
        (df["Size"] <= high)
    ]

    plt.figure(figsize=(10, 6))

    plt.plot(
        subset["Size"],
        subset["MergeSortMs"],
        marker="o",
        linewidth=2,
        markersize=6,
        label="Merge Sort O(n log n)"
    )

    plt.plot(
        subset["Size"],
        subset["LinearSortMs"],
        marker="s",
        linewidth=2,
        markersize=6,
        label="Counting Sort O(n)"
    )

    # Show crossover marker only if visible
    if low <= CROSSOVER_X <= high:
        plt.axvline(
            x=CROSSOVER_X,
            color="red",
            linestyle="--",
            linewidth=2,
            label="Observed crossover (~850)"
        )

    plt.title(title)
    plt.xlabel("Dataset Size (records)")
    plt.ylabel("Average Execution Time (ms)")
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.legend()

    plt.tight_layout()
    plt.savefig(filename, dpi=300)
    plt.close()

# ======================
# Logarithmic comparison
# ======================

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

plt.axvline(
    x=CROSSOVER_X,
    color="red",
    linestyle="--",
    linewidth=2,
    label="Observed crossover (~850)"
)

plt.yscale("log")

plt.title(
    "Performance Comparison (Logarithmic Scale)"
)

plt.xlabel("Dataset Size (records)")
plt.ylabel("Execution Time (ms, log scale)")

plt.grid(True, which="both",
         linestyle="--",
         alpha=0.5)

plt.legend()

plt.tight_layout()

plt.savefig(
    "report/logarithmic_comparison.png",
    dpi=300
)

plt.close()

print("Generated:")
print("  report/small_inputs.png")
print("  report/transition_region.png")
print("  report/large_inputs.png")
print("  report/logarithmic_comparison.png")