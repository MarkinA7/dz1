#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

namespace bst {

template <typename T>
class BSTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void copyTree(Node*& thisRoot, Node* otherRoot);
    void destroyTree(Node* node);
    void insertNode(Node*& node, const T& value);
    bool searchNode(Node* node, const T& value) const;
    void removeNode(Node*& node, const T& value);
    Node* findMin(Node* node) const;
    void preorderHelper(Node* node, ostream& os) const;
    void inorderHelper(Node* node, ostream& os) const;
    void postorderHelper(Node* node, ostream& os) const;
    void saveHelper(Node* node, ofstream& ofs) const;
    void loadHelper(Node*& node, ifstream& ifs);

public:
    BSTree();
    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;
    ~BSTree();

    void insert(const T& value);
    void remove(const T& value);
    void clear();
    bool search(const T& value) const;
    void preorder() const;
    void inorder() const;
    void postorder() const;

    template <typename U>
    friend ostream& operator<<(ostream& os, const BSTree<U>& tree);

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

} // namespace bst

#include "BSTree.cpp"
#endif // BSTREE_HPP
