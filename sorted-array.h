
#ifndef SORTED_H
#define SORTED_H

#include <string>
using namespace std;

class SortedArray {
  int size;
  string *data;

public:
  SortedArray(int size);
  ~SortedArray();
  void insert(string *Array);
  void sort();
  int binarySearch(string key);
  int *getIterations(int *keys, int Size, const int pairs);
};

#endif
