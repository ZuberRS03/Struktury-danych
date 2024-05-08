#include "BSTTree.h"

BSTTree::BSTTree() : root(nullptr), treeSize(0) {} // Konstruktor

BSTTree::~BSTTree() {
    clear(root); // Usuwamy wszystkie węzły
}

void BSTTree::clear(Node* node) {
    if (node) { // Jeżeli węzeł istnieje
        clear(node->left); // Usuwamy lewe poddrzewo
        clear(node->right); // Usuwamy prawe poddrzewo
        delete node; // Usuwamy węzeł
    }
}

void BSTTree::insert(int value, int priority) {
    Node* newNode = new Node(value, priority); // Tworzymy nowy węzeł
    if (!root) { // Jeżeli drzewo jest puste
        root = newNode; // Ustawiamy korzeń na nowy węzeł
        treeSize++; // Zwiększamy licznik elementów
        return; // Przerywamy działanie metody
    }

    Node* parent = nullptr; // Wskaźnik na rodzica
    Node* current = root; // Wskaźnik na obecny węzeł
    while (current) { // Dopóki obecny węzeł istnieje
        parent = current; // Ustawiamy wskaźnik na rodzica na obecny węzeł
        if (priority < current->priority) { // Jeżeli priorytet nowego węzła jest mniejszy od priorytetu obecnego węzła
            current = current->left; // Przechodzimy do lewego dziecka
        } else { // Jeżeli priorytet nowego węzła jest większy od priorytetu obecnego węzła
            current = current->right; // Przechodzimy do prawego dziecka
        }
    }

    if (priority < parent->priority) { // Jeżeli priorytet nowego węzła jest mniejszy od priorytetu rodzica
        parent->left = newNode; // Ustawiamy lewe dziecko rodzica na nowy węzeł
    } else { // Jeżeli priorytet nowego węzła jest większy od priorytetu rodzica
        parent->right = newNode; // Ustawiamy prawe dziecko rodzica na nowy węzeł
    }

    treeSize++;
}

BSTTree::Node* BSTTree::insert(Node* node, int value, int priority) {
    if (!node) return new Node(value, priority); // Jeżeli węzeł nie istnieje, tworzymy nowy węzeł
    if (priority > node->priority) { // Jeżeli priorytet nowego węzła jest większy od priorytetu obecnego węzła
        Node* newNode = new Node(value, priority); // Tworzymy nowy węzeł
        newNode->left = node;  // Ustawiamy lewe dziecko nowego węzła na obecny węzeł
        return newNode; // Zwracamy nowy węzeł
    } else if (priority < node->priority) { // Jeżeli priorytet nowego węzła jest mniejszy od priorytetu obecnego węzła
        node->left = insert(node->left, value, priority); // Dodajemy nowy węzeł do lewego poddrzewa
    } else { // Jeżeli priorytety są równe
        node->right = insert(node->right, value, priority); // Dodajemy nowy węzeł do prawego poddrzewa
    }
    return node; // Zwracamy obecny węzeł
}

std::pair<int, int> BSTTree::extractMax() {
    if (!root) throw std::runtime_error("BST is empty"); // Jeżeli drzewo jest puste, wyrzucamy wyjątek
    std::pair<int, int> max = {root->value, root->priority}; // Zapisujemy wartość i priorytet korzenia
    Node* maxNode = extractMax(root); // Usuwamy element o najwyższym priorytecie
    delete maxNode; // Usuwamy węzeł
    treeSize--; // Zmniejszamy licznik elementów
    return max; // Zwracamy wartość i priorytet elementu
}

BSTTree::Node* BSTTree::extractMax(Node*& node) {
    if (!node->right) { // Jeżeli prawe dziecko nie istnieje
        Node* temp = node; // Zapisujemy obecny węzeł
        node = node->left; // Przesuwamy wskaźnik na obecny węzeł na lewe dziecko
        return temp; // Zwracamy obecny węzeł
    }
    return extractMax(node->right); // Usuwamy element o najwyższym priorytecie z prawego poddrzewa
}

std::pair<int, int> BSTTree::findMax() const {
    Node* maxNode = findMax(root); // Znajdujemy element o najwyższym priorytecie
    if (!maxNode) throw std::runtime_error("BST is empty"); // Jeżeli drzewo jest puste, wyrzucamy wyjątek
    return {maxNode->value, maxNode->priority}; // Zwracamy wartość i priorytet elementu
}

BSTTree::Node* BSTTree::findMax(Node* node) const {
    while (node && node->right) node = node->right; // Przechodzimy do prawego dziecka
    return node; // Zwracamy węzeł
}

void BSTTree::modifyKey(int value, int newPriority) {
    root = remove(root, value); // Usuwamy element o wartości value
    insert(value, newPriority); // Dodajemy element o wartości value i priorytecie newPriority
}

BSTTree::Node* BSTTree::remove(Node* root, int value) {
    Node* parent = nullptr; // Wskaźnik na rodzica
    Node* current = root; // Wskaźnik na obecny węzeł
    while (current && current->value != value) { // Dopóki obecny węzeł istnieje i wartość obecnego węzła jest różna od value
        parent = current; // Ustawiamy wskaźnik na rodzica na obecny węzeł
        if (value < current->value) { // Jeżeli value jest mniejsze od wartości obecnego węzła
            current = current->left; // Przechodzimy do lewego dziecka
        } else { // Jeżeli value jest większe od wartości obecnego węzła
            current = current->right; // Przechodzimy do prawego dziecka
        }
    }

    if (!current) return root; // Nie znaleziono wartości

    // Przypadek 1: Usuwany węzeł nie ma potomków (węzeł liści)
    if (!current->left && !current->right) {
        if (current != root) { // Jeżeli usunięty węzeł nie jest korzeniem
            if (parent->left == current) { // Jeżeli usunięty węzeł jest lewym dzieckiem
                parent->left = nullptr; // Ustawiamy lewe dziecko rodzica na nullptr
            } else {  // Jeżeli usunięty węzeł jest prawym dzieckiem
                parent->right = nullptr; // Ustawiamy prawe dziecko rodzica na nullptr
            }
        } else { // Jeżeli usunięty węzeł jest korzeniem
            root = nullptr; // Ustawiamy korzeń na nullptr
        }
        delete current; // Usuwamy węzeł
        treeSize--; // Zmniejszamy licznik elementów
    }
    // Przypadek 2: Usuwany węzeł ma dwa potomki
    else if (current->left && current->right) {
        Node* successor = current->right; // Węzeł następnik
        Node* successorParent = current; // Rodzic następnika

        while (successor->left) { // Dopóki lewe dziecko następnika istnieje
            successorParent = successor; // Ustawiamy rodzica następnika na następnika
            successor = successor->left; // Przechodzimy do lewego dziecka następnika
        }

        current->value = successor->value; // Ustawiamy wartość usuniętego węzła na wartość następnika
        current->priority = successor->priority; // Ustawiamy priorytet usuniętego węzła na priorytet następnika

        if (successorParent != current) { // Jeżeli rodzic następnika nie jest równy usuniętemu węzłowi
            successorParent->left = successor->right; // Ustawiamy lewe dziecko rodzica następnika na prawe dziecko następnika
        } else {
            successorParent->right = successor->right; // Ustawiamy prawe dziecko rodzica następnika na prawe dziecko następnika
        }

        delete successor; // Usuwamy następnika
        treeSize--; // Zmniejszamy licznik elementów
    }
    // Przypadek 3: Usuwany węzeł ma jednego potomka
    else {
        Node* child = (current->left) ? current->left : current->right; // Ustawiamy dziecko na lewe dziecko, jeżeli istnieje, w przeciwnym wypadku na prawe dziecko

        if (current != root) { // Jeżeli usunięty węzeł nie jest korzeniem
            if (current == parent->left) { // Jeżeli usunięty węzeł jest lewym dzieckiem
                parent->left = child; // Ustawiamy lewe dziecko rodzica na dziecko
            } else { // Jeżeli usunięty węzeł jest prawym dzieckiem
                parent->right = child; // Ustawiamy prawe dziecko rodzica na dziecko
            }
        } else { // Jeżeli usunięty węzeł jest korzeniem
            root = child; // Ustawiamy korzeń na dziecko
        }

        delete current; // Usuwamy węzeł
        treeSize--; // Zmniejszamy licznik elementów
    }

    return root; // Zwracamy korzeń
}

int BSTTree::returnSize() const {
    return treeSize; // Zwracamy licznik elementów
}

void BSTTree::clear() {
    clear(root); // Usuwamy wszystkie węzły
    root = nullptr; // Ustawiamy korzeń na nullptr
    treeSize = 0;  // Zerujemy licznik elementów
}

void BSTTree::print() const {
    print(root); // Wypisujemy elementy drzewa
    std::cout << std::endl; // Wypisujemy nową linię
}

void BSTTree::print(Node* node) const {
    if (node) { // Jeżeli węzeł istnieje
        print(node->left); // Wypisujemy lewe poddrzewo
        std::cout << node->value << " " << node->priority << std::endl; // Wypisujemy wartość i priorytet węzła
        print(node->right); // Wypisujemy prawe poddrzewo
    }
}