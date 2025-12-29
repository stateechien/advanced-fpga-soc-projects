# Blink IP Integration on Vitis

This project implements a custom Blink IP and integrates it into a Vitis-based system.

## Objectives
- Design a custom AXI-Lite peripheral
- Package and integrate IP into a system
- Validate functionality through hardware execution

## Key Features
- Custom RTL IP design
- AXI-Lite register control
- Vitis-based system integration

## Verification
- Hardware execution on target platform
- Functional validation via software control

## Takeaways
Successful FPGA development requires integration across RTL, interconnects, and software.

## How to Reproduce

1. Package Blink AXI-Lite IP in Vivado
2. Create block design and connect IP to Zynq PS
3. Generate bitstream and export hardware
4. Open Vitis and create a control application
5. Program FPGA and run application
6. Verify Blink behavior through hardware execution
