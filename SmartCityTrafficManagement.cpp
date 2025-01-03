#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

class SparseTable {
private:
    vector<vector<int>> maxTable, minTable;
    vector<int> logTable;

public:
    SparseTable() {}

    void buildLogTable(int n) {
        logTable.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i / 2] + 1;
        }
    }

    void buildSparseTable(const vector<int>& arr) {
        int n = arr.size();
        int logN = log2(n) + 1;

        maxTable.assign(n, vector<int>(logN, 0));
        minTable.assign(n, vector<int>(logN, INT_MAX));

        for (int i = 0; i < n; i++) {
            maxTable[i][0] = arr[i];
            minTable[i][0] = arr[i];
        }

        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                maxTable[i][j] = max(maxTable[i][j - 1], maxTable[i + (1 << (j - 1))][j - 1]);
                minTable[i][j] = min(minTable[i][j - 1], minTable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int queryMax(int L, int R) {
        L--; R--;
        int j = logTable[R - L + 1];
        return max(maxTable[L][j], maxTable[R - (1 << j) + 1][j]);
    }

    int queryMin(int L, int R) {
        L--; R--;
        int j = logTable[R - L + 1];
        return min(minTable[L][j], minTable[R - (1 << j) + 1][j]);
    }
};

class TrafficMonitor {
private:
    vector<int> trafficData;
    unordered_map<string, int> segmentMap;
    SparseTable sparseTable;

public:
    TrafficMonitor(int n) {
        trafficData.resize(n, 0);
        sparseTable.buildLogTable(n);
    }

    void addSegment(const string& segmentID) {
        if (segmentMap.find(segmentID) != segmentMap.end()) {
            cout << "Segment already exists.\n";
            return;
        }

        if (segmentMap.size() >= trafficData.size()) {
            cout << "Error: Maximum number of segments reached. Cannot add more segments.\n";
            return;
        }

        segmentMap[segmentID] = segmentMap.size();
        cout << "Segment " << segmentID << " added successfully.\n";
    }

    void deleteSegment(const string& segmentID) {
        if (segmentMap.find(segmentID) == segmentMap.end()) {
            cout << "Segment not found.\n";
            return;
        }

        int index = segmentMap[segmentID];
        trafficData[index] = 0;
        segmentMap.erase(segmentID);
        sparseTable.buildSparseTable(trafficData);
        cout << "Segment " << segmentID << " deleted successfully.\n";
    }

    void updateTrafficData(const string& segmentID, int vehicleCount) {
        if (segmentMap.find(segmentID) == segmentMap.end()) {
            cout << "Segment not found. Add the segment first.\n";
            return;
        }

        int index = segmentMap[segmentID];
        trafficData[index] = vehicleCount;
        sparseTable.buildSparseTable(trafficData);
        cout << "Traffic data for segment " << segmentID << " updated to " << vehicleCount << " vehicles.\n";
    }

    int getTrafficData(const string& segmentID) const {
        if (segmentMap.find(segmentID) == segmentMap.end()) {
            cout << "No data found for segment ID: " << segmentID << endl;
            return -1;
        }
        return trafficData[segmentMap.at(segmentID)];
    }

    int queryMaxTraffic(int L, int R) {
        return sparseTable.queryMax(L, R);
    }

    int queryMinTraffic(int L, int R) {
        return sparseTable.queryMin(L, R);
    }

    double queryAverageTraffic(int L, int R) {
        if (L < 1 || R > trafficData.size() || L > R) {
            cout << "Invalid range query.\n";
            return -1;
        }
        return accumulate(trafficData.begin() + (L - 1), trafficData.begin() + R, 0.0) / (R - L + 1);
    }

    int queryTotalTraffic() {
        return accumulate(trafficData.begin(), trafficData.end(), 0);
    }

    void displayRankedSegments() const {
        vector<pair<string, int>> rankedSegments;
        for (const auto& entry : segmentMap) {
            rankedSegments.emplace_back(entry.first, trafficData[entry.second]);
        }
        sort(rankedSegments.begin(), rankedSegments.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        cout << "Segments ranked by traffic:\n";
        for (const auto& segment : rankedSegments) {
            cout << segment.first << ": " << segment.second << " vehicles\n";
        }
    }

    void displayTrafficData() const {
        cout << "Traffic Data for each Road Segment:\n";
        for (const auto& entry : segmentMap) {
            cout << "Segment ID " << entry.first << ": " << trafficData[entry.second] << " vehicles\n";
        }
    }
};

void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add road segment\n";
    cout << "2. Delete road segment\n";
    cout << "3. Update traffic data\n";
    cout << "4. Retrieve traffic data\n";
    cout << "5. Display all traffic data\n";
    cout << "6. Query maximum traffic in a range\n";
    cout << "7. Query minimum traffic in a range\n";
    cout << "8. Query average traffic in a range\n";
    cout << "9. Query total traffic count\n";
    cout << "10. Display ranked segments\n";
    cout << "11. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int numSegments;
    cout << "Enter the total number of road segments: ";
    cin >> numSegments;

    TrafficMonitor monitor(numSegments);
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string segmentID;
            cout << "Enter road segment ID to add: ";
            cin >> segmentID;
            monitor.addSegment(segmentID);
            break;
        }
        case 2: {
            string segmentID;
            cout << "Enter road segment ID to delete: ";
            cin >> segmentID;
            monitor.deleteSegment(segmentID);
            break;
        }
        case 3: {
            string segmentID;
            int vehicleCount;
            cout << "Enter road segment ID: ";
            cin >> segmentID;
            cout << "Enter vehicle count: ";
            cin >> vehicleCount;
            monitor.updateTrafficData(segmentID, vehicleCount);
            break;
        }
        case 4: {
            string segmentID;
            cout << "Enter road segment ID to retrieve data: ";
            cin >> segmentID;
            int vehicleCount = monitor.getTrafficData(segmentID);
            if (vehicleCount != -1) {
                cout << "Vehicles on Segment " << segmentID << ": " << vehicleCount << endl;
            }
            break;
        }
        case 5:
            monitor.displayTrafficData();
            break;
        case 6: {
            int L, R;
            cout << "Enter range (L R) for maximum traffic query: ";
            cin >> L >> R;
            cout << "Maximum traffic: " << monitor.queryMaxTraffic(L, R) << endl;
            break;
        }
        case 7: {
            int L, R;
            cout << "Enter range (L R) for minimum traffic query: ";
            cin >> L >> R;
            cout << "Minimum traffic: " << monitor.queryMinTraffic(L, R) << endl;
            break;
        }
        case 8: {
            int L, R;
            cout << "Enter range (L R) for average traffic query: ";
            cin >> L >> R;
            cout << "Average traffic: " << monitor.queryAverageTraffic(L, R) << endl;
            break;
        }
        case 9:
            cout << "Total traffic across all segments: " << monitor.queryTotalTraffic() << endl;
            break;
        case 10:
            monitor.displayRankedSegments();
            break;
        case 11:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 11.\n";
        }
    } while (choice != 11);

    return 0;
}
