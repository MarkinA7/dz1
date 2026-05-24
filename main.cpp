#include <iostream>
#include "BSTree.hpp"
using namespace std;

int main() {
    using namespace bst;

    BSTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Исходное дерево (in-order): " << tree << endl;

    cout << "Pre-order: ";
    tree.preorder();

    cout << "In-order: ";
    tree.inorder();

    cout << "Post-order: ";
    tree.postorder();

    cout << "Поиск 40: " << (tree.search(40) ? "найден" : "не найден") << endl;
    cout << "Поиск 100: " << (tree.search(100) ? "найден" : "не найден") << endl;

    tree.remove(20);
    cout << "После удаления 20: " << tree << endl;
    tree.remove(30);
    cout << "После удаления 30: " << tree << endl;
    tree.remove(50);
    cout << "После удаления 50: " << tree << endl;

    BSTree<int> copyTree(tree);
    cout << "Копия дерева: " << copyTree << endl;

    BSTree<int> moveTree(move(copyTree));
    cout << "Перемещённое дерево: " << moveTree << endl;
    cout << "Исходное после перемещения (должно быть пусто): " << copyTree << endl;

    moveTree.saveToFile("tree.txt");
    cout << "Дерево сохранено в tree.txt" << endl;

    BSTree<int> loadedTree;
    loadedTree.loadFromFile("tree.txt");
    cout << "Дерево, загруженное из файла: " << loadedTree << endl;

    tree.clear();
    cout << "Исходное дерево после clear(): " << tree << "(пусто)" << endl;

    return 0;
}
