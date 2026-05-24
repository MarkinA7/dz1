#ifndef BSTREE_CPP
#define BSTREE_CPP

#include "BSTree.hpp"
using namespace std;

namespace bst {

template <typename T>
void BSTree<T>::copyTree(Node*& thisRoot, Node* otherRoot) {
    if (otherRoot == nullptr) {
        thisRoot = nullptr;
        return;
    }
    thisRoot = new Node(otherRoot->data);
    copyTree(thisRoot->left, otherRoot->left);
    copyTree(thisRoot->right, otherRoot->right);
}

template <typename T>
void BSTree<T>::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template <typename T>
void BSTree<T>::insertNode(Node*& node, const T& value) {
    if (node == nullptr) {
        node = new Node(value);
    } else if (value < node->data) {
        insertNode(node->left, value);
    } else if (value > node->data) {
        insertNode(node->right, value);
    }
}

template <typename T>
bool BSTree<T>::searchNode(Node* node, const T& value) const {
    if (node == nullptr) return false;
    if (value == node->data) return true;
    if (value < node->data)
        return searchNode(node->left, value);
    else
        return searchNode(node->right, value);
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::findMin(Node* node) const {
    while (node && node->left != nullptr)
        node = node->left;
    return node;
}

template <typename T>
void BSTree<T>::removeNode(Node*& node, const T& value) {
    if (node == nullptr) return;
    if (value < node->data) {
        removeNode(node->left, value);
    } else if (value > node->data) {
        removeNode(node->right, value);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* minRight = findMin(node->right);
            node->data = minRight->data;
            removeNode(node->right, minRight->data);
        }
    }
}

template <typename T>
void BSTree<T>::preorderHelper(Node* node, ostream& os) const {
    if (node != nullptr) {
        os << node->data << " ";
        preorderHelper(node->left, os);
        preorderHelper(node->right, os);
    }
}

template <typename T>
void BSTree<T>::inorderHelper(Node* node, ostream& os) const {
    if (node != nullptr) {
        inorderHelper(node->left, os);
        os << node->data << " ";
        inorderHelper(node->right, os);
    }
}

template <typename T>
void BSTree<T>::postorderHelper(Node* node, ostream& os) const {
    if (node != nullptr) {
        postorderHelper(node->left, os);
        postorderHelper(node->right, os);
        os << node->data << " ";
    }
}

template <typename T>
void BSTree<T>::saveHelper(Node* node, ofstream& ofs) const {
    if (node == nullptr) {
        ofs << "# ";
    } else {
        ofs << node->data << " ";
        saveHelper(node->left, ofs);
        saveHelper(node->right, ofs);
    }
}

template <typename T>
void BSTree<T>::loadHelper(Node*& node, ifstream& ifs) {
    string token;
    if (!(ifs >> token)) return;
    if (token == "#") {
        node = nullptr;
    } else {
        T value;
        istringstream iss(token);
        if (iss >> value) {
            node = new Node(value);
            loadHelper(node->left, ifs);
            loadHelper(node->right, ifs);
        }
    }
}

template <typename T>
BSTree<T>::BSTree() : root(nullptr) {}

template <typename T>
BSTree<T>::BSTree(const BSTree& other) : root(nullptr) {
    copyTree(root, other.root);
}

template <typename T>
BSTree<T>::BSTree(BSTree&& other) noexcept : root(other.root) {
    other.root = nullptr;
}

template <typename T>
BSTree<T>::~BSTree() {
    clear();
}

template <typename T>
void BSTree<T>::insert(const T& value) {
    insertNode(root, value);
}
template <typename T>
void BSTree<T>::remove(const T& value) {
    removeNode(root, value);
}

template <typename T>
void BSTree<T>::clear() {
    destroyTree(root);
    root = nullptr;
}

template <typename T>
bool BSTree<T>::search(const T& value) const {
    return searchNode(root, value);
}

template <typename T>
void BSTree<T>::preorder() const {
    preorderHelper(root, cout);
    cout << endl;
}

template <typename T>
void BSTree<T>::inorder() const {
    inorderHelper(root, cout);
    cout << endl;
}

template <typename T>
void BSTree<T>::postorder() const {
    postorderHelper(root, cout);
    cout << endl;
}

template <typename U>
ostream& operator<<(ostream& os, const BSTree<U>& tree) {
    tree.inorderHelper(tree.root, os);
    return os;
}

template <typename T>
void BSTree<T>::saveToFile(const string& filename) const {
    ofstream ofs(filename);
    if (ofs.is_open()) {
        saveHelper(root, ofs);
        ofs.close();
    }
}

template <typename T>
void BSTree<T>::loadFromFile(const string& filename) {
    clear();
    ifstream ifs(filename);
    if (ifs.is_open()) {
        loadHelper(root, ifs);
        ifs.close();
    }
}

} // namespace bst

#endif // BSTREE_CPP
