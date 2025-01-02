#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class TrafficMonitor {
private:
    vector<string> segmentIDs;      // Dynamic array (vector) for road segment IDs
    vector<int> vehicleCounts;      // Dynamic array (vector) for vehicle counts

public:
    // Update traffic data for a specific road segment
    void updateTrafficData(const string& segmentID, int vehicleCount) {
        if (vehicleCount < 0) {
            cout << "Vehicle count cannot be negative. Please try again.\n";
            return;
        }

        // Find the segment ID in the array
        auto it = find(segmentIDs.begin(), segmentIDs.end(), segmentID);
        if (it != segmentIDs.end()) {
            // If segment exists, update the vehicle count
            int index = distance(segmentIDs.begin(), it);
            vehicleCounts[index] = vehicleCount;
            cout << "Traffic data for segment " << segmentID << " updated to " << vehicleCount << " vehicles.\n";
        } else {
            // If segment does not exist, add it to the arrays
            segmentIDs.push_back(segmentID);
            vehicleCounts.push_back(vehicleCount);
            cout << "Traffic data for segment " << segmentID << " added with " << vehicleCount << " vehicles.\n";
        }
    }

    // Retrieve the vehicle count for a specific road segment
    int getTrafficData(const string& segmentID) const {
        // Find the segment ID in the array
        auto it = find(segmentIDs.begin(), segmentIDs.end(), segmentID);
        if (it != segmentIDs.end()) {
            // If segment found, return the vehicle count
            int index = distance(segmentIDs.begin(), it);
            return vehicleCounts[index];
        } else {
            // If segment does not exist, return -1
            cout << "No data found for segment ID: " << segmentID << endl;
            return -1;
        }
    }

    // Display all traffic data (for debugging or analysis purposes)
    void displayTrafficData() const {
        if (segmentIDs.empty()) {
            cout << "No traffic data available.\n";
            return;
        }

        cout << "Traffic Data for each Road Segment:" << endl;
        for (size_t i = 0; i < segmentIDs.size(); i++) {
            cout << "Segment ID " << segmentIDs[i] << ": " << vehicleCounts[i] << " vehicles" << endl;
        }
    }
};

void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Update traffic data\n";
    cout << "2. Retrieve traffic data\n";
    cout << "3. Display all traffic data\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    TrafficMonitor monitor;
    string segmentID;
    int vehicleCount;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter road segment ID: ";
            cin >> segmentID;
            cout << "Enter vehicle count: ";
            cin >> vehicleCount;
            monitor.updateTrafficData(segmentID, vehicleCount);
            break;

        case 2:
            cout << "Enter road segment ID to retrieve data: ";
            cin >> segmentID;
            vehicleCount = monitor.getTrafficData(segmentID);
            if (vehicleCount != -1) {
                cout << "Vehicles on Segment " << segmentID << ": " << vehicleCount << endl;
            }
            break;

        case 3:
            monitor.displayTrafficData();
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}
