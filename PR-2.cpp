// Answer

#include <iostream>
#include <cstring>

class Train {
private:
    int trainNumber;
    char trainName[50];
    char source[50];
    char destination[50];
    char trainTime[10];
    static int trainCount;

public:

    Train() : trainNumber(0) {
        strcpy(trainName, "");
        strcpy(source, "");
        strcpy(destination, "");
        strcpy(trainTime, "");
        trainCount++;
    }

    Train(int tNumber, const char* tName, const char* src, const char* dest, const char* time) : trainNumber(tNumber) {
        strcpy(trainName, tName);
        strcpy(source, src);
        strcpy(destination, dest);
        strcpy(trainTime, time);
        trainCount++;
    }

    ~Train() {
        trainCount--;
    }

    void setTrainNumber(int tNumber) {
        trainNumber = tNumber;
    }

    void setTrainName(const char* tName) {
        strcpy(trainName, tName);
    }

    void setSource(const char* src) {
        strcpy(source, src);
    }

    void setDestination(const char* dest) {
        strcpy(destination, dest);
    }

    void setTrainTime(const char* time) {
        strcpy(trainTime, time);
    }

    int getTrainNumber() const {
        return trainNumber;
    }

    const char* getTrainName() const {
        return trainName;
    }

    const char* getSource() const {
        return source;
    }

    const char* getDestination() const {
        return destination;
    }

    const char* getTrainTime() const {
        return trainTime;
    }

    void inputTrainDetails() {
        std::cout << "Enter Train Number: ";
        std::cin >> trainNumber;
        std::cin.ignore();
        
        std::cout << "Enter Train Name: ";
        std::cin.getline(trainName, 50);
        
        std::cout << "Enter Source: ";
        std::cin.getline(source, 50);
        
        std::cout << "Enter Destination: ";
        std::cin.getline(destination, 50);
        
        std::cout << "Enter Train Time: ";
        std::cin.getline(trainTime, 10);
    }

    void displayTrainDetails() const {
        std::cout << "Train Number: " << trainNumber << std::endl;
        std::cout << "Train Name: " << trainName << std::endl;
        std::cout << "Source: " << source << std::endl;
        std::cout << "Destination: " << destination << std::endl;
        std::cout << "Train Time: " << trainTime << std::endl;
    }

    static int getTrainCount() {
        return trainCount;
    }
};

int Train::trainCount = 0;

class RailwaySystem {
private:
    Train trains[100];
    int totalTrains;

public:
    RailwaySystem() : totalTrains(0) {}

    void addTrain() {
        if (totalTrains < 100) {
            trains[totalTrains].inputTrainDetails();
            totalTrains++;
            std::cout << "Train added successfully!\n";
        } else {
            std::cout << "Cannot add more trains. Maximum limit reached.\n";
        }
    }

    void displayAllTrains() const {
        if (totalTrains == 0) {
            std::cout << "No trains to display.\n";
            return;
        }

        for (int i = 0; i < totalTrains; ++i) {
            std::cout << "\nTrain " << i + 1 << " Details:\n";
            trains[i].displayTrainDetails();
        }
    }

    void searchTrainByNumber(int number) const {
        bool found = false;
        for (int i = 0; i < totalTrains; ++i) {
            if (trains[i].getTrainNumber() == number) {
                std::cout << "\nTrain found:\n";
                trains[i].displayTrainDetails();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Train with number " << number << " not found.\n";
        }
    }
};

int main() {
    RailwaySystem system;
    int choice, trainNumber;

    do {
        std::cout << "\nRailway System Menu:\n";
        std::cout << "1. Add Train\n";
        std::cout << "2. Display All Trains\n";
        std::cout << "3. Search Train by Number\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.addTrain();
                break;
            case 2:
                system.displayAllTrains();
                break;
            case 3:
                std::cout << "Enter Train Number to search: ";
                std::cin >> trainNumber;
                system.searchTrainByNumber(trainNumber);
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
