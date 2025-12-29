# CORDIC Accelerator (Vivado HLS)

This project implements a CORDIC-based accelerator for sine and cosine computation.

**Note:** This project focuses on design, integration, and validation results. 
Build artifacts and generated files are intentionally excluded.

## Objectives
- Implement fixed-point CORDIC algorithm in hardware
- Analyze numerical accuracy using RMSE
- Compare different iteration depths and architectures

## Key Features
- Fixed-point arithmetic
- RMSE-based validation
- Latency vs resource trade-off exploration

## Verification
- C simulation against golden sine/cosine values
- RTL co-simulation for functional equivalence

## Takeaways
Accuracy, latency, and resource usage must be balanced when implementing iterative math algorithms in hardware.

## How to Reproduce

1. Open Vivado HLS
2. Create a new project and add CORDIC source and testbench
3. Set fixed-point configuration as defined in source
4. Run C Simulation to compute RMSE against golden model
5. Run C Synthesis and RTL Co-simulation
6. Compare latency/resource trade-offs across configurations
