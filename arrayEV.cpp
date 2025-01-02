#include <iostream>
#include <vector>
using namespace std;

class EVChargingArray {
private:
    vector<bool> stationStatus; // Array to track station status: true = Free, false = Occupied

public:
    // Constructor to initialize stations
    EVChargingArray(int numStations) {
        stationStatus.resize(numStations, true); // All stations are initially Free
        cout << numStations << " stations initialized. All are Free.\n";
    }

    // Mark a station as Occupied
    void occupyStation(int stationID) {
        if (isValidStation(stationID)) {
            if (stationStatus[stationID]) {
                stationStatus[stationID] = false;
                cout << "Station " << stationID << " is now Occupied.\n";
            } else {
                cout << "Station " << stationID << " is already Occupied.\n";
            }
        }
    }

    // Mark a station as Free
    void freeStation(int stationID) {
        if (isValidStation(stationID)) {
            if (!stationStatus[stationID]) {
                stationStatus[stationID] = true;
                cout << "Station " << stationID << " is now Free.\n";
            } else {
                cout << "Station " << stationID << " is already Free.\n";
            }
        }
    }

    // Display all station statuses
    void displayStations() {
        cout << "\nCharging Station Status:\n";
        for (size_t i = 0; i < stationStatus.size(); ++i) {
            cout << "Station " << i << ": " << (stationStatus[i] ? "Free" : "Occupied") << endl;
        }
    }

private:
    // Check if a station ID is valid
    bool isValidStation(int stationID) {
        if (stationID < 0 || stationID >= stationStatus.size()) {
            cout << "Invalid Station ID: " << stationID << ". Please enter a valid ID.\n";
            return false;
        }
        return true;
    }
};

// Main function
int main() {
    int numStations;
    cout << "Enter the number of charging stations: ";
    cin >> numStations;

    EVChargingArray chargingStations(numStations);
    int choice, stationID;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Occupy a Station\n";
        cout << "2. Free a Station\n";
        cout << "3. Display Station Status\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Station ID to Occupy: ";
            cin >> stationID;
            chargingStations.occupyStation(stationID);
            break;
        case 2:
            cout << "Enter Station ID to Free: ";
            cin >> stationID;
            chargingStations.freeStation(stationID);
            break;
        case 3:
            chargingStations.displayStations();
            break;
        case 4:
            cout << "Exiting the system. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
