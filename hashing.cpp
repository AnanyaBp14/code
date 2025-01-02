#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>  // To clear input buffer

using namespace std;

// HashMap to store segment metadata
unordered_map<int, string> segmentMetadata;

// Function to update segment metadata
void updateMetadataHash(int segmentID, const string& name) {
    segmentMetadata[segmentID] = name;
    cout << "Metadata updated for segment " << segmentID << ": " << name << "\n";
}

// Function to retrieve segment metadata
void getMetadataHash(int segmentID) {
    if (segmentMetadata.find(segmentID) != segmentMetadata.end()) {
        cout << "Segment " << segmentID << ": " << segmentMetadata[segmentID] << "\n";
    } else {
        cout << "Error: Segment ID " << segmentID << " not found!\n";
    }
}

// Function to display all metadata
void displayMetadataHash() {
    if (segmentMetadata.empty()) {
        cout << "No metadata available to display.\n";
    } else {
        cout << "\nSegment Metadata (Hash):\n";
        for (const auto& entry : segmentMetadata) {
            cout << "Segment " << entry.first << ": " << entry.second << "\n";
        }
    }
}

// Function to handle user input for updating metadata
void inputMetadata() {
    int segmentID;
    string name;
    cout << "\nEnter segment ID to update: ";
    while (!(cin >> segmentID)) {
        cin.clear();  // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
        cout << "Invalid input! Please enter a valid integer segment ID: ";
    }
    cin.ignore(); // To ignore the newline character left in the buffer
    cout << "Enter metadata (name) for segment " << segmentID << ": ";
    getline(cin, name);

    updateMetadataHash(segmentID, name);
}

// Function to handle the menu display and user choices
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Update Segment Metadata\n";
    cout << "2. Retrieve Segment Metadata\n";
    cout << "3. Display All Segment Metadata\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// Main function to drive the menu options
int main() {
    int choice;

    do {
        displayMenu();

        // Input validation for menu choice
        while (!(cin >> choice)) {
            cin.clear();  // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
            cout << "Invalid input! Please enter a valid menu choice (1-4): ";
        }

        switch (choice) {
            case 1:
                inputMetadata();
                break;
            case 2: {
                int segmentID;
                cout << "Enter segment ID to retrieve metadata: ";
                while (!(cin >> segmentID)) {
                    cin.clear();  // clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
                    cout << "Invalid input! Please enter a valid segment ID: ";
                }
                getMetadataHash(segmentID);
                break;
            }
            case 3:
                displayMetadataHash();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Error: Invalid choice! Please try again.\n";
        }
    } while (choice != 4);  // Repeat until the user chooses to exit

    return 0;
}
