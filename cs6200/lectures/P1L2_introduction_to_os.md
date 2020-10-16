# Simple Definition

a piece of software that:<br>

- **abstracts** (simplify what hardware looks like)
- **arbitrates** (to control the hardware use)<br>

the underlying hardware systems

# Shop Manager Metaphor

### A shop manager

- Directs operational resources: use of employee time, parts, tools
- Enforces working policies: fairness, safety, cleanup
- Mitigates difficulty of complex tasks: simplifies operation, optimizes performance

### An operating system

- Directs operational resources: use of CPU, memory, peripheral devices
- Enforces working policies: fair resource access, limits to resource usage
- Mitigates difficulty of complex tasks: abstract hardware details (system calls)

# What is OS?

![What's os](assets/P1L2/os.png)

Let's first look at the hardware of a computing system. This computing system consists of:

- Central Processing Unit (CPU)
- Physical Memory
- Network Interfaces (Ethernet/Wifi Card)
- GPU
- Storage Devices (Disk, Flash drives [USB])

In addition, a computing system can have higher level applications. These are the "programs" that we use every day on our computer:

- Skype
- Word
- Chrome

The Operating System is the layer of software that sits **between** the hardware components and the higher level applications.

### Main Functions of an Operating System

1.  Hide hardware complexity.<br>
    The operating system provides a higher level abstraction, the file, with a number of operations - like read and write - which applications can interact with.

2.  manages underlying hardware resources. <br>
    Operating system allocates memory for applications, schedules them for execution on the CPU, controls access to various network devices and so on.

3.  Provides isolation and protection.<br>
    When applications are running concurrently, the operation system has to ensure that they can do what they need to without hurting one another. For example, memory allocated to each application must not be readable/writable from another application.

# Operating System Definition

An operating system is a layer of systems software that:

- directly has privileged access to the underlying hardware
- hide the hardware complexity
- manages hardware on behalf of one or more applications according to some predefined policies.
- Ensures that applications are isolated and protected from one another

# Operating System Examples

Certain operating systems may target:

- desktop environment
- embedded environment
- a mainframe or a server environment

We will focus on operating systems for desktop environments and embedded environments.

For desktop operating systems we have:

- Microsoft Windows
- Unix-based
  - Mac OSX (BSD)
  - Linux (Ubuntu, Centos, Fedora)

For embedded operating systems:

- Android
- iOS
- Symbian

# OS Elements

To achieve its goals, an operating systems provides:

1. High level **abstractions**
2. **mechanisms** to operate on these abstractions.
3. **Policies** (how mechanisms will be used)

### Examples of abstractions

- application abstractions: process, thread
- hardware abstractions: file, socket, memory page

### Corresponding mechanisms

- create/schedule
- open/write/allocate

### Policies (how mechanisms will be used)

- least-recently used (LRU)
- earliest deadline first (EDF)

# OS Elements Example

Let's look at an example of memory management.

The main abstraction here is the memory page, which corresponds to some addressable region of memory of some fixed size.

The operating system integrates mechanisms to operate on that page like allocate, which actually allocates the memory in DRAM. It can also map that page into the address space of the process, so that the process can interact with the underlying DRAM.

Over time, the page may be moved to different spaces of memory, or may be moved to disk, but those who use the page abstraction don't have to worry about those details. That's the point of the abstraction.

How do we determine when to move the page from DRAM to disk? This is an example of a policy, and one such implementation of that policy would use the least-recently-used (LRU) algorithm, moving pages that have been accessed longest ago onto disk.

# Design Principles

### Separation of mechanism and policy

We want to incorporate flexible mechanisms that can support a number of policies.

For the example of memory, we can have many policies: LRU, LFU (least-frequently used), random. It is a good design strategy to create our memory management mechanisms such that they can generalize to these different policies.

In different settings, different policies make more sense.

### Optimize for the common case

- Where will the OS be used?
- What will the user want to execute on that machine?
- What are the workload requirements?

Understanding the common case - which may change in different contexts - helps the OS implement the correct policy, which of course relies on generalized mechanisms.

# OS Protection Boundary

![boundary protection](assets/P1L2/boundary_protection.png)

Computer systems distinguish between at least two modes of execution:

- user-level (unprivileged)
- kernel-level (privileged)

Because an OS must have direct access to hardware, it must operate in kernel mode.

Applications generally operate in user-mode.

Hardware access can only be utilized in the kernel mode from the OS directly.

Crossing from user-level to kernel-level is supported by most modern operating systems.

As an example, the operating system can flip a bit in the CPU that allows applications executing instructions to have direct access to hardware resources. When the bit is not flipped, operations are forbidden.

When privileged instructions are encountered during a non-privileged execution, the application will be trapped. This means the application's execution will be interrupted, and control will be handed back to the OS.

The OS can decide whether to grant the access or potentially terminate the process.

The OS also exposes an interface of system calls, which the application can invoke, which allows privileged access of hardware resources for the application on behalf of the operating system.

For example:

- open (file)
- send (socket)
- malloc (memory)

Operating systems also support signals, which is a way for the operating system to send notifications to the application.

# System Call Flow

![system call](assets/P1L2/system_call1.png)

Begin within the context of a currently executing process. The process needs access to some hardware, and thus needs to make a system call. The application makes the system call (potentially passing arguments), and control is passed to the operating system, which accesses the hardware. Execution control (as well as any necessary data) is passed back from the operating system to the application process.

In terms of context switching, the process involves a change from user-mode to kernel-mode to user-mode.

Not necessarily a cheap operation to make a system call!

Arguments to system call can either be passed directly from process to operating system, or they can be passed indirectly by specifying their address

![system call](assets/P1L2/system_call2.png)

In synchronous mode, the process waits until the system call completes. Asynchronous modes exist also.

# Crossing the OS Boundary

User/Kernel transitions are very common and useful throughout the course of application execution.

- hardware supported

  For example, the hardware will cause a trap on illegal executions that require special privilege. Hardware initiates transfer of control from process to operating system when a trap occurs.

- Requires instructions to execute, which can take ~100ns on a 2Ghz Linux box.

- Switches locality: affects hardware cache!

- Not cheap

# OS Services

An operating system provides applications with access to the underlying hardware.

It does so by exporting a number of services, which are often directly linked to the components of the hardware:

- Scheduling component (CPU)
- Memory manager (physical memory)
- Block device driver (block device)

In addition, some services are even higher level abstractions, not having a direct hardware component. For example, the filesystem as a service.

### Basic services

- Process management
- File management
- Device management
- Memory management
- Storage management
- Security

### Linux VS Windoes

![system calls](assets/P1L2/system_calls.png)

# Monolithic OS

![Monolithic OS](assets/P1L2/mono_os1.png)
![Monolithic OS](assets/P1L2/mono_os2.png)

# Modular OS

![Modular OS](assets/P1L2/modular_os.png)

This type of operating system has a basic set of services and APIs that come with it.

Anything not included can be added, as a module.

As a result, each application can interface with the operating systems in the ways that make most sense to it.

Dynamically install new modules in the operating system!

# Microkernel

Microkernels only require the most basic operating system components.

Everything else (including file systems and disk drivers) will run outside of the operating system at user-level.

This setup requires lots of interprocess communication (IPC), as the traditional operating system components run within application processes.

![Microkernel](assets/P1L2/microkernel.png)

# Linux and Mac OS Architecture

![linux architecture](assets/P1L2/linux-arch.png)

![mac architecture](assets/P1L2/mac-arch.png)
