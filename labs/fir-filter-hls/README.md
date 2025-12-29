# FIR Filter Accelerator (Vivado HLS)

This project implements a Finite Impulse Response (FIR) filter using Vivado HLS.

## Objectives
- Design a streaming FIR filter accelerator
- Explore pipelining and initiation interval (II)
- Validate functionality through C simulation and RTL co-simulation

## Key Features
- Fixed-point FIR implementation
- HLS pipeline optimization
- Latency and resource analysis from synthesis reports

## Verification
- C simulation against golden output
- RTL co-simulation (XSIM)

## Takeaways
This project demonstrates how HLS directives affect performance and resource usage in streaming DSP designs.

## How to Reproduce

1. Launch Vivado HLS (2022.2 or later)
2. Create a new HLS project and add FIR source files
3. Set top function to FIR module
4. Target device: xc7z020-clg400-1
5. Run:
   - C Simulation
   - C Synthesis
   - RTL Co-simulation (XSIM)
6. Review latency, II, and resource usage in synthesis report
