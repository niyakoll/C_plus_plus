#include <iostream>    // for std::cout, std::cin
#include <vector>      // for std::vector
#include <memory>      // for std::unique_ptr and std::make_unique
//Real robotics code never uses raw new/delete — always smart pointers to avoid memory leaks.
#include <string>      // for std::string
//Base Class Robot
enum class Direction {Up,Down,Left,Right};
const int GRID_SIZE = 10;
std::vector<std::pair<int,int>> obstacles = {
    {3, 3}, {4, 3}, {5, 3},  // a wall
    {7, 6}, {2, 8}
};
class Robot{
    protected:
    //protected: derived classes (Wheeled, Legged, Flying) can access these directly.
    //shared state is protected, not exposed to outside world
    //In real ROS robots, base classes have protected members like pose_, velocity_, battery_level_.
        int positionX = 0;
        int positionY = 0;
        int battery = 100;
        std::string type;
        std::vector<std::pair<int,int>> path;
        bool isObstacle(int posX, int posY)const{
            for(const auto& obs : obstacles){
                if(obs.first == posX && obs.second == posY)return true;
            }
            return false;
        }
    public:
        
        Robot(std::string t) : type(t){
            path.emplace_back(positionX, positionY);
        } //construtor, init list() type = t
        //Constructor using member initializer list
        //Initializes type ("Wheeled", "Legged", etc.)
        

        virtual void move(Direction dir) = 0; //pure virtual = absract class
        //forces every derived robot to implement its own movement.
        // "= 0 " is a promise, bthe robot can move but no default movement, must overiden when derived(pure virtual function), make robot become abstract class
        //can not create a plain Robot object

        virtual void update(){
            
        }


        virtual void showPath()const{
            std::cout << "Path History: \n";
            for(auto& [x,y] : path){
                std::cout << "(" << x << "," << y << ") ";
                std::cout << "->";
            }
            std::cout << "\n";
        }
        virtual void showStatus() const{
        //virtual: can be overridden (though we use default here)
        //const: promises not to modify the object — good practice for status display
            std::cout << type << "at (" << positionX << ", " << positionY << " ) Battery : " << battery << "%\n";
        }
        //Getter, for grid display
        int getX()const{return positionX;}
        int getY()const{return positionY;}
        //Const getters — safe way for outside code (like displayGrid) to read position/type.
        //Encapsulation: direct access to positionX/Y denied, must use getters.
        std::string getType()const{return type;}
        virtual ~Robot() = default; // crucial for polymorphism
        //Virtual destructor — absolutely required for polymorphism.
        //virtual : allow overide
        //~Robot() : destructor, for cleaning up resources
        //default: default destructor

};
//Derived Classed
class WheeledRobot : public Robot {
        
    public:
        WheeledRobot() : Robot("Wheeled") {}
        //Calls base constructor with type string
        //Constructor is public → main() can create it
        void move(Direction dir) override {
            //This is polymorphism in action — same move() call, different results!
            if(battery < 10){
                std::cout << "Low battery!\n";
                return;
            }
            int dy = 0;
            int dx = 0;
            switch (dir){
                case Direction::Up: dy = 1;break;
                case Direction::Down: dy = -1;break;
                case Direction::Right: dx = 1;break;
                case Direction::Left: dx = -1;break;
            
            default:
                break;
            }
            int newX = positionX + dx;
            int newY = positionY + dy;
            if(newX < 0 || newX >= GRID_SIZE || newY < 0 || newY >= GRID_SIZE){
                std::cout << "Cannot move — boundary!\n";
                return;
            }
            else if(isObstacle(newX,newY)){
                std::cout << "Blocked by obstacle!\n";
                return;
            }
            else{
                positionX = newX;
                positionY = newY;
                battery -= 5;
                std::cout << "WheeledRobot moved efficiently\n";
                path.emplace_back(positionX, positionY);
            }
            
        }
        void update() override {
            move(Direction::Right);
        }
};
class LeggedRobot : public Robot{
    public:
        LeggedRobot() : Robot("Legged") {}
     void move(Direction dir) override {
            //This is polymorphism in action — same move() call, different results!
            if(battery < 10){
                std::cout << "Low battery!\n";
                return;
            }
            int dy = 0;
            int dx = 0;
            switch (dir){
                case Direction::Up: dy = 1;break;
                case Direction::Down: dy = -1;break;
                case Direction::Right: dx = 1;break;
                case Direction::Left: dx = -1;break;
            
            default:
                break;
            }
            int newX = positionX + dx;
            int newY = positionY + dy;
            if(newX < 0 || newX >= GRID_SIZE || newY < 0 || newY >= GRID_SIZE){
                std::cout << "Cannot move — boundary!\n";
                return;
            }
            else if(isObstacle(newX,newY)){
                std::cout << "Blocked by obstacle!\n";
                return;
            }
            else{
                positionX = newX;
                positionY = newY;
                battery -= 10;
                std::cout << "LeggedRobot moved efficiently\n";
                path.emplace_back(positionX, positionY);
            }
            
        }
        void update() override {
            int testX = positionX+1;// try move to right
            int testY = positionY;
            if(isObstacle(testX,testY)||testX >= GRID_SIZE-1){
                testX = positionX;
                testY = positionY + 1; //try move to up
                if (isObstacle(testX, testY) || testY >= GRID_SIZE-1) {
                    // Try left as last resort
                    move(Direction::Left); 
                    return;
                }
                move(Direction::Up);
            }
            else{
                move(Direction::Right);
            }
        }
};

class FlyingRobot : public Robot{
    public:
        FlyingRobot(std::string name) : Robot(name){}
     void move(Direction dir) override {
            //This is polymorphism in action — same move() call, different results!
            if(battery < 10){
                std::cout << "Low battery!\n";
                return;
            }
            int dy = 0;
            int dx = 0;
            switch (dir){
                case Direction::Up: dy = 3;break;
                case Direction::Down: dy = -3;break;
                case Direction::Right: dx = 3;break;
                case Direction::Left: dx = -3;break;
            
            default:
                break;
            }
            int newX = positionX + dx;
            int newY = positionY + dy;
            if(newX < 0 || newX >= GRID_SIZE || newY < 0 || newY >= GRID_SIZE){
                std::cout << "Cannot move — boundary!\n";
                return;
            }
            else if(isObstacle(newX,newY)){
                std::cout << "Blocked by obstacle!\n";
                return;
            }
            else{
                positionX = newX;
                positionY = newY;
                battery -= 18;
                std::cout << "FlyingRobot moved efficiently\n";
                path.emplace_back(positionX, positionY);
            }
            
        }
        void update() override {
            // Flying robots love altitude!
            move(Direction::Up);  // big jump of 3
        }
};

void displayGrid(const std::vector<std::unique_ptr<Robot>>& robots){
    std::cout << "\n=== Grid World (0 to " << GRID_SIZE-1 << ") ===\n";
    for(int row = GRID_SIZE-1; row >= 0; --row){
        for(int col = 0; col < GRID_SIZE; ++col){
            char symbol = '.';
            bool isObstacle = false;
            for(const auto& obs : obstacles){
                if(obs.first == col && obs.second == row){
                    symbol = '#'; // obstacle symbol
                    isObstacle = true;
                    break;
                }
            }
            if (isObstacle)
            {
                std::cout << symbol << ' ';
                continue;
            }
            for(const auto& robot : robots){
                if(robot->getX() == col && robot -> getY() == row){
                    symbol = robot->getType()[0]; // 'W' or 'L'
                    break;
                }
            }
            std::cout << symbol << ' ';
        }
        std::cout << '\n'; 
    }
    std::cout << "\n";
    
}
void moveOption(std::vector<std::unique_ptr<Robot>>& robots){
            std::cout << "Choose robot:\n1. Wheeled  2. Legged  3. Flying\n";
            int robotChoice; 
            std::cin >> robotChoice;
            if (robotChoice < 1 || robotChoice > robots.size()) {
                std::cout << "Invalid robot!\n";
                return;
            }
            std::cout << "Choose direction:\n1. Up  2. Down  3. Left  4. Right\n";
            int dirChoice; 
            std::cin >> dirChoice;
            if (dirChoice < 1 || dirChoice > 4) {
                std::cout << "Invalid direction!\n";
                return;
            }
            Direction dir;
            switch (dirChoice) {
                case 1: dir = Direction::Up; break;
                case 2: dir = Direction::Down; break;
                case 3: dir = Direction::Left; break;
                case 4: dir = Direction::Right; break;
            }

            robots[robotChoice-1]->move(dir);
            robots[robotChoice-1]->showPath();
        };
void moveTogather(std::vector<std::unique_ptr<Robot>>& robots){
            std::cout << "How many simulation steps? (between 1-4) ";
            int steps; 
            if(!(std::cin >> steps)|| steps <= 0 || steps > 4){
                std::cout << "Invalid number of steps!(must be 1-4)\n";
                return;
            }
            std::cout << "Choose direction for all robots:\n1. Up  2. Down  3. Left  4. Right\n";
            int dirChoice; 
            std::cin >> dirChoice;
            if (dirChoice < 1 || dirChoice > 4) {
                std::cout << "Invalid direction!\n";
                return;
            }
            Direction dir;
            switch (dirChoice) {
                case 1: dir = Direction::Up; break;
                case 2: dir = Direction::Down; break;
                case 3: dir = Direction::Left; break;
                case 4: dir = Direction::Right; break;
            }
            std::cout << "\nStarting autonomous simulation for " << steps << " steps...\n\n";
            for(auto& rb : robots){
                for(int s = 0 ; s < steps ; ++s){
                    std::cout << "--- Simulation Step " << (s + 1) << " ---\n";
                    rb->move(dir);
                }
                displayGrid(robots);
            }
            std::cout << "Autonomous simulation complete!\n";
        };
void autonomousMovement(std::vector<std::unique_ptr<Robot>>& robots){
            std::cout << "How many simulation steps? (between 1-9) ";
            int steps; 
            if(!(std::cin >> steps)|| steps <= 0 || steps > 9){
                std::cout << "Invalid number of steps!(must be 1-9)\n";
                return;
            }
            
            std::cout << "\nStarting autonomous simulation for " << steps << " steps...\n\n";
            for(int s = 0 ; s < steps ; ++s){
                std::cout << "--- Simulation Step " << (s + 1) << " ---\n";
                for(auto& rb : robots){
                    rb->update();
                }
                displayGrid(robots);
            }
            std::cout << "Autonomous simulation complete!\n";
        };
int main() {
    std::vector<std::unique_ptr<Robot>> robots;
    robots.push_back(std::make_unique<WheeledRobot>());
    robots.push_back(std::make_unique<LeggedRobot>());
    robots.push_back(std::make_unique<FlyingRobot>("FlyingRobot"));
    
    int choice;
    do {
        displayGrid(robots);
        std::cout << "\n=== Robot Simulator Menu ===\n";
        std::cout << "1. Move robot\n";
        std::cout << "2. Show all status\n";
        std::cout << "3. Autonomous Movement (each robot uses own AI)\n";
        std::cout << "4. Quit\n";
        std::cin >> choice;
        switch(choice){
            case 1 : moveOption(robots);break;
            case 2 : for (const auto& r : robots) r->showStatus();break;
            case 3 : autonomousMovement(robots);break;
            case 4 : std::cout << "Goodbye!\n"; break;
        }
        //std::cout << "Choice: ";
        
        
        /*
        switch (choice) {
            case 1: if (robots.size() > 0){
                        std::cout << "Choose direction:\n1. Up  2. Down  3. Left  4. Right\n";
                        int dirChoice; std::cin >> dirChoice;
                        Direction dir;
                        switch (dirChoice) {
                            case 1: dir = Direction::Up; break;
                            case 2: dir = Direction::Down; break;
                            case 3: dir = Direction::Left; break;
                            case 4: dir = Direction::Right; break;
                        }

                        robots[0]->move(dir);
                    }
            case 2: if (robots.size() > 1) robots[1]->move(); break;
            case 3: if (robots.size() > 2) robots[2]->move(); break;
            case 4:
                for (const auto& r : robots) r->showStatus();
                break;
        }
                */
    } while (choice != 4);

    return 0;
}