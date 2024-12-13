# gpu = [0.032983, 0.049000, 0.081636, 0.147070, 0.286343, 0.555099, 1.107961, 4.442266]
# cpu = [1.0928, 0.5958, 0.6652, 1.6599, 3.3655, 12.7233, 48.9732, 195.9965]

# for i in range(len(gpu)):
#     print(f'{cpu[i]:.4f} {gpu[i]:.4f} {cpu[i]/gpu[i]:.4f}')

# def convert_mbs_to_gibs(mbs):
#     GIB_TO_MB_RATIO = 1024  # 1 GiB = 1024 MB
#     gibs = mbs / GIB_TO_MB_RATIO
#     return gibs

# # Example usage
# if __name__ == "__main__":
#     while True:
#       mbs_input = float(input("Enter the speed in MB/s: "))
#       gibs_output = convert_mbs_to_gibs(mbs_input)
#       print(f"{mbs_input} MB/s is equivalent to {gibs_output:.6f} GiB/s.")
#       print('---------------------------------')

import matplotlib.pyplot as plt
import numpy as np

# Data
N = [4096, 8192, 12288, 16384, 20480, 24576, 28672, 32768, 36864, 40960, 45056, 49152, 53248, 57344, 61440, 65536, 69632, 73728, 77824, 81920]
CPU = [0.492139, 1.471328, 2.478942, 3.386801, 5.059240, 7.112179, 9.892856, 12.59829, 15.54297, 19.36099, 23.48723, 27.69359, 32.63063, 37.43660, 42.85863, 49.46104, 55.14939, 62.04446, 69.26138, 76.60071]
Step_0 = [0.081679, 0.158931, 0.235794, 0.333549, 0.417726, 0.499557, 0.599185, 0.688993, 0.774345, 0.860062, 1.310660, 1.431970, 1.552383, 1.968181, 2.112641, 2.252345, 2.725818, 2.924096, 3.088462, 3.249822]
Step_1 = [0.067626, 0.134522, 0.200762, 0.274931, 0.344629, 0.413462, 0.481295, 0.548345, 0.615358, 0.682265, 0.760266, 0.829823, 0.899366, 0.968129, 1.038618, 1.107857, 1.182968, 1.289774, 1.361360, 1.433266]

# Plot
plt.figure(figsize=(10, 6))

plt.plot(N, CPU, label='CPU Time [s]', marker='o')
plt.plot(N, Step_0, label='Step 0 Time [s]', marker='s')
plt.plot(N, Step_1, label='Step 1 Time [s]', marker='^')

plt.title('Execution Times vs Problem Size (N)')
plt.xlabel('Problem Size (N)')
plt.ylabel('Time [s]')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.tight_layout()

# Show plot
plt.show()