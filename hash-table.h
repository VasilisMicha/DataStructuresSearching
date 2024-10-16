
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>

using namespace std;

class HashTable {
private:
  size_t customHash(string str);
  size_t doubleHash(string str, size_t probeCount);

  size_t tableSize;
  string *table;
  size_t *countArray;

public:
  explicit HashTable(size_t tableSize);
  ~HashTable();

  void insert(string value);
  int search(string value);
  size_t count(int index);

};

#endif // HASH_TABLE_H
