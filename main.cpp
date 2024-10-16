#include "hash-table.h"
#include "binary-search-tree.h"
#include "bst-AVL.h"
#include "sorted-array.h"
#include "unsorted-array.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  string file;
  ifstream f1("small-file.txt"); //opening file 
  if (!f1.is_open()) { //checking if the file exists
    cerr << "Couldn't open file" << endl;
    return 1;
  } else {
    const int sizeGap = 1000000;  // memory allocation size
    size_t memoryAllocation = sizeGap;
    size_t size = 0;
    string consecutiveChars;
    string alphabetChars;
    string *words = new string[memoryAllocation];

    // Creating an array with the words of the text
    while (f1 >> consecutiveChars) {  //reading every word from the file until there is none left
      for (char c : consecutiveChars) {
        if (isalpha(c)) // Selecting only alphabet chars
          alphabetChars += c;
      }
      if (!alphabetChars.empty()) {  // ignore the empty string
        if (size == memoryAllocation) { // memory allocation after every sizeGap iterations
          memoryAllocation += sizeGap;
          string *newWords = new string[memoryAllocation]; 
          //you can't just realloc with new you need to delete the array and create it with more size
          for (int i = 0; i < size; i++) {
            newWords[i] = words[i];
          }
          delete[] words;
          words = newWords;
        }
        words[size++] = alphabetChars;
      }
      alphabetChars.clear();
    }
    
    string *pairsOfWords = new string[--size]; //decreasing by one the size bc the last word doesn't have 2 pairs
    for (int i = 0; i < size; i++) {
      pairsOfWords[i] = words[i] + " " + words[i + 1];
    }
    delete[] words;

    // Converting every string to lower case
    string lowerCase;
    for (int i = 0; i < size; i++) {
      lowerCase = "";
      for (char c : pairsOfWords[i]) {
        lowerCase += tolower(c);
      }
      pairsOfWords[i] = lowerCase;
    }
    f1.close();

    ofstream f2("output.txt");


    //Unsorted Array
    clock_t startTime = clock();

    UnsortedArray array1 = UnsortedArray(size);
    array1.insert(pairsOfWords);

    clock_t endTime = clock();
    f2 << "Unsorted Array implementation time:"
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl
       << endl;


    // Sorted Array
    startTime = clock();

    SortedArray array2 = SortedArray(size);
    array2.insert(pairsOfWords);
    array2.sort();

    endTime = clock();
    f2 << "Sorted Array implementation time:"
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl
       << endl;

    // Binary Search Tree
    startTime = clock();
    
    BinarySearchTree tree = BinarySearchTree();
    for (int i = 0; i < size; i++) {
      tree.insert(pairsOfWords[i]);
    }
    
    endTime = clock();
    f2 << "Binary Search Tree implementation time:"
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl
       << endl;

    // Binary Search Tree AVL
    startTime = clock();
    
    BST_AVL treeAvl = BST_AVL();
    for (int i = 0; i < size; i++) {
      treeAvl.insert(pairsOfWords[i]);
    }
    
    endTime = clock();
    f2 << "Binary Search Tree AVL implementation time:"
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl
       << endl;


    //Hash Table
    startTime = clock();
    
    size_t tableSize = size/0.7;
    HashTable hash(tableSize);
    for (int i=0;i<size;i++){
      hash.insert(pairsOfWords[i]);
    }
    
    endTime = clock();
    f2 << "Hash Table implementation time:"
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl
       << endl;



    // Picking randomly 1000 pairs of words
    const int pairsToSearch = 1000;
    string *Q = new string[pairsToSearch];
    srand(time(NULL));
    for (int i = 0; i < pairsToSearch; i++) {
      Q[i] = pairsOfWords[rand() % size];
    }


    //Searching in Unsorted Array
    startTime = clock();

    int* searchedPos1 = new int[pairsToSearch];
    for (int i=0;i<pairsToSearch;i++){
      searchedPos1[i] = array1.LinearSearch(Q[i]);
    }
    
    endTime = clock();
    f2 << "Unsorted Array search time: "
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;
    
    int* iterationsUnsorted = new int[pairsToSearch];
    iterationsUnsorted = array1.getIterations(searchedPos1, size, pairsToSearch);
    
    f2 << "Iterations in Unsorted Array: ";
    for (int i = 0; i < pairsToSearch-1; i++)
      f2 << i + 1 << ")" <<Q[i]<<"("<<iterationsUnsorted[i]<<")" << ", ";
    f2 << 1000 << ")" <<Q[999]<<"("<<iterationsUnsorted[999]<<")" <<endl<<endl;
    delete[] iterationsUnsorted;


    // Searching in Sorted Array
    startTime = clock();

    int *searchedPos2 = new int[pairsToSearch];
    for (int i = 0; i < pairsToSearch; i++) {
      searchedPos2[i] = array2.binarySearch(Q[i]);
    }
    
    endTime = clock();
    f2 << "Sorted Array search time: "
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;

    int *iterationsSorted = new int[pairsToSearch];
    iterationsSorted = array2.getIterations(searchedPos2, size, pairsToSearch);
    
    f2 << "Iterations in Sorted Array: ";
    for (int i = 0; i < pairsToSearch; i++)
      f2 << i + 1 << ")" <<Q[i]<<"(" <<iterationsSorted[i]<<")" << ", ";
    f2 << 1000 << ")" <<Q[999]<<"("<<iterationsSorted[999]<<")" <<endl<<endl;
    delete[] iterationsSorted;

    // Searching in Binary Search Tree
    startTime = clock();
    
    Node **nodes = new Node *[pairsToSearch];
    for (int i = 0; i < pairsToSearch; i++) {
      nodes[i] = tree.search(Q[i]);
    }
    
    endTime = clock();
    
    f2 << "Binary Search Tree search time: "
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;

    f2 << "Iterations in Binary Search Tree: ";
    for (int i = 0; i < pairsToSearch; i++) {
      f2 << i + 1 << ")" <<Q[i]<<"("<< tree.getCount(nodes[i])<<")" << ", ";
    }
    f2 << 1000 << ")" <<Q[999]<<"("<<tree.getCount(nodes[999])<<")" <<endl<<endl;


    // Searching in Binary Search Tree AVL
    startTime = clock();

    NodeAvl **nodesAvl = new NodeAvl *[pairsToSearch];
    for (int i = 0; i < pairsToSearch; i++) {
      nodesAvl[i] = treeAvl.search(Q[i]);
    }
    
    endTime = clock();
    f2 << "Binary Search Tree AVL search time: "
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;

    f2 << "Iterations in Binary Search Tree AVL: ";
    for (int i = 0; i < pairsToSearch; i++) {
      f2 << i + 1 << ")" <<Q[i]<<"("<< treeAvl.getCount(nodesAvl[i]) <<")"<< ", ";
    }
    f2 << 1000 << ")" <<Q[999]<<"("<<treeAvl.getCount(nodesAvl[999])<<")" <<endl<<endl;

      
    //Searching in Hash Table
    startTime = clock();

    int* hashPos = new int[pairsToSearch];
    for (int i=0;i<pairsToSearch;i++){
      hashPos[i] = hash.search(Q[i]);
    }
    
    endTime = clock();
    f2 << "Hash Table search time: "
       << double(endTime - startTime) / CLOCKS_PER_SEC << "seconds" << endl;
    
   f2 << "Iterations in Hash Table: ";
    for (int i = 0; i < pairsToSearch; i++) {
      f2 << i + 1 << ")" <<Q[i]<<"("<<hash.count(hashPos[i])<<")" << ", ";
    }
    f2 << 1000 << ")" <<Q[999]<<"("<<hash.count(hashPos[999])<<")" <<endl<<endl;

    f2.close();



    delete[] pairsOfWords;
    delete[] Q;
    delete[] searchedPos1;
    delete [] searchedPos2;
    delete[] nodes;
  }
}
