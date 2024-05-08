#include <iostream> //do obsługi strumieni wejścia/wyjścia
#include <fstream> //do obsługi plików
#include <chrono> //do mierzenia czasu
#include <cstdlib> //do losowania liczb
#include <iomanip> //do std::fixed i std::setprecision

#include "MaxHeap.h"
#include "BSTTree.h"

using namespace std;
using namespace std::chrono;

ifstream fin;
ofstream fout;

//menu wyboru kolejki
int menuKolejki() {
    int wybor;
    cout << "----------Wybor kolejki priorytetowej----------\n";
    cout << "1. Max Heap\n";
    cout << "2. BST Tree\n";
    cout << "3. Exit\n";
    cout << "-----------------------------------------------\n";
    cout << "Wybor: ";
    cin >> wybor;
    return wybor;
}

//funkcja losująca liczbę z przedziału <min, max>
int losujLiczbe(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//funkcja wypełniająca kolejkę losowymi danymi
//funkcja do przerobienia na dane z pliku
void wypelnijKolejkeMaxHeap(MaxHeap &heap, int liczbaElementow, int listaDanych[][2]) {
    heap.clearHeap();
    for (int i = 0; i < liczbaElementow; i++) {
        heap.insert(listaDanych[i][0], listaDanych[i][1]);
    }
}

//funkcja wypełniająca kolejkę losowymi danymi
//funkcja do przerobienia na dane z pliku
void wypelnijKolejkeBST(BSTTree &bst, int liczbaElementow, int listaDanych[][2]) {
    bst.clear();
    for (int i = 0; i < liczbaElementow; i++) {
        bst.insert(listaDanych[i][0], listaDanych[i][1]);
    }
}

int main() {
    srand(time(nullptr));  // Inicjalizacja generatora liczb losowych
    //podatawowe dane do badan
    const int liczbaPomiarow = 30; // Liczba pomiarów
    const int liczbaElementow = 100000; // Max liczba elementów w stróktórze danych 100000
    const int skokIlosciDanych = 5000; // Skok ilości danych 5000
    const int maxPriority = liczbaElementow * 10;
    const int ilczbPoPrzecinku = 6;

    //wybor kolejki
    int wybranaKolejka = menuKolejki();
  
    //generowanie wszystkich liczb
    int listaDanych[liczbaElementow][2]; //tablica przechowująca wylosowane dane
    for(int i = 0; i < liczbaElementow; i++) {
        listaDanych[i][0] = i;
        listaDanych[i][1] = losujLiczbe(1, maxPriority);
    }

    switch (wybranaKolejka) {
        case 1: {
            fout.open("wynikiMaxHeap.txt"); //otwarcie pliku do zapisu
            fout << "Liczba elementow;Czas insert(e,p);Czas extract-max();Czas find-max();Czas modify-key(e,p);Czas return-size()\n"; //nagłówek pliku

            MaxHeap heap[liczbaPomiarow]; //Tworzenie tablicy obiektów klasy MaxHeap

            for(int startElementow = 1; startElementow < liczbaElementow; startElementow += skokIlosciDanych) { //pętla dla różnej ilości danych

                //pomiar czasu Insert
                double czasInsert = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) { //pętla dla różnych pomiarów
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed insertem: " << i << endl;
//                        heap[i].print();
//                        cout << heap[i].isHeapValid() << endl;
                    int wartosc = losujLiczbe(0, startElementow); //losowanie wartości
                    int priorytet = losujLiczbe(1, maxPriority); //losowanie priorytetu
                    auto start = high_resolution_clock::now(); //początek pomiaru czasu
                    heap[i].insert(wartosc, priorytet); //dodanie losowego elementu do kolejki
                    auto stop = high_resolution_clock::now(); //koniec pomiaru czasu
//                        cout << "Kolejka po insert: " << i << endl;
//                        heap[i].print();
//                        cout << heap[i].isHeapValid() << endl;
//                        cout << "-------------------------------" << endl;
                    czasInsert += duration<double, milli>(stop - start).count(); //dodanie czasu do sumy
                }
                czasInsert /= liczbaPomiarow; //średni czas Insert

                //pomiar czasu ExtractMax
                double czasExtractMax = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed extractMax: " << i << endl;
//                        heap[i].print();
                    auto start = high_resolution_clock::now();
                    heap[i].extractMax(); //usunięcie maksymalnego elementu z kolejki
                    auto stop = high_resolution_clock::now();
//                        cout << "Kolejka po extractMax: " << i << endl;
//                        heap[i].print();
//                        cout << heap[i].isHeapValid() << endl;
//                        cout << "-------------------------------" << endl;
                    czasExtractMax += duration<double, milli>(stop - start).count();
                }
                czasExtractMax /= liczbaPomiarow; //średni czas ExtractMax

                //pomiar czasu FindMax
                double czasFindMax = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed findMax: " << i << endl;
//                        heap[i].print();
                    auto start = high_resolution_clock::now();
                    heap[i].findMax(); //znalezienie maksymalnego elementu w kolejce
                    auto stop = high_resolution_clock::now();
//                        cout << "Wynik dla findMax: " << i << endl;
//                        pair<int, int> maxElement = heap[i].findMax();
//                        cout << "Maksymalny element w kopcu to: " << maxElement.first << " z priorytetem: " << maxElement.second << endl;
//                        cout << "-------------------------------" << endl;
                    czasFindMax += duration<double, milli>(stop - start).count();
                }
                czasFindMax /= liczbaPomiarow; //średni czas FindMax

                //pomiar czasu ModifyKey
                double czasModifyKey = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed modifyKey: " << i << endl;
//                        heap[i].print();
                    int wartosc = losujLiczbe(0, startElementow - 1);
                    int priorytet = losujLiczbe(1, maxPriority);
                    auto start = high_resolution_clock::now();
                    heap[i].modifyKey(wartosc, priorytet); //zmiana priorytetu losowego elementu
                    auto stop = high_resolution_clock::now();
//                        cout << "Kolejka po modifyKey: " << i << endl;
//                        heap[i].print();
//                        cout << "-------------------------------" << endl;
                    czasModifyKey += duration<double, milli>(stop - start).count();
                }
                czasModifyKey /= liczbaPomiarow; //średni czas ModifyKey

                //pomiar czasu ReturnSize
                double czasReturnSize = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed returnSize: " << i << endl;
//                        heap[i].print();
                    auto start = high_resolution_clock::now();
                    heap[i].returnSize(); //zwrócenie rozmiaru kolejki
                    auto stop = high_resolution_clock::now();
//                        cout << "Rozmiar kopca to: " << heap[i].returnSize() << endl;
//                        cout << "-------------------------------" << endl;
                    czasReturnSize += duration<double, milli>(stop - start).count();
                }
                czasReturnSize /= liczbaPomiarow; //średni czas ReturnSize

                fout << startElementow << ";" << fixed << setprecision(ilczbPoPrzecinku) << czasInsert <<
                ";" << fixed << setprecision(ilczbPoPrzecinku) << czasExtractMax <<
                ";" << fixed << setprecision(ilczbPoPrzecinku) << czasFindMax <<
                ";" << fixed << setprecision(ilczbPoPrzecinku) << czasModifyKey <<
                ";" << fixed << setprecision(ilczbPoPrzecinku) << czasReturnSize << "\n";
            }

            fout.close();
            break;
        }

        case 2: {
            fout.open("wynikiBSTTree.txt");
            fout << "Liczba elementow;Czas insert(e,p);Czas extract-max();Czas find-max();Czas modify-key(e,p);Czas return-size()\n";

            BSTTree bst[liczbaPomiarow]; //Tworzenie tablicy obiektów klasy MaxHeap

            for(int startElementow = 1; startElementow < liczbaElementow; startElementow += skokIlosciDanych) {

                //pomiar czasu Insert
                double czasInsert = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeBST(bst[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed insertem: " << i << endl;
//                        bst[i].print();
                    int wartosc = losujLiczbe(0, startElementow);
                    int priorytet = losujLiczbe(1, maxPriority);
                    auto start = high_resolution_clock::now(); //początek pomiaru czasu
                    bst[i].insert(wartosc, priorytet); //dodanie losowego elementu do kolejki
                    auto stop = high_resolution_clock::now(); //koniec pomiaru czasu
//                        cout << "Kolejka po insert: " << i << endl;
//                        bst[i].print();
//                        cout << "-------------------------------" << endl;
                    czasInsert += duration<double, milli>(stop - start).count(); //dodanie czasu do sumy
                }
                czasInsert /= liczbaPomiarow; //średni czas Insert

                //pomiar czasu FindMax
                double czasFindMax = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeBST(bst[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed findMax: " << i << endl;
//                        bst[i].print();
                    auto start = high_resolution_clock::now();
                    bst[i].findMax(); //znalezienie maksymalnego elementu w kolejce
                    auto stop = high_resolution_clock::now();
//                        cout << "Wynik dla findMax: " << i << endl;
//                        pair<int, int> maxElement = bst[i].findMax();
//                        cout << "Maksymalny element w kopcu to: " << maxElement.first << " z priorytetem: " << maxElement.second << endl;
//                        cout << "-------------------------------" << endl;
                    czasFindMax += duration<double, milli>(stop - start).count();
                }
                czasFindMax /= liczbaPomiarow; //średni czas FindMax

                //pomiar czasu ExtractMax
                double czasExtractMax = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    //wypelnijKolejkeBST(bst[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed extractMax: " << i << endl;
//                        bst[i].print();
                    auto start = high_resolution_clock::now();
                    bst[i].extractMax(); //usunięcie maksymalnego elementu z kolejki
                    auto stop = high_resolution_clock::now();
//                        cout << "Kolejka po extractMax: " << i << endl;
//                        bst[i].print();
//                        cout << "-------------------------------" << endl;
                    czasExtractMax += duration<double, milli>(stop - start).count();
                }
                czasExtractMax /= liczbaPomiarow; //średni czas ExtractMax

                //pomiar czasu ReturnSize
                double czasReturnSize = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeBST(bst[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed returnSize: " << i << endl;
//                        bst[i].print();
                    auto start = high_resolution_clock::now();
                    bst[i].returnSize(); //zwrócenie rozmiaru kolejki
                    auto stop = high_resolution_clock::now();
//                        cout << "Rozmiar kopca to: " << bst[i].returnSize() << endl;
//                        cout << "-------------------------------" << endl;
                    czasReturnSize += duration<double, milli>(stop - start).count();
                }
                czasReturnSize /= liczbaPomiarow; //średni czas ReturnSize

                //pomiar czasu ModifyKey
                double czasModifyKey = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    //wypelnijKolejkeBST(bst[i], startElementow, listaDanych); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed modifyKey: " << i << endl;
//                        bst[i].print();
                    int wartosc = losujLiczbe(0, startElementow);
                    int priorytet = losujLiczbe(1, maxPriority);
                    auto start = high_resolution_clock::now();
                    bst[i].modifyKey(wartosc, priorytet); //zmiana priorytetu losowego elementu
                    auto stop = high_resolution_clock::now();
//                        cout << "Kolejka po modifyKey: " << i << endl;
//                        bst[i].print();
//                        cout << "-------------------------------" << endl;
                    czasModifyKey += duration<double, milli>(stop - start).count();
                }
                czasModifyKey /= liczbaPomiarow; //średni czas ModifyKey

                fout << startElementow << ";" << fixed << setprecision(ilczbPoPrzecinku) << czasInsert <<
                     ";" << fixed << setprecision(ilczbPoPrzecinku) << czasExtractMax <<
                     ";" << fixed << setprecision(ilczbPoPrzecinku) << czasFindMax <<
                     ";" << fixed << setprecision(ilczbPoPrzecinku) << czasModifyKey <<
                     ";" << fixed << setprecision(ilczbPoPrzecinku) << czasReturnSize << "\n";
            }

            fout.close();
            break;
        }

        case 3:{
            cout << "Koniec programu\n";
            break;
        }
        default:{
            cout << "Niepoprawny wybor\n";
            break;
        }
    }
    return 0;
}