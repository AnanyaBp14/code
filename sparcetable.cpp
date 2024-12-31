#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SparseTable {
private:
    vector<vector<int>> st; // 2D vector to store the sparse table
    vector<int> log;       // Stores the logarithms to optimize range queries

public:
    // Constructor to build the sparse table for the given traffic data
    SparseTable(const vector<int>& data) {
        int n = data.size();
        int maxLog = log2(n) + 1;
        
        // Initialize the sparse table
        st.resize(n, vector<int>(maxLog));

        // Fill the first column (st[i][0]) with the original data
        for (int i = 0; i < n; i++) {
            st[i][0] = data[i];
        }

        // Precompute logs
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; i++) {
            log[i] = log[i / 2] + 1;
        }

        // Build the Sparse Table
        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Range Maximum Query (RMQ) from index l to r
    int query(int l, int r) {
        int j = log[r - l + 1]; // Find the highest power of 2 that fits in the range
        return max(st[l][j], st[r - (1 << j) + 1][j]);
    }

    // Display the Sparse Table (for debugging purposes)
    void display() {
        int n = st.size();
        int m = st[0].size();
        cout << "Sparse Table:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << st[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Example traffic data: vehicle count on different road segments
    vector<int> trafficData = {100, 150, 200, 80, 120, 140, 90, 180, 160};

    // Build the Sparse Table for traffic data
    SparseTable st(trafficData);

    // Display the sparse table (optional)
    st.display();

    // Query: Find the maximum vehicle count in the range [2, 5] (segments 3 to 6)
    int maxTraffic = st.query(2, 5); // Segment 3 to Segment 6
    cout << "Max traffic in the range [2, 5]: " << maxTraffic << endl;

    // Query: Find the maximum vehicle count in the range [0, 8] (segments 1 to 9)
    maxTraffic = st.query(0, 8); // Segment 1 to Segment 9
    cout << "Max traffic in the range [0, 8]: " << maxTraffic << endl;

    return 0;
}
