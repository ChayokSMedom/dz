#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace TreeNS {

template <typename T>
class BSTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        explicit Node(const T& value);
        explicit Node(T&& value);
    };

    Node* root;

    // Вспомогательные приватные методы
    Node* copyTree(Node* otherRoot);
    void deleteTree(Node* node);
    Node* insertNode(Node* node, const T& value);
    Node* insertNode(Node* node, T&& value);
    Node* deleteNode(Node* node, const T& value);
    Node* findMin(Node* node) const;
    bool findNode(Node* node, const T& value) const;
    void preOrder(Node* node, std::ostream& os) const;
    void inOrder(Node* node, std::ostream& os) const;
    void postOrder(Node* node, std::ostream& os) const;
    void saveToFile(Node* node, std::ofstream& file) const;
    Node* loadFromFile(std::ifstream& file);

public:
    // Конструкторы и деструктор
    BSTree();
    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;
    ~BSTree();

    // Операторы присваивания
    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;

    // Основные операции
    void insert(const T& value);
    void insert(T&& value);
    void remove(const T& value);
    void clear();
    bool search(const T& value) const;

    // Обходы
    void preOrderPrint(std::ostream& os = std::cout) const;
    void inOrderPrint(std::ostream& os = std::cout) const;
    void postOrderPrint(std::ostream& os = std::cout) const;

    // Работа с файлами
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    // Проверка
    bool isEmpty() const;  // Только объявление!

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const BSTree& tree) {
        tree.inOrderPrint(os);
        return os;
    }
};

} // namespace TreeNS

#endif
