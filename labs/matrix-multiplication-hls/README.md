# Dense Matrix Multiplication Accelerator

This project implements matrix multiplication using Vivado HLS and explores performance optimization techniques.

## Objectives
- Implement baseline matrix multiplication
- Optimize using blocking and loop transformations
- Compare performance and resource utilization

## Key Features
- Baseline vs optimized designs
- Dataflow and loop reordering
- Latency and resource comparison

## Verification
- C simulation
- Synthesis report analysis

## Takeaways
Memory access patterns and dataflow design are critical for compute-intensive accelerators.

## How to Reproduce

1. Open Vivado HLS
2. Import baseline and optimized matrix multiplication sources
3. Set target device to Zynq-7000
4. Run C Simulation for functional correctness
5. Run C Synthesis for both versions
6. Compare latency and resource utilization reports
