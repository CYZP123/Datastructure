#include <iostream>

using namespace std;

#include "BinaryTree.h"
#define BinNodePosi(T) sub::BinNode<T> *  // Node position

struct Visit {
  virtual void operator()(const char data) { cout << data << ", "; }
};

int main() {
  sub::BinTree<char> btree;
  BinNodePosi(char) i = btree.InsertAsRoot('i');

  BinNodePosi(char) d = btree.InsertAsLChild(i, 'd');
  BinNodePosi(char) l = btree.InsertAsRChild(i, 'l');

  BinNodePosi(char) c = btree.InsertAsLChild(d, 'c');
  BinNodePosi(char) h = btree.InsertAsRChild(d, 'h');
  BinNodePosi(char) k = btree.InsertAsLChild(l, 'k');
  BinNodePosi(char) n = btree.InsertAsRChild(l, 'n');

  cout << "The Tree size is " << btree.Size() << endl;
  Visit visit;
  btree.TravPost_R(visit);
  cout << endl;
}