
#ifndef UNSORTED_H
#define UNSORTED_H

#include <string>
using namespace std;


class UnsortedArray {
  int size;
  string* data;
public:
  UnsortedArray(int size);
  ~UnsortedArray();
  void insert(string* Array);
  int LinearSearch(string x);
  int* getIterations(int* keys, const int Size, const int Pairs);
};

#endif
