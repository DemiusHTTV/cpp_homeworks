import matplotlib.pyplot as plt
import numpy as np

np.set_printoptions(suppress=True, precision=6)

# CSV produced by ../classLine-List/main.cpp
# Columns: N,k,answer,time_list,time_vector

data = np.genfromtxt(
    "results.csv", delimiter=",", names=True, dtype=None, encoding=None
)

N = data["N"].astype(float)
time_list = data["time_list"].astype(float)
time_vector = data["time_vector"].astype(float)

# sort by N to draw nice connected lines
order = np.argsort(N)
N = N[order]
time_list = time_list[order]
time_vector = time_vector[order]


def power_law_fit(x, y):
    # time ~ C * N^p  =>  log10(time) = b + p*log10(N)
    lx = np.log10(x)
    ly = np.log10(y)
    p, b = np.polyfit(lx, ly, 1)
    return float(p), float(b)


def power_law_predict(b, p, x):
    return 10 ** (b + p * np.log10(x))


p_list, b_list = power_law_fit(N, time_list)
p_vec, b_vec = power_law_fit(N, time_vector)

mark_N = 4_000_000
N_new = np.logspace(np.log10(N.min()), np.log10(mark_N), 400)

pred_list = power_law_predict(b_list, p_list, N_new)
pred_vec = power_law_predict(b_vec, p_vec, N_new)

mark_list = float(power_law_predict(b_list, p_list, mark_N))
mark_vec = float(power_law_predict(b_vec, p_vec, mark_N))

print("Asymptotic fit (log-log power law):")
print(f"  LineList: time ~ C * N^{p_list:.3f}")
print(f"  Vector:   time ~ C * N^{p_vec:.3f}")
print()
print(f"Prediction at N={mark_N:,}:")
print(f"  LineList ~ {mark_list:.3f} s")
print(f"  Vector   ~ {mark_vec:.3f} s")

# Reference lines to make complexity visually obvious
# Scale them to pass through the first measured point.
N0 = N[0]
ref_on = time_list[0] * (N_new / N0) ** 1
ref_on2 = time_vector[0] * (N_new / N0) ** 2

plt.rcParams.update({"axes.titlesize": 11, "axes.labelsize": 10})
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

# 1) Measured: connect points so it's not "криво"
ax1.plot(N, time_list, "-o", label="LineList (measured)", linewidth=1.5)
ax1.plot(N, time_vector, "-o", label="Vector (measured)", linewidth=1.5)
ax1.set_xscale("log")
ax1.set_yscale("log")
ax1.set_xlabel("N")
ax1.set_ylabel("Time (s)")
ax1.set_title("Measured time (connected points, log-log)")
ax1.grid(True, which="both", linewidth=0.4, alpha=0.5)
ax1.legend()

# 2) Fit + prediction + reference complexities
ax2.plot(N_new, pred_list, color="tab:green", linewidth=2.0, label=f"LineList fit: N^{p_list:.2f}")
ax2.plot(N_new, pred_vec, color="tab:red", linewidth=2.0, label=f"Vector fit: N^{p_vec:.2f}")
ax2.scatter(N, time_list, color="tab:green", s=30, zorder=5)
ax2.scatter(N, time_vector, color="tab:red", s=30, zorder=5)

ax2.plot(N_new, ref_on, "--", color="0.35", linewidth=1.2, label="Reference: O(N)")
ax2.plot(N_new, ref_on2, "--", color="0.65", linewidth=1.2, label="Reference: O(N^2)")

ax2.scatter([mark_N], [mark_list], color="black", zorder=6)
ax2.annotate(
    f"{mark_list:.2f}s @ {mark_N/1_000_000:.0f}M",
    xy=(mark_N, mark_list),
    xytext=(0, 10),
    textcoords="offset points",
    ha="center",
    fontsize=9,
)

ax2.scatter([mark_N], [mark_vec], color="black", zorder=6)
ax2.annotate(
    f"{mark_vec:.0f}s @ {mark_N/1_000_000:.0f}M",
    xy=(mark_N, mark_vec),
    xytext=(0, -16),
    textcoords="offset points",
    ha="center",
    fontsize=9,
)

ax2.set_xscale("log")
ax2.set_yscale("log")
ax2.set_xlabel("N")
ax2.set_ylabel("Time (s)")
ax2.set_title("Asymptotic fit + prediction + O(N)/O(N^2) refs (log-log)")
ax2.grid(True, which="both", linewidth=0.4, alpha=0.5)
ax2.legend()

plt.tight_layout()
plt.savefig("josephus.png", dpi=180)
plt.show()
