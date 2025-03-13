# Semaphore Synchronization for p1, p2, p3

## Overview
This project demonstrates how to use semaphores in Linux to synchronize three processes, p1, p2, and p3. The processes run in the following order repeatedly:
- **p1**: Prints a message once.
- **p2**: Prints a message once.
- **p3**: Prints a message twice.

## Requirements
- **GCC**: Ensure you have GCC installed. You can install it using:
```bash:
sudo apt-get install gcc
```

## Files
- **p1.c**: Creates semaphores and prints its message. It sets the initial semaphore values.
- **p2.c**: Waits for p1 to complete, then prints its message, and signals p3 twice.
- **p3.c**: Waits for two signals from p2, prints its message twice, and signals p1 to start the next cycle.
- **sem.c**: Contains the semaphore functions.
- **awk_sem.h**: Header file with the function declarations for semaphore operations.

## Compilation
In a Linux terminal, compile the programs with:
```bash
gcc -o p1 p1.c sem.c
gcc -o p2 p2.c sem.c
gcc -o p3 p3.c sem.c
```

## Execution
1. **Clear Existing Semaphores:**  
   To avoid interference from previous semaphores, run the following command:
   ```bash
   ipcs -s | awk 'NR>3 {print $2}' | xargs -n 1 ipcrm sem
   ```
2. **Run the Programs:**  
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

- **p2.c:**  
  - Waits on Semaphore B.
  - Prints its message.
  - Signals Semaphore C twice so that p3 can print twice.

- **p3.c:**  
  - Waits on Semaphore C twice (one for each message).
  - Prints its message twice.
  - After printing, it signals Semaphore A to allow p1 to start the next cycle.

## Notes
- Make sure to clear any existing semaphores before running the programs.
- Use only the provided semaphore functions for synchronization to meet the assignment requirements.
