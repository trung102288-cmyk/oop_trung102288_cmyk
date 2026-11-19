#include <iostream>                         
#include <string>                           
#include <iomanip>                          
using namespace std;                        
class Vehicle {                             
protected:                                  
    int vehicleID;                          
    int entryTime;                          
    int parkingDuration;                    
public:                                     
    Vehicle(int id, int entry, int duration) 
        : vehicleID(id), entryTime(entry), parkingDuration(duration) {} 
    virtual ~Vehicle() {}                   
    int getVehicleID() const { return vehicleID; }             
    int getEntryTime() const { return entryTime; }             
    int getParkingDuration() const { return parkingDuration; } 
    void setVehicleID(int id) { vehicleID = id; }              
    void setEntryTime(int entry) { entryTime = entry; }        
    void setParkingDuration(int duration) { parkingDuration = duration; } 
    virtual double calculateFee() const = 0; 
    virtual void display() const = 0;        
    virtual string getType() const = 0;      
};
class Car : public Vehicle {                
private:                                    
    int numberOfSeats;                      
public:                                     
    Car(int id, int entry, int duration, int seats) 
        : Vehicle(id, entry, duration), numberOfSeats(seats) {} 
    double calculateFee() const override {  
        const double baseRate = 6.0;        
        double total = 0.0;                 
        for (int i = 0; i < parkingDuration; ++i) { 
            int currentHour = (entryTime + i) % 24; 
            bool isPeak = (currentHour >= 7 && currentHour < 9) ||   
                          (currentHour >= 17 && currentHour < 19);   
            if (isPeak) {                   
                total += (i < 2) ? baseRate * 1.30 : baseRate; 
            } else {                        
                total += (i < 2) ? baseRate * 0.95 : baseRate * 0.90; 
            }
        }
        return total;                       
    }
    void display() const override {         
        cout << "[Car] ID: " << vehicleID   
             << " | Entry: " << entryTime << "h" 
             << " | Duration: " << parkingDuration << "h" 
             << " | Seats: " << numberOfSeats 
             << " | Fee: $" << fixed << setprecision(2) << calculateFee() 
             << "\n";                       
    }
    string getType() const override {       
        return "Car";                       
    }
};
class Motorcycle : public Vehicle {         
private:                                    
    int engineCapacity;                     
public:                                     
    Motorcycle(int id, int entry, int duration, int cc) 
        : Vehicle(id, entry, duration), engineCapacity(cc) {} 
    double calculateFee() const override {  
        const double baseRate = 4.0;        
        double total = 0.0;                 
        for (int i = 0; i < parkingDuration; ++i) { 
            int currentHour = (entryTime + i) % 24; 
            bool isPeak = (currentHour >= 7 && currentHour < 9) ||   
                          (currentHour >= 17 && currentHour < 19);   
            if (isPeak) {                   
                total += (i < 2) ? baseRate * 1.30 : baseRate; 
            } else {                        
                total += (i < 2) ? baseRate * 0.95 : baseRate * 0.90; 
            }
        }
        return total;                       
    }
    void display() const override {         
        cout << "[Motorcycle] ID: " << vehicleID 
             << " | Entry: " << entryTime << "h" 
             << " | Duration: " << parkingDuration << "h" 
             << " | Engine: " << engineCapacity << "cc" 
             << " | Fee: $" << fixed << setprecision(2) << calculateFee() 
             << "\n";                       
    }
    string getType() const override {      
        return "Motorcycle";               
    }
};
class Bicycle : public Vehicle {            
private:                                    
    bool isElectric;                        
public:                                     
    Bicycle(int id, int entry, int duration, bool electric) 
        : Vehicle(id, entry, duration), isElectric(electric) {} 
    double calculateFee() const override {  
        const double baseRate = 2.0;        
        double total = 0.0;                 
        for (int i = 0; i < parkingDuration; ++i) { 
            int currentHour = (entryTime + i) % 24; 
            bool isPeak = (currentHour >= 7 && currentHour < 9) ||   
                          (currentHour >= 17 && currentHour < 19);   
            if (isPeak) {                  
                total += (i < 2) ? baseRate * 1.30 : baseRate; 
            } else {                        
                total += (i < 2) ? baseRate * 0.95 : baseRate * 0.90; 
            }
        }
        return total;                       
    }
    void display() const override {         
        cout << "[Bicycle] ID: " << vehicleID 
             << " | Entry: " << entryTime << "h" 
             << " | Duration: " << parkingDuration << "h" 
             << " | Type: " << (isElectric ? "Electric" : "Standard")
             << " | Fee: $" << fixed << setprecision(2) << calculateFee() 
             << "\n";                       
    }
    string getType() const override {       
        return "Bicycle";                   
    }
};
class ParkingLot {                          
private:                                    
    int parkID;                             
    int capacity;                          
    int currentVehicleCount;                
    Vehicle** vehicles;                     

void resize() {                         
int newCapacity = capacity * 2;     
Vehicle** newArray = new Vehicle*[newCapacity]; 
for (int i = 0; i < currentVehicleCount; ++i) { 
newArray[i] = vehicles[i];      
}
for (int i = currentVehicleCount; i < newCapacity; ++i) { 
newArray[i] = nullptr;          
}
delete[] vehicles;                  
vehicles = newArray;                
capacity = newCapacity;             
}
public:                                     
ParkingLot(int id, char lotSize, int initialCapacity = 4) 
: parkID(id), size(lotSize), capacity(initialCapacity), currentVehicleCount(0) { 
vehicles = new Vehicle*[capacity];  
for (int i = 0; i < capacity; ++i) { 
vehicles[i] = nullptr;          
}
}
~ParkingLot() {                         
for (int i = 0; i < currentVehicleCount; ++i) { 
delete vehicles[i];             
}
delete[] vehicles;                  
}
int getParkID() const { return parkID; } 
char getSize() const { return size; }    
int getCurrentVehicleCount() const { return currentVehicleCount; } 
bool addVehicle(Vehicle* v) {           
if (v == nullptr) return false;     
for (int i = 0; i < currentVehicleCount; ++i) { 
if (vehicles[i]->getVehicleID() == v->getVehicleID()) { 
return false;               
}
}
if (currentVehicleCount == capacity) { 
resize();                      
}
vehicles[currentVehicleCount++] = v; 
return true;                        
}
bool removeVehicle(int vehicleID) {     
for (int i = 0; i < currentVehicleCount; ++i) { 
if (vehicles[i]->getVehicleID() == vehicleID) { 
delete vehicles[i];         
for (int j = i; j < currentVehicleCount - 1; ++j) { 
vehicles[j] = vehicles[j + 1]; 
}
vehicles[--currentVehicleCount] = nullptr; 
return true;                
}
}
return false;                       
}
void displayLotInfo() const {           
cout << "=== Parking Lot ID: " << parkID 
<< " | Size: " << size         
<< " | Vehicles: " << currentVehicleCount << "/" << capacity << " ===\n"; 
if (currentVehicleCount == 0) {     
cout << "  (Empty lot)\n";    
return;                         
}
for (int i = 0; i < currentVehicleCount; ++i) { 
cout << "  ";                   
vehicles[i]->display();         
}
}
void displayVehiclesByType(const string& type) const { 
for (int i = 0; i < currentVehicleCount; ++i) { 
if (vehicles[i]->getType() == type) { 
cout << "  [Lot " << parkID << "] "; 
vehicles[i]->display();     
}
}
}
void accumulateFees(double& totalFee, int& totalCount) const { 
for (int i = 0; i < currentVehicleCount; ++i) { 
totalFee += vehicles[i]->calculateFee(); 
totalCount++;                   
}
}
};
class SystemInterface {                     
private:                                    
int lotCapacity;                       
int currentLotCount;                    
void resizeLots() {                     
int newCapacity = lotCapacity * 2;  
ParkingLot** newArray = new ParkingLot*[newCapacity]; 
newArray[i] = parkingLots[i];   
}
for (int i = currentLotCount; i < newCapacity; ++i) {
newArray[i] = nullptr;          
}
delete[] parkingLots;              
parkingLots = newArray;            
lotCapacity = newCapacity;          
}
ParkingLot* findLotByID(int parkID) const { 
for (int i = 0; i < currentLotCount; ++i) { 
if (parkingLots[i]->getParkID() == parkID) { 
return parkingLots[i];      
}
}
return nullptr;                    
}
public:                                     
SystemInterface(int initialCapacity = 4) 
: lotCapacity(initialCapacity), currentLotCount(0) { 
parkingLots = new ParkingLot*[lotCapacity]; 
for (int i = 0; i < lotCapacity; ++i) { 
parkingLots[i] = nullptr;       
}
}
~SystemInterface() {                    
for (int i = 0; i < currentLotCount; ++i) { 
delete parkingLots[i];          
}
delete[] parkingLots;               
}
void createParkingLot() {               
int id;                             
char size;                          
cout << "Enter Parking Lot ID: ";   
cin >> id;                          
if (findLotByID(id) != nullptr) {   
cout << "Error: Parking Lot ID already exists!\n"; 
return;                         
}
cout << "Enter Lot Size (S/M/L): "; 
cin >> size;                        
if (currentLotCount == lotCapacity) { 
resizeLots();                   
}
parkingLots[currentLotCount++] = new ParkingLot(id, size); 
cout << "Parking Lot created successfully!\n"; 
}
void addVehicleToLot() {                
int lotID;                          
cout << "Enter Target Parking Lot ID: "; 
cin >> lotID;                       
ParkingLot* lot = findLotByID(lotID); 
if (lot == nullptr) {               
cout << "Error: Parking Lot not found!\n"; 
return;                         
}
int typeChoice;                     
cout << "Select Vehicle Type (1. Car, 2. Motorcycle, 3. Bicycle): "; 
cin >> typeChoice;                  
cout << "Enter Vehicle ID: ";       
cin >> vID;                         
cout << "Enter Entry Time (0-23): "; 
cin >> entry;                       
cout << "Enter Parking Duration (1-23): "; 
cin >> duration;                    
Vehicle* newVehicle = nullptr;      
if (typeChoice == 1) {             
int seats;                      
cout << "Enter Number of Seats: "; 
cin >> seats;                   
newVehicle = new Car(vID, entry, duration, seats); 
} else if (typeChoice == 2) {       
int cc;                         
cout << "Enter Engine Capacity (cc): "; 
cin >> cc;                      
newVehicle = new Motorcycle(vID, entry, duration, cc); 
} else if (typeChoice == 3) {       
int electricInput;              
cout << "Is Electric? (1 = Yes, 0 = No): "; 
cin >> electricInput;           
newVehicle = new Bicycle(vID, entry, duration, electricInput == 1); 
} else {                            
cout << "Invalid vehicle type!\n"; 
return;                         
}
if (lot->addVehicle(newVehicle)) {  
cout << "Vehicle added successfully!\n"; 
} else {                            
delete newVehicle;              
cout << "Error: Duplicate Vehicle ID in this lot!\n"; 
}
}
void removeParkingLot() {               
int lotID;                          
cout << "Enter Parking Lot ID to delete: "; 
cin >> lotID;                      
for (int i = 0; i < currentLotCount; ++i) { 
if (parkingLots[i]->getParkID() == lotID) { 
delete parkingLots[i];      
for (int j = i; j < currentLotCount - 1; ++j) { 
parkingLots[j] = parkingLots[j + 1]; 
}
parkingLots[--currentLotCount] = nullptr; 
cout << "Parking Lot deleted successfully!\n"; 
return;                     
}
}
cout << "Error: Parking Lot not found!\n"; 
}
void removeVehicleFromLot() {           
int lotID, vID;                     
cout << "Enter Parking Lot ID: ";   
cin >> lotID;                       
ParkingLot* lot = findLotByID(lotID);
if (lot == nullptr) {               
cout << "Error: Parking Lot not found!\n"; 
return;                         
}
cout << "Enter Vehicle ID to remove: "; 
cin >> vID;                         
if (lot->removeVehicle(vID)) {      
cout << "Vehicle removed and memory freed!\n"; 
} else {                            
cout << "Error: Vehicle ID not found in this lot!\n"; 
}
}
void displayAllLots() const {           
if (currentLotCount == 0) {         
cout << "No parking lots available.\n"; 
return;                        
}
for (int i = 0; i < currentLotCount; ++i) { 
parkingLots[i]->displayLotInfo(); 
}
}
void displaySpecificLot() const {      
int lotID;                         
cout << "Enter Parking Lot ID: ";   
cin >> lotID;                       
ParkingLot* lot = findLotByID(lotID); 
if (lot == nullptr) {               
cout << "Error: Parking Lot not found!\n"; 
return;                         
}
lot->displayLotInfo();             
}
void listVehiclesByType() const {       
int choice;                         
cout << "Select Type to List (1. Car, 2. Motorcycle, 3. Bicycle): "; 
cin >> choice;                      
string targetType;                  
if (choice == 1) targetType = "Car";
else if (choice == 2) targetType = "Motorcycle"; 
else if (choice == 3) targetType = "Bicycle";    
else {                              
cout << "Invalid choice!\n";    
return;                         
}
cout << "--- Vehicles of type: " << targetType << " ---\n"; 
for (int i = 0; i < currentLotCount; ++i) { 
parkingLots[i]->displayVehiclesByType(targetType); 
}
}
void summarizeAverageFee() const {      
double totalFee = 0.0;              
int totalVehicles = 0;              
for (int i = 0; i < currentLotCount; ++i) { 
parkingLots[i]->accumulateFees(totalFee, totalVehicles); 
}
if (totalVehicles == 0) {           
cout << "No vehicles in the system to calculate average fee.\n"; 
return;                         
}
double averageFee = totalFee / totalVehicles; 
cout << fixed << setprecision(2)    
<< "Total Vehicles: " << totalVehicles 
<< " | Total Revenue: $" << totalFee   
<< " | Average Fee: $" << averageFee << "\n"; 
}
void run() {                           
int choice = 0;                    
do {                                
cout << "\n========= PARKING MANAGEMENT SYSTEM (STAGE 4) =========\n"
<< "1. Create a new Parking Lot\n"
<< "2. Add a Vehicle to a Parking Lot\n"
<< "3. Delete a Parking Lot\n"
<< "4. Remove a Vehicle from a Parking Lot\n"
<< "5. Display all Parking Lots\n"
<< "6. Display Vehicles in a specific Parking Lot\n"
<< "7. List Vehicles by Type\n"
<< "8. Summarize Average Parking Fee\n"
<< "9. Exit Program\n"
<< "Enter your choice (1-9): ";
cin >> choice;                  
switch (choice) {               
case 1: createParkingLot(); break;     
case 2: addVehicleToLot(); break;      
case 3: removeParkingLot(); break;     
case 4: removeVehicleFromLot(); break; 
case 5: displayAllLots(); break;       
case 6: displaySpecificLot(); break;   
case 7: listVehiclesByType(); break;   
case 8: summarizeAverageFee(); break;  
case 9: cout << "Cleaning up memory and exiting...\n"; break; 
default: cout << "Invalid choice. Please try again.\n"; break; 
}
} while (choice != 9);              
}
};

int main() {                               
// Vehicle v(1, 8, 2);                  
SystemInterface system;                 
system.run();                           
return 0;                               
}
