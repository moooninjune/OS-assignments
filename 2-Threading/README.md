# Multi-threaded Prime and Palindrome Checker

**Course:** CPE 473: Operating Systems  
**Institution:** Jordan University of Science and Technology  
**Department:** Computer Engineering  

## Assignment Overview

In this assignment, you will implement a **multi-threaded program** in C/C++ to:

1. Check for **Prime Numbers** and **Palindrome Numbers** in a given range.
2. Identify numbers that are **both Prime and Palindrome** (Palindromic Primes).

Your program will create `T` worker threads to divide the range and process numbers. Each thread will handle a part of the range and report its results.

## Program Details

### Input Format
The input file (`in.txt`) contains:
- Two integers: `rangeStart` and `rangeEnd`, representing the range of numbers (inclusive).

The program will accept the **number of threads (`T`)** as a command-line argument.

### Output Format
1. Results from each thread (to be printed on **STDOUT**):
   - Thread ID
   - Start and end of the range it is processing
2. Summary (on **STDOUT**):
   - Total numbers processed.
   - Counts for:
     - Prime numbers
     - Palindrome numbers
     - Palindromic Prime numbers
3. Results of prime numbers (to be saved in **out.txt**):
   - Lists of Prime numbers, Palindrome numbers, and Palindromic Primes.

## Implementation Requirements

1. **Two Versions of the Program**:
   - **Thread-unsafe version**: No synchronization mechanisms.
   - **Thread-safe version**: Proper synchronization for shared resources.

2. **Global Variables**:
   - `numOfPrimes`: Total number of prime numbers.
   - `numOfPalindromes`: Total number of palindrome numbers.
   - `numOfPalindromicPrimes`: Total number of palindromic prime numbers.
   - `TotalNums`: Total numbers processed.
   - Lists:
     - `PrimeList`: All prime numbers.
     - `PalindromeList`: All palindrome numbers.
     - `PalindromicPrimesList`: All palindromic primes.

3. Each thread must:
   - Print its ID and range at the start.
   - Update shared variables and lists.

4. **Command-line Argument (`T`)**:
   - Specify the number of threads.
   - Example: `./a.out 4`

5. **Environment**:
   - **OS:** Linux (Ubuntu).
   - **Compiler:** g++.
   - **Thread Library:** pthread.

## Links to my code:
- **Source codes:** [Unsafe version](/2-Threading/unsafe-version.cpp), [Safe version](/2-Threading/safe-version.cpp)

- **Report:** [Report.pdf](/2-Threading/Report.pdf)