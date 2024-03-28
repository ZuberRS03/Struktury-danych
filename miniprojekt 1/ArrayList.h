#ifndef MINIPROJEKT_1_ARRAYLIST_H
#define MINIPROJEKT_1_ARRAYLIST_H

#include <iostream>

template <typename T>
class ArrayList {
private:
    int ileElementow; //licznik elementów w tablicy
    T *przedmioty; //tablica przechowująca elementy
public:
    ArrayList() : ileElementow{ 0 }, przedmioty{ nullptr } {} //konstruktor
    ~ArrayList(); //destruktor

    void dodajElement(T element); //metoda dodająca element do tablicy na końcu
    void dodajElement(T element, int index); //metoda dodająca element na podanym indeksie
    void usunElement(int index); //metoda usuwająca element z tablicy
    int rozmiar(); //metoda zwracająca ilość elementów w tablicy
    void wypisz(); //metoda wypisująca elementy tablicy
    void wyczysc(); //metoda czyszcząca tablicę
    void zmienRozmiar(int nowyRozmiar); //metoda zmieniająca rozmiar tablicy
    void wyszukajElement(T element); //metoda wyszukująca element w tablicy
    T pobierzElement(int index); //metoda zwracająca element z tablicy
};

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] przedmioty;
}

template<typename T>
void ArrayList<T>::dodajElement(T element) {
    T *nowaTablica = new T[ileElementow + 1]; //tworzymy nową tablicę o 1 większą
    for (int i = 0; i < ileElementow; i++) {  //przepisujemy elementy z tablicy przedmioty do nowej tablicy
        nowaTablica[i] = przedmioty[i];
    }
    nowaTablica[ileElementow] = element; //dodajemy nowy element na końcu tablicy
    delete[] przedmioty; //zwalniamy pamięć zajmowaną przez starą tablicę
    przedmioty = nowaTablica; //przypisujemy nową tablicę do wskaźnika przedmioty
    ileElementow++; //zwiększamy licznik elementów
}

template<typename T>
void ArrayList<T>::dodajElement(T element, int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index > ileElementow) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    T *nowaTablica = new T[ileElementow + 1];
    for (int i = 0; i < index; i++) {
        nowaTablica[i] = przedmioty[i];
    }
    nowaTablica[index] = element;
    for (int i = index; i < ileElementow; i++) {
        nowaTablica[i + 1] = przedmioty[i];
    }
    delete[] przedmioty;
    przedmioty = nowaTablica;
    ileElementow++;
}

template<typename T>
void ArrayList<T>::usunElement(int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index >= ileElementow) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    T *nowaTablica = new T[ileElementow - 1];
    for (int i = 0; i < index; i++) {
        nowaTablica[i] = przedmioty[i];
    }
    for (int i = index + 1; i < ileElementow; i++) {
        nowaTablica[i - 1] = przedmioty[i];
    }
    delete[] przedmioty;
    przedmioty = nowaTablica;
    ileElementow--;
}

template<typename T>
int ArrayList<T>::rozmiar() {
    return ileElementow;
}

template<typename T>
void ArrayList<T>::wypisz() {
    for (int i = 0; i < ileElementow; i++) {
        std::cout << przedmioty[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void ArrayList<T>::wyczysc() {
    delete[] przedmioty;
    przedmioty = nullptr;
    ileElementow = 0;
}

template<typename T>
void ArrayList<T>::zmienRozmiar(int nowyRozmiar) {
    T *nowaTablica = new T[nowyRozmiar];
    for (int i = 0; i < ileElementow; i++) {
        nowaTablica[i] = przedmioty[i];
    }
    delete[] przedmioty;
    przedmioty = nowaTablica;
}

template<typename T>
void ArrayList<T>::wyszukajElement(T element) {
    for (int i = 0; i < ileElementow; i++) {
        if (przedmioty[i] == element) {
            std::cout << "Element: " << element << " znajduje sie na pozycji " << i << std::endl;
            return;
        }
    }
    std::cout << "Element: " << element << " nie znajduje sie w tablicy" << std::endl;
}

template<typename T>
T ArrayList<T>::pobierzElement(int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index >= ileElementow) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    return przedmioty[index];
}
#endif //MINIPROJEKT_1_ARRAYLIST_H
