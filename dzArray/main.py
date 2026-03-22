import matplotlib.pyplot as plt
import numpy as np

np.set_printoptions(suppress=True, precision=6)

data = np.genfromtxt("dzArray/josephus.csv", delimiter=",", names=True, dtype=None)
# Load data from CSV in the current directory
N = data["N"]
times = data["time"]

fig, (ax_l, ax_r) = plt.subplots(1, 2, figsize=(12, 6))

# Left plot: raw measurements
ax_l.plot(N, times, marker="o")
ax_l.set_xscale("log")
ax_l.set_xlabel("N")
ax_l.set_ylabel("Time (s)")
ax_l.set_title("Josephus Problem")

# Right plot: power-law fit (linear regression in log-log space) with prediction
logN = np.log10(N)
logT = np.log10(times)
slope, intercept = np.polyfit(logN, logT, 1)

N_new = np.logspace(np.log10(N.min()), np.log10(4_000_000), 300)
pred_time = 10 ** (intercept + slope * np.log10(N_new))

ax_r.plot(N_new, pred_time, color="red", label="Power-law fit")
ax_r.scatter(N, times, color="tab:blue", s=25, zorder=5, label="Measured")

mark_N = 4_000_000
mark_time = float(10 ** (intercept + slope * np.log10(mark_N)))
ax_r.scatter([mark_N], [mark_time], color="black", zorder=6)
ax_r.set_xscale("log")
ax_r.set_xlabel("N")
ax_r.set_ylabel("Time (s)")
ax_r.set_ylim(0, pred_time.max() * 1.05)
ax_r.legend()

plt.tight_layout()
plt.savefig("josephus.png")
plt.show() 
