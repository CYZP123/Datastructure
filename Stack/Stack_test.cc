#include <iostream>

#include "Stack.h"

using namespace std;

int main() {
  sub::Stack<int> s;

  s.Push(100);
  cout << s.Size() << endl;
  cout << s.Top() << endl;
  cout << s.Pop() << endl;
  cout << s.Size() << endl;

  cout << s.Pop() << endl;
}