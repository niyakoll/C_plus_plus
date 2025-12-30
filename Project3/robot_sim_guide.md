# Project 3 Complete Guidelines for New Learners  
**Simple 2D Robot Simulator – Learn Modern C++ OOP with Robotics Focus**


This guide is written for **absolute beginners** who have finished Phase 1 & 2 and want to understand **every line** of Project 3.

We will go **step by step**, explain **why** each feature exists, and show **how it connects to real robotics**.

---

### 1. Project Overview – What Does This Program Do?

- A 10×10 grid world is printed in the console.
- Three different robots exist: **Wheeled**, **Legged**, **Flying**.
- Each robot has:
  - Position (X,Y)
  - Battery level
  - Movement rules (speed, battery cost)
  - Path history (trail of `*` or list)
- Obstacles (`#`) block movement.
- Menu lets you:
  - Manually move any robot in 4 directions
  - Run **autonomous simulation** where each robot decides its own move (different AI!)
- Grid updates live as robots move.

This is exactly how real robot **fleet simulators** start (warehouse robots, search-and-rescue teams).

---

### 2. Key C++ Concepts You Mastered in This Project

| Concept                  | Why It Matters in Real Robotics                                      | Where You Used It                          |
|--------------------------|---------------------------------------------------------------------|--------------------------------------------|
| Inheritance              | All robots share common data (position, battery)                    | `class WheeledRobot : public Robot`        |
| Polymorphism             | One command → different behavior per robot type                     | `robot->move(dir)` calls correct version   |
| Pure virtual functions   | Force every robot to define its own move logic                       | `virtual void move(Direction) = 0;`        |
| Virtual destructor       | Prevent memory leaks when using polymorphism                        | `virtual ~Robot() = default;`              |
| Protected members        | Shared state safe for derived classes                               | `protected: int positionX;`                |
| enum class               | Type-safe directions (no magic numbers)                             | `enum class Direction`                     |
| std::unique_ptr          | Safe memory management for polymorphic objects                      | `vector<unique_ptr<Robot>>`                |
| emplace_back             | Efficient logging of path history                                   | `path.emplace_back(x, y)`                  |
| Override keyword         | Compiler checks you are correctly overriding                         | `void move(...) override`                  |
| Const correctness        | Safe read-only functions                                            | `showStatus() const`                       |

---

### 3. Step-by-Step Learning Guide (Follow This Order)

#### Step 1 – Understand the Base Class `Robot`

```cpp
class Robot {
protected:
    int positionX = 0;
    int positionY = 0;
    int battery = 100;
    std::string type;
    std::vector<std::pair<int,int>> path;
    
    bool isObstacle(int posX, int posY) const { ... }
public:
    Robot(std::string t) : type(t) { path.emplace_back(0,0); }
    virtual void move(Direction dir) = 0;     // MUST override
    virtual void update() {}                  // optional override
    virtual void showPath() const { ... }
    virtual void showStatus() const { ... }
    int getX() const { return positionX; }
    int getY() const { return positionY; }
    std::string getType() const { return type; }
    virtual ~Robot() = default;
};
```

**Learning Points**:
- `protected` → derived classes can access, outside cannot (encapsulation).
- `virtual void move(...) = 0` → **pure virtual** → `Robot` is **abstract** → cannot create `Robot r;`
- `virtual ~Robot()` → required for safe deletion through base pointer.
- `path` stores every position visited → real robots log odometry.

#### Step 2 – Study One Derived Class (WheeledRobot)

```cpp
class WheeledRobot : public Robot {
public:
    WheeledRobot() : Robot("Wheeled") {}

    void move(Direction dir) override {
        if (battery < 10) { ... return; }
        int dx = 0, dy = 0;
        switch(dir) { ... }  // set dx/dy
        int newX = positionX + dx;
        int newY = positionY + dy;

        // Boundary check
        if (newX < 0 || newX >= GRID_SIZE || ...) { ... return; }
        // Obstacle check
        if (isObstacle(newX, newY)) { ... return; }

        // Success → update position, battery, path
        positionX = newX;
        positionY = newY;
        battery -= 5;
        path.emplace_back(positionX, positionY);
    }

    void update() override {
        move(Direction::Right);  // simple AI: always go right
    }
};
```

**Learning Points**:
- `override` keyword → safety (compiler warns if wrong)
- `isObstacle()` called from derived → protected access works!
- `update()` → autonomous AI per robot type
- `emplace_back` → efficient path logging

#### Step 3 – See How Polymorphism Works in `main()`

```cpp
std::vector<std::unique_ptr<Robot>> robots;
robots.push_back(std::make_unique<WheeledRobot>());
robots.push_back(std::make_unique<LeggedRobot>());
robots.push_back(std::make_unique<FlyingRobot>("FlyingRobot"));

for (auto& r : robots) r->update();  // calls each robot's own update()!
```

Even though the pointer is `Robot*`, it calls the correct derived version → **polymorphism magic!**

#### Step 4 – Understand Autonomous vs Manual Movement

- `move(Direction)` → manual control (menu)
- `update()` → autonomous AI (different per robot)
  - Wheeled: always right
  - Legged: avoid obstacles intelligently
  - Flying: always up (big jumps)

This shows **different intelligence** per robot type — real robotics research!

#### Step 5 – Grid Display with Obstacles

```cpp
void displayGrid(...) {
    // Print # for obstacles
    // Print robot symbol (W, L, F) if present
    // Print . otherwise
}
```

Real simulators (Gazebo, RViz) do the same but in 3D.

---

### 4. How This Project Prepares You for Real Robotics

| Your Project Feature               | Real-World Equivalent                                 |
|------------------------------------|-------------------------------------------------------|
| Different robot types (inheritance) | Unitree G1, Boston Dynamics Spot, warehouse robots    |
| Polymorphic `move()`               | ROS 2 navigation stack sending same goal to any robot |
| Obstacle avoidance in `update()`   | SLAM, path planning (A*, DWA)                         |
| Path history (`path` vector)       | Odometry logging, trajectory recording                |
| Battery management                 | Real power monitoring in long missions                 |
| Smart pointers                     | Used in all modern ROS 2 code                         |

You are now writing code with the **same design patterns** as professional robotics teams!

---

### 5. Next Steps – Extend the Project (Practice!)

Try these challenges (in order):

1. Add trail display (`*` where robots have been)
2. Add collision: robots cannot occupy same cell
3. Add recharge station at (0,0) — restore battery
4. Add new robot: `SwimmingRobot` that ignores obstacles but slow
5. Add random obstacles at start

Each will teach you more OOP and real robot problems.

---

### 6. References for Deeper Learning

- learncpp.com OOP series: https://www.learncpp.com/cpp-tutorial/inheritance/
- cppreference polymorphism: https://en.cppreference.com/w/cpp/language/virtual
- ROS 2 composition (same idea): https://docs.ros.org/en/rolling/Concepts/About-Composition.html
- Unitree SDK2 examples: https://github.com/unitreerobotics/unitree_sdk2

---

**You have completed Project 3!**  
You now understand how real robotics software is structured using inheritance and polymorphism.

Next: **Phase 4** – Multithreading (sensor thread + control thread) and CMake build system.

