#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_set>
#include <set>
#include <map>
#include <random>

using namespace std;
using namespace std::chrono;

/* ============================================================
   Custom Unbalanced Binary Search Tree (BST)
   ============================================================ */

struct Node {
    string key;
    Node* left;
    Node* right;

    Node(const string& k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    /* Insert a key recursively into the BST */
    Node* insertRec(Node* node, const string& key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insertRec(node->left, key);
        else if (key > node->key) node->right = insertRec(node->right, key);
        return node; // duplicates ignored
    }

    /* Search for a key recursively */
    bool searchRec(Node* node, const string& key) {
        if (!node) return false;
        if (node->key == key) return true;
        if (key < node->key) return searchRec(node->left, key);
        return searchRec(node->right, key);
    }

    /* Find minimum node (used for deletion) */
    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    /* Delete a key recursively */
    Node* deleteRec(Node* node, const string& key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = deleteRec(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteRec(node->right, key);
        }
        else {
            // Case 1: no child
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Case 2: one child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: two children
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteRec(node->right, temp->key);
        }
        return node;
    }

public:
    BST() : root(nullptr) {}

    void insert(const string& key) { root = insertRec(root, key); }
    bool search(const string& key) { return searchRec(root, key); }
    void remove(const string& key) { root = deleteRec(root, key); }
};


/* ============================================================
   Timer Helper
   ============================================================ */

template <typename Func>
long long measureTime(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}


/* ============================================================
   MAIN BENCHMARK
   ============================================================ */
int main() {
    
    string filename = "bigtext.txt";  // your large file
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }

    vector<string> words;

    string word;
    while (file >> word) {
        words.push_back(word);
    }


    cout << "Loaded " << words.size() << " words.\n\n";  
    

    // Data structures
    unordered_set<string> uset;
    set<string> tset;
    map<string, int> tmap;
    BST bst;

    /* ================= INSERTION BENCHMARK ================= */

    cout << "=== INSERTION ===\n";

    cout << "unordered_set: "
        << measureTime([&]() { for (auto& s : words) uset.insert(s); })
        << " ms\n";

    cout << "set: "
        << measureTime([&]() { for (auto& s : words) tset.insert(s); })
        << " ms\n";

    cout << "map: "
        << measureTime([&]() { for (auto& s : words) tmap[s] = 1; })
        << " ms\n";

    cout << "BST (unbalanced): "
        << measureTime([&]() { for (auto& s : words) bst.insert(s); })
        << " ms\n\n";

    /* ============= SEARCH BENCHMARK (same as rbt.search loop) ============= */

    cout << "=== SEARCH ===\n";

    cout << "unordered_set: "
        << measureTime([&]() {
        for (size_t i = 0; i < std::min<size_t>(100000, words.size()); i++)
            uset.find(words[i]);
            })
        << " ms\n";

    cout << "set: "
        << measureTime([&]() {
        for (size_t i = 0; i < std::min<size_t>(100000, words.size()); i++)
            tset.find(words[i]);
            })
        << " ms\n";

    cout << "map: "
        << measureTime([&]() {
        for (size_t i = 0; i < std::min<size_t>(100000, words.size()); i++)
            tmap.find(words[i]);
            })
        << " ms\n";

    cout << "BST (unbalanced): "
        << measureTime([&]() {
        for (size_t i = 0; i < std::min<size_t>(100000, words.size()); i++)
            bst.search(words[i]);
            })
        << " ms\n";


    /* ============= DELETE BENCHMARK (same as rbt.remove loop) ============= */

    cout << "=== DELETION ===\n";

    cout << "unordered_set: "
        << measureTime([&]() {
        for (size_t i = 0; i < std::min<size_t>(200000, words.size()); i++)
            uset.erase(words[i]);
            })
        << " ms\n";

    cout << "set: "
        << measureTime([&]() {
        for (size_t i = 0; i < std::min<size_t>(200000, words.size()); i++)
            tset.erase(words[i]);
            })
        << " ms\n";

    cout << "map: "
        << measureTime([&]() {
        for (size_t i = 0; i < std::min<size_t>(200000, words.size()); i++)
            tmap.erase(words[i]);
            })
        << " ms\n";

    cout << "BST (unbalanced): "
        << measureTime([&]() {
        for (size_t i = 0; i < std::min<size_t>(200000, words.size()); i++)
            bst.remove(words[i]);
            })
        << " ms\n";
    

    return 0;
}
