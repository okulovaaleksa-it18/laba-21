#include "head.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <algorithm>

using namespace std;

// Символы для отрисовки дерева
const string ch_hor = "-";
const string ch_ver = "|";
const string ch_ddia = "/";
const string ch_rddia = "\\";

// Конструктор узла дерева
Tree::Tree(int val) : key(val), left(nullptr), right(nullptr) {}

// Деструктор дерева (рекурсивное удаление узлов)
Tree::~Tree()
{
    delete left;
    delete right;
}

// Создание нового узла
Tree* Tree::createNode(int val)
{
    return new Tree(val);
}

// Вставка узла в дерево 
Tree* Tree::insertNode(Tree* root, int data, bool asBST) {
    if (root == nullptr) return createNode(data);

    if (asBST) {
        // Для BST: вставка по правилам бинарного дерева поиска
        if (data < root->key)
            root->left = insertNode(root->left, data, asBST);
        else if (data > root->key)
            root->right = insertNode(root->right, data, asBST);
    }
    else {
        // Для обычного бинарного дерева: вставка в первое доступное место
        if (root->left == nullptr)
            root->left = insertNode(root->left, data, asBST);
        else if (root->right == nullptr)
            root->right = insertNode(root->right, data, asBST);
        else {
            // Если оба поддерева заняты, выбираем случайное для вставки
            if (rand() % 2)
                root->left = insertNode(root->left, data, asBST);
            else
                root->right = insertNode(root->right, data, asBST);
        }
    }
    return root;
}

// Префиксный обход дерева (корень-левое-правое)
void Tree::prefixTraversal(Tree* root) {
    if (root) {
        cout << root->key << " ";
        prefixTraversal(root->left);
        prefixTraversal(root->right);
    }
}

// Поиск значения в обычном бинарном дереве (полный обход)
bool Tree::searchInTree(Tree* root, int x) {
    if (root == nullptr) return false;
    if (root->key == x) return true;
    return searchInTree(root->left, x) || searchInTree(root->right, x);
}

// Подсчет количества узлов в дереве
int Tree::countNodes(Tree* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Проверка на идеальную сбалансированность дерева
bool Tree::isPerfectlyBalanced(Tree* root) {
    if (root == nullptr) return true;

    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);

    if (abs(leftCount - rightCount) > 1)
        return false;

    return isPerfectlyBalanced(root->left) && isPerfectlyBalanced(root->right);
}


// Рекурсивная функция для графического отображения дерева
void Tree::dump4(const Tree* node, bool high,
    vector<string> const& lpref,
    vector<string> const& cpref,
    vector<string> const& rpref,
    bool is_root, bool is_left,
    shared_ptr<vector<vector<string>>> lines)
{
    if (!node) return;

    using VS = vector<string>;
    auto VSCat = [](VS const& a, VS const& b)
        {
            VS r = a;
            r.insert(r.end(), b.begin(), b.end());
            return r;
        };

    if (is_root)
        lines = make_shared<vector<VS>>();
    if (node->left)

        dump4(node->left, high,
            VSCat(lpref, high ? VS{ " ", " " } : VS{ " " }),
            VSCat(lpref, high ? VS{ ch_ddia, ch_ver } : VS{ ch_ddia }),
            VSCat(lpref, high ? VS{ ch_hor, " " } : VS{ ch_hor }),
            false, true, lines);

    auto sval = to_string(node->key);
    size_t sm = is_left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);

    for (size_t i = 0; i < sval.size(); ++i)
        lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, { string(1, sval[i]) }));

    if (node->right)
        dump4(node->right, high,
            VSCat(rpref, high ? VS{ ch_hor, " " } : VS{ ch_hor }),
            VSCat(rpref, high ? VS{ ch_rddia, ch_ver } : VS{ ch_rddia }),
            VSCat(rpref, high ? VS{ " ", " " } : VS{ " " }),
            false, false, lines);

    if (is_root)
    {
        VS out;
        for (size_t l = 0;; ++l)
        {
            bool last = true;
            string line;
            for (const auto& vec : *lines)
                if (l < vec.size())
                {
                    line += vec[l];
                    last = false;
                }
                else line += " ";
            if (last) break;
            out.push_back(line);
        }
        for (const auto& s : out)
            cout << s << endl;
    }
}

// Ввод дерева с консоли
Tree* Tree::inputFromConsole(bool asBST) {
    Tree* root = nullptr;
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите элементы:\n";
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        root = insertNode(root, val, asBST);
    }
    return root;
}

// Ввод дерева из файла
Tree* Tree::inputFromFile(string filename, bool asBST) {
    ifstream file(filename);
    Tree* root = nullptr;
    int val;
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return nullptr;
    }
    while (file >> val)
        root = insertNode(root, val, asBST);
    file.close();
    return root;
}

// Генерация случайного дерева
Tree* Tree::generateRandomTree(bool asBST) {
    Tree* root = nullptr;
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    srand(time(0));
    cout << "Сгенерированные элементы: ";
    for (int i = 0; i < n; ++i) {
        int val = rand() % 100;
        cout << val << " ";
        root = insertNode(root, val, asBST);
    }
    cout << endl;
    return root;
}

// Удаление дерева
void Tree::deleteTree(Tree* root) {
    if (root) {
        delete root;
    }
}


namespace InputUtils {
    // Проверка корректности ввода целого числа
    bool validateInt(const string& input)
    {
        if (input.empty()) return false;
        size_t start = 0;
        if (input[0] == '-')
        {
            if (input.length() == 1) return false;
            start = 1;
        }
        return all_of(input.begin() + start, input.end(), [](char c)
            {
                return isdigit(c);
            });
    }

    // Функция для безопасного ввода целого числа
    int getInt(const string& prompt)
    {
        string input;
        while (true)
        {
            if (!prompt.empty()) cout << prompt;

            getline(cin, input);

            // Удаляем пробелы с начала и конца строки
            input.erase(0, input.find_first_not_of(" \t"));
            input.erase(input.find_last_not_of(" \t") + 1);

            if (validateInt(input))
            {
                try
                {
                    return stoi(input);
                }
                catch (...)
                {
                    cout << "Число слишком большое. Пожалуйста, введите другое число: ";
                }
            }
            else
            {
                cout << "Некорректный ввод. Пожалуйста, введите целое число: ";
            }
        }
    }
}
