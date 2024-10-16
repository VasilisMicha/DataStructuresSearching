
#include "unsorted-array.h"
#include <iostream>
#include <string>
using namespace std;

UnsortedArray::UnsortedArray(int size) {
  this->size = size;
  data = new string[size + 1];
  for (int i = 0; i < size; i++)
    data[i] = "";
}

UnsortedArray::~UnsortedArray(){
  delete [] data;
}

void UnsortedArray::insert(string *A) {
  for (int i = 0; i < size; i++) {
    data[i] = A[i];
  }
}

// Linear Search for Unsorted Array
int UnsortedArray::LinearSearch(string x) {
  data[size] = x;
  int i;
  for (i = 0; x != data[i]; i++); //Using only one comparison to save time
  if (i != size) {
    return i;
  }
  return -1;
}

int *UnsortedArray::getIterations(int *keys, const int Size, const int Pairs) {
  int *iterations = new int[Pairs];
  for (int i = 0; i < Pairs; i++) {
    iterations[i] = 0;
    for (int j = keys[i] + 1; j < size; j++) { //start searching after the 1st value
      if (data[keys[i]] == data[j]) {
        iterations[i]++;
      }
    }
    iterations[i]++;
  }

  return iterations;
}
