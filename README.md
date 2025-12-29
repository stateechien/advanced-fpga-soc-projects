# Advanced FPGA & SoC Projects

This repository contains a curated set of FPGA and SoC projects that I personally implemented, focusing on accelerator design, system integration, and hardware–software co-design.

All projects in this repository are hands-on implementations and verification results produced by myself. Course slides or reference materials are intentionally excluded to keep the repository engineering-focused.

## Project Overview

| Category | Projects |
|--------|---------|
| DSP / Math Accelerators | FIR Filter, CORDIC |
| Compute Accelerators | Dense Matrix Multiplication, Sparse Matrix Multiplication |
| System Validation | AXI Stream, AXI VIP, ILA |
| SoC Integration | Blink IP on Vitis |

## Toolchain
- Vivado / Vivado HLS
- Vitis
- AXI (Lite / Stream), AXI VIP
- Integrated Logic Analyzer (ILA)
- Zynq SoC

Each project folder contains implementation files and validation results generated during development.

##  Projects and Links
| Category | Link |
|----------|------|
| FIR Filter Accelerator | [fir-filter-hls](labs/fir-filter-hls/README.md) |
| CORDIC Accelerator | [cordic-hls](labs/cordic-hls/README.md) |
| Dense Matrix Multiplication | [matrix-multiplication-hls](labs/matrix-multiplication-hls/README.md) |
| Sparse Matrix Multiply | [sparse-matrix-multiplication](labs/sparse-matrix-multiplication/README.md) |
| AXI Stream Validation | [axi-stream-validation](labs/axi-stream-validation/README.md) |
| Blink IP on Vitis | [blink-ip-vitis](labs/blink-ip-vitis/README.md) |

## System Architecture Overview

The projects in this repository follow a layered FPGA and SoC architecture,
covering accelerator design, system integration, and software–hardware co-design.

### Software Layer
- Linux user applications (e.g., Blink control app)
- Vitis / bare-metal control programs

### Processing System (PS)
- Zynq ARM Cortex-A9
- MicroBlaze soft processor  
- Responsibilities:
  - System control
  - Hardware configuration
  - Data movement orchestration

### Programmable Logic (PL)
- Custom accelerators (Vivado HLS / RTL):
  - FIR Filter
  - CORDIC
  - Dense Matrix Multiplication
  - Sparse Matrix Multiplication (CSR-based)
- System IPs:
  - AXI Stream data paths
  - AXI VIP (protocol-aware verification)
  - ILA (on-chip debugging)
  - Blink AXI-Lite IP

### Design & Verification Flow
- Algorithm modeling (C/C++)
- Vivado HLS (C simulation, synthesis, RTL co-simulation)
- Vivado (integration, timing/resource analysis, ILA)
- Vitis / PetaLinux (software and OS integration)


**Key Focus:**  
End-to-end hardware–software co-design, from algorithm-level acceleration
to SoC integration and Linux-based hardware control.
