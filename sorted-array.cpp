
#include "sorted-array.h"
#include <iostream>
#include <string>
using namespace std;


void swapstr(string &a, string &b) {
  string temp = a;
  a = b;
  b = temp;
}

void QuickSort(string arr[], int low, int high) {
  if (low < high) {
    string pivot = arr[low];
    int i = low + 1;
    int j = high;
    while (i <= j) {
      while (i <= j && arr[i] < pivot) {
        i++;
      }
      while (i <= j && arr[j] > pivot) {
        j--;
      }
      if (i <= j) {
        swapstr(arr[i], arr[j]);
        i++;
        j--;
      }
    }
    swap(arr[low], arr[j]);
    if (low < j - 1) {
      QuickSort(arr, low, j - 1);
    }
    if (j + 1 < high) {
      QuickSort(arr, j + 1, high);
    }
  }
}




SortedArray::SortedArray(int size) {
  this->size = size;
  data = new string[size];
  for (int i = 0; i < size; i++)
    data[i] = "";
}

SortedArray::~SortedArray(){
  delete[] data;
}

void SortedArray::insert(string *A) {
  for (int i = 0; i < size; i++) {
    data[i] = A[i];
  }
}

void SortedArray::sort() { QuickSort(data, 0, size-1); }


int SortedArray::binarySearch(string key) {
  int left = 0;
  int right = size - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (data[mid] == key) {
      return mid;
    } else if (data[mid] < key) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

int *SortedArray::getIterations(int *keys, int Size, const int pairs) {
  int *iterations = new int[Size];
  for (int i = 0; i < pairs; i++) {
    // Counting from right side
    int counter1 = 0;
    int index1 = keys[i] + 1;
    while (index1 < Size) {
      if (data[index1] == data[keys[i]]) {
        counter1++;
        index1++;
      } else
        break;
    }
    // Counting from left side
    int counter2 = 0;
    int index2 = keys[i] - 1;
    while (index2 >= 0) {
      if (data[index2] == data[keys[i]]) {
        counter2++;
        index2--;
      } else
        break;
    }
    iterations[i] = counter1 + counter2 + 1;
  }
  return iterations;
}
