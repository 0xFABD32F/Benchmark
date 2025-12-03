# 🌳 Tree Data Structures Performance Benchmark

[![C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)](https://en.cppreference.com/)
[![Research](https://img.shields.io/badge/paper-LaTeX-orange.svg)](paper.pdf)
[![Code License](https://img.shields.io/badge/Code%20License-MIT-green.svg)](LICENSE)
[![Paper License](https://img.shields.io/badge/Paper%20License-CC%20BY%204.0-blue.svg)](LICENSE)

> **A comprehensive empirical analysis comparing Red-Black Trees, Unbalanced BSTs, and C++ STL containers**

## 📊 Quick Results

Our benchmarks reveal surprising performance characteristics across five data structures:

| Data Structure | Insertion | Search | Deletion | Overall Rank |
|---------------|-----------|--------|----------|--------------|
| 🥇 **unordered_set** | **26,784 ms** | **276 ms** | **930 ms** | 🏆 **#1** |
| 🥈 **Red-Black Tree** | 43,289 ms | 312 ms | 1,053 ms | 🥈 **#2** |
| 🥉 **Unbalanced BST** | 77,955 ms | 717 ms | 1,347 ms | 🥉 **#3** |
| **std::set** | 84,759 ms | 2,409 ms | 3,085 ms | #4 |
| **std::map** | 86,819 ms | 893 ms | 3,139 ms | #5 |

---

## 🎯 Key Findings

### 💡 Hash Tables Dominate
**`std::unordered_set`** consistently outperformed all tree structures:
- ✅ **1.62×** faster insertion than Red-Black Tree
- ✅ **1.13×** faster search than Red-Black Tree
- ✅ **1.13×** faster deletion than Red-Black Tree

### ⚖️ Balanced Trees Matter
**Red-Black Tree** vs **Unbalanced BST**:
- ✅ **1.80×** faster insertion
- ✅ **2.30×** faster search
- ✅ **1.28×** faster deletion

### 🚀 Custom Implementations Win
Our custom Red-Black Tree **dramatically** outperformed STL containers:
- ✅ **7.72×** faster search than `std::set`
- ✅ **2.93×** faster deletion than `std::set`
- ✅ Similar underlying structure, massive performance difference

---

## 📈 Visual Performance Comparison

### Insertion Performance
```
unordered_set ████████████████░░░░░░░░░░░░░░░░░░░░  26,784 ms  ⭐ FASTEST
Red-Black Tree ████████████████████████░░░░░░░░░░░░  43,289 ms
Unbalanced BST ████████████████████████████████████████  77,955 ms
std::set       █████████████████████████████████████████████  84,759 ms
std::map       ██████████████████████████████████████████████  86,819 ms  ⚠️ SLOWEST
```

### Search Performance
```
unordered_set ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  276 ms   ⭐ FASTEST
Red-Black Tree ███░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  312 ms
Unbalanced BST ████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  717 ms
std::map       ██████████░░░░░░░░░░░░░░░░░░░░░░░░░░░  893 ms
std::set       ████████████████████████████░░░░░░░░░░  2,409 ms  ⚠️ SLOWEST
```

### Deletion Performance
```
unordered_set ████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  930 ms   ⭐ FASTEST
Red-Black Tree █████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░  1,053 ms
Unbalanced BST ████████████░░░░░░░░░░░░░░░░░░░░░░░░░  1,347 ms
std::set       ███████████████████████████░░░░░░░░░░░  3,085 ms
std::map       ████████████████████████████░░░░░░░░░░  3,139 ms  ⚠️ SLOWEST
```

---

## 🏗️ Project Structure
```
📦 Benchmark
│── 🔴 RBT.cpp                   # Custom RBT implementation
│── 🌲 Benchmark.cpp             # BST + STL benchmarks
└── 📝 bigtext.txt              # Test dataset
```

---

## 🔬 Methodology

### Test Environment
- **Compiler:** Modern C++ with optimization enabled
- **Dataset:** Large text file with natural language strings
- **Operations:** Sequential insertion, search, and deletion
- **Timing:** High-resolution clock (microsecond precision)

### Data Structures Tested

#### 1️⃣ Red-Black Tree (Custom Implementation)
```cpp
✅ Self-balancing BST
✅ O(log n) guaranteed worst-case
✅ Color-based balancing
✅ Rotations on insert/delete
```

#### 2️⃣ Unbalanced Binary Search Tree
```cpp
⚠️ No balancing mechanism
⚠️ O(n) worst-case possible
✅ Simple implementation
✅ Good for random data
```

#### 3️⃣ std::unordered_set (Hash Table)
```cpp
✅ O(1) average case
✅ Hash-based lookup
⚠️ No ordering guarantees
⚠️ O(n) worst-case collisions
```

#### 4️⃣ std::set (STL Red-Black Tree)
```cpp
✅ O(log n) guaranteed
✅ Ordered iteration
✅ Standard library reliability
⚠️ Abstraction overhead
```

#### 5️⃣ std::map (STL Red-Black Tree)
```cpp
✅ Key-value pairs
✅ O(log n) guaranteed
✅ Ordered iteration
⚠️ Additional memory overhead
```

---

## 🎓 Detailed Analysis

### Performance Ratios (Normalized to unordered_set)

| Structure | Insertion | Search | Deletion | Average |
|-----------|-----------|--------|----------|---------|
| **unordered_set** | **1.00×** | **1.00×** | **1.00×** | **1.00×** |
| Red-Black Tree | 1.62× | 1.13× | 1.13× | 1.29× |
| Unbalanced BST | 2.91× | 2.60× | 1.45× | 2.32× |
| std::set | 3.17× | 8.73× | 3.32× | 5.07× |
| std::map | 3.24× | 3.24× | 3.37× | 3.28× |

### 🔍 Why Custom RBT Beats std::set?

Despite both using Red-Black Tree structure, our custom implementation is **7.72× faster** in search operations:

1. **No abstraction overhead** - Direct node access
2. **Optimized for strings** - Specialized comparison
3. **Minimal metadata** - Only essential node data
4. **Cache-friendly** - Compact memory layout
5. **No iterator guarantees** - Faster modifications

### ⚠️ Surprising Finding: std::set Search Performance

`std::set` showed unexpectedly poor search performance (2,409 ms vs RBT's 312 ms):
- Additional comparison function overhead
- Iterator validity maintenance
- Thread-safety considerations
- Conservative implementation trade-offs

---

## 🚀 Usage

### Compile and Run
```bash
# Compile Red-Black Tree benchmark
g++ -std=c++17 -O2 RBT.cpp -o rbt_benchmark

# Compile BST benchmark
g++ -std=c++17 -O2 Benchmark.cpp -o bst_benchmark

# Run benchmarks
./rbt_benchmark
./bst_benchmark
```

### Requirements
- C++17 or higher
- Standard library support
- Test data file (`bigtext.txt`)

---

## 📚 Implementation Details

### Red-Black Tree Features
```cpp
template<typename T>
class RBTree {
    enum Color { RED, BLACK };
    
    struct Node {
        T data;
        Color color;
        Node *parent, *left, *right;
    };
    
    // Core operations
    void insert(const T& value);     // O(log n)
    bool search(const T& key);       // O(log n)
    void remove(const T& key);       // O(log n)
    
private:
    void fixInsert(Node* z);         // Rebalancing
    void fixDelete(Node* x);         // Rebalancing
    void rotateLeft(Node* x);        // Tree rotation
    void rotateRight(Node* x);       // Tree rotation
};
```

### Unbalanced BST Features
```cpp
class BST {
    struct Node {
        string key;
        Node *left, *right;
    };
    
    // Core operations (no balancing)
    void insert(const string& key);  // O(log n) avg, O(n) worst
    bool search(const string& key);  // O(log n) avg, O(n) worst
    void remove(const string& key);  // O(log n) avg, O(n) worst
};
```

---

## 💭 When to Use What?

### ✅ Use `std::unordered_set` when:
- ✔️ You need maximum performance
- ✔️ Order doesn't matter
- ✔️ You're okay with hash collisions
- ✔️ Memory is not extremely constrained

### ✅ Use Custom Red-Black Tree when:
- ✔️ You need ordered iteration
- ✔️ Performance is critical
- ✔️ Guaranteed O(log n) is required
- ✔️ You can maintain custom code

### ✅ Use `std::set` when:
- ✔️ You need standard library reliability
- ✔️ Development time matters more than performance
- ✔️ Iterator validity is important
- ✔️ Ordered iteration is required

### ❌ Never Use Unbalanced BST when:
- ❌ Data might be sorted or patterned
- ❌ Performance is critical
- ❌ Worst-case guarantees matter

---

## 📖 Research Paper

A comprehensive research paper with detailed analysis, theoretical validation, and visualizations is available:

📄 **[Read the Full Paper (PDF)](paper.pdf)**

### Paper Sections:
1. Introduction and Motivation
2. Background and Related Work
3. Methodology and Experimental Setup
4. Benchmark Results
5. Detailed Analysis and Discussion
6. Theoretical Validation
7. Performance Recommendations
8. Limitations and Future Work
9. Conclusions

---

## 🎯 Conclusions

### Key Takeaways

1. **Hash tables dominate for unordered data** - `unordered_set` wins across all operations
2. **Self-balancing matters** - RBT significantly outperforms unbalanced BST
3. **Custom implementations excel** - 7.72× faster than STL equivalents
4. **STL overhead is real** - Abstraction costs measurable performance
5. **Never use unbalanced BST in production** - Even moderate imbalance degrades performance

### Performance Summary
```
🏆 CHAMPION: std::unordered_set
   - Best all-around performance
   - Consistent across all operations
   - Hash table efficiency validated

🥈 RUNNER-UP: Custom Red-Black Tree
   - Excellent balanced performance
   - Guaranteed O(log n) operations
   - Dramatically faster than STL

🥉 THIRD PLACE: Unbalanced BST
   - Acceptable for random data
   - Degraded but not catastrophic
   - Educational purposes only
```

---

## 🤝 Contributing

Contributions are welcome! Areas for improvement:

- [ ] AVL tree implementation and benchmarks
- [ ] Concurrent access patterns
- [ ] Memory consumption analysis
- [ ] Cache behavior profiling
- [ ] Additional data types (integers, custom objects)
- [ ] Different data distributions (sorted, random, adversarial)

### How to Contribute

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

---

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- C++ Standards Committee for robust STL implementations
- Research community for advancing data structure theory
- Open-source contributors for performance engineering practices

---

## 📧 Contact

For questions or discussions about this research:

- 📧 Email: soukariabdourahmane@gmail.com
- 💬 Issues: [GitHub Issues](https://github.com/0xFABD32F/Benchmark/issues)
- 📄 Paper: [Full Research Paper](paper.pdf)

---

## 📊 Citation

If you use this work in your research, please cite:
```bibtex
@article{tree_benchmark_2025,
  title={Comparative Performance Analysis of Tree-Based Data Structures: Red-Black Trees vs. Unbalanced Binary Search Trees and Standard Library Containers},
  author={SOUKARI Abdourahmane},
  year={2025}
}
```

---

<div align="center">

### ⭐ Star this repository if you found it helpful!

**Made with ❤️ for Computer Science Education**

[⬆ Back to Top](#-tree-data-structures-performance-benchmark)

</div>
