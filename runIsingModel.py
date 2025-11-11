import subprocess
import numpy as np
import matplotlib.pyplot as plt


executable_path = "./isingModel"

equilibirum_steps_input = input("Input number of equilibrium steps: ")
measurement_steps_input = input("Input number of measurment steps: ")  # 500k sweeps
lower_temp_input = input("Input lower temperature bound: ")
upper_temp_input = input("Input upper temperature bound: ")
lower_temp = float(lower_temp_input)
upper_temp = float(upper_temp_input)
temperatures = np.linspace(lower_temp, upper_temp, 50)

results = []

print("--- Starting Ising Model Scan ---")

for T in temperatures:
    temp_str = str(T)
    print(f"Running simulation for T = {T:.3f}...")

    command = [
        executable_path,
        equilibirum_steps_input,
        measurement_steps_input,
        temp_str,
    ]

    try:
        result = subprocess.run(command, capture_output=True, text=True, check=True)
        output = result.stdout

        try:
            mag_str = output.split("=")[-1]
            mag = float(mag_str)
            results.append((T, mag))
            print(f"  Success: <s> = {mag:.5f}")
        except (IndexError, ValueError):
            print(f"  Error: Could not parse output: '{output}'")

    except subprocess.CalledProcessError as e:
        print(f"  Error: Simulation failed for T = {T:.3f}")
        print(f"  Command: {' '.join(command)}")
        print(f"  STDERR: {e.stderr}")

print("--- Scan Complete ---")

if results:
    data = np.array(results)

    np.savetxt(
        "mag_vs_temp.dat",
        data,
        header="Temperature   Average_Magnetization",
        fmt="%.5f",
    )
    print("Data saved to mag_vs_temp.dat")

    plt.figure(figsize=(10, 6))
    plt.plot(data[:, 0], np.abs(data[:, 1]), "o-")
    plt.xlabel("Temperature (T)")
    plt.ylabel("Average Magnetization |<s>|")
    plt.title("Ising Model Phase Transition (L=50)")
    plt.grid(True)
    plt.show()
else:
    print("No valid results to plot.")
