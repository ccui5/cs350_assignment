#include "cache.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <vector>
#define random(x, y) (x + rand() % (y - x))
using namespace std;

void clean(Cache &ca) {
    for (int i = 0; i < ca.size; i++) {
        ca.cache[i][0] = -1;
    }
    ca.occ = 0;
}
int findMin(Cache &ca) {
    int retVal = 0, curr = 10000000;
    for (int i = 0; i < ca.size; i++) {
        if (curr > ca.cache[i][1]) {
            curr = ca.cache[i][1];
            retVal = i;
        }
    }
    return retVal;
}
bool is_cache_hit(int addr, Cache &ca) {
    for (int i = 0; i < ca.size; i++) {
        if (addr == ca.cache[i][0]) return true;
    }
    return false;
}
int cal_dist(vector<int> arr, int val, int start) {
    int retVal = 10000000, dis = 0;
    for (int i = start + 1; i < arr.size(); i++) {
        dis++;
        if (arr[i] == val) {
            retVal = dis;
            return retVal;
        }
    }
    return retVal;
}
double opt(vector<int> arr, Cache &ca) {
    double rate;
    int hit = 0, victim = 0, curr;
    for (int i = 0; i < arr.size(); i++) {
        curr = 0;
        if (is_cache_hit(arr[i], ca)) {
            hit++;
        } else {                     //cache miss
            if (ca.occ < ca.size) {  // have empty space
                ca.cache[ca.occ][0] = arr[i];
                ca.occ++;
            } else {
                for (int j = 0; j < ca.size; j++) {
                    if (curr < cal_dist(arr, ca.cache[j][0], i)) {
                        curr = cal_dist(arr, ca.cache[j][0], i);
                        victim = j;
                    }
                }
                ca.cache[victim][0] = arr[i];
            }
        }
    }
    cout << "hit: " << hit << endl;
    rate = hit / arr.size();
    return rate;
}
double LRU(vector<int> arr, Cache &ca) {
    double rate;
    int hit = 0, victim, curr = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (ca.occ < ca.size) {  // have empty space
            ca.cache[ca.occ][0] = arr[i];
            ca.cache[ca.occ][1] = i;
            ca.occ++;
        } else {
            if (is_cache_hit(arr[i], ca)) {
                hit++;
            } else {
                victim = findMin(ca);
                ca.cache[victim][0] = arr[i];
                ca.cache[victim][1] = i;
            }
        }
    }
    cout << hit << endl;
    rate = hit / arr.size();

    return rate;
}
double FIFO(vector<int> arr, Cache &ca) {
    double rate;
    int hit = 0, victim, size = arr.size();
    queue<int> q;
    for (int i = 0; i < arr.size(); i++) {
        if (q.size() < ca.size) {
            q.push(arr[i]);
        } else {
            victim = q.front();
            q.pop();
            q.push(arr[i]);
        }
        if (is_cache_hit(arr[i], ca)) {
            hit++;
        } else {                     //cache miss
            if (ca.occ < ca.size) {  // have empty space
                ca.cache[ca.occ][0] = arr[i];
                ca.occ++;
            } else {
                for (int j = 0; j < ca.size; j++) {
                    if (ca.cache[j][0] == victim) {
                        ca.cache[j][0] = arr[i];
                    }
                }
            }
        }
    }
    cout << hit << endl;
    rate = hit / arr.size();
    return rate;
}

double Rand(vector<int> arr, Cache &ca) {
    double rate;
    int hit = 0, victim = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (is_cache_hit(arr[i], ca)) {
            hit++;
        } else {
            if (ca.occ < ca.size) {  // have empty space
                ca.cache[ca.occ][0] = arr[i];
                ca.occ++;
            } else {
                victim = random(0, ca.size);
            }
        }
        ca.cache[victim][0] = arr[i];
    }
    rate = hit / arr.size();
    return rate;
}
double Clock(vector<int> arr, Cache &ca) {
    double rate;
    int hit = 0, victim = 0, size = ca.size;
    for (int i = 0; i < arr.size(); i++) {
        if (is_cache_hit(arr[i], ca)) {
            hit++;
        } else {
            ca.cache[victim][0] = arr[i];
        }
        victim++;
        if (victim == size) {
            victim -= size;
        }
    }
    rate = hit / arr.size();

    return rate;
}
