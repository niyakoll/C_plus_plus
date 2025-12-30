### Welcome to Phase 3: Intermediate – Modern C++  
**Project 3: Simple 2D Robot Simulator**

You're doing fantastic! You've mastered the basics (Phase 1) and core C++ with classes and vectors (Phase 2). Now we're stepping into **real object-oriented programming (OOP)** — the way professional robotics software is built.

Project 3 is the **most exciting one yet** because you'll see your code come alive on a console "grid world" with multiple robot types moving differently — just like a mini version of real robot fleet simulators used in warehouses, search-and-rescue, or autonomous exploration.

#### Project Introduction & What It Does

**Overview**  
We build a **text-based 2D grid simulator** (10×10 world) where different types of robots live and move around.  
- The grid is printed in the console (`.` = empty, `W` = WheeledRobot, `L` = LeggedRobot, `F` = FlyingRobot).  
- You control the robots via a menu: choose which robot and which direction to move.  
- Each robot type **moves differently** (different speed, battery cost, direction capabilities).  
- Features include:  
  - Battery drain (low battery warning)  
  - Boundary checking (can't leave the grid)  
  - Path history (shows where each robot has been with `*` trail)  
  - Position status display  

**User Experience Example**  
```
=== Grid World (0 to 9) ===
9 . . . . . . . . . .
8 . . . . . . . . . .
...
0 W . . . . . . . . L

=== Robot Simulator Menu ===
1. Move robot
2. Show all status
3. Quit
Choice: 1
Choose robot: 1. Wheeled  2. Legged  3. Flying → 1
Choose direction: 1. Up  2. Down  3. Left  4. Right → 1
WheeledRobot moved up!
```

This feels like controlling a real robot fleet in a simple world!

#### Objective

**Main Goal**  
Write **clean, reusable, professional-style C++ code** using full OOP to simulate different robot behaviors in a shared 2D grid world.

**Specific Objectives**
- Understand how big robotics systems organize code (base class + derived classes = robot hierarchy).
- Use polymorphism so one command (`move()`) does different things depending on robot type.
- Practice modern C++ features: smart pointers, enum class, const correctness, protected members.
- Build a complete interactive program you can play with and extend.

#### Expected Learning Outcome

By the end of Project 3 you will:
- Confidently design **inheritance hierarchies** (base + derived classes).
- Use **polymorphism** to write flexible code (same pointer → different behavior).
- Store mixed objects safely with `std::vector<std::unique_ptr<Base>>`.
- Understand why real robotics frameworks (ROS 2, Unitree SDK) use exactly this pattern.
- Have a **portfolio-ready mini simulator** that shows professional OOP skills.
- Be ready for Phase 4 (multithreading) and Phase 5 (real ROS 2 + hardware).

#### Key Concepts Introduced (With Simple Explanation)

| Concept                     | Simple Explanation                                                                 | Why It's Important in Robotics                          | Your Project Use |
|-----------------------------|------------------------------------------------------------------------------------|---------------------------------------------------------|------------------|
| **Inheritance**             | Derived class "is a" base class and inherits data/behavior.                        | All robots share common traits (position, battery) but have unique movement. | `WheeledRobot : public Robot` |
| **Polymorphism**            | Same function call → different behavior based on actual object type.               | One control system can command any robot type without knowing details.      | `robot->move(dir)` calls correct version |
| **Virtual functions**       | Functions that can be overridden in derived classes.                               | Enables polymorphic behavior.                                   | `virtual void move(Direction) = 0;` |
| **Pure virtual (= 0)**      | Forces derived classes to implement the function → makes base class abstract.     | No "generic" robot — every type must define its own move.       | Forces each robot to implement move |
| **Virtual destructor**      | Ensures proper cleanup when deleting through base pointer.                         | Prevents memory leaks in large systems.                          | `virtual ~Robot() = default;` |
| **Protected members**       | Accessible to derived classes but hidden from outside.                             | Shared state (position, battery) safe for inheritance.           | `protected: int positionX;` |
| **enum class**              | Strongly-typed, scoped list of named constants (Up, Down, Left, Right).            | Type-safe directions instead of magic numbers.                  | `enum class Direction` |
| **std::unique_ptr**         | Smart pointer with unique ownership — auto cleanup.                               | Safe memory management for polymorphic objects.                 | `std::vector<std::unique_ptr<Robot>>` |
| **emplace_back**            | Efficiently construct objects directly inside vector.                              | Fast path logging in real-time systems.                         | `path.emplace_back(x, y);` |

These are **exactly the patterns** used in real robotics frameworks (ROS 2 node hierarchies, Unitree SDK high/low level control).

#### Important Notes for Beginners

1. **This project is small but complete** — you will see real results fast (grid updating, robots moving).
2. **We use only modern C++20/23 features** — exactly what robotics companies expect in 2025.
3. **Focus on clean design** — real code is organized this way so teams of 50+ engineers can work together.
4. **Play with it!** Try adding new robot types (SwimmingRobot?) or features (obstacles) — this is how pros learn.
5. **References** (bookmark these):
   - learncpp.com OOP series: https://www.learncpp.com/cpp-tutorial/inheritance/
   - cppreference virtual functions: https://en.cppreference.com/w/cpp/language/virtual
   - ROS 2 composition (polymorphism): https://docs.ros.org/en/rolling/Concepts/About-Composition.html

#### Let's Start Building!

We'll build Project 3 step by step:
1. Abstract base `Robot` with pure virtual `move()`
2. Derived classes with different movement
3. Grid display
4. Polymorphic container + menu
5. Path history, boundaries, collision, recharge

