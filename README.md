<<<<<<< HEAD
# HW3 - Cache Simulator 

## Description
This program simulates a cache using given configuration parameters and a sequence of memory addresses.  
For each memory reference, it determines whether the access results in a **HIT** or a **MISS**.

## How to Compile
Open a terminal in the project folder and run:

g++ -o cache_sim.exe main.cpp cache_class.cpp

## How to Run
Run the program using:

.\cache_sim.exe <num_entries> <associativity> <input_file>

Example:

.\cache_sim.exe 4 2 input.txt

## Input Format
The input file should contain memory addresses separated by spaces.

Example:
1 3 5 1 3 1

## Output
The program creates a file named:

cache_sim_output

Each line shows:
ADDRESS : HIT or MISS

Example:
1 : MISS  
3 : MISS  
5 : MISS  
1 : MISS  
3 : MISS  
1 : HIT  

## Design
- Cache is implemented using a 2D array (sets and ways)
- Each entry stores:
  - valid bit
  - tag
  - reference value (used for replacement)
- Replacement policy: FIFO (oldest entry replaced first)

## Limitations
- Cache block size is fixed to 1 word
- No multi-level cache support
- No miss classification (compulsory, conflict, capacity)

## Author
Sergio Mendoza
=======
# cache_sim_HW3
>>>>>>> b96c0998fd353dcaaf0b20caca244e86169138c8
