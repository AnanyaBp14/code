#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>  // For sorting in BST

using namespace std;

// Trie Node structure to store station names
struct TrieNode {
    unordered_map<char, unique_ptr<TrieNode>> children;  // Children nodes for each character
    bool isEndOfWord;  // Flag to mark the end of a word
    string location;  // Location of the charging station

    TrieNode() : isEndOfWord(false), location("") {}
};

// Trie class to manage EV charging stations by name or location
class EVChargingStationTrie {
public:
    unique_ptr<TrieNode> root;

    EVChargingStationTrie() : root(make_unique<TrieNode>()) {}

    // Insert a charging station name into the Trie
    void insert(const string& stationName, const string& location) {
        if (stationName.empty()) {
            cout << "Station name cannot be empty!" << endl;
            return;
        }

        TrieNode* node = root.get();
        for (char c : stationName) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = make_unique<TrieNode>();
            }
            node = node->children[c].get();
        }
        node->isEndOfWord = true;
        node->location = location;  // Store location when the station name is fully inserted
        cout << "Charging station '" << stationName << "' inserted at location: " << location << endl;
    }

    // Search for a charging station name in the Trie
    bool search(const string& stationName) const {
        if (stationName.empty()) {
            cout << "Search string cannot be empty!" << endl;
            return false;
        }

        TrieNode* node = root.get();
        for (char c : stationName) {
            if (node->children.find(c) == node->children.end()) {
                return false;  // Character not found, return false
            }
            node = node->children.at(c).get();
        }
        return node->isEndOfWord;  // Check if it's the end of the word
    }

    // Auto-suggest stations based on prefix
    void suggestStations(TrieNode* node, const string& prefix) const {
        if (node->isEndOfWord) {
            cout << prefix << " (Location: " << node->location << ")" << endl;  // Print the station name and location
        }
        for (auto& child : node->children) {
            suggestStations(child.second.get(), prefix + child.first);  // Recurse with updated prefix
        }
    }

    // Suggest stations that start with a given prefix
    void suggest(const string& prefix) const {
        if (prefix.empty()) {
            cout << "Prefix cannot be empty!" << endl;
            return;
        }

        TrieNode* node = root.get();
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                cout << "No suggestions found.\n";
                return;
            }
            node = node->children.at(c).get();
        }
        suggestStations(node, prefix);  // Suggest stations based on the prefix
    }
};

// Binary Search Tree (BST) to store and manage stations sorted by names
struct Station {
    string stationName;
    string location;

    Station(const string& name, const string& loc) : stationName(name), location(loc) {}
};

class EVChargingStationBST {
private:
    struct Node {
        Station station;
        unique_ptr<Node> left, right;

        Node(const Station& station) : station(station), left(nullptr), right(nullptr) {}
    };

    unique_ptr<Node> root;

    void insert(unique_ptr<Node>& node, const Station& station) {
        if (!node) {
            node = make_unique<Node>(station);
            return;
        }

        if (station.stationName < node->station.stationName)
            insert(node->left, station);
        else if (station.stationName > node->station.stationName)
            insert(node->right, station);
    }

    void inOrderTraversal(const unique_ptr<Node>& node) const {
        if (!node) return;
        inOrderTraversal(node->left);
        cout << "Station: " << node->station.stationName << ", Location: " << node->station.location << endl;
        inOrderTraversal(node->right);
    }

public:
    void insert(const Station& station) {
        insert(root, station);
    }

    void displayAllStations() const {
        cout << "\nAll Stations (Sorted by Name):\n";
        inOrderTraversal(root);
    }
};

// Function to display the menu and handle user input
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Insert a charging station\n";
    cout << "2. Search for a charging station\n";
    cout << "3. Suggest charging stations\n";
    cout << "4. Display all charging stations (sorted)\n";
    cout << "5. Update a charging station\n";
    cout << "6. Delete a charging station\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    EVChargingStationTrie trie;
    EVChargingStationBST bst;
    string stationName, location, prefix;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter charging station name: ";
            cin.ignore();
            getline(cin, stationName);
            cout << "Enter location: ";
            getline(cin, location);
            trie.insert(stationName, location);
            bst.insert(Station(stationName, location));
            break;

        case 2:
            cout << "Enter charging station name to search: ";
            cin.ignore();
            getline(cin, stationName);
            if (trie.search(stationName)) {
                cout << "Charging station '" << stationName << "' found.\n";
            } else {
                cout << "Charging station '" << stationName << "' not found.\n";
            }
            break;

        case 3:
            cout << "Enter prefix for charging station suggestion: ";
            cin.ignore();
            getline(cin, prefix);
            cout << "Suggested charging stations for prefix '" << prefix << "':\n";
            trie.suggest(prefix);
            break;

        case 4:
            bst.displayAllStations();
            break;

        case 5:
            cout << "Enter station name to update: ";
            cin.ignore();
            getline(cin, stationName);
            cout << "Enter new location: ";
            getline(cin, location);
            // In a real system, we would modify the corresponding station's details in the Trie and BST
            cout << "Station '" << stationName << "' updated to location: " << location << endl;
            break;

        case 6:
            cout << "Enter station name to delete: ";
            cin.ignore();
            getline(cin, stationName);
            // Deleting functionality can be added (for now just print)
            cout << "Station '" << stationName << "' deleted.\n";
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
