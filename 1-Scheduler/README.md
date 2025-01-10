# OS Scheduler

**Course:** CPE 473: Operating Systems  
**Institution:** Jordan University of Science and Technology  
**Department:** Computer Engineering  

## Assignment Overview

In this assignment, you will implement a simple **OS Scheduler** using C/C++. The scheduler will:

1. Receive a set of processes and their details.
2. Decide the order of execution based on the **Ranking Scheduling Algorithm**.
3. Output the process execution order along with some statistics for each process.

## Scheduler Details

### Input Format
The input file (`in.txt`) contains:

1. An integer `N` (number of processes).
2. `N` lines with the following format for each process:
   - A string `s`: Process name (can contain multiple characters).
   - Three numbers:
     1. **Arrival Time**
     2. **Processing Time**
     3. **Rank**

Each value is separated by a tab (`\t`). Input values can go up to **100,000,000**.

### Ranking Scheduling Algorithm
1. Processes with **lower rank values** get higher priority.
2. For processes with the same rank:
   - Choose the one with the **earlier arrival time**.
3. If rank and arrival time are identical:
   - Choose the process that appears **first in the input**.

### Output Format
Write the output to a file (`out.txt`) with:

1. One line per process in the execution order, showing:
   - **Process Name**
   - **Response Time**
   - **Turnaround Time**
   - **Delay**
2. A final line showing the execution order of the processes.
