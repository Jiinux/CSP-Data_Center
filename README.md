
# Server Farm Workload Allocation Using CSP

## Project Description

This project solves the Server Farm Workload Allocation problem using Constraint Satisfaction Problems (CSP).

The goal is to assign four Virtual Machines (VMs) to three server racks while satisfying the given constraints.

## Problem Components

### Variables

The variables are the four Virtual Machines:

- VM1
- VM2
- VM3
- VM4

### Domains

Each VM can be assigned to one of the following racks:

- Rack A
- Rack B
- Rack C

### Constraints

The problem has three main constraints:

1. **Anti-Affinity:** VM1 and VM2 cannot be assigned to the same rack.
2. **Capacity Control:** VM3 and VM4 cannot both be assigned to Rack C.
3. **Network Isolation:** VM4 can only be assigned to Rack A or Rack B.

## Algorithms Used

The project uses the following algorithms:

### 1. Backtracking

Backtracking assigns values to variables one at a time. If an assignment violates a constraint, the algorithm goes back and tries another value.

### 2. Minimum Remaining Values (MRV)

MRV selects the variable that has the smallest number of valid values remaining in its domain.

### 3. Forward Checking

Forward Checking checks the remaining possible values after each assignment. It helps detect invalid paths early.

## Project Structure

- `main.cpp`: Contains the C++ source code.
- `README.md`: Explains the project and how to run it.
- `Report_Guide.md`: Contains the report structure and required explanations.
- `sample_output.txt`: Shows an example of the program output.

## Requirements

- C++ compiler
- Any C++ IDE, such as Code::Blocks or Visual Studio

## How to Run

1. Open the project in your C++ IDE.
2. Open `main.cpp`.
3. Compile the program.
4. Run the program.
5. Observe the solutions and experiment results.

You can also compile using the terminal:

```bash
g++ main.cpp -o server_farm
```

Then run:

```bash
./server_farm
```

On Windows, run:

```bash
server_farm.exe
```

## Experiments

The program performs three experiments:

1. Solve the original CSP problem.
2. Remove the Network Isolation constraint and observe the changes.
3. Add a contradictory constraint and observe whether a solution exists.

## Expected Result

The program should find a valid assignment for the original problem while respecting all constraints.

The contradictory experiment should demonstrate how conflicting constraints can make a CSP problem unsolvable.
