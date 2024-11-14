#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers

class Vehicle {
protected:
    int vehicleID;
    std::string manufacturer;
    std::string model;
    int year;
    static int totalVehicles;

public:
    // Default Constructor
    Vehicle() : vehicleID(0), manufacturer(""), model(""), year(0) {
        totalVehicles++;
    }

    // Parameterized Constructor
    Vehicle(int vID, const std::string& manuf, const std::string& mod, int yr) 
        : vehicleID(vID), manufacturer(manuf), model(mod), year(yr) {
        totalVehicles++;
    }

    // Destructor
    virtual ~Vehicle() {
        totalVehicles--;
    }

    // Setters and Getters
    void setVehicleID(int vID) { vehicleID = vID; }
    void setManufacturer(const std::string& manuf) { manufacturer = manuf; }
    void setModel(const std::string& mod) { model = mod; }
    void setYear(int yr) { year = yr; }
    
    int getVehicleID() const { return vehicleID; }
    std::string getManufacturer() const { return manufacturer; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    
    virtual void displayInfo() const {
        std::cout << "Vehicle ID: " << vehicleID << ", Manufacturer: " << manufacturer 
                  << ", Model: " << model << ", Year: " << year << std::endl;
    }

    static int getTotalVehicles() { return totalVehicles; }
};

// Initialize static member
int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
protected:
    std::string fuelType;

public:
    Car(int vID, const std::string& manuf, const std::string& mod, int yr, const std::string& fuel) 
        : Vehicle(vID, manuf, mod, yr), fuelType(fuel) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Fuel Type: " << fuelType << std::endl;
    }
};

class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar(int vID, const std::string& manuf, const std::string& mod, int yr, const std::string& fuel, int battery)
        : Car(vID, manuf, mod, yr, fuel), batteryCapacity(battery) {}

    void displayInfo() const override {
        Car::displayInfo();
        std::cout << "Battery Capacity: " << batteryCapacity << " kWh" << std::endl;
    }
};

class SportsCar : public ElectricCar {
private:
    int topSpeed;

public:
    SportsCar(int vID, const std::string& manuf, const std::string& mod, int yr, const std::string& fuel, int battery, int speed)
        : ElectricCar(vID, manuf, mod, yr, fuel, battery), topSpeed(speed) {}

    void displayInfo() const override {
        ElectricCar::displayInfo();
        std::cout << "Top Speed: " << topSpeed << " km/h" << std::endl;
    }
};

class Aircraft {
protected:
    int flightRange;

public:
    Aircraft(int range) : flightRange(range) {}

    virtual void displayAircraftInfo() const {
        std::cout << "Flight Range: " << flightRange << " km" << std::endl;
    }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar(int vID, const std::string& manuf, const std::string& mod, int yr, const std::string& fuel, int range)
        : Car(vID, manuf, mod, yr, fuel), Aircraft(range) {}

    void displayInfo() const override {
        Car::displayInfo();
        displayAircraftInfo();
    }
};

class Sedan : public Car {
public:
    Sedan(int vID, const std::string& manuf, const std::string& mod, int yr, const std::string& fuel)
        : Car(vID, manuf, mod, yr, fuel) {}

    void displayInfo() const override {
        Car::displayInfo();
        std::cout << "Vehicle Type: Sedan" << std::endl;
    }
};

class SUV : public Car {
public:
    SUV(int vID, const std::string& manuf, const std::string& mod, int yr, const std::string& fuel)
        : Car(vID, manuf, mod, yr, fuel) {}

    void displayInfo() const override {
        Car::displayInfo();
        std::cout << "Vehicle Type: SUV" << std::endl;
    }
};

class VehicleRegistry {
private:
    std::vector<std::shared_ptr<Vehicle>> vehicles;

public:
    void addVehicle(std::shared_ptr<Vehicle> vehicle) {
        vehicles.push_back(vehicle);
        std::cout << "Vehicle added successfully!\n";
    }

    void displayAllVehicles() const {
        if (vehicles.empty()) {
            std::cout << "No vehicles in the registry.\n";
            return;
        }
        for (const auto& vehicle : vehicles) {
            vehicle->displayInfo();
            std::cout << "--------------------------------\n";
        }
    }

    void searchById(int id) const {
        for (const auto& vehicle : vehicles) {
            if (vehicle->getVehicleID() == id) {
                std::cout << "Vehicle found:\n";
                vehicle->displayInfo();
                return;
            }
        }
        std::cout << "Vehicle with ID " << id << " not found.\n";
    }
};

int main() {
    VehicleRegistry registry;
    int choice, id, year, battery, range, speed;
    std::string manufacturer, model, fuelType;

    do {
        std::cout << "\nVehicle Registry Menu:\n";
        std::cout << "1. Add a Vehicle\n";
        std::cout << "2. View All Vehicles\n";
        std::cout << "3. Search Vehicle by ID\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter Vehicle ID: ";
                std::cin >> id;
                std::cout << "Enter Manufacturer: ";
                std::cin >> manufacturer;
                std::cout << "Enter Model: ";
                std::cin >> model;
                std::cout << "Enter Year: ";
                std::cin >> year;

                std::cout << "\nSelect Vehicle Type:\n";
                std::cout << "1. Car\n2. Electric Car\n3. Sports Car\n4. Flying Car\n5. Sedan\n6. SUV\n";
                int type;
                std::cin >> type;

                switch (type) {
                    case 1:
                        std::cout << "Enter Fuel Type: ";
                        std::cin >> fuelType;
                        registry.addVehicle(std::make_shared<Car>(id, manufacturer, model, year, fuelType));
                        break;
                    case 2:
                        std::cout << "Enter Fuel Type: ";
                        std::cin >> fuelType;
                        std::cout << "Enter Battery Capacity: ";
                        std::cin >> battery;
                        registry.addVehicle(std::make_shared<ElectricCar>(id, manufacturer, model, year, fuelType, battery));
                        break;
                    case 3:
                        std::cout << "Enter Fuel Type: ";
                        std::cin >> fuelType;
                        std::cout << "Enter Battery Capacity: ";
                        std::cin >> battery;
                        std::cout << "Enter Top Speed: ";
                        std::cin >> speed;
                        registry.addVehicle(std::make_shared<SportsCar>(id, manufacturer, model, year, fuelType, battery, speed));
                        break;
                    case 4:
                        std::cout << "Enter Fuel Type: ";
                        std::cin >> fuelType;
                        std::cout << "Enter Flight Range: ";
                        std::cin >> range;
                        registry.addVehicle(std::make_shared<FlyingCar>(id, manufacturer, model, year, fuelType, range));
                        break;
                    case 5:
                        std::cout << "Enter Fuel Type: ";
                        std::cin >> fuelType;
                        registry.addVehicle(std::make_shared<Sedan>(id, manufacturer, model, year, fuelType));
                        break;
                    case 6:
                        std::cout << "Enter Fuel Type: ";
                        std::cin >> fuelType;
                        registry.addVehicle(std::make_shared<SUV>(id, manufacturer, model, year, fuelType));
                        break;
                    default:
                        std::cout << "Invalid vehicle type.\n";
                }
                break;
            case 2:
                registry.displayAllVehicles();
                break;
            case 3:
                std::cout << "Enter Vehicle ID to search: ";
                std::cin >> id;
                registry.searchById(id);
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
