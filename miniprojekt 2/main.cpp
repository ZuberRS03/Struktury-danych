#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <vector>

#include "MaxHeap.h"
#include "BSTTree.h"

using namespace std;
using namespace std::chrono;

ifstream fin;
ofstream fout;

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

int losujLiczbe(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    srand(time(nullptr));  // Inicjalizacja generatora liczb losowych
    const int liczbaPomiarow = 30;
    const int liczbaElementow = 100000;
    const int skokIlosciDanych = 5000;
    const int maxPriority = liczbaElementow * 10;

    int wybranaKolejka = menuKolejki();

    switch (wybranaKolejka) {
        case 1: {
            fout.open("wynikiMaxHeap.txt");
            fout << "Liczba elementow;Czas insert(e,p);Czas extract-max();Czas find-max();Czas modify-key(e,p);Czas return-size()\n";

            MaxHeap heap;
            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych) {
                vector<pair<int, int>> elementsToInsert;
                for (int i = 0; i < startElementow; i++) {
                    elementsToInsert.push_back({i, losujLiczbe(1, maxPriority)});
                }

                auto start = high_resolution_clock::now();
                for (auto& elem : elementsToInsert) {
                    heap.insert(elem.first, elem.second);
                }
                auto stop = high_resolution_clock::now();
                auto insertDuration = duration_cast<milliseconds>(stop - start).count();

                start = high_resolution_clock::now();
                auto maxElem = heap.extractMax();
                stop = high_resolution_clock::now();
                auto extractMaxDuration = duration_cast<milliseconds>(stop - start).count();

                start = high_resolution_clock::now();
                maxElem = heap.findMax();
                stop = high_resolution_clock::now();
                auto findMaxDuration = duration_cast<milliseconds>(stop - start).count();

                int modifyValue = elementsToInsert.back().first;
                start = high_resolution_clock::now();
                heap.modifyKey(modifyValue, losujLiczbe(1, maxPriority));
                stop = high_resolution_clock::now();
                auto modifyKeyDuration = duration_cast<milliseconds>(stop - start).count();

                start = high_resolution_clock::now();
                size_t size = heap.returnSize();
                stop = high_resolution_clock::now();
                auto returnSizeDuration = duration_cast<milliseconds>(stop - start).count();

                fout << startElementow << ";" << insertDuration << ";" << extractMaxDuration << ";" << findMaxDuration << ";" << modifyKeyDuration << ";" << returnSizeDuration << "\n";
            }

            fout.close();
            break;
        }
        case 2: {
            fout.open("wynikiBSTTree.txt");
            fout << "Liczba elementow;Czas insert(e,p);Czas extract-max();Czas find-max();Czas modify-key(e,p);Czas return-size()\n";

            BSTTree bst;
            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych) {
                vector<pair<int, int>> elementsToInsert;
                for (int i = 0; i < startElementow; i++) {
                    elementsToInsert.push_back({i, losujLiczbe(1, maxPriority)});
                }

                auto start = high_resolution_clock::now();
                for (auto& elem : elementsToInsert) {
                    bst.insert(elem.first, elem.second);
                }
                auto stop = high_resolution_clock::now();
                auto insertDuration = duration_cast<milliseconds>(stop - start).count();

                start = high_resolution_clock::now();
                auto maxElem = bst.extractMax();
                stop = high_resolution_clock::now();
                auto extractMaxDuration = duration_cast<milliseconds>(stop - start).count();

                start = high_resolution_clock::now();
                maxElem = bst.findMax();
                stop = high_resolution_clock::now();
                auto findMaxDuration = duration_cast<milliseconds>(stop - start).count();

                int modifyValue = elementsToInsert.back().first;
                start = high_resolution_clock::now();
                bst.modifyKey(modifyValue, losujLiczbe(1, maxPriority));
                stop = high_resolution_clock::now();
                auto modifyKeyDuration = duration_cast<milliseconds>(stop - start).count();

                start = high_resolution_clock::now();
                size_t size = bst.returnSize();
                stop = high_resolution_clock::now();
                auto returnSizeDuration = duration_cast<milliseconds>(stop - start).count();

                fout << startElementow << ";" << insertDuration << ";" << extractMaxDuration << ";" << findMaxDuration << ";" << modifyKeyDuration << ";" << returnSizeDuration << "\n";
            }

            fout.close();
            break;
        }
        case 3: {
            cout << "Koniec programu\n";
            break;
        }
        default: {
            cout << "Niepoprawny wybor\n";
            break;
        }
    }

    return 0;
}