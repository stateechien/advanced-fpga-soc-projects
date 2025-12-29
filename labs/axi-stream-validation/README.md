# AXI Stream Validation with AXI VIP and ILA

This project focuses on validating AXI Stream data paths using protocol-aware tools.

## Objectives
- Verify AXI Stream handshake behavior
- Use AXI VIP for stimulus generation
- Debug runtime behavior using ILA

## Key Features
- AXI Stream protocol validation
- AXI VIP-based verification
- On-chip waveform capture using ILA

## Verification
- Simulation with AXI VIP
- Hardware-level debugging with ILA

## Takeaways
System-level validation requires both simulation and on-chip debugging to ensure protocol correctness.

## How to Reproduce

1. Open Vivado
2. Create a block design with AXI Stream components
3. Insert AXI VIP for protocol-aware verification
4. Run simulation to verify TVALID/TREADY behavior
5. Add ILA core and regenerate bitstream
6. Capture on-chip waveforms to validate runtime behavior
