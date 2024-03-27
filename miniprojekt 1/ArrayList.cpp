#include "ArrayList.h"

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] przedmioty;
}

template<typename T>
void ArrayList<T>::dodajElement(T element) {
    T *nowaTablica = new T[ileElementow + 1];
    for (int i = 0; i < ileElementow; i++) {
        nowaTablica[i] = przedmioty[i];
    }
    nowaTablica[ileElementow] = element;
    delete[] przedmioty;
    przedmioty = nowaTablica;
    ileElementow++;
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
            std::cout << "Element " << element << " znajduje się na pozycji " << i << std::endl;
            return;
        }
    }
    std::cout << "Element " << element << " nie znajduje się w tablicy" << std::endl;
}

template<typename T>
T ArrayList<T>::pobierzElement(int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index >= ileElementow) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    return przedmioty[index];
}