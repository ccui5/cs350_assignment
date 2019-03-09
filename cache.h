#ifndef CACHE
#define CACHE
#include <vector>
using namespace std;
/*cache will be in 
    [val][tag][h/m]
    [val][tag][h/m]
    ...
    */
class Cache {
   public:
    int **cache;
    int size;
    vector<int> cacheT;  //this will save the cache hot and cold information
    int occ;
    Cache(int size) {
        this->size = size;
        cache = new int *[size];
        for (int i = 0; i < size; i++) {
            cache[i] = new int[3];
        }
        occ = 0;
    }
};
double opt(vector<int> arr, Cache &ca);
double Clock(vector<int> arr, Cache &ca);
double Rand(vector<int> arr, Cache &ca);
double FIFO(vector<int> arr, Cache &ca);
double LRU(vector<int> arr, Cache &ca);
void clean(Cache &ca);

#endif