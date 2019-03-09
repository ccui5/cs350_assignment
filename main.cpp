#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "cache.h"
using namespace std;
int main(int argv, char** argc) {
    ifstream input("input.txt");
    vector<int> arr;
    double rate;
    int a, i = 0;
    while (input >> a) {
        arr.push_back(a);
        i++;
    }
    input.close();
    ofstream output("output");
    Cache* c = new Cache(5);
    clean(*c);
    opt(arr, *c);

    clean(*c);
    FIFO(arr, *c);

    clean(*c);

    /*   for (int j = 5; j <= 100; j += 5) {
        Cache* c = new Cache(j);
        output << "the cache size is " << j << endl;
        //opt
        clean(*c);
        rate = opt(arr, *c);
        output << "opt rate: " << rate << endl;
        //LRU
        clean(*c);
        rate = LRU(arr, *c);
        output << "LRU rate: " << rate << endl;
        //FIFO
        clean(*c);
        rate = FIFO(arr, *c);
        output << "FIFO rate: " << rate << endl;
        //Rand
        clean(*c);
        rate = Rand(arr, *c);
        output << "Rand rate: " << rate << endl;
        //clock
        clean(*c);
        rate = Clock(arr, *c);
        output << "Clock rate: " << rate << endl;

        free(c);
    }
    */
}