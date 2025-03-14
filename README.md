# Semaphore Synchronization for p1, p2, p3

## Overview

This project demonstrates inter-process synchronization using semaphores. The system consists of multiple processes, p1, p2, and p3, which coordinate execution using a semaphore mechanism implemented in sem.c.

## Requirements

- **GCC**: Ensure you have GCC installed. You can install it using:

```bash
sudo apt-get install gcc
```

## Files

- **p1.c**: Creates semaphores and prints its message. It initializes the semaphore values and ensures proper process synchronization.
- **p2.c**: Waits for p1 to complete, then prints its message, and signals p3 twice to allow it to execute twice.
- **p3.c**: Waits for two signals from p2, prints its message twice, and signals p1 to start the next cycle.
- **sem.c**: Contains the semaphore functions.
- **awk\_sem.h**: Header file with the function declarations for semaphore operations.

## Compilation

In a Linux terminal, compile the programs with:

```bash
gcc -o p1 p1.c sem.c
gcc -o p2 p2.c sem.c
gcc -o p3 p3.c sem.c
```

## Execution

1. **Check for Existing Semaphores and Clear if Necessary:**\
   Before running the programs, check if any previous semaphores exist and clear them if needed:
   ```bash
   ipcs -s
   ipcs -s | awk 'NR>3 {print $2}' | xargs -n 1 ipcrm sem
   ```
   This ensures that there are no leftover semaphores that may interfere with execution.

2. **Run the Programs:**\
   Start the processes in the background:
   ```bash
   ./p1 &
   ./p2 &
   ./p3 &
   ```
   The expected output will cycle as follows:
   - p1 prints once.
   - p2 prints once.
   - p3 prints twice.
     This cycle repeats continuously.

## Synchronization Logic

- **p1.c:**

  - Creates three semaphores with the following initial values:
    - Semaphore A (for p1): 1
    - Semaphore B (for p2): 0
    - Semaphore C (for p3): 0
  - p1 waits on Semaphore A, prints its message, and then signals Semaphore B.
  - Before starting the next iteration, p1 waits for Semaphore A to be released by p3.

- **p2.c:**

  - Waits on Semaphore B.
  - Prints its message.
  - Signals Semaphore C twice so that p3 can execute twice.

- **p3.c:**

  - Waits on Semaphore C twice (one for each execution).
  - Prints its message twice.
  - After printing, it signals Semaphore A twice to allow p1 to start the next cycle.

## Notes

- Make sure to clear any existing semaphores before running the programs.
- Use only the provided semaphore functions for synchronization to meet the assignment requirements.
- *Previous Issue:* The original version of the code did not include an initial `P(sem1)` in p1. Despite this, the correct execution cycle was still achieved because p2 signals Semaphore C twice, ensuring that p3 executes twice before p1 resumes. However, to prevent `race conditions` in concurrent execution, explicitly including `P(sem1)` in p1 ensures proper synchronization.