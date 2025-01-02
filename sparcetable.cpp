#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Sparse Table for range maximum queries
class SparseTable {
private:
    vector<vector<int>> table;
    vector<int> log;

public:
    // Build the Sparse Table
    SparseTable(const vector<int>& data) {
        int n = data.size();
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }

        int k = log[n];
        table.resize(n, vector<int>(k + 1));

        // Initialize Sparse Table with input data
        for (int i = 0; i < n; i++) {
            table[i][0] = data[i];
        }

        // Build the Sparse Table
        for (int j = 1; j <= k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = max(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Query for the maximum in a range [L, R]
    int query(int L, int R) {
        int j = log[R - L + 1];
        return max(table[L][j], table[R - (1 << j) + 1][j]);
    }

    // Update traffic data for a segment
    void updateTrafficData(vector<int>& data, int segmentID, int trafficCount) {
        data[segmentID] = trafficCount;
        // Rebuild the Sparse Table after data update
        *this = SparseTable(data);
    }

    // Display all traffic data
    void displayTrafficData(const vector<int>& data) {
        cout << "Traffic Data for All Segments:\n";
        for (size_t i = 0; i < data.size(); i++) {
            cout << "Segment " << (i + 1) << ": " << data[i] << " vehicles\n";  // 1-based index
        }
    }
};

int main() {
    int n;

    // Ask user for the number of traffic segments
    cout << "Enter the number of traffic segments: ";
    cin >> n;

    vector<int> trafficData(n);

    // Build Sparse Table
    SparseTable sparseTable(trafficData);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Update Traffic Data\n";
        cout << "2. Query Maximum Traffic in Range\n";
        cout << "3. Display All Traffic Data\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int segmentID, trafficCount;
                cout << "Enter the segment ID to update (1-based index): ";
                cin >> segmentID;
                if (segmentID < 1 || segmentID > n) {
                    cout << "Invalid segment ID!\n";
                    break;
                }
                cout << "Enter the new traffic count for segment " << segmentID << ": ";
                cin >> trafficCount;
                sparseTable.updateTrafficData(trafficData, segmentID - 1, trafficCount);  // Convert to 0-based
                cout << "Traffic data updated for segment " << segmentID << ".\n";
                break;
            }
            case 2: {
                int L, R;
                cout << "Enter the range [L, R] for the query (1-based index): ";
                cin >> L >> R;
                if (L < 1 || R > n || L > R) {
                    cout << "Invalid range. Please ensure 1 <= L <= R <= " << n << ".\n";
                    break;
                }
                cout << "Maximum traffic between segment " << L << " and " << R << ": "
                     << sparseTable.query(L - 1, R - 1) << " vehicles\n";  // Convert to 0-based
                break;
            }
            case 3:
                sparseTable.displayTrafficData(trafficData);
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);  // Repeat until the user chooses to exit

    return 0;
}
