#include <iostream> //do obsługi strumieni wejścia/wyjścia
#include <fstream> //do obsługi plików
#include <chrono> //do mierzenia czasu
#include <cstdlib> //do losowania liczb
#include <vector>

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
void wypelnijKolejkeMaxHeap(MaxHeap &heap, int liczbaElementow, int maxPriority) {
    heap.clearHeap();
    for (int i = 0; i < liczbaElementow; i++) {
        heap.insert(i, losujLiczbe(1, maxPriority));
    }
}

int main() {
    srand(time(nullptr));  // Inicjalizacja generatora liczb losowych
    //podatawowe dane do badan
    const int liczbaPomiarow = 4; // Liczba pomiarów 30
    const int liczbaElementow = 5; // Max liczba elementów w stróktórze danych 100000
    const int skokIlosciDanych = 1; // Skok ilości danych 5000
    //const int maxPriority = liczbaElementow * 10;
    const int maxPriority = 10;

    //wybor kolejki
    int wybranaKolejka = menuKolejki();
  
    //Ewentualne wczytanie danych z pliku

    switch (wybranaKolejka) {
        case 1: {
            fout.open("wynikiMaxHeap.txt");
            fout << "Liczba elementow;Czas insert(e,p);Czas extract-max();Czas find-max();Czas modify-key(e,p);Czas return-size()\n";

            MaxHeap heap[liczbaPomiarow]; //Tworzenie tablicy obiektów klasy MaxHeap

            for(int startElementow = 1; startElementow < liczbaElementow; startElementow += skokIlosciDanych) {

                //pomiar czasu Insert
                double czasInsert = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, maxPriority); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed insertem: " << i << endl;
//                        heap[i].printHeap();
                    auto start = high_resolution_clock::now(); //początek pomiaru czasu
                    heap[i].insert(losujLiczbe(1, startElementow), losujLiczbe(1, maxPriority)); //dodanie losowego elementu do kolejki
                    auto stop = high_resolution_clock::now(); //koniec pomiaru czasu
//                        cout << "Kolejka po insert: " << i << endl;
//                        heap[i].printHeap();
//                        cout << "-------------------------------" << endl;
                    czasInsert += duration_cast<milliseconds>(stop - start).count(); //dodanie czasu do sumy
                }
                czasInsert /= liczbaPomiarow; //średni czas Insert

                //pomiar czasu ExtractMax
                double czasExtractMax = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, maxPriority); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed extractMax: " << i << endl;
//                        heap[i].printHeap();
                    auto start = high_resolution_clock::now();
                    heap[i].extractMax(); //usunięcie maksymalnego elementu z kolejki
                    auto stop = high_resolution_clock::now();
//                        cout << "Kolejka po extractMax: " << i << endl;
//                        heap[i].printHeap();
//                        cout << "-------------------------------" << endl;
                    czasExtractMax += duration_cast<milliseconds>(stop - start).count();
                }
                czasExtractMax /= liczbaPomiarow; //średni czas ExtractMax

                //pomiar czasu FindMax
                double czasFindMax = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, maxPriority); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed findMax: " << i << endl;
//                        heap[i].printHeap();
                    auto start = high_resolution_clock::now();
                    heap[i].findMax(); //znalezienie maksymalnego elementu w kolejce
                    auto stop = high_resolution_clock::now();
//                        cout << "Wynik dla findMax: " << i << endl;
//                        pair<int, int> maxElement = heap[i].findMax();
//                        cout << "Maksymalny element w kopcu to: " << maxElement.first << " z priorytetem: " << maxElement.second << endl;
//                        cout << "-------------------------------" << endl;
                    czasFindMax += duration_cast<milliseconds>(stop - start).count();
                }
                czasFindMax /= liczbaPomiarow; //średni czas FindMax

                //pomiar czasu ModifyKey
                double czasModifyKey = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, maxPriority); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed modifyKey: " << i << endl;
//                        heap[i].printHeap();
                    auto start = high_resolution_clock::now();
                    heap[i].modifyKey(losujLiczbe(0,startElementow - 1), losujLiczbe(1, maxPriority)); //zmiana priorytetu losowego elementu
                    auto stop = high_resolution_clock::now();
//                        cout << "Kolejka po modifyKey: " << i << endl;
//                        heap[i].printHeap();
//                        cout << "-------------------------------" << endl;
                    czasModifyKey += duration_cast<milliseconds>(stop - start).count();
                }
                czasModifyKey /= liczbaPomiarow; //średni czas ModifyKey

                //pomiar czasu ReturnSize
                double czasReturnSize = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijKolejkeMaxHeap(heap[i], startElementow, maxPriority); //wypełnienie kolejki losowymi danymi
//                        cout << "Kolejka przed returnSize: " << i << endl;
//                        heap[i].printHeap();
                    auto start = high_resolution_clock::now();
                    heap[i].returnSize(); //zwrócenie rozmiaru kolejki
                    auto stop = high_resolution_clock::now();
//                        cout << "Rozmiar kopca to: " << heap[i].returnSize() << endl;
//                        cout << "-------------------------------" << endl;
                    czasReturnSize += duration_cast<milliseconds>(stop - start).count();
                }
                czasReturnSize /= liczbaPomiarow; //średni czas ReturnSize

                fout << startElementow << ";" << czasInsert << ";" << czasExtractMax << ";" << czasFindMax << ";" << czasModifyKey << ";" << czasReturnSize << "\n";
            }

            fout.close();
            break;
        }

        case 2: {
            fout.open("wynikiBSTTree.txt");
            fout << "Liczba elementow;Czas insert(e,p);Czas extract-max();Czas find-max();Czas modify-key(e,p);Czas return-size()\n";

//            BSTTree bst;
//            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych) {
//                vector<pair<int, int>> elementsToInsert;
//                for (int i = 0; i < startElementow; i++) {
//                    elementsToInsert.push_back({i, losujLiczbe(1, maxPriority)});
//                }
//
//                auto start = high_resolution_clock::now();
//                for (auto& elem : elementsToInsert) {
//                    bst.insert(elem.first, elem.second);
//                }
//                auto stop = high_resolution_clock::now();
//                auto insertDuration = duration_cast<milliseconds>(stop - start).count();
//
//                start = high_resolution_clock::now();
//                auto maxElem = bst.extractMax();
//                stop = high_resolution_clock::now();
//                auto extractMaxDuration = duration_cast<milliseconds>(stop - start).count();
//
//                start = high_resolution_clock::now();
//                maxElem = bst.findMax();
//                stop = high_resolution_clock::now();
//                auto findMaxDuration = duration_cast<milliseconds>(stop - start).count();
//
//                int modifyValue = elementsToInsert.back().first;
//                start = high_resolution_clock::now();
//                bst.modifyKey(modifyValue, losujLiczbe(1, maxPriority));
//                stop = high_resolution_clock::now();
//                auto modifyKeyDuration = duration_cast<milliseconds>(stop - start).count();
//
//                start = high_resolution_clock::now();
//                size_t size = bst.returnSize();
//                stop = high_resolution_clock::now();
//                auto returnSizeDuration = duration_cast<milliseconds>(stop - start).count();
//
//                fout << startElementow << ";" << insertDuration << ";" << extractMaxDuration << ";" << findMaxDuration << ";" << modifyKeyDuration << ";" << returnSizeDuration << "\n";
//
//            }

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