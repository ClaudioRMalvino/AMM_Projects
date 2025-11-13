# Atomistic Modeling of Materials (AMM) Projects

This repository contains projects and exercises completed for the "Atomistic Modeling of Materials" course. The projects focus on implementing computational physics techniques, including Monte Carlo methods, discussed in the course.

## Course Description

This course gives an introduction to the atomistic simulation of materials using classical molecular dynamics and Monte Carlo techniques, and consists of a series of lectures with associated computing classes in which both the theoretical and practical aspects of running simulations will be covered. The course starts with a brief review of essential concepts in thermodynamics and statistical mechanics required to understand atomistic simulation methods, and is suitable for those with a physical sciences background. It comprises twelve lectures and two practical sessions.

[Link to official course description](https://mphil.csc.cam.ac.uk/current-students/lectures-supported-by-the-mphil/atomistic-modelling-of-materials-m24-e/)
---

## Projects

This repository includes the following projects:

### 1. Monte Carlo Estimation of Pi

* **File:** `monteCarloPi.cpp`

**Description**
A simple C++ program that estimates the value of $\pi$ (Pi) using the "hit-or-miss" Monte Carlo method. The program simulates random points in a 2x2 square centered at the origin and counts the fraction of points that fall within a unit circle (radius 1) inscribed within that square.

The value of $\pi$ is then approximated using the formula:
$\pi \approx 4 \times \frac{\text{Points in Circle}}{\text{Total Points}}$

**How to Build and Run**
1.  Compile the program:
    ```bash
    g++ -std=c++20 monteCarloPi.cpp -o monteCarloPi
    ```
2.  Run the executable:
    ```bash
    ./monteCarloPi
    ```
    **Example Output:**
    ```
    valid points = 785397
    Approximate Monte Carlo pi = 3.14159
    ```

---

### 2. 2D Ising Model Simulation

* **Files:** `isingModel.cpp`, `runIsingModel.py`

**Description**
This project simulates the 2D Ising Model on a square lattice using the Metropolis-Hastings algorithm. The C++ program (`isingModel.cpp`) calculates the average magnetization of the system at a given temperature after allowing it to reach thermal equilibrium.

The simulation is controlled by a Python script (`runIsingModel.py`) which:
1.  Prompts the user for simulation parameters (equilibration steps, measurement steps, temperature range).
2.  Calls the compiled C++ executable repeatedly for a range of temperatures.
3.  Parses the average magnetization output from the C++ program.
4.  Saves the final `Temperature` vs. `Average_Magnetization` data to `mag_vs_temp.dat`.
5.  Generates a plot of the absolute average magnetization vs. temperature, allowing for visualization of the phase transition (Curie temperature).

**How to Build and Run**

1.  **Compile the C++ code:**
    ```bash
    g++ -std=c++20 isingModel.cpp -o isingModel
    ```

2.  **Install Python dependencies:**
    The helper script requires `numpy` and `matplotlib`.
    ```bash
    pip install numpy matplotlib
    ```

3.  **Run the Python script:**
    ```bash
    python3 runIsingModel.py
    ```

4.  **Follow the prompts:**
    The script will ask for the number of steps and the temperature bounds for the scan.
    ```
    Input number of equilibrium steps: 50000
    Input number of measurment steps: 100000
    Input lower temperature bound: 1.0
    Input upper temperature bound: 4.0
    ```

The script will then run the simulation for each temperature, print the progress, and finally display the plot and save the data.

---

## Build System

A `CMakeLists.txt` file is included.

* **C++:** A C++ compiler supporting the C++20 standard (e.g., `g++` or `clang++`).
* **Python:** Python 3
* **Python Libraries:** `numpy`, `matplotlib`
