### What is an Operating System

A program that acts as an intermediary between a user of a computer and the computer hardware

### Operating system goals

- Execute user programs and make solving user problems easier
- Make the computer system convenient to use
- Use the computer hardware in an efficient manner

### Computer System Structure

Computer system can be divided into four components:

- Hardware – provides basic computing resources
  - CPU, memory, I/O devices
- Operating system
  - Controls and coordinates use of hardware among various applications and users
- Application programs – define the ways in which the system resources are used to solve the computing problems of the users
  - Word processors, compilers, web browsers, database systems, video games
- Users
  - People, machines, other computers

![four components](assets/ch1/components.png)

# What Operating Systems Do

- Depends on the point of view
- PC (**single-user**) want convenience, **ease of use** and **good performance**
  - Don’t care about **resource utilization** (How various hardware and software resources are shared).
- **mainframe** or **minicomputer** must keep all users happy. OS maximize resource utilization - to assure all available CPU time, memory, and I/O are used efficiently and no individual users takes more than her fail share.
- **workstations** users have dedicated resources but also share resources such as networking and servers. OS compromise between individual usability and resource utilization.
- Handheld computers are resource poor, optimized for usability and battery life
- Some computers have little or no user interface, such as embedded computers in devices and automobiles

## Operating System Definition

- No universally accepted definition
- “Everything a vendor ships when you order an operating system” is a good approximation
  - But varies wildly
- “The one program running at all times on the computer” is the kernel.
- Everything else is either
  - a system program (ships with the operating system) , or
  - an application program.
- Mobile operationg systems often include core kernel and **middleware** - a set of software frameworkds providing additional services to application developers

### OS is a **resource allocator**

- Manages all resources
- Decides between conflicting requests for efficient and fair resource use

### OS is a **control program**

- Controls execution of programs to prevent errors and improper use of the computer

# Computer System Organization

## Computer-system operation

- One or more CPUs, device controllers connect through common bus providing access to shared memory
- Concurrent execution of CPUs and devices competing for memory cycles

![Modern Computer System](assets/ch1/modern_computer.png)

I/O devices and the CPU can execute concurrently

Each device controller is in charge of a particular device type

Each device controller has a local buffer
CPU moves data from/to main memory to/from local buffers

I/O is from the device to local buffer of controller

Device controller informs CPU that it has finished its operation by causing an interrupt

### Computer Startup

**bootstrap program** is loaded at power-up or reboot

- Typically stored in ROM or EPROM, generally known as **firmware**
- Initializes all aspects of system (CPU registers, device controllers, memory contents, etc.)
- Locate operating-system kernel, load it into memory and execute it
- **System processes / system daemons** (run the entire time the kernel is running) are loaded into memory at boot time and privide services out of the kernel
- The system is then fully booted and the system waits for some event to occur

### Interrupts

The occurance of an event is usually signaled by an interrupt from either the hardware or the software.

#### hardware

sending a signal to the CPU by the way of the system bus

#### software

executing a special operation called a **system call (monitor call)**

#### When CPU interrupted

1. Cpu stops and transfers executuins to a **fixed location** (contains the starting address whether the service routine for the interrupt is located)

2. interrupt service routine executes

3. CPU resumes the interrupted computation.

![Interrupt Timeline](assets/ch1/interrupt_timeline.png)

#### Common Functions of Interrupts

- Interrupt transfers control to the interrupt service routine generally, through the **interrupt vector**, which contains the addresses of all the service routines

- Interrupt architecture must save the address of the interrupted instruction

- A trap or exception is a software-generated interrupt caused either by an error or a user request

- An operating system is interrupt driven

#### Interrupt Handling

The operating system preserves the state of the CPU by storing registers and the program counter

Determines which type of interrupt has occurred:

- polling
- vectored interrupt system

Separate segments of code determine what action should be taken for each type of interrupt<br>
<br>

## Storage Structure

### Main memory

- CPU can laod instructions **only** from memory

- General-purpose computers run most from **rewriteble memory** (**main mamory** / **random-access memory**/ **RAM**)

- commonly implemented in **DRAM** (dynamic random-access memory)

#### instructions

##### Load

moves a byte or word from main memory to an internal register within CPU

##### store

moves the content of a register to main memory

#### Cannot resides programs and data in main memory permanenty

1. too small to store all

2. **volatile** storage device that loses its contents when power is tuerned off or otherwise lost<br>
   <br>

### Secondary storage

- extension of main memory
- provides large **nonvolatile** storage capacity
- most common device - **magnetic disk**

### Solid-state disk

- faster than magnetic disks, nonvolatile

### Storage Hierarchy

Storage systems organized in hierarchy

- Speed
- Cost
- Volatility

![storage hierarchy](assets/ch1/storage_hierarchy.png) <br>
<br>

# Computer-System Architecture

## Single-Processor Systems

Most computer systems use a single general-purpose processor

![single processor](assets/ch1/single_processor.png)

### Components

- main CPU executing a general-purpose instruction set
- other special-purpose processors as well<br>
  <br>

## Multiprocessor Systems

![multiple processor](assets/ch1/multi_processors.png)

Also known as parallel systems, tightly-coupled systems

Have two or more processors in close communication, sharing computer buss and sometimes the clock, memory, and peripheral devices

### Advantages

1. Increased throughput

   Get more work done in less time

   The speed-up ratio with N processors is not N

2. Economy of scale

   cost less than equivalent multiple single-processor systems because they can share peripherals, mass storage and power suppplies.

3. Increased reliability

   The faillure of one processor will not halt the system, only slow it down

### Two types

1. Asymmetric Multiprocessing

   - each processor is assigned a specie task.

   - boss-worker relationship

2. Symmetric Multiprocessing (commonly)

   - each processor performs all tasks
   - all processors are peers
   - all processors share physical memory while each processor has own set of registers and cache

### A Dual-Core Design

Recent trend: include multiple computing cores on a single chip (**multicore**)

![dual core](assets/ch1/dual-core.png) <br>
<br>

## Clustered Systems

clustered_system
![Clustered System](assets/ch1/clustered_system.png)

- Another type pf multiprocessor system
- Diff: composed of two or more individual systems joined together
- Loosely coupled
- Provides a high-availability service which survives failures
  - Asymmetric clustering has one machine in hot-standby mode
  - Symmetric clustering has multiple nodes running applications, monitoring each other
- Also for high-performance computing (HPC)
  - Applications must be written to use parallelization
- Some have **distributed lock manager (DLM)** to avoid conflicting operations <br>
  <br>

# Operating-System Structure

### Multiprogramming

- Single user cannot keep CPU and I/O devices busy at all times

- Multiprogramming organizes jobs (code and data) so CPU always has one to execute

- A subset of total jobs in system is kept in memory. Jobs are initially kept on the disk in **job pool**

- One job selected and run via job scheduling. When it has to wait (for I/O for example), OS switches to another job

![memory layout](assets/ch1/memo_layout.png)<br>
<br>

### Time sharing (multitask)

Logical extension in which CPU switches jobs so frequently that users can interact with each job while it is running, creating interactive computing

- Response time should be < 1 second
- Each user has at least one program executing in memory -> process
- If several jobs ready to run at the same time -> CPU scheduling
- If processes don’t fit in memory, **swapping** moves them in and out to run to ensure reasonable response time
- Virtual memory allows execution of processes not completely in memory
