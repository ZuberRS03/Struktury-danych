#ifndef BSTTREE_H
#define BSTTREE_H

#include <iostream>
#include <stdexcept>
#include <utility>

class BSTTree {
private:
    // struktura węzła drzewa
    struct Node {
        int value; // wartość węzła
        int priority; // priorytet węzła
        Node* left; // wskaźnik na lewe dziecko
        Node* right; // wskaźnik na prawe dziecko
        Node(int v, int p) : value(v), priority(p), left(nullptr), right(nullptr) {} // konstruktor węzła
    };
    Node* root; // korzeń drzewa
    int treeSize; // rozmiar drzewa

    /*
     * @brief Metoda pomocnicza dodająca element do drzewa
     * @param node - wskaźnik na węzeł
     * @param value - wartość elementu
     * @param priority - priorytet elementu
     * @return Node* - wskaźnik na węzeł
     */
    Node* insert(Node* node, int value, int priority);

    /*
     * @brief Metoda pomocnicza usuwająca element o najwyższym priorytecie z drzewa
     * @param node - wskaźnik na węzeł
     * @return Node* - wskaźnik na węzeł
     */
    Node* extractMax(Node*& node);

    /*
     * @brief Metoda pomocnicza znajdująca element o najwyższym priorytecie w drzewie
     * @param node - wskaźnik na węzeł
     * @return Node* - wskaźnik na węzeł
     */
    Node* findMax(Node* node) const;

    /*
     * @brief Metoda pomocnicza usuwająca element z drzewa
     * @param node - wskaźnik na węzeł
     * @param value - wartość elementu
     * @return Node* - wskaźnik na węzeł
     */
    Node* remove(Node* node, int value);

    /*
     * @brief Metoda pomocnicza czyszcząca drzewo
     * @param node - wskaźnik na węzeł
     * @return void
     */
    void clear(Node* node);

    /*
     * @brief Metoda pomocnicza wypisująca elementy drzewa
     * @param node - wskaźnik na węzeł
     * @return void
     */
    void print(Node* node) const;

public:
    /*
     * @brief Konstruktor klasy BSTTree
     */
    BSTTree();

    /*
     * @brief Destruktor klasy BSTTree
     */
    ~BSTTree();

    /*
     * @brief Metoda dodająca element do drzewa
     * @param value - wartość elementu
     * @param priority - priorytet elementu
     * @return void
     */
    void insert(int value, int priority);

    /*
     * @brief Metoda usuwająca element o najwyższym priorytecie z drzewa
     * @return std::pair<int, int> - element o najwyższym priorytecie
     */
    std::pair<int, int> extractMax();

    /*
     * @brief Metoda zwracająca element o najwyższym priorytecie z drzewa
     * @return std::pair<int, int> - element o najwyższym priorytecie
     */
    std::pair<int, int> findMax() const;

    /*
     * @brief Metoda modyfikująca priorytet elementu w drzewie
     * @param value - wartość elementu, którego priorytet chcemy zmodyfikować
     * @param newPriority - nowy priorytet elementu
     * @return void
     */
    void modifyKey(int value, int newPriority);

    /*
     * @brief Metoda zwracająca rozmiar drzewa
     * @return int - rozmiar drzewa
     */
    int returnSize() const;

    /*
     * @brief Metoda czyszcząca drzewo
     * @return void
     */
    void clear();

    /*
     * @brief Metoda wypisująca elementy drzewa
     * @return void
     */
    void print() const;
};

#endif