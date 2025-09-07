
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

class Tree {
public:
    int key;
    Tree* left;
    Tree* right;

    Tree(int val);
    ~Tree();
    static Tree* createNode(int val);
    static Tree* insertNode(Tree* root, int data, bool asBST = false); // Добавлен параметр для выбора типа дерева
    static void prefixTraversal(Tree* root);
    static bool searchInTree(Tree* root, int x); // Переименовано, так как поиск теперь в обычном дереве
    static int countNodes(Tree* root);
    static bool isPerfectlyBalanced(Tree* root);
    static void dump4(const Tree* node, bool high,
        vector<string> const& lpref,
        vector<string> const& cpref,
        vector<string> const& rpref,
        bool is_root, bool is_left,
        shared_ptr<vector<vector<string>>> lines);
    static Tree* inputFromConsole(bool asBST = false);
    static Tree* inputFromFile(string filename, bool asBST = false);
    static Tree* generateRandomTree(bool asBST = false);
    static void deleteTree(Tree* root);
};

// Вспомогательные функции для проверки ввода
namespace InputUtils 
{
    int getInt(const string& prompt);
    bool validateInt(const string& input);
}
