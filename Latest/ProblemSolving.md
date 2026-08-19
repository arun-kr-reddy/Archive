# Problem Solving
- [Arrays](#arrays)
- [Hash Tables](#hash-tables)
- [Graphs](#graphs)
- [Array \& Hash Map](#array--hash-map)

## To Do <!-- omit from toc -->
- Bloom Filter

## Arrays
- **Static Array:** fixed (compile-time) length container indexable for the range `[0, n-1]`
- **Dynamic Array:** can resize itself during runtime, resizing requires copying over existing elements
- **Dynamic Array Implementation:**
  - static array with initial size (capacity)
  - keep adding elements keeping tracking of size
  - when size == capacity, create new static array of double the capacity, copy elements over

## Hash Tables
- **Hash Table:** provides a mapping from keys to values using a technique called hashing
- **Hash Function:**
  - maps a key `x` to a whole number, which is used as index
  - 
    |                |                               |
    | -------------- | ----------------------------- |
    | `H(x) == H(y)` | `x` & `y` might be equal      |
    | `H(x) != H(y)` | `x` & `y` certainly not equal |
  - should be deterministic, *i.e.* same index for same key every time
  - should be uniform to minimize hash collisions
  - to be hashable key type should be immutable  
    *example:* lists/set can change in-place, rendering original index unreachable
- **Load Factor:** represents ratio of current size to total capacity of a hash table
- **Re-Hashing:** to maintain `O(1)` lookup, resize table (double *i.e.* exponential) and rehash keys once load factor hits a threshold
- **Hash Collisions:**
  - same hash value generated for two distinct keys
  - **Separate Chaining:**
    - each hash table bucket is a container that can hold multiple collided keys
    - collided keys appended to the container (usually LL)
    - `O(1 + a)`, where `a` is average LL length, as load factor grows `a ≈ n`, *i.e.* `O(n)`
  - **Open Addressing:**
    - search next available slot within the hash table array
    - next slot by offsetting current position to probing sequence function
    - 
      |                            |                                                       |
      | -------------------------- | ----------------------------------------------------- |
      | linear probing             | `P(i) = i`, sequential search for `i`th iteration     |
      | quadratic probing          | `P(i) = i^2`, search further & further away           |
      | double hashing             | `P(k, i) = i * H2(k)`, `H2()` secondary hash function |
      | pseuo-random num generator | `P(k, i) = RNG(H(k))[i]`, `RNG` seeded with `H(k)`    |
    - since probing sequence output used as offset, it should be non-zero
    - **Cycling:**
      - probing function hits same subset of indices repeatedly without checking every slot
      - instead use probing function that produce cycle of exactly table length
      - ![](./Media/Hash_Map_Probing_Cycling.png)
    - **Clustering:**
      - tendency for occupied slots to bunch together in contiguous groups
      - high load factor (~0.8) leads to high clustering, leading to higher search times
      - but linear probing can scan much faster (even at high load factors) due to high cache spatial locality
    - **Tombstones (Removing Element):**
      - elements searched till `NULL` encountered
      - replacing removed element with `NULL` leads to premature search stop
      - instead place unique tomstone marker that is skipped during search
      - tombstones increase load factor, so removed by resize or overwritten by insert
      - lazy relocation (optimization) moves a found key to the first encountered tombstone to shorten probe path for future lookups

## Graphs
- **Graph:** non-linear data structure consisting of a finite set of vertices/nodes and the edges that connect them  
  `(u, v)` represents connection (edge) from `u` to `v`
- **Terminology:**
  - **Neighbor:** vertices connected by an edge
  - **Degree:** number of edges connected to a particular node
  - **Path:** sequence of vertices connected by edges  
    **Path Length:** number of edges in a path  
    *example:* 0 → 6 → 7 → 3 → 2 path has length 4
  - **Cycle:** path that starts & ends at the same vertex  
    *i.e.* all cycles are path, but not all paths are cycles
  - **Connectivity:** if a path exists between two vertices  
    **Connected Component:** subset of vertices that is connected
- **Types:**
  - ![](./Media/Graph_Types.png)
  - **Undirected:** edges have no orientation, *i.e.* `(u,v) == (v,u)`  
    **Directed (Digraph):** edges are uni-directional  
    **Directed Acyclic Graphs (DAGs):** directed graphs with no cycles used to represent structures with dependencies (in compiler, build systems)
  - **Weighted:** edges contain certain weight to represent arbitrary value (cost, distance, quantity)  
  - **Tree:** has three properties
    - connected and acyclic
    - removing edge disconnects graph
    - adding edge creates a cycle
    - ```mermaid
      graph TD
        A --- B
        A --- C
        A --- D
        B --- E
        B --- F
        D --- G
      ```
- **Representation:**
  ```mermaid
  graph LR
    A -->|2| B
    A -->|5| C
    B -->|4| D
    C -->|2| D
    B -->|3| A
    D -->|3| B
    D -->|1| C
  ```
  - **Adjacency Matrix:** `m[i][j]` represents edge weight of going from node `i` → `j`  
    `O(n^2)` space & time (must even scan 0s), but edge weight lookup `O(1)`
    ```
    [*  A  B  C  D]
    [A  0  2  5  0]
    [B  3  0  0  4]
    [C  0  0  0  2]
    [D  0  3  1  0]
    ```
  - **Edge Set:** unordered list of edges (with weight as third param)  
    iterating over all edges and edge weight lookup `O(num_edges)`
    ```
    [(A, B, 2), (A, C, 5), (B, D, 4), (C, D, 2), (B, A, 3), (D, B, 3), (D, C, 1)]
    ```
  - **Adjacency List:** map each nodes to its neighbors
    iterating over all edges `O(num_edges)` but edge weight lookup `O(num_edges_for_node)`
    ```
    A -> [(B, 2), (C, 5)]
    B -> [(A, 3), (D, 4)]
    C -> [(D, 2)]
    D -> [(B, 3), (C, 1)]
    ```
- **Graph Traversal:** start at a vertex and visit every other (connected) vertex  
  `O(V+E)` time, `O(V)` for processing nodes/vertices themselves and `O(E)` for traversing edges looking for neighbors  
  `O(V^2)` for adjacency matrix

### Depth-First Search
- ![](./Media/Graph_DFS.gif)
- **Depth-First Search:** explore as far as possible along each branch by visiting a node and then recursively visiting all of its neighbors before backtracking
- **Recursive DFS:** using call-stack, but can lead to stack overflow
  ```cpp
  visited(num_nodes) = {false};

  depthFirstSearch(node) {
    visited[node] = true; // mark node
    process(node);        // process node

    for (i : neighbors(node)) {
      if (!visited(i)) {
        depthFirstSearch(i); // explore un-visited nodes
      }
    }
  }

  dfs(0); // start from node zero
  ```
- **Iterative DFS:** using explicit stack data structure
  ```cpp
  visited(num_nodes) = {false};
  stack();

  depthFirstSearch() {
    stack.push(0); // start from node zero

    while (stack.size()) {
      node = stack.pop();
      if !(visited(node)) {   // required for correctness (EXPLAINED BELOW)
        visited[node] = true;
        process(node);

        for (i : neighbors(node)) {
          if (!visited(i)) {  // just an optimization
            stack.push(i); // push un-visited nodes
          }
        }
      }
    }
  }
  ```
  - **Why Check Visited After `pop()`?:**
    - in recursion, neighbors immediately visited so duplicates not added to stack
    - in iteration, two nodes with common neighbor will push duplicate nodes to stack  
      **note:** visited check before `push()` optimization to prevent useless `pop()`
- **Post-Order DFS Traversal:** process node only once all neighbor nodes done processing  
  one-line change of moving `process(node)` to the bottom
  ```cpp
  depthFirstSearch(node) {
    visited[node] = true;

    for (i : neighbors(node)) {
      if (!visited(i)) {
        depthFirstSearch(i);
      }
    }

    process(node); // process node once all neighbors done
  }
  ```
- ***Examples:***
  - **Cycle Detection:** any new edge pointing to already visited node
  - **Connected Components:** mark/paint all reachable nodes as being part of same component  
    **note:** will have to visit all clusters
    ```cpp
    for (int i = 0; i < num_nodes; i++) {
      if (!visited[i]) {
        paint++;
        depthFirstSearch(i, paint);
      }
    }
    ```
  - **Topological Sort:** turn DAG into linear ordering such that each node is processed only after all its dependencies are visited  
    DFS post-order outputs what finished last (dependencies done) to what finished first (leaf node)  
    *i.e.* reverse DFS post-order works as topological sort
    ```cpp
    depthFirstSearch(node) {
      visited[node] = true;

      for (i : neighbors(node)) {
        if (!visited(i)) {
          depthFirstSearch(i);
        }
      }

      deque.pushfront(node); // what finished earlier pushed to start
    }
    ```

### Breadth-First Search
- ![](./Media/Graph_BFS.gif)
- **Breadth-First Search:** explores all neighbors at the present depth (*i.e.* distance from root) before moving on to the nodes at the next depth level (*i.e.* exploring in waves)
- **Iterative BFS:** using explicit queue  
  **note:** code similar to iterative DFS will be correct but space inefficient
  ```cpp
  visited(num_nodes) = {false};

  breadthFirstSearch() {
    queue.push_front(0);
    visited[0] = true; // mark visited immediately when added to queue (EXPLAINED BELOW)

    while (queue.size()) {
      node = queue.pop_back();
      process(node);

      for (i : neighbors(node)) {
        if (!visited[i]) {
          queue.push_front(i); // en-queue un-visited nodes for next "wave"
          visited[i] = true;
        }
      }
    }
  }
  ```
  - **Why Mark Visited Immediately After `enqueue()`?:** multiple nodes in same wave will add common neighbor node from next level, causing queue to grow exponentially for complete graphs
- ***Examples:***
  - **Flood Fill:** fill all pixels 4-connected to starting pixel with a new pixel value  
    *i.e.* BFS then fill connected components  
    can also use DFS but BFS more intuitive
  - **Shortest Path:** shortest path between two nodes by leaving a trail of breadcrumbs (parent) then reconstruct the path using it

[CONTINUE](https://www.youtube.com/watch?v=KiCBXu4P-2Y&list=PLDV1Zeh2NRsDGO4--qE8yH72HFL1Km93P&index=6)

# Leetcode
- [Array \& Hash Map](#array--hash-map)
  - [Contains Duplicate (E 217)](#contains-duplicate-e-217)
  - [Valid Anagram (E 242)](#valid-anagram-e-242)
  - [Two Sum (E 1)](#two-sum-e-1)

## Links <!-- omit from toc -->
- [Neetcode Roadmap](https://neetcode.io/roadmap)
- [Leetcode Progress](https://leetcode.com/progress/)

## To Do <!-- omit from toc -->

## Plan <!-- omit from toc -->
- 
  | Week | Topics                                  | #   |
  | ---- | --------------------------------------- | --- |
  | 1    | Arrays & Hashing → Two Pointers → Stack | 12  |
  | 2    | Sliding Window, Binary Search, LL       | 12  |
  | 3    | Trees → Tries                           | 14  |
  | 4    | Backtracking → Heap → Graphs            | 10  |
  | 5    | 1D DP → 2D DP → Advanced Graphs         | 12  |
  | 6    | Intervals, Greedy, Bit Manip, Math      | 15  |

## Array & Hash Map

### Contains Duplicate (E 217)
- `bool containsDuplicate(vector<int>& nums)`
- given integer array `nums`, return true if any value appreads at-least twice
- `O(n)` time & `O(n)` space  
  using sort then linear scan `O(n*logn + n)` time, `O(1)` space
  ```cpp
  bool containsDuplicate(vector<int> &nums) {
    unordered_set<int> prevNumMap;
    prevNumMap.reserve(nums.size());

    for (const int &val : nums) {
      if (prevNumMap.contains(val))
        return true;
      else
        prevNumMap.insert(val);
    }

    return false;
  }
  ```

### Valid Anagram (E 242)
- `bool isAnagram(string s, string t)`
- given two strings `s` &  `t`, return true if they are anagrams (must use all letters and with same frequency)
- `O(n)` time, `O(k)` space (`k == 26` alphabets)  
  ```cpp
  bool isAnagram(string s, string t) {
    if (s.size() != t.size())
      return false;

    unordered_map<char, size_t> charFreq;
    for (const char &c : s)
      charFreq[c]++;

    for (const char &c : t) {
      if (!charFreq.contains(c))
        return false;

      charFreq[c]--;
      if (charFreq[c] == 0)
        charFreq.erase(c);
    }

    return true;
  }
  ```
- **note:** using array of 26 counters same `O()` but practically much faster
  ```cpp
  bool isAnagram(string s, string t) {
    if (s.size() != t.size())
      return false;

    std::array<int, 26> freqCount = {0};
    for (const char &c : s) {
      freqCount[c - 'a']++;
    }

    for (const char &c : t) {
      if (freqCount[c - 'a'] == 0) {
        return false;
      }

      freqCount[c - 'a']--;
    }

    return true;
  }
  ```

### Two Sum (E 1)
- `vector<int> twoSum(vector<int> &nums, int target)`
- given integer array and target, return indices of the two numbers such that they add up to target
- `O(n)` time, `O(n)` space
  ```cpp
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> prevNums;

    for (int i = 0; i < nums.size(); i++) {
      const int required = target - nums[i];
      if (prevNums.contains(required)) {
        return {prevNums[required], i};
      }

      prevNums[nums[i]] = i;
    }

    return {};
  }
  ```