#include <iostream> //input/output stream
//using namespace std; // for beginners, ok here

//display robot status
void displayStatus(const int& positionX, const int& positionY, const int& battery) {
    std::cout << "\n--- Robot Status ---\n";
    std::cout << "positionX : " << positionX << std::endl;
    std::cout << "positionY : " << positionY << std::endl;
    std::cout << "Battery : " << battery << std::endl;
}
//robot move 
void moveRobot(int& positionX, int& positionY, int dx, int dy, int& battery){
    if(battery<10){
        std::cout << "Low battery! remaining : " << battery << "%" << std::endl;
        std::cout << "Please recharge Robot..." << std::endl;
        return;
    }
    positionX += dx;
    positionY += dy;
    battery -= 8;
    
    std::cout << "new position : X -> " << positionX << " Y - > " << positionY << std::endl;
    std::cout << "Battery used 8%" << std::endl;
    std::cout << "Battery remaining: " << battery << std::endl;
}

//robot reset position and battery
void reset(int& positionX, int& positionY, int& battery){
    
    positionY = 0;
    positionX = 0;
    battery = 100;
    std::cout << "Robot reseted." << std::endl;
    std::cout << "new position : X -> " << positionX << " Y - > " << positionY << std::endl;
    std::cout << "Battery : " << battery << std::endl;
}
void chargeRobot(int& battery){
    battery += 20;
    if(battery >= 100){
        battery = 100;
        std::cout << "Battery is 100%!" ;
        return;
    }
    std::cout << "Battery : " << battery << std::endl;
}
int main() {
    int positionX = 0;
    int positionY = 0;
    int battery = 100;
    char choice;
    std::cout << "\n\nWelcome to the TEXT BASE ROBOT Controller!" << std::endl;
    std::cout << "This program is starting..." << std::endl;
    //std::cout << "initial position X : " << positionX << endl;
    //std::cout << "initial position Y : " << positionY << endl;
    std::cout << "initial position X : " << positionX << "\ninitial position Y : " << positionY << std::endl;
    std::cout << "initial battery : " << battery << "%" << std::endl;
    do {
        std::cout << "=== Main Menu ===\n";
        std::cout << "1. Move forward\n";
        std::cout << "2. Move Backward\n";
        std::cout << "3. Move Left\n";
        std::cout << "4. Move Right\n";
        std::cout << "5. Reset position\n";
        std::cout << "6. Charge battery\n";
        std::cout << "7. Show status\n";
        std::cout << "8. Quit\n";
        std::cout << "Enter your choice (1-8): ";
        //std::cin >> choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();                  // clear error flag
            std::cin.ignore(10000, '\n');      // discard bad input
            std::cout << "Invalid input! Please enter a number.\n";
            continue;                     // skip switch, show menu again
        }
        switch(choice){
            case '1' :
                moveRobot(positionX,positionY,0,1,battery);
                std::cout << "Robot move forward!";
                break;
            case '2' :
                moveRobot(positionX,positionY,0,-1,battery);
                std::cout << "Robot move backward!";
                break;
            case '3' :
                moveRobot(positionX,positionY,-1,0,battery);
                std::cout << "Robot move left!";
                break;
            case '4' :
                moveRobot(positionX,positionY,1,0,battery);
                std::cout << "Robot move right!";
                break;
            case '5' :
                reset(positionX,positionY,battery);
                break;
            case '6' :
                chargeRobot(battery);
                break;
            case '7' :
                displayStatus(positionX,positionY,battery);
                break;
            case '8' :
                std::cout << "Shutting down simulator. Goodbye!" << std::endl;
                break;
            default :
                std::cout << "Invalid choice! Please enter 1 - 8." << std::endl;
        }
        if(battery < 10 && choice != '8'){
            std::cout << "\n === CRITICAL !!!===\nBattery is " << battery << "%!" << " Recharge immediately!" << std::endl; 
        }

    }
    while (choice != '8');
    
    
    return 0;
}
