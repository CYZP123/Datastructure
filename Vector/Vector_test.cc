#include <iostream>

#include "Vector.h"

using namespace std;


int main() {
  sub::Vector<int> v;

  v.Report("Init");
  v.Insert(0, 9);
  v.Insert(0, 4);
  v.Report("Insert(0, 4) Insert(0, 9)");

  v.Insert(1, 5);
  v.Report("Insert(1, 5)");
  v.Put(1, 2);
  v.Report("Put(1, 2)");
  
  cout << "Get(2) = " << v.Get(2) << endl;

  v.Insert(3, 6);
  v.Report("v.Insert(3, 6)");
  v.Insert(3, 6);
  v.Report("v.Insert(3, 6)");

  v.Insert(1, 7);
  v.Report("insert(1, 7)");  // 4,7,2,9,6
  v.Remove(2);
  v.Report("remove(2)");  // 4,7,9,6
  v.Insert(1, 3);
  v.Report("insert(1,3)");  // 4,3,7,9,6
  v.Insert(3, 4);
  v.Report("insert(3, 4)");  // 4,3,7,4,9,6
  cout << "size()=" << v.Size() << endl;

  cout << "disordered()=" << v.DisOrdered() << endl;  // 3
  cout << "find(9)=" << v.Find(9) << endl;            // 4
  cout << "find(5)=" << v.Find(5) << endl;            //-1

}


