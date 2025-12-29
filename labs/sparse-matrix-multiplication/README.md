# Sparse Matrix Multiplication Accelerator

This project explores sparse matrix multiplication using the CSR (Compressed Sparse Row) format.

## Objectives
- Implement sparse matrix multiplication in hardware
- Compare direct CSR computation with adapter-based approaches
- Analyze architectural trade-offs

## Key Features
- CSR data structure handling
- Multiple architectural approaches
- Design space exploration

## Verification
- Testbench-based functional validation
- Synthesis report comparison

## Takeaways
Sparse computation introduces control complexity, and architecture selection significantly impacts performance and reuse.

## How to Reproduce

1. Open Vivado HLS
2. Add CSR sparse matrix multiplication source files
3. Select top function for CSR-based accelerator
4. Run C Simulation using provided testbench
5. Run C Synthesis to analyze control and memory behavior
6. Compare with dense MM design for architectural trade-offs
