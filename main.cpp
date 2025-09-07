#include <iostream>
#include <string>
#include <sstream>
#include "head.h"

using namespace std;

// Вывод меню программы
void printMenu()
{
    cout << "\nВыберите задачу для выполнения:\n";
    cout << "1. Префиксный обход дерева TreeWork9\n";
    cout << "2. Поиск значения в дереве TreeWork11\n";
    cout << "3. Проверка на идеальную сбалансированность TreeWork19\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

// Функция для безопасного ввода целого числа
int getIntInput(const string& prompt)
{
    string input;
    int value;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        // Удаляем пробелы с начала и конца строки
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        // Проверяем корректность ввода
        bool valid = !input.empty();
        for (size_t i = 0; i < input.size() && valid; ++i)
        {
            if (i == 0 && input[i] == '-') continue;
            if (!isdigit(input[i])) valid = false;
        }

        if (valid)
        {
            try
            {
                value = stoi(input);
                return value;
            }
            catch (...)
            {
                cout << "Число слишком большое. Повторите ввод.\n";
            }
        }
        else
        {
            cout << "Ошибка: введите целое число без лишних символов.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    while (true) {
        printMenu();
        int taskChoice = getIntInput("");

        if (taskChoice == 0) break;
        if (taskChoice < 1 || taskChoice > 3) {
            cout << "Неверный выбор!\n";
            continue;
        }

        cout << "\nВыберите тип дерева:\n";
        cout << "1. Обычное бинарное дерево\n";
        cout << "2. Бинарное дерево поиска\n";
        int treeType = getIntInput("Введите номер (1 или 2): ");
        bool asBST = (treeType == 2);

        Tree* root = nullptr;
        cout << "\nВыберите способ заполнения дерева:\n";
        cout << "1. Ввод с консоли\n";
        cout << "2. Загрузка из файла\n";
        cout << "3. Случайная генерация\n";

        int inputChoice = getIntInput("Введите номер (1-3): ");
        switch (inputChoice) {
        case 1:
            root = Tree::inputFromConsole(asBST);
            break;
        case 2:
            root = Tree::inputFromFile("laba21.txt", asBST);
            break;
        case 3:
            root = Tree::generateRandomTree(asBST);
            break;
        default:
            cout << "Неверный выбор!\n";
            continue;
        }

        if (!root) {
            cout << "Дерево не создано!\n";
            continue;
        }

        cout << "\nПрефиксный обход:\n";
        Tree::prefixTraversal(root);
        cout << "\n\nГрафическое представление дерева:\n";
        Tree::dump4(root, true, {}, {}, {}, true, true, nullptr);

        switch (taskChoice) {
        case 1:
            break;
        case 2: {
            int x = getIntInput("\nВведите значение для поиска: ");
            cout << "Значение " << x << (Tree::searchInTree(root, x) ? " найдено" : " не найдено") << " в дереве.\n";
            break;
        }
        case 3:
            cout << "\nИдеально сбалансированное дерево: " << (Tree::isPerfectlyBalanced(root) ? "True" : "False") << endl;
            break;
        }

        Tree::deleteTree(root);
    }

    return 0;
}
