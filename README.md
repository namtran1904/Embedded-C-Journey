# 💻 Embedded C Mastery Roadmap: From K&R to Low-Level Firmware

This repository shows my learning path to master **Low-Level C Programming** and **Embedded Systems**. Instead of using heavy software libraries, this path focuses on writing efficient, safe, and bare-metal compatible code under strict hardware limits (no dynamic memory, fixed-point math, and deterministic execution).

---

## 🗺️ Roadmap Structure

### 📌 Phase 1: Bitwise Operations & Binary Logic
*Focus: Manipulating individual bits — a survival skill for microcontroller programming.*

- **Bài 2:** Virtual register design for screen control (Set/Clear/Toggle/Read via Bit Masking).
  > *💡 Meaning:* Simulate how to change GPIO pin states on a microcontroller without affecting other neighbor pins.
- **Bài 14:** Binary to BCD conversion using bit-shifting (avoiding expensive division).
  > *💡 Meaning:* Optimize performance by using bit shifts instead of division, which takes too many CPU cycles on cheap MCUs.
- **Bài 23:** Endianness Swapper (Shift & Mask).
  > *💡 Meaning:* Handle byte order conversion (Big/Little Endian) when sending and receiving data between different chip architectures.
- **Bài 26:** Bit-Field Unpacking for variable-length data fields.
  > *💡 Meaning:* Unpack network packets or sensor data that have custom bit lengths (not aligned to bytes).
- **Bài 28:** Lightweight XOR Byte Scrambler.
  > *💡 Meaning:* Do basic raw data scrambling to avoid repeating bit patterns when sending signals through communication lines.

### 🔄 Phase 2: Control Flow & Finite State Machines (FSM)
*Focus: Writing clean, lightweight char-by-char parsers without heavy string libraries.*

- **Bài 6:** NMEA GPS Sentence Parser (Char-by-char FSM).
  > *💡 Meaning:* Read and split GPS data in real-time byte by byte, saving RAM instead of using large string buffers.
- **Bài 15:** Physical Button Debouncer (ISR-friendly without blocking delays).
  > *💡 Meaning:* Handle physical button noise inside interrupts without freezing the system using blocking `delay()` functions.
- **Bài 20:** Command packet receiver and validator (3-byte header FSM).
  > *💡 Meaning:* Accurately recognize command frames from a continuous UART/SPI data stream.

### 📦 Phase 3: Modular Design, Scope & Preprocessor
*Focus: Encapsulation (`static`), file separation, and professional macro design.*

- **Bài 5:** Critical section simulation (Interrupt resource protection).
  > *💡 Meaning:* Simulate disabling interrupts to protect shared data from conflict between the main loop and ISRs.
- **Bài 9:** Internal module password encapsulation using the `static` keyword.
  > *💡 Meaning:* Hide internal data and functions so they can only be accessed inside a single file (like object-oriented encapsulation in C).
- **Bài 22:** Advanced logging system using Variadic Macros (`__FILE__`, `__LINE__`, `__VA_ARGS__`).
  > *💡 Meaning:* Build a smart debug system that automatically logs the exact file and line number where an error occurs.

### 🧠 Phase 4: Pointers & Memory Management (Core of C)
*Focus: Mastering RAM access without relying on `malloc`.*

- **Bài 3:** Static Ping-Pong Buffer (Dual-buffer pointer swapping).
  > *💡 Meaning:* A dual-buffer pointer swapping technique that allows writing new data while processing old data without conflicts.
- **Bài 7:** Array Slicing using pointer arithmetic.
  > *💡 Meaning:* Slice a data array into smaller parts to process independently without wasting memory on temporary sub-arrays.
- **Bài 13:** Function Pointer Table for button event dispatching (replacing `switch-case`).
  > *💡 Meaning:* Replace messy `switch-case` statements with a function pointer table to keep code clean and easy to scale.
- **Bài 18:** Generic Ring Buffer implementation using `void*`.
  > *💡 Meaning:* Create a versatile queue that holds any data type, acting as the base for UART/SPI drivers.
- **Bài 27:** Callback registration for button drivers.
  > *💡 Meaning:* Design an event-driven architecture to separate the hardware layer from the application layer.
- **Bài 29:** Optimized sliding-window 5-point Median Filter.
  > *💡 Meaning:* Remove sudden noise (spike noise) from sensors using an optimized sliding window.

### 🔌 Phase 5: Structures & Hardware Communication
*Focus: Interfacing directly with raw binary data, memory mapping, and hardware registers.*

- **Bài 1:** Command Packet Decoder (Pointer casting & `__attribute__((packed))`).
  > *💡 Meaning:* Directly cast byte streams from network/UART into structs without bit shifting caused by compiler padding.
- **Bài 11:** Memory-mapped RAM simulation of peripheral registers.
  > *💡 Meaning:* Understand how microcontrollers map hardware registers into RAM memory space.
- **Bài 16:** Error log struct array sorting without dynamic memory.
  > *💡 Meaning:* Manage and sort system error history within a limited static memory space.
- **Bài 21:** Static Memory Pool Allocator.
  > *💡 Meaning:* Build a custom memory management system for embedded devices with NO `malloc`/`free`.
- **Bài 25:** Cooperative Task Scheduler.
  > *💡 Meaning:* Build a simple cooperative multitasking scheduler for systems without a Real-Time Operating System (RTOS).

### 📐 Phase 6: Embedded Arithmetic & Communication Protocols
*Focus: Implementing complex mathematical algorithms and industrial protocols on microcontrollers without an FPU.*

- **Bài 4:** Fixed-point Q15 multiplication.
  > *💡 Meaning:* Perform real-number multiplication using integers on chips that do not have a hardware FPU.
- **Bài 8:** Modbus CRC-16 checksum calculation (Bit-by-bit shift).
  > *💡 Meaning:* Ensure data integrity for industrial communication using the Modbus protocol.
- **Bài 10:** Exponential Moving Average (EMA) low-pass filter using fixed-point arithmetic.
  > *💡 Meaning:* Smoothly filter sensor noise while using very low calculation resources.
- **Bài 12:** General-purpose PID controller with Anti-Windup.
  > *💡 Meaning:* Control motors or temperature accurately, preventing the integral windup issue.
- **Bài 17:** Integer Square Root via Newton-Raphson method.
  > *💡 Meaning:* Calculate square roots very fast using integers to support positioning and kinematics algorithms.
- **Bài 19:** 1st-order Digital Bandpass Filter.
  > *💡 Meaning:* Filter out unwanted frequencies to get the target signal from raw sensor data.
- **Bài 24:** Two-point linear sensor calibration using fixed-point math.
  > *💡 Meaning:* Calibrate linear errors for physical sensors in real applications.
- **Bài 30 (Capstone):** Complete Modbus RTU Frame Parser over UART.
  > *💡 Meaning:* Combine all knowledge to build a complete industrial communication protocol from scratch.

---

## 🛠️ Key Technical Highlights
- **🔒 No `malloc` / Static Allocation:** All buffers and memory pools are statically allocated to ensure zero memory leaks and predictable execution time.
- **⚡ Low-Level Safety:** Strict management of Memory Alignment (`__attribute__((packed))`) and Endianness.
- **⚙️ Algorithmic Efficiency:** Implementation of fixed-point math, ring buffers, and FSM parsers tailored for resource-limited microcontrollers.
