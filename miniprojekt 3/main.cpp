#include <iostream> //podstawowa biblioteka wejścia/wyjścia
#include <fstream> //do wczytywania i zapisywania plików
#include <chrono> //do pomiaru czasu
#include <cstdlib> //do losowania liczb

#include "OpenAddressingHashTable.h"
#include "ChainedHashTable.h"
#include "CuckooHashTable.h"

using namespace std;

ifstream fin;
ofstream fout;

int losujLiczbe(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {


    return 0;
}
