# MIPS R10000 Uses Decoupled Architecture Reading Report

Author: Chongxi Wang

## Abstract

This article introduces that the MIPS Technologies unveiled the design of the R10000, which uses new technologies and has a great performance.

- R10000 uses a new technology, known as out-of-order execution. The processor uses deep queues decouple the intruction fetch logic from the execution units.

- R10000 can reach a speed of 200 MHz. At this speed, R10000 is expected to get a grade of 300 in SPEC int 92, as well as 600 in SPEC fp 92.

## Speculative Execution Beyond Branches

This part mainly talks about how R10000 executes, including instruction fetching and out-of-order execution.

The front end of the processor maintain a continuous flow of instructions into the instuction queues. The details are listed as follows.

- Instruction cache: 32K, two-way set-associative instruction cache.

- Predecoding: 4 extra bits per instruction, helps determine the appropriate queue.

- Fetching: 4 instructions per cycle from the cache.

- Branch prediction: standard two-bit Smith method with a 512-entry table, as well as a single-entry return-address buffer.

- Branch: if predicted taken, send the target address to the instruction cache; if misprediction, fetch from the "resume" cache where saves the original sequential instructions.

The R10000 supports out-of-order execution. The main technologies is renaming registers, queue(reservation stations), and active list(reorder buffer).

- Renaming registers: 64 physical registers each for interger and floating-point values.

- Renaming: target register from unused registers, source register from mapping table.

- Mapping table: 12 read ports and 4 write ports for integer, 16 read ports and 4 write ports for float.

- There queues: integer ALU, floating-point ALU, load/store.

- Queue stall: integer multiply and divide instructions can stall the queue.

- Active list: track up 32 consecutive instructions, similar to reorder buffer.

## Dynamic Instructon Issue

This part discusses about how the queue works in detail.

- Executable instruction: the operands are available.

- Busy bit: set when a physical register is assigned to a result.

- Working process: executable instructions flow from queue to regfile, picking up the operand, then into the appropriate function unit.

- Instruction priority:

  1. ALU1: give priority to minimiza the mispredicted branch penalty.

  2. ALU2 & FP multiplier: give priority to older instructions.

  3. Address queue: give priority strictly to older instructions.

## Function Units Proceed at Own Pace

This part talks about the functional units and its pipeline.

- Function unit pipelines:

  1. ALU: Issue(read registers) - Execute(ALU) - Write(write result) 3-stage-pipeline.

  2. Memory: Issue(read registers) - Addr(calculate address) - Cache(access D-cache) - Write(write result) 4-stage-pipeline.

  3. FPU: Issue(read registers) - EX1 - EX2 - EX3(fp operation take three cycles) - Write(write result) 5-stage-pipeline.

- Two ALU:

  1. ALU1: any ALU instructions except multiply & divide instructions.

  2. ALU2: any ALU instructions except shift instructions.

- Two floating-point units:

  1. FP1: addition and similar functions.

  2. FP2: multiply, divide, and square-root operation.

## Active List Maintains Order

This part shows how the active list, which is similar to reorder buffer, maintains order.

- Retired: when that instruction and all preceding instructions have been compeleted, up to 4 instruction can retire per cycle.

- Exception: active list undoes the results of the instructions executed out of order.

- Mispredicted branch: save the mapping table and other important state in shadow register.

## Associative Caches at All Levels

This part introduces the caches in the R10000.

- Instruction cache: 32K, two-way set association, 64-byte lines.

- Data cache: 32K, two-way set association, 32-byte lines.

- Six-transistor: new technology to eliminate extra poly layer.

- TLB:

  1. Unified TLB: 64 pairs of entries.

  2. Instruction micro-TLB: 8 single-page entries.

- Secondary cache: 128-bit interface, range from 512K to 16M, use 100 0r 133 MHz cache with a 200 MHz processor.

- External cache: two-way set associative, 8K * 1 way prediction table, precision precision about 90%.

- System bus: 64-bit multiplexed address/data bus, limited about 100 MHz in uniprocessor and 80 MHz with multiple processors, three cycles for each address, maximum bandwidth 539 MBytes/s at 80 MHz.

## MIPS CPU Vendors Dwindle to Two

Only two vendors have signed up according to this part.

- Area: 298 mm^2, 0.5-micron process, four metal layers.

- Vendor: NEC, Toshiba.

## Next-Generation CPUs Are Simimal

This part tells that almost all the next-generation CPUs are similar, including R10000, PPC 620, UltraSparc, 21164.

- R10000: clock speed 200 MHz, cache size 32K/32K, 4 dispatch per cycle, 5 function units, predecode bits 4 bits, rename regs 32 ints & 32 fp, branch history 512 * 2, out of order 32 instructions, external cache control on chip, use synch SRAM, use Glueless MP, power 30 W, use 0.5-micron IC process, four metal layer, 2.3 M logic transistors, 5.9 M total transistors, 527-pin CPGA, area 298 mm^2, price $320, first silicon 4Q94, volume parts 4Q95, SEPCint92 > 300, SPECfp92 > 600.

- PPC 620: clock speed 133 MHz, cache size 32K/32K, 4 dispatch per cycle, 6 function units, predecode bits 7 bits, rename regs 8 ints & 8 fp, branch history 2K * 2, out of order 16 instructions, external cache control on chip, use synch SRAM, use Glueless MP, power 30 W, use 0.5-micron IC process, four metal layer, 2.2 M logic transistors, 6.9 M total transistors, 625-pin CBGA, area 311 mm^2, price $380, first silicon 7/94, volume parts 3Q95, SEPCint92 = 225, SPECfp92 = 300.

- UltraSparc: clock speed 167 MHz, cache size 16K/16K, 4 dispatch per cycle, 9 function units, predecode bits 4 bits, no rename regs, branch history 512 * 2, do not support out of order, external cache control on chip, use synch SRAM, use Glueless MP, power 30 W, use 0.5-micron IC process, four metal layer, 2.0 M logic transistors, 3.8 M total transistors, 521-pin CPGA, area 315 mm^2, price $420, first silicon 10/94, volume parts 3Q95, SEPCint92 = 275, SPECfp92 = 305.

- 21164: clock speed 300 MHz, cache size 8K/8K/96K, 4 dispatch per cycle, 4 function units, no predecode bits, no rename regs, branch history 2K * 2, out of order 6 load instructions, external cache control on chip, optionally use synch SRAM, use Glueless MP, power 50 W, use 0.5-micron IC process, four metal layer, 1.8 M logic transistors, 9.3 M total transistors, 499-pin CPGA, area 298 mm^2, price $430, first silicon 2/94, volume parts 1Q95, SEPCint92 = 330, SPECfp92 = 500.

## The future of MIPS

This part outlooks the expection of MIPS in the future. R10000 is expexted to achieve 300 SEPCint92 goal at 100 MHz, which is really competitive to PPC 620, UltraSparc, and 21164. Techniques such as register renaming and out-of-order execution will be widely used in the future design.

## My reading thoughts

Two decades ago, the greatest chip designers has created those classic techniques, such as renaming register, reorder buffer, reserve station, and so on. In the past two decades, it seems that every designer follows the same path: expand the scale of the chip, and refine the internal structure. However, the Moore's law will end soon, it is time to innovate and find another path of CPU development.

We still fall behind about 5 to 10 years in CPU designing field, compared to US. But I believe that we can close the gap soon. The most important thing is that we cannot fall behind again in the next generation CPU.

I still do not know what the next generation CPU is like. Perhaps the name is not CPU and "processor" is more appropriate. Nowadays, under the background of artificial intelligence and machine learning, those specified processors called "NPU" or "MLU" is pretty popular. Maybe they are the answer of the next generation processor. But in my opinion, they are not the answer in large probability because they are lack of principle innovation. We need to try, to create, to innovate, and see whose processor perform best.
