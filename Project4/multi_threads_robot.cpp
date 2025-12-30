//multi_threads_robot.cpp
// === import library ===
// ======================
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread> // allow running multiple functions at the same time (concurrently)
#include <mutex> //a lock to prevent race conditions
#include <atomic> //faster and simpler lock for simple types(int,bool)
#include <chrono> //modern, precise time measurement and sleeping

//Shared struct
struct RobotState{
    int positionX = 0;
    int positionY = 0;
    int battery = 100;
    double temperature = 25.0;
    bool running = true;
    std::mutex mtx; //hand glove for prevent race conditions
};

void sensorThread(RobotState& state){
    while(state.running){
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); //5Hz
    }
}