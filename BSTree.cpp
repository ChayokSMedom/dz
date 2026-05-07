#include "BSTree.hpp"
#include <sstream>
#include <stdexcept>

namespace TreeNS {

// ==================== Конструкторы узла ====================

template <typename T>
BSTree<T>::Node::Node(const T& value) : data(value), left(nullptr), right(nullptr) {}

template <typename T>
BSTree<T>::Node::Node(T&& value) : data(std::move(value)), left(nullptr), right(nullptr) {}

// ==================== Конструкторы и деструктор дерева ====================

template <typename T>
BSTree<T>::BSTree() : root(nullptr) {}

template <typename T>
BSTree<T>::BSTree(const BSTree& other) : root(nullptr) {
    root = copyTree(other.root);
}

template <typename T>
BSTree<T>::BSTree(BSTree&& other) noexcept : root(other.root) {
    other.root = nullptr;
}

template <typename T>
BSTree<T>::~BSTree() {
    deleteTree(root);
}

// ==================== Операторы присваивания ====================

template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& other) {
    if (this != &other) {
        deleteTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(BSTree&& other) noexcept {
    if (this != &other) {
        deleteTree(root);
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

// ==================== Вспомогательные методы ====================

template <typename T>
typename BSTree<T>::Node* BSTree<T>::copyTree(Node* otherRoot) {
    if (!otherRoot) return nullptr;
    Node* newNode = new Node(otherRoot->data);
    newNode->left = copyTree(otherRoot->left);
    newNode->right = copyTree(otherRoot->right);
    return newNode;
}

template <typename T>
void BSTree<T>::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::findMin(Node* node) const {
    while (node && node->left) node = node->left;
    return node;
}

// ==================== Добавление узла ====================

template <typename T>
void BSTree<T>::insert(const T& value) {
    root = insertNode(root, value);
}

template <typename T>
void BSTree<T>::insert(T&& value) {
    root = insertNode(root, std::move(value));
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::insertNode(Node* node, const T& value) {
    if (!node) return new Node(value);
    if (value < node->data)
        node->left = insertNode(node->left, value);
    else if (value > node->data)
        node->right = insertNode(node->right, value);
    return node;
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::insertNode(Node* node, T&& value) {
    if (!node) return new Node(std::move(value));
    if (value < node->data)
        node->left = insertNode(node->left, std::move(value));
    else if (value > node->data)
        node->right = insertNode(node->right, std::move(value));
    return node;
}

// ==================== Удаление узла ====================

template <typename T>
void BSTree<T>::remove(const T& value) {
    root = deleteNode(root, value);
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::deleteNode(Node* node, const T& value) {
    if (!node) return nullptr;

    if (value < node->data)
        node->left = deleteNode(node->left, value);
    else if (value > node->data)
        node->right = deleteNode(node->right, value);
    else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* minNode = findMin(node->right);
        node->data = minNode->data;
        node->right = deleteNode(node->right, minNode->data);
    }
    return node;
}

// ==================== Удаление дерева ====================

template <typename T>
void BSTree<T>::clear() {
    deleteTree(root);
    root = nullptr;
}

// ==================== Поиск ====================

template <typename T>
bool BSTree<T>::search(const T& value) const {
    return findNode(root, value);
}

template <typename T>
bool BSTree<T>::findNode(Node* node, const T& value) const {
    if (!node) return false;
    if (value == node->data) return true;
    if (value < node->data) return findNode(node->left, value);
    return findNode(node->right, value);
}

// ==================== Обходы ====================

template <typename T>
void BSTree<T>::preOrderPrint(std::ostream& os) const {
    preOrder(root, os);
}

template <typename T>
void BSTree<T>::preOrder(Node* node, std::ostream& os) const {
    if (node) {
        os << node->data << " ";
        preOrder(node->left, os);
        preOrder(node->right, os);
    }
}

template <typename T>
void BSTree<T>::inOrderPrint(std::ostream& os) const {
    inOrder(root, os);
}

template <typename T>
void BSTree<T>::inOrder(Node* node, std::ostream& os) const {
    if (node) {
        inOrder(node->left, os);
        os << node->data << " ";
        inOrder(node->right, os);
    }
}

template <typename T>
void BSTree<T>::postOrderPrint(std::ostream& os) const {
    postOrder(root, os);
}

template <typename T>
void BSTree<T>::postOrder(Node* node, std::ostream& os) const {
    if (node) {
        postOrder(node->left, os);
        postOrder(node->right, os);
        os << node->data << " ";
    }
}

// ==================== Работа с файлами ====================

template <typename T>
void BSTree<T>::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for writing: " + filename);
    saveToFile(root, file);
    file.close();
}

template <typename T>
void BSTree<T>::saveToFile(Node* node, std::ofstream& file) const {
    if (!node) {
        file << "# ";
        return;
    }
    file << node->data << " ";
    saveToFile(node->left, file);
    saveToFile(node->right, file);
}

template <typename T>
void BSTree<T>::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for reading: " + filename);
    clear();
    root = loadFromFile(file);
    file.close();
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::loadFromFile(std::ifstream& file) {
    std::string token;
    file >> token;
    if (token == "#") return nullptr;

    T value;
    std::istringstream iss(token);
    iss >> value;
    Node* node = new Node(value);
    node->left = loadFromFile(file);
    node->right = loadFromFile(file);
    return node;
}

// ==================== Проверка на пустоту (определение) ====================

template <typename T>
bool BSTree<T>::isEmpty() const {
    return root == nullptr;
}

// ==================== Явная инстанциация ====================
template class BSTree<int>;
template class BSTree<double>;
template class BSTree<std::string>;

} // namespace TreeNS
