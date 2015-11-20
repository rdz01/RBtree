#include "RedBlackTree.h"
#include "RedBlackTree.cpp"

#include <string>
#include <iostream>
#include <iomanip>// - for setw>
#include <fstream>
#include <cstdlib>
#include <stdexcept>


using RBTree::RedBlackTree;
using namespace std;

void insertTest();
void searchTest();
void loadTest();
 
void part1();
void part1insert();
void part1load();
void part1search();
void part1remove();
void part1copy();
 
void part2();

//void part1insert();
//void part1remove();//delete fixup need to be fix
//void part1copy();
//void part1search();
////void part1load();
//void part2();

template <class T>
T* readFile(string infile, int & n);
template <class T>
void statsPrint(const RedBlackTree<T> & rb, int n, int bh, int h, bool rc);
template <class T>
void dumpPrint(const RedBlackTree<T> & rb, string result, int space);

int main(){

	
	/*part1insert();
	part1remove();
	part1copy();
	part1search();
	part2();
*/
	part1();
	part2();

	int x;
	cin>>x;
	return 0;
	
}

// RedBlackTree<int> tests
void part1()
{
  part1insert();
  cout << endl << endl;
  part1load();
  cout << endl << endl;
  part1search();
  cout << endl << endl;
  part1remove();
  cout << endl << endl;
  part1copy();
}

// Tests insert
void part1insert()
{
  cout << "INSERT TEST";
  RedBlackTree<int> rb;
  rb.insert(50); //root
  rb.insert(60); // OK
  cout << endl << "insert succeeds: " << rb.insert(70) << " [1]" << endl; // pRt, nRt, uB - 6
  rb.insert(80); // pRt, uRd - 1
  rb.insert(75); // pRt, nL, uB - 5
  rb.insert(40); // OK
  rb.insert(55); // OK
  rb.insert(30); // pL, uRd - 1
  rb.insert(45); // OK
  rb.insert(42); // pRt, uRd, ggpRd - 4, pL, nL, uB - 3
  rb.insert(43); // pL, nRt, uB - 2
  cout << "insert duplicate: " << rb.insert(40) << " [0]"; //duplicate
  cout << endl << "insert tests passed without failure";
  statsPrint(rb, 11, 2, 4, true);
  cout << endl << endl << "search test";
  cout << endl << "search 10 = " << rb.search(10) << " [0]";
  cout << endl << "search 80 = " << rb.search(80) << " [1]";
  cout << endl << "search 43 = " << rb.search(43) << " [1]";  
  cout <<endl;
}

// Tests load (and dump)
void part1load()
{
  cout << "LOAD TEST";
  int arr[] = {34,21,76,19,98,42,33,11,83,91,27,72,85,63};
  int n = 14;
  RedBlackTree<int> rb;
  rb.load(arr, n);
  cout << endl << "load test passed without failure";
  statsPrint(rb, 14, 3, 5, true);
 
  dumpPrint<int>(rb, "*11 19 21 27 33 34 42 63 72 76 83 85 91 98", 3);
}

// Tests range search
void part1search()
{
  cout << "SEARCH TEST";
  int arr[] = {99,92,85,78,71,64,57,50,43,36,29,22,15};
  int n = 13;
  RedBlackTree<int> rb;
  rb.load(arr, n);
  cout << endl << "load test passed without failure";
  statsPrint(rb, 13, 3, 5, true);
 
  cout << endl << endl << "search (low, high) tests" << endl;
  int* out = rb.search(11, 99, n);
  for(int i=0; i < n; i++){
         cout << setw(3) << out[i];
  }
  cout << endl << "*15 22 29 36 43 50 57 64 71 78 85 92 99" << endl;
  delete[] out;
 
  out = rb.search(51, 56, n);
  for(int i=0; i < n; i++){
         cout << setw(3) << out[i];
  }
  cout << endl << "*should be blank line above" << endl;
  delete[] out;
 
  out = rb.search(21, 62, n);
  for(int i=0; i < n; i++){
         cout << setw(3) << out[i];
  }
  cout << endl << "*22 29 36 43 50 57" << endl;
  delete[] out;
 
      out = rb.search(76, 81, n);
  for(int i=0; i < n; i++){
         cout << setw(3) << out[i];
  }
  cout << endl << "*78";
  delete[] out;
}


void part1remove()
{

  cout << "REMOVE TEST";
  int arr[] = {99,92,85,78,71,64,57,50,43,36,29,22,15};
  int n = 13;
  RedBlackTree<int> rb;
  rb.load(arr, n);
 
  rb.remove(99); // R - case 4
  cout << endl << "remove succeeds: " << rb.remove(92) << " [1]"; // case 9
  cout << endl << "remove fails: " << rb.remove(110) << " [0]";
  rb.remove(85); // R - case 1
  rb.remove(64); // no fix
  rb.remove(71); // R - case 2
  rb.remove(43); // R - case 4
  rb.remove(15); // L - case 3,4
  rb.remove(22); // L - case 1
  statsPrint(rb, 5, 2, 3, true);
 
  int arr2[] = {99,92,85,78,71,64,57,50,43,36,29,22,15,87};
  n = 14;
  rb.load(arr2, n);
  cout << endl << endl << "load second array";
  rb.remove(57); // L - case 2
  rb.remove(99); // R - case 3
  statsPrint(rb, 12, 3, 5, true);
  cout << endl << "remove tests passed without failure";
}

// Tests copy constructor and operator=
void part1copy()
{
  cout << endl << "COPY TEST";
  RedBlackTree<int> rb1;
  rb1.insert(22);
  rb1.insert(16);
  rb1.insert(38);
  rb1.insert(19);
  rb1.insert(57);
  rb1.insert(29);
  cout << endl << "insert into rb1";
  statsPrint(rb1, 6, 2, 3, true);
  dumpPrint<int>(rb1, "*16 19 22 29 38 57", 3);

  RedBlackTree<int> rb2(rb1);
  rb1.remove(16);
  rb1.remove(22);
  cout << endl << endl << "remove 16 and 22 from rb1";
  statsPrint(rb1, 4, 2, 3, true);
  dumpPrint<int>(rb1, "*19 29 38 57 (rb1)", 3);
  cout << endl;
  statsPrint(rb2, 6, 2, 3, true);
  dumpPrint<int>(rb2, "*16 19 22 29 38 57 (rb2 - copy)", 3);
  RedBlackTree<int> rb3;
  rb3.insert(312);
  rb3 = rb2;
  rb2.deleteAll();
  rb2.insert(799);
  cout << endl << endl << "assign rb2 to rb3";
  statsPrint(rb3, 6, 2, 3, true);
  dumpPrint<int>(rb3, "*16 19 22 29 38 57 (assign)", 3);
  rb3 = rb3;
  dumpPrint<int>(rb3, "*16 19 22 29 38 57 (self assign)", 3);
}


void part2()
{
  cout << endl << endl << "REDBLACKTREE<STRING>";
  cout << endl << "insert file and print contents (load, dump)" << endl;
  RedBlackTree<string> rb;
  string fname = "part2.txt"; //should contain strings
  int n = 0;
 
  // read file and load contents into tree
  string* arr = readFile<string>(fname, n);
  rb.load(arr, n);
 
  // read contents from tree into array
  int out_n = 0;
  string* out = rb.dump(out_n);
 
  // print dumped contents
  int count = 0;
  for(int i=0; i < out_n; i++){
         if(count % 5 == 0){
                 cout << endl;
         }
         cout << left << setw(13) << out[i];
         count ++;
  }
  cout << endl;
  statsPrint(rb, 174, 5, 9, true);
 
  // remove all items from tree
  cout << endl << endl << "empty tree one item at a time";
  for(int i=0; i < n; i++){
         rb.remove(arr[i]);
  }
  statsPrint(rb, 0, 0, 0, true);
 
  delete[] arr;
  delete[] out;
}

template <class T>
void statsPrint(const RedBlackTree<T> & rb, int n, int bh, int h, bool rc)
{
  cout << endl << "n = " << rb.size() << " [" << n << "]";
  cout << ", bh = " << rb.b_height() << " [" << bh << "]";
  cout << ", ht = " << rb.height() << " [" << h << "]";
  cout << ", red check: " << rb.redCheck() << " [" << rc << "]";
}

template <class T>
void dumpPrint(const RedBlackTree<T> & rb, string result, int space)
{
  int n = 0;
  T* out = rb.dump(n);
  cout << endl;
  for(int i=0; i < n; i++){
         cout << setw(space) << out[i];
  }
  cout << endl << result;
  delete[] out;
}

// Opens a file and reads the contents into an array
// PARAM: fname is the name of the file to be opened
//        n is the size of the result
// PRE: the file contains values separated by white space
// POST: n is set to the size of the result
template <class T>
T* readFile(string infile, int & n)
{
  T* result;
  T next;
  n = 0;
 
  ifstream ist(infile.c_str()); // open file
  // Check if file opened correctly
  if(ist.fail())
         throw runtime_error("file not found");
    
  // Find file size
  while(ist >> next){
         n++;
  }
 
  // Read file into array
  ist.close();
  ist.open(infile.c_str());
  result = new T[n];
  for(int i=0; i < n; ++i){
         ist >> result[i];
  }
  ist.close();
 
  return result;
}



