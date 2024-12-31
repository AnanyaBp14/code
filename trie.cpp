#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Trie Node structure
struct TrieNode {
    unordered_map<char, TrieNode*> children;  // Children nodes for each character
    bool isEndOfWord;  // Flag to mark the end of a word

    TrieNode() {
        isEndOfWord = false;
    }
};

// Trie class to manage EV charging stations by name or location
class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // Insert a charging station name into the Trie
    void insert(const string& stationName) {
        TrieNode* node = root;
        for (char c : stationName) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;  // Mark the end of the word
    }

    // Search for a charging station name in the Trie
    bool search(const string& stationName) {
        TrieNode* node = root;
        for (char c : stationName) {
            if (node->children.find(c) == node->children.end()) {
                return false;  // Character not found, return false
            }
            node = node->children[c];
        }
        return node->isEndOfWord;  // Check if it's the end of the word
    }

    // Auto-suggest stations based on prefix
    void suggestStations(TrieNode* node, string& prefix) {
        if (node->isEndOfWord) {
            cout << prefix << endl;  // Print the station name
        }
        for (auto& child : node->children) {
            prefix.push_back(child.first);  // Add the character to the prefix
            suggestStations(child.second, prefix);  // Recurse for next level
            prefix.pop_back();  // Backtrack
        }
    }

    // Suggest stations that start with a given prefix
    void suggest(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                cout << "No suggestions found." << endl;
                return;
            }
            node = node->children[c];
        }
        suggestStations(node, prefix);  // Suggest stations based on the prefix
    }
};

// Main function to test the Trie implementation
int main() {
    Trie trie;

    // Insert charging station names into the Trie
    trie.insert("Downtown Charging Station");
    trie.insert("City Center Charging");
    trie.insert("Mall Charging Station");
    trie.insert("Highway Charging Hub");

    // Search for a specific charging station by name
    string searchQuery = "City Center Charging";
    cout << "Searching for '" << searchQuery << "': " 
         << (trie.search(searchQuery) ? "Found" : "Not Found") << endl;

    // Suggest stations based on a prefix
    string prefix = "Mall";
    cout << "\nSuggestions for prefix '" << prefix << "':\n";
    trie.suggest(prefix);

    return 0;
}
