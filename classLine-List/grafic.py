import matplotlib.pyplot as plt
import csv
import numpy as np
from scipy import stats

N_values = []
times = []

with open('results.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        N_values.append(int(row[0]))
        times.append(float(row[2]))

N_array = np.array(N_values)
times_array = np.array(times)

log_N = np.log(N_array)
log_times = np.log(times_array)

slope, intercept, r_value, p_value, std_err = stats.linregress(log_N, log_times)

N_future = np.array([2000000, 3000000, 5000000, 7000000, 10000000])
log_N_future = np.log(N_future)
log_t_predicted = slope * log_N_future + intercept
t_predicted = np.exp(log_t_predicted)

N_all = np.concatenate([N_array, N_future])
times_all = np.concatenate([times_array, t_predicted])

plt.figure(figsize=(12, 7))

plt.plot(N_array, times_array, 'bo-', linewidth=2, markersize=8, label='Фактические данные')
plt.plot(N_future, t_predicted, 'r--', linewidth=2, markersize=8, label='Прогноз')
plt.plot(N_future, t_predicted, 'rs', markersize=8)

plt.xlabel('N (количество элементов)', fontsize=12)
plt.ylabel('Время выполнения (секунды)', fontsize=12)
plt.title('Задача Иосифа Флавия: прогноз времени выполнения (k=2)', fontsize=14)
plt.grid(True, alpha=0.3)
plt.xscale('log')
plt.yscale('log')
plt.legend()

for i, (N, t) in enumerate(zip(N_array, times_array)):
    plt.annotate(f'{t:.3f}s', (N, t), xytext=(5, 5), textcoords='offset points', fontsize=8)

for i, (N, t) in enumerate(zip(N_future, t_predicted)):
    plt.annotate(f'{t:.1f}s', (N, t), xytext=(5, 5), textcoords='offset points', fontsize=8, color='red')

plt.show()
plt.savefig('classLine-List.png', dpi=300, bbox_inches='tight')

