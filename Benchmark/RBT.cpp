/*
====================================================================
    Red–Black Tree Benchmark — Insert / Search / Delete
    ---------------------------------------------------

    This program implements a classic Red–Black Tree (RBT) with
    support for insertion, deletion, and search. The tree uses raw
    pointers for node links (parent / left / right) because RBT
    rotations and pointer rewiring are considerably more complex
    when attempted with smart pointers. Raw pointers keep the
    implementation correct, readable, and aligned with the way
    professional RBTs are typically written (including those in
    the C++ standard library).

    Memory is fully owned and released by the tree object:
        - Nodes are allocated with 'new'
        - The destructor recursively frees all nodes

    BENCHMARKING
    ------------
    The benchmark uses:
        - 10,000,000 random integers for insertion
        - 100,000 search queries
        - 200,000 deletions

    Random numbers are generated using std::mt19937 with a fixed
    seed to guarantee repeatable, stable measurements.

    WHY A RED–BLACK TREE?
    ---------------------
    A Red–Black Tree maintains a balanced structure across all
    operations, ensuring O(log n) search, insert, and delete time,
    even in the worst case. This makes it ideal for comparing
    behavior with an unbalanced BST implementation.

====================================================================
*/

#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>

enum Color { RED, BLACK };

template<typename T>
class RBTree {
private:

    struct Node {
        T data;
        Color color;
        Node* parent;
        Node* left;
        Node* right;

        Node(const T& value)
            : data(value), color(RED), parent(nullptr), left(nullptr), right(nullptr) {
        }
    };

    Node* root = nullptr;

    // Utility: rotate left
    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left)
            y->left->parent = x;

        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // Utility: rotate right
    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right)
            y->right->parent = x;

        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    // Fixup after insertion
    void fixInsert(Node* z) {
        while (z->parent && z->parent->color == RED) {
            Node* gp = z->parent->parent;

            if (z->parent == gp->left) {
                Node* uncle = gp->right;

                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    z = gp;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rotateRight(gp);
                }
            }
            else {
                Node* uncle = gp->left;

                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    z = gp;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rotateLeft(gp);
                }
            }
        }
        root->color = BLACK;
    }

    // Search utility
    Node* searchNode(Node* node, const T& key) const {
        if (!node)
            return nullptr;
        if (key == node->data)
            return node;
        if (key < node->data)
            return searchNode(node->left, key);
        return searchNode(node->right, key);
    }

    // Find minimum in subtree
    Node* minNode(Node* x) {
        while (x->left)
            x = x->left;
        return x;
    }

    // Replace one subtree with another
    void transplant(Node* u, Node* v) {
        if (!u->parent)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v)
            v->parent = u->parent;
    }

    // Fixup after deletion
    void fixDelete(Node* x) {
        while (x != root && (!x || x->color == BLACK)) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w && w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if ((!w->left || w->left->color == BLACK) &&
                    (!w->right || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (!w->right || w->right->color == BLACK) {
                        if (w->left)
                            w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right)
                        w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else {
                Node* w = x->parent->left;
                if (w && w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if ((!w->right || w->right->color == BLACK) &&
                    (!w->left || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (!w->left || w->left->color == BLACK) {
                        if (w->right)
                            w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left)
                        w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        if (x)
            x->color = BLACK;
    }

    // Delete a node
    void deleteNode(Node* z) {
        Node* y = z;
        Node* x = nullptr;
        Color originalColor = y->color;

        if (!z->left) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (!z->right) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minNode(z->right);
            originalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x)
                    x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (originalColor == BLACK && x)
            fixDelete(x);
    }

    // Recursively free all nodes
    void freeTree(Node* node) {
        if (!node) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:

    ~RBTree() {
        freeTree(root);
    }

    // Public insert
    void insert(const T& value) {
        Node* z = new Node(value);
        Node* y = nullptr;
        Node* x = root;

        while (x) {
            y = x;
            if (value < x->data) x = x->left;
            else x = x->right;
        }

        z->parent = y;

        if (!y)
            root = z;
        else if (value < y->data)
            y->left = z;
        else
            y->right = z;

        fixInsert(z);
    }

    bool search(const T& key) const {
        return searchNode(root, key) != nullptr;
    }

    void remove(const T& key) {
        Node* z = searchNode(root, key);
        if (z)
            deleteNode(z);
    }
};



/* ============================================================
                    BENCHMARKING MAIN
   ============================================================ */

int main() {
    std::vector<std::string> words;
    
    std::ifstream file("bigtext.txt");

    if (!file) {
        std::cerr << "Error: cannot open bigfile.txt\n";
        return 1;
    }

    std::string word;

    // ---- LOAD WORDS FROM FILE ----
    while (file >> word) {
        words.push_back(word);
    }

    std::cout << "Loaded " << words.size() << " words.\n";

    RBTree<std::string> rbt;
    int index = words.size() - 1;

    // INSERT
    auto t1 = std::chrono::high_resolution_clock::now();
    for (const auto& w : words)
        rbt.insert(w);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto s1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < std::min<size_t>(100000, words.size()); i++)
        rbt.search(words[i]);
    auto s2 = std::chrono::high_resolution_clock::now();

    // DELETE
    auto d1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < std::min<size_t>(200000, words.size()); i++)
        rbt.remove(words[i]);
    auto d2 = std::chrono::high_resolution_clock::now();

    // RESULTS
    std::cout << "\n=== RED-BLACK TREE PERFORMANCE ===\n";
    std::cout << "Insert time: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
        << " ms\n";

    std::cout << "Search time: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(s2 - s1).count()
        << " ms\n";

    std::cout << "Delete time: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(d2 - d1).count()
        << " ms\n";

    return 0;
    
    
}
