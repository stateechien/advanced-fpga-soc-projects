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
