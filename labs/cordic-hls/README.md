# CORDIC Accelerator (Vivado HLS)

This project implements a CORDIC-based accelerator for sine and cosine computation.

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
