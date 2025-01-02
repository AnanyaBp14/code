#include <iostream>
using namespace std;

// Node structure for BST
struct BSTNode {
    int slotID;             // Unique ID for the charging slot
    bool isAvailable;       // Availability of the slot
    BSTNode* left;          // Left child
    BSTNode* right;         // Right child

    BSTNode(int id) : slotID(id), isAvailable(true), left(nullptr), right(nullptr) {}
};

// Class for managing the BST
class EVSlotBST {
private:
    BSTNode* root;

    // Helper function to insert a slot into the BST
    BSTNode* insertSlot(BSTNode* node, int slotID) {
        if (!node) return new BSTNode(slotID);

        if (slotID < node->slotID) {
            node->left = insertSlot(node->left, slotID);
        } else if (slotID > node->slotID) {
            node->right = insertSlot(node->right, slotID);
        } else {
            cout << "Slot with ID " << slotID << " already exists.\n";
        }
        return node;
    }

    // Helper function to find a slot in the BST
    BSTNode* findSlot(BSTNode* node, int slotID) {
        if (!node || node->slotID == slotID) return node;

        if (slotID < node->slotID) {
            return findSlot(node->left, slotID);
        } else {
            return findSlot(node->right, slotID);
        }
    }

    // Helper function to display the BST in-order
    void displaySlots(BSTNode* node) {
        if (!node) return;
        displaySlots(node->left);
        cout << "Slot ID: " << node->slotID
             << " | Availability: " << (node->isAvailable ? "Available" : "Occupied") << endl;
        displaySlots(node->right);
    }

public:
    EVSlotBST() : root(nullptr) {}

    // Insert a new charging slot
    void addSlot(int slotID) {
        root = insertSlot(root, slotID);
        cout << "Slot " << slotID << " added successfully.\n";
    }

    // Allocate a slot to an EV
    void allocateSlot(int slotID) {
        BSTNode* slot = findSlot(root, slotID);
        if (!slot) {
            cout << "Slot with ID " << slotID << " does not exist.\n";
            return;
        }
        if (slot->isAvailable) {
            slot->isAvailable = false;
            cout << "Slot " << slotID << " allocated successfully.\n";
        } else {
            cout << "Slot " << slotID << " is already occupied.\n";
        }
    }

    // Deallocate a slot after use
    void deallocateSlot(int slotID) {
        BSTNode* slot = findSlot(root, slotID);
        if (!slot) {
            cout << "Slot with ID " << slotID << " does not exist.\n";
            return;
        }
        if (!slot->isAvailable) {
            slot->isAvailable = true;
            cout << "Slot " << slotID << " deallocated successfully.\n";
        } else {
            cout << "Slot " << slotID << " is already available.\n";
        }
    }

    // Display all slots in the system
    void displaySlots() {
        cout << "\nAll Charging Slots:\n";
        displaySlots(root);
    }
};

// Main function
int main() {
    EVSlotBST evSlots;
    int choice, slotID;

    while (true) {
        cout << "\nEV Charging Slot Management Menu:\n";
        cout << "1. Add Charging Slot\n";
        cout << "2. Allocate Slot to EV\n";
        cout << "3. Deallocate Slot\n";
        cout << "4. Display All Slots\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Slot ID to Add: ";
            cin >> slotID;
            evSlots.addSlot(slotID);
            break;
        case 2:
            cout << "Enter Slot ID to Allocate: ";
            cin >> slotID;
            evSlots.allocateSlot(slotID);
            break;
        case 3:
            cout << "Enter Slot ID to Deallocate: ";
            cin >> slotID;
            evSlots.deallocateSlot(slotID);
            break;
        case 4:
            evSlots.displaySlots();
            break;
        case 5:
            cout << "Exiting EV Charging Slot Management System. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
