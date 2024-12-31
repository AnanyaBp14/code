#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Traffic data structure: Vehicle count for each road segment
class TrafficMonitor {
private:
    // HashMap to store traffic data (key: road segment ID, value: vehicle count)
    unordered_map<string, int> trafficData;

public:
    // Update traffic data for a specific road segment
    void updateTrafficData(const string& segmentID, int vehicleCount) {
        trafficData[segmentID] = vehicleCount;  // Update or add the data for the given segment ID
    }

    // Retrieve the vehicle count for a specific road segment
    int getTrafficData(const string& segmentID) {
        if (trafficData.find(segmentID) != trafficData.end()) {
            return trafficData[segmentID];
        } else {
            cout << "No data found for segment ID: " << segmentID << endl;
            return -1;  // Indicating that no data was found
        }
    }

    // Display all traffic data (for debugging or analysis purposes)
    void displayTrafficData() {
        cout << "Traffic Data for each Road Segment:" << endl;
        for (const auto& entry : trafficData) {
            cout << "Segment ID " << entry.first << ": " << entry.second << " vehicles" << endl;
        }
    }
};

int main() {
    // Create the TrafficMonitor object
    TrafficMonitor monitor;

    // Simulate traffic data updates
    monitor.updateTrafficData("A1", 120);  // Segment A1: 120 vehicles
    monitor.updateTrafficData("B2", 200);  // Segment B2: 200 vehicles
    monitor.updateTrafficData("C3", 150);  // Segment C3: 150 vehicles
    monitor.updateTrafficData("D4", 80);   // Segment D4: 80 vehicles

    // Display updated traffic data
    monitor.displayTrafficData();

    // Retrieve specific segment data
    int vehiclesOnB2 = monitor.getTrafficData("B2"); // Get data for segment B2
    cout << "Vehicles on Segment B2: " << vehiclesOnB2 << endl;

    // Attempt to retrieve data for a non-existent segment
    int vehiclesOnNonExistent = monitor.getTrafficData("E5"); // Non-existent segment
    cout << "Vehicles on Segment E5: " << vehiclesOnNonExistent << endl;

    return 0;
}
