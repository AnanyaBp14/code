#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Trie Node structure
struct TrieNode {
    unordered_map<string, TrieNode*> children;
    bool isAvailable; // Indicates if a slot is available (true = available, false = occupied)

    TrieNode() : isAvailable(true) {}
};

// Trie class for EV Charging Management
class EVChargingTrie {
private:
    TrieNode* root;

public:
    // Constructor
    EVChargingTrie() {
        root = new TrieNode();
    }

    // Add a new charging slot to the trie
    void addSlot(const vector<string>& locationHierarchy) {
        TrieNode* currentNode = root;
        for (const string& location : locationHierarchy) {
            if (!currentNode->children.count(location)) {
                currentNode->children[location] = new TrieNode();
            }
            currentNode = currentNode->children[location];
        }
        cout << "Charging slot added successfully.\n";
    }

    // Allocate a slot if available
    void allocateSlot(const vector<string>& locationHierarchy) {
        TrieNode* slotNode = navigateToSlot(locationHierarchy);
        if (slotNode && slotNode->isAvailable) {
            slotNode->isAvailable = false;
            cout << "Slot allocated successfully.\n";
        } else if (!slotNode) {
            cout << "Error: Slot does not exist.\n";
        } else {
            cout << "Error: Slot already occupied.\n";
        }
    }

    // Free a slot
    void freeSlot(const vector<string>& locationHierarchy) {
        TrieNode* slotNode = navigateToSlot(locationHierarchy);
        if (slotNode && !slotNode->isAvailable) {
            slotNode->isAvailable = true;
            cout << "Slot freed successfully.\n";
        } else if (!slotNode) {
            cout << "Error: Slot does not exist.\n";
        } else {
            cout << "Error: Slot is already free.\n";
        }
    }

    // Check availability of a specific station
    void checkSlotAvailability(const string& stationName) {
        int availableSlots = countAvailableSlots("Vayujiva", stationName, root);
        if (availableSlots >= 0) {
            cout << "Available slots at " << stationName << ": " << availableSlots << endl;
        } else {
            cout << "Error: Station does not exist.\n";
        }
    }

private:
    // Navigate to a specific slot in the trie
    TrieNode* navigateToSlot(const vector<string>& locationHierarchy) {
        TrieNode* currentNode = root;
        for (const string& location : locationHierarchy) {
            if (!currentNode->children.count(location)) {
                return nullptr;
            }
            currentNode = currentNode->children[location];
        }
        return currentNode;
    }

    // Recursively count the available slots at a station
    int countAvailableSlots(const string& cityName, const string& stationName, TrieNode* currentNode) {
        if (!currentNode) return -1; // Invalid node

        // Check if the city is correct
        if (cityName != "Vayujiva") return -1; // Invalid city

        // Navigate to the station node under the city
        if (currentNode->children.count(cityName)) {
            TrieNode* cityNode = currentNode->children[cityName];

            // Check if the station exists under the city
            if (cityNode->children.count(stationName)) {
                TrieNode* stationNode = cityNode->children[stationName];
                // Count the available slots under this station node
                int availableSlots = 0;
                for (auto& slot : stationNode->children) {
                    if (slot.second->isAvailable) {
                        availableSlots++;
                    }
                }
                return availableSlots;
            }
        }

        return -1; // Station does not exist
    }
};

// Helper function to get user input for location hierarchy
vector<string> getLocationHierarchy() {
    vector<string> hierarchy;
    string station, slot;

    cout << "Enter Station Name: ";
    cin >> station;

    cout << "Enter Slot Name: ";
    cin >> slot;

    hierarchy.push_back("Vayujiva"); // Always "Vayujiva"
    hierarchy.push_back(station);
    hierarchy.push_back(slot);

    return hierarchy;
}

// Main function
int main() {
    EVChargingTrie chargingTrie;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Charging Slot\n";
        cout << "2. Allocate Charging Slot\n";
        cout << "3. Free Charging Slot\n";
        cout << "4. Check Available Slots in Station\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        vector<string> locationHierarchy;

        switch (choice) {
        case 1:
            locationHierarchy = getLocationHierarchy();
            chargingTrie.addSlot(locationHierarchy);
            break;

        case 2:
            locationHierarchy = getLocationHierarchy();
            chargingTrie.allocateSlot(locationHierarchy);
            break;

        case 3:
            locationHierarchy = getLocationHierarchy();
            chargingTrie.freeSlot(locationHierarchy);
            break;

        case 4:
            {
                string stationName;
                cout << "Enter Station Name to check available slots: ";
                cin >> stationName;
                chargingTrie.checkSlotAvailability(stationName);
            }
            break;

        case 5:
            cout << "Goodbye! Exiting the system.\n";
            return 0;

        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
}
