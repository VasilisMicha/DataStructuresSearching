
#include "hash-table.h"

using namespace std;

HashTable::HashTable(size_t tableSize) {
  this->tableSize = tableSize;
  table= new string[tableSize];
  countArray = new size_t[tableSize];
  //initializing table and countArray
  for (size_t i = 0; i < tableSize; i++) {
    table[i] = "";
    countArray[i] = 0;
  }
}

HashTable::~HashTable() {
  delete[] table;
  delete[] countArray;
}

void HashTable::insert(string value) {
  size_t index = customHash(value) % tableSize;
  size_t probeCount = 1;
  // Handling collisions using double hashing
  while (!table[index].empty()) {
    if (table[index] == value) {
      countArray[index]++;
      return;
    }
    //Updating index
    index = (index + doubleHash(value, probeCount)) % tableSize;
    probeCount++;
  }

  table[index] = value;
  countArray[index] = 1;
}

int HashTable::search(string value) {
  size_t index = customHash(value) % tableSize;
  size_t probeCount = 1;

  while (!table[index].empty()) {
    if (table[index] == value)
      return index;

    index = (index + doubleHash(value, probeCount)) % tableSize;
    probeCount++;
  }

  return -1;
}

size_t HashTable::count(int index) {
  return countArray[index];
}

size_t HashTable::customHash(string str){
  size_t hash = 0;
  // Iterate through each character in the string and calculate the hash value
  for (char c : str) {
    hash = hash * 31 + static_cast<unsigned char>(c);
  }

  return hash;
}
// Function to perform double hashing
size_t HashTable::doubleHash(string str, size_t probeCount){
  size_t h1 = customHash(str) % tableSize;
  size_t h2 = 1 + (customHash(str) % (tableSize - 1));

  return (h1 + probeCount * h2) % tableSize;
}
