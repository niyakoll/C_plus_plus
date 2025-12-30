### Welcome to Phase 4: Advanced C++  
**Project 4: Multi-Threaded Robot Controller**

Congratulations on completing **Project 3**! You now have a solid grasp of **object-oriented design, inheritance, and polymorphism** — the foundation of all large-scale robotics software.

Phase 4 is where things get **exciting and real-world**. Modern robots must do **many things at the same time**:
- Read sensors at high speed
- Run control loops (PID, trajectory following)
- Log data
- Communicate with other systems

Doing all this in a single thread would be slow and unresponsive.  
**Multithreading** lets us run tasks **concurrently** — this is **critical for real-time robotics**.

Project 4 will upgrade our 2D simulator into a **real-time capable controller** with separate threads — just like professional robot firmware.

#### Project Introduction & What It Does

**Overview**  
We take the grid world from Project 3 and add **multiple independent threads**:
- **Sensor thread**: simulates fast sensor updates (e.g., fake LIDAR or IMU at 100 Hz)
- **Control thread**: runs the main loop (user input, robot movement, collision check) at 10–20 Hz
- **Logging thread**: saves robot positions and sensor data to console/file safely
- **Main thread**: coordinates everything and handles shutdown

The program runs **smoothly even under load** — no blocking, no missed sensor readings.

**User Experience Example**  
```
[Sensor Thread] New distance reading: 45.2 cm
[Control Thread] Moving WheeledRobot right...
[Logging Thread] Saved position (3,5) at time 1.234s
Grid updates live while sensors run in background!
```

This feels like controlling a **real robot** with separate sensor, control, and telemetry systems.

#### Objective

**Main Goal**  
Master **concurrent programming** in C++ to build a responsive, real-time robot controller — the same architecture used in actual robot firmware.

**Specific Objectives**
- Understand why robotics needs multithreading (real-time constraints).
- Use `std::thread`, `std::mutex`, `std::condition_variable` safely.
- Share data between threads without race conditions.
- Practice clean shutdown and thread joining.
- Prepare for real ROS 2 (which is heavily multithreaded).

#### Expected Learning Outcome

By the end of Project 4 you will:
- Confidently write **multi-threaded C++ programs** with safe data sharing.
- Understand **RAII, mutexes, and condition variables** — core of modern systems.
- Simulate **real-time robot loops** (sensor → control → actuator).
- Know how professional teams structure concurrent code (ROS 2 nodes, embedded firmware).
- Have a **portfolio-ready real-time controller** that shows advanced skills.
- Be ready for Phase 5: actual ROS 2 nodes and real hardware.

#### Key Concepts Introduced (With Simple Explanation)

| Concept                     | Simple Explanation                                                                 | Why It's Critical in Robotics                          | Your Project Use |
|-----------------------------|------------------------------------------------------------------------------------|---------------------------------------------------------|------------------|
| **std::thread**             | Creates a new thread of execution                                                  | Run sensors at high rate while accepting commands       | Sensor & logging threads |
| **std::mutex**              | Lock that protects shared data — only one thread can access at a time              | Prevent corrupted position/battery when multiple threads write | Protecting shared robot state |
| **std::lock_guard**         | RAII wrapper — automatically unlocks mutex when out of scope                       | Safe, exception-proof locking                           | Every data access |
| **std::condition_variable** | Lets threads wait and notify each other                                            | Control thread waits for new sensor data                | Sync sensor → control |
| **Atomic variables**        | Thread-safe variables without mutex (for simple types)                             | Fast battery counter or flags                           | Optional battery level |
| **Thread join/detach**      | Wait for thread to finish or let it run independently                              | Clean shutdown — no zombie threads                      | Graceful exit |
| **Thread-safe queue**       | Queue with mutex protection for passing data between threads                       | Sensor thread → control thread data passing             | Real-time messages |

These are **exactly the tools** used in:
- ROS 2 executors (multi-threaded node spinning)
- Unitree/Boston Dynamics low-level control loops
- Embedded real-time systems (FreeRTOS, Zephyr)

#### Important Notes for Beginners

1. **Multithreading is powerful but dangerous** — race conditions can cause crashes that are hard to debug. We’ll use safe patterns from day one.
2. **We focus on std::thread + mutex** — this is what 99% of robotics C++ uses (ROS 2, Eigen, OpenCV all use it).
3. **Real-time feel** — you’ll see the program remain responsive even when threads are busy.
4. **Build system** — we’ll introduce **CMake** (industry standard) to compile multi-file projects cleanly.
5. **References** (bookmark these):
   - learncpp.com threading: https://www.learncpp.com/cpp-tutorial/an-introduction-to-stdthread/
   - cppreference std::thread: https://en.cppreference.com/w/cpp/thread
   - C++ Core Guidelines concurrency: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#cp-concurrency

#### Let's Start Building!

We’ll build Project 4 in small, safe steps:
1. Single-thread version (review from Project 3)
2. Add sensor thread with shared data + mutex
3. Add logging thread with thread-safe queue
4. Add condition variable for efficient waiting
5. Clean shutdown with join()
6. CMake build system

