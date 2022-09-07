#include <iostream>

#include "Queue.h"

using namespace std;

int main() {
  sub::Queue<int> q;

  for (size_t i = 0; i < 10; ++i)
    q.Enqueue(i);

  while (!q.Empty()) {
    cout << q.Dequeue() << endl;
  }
}