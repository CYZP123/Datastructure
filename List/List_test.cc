#include <iostream>

#include "List.h"

using namespace std;

int main() {
  sub::List<int> v;
  v.Report("Init");
  
  v.InsertAsFirst(4);
  v.InsertAsFirst(9);
  v.Report("InsertAsFirst(4), InsertAsFirst(9)");

  sub::ListNode<int> *p = v.First();
  v.InsertAfter(p, 5);
  v.Report("InsertAfter(5)");

  p = v.First();
  v.InsertBefore(p, 2);
  v.Report("InsertBefore(first, 2)");
  cout << "last=" << v.Last()->data_ << endl;

  v.InsertAsFirst(100);
  p = v.First();
  cout << "removed=" << v.Remove(p) << endl;

  v.InsertAsFirst(8);
  v.InsertAsFirst(7);
  v.InsertAsFirst(5);
  v.InsertAsFirst(2);
  v.InsertAsFirst(4);

  v.Report("ori");

  sub::List<int> v1;
  v1.InsertAsLast(1);
  v1.InsertAsLast(1);
  v1.InsertAsLast(2); 
  v1.InsertAsLast(3); 
  v1.InsertAsLast(4);
  v1.Uniquify();
  v1.Report("Uniquify");  

  v1.Reverse();
  v1.Report("Reverse");
  v1.Reverse2();
  v1.Report("Reverse2");
  v1.Reverse3();
  v1.Report("Reverse3");
}


