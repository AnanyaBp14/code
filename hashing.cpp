#include <iostream>
#include <string>
using namespace std;

// Structure to represent an EV Charging Station
struct ChargingStation {
    int id;             // Station ID
    double distance;    // Distance from a central point
    string name;        // Station name
    ChargingStation* left;
    ChargingStation* right;

    ChargingStation(int id, double distance, string name)
        : id(id), distance(distance), name(name), left(nullptr), right(nullptr) {}
};

// Insert a new station into the BST
ChargingStation* insert(ChargingStation* root, int id, double distance, string name) {
    if (root == nullptr) {
        return new ChargingStation(id, distance, name);
    }
    if (distance < root->distance) {
        root->left = insert(root->left, id, distance, name);
    } else {
        root->right = insert(root->right, id, distance, name);
    }
    return root;
}

// Search for the nearest station (minimum distance)
ChargingStation* findNearest(ChargingStation* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Search for a station by name
ChargingStation* searchByName(ChargingStation* root, const string& name) {
    if (root == nullptr || root->name == name) {
        return root;
    }
    if (name < root->name) {
        return searchByName(root->left, name);
    } else {
        return searchByName(root->right, name);
    }
}

// In-order traversal to display all stations
void inOrderTraversal(ChargingStation* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << "ID: " << root->id << ", Distance: " << root->distance
             << ", Name: " << root->name << endl;
        inOrderTraversal(root->right);
    }
}

// Main function
int main() {
    ChargingStation* root = nullptr;

    // Insert some sample charging stations
    root = insert(root, 1, 2.5, "Downtown Charging");
    root = insert(root, 2, 1.2, "Mall Charging Station");
    root = insert(root, 3, 3.8, "Highway Charging Hub");
    root = insert(root, 4, 0.8, "City Center Charging");

    cout << "All Charging Stations (sorted by distance):\n";
    inOrderTraversal(root);

    cout << "\nNearest Charging Station:\n";
    ChargingStation* nearest = findNearest(root);
    if (nearest) {
        cout << "ID: " << nearest->id << ", Distance: " << nearest->distance
             << ", Name: " << nearest->name << endl;
    }

    cout << "\nSearch for 'Mall Charging Station':\n";
    ChargingStation* searchResult = searchByName(root, "Mall Charging Station");
    if (searchResult) {
        cout << "ID: " << searchResult->id << ", Distance: " << searchResult->distance
             << ", Name: " << searchResult->name << endl;
    } else {
        cout << "Station not found!\n";
    }

    return 0;
}
