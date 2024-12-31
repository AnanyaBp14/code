#include <iostream>
#include <vector>
using namespace std;

// Structure to represent traffic data at an intersection
struct TrafficData {
    int intersectionID;  // Intersection ID
    int vehicleCount;    // Number of vehicles at this intersection
    double averageSpeed; // Average speed of vehicles at this intersection

    TrafficData(int id, int count, double speed)
        : intersectionID(id), vehicleCount(count), averageSpeed(speed) {}
};

class TrafficMonitor {
private:
    vector<TrafficData> trafficArray; // Array of traffic data at different intersections

public:
    // Add traffic data for an intersection
    void addTrafficData(int id, int vehicleCount, double averageSpeed) {
        trafficArray.push_back(TrafficData(id, vehicleCount, averageSpeed));
    }

    // Update the traffic data for a specific intersection
    void updateTrafficData(int intersectionID, int vehicleCount, double averageSpeed) {
        for (auto& data : trafficArray) {
            if (data.intersectionID == intersectionID) {
                data.vehicleCount = vehicleCount;
                data.averageSpeed = averageSpeed;
                return;
            }
        }
        cout << "Intersection ID not found!" << endl;
    }

    // Get traffic data for a specific intersection
    void getTrafficData(int intersectionID) {
        for (const auto& data : trafficArray) {
            if (data.intersectionID == intersectionID) {
                cout << "Intersection ID: " << data.intersectionID << endl;
                cout << "Vehicle Count: " << data.vehicleCount << endl;
                cout << "Average Speed: " << data.averageSpeed << " km/h" << endl;
                return;
            }
        }
        cout << "Intersection ID not found!" << endl;
    }

    // Display all traffic data
    void displayAllTrafficData() {
        if (trafficArray.empty()) {
            cout << "No traffic data available!" << endl;
            return;
        }
        for (const auto& data : trafficArray) {
            cout << "Intersection ID: " << data.intersectionID << endl;
            cout << "Vehicle Count: " << data.vehicleCount << endl;
            cout << "Average Speed: " << data.averageSpeed << " km/h" << endl;
            cout << "------------------------------" << endl;
        }
    }
};

// Main function to test the traffic monitoring system
int main() {
    TrafficMonitor monitor;

    // Add some traffic data
    monitor.addTrafficData(101, 45, 30.5);  // Intersection 101, 45 vehicles, avg speed 30.5 km/h
    monitor.addTrafficData(102, 30, 25.0);  // Intersection 102, 30 vehicles, avg speed 25.0 km/h
    monitor.addTrafficData(103, 60, 35.0);  // Intersection 103, 60 vehicles, avg speed 35.0 km/h

    // Display all traffic data
    cout << "All Traffic Data:\n";
    monitor.displayAllTrafficData();

    // Update traffic data for a specific intersection
    monitor.updateTrafficData(102, 40, 28.0);  // Intersection 102, 40 vehicles, avg speed 28.0 km/h

    // Get traffic data for a specific intersection
    cout << "\nUpdated Traffic Data for Intersection 102:\n";
    monitor.getTrafficData(102);

    return 0;
}
