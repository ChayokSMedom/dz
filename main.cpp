#include "BSTree.hpp"
#include <iostream>

using namespace TreeNS;

int main() {

    BSTree<int> tree;

    std::cout << "1. Adding: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    std::cout << "\n2. Pre-order: ";
    tree.preOrderPrint();

    std::cout << "\n3. In-order: ";
    tree.inOrderPrint();

    std::cout << "\n4. Post-order: ";
    tree.postOrderPrint();

    std::cout << "\n\n5. Operator<<: " << tree << std::endl;

    std::cout << "\n6. Search 40: " << (tree.search(40) ? "found" : "not found") << std::endl;
    std::cout << "   Search 100: " << (tree.search(100) ? "found" : "not found") << std::endl;

    std::cout << "\n7. Removing 30..." << std::endl;
    tree.remove(30);
    std::cout << "   Tree: " << tree << std::endl;

    std::cout << "\n8. Copy constructor" << std::endl;
    BSTree<int> tree2 = tree;
    std::cout << "   tree2: " << tree2 << std::endl;

    std::cout << "\n9. Move constructor" << std::endl;
    BSTree<int> tree3 = std::move(tree2);
    std::cout << "   tree3: " << tree3 << std::endl;
    std::cout << "   tree2 empty: " << tree2.isEmpty() << std::endl;

    std::cout << "\n10. Save to file" << std::endl;
    tree3.saveToFile("tree.txt");
    std::cout << "    Saved to 'tree.txt'" << std::endl;

    std::cout << "\n11. Load from file" << std::endl;
    BSTree<int> tree4;
    tree4.loadFromFile("tree.txt");
    std::cout << "    Loaded: " << tree4 << std::endl;

    std::cout << "\n12. Clear tree" << std::endl;
    tree3.clear();
    std::cout << "    tree3 empty: " << tree3.isEmpty() << std::endl;

    std::cout << std::endl;

    return 0;
}
