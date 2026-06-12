// ************************************************************************************************************************************************************
// preprocessor
// ************************************************************************************************************************************************************
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <vector>

#define CHECK_ERROR(condition, statements) \
    if (!(condition))                      \
    {                                      \
        statements                         \
    }

using std::cout;
using std::endl;
using std::vector;

// ************************************************************************************************************************************************************
// types
// ************************************************************************************************************************************************************
class binarySearchTree
{
  public:
    binarySearchTree() = delete;

    binarySearchTree(uint32_t val) : _key(val)
    {
        _height = 0;
        _parent = nullptr;
        _left   = nullptr;
        _right  = nullptr;
    }

    const uint32_t getKey() const { return _key; }
    const int32_t getHeight() const { return _height; }
    binarySearchTree *getParent() const { return _parent; }
    binarySearchTree *getLeft() const { return _left; }
    binarySearchTree *getRight() const { return _right; }

    void setHeight(int32_t height)
    {
        if (this)
            _height = height;
    }
    void setParent(binarySearchTree *parent_node)
    {
        if (this)
            _parent = parent_node;
    }

    void setLeft(binarySearchTree *left_node)
    {
        if (this)
        {
            _left = left_node;
            left_node->setParent(this);
        }
    }
    void setRight(binarySearchTree *right_node)
    {
        if (this)
        {
            _right = right_node;
            right_node->setParent(this);
        }
    }

  private:
    const uint32_t _key;
    int32_t _height;
    binarySearchTree *_parent;
    binarySearchTree *_left;
    binarySearchTree *_right;
};

// ************************************************************************************************************************************************************
// declarations
// ************************************************************************************************************************************************************
void fillVector(vector<uint32_t> &input, uint32_t max);
void printVector(const vector<uint32_t> &input);
void printVector(const vector<uint32_t> &input, size_t start_idx, size_t end_idx);
void printHeapTree(const vector<uint32_t> &input);
void printHeapTree(const vector<uint32_t> &input, size_t size);
void printBst(const binarySearchTree &root);

size_t find1DPeakLinear(const vector<uint32_t> &input);
size_t find1DPeakRecursive(const vector<uint32_t> &input, int32_t start_idx, int32_t end_idx);
bool check1DPeak(const vector<uint32_t> &input, size_t idx);

bool checkSortingOutput(const vector<uint32_t> &input);
void insertionSort(vector<uint32_t> &input);
void insertionBinarySort(vector<uint32_t> &input);
void mergeSort(vector<uint32_t> &input);

bool isMaxHeap(const vector<uint32_t> &input, size_t size, size_t idx);
void buildMaxHeap(vector<uint32_t> &input);
void heapInsert(vector<uint32_t> &input, uint32_t value);
void heapSort(vector<uint32_t> &input);

bool checkBst(const binarySearchTree &root);
void bstUpdateHeights(binarySearchTree &root);
void bstInsert(binarySearchTree &root, binarySearchTree &new_node);
void bstDelete(binarySearchTree &root, const uint32_t value);
binarySearchTree &bstMin(binarySearchTree &root);
binarySearchTree &bstMax(binarySearchTree &root);
binarySearchTree &bstPredecessor(binarySearchTree &root);
binarySearchTree &bstSuccessor(binarySearchTree &root);

class baseClass
{
  public:
    void func1() { std::cout << "baseClass::func1" << std::endl; }
    virtual void func2() { std::cout << "baseClass::func2" << std::endl; }
};

class derivedClass : public baseClass
{
  public:
    void func1() { std::cout << "derivedClass::func1" << std::endl; }  // adding override would result in an error
    void func2() override { std::cout << "derivedClass::func2" << std::endl; }
};

// ************************************************************************************************************************************************************
// definitions
// ************************************************************************************************************************************************************
int main()
{
    baseClass *basePtr = new derivedClass();  // constructed as derivedClass but stored as baseClass*

    basePtr->func1();  // early binding "baseClass::func1"
    basePtr->func2();  // late binding "derivedClass::func2"

    vector<uint32_t> input(20);  // used vector to avoid sending size for each call with array

    // 1D peak finding
    fillVector(input, 100);
    input = {17, 72, 93, 95, 19, 8, 65, 54, 69, 56, 56, 93, 76, 72, 42, 30, 89, 1, 64, 33};

    size_t peak = input.size();

    cout << "peak finding ------------ " << endl;

    peak = find1DPeakLinear(input);
    cout << "peak is " << input.at(peak) << " at idx " << peak << endl;
    CHECK_ERROR(check1DPeak(input, peak), assert(0);)
    cout << endl;

    peak = find1DPeakRecursive(input, 0, input.size());
    cout << "peak is " << input.at(peak) << " at idx " << peak << endl;
    CHECK_ERROR(check1DPeak(input, peak), assert(0);)
    cout << endl;

    // sorting
    cout << "sorting ---------------- " << endl;

    fillVector(input, 100);
    insertionSort(input);
    CHECK_ERROR(checkSortingOutput(input), assert(0);)
    cout << endl;

    fillVector(input, 100);
    insertionBinarySort(input);
    CHECK_ERROR(checkSortingOutput(input), assert(0);)
    cout << endl;

    fillVector(input, 100);
    printVector(input);
    mergeSort(input);
    printVector(input);
    CHECK_ERROR(checkSortingOutput(input), assert(0);)
    cout << endl;

    // heap
    cout << "heap ---------------- " << endl;
    fillVector(input, 100);
    printHeapTree(input);
    buildMaxHeap(input);
    printHeapTree(input);
    CHECK_ERROR(isMaxHeap(input, input.size(), 0), assert(0);)

    heapInsert(input, std::rand() % 100);
    printHeapTree(input);
    CHECK_ERROR(isMaxHeap(input, input.size(), 0), assert(0);)

    fillVector(input, 100);
    printHeapTree(input);
    heapSort(input);
    CHECK_ERROR(checkSortingOutput(input), assert(0);)

    // binary search tree
    binarySearchTree root(std::rand() % 100);

    bstInsert(root, binarySearchTree(std::rand() % 100));
    bstInsert(root, binarySearchTree(std::rand() % 100));
    bstInsert(root, binarySearchTree(std::rand() % 100));
    bstInsert(root, binarySearchTree(std::rand() % 100));
    bstInsert(root, binarySearchTree(std::rand() % 100));
    bstInsert(root, binarySearchTree(std::rand() % 100));

    printBst(root);
    CHECK_ERROR(checkBst(root), assert(0);)
    cout << endl;

    bstDelete(root, (root.getLeft() != nullptr) ? (root.getLeft()->getKey()) : (root.getRight()->getKey()));
    printBst(root);
    CHECK_ERROR(checkBst(root), assert(0);)
    cout << endl;

    cout << "min is " << bstMin(root).getKey() << endl;
    cout << "max is " << bstMax(root).getKey() << endl;

    cout << "predecessor is " << bstPredecessor(root).getKey() << endl;
    cout << "successor is " << bstSuccessor(root).getKey() << endl;

    // AVL tree
    bstUpdateHeights(root);

    return 0;
}

void fillVector(vector<uint32_t> &input, uint32_t max)
{
    std::srand(unsigned(std::time(nullptr)));
    std::generate(input.begin(), input.end(), std::rand);

    for (uint32_t &element : input)
    {
        element = element % max;
    }
}

void printVector(const vector<uint32_t> &input)
{
    for (const uint32_t &element : input)
    {
        cout << element << " ";
    }
    cout << endl;
}

void printVector(const vector<uint32_t> &input, size_t start_idx, size_t end_idx)
{
    CHECK_ERROR(start_idx <= end_idx, assert(0);)

    for (size_t idx = start_idx; idx <= end_idx; ++idx)
    {
        cout << input.at(idx) << " ";
    }
    cout << endl;
}

void printHeapTree(const vector<uint32_t> &input)
{
    size_t idx        = 0;
    size_t num_layers = ceil(std::log2f(input.size()));

    for (size_t layer = 1; layer <= num_layers; layer++)
    {
        for (size_t element = 0; element < (pow(2, layer - 1)) && (idx < input.size()); ++element, ++idx)
        {
            cout << input.at(idx) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printHeapTree(const vector<uint32_t> &input, size_t size)
{
    size_t idx        = 0;
    size_t num_layers = ceil(std::log2f(size));

    for (size_t layer = 1; layer <= num_layers; layer++)
    {
        for (size_t element = 0; element < (pow(2, layer - 1)) && (idx < size); ++element, ++idx)
        {
            cout << input.at(idx) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

std::string getNSpaces(size_t size)
{
    std::string spaces = "";

    for (size_t n = 0; n < size; ++n)
        spaces += " ";

    return spaces;
}

void printBst(const binarySearchTree &root)
{
    binarySearchTree *left  = root.getLeft();
    binarySearchTree *right = root.getRight();

    if (left != nullptr)
    {
        cout << left->getKey() << "(" << left->getHeight() << ")"
             << " <- " << root.getKey() << "(" << root.getHeight() << ")" << endl;
        printBst(*left);
    }

    if (right != nullptr)
    {
        cout << getNSpaces(8);
        cout << root.getKey() << "(" << root.getHeight() << ")"
             << " -> " << right->getKey() << "(" << right->getHeight() << ")" << endl;
        printBst(*right);
    }
}

// ************************************************************************************************************************************************************
// AVL tree
// ************************************************************************************************************************************************************
void bstBalanceTree(binarySearchTree &root)
{
}

// ************************************************************************************************************************************************************
// binary search tree
// ************************************************************************************************************************************************************
bool checkBst(const binarySearchTree &root)
{
    bool flag               = true;
    binarySearchTree *right = root.getRight();
    binarySearchTree *left  = root.getLeft();

    if (right != nullptr)
    {
        flag = right->getKey() > root.getKey();
        flag &= checkBst(*right);
    }

    if (left != nullptr)
    {
        flag = left->getKey() < root.getKey();
        flag &= checkBst(*left);
    }

    return flag;
}

void bstUpdateHeights(binarySearchTree &root)
{
    binarySearchTree *left  = root.getLeft();
    binarySearchTree *right = root.getRight();

    if ((left == nullptr) && (right == nullptr))  // update leaf
    {
        int32_t left_height  = (left != nullptr) ? ((*left).getHeight()) : (-1);
        int32_t right_height = (right != nullptr) ? ((*right).getHeight()) : (-1);
        root.setHeight(std::max(left_height, right_height) + 1);
    }
    else
    {
        if (left != nullptr)
            bstUpdateHeights(*left);

        if (right != nullptr)
            bstUpdateHeights(*right);

        int32_t left_height  = (left != nullptr) ? ((*left).getHeight()) : (-1);
        int32_t right_height = (right != nullptr) ? ((*right).getHeight()) : (-1);
        root.setHeight(std::max(left_height, right_height) + 1);
    }
}

void bstInsert(binarySearchTree &root, binarySearchTree &new_node)
{
    if (new_node.getKey() > root.getKey())
    {
        binarySearchTree *right = root.getRight();
        if (right != nullptr)
        {
            bstInsert(*right, new_node);
        }
        else
        {
            root.setRight(&new_node);
        }
    }
    else if (new_node.getKey() < root.getKey())
    {
        binarySearchTree *left = root.getLeft();
        if (left != nullptr)
        {
            bstInsert(*left, new_node);
        }
        else
        {
            root.setLeft(&new_node);
        }
    }
}

static void bstSwapPointers(binarySearchTree *first, binarySearchTree *second)
{
    binarySearchTree *temp = second;
    second                 = first;
    first                  = temp;
}

static void bstCheckAndSet(binarySearchTree &root, binarySearchTree &node, uint32_t old_value)
{
    if ((root.getLeft() != nullptr) && (old_value == root.getLeft()->getKey()))
        root.setLeft(&node);
    else if ((root.getRight() != nullptr) && (old_value == root.getRight()->getKey()))
        root.setRight(&node);
}

static void bstSwapNodes(binarySearchTree &old_node, binarySearchTree &new_node)
{
    if (old_node.getParent() != nullptr)
    {
        bstCheckAndSet(*old_node.getParent(), new_node, old_node.getKey());  // change child of old parent
    }
    bstSwapPointers(old_node.getParent(), new_node.getParent());  // swap parent pointers

    if (old_node.getLeft() != nullptr)
    {
        old_node.getLeft()->setParent(&new_node);  // change left child's parent to new
    }
    bstSwapPointers(old_node.getLeft(), new_node.getLeft());  // swap left child pointers

    if (old_node.getRight() != nullptr)
    {
        old_node.getRight()->setParent(&new_node);  // same for right
    }
    bstSwapPointers(old_node.getRight(), new_node.getRight());
}

void bstDelete(binarySearchTree &root, const uint32_t value)
{
    if (value > root.getKey())
    {
        binarySearchTree *new_root = root.getRight();
        if (new_root->getKey() == value)  // delete node
        {
            bool is_left_valid  = new_root->getLeft() != nullptr;
            bool is_right_valid = new_root->getRight() != nullptr;
            if (!is_left_valid && !is_right_valid)  // leaf
            {
                if (value == new_root->getParent()->getLeft()->getKey())
                    new_root->getParent()->setLeft(nullptr);
                else if (value == new_root->getParent()->getRight()->getKey())
                    new_root->getParent()->setRight(nullptr);
            }
            else if ((is_left_valid && !is_right_valid) || (!is_left_valid && is_right_valid))  // one node
            {
                if (value == new_root->getParent()->getLeft()->getKey())
                    bstSwapNodes(*new_root, *new_root->getLeft());

                else
                    bstSwapNodes(*new_root, *new_root->getRight());
            }
            else  // both elements
            {
                bstSwapNodes(*new_root, bstSuccessor(*new_root));
            }
        }
        else if ((new_root->getRight() != nullptr) && (value > new_root->getKey()))
        {
            return bstDelete(*(new_root->getRight()), value);
        }
        else if ((new_root->getLeft() != nullptr) && (value < new_root->getKey()))
        {
            return bstDelete(*(new_root->getLeft()), value);
        }
        else
        {
            return;
        }
    }
    else if (value < root.getKey())
    {
        binarySearchTree *new_root = root.getLeft();
        if (new_root->getKey() == value)  // delete node
        {
            bool is_left_valid  = new_root->getLeft() != nullptr;
            bool is_right_valid = new_root->getRight() != nullptr;
            if (!is_left_valid && !is_right_valid)  // leaf
            {
                if (value == new_root->getParent()->getLeft()->getKey())
                    new_root->getParent()->setLeft(nullptr);
                else if (value == new_root->getParent()->getRight()->getKey())
                    new_root->getParent()->setRight(nullptr);
            }
            else if (is_left_valid && !is_right_valid)  // one (left) node
            {
                bstSwapNodes(*new_root, *new_root->getLeft());
            }
            else if (!is_left_valid && is_right_valid)  // one (right) node
            {
                bstSwapNodes(*new_root, *new_root->getRight());
            }
            else  // both elements
            {
                bstSwapNodes(*new_root, bstSuccessor(*new_root));
            }
        }
        else if ((new_root->getRight() != nullptr) && (value > new_root->getKey()))
        {
            return bstDelete(*(new_root->getRight()), value);
        }
        else if ((new_root->getLeft() != nullptr) && (value < new_root->getKey()))
        {
            return bstDelete(*(new_root->getLeft()), value);
        }
        else
        {
            return;
        }
    }
    else if (value == root.getKey())
    {
        binarySearchTree *new_root = &root;
        if (new_root->getKey() == value)  // delete node
        {
            bool is_left_valid  = new_root->getLeft() != nullptr;
            bool is_right_valid = new_root->getRight() != nullptr;
            if (!is_left_valid && !is_right_valid)  // leaf
            {
                if (value == new_root->getParent()->getLeft()->getKey())
                    new_root->getParent()->setLeft(nullptr);
                else if (value == new_root->getParent()->getRight()->getKey())
                    new_root->getParent()->setRight(nullptr);
            }
            else if (is_left_valid && !is_right_valid)  // one (left) node
            {
                bstSwapNodes(*new_root, *new_root->getLeft());
            }
            else if (!is_left_valid && is_right_valid)  // one (right) node
            {
                bstSwapNodes(*new_root, *new_root->getRight());
            }
            else  // both elements
            {
                bstSwapNodes(*new_root, bstSuccessor(*new_root));
            }
        }
        else if ((new_root->getRight() != nullptr) && (value > new_root->getKey()))
        {
            return bstDelete(*(new_root->getRight()), value);
        }
        else if ((new_root->getLeft() != nullptr) && (value < new_root->getKey()))
        {
            return bstDelete(*(new_root->getLeft()), value);
        }
        else
        {
            return;
        }
    }
}

binarySearchTree &bstMin(binarySearchTree &root)
{
    if (root.getLeft() != nullptr)
    {
        return bstMin(*(root.getLeft()));
    }
    else
    {
        return root;
    }
}

binarySearchTree &bstMax(binarySearchTree &root)
{
    if (root.getRight() != nullptr)
    {
        return bstMax(*(root.getRight()));
    }
    else
    {
        return root;
    }
}

binarySearchTree &bstPredecessor(binarySearchTree &root)
{
    if (root.getLeft() != nullptr)
    {
        return bstMin(*(root.getLeft()));
    }
    else if (root.getParent() != nullptr)
    {
        return *root.getParent();
    }
    else
    {
        return root;
    }
}

binarySearchTree &bstSuccessor(binarySearchTree &root)
{
    if (root.getRight() != nullptr)
    {
        return bstMin(*(root.getRight()));
    }
    else if (root.getParent() != nullptr)
    {
        return *root.getParent();
    }
    else

    {
        return root;
    }
}

// ************************************************************************************************************************************************************
// heap
// ************************************************************************************************************************************************************
static size_t
heapParent(size_t idx)
{
    return ((idx - 1) / 2);
}

static size_t heapLeft(size_t idx)
{
    return (2 * idx + 1);
}

static size_t heapRight(size_t idx)
{
    return (2 * idx + 2);
}

bool isMaxHeap(const vector<uint32_t> &input, size_t size, size_t idx)
{
    // leaf if idx in second half of total size
    if (idx > size / 2)
    {
        return true;
    }
    else
    {
        uint32_t parent = 0, left = 0, right = 0;
        size_t left_idx = 0, right_idx = 0;
        bool left_valid = false, right_valid = false;

        left_idx    = heapLeft(idx);
        right_idx   = heapRight(idx);
        left_valid  = left_idx < size;
        right_valid = right_idx < size;

        parent = input.at(idx);
        if (left_valid)
            left = input.at(left_idx);
        if (right_valid)
            right = input.at(right_idx);

        if (left_valid && (right_valid))
        {
            return (parent >= left) && (parent >= right) && isMaxHeap(input, size, left_idx) && isMaxHeap(input, size, right_idx);
        }
        else if (left_valid)
        {
            return (parent >= left) && (isMaxHeap(input, size, left_idx));
        }
        else
        {
            return (parent >= right) && (isMaxHeap(input, size, right_idx));
        }

        return true;  // second-last layer with no children
    }

    return false;
}

static void maxHeapify(vector<uint32_t> &input, size_t size, size_t idx)
{
    cout << "maxHeapifing: " << input.at(idx) << endl;
    printHeapTree(input);

    uint32_t parent = 0, left = 0, right = 0;
    size_t left_idx = 0, right_idx = 0;
    bool left_valid = false, right_valid = false;

    left_idx    = heapLeft(idx);
    right_idx   = heapRight(idx);
    left_valid  = left_idx < size;
    right_valid = right_idx < size;

    parent = input.at(idx);
    if (left_valid)
    {
        CHECK_ERROR(isMaxHeap(input, size, left_idx), assert(0);)
        left = input.at(left_idx);
    }
    if (right_valid)
    {
        CHECK_ERROR(isMaxHeap(input, size, right_idx), assert(0);)
        right = input.at(right_idx);
    }

    if (!isMaxHeap(input, size, idx))  // recurse till subtree not heap
    {
        size_t swap_idx = 0;

        if (left_valid && (right_valid))  // both childs present
        {
            swap_idx = (left >= right) ? (left_idx) : (right_idx);
        }
        else if (left_valid)
        {
            swap_idx = left_idx;
        }
        else
        {
            swap_idx = right_idx;
        }

        // swap
        uint32_t temp      = input.at(idx);
        input.at(idx)      = input.at(swap_idx);
        input.at(swap_idx) = temp;

        if (swap_idx < (input.size() / 2))  // fix child if not a leaf
            maxHeapify(input, size, swap_idx);
    }
}

void buildMaxHeap(vector<uint32_t> &input)
{
    for (size_t idx = ((input.size() / 2) - 1); (idx >= 0) && (idx < input.size()); --idx)
    {
        maxHeapify(input, input.size(), idx);
    }
}

void heapInsert(vector<uint32_t> &input, uint32_t value)
{
    input.push_back(value);
    printHeapTree(input);
    for (size_t idx = (input.size() - 1); idx >= 0 && idx <= input.size(); idx = heapParent(idx))  // recursively heapify parent of newly added value
    {
        maxHeapify(input, input.size(), heapParent(idx));
        // printHeapTree(input);

        size_t grand_parent = heapParent(heapParent(idx));
        if (isMaxHeap(input, input.size(), grand_parent))  // no need to heapify if grand-parent heap property maintained
            break;
    }
}

void heapSort(vector<uint32_t> &input)
{
    buildMaxHeap(input);

    CHECK_ERROR(isMaxHeap(input, input.size(), 1), assert(0);)
    for (size_t size = (input.size() - 1); size > 0 && (size < input.size()); --size)  // > 0 because last (smallest) element will be in place by the end
    {
        // swap first (max) & last element
        uint32_t temp  = input.at(0);
        input.at(0)    = input.at(size);
        input.at(size) = temp;

        maxHeapify(input, size, 0);
        CHECK_ERROR(isMaxHeap(input, size, 0), assert(0););

        // printHeapTree(input, size);
        // printVector(input);
        // cout << endl;
    }
}

// ************************************************************************************************************************************************************
// sorting
// ************************************************************************************************************************************************************
bool checkSortingOutput(const vector<uint32_t> &input)
{
    CHECK_ERROR(input.size() > 0, assert(0);)
    for (size_t idx = 1; idx < input.size(); ++idx)
    {
        if (input.at(idx - 1) > input.at(idx))
            return false;
    }

    return true;
}

void insertionSort(vector<uint32_t> &input)
{
    CHECK_ERROR(input.size() > 0, assert(0);)

    printVector(input);

    for (size_t start_pos = 1; start_pos < input.size(); ++start_pos)
    {
        for (size_t end_pos = start_pos; end_pos > 0; --end_pos)
        {
            if (input.at(end_pos - 1) > input.at(end_pos))
            {
                uint32_t temp         = input.at(end_pos - 1);
                input.at(end_pos - 1) = input.at(end_pos);
                input.at(end_pos)     = temp;
            }
        }
    }

    printVector(input);
}

static size_t binarySearch(const vector<uint32_t> &input, uint32_t value, int32_t start_idx, int32_t end_idx)
{
    // cout << "value: " << value << " " << start_idx << " " << end_idx << endl;

    // start_idx == end_idx means single element left
    // start_idx & end_idx crossing indicates that element > (start_idx - 1) && < (start_idx)
    // if size_t used for idx end_idx int undeflow when start & end cross before first element (insert at start)
    if (start_idx >= end_idx)
    {
        if (input.at(start_idx) > value)
        {
            return start_idx;
        }
        else
        {
            return start_idx + 1;
        }
    }
    else
    {
        int32_t mid_idx = start_idx + (end_idx - start_idx) / 2;

        if (input.at(mid_idx) > value)
        {
            return binarySearch(input, value, start_idx, mid_idx - 1);
        }
        else if (input.at(mid_idx) < value)
        {
            return binarySearch(input, value, mid_idx + 1, end_idx);
        }
        else
        {
            return mid_idx;  // same value
        }
    }
}

void insertionBinarySort(vector<uint32_t> &input)
{
    CHECK_ERROR(input.size() > 0, assert(0);)

    printVector(input);

    for (size_t start_pos = 1; start_pos < input.size(); ++start_pos)
    {
        size_t end_pos = binarySearch(input, input.at(start_pos), 0, start_pos - 1);
        uint32_t temp  = input.at(start_pos);
        input.erase(input.begin() + start_pos);
        input.insert(input.begin() + end_pos, temp);
        // printVector(input);
    }

    printVector(input);
}

static void mergeSortedLists(vector<uint32_t> &input, vector<uint32_t> &left, vector<uint32_t> &right)
{
    input.clear();

    while (left.size() || right.size())
    {
        if (left.size() == 0)
        {
            input.push_back(right.at(0));
            right.erase(right.begin());
            continue;
        }

        if (right.size() == 0)
        {
            input.push_back(left.at(0));
            left.erase(left.begin());
            continue;
        }

        if (left.at(0) < right.at(0))
        {
            input.push_back(left.at(0));
            left.erase(left.begin());
        }
        else
        {
            input.push_back(right.at(0));
            right.erase(right.begin());
        }
    }
}

void mergeSort(vector<uint32_t> &input)
{
    CHECK_ERROR(input.size() > 0, assert(0);)

    // printVector(input);

    if (input.size() == 2)
    {
        if (input.at(0) > input.at(1))
        {
            uint32_t temp = input.at(0);
            input.at(0)   = input.at(1);
            input.at(1)   = temp;
        }
    }
    else if (input.size() == 1)
    {
    }
    else
    {
        size_t half_size = input.size() / 2;
        vector<uint32_t> left(input.begin(), input.begin() + half_size);
        vector<uint32_t> right(input.begin() + half_size, input.end());

        mergeSort(left);
        mergeSort(right);

        mergeSortedLists(input, left, right);
    }

    // printVector(input);
}

// ************************************************************************************************************************************************************
// document distance
// ************************************************************************************************************************************************************

// ************************************************************************************************************************************************************
// 2D peak finding
// ************************************************************************************************************************************************************

// ************************************************************************************************************************************************************
// 1D peak finding
// ************************************************************************************************************************************************************
bool check1DPeak(const vector<uint32_t> &input, size_t idx)
{
    CHECK_ERROR(idx < input.size(), return false;)

    if (0 == idx)
    {
        return (input.at(idx) >= input.at(idx + 1));
    }
    else if ((input.size() - 1) == idx)
    {
        return (input.at(idx) >= input.at(idx - 1));
    }
    else
    {
        return (input.at(idx) >= input.at(idx - 1)) && (input.at(idx) >= input.at(idx + 1));
    }

    CHECK_ERROR(0, assert(0);)
}

size_t find1DPeakLinear(const vector<uint32_t> &input)
{
    auto last_element_itr = input.rbegin();

    printVector(input);

    // base case
    if (1 == input.size())
    {
        return 0;
    }

    // check edges first
    if (*(input.begin()) >= *(input.begin() + 1))
    {
        return 0;
    }
    else if (*(input.end() - 1) >= *(input.end() - 2))
    {
        return (input.end() - input.begin() - 1);
    }
    else
    {
        for (size_t idx = 1; idx < (input.size() - 1); ++idx)
        {
            if ((input.at(idx) > input.at(idx - 1)) && (input.at(idx) > input.at(idx + 1)))
            {
                return idx;
            }
        }
    }

    // peak not found
    return input.size();
}

size_t find1DPeakRecursive(const vector<uint32_t> &input, int32_t start_idx, int32_t end_idx)
{
    auto last_element_itr = input.rbegin();

    printVector(input, start_idx, end_idx - 1);

    // base case
    if (1 == input.size())
    {
        return 0;
    }

    // check edges first
    auto start_itr = input.begin() + start_idx;
    auto end_itr   = input.begin() + end_idx - 1;
    if ((start_itr == input.begin()) && (*start_itr >= *(start_itr + 1)))
    {
        return start_idx;
    }
    else if ((end_itr == (input.end() - 1)) && (*end_itr >= *(end_itr - 1)))
    {
        return (end_idx - 1);
    }
    else
    {
        int32_t mid_idx = start_idx + (end_idx - start_idx) / 2;
        if (input.at(mid_idx - 1) > input.at(mid_idx))  // left
        {
            return find1DPeakRecursive(input, start_idx, mid_idx + 1);
        }
        else if (input.at(mid_idx + 1) > input.at(mid_idx))  // right
        {
            return find1DPeakRecursive(input, mid_idx - 1, end_idx);
        }
        else
        {
            return mid_idx;
        }
    }

    // peak not found
    return input.size();
}