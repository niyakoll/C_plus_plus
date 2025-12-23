#include <iostream>
#include <vector> //for dynamic arrays
#include <string> //for proper strings
#include <iomanip> // for formating (setprecision), to fix the dec point
#include <cstdlib> // for rand()
#include <random> //modern way to create random number
#include <ctime> // for time()
void takeReading(std::vector<double>& tempReadings, std::vector<double>& distReadings, std::vector<double>& lightReadings, int& battery){
    //Check battery
    if(battery <= 10){
        std::cout << "Battery too low for sensing!\n";
        return;
    }
    //Method 1(modern version): random device 
    //create a random device
    static std::random_device random;
    //create Mersenne Twister engine
    static std::mt19937 gen(random()); // seed with random device
    //create distribution
    static std::uniform_real_distribution<double> temp_ran(20.0,40.0);
    static std::uniform_real_distribution<double> dist_ran(10.0,200.0);
    static std::uniform_real_distribution<double> light_ran(100.0,1000.0);
    //Method 2 (old version): Simulate relistic values
    //double temp = 20.0 + (rand()%20); //20-40 C
    //double dist = 10.0 + (rand()%190) / 10.0; //10-200 cm
    //double light = 100 + (rand()%900); //100-1000 lux

    double temp = temp_ran(gen); //20-40 C
    double dist = dist_ran(gen); //10-200 cm
    double light = light_ran(gen); //100-1000 lux

    tempReadings.push_back(temp);
    distReadings.push_back(dist);
    lightReadings.push_back(light);

    battery -= 5;

    std::cout << "New readings taken!\n";
    std::cout << "Temp : " << temp << " °C\n";
    std::cout << "Dist : " << dist << " cm\n";
    std::cout << "Light : " << light << " lux\n";

}
void showHistory(const std::vector<double>& readings, const std::string& sensorName){
    std::cout << "\n === " << sensorName << " History (" << readings.size() << " readings) ===\n";
    if(readings.empty()){
        std::cout << "No data yet.\n";
        return;
    }
    //Method 1: range base for loop
    for (double value : readings){
        std::cout << sensorName << " : " << value << "\n";
    }
    //Method 2: iterator version
    /* 
    for (auto it = readings.begin() ; it != readings.end(); ++it){
        std::cout << std::fixed << std::setprecision(2);
        std::cout << sensorName << " : " << *it << "\n";
    }
    */
}
double calculateAverage(const std::vector<double>& readings){
    if(readings.empty()){
        return 0.0;
    }
    double sum = 0.0;
    for (double value : readings){
        sum += value;
    }
    return sum / readings.size();
}
//display robot status
void displayStatus(const int& positionX, const int& positionY, const int& battery) {
    std::cout << "\n--- Robot Status ---\n";
    std::cout << "positionX : " << positionX << std::endl;
    std::cout << "positionY : " << positionY << std::endl;
    std::cout << "Battery : " << battery << std::endl;
}
class Sensor{
    private:
        std::string name;
        std::string unit;
        std::vector<double> readings;
    public:
        Sensor(std::string n,std::string u):name(n),unit(u){

        }
    //Add new readings
    void addReading(double value){
        readings.push_back(value);
    }
    //Show history
    void showHistory()const{
        std::cout << "\n === " << name << " History (" << readings.size() << " readings) ===\n";
        if(readings.empty()){
            std::cout << "No data yet.\n";
            return;
        }
        //Method 1: range base for loop
        for (double value : readings){
            std::cout << name << " : " << value << " " << unit << "\n";
        }
    }
    // Calculate average
    double getAverage() const {
        if (readings.empty()) return 0.0;
        double sum = 0.0;
        for (double v : readings) sum += v;
        return sum / readings.size();
    }
    // Return true if latest reading is anomaly
    bool detcetAnomaly(double threshold = 2.0)const{
        if(readings.size() < 2){
            return false;
        }
        double avg = getAverage();
        double latest = readings.back();
        // Simple rule: if latest > threshold * average
        if (latest > threshold * avg || latest < avg / threshold) {
            std::cout << "ANOMALY DETECTED in " << name 
                      << ": " << latest << " " << unit 
                      << " (avg: " << avg << ")\n";
            return true;
        }
        return false;
    }
    //Get name
    std::string getName() const {
        return name;
    }

};
void ctakeReading(Sensor& temp_readings,Sensor& dist_readings,Sensor& light_readings,Sensor& weight_readings, int& battery){
        //Check battery
        if(battery <= 10){
            std::cout << "Battery too low for sensing!\n";
            return;
        }
        
        static std::random_device random;
        //create Mersenne Twister engine
        static std::mt19937 gen(random()); // seed with random device
        //create distribution
        static std::uniform_real_distribution<double> ctemp_ran(20.0,40.0);
        static std::uniform_real_distribution<double> cdist_ran(10.0,200.0);
        static std::uniform_real_distribution<double> clight_ran(100.0,1000.0);
        static std::uniform_real_distribution<double> cweight_ran(30000.0,80000.0);

        double ctemp = ctemp_ran(gen); //20-40 C
        double cdist = cdist_ran(gen); //10-200 cm
        double clight = clight_ran(gen); //100-1000 lux
        double cweight = cweight_ran(gen);

        temp_readings.addReading(ctemp);
        dist_readings.addReading(cdist);
        light_readings.addReading(clight);
        weight_readings.addReading(cweight);

        battery -= 5;

        std::cout << "New readings taken!\n";
        std::cout << "Temp : " << ctemp << " °C\n";
        std::cout << "Dist : " << cdist << " cm\n";
        std::cout << "Light : " << clight << " lux\n";
        std::cout << "Weight : " << cweight << " g\n";


    }
int main() {
    int positionX = 0;
    int positionY = 0;
    int battery  = 100;
    int choice;
    double temp_avg;
    double dist_avg;
    double light_avg;
    double weight_avg;

    /*Method 1 : define vector readings one by one
    std::vector<double> tempReadings;
    std::vector<double> distReadings;
    std::vector<double> lightReadings;
    */

    //Method 2: use class to initial Sensor object, no duplicated code
    Sensor temperature("Temperature","°C");
    Sensor distance("Distance","cm");
    Sensor light("Light","lux");
    Sensor weight("Weight","g");

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n\n=== Sensor Data Logger Robot ===\n";
    std::cout << "Starting up...\n\n";
    
    

    do{
        std::cout << "=== Main Menu ===\n";
        std::cout << "1. Take new readings\n";
        std::cout << "2. Show temperature readings\n";
        std::cout << "3. Show distance readings\n";
        std::cout << "4. Show light readings\n";
        std::cout << "5. Show weight readings\n";
        std::cout << "6. Show temperature average\n";
        std::cout << "7. Show distance average\n";
        std::cout << "8. Show light average\n";
        std::cout << "9. Show weight average\n";
        std::cout << "10. Detect anomaly\n";
        std::cout << "11. Show robot status\n";
        std::cout << "12. Quit\n";
        if (!(std::cin >> choice)) {
            std::cin.clear();                  // clear error flag
            std::cin.ignore(10000, '\n');      // discard bad input
            std::cout << "Invalid input! Please enter a number.\n";
            continue;                     // skip switch, show menu again
        }
        switch(choice){
            case 1 :
                //takeReading(tempReadings,distReadings,lightReadings,battery);
                ctakeReading(temperature,distance,light,weight,battery);
                break;
            case 2 :
                //showHistory(tempReadings,"temperature");
                temperature.showHistory();
                break;
            case 3 :
                //showHistory(distReadings,"distance");
                distance.showHistory();
                break;
            case 4 :
                //showHistory(lightReadings,"Light");
                light.showHistory();
                break;
            case 5 :
                weight.showHistory();
                break;
            case 6 :
                //temp_avg = calculateAverage(tempReadings);
                temp_avg = temperature.getAverage();
                std::cout << "Average temperature: " << temp_avg << " °C\n";
                break;
            case 7 :
                //dist_avg = calculateAverage(distReadings);
                dist_avg = distance.getAverage();
                std::cout << "Average distance: " << dist_avg << " cm\n";
                break;
            case 8 :
                //light_avg = calculateAverage(lightReadings);
                light_avg = light.getAverage();
                std::cout << "Average light: " << light_avg << " lux\n";
                break;
            case 9 :
                weight_avg = weight.getAverage();
                std::cout << "Average weight: " << weight_avg << " g\n";
                break;
            case 10 :
                temperature.detcetAnomaly();
                distance.detcetAnomaly();
                light.detcetAnomaly();
                weight.detcetAnomaly();
                break;
            case 11 :
                displayStatus(positionX,positionY,battery);
                break;
            case 12 :
                std::cout << "Shutting down simulator. Goodbye!\n" ;
                break;
            default :
                std::cout << "Invalid choice! Please enter 1-12.\n";
                break;
        }
        if(battery < 10 && choice != 12){
            std::cout << "\n === CRITICAL !!!===\nBattery is " << battery << "%!" << " Recharge immediately!\n" ; 
        }

    }
    while(choice!= 12);

    /*testing
    
    takeReading(tempReadings,distReadings,lightReadings,battery);
    takeReading(tempReadings,distReadings,lightReadings,battery);
    takeReading(tempReadings,distReadings,lightReadings,battery);
    showHistory(tempReadings, "Temperature");
    double temp_avg = calculateAverage(tempReadings);
    std::cout << "Average temperature: " << temp_avg << "°C\n";
    */
    return 0;
}